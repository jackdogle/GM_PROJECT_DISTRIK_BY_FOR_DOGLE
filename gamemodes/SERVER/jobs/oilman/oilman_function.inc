#include <YSI\y_hooks>

enum E_STUFFOILMAN {
    STREAMER_TAG_AREA:CollectOil[4],
    STREAMER_TAG_AREA:RefinedOil,
    STREAMER_TAG_AREA:MixxingOil,

    STREAMER_TAG_MAP_ICON:OilMapIcon[3],

    STREAMER_TAG_3D_TEXT_LABEL: CollectOilLabel[4],
    STREAMER_TAG_3D_TEXT_LABEL: RefinedOilLabel,
    STREAMER_TAG_3D_TEXT_LABEL: MixxingOilLabel,

    bool: DurringOilman
};
new PlayerVarsOil[MAX_PLAYERS][E_STUFFOILMAN];

new pTimerCollectOil[MAX_PLAYERS] = {-1, ...};
new pTimerRefinedOil[MAX_PLAYERS] = {-1, ...};
new pTimerMixxingOil[MAX_PLAYERS] = {-1, ...};

forward LoadVarsOilman(playerid);
public LoadVarsOilman(playerid)
{
    UnloadVarsOilman(playerid);

    PlayerVarsOil[playerid][CollectOil][0] = CreateDynamicSphere(479.8763, 1300.6165, 10.3968 - 0.2, 3.0, 0, 0, playerid);
    PlayerVarsOil[playerid][CollectOil][1] = CreateDynamicSphere(482.6979, 1294.6884, 10.2835 - 0.2, 3.0, 0, 0, playerid);
    PlayerVarsOil[playerid][CollectOil][2] = CreateDynamicSphere(488.1861, 1291.2322, 10.0430 - 0.2, 3.0, 0, 0, playerid);
    PlayerVarsOil[playerid][CollectOil][3] = CreateDynamicSphere(492.3781, 1290.7634, 10.0365 - 0.2, 3.0, 0, 0, playerid);
    PlayerVarsOil[playerid][RefinedOil] = CreateDynamicSphere(486.6990, 1534.5759, 1.0032 - 0.2, 3.0, 0, 0, playerid);
    PlayerVarsOil[playerid][MixxingOil] = CreateDynamicSphere(281.4789, 1342.7750, 10.5859 - 0.2, 3.0, 0, 0, playerid);

    PlayerVarsOil[playerid][OilMapIcon][0] = CreateDynamicMapIcon(479.8763, 1300.6165, 10.3968, 51, -1, 0, 0, playerid, 9999.0, MAPICON_GLOBAL, -1, 1);
    PlayerVarsOil[playerid][OilMapIcon][1] = CreateDynamicMapIcon(486.6990, 1534.5759, 1.0032, 51, -1, 0, 0, playerid, 9999.0, MAPICON_GLOBAL, -1, 1);
    PlayerVarsOil[playerid][OilMapIcon][2] = CreateDynamicMapIcon(281.4789, 1342.7750, 10.5859, 51, -1, 0, 0, playerid, 9999.0, MAPICON_GLOBAL, -1, 1);

    PlayerVarsOil[playerid][CollectOilLabel][0] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" - Collect Oil", -1, 479.8763, 1300.6165, 10.3968 - 0.4, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid);
    PlayerVarsOil[playerid][CollectOilLabel][1] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" - Collect Oil", -1, 482.6979, 1294.6884, 10.2835 - 0.4, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid);
    PlayerVarsOil[playerid][CollectOilLabel][2] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" - Collect Oil", -1, 488.1861, 1291.2322, 10.0430 - 0.4, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid);
    PlayerVarsOil[playerid][CollectOilLabel][3] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" - Collect Oil", -1, 492.3781, 1290.7634, 10.0365 - 0.4, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid);
    PlayerVarsOil[playerid][RefinedOilLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" - Refined Oil", -1, 486.6990, 1534.5759, 1.0032 + 0.2, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid);
    PlayerVarsOil[playerid][MixxingOilLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" - Mixxing Oil", -1, 281.4789, 1342.7750, 10.5859 + 0.2, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid);

}

