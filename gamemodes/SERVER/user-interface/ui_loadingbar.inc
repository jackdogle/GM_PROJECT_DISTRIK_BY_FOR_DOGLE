#if defined _loadingbar_included
  #endinput
#endif
#define _loadingbar_included

#define			 MAX_CALLBACK_STR			34

static  PlayerText:LoadingBar[MAX_PLAYERS][8],
        LoadingTimer[MAX_PLAYERS],
        LoadingValue[MAX_PLAYERS],
        LoadingMaxValue[MAX_PLAYERS],
        bool:IsLoading[MAX_PLAYERS],
		LoadingCallback[MAX_PLAYERS][MAX_CALLBACK_STR];

forward OnLoadingBarFinished(playerid);
forward OnLoadingBarProgress(playerid, value);

Remove_BarLoading(playerid)
{
	AccountData[playerid][pProgress] = 0; 
	for(new i = 0; i < 8; i++)
	{
		PlayerTextDrawDestroy(playerid, LoadingBar[playerid][i]);
	}
	LoadingValue[playerid] = 0;
	LoadingMaxValue[playerid] = 0;
	IsLoading[playerid] = false;
	LoadingCallback[playerid][0] = EOS;
	return 1;
}

static Loading_BarUpdate(playerid)
{
	new str[64];
	format(str, sizeof(str), "%d%%", LoadingValue[playerid]);
	PlayerTextDrawTextSize(playerid, LoadingBar[playerid][7], LoadingValue[playerid] * 105 / LoadingMaxValue[playerid], 12.000);
	PlayerTextDrawShow(playerid, LoadingBar[playerid][7]);
	PlayerTextDrawSetString(playerid, LoadingBar[playerid][5], str);
	PlayerTextDrawShow(playerid, LoadingBar[playerid][5]);
}

