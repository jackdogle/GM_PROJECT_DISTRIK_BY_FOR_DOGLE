#include <YSI\y_hooks>

enum JobLumberStuff {
    LumberCooldown[11],
    STREAMER_TAG_MAP_ICON:LumberIcon,
    STREAMER_TAG_AREA:LumberTakeKayu[11],
    STREAMER_TAG_3D_TEXT_LABEL:LumberTreeLabel[11],
    STREAMER_TAG_AREA:LumberPotongKayu[2],
    STREAMER_TAG_AREA:LumberKemasKayu,

    // STREAMER_TAG_OBJECT:TreeObjects[11],
};
new PlayerVarsLumber[MAX_PLAYERS][JobLumberStuff];

new pTakingKayuTimer[MAX_PLAYERS] = {-1, ...},
    pGergajiKayuTimer[MAX_PLAYERS] = {-1, ...},
    pKemasKayuTimer[MAX_PLAYERS] = {-1, ...};

static Float:TreePos[][] = 
{
    {-491.704162, -47.821651, 59.509613, 0.000000, 0.000000, 0.000000},
    {-486.264160, -40.781661, 59.099620, 0.000000, 0.000000, 0.000000},
    {-477.874298, -47.801651, 59.009620, 0.000000, 0.000000, 0.000000},
    {-484.634307, -54.481658, 59.579620, 0.000000, 0.000000, 0.000000},
    {-484.634307, -46.481662, 59.199630, 0.000000, 0.000000, 0.000000},
    {-484.634307, -31.481674, 58.069633, 0.000000, 0.000000, 0.000000},
    {-493.434295, -31.481674, 58.019641, 0.000000, 0.000000, 0.000000},
    {-479.424285, -24.911674, 57.029647, -8.099999, 0.000000, 0.000000},
    {-472.004302, -33.998680, 58.333019, -8.099999, 0.000000, 0.000000},
    {-445.374176, -45.131652, 58.529628, 0.000000, 0.000000, 0.000000},
    {-436.354187, -49.511646, 58.099628, 0.000000, 0.000000, 0.000000},
    {-437.004180, -41.521644, 58.049617, 0.000000, 0.000000, 0.000000}
};

stock LoadVarsLumber(playerid)
{
    UnloadVarsLumber(playerid);

    PlayerVarsLumber[playerid][LumberIcon] = CreateDynamicMapIcon(-439.7503, -62.3335, 58.9720, 60, -1, -1, -1, playerid, 9999.0, MAPICON_GLOBAL, -1, 1);

    PlayerVarsLumber[playerid][LumberPotongKayu][0] = CreateDynamicSphere(-438.2198, -75.8204, 58.9699, 2.0, -1, -1, playerid);
    PlayerVarsLumber[playerid][LumberPotongKayu][1] = CreateDynamicSphere(-438.2239, -79.1185, 58.9451, 2.0, -1, -1, playerid);
    PlayerVarsLumber[playerid][LumberKemasKayu] = CreateDynamicSphere(-463.6386, -41.6182, 59.9543, 3.0, -1, -1, playerid);

    for(new i = 0; i < 11; i++)
    {
        PlayerVarsLumber[playerid][LumberTakeKayu][i] = CreateDynamicSphere(TreePos[i][0], TreePos[i][1], TreePos[i][2], 2.0, 0, 0, playerid);
        // PlayerVarsLumber[playerid][TreeObjects][i] = CreateDynamicObject(657, TreePos[i][0], TreePos[i][1], TreePos[i][2], TreePos[i][3], TreePos[i][4], TreePos[i][5], 0, 0, playerid, 300.00, 300.00); 
        PlayerVarsLumber[playerid][LumberTreeLabel][i] = CreateDynamic3DTextLabel(sprintf(""GREEN"[Y]"WHITE" Potong Kayu\n%d Detik", PlayerVarsLumber[playerid][LumberCooldown][i]), -1, TreePos[i][0], TreePos[i][1], TreePos[i][2] + 1.5, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, playerid, 20.0, -1, 0);
    }
    return 1;
}

stock UnloadVarsLumber(playerid)
{
    if(DestroyDynamicMapIcon(PlayerVarsLumber[playerid][LumberIcon]))
        PlayerVarsLumber[playerid][LumberIcon] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
    
    if(DestroyDynamicArea(PlayerVarsLumber[playerid][LumberPotongKayu][0]))
        PlayerVarsLumber[playerid][LumberPotongKayu][0] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
    
    if(DestroyDynamicArea(PlayerVarsLumber[playerid][LumberPotongKayu][1]))
        PlayerVarsLumber[playerid][LumberPotongKayu][1] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    if(DestroyDynamicArea(PlayerVarsLumber[playerid][LumberKemasKayu]))
        PlayerVarsLumber[playerid][LumberKemasKayu] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
    
    for(new i = 0; i < 11; i++)
    {
        if(DestroyDynamicArea(PlayerVarsLumber[playerid][LumberTakeKayu][i]))
            PlayerVarsLumber[playerid][LumberTakeKayu][i] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        
        if(DestroyDynamic3DTextLabel(PlayerVarsLumber[playerid][LumberTreeLabel][i]))
            PlayerVarsLumber[playerid][LumberTreeLabel][i] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }
    return 1;
}

