#include <YSI\y_hooks>

new pTakingSusuTimer[MAX_PLAYERS] = {-1, ...};
new pProcessSusuTimer[MAX_PLAYERS] = {-1, ...};

enum E_SUSUSTUFF
{
    STREAMER_TAG_AREA:SusuJobArea,
    STREAMER_TAG_AREA:SusuTakeArea,
    STREAMER_TAG_AREA:SusuProcessArea,

    STREAMER_TAG_PICKUP:SusuJobPickup,

    STREAMER_TAG_OBJECT:CowObject,
    STREAMER_TAG_MAP_ICON:MilkerIcon,

    bool:DuringTakeSusu
};
new PlayerSusuVars[MAX_PLAYERS][E_SUSUSTUFF];

function LoadVarsMilker(playerid)
{
    UnloadVarsMilker(playerid);

    PlayerSusuVars[playerid][SusuJobArea] = CreateDynamicCircle(300.2218, 1141.0870, 2.2, 0, 0, playerid);
    PlayerSusuVars[playerid][SusuProcessArea] = CreateDynamicCircle(313.2670, 1146.6887, 3.0, 0, 0, playerid);
    PlayerSusuVars[playerid][MilkerIcon] = CreateDynamicMapIcon(300.2218, 1141.0870, 9.1375, 38, -1, 0, 0, playerid, 9999.0, MAPICON_GLOBAL, -1, 1);
}

function UnloadVarsMilker(playerid)
{
    if(IsValidDynamicArea(PlayerSusuVars[playerid][SusuJobArea]))
        DestroyDynamicArea(PlayerSusuVars[playerid][SusuJobArea]);
    PlayerSusuVars[playerid][SusuJobArea] = STREAMER_TAG_AREA: -1;
    
    if(IsValidDynamicArea(PlayerSusuVars[playerid][SusuProcessArea]))
        DestroyDynamicArea(PlayerSusuVars[playerid][SusuProcessArea]);
    PlayerSusuVars[playerid][SusuProcessArea] = STREAMER_TAG_AREA: -1;
    
    if(IsValidDynamicMapIcon(PlayerSusuVars[playerid][MilkerIcon]))
        DestroyDynamicMapIcon(PlayerSusuVars[playerid][MilkerIcon]);
    PlayerSusuVars[playerid][MilkerIcon] = STREAMER_TAG_MAP_ICON: -1;
    return 1;
}

new Float: CowSpawn[][6] = {
    {255.676315, 1132.190307, 9.590692, -3.599999, 2.599999, -90.000000},
    {232.010650, 1144.196411, 11.504108, 0.000000, 0.000000, 90.000000},
    {231.085708, 1125.457275, 11.084877, 0.000000, 0.000000, 90.000000},
    {244.098205, 1132.427368, 10.070066, 0.000000, 0.000000, 0.000000},
    {270.273223, 1080.310913, 14.967310, -16.599998, 0.000000, 0.000000},
    {250.763809, 1064.126342, 17.084674, 18.800004, 0.000000, -163.100051},
    {260.040649, 1049.746459, 21.084369, -0.100008, 0.000000, 90.000000}
};

hook OnPlayerConnect(playerid)
{
    pTakingSusuTimer[playerid] = -1;
    pProcessSusuTimer[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pTakingSusuTimer[playerid]);
    KillTimer(pProcessSusuTimer[playerid]);
    pTakingSusuTimer[playerid] = -1;
    pProcessSusuTimer[playerid] = -1;
    return 1;
}

