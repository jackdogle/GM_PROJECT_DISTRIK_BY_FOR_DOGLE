#include <YSI\y_hooks>

stock IsSweeperVehicle(vehicleid)
{
    for(new i = 0; i < sizeof(SweeperVehicles); i ++)
    {
        if(vehicleid == SweeperVehicles[i]) return 1;
    }
    return 0;
}

new Float:SweeperPoint[][] = 
{
    {639.8176,-1491.2795,14.3365},
    {650.0420,-1408.3289,13.1259},
    {780.5126,-1408.0054,13.0957},
    {933.1622,-1407.6581,12.9953},
    {1061.0597,-1383.4935,13.2501},
    {1073.4880,-1284.2584,13.1079},
    {1193.0846,-1294.1486,13.1071},
    {1194.1467,-1413.4940,12.9332},
    {1182.6061,-1568.6561,13.0847},
    {1022.8121,-1569.8163,13.1157},
    {849.7322,-1598.2372,13.1157},
    {751.5304,-1584.2633,13.5005},
    {640.5300,-1570.9209,15.1846},
    {616.4615,-1514.8971,14.7153}
};

hook OnGameModeInit()
{
    SweeperVehicles[0] = AddStaticVehicleEx(574, 599.8531, -1506.0258, 14.7921, 270.7113, 1, 1, 60000);
	SweeperVehicles[1] = AddStaticVehicleEx(574, 599.9737, -1509.2354, 14.7736, 265.4801, 1, 1, 60000);
	SweeperVehicles[2] = AddStaticVehicleEx(574, 599.8913, -1512.1049, 14.7723, 267.0818, 1, 1, 60000);
    for(new i = 0; i < sizeof(SweeperVehicles); i ++)
    {
        VehicleCore[SweeperVehicles[i]][vCoreFuel] = MAX_FUEL_FULL;
        SetVehicleNumberPlate(SweeperVehicles[i], "SWEEPER");
        SetValidVehicleHealth(SweeperVehicles[i], 1000.0);
    }
    CreateDynamicPickup(1239, 23, 600.2407, -1514.8455, 15.0275 + 0.15, -1, -1, -1, 10.0);
    CreateDynamic3DTextLabel(""DEEPSKYBLUE1"[Sweeper Point]", -1, 600.2407, -1514.8455, 15.0275 + 1.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(DurringSweeping[playerid])
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(IsSweeperVehicle(vehicleid))
        {
            SetVehicleToRespawn(vehicleid);
            VehicleCore[vehicleid][vCoreFuel] = MAX_FUEL_FULL;
            SetValidVehicleHealth(vehicleid, 1000.0);
        }
    }
    return 1;
}

hook OnPlayerExitVehicle(playerid, vehicleid)
{
    if(DurringSweeping[playerid] && IsSweeperVehicle(vehicleid))
    {
        SetVehicleToRespawn(vehicleid);
        VehicleCore[vehicleid][vCoreFuel] = MAX_FUEL_FULL;
        SetValidVehicleHealth(vehicleid, 1000.0);
        SendClientMessage(playerid, -1, "[i] Anda turun dari kendaraan, anda gagal mengerjakan tugas sebagai Street Cleaning ( Sweeper )");
        DurringSweeping[playerid] = false;
        SweeperIndex[playerid] = 0;
        DisablePlayerCheckpoint(playerid);
    }
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(IsSweeperVehicle(vehicleid))
        {
            if(!DurringSweeping[playerid])
            {
                if(AccountData[playerid][pSweeperTime] > 0)
                    return ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Anda harus menunggu %d menit sebelum bekerja kembali!", AccountData[playerid][pSweeperTime]/60)), RemovePlayerFromVehicle(playerid);
                
                ShowPlayerDialog(playerid, DIALOG_SWEEPER_START, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Sweeper Sidejob", "Apakah anda ingin memulai tugas sweeper?\
                \nAnda harus membersihkan jalanan sesuai dengan checkpoint yang ada", "Iya", "Tidak");
            }
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_SWEEPER_START:
        {
            if(!response) return RemovePlayerFromVehicle(playerid);

            DurringSweeping[playerid] = true;
            SweeperIndex[playerid] = 0;
            SetPlayerCheckpoint(playerid, SweeperPoint[SweeperIndex[playerid]][0], SweeperPoint[SweeperIndex[playerid]][1], SweeperPoint[SweeperIndex[playerid]][2], 4.0);
            SwitchVehicleEngine(GetPlayerVehicleID(playerid), true);
            AccountData[playerid][pSweeperTime] = 1800;

            new query[255];
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_SweeperDelay`=1800 WHERE `pID`=%d", AccountData[playerid][pID]);
            mysql_tquery(g_SQL, query);
        }
    }
    return 1;
}

hook OnPlayerEnterCP(playerid)
{
    if(DurringSweeping[playerid] && IsSweeperVehicle(GetPlayerVehicleID(playerid)))
    {
        if(SweeperIndex[playerid] < 13)
        {
            SweeperIndex[playerid] ++;
            SetPlayerCheckpoint(playerid, SweeperPoint[SweeperIndex[playerid]][0], SweeperPoint[SweeperIndex[playerid]][1], SweeperPoint[SweeperIndex[playerid]][2], 4.0);
            PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
            GiveMoney(playerid, 80);
            ShowItemBox(playerid, "Received $80", "Uang", 1212);
        }
        else 
        {
            SweeperIndex[playerid] = -1;
            DurringSweeping[playerid] = false;
            new vehid = GetPlayerVehicleID(playerid);
            SetVehicleToRespawn(vehid);
            VehicleCore[vehid][vCoreFuel] = MAX_FUEL_FULL;
            SetValidVehicleHealth(vehid, 1000.0);
            DisablePlayerCheckpoint(playerid);
            SendClientMessage(playerid, -1, "[i] Anda mendapatkan "GREEN"$1040"WHITE" dari hasil pekerjaan sweeper. dan anda mendapatkan bonus sebesar "GREEN"$950");
            GiveMoney(playerid, 950);
            ShowItemBox(playerid, "Received $950", "Uang", 1212);
        }
    }
    return 1;
}

ptask VehicleSweeperSpeed[1000](playerid) 
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(DurringSweeping[playerid] && IsSweeperVehicle(vehicleid)) 
    {
        SetVehicleSpeedCap(vehicleid, 35.0);
    }
    return 1;
}