forward UnloadVarsOilman(playerid);
public UnloadVarsOilman(playerid)
{
    if(DestroyDynamic3DTextLabel(PlayerVarsOil[playerid][CollectOilLabel][0]))
        PlayerVarsOil[playerid][CollectOilLabel][0] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(PlayerVarsOil[playerid][CollectOilLabel][1]))
        PlayerVarsOil[playerid][CollectOilLabel][1] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(PlayerVarsOil[playerid][CollectOilLabel][2]))
        PlayerVarsOil[playerid][CollectOilLabel][2] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(PlayerVarsOil[playerid][CollectOilLabel][3]))
        PlayerVarsOil[playerid][CollectOilLabel][3] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(PlayerVarsOil[playerid][RefinedOilLabel]))
        PlayerVarsOil[playerid][RefinedOilLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(PlayerVarsOil[playerid][MixxingOilLabel]))
        PlayerVarsOil[playerid][MixxingOilLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    // -----------------------------------------------------------------------------
    if(DestroyDynamicMapIcon(PlayerVarsOil[playerid][OilMapIcon][0]))
        PlayerVarsOil[playerid][OilMapIcon][0] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
    
    if(DestroyDynamicMapIcon(PlayerVarsOil[playerid][OilMapIcon][1]))
        PlayerVarsOil[playerid][OilMapIcon][1] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
    
    if(DestroyDynamicMapIcon(PlayerVarsOil[playerid][OilMapIcon][2]))
        PlayerVarsOil[playerid][OilMapIcon][2] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

    if(DestroyDynamicArea(PlayerVarsOil[playerid][CollectOil][0]))
        PlayerVarsOil[playerid][CollectOil][0] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    if(DestroyDynamicArea(PlayerVarsOil[playerid][CollectOil][1]))
        PlayerVarsOil[playerid][CollectOil][1] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    if(DestroyDynamicArea(PlayerVarsOil[playerid][CollectOil][2]))
        PlayerVarsOil[playerid][CollectOil][2] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    if(DestroyDynamicArea(PlayerVarsOil[playerid][CollectOil][3]))
        PlayerVarsOil[playerid][CollectOil][3] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    if(DestroyDynamicArea(PlayerVarsOil[playerid][RefinedOil]))
        PlayerVarsOil[playerid][RefinedOil] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    if(DestroyDynamicArea(PlayerVarsOil[playerid][MixxingOil]))
        PlayerVarsOil[playerid][MixxingOil] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
}

