#include <YSI\y_hooks>

new pTimerDuringBobol[MAX_PLAYERS] = {-1, ...},
    pTimerAsuransikan[MAX_PLAYERS] = {-1, ...},
    pTimerImpound[MAX_PLAYERS] = {-1, ...},
    pTimerMakePlate[MAX_PLAYERS] = {-1, ...},
    pTimerPeleburan[MAX_PLAYERS] = {-1, ...};

new ListedSapdItem[MAX_PLAYERS][100];
new STREAMER_TAG_OBJECT:FirePeleburan[4];

enum e_policevars
{
    STREAMER_TAG_OBJECT: PoliceConeObjid,
    STREAMER_TAG_OBJECT: PoliceRoadBlockObjid,
    STREAMER_TAG_OBJECT: PoliceRanjauObjid,
    Float:PoliceRanjauPos[3]
};
new PlayerFactionPoliceVars[MAX_PLAYERS][e_policevars];

enum e_policestuff
{
    Float:PoldaGaragePOS[3],
    Float:FederalGaragePOS[3],
    Float:PoldaSpawnPOS[4],
    Float:FederalSpawnPOS[4],

    STREAMER_TAG_AREA:PoldaDuty,
    STREAMER_TAG_AREA:PoldaDesk,
    STREAMER_TAG_AREA:PoldaGun,
    STREAMER_TAG_AREA:PoldaBrankas,
    STREAMER_TAG_AREA:PoldaLocker,
    STREAMER_TAG_AREA:PoldaLockerPD,
    STREAMER_TAG_AREA:PoldaGarage,
    STREAMER_TAG_AREA:PoldaImpound,
    STREAMER_TAG_AREA:PoldaHelipad,
    
    STREAMER_TAG_AREA:FederalGarage,
    STREAMER_TAG_AREA:FederalDuty,
    STREAMER_TAG_AREA:FederalLocker,

    STREAMER_TAG_OBJECT:PoldaObject[11],
}
new PoliceStuff[e_policestuff];
new STREAMER_TAG_OBJECT: PoliceObject[MAX_PLAYERS][12];

new const PolisiRank[16][] = {
    "N/A",
    "BRIPDA",
    "BRIPTU",
    "BRIPKA",
    "AIPDA",
    "AIPTU",
    "IPDA",
    "IPTU",
    "AKP",
    "KOMPOL",
    "AKPB",
    "KOMBES",
    "BRIGJEN",
    "IRJEN",
    "KOMJEN",
    "JENDPOL"
};

VarsDoorPolice()
{
    PoliceStuff[PoldaDuty] = CreateDynamicSphere(659.6660,-1503.6816,20.9643, 2.0, 0, 0, -1);
    PoliceStuff[PoldaDesk] = CreateDynamicSphere(659.1224,-1519.9105,17.4683, 2.0, 0, 0, -1);
    PoliceStuff[PoldaGun] = CreateDynamicSphere(659.5682,-1493.7123,20.9623, 2.0, 0, 0, -1);
    PoliceStuff[PoldaBrankas] = CreateDynamicSphere(660.0930,-1516.5671,20.9643, 2.0, 0, 0, -1);
    PoliceStuff[PoldaLocker] = CreateDynamicSphere(662.8520,-1498.8215,20.9643, 2.0, 0, 0, -1);
    PoliceStuff[PoldaLockerPD] = CreateDynamicSphere(662.5468,-1493.5961,20.9623, 2.0, 0, 0, -1);
    PoliceStuff[PoldaGarage] = CreateDynamicSphere(1490.709350,-1801.254638,13.546895, 2.0, 0, 0, -1);
    PoliceStuff[PoldaImpound] = CreateDynamicSphere(983.5379,2474.1208,10.8549, 2.0, 0, 0, -1);
    PoliceStuff[PoldaHelipad] = CreateDynamicSphere(675.5129,-1509.8757,30.5265, 2.0, 0, 0, -1);
    PoliceStuff[FederalDuty] = CreateDynamicSphere(967.5986,2469.6765,10.9001, 2.0, 0, 0, -1);
    PoliceStuff[FederalLocker] = CreateDynamicSphere(248.4755, 1859.1525, 14.0840, 2.0, 0, 0, -1);
    PoliceStuff[FederalGarage] = CreateDynamicSphere(249.8746, 1828.6891, 17.6406, 2.0, 0, 0, -1);
}

AddedKriminal_History(playerid, otherid, string[])
{
    new query[255];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `criminallogs` (`OwnerID`, `Sender`, `History`, `Time`) VALUES ('%d', '%s', '%s', CURRENT_TIMESTAMP())", AccountData[otherid][pID], AccountData[playerid][pName], string);
    mysql_tquery(g_SQL, query);
    return 1;
}

