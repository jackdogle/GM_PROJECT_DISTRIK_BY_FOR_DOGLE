// ==== [TARIK TAMBANG EVENT] ==== 

//Creator by: Chess7
//Store: Juragan

#include <YSI\y_hooks>

#define TARIK_MAX_TEAM 5
#define TARIK_TIME_MAX 120

new bool:g_TarikEvent;
new bool:g_TarikRunning;
new g_TarikTeam[MAX_PLAYERS]; // 0=none, 1=Merah, 2=Biru
new Float:g_TarikProgress;    // -100 sampai 100
new g_TarikTime, g_TarikTimer;
new g_TarikNeeded; // jumlah peserta per tim
new PlayerText: TarikTambangTD[MAX_PLAYERS][14];
new Float:TarikTambangPOS[MAX_PLAYERS][4];

new Float:TarikPos_Merah[5][3] = {
    {1962.6938,-2592.9275,13.5469},
    {1961.5939,-2592.4868,13.5469},
    {1960.6273,-2592.7776,13.5469},
    {1959.7609,-2592.7734,13.5469},
    {1958.8914,-2592.5671,13.5469}
};
new Float:TarikPos_Putih[5][3] = {
    {1965.8312,-2592.1697,13.5469},
    {1966.9576,-2592.5688,13.5469},
    {1967.8689,-2592.4819,13.5469},
    {1968.7235,-2592.4565,13.5469},
    {1970.0654,-2592.3799,13.5469}
};

CMD:starttariktambang(playerid, params[])
{
    if(CheckAdmin(playerid, 5))
		return PermissionError(playerid);

    if(g_TarikRunning) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Event sedang berlangsung, Gunakan /stoptariktambang");

    ShowPlayerDialog(playerid, DIALOG_TARIKTAMBANG, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE_E"- Pilih Jumlah Peserta per Tim", "1 vs 1\n2 vs 2\n3 vs 3\n4 vs 4\n5 vs 5", "Pilih", "Batal");
    return 1;
}

CMD:stoptariktambang(playerid, params[])
{
    if(CheckAdmin(playerid, 5))
		return PermissionError(playerid);

    if(!g_TarikEvent) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada event tarik tambang yang aktif!");

    StopTarikEvent();
    SendClientMessageToAll(-1, ""YELLOW"[EVENT]: "WHITE_E"Tarik tambang telah dihentikan oleh admin "RED"%s.", AccountData[playerid][pAdminname]);
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(dialogid == DIALOG_TARIKTAMBANG)
    {
        if(response)
        {
            g_TarikNeeded = listitem + 1;
            ShowPlayerDialog(playerid, DIALOG_TIMETAMBANG, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE_E"-Batas Waktu Event (detik)", "Masukkan batas waktu event tarik tambang (maks 120 detik):", "Set", "Batal");
        }
    }
    if(dialogid == DIALOG_TIMETAMBANG)
    {
        if(response)
        {
            g_TarikTime = strval(inputtext);
            if(g_TarikTime < 10 || g_TarikTime > TARIK_TIME_MAX)
            {
                ShowTDN(playerid, NOTIFICATION_ERROR, "Batas waktu minimal 10 detik, maksimal 120 detik!");
                return 1;
            }
            MulaiPersiapanTarik(playerid);
        }
    }
    return 1;
}

stock MulaiPersiapanTarik(adminid)
{
    g_TarikEvent = true;
    g_TarikRunning = false;
    g_TarikProgress = 1.0;

    SendClientMessageToAll(-1, ""YELLOW"[EVENT]: "WHITE"Tarik Tambang dimulai! Gunakan "YELLOW"/jointarik 1 ["RED"Team Merah] "WHITE"atau "YELLOW"/jointarik 2 ["BLUE"Team Biru] "WHITE"untuk bergabung.");

    if(IsPlayerConnected(adminid))
    {
        SendClientMessage(adminid, -1, ""RED"[ADMIN]: "WHITE"Anda memulai event Tarik Tambang. Gunakan: "YELLOW"/jointarik 1 ["RED"Tim Merah] "WHITE"Atau "YELLOW"/jointarik 2 ["BLUE"Tim biru]");
    }
}

