
#include <YSI\y_hooks>

new Text:FPSDISPLAY[6];
new PlayerText:FPSDISPLAYTD[MAX_PLAYERS][5];

hook OnGameModeInit()
{
	FPSDISPLAY[0] = TextDrawCreate(0.000000, -1.000000, "ld_dual:white");
	TextDrawFont(FPSDISPLAY[0], 4);
	TextDrawLetterSize(FPSDISPLAY[0], 0.600000, 2.000000);
	TextDrawTextSize(FPSDISPLAY[0], 235.500000, 16.500000);
	TextDrawSetOutline(FPSDISPLAY[0], 1);
	TextDrawSetShadow(FPSDISPLAY[0], 0);
	TextDrawAlignment(FPSDISPLAY[0], 1);
	TextDrawColor(FPSDISPLAY[0], 1351860735);
	TextDrawBackgroundColor(FPSDISPLAY[0], 255);
	TextDrawBoxColor(FPSDISPLAY[0], 50);
	TextDrawUseBox(FPSDISPLAY[0], 1);
	TextDrawSetProportional(FPSDISPLAY[0], 1);
	TextDrawSetSelectable(FPSDISPLAY[0], 0);

	FPSDISPLAY[1] = TextDrawCreate(0.500000, 1.000000, "ld_dual:white");
	TextDrawFont(FPSDISPLAY[1], 4);
	TextDrawLetterSize(FPSDISPLAY[1], 0.600000, 2.000000);
	TextDrawTextSize(FPSDISPLAY[1], 46.000000, 13.500000);
	TextDrawSetOutline(FPSDISPLAY[1], 1);
	TextDrawSetShadow(FPSDISPLAY[1], 0);
	TextDrawAlignment(FPSDISPLAY[1], 1);
	TextDrawColor(FPSDISPLAY[1], 573060351);
	TextDrawBackgroundColor(FPSDISPLAY[1], 255);
	TextDrawBoxColor(FPSDISPLAY[1], 50);
	TextDrawUseBox(FPSDISPLAY[1], 1);
	TextDrawSetProportional(FPSDISPLAY[1], 1);
	TextDrawSetSelectable(FPSDISPLAY[1], 0);

	FPSDISPLAY[2] = TextDrawCreate(47.500000, 1.000000, "ld_dual:white");
	TextDrawFont(FPSDISPLAY[2], 4);
	TextDrawLetterSize(FPSDISPLAY[2], 0.600000, 2.000000);
	TextDrawTextSize(FPSDISPLAY[2], 46.000000, 13.500000);
	TextDrawSetOutline(FPSDISPLAY[2], 1);
	TextDrawSetShadow(FPSDISPLAY[2], 0);
	TextDrawAlignment(FPSDISPLAY[2], 1);
	TextDrawColor(FPSDISPLAY[2], 573060351);
	TextDrawBackgroundColor(FPSDISPLAY[2], 255);
	TextDrawBoxColor(FPSDISPLAY[2], 50);
	TextDrawUseBox(FPSDISPLAY[2], 1);
	TextDrawSetProportional(FPSDISPLAY[2], 1);
	TextDrawSetSelectable(FPSDISPLAY[2], 0);

	FPSDISPLAY[3] = TextDrawCreate(94.500000, 1.000000, "ld_dual:white");
	TextDrawFont(FPSDISPLAY[3], 4);
	TextDrawLetterSize(FPSDISPLAY[3], 0.600000, 2.000000);
	TextDrawTextSize(FPSDISPLAY[3], 46.000000, 13.500000);
	TextDrawSetOutline(FPSDISPLAY[3], 1);
	TextDrawSetShadow(FPSDISPLAY[3], 0);
	TextDrawAlignment(FPSDISPLAY[3], 1);
	TextDrawColor(FPSDISPLAY[3], 573060351);
	TextDrawBackgroundColor(FPSDISPLAY[3], 255);
	TextDrawBoxColor(FPSDISPLAY[3], 50);
	TextDrawUseBox(FPSDISPLAY[3], 1);
	TextDrawSetProportional(FPSDISPLAY[3], 1);
	TextDrawSetSelectable(FPSDISPLAY[3], 0);

	FPSDISPLAY[4] = TextDrawCreate(141.500000, 1.000000, "ld_dual:white");
	TextDrawFont(FPSDISPLAY[4], 4);
	TextDrawLetterSize(FPSDISPLAY[4], 0.600000, 2.000000);
	TextDrawTextSize(FPSDISPLAY[4], 46.000000, 13.500000);
	TextDrawSetOutline(FPSDISPLAY[4], 1);
	TextDrawSetShadow(FPSDISPLAY[4], 0);
	TextDrawAlignment(FPSDISPLAY[4], 1);
	TextDrawColor(FPSDISPLAY[4], 573060351);
	TextDrawBackgroundColor(FPSDISPLAY[4], 255);
	TextDrawBoxColor(FPSDISPLAY[4], 50);
	TextDrawUseBox(FPSDISPLAY[4], 1);
	TextDrawSetProportional(FPSDISPLAY[4], 1);
	TextDrawSetSelectable(FPSDISPLAY[4], 0);

	FPSDISPLAY[5] = TextDrawCreate(188.500000, 1.000000, "ld_dual:white");
	TextDrawFont(FPSDISPLAY[5], 4);
	TextDrawLetterSize(FPSDISPLAY[5], 0.600000, 2.000000);
	TextDrawTextSize(FPSDISPLAY[5], 46.000000, 13.500000);
	TextDrawSetOutline(FPSDISPLAY[5], 1);
	TextDrawSetShadow(FPSDISPLAY[5], 0);
	TextDrawAlignment(FPSDISPLAY[5], 1);
	TextDrawColor(FPSDISPLAY[5], 573060351);
	TextDrawBackgroundColor(FPSDISPLAY[5], 255);
	TextDrawBoxColor(FPSDISPLAY[5], 50);
	TextDrawUseBox(FPSDISPLAY[5], 1);
	TextDrawSetProportional(FPSDISPLAY[5], 1);
	TextDrawSetSelectable(FPSDISPLAY[5], 0);

	return 1;
}

