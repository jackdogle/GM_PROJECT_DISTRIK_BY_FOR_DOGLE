#include <YSI\y_hooks>

new pBenangTimer[MAX_PLAYERS] = {-1, ...};
new pKainTimer[MAX_PLAYERS] = {-1, ...};
new pJahitTimer[MAX_PLAYERS] = {-1, ...};

enum E_STUFFTAILOR
{
    STREAMER_TAG_MAP_ICON:TailorIcon,
    STREAMER_TAG_AREA:TailorMakeBenang[4],
    STREAMER_TAG_AREA:TailorMakeKaC[7],
    STREAMER_TAG_OBJECT:TailorCircleObjects[11],
};
new PlayerTailorVars[MAX_PLAYERS][E_STUFFTAILOR];

stock LoadVarsTailor(playerid)
{
    UnloadVarsTailor(playerid);

    PlayerTailorVars[playerid][TailorIcon] = CreateDynamicMapIcon(2348.7112,-82.1600,26.3359, 45, -1, 0, 0, playerid, 9999.0, MAPICON_GLOBAL, -1, 1);

    PlayerTailorVars[playerid][TailorMakeBenang][0] = CreateDynamicSphere(2381.9028, -85.9892, 26.8360, 1.5, 0, 0, playerid);
    PlayerTailorVars[playerid][TailorMakeBenang][1] = CreateDynamicSphere(2377.6863, -86.2427, 26.8360, 1.5, 0, 0, playerid);
    PlayerTailorVars[playerid][TailorMakeBenang][2] = CreateDynamicSphere(2373.0012, -86.0525, 26.8350, 1.5, 0, 0, playerid);
    PlayerTailorVars[playerid][TailorMakeBenang][3] = CreateDynamicSphere(2368.0559, -86.1394, 26.8350, 1.5, 0, 0, playerid);

    PlayerTailorVars[playerid][TailorMakeKaC][0] = CreateDynamicSphere(2362.9548, -81.6238, 26.8350, 1.5, 0, 0, playerid);
    PlayerTailorVars[playerid][TailorMakeKaC][1] = CreateDynamicSphere(2366.5676, -81.3811, 26.8350, 1.5, 0, 0, playerid);
    PlayerTailorVars[playerid][TailorMakeKaC][2] = CreateDynamicSphere(2370.1460, -81.5627, 26.8350, 1.5, 0, 0, playerid);
    PlayerTailorVars[playerid][TailorMakeKaC][3] = CreateDynamicSphere(2373.4756, -81.4672, 26.8350, 1.5, 0, 0, playerid);
    PlayerTailorVars[playerid][TailorMakeKaC][4] = CreateDynamicSphere(2377.2185, -81.5238, 26.8360, 1.5, 0, 0, playerid);
    PlayerTailorVars[playerid][TailorMakeKaC][5] = CreateDynamicSphere(2380.6672, -81.5442, 26.8360, 1.5, 0, 0, playerid);
    PlayerTailorVars[playerid][TailorMakeKaC][6] = CreateDynamicSphere(2384.3474, -81.3582, 26.8360, 1.5, 0, 0, playerid);

    PlayerTailorVars[playerid][TailorCircleObjects][0] = CreateDynamicObject(1317, 2366.586181, -81.458183, 25.174983, 0.000000, 0.000000, 0.000000, 0, 0, playerid, 300.00, 300.00); 
    SetDynamicObjectMaterial(PlayerTailorVars[playerid][TailorCircleObjects][0], 0, 10765, "airportgnd_sfse", "white", 0xA5FA6D95);
	PlayerTailorVars[playerid][TailorCircleObjects][1] = CreateDynamicObject(1317, 2362.934814, -81.458183, 25.174983, 0.000000, 0.000000, 0.000000, 0, 0, playerid, 300.00, 300.00); 
	SetDynamicObjectMaterial(PlayerTailorVars[playerid][TailorCircleObjects][1], 0, 10765, "airportgnd_sfse", "white", 0xA5FA6D95);
	PlayerTailorVars[playerid][TailorCircleObjects][2] = CreateDynamicObject(1317, 2370.116210, -81.458183, 25.174983, 0.000000, 0.000000, 0.000000, 0, 0, playerid, 300.00, 300.00); 
	SetDynamicObjectMaterial(PlayerTailorVars[playerid][TailorCircleObjects][2], 0, 10765, "airportgnd_sfse", "white", 0xA5FA6D95);
	PlayerTailorVars[playerid][TailorCircleObjects][3] = CreateDynamicObject(1317, 2373.557861, -81.458183, 25.174983, 0.000000, 0.000000, 0.000000, 0, 0, playerid, 300.00, 300.00); 
	SetDynamicObjectMaterial(PlayerTailorVars[playerid][TailorCircleObjects][3], 0, 10765, "airportgnd_sfse", "white", 0xA5FA6D95);
	PlayerTailorVars[playerid][TailorCircleObjects][4] = CreateDynamicObject(1317, 2377.117431, -81.458183, 25.174983, 0.000000, 0.000000, 0.000000, 0, 0, playerid, 300.00, 300.00); 
	SetDynamicObjectMaterial(PlayerTailorVars[playerid][TailorCircleObjects][4], 0, 10765, "airportgnd_sfse", "white", 0xA5FA6D95);
	PlayerTailorVars[playerid][TailorCircleObjects][5] = CreateDynamicObject(1317, 2380.678710, -81.458183, 25.174983, 0.000000, 0.000000, 0.000000, 0, 0, playerid, 300.00, 300.00); 
	SetDynamicObjectMaterial(PlayerTailorVars[playerid][TailorCircleObjects][5], 0, 10765, "airportgnd_sfse", "white", 0xA5FA6D95);
	PlayerTailorVars[playerid][TailorCircleObjects][6] = CreateDynamicObject(1317, 2384.329101, -81.458183, 25.174983, 0.000000, 0.000007, 0.000000, 0, 0, playerid, 300.00, 300.00); 
	SetDynamicObjectMaterial(PlayerTailorVars[playerid][TailorCircleObjects][6], 0, 10765, "airportgnd_sfse", "white", 0xA5FA6D95);
	PlayerTailorVars[playerid][TailorCircleObjects][7] = CreateDynamicObject(1317, 2381.918457, -86.128189, 25.174983, 0.000000, 0.000000, 0.000000, 0, 0, playerid, 300.00, 300.00); 
	SetDynamicObjectMaterial(PlayerTailorVars[playerid][TailorCircleObjects][7], 0, 10765, "airportgnd_sfse", "white", 0xA5FA6D95);
	PlayerTailorVars[playerid][TailorCircleObjects][8] = CreateDynamicObject(1317, 2377.718261, -86.128189, 25.174983, 0.000000, 0.000000, 0.000000, 0, 0, playerid, 300.00, 300.00); 
	SetDynamicObjectMaterial(PlayerTailorVars[playerid][TailorCircleObjects][8], 0, 10765, "airportgnd_sfse", "white", 0xA5FA6D95);
	PlayerTailorVars[playerid][TailorCircleObjects][9] = CreateDynamicObject(1317, 2372.958007, -86.128189, 25.174983, 0.000000, 0.000000, 0.000000, 0, 0, playerid, 300.00, 300.00); 
	SetDynamicObjectMaterial(PlayerTailorVars[playerid][TailorCircleObjects][9], 0, 10765, "airportgnd_sfse", "white", 0xA5FA6D95);
	PlayerTailorVars[playerid][TailorCircleObjects][10] = CreateDynamicObject(1317, 2368.048095, -86.128189, 25.174983, 0.000000, 0.000000, 0.000000, 0, 0, playerid, 300.00, 300.00); 
	SetDynamicObjectMaterial(PlayerTailorVars[playerid][TailorCircleObjects][10], 0, 10765, "airportgnd_sfse", "white", 0xA5FA6D95);
}

