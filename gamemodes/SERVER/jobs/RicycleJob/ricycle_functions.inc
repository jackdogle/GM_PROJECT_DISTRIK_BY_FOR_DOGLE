#include <YSI\y_hooks>

new pTimerTakeDaur[MAX_PLAYERS] = {-1, ...},
    pTimerSortir[MAX_PLAYERS] = {-1, ...},
    pTimerDaurUlang[MAX_PLAYERS] = {-1, ...};

enum STUFFDAUR {
    STREAMER_TAG_AREA:DaurStartArea,
    STREAMER_TAG_3D_TEXT_LABEL:DaurLabelStart,

    STREAMER_TAG_AREA:DaurLabelArea,
    STREAMER_TAG_3D_TEXT_LABEL:DaurLabel,

    STREAMER_TAG_AREA:SortirLabelArea[4],
    STREAMER_TAG_3D_TEXT_LABEL:SortirLabel[4],

    STREAMER_TAG_MAP_ICON:DaurIcon,

    STREAMER_TAG_AREA:DaurArea[4],
    STREAMER_TAG_3D_TEXT_LABEL:DaurUlangLabel[4],
    STREAMER_TAG_OBJECT:DaurObject[4],
    STREAMER_TAG_OBJECT:MesinDaurObject[4],

    bool: DurringDaur,
    STREAMER_TAG_OBJECT:BoxObject[4],
};
new PlayerDaurVars[MAX_PLAYERS][STUFFDAUR];


stock LoadVarsDaur(playerid)
{
    UnloadVarsDaur(playerid);

    PlayerDaurVars[playerid][DaurStartArea] = CreateDynamicSphere(2281.3833, 2723.7085, -46.5938, 2.0, -1, -1, playerid); 
    PlayerDaurVars[playerid][DaurLabelStart] =  CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Mulai Pekerjaan", -1, 2281.3833, 2723.7085, -46.5938 + 0.3, 8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);
    PlayerDaurVars[playerid][DaurIcon] = CreateDynamicMapIcon(2291.5, 2764.01, 10.8203, 24, -1, -1, -1, playerid, 9999.9, MAPICON_GLOBAL, -1, 1);

    PlayerDaurVars[playerid][DaurArea][0] = CreateDynamicSphere(22.1153, 1384.9559, 9.1719, 2.0, -1, -1);
    PlayerDaurVars[playerid][DaurArea][1] = CreateDynamicSphere(23.8160, 1372.4774, 9.1719, 2.0, -1, -1);
    PlayerDaurVars[playerid][DaurArea][2] = CreateDynamicSphere(25.3356, 1359.3785, 9.1719, 2.0, -1, -1);
    PlayerDaurVars[playerid][DaurArea][3] = CreateDynamicSphere(27.2861, 1349.4387, 9.1719, 2.0, -1, -1);
    PlayerDaurVars[playerid][DaurUlangLabel][0] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Daur Ulang", -1, 22.1153, 1384.9559, 9.1719, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);
    PlayerDaurVars[playerid][DaurUlangLabel][1] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Daur Ulang", -1, 23.8160, 1372.4774, 9.1719, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);
    PlayerDaurVars[playerid][DaurUlangLabel][2] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Daur Ulang", -1, 25.3356, 1359.3785, 9.1719, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);
    PlayerDaurVars[playerid][DaurUlangLabel][3] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Daur Ulang", -1, 27.2861, 1349.4387, 9.1719, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);

    PlayerDaurVars[playerid][MesinDaurObject][0] = CreateDynamicObject(18763, 26.089714, 1385.557739, 15.381930, 0.000000, 0.000000, 7.799995, 0, 0, playerid, 300.00, 300.00); 
    SetDynamicObjectMaterial(PlayerDaurVars[playerid][MesinDaurObject][0], 0, 13659, "8bars", "bridgeconc", 0x00000000);
    PlayerDaurVars[playerid][MesinDaurObject][1] = CreateDynamicObject(18763, 27.777893, 1372.957519, 14.891917, 0.000001, 0.000014, 7.799994, 0, 0, playerid, 300.00, 300.00); 
    SetDynamicObjectMaterial(PlayerDaurVars[playerid][MesinDaurObject][1], 0, 13659, "8bars", "bridgeconc", 0x00000000);
    PlayerDaurVars[playerid][MesinDaurObject][2] = CreateDynamicObject(18763, 29.467884, 1359.775756, 14.891917, 0.000003, 0.000029, 7.799994, 0, 0, playerid, 300.00, 300.00); 
    SetDynamicObjectMaterial(PlayerDaurVars[playerid][MesinDaurObject][2], 0, 13659, "8bars", "bridgeconc", 0x00000000);
    PlayerDaurVars[playerid][MesinDaurObject][3] = CreateDynamicObject(18763, 30.807901, 1349.954101, 14.891917, 0.000004, 0.000037, 7.799994, 0, 0, playerid, 300.00, 300.00); 
    SetDynamicObjectMaterial(PlayerDaurVars[playerid][MesinDaurObject][3], 0, 13659, "8bars", "bridgeconc", 0x00000000);
}

