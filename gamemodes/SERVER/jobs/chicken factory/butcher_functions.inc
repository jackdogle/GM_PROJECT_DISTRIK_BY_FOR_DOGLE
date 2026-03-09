#include <YSI\y_hooks>

new pTimerTakeAyam[MAX_PLAYERS] = {-1, ...};
new pTimerButcher[MAX_PLAYERS] = {-1, ...};
new pTimerPackChicken[MAX_PLAYERS] = {-1, ...};

enum e_butcherdata
{
    STREAMER_TAG_AREA:ButcherStartArea,
    STREAMER_TAG_AREA:ButcherProcessArea[4],
    STREAMER_TAG_AREA:ButcherPackArea[6],
    STREAMER_TAG_AREA:ButcherTakeChicken,

    STREAMER_TAG_3D_TEXT_LABEL:ButcherStartLabel,
    STREAMER_TAG_3D_TEXT_LABEL:ButcherProcessLabel[4],
    STREAMER_TAG_3D_TEXT_LABEL:ButcherPackLabel[6],
    
    STREAMER_TAG_MAP_ICON:ButcherIcon[2],
    STREAMER_TAG_OBJECT:ChickenObject,

    bool: DurringButcher
};
new PlayerChickenVars[MAX_PLAYERS][e_butcherdata];

new Float: ChickenSpawn[][] = {
    {1519.689331, 22.211219, 23.120628, 0.000000, -90.899986, 0.000000},
    {1513.779907, 22.211219, 23.027807, 0.000000, -90.899986, 0.000000},
    {1513.779907, 18.371221, 23.027807, 0.000000, -90.899986, 0.000000},
    {1511.610229, 16.041221, 22.993722, 0.000000, -90.899986, 0.000000},
    {1521.518676, 16.041221, 23.149374, 0.000000, -90.899986, 0.000000},
    {1519.129150, 11.281220, 23.111837, 0.000000, -90.899986, 0.000000},
    {1519.129150, 17.051219, 23.111837, 0.000000, -90.899986, 0.000000},
    {1515.619506, 15.101212, 23.056707, 0.000000, -90.899986, 0.000000},
    {1524.498291, 15.101212, 23.196182, 0.000000, -90.899986, 0.000000},
    {1524.498291, 19.031209, 23.196182, 0.000000, -90.899986, 0.000000},
    {1522.388427, 19.031209, 23.163045, 0.000000, -90.899986, 0.000000},
    {1522.388427, 21.921209, 23.163045, 0.000000, -90.899986, 0.000000},
    {1516.649047, 21.921209, 23.072885, 0.000000, -90.899986, 0.000000},
    {1517.449096, 11.501216, 23.085449, 0.000000, -90.899986, 0.000000}
};

