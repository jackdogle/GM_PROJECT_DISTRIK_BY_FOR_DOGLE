/*
===========================================================
    Vehicle Accesories Script, Author : Revelt
===========================================================*/

#include <YSI\y_hooks>

hook OnPlayerConnect(playerid)
{
    Player_EditVehicleObject[playerid] = -1;
    Player_EditVehicleObjectSlot[playerid] = -1;
    Player_EditingObject[playerid] = 0;
}

hook OnGameModeInit()
{
    for (new i; i < sizeof(ColorList); i++) {
    format(color_string, sizeof(color_string), "%s{%06x}%03d %s", color_string, ColorList[i] >>> 8, i, ((i+1) % 16 == 0) ? ("\n") : (""));
    }

    for (new i; i < sizeof(FontNames); i++) {
        format(object_font, sizeof(object_font), "%s%s\n", object_font, FontNames[i]);
    }

    CreateDynamicPickup(1239, 23, 1103.7428, -1246.4520, 15.8362, 0, 0, -1, 15.0, -1, 0);
    CreateDynamicPickup(1239, 23, 1093.8877, -1246.2726, 15.8362, 0, 0, -1, 15.0, -1, 0);
    CreateDynamic3DTextLabel("Use '"YELLOW"/buymod"WHITE"' untuk membeli Aksesoris Kendaraan", -1, 1103.7428, -1246.4520, 15.8362, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
    CreateDynamic3DTextLabel("Use '"YELLOW"/buymod"WHITE"' untuk membeli Aksesoris Kendaraan", -1, 1093.8877, -1246.2726, 15.8362, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
}