stock UnloadVarsDaur(playerid)
{
    if(IsValidDynamicArea(PlayerDaurVars[playerid][DaurStartArea]))
        DestroyDynamicArea(PlayerDaurVars[playerid][DaurStartArea]);

    if(IsValidDynamic3DTextLabel(PlayerDaurVars[playerid][DaurLabelStart]))
        DestroyDynamic3DTextLabel(PlayerDaurVars[playerid][DaurLabelStart]);

    if(IsValidDynamicMapIcon(PlayerDaurVars[playerid][DaurIcon]))
        DestroyDynamicMapIcon(PlayerDaurVars[playerid][DaurIcon]);

    for(new i = 0; i < 4; i ++)
    {
        if(IsValidDynamicArea(PlayerDaurVars[playerid][DaurArea][i]))   
            DestroyDynamicArea(PlayerDaurVars[playerid][DaurArea][i]);

        if(IsValidDynamic3DTextLabel(PlayerDaurVars[playerid][DaurUlangLabel][i]))  
            DestroyDynamic3DTextLabel(PlayerDaurVars[playerid][DaurUlangLabel][i]);
    }
}

new Float: TakeRandom[][5] = 
{
    {2291.9810, 2753.2588, -46.3937},
    {2283.5994, 2744.1582, -46.5938},
    {2303.9465, 2739.6467, -46.5938},
    {2309.5784, 2748.7966, -46.5938},
    {2310.8992, 2739.5969, -46.5938}
};
Dialog:DialogStartRecycler(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
    if(GetPlayerJob(playerid) != JOB_RECYCLER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang pekerja Recycler!");
    switch(listitem)
    {
        case 0:// 
        {
            new rand = Random(sizeof(TakeRandom));
            if(PlayerDaurVars[playerid][DurringDaur]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memulai pekerjaan!");    
            PlayerDaurVars[playerid][DurringDaur] = true;
            PlayerDaurVars[playerid][DaurLabelArea] = CreateDynamicSphere(TakeRandom[rand][0], TakeRandom[rand][1], TakeRandom[rand][2], 2.0, -1, -1, playerid);
            PlayerDaurVars[playerid][DaurLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Mengambil", -1, TakeRandom[rand][0], TakeRandom[rand][1], TakeRandom[rand][2] + 0.3, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil memulai pekerjaan!");
        }
        case 1:// 
        {
            if(!PlayerDaurVars[playerid][DurringDaur]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(IsValidDynamic3DTextLabel(PlayerDaurVars[playerid][DaurLabel])) DestroyDynamic3DTextLabel(PlayerDaurVars[playerid][DaurLabel]);
            if(IsValidDynamicArea(PlayerDaurVars[playerid][DaurArea])) DestroyDynamicArea(PlayerDaurVars[playerid][DaurArea]);
            PlayerDaurVars[playerid][DurringDaur] = false;
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menyelesaikan pekerjaan!");
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pJob] == JOB_RECYCLER)
        {
            if(IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][DaurStartArea]))
            {
                if(AccountData[playerid][pInjured]) return 0;
                if(GetPlayerJob(playerid) == JOB_RECYCLER)
                {
                    Dialog_Show(playerid, DialogStartRecycler, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Recycler Job", ""VERONA_ARWIN"Mulai Pekerjaan\n"WHITE"Selesaikan Pekerjaan\n", "Pilih", "Batal");
                }
            }

            if(IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][DaurLabelArea]))
            {
                if(!PlayerDaurVars[playerid][DurringDaur]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");          
                AccountData[playerid][ActivityTime] = 1;
                pTimerTakeDaur[playerid] = SetTimerEx("TakeDaur", 1000, true, "d", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            }

            if(IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][SortirLabelArea][0]))
            {
                if(!PlayerDaurVars[playerid][DurringDaur]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                AccountData[playerid][ActivityTime] = 1;
                pTimerSortir[playerid] = SetTimerEx("Sortir1", 1000, true, "d", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENYORTIR");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                RemovePlayerAttachedObject(playerid, 9);
                PlayerDaurVars[playerid][BoxObject][0] = CreateDynamicObject(2912, 2309.481201, 2703.322753, -46.166324, -9.600004, 0.000000, -2.100000, -1, -1, playerid, 300.00, 300.00);
                MoveDynamicObject(PlayerDaurVars[playerid][BoxObject][0], 2309.481201, 2687.236816, -43.626422, 2.0, -9.600003, 0.000007, -2.099998);
            }

            if(IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][SortirLabelArea][1]))
            {
                if(!PlayerDaurVars[playerid][DurringDaur]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                AccountData[playerid][ActivityTime] = 1;
                pTimerSortir[playerid] = SetTimerEx("Sortir2", 1000, true, "d", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENYORTIR");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                RemovePlayerAttachedObject(playerid, 9);
                PlayerDaurVars[playerid][BoxObject][1] = CreateDynamicObject(2912, 2301.510498, 2703.502685, -46.248729, -10.400002, 0.000000, -2.100000, -1, -1, playerid, 300.00, 300.00);
                MoveDynamicObject(PlayerDaurVars[playerid][BoxObject][1], 2301.510498, 2687.416748, -43.708827, 2.0, -10.400002, 0.000007, -2.099998);
            }

            if(IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][SortirLabelArea][2]))
            {
                if(!PlayerDaurVars[playerid][DurringDaur]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                AccountData[playerid][ActivityTime] = 1;
                pTimerSortir[playerid] = SetTimerEx("Sortir3", 1000, true, "d", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENYORTIR");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                RemovePlayerAttachedObject(playerid, 9);
                PlayerDaurVars[playerid][BoxObject][2] = CreateDynamicObject(2912, 2291.950439, 2703.414550, -46.170658, -11.800001, 0.000000, -2.100000, -1, -1, playerid, 300.00, 300.00);
                MoveDynamicObject(PlayerDaurVars[playerid][BoxObject][2], 2291.950439, 2687.328613, -43.630756, 2.0, -11.800000, 0.000007, -2.099998);
            }

            if(IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][SortirLabelArea][3]))
            {
                if(!PlayerDaurVars[playerid][DurringDaur]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                AccountData[playerid][ActivityTime] = 1;
                pTimerSortir[playerid] = SetTimerEx("Sortir4", 1000, true, "d", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENYORTIR");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                RemovePlayerAttachedObject(playerid, 9);
                PlayerDaurVars[playerid][BoxObject][3] = CreateDynamicObject(2912, 2282.411376, 2703.444335, -46.187747, -12.000002, 0.000000, -1.800000, -1, -1, playerid, 300.00, 300.00); 
                MoveDynamicObject(PlayerDaurVars[playerid][BoxObject][3], 2282.411376, 2687.358398, -43.647846, 2.0, -12.000002, 0.000007, -1.799999);
            }

            if(IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][DaurArea][0]))
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                if(GetPlayerJob(playerid) != JOB_RECYCLER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Recycler Job!");
                if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                if(Inventory_Count(playerid, "Boxmats") < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Boxmats tidak cukup! (Min: 10)");

                AccountData[playerid][ActivityTime] = 1;
                pTimerDaurUlang[playerid] = SetTimerEx("DaurUlang1", 1000, true, "i", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "DAUR ULANG");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);

                PlayerDaurVars[playerid][DaurObject][0] = CreateDynamicObject(19772, 25.511131, 1385.435302, 9.711877, 0.000000, 0.000000, 8.500000, 0, 0, playerid, 300.00, 300.00); 
                SetTimerEx("MoveMesin1", 1500, false, "d", playerid);
            }

            if(IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][DaurArea][1]))
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                if(GetPlayerJob(playerid) != JOB_RECYCLER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Recycler Job!");
                if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                if(Inventory_Count(playerid, "Boxmats") < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Boxmats tidak cukup! (Min: 10)");

                AccountData[playerid][ActivityTime] = 1;
                pTimerDaurUlang[playerid] = SetTimerEx("DaurUlang2", 1000, true, "i", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "DAUR ULANG");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);

                PlayerDaurVars[playerid][DaurObject][1] = CreateDynamicObject(19772, 27.376514, 1372.955932, 9.711877, 0.000000, 0.000000, 7.699999, 0, 0, playerid, 300.00, 300.00); 
                SetTimerEx("MoveMesin2", 1500, false, "d", playerid);
            }

            if(IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][DaurArea][2]))
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                if(GetPlayerJob(playerid) != JOB_RECYCLER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Recycler Job!");
                if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                if(Inventory_Count(playerid, "Boxmats") < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Boxmats tidak cukup! (Min: 10)");

                AccountData[playerid][ActivityTime] = 1;
                pTimerDaurUlang[playerid] = SetTimerEx("DaurUlang3", 1000, true, "i", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "DAUR ULANG");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);

                PlayerDaurVars[playerid][DaurObject][2] = CreateDynamicObject(19772, 29.171897, 1359.677612, 9.711877, 0.000000, 0.000000, 7.699999, 0, 0, playerid, 300.00, 300.00); 
                SetTimerEx("MoveMesin3", 1500, false, "d", playerid);
            }

            if(IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][DaurArea][3]))
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                if(GetPlayerJob(playerid) != JOB_RECYCLER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Recycler Job!");
                if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                if(Inventory_Count(playerid, "Boxmats") < 10) return ShowTDN(playerid, NOTIFICATION_ERROR, "Boxmats tidak cukup! (Min: 10)");

                AccountData[playerid][ActivityTime] = 1;
                pTimerDaurUlang[playerid] = SetTimerEx("DaurUlang4", 1000, true, "i", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "DAUR ULANG");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);

                PlayerDaurVars[playerid][DaurObject][3] = CreateDynamicObject(19772, 30.505033, 1349.817382, 9.711877, 0.000000, 0.000000, 7.699999, 0, 0, playerid, 300.00, 300.00); 
                SetTimerEx("MoveMesin4", 1500, false, "d", playerid);
            }
        }
    }
    return 1;
}