/*forward UnloadVarsOilman(playerid);
public UnloadVarsOilman(playerid)
{
    if(IsValidDynamic3DTextLabel(PlayerVarsOil[playerid][CollectOilLabel][0]))
        DestroyDynamic3DTextLabel(PlayerVarsOil[playerid][CollectOilLabel][0]);
    PlayerVarsOil[playerid][CollectOilLabel][0] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(IsValidDynamic3DTextLabel(PlayerVarsOil[playerid][CollectOilLabel][1]))
        DestroyDynamic3DTextLabel(PlayerVarsOil[playerid][CollectOilLabel][1]);
    PlayerVarsOil[playerid][CollectOilLabel][1] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(IsValidDynamic3DTextLabel(PlayerVarsOil[playerid][CollectOilLabel][2]))
        DestroyDynamic3DTextLabel(PlayerVarsOil[playerid][CollectOilLabel][2]);
    PlayerVarsOil[playerid][CollectOilLabel][2] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(IsValidDynamic3DTextLabel(PlayerVarsOil[playerid][CollectOilLabel][3]))
        DestroyDynamic3DTextLabel(PlayerVarsOil[playerid][CollectOilLabel][3]);
    PlayerVarsOil[playerid][CollectOilLabel][3] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(IsValidDynamic3DTextLabel(PlayerVarsOil[playerid][RefinedOilLabel]))
        DestroyDynamic3DTextLabel(PlayerVarsOil[playerid][RefinedOilLabel]);
    PlayerVarsOil[playerid][RefinedOilLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(IsValidDynamic3DTextLabel(PlayerVarsOil[playerid][MixxingOilLabel]))
        DestroyDynamic3DTextLabel(PlayerVarsOil[playerid][MixxingOilLabel]);
    PlayerVarsOil[playerid][MixxingOilLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    // -----------------------------------------------------------------------------
    if(IsValidDynamicMapIcon(PlayerVarsOil[playerid][OilMapIcon][0]))
        DestroyDynamicMapIcon(PlayerVarsOil[playerid][OilMapIcon][0]);
    PlayerVarsOil[playerid][OilMapIcon][0] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
    
    if(IsValidDynamicMapIcon(PlayerVarsOil[playerid][OilMapIcon][1]))
        DestroyDynamicMapIcon(PlayerVarsOil[playerid][OilMapIcon][1]);
    PlayerVarsOil[playerid][OilMapIcon][1] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
    
    if(IsValidDynamicMapIcon(PlayerVarsOil[playerid][OilMapIcon][2]))
        DestroyDynamicMapIcon(PlayerVarsOil[playerid][OilMapIcon][2]);
    PlayerVarsOil[playerid][OilMapIcon][2] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

    if(IsValidDynamicArea(PlayerVarsOil[playerid][CollectOil][0]))
        DestroyDynamicArea(PlayerVarsOil[playerid][CollectOil][0]);
    PlayerVarsOil[playerid][CollectOil][0] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    if(IsValidDynamicArea(PlayerVarsOil[playerid][CollectOil][1]))
        DestroyDynamicArea(PlayerVarsOil[playerid][CollectOil][1]);
    PlayerVarsOil[playerid][CollectOil][1] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    if(IsValidDynamicArea(PlayerVarsOil[playerid][CollectOil][2]))
        DestroyDynamicArea(PlayerVarsOil[playerid][CollectOil][2]);
    PlayerVarsOil[playerid][CollectOil][2] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    if(IsValidDynamicArea(PlayerVarsOil[playerid][CollectOil][3]))
        DestroyDynamicArea(PlayerVarsOil[playerid][CollectOil][3]);
    PlayerVarsOil[playerid][CollectOil][3] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    if(IsValidDynamicArea(PlayerVarsOil[playerid][RefinedOil]))
        DestroyDynamicArea(PlayerVarsOil[playerid][RefinedOil]);
    PlayerVarsOil[playerid][RefinedOil] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    if(IsValidDynamicArea(PlayerVarsOil[playerid][MixxingOil]))
        DestroyDynamicArea(PlayerVarsOil[playerid][MixxingOil]);
    PlayerVarsOil[playerid][MixxingOil] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
}*/

Oilman_CollectArea(const playerid)
{
    if(IsPlayerInDynamicArea(playerid, PlayerVarsOil[playerid][CollectOil][0])) return 1;
    if(IsPlayerInDynamicArea(playerid, PlayerVarsOil[playerid][CollectOil][1])) return 1;
    if(IsPlayerInDynamicArea(playerid, PlayerVarsOil[playerid][CollectOil][2])) return 1;
    if(IsPlayerInDynamicArea(playerid, PlayerVarsOil[playerid][CollectOil][3])) return 1;
    return 0;
}

