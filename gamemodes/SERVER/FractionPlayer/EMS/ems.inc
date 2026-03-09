#include <YSI\y_hooks>

new const EMSRank[12][] = {
	"N/A",
    "Training",
    "Perawat",
    "Dokter Umum",
    "Dokter Spesialis",
    "Komisi Disiplin",
    "Komisi Umum",
    "SEKBEN",
    "Direktur SDM",
    "Direktur Keilmuan",
    "Wadir Utama",
    "Direktur Utama"
};
enum e_emsstuff
{
    Float:EMSGaragePOS[3],
    Float:EMSSpawnPOS[4],

    STREAMER_TAG_AREA:EMSDuty,
    STREAMER_TAG_AREA:EMSLocker,
    STREAMER_TAG_AREA:EMSGarage,
    STREAMER_TAG_AREA:EMSBrankas,
    STREAMER_TAG_AREA:EMSDesk,
    STREAMER_TAG_AREA:EMSItemsLocker,
    STREAMER_TAG_AREA:EMSHeli,
};
new EMSStuff[e_emsstuff];
new STREAMER_TAG_OBJECT: EMSObject[MAX_PLAYERS][7];
new bool: EMSSpawnHeli[MAX_PLAYERS] = {false, ...};
new EMSHeliVeh[MAX_PLAYERS];

new pTimerReviving[MAX_PLAYERS] = {-1, ...};

CMD:setbrankasems(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);
    
    GetPlayerPos(playerid, PosBrankasEms[0], PosBrankasEms[1], PosBrankasEms[2]);

    BrankasVirtual = GetPlayerVirtualWorld(playerid);
	BrankasInterior = GetPlayerInterior(playerid);
    BrankasEms_Save();
    RefreshFactionMap(playerid);

    if(DestroyDynamicArea(EMSStuff[EMSBrankas]))
		EMSStuff[EMSBrankas] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
    
    EMSStuff[EMSBrankas] = CreateDynamicSphere(PosBrankasEms[0],PosBrankasEms[1],PosBrankasEms[2],2.0,BrankasVirtual,BrankasInterior,-1);

	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengubah posisi brankas EMS.", GetAdminName(playerid));
    return 1;
}

VarsDoorEms()
{
    EMSStuff[EMSDuty] = CreateDynamicSphere(1318.4379,742.3047,10.8784, 2.0, 0, 0, -1);
    EMSStuff[EMSGarage] = CreateDynamicSphere(1796.9568,-1116.0157,24.1013, 2.0, 0, 0, -1);			
    EMSStuff[EMSBrankas] = CreateDynamicSphere(PosBrankasEms[0], PosBrankasEms[1], PosBrankasEms[2], 2.0, BrankasVirtual, BrankasInterior, -1);
    EMSStuff[EMSLocker] = CreateDynamicSphere(1309.0132,745.6656,10.8714, 2.0, 0, 0, -1);
    EMSStuff[EMSDesk] = CreateDynamicSphere(1314.4333,740.5828,10.8784, 2.0, 0, 0, -1);
    EMSStuff[EMSItemsLocker] = CreateDynamicSphere(1315.1475,743.5298,10.8784, 2.0, 0, 0, -1);
    EMSStuff[EMSHeli] = CreateDynamicSphere(1345.3456,741.7292,17.7031, 2.0, -1, -1, -1);
}

hook OnGameModeInit()
{
    VarsDoorEms();
    g_RSLeftDoorOpened = false;
    RSLeftDoorSensor = CreateDynamicSphere(1337.127685, 742.751708, 10.913945, 4.25, 0, 0, -1);
    RSDoor[0] = CreateDynamicObject(1569,  1337.177612, 744.322692, 9.912506, 0.000000, 0.000000, 270.000000, 0, 0, -1, 200.00, 200.00);  // close kanan
    RSDoor[1] = CreateDynamicObject(1569, 1337.207641, 741.302856, 9.912506, 0.000000, 0.000000, 90.000000, 0, 0, -1, 200.00, 200.00);  // close kiri 
    return 1;
}

