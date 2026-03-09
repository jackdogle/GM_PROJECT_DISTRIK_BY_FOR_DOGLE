#include <YSI\y_hooks>
new pTimerMancing[MAX_PLAYERS] = {-1, ...};
new pTimerSellFish[MAX_PLAYERS] = {-1, ...};

new STREAMER_TAG_AREA:FishingArea[8];
new STREAMER_TAG_AREA:SellFishArea;
new STREAMER_TAG_AREA:SellFishIlegalArea;

static Float:FishingPoint[][] = 
{
    {406.5300,-2103.3367,4.3839},
    {398.5721,-2103.3367,4.3859},
    {390.5535,-2103.3367,4.3859},
    {382.5461,-2103.3367,4.3859},
    {374.5326,-2103.3367,4.3859},
    {366.5767,-2103.3367,4.3859},
    {358.4902,-2103.3367,4.3859},
    {350.5006,-2103.3367,4.3859}
};

hook OnPlayerConnect(playerid)
{
    pTimerMancing[playerid] = -1;
    pTimerSellFish[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pTimerMancing[playerid]);
    KillTimer(pTimerSellFish[playerid]);
    pTimerMancing[playerid] = -1;
    pTimerSellFish[playerid] = -1;
    return 1;
}

hook OnGameModeInit()
{
    for(new x = 0; x < 8; x ++)
    {
        FishingArea[x] = CreateDynamicSphere(FishingPoint[x][0], FishingPoint[x][1], FishingPoint[x][2], 2.0, 0, 0, -1), CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Memancing", -1, FishingPoint[x][0], FishingPoint[x][1], FishingPoint[x][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 15.0, -1, 0);
    }
    SellFishArea = CreateDynamicSphere(359.720977, -2032.062255, 7.835937, 2.0, 0, 0, -1); 
    SellFishIlegalArea = CreateDynamicSphere(2160.7388, -102.3210, 2.7500, 2.0, 0, 0, -1);
    CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Jual Hiu/Penyu", -1, 2160.7388, -102.3210, 2.7500, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 15.0, -1, 0);
    CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Jual Ikan", -1, 359.720977, -2032.062255, 7.835937, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 15.0, -1, 0);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInDynamicArea(playerid, SellFishArea))
        {
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
            if(!PlayerHasItem(playerid, "Ikan Tawar")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki ikan tawar untuk dijual!");

            AccountData[playerid][ActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENJUAL IKAN");
            ShowProgressBar(playerid);

            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            pTimerSellFish[playerid] = SetTimerEx("SellingFish", 1000, true, "d", playerid);
        }

        if(IsPlayerInDynamicArea(playerid, SellFishIlegalArea))
        {
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
            new count, count2;
            foreach(new i : Player) if (IsPlayerConnected(i)) if (SQL_IsCharacterLogged(i))
            {
                if(AccountData[i][pFaction] == FACTION_POLISI && AccountData[i][pDutyPD]) count++;
                if(AccountData[i][pFaction] == FACTION_EMS && AccountData[i][pDutyEms]) count2++;
            }
            if(count <= 4 && count2 <= 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 Polisi Duty & 2 EMS Duty");
            
            ShowPlayerDialog(playerid, DIALOG_SELLFISH_ILEGAL, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Sell Ilegal Fish",
            "Ikan Hiu\nPenyu", "Pilih", "Batal");
        }

        for(new x = 0; x < 8; x ++)
        {
            if(IsPlayerInDynamicArea(playerid, FishingArea[x]))
            {
                if(!PlayerHasItem(playerid, "Pancingan")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki pancingan!");
                if(!PlayerHasItem(playerid, "Umpan")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki umpan!");

                ApplyAnimationEx(playerid, "SWORD", "sword_block", 50.0, 0, 1, 0, 1, 1, 1);
                SetPlayerAttachedObject(playerid, 9,18632,6,0.079376,0.037070,0.007706,181.482910,0.000000,0.000000,1.000000,1.000000,1.000000);
                if(!IsValidBarFish(playerid)) 
                {
                    BarFish(playerid, "Anda sedang mancing", "FishingTime");
                    SetPVarInt(playerid, "FishingAreaID", x);
                }
            }
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_SELLFISH_ILEGAL:
        {
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu sampai progress selesai!");
            switch(listitem)
            {
                case 0: //hiu
                {
                    if(!PlayerHasItem(playerid, "Hiu")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki ikan hiu!");
                    
                    AccountData[playerid][ActivityTime] = 1;
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "JUAL HIU");
                    ShowProgressBar(playerid);

                    ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                    pTimerSellFish[playerid] = SetTimerEx("SellShark", 1000, true, "i", playerid);
                }
                case 1: //penyu
                {
                    if(!PlayerHasItem(playerid, "Penyu")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki penyu!");
                    
                    AccountData[playerid][ActivityTime] = 1;
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "JUAL PENYU");
                    ShowProgressBar(playerid);

                    ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                    pTimerSellFish[playerid] = SetTimerEx("SellPenyu", 1000, true, "i", playerid);
                }
            }
        }
    }
    return 1;
}

/* Other Func */
forward SellPenyu(playerid);
public SellPenyu(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, SellFishIlegalArea))
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsValidDynamicArea(SellFishIlegalArea))
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!PlayerHasItem(playerid, "Penyu"))
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki penyu!");
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        new count = Inventory_Count(playerid, "Penyu");
        new price = count * 150;

        SendClientMessageEx(playerid, -1, "[i] Anda mendapatkan "RED"%s"WHITE" uang merah dari hasil penjualan penyu sejumlah "YELLOW"%dx", FormatMoney(price), count);
        Inventory_Remove(playerid, "Penyu", count);
        ShowItemBox(playerid, sprintf("Removed %dx", count), "Penyu", 1609);
        AccountData[playerid][pRedMoney] += price;
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

forward SellShark(playerid);
public SellShark(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, SellFishIlegalArea))
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsValidDynamicArea(SellFishIlegalArea))
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!PlayerHasItem(playerid, "Hiu"))
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki ikan hiu!");
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        new count = Inventory_Count(playerid, "Hiu");
        new price = count * 250;

        SendClientMessageEx(playerid, -1, "[i] Anda mendapatkan "RED"%s"WHITE" uang merah dari hasil penjualan hiu sejumlah "YELLOW"%dx", FormatMoney(price), count);
        Inventory_Remove(playerid, "Hiu", count);
        ShowItemBox(playerid, sprintf("Removed %dx", count), "Hiu", 1608);
        AccountData[playerid][pRedMoney] += price;
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

