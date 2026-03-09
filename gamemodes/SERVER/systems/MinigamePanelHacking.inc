#include <YSI\y_hooks>

// Variables
new PlayerText: MinigamePanelHacking[MAX_PLAYERS][28];
new MinigamePH_Color[MAX_PLAYERS][27];
new bool:MinigamePH_Active[MAX_PLAYERS];
new MinigamePH_Errors[MAX_PLAYERS];
new MinigamePH_Success[MAX_PLAYERS];
new MinigamePH_Attempts[MAX_PLAYERS];
new MinigamePH_Callback[MAX_PLAYERS][64];
new MinigamePH_CallbackParams[MAX_PLAYERS][64];
new bool:MinigamePH_Clicked[MAX_PLAYERS][27];
new MinigamePH_Timer[MAX_PLAYERS];
new MinigamePH_TimerTask[MAX_PLAYERS]; 

new MinigamePH_TimerV1[MAX_PLAYERS];
new MinigamePH_TimerTaskV1[MAX_PLAYERS]; 


CreateMinigamePHTextDraws(playerid)
{
    MinigamePanelHacking[playerid][0] = CreatePlayerTextDraw(playerid, 216.000, 58.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][0], 226.000, 313.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][0], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][0], 512780609);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][0], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][0], 1);

    MinigamePanelHacking[playerid][1] = CreatePlayerTextDraw(playerid, 224.000, 84.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][1], 209.000, 3.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][1], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][1], 2147472639);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][1], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][1], 1);

    MinigamePanelHacking[playerid][2] = CreatePlayerTextDraw(playerid, 224.000, 93.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][2], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][2], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][2], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][2], 1);

    MinigamePanelHacking[playerid][3] = CreatePlayerTextDraw(playerid, 267.000, 93.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][3], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][3], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][3], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][3], 1);

    MinigamePanelHacking[playerid][4] = CreatePlayerTextDraw(playerid, 310.000, 93.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][4], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][4], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][4], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][4], 1);

    MinigamePanelHacking[playerid][5] = CreatePlayerTextDraw(playerid, 352.000, 93.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][5], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][5], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][5], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][5], 1);

    MinigamePanelHacking[playerid][6] = CreatePlayerTextDraw(playerid, 394.000, 93.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][6], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][6], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][6], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][6], 1);

    MinigamePanelHacking[playerid][7] = CreatePlayerTextDraw(playerid, 394.000, 144.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][7], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][7], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][7], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][7], 1);

    MinigamePanelHacking[playerid][8] = CreatePlayerTextDraw(playerid, 352.000, 144.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][8], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][8], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][8], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][8], 1);

    MinigamePanelHacking[playerid][9] = CreatePlayerTextDraw(playerid, 310.000, 144.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][9], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][9], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][9], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][9], 1);

    MinigamePanelHacking[playerid][10] = CreatePlayerTextDraw(playerid, 267.000, 144.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][10], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][10], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][10], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][10], 1);

    MinigamePanelHacking[playerid][11] = CreatePlayerTextDraw(playerid, 224.000, 144.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][11], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][11], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][11], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][11], 1);

    MinigamePanelHacking[playerid][12] = CreatePlayerTextDraw(playerid, 224.000, 195.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][12], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][12], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][12], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][12], 1);

    MinigamePanelHacking[playerid][13] = CreatePlayerTextDraw(playerid, 267.000, 195.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][13], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][13], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][13], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][13], 1);

    MinigamePanelHacking[playerid][14] = CreatePlayerTextDraw(playerid, 310.000, 195.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][14], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][14], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][14], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][14], 1);

    MinigamePanelHacking[playerid][15] = CreatePlayerTextDraw(playerid, 352.000, 195.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][15], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][15], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][15], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][15], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][15], 1);

    MinigamePanelHacking[playerid][16] = CreatePlayerTextDraw(playerid, 394.000, 195.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][16], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][16], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][16], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][16], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][16], 1);

    MinigamePanelHacking[playerid][17] = CreatePlayerTextDraw(playerid, 394.000, 247.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][17], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][17], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][17], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][17], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][17], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][17], 1);

    MinigamePanelHacking[playerid][18] = CreatePlayerTextDraw(playerid, 352.000, 247.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][18], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][18], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][18], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][18], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][18], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][18], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][18], 1);

    MinigamePanelHacking[playerid][19] = CreatePlayerTextDraw(playerid, 310.000, 247.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][19], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][19], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][19], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][19], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][19], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][19], 1);

    MinigamePanelHacking[playerid][20] = CreatePlayerTextDraw(playerid, 267.000, 247.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][20], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][20], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][20], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][20], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][20], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][20], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][20], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][20], 1);

    MinigamePanelHacking[playerid][21] = CreatePlayerTextDraw(playerid, 224.000, 247.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][21], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][21], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][21], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][21], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][21], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][21], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][21], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][21], 1);

    MinigamePanelHacking[playerid][22] = CreatePlayerTextDraw(playerid, 224.000, 299.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][22], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][22], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][22], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][22], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][22], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][22], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][22], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][22], 1);

    MinigamePanelHacking[playerid][23] = CreatePlayerTextDraw(playerid, 267.000, 299.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][23], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][23], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][23], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][23], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][23], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][23], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][23], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][23], 1);

    MinigamePanelHacking[playerid][24] = CreatePlayerTextDraw(playerid, 310.000, 299.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][24], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][24], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][24], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][24], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][24], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][24], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][24], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][24], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][24], 1);

    MinigamePanelHacking[playerid][25] = CreatePlayerTextDraw(playerid, 352.000, 299.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][25], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][25], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][25], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][25], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][25], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][25], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][25], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][25], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][25], 1);

    MinigamePanelHacking[playerid][26] = CreatePlayerTextDraw(playerid, 394.000, 299.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][26], 39.000, 46.000);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][26], 1);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][26], -1);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][26], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][26], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][26], 255);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][26], 4);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][26], 1);
    PlayerTextDrawSetSelectable(playerid, MinigamePanelHacking[playerid][26], 1);

    MinigamePanelHacking[playerid][27] = CreatePlayerTextDraw(playerid, 326.000, 69.000, "Hacking Panel");
    PlayerTextDrawLetterSize(playerid, MinigamePanelHacking[playerid][27], 0.160, 0.899);
    PlayerTextDrawAlignment(playerid, MinigamePanelHacking[playerid][27], 2);
    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][27], 2147472639);
    PlayerTextDrawSetShadow(playerid, MinigamePanelHacking[playerid][27], 0);
    PlayerTextDrawSetOutline(playerid, MinigamePanelHacking[playerid][27], 0);
    PlayerTextDrawBackgroundColor(playerid, MinigamePanelHacking[playerid][27], 150);
    PlayerTextDrawFont(playerid, MinigamePanelHacking[playerid][27], 1);
    PlayerTextDrawSetProportional(playerid, MinigamePanelHacking[playerid][27], 1);

    return 1;
}

