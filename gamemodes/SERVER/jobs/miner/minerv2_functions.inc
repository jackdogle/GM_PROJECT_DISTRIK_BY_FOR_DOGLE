#include <YSI\y_hooks>

enum _EMiningData 
{
    MinerStoneCooldown[23], 
    STREAMER_TAG_AREA:MinerStoneArea[23],
    STREAMER_TAG_OBJECT:MinerStoneObject[23],
    STREAMER_TAG_AREA:MinerStoneWash[3],
    STREAMER_TAG_AREA:MinerStoneLebur[3],
    STREAMER_TAG_MAP_ICON:MinerStoneIcon[3],
    STREAMER_TAG_3D_TEXT_LABEL:MinerLeburText[3]
};
new PlayerMinerVars[MAX_PLAYERS][_EMiningData];

new pTimerMining[MAX_PLAYERS] = {-1, ...};
new pTimerWash[MAX_PLAYERS] = {-1, ...};
new pTimerLebur[MAX_PLAYERS] = {-1, ...};

stock const Float: MinerStonePoint[][] = 
{
    {2446.571777, 1670.389282, -31.135091},
    {2448.557373, 1674.951904, -30.939241},
    {2452.133056, 1678.152709, -30.729717},
    {2463.547119, 1663.825927, -33.553436},
    {2456.448242, 1673.300170, -46.238826},
    {2461.801269, 1676.579223, -45.890556},
    {2468.667724, 1679.963500, -47.781345},
    {2469.781005, 1665.766113, -49.670333},
    {2490.583007, 1685.236328, -44.937145},
    {2500.900390, 1683.178344, -46.636669},
    {2503.343261, 1681.015869, -49.203823},
    {2511.181152, 1664.836547, -49.823101},
    {2521.978027, 1678.756958, -42.580474},
    {2526.270751, 1676.746215, -42.890468},
    {2522.802734, 1664.866943, -49.731365},
    {2510.872314, 1664.304321, -46.764965},
    {2482.658447, 1691.915893, -23.266759},
    {2486.969726, 1692.306152, -23.096754},
    {2518.243652, 1683.548950, -30.134899},
    {2520.863037, 1682.450073, -30.134899},
    {2520.142333, 1661.838623, -29.001743},
    {2498.593261, 1660.792724, -27.500534},
    {2526.854980, 1660.735351, -17.910015}
};

stock MinerJobStuffs(playerid) 
{
    UnloadMinerJobStuffs(playerid);

    PlayerMinerVars[playerid][MinerLeburText][0] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Meleburkan Batu", -1, 2152.3289, -2263.5745, 13.3000+0.4, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, playerid);
    PlayerMinerVars[playerid][MinerLeburText][1] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Meleburkan Batu", -1, 2147.9492, -2263.9167, 13.2982+0.4, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, playerid);
    PlayerMinerVars[playerid][MinerLeburText][2] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Meleburkan Batu", -1, 2152.1406, -2267.9675, 13.3071+0.4, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, playerid);

    PlayerMinerVars[playerid][MinerStoneIcon][0] = CreateDynamicMapIcon(686.5589, 896.8207, - 39.5803, 11, -1, 0, 0, playerid, 9999.0, MAPICON_GLOBAL, -1, 1);
    PlayerMinerVars[playerid][MinerStoneIcon][1] = CreateDynamicMapIcon(-412.7031, 1197.8976, 2.2932, 11, -1, 0, 0, playerid, 9999.0, MAPICON_GLOBAL, -1, 1);
    PlayerMinerVars[playerid][MinerStoneIcon][2] = CreateDynamicMapIcon(2193.07, -2253.17,  13.54, 11, -1, 0, 0, playerid, 9999.0, MAPICON_GLOBAL, -1, 1);

    PlayerMinerVars[playerid][MinerStoneLebur][0] = CreateDynamicSphere(2152.4473, -2263.5190, 13.3000, 2.0, 0, 0, playerid);
    PlayerMinerVars[playerid][MinerStoneLebur][1] = CreateDynamicSphere(2152.1008, -2268.0110, 13.3072, 2.0, 0, 0, playerid);
    PlayerMinerVars[playerid][MinerStoneLebur][2] = CreateDynamicSphere(2147.9453, -2263.9194, 13.2982, 2.0, 0, 0, playerid);
    PlayerMinerVars[playerid][MinerStoneWash] = CreateDynamicSphere(-414.8238,1198.8524,1.1200, 10.0, 0, 0, playerid);

    for(new x = 0; x < 23; x++)
    {
        PlayerMinerVars[playerid][MinerStoneObject][x] = CreateDynamicObject(3930, MinerStonePoint[x][0], MinerStonePoint[x][1], MinerStonePoint[x][2], 0.000000, 0.000000, 0.000000, -1, 10, playerid, 400.00, 400.00);
        PlayerMinerVars[playerid][MinerStoneArea][x] = CreateDynamicSphere(MinerStonePoint[x][0], MinerStonePoint[x][1], MinerStonePoint[x][2], 1.5, -1, 10, playerid);
    }
    return 1;
}