stock Sapd_GedelahFiture(playerid, targetid)
{
    new 
        amount[MAX_INVENTORY],
        str[512],
        string[256],
        count2 = 0;
    
    format(str, sizeof(str), "Nama Barang\tJumlah\n");
    forex(i, MAX_INVENTORY)
    {
        if(InventoryData[targetid][i][invExists])
        {
            strunpack(string, InventoryData[targetid][i][invItem]);
            amount[i] = InventoryData[targetid][i][invQuantity];

            if(InventoryData[targetid][i][invQuantity] > 0)
            {
                format(str, sizeof(str), "%s %s\t%d\n", str, string, amount[i]);
                ListedSapdItem[playerid][count2 ++] = i;
            }
        }
    }
    if(!count2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki Barang apapun!");
    Dialog_Show(playerid, SapdGeledah, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Geledah", str, "Pilih", "Batal");
    return 1;
}

Dialog:SapdGeledah(playerid, response, listitem, inputtext[])
{
    if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Kota District !");
    if(response)
    {
        new targetid = AccountData[playerid][pTarget];
        AccountData[playerid][pListItemGudang] = ListedSapdItem[playerid][listitem];

        new 
            name[48],
            str[128];
        
        strunpack(name, InventoryData[targetid][listitem][invItem]);
        if(InventoryData[targetid][listitem][invExists])
        {
            format(str, sizeof(str), "Anda akan mengambil barang:\nNama: %s\nJumlah: %d\nMohon masukan jumlah yang ingin anda ambil:", name, InventoryData[targetid][listitem][invQuantity]);
            Dialog_Show(playerid, SapdTakeBarang, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Geledah", str, "Input", "Batal");
        }
    }
    return 1;
}

Dialog:SapdTakeBarang(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new targetid = AccountData[playerid][pTarget];
        if(AccountData[targetid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Pemain tersebut sedang melakukan sesuatu, harap tunggu!");
        if(AccountData[targetid][menuShowed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang ingin menyimpan sesuatu!");

        new 
            itemid = -1,
            string[32];
        
        itemid = AccountData[playerid][pListItemGudang];
        new model = InventoryData[targetid][itemid][invModel];
        strunpack(string, InventoryData[targetid][itemid][invItem]);

        new amount = floatround(strval(inputtext));

        if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Input");
        if(amount > InventoryData[targetid][itemid][invQuantity]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Barang pemain tersebut tidak sebanyak itu");
        if(!strcmp(string, "Radio", true))
        {
            if(ToggleRadio[targetid] || RadioMicOn[targetid])
            {
                ToggleRadio[targetid] = false;
                RadioMicOn[targetid] = false;
                CallRemoteFunction("UpdatePlayerVoiceMicToggle", "dd", targetid, false);
                CallRemoteFunction("UpdatePlayerVoiceRadioToggle", "dd", targetid, false);
                CallRemoteFunction("AssignFreqToFSVoice", "ddd", targetid, true, 0);
                PlayerTextDrawSetString(targetid, ATRP_RadioTD[targetid][7], "0");
            }
        }
        
        Inventory_Add(playerid, string, InventoryData[targetid][itemid][invModel], amount);
        Inventory_Remove(targetid, string, amount);
        
        ShowItemBox(playerid, sprintf("Received %dx", amount), string, model);
        ShowItemBox(targetid, sprintf("Removed %dx", amount), string, model);
        SendRPMeAboveHead(playerid, "Menyita paksa barang orang didepan", X11_PLUM1);
    }
    return 1;
}

IsPeleburanArea(playerid)
{
    if(IsPlayerInRangeOfPoint(playerid, 3.0, 2614.9568, 2831.0708, 13.7874))    
        return 1;
    
    return 0;
}

hook OnPlayerConnect(playerid)
{
    pTimerDuringBobol[playerid] = -1;
    pTimerAsuransikan[playerid] = -1;
    pTimerImpound[playerid] = -1;
    pTimerMakePlate[playerid] = -1;
    pTimerPeleburan[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pTimerDuringBobol[playerid]);
    KillTimer(pTimerAsuransikan[playerid]);
    KillTimer(pTimerImpound[playerid]);
    KillTimer(pTimerMakePlate[playerid]);
    KillTimer(pTimerPeleburan[playerid]);
    pTimerDuringBobol[playerid] = -1;
    pTimerAsuransikan[playerid] = -1;
    pTimerImpound[playerid] = -1;
    pTimerMakePlate[playerid] = -1;
    pTimerPeleburan[playerid] = -1;
    DeletePVar(playerid, "PlayerHaveImpoundVeh");

    if(IsValidDynamicObject(PlayerFactionPoliceVars[playerid][PoliceConeObjid]))
    {
        DestroyDynamicObject(PlayerFactionPoliceVars[playerid][PoliceConeObjid]);
        PlayerFactionPoliceVars[playerid][PoliceConeObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
    }
    if(IsValidDynamicObject(PlayerFactionPoliceVars[playerid][PoliceRoadBlockObjid]))
    {
        DestroyDynamicObject(PlayerFactionPoliceVars[playerid][PoliceRoadBlockObjid]);
        PlayerFactionPoliceVars[playerid][PoliceRoadBlockObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
    }
    if(IsValidDynamicObject(PlayerFactionPoliceVars[playerid][PoliceRanjauObjid]))
    {
        DestroyDynamicObject(PlayerFactionPoliceVars[playerid][PoliceRanjauObjid]);
        PlayerFactionPoliceVars[playerid][PoliceRanjauObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        PlayerFactionPoliceVars[playerid][PoliceRanjauPos][0] = 0.0;
        PlayerFactionPoliceVars[playerid][PoliceRanjauPos][1] = 0.0;
        PlayerFactionPoliceVars[playerid][PoliceRanjauPos][2] = 0.0;
    }
    return 1;
}

hook OnScriptInit()
{
    CreateDynamic3DTextLabel(""YELLOW"[DROP]"WHITE"\nDrop item disini untuk meleburkan", -1, 2614.9568, 2831.0708, 13.7874, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
    VarsDoorPolice();
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pFaction] == FACTION_POLISI)
    {

        if(areaid == PoliceStuff[PoldaHelipad] && AccountData[playerid][pDutyPD])
        {
            ShowKey(playerid, "[Y] Garasi Polisi");
        }

        if(areaid == PoliceStuff[PoldaLocker] && AccountData[playerid][pDutyPD])
        {
            ShowKey(playerid, "[Y] Locker Polisi");
        }
        if(areaid == PoliceStuff[PoldaLockerPD] && AccountData[playerid][pDutyPD])
        {
            ShowKey(playerid, "[Y] Locker Senjata Anggota");
        }

        if(areaid == PoliceStuff[PoldaBrankas] && AccountData[playerid][pDutyPD])
        {
            ShowKey(playerid, "[Y] Penyimpanan Barang Bukti");
        }
        
        if(areaid == PoliceStuff[PoldaGun] && AccountData[playerid][pDutyPD])
        {
            ShowKey(playerid, "[Y] Brankas Senjata");
        }

        if(areaid == PoliceStuff[FederalLocker] && AccountData[playerid][pDutyPD])
        {
            ShowKey(playerid, "[Y] Locker Polisi");
        }

        if(areaid == PoliceStuff[PoldaDesk] && AccountData[playerid][pDutyPD])
        {
            ShowKey(playerid, "[Y] Desk Polisi");
        }

        if(areaid == PoliceStuff[PoldaImpound] && AccountData[playerid][pDutyPD])
        {
            ShowKey(playerid, "[Y] Impound");
        }

        if(areaid == PoliceStuff[PoldaDuty])
        {
            if(!AccountData[playerid][pDutyPD])
            {
                ShowKey(playerid, "[Y] ~g~On Duty");
            }
            else
            {
                ShowKey(playerid, "[Y] ~r~Off Duty");
            }
        }
        
        if(areaid == PoliceStuff[FederalDuty])
        {
            if(!AccountData[playerid][pDutyPD])
            {
                ShowKey(playerid, "[Y] ~g~On Duty");
            }
            else
            {
                ShowKey(playerid, "[Y] ~r~Off Duty");
            }
        }
    }
    else 
    {
        if(areaid == PoliceStuff[PoldaImpound])
        {
            ShowKey(playerid, "[Y] Cek Kendaraanmu");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == PoliceStuff[PoldaGarage])
    {
        HideShortKey(playerid);
    }

    if(areaid == PoliceStuff[PoldaBrankas])
    {
        HideShortKey(playerid);
    }

    if(areaid == PoliceStuff[PoldaHelipad])
    {
        HideShortKey(playerid);
    }

    if(areaid == PoliceStuff[FederalGarage])
    {
        HideShortKey(playerid);
    }

    if(areaid == PoliceStuff[PoldaLocker])
    {
        HideShortKey(playerid);
    }

    if(areaid == PoliceStuff[PoldaLockerPD])
    {
        HideShortKey(playerid);
    }
    
    if(areaid == PoliceStuff[PoldaGun])
    {
        HideShortKey(playerid);
    }

    if(areaid == PoliceStuff[FederalLocker])
    {
        HideShortKey(playerid);
    }

    if(areaid == PoliceStuff[PoldaDesk])
    {
        HideShortKey(playerid);
    }

    if(areaid == PoliceStuff[PoldaImpound])
    {
        HideShortKey(playerid);
    }

    if(areaid == PoliceStuff[PoldaDuty])
    {
        HideShortKey(playerid);
    }
    
    if(areaid == PoliceStuff[FederalDuty])
    {
        HideShortKey(playerid);
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pFaction] == FACTION_POLISI)
        {
            if(IsPlayerInDynamicArea(playerid, PoliceStuff[PoldaDuty]))
            {
                if(AccountData[playerid][pUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih menggunakan pakaian kepolisian!");
                if(!AccountData[playerid][pDutyPD])
                {
                    AccountData[playerid][pDutyPD] = true;
                    SetFactionColor(playerid);
                    AccountData[playerid][pDutyTimer] = SetTimerEx("FactDutyHour", 1000, true, "i", playerid);
                    ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~g~On Duty~w~ Polisi");
                }
                else
                {
                    AccountData[playerid][pDutyPD] = false;
                    SetPlayerColor(playerid, COLOR_WHITE);
                    ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~r~Off Duty~w~ Polisi");
                    //ResetPlayerWeaponsEx(playerid);
                }
                RefreshFactionMap(playerid);
            }

            if(IsPlayerInDynamicArea(playerid, PoliceStuff[FederalDuty]))
            {
                if(!AccountData[playerid][pDutyPD])
                {
                    AccountData[playerid][pDutyPD] = true;
                    AccountData[playerid][pDutyTimer] = SetTimerEx("FactDutyHour", 1000, true, "i", playerid);
                    ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~g~On Duty~w~ Polisi");
                }
                else
                {
                    AccountData[playerid][pDutyPD] = false;
                    ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~r~Off Duty~w~ Polisi");
                }
                RefreshFactionMap(playerid);
            }

            if(IsPlayerInDynamicArea(playerid, PoliceStuff[PoldaImpound]) && AccountData[playerid][pDutyPD])
            {
                ShowPlayerDialog(playerid, DIALOG_POLICE_IMPOUND, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Impound",
                "Masukkan ID Pemain yang ingin dicek kendaraannya", "Submit", "Batal");
                // Dialog_Show(playerid, DialogCekPlayerImpound, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Impound",
                // "Mohon masukkan ID Pemain yang ingin di cek kendaraannya:", "Input", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PoliceStuff[PoldaLocker]) && AccountData[playerid][pDutyPD])
            {
                Dialog_Show(playerid, DialogLockerSapd, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Pakaian",
                "Baju Biasa\
                \n"GRAY"Baju Dinas", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PoliceStuff[PoldaLockerPD]) && AccountData[playerid][pDutyPD])
            {
                ShowLockerDialog(playerid);
            }

            if(IsPlayerInDynamicArea(playerid, PoliceStuff[FederalLocker]) && AccountData[playerid][pDutyPD])
            {
                Dialog_Show(playerid, DialogLockerSapd, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Pakaian",
                "Baju Biasa\
                \n"GRAY"Baju Dinas", "Pilih", "Batal");
            }

           /* if(IsPlayerInRangeOfPoint(playerid, 2.5, 1490.709350,-1801.254638,13.546895) && AccountData[playerid][pDutyPD]) // Polda Garage
            {
                ShowPlayerDialog(playerid, DIALOG_POLICE_GARAGE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Garasi Polda",
                "Keluarkan Kendaraan\n"GRAY"Simpan Kendaraan\nBeli Kendaraan\n"GRAY"Hapus Kendaraan", "Pilih", "Batal");
            }

            if(IsPlayerInRangeOfPoint(playerid, 2.5, 249.8746, 1828.6891, 17.6406) && AccountData[playerid][pDutyPD]) // Federal Garage
            {
                ShowPlayerDialog(playerid, DIALOG_FEDERAL_GARAGE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Garasi Federal",
                "Keluarkan Kendaraan\ 
                \n"GRAY"Simpan Kendaraan\ 
                \nBeli Kendaraan\ 
                \n"GRAY"Hapus Kendaraan", "Pilih", "Batal");
            }*/

            if(IsPlayerInRangeOfPoint(playerid, 2.5, 675.5129,-1509.8757,30.5265) && AccountData[playerid][pDutyPD]) // Helipad
            {
                ShowPlayerDialog(playerid, DIALOG_POLICE_HELI_GARAGE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Garasi Polda",
                "Keluarkan Kendaraan\
                \n"GRAY"Simpan Kendaraan\
                \nBeli Kendaraan\
                \n"GRAY"Hapus Kendaraan", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PoliceStuff[PoldaGun]) && AccountData[playerid][pDutyPD])
            {   
                if(!AccountData[playerid][pUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus ganti pakaian terlebih dahulu!");
                if(AccountData[playerid][pFactionRank] < 12) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank BRIGJEN untuk akses persenjataan");
                Dialog_Show(playerid, BrankasPolice, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Brankas Kepolisian", "Beli Senjata", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PoliceStuff[PoldaDesk]))
            {
                if(AccountData[playerid][pFactionRank] < 14) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOMJEN untuk akses desk!");
                ShowPlayerDialog(playerid, DIALOG_POLICE_BOSDESK, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Bos Desk",
                "Invite\
                \n"GRAY"Kelola Jabatan\
                \nKick\
                \n"GRAY"Saldo Finansial\
                \nDeposit Saldo\
                \n"GRAY"Tarik Saldo", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PoliceStuff[PoldaBrankas]) && AccountData[playerid][pDutyPD])
            {
                if(NearPlayerOpenStorage(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain disekitar sedang membuka brankas!");
                
                AccountData[playerid][menuShowed] = true;
                ShowPlayerDialog(playerid, DIALOG_POLVAULT, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Penyimpanan Barang Bukti",
                "Simpan Barang Bukti\n"GRAY"Ambil Barang Bukti", "Pilih", "Batal");
            }
        }
        else
        {
            if(IsPlayerInDynamicArea(playerid, PoliceStuff[PoldaImpound]))
            {
                ShowPlayerVehicleImpound(playerid, playerid);
            }
        }
    }
    return 1;
}

Dialog:DIALOG_TENTARA_PANEL(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Tentara!");
    new targetid = AccountData[playerid][pTarget];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi kedalam server!");
    if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan player tersebut!");
    if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan, tidak dapat menggunakan Panel!");
    switch(listitem)
    {
        case 0: //revive
        {
            if(!AccountData[targetid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak pingsan!");
            if(!PlayerHasItem(playerid, "Medkit")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki medkit!");
            if(AccountData[playerid][EMSDuringReviving]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang merevive seseorang, tunggu sebentar!");

            Inventory_Remove(playerid, "Medkit");
            SendRPMeAboveHead(playerid, "Menggunakan Medkit", X11_PLUM1);

            ApplyAnimation(playerid, "MEDIC", "CPR", 8.33, 1, 0, 0, 1, 0, 1);

            AccountData[playerid][ActivityTime] = 1;
            AccountData[playerid][EMSDuringReviving] = true;
            pTimerReviving[playerid] = SetTimerEx("EMSReviving", 1000, true, "dd", playerid, targetid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEREVIVE");
            ShowProgressBar(playerid);
        }
        case 1:// Treatment
        {   
            GetPlayerHealth(targetid, AccountData[targetid][pHealth]);
            SetPlayerHealthEx(targetid, 100.0);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Treatment Berhasil!");

            AccountData[targetid][pHead] = 100;
            AccountData[targetid][pPerut] = 100;
            AccountData[targetid][pRHand] = 100;
            AccountData[targetid][pLHand] = 100;
            AccountData[targetid][pRFoot] = 100;
            AccountData[targetid][pLFoot] = 100;
        }
        case 2://seret
        {
            CarryPlayerNearest(playerid, targetid);
        }
        case 3:// uncar
        {
            new oncarry = IsDragging[playerid];
            TogglePlayerControllable(oncarry, true);
            AccountData[oncarry][pDraggedBy] = INVALID_PLAYER_ID;
            IsDragging[playerid] = INVALID_PLAYER_ID;
            SendRPMeAboveHead(playerid, "Melepaskan seretan", X11_LIGHTGREEN);
        }
        case 4:// Borgol
        {
            if(AccountData[targetid][pCuffed])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Player tersebut sudah di borgol!");
            
            AccountData[targetid][pCuffed] = 1;
            SetPlayerSpecialAction(targetid, SPECIAL_ACTION_CUFFED);
            ShowTDN(targetid, NOTIFICATION_WARNING, "Anda telah diborgol!");
        }
        case 5:// lepas borgol
        {
            if(!AccountData[targetid][pCuffed])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Player tersebut belum di borgol!");
            
            AccountData[targetid][pCuffed] = 0;
            ClearAnimations(targetid, 1);
            SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
            ShowTDN(targetid, NOTIFICATION_WARNING, "Borgol anda telah dilepaskan!");
        }
        case 6:// Invouce blm terbayar
        {
            PeriksaInvoice(playerid, targetid);
        }
        case 7:// Periksa kesehatan
        {
            GetBoneStatus(playerid, targetid);
        }
        case 8:// cek blacklist
        {
            ShowDurringBlacklist(playerid, targetid);
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(dialogid == DIALOG_POLICE_PANEL)
    {
        if(!response) return 1;
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari anggota Kepolisian District ");
        new targetid = AccountData[playerid][pTarget];
        if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi kedalam server!");
        if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan player tersebut!");
        if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan, tidak dapat menggunakan Panel!");
        switch(listitem)
        {
            case 0:
            {
                DisplayLicensi(playerid, targetid);
            }
            case 1: // Periksa Invoice 
            {
                PeriksaInvoice(playerid, targetid);
            }
            case 2: // Kartu Identitas
            {
                CekIdentitas(playerid, targetid);
            }
            case 3: // Geledah
            {
                if(IsPlayerPlayingAnimation(targetid, "ROB_BANK", "SHP_HandsUp_Scr") || AccountData[targetid][pInjured])
                {
                    Sapd_GedelahFiture(playerid, targetid);
                    SendRPMeAboveHead(playerid, "Menggeledah orang didepannya", X11_PLUM1);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 3000, 1);
                }
                else return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak mengangkat tangannya!");
            }
            case 4: // Borgol
            {
                AccountData[targetid][pCuffed] = true;
                SetPlayerSpecialAction(targetid, SPECIAL_ACTION_CUFFED);
                SendRPMeAboveHead(playerid, "Memborgol orang didepannya", X11_PLUM1);
                ShowTDN(targetid, NOTIFICATION_WARNING, "Anda Diborgol oleh Petugas");
            }
            case 5: // Lepas Borgol
            {
                if(AccountData[targetid][pCuffed] == 1)
                {
                    AccountData[targetid][pCuffed] = 0;
                    SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
                    SendRPMeAboveHead(playerid, "Melepaskan borgol", X11_PLUM1);
                    ShowTDN(targetid, NOTIFICATION_WARNING, "Borgol anda telah dibuka");
                }
            }
            case 6: // seret
            {
                CarryPlayerNearest(playerid, targetid);
            }
            case 7: // lepas seret
            {
                new oncarry = IsDragging[playerid];
                TogglePlayerControllable(oncarry, true);
                AccountData[oncarry][pDraggedBy] = INVALID_PLAYER_ID;
                IsDragging[playerid] = INVALID_PLAYER_ID;
                SendRPMeAboveHead(playerid, "Melepaskan seretan", X11_LIGHTGREEN);
            }
            case 8: // Masukkan Mobil
            {
                new vehicleid = GetNearestVehicleToPlayer(playerid, 3.0, false);

                if(AccountData[targetid][pCuffed] != 1)	
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Orang itu belum di borgol!.");
                
                if(vehicleid == INVALID_VEHICLE_ID)
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak berada didekat kendaraan apapun!.");
                
                if(GetVehicleMaxSeats(vehicleid) < 2)
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "You can't detain that player in this vehicle.");

                if(!IsPlayerInVehicle(targetid, vehicleid))
                {
                    new seatid = GetAvailableSeat(vehicleid, 2);

                    if(seatid == -1)
                        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada bangku kosong lagi!.");

                    new
                        string[64];

                    format(string, sizeof(string), "Kamu dimasukan paksa kedalam mobil oleh petugas %s.", ReturnName(playerid));
                    ShowTDN(targetid, NOTIFICATION_WARNING, string);
                    TogglePlayerControllable(targetid, 0);

                    PutPlayerInVehicle(targetid, vehicleid, seatid);

                    SendRPMeAboveHead(playerid, "Membuka pintu kendaraan dan memasukan seseorang kedalam mobil", X11_PLUM1);
                }
            }
            case 9: // Keluarkan Paksa
            {
                new vehicleid = GetNearestVehicleToPlayer(playerid, 3.0, false);

                if(IsPlayerInVehicle(targetid, vehicleid))
                {
                    TogglePlayerControllable(targetid, 1);

                    RemoveFromVehicle(targetid);
                    SendRPMeAboveHead(playerid, "Mengeluarkan paksa seseorang dari kendaraan", X11_PLUM1);
                }
            }
            case 10: // Invoice Manual
            {
                GivePlayerInvoice(playerid, targetid);
            }
            case 11:// Penjarakan
            {
                if(!IsPlayerInRangeOfPoint(playerid, 30.0, 296.9771, 1833.0996, 7.7340))
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada didalam penjara federal!");

                Dialog_Show(playerid, Dialog_PenjaraFederal, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Penjarakan", "Masukan jumlah menit yang ingin diberikan:", "Input", "Batal");
            }
            case 12: // bebaskan dari penjara
            {
                if(!AccountData[targetid][pArrest]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dalam masa tahanan!");

                SetPlayerPositionEx(targetid, 313.5431, 1843.3695, 7.7266, 178.6274, 5000);
                SendClientMessageToAllEx(X11_LIGHTGREY, "[Federal] %s telah dibebaskan dari penjara federal", ReturnName(targetid));
                AccountData[targetid][pArrest] = 0;
                AccountData[targetid][pArrestTime] = 0;
            }
            case 13:// Ambil Uang Kotor
            {
                if(AccountData[targetid][pRedMoney] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki uang kotor!");
                
                AccountData[targetid][pRedMoney] = 0;
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengambil semua uang haram");
                ShowTDN(targetid, NOTIFICATION_WARNING, "Petugas mengambil semua uang merahmu!");
            }
            case 14:// Lepaskan Karung
            {
                if(AccountData[targetid][pDurringKarung])
                {
                    HideKarungTD(targetid);
                    AccountData[targetid][pDurringKarung] = false;
                    RemovePlayerAttachedObject(targetid, 9);
                    ShowTDN(targetid, NOTIFICATION_WARNING, "Petugas Kepolisian membuka Karung dikepala anda");
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil melepaskan karung");
                }
            }
            case 15:// cek Blacklist
            {
                ShowDurringBlacklist(playerid, targetid);
            }
            case 16: // Lihat Senjata
            {
                CheckTargetWeapon(playerid, targetid);
            }
            case 17: // Lihat Senjata
            {
                TakeWeaponLooting(playerid, targetid);
            }
            case 18: // Cek Riwayat Kriminal
            {
                new query[200], Cache:executee;
                mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `criminallogs` WHERE `OwnerID`=%d ORDER BY `Time` ASC", AccountData[targetid][pID]);
                executee = mysql_query(g_SQL, query, true);
                if(cache_num_rows())
                {
                    new list[2500], sender[24], string[128], date[64];
                    
                    format(list, sizeof(list), "Tanggal\tPetugas\tCatatan\n");
                    for(new i; i < cache_num_rows(); i ++)
                    {
                        cache_get_value_name(i, "Sender", sender);
                        cache_get_value_name(i, "History", string);
                        cache_get_value_name(i, "Time", date);

                        format(list, sizeof(list), "%s%s\t%s\t%s\n", list, date, sender, string);
                    }
                    new title[100];
                    format(title, sizeof(title), "Catatan Kriminal - %s", AccountData[targetid][pName]);
                    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, title, list, "Tutup", "");
                }
                else
                {
                    new list[208], title[100];
                    format(list, sizeof(list), "Tanggal\tPetugas\tCatatan\n");
                    format(list, sizeof(list), "%sTidak ada Catatan Kriminal yang dapat ditampilkan untuk anda.", list);
                    format(title, sizeof(title), "Catatan Kriminal - %s", AccountData[targetid][pName]);
                    ShowPlayerDialog(targetid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, title, list, "Tutup", "");
                }
                cache_delete(executee);
            }
            case 19: // Buat Catatan Kriminal
            {
                SetPVarInt(playerid, "IDTarget", targetid);
                ShowPlayerDialog(playerid, DIALOG_ADD_HKRIMINAL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Buat Catatan Kriminal",
                "Mohon masukkan deskripsi catatan kriminal yang akan diberikan kepada orang tersebut dibawah ini:", "Buat", "Batal");
            }
            case 20: // Hapus Catatan Kriminal
            {
                SetPVarInt(playerid, "IDTarget", targetid);
                ShowPlayerDialog(playerid, DIALOG_REMOVE_HKRIMINAL, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Catatan Kriminal",
                "Apakah anda yakin ingin menghapus semua catatan kriminal yang dimilikinya?", "Iya", "Tidak");
            }
        }
    }
    else if(dialogid == DIALOG_REMOVE_HKRIMINAL)
    {
        if(!response)
        {
            DeletePVar(playerid, "IDTarget");
            return 1;
        }

        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian District !");
        if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        new targetid = GetPVarInt(playerid, "IDTarget");
        if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
        if(!IsPlayerNearPlayer(playerid, targetid, 4.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak di dekat anda!");
        
        new query[200];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `criminallogs` WHERE `OwnerID` = %d", AccountData[targetid][pID]);
        mysql_tquery(g_SQL, query);

        ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil menghapus semua Catatan Kriminal milik %s", ReturnName(targetid)));
        ShowTDN(targetid, NOTIFICATION_INFO, "Semua catatan kriminal anda telah berhasil di hapus");
        DeletePVar(playerid, "IDTarget");
    }
    else if(dialogid == DIALOG_ADD_HKRIMINAL)
    {
        if(!response)
        {
            DeletePVar(playerid, "IDTarget");
            return 1;
        }

        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian District !");
        if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        new targetid = GetPVarInt(playerid, "IDTarget");
        if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
        if(!IsPlayerNearPlayer(playerid, targetid, 4.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak di dekat anda!");

        if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_ADD_HKRIMINAL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Buat Catatan Kriminal",
        "Error: Tidak dapat diisi kosong!\nMohon masukkan deskripsi catatan kriminal yang akan diberikan kepada orang tersebut dibawah ini:", "Buat", "Batal");

        if(IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_ADD_HKRIMINAL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Buat Catatan Kriminal",
        "Error: Tidak dapat diisi angka!\nMohon masukkan deskripsi catatan kriminal yang akan diberikan kepada orang tersebut dibawah ini:", "Buat", "Batal");

        if(strlen(inputtext) > 128) return ShowPlayerDialog(playerid, DIALOG_ADD_HKRIMINAL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Buat Catatan Kriminal",
        "Error: Tidak dapat lebih dari 128 characters!\nMohon masukkan deskripsi catatan kriminal yang akan diberikan kepada orang tersebut dibawah ini:", "Buat", "Batal");

        AddedKriminal_History(playerid, targetid, inputtext);
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membuat catatan kriminal");
        ShowTDN(targetid, NOTIFICATION_INFO, "Anda telah menerima catatan kriminal");
        DeletePVar(playerid, "IDTarget");
    }
    else if(dialogid == DIALOG_POLICE_BOSDESK)
    {
        if(!response) return 1;
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian District !");
        if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        switch(listitem)
        {
            case 0:// Invite
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
                    "Tidak ada orang di sekitar anda!", "Tutup", "");
                }

                ShowPlayerDialog(playerid, DIALOG_POLICE_INVITE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Invite", frmxt, "Pilih", "Batal");
            }
            case 1:// Kelola Jabatan:
            {
                new dbquery[258];
                mysql_format(g_SQL, dbquery, sizeof(dbquery), "SELECT * FROM `player_characters` WHERE `Char_Faction` = 1 ORDER BY `Char_FactionRank` DESC");
                mysql_query(g_SQL, dbquery);

                new rows = cache_num_rows();
                if(rows)
                {
                    new fckname[64], fckrank, fcklastlogin[30], shstr[4046];

                    format(shstr, sizeof(shstr), "Nama\tRank\tLast Online\n");
                    for(new i; i < rows; ++i)
                    {
                        cache_get_value_name(i, "Char_Name", fckname);
                        cache_get_value_name_int(i, "Char_FactionRank", fckrank);
                        cache_get_value_name(i, "Char_LastLogin", fcklastlogin);

                        format(shstr, sizeof(shstr), "%s%s\t%s\t%s\n", shstr, fckname, PolisiRank[fckrank], fcklastlogin);
                    }
                    ShowPlayerDialog(playerid, DIALOG_POLICESETRANK, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Set Jabatan", shstr, "Pilih", "Batal");
                    // ShowPlayerDialogPages(playerid, "PolisiSetRank", DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Set Jabatan", "Pilih", "Batal", 15, ""GREEN">> Lanjut", ""ORANGE"<< Kembali");
                }
                else 
                {
                    PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Set Jabatan", "Tidak ada Anggota Polisi!", "Tutup", "");
                }
            }
            case 2://
            {
                mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 1 ORDER BY Char_FactionRank DESC");

                new rows = cache_num_rows();
                if(rows)
                {
                    new fckname[64], fckrank, fcklastlogin[30], shstr[4046];

                    format(shstr, sizeof(shstr), "Nama\tRank\tLast Online\n");
                    for(new i; i < rows; ++i)
                    {
                        cache_get_value_name(i, "Char_Name", fckname);
                        cache_get_value_name_int(i, "Char_FactionRank", fckrank);
                        cache_get_value_name(i, "Char_LastLogin", fcklastlogin);

                        format(shstr, sizeof(shstr), "%s%s\t%s\t%s\n", shstr, fckname, PolisiRank[fckrank], fcklastlogin);
                    }
                    ShowPlayerDialog(playerid, DIALOG_POLICEKICKMEMBER, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Set Jabatan", shstr, "Kick", "Batal");
                    // ShowPlayerDialogPages(playerid, "PolisiKickMember", DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Set Jabatan", "Kick", "Batal", 15, ""GREEN">> Lanjut", ""ORANGE"<< Kembali");
                }
                else 
                {
                    PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Set Jabatan", "Tidak ada Anggota Kepolisian!", "Tutup", "");
                }
            }
            case 3:// Saldo Finansial
            {
                new frmxt[255];
                format(frmxt, sizeof(frmxt), "Perusahaan Kepolisian District  saat ini memiliki saldo sebesar:\
                \n"DARKGREEN"%s", FormatMoney(PoliceMoneyVault));
                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Police Money", frmxt, "Tutup", "");
            }
            case 4:// Depo Saldo 
            {
                ShowPlayerDialog(playerid, DIALOG_DEPOSIT_POLICE, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Polisi Deposit",
                "Mohon masukkan nominal deposit untuk saldo perusahaan:", "Input", "Batal");
            }
            case 5:// Withdraw Saldo
            {
                ShowPlayerDialog(playerid, DIALOG_WITHDRAW_POLICE, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Polisi Withdraw",
                "Mohon masukkan nominal penarikan tunai dari saldo perusahaan:", "Input", "Batal");
            }
        }
    }
    else if(dialogid == DIALOG_POLICE_INVITE)
    {
        static icsr[855];
        if(!response) return 1;
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Kepolisian!");
        if(AccountData[playerid][pFactionRank] < 14) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOMJEN untuk akses bos desk!");

        new targetid = NearestPlayer[playerid][listitem];
        if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
        AccountData[targetid][pFaction] = FACTION_POLISI;
        AccountData[targetid][pFactionRank] = 1;
        RefreshFactionMap(targetid);
        mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction` = 1, `Char_FactionRank` = 1 WHERE `pID` = %d", AccountData[targetid][pID]);
        mysql_tquery(g_SQL, icsr);
        ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil invite faction %s", AccountData[targetid][pName]));
    }
    else if(dialogid == DIALOG_POLICESETRANK)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Polda District !");
        if(AccountData[playerid][pFactionRank] < 14) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOMJEN untuk mengakses Bos Desk!");

        mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 1 ORDER BY `Char_FactionRank` DESC");
        new rows = cache_num_rows();
        if(rows)
        {
            cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
            cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
            if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak dapat mengatur jabatan sendiri!");
            if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengatur jabatan rank diatasmu!");
            ShowPlayerDialog(playerid, DIALOG_RANK_SET_POLISI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. BRIPDA\n\
            2. BRIPTU\n\
            3. BRIPKA\n\
            4. AIPDA\n\
            5. AIPTU\n\
            6. IPDA\n\
            7. IPTU\n\
            8. AKP\n\
            9. KOMPOL\n\
            10. AKPB\n\
            11. KOMBES\n\
            12. BRIGJEN\n\
            13. IRJEN\n\
            14. KOMJEN\n\
            15. JENDPOL", "Set", "Batal");
        }
    }
    else if(dialogid == DIALOG_POLICEKICKMEMBER)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Polda District !");
        if(AccountData[playerid][pFactionRank] < 14) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOMJEN untuk mengakses Bos Desk!");

        mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 1 ORDER BY `Char_FactionRank` DESC");
        if(cache_num_rows())
        {
            new pidrow, fckname[64], fckrank, fcklastlogin[30], kckstr[225], icsr[128];

            cache_get_value_name_int(listitem, "pID", pidrow);
            cache_get_value_name(listitem, "Char_Name", fckname);
            cache_get_value_name_int(listitem, "Char_FactionRank", fckrank);
            cache_get_value_name(listitem, "Char_LastLogin", fcklastlogin);

            if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat kick diri sendiri!");
            if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat kick pangkat diatasmu!");

            /* kendaraan pribadi yg milik faction di cek*/
            new strgbg[158];
            mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_OwnerID`=%d AND `PVeh_Faction` = 1", pidrow);
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
                            if(PlayerVehicle[pvid][pVehFaction] == FACTION_POLISI)
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
                    if(AccountData[i][pDutyPD])
                        AccountData[i][pDutyPD] = false;
                    if(AccountData[i][pUsingUniform])
                        AccountData[i][pUsingUniform] = false;
                    SetPlayerSkin(i, AccountData[i][pSkin]);
                    RefreshFactionMap(i);
                    ShowTDN(i, NOTIFICATION_WARNING, "Anda telah dikeluarkan dari faction Kepolisian District !");
                }
            }
            mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`=0, `Char_FactionRank`=0, `Char_UsingUniform`=0 WHERE `pID`=%d", pidrow);
            mysql_tquery(g_SQL, icsr);
            format(kckstr, sizeof(kckstr), "Anda telah berhasil menendang anggota:\n\
            Nama: %s\n\
            Rank: %s\n\
            Last Online: %s", fckname, PolisiRank[fckrank], fcklastlogin);
            ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota",
            kckstr, "Tutup", "");

            AccountData[playerid][pTempSQLFactMemberID] = -1;
            AccountData[playerid][pTempSQLFactRank] = 0;
        }
    }
    else if(dialogid == DIALOG_RANK_SET_POLISI)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Polda District !");
        if(AccountData[playerid][pFactionRank] < 14) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal Rank KOMJEN untuk akses Bos Desk!");

        if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_POLISI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
        "Error: Tidak dapat diisi kosong!\
        \nSilahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\
        \n1. BRIPDA\
        \n2. BRIPTU\
        \n3. BRIPKA\
        \n4. AIPDA\
        \n5. AIPTU\
        \n6. IPDA\
        \n7. IPTU\
        \n8. AKP\
        \n9. KOMPOL\
        \n10. AKPB\
        \n11. KOMBES\
        \n12. BRIGJEN\
        \n13. IRJEN\
        \n14. KOMJEN\
        \n15. JENDPOL", "Set", "Batal");

        if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_POLISI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
        "Error: Hanya dapat diisi angka!\
        \nSilahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\
        \n1. BRIPDA\
        \n2. BRIPTU\
        \n3. BRIPKA\
        \n4. AIPDA\
        \n5. AIPTU\
        \n6. IPDA\
        \n7. IPTU\
        \n8. AKP\
        \n9. KOMPOL\
        \n10. AKPB\
        \n11. KOMBES\
        \n12. BRIGJEN\
        \n13. IRJEN\
        \n14. KOMJEN\
        \n15. JENDPOL", "Set", "Batal");

        if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pFactionRank]) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_POLISI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
        "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\
        \nSilahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\
        \n1. BRIPDA\
        \n2. BRIPTU\
        \n3. BRIPKA\
        \n4. AIPDA\
        \n5. AIPTU\
        \n6. IPDA\
        \n7. IPTU\
        \n8. AKP\
        \n9. KOMPOL\
        \n10. AKPB\
        \n11. KOMBES\
        \n12. BRIGJEN\
        \n13. IRJEN\
        \n14. KOMJEN\
        \n15. JENDPOL", "Set", "Batal");

        new affah[200];
        mysql_format(g_SQL, affah, sizeof(affah), "UPDATE `player_characters` SET `Char_FactionRank`=%d WHERE `pID`=%d", strval(inputtext), AccountData[playerid][pTempSQLFactMemberID]);
        mysql_tquery(g_SQL, affah);

        foreach(new i : Player)
        {
            if(IsPlayerConnected(i) && AccountData[i][IsLoggedIn] && AccountData[playerid][pTempSQLFactMemberID] == AccountData[i][pID])
            {
                AccountData[i][pFactionRank] = strval(inputtext);
                ShowTDN(i, NOTIFICATION_INFO, "Jabatan baru anda di faction telah diubah");
            }
        }
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengubah jabatan faction player tersebut");
    }
    else if(dialogid == DIALOG_DEPOSIT_POLICE)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Kepolisian!");
        if(AccountData[playerid][pFactionRank] < 13) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank IRJEN untuk akses desk!");
        new depocash = strval(inputtext), frmtmny[128];
        if(depocash > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak sebanyak itu!");
        if(depocash < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal kurang dari $1 untuk deposit!");
        TakeMoney(playerid, depocash);
        PoliceMoneyVault += depocash;
        mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `policemoneyvault` = %d WHERE `ID` = 0", PoliceMoneyVault);
        mysql_tquery(g_SQL, frmtmny);
        ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil deposit %s untuk Kepolisian District ", FormatMoney(depocash)));
    }
    else if(dialogid == DIALOG_WITHDRAW_POLICE)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Kepolisian!");
        if(AccountData[playerid][pFactionRank] < 13) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank IRJEN untuk akses desk!");
        new withdrawcash = strval(inputtext), frmtmny[128];
        if(withdrawcash > PoliceMoneyVault) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang perusahaan tidak sebanyak itu!");
        if(withdrawcash < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal kurang dari $1 untuk withdraw!");
        PoliceMoneyVault -= withdrawcash;
        GiveMoney(playerid, withdrawcash);

        mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `policemoneyvault` = %d WHERE `ID` = 0", PoliceMoneyVault);
        mysql_tquery(g_SQL, frmtmny);

        AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], withdrawcash, "Polda");

        ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil withdraw %s dari Kepolisian District ", FormatMoney(withdrawcash)));
    }
    else if(dialogid == DIALOG_POLVAULT)
    {
        if(!response) 
        {
            AccountData[playerid][menuShowed] = false;
            return 1;
        }

        if(AccountData[playerid][pFaction] != FACTION_POLISI) 
        {
            AccountData[playerid][menuShowed] = false;   
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Kepolisian!");
        }
        switch(listitem)
        {
            case 0: //deposit
            {
                FactionBrankas[playerid][factionBrankasID] = 0;
                FactionBrankas[playerid][factionBrankasTemp] = EOS;
                FactionBrankas[playerid][factionBrankasModel] = 0;
                FactionBrankas[playerid][factionBrankasQuant] = 0;

                new str[1218], amounts, itemname[32], tss[125];
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

                        format(str, sizeof(str), "%s"RED"%s\t%d\t-\n", str, itemname, amounts);
                    }
                    ShowPlayerDialog(playerid, DIALOG_POLVAULT_DEPOSIT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Penyimpanan Barang Bukti", str, "Pilih", "Batal");
                }
                else 
                {
                    AccountData[playerid][menuShowed] = false;
                    PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Penyimpanan Barang Bukti",
                    "Anda tidak memiliki item untuk disimpan!", "Tutup", "");
                }
            }
            case 1: //withdraw
            {
                if(AccountData[playerid][pFactionRank] < 14) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOMJEN untuk mengambil Barang di brankas");

                new str[4036], amounts, itemname[64];
                format(str, sizeof(str), "Nama Item\tJumlah\tBerat (-/-)\n");
                mysql_query(g_SQL, "SELECT * FROM `polisi_brankas` WHERE `PID`=0");
                if(cache_num_rows() > 0)
                {
                    for(new x; x < cache_num_rows(); ++x)
                    {
                        cache_get_value_name(x, "Item", itemname);
                        cache_get_value_name_int(x, "Quantity", amounts);

                        format(str, sizeof(str), "%s"RED"%s\t%d\t-\n", str, itemname, amounts);
                    }
                    ShowPlayerDialog(playerid, DIALOG_POLVAULT_WITHDRAW, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Penyimpanan Barang Bukti", str, "Pilih", "Batal");
                }
                else 
                {
                    AccountData[playerid][menuShowed] = false;
                    PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Penyimpanan Barang Bukti",
                    "Tidak ada barang bukti saat ini!", "Tutup", "");
                }
            }
        }
    }
    else if(dialogid == DIALOG_POLVAULT_DEPOSIT)
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

        new tss[128];
        mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
        mysql_query(g_SQL, tss);
        if(cache_num_rows() > 0)
        {
            cache_get_value_name(listitem, "invItem", FactionBrankas[playerid][factionBrankasTemp]);
            cache_get_value_name_int(listitem, "invModel", FactionBrankas[playerid][factionBrankasModel]);
            cache_get_value_name_int(listitem, "invQuantity", FactionBrankas[playerid][factionBrankasQuant]);

            new shstr[528];
            format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: "RED"%s\nJumlah di tas: %d\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_POLVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Penyimpanan Barang Buktii",
            shstr, "Input", "Batal");
        }
    }
    else if(dialogid == DIALOG_POLVAULT_IN)
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
            format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: "RED"%s\nJumlah di tas: %d\nTidak dapat diisi kosong!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_POLVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Penyimpanan Barang Bukti",
            shstr, "Input", "Batal");
            return 1;
        }
        
        if(!IsNumeric(inputtext))
        {
            AccountData[playerid][menuShowed] = true;
            format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: "RED"%s\nJumlah di tas: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_POLVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Penyimpanan Barang Bukti",
            shstr, "Input", "Batal");
            return 1;
        }

        if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[playerid][factionBrankasQuant])
        {
            AccountData[playerid][menuShowed] = true;
            format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: "RED"%s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_POLVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Penyimpanan Barang Bukti",
            shstr, "Input", "Batal");
            return 1;
        }

        new quantity = strval(inputtext);
        Inventory_Remove(playerid, FactionBrankas[playerid][factionBrankasTemp], quantity);
        ShowItemBox(playerid, sprintf("Removed %dx", quantity), FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel]);

        new invstr[1028];
        mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `polisi_brankas` WHERE `PID`=0 AND `Item` = '%s'", FactionBrankas[playerid][factionBrankasTemp]);
        mysql_query(g_SQL, shstr);

        static frmtx[178];
        format(frmtx, sizeof(frmtx), "POLISI - Menyimpan "RED"%s dengan Jumlah %d", FactionBrankas[playerid][factionBrankasTemp], quantity);
        AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], quantity, frmtx);

        new rows = cache_num_rows();
        if(rows > 0)
        {
            mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `polisi_brankas` SET `Quantity` = `Quantity` + %d WHERE `PID`=0 AND `Item`='%s'", quantity, FactionBrankas[playerid][factionBrankasTemp]);
            mysql_tquery(g_SQL, invstr, "OnPolisiDeposit", "i", playerid);
        }
        else 
        {
            mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `polisi_brankas` SET `PID`=0, `Item`='%s', `Model`=%d, `Quantity`=%d", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel], quantity);
            mysql_tquery(g_SQL, invstr, "OnBengkelDeposit", "i", playerid);
        }
        AccountData[playerid][menuShowed] = false;
    }
    else if(dialogid == DIALOG_POLVAULT_WITHDRAW)
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
        mysql_query(g_SQL, "SELECT * FROM `polisi_brankas` WHERE `PID`=0");
        if(cache_num_rows() > 0)
        {
            cache_get_value_name_int(listitem, "ID", FactionBrankas[playerid][factionBrankasID]);
            cache_get_value_name(listitem, "Item", FactionBrankas[playerid][factionBrankasTemp]);
            cache_get_value_name_int(listitem, "Model", FactionBrankas[playerid][factionBrankasModel]);
            cache_get_value_name_int(listitem, "Quantity", FactionBrankas[playerid][factionBrankasQuant]);

            format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_POLVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Penyimpanan Barang Bukti",
            shstr, "Input", "Batal");
        }
        else 
        {
            AccountData[playerid][menuShowed] = false;
            ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Penyimpanan Barang Bukti",
            "Brankas ini isinya kosong!", "Tutup", "");
        }
    }
    else if(dialogid == DIALOG_POLVAULT_OUT)
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
            ShowPlayerDialog(playerid, DIALOG_POLVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Penyimpanan Barang Bukti",
            shstr, "Input", "Batal");
            return 1;
        }

        if(!IsNumeric(inputtext))
        {
            AccountData[playerid][menuShowed] = true;
            format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_POLVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Penyimpanan Barang Bukti",
            shstr, "Input", "Batal");
            return 1;
        }

        if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[playerid][factionBrankasQuant])
        {
            AccountData[playerid][menuShowed] = true;
            format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_POLVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Penyimpanan Barang Bukti",
            shstr, "Input", "Batal");
            return 1;
        }

        new quantity = strval(inputtext), jts[150];

        if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!"), AccountData[playerid][menuShowed] = false;

        FactionBrankas[playerid][factionBrankasQuant] -= quantity;
        if(FactionBrankas[playerid][factionBrankasQuant] > 0)
        {
            mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `polisi_brankas` SET `Quantity`=%d WHERE `ID`=%d", FactionBrankas[playerid][factionBrankasQuant], FactionBrankas[playerid][factionBrankasID]);
            mysql_tquery(g_SQL, jts);
        }
        else 
        {
            mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `polisi_brankas` WHERE `ID`=%d", FactionBrankas[playerid][factionBrankasID]);
            mysql_tquery(g_SQL, jts);
        }
        Inventory_Add(playerid, FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel], quantity);
        ShowItemBox(playerid, sprintf("Received %dx", quantity), FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel]);

        static frmtx[178];
        format(frmtx, sizeof(frmtx), "POLISI - Mengambil %s dengan Jumlah %d", FactionBrankas[playerid][factionBrankasTemp], quantity);
        AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], quantity, frmtx);
    
        FactionBrankas[playerid][factionBrankasID] = 0;
        FactionBrankas[playerid][factionBrankasTemp] = EOS;
        FactionBrankas[playerid][factionBrankasModel] = 0;
        FactionBrankas[playerid][factionBrankasQuant] = 0;
        AccountData[playerid][menuShowed] = false;
    }
    else if(dialogid == DIALOG_POLICE_HELI_GARAGE)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota kepolisian!");
        if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        switch(listitem)
        {
            case 0:// Keluarkan Kendaraan
            {
                if(CountPlayerFactVehInGarage(playerid, 8) < 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun di garasi ini!");

                new id, count = CountPlayerFactVehInGarage(playerid, 8), list[596];
                format(list,sizeof(list),"No\tModel Kendaraan\tNomor Plat\n");
                for(new itt = 0; itt < count; itt++)
                {
                    id = GetVehicleIDStoredFactGarage(playerid, itt, 8);
                    if(itt == count)
                    {
                        format(list, sizeof(list), "%s%d\t%s\t%s", list, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                    } else format(list, sizeof(list), "%s%d\t%s\t%s\n", list, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                }
                ShowPlayerDialog(playerid, DIALOG_POLICE_HELI_GARAGE_OUT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Garasi Polda", list, "Pilih", "Batal");
            }
            case 1:// Simpan Kendaraan
            {
                new carid = -1, bool: foundnearby = false;
                if((carid = Vehicle_Nearest(playerid, 10.0)) != -1)
                {
                    if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
                    if(PlayerVehicle[carid][pVehRental] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat disimpan digarasi Faction!");
                    if(PlayerVehicle[carid][pVehFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan kendaraan Kepolisian!");
                    Vehicle_GetStatus(carid);
                    PlayerVehicle[carid][pVehFactStored] = 8;

                    foundnearby = true;

                    if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]))
                    {
                        DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
                        SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

                        DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
                        PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
                    }
                }
                if(!foundnearby) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan dari Kepolisian District  milik anda di sekitar!");
            }
            case 2:// Beli Kendaraan
            {
                ShowPlayerDialog(playerid, DIALOG_POLICE_HELI_BUY, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Garasi Polda",
                "Model\tHarga\ 
                \nMaverick\t$15000", "Pilih", "Batal");
            }
            case 3:// Hapus Kendaraan
            {
                new frmtdel[151];
                mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 1 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
                mysql_query(g_SQL, frmtdel);

                new rows = cache_num_rows();
                if(rows)
                {
                    new list[522], hkvid, hkvmod;

                    format(list, sizeof(list), "Database ID\tModel\n");
                    for(new i; i < rows; ++i)
                    {
                        cache_get_value_name_int(i, "id", hkvid);
                        cache_get_value_name_int(i, "PVeh_ModelID", hkvmod);

                        format(list, sizeof(list), "%s%d\t%s\n", list, hkvid, GetVehicleModelName(hkvmod));
                    }
                    ShowPlayerDialog(playerid, DIALOG_POLICE_GARAGE_DEL, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Hapus Kendaraan", list, "Hapus", "Batal");
                }
                else 
                {
                    PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Kendaraan", "Anda tidak memiliki kendaraan Polisi!", "Tutup", "");
                }
            }
        }
    }
    else if(dialogid == DIALOG_POLICE_HELI_BUY)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota kepolisian!");
        if(!IsPlayerInDynamicArea(playerid, PoliceStuff[PoldaHelipad])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat Helipad Polda!");

        // new count = 0;
        // foreach(new carid : PvtVehicles)
        // {
        //     if(PlayerVehicle[carid][pVehExists] && PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
        //         count ++;
        // }
        // if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");

        switch(listitem)
        {
            case 0: //maverick
            {
                if(AccountData[playerid][pMoney] < 15000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 15000);
              //  VehicleFaction_Create(playerid, 497, FACTION_POLISI, 1438.036865, -1805.200561, 41.438545, 264.86, 36, 36, 15000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
        }
    }
    else if(dialogid == DIALOG_POLICE_HELI_GARAGE_OUT)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota kepolisian!");
        if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

        new id = GetVehicleIDStoredFactGarage(playerid, listitem, 8);
        if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

        if(!IsPlayerInDynamicArea(playerid, PoliceStuff[PoldaHelipad])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat Helipad Polda!");
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

        PlayerVehicle[id][pVehPos][0] = 675.5129;
        PlayerVehicle[id][pVehPos][1] = -1509.8757;
        PlayerVehicle[id][pVehPos][2] = 30.5265;
        PlayerVehicle[id][pVehPos][3] = 263.4117;

        OnPlayerVehicleRespawn(id);

        SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
    }
    else if(dialogid == DIALOG_POLICE_GARAGE)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota kepolisian!");
        if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        switch(listitem)
        {
            case 0:// Keluarkan Kendaraan
            {
                if(CountPlayerFactVehInGarage(playerid, 9) < 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun di garasi ini!");

                new id, count = CountPlayerFactVehInGarage(playerid, 9), list[596];
                format(list,sizeof(list),"No\tModel Kendaraan\tNomor Plat\n");
                for(new itt = 0; itt < count; itt++)
                {
                    id = GetVehicleIDStoredFactGarage(playerid, itt, 9);
                    if(itt == count)
                    {
                        format(list, sizeof(list), "%s%d\t%s\t%s", list, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                    } else format(list, sizeof(list), "%s%d\t%s\t%s\n", list, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                }
                ShowPlayerDialog(playerid, DIALOG_POLICE_GARAGE_OUT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Garasi Polda", list, "Pilih", "Batal");
            }
            case 1:// Simpan Kendaraan
            {
                new carid = -1, bool: foundnearby = false;
                if((carid = Vehicle_Nearest(playerid, 10.0)) != -1)
                {
                    if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
                    if(PlayerVehicle[carid][pVehRental] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat disimpan digarasi Faction!");
                    if(PlayerVehicle[carid][pVehFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan kendaraan Kepolisian!");
                    Vehicle_GetStatus(carid);
                    PlayerVehicle[carid][pVehFactStored] = 9;

                    foundnearby = true;

                    if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]))
                    {
                        DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
                        SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

                        DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
                        PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
                    }
                }
                if(!foundnearby) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan dari Kepolisian District  milik anda di sekitar!");
            }
            case 2:// Beli Kendaraan
            {
                ShowPlayerDialog(playerid, DIALOG_POLICE_GARAGE_BUY, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Beli Kendaraan",
                "Model\tHarga\
                \nSultan Sabhara\t$5000\
                \n"GRAY"Cheetah Speed Hunter\t"GRAY"$20000\
                \nBullet Speed Hunter\t$20000\
                \n"GRAY"Sanchez Sabhara\t"GRAY"$4000\
                \nFBI Rancher\t$6000\
                \n"GRAY"Mobil Tahanan\t"GRAY"$8000\
                \nHPV 1000\t$4000\
                \n"GRAY"Mobil Patwal\t"GRAY"$5000\
                \nBarracuda\t$10000\
                \n"GRAY"Insurgent\t"GRAY"$7000", "Beli", "Batal");
            }
            case 3:// Hapus Kendaraan
            {
                new frmtdel[151];
                mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 1 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
                mysql_query(g_SQL, frmtdel);

                new rows = cache_num_rows();
                if(rows)
                {
                    new list[522], hkvid, hkvmod;

                    format(list, sizeof(list), "Database ID\tModel\n");
                    for(new i; i < rows; ++i)
                    {
                        cache_get_value_name_int(i, "id", hkvid);
                        cache_get_value_name_int(i, "PVeh_ModelID", hkvmod);

                        format(list, sizeof(list), "%s%d\t%s\n", list, hkvid, GetVehicleModelName(hkvmod));
                    }
                    ShowPlayerDialog(playerid, DIALOG_POLICE_GARAGE_DEL, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Hapus Kendaraan", list, "Hapus", "Batal");
                }
                else 
                {
                    PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Kendaraan", "Anda tidak memiliki kendaraan Polisi!", "Tutup", "");
                }
            }
        }
    }
    else if(dialogid == DIALOG_POLICE_GARAGE_BUY)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota kepolisian!");
        if(!IsPlayerInDynamicArea(playerid, PoliceStuff[PoldaGarage])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat Garasi Polda!");

        // new count = 0;
        // foreach(new carid : PvtVehicles)
        // {
        //     if(PlayerVehicle[carid][pVehExists] && PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
        //         count ++;
        // }
        // if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");

        switch(listitem)
        {
            case 0: //sultan sabhara
            {
                if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 5000);
                //VehicleFaction_Create(playerid, 560, FACTION_POLISI, PoliceStuff[PoldaSpawnPOS][0], PoliceStuff[PoldaSpawnPOS][1], PoliceStuff[PoldaSpawnPOS][2], PoliceStuff[PoldaSpawnPOS][3], 36, 36, 5000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 1: // Cheetah Speed Hunter
            {   
                if(AccountData[playerid][pMoney] < 20000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 20000);
               // VehicleFaction_Create(playerid, 415, FACTION_POLISI, PoliceStuff[PoldaSpawnPOS][0], PoliceStuff[PoldaSpawnPOS][1], PoliceStuff[PoldaSpawnPOS][2], PoliceStuff[PoldaSpawnPOS][3], 1, 2, 20000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 2: // Bullet Speed Hunter
            {
                if(AccountData[playerid][pMoney] < 20000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 20000);
                //VehicleFaction_Create(playerid, 541, FACTION_POLISI, PoliceStuff[PoldaSpawnPOS][0], PoliceStuff[PoldaSpawnPOS][1], PoliceStuff[PoldaSpawnPOS][2], PoliceStuff[PoldaSpawnPOS][3], 0, 0, 20000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 3: //sanchez sabhara
            {
                if(AccountData[playerid][pMoney] < 4000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 4000);
                //VehicleFaction_Create(playerid, 468, FACTION_POLISI, PoliceStuff[PoldaSpawnPOS][0], PoliceStuff[PoldaSpawnPOS][1], PoliceStuff[PoldaSpawnPOS][2], PoliceStuff[PoldaSpawnPOS][3], 36, 36, 4000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 4: // FBI Rancher
            {
                if(AccountData[playerid][pMoney] < 6000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 6000);
                //VehicleFaction_Create(playerid, 490, FACTION_POLISI, PoliceStuff[PoldaSpawnPOS][0], PoliceStuff[PoldaSpawnPOS][1], PoliceStuff[PoldaSpawnPOS][2], PoliceStuff[PoldaSpawnPOS][3], 36, 36, 6000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 5: //Mobil Tahanan
            {
                if(AccountData[playerid][pMoney] < 8000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 8000);
                //VehicleFaction_Create(playerid, 427, FACTION_POLISI, PoliceStuff[PoldaSpawnPOS][0], PoliceStuff[PoldaSpawnPOS][1], PoliceStuff[PoldaSpawnPOS][2], PoliceStuff[PoldaSpawnPOS][3], 36, 36, 8000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 6: //HPV 1000
            {
                if(AccountData[playerid][pMoney] < 4000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 4000);
               // VehicleFaction_Create(playerid, 523, FACTION_POLISI, PoliceStuff[PoldaSpawnPOS][0], PoliceStuff[PoldaSpawnPOS][1], PoliceStuff[PoldaSpawnPOS][2], PoliceStuff[PoldaSpawnPOS][3], 36, 36, 4000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 7: //Mobil Patwal
            {
                if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 5000);
               // VehicleFaction_Create(playerid, 426, FACTION_POLISI, PoliceStuff[PoldaSpawnPOS][0], PoliceStuff[PoldaSpawnPOS][1], PoliceStuff[PoldaSpawnPOS][2], PoliceStuff[PoldaSpawnPOS][3], 36, 36, 5000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 8: //Barracuda
            {
                if(AccountData[playerid][pMoney] < 10000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 10000);
               // VehicleFaction_Create(playerid, 601, FACTION_POLISI, PoliceStuff[PoldaSpawnPOS][0], PoliceStuff[PoldaSpawnPOS][1], PoliceStuff[PoldaSpawnPOS][2], PoliceStuff[PoldaSpawnPOS][3], 36, 36, 10000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 9: //Insurgent
            {
                if(AccountData[playerid][pMoney] < 7000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 7000);
               // VehicleFaction_Create(playerid, 528, FACTION_POLISI, PoliceStuff[PoldaSpawnPOS][0], PoliceStuff[PoldaSpawnPOS][1], PoliceStuff[PoldaSpawnPOS][2], PoliceStuff[PoldaSpawnPOS][3], 36, 36, 7000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
        }
    }
    else if(dialogid == DIALOG_FEDERAL_GARAGE_BUY)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota kepolisian!");
        if(!IsPlayerInDynamicArea(playerid, PoliceStuff[FederalGarage])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat Garasi Federal!");

        // new count = 0;
        // foreach(new carid : PvtVehicles)
        // {
        //     if(PlayerVehicle[carid][pVehExists] && PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
        //         count ++;
        // }
        // if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");

        switch(listitem)
        {
            case 0: //sultan sabhara
            {
                if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 5000);
                //VehicleFaction_Create(playerid, 560, FACTION_POLISI, PoliceStuff[FederalSpawnPOS][0], PoliceStuff[FederalSpawnPOS][1], PoliceStuff[FederalSpawnPOS][2], PoliceStuff[FederalSpawnPOS][3], 36, 36, 5000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 1: // Cheetah Speed Hunter
            {
                if(AccountData[playerid][pMoney] < 20000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 20000);
               // VehicleFaction_Create(playerid, 415, FACTION_POLISI, PoliceStuff[FederalSpawnPOS][0], PoliceStuff[FederalSpawnPOS][1], PoliceStuff[FederalSpawnPOS][2], PoliceStuff[FederalSpawnPOS][3], 1, 2, 20000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 2: // Bullet Speed Hunter
            {
                if(AccountData[playerid][pMoney] < 20000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 20000);
                //VehicleFaction_Create(playerid, 541, FACTION_POLISI, PoliceStuff[FederalSpawnPOS][0], PoliceStuff[FederalSpawnPOS][1], PoliceStuff[FederalSpawnPOS][2], PoliceStuff[FederalSpawnPOS][3], 0, 0, 20000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 3: //sanchez sabhara
            {
                if(AccountData[playerid][pMoney] < 4000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 4000);
               // VehicleFaction_Create(playerid, 468, FACTION_POLISI, PoliceStuff[FederalSpawnPOS][0], PoliceStuff[FederalSpawnPOS][1], PoliceStuff[FederalSpawnPOS][2], PoliceStuff[FederalSpawnPOS][3], 36, 36, 4000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 4: // FBI Rancher
            {
                if(AccountData[playerid][pMoney] < 6000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 6000);
                //VehicleFaction_Create(playerid, 490, FACTION_POLISI, PoliceStuff[FederalSpawnPOS][0], PoliceStuff[FederalSpawnPOS][1], PoliceStuff[FederalSpawnPOS][2], PoliceStuff[FederalSpawnPOS][3], 36, 36, 6000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 5: //Mobil Tahanan
            {
                if(AccountData[playerid][pMoney] < 8000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 8000);
                //VehicleFaction_Create(playerid, 427, FACTION_POLISI, PoliceStuff[FederalSpawnPOS][0], PoliceStuff[FederalSpawnPOS][1], PoliceStuff[FederalSpawnPOS][2], PoliceStuff[FederalSpawnPOS][3], 36, 36, 8000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 6: //HPV 1000
            {
                if(AccountData[playerid][pMoney] < 4000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 4000);
               // VehicleFaction_Create(playerid, 523, FACTION_POLISI, PoliceStuff[FederalSpawnPOS][0], PoliceStuff[FederalSpawnPOS][1], PoliceStuff[FederalSpawnPOS][2], PoliceStuff[FederalSpawnPOS][3], 36, 36, 4000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 7: //Mobil Patwal
            {
                if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 5000);
               // VehicleFaction_Create(playerid, 426, FACTION_POLISI, PoliceStuff[FederalSpawnPOS][0], PoliceStuff[FederalSpawnPOS][1], PoliceStuff[FederalSpawnPOS][2], PoliceStuff[FederalSpawnPOS][3], 36, 36, 5000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 8: //Barracuda
            {
                if(AccountData[playerid][pMoney] < 10000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 10000);
               // VehicleFaction_Create(playerid, 601, FACTION_POLISI, PoliceStuff[FederalSpawnPOS][0], PoliceStuff[FederalSpawnPOS][1], PoliceStuff[FederalSpawnPOS][2], PoliceStuff[FederalSpawnPOS][3], 36, 36, 10000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
            case 9: //Insurgent
            {
                if(AccountData[playerid][pMoney] < 7000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                TakeMoney(playerid, 7000);
                //VehicleFaction_Create(playerid, 528, FACTION_POLISI, PoliceStuff[FederalSpawnPOS][0], PoliceStuff[FederalSpawnPOS][1], PoliceStuff[FederalSpawnPOS][2], PoliceStuff[FederalSpawnPOS][3], 36, 36, 7000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
            }
        }
    }
    else if(dialogid == DIALOG_FEDERAL_GARAGE)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota kepolisian!");
        if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        switch(listitem)
        {
            case 0:// Keluarkan Kendaraan
            {
                if(CountPlayerFactVehInGarage(playerid, FACTION_POLISI) < 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun di garasi ini!");

                new id, count = CountPlayerFactVehInGarage(playerid, FACTION_POLISI), list[596];
                format(list,sizeof(list),"No\tModel Kendaraan\tNomor Plat\n");
                for(new itt = 0; itt < count; itt++)
                {
                    id = GetVehicleIDStoredFactGarage(playerid, itt, FACTION_POLISI);
                    if(itt == count)
                    {
                        format(list, sizeof(list), "%s%d\t%s\t%s", list, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                    } else format(list, sizeof(list), "%s%d\t%s\t%s\n", list, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                }
                ShowPlayerDialog(playerid, DIALOG_FEDERAL_GARAGE_OUT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Garasi Federal", list, "Pilih", "Batal");
            }
            case 1:// Simpan KendaraanA
            {
                new carid = -1, bool: foundnearby = false;
                if((carid = Vehicle_Nearest(playerid, 10.0)) != -1)
                {
                    if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
                    if(PlayerVehicle[carid][pVehRental] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat disimpan digarasi Faction!");
                    if(PlayerVehicle[carid][pVehFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan kendaraan Kepolisian!");
                    Vehicle_GetStatus(carid);
                    PlayerVehicle[carid][pVehFactStored] = FACTION_POLISI;

                    foundnearby = true;

                    if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]))
                    {
                        DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
                        SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

                        DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
                        PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
                    }
                }
                if(!foundnearby) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan dari Kepolisian District  milik anda di sekitar!");
            }
            case 2:// Beli Kendaraan
            {
                ShowPlayerDialog(playerid, DIALOG_FEDERAL_GARAGE_BUY, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Beli Kendaraan",
                "Model\tHarga\
                \nSultan Sabhara\t$5000\
                \n"GRAY"Cheetah Speed Hunter\t"GRAY"$20000\
                \nBullet Speed Hunter\t$20000\
                \n"GRAY"Sanchez Sabhara\t"GRAY"$4000\
                \nFBI Rancher\t$6000\
                \n"GRAY"Mobil Tahanan\t"GRAY"$8000\
                \nHPV 1000\t$4000\
                \n"GRAY"Mobil Patwal\t"GRAY"$5000\
                \nBarracuda\t$10000\
                \n"GRAY"Insurgent\t"GRAY"$7000", "Beli", "Batal");
            }
            case 3:// Hapus Kendaraan
            {
                new frmtdel[151];
                mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 1 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
                mysql_query(g_SQL, frmtdel);

                new rows = cache_num_rows();
                if(rows)
                {
                    new list[522], hkvid, hkvmod;

                    format(list, sizeof(list), "Database ID\tModel\n");
                    for(new i; i < rows; ++i)
                    {
                        cache_get_value_name_int(i, "id", hkvid);
                        cache_get_value_name_int(i, "PVeh_ModelID", hkvmod);

                        format(list, sizeof(list), "%s%d\t%s\n", list, hkvid, GetVehicleModelName(hkvmod));
                    }
                    ShowPlayerDialog(playerid, DIALOG_POLICE_GARAGE_DEL, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Hapus Kendaraan", list, "Hapus", "Batal");
                }
                else 
                {
                    PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Kendaraan", "Anda tidak memiliki kendaraan Polisi!", "Tutup", "");
                }
            }
        }
    }
    else if(dialogid == DIALOG_POLICE_GARAGE_DEL)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Kepolisian!");


        new frmtdel[151], Cache:execute;
        mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 1 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
        execute = mysql_query(g_SQL, frmtdel, true);
        new rowscount = cache_num_rows();
        if(rowscount)
        {
            new hvid, hvmod, hvprice, kckstr[225], strgbg[128];
            if(listitem >= 0 && listitem < rowscount)
            {
                cache_get_value_name_int(listitem, "id", hvid);
                cache_get_value_name_int(listitem, "PVeh_ModelID", hvmod);
                cache_get_value_name_int(listitem, "PVeh_Price", hvprice);

                format(kckstr, sizeof(kckstr), "Anda berhasil menghapus kendaraan:\n\
                Database ID: %d\n\
                Model: %s", hvid, GetVehicleModelName(hvmod));
                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Kendaraan", kckstr, "Tutup", "");

                new pvid = GetFactionVehicleIDFromListitem(playerid, listitem, FACTION_POLISI);

                PlayerVehicle[pvid][pVehExists] = false;
                if(IsValidVehicle(PlayerVehicle[pvid][pVehPhysic]))
                {
                    DisableVehicleSpeedCap(PlayerVehicle[pvid][pVehPhysic]);
                    SetVehicleNeonLights(PlayerVehicle[pvid][pVehPhysic], false, PlayerVehicle[pvid][pVehNeon], 0);

                    DestroyVehicle(PlayerVehicle[pvid][pVehPhysic]);
                    PlayerVehicle[pvid][pVehPhysic] = INVALID_VEHICLE_ID;
                }
                GiveMoney(playerid, hvprice);
                
                mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `id`=%d", hvid);
                mysql_tquery(g_SQL, strgbg);

                Iter_Remove(PvtVehicles, pvid);
            }
        }
        cache_delete(execute);
    }
    else if(dialogid == DIALOG_FEDERAL_GARAGE_OUT)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota kepolisian!");
        if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

        new id = GetVehicleIDStoredFactGarage(playerid, listitem, FACTION_POLISI);
        if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

        if(!IsPlayerInDynamicArea(playerid, PoliceStuff[FederalGarage])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat garasi federal!");
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

        PlayerVehicle[id][pVehPos][0] = PoliceStuff[FederalSpawnPOS][0];
        PlayerVehicle[id][pVehPos][1] = PoliceStuff[FederalSpawnPOS][1];
        PlayerVehicle[id][pVehPos][2] = PoliceStuff[FederalSpawnPOS][2];
        PlayerVehicle[id][pVehPos][3] = PoliceStuff[FederalSpawnPOS][3];

        OnPlayerVehicleRespawn(id);

        SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
    }
    else if(dialogid == DIALOG_POLICE_GARAGE_OUT)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota kepolisian!");
        if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

        new id = GetVehicleIDStoredFactGarage(playerid, listitem, 9);
        if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

        if(!IsPlayerInDynamicArea(playerid, PoliceStuff[PoldaGarage])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat garasi polisi!");
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

        PlayerVehicle[id][pVehPos][0] = PoliceStuff[PoldaSpawnPOS][0];
        PlayerVehicle[id][pVehPos][1] = PoliceStuff[PoldaSpawnPOS][1];
        PlayerVehicle[id][pVehPos][2] = PoliceStuff[PoldaSpawnPOS][2];
        PlayerVehicle[id][pVehPos][3] = PoliceStuff[PoldaSpawnPOS][3];
        OnPlayerVehicleRespawn(id);

        SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
    }
    else if(dialogid == DIALOG_POLICE_IMPOUND)
    {
        if(!response) return 1;

        if(isnull(inputtext))
        {
            ShowPlayerDialog(playerid, DIALOG_POLICE_IMPOUND, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Impound",
            "Error: Tidak dapat diisi kosong!\nMasukkan ID Pemain yang ingin dicek kendaraannya", "Submit", "Batal");
            return 1;
        }

        if(!IsNumeric(inputtext))
        {
            ShowPlayerDialog(playerid, DIALOG_POLICE_IMPOUND, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Impound",
            "Error: Hanya dapat di isi angka!\nMasukkan ID Pemain yang ingin dicek kendaraannya", "Submit", "Batal");
            return 1;
        }
        new targetid = strval(inputtext);
        if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
        if(!IsPlayerNearPlayer(playerid, targetid, 5.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak berada didekat anda!");
        if(CountPlayerVehicleImpound(targetid) < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki kendaraan yang di impound!"); 
        ShowPlayerVehicleImpound(playerid, targetid);
        SetPVarInt(playerid, "PlayerHaveImpoundVeh", targetid);
    }
    else if(dialogid == DIALOG_POLICE_TAKE_IMPOUND)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Kepolisian District !");
        if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        new vehid = ReturnVehicleIDImpounded(GetPVarInt(playerid, "PlayerHaveImpoundVeh"), listitem);

        PlayerVehicle[vehid][pVehParked] = -1;
        PlayerVehicle[vehid][pVehHouseGarage] = -1;
        PlayerVehicle[vehid][pVehHelipadGarage] = -1;
        PlayerVehicle[vehid][pVehFamiliesGarage] = -1;
        PlayerVehicle[vehid][pVehFactStored] = -1;

        PlayerVehicle[vehid][pVehWorld] = GetPlayerVirtualWorld(playerid);
        PlayerVehicle[vehid][pVehInterior] = GetPlayerInterior(playerid);

        PlayerVehicle[vehid][pVehImpounded] = false;
        PlayerVehicle[vehid][pVehImpoundDuration] = 0;
        PlayerVehicle[vehid][pVehImpoundFee] = 0;
        format(PlayerVehicle[vehid][pVehImpoundReason], 32, "N/A");

        PlayerVehicle[vehid][pVehDamage][0] = 0;
        PlayerVehicle[vehid][pVehDamage][1] = 0;
        PlayerVehicle[vehid][pVehDamage][2] = 0;
        PlayerVehicle[vehid][pVehDamage][3] = 0;

        PlayerVehicle[vehid][pVehFuel] = MAX_FUEL_FULL;
        PlayerVehicle[vehid][pVehHealth] = 1000.0;

        PlayerVehicle[vehid][pVehPos][0] = PoliceStuff[PoldaSpawnPOS][0];
        PlayerVehicle[vehid][pVehPos][1] = PoliceStuff[PoldaSpawnPOS][1];
        PlayerVehicle[vehid][pVehPos][2] = PoliceStuff[PoldaSpawnPOS][2];
        PlayerVehicle[vehid][pVehPos][3] = PoliceStuff[PoldaSpawnPOS][3];

        OnPlayerVehicleRespawn(vehid);
        Info(playerid, "Berhasil mengeluarkan kendaraan "YELLOW"%s - %s"WHITE" dari Samsat", GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]);
        DeletePVar(playerid, "PlayerHaveImpoundVeh");

        new dbstr[200];
        mysql_format(g_SQL, dbstr, sizeof(dbstr), "UPDATE `player_vehicles` SET `PVeh_Impounded`=0, `PVeh_ImpoundedPrice`=0, `PVeh_ImpoundedTime`=0, `PVeh_ImpoundedReason`='N/A' WHERE `id`=%d", PlayerVehicle[vehid][pVehID]);
        mysql_tquery(g_SQL, dbstr);
        /*if(PlayerVehicle[vehid][pVehImpoundDuration] <= gettime())
        {
            PlayerVehicle[vehid][pVehParked] = -1;
			PlayerVehicle[vehid][pVehHouseGarage] = -1;
            PlayerVehicle[vehid][pVehHelipadGarage] = -1;
			PlayerVehicle[vehid][pVehFamiliesGarage] = -1;
			PlayerVehicle[vehid][pVehFactStored] = -1;

            PlayerVehicle[vehid][pVehWorld] = GetPlayerVirtualWorld(playerid);
            PlayerVehicle[vehid][pVehInterior] = GetPlayerInterior(playerid);

            PlayerVehicle[vehid][pVehImpounded] = false;
            PlayerVehicle[vehid][pVehImpoundDuration] = 0;
            PlayerVehicle[vehid][pVehImpoundFee] = 0;
            format(PlayerVehicle[vehid][pVehImpoundReason], 32, "N/A");

            PlayerVehicle[vehid][pVehDamage][0] = 0;
            PlayerVehicle[vehid][pVehDamage][1] = 0;
            PlayerVehicle[vehid][pVehDamage][2] = 0;
            PlayerVehicle[vehid][pVehDamage][3] = 0;

            PlayerVehicle[vehid][pVehFuel] = MAX_FUEL_FULL;
            PlayerVehicle[vehid][pVehHealth] = 1000.0;

            PlayerVehicle[vehid][pVehPos][0] = PoliceStuff[PoldaSpawnPOS][0];
            PlayerVehicle[vehid][pVehPos][1] = PoliceStuff[PoldaSpawnPOS][1];
            PlayerVehicle[vehid][pVehPos][2] = PoliceStuff[PoldaSpawnPOS][2];
            PlayerVehicle[vehid][pVehPos][3] = PoliceStuff[PoldaSpawnPOS][3];

            OnPlayerVehicleRespawn(vehid);
            Info(playerid, "Berhasil mengeluarkan kendaraan "YELLOW"%s - %s"WHITE" dari Samsat", GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]);
        
            new dbstr[200];
            mysql_format(g_SQL, dbstr, sizeof(dbstr), "UPDATE `player_vehicles` SET `PVeh_Impounded`=0, `PVeh_ImpoundedPrice`=0, `PVeh_ImpoundedTime`=0, `PVeh_ImpoundedReason`='N/A' WHERE `id`=%d", PlayerVehicle[vehid][pVehID]);
            mysql_tquery(g_SQL, dbstr);
        }
        else 
        {
            PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
            ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Impound",
            "Kendaraan tersebut belum waktunya dikeluarkan!", "Tutup", "");
        }*/
    }
    else if(dialogid == DIALOG_PDM)
    {
        if(response)
        {
            if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Kepolisan District !");
            if(!AccountData[playerid][pDutyPD]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang ~g~On Duty");
            switch(listitem)
            {
                case 0: // Interaksi Kendaraan
                {
                    new vehid = GetNearestVehicleToPlayer(playerid, 4.0, false);
                    if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada didekat kendaraan manapun!");
                    if(VehicleCore[vehid][vehAdmin]) return ShowTDN(playerid, NOTIFICATION_ERROR, "ini adalah kendaraan static Admin!");

                    foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehPhysic] == vehid)
                    {
                        NearestVehicleID[playerid] = vehid;
                    }
                    ShowPlayerDialog(playerid, DIALOG_PDM_VEHICLE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Interaksi Kendaraan",
                    "Informasi Kendaraan\n"GRAY"Membobol Kendaraan\nMenyita Kendaraan Ke Asuransi\n"GRAY"Menyita Kendaraan Ke Samsat", "Pilih", "Batal");
                }
                case 1: // Mengeluarkan Object
                {
                    ShowPlayerDialog(playerid, DIALOG_PDM_OBJECT, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Mengeluarkan Object",
                    "Kerucut\n"GRAY"Pembatas Jalan\nRanjau Kendaraan", "Pilih", "Batal");
                }
                case 2: // cek tahanan
                {
                    static frmxt[598], count, hours, minutes, seconds;
                    format(frmxt, sizeof(frmxt), "Nama Tahanan\tSisa Waktu\n");
                    foreach(new i : Player) if (IsPlayerConnected(i)) if (AccountData[i][pArrest])
                    {
                        GetElapsedTime(AccountData[i][pArrestTime]--, hours, minutes, seconds);
                        format(frmxt, sizeof(frmxt), "%s"YELLOW"P%d:"WHITE" %s\t%02d Jam %02d Menit\n", frmxt, i, AccountData[i][pName], hours, minutes);
                        count ++;
                    }
                    if(count == 0)
                        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- List Tahanan", "Tidak ada pemain dalam masa hukuman penjara!", "Tutup", "");
                    else
                        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- List Tahanan", frmxt, "Tutup", "");
                }
            }
        }
        else
        {
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        }
    }
    else if(dialogid == DIALOG_PDM_OBJECT)
    {
        if(!response) return 1;
        switch(listitem)
        {
            case 0: // kerucut
            {
                if(IsValidDynamicObject(PlayerFactionPoliceVars[playerid][PoliceConeObjid]))
                {
                    DestroyDynamicObject(PlayerFactionPoliceVars[playerid][PoliceConeObjid]);
                    PlayerFactionPoliceVars[playerid][PoliceConeObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                    SendRPMeAboveHead(playerid, "Mengambil kerucut jalan", X11_PLUM1);
                    return 1;
                }

                if(DestroyDynamicObject(PlayerFactionPoliceVars[playerid][PoliceConeObjid]))
                    PlayerFactionPoliceVars[playerid][PoliceConeObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
                
                new Float:X, Float:Y, Float:Z, Float:Ang;
                GetPlayerPos(playerid, X, Y, Z);
                Ang = GetXYInFrontOfPlayer(playerid, X, Y, 3.0);
                PlayerFactionPoliceVars[playerid][PoliceConeObjid] = CreateDynamicObject(1238, X, Y, Z - 0.8, 0.0, 0.0, Ang, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 100.0);

                SendRPMeAboveHead(playerid, "Meletakkan kerucut", X11_PLUM1);
            }
            case 1: //Pembatas jalan
            {
                if(IsValidDynamicObject(PlayerFactionPoliceVars[playerid][PoliceRoadBlockObjid]))
                {
                    DestroyDynamicObject(PlayerFactionPoliceVars[playerid][PoliceRoadBlockObjid]);
                    PlayerFactionPoliceVars[playerid][PoliceRoadBlockObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

                    SendRPMeAboveHead(playerid, "Mengambil pembatas jalan", X11_PLUM1);
                    return 1;
                }

                if(DestroyDynamicObject(PlayerFactionPoliceVars[playerid][PoliceRoadBlockObjid]))
                    PlayerFactionPoliceVars[playerid][PoliceRoadBlockObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
                
                new Float:X, Float:Y, Float:Z, Float:Ang;
                GetPlayerPos(playerid, X, Y, Z);
                Ang = GetXYInFrontOfPlayer(playerid, X, Y, 3.0);
                PlayerFactionPoliceVars[playerid][PoliceRoadBlockObjid] = CreateDynamicObject(1422, X, Y, Z - 0.8, 0.0, 0.0, Ang - 90, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 100.0);

                SendRPMeAboveHead(playerid, "Meletakkan pembatas jalan", X11_PLUM1); 
            }
            case 2: //spike
            {
                if(IsValidDynamicObject(PlayerFactionPoliceVars[playerid][PoliceRanjauObjid]))
                {
                    DestroyDynamicObject(PlayerFactionPoliceVars[playerid][PoliceRanjauObjid]);
                    PlayerFactionPoliceVars[playerid][PoliceRanjauObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
                    PlayerFactionPoliceVars[playerid][PoliceRanjauPos][0] = 0.0;                    
                    PlayerFactionPoliceVars[playerid][PoliceRanjauPos][1] = 0.0;
                    PlayerFactionPoliceVars[playerid][PoliceRanjauPos][2] = 0.0;

                    SendRPMeAboveHead(playerid, "Mengambil ranjau kendaraan", X11_PLUM1);
                    return 1;
                }

                if(DestroyDynamicObject(PlayerFactionPoliceVars[playerid][PoliceRanjauObjid]))
                    PlayerFactionPoliceVars[playerid][PoliceRanjauObjid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
                
                new Float:X, Float:Y, Float:Z, Float:Ang;
                GetPlayerPos(playerid, X, Y, Z);
                Ang = GetXYInFrontOfPlayer(playerid, X, Y, 3.0);
                PlayerFactionPoliceVars[playerid][PoliceRanjauObjid] = CreateDynamicObject(2899, X, Y, Z - 0.7, 0.0, 0.0, Ang, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 100.0);
                PlayerFactionPoliceVars[playerid][PoliceRanjauPos][0] = X;                    
                PlayerFactionPoliceVars[playerid][PoliceRanjauPos][1] = Y;
                PlayerFactionPoliceVars[playerid][PoliceRanjauPos][2] = Z - 0.7;
                
                SendRPMeAboveHead(playerid, "Meletakkan ranjau kendaraan", X11_PLUM1); 
            }
        }
    }
    else if(dialogid == DIALOG_PDM_VEHICLE)
    {
        if(!response) 
        {
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
            return 1;
        }

        if(AccountData[playerid][pFaction] != FACTION_POLISI) 
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Kepolisian District !");
            NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
            return 1;
        }

        if(!AccountData[playerid][pDutyPD]) 
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang ~g~On Duty!");
            NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
            return 1;
        }
        new vehid = NearestVehicleID[playerid];

        if(VehicleCore[vehid][vehAdmin]) 
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Ini adalah kendaraan Admin!");
            NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
            return 1;
        }

        foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehPhysic] == vehid)
        {
            AccountData[playerid][pTempVehID] = i;
        }
        switch(listitem)
        {
            case 0: //vehicle info
            {
                static sha[597];

                foreach(new player : Player) if (AccountData[player][IsLoggedIn])
                {
                    if(PlayerVehicle[AccountData[playerid][pTempVehID]][pVehOwnerID] == AccountData[player][pID])
                    {
                        format(sha, sizeof(sha), "Nama Kendaraan: %s\
                        \nPlat Kendaraan: %s\nPemilik: %s\nStatus Kendaraan: %s", GetVehicleName(PlayerVehicle[AccountData[playerid][pTempVehID]][pVehPhysic]),
                        PlayerVehicle[AccountData[playerid][pTempVehID]][pVehPlate], AccountData[player][pName], (PlayerVehicle[AccountData[playerid][pTempVehID]][pVehRental] == -1) ? ""GREEN"Dimiliki" : ""ORANGE"Rental");
                    }
                    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Informasi Kendaraan", sha, "Tutup", "");
                }
            }
            case 1: // Bobol
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
                if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus diluar kendaraan!");
                if(!PlayerVehicle[AccountData[playerid][pTempVehID]][pVehLocked]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak terkunci!");

                AccountData[playerid][ActivityTime] = 1;
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMBOBOL");
                ShowProgressBar(playerid);

                pTimerDuringBobol[playerid] = SetTimerEx("BreachVehicleKey", 1000, true, "dd", playerid, PlayerVehicle[AccountData[playerid][pTempVehID]][pVehPhysic]);
                ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                SendRPMeAboveHead(playerid, "Membobol Kunci Kendaraan", X11_PLUM1);
            }
            case 2: //asuransi
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
                if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus diluar kendaraan!");
                
                AccountData[playerid][ActivityTime] = 1;
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENYITA");
                ShowProgressBar(playerid);

                ApplyAnimationEx(playerid, "COP_AMBIENT", "Copbrowse_loop", 4.1, 1, 0, 0, 0, 0, 1);
                pTimerAsuransikan[playerid] = SetTimerEx("InsurancedVehicles", 1000, true, "dd", playerid, PlayerVehicle[AccountData[playerid][pTempVehID]][pVehPhysic]);
            }
            case 3: //Impound
            {
                ShowPlayerDialog(playerid, DIALOG_PDM_VEHICLE_IMPOUND, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Menyita Kendaraan",
                "Harap masukkan sesuai format yang ada dibawah ini!\n[Durasi sita [hari]] [denda] [alasan]", "Input", "Batal");
            }
        }
    }
    else if(dialogid == DIALOG_PDM_VEHICLE_IMPOUND)
    {
        if(!response) 
        {
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
            return 1;
        }

        if(AccountData[playerid][pFaction] != FACTION_POLISI) 
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Kepolisian District !");
            NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
            return 1;
        }

        if(!AccountData[playerid][pDutyPD]) 
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang ~g~On Duty!");
            NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
            return 1;
        }
        new vehid = NearestVehicleID[playerid];

        if(VehicleCore[vehid][vehAdmin]) 
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Ini adalah kendaraan Admin!");
            NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
            return 1;
        }
        
        if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus diluar kendaraan!");

        if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_PDM_VEHICLE_IMPOUND, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Menyita Kendaraan",
        "Error: Tidak dapat diisi kosong!\nHarap masukkan sesuai format yang ada dibawah ini!\n[Durasi sita [hari]] [denda] [alasan]", "Input", "Batal");

        new impoundtime, fee, reason[128];
        if(sscanf(inputtext, "dds[128]", impoundtime, fee, reason)) return ShowPlayerDialog(playerid, DIALOG_PDM_VEHICLE_IMPOUND, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Menyita Kendaraan",
        "Harap masukkan sesuai format yang ada dibawah ini!\n[Durasi sita [hari]] [denda] [alasan]", "Input", "Batal");

        if(impoundtime < 1 || impoundtime > 30) return ShowPlayerDialog(playerid, DIALOG_PDM_VEHICLE_IMPOUND, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Menyita Kendaraan",
        "Error: Maksimal waktu 30 hari!\nHarap masukkan sesuai format yang ada dibawah ini!\n[Durasi sita [hari]] [denda] [alasan]", "Input", "Batal");

        if(fee < 1) return ShowPlayerDialog(playerid, DIALOG_PDM_VEHICLE_IMPOUND, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Menyita Kendaraan",
        "Error: Anda tidak dapat memasukkan nominal kurang dari $1!\nHarap masukkan sesuai format yang ada dibawah ini!\n[Durasi sita [hari]] [denda] [alasan]", "Input", "Batal");

        SetPVarString(playerid, "ImpoundReason", reason);
        SetPVarInt(playerid, "ImpoundTime", impoundtime);
        SetPVarInt(playerid, "ImpoundFee", fee);
        
        AccountData[playerid][ActivityTime] = 1;
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENYITA");
        ShowProgressBar(playerid);

        ApplyAnimationEx(playerid, "COP_AMBIENT", "Copbrowse_loop", 4.1, 1, 0, 0, 0, 0, 1);
        foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehPhysic] == vehid)
        {
            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
            {
                pTimerImpound[playerid] = SetTimerEx("ImpoundVehicles", 1000, true, "dd", playerid, PlayerVehicle[i][pVehPhysic]);
            }
        }
    }
    return 1;
}

CheckTargetWeapon(playerid, targetid)
{
    new frmtgun[596], weaponid, ammo, bool: found = false;
    format(frmtgun, sizeof(frmtgun), "Senjata\tAmunisi\n");
    for(new i = 1; i < MAX_WEAPON_SLOT; i ++) {
        GetPlayerWeaponData(targetid, i, weaponid, ammo);

        if(weaponid){
            format(frmtgun, sizeof(frmtgun), "%s%s\t%d Ammo\n", frmtgun, ReturnWeaponName(weaponid), ammo);
            found = true;
        }
    }

    if(!found)
    {
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kepemilikan Senjata",
        "Pemain tersebut tidak memiliki senjata apapun!", "Tutup", "");
    }
    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Kepemilikan Senjata",
    frmtgun, "Tutup", "");
    return 1;
}

Dialog:Dialog_PenjaraFederal(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari anggota Kepolisian District ");
    new targetid = AccountData[playerid][pTarget];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi kedalam server!");
    if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan player tersebut!");
    if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan, tidak dapat melakukan ini!");

    if(!IsNumeric(inputtext))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Format Angka!");

    if(strval(inputtext) < 1 || strval(inputtext) > 120)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 1 Menit dan Maksimal 120 Menit!");

    AccountData[targetid][pArrest] = 1;
    AccountData[targetid][pArrestTime] = floatround(strval(inputtext)) * 60;

    SetPlayerPosArrest(targetid, 1);
    SendClientMessageToAllEx(X11_LIGHTGREY, "[Federal] %s telah dipenjarakan selama %d bulan.", GetRPName(targetid), strval(inputtext));
    
    return 1;
}

Dialog:BrankasPolice(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new xjjs[512];
                format(xjjs, sizeof(xjjs), "Senjata\tAmmo\tHarga\
                \nDesert Eagle\t100\
                \n"GRAY"M4A1\t500\
                \nShotgun\t100\
                \n"GRAY"MP-5\t150\
                \nSniper\t80\
                \n"GRAY"Spas\t100");
                Dialog_Show(playerid, BRGUNPOLICE, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas Persenjataan", xjjs, "Beli", "Tutup");
            }
            case 1:// 
            {
                if(AccountData[playerid][pTaserGun]) {
                    AccountData[playerid][pTaserGun] = 0;
                }
                ResetPlayerWeaponsEx(playerid);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengembalikan Senjata Kepolisian!");
            }
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BRGUNPOLICE(playerid, response, listitem, inputtext[])
{
    if(!response) 
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
        
    if(GetPlayerFaction(playerid) != FACTION_POLISI) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Polda District !");

    new weaponid, ammo, weaponName[32];
    switch(listitem)
    {
        case 0: // Desert Eagle
        {
            weaponid = 24; // ID Deagle
            format(weaponName, sizeof(weaponName), "Desert Eagle");
        }
        case 1: // M4A1
        {
            weaponid = 31;
            format(weaponName, sizeof(weaponName), "M4A1");
        }
        case 2: // Shotgun
        {
            weaponid = 25;
            format(weaponName, sizeof(weaponName), "Shotgun");
        }
        case 3: // MP5
        {
            weaponid = 29;
            format(weaponName, sizeof(weaponName), "MP-5");
        }
        case 4: // Sniper
        {
            weaponid = 34;
            format(weaponName, sizeof(weaponName), "Sniper Rifle");
        }
        case 5: // Spas-12
        {
            weaponid = 27;
            format(weaponName, sizeof(weaponName), "Spas-12");
        }
        default: return 1;
    }
    for(new i = 0; i < 13; i++)
    {
        new w, a;
        GetPlayerWeaponData(playerid, i, w, a);
        if(w == weaponid && a > 0)
        {
            new msg[64];
            format(msg, sizeof(msg), "Anda masih memiliki %s!", weaponName);
            return ShowTDN(playerid, NOTIFICATION_ERROR, msg);
        }
    }
    switch(weaponid)
    {
        case 24: ammo = 100;
        case 31: ammo = 500;
        case 25: ammo = 100;
        case 29: ammo = 150;
        case 34: ammo = 80;
        case 27: ammo = 100;
    }
    GivePlayerWeaponEx(playerid, weaponid, ammo);

    new successMsg[80];
    format(successMsg, sizeof(successMsg), "Berhasil mengambil %s dari brankas!", weaponName);
    ShowTDN(playerid, NOTIFICATION_SUKSES, successMsg);

    return 1;
}

/*Dialog:BRGUNPOLICE(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    if(GetPlayerFaction(playerid) != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Polda District !");
    switch(listitem)
    {
        case 0:// nDesert Eagle
        {
            //new pricing = 5000;
            new weaponid = 24, ammo = 100;
            //if(GetPlayerMoney(playerid) < pricing) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang tidak cukup!");

            //TakeMoney(playerid, pricing);
            GivePlayerWeaponEx(playerid, weaponid, ammo);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil Mengambil Desert Eagle!");   
        }
        case 1:// M4A1
        {
            //new pricing = 18000;
            new weaponid = 31, ammo = 500;
            //if(GetPlayerMoney(playerid) < pricing) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang tidak cukup!");

            //TakeMoney(playerid, pricing);
            GivePlayerWeaponEx(playerid, weaponid, ammo);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membeli M4!");
            
            //static frmtx[178];
            //format(frmtx, sizeof(frmtx), "POLISI - Membeli M4A1 Seharga $18000");
            //AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], 18000, frmtx);
        }
        case 2:// nShotgun
        {
            //new pricing = 7000;
            new weaponid = 25, ammo = 100;
            //if(GetPlayerMoney(playerid) < pricing) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang tidak cukup!");

            //TakeMoney(playerid, pricing);
            GivePlayerWeaponEx(playerid, weaponid, ammo);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membeli Shotgun!");
            
            //static frmtx[178];
            //format(frmtx, sizeof(frmtx), "POLISI - Membeli Shotgun Seharga $7000");
            //ddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], 7000, frmtx);
        }
        case 3:// MP-5
        {
            //new pricing = 8000;
            new weaponid = 29, ammo = 150;
            //if(GetPlayerMoney(playerid) < pricing) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang tidak cukup!");

            //TakeMoney(playerid, pricing);
            GivePlayerWeaponEx(playerid, weaponid, ammo);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membeli MP-5!");

            //static frmtx[178];
            //format(frmtx, sizeof(frmtx), "POLISI - Membeli MP5 Seharga $8000");
            //AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], 8000, frmtx);
        }
        case 4:// Sniper
        {
            //new pricing = 20000;
            new weaponid = 34, ammo = 80;
            //if(GetPlayerMoney(playerid) < pricing) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang tidak cukup!");

            //TakeMoney(playerid, pricing);
            GivePlayerWeaponEx(playerid, weaponid, ammo);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membeli Sniper!");

            //static frmtx[178];
            //format(frmtx, sizeof(frmtx), "POLISI - Membeli Sniper Seharga $20000");
            //AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], 20000, frmtx);
        }
        case 5:// Spass
        {
            //new pricing = 15000;
            new weaponid = 27, ammo = 100;
            //if(GetPlayerMoney(playerid) < pricing) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang tidak cukup!");

            //TakeMoney(playerid, pricing);
            GivePlayerWeaponEx(playerid, weaponid, ammo);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membeli Spass!");

            //static frmtx[178];
            //format(frmtx, sizeof(frmtx), "POLISI - Membeli Spass Seharga $15000");
            //AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], 15000, frmtx);
        }
    }
    return 1;
}*/

Dialog:BrankasSenjataPolice(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new weaponid = 24, ammo = 80;
                GivePlayerWeapon(playerid, weaponid, ammo);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil senjata dari brankas");
                foreach(new i : Player) {
                    if(AccountData[i][pFaction] == 1 && IsPlayerConnected(i)) {
                        SendClientMessageEx(i, -1, ""C_POLISI"[LOGS BRANKAS]"WHITE": Petugas %s Mengambil %s dari Gudang Persenjataan", GetRPName(playerid), ReturnWeaponName(weaponid));
                    }
                }
            }
            case 1:
            {
                new weaponid = 31, ammo = 150;
                GivePlayerWeapon(playerid, weaponid, ammo);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil senjata dari brankas");
                foreach(new i : Player) {
                    if(AccountData[i][pFaction] == 1 && IsPlayerConnected(i)) {
                        SendClientMessageEx(i, -1, ""C_POLISI"[LOGS BRANKAS]"WHITE": Petugas %s Mengambil %s dari Gudang Persenjataan", GetRPName(playerid), ReturnWeaponName(weaponid));
                    }
                }
            }
            case 2:
            {
                new weaponid = 25, ammo = 100;
                GivePlayerWeapon(playerid, weaponid, ammo);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil senjata dari brankas");
                foreach(new i : Player) {
                    if(AccountData[i][pFaction] == 1 && IsPlayerConnected(i)) {
                        SendClientMessageEx(i, -1, ""C_POLISI"[LOGS BRANKAS]"WHITE": Petugas %s Mengambil %s dari Gudang Persenjataan", GetRPName(playerid), ReturnWeaponName(weaponid));
                    }
                }
            }
            case 3:
            {
                new weaponid = 29, ammo = 200;
                GivePlayerWeapon(playerid, weaponid, ammo);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil senjata dari brankas");
                foreach(new i : Player) {
                    if(AccountData[i][pFaction] == 1 && IsPlayerConnected(i)) {
                        SendClientMessageEx(i, -1, ""C_POLISI"[LOGS BRANKAS]"WHITE": Petugas %s Mengambil %s dari Gudang Persenjataan", GetRPName(playerid), ReturnWeaponName(weaponid));
                    }
                }
            }
            case 4:
            {
                new weaponid = 34, ammo = 30;
                GivePlayerWeapon(playerid, weaponid, ammo);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil senjata dari brankas");
                foreach(new i : Player) {
                    if(AccountData[i][pFaction] == 1 && IsPlayerConnected(i)) {
                        SendClientMessageEx(i, -1, ""C_POLISI"[LOGS BRANKAS]"WHITE": Petugas %s Mengambil %s dari Gudang Persenjataan", GetRPName(playerid), ReturnWeaponName(weaponid));
                    }
                }
            }
            case 5://
            {
                if(!AccountData[playerid][pTaserGun])
                {
                    AccountData[playerid][pTaserGun] = 1;
                    new weaponid = 23, ammo = 20000;
                    GivePlayerWeapon(playerid, weaponid, ammo);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil senjata dari brankas");
                    foreach(new i : Player) {
                        if(AccountData[i][pFaction] == 1 && IsPlayerConnected(i)) {
                            SendClientMessageEx(i, -1, ""C_POLISI"[LOGS BRANKAS]"WHITE": Petugas %s Mengambil Pistol Taser dari Gudang Persenjataan", GetRPName(playerid));
                        }
                    }
                }
            }
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}
Dialog:DialogLockerSapd(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Kota District !");
    if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan, tidak dapat mengganti Pakaian!");
    switch(listitem)
    {
        case 0://
        {
            SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
            AccountData[playerid][pUsingUniform] = false;
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengganti pakaian biasa!");
            SetPlayerArmourEx(playerid, 0);
        }
        case 1:// 
        {
            if(AccountData[playerid][pGender] == 1) {
                Dialog_Show(playerid, Clothes_MaleSAPD, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Baju Dinas", ""WHITE"Sabhara\
                \n"GRAY"Polantas 1\n"WHITE"Polantas 2\n"GRAY"Brimob 1\n"WHITE"Brimob 2\n"GRAY"Propam\n"WHITE"Jenderal 1\
                \n"GRAY"Jenderal 2\n"WHITE"FBI\n"GRAY"DIV Udara\n"WHITE"Casis\n"GRAY"Rompi Kepolisian", "Pilih", "Batal");
            } else {
                Dialog_Show(playerid, Clothes_FemaleSAPD, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Baju Dinas", ""WHITE"Sabhara\n"GRAY"Polantas\n"WHITE"Brimob\
                \n"GRAY"Rompi Kepolisian", "Pilih", "Batal");
            }
        }
    }
    return 1;
}
Dialog:Clothes_MaleSAPD(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0: AccountData[playerid][pUniform] = 311; // sabhara
            case 1: AccountData[playerid][pUniform] = 282; // 
            case 2: AccountData[playerid][pUniform] = 284; // 
            case 3: AccountData[playerid][pUniform] = 280; // 
            case 4: AccountData[playerid][pUniform] = 285; // 
            case 5: AccountData[playerid][pUniform] = 304; // 
            case 6: AccountData[playerid][pUniform] = 283; // 
            case 7: AccountData[playerid][pUniform] = 310; // 
            case 8: AccountData[playerid][pUniform] = 286; // 
            case 9: AccountData[playerid][pUniform] = 305; // 
            case 10: AccountData[playerid][pUniform] = 303; // 
            case 11: 
            {
                if(!AccountData[playerid][pUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memakai seragam!");
                SetPlayerArmourEx(playerid, 200); //
            }
        }
        SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
        AccountData[playerid][pUsingUniform] = true;
    }
    return 1;
}
Dialog:Clothes_FemaleSAPD(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0: AccountData[playerid][pUniform] = 309;
            case 1: AccountData[playerid][pUniform] = 306;
            case 2: AccountData[playerid][pUniform] = 307;
            case 3: 
            {
                if(!AccountData[playerid][pUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memakai seragam!");
                SetPlayerArmourEx(playerid, 200); //
            }
        }
        SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
        AccountData[playerid][pUsingUniform] = true;
    }
    return 1;
}

// ----------- COMMAND FACTION POLISI -----------
CMD:melt(playerid, params[])
{
    if(!IsPlayerConnected(playerid)) return false;
    if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota kepolisian!");
    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
    if(!PlayerHasItem(playerid, "Korek Api")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki korek api!");
    if(!IsPeleburanArea(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak di tempat peleburan barang!");

    ApplyAnimation(playerid, "ped", "Jetpack_Idle", 4.1, 0, 0, 0, 1, 2500, 1);
    SendRPMeAboveHead(playerid, "Menyalakan api menggunakan korek api miliknya", X11_PLUM1);
    pTimerPeleburan[playerid] = SetTimerEx("FireOnLebur", 3500, false, "d", playerid);
    return 1;
}

CMD:pdm(playerid, params[])
{
    if(!IsPlayerConnected(playerid)) return false;
    if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
    if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari KEPOLISIAN District !");
    if(!AccountData[playerid][pDutyPD]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang Bertugas/On Duty!");

    ShowPlayerDialog(playerid, DIALOG_PDM, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Police Menu",
    "Interaksi Kendaraan\
    \n"GRAY"Mengeluarkan Object\
    \nList Tahanan", "Pilih", "Batal");
    return 1;
}

CMD:takegunlic(playerid, params[])
{
    if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Kepolisian!");

    new otherid;
    if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/takegunlic [name/playerid]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!IsPlayerNearPlayer(playerid, otherid, 2.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak didekat anda!");
    if(!AccountData[otherid][pGunLic]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki lisensi senjata!");

    AccountData[otherid][pGunLic] = 0;
    AccountData[otherid][pGunLicTime] = 0;
    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil menyita lisensi senjata dari %s", ReturnName(otherid)));
    ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("%s menyita lisensi senjata anda", ReturnName(playerid)));
    
    new cQuery[255];
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_characters` SET `Char_WeaponLic`=%d, `Char_WeaponLicTime`=%d WHERE `pID`=%d", AccountData[otherid][pGunLic], AccountData[otherid][pGunLicTime], AccountData[otherid][pID]);
    mysql_tquery(g_SQL, cQuery);
    return 1;
}

CMD:takeskck(playerid, params[])
{
    if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Polisi District !");
    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");

    new otherid;
    if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/takeskck [name/playerid]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!IsPlayerNearPlayer(playerid, otherid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada didekat pemain tersebut!");
    if(!AccountData[otherid][pSKCK]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki SKCK/Expired!");

    AccountData[otherid][pSKCK] = 0;
    AccountData[otherid][pSKCKTime] = 0;
    ShowTDN(otherid, NOTIFICATION_WARNING, sprintf("Petugas %s mengambil SKCK milik anda.", ReturnName(playerid)));
    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil menarik SKCK milik %s", ReturnName(otherid)));
    return 1;
}

CMD:takesim(playerid, params[])
{
    if(!IsPlayerConnected(playerid)) return 0;
    if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
    if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari KEPOLISIAN District !");

    new otherid, sim;
    if(sscanf(params, "ud", otherid, sim))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/takesim [playerid/Name] [sim]~n~1. SIM A 2.SIM B 3.SIM C");
    
    if(sim < 1 || sim > 3)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid SIM Dimulai dari 1 sampai 3!");
    
    if(otherid == INVALID_PLAYER_ID)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Player tidak didalam server atau Disconnect!");
    
    if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Player tidak didalam server atau Disconnect!");

    if(!IsPlayerNearPlayer(playerid, otherid, 3.0))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada didekat pemain tersebut!");

    switch(sim)
    {
        case 1:
        {
            if(AccountData[otherid][pSimA] != 1)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki Sim A!");
            
            AccountData[otherid][pSimA] = 0;
            AccountData[otherid][pSimATime] = 0;
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil mengambil SIM A milik %s", GetRPName(otherid)));
            ShowTDN(otherid, NOTIFICATION_INFO, sprintf("Petugas %s telah mengambil SIM A milik anda", GetRPName(playerid)));
        }
        case 2:
        {
            if(AccountData[otherid][pSimB] != 1)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki Sim B!");
            
            AccountData[otherid][pSimB] = 0;
            AccountData[otherid][pSimBTime] = 0;
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil mengambil SIM B milik %s", GetRPName(otherid)));
            ShowTDN(otherid, NOTIFICATION_INFO, sprintf("Petugas %s telah mengambil SIM B milik anda", GetRPName(playerid)));
        }
        case 3:
        {
            if(AccountData[otherid][pSimC] != 1)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki Sim C!");
            
            AccountData[otherid][pSimC] = 0;
            AccountData[otherid][pSimCTime] = 0;
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil mengambil SIM C milik %s", GetRPName(otherid)));
            ShowTDN(otherid, NOTIFICATION_INFO, sprintf("Petugas %s telah mengambil SIM C milik anda", GetRPName(playerid)));
        }
    }
    return 1;
}

CMD:amakegunlic(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);
    
    new otherid;
    if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/makegunlic [name/playerid]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(AccountData[otherid][pGunLic]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah memiliki Lisensi Gun!");

    AccountData[otherid][pGunLic] = 1;
    AccountData[otherid][pGunLicTime] = gettime() + (30 * 86400);
    Info(playerid, "Berhasil membuat lisensi senjata kepada %s", ReturnName(otherid));
    Info(otherid, "Petugas %s membuatkan anda lisensi senjata", ReturnName(playerid));

    new cQuery[255];
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_characters` SET `Char_WeaponLic`=%d, `Char_WeaponLicTime`=%d WHERE `pID`=%d", AccountData[otherid][pGunLic], AccountData[otherid][pGunLicTime], AccountData[otherid][pID]);
    mysql_tquery(g_SQL, cQuery);
    return 1;
}

CMD:makegunlic(playerid, params[])
{
    if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Kepolisian!");
    if(AccountData[playerid][pFactionRank] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank IPDA untuk membuat Lisensi Senjata!");
    
    new otherid;
    if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/makegunlic [name/playerid]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(AccountData[otherid][pGunLic]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah memiliki Lisensi Gun!");

    AccountData[otherid][pGunLic] = 1;
    AccountData[otherid][pGunLicTime] = gettime() + (30 * 86400);
    Info(playerid, "Berhasil membuat lisensi senjata kepada %s", ReturnName(otherid));
    Info(otherid, "Petugas %s membuatkan anda lisensi senjata", ReturnName(playerid));

    new cQuery[255];
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_characters` SET `Char_WeaponLic`=%d, `Char_WeaponLicTime`=%d WHERE `pID`=%d", AccountData[otherid][pGunLic], AccountData[otherid][pGunLicTime], AccountData[otherid][pID]);
    mysql_tquery(g_SQL, cQuery);
    return 1;
}

CMD:givesim(playerid, params[])
{
    if(!IsPlayerConnected(playerid)) return 0;
    if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingasn!");
    if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari KEPOLISIAN District !");

    new otherid, sim;
    if(sscanf(params, "ud", otherid, sim))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/givesim [playerid/Name] [type sim]~n~1.SIM A 2.SIM B 3.SIM C");
    
    if(sim < 1 || sim > 3)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid SIM Dimulai dari 1 sampai 3!");
    
    if(otherid == INVALID_PLAYER_ID)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Player tidak didalam server atau Disconnect!");
    
    if(!IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Player tidak didalam server atau Disconnect!");

    if(!IsPlayerNearPlayer(playerid, otherid, 3.0))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada didekat pemain tersebut!");
    
    switch(sim)
    {
        case 1:
        {
            if(AccountData[otherid][pSimA] == 1)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut telah memiliki SIM A!");

            AccountData[otherid][pSimA] = 1;
            AccountData[otherid][pSimATime] = gettime() + (30 * 86400);// 30 hari / 1 bulan
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda memberikan Sim A Kepada %s", AccountData[otherid][pName]));
            ShowTDN(otherid, NOTIFICATION_INFO, sprintf("%s memberikan anda Sim A", AccountData[playerid][pName]));
        }
        case 2:
        {
            if(AccountData[otherid][pSimB] == 1)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut telah memiliki SIM B!");

            AccountData[otherid][pSimB] = 1;
            AccountData[otherid][pSimBTime] = gettime() + (30 * 86400);// 30 hari / 1 bulan
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda memberikan Sim B Kepada %s", AccountData[otherid][pName]));
            ShowTDN(otherid, NOTIFICATION_INFO, sprintf("%s memberikan anda Sim B", AccountData[playerid][pName]));
        }
        case 3:
        {
            if(AccountData[otherid][pSimC] == 1)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut telah memiliki SIM C!");

            AccountData[otherid][pSimC] = 1;
            AccountData[otherid][pSimCTime] = gettime() + (30 * 86400);// 30 hari / 1 bulan
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda memberikan Sim C Kepada %s", AccountData[otherid][pName]));
            ShowTDN(otherid, NOTIFICATION_INFO, sprintf("%s memberikan anda Sim C", AccountData[playerid][pName]));
        }
    }
    return 1;
}
CMD:giveplate(playerid, params[])
{
    if(!IsPlayerConnected(playerid) && !AccountData[playerid][IsLoggedIn]) return 0;
    if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan, tidak dapat memasang Plate!");
    if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Kepolisian Kota District !");
    if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");

    new vehid;
    if(sscanf(params, "d", vehid))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/giveplate [VID]");

    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di luar kendaraan!");

    if(vehid == INVALID_VEHICLE_ID || !IsValidVehicle(vehid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "VID Kendaraan tidak valid!");

    if(!IsPlayerNearVehicle(playerid, vehid, 3.5))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus dekat dengan kendaraan tersebut!");
    
    if(AccountData[playerid][ActivityTime] != 0) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang melakukan sesuatu, harap tunggu!");
    
    foreach(new iterid : PvtVehicles)
    {
        if(PlayerVehicle[iterid][pVehPhysic] == vehid && IsValidVehicle(PlayerVehicle[iterid][pVehPhysic]))
        {
            if(PlayerVehicle[iterid][pVehPlateOwn] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut sudah terpasang Plat Nomor!");

            AccountData[playerid][ActivityTime] = 1;
            pTimerMakePlate[playerid] = SetTimerEx("MakePlate", 1000, true, "dd", playerid, PlayerVehicle[iterid][pVehPhysic]);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMASANG PLATE");
            ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 4.1, 1, 0, 0, 0, 0, 1);
            ShowProgressBar(playerid);
        }
    }
    return 1;
}

forward FireOnLebur(playerid);
public FireOnLebur(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerPeleburan[playerid]);
        pTimerPeleburan[playerid] = -1;
        for(new i = 0; i != 4; i ++) {
            DestroyDynamicObject(FirePeleburan[i]);
        }
        return 0;
    }
    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);

    FirePeleburan[0] = CreateDynamicObject(18691, 2619.182861, 2830.873046, 10.587377, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
	FirePeleburan[1] = CreateDynamicObject(18691, 2618.001708, 2830.873046, 10.587377, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
	FirePeleburan[2] = CreateDynamicObject(18691, 2618.371582, 2830.042236, 10.587377, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00); 
	FirePeleburan[3] = CreateDynamicObject(18691, 2618.371582, 2831.503662, 10.587377, 0.000000, 0.000000, 0.000000, 0, 0, -1, 200.00, 200.00);
    SetTimerEx("FireOffLebur", 10000, false, "d", playerid);
    return 1;
}
forward FireOffLebur(playerid);
public FireOffLebur(playerid)
{
    KillTimer(pTimerPeleburan[playerid]);
    pTimerPeleburan[playerid] = -1;
    for(new i = 0; i != 4; i ++) {
        DestroyDynamicObject(FirePeleburan[i]);
    }
    return 1;
}

forward ImpoundVehicles(playerid, VID);
public ImpoundVehicles(playerid, VID)
{
    if(VID == -1) return 0;

    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerImpound[playerid]);
        pTimerImpound[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(GetNearestVehicleToPlayer(playerid, 3.5, false) != VID)
    {
        KillTimer(pTimerImpound[playerid]);
        pTimerImpound[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda terlalu jauh dari kendaraan!");
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerImpound[playerid]);
        pTimerImpound[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pTimerImpound[playerid]);
        pTimerImpound[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        new impoundtime = GetPVarInt(playerid, "ImpoundTime");
        new fee = GetPVarInt(playerid, "ImpoundFee");
        new reason[128];
        GetPVarString(playerid, "ImpoundReason", reason, sizeof(reason));

        foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehPhysic] == VID)
        {
            foreach(new player : Player)
            {
                if(PlayerVehicle[i][pVehOwnerID] == AccountData[player][pID])
                {
                    SendClientMessageEx(player, X11_ORANGE1, "[IMPOUND]:"WHITE" Kendaraan anda telah terkena Impound selama: %d Hari // Denda: %s // Alasan: %s", impoundtime, FormatMoney(fee), reason);
                }
            }

            PlayerVehicle[i][pVehImpounded] = true;
            PlayerVehicle[i][pVehImpoundFee] = fee;
            PlayerVehicle[i][pVehImpoundDuration] = gettime() + (3600 * 24 * impoundtime);
            format(PlayerVehicle[i][pVehImpoundReason], sizeof(reason), reason);

            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic])) DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
            PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;

            new dbstr[258];
            mysql_format(g_SQL, dbstr, sizeof(dbstr), "UPDATE `player_vehicles` SET `PVeh_Impounded`=1, `PVeh_ImpoundedTime`=%d, `PVeh_ImpoundedPrice`=%d, `PVeh_ImpoundedReason`='%s' WHERE `id`=%d", PlayerVehicle[i][pVehImpoundDuration], PlayerVehicle[i][pVehImpoundFee], PlayerVehicle[i][pVehImpoundReason], PlayerVehicle[i][pVehID]);
            mysql_tquery(g_SQL, dbstr);
        }
        NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
        AccountData[playerid][pTempVehID] = -1;
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime]*110/15;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward InsurancedVehicles(playerid, VID);
public InsurancedVehicles(playerid, VID)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerAsuransikan[playerid]);
        pTimerAsuransikan[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(GetNearestVehicleToPlayer(playerid, 3.5, false) != VID)
    {
        KillTimer(pTimerAsuransikan[playerid]);
        pTimerAsuransikan[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda terlalu jauh dari kendaraan!");
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerAsuransikan[playerid]);
        pTimerAsuransikan[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 10)
    {
        KillTimer(pTimerAsuransikan[playerid]);
        pTimerAsuransikan[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehPhysic] == VID)
        {
            PlayerVehicle[i][pVehInsuranced] = true;
            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic])) DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
            PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;
        }
        NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
        AccountData[playerid][pTempVehID] = -1;
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Menyita kendaraan ke asuransi berhasil dilakukan");
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/10;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward BreachVehicleKey(playerid, VID);
public BreachVehicleKey(playerid, VID)
{
    if(VID == -1) return 0;

    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerDuringBobol[playerid]);
        pTimerDuringBobol[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(GetNearestVehicleToPlayer(playerid, 3.5, false) != VID)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda terlalu jauh dengan kendaraan!");
        KillTimer(pTimerDuringBobol[playerid]);
        pTimerDuringBobol[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pTimerDuringBobol[playerid]);
        pTimerDuringBobol[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pTimerDuringBobol[playerid]);
        pTimerDuringBobol[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehPhysic] == VID)
        {
            PlayerVehicle[i][pVehLocked] = false;
            LockVehicle(PlayerVehicle[i][pVehPhysic], false);
            ToggleVehicleLights(PlayerVehicle[i][pVehPhysic], false);
        }
        NearestVehicleID[playerid] = INVALID_VEHICLE_ID;
        AccountData[playerid][pTempVehID] = -1;
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membobol paksa kunci kendaraan!");
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime]*110/15;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward MakePlate(playerid, vehicleid);
public MakePlate(playerid, vehicleid)
{
    if(vehicleid == -1) return false;

    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerMakePlate[playerid]);
        pTimerMakePlate[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(IsPlayerInjured(playerid))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pTimerMakePlate[playerid]);
        pTimerMakePlate[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(GetNearestVehicleToPlayer(playerid, 3.5, false) != vehicleid)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada didekat kendaraan!");
        KillTimer(pTimerMakePlate[playerid]);
        pTimerMakePlate[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Plat Besi") < 1)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Plat Besi!");
        KillTimer(pTimerMakePlate[playerid]);
        pTimerMakePlate[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 130)
    {
        KillTimer(pTimerMakePlate[playerid]);
        pTimerMakePlate[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Plat Besi");
        ShowItemBox(playerid, "Removed 1x", "PLAT BESI", 3117);

        foreach(new iterid : PvtVehicles)
        {
            if(PlayerVehicle[iterid][pVehPhysic] == vehicleid && IsValidVehicle(PlayerVehicle[iterid][pVehPhysic]))
            {
                new xd1 = Random(sizeof(g_Alphabet)),
                    xd2 = Random(sizeof(g_Alphabet)),
                    xd3 = Random(sizeof(g_Alphabet));
                
                PlayerVehicle[iterid][pVehPlateOwn] = true;
                format(PlayerVehicle[iterid][pVehPlate], 128, "AE %d%d%d%d %s%s%s", random(10), random(10), random(10), random(10), g_Alphabet[xd1], g_Alphabet[xd2], g_Alphabet[xd3]);
                SavePlayerVehicle(iterid);
                
                RespawnVehicle(PlayerVehicle[iterid][pVehPhysic]);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Plate berhasil terpasang di kendaraan tersebut!");
                foreach(new pid : Player) if(PlayerVehicle[iterid][pVehOwnerID] == AccountData[pid][pID])
                {
                    SendClientMessageEx(pid, -1, ""YELLOW"INFORMATION:"WHITE" Petugas %s memasangkan plate %s ke kendaraan anda", ReturnName(playerid), PlayerVehicle[iterid][pVehPlate]);
                }
            }   
        }
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 16.25;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime]*110/130;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

/*DialogPages:PolisiSetRank(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Polda District !");
    if(AccountData[playerid][pFactionRank] < 14) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOMJEN untuk mengakses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 1 ORDER BY `Char_FactionRank` DESC");
    new rows = cache_num_rows();
    if(rows)
    {
        cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
        cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak dapat mengatur jabatan sendiri!");
        if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengatur jabatan rank diatasmu!");
        ShowPlayerDialog(playerid, DIALOG_RANK_SET_POLISI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
        "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
        1. BRIPDA\n\
        2. BRIPTU\n\
        3. BRIPKA\n\
        4. AIPDA\n\
        5. AIPTU\n\
        6. IPDA\n\
        7. IPTU\n\
        8. AKP\n\
        9. KOMPOL\n\
        10. AKPB\n\
        11. KOMBES\n\
        12. BRIGJEN\n\
        13. IRJEN\n\
        14. KOMJEN\n\
        15. JENDPOL", "Set", "Batal");
    }
    return 1;
}

DialogPages:PolisiKickMember(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Polda District !");
    if(AccountData[playerid][pFactionRank] < 14) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOMJEN untuk mengakses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 1 ORDER BY `Char_FactionRank` DESC");
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
        mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_OwnerID`=%d AND `PVeh_Faction` = 1", pidrow);
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
                        if(PlayerVehicle[pvid][pVehFaction] == FACTION_POLISI)
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
                if(AccountData[i][pDutyPD])
                    AccountData[i][pDutyPD] = false;
                if(AccountData[i][pUsingUniform])
					AccountData[i][pUsingUniform] = false;
				SetPlayerSkin(i, AccountData[i][pSkin]);
                RefreshFactionMap(i);
                ShowTDN(i, NOTIFICATION_WARNING, "Anda telah dikeluarkan dari faction Kepolisian District !");
            }
        }
        mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`=0, `Char_FactionRank`=0, `Char_UsingUniform`=0 WHERE `pID`=%d", pidrow);
        mysql_tquery(g_SQL, icsr);
        format(kckstr, sizeof(kckstr), "Anda telah berhasil menendang anggota:\n\
        Nama: %s\n\
        Rank: %s\n\
        Last Online: %s", fckname, PolisiRank[fckrank], fcklastlogin);
        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota",
        kckstr, "Tutup", "");

        AccountData[playerid][pTempSQLFactMemberID] = -1;
        AccountData[playerid][pTempSQLFactRank] = 0;
    }
    return 1;
}*/

forward OnPolisiDeposit(playerid);
public OnPolisiDeposit(playerid)
{
    BrankasLastUse[playerid] = 0;
    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyimpan item");
    FactionBrankas[playerid][factionBrankasID] = 0;
    FactionBrankas[playerid][factionBrankasTemp] = EOS;
    FactionBrankas[playerid][factionBrankasModel] = 0;
    FactionBrankas[playerid][factionBrankasQuant] = 0;
    return 1;
}

CheckPlayerInSpike(playerid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        foreach(new i : Player) if(AccountData[i][pSpawned] && AccountData[i][IsLoggedIn])
        {
            if(PlayerFactionPoliceVars[i][PoliceRanjauObjid] && IsPlayerInRangeOfPoint(playerid, 3.5, PlayerFactionPoliceVars[i][PoliceRanjauPos][0], PlayerFactionPoliceVars[i][PoliceRanjauPos][1], PlayerFactionPoliceVars[i][PoliceRanjauPos][2]))
            {
                if(IsPlayerInAnyVehicle(playerid))
				{
					new carid = GetPlayerVehicleID(playerid);
					GetVehicleDamageStatus(carid, PlayerVehicle[carid][pVehDamage][0], PlayerVehicle[carid][pVehDamage][1], PlayerVehicle[carid][pVehDamage][2], PlayerVehicle[carid][pVehDamage][3]);
					PlayerVehicle[carid][pVehDamage][3] = encode_tires(1, 1, 1, 1);
					UpdateVehicleDamageStatus(carid, PlayerVehicle[carid][pVehDamage][0], PlayerVehicle[carid][pVehDamage][1], PlayerVehicle[carid][pVehDamage][2], PlayerVehicle[carid][pVehDamage][3]);
				}
            }
        }
    }
    return 1;
}

encode_tires(tires1, tires2, tires3, tires4) {

	return tires1 | (tires2 << 1) | (tires3 << 2) | (tires4 << 3);
}


CMD:suspect(playerid, params[])
{
    if(AccountData[playerid][pFaction] != FACTION_POLISI)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota kepolisian District!");
    
    if(!AccountData[playerid][pDutyPD])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus onduty kepolisian untuk mengunakan track suspect!");
    
    new otherid;
    if(sscanf(params, "d", otherid))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/suspect [id]");

    if(otherid == INVALID_PLAYER_ID || !IsPlayerConnected(otherid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "suspect Tidak valid!");

    TrackSuspect(otherid, playerid); 
    return 1;
}