VRRP::MoveMesin1(playerid)
{
    MoveDynamicObject(PlayerDaurVars[playerid][MesinDaurObject][0], 26.089714, 1385.557739, 11.981889 - 0.5, 1.5, 0.000001, 0.000007, 7.799995);
    PlayerPlaySound(playerid, 1035, 0, 0, 0);
    SetTimerEx("MoveMesin1UP", 5500, false, "i", playerid);
}
VRRP::MoveMesin1UP(playerid)
{
    PlayerPlaySound(playerid, 1009, 0, 0, 0);
    MoveDynamicObject(PlayerDaurVars[playerid][DaurObject][0], 25.511131, 1385.435302, 9.711877 - 1.0, 3.0, 0.000000, 0.000000, 8.500000);
    MoveDynamicObject(PlayerDaurVars[playerid][MesinDaurObject][0], 26.089714, 1385.557739, 15.381930, 0.55, 0.000000, 0.000000, 7.799995); 
}

VRRP::MoveMesin2(playerid)
{
    MoveDynamicObject(PlayerDaurVars[playerid][MesinDaurObject][1], 27.777893, 1372.957519, 11.491876 - 0.1, 1.5, 0.000003, 0.000022, 7.799992);
    SetTimerEx("MoveMesin2UP", 5500, false, "i", playerid);
}
VRRP::MoveMesin2UP(playerid)
{
    PlayerPlaySound(playerid, 1009, 0, 0, 0);
    MoveDynamicObject(PlayerDaurVars[playerid][DaurObject][1], 27.376514, 1372.955932, 9.711877 - 1.0, 3.0, 0.000000, 0.000000, 7.699999);
    MoveDynamicObject(PlayerDaurVars[playerid][MesinDaurObject][1], 27.777893, 1372.957519, 14.891917, 0.60, 0.000001, 0.000014, 7.799994); 
}