UnloadMinerJobStuffs(playerid) 
{
    for(new x = 0; x < 3; x ++) 
    {
        if(DestroyDynamicArea(PlayerMinerVars[playerid][MinerStoneLebur][x]))
            PlayerMinerVars[playerid][MinerStoneLebur][x] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(PlayerMinerVars[playerid][MinerStoneIcon][x]))
            PlayerMinerVars[playerid][MinerStoneIcon][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        if(DestroyDynamic3DTextLabel(PlayerMinerVars[playerid][MinerLeburText][x]))
            PlayerMinerVars[playerid][MinerLeburText][x] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    }
    
    if(DestroyDynamicArea(PlayerMinerVars[playerid][MinerStoneWash]))
        PlayerMinerVars[playerid][MinerStoneWash] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
    
    for(new x = 0; x < 23; x++)
    {
        if(DestroyDynamicArea(PlayerMinerVars[playerid][MinerStoneArea][x]))
            PlayerMinerVars[playerid][MinerStoneArea][x] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        
        if(DestroyDynamicObject(PlayerMinerVars[playerid][MinerStoneObject][x]))
            PlayerMinerVars[playerid][MinerStoneObject][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    pTimerMining[playerid] = -1;
    pTimerWash[playerid] = -1;
    pTimerLebur[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pTimerMining[playerid]);
    KillTimer(pTimerWash[playerid]);
    KillTimer(pTimerLebur[playerid]);
    pTimerMining[playerid] = -1;
    pTimerWash[playerid] = -1;
    pTimerLebur[playerid] = -1;
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid) 
{
    if(AccountData[playerid][pJob] == JOB_MINER && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        for(new x = 0; x < 23; x++)
        {
            if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][MinerStoneArea][x]))
            {
                if(areaid == PlayerMinerVars[playerid][MinerStoneArea][x])
                {
                    if(PlayerMinerVars[playerid][MinerStoneCooldown][x] == 0)
                    {
                        ShowKey(playerid, "[Y] Ambil Batuan");
                    }
                }
            }
        }

        if(areaid == PlayerMinerVars[playerid][MinerStoneWash])
        {
            ShowKey(playerid, "[Y] Cuci Batuan");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid) 
{
    for(new x = 0; x < 23; x++) 
    {
        if(areaid == PlayerMinerVars[playerid][MinerStoneArea][x]) 
        {
            HideShortKey(playerid);
        }
    }

    if(areaid == PlayerMinerVars[playerid][MinerStoneWash])
    {
        HideShortKey(playerid);
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pJob] == JOB_MINER) 
        {
            for(new x = 0; x < 23; x++) 
            {
                if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][MinerStoneArea][x])) 
                {
                    if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                    if(PlayerMinerVars[playerid][MinerStoneCooldown][x] != 0) return 0;
                    if(Inventory_Count(playerid, "Batu Kotor") >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Batu Kotor anda sudah mencapai max (100)!");

                    AccountData[playerid][ActivityTime] = 1;
                    pTimerMining[playerid] = SetTimerEx("MinerStoneTake", 1000, true, "dd", playerid, x);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENAMBANG");
                    ShowProgressBar(playerid);
                    HideShortKey(playerid);
                    ApplyAnimation(playerid, "RIOT", "RIOT_ANGRY_B", 4.1, 1, 0, 0, 0, 0, 1);
                    SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.028, -0.127, 0.021, 95.800, 94.400, -85.000, 1.000, 1.000, 1.000);
                }
            }

            if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][MinerStoneWash]))
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                if(Inventory_Count(playerid, "Batu Kotor") < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Batu kotor tidak mencukupi! (Min: 1)");
                if(Inventory_Count(playerid, "Batu Bersih") >= 100) return ShowTDN(playerid, NOTIFICATION_ERROR, "Batu Bersih anda sudah mencapai max (100)!");

                AccountData[playerid][ActivityTime] = 1;
                pTimerWash[playerid] = SetTimerEx("MinerWashing", 1000, true, "d", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENCUCI BATUAN");
                ShowProgressBar(playerid);
                HideShortKey(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            }

            for(new x = 0; x < 3; x++)
            {
                if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][MinerStoneLebur][x]))
                {
                    if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                    if(!PlayerHasItem(playerid, "Batu Bersih")) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak memiliki batu bersih");

                    AccountData[playerid][ActivityTime] = 1;
                    pTimerLebur[playerid] = SetTimerEx("MinerLebur", 1000, true, "dd", playerid, x);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MELEBUR BATUAN");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
            }
        }
    }
    return 1;
}

