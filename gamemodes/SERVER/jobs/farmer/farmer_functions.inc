#include <YSI\y_hooks>

forward TakePadi(playerid);
public TakePadi(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][0]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][0]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][0]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][0]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][0]))
            DestroyDynamicArea(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][0]));
        PlayerFarmVars[playerid][PadiArea][0] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi1(playerid);
public TakePadi1(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][1]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][1]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][1]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][1]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][1]))
            DestroyDynamicArea(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][1]));
        PlayerFarmVars[playerid][PadiArea][1] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi2(playerid);
public TakePadi2(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][2]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][2]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][2]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][2]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][2]))
            PlayerFarmVars[playerid][PadiArea][2] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi3(playerid);
public TakePadi3(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][3]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][3]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][3]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][3]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][3]))
            PlayerFarmVars[playerid][PadiArea][3] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi4(playerid);
public TakePadi4(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][4]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][4]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][4]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][4]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][4]))
            PlayerFarmVars[playerid][PadiArea][4] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi5(playerid);
public TakePadi5(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][5]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][5]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][5]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][5]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][5]))
            PlayerFarmVars[playerid][PadiArea][5] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi6(playerid);
public TakePadi6(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][6]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][6]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][6]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][6]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][6]))
            PlayerFarmVars[playerid][PadiArea][6] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi7(playerid);
public TakePadi7(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][7]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][7]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][7]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][7]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][7]))
            PlayerFarmVars[playerid][PadiArea][7] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi8(playerid);
public TakePadi8(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][8]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][8]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][8]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][8]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][8]))
            PlayerFarmVars[playerid][PadiArea][8] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi9(playerid);
public TakePadi9(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][9]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][9]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][9]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][9]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][9]))
            PlayerFarmVars[playerid][PadiArea][9] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi10(playerid);
public TakePadi10(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][10]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][10]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][10]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][10]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][10]))
            PlayerFarmVars[playerid][PadiArea][10] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi11(playerid);
public TakePadi11(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][11]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][11]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][11]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][11]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][11]))
            PlayerFarmVars[playerid][PadiArea][11] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi12(playerid);
public TakePadi12(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][12]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][12]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][12]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][12]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][12]))
            PlayerFarmVars[playerid][PadiArea][12] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi13(playerid);
public TakePadi13(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][13]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][13]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][13]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][13]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][13]))
            PlayerFarmVars[playerid][PadiArea][13] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi14(playerid);
public TakePadi14(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][14]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][14]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][14]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][14]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][14]))
            PlayerFarmVars[playerid][PadiArea][14] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi15(playerid);
public TakePadi15(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][15]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][15]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][15]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][15]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][15]))
            PlayerFarmVars[playerid][PadiArea][15] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi16(playerid);
public TakePadi16(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][16]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][16]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][16]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][16]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][16]))
            PlayerFarmVars[playerid][PadiArea][16] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi17(playerid);
public TakePadi17(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][17]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][17]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][17]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][17]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][17]))
            PlayerFarmVars[playerid][PadiArea][17] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi18(playerid);
public TakePadi18(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][18]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][18]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][18]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][18]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][18]))
            PlayerFarmVars[playerid][PadiArea][18] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi19(playerid);
public TakePadi19(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][19]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][19]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][19]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][19]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][19]))
            PlayerFarmVars[playerid][PadiArea][19] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi20(playerid);
public TakePadi20(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][20]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][20]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][20]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][20]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][20]))
            PlayerFarmVars[playerid][PadiArea][20] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi21(playerid);
public TakePadi21(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][21]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][21]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][21]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][21]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][21]))
            PlayerFarmVars[playerid][PadiArea][21] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakePadi22(playerid);
public TakePadi22(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][22]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][22]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][22]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][22]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][22]))
            PlayerFarmVars[playerid][PadiArea][22] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakePadi23(playerid);
public TakePadi23(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][23]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][23]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][23]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][23]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][23]))
            PlayerFarmVars[playerid][PadiArea][23] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakePadi24(playerid);
public TakePadi24(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][24]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][24]))
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeBerasTimer[playerid]);
        pTakeBerasTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Padi", 804, 4);
        ShowItemBox(playerid, "ADDED 4x", "PADI", 804);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][24]))
            DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][24]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][24]))
            PlayerFarmVars[playerid][PadiArea][24] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai(playerid);
public TakeCabai(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][0]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][0]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][0]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][0]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][0]))
            PlayerFarmVars[playerid][CabaiArea][0] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai1(playerid);
public TakeCabai1(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][1]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][1]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][1]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][1]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][1]))
            PlayerFarmVars[playerid][CabaiArea][1] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai2(playerid);