CMD:jointarik(playerid, params[])
{
    if(!g_TarikEvent) return ShowTDN(playerid, NOTIFICATION_ERROR, "Event belum dimulai!");
    if(g_TarikRunning) return ShowTDN(playerid, NOTIFICATION_ERROR, "Event sudah berjalan!");

    new team;
    if(sscanf(params, "i", team)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "Gunakan: /jointarik [1=Merah | 2=Putih]");
    if(team != 1 && team != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tim hanya 1 atau 2!");

    new count = 0;
    for(new i; i < MAX_PLAYERS; i++) if(g_TarikTeam[i] == team) count++;
    if(count >= g_TarikNeeded) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tim ini sudah penuh!");

    g_TarikTeam[playerid] = team;
    if(team == 1) 
    {
        SetPlayerPos(playerid, TarikPos_Merah[count][0], TarikPos_Merah[count][1], TarikPos_Merah[count][2]);
        SetPlayerFacingAngle(playerid, 269.8280);
    }
    else 
    {
        SetPlayerPos(playerid, TarikPos_Putih[count][0], TarikPos_Putih[count][1], TarikPos_Putih[count][2]);
        SetPlayerFacingAngle(playerid, 89.8279);
    }
    ApplyAnimation(playerid, "CHAINSAW", "csaw_part", 4.1, 1, 0, 0, 0, 0, 1);

    SetPlayerCameraPos(playerid, 1964.4357,-2582.5051,13.5469);
    SetPlayerCameraLookAt(playerid, 1964.4298,-2584.4570,13.5469);
    new Float:x, Float:y, Float:z, Float:a;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid,a);
    TarikTambangPOS[playerid][0] = x;
    TarikTambangPOS[playerid][1] = y;
    TarikTambangPOS[playerid][2] = z;
    TarikTambangPOS[playerid][3] = a;

    ShowTDNambang(playerid);
    TogglePlayerControllable(playerid, 0);
    for(new xxx = 0; xxx < 15; xxx ++) PlayerTextDrawHide(playerid, HbeStuffs[playerid][xxx]);
    HideHBE(playerid);

    if(team == 1)
        Info(playerid, "Anda berhasil bergabung ke dalam tim "RED"Merah!");
    else
        Info(playerid, "Anda berhasil bergabung ke dalam tim "BLUE"Biru!");

    UpdateTarikTeamCount();

    if(IsAllTeamFull()) MulaiEventTarik();
    return 1;
}

stock IsAllTeamFull()
{
    new merah = 0, biru = 0;
    for(new i; i < MAX_PLAYERS; i++)
    {
        if(g_TarikTeam[i] == 1) merah++;
        if(g_TarikTeam[i] == 2) biru++;
    }
    return (merah == g_TarikNeeded && biru == g_TarikNeeded);
}

stock UpdateTarikTeamCount()
{
    new merah = 0, biru = 0;

    for(new i; i < MAX_PLAYERS; i++)
    {
        if(g_TarikTeam[i] == 1) merah++;
        else if(g_TarikTeam[i] == 2) biru++;
    }

    new strMerah[8], strBiru[8];
    format(strMerah, sizeof strMerah, "%d", merah);
    format(strBiru, sizeof strBiru, "%d", biru);

    for(new p; p < MAX_PLAYERS; p++)
    {
        if(g_TarikTeam[p] != 0)
        {
            PlayerTextDrawSetString(p, TarikTambangTD[p][11], strMerah);
            PlayerTextDrawShow(p, TarikTambangTD[p][11]);

            PlayerTextDrawSetString(p, TarikTambangTD[p][10], strBiru);
            PlayerTextDrawShow(p, TarikTambangTD[p][10]);
        }
    }
}

stock MulaiEventTarik()
{
    g_TarikRunning = true;
    SendClientMessageToAll(-1, ""YELLOW"[EVENT] "WHITE"Semua tim penuh! Tarik tambang dimulai sekarang!");
    g_TarikTimer = SetTimer("UpdateTarikEvent", 1000, true);
}