hook OnGameModeExit()
{
	TextDrawDestroy(FPSDISPLAY[0]);
	TextDrawDestroy(FPSDISPLAY[1]);
	TextDrawDestroy(FPSDISPLAY[2]);
	TextDrawDestroy(FPSDISPLAY[3]);
	TextDrawDestroy(FPSDISPLAY[4]);
	TextDrawDestroy(FPSDISPLAY[5]);
	return 1;
}

hook OnPlayerConnect(playerid)
{
	FPSDISPLAYTD[playerid][0] = CreatePlayerTextDraw(playerid, 22.000000, 3.000000, "FPS_:_75");
	PlayerTextDrawFont(playerid, FPSDISPLAYTD[playerid][0], 1);
	PlayerTextDrawLetterSize(playerid, FPSDISPLAYTD[playerid][0], 0.129162, 0.800000);
	PlayerTextDrawTextSize(playerid, FPSDISPLAYTD[playerid][0], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, FPSDISPLAYTD[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, FPSDISPLAYTD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, FPSDISPLAYTD[playerid][0], 2);
	PlayerTextDrawColor(playerid, FPSDISPLAYTD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, FPSDISPLAYTD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, FPSDISPLAYTD[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, FPSDISPLAYTD[playerid][0], 0);
	PlayerTextDrawSetProportional(playerid, FPSDISPLAYTD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, FPSDISPLAYTD[playerid][0], 0);

	FPSDISPLAYTD[playerid][1] = CreatePlayerTextDraw(playerid, 70.000000, 3.000000, "PING_:_31MS");
	PlayerTextDrawFont(playerid, FPSDISPLAYTD[playerid][1], 1);
	PlayerTextDrawLetterSize(playerid, FPSDISPLAYTD[playerid][1], 0.129162, 0.800000);
	PlayerTextDrawTextSize(playerid, FPSDISPLAYTD[playerid][1], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, FPSDISPLAYTD[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, FPSDISPLAYTD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, FPSDISPLAYTD[playerid][1], 2);
	PlayerTextDrawColor(playerid, FPSDISPLAYTD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, FPSDISPLAYTD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, FPSDISPLAYTD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, FPSDISPLAYTD[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, FPSDISPLAYTD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, FPSDISPLAYTD[playerid][1], 0);

	FPSDISPLAYTD[playerid][2] = CreatePlayerTextDraw(playerid, 117.000000, 3.000000, "PL_:_18%");
	PlayerTextDrawFont(playerid, FPSDISPLAYTD[playerid][2], 1);
	PlayerTextDrawLetterSize(playerid, FPSDISPLAYTD[playerid][2], 0.129162, 0.800000);
	PlayerTextDrawTextSize(playerid, FPSDISPLAYTD[playerid][2], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, FPSDISPLAYTD[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, FPSDISPLAYTD[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, FPSDISPLAYTD[playerid][2], 2);
	PlayerTextDrawColor(playerid, FPSDISPLAYTD[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, FPSDISPLAYTD[playerid][2], 255);
	PlayerTextDrawBoxColor(playerid, FPSDISPLAYTD[playerid][2], 50);
	PlayerTextDrawUseBox(playerid, FPSDISPLAYTD[playerid][2], 0);
	PlayerTextDrawSetProportional(playerid, FPSDISPLAYTD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, FPSDISPLAYTD[playerid][2], 0);

	FPSDISPLAYTD[playerid][3] = CreatePlayerTextDraw(playerid, 164.000000, 3.000000, "CPU:_38%");
	PlayerTextDrawFont(playerid, FPSDISPLAYTD[playerid][3], 1);
	PlayerTextDrawLetterSize(playerid, FPSDISPLAYTD[playerid][3], 0.129162, 0.800000);
	PlayerTextDrawTextSize(playerid, FPSDISPLAYTD[playerid][3], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, FPSDISPLAYTD[playerid][3], 0);
	PlayerTextDrawSetShadow(playerid, FPSDISPLAYTD[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, FPSDISPLAYTD[playerid][3], 2);
	PlayerTextDrawColor(playerid, FPSDISPLAYTD[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, FPSDISPLAYTD[playerid][3], 255);
	PlayerTextDrawBoxColor(playerid, FPSDISPLAYTD[playerid][3], 50);
	PlayerTextDrawUseBox(playerid, FPSDISPLAYTD[playerid][3], 0);
	PlayerTextDrawSetProportional(playerid, FPSDISPLAYTD[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, FPSDISPLAYTD[playerid][3], 0);

	FPSDISPLAYTD[playerid][4] = CreatePlayerTextDraw(playerid, 211.000000, 3.000000, "GPU:_66%");
	PlayerTextDrawFont(playerid, FPSDISPLAYTD[playerid][4], 1);
	PlayerTextDrawLetterSize(playerid, FPSDISPLAYTD[playerid][4], 0.129162, 0.800000);
	PlayerTextDrawTextSize(playerid, FPSDISPLAYTD[playerid][4], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, FPSDISPLAYTD[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, FPSDISPLAYTD[playerid][4], 0);
	PlayerTextDrawAlignment(playerid, FPSDISPLAYTD[playerid][4], 2);
	PlayerTextDrawColor(playerid, FPSDISPLAYTD[playerid][4], -1);
	PlayerTextDrawBackgroundColor(playerid, FPSDISPLAYTD[playerid][4], 255);
	PlayerTextDrawBoxColor(playerid, FPSDISPLAYTD[playerid][4], 50);
	PlayerTextDrawUseBox(playerid, FPSDISPLAYTD[playerid][4], 0);
	PlayerTextDrawSetProportional(playerid, FPSDISPLAYTD[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, FPSDISPLAYTD[playerid][4], 0);

	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	PlayerTextDrawDestroy(playerid, FPSDISPLAYTD[playerid][0]);
	PlayerTextDrawDestroy(playerid, FPSDISPLAYTD[playerid][1]);
	PlayerTextDrawDestroy(playerid, FPSDISPLAYTD[playerid][2]);
	PlayerTextDrawDestroy(playerid, FPSDISPLAYTD[playerid][3]);
	PlayerTextDrawDestroy(playerid, FPSDISPLAYTD[playerid][4]);
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	TextDrawShowForPlayer(playerid, FPSDISPLAY[0]);
	TextDrawShowForPlayer(playerid, FPSDISPLAY[1]);
	TextDrawShowForPlayer(playerid, FPSDISPLAY[2]);
	TextDrawShowForPlayer(playerid, FPSDISPLAY[3]);
	TextDrawShowForPlayer(playerid, FPSDISPLAY[4]);
	TextDrawShowForPlayer(playerid, FPSDISPLAY[5]);
	PlayerTextDrawShow(playerid, FPSDISPLAYTD[playerid][0]);
	PlayerTextDrawShow(playerid, FPSDISPLAYTD[playerid][1]);
	PlayerTextDrawShow(playerid, FPSDISPLAYTD[playerid][2]);
	PlayerTextDrawShow(playerid, FPSDISPLAYTD[playerid][3]);
	PlayerTextDrawShow(playerid, FPSDISPLAYTD[playerid][4]);

	return 1;
}

ptask UpdateFpsDisplay[1000](playerid)
{
	new Happ[256], cpuguz = random(101), gpuguz = random(101);
    format(Happ, sizeof(Happ), "FPS_:_%d", GetPlayerFPS(playerid));
    PlayerTextDrawSetString(playerid, FPSDISPLAYTD[playerid][0], Happ);

    format(Happ, sizeof(Happ), "PING_:_%dMS", GetPlayerPing(playerid));
    PlayerTextDrawSetString(playerid, FPSDISPLAYTD[playerid][1], Happ);

    format(Happ, sizeof(Happ), "PL_:_%.2f%", GetPlayerPacketLoss(playerid));
    PlayerTextDrawSetString(playerid, FPSDISPLAYTD[playerid][2], Happ);

    format(Happ, sizeof(Happ), "CPU_:_%d%", cpuguz);
    PlayerTextDrawSetString(playerid, FPSDISPLAYTD[playerid][3], Happ);

    format(Happ, sizeof(Happ), "GPU_:_%d%", gpuguz);
    PlayerTextDrawSetString(playerid, FPSDISPLAYTD[playerid][4], Happ);

    return 1;
}