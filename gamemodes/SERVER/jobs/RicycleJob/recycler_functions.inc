#include <YSI\y_hooks>

enum e_recyclerdata
{
    bool: DurringRecycler,
    STREAMER_TAG_AREA:RecyclerStartArea,
    STREAMER_TAG_AREA:RecyclerTakeArea,
    STREAMER_TAG_AREA:RecyclerSortirArea[4],
    STREAMER_TAG_AREA:RecyclerOlahArea[4],

    STREAMER_TAG_3D_TEXT_LABEL:RecyclerStartLabel,
    STREAMER_TAG_3D_TEXT_LABEL:RecyclerTakeLabel,
    STREAMER_TAG_3D_TEXT_LABEL:RecyclerSortirLabel[4],
    STREAMER_TAG_3D_TEXT_LABEL:RecyclerOlahLabel[4],

    STREAMER_TAG_OBJECT:RecyclerEngine[4],
    STREAMER_TAG_MAP_ICON:RecyclerIcon[2],
};
new PlayerRecyclerVars[MAX_PLAYERS][e_recyclerdata];

new pTimerRecycler[MAX_PLAYERS] = {-1, ...};
new STREAMER_TAG_OBJECT: BoxObject[MAX_PLAYERS];

static Float:TakePoint[][] = 
{
    {-1467.8176, 2632.4116, 28.9015},
    {-1484.6486, 2626.7683, 28.9015},
    {-1500.4303, 2631.4556, 28.9015},
    {-1496.0016, 2618.5842, 28.9015},
    {-1511.2738, 2613.9146, 28.9015},
    {-1506.2219, 2631.1919, 28.9015},
    {-1446.7095, 2623.4207, 28.9015},
    {-1435.1993, 2631.2083, 28.9015},
    {-1431.7559, 2613.8562, 28.9015},
    {-1420.8304, 2617.3191, 28.9015}
};

static Float:OlahPoint[][] =
{
    {26.6877, 1384.8459, 9.2719},
    {26.6871, 1372.1544, 9.2719},
    {26.6879, 1359.6985, 9.2719},
    {26.6856, 1345.7262, 9.2719}
};

