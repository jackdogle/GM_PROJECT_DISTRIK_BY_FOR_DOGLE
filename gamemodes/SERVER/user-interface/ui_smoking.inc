#include <YSI\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && IsPlayerSmoking[playerid])
    {
        if(SmokingDelayTime[playerid] <= gettime())
        {
            ApplyAnimationEx(playerid, "GANGS", "smkcig_prtl", 4.5, 0,1,0,1,1,1);
            SetTimerEx("SmokeCigar", 3500, false, "d", playerid);
            SmokingDelayTime[playerid] = gettime() + 5;
        }
    }
    return 1;
}

forward SmokeCigar(playerid);
public SmokeCigar(playerid)
{
    SetPlayerAttachedObject(playerid, 7, 18677, 2, -0.028, 0.160, -1.640, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
    CountSmoking[playerid] --;
    if(CountSmoking[playerid] == 0)
    {
        IsPlayerSmoking[playerid] = false;
        CountSmoking[playerid] = 0;
        SmokingDelayTime[playerid] = 0;

        AccountData[playerid][pStress] -= 5;
        SendClientMessage(playerid, -1, "[i] Rokok anda telah habis sebatang. Stress anda menurun "RED"5%%");
    }
    return 1;
}