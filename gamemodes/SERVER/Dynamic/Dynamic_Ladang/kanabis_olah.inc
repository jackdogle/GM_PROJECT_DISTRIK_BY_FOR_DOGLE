#include <YSI\y_hooks>

new 
    STREAMER_TAG_AREA:kanabisOlah;

stock LabelOlah()
{
    kanabisOlah = CreateDynamicSphere(873.7858, -15.7096, 63.1953, 4.0, 0, 0);
}

hook OnGameModeInit()
{
    LabelOlah();
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == kanabisOlah)
    {
        ShowKey(playerid, "[Y]- Olah Kanabis");
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == kanabisOlah)
    {
        HideShortKey(playerid);
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInDynamicArea(playerid, kanabisOlah))
        {
            new count = 0, ecount = 0;
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
            
            foreach(new i : Player) {
                if(IsPlayerConnected(i))
                {
                    if(AccountData[i][pDutyPD]) count++;
                    if(AccountData[i][pDutyEms]) ecount++;
                }
            }
            if(count >= 4 && ecount >= 2)
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

                AccountData[playerid][ActivityTime] = 1;
                pOlahKanabis[playerid] = SetTimerEx("MengolahKanabis", 1000, true, "i", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH KANABIS");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            }
            else
            {
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 Polisi dan 2 EMS!");
            }
            
            
        }
    }
    return 1;
}

forward MengolahKanabis(playerid);
public MengolahKanabis(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pOlahKanabis[playerid]);
        pOlahKanabis[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(kanabisOlah))
    {
        KillTimer(pOlahKanabis[playerid]);
        pOlahKanabis[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, kanabisOlah))
    {
        KillTimer(pOlahKanabis[playerid]);
        pOlahKanabis[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50)
    {
        KillTimer(pOlahKanabis[playerid]);
        pOlahKanabis[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh");
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pOlahKanabis[playerid]);
        pOlahKanabis[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kanabis") < 10)
    {
        KillTimer(pOlahKanabis[playerid]);
        pOlahKanabis[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Kanabis tidak cukup! (Min: 10)");
        return 0;
    }

    if(Inventory_Count(playerid, "Plastik") < 20)
    {
        KillTimer(pOlahKanabis[playerid]);
        pOlahKanabis[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Plastik tidak cukup! (Min: 20)");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pOlahKanabis[playerid]);
        pOlahKanabis[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Inventory_Remove(playerid, "Kanabis", 10);
        Inventory_Remove(playerid, "Plastik", 20);
        Inventory_Add(playerid, "Marijuana", 1575, 1);
        ShowItemBox(playerid, "Removed 20x", "Plastik", 1264);
        ShowItemBox(playerid, "Removed 10x", "Kanabis", 19473);
        ShowItemBox(playerid, "Received 1x", "Marijuana", 1575);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/15;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}