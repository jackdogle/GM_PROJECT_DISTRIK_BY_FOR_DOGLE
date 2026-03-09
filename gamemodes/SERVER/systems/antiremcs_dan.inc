#include <YSI\y_hooks>

hook OnGameModeInit()
{
    MapAndreas_Init(MAP_ANDREAS_MODE_FULL, "scriptfiles/SAFull.hmap");
    return 1;
}

hook OnGameModeExit()
{
    MapAndreas_Unload();
    return 1;
}

new VehicleDestroyed = 136;
IRPC:VehicleDestroyed(playerid, BitStream:bs)
{
    new vehicleid;

    BS_ReadUint16(bs, vehicleid);

    if (GetVehicleModel(vehicleid) < 400)
    {
        SendAdminMessage(X11_DARKORANGE, "Anticheat debug: RPC VehicleDestroyed detected. Player: (%d) %s | vehicleid: %d", playerid, ReturnName(playerid), vehicleid);
        return 0;
    }

    return OnVehicleRequestDeath(vehicleid, playerid);
}

forward OnVehicleRequestDeath(vehicleid, killerid);
public OnVehicleRequestDeath(vehicleid, killerid)
{
    if(!AccountData[killerid][pSpawned])
        return 0;
    
    new Float:X, Float:Y, Float:Z, Float:health;
    GetVehiclePos(vehicleid, X, Y, Z);
    MapAndreas_FindZ_For2DCoord(X, Y, Z);
    GetVehicleHealth(vehicleid, health);
    
    // If car above the water MapAndreas return a height 0.0
    if(GetPlayerState(killerid) != PLAYER_STATE_ONFOOT && GetPlayerVehicleID(killerid) == vehicleid)
        return 0;

    if (health >= 350.0 && Z != 0.0)
    {
        SendAdminMessage(X11_RED, "[AntiCheat]: "YELLOW"%s(%d)"LIGHTGREY" diduga menggunakan Rem.cs kepada "YELLOW"[VID: %d] [%s]", ReturnName(killerid), killerid, vehicleid, GetVehicleName(vehicleid));
        printf("RPC OnVehicleRequestDeath detected. Killer: (%d) %s | vehicleid: %d | Z: %.2f | health: %.2f", killerid, killerid != INVALID_PLAYER_ID ? ReturnName(killerid) : "(Unknown)", vehicleid, Z, health);
    }
    return 1;
}