forward TakeSusu(playerid);
public TakeSusu(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakingSusuTimer[playerid]);
        pTakingSusuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);  
        return 0;
    }

    if(!IsValidDynamicArea(PlayerSusuVars[playerid][SusuTakeArea]))
    {
        KillTimer(pTakingSusuTimer[playerid]);
        pTakingSusuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerSusuVars[playerid][SusuTakeArea]))
    {
        HideProgressBar(playerid);
        KillTimer(pTakingSusuTimer[playerid]);
        pTakingSusuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        HideProgressBar(playerid);
        KillTimer(pTakingSusuTimer[playerid]);
        pTakingSusuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!");
        return 0;
    }

    if(AccountData[playerid][pInjured] == 1)
    {
        HideProgressBar(playerid);
        KillTimer(pTakingSusuTimer[playerid]);
        pTakingSusuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 105)
    {
        KillTimer(pTakingSusuTimer[playerid]);
        pTakingSusuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        if(IsValidDynamicObject(PlayerSusuVars[playerid][CowObject]))
            DestroyDynamicObject(PlayerSusuVars[playerid][CowObject]);
        PlayerSusuVars[playerid][CowObject] = STREAMER_TAG_OBJECT: -1;
        if(IsValidDynamicArea(PlayerSusuVars[playerid][SusuTakeArea]))
            DestroyDynamicArea(PlayerSusuVars[playerid][SusuTakeArea]);
        PlayerSusuVars[playerid][SusuTakeArea] = STREAMER_TAG_AREA: -1;

        new rand = Random(sizeof(CowSpawn));
        PlayerSusuVars[playerid][CowObject] = CreateDynamicObject(19833, CowSpawn[rand][0], CowSpawn[rand][1], CowSpawn[rand][2], CowSpawn[rand][3], CowSpawn[rand][4], CowSpawn[rand][5], -1, -1, playerid, 300.00, 300.00);
        PlayerSusuVars[playerid][SusuTakeArea] = CreateDynamicCircle(CowSpawn[rand][0], CowSpawn[rand][1], 2.0, 0, 0, playerid);

        new str[512];
        new randmilk = RandomEx(1, 7);
        Inventory_Add(playerid, "Susu Murni", 19570, randmilk);
        format(str, sizeof str, "ADDED %dx", randmilk);
        ShowItemBox(playerid, str, "Susu Murni", 19570);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else
    {
        AccountData[playerid][ActivityTime] += 17.5;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/105;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
    }
    return 1;
}

