#include <YSI\y_hooks>
#define MAX_DYNAMIC_SPEED     100

#define IsPlayerToggleSpeedTrap(%0)			GetPVarInt(%0, "ToggleSpeedLog")
#define SetPlayerToggleSpeedTrap(%0,%1)		SetPVarInt(%0, "ToggleSpeedLog",%1)

enum E_SPEED_DATA
{
    speedID,
    speedMax,

    speedDetail[128],
    Float:speedPos[4],

    STREAMER_TAG_AREA:speedArea,
    STREAMER_TAG_OBJECT:speedObject,
    STREAMER_TAG_3D_TEXT_LABEL:speedLabel
};

new 
    Iterator:Speed<MAX_DYNAMIC_SPEED>,
    SpeedData[MAX_DYNAMIC_SPEED][E_SPEED_DATA];