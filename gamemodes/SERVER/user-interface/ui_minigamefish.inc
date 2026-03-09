#include <YSI\y_hooks>
#define POSISI_AWALMAKER 299 // Posisi minimum Maker
#define POSISI_AKHIRMAKER 185 // Posisi maksimum Maker
#define POSISI_AWAL 304 // Posisi Awal Muncul Bar
#define MIN_BAR 0     // Posisi minimum bar
#define MAX_BAR -121 	// Posisi maksimum bar
#define POS_TARGET 50  	// Posisi target untuk menang
#define TOLERANSI 5    	// Toleransi untuk menganggap pemain berhasil
#define SPEED_BAR 5 	// kecepatan bar
#define	CALLBACK_MAX 34 // Maximal 34 huruf saat callback di panggil
#define TargetLebar 5

new bool:DirectionBar[MAX_PLAYERS];   // Arah pergerakan bar (true = atas, false = bawah)
new GamesBarShow[MAX_PLAYERS];
new Float:MoveBar[MAX_PLAYERS];   // Posisi bar saat ini untuk setiap pemain
new TimersBar[MAX_PLAYERS];      // Timer untuk menggerakkan bar

new Float:lokasitarget[MAX_PLAYERS];
new PlayerText:MiniGameFish[MAX_PLAYERS][7];

new CallbackLoading[MAX_PLAYERS][CALLBACK_MAX];


stock IsValidBarFish(playerid)
	return GamesBarShow[playerid];

//manggilanya BarFish(playerid, "HDFishbar", "Callback");