ShowMinigamePH(playerid, const callback[] = "", const params[] = "")
{
    if(MinigamePH_Active[playerid]) return 0; 
    
    MinigamePH_Active[playerid] = true;
    MinigamePH_Errors[playerid] = 0;
    MinigamePH_Success[playerid] = 0;
    MinigamePH_Attempts[playerid] = 0;
    MinigamePH_TimerV1[playerid] = 10;
    MinigamePH_Locked[playerid] = true;
    
    // Reset status klik
    for(new i = 0; i < 27; i++)
    {
        MinigamePH_Clicked[playerid][i] = false;
    }
    
    // Simpan callback dan parameter
    format(MinigamePH_Callback[playerid], sizeof(MinigamePH_Callback[]), callback);
    format(MinigamePH_CallbackParams[playerid], sizeof(MinigamePH_CallbackParams[]), params);

    for(new i = 2; i < 27; i++)
    {
        PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][i], -1);
        MinigamePH_Color[playerid][i] = -1;
    }

    PlayerTextDrawShow(playerid, MinigamePanelHacking[playerid][0]);
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][1], 209.000, 3.000);
    PlayerTextDrawShow(playerid, MinigamePanelHacking[playerid][1]);
    PlayerTextDrawShow(playerid, MinigamePanelHacking[playerid][27]);
    
    for(new i = 2; i < 27; i++)
    {
        PlayerTextDrawShow(playerid, MinigamePanelHacking[playerid][i]);
    }
    
    new redBoxes = 0;
    new usedBoxes[27];
    for(new i = 0; i < 27; i++) usedBoxes[i] = 0; 

    while(redBoxes < 12)
    {
        new rand = random(25) + 2;
        if(usedBoxes[rand] == 0)
        {
            PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][rand], COLOR_RED);
            PlayerTextDrawShow(playerid, MinigamePanelHacking[playerid][rand]);
            MinigamePH_Color[playerid][rand] = COLOR_RED;
            usedBoxes[rand] = 1;
            redBoxes++;
        }
    }

    MinigamePH_TimerTaskV1[playerid] = SetTimerEx("ResetButtonColorsPH", 1000, true, "i", playerid);
    
    // Aktifkan SelectTextDraw agar tombol bisa diklik
    SelectTextDraw(playerid, COLOR_BLUE);
    
    return 1;
}

