enum
{
    TYPE_WARN = 1,
    TYPE_JAIL,
    TYPE_BAN
}

stock JailUser(playerid, targetid, minutes, fee, reason[])
{
    AccountData[targetid][pJail] = 1;
    AccountData[targetid][pJailTime] = minutes * 60;
    format(AccountData[targetid][pJailReason], 126, reason);
    format(AccountData[targetid][pJailBy], MAX_PLAYER_NAME, AccountData[playerid][pAdminname]);
    TakeMoney(targetid, fee);
    SendClientMessageToAllEx(X11_DARKORANGE, "[AdmCmd] %s(%d) telah dijail selama %d menit terkena denda sebesar %s oleh %s", ReturnName(targetid), targetid, minutes, FormatMoney(fee), AccountData[playerid][pAdminname]);
	SendClientMessageToAllEx(X11_DARKORANGE, "Reason ~> %s", reason);
    SpawnPlayerInJail(targetid);
    SetCameraBehindPlayer(targetid);
    UpdatePlayerData(targetid);

    new string[192];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `warninglogs` (`pID`, `WarnType`, `WarnReason`, `WarnSender`, `WarnTime`) VALUES('%d', '%d', '%e', '%e', '%d')", AccountData[targetid][pID], TYPE_JAIL, reason, AccountData[playerid][pAdminname], gettime());
    mysql_tquery(g_SQL, string);
    return 1;
}

stock GetTotalWarning(playerid)
{
    new query[128], Cache:result, total = 0;
    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `warninglogs` WHERE `pID` = '%d' AND `WarnType` = '%d'", AccountData[playerid][pID], TYPE_WARN);
    result = mysql_query(g_SQL, query, true);
    if(cache_num_rows())
    {
        return total = cache_num_rows();
    }
    cache_delete(result);
    return total;
}

forward OnWarnUser(playerid, targetid, reason[]);
public OnWarnUser(playerid, targetid, reason[])
{
    SendClientMessageToAllEx(X11_ORANGERED, "[AdmCmd] %s(%d) telah diberikan warning oleh %s (%d warning)", ReturnName(targetid), targetid, AccountData[playerid][pAdminname], GetTotalWarning(targetid));
    SendClientMessageToAllEx(X11_ORANGERED, "Reason: %s", reason);
    return 1;
}

stock WarnUser(playerid, targetid, reason[])
{
    new string[192];
    mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `warninglogs` (`pID`, `WarnType`, `WarnReason`, `WarnSender`, `WarnTime`) VALUES('%d', '%d', '%e', '%e', '%d')", AccountData[targetid][pID], TYPE_WARN, reason, AccountData[playerid][pAdminname], gettime());
    mysql_tquery(g_SQL, string, "OnWarnUser", "dds", playerid, targetid, reason);
    return 1;
}

stock OfflineWarnUser(playerid, name[], reason[])
{
    new sqlid;
    new string[192];

    mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `player_characters` WHERE `Char_Name`='%e' LIMIT 1", name);
    mysql_query(g_SQL, string, true);
    if(cache_num_rows())
    {
        cache_get_value_name_int(0, "pID", sqlid);
        mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `warninglogs` (`pID`, `WarnType`, `WarnReason`, `WarnSender`, `WarnTime`) VALUES('%d', '%d', '%e', '%e', '%d')", sqlid, TYPE_WARN, reason, AccountData[playerid][pAdminname], gettime());
        mysql_query(g_SQL, string, false);

        SendClientMessageToAllEx(X11_ORANGERED, "[AdmCmd] %s telah diberikan offline warning oleh "RED"%s", name, AccountData[playerid][pAdminname]);
        SendClientMessageToAllEx(X11_ORANGERED, "Reason: %s", reason);
    }
    else
    {
        Error(playerid, "Tidak ditemukan akun dengan nama "RED"%s", name);
    }
    return 1;
}