Lumber_GergajiArea(playerid)
{
    if(IsPlayerInDynamicArea(playerid, PlayerVarsLumber[playerid][LumberPotongKayu][0])) 
        return 1;    
    else if(IsPlayerInDynamicArea(playerid, PlayerVarsLumber[playerid][LumberPotongKayu][1])) 
        return 1;
    
    return 0;
}

hook OnPlayerConnect(playerid)
{
    pTakingKayuTimer[playerid] = -1;
    pGergajiKayuTimer[playerid] = -1;
    pKemasKayuTimer[playerid] = -1;
    UnloadVarsLumber(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pTakingKayuTimer[playerid]);
    KillTimer(pGergajiKayuTimer[playerid]);
    KillTimer(pKemasKayuTimer[playerid]);
    pTakingKayuTimer[playerid] = -1;
    pGergajiKayuTimer[playerid] = -1;
    pKemasKayuTimer[playerid] = -1;
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pJob] == JOB_LUMBERJACK)
    {
        if(areaid == PlayerVarsLumber[playerid][LumberPotongKayu][0] || areaid == PlayerVarsLumber[playerid][LumberPotongKayu][1])
        {
            ShowKey(playerid, "[Y]- Gergaji Kayu");
        }

        if(areaid == PlayerVarsLumber[playerid][LumberKemasKayu])
        {
            ShowKey(playerid, "[Y]- Kemas Kayu");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pJob] == JOB_LUMBERJACK)
    {
        if(areaid == PlayerVarsLumber[playerid][LumberPotongKayu][0] || areaid == PlayerVarsLumber[playerid][LumberPotongKayu][1])
        {
            HideShortKey(playerid);
        }

        if(areaid == PlayerVarsLumber[playerid][LumberKemasKayu])
        {
            HideShortKey(playerid);
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && AccountData[playerid][pJob] == JOB_LUMBERJACK)
    {
        if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            for(new i = 0; i < 11; i ++)
            {
                if(IsPlayerInDynamicArea(playerid, PlayerVarsLumber[playerid][LumberTakeKayu][i]))
                {
                    if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
                    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                    if(PlayerVarsLumber[playerid][LumberCooldown][i] != 0) return 0;

                    AccountData[playerid][ActivityTime] = 1;
                    pTakingKayuTimer[playerid] = SetTimerEx("TakeKayu", 1000, true, "dd", playerid, i);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMOTONG KAYU");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "CHAINSAW", "CSAW_G", 4.1, 1, 0, 0, 0, 0, 1); // Animation Gergaji
                    SetPlayerAttachedObject(playerid, JOB_SLOT, 341, 6, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000); // Attach Object Gergaji
                }
            }

            if(Lumber_GergajiArea(playerid))
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");

                AccountData[playerid][ActivityTime] = 1;
                pGergajiKayuTimer[playerid] = SetTimerEx("GergajiKayu", 1000, true, "d", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "GERGAJI KAYU");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "CHAINSAW", "CSAW_G", 4.1, 1, 0, 0, 0, 0, 1); // Animation Gergaji
                SetPlayerAttachedObject(playerid, JOB_SLOT, 341, 6, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000); // Attach Object Gergaji
            }

            if(IsPlayerInDynamicArea(playerid, PlayerVarsLumber[playerid][LumberKemasKayu]))
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");

                AccountData[playerid][ActivityTime] = 1;
                pKemasKayuTimer[playerid] = SetTimerEx("KemasKayu", 1000, true, "d", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGEMAS KAYU");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1); // Animation cuci Tangan
            }
        }
    }
    return 1;
}

