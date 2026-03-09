GetPlayerWayPointStatus(playerid)
{
    return playerWaypoint[playerid];
}

SetPlayerWayPointStatus(playerid, bool:status)
{
    if(IsPlayerConnected(playerid) && AccountData[playerid][pSpawned])
    {
        playerWaypoint[playerid] = status;
    }
    return 1;
}

stock RemoveDriverMarkerPoint(playerid)
{
    if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
    {
        new 
            driverid = GetVehicleDriverID(GetPlayerVehicleID(playerid));
        
        if(driverid != INVALID_PLAYER_ID && GetPlayerWayPointStatus(driverid))
        {
            RemovePlayerMapIcon(driverid, 20);
            ShowPlayerFooter(driverid, sprintf("~y~%s~w~ telah ~r~menghapus~w~ tanda pada map!", ReturnName(playerid)));
            SetPlayerWayPointStatus(driverid, false);
        }
    }
    return 1;
}

SetDriverMarkerPoint(playerid, Float:zX, Float:zY, Float:zZ)
{
    if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
    {
        new 
            driverid = GetVehicleDriverID(GetPlayerVehicleID(playerid));

        if(driverid != INVALID_PLAYER_ID)
        {
            SetPlayerMapIcon(driverid, 20, zX, zY, zZ, 0, X11_LIGHTGREEN, MAPICON_GLOBAL);
            ShowPlayerFooter(driverid, sprintf("~y~%s~w~ telah menandai map!", ReturnName(playerid)));
            Info(driverid, "Right click pada map untuk menghilangkan waypoint yang aktif!");
            SetPlayerWayPointStatus(driverid, true);
        }
    }
    return 1;
}