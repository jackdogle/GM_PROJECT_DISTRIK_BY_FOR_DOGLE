#include <YSI\y_hooks>

hook OnPlayerConnect(playerid)
{
    pBenangTimer[playerid] = -1;
    pKainTimer[playerid] = -1;
    pJahitTimer[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pBenangTimer[playerid]);
    KillTimer(pKainTimer[playerid]);
    KillTimer(pJahitTimer[playerid]);
    pBenangTimer[playerid] = -1;
    pKainTimer[playerid] = -1;
    pJahitTimer[playerid] = -1;
    return 1;
}

forward CollectBenang(playerid);
public CollectBenang(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pBenangTimer[playerid]);
        pBenangTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(IsPlayerInjured(playerid))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pBenangTimer[playerid]);
        pBenangTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(GetTotalWeightStatus(playerid) >= 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");
        KillTimer(pBenangTimer[playerid]);
        pBenangTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!TailorBenang_Area(playerid))
    {
        KillTimer(pBenangTimer[playerid]);
        pBenangTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!PlayerHasItem(playerid, "Bulu"))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Bulu tidak cukup! (Min: 1)");
        KillTimer(pBenangTimer[playerid]);
        pBenangTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pBenangTimer[playerid]);
        pBenangTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Bulu", 1);
        Inventory_Add(playerid, "Benang", 1902, 2);
        ShowItemBox(playerid, "Removed 1x", "Bulu", 19517);
        ShowItemBox(playerid, "Received 2x", "Benang", 1902);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 18.75;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward CollectKain(playerid);
public CollectKain(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pKainTimer[playerid]);
        pKainTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!TailorKaC_Area(playerid))
    {
        KillTimer(pKainTimer[playerid]);
        pKainTimer[playerid] = -1;
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
        KillTimer(pKainTimer[playerid]);
        pKainTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!PlayerHasItem(playerid, "Benang"))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Benang tidak cukup! (Min: 1)");
        KillTimer(pKainTimer[playerid]);
        pKainTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(GetTotalWeightStatus(playerid) >= 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");
        KillTimer(pKainTimer[playerid]);
        pKainTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }
    
    if(AccountData[playerid][ActivityTime] >= 120)
    {
        KillTimer(pKainTimer[playerid]);
        pKainTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Benang", 1);
        Inventory_Add(playerid, "Kain", 11747, 2);
        ShowItemBox(playerid, "Received 2x", "Kain", 11747);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 15;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/120;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward CollectPakaian(playerid);
public CollectPakaian(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pJahitTimer[playerid]);
        pJahitTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!TailorKaC_Area(playerid))
    {
        KillTimer(pJahitTimer[playerid]);
        pJahitTimer[playerid] = -1;
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
        KillTimer(pJahitTimer[playerid]);
        pJahitTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(GetTotalWeightStatus(playerid) >= 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda penuh!");
        KillTimer(pJahitTimer[playerid]);
        pJahitTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!PlayerHasItem(playerid, "Kain"))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Kain tidak cukup! (Min: 1)");
        KillTimer(pJahitTimer[playerid]);
        pJahitTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 145)
    {
        KillTimer(pJahitTimer[playerid]);
        pJahitTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Kain", 1);
        Inventory_Add(playerid, "Pakaian", 2399, 1);
        ShowItemBox(playerid, "Removed 1x", "Kain", 11747);
        ShowItemBox(playerid, "Received 1x", "Pakaian", 2399);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 14.5;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/145;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}