stock BarFish(playerid, const HDFishbar[] = "_",const callback[] = "")
{
	if(GamesBarShow[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Bar Sedang aktif"));
    MoveBar[playerid] = MIN_BAR;
    DirectionBar[playerid] = true;
    GamesBarShow[playerid] = 1;
    // Jika callback tidak kosong, maka lakukan sesuatu
    if(callback[0] != EOS)
	{
		format(CallbackLoading[playerid], CALLBACK_MAX, "%s", callback);
	}
	//for(new i = 0; i < 1; i++) PlayerTextDrawShow(playerid, MiniGameFish[playerid][i]);

    CreateBarFish(playerid, HDFishbar);
    return 1;
}

JavaTR:CreateBarFish(playerid, const HDFishbar[])
{    
    TimersBar[playerid] = SetTimerEx("MoveBarFishings", 100, true, "d", playerid);   
	lokasitarget[playerid] = float(RandomEx(POSISI_AKHIRMAKER , POSISI_AWALMAKER - floatround(TargetLebar))); 
	    
	MiniGameFish[playerid][0] = CreatePlayerTextDraw(playerid, 206.000000, 180.000000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MiniGameFish[playerid][0], 61.000000, 130.000000);
    PlayerTextDrawAlignment(playerid, MiniGameFish[playerid][0], 1);
    PlayerTextDrawColor(playerid, MiniGameFish[playerid][0], 165);
    PlayerTextDrawSetShadow(playerid, MiniGameFish[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, MiniGameFish[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, MiniGameFish[playerid][0], 255);
    PlayerTextDrawFont(playerid, MiniGameFish[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, MiniGameFish[playerid][0], 1);

    MiniGameFish[playerid][1] = CreatePlayerTextDraw(playerid, 228.000000, 185.000000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MiniGameFish[playerid][1], 17.000000, 120.000000);
    PlayerTextDrawAlignment(playerid, MiniGameFish[playerid][1], 1);
    PlayerTextDrawColor(playerid, MiniGameFish[playerid][1], 7935);
    PlayerTextDrawSetShadow(playerid, MiniGameFish[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, MiniGameFish[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, MiniGameFish[playerid][1], 255);
    PlayerTextDrawFont(playerid, MiniGameFish[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, MiniGameFish[playerid][1], 1);

    MiniGameFish[playerid][2] = CreatePlayerTextDraw(playerid, 228.000000, POSISI_AWAL, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MiniGameFish[playerid][2], 17.000000, -121.000000);
    PlayerTextDrawAlignment(playerid, MiniGameFish[playerid][2], 1);
    PlayerTextDrawColor(playerid, MiniGameFish[playerid][2], 512819199);
    PlayerTextDrawSetShadow(playerid, MiniGameFish[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, MiniGameFish[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, MiniGameFish[playerid][2], 255);
    PlayerTextDrawFont(playerid, MiniGameFish[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, MiniGameFish[playerid][2], 1);

    MiniGameFish[playerid][3] = CreatePlayerTextDraw(playerid, 228.000000, lokasitarget[playerid], "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MiniGameFish[playerid][3], 17.000000, 5.000000);
    PlayerTextDrawAlignment(playerid, MiniGameFish[playerid][3], 1);
    PlayerTextDrawColor(playerid, MiniGameFish[playerid][3], 16711935);
    PlayerTextDrawSetShadow(playerid, MiniGameFish[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, MiniGameFish[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, MiniGameFish[playerid][3], 255);
    PlayerTextDrawFont(playerid, MiniGameFish[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, MiniGameFish[playerid][3], 1);

    MiniGameFish[playerid][4] = CreatePlayerTextDraw(playerid, 269.000000, 281.000000, "LD_POOL:ball");
    PlayerTextDrawTextSize(playerid, MiniGameFish[playerid][4], 18.000000, 20.000000);
    PlayerTextDrawAlignment(playerid, MiniGameFish[playerid][4], 1);
    PlayerTextDrawColor(playerid, MiniGameFish[playerid][4], 512819199);
    PlayerTextDrawSetShadow(playerid, MiniGameFish[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, MiniGameFish[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, MiniGameFish[playerid][4], 255);
    PlayerTextDrawFont(playerid, MiniGameFish[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, MiniGameFish[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, MiniGameFish[playerid][4], 1);

    MiniGameFish[playerid][5] = CreatePlayerTextDraw(playerid, 274.000000, 283.000000, "H");
    PlayerTextDrawLetterSize(playerid, MiniGameFish[playerid][5], 0.000, 1.000);
    PlayerTextDrawAlignment(playerid, MiniGameFish[playerid][5], 1);
    PlayerTextDrawColor(playerid, MiniGameFish[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, MiniGameFish[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, MiniGameFish[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, MiniGameFish[playerid][5], 150);
    PlayerTextDrawFont(playerid, MiniGameFish[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, MiniGameFish[playerid][5], 1);

    MiniGameFish[playerid][6] = CreatePlayerTextDraw(playerid, 236.000000, 167.000000, HDFishbar);
    PlayerTextDrawLetterSize(playerid, MiniGameFish[playerid][6], 0.220, 1.099);
    PlayerTextDrawAlignment(playerid, MiniGameFish[playerid][6], 2);
    PlayerTextDrawColor(playerid, MiniGameFish[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, MiniGameFish[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, MiniGameFish[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, MiniGameFish[playerid][6], 150);
    PlayerTextDrawFont(playerid, MiniGameFish[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, MiniGameFish[playerid][6], 1);

	for(new i = 0; i < 7; i++) PlayerTextDrawShow(playerid, MiniGameFish[playerid][i]);
	SelectTextDraw(playerid, COLOR_BLUE);
	return 1;
}

forward MoveBarFishings(playerid);
public MoveBarFishings(playerid)
{
    if (DirectionBar[playerid])
    {
        MoveBar[playerid] = MoveBar[playerid] - SPEED_BAR;
        if (MoveBar[playerid] <= MAX_BAR)
        {
            DirectionBar[playerid] = false;
            MoveBar[playerid] = MAX_BAR;
        }
    }
    else
    {
		MoveBar[playerid] = MoveBar[playerid] + SPEED_BAR;
		if (MoveBar[playerid] >= MIN_BAR)
		{
		    DirectionBar[playerid] = true;
		    MoveBar[playerid] = MIN_BAR;
		}
	}
    
    // Mengatur posisi bar menggunakan TextDraw
    PlayerTextDrawTextSize(playerid, MiniGameFish[playerid][2], 17.000000, MoveBar[playerid]);
    PlayerTextDrawShow(playerid, MiniGameFish[playerid][2]);
    PlayerTextDrawShow(playerid, MiniGameFish[playerid][5]);
	//printf("[Bar] playerid :%d | PosY:%.2f | arah: %s", playerid, MoveBar[playerid], DirectionBar[playerid] ? "Naik" : "Turun");
}

JavaTR:StopBarFish(playerid)
{
    new Float:BarPosY = POSISI_AWALMAKER + MoveBar[playerid];
    //printf("DEBUG: MoveBar: %.2f | BarPosY: %.2f | Target: %.2f - %.2f", MoveBar[playerid], BarPosY, lokasitarget[playerid], lokasitarget[playerid] + TargetLebar);
    if (floatabs(BarPosY - lokasitarget[playerid]) <= TargetLebar)
    {
		if(CallbackLoading[playerid][0] != EOS)
		{
			CallLocalFunction(CallbackLoading[playerid], "d", playerid);
			printf("memanggil %s", CallbackLoading[playerid]);
		}
   	}
    else
    {
    	ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Aktivity gagal, karna garis titik tidak tepat"));
    }
	CallbackLoading[playerid][0] = EOS;
    KillTimer(TimersBar[playerid]);
    GamesBarShow[playerid] = 0;

	// Or
	for(new i = 0; i < 7; i++)
	{
		// i == 0  :: OK
		// i == 1  :: Error
		PlayerTextDrawDestroy(playerid, MiniGameFish[playerid][i]);
	}
	CancelSelectTextDraw(playerid);
	ClearAnimations(playerid, 0);
    StopLoopingAnim(playerid);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
    RemovePlayerAttachedObject(playerid, 9);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    return 1;
}

CMD:tes(playerid, params[])
{
	//manggilanya BarFish(playerid, "HDFishbar", "Callback");
    BarFish(playerid, "tes", "tes");
    return 1;
}

JavaTR:tes(playerid)
{
	SendClientMessage(playerid, -1, "Test tes");
	return 1;
}


hook OnClickDynPlayerTextDraw(playerid, PlayerText:textid)
{
    if(textid == MiniGameFish[playerid][4])
    {
    	if(GamesBarShow[playerid]) return StopBarFish(playerid);
    }
    return 1;
}