forward FishingTime(playerid);
public FishingTime(playerid)
{
    new x = GetPVarInt(playerid, "FishingAreaID");
    if(x == 0) return 0;

    if(!IsPlayerConnected(playerid))
    {
        return 0;
    }

    if(!IsValidDynamicArea(FishingArea[x]))
    {
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
        RemovePlayerAttachedObject(playerid, 9);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, FishingArea[x]))
    {
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
        RemovePlayerAttachedObject(playerid, 9);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
        RemovePlayerAttachedObject(playerid, 9);
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
        RemovePlayerAttachedObject(playerid, 9);
        return 0;
    }
    ClearAnimations(playerid, 1);
    StopLoopingAnim(playerid);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
    RemovePlayerAttachedObject(playerid, 9);

    Inventory_Remove(playerid, "Umpan");
    ShowItemBox(playerid, "Removed 1x", "Umpan", 1603);

    new rands = RandomEx(1, 58), randikan = RandomEx(3, 10);
    switch(rands)
    {
        case 1..10:
        {
            Inventory_Add(playerid, "Ikan Tawar", 1599, randikan);
            ShowItemBox(playerid, sprintf("Received %dx", randikan), "Ikan Tawar", 1599);
        }
        case 11..21:
        {
            SendClientMessageEx(playerid, -1, "[i] Pancingan mu terbawa ikan besar dan jatuh ke dasar laut");
            Inventory_Remove(playerid, "Pancingan");
        }
        case 22..31:
        {
            SendClientMessage(playerid, -1, "[i] Anda zonk mendapatkan sampah makanan");
            Inventory_Add(playerid, "Sampah Makanan", 2840);
            ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);
        }
        case 32..50:
        {
            Inventory_Add(playerid, "Ikan Tawar", 1599);
            ShowItemBox(playerid, "Removed 1x", "Umpan", 1603);
            ShowItemBox(playerid, "Received 1x", "Ikan Tawar", 1599);
        }
        case 51..53:
        {
            Inventory_Add(playerid, "Ikan Tawar", 1599, 50);
            ShowItemBox(playerid, "Received 50x", "Ikan Tawar", 1599);
            Info(playerid, "Anda beruntung karena mendapatkan "YELLOW"50"WHITE" ikan hari ini");
        }
        case 54..55:
        {
            Inventory_Add(playerid, "Penyu", 1609);
            ShowItemBox(playerid, "Received 1x", "Penyu", 1609);
        }
        case 56..57:
        {
            Inventory_Add(playerid, "Hiu", 1608);
            ShowItemBox(playerid, "Received 1x", "Hiu", 1608);
        }
    }
    GivePlayerXP(playerid, 1);
    return 1;
}

forward SellingFish(playerid);
public SellingFish(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(SellFishArea))
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, SellFishArea))
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }
    
    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pTimerSellFish[playerid]);
        pTimerSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    
        new value = Inventory_Count(playerid, "Ikan Tawar");
        ShowItemBox(playerid, sprintf("Removed %dx", value), "Ikan Tawar", 1599);
        ShowItemBox(playerid, sprintf("Received %s", FormatMoney(value * 3)), "Uang", 1212);
        Inventory_Remove(playerid, "Ikan Tawar", value);
        GiveMoney(playerid, (value * 3));
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