VRRP::MoveMesin3(playerid)
{
    MoveDynamicObject(PlayerDaurVars[playerid][MesinDaurObject][2], 29.467884, 1359.775756, 11.491876 - 0.1, 1.5, 0.000005, 0.000037, 7.799992);
    SetTimerEx("MoveMesin3UP", 5500, false, "i", playerid);
}

VRRP::MoveMesin3UP(playerid)
{
    PlayerPlaySound(playerid, 1009, 0, 0, 0);
    MoveDynamicObject(PlayerDaurVars[playerid][DaurObject][2], 29.171897, 1359.677612, 9.711877 - 1.0, 3.0, 0.000000, 0.000000, 7.699999);
    MoveDynamicObject(PlayerDaurVars[playerid][MesinDaurObject][2], 29.467884, 1359.775756, 14.891917, 0.60, 0.000003, 0.000029, 7.799994);
}

VRRP::MoveMesin4(playerid)
{
    MoveDynamicObject(PlayerDaurVars[playerid][MesinDaurObject][3], 30.807901, 1349.954101, 11.491876 - 0.1, 1.5, 0.000006, 0.000044, 7.799992);
    SetTimerEx("MoveMesin4UP", 5500, false, "i", playerid);
}

VRRP::MoveMesin4UP(playerid)
{
    PlayerPlaySound(playerid, 1009, 0, 0, 0);
    MoveDynamicObject(PlayerDaurVars[playerid][DaurObject][3], 30.505033, 1349.817382, 9.711877 - 1.0, 3.0, 0.000000, 0.000000, 7.699999);
    MoveDynamicObject(PlayerDaurVars[playerid][MesinDaurObject][3], 30.807901, 1349.954101, 14.891917, 0.60, 0.000004, 0.000037, 7.799994);
}