stock ShowPlayerWarning(playerid, targetid)
{
    new const warntype[][] = {
        "Unknows",
        "{00FF00}Warning",
		"{FFFF00}OOC Jail",
		"{FF0000}Banned"
    };
    new query[128], shstr[1012];
    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `warninglogs` WHERE `pID` = '%d'", AccountData[playerid][pID]);
    mysql_query(g_SQL, query, true);
    if(cache_num_rows())
    {
        format(shstr, sizeof(shstr), "Type\tPenerbit\tTanggal\tAlasan\n");
        forex(i, cache_num_rows())
        {
            new type, sender[64], date, reason[128];
            cache_get_value_name_int(i, "WarnType", type);
            cache_get_value_name(i, "WarnSender", sender);
            cache_get_value_name_int(i, "WarnTime", date);
            cache_get_value_name(i, "WarnReason", reason);
            format(shstr, sizeof(shstr), "%s%s\t%s\t%s\t%s\n", shstr, warntype[type], sender, ReturnDateNoTime(date), reason);
        }
        ShowPlayerDialog(targetid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Riwayat Peringatan", shstr, "Tutup", "");
    }
    else
    {
        Error(playerid, "Player tersebut tidak memiliki warning!");
    }
    return 1;
}

CMD:mywarn(playerid, params[])
{
    ShowPlayerWarning(playerid, playerid);
    return 1;
}

CMD:owarn(playerid, params[])
{
    new name[24], reason[64];
    
    if(AccountData[playerid][pAdmin] < 1) 
        return PermissionError(playerid);
    
    if(sscanf(params, "s[24]s[64]", name, reason))  
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/owarn [player name]");
    
    if(!IsRoleplayName(name))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid penggunaan PlayerName (Gunakan _ sebagai spasi)");

    if(strlen(reason) > 64)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Max reason hanya sampai 64 characters!");
    
    OfflineWarnPlayer(playerid, name, reason);
    return 1;
}

CMD:warn(playerid, params[])
{
    new otherid, reason[64];

    if(AccountData[playerid][pAdmin] < 1)
        return PermissionError(playerid);

    if(sscanf(params, "us[64]", otherid, reason))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/warn [name/playerid]");
    
    if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    
    if(strlen(reason) > 64) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Max reason hanya sampai 64 characters!");
    
    WarnUser(playerid, otherid, reason);
    return 1;
}

CMD:unwarn(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1)
        return PermissionError(playerid);
    
    new userid;
    if(sscanf(params, "u", userid))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/unwarn [name/playerid]");
    
    if(!IsPlayerConnected(userid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
  
    AccountData[userid][pWarn] -= 1;
    SendClientMessageEx(userid, X11_ORANGERED, "[AdmCmd] %s telah menghapus 1 point warning anda (%d warning)", AccountData[playerid][pAdminname], AccountData[userid][pWarn]);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menghapus 1 point warning player "YELLOW"%s(%d).", AccountData[playerid][pAdminname], ReturnName(userid), userid);
    return 1;
}

CMD:clearwarn(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);
    
    new otherid;
    if(sscanf(params, "u", otherid)) 
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/clearwarn [name/playerid]");
    
    if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    
    AccountData[otherid][pWarn] = 0;
    SendClientMessageEx(otherid, X11_ORANGERED, "[AdmCmd] %s telah menghapus membersihkan seluruh riwayat peringatan anda (%d warning)", AccountData[playerid][pAdminname], AccountData[otherid][pWarn]);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menghapus semua point warning player "YELLOW"%s(%d).", AccountData[playerid][pAdminname], ReturnName(otherid), otherid);
    
    new query[178];
    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `warninglogs` WHERE `pID`='%d'", AccountData[otherid][pID]);
    mysql_query(g_SQL, query, false);
    return 1;
}

CMD:ajail(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1)
        return PermissionError(playerid);
    
    new count = 0, list[1248];
    format(list, sizeof(list), "Player\tJail By\tReason\tDuration\n");
    foreach(new i : Player) if (IsPlayerConnected(i) && AccountData[i][pSpawned])
    {
        if(AccountData[i][pJail])
        {
            new hours, minutes, seconds;
            GetElapsedTime(AccountData[i][pJailTime], hours, minutes, seconds);
            format(list, sizeof(list), "%s%s(%d)\t"YELLOW"%s\t"RED"%s\t"WHITE"%02d jam %02d menit\n", list, ReturnName(i), i, AccountData[i][pJailBy], AccountData[i][pJailReason], hours, minutes);
            count ++;
        }
    }
    if(count == 0)
		Error(playerid, "Tidak ada pemain yang sedang di jail!");
	else 
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Player Jail", list, "Close", "");
	return 1;
}

