#include <YSI\y_hooks>

new const BengkelRank[7][] = {
    "N/A",
    "Magang",
    "Junior",
    "Senior",
    "Manager Bengkel",
    "Wakil Bengkel",
    "Kepala Bengkel"
};

/*enum E_WORKSHOP
{
    wID,
    wName[24],
    wOwner[MAX_PLAYER_NAME + 1],
    wComp,
    wMoney,
    Text3D:wText,
    wPickup,
    Float:wX,
    Float:wY,
    Float:wZ,
    wStatus
};
new wsData[MAX_WORKSHOP][E_WORKSHOP],
    wsEmploy[MAX_WORKSHOP][4][MAX_PLAYER_NAME + 1],
    Iterator:Workshop<MAX_WORKSHOP>;*/

enum e_bengkelstuff
{
    STREAMER_TAG_AREA:BengkelDuty,
    STREAMER_TAG_AREA:BengkelDesk,
    STREAMER_TAG_AREA:BengkelLocker,
    STREAMER_TAG_AREA:BengkelModif[6],
    STREAMER_TAG_AREA:BengkelGarage,
    STREAMER_TAG_AREA:BengkelBrankas,
    STREAMER_TAG_AREA:BengkelCraft,

    Float:bengkelgaragePos[3],
    Float:bengkelgarageSpawnPos[4],
}
new Bengkel_Stuff[e_bengkelstuff];
new Bengkel_Object[MAX_PLAYERS][6];

new pTimerCreateKit[MAX_PLAYERS] = {-1, ...};

// ---------- COMMAND -------------


//-------------------
IsAModifArea(playerid)
{
    if(IsPlayerConnected(playerid))
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 2860.5645,-1856.4572,11.2466) ||
        IsPlayerInRangeOfPoint(playerid, 3.0, 2860.9443,-1848.3844,11.2466) ||
        IsPlayerInRangeOfPoint(playerid, 3.0, 2861.5933,-1840.8214,11.2466) ||
        IsPlayerInRangeOfPoint(playerid, 3.0, 2862.2117,-1832.5049,11.2466) ||
        IsPlayerInRangeOfPoint(playerid, 3.0, 2862.7129,-1824.0803,11.2466))
        {
            return 1;
        }
        /*foreach(new i : Workshop)
        {
            if(IsPlayerInRangeOfPoint(playerid, 45.0, wsData[i][wX], wsData[i][wY], wsData[i][wZ])) 
            {
                if(IsWorkshopOwner(playerid, i))
                    return 1;
            }
        }*/
    }

    return 0;
}

VarsGerbangBengkel()
{
    // Pickup Modif
    new string[512];
    format(string, sizeof(string), ""YELLOW"/modif"WHITE_E" Modifikasi Kendaraan");
    CreateDynamic3DTextLabel(string, -1, 2860.5645,-1856.4572,11.2466 + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1);
    CreateDynamic3DTextLabel(string, -1, 2860.9443,-1848.3844,11.2466 + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1);
    CreateDynamic3DTextLabel(string, -1, 2861.5933,-1840.8214,11.2466 + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1);
    CreateDynamic3DTextLabel(string, -1, 2862.2117,-1832.5049,11.2466 + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1);
    CreateDynamic3DTextLabel(string, -1, 2862.7129,-1824.0803,11.2466 + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1);
    CreateDynamicPickup(1239, 23, 2860.5645,-1856.4572,11.2466 + 0.1, -1, -1, -1, 10.0);
    CreateDynamicPickup(1239, 23, 2860.9443,-1848.3844,11.2466 + 0.1, -1, -1, -1, 10.0);
    CreateDynamicPickup(1239, 23, 2861.5933,-1840.8214,11.2466 + 0.1, -1, -1, -1, 10.0);
    CreateDynamicPickup(1239, 23, 2862.2117,-1832.5049,11.2466 + 0.1, -1, -1, -1, 10.0);
    CreateDynamicPickup(1239, 23, 2862.7129,-1824.0803,11.2466 + 0.1, -1, -1, -1, 10.0);

    Bengkel_Stuff[BengkelDuty] = CreateDynamicSphere(2859.3032,-1875.5648,11.1319, 1.5, -1, -1, -1);
    Bengkel_Stuff[BengkelDesk] = CreateDynamicSphere(2856.9292,-1872.4506,11.1274, 1.5, -1, -1, -1);
    Bengkel_Stuff[BengkelLocker] = CreateDynamicSphere(2863.5364,-1876.0488,11.1394, 1.5, -1, -1, -1);
    Bengkel_Stuff[BengkelGarage] = CreateDynamicSphere(-84.8240, 1043.5159, 19.7411, 1.5, -1, -1, -1);
    Bengkel_Stuff[BengkelBrankas] = CreateDynamicSphere(2862.0681,-1873.4342,11.1365, 1.5, -1, -1, -1);
    Bengkel_Stuff[BengkelCraft] = CreateDynamicSphere(2861.9329,-1868.8961,11.1357, 1.5, -1, -1, -1);
    
    Bengkel_Stuff[BengkelModif][0] = CreateDynamicSphere(2860.5645,-1856.4572,11.2466, 2.5, -1, -1, -1);
    Bengkel_Stuff[BengkelModif][1] = CreateDynamicSphere(2860.9443,-1848.3844,11.2466, 2.5, -1, -1, -1);
    Bengkel_Stuff[BengkelModif][2] = CreateDynamicSphere(2861.5933,-1840.8214,11.2466, 2.5, -1, -1, -1);
    Bengkel_Stuff[BengkelModif][3] = CreateDynamicSphere(2862.2117,-1832.5049,11.2466, 2.5, -1, -1, -1);
    Bengkel_Stuff[BengkelModif][4] = CreateDynamicSphere(2862.7129,-1824.0803,11.2466, 2.5, -1, -1, -1);

}

hook OnPlayerConnect(playerid)
{
    pTimerCreateKit[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pTimerCreateKit[playerid]);
    pTimerCreateKit[playerid] = -1;
    return 1;
}