forward TakeDaur(playerid);
public TakeDaur(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerTakeDaur[playerid]);
        pTimerTakeDaur[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerDaurVars[playerid][DaurLabelArea]))
    {
        KillTimer(pTimerTakeDaur[playerid]);
        pTimerTakeDaur[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][DaurLabelArea]))
    {
        KillTimer(pTimerTakeDaur[playerid]);
        pTimerTakeDaur[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerTakeDaur[playerid]);
        pTimerTakeDaur[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTimerTakeDaur[playerid]);
        pTimerTakeDaur[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
		SetPlayerAttachedObject(playerid, 9, 2912, 1, 0.181, 0.253, -0.067, -82.3, 1.0, 6.0, 0.51, 0.575, 0.483);
        
        if(DestroyDynamicArea(PlayerDaurVars[playerid][DaurLabelArea]))
            PlayerDaurVars[playerid][DaurLabelArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        
        if(DestroyDynamic3DTextLabel(PlayerDaurVars[playerid][DaurLabel]))
            PlayerDaurVars[playerid][DaurLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        
        new rand = RandomEx(1, 4);
        if(rand == 1)
        {
            PlayerDaurVars[playerid][SortirLabelArea][0] = CreateDynamicSphere(2308.0110, 2703.8499, -46.5938, 2.0, -1, -1, playerid);
            PlayerDaurVars[playerid][SortirLabel][0] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Menyortir", -1, 2308.0110, 2703.8499, -46.5938 + 0.3, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);       
        }
        if(rand == 2)
        {
            PlayerDaurVars[playerid][SortirLabelArea][1] = CreateDynamicSphere(2300.3809, 2703.6301, -46.5938, 2.0, -1, -1, playerid);
            PlayerDaurVars[playerid][SortirLabel][1] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Menyortir", -1, 2300.3809, 2703.6301, -46.5938 + 0.3, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);  
        }              
        if(rand == 3)
        {
            PlayerDaurVars[playerid][SortirLabelArea][2] = CreateDynamicSphere(2291.0989, 2703.2781, -46.5938, 2.0, -1, -1, playerid);
            PlayerDaurVars[playerid][SortirLabel][2] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Menyortir", -1, 2291.0989, 2703.2781, -46.5938 + 0.3, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);
        }
        if(rand == 4)
        {
            PlayerDaurVars[playerid][SortirLabelArea][3] = CreateDynamicSphere(2281.5178, 2703.3074, -46.5938, 2.0, -1, -1, playerid);
            PlayerDaurVars[playerid][SortirLabel][3] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Menyortir", -1, 2281.5178, 2703.3074, -46.5938 + 0.3, 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);
        }
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 25;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
    }
    return 1;
}

forward Sortir1(playerid);
public Sortir1(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerDaurVars[playerid][SortirLabelArea][0]))
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][SortirLabelArea][0]))
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        if(DestroyDynamicArea(PlayerDaurVars[playerid][SortirLabelArea][0])) PlayerDaurVars[playerid][SortirLabelArea][0] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        if(DestroyDynamic3DTextLabel(PlayerDaurVars[playerid][SortirLabel][0])) PlayerDaurVars[playerid][SortirLabel][0] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        if(DestroyDynamicObject(PlayerDaurVars[playerid][BoxObject][0])) PlayerDaurVars[playerid][BoxObject][0] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        new rands = RandomEx(1, 51), randboxmats = (1, 4);
        switch(rands)
        {
            case 1..21:
            {
                Inventory_Add(playerid, "Boxmats", 2912, randboxmats);
                ShowItemBox(playerid, sprintf("ADDED %dx", randboxmats), "Boxmats", 2912);
            }
            case 22..51:
            {
                Inventory_Add(playerid, "Boxmats", 2912, 1);
                ShowItemBox(playerid, "ADDED 1x", "Boxmats", 2912);
            }
        }
        GivePlayerXP(playerid, DEFAULT_XP);
        new rand = Random(sizeof(TakeRandom));
        PlayerDaurVars[playerid][DaurLabelArea] = CreateDynamicSphere(TakeRandom[rand][0], TakeRandom[rand][1], TakeRandom[rand][2], 2.0, -1, -1, playerid);
        PlayerDaurVars[playerid][DaurLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Mengambil", -1, TakeRandom[rand][0], TakeRandom[rand][1], TakeRandom[rand][2] + 0.3, 80.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 18.75;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]); 
        return 0;
    }
    return 1;
}

