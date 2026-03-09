#define MAX_DYNAMIC_BASEMENT    20

enum E_UNDERGROUND_DATA
{
    underID,

    Float:underEnter[4],
    Float:underExitSpawn[4],

    enterCP,
    exitCP,

    Text3D:enterLabel,
    Text3D:exitLabel
};

new 
    Iterator:Underground<MAX_DYNAMIC_BASEMENT>,
    UndergroundData[MAX_DYNAMIC_BASEMENT][E_UNDERGROUND_DATA];