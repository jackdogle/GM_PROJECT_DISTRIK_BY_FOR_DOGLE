#include <YSI\y_hooks>

new PlayerText: P_TOYS[MAX_PLAYERS][28];

CreateTDToys(playerid)
{
    P_TOYS[playerid][0] = CreatePlayerTextDraw(playerid, 67.000, 152.000, "X");
    PlayerTextDrawLetterSize(playerid, P_TOYS[playerid][0], 0.469, 2.099);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][0], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][0], 1);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][0], 1);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][0], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][0], 1);

    P_TOYS[playerid][1] = CreatePlayerTextDraw(playerid, 35.000, 174.000, "LD_BEAT:left");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][1], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][1], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][1], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][1], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][1], 1);

    P_TOYS[playerid][2] = CreatePlayerTextDraw(playerid, 78.000, 174.000, "LD_BEAT:right");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][2], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][2], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][2], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][2], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][2], 1);

    P_TOYS[playerid][3] = CreatePlayerTextDraw(playerid, 67.000, 212.000, "Y");
    PlayerTextDrawLetterSize(playerid, P_TOYS[playerid][3], 0.469, 2.099);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][3], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][3], 1);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][3], 1);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][3], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][3], 1);

    P_TOYS[playerid][4] = CreatePlayerTextDraw(playerid, 35.000, 234.000, "LD_BEAT:left");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][4], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][4], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][4], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][4], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][4], 1);

    P_TOYS[playerid][5] = CreatePlayerTextDraw(playerid, 78.000, 234.000, "LD_BEAT:right");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][5], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][5], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][5], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][5], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][5], 1);

    P_TOYS[playerid][6] = CreatePlayerTextDraw(playerid, 67.000, 275.000, "Z");
    PlayerTextDrawLetterSize(playerid, P_TOYS[playerid][6], 0.469, 2.099);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][6], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][6], 1);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][6], 1);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][6], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][6], 1);

    P_TOYS[playerid][7] = CreatePlayerTextDraw(playerid, 35.000, 297.000, "LD_BEAT:left");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][7], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][7], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][7], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][7], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][7], 1);

    P_TOYS[playerid][8] = CreatePlayerTextDraw(playerid, 78.000, 297.000, "LD_BEAT:right");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][8], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][8], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][8], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][8], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][8], 1);

    P_TOYS[playerid][9] = CreatePlayerTextDraw(playerid, 157.000, 152.000, "RX");
    PlayerTextDrawLetterSize(playerid, P_TOYS[playerid][9], 0.469, 2.099);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][9], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][9], 1);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][9], 1);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][9], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][9], 1);

    P_TOYS[playerid][10] = CreatePlayerTextDraw(playerid, 130.000, 174.000, "LD_BEAT:left");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][10], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][10], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][10], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][10], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][10], 1);

    P_TOYS[playerid][11] = CreatePlayerTextDraw(playerid, 173.000, 174.000, "LD_BEAT:right");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][11], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][11], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][11], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][11], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][11], 1);

    P_TOYS[playerid][12] = CreatePlayerTextDraw(playerid, 158.000, 212.000, "RY");
    PlayerTextDrawLetterSize(playerid, P_TOYS[playerid][12], 0.469, 2.099);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][12], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][12], 1);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][12], 1);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][12], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][12], 1);

    P_TOYS[playerid][13] = CreatePlayerTextDraw(playerid, 130.000, 234.000, "LD_BEAT:left");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][13], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][13], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][13], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][13], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][13], 1);

    P_TOYS[playerid][14] = CreatePlayerTextDraw(playerid, 173.000, 234.000, "LD_BEAT:right");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][14], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][14], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][14], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][14], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][14], 1);

    P_TOYS[playerid][15] = CreatePlayerTextDraw(playerid, 156.000, 275.000, "RZ");
    PlayerTextDrawLetterSize(playerid, P_TOYS[playerid][15], 0.469, 2.099);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][15], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][15], 1);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][15], 1);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][15], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][15], 1);

    P_TOYS[playerid][16] = CreatePlayerTextDraw(playerid, 130.000, 297.000, "LD_BEAT:left");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][16], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][16], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][16], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][16], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][16], 1);

    P_TOYS[playerid][17] = CreatePlayerTextDraw(playerid, 173.000, 297.000, "LD_BEAT:right");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][17], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][17], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][17], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][17], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][17], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][17], 1);

    P_TOYS[playerid][18] = CreatePlayerTextDraw(playerid, 252.000, 152.000, "SX");
    PlayerTextDrawLetterSize(playerid, P_TOYS[playerid][18], 0.469, 2.099);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][18], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][18], -1);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][18], 1);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][18], 1);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][18], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][18], 1);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][18], 1);

    P_TOYS[playerid][19] = CreatePlayerTextDraw(playerid, 225.000, 174.000, "LD_BEAT:left");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][19], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][19], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][19], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][19], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][19], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][19], 1);

    P_TOYS[playerid][20] = CreatePlayerTextDraw(playerid, 268.000, 174.000, "LD_BEAT:right");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][20], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][20], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][20], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][20], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][20], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][20], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][20], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][20], 1);

    P_TOYS[playerid][21] = CreatePlayerTextDraw(playerid, 251.000, 212.000, "SY");
    PlayerTextDrawLetterSize(playerid, P_TOYS[playerid][21], 0.469, 2.099);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][21], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][21], -1);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][21], 1);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][21], 1);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][21], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][21], 1);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][21], 1);

    P_TOYS[playerid][22] = CreatePlayerTextDraw(playerid, 225.000, 234.000, "LD_BEAT:left");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][22], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][22], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][22], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][22], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][22], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][22], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][22], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][22], 1);

    P_TOYS[playerid][23] = CreatePlayerTextDraw(playerid, 268.000, 234.000, "LD_BEAT:right");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][23], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][23], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][23], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][23], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][23], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][23], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][23], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][23], 1);

    P_TOYS[playerid][24] = CreatePlayerTextDraw(playerid, 250.000, 275.000, "SZ");
    PlayerTextDrawLetterSize(playerid, P_TOYS[playerid][24], 0.479, 2.099);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][24], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][24], -1);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][24], 1);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][24], 1);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][24], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][24], 1);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][24], 1);

    P_TOYS[playerid][25] = CreatePlayerTextDraw(playerid, 225.000, 297.000, "LD_BEAT:left");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][25], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][25], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][25], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][25], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][25], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][25], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][25], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][25], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][25], 1);

    P_TOYS[playerid][26] = CreatePlayerTextDraw(playerid, 268.000, 297.000, "LD_BEAT:right");
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][26], 28.000, 28.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][26], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][26], -2686721);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][26], 0);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][26], 0);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][26], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][26], 4);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][26], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][26], 1);

    P_TOYS[playerid][27] = CreatePlayerTextDraw(playerid, 236.000, 350.000, "SIMPAN");
    PlayerTextDrawLetterSize(playerid, P_TOYS[playerid][27], 0.359, 2.099);
    PlayerTextDrawTextSize(playerid, P_TOYS[playerid][27], 308.000, 10.000);
    PlayerTextDrawAlignment(playerid, P_TOYS[playerid][27], 1);
    PlayerTextDrawColor(playerid, P_TOYS[playerid][27], -1);
    PlayerTextDrawUseBox(playerid, P_TOYS[playerid][27], 1);
    PlayerTextDrawBoxColor(playerid, P_TOYS[playerid][27], 0);
    PlayerTextDrawSetShadow(playerid, P_TOYS[playerid][27], 1);
    PlayerTextDrawSetOutline(playerid, P_TOYS[playerid][27], 1);
    PlayerTextDrawBackgroundColor(playerid, P_TOYS[playerid][27], 255);
    PlayerTextDrawFont(playerid, P_TOYS[playerid][27], 1);
    PlayerTextDrawSetProportional(playerid, P_TOYS[playerid][27], 1);
    PlayerTextDrawSetSelectable(playerid, P_TOYS[playerid][27], 1);
}

hook OnPlayerConnect(playerid)
{
	CreateTDToys(playerid);
	return 1;
}

ShowTDToys(playerid)
{
	for(new txd; txd < 28; txd ++)
	{
		PlayerTextDrawShow(playerid, P_TOYS[playerid][txd]);
	}
	SelectTextDraw(playerid, ARWIN);
	Info(playerid, "Gunakan "VERONA"'/cursor'"WHITE" jika cursor menghilang / textdraw tidak dapat ditekan");
	return 1;
}

HideTDToys(playerid)
{
	for(new txd; txd < 28; txd ++)
	{
		PlayerTextDrawHide(playerid, P_TOYS[playerid][txd]);
	}
	CancelSelectTextDraw(playerid);
	return 1;
}