public TakeCabai2(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][2]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][2]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][2]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][2]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][2]))
            PlayerFarmVars[playerid][CabaiArea][2] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai3(playerid);
public TakeCabai3(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][3]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][3]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][3]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][3]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][3]))
            PlayerFarmVars[playerid][CabaiArea][3] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai4(playerid);
public TakeCabai4(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][4]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][4]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][4]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][4]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][4]))
            PlayerFarmVars[playerid][CabaiArea][4] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai5(playerid);
public TakeCabai5(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][5]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][5]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][5]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][5]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][5]))
            PlayerFarmVars[playerid][CabaiArea][5] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai6(playerid);
public TakeCabai6(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][6]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][6]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][6]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][6]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][6]))
            PlayerFarmVars[playerid][CabaiArea][6] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai7(playerid);
public TakeCabai7(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][7]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][7]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][7]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][7]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][7]))
            PlayerFarmVars[playerid][CabaiArea][7] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai8(playerid);
public TakeCabai8(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][8]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][8]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][8]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][8]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][8]))
            PlayerFarmVars[playerid][CabaiArea][8] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai9(playerid);
public TakeCabai9(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][9]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][9]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][9]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][9]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][9]))
            PlayerFarmVars[playerid][CabaiArea][9] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai10(playerid);
public TakeCabai10(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][10]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][10]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][10]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][10]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][10]))
            PlayerFarmVars[playerid][CabaiArea][10] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai11(playerid);
public TakeCabai11(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][11]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][11]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][11]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][11]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][11]))
            PlayerFarmVars[playerid][CabaiArea][11] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai12(playerid);
public TakeCabai12(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][12]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][12]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][12]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][12]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][12]))
            PlayerFarmVars[playerid][CabaiArea][12] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai13(playerid);
public TakeCabai13(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][13]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][13]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][13]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][13]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][13]))
            PlayerFarmVars[playerid][CabaiArea][13] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai14(playerid);
public TakeCabai14(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][14]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][14]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][14]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][14]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][14]))
            PlayerFarmVars[playerid][CabaiArea][14] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai15(playerid);
public TakeCabai15(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][15]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][15]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][15]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][15]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][15]))
            PlayerFarmVars[playerid][CabaiArea][15] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai16(playerid);
public TakeCabai16(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][16]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][16]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][16]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][16]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][16]))
            PlayerFarmVars[playerid][CabaiArea][16] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai17(playerid);
public TakeCabai17(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][17]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][17]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][17]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][17]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][17]))
            PlayerFarmVars[playerid][CabaiArea][17] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai18(playerid);
public TakeCabai18(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][18]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][18]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][18]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][18]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][18]))
            PlayerFarmVars[playerid][CabaiArea][18] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai19(playerid);
public TakeCabai19(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][19]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][19]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 5);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][19]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][19]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][19]))
            PlayerFarmVars[playerid][CabaiArea][19] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai20(playerid);
public TakeCabai20(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][20]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][20]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 5);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][20]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][20]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][20]))
            PlayerFarmVars[playerid][CabaiArea][20] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeCabai21(playerid);
public TakeCabai21(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][21]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][21]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][21]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][21]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][21]))
            PlayerFarmVars[playerid][CabaiArea][21] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeCabai22(playerid);
public TakeCabai22(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][22]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][22]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][22]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][22]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][22]))
            PlayerFarmVars[playerid][CabaiArea][22] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeCabai23(playerid);
public TakeCabai23(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][23]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][23]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][23]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][23]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][23]))
            PlayerFarmVars[playerid][CabaiArea][23] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeCabai24(playerid);
public TakeCabai24(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][24]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][24]))
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeCabaiTimer[playerid]);
        pTakeCabaiTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Cabe", 2253, 4);
        ShowItemBox(playerid, "ADDED 4x", "CABE", 2253);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][24]))
            DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][24]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][24]))
            PlayerFarmVars[playerid][CabaiArea][24] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu(playerid);
public TakeTebu(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][0]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][0]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][0]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][0]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][0]))
            PlayerFarmVars[playerid][TebuArea][0] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu1(playerid);
public TakeTebu1(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][1]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][1]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][1]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][1]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][1]))
            PlayerFarmVars[playerid][TebuArea][1] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu2(playerid);
public TakeTebu2(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][2]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][2]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][2]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][2]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][2]))
            PlayerFarmVars[playerid][TebuArea][2] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu3(playerid);
public TakeTebu3(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][3]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][3]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][3]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][3]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][3]))
            PlayerFarmVars[playerid][TebuArea][3] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu4(playerid);