stock UnloadVarsTailor(playerid)
{
    if(IsValidDynamicMapIcon(PlayerTailorVars[playerid][TailorIcon]))
        DestroyDynamicMapIcon(PlayerTailorVars[playerid][TailorIcon]);
    PlayerTailorVars[playerid][TailorIcon] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

    for(new i = 0; i < 4; i ++) {
        if(IsValidDynamicArea(PlayerTailorVars[playerid][TailorMakeBenang][i]))
            DestroyDynamicArea(PlayerTailorVars[playerid][TailorMakeBenang][i]);
        PlayerTailorVars[playerid][TailorMakeBenang][i] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
    }

    for(new i = 0; i < 7; i ++) {
        if(IsValidDynamicArea(PlayerTailorVars[playerid][TailorMakeKaC][i]))
            DestroyDynamicArea(PlayerTailorVars[playerid][TailorMakeKaC][i]);
        PlayerTailorVars[playerid][TailorMakeKaC][i] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
    }

    for(new i = 0; i < 11; i ++) {
        if(IsValidDynamicObject(PlayerTailorVars[playerid][TailorCircleObjects][i]))
            DestroyDynamicObject(PlayerTailorVars[playerid][TailorCircleObjects][i]);
        PlayerTailorVars[playerid][TailorCircleObjects][i] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
    }
}

