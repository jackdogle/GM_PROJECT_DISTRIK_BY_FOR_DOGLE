#include <YSI\y_hooks>

hook OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    if(GetPlayerWayPointStatus(playerid))
    {
        RemovePlayerMapIcon(playerid, 20);
    }

    if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
    {
        SetDriverMarkerPoint(playerid, fX, fY, fZ); 
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    playerWaypoint[playerid] = false;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    RemovePlayerMapIcon(playerid, 20);
    playerWaypoint[playerid] = false;
    return 1;
}