forward MinerStoneTake(playerid, t);
public MinerStoneTake(playerid, t) 
{
    if(t < 0 || t >= 31) return 0;
    
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerMining[playerid]);
        pTimerMining[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }
    
    if(!IsValidDynamicArea(PlayerMinerVars[playerid][MinerStoneArea][t]))
    {
        KillTimer(pTimerMining[playerid]);
        pTimerMining[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, 9);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][MinerStoneArea][t]))
    {
        KillTimer(pTimerMining[playerid]);
        pTimerMining[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, 9);
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
        KillTimer(pTimerMining[playerid]);
        pTimerMining[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, 9);
        return 0;
    }

    if(AccountData[playerid][pInjured]) 
    {
        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang pingsan");
        KillTimer(pTimerMining[playerid]);
        pTimerMining[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, 9);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 10)
    {
        KillTimer(pTimerMining[playerid]);
        pTimerMining[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, 9);

        if(DestroyDynamicArea(PlayerMinerVars[playerid][MinerStoneArea][t]))
            PlayerMinerVars[playerid][MinerStoneArea][t] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        
        PlayerMinerVars[playerid][MinerStoneCooldown][t] = 45;
        AccountData[playerid][pThirst] --;

        new rands = RandomEx(1, 101), randbatu = RandomEx(1, 5);
        if(GetTotalWeightFloat(playerid) > 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");

        switch(rands) 
        {
            case 1..79:
            {
                Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
                ShowItemBox(playerid, sprintf("Received %dx", randbatu), "Batu Kotor", 3930);
            }
            case 80..100:
            {
                Inventory_Add(playerid, "Batu Kotor", 3930, 1);

                new randv = RandomEx(1, 4);
                Inventory_Add(playerid, "Material", 19843, randv);
                ShowItemBox(playerid, sprintf("Received %dx", randv), "Material", 19843);
                ShowItemBox(playerid, "Received 1x", "Batu Kotor", 3930);
            }
        }
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        static Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime]*110/10;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        PlayerPlayNearbySound(playerid, 1135);
        return 0;
    }
    return 1;
}

