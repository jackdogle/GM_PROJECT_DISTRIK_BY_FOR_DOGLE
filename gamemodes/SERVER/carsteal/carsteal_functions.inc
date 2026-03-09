#include <YSI\y_hooks>

enum e_carstealdata
{
    STREAMER_TAG_ACTOR:carstealActor,
    STREAMER_TAG_AREA:carstealStartArea,
};
new Steal_Stuffs[e_carstealdata];

//define
#define IsDurringCarSteal(%0)           DurringCarSteal[%0]
#define SetIsDurringCarSteal(%0,%1)     DurringCarSteal[%0] = %1

//pvars
new g_CarStealTimer;
new STREAMER_TAG_3D_TEXT_LABEL:CarStealLabel[MAX_PLAYERS];
new STREAMER_TAG_3D_TEXT_LABEL:CarStealVehLabel[MAX_PLAYERS];
new STREAMER_TAG_CP:CarStealStoreParts[MAX_PLAYERS];
new STREAMER_TAG_AREA:CarStealStoreVeh[MAX_PLAYERS];
new CarStealVehicle[MAX_PLAYERS] = {INVALID_VEHICLE_ID, ...};
new bool:DurringCarSteal[MAX_PLAYERS] = {false, ...};
new CarStealTimer[MAX_PLAYERS] = {0, ...};
new LabelTimer[MAX_PLAYERS] = {-1, ...};
new UncoveredParts[MAX_PLAYERS] = {0, ...};
new pUncoveredTimer[MAX_PLAYERS] = {-1, ...};