forward Sortir2(playerid);
public Sortir2(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerDaurVars[playerid][SortirLabelArea][1]))
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][SortirLabelArea][1]))
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        if(DestroyDynamicArea(PlayerDaurVars[playerid][SortirLabelArea][1])) PlayerDaurVars[playerid][SortirLabelArea][1] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        if(DestroyDynamic3DTextLabel(PlayerDaurVars[playerid][SortirLabel][1])) PlayerDaurVars[playerid][SortirLabel][1] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        if(DestroyDynamicObject(PlayerDaurVars[playerid][BoxObject][1])) PlayerDaurVars[playerid][BoxObject][1] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        new rands = RandomEx(1, 51), randboxmats = (1, 4);
        switch(rands)
        {
            case 1..21:
            {
                Inventory_Add(playerid, "Boxmats", 2912, randboxmats);
                ShowItemBox(playerid, sprintf("ADDED %dx", randboxmats), "Boxmats", 2912);
            }
            case 22..51:
            {
                Inventory_Add(playerid, "Boxmats", 2912, 1);
                ShowItemBox(playerid, "ADDED 1x", "Boxmats", 2912);
            }
        }
        GivePlayerXP(playerid, DEFAULT_XP);
        new rand = Random(sizeof(TakeRandom));
        PlayerDaurVars[playerid][DaurLabelArea] = CreateDynamicSphere(TakeRandom[rand][0], TakeRandom[rand][1], TakeRandom[rand][2], 2.0, -1, -1, playerid);
        PlayerDaurVars[playerid][DaurLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Mengambil", -1, TakeRandom[rand][0], TakeRandom[rand][1], TakeRandom[rand][2] + 0.3, 80.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 18.75;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]); 
        return 0;
    }
    return 1;
}