hook OnPlayerConnect(playerid)
{
    pTimerReviving[playerid] = -1;
    EMSSpawnHeli[playerid] = false;
    EMSHeliVeh[playerid] = INVALID_VEHICLE_ID;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(EMSSpawnHeli[playerid])
    {
        if(IsValidVehicle(EMSHeliVeh[playerid])) DestroyVehicle(EMSHeliVeh[playerid]);
    }
    KillTimer(pTimerReviving[playerid]);
    pTimerReviving[playerid] = -1;
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pFaction] == FACTION_EMS)
        {
            if(IsPlayerInDynamicArea(playerid, EMSStuff[EMSDuty]))
            {
                if(!AccountData[playerid][pDutyEms])
                {
                    AccountData[playerid][pDutyEms] = true;
                    SetFactionColor(playerid);
                    ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~g~On Duty~w~ EMS");
                    AccountData[playerid][pDutyTimer] = SetTimerEx("FactDutyHour", 1000, true, "d", playerid);
                }
                else 
                {
                    AccountData[playerid][pDutyEms] = false;
                    SetPlayerColor(playerid, COLOR_WHITE);
                    ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~r~Off Duty~w~ EMS");
                }
                RefreshFactionMap(playerid);
            }

            if(IsPlayerInDynamicArea(playerid, EMSStuff[EMSLocker]) && AccountData[playerid][pDutyEms])
            {
                ShowPlayerDialog(playerid, DIALOG_EMS_LOCKER, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Locker EMS",
                "Baju Biasa\n"GRAY"Baju Dinas", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, EMSStuff[EMSDesk]) && AccountData[playerid][pDutyEms])
            {
                if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Komisi Disiplin untuk akses desk!");

                ShowPlayerDialog(playerid, DIALOG_EMS_BOSDESK, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Bos Desk",
                "Invite\
                \n"GRAY"Kelola Jabatan\
                \nKick\
                \n"GRAY"Lihat Anggota\
                \nSaldo Finansial\
                \n"GRAY"Deposit Saldo\
                \nTarik Saldo", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, EMSStuff[EMSHeli]) && AccountData[playerid][pDutyEms])
            {
                if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus diluar kendaraan!");
                if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                if(!EMSSpawnHeli[playerid])
                {
                    EMSHeliVeh[playerid] = AddStaticVehicleEx(487, 1345.3456,741.7292,17.7031,94.2814, 3, 1, 60000, 1);
                    VehicleCore[EMSHeliVeh[playerid]][vCoreFuel] = MAX_FUEL_FULL;
                    PutPlayerInVehicle(playerid, EMSHeliVeh[playerid], 0);
                    EMSSpawnHeli[playerid] = true;
                }
                else 
                {
                    if(IsValidVehicle(EMSHeliVeh[playerid])) DestroyVehicle(EMSHeliVeh[playerid]);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Helikopter berhasil dikembalikan");
                    EMSSpawnHeli[playerid] = false;
                }
            }

            /*if(IsPlayerInRangeOfPoint(playerid, 2.0, EMSStuff[EMSGaragePOS][0], EMSStuff[EMSGaragePOS][1], EMSStuff[EMSGaragePOS][2]) && AccountData[playerid][pDutyEms])
            {
                ShowPlayerDialog(playerid, DIALOG_EMS_GARAGE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Garasi EMS",
                "Keluarkan Kendaraan\
                \n"GRAY"Simpan Kendaraan\
                \nBeli Kendaraan\
                \n"GRAY"Hapus Kendaraan", "Pilih", "Batal");  
            }*/

            if(IsPlayerInDynamicArea(playerid, EMSStuff[EMSBrankas]) && AccountData[playerid][pDutyEms])
            {
                if(NearPlayerOpenStorage(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain disekitar sedang membuka brankas!");
                
                AccountData[playerid][menuShowed] = true;
                ShowPlayerDialog(playerid, DIALOG_EMSVAULT, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Brankas EMS",
                "Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, EMSStuff[EMSItemsLocker]) && AccountData[playerid][pDutyEms])
            {
                if(AccountData[playerid][pFactionRank] < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Dokter untuk akses store!");
                
                new sstr[512];
                format(sstr, sizeof sstr, "Item\tStok\tHarga\n");
                format(sstr, sizeof sstr, "%sPerban\t%d\t$25\n", sstr, Bandage);
                format(sstr, sizeof sstr, "%sMedkit\t%d\t$75\n", sstr, Medkit);
                format(sstr, sizeof sstr, "%sAlprazolam\t%d\t$50\n", sstr, PillStress);
                Dialog_Show(playerid, Brankas_Ems, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas Ems", sstr, "Pilih", "Batal");
            }
        }
    }
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pFaction] == FACTION_EMS)
    {
        if(areaid == EMSStuff[EMSBrankas] && AccountData[playerid][pDutyEms])
        {
            ShowKey(playerid, "[Y] Brankas EMS");
        }

        if(areaid == EMSStuff[EMSDuty])
        {
            if(!AccountData[playerid][pDutyEms])
            {
                ShowKey(playerid, "[Y] ~g~On Duty");
            }
            else
            {
                ShowKey(playerid, "[Y] ~r~Off Duty");
            }
        }

        if(areaid == EMSStuff[EMSLocker] && AccountData[playerid][pDutyEms])
        {
            ShowKey(playerid, "[Y] Locker EMS");
        }

        if(areaid == EMSStuff[EMSDesk] && AccountData[playerid][pDutyEms])
        {
            ShowKey(playerid, "[Y] EMS Desk");               
        }
        
        if(areaid == EMSStuff[EMSHeli] && AccountData[playerid][pDutyEms])
        {
            if(!EMSSpawnHeli[playerid])
            {
                ShowKey(playerid, "[Y] Spawn Heli");               
            }
            else 
            {
                ShowKey(playerid, "[Y] Kembalikan Heli");
            }
        }

        if(areaid == EMSStuff[EMSItemsLocker] && AccountData[playerid][pDutyEms])
        {
            ShowKey(playerid, "[Y] Store EMS");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == EMSStuff[EMSBrankas])
    {
        HideShortKey(playerid);
    }

    if(areaid == EMSStuff[EMSItemsLocker])
    {
        HideShortKey(playerid);
    }

    if(areaid == EMSStuff[EMSDuty])
    {
        if(!AccountData[playerid][pDutyEms])
        {
            HideShortKey(playerid);
        }
        else
        {
            HideShortKey(playerid);
        }
    }

    if(areaid == EMSStuff[EMSLocker])
    {
        HideShortKey(playerid);
    }
    
    if(areaid == EMSStuff[EMSGarage])
    {
        HideShortKey(playerid);
    }

    if(areaid == EMSStuff[EMSDesk])
    {
        HideShortKey(playerid);         
    }
    
    if(areaid == EMSStuff[EMSHeli])
    {
        HideShortKey(playerid);         
    }
    return 1;
}

Dialog:Brankas_Ems(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                Dialog_Show(playerid, Perban_Ems, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS", "Mohon ikuti sesuai format berikut:\n[ambil] [jumlah] atau [depo] [jumlah]\nMohon masukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 1:
            {
                Dialog_Show(playerid, Medkit_Ems, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS", "Mohon ikuti sesuai format berikut:\n[ambil] [jumlah] atau [depo] [jumlah]\nMohon masukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 2:
            {
                Dialog_Show(playerid, Pill_Ems, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS", "Mohon ikuti sesuai format berikut:\n[ambil] [jumlah] atau [depo] [jumlah]\nMohon masukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
        }
    }
    else ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    return 1;
}
Dialog:Pill_Ems(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext, "s[128]d", option, amount))
        {
            Dialog_Show(playerid, Pill_Ems, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS", "Mohon ikuti sesuai format berikut:\n[ambil] [jumlah] atau [depo] [jumlah]\nMohon masukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            new harga = 50;
            new bayar = amount * harga;
            if(GetPlayerMoney(playerid) < bayar) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
            if(amount > PillStress) return ShowTDN(playerid, NOTIFICATION_ERROR, "Stok dibrankas tidak sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            PillStress -= amount;
            GiveMoney(playerid, -bayar);
            Inventory_Add(playerid, "Alprazolam", 1241, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil Alprazolam");
            BrankasEms_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "EMS - Membeli Alprazolam sejumlah %d dari dalam Apotik", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }

        if(!strcmp(option, "depo", true))
        {
            new harga = 50;
            if(amount > Inventory_Count(playerid, "Alprazolam")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Alprazolam sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input");

            new paydepo = amount * harga;
            PillStress += amount;
            GiveMoney(playerid, paydepo);
            Inventory_Remove(playerid, "Alprazolam", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyimpan Alprazolam");
            BrankasEms_Save();
        }
    }
    else ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    return 1;
}

Dialog:Medkit_Ems(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext, "s[128]d", option, amount))
        {
            Dialog_Show(playerid, Medkit_Ems, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS", "Mohon ikuti sesuai format berikut:\n[ambil] [jumlah] atau [depo] [jumlah]\nMohon masukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            new harga = 75;
            new bayar = amount * harga;
            if(GetPlayerMoney(playerid) < bayar) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
            if(amount > Medkit) return ShowTDN(playerid, NOTIFICATION_ERROR, "Stok dibrankas tidak sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            Medkit -= amount;
            GiveMoney(playerid, -bayar);
            Inventory_Add(playerid, "Medkit", 11738, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil medkit");
            BrankasEms_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "EMS - Membeli Medkit sejumlah %d dari dalam Apotik", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }

        if(!strcmp(option, "depo", true))
        {
            new harga = 75;
            if(amount > Inventory_Count(playerid, "Medkit")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki medkit sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input");

            new paydepo = amount * harga;
            Medkit += amount;
            GiveMoney(playerid, paydepo);
            Inventory_Remove(playerid, "Medkit", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyimpan medkit");
            BrankasEms_Save();
        }
    }
    else ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    return 1;
}

Dialog:Perban_Ems(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext, "s[128]d", option, amount))
        {
            Dialog_Show(playerid, Perban_Ems, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS", "Mohon ikuti sesuai format berikut:\n[ambil] [jumlah] atau [depo] [jumlah]\nMohon masukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            new harga = 25;
            new bayar = amount * harga;
            if(GetPlayerMoney(playerid) < bayar) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
            if(amount > Bandage) return ShowTDN(playerid, NOTIFICATION_ERROR, "Stok dibrankas tidak sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            Bandage -= amount;
            GiveMoney(playerid, -bayar);
            Inventory_Add(playerid, "Bandage", 11736, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil perban");
            BrankasEms_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "EMS - Membeli Bandage sejumlah %d dari dalam Apotik", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }

        if(!strcmp(option, "depo", true))
        {
            new harga = 25;
            if(amount > Inventory_Count(playerid, "Bandage")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki perban sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input");

            new paydepo = amount * harga;
            Bandage += amount;
            GiveMoney(playerid, paydepo);
            Inventory_Remove(playerid, "Bandage", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyimpan perban");
            BrankasEms_Save();
        }
    }
    else ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    static icsr[1026];
    switch(dialogid)
    {
        case DIALOG_EMSBRANKAS:
        {
            if(!response) return 0;
            if(GetPlayerFaction(playerid) != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang EMS!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            switch(listitem)
            {
                case 0:// perban
                {
                    ShowPlayerDialog(playerid, DIALOG_EMSBKCONFIRM, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS",
                    ""WHITE"Anda akan membeli Perban dengan:\
                    \n\nUang: $150\
                    \nKain: 50x\
                    \nPure Oil: 25x\
                    \nPlastik: 150x\
                    \nKaret: 25x\
                    \n\n"YELLOW"( Masukkan berapa jumlah yang ingin anda beli! )", "Input", "Batal");
                }
                case 1:// medkit 
                {
                    ShowPlayerDialog(playerid, DIALOG_EMSBKCONFIRM, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS",
                    ""WHITE"Anda akan membeli Medkit dengan:\
                    \n\nUang: $150\
                    \nKain: 20x\
                    \nPure Oil: 10x\
                    \nPlastik: 15x\
                    \nKaret: 10x\
                    \n\n"YELLOW"( Masukkan berapa jumlah yang ingin anda beli! )", "Input", "Batal");
                }
                case 2:// Alprazolam
                {
                    ShowPlayerDialog(playerid, DIALOG_EMSBKCONFIRM, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS",
                    ""WHITE"Anda akan membeli Alprazolam dengan:\
                    \n\nUang: $150\
                    \nKain: 5x\
                    \nPure Oil: 6x\
                    \nPlastik: 7x\
                    \nKaret: 8x\
                    \n\n"YELLOW"( Masukkan berapa jumlah yang ingin anda beli! )", "Input", "Batal");
                }
            }
            AccountData[playerid][pTempSQLFactMemberID] = listitem;
        }
        case DIALOG_EMSBKCONFIRM:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
            if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota EMS District !");
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EMSBKCONFIRM, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS",
            "Error: Tidak dapat dikosongkan!\
            \n( Masukkan berapa jumlah yang ingin anda beli! )", "Input", "Batal");
            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EMSBKCONFIRM, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS",
            "Error: Hanya dapat diisi angka!\
            \n( Masukkan berapa jumlah yang ingin anda beli! )", "Input", "Batal");

            static value, sha[168]; 
            value = strval(inputtext);

            if(value < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

            switch(AccountData[playerid][pTempSQLFactMemberID])
            {
                case 0:// perban
                {
                    new pricing = value * 150;
                    new bahan1 = value * 50;// kain
                    new bahan2 = value * 25;// pure oil
                    new bahan3 = value * 150;// plastik
                    new bahan4 = value * 25;// karet
                    if(AccountData[playerid][pMoney] < pricing) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang tidak cukup!");
                    if(Inventory_Count(playerid, "Kain") < bahan1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kain anda tidak cukup!");
                    if(Inventory_Count(playerid, "Pure Oil") < bahan2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pure Oil anda tidak cukup!");
                    if(Inventory_Count(playerid, "Plastik") < bahan3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Plastik anda tidak cukup!");
                    if(Inventory_Count(playerid, "Karet") < bahan4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karet anda tidak cukup!");

                    if(GetTotalWeightFloat(playerid) > 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
                    TakeMoney(playerid, pricing);
                    Inventory_Remove(playerid, "Kain", bahan1);
                    Inventory_Remove(playerid, "Pure Oil", bahan2);
                    Inventory_Remove(playerid, "Plastik", bahan3);
                    Inventory_Remove(playerid, "Karet", bahan4);
                    EMSMoneyVault += pricing;
                    mysql_format(g_SQL, sha, sizeof(sha), "UPDATE `stuffs` SET `emsmoneyvault`=%d WHERE id=0", EMSMoneyVault);
                    mysql_tquery(g_SQL, sha);
                    Inventory_Add(playerid, "Bandage", 11736, value);
                    ShowItemBox(playerid, sprintf("Recieved %dx", value), "BANDAGE", 11736);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil perban!");
                }
                case 1://medkit 
                {
                    new pricing = value * 150;
                    new bahan1 = value * 20;// kain
                    new bahan2 = value * 10;// pure oil
                    new bahan3 = value * 15;// plastik
                    new bahan4 = value * 10;// karet
                    if(AccountData[playerid][pMoney] < pricing) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang tidak cukup!");
                    if(Inventory_Count(playerid, "Kain") < bahan1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kain anda tidak cukup!");
                    if(Inventory_Count(playerid, "Pure Oil") < bahan2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pure Oil anda tidak cukup!");
                    if(Inventory_Count(playerid, "Plastik") < bahan3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Plastik anda tidak cukup!");
                    if(Inventory_Count(playerid, "Karet") < bahan4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karet anda tidak cukup!");

                    if(GetTotalWeightFloat(playerid) > 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
                    TakeMoney(playerid, pricing);
                    Inventory_Remove(playerid, "Kain", bahan1);
                    Inventory_Remove(playerid, "Pure Oil", bahan2);
                    Inventory_Remove(playerid, "Plastik", bahan3);
                    Inventory_Remove(playerid, "Karet", bahan4);
                    EMSMoneyVault += pricing;
                    mysql_format(g_SQL, sha, sizeof(sha), "UPDATE `stuffs` SET `emsmoneyvault`=%d WHERE id=0", EMSMoneyVault);
                    mysql_tquery(g_SQL, sha);
                    Inventory_Add(playerid, "Medkit", 11738, value);
                    ShowItemBox(playerid, sprintf("Recieved %dx", value), "MEDKIT", 11738);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil medkit!");
                }
                case 2:// Alprazolam
                {
                    new pricing = value * 150;
                    new bahan1 = value * 5;// kain
                    new bahan2 = value * 6;// pure oil
                    new bahan3 = value * 7;// plastik
                    new bahan4 = value * 8;// karet
                    if(AccountData[playerid][pMoney] < pricing) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang tidak cukup!");
                    if(Inventory_Count(playerid, "Kain") < bahan1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kain anda tidak cukup!");
                    if(Inventory_Count(playerid, "Pure Oil") < bahan2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pure Oil anda tidak cukup!");
                    if(Inventory_Count(playerid, "Plastik") < bahan3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Plastik anda tidak cukup!");
                    if(Inventory_Count(playerid, "Karet") < bahan4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Karet anda tidak cukup!");

                    if(GetTotalWeightFloat(playerid) > 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
                    TakeMoney(playerid, pricing);
                    Inventory_Remove(playerid, "Kain", bahan1);
                    Inventory_Remove(playerid, "Pure Oil", bahan2);
                    Inventory_Remove(playerid, "Plastik", bahan3);
                    Inventory_Remove(playerid, "Karet", bahan4);
                    EMSMoneyVault += pricing;
                    mysql_format(g_SQL, sha, sizeof(sha), "UPDATE `stuffs` SET `emsmoneyvault`=%d WHERE id=0", EMSMoneyVault);
                    mysql_tquery(g_SQL, sha);
                    Inventory_Add(playerid, "Alprazolam", 1241, value);
                    ShowItemBox(playerid, sprintf("Recieved %dx", value), "Alprazolam", 1241);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil Alprazolam!");
                }
            }
            AccountData[playerid][pTempSQLFactMemberID] = -1;
        }
        case DIALOG_EMS_GARAGE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Anggota EMS!");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            switch(listitem)
            {
                case 0: //takeout
                {
                    if(!CountPlayerFactVehInGarage(playerid, FACTION_EMS)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun disini!");

                    new id, count = CountPlayerFactVehInGarage(playerid, FACTION_EMS), lstr[596];
                    format(lstr, sizeof(lstr), "No\tModel Kendaraan\tNomor Plat\n");
                    for(new itt; itt < count; itt++)
                    {
                        id = GetVehicleIDStoredFactGarage(playerid, itt, FACTION_EMS);
                        if(itt == count)
                        {
                            format(lstr, sizeof(lstr), "%s%d\t%s\t%s", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                        }
                        else format(lstr, sizeof(lstr), "%s%d\t%s\t%s\n", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                    }
                    ShowPlayerDialog(playerid, DIALOG_EMS_GARAGE_TAKEOUT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Garasi EMS", lstr, "Pilih", "Batal");
                }
                case 1:// Simpan KendaraanA
                {
                    new carid = -1, bool: foundnearby = false;
                    if((carid = Vehicle_Nearest(playerid, 12.0)) != -1)
                    {
                        if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
                        if(PlayerVehicle[carid][pVehRental] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat disimpan digarasi Faction!");
                        if(PlayerVehicle[carid][pVehFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan kendaraan EMS!");
                        Vehicle_GetStatus(carid);
                        PlayerVehicle[carid][pVehFactStored] = FACTION_EMS;

                        foundnearby = true;

                        if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]))
                        {
                            DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
                            SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

                            DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
                            PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
                        }
                    }
                    if(!foundnearby) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan dari EMS District  milik anda di sekitar!");
                }
                case 2:// Beli Kendaraan
                {
                    ShowPlayerDialog(playerid, DIALOG_EMS_GARAGE_BUY, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Garasi EMS",
                    "Model\tHarga\
                    \nAmbulance\t$5000\
                    \n"GRAY"Van Jenazah\t"GRAY"$8000\
                    \nFBI Rancher\t$6000\
                    \n"GRAY"Sanchez\t"GRAY"$4000", "Pilih", "Batal");
                }
                case 3:// Hapus Kendaraan
                {
                    new frmtdel[158];
                    mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 3 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
                    mysql_query(g_SQL, frmtdel);

                    new rowscount = cache_num_rows();
                    if(rowscount)
                    {
                        new list[255], havpid, havmod;

                        format(list, sizeof(list), "Database ID\tModel\n");
                        for(new x; x < rowscount; ++x)
                        {
                            cache_get_value_name_int(x, "id", havpid);
                            cache_get_value_name_int(x, "PVeh_ModelID", havmod);

                            format(list, sizeof(list), "%s%d\t%s\n", list, havpid, GetVehicleModelName(havmod));
                        }
                        ShowPlayerDialog(playerid, DIALOG_EMS_GARAGE_DELETE, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Hapus Kendaraan", list, "Hapus", "Batal");
                    }
                    else 
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Kendaraan", "Anda tidak memiliki kendaraan EMS.", "Tutp", "");
                    }
                }
            }
        }
        case DIALOG_EMS_GARAGE_BUY:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota EMS!");
            if(!IsPlayerInDynamicArea(playerid, EMSStuff[EMSGarage])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat Garasi EMS!");

            // new count = 0;
            // foreach(new carid : PvtVehicles)
            // {
            //     if(PlayerVehicle[carid][pVehExists] && PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
            //         count ++;
            // }
            // if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");

            switch(listitem)
            {
                case 0: //ambulance
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 5000);
                    //VehicleFaction_Create(playerid, 416, FACTION_EMS, EMSStuff[EMSSpawnPOS][0], EMSStuff[EMSSpawnPOS][1], EMSStuff[EMSSpawnPOS][2], EMSStuff[EMSSpawnPOS][3], 1, 3, 5000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan!");
                }
                case 1: //ambulance
                {
                    if(AccountData[playerid][pMoney] < 8000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 8000);
                    //VehicleFaction_Create(playerid, 442, FACTION_EMS, EMSStuff[EMSSpawnPOS][0], EMSStuff[EMSSpawnPOS][1], EMSStuff[EMSSpawnPOS][2], EMSStuff[EMSSpawnPOS][3], 0, 0, 8000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan!");
                }
                case 2: //FBI Rancher
                {
                    if(AccountData[playerid][pMoney] < 6000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 6000);
                   // VehicleFaction_Create(playerid, 490, FACTION_EMS, EMSStuff[EMSSpawnPOS][0], EMSStuff[EMSSpawnPOS][1], EMSStuff[EMSSpawnPOS][2], EMSStuff[EMSSpawnPOS][3], 3, 3, 6000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan!");
                }
                case 3: //Sanchez
                {
                    if(AccountData[playerid][pMoney] < 4000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 4000);
                    //VehicleFaction_Create(playerid, 468, FACTION_EMS, EMSStuff[EMSSpawnPOS][0], EMSStuff[EMSSpawnPOS][1], EMSStuff[EMSSpawnPOS][2], EMSStuff[EMSSpawnPOS][3], 3, 3, 4000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan!");
                }
            }
        }
        case DIALOG_EMS_GARAGE_TAKEOUT:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota EMS!");
            if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            new id = GetVehicleIDStoredFactGarage(playerid, listitem, FACTION_EMS);
            if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            if(!IsPlayerInDynamicArea(playerid, EMSStuff[EMSGarage])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat Garasi EMS!");
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

            PlayerVehicle[id][pVehPos][0] = EMSStuff[EMSSpawnPOS][0];
            PlayerVehicle[id][pVehPos][1] = EMSStuff[EMSSpawnPOS][1];
            PlayerVehicle[id][pVehPos][2] = EMSStuff[EMSSpawnPOS][2];
            PlayerVehicle[id][pVehPos][3] = EMSStuff[EMSSpawnPOS][3];

            OnPlayerVehicleRespawn(id);

            SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
        }
        case DIALOG_EMS_PANEL:
        {
            if(!response) return 1;
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
            if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota EMS District !");
            new targetid = AccountData[playerid][pTarget];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan, tidak dapat menggunakan Panel!");
            switch(listitem)
            {
                case 0: //revive
                {
                    if(!PlayerHasItem(playerid, "Medkit")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki medkit!");
                    if(AccountData[playerid][EMSDuringReviving]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang merevive seseorang, tunggu sebentar!");
                    if(!AccountData[targetid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak pingsan!");

                    Inventory_Remove(playerid, "Medkit");
                    SendRPMeAboveHead(playerid, "Menyadarkan korban dengan Medkit", X11_PLUM1);

                    ApplyAnimation(playerid, "MEDIC", "CPR", 8.33, 1, 0, 0, 1, 0, 1);

                    AccountData[playerid][ActivityTime] = 1;
                    AccountData[playerid][EMSDuringReviving] = true;
                    pTimerReviving[playerid] = SetTimerEx("EMSReviving", 1000, true, "dd", playerid, targetid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEREVIVE");
                    ShowProgressBar(playerid);
                }
                case 1:// Treatment
                {   
                    if(AccountData[targetid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang memiliki progress!");
                    
                    SendRPMeAboveHead(playerid, "Memberikan pelayanan treatment", X11_PLUM1);
                    AccountData[targetid][ActivityTime] = 1;
                    pTimerReviving[targetid] = SetTimerEx("EMSTreatment", 1000, true, "d", targetid);
                    PlayerTextDrawSetString(targetid, ProgressBar[targetid][2], "TREATMENT");
                    TogglePlayerControllable(targetid, false);
                    ApplyAnimationEx(targetid, "CRACK", "crckidle1", 4.1, 0, 0, 0, 1, 0, 1);
                    ShowProgressBar(targetid);
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
                case 7:// kasih invoice manual
                {
                    GivePlayerInvoice(playerid, targetid);
                }
                case 8:// Periksa kesehatan
                {
                    GetBoneStatus(playerid, targetid);
                }
                case 9:// Masukkan korban
                {
                    new seatid,
                        vehicleid = GetNearestVehicleToPlayer(playerid, 3.0, false)
                    ;
                    if(!AccountData[targetid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dalam keadaan pingsan!");
                    if(vehicleid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada didekat kendaraan!");
                    if(GetVehicleModel(vehicleid) == 416)
                    {
                        seatid = GetAvailableSeat(vehicleid, 2);

                        if(seatid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada tempat kosong lagi dikendaraan!");
                    
                        ClearAnimations(targetid, 1);
                        AccountData[targetid][pInjured] = 2;

                        PutPlayerInVehicle(targetid, vehicleid, seatid);

                        TogglePlayerControllable(targetid, 0);
                        SetPlayerHealth(targetid, 100.0);
                    }
                    else ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan kendaraan Ambulance!");
                }
                case 10:// keluarkan
                {
                    new vehicleid = GetNearestVehicleToPlayer(playerid, 3.0, false);
                    if(AccountData[targetid][pInjured] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dalam keadaan pingsan!");
                    if(!IsPlayerInVehicle(targetid, vehicleid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak didalam kendaraan anda!");

                    RemovePlayerFromVehicle(targetid);
                    AccountData[targetid][pInjured] = 1;
                }
                case 11:// cek blacklist
                {
                    ShowDurringBlacklist(playerid, targetid);
                }
            }
        }
        case DIALOG_EMSVAULT:
        {
            if(!response) 
            {
                AccountData[playerid][menuShowed] = false;
                return 1;
            }
            if(AccountData[playerid][pFaction] != FACTION_EMS) 
            {
                AccountData[playerid][menuShowed] = false;   
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota dari EMS!");
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
                        ShowPlayerDialog(playerid, DIALOG_EMSVAULT_DEPOSIT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas EMS", str, "Pilih", "Batal");
                    }
                    else 
                    {
                        AccountData[playerid][menuShowed] = false;
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas EMS",
                        "Anda tidak memiliki barang untuk disimpan!", "Tutup", "");
                    }
                    cache_delete(execute);
                }
                case 1: //withdraw
                {
                    new str[4036], amounts, itemname[64], Cache:execute;
                    format(str, sizeof(str), "Nama Item\tJumlah\tBerat (-/-)\n");
                    execute = mysql_query(g_SQL, "SELECT * FROM `ems_brankas` WHERE `PID`=0");
                    if(cache_num_rows() > 0)
                    {
                        for(new x; x < cache_num_rows(); ++x)
                        {
                            cache_get_value_name(x, "Item", itemname);
                            cache_get_value_name_int(x, "Quantity", amounts);

                            format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EMSVAULT_WITHDRAW, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas EMS", str, "Pilih", "Batal");
                    }
                    else 
                    {
                        AccountData[playerid][menuShowed] = false;
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas EMS",
                        "Tidak ada barang di brankas saat ini!", "Tutup", "");
                    }
                    cache_delete(execute);
                }
            }
        }
        case DIALOG_EMSVAULT_DEPOSIT:
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
                ShowPlayerDialog(playerid, DIALOG_EMSVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS",
                shstr, "Input", "Batal");
            }
            cache_delete(execute);
        }
        case DIALOG_EMSVAULT_IN:
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
                ShowPlayerDialog(playerid, DIALOG_EMSVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS",
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_EMSVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS",
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[playerid][factionBrankasQuant])
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_EMSVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS",
                shstr, "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);
            Inventory_Remove(playerid, FactionBrankas[playerid][factionBrankasTemp], quantity);
            ShowItemBox(playerid, sprintf("Removed %dx", quantity), FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel]);

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "EMS - Memasukkan %s sejumlah %d ke dalam brankas", FactionBrankas[playerid][factionBrankasTemp], quantity);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], quantity, frmtx);

            new invstr[1028];
            mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `ems_brankas` WHERE `PID`=0 AND `Item` = '%s'", FactionBrankas[playerid][factionBrankasTemp]);
            mysql_query(g_SQL, shstr);
            new rows = cache_num_rows();
            if(rows > 0)
            {
                mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `ems_brankas` SET `Quantity` = `Quantity` + %d WHERE `PID` = 0 AND `Item`='%s'", quantity, FactionBrankas[playerid][factionBrankasTemp]);
                mysql_tquery(g_SQL, invstr, "OnEMSDeposit", "i", playerid);
            }
            else 
            {
                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `ems_brankas` SET `PID`=0, `Item`='%s', `Model`=%d, `Quantity`=%d", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel], quantity);
                mysql_tquery(g_SQL, invstr, "OnEMSDeposit", "i", playerid);
            }
            AccountData[playerid][menuShowed] = false;
        }
        case DIALOG_EMSVAULT_WITHDRAW:
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
            execute = mysql_query(g_SQL, "SELECT * FROM `ems_brankas` WHERE `PID`=0");
            if(cache_num_rows() > 0)
            {
                cache_get_value_name_int(listitem, "ID", FactionBrankas[playerid][factionBrankasID]);
                cache_get_value_name(listitem, "Item", FactionBrankas[playerid][factionBrankasTemp]);
                cache_get_value_name_int(listitem, "Model", FactionBrankas[playerid][factionBrankasModel]);
                cache_get_value_name_int(listitem, "Quantity", FactionBrankas[playerid][factionBrankasQuant]);

                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_EMSVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS",
                shstr, "Input", "Batal");
            }
            else 
            {
                AccountData[playerid][menuShowed] = false;
                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas EMS",
                "Brankas ini isinya kosong!", "Tutup", "");
            }
            cache_delete(execute);
        }
        case DIALOG_EMSVAULT_OUT:
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
                ShowPlayerDialog(playerid, DIALOG_EMSVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS",
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_EMSVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS",
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[playerid][factionBrankasQuant])
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_EMSVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas EMS",
                shstr, "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext), jts[150];

            if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!"), AccountData[playerid][menuShowed] = false;

            FactionBrankas[playerid][factionBrankasQuant] -= quantity;
            if(FactionBrankas[playerid][factionBrankasQuant] > 0)
            {
                mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `ems_brankas` SET `Quantity`=%d WHERE `ID`=%d", FactionBrankas[playerid][factionBrankasQuant], FactionBrankas[playerid][factionBrankasID]);
                mysql_tquery(g_SQL, jts);
            }
            else 
            {
                mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `ems_brankas` WHERE `ID`=%d", FactionBrankas[playerid][factionBrankasID]);
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
        case DIALOG_EMS_GARAGE_DELETE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari EMS District !");

            new frmtdel[151], Cache:execute;
            mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 3 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
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

                    format(kckstr, sizeof(kckstr), "Anda berhasil menghapus kendaraan:\
                    \nDatabase ID: %d\
                    \nModel: %s", hvid, GetVehicleModelName(hvmod));
                    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Kendaraan", kckstr, "Tutup", "");

                    new pvid = GetFactionVehicleIDFromListitem(playerid, listitem, FACTION_EMS);

                    PlayerVehicle[pvid][pVehExists] = false;
                    if(IsValidVehicle(PlayerVehicle[pvid][pVehPhysic]))
                    {
                        DisableVehicleSpeedCap(PlayerVehicle[pvid][pVehPhysic]);
                        SetVehicleNeonLights(PlayerVehicle[pvid][pVehPhysic], false, PlayerVehicle[pvid][pVehNeon], 0);

                        DestroyVehicle(PlayerVehicle[pvid][pVehPhysic]);
                        PlayerVehicle[pvid][pVehPhysic] = INVALID_VEHICLE_ID;
                    }
                    GiveMoney(playerid, hvprice);

                    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `id` = %d", hvid);
                    mysql_tquery(g_SQL, strgbg);

                    Iter_Remove(PvtVehicles, pvid);
                }
            }
            cache_delete(execute);
        }
        case DIALOG_EMS_BOSDESK:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari EMS District !");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan tidak dapat mengakses Bos Desk!");
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
                        "Tidak ada orang di sekitar anda!", "Tutup", "");
                    }

                    ShowPlayerDialog(playerid, DIALOG_EMS_INVITE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Invite", frmxt, "Pilih", "Batal");
                }
                case 1:// Kelola Jabatan
                {
                    new Cache:execute;
                    execute = mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 3 ORDER BY Char_FactionRank DESC");

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

                            format(shstr, sizeof(shstr), "%s%s\t%s\t%s\n", shstr, fckname, EMSRank[fckrank], fcklastlogin);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EMSSETRANK, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Set Jabatan", shstr, "Pilih", "Batal");
                    }
                    else 
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Set Jabatan", "Tidak ada Anggota EMS!", "Tutup", "");
                    }
                    cache_delete(execute);
                }
                case 2:// Kick Offline / Online
                {
                    new Cache:execute;
                    execute = mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 3 ORDER BY Char_FactionRank DESC");

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

                            format(shstr, sizeof(shstr), "%s%s\t%s\t%s\n", shstr, fckname, EMSRank[fckrank], fcklastlogin);
                        }
                        ShowPlayerDialog(playerid, DIALOG_EMSKICKMEMBER, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Kick Anggota", shstr, "Kick", "Batal");
                    }
                    else 
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota", "Tidak ada Anggota EMS!", "Tutup", "");
                    }
                    cache_delete(execute);
                }
                case 3:// Anggota Online
                {
                    new duty[128], lstr[1024];
                    format(lstr, sizeof lstr, "Nama\tRank\tStatus Duty\n");
                    foreach(new i : Player) {
                        if(AccountData[i][pFaction] == 3) {
                            switch(AccountData[i][pDutyEms])
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
                    format(frmxt, sizeof(frmxt), "Perusahaan EMS District  saat ini memiliki saldo sebesar:\ 
                    \n"DARKGREEN"%s", FormatMoney(EMSMoneyVault));
                    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- EMS Money", frmxt, "Tutup", "");
                }
                case 5:// Deposit saldo
                {
                    ShowPlayerDialog(playerid, DIALOG_DEPOSIT_EMS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- EMS Deposit",
                    "Mohon masukkan nominal deposit untuk saldo perusahaan:", "Input", "Batal");
                }
                case 6://
                {
                    ShowPlayerDialog(playerid, DIALOG_WITHDRAW_EMS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- EMS Withdraw",
                    "Mohon masukkan nominal penarikan tunai dari saldo perusahaan:", "Input", "Batal");
                }
            }
        }
        case DIALOG_DEPOSIT_EMS:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota EMS District !");
            if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Komisi Disiplin untuk akses Bos Desk!");
            new depocash = strval(inputtext), frmtmny[128];
            if(depocash > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak sebanyak itu!");
            if(depocash < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal kurang dari $1 untuk deposit!");
            TakeMoney(playerid, depocash);
            EMSMoneyVault += depocash;
            mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `emsmoneyvault` = %d WHERE `ID` = 0", EMSMoneyVault);
            mysql_tquery(g_SQL, frmtmny);
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil deposit %s untuk EMS District ", FormatMoney(depocash)));

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "EMS - Deposit Uang %s ke dalam perusahaan", FormatMoney(depocash));
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], depocash, frmtx);
        }
        case DIALOG_WITHDRAW_EMS:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota EMS District !");
            if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Komisi Disiplin untuk akses Bos Desk!");
            new withdrawcash = strval(inputtext), frmtmny[128];
            if(withdrawcash > EMSMoneyVault) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang perusahaan tidak sebanyak itu!");
            if(withdrawcash < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal kurang dari $1 untuk withdraw!");
            EMSMoneyVault -= withdrawcash;
            GiveMoney(playerid, withdrawcash);

            mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `emsmoneyvault` = %d WHERE `ID` = 0", EMSMoneyVault);
            mysql_tquery(g_SQL, frmtmny);

            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], withdrawcash, "EMS");

            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil withdraw %s dari EMS District ", FormatMoney(withdrawcash)));

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "EMS - Withdraw Uang %s dari perusahaan", FormatMoney(withdrawcash));
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], withdrawcash, frmtx);
        }
        case DIALOG_EMSKICKMEMBER:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota EMS District !");
            if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Komisi Disiplin untuk mengakses Bos Desk!");

            new Cache:execute = mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 3 ORDER BY `Char_FactionRank` DESC", true);
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
                mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_OwnerID`=%d AND `PVeh_Faction` = 3", pidrow);
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
                                if(PlayerVehicle[pvid][pVehFaction] == FACTION_EMS)
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
                        if(AccountData[i][pDutyEms])
                            AccountData[i][pDutyEms] = false;
                        if(AccountData[i][pUsingUniform])
                            AccountData[i][pUsingUniform] = false;
                        SetPlayerSkin(i, AccountData[i][pSkin]);
                        ShowTDN(i, NOTIFICATION_WARNING, "Anda telah dikeluarkan dari faction EMS District !");
                    }
                }
                mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`=0, `Char_FactionRank`=0, `Char_UsingUniform`=0 WHERE `pID`=%d", pidrow);
                mysql_tquery(g_SQL, icsr);
                format(kckstr, sizeof(kckstr), "Anda telah berhasil menendang anggota:\n\
                Nama: %s\n\
                Rank: %s\n\
                Last Online: %s", fckname, EMSRank[fckrank], fcklastlogin);
                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota",
                kckstr, "Tutup", "");
                
                AccountData[playerid][pTempSQLFactMemberID] = -1;
                AccountData[playerid][pTempSQLFactRank] = 0;
            }
            cache_delete(execute);
        }
        case DIALOG_EMSSETRANK:
        {
            new Cache:execute;
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota EMS District !");
            if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Komisi Disiplin untuk mengakses Bos Desk!");

            execute = mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 3 ORDER BY `Char_FactionRank` DESC");
            new rows = cache_num_rows();
            if(rows)
            {
                cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
                cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
                if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak dapat mengatur jabatan sendiri!");
                if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengatur jabatan rank diatasmu!");
                ShowPlayerDialog(playerid, DIALOG_RANK_SET_EMS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
                "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
                1. Training\n\
                2. Perawat\n\
                3. Dokter Umum\n\
                4. Dokter Spesialis\n\
                5. Komisi Disiplin\n\
                6. Komisi Umum\n\
                7. SEKBEN\n\
                8. Direktur SDM\n\
                9. Direktur Keilmuan\n\
                10.Wadir Utam\n\
                11.Direktur Utama", "Set", "Batal");
            }
            cache_delete(execute);
        }
        case DIALOG_RANK_SET_EMS:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota EMS District !");
            if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Komisi Disiplin untuk akses Bos Desk!");

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_EMS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Error: Tidak dapat diisi kosong!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Training\n\
            2. Perawat\n\
            3. Dokter Umum\n\
            4. Dokter Spesialis\n\
            5. Komisi Disiplin\n\
            6. Komisi Umum\n\
            7. SEKBEN\n\
            8. Direktur SDM\n\
            9. Direktur Keilmuan\n\
            10.Wadir Utam\n\
            11.Direktur Utama", "Set", "Batal");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_EMS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Error: Hanya dapat diisi angka!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Training\n\
            2. Perawat\n\
            3. Dokter Umum\n\
            4. Dokter Spesialis\n\
            5. Komisi Disiplin\n\
            6. Komisi Umum\n\
            7. SEKBEN\n\
            8. Direktur SDM\n\
            9. Direktur Keilmuan\n\
            10.Wadir Utam\n\
            11.Direktur Utama", "Set", "Batal");

            if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pFactionRank]) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_EMS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Training\n\
            2. Perawat\n\
            3. Dokter Umum\n\
            4. Dokter Spesialis\n\
            5. Komisi Disiplin\n\
            6. Komisi Umum\n\
            7. SEKBEN\n\
            8. Direktur SDM\n\
            9. Direktur Keilmuan\n\
            10.Wadir Utam\n\
            11.Direktur Utama", "Set", "Batal");

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
        case DIALOG_EMS_INVITE:
        {
            if(!response) return 0;
            if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota EMS District !");
            if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Komisi Disiplin untuk akses bos desk!");

            new targetid = NearestPlayer[playerid][listitem];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            AccountData[targetid][pFaction] = FACTION_EMS;
            AccountData[targetid][pFactionRank] = 1;
            RefreshFactionMap(targetid);
            mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction` = 3, `Char_FactionRank` = 1 WHERE `pID` = %d", AccountData[targetid][pID]);
            mysql_tquery(g_SQL, icsr);
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil invite faction %s", AccountData[targetid][pName]));
        }
        case DIALOG_EMS_LOCKER:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota EMS!");

            switch(listitem)
            {
                case 0:
                {
                    SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
                    AccountData[playerid][pUsingUniform] = false;
                }
                case 1:
                {
                    ShowPlayerDialog(playerid, DIALOG_EMS_CLOTHES, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Lemari EMS",
                    "Dokter 1\ 
                    \n"GRAY"Dokter 2\ 
                    \nDokter 3\ 
                    \n"GRAY"Dokter 4", "Pilih", "Batal");
                }
            }
        }
        case DIALOG_EMS_CLOTHES:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(!AccountData[playerid][pDutyEms]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus Duty EMS!");
            if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota EMS!");

            switch(listitem)
            {
                case 0: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (70) : (141);
                case 1: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (276) : (308);
                case 2: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (275) : (219);
                case 3: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (274) : (148);
            }
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
            AccountData[playerid][pUsingUniform] = true;
        }
    }
    return 0;
}

forward EMSTreatment(playerid);
public EMSTreatment(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerReviving[playerid]);
        pTimerReviving[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 20)
    {
        KillTimer(pTimerReviving[playerid]);
        pTimerReviving[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        TogglePlayerControllable(playerid, true);
        ShowPlayerFooter(playerid, "~r~EMS:~w~ Treatment telah selesai");

        AccountData[playerid][pHead] = 100;
        AccountData[playerid][pPerut] = 100;
        AccountData[playerid][pRHand] = 100;
        AccountData[playerid][pLHand] = 100;
        AccountData[playerid][pRFoot] = 100;
        AccountData[playerid][pLFoot] = 100;
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;
        
        new Float:Health;
        GetPlayerHealth(playerid, Health);

        Health += 10;
        if(Health > 100) {
            Health = 100.0;
        }

        SetPlayerHealthEx(playerid, Health);

        static Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/20;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward EMSReviving(playerid, targetid);
public EMSReviving(playerid, targetid)
{
    if(!IsPlayerConnected(playerid))    
    {
        KillTimer(pTimerReviving[playerid]);
        pTimerReviving[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInjured(targetid))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak pingsan!");
        KillTimer(pTimerReviving[playerid]);
        pTimerReviving[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 10)
    {
        KillTimer(pTimerReviving[playerid]);
        pTimerReviving[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            
        if(AccountData[targetid][pInjured])
        {
            AccountData[targetid][pInjured] = false;
            AccountData[targetid][pInjuredTime] = 0;
            AccountData[targetid][pHunger] = 80;
            AccountData[targetid][pThirst] = 80;
            AccountData[targetid][pStress] = 0;
            SetPlayerHealthEx(targetid, 100.0);

            ClearAnimations(targetid, 1);
            SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
            StopLoopingAnim(targetid);
            TogglePlayerControllable(playerid, true);

            ShowTDdeathHapp(playerid, false);
        }

        AccountData[playerid][EMSDuringReviving] = false;
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil merevive seseorang");
        ShowItemBox(playerid, "REMOVED 1x", "MEDKIT", 11738);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/10;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

/*DialogPages:EmsSetRank(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota EMS District !");
    if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Komisi Disiplin untuk mengakses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 3 ORDER BY `Char_FactionRank` DESC");
    new rows = cache_num_rows();
    if(rows)
    {
        cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
        cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak dapat mengatur jabatan sendiri!");
        if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengatur jabatan rank diatasmu!");
        ShowPlayerDialog(playerid, DIALOG_RANK_SET_EMS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
        "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
        1. Training\n\
        2. Perawat\n\
        3. Dokter Umum\n\
        4. Dokter Spesialis\n\
        5. Komisi Disiplin\n\
        6. Komisi Umum\n\
        7. SEKBEN\n\
        8. Direktur SDM\n\
        9. Direktur Keilmuan\n\
        10.Wadir Utam\n\
        11.Direktur Utama", "Set", "Batal");
    }
    return 1;
}

DialogPages:EmsKickMember(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota EMS District !");
    if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Komisi Disiplin untuk mengakses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 3 ORDER BY `Char_FactionRank` DESC");
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
        mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_OwnerID`=%d AND `PVeh_Faction` = 3", pidrow);
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
                        if(PlayerVehicle[pvid][pVehFaction] == FACTION_EMS)
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
                if(AccountData[i][pDutyEms])
                    AccountData[i][pDutyEms] = false;
                if(AccountData[i][pUsingUniform])
                    AccountData[i][pUsingUniform] = false;
                SetPlayerSkin(i, AccountData[i][pSkin]);
                ShowTDN(i, NOTIFICATION_WARNING, "Anda telah dikeluarkan dari faction EMS District !");
            }
        }
        mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`=0, `Char_FactionRank`=0, `Char_UsingUniform`=0 WHERE `pID`=%d", pidrow);
        mysql_tquery(g_SQL, icsr);
        format(kckstr, sizeof(kckstr), "Anda telah berhasil menendang anggota:\n\
        Nama: %s\n\
        Rank: %s\n\
        Last Online: %s", fckname, EMSRank[fckrank], fcklastlogin);
        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota",
        kckstr, "Tutup", "");
        
        AccountData[playerid][pTempSQLFactMemberID] = -1;
        AccountData[playerid][pTempSQLFactRank] = 0;
    }
    return 1;
}*/

forward OnEMSDeposit(playerid);
public OnEMSDeposit(playerid)
{
    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyimpan item");
    FactionBrankas[playerid][factionBrankasID] = 0;
    FactionBrankas[playerid][factionBrankasTemp] = EOS;
    FactionBrankas[playerid][factionBrankasModel] = 0;
    FactionBrankas[playerid][factionBrankasQuant] = 0;
    return 1;
}
