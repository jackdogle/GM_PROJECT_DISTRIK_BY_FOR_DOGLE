/*
    Minigame System
    Author: Kawee
    Description: Sistem minigame yang dapat digunakan kembali dengan integrasi bilah kemajuan
*/

#include <YSI\y_hooks>

// Variables
new PlayerText:Minigame_Buttons[MAX_PLAYERS][9];
new PlayerText:Minigame_Background[MAX_PLAYERS][4];
new Minigame_Color[MAX_PLAYERS][9];
new bool:Minigame_Active[MAX_PLAYERS];  
new Minigame_Errors[MAX_PLAYERS];
new Minigame_Success[MAX_PLAYERS];
new Minigame_Attempts[MAX_PLAYERS];
new Minigame_Callback[MAX_PLAYERS][64];
new Minigame_CallbackParams[MAX_PLAYERS][64];
new bool:Minigame_Clicked[MAX_PLAYERS][9];
new Minigame_Timer[MAX_PLAYERS];
new Minigame_TimerTask[MAX_PLAYERS];

CreateMinigameTextDraws(playerid)
{
    Minigame_Background[playerid][0] = CreatePlayerTextDraw(playerid, 228.000, 123.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, Minigame_Background[playerid][0], 189.000, 244.000);
    PlayerTextDrawAlignment(playerid, Minigame_Background[playerid][0], 1);
    PlayerTextDrawColor(playerid, Minigame_Background[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, Minigame_Background[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, Minigame_Background[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, Minigame_Background[playerid][0], 255);
    PlayerTextDrawFont(playerid, Minigame_Background[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, Minigame_Background[playerid][0], 1);

    Minigame_Background[playerid][1] = CreatePlayerTextDraw(playerid, 229.000, 124.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, Minigame_Background[playerid][1], 187.000, 242.000);
    PlayerTextDrawAlignment(playerid, Minigame_Background[playerid][1], 1);
    PlayerTextDrawColor(playerid, Minigame_Background[playerid][1], 255);
    PlayerTextDrawSetShadow(playerid, Minigame_Background[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, Minigame_Background[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, Minigame_Background[playerid][1], 255);
    PlayerTextDrawFont(playerid, Minigame_Background[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, Minigame_Background[playerid][1], 1);

    Minigame_Background[playerid][2] = CreatePlayerTextDraw(playerid, 236.000, 355.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, Minigame_Background[playerid][2], 172.000, 5.000);
    PlayerTextDrawAlignment(playerid, Minigame_Background[playerid][2], 1);
    PlayerTextDrawColor(playerid, Minigame_Background[playerid][2], -10270721);
    PlayerTextDrawSetShadow(playerid, Minigame_Background[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, Minigame_Background[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, Minigame_Background[playerid][2], 255);
    PlayerTextDrawFont(playerid, Minigame_Background[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, Minigame_Background[playerid][2], 1);

    Minigame_Background[playerid][3] = CreatePlayerTextDraw(playerid, 255.000, 107.000, "Tekan Kotak Warna Merah");
    PlayerTextDrawLetterSize(playerid, Minigame_Background[playerid][3], 0.300, 1.500);
    PlayerTextDrawAlignment(playerid, Minigame_Background[playerid][3], 1);
    PlayerTextDrawColor(playerid, Minigame_Background[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, Minigame_Background[playerid][3], 1);
    PlayerTextDrawSetOutline(playerid, Minigame_Background[playerid][3], 1);
    PlayerTextDrawBackgroundColor(playerid, Minigame_Background[playerid][3], 150);
    PlayerTextDrawFont(playerid, Minigame_Background[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, Minigame_Background[playerid][3], 1);

    Minigame_Buttons[playerid][0] = CreatePlayerTextDraw(playerid, 231.000, 129.000, "LD_SPAC:white");
    PlayerTextDrawLetterSize(playerid, Minigame_Buttons[playerid][0], -0.008, 0.000);
    PlayerTextDrawTextSize(playerid, Minigame_Buttons[playerid][0], 59.000, 65.000);
    PlayerTextDrawAlignment(playerid, Minigame_Buttons[playerid][0], 1);
    PlayerTextDrawColor(playerid, Minigame_Buttons[playerid][0], 1768516095);
    PlayerTextDrawSetShadow(playerid, Minigame_Buttons[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, Minigame_Buttons[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, Minigame_Buttons[playerid][0], 255);
    PlayerTextDrawFont(playerid, Minigame_Buttons[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, Minigame_Buttons[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, Minigame_Buttons[playerid][0], 1);

    Minigame_Buttons[playerid][1] = CreatePlayerTextDraw(playerid, 293.000, 129.000, "LD_SPAC:white");
    PlayerTextDrawLetterSize(playerid, Minigame_Buttons[playerid][1], -0.008, 0.000);
    PlayerTextDrawTextSize(playerid, Minigame_Buttons[playerid][1], 59.000, 65.000);
    PlayerTextDrawAlignment(playerid, Minigame_Buttons[playerid][1], 1);
    PlayerTextDrawColor(playerid, Minigame_Buttons[playerid][1], 1768516095);
    PlayerTextDrawSetShadow(playerid, Minigame_Buttons[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, Minigame_Buttons[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, Minigame_Buttons[playerid][1], 255);
    PlayerTextDrawFont(playerid, Minigame_Buttons[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, Minigame_Buttons[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, Minigame_Buttons[playerid][1], 1);

    Minigame_Buttons[playerid][2] = CreatePlayerTextDraw(playerid, 355.000, 129.000, "LD_SPAC:white");
    PlayerTextDrawLetterSize(playerid, Minigame_Buttons[playerid][2], -0.008, 0.000);
    PlayerTextDrawTextSize(playerid, Minigame_Buttons[playerid][2], 59.000, 65.000);
    PlayerTextDrawAlignment(playerid, Minigame_Buttons[playerid][2], 1);
    PlayerTextDrawColor(playerid, Minigame_Buttons[playerid][2], 1768516095);
    PlayerTextDrawSetShadow(playerid, Minigame_Buttons[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, Minigame_Buttons[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, Minigame_Buttons[playerid][2], 255);
    PlayerTextDrawFont(playerid, Minigame_Buttons[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, Minigame_Buttons[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, Minigame_Buttons[playerid][2], 1);

    Minigame_Buttons[playerid][3] = CreatePlayerTextDraw(playerid, 231.000, 198.000, "LD_SPAC:white");
    PlayerTextDrawLetterSize(playerid, Minigame_Buttons[playerid][3], -0.008, 0.000);
    PlayerTextDrawTextSize(playerid, Minigame_Buttons[playerid][3], 59.000, 65.000);
    PlayerTextDrawAlignment(playerid, Minigame_Buttons[playerid][3], 1);
    PlayerTextDrawColor(playerid, Minigame_Buttons[playerid][3], 1768516095);
    PlayerTextDrawSetShadow(playerid, Minigame_Buttons[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, Minigame_Buttons[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, Minigame_Buttons[playerid][3], 255);
    PlayerTextDrawFont(playerid, Minigame_Buttons[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, Minigame_Buttons[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, Minigame_Buttons[playerid][3], 1);

    Minigame_Buttons[playerid][4] = CreatePlayerTextDraw(playerid, 293.000, 198.000, "LD_SPAC:white");
    PlayerTextDrawLetterSize(playerid, Minigame_Buttons[playerid][4], -0.008, 0.000);
    PlayerTextDrawTextSize(playerid, Minigame_Buttons[playerid][4], 59.000, 65.000);
    PlayerTextDrawAlignment(playerid, Minigame_Buttons[playerid][4], 1);
    PlayerTextDrawColor(playerid, Minigame_Buttons[playerid][4], 1768516095);
    PlayerTextDrawSetShadow(playerid, Minigame_Buttons[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, Minigame_Buttons[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, Minigame_Buttons[playerid][4], 255);
    PlayerTextDrawFont(playerid, Minigame_Buttons[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, Minigame_Buttons[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, Minigame_Buttons[playerid][4], 1);

    Minigame_Buttons[playerid][5] = CreatePlayerTextDraw(playerid, 355.000, 198.000, "LD_SPAC:white");
    PlayerTextDrawLetterSize(playerid, Minigame_Buttons[playerid][5], -0.008, 0.000);
    PlayerTextDrawTextSize(playerid, Minigame_Buttons[playerid][5], 59.000, 65.000);
    PlayerTextDrawAlignment(playerid, Minigame_Buttons[playerid][5], 1);
    PlayerTextDrawColor(playerid, Minigame_Buttons[playerid][5], 1768516095);
    PlayerTextDrawSetShadow(playerid, Minigame_Buttons[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, Minigame_Buttons[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, Minigame_Buttons[playerid][5], 255);
    PlayerTextDrawFont(playerid, Minigame_Buttons[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, Minigame_Buttons[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, Minigame_Buttons[playerid][5], 1);

    Minigame_Buttons[playerid][6] = CreatePlayerTextDraw(playerid, 231.000, 267.000, "LD_SPAC:white");
    PlayerTextDrawLetterSize(playerid, Minigame_Buttons[playerid][6], -0.008, 0.000);
    PlayerTextDrawTextSize(playerid, Minigame_Buttons[playerid][6], 59.000, 65.000);
    PlayerTextDrawAlignment(playerid, Minigame_Buttons[playerid][6], 1);
    PlayerTextDrawColor(playerid, Minigame_Buttons[playerid][6], 1768516095);
    PlayerTextDrawSetShadow(playerid, Minigame_Buttons[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, Minigame_Buttons[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, Minigame_Buttons[playerid][6], 255);
    PlayerTextDrawFont(playerid, Minigame_Buttons[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, Minigame_Buttons[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, Minigame_Buttons[playerid][6], 1);

    Minigame_Buttons[playerid][7] = CreatePlayerTextDraw(playerid, 293.000, 267.000, "LD_SPAC:white");
    PlayerTextDrawLetterSize(playerid, Minigame_Buttons[playerid][7], -0.008, 0.000);
    PlayerTextDrawTextSize(playerid, Minigame_Buttons[playerid][7], 59.000, 65.000);
    PlayerTextDrawAlignment(playerid, Minigame_Buttons[playerid][7], 1);
    PlayerTextDrawColor(playerid, Minigame_Buttons[playerid][7], 1768516095);
    PlayerTextDrawSetShadow(playerid, Minigame_Buttons[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, Minigame_Buttons[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, Minigame_Buttons[playerid][7], 255);
    PlayerTextDrawFont(playerid, Minigame_Buttons[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, Minigame_Buttons[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, Minigame_Buttons[playerid][7], 1);

    Minigame_Buttons[playerid][8] = CreatePlayerTextDraw(playerid, 355.000, 267.000, "LD_SPAC:white");
    PlayerTextDrawLetterSize(playerid, Minigame_Buttons[playerid][8], -0.008, 0.000);
    PlayerTextDrawTextSize(playerid, Minigame_Buttons[playerid][8], 59.000, 65.000);
    PlayerTextDrawAlignment(playerid, Minigame_Buttons[playerid][8], 1);
    PlayerTextDrawColor(playerid, Minigame_Buttons[playerid][8], 1768516095);
    PlayerTextDrawSetShadow(playerid, Minigame_Buttons[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, Minigame_Buttons[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, Minigame_Buttons[playerid][8], 255);
    PlayerTextDrawFont(playerid, Minigame_Buttons[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, Minigame_Buttons[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, Minigame_Buttons[playerid][8], 1);
    
    return 1;
}

// Function
ShowMinigame(playerid, const callback[] = "", const params[] = "")
{
    if(Minigame_Active[playerid]) return 0;
    
    Minigame_Active[playerid] = true;
    Minigame_Errors[playerid] = 0;
    Minigame_Success[playerid] = 0;
    Minigame_Attempts[playerid] = 0;
    Minigame_Timer[playerid] = 10; // 10 detik
    Minigame_Locked[playerid] = true;
    
    // Reset status klik
    for(new i = 0; i < 9; i++)
    {
        Minigame_Clicked[playerid][i] = false;
    }
    
    // Simpan callback dan parameter
    format(Minigame_Callback[playerid], sizeof(Minigame_Callback[]), callback);
    format(Minigame_CallbackParams[playerid], sizeof(Minigame_CallbackParams[]), params);
    
    // Reset semua tombol ke warna default
    for(new i = 0; i < 9; i++)
    {
        PlayerTextDrawColor(playerid, Minigame_Buttons[playerid][i], 1768516095);
        Minigame_Color[playerid][i] = 1768516095;
    }
    
    PlayerTextDrawShow(playerid, Minigame_Background[playerid][0]);
    PlayerTextDrawShow(playerid, Minigame_Background[playerid][1]);
    
    // Set timer bar ke ukuran penuh
    PlayerTextDrawTextSize(playerid, Minigame_Background[playerid][2], 172.000, 5.000);
    PlayerTextDrawShow(playerid, Minigame_Background[playerid][2]);
    
    PlayerTextDrawShow(playerid, Minigame_Background[playerid][3]);
    
    for(new i = 0; i < 9; i++)
    {
        PlayerTextDrawShow(playerid, Minigame_Buttons[playerid][i]);
    }
    
    // Tampilkan kotak merah - pastikan 4 kotak merah
    new redBoxes = 0;
    new usedBoxes[9];
    for(new i = 0; i < 9; i++) usedBoxes[i] = 0;
    
    while(redBoxes < 4)
    {
        new rand = random(9);
        if(usedBoxes[rand] == 0)
        {
            PlayerTextDrawColor(playerid, Minigame_Buttons[playerid][rand], COLOR_RED);
            PlayerTextDrawShow(playerid, Minigame_Buttons[playerid][rand]);
            Minigame_Color[playerid][rand] = COLOR_RED;
            usedBoxes[rand] = 1;
            redBoxes++;
        }
    }

    SetTimerEx("ResetButtonColors", 1500, false, "i", playerid);
    
    // Aktifkan SelectTextDraw agar tombol bisa diklik
    SelectTextDraw(playerid, COLOR_BLUE);
    
    // Mulai timer visual
    Minigame_TimerTask[playerid] = SetTimerEx("UpdateMinigameTimer", 1000, true, "i", playerid);
    
    return 1;
}

HideMinigame(playerid)
{
    if(!Minigame_Active[playerid]) return 0;
    
    Minigame_Active[playerid] = false;
    
    // Hentikan timer
    KillTimer(Minigame_TimerTask[playerid]);
    
    PlayerTextDrawHide(playerid, Minigame_Background[playerid][0]);
    PlayerTextDrawHide(playerid, Minigame_Background[playerid][1]);
    PlayerTextDrawHide(playerid, Minigame_Background[playerid][2]);
    PlayerTextDrawHide(playerid, Minigame_Background[playerid][3]);
    
    for(new i = 0; i < 9; i++)
    {
        PlayerTextDrawHide(playerid, Minigame_Buttons[playerid][i]);
    }
    
    return 1;
}

forward ResetButtonColors(playerid);
public ResetButtonColors(playerid)
{
    for(new i = 0; i < 9; i++)
    {
        if(Minigame_Color[playerid][i] == COLOR_RED)
        {
            PlayerTextDrawColor(playerid, Minigame_Buttons[playerid][i], 1768516095);
            PlayerTextDrawShow(playerid, Minigame_Buttons[playerid][i]);
        }
    }
    Minigame_Locked[playerid] = false;
    return 1;
}

// Fungsi untuk update timer visual
forward UpdateMinigameTimer(playerid);
public UpdateMinigameTimer(playerid)
{
    if(!Minigame_Active[playerid]) return 0;
    
    Minigame_Timer[playerid]--;
    
    // Update timer bar
    new Float:width = 172.0 * (Minigame_Timer[playerid] / 10.0);
    PlayerTextDrawTextSize(playerid, Minigame_Background[playerid][2], width, 5.000);
    PlayerTextDrawShow(playerid, Minigame_Background[playerid][2]);
    
    if(Minigame_Timer[playerid] <= 0)
    {
        // Waktu habis
        KillTimer(Minigame_TimerTask[playerid]);
        HideMinigame(playerid);
        CancelSelectTextDraw(playerid);
        Minigame_Active[playerid] = false;
        Minigame_Locked[playerid] = false;
        SendClientMessageEx(playerid, COLOR_WHITE, ""RED_E"Time's up! "WHITE_E"You failed the minigame");
    }
    
    return 1;
}


forward OnMinigameComplete(playerid, const callback[], const params[]);
public OnMinigameComplete(playerid, const callback[], const params[])
{
    if(strcmp(params, "ChickenTakeMinigame") == 0)
    {
        AccountData[playerid][ActivityTime] = 1;
        ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 4.0, 1, 0, 0, 0, 0, 1);
        pTimerTakeAyam[playerid] = SetTimerEx("ChickenTake", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL AYAM");
        ShowProgressBar(playerid);
    }
    if(strcmp(params, "TakePetrol") == 0)
    {
        AccountData[playerid][ActivityTime] = 1;
        ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);   
        pTimerCollectOil[playerid] = SetTimerEx("TakingOil", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "COLLECT OIL");
        ShowProgressBar(playerid);
    }
    if(strcmp(params, "TakePureOil") == 0)
    {
        AccountData[playerid][ActivityTime] = 1;
        ApplyAnimation(playerid, "BAR", "Barserve_give", 4.1, 1, 0, 0, 0, 0, 1);
        pTimerRefinedOil[playerid] = SetTimerEx("OilRefined", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "REFINED OIL");
        ShowProgressBar(playerid);
    }
    if(strcmp(params, "TailorBenangMinigame") == 0)
    {
        if(TailorBenang_Area(playerid))
        {
            AccountData[playerid][ActivityTime] = 1;
            pBenangTimer[playerid] = SetTimerEx("CollectBenang", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH BENANG");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
        }
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    CreateMinigameTextDraws(playerid);
    CreateMinigamePHTextDraws(playerid);
    return 1;
} 