forward MinerWashing(playerid);
public MinerWashing(playerid) 
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerWash[playerid]);
        pTimerWash[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerMinerVars[playerid][MinerStoneWash]))
    {
        KillTimer(pTimerWash[playerid]);
		pTimerWash[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][MinerStoneWash]))
    {
        KillTimer(pTimerWash[playerid]);
		pTimerWash[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured]) 
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pTimerWash[playerid]);
		pTimerWash[playerid] = -1;
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
        KillTimer(pTimerWash[playerid]);
		pTimerWash[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 8)
    {
        KillTimer(pTimerWash[playerid]);
		pTimerWash[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        if(GetTotalWeightFloat(playerid) > 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");

        new rand = RandomEx(1, 15);
        Inventory_Add(playerid, "Component", 3096, rand);
        ShowItemBox(playerid, sprintf("Received %dx", rand), "Material", 3096);
        Inventory_Remove(playerid, "Batu Kotor", 5);
        Inventory_Add(playerid, "Batu Bersih", 2936, 5);
        ShowItemBox(playerid, "Removed 5x", "Batu Kotor", 3930);
        ShowItemBox(playerid, "Received 5x", "Batu Bersih", 2936);
        
        AccountData[playerid][pThirst] --;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        static Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime]*110/8;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward MinerLebur(playerid, t);
public MinerLebur(playerid, t)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerLebur[playerid]);
        pTimerLebur[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerMinerVars[playerid][MinerStoneLebur][t])) 
    {
        KillTimer(pTimerLebur[playerid]);
        pTimerLebur[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][MinerStoneLebur][t]))
    {
        KillTimer(pTimerLebur[playerid]);
        pTimerLebur[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pTimerLebur[playerid]);
        pTimerLebur[playerid] = -1;
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
        KillTimer(pTimerLebur[playerid]);
        pTimerLebur[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!PlayerHasItem(playerid, "Batu Bersih"))
    {
        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak memiliki batu bersih!");
        KillTimer(pTimerLebur[playerid]);
        pTimerLebur[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 6)
    {
        KillTimer(pTimerLebur[playerid]);
        pTimerLebur[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        new rands = RandomEx(1, 71), randbesi = RandomEx(1, 3);
        new randtembaga = RandomEx(1, 2), randemas = RandomEx(1, 2);
        if(GetTotalWeightFloat(playerid) > 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
        switch(rands) 
        {
            case 1..50:
            {
                Inventory_Remove(playerid, "Batu Bersih");
                Inventory_Add(playerid, "Besi", 19809, randbesi);
                Inventory_Add(playerid, "Tembaga", 11748, randtembaga);
                ShowItemBox(playerid, sprintf("Received %dx", randbesi), "Besi", 19809);
                ShowItemBox(playerid, sprintf("Received %dx", randtembaga), "Tembaga", 11748);
            }
            case 51..55:
            {
                Inventory_Remove(playerid, "Batu Bersih");
                Inventory_Add(playerid, "Emas", 19941, randemas);
                ShowItemBox(playerid, sprintf("Received %dx", randemas), "Emas", 19941);
            }
            case 56..58:
            {
                Inventory_Remove(playerid, "Batu Bersih");
                Inventory_Add(playerid, "Berlian", 19941, 1);
                ShowItemBox(playerid, "Received 1x", "Berlian", 19941);
            }
            case 59..70:
            {
                Inventory_Remove(playerid, "Batu Bersih");
                Inventory_Add(playerid, "Tembaga", 11748, randtembaga);
                ShowItemBox(playerid, sprintf("Received %dx", randtembaga), "Tembaga", 11748);
            }
        }
        AccountData[playerid][pThirst] --;
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;
        
        static Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime]*110/6;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

ptask MinerStoneCooldownUpdate[1000](playerid) 
{
    if(AccountData[playerid][pJob] == JOB_MINER) 
    {
        for(new x = 0; x < 23; x++)
        {
            if(PlayerMinerVars[playerid][MinerStoneCooldown][x] > 0)
            {
                PlayerMinerVars[playerid][MinerStoneCooldown][x] --;
                if(PlayerMinerVars[playerid][MinerStoneCooldown][x] == 0)
                {
                    PlayerMinerVars[playerid][MinerStoneArea][x] = CreateDynamicSphere(MinerStonePoint[x][0], MinerStonePoint[x][1], MinerStonePoint[x][2], 1.5, -1, 10, playerid);
                    PlayerMinerVars[playerid][MinerStoneCooldown][x] = 0;
                }
            }
        }
    }
    return 1;
}