forward ProcessSusu(playerid);
public ProcessSusu(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pProcessSusuTimer[playerid]);
        pProcessSusuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerSusuVars[playerid][SusuProcessArea]))
    {
        KillTimer(pProcessSusuTimer[playerid]);
        pProcessSusuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerSusuVars[playerid][SusuProcessArea]))
    {
        KillTimer(pProcessSusuTimer[playerid]);
        pProcessSusuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pProcessSusuTimer[playerid]);
        pProcessSusuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Susu Murni") < 5)
    {
        KillTimer(pProcessSusuTimer[playerid]);
        pProcessSusuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Susu Murni Tidak Cukup!");
        return 0;
    }

    if(AccountData[playerid][pInjured] == 1)
    {
        KillTimer(pProcessSusuTimer[playerid]);
        pProcessSusuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 121)
    {
        KillTimer(pProcessSusuTimer[playerid]);
        pProcessSusuTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Inventory_Remove(playerid, "Susu Murni", 5);
        Inventory_Remove(playerid, "Botol");
        Inventory_Add(playerid, "Susu Olahan", 19570);
        ShowItemBox(playerid, "ADDED 1x", "Susu Olahan", 19570);
        GivePlayerXP(playerid, DEFAULT_XP);
    }
    else
    {
        AccountData[playerid][ActivityTime] += 12.1;

        new Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/121;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_SUSU_START:
        {
            if(!response) return 0;
            switch(listitem)
            {
                case 0:
                {
                    if(PlayerSusuVars[playerid][DuringTakeSusu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memulai pekerjaan ini");
                    new rand = random(sizeof(CowSpawn));
                    if(IsValidDynamicObject(PlayerSusuVars[playerid][CowObject]))
                        DestroyDynamicObject(PlayerSusuVars[playerid][CowObject]);
                    PlayerSusuVars[playerid][CowObject] = STREAMER_TAG_OBJECT: -1;
                    if(IsValidDynamicArea(PlayerSusuVars[playerid][SusuTakeArea]))
                        DestroyDynamicArea(PlayerSusuVars[playerid][SusuTakeArea]);
                    PlayerSusuVars[playerid][SusuTakeArea] = STREAMER_TAG_AREA: -1;
                    PlayerSusuVars[playerid][DuringTakeSusu] = true;
                    PlayerSusuVars[playerid][CowObject] = CreateDynamicObject(19833, CowSpawn[rand][0], CowSpawn[rand][1], CowSpawn[rand][2], CowSpawn[rand][3], CowSpawn[rand][4], CowSpawn[rand][5], -1, -1, playerid, 300.00, 300.00);
                    PlayerSusuVars[playerid][SusuTakeArea] = CreateDynamicCircle(CowSpawn[rand][0], CowSpawn[rand][1], 2.0, 0, 0, playerid);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil memulai pekerjaan");
                }
                case 1:
                {
                    if(!PlayerSusuVars[playerid][DuringTakeSusu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
                    if(IsValidDynamicObject(PlayerSusuVars[playerid][CowObject]))
                        DestroyDynamicObject(PlayerSusuVars[playerid][CowObject]);
                    PlayerSusuVars[playerid][CowObject] = STREAMER_TAG_OBJECT: -1;
                    if(IsValidDynamicArea(PlayerSusuVars[playerid][SusuTakeArea]))
                        DestroyDynamicArea(PlayerSusuVars[playerid][SusuTakeArea]);
                    PlayerSusuVars[playerid][SusuTakeArea] = STREAMER_TAG_AREA: -1;
                    PlayerSusuVars[playerid][DuringTakeSusu] = false;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyelesaikan pekerjaan");
                }
            }
        }
    }
    return 0;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(GetPlayerJob(playerid) == JOB_MILKER && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(areaid == PlayerSusuVars[playerid][SusuJobArea])
        {
            ShowKey(playerid, "[Y]- Memulai");
        }
        if(areaid == PlayerSusuVars[playerid][SusuTakeArea])
        {
            ShowKey(playerid, "[Y]- Perah Susu");
        }
        if(areaid == PlayerSusuVars[playerid][SusuProcessArea])
        {
            ShowKey(playerid, "[Y]- Olah Susu");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == PlayerSusuVars[playerid][SusuJobArea])
    {
        HideShortKey(playerid);
    }
    else if(areaid == PlayerSusuVars[playerid][SusuTakeArea])
    {
        HideShortKey(playerid);
    }
    else if(areaid == PlayerSusuVars[playerid][SusuProcessArea])
    {
        HideShortKey(playerid);
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pJob] == JOB_MILKER)
        {
            if(IsPlayerInDynamicArea(playerid, PlayerSusuVars[playerid][SusuJobArea]))
            {
                ShowPlayerDialog(playerid, DIALOG_SUSU_START, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Pemerah Susu",
                "Mulai Perah susu\nSelesaikan Pekerjaan", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, PlayerSusuVars[playerid][SusuTakeArea]))
            {
                if(!PlayerSusuVars[playerid][DuringTakeSusu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

                AccountData[playerid][ActivityTime] = 1;
                pTakingSusuTimer[playerid] = SetTimerEx("TakeSusu", 1000, true, "i", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMERAH SUSU");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,1,0,0,0,0,1);
            }

            if(IsPlayerInDynamicArea(playerid, PlayerSusuVars[playerid][SusuProcessArea]))
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

                AccountData[playerid][ActivityTime] = 1;
                pProcessSusuTimer[playerid] = SetTimerEx("ProcessSusu", 1000, true, "i", playerid);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH SUSU");
                ShowProgressBar(playerid);
                ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            }
        }   
    }
    return 1;
}