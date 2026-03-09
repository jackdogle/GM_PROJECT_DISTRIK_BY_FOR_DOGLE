#include <YSI\y_hooks>

enum KARGOSTUFF {
    STREAMER_TAG_AREA:KargoStartArea,
    STREAMER_TAG_MAP_ICON:KargoIcon,
    STREAMER_TAG_OBJECT:PertaminaObject,
    Text3D:kargoLabel,

    KargoTrailer,
    KargoFailTimer,
    
    bool:TrailerKargoAttached,
    bool: KargoStarted
};
new PlayerKargoVars[MAX_PLAYERS][KARGOSTUFF];

new KargoIndex[MAX_PLAYERS] = {-1, ...};
new TimerKargo[MAX_PLAYERS] = {-1, ...};
new KargoSaveCP[MAX_PLAYERS] = {-1, ...};

stock GetKargoCheckpointPos(index, &Float:x, &Float:y, &Float:z)
{
    if(index < 0 || index >= MAX_KARGO) return 0;
    x = KargoCheckpoint[index][0];
    y = KargoCheckpoint[index][1];
    z = KargoCheckpoint[index][2];
    return 1;
}

stock LoadVarsKargo(playerid)
{
    UnloadVarsKargo(playerid);

    PlayerKargoVars[playerid][KargoStartArea] = CreateDynamicSphere(-1677.9747, 33.3353, 3.5547, 2.0, 0, 0, playerid);
    PlayerKargoVars[playerid][kargoLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Mulai Kargo", -1, -1677.9747, 33.3353, 3.5547 + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid);
    PlayerKargoVars[playerid][KargoIcon] = CreateDynamicMapIcon(-1677.9747, 33.3353, 3.5547, 51, -1, -1, -1, playerid, 9999.0, MAPICON_GLOBAL, -1, 1);
}

stock UnloadVarsKargo(playerid)
{
    if(IsValidDynamic3DTextLabel(PlayerKargoVars[playerid][kargoLabel]))
        DestroyDynamic3DTextLabel(PlayerKargoVars[playerid][kargoLabel]);
    PlayerKargoVars[playerid][kargoLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(IsValidDynamicArea(PlayerKargoVars[playerid][KargoStartArea]))
        DestroyDynamicArea(PlayerKargoVars[playerid][KargoStartArea]);
    PlayerKargoVars[playerid][KargoStartArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    if(IsValidDynamicMapIcon(PlayerKargoVars[playerid][KargoIcon]))
        DestroyDynamicMapIcon(PlayerKargoVars[playerid][KargoIcon]);
    PlayerKargoVars[playerid][KargoIcon] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
}

hook OnPlayerConnect(playerid)
{
    if(!PlayerKargoVars[playerid][KargoStarted])
    {
        PlayerKargoVars[playerid][KargoStarted] = false;
        KargoIndex[playerid] = -1;
        KargoSaveCP[playerid] = -1;
        PlayerKargoVars[playerid][KargoTrailer] = -1;
        PlayerKargoVars[playerid][PertaminaObject] = -1;
    }
    TimerKargo[playerid] = -1;
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pJob] == JOB_KARGO)
        {
            if(IsPlayerInDynamicArea(playerid, PlayerKargoVars[playerid][KargoStartArea]))
            {
                if(PlayerKargoVars[playerid][KargoStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda dalam pengantaran kargo, mohon segera diantarkan!");

                Dialog_Show(playerid, DialogKargoRute, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Kargo", ""WHITE"Pertamina\n"VERONA_ARWIN"Barang", "Pilih", "Batal");
            }
        }
    }
    return 1;
}

// -------------------------- DIALOG
Dialog:DialogKargoRute(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
    if(AccountData[playerid][pJob] != JOB_KARGO) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pengantar kargo!");
    switch(listitem)
    {
        case 0:
        {
            new rands = RandomEx(1, 20);
            new Float:cx, Float:cy, Float:cz;
            switch(rands)
            {
                case 1..9: GetKargoCheckpointPos(0, cx, cy, cz); // Solar
                case 10..15: GetKargoCheckpointPos(1, cx, cy, cz); // Dexlite
                case 16..20: GetKargoCheckpointPos(2, cx, cy, cz); // Pertamax
            }

            // Spawn Trailer & Job Vehicle
            PlayerKargoVars[playerid][KargoTrailer] = CreateVehicle(584, -1703.6455, 15.3515, 4.1600, 316.0175, -1, -1, 60000, 0);
            CreateJobVehicle(playerid, 515, -1703.6455, 15.3515, 4.1600, 316.0175, -1, -1, true, false);

            // Spawn Muatan
            PlayerKargoVars[playerid][PertaminaObject] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(PlayerKargoVars[playerid][PertaminaObject], 0, "{000000}PERTAMINA", 130, "Arial", 60, 1, 0, 0, 1);
            AttachDynamicObjectToVehicle(PlayerKargoVars[playerid][PertaminaObject], PlayerKargoVars[playerid][KargoTrailer], -1.085, -0.650, 0.765, 0.0, -39.799, 180.0);

            PlayerKargoVars[playerid][PertaminaObject] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
            SetDynamicObjectMaterialText(PlayerKargoVars[playerid][PertaminaObject], 0, "{000000}PERTAMINA", 130, "Arial", 60, 1, 0, 0, 1);
            AttachDynamicObjectToVehicle(PlayerKargoVars[playerid][PertaminaObject], PlayerKargoVars[playerid][KargoTrailer], 1.093, -1.080, 0.749, 0.0, -42.999, 0.0);

            // Fuel & Engine
            new randsbensin = RandomEx(55, 100);
            VehicleCore[JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle]][vCoreFuel] = randsbensin;
            SwitchVehicleEngine(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], true);

            // Set Checkpoint & Info
            SetPlayerRaceCheckpoint(playerid, 1, cx, cy, cz, cx, cy, cz, 5.0);
            KargoIndex[playerid] = 1;
            PlayerKargoVars[playerid][KargoStarted] = true;
            KargoRemakeUsed[playerid] = 0;
            KargoSaveCP[playerid] = (rands <= 9) ? 0 : (rands <= 15 ? 1 : 2); 

            SendClientMessageEx(playerid, -1, ""YELLOW"[i]"WHITE_E": Silahkan ikuti tanda untuk mengangkut muatan "YELLOW"Bahan Bakar"WHITE" di %s.", GetLocation(cx, cy, cz));
            AttachTrailerToVehicle(PlayerKargoVars[playerid][KargoTrailer], JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle]);
        }
        case 1:
        {
            new rands = RandomEx(1, 20);
            switch(rands)
            {
                case 1..9:
                {
                    PlayerKargoVars[playerid][KargoTrailer] = CreateVehicle(450, -1703.6455, 15.3515, 4.1600, 316.0175, -1, -1, 60000, 0);
                    CreateJobVehicle(playerid, 515, -1703.6455, 15.3515, 4.1600, 316.0175, -1, -1, true, false);

                    new randsbensin = RandomEx(55, 100);
                    VehicleCore[JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle]][vCoreFuel] = randsbensin;
                    SwitchVehicleEngine(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], true);

                    SendClientMessageEx(playerid, -1, ""YELLOW"[i]"WHITE_E": Silahkan ikuti tanda untuk mengankut mengangkut muatan "YELLOW"Batu Bara."WHITE" yang terletak di %s.",
                    GetLocation(-1515.8962,2532.1870,55.6918));
                    SetPlayerRaceCheckpoint(playerid, 1, -1515.8962,2532.1870,55.6918, -1515.8962,2532.1870,55.6918, 5.0);
                    KargoIndex[playerid] = 1;

                    PlayerKargoVars[playerid][KargoStarted] = true;
                }
                case 10..15:
                {
                    PlayerKargoVars[playerid][KargoTrailer] = CreateVehicle(450, -1703.6455, 15.3515, 4.1600, 316.0175, -1, -1, 60000, 0);
                    CreateJobVehicle(playerid, 515, -1703.6455, 15.3515, 4.1600, 316.0175, -1, -1, true, false);

                    new randsbensin = RandomEx(55, 100);
                    VehicleCore[JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle]][vCoreFuel] = randsbensin;
                    SwitchVehicleEngine(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], true);

                    SendClientMessageEx(playerid, -1, ""YELLOW"[i]"WHITE_E": Silahkan ikuti tanda untuk mengankut mengangkut muatan "YELLOW"Televisi."WHITE" yang terletak di %s.",
                    GetLocation(1947.1000, -2121.3438, 13.5470));
                    SetPlayerRaceCheckpoint(playerid, 1, 1947.1000, -2121.3438, 13.5470, 1947.1000, -2121.3438, 13.5470, 5.0);
                    KargoIndex[playerid] = 1;

                    PlayerKargoVars[playerid][KargoStarted] = true;
                }
                case 16..20:
                {
                    PlayerKargoVars[playerid][KargoTrailer] = CreateVehicle(450, -1703.6455, 15.3515, 4.1600, 316.0175, -1, -1, 60000, 0);
                    CreateJobVehicle(playerid, 515, -1703.6455, 15.3515, 4.1600, 316.0175, -1, -1, true, false);

                    new randsbensin = RandomEx(55, 100);
                    VehicleCore[JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle]][vCoreFuel] = randsbensin;
                    SwitchVehicleEngine(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], true);

                    SendClientMessageEx(playerid, -1, ""YELLOW"[i]"WHITE_E": Silahkan ikuti tanda untuk mengankut mengangkut muatan "YELLOW"Pakaian Branded."WHITE" yang terletak di %s.",
                    GetLocation(-750.8494,1585.2804,26.9609));
                    SetPlayerRaceCheckpoint(playerid, 1, -750.8494,1585.2804,26.9609, -750.8494,1585.2804,26.9609, 5.0);
                    KargoIndex[playerid] = 1;

                    PlayerKargoVars[playerid][KargoStarted] = true;
                }
            }
            AttachTrailerToVehicle(PlayerKargoVars[playerid][KargoTrailer], JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle]);
        }
    }
    return 1;
}