CMD:jail(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1)
        return PermissionError(playerid);
    
    new otherid, minutes, fee, reason[126];
    if(sscanf(params, "udds[126]", otherid, minutes, fee, reason))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/jail [name/playerid] [menit] [denda] [alasan]");
    
    if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    
    if(AccountData[otherid][pAdmin] > AccountData[playerid][pAdmin])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memenjarakan level admin diatas anda!");
    
    if(minutes < 1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak bisa menjail pemain dibawah 1 menit!");
    
    if(fee < 0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak bisa memberikan denda dibawah $0!");
    
    AccountData[otherid][pInjured] = 0;
    AccountData[otherid][pInjuredTime] = 0;
    JailUser(playerid, otherid, minutes, fee, reason);

    static shstr[178];
    format(shstr, sizeof(shstr), "Menggunakan cmd /jail kepada pemain %s selama %d menit + %s denda", AccountData[otherid][pName], minutes, FormatMoney(fee));
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), shstr);
	return 1;
}

forward OnOfflineJailed(playerid, name[], reason[], fee, time);
public OnOfflineJailed(playerid, name[], reason[], fee, time)
{
    new rows = cache_num_rows(), sqlid;
    if(rows)
    {
        cache_get_value_name_int(0, "pID", sqlid);

        new cQuery[256];
        mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_characters` SET `Char_Jail` = 1, `Char_JailTime` = '%d', `Char_JailReason` = '%e', `Char_Money` = `Char_Money` - '%d' WHERE `pID` = '%d'", time * 60, reason, fee, sqlid);
        mysql_query(g_SQL, cQuery, false);

        new string[192];
        mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `warninglogs` (`pID`, `WarnType`, `WarnReason`, `WarnSender`, `WarnTime`) VALUES('%d', '%d', '%e', '%e', '%d')", sqlid, TYPE_JAIL, reason, AccountData[playerid][pAdminname], gettime());
        mysql_query(g_SQL, string, false);

        SendClientMessageToAllEx(X11_ORANGERED, "[AdmCmd] %s telah dijail (offline) dan didenda sebesar %s oleh %s", name, FormatMoney(fee), AccountData[playerid][pAdminname]);
        SendClientMessageToAllEx(X11_ORANGERED, "Reason: %s", reason);
    }
    else
    {
        Error(playerid, "Tidak ditemukan akun dengan nama %s", name);
    }
    return 1;
}

CMD:ojail(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1)
        return PermissionError(playerid);
    
    new
        minutes, name[24], reason[64], fee;
    
    if(sscanf(params, "s[24]dds[64]", name, minutes, fee, reason)) 
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/ojail [player name] [menit] [denda] [alasan]");
    
    foreach(new i : Player) if (!strcmp(AccountData[i][pName], name, true))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang online, gunakan '/jail'");
    
    new characterQuery[178];
    mysql_format(g_SQL, characterQuery, sizeof(characterQuery), "SELECT * FROM `player_characters` WHERE `Char_Name`='%s' LIMIT 1", name);
    mysql_tquery(g_SQL, characterQuery, "OnOfflineJailed", "dssdd", playerid, name, reason, fee, minutes);
    return 1;
}
