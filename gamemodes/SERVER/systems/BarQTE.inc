#define BAR_MIN 280     // Posisi minimum bar
#define BAR_MAX 380    	// Posisi maksimum bar
#define TARGET_POS 50  	// Posisi target untuk menang
#define TOLERANCE 5    	// Toleransi untuk menganggap pemain berhasil
#define BAR_SPEED 5 	// kecepatan bar
#define	MAX_CALLBACK 34
#define MAX_LEVEL 3
#define COOLDOWN_MS 30000
#define LebarTarget 4

new bool:BarDirection[MAX_PLAYERS];   // Arah pergerakan bar (true = maju, false = mundur)
new showBarGames[MAX_PLAYERS];
new Float:BarPosition[MAX_PLAYERS];   // Posisi bar saat ini untuk setiap pemain
new Float:BarMove[MAX_PLAYERS];   // Posisi bar saat ini untuk setiap pemain
new BarTimer[MAX_PLAYERS];      // Timer untuk menggerakkan bar
new g_QTELevel[MAX_PLAYERS];
new g_QTECooldown[MAX_PLAYERS];
new g_QTEPoliceNotify[MAX_PLAYERS];

new Float:targetlokasi[MAX_PLAYERS];
new PlayerText:PlayerTD[MAX_PLAYERS][4];

new LoadingCallback[MAX_PLAYERS][MAX_CALLBACK];


stock IsValidBarQTE(playerid)
	return showBarGames[playerid];

//manggilanya BarQTE(playerid, "HDevinteks", "Callback");

stock BarQTE(playerid, const HDevinteks[] = "_",const callback[] = "")
{
	if(showBarGames[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Bar Sedang aktif"));
	if(g_QTECooldown[playerid] > GetTickCount())
	{
		new id = g_PlayerRobbery[playerid];
		if(id == -1) return 1;

		g_QTELevel[playerid] = 1;
		DurringRobbery[playerid] = false;
		g_BerankasCode[id] = 0;
		//UpdateRobberyTextLabel(id);
		RemovePlayerAttachedObject(playerid, 0);
		ClearAnimations(playerid, 0);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		new wait = (g_QTECooldown[playerid] - GetTickCount())/1000;
		return Info(playerid, "Tunggu %d detik sebelum mencoba lagi!", wait);
	}
	g_QTELevel[playerid] = 1;
	BarPosition[playerid] = 0.0;
    BarDirection[playerid] = true;
    showBarGames[playerid] = 1;
    if(callback[0] != EOS)
	{
		format(LoadingCallback[playerid], MAX_CALLBACK, "%s", callback);
	}
    CreateBar(playerid, HDevinteks);
    return 1;
}

JavaTR: CreateBar(playerid, const HDevinteks[])
{    
    BarMove[playerid] = BAR_MIN, BarTimer[playerid] = SetTimerEx("MoveBarV3", 100, true, "i", playerid);   
	targetlokasi[playerid] = RandomEx(BAR_MIN , BAR_MAX - LebarTarget); 
	    
	PlayerTD[playerid][0] = CreatePlayerTextDraw(playerid, 330.000000, 341.000000, "_");
	PlayerTextDrawFont(playerid, PlayerTD[playerid][0], 1);
	PlayerTextDrawLetterSize(playerid, PlayerTD[playerid][0], 0.500000, 1.500000);
	PlayerTextDrawTextSize(playerid, PlayerTD[playerid][0], 160.000000, 100.000000);
	PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, PlayerTD[playerid][0], 2);
	PlayerTextDrawColor(playerid, PlayerTD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, PlayerTD[playerid][0], 505428735);
	PlayerTextDrawUseBox(playerid, PlayerTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerTD[playerid][0], 0);

	PlayerTD[playerid][1] = CreatePlayerTextDraw(playerid, BAR_MIN, 342.000000, "_");// geser
	PlayerTextDrawFont(playerid, PlayerTD[playerid][1], 1);
	PlayerTextDrawLetterSize(playerid, PlayerTD[playerid][1], 1.000000, 1.297999);
	PlayerTextDrawTextSize(playerid, PlayerTD[playerid][1], 380.000000, 89.000000);
	PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, PlayerTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, PlayerTD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][1], 12582911);
	PlayerTextDrawBoxColor(playerid, PlayerTD[playerid][1], 12582911);
	PlayerTextDrawUseBox(playerid, PlayerTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerTD[playerid][1], 0);

	PlayerTD[playerid][2] = CreatePlayerTextDraw(playerid, 311.000, 343.000, HDevinteks);
	PlayerTextDrawLetterSize(playerid, PlayerTD[playerid][2], 0.200, 0.799);
	PlayerTextDrawAlignment(playerid, PlayerTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, PlayerTD[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][2], 150);
	PlayerTextDrawFont(playerid, PlayerTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerTD[playerid][2], 0);

	PlayerTD[playerid][3] = CreatePlayerTextDraw(playerid, targetlokasi[playerid], 341.000000, "_"); // target
	PlayerTextDrawFont(playerid, PlayerTD[playerid][3], 1);
	PlayerTextDrawLetterSize(playerid, PlayerTD[playerid][3], 0.536000, 1.500000);
	PlayerTextDrawTextSize(playerid, PlayerTD[playerid][3], targetlokasi[playerid] + LebarTarget, 70.000000);
	PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, PlayerTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, PlayerTD[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][3], 255);
	PlayerTextDrawBoxColor(playerid, PlayerTD[playerid][3], -1448498689);
	PlayerTextDrawUseBox(playerid, PlayerTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerTD[playerid][3], 0);

	for(new i = 0; i < 4; i++) PlayerTextDrawShow(playerid, PlayerTD[playerid][i]);
    Info(playerid, "Gunakan Otot "YELLOW"H "WHITE"Untuk memainkan minigame");

	return 1;
}

