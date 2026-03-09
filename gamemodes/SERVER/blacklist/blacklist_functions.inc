#include <YSI\y_hooks>

enum _:EBlacklistData
{
    PDIssuer[64],
    PDIssuerRank[100],
    PDReason[128],
    PDDur,

    PEMERIssuer[64],
    PEMERIssuerRank[100],
    PEMERReason[128],
    PEMERDur,

    EMSIssuer[64],
    EMSIssuerRank[100],
    EMSReason[128],
    EMSDur,

    BENGKELIssuer[64],
    BENGKELIssuerRank[100],
    BENGKELReason[128],
    BENGKELDur,

    PEDAIssuer[64],
    PEDAIssuerRank[100],
    PEDAReason[128],
    PEDADur
};
new BlackListInfo[MAX_PLAYERS][_:EBlacklistData];

CMD:unblacklist(playerid, params[])
{
    if(AccountData[playerid][pFaction] == FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari instansi pemerintah!");
    if(AccountData[playerid][pFaction] == FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Gojek tidak dapat memblacklist!");

    new 
        otherid
    ;
    if(sscanf(params, "d", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/unblacklist [playerid]");
    if(otherid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat unblacklist diri sendiri!");
    if(otherid == INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke dalam server!");
    if(!IsPlayerNearPlayer(playerid, otherid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus berada di dekat anda!");
    switch(AccountData[playerid][pFaction])
    {
        case 1:// Polisi
        {
            if(BlackListInfo[otherid][PDDur] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terblacklist di kepolisian!");

            format(BlackListInfo[otherid][PDIssuer], 64, "");
            format(BlackListInfo[otherid][PDIssuerRank], 64, "");
            format(BlackListInfo[otherid][PDReason], 64, "");
            BlackListInfo[otherid][PDDur] = 0;
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil menghapus nama %s dari daftar blacklist kepolisian!", ReturnName(otherid)));
            ShowTDN(otherid, NOTIFICATION_WARNING, sprintf("Petugas %s menghapus nama anda dari daftar blacklist kepolisian!", ReturnName(playerid)));

            new query[512];
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `blacklist_players` SET `PoliceIssuer`='', `PoliceIssuerRank`='', `PoliceReason`='', `PoliceDuration`=0 WHERE `PID`=%d", AccountData[otherid][pID]);
            mysql_tquery(g_SQL, query);
        }
        case 2:// pemerintah
        {
            if(BlackListInfo[otherid][PEMERDur] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terblacklist di pemerintahan!");

            format(BlackListInfo[otherid][PEMERIssuer], 64, "");
            format(BlackListInfo[otherid][PEMERIssuerRank], 64, "");
            format(BlackListInfo[otherid][PEMERReason], 64, "");
            BlackListInfo[otherid][PEMERDur] = 0;
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil menghapus nama %s dari daftar blacklist pemerintahan!", ReturnName(otherid)));
            ShowTDN(otherid, NOTIFICATION_WARNING, sprintf("Petugas %s menghapus nama anda dari daftar blacklist pemerintahan!", ReturnName(playerid)));

            new query[512];
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `blacklist_players` SET `PemerintahIssuer`='', `PemerintahIssuerRank`='', `PemerintahReason`='', `PemerintahDuration`=0 WHERE `PID`=%d", AccountData[otherid][pID]);
            mysql_tquery(g_SQL, query);
        }
        case 3:// ems
        {
            if(BlackListInfo[otherid][EMSDur] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terblacklist di EMS!");

            format(BlackListInfo[otherid][EMSIssuer], 64, "");
            format(BlackListInfo[otherid][EMSIssuerRank], 64, "");
            format(BlackListInfo[otherid][EMSReason], 64, "");
            BlackListInfo[otherid][EMSDur] = 0;
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil menghapus nama %s dari daftar blacklist EMS!", ReturnName(otherid)));
            ShowTDN(otherid, NOTIFICATION_WARNING, sprintf("Petugas %s menghapus nama anda dari daftar blacklist EMS!", ReturnName(playerid)));

            new query[512];
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `blacklist_players` SET `EMSIssuer`='', `EMSIssuerRank`='', `EMSReason`='', `EMSDuration`=0 WHERE `PID`=%d", AccountData[otherid][pID]);
            mysql_tquery(g_SQL, query);
        }
        case 5:// bengkel
        {
            if(BlackListInfo[otherid][BENGKELDur] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terblacklist di bengkel!");

            format(BlackListInfo[otherid][BENGKELIssuer], 64, "");
            format(BlackListInfo[otherid][BENGKELIssuerRank], 64, "");
            format(BlackListInfo[otherid][BENGKELReason], 64, "");
            BlackListInfo[otherid][BENGKELDur] = 0;
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil menghapus nama %s dari daftar blacklist bengkel!", ReturnName(otherid)));
            ShowTDN(otherid, NOTIFICATION_WARNING, sprintf("Petugas %s menghapus nama anda dari daftar blacklist bengkel!", ReturnName(playerid)));

            new query[512];
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `blacklist_players` SET `BengkelIssuer`='', `BengkelIssuerRank`='', `BengkelReason`='', `BengkelDuration`=0 WHERE `PID`=%d", AccountData[otherid][pID]);
            mysql_tquery(g_SQL, query);
        }
        case 6:// pedagang
        {
            if(BlackListInfo[otherid][PEDADur] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terblacklist di pedagang!");

            format(BlackListInfo[otherid][PEDAIssuer], 64, "");
            format(BlackListInfo[otherid][PEDAIssuerRank], 64, "");
            format(BlackListInfo[otherid][PEDAReason], 64, "");
            BlackListInfo[otherid][PEDADur] = 0;
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil menghapus nama %s dari daftar blacklist pedagang!", ReturnName(otherid)));
            ShowTDN(otherid, NOTIFICATION_WARNING, sprintf("Petugas %s menghapus nama anda dari daftar blacklist pedagang!", ReturnName(playerid)));

            new query[512];
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `blacklist_players` SET `PedagangIssuer`='', `PedagangIssuerRank`='', `PedagangReason`='', `PedagangDuration`=0 WHERE `PID`=%d", AccountData[otherid][pID]);
            mysql_tquery(g_SQL, query);
        }
    }
    return 1;
}

CMD:blacklist(playerid, params[])
{
    if(AccountData[playerid][pFaction] == FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari instansi pemerintah!");
    if(AccountData[playerid][pFaction] == FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Gojek tidak dapat memblacklist!");

    new 
        otherid,
        reason[128],
        query[4046]
    ;
    if(sscanf(params, "us[128]", otherid, reason)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/blacklist [playerid/Name] [reason]");
    if(otherid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat blacklist diri sendiri!");
    if(otherid == INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke dalam server!");
    if(!IsPlayerNearPlayer(playerid, otherid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus berada di dekat anda!");
    if(strlen(reason) > 128) return ShowTDN(playerid, NOTIFICATION_ERROR, "Max Reason 128 Characters!");
    switch(AccountData[playerid][pFaction])
    {
        case 1:// polisi
        {
            if(BlackListInfo[otherid][PDDur] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah diblacklist dari kepolisian!");

            format(BlackListInfo[otherid][PDIssuer], MAX_PLAYER_NAME, AccountData[playerid][pName]);
            format(BlackListInfo[otherid][PDIssuerRank], 128, PolisiRank[AccountData[playerid][pFactionRank]]);
            format(BlackListInfo[otherid][PDReason], 128, reason);
            BlackListInfo[otherid][PDDur] = 1;// 3600 detik x 24 x hasil input = hari

            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil memasukan seseorang ke daftar Blacklist!");
            SendClientMessageToAllEx(X11_GRAY, "POLDA %s | %s telah dimasukkan ke daftar blacklist. Alasan: %s", AccountData[playerid][pName], ReturnName(otherid), reason);
        
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `blacklist_players` SET `PoliceIssuer`='%s', `PoliceIssuerRank`='%s', `PoliceReason`='%s', `PoliceDuration`='%d 'WHERE `PID`='%d'", BlackListInfo[otherid][PDIssuer], BlackListInfo[otherid][PDIssuerRank], BlackListInfo[otherid][PDReason], BlackListInfo[otherid][PDDur], AccountData[otherid][pID]);
            mysql_tquery(g_SQL, query);
        }
        case 2:// pemerintah
        {
            if(BlackListInfo[otherid][PEMERDur] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah diblacklist dari pemerintahan!");

            format(BlackListInfo[otherid][PEMERIssuer], MAX_PLAYER_NAME, AccountData[playerid][pName]);
            format(BlackListInfo[otherid][PEMERIssuerRank], 128, PemerintahRank[AccountData[playerid][pFactionRank]]);
            format(BlackListInfo[otherid][PEMERReason], 128, reason);
            BlackListInfo[otherid][PEMERDur] = 1;// 3600 detik x 24 x hasil input = hari

            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil memasukan seseorang ke daftar Blacklist!");
            SendClientMessageToAllEx(X11_GRAY, "PEMERINTAH %s | %s telah dimasukkan ke daftar blacklist. Alasan: %s", AccountData[playerid][pName], ReturnName(otherid), reason);
        
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `blacklist_players` SET `PemerintahIssuer`='%s', `PemerintahIssuerRank`='%s', `PemerintahReason`='%s', `PemerintahDuration`='%d' WHERE `PID`='%d'", BlackListInfo[otherid][PEMERIssuer], BlackListInfo[otherid][PEMERIssuerRank], BlackListInfo[otherid][PEMERReason], BlackListInfo[otherid][PEMERDur], AccountData[otherid][pID]);
            mysql_tquery(g_SQL, query);
        }
        case 3:// EMS
        {
            if(BlackListInfo[otherid][EMSDur] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah diblacklist dari EMS!");

            format(BlackListInfo[otherid][EMSIssuer], MAX_PLAYER_NAME, AccountData[playerid][pName]);
            format(BlackListInfo[otherid][EMSIssuerRank], 128, EMSRank[AccountData[playerid][pFactionRank]]);
            format(BlackListInfo[otherid][EMSReason], 128, reason);
            BlackListInfo[otherid][EMSDur] = 1;// 3600 detik x 24 x hasil input = hari

            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil memasukan seseorang ke daftar Blacklist!");
            SendClientMessageToAllEx(X11_GRAY, "EMS %s | %s telah dimasukkan ke daftar blacklist. Alasan: %s", AccountData[playerid][pName], ReturnName(otherid), reason);
        
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `blacklist_players` SET `EMSIssuer`='%s', `EMSIssuerRank`='%s', `EMSReason`='%s', `EMSDuration`='%d' WHERE `PID`='%d'", BlackListInfo[otherid][EMSIssuer], BlackListInfo[otherid][EMSIssuerRank], BlackListInfo[otherid][EMSReason], BlackListInfo[otherid][EMSDur], AccountData[otherid][pID]);
            mysql_tquery(g_SQL, query);
        }
        case 5:// Bengkel
        {
            if(BlackListInfo[otherid][BENGKELDur] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah diblacklist dari bengkel!");

            format(BlackListInfo[otherid][BENGKELIssuer], MAX_PLAYER_NAME, AccountData[playerid][pName]);
            format(BlackListInfo[otherid][BENGKELIssuerRank], 128, BengkelRank[AccountData[playerid][pFactionRank]]);
            format(BlackListInfo[otherid][BENGKELReason], 128, reason);
            BlackListInfo[otherid][BENGKELDur] = 1;// 3600 detik x 24 x hasil input = hari

            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil memasukan seseorang ke daftar Blacklist!");
            SendClientMessageToAllEx(X11_GRAY, "BENGKEL %s | %s telah dimasukkan ke daftar blacklist. Alasan: %s", AccountData[playerid][pName], ReturnName(otherid), reason);
        
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `blacklist_players` SET `BengkelIssuer`='%s', `BengkelIssuerRank`='%s', `BengkelReason`='%s', `BengkelDuration`='%d' WHERE `PID`='%d'", BlackListInfo[otherid][BENGKELIssuer], BlackListInfo[otherid][BENGKELIssuerRank], BlackListInfo[otherid][BENGKELReason], BlackListInfo[otherid][BENGKELDur], AccountData[otherid][pID]);
            mysql_tquery(g_SQL, query);
        }
        case 6:// Pedagang
        {
            if(BlackListInfo[otherid][PEDADur] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah diblacklist dari pedagang!");

            format(BlackListInfo[otherid][PEDAIssuer], MAX_PLAYER_NAME, AccountData[playerid][pName]);
            format(BlackListInfo[otherid][PEDAIssuerRank], 128, PedagangRank[AccountData[playerid][pFactionRank]]);
            format(BlackListInfo[otherid][PEDAReason], 128, reason);
            BlackListInfo[otherid][PEDADur] = 1;// 3600 detik x 24 x hasil input = hari

            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil memasukan seseorang ke daftar Blacklist!");
            SendClientMessageToAllEx(X11_GRAY, "PEDAGANG %s | %s telah dimasukkan ke daftar blacklist Reason: %s", AccountData[playerid][pName], ReturnName(otherid), reason);
        
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `blacklist_players` SET `PedagangIssuer`='%s', `PedagangIssuerRank`='%s', `PedagangReason`='%s', `PedagangDuration`='%d' WHERE `PID`='%d'", BlackListInfo[otherid][PEDAIssuer], BlackListInfo[otherid][PEDAIssuerRank], BlackListInfo[otherid][PEDAReason], BlackListInfo[otherid][PEDADur], AccountData[otherid][pID]);
            mysql_tquery(g_SQL, query);
        }
    }
    return 1;
}

forward LoadBlacklistInfo(playerid);
public LoadBlacklistInfo(playerid)
{
    new rows = cache_num_rows();
    new Cache:Blcache;
    if(rows)
    {
        Blcache = cache_save();

        forex(i, rows)
        {
            cache_get_value_name(i, "PoliceIssuer", BlackListInfo[playerid][PDIssuer]);
            cache_get_value_name(i, "PoliceIssuerRank", BlackListInfo[playerid][PDIssuerRank]);
            cache_get_value_name(i, "PoliceReason", BlackListInfo[playerid][PDReason]);
            cache_get_value_name_int(i, "PoliceDuration", BlackListInfo[playerid][PDDur]);
            
            cache_get_value_name(i, "PemerintahIssuer", BlackListInfo[playerid][PEMERIssuer]);
            cache_get_value_name(i, "PemerintahIssuerRank", BlackListInfo[playerid][PEMERIssuerRank]);
            cache_get_value_name(i, "PemerintahReason", BlackListInfo[playerid][PEMERReason]);
            cache_get_value_name_int(i, "PemerintahDuration", BlackListInfo[playerid][PEMERDur]);
            
            cache_get_value_name(i, "EMSIssuer", BlackListInfo[playerid][EMSIssuer]);
            cache_get_value_name(i, "EMSIssuerRank", BlackListInfo[playerid][EMSIssuerRank]);
            cache_get_value_name(i, "EMSReason", BlackListInfo[playerid][EMSReason]);
            cache_get_value_name_int(i, "EMSDuration", BlackListInfo[playerid][EMSDur]);
            
            cache_get_value_name(i, "BengkelIssuer", BlackListInfo[playerid][BENGKELIssuer]);
            cache_get_value_name(i, "BengkelIssuerRank", BlackListInfo[playerid][BENGKELIssuerRank]);
            cache_get_value_name(i, "BengkelReason", BlackListInfo[playerid][BENGKELReason]);
            cache_get_value_name_int(i, "BengkelDuration", BlackListInfo[playerid][BENGKELDur]);
            
            cache_get_value_name(i, "PedagangIssuer", BlackListInfo[playerid][PEDAIssuer]);
            cache_get_value_name(i, "PedagangIssuerRank", BlackListInfo[playerid][PEDAIssuerRank]);
            cache_get_value_name(i, "PedagangReason", BlackListInfo[playerid][PEDAReason]);
            cache_get_value_name_int(i, "PedagangDuration", BlackListInfo[playerid][PEDADur]);
        }

        if(cache_is_valid(Blcache))
        {
            cache_delete(Blcache);
            printf("[Dynamic Blacklist]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Blacklist]: Cache tidak valid atau sudah dihapus.");
        }
    }
    return 1;
}

ShowDurringBlacklist(playerid, targetid)
{
    new 
        strgbg[2500],
        status1[128],
        status2[128],
        status3[128],
        status4[128],
        status5[128];
    
    if(BlackListInfo[targetid][PDDur] != 0) {
        status1 = ""ORANGE"Blacklist";
    } else {
        status1 = ""DARKRED"Tidak";
    }
    if(BlackListInfo[targetid][PEMERDur] != 0) {
        status2 = ""ORANGE"Blacklist";
    } else {
        status2 = ""DARKRED"Tidak";
    } 
    if(BlackListInfo[targetid][EMSDur] != 0) {
        status3 = ""ORANGE"Blacklist";
    } else {
        status3 = ""DARKRED"Tidak";
    } 
    if(BlackListInfo[targetid][BENGKELDur] != 0) {
        status4 = ""ORANGE"Blacklist";
    } else {
        status4 = ""DARKRED"Tidak";
    } 
    if(BlackListInfo[targetid][PEDADur] != 0) {
        status5 = ""ORANGE"Blacklist";
    } else {
        status5 = ""DARKRED"Tidak";
    } 
    
    format(strgbg, sizeof(strgbg), ""GRAY"Daftar Blacklist Dari "YELLOW"%s.\
    \n\n"GRAY"- [Kepolisian Daerah District ] -\
    \nStatus: "YELLOW"%s\
    \n"GRAY"Petugas: %s\
    \nAlasan: %s\
    \n\n- [Pemerintah Daerah District ] -\
    \nStatus: "YELLOW"%s\
    \n"GRAY"Petugas: %s\
    \nAlasan: %s\
    \n\n- [EMS Kota District ] -\
    \nStatus: "YELLOW"%s\
    \n"GRAY"Petugas: %s\
    \nAlasan: %s\
    \n\n- [Bengkel Kota District ]-\
    \nStatus: "YELLOW"%s\
    \n"GRAY"Petugas: %s\
    \nAlasan: %s\
    \n\n- [Pedagang Kota District ] -\
    \nStatus: "YELLOW"%s\
    \n"GRAY"Petugas: %s\
    \nAlasan: %s", 
    ReturnName(targetid),
    status1,
    BlackListInfo[targetid][PDIssuer],
    BlackListInfo[targetid][PDReason],
    status2,
    BlackListInfo[targetid][PEMERIssuer],
    BlackListInfo[targetid][PEMERReason],
    status3,
    BlackListInfo[targetid][EMSIssuer],
    BlackListInfo[targetid][EMSReason],
    status4,
    BlackListInfo[targetid][BENGKELIssuer],
    BlackListInfo[targetid][BENGKELReason],
    status5,
    BlackListInfo[targetid][PEDAIssuer],
    BlackListInfo[targetid][PEDAReason]);
    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Cek Blacklist", strgbg, "Tutup", "");
    return 1;
}

/*ptask BlacklistDelay[1000](playerid)
{
    if(!AccountData[playerid][IsLoggedIn] && !AccountData[playerid][pSpawned]) return false;
    if(BlackListInfo[playerid][PDDur] != 0 && BlackListInfo[playerid][PDDur] <= gettime())
    {
        format(BlackListInfo[playerid][PDIssuer], 64, "");
        format(BlackListInfo[playerid][PDIssuerRank], 64, "");
        format(BlackListInfo[playerid][PDReason], 64, "");
        BlackListInfo[playerid][PDDur] = 0;
        SendClientMessageEx(playerid, -1, ""DARKRED"BLACKLIST:"WHITE" Nama anda sudah terhapus dari list blacklist Kepolisian!");

        new query[512];
        mysql_format(g_SQL, query, sizeof(query), "UPDATE `blacklist_players` SET `PoliceIssuer`='', `PoliceIssuerRank`='', `PoliceReason`='', `PoliceDuration`=0 WHERE `PID`=%d", AccountData[playerid][pID]);
        mysql_tquery(g_SQL, query);
    }
    if(BlackListInfo[playerid][PEMERDur] != 0 && BlackListInfo[playerid][PEMERDur] <= gettime())
    {
        format(BlackListInfo[playerid][PEMERIssuer], 64, "");
        format(BlackListInfo[playerid][PEMERIssuerRank], 64, "");
        format(BlackListInfo[playerid][PEMERReason], 64, "");
        BlackListInfo[playerid][PEMERDur] = 0;
        SendClientMessageEx(playerid, -1, ""DARKRED"BLACKLIST:"WHITE" Nama anda sudah terhapus dari list blacklist Pemerintahan!");

        new query[512];
        mysql_format(g_SQL, query, sizeof(query), "UPDATE `blacklist_players` SET `PemerintahIssuer`='', `PemerintahIssuerrank`='', `PemerintahReason`='', `PemerintahDuration`=0 WHERE `PID`=%d", AccountData[playerid][pID]);
        mysql_tquery(g_SQL, query);
    }
    if(BlackListInfo[playerid][EMSDur] != 0 && BlackListInfo[playerid][EMSDur] <= gettime())
    {
        format(BlackListInfo[playerid][EMSIssuer], 64, "");
        format(BlackListInfo[playerid][EMSIssuerRank], 64, "");
        format(BlackListInfo[playerid][EMSReason], 64, "");
        BlackListInfo[playerid][EMSDur] = 0;
        SendClientMessageEx(playerid, -1, ""DARKRED"BLACKLIST:"WHITE" Nama anda sudah terhapus dari list blacklist EMS!");

        new query[512];
        mysql_format(g_SQL, query, sizeof(query), "UPDATE `blacklist_players` SET `EMSIssuer`='', `EMSIssuerrank`='', `EMSReason`='', `EMSDuration`=0 WHERE `PID`=%d", AccountData[playerid][pID]);
        mysql_tquery(g_SQL, query);
    }
    if(BlackListInfo[playerid][BENGKELDur] != 0 && BlackListInfo[playerid][BENGKELDur] <= gettime())
    {
        format(BlackListInfo[playerid][BENGKELIssuer], 64, "");
        format(BlackListInfo[playerid][BENGKELIssuerRank], 64, "");
        format(BlackListInfo[playerid][BENGKELReason], 64, "");
        BlackListInfo[playerid][BENGKELDur] = 0;
        SendClientMessageEx(playerid, -1, ""DARKRED"BLACKLIST:"WHITE" Nama anda sudah terhapus dari list blacklist Bengkel!");

        new query[512];
        mysql_format(g_SQL, query, sizeof(query), "UPDATE `blacklist_players` SET `BengkelIssuer`='', `BengkelIssuerrank`='', `BengkelReason`='', `BengkelDuration`=0 WHERE `PID`=%d", AccountData[playerid][pID]);
        mysql_tquery(g_SQL, query);
    }
    if(BlackListInfo[playerid][PEDADur] != 0 && BlackListInfo[playerid][PEDADur] <= gettime())
    {
        format(BlackListInfo[playerid][PEDAIssuer], 64, "");
        format(BlackListInfo[playerid][PEDAIssuerRank], 64, "");
        format(BlackListInfo[playerid][PEDAReason], 64, "");
        BlackListInfo[playerid][PEDADur] = 0;
        SendClientMessageEx(playerid, -1, ""DARKRED"BLACKLIST:"WHITE" Nama anda sudah terhapus dari list blacklist Pedagang!");

        new query[512];
        mysql_format(g_SQL, query, sizeof(query), "UPDATE `blacklist_players` SET `PedagangIssuer`='', `PedagangIssuerrank`='', `PedagangReason`='', `PedagangDuration`=0 WHERE `PID`=%d", AccountData[playerid][pID]);
        mysql_tquery(g_SQL, query);
    }
    return 1;
}*/