hook OnClickDynPlayerTextDraw(playerid, PlayerText:textid)
{
    if(textid == TarikTambangTD[playerid][8])
    {
        if(g_TarikRunning && g_TarikTeam[playerid] != 0)
        {
            if(g_TarikTeam[playerid] == 1) // team merah
            {
                g_TarikProgress += 1.0;
                if(g_TarikProgress > 136.0) g_TarikProgress = 136.0;
                ApplyAnimation(playerid, "CHAINSAW", "csaw_part", 4.1, 1, 0, 0, 0, 0, 1);
            }
            else //team biru
            {
                g_TarikProgress -= 1.0;
                if(g_TarikProgress < -136.0) g_TarikProgress = -136.0;
                ApplyAnimation(playerid, "CHAINSAW", "csaw_part", 4.1, 1, 0, 0, 0, 0, 1);
            }
            if(g_TarikProgress >= 0.0) //kalo + nilai x nya ubah jadi merah
            {
                PlayerTextDrawColor(playerid, TarikTambangTD[playerid][1], -1306385665);
            }
            else //kalo nilai x nya - ubah jadi biru
            {
                PlayerTextDrawColor(playerid, TarikTambangTD[playerid][1], 512819004);
            }
            PlayerTextDrawShow(playerid, TarikTambangTD[playerid][1]);

            UpdateTarikBarForAll();
        }
    }
    return 1;
}

forward UpdateTarikEvent(playerid);
public UpdateTarikEvent(playerid)
{
    if(!g_TarikRunning) return 0;
    g_TarikTime--;

    new msg[16];
    format(msg, sizeof msg, "%d", g_TarikTime);

    for(new p; p < MAX_PLAYERS; p++)
    {
        if(g_TarikTeam[p] != 0)
        {
            PlayerTextDrawSetString(p, TarikTambangTD[p][13], msg);
            PlayerTextDrawShow(p, TarikTambangTD[p][13]);
        }
    }
    if(g_TarikProgress >= 136.0)
    {
        SendClientMessageToAll(-1, "[EVENT] Tim "RED"Merah menang!");
        StopTarikEvent();
    }
    else if(g_TarikProgress <= -136.0)
    {
        SendClientMessageToAll(-1, "[EVENT] Tim "BLUE"Biru menang!");
        StopTarikEvent();
    }
    else if(g_TarikTime <= 0)
    {
        if(g_TarikProgress > 0.0) SendClientMessageToAll(-1, "[EVENT] Waktu habis! Tim "RED"Merah unggul!");
        else if(g_TarikProgress < 0.0) SendClientMessageToAll(-1, "[EVENT] Waktu habis! Tim "BLUE"Biru unggul!");
        else SendClientMessageToAll(-1, "[EVENT] Waktu habis! Hasil imbang!");
        StopTarikEvent();
    }
    return 1;
}

stock StopTarikEvent()
{
    g_TarikEvent = false;
    g_TarikRunning = false;
    g_TarikProgress = 1.0; 
    KillTimer(g_TarikTimer);

    for(new i; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i))
        {
            PlayerTextDrawSetString(i, TarikTambangTD[i][10], "0"); // Biru
            PlayerTextDrawShow(i, TarikTambangTD[i][10]);

            PlayerTextDrawSetString(i, TarikTambangTD[i][11], "0"); // Merah
            PlayerTextDrawShow(i, TarikTambangTD[i][11]);

            PlayerTextDrawSetString(i, TarikTambangTD[i][13], "0");
            PlayerTextDrawShow(i, TarikTambangTD[i][13]);

            PlayerTextDrawTextSize(i, TarikTambangTD[i][1], 1.0, 15.0);
            PlayerTextDrawShow(i, TarikTambangTD[i][1]);

            HideTDNambang(i);
            ShowHbeTextdraws(i, AccountData[i][pHUDMode]);
            g_TarikTeam[i] = 0;
            SetCameraBehindPlayer(i);
            TogglePlayerControllable(i, 1);
            ClearAnimations(i, 1);
            StopLoopingAnim(i);
            SetPlayerSpecialAction(i, SPECIAL_ACTION_NONE);
            TogglePlayerControllable(i, 1);
            RemovePlayerAttachedObject(i, 9);
            ApplyAnimation(i, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
            AccountData[i][pLoopAnim] = false;
            SetPlayerPos(i, TarikTambangPOS[i][0], TarikTambangPOS[i][1], TarikTambangPOS[i][2]);
            SetPlayerFacingAngle(i, TarikTambangPOS[i][3]);
        }
    }
}

