#include <YSI\y_hooks>

#define IsForkliftWorking(%0)       forklift_working[%0]
#define SetForkliftWorking(%0,%1)   forklift_working[%0] = %1

new STREAMER_TAG_CP:ForkliftCheckpoint[MAX_PLAYERS],
    STREAMER_TAG_OBJECT:ForkliftObject[MAX_VEHICLES],
    bool:forklift_working[MAX_PLAYERS] = {false, ...},
    ForkliftIndex[MAX_PLAYERS] = {0, ...},
    ForkliftCreate[MAX_PLAYERS] = {0, ...},
    pTimerForklift[MAX_PLAYERS] = {-1, ...},
    ForkliftVehicleID[MAX_PLAYERS] = {RETURN_INVALID_VEHICLE_ID};


IsForkliftVehicles(vehicleid)
{
    for (new i = 0; i < sizeof(ForkliftVehicles); i++)
    {
        if(vehicleid == ForkliftVehicles[i]) return 1;
    }
    return 0;
}

new Float:ForkliftPoint[][] = 
{
    {-1547.7629,123.4576,3.5547}, //memuat
    {-1751.0033,-164.9045,3.5547}, //memuat
    {-1606.1606,167.8583,3.5547} //memuat
};

CancelForklift(playerid, vehicleid)
{
    if(IsForkliftWorking(playerid))
    {
        ForkliftVehicleID[playerid] = RETURN_INVALID_VEHICLE_ID;
        ForkliftIndex[playerid] = 0;
        ForkliftCreate[playerid] = 0;
        KillTimer(pTimerForklift[playerid]);
        pTimerForklift[playerid] = -1;
        SetForkliftWorking(playerid, false);

        SetVehicleToRespawn(vehicleid);
        VehicleCore[vehicleid][vCoreFuel] = MAX_FUEL_FULL;
        SetValidVehicleHealth(vehicleid, 1000.0);
        if(DestroyDynamicCP(ForkliftCheckpoint[playerid])) ForkliftCheckpoint[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        if(DestroyDynamicObject(ForkliftObject[vehicleid])) ForkliftObject[vehicleid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    pTimerForklift[playerid] = -1;
    ForkliftIndex[playerid] = 0;
    ForkliftCreate[playerid] = 0;
    ForkliftVehicleID[playerid] = RETURN_INVALID_VEHICLE_ID;
    SetForkliftWorking(playerid, false);
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(IsForkliftWorking(playerid))
    {
        ForkliftIndex[playerid] = 0;
        ForkliftCreate[playerid] = 0;
        SetVehicleToRespawn(ForkliftVehicleID[playerid]);
        VehicleCore[ForkliftVehicleID[playerid]][vCoreFuel] = MAX_FUEL_FULL;
        SetValidVehicleHealth(ForkliftVehicleID[playerid], 1000.0);
        if(DestroyDynamicCP(ForkliftCheckpoint[playerid])) ForkliftCheckpoint[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        if(DestroyDynamicObject(ForkliftObject[ForkliftVehicleID[playerid]])) ForkliftObject[ForkliftVehicleID[playerid]] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        ForkliftVehicleID[playerid] = RETURN_INVALID_VEHICLE_ID;
        KillTimer(pTimerForklift[playerid]);
    }
    return 1;
}

hook OnScriptInit()
{
    ForkliftVehicles[0] = AddStaticVehicleEx(530, -1716.9142, -60.3579, 3.3186, 131.4505, 0, 0, 60000, 0);
    ForkliftVehicles[1] = AddStaticVehicleEx(530, -1714.6615, -62.4159, 3.3159, 130.9259, 0, 0, 60000, 0);
    for(new i = 0; i < sizeof(ForkliftVehicles); i++)
    {
        VehicleCore[ForkliftVehicles[i]][vCoreFuel] = MAX_FUEL_FULL;
        SetValidVehicleHealth(ForkliftVehicles[i], 1000.0);
        SetVehicleNumberPlate(ForkliftVehicles[i], "FORKLIFT");
    }
    return 1;
}

hook OnPlayerExitVehicle(playerid, vehicleid)
{
    if(IsForkliftWorking(playerid) && IsForkliftVehicles(GetPlayerVehicleID(playerid)))
    {
        CancelForklift(playerid, ForkliftVehicleID[playerid]);
        SendClientMessageEx(playerid, X11_ARWIN, "[Forklift]: Anda turun dari kendaraan, anda gagal mengerjakan tugas sebagai forklifter");
    }
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(newstate == PLAYER_STATE_DRIVER && !IsForkliftWorking(playerid) && IsForkliftVehicles(vehicleid))
    {
        if(!AccountData[playerid][pForkliftTime])
        {
            SetCameraBehindPlayer(playerid);
            ShowPlayerDialog(playerid, DIALOG_FORKLIFT_START, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Forklift Sidejob",
            "Apakah anda ingin memulai tugas forklift?\nAnda akan menerima bayaran setelah membongkar 10 create", "Iya", "Tidak");
        }
        else
        {
            ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Anda harus menunggu %d menit untuk bekerja kembali!", AccountData[playerid][pForkliftTime]/60));
            RemovePlayerFromVehicle(playerid);
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_FORKLIFT_START:
        {
            if(response)
            {
                ForkliftVehicleID[playerid] = GetPlayerVehicleID(playerid);
                ForkliftIndex[playerid] = 1; // Ambil
                ForkliftCreate[playerid] = 0;
                SetForkliftWorking(playerid, true);

                ForkliftCheckpoint[playerid] = CreateDynamicCP(-1731.7854, 216.6169, 3.5547, 3.0, 0, 0, playerid, 500.0, -1, 0);
                ShowPlayerFooter(playerid, "~g~Sidejob Forklift: ~w~Pergi dan angkut ~y~10~n~~y~crate~w~ ke tempat yang telah ditandai~n~dengan ~r~icon~w~ pada map!", 5000);
            }
            else
            {
                Info(playerid, "Anda menolak bekerja sebagai Forklifter!");
                return RemovePlayerFromVehicle(playerid);
            }
        }
    }
    return 1;
}

hook OnPlayerEnterRaceCP(playerid)
{
    if(IsForkliftWorking(playerid) && IsForkliftVehicles(GetPlayerVehicleID(playerid)) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        if(ForkliftIndex[playerid] == 3)
        {
            DisablePlayerRaceCheckpoint(playerid);
            GiveMoney(playerid, 1550);
            ShowItemBox(playerid, "Received $1,550", "Uang", 1212);
            CancelForklift(playerid, ForkliftVehicleID[playerid]);

            AccountData[playerid][pForkliftTime] = 1800;
            new query[255];
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_ForkliftDelay`=1800 WHERE `pID`=%d", AccountData[playerid][pID]);
            mysql_tquery(g_SQL, query);
        }
    }
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP: checkpointid)
{
    if(IsForkliftWorking(playerid) && IsForkliftVehicles(GetPlayerVehicleID(playerid)))
    {
        if(checkpointid == ForkliftCheckpoint[playerid] && ForkliftIndex[playerid] == 1)
        {
            AccountData[playerid][ActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGANGKUT");
            ShowProgressBar(playerid);

            pTimerForklift[playerid] = SetTimerEx("TakingCreate", 1000, true, "dd", playerid, ForkliftVehicleID[playerid]);
            TogglePlayerControllable(playerid, false);
        }
        if(checkpointid == ForkliftCheckpoint[playerid] && ForkliftIndex[playerid] == 2)
        {
            AccountData[playerid][ActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMBONGKAR MUATAN");
            ShowProgressBar(playerid);

            pTimerForklift[playerid] = SetTimerEx("DropCreate", 1000, true, "dd", playerid, ForkliftVehicleID[playerid]);
            TogglePlayerControllable(playerid, false);
        }
    }
    return 1;
}

forward TakingCreate(playerid, VID);
public TakingCreate(playerid, VID)
{
    if(VID == -1) return 0;
    if(ForkliftIndex[playerid] != 1) return 0;

    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerForklift[playerid]);
        pTimerForklift[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInDynamicCP(playerid, ForkliftCheckpoint[playerid]))
    {
        KillTimer(pTimerForklift[playerid]);
        pTimerForklift[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        TogglePlayerControllable(playerid, true);
        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda menjauh dari Checkpoint!");
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerForklift[playerid]);
        pTimerForklift[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        TogglePlayerControllable(playerid, true);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 12)
    {
        KillTimer(pTimerForklift[playerid]);
        pTimerForklift[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        TogglePlayerControllable(playerid, true);
        ForkliftObject[VID] = CreateDynamicObject(2912, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0);
        AttachDynamicObjectToVehicle(ForkliftObject[VID], VID, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0);

        if(DestroyDynamicCP(ForkliftCheckpoint[playerid])) 
            ForkliftCheckpoint[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

        new rands = Random(sizeof(ForkliftPoint));
        ForkliftCheckpoint[playerid] = CreateDynamicCP(ForkliftPoint[rands][0], ForkliftPoint[rands][1], ForkliftPoint[rands][2], 3.0, 0, 0, playerid, 500.0, -1, 0);
        ForkliftIndex[playerid] = 2; // Bongkar
        ShowPlayerFooter(playerid, "~g~Sidejob Forklift: ~w~Bawa ~y~crate~w~ ke tempat~n~bongkar muatan yang telah ditandai~n~dengan ~r~icon~w~ pada map!", 5000);
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/12;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward DropCreate(playerid, VID);
public DropCreate(playerid, VID)
{
    if(VID == -1) return 0;
    if(ForkliftIndex[playerid] != 2) return 0;

    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerForklift[playerid]);
        pTimerForklift[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInDynamicCP(playerid, ForkliftCheckpoint[playerid]))
    {
        KillTimer(pTimerForklift[playerid]);
        pTimerForklift[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        TogglePlayerControllable(playerid, true);
        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda menjauh dari Checkpoint!");
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerForklift[playerid]);
        pTimerForklift[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        TogglePlayerControllable(playerid, true);
        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang pingsan!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pTimerForklift[playerid]);
        pTimerForklift[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        TogglePlayerControllable(playerid, true);
        if(DestroyDynamicObject(ForkliftObject[VID])) ForkliftObject[VID] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        if(DestroyDynamicCP(ForkliftCheckpoint[playerid])) ForkliftCheckpoint[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        ForkliftCreate[playerid] ++;

        if(ForkliftCreate[playerid] < 10)
        {
            ForkliftCheckpoint[playerid] = CreateDynamicCP(-1731.7854, 216.6169, 3.5547, 3.0, 0, 0, playerid, 500.0, -1, 0);
            ForkliftIndex[playerid] = 1;
            ShowPlayerFooter(playerid, sprintf("~y~%d/10 crate telah dimuat!", ForkliftCreate[playerid]), 5000);
        }
        else
        {
            ForkliftIndex[playerid] = 3; // Finish
            SetPlayerRaceCheckpoint(playerid, 1, -1729.4452,-58.9427,3.5547, -1729.4452,-58.9427,3.5547, 5.0);
            ShowPlayerFooter(playerid, "~g~sidejob Forklift:~y~ 10 crate~w~ sudah termuat semua~n~kembali ke ~r~tanda~w~ dimap!", 5000);
        }
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

task ForkliftSpeedUpdate[1000](playerid)
{
    if (IsValidVehicle(ForkliftVehicles[0]))
    {
        SetVehicleSpeedCap(ForkliftVehicles[0], 30.0);
    }
    if (IsValidVehicle(ForkliftVehicles[1]))
    {
        SetVehicleSpeedCap(ForkliftVehicles[1], 30.0);
    }
    return 1;
}