public TakeTebu4(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][4]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][4]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][4]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][4]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][4]))
            PlayerFarmVars[playerid][TebuArea][4] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu5(playerid);
public TakeTebu5(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][5]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][5]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][5]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][5]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][5]))
            PlayerFarmVars[playerid][TebuArea][5] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu6(playerid);
public TakeTebu6(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][6]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][6]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][6]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][6]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][6]))
            PlayerFarmVars[playerid][TebuArea][6] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu7(playerid);
public TakeTebu7(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][7]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][7]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][7]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][7]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][7]))
            PlayerFarmVars[playerid][TebuArea][7] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu8(playerid);
public TakeTebu8(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][8]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][8]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][8]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][8]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][8]))
            PlayerFarmVars[playerid][TebuArea][8] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu9(playerid);
public TakeTebu9(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][9]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][9]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][9]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][9]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][9]))
            PlayerFarmVars[playerid][TebuArea][9] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu10(playerid);
public TakeTebu10(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][10]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][10]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][10]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][10]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][10]))
            PlayerFarmVars[playerid][TebuArea][10] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu11(playerid);
public TakeTebu11(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][11]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][11]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][11]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][11]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][11]))
            PlayerFarmVars[playerid][TebuArea][11] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu12(playerid);
public TakeTebu12(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][12]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][12]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][12]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][12]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][12]))
            PlayerFarmVars[playerid][TebuArea][12] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu13(playerid);
public TakeTebu13(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][13]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][13]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][13]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][13]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][13]))
            PlayerFarmVars[playerid][TebuArea][13] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu14(playerid);
public TakeTebu14(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][14]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][14]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][14]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][14]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][14]))
            PlayerFarmVars[playerid][TebuArea][14] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu15(playerid);
public TakeTebu15(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][15]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][15]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][15]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][15]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][15]))
            PlayerFarmVars[playerid][TebuArea][15] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu16(playerid);
public TakeTebu16(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][16]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][16]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][16]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][16]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][16]))
            PlayerFarmVars[playerid][TebuArea][16] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu17(playerid);
public TakeTebu17(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][17]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][17]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][17]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][17]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][17]))
            PlayerFarmVars[playerid][TebuArea][17] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu18(playerid);
public TakeTebu18(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][18]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][18]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][18]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][18]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][18]))
            PlayerFarmVars[playerid][TebuArea][18] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu19(playerid);
public TakeTebu19(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][19]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][19]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][19]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][19]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][19]))
            PlayerFarmVars[playerid][TebuArea][19] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu20(playerid);
public TakeTebu20(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][20]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][20]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][20]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][20]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][20]))
            PlayerFarmVars[playerid][TebuArea][20] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeTebu21(playerid);
public TakeTebu21(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][21]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][21]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][21]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][21]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][21]))
            PlayerFarmVars[playerid][TebuArea][21] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeTebu22(playerid);
public TakeTebu22(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][22]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][22]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][22]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][22]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][22]))
            PlayerFarmVars[playerid][TebuArea][22] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeTebu23(playerid);
public TakeTebu23(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][23]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][23]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][23]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][23]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][23]))
            PlayerFarmVars[playerid][TebuArea][23] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeTebu24(playerid);
public TakeTebu24(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][24]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][24]))
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeTebuTimer[playerid]);
        pTakeTebuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Tebu", 806, 4);
        ShowItemBox(playerid, "ADDED 4x", "TEBU", 806);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][24]))
            DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][24]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][24]))
            PlayerFarmVars[playerid][TebuArea][24] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward ProcessGaram(playerid);
public ProcessGaram(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PetaniOlah]))
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PetaniOlah]))
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");
        return 0;
    }

    if(Inventory_Count(playerid, "Garam Kristal") < 4)
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Garam Kristal tidak cukup! (Min: 4)");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 120)
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Inventory_Remove(playerid, "Garam Kristal");
        Inventory_Add(playerid, "Garam", 1279, 1);
        ShowItemBox(playerid, "ADDED 1x", "GARAM", 1279);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 4;

        new Float: progressvalue = AccountData[playerid][ActivityTime] * 110/120;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward ProcessBeras(playerid);
public ProcessBeras(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PetaniOlah]))
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PetaniOlah]))
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");
        return 0;
    }

    if(Inventory_Count(playerid, "Padi") < 4)
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Padi tidak cukup! (Min: 4)");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 120)
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Inventory_Remove(playerid, "Padi");
        Inventory_Add(playerid, "Beras", 2060, 1);
        ShowItemBox(playerid, "ADDED 1x", "BERAS", 2060);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 4;

        new Float: progressvalue = AccountData[playerid][ActivityTime] * 110/120;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward ProcessGula(playerid);