// ----------------------------- CALLBACK FUNCTIONS
forward KemasKayu(playerid);
public KemasKayu(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pKemasKayuTimer[playerid]);
        pKemasKayuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerVarsLumber[playerid][LumberKemasKayu]))
    {
        KillTimer(pKemasKayuTimer[playerid]);
        pKemasKayuTimer[playerid] = 1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerVarsLumber[playerid][LumberKemasKayu]))
    {
        KillTimer(pKemasKayuTimer[playerid]);
        pKemasKayuTimer[playerid] = 1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(IsPlayerInjured(playerid))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pKemasKayuTimer[playerid]);
        pKemasKayuTimer[playerid] = 1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(GetTotalWeightFloat(playerid) >= 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        KillTimer(pKemasKayuTimer[playerid]);
        pKemasKayuTimer[playerid] = 1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Kayu Potongan") < 2)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Kayu Potongan tidak cukup! (Min: 2)");
        KillTimer(pKemasKayuTimer[playerid]);
        pKemasKayuTimer[playerid] = 1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 120)
    {
        KillTimer(pKemasKayuTimer[playerid]);
        pKemasKayuTimer[playerid] = 1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    
        Inventory_Remove(playerid, "Kayu Potongan", 2);
        Inventory_Add(playerid, "Kayu Kemas", 2912, 2);
        ShowItemBox(playerid, "Removed 2x", "Kayu Potongan", 1463);
        ShowItemBox(playerid, "Recieved 2x", "Kayu Kemas", 2912);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/120;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward GergajiKayu(playerid);
public GergajiKayu(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pGergajiKayuTimer[playerid]);
        pGergajiKayuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!Lumber_GergajiArea(playerid))
    {
        KillTimer(pGergajiKayuTimer[playerid]);
        pGergajiKayuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, JOB_SLOT); // Menghapus Object Gergaji
        return 0;
    }

    if(IsPlayerInjured(playerid))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pGergajiKayuTimer[playerid]);
        pGergajiKayuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, JOB_SLOT); // Menghapus Object Gergaji
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");
        KillTimer(pGergajiKayuTimer[playerid]);
        pGergajiKayuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, JOB_SLOT); // Menghapus Object Gergaji
        return 0;
    }

    if(!PlayerHasItem(playerid, "Kayu"))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Kayu!");
        KillTimer(pGergajiKayuTimer[playerid]);
        pGergajiKayuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, JOB_SLOT); // Menghapus Object Gergaji
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 10)
    {
        KillTimer(pGergajiKayuTimer[playerid]);
        pGergajiKayuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, JOB_SLOT); // Menghapus Object Gergaji
        
        Inventory_Remove(playerid, "Kayu");
        Inventory_Add(playerid, "Kayu Potongan", 1463, 2);
        ShowItemBox(playerid, "Removed 1x", "Kayu", 19793);
        ShowItemBox(playerid, "Recieved 2x", "Kayu Potongan", 1463);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/10;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeKayu(playerid, x);
public TakeKayu(playerid, x)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakingKayuTimer[playerid]);
        pTakingKayuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;    
    }

    if(!IsValidDynamicArea(PlayerVarsLumber[playerid][LumberTakeKayu][x]))
    {
        KillTimer(pTakingKayuTimer[playerid]);
        pTakingKayuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, JOB_SLOT); // Menghapus Object Gergaji
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerVarsLumber[playerid][LumberTakeKayu][x]))
    {
        KillTimer(pTakingKayuTimer[playerid]);
        pTakingKayuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, JOB_SLOT); // Menghapus Object Gergaji
        return 0;
    }

    if(IsPlayerInjured(playerid))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pTakingKayuTimer[playerid]);
        pTakingKayuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, JOB_SLOT); // Menghapus Object Gergaji
        return 0;
    }

    if(GetTotalWeightFloat(playerid) >= 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");
        KillTimer(pTakingKayuTimer[playerid]);
        pTakingKayuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, JOB_SLOT); // Menghapus Object Gergaji
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pTakingKayuTimer[playerid]);
        pTakingKayuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        StopLoopingAnim(playerid);
        RemovePlayerAttachedObject(playerid, JOB_SLOT); // Menghapus Object Gergaji
        
        PlayerVarsLumber[playerid][LumberCooldown][x] = 45;
        AccountData[playerid][pThirst] --;
        Inventory_Add(playerid, "Kayu", 19793, 1);
        ShowItemBox(playerid, "Recieved 1x", "Kayu", 19793);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/15;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

ptask TreeCooldownUpdate[1000](playerid) 
{
    if(AccountData[playerid][pJob] == JOB_LUMBERJACK) 
    {
        for(new x = 0; x < 11; x++)
        {
            if(PlayerVarsLumber[playerid][LumberCooldown][x] > 0)
            {
                PlayerVarsLumber[playerid][LumberCooldown][x] --;
                if(PlayerVarsLumber[playerid][LumberCooldown][x] == 0)
                {
                    PlayerVarsLumber[playerid][LumberCooldown][x] = CreateDynamicSphere(TreePos[x][0],TreePos[x][1],TreePos[x][2], 2.0, -1, 10, playerid);
                    PlayerVarsLumber[playerid][LumberCooldown][x] = 0;
                }
                
                if(IsValidDynamic3DTextLabel(PlayerVarsLumber[playerid][LumberTreeLabel][x]))
                {
                    UpdateDynamic3DTextLabelText(PlayerVarsLumber[playerid][LumberTreeLabel][x], -1, sprintf(""GREEN"[Y]"WHITE" Potong Kayu\n%d Detik", PlayerVarsLumber[playerid][LumberCooldown][x]));
                }
            }
        }
    }
    return 1;
}