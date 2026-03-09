#include <YSI\y_hooks>

new
    AFKTick[MAX_PLAYERS] = { 0, ... },
    AFKChecker[MAX_PLAYERS] = { 0, ... },
    AFKTime[MAX_PLAYERS] = { 0, ... };

hook OnPlayerConnect(playerid)
{
    AFKTick[playerid] = 0;
    AFKChecker[playerid] = 0;
    AFKTime[playerid] = 0;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    AFKTick[playerid] = 0;
    AFKChecker[playerid] = 0;
    AFKTime[playerid] = 0;
    return 1;
}

hook OnPlayerUpdate(playerid)
{
    if(!AccountData[playerid][pSpawned])
        return 0;
    
    AFKTick[playerid] ++;
    return 1;
}

ptask Player_AFKUpdate[1000](playerid)
{
    if(!AccountData[playerid][pSpawned])
        return 0;
    
    if(AFKTick[playerid] > 10000) AFKTick[playerid] = 1, AFKChecker[playerid] = 0;
    if(AFKChecker[playerid] < AFKTick[playerid] && GetPlayerState(playerid)) AFKChecker[playerid] = AFKTick[playerid], AFKTime[playerid] = 0;
    if(AFKChecker[playerid] == AFKTick[playerid] && GetPlayerState(playerid)) 
    {
        AFKTime[playerid] ++;
        if(AFKTime[playerid] > 2)
        {
            SetPlayerChatBubble(playerid, "[Sedang Melamun]", X11_DARKORANGE, 15.0, 1200);
        }
    }
    return 1;
}