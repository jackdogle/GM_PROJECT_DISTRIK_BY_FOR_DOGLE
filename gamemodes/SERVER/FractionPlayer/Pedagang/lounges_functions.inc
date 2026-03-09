#include <YSI\y_hooks>

forward ProcessEsTeh(playerid);
public ProcessEsTeh(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if((!IsValidDynamicArea(Pedagang_Stuff[PdgCooking]) && !IsValidDynamicArea(Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if((!IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCooking]) && !IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Gula") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Gula tidak cukup, (Min: 10)");
        return 0;
    }

    if(Inventory_Count(playerid, "Air Mineral") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Air Mineral tidak cukup, (Min: 10)");
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 3)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Gula", 10);
        Inventory_Remove(playerid, "Air Mineral", 10);
        Inventory_Add(playerid, "Es Teh", 1546, 10);
        ShowItemBox(playerid, "Received 10x", "Es Teh", 1546);
    }
    else 
    {
        AccountData[playerid][ActivityTime]  ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/3;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward ProccesEsJeruk(playerid);
public ProccesEsJeruk(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pCookingTimer[playerid]);
        pCookingTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }
    if(AccountData[playerid][pInjured])
    {
        KillTimer(pCookingTimer[playerid]);
        pCookingTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }
    if(Inventory_Count(playerid, "Gula") < 5)
    {
        KillTimer(pCookingTimer[playerid]);
        pCookingTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Gula tidak cukup, (Min: 5)");
        return 0;
    }

    if(Inventory_Count(playerid, "Air Mineral") < 5)
    {
        KillTimer(pCookingTimer[playerid]);
        pCookingTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Air Mineral tidak cukup, (Min: 5)");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 10)
    {
        KillTimer(pCookingTimer[playerid]);
        pCookingTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Gula", 5);
        Inventory_Remove(playerid, "Air Mineral", 5);
        AccountData[playerid][pThirst] += 15;
        Info(playerid, "Anda berhasil membuat jus jeruk lalu meminum nya");
    }
    else 
    {
        AccountData[playerid][ActivityTime]  ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/10;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward ProccesNasiPecelAl(playerid);
public ProccesNasiPecelAl(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pCookingTimer[playerid]);
        pCookingTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pCookingTimer[playerid]);
        pCookingTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Ikan") < 5)
    {
        KillTimer(pCookingTimer[playerid]);
        pCookingTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Ikan tidak cukup, (Min: 5)");
        return 0;
    }

    if(Inventory_Count(playerid, "Beras") < 5)
    {
        KillTimer(pCookingTimer[playerid]);
        pCookingTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Beras tidak cukup, (Min: 5)");
        return 0;
    }

    if(Inventory_Count(playerid, "Sambal") < 5)
    {
        KillTimer(pCookingTimer[playerid]);
        pCookingTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Sambal tidak cukup, (Min: 5)");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 10)
    {
        KillTimer(pCookingTimer[playerid]);
        pCookingTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Beras", 5);
        Inventory_Remove(playerid, "Ikan", 5);
        Inventory_Remove(playerid, "Sambal", 5);
        AccountData[playerid][pHunger] += 10;
        Info(playerid, "Anda berhasil memasak nasi pecel lalu memakannya!");
    }
    else 
    {
        AccountData[playerid][ActivityTime]  ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/10;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}


forward ProcessNasiGoreng(playerid);
public ProcessNasiGoreng(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if((!IsValidDynamicArea(Pedagang_Stuff[PdgCooking]) && !IsValidDynamicArea(Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if((!IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCooking]) && !IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Beras") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Beras tidak cukup, (Min: 10)");
        return 0;
    }

    if(Inventory_Count(playerid, "Sambal") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Sambal tidak cukup, (Min: 10)");
        return 0;
    }

    if(Inventory_Count(playerid, "Garam") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Garam tidak cukup, (Min: 10)");
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 3)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Beras", 10);
        Inventory_Remove(playerid, "Garam", 10);
        Inventory_Remove(playerid, "Sambal", 10);
        Inventory_Add(playerid, "Nasi Goreng", 2355, 10);
        ShowItemBox(playerid, "Received 10x", "Nasi Goreng", 2355);
    }
    else 
    {
        AccountData[playerid][ActivityTime]  ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/3;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward ProcessBakso(playerid);
public ProcessBakso(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if((!IsValidDynamicArea(Pedagang_Stuff[PdgCooking]) && !IsValidDynamicArea(Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if((!IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCooking]) && !IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Ikan") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Ikan tidak cukup, (Min: 10)");
        return 0;
    }

    if(Inventory_Count(playerid, "Sambal") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Sambal tidak cukup, (Min: 10)");
        return 0;
    }

    if(Inventory_Count(playerid, "Garam") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Garam tidak cukup, (Min: 10)");
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 3)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Ikan", 10);
        Inventory_Remove(playerid, "Garam", 10);
        Inventory_Remove(playerid, "Sambal", 10);
        Inventory_Add(playerid, "Bakso", 19567, 10);
        ShowItemBox(playerid, "Received 10x", "Bakso", 19567);
    }
    else 
    {
        AccountData[playerid][ActivityTime]  ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/3;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward ProcessNasiPecel(playerid);
public ProcessNasiPecel(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if((!IsValidDynamicArea(Pedagang_Stuff[PdgCooking]) && !IsValidDynamicArea(Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if((!IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCooking]) && !IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Ikan") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Ikan tidak cukup, (Min: 10)");
        return 0;
    }

    if(Inventory_Count(playerid, "Beras") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Beras tidak cukup, (Min: 10)");
        return 0;
    }

    if(Inventory_Count(playerid, "Sambal") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Sambal tidak cukup, (Min: 10)");
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 3)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Beras", 10);
        Inventory_Remove(playerid, "Ikan", 10);
        Inventory_Remove(playerid, "Sambal", 10);
        Inventory_Add(playerid, "Nasi Pecel", 2355, 10);
        ShowItemBox(playerid, "Received 10x", "Nasi Pecel", 19567);
    }
    else 
    {
        AccountData[playerid][ActivityTime]  ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/3;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward ProcessSusuFresh(playerid);
public ProcessSusuFresh(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if((!IsValidDynamicArea(Pedagang_Stuff[PdgCooking]) && !IsValidDynamicArea(Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if((!IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCooking]) && !IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Gula") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Gula tidak cukup, (Min: 10)");
        return 0;
    }

    if(Inventory_Count(playerid, "Susu Olahan") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Susu Olahan tidak cukup, (Min: 10)");
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 3)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Gula", 10);
        Inventory_Remove(playerid, "Susu Olahan", 10);
        Inventory_Add(playerid, "Susu Fresh", 19569, 10);
        ShowItemBox(playerid, "Received 10x", "Susu Fresh", 19569);
    }
    else 
    {
        AccountData[playerid][ActivityTime]  ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/3;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward ProcessBurdas(playerid);
public ProcessBurdas(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if((!IsValidDynamicArea(Pedagang_Stuff[PdgCooking]) && !IsValidDynamicArea(Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if((!IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCooking]) && !IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Sambal") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Sambal tidak cukup, (Min: 10)");
        return 0;
    }

    if(Inventory_Count(playerid, "Ayam Kemas") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Ayam Kemas tidak cukup, (Min: 10)");
        return 0;
    }

    if(Inventory_Count(playerid, "Beras") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Beras tidak cukup, (Min: 10)");
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 3)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Beras", 10);
        Inventory_Remove(playerid, "Sambal", 10);
        Inventory_Remove(playerid, "Ayam Kemas", 10);
        Inventory_Add(playerid, "Bubur Pedas", 19568, 10);
        ShowItemBox(playerid, "Received 10x", "Bubur Pedas", 19568);
    }
    else 
    {
        AccountData[playerid][ActivityTime]  ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/3;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward ProcessKopiKenangan(playerid);
public ProcessKopiKenangan(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if((!IsValidDynamicArea(Pedagang_Stuff[PdgCooking]) && !IsValidDynamicArea(Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if((!IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCooking]) && !IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Gula") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Gula tidak cukup, (Min: 10)");
        return 0;
    }

    if(Inventory_Count(playerid, "Air Mineral") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Air Mineral tidak cukup, (Min: 10)");
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 3)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Air Mineral", 10);
        Inventory_Remove(playerid, "Gula", 10);
        Inventory_Add(playerid, "Kopi Kenangan", 19835, 10);
        ShowItemBox(playerid, "Received 10x", "Kopi Kenangan", 19835);
    }
    else 
    {
        AccountData[playerid][ActivityTime]  ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/3;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward ProcessMatcha(playerid);
public ProcessMatcha(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if((!IsValidDynamicArea(Pedagang_Stuff[PdgCooking]) && !IsValidDynamicArea(Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if((!IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCooking]) && !IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCookingEms])))
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Gula") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Gula tidak cukup, (Min: 10)");
        return 0;
    }

    if(Inventory_Count(playerid, "Air Mineral") < 10)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Air Mineral tidak cukup, (Min: 10)");
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 3)
    {
        KillTimer(pMasakTimer[playerid]);
        pMasakTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Air Mineral", 10);
        Inventory_Remove(playerid, "Gula", 10);
        Inventory_Add(playerid, "Choco Matcha", 1667, 10);
        ShowItemBox(playerid, "Received 10x", "Choco Matcha", 1667);
    }
    else 
    {
        AccountData[playerid][ActivityTime]  ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/3;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}