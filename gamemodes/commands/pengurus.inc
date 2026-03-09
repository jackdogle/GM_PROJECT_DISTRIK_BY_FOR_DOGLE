#include <YSI\y_hooks>

SSCANF:VotingMenu(string[])
{
    if(!strcmp(string,"create",true)) return 1;
    else if(!strcmp(string,"end",true)) return 2;
    return 0;
}

alias:gmessage("serverann")
CMD:gmessage(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    if(!AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty untuk menggunakan perintah ini!");

    new text[256];
    if(sscanf(params, "s[256]", text)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gmessage [pesan]");
    if(strlen(text) < 1 || strlen(text) > 256) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pesan tidak dapat kurang dari 1 atau lebih dari 256 characters!");
    
    ShowGlobalMessage(playerid, text, 7000);
    return 1;
}

CMD:vote(playerid, params[])
{
    static action, nextParams[128];
    
    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    if(!AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty untuk menggunakan perintah ini!");
    
    if(sscanf(params, "k<VotingMenu>S()[128]", action, nextParams))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/vote (create, end)");
    
    switch(action)
    {
        case 1: 
        {
            new string[128], time;
            if(sscanf(nextParams, "ds[128]", time, string)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/voting [lama waktu voting (menit)] [text]");
            if(strlen(string) > 128) return ShowTDN(playerid, NOTIFICATION_ERROR, "Max Characters 128 only!");
            if(time < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat memasukkan waktu dibawah 1 menit!");
            if(OpenVote || VoteTime != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sudah ada voting yang sedang berjalan sekarang!");

            OpenVote = 1;
            VoteTime = gettime() + time*60;
            format(VoteText, sizeof(VoteText), string);
            SendClientMessageToAllEx(X11_ARWIN, "[AdmCmd]"RED" %s"ARWIN1" telah memulai Voting. Waktu Voting Hanya "YELLOW"%d Menit", AccountData[playerid][pAdminname], time);
            SendClientMessageToAllEx(-1, ""YELLOW"VOTE:"WHITE" %s // YES: %d // NO: %d", VoteText, VoteYes, VoteNo);
            SendClientMessageToAllEx(-1, "~> Gunakan "GREEN"Y"WHITE" untuk Yes & "RED"N"WHITE" untuk Tidak");
        }
        case 2: 
        {
            if(!OpenVote) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada voting yang sedang berlangsung!");

            OpenVote = 0;
            VoteYes = 0;
            VoteNo = 0;
            VoteTime = 0;
            VoteText[0] = EOS;
            foreach(new i : Player) if (IsPlayerConnected(i))
            {
                PlayerVoting[playerid] = false;
            }
            SendClientMessageToAllEx(X11_ARWIN, "[AdmCmd]"RED" %s"ARWIN1" telah menghentikan Voting Server yang sedang berlangsung!", AccountData[playerid][pAdminname]);
        }
    }
    return 1;
}

CMD:oresetweap(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    if(!AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty untuk menggunakan perintah ini!");
    
    new playerName[32];
    if(sscanf(params, "s[32]", playerName)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/resetweapoff [player name]");
    foreach(new i : Player) if (IsPlayerConnected(i) && AccountData[i][pSpawned])
    {
        if(!strcmp(AccountData[i][pName], playerName, true))
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang online!");
            return 1;
        }
    }

    new string[178];
    mysql_format(g_SQL, string, sizeof(string), "SELECT * FROM `player_characters` WHERE `Char_Name`='%s'", playerName);
    mysql_tquery(g_SQL, string, "OffResetWeapon", "ds", playerid, playerName);
    return 1;
}

forward OffResetWeapon(playerid, name[]);
public OffResetWeapon(playerid, name[])
{
    if(!cache_num_rows())
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Tidak ditemukan akun dengan nama %s", name));
    }
    else
    {
        new RegID, string[178];
        cache_get_value_name_int(0, "pID", RegID);

        for(new i = 0; i < 13; i++) {
            mysql_format(g_SQL, string, sizeof(string), "UPDATE `player_characters` SET `Gun%d`=0, `Ammo%d`=0 WHERE `pID`=%d", i+1, i+1, RegID);
            mysql_query(g_SQL, string, false);
        }
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mereset (offline) senjata milik player "YELLOW"%s", AccountData[playerid][pAdminname], name);
    }
    return 1;
}

CMD:resetplaytime(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    if(!AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty untuk menggunakan perintah ini!");

    new otherid;
    if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/resetplaytime [name/playerid]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    AccountData[otherid][OnlineTimer] = 0;
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mereset playtime "YELLOW"%s(%d)", AccountData[playerid][pAdminname], AccountData[otherid][pName], otherid);
    return 1;
}

CMD:clearwarn(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    if(!AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty untuk menggunakan perintah ini!");
    
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

alias:setredmoney("srm")
CMD:setredmoney(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    if(!AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty untuk menggunakan perintah ini!");

    new otherid, value;
    if(sscanf(params, "ud", otherid, value)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setredmoney [name/playerid] [ammount]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(value < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal kurang dari $0!");

    AccountData[otherid][pRedMoney] = value;
    SendClientMessageEx(otherid, X11_ARWIN, "[AdmCmd]"RED" %s"ARWIN1" menetapkan Red Money anda menjadi "RED"%s", AccountData[playerid][pAdminname], FormatMoney(value));
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menetapkan Red Money pemain "YELLOW"%s(%d)"ARWIN1" menjadi "RED"%s", AccountData[playerid][pAdminname], AccountData[otherid][pName], otherid, FormatMoney(value));
    
    new shstr[255];
    format(shstr, sizeof(shstr), "Menggunakan command /setmoney kepada UCP:[%s] Name:[%s] Dengan Value $%d", AccountData[otherid][pUCP], AccountData[otherid][pName], value);
    AddAdminLog(AccountData[playerid][pUCP], AccountData[playerid][pName], GetStaffRank(playerid), shstr);
    return 1;
}

alias:setfaction("setfact")
CMD:setfaction(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;

    if(AccountData[playerid][pAdmin] < 7 && AccountData[playerid][pHandleGoodside] < 1) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Management & Handle Goodside!");

    if(!AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty untuk menggunakan perintah ini!");

    new otherid, fid, rank, tss[128];
    if(sscanf(params, "udd", otherid, fid, rank)) 
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setfaction [name/playerid], [faction id] [pangkat]");
    if(!IsPlayerConnected(otherid)) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(fid < 0 || fid > 7) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Faction ID tidak valid! (0 - 7)");
    if(rank < 0 || rank > 15) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Rank ID tidak valid! (0 - 15)");

    if(AccountData[playerid][pAdmin] < 7)
    {
        if(AccountData[playerid][pHandleGoodside] >= 1 && rank > 2)
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Handle Goodside hanya bisa set rank sampai 2!");
        }
    }
    if(fid == FACTION_NONE)
    {
        AccountData[otherid][pFaction] = FACTION_NONE;
        AccountData[otherid][pFactionRank] = 0;

        RefreshFactionMap(otherid);
        SendClientMessageEx(otherid, X11_ARWIN, "[AdmCmd] "RED"%s"ARWIN1" telah menghapus faction anda.", GetAdminName(playerid));
        SendStaffMessage(X11_GRAY, ""RED"%s"ARWIN1" telah menghapus faction "YELLOW"%s(%d).", GetAdminName(playerid), AccountData[otherid][pName], otherid);
        
        mysql_format(g_SQL, tss, sizeof(tss), "UPDATE player_characters SET Char_Faction=0, Char_FactionRank=0 WHERE pID=%d", AccountData[otherid][pID]);
        mysql_tquery(g_SQL, tss);
    }
    else 
    {
        AccountData[otherid][pFaction] = fid;
        AccountData[otherid][pFactionRank] = rank;

        RefreshFactionMap(otherid);
        SendClientMessageEx(otherid, X11_ARWIN, "[AdmCmd] "RED"%s"ARWIN1" telah menetapkan anda menjadi Factions "YELLOW"%s - %s.", GetAdminName(playerid), GetFactName(otherid), GetFactionRank(otherid));
        SendStaffMessage(X11_GRAY, ""RED"%s"ARWIN1" telah menetapkan Factions "YELLOW"%s(%d) - %s - %s.", GetAdminName(playerid), AccountData[otherid][pName], otherid, GetFactName(otherid), GetFactionRank(otherid));
        
        mysql_format(g_SQL, tss, sizeof(tss), "UPDATE player_characters SET Char_Faction=%d, Char_FactionRank=%d WHERE pID=%d", fid, rank, AccountData[otherid][pID]);
        mysql_tquery(g_SQL, tss);
    }
    static tmp[125];
    format(tmp, sizeof(tmp), "Menggunakan cmd /setfaction kepada %s menjadi Faction %s - %s.", AccountData[otherid][pName], GetFactName(otherid), GetFactionRank(otherid));
    AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), tmp);
    return 1;
}

CMD:playnearsong(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    if(!AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty untuk menggunakan perintah ini!");

    new songname[128], tmp[512], Float:x, Float:y, Float:z;
    if (sscanf(params, "s[128]", songname))
    {
        ShowTDN(playerid, NOTIFICATION_SYNTAX, "/playnearsong <link>");
        return 1;
    }
    
    GetPlayerPos(playerid, x, y, z);
    format(tmp, sizeof(tmp), "%s", songname);
    foreach(new ii : Player)
    {
        if(IsPlayerInRangeOfPoint(ii, 35.0, x, y, z))
        {
            PlayAudioStreamForPlayer(ii, tmp, x, y, z, 35.0, 1);
            Info(ii, "/stopsong, /togsong");
        }
    }
    return 1;
}

alias:updatedb("saveall", "saveallplayer", "backupdb")
CMD:updatedb(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    if(!AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty untuk menggunakan perintah ini!");

    foreach(new i : Player) if (IsPlayerConnected(i))
    {
        UpdatePlayerData(i);
    }
    foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists])
    {
        SavePlayerVehicle(i);
    }
    SendClientMessageToAllEx(X11_ARWIN, "[AdmCmd] "RED"%s"ARWIN1" Telah membackup semua data pemain online ke "DEEPSKYBLUE1"District Database", AccountData[playerid][pAdminname]);
    return 1;
}

CMD:setname(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    if(!AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty untuk menggunakan perintah ini!");

    new otherid, frmtname[24];
    if(sscanf(params, "us[24]", otherid, frmtname)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setname [name/playerid] [new name]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(strlen(frmtname) < 4 || strlen(frmtname) > 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Nama tidak boleh kurang dari 4 character atau lebih dari 24 characters!");
    if(!IsValidName(frmtname)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Format nama tidak valid!");

    new query[255];
    mysql_format(g_SQL, query, sizeof(query), "SELECT `Char_Name` FROM `player_characters` WHERE `Char_Name`='%s'", frmtname);
    mysql_tquery(g_SQL, query, "ChangedName", "dds", otherid, playerid, frmtname);
    return 1;
}

forward ChangedName(otherPlayer, playerid, const name[]);
public ChangedName(otherPlayer, playerid, const name[])
{
    if(!cache_num_rows())
    {
        new oldname[24], newname[24], query[255];
        GetPlayerName(otherPlayer, oldname, sizeof(oldname));

        mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_Name`='%s' WHERE `pID`=%d", name, AccountData[otherPlayer][pID]);
        mysql_tquery(g_SQL, query);

        for(new id; id < MAX_RUMAH; id++) if (HouseData[id][hsOwnerID] == AccountData[otherPlayer][pID]) 
        {
            format(HouseData[id][hsOwner], MAX_PLAYER_NAME, name);
            HouseRefresh(id);
            HouseSave(id);
        }

        for(new id; id < MAX_DYNAMIC_RUSUN; id++) if (RusunData[id][rusunOwnerID] == AccountData[otherPlayer][pID])
        {
            format(RusunData[id][rusunOwner], MAX_PLAYER_NAME, name);
            Rusun_Refresh(id);
            Rusun_Save(id);
        }   

        for(new id; id < MAX_FAMILIES; id ++) if(!strcmp(FamData[id][famLeader], oldname, true))
        {
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `families` SET `F_Leader`='%s' WHERE `F_Leader`='%s'", name, oldname);
            mysql_tquery(g_SQL, query);
        }

        if(AccountData[playerid][PurchasedToy])
        {
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `toys` SET `Owner`='%s' WHERE `Owner`='%s'", name, oldname);
            mysql_tquery(g_SQL, query);
        }
        if(AccountData[playerid][PurchasedToyAxp])
        {
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `toys_axp` SET `Owner`='%s' WHERE `Owner`='%s'", name, oldname);
            mysql_tquery(g_SQL, query);
        }
        if(AccountData[playerid][PurchasedDragonToy])
        {
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `dragon_toys` SET `Owner`='%s' WHERE `Owner`='%s'", name, oldname);
            mysql_tquery(g_SQL, query);
        }
        if(AccountData[playerid][PurchasedSonicToy])
        {
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `sonic_toys` SET `Owner`='%s' WHERE `Owner`='%s'", name, oldname);
            mysql_tquery(g_SQL, query);
        }
        if(AccountData[playerid][PurchasedGrinchToy])
        {
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `grinch_toys` SET `Owner`='%s' WHERE `Owner`='%s'", name, oldname);
            mysql_tquery(g_SQL, query);
        }
        if(AccountData[playerid][PurchasedGhostToy])
        {
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `ghost_toys` SET `Owner`='%s' WHERE `Owner`='%s'", name, oldname);
            mysql_tquery(g_SQL, query);
        }

        SendClientMessageEx(otherPlayer, X11_ARWIN, "[AdmCmd] "RED"%s"ARWIN1" telah mengubah nama anda. "YELLOW"%s ~> %s", AccountData[playerid][pAdminname], oldname, name);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengubah nama pemain "YELLOW"%s(%d)"ARWIN1" menjadi "YELLOW"%s", AccountData[playerid][pAdminname], oldname, otherPlayer, name);

        SetPlayerName(otherPlayer, name);
        GetPlayerName(otherPlayer, newname, sizeof(newname));
        AccountData[otherPlayer][pName] = newname;
    }
    else 
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Sudah ada akun dengan nama %s di database!", name));
    }
    return 1;
}