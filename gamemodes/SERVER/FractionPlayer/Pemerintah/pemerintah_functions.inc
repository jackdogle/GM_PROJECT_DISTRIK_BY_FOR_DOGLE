#include <YSI\y_hooks>

enum e_pemerstuff
{
    Float:PemerGaragePOS[3],
    Float:PemerSpawnPOS[4],

    STREAMER_TAG_AREA:PemerDuty,
    STREAMER_TAG_AREA:PemerBrankas,
    STREAMER_TAG_AREA:PemerLocker,
    STREAMER_TAG_AREA:PemerDesk,
    STREAMER_TAG_AREA:PemerGarage,
};
new PemerStuff[e_pemerstuff];
new PemerObject[MAX_PLAYERS][5];

new const PemerintahRank[9][] = {
    "N/A",
    "Magang",
    "Staff",
    "Staff Senior",
    "Wakil Divisi",
    "Kepala Divisi",
    "Sekda",
    "Wakil Gubernur",
    "Gubernur"
};

VarsDoorPemerintah()
{
    PemerStuff[PemerDuty] = CreateDynamicSphere(1410.2715,1565.2283,3010.8323, 2.0, 0, 0, -1);
    PemerStuff[PemerBrankas] = CreateDynamicSphere(1427.3378,1555.8997,3010.8323, 2.0, 0, 0, -1);
    PemerStuff[PemerLocker] = CreateDynamicSphere(1413.1270,1563.4674,3010.8323, 2.0, 0, 0, -1);
    PemerStuff[PemerDesk] = CreateDynamicSphere(1402.9844,1523.8341,3010.8398, 2.0, 0, 0, -1);
    PemerStuff[PemerGarage] = CreateDynamicSphere(1239.3116, -2029.9304, 59.9014, 2.0, -1, -1, -1);
}