forward Loading_TimerUpdate2(playerid);
public Loading_TimerUpdate2(playerid)
{
	if(!IsValidLoadingBar(playerid))
		return 0;

	if(LoadingValue[playerid] < LoadingMaxValue[playerid])
	{
		LoadingValue[playerid]++;
		Loading_BarUpdate(playerid);
        CallLocalFunction(#OnLoadingBarProgress, "dd", playerid, LoadingValue[playerid]);
	}
	else
	{
        CallLocalFunction(#OnLoadingBarFinished, "d", playerid);
		StopPlayerLoadingBar(playerid);	
	}
	return 1;
}

/* Used Functions */

stock IsValidLoadingBar(playerid)
	return IsLoading[playerid];

stock ShowProgressbar(playerid, const text[] = "_", Times)
{
	if(IsValidLoadingBar(playerid))
		StopPlayerLoadingBar(playerid);

	LoadingBar[playerid][0] = CreatePlayerTextDraw(playerid, 268.000, 399.000, "LD_BUM:blkdot");
	PlayerTextDrawTextSize(playerid, LoadingBar[playerid][0], 110.000, 1.000);
	PlayerTextDrawAlignment(playerid, LoadingBar[playerid][0], 1);
	PlayerTextDrawColor(playerid, LoadingBar[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, LoadingBar[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, LoadingBar[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, LoadingBar[playerid][0], 255);
	PlayerTextDrawFont(playerid, LoadingBar[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, LoadingBar[playerid][0], 1);

	LoadingBar[playerid][1] = CreatePlayerTextDraw(playerid, 268.000, 417.000, "LD_BUM:blkdot");
	PlayerTextDrawTextSize(playerid, LoadingBar[playerid][1], 110.000, 1.000);
	PlayerTextDrawAlignment(playerid, LoadingBar[playerid][1], 1);
	PlayerTextDrawColor(playerid, LoadingBar[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, LoadingBar[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, LoadingBar[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, LoadingBar[playerid][1], 255);
	PlayerTextDrawFont(playerid, LoadingBar[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, LoadingBar[playerid][1], 1);

	LoadingBar[playerid][2] = CreatePlayerTextDraw(playerid, 268.000, 418.000, "LD_BUM:blkdot");
	PlayerTextDrawTextSize(playerid, LoadingBar[playerid][2], 1.000, -19.000);
	PlayerTextDrawAlignment(playerid, LoadingBar[playerid][2], 1);
	PlayerTextDrawColor(playerid, LoadingBar[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, LoadingBar[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, LoadingBar[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, LoadingBar[playerid][2], 255);
	PlayerTextDrawFont(playerid, LoadingBar[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, LoadingBar[playerid][2], 1);

	LoadingBar[playerid][3] = CreatePlayerTextDraw(playerid, 378.000, 418.000, "LD_BUM:blkdot");
	PlayerTextDrawTextSize(playerid, LoadingBar[playerid][3], 1.000, -19.000);
	PlayerTextDrawAlignment(playerid, LoadingBar[playerid][3], 1);
	PlayerTextDrawColor(playerid, LoadingBar[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, LoadingBar[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, LoadingBar[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, LoadingBar[playerid][3], 255);
	PlayerTextDrawFont(playerid, LoadingBar[playerid][3], 4);
	PlayerTextDrawSetProportional(playerid, LoadingBar[playerid][3], 1);

	LoadingBar[playerid][4] = CreatePlayerTextDraw(playerid, 269.000, 390.000, "EATING");
	PlayerTextDrawLetterSize(playerid, LoadingBar[playerid][4], 0.148, 0.797);
	PlayerTextDrawAlignment(playerid, LoadingBar[playerid][4], 1);
	PlayerTextDrawColor(playerid, LoadingBar[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, LoadingBar[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, LoadingBar[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, LoadingBar[playerid][4], 150);
	PlayerTextDrawFont(playerid, LoadingBar[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, LoadingBar[playerid][4], 1);

	LoadingBar[playerid][5] = CreatePlayerTextDraw(playerid, 365.000, 390.000, "100");
	PlayerTextDrawLetterSize(playerid, LoadingBar[playerid][5], 0.148, 0.797);
	PlayerTextDrawAlignment(playerid, LoadingBar[playerid][5], 1);
	PlayerTextDrawColor(playerid, LoadingBar[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, LoadingBar[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, LoadingBar[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, LoadingBar[playerid][5], 150);
	PlayerTextDrawFont(playerid, LoadingBar[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, LoadingBar[playerid][5], 1);

	LoadingBar[playerid][6] = CreatePlayerTextDraw(playerid, 271.000, 402.000, "LD_BUM:blkdot");
	PlayerTextDrawTextSize(playerid, LoadingBar[playerid][6], 105.000, 12.000);
	PlayerTextDrawAlignment(playerid, LoadingBar[playerid][6], 1);
	PlayerTextDrawColor(playerid, LoadingBar[playerid][6], 606879231);
	PlayerTextDrawSetShadow(playerid, LoadingBar[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, LoadingBar[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, LoadingBar[playerid][6], 255);
	PlayerTextDrawFont(playerid, LoadingBar[playerid][6], 4);
	PlayerTextDrawSetProportional(playerid, LoadingBar[playerid][6], 1);

	LoadingBar[playerid][7] = CreatePlayerTextDraw(playerid, 271.000, 402.000, "LD_BUM:blkdot");
	PlayerTextDrawTextSize(playerid, LoadingBar[playerid][7], 0.000, 12.000);
	PlayerTextDrawAlignment(playerid, LoadingBar[playerid][7], 1);
	PlayerTextDrawColor(playerid, LoadingBar[playerid][7], SERVER_TEXTDRAW_COLOR);
	PlayerTextDrawSetShadow(playerid, LoadingBar[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, LoadingBar[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, LoadingBar[playerid][7], 255);
	PlayerTextDrawFont(playerid, LoadingBar[playerid][7], 4);
	PlayerTextDrawSetProportional(playerid, LoadingBar[playerid][7], 1);

	PlayerTextDrawSetString(playerid, LoadingBar[playerid][4], text);

	for(new i = 0; i < 8; i++)
	{
		PlayerTextDrawShow(playerid, LoadingBar[playerid][i]);
	}
	new Timer = Times*1000/100;
	LoadingValue[playerid] = 0;
	IsLoading[playerid] = true;
	AccountData[playerid][pProgress] = 1;
	LoadingMaxValue[playerid] = 100;
	LoadingTimer[playerid] = SetTimerEx(#Loading_TimerUpdate2, Timer, true, "d", playerid);
	return 1;
}

stock StopPlayerLoadingBar(playerid)
{
	AccountData[playerid][pProgress] = 0;
    KillTimer(LoadingTimer[playerid]);
    Remove_BarLoading(playerid);	
}

CMD:prg(playerid, params[])
{
	ShowProgressbar(playerid, "OPENING_BOX", 5);	
	return 1;
}