HideMinigamePH(playerid)
{
    if(!MinigamePH_Active[playerid]) return 0;
    
    MinigamePH_Active[playerid] = false; 

    KillTimer(MinigamePH_TimerTask[playerid]);
    KillTimer(MinigamePH_TimerTaskV1[playerid]);
    
    for(new i = 0; i < 28; i++)
    {
        PlayerTextDrawHide(playerid, MinigamePanelHacking[playerid][i]);
    }
    
    return 1;
}

forward ResetButtonColorsPH(playerid);
public ResetButtonColorsPH(playerid)
{
    MinigamePH_TimerV1[playerid]--;

    // Update timer bar
    new Float:width = 209.0 * (MinigamePH_TimerV1[playerid] / 10.0);
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][1], width, 3.000);
    PlayerTextDrawShow(playerid, MinigamePanelHacking[playerid][1]);

    if(MinigamePH_TimerV1[playerid] <= 0)
    {
        PlayerTextDrawHide(playerid, MinigamePanelHacking[playerid][0]);
        PlayerTextDrawHide(playerid, MinigamePanelHacking[playerid][1]);
        for(new i = 2; i < 27; i++)
        {
            if(MinigamePH_Color[playerid][i] == COLOR_RED)
            {
                PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][i], -1);
                PlayerTextDrawShow(playerid, MinigamePanelHacking[playerid][i]);
            }
        }
        KillTimer(MinigamePH_TimerTaskV1[playerid]);

        MinigamePH_Timer[playerid] = 30;
        MinigamePH_Locked[playerid] = false;
        PlayerTextDrawShow(playerid, MinigamePanelHacking[playerid][0]);
        PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][1], 209.000, 3.000);
        PlayerTextDrawShow(playerid, MinigamePanelHacking[playerid][1]);
        MinigamePH_TimerTask[playerid] = SetTimerEx("UpdateMinigamePHTimer", 1000, true, "i", playerid);
    }
    return 1;
}

forward UpdateMinigamePHTimer(playerid); 
public UpdateMinigamePHTimer(playerid)
{
    if(!MinigamePH_Active[playerid]) return 0;
    
    MinigamePH_Timer[playerid]--;
    
    new Float:width = 209.0 * (MinigamePH_Timer[playerid] / 30.0);
    PlayerTextDrawTextSize(playerid, MinigamePanelHacking[playerid][1], width, 3.000);
    PlayerTextDrawShow(playerid, MinigamePanelHacking[playerid][1]);
    
    if(MinigamePH_Timer[playerid] <= 0)
    {
        // Waktu habis
        KillTimer(MinigamePH_TimerTask[playerid]);
        HideMinigamePH(playerid);
        CancelSelectTextDraw(playerid);
        MinigamePH_Active[playerid] = false;
        MinigamePH_Locked[playerid] = false;
        SendClientMessageEx(playerid, COLOR_WHITE, ""RED_E"Time's up! "WHITE_E"You failed the minigame");
    }
    
    return 1;
}

forward OnMinigamePHComplete(playerid, const callback[], const params[]);
public OnMinigamePHComplete(playerid, const callback[], const params[])
{
    if(strcmp(params, "RobbankProcces") == 0)
    {
        Inventory_Remove(playerid, "Hacking Tools", 1);
        Inventory_Remove(playerid, "Bomb", 1);
        ShowItemBox(playerid, "Removed 1x", "Hacking Tools", 19893);
        ShowItemBox(playerid, "Removed 1x", "Bomb", 1636);
        ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 4.0, 1, 0, 0, 0, 0, 1);
        AccountData[playerid][ActivityTime] = 1;
        pTimerRobbank[playerid] = SetTimerEx("ProccesExplodeBank", 1000, true, "i", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "Planting Boomb");
        ShowProgressBar(playerid);
    }
    return 1;
}