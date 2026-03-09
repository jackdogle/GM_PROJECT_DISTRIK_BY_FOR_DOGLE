#if defined _systems_publicworks_included
    #endinput
#endif
#define _systems_publicworks_included

#include <a_samp>
#include <streamer>

#define MAX_ROAD_HOLES 50
#define COLOR_PUBLICWORKS 0xFF8000FF

enum E_HOLE_DATA
{
    bool:hExists,
    hObjID,
    Float:hX,
    Float:hY,
    Float:hZ
}
new RoadHole[MAX_ROAD_HOLES][E_HOLE_DATA];
new bool:IsOnDuty[MAX_PLAYERS];

forward FixRoadProgress(playerid, holeid);

stock CreateRoadHole(Float:x, Float:y, Float:z)
{
    for(new i = 0; i < MAX_ROAD_HOLES; i++)
    {
        if(!RoadHole[i][hExists])
        {
            RoadHole[i][hExists] = true;
            RoadHole[i][hX] = x;
            RoadHole[i][hY] = y;
            RoadHole[i][hZ] = z - 0.95;
            RoadHole[i][hObjID] = CreateDynamicObject(2818, x, y, z - 0.95, 0.0, 0.0, 0.0);
            return i;
        }
    }
    return -1;
}

CMD:wduty(playerid, params[])
{
    if(!IsOnDuty[playerid])
    {
        IsOnDuty[playerid] = true;
        SendClientMessage(playerid, COLOR_PUBLICWORKS, "Anda sekarang sedang On-Duty (Public Works).");
        SendClientMessage(playerid, -1, "Gunakan /carijalan untuk melihat lokasi kerusakan di GPS.");
    }
    else
    {
        IsOnDuty[playerid] = false;
        DisablePlayerCheckpoint(playerid);
        SendClientMessage(playerid, 0xFF0000FF, "Anda sekarang Off-Duty.");
    }
    return 1;
}

CMD:carijalan(playerid, params[])
{
    if(!IsOnDuty[playerid]) return SendClientMessage(playerid, -1, "Anda harus /duty terlebih dahulu!");

    new found = -1;
    for(new i = 0; i < MAX_ROAD_HOLES; i++)
    {
        if(RoadHole[i][hExists])
        {
            found = i;
            break;
        }
    }

    if(found != -1)
    {
        SetPlayerCheckpoint(playerid, RoadHole[found][hX], RoadHole[found][hY], RoadHole[found][hZ], 4.0);
        SendClientMessage(playerid, COLOR_PUBLICWORKS, "Lokasi kerusakan jalan telah ditandai di GPS (Tanda Merah).");
    }
    else
    {
        SendClientMessage(playerid, -1, "Saat ini tidak ada laporan kerusakan jalan.");
    }
    return 1;
}

CMD:perbaiki(playerid, params[])
{
    if(!IsOnDuty[playerid]) return SendClientMessage(playerid, -1, "Anda harus /duty terlebih dahulu!");

    new holeid = -1;
    for(new i = 0; i < MAX_ROAD_HOLES; i++)
    {
        if(RoadHole[i][hExists] && IsPlayerInRangeOfPoint(playerid, 3.0, RoadHole[i][hX], RoadHole[i][hY], RoadHole[i][hZ]))
        {
            holeid = i;
            break;
        }
    }

    if(holeid == -1) return SendClientMessage(playerid, -1, "Anda tidak berada di dekat lubang jalan.");
    
    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 1, 0);
    SetTimerEx("FixRoadProgress", 6000, false, "ii", playerid, holeid);
    
    GameTextForPlayer(playerid, "~w~Menambal Aspal...", 5000, 3);
    return 1;
}

public FixRoadProgress(playerid, holeid)
{
    if(RoadHole[holeid][hExists])
    {
        DestroyDynamicObject(RoadHole[holeid][hObjID]);
        RoadHole[holeid][hExists] = false;
        DisablePlayerCheckpoint(playerid);
        
        ClearAnimations(playerid);
        GivePlayerMoney(playerid, 450);
        
        SendClientMessage(playerid, COLOR_PUBLICWORKS, "Jalan diperbaiki! Gaji $450 diterima. Gunakan /carijalan lagi jika ingin lanjut.");
        PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
    }
    return 1;
}

CMD:cone(playerid, params[])
{
    if(!IsOnDuty[playerid]) return SendClientMessage(playerid, -1, "Hanya petugas On-Duty yang bisa memasang ini.");
    
    new Float:px, Float:py, Float:pz, Float:pa;
    GetPlayerPos(playerid, px, py, pz);
    GetPlayerFacingAngle(playerid, pa);
    
    CreateDynamicObject(1238, px + (1.0 * floatsin(-pa, degrees)), py + (1.0 * floatcos(-pa, degrees)), pz - 0.8, 0.0, 0.0, pa);
    SendClientMessage(playerid, -1, "Traffic Cone terpasang.");
    return 1;
}

CMD:bersihkancone(playerid, params[])
{
    new Float:ox, Float:oy, Float:oz;
    new foundObj = -1;

    for(new i = 1; i <= Streamer_GetUpperBound(STREAMER_TYPE_OBJECT); i++)
    {
        if(IsValidDynamicObject(i))
        {
            if(Streamer_GetIntData(STREAMER_TYPE_OBJECT, i, E_STREAMER_MODEL_ID) == 1238)
            {
                GetDynamicObjectPos(i, ox, oy, oz);
                if(IsPlayerInRangeOfPoint(playerid, 3.5, ox, oy, oz))
                {
                    foundObj = i;
                    break;
                }
            }
        }
    }

    if(foundObj != -1)
    {
        DestroyDynamicObject(foundObj);
        SendClientMessage(playerid, -1, "Traffic Cone telah dibereskan.");
    }
    return 1;
}