forward Sortir3(playerid);
public Sortir3(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerDaurVars[playerid][SortirLabelArea][2]))
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][SortirLabelArea][2]))
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        if(DestroyDynamicArea(PlayerDaurVars[playerid][SortirLabelArea][2])) PlayerDaurVars[playerid][SortirLabelArea][2] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        if(DestroyDynamic3DTextLabel(PlayerDaurVars[playerid][SortirLabel][2])) PlayerDaurVars[playerid][SortirLabel][2] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        if(DestroyDynamicObject(PlayerDaurVars[playerid][BoxObject][2])) PlayerDaurVars[playerid][BoxObject][2] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        new rands = RandomEx(1, 51), randboxmats = (1, 4);
        switch(rands)
        {
            case 1..21:
            {
                Inventory_Add(playerid, "Boxmats", 2912, randboxmats);
                ShowItemBox(playerid, sprintf("ADDED %dx", randboxmats), "Boxmats", 2912);
            }
            case 22..51:
            {
                Inventory_Add(playerid, "Boxmats", 2912, 1);
                ShowItemBox(playerid, "ADDED 1x", "Boxmats", 2912);
            }
        }
        GivePlayerXP(playerid, DEFAULT_XP);
        new rand = Random(sizeof(TakeRandom));
        PlayerDaurVars[playerid][DaurLabelArea] = CreateDynamicSphere(TakeRandom[rand][0], TakeRandom[rand][1], TakeRandom[rand][2], 2.0, -1, -1, playerid);
        PlayerDaurVars[playerid][DaurLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Mengambil", -1, TakeRandom[rand][0], TakeRandom[rand][1], TakeRandom[rand][2] + 0.3, 80.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 18.75;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]); 
        return 0;
    }
    return 1;
}

forward Sortir4(playerid);
public Sortir4(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerDaurVars[playerid][SortirLabelArea][3]))
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][SortirLabelArea][3]))
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 150)
    {
        KillTimer(pTimerSortir[playerid]);
        pTimerSortir[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        if(DestroyDynamicArea(PlayerDaurVars[playerid][SortirLabelArea][3])) PlayerDaurVars[playerid][SortirLabelArea][3] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        if(DestroyDynamic3DTextLabel(PlayerDaurVars[playerid][SortirLabel][3])) PlayerDaurVars[playerid][SortirLabel][3] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        if(DestroyDynamicObject(PlayerDaurVars[playerid][BoxObject][3])) PlayerDaurVars[playerid][BoxObject][3] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        new rands = RandomEx(1, 51), randboxmats = (1, 4);
        switch(rands)
        {
            case 1..21:
            {
                Inventory_Add(playerid, "Boxmats", 2912, randboxmats);
                ShowItemBox(playerid, sprintf("ADDED %dx", randboxmats), "Boxmats", 2912);
            }
            case 22..51:
            {
                Inventory_Add(playerid, "Boxmats", 2912, 1);
                ShowItemBox(playerid, "ADDED 1x", "Boxmats", 2912);
            }
        }
        GivePlayerXP(playerid, DEFAULT_XP);
        new rand = Random(sizeof(TakeRandom));
        PlayerDaurVars[playerid][DaurLabelArea] = CreateDynamicSphere(TakeRandom[rand][0], TakeRandom[rand][1], TakeRandom[rand][2], 2.0, -1, -1, playerid);
        PlayerDaurVars[playerid][DaurLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Mengambil", -1, TakeRandom[rand][0], TakeRandom[rand][1], TakeRandom[rand][2] + 0.3, 80.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 18.75;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110/150;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]); 
        return 0;
    }
    return 1;
}

forward DaurUlang1(playerid);
public DaurUlang1(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(IsPlayerInjured(playerid))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        return 0;
    }

    if(!IsValidDynamicArea(PlayerDaurVars[playerid][DaurArea][0]))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][DaurArea][0]))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!PlayerHasItem(playerid, "Boxmats"))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Boxmats!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 126)
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        DestroyDynamicObject(PlayerDaurVars[playerid][DaurObject][0]);
        
        new rands = RandomEx(1, 90);
        new randbaja = RandomEx(2, 10), randkaret = RandomEx(4, 15), 
        randplastik = RandomEx(4, 10), randkaca = RandomEx(1, 6), 
        randalumu = RandomEx(1, 12), randplatbesi = RandomEx(1, 3);
        switch(rands)
        {
            case 1..11:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Baja", 19772, randbaja);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randbaja), "BAJA", 19772);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 12..35:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Plastik", 1264, randplastik);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randplastik), "PLASTIK", 1264);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 36..56:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Karet", 1316, randkaret);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randkaret), "KARET", 1316);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 57..71:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Alumunium", 2937, randalumu);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randalumu), "ALUMUNIUM", 2937);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 72..89:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Kaca", 1649, randkaca);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randkaca), "KACA", 1649);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
        }
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 8.4;

        new Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime]*99.000000/126.000000;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward DaurUlang2(playerid);
