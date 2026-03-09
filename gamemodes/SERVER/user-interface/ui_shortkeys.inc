#include <YSI\y_hooks>

CreateTDShortKey(playerid)
{
    PlayerTextdraws[playerid][textdraw_interaksi][0] = CreatePlayerTextDraw(playerid, 277.000, 343.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], 74.000, 15.000);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], 1);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], 10495);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], 255);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], 4);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0], 1);

    PlayerTextdraws[playerid][textdraw_interaksi][1] = CreatePlayerTextDraw(playerid, 278.000, 344.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], 72.000, 13.000);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], 1);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], 512819199);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], 255);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], 4);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1], 1);

    PlayerTextdraws[playerid][textdraw_interaksi][2] = CreatePlayerTextDraw(playerid, 292.000, 343.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], -1.000, 5.000);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], 1);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], 10495);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], 255);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], 4);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2], 1);

    PlayerTextdraws[playerid][textdraw_interaksi][3] = CreatePlayerTextDraw(playerid, 284.000, 343.000, "Y");
    PlayerTextDrawLetterSize(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 0.260, 1.399);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 2);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 10239);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 0);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3], 1);

    PlayerTextdraws[playerid][textdraw_interaksi][4] = CreatePlayerTextDraw(playerid, 321.000, 345.000, "Akses garasi umum");
    PlayerTextDrawLetterSize(playerid, PlayerTextdraws[playerid][textdraw_interaksi][4], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][textdraw_interaksi][4], 2);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][4], 10239);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][textdraw_interaksi][4], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][textdraw_interaksi][4], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][4], 0);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][textdraw_interaksi][4], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][textdraw_interaksi][4], 1);

    PlayerTextdraws[playerid][textdraw_interaksi][5] = CreatePlayerTextDraw(playerid, 292.000, 352.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][textdraw_interaksi][5], -1.000, 5.000);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][textdraw_interaksi][5], 1);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][5], 10495);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][textdraw_interaksi][5], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][textdraw_interaksi][5], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][textdraw_interaksi][5], 255);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][textdraw_interaksi][5], 4);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][textdraw_interaksi][5], 1);
}

hook OnPlayerConnect(playerid)
{
    CreateTDShortKey(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    for(new x = 0; x < 6; x++)
    {
        PlayerTextDrawDestroy(playerid, PlayerTextdraws[playerid][textdraw_interaksi][x]);
    }
}

ShowKey(playerid, const text[])
{
    PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][textdraw_interaksi][4], text);
    for(new x = 0; x < 6; x++)
    {
        PlayerTextDrawShow(playerid, PlayerTextdraws[playerid][textdraw_interaksi][x]);
    }
    PlayerPlaySound(playerid, 1058, 0, 0, 0);
    return 1;
}

HideShortKey(playerid)
{
    PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][textdraw_interaksi][0]);
    PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][textdraw_interaksi][1]);
    PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][textdraw_interaksi][2]);
    PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][textdraw_interaksi][3]);
    PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][textdraw_interaksi][4]);
    PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][textdraw_interaksi][5]);
    return 1;
}