/*hook OnPlayerEnterRaceCP(playerid)
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(PlayerKargoVars[playerid][KargoStarted] && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && GetPlayerJob(playerid) == JOB_KARGO)
    {
        if(GetVehicleModel(vehicleid) == 515)
        {
            if(KargoIndex[playerid] == 1)
            {
                AccountData[playerid][ActivityTime] = 1;
                TimerKargo[playerid] = SetTimerEx("MuatKargo", 1000, true, "d", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMUAT KARGO");
                ShowProgressBar(playerid);
                TogglePlayerControllable(playerid, 0);
            }

            if(KargoIndex[playerid] == 2)
            {
                DisablePlayerRaceCheckpoint(playerid);
                GiveMoney(playerid, 1250);
                ShowItemBox(playerid, "Received $1250", "UANG", 1212);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengantarkan kargo!");
                GivePlayerXP(playerid, DEFAULT_XP);

                DestroyJobVehicle(playerid);
                DestroyDynamicObject(PlayerKargoVars[playerid][PertaminaObject]);
                DestroyVehicle(PlayerKargoVars[playerid][KargoTrailer]);
                GivePlayerXP(playerid, DEFAULT_XP+50);

                KargoIndex[playerid] = -1;
                PlayerKargoVars[playerid][KargoStarted] = false;
            }
        }
    }
    return 1;
}*/