LoadVarsDaur(playerid)
{
    UnloadVarsDaur(playerid);

    PlayerRecyclerVars[playerid][RecyclerStartArea] = CreateDynamicSphere(-1485.7316, 2594.8167, 28.9015, 2.0, 0, 6, playerid);
    PlayerRecyclerVars[playerid][RecyclerStartLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Mulai Recycler", -1, -1485.7316, 2594.8167, 28.9015, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 6, playerid);
    PlayerRecyclerVars[playerid][RecyclerIcon][0] = CreateDynamicMapIcon(2291.5, 2764.01, 10.8203, 24, -1, -1, -1, playerid, 9999.9, MAPICON_GLOBAL, -1, 1);
    PlayerRecyclerVars[playerid][RecyclerIcon][1] = CreateDynamicMapIcon(-6.6423, 1367.3634, 9.2719, 24, -1, -1, -1, playerid, 9999.9, MAPICON_GLOBAL, -1, 1);
    
    PlayerRecyclerVars[playerid][RecyclerEngine][0] = CreateDynamicObject(18763, 29.546903, 1384.940185, 15.201889, 0.000000, 0.000000, 0.000000, 0, 0, playerid, 400.00, 400.00); 
    SetDynamicObjectMaterial(PlayerRecyclerVars[playerid][RecyclerEngine][0], 0, 16640, "a51", "metpat64", 0x00000000);
    PlayerRecyclerVars[playerid][RecyclerEngine][1] = CreateDynamicObject(18763, 29.546903, 1372.059692, 15.201889, 0.000000, 0.000000, 0.000000, 0, 0, playerid, 400.00, 400.00); 
    SetDynamicObjectMaterial(PlayerRecyclerVars[playerid][RecyclerEngine][1], 0, 16640, "a51", "metpat64", 0x00000000);
    PlayerRecyclerVars[playerid][RecyclerEngine][2] = CreateDynamicObject(18763, 29.546903, 1359.649780, 15.201889, 0.000000, 0.000000, 0.000000, 0, 0, playerid, 400.00, 400.00); 
    SetDynamicObjectMaterial(PlayerRecyclerVars[playerid][RecyclerEngine][2], 0, 16640, "a51", "metpat64", 0x00000000);
    PlayerRecyclerVars[playerid][RecyclerEngine][3] = CreateDynamicObject(18763, 29.546903, 1345.639892, 15.201889, 0.000000, 0.000000, 0.000000, 0, 0, playerid, 400.00, 400.00); 
    SetDynamicObjectMaterial(PlayerRecyclerVars[playerid][RecyclerEngine][3], 0, 16640, "a51", "metpat64", 0x00000000);
    forex(i, 4)
    {
        PlayerRecyclerVars[playerid][RecyclerOlahArea][i] = CreateDynamicSphere(OlahPoint[i][0], OlahPoint[i][1], OlahPoint[i][2], 2.0, 0, 0, playerid);
        PlayerRecyclerVars[playerid][RecyclerOlahLabel][i] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Daur Ulang", -1, OlahPoint[i][0], OlahPoint[i][1], OlahPoint[i][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid);
    }
    return 1;
}

UnloadVarsDaur(playerid)
{
    if(DestroyDynamicArea(PlayerRecyclerVars[playerid][RecyclerStartArea]))
        PlayerRecyclerVars[playerid][RecyclerStartArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    if(DestroyDynamic3DTextLabel(PlayerRecyclerVars[playerid][RecyclerStartLabel]))
        PlayerRecyclerVars[playerid][RecyclerStartLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    if(DestroyDynamicMapIcon(PlayerRecyclerVars[playerid][RecyclerIcon][0]))
        PlayerRecyclerVars[playerid][RecyclerIcon][0] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
    if(DestroyDynamicMapIcon(PlayerRecyclerVars[playerid][RecyclerIcon][1]))
        PlayerRecyclerVars[playerid][RecyclerIcon][1] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
    
    for(new i; i < 4; i ++)
    {
        if(DestroyDynamicArea(PlayerRecyclerVars[playerid][RecyclerOlahArea][i]))
            PlayerRecyclerVars[playerid][RecyclerOlahArea][i] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(PlayerRecyclerVars[playerid][RecyclerOlahLabel][i]))
            PlayerRecyclerVars[playerid][RecyclerOlahLabel][i] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        
        if(DestroyDynamicObject(PlayerRecyclerVars[playerid][RecyclerEngine][i]))
            PlayerRecyclerVars[playerid][RecyclerEngine][i] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
    }
    return 1;
}

/* Hook System */
hook OnPlayerDisconnect(playerid, reason)
{
    if(PlayerRecyclerVars[playerid][DurringRecycler])
    {
        for(new i; i < 4; i++)
        {
            if(DestroyDynamic3DTextLabel(PlayerRecyclerVars[playerid][RecyclerSortirLabel][i])) PlayerRecyclerVars[playerid][RecyclerSortirLabel][i] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        }
        if(DestroyDynamic3DTextLabel(PlayerRecyclerVars[playerid][RecyclerTakeLabel])) PlayerRecyclerVars[playerid][RecyclerTakeLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        if(DestroyDynamicArea(PlayerRecyclerVars[playerid][RecyclerTakeArea])) PlayerRecyclerVars[playerid][RecyclerTakeArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;        
        if(DestroyDynamicArea(PlayerRecyclerVars[playerid][RecyclerSortirArea])) PlayerRecyclerVars[playerid][RecyclerSortirArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
    }
    KillTimer(pTimerRecycler[playerid]);
    pTimerRecycler[playerid] = -1;
    PlayerRecyclerVars[playerid][DurringRecycler] = false;
    DeletePVar(playerid, "DurringDaur");
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pJob] == JOB_RECYCLER)
        {
            if(IsPlayerInDynamicArea(playerid, PlayerRecyclerVars[playerid][RecyclerStartArea]))
            {
                if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");

                ShowPlayerDialog(playerid, DIALOG_RECYCLER_START, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Recycler Job", 
                "Mulai Pekerjaan\n"GRAY"Selesaikan Pekerjaan", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PlayerRecyclerVars[playerid][RecyclerTakeArea]) && PlayerRecyclerVars[playerid][DurringRecycler])
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

                AccountData[playerid][ActivityTime] = 1;
                pTimerRecycler[playerid] = SetTimerEx("TakeRecycler", 1000, true, "d", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL");
                ShowProgressBar(playerid);
                ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            }

            for(new x = 0; x < 4; x++)
            {
                if(IsPlayerInDynamicArea(playerid, PlayerRecyclerVars[playerid][RecyclerSortirArea][x]) && PlayerRecyclerVars[playerid][DurringRecycler])
                {
                    if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

                    AccountData[playerid][ActivityTime] = 1;
                    pTimerRecycler[playerid] = SetTimerEx("SortirRecycler", 1000, true, "dd", playerid, x);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENYORTIR");
                    ShowProgressBar(playerid);
                    ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                    RemovePlayerAttachedObject(playerid, 9);
                    
                    if(x == 0)
                    {
                        BoxObject[playerid] = CreateDynamicObject(1271, -1446.673217, 2583.610107, 29.541492, -9.999999, 0.000000, 0.000000, -1, -1, -1, 400.00, 400.00); 
                        MoveDynamicObject(BoxObject[playerid], -1446.673217, 2571.979980, 31.661521, 1.0 -9.999999, 0.000007, 0.000001);
                        Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
                    }
                    if(x == 1)
                    {
                        BoxObject[playerid] = CreateDynamicObject(1271, -1460.103637, 2583.610107, 29.541492, -9.999999, 0.000000, 0.000000, -1, -1, -1, 400.00, 400.00); 
                        MoveDynamicObject(BoxObject[playerid], -1460.103637, 2571.979980, 31.661521, 1.0 -9.999999, 0.000007, 0.000001);
                        Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
                    }
                    if(x == 2)
                    {
                        BoxObject[playerid] = CreateDynamicObject(1271, -1470.734252, 2583.610107, 29.541492, -9.999999, 0.000000, 0.000000, -1, -1, -1, 400.00, 400.00); 
                        MoveDynamicObject(BoxObject[playerid], -1470.734252, 2571.979980, 31.661521, 1.0, -9.999999, 0.000000, 0.000000);
                        Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
                    }
                    if(x == 3)
                    {
                        BoxObject[playerid] = CreateDynamicObject(1271, -1484.035034, 2583.610107, 29.541492, -9.999999, 0.000000, 0.000000, -1, -1, -1, 400.00, 400.00); 
                        MoveDynamicObject(BoxObject[playerid], -1484.035034, 2571.979980, 31.661521, 1.0, -9.999999, 0.000000, 0.000000);
                        Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
                    }
                }

                if(IsPlayerInDynamicArea(playerid, PlayerRecyclerVars[playerid][RecyclerOlahArea][x]))
                {
                    if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                    if(Inventory_Count(playerid, "Boxmats") < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Boxmats tidak mencukupi! (Min 5)");

                    AccountData[playerid][ActivityTime] = 1;
                    pTimerRecycler[playerid] = SetTimerEx("RecyclerOlah", 1000, true, "dd", playerid, x);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "DAUR ULANG");
                    ShowProgressBar(playerid);
                    ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                
                    if(x == 0)
                    {
                        MoveDynamicObject(PlayerRecyclerVars[playerid][RecyclerEngine][0], 29.546903, 1384.940185, 15.201889 - 4.0, 1.0, 0.000000, 0.000000, 0.000000);
                        SetTimerEx("EngineOneUP", 5500, false, "d", playerid);
                    }
                    if(x == 1)
                    {
                        MoveDynamicObject(PlayerRecyclerVars[playerid][RecyclerEngine][1], 29.546903, 1372.059692, 15.201889 - 4.0, 1.0, 0.000000, 0.000000, 0.000000);
                        SetTimerEx("EngineTwoUP", 5500, false, "d", playerid);
                    }
                    if(x == 2)
                    {
                        MoveDynamicObject(PlayerRecyclerVars[playerid][RecyclerEngine][2], 29.546903, 1359.649780, 15.201889 - 4.0, 1.0, 0.000000, 0.000000, 0.000000);
                        SetTimerEx("EngineThreeUP", 5500, false, "d", playerid);
                    }
                    if(x == 3)
                    {
                        MoveDynamicObject(PlayerRecyclerVars[playerid][RecyclerEngine][3], 29.546903, 1345.639892, 15.201889 - 4.0, 1.0, 0.000000, 0.000000, 0.000000);
                        SetTimerEx("EngineFourUP", 5500, false, "d", playerid);
                    }
                }
            }
        }
    }
    return 1;
}

CancelRecycler(playerid)
{
    if(DestroyDynamic3DTextLabel(PlayerRecyclerVars[playerid][RecyclerTakeLabel])) 
        PlayerRecyclerVars[playerid][RecyclerTakeLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    
    for(new i; i < 4; i++)
    {
        if(DestroyDynamic3DTextLabel(PlayerRecyclerVars[playerid][RecyclerSortirLabel][i])) 
            PlayerRecyclerVars[playerid][RecyclerSortirLabel][i] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }
    
    if(DestroyDynamicArea(PlayerRecyclerVars[playerid][RecyclerTakeArea])) 
        PlayerRecyclerVars[playerid][RecyclerTakeArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
    
    if(DestroyDynamicArea(PlayerRecyclerVars[playerid][RecyclerSortirArea])) 
        PlayerRecyclerVars[playerid][RecyclerSortirArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

    PlayerRecyclerVars[playerid][DurringRecycler] = false;
    DeletePVar(playerid, "DurringDaur");
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_RECYCLER_START:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pJob] != JOB_RECYCLER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang pekerja Recycler!");
            switch(listitem)
            {
                case 0: //mulai
                {
                    if(PlayerRecyclerVars[playerid][DurringRecycler]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memulai pekerjaan ini!");
                    new rand = Random(sizeof(TakePoint));

                    PlayerRecyclerVars[playerid][RecyclerTakeArea] = CreateDynamicSphere(TakePoint[rand][0], TakePoint[rand][1], TakePoint[rand][2], 2.0, 0, 6, playerid);
                    PlayerRecyclerVars[playerid][RecyclerTakeLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Mengambil", -1, TakePoint[rand][0], TakePoint[rand][1], TakePoint[rand][2], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 6, playerid);
                    PlayerRecyclerVars[playerid][DurringRecycler] = true;

                    SetPVarInt(playerid, "DurringDaur", 1);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil memulai pekerjaan");
                }
                case 1: //selesai
                {
                    if(!PlayerRecyclerVars[playerid][DurringRecycler]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
                    CancelRecycler(playerid);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menyelesaikan pekerjaan!");
                }
            }
        }
    }
    return 1;
}

/* Other Functions */
forward TakeRecycler(playerid);
public TakeRecycler(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerRecyclerVars[playerid][RecyclerTakeArea]))
    {
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }
    
    if(!IsPlayerInDynamicArea(playerid, PlayerRecyclerVars[playerid][RecyclerTakeArea]))
    {
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
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
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 8)
    {
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerAttachedObject(playerid, 9, 2912, 1, 0.181, 0.253, -0.067, -82.3, 1.0, 6.0, 0.51, 0.575, 0.483);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
        if(DestroyDynamicArea(PlayerRecyclerVars[playerid][RecyclerTakeArea])) PlayerRecyclerVars[playerid][RecyclerTakeArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        if(DestroyDynamic3DTextLabel(PlayerRecyclerVars[playerid][RecyclerTakeLabel])) PlayerRecyclerVars[playerid][RecyclerTakeLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        new rand = RandomEx(1, 41);
        switch(rand)
        {
            case 1..9:
            {
                PlayerRecyclerVars[playerid][RecyclerSortirArea][0] = CreateDynamicSphere(-1447.6829, 2583.7949, 28.9015, 2.0, 0, 6, playerid);
                PlayerRecyclerVars[playerid][RecyclerSortirLabel][0] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Sortir", -1, -1447.6829, 2583.7949, 28.9015, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 6, playerid);
            }
            case 10..19:
            {
                PlayerRecyclerVars[playerid][RecyclerSortirArea][1] = CreateDynamicSphere(-1461.1429, 2583.5684, 28.9015, 2.0, 0, 6, playerid);
                PlayerRecyclerVars[playerid][RecyclerSortirLabel][1] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Sortir", -1, -1461.1429, 2583.5684, 28.9015, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 6, playerid);
            }
            case 20..29:
            {
                PlayerRecyclerVars[playerid][RecyclerSortirArea][2] = CreateDynamicSphere(-1472.1234, 2583.6997, 28.9015, 2.0, 0, 6, playerid);
                PlayerRecyclerVars[playerid][RecyclerSortirLabel][2] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Sortir", -1, -1472.1234, 2583.6997, 28.9015, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 6, playerid);
            }
            case 30..40:
            {
                PlayerRecyclerVars[playerid][RecyclerSortirArea][3] = CreateDynamicSphere(-1485.2805, 2583.6887, 28.9015, 2.0, 0, 6, playerid);
                PlayerRecyclerVars[playerid][RecyclerSortirLabel][3] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Sortir", -1, -1485.2805, 2583.6887, 28.9015, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 6, playerid);
            }
        }
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/8;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward SortirRecycler(playerid, t);
public SortirRecycler(playerid, t)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerRecyclerVars[playerid][RecyclerSortirArea][t]))
    {
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerRecyclerVars[playerid][RecyclerSortirArea][t]))
    {
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
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
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        RemovePlayerAttachedObject(playerid, 9);
        
        if(DestroyDynamicArea(PlayerRecyclerVars[playerid][RecyclerSortirArea][t])) PlayerRecyclerVars[playerid][RecyclerSortirArea][t] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        if(DestroyDynamic3DTextLabel(PlayerRecyclerVars[playerid][RecyclerSortirLabel][t])) PlayerRecyclerVars[playerid][RecyclerSortirLabel][t] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        if(DestroyDynamicObject(BoxObject[playerid])) BoxObject[playerid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        new rands = RandomEx(1, 51), randbox = RandomEx(2, 3);
        switch(rands)
        {
            case 1..21:
            {
                Inventory_Add(playerid, "Boxmats", 2912, randbox);
                ShowItemBox(playerid, sprintf("Received %dx", randbox), "Boxmats", 2912);
            }
            case 22..51:
            {
                Inventory_Add(playerid, "Boxmats", 2912, randbox);
                ShowItemBox(playerid, sprintf("Received %dx", randbox), "Boxmats", 2912);
            }
        }
        GivePlayerXP(playerid, DEFAULT_XP);
        new randtakes = Random(sizeof(TakePoint));
        PlayerRecyclerVars[playerid][RecyclerTakeArea] = CreateDynamicSphere(TakePoint[randtakes][0], TakePoint[randtakes][1], TakePoint[randtakes][2], 2.0, 0, 6, playerid);
        PlayerRecyclerVars[playerid][RecyclerTakeLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Mengambil", -1, TakePoint[randtakes][0], TakePoint[randtakes][1], TakePoint[randtakes][2], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 6, playerid);
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/15;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]); 
        return 0;
    }
    return 1;
}

forward RecyclerOlah(playerid, t);
public RecyclerOlah(playerid, t)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerRecyclerVars[playerid][RecyclerOlahArea][t]))
    {
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerRecyclerVars[playerid][RecyclerOlahArea][t]))
    {
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
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
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
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
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pTimerRecycler[playerid]);
        pTimerRecycler[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        new rands = RandomEx(1, 90);
        new randbaja = RandomEx(2, 3), randkaret = RandomEx(4, 15), 
        randplastik = RandomEx(4, 5), randkaca = RandomEx(2, 3),   
        randalumu = RandomEx(2, 3), randplatbesi = RandomEx(1, 3);
        switch(rands)
        {
            case 1..11:
            {
                Inventory_Remove(playerid, "Boxmats", 5);
                Inventory_Add(playerid, "Baja", 19772, randbaja);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Received %dx", randbaja), "Baja", 19772);
                ShowItemBox(playerid, sprintf("Received %dx", randplatbesi), "Plat Besi", 3117);
            }
            case 12..35:
            {
                Inventory_Remove(playerid, "Boxmats", 5);
                Inventory_Add(playerid, "Plastik", 1264, randplastik);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Received %dx", randplastik), "Plastik", 1264);
                ShowItemBox(playerid, sprintf("Received %dx", randplatbesi), "Plat Besi", 3117);
            }
            case 36..56:
            {
                Inventory_Remove(playerid, "Boxmats", 5);
                Inventory_Add(playerid, "Karet", 1316, randkaret);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Received %dx", randkaret), "Karet", 1316);
                ShowItemBox(playerid, sprintf("Received %dx", randplatbesi), "Plat Besi", 3117);
            }
            case 57..71:
            {
                Inventory_Remove(playerid, "Boxmats", 5);
                Inventory_Add(playerid, "Alumunium", 2937, randalumu);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Received %dx", randalumu), "Alumunium", 2937);
                ShowItemBox(playerid, sprintf("Received %dx", randplatbesi), "Plat Besi", 3117);
            }
            case 72..89:
            {
                Inventory_Remove(playerid, "Boxmats", 5);
                Inventory_Add(playerid, "Kaca", 1649, randkaca);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Received %dx", randkaca), "Kaca", 1649);
                ShowItemBox(playerid, sprintf("Received %dx", randplatbesi), "Plat Besi", 3117);
            }
        }
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/15;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]); 
        return 0;
    }
    return 1;
}