hook OnGameModeInit()
{
    VarsDoorPemerintah();
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pFaction] == FACTION_PEMERINTAH)
        {
            if(IsPlayerInDynamicArea(playerid, PemerStuff[PemerDuty]))
            {
                if(!AccountData[playerid][pDutyPemerintah])
                {
                    AccountData[playerid][pDutyPemerintah] = true;
                    SetFactionColor(playerid);
                    AccountData[playerid][pDutyTimer] = SetTimerEx("FactDutyHour", 1000, true, "i", playerid);
                    ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~g~On Duty~w~ Pemerintah");
                }
                else 
                {
                    AccountData[playerid][pDutyPemerintah] = false;
                    SetPlayerColor(playerid, COLOR_WHITE);
                    ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~r~Off Duty~w~ Pemerintah");
                }
                RefreshFactionMap(playerid);
            }

            if(IsPlayerInDynamicArea(playerid, PemerStuff[PemerLocker]) && AccountData[playerid][pDutyPemerintah])
            {
                ShowPlayerDialog(playerid, DIALOG_PEMERINTAH_LOCKER, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Locker Pemerintah",
                "Baju Warga\n"GRAY"Baju Tugas", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PemerStuff[PemerDesk]) && AccountData[playerid][pDutyPemerintah])
            {
                if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank SEKDA untuk mengakses bos desk!");

                ShowPlayerDialog(playerid, DIALOG_PEMERINTAH_BOSDESK, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Bos Desk",
                "Invite\
                \n"GRAY"Kelola Jabatan\
                \nKick\
                \n"GRAY"Lihat Anggota\
                \nSaldo Finansial\
                \n"GRAY"Deposit Saldo\
                \nTarik Saldo", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PemerStuff[PemerBrankas]) && AccountData[playerid][pDutyPemerintah])
            {
                if(NearPlayerOpenStorage(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain disekitar sedang membuka brankas!");
                
                AccountData[playerid][menuShowed] = true;
                ShowPlayerDialog(playerid, DIALOG_PEMERVAULT, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Brankas Pemerintah",
                "Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Batal");
            }

            /*if(IsPlayerInRangeOfPoint(playerid, 2.0, PemerStuff[PemerGaragePOS][0], PemerStuff[PemerGaragePOS][1], PemerStuff[PemerGaragePOS][2]) && AccountData[playerid][pDutyPemerintah])
            {
                ShowPlayerDialog(playerid, DIALOG_PEMER_GARAGE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Garasi Pemerintah",
                "Keluarkan Kendaraan\
                \n"GRAY"Simpan Kendaraan\
                \nBeli Kendaraan\
                \n"GRAY"Hapus Kendaraan", "Pilih", "Batal");
            }*/
        }
    }
    return 1;
}
//----------------------------------------------
hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    static icsr[1024];
    switch(dialogid)
    {
        case DIALOG_PEMER_GARAGE:
        {
            if(!response) return false;
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Daerah Kota District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            switch(listitem)
            {
                case 0:// Keluarkan kendaraan
                {
                    if(!CountPlayerFactVehInGarage(playerid, FACTION_PEMERINTAH)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun di garasi ini!");

                    new id, count = CountPlayerFactVehInGarage(playerid, FACTION_PEMERINTAH), lstr[596];
                    format(lstr, sizeof(lstr), "No\tModel Kendaraan\tNomor Plat\n");
                    for(new itt; itt < count; itt++)
                    {
                        id = GetVehicleIDStoredFactGarage(playerid, listitem, FACTION_PEMERINTAH);
                        if(itt == count)
                        {
                            format(lstr, sizeof(lstr), "%s%d\t%s\t%s", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                        }
                        else format(lstr, sizeof(lstr), "%s%d\t%s\t%s\n", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                    }
                    ShowPlayerDialog(playerid, DIALOG_PEMER_GARAGE_TAKEOUT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Garasi Gojek", lstr, "Pilih", "Batal");
                }
                case 1://Simpan Kendaraan
                {
                    new carid = -1, bool: foundnearby = false;
                    if((carid = Vehicle_Nearest(playerid, 15.0)) != -1)
                    {
                        if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
                        if(PlayerVehicle[carid][pVehRental] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat disimpan digarasi Faction!");
                        if(PlayerVehicle[carid][pVehFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan kendaraan Pemerintah!");
                        Vehicle_GetStatus(carid);
                        PlayerVehicle[carid][pVehFactStored] = FACTION_PEMERINTAH;

                        foundnearby = true;

                        if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]))
                        {
                            DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
                            SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

                            DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
                            PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
                        }
                    }
                    if(!foundnearby) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan dari Pemerintah District  milik anda di sekitar!");
                }
                case 2://Beli Kendaraan
                {
                    ShowPlayerDialog(playerid, DIALOG_PEMER_GARAGE_BUY, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Beli Kendaraan",
                    "Model\tHarga\
                    \nStretch\t$8000\
                    \n"GRAY"Stratum\t"GRAY"$5000\
                    \nHustler\t$10000", "Pilih", "Batal");
                }
                case 3:// Hapus Kendaraan
                {
                    new frmtdel[158];
                    mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 2 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
                    mysql_query(g_SQL, frmtdel);

                    new rows = cache_num_rows();
                    if(rows)
                    {
                        new list[255], havpid, havmod;
                        
                        format(list, sizeof(list), "Database ID\tModel\n");
                        for(new x; x < rows; ++x)
                        {
                            cache_get_value_name_int(x, "id", havpid);
                            cache_get_value_name_int(x, "PVeh_ModelID", havmod);

                            format(list, sizeof(list), "%s%d\t%s\n", list, havpid, GetVehicleModelName(havmod));
                        }
                        ShowPlayerDialog(playerid, DIALOG_PEMER_GARAGE_DELETE, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Hapus Kendaraan", list, "Hapus", "Batal");
                    }
                    else 
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Kendaraan", "Anda tidak memiliki kendaraan Pemerintah", "Tutup", "");
                    }
                }
            }
        }
        case DIALOG_PEMER_GARAGE_TAKEOUT:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pemerintah District ");
            if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            new id = GetVehicleIDStoredFactGarage(playerid, listitem, FACTION_PEMERINTAH);
            if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");
            
            if(!IsPlayerInRangeOfPoint(playerid, 3.0, PemerStuff[PemerGaragePOS][0], PemerStuff[PemerGaragePOS][1], PemerStuff[PemerGaragePOS][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di Garasi Pemerintah!");
            if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
            PlayerVehicle[id][pVehParked] = -1;
            PlayerVehicle[id][pVehHouseGarage] = -1;
            PlayerVehicle[id][pVehHelipadGarage] = -1;
            PlayerVehicle[id][pVehFamiliesGarage] = -1;
            PlayerVehicle[id][pVehFactStored] = -1;

            if(PlayerVehicle[id][pVehLocked])
                PlayerVehicle[id][pVehLocked] = false;

            PlayerVehicle[id][pVehPos][0] = PemerStuff[PemerSpawnPOS][0];
            PlayerVehicle[id][pVehPos][1] = PemerStuff[PemerSpawnPOS][1];
            PlayerVehicle[id][pVehPos][2] = PemerStuff[PemerSpawnPOS][2];
            PlayerVehicle[id][pVehPos][3] = PemerStuff[PemerSpawnPOS][3];

            OnPlayerVehicleRespawn(id);

            SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
        }
        case DIALOG_PEMER_GARAGE_DELETE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Daerah District !");

            new frmtdel[158], Cache:execute;
            mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 2 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
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

                    new pvid = GetFactionVehicleIDFromListitem(playerid, listitem, FACTION_PEMERINTAH);

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
        case DIALOG_PEMER_GARAGE_BUY:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pemerintah!");
            if(!IsPlayerInDynamicArea(playerid, PemerStuff[PemerGarage])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat Garasi Pemerintah!");

            // new count = 0;
            // foreach(new carid : PvtVehicles)
            // {
            //     if(PlayerVehicle[carid][pVehExists] && PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
            //         count ++;
            // }
            // if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");

            switch(listitem)
            {
                case 0: //stretch
                {
                    if(AccountData[playerid][pMoney] < 8000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 8000);
                    //VehicleFaction_Create(playerid, 409, FACTION_PEMERINTAH, PemerStuff[PemerSpawnPOS][0], PemerStuff[PemerSpawnPOS][1], PemerStuff[PemerSpawnPOS][2], PemerStuff[PemerSpawnPOS][3], 6, 6, 8000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan!");
                }
                case 1: //stratum
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 5000);
                    //VehicleFaction_Create(playerid, 561, FACTION_PEMERINTAH, PemerStuff[PemerSpawnPOS][0], PemerStuff[PemerSpawnPOS][1], PemerStuff[PemerSpawnPOS][2], PemerStuff[PemerSpawnPOS][3], 6, 6, 5000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan!");
                }
                case 2: //Hustler
                {
                    if(AccountData[playerid][pMoney] < 10000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 10000);
                    //VehicleFaction_Create(playerid, 545, FACTION_PEMERINTAH, PemerStuff[PemerSpawnPOS][0], PemerStuff[PemerSpawnPOS][1], PemerStuff[PemerSpawnPOS][2], PemerStuff[PemerSpawnPOS][3], 6, 6, 5000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan!");
                }
            }
        }
        case DIALOG_PEMERVAULT:
        {
            if(!response) 
            {
                AccountData[playerid][menuShowed] = false;
                return 1;
            }
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) 
            {
                AccountData[playerid][menuShowed] = false;   
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari Pemerintah Daerah Kota District !");
            }
            switch(listitem)
            {
                case 0: //deposit
                {
                    FactionBrankas[playerid][factionBrankasID] = 0;
                    FactionBrankas[playerid][factionBrankasTemp] = EOS;
                    FactionBrankas[playerid][factionBrankasModel] = 0;
                    FactionBrankas[playerid][factionBrankasQuant] = 0;

                    new str[1218], amounts, itemname[64], tss[125];
                    format(str, sizeof(str), "Nama Item\tJumlah\tBerat (-/-)\n");
                    mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
                    mysql_query(g_SQL, tss);
                    new rows = cache_num_rows();
                    if(rows) 
                    {
                        for(new x; x < rows; ++x)
                        {
                            cache_get_value_name(x, "invItem", itemname);
                            cache_get_value_name_int(x, "invQuantity", amounts);

                            format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                        }
                        ShowPlayerDialog(playerid, DIALOG_PEMERVAULT_DEPOSIT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas Pemerintah", str, "Pilih", "Batal");
                    }
                    else 
                    {
                        AccountData[playerid][menuShowed] = false;
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas Pemerintah",
                        "Anda tidak memiliki barang untuk disimpan!", "Tutup", "");
                    }
                }
                case 1: //withdraw
                {
                    new str[4036], amounts, itemname[64];
                    format(str, sizeof(str), "Nama Item\tJumlah\tBerat (-/-)\n");
                    mysql_query(g_SQL, "SELECT * FROM `pemerintah_brankas` WHERE `PID`=0");
                    if(cache_num_rows() > 0)
                    {
                        for(new x; x < cache_num_rows(); ++x)
                        {
                            cache_get_value_name(x, "Item", itemname);
                            cache_get_value_name_int(x, "Quantity", amounts);

                            format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                        }
                        ShowPlayerDialog(playerid, DIALOG_PEMERVAULT_WITHDRAW, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas Pemerintah", str, "Pilih", "Batal");
                    }
                    else 
                    {
                        AccountData[playerid][menuShowed] = false;
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas Pemerintah",
                        "Tidak ada barang di brankas saat ini!", "Tutup", "");
                    }
                }
            }
        }
        case DIALOG_PEMERVAULT_DEPOSIT:
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

            new tss[128];
            mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
            mysql_query(g_SQL, tss);
            if(cache_num_rows() > 0)
            {
                cache_get_value_name(listitem, "invItem", FactionBrankas[playerid][factionBrankasTemp]);
                cache_get_value_name_int(listitem, "invModel", FactionBrankas[playerid][factionBrankasModel]);
                cache_get_value_name_int(listitem, "invQuantity", FactionBrankas[playerid][factionBrankasQuant]);

                new shstr[528];
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_PEMERVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pemerintah",
                shstr, "Input", "Batal");
            }
        }
        case DIALOG_PEMERVAULT_IN:
        {
            if(!response)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            }

            new shstr[512];
            if(isnull(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nTidak dapat diisi kosong!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_PEMERVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pemerintah",
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_PEMERVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pemerintah",
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[playerid][factionBrankasQuant])
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_PEMERVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pemerintah",
                shstr, "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);
            Inventory_Remove(playerid, FactionBrankas[playerid][factionBrankasTemp], quantity);
            ShowItemBox(playerid, sprintf("Removed %dx", quantity), FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel]);

            new invstr[1028];
            mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `pemerintah_brankas` WHERE `PID`=0 AND `Item` = '%s'", FactionBrankas[playerid][factionBrankasTemp]);
            mysql_query(g_SQL, shstr);
            new rows = cache_num_rows();
            if(rows > 0)
            {
                mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `pemerintah_brankas` SET `Quantity` = `Quantity` + %d WHERE `PID` = 0 AND `Item`='%s'", quantity, FactionBrankas[playerid][factionBrankasTemp]);
                mysql_tquery(g_SQL, invstr, "OnPemerintahDeposit", "i", playerid);
            }
            else 
            {
                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `pemerintah_brankas` SET `PID`=0, `Item`='%s', `Model`=%d, `Quantity`=%d", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel], quantity);
                mysql_tquery(g_SQL, invstr, "OnPemerintahDeposit", "i", playerid);
            }
            AccountData[playerid][menuShowed] = false;
        }
        case DIALOG_PEMERVAULT_WITHDRAW:
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

            new shstr[1218];
            mysql_query(g_SQL, "SELECT * FROM `pemerintah_brankas` WHERE `PID`=0");
            if(cache_num_rows() > 0)
            {
                cache_get_value_name_int(listitem, "ID", FactionBrankas[playerid][factionBrankasID]);
                cache_get_value_name(listitem, "Item", FactionBrankas[playerid][factionBrankasTemp]);
                cache_get_value_name_int(listitem, "Model", FactionBrankas[playerid][factionBrankasModel]);
                cache_get_value_name_int(listitem, "Quantity", FactionBrankas[playerid][factionBrankasQuant]);

                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_PEMERVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pemerintah",
                shstr, "Input", "Batal");
            }
            else 
            {
                AccountData[playerid][menuShowed] = false;
                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas Pemerintah",
                "Brankas ini isinya kosong!", "Tutup", "");
            }
        }
        case DIALOG_PEMERVAULT_OUT:
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
                ShowPlayerDialog(playerid, DIALOG_PEMERVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pemerintah",
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_PEMERVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pemerintah",
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[playerid][factionBrankasQuant])
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_PEMERVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pemerintah",
                shstr, "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext), jts[150];

            if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!"), AccountData[playerid][menuShowed] = false;

            FactionBrankas[playerid][factionBrankasQuant] -= quantity;
            if(FactionBrankas[playerid][factionBrankasQuant] > 0)
            {
                mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `pemerintah_brankas` SET `Quantity`=%d WHERE `ID`=%d", FactionBrankas[playerid][factionBrankasQuant], FactionBrankas[playerid][factionBrankasID]);
                mysql_tquery(g_SQL, jts);
            }
            else 
            {
                mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `pemerintah_brankas` WHERE `ID`=%d", FactionBrankas[playerid][factionBrankasID]);
                mysql_tquery(g_SQL, jts);
            }
            Inventory_Add(playerid, FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel], quantity);
            ShowItemBox(playerid, sprintf("Received %dx", quantity), FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel]);
        
            FactionBrankas[playerid][factionBrankasID] = 0;
            FactionBrankas[playerid][factionBrankasTemp] = EOS;
            FactionBrankas[playerid][factionBrankasModel] = 0;
            FactionBrankas[playerid][factionBrankasQuant] = 0;
            AccountData[playerid][menuShowed] = false;
        }
        case DIALOG_PEMERINTAH_BOSDESK:
        {
            if(!response) return 0;
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Daerah Kota District !");
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

                    ShowPlayerDialog(playerid, DIALOG_PEMERINTAH_INVITE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Invite", frmxt, "Pilih", "Batal");
                }
                case 1:// Kelola Jabatan Offline / Online
                {
                    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 2 ORDER BY Char_FactionRank DESC");

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

                            format(shstr, sizeof(shstr), "%s%s\t%s\t%s\n", shstr, fckname, PemerintahRank[fckrank], fcklastlogin);
                        }
                        ShowPlayerDialog(playerid, DIALOG_PEMERSETRANK, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Set Jabatan", shstr, "Pilih", "Batal");
                    }
                    else 
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Set Jabatan", "Tidak ada Anggota Pemerintah!", "Tutup", "");
                    }
                }
                case 2:// kick offline / online
                {
                    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 2 ORDER BY Char_FactionRank DESC");

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

                            format(shstr, sizeof(shstr), "%s%s\t%s\t%s\n", shstr, fckname, PemerintahRank[fckrank], fcklastlogin);
                        }
                        ShowPlayerDialog(playerid, DIALOG_PEMERKICKMEMBER, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Kick Anggota", shstr, "Pilih", "Batal");
                    }
                    else 
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota", "Tidak ada Anggota Pemerintahan!", "Tutup", "");
                    }
                }
                case 3:// Cek anggota Duty
                {
                    new duty[128], lstr[1024];
                    format(lstr, sizeof lstr, "Nama\tRank\tStatus Duty\n");
                    foreach(new i : Player) {
                        if(AccountData[i][pFaction] == FACTION_PEMERINTAH) {
                            switch(AccountData[i][pDutyPemerintah])
                            {
                                case 0:
                                {
                                    duty = ""ORANGE"Off Duty";
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
                case 4: // cek Keuangan
                {
                    new frmxt[158];
                    format(frmxt, sizeof(frmxt), "Pemerintahan Daerah District  saat ini memiliki saldo sebesar:\ 
                    \n"DARKGREEN"%s", FormatMoney(PemerintahMoneyVault));
                    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Pemerintah Money", frmxt, "Tutup", "");
                }
                case 5:// Deposit Uang
                {
                    ShowPlayerDialog(playerid, DIALOG_PEMERINTAH_DEPOSIT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Pemerintah Deposit",
                    "Mohon masukkan nominal deposit untuk saldo finansial:", "Input", "Batal");
                }
                case 6: // Tarik Uang
                {
                    ShowPlayerDialog(playerid, DIALOG_PEMERINTAH_WITHDRAW, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Pemerintah Withdraw",
                    "Mohon masukkan nominal penarikan tunai dari saldo finansial:", "Input", "Batal");
                }
            }
        }
        case DIALOG_PEMERINTAH_DEPOSIT:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pemerintah District !");
            if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Gubernur untuk akses desk!");
            new depocash = strval(inputtext), frmtmny[128];
            if(depocash > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak sebanyak itu!");
            if(depocash < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukan nominal kurang dari $1 untuk deposit!");
            TakeMoney(playerid, depocash);
            PemerintahMoneyVault += depocash;
            mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `pemerintahmoneyvault` = %d WHERE `ID` = 0", PemerintahMoneyVault);
            mysql_tquery(g_SQL, frmtmny);
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil deposit %s ke Pemerintah District ", FormatMoney(depocash)));
        } 
        case DIALOG_PEMERINTAH_WITHDRAW:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pemerintah District !");
            if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Gubernur untuk akses desk!");
            new withdrawcash = strval(inputtext), frmtmny[128];
            if(withdrawcash > PemerintahMoneyVault) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang perusahaan tidak sebanyak itu!");
            if(withdrawcash < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukan nominal kurang dari $1 untuk withdraw!");
            PemerintahMoneyVault -= withdrawcash;
            GiveMoney(playerid, withdrawcash);

            mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `pemerintahmoneyvault` = %d WHERE `ID` = 0", PemerintahMoneyVault);
            mysql_tquery(g_SQL, frmtmny);

            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], withdrawcash, "Pemerintah");

            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil withdraw %s dari Pemerintah District ", FormatMoney(withdrawcash)));
        }
        case DIALOG_PEMERINTAH_INVITE:
        {
            if(!response) return 0;
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Daerah Kota District !");
            if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Gubernur untuk akses bos desk!");

            new targetid = NearestPlayer[playerid][listitem];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            AccountData[targetid][pFaction] = FACTION_PEMERINTAH;
            AccountData[targetid][pFactionRank] = 1;
            RefreshFactionMap(targetid);
            mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction` = 2, `Char_FactionRank` = 1 WHERE `pID` = %d", AccountData[targetid][pID]);
            mysql_tquery(g_SQL, icsr);
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil invite faction %s", AccountData[targetid][pName]));
        }
        case DIALOG_PEMERKICKMEMBER:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pemerintah District !");
            if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Gubernur untuk mengakses Bos Desk!");

            mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 2 ORDER BY `Char_FactionRank` DESC");
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
                mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_OwnerID`=%d AND `PVeh_Faction` = 2", pidrow);
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
                                if(PlayerVehicle[pvid][pVehFaction] == FACTION_PEMERINTAH)
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
                        if(AccountData[i][pDutyPemerintah])
                            AccountData[i][pDutyPemerintah] = false;
                        if(AccountData[i][pUsingUniform])
                            AccountData[i][pUsingUniform] = false;
                        SetPlayerSkin(i, AccountData[i][pSkin]);
                        RefreshFactionMap(i);
                        ShowTDN(i, NOTIFICATION_WARNING, "Anda telah dikeluarkan dari faction Pemerintah District !");
                    }
                }
                mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`=0, `Char_FactionRank`=0, `Char_UsingUniform`=0 WHERE `pID`=%d", pidrow);
                mysql_tquery(g_SQL, icsr);
                format(kckstr, sizeof(kckstr), "Anda telah berhasil menendang anggota:\n \
                Nama: %s\n\
                Rank: %s\n\
                Last Online: %s", fckname, PemerintahRank[fckrank], fcklastlogin);
                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota",
                kckstr, "Tutup", "");

                AccountData[playerid][pTempSQLFactMemberID] = -1;
                AccountData[playerid][pTempSQLFactRank] = 0;
            }
        }
        case DIALOG_PEMERSETRANK:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pemerintah District !");
            if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Gubernur untuk mengakses Bos Desk!");

            mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 2 ORDER BY `Char_FactionRank` DESC");
            new rows = cache_num_rows();
            if(rows)
            {
                cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
                cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
                if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak dapat mengatur jabatan sendiri!");
                if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengatur jabatan rank diatasmu!");
                ShowPlayerDialog(playerid, DIALOG_RANK_SET_PEMERINTAH, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
                "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
                1. Magang\n\
                2. Staff\n\
                3. Staff Senior\n\
                4. Wakil Divisi\n\
                5. Kepala Divisi\n\
                6. Sekda\n\
                7. Wakil Gubernur\n\
                8. Gubernur", "Set", "Batal");
            }
        }
        case DIALOG_PERPANJANG_HOUSE:
        {
            if(!response)
            {
                RemovePlayerAttachedObject(playerid, 9);
                ClearAnimations(playerid, true);
                StopLoopingAnim(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            }
            
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pemerintah District !");
            if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal Rank Wakil Gubernur untuk akses Bos Desk!");
            new idx = listitem;
            new hid = PlayerHouseList[playerid][idx];
            if(hid == -1) return 1; 

            new price;
            switch(HouseData[hid][hsType])
            {
                case 1: price = 2000;  // Standart (Dollar Menengah)
                case 2: price = 4000;  // Medium
                case 3: price = 6000;  // Modern
                case 4, 99: price = 8000; // Mansion
                default: price = 2000;
            }
            if(AccountData[playerid][pMoney] < price)
            {
                RemovePlayerAttachedObject(playerid, 9);
                ClearAnimations(playerid, true);
                StopLoopingAnim(playerid);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Uangmu tidak cukup untuk membayar pajak rumah ini!");
            }
            HouseData[hid][hVisit] = gettime() + (86400 * 14);
            HouseRefresh(hid);
            HouseSave(hid);
            TakeMoney(playerid, price);
            PemerintahMoneyVault += (price / 100) * 20;
            new icsr[200];
            mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE stuffs SET pemerintahmoneyvault=%d WHERE ID=0", PemerintahMoneyVault);
            mysql_tquery(g_SQL, icsr);
            Info(playerid, "Pajak rumah ID "YELLOW"%d "WHITE"berhasil diperpanjang selama 14 hari. Harga: $"GREEN_E"%d", hid, price);

            new ownerid = HouseData[hid][hsOwnerID];
            if(IsPlayerConnected(ownerid))
            {
                Info(playerid, "Rumahmu (ID "YELLOW"%d) "WHITE"telah diperpanjang pajaknya oleh pemerintah selama "YELLOW"14 hari.", hid);
            }
            ClearAnimations(playerid, true);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        }
        case DIALOG_RANK_SET_PEMERINTAH:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pemerintah District !");
            if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal Rank Wakil Gubernur untuk akses Bos Desk!");

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_PEMERINTAH, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Error: Tidak dapat diisi kosong!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Magang\n\
            2. Staff\n\
            3. Staff Senior\n\
            4. Wakil Divisi\n\
            5. Kepala Divisi\n\
            6. Sekda\n\
            7. Wakil Gubernur\n\
            8. Gubernur", "Set", "Batal");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_PEMERINTAH, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Error: Hanya dapat diisi angka!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Magang\n\
            2. Staff\n\
            3. Staff Senior\n\
            4. Wakil Divisi\n\
            5. Kepala Divisi\n\
            6. Sekda\n\
            7. Wakil Gubernur\n\
            8. Gubernur", "Set", "Batal");

            if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pFactionRank]) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_PEMERINTAH, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Magang\n\
            2. Staff\n\
            3. Staff Senior\n\
            4. Wakil Divisi\n\
            5. Kepala Divisi\n\
            6. Sekda\n\
            7. Wakil Gubernur\n\
            8. Gubernur", "Set", "Batal");

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
            return 1;
        }
        case DIALOG_PEMERINTAH_PANEL:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota District !");
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
                case 3:// Seret
                {
                    CarryPlayerNearest(playerid, targetid);
                }
                case 4:
                {
                    new oncarry = IsDragging[playerid];
                    TogglePlayerControllable(oncarry, true);
                    AccountData[oncarry][pDraggedBy] = INVALID_PLAYER_ID;
                    IsDragging[playerid] = INVALID_PLAYER_ID;
                    SendRPMeAboveHead(playerid, "Melepaskan seretan", X11_LIGHTGREEN);
                }
                case 5:
                {
                    if(!AccountData[targetid][pCuffed])
                    {
                        AccountData[targetid][pCuffed] = true;
                        SetPlayerSpecialAction(targetid, SPECIAL_ACTION_CUFFED);
                        SendRPMeAboveHead(playerid, "Memborgol orang didepan", X11_PLUM1);
                        ShowTDN(targetid, NOTIFICATION_WARNING, "Anda sedang diborgol");
                    }
                    else ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah diborgol");
                }
                case 6:
                {
                    if(AccountData[targetid][pCuffed])
                    {
                        AccountData[targetid][pCuffed] = 0;
                        SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
                        ClearAnimations(targetid, 1);
                        SendRPMeAboveHead(playerid, "Melepaskan borgol", X11_PLUM1);
                        ShowTDN(targetid, NOTIFICATION_WARNING, "Borgol anda telah dibuka");
                    }
                }
                case 7:// cek blacklist
                {
                    ShowDurringBlacklist(playerid, targetid);
                }
            }
        }
        case DIALOG_PEMERINTAH_LOCKER:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Daerah Kota District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            switch(listitem)
            {
                case 0://
                {
                    SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
                    AccountData[playerid][pUsingUniform] = false;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengganti Pakaian Biasa!");
                }
                case 1:// Switch Pakaian
                {
                    if(AccountData[playerid][pGender] == 1) {
                        ShowPlayerDialog(playerid, DIALOG_PEMERINTAH_LOCKERMALE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Baju Dinas", ""WHITE"Pemerintah 1\n"GRAY"Pemerintah 2\n"WHITE"Pemerintah 3", "Pilih", "Batal");
                    } else {
                        ShowPlayerDialog(playerid, DIALOG_PEMERINTAH_LOCKERFEMALE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Baju Dinas", ""WHITE"Pemerintah 1\n"GRAY"Pemerintah 2", "Pilih", "Batal");
                    }
                }
            }
        }
        case DIALOG_PEMERINTAH_LOCKERMALE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota District !");
            
            switch(listitem)
            {
                case 0: AccountData[playerid][pUniform] = 295;
                case 1: AccountData[playerid][pUniform] = 164;
                case 2: AccountData[playerid][pUniform] = 228;
            }
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
            AccountData[playerid][pUsingUniform] = true;
        }
        case DIALOG_PEMERINTAH_LOCKERFEMALE:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota District !");
            
            switch(listitem)
            {
                case 0: AccountData[playerid][pUniform] = 150;
                case 1: AccountData[playerid][pUniform] = 141;
            }
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
            AccountData[playerid][pUsingUniform] = true;
        }
    }
    return 1;
}

// Command
CMD:ubahnamaktp(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota pemerintah!");
    new otherid, tmp[24];
    if(sscanf(params, "us[24]", otherid, tmp)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/ubahnamaktp [name/playerid] [nama baru]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(otherid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menggunakan kepada diri sendiri!");
    if(AccountData[otherid][pFaction] == FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat Abusing!");
    if(strlen(tmp) < 1 || strlen(tmp) > 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat memasukkan kurang dari 1 characters atau lebih dari 24 characters!");
    if(!IsValidName(tmp)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Format nama tidak valid!");

    new query[255];
    mysql_format(g_SQL, query, sizeof(query), "SELECT `Char_Name` FROM `player_characters` WHERE `Char_Name`='%s'", tmp);
    mysql_tquery(g_SQL, query, "OnChangeKtpName", "iis", otherid, playerid, tmp);
    return 1;
}
/* Change Name Callback */
forward OnChangeKtpName(otherPlayer, playerid, const name[]);
public OnChangeKtpName(otherPlayer, playerid, const name[])
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

		if(AccountData[playerid][pFamilyRank] == 6)
		{
			mysql_format(g_SQL, query, sizeof(query), "UPDATE `families` SET `F_Leader`='%s' WHERE `F_Leader`='%s'", name, oldname);
			mysql_tquery(g_SQL, query);
		}

		if(AccountData[playerid][PurchasedToy])
		{
			mysql_format(g_SQL, query, sizeof(query), "UPDATE `toys` SET `Owner`='%s' WHERE `Owner`='%s'", name, oldname);
			mysql_tquery(g_SQL, query);
		}
        
        SendClientMessageEx(otherPlayer, X11_SKYBLUE1, "[PEMERINTAH]:"WHITE" Berhasil melakukan pengubahan nama KTP.");
        SendClientMessageEx(otherPlayer, -1, "~> Nama KTP Sebelum: "YELLOW"%s.", oldname);
        SendClientMessageEx(otherPlayer, -1, "~> Nama KTP Sesudah: "YELLOW"%s.", name);
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil melakukan pengubahan nama KTP");

		SetPlayerName(otherPlayer, name);
		GetPlayerName(otherPlayer, newname, sizeof(newname));
		AccountData[otherPlayer][pName] = newname;
	}
	else 
	{
		return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Sudah ada pemain dengan nama %s di database!", name));
	}
	return 1;
}

CMD:makehuntlic(playerid, params[])
{
    if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pemerintahan!");
    if(!AccountData[playerid][pDutyPemerintah]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum On Duty!");

    new otherid;
    if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/makehuntlic [name/playerid]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(AccountData[otherid][pHuntingLic]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah memilik Lisensi Hunting!");

    AccountData[otherid][pHuntingLic] = 1;
    AccountData[otherid][pHuntingLicTime] = gettime() + (30 * 86400); // 30 Hari waktu internasional
    Info(playerid, "Berhasil membuat Lisensi Hunting selama 30 hari!");
    Info(otherid, "Seseorang telah membuatkan anda Lisensi Hunting");
    return 1;
}

CMD:makektp(playerid, params[])
{
    if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pemerintah Kota District !");
    
    new userid;
    if(sscanf(params, "u", userid))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/makektp [name/playerid]");

    if(!IsPlayerConnected(userid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Player tersebut tidak terkoneksi kedalam server!");
    if(!IsPlayerNearPlayer(playerid, userid, 8.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Player tersebut!"); 
    if(AccountData[userid][Ktp] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Player tersebut telah memiliki KTP!");

    AccountData[userid][Ktp] = 1;
    AccountData[userid][pKtpTime] = gettime() + (14 * 86400); // 14 Hari waktu internasional
    GenerateRandomNIK(userid);
    ShowTDN(playerid, NOTIFICATION_INFO, "Pembuatan KTP berhasil dilakukan!");
    ShowTDN(userid, NOTIFICATION_INFO, "Pemerintah telah membuatkan anda KTP!");
    return 1;
}

/*DialogPages:PemerintahSetRank(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pemerintah District !");
    if(AccountData[playerid][pFactionRank] < 7) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Gubernur untuk mengakses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 2 ORDER BY `Char_FactionRank` DESC");
    new rows = cache_num_rows();
    if(rows)
    {
        cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
        cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak dapat mengatur jabatan sendiri!");
        if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengatur jabatan rank diatasmu!");
        ShowPlayerDialog(playerid, DIALOG_RANK_SET_PEMERINTAH, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
        "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
        1. Magang\n\
        2. Staff\n\
        3. Staff Senior\n\
        4. Wakil Divisi\n\
        5. Kepala Divisi\n\
        6. Sekda\n\
        7. Wakil Gubernur\n\
        8. Gubernur", "Set", "Batal");
    }
    return 1;
}

DialogPages:PemerintahKickMember(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pemerintah District !");
    if(AccountData[playerid][pFactionRank] < 7) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil Gubernur untuk mengakses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 2 ORDER BY `Char_FactionRank` DESC");
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
        mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_OwnerID`=%d AND `PVeh_Faction` = 2", pidrow);
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
                        if(PlayerVehicle[pvid][pVehFaction] == FACTION_PEMERINTAH)
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
                if(AccountData[i][pDutyPemerintah])
                    AccountData[i][pDutyPemerintah] = false;
				if(AccountData[i][pUsingUniform])
					AccountData[i][pUsingUniform] = false;
				SetPlayerSkin(i, AccountData[i][pSkin]);
                RefreshFactionMap(i);
                ShowTDN(i, NOTIFICATION_WARNING, "Anda telah dikeluarkan dari faction Pemerintah District !");
            }
        }
        mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`=0, `Char_FactionRank`=0, `Char_UsingUniform`=0 WHERE `pID`=%d", pidrow);
        mysql_tquery(g_SQL, icsr);
        format(kckstr, sizeof(kckstr), "Anda telah berhasil menendang anggota:\n \
        Nama: %s\n\
        Rank: %s\n\
        Last Online: %s", fckname, PemerintahRank[fckrank], fcklastlogin);
        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota",
        kckstr, "Tutup", "");

        AccountData[playerid][pTempSQLFactMemberID] = -1;
        AccountData[playerid][pTempSQLFactRank] = 0;
    }
    return 1;
}*/

forward OnPemerintahDeposit(playerid);
public OnPemerintahDeposit(playerid)
{
    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyimpan item");
    FactionBrankas[playerid][factionBrankasID] = 0;
    FactionBrankas[playerid][factionBrankasTemp] = EOS;
    FactionBrankas[playerid][factionBrankasModel] = 0;
    FactionBrankas[playerid][factionBrankasQuant] = 0;
    return 1;
}


CMD:listgudang(playerid, params[])
{
    if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya anggota pemerintah yang bisa menggunakan ini!");
    
    if (!AccountData[playerid][pDutyPemerintah])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus duty Pemerintah!");

    if(AccountData[playerid][pFaction] == FACTION_PEMERINTAH)
    {
        if(AccountData[playerid][pFactionRank] < 5)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Sekda untuk mengakses ini!");
    }

    new total = Iter_Count(Gudang);
    if(total <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Belum ada gudang tersedia!");

    static list[4096];
    list[0] = '\0';

    new id;
    for(id = 0; id < MAX_DYNAMIC_GUDANG; id++)
    {
        if(!Iter_Contains(Gudang, id)) continue;
        static tmp[256];
        format(tmp, sizeof(tmp), "%d: %s\t"GREEN"%s / bulan\n", id, GudangData[id][gudangName], FormatMoney(GudangData[id][gudangPrice]));
        strcat(list, tmp, sizeof(list));
    }

    AccountData[playerid][pTempValue] = -1; // nanti dipakai untuk simpan id gudang
    ShowPlayerDialog(playerid, DialogGudangList, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- List Gudang",list, "Pilih", "Batal");

    return 1;
}