hook OnPlayerConnect(playerid)
{
    pTimerCollectOil[playerid] = -1;
    pTimerRefinedOil[playerid] = -1;
    pTimerMixxingOil[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pTimerCollectOil[playerid]);
    KillTimer(pTimerRefinedOil[playerid]);
    KillTimer(pTimerMixxingOil[playerid]);
    pTimerCollectOil[playerid] = -1;
    pTimerRefinedOil[playerid] = -1;
    pTimerMixxingOil[playerid] = -1;
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pJob] == JOB_OILMAN)
        {
            if(Oilman_CollectArea(playerid))
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                if(Inventory_Count(playerid, "Petrol") >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Petrol anda sudah mencapai max (100)!");

                // Tampilkan minigame dengan callback
                ShowMinigame(playerid, "OnMinigameComplete", "TakePetrol"); 
            }

            if(IsPlayerInDynamicArea(playerid, PlayerVarsOil[playerid][RefinedOil]))
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                if(Inventory_Count(playerid, "Pure Oil") >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pure Oil anda sudah mencapai max (100)!");
                
                // Tampilkan minigame dengan callback
                ShowMinigame(playerid, "OnMinigameComplete", "TakePureOil"); 
            }

            if(IsPlayerInDynamicArea(playerid, PlayerVarsOil[playerid][MixxingOil]))
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                if(Inventory_Count(playerid, "GAS") >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "GAS anda sudah mencapai max (100)!");

                AccountData[playerid][ActivityTime] = 1;
                pTimerMixxingOil[playerid] = SetTimerEx("OilMixxing", 1000, true, "d", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MIXXING OIL");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            }
        }
    }
    return 1;
}

// ------------------------------------- Callback Function
forward OilMixxing(playerid);
public OilMixxing(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerMixxingOil[playerid]);
        pTimerMixxingOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerVarsOil[playerid][MixxingOil]))
    {
        KillTimer(pTimerMixxingOil[playerid]);
        pTimerMixxingOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerVarsOil[playerid][MixxingOil]))
    {
        KillTimer(pTimerMixxingOil[playerid]);
        pTimerMixxingOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!PlayerHasItem(playerid, "Pure Oil"))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Pure Oil!");
        KillTimer(pTimerMixxingOil[playerid]);
        pTimerMixxingOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
        KillTimer(pTimerMixxingOil[playerid]);
        pTimerMixxingOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 120)
    {
        KillTimer(pTimerMixxingOil[playerid]);
        pTimerMixxingOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Inventory_Remove(playerid, "Pure Oil", 1);
        Inventory_Add(playerid, "GAS", 1650, 5);
        ShowItemBox(playerid, "Removed 1x", "Pure oil", 3632);
        ShowItemBox(playerid, "Received 5x", "GAS", 1650);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 20;

        new Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward OilRefined(playerid);
public OilRefined(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerRefinedOil[playerid]);
        pTimerRefinedOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerVarsOil[playerid][RefinedOil]))
    {
        KillTimer(pTimerRefinedOil[playerid]);
        pTimerRefinedOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerVarsOil[playerid][RefinedOil]))
    {
        KillTimer(pTimerRefinedOil[playerid]);
        pTimerRefinedOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Petrol") < 1)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Petrol tidak cukup! (Min: 1)");
        KillTimer(pTimerRefinedOil[playerid]);
        pTimerRefinedOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");
        KillTimer(pTimerRefinedOil[playerid]);
        pTimerRefinedOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTimerRefinedOil[playerid]);
        pTimerRefinedOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
       
        Inventory_Remove(playerid, "Petrol");
        Inventory_Add(playerid, "Pure Oil", 3632, 2);
        ShowItemBox(playerid, "Removed 1x", "Petrol", 19621);
        ShowItemBox(playerid, "Received 2x", "Pure Oil", 3632);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakingOil(playerid);
public TakingOil(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerCollectOil[playerid]);
        pTimerCollectOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!Oilman_CollectArea(playerid))
    {
        KillTimer(pTimerCollectOil[playerid]);
        pTimerCollectOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");
        KillTimer(pTimerCollectOil[playerid]);
        pTimerCollectOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTimerCollectOil[playerid]);
        pTimerCollectOil[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Inventory_Add(playerid, "Petrol", 19621, 2);
        ShowItemBox(playerid, "Received 2x", "PETROL", 19621);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 18.75;

        new Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}