FUNC::EngineOneUP(playerid)
{
    PlayerPlaySound(playerid, 1009, 0.0, 0.0, 0.0);
    MoveDynamicObject(PlayerRecyclerVars[playerid][RecyclerEngine][0], 29.546903, 1384.940185, 15.201889, 0.5, 0.000000, 0.000000, 0.000000);
}

FUNC::EngineTwoUP(playerid)
{
    PlayerPlaySound(playerid, 1009, 0.0, 0.0, 0.0);
    MoveDynamicObject(PlayerRecyclerVars[playerid][RecyclerEngine][1], 29.546903, 1372.059692, 15.201889, 0.5, 0.000000, 0.000000, 0.000000);
}

FUNC::EngineThreeUP(playerid)
{
    PlayerPlaySound(playerid, 1009, 0.0, 0.0, 0.0);
    MoveDynamicObject(PlayerRecyclerVars[playerid][RecyclerEngine][2], 29.546903, 1359.649780, 15.201889, 0.5, 0.000000, 0.000000, 0.000000);
}

FUNC::EngineFourUP(playerid)
{
    PlayerPlaySound(playerid, 1009, 0.0, 0.0, 0.0);
    MoveDynamicObject(PlayerRecyclerVars[playerid][RecyclerEngine][3], 29.546903, 1345.639892, 15.201889, 0.5, 0.000000, 0.000000, 0.000000);
}