JavaTR: MoveBarV3(playerid)
{
	if(!showBarGames[playerid]) return 0;

	new speed;
    switch(g_QTELevel[playerid])
	{
		case 1:
        {
            speed = 5;
        }
        case 2:
        {
            speed = 7;
        }
        case 3:
        {
            speed = 9;
        }
	}
	if(!BarDirection[playerid])
	{
		BarMove[playerid] = BarMove[playerid] - speed;
		if(BarMove[playerid] <= BAR_MIN)
		{
			BarDirection[playerid] = true;
			BarMove[playerid] = BAR_MIN;
		}
	}
	else
	{
		BarMove[playerid] = BarMove[playerid] + speed;
		if(BarMove[playerid] >= BAR_MAX)
		{
			BarDirection[playerid] = false;
			BarMove[playerid] = BAR_MAX;
		}
	}
    
    // Mengatur posisi bar menggunakan TextDraw
    PlayerTextDrawTextSize(playerid, PlayerTD[playerid][1], BarMove[playerid], 71.000000);
    PlayerTextDrawShow(playerid, PlayerTD[playerid][1]);
    return 1;
}

stock StopBar(playerid, bool:success)
{
	new id = g_PlayerRobbery[playerid];
	if(id == -1) return 1;

	showBarGames[playerid] = 0;
	KillTimer(BarTimer[playerid]);
	for(new i = 0; i < 4; i++)
	{
		PlayerTextDrawDestroy(playerid, PlayerTD[playerid][i]);
	}
	RemovePlayerAttachedObject(playerid, 0);
	ClearAnimations(playerid, 0);
    StopLoopingAnim(playerid);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	DurringRobbery[playerid] = false;
	g_BerankasCode[id] = 0;
	//UpdateRobberyTextLabel(id);

	if(success)
	{
		Info(playerid, "Anda berhasil menyelesaikan semua tahap!");
		if(LoadingCallback[playerid][0] != EOS)
		{
			CallLocalFunction(LoadingCallback[playerid], "d", playerid);
			printf("memanggil %s", LoadingCallback[playerid]);
		}
	}
    else
    {
    	ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Aktivity gagal, karna garis titik tidak tepat"));
		g_QTECooldown[playerid] = GetTickCount() + COOLDOWN_MS;
		g_QTEPoliceNotify[playerid] = 1;
		g_QTELevel[playerid] = 1;
		DurringRobbery[playerid] = false;
		g_BerankasCode[id] = 0;
		//UpdateRobberyTextLabel(id);
    }
	LoadingCallback[playerid][0] = EOS;
    return 1;
}

CMD:pesan(playerid, params[])
{
	//manggilanya BarQTE(playerid, "HDevinteks", "Callback");
    BarQTE(playerid, "pesan", "Pesan");
    return 1;
}

JavaTR:Pesan(playerid)
{
	SendClientMessage(playerid, -1, "Test Pesan");
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	//printf("KeyChange: playerid=%d, newkeys=%d, oldkeys=%d", playerid, newkeys, oldkeys);
    if (newkeys & KEY_CTRL_BACK) 
    {
    	if(!showBarGames[playerid]) return 0;
		if(floatabs(BarMove[playerid] - targetlokasi[playerid]) <= LebarTarget)
		{
			g_QTELevel[playerid]++;
			if(g_QTELevel[playerid] > MAX_LEVEL)
			{
				StopBar(playerid, true);
			}
			else
			{ 
				UpdateBarTarget(playerid);
				Info(playerid, "Anda berhasil melewati tahap %d, lanjut ke tahap berikutnya!", g_QTELevel[playerid]);
			}
		}
		else
		{
			StopBar(playerid, false);
		}
    }
    return 1;
}

stock UpdateBarTarget(playerid)
{
	PlayerTextDrawDestroy(playerid, PlayerTD[playerid][3]);

	targetlokasi[playerid] = RandomEx(BAR_MIN , BAR_MAX - LebarTarget); 

	PlayerTD[playerid][3] = CreatePlayerTextDraw(playerid, targetlokasi[playerid], 341.000000, "_"); // target
	PlayerTextDrawFont(playerid, PlayerTD[playerid][3], 1);
	PlayerTextDrawLetterSize(playerid, PlayerTD[playerid][3], 0.536000, 1.500000);
	PlayerTextDrawTextSize(playerid, PlayerTD[playerid][3], targetlokasi[playerid] + LebarTarget, 70.000000);
	PlayerTextDrawSetOutline(playerid, PlayerTD[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, PlayerTD[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, PlayerTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, PlayerTD[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, PlayerTD[playerid][3], 255);
	PlayerTextDrawBoxColor(playerid, PlayerTD[playerid][3], -1448498689);
	PlayerTextDrawUseBox(playerid, PlayerTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, PlayerTD[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerTD[playerid][3], 0);
	PlayerTextDrawShow(playerid, PlayerTD[playerid][3]);
	return 1;
}
				