hook OnGameModeInit()
{
    VarsGerbangBengkel();
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pFaction] == FACTION_BENGKEL)
    {
        if(areaid == Bengkel_Stuff[BengkelLocker] && AccountData[playerid][pDutyBengkel])
        {
            ShowKey(playerid, "[Y] Locker Bengkel");
        }

        if(areaid == Bengkel_Stuff[BengkelDuty])
        {
            if(!AccountData[playerid][pDutyBengkel])
            {
                ShowKey(playerid, "[Y] ~g~On Duty");
            }
            else
            {
                ShowKey(playerid, "[Y] ~r~Off Duty");
            }
        }
        if(areaid == Bengkel_Stuff[BengkelDesk] && AccountData[playerid][pDutyBengkel])
        {
            ShowKey(playerid, "[Y] Bengkel Desk");
        }

        if(areaid == Bengkel_Stuff[BengkelBrankas] && AccountData[playerid][pDutyBengkel])
        {
            ShowKey(playerid, "[Y] Brankas Bengkel");
        }

        if(areaid == Bengkel_Stuff[BengkelCraft] && AccountData[playerid][pDutyBengkel])
        {
            ShowKey(playerid, "[Y] Crafting Bengkel");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == Bengkel_Stuff[BengkelLocker])
    {
        HideShortKey(playerid);
    }

    if(areaid == Bengkel_Stuff[BengkelDuty])
    {
        HideShortKey(playerid);
    }

    if(areaid == Bengkel_Stuff[BengkelGarage])
    {
        HideShortKey(playerid);
    }

    if(areaid == Bengkel_Stuff[BengkelDesk])
    {
        HideShortKey(playerid);
    }

    if(areaid == Bengkel_Stuff[BengkelBrankas])
    {
        HideShortKey(playerid);
    }

    if(areaid == Bengkel_Stuff[BengkelCraft])
    {
        HideShortKey(playerid);
    }
    return 1;
}
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pFaction] == FACTION_BENGKEL)
        {
            if(IsPlayerInDynamicArea(playerid, Bengkel_Stuff[BengkelDuty]))
            {
                if(!AccountData[playerid][pDutyBengkel])
                {
                    AccountData[playerid][pDutyBengkel] = true;
                    SetFactionColor(playerid);
                    AccountData[playerid][pDutyTimer] = SetTimerEx("FactDutyHour", 1000, true, "i", playerid);
                    ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~g~On Duty~w~ Bengkel");
                }
                else 
                {
                    AccountData[playerid][pDutyBengkel] = false;
                    SetPlayerColor(playerid, COLOR_WHITE);
                    ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~r~Off Duty~w~ Bengkel");
                }
                RefreshFactionMap(playerid);
            }

            if(IsPlayerInDynamicArea(playerid, Bengkel_Stuff[BengkelLocker]) && AccountData[playerid][pDutyBengkel])
            {
                ShowPlayerDialog(playerid, DIALOG_BENGKEL_LOCKER, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Locker Bengkel",
                "Baju Biasa\
                \n"GRAY"Baju Kerja", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, Bengkel_Stuff[BengkelCraft]) && AccountData[playerid][pDutyBengkel])
            {
                if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Manager Bengkel untuk dapat Craft!");
                
                ShowPlayerDialog(playerid, DIALOG_BENGKEL_BRANKASITEM, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Barang Bengkel",
                "Nama Item\tKeterangan\
                \nRepair Kits\tUntuk memperbaiki mesin kendaraan dan juga body\
                \n"GRAY"Tools Kit\t"GRAY"Untuk memperbaiki mesin kendaraan tidak dengan body", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, Bengkel_Stuff[BengkelBrankas]) && AccountData[playerid][pDutyBengkel])
            {
                if(AccountData[playerid][pFactionRank] < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Senior Keatas untuk akses desk!");
                if(NearPlayerOpenStorage(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain disekitar sedang membuka brankas!");

                AccountData[playerid][menuShowed] = true;
                ShowPlayerDialog(playerid, DIALOG_BENGVAULT, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Brankas Bengkel",
                "Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, Bengkel_Stuff[BengkelDesk]))
            {
                if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Bengkel untuk akses desk!");
                ShowPlayerDialog(playerid, DIALOG_BENGKEL_BOSDESK, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Bos Desk",
                "Invite\
                \n"GRAY"Kelola Jabatan\
                \nKick\
                \n"GRAY"Lihat Anggota\
                \nSaldo Finansial\
                \n"GRAY"Deposit Saldo\
                \nTarik Saldo", "Pilih", "Batal");
            }

            /*if(IsPlayerInRangeOfPoint(playerid, 2.0, Bengkel_Stuff[bengkelgaragePos][0], Bengkel_Stuff[bengkelgaragePos][1], Bengkel_Stuff[bengkelgaragePos][2]) && AccountData[playerid][pDutyBengkel])
            {
                ShowPlayerDialog(playerid, DIALOG_BENGKEL_GARAGE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Garasi Bengkel",
                "Keluarkan Kendaraan\
                \n"GRAY"Simpan Kendaraan\
                \nBeli Kendaraan\
                \n"GRAY"Hapus Kendaraan", "Pilih", "Batal");
            }*/
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    static icsr[255];
    switch(dialogid)
    {
        case DIALOG_BENGKEL_BOSDESK:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bengkel District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            switch(listitem)
            {
                case 0: //invite
                {
                    new frmxt[522], count = 0;

                    foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 1.5))
                    {
                        format(frmxt, sizeof(frmxt), "%sPlayer ID: %d\n", frmxt, i);
                        NearestPlayer[playerid][count++] = i;
                    }

                    if(count == 0)
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Invite",
                        "Tidak ada orang disekitar anda!", "Tutup", "");
                    }

                    ShowPlayerDialog(playerid, DIALOG_BENGKEL_INVITE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Invite", frmxt, "Pilih", "Batal");

                }
                case 1:// Kelola Jabatan
                {
                    new Cache:execute;
                    execute = mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 5 ORDER BY Char_FactionRank DESC");

                    new rows = cache_num_rows();
                    if(rows)
                    {
                        new fckname[64], fckrank, fcklastlogin[30], shstr[2048];

                        format(shstr, sizeof(shstr), "Nama\tRank\tLast Online\n");
                        for(new i; i < rows; ++i)
                        {
                            cache_get_value_name(i, "Char_Name", fckname);
                            cache_get_value_name_int(i, "Char_FactionRank", fckrank);
                            cache_get_value_name(i, "Char_LastLogin", fcklastlogin);

                            format(shstr, sizeof(shstr), "%s%s\t%s\t%s\n", shstr, fckname, BengkelRank[fckrank], fcklastlogin);
                        }
                        ShowPlayerDialog(playerid, DIALOG_BENGKELSETRANK, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Set Jabatan", shstr, "Pilih", "Batal");
                    }
                    else 
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Set Jabatan", "Tidak ada Anggota Bengkel!", "Tutup", "");
                    }
                    cache_delete(execute);
                }
                case 2:// Kick Offline / Online
                {
                    new Cache:execute;
                    execute = mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 5 ORDER BY Char_FactionRank DESC");

                    new rows = cache_num_rows();
                    if(rows)
                    {
                        new fckname[64], fckrank, fcklastlogin[30], shstr[2048];

                        format(shstr, sizeof(shstr), "Nama\tRank\tLast Online\n");
                        for(new i; i < rows; ++i)
                        {
                            cache_get_value_name(i, "Char_Name", fckname);
                            cache_get_value_name_int(i, "Char_FactionRank", fckrank);
                            cache_get_value_name(i, "Char_LastLogin", fcklastlogin);

                            format(shstr, sizeof(shstr), "%s%s\t%s\t%s\n", shstr, fckname, BengkelRank[fckrank], fcklastlogin);
                        }
                        ShowPlayerDialog(playerid, DIALOG_BENGKELKICKMEMBER, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Kick Anggota", shstr, "Kick", "Batal");
                    }
                    else 
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota", "Tidak ada Anggota Bengkel!", "Tutup", "");
                    }
                    cache_delete(execute);
                }
                case 3:// Anggota Online
                {
                    new duty[128], lstr[1024];
                    format(lstr, sizeof lstr, "Nama\tRank\tStatus Duty\n");
                    foreach(new i : Player) {
                        if(AccountData[i][pFaction] == FACTION_BENGKEL) {
                            switch(AccountData[i][pDutyBengkel])
                            {
                                case 0:
                                {
                                    duty = ""RED_E"Off Duty";
                                }
                                case 1:
                                {
                                    duty = ""GREEN"On Duty";
                                }
                            }
                            format(lstr, sizeof lstr, "%s%s(%d)\t%s\t%s", lstr, GetRPName(i), i, GetFactionRank(i), duty);
                            format(lstr, sizeof lstr, "%s\n", lstr);
                        }
                    }
                    format(lstr, sizeof lstr, "%s\n", lstr);
                    Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Anggota", lstr, "Close", "");
                }
                case 4:// Saldo Finansial
                {
                    new frmxt[158];
                    format(frmxt, sizeof(frmxt), "Perusahaan Bengkel District  saat ini memiliki saldo sebesar:\
                    \n"DARKGREEN"%s", FormatMoney(BengkelMoneyVault));
                    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Bengkel Money", frmxt, "Tutup", "");
                }
                case 5:// Deposit Saldo
                {
                    ShowPlayerDialog(playerid, DIALOG_DEPOSIT_BENGKEL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Bengkel Deposit",
                    "Mohon masukkan nominal deposit untuk saldo perusahaan:", "Input", "Batal");
                }
                case 6:// Withdraw Saldo
                {
                    ShowPlayerDialog(playerid, DIALOG_WITHDRAW_BENGKEL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Bengkel Withdraw",
                    "Mohon masukkan nominal penarikan tunai dari saldo perusahaan:", "Input", "Batal");
                }
            }
        }
        case DIALOG_DEPOSIT_BENGKEL:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Bengkel!");
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Bengkel untuk akses desk!");
            new depocash = strval(inputtext), frmtmny[128];
            if(depocash > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak sebanyak itu!");
            if(depocash < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal kurang dari $1 untuk deposit!");
            TakeMoney(playerid, depocash);
            BengkelMoneyVault += depocash;
            mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `bengkelmoneyvault` = %d WHERE `ID` = 0", BengkelMoneyVault);
            mysql_tquery(g_SQL, frmtmny);
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil deposit %s untuk Bengkel District ", FormatMoney(depocash)));
        }
        case DIALOG_WITHDRAW_BENGKEL:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Bengkel!");
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Bengkel untuk akses desk!");
            new withdrawcash = strval(inputtext), frmtmny[128];
            if(withdrawcash > BengkelMoneyVault) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang perusahaan tidak sebanyak itu!");
            if(withdrawcash < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal kurang dari $1 untuk withdraw!");
            BengkelMoneyVault -= withdrawcash;
            GiveMoney(playerid, withdrawcash);

            mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `bengkelmoneyvault` = %d WHERE `ID` = 0", BengkelMoneyVault);
            mysql_tquery(g_SQL, frmtmny);

            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], withdrawcash, "Bengkel");

            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil withdraw %s dari Bengkel District ", FormatMoney(withdrawcash)));
        }
        case DIALOG_BENGVAULT: 
        {
            if(!response) 
            {
                AccountData[playerid][menuShowed] = false;
                return 1;
            }
            
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) 
            {
                AccountData[playerid][menuShowed] = false;   
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Bengkel!");
            }
            switch(listitem)
            {
                case 0: //deposit
                {
                    FactionBrankas[playerid][factionBrankasID] = 0;
                    FactionBrankas[playerid][factionBrankasTemp] = EOS;
                    FactionBrankas[playerid][factionBrankasModel] = 0;
                    FactionBrankas[playerid][factionBrankasQuant] = 0;

                    new str[1218], amounts, itemname[64], tss[125], Cache:execute;
                    format(str, sizeof(str), "Nama Item\tJumlah\tBerat (-/-)\n");
                    mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
                    execute = mysql_query(g_SQL, tss, true);
                    new rows = cache_num_rows();
                    if(rows) 
                    {
                        for(new x; x < rows; ++x)
                        {
                            cache_get_value_name(x, "invItem", itemname);
                            cache_get_value_name_int(x, "invQuantity", amounts);

                            format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                        }
                        ShowPlayerDialog(playerid, DIALOG_BENGVAULT_DEPOSIT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas Bengkel", str, "Pilih", "Batal");
                    }
                    else 
                    {
                        AccountData[playerid][menuShowed] = false;
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas Bengkel",
                        "Anda tidak memiliki barang untuk disimpan!", "Tutup", "");
                    }
                    cache_delete(execute);
                }
                case 1: //withdraw
                {
                    new str[4036], amounts, itemname[64], Cache:execute;
                    format(str, sizeof(str), "Nama Item\tJumlah\tBerat (-/-)\n");
                    execute = mysql_query(g_SQL, "SELECT * FROM `bengkel_brankas` WHERE `PID`=0");
                    if(cache_num_rows() > 0)
                    {
                        for(new x; x < cache_num_rows(); ++x)
                        {
                            cache_get_value_name(x, "Item", itemname);
                            cache_get_value_name_int(x, "Quantity", amounts);

                            format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                        }
                        ShowPlayerDialog(playerid, DIALOG_BENGVAULT_WITHDRAW, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas Bengkel", str, "Pilih", "Batal");
                    }
                    else 
                    {
                        AccountData[playerid][menuShowed] = false;
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas Bengkel",
                        "Tidak ada barang di brankas saat ini!", "Tutup", "");
                    }
                    cache_delete(execute);
                }
            }
        }
        case DIALOG_BENGVAULT_DEPOSIT:
        {
            if(!response)
            {
                BrankasLastUse[playerid] = 0;
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            }

            if(listitem == -1)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item!");
            }

            new tss[128], Cache:execute;
            mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
            execute = mysql_query(g_SQL, tss, true);
            if(cache_num_rows() > 0)
            {
                cache_get_value_name(listitem, "invItem", FactionBrankas[playerid][factionBrankasTemp]);
                cache_get_value_name_int(listitem, "invModel", FactionBrankas[playerid][factionBrankasModel]);
                cache_get_value_name_int(listitem, "invQuantity", FactionBrankas[playerid][factionBrankasQuant]);

                new shstr[528];
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_BENGVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Bengkel",
                shstr, "Input", "Batal");
            }
            cache_delete(execute);
        }
        case DIALOG_BENGVAULT_IN:
        {
            if(GetTickCount() - BrankasLastUse[playerid] < 2000)
            {
                AccountData[playerid][menuShowed] = false;
                ShowTDN(playerid, NOTIFICATION_ERROR, "mohon tunggu sebentar!");
                return 1;
            }
            BrankasLastUse[playerid] = GetTickCount();

            if(!response)
            {
                BrankasLastUse[playerid] = 0;
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            }

            new shstr[512];
            if(isnull(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nTidak dapat diisi kosong!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_BENGVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Bengkel",
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_BENGVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Bengkel",
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[playerid][factionBrankasQuant])
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_BENGVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Bengkel",
                shstr, "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);
            Inventory_Remove(playerid, FactionBrankas[playerid][factionBrankasTemp], quantity);
            ShowItemBox(playerid, sprintf("Removed %dx", quantity), FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel]);

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "BENGKEL - Memasukkan %s sejumlah %d ke dalam brankas", FactionBrankas[playerid][factionBrankasTemp], quantity);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], quantity, frmtx);

            new invstr[1028];
            mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `bengkel_brankas` WHERE `PID`=0 AND `Item` = '%s'", FactionBrankas[playerid][factionBrankasTemp]);
            mysql_query(g_SQL, shstr);
            new rows = cache_num_rows();
            if(rows > 0)
            {
                mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `bengkel_brankas` SET `Quantity` = `Quantity` + %d WHERE `PID` = 0 AND `Item`='%s'", quantity, FactionBrankas[playerid][factionBrankasTemp]);
                mysql_tquery(g_SQL, invstr, "OnBengkelDeposit", "i", playerid);
            }
            else 
            {
                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `bengkel_brankas` SET `PID`=0, `Item`='%s', `Model`=%d, `Quantity`=%d", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel], quantity);
                mysql_tquery(g_SQL, invstr, "OnBengkelDeposit", "i", playerid);
            }
            AccountData[playerid][menuShowed] = false;
        }
        case DIALOG_BENGVAULT_WITHDRAW:
        {
            if(!response)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            }

            if(listitem == -1)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item!");
            }

            new shstr[1218], Cache:execute;
            execute = mysql_query(g_SQL, "SELECT * FROM `bengkel_brankas` WHERE `PID`=0");
            if(cache_num_rows() > 0)
            {
                cache_get_value_name_int(listitem, "ID", FactionBrankas[playerid][factionBrankasID]);
                cache_get_value_name(listitem, "Item", FactionBrankas[playerid][factionBrankasTemp]);
                cache_get_value_name_int(listitem, "Model", FactionBrankas[playerid][factionBrankasModel]);
                cache_get_value_name_int(listitem, "Quantity", FactionBrankas[playerid][factionBrankasQuant]);

                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_BENGVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Bengkel",
                shstr, "Input", "Batal");
            }
            else 
            {
                AccountData[playerid][menuShowed] = false;
                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas Bengkel",
                "Brankas ini isinya kosong!", "Tutup", "");
            }
            cache_delete(execute);
        }
        case DIALOG_BENGVAULT_OUT:
        {
            if(!response)
            {
                AccountData[playerid][menuShowed] = false;
                return 1;
            }

            new shstr[512];
            if(isnull(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nTidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_BENGVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Bengkel",
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_BENGVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Bengkel",
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[playerid][factionBrankasQuant])
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_BENGVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Bengkel",
                shstr, "Input", "Batal");
                return 1;
            }
            new quantity = strval(inputtext), jts[150];

            if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!"), AccountData[playerid][menuShowed] = false;

            FactionBrankas[playerid][factionBrankasQuant] -= quantity;
            if(FactionBrankas[playerid][factionBrankasQuant] > 0)
            {
                mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `bengkel_brankas` SET `Quantity`=%d WHERE `ID`=%d", FactionBrankas[playerid][factionBrankasQuant], FactionBrankas[playerid][factionBrankasID]);
                mysql_tquery(g_SQL, jts);
            }
            else 
            {
                mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `bengkel_brankas` WHERE `ID`=%d", FactionBrankas[playerid][factionBrankasID]);
                mysql_tquery(g_SQL, jts);
            }
            Inventory_Add(playerid, FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel], quantity);
            ShowItemBox(playerid, sprintf("Received %dx", quantity), FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel]);

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "BENGKEL - Mengambil %s sejumlah %d dari dalam brankas", FactionBrankas[playerid][factionBrankasTemp], quantity);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], quantity, frmtx);

            FactionBrankas[playerid][factionBrankasID] = 0;
            FactionBrankas[playerid][factionBrankasTemp] = EOS;
            FactionBrankas[playerid][factionBrankasModel] = 0;
            FactionBrankas[playerid][factionBrankasQuant] = 0;
            AccountData[playerid][menuShowed] = false;
        }
        case DIALOG_BENGKELKICKMEMBER:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Bengkel District !");
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Manager Bengkel untuk mengakses Bos Desk!");

            new Cache:execute = mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 5 ORDER BY `Char_FactionRank` DESC", true);
            if(cache_num_rows())
            {
                new pidrow, fckname[64], fckrank, fcklastlogin[30], kckstr[225];

                cache_get_value_name_int(listitem, "pID", pidrow);
                cache_get_value_name(listitem, "Char_Name", fckname);
                cache_get_value_name_int(listitem, "Char_FactionRank", fckrank);
                cache_get_value_name(listitem, "Char_LastLogin", fcklastlogin);

                if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat kick diri sendiri!");
                if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat kick pangkat diatasmu!");

                /* kendaraan pribadi yg milik faction di cek*/
                new strgbg[158];
                mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_OwnerID`=%d AND `PVeh_Faction` = 5", pidrow);
                mysql_tquery(g_SQL, strgbg);

                foreach(new i : Player)
                {
                    if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && pidrow == AccountData[i][pID])
                    {
                        AccountData[i][pFaction] = 0;
                        AccountData[i][pFactionRank] = 0;

                        //jika kendaraan pribadi ada di server dan player sedang online, maka kendaraan fisik dihapus
                        foreach(new pvid : PvtVehicles)
                        {
                            if(PlayerVehicle[pvid][pVehExists] && PlayerVehicle[pvid][pVehOwnerID] == AccountData[i][pID])
                            {
                                if(PlayerVehicle[pvid][pVehFaction] == FACTION_BENGKEL)
                                {
                                    PlayerVehicle[pvid][pVehExists] = false;

                                    if(IsValidVehicle(PlayerVehicle[pvid][pVehPhysic]))
                                    {
                                        DisableVehicleSpeedCap(PlayerVehicle[pvid][pVehPhysic]);
                                        SetVehicleNeonLights(PlayerVehicle[pvid][pVehPhysic], false, PlayerVehicle[pvid][pVehNeon], 0);

                                        DestroyVehicle(PlayerVehicle[pvid][pVehPhysic]);
                                        PlayerVehicle[pvid][pVehPhysic] = INVALID_VEHICLE_ID;
                                    }

                                    Iter_Remove(PvtVehicles, pvid);
                                }
                            }
                        }
                        if(AccountData[i][pDutyBengkel])
                            AccountData[i][pDutyBengkel] = false;
                        if(AccountData[i][pUsingUniform])
                            AccountData[i][pUsingUniform] = false;
                        SetPlayerSkin(i, AccountData[i][pSkin]);
                        RefreshFactionMap(i);
                        ShowTDN(i, NOTIFICATION_WARNING, "Anda telah dikeluarkan dari faction Bengkel District !");
                    }
                }
                mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`=0, `Char_FactionRank`=0, `Char_UsingUniform`=0 WHERE `pID`=%d", pidrow);
                mysql_tquery(g_SQL, icsr);
                format(kckstr, sizeof(kckstr), "Anda telah berhasil menendang anggota:\n\
                Nama: %s\n\
                Rank: %s\n\
                Last Online: %s", fckname, BengkelRank[fckrank], fcklastlogin);
                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota",
                kckstr, "Tutup", "");

                AccountData[playerid][pTempSQLFactMemberID] = -1;
                AccountData[playerid][pTempSQLFactRank] = 0;
            }
            cache_delete(execute);
        }
        case DIALOG_BENGKELSETRANK:
        {
            new Cache:execute;
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Bengkel District !");
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Bengkel untuk mengakses Bos Desk!");

            execute = mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 5 ORDER BY `Char_FactionRank` DESC");
            new rows = cache_num_rows();
            if(rows)
            {
                cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
                cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
                if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak dapat mengatur jabatan sendiri!");
                if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengatur jabatan rank diatasmu!");
                ShowPlayerDialog(playerid, DIALOG_RANK_SET_BENGKEL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan",
                "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
                1. Magang\n\
                2. Junior\n\
                3. Senior\n\
                4. Manager Bengkel\n\
                5. Wakil Bengkel\n\
                6. Kepala Bengkel", "Set", "Batal");
            }
            cache_delete(execute);
        }
        case DIALOG_RANK_SET_BENGKEL:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Bengkel District !");
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal Rank Manager Bengkel untuk akses Bos Desk!");

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_BENGKEL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Error: Tidak dapat diisi kosong!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Magang\n\
            2. Junior\n\
            3. Senior\n\
            4. Manager Bengkel\n\
            5. Wakil Bengkel\n\
            6. Kepala Bengkel", "Set", "Batal");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_BENGKEL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Error: Hanya dapat diisi angka!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Magang\n\
            2. Junior\n\
            3. Senior\n\
            4. Manager Bengkel\n\
            5. Wakil Bengkel\n\
            6. Kepala Bengkel", "Set", "Batal");

            if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pFactionRank]) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_BENGKEL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Magang\n\
            2. Junior\n\
            3. Senior\n\
            4. Manager Bengkel\n\
            5. Wakil Bengkel\n\
            6. Kepala Bengkel", "Set", "Batal");

            new affah[128];
            mysql_format(g_SQL, affah, sizeof(affah), "UPDATE `player_characters` SET `Char_FactionRank`=%d WHERE `pID`=%d", strval(inputtext), AccountData[playerid][pTempSQLFactMemberID]);
            mysql_tquery(g_SQL, affah);

            foreach(new i : Player)
            {
                if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && AccountData[playerid][pTempSQLFactMemberID] == AccountData[i][pID])
                {
                    AccountData[i][pFactionRank] = strval(inputtext);
                    ShowTDN(i, NOTIFICATION_INFO, "Jabatan baru anda di faction telah diubah");
                }
            }

            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengubah jabatan faction player tersebut");
        }
        case DIALOG_BENGKEL_INVITE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Bengkel!");
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Manager Bengkel untuk akses bos desk!");

            new targetid = NearestPlayer[playerid][listitem];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            AccountData[targetid][pFaction] = FACTION_BENGKEL;
            AccountData[targetid][pFactionRank] = 1;
            
            RefreshFactionMap(targetid);
            mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`= 5, `Char_FactionRank` = 1 WHERE `pID`=%d", AccountData[targetid][pID]);
            mysql_tquery(g_SQL, icsr);
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil invite faction %s", AccountData[targetid][pName]));
        }
        case DIALOG_BENGKEL_BRANKASITEM:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bengkel District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:// Repair Kits
                {
                    static jskc[512];
                    format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"Repair Kit"WHITE" dengan bahan sebagai berikut:\
                    \n\n"WHITE"Besi: "ORANGE"%d/15\
                    \n"WHITE"Tembaga: "ORANGE"%d/15\
                    \n"WHITE"Petrol: "ORANGE"%d/1\
                    \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ? )", Inventory_Count(playerid, "Besi"), Inventory_Count(playerid, "Tembaga"), Inventory_Count(playerid, "Petrol"));
                    ShowPlayerDialog(playerid, DIALOG_BENGKEL_BRANKASCONF, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Barang Bengkel", jskc, "Iya", "Batal");
                }
                case 1:// Tools
                {
                    static jskc[512];
                    format(jskc, sizeof(jskc), ""WHITE"Anda akan membuat "RED"Tools Kit"WHITE" dengan bahan sebagai berikut:\
                    \n\n"WHITE"Besi: "ORANGE"%d/15\
                    \n"WHITE"Tembaga: "ORANGE"%d/15\
                    \n"WHITE"Pure Oil: "ORANGE"%d/1\
                    \n\n"YELLOW"( Apakah anda yakin ingin membuat barang tersebut ? )", Inventory_Count(playerid, "Besi"), Inventory_Count(playerid, "Tembaga"), Inventory_Count(playerid, "Pure Oil"));
                    ShowPlayerDialog(playerid, DIALOG_BENGKEL_BRANKASCONF, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Barang Bengkel", jskc, "Iya", "Batal");
                }
            }
            AccountData[playerid][pTempValue] = listitem;
        }
        case DIALOG_BENGKEL_BRANKASCONF:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bengkel District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            switch(AccountData[playerid][pTempValue])
            {
                case 0://
                {
                    if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

                    AccountData[playerid][ActivityTime] = 1;
                    pTimerCreateKit[playerid] = SetTimerEx("CreateRepairKit", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMBUAT REPAIR KIT");
                    ShowProgressBar(playerid);

                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
                case 1:// 
                {
                    if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

                    AccountData[playerid][ActivityTime] = 1;
                    pTimerCreateKit[playerid] = SetTimerEx("CreateToolsKit", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMBUAT REPAIR KIT");
                    ShowProgressBar(playerid);

                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
            }
        }
        case DIALOG_BENGKEL_BRANKASREPAIRKIT:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bengkel District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;

            new option[128], amount;
            if(sscanf(inputtext, "s[128]d", option, amount))
            {
                ShowPlayerDialog(playerid, DIALOG_BENGKEL_BRANKASREPAIRKIT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Bengkel", "Mohon ikuti sesuai format berikut:\n[ambil] [jumlah] atau [depo] [jumlah]\nMohon masukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
                return 1;
            }
            if(!strcmp(option, "ambil", true))
            {
                new price = 350;
                new bayar = amount * price;
                if(GetPlayerMoney(playerid) < bayar) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                if(amount > repairkit) return ShowTDN(playerid, NOTIFICATION_ERROR, "Repair Kit Dibrankas tidak sebanyak itu!");
                if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Input");

                repairkit -= amount;
                TakeMoney(playerid, bayar);
                Inventory_Add(playerid, "Repair Kit", 19921, amount);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil Repair Kit!");
                ShowItemBox(playerid, sprintf("ADDED %dx", amount), "REPAIR KIT", 19921);
                BrankasBengkel_Save();
            }
            if(!strcmp(option, "depo", true))
            {
                new price = 350;
                new bayar = amount * price;
                if(amount > Inventory_Count(playerid, "Repair Kit")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Repair Kit Anda tidak sebanyak itu!");
                if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Input");

                repairkit += amount;
                GiveMoney(playerid, bayar);
                Inventory_Remove(playerid, "Repair Kit", amount);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil memasukan Repair Kit!");
                ShowItemBox(playerid, sprintf("REMOVED %dx", amount), "REPAIR KIT", 19921);
                BrankasBengkel_Save();
            }
        }
        case DIALOG_BENGKEL_BRANKASTOOLSKIT:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bengkel District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;

            new option[128], amount;
            if(sscanf(inputtext, "s[128]d", option, amount))
            {
                ShowPlayerDialog(playerid, DIALOG_BENGKEL_BRANKASTOOLSKIT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Bengkel", "Mohon ikuti sesuai format berikut:\n[ambil] [jumlah] atau [depo] [jumlah]\nMohon masukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
                return 1;
            }
            if(!strcmp(option, "ambil", true))
            {
                new price = 200;
                new bayar = amount * price;
                if(GetPlayerMoney(playerid) < bayar) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
                if(amount > toolskit) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tools Kit Dibrankas tidak sebanyak itu!");
                if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Input");

                toolskit -= amount;
                TakeMoney(playerid, bayar);
                Inventory_Add(playerid, "Tools Kit", 19918, amount);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil Tools Kit!");
                ShowItemBox(playerid, sprintf("ADDED %dx", amount), "TOOLS KIT", 19918);
                BrankasBengkel_Save();
            }
            if(!strcmp(option, "depo", true))
            {
                new price = 200;
                new bayar = amount * price;
                if(amount > Inventory_Count(playerid, "Tools Kit")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tools Kit Anda tidak sebanyak itu!");
                if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Input");

                toolskit += amount;
                GiveMoney(playerid, bayar);
                Inventory_Remove(playerid, "Tools Kit", amount);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil memasukan Repair Kit!");
                ShowItemBox(playerid, sprintf("REMOVED %dx", amount), "TOOLS KIT", 19918);
                BrankasBengkel_Save();
            }
        }
        case DIALOG_BENGKEL_PANEL:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bengkel District !");
            new targetid = AccountData[playerid][pTarget];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi kedalam server!");
            if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan player tersebut!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan, tidak dapat menggunakan Panel!");
            switch(listitem)
            {
                case 0:// Kartu Identitas
                {
                    CekIdentitas(playerid, targetid);
                }
                case 1:// Cek Invoice
                {
                    PeriksaInvoice(playerid, targetid);
                }
                case 2:// Give Invoice
                {
                    GivePlayerInvoice(playerid, targetid);
                }
                case 3:// cek blacklist
                {
                    ShowDurringBlacklist(playerid, targetid);
                }
                case 4: // Ikat
                {
                    AccountData[targetid][pCuffed] = 1;
                    SetPlayerSpecialAction(targetid, SPECIAL_ACTION_CUFFED);
                    SendRPMeAboveHead(playerid, "Mengikat orang didepannya menggunakan tali", X11_PLUM1);
                    ShowTDN(targetid, NOTIFICATION_WARNING, "Anda sedang diikat!");
                }
                case 5: // Lepas Ikatan
                {
                    AccountData[targetid][pCuffed] = 0;
                    SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
                    SendRPMeAboveHead(playerid, "Melepaskan ikatan orang didepan", X11_PLUM1);
                    ShowTDN(targetid, NOTIFICATION_WARNING, "Ikatan anda telah dilepaskan!");
                }
            }
        }
        case DIALOG_BENGKEL_GARAGE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bengkel District !");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            
            switch(listitem)
            {
                case 0: //takeout
                {
                    if(CountPlayerFactVehInGarage(playerid, FACTION_BENGKEL) < 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun di garasi ini!");

                    new id, count = CountPlayerFactVehInGarage(playerid, FACTION_BENGKEL), list[596];
                    format(list,sizeof(list),"No\tModel Kendaraan\tNomor Plat\n");
                    for(new itt = 0; itt < count; itt++)
                    {
                        id = GetVehicleIDStoredFactGarage(playerid, itt, FACTION_BENGKEL);
                        if(itt == count)
                        {
                            format(list, sizeof(list), "%s%d\t%s\t%s", list, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                        } else format(list, sizeof(list), "%s%d\t%s\t%s\n", list, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                    }
                    ShowPlayerDialog(playerid, DIALOG_BENGKELTAKEVEH, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Garasi Bengkel", list, "Pilih", "Batal");
                }
                case 1:// simpan kendaraan
                {
                    new carid = -1, bool: foundnearby = false;
                    if((carid = Vehicle_Nearest(playerid, 10.0)) != -1)
                    {
                        if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
                        if(PlayerVehicle[carid][pVehRental] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat disimpan digarasi Faction!");
                        if(PlayerVehicle[carid][pVehFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan kendaraan Bengkel!");
                        Vehicle_GetStatus(carid);
                        PlayerVehicle[carid][pVehFactStored] = FACTION_BENGKEL;

                        foundnearby = true;

                        if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]))
                        {
                            DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
                            SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

                            DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
                            PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
                        }
                    }
                    if(!foundnearby) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan dari Bengkel District  milik anda di sekitar!");
                }
                case 2:// Beli Kendaraan
                {
                    ShowPlayerDialog(playerid, DIALOG_BENGKELBUYVEH, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Beli Kendaraan",
                    "Model\tHarga\
                    \nTow Truck\t$5000\
                    \n"GRAY"Rumpo\t"GRAY"$8000\
                    \nSanchez\t$4000\
                    \n"GRAY"Bloody Banger\t"GRAY"$25000", "Pilih", "Batal");
                }
                case 3:// Hapus Kendaraan
                {
                    new frmtdel[151], Cache:execute;
                    mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 5 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
                    execute = mysql_query(g_SQL, frmtdel, true);

                    new rows = cache_num_rows();
                    if(rows)
                    {
                        new list[255], hapvid, hapmod;

                        format(list, sizeof(list), "Database ID\tModel\n");
                        for(new x; x < rows; ++ x)
                        {
                            cache_get_value_name_int(x, "id", hapvid);
                            cache_get_value_name_int(x, "PVeh_ModelID", hapmod);

                            format(list, sizeof(list), "%s%d\t%s\n", list, hapvid, GetVehicleModelName(hapmod));
                        }
                        ShowPlayerDialog(playerid, DIALOG_BENGKELDELCAR, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Hapus Kendaraan", list, "Hapus", "Batal");
                    }
                    else 
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Kendaraan", "Anda tidak memiliki kendaraan Bengkel!", "Tutup", "");
                    }
                    cache_delete(execute);
                }
            }
        }
        case DIALOG_BENGKELDELCAR:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Bengkel District !");
            
            new frmtdel[159], Cache:execute;
            mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 5 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
            execute = mysql_query(g_SQL, frmtdel, true);
            if(cache_num_rows())
            {
                new hapvid, hapmods, hvprice, kckstr[225], strgbg[128];

                if(listitem >= 0 && listitem < cache_num_rows())
                {
                    cache_get_value_name_int(listitem, "id", hapvid);
                    cache_get_value_name_int(listitem, "PVeh_ModelID", hapmods);
                    cache_get_value_name_int(listitem, "PVeh_Price", hvprice);

                    format(kckstr, sizeof(kckstr), "Anda berhasil menghapus kendaraan:\
                    \nDatabase ID: %d\
                    \nModel: %s", hapvid, GetVehicleModelName(hapmods));
                    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Kendaraan", kckstr, "Tutup", "");

                    new pvid = GetFactionVehicleIDFromListitem(playerid, listitem, FACTION_BENGKEL);

                    PlayerVehicle[pvid][pVehExists] = false;
                    if(IsValidVehicle(PlayerVehicle[pvid][pVehPhysic]))
                    {
                        DisableVehicleSpeedCap(PlayerVehicle[pvid][pVehPhysic]);
                        SetVehicleNeonLights(PlayerVehicle[pvid][pVehPhysic], false, PlayerVehicle[pvid][pVehNeon], 0);

                        DestroyVehicle(PlayerVehicle[pvid][pVehPhysic]);
                        PlayerVehicle[pvid][pVehPhysic] = INVALID_VEHICLE_ID;
                    }
                    GiveMoney(playerid, hvprice);
                    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `id` = %d", hapvid);
                    mysql_tquery(g_SQL, strgbg);

                    Iter_Remove(PvtVehicles, pvid);
                }
            }   
            cache_delete(execute);
        }
        case DIALOG_BENGKELBUYVEH:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota bengkel!");
            
            if(!IsPlayerInDynamicArea(playerid, Bengkel_Stuff[BengkelGarage])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat Garasi Bengkel!");

            // new count = 0;
            // foreach(new i : PvtVehicles)
            // {
            //     if(PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
            //         count ++;
            // }

            // if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");

            switch(listitem)
            {
                case 0: //tow 
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 5000);
                    //VehicleFaction_Create(playerid, 525, FACTION_BENGKEL, Bengkel_Stuff[bengkelgarageSpawnPos][0], Bengkel_Stuff[bengkelgarageSpawnPos][1], Bengkel_Stuff[bengkelgarageSpawnPos][2], Bengkel_Stuff[bengkelgarageSpawnPos][3], 3, 20, 5000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil!");
                }
                case 1: //Rumpo 
                {
                    if(AccountData[playerid][pMoney] < 8000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 8000);
                    //VehicleFaction_Create(playerid, 440, FACTION_BENGKEL, Bengkel_Stuff[bengkelgarageSpawnPos][0], Bengkel_Stuff[bengkelgarageSpawnPos][1], Bengkel_Stuff[bengkelgarageSpawnPos][2], Bengkel_Stuff[bengkelgarageSpawnPos][3], 1, 20, 8000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil!");
                }
                case 2: //Sanchez 
                {
                    if(AccountData[playerid][pMoney] < 4000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 4000);
                    //VehicleFaction_Create(playerid, 468, FACTION_BENGKEL, Bengkel_Stuff[bengkelgarageSpawnPos][0], Bengkel_Stuff[bengkelgarageSpawnPos][1], Bengkel_Stuff[bengkelgarageSpawnPos][2], Bengkel_Stuff[bengkelgarageSpawnPos][3], 86, 86, 4000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil!");
                }
                case 3: //Bloody 
                {
                    if(AccountData[playerid][pMoney] < 25000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 25000);
                   // VehicleFaction_Create(playerid, 504, FACTION_BENGKEL, Bengkel_Stuff[bengkelgarageSpawnPos][0], Bengkel_Stuff[bengkelgarageSpawnPos][1], Bengkel_Stuff[bengkelgarageSpawnPos][2], Bengkel_Stuff[bengkelgarageSpawnPos][3], 1, 20, 25000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil!");
                }
            }
        }
        case DIALOG_BENGKELTAKEVEH:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota bengkel!");
            if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            new id = GetVehicleIDStoredFactGarage(playerid, listitem, FACTION_BENGKEL);
            if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            if(!IsPlayerInRangeOfPoint(playerid, 2.0, Bengkel_Stuff[bengkelgaragePos][0], Bengkel_Stuff[bengkelgaragePos][1], Bengkel_Stuff[bengkelgaragePos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat garasi bengkel!");
            if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
            PlayerVehicle[id][pVehParked] = -1;
            PlayerVehicle[id][pVehHouseGarage] = -1;
            PlayerVehicle[id][pVehHelipadGarage] = -1;
            PlayerVehicle[id][pVehFamiliesGarage] = -1;
            PlayerVehicle[id][pVehFactStored] = -1;

            PlayerVehicle[id][pVehWorld] = GetPlayerVirtualWorld(playerid);
            PlayerVehicle[id][pVehInterior] = GetPlayerInterior(playerid);

            if(PlayerVehicle[id][pVehLocked])
                PlayerVehicle[id][pVehLocked] = false;

            PlayerVehicle[id][pVehPos][0] = Bengkel_Stuff[bengkelgarageSpawnPos][0];
            PlayerVehicle[id][pVehPos][1] = Bengkel_Stuff[bengkelgarageSpawnPos][1];
            PlayerVehicle[id][pVehPos][2] = Bengkel_Stuff[bengkelgarageSpawnPos][2];
            PlayerVehicle[id][pVehPos][3] = Bengkel_Stuff[bengkelgarageSpawnPos][3];

            OnPlayerVehicleRespawn(id);

            SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
        }
        case DIALOG_BENGKEL_LOCKER:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Bengkel!");

            switch(listitem)
            {
                case 0:
                {
                    SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
                    AccountData[playerid][pUsingUniform] = false;
                }
                case 1:
                {
                    ShowPlayerDialog(playerid, DIALOG_BENGKEL_CLOTHES, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Locker Bengkel",
                    "Bengkel 1\n"GRAY"Bengkel 2\nBengkel 3", "Pilih", "Batal");
                }
            }
        }
        case DIALOG_BENGKEL_CLOTHES:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Bengkel!");

            switch(listitem)
            {
                case 0: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (268) : (298);
                case 1: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (42) : (192);
                case 2: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (119) : (69);
            }
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
            AccountData[playerid][pUsingUniform] = true;
        }
        case DIALOG_MODIF_COLOROPTION:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:// Ganti Warna
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_WARNA1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warna 1", color_string, "Input", "Batal");
                    // ShowPlayerDialog(playerid, DIALOG_MODIF_WARNA1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warna 1", "Mohon masukkan ID Color Dimulai Dari Angka 1 - 255\n"YELLOW"(Masukkan Dibawah Sini):", "Input", "Batal");
                }
                case 1:// Paintjob
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_PAINTJOB, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Paint Job", "Mohon masukkan ID Paintjob kendaraan dikolom bawah ini:\n"YELLOW"(0 - 1 - 2 (3 Untuk Mengembalikan Ke Default))", "Input", "Batal");
                }
            }
        }
        case DIALOG_MODIF_WARNA1:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            
            AccountData[playerid][pMechColor1] = floatround(strval(inputtext));

            if(AccountData[playerid][pMechColor1] < 0 || AccountData[playerid][pMechColor1] > 255)
                return ShowPlayerDialog(playerid, DIALOG_MODIF_WARNA1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warna 1", "Mohon masukkan ID Color Dimulai Dari Angka 1 - 255\n"YELLOW"(Masukkan Dibawah Sini):", "Input", "Batal");
            
            ShowPlayerDialog(playerid, DIALOG_MODIF_WARNA2, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warna 2", color_string, "Input", "Batal");
            // ShowPlayerDialog(playerid, DIALOG_MODIF_WARNA2, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warna 2", "Mohon masukkan ID Color Dimulai Dari Angka 1 - 255\n"YELLOW"(Masukkan Dibawah Sini):", "Input", "Batal");
        }
        case DIALOG_MODIF_WARNA2:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;

            AccountData[playerid][pMechColor2] = floatround(strval(inputtext));

            if(AccountData[playerid][pMechColor2] < 0 || AccountData[playerid][pMechColor2] > 255)
                return ShowPlayerDialog(playerid, DIALOG_MODIF_WARNA2, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warna 2", "Mohon masukkan ID Color Dimulai Dari Angka 1 - 255\n"YELLOW"(Masukkan Dibawah Sini):", "Input", "Batal");

            new vehicleid = GetPlayerVehicleID(playerid);
            foreach(new ii : PvtVehicles)
            {
                ChangeVehicleColor(vehicleid, AccountData[playerid][pMechColor1], AccountData[playerid][pMechColor2]);
                if(vehicleid == PlayerVehicle[ii][pVehPhysic])
                {
                    PlayerVehicle[ii][pVehColor1] = AccountData[playerid][pMechColor1];
                    PlayerVehicle[ii][pVehColor2] = AccountData[playerid][pMechColor2];
                }
            }
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda Berhasil Mengganti Warna Kendaraan!");
        }
        case DIALOG_MODIF_PAINTJOB:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;

            AccountData[playerid][pMechColor1] = floatround(strval(inputtext));

            if(AccountData[playerid][pMechColor1] < 0 || AccountData[playerid][pMechColor1] > 3)
                return ShowPlayerDialog(playerid, DIALOG_MODIF_PAINTJOB, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Paint Job", "ERROR: 0 - 1- 2 (3 untuk mengembalikan ke Semula)\n\nMohon masukkan ID Paintjob kendaraan dikolom bawah ini:", "Input", "Batal");

            new vehicleid = GetPlayerVehicleID(playerid);
            foreach(new ii : PvtVehicles)
            {
                ChangeVehiclePaintjob(vehicleid, AccountData[playerid][pMechColor1]);
                if(vehicleid == PlayerVehicle[ii][pVehPhysic])
                {
                    PlayerVehicle[ii][pVehPaintjob] = AccountData[playerid][pMechColor1];
                }
            }
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda Berhasil Mengganti Paintjob Kendaraan!");
        }
        case DIALOG_MODIF:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
				{
					ShowPlayerDialog(playerid, DIALOG_MODIF_COLOROPTION, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Ganti Warna Kendaraan", "Ganti Warna Kendaraan\nPaint Job Kendaraan", "Pilih", "Batal");
				}
				case 1:
				{
					ShowPlayerDialog(playerid, DIALOG_MODIF_VELG, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Velg", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n"RED"> Kembalikan Menjadi Standart", "Confirm", "back");
				}
				case 2:
				{
					ShowPlayerDialog(playerid, DIALOG_MODIF_SPOILER,DIALOG_STYLE_LIST,""TCRP"District "WHITE" - Spoiler","Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n"RED"> Kembalikan Menjadi Standart","Choose","back");
				}
				case 3:
				{
					ShowPlayerDialog(playerid, DIALOG_MODIF_HOODS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Hoods", "Fury\nChamp\nRace\nWorx\n", "Confirm", "back");
				}
				case 4:
				{
					ShowPlayerDialog(playerid, DIALOG_MODIF_VENTS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Venst", "Oval\nSquare\n", "Confirm", "back");
				}
				case 5:
				{
					ShowPlayerDialog(playerid, DIALOG_MODIF_LIGHTS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Lights", "Round\nSquare\n", "Confirm", "back");
				}
				case 6:
				{
					ShowPlayerDialog(playerid, DIALOG_MODIF_EXHAUSTS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Exhaust", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n"RED"> Kembalikan Menjadi Standart", "Confirm", "back");
				}
				case 7:
				{
					ShowPlayerDialog(playerid, DIALOG_MODIF_FRONT_BUMPERS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Front Bumper", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n"RED"> Kembalikan Menjadi Standart", "Confirm", "back");
				}
				case 8:
				{
					ShowPlayerDialog(playerid, DIALOG_MODIF_REAR_BUMPERS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Rear Bumper", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n"RED"> Kembalikan Menjadi Standart", "Confirm", "back");
				}
				case 9:
				{
					ShowPlayerDialog(playerid, DIALOG_MODIF_ROOFS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n"RED"> Kembalikan Menjadi Standart", "Confirm", "back");
				}
				case 10:
				{
					ShowPlayerDialog(playerid, DIALOG_MODIF_SIDE_SKIRTS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Side Kirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n"RED"> Kembalikan Menjadi Standart", "Confirm", "back");
				}
				case 11:
				{
					ShowPlayerDialog(playerid, DIALOG_MODIF_BULLBARS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Bullbas", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar", "Confirm", "back");
				}
				case 12:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1087);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1087);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 13:
				{
					new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1009);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1009);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 14:
				{
					new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1008);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1008);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 15:
				{
					new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1010);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1010);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 16:
				{
					ShowPlayerDialog(playerid, DIALOG_MODIF_NEON, DIALOG_STYLE_LIST,""TCRP"District "WHITE" - Neon",
                    "Merah\
                    \n"GRAY"Biru\
                    \nHijau\
                    \n"GRAY"Kuning\
                    \nPink\
                    \n"GRAY"Putih\
                    \n"RED"> Remove Neon", "Pilih", "Batal");
				}
                case 17:
                {
                    ShowPlayerDialog(playerid, DIALOG_UPGRADE, DIALOG_STYLE_TABLIST, ""TCRP"District "WHITE"- Upgrade Kendaraan",
                    "Engine Upgrade\t$10000\
                    \n"GRAY"Body Upgrade\t"GRAY"$5000", "Upgrade", "Cancel");
                }
                case 18:
                {
                    ShowPlayerDialog(playerid, DIALOG_UPGRADEBAGASI, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Upgrade Kapasitas Bagasi",
                    "Luxury "YELLOW"(Max 70 kg)\
                    \n"WHITE"Compact "YELLOW" (Max 60 kg)\
                    \n"WHITE"Truck "YELLOW" (Max 100 kg)", "Pilih", "Batal");
                }
                case 19:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][11]);
                            PlayerVehicle[index][pVehMod][11] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
                case 20:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][1]);
                            PlayerVehicle[index][pVehMod][1] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_VELG:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
				{
					new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1025);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1025);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 1:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1074);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1074);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 2:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1076);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1076);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 3:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1078);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1078);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 4:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1081);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1081);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 5:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1082);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1082);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 6:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1085);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1085);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 7:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1096);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1096);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 8:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1097);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1097);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 9:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1098);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1098);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 10:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1084);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1084);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 11:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1073);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1073);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 12:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1075);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1075);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 13:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1077);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1077);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 14:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1079);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1079);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 15:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1080);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1080);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
				case 16:
				{
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1083);
						        SavePVComponents(PlayerVehicle[i][pVehPhysic], 1083);
						        PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
				}
                case 17:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][15]);
                            PlayerVehicle[index][pVehMod][15] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_SPOILER:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1147);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1147);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1049);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1049);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1162);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1162);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1058);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1058);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1164);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1164);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1138);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1138);
                                }
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 1:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1146);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1146);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1050);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1050);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1158);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1158);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1060);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1060);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1163);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1163);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1139);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1139);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 2:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic]) 
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 527 ||
                            VehicleModel == 415 ||
                            VehicleModel == 546 ||
                            VehicleModel == 603 ||
                            VehicleModel == 426 ||
                            VehicleModel == 436 ||
                            VehicleModel == 405 ||
                            VehicleModel == 477 ||
                            VehicleModel == 580 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1001);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1001);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 3:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic]) 
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 518 ||
                            VehicleModel == 415 ||
                            VehicleModel == 546 ||
                            VehicleModel == 517 ||
                            VehicleModel == 603 ||
                            VehicleModel == 405 ||
                            VehicleModel == 477 ||
                            VehicleModel == 580 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1023);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1023);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 4:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 518 ||
                            VehicleModel == 415 ||
                            VehicleModel == 401 ||
                            VehicleModel == 517 ||
                            VehicleModel == 426 ||
                            VehicleModel == 436 ||
                            VehicleModel == 477 ||
                            VehicleModel == 547 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1003);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1003);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 5:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 589 ||
                            VehicleModel == 492 ||
                            VehicleModel == 547 ||
                            VehicleModel == 405)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1000);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1000);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 6:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 527 ||
                            VehicleModel == 542 ||
                            VehicleModel == 405)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1014);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1014);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 7:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 527 ||
                            VehicleModel == 542)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1015);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1015);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 8:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
						if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 546 ||
                            VehicleModel == 517)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1002);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1002);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
                case 9:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][0]);
                            PlayerVehicle[index][pVehMod][0] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_HOODS:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 589 ||
                            VehicleModel == 492 ||
                            VehicleModel == 426 ||
                            VehicleModel == 550)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1005);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1005);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 1:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 401 ||
                            VehicleModel == 402 ||
                            VehicleModel == 546 ||
                            VehicleModel == 426 ||
                            VehicleModel == 550)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1004);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1004);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 2:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 401)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1011);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1011);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 3:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 549)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1012);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1012);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
            }
        }
        case DIALOG_MODIF_VENTS:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 546 ||
                            VehicleModel == 517 ||
                            VehicleModel == 603 ||
                            VehicleModel == 547 ||
                            VehicleModel == 439 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1142);
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1443);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1142);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1143);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 1:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 589 ||
                            VehicleModel == 546 ||
                            VehicleModel == 517 ||
                            VehicleModel == 603 ||
                            VehicleModel == 439 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1144);
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1145);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1144);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1145);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
            }
        }
        case DIALOG_MODIF_LIGHTS:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 589 ||
                            VehicleModel == 400 ||
                            VehicleModel == 436 ||
                            VehicleModel == 439)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1013);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1013);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 1:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 589 ||
                            VehicleModel == 603 ||
                            VehicleModel == 400)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1024);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1024);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
            }
        }
        case DIALOG_MODIF_EXHAUSTS:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 558 ||
                            VehicleModel == 561 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1034);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1034);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1046);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1046);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1065);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1065);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1064);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1064);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1028);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1028);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1089);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1089);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
				case 1:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 558 ||
                            VehicleModel == 561 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1037);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1037);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1045);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1045);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1066);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1066);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1059);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1059);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1029);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1029);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1092);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1092);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                else
                                {
                                    ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                                }
                            }
                        }
					}
				}
				case 2:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 575 ||
                            VehicleModel == 534 ||
                            VehicleModel == 567 ||
                            VehicleModel == 536 ||
                            VehicleModel == 576 ||
                            VehicleModel == 535)
                            {
                                if(VehicleModel == 575)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1044);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1044);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 534)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1126);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1126);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1129);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1129);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1104);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1104);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 576)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1113);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1113);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 535)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1136);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1136);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                else
                                {
                                    ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                                }
                            }
                        }
					}
				}
				case 3:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 575 ||
                            VehicleModel == 534 ||
                            VehicleModel == 567 ||
                            VehicleModel == 536 ||
                            VehicleModel == 576 ||
                            VehicleModel == 535)
                            {
                                if(VehicleModel == 575)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1043);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1043);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 534)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1127);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1127);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1132);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1132);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1105);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1105);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 576)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1135);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1135);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 535)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1114);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1114);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                else
                                {
                                    ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                                }
                            }
                        }
					}
				}
				case 4:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 527 ||
                            VehicleModel == 542 ||
                            VehicleModel == 589 ||
                            VehicleModel == 400 ||
                            VehicleModel == 517 ||
                            VehicleModel == 603 ||
                            VehicleModel == 426 ||
                            VehicleModel == 547 ||
                            VehicleModel == 405 ||
                            VehicleModel == 580 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549 ||
                            VehicleModel == 477)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1020);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1020);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 5:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 527 ||
                            VehicleModel == 542 ||
                            VehicleModel == 400 ||
                            VehicleModel == 426 ||
                            VehicleModel == 436 ||
                            VehicleModel == 547 ||
                            VehicleModel == 405 ||
                            VehicleModel == 477)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1021);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1021);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 6:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 436)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1022);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1022);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 7:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 518 ||
                            VehicleModel == 415 ||
                            VehicleModel == 542 ||
                            VehicleModel == 546 ||
                            VehicleModel == 400 ||
                            VehicleModel == 517 ||
                            VehicleModel == 603 ||
                            VehicleModel == 426 ||
                            VehicleModel == 436 ||
                            VehicleModel == 547 ||
                            VehicleModel == 405 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549 ||
                            VehicleModel == 477)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1019);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1019);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
				case 8:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 415 ||
                            VehicleModel == 542 ||
                            VehicleModel == 546 ||
                            VehicleModel == 400 ||
                            VehicleModel == 517 ||
                            VehicleModel == 603 ||
                            VehicleModel == 426 ||
                            VehicleModel == 415 ||
                            VehicleModel == 547 ||
                            VehicleModel == 405 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549 ||
                            VehicleModel == 477)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1018);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1018);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
					}
				}
                case 9:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][4]);
                            PlayerVehicle[index][pVehMod][4] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_FRONT_BUMPERS:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1171);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1171);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1153);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1153);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1160);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1160);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1155);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1155);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1166);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1166);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1169);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1169);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
				case 1:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1172);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1172);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1152);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1152);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1173);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1173);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1157);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1157);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1165);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1165);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1170);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1170);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
				case 2:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 575 ||
                            VehicleModel == 534 ||
                            VehicleModel == 567 ||
                            VehicleModel == 536 ||
                            VehicleModel == 576 ||
                            VehicleModel == 535)
                            {
                                if(VehicleModel == 575)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1174);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1174);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 534)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1179);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1179);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1189);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1189);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1182);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1182);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 576)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1191);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1191);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 535)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1115);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1115);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
				case 3:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 575 ||
                            VehicleModel == 534 ||
                            VehicleModel == 567 ||
                            VehicleModel == 536 ||
                            VehicleModel == 576 ||
                            VehicleModel == 535)
                            {
                                if(VehicleModel == 575)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1175);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1175);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 534)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1185);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1185);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1188);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1188);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1181);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1181);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 576)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1190);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1190);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 535)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1116);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1116);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
                case 4:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][2]);
                            PlayerVehicle[index][pVehMod][2] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_REAR_BUMPERS:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1149);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1149);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1150);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1150);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1159);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1159);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1154);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1154);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1168);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1168);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1141);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1141);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
				case 1:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1148);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1148);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1151);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1151);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1161);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1161);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1156);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1156);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1167);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1167);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1140);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1140);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
				case 2:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 575 ||
                            VehicleModel == 534 ||
                            VehicleModel == 567 ||
                            VehicleModel == 536 ||
                            VehicleModel == 576 ||
                            VehicleModel == 535)
                            {
                                if(VehicleModel == 575)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1176);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1176);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 534)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1180);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1180);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1187);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1187);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1184);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1184);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 576)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1192);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1192);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 535)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1109);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1109);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
				case 3:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 575 ||
                            VehicleModel == 534 ||
                            VehicleModel == 567 ||
                            VehicleModel == 536 ||
                            VehicleModel == 576 ||
                            VehicleModel == 535)
                            {
                                if(VehicleModel == 575)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1177);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1177);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 534)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1178);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1178);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1186);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1186);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1183);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1183);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 576)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1193);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1193);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 535)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1110);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1110);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
                case 4:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][3]);
                            PlayerVehicle[index][pVehMod][3] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_ROOFS:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1038);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1038);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1054);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1054);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1067);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1067);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1055);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1055);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1088);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1088);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1032);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1032);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
				case 1:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1038);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1038);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1053);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1053);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1068);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1068);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1061);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1061);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1091);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1091);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1033);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1033);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
				case 2:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 567 ||
                            VehicleModel == 536)
                            {
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1130);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1130);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1128);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1128);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
				case 3:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 567 ||
                            VehicleModel == 536)
                            {
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1131);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1131);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1103);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1103);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
				case 4:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 589 ||
                            VehicleModel == 492 ||
                            VehicleModel == 546 ||
                            VehicleModel == 603 ||
                            VehicleModel == 426 ||
                            VehicleModel == 436 ||
                            VehicleModel == 580 ||
                            VehicleModel == 550 ||
                            VehicleModel == 477)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1006);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1006);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
					}
				}
                case 5:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][8]);
                            PlayerVehicle[index][pVehMod][8] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_SIDE_SKIRTS:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1036);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1040);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1036);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1040);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1047);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1051);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1047);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1051);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1069);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1071);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1069);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1071);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1056);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1062);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1056);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1062);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1090);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1094);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1090);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1094);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1026);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1027);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1026);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1027);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
				case 1:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1039);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1041);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1039);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1041);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1048);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1052);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1048);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1052);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1070);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1072);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1070);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1072);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1057);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1063);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1057);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1063);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1093);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1095);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1093);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1095);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1031);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1030);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1031);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1030);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
				case 2:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 575 ||
                            VehicleModel == 536 ||
                            VehicleModel == 576 ||
                            VehicleModel == 567)
                            {
                                if(VehicleModel == 575)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1042);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1099);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1042);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1099);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1108);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1107);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1108);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1107);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 576)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1134);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1137);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1134);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1137);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1102);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1133);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1102);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1133);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
					}
				}
				case 3:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 534)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1102);
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1101);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1102);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1101);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
					}
				}
				case 4:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 534)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1106);
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1124);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1106);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1124);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
					}
				}
				case 5:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 535)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1118);
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1120);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1118);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1120);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
					}
				}
				case 6:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 535)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1119);
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1121);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1119);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1121);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
					}
				}
				case 7:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 527 ||
                            VehicleModel == 415 ||
                            VehicleModel == 589 ||
                            VehicleModel == 546 ||
                            VehicleModel == 517 ||
                            VehicleModel == 603 ||
                            VehicleModel == 436 ||
                            VehicleModel == 439 ||
                            VehicleModel == 580 ||
                            VehicleModel == 549 ||
                            VehicleModel == 477)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1007);
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1017);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1007);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1017);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
					}
				}
                case 8:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][9]);
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][10]);
                            PlayerVehicle[index][pVehMod][9] = 0;
                            PlayerVehicle[index][pVehMod][10] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_BULLBARS:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 534)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1100);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1100);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
					}
				}
				case 1:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 534)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1123);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1123);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
					}
				}
				case 2:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 534)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1125);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1125);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
					}
				}
				case 3:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 534)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1117);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1117);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
					}
				}
            }
        }
        case DIALOG_UPGRADEBAGASI:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid))
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(AccountData[playerid][ActivityTime] != 0)
                return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu sampai selesai!");

            new vehid = GetPlayerVehicleID(playerid);
            if(!IsEngineVehicle(vehid))
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di dalam kendaraan!");

            new bool:found = false;

            foreach(new i : PvtVehicles)
            {
                if(vehid == PlayerVehicle[i][pVehPhysic])
                {
                    found = true;

                    new modelid = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                    new Float:maxCap = 0.0;
                    new reqComp = 0;

                    switch(listitem)
                    {
                        case 0: // Luxury
                        {
                            if(!IsLuxuryVeh(modelid))
                                return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan tipe Luxury/Sport!");
                            reqComp = 100;
                            maxCap = 70.0;
                        }
                        case 1: // Compact
                        {
                            if(!IsCompactVeh(modelid))
                                return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan tipe Compact!");
                            reqComp = 70; // harga komponen Compact
                            maxCap = 60.0;
                        }
                        case 2: // Truck
                        {
                            if(!IsTruckVeh(modelid))
                                return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan tipe Truck!");
                            reqComp = 200; // harga komponen Truck
                            maxCap = 100.0;
                        }
                    }

                    // cek komponen
                    if(Inventory_Count(playerid, "Component") < reqComp)
                        return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda butuh %d component untuk upgrade ini!", reqComp));

                    // cek kapasitas maksimum
                    if(PlayerVehicle[i][pVehCapacity] >= maxCap)
                        return ShowTDN(playerid, NOTIFICATION_ERROR, "Kapasitas kendaraan ini sudah maksimum!");

                    // Set status upgrade
                    AccountData[playerid][ActivityTime] = 1;
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "UPGRADE BAGASI");
                    ShowProgressBar(playerid);

                    //ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);

                    // Jalankan timer dengan slot PvtVehicle
                    pUpgradeBagasiTimer[playerid] = SetTimerEx("FinishUpgradeBagasi", 1000, true, "dd", playerid, i);

                    printf("DEBUG: UpgradeBagasi DIMULAI playerid=%d slot=%d vehid=%d type=%d reqComp=%d maxCap=%.1f",playerid, i, vehid, listitem, reqComp, maxCap);
                    break;
                }
            }

            if(!found)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tidak ditemukan di data pribadi!");
        }
        case DIALOG_UPGRADE:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            switch(listitem)
            {
                case 0: // Engine
                {
                    if(AccountData[playerid][pMoney] < 10000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    
                    new vehid = GetPlayerVehicleID(playerid);
                    Vehicle_AddUpgrade(vehid, 1);
                    TakeMoney(playerid, 10000);
                    Info(playerid, "Anda mengupgrade engine "YELLOW"%s"WHITE" Max Health Kendaraan sekarang "YELLOW"2000.0", GetVehicleName(vehid));
                }
                case 1: // Body
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    
                    new vehid = GetPlayerVehicleID(playerid);
                    Vehicle_AddUpgrade(vehid, 3);
                    TakeMoney(playerid, 5000);
                    Info(playerid, "Anda mengupgrade body "YELLOW"%s"WHITE" Body kendaraan sekarang tidak mudah hancur", GetVehicleName(vehid));
                }
            }
            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
        }
        case DIALOG_MODIF_NEON:
        {
            if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari BENGKEL District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, RED_NEON, 0);

                            PlayerVehicle[i][pVehNeon] = RED_NEON;

                            if(PlayerVehicle[i][pVehNeon] == 0)
                            {
                                PlayerVehicle[i][cTogNeon] = 0;
                            }
                            else 
                            {
                                PlayerVehicle[i][cTogNeon] = 1;
                            }
                        }
					}
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				}
				case 1:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, BLUE_NEON, 0);

                            PlayerVehicle[i][pVehNeon] = BLUE_NEON;

                            if(PlayerVehicle[i][pVehNeon] == 0)
                            {
                                PlayerVehicle[i][cTogNeon] = 0;
                            }
                            else 
                            {
                                PlayerVehicle[i][cTogNeon] = 1;
                            }
                        }
					}
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				}
				case 2:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, GREEN_NEON, 0);

                            PlayerVehicle[i][pVehNeon] = GREEN_NEON;

                            if(PlayerVehicle[i][pVehNeon] == 0)
                            {
                                PlayerVehicle[i][cTogNeon] = 0;
                            }
                            else 
                            {
                                PlayerVehicle[i][cTogNeon] = 1;
                            }
                        }
					}
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				}
				case 3:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, YELLOW_NEON, 0);

                            PlayerVehicle[i][pVehNeon] = YELLOW_NEON;

                            if(PlayerVehicle[i][pVehNeon] == 0)
                            {
                                PlayerVehicle[i][cTogNeon] = 0;
                            }
                            else 
                            {
                                PlayerVehicle[i][cTogNeon] = 1;
                            }
                        }
					}
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				}
				case 4:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, PINK_NEON, 0);

                            PlayerVehicle[i][pVehNeon] = PINK_NEON;

                            if(PlayerVehicle[i][pVehNeon] == 0)
                            {
                                PlayerVehicle[i][cTogNeon] = 0;
                            }
                            else 
                            {
                                PlayerVehicle[i][cTogNeon] = 1;
                            }
                        }
					}
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				}
				case 5:
				{
                    new vehid = GetPlayerVehicleID(playerid);
					foreach(new i : PvtVehicles)
					{
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, WHITE_NEON, 0);

                            PlayerVehicle[i][pVehNeon] = WHITE_NEON;

                            if(PlayerVehicle[i][pVehNeon] == 0)
                            {
                                PlayerVehicle[i][cTogNeon] = 0;
                            }
                            else 
                            {
                                PlayerVehicle[i][cTogNeon] = 1;
                            }
                        }
					}
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				}
                case 6:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            SetVehicleNeonLights(vehid, false, PlayerVehicle[index][pVehNeon], 0);
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehNeon]);
                            PlayerVehicle[index][pVehNeon] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
    }
    return 1;
}

// ------------------------------------------------------------- Callback Function
forward CreateToolsKit(playerid);
public CreateToolsKit(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Bengkel_Stuff[BengkelCraft]))
    {
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(IsPlayerInjured(playerid))
    {
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(GetTotalWeightFloat(playerid) >= 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Besi") < 15)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Besi anda tidak cukup!");
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Tembaga") < 15)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Tembaga anda tidak cukup!");
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Pure Oil") < 1)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Pure Oil anda tidak cukup!");
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 10)
    {
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    
        Inventory_Remove(playerid, "Besi", 15);
        Inventory_Remove(playerid, "Tembaga", 15);
        Inventory_Remove(playerid, "Pure Oil", 1);
        Inventory_Add(playerid, "Tools Kit", 19918, 1);
        ShowItemBox(playerid, "Received 1x", "Tools Kit", 19918);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/10;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward CreateRepairKit(playerid);
public CreateRepairKit(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Bengkel_Stuff[BengkelCraft]))
    {
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(IsPlayerInjured(playerid))
    {
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(GetTotalWeightFloat(playerid) >= 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Besi") < 15)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Besi anda tidak cukup!");
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Tembaga") < 15)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Tembaga anda tidak cukup!");
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Petrol") < 1)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Petrol anda tidak cukup!");
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 120)
    {
        KillTimer(pTimerCreateKit[playerid]);
        pTimerCreateKit[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    
        Inventory_Remove(playerid, "Besi", 15);
        Inventory_Remove(playerid, "Tembaga", 15);
        Inventory_Remove(playerid, "Petrol", 1);
        Inventory_Add(playerid, "Repair Kit", 19921, 1);
        ShowItemBox(playerid, "Received 1x", "REPAIR KIT", 19921);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 20;

        new Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110.0/120;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

// -------------------------------------------------------------
new pv_spoiler[20][0] =
{
	{1000},
	{1001},
	{1002},
	{1003},
	{1014},
	{1015},
	{1016},
	{1023},
	{1058},
	{1060},
	{1049},
	{1050},
	{1138},
	{1139},
	{1146},
	{1147},
	{1158},
	{1162},
	{1163},
	{1164}
};
new pv_nitro[3][0] =
{
    {1008},
    {1009},
    {1010}
};
new pv_fbumper[23][0] =
{
    {1117},
    {1152},
    {1153},
    {1155},
    {1157},
    {1160},
    {1165},
    {1166},
    {1169},
    {1170},
    {1171},
    {1172},
    {1173},
    {1174},
    {1175},
    {1179},
    {1181},
    {1182},
    {1185},
    {1188},
    {1189},
    {1190},
    {1191}
};
new pv_rbumper[22][0] =
{
    {1140},
    {1141},
    {1148},
    {1149},
    {1150},
    {1151},
    {1154},
    {1156},
    {1159},
    {1161},
    {1167},
    {1168},
    {1176},
    {1177},
    {1178},
    {1180},
    {1183},
    {1184},
    {1186},
    {1187},
    {1192},
    {1193}
};
new pv_exhaust[28][0] =
{
    {1018},
    {1019},
    {1020},
    {1021},
    {1022},
    {1028},
    {1029},
    {1037},
    {1043},
    {1044},
    {1045},
    {1046},
    {1059},
    {1064},
    {1065},
    {1066},
    {1089},
    {1092},
    {1104},
    {1105},
    {1113},
    {1114},
    {1126},
    {1127},
    {1129},
    {1132},
    {1135},
    {1136}
};
new pv_bventr[2][0] =
{
    {1142},
    {1144}
};
new pv_bventl[2][0] =
{
    {1143},
    {1145}
};
new pv_bscoop[4][0] =
{
	{1004},
	{1005},
	{1011},
	{1012}
};
new pv_roof[17][0] =
{
    {1006},
    {1032},
    {1033},
    {1035},
    {1038},
    {1053},
    {1054},
    {1055},
    {1061},
    {1067},
    {1068},
    {1088},
    {1091},
    {1103},
    {1128},
    {1130},
    {1131}
};
new pv_lskirt[21][0] =
{
    {1007},
    {1026},
    {1031},
    {1036},
    {1039},
    {1042},
    {1047},
    {1048},
    {1056},
    {1057},
    {1069},
    {1070},
    {1090},
    {1093},
    {1106},
    {1108},
    {1118},
    {1119},
    {1133},
    {1122},
    {1134}
};
new pv_rskirt[21][0] =
{
    {1017},
    {1027},
    {1030},
    {1040},
    {1041},
    {1051},
    {1052},
    {1062},
    {1063},
    {1071},
    {1072},
    {1094},
    {1095},
    {1099},
    {1101},
    {1102},
    {1107},
    {1120},
    {1121},
    {1124},
    {1137}
};
new pv_hydraulics[1][0] =
{
    {1087}
};
new pv_base[1][0] =
{
    {1086}
};
new pv_rbbars[4][0] =
{
    {1109},
    {1110},
    {1123},
    {1125}
};
new pv_fbbars[2][0] =
{
    {1115},
    {1116}
};
new pv_wheels[17][0] =
{
    {1025},
    {1073},
    {1074},
    {1075},
    {1076},
    {1077},
    {1078},
    {1079},
    {1080},
    {1081},
    {1082},
    {1083},
    {1084},
    {1085},
    {1096},
    {1097},
    {1098}
};
new pv_lights[2][0] =
{
	{1013},
	{1024}
};

SavePVComponents(vehicleid, componentid)
{
	foreach(new ii: PvtVehicles)
	{
		if(vehicleid == PlayerVehicle[ii][pVehPhysic])
		{
			for(new s = 0; s < 20; s++)
			{
				if(componentid == pv_spoiler[s][0])
				{
					PlayerVehicle[ii][pVehMod][0] = componentid;
				}
			}

			for(new s = 0; s < 3; s++)
			{
				if(componentid == pv_nitro[s][0])
				{
					PlayerVehicle[ii][pVehMod][1] = componentid;
				}
			}

			for(new s = 0; s < 23; s++)
			{
				if(componentid == pv_fbumper[s][0])
				{
					PlayerVehicle[ii][pVehMod][2] = componentid;
				}
			}

			for(new s = 0; s < 22; s++)
			{
				if(componentid == pv_rbumper[s][0])
				{
					PlayerVehicle[ii][pVehMod][3] = componentid;
				}
			}

			for(new s = 0; s < 28; s++)
			{
				if(componentid == pv_exhaust[s][0])
				{
					PlayerVehicle[ii][pVehMod][4] = componentid;
				}
			}

			for(new s = 0; s < 2; s++)
			{
				if(componentid == pv_bventr[s][0])
				{
					PlayerVehicle[ii][pVehMod][5] = componentid;
				}
			}

			for(new s = 0; s < 2; s++)
			{
				if(componentid == pv_bventl[s][0])
				{
					PlayerVehicle[ii][pVehMod][6] = componentid;
				}
			}

			for(new s = 0; s < 4; s++)
			{
				if(componentid == pv_bscoop[s][0])
				{
					PlayerVehicle[ii][pVehMod][7] = componentid;
				}
			}

			for(new s = 0; s < 17; s++)
			{
				if(componentid == pv_roof[s][0])
				{
					PlayerVehicle[ii][pVehMod][8] = componentid;
				}
			}

			for(new s = 0; s < 21; s++)
			{
				if(componentid == pv_lskirt[s][0])
				{
					PlayerVehicle[ii][pVehMod][9] = componentid;
				}
			}

			for(new s = 0; s < 21; s++)
			{
				if(componentid == pv_rskirt[s][0])
				{
					PlayerVehicle[ii][pVehMod][10] = componentid;
				}
			}

			for(new s = 0; s < 1; s++)
			{
				if(componentid == pv_hydraulics[s][0])
				{
					PlayerVehicle[ii][pVehMod][11] = componentid;
				}
			}

			for(new s = 0; s < 1; s++)
			{
				if(componentid == pv_base[s][0])
				{
					PlayerVehicle[ii][pVehMod][12] = componentid;
				}
			}

			for(new s = 0; s < 4; s++)
			{
				if(componentid == pv_rbbars[s][0])
				{
					PlayerVehicle[ii][pVehMod][13] = componentid;
				}
			}

			for(new s = 0; s < 2; s++)
			{
				if(componentid == pv_fbbars[s][0])
				{
					PlayerVehicle[ii][pVehMod][14] = componentid;
				}
			}

			for(new s = 0; s < 17; s++)
			{
				if(componentid == pv_wheels[s][0])
				{
					PlayerVehicle[ii][pVehMod][15] = componentid;
				}
			}

			for(new s = 0; s < 2; s++)
			{
				if(componentid == pv_lights[s][0])
				{
					PlayerVehicle[ii][pVehMod][16] = componentid;
				}
			}
		}
	}
	return 1;
}

/*DialogPages:BengkelSetRank(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Bengkel District !");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Bengkel untuk mengakses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 5 ORDER BY `Char_FactionRank` DESC");
    new rows = cache_num_rows();
    if(rows)
    {
        cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
        cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak dapat mengatur jabatan sendiri!");
        if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengatur jabatan rank diatasmu!");
        ShowPlayerDialog(playerid, DIALOG_RANK_SET_BENGKEL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan",
        "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
        1. Magang\n\
        2. Junior\n\
        3. Senior\n\
        4. Manager Bengkel\n\
        5. Wakil Bengkel\n\
        6. Kepala Bengkel", "Set", "Batal");
    }
    return 1;
}

DialogPages:BengkelKickMember(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Bengkel District !");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Manager Bengkel untuk mengakses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 5 ORDER BY `Char_FactionRank` DESC");
    if(cache_num_rows())
    {
        new pidrow, fckname[64], fckrank, fcklastlogin[30], kckstr[225], icsr[128];

        cache_get_value_name_int(listitem, "pID", pidrow);
        cache_get_value_name(listitem, "Char_Name", fckname);
        cache_get_value_name_int(listitem, "Char_FactionRank", fckrank);
        cache_get_value_name(listitem, "Char_LastLogin", fcklastlogin);

        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat kick diri sendiri!");
        if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat kick pangkat diatasmu!");

        // kendaraan pribadi yg milik faction di cek
        new strgbg[158];
        mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_OwnerID`=%d AND `PVeh_Faction` = 5", pidrow);
        mysql_tquery(g_SQL, strgbg);

        foreach(new i : Player)
        {
            if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && pidrow == AccountData[i][pID])
            {
                AccountData[i][pFaction] = 0;
                AccountData[i][pFactionRank] = 0;

                //jika kendaraan pribadi ada di server dan player sedang online, maka kendaraan fisik dihapus
                foreach(new pvid : PvtVehicles)
                {
                    if(PlayerVehicle[pvid][pVehExists] && PlayerVehicle[pvid][pVehOwnerID] == AccountData[i][pID])
                    {
                        if(PlayerVehicle[pvid][pVehFaction] == FACTION_BENGKEL)
                        {
                            PlayerVehicle[pvid][pVehExists] = false;

                            if(IsValidVehicle(PlayerVehicle[pvid][pVehPhysic]))
                            {
                                DisableVehicleSpeedCap(PlayerVehicle[pvid][pVehPhysic]);
                                SetVehicleNeonLights(PlayerVehicle[pvid][pVehPhysic], false, PlayerVehicle[pvid][pVehNeon], 0);

                                DestroyVehicle(PlayerVehicle[pvid][pVehPhysic]);
                                PlayerVehicle[pvid][pVehPhysic] = INVALID_VEHICLE_ID;
                            }

                            Iter_Remove(PvtVehicles, pvid);
                        }
                    }
                }
                if(AccountData[i][pDutyBengkel])
                    AccountData[i][pDutyBengkel] = false;
                if(AccountData[i][pUsingUniform])
                    AccountData[i][pUsingUniform] = false;
                SetPlayerSkin(i, AccountData[i][pSkin]);
                RefreshFactionMap(i);
                ShowTDN(i, NOTIFICATION_WARNING, "Anda telah dikeluarkan dari faction Bengkel District !");
            }
        }
        mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`=0, `Char_FactionRank`=0, `Char_UsingUniform`=0 WHERE `pID`=%d", pidrow);
        mysql_tquery(g_SQL, icsr);
        format(kckstr, sizeof(kckstr), "Anda telah berhasil menendang anggota:\n\
        Nama: %s\n\
        Rank: %s\n\
        Last Online: %s", fckname, BengkelRank[fckrank], fcklastlogin);
        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota",
        kckstr, "Tutup", "");

        AccountData[playerid][pTempSQLFactMemberID] = -1;
        AccountData[playerid][pTempSQLFactRank] = 0;
    }
    return 1;
}*/

forward OnBengkelDeposit(playerid);
public OnBengkelDeposit(playerid)
{
    BrankasLastUse[playerid] = 0;
    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyimpan item");
    FactionBrankas[playerid][factionBrankasID] = 0;
    FactionBrankas[playerid][factionBrankasTemp] = EOS;
    FactionBrankas[playerid][factionBrankasModel] = 0;
    FactionBrankas[playerid][factionBrankasQuant] = 0;
    return 1;
}


CMD:modif(playerid, params[])
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(!AccountData[playerid][IsLoggedIn]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus login!");
    if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Bengkel District !");
    if(!AccountData[playerid][pDutyBengkel]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty Bengkel!");
    if(!IsEngineVehicle(vehicleid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak didalam kendaraan!");
    if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");

    if(IsAModifArea(playerid))
    {
        static minsty[512];
        format(minsty, sizeof(minsty), ""WHITE"Ganti Warna Kendaraan\n");
        format(minsty, sizeof(minsty), "%s"GRAY"Velg Kendaraan\n", minsty);
        format(minsty, sizeof(minsty), "%s"WHITE"Spoiler Kendaraan\n", minsty);
        format(minsty, sizeof(minsty), "%s"GRAY"Hood Kendaraan\n", minsty);
        format(minsty, sizeof(minsty), "%s"WHITE"Vents Kendaraan\n", minsty);
        format(minsty, sizeof(minsty), "%s"GRAY"Lights Kendaraan\n", minsty);
        format(minsty, sizeof(minsty), "%s"WHITE"Exhaust Kendaraan\n", minsty);
        format(minsty, sizeof(minsty), "%s"GRAY"Front Bumper\n", minsty);
        format(minsty, sizeof(minsty), "%s"WHITE"Rear Bumper\n", minsty);
        format(minsty, sizeof(minsty), "%s"GRAY"Roofs Kendaraan\n", minsty);
        format(minsty, sizeof(minsty), "%s"WHITE"Side Kirts\n", minsty);
        format(minsty, sizeof(minsty), "%s"GRAY"Bullbars Kendaraan\n", minsty);
        format(minsty, sizeof(minsty), "%s"WHITE"Hydraulic Kendaraan\n", minsty);
        format(minsty, sizeof(minsty), "%s"GRAY"Nitro X3\n", minsty);
        format(minsty, sizeof(minsty), "%s"WHITE"Nitro X5\n", minsty);
        format(minsty, sizeof(minsty), "%s"GRAY"Nitro X10\n", minsty);
        format(minsty, sizeof(minsty), "%s"WHITE"Neon Kendaraan\n", minsty);
        format(minsty, sizeof(minsty), "%s"WHITE"Upgrade Kendaraan\n", minsty);
        format(minsty, sizeof(minsty), "%s"WHITE"Upgrade Kapasitas Bagasi\n", minsty);
        format(minsty, sizeof(minsty), "\n%s"RED"> Remove Hydraulic\n", minsty);
        format(minsty, sizeof(minsty), "%s"RED"> Remove Nitro\n", minsty);
        ShowPlayerDialog(playerid, DIALOG_MODIF, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Modifikasi", minsty, "Pilih", "Batal");
    }
    return 1;
}

forward FinishUpgradeBagasi(playerid, slot);
public FinishUpgradeBagasi(playerid, slot)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pUpgradeBagasiTimer[playerid]);
        pUpgradeBagasiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(PlayerVehicle[slot][pVehID] <= 0)
    {
        SavePlayerVehicle(slot);
        if(PlayerVehicle[slot][pVehID] <= 0)
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Upgrade gagal: kendaraan belum tersimpan di database!");
            KillTimer(pUpgradeBagasiTimer[playerid]);
            pUpgradeBagasiTimer[playerid] = -1;
            AccountData[playerid][ActivityTime] = 0;
            HideProgressBar(playerid);
            return 0;
        }
    }

    if(AccountData[playerid][pInjured])
    {
        Error(playerid, "Anda sedang pingsan!");
        KillTimer(pUpgradeBagasiTimer[playerid]);
        pUpgradeBagasiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    // Lama proses = 15 detik
    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pUpgradeBagasiTimer[playerid]);
        pUpgradeBagasiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        new modelid = GetVehicleModel(PlayerVehicle[slot][pVehPhysic]);
        new Float:maxCap = 0.0;
        new reqComp = 0;

        if(IsLuxuryVeh(modelid)) { maxCap = 70.0; reqComp = 100; }
        else if(IsCompactVeh(modelid)) { maxCap = 60.0; reqComp = 70; }
        else if(IsTruckVeh(modelid)) { maxCap = 100.0; reqComp = 200; }

        if(maxCap <= 0.0 || reqComp <= 0)
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak mendukung upgrade kapasitas!");
            return 0;
        }

        // Hapus komponen sesuai tipe
        Inventory_Remove(playerid, "Component", reqComp);
        ShowItemBox(playerid, sprintf("Removed %dx", reqComp), "Component", 3096);

        // Upgrade kapasitas
        PlayerVehicle[slot][pVehCapacity] += 10.0;
        if(PlayerVehicle[slot][pVehCapacity] > maxCap)
            PlayerVehicle[slot][pVehCapacity] = maxCap;

        // Debug log
        printf("DEBUG: FinishUpgradeBagasi playerid=%d slot=%d vehid=%d pVehID=%d reqComp=%d NewCap=%.2f/%.2f",playerid, slot, PlayerVehicle[slot][pVehPhysic], PlayerVehicle[slot][pVehID],reqComp, PlayerVehicle[slot][pVehCapacity], maxCap);

        // Update DB
        new query[256];
        mysql_format(g_SQL, query, sizeof(query), "UPDATE player_vehicles SET PVeh_Capacity = %.2f WHERE id = %d",PlayerVehicle[slot][pVehCapacity], PlayerVehicle[slot][pVehID]);
        mysql_tquery(g_SQL, query);

        ShowTDN(playerid, NOTIFICATION_SUKSES,sprintf("Upgrade selesai! Kapasitas sekarang: %.0f kg", PlayerVehicle[slot][pVehCapacity]));

        return 1;
    }
    else
    {
        AccountData[playerid][ActivityTime]++;
        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/15; 
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
    }
    return 1;
}