public DaurUlang2(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(IsPlayerInjured(playerid))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        return 0;
    }

    if(!IsValidDynamicArea(PlayerDaurVars[playerid][DaurArea][1]))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][DaurArea][1]))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!PlayerHasItem(playerid, "Boxmats"))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Boxmats!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 126)
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        DestroyDynamicObject(PlayerDaurVars[playerid][DaurObject][1]);
        
        new rands = RandomEx(1, 90);
        new randbaja = RandomEx(2, 10), randkaret = RandomEx(4, 15), 
        randplastik = RandomEx(4, 10), randkaca = RandomEx(1, 6), 
        randalumu = RandomEx(1, 12), randplatbesi = RandomEx(1, 3);
        switch(rands)
        {
            case 1..11:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Baja", 19772, randbaja);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randbaja), "BAJA", 19772);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 12..35:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Plastik", 1264, randplastik);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randplastik), "PLASTIK", 1264);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 36..56:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Karet", 1316, randkaret);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randkaret), "KARET", 1316);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 57..71:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Alumunium", 2937, randalumu);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randalumu), "ALUMUNIUM", 2937);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 72..89:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Kaca", 1649, randkaca);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randkaca), "KACA", 1649);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
        }
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 8.4;

        new Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime]*99.000000/126.000000;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward DaurUlang3(playerid);
public DaurUlang3(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(IsPlayerInjured(playerid))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        return 0;
    }

    if(!IsValidDynamicArea(PlayerDaurVars[playerid][DaurArea][2]))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][DaurArea][2]))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!PlayerHasItem(playerid, "Boxmats"))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Boxmats!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 126)
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        DestroyDynamicObject(PlayerDaurVars[playerid][DaurObject][2]);
        
        new rands = RandomEx(1, 90);
        new randbaja = RandomEx(2, 10), randkaret = RandomEx(4, 15), 
        randplastik = RandomEx(4, 10), randkaca = RandomEx(1, 6), 
        randalumu = RandomEx(1, 12), randplatbesi = RandomEx(1, 3);
        switch(rands)
        {
            case 1..11:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Baja", 19772, randbaja);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randbaja), "BAJA", 19772);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 12..35:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Plastik", 1264, randplastik);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randplastik), "PLASTIK", 1264);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 36..56:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Karet", 1316, randkaret);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randkaret), "KARET", 1316);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 57..71:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Alumunium", 2937, randalumu);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randalumu), "ALUMUNIUM", 2937);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 72..89:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Kaca", 1649, randkaca);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randkaca), "KACA", 1649);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
        }
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 8.4;

        new Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime]*99.000000/126.000000;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward DaurUlang4(playerid);
public DaurUlang4(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(IsPlayerInjured(playerid))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        return 0;
    }

    if(!IsValidDynamicArea(PlayerDaurVars[playerid][DaurArea][3]))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerDaurVars[playerid][DaurArea][3]))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!PlayerHasItem(playerid, "Boxmats"))
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Boxmats!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 126)
    {
        KillTimer(pTimerDaurUlang[playerid]);
        pTimerDaurUlang[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        DestroyDynamicObject(PlayerDaurVars[playerid][DaurObject][3]);
        
        new rands = RandomEx(1, 90);
        new randbaja = RandomEx(2, 10), randkaret = RandomEx(4, 15), 
        randplastik = RandomEx(4, 10), randkaca = RandomEx(1, 6), 
        randalumu = RandomEx(1, 12), randplatbesi = RandomEx(1, 3);
        switch(rands)
        {
            case 1..11:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Baja", 19772, randbaja);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randbaja), "BAJA", 19772);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 12..35:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Plastik", 1264, randplastik);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randplastik), "PLASTIK", 1264);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 36..56:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Karet", 1316, randkaret);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randkaret), "KARET", 1316);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 57..71:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Alumunium", 2937, randalumu);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randalumu), "ALUMUNIUM", 2937);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
            case 72..89:
            {
                Inventory_Remove(playerid, "Boxmats", 10);
                Inventory_Add(playerid, "Kaca", 1649, randkaca);
                Inventory_Add(playerid, "Plat Besi", 3117, randplatbesi);
                ShowItemBox(playerid, sprintf("Recived %dx", randkaca), "KACA", 1649);
                ShowItemBox(playerid, sprintf("Recived %dx", randplatbesi), "PLAT BESI", 3117);
            }
        }
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 8.4;

        new Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime]*99.000000/126.000000;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}