hook OnScriptInit()
{
    Steal_Stuffs[carstealActor] = CreateDynamicActor(115, 931.33, 2066.61, 10.82, 0.0, true, 100.0, 0, 0, -1, 30.0, -1, 1);
    Steal_Stuffs[carstealStartArea] = CreateDynamicSphere(931.33, 2066.61, 10.82, 5.0, 0, 0, -1, 0);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    DurringCarSteal[playerid] = false;
    CarStealVehicle[playerid] = INVALID_VEHICLE_ID;
    CarStealTimer[playerid] = 0;
    LabelTimer[playerid] = -1;
    UncoveredParts[playerid] = 0;
    pUncoveredTimer[playerid] = -1;
    pUpgradeBagasiTimer[playerid] = -1;
    isFixingVehicle[playerid] = 0;
	AccountData[playerid][FixVehTimer] = -1;
    FixVehicleTarget[playerid] = 0;
    SetPVarInt(playerid, "HoldParts", false);
    CarStealLabel[playerid] = CreateDynamic3DTextLabel(""GREEN"Gangster:"WHITE" Apakah kamu ingin melakukan tugas dariku?\nJika kamu berani melakukannya saya akan memberikan kamu upah setimpal\n"YELLOW"CMD:"WHITE"/carsteal", -1, 931.33, 2066.61, 10.82 + 1.5, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid, 10.0, -1, 0);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(IsDurringCarSteal(playerid))
    {
        SetIsDurringCarSteal(playerid, false);
        if(IsValidVehicle(CarStealVehicle[playerid])) DestroyVehicle(CarStealVehicle[playerid]);
        CarStealVehicle[playerid] = INVALID_VEHICLE_ID;
        
        foreach(new i : Player) if (IsPlayerConnected(i)) if (AccountData[i][pFaction] == FACTION_POLISI && AccountData[i][pDutyPD])
        {
            if(AccountData[i][pSuspectTimer] != -1)
            {
                KillTimer(AccountData[i][pSuspectTimer]);
                AccountData[i][pSuspectTimer] = -1;
                DisablePlayerRaceCheckpoint(i);
            }
        }
    }
    KillTimer(pUncoveredTimer[playerid]);
    KillTimer(LabelTimer[playerid]);
    KillTimer(pUpgradeBagasiTimer[playerid]);
    KillTimer(AccountData[playerid][FixVehTimer]);
    LabelTimer[playerid] = -1;
    pUncoveredTimer[playerid] = -1;
    pUpgradeBagasiTimer[playerid] = -1;
    UncoveredParts[playerid] = 0;
    isFixingVehicle[playerid] = 0;
	AccountData[playerid][FixVehTimer] = -1;
    FixVehicleTarget[playerid] = 0;
    
    if(DestroyDynamicArea(CarStealStoreVeh[playerid])) CarStealStoreVeh[playerid] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
    if(DestroyDynamicCP(CarStealStoreParts[playerid])) CarStealStoreParts[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
    if(DestroyDynamic3DTextLabel(CarStealLabel[playerid])) CarStealLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    if(DestroyDynamic3DTextLabel(CarStealVehLabel[playerid])) CarStealVehLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    return 1;
}

hook OnVehicleSpawn(vehicleid)
{
    foreach(new i : Player) if (SQL_IsCharacterLogged(i))
    {
        if(IsDurringCarSteal(i) && CarStealVehicle[i] == vehicleid)
        {
            SetIsDurringCarSteal(i, false);
            if(IsValidVehicle(CarStealVehicle[i])) DestroyVehicle(CarStealVehicle[i]);
            CarStealVehicle[i] = INVALID_VEHICLE_ID;
            KillTimer(pUncoveredTimer[i]);
            KillTimer(LabelTimer[i]);
            LabelTimer[i] = -1;
            pUncoveredTimer[i] = -1;
            UncoveredParts[i] = 0;
            CarStealTimer[i] = 0;
            
            if(DestroyDynamicArea(CarStealStoreVeh[i])) CarStealStoreVeh[i] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
            if(DestroyDynamicCP(CarStealStoreParts[i])) CarStealStoreParts[i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
            if(DestroyDynamic3DTextLabel(CarStealVehLabel[i])) CarStealVehLabel[i] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            Info(i, "Kendaraan pencurian telah hancur, anda dinyatakan gagal dalam misi ini!");
        }
    }
    return 1;
}

FUNC::UpdateGangLabel(playerid)
{
    KillTimer(LabelTimer[playerid]);
    LabelTimer[playerid] = -1;
    UpdateDynamic3DTextLabelText(CarStealLabel[playerid], -1, ""GREEN"Gangster:"WHITE" Apakah kamu ingin melakukan tugas dariku?\nJika kamu berani melakukannya saya akan memberikan kamu upah setimpal\n"YELLOW"CMD:"WHITE"/carsteal");
    return 1;
}

static Float: StorePartsPoint[4][4] = {
    {951.4497, 2083.5347, 10.8203, 357.2103},
    {974.0211, 2078.6543, 10.8203, 264.5541},
    {974.3754, 2067.5457, 10.8203, 2.4084},
    {956.1997, 2068.2485, 10.8203, 174.8432}
};

CMD:csinfo(playerid, params[])
{
    new hours, minutes, seconds;
    GetElapsedTime(CarStealTimer[playerid]--, hours, minutes, seconds);
    if(IsDurringCarSteal(playerid))
    {
        new frmxt[255], Float:x, Float:y, Float:z;
        GetVehiclePos(CarStealVehicle[playerid], x, y, z);
        if(GetPVarInt(playerid, "CsInfo") == 1) // Sultan
        {
            format(frmxt, sizeof(frmxt), ""WHITE"Carilah kendaraan ini:\n\nModel: "YELLOW"Sultan\n"WHITE"Lokasi: "YELLOW"%s\n\n"WHITE"Segera temukan dan berikan kepada Gangster sebelum waktu selesai "ORANGE"(%02d Menit %02d Detik)", GetLocation(x, y, z), minutes, seconds);
            ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Cari Kendaraan", frmxt, "Tutup", "");
        }
        else if(GetPVarInt(playerid, "CsInfo") == 2) // Bulet
        {
            format(frmxt, sizeof(frmxt), ""WHITE"Carilah kendaraan ini:\n\nModel: "YELLOW"Bullet\n"WHITE"Lokasi: "YELLOW"%s\n\n"WHITE"Segera temukan dan berikan kepada Gangster sebelum waktu selesai "ORANGE"(%02d Menit %02d Detik)", GetLocation(x, y, z), minutes, seconds);
            ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Cari Kendaraan", frmxt, "Tutup", "");
        }
        else if(GetPVarInt(playerid, "CsInfo") == 3) // Jester
        {
            format(frmxt, sizeof(frmxt), ""WHITE"Carilah kendaraan ini:\n\nModel: "YELLOW"Jester\n"WHITE"Lokasi: "YELLOW"%s\n\n"WHITE"Segera temukan dan berikan kepada Gangster sebelum waktu selesai "ORANGE"(%02d Menit %02d Detik)", GetLocation(x, y, z), minutes, seconds);
            ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Cari Kendaraan", frmxt, "Tutup", "");
        }
        else if(GetPVarInt(playerid, "CsInfo") == 4) // Cheetah
        {
            format(frmxt, sizeof(frmxt), ""WHITE"Carilah kendaraan ini:\n\nModel: "YELLOW"Cheetah\n"WHITE"Lokasi: "YELLOW"%s\n\n"WHITE"Segera temukan dan berikan kepada Gangster sebelum waktu selesai "ORANGE"(%02d Menit %02d Detik)", GetLocation(x, y, z), minutes, seconds);
            ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Cari Kendaraan", frmxt, "Tutup", "");
        }
    }
    else
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dalam misi pencurian kendaraan!");
    }
    return 1;
}

CMD:carsteal(playerid, params[])
{
    new pdcount, emscount;
    foreach(new i : Player) if (AccountData[i][IsLoggedIn])
    {
        if(AccountData[i][pDutyPD]) pdcount++;
        if(AccountData[i][pDutyEms]) emscount++;
    }
    if(pdcount <= 4 && emscount <= 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 Polisi Duty & 2 EMS Duty");

    if(g_CarStealTimer != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Carsteal sedang delay %s", RemainingTime(g_CarStealTimer)));

    if(IsDurringCarSteal(playerid))
    {
        UpdateDynamic3DTextLabelText(CarStealLabel[playerid], -1, ""GREEN"Gangster:"WHITE" What The Fuck?, Kerjakan saja dulu tugas yang ku berikan sebelumnya!\n"WHITE"Bukan malah kau menanyakan tugas lagi!");
        if(LabelTimer[playerid] != -1)
        {
            KillTimer(LabelTimer[playerid]);
            LabelTimer[playerid] = -1;
        }
        LabelTimer[playerid] = SetTimerEx("UpdateGangLabel", 6000, false, "d", playerid);
    }

    if(IsPlayerInDynamicArea(playerid, Steal_Stuffs[carstealStartArea]))
    {
        if(!PlayerHasItem(playerid, "Linggis"))
        {
            UpdateDynamic3DTextLabelText(CarStealLabel[playerid], -1, ""GREEN"Gangster:"WHITE" Kamu tidak memiliki linggis!\nIngin membelinya dariku?");
            ApplyDynamicActorAnimation(Steal_Stuffs[carstealActor], "GANGS", "prtial_gngtlkA", 4.1, 0, 0, 0, 0, 5000);
            ShowPlayerDialog(playerid, DIALOG_CARSTEAL_SHOP, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Steal Shop",
            "Nama Item\tHarga\
            \nLinggis\t$1000\
            \n"GRAY"Letter T\t"GRAY"$1000", "Pilih", "Batal");
            if(LabelTimer[playerid] != -1)
            {
                KillTimer(LabelTimer[playerid]);
                LabelTimer[playerid] = -1;
            }
            LabelTimer[playerid] = SetTimerEx("UpdateGangLabel", 6000, false, "d", playerid);
        }
        else if(!PlayerHasItem(playerid, "Kunci T"))
        {
            UpdateDynamic3DTextLabelText(CarStealLabel[playerid], -1, ""GREEN"Gangster:"WHITE" Kamu tidak memiliki Kunci T!\nIngin membelinya dariku?");
            ApplyDynamicActorAnimation(Steal_Stuffs[carstealActor], "GANGS", "prtial_gngtlkA", 4.1, 0, 0, 0, 0, 5000);
            ShowPlayerDialog(playerid, DIALOG_CARSTEAL_SHOP, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Steal Shop",
            "Nama Item\tHarga\
            \nLinggis\t$1000\
            \n"GRAY"Letter T\t"GRAY"$1000", "Pilih", "Batal");
            if(LabelTimer[playerid] != -1)
            {
                KillTimer(LabelTimer[playerid]);
                LabelTimer[playerid] = -1;
            }
            LabelTimer[playerid] = SetTimerEx("UpdateGangLabel", 6000, false, "d", playerid);
        }
        else
        {
            new Float:x, Float:y, Float:z;
            new rands = RandomEx(1, 145);
            new shstr[598];
            switch(rands)
            {
                case 1..81:
                {
                    CarStealVehicle[playerid] = CreateVehicle(560, 2640.1260, -2228.1013, 16.0020, 89.8542, 126, 1, 60000, 0);
                    GetVehiclePos(CarStealVehicle[playerid], x, y, z);

                    VehicleCore[CarStealVehicle[playerid]][vCoreFuel] = MAX_FUEL_FULL;
                    SetValidVehicleHealth(CarStealVehicle[playerid], 1000.0);
                    format(shstr, sizeof(shstr), ""GREEN"Gangster"WHITE": Oke, dengarkan saya! Sebuah "LIGHTGREEN"Sultan"WHITE" sedang diparkirkan di sekitar %s\n"WHITE"Ambil dan bawalah kemari, kamu punya waktu selama 1 jam. Waspadalah terhadap polisi!\n"YELLOW"CMD:"WHITE" '/csinfo'", GetLocation(x, y, z));
                    UpdateDynamic3DTextLabelText(CarStealLabel[playerid], -1, shstr);
                    ApplyDynamicActorAnimation(Steal_Stuffs[carstealActor], "GANGS", "prtial_gngtlkA", 4.1, 0, 0, 0, 0, 5000);
                    SetIsDurringCarSteal(playerid, true);
                    SetPVarInt(playerid, "CsInfo", 1); // Sultan
                    CarStealTimer[playerid] = 3600; //Player Timer Delay
                    g_CarStealTimer = gettime() + 3600; // Global Timer Delay
                    if(LabelTimer[playerid] != -1)
                    {
                        KillTimer(LabelTimer[playerid]);
                        LabelTimer[playerid] = -1;
                    }
                    LabelTimer[playerid] = SetTimerEx("UpdateGangLabel", 6000, false, "d", playerid);
                }
                case 82..91:
                {
                    CarStealVehicle[playerid] = CreateVehicle(541, -2202.3462, -2338.8181, 30.2633, 54.6390, 126, 1, 60000, 0);
                    GetVehiclePos(CarStealVehicle[playerid], x, y, z);

                    VehicleCore[CarStealVehicle[playerid]][vCoreFuel] = MAX_FUEL_FULL;
                    SetValidVehicleHealth(CarStealVehicle[playerid], 1000.0);
                    UpdateDynamic3DTextLabelText(CarStealLabel[playerid], -1, sprintf(""GREEN"Gangster"WHITE": Oke, dengarkan saya! Sebuah "LIGHTGREEN"Bullet"WHITE" sedang diparkirkan di sekitar %s\n"WHITE"Ambil dan bawalah kemari, kamu punya waktu selama 1 jam. Waspadalah terhadap polisi!\n"YELLOW"CMD"WHITE": '/csinfo'", GetLocation(x, y, z)));
                    ApplyDynamicActorAnimation(Steal_Stuffs[carstealActor], "GANGS", "prtial_gngtlkA", 4.1, 0, 0, 0, 0, 5000);
                    SetIsDurringCarSteal(playerid, true);
                    SetPVarInt(playerid, "CsInfo", 2); // Bullet
                    CarStealTimer[playerid] = 3600; //Player Timer Delay
                    g_CarStealTimer = gettime() + 3600; // Global Timer Delay
                    if(LabelTimer[playerid] != -1)
                    {
                        KillTimer(LabelTimer[playerid]);
                        LabelTimer[playerid] = -1;
                    }
                    LabelTimer[playerid] = SetTimerEx("UpdateGangLabel", 6000, false, "d", playerid);
                }
                case 92..121:
                {
                    CarStealVehicle[playerid] = CreateVehicle(559, -1473.6002, 2626.9861, 55.5413, 358.9156, 126, 1, 60000, 0);
                    GetVehiclePos(CarStealVehicle[playerid], x, y, z);

                    VehicleCore[CarStealVehicle[playerid]][vCoreFuel] = MAX_FUEL_FULL;
                    SetValidVehicleHealth(CarStealVehicle[playerid], 1000.0);
                    UpdateDynamic3DTextLabelText(CarStealLabel[playerid], -1, sprintf(""GREEN"Gangster"WHITE": Oke, dengarkan saya! Sebuah "LIGHTGREEN"Jester"WHITE" sedang diparkirkan di sekitar %s\n"WHITE"Ambil dan bawalah kemari, kamu punya waktu selama 1 jam. Waspadalah terhadap polisi!\n"YELLOW"CMD"WHITE": '/csinfo'", GetLocation(x, y, z)));
                    ApplyDynamicActorAnimation(Steal_Stuffs[carstealActor], "GANGS", "prtial_gngtlkA", 4.1, 0, 0, 0, 0, 5000);
                    SetIsDurringCarSteal(playerid, true);
                    SetPVarInt(playerid, "CsInfo", 3); // Jester
                    CarStealTimer[playerid] = 3600; //Player Timer Delay
                    g_CarStealTimer = gettime() + 3600; // Global Timer Delay
                    if(LabelTimer[playerid] != -1)
                    {
                        KillTimer(LabelTimer[playerid]);
                        LabelTimer[playerid] = -1;
                    }
                    LabelTimer[playerid] = SetTimerEx("UpdateGangLabel", 6000, false, "d", playerid);
                }
                case 122..145:
                {
                    CarStealVehicle[playerid] = CreateVehicle(415, -2524.3005, 305.7137, 27.6205, 69.5191, 126, 1, 60000, 0);
                    GetVehiclePos(CarStealVehicle[playerid], x, y, z);

                    VehicleCore[CarStealVehicle[playerid]][vCoreFuel] = MAX_FUEL_FULL;
                    SetValidVehicleHealth(CarStealVehicle[playerid], 1000.0);
                    UpdateDynamic3DTextLabelText(CarStealLabel[playerid], -1, sprintf(""GREEN"Gangster"WHITE": Oke, dengarkan saya! Sebuah "LIGHTGREEN"Cheetah"WHITE" sedang diparkirkan di sekitar %s\n"WHITE"Ambil dan bawalah kemari, kamu punya waktu selama 1 jam. Waspadalah terhadap polisi!\n"YELLOW"CMD"WHITE": '/csinfo'", GetLocation(x, y, z)));
                    ApplyDynamicActorAnimation(Steal_Stuffs[carstealActor], "GANGS", "prtial_gngtlkA", 4.1, 0, 0, 0, 0, 5000);
                    SetIsDurringCarSteal(playerid, true);
                    SetPVarInt(playerid, "CsInfo", 4); // Cheetah
                    CarStealTimer[playerid] = 3600; //Player Timer Delay
                    g_CarStealTimer = gettime() + 3600; // Global Timer Delay
                    if(LabelTimer[playerid] != -1)
                    {
                        KillTimer(LabelTimer[playerid]);
                        LabelTimer[playerid] = -1;
                    }
                    LabelTimer[playerid] = SetTimerEx("UpdateGangLabel", 6000, false, "d", playerid);
                }
            }
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsDurringCarSteal(playerid))
        {
            new vehid = GetNearestVehicle(playerid);
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
            if(GetPVarInt(playerid, "HoldParts")) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang membawa parts kendaraan!, letakkan terlebih dahulu!");
            if(vehid == CarStealVehicle[playerid])
            {
                if(!UncoveredParts[playerid])
                {
                    AccountData[playerid][ActivityTime] = 1;
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMBONGKAR");
                    ShowProgressBar(playerid);

                    ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
                    pUncoveredTimer[playerid] = SetTimerEx("UncoveredTire", 1000, true, "dd", playerid, CarStealVehicle[playerid]);
                }
                else if(UncoveredParts[playerid] == 3)
                {
                    AccountData[playerid][ActivityTime] = 1;
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMBONGKAR");
                    ShowProgressBar(playerid);

                    ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
                    pUncoveredTimer[playerid] = SetTimerEx("UncoveredBBumper", 1000, true, "dd", playerid, CarStealVehicle[playerid]);
                }
                else if(UncoveredParts[playerid] == 5)
                {
                    AccountData[playerid][ActivityTime] = 1;
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMBONGKAR");
                    ShowProgressBar(playerid);

                    ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
                    pUncoveredTimer[playerid] = SetTimerEx("UncoveredFBumper", 1000, true, "dd", playerid, CarStealVehicle[playerid]);
                }
                else if(UncoveredParts[playerid] == 7)
                {
                    AccountData[playerid][ActivityTime] = 1;
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMBONGKAR");
                    ShowProgressBar(playerid);

                    ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                    pUncoveredTimer[playerid] = SetTimerEx("UncoveredDoors", 1000, true, "dd", playerid, CarStealVehicle[playerid]);
                }
            }
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_CARSTEAL_SHOP:
        {
            if(!response)
            {
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
                return 1;
            }
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            switch(listitem)
            {
                case 0: //
                {
                    if(AccountData[playerid][pMoney] < 1000)
                    {
                        UpdateDynamic3DTextLabelText(CarStealLabel[playerid], -1, ""GREEN"Gangster:"WHITE" Bagaimana kamu bisa membeli barang dariku jika uangmu saja tidak cukup?");
                        ApplyDynamicActorAnimation(Steal_Stuffs[carstealActor], "GANGS", "prtial_gngtlkA", 4.1, 0, 0, 0, 0, 5000);
                        if(LabelTimer[playerid] != -1)
                        {
                            KillTimer(LabelTimer[playerid]);
                            LabelTimer[playerid] = -1;
                        }
                        LabelTimer[playerid] = SetTimerEx("UpdateGangLabel", 6000, false, "d", playerid);
                    }
                    else
                    {
                        TakeMoney(playerid, 1000);
                        Inventory_Add(playerid, "Linggis", 18634);
                        ShowItemBox(playerid, "Received 1x", "Linggis", 18634);
                        UpdateDynamic3DTextLabelText(CarStealLabel[playerid], -1, ""GREEN"Gangster"WHITE": Ini dia barangnya! terimakasih sudah membeli, jaga barang itu jangan sampai pihak kepolisian mengetahui");
                        if(LabelTimer[playerid] != -1)
                        {
                            KillTimer(LabelTimer[playerid]);
                            LabelTimer[playerid] = -1;
                        }
                        LabelTimer[playerid] = SetTimerEx("UpdateGangLabel", 6000, false, "d", playerid);
                    }
                }
                case 1: 
                {
                    if(AccountData[playerid][pMoney] < 1000)
                    {
                        UpdateDynamic3DTextLabelText(CarStealLabel[playerid], -1, ""GREEN"Gangster:"WHITE" Bagaimana kamu bisa membeli barang dariku jika uangmu saja tidak cukup?");
                        ApplyDynamicActorAnimation(Steal_Stuffs[carstealActor], "GANGS", "prtial_gngtlkA", 4.1, 0, 0, 0, 0, 5000);
                        if(LabelTimer[playerid] != -1)
                        {
                            KillTimer(LabelTimer[playerid]);
                            LabelTimer[playerid] = -1;
                        }
                        LabelTimer[playerid] = SetTimerEx("UpdateGangLabel", 6000, false, "d", playerid);
                    }
                    else
                    {
                        TakeMoney(playerid, 1000);
                        Inventory_Add(playerid, "Kunci T", 334);
                        ShowItemBox(playerid, "Received 1x", "Kunci T", 334);
                        UpdateDynamic3DTextLabelText(CarStealLabel[playerid], -1, ""GREEN"Gangster"WHITE": Ini dia barangnya! terimakasih sudah membeli, jaga barang itu jangan sampai pihak kepolisian mengetahui");
                        if(LabelTimer[playerid] != -1)
                        {
                            KillTimer(LabelTimer[playerid]);
                            LabelTimer[playerid] = -1;
                        }
                        LabelTimer[playerid] = SetTimerEx("UpdateGangLabel", 6000, false, "d", playerid);
                    }
                }
            }
        }
        case DIALOG_RACE_PLAYER_COUNT:
        {
            gRaceTotalPlayers = (listitem == 0) ? 2 : (listitem == 1) ? 4 : 6;
            for(new i = 0; i < sizeof(gRacePlayers); i++)
            {
                gRacePlayers[i] = INVALID_PLAYER_ID;
            }
            ShowPlayerDialog(playerid, DIALOG_RACE_LAP_COUNT, DIALOG_STYLE_LIST, "Jumlah Lap", "Lap 1\nLap 2\nLap 3", "Pilih", "Batal");
        }
        case DIALOG_RACE_LAP_COUNT:
        {
            gRaceLapCount = listitem + 1;
            gRacePlayers[0] = playerid;
            ShowPlayerDialog(playerid, DIALOG_RACE_INVITE_PLAYER1, DIALOG_STYLE_INPUT, "Masukan ID pemain", "Contoh: 1", "Kirim", "Batal");
        }
        case DIALOG_RACE_INVITE_PLAYER1 .. DIALOG_RACE_INVITE_PLAYER6:
        {
            new targetid = strval(inputtext);
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID tidak valid");

            new invitedIndex = dialogid - DIALOG_RACE_INVITE_PLAYER1 + 1;
            if(invitedIndex >= sizeof(gRacePlayers)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot undangan penuh!");
            gRacePlayers[invitedIndex] = targetid;

            ShowPlayerDialog(targetid, DIALOG_RACE_CONFIRM_INVITE, DIALOG_STYLE_MSGBOX, "Race Invite", "Kamu diundang balapan, ketik /jointrace untuk ikut", "Siap", "");
            SendClientMessage(targetid, -1, "Gunakan "YELLOW_E"/joinrace "WHITE_E"untuk menerima undangan race");

            if(invitedIndex < gRaceTotalPlayers - 1)
            {
                ShowPlayerDialog(gRacePlayers[0], DIALOG_RACE_INVITE_PLAYER1 + invitedIndex, DIALOG_STYLE_INPUT, "Masukan ID pemain", "Contoh: 1", "Kirim", "Batal");
            }
            else
            {
                ShowRaceVehicleList(gRacePlayers[0]);
            }
        }
        case DIALOG_RACE_VEH_LIST:
        {
            if (!response) return 1;

            new selected = listitem;
            new vehicleSlot = selected + 1;
            new vid = ReturnPlayerVehID(playerid, vehicleSlot);

            if (vid == INVALID_VEHICLE_ID || PlayerVehicle[vid][pVehPhysic] == INVALID_VEHICLE_ID)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tidak tersedia atau belum di-spawn!");

            new slot = GetRaceSlotForPlayer(playerid);
            if (slot == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot balapan tidak ditemukan!");

            new vehicleid = PlayerVehicle[vid][pVehPhysic];
            SetVehiclePosition(playerid, vehicleid, gRaceSpawnPos[slot][0], gRaceSpawnPos[slot][1], gRaceSpawnPos[slot][2], gRaceSpawnPos[slot][3]);    
            SwitchVehicleEngine(vehicleid, true); 

            PutPlayerInVehicle(playerid, vehicleid, 0);
            TogglePlayerControllable(playerid, false);

            gRacePlayerReady[playerid] = true;
            if (AllRacersReady())
            {
                raceCountdown = 5;
                countdownTimer = SetTimer("RaceCountdown", 1000, true);
                for (new i = 0; i < gRaceTotalPlayers; i++)
                {
                    new id = gRacePlayers[i];
                    GameTextForPlayer(id, "~r~Countdown~n~Dimulai!", 2000, 3);
                    ShowTDBalapan(id, true);
                    PlayerTextDrawSetString(id, BalapanTD[id][11], "-");
                    PlayerTextDrawSetString(id, BalapanTD[id][18], "-");
                    PlayerTextDrawSetString(id, BalapanTD[id][19], "-");
                    PlayerTextDrawSetString(id, BalapanTD[id][20], "-");

                    PlayerTextDrawSetString(id, BalapanTD[id][12], "0/%d", gRaceLapCount);
                    PlayerTextDrawSetString(id, BalapanTD[id][21], "0/%d", gRaceLapCount);
                    PlayerTextDrawSetString(id, BalapanTD[id][22], "0/%d", gRaceLapCount);
                    PlayerTextDrawSetString(id, BalapanTD[id][23], "0/%d", gRaceLapCount);
                }
            }
        }
        case DIALOG_ADMIN_RACE_LAP_COUNT:
        {
            gAdminRaceLapCount = listitem + 1;
            ShowPlayerDialog(playerid, DIALOG_ADMIN_RACE_VEHICLE, DIALOG_STYLE_INPUT, "ID Kendaraan Balapan", "Masukkan model ID kendaraan (contoh: 411 untuk Infernus)", "Set", "Batal");
        }
        case DIALOG_ADMIN_RACE_VEHICLE:
        {
            gAdminRaceVehicleModel = strval(inputtext);
            if(gAdminRaceVehicleModel < 400 || gAdminRaceVehicleModel > 611)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "ID kendaraan tidak valid!");

            gAdminRaceActive = true;
            gAdminRaceTotalPlayers = 0;
            foreach (new i : Player)
                gAdminRacePlayers[i] = INVALID_PLAYER_ID;

            new msg[128];
            format(msg, sizeof(msg), ""YELLOW_E"[EVENT]: "WHITE_E"Admin "RED_E"%s "WHITE_E"telah membuat event balapan! Gunakan "YELLOW_E"/joinbalap "WHITE_E"untuk ikut!", AccountData[playerid][pAdminname]);
            SendClientMessageToAll(-1, msg);
        }
    }
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER && oldstate == PLAYER_STATE_ONFOOT)
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(vehicleid == CarStealVehicle[playerid])
        {
            if(!IsDurringCarSteal(playerid))
            {
                RemovePlayerFromVehicle(playerid);
                return Error(playerid, "Kendaraan ini tidak tersedia untuk anda!");
            }

            new Float:x, Float:y, Float:z;
            GetPlayerPos(playerid, x, y, z);
            foreach(new i : Player) if (SQL_IsCharacterLogged(i))
            {
                if(AccountData[i][pFaction] == FACTION_POLISI && AccountData[i][pDutyPD])
                {
                    SendClientMessageEx(i, X11_RED, "[EMERGENCY]: "WHITE"Telah terjadi pencurian kendaraan di daerah %s", GetLocation(x, y, z));
                    SendClientMessageEx(i, -1, "~> Lokasi terbaru akan di Update Setiap 5 Menit sekali, jangan sampai kehilangan jejak!");
                    SendClientMessageEx(i, -1, "~> Details: Jenis Kendaraan: "YELLOW"%s"WHITE" // Warna: Pink", GetVehicleName(vehicleid));
                    SetPlayerRaceCheckpoint(i, 1, x, y, z, 0.0, 0.0, 0.0, 5.0);
                    AccountData[i][pSuspectTimer] = SetTimerEx("TrackStealUpdate", 120000, true, "dd", playerid, i);
                }
            }
            SetPlayerRaceCheckpoint(playerid, 1, 933.1342, 2079.3425, 10.5437, 933.1342, 2079.3425, 10.5437, 5.0);
            TextDrawSetString(RobberyGlobalTD[3], "District ~n~Car Stealing");
            RobberyShowTD(playerid, "Bawa kendaraan ini kepada Gangster!");
            CarStealStoreVeh[playerid] = CreateDynamicSphere(933.1342, 2079.3425, 10.5437, 2.5, 0, 0, -1, 0);
        }
    }
    return 1;
}

forward TrackStealUpdate(playerid, policeid);
public TrackStealUpdate(playerid, policeid)
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    SetPlayerRaceCheckpoint(policeid, 1, x, y, z, 0.0, 0.0, 0.0, 5.0);
    pMapCP[policeid] = true;
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    if(areaid == CarStealStoreVeh[playerid] && IsDurringCarSteal(playerid))
    {
        DisablePlayerRaceCheckpoint(playerid);
        SwitchVehicleEngine(CarStealVehicle[playerid], false);
        LockVehicle(CarStealVehicle[playerid], true); //terkunci
        RemovePlayerFromVehicle(playerid);
        CarStealVehLabel[playerid] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Bongkar Ban", -1, 0.0, 0.0, 0.8, 15.0, INVALID_PLAYER_ID, CarStealVehicle[playerid], 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), playerid, 15.0, -1, 0);

        if(DestroyDynamicArea(CarStealStoreVeh[playerid]))
            CarStealStoreVeh[playerid] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

        foreach(new i : Player) if (AccountData[i][pSuspectTimer])
        {
            DisablePlayerRaceCheckpoint(i);
            KillTimer(AccountData[i][pSuspectTimer]);
            AccountData[i][pSuspectTimer] = -1;
            pMapCP[i] = false;
        }
    }
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(checkpointid == CarStealStoreParts[playerid] && IsDurringCarSteal(playerid))
    {
        if(UncoveredParts[playerid] == 2)
        {
            ApplyAnimation(playerid, "CARRY", "putdwn", 4.0,0,0,0,0,0,0);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);
            UncoveredParts[playerid] = 3;
            SetPVarInt(playerid, "HoldParts", false);

            if(DestroyDynamicCP(CarStealStoreParts[playerid]))
                CarStealStoreParts[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        }
        else if(UncoveredParts[playerid] == 4)
        {
            ApplyAnimation(playerid, "CARRY", "putdwn", 4.0,0,0,0,0,0,0);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);
            UncoveredParts[playerid] = 5;
            SetPVarInt(playerid, "HoldParts", false);

            if(DestroyDynamicCP(CarStealStoreParts[playerid]))
                CarStealStoreParts[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        }
        else if(UncoveredParts[playerid] == 6)
        {
            ApplyAnimation(playerid, "CARRY", "putdwn", 4.0,0,0,0,0,0,0);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);
            UncoveredParts[playerid] = 7;
            SetPVarInt(playerid, "HoldParts", false);

            if(DestroyDynamicCP(CarStealStoreParts[playerid]))
                CarStealStoreParts[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        }
        else if(UncoveredParts[playerid] == 8) // Selesai
        {
            ApplyAnimation(playerid, "CARRY", "putdwn", 4.0,0,0,0,0,0,0);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            RemovePlayerAttachedObject(playerid, 9);
            SetPVarInt(playerid, "HoldParts", false);
            UpdateDynamic3DTextLabelText(CarStealVehLabel[playerid], -1, "Bicaralah kepada "GREEN"Ganster"WHITE" untuk meminta hasil dari kerja kerasmu!");

            if(DestroyDynamicCP(CarStealStoreParts[playerid]))
                CarStealStoreParts[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
            
            CarStealStoreParts[playerid] = CreateDynamicCP(931.37, 2068.86, 10.82, 2.0, 0, 0, playerid, 10.0, -1, 0);
            UncoveredParts[playerid] = 9; // Selesai
        } 
        else if(UncoveredParts[playerid] == 9)
        {
            new rands = RandomEx(2500, 8000), shstr[225];
            format(shstr, sizeof(shstr), ""GREEN"Gangster:"WHITE" Kerja bagus bung! Aku hargai hasil perjuanganmu dengan uang haram sebesar "DARKGREEN"%s\n"WHITE"Datanglah kemari nanti jika inginkan tugas dariku lagi!", FormatMoney(rands));
            UpdateDynamic3DTextLabelText(CarStealLabel[playerid], -1, shstr);
            ApplyDynamicActorAnimation(Steal_Stuffs[carstealActor], "GANGS", "prtial_gngtlkA", 4.1, 0, 0, 0, 0, 5000);
            if(LabelTimer[playerid] != -1)
            {
                KillTimer(LabelTimer[playerid]);
                LabelTimer[playerid] = -1;
            }
            LabelTimer[playerid] = SetTimerEx("UpdateGangLabel", 6000, false, "d", playerid);

            AccountData[playerid][pRedMoney] += rands;
            ShowItemBox(playerid, "Removed 1x", "Linggis", 18636);
            ShowItemBox(playerid, "Removed 1x", "Kunci T", 334);
            ShowItemBox(playerid, sprintf("Received %s", FormatMoney(rands)), "Uang Merah", 1212);

            Inventory_Remove(playerid, "Linggis");
            Inventory_Remove(playerid, "Kunci T");

            if(DestroyDynamicCP(CarStealStoreParts[playerid]))
                CarStealStoreParts[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
            
            if(DestroyDynamic3DTextLabel(CarStealVehLabel[playerid]))
                CarStealVehLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            
            SetIsDurringCarSteal(playerid, false);
            UncoveredParts[playerid] = 0;
            foreach(new i : Player) if (IsPlayerConnected(i)) if (AccountData[i][pFaction] == FACTION_POLISI && AccountData[i][pDutyPD])
            {
                if(AccountData[i][pSuspectTimer] != -1)
                {
                    KillTimer(AccountData[i][pSuspectTimer]);
                    AccountData[i][pSuspectTimer] = -1;
                    DisablePlayerRaceCheckpoint(i);
                }
            }

            if(IsValidVehicle(CarStealVehicle[playerid])) DestroyVehicle(CarStealVehicle[playerid]);
            CarStealVehicle[playerid] = INVALID_VEHICLE_ID;
        }
    }
    return 1;
}

/* Func */
forward UncoveredDoors(playerid, vehicleid);
public UncoveredDoors(playerid, vehicleid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(GetNearestVehicleToPlayer(playerid, 5.0, false) != vehicleid)
    {
        Error(playerid, "Anda terlalu jauh dari kendaraan!");
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        Error(playerid, "Anda sedang pingsan!");
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
        SetPlayerAttachedObject(playerid, 9,2912,1,0.104, 0.363, -0.032, -91.000, 1.100, 86.500, 0.613, 0.542, 0.682);
        SetPVarInt(playerid, "HoldParts", true);
        UncoveredParts[playerid] = 8;

        if(DestroyDynamicCP(CarStealStoreParts[playerid]))    
            CarStealStoreParts[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        new rands = Random(sizeof(StorePartsPoint));
        CarStealStoreParts[playerid] = CreateDynamicCP(StorePartsPoint[rands][0], StorePartsPoint[rands][1], StorePartsPoint[rands][2], 3.0, 0, 0, playerid, 100.0, -1, 0);
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/15;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward UncoveredFBumper(playerid, vehicleid);
public UncoveredFBumper(playerid, vehicleid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(GetNearestVehicleToPlayer(playerid, 5.0, false) != vehicleid)
    {
        Error(playerid, "Anda terlalu jauh dari kendaraan!");
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        Error(playerid, "Anda sedang pingsan!");
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        UpdateDynamic3DTextLabelText(CarStealVehLabel[playerid], -1, ""GREEN"[Y]"WHITE" Bongkar Pintu");
        SetPlayerAttachedObject(playerid, 9, 1160, 6, 0.177, 0.253, 0.906, -179.7, -91.1, 0.0, 1, 1, 1);
        UncoveredParts[playerid] = 6;
        SetPVarInt(playerid, "HoldParts", true);

        if(DestroyDynamicCP(CarStealStoreParts[playerid]))    
            CarStealStoreParts[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        new rands = Random(sizeof(StorePartsPoint));
        CarStealStoreParts[playerid] = CreateDynamicCP(StorePartsPoint[rands][0], StorePartsPoint[rands][1], StorePartsPoint[rands][2], 3.0, 0, 0, playerid, 100.0, -1, 0);
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/15;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward UncoveredBBumper(playerid, vehicleid);
public UncoveredBBumper(playerid, vehicleid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(GetNearestVehicleToPlayer(playerid, 5.0, false) != vehicleid)
    {
        Error(playerid, "Anda terlalu jauh dari kendaraan!");
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        Error(playerid, "Anda sedang pingsan!");
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        UpdateDynamic3DTextLabelText(CarStealVehLabel[playerid], -1, ""GREEN"[Y]"WHITE" Bongkar Bumper Depan");
        SetPlayerAttachedObject(playerid, 9, 1160, 6, 0.177, 0.253, 0.906, -179.7, -91.1, 0.0, 1, 1, 1);
        UncoveredParts[playerid] = 4;
        SetPVarInt(playerid, "HoldParts", true);

        if(DestroyDynamicCP(CarStealStoreParts[playerid]))    
            CarStealStoreParts[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        new rands = Random(sizeof(StorePartsPoint));
        CarStealStoreParts[playerid] = CreateDynamicCP(StorePartsPoint[rands][0], StorePartsPoint[rands][1], StorePartsPoint[rands][2], 3.0, 0, 0, playerid, 100.0, -1, 0);
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/15;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward UncoveredTire(playerid, vehicleid);
public UncoveredTire(playerid, vehicleid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(GetNearestVehicleToPlayer(playerid, 5.0, false) != vehicleid)
    {
        Error(playerid, "Anda terlalu jauh dari kendaraan!");
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        Error(playerid, "Anda sedang pingsan!");
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pUncoveredTimer[playerid]);
        pUncoveredTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
        
        UpdateDynamic3DTextLabelText(CarStealVehLabel[playerid], -1, ""GREEN"[Y]"WHITE" Bongkar Bumper Belakang");
        SetPlayerAttachedObject(playerid, 9,1080,1,0.141, 0.497, 0.000, 0.000, -3.000, 92.200, 0.965, 0.502, 0.595);
        UncoveredParts[playerid] = 2;
        SetPVarInt(playerid, "HoldParts", true);

        if(DestroyDynamicCP(CarStealStoreParts[playerid]))    
            CarStealStoreParts[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        new rands = Random(sizeof(StorePartsPoint));
        CarStealStoreParts[playerid] = CreateDynamicCP(StorePartsPoint[rands][0], StorePartsPoint[rands][1], StorePartsPoint[rands][2], 3.0, 0, 0, playerid, 100.0, -1, 0);
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/15;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

ptask CarStealTimerUpdate[1000](playerid)
{
    if(!AccountData[playerid][pSpawned])
        return 0;

    if(AccountData[playerid][IsLoggedIn] && IsDurringCarSteal(playerid))
    {
        CarStealTimer[playerid] --;
        if(!CarStealTimer[playerid])
        {
            SetIsDurringCarSteal(playerid, false);
            if(IsValidVehicle(CarStealVehicle[playerid])) DestroyVehicle(CarStealVehicle[playerid]);
            CarStealVehicle[playerid] = INVALID_VEHICLE_ID;

            KillTimer(pUncoveredTimer[playerid]);
            KillTimer(LabelTimer[playerid]);
            LabelTimer[playerid] = -1;
            pUncoveredTimer[playerid] = -1;
            UncoveredParts[playerid] = 0;
            CarStealTimer[playerid] = 0;

            foreach(new i : Player) if (IsPlayerConnected(i)) if (AccountData[i][pFaction] == FACTION_POLISI && AccountData[i][pDutyPD])
            {
                if(AccountData[i][pSuspectTimer] != -1)
                {
                    KillTimer(AccountData[i][pSuspectTimer]);
                    AccountData[i][pSuspectTimer] = -1;
                    DisablePlayerRaceCheckpoint(i);
                }
            }
            
            DisablePlayerRaceCheckpoint(playerid);
            if(DestroyDynamicArea(CarStealStoreVeh[playerid])) CarStealStoreVeh[playerid] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
            if(DestroyDynamicCP(CarStealStoreParts[playerid])) CarStealStoreParts[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
            if(DestroyDynamic3DTextLabel(CarStealVehLabel[playerid])) CarStealVehLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            Warning(playerid, "Waktu misi pencurian telah habis, anda dinyatakan gagal dalam misi ini!");
        }
    }
    return 1;
}

ptask CarStealDelayUpdate[1000]()
{
    new currentTime = gettime();

    if (g_CarStealTimer != 0 && g_CarStealTimer <= currentTime)
    {
        g_CarStealTimer = 0;
        SendStaffMessage(X11_ARWIN, "[CarStealInfo] Waktu Car Steal telah di reset secara otomatis!");
    }

    return 1;
}