LoadVarsButcher(playerid)
{
    UnloadVarsButcher(playerid);

    PlayerChickenVars[playerid][DurringButcher] = false;

    PlayerChickenVars[playerid][ButcherStartArea] = CreateDynamicSphere(1537.7798, 14.9313, 24.1406, 2.0, 0, 0, playerid);
    PlayerChickenVars[playerid][ButcherProcessArea][0] = CreateDynamicSphere(1925.6368, 135.9666, 37.3512, 2.0, 0, 0, playerid);
    PlayerChickenVars[playerid][ButcherProcessArea][1] = CreateDynamicSphere(1921.9147, 137.1642, 37.3512, 2.0, 0, 0, playerid);
    PlayerChickenVars[playerid][ButcherProcessArea][2] = CreateDynamicSphere(1917.5660, 138.5687, 37.3512, 2.0, 0, 0, playerid);
    PlayerChickenVars[playerid][ButcherProcessArea][3] = CreateDynamicSphere(1913.5212, 139.9623, 37.3512, 2.0, 0, 0, playerid);
    PlayerChickenVars[playerid][ButcherPackArea][0] = CreateDynamicSphere(1942.7374, 144.3086, 37.3512, 2.0, 0, 0, playerid);
    PlayerChickenVars[playerid][ButcherPackArea][1] = CreateDynamicSphere(1944.2256, 148.7797, 37.3512, 2.0, 0, 0, playerid);
    PlayerChickenVars[playerid][ButcherPackArea][2] = CreateDynamicSphere(1945.5770, 152.8428, 37.3512, 2.0, 0, 0, playerid); 
    PlayerChickenVars[playerid][ButcherPackArea][3] = CreateDynamicSphere(1951.6533, 150.8964, 37.3512, 2.0, 0, 0, playerid);
    PlayerChickenVars[playerid][ButcherPackArea][4] = CreateDynamicSphere(1950.1649, 146.4068, 37.3512, 2.0, 0, 0, playerid);
    PlayerChickenVars[playerid][ButcherPackArea][5] = CreateDynamicSphere(1948.6040, 141.7282, 37.3512, 2.0, 0, 0, playerid);     

    PlayerChickenVars[playerid][ButcherStartLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Mulai Pekerjaan", 0xFFFFFFFF, 1537.7798, 14.9313,  24.1406, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid, 10.0, -1, 0);
    PlayerChickenVars[playerid][ButcherProcessLabel][0] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Memotong Ayam", 0xFFFFFFFF, 1925.6368, 135.9666, 37.3512, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid, 10.0, -1, 0);
    PlayerChickenVars[playerid][ButcherProcessLabel][1] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Memotong Ayam", 0xFFFFFFFF, 1921.9147, 137.1642, 37.3512, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid, 10.0, -1, 0);
    PlayerChickenVars[playerid][ButcherProcessLabel][2] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Memotong Ayam", 0xFFFFFFFF, 1917.5660, 138.5687, 37.3512, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid, 10.0, -1, 0);
    PlayerChickenVars[playerid][ButcherProcessLabel][3] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Memotong Ayam", 0xFFFFFFFF, 1913.5212, 139.9623, 37.3512, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid, 10.0, -1, 0);
    PlayerChickenVars[playerid][ButcherPackLabel][0] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Kemas Ayam", 0xFFFFFFFF, 1942.7374, 144.3086, 37.3512, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid, 10.0, -1, 0);
    PlayerChickenVars[playerid][ButcherPackLabel][1] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Kemas Ayam", 0xFFFFFFFF, 1944.2256, 148.7797, 37.3512, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid, 10.0, -1, 0);
    PlayerChickenVars[playerid][ButcherPackLabel][2] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Kemas Ayam", 0xFFFFFFFF, 1945.5770, 152.8428, 37.3512, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid, 10.0, -1, 0);
    PlayerChickenVars[playerid][ButcherPackLabel][3] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Kemas Ayam", 0xFFFFFFFF, 1951.6533, 150.8964, 37.3512, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid, 10.0, -1, 0);
    PlayerChickenVars[playerid][ButcherPackLabel][4] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Kemas Ayam", 0xFFFFFFFF, 1950.1649, 146.4068, 37.3512, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid, 10.0, -1, 0);
    PlayerChickenVars[playerid][ButcherPackLabel][5] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Kemas Ayam", 0xFFFFFFFF, 1948.6040, 141.7282, 37.3512, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid, 10.0, -1, 0);
    
    PlayerChickenVars[playerid][ButcherIcon][0] = CreateDynamicMapIcon(1537.9041, 15.2733, 24.1406, 14, -1, 0, 0, playerid, 5000.0, MAPICON_GLOBAL, -1, 0);
    PlayerChickenVars[playerid][ButcherIcon][1] = CreateDynamicMapIcon(1910.7761, 162.6994, 37.1606, 14, -1, 0, 0, playerid, 5000.0, MAPICON_GLOBAL, -1, 0);
    return 1;
}

UnloadVarsButcher(playerid)
{
    if(DestroyDynamicArea(PlayerChickenVars[playerid][ButcherStartArea]))
        PlayerChickenVars[playerid][ButcherStartArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(PlayerChickenVars[playerid][ButcherStartLabel]))
        PlayerChickenVars[playerid][ButcherStartLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamicMapIcon(PlayerChickenVars[playerid][ButcherIcon][0]))
        PlayerChickenVars[playerid][ButcherIcon][0] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
    if(DestroyDynamicMapIcon(PlayerChickenVars[playerid][ButcherIcon][1]))
        PlayerChickenVars[playerid][ButcherIcon][1] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

    for(new x = 0; x < 4; x ++)
    {
        if(DestroyDynamicArea(PlayerChickenVars[playerid][ButcherProcessArea][x]))
            PlayerChickenVars[playerid][ButcherProcessArea][x] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(PlayerChickenVars[playerid][ButcherProcessLabel][x]))
            PlayerChickenVars[playerid][ButcherProcessLabel][x] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }

    for(new x = 0; x < 6; x ++) 
    {
        if(DestroyDynamicArea(PlayerChickenVars[playerid][ButcherPackArea][x]))
            PlayerChickenVars[playerid][ButcherPackArea][x] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(PlayerChickenVars[playerid][ButcherPackLabel][x]))
            PlayerChickenVars[playerid][ButcherPackLabel][x] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    pTimerTakeAyam[playerid] = -1;
    pTimerRobbank[playerid] = -1;
    pTimerButcher[playerid] = -1;
    pTimerPackChicken[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pTimerRobbank[playerid]);
    KillTimer(pTimerTakeAyam[playerid]);
    KillTimer(pTimerButcher[playerid]);
    KillTimer(pTimerPackChicken[playerid]);
    pTimerTakeAyam[playerid] = -1;
    pTimerRobbank[playerid] = -1;
    pTimerButcher[playerid] = -1;
    pTimerPackChicken[playerid] = -1;
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    if(AccountData[playerid][pJob] == JOB_BUTCHER && PlayerChickenVars[playerid][DurringButcher])
    {
        if(areaid == PlayerChickenVars[playerid][ButcherTakeChicken])
        {
            ShowKey(playerid, "[Y] Ambil Ayam");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    if(areaid == PlayerChickenVars[playerid][ButcherTakeChicken])
    {
        HideShortKey(playerid);
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_AYAM_START:
        {
            if(!response) return 1;
            if(AccountData[playerid][pJob] != JOB_BUTCHER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang tukang ayam!");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan, tidak dapat melakukan pekerjaan!");
            switch(listitem)
            {
                case 0: // mulai
                {
                    if(PlayerChickenVars[playerid][DurringButcher]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memulai pekerjaan ini!");
                    PlayerChickenVars[playerid][DurringButcher] = true;

                    if(DestroyDynamicObject(PlayerChickenVars[playerid][ChickenObject])) PlayerChickenVars[playerid][ChickenObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
                    if(DestroyDynamicArea(PlayerChickenVars[playerid][ButcherTakeChicken])) PlayerChickenVars[playerid][ButcherTakeChicken] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

                    new rand = random(sizeof(ChickenSpawn));
                    PlayerChickenVars[playerid][ChickenObject] = CreateDynamicObject(19078, ChickenSpawn[rand][0], ChickenSpawn[rand][1], ChickenSpawn[rand][2], ChickenSpawn[rand][3], ChickenSpawn[rand][4], ChickenSpawn[rand][5], 0, 0, playerid, 50.0);
                    PlayerChickenVars[playerid][ButcherTakeChicken] = CreateDynamicSphere(ChickenSpawn[rand][0], ChickenSpawn[rand][1], ChickenSpawn[rand][2], 2.0, 0, 0, playerid);
                    Info(playerid, "Anda sekarang telah "GREEN"Duty"WHITE" sebagai pemotong ayam");
                }
                case 1: //selesai
                {
                    if(!PlayerChickenVars[playerid][DurringButcher]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini sebelumnya!");
                    PlayerChickenVars[playerid][DurringButcher] = false;
                    if(DestroyDynamicObject(PlayerChickenVars[playerid][ChickenObject])) PlayerChickenVars[playerid][ChickenObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
                    if(DestroyDynamicArea(PlayerChickenVars[playerid][ButcherTakeChicken])) PlayerChickenVars[playerid][ButcherTakeChicken] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
                    Info(playerid, "Anda sekarang telah "RED"Off Duty"WHITE" sebagai pemotong ayam");
                }
            }
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pJob] == JOB_BUTCHER)
        {
            if(IsPlayerInDynamicArea(playerid, PlayerChickenVars[playerid][ButcherStartArea]))
            {
                ShowPlayerDialog(playerid, DIALOG_AYAM_START, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Tukang Ayam",
                "Mulai Pekerjaan\n"GRAY"Selesaikan Pekerjaan", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PlayerChickenVars[playerid][ButcherTakeChicken]) && PlayerChickenVars[playerid][DurringButcher])
            {
                if(!PlayerChickenVars[playerid][DurringButcher]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan!");
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

                // Tampilkan minigame dengan callback
                ShowMinigame(playerid, "OnMinigameComplete", "ChickenTakeMinigame"); 
                return 1;                
            }
            for(new x = 0; x < 4; x ++)
            {
                if(IsPlayerInDynamicArea(playerid, PlayerChickenVars[playerid][ButcherProcessArea][x]))
                {
                    if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                    if(!PlayerHasItem(playerid, "Ayam Hidup")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki ayam hidup!");
                    if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");

                    AccountData[playerid][ActivityTime] = 1;
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMOTONG AYAM");
                    ShowProgressBar(playerid);

                    ApplyAnimationEx(playerid, "KNIFE", "KILL_Knife_Player", 4.1, 1, 0, 0, 0, 0, 1);
                    SetPlayerAttachedObject(playerid, JOB_SLOT, 335, 6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
                    pTimerButcher[playerid] = SetTimerEx("ChickenProcessed", 1000, true, "dd", playerid, x);
                }
            }

            for(new x = 0; x < 6; x ++)
            {
                if(IsPlayerInDynamicArea(playerid, PlayerChickenVars[playerid][ButcherPackArea][x]))
                {
                    if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                    if(!PlayerHasItem(playerid, "Ayam Potong")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ayam potong tidak mencukupi! (Min: 5)");

                    AccountData[playerid][ActivityTime] = 1;
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "PACKING AYAM");
                    ShowProgressBar(playerid);

                    ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                    pTimerPackChicken[playerid] = SetTimerEx("ChickenPacking", 1000, true, "dd", playerid, x);
                }
            }
        }
    }
    return 1;
}

/* Other Functions */
forward ChickenPacking(playerid, x);
public ChickenPacking(playerid, x)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerPackChicken[playerid]);
        pTimerPackChicken[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerChickenVars[playerid][ButcherPackArea][x]))
    {
        KillTimer(pTimerPackChicken[playerid]);
        pTimerPackChicken[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerChickenVars[playerid][ButcherPackArea][x]))
    {
        KillTimer(pTimerPackChicken[playerid]);
        pTimerPackChicken[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!PlayerHasItem(playerid, "Ayam Potong"))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Ayam Potong tidak cukup! (Min: 1)");
        KillTimer(pTimerPackChicken[playerid]);
        pTimerPackChicken[playerid] = -1;
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
        KillTimer(pTimerPackChicken[playerid]);
        pTimerPackChicken[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(GetTotalWeightFloat(playerid) >= 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
        KillTimer(pTimerPackChicken[playerid]);
        pTimerPackChicken[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 12)
    {
        KillTimer(pTimerPackChicken[playerid]);
        pTimerPackChicken[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Ayam Potong", 1);
        Inventory_Add(playerid, "Ayam Kemas", 2768, 2);
        ShowItemBox(playerid, "Removed 1x", "Ayam Potong", 2804);
        ShowItemBox(playerid, "Received 2x", "Ayam Kemas", 2768);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/12;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward ChickenProcessed(playerid, x);
public ChickenProcessed(playerid, x)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerButcher[playerid]);
        pTimerButcher[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerChickenVars[playerid][ButcherProcessArea][x]))
    {
        KillTimer(pTimerButcher[playerid]);
        pTimerButcher[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerChickenVars[playerid][ButcherProcessArea][x]))
    {
        KillTimer(pTimerButcher[playerid]);
        pTimerButcher[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        return 0;
    }

    if(!PlayerHasItem(playerid, "Ayam Hidup"))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Ayam Hidup tidak cukup! (Min: 1)");
        KillTimer(pTimerButcher[playerid]);
        pTimerButcher[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        return 0;
    }

    if(GetTotalWeightFloat(playerid) >= 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
        KillTimer(pTimerButcher[playerid]);
        pTimerButcher[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pTimerButcher[playerid]);
        pTimerButcher[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, JOB_SLOT);

        Inventory_Remove(playerid, "Ayam Hidup");
        Inventory_Add(playerid, "Ayam Potong", 2804, 1);
        ShowItemBox(playerid, "Removed 1x", "Ayam Hidup", 16776);
        ShowItemBox(playerid, "Received 1x", "Ayam Potong", 2804);

        new rands = RandomEx(1, 51), randbulu = RandomEx(1, 3);
        switch(rands)
        {
            case 1..11:
            {
                Inventory_Add(playerid, "Bulu", 19517, randbulu);
                Info(playerid, "Anda mendapatkan "YELLOW"Bulu"WHITE" sebanyak "YELLOW"%dx", randbulu);
            }
            case 12..31:
            {
                Inventory_Add(playerid, "Bulu", 19517, 2);
                Info(playerid, "Anda mendapatkan "YELLOW"Bulu"WHITE" sebanyak "YELLOW"2x");
            }
            case 32..50:
            {
                Inventory_Add(playerid, "Bulu", 19517, randbulu);
                Info(playerid, "Anda mendapatkan "YELLOW"Bulu"WHITE" sebanyak "YELLOW"%dx", randbulu);
            }
        }
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

forward ChickenTake(playerid);
public ChickenTake(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerTakeAyam[playerid]);
        pTimerTakeAyam[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerChickenVars[playerid][ButcherTakeChicken]))
    {
        KillTimer(pTimerTakeAyam[playerid]);
        pTimerTakeAyam[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerChickenVars[playerid][ButcherTakeChicken]))
    {
        KillTimer(pTimerTakeAyam[playerid]);
        pTimerTakeAyam[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Ayam Hidup") >= 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Ayam hidup sudah mencapai batas maksimal (M: 50)!");
        KillTimer(pTimerTakeAyam[playerid]);
        pTimerTakeAyam[playerid] = -1;
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
        KillTimer(pTimerTakeAyam[playerid]);
        pTimerTakeAyam[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    }

    if(GetTotalWeightFloat(playerid) >= 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
        KillTimer(pTimerTakeAyam[playerid]);
        pTimerTakeAyam[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 10)
    {
        KillTimer(pTimerTakeAyam[playerid]);
        pTimerTakeAyam[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        if(DestroyDynamicObject(PlayerChickenVars[playerid][ChickenObject])) PlayerChickenVars[playerid][ChickenObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        if(DestroyDynamicArea(PlayerChickenVars[playerid][ButcherTakeChicken])) PlayerChickenVars[playerid][ButcherTakeChicken] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

        new rand = random(sizeof(ChickenSpawn));
        PlayerChickenVars[playerid][ChickenObject] = CreateDynamicObject(19078, ChickenSpawn[rand][0], ChickenSpawn[rand][1], ChickenSpawn[rand][2], ChickenSpawn[rand][3], ChickenSpawn[rand][4], ChickenSpawn[rand][5], 0, 0, playerid, 50.0);
        PlayerChickenVars[playerid][ButcherTakeChicken] = CreateDynamicSphere(ChickenSpawn[rand][0], ChickenSpawn[rand][1], ChickenSpawn[rand][2], 2.0, 0, 0, playerid);

        Inventory_Add(playerid, "Ayam Hidup", 16776);
        ShowItemBox(playerid, "Received 1x", "Ayam Hidup", 16776);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/10;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;   
}