hook OnPlayerEnterRaceCP(playerid)
{
    new vehicleid = GetPlayerVehicleID(playerid);

    // Cek kondisi kargo aktif, driver, job kargo, dan kendaraan model 515
    if(!PlayerKargoVars[playerid][KargoStarted]) return 1;
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
    if(GetPlayerJob(playerid) != JOB_KARGO) return 1;
    if(GetVehicleModel(vehicleid) != 515) return 1;

    if(KargoIndex[playerid] == 1)
    {
        AccountData[playerid][ActivityTime] = 1;
        TimerKargo[playerid] = SetTimerEx("MuatKargo", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMUAT KARGO");
        ShowProgressBar(playerid);
        TogglePlayerControllable(playerid, 0);
    }

    if(KargoIndex[playerid] == 2)
    {
        DisablePlayerRaceCheckpoint(playerid);
        GiveMoney(playerid, 1250);
        ShowItemBox(playerid, "Received $1250", "UANG", 1212);
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengantarkan kargo!");
        GivePlayerXP(playerid, DEFAULT_XP);

        DestroyJobVehicle(playerid);
        DestroyDynamicObject(PlayerKargoVars[playerid][PertaminaObject]);
        DestroyVehicle(PlayerKargoVars[playerid][KargoTrailer]);
        GivePlayerXP(playerid, DEFAULT_XP+50);

        KargoIndex[playerid] = -1;
        KargoSaveCP[playerid] = -1;
        PlayerKargoVars[playerid][KargoStarted] = false;
    }
    return 1;
}

hook OnPlayerLeaveRaceCP(playerid)
{
    if(PlayerKargoVars[playerid][KargoStarted] && KargoIndex[playerid] == 1)
    {
        KillTimer(TimerKargo[playerid]);
        TimerKargo[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(PlayerKargoVars[playerid][KargoStarted]) {
        if(DestroyDynamicObject(PlayerKargoVars[playerid][PertaminaObject]))
            PlayerKargoVars[playerid][PertaminaObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        DestroyJobVehicle(playerid);
        DestroyVehicle(PlayerKargoVars[playerid][KargoTrailer]);
        
        PlayerKargoVars[playerid][KargoTrailer] = INVALID_VEHICLE_ID;
    }
    KillTimer(TimerKargo[playerid]);
    TimerKargo[playerid] = -1;
    return 1;
}

hook OnVehicleSpawn(vehicleid)
{
    foreach(new i : Player) if (PlayerKargoVars[i][KargoStarted])
    {
        if (AccountData[i][pJobVehicle] != 0)
        {
            if (vehicleid == JobVehicle[AccountData[i][pJobVehicle]][Vehicle])
            {
                DestroyJobVehicle(i);
                AccountData[i][pJobVehicle] = 0;

                if (IsValidVehicle(PlayerKargoVars[i][KargoTrailer]))
                {
                    DestroyVehicle(PlayerKargoVars[i][KargoTrailer]);
                    PlayerKargoVars[i][KargoTrailer] = INVALID_VEHICLE_ID;
                }

                PlayerKargoVars[i][KargoStarted] = false;
                KargoIndex[i] = -1;
                TimerKargo[i] = -1;
                KargoSaveCP[i] = -1;
                Warning(i, "Kargo anda hancur total. Misi pengantaran anda gagal!");
            }
        }
    }
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    if(PlayerKargoVars[playerid][KargoStarted])
    {   
        if(IsValidVehicle(PlayerKargoVars[playerid][KargoTrailer]))
            DestroyVehicle(PlayerKargoVars[playerid][KargoTrailer]);

        DestroyJobVehicle(playerid);   
        PlayerKargoVars[playerid][KargoStarted] = false;
        SendClientMessageEx(playerid, -1, ""YELLOW"KARGO:"WHITE_E" Anda pingsan, pengantaran kargo dibatalkan!");
    }
    return 1;
}

// ------------------------------ Callback Func
forward MuatKargo(playerid);
public MuatKargo(playerid)
{
    if(!IsPlayerConnected(playerid))   
    {
        KillTimer(TimerKargo[playerid]);
        TimerKargo[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(IsPlayerInjured(playerid))
    {
        KillTimer(TimerKargo[playerid]);
        TimerKargo[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        TogglePlayerControllable(playerid, 1);
        return 0;
    }

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
    {
        KillTimer(TimerKargo[playerid]);
        TimerKargo[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        TogglePlayerControllable(playerid, 1);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 50)
    {
        KillTimer(TimerKargo[playerid]);
        TimerKargo[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        SendClientMessageEx(playerid, -1, ""YELLOW"[i]"WHITE_E": Bawa mautan kargo kembali ke pelabuhan "YELLOW"Tanjung Priok. "WHITE_E"Ikutilah tanda yang diberikan!");
        SetPlayerRaceCheckpoint(playerid, 1, -1547.1716, 125.6070, 3.5547, -1547.1716, 125.6070, 3.5547, 5.0);
        KargoIndex[playerid] = 2;
        TogglePlayerControllable(playerid, 1);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/50;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
hook OnTrailerHooked(playerid,vehicleid,trailerid)
{
    if(PlayerKargoVars[playerid][KargoStarted])
    {
        if(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle] != INVALID_VEHICLE_ID)
        {
            if(trailerid == PlayerKargoVars[playerid][KargoTrailer])
            {
                PlayerKargoVars[playerid][KargoFailTimer] = 0;
                SendClientMessageEx(playerid, -1, ""VERONADOT"Trailer terpasang kembali, silahkan melanjutkan perjalanan.");
            }
        }
    }
}

hook OnTrailerUnhooked(playerid,vehicleid,trailerid)
{
    if(PlayerKargoVars[playerid][KargoStarted])
    {
        if(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle] != INVALID_VEHICLE_ID)
        {
            if(trailerid == PlayerKargoVars[playerid][KargoTrailer])
            {
                PlayerKargoVars[playerid][KargoFailTimer] = 60;
                SendClientMessageEx(playerid, -1, ""VERONADOT"Trailer terlepas! anda memiliki waktu "RED"60 detik"WHITE" untuk menghubungkan kembali!");
            }
        }
    }
    return 1;
}

// ----------------------------- Timering Kargo
ptask KargoVehicle_Update[1000](playerid)
{
    // Pastikan misi kargo telah dimulai
    if (PlayerKargoVars[playerid][KargoStarted])
    {
        // Periksa jika timer masih aktif
        if (PlayerKargoVars[playerid][KargoFailTimer] > 0)
        {
            PlayerKargoVars[playerid][KargoFailTimer]--;
            static text[12];
            format(text, 12, "~y~%d", PlayerKargoVars[playerid][KargoFailTimer]);
            // Update timer pada player
            GameTextForPlayer(playerid, text, 1000, 4);
            
            // Ketika timer mencapai 0, hentikan misi
            if (PlayerKargoVars[playerid][KargoFailTimer] == 0)
            {
                DisablePlayerRaceCheckpoint(playerid);
                PlayerKargoVars[playerid][KargoStarted] = false;
                PlayerKargoVars[playerid][KargoFailTimer] = 0;
                KargoIndex[playerid] = -1;
                KargoSaveCP[playerid] = -1;

                // Hancurkan objek dan kendaraan jika valid
                if (IsValidDynamicObject(PlayerKargoVars[playerid][PertaminaObject]))
                {
                    DestroyDynamicObject(PlayerKargoVars[playerid][PertaminaObject]);
                }

                // Hancurkan kendaraan yang terkait dengan misi
                DestroyJobVehicle(playerid);

                if (IsValidVehicle(PlayerKargoVars[playerid][KargoTrailer]))
                {
                    DestroyVehicle(PlayerKargoVars[playerid][KargoTrailer]);
                }

                // Kirim pesan kegagalan misi
                SendClientMessageEx(playerid, -1, "~YELLOW~[i]~WHITE_E: Misi anda dalam pengantaran kargo gagal, karena trailer lepas dari truk!");
            }
        }
    }
    return 1;
}

CMD:startkargo(playerid)
{
    if(AccountData[playerid][pJob] != JOB_KARGO)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pengantar kargo!");
        return 1;
    }

    if(!PlayerKargoVars[playerid][KargoStarted])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Belum ada kargo yang bisa dilanjutkan.");
        return 1;
    }

    if(KargoRemakeUsed[playerid])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah menggunakan startkargo, silahkan lanjutkan pekerjaan Anda.");
        return 1;
    }
    ShowPlayerDialog(playerid, DialogKargoRemake, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Kargo", ""GRAY"1. Lanjutkan Kargo\n2. Reset Kargo", "Pilih", "Batal");
    KargoRemakeUsed[playerid] = 1;

    return 1;
}