public ProcessGula(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PetaniOlah]))
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PetaniOlah]))
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");
        return 0;
    }

    if(Inventory_Count(playerid, "Tebu") < 4)
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Tebu tidak cukup! (Min: 4)");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 120)
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Inventory_Remove(playerid, "Tebu");
        Inventory_Add(playerid, "Gula", 1575, 1);
        ShowItemBox(playerid, "ADDED 1x", "GULA", 1575);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 4;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/120;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward ProcessSambel(playerid);
public ProcessSambel(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][PetaniOlah]))
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PetaniOlah]))
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");
        return 0;
    }

    if(Inventory_Count(playerid, "Cabe") < 4)
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Cabai tidak cukup! (Min: 4)");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 120)
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Inventory_Remove(playerid, "Cabe");
        Inventory_Add(playerid, "Sambel", 11722, 1);
        ShowItemBox(playerid, "ADDED 1x", "SAMBEL", 11722);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 4;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/120;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeSalt(playerid);
public TakeSalt(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][0]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][0]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][0]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][0]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][0]))
            PlayerFarmVars[playerid][GaramArea][0] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward TakeSalt1(playerid);
public TakeSalt1(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][1]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][1]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][1]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][1]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][1]))
            PlayerFarmVars[playerid][GaramArea][1] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt2(playerid);
public TakeSalt2(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][2]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][2]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][2]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][2]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][2]))
            PlayerFarmVars[playerid][GaramArea][2] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt3(playerid);
public TakeSalt3(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][3]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][3]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][3]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][3]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][3]))
            PlayerFarmVars[playerid][GaramArea][3] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt4(playerid);
public TakeSalt4(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][4]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][4]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][4]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][4]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][4]))
            PlayerFarmVars[playerid][GaramArea][4] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt5(playerid);
public TakeSalt5(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][5]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][5]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][5]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][5]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][5]))
            PlayerFarmVars[playerid][GaramArea][5] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt6(playerid);
public TakeSalt6(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][6]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][6]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][6]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][6]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][6]))
            PlayerFarmVars[playerid][GaramArea][6] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt7(playerid);
public TakeSalt7(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][7]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][7]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][7]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][7]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][7]))
            PlayerFarmVars[playerid][GaramArea][7] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt8(playerid);
public TakeSalt8(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][8]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][8]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][8]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][8]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][8]))
            PlayerFarmVars[playerid][GaramArea][8] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt9(playerid);
public TakeSalt9(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][9]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][9]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][9]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][9]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][9]))
            PlayerFarmVars[playerid][GaramArea][9] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt10(playerid);
public TakeSalt10(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][10]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][10]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][10]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][10]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][10]))
            PlayerFarmVars[playerid][GaramArea][10] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt11(playerid);
public TakeSalt11(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][11]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][11]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][11]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][11]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][11]))
            PlayerFarmVars[playerid][GaramArea][11] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt12(playerid);
public TakeSalt12(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][12]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][12]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][12]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][12]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][12]))
            PlayerFarmVars[playerid][GaramArea][12] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt13(playerid);
public TakeSalt13(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][13]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][13]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][13]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][13]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][13]))
            PlayerFarmVars[playerid][GaramArea][13] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt14(playerid);
public TakeSalt14(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][14]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][14]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][14]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][14]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][14]))
            PlayerFarmVars[playerid][GaramArea][14] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt15(playerid);
public TakeSalt15(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][15]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][15]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][15]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][15]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][15]))
            PlayerFarmVars[playerid][GaramArea][15] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt16(playerid);
public TakeSalt16(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][16]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][16]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][16]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][16]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][16]))
            PlayerFarmVars[playerid][GaramArea][16] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt17(playerid);
public TakeSalt17(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][17]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][17]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][17]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][17]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][17]))
            PlayerFarmVars[playerid][GaramArea][17] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt18(playerid);
public TakeSalt18(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][18]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][18]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][18]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][18]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][18]))
            PlayerFarmVars[playerid][GaramArea][18] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt19(playerid);
public TakeSalt19(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][19]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][19]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][19]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][19]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][19]))
            PlayerFarmVars[playerid][GaramArea][19] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}
forward TakeSalt20(playerid);
public TakeSalt20(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][20]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][20]))
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTakeSaltTimer[playerid]);
        pTakeSaltTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        HideShortKey(playerid);

        Inventory_Add(playerid, "Garam Kristal", 1611, 5);
        ShowItemBox(playerid, "ADDED 5x", "GARAM KRISTAL", 1611);

        if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][20]))
            DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][20]);

        if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][20]))
            PlayerFarmVars[playerid][GaramArea][20] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}