hook OnPlayerConnect(playerid)
{
    pBenangTimer[playerid] = -1;
    pKainTimer[playerid] = -1;
    pJahitTimer[playerid] = -1;
    return 1;
}

stock TailorBenang_Area(playerid)
{
    for(new i = 0; i < 4; i ++) {
        if(IsPlayerInDynamicArea(playerid, PlayerTailorVars[playerid][TailorMakeBenang][i]))
            return 1;
    }
    return 0;
}

stock TailorKaC_Area(playerid)
{
    for(new i = 0; i < 7; i ++) {
        if(IsPlayerInDynamicArea(playerid, PlayerTailorVars[playerid][TailorMakeKaC][i]))
            return 1;
    }
    return 0;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pJob] == JOB_TAILOR)
    {
        for(new i = 0; i < 4; i ++) {
            if(areaid == PlayerTailorVars[playerid][TailorMakeBenang][i]) {
                ShowKey(playerid, "[Y]- Membuat Benang");
            }
        }

        for(new i = 0; i < 7; i ++) {
            if(areaid == PlayerTailorVars[playerid][TailorMakeKaC][i]) {
                ShowKey(playerid, "[Y]- Olah Bahan");
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pJob] == JOB_TAILOR)
    {
        for(new i = 0; i < 4; i ++) {
            if(areaid == PlayerTailorVars[playerid][TailorMakeBenang][i]) {
                HideShortKey(playerid);
            }
        }

        for(new i = 0; i < 7; i ++) {
            if(areaid == PlayerTailorVars[playerid][TailorMakeKaC][i]) {
                HideShortKey(playerid);
            }
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(TailorBenang_Area(playerid))
        {
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(AccountData[playerid][pJob] != JOB_TAILOR) return false;

            ShowMinigame(playerid, "OnMinigameComplete", "TailorBenangMinigame");
        }

        if(TailorKaC_Area(playerid))
        {
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(AccountData[playerid][pJob] != JOB_TAILOR) return false;

            Dialog_Show(playerid, DialogOlahTailor, DIALOG_STYLE_TABLIST_HEADERS, "Olah Bahan -"TCRP" District ",
            "Bahan\tKebutuhan\
            \nKain\t1 Benang\
            \n"LIGHTGREY"Pakaian\t1 Kain", "Olah", "Batal");
        }
    }
    return 1;
}

Dialog:DialogOlahTailor(playerid, response, listitem, inputtext[])
{
    if(!response) return false;
    if(AccountData[playerid][pJob] != JOB_TAILOR) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan tukang jahit!");
    switch(listitem)
    {
        case 0:// 
        {
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
            
            AccountData[playerid][ActivityTime] = 1;
            pKainTimer[playerid] = SetTimerEx("CollectKain", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMBUAT KAIN");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);   
        }
        case 1:// 
        {
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            AccountData[playerid][ActivityTime] = 1;
            pJahitTimer[playerid] = SetTimerEx("CollectPakaian", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMBUAT PAKAIAN");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);  
        }
    }
    return 1;
}

// hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
// {
//     if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
//     {
//         if(AccountData[playerid][pJob] == JOB_TAILOR)
//         {
//             if(IsPlayerInDynamicArea(playerid, PlayerTailorVars[playerid][TailorBenang1]))
//             {
//                 if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
//                 if(AccountData[playerid][pInjured]) return 0;

//                 AccountData[playerid][ActivityTime] = 1;
//                 pBenangTimer[playerid] = SetTimerEx("OlahBenang1", 1000, true, "d", playerid);
//                 PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH BENANG");
//                 ShowProgressBar(playerid);
//                 ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
//             }

//             if(IsPlayerInDynamicArea(playerid, PlayerTailorVars[playerid][TailorBenang2]))
//             {
//                 if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
//                 if(AccountData[playerid][pInjured]) return 0;

//                 AccountData[playerid][ActivityTime] = 1;
//                 pBenangTimer[playerid] = SetTimerEx("OlahBenang2", 1000, true, "d", playerid);
//                 PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH BENANG");
//                 ShowProgressBar(playerid);
//                 ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
//             }

//             if(IsPlayerInDynamicArea(playerid, PlayerTailorVars[playerid][TailorBenang3]))
//             {
//                 if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
//                 if(AccountData[playerid][pInjured]) return 0;

//                 AccountData[playerid][ActivityTime] = 1;
//                 pBenangTimer[playerid] = SetTimerEx("OlahBenang3", 1000, true, "d", playerid);
//                 PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH BENANG");
//                 ShowProgressBar(playerid);
//                 ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
//             }

//             if(IsPlayerInDynamicArea(playerid, PlayerTailorVars[playerid][TailorKain1]))
//             {
//                 if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
//                 if(AccountData[playerid][pInjured]) return 0;

//                 AccountData[playerid][ActivityTime] = 1;
//                 pKainTimer[playerid] = SetTimerEx("BuatKain1", 1000, true, "d", playerid);
//                 PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMBUAT KAIN");
//                 ShowProgressBar(playerid);
//                 ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
//             }

//             if(IsPlayerInDynamicArea(playerid, PlayerTailorVars[playerid][TailorKain2]))
//             {
//                 if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
//                 if(AccountData[playerid][pInjured]) return 0;

//                 AccountData[playerid][ActivityTime] = 1;
//                 pKainTimer[playerid] = SetTimerEx("BuatKain2", 1000, true, "d", playerid);
//                 PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMBUAT KAIN");
//                 ShowProgressBar(playerid);
//                 ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
//             }

//             if(IsPlayerInDynamicArea(playerid, PlayerTailorVars[playerid][TailorKain3]))
//             {
//                 if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
//                 if(AccountData[playerid][pInjured]) return 0;

//                 AccountData[playerid][ActivityTime] = 1;
//                 pKainTimer[playerid] = SetTimerEx("BuatKain3", 1000, true, "d", playerid);
//                 PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMBUAT KAIN");
//                 ShowProgressBar(playerid);
//                 ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
//             }

//             if(IsPlayerInDynamicArea(playerid, PlayerTailorVars[playerid][TailorJahit1]))
//             {
//                 if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
//                 if(AccountData[playerid][pInjured]) return 0;

//                 AccountData[playerid][ActivityTime] = 1;
//                 pJahitTimer[playerid] = SetTimerEx("JahitBaju1", 1000, true, "d", playerid);
//                 PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENJAHIT");
//                 ShowProgressBar(playerid);
//                 ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
//             }

//             if(IsPlayerInDynamicArea(playerid, PlayerTailorVars[playerid][TailorJahit2]))
//             {
//                 if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
//                 if(AccountData[playerid][pInjured]) return 0;

//                 AccountData[playerid][ActivityTime] = 1;
//                 pJahitTimer[playerid] = SetTimerEx("JahitBaju2", 1000, true, "d", playerid);
//                 PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENJAHIT");
//                 ShowProgressBar(playerid);
//                 ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
//             }

//             if(IsPlayerInDynamicArea(playerid, PlayerTailorVars[playerid][TailorJahit3]))
//             {
//                 if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
//                 if(AccountData[playerid][pInjured]) return 0;

//                 AccountData[playerid][ActivityTime] = 1;
//                 pJahitTimer[playerid] = SetTimerEx("JahitBaju3", 1000, true, "d", playerid);
//                 PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENJAHIT");
//                 ShowProgressBar(playerid);
//                 ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
//             }
//         }
//     }
//     return 1;
// }