stock UpdateTarikBarForAll()
{
    for(new i; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerConnected(i) && g_TarikTeam[i] != 0)
        {
            PlayerTextDrawTextSize(i, TarikTambangTD[i][1], g_TarikProgress, 15.0);
            PlayerTextDrawShow(i, TarikTambangTD[i][1]);
        }
    }
}

CreateTDNambang(playerid)
{
    TarikTambangTD[playerid][0] = CreatePlayerTextDraw(playerid, 195.000, 342.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, TarikTambangTD[playerid][0], 271.000, 15.000);
    PlayerTextDrawAlignment(playerid, TarikTambangTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, TarikTambangTD[playerid][0], 10495);
    PlayerTextDrawSetShadow(playerid, TarikTambangTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, TarikTambangTD[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, TarikTambangTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, TarikTambangTD[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, TarikTambangTD[playerid][0], 1);

    TarikTambangTD[playerid][1] = CreatePlayerTextDraw(playerid, 330.000, 342.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, TarikTambangTD[playerid][1], 1.000, 15.000);
    PlayerTextDrawAlignment(playerid, TarikTambangTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, TarikTambangTD[playerid][1], 16711935);
    PlayerTextDrawSetShadow(playerid, TarikTambangTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, TarikTambangTD[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, TarikTambangTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, TarikTambangTD[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, TarikTambangTD[playerid][1], 1);

    TarikTambangTD[playerid][2] = CreatePlayerTextDraw(playerid, 330.000, 330.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, TarikTambangTD[playerid][2], 2.000, 42.000);
    PlayerTextDrawAlignment(playerid, TarikTambangTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, TarikTambangTD[playerid][2], -1306385665);
    PlayerTextDrawSetShadow(playerid, TarikTambangTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, TarikTambangTD[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, TarikTambangTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, TarikTambangTD[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, TarikTambangTD[playerid][2], 1);

    TarikTambangTD[playerid][3] = CreatePlayerTextDraw(playerid, 402.000, 315.000, "TIM MERAH");
    PlayerTextDrawLetterSize(playerid, TarikTambangTD[playerid][3], 0.240, 1.099);
    PlayerTextDrawAlignment(playerid, TarikTambangTD[playerid][3], 2);
    PlayerTextDrawColor(playerid, TarikTambangTD[playerid][3], -16776961);
    PlayerTextDrawSetShadow(playerid, TarikTambangTD[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, TarikTambangTD[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, TarikTambangTD[playerid][3], 150);
    PlayerTextDrawFont(playerid, TarikTambangTD[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, TarikTambangTD[playerid][3], 1);

    TarikTambangTD[playerid][4] = CreatePlayerTextDraw(playerid, 263.000, 315.000, "TIM BIRU");
    PlayerTextDrawLetterSize(playerid, TarikTambangTD[playerid][4], 0.240, 1.099);
    PlayerTextDrawAlignment(playerid, TarikTambangTD[playerid][4], 2);
    PlayerTextDrawColor(playerid, TarikTambangTD[playerid][4], 512819199);
    PlayerTextDrawSetShadow(playerid, TarikTambangTD[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, TarikTambangTD[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, TarikTambangTD[playerid][4], 150);
    PlayerTextDrawFont(playerid, TarikTambangTD[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, TarikTambangTD[playerid][4], 1);

    TarikTambangTD[playerid][5] = CreatePlayerTextDraw(playerid, 330.000, 252.000, "Tekan tombol ini");
    PlayerTextDrawLetterSize(playerid, TarikTambangTD[playerid][5], 0.180, 0.899);
    PlayerTextDrawAlignment(playerid, TarikTambangTD[playerid][5], 2);
    PlayerTextDrawColor(playerid, TarikTambangTD[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, TarikTambangTD[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, TarikTambangTD[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, TarikTambangTD[playerid][5], 150);
    PlayerTextDrawFont(playerid, TarikTambangTD[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, TarikTambangTD[playerid][5], 1);

    TarikTambangTD[playerid][6] = CreatePlayerTextDraw(playerid, 329.000, 264.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, TarikTambangTD[playerid][6], 1.000, 16.000);
    PlayerTextDrawAlignment(playerid, TarikTambangTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, TarikTambangTD[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, TarikTambangTD[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, TarikTambangTD[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, TarikTambangTD[playerid][6], 255);
    PlayerTextDrawFont(playerid, TarikTambangTD[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, TarikTambangTD[playerid][6], 1);

    TarikTambangTD[playerid][7] = CreatePlayerTextDraw(playerid, 325.000, 271.000, "v");
    PlayerTextDrawLetterSize(playerid, TarikTambangTD[playerid][7], 0.329, 1.099);
    PlayerTextDrawAlignment(playerid, TarikTambangTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, TarikTambangTD[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, TarikTambangTD[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, TarikTambangTD[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, TarikTambangTD[playerid][7], 150);
    PlayerTextDrawFont(playerid, TarikTambangTD[playerid][7], 2);
    PlayerTextDrawSetProportional(playerid, TarikTambangTD[playerid][7], 1);

    TarikTambangTD[playerid][8] = CreatePlayerTextDraw(playerid, 319.000, 285.000, "LD_POOL:ball");
    PlayerTextDrawTextSize(playerid, TarikTambangTD[playerid][8], 22.000, 24.000);
    PlayerTextDrawAlignment(playerid, TarikTambangTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, TarikTambangTD[playerid][8], 10495);
    PlayerTextDrawSetShadow(playerid, TarikTambangTD[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, TarikTambangTD[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, TarikTambangTD[playerid][8], 255);
    PlayerTextDrawFont(playerid, TarikTambangTD[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, TarikTambangTD[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, TarikTambangTD[playerid][8], 1);

    TarikTambangTD[playerid][9] = CreatePlayerTextDraw(playerid, 330.000, 252.000, "Tekan tombol ini");
    PlayerTextDrawLetterSize(playerid, TarikTambangTD[playerid][9], 0.180, 0.899);
    PlayerTextDrawAlignment(playerid, TarikTambangTD[playerid][9], 2);
    PlayerTextDrawColor(playerid, TarikTambangTD[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, TarikTambangTD[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, TarikTambangTD[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, TarikTambangTD[playerid][9], 150);
    PlayerTextDrawFont(playerid, TarikTambangTD[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, TarikTambangTD[playerid][9], 1);

    TarikTambangTD[playerid][10] = CreatePlayerTextDraw(playerid, 263.000, 327.000, "0");
    PlayerTextDrawLetterSize(playerid, TarikTambangTD[playerid][10], 0.240, 1.099);
    PlayerTextDrawAlignment(playerid, TarikTambangTD[playerid][10], 2);
    PlayerTextDrawColor(playerid, TarikTambangTD[playerid][10], 512819199);
    PlayerTextDrawSetShadow(playerid, TarikTambangTD[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, TarikTambangTD[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, TarikTambangTD[playerid][10], 150);
    PlayerTextDrawFont(playerid, TarikTambangTD[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, TarikTambangTD[playerid][10], 1);

    TarikTambangTD[playerid][11] = CreatePlayerTextDraw(playerid, 402.000, 326.000, "0");
    PlayerTextDrawLetterSize(playerid, TarikTambangTD[playerid][11], 0.240, 1.099);
    PlayerTextDrawAlignment(playerid, TarikTambangTD[playerid][11], 2);
    PlayerTextDrawColor(playerid, TarikTambangTD[playerid][11], -16776961);
    PlayerTextDrawSetShadow(playerid, TarikTambangTD[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, TarikTambangTD[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, TarikTambangTD[playerid][11], 150);
    PlayerTextDrawFont(playerid, TarikTambangTD[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, TarikTambangTD[playerid][11], 1);

    TarikTambangTD[playerid][12] = CreatePlayerTextDraw(playerid, 325.000, 374.000, "Sisa waktu:");
    PlayerTextDrawLetterSize(playerid, TarikTambangTD[playerid][12], 0.170, 1.199);
    PlayerTextDrawAlignment(playerid, TarikTambangTD[playerid][12], 2);
    PlayerTextDrawColor(playerid, TarikTambangTD[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, TarikTambangTD[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, TarikTambangTD[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, TarikTambangTD[playerid][12], 150);
    PlayerTextDrawFont(playerid, TarikTambangTD[playerid][12], 2);
    PlayerTextDrawSetProportional(playerid, TarikTambangTD[playerid][12], 1);

    TarikTambangTD[playerid][13] = CreatePlayerTextDraw(playerid, 355.000, 374.000, "100");
    PlayerTextDrawLetterSize(playerid, TarikTambangTD[playerid][13], 0.170, 1.199);
    PlayerTextDrawAlignment(playerid, TarikTambangTD[playerid][13], 2);
    PlayerTextDrawColor(playerid, TarikTambangTD[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, TarikTambangTD[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, TarikTambangTD[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, TarikTambangTD[playerid][13], 150);
    PlayerTextDrawFont(playerid, TarikTambangTD[playerid][13], 2);
    PlayerTextDrawSetProportional(playerid, TarikTambangTD[playerid][13], 1);

    return 1;
}

DestroyTDNambang(playerid)
{
    for(new i = 0; i < 14; i++)
    {
        PlayerTextDrawDestroy(playerid, TarikTambangTD[playerid][i]);
    }
    return 1;
}

hook OnPlayerConnect(playerid)
{
    CreateTDNambang(playerid);
    g_TarikTeam[playerid] = 0;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    DestroyTDNambang(playerid);

    if(g_TarikTeam[playerid] != 0)
    {
        g_TarikTeam[playerid] = 0;
        HideTDNambang(playerid);
        SetCameraBehindPlayer(playerid);
        UpdateTarikTeamCount();

        new msg[256];
        format(msg, sizeof(msg), ""YELLOW"Event: "WHITE_E"Peserta "YELLOW_E"%s "WHITE_E"keluar dari event tarik tambang", AccountData[playerid][pName]);
        SendClientMessageToAll(-1, msg);

        if(g_TarikRunning && g_TarikNeeded == 1)
        {
            new merah = 0, biru = 0;
            for(new i; i < MAX_PLAYERS; i++)
            {
                if(IsPlayerConnected(i))
                {
                    if(g_TarikTeam[i] == 1) merah++;
                    else if(g_TarikTeam[i] == 2) biru++;
                }
            }

            if(merah == 0 && biru > 0)
            {
                SendClientMessageToAll(-1, ""GREEN"[EVENT]: "WHITE"Tim Biru menang karena lawan keluar!");
                StopTarikEvent();
            }
            else if(biru == 0 && merah > 0)
            {
                SendClientMessageToAll(-1, ""GREEN"[EVENT]: "WHITE"Tim Merah menang karena lawan keluar!");
                StopTarikEvent();
            }
        }
    }
    return 1;
}

ShowTDNambang(playerid)
{
    for(new i = 0; i < 14; i++)
    {
        PlayerTextDrawShow(playerid, TarikTambangTD[playerid][i]);
        SelectTextDraw(playerid, COLOR_BLUE);
    }
    return 1;
}

HideTDNambang(playerid)
{
    for(new i = 0; i < 14; i++)
    {
        PlayerTextDrawHide(playerid, TarikTambangTD[playerid][i]);
        CancelSelectTextDraw(playerid);
    }
    return 1;
}