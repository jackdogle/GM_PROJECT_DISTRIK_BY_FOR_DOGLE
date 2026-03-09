enum eStuffBox
{
	BoxMessage1[320],
	BoxMessage2[320],
	BoxModel,
	BoxSize
}
new InfoBox[MAX_PLAYERS][4][eStuffBox];
new MaxPlayerBox[MAX_PLAYERS];
new PlayerText: TextDrawBox[MAX_PLAYERS][4*7];
new IndexBox[MAX_PLAYERS];

VRRP::HiddenBox(playerid)
{
	if(!IndexBox[playerid]) return 1;
	--IndexBox[playerid];
	MaxPlayerBox[playerid]--;
	for(new i=-1; ++i<7;) PlayerTextDrawDestroy(playerid, TextDrawBox[playerid][(IndexBox[playerid]*7)+i]);

	return 1;
}

ShowItemBox(playerid, pesan1[], pesan2[], model)
{
	ShowingBox(playerid, pesan1, pesan2, model);
	return 1;
}

stock ShowingBox(playerid, string:message[], string:message2[], model)
{
	if(MaxPlayerBox[playerid] == 4) return 1;
	MaxPlayerBox[playerid]++;
	for(new x=-1;++x<IndexBox[playerid];)
	{
		for(new i=-1;++i<7;) PlayerTextDrawDestroy(playerid, TextDrawBox[playerid][(x*7) + i]);
		InfoBox[playerid][IndexBox[playerid]-x] = InfoBox[playerid][(IndexBox[playerid]-x)-1];
	}
	format(InfoBox[playerid][0][BoxMessage1], 320, "%s", message);
	format(InfoBox[playerid][0][BoxMessage2], 320, "%s", message2);
	InfoBox[playerid][0][BoxModel] = model;
	InfoBox[playerid][0][BoxSize] = 3;

	++IndexBox[playerid];
	new Float:new_x=0.0;
	for(new x=-1;++x<IndexBox[playerid];)
	{
		CreateBox(playerid, x, x * 7, new_x);
		new_x += (InfoBox[playerid][x][BoxSize]*7.25)+35.0;
	}
	SetTimerEx("HiddenBox", 7000, false, "i", playerid);
	return 1;
}

stock CreateBox(const playerid, index, i, const Float:new_x)
{
	new lines = InfoBox[playerid][index][BoxSize];
	new Float:x = (lines * 7) + new_x;
	new Float:posisibaru = x-30.0;

	PlayerPlaySound(playerid, 1150, 0, 0, 0);
    TextDrawBox[playerid][i] = CreatePlayerTextDraw(playerid, 343.000+posisibaru, 327.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, TextDrawBox[playerid][i], 48.000, 60.000);
    PlayerTextDrawAlignment(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawColor(playerid, TextDrawBox[playerid][i], 512819004);
    PlayerTextDrawSetShadow(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawSetOutline(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawBackgroundColor(playerid, TextDrawBox[playerid][i], 255);
    PlayerTextDrawFont(playerid, TextDrawBox[playerid][i], 4);
    PlayerTextDrawSetProportional(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawShow(playerid, TextDrawBox[playerid][i]);

    TextDrawBox[playerid][++i] = CreatePlayerTextDraw(playerid, 341.000+posisibaru, 375.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, TextDrawBox[playerid][i], 12.000, 14.000);
    PlayerTextDrawAlignment(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawColor(playerid, TextDrawBox[playerid][i], 512819199);
    PlayerTextDrawSetShadow(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawSetOutline(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawBackgroundColor(playerid, TextDrawBox[playerid][i], 255);
    PlayerTextDrawFont(playerid, TextDrawBox[playerid][i], 4);
    PlayerTextDrawSetProportional(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawShow(playerid, TextDrawBox[playerid][i]);

    TextDrawBox[playerid][++i] = CreatePlayerTextDraw(playerid, 381.000+posisibaru, 375.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, TextDrawBox[playerid][i], 12.000, 14.000);
    PlayerTextDrawAlignment(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawColor(playerid, TextDrawBox[playerid][i], 512819199);
    PlayerTextDrawSetShadow(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawSetOutline(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawBackgroundColor(playerid, TextDrawBox[playerid][i], 255);
    PlayerTextDrawFont(playerid, TextDrawBox[playerid][i], 4);
    PlayerTextDrawSetProportional(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawShow(playerid, TextDrawBox[playerid][i]);

    TextDrawBox[playerid][++i] = CreatePlayerTextDraw(playerid, 348.000+posisibaru, 377.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, TextDrawBox[playerid][i], 40.000, 9.500);
    PlayerTextDrawAlignment(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawColor(playerid, TextDrawBox[playerid][i], 512819199);
    PlayerTextDrawSetShadow(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawSetOutline(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawBackgroundColor(playerid, TextDrawBox[playerid][i], 255);
    PlayerTextDrawFont(playerid, TextDrawBox[playerid][i], 4);
    PlayerTextDrawSetProportional(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawShow(playerid, TextDrawBox[playerid][i]);

    TextDrawBox[playerid][++i] = CreatePlayerTextDraw(playerid, 345.000+posisibaru, 334.000, "_");
    PlayerTextDrawTextSize(playerid, TextDrawBox[playerid][i], 43.000, 40.000);
    PlayerTextDrawAlignment(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawColor(playerid, TextDrawBox[playerid][i], -1);
    PlayerTextDrawSetShadow(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawSetOutline(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawBackgroundColor(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawFont(playerid, TextDrawBox[playerid][i], 5);
    PlayerTextDrawSetProportional(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawSetPreviewModel(playerid, TextDrawBox[playerid][i], InfoBox[playerid][index][BoxModel]);
    PlayerTextDrawSetPreviewRot(playerid, TextDrawBox[playerid][i], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, TextDrawBox[playerid][i], 0, 0);
    PlayerTextDrawShow(playerid, TextDrawBox[playerid][i]);

    TextDrawBox[playerid][++i] = CreatePlayerTextDraw(playerid, 345.000+posisibaru, 328.000, InfoBox[playerid][index][BoxMessage1]);
    PlayerTextDrawLetterSize(playerid, TextDrawBox[playerid][i], 0.129, 0.698);
    PlayerTextDrawAlignment(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawColor(playerid, TextDrawBox[playerid][i], -1);
    PlayerTextDrawSetShadow(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawSetOutline(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawBackgroundColor(playerid, TextDrawBox[playerid][i], 150);
    PlayerTextDrawFont(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawSetProportional(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawShow(playerid, TextDrawBox[playerid][i]);

    TextDrawBox[playerid][++i] = CreatePlayerTextDraw(playerid, 367.000+posisibaru, 377.000, InfoBox[playerid][index][BoxMessage2]);
    PlayerTextDrawLetterSize(playerid, TextDrawBox[playerid][i], 0.160, 0.899);
    PlayerTextDrawAlignment(playerid, TextDrawBox[playerid][i], 2);
    PlayerTextDrawColor(playerid, TextDrawBox[playerid][i], -1);
    PlayerTextDrawSetShadow(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawSetOutline(playerid, TextDrawBox[playerid][i], 0);
    PlayerTextDrawBackgroundColor(playerid, TextDrawBox[playerid][i], 150);
    PlayerTextDrawFont(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawSetProportional(playerid, TextDrawBox[playerid][i], 1);
    PlayerTextDrawShow(playerid, TextDrawBox[playerid][i]);

	return 1;
}