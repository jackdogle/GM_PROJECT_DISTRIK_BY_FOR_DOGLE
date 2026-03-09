#include <YSI\y_hooks>

new PlayerText: ATRP_Phone[MAX_PLAYERS][70];

new PlayerText: ATRP_CallTD[MAX_PLAYERS][15];
new PlayerText: CloseCallButton[MAX_PLAYERS];
new PlayerText: ContactNameTD[MAX_PLAYERS];
new PlayerText: StatusDialingTD[MAX_PLAYERS];
new PlayerText: RedButtonoutComingCall[MAX_PLAYERS];
new PlayerText: RedButtonincomingCall[MAX_PLAYERS];
new PlayerText: GreenButtonincomingCall[MAX_PLAYERS];

new PlayerText: ATRP_BankTD[MAX_PLAYERS][46];

new PlayerText: ATRP_SpotifyTD[MAX_PLAYERS][57];
new PlayerText: ATRP_HomeSpotify[MAX_PLAYERS][37];

new PlayerText: ATRP_TwitterHomeTD[MAX_PLAYERS][33];
new PlayerText: CloseTwitterHome[MAX_PLAYERS];

new PlayerText: ATRP_TwitterHomepageTD[MAX_PLAYERS][58];
new PlayerText: CloseTwitterHomePage[MAX_PLAYERS];
new PlayerText: ATRP_TwitterNotif[MAX_PLAYERS][38];

ATRPPhoneTwitterPostLoad(playerid)
{
    ATRP_TwitterNotif[playerid][0] = CreatePlayerTextDraw(playerid, 427.000, 356.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][0], 114.000, 101.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][0], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][0], -1329275137);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][0], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][0], 1);

    ATRP_TwitterNotif[playerid][1] = CreatePlayerTextDraw(playerid, 421.000, 337.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][1], 37.000, 42.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][1], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][1], -1329275137);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][1], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][1], 1);

    ATRP_TwitterNotif[playerid][2] = CreatePlayerTextDraw(playerid, 510.000, 337.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][2], 37.000, 42.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][2], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][2], -1329275137);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][2], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][2], 1);

    ATRP_TwitterNotif[playerid][3] = CreatePlayerTextDraw(playerid, 437.000, 344.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][3], 95.000, 101.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][3], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][3], -1329275137);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][3], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][3], 1);

    ATRP_TwitterNotif[playerid][4] = CreatePlayerTextDraw(playerid, 423.000, 340.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][4], 32.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][4], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][4], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][4], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][4], 1);

    ATRP_TwitterNotif[playerid][5] = CreatePlayerTextDraw(playerid, 513.000, 340.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][5], 32.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][5], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][5], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][5], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][5], 1);

    ATRP_TwitterNotif[playerid][6] = CreatePlayerTextDraw(playerid, 428.500, 358.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][6], 111.000, 101.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][6], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][6], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][6], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][6], 1);

    ATRP_TwitterNotif[playerid][7] = CreatePlayerTextDraw(playerid, 439.500, 346.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][7], 88.000, 101.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][7], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][7], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][7], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][7], 1);

    ATRP_TwitterNotif[playerid][8] = CreatePlayerTextDraw(playerid, 426.000, 343.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][8], 26.000, 30.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][8], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][8], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][8], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][8], 1);

    ATRP_TwitterNotif[playerid][9] = CreatePlayerTextDraw(playerid, 516.000, 343.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][9], 26.000, 30.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][9], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][9], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][9], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][9], 1);

    ATRP_TwitterNotif[playerid][10] = CreatePlayerTextDraw(playerid, 430.500, 357.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][10], 107.000, 101.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][10], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][10], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][10], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][10], 1);

    ATRP_TwitterNotif[playerid][11] = CreatePlayerTextDraw(playerid, 437.500, 348.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][11], 93.000, 101.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][11], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][11], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][11], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][11], 1);

    ATRP_TwitterNotif[playerid][12] = CreatePlayerTextDraw(playerid, 426.000, 363.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][12], 1.000, 17.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][12], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][12], -1329275137);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][12], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][12], 1);

    ATRP_TwitterNotif[playerid][13] = CreatePlayerTextDraw(playerid, 426.000, 387.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][13], 1.000, 28.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][13], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][13], -1329275137);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][13], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][13], 1);

    ATRP_TwitterNotif[playerid][14] = CreatePlayerTextDraw(playerid, 426.000, 420.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][14], 1.000, 28.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][14], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][14], -1329275137);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][14], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][14], 1);

    ATRP_TwitterNotif[playerid][15] = CreatePlayerTextDraw(playerid, 541.000, 400.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][15], 1.000, 28.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][15], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][15], -1329275137);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][15], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][15], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][15], 1);

    ATRP_TwitterNotif[playerid][16] = CreatePlayerTextDraw(playerid, 468.000, 354.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][16], 29.000, 9.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][16], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][16], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][16], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][16], 1);

    ATRP_TwitterNotif[playerid][17] = CreatePlayerTextDraw(playerid, 463.000, 352.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][17], 11.000, 13.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][17], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][17], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][17], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][17], 1);

    ATRP_TwitterNotif[playerid][18] = CreatePlayerTextDraw(playerid, 491.000, 352.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][18], 11.000, 13.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][18], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][18], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][18], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][18], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][18], 1);

    ATRP_TwitterNotif[playerid][19] = CreatePlayerTextDraw(playerid, 518.000, 352.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][19], 13.000, 6.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][19], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][19], -1329275137);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][19], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][19], 1);

    ATRP_TwitterNotif[playerid][20] = CreatePlayerTextDraw(playerid, 513.900, 353.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][20], 1.000, 8.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][20], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][20], -1329275137);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][20], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][20], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][20], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][20], 1);

    ATRP_TwitterNotif[playerid][21] = CreatePlayerTextDraw(playerid, 512.000, 355.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][21], 0.899, 6.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][21], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][21], -1329275137);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][21], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][21], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][21], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][21], 1);

    ATRP_TwitterNotif[playerid][22] = CreatePlayerTextDraw(playerid, 510.000, 357.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][22], 0.899, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][22], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][22], -1329275137);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][22], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][22], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][22], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][22], 1);

    ATRP_TwitterNotif[playerid][23] = CreatePlayerTextDraw(playerid, 524.000, 352.000, "70");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterNotif[playerid][23], 0.109, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][23], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][23], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][23], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][23], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][23], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][23], 1);

    ATRP_TwitterNotif[playerid][24] = CreatePlayerTextDraw(playerid, 520.000, 353.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][24], 13.000, 3.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][24], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][24], -1329275137);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][24], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][24], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][24], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][24], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][24], 1);

    ATRP_TwitterNotif[playerid][25] = CreatePlayerTextDraw(playerid, 442.000, 351.000, "10:20");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterNotif[playerid][25], 0.140, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][25], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][25], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][25], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][25], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][25], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][25], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][25], 1);

    ATRP_TwitterNotif[playerid][26] = CreatePlayerTextDraw(playerid, 441.000, 378.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][26], 85.000, 46.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][26], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][26], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][26], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][26], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][26], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][26], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][26], 1);

    ATRP_TwitterNotif[playerid][27] = CreatePlayerTextDraw(playerid, 439.000, 371.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][27], 12.000, 13.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][27], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][27], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][27], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][27], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][27], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][27], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][27], 1);

    ATRP_TwitterNotif[playerid][28] = CreatePlayerTextDraw(playerid, 516.000, 371.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][28], 12.000, 13.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][28], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][28], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][28], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][28], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][28], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][28], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][28], 1);

    ATRP_TwitterNotif[playerid][29] = CreatePlayerTextDraw(playerid, 516.000, 418.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][29], 12.000, 13.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][29], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][29], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][29], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][29], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][29], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][29], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][29], 1);

    ATRP_TwitterNotif[playerid][30] = CreatePlayerTextDraw(playerid, 439.000, 418.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][30], 12.000, 13.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][30], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][30], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][30], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][30], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][30], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][30], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][30], 1);

    ATRP_TwitterNotif[playerid][31] = CreatePlayerTextDraw(playerid, 445.000, 373.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterNotif[playerid][31], 78.000, 56.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][31], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][31], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][31], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][31], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][31], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][31], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][31], 1);

    ATRP_TwitterNotif[playerid][32] = CreatePlayerTextDraw(playerid, 446.000, 375.000, "X");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterNotif[playerid][32], 0.240, 1.299);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][32], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][32], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][32], 1);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][32], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][32], -1);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][32], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][32], 1);

    ATRP_TwitterNotif[playerid][33] = CreatePlayerTextDraw(playerid, 523.000, 376.000, "District ");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterNotif[playerid][33], 0.129, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][33], 3);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][33], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][33], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][33], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][33], -1);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][33], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][33], 1);

    ATRP_TwitterNotif[playerid][34] = CreatePlayerTextDraw(playerid, 444.000, 420.000, "12:12");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterNotif[playerid][34], 0.129, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][34], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][34], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][34], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][34], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][34], -1);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][34], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][34], 1);

    ATRP_TwitterNotif[playerid][35] = CreatePlayerTextDraw(playerid, 483.000, 397.000, "Jual ayam enak banget nih dek");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterNotif[playerid][35], 0.129, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][35], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][35], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][35], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][35], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][35], -1);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][35], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][35], 1);

    ATRP_TwitterNotif[playerid][36] = CreatePlayerTextDraw(playerid, 483.000, 405.000, "Murah banget dekk ku");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterNotif[playerid][36], 0.129, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][36], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][36], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][36], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][36], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][36], -1);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][36], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][36], 1);

    ATRP_TwitterNotif[playerid][37] = CreatePlayerTextDraw(playerid, 483.000, 405.000, "Asik banget bang sumpa");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterNotif[playerid][37], 0.129, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterNotif[playerid][37], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterNotif[playerid][37], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterNotif[playerid][37], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterNotif[playerid][37], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterNotif[playerid][37], -1);
    PlayerTextDrawFont(playerid, ATRP_TwitterNotif[playerid][37], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterNotif[playerid][37], 1);

    return 1;
}
ATRPPhoneTwitterPostUnload(playerid)
{
    for(new i = 0; i < 38; i++)
    {
        PlayerTextDrawDestroy(playerid, ATRP_TwitterNotif[playerid][i]);
    }
    return 1;
}
ATRPhoneTwitterHomepageLoad(playerid)
{
    ATRP_TwitterHomepageTD[playerid][0] = CreatePlayerTextDraw(playerid, 423.000, 171.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][0], 106.000, 235.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][0], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][0], 1);

    ATRP_TwitterHomepageTD[playerid][1] = CreatePlayerTextDraw(playerid, 416.700, 149.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][1], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][1], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][1], 1);

    ATRP_TwitterHomepageTD[playerid][2] = CreatePlayerTextDraw(playerid, 495.700, 149.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][2], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][2], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][2], 1);

    ATRP_TwitterHomepageTD[playerid][3] = CreatePlayerTextDraw(playerid, 495.700, 383.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][3], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][3], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][3], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][3], 1);

    ATRP_TwitterHomepageTD[playerid][4] = CreatePlayerTextDraw(playerid, 416.700, 383.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][4], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][4], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][4], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][4], 1);

    ATRP_TwitterHomepageTD[playerid][5] = CreatePlayerTextDraw(playerid, 438.000, 156.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][5], 77.000, 265.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][5], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][5], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][5], 1);

    ATRP_TwitterHomepageTD[playerid][6] = CreatePlayerTextDraw(playerid, 419.700, 152.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][6], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][6], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][6], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][6], 1);

    ATRP_TwitterHomepageTD[playerid][7] = CreatePlayerTextDraw(playerid, 499.700, 152.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][7], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][7], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][7], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][7], 1);

    ATRP_TwitterHomepageTD[playerid][8] = CreatePlayerTextDraw(playerid, 499.700, 387.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][8], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][8], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][8], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][8], 1);

    ATRP_TwitterHomepageTD[playerid][9] = CreatePlayerTextDraw(playerid, 419.700, 387.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][9], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][9], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][9], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][9], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][9], 1);

    ATRP_TwitterHomepageTD[playerid][10] = CreatePlayerTextDraw(playerid, 438.000, 158.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][10], 77.000, 260.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][10], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][10], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][10], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][10], 1);

    ATRP_TwitterHomepageTD[playerid][11] = CreatePlayerTextDraw(playerid, 425.000, 169.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][11], 102.500, 235.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][11], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][11], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][11], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][11], 1);

    ATRP_TwitterHomepageTD[playerid][12] = CreatePlayerTextDraw(playerid, 461.000, 164.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][12], 30.500, 7.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][12], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][12], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][12], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][12], 1);

    ATRP_TwitterHomepageTD[playerid][13] = CreatePlayerTextDraw(playerid, 456.000, 162.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][13], 10.000, 10.500);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][13], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][13], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][13], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][13], 1);

    ATRP_TwitterHomepageTD[playerid][14] = CreatePlayerTextDraw(playerid, 486.000, 162.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][14], 10.000, 10.500);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][14], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][14], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][14], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][14], 1);

    ATRP_TwitterHomepageTD[playerid][15] = CreatePlayerTextDraw(playerid, 440.000, 166.000, "18:00");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][15], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][15], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][15], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][15], 1);

    ATRP_TwitterHomepageTD[playerid][16] = CreatePlayerTextDraw(playerid, 513.000, 164.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][16], 9.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][16], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][16], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][16], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][16], 1);

    ATRP_TwitterHomepageTD[playerid][17] = CreatePlayerTextDraw(playerid, 513.500, 165.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][17], 7.000, 2.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][17], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][17], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][17], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][17], 1);

    ATRP_TwitterHomepageTD[playerid][18] = CreatePlayerTextDraw(playerid, 508.500, 165.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][18], 1.000, 5.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][18], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][18], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][18], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][18], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][18], 1);

    ATRP_TwitterHomepageTD[playerid][19] = CreatePlayerTextDraw(playerid, 506.500, 166.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][19], 1.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][19], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][19], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][19], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][19], 1);

    ATRP_TwitterHomepageTD[playerid][20] = CreatePlayerTextDraw(playerid, 505.000, 167.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][20], 1.000, 3.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][20], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][20], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][20], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][20], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][20], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][20], 1);

    ATRP_TwitterHomepageTD[playerid][21] = CreatePlayerTextDraw(playerid, 450.000, 405.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][21], 56.000, 10.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][21], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][21], 0);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][21], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][21], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][21], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][21], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_TwitterHomepageTD[playerid][21], 1);

    ATRP_TwitterHomepageTD[playerid][22] = CreatePlayerTextDraw(playerid, 450.000, 409.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][22], 56.000, 3.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][22], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][22], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][22], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][22], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][22], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][22], 1);

    ATRP_TwitterHomepageTD[playerid][23] = CreatePlayerTextDraw(playerid, 430.000, 176.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][23], 7.000, 8.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][23], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][23], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][23], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][23], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][23], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][23], 1);

    ATRP_TwitterHomepageTD[playerid][24] = CreatePlayerTextDraw(playerid, 428.000, 182.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][24], 11.000, 8.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][24], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][24], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][24], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][24], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][24], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][24], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][24], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_TwitterHomepageTD[playerid][24], 1);

    ATRP_TwitterHomepageTD[playerid][25] = CreatePlayerTextDraw(playerid, 439.000, 180.000, "Chess7");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][25], 0.119, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][25], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][25], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][25], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][25], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][25], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][25], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][25], 1);

    ATRP_TwitterHomepageTD[playerid][26] = CreatePlayerTextDraw(playerid, 509.000, 179.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][26], 13.000, 13.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][26], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][26], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][26], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][26], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][26], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][26], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][26], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_TwitterHomepageTD[playerid][26], 1);

    ATRP_TwitterHomepageTD[playerid][27] = CreatePlayerTextDraw(playerid, 512.000, 179.000, "+");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][27], 0.280, 1.299);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][27], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][27], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][27], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][27], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][27], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][27], 2);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][27], 1);

    ATRP_TwitterHomepageTD[playerid][28] = CreatePlayerTextDraw(playerid, 432.000, 210.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][28], 87.000, 31.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][28], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][28], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][28], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][28], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][28], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][28], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][28], 1);

    ATRP_TwitterHomepageTD[playerid][29] = CreatePlayerTextDraw(playerid, 432.000, 244.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][29], 87.000, 31.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][29], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][29], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][29], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][29], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][29], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][29], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][29], 1);

    ATRP_TwitterHomepageTD[playerid][30] = CreatePlayerTextDraw(playerid, 432.000, 278.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][30], 87.000, 31.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][30], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][30], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][30], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][30], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][30], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][30], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][30], 1);

    ATRP_TwitterHomepageTD[playerid][31] = CreatePlayerTextDraw(playerid, 432.000, 312.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][31], 87.000, 31.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][31], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][31], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][31], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][31], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][31], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][31], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][31], 1);

    ATRP_TwitterHomepageTD[playerid][32] = CreatePlayerTextDraw(playerid, 432.000, 346.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][32], 87.000, 31.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][32], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][32], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][32], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][32], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][32], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][32], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][32], 1);

    ATRP_TwitterHomepageTD[playerid][33] = CreatePlayerTextDraw(playerid, 435.000, 211.000, "Chess7");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][33], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][33], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][33], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][33], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][33], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][33], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][33], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][33], 1);

    ATRP_TwitterHomepageTD[playerid][34] = CreatePlayerTextDraw(playerid, 435.000, 245.000, "Chess7");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][34], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][34], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][34], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][34], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][34], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][34], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][34], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][34], 1);

    ATRP_TwitterHomepageTD[playerid][35] = CreatePlayerTextDraw(playerid, 435.000, 279.000, "Chess7");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][35], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][35], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][35], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][35], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][35], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][35], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][35], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][35], 1);

    ATRP_TwitterHomepageTD[playerid][36] = CreatePlayerTextDraw(playerid, 435.000, 313.000, "Chess7");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][36], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][36], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][36], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][36], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][36], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][36], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][36], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][36], 1);

    ATRP_TwitterHomepageTD[playerid][37] = CreatePlayerTextDraw(playerid, 435.000, 348.000, "Chess7");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][37], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][37], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][37], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][37], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][37], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][37], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][37], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][37], 1);

    ATRP_TwitterHomepageTD[playerid][38] = CreatePlayerTextDraw(playerid, 516.000, 233.000, "18:00");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][38], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][38], 3);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][38], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][38], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][38], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][38], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][38], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][38], 1);

    ATRP_TwitterHomepageTD[playerid][39] = CreatePlayerTextDraw(playerid, 516.000, 266.000, "18:00");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][39], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][39], 3);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][39], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][39], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][39], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][39], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][39], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][39], 1);

    ATRP_TwitterHomepageTD[playerid][40] = CreatePlayerTextDraw(playerid, 516.000, 300.000, "18:00");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][40], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][40], 3);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][40], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][40], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][40], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][40], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][40], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][40], 1);

    ATRP_TwitterHomepageTD[playerid][41] = CreatePlayerTextDraw(playerid, 516.000, 334.000, "18:00");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][41], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][41], 3);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][41], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][41], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][41], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][41], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][41], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][41], 1);

    ATRP_TwitterHomepageTD[playerid][42] = CreatePlayerTextDraw(playerid, 516.000, 368.000, "18:00");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][42], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][42], 3);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][42], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][42], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][42], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][42], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][42], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][42], 1);

    ATRP_TwitterHomepageTD[playerid][43] = CreatePlayerTextDraw(playerid, 476.000, 222.000, "kemana aja sih");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][43], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][43], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][43], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][43], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][43], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][43], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][43], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][43], 1);

    ATRP_TwitterHomepageTD[playerid][44] = CreatePlayerTextDraw(playerid, 476.000, 253.000, "kemana aja sih");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][44], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][44], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][44], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][44], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][44], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][44], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][44], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][44], 1);

    ATRP_TwitterHomepageTD[playerid][45] = CreatePlayerTextDraw(playerid, 476.000, 286.000, "kemana aja sih");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][45], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][45], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][45], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][45], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][45], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][45], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][45], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][45], 1);

    ATRP_TwitterHomepageTD[playerid][46] = CreatePlayerTextDraw(playerid, 476.000, 320.000, "kemana aja sih");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][46], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][46], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][46], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][46], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][46], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][46], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][46], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][46], 1);

    ATRP_TwitterHomepageTD[playerid][47] = CreatePlayerTextDraw(playerid, 476.000, 353.000, "kemana aja sih");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][47], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][47], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][47], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][47], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][47], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][47], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][47], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][47], 1);

    ATRP_TwitterHomepageTD[playerid][48] = CreatePlayerTextDraw(playerid, 501.000, 381.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][48], 18.000, 10.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][48], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][48], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][48], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][48], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][48], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][48], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][48], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_TwitterHomepageTD[playerid][48], 1);

    ATRP_TwitterHomepageTD[playerid][49] = CreatePlayerTextDraw(playerid, 432.000, 381.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomepageTD[playerid][49], 18.000, 10.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][49], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][49], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][49], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][49], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][49], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][49], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][49], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_TwitterHomepageTD[playerid][49], 1);

    ATRP_TwitterHomepageTD[playerid][50] = CreatePlayerTextDraw(playerid, 507.000, 381.000, ">");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][50], 0.280, 0.999);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][50], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][50], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][50], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][50], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][50], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][50], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][50], 1);

    ATRP_TwitterHomepageTD[playerid][51] = CreatePlayerTextDraw(playerid, 437.000, 381.000, "<");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][51], 0.280, 0.999);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][51], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][51], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][51], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][51], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][51], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][51], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][51], 1);

    ATRP_TwitterHomepageTD[playerid][52] = CreatePlayerTextDraw(playerid, 475.000, 383.000, "1/4");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][52], 0.150, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][52], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][52], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][52], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][52], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][52], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][52], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][52], 1);

    ATRP_TwitterHomepageTD[playerid][53] = CreatePlayerTextDraw(playerid, 476.000, 228.000, "kemana aja sih");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][53], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][53], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][53], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][53], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][53], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][53], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][53], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][53], 1);

    ATRP_TwitterHomepageTD[playerid][54] = CreatePlayerTextDraw(playerid, 476.000, 260.000, "kemana aja sih");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][54], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][54], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][54], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][54], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][54], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][54], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][54], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][54], 1);

    ATRP_TwitterHomepageTD[playerid][55] = CreatePlayerTextDraw(playerid, 476.000, 293.000, "kemana aja sih");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][55], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][55], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][55], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][55], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][55], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][55], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][55], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][55], 1);

    ATRP_TwitterHomepageTD[playerid][56] = CreatePlayerTextDraw(playerid, 476.000, 326.000, "kemana aja sih");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][56], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][56], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][56], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][56], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][56], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][56], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][56], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][56], 1);

    ATRP_TwitterHomepageTD[playerid][57] = CreatePlayerTextDraw(playerid, 476.000, 359.000, "kemana aja sih");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomepageTD[playerid][57], 0.128, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomepageTD[playerid][57], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomepageTD[playerid][57], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomepageTD[playerid][57], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomepageTD[playerid][57], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomepageTD[playerid][57], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomepageTD[playerid][57], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomepageTD[playerid][57], 1);
    return 1;
}

ATRPhoneTwitterHomepageUnload(playerid)
{
    for(new i; i < 58; i++) PlayerTextDrawDestroy(playerid, ATRP_TwitterHomepageTD[playerid][i]);
    PlayerTextDrawDestroy(playerid, CloseTwitterHomePage[playerid]);
    return 1;
}

ATRPhoneTwitterHomeLoad(playerid)
{
    ATRP_TwitterHomeTD[playerid][0] = CreatePlayerTextDraw(playerid, 423.000, 171.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][0], 106.000, 235.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][0], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][0], 1);

    ATRP_TwitterHomeTD[playerid][1] = CreatePlayerTextDraw(playerid, 416.700, 149.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][1], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][1], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][1], 1);

    ATRP_TwitterHomeTD[playerid][2] = CreatePlayerTextDraw(playerid, 495.700, 149.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][2], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][2], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][2], 1);

    ATRP_TwitterHomeTD[playerid][3] = CreatePlayerTextDraw(playerid, 495.700, 383.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][3], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][3], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][3], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][3], 1);

    ATRP_TwitterHomeTD[playerid][4] = CreatePlayerTextDraw(playerid, 416.700, 383.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][4], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][4], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][4], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][4], 1);

    ATRP_TwitterHomeTD[playerid][5] = CreatePlayerTextDraw(playerid, 438.000, 156.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][5], 77.000, 265.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][5], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][5], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][5], 1);

    ATRP_TwitterHomeTD[playerid][6] = CreatePlayerTextDraw(playerid, 419.700, 152.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][6], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][6], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][6], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][6], 1);

    ATRP_TwitterHomeTD[playerid][7] = CreatePlayerTextDraw(playerid, 499.700, 152.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][7], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][7], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][7], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][7], 1);

    ATRP_TwitterHomeTD[playerid][8] = CreatePlayerTextDraw(playerid, 499.700, 387.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][8], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][8], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][8], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][8], 1);

    ATRP_TwitterHomeTD[playerid][9] = CreatePlayerTextDraw(playerid, 419.700, 387.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][9], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][9], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][9], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][9], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][9], 1);

    ATRP_TwitterHomeTD[playerid][10] = CreatePlayerTextDraw(playerid, 438.000, 158.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][10], 77.000, 260.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][10], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][10], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][10], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][10], 1);

    ATRP_TwitterHomeTD[playerid][11] = CreatePlayerTextDraw(playerid, 425.000, 169.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][11], 102.500, 235.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][11], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][11], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][11], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][11], 1);

    ATRP_TwitterHomeTD[playerid][12] = CreatePlayerTextDraw(playerid, 461.000, 164.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][12], 30.500, 7.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][12], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][12], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][12], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][12], 1);

    ATRP_TwitterHomeTD[playerid][13] = CreatePlayerTextDraw(playerid, 456.000, 162.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][13], 10.000, 10.500);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][13], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][13], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][13], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][13], 1);

    ATRP_TwitterHomeTD[playerid][14] = CreatePlayerTextDraw(playerid, 486.000, 162.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][14], 10.000, 10.500);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][14], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][14], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][14], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][14], 1);

    ATRP_TwitterHomeTD[playerid][15] = CreatePlayerTextDraw(playerid, 440.000, 166.000, "18:00");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomeTD[playerid][15], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][15], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][15], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][15], 1);

    ATRP_TwitterHomeTD[playerid][16] = CreatePlayerTextDraw(playerid, 513.000, 164.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][16], 9.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][16], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][16], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][16], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][16], 1);

    ATRP_TwitterHomeTD[playerid][17] = CreatePlayerTextDraw(playerid, 513.500, 165.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][17], 7.000, 2.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][17], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][17], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][17], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][17], 1);

    ATRP_TwitterHomeTD[playerid][18] = CreatePlayerTextDraw(playerid, 508.500, 165.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][18], 1.000, 5.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][18], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][18], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][18], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][18], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][18], 1);

    ATRP_TwitterHomeTD[playerid][19] = CreatePlayerTextDraw(playerid, 506.500, 166.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][19], 1.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][19], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][19], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][19], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][19], 1);

    ATRP_TwitterHomeTD[playerid][20] = CreatePlayerTextDraw(playerid, 505.000, 167.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][20], 1.000, 3.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][20], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][20], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][20], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][20], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][20], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][20], 1);

    ATRP_TwitterHomeTD[playerid][21] = CreatePlayerTextDraw(playerid, 450.000, 405.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][21], 56.000, 10.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][21], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][21], 0);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][21], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][21], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][21], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][21], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_TwitterHomeTD[playerid][21], 1);

    ATRP_TwitterHomeTD[playerid][22] = CreatePlayerTextDraw(playerid, 450.000, 409.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][22], 56.000, 3.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][22], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][22], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][22], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][22], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][22], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][22], 1);

    ATRP_TwitterHomeTD[playerid][23] = CreatePlayerTextDraw(playerid, 450.000, 287.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][23], 56.000, 13.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][23], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][23], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][23], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][23], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][23], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][23], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_TwitterHomeTD[playerid][23], 1);

    ATRP_TwitterHomeTD[playerid][24] = CreatePlayerTextDraw(playerid, 450.000, 313.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][24], 56.000, 13.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][24], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][24], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][24], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][24], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][24], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][24], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][24], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_TwitterHomeTD[playerid][24], 1);

    ATRP_TwitterHomeTD[playerid][25] = CreatePlayerTextDraw(playerid, 440.000, 283.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][25], 21.000, 21.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][25], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][25], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][25], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][25], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][25], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][25], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][25], 1);

    ATRP_TwitterHomeTD[playerid][26] = CreatePlayerTextDraw(playerid, 495.000, 283.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][26], 21.000, 21.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][26], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][26], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][26], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][26], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][26], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][26], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][26], 1);

    ATRP_TwitterHomeTD[playerid][27] = CreatePlayerTextDraw(playerid, 494.000, 310.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][27], 21.000, 19.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][27], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][27], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][27], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][27], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][27], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][27], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][27], 1);

    ATRP_TwitterHomeTD[playerid][28] = CreatePlayerTextDraw(playerid, 440.000, 310.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_TwitterHomeTD[playerid][28], 21.000, 19.000);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][28], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][28], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][28], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][28], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][28], 255);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][28], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][28], 1);

    ATRP_TwitterHomeTD[playerid][29] = CreatePlayerTextDraw(playerid, 466.000, 220.000, "X");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomeTD[playerid][29], 0.739, 4.899);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][29], 1);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][29], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][29], 1);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][29], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][29], -1);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][29], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][29], 1);

    ATRP_TwitterHomeTD[playerid][30] = CreatePlayerTextDraw(playerid, 475.000, 210.000, "Welcome To Twitt");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomeTD[playerid][30], 0.160, 0.899);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][30], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][30], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][30], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][30], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][30], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][30], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][30], 1);

    ATRP_TwitterHomeTD[playerid][31] = CreatePlayerTextDraw(playerid, 478.000, 289.000, "Sign In");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomeTD[playerid][31], 0.150, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][31], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][31], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][31], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][31], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][31], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][31], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][31], 1);

    ATRP_TwitterHomeTD[playerid][32] = CreatePlayerTextDraw(playerid, 479.000, 315.000, "Create Account");
    PlayerTextDrawLetterSize(playerid, ATRP_TwitterHomeTD[playerid][32], 0.140, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_TwitterHomeTD[playerid][32], 2);
    PlayerTextDrawColor(playerid, ATRP_TwitterHomeTD[playerid][32], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_TwitterHomeTD[playerid][32], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_TwitterHomeTD[playerid][32], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_TwitterHomeTD[playerid][32], 150);
    PlayerTextDrawFont(playerid, ATRP_TwitterHomeTD[playerid][32], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_TwitterHomeTD[playerid][32], 1);
    return 1;
}

ATRPhoneTwitterHomeUnload(playerid)
{
    for(new i; i < 33; i++) PlayerTextDrawDestroy(playerid, ATRP_TwitterHomeTD[playerid][i]);
    return 1;
}

ATRPhoneLoad(playerid)
{
    ATRP_Phone[playerid][0] = CreatePlayerTextDraw(playerid, 423.000, 171.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][0], 106.000, 235.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][0], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][0], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][0], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][0], 1);

    ATRP_Phone[playerid][1] = CreatePlayerTextDraw(playerid, 416.700, 149.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][1], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][1], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][1], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][1], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][1], 1);

    ATRP_Phone[playerid][2] = CreatePlayerTextDraw(playerid, 495.700, 149.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][2], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][2], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][2], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][2], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][2], 1);

    ATRP_Phone[playerid][3] = CreatePlayerTextDraw(playerid, 495.700, 383.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][3], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][3], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][3], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][3], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][3], 1);

    ATRP_Phone[playerid][4] = CreatePlayerTextDraw(playerid, 416.700, 383.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][4], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][4], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][4], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][4], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][4], 1);

    ATRP_Phone[playerid][5] = CreatePlayerTextDraw(playerid, 438.000, 156.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][5], 77.000, 265.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][5], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][5], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][5], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][5], 1);

    ATRP_Phone[playerid][6] = CreatePlayerTextDraw(playerid, 419.700, 152.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][6], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][6], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][6], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][6], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][6], 1);

    ATRP_Phone[playerid][7] = CreatePlayerTextDraw(playerid, 499.700, 152.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][7], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][7], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][7], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][7], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][7], 1);

    ATRP_Phone[playerid][8] = CreatePlayerTextDraw(playerid, 499.700, 387.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][8], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][8], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][8], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][8], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][8], 1);

    ATRP_Phone[playerid][9] = CreatePlayerTextDraw(playerid, 419.700, 387.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][9], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][9], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][9], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][9], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][9], 1);

    ATRP_Phone[playerid][10] = CreatePlayerTextDraw(playerid, 438.000, 158.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][10], 77.000, 260.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][10], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][10], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][10], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][10], 1);

    ATRP_Phone[playerid][11] = CreatePlayerTextDraw(playerid, 425.000, 169.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][11], 102.500, 235.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][11], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][11], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][11], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][11], 1);

    ATRP_Phone[playerid][12] = CreatePlayerTextDraw(playerid, 461.000, 164.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][12], 30.500, 7.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][12], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][12], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][12], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][12], 1);

    ATRP_Phone[playerid][13] = CreatePlayerTextDraw(playerid, 456.000, 162.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][13], 10.000, 10.500);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][13], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][13], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][13], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][13], 1);

    ATRP_Phone[playerid][14] = CreatePlayerTextDraw(playerid, 486.000, 162.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][14], 10.000, 10.500);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][14], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][14], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][14], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][14], 1);

    ATRP_Phone[playerid][15] = CreatePlayerTextDraw(playerid, 475.000, 192.000, "18:00");
    PlayerTextDrawLetterSize(playerid, ATRP_Phone[playerid][15], 0.358, 1.500);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][15], 2);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][15], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][15], 150);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][15], 1);

    ATRP_Phone[playerid][16] = CreatePlayerTextDraw(playerid, 475.000, 207.000, "12 Febuary");
    PlayerTextDrawLetterSize(playerid, ATRP_Phone[playerid][16], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][16], 2);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][16], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][16], 150);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][16], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][16], 1);

    ATRP_Phone[playerid][17] = CreatePlayerTextDraw(playerid, 440.000, 166.000, "18:00");
    PlayerTextDrawLetterSize(playerid, ATRP_Phone[playerid][17], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][17], 2);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][17], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][17], 150);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][17], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][17], 1);

    ATRP_Phone[playerid][18] = CreatePlayerTextDraw(playerid, 513.000, 164.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][18], 9.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][18], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][18], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][18], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][18], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][18], 1);

    ATRP_Phone[playerid][19] = CreatePlayerTextDraw(playerid, 513.500, 165.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][19], 7.000, 2.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][19], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][19], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][19], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][19], 1);

    ATRP_Phone[playerid][20] = CreatePlayerTextDraw(playerid, 508.500, 165.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][20], 1.000, 5.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][20], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][20], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][20], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][20], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][20], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][20], 1);

    ATRP_Phone[playerid][21] = CreatePlayerTextDraw(playerid, 506.500, 166.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][21], 1.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][21], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][21], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][21], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][21], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][21], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][21], 1);

    ATRP_Phone[playerid][22] = CreatePlayerTextDraw(playerid, 505.000, 167.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][22], 1.000, 3.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][22], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][22], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][22], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][22], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][22], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][22], 1);

    ATRP_Phone[playerid][23] = CreatePlayerTextDraw(playerid, 450.000, 405.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][23], 56.000, 10.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][23], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][23], 0);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][23], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][23], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][23], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][23], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_Phone[playerid][23], 1);

    ATRP_Phone[playerid][24] = CreatePlayerTextDraw(playerid, 450.000, 409.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][24], 56.000, 3.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][24], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][24], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][24], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][24], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][24], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][24], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][24], 1);

    ATRP_Phone[playerid][25] = CreatePlayerTextDraw(playerid, 433.000, 237.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][25], 24.000, 26.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][25], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][25], -12254977);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][25], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][25], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][25], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][25], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][25], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_Phone[playerid][25], 1);

    ATRP_Phone[playerid][26] = CreatePlayerTextDraw(playerid, 463.000, 237.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][26], 24.000, 26.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][26], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][26], 2005441023);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][26], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][26], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][26], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][26], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][26], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_Phone[playerid][26], 1);

    ATRP_Phone[playerid][27] = CreatePlayerTextDraw(playerid, 493.000, 237.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][27], 24.000, 26.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][27], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][27], 2147418367);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][27], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][27], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][27], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][27], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][27], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_Phone[playerid][27], 1);

    ATRP_Phone[playerid][28] = CreatePlayerTextDraw(playerid, 433.000, 272.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][28], 24.000, 26.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][28], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][28], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][28], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][28], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][28], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][28], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][28], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_Phone[playerid][28], 1);

    ATRP_Phone[playerid][29] = CreatePlayerTextDraw(playerid, 463.000, 272.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][29], 24.000, 26.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][29], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][29], 2096890111);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][29], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][29], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][29], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][29], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][29], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_Phone[playerid][29], 1);

    ATRP_Phone[playerid][30] = CreatePlayerTextDraw(playerid, 493.000, 272.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][30], 24.000, 26.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][30], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][30], 10495);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][30], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][30], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][30], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][30], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][30], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_Phone[playerid][30], 1);

    ATRP_Phone[playerid][31] = CreatePlayerTextDraw(playerid, 493.000, 307.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][31], 24.000, 26.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][31], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][31], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][31], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][31], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][31], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][31], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][31], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_Phone[playerid][31], 1);

    ATRP_Phone[playerid][32] = CreatePlayerTextDraw(playerid, 463.000, 307.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][32], 24.000, 26.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][32], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][32], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][32], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][32], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][32], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][32], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][32], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_Phone[playerid][32], 1);

    ATRP_Phone[playerid][33] = CreatePlayerTextDraw(playerid, 433.000, 307.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][33], 24.000, 26.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][33], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][33], -1306385665);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][33], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][33], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][33], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][33], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][33], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_Phone[playerid][33], 1);

    ATRP_Phone[playerid][34] = CreatePlayerTextDraw(playerid, 433.000, 342.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][34], 24.000, 26.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][34], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][34], -2686721);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][34], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][34], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][34], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][34], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][34], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_Phone[playerid][34], 1);

    ATRP_Phone[playerid][35] = CreatePlayerTextDraw(playerid, 463.000, 342.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][35], 24.000, 26.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][35], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][35], 13554175);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][35], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][35], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][35], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][35], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][35], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_Phone[playerid][35], 1);

    ATRP_Phone[playerid][36] = CreatePlayerTextDraw(playerid, 493.000, 342.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][36], 24.000, 26.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][36], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][36], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][36], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][36], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][36], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][36], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][36], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_Phone[playerid][36], 1);

    ATRP_Phone[playerid][37] = CreatePlayerTextDraw(playerid, 431.000, 235.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][37], 28.000, 29.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][37], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][37], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][37], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][37], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][37], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][37], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][37], 1);

    ATRP_Phone[playerid][38] = CreatePlayerTextDraw(playerid, 432.000, 237.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][38], 26.000, 25.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][38], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][38], -12254977);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][38], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][38], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][38], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][38], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][38], 1);

    ATRP_Phone[playerid][39] = CreatePlayerTextDraw(playerid, 445.000, 239.000, "S");
    PlayerTextDrawLetterSize(playerid, ATRP_Phone[playerid][39], 0.388, 2.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][39], 2);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][39], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][39], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][39], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][39], 150);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][39], 2);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][39], 1);

    ATRP_Phone[playerid][40] = CreatePlayerTextDraw(playerid, 465.000, 239.000, "LD_DRV:silboat");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][40], 21.000, 21.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][40], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][40], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][40], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][40], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][40], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][40], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][40], 1);

    ATRP_Phone[playerid][41] = CreatePlayerTextDraw(playerid, 491.000, 235.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][41], 28.000, 29.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][41], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][41], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][41], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][41], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][41], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][41], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][41], 1);

    ATRP_Phone[playerid][42] = CreatePlayerTextDraw(playerid, 492.000, 237.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][42], 26.000, 25.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][42], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][42], 2147418367);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][42], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][42], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][42], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][42], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][42], 1);

    ATRP_Phone[playerid][43] = CreatePlayerTextDraw(playerid, 505.000, 239.000, "B");
    PlayerTextDrawLetterSize(playerid, ATRP_Phone[playerid][43], 0.388, 2.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][43], 2);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][43], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][43], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][43], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][43], 150);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][43], 2);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][43], 1);

    ATRP_Phone[playerid][44] = CreatePlayerTextDraw(playerid, 440.000, 275.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][44], 10.000, 12.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][44], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][44], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][44], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][44], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][44], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][44], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][44], 1);

    ATRP_Phone[playerid][45] = CreatePlayerTextDraw(playerid, 435.000, 284.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][45], 20.000, 12.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][45], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][45], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][45], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][45], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][45], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][45], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][45], 1);

    ATRP_Phone[playerid][46] = CreatePlayerTextDraw(playerid, 433.000, 291.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][46], 24.000, 6.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][46], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][46], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][46], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][46], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][46], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][46], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][46], 1);

    ATRP_Phone[playerid][47] = CreatePlayerTextDraw(playerid, 463.000, 271.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][47], 24.000, 25.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][47], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][47], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][47], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][47], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][47], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][47], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][47], 1);

    ATRP_Phone[playerid][48] = CreatePlayerTextDraw(playerid, 465.000, 271.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][48], 24.000, 21.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][48], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][48], 2096890111);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][48], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][48], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][48], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][48], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][48], 1);

    ATRP_Phone[playerid][49] = CreatePlayerTextDraw(playerid, 469.000, 277.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][49], 5.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][49], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][49], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][49], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][49], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][49], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][49], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][49], 1);

    ATRP_Phone[playerid][50] = CreatePlayerTextDraw(playerid, 477.000, 285.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][50], 5.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][50], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][50], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][50], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][50], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][50], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][50], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][50], 1);

    ATRP_Phone[playerid][51] = CreatePlayerTextDraw(playerid, 497.000, 273.000, "+");
    PlayerTextDrawLetterSize(playerid, ATRP_Phone[playerid][51], 0.300, 1.500);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][51], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][51], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][51], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][51], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][51], 150);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][51], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][51], 1);

    ATRP_Phone[playerid][52] = CreatePlayerTextDraw(playerid, 497.000, 281.000, "x");
    PlayerTextDrawLetterSize(playerid, ATRP_Phone[playerid][52], 0.300, 1.500);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][52], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][52], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][52], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][52], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][52], 150);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][52], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][52], 1);

    ATRP_Phone[playerid][53] = CreatePlayerTextDraw(playerid, 506.000, 282.000, "=");
    PlayerTextDrawLetterSize(playerid, ATRP_Phone[playerid][53], 0.300, 1.500);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][53], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][53], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][53], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][53], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][53], 150);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][53], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][53], 1);

    ATRP_Phone[playerid][54] = CreatePlayerTextDraw(playerid, 506.000, 273.000, "-");
    PlayerTextDrawLetterSize(playerid, ATRP_Phone[playerid][54], 0.509, 1.299);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][54], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][54], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][54], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][54], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][54], 150);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][54], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][54], 1);

    ATRP_Phone[playerid][55] = CreatePlayerTextDraw(playerid, 504.000, 308.000, "X");
    PlayerTextDrawLetterSize(playerid, ATRP_Phone[playerid][55], 0.388, 2.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][55], 2);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][55], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][55], 1);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][55], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][55], -1);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][55], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][55], 1);

    ATRP_Phone[playerid][56] = CreatePlayerTextDraw(playerid, 464.000, 307.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][56], 22.000, 20.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][56], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][56], 16711935);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][56], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][56], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][56], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][56], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][56], 1);

    ATRP_Phone[playerid][57] = CreatePlayerTextDraw(playerid, 463.000, 309.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][57], 24.000, 20.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][57], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][57], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][57], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][57], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][57], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][57], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][57], 1);

    ATRP_Phone[playerid][58] = CreatePlayerTextDraw(playerid, 466.000, 313.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][58], 18.000, 12.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][58], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][58], 16711935);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][58], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][58], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][58], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][58], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][58], 1);

    ATRP_Phone[playerid][59] = CreatePlayerTextDraw(playerid, 465.000, 315.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][59], 20.000, 12.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][59], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][59], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][59], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][59], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][59], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][59], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][59], 1);

    ATRP_Phone[playerid][60] = CreatePlayerTextDraw(playerid, 470.000, 319.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][60], 9.000, 5.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][60], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][60], 16711935);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][60], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][60], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][60], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][60], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][60], 1);

    ATRP_Phone[playerid][61] = CreatePlayerTextDraw(playerid, 439.000, 310.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][61], 12.000, 12.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][61], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][61], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][61], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][61], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][61], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][61], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][61], 1);

    ATRP_Phone[playerid][62] = CreatePlayerTextDraw(playerid, 440.000, 312.000, "V");
    PlayerTextDrawLetterSize(playerid, ATRP_Phone[playerid][62], 0.358, 1.799);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][62], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][62], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][62], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][62], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][62], 150);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][62], 2);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][62], 1);

    ATRP_Phone[playerid][63] = CreatePlayerTextDraw(playerid, 441.000, 313.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][63], 8.000, 12.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][63], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][63], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][63], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][63], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][63], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][63], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][63], 1);

    ATRP_Phone[playerid][64] = CreatePlayerTextDraw(playerid, 442.000, 313.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][64], 6.000, 7.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][64], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][64], -1306385665);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][64], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][64], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][64], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][64], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][64], 1);

    ATRP_Phone[playerid][65] = CreatePlayerTextDraw(playerid, 437.000, 345.000, "LD_CHAT:badchat");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][65], 16.000, 17.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][65], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][65], -65281);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][65], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][65], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][65], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][65], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][65], 1);

    ATRP_Phone[playerid][66] = CreatePlayerTextDraw(playerid, 470.000, 349.000, "HUD:radar_gangB");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][66], 10.000, 14.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][66], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][66], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][66], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][66], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][66], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][66], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][66], 1);

    ATRP_Phone[playerid][67] = CreatePlayerTextDraw(playerid, 466.000, 347.000, "HUD:radar_gangY");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][67], 9.000, 14.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][67], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][67], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][67], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][67], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][67], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][67], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][67], 1);

    ATRP_Phone[playerid][68] = CreatePlayerTextDraw(playerid, 475.000, 347.000, "HUD:radar_gangG");
    PlayerTextDrawTextSize(playerid, ATRP_Phone[playerid][68], 10.000, 14.000);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][68], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][68], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][68], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][68], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][68], 255);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][68], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][68], 1);

    ATRP_Phone[playerid][69] = CreatePlayerTextDraw(playerid, 502.000, 341.000, "!");
    PlayerTextDrawLetterSize(playerid, ATRP_Phone[playerid][69], 0.588, 2.598);
    PlayerTextDrawAlignment(playerid, ATRP_Phone[playerid][69], 1);
    PlayerTextDrawColor(playerid, ATRP_Phone[playerid][69], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_Phone[playerid][69], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_Phone[playerid][69], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_Phone[playerid][69], 150);
    PlayerTextDrawFont(playerid, ATRP_Phone[playerid][69], 2);
    PlayerTextDrawSetProportional(playerid, ATRP_Phone[playerid][69], 1);
}

ATRPhoneUnload(playerid)
{
    for(new i; i < 70; i++) PlayerTextDrawDestroy(playerid, ATRP_Phone[playerid][i]);
    return 1;
}

ATRPhoneCallLoad(playerid)
{
    ATRP_CallTD[playerid][0] = CreatePlayerTextDraw(playerid, 480.000, 148.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_CallTD[playerid][0], 42.000, 42.000);
    PlayerTextDrawAlignment(playerid, ATRP_CallTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, ATRP_CallTD[playerid][0], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_CallTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_CallTD[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_CallTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, ATRP_CallTD[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_CallTD[playerid][0], 1);

    ATRP_CallTD[playerid][1] = CreatePlayerTextDraw(playerid, 487.000, 170.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_CallTD[playerid][1], 115.000, 235.000);
    PlayerTextDrawAlignment(playerid, ATRP_CallTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, ATRP_CallTD[playerid][1], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_CallTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_CallTD[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_CallTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, ATRP_CallTD[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_CallTD[playerid][1], 1);

    ATRP_CallTD[playerid][2] = CreatePlayerTextDraw(playerid, 567.000, 148.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_CallTD[playerid][2], 42.000, 42.000);
    PlayerTextDrawAlignment(playerid, ATRP_CallTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, ATRP_CallTD[playerid][2], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_CallTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_CallTD[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_CallTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, ATRP_CallTD[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_CallTD[playerid][2], 1);

    ATRP_CallTD[playerid][3] = CreatePlayerTextDraw(playerid, 480.000, 385.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_CallTD[playerid][3], 42.000, 42.000);
    PlayerTextDrawAlignment(playerid, ATRP_CallTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, ATRP_CallTD[playerid][3], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_CallTD[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_CallTD[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_CallTD[playerid][3], 255);
    PlayerTextDrawFont(playerid, ATRP_CallTD[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_CallTD[playerid][3], 1);

    ATRP_CallTD[playerid][4] = CreatePlayerTextDraw(playerid, 567.000, 385.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_CallTD[playerid][4], 42.000, 42.000);
    PlayerTextDrawAlignment(playerid, ATRP_CallTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, ATRP_CallTD[playerid][4], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_CallTD[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_CallTD[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_CallTD[playerid][4], 255);
    PlayerTextDrawFont(playerid, ATRP_CallTD[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_CallTD[playerid][4], 1);

    ATRP_CallTD[playerid][5] = CreatePlayerTextDraw(playerid, 503.000, 155.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_CallTD[playerid][5], 84.000, 265.000);
    PlayerTextDrawAlignment(playerid, ATRP_CallTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, ATRP_CallTD[playerid][5], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_CallTD[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_CallTD[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_CallTD[playerid][5], 255);
    PlayerTextDrawFont(playerid, ATRP_CallTD[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_CallTD[playerid][5], 1);

    ATRP_CallTD[playerid][6] = CreatePlayerTextDraw(playerid, 484.000, 152.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_CallTD[playerid][6], 42.000, 42.000);
    PlayerTextDrawAlignment(playerid, ATRP_CallTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, ATRP_CallTD[playerid][6], 505753343);
    PlayerTextDrawSetShadow(playerid, ATRP_CallTD[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_CallTD[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_CallTD[playerid][6], 255);
    PlayerTextDrawFont(playerid, ATRP_CallTD[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_CallTD[playerid][6], 1);

    ATRP_CallTD[playerid][7] = CreatePlayerTextDraw(playerid, 491.000, 170.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_CallTD[playerid][7], 107.000, 229.000);
    PlayerTextDrawAlignment(playerid, ATRP_CallTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, ATRP_CallTD[playerid][7], 505753343);
    PlayerTextDrawSetShadow(playerid, ATRP_CallTD[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_CallTD[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_CallTD[playerid][7], 255);
    PlayerTextDrawFont(playerid, ATRP_CallTD[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_CallTD[playerid][7], 1);

    ATRP_CallTD[playerid][8] = CreatePlayerTextDraw(playerid, 563.000, 152.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_CallTD[playerid][8], 42.000, 42.000);
    PlayerTextDrawAlignment(playerid, ATRP_CallTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, ATRP_CallTD[playerid][8], 505753343);
    PlayerTextDrawSetShadow(playerid, ATRP_CallTD[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_CallTD[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_CallTD[playerid][8], 255);
    PlayerTextDrawFont(playerid, ATRP_CallTD[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_CallTD[playerid][8], 1);

    ATRP_CallTD[playerid][9] = CreatePlayerTextDraw(playerid, 563.000, 381.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_CallTD[playerid][9], 42.000, 42.000);
    PlayerTextDrawAlignment(playerid, ATRP_CallTD[playerid][9], 1);
    PlayerTextDrawColor(playerid, ATRP_CallTD[playerid][9], 505753343);
    PlayerTextDrawSetShadow(playerid, ATRP_CallTD[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_CallTD[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_CallTD[playerid][9], 255);
    PlayerTextDrawFont(playerid, ATRP_CallTD[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_CallTD[playerid][9], 1);

    ATRP_CallTD[playerid][10] = CreatePlayerTextDraw(playerid, 484.000, 381.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_CallTD[playerid][10], 42.000, 42.000);
    PlayerTextDrawAlignment(playerid, ATRP_CallTD[playerid][10], 1);
    PlayerTextDrawColor(playerid, ATRP_CallTD[playerid][10], 505753343);
    PlayerTextDrawSetShadow(playerid, ATRP_CallTD[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_CallTD[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_CallTD[playerid][10], 255);
    PlayerTextDrawFont(playerid, ATRP_CallTD[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_CallTD[playerid][10], 1);

    ATRP_CallTD[playerid][11] = CreatePlayerTextDraw(playerid, 504.000, 159.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_CallTD[playerid][11], 79.000, 256.000);
    PlayerTextDrawAlignment(playerid, ATRP_CallTD[playerid][11], 1);
    PlayerTextDrawColor(playerid, ATRP_CallTD[playerid][11], 505753343);
    PlayerTextDrawSetShadow(playerid, ATRP_CallTD[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_CallTD[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_CallTD[playerid][11], 255);
    PlayerTextDrawFont(playerid, ATRP_CallTD[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_CallTD[playerid][11], 1);

    ATRP_CallTD[playerid][12] = CreatePlayerTextDraw(playerid, 528.000, 166.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_CallTD[playerid][12], 15.000, 16.000);
    PlayerTextDrawAlignment(playerid, ATRP_CallTD[playerid][12], 1);
    PlayerTextDrawColor(playerid, ATRP_CallTD[playerid][12], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_CallTD[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_CallTD[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_CallTD[playerid][12], 255);
    PlayerTextDrawFont(playerid, ATRP_CallTD[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_CallTD[playerid][12], 1);

    ATRP_CallTD[playerid][13] = CreatePlayerTextDraw(playerid, 537.000, 169.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_CallTD[playerid][13], 17.000, 10.000);
    PlayerTextDrawAlignment(playerid, ATRP_CallTD[playerid][13], 1);
    PlayerTextDrawColor(playerid, ATRP_CallTD[playerid][13], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_CallTD[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_CallTD[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_CallTD[playerid][13], 255);
    PlayerTextDrawFont(playerid, ATRP_CallTD[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_CallTD[playerid][13], 1);

    ATRP_CallTD[playerid][14] = CreatePlayerTextDraw(playerid, 547.000, 166.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_CallTD[playerid][14], 15.000, 16.000);
    PlayerTextDrawAlignment(playerid, ATRP_CallTD[playerid][14], 1);
    PlayerTextDrawColor(playerid, ATRP_CallTD[playerid][14], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_CallTD[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_CallTD[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_CallTD[playerid][14], 255);
    PlayerTextDrawFont(playerid, ATRP_CallTD[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_CallTD[playerid][14], 1);

    CloseCallButton[playerid] = CreatePlayerTextDraw(playerid, 528.000, 401.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, CloseCallButton[playerid], 36.000, 8.000);
    PlayerTextDrawAlignment(playerid, CloseCallButton[playerid], 1);
    PlayerTextDrawColor(playerid, CloseCallButton[playerid], -1);
    PlayerTextDrawSetShadow(playerid, CloseCallButton[playerid], 0);
    PlayerTextDrawSetOutline(playerid, CloseCallButton[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, CloseCallButton[playerid], 255);
    PlayerTextDrawFont(playerid, CloseCallButton[playerid], 4);
    PlayerTextDrawSetProportional(playerid, CloseCallButton[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, CloseCallButton[playerid], 1);

    ContactNameTD[playerid] = CreatePlayerTextDraw(playerid, 545.000, 203.000, "Cecep_Sugeni");
    PlayerTextDrawLetterSize(playerid, ContactNameTD[playerid], 0.250, 1.500);
    PlayerTextDrawAlignment(playerid, ContactNameTD[playerid], 2);
    PlayerTextDrawColor(playerid, ContactNameTD[playerid], -1);
    PlayerTextDrawSetShadow(playerid, ContactNameTD[playerid], 0);
    PlayerTextDrawSetOutline(playerid, ContactNameTD[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, ContactNameTD[playerid], 150);
    PlayerTextDrawFont(playerid, ContactNameTD[playerid], 1);
    PlayerTextDrawSetProportional(playerid, ContactNameTD[playerid], 1);

    StatusDialingTD[playerid] = CreatePlayerTextDraw(playerid, 546.000, 222.000, "Panggilan masuk...");
    PlayerTextDrawLetterSize(playerid, StatusDialingTD[playerid], 0.250, 1.500);
    PlayerTextDrawAlignment(playerid, StatusDialingTD[playerid], 2);
    PlayerTextDrawColor(playerid, StatusDialingTD[playerid], -1);
    PlayerTextDrawSetShadow(playerid, StatusDialingTD[playerid], 0);
    PlayerTextDrawSetOutline(playerid, StatusDialingTD[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, StatusDialingTD[playerid], 150);
    PlayerTextDrawFont(playerid, StatusDialingTD[playerid], 1);
    PlayerTextDrawSetProportional(playerid, StatusDialingTD[playerid], 1);

    RedButtonoutComingCall[playerid] = CreatePlayerTextDraw(playerid, 527.000, 304.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, RedButtonoutComingCall[playerid], 38.000, 39.000);
    PlayerTextDrawAlignment(playerid, RedButtonoutComingCall[playerid], 1);
    PlayerTextDrawColor(playerid, RedButtonoutComingCall[playerid], -16776961);
    PlayerTextDrawSetShadow(playerid, RedButtonoutComingCall[playerid], 0);
    PlayerTextDrawSetOutline(playerid, RedButtonoutComingCall[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, RedButtonoutComingCall[playerid], 255);
    PlayerTextDrawFont(playerid, RedButtonoutComingCall[playerid], 4);
    PlayerTextDrawSetProportional(playerid, RedButtonoutComingCall[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, RedButtonoutComingCall[playerid], 1);
    
    RedButtonincomingCall[playerid] = CreatePlayerTextDraw(playerid, 501.000, 304.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, RedButtonincomingCall[playerid], 38.000, 39.000);
    PlayerTextDrawAlignment(playerid, RedButtonincomingCall[playerid], 1);
    PlayerTextDrawColor(playerid, RedButtonincomingCall[playerid], -16776961);
    PlayerTextDrawSetShadow(playerid, RedButtonincomingCall[playerid], 0);
    PlayerTextDrawSetOutline(playerid, RedButtonincomingCall[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, RedButtonincomingCall[playerid], 255);
    PlayerTextDrawFont(playerid, RedButtonincomingCall[playerid], 4);
    PlayerTextDrawSetProportional(playerid, RedButtonincomingCall[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, RedButtonincomingCall[playerid], 1);

    GreenButtonincomingCall[playerid] = CreatePlayerTextDraw(playerid, 551.000, 304.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, GreenButtonincomingCall[playerid], 38.000, 39.000);
    PlayerTextDrawAlignment(playerid, GreenButtonincomingCall[playerid], 1);
    PlayerTextDrawColor(playerid, GreenButtonincomingCall[playerid], 16744447);
    PlayerTextDrawSetShadow(playerid, GreenButtonincomingCall[playerid], 0);
    PlayerTextDrawSetOutline(playerid, GreenButtonincomingCall[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, GreenButtonincomingCall[playerid], 255);
    PlayerTextDrawFont(playerid, GreenButtonincomingCall[playerid], 4);
    PlayerTextDrawSetProportional(playerid, GreenButtonincomingCall[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, GreenButtonincomingCall[playerid], 1);
    return 1;
}

ATRPhoneCallUnload(playerid)
{
    for(new i; i < 15; i++) PlayerTextDrawDestroy(playerid, ATRP_CallTD[playerid][i]);
    PlayerTextDrawDestroy(playerid, CloseCallButton[playerid]);
    PlayerTextDrawDestroy(playerid, ContactNameTD[playerid]);
    PlayerTextDrawDestroy(playerid, StatusDialingTD[playerid]);
    PlayerTextDrawDestroy(playerid, RedButtonoutComingCall[playerid]);
    PlayerTextDrawDestroy(playerid, RedButtonincomingCall[playerid]);
    PlayerTextDrawDestroy(playerid, GreenButtonincomingCall[playerid]);
    return 1;
}

ATRPhoneBankLoad(playerid)
{
    ATRP_BankTD[playerid][0] = CreatePlayerTextDraw(playerid, 423.000, 171.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][0], 106.000, 235.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][0], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][0], 1);

    ATRP_BankTD[playerid][1] = CreatePlayerTextDraw(playerid, 416.700, 149.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][1], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][1], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][1], 1);

    ATRP_BankTD[playerid][2] = CreatePlayerTextDraw(playerid, 495.700, 149.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][2], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][2], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][2], 1);

    ATRP_BankTD[playerid][3] = CreatePlayerTextDraw(playerid, 495.700, 383.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][3], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][3], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][3], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][3], 1);

    ATRP_BankTD[playerid][4] = CreatePlayerTextDraw(playerid, 416.700, 383.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][4], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][4], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][4], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][4], 1);

    ATRP_BankTD[playerid][5] = CreatePlayerTextDraw(playerid, 438.000, 156.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][5], 77.000, 265.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][5], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][5], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][5], 1);

    ATRP_BankTD[playerid][6] = CreatePlayerTextDraw(playerid, 419.700, 152.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][6], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][6], 1018402559);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][6], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][6], 1);

    ATRP_BankTD[playerid][7] = CreatePlayerTextDraw(playerid, 499.700, 152.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][7], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][7], 1018402559);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][7], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][7], 1);

    ATRP_BankTD[playerid][8] = CreatePlayerTextDraw(playerid, 499.700, 387.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][8], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][8], 1018402559);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][8], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][8], 1);

    ATRP_BankTD[playerid][9] = CreatePlayerTextDraw(playerid, 419.700, 387.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][9], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][9], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][9], 1018402559);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][9], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][9], 1);

    ATRP_BankTD[playerid][10] = CreatePlayerTextDraw(playerid, 438.000, 158.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][10], 77.000, 260.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][10], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][10], 1018402559);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][10], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][10], 1);

    ATRP_BankTD[playerid][11] = CreatePlayerTextDraw(playerid, 425.000, 169.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][11], 102.500, 235.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][11], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][11], 1018402559);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][11], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][11], 1);

    ATRP_BankTD[playerid][12] = CreatePlayerTextDraw(playerid, 461.000, 164.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][12], 30.500, 7.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][12], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][12], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][12], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][12], 1);

    ATRP_BankTD[playerid][13] = CreatePlayerTextDraw(playerid, 456.000, 162.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][13], 10.000, 10.500);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][13], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][13], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][13], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][13], 1);

    ATRP_BankTD[playerid][14] = CreatePlayerTextDraw(playerid, 486.000, 162.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][14], 10.000, 10.500);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][14], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][14], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][14], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][14], 1);

    ATRP_BankTD[playerid][15] = CreatePlayerTextDraw(playerid, 440.000, 166.000, "18:00");
    PlayerTextDrawLetterSize(playerid, ATRP_BankTD[playerid][15], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][15], 2);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][15], 150);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][15], 1);

    ATRP_BankTD[playerid][16] = CreatePlayerTextDraw(playerid, 513.000, 164.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][16], 9.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][16], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][16], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][16], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][16], 1);

    ATRP_BankTD[playerid][17] = CreatePlayerTextDraw(playerid, 513.500, 165.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][17], 7.000, 2.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][17], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][17], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][17], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][17], 1);

    ATRP_BankTD[playerid][18] = CreatePlayerTextDraw(playerid, 508.500, 165.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][18], 1.000, 5.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][18], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][18], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][18], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][18], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][18], 1);

    ATRP_BankTD[playerid][19] = CreatePlayerTextDraw(playerid, 506.500, 166.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][19], 1.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][19], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][19], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][19], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][19], 1);

    ATRP_BankTD[playerid][20] = CreatePlayerTextDraw(playerid, 505.000, 167.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][20], 1.000, 3.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][20], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][20], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][20], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][20], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][20], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][20], 1);

    ATRP_BankTD[playerid][21] = CreatePlayerTextDraw(playerid, 450.000, 405.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][21], 56.000, 10.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][21], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][21], 0);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][21], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][21], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][21], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][21], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_BankTD[playerid][21], 1);

    ATRP_BankTD[playerid][22] = CreatePlayerTextDraw(playerid, 450.000, 409.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][22], 56.000, 3.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][22], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][22], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][22], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][22], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][22], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][22], 1);

    ATRP_BankTD[playerid][23] = CreatePlayerTextDraw(playerid, 430.000, 176.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][23], 7.000, 8.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][23], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][23], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][23], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][23], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][23], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][23], 1);

    ATRP_BankTD[playerid][24] = CreatePlayerTextDraw(playerid, 428.000, 182.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][24], 11.000, 8.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][24], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][24], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][24], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][24], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][24], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][24], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][24], 1);

    ATRP_BankTD[playerid][25] = CreatePlayerTextDraw(playerid, 439.000, 180.000, "Chess7");
    PlayerTextDrawLetterSize(playerid, ATRP_BankTD[playerid][25], 0.119, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][25], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][25], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][25], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][25], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][25], 150);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][25], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][25], 1);

    ATRP_BankTD[playerid][26] = CreatePlayerTextDraw(playerid, 468.000, 205.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][26], 17.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][26], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][26], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][26], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][26], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][26], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][26], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][26], 1);

    ATRP_BankTD[playerid][27] = CreatePlayerTextDraw(playerid, 482.000, 203.000, "/");
    PlayerTextDrawLetterSize(playerid, ATRP_BankTD[playerid][27], 0.419, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][27], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][27], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][27], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][27], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][27], 150);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][27], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][27], 1);

    ATRP_BankTD[playerid][28] = CreatePlayerTextDraw(playerid, 472.000, 203.000, "/");
    PlayerTextDrawLetterSize(playerid, ATRP_BankTD[playerid][28], -0.459, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][28], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][28], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][28], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][28], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][28], 150);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][28], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][28], 1);

    ATRP_BankTD[playerid][29] = CreatePlayerTextDraw(playerid, 466.000, 213.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][29], 17.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][29], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][29], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][29], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][29], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][29], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][29], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][29], 1);

    ATRP_BankTD[playerid][30] = CreatePlayerTextDraw(playerid, 479.000, 211.000, "/");
    PlayerTextDrawLetterSize(playerid, ATRP_BankTD[playerid][30], 0.419, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][30], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][30], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][30], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][30], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][30], 150);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][30], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][30], 1);

    ATRP_BankTD[playerid][31] = CreatePlayerTextDraw(playerid, 470.000, 211.000, "/");
    PlayerTextDrawLetterSize(playerid, ATRP_BankTD[playerid][31], -0.459, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][31], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][31], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][31], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][31], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][31], 150);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][31], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][31], 1);

    ATRP_BankTD[playerid][32] = CreatePlayerTextDraw(playerid, 480.000, 212.000, "/");
    PlayerTextDrawLetterSize(playerid, ATRP_BankTD[playerid][32], -0.649, 1.299);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][32], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][32], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][32], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][32], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][32], 150);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][32], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][32], 1);

    ATRP_BankTD[playerid][33] = CreatePlayerTextDraw(playerid, 475.000, 227.000, "District Bank");
    PlayerTextDrawLetterSize(playerid, ATRP_BankTD[playerid][33], 0.149, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][33], 2);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][33], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][33], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][33], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][33], 150);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][33], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][33], 1);

    ATRP_BankTD[playerid][34] = CreatePlayerTextDraw(playerid, 439.000, 265.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][34], 75.000, 15.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][34], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][34], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][34], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][34], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][34], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][34], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][34], 1);

    ATRP_BankTD[playerid][35] = CreatePlayerTextDraw(playerid, 439.000, 303.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][35], 75.000, 15.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][35], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][35], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][35], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][35], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][35], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][35], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][35], 1);

    ATRP_BankTD[playerid][36] = CreatePlayerTextDraw(playerid, 459.000, 342.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][36], 35.000, 39.000);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][36], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][36], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][36], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][36], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][36], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][36], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][36], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_BankTD[playerid][36], 1);

    ATRP_BankTD[playerid][37] = CreatePlayerTextDraw(playerid, 429.000, 299.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][37], 19.000, 21.799);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][37], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][37], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][37], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][37], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][37], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][37], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][37], 1);

    ATRP_BankTD[playerid][38] = CreatePlayerTextDraw(playerid, 504.000, 299.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][38], 19.000, 21.799);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][38], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][38], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][38], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][38], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][38], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][38], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][38], 1);

    ATRP_BankTD[playerid][39] = CreatePlayerTextDraw(playerid, 504.000, 261.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][39], 19.000, 21.799);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][39], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][39], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][39], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][39], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][39], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][39], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][39], 1);

    ATRP_BankTD[playerid][40] = CreatePlayerTextDraw(playerid, 428.000, 261.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_BankTD[playerid][40], 19.000, 21.799);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][40], 1);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][40], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][40], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][40], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][40], 255);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][40], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][40], 1);

    ATRP_BankTD[playerid][41] = CreatePlayerTextDraw(playerid, 475.000, 255.000, "No Rekening:");
    PlayerTextDrawLetterSize(playerid, ATRP_BankTD[playerid][41], 0.149, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][41], 2);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][41], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][41], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][41], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][41], 150);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][41], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][41], 1);

    ATRP_BankTD[playerid][42] = CreatePlayerTextDraw(playerid, 475.000, 292.000, "Uang:");
    PlayerTextDrawLetterSize(playerid, ATRP_BankTD[playerid][42], 0.149, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][42], 2);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][42], 16423679);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][42], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][42], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][42], 150);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][42], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][42], 1);

    ATRP_BankTD[playerid][43] = CreatePlayerTextDraw(playerid, 476.000, 268.000, "9999999");
    PlayerTextDrawLetterSize(playerid, ATRP_BankTD[playerid][43], 0.149, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][43], 2);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][43], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][43], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][43], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][43], 150);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][43], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][43], 1);

    ATRP_BankTD[playerid][44] = CreatePlayerTextDraw(playerid, 476.000, 307.000, "999999");
    PlayerTextDrawLetterSize(playerid, ATRP_BankTD[playerid][44], 0.149, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][44], 2);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][44], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][44], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][44], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][44], 150);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][44], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][44], 1);

    ATRP_BankTD[playerid][45] = CreatePlayerTextDraw(playerid, 476.000, 371.000, "V");
    PlayerTextDrawLetterSize(playerid, ATRP_BankTD[playerid][45], 0.388, -2.100);
    PlayerTextDrawAlignment(playerid, ATRP_BankTD[playerid][45], 2);
    PlayerTextDrawColor(playerid, ATRP_BankTD[playerid][45], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_BankTD[playerid][45], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_BankTD[playerid][45], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_BankTD[playerid][45], 150);
    PlayerTextDrawFont(playerid, ATRP_BankTD[playerid][45], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_BankTD[playerid][45], 1);
    return 1;
}

ATRPhoneBankUnload(playerid)
{
    for(new i; i < 46; i++) PlayerTextDrawDestroy(playerid, ATRP_BankTD[playerid][i]);
    return 1;
}

ATRPhoneSpotifyHomeLoad(playerid)
{
    ATRP_HomeSpotify[playerid][0] = CreatePlayerTextDraw(playerid, 423.000, 171.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][0], 106.000, 235.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][0], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][0], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][0], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][0], 1);

    ATRP_HomeSpotify[playerid][1] = CreatePlayerTextDraw(playerid, 416.700, 149.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][1], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][1], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][1], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][1], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][1], 1);

    ATRP_HomeSpotify[playerid][2] = CreatePlayerTextDraw(playerid, 495.700, 149.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][2], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][2], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][2], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][2], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][2], 1);

    ATRP_HomeSpotify[playerid][3] = CreatePlayerTextDraw(playerid, 495.700, 383.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][3], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][3], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][3], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][3], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][3], 1);

    ATRP_HomeSpotify[playerid][4] = CreatePlayerTextDraw(playerid, 416.700, 383.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][4], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][4], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][4], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][4], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][4], 1);

    ATRP_HomeSpotify[playerid][5] = CreatePlayerTextDraw(playerid, 438.000, 156.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][5], 77.000, 265.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][5], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][5], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][5], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][5], 1);

    ATRP_HomeSpotify[playerid][6] = CreatePlayerTextDraw(playerid, 419.700, 152.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][6], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][6], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][6], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][6], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][6], 1);

    ATRP_HomeSpotify[playerid][7] = CreatePlayerTextDraw(playerid, 499.700, 152.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][7], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][7], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][7], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][7], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][7], 1);

    ATRP_HomeSpotify[playerid][8] = CreatePlayerTextDraw(playerid, 499.700, 387.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][8], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][8], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][8], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][8], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][8], 1);

    ATRP_HomeSpotify[playerid][9] = CreatePlayerTextDraw(playerid, 419.700, 387.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][9], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][9], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][9], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][9], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][9], 1);

    ATRP_HomeSpotify[playerid][10] = CreatePlayerTextDraw(playerid, 438.000, 158.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][10], 77.000, 260.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][10], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][10], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][10], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][10], 1);

    ATRP_HomeSpotify[playerid][11] = CreatePlayerTextDraw(playerid, 425.000, 169.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][11], 102.500, 235.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][11], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][11], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][11], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][11], 1);

    ATRP_HomeSpotify[playerid][12] = CreatePlayerTextDraw(playerid, 461.000, 164.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][12], 30.500, 7.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][12], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][12], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][12], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][12], 1);

    ATRP_HomeSpotify[playerid][13] = CreatePlayerTextDraw(playerid, 456.000, 162.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][13], 10.000, 10.500);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][13], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][13], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][13], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][13], 1);

    ATRP_HomeSpotify[playerid][14] = CreatePlayerTextDraw(playerid, 486.000, 162.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][14], 10.000, 10.500);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][14], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][14], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][14], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][14], 1);

    ATRP_HomeSpotify[playerid][15] = CreatePlayerTextDraw(playerid, 440.000, 166.000, "18:00");
    PlayerTextDrawLetterSize(playerid, ATRP_HomeSpotify[playerid][15], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][15], 2);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][15], 150);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][15], 1);

    ATRP_HomeSpotify[playerid][16] = CreatePlayerTextDraw(playerid, 513.000, 164.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][16], 9.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][16], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][16], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][16], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][16], 1);

    ATRP_HomeSpotify[playerid][17] = CreatePlayerTextDraw(playerid, 513.500, 165.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][17], 7.000, 2.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][17], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][17], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][17], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][17], 1);

    ATRP_HomeSpotify[playerid][18] = CreatePlayerTextDraw(playerid, 508.500, 165.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][18], 1.000, 5.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][18], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][18], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][18], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][18], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][18], 1);

    ATRP_HomeSpotify[playerid][19] = CreatePlayerTextDraw(playerid, 506.500, 166.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][19], 1.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][19], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][19], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][19], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][19], 1);

    ATRP_HomeSpotify[playerid][20] = CreatePlayerTextDraw(playerid, 505.000, 167.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][20], 1.000, 3.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][20], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][20], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][20], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][20], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][20], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][20], 1);

    ATRP_HomeSpotify[playerid][21] = CreatePlayerTextDraw(playerid, 450.000, 405.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][21], 56.000, 10.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][21], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][21], 0);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][21], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][21], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][21], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][21], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_HomeSpotify[playerid][21], 1);

    ATRP_HomeSpotify[playerid][22] = CreatePlayerTextDraw(playerid, 450.000, 409.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][22], 56.000, 3.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][22], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][22], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][22], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][22], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][22], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][22], 1);

    ATRP_HomeSpotify[playerid][23] = CreatePlayerTextDraw(playerid, 465.000, 223.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][23], 24.000, 28.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][23], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][23], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][23], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][23], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][23], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][23], 1);

    ATRP_HomeSpotify[playerid][24] = CreatePlayerTextDraw(playerid, 468.000, 232.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][24], 18.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][24], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][24], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][24], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][24], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][24], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][24], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][24], 1);

    ATRP_HomeSpotify[playerid][25] = CreatePlayerTextDraw(playerid, 470.000, 236.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][25], 14.000, 3.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][25], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][25], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][25], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][25], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][25], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][25], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][25], 1);

    ATRP_HomeSpotify[playerid][26] = CreatePlayerTextDraw(playerid, 472.000, 239.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][26], 10.000, 3.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][26], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][26], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][26], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][26], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][26], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][26], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][26], 1);

    ATRP_HomeSpotify[playerid][27] = CreatePlayerTextDraw(playerid, 478.000, 258.000, "Jutaan lagu.");
    PlayerTextDrawLetterSize(playerid, ATRP_HomeSpotify[playerid][27], 0.240, 1.399);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][27], 2);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][27], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][27], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][27], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][27], 150);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][27], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][27], 1);

    ATRP_HomeSpotify[playerid][28] = CreatePlayerTextDraw(playerid, 478.000, 271.000, "Gratis di Spotify");
    PlayerTextDrawLetterSize(playerid, ATRP_HomeSpotify[playerid][28], 0.240, 1.399);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][28], 2);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][28], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][28], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][28], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][28], 150);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][28], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][28], 1);

    ATRP_HomeSpotify[playerid][29] = CreatePlayerTextDraw(playerid, 442.000, 339.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][29], 71.000, 13.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][29], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][29], 16711935);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][29], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][29], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][29], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][29], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][29], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_HomeSpotify[playerid][29], 1);

    ATRP_HomeSpotify[playerid][30] = CreatePlayerTextDraw(playerid, 442.000, 359.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][30], 71.000, 13.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][30], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][30], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][30], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][30], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][30], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][30], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][30], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_HomeSpotify[playerid][30], 1);

    ATRP_HomeSpotify[playerid][31] = CreatePlayerTextDraw(playerid, 435.000, 336.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][31], 15.000, 19.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][31], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][31], 16711935);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][31], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][31], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][31], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][31], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][31], 1);

    ATRP_HomeSpotify[playerid][32] = CreatePlayerTextDraw(playerid, 505.000, 336.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][32], 15.000, 19.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][32], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][32], 16711935);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][32], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][32], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][32], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][32], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][32], 1);

    ATRP_HomeSpotify[playerid][33] = CreatePlayerTextDraw(playerid, 434.000, 356.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][33], 15.000, 19.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][33], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][33], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][33], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][33], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][33], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][33], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][33], 1);

    ATRP_HomeSpotify[playerid][34] = CreatePlayerTextDraw(playerid, 505.000, 356.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_HomeSpotify[playerid][34], 15.000, 19.000);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][34], 1);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][34], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][34], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][34], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][34], 255);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][34], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][34], 1);

    ATRP_HomeSpotify[playerid][35] = CreatePlayerTextDraw(playerid, 478.000, 341.000, "Daftar Gratis");
    PlayerTextDrawLetterSize(playerid, ATRP_HomeSpotify[playerid][35], 0.140, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][35], 2);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][35], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][35], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][35], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][35], 150);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][35], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][35], 1);

    ATRP_HomeSpotify[playerid][36] = CreatePlayerTextDraw(playerid, 478.000, 361.000, "Masuk");
    PlayerTextDrawLetterSize(playerid, ATRP_HomeSpotify[playerid][36], 0.140, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_HomeSpotify[playerid][36], 2);
    PlayerTextDrawColor(playerid, ATRP_HomeSpotify[playerid][36], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_HomeSpotify[playerid][36], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_HomeSpotify[playerid][36], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_HomeSpotify[playerid][36], 150);
    PlayerTextDrawFont(playerid, ATRP_HomeSpotify[playerid][36], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_HomeSpotify[playerid][36], 1);
    return 1;
}

ATRPhoneSpotifyLoad(playerid)
{
    ATRP_SpotifyTD[playerid][0] = CreatePlayerTextDraw(playerid, 423.000, 171.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][0], 106.000, 235.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][0], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][0], 1);

    ATRP_SpotifyTD[playerid][1] = CreatePlayerTextDraw(playerid, 416.700, 149.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][1], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][1], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][1], 1);

    ATRP_SpotifyTD[playerid][2] = CreatePlayerTextDraw(playerid, 495.700, 149.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][2], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][2], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][2], 1);

    ATRP_SpotifyTD[playerid][3] = CreatePlayerTextDraw(playerid, 495.700, 383.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][3], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][3], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][3], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][3], 1);

    ATRP_SpotifyTD[playerid][4] = CreatePlayerTextDraw(playerid, 416.700, 383.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][4], 40.000, 45.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][4], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][4], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][4], 1);

    ATRP_SpotifyTD[playerid][5] = CreatePlayerTextDraw(playerid, 438.000, 156.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][5], 77.000, 265.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][5], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][5], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][5], 1);

    ATRP_SpotifyTD[playerid][6] = CreatePlayerTextDraw(playerid, 419.700, 152.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][6], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][6], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][6], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][6], 1);

    ATRP_SpotifyTD[playerid][7] = CreatePlayerTextDraw(playerid, 499.700, 152.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][7], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][7], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][7], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][7], 1);

    ATRP_SpotifyTD[playerid][8] = CreatePlayerTextDraw(playerid, 499.700, 387.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][8], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][8], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][8], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][8], 1);

    ATRP_SpotifyTD[playerid][9] = CreatePlayerTextDraw(playerid, 419.700, 387.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][9], 33.000, 37.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][9], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][9], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][9], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][9], 1);

    ATRP_SpotifyTD[playerid][10] = CreatePlayerTextDraw(playerid, 438.000, 158.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][10], 77.000, 260.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][10], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][10], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][10], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][10], 1);

    ATRP_SpotifyTD[playerid][11] = CreatePlayerTextDraw(playerid, 425.000, 169.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][11], 102.500, 235.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][11], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][11], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][11], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][11], 1);

    ATRP_SpotifyTD[playerid][12] = CreatePlayerTextDraw(playerid, 461.000, 164.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][12], 30.500, 7.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][12], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][12], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][12], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][12], 1);

    ATRP_SpotifyTD[playerid][13] = CreatePlayerTextDraw(playerid, 456.000, 162.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][13], 10.000, 10.500);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][13], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][13], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][13], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][13], 1);

    ATRP_SpotifyTD[playerid][14] = CreatePlayerTextDraw(playerid, 486.000, 162.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][14], 10.000, 10.500);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][14], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][14], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][14], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][14], 1);

    ATRP_SpotifyTD[playerid][15] = CreatePlayerTextDraw(playerid, 440.000, 166.000, "18:00");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][15], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][15], 2);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][15], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][15], 1);

    ATRP_SpotifyTD[playerid][16] = CreatePlayerTextDraw(playerid, 513.000, 164.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][16], 9.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][16], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][16], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][16], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][16], 1);

    ATRP_SpotifyTD[playerid][17] = CreatePlayerTextDraw(playerid, 513.500, 165.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][17], 7.000, 2.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][17], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][17], 512819199);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][17], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][17], 1);

    ATRP_SpotifyTD[playerid][18] = CreatePlayerTextDraw(playerid, 508.500, 165.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][18], 1.000, 5.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][18], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][18], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][18], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][18], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][18], 1);

    ATRP_SpotifyTD[playerid][19] = CreatePlayerTextDraw(playerid, 506.500, 166.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][19], 1.000, 4.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][19], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][19], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][19], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][19], 1);

    ATRP_SpotifyTD[playerid][20] = CreatePlayerTextDraw(playerid, 505.000, 167.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][20], 1.000, 3.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][20], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][20], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][20], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][20], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][20], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][20], 1);

    ATRP_SpotifyTD[playerid][21] = CreatePlayerTextDraw(playerid, 450.000, 405.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][21], 56.000, 10.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][21], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][21], 0);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][21], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][21], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][21], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][21], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_SpotifyTD[playerid][21], 1);

    ATRP_SpotifyTD[playerid][22] = CreatePlayerTextDraw(playerid, 450.000, 409.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][22], 56.000, 3.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][22], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][22], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][22], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][22], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][22], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][22], 1);

    ATRP_SpotifyTD[playerid][23] = CreatePlayerTextDraw(playerid, 431.500, 182.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][23], 7.000, 7.500);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][23], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][23], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][23], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][23], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][23], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][23], 1);

    ATRP_SpotifyTD[playerid][24] = CreatePlayerTextDraw(playerid, 429.000, 188.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][24], 12.500, 7.500);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][24], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][24], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][24], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][24], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][24], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][24], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][24], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_SpotifyTD[playerid][24], 1);

    ATRP_SpotifyTD[playerid][25] = CreatePlayerTextDraw(playerid, 441.000, 186.000, "Chess7");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][25], 0.129, 0.799);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][25], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][25], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][25], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][25], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][25], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][25], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][25], 1);

    ATRP_SpotifyTD[playerid][26] = CreatePlayerTextDraw(playerid, 429.000, 219.000, "Sering kamu putar baru-baru ini");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][26], 0.139, 0.999);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][26], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][26], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][26], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][26], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][26], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][26], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][26], 1);

    ATRP_SpotifyTD[playerid][27] = CreatePlayerTextDraw(playerid, 428.000, 231.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][27], 96.000, 24.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][27], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][27], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][27], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][27], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][27], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][27], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][27], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_SpotifyTD[playerid][27], 1);

    ATRP_SpotifyTD[playerid][28] = CreatePlayerTextDraw(playerid, 428.000, 256.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][28], 96.000, 24.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][28], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][28], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][28], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][28], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][28], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][28], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][28], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_SpotifyTD[playerid][28], 1);

    ATRP_SpotifyTD[playerid][29] = CreatePlayerTextDraw(playerid, 428.000, 280.500, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][29], 96.000, 24.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][29], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][29], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][29], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][29], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][29], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][29], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][29], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_SpotifyTD[playerid][29], 1);

    ATRP_SpotifyTD[playerid][30] = CreatePlayerTextDraw(playerid, 428.000, 305.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][30], 96.000, 24.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][30], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][30], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][30], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][30], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][30], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][30], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][30], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_SpotifyTD[playerid][30], 1);

    ATRP_SpotifyTD[playerid][31] = CreatePlayerTextDraw(playerid, 428.000, 329.500, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][31], 96.000, 24.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][31], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][31], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][31], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][31], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][31], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][31], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][31], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_SpotifyTD[playerid][31], 1);

    ATRP_SpotifyTD[playerid][32] = CreatePlayerTextDraw(playerid, 428.000, 354.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][32], 96.000, 24.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][32], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][32], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][32], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][32], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][32], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][32], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][32], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_SpotifyTD[playerid][32], 1);

    ATRP_SpotifyTD[playerid][33] = CreatePlayerTextDraw(playerid, 432.000, 236.000, "HUD:radar_dateDisco");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][33], 12.000, 14.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][33], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][33], 16711935);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][33], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][33], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][33], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][33], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][33], 1);

    ATRP_SpotifyTD[playerid][34] = CreatePlayerTextDraw(playerid, 432.000, 261.000, "HUD:radar_dateDisco");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][34], 12.000, 14.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][34], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][34], 16711935);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][34], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][34], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][34], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][34], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][34], 1);

    ATRP_SpotifyTD[playerid][35] = CreatePlayerTextDraw(playerid, 432.000, 285.000, "HUD:radar_dateDisco");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][35], 12.000, 14.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][35], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][35], 16711935);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][35], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][35], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][35], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][35], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][35], 1);

    ATRP_SpotifyTD[playerid][36] = CreatePlayerTextDraw(playerid, 432.000, 310.000, "HUD:radar_dateDisco");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][36], 12.000, 14.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][36], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][36], 16711935);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][36], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][36], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][36], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][36], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][36], 1);

    ATRP_SpotifyTD[playerid][37] = CreatePlayerTextDraw(playerid, 432.000, 334.000, "HUD:radar_dateDisco");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][37], 12.000, 14.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][37], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][37], 16711935);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][37], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][37], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][37], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][37], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][37], 1);

    ATRP_SpotifyTD[playerid][38] = CreatePlayerTextDraw(playerid, 432.000, 359.000, "HUD:radar_dateDisco");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][38], 12.000, 14.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][38], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][38], 16711935);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][38], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][38], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][38], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][38], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][38], 1);

    ATRP_SpotifyTD[playerid][39] = CreatePlayerTextDraw(playerid, 478.000, 238.000, "Judul: Isabella");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][39], 0.129, 0.899);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][39], 2);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][39], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][39], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][39], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][39], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][39], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][39], 1);

    ATRP_SpotifyTD[playerid][40] = CreatePlayerTextDraw(playerid, 478.000, 264.000, "Judul: Isabella");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][40], 0.129, 0.899);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][40], 2);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][40], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][40], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][40], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][40], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][40], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][40], 1);

    ATRP_SpotifyTD[playerid][41] = CreatePlayerTextDraw(playerid, 478.000, 288.000, "Judul: Isabella");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][41], 0.129, 0.899);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][41], 2);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][41], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][41], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][41], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][41], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][41], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][41], 1);

    ATRP_SpotifyTD[playerid][42] = CreatePlayerTextDraw(playerid, 478.000, 312.000, "Judul: Isabella");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][42], 0.129, 0.899);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][42], 2);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][42], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][42], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][42], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][42], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][42], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][42], 1);

    ATRP_SpotifyTD[playerid][43] = CreatePlayerTextDraw(playerid, 478.000, 336.000, "Judul: Isabella");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][43], 0.129, 0.899);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][43], 2);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][43], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][43], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][43], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][43], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][43], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][43], 1);

    ATRP_SpotifyTD[playerid][44] = CreatePlayerTextDraw(playerid, 478.000, 360.000, "Judul: Isabella");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][44], 0.129, 0.899);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][44], 2);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][44], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][44], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][44], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][44], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][44], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][44], 1);

    ATRP_SpotifyTD[playerid][45] = CreatePlayerTextDraw(playerid, 518.000, 235.000, ":");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][45], 0.209, 1.299);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][45], 2);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][45], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][45], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][45], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][45], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][45], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][45], 1);

    ATRP_SpotifyTD[playerid][46] = CreatePlayerTextDraw(playerid, 518.000, 261.000, ":");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][46], 0.209, 1.299);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][46], 2);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][46], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][46], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][46], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][46], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][46], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][46], 1);

    ATRP_SpotifyTD[playerid][47] = CreatePlayerTextDraw(playerid, 518.000, 285.000, ":");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][47], 0.209, 1.299);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][47], 2);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][47], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][47], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][47], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][47], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][47], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][47], 1);

    ATRP_SpotifyTD[playerid][48] = CreatePlayerTextDraw(playerid, 518.000, 309.000, ":");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][48], 0.209, 1.299);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][48], 2);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][48], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][48], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][48], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][48], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][48], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][48], 1);

    ATRP_SpotifyTD[playerid][49] = CreatePlayerTextDraw(playerid, 518.000, 333.000, ":");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][49], 0.209, 1.299);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][49], 2);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][49], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][49], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][49], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][49], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][49], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][49], 1);

    ATRP_SpotifyTD[playerid][50] = CreatePlayerTextDraw(playerid, 518.000, 357.000, ":");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][50], 0.209, 1.299);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][50], 2);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][50], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][50], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][50], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][50], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][50], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][50], 1);

    ATRP_SpotifyTD[playerid][51] = CreatePlayerTextDraw(playerid, 447.000, 385.100, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][51], 61.500, 10.000);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][51], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][51], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][51], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][51], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][51], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][51], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][51], 1);

    ATRP_SpotifyTD[playerid][52] = CreatePlayerTextDraw(playerid, 447.500, 386.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][52], 60.500, 8.500);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][52], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][52], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][52], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][52], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][52], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][52], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][52], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_SpotifyTD[playerid][52], 1);

    ATRP_SpotifyTD[playerid][53] = CreatePlayerTextDraw(playerid, 449.500, 386.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][53], 6.000, 7.500);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][53], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][53], 892679679);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][53], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][53], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][53], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][53], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][53], 1);

    ATRP_SpotifyTD[playerid][54] = CreatePlayerTextDraw(playerid, 451.500, 388.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, ATRP_SpotifyTD[playerid][54], 2.000, 3.500);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][54], 1);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][54], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][54], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][54], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][54], 255);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][54], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][54], 1);

    ATRP_SpotifyTD[playerid][55] = CreatePlayerTextDraw(playerid, 454.000, 390.000, "/");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][55], -0.190, 0.298);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][55], 2);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][55], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][55], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][55], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][55], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][55], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][55], 1);

    ATRP_SpotifyTD[playerid][56] = CreatePlayerTextDraw(playerid, 478.000, 387.000, "Search");
    PlayerTextDrawLetterSize(playerid, ATRP_SpotifyTD[playerid][56], 0.129, 0.598);
    PlayerTextDrawAlignment(playerid, ATRP_SpotifyTD[playerid][56], 2);
    PlayerTextDrawColor(playerid, ATRP_SpotifyTD[playerid][56], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_SpotifyTD[playerid][56], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_SpotifyTD[playerid][56], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_SpotifyTD[playerid][56], 150);
    PlayerTextDrawFont(playerid, ATRP_SpotifyTD[playerid][56], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_SpotifyTD[playerid][56], 1);

    return 1;
}

ATRPhoneSpotifyUnload(playerid)
{
    for(new i; i < 57; i++) PlayerTextDrawDestroy(playerid, ATRP_SpotifyTD[playerid][i]);
    return 1;
}

ATRPhoneSpotifyHomeUnload(playerid)
{
    for(new i; i < 37; i++) PlayerTextDrawDestroy(playerid, ATRP_HomeSpotify[playerid][i]);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    if (IsValidDynamicMapIcon(SharelocSender[playerid]))
    {
        DestroyDynamicMapIcon(SharelocSender[playerid]);
        SharelocSender[playerid] = INVALID_STREAMER_ID;
    }
    ATRPhoneLoad(playerid);
    ATRPhoneCallLoad(playerid);
    ATRPhoneBankLoad(playerid);
    ATRPhoneSpotifyLoad(playerid);
    ATRPhoneSpotifyHomeLoad(playerid);
    ATRPhoneTwitterHomepageLoad(playerid);
    ATRPhoneTwitterHomeLoad(playerid);
    ATRPPhoneTwitterPostLoad(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if (IsValidDynamicMapIcon(SharelocSender[playerid]))
    {
        DestroyDynamicMapIcon(SharelocSender[playerid]);
        SharelocSender[playerid] = INVALID_STREAMER_ID;
        SharelocTimer[playerid] = 0;
    }
    ATRPhoneUnload(playerid);
    ATRPhoneCallUnload(playerid);
    ATRPhoneBankUnload(playerid);
    ATRPhoneSpotifyUnload(playerid);
    ATRPhoneSpotifyHomeUnload(playerid);
    ATRPhoneTwitterHomepageUnload(playerid);
    ATRPhoneTwitterHomeUnload(playerid);
    ATRPPhoneTwitterPostUnload(playerid);
    return 1;
}

Toggle_PhoneTD(playerid, bool:toggle)
{
    if(!toggle)
    {
        for(new i; i < 70; i++) PlayerTextDrawHide(playerid, ATRP_Phone[playerid][i]);
        ShowHbeTextdraws(playerid, AccountData[playerid][pHUDMode]);
    }
    else
    {
        for(new i; i < 70; i++) PlayerTextDrawShow(playerid, ATRP_Phone[playerid][i]);
        for(new x = 0; x < 15; x ++) PlayerTextDrawHide(playerid, HbeStuffs[playerid][x]);
        HideHBE(playerid);
    }
    return 1;
}

Toggle_CallTD(playerid, bool:toggle)
{
    if(!toggle)
    {
        for(new i; i < 15; i++) PlayerTextDrawHide(playerid, ATRP_CallTD[playerid][i]);
        PlayerTextDrawHide(playerid, CloseCallButton[playerid]);
        PlayerTextDrawHide(playerid, ContactNameTD[playerid]);
        PlayerTextDrawHide(playerid, StatusDialingTD[playerid]);
    }
    else
    {
        for(new i; i < 15; i++) PlayerTextDrawShow(playerid, ATRP_CallTD[playerid][i]);
        PlayerTextDrawShow(playerid, CloseCallButton[playerid]);
        PlayerTextDrawShow(playerid, ContactNameTD[playerid]);
        PlayerTextDrawShow(playerid, StatusDialingTD[playerid]);
    }
    return 1;
}

Toggle_BankTD(playerid, bool:toggle)
{
    if(!toggle)
    {
        for(new i; i < 46; i++) PlayerTextDrawHide(playerid, ATRP_BankTD[playerid][i]);
    }
    else
    {
        PlayerTextDrawSetString(playerid, ATRP_BankTD[playerid][43], sprintf("%d", AccountData[playerid][pBankRek]));
        PlayerTextDrawSetString(playerid, ATRP_BankTD[playerid][44], sprintf("%s", FormatMoney(AccountData[playerid][pBankMoney])));
        PlayerTextDrawSetString(playerid, ATRP_BankTD[playerid][25], sprintf("%s", AccountData[playerid][pName]));
        for(new i; i < 46; i++) PlayerTextDrawShow(playerid, ATRP_BankTD[playerid][i]);
        for(new x = 0; x < 15; x ++) PlayerTextDrawHide(playerid, HbeStuffs[playerid][x]);
        HideHBE(playerid);
    }
    return 1;
}


Toggle_SpotifyHomeTD(playerid, bool:toggle)
{
    if(!toggle)
    {
        for(new i; i < 37; i++) PlayerTextDrawHide(playerid, ATRP_HomeSpotify[playerid][i]);
    }
    else
    {
        for(new i; i < 37; i++) PlayerTextDrawShow(playerid, ATRP_HomeSpotify[playerid][i]);
        for(new x = 0; x < 15; x ++) PlayerTextDrawHide(playerid, HbeStuffs[playerid][x]);
        HideHBE(playerid);
    }
}

Toggle_SpotifyTD(playerid, bool:toggle)
{
    if(!toggle)
    {
        for(new i; i < 57; i++) PlayerTextDrawHide(playerid, ATRP_SpotifyTD[playerid][i]);
    }
    else
    {
        //for(new i; i < 57; i++) PlayerTextDrawShow(playerid, ATRP_SpotifyTD[playerid][i]);
        Spotify_LoadHistory(playerid);
        PlayerTextDrawSetString(playerid, ATRP_SpotifyTD[playerid][25], sprintf("%s", AccountData[playerid][SpotifyName]));
        for(new x = 0; x < 15; x ++) PlayerTextDrawHide(playerid, HbeStuffs[playerid][x]);
        HideHBE(playerid);
    }
    return 1;
}

Toggle_TwitterHome(playerid, bool:toggle)
{
    if(!toggle)
    {
        for(new i; i < 33; i++) PlayerTextDrawHide(playerid, ATRP_TwitterHomeTD[playerid][i]);
    }
    else
    {
        for(new i; i < 33; i++) PlayerTextDrawShow(playerid, ATRP_TwitterHomeTD[playerid][i]);
        for(new x = 0; x < 15; x ++) PlayerTextDrawHide(playerid, HbeStuffs[playerid][x]);
        HideHBE(playerid);
    }
    return 1;
}

Toggle_TwitterHomepage(playerid, bool:toggle)
{
    if(!toggle)
    {
        for(new i; i < 58; i++) PlayerTextDrawHide(playerid, ATRP_TwitterHomepageTD[playerid][i]);
    }
    else
    {
        PlayerTextDrawSetString(playerid, ATRP_TwitterHomepageTD[playerid][25], sprintf("%s", AccountData[playerid][TwitterName]));
        ShowPlayerTwitterPageV1(playerid, 0);
        printf("[DEBUG] Menampilkan Layout Twitter (0-36)...");
        for(new x = 0; x < 15; x ++) PlayerTextDrawHide(playerid, HbeStuffs[playerid][x]);
        HideHBE(playerid);
    }
    return 1;
}

HideAllSmartphone(playerid)
{
    Toggle_PhoneTD(playerid, false);
    Toggle_BankTD(playerid, false);
    Toggle_SpotifyTD(playerid, false);
    Toggle_TwitterHome(playerid, false);
    Toggle_TwitterHomepage(playerid, false);
    return 1;
}

ShowingSmartphone(playerid)
{
    if (IsPlayerInWater(playerid))
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membuka Smartphone di dalam air!");
    }

    if(!PlayerHasItem(playerid, "Smartphone"))
    {
        CancelSelectTextDraw(playerid);
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Smartphone!");
    }
    
    if(AccountData[playerid][pInjured])   
    {
        CancelSelectTextDraw(playerid);
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak bisa melakukannya saat ini!");
    }

    if(!AccountData[playerid][phoneShown])
    {
        SendRPMeAboveHead(playerid, "Membuka HP Miliknya", X11_PLUM1);
        if(AccountData[playerid][phoneDurringConversation] && AccountData[playerid][phoneCallingWithPlayerID] != INVALID_PLAYER_ID)
        {
            new otherid = AccountData[playerid][phoneCallingWithPlayerID];
            PlayerTextDrawSetString(playerid, ContactNameTD[playerid], sprintf("%s", GetMySavedContactName(playerid, AccountData[otherid][pPhone])));
            Toggle_CallTD(playerid, true);
            PlayerTextDrawShow(playerid, RedButtonoutComingCall[playerid]);
            AccountData[playerid][phoneShown] = true;
            return 1;
        }

        if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            ApplyAnimation(playerid, "ped", "Jetpack_Idle", 4.1, 0, 0, 0, 1, 0, 1);
            SetPlayerAttachedObject(playerid, 9, 18870, 5, 0.043000, 0.022999, -0.006000, -112.000022, -34.900020, -8.500002, 1.000000, 1.000000, 1.000000);    
        }
        Toggle_PhoneTD(playerid, true);
        AccountData[playerid][phoneShown] = true;
        SelectTextDraw(playerid, X11_DEEPSKYBLUE1);
    }
    else 
    {
        AccountData[playerid][phoneShown] = false;
        Inventory_Close(playerid);
        CancelSelectTextDraw(playerid);
    }

    return 1;
}

CutCallingLine(playerid)
{
    new inlinewithplayerID = AccountData[playerid][phoneCallingWithPlayerID];
    AccountData[playerid][phoneIncomingCall] = false;
    AccountData[playerid][phoneDurringConversation] = false;
    AccountData[playerid][phoneCallingTime] = 0;
    
    if(IsPlayerConnected(inlinewithplayerID))
    {
        AccountData[inlinewithplayerID][phoneCallingWithPlayerID] = INVALID_PLAYER_ID;
        AccountData[inlinewithplayerID][phoneIncomingCall] = false;
        AccountData[inlinewithplayerID][phoneDurringConversation] = false;
        AccountData[inlinewithplayerID][phoneCallingTime] = 0;

        SendRPMeAboveHead(inlinewithplayerID, "Menutup HP miliknya.", X11_PLUM);

        if(!IsPlayerInAnyVehicle(inlinewithplayerID) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            ClearAnimations(inlinewithplayerID, 1);
            StopLoopingAnim(inlinewithplayerID);
            ApplyAnimation(inlinewithplayerID, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
        }
        RemovePlayerAttachedObject(inlinewithplayerID, 9);
        HideAllSmartphone(inlinewithplayerID);
        Toggle_CallTD(inlinewithplayerID, false);
        PlayerTextDrawHide(inlinewithplayerID, GreenButtonincomingCall[inlinewithplayerID]);
        PlayerTextDrawHide(inlinewithplayerID, RedButtonincomingCall[inlinewithplayerID]);
        PlayerTextDrawHide(inlinewithplayerID, RedButtonoutComingCall[inlinewithplayerID]);
        if(AccountData[inlinewithplayerID][phoneShown]) 
        {
            AccountData[inlinewithplayerID][phoneShown] = false;
        }
        CallRemoteFunction("DisconnectPlayerCalling", "dd", playerid, inlinewithplayerID);
        Info(inlinewithplayerID, "Telepon terputus...");
    }
    return 1;
}

forward OnOutcomingCall(playerid, const targetnumber[]);
public OnOutcomingCall(playerid, const targetnumber[])
{
    HideAllSmartphone(playerid);

    new contnstr[25];
    format(contnstr, sizeof(contnstr), "%s", targetnumber);
    for(new cid; cid < MAX_CONTACTS; ++cid)
    {
        if(ContactData[playerid][cid][contactExists])
        {
            if(!strcmp(ContactData[playerid][cid][contactNumber], targetnumber, false))
            {
                format(contnstr, sizeof(contnstr), "%s", ContactData[playerid][cid][contactName]);
            }
        }
    }
    PlayerTextDrawSetString(playerid, ContactNameTD[playerid], contnstr);
    PlayerTextDrawSetString(playerid, StatusDialingTD[playerid], "Berdering...");

    new targetnumberownerid = GetNumberOwner(targetnumber);
    if(IsPlayerConnected(targetnumberownerid) && targetnumberownerid != INVALID_PLAYER_ID)
    {
        if(AccountData[targetnumberownerid][phoneAirplaneMode])
        {
            PlayerTextDrawSetString(playerid, StatusDialingTD[playerid], "Nomor tidak aktif...");
            AccountData[playerid][phoneIncomingCall] = true;
        }
        else if(AccountData[targetnumberownerid][phoneIncomingCall] || AccountData[targetnumberownerid][phoneDurringConversation])
        {
            PlayerTextDrawSetString(playerid, StatusDialingTD[playerid], "Panggilan sedang sibuk...");
            AccountData[playerid][phoneIncomingCall] = true;
        }
        else
        {
            AccountData[playerid][phoneCallingWithPlayerID] = targetnumberownerid;
            AccountData[playerid][phoneIncomingCall] = false;
            OnIncomingCall(targetnumberownerid, AccountData[playerid][pPhone]);
        }
    }
    ApplyAnimation(playerid, "ped", "phone_talk", 3.1, 0, 1, 0, 1, 1, 1);
    RemovePlayerAttachedObject(playerid, 9);
    SetPlayerAttachedObject(playerid, 9, 18870, 6,  0.099000, 0.009999, 0.000000,  78.200027, 179.000061, -1.500000,  1.000000, 1.000000, 1.000000); // 276
    Toggle_CallTD(playerid, true);
    PlayerTextDrawShow(playerid, RedButtonoutComingCall[playerid]);
    return 1;
}

forward OnIncomingCall(playerid, const fromnumber[]);
public OnIncomingCall(playerid, const fromnumber[])
{
    HideAllSmartphone(playerid);

    new contnstr[25];
    format(contnstr, sizeof(contnstr), "%s", fromnumber);
    for(new cid; cid < MAX_CONTACTS; ++cid)
    {
        if(ContactData[playerid][cid][contactExists])
        {
            if(!strcmp(ContactData[playerid][cid][contactNumber], fromnumber, false))
            {
                format(contnstr, sizeof(contnstr), "%s", ContactData[playerid][cid][contactName]);
            }
        }
    }
    if(!AccountData[playerid][phoneShown]) 
        AccountData[playerid][phoneShown] = true;

    PlayerTextDrawSetString(playerid, ContactNameTD[playerid], contnstr);
    PlayerTextDrawSetString(playerid, StatusDialingTD[playerid], "Panggilan masuk...");
    PlayAudioStreamForPlayer(playerid, AccountData[playerid][phoneCallRingtone], 0.0, 0.0, 0.0, 30.0, 0); // Memulai Nada Dering Sendiri

    for(new i; i < 15; i++) PlayerTextDrawShow(playerid, ATRP_CallTD[playerid][i]);
    PlayerTextDrawShow(playerid, CloseCallButton[playerid]);
    PlayerTextDrawShow(playerid, ContactNameTD[playerid]);
    PlayerTextDrawShow(playerid, StatusDialingTD[playerid]);
    PlayerTextDrawShow(playerid, RedButtonincomingCall[playerid]);
    PlayerTextDrawShow(playerid, GreenButtonincomingCall[playerid]);
    SelectTextDraw(playerid, 0xFF9999FF);
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_SPOTIFY_SIGN:
        {
            if(!response) return 1;
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_SPOTIFY_SIGN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Daftar Spotify", "Error: Tidak dapat diisi kosong!\nHai, selamat datang di Spotify!\
            \nSilahkan masukkan username Spotify kamu, ini akan ditampilkan pada setiap daftar atau aktivitas musik kamu:\
            \nIngat: Username hanya dapat berupa huruf dan angka, tidak menggunakan simbol!\
            \nPanjang username 7 - 24 karakter!", "Set", "Batal");

            if(strlen(inputtext) < 7 || strlen(inputtext) > 24) return ShowPlayerDialog(playerid, DIALOG_SPOTIFY_SIGN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Daftar Spotify", "Error: Nama tidak dapat kurang dari 7 huruf atau lebih dari 24!\nHai, selamat datang di Spotify!\
            \nSilahkan masukkan username Spotify kamu, ini akan ditampilkan pada setiap daftar atau aktivitas musik kamu:\
            \nIngat: Username hanya dapat berupa huruf dan angka, tidak menggunakan simbol!\
            \nPanjang username 7 - 24 karakter!", "Set", "Batal");

            format(AccountData[playerid][pTempText], 24, inputtext);
            ShowPlayerDialog(playerid, DIALOG_SPOTIFY_SIGNPASSWORD, DIALOG_STYLE_PASSWORD, ""TCRP"District  "WHITE"- Daftar Spotify",
            sprintf("Hai %s!\nSilahkan masukkan kata sandi untuk akun Spotify kamu:\nIngat: Panjang kata sandi 7 - 32 karakter!\nTahap ini tidak dapat dibatalkan!", inputtext), "Set", "");
        }
        case DIALOG_SPOTIFY_SIGNPASSWORD:
        {
            if(!response) return 1;
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_SPOTIFY_SIGNPASSWORD, DIALOG_STYLE_PASSWORD, ""TCRP"District  "WHITE"- Daftar Spotify",
            sprintf("Error: Tidak dapat diisi kosong!\nHai, %s!\nSilahkan masukkan kata sandi untuk akun Spotify kamu:\nIngat: Panjang kata sandi 7 - 32 karakter!\nTahap ini tidak dapat dibatalkan!", AccountData[playerid][pTempText]), "Set", "");

            if(strlen(inputtext) < 7 || strlen(inputtext) > 32) return ShowPlayerDialog(playerid, DIALOG_SPOTIFY_SIGNPASSWORD, DIALOG_STYLE_PASSWORD, ""TCRP"District  "WHITE"- Daftar Spotify",
            sprintf("Error: Password tidak dapat kurang dari 7 atau lebih dari 32 huruf!\nHai, %s!\nSilahkan masukkan kata sandi untuk akun Spotify kamu:\nIngat: Panjang kata sandi 7 - 32 karakter!\nTahap ini tidak dapat dibatalkan!", AccountData[playerid][pTempText]), "Set", "");

            format(AccountData[playerid][SpotifyName], 128, AccountData[playerid][pTempText]);
            format(AccountData[playerid][SpotifyPassword], 64, inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membuat akun Spotify, silahkan login!");
        }
        case DIALOG_SPOTIFY_LOGIN:
        {
            if(!response) return 1;
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_SPOTIFY_LOGIN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Login Spotify",
            "Error: Tidak dapat diisi kosong!\nHai, selamat datang di Spotify!\nSilahkan masukkan username Spotify kamu yang telah terdaftar:", "Input", "Batal");

            if(strcmp(inputtext, AccountData[playerid][SpotifyName])) return ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Akun Spotify %s tidak ditemukan!", inputtext));

            ShowPlayerDialog(playerid, DIALOG_SPOTIFY_LOGINPASSWORD, DIALOG_STYLE_PASSWORD, ""TCRP"District  "WHITE"- Login Spotify",
            sprintf("Hai, %s!\nSilahkan masukkan kata sandi akun Spotify kamu untuk masuk:", inputtext), "Input", "Batal");
        }
        case DIALOG_SPOTIFY_LOGINPASSWORD:
        {
            if(!response) return 1;
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_SPOTIFY_LOGINPASSWORD, DIALOG_STYLE_PASSWORD, ""TCRP"District  "WHITE"- Login Spotify",
            sprintf("Error: Anda harus memasukkan kata sandi!\nHai, %s!\nSilahkan masukkan kata sandi akun Spotify kamu untuk masuk:", AccountData[playerid][SpotifyName]), "Input", "Batal");

            if(strcmp(inputtext, AccountData[playerid][SpotifyPassword])) return ShowPlayerDialog(playerid, DIALOG_SPOTIFY_LOGINPASSWORD, DIALOG_STYLE_PASSWORD, ""TCRP"District  "WHITE"- Login Spotify",
            sprintf("Error: Kata sandi yang anda masukkan salah!\nHai, %s!\nSilahkan masukkan kata sandi akun Spotify kamu untuk masuk:", AccountData[playerid][SpotifyName]), "Input", "Batal");

            AccountData[playerid][Spotify] = true;
            Toggle_SpotifyHomeTD(playerid, false);
            Toggle_SpotifyTD(playerid, true);
        }
        case DIALOG_TWITTER_LOGIN:
        {
            if(!response) return 1;
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_TWITTER_LOGIN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Login Twitter",
            "Error: Tidak dapat diisi kosong!\nHai, selamat datang di Twitter!\nSilahkan masukkan username Twitter kamu yang telah terdaftar:", "Input", "Batal");

            if(strcmp(inputtext, AccountData[playerid][TwitterName])) return ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Akum Twitter %s tidak ditemukan!", inputtext));

            ShowPlayerDialog(playerid, DIALOG_TWITTER_LOGINPASSWORD, DIALOG_STYLE_PASSWORD, ""TCRP"District  "WHITE"- Login Twitter",
            sprintf("Hai, %s!\nSilahkan masukkan kata sandi akun Twitter kamu untuk masuk:", inputtext), "Input", "Batal");
        }
        case DIALOG_TWITTER_LOGINPASSWORD:
        {
            if(!response) return 1;
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_TWITTER_LOGINPASSWORD, DIALOG_STYLE_PASSWORD, ""TCRP"District  "WHITE"- Login Twitter",
            sprintf("Error: Anda harus memasukkan kata sandi!\nHai, %s!\nSilahkan masukkan kata sandi akun Twitter kamu untuk masuk:", AccountData[playerid][TwitterName]), "Input", "Batal");

            if(strcmp(inputtext, AccountData[playerid][TwitterPassword])) return ShowPlayerDialog(playerid, DIALOG_TWITTER_LOGINPASSWORD, DIALOG_STYLE_PASSWORD, ""TCRP"District  "WHITE"- Login Twitter",
            sprintf("Error: Kata sandi yang anda masukkan salah!\nHai, %s!\nSilahkan masukkan kata sandi akun Twitter kamu untuk masuk:", AccountData[playerid][TwitterName]), "Input", "Batal");

            AccountData[playerid][Twitter] = true;
            Toggle_TwitterHome(playerid, false);
            Toggle_TwitterHomepage(playerid, true);
        }
        case DIALOG_TWITTER_SIGN:
        {
            if(!response) return 1;
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_TWITTER_SIGN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Daftar Twitter", "Error: Tidak dapat diisi kosong!\nHai, selamat datang di Twitter!\
            \nSilahkan masukkan username Twitter kamu, ini akan ditampilkan pada setiap post tweet yang kamu buat:\
            \nIngat: Username hanya dapat berupa huruf dan angka, tidak menggunakan simbol!\
            \nPanjang username 7 - 24 karakter!", "Set", "Batal");

            if(strlen(inputtext) < 7 || strlen(inputtext) > 24) return ShowPlayerDialog(playerid, DIALOG_TWITTER_SIGN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Daftar Twitter", "Error: Nama tidak dapat kurang dari 7 huruf atau lebih dari 24!\nHai, selamat datang di Twitter!\
            \nSilahkan masukkan username Twitter kamu, ini akan ditampilkan pada setiap post tweet yang kamu buat:\
            \nIngat: Username hanya dapat berupa huruf dan angka, tidak menggunakan simbol!\
            \nPanjang username 7 - 24 karakter!", "Set", "Batal");

            format(AccountData[playerid][pTempText], 24, inputtext);
            ShowPlayerDialog(playerid, DIALOG_TWITTER_SIGNPASSWORD, DIALOG_STYLE_PASSWORD, ""TCRP"District  "WHITE"- Daftar Twitter",
            sprintf("Hai %s!\nSilahkan massukan kata sandi untuk akun Twitter kamu:\nIngat: Panjang kata sandi 7 - 32 Karakter!\nTahap ini tidak dapat dibatalkan!", inputtext), "Set", "");
        }
        case DIALOG_TWITTER_SIGNPASSWORD:
        {
            if(!response) return 1;
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_TWITTER_SIGNPASSWORD, DIALOG_STYLE_PASSWORD, ""TCRP"District  "WHITE"- Daftar Twitter",
            sprintf("Error: Tidak dapat diisi kosong!\nHai, %s!\nSilahkan masukkan kata sandi untuk akun Twitter kamu:\nIngat: Panjang kata sandi 7 - 32 Karakter!\nTahap ini tidak dapat dibatalkan!", AccountData[playerid][pTempText]), "Set", "");

            if(strlen(inputtext) < 7 || strlen(inputtext) > 32) return ShowPlayerDialog(playerid, DIALOG_TWITTER_SIGNPASSWORD, DIALOG_STYLE_PASSWORD, ""TCRP"District  "WHITE"- Daftar Twitter",
            sprintf("Error: Password tidak dapat kurang dari 7 atau 32 huruf!\nHai, %s!\nSilahkan masukkan kata sandi untuk akun Twitter kamu:\nIngat: Panjang kata sandi 7 - 32 Karakter!\nTahap ini tidak dapat dibatalkan!", AccountData[playerid][pTempText]), "Set", "");

            format(AccountData[playerid][TwitterName], 128, AccountData[playerid][pTempText]);
            format(AccountData[playerid][TwitterPassword], 64, inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membuat akun twitter, silahkan login!");
        }
        case DialogOpenContact:
        {
            if(!response) return 1;
            switch(listitem)
            {
                case 0: // 
                {
                    ShowPlayerDialog(playerid, DIALOG_ADD_CONTACT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Tambah Kontak",
                    "Mohon masukkan nama kontak yang akan disimpan dibawah ini:", "Set", "Batal");
                }
                case 1: //
                {
                    ShowContactList(playerid);
                }
            }
        }
        case DIALOG_AIRDROPDISPLAY:
        {
            if(!response) return 1;
            switch(listitem)
            {
                case 0: // izin airdrop
                {
                    switch(AccountData[playerid][AirdropPermission])
                    {
                        case false: AccountData[playerid][AirdropPermission] = true;
                        case true: AccountData[playerid][AirdropPermission] = false;
                    }

                    new strings[255];
                    format(strings, sizeof(strings), "Status: %s\
                    \nShare Contacts", AccountData[playerid][AirdropPermission] ? ""LIGHTGREEN"Share Contact diizinkan" : ""RED"Share Contact tidak diizinkan");
                    
                    ShowPlayerDialog(playerid, DIALOG_AIRDROPDISPLAY, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Airdrop", strings, "Pilih", "Batal");
                }
                case 1: // share
                {
                    if(!AccountData[playerid][AirdropPermission]) 
                        return ShowTDN(playerid, NOTIFICATION_WARNING, "Izinkan terlebih dahulu Permission Share Contact!");

                    new frmxt[255], count = 0;

                    foreach(new i : Player) if (i != playerid) if (IsPlayerNearPlayer(playerid, i, 2.0) && AccountData[i][AirdropPermission])
                    {
                        format(frmxt, sizeof(frmxt), "%sPlayer ID: %d\n", frmxt, i);
                        NearestPlayer[playerid][count++] = i;
                    }

                    if(count == 0)
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Airdrop",
                        "Tidak ada player yang dekat dengan anda!", "Tutup", "");
                    }

                    ShowPlayerDialog(playerid, DIALOG_AIRDROP, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Airdrop", frmxt, "Pilih", "Batal");
                }
            }
        }
        case DIALOG_AIRDROP:
        {
            if(!response) return 1;
            new targetid = NearestPlayer[playerid][listitem];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            if(!IsPlayerNearPlayer(playerid, targetid, 2.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");
            if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih orang yang ingin anda bagikan kontak!");

            SetPVarString(targetid, "NumberPhone", AccountData[playerid][pPhone]);
            strpack(AccountData[targetid][pNamaAirdrop], ReturnName(playerid), MAX_PLAYER_NAME);

            new shstr[522];
            format(shstr, sizeof(shstr), "Anda menerima permintaan penyimpanan kotak dari:\nNama: %s\nNomor HP: %s\nApakah anda yakin ingin menyimpan kontak tersebut?", AccountData[playerid][pName], AccountData[playerid][pPhone]);
            ShowPlayerDialog(targetid, DIALOG_AIRDROP_CONF, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Airdrop", shstr, "Iya", "Tidak");
        }
        case DIALOG_AIRDROP_CONF:
        {
            if(!response) return 1;

            new frmtname[64], frmtnumber[64], tss[255];            

            GetPVarString(playerid, "NumberPhone", frmtnumber, sizeof(frmtnumber));
            strunpack(frmtname, AccountData[playerid][pNamaAirdrop]);

            if(IsNumberAlreadySaved(playerid, frmtnumber)) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Nomor tersebut sudah terdaftar di kontak atas nama %s", GetMySavedContactName(playerid, frmtnumber)));
            if(CountPlayerContact(playerid) >= MAX_CONTACTS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Penyimpanan kontak anda penuh!");

            for(new cid = 0; cid < MAX_CONTACTS; cid ++)
            {
                if(!ContactData[playerid][cid][contactExists])
                {
                    ContactData[playerid][cid][contactExists] = true;
                    ContactData[playerid][cid][contactOwnerID] = GetUCPSQLID(playerid);
                    format(ContactData[playerid][cid][contactNumber], sizeof(frmtnumber), "%s", frmtnumber);
                    format(ContactData[playerid][cid][contactName], sizeof(frmtname), "%s", frmtname);

                    mysql_format(g_SQL, tss, sizeof(tss), "INSERT INTO `contacts` SET `ID`=%d, `contactName`='%s', `contactNumber`='%s', `contactOwner`=%d, `contactUnread`=0", GetUCPSQLID(playerid), ContactData[playerid][cid][contactName], ContactData[playerid][cid][contactNumber], ContactData[playerid][cid][contactOwnerID]);
                    mysql_tquery(g_SQL, tss, "OnContactAdded", "dd", playerid, cid);
                    return 1;
                }
            }
        }
        case DANN_BOOMBOX:
        {
            if(!response)
            {
                SendClientMessageEx(playerid, COLOR_WHITE, ""VERONADOT"Kamu Membatalkan Music");
                return 1;
            }
            switch(listitem)
            {
                case 0:
                {
                    if(GetPVarType(playerid, "BBArea"))
                    {
                        SendRPMeAboveHead(playerid, "Mematikan musik", X11_PLUM1);
                        foreach(new i : Player)
                        {
                            if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "BBArea")))
                            {
                                StopStream(i);
                            }
                        }
                        DeletePVar(playerid, "BBStation");
                    }
                    SendClientMessageEx(playerid, COLOR_WHITE, "{00ff00}[!]{ffffff}: Kamu Telah Mematikan Boomboxnya");
                }
                case 1:
                {
                    static jskc[512];
                    format(jskc, sizeof(jskc), ""VERONA_ARWIN"Boombox Music - Cerahi Hidupmu Secerah Matahari Di Pagi Hari\n\n"VERONA_ARWIN"Kami sarankan anda untuk upload file mp3 ke discord terlebih dahulu.\n"RED_E"Note: Fitur ini tidak support link Youtube secara langsung!\n\n"YELLOW"(Apabila file mp3 telah di upload ke discord, silahkan copy linknya dan paste dibawah ini):");
                    ShowPlayerDialog(playerid,DANN_BOOMBOX1,DIALOG_STYLE_INPUT, "Boombox Play Music", jskc, "Play", "Cancel");
                }
            }
        }
        case DANN_BOOMBOX1:
        {
            if(response == 1)
            {
                if(isnull(inputtext))
                {
                    ShowTDN(playerid, NOTIFICATION_WARNING, "Kamu belum memasukan URL!");
                    // SendClientMessageEx(playerid, COLOR_WHITE, "{00ff00}[!]{ffffff}: Kamu Tidak Menulis Apapun");
                    return 1;
                }
                if(strlen(inputtext))
                {
                    if(GetPVarType(playerid, "PlacedBB"))
                    {
                        foreach(new i : Player)
                        {
                            if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "BBArea")))
                            {
                                PlayStream(i, inputtext, GetPVarFloat(playerid, "BBX"), GetPVarFloat(playerid, "BBY"), GetPVarFloat(playerid, "BBZ"), 30.0, 1);
                            }
                        }
                        SetPVarString(playerid, "BBStation", inputtext);
                    }
                }
            }
        }
        case DIALOG_ADD_CONTACT:
        {
            if(!response) return 1;

            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_ADD_CONTACT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Tambah Kontak",
                "Error: Tidak dapat diisi kosong!\nMohon masukkan nama kontak yang akan disimpan dibawah ini:", "Set", "Batal");
                return 1;
            }

            if(strlen(inputtext) < 1 || strlen(inputtext) > 64)
            {
                ShowPlayerDialog(playerid, DIALOG_ADD_CONTACT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Tambah Kontak",
                "Error: Tidak dapat kurang dari 1 huruf atau lebih dari 64!\nMohon masukkan nama kontak yang akan disimpan dibawah ini:", "Set", "Batal");
                return 1;
            }
            
            strpack(AccountData[playerid][pTempText], inputtext, 64);
            ShowPlayerDialog(playerid, DIALOG_ADD_CONTACTNUMB, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Tambah Kontak",
            sprintf("Mohon masukkan nomor HP dari %s:", inputtext), "Input", "Kembali");
        }
        case DIALOG_ADD_CONTACTNUMB:
        {
            if(!response)
            {
                ShowPlayerDialog(playerid, DIALOG_ADD_CONTACT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Tambah Kontak",
                "Mohon masukkan nama kontak yang akan disimpan dibawah ini:", "Set", "Batal");
                return 1;
            }

            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_ADD_CONTACTNUMB, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Tambah Kontak",
                "Error: Tidak dapat diisi kosong!\nMohon masukkan nomor HP kontak yang akan disimpan dibawah ini:", "Input", "Kembali");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_ADD_CONTACTNUMB, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Tambah Kontak",
                "Error: Masukkan nomor HP kontak hanya berisi angka!\nMohon masukkan nomor HP kontak yang akan disimpan dibawah ini:", "Input", "Kembali");
                return 1;
            }

            if(IsNumberAlreadySaved(playerid, inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Nomor tersebut sudah terdaftar di kontak atas nama %s", GetMySavedContactName(playerid, inputtext)));
            if(CountPlayerContact(playerid) >= MAX_CONTACTS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Penyimpanan kontak anda telah penuh!");

            new tss[255], frmtname[64];

            strunpack(frmtname, AccountData[playerid][pTempText]);
            for(new cid = 0; cid < MAX_CONTACTS; cid++)
            {
                if(!ContactData[playerid][cid][contactExists])
                {
                    ContactData[playerid][cid][contactExists] = true;
                    ContactData[playerid][cid][contactOwnerID] = GetUCPSQLID(playerid);
                    format(ContactData[playerid][cid][contactNumber], 64, inputtext);
                    format(ContactData[playerid][cid][contactName], 64, frmtname);
                
                    mysql_format(g_SQL, tss, sizeof(tss), "INSERT INTO `contacts` SET `ID`=%d, `contactName`='%s', `contactNumber`='%s', `contactOwner`=%d, `contactUnread`=0", GetUCPSQLID(playerid), ContactData[playerid][cid][contactName], ContactData[playerid][cid][contactNumber], ContactData[playerid][cid][contactOwnerID]);
                    mysql_tquery(g_SQL, tss, "OnContactAdded", "dd", playerid, cid);    
                    return 1;
                }
            }
        }
        case DialogTelepon:
        {
            if(!response) return 1;

            if(AccountData[playerid][phoneAirplaneMode])
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone sedang dalam Mode Pesawat!");

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DialogTelepon, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Telepon",
            "Error: Tidak dapat diisi kosong!\nMohon masukan nomor telepon yang ingin anda hubungi:", "Input", "Batal");
               
            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DialogTelepon, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Telepon",
            "Error: Hanya dapat diisi angka!\nMohon masukan nomor telepon yang ingin anda hubungi:", "Input", "Batal");

            if(!strcmp(inputtext, "110", true)) // Polisi
            {
                Dialog_Show(playerid, CALLCENTER_POLISI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Darurat Polisi",
                "Masukkan kendala anda yang ingin dilaporkan kepada pihak kepolisian dibawah ini\
                \nJelaskan detail dan kendala yang sedang kamu alami dan ingin lapor ke kepolisian:", "Kirim", "Batal");
            }
            else if(!strcmp(inputtext, "118", true)) // Ems
            {
                Dialog_Show(playerid, CALLCENTER_EMS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Darurat Rumah Sakit",
                "Masukkan kendala anda yang ingin dilaporkan kepada pihak Rumah Sakit dibawah ini\
                \nJelaskan detail dan kendala yang sedang kamu alami dan ingin lapor ke Rumah Sakit:", "Kirim", "Batal");
            }
            else if(!strcmp(inputtext, "117", true)) // Pemerintah
            {
                Dialog_Show(playerid, CALLCENTER_PEMDA, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Call Center Pemerintah",
                "Masukkan kendala anda yang ingin dilaporkan kepada pihak Pemerintah dibawah ini\
                \nJelaskan detail dan kendala yang sedang kamu alami dan ingin lapor ke Pemerintah:", "Kirim", "Batal");
            }
            else
            {
                new targetnumberownerid = GetNumberOwner(inputtext);
                if(!IsPlayerConnected(targetnumberownerid) || targetnumberownerid == INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon maaf nomor tersebut sedang tidak aktif!");
                if(!strcmp(AccountData[playerid][pPhone], inputtext, false)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menghubungi diri sendiri!");
                OnOutcomingCall(playerid, inputtext);
            }

    
        }
        case DialogContact:
        {
            new index = ListedContacts[playerid][listitem];

            if(!response)
            {
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");

                PlayerContactPage[playerid] = 0;
                return true;
            }

            if(strfind(inputtext, "<< Halaman Sebelumnya") != -1)
            {
                PlayerContactPage[playerid] --;
                ShowContactList(playerid);
                return true;
            }

            if(strfind(inputtext, ">> Halaman Selanjutnya") != -1)
            {
                new next_page = PlayerContactPage[playerid] + 1;
                new start_index = next_page * 15;
                if(ContactData[playerid][start_index][contactExists])
                {
                    PlayerContactPage[playerid] ++;
                    ShowContactList(playerid);
                }
                else
                {
                    PlayerContactPage[playerid] = PlayerContactPage[playerid];
                    ShowContactList(playerid);
                    Error(playerid, "Anda tidak memiliki kontak lagi di halaman selanjutnya!");
                }
                return true;
            }

            /*if(!strcmp(inputtext, ">> Halaman Selanjutnya", true))
            {
                mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `contacts` WHERE `ID` = %d ORDER BY ID ASC LIMIT %d, 15", AccountData[playerid][pID], (PlayerContactPage[playerid] + 1) * 15);
                result = mysql_query(g_SQL, query, true);
                if(cache_num_rows())
                {
                    cache_delete(result);
                    PlayerContactPage[playerid] ++;
                    ShowContactList(playerid);
                }
                else
                {
                    cache_delete(result);
                    PlayerContactPage[playerid] = PlayerContactPage[playerid];
                    ShowContactList(playerid);
                }
                return true;
            }*/

            if(ContactData[playerid][index][contactExists])
            {
                AccountData[playerid][pContact] = index;
                
                ShowPlayerDialog(playerid, DialogContactMenu, DIALOG_STYLE_LIST, sprintf(""TCRP"District "WHITE" - %s", ContactData[playerid][AccountData[playerid][pContact]][contactName]),
                "Panggil\
                \n"GRAY"Whatsapp\
                \nShareloc\
                \n"GRAY"Edit Nama Kontak\
                \nEdit Nomor Kontak\
                \n"GRAY"Blokir/Buka Blokir Kontak\
                \nHapus Kontak", "Pilih", "Batal");
            }
            
            for(new i = 0; i < MAX_CONTACTS; i++) {
                ListedContacts[playerid][i] = -1;
            }
        }
        case DIALOG_YELLOW_PAGE_EMPTY:
        {
            if(!response)
            {
                return AccountData[playerid][CurrentlyReadYellow] = false;
            }

            ShowPlayerDialog(playerid, DIALOG_YELLOW_PAGE_SEND, DIALOG_STYLE_INPUT, ""TCRP"District  "GRAY"- Buat Iklan", "Masukkan iklan yang ingin anda buat dibawah sini:", "Kirim", "Kembali");
        }
        case DIALOG_YELLOW_PAGE:
        {
            if(!response)
            {
                return AccountData[playerid][CurrentlyReadYellow] = false;
            }
            
            new cQuery[333];
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "SELECT * FROM `yellowpages` WHERE ID=1");
            mysql_query(g_SQL, cQuery);
            if(cache_num_rows())
            {
                new YellowSender[64], YellowNumber[64], YellowMessage[128], frmxt[598];
                if(listitem >= 0 && listitem < cache_num_rows())
                {
                    cache_get_value_name(listitem, "YellowFrom", YellowSender);
                    cache_get_value_name(listitem, "YellowPhone", YellowNumber);
                    cache_get_value_name(listitem, "YellowText", YellowMessage);
                
                    SetPVarString(playerid, "YellowNumber", YellowNumber);
                    format(frmxt, sizeof(frmxt), ""WHITE"Pengirim: "YELLOW"%s\n"BLUEJEGE"%s", YellowSender, YellowMessage);
                    ShowPlayerDialog(playerid, DIALOG_YELLOW_CALL, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Iklan",
                    frmxt, "Hubungi", "Batal");
                }
            }
        }
        case DIALOG_YELLOW_PAGE_MENU:
        {
            if(!response)
            {
                AccountData[playerid][CurrentlyReadYellow] = false;
                return 1;
            }
            
            switch(listitem)
            {
                case 0: // Lihat Iklan
                {
                    ShowPlayerYellowsPage(playerid);
                }
                case 1: //Buat Iklan
                {
                    ShowPlayerDialog(playerid, DIALOG_YELLOW_PAGE_SEND, DIALOG_STYLE_INPUT, ""TCRP"District  "GRAY"- Buat Iklan",
                    "Masukkan iklan yang ingin anda buat dibawah sini:", "Kirim", "Kembali");
                }
            }
        }
        case DIALOG_YELLOW_CALL:
        {
            if(!response)
            {
                SetPVarString(playerid, "YellowNumber", "");
                ShowPlayerYellowsPage(playerid);
                return 1;
            }

            new YellowPhoneNumber[64];
            GetPVarString(playerid, "YellowNumber", YellowPhoneNumber, sizeof(YellowPhoneNumber));
            
            new ownernumberID = GetNumberOwner(YellowPhoneNumber);
            if(!strcmp(YellowPhoneNumber, AccountData[playerid][pPhone], false)) 
            {
                AccountData[playerid][CurrentlyReadYellow] = false;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Nomor tersebut sedang sibuk!");
            }

            if(!IsPlayerConnected(ownernumberID)) 
            {
                AccountData[playerid][CurrentlyReadYellow] = false;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            }

            OnOutcomingCall(playerid, sprintf("%s", YellowPhoneNumber));
            AccountData[playerid][CurrentlyReadYellow] = false;
        }
        case DIALOG_YELLOW_PAGE_SEND:
        {
            if(!response) 
            {
                AccountData[playerid][CurrentlyReadYellow] = false;
                return 1;
            }

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_YELLOW_PAGE_SEND, DIALOG_STYLE_INPUT, ""TCRP"District  "GRAY"- Buat Iklan",
                "Error: Iklan tidak dapat kosong!\nMasukkan iklan yang ingin anda buat dibawah sini:", "Kirim", "Kembali");
            
            if(strlen(inputtext) < 1 || strlen(inputtext) > 128) return ShowPlayerDialog(playerid, DIALOG_YELLOW_PAGE_SEND, DIALOG_STYLE_INPUT, ""TCRP"District  "GRAY"- Buat Iklan",
                "Error: Iklan tidak boleh kurang dari 1 atau lebih dari 128 huruf!\nMasukkan iklan yang ingin anda buat dibawah sini:", "Kirim", "Kembali");
            
            if(!IsValidFormatText(inputtext)) return ShowPlayerDialog(playerid, DIALOG_TWITTER_POST_SEND, DIALOG_STYLE_INPUT, ""TCRP"District  "GRAY"- Kirim Tweet",
                "Error: Dilarang menggunakan tanda '\'' atau apapun itu!\nMasukkan Tweet yang ingin anda buat dibawah sini:", "Kirim", "Kembali");

            new frmttime[255], query[600];
            new hours, minutes, seconds, years, months, days;
            gettime(hours, minutes, seconds);
            getdate(years, months, days);
            format(frmttime, sizeof(frmttime), "%02d/%02d/%02d %02d:%02d:%02d", years, months, days, hours, minutes, seconds);

            mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `yellowpages` (`ID`, `YellowFrom`, `YellowPhone`, `YellowDate`, `YellowText`) VALUES ('1', '%s', '%s', '%s', '%s')", ReturnName(playerid), AccountData[playerid][pPhone], frmttime, inputtext);
            mysql_tquery(g_SQL, query, "OnPlayerAdvert", "d", playerid);
            foreach(new i : Player) if (IsPlayerConnected(i) && AccountData[i][IsLoggedIn]) if (i != playerid)
            {
                if(AccountData[i][CurrentlyReadYellow]) return ShowPlayerYellowsPage(i);
            }
        }
        case DIALOG_WHATSAPP_CHAT:
        {
            new cidt = AccountData[playerid][pContact];
            if(!response) 
            {
                ShowContactList(playerid);
                AccountData[playerid][CurrentlyReadWA] = false;
            }
            else
            {
                new title[100];
                format(title, sizeof(title), "WhatsApp Chat - %s", ContactData[playerid][cidt][contactName]);
                ShowPlayerDialog(playerid, DIALOG_WHATSAPP_SEND, DIALOG_STYLE_INPUT, title, "Masukkan pesan WhatsApp yang ingin anda kirim dibawah ini:", "Kirim", "Kembali");
            }
            return 1;
        }
        case DIALOG_WHATSAPP_CHAT_EMPTY:
        {
            new cidt = AccountData[playerid][pContact];
            if(!response) 
            {
                ShowContactList(playerid);
                AccountData[playerid][CurrentlyReadWA] = false;
            }
            else
            {
                new title[100];
                format(title, sizeof(title), "WhatsApp Chat - %s", ContactData[playerid][cidt][contactName]);
                ShowPlayerDialog(playerid, DIALOG_WHATSAPP_SEND, DIALOG_STYLE_INPUT, title, "Masukkan pesan WhatsApp yang ingin anda kirim dibawah ini:", "Kirim", "Kembali");
            }
            return 1;
        }
        case DIALOG_WHATSAPP_SEND:
        {
            if(!response) 
            {
                AccountData[playerid][CurrentlyReadWA] = false;
                return 1;
            }
            
            new cidt = AccountData[playerid][pContact];
            new targetid = GetNumberOwner(ContactData[playerid][cidt][contactNumber]);
            if(targetid == INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon maaf nomor telepon itu sedang tidak aktif!");
            new ChatID = (AccountData[playerid][pMaskID]+AccountData[targetid][pMaskID]);

            new title[100];
            format(title, sizeof(title), "WhatsApp Chat - %s", ContactData[playerid][cidt][contactName]);

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_WHATSAPP_SEND, DIALOG_STYLE_INPUT, title, 
            "Error: Pesan tidak boleh kosong!\nMasukkan pesan WhatsApp yang ingin anda kirim dibawah ini:", "Kirim", "Kembali");

            if(strlen(inputtext) < 1 || strlen(inputtext) > 128) return ShowPlayerDialog(playerid, DIALOG_WHATSAPP_SEND, DIALOG_STYLE_INPUT, title, 
            "Error: Pesan tidak dapat kurang dari 1 atau lebih dari 128 huruf!\nMasukkan pesan WhatsApp yang ingin anda kirim dibawah ini:", "Kirim", "Kembali");

            if(!IsValidFormatText(inputtext)) return ShowPlayerDialog(playerid, DIALOG_TWITTER_POST_SEND, DIALOG_STYLE_INPUT, ""TCRP"District  "GRAY"- Kirim Tweet",
            "Error: Dilarang menggunakan tanda '\'' atau apapun itu!\nMasukkan Tweet yang ingin anda buat dibawah sini:", "Kirim", "Kembali");

            if(CheckNumberBlocked(targetid, AccountData[playerid][pPhone])) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak dapat mengirim pesan, nomor anda di Blokir!");

            for(new i; i < MAX_CONTACTS; i ++) {
                if(ContactData[targetid][i][contactExists]) {
                    if(!strcmp(ContactData[targetid][i][contactNumber], AccountData[playerid][pPhone], false)) {
                        ContactData[targetid][i][contactUnread] += 1;
                    }
                }
                new dbstr[151];
                mysql_format(g_SQL, dbstr, sizeof(dbstr), "UPDATE `contacts` SET `contactUnread` = %d WHERE `contactID` = %d", ContactData[targetid][i][contactUnread], ContactData[targetid][i][contactID]);
                mysql_tquery(g_SQL, dbstr);
            }
            new frmttime[255];
            new hours, minutes, seconds, years, months, days;
            gettime(hours, minutes, seconds);
            getdate(years, months, days);
            format(frmttime, sizeof(frmttime), "%02d-%02d-%02d %02d:%02d:%02d", years, months, days, hours, minutes, seconds);

            new query[1048];
            mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `whatsapp_chats` (`ID`, `chatTimestamp`, `chatSender`, `chatMessage`) VALUES ('%d', '%s', '%s', '%s')", ChatID, frmttime, GetMySavedContactName(targetid, AccountData[playerid][pPhone]), inputtext);
            mysql_tquery(g_SQL, query, "OnWhatsappSent", "iiii", playerid, targetid, cidt, (AccountData[playerid][pMaskID]+AccountData[targetid][pMaskID]));
        }
        case DIALOG_TWITTER_POST_EMPTY:
        {
            if(!response)
            {
                AccountData[playerid][CurrentlyReadTwitter] = false;
                return 1;
            }

            ShowPlayerDialog(playerid, DIALOG_TWITTER_POST_SEND, DIALOG_STYLE_INPUT, ""TCRP"District  "GRAY"- Kirim Tweet", "Masukkan Tweet yang ingin anda buat dibawah sini:", "Kirim", "Kembali");
        }
        case DIALOG_TWITTER_POST:
        {
            if(!response)
            {
                AccountData[playerid][CurrentlyReadTwitter] = false;
                return 1;
            }

            ShowPlayerDialog(playerid, DIALOG_TWITTER_POST_SEND, DIALOG_STYLE_INPUT, ""TCRP"District  "GRAY"- Kirim Tweet", "Masukkan Tweet yang ingin anda buat dibawah sini:", "Kirim", "Kembali");
        }
        case DIALOG_TWITTER_POST_SEND:
        {
            if(!response) 
            {
                AccountData[playerid][CurrentlyReadTwitter] = false;
                return 1;
            }

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_TWITTER_POST_SEND, DIALOG_STYLE_INPUT, ""TCRP"District  "GRAY"- Kirim Tweet",
                "Error: Tweet tidak dapat kosong!\nMasukkan Tweet yang ingin anda buat dibawah sini:", "Kirim", "Kembali");
            
            if(strlen(inputtext) < 1 || strlen(inputtext) > 128) return ShowPlayerDialog(playerid, DIALOG_TWITTER_POST_SEND, DIALOG_STYLE_INPUT, ""TCRP"District  "GRAY"- Kirim Tweet",
                "Error: Tweet tidak boleh kurang dari 1 atau lebih dari 128 huruf!\nMasukkan Tweet yang ingin anda buat dibawah sini:", "Kirim", "Kembali");

            if(!IsValidFormatText(inputtext)) return ShowPlayerDialog(playerid, DIALOG_TWITTER_POST_SEND, DIALOG_STYLE_INPUT, ""TCRP"District  "GRAY"- Kirim Tweet",
            "Error: Dilarang menggunakan tanda '\'' atau apapun itu!\nMasukkan Tweet yang ingin anda buat dibawah sini:", "Kirim", "Kembali");

            new frmttime[255], query[522];
            new hours, minutes, seconds;
            gettime(hours, minutes, seconds);
            //getdate(years, months, days);
            format(frmttime, sizeof(frmttime), "%02d:%02d:%02d", hours, minutes, seconds);

            mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `tweets` (`ID`, `TwitterFrom`, `TwitterDate`, `TwitterText`) VALUES ('1', '%s', '%s', '%s')", AccountData[playerid][TwitterName], frmttime, inputtext);
            mysql_tquery(g_SQL, query, "OnPlayerTweet", "d", playerid);
            AddTweetLog(AccountData[playerid][pName], AccountData[playerid][pUCP], inputtext);
            new str1[128], str2[128];
            strmid(str1, inputtext, 0, 20);
            foreach(new ii : Player)
            {
                if(!IsPlayerConnected(ii)) continue;

                PlayerTextDrawSetString(ii, ATRP_TwitterNotif[ii][33], AccountData[playerid][TwitterName]);
                PlayerTextDrawSetString(ii, ATRP_TwitterNotif[ii][34], frmttime);
                PlayerTextDrawSetString(ii, ATRP_TwitterNotif[ii][35], str1);
                if(strlen(inputtext) > 20)
                {
                    strmid(str2, inputtext, 20, strlen(inputtext));
                    PlayerTextDrawSetString(ii, ATRP_TwitterNotif[ii][36], str2);
                    PlayerTextDrawShow(ii, ATRP_TwitterNotif[ii][36]);

                    PlayerTextDrawSetString(ii, ATRP_TwitterNotif[ii][37], str2);
                    PlayerTextDrawShow(ii, ATRP_TwitterNotif[ii][37]);
                }
                else 
                {
                    PlayerTextDrawSetString(ii, ATRP_TwitterNotif[ii][36], "");
                    PlayerTextDrawHide(ii, ATRP_TwitterNotif[ii][36]);

                    PlayerTextDrawSetString(ii, ATRP_TwitterNotif[ii][37], "");
                    PlayerTextDrawHide(ii, ATRP_TwitterNotif[ii][37]);
                }
                for(new td = 0; td < 38; td++)
                {
                    PlayerTextDrawShow(ii, ATRP_TwitterNotif[ii][td]);
                }
                for(new x = 0; x < 15; x ++) PlayerTextDrawHide(playerid, HbeStuffs[playerid][x]);
                HideHBE(playerid);
                CancelSelectTextDraw(playerid);
                ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
                RemovePlayerAttachedObject(playerid, 9);
                Toggle_PhoneTD(playerid, false);
                HideAllSmartphone(playerid);
                SetTimerEx("HidePostTwitter", 5000, false, "i", ii);
            }

            /*foreach(new i : Player) if (AccountData[i][pSpawned] && AccountData[i][CurrentlyReadTwitter]) {
                ShowPlayerTwitterPage(i);
            }*/
        }
        case DialogContactMenu:
        {
            if(!response)
            {
                ShowContactList(playerid);
                return 1;
            }

            new cidt = AccountData[playerid][pContact];
            new ownernumber = GetNumberOwner(ContactData[playerid][cidt][contactNumber]);
            switch(listitem)
            {
                case 0:// Panggil
                {
                    if(AccountData[playerid][phoneAirplaneMode]) 
                        return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone sedang dalam Mode Pesawat!");
                        
                    new targetnumber[25];
                    format(targetnumber, sizeof(targetnumber), "%s", ContactData[playerid][cidt][contactNumber]);
                    if(!strcmp(AccountData[playerid][pPhone], targetnumber, false)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menghubungi diri sendiri!");
                    if(!IsPlayerConnected(ownernumber)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon maaf nomor tersebut sedang tidak aktif!");
                    if(CheckNumberBlocked(playerid, AccountData[ownernumber][pPhone])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Nomor tersebut anda blokir, buka terlebih dahulu!");
                    if(CheckNumberBlocked(ownernumber, AccountData[playerid][pPhone])) return ShowTDN(playerid, NOTIFICATION_WARNING, "Tidak dapat melakukan panggilan ini, nomor anda diblokir!");
                    OnOutcomingCall(playerid, targetnumber);
                }
                case 1:// Whatsapp
                {
                    if(AccountData[playerid][phoneAirplaneMode]) 
                        return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone sedang dalam Mode Pesawat!");

                    if(!IsPlayerConnected(ownernumber)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon maaf nomor tersebut tidak aktif di kota!");
                    if(CheckNumberBlocked(playerid, AccountData[ownernumber][pPhone])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Nomor tersebut anda blokir, buka terlebih dahulu!");

                    new query[525], harlem[128];
                    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `whatsapp_chats` WHERE `ID`=%d ORDER BY `chatTimestamp` ASC LIMIT 30", AccountData[playerid][pMaskID]+AccountData[ownernumber][pMaskID]);
                    mysql_query(g_SQL, query);
                    if(cache_num_rows())
                    {
                        if(cache_num_rows() >= 30)
                        {
                            mysql_format(g_SQL, harlem, sizeof(harlem), "DELETE FROM `whatsapp_chats` WHERE `ID`=%d", AccountData[playerid][pMaskID]+AccountData[ownernumber][pMaskID]);
                            mysql_tquery(g_SQL, harlem);
                        }

                        new list[2500], date[64], issuer[24], watext[128];

                        ContactData[playerid][cidt][contactUnread] = 0;
                        mysql_format(g_SQL, query, sizeof(query), "UPDATE `contacts` SET `contactUnread`= 0 WHERE `contactID`=%d", ContactData[playerid][cidt][contactID]);
                        mysql_tquery(g_SQL, query);

                        format(list, sizeof(list), "Tanggal\tPengirim\tPesan\n");
                        for(new i; i < cache_num_rows(); ++i)
                        {
                            cache_get_value_name(i, "chatTimestamp", date);
                            cache_get_value_name(i, "chatSender", issuer);
                            cache_get_value_name(i, "chatMessage", watext);
                        
                            format(list, sizeof(list), "%s%s\t%s\t%s\n", list, date, issuer, watext);
                        }
                        new title[100];
                        format(title, sizeof(title), "WhatsApp Chat - %s", ContactData[playerid][cidt][contactName]);
                        ShowPlayerDialog(playerid, DIALOG_WHATSAPP_CHAT, DIALOG_STYLE_TABLIST_HEADERS, title, list, "Kirim", "Kembali");
                    }
                    else 
                    {
                        new list[208], title[102];
                        format(list, sizeof(list), "Tanggal\tPengirim\tPesan\n");
                        format(list, sizeof(list), "%sPesan dan panggilan terenkripsi secara end-to-end.", list);
                        format(title, sizeof(title), "WhatsApp Chat - %s", ContactData[playerid][cidt][contactName]);
                        ShowPlayerDialog(playerid, DIALOG_WHATSAPP_CHAT_EMPTY, DIALOG_STYLE_TABLIST_HEADERS, title, list, "Kirim", "Kembali");
                    }
                    AccountData[playerid][CurrentlyReadWA] = true;
                }
                case 2:// Shareloc
                {
                    if(AccountData[playerid][phoneAirplaneMode]) 
                        return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone sedang dalam Mode Pesawat!");

                    if(!IsPlayerConnected(ownernumber)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon maaf nomor tersebut tidak aktif di kota!");
                    if(CheckNumberBlocked(playerid, AccountData[ownernumber][pPhone])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Nomor tersebut anda blokir, buka terlebih dahulu!");
                    if(CheckNumberBlocked(ownernumber, AccountData[playerid][pPhone])) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak dapat mengirim shareloc, nomor anda di Blokir!");

                    static Float:x, Float:y, Float:z;
                    GetPlayerPos(playerid, x, y, z);

                    if (SharelocSender[ownernumber] != INVALID_STREAMER_ID) 
                        DestroyDynamicMapIcon(SharelocSender[ownernumber]);

                    SharelocSender[ownernumber] = CreateDynamicMapIcon(x, y, z, 0, COLOR_CLIENT, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), ownernumber, 5000.0, MAPICON_GLOBAL, -1, 0);
                    SharelocTimer[ownernumber] = 120;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil mengirim lokasi kepada %s", ReturnName(ownernumber)));
                    Syntax(ownernumber, "%s mengirimkan shareloc kepada anda", GetMySavedContactName(ownernumber, AccountData[playerid][pPhone]));
                }
                case 3: // Edit Nama Kontak
                {
                    ShowPlayerDialog(playerid, DIALOG_EDIT_CONTACTNAME, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Nama Kontak",
                    sprintf("Mohon masukkan nama baru untuk diterapkan pada kontak %s", ContactData[playerid][cidt][contactName]), "Save", "Batal");
                }
                case 4: // Edit Number
                {
                    ShowPlayerDialog(playerid, DIALOG_EDIT_CONTACTNUMBER, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Nomor Kontak",
                    sprintf("Mohon masukkan nomor baru untuk diterapkan pada kontak %s", ContactData[playerid][cidt][contactName]), "Save", "Batal");
                }
                case 5: // Blokir Kontak
                {
                    switch(ContactData[playerid][cidt][contactBlocked])
                    {
                        case 0:
                        {
                            ContactData[playerid][cidt][contactBlocked] = 1;
                            mysql_query(g_SQL, sprintf("UPDATE `contacts` SET `contactBlocked` = %d WHERE `ID` = '%d' AND `contactID` = '%d'", ContactData[playerid][cidt][contactBlocked], AccountData[playerid][pID], ContactData[playerid][cidt][contactID]), false);
                            ShowContactList(playerid);
                            
                            Info(playerid, "Anda memblokir kontak %s (%s)", ContactData[playerid][cidt][contactName], ContactData[playerid][cidt][contactNumber]);
                        }
                        case 1:
                        {
                            ContactData[playerid][cidt][contactBlocked] = 0;
                            mysql_query(g_SQL, sprintf("UPDATE `contacts` SET `contactBlocked` = %d WHERE `ID` = '%d' AND `contactID` = '%d'", ContactData[playerid][cidt][contactBlocked], AccountData[playerid][pID], ContactData[playerid][cidt][contactID]), false);
                            ShowContactList(playerid);
                            
                            Info(playerid, "Anda membuka memblokir kontak %s (%s)", ContactData[playerid][cidt][contactName], ContactData[playerid][cidt][contactNumber]);
                        }
                    }
                }
                case 6:// Hapus Kontak
                {
                    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda telah menghapus %s dari daftar kontak!", ContactData[playerid][cidt][contactName]));
                    
                    static frmtx[188];
                    mysql_format(g_SQL, frmtx, sizeof(frmtx), "DELETE FROM `contacts` WHERE `ID` = '%d' AND `contactID` = '%d'", AccountData[playerid][pID], ContactData[playerid][cidt][contactID]);
                    mysql_query(g_SQL, frmtx);
                    
                    ContactData[playerid][cidt][contactExists] = false;
                    ContactData[playerid][cidt][contactNumber] = 0;
                    ContactData[playerid][cidt][contactID] = 0;
                    PlayerContactPage[playerid] = 0;
                    
                    for (new i = 0; i < MAX_CONTACTS; i ++) {
                        ContactData[playerid][i][contactExists] = false;
                    }
                    
                    static cQuery[200];
                    mysql_format(g_SQL, cQuery, sizeof(cQuery), "SELECT * FROM `contacts` WHERE `ID`=%d AND `contactOwner`=%d", AccountData[playerid][pID], AccountData[playerid][pID]);
	                mysql_tquery(g_SQL, cQuery, "LoadPlayerContact", "d", playerid);
                    // ShowContactList(playerid);
                }
            }
        }
        case DIALOG_EDIT_CONTACTNUMBER:
        {
            if(response)
            {
                if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EDIT_CONTACTNUMBER, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Nomor Kontak",
                sprintf("Error: Tidak dapat diisi kosong!\nMohon masukkan nomor baru untuk diterapkan pada kontak %s", ContactData[playerid][AccountData[playerid][pContact]][contactName]), "Save", "Batal");

                if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EDIT_CONTACTNUMBER, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Nomor Kontak",
                sprintf("Error: Hanya dapat diisi angka!\nMohon masukkan nomor baru untuk diterapkan pada kontak %s", ContactData[playerid][AccountData[playerid][pContact]][contactName]), "Save", "Batal");

                CallLocalFunction("OnContactEditNumber", "dds", playerid, AccountData[playerid][pContact], inputtext);
            }
            else ShowContactList(playerid);
        }
        case DIALOG_EDIT_CONTACTNAME:
        {
            if(response)
            {
                if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EDIT_CONTACTNAME, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Nama Kontak",
                sprintf("Error: Tidak dapat diisi kosong!\nMohon masukkan nama baru untuk diterapkan pada kontak %s", ContactData[playerid][AccountData[playerid][pContact]][contactName]), "Save", "Batal");

                if(IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EDIT_CONTACTNAME, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Nama Kontak",
                sprintf("Error: Tidak dapat memasukkan angka semua!\nMohon masukkan nama baru untuk diterapkan pada kontak %s", ContactData[playerid][AccountData[playerid][pContact]][contactName]), "Save", "Batal");

                if(strlen(inputtext) < 1 || strlen(inputtext) > 32) return ShowPlayerDialog(playerid, DIALOG_EDIT_CONTACTNAME, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Nama Kontak",
                sprintf("Error: Nama tidak dapat kurang dari 1 huruf atau lebih dari 32!\nMohon masukkan nama baru untuk diterapkan pada kontak %s", ContactData[playerid][AccountData[playerid][pContact]][contactName]), "Save", "Batal");

                CallLocalFunction("OnContactEditName", "dds", playerid, AccountData[playerid][pContact], inputtext);
            }
            else ShowContactList(playerid);
        }
        case DialogTransfer:
        {
            if(!response) return false;
            
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DialogTransfer, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Transfer",
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan nomor rekening yang ingin anda transfer:", "Submit", "Batal");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DialogTransfer, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Transfer",
            "Error: Hanya dapat diisi angka!\nMohon masukkan nomor rekening yang ingin anda transfer:", "Submit", "Batal");

            if(strval(inputtext) == AccountData[playerid][pBankRek]) return ShowPlayerDialog(playerid, DialogTransfer, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Transfer",
            "Error: Tidak dapat mengirim ke rekening diri sendiri!\nMohon masukkan nomor rekening yang ingin anda transfer:", "Submit", "Batal");

            new query[128];
            mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_characters` WHERE `Char_BankRek`=%d", strval(inputtext));
            mysql_tquery(g_SQL, query, "SearchBankRek", "dd", playerid, strval(inputtext));
        }
        case DialogTransfer1:
        {
            if(!response) return 1;

            new targetid = GetRekeningOwner(AccountData[playerid][pTransferRek]);

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DialogTransfer1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Transfer",
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan jumlah nominal yang ingin anda kirim ke rekening tersebut:", "Kirim", "Batal"); 
        
            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DialogTransfer1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Transfer",
            "Error: Hanya dapat diisi angka!\nMohon masukkan jumlah nominal yang ingin anda kirim ke rekening tersebut:", "Kirim", "Batal");
        
            if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pBankMoney]) return ShowPlayerDialog(playerid, DialogTransfer1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Transfer",
            "Error: Jumlah tidak vaid!\nMohon masukkan jumlah nominal yang ingin anda kirim ke rekening tersebut:", "Kirim", "Batal");
        
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemilik rekening tersebut tidak terkoneksi ke server!");
            AccountData[targetid][pBankMoney] += strval(inputtext);
            AccountData[playerid][pBankMoney] -= strval(inputtext);
            SendClientMessageEx(targetid, -1, "[i] Anda mendapatkan transfer dari // Nama Rek: %s // Jumlah Transfer: "GREEN"%s", AccountData[playerid][pName], FormatMoney(strval(inputtext)));
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil mengirim %s ke rekening %d", FormatMoney(strval(inputtext)), AccountData[playerid][pTransferRek]));
            
            foreach(new i : Player) if (AccountData[i][pAdmin] >= 1 && IsPlayerConnected(i))
			{
				SendClientMessageEx(i, -1, ""YELLOW"[Transfer Logs]: %s(%d) Mentransfer uang sebesar %s kepada %s(%d)", AccountData[playerid][pName], playerid, FormatMoney(strval(inputtext)), AccountData[targetid][pName], targetid);
			}
            new frmxt[255];
			format(frmxt, sizeof(frmxt), "Menstransfer uang kepada rekening %d sebesar $%d", AccountData[playerid][pTransferRek], strval(inputtext));
			AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], frmxt, strval(inputtext));
            AccountData[playerid][pTransferRek] = 0;
        }
        case DialogSpotify:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan musik");
            if(response)
            {
                switch(listitem)
                {
                    case 0:
                    {
                        SendRPMeAboveHead(playerid, "Mematikan musik di Spotifynya", X11_PLUM1);
                        StopStream(playerid);
                    }
                    case 1:
                    {
                        static jskc[512];
                        format(jskc, sizeof(jskc), ""VERONA_ARWIN"Spotify Music - Cerahi Hidupmu Secerah Matahari Di Pagi Hari\n\n"VERONA_ARWIN"Kami sarankan anda untuk upload file mp3 ke discord terlebih dahulu.\n"RED_E"Note: Fitur ini tidak support link Youtube secara langsung!\n\n"YELLOW"(Apabila file mp3 telah di upload ke discord, silahkan copy linknya dan paste dibawah ini):");
                        ShowPlayerDialog(playerid, DialogSpotify1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Spotify", jskc, "Input", "Cancel");
                    }
                }
            }
        }
        case DialogSpotify1:
        {
            if(response == 1)
            {
                if(isnull(inputtext) || strlen(inputtext) == 0)
                {
                    ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum memasukan URL musik!");
                    return 1;
                }

                format(tempSpotifyURL[playerid], 256, "%s", inputtext);

                static jskc[512];
                format(jskc, sizeof(jskc), ""VERONA_ARWIN"Spotify Music - Cerahi Hidupmu Secerah Matahari Di Pagi Hari\n\n"VERONA_ARWIN"Kami sarankan anda untuk memasukan Judul dengan benar, Karna Nama judul adalah cerminan diri sendiri");
                ShowPlayerDialog(playerid, DialogSpotifyTitle, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Masukkan Judul Lagu:", jskc, "Input", "Cancel");
            }
            else
            {
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan musik");
            }
        }
        case DialogSpotifyTitle:
        {
            if(response == 1)
            {
                if(isnull(inputtext) || strlen(inputtext) == 0)
                {
                    ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum memasukan judul lagu!");
                    return 1;
                }

                // simpan judul lagu
                new title[128];
                format(title, sizeof(title), "%s", inputtext);

                // ambil URL dari memory sementara
                new url[256];
                format(url, sizeof(url), "%s", tempSpotifyURL[playerid]);

                // mainkan lagu
                PlayStream(playerid, url, 0.0, 0.0, 0.0, 1, 0);
                SendRPMeAboveHead(playerid, "Memutar lagu di Spotify", X11_PLUM1);

                // simpan ke array history
                if(SpotifyCount[playerid] < MAX_SPOTIFY_HISTORY)
                {
                    format(SpotifyHistory[playerid][SpotifyCount[playerid]], 256, "%s", url);
                    format(SpotifyTitle[playerid][SpotifyCount[playerid]], 128, "%s", title);
                    SpotifyCount[playerid]++;
                }
                else
                {
                    for(new i = 0; i < MAX_SPOTIFY_HISTORY - 1; i++)
                    {
                        format(SpotifyHistory[playerid][i], 256, "%s", SpotifyHistory[playerid][i+1]);
                        format(SpotifyTitle[playerid][i], 128, "%s", SpotifyTitle[playerid][i+1]);
                    }
                    format(SpotifyHistory[playerid][MAX_SPOTIFY_HISTORY-1], 256, "%s", url);
                    format(SpotifyTitle[playerid][MAX_SPOTIFY_HISTORY-1], 128, "%s", title);
                }

                // update database
                new query[256];
                format(query, sizeof(query), "INSERT INTO spotify_history (player_id, url, title) VALUES (%d, '%s', '%s')", AccountData[playerid][pID], url, title);
                mysql_tquery(g_SQL, query);

                Spotify_ClearOldHistory(playerid);

                /*for(new i = 0; i < SpotifyCount[playerid] && i < MAX_SPOTIFY_HISTORY; i++)
                {
                    PlayerTextDrawSetString(playerid, ATRP_SpotifyTD[playerid][i], SpotifyTitle[playerid][i]);
                    PlayerTextDrawShow(playerid, ATRP_SpotifyTD[playerid][26]);
                    PlayerTextDrawShow(playerid, ATRP_SpotifyTD[playerid][27 + i]); //box
                    PlayerTextDrawShow(playerid, ATRP_SpotifyTD[playerid][33 + i]); //logo spotify
                    PlayerTextDrawShow(playerid, ATRP_SpotifyTD[playerid][39 + i]); //title
                    PlayerTextDrawShow(playerid, ATRP_SpotifyTD[playerid][45 + i]); //titik :
                }*/
            }
            else
            {
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan input judul lagu");
            }
        }
        case LokasiGps:
        {
            if(!response) return 1;
            if(!PlayerHasItem(playerid, "Smartphone")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki smartphone!");

            switch(listitem)
            {
                case 0:
                {
                    new minsty[4096];
                    format(minsty, sizeof(minsty), "Nama\tLokasi\tJarak\
                    \nBalai Kota\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Kantor Kepolisian District \t"GRAY"%s\t"YELLOW"%.2f m\
                    \nRumah Sakit District \t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Bengkel Kota District \t"GRAY"%s\t"YELLOW"%.2f m\
                    \nAsuransi\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Asuransi LV\t"GRAY"%s\t"YELLOW"%.2f m\
                    \nRestaurant District \t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Pelabuhan\t"GRAY"%s\t"YELLOW"%.2f m\
                    \nBahamas\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Rusun Abah Iwan\t"GRAY"%s\t"YELLOW"%.2f m\
                    \nTerminal Desa\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Pasar Modern District \t"GRAY"%s\t"YELLOW"%.2f m\
                    \nShowroom District \t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Gudang Warbun\t"GRAY"%s\t"YELLOW"%.2f m\
                    \nGudang Fort Carson\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"OYO Hotels #1\t"GRAY"%s\t"YELLOW"%.2f m\
                    \nRusun Suroh\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Rusun Jamal\t"GRAY"%s\t"YELLOW"%.2f m\
                    \nToko Olahraga\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Motel Romo\t"GRAY"%s\t"YELLOW"%.2f m\
                    \nVenue District \t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Bahamas LV\t"GRAY"%s\t"YELLOW"%.2f m\
                    \nBahamas SF\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Rusun BlueDoorz\t"GRAY"%s\t"YELLOW"%.2f m\
                    \nUniversitas District \t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Panggung San Fiero\t"GRAY"%s\t"YELLOW"%.2f m\
                    \nDrag Race Las Venturas\t%s\t"YELLOW"%.2f m\
                    \nAkademy Kepolisian District\t%s\t"YELLOW"%.2f m\
                    ",
                    GetLocation(1133.9788, -2036.3195, 69.0078), GetPlayerDistanceFromPoint(playerid, 1133.9788, -2036.3195, 69.0078),
                    GetLocation(654.3464,-1470.5109,15.4395), GetPlayerDistanceFromPoint(playerid, 654.3464,-1470.5109,15.4395),
                    GetLocation(1346.7227,744.1487,10.6719), GetPlayerDistanceFromPoint(playerid, 1346.7227,744.1487,10.6719),
                    GetLocation(2851.0793,-1856.4265,11.0816), GetPlayerDistanceFromPoint(playerid, 2851.0793,-1856.4265,11.0816),
                    GetLocation(424.6763,-1322.2543,15.0031), GetPlayerDistanceFromPoint(playerid, 424.6763,-1322.2543,15.0031),//asuransi ls
                    GetLocation(51.3536, 1222.1011, 18.9170), GetPlayerDistanceFromPoint(playerid, 51.3536, 1222.1011, 18.9170),
                    GetLocation(334.0528,-1815.5964,4.3290), GetPlayerDistanceFromPoint(playerid, 334.0528,-1815.5964,4.3290),
                    GetLocation(323.3055,-1833.9069,3.7856), GetPlayerDistanceFromPoint(playerid, 323.3055,-1833.9069,3.7856),
                    GetLocation(2422.3745,-1234.7301,24.5338), GetPlayerDistanceFromPoint(playerid, 2422.3745,-1234.7301,24.5338),
                    GetLocation(2224.1106,-1152.6976,25.7977), GetPlayerDistanceFromPoint(playerid, 2224.1106,-1152.6976,25.7977),
                    GetLocation(88.39, -280.85, 1.57), GetPlayerDistanceFromPoint(playerid, 88.39, -280.85, 1.57),
                    GetLocation(2793.5034, -1087.5909, 30.7188), GetPlayerDistanceFromPoint(playerid, 2793.5034, -1087.5909, 30.7188),
                    GetLocation(557.2151,-1288.9968,17.2483), GetPlayerDistanceFromPoint(playerid, 557.2151,-1288.9968,17.2483),
                    GetLocation(2076.8, -2033.33, 13.5469), GetPlayerDistanceFromPoint(playerid, 2076.8, -2033.33, 13.5469),
                    GetLocation(-136.0707, 1116.6332, 20.1966), GetPlayerDistanceFromPoint(playerid, -136.0707, 1116.6332, 20.1966),
                    GetLocation(2223.5115, -1143.1807, 25.7969), GetPlayerDistanceFromPoint(playerid, 2223.5115, -1143.1807, 25.7969),
                    GetLocation(221.2156, -117.9283, 1.5781), GetPlayerDistanceFromPoint(playerid, 221.2156, -117.9283, 1.5781),
                    GetLocation(2183.3953, -1794.7335, 13.3606), GetPlayerDistanceFromPoint(playerid, 2183.3953, -1794.7335, 13.3606),
                    GetLocation(1386.4347, 293.3129, 19.5469), GetPlayerDistanceFromPoint(playerid, 1386.4347, 293.3129, 19.5469),
                    GetLocation(-3.3894, 1212.4326, 19.3527), GetPlayerDistanceFromPoint(playerid, -3.3894, 1212.4326, 19.3527),
                    GetLocation(836.0340, -2008.6443, 12.8672), GetPlayerDistanceFromPoint(playerid, 836.0340, -2008.6443, 12.8672),
                    GetLocation(2222.4739, 1837.4940, 10.8203), GetPlayerDistanceFromPoint(playerid, 2222.4739, 1837.4940, 10.8203),
                    GetLocation(-2442.7500, 755.2680, 35.2719), GetPlayerDistanceFromPoint(playerid, -2442.7500, 755.2680, 35.2719),
                    GetLocation(2613.9070, 732.6111, 10.8203), GetPlayerDistanceFromPoint(playerid, 2613.9070, 732.6111, 10.8203),
                    GetLocation(2819.3628, -1086.1926, 30.7333), GetPlayerDistanceFromPoint(playerid, 2819.3628, -1086.1926, 30.7333),
                    GetLocation(-2882.8586, 464.0963, 4.9141), GetPlayerDistanceFromPoint(playerid, -2882.8586, 464.0963, 4.9141),
                    GetLocation(2832.8967, 1903.7570, 10.8203), GetPlayerDistanceFromPoint(playerid, 2832.8967, 1903.7570, 10.8203),
                    GetLocation(959.2909,2402.5684,10.8203), GetPlayerDistanceFromPoint(playerid, 959.2909,2402.5684,10.8203));
                    ShowPlayerDialog(playerid, LokasiUmum, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- GPS", minsty, "Pilih", "Batal");
                }
                case 1:
                {
                    new minsty[4012];
                    format(minsty, sizeof(minsty), "Pekerjaan\tNama\tLokasi\tJarak\
                    \n"GRAY"Electrican Job\t"GRAY"( Multiplayer Job )\t"GRAY"%s\t"YELLOW"%.2f m\
                    \nSupir Bus\tTerminal District \t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Tukang Ayam #1\t"GRAY"Kandang Ayam District \t%s\t"YELLOW"%.2f m\
                    \nTukang Ayam #2\tKantor Ayam District \t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Petani #1\t"GRAY"Pembelian Bibit\t%s\t"YELLOW"%.2f m\
                    \nPetani #2\tLadang Tanaman\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Petani #3\t"GRAY"Olah Tanaman\t%s\t"YELLOW"%.2f m\
                    \nTukang Kayu\tHutan Kayu\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Kargo\t"GRAY"Pengambilan Truck Kargo\t%s\t"YELLOW"%.2f m\
                    \nPemerah Sapi\tLokasi Pemerahan\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Penambang #1\t"GRAY"Pertambangan District \t%s\t"YELLOW"%.2f m\
                    \nPenambang #2\tPencucian Batu\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Penambang #3\t"GRAY"Peleburan Batu\t%s\t"YELLOW"%.2f m\
                    \nPenjahit #1\tKantor Penjahit\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Penjahit #2\t"GRAY"Penjualan Pakaian\t%s\t"YELLOW"%.2f m\
                    \nRecycler #1\tTempat Penyortiran\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Recycler #2\t"GRAY"Tempat Daur Ulang\t%s\t"YELLOW"%.2f m\
                    \nTukang Minyak #1\tAmbil Minyak\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Tukang Minyak #2\t"GRAY"Refined Minyak\t%s\t"YELLOW"%.2f m\
                    \nTukang Minyak #3\tMixxing Minyak\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Tukang Minyak #4\t"GRAY"Penjualan Gas\t%s\t"YELLOW"%.2f m\
                    \nNelayan #1\tRental Perahu\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Nelayan #2\t"GRAY"Penangkapan Ikan\t"GRAY"%s\t"YELLOW"%.2f m\
                    \nDriver Mixer\t"GRAY"Mulai Bekerja\t"GRAY"%s\t"YELLOW"%.2f m\
                    \n"GRAY"Trashmaster\tSidejob\t%s\t"YELLOW"%.2f m\
                    \nMower\t"GRAY"Sidejob\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Sweeper\tSidejob\t%s\t"YELLOW"%.2f m\
                    \nDelivery\t"GRAY"Sidejob\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Forklift\tSidejob\t%s\t"YELLOW"%.2f m\
                    ",
                    GetLocation(-2521.1821, -621.8853, 132.7418), GetPlayerDistanceFromPoint(playerid, -2521.1821, -621.8853, 132.7418),
                    GetLocation(96.0680,-272.6256,1.5781), GetPlayerDistanceFromPoint(playerid, 96.0680,-272.6256,1.5781),
                    GetLocation(1546.5872,28.7098,24.1406), GetPlayerDistanceFromPoint(playerid, 1546.5872,28.7098,24.1406),
                    GetLocation(1911.8618,164.4111,37.1539), GetPlayerDistanceFromPoint(playerid, 1911.8618,164.4111,37.1539),
                    GetLocation(-547.7806, -185.1288, 78.4063), GetPlayerDistanceFromPoint(playerid, -547.7806, -185.1288, 78.4063),
                    GetLocation(-376.1269, -1439.9231, 25.7266), GetPlayerDistanceFromPoint(playerid, -376.1269, -1439.9231, 25.7266),
                    GetLocation(3.9224, 66.8390, 3.1172), GetPlayerDistanceFromPoint(playerid, 3.9224, 66.8390, 3.1172),
                    GetLocation(-439.7503, -62.3335, 58.9720), GetPlayerDistanceFromPoint(playerid, -439.7503, -62.3335, 58.9720),
                    GetLocation(-1704.2260, 49.6503, 3.5495), GetPlayerDistanceFromPoint(playerid, -1704.2260, 49.6503, 3.5495),
                    GetLocation(306.8608,1141.2626,8.5859), GetPlayerDistanceFromPoint(playerid, 306.8608,1141.2626,8.5859),
                    GetLocation(686.9853,895.7302,-39.5328), GetPlayerDistanceFromPoint(playerid, 686.9853,895.7302,-39.5328),
                    GetLocation(-412.7031, 1197.8976, 2.2932), GetPlayerDistanceFromPoint(playerid, -412.7031, 1197.8976, 2.2932),
                    GetLocation(2182.6780,-2259.5010,13.3878), GetPlayerDistanceFromPoint(playerid, 2182.6780,-2259.5010,13.3878),
                    GetLocation(2348.7112, -82.1600, 26.3359), GetPlayerDistanceFromPoint(playerid, 2348.7112, -82.1600, 26.3359),
                    GetLocation(676.1796,-619.9467,16.3359), GetPlayerDistanceFromPoint(playerid, 676.1796,-619.9467,16.3359),
                    GetLocation(2297.9268, 2764.1992, 10.8203), GetPlayerDistanceFromPoint(playerid, 2297.9268, 2764.1992, 10.8203),
                    GetLocation(-31.6359, 1386.9554, 9.1719), GetPlayerDistanceFromPoint(playerid, -31.6359, 1386.9554, 9.1719),
                    GetLocation(471.9127, 1299.1512, 9.7176), GetPlayerDistanceFromPoint(playerid, 471.9127, 1299.1512, 9.7176),
                    GetLocation(497.5595, 1518.7350, 1.0000), GetPlayerDistanceFromPoint(playerid, 497.5595, 1518.7350, 1.0000),
                    GetLocation(279.6849, 1348.9515, 10.5859), GetPlayerDistanceFromPoint(playerid, 279.6849, 1348.9515, 10.5859),
                    GetLocation(1929.94, -1776.33, 13.5469), GetPlayerDistanceFromPoint(playerid, 1929.94, -1776.33, 13.5469),
                    GetLocation(111.3999, -1895.6553, 2.9408), GetPlayerDistanceFromPoint(playerid, 111.3999, -1895.6553, 2.9408),
                    GetLocation(352.4596, -2669.7722, -0.0401), GetPlayerDistanceFromPoint(playerid, 352.4596, -2669.7722, -0.0401),
                    GetLocation(641.2187,1238.3390,11.6796), GetPlayerDistanceFromPoint(playerid, 641.2187,1238.3390,11.6796),
                    GetLocation(1037.3827, -305.1682, 74.0922), GetPlayerDistanceFromPoint(playerid, 1037.3827, -305.1682, 74.0922),
                    GetLocation(2118.1814, -1188.9286, 23.9358), GetPlayerDistanceFromPoint(playerid, 2118.1814, -1188.9286, 23.9358),
                    GetLocation(604.9979, -1508.6365, 14.9549), GetPlayerDistanceFromPoint(playerid, 604.9979, -1508.6365, 14.9549),
                    GetLocation(1001.3441, -1445.8391, 13.5469), GetPlayerDistanceFromPoint(playerid, 1001.3441, -1445.8391, 13.5469),
                    GetLocation(-1723.7289, -63.5671, 3.5547), GetPlayerDistanceFromPoint(playerid, -1723.7289, -63.5671, 3.5547));
                    ShowPlayerDialog(playerid, LokasiPekerjaan, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- GPS", minsty, "Pilih", "Batal");
                }
                case 2:
                {
                    new minsty[1218];
                    format(minsty, sizeof(minsty), "Hobi\tNama\tLokasi\tJarak\
                    \nMemancing #1\tSpot Pemancingan\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Memancing #2\t"GRAY"Penjualan Ikan\t%s\t"YELLOW"%.2f m\
                    \nBerburu #1\tSpot Perburuan\t%s\t"YELLOW"%.2f m\
                    \n"GRAY"Berburu #2\t"GRAY"Penjualan Hasil Buruan\t%s\t"YELLOW"%.2f m\
                    ",
                    GetLocation(383.1566,-2075.2007,7.8359), GetPlayerDistanceFromPoint(playerid, 383.1566,-2075.2007,7.8359),
                    GetLocation(1052.0156,-345.4073,73.9922), GetPlayerDistanceFromPoint(playerid, 1052.0156,-345.4073,73.9922),
                    GetLocation(-387.3126,-2259.8279,45.5646), GetPlayerDistanceFromPoint(playerid, -387.3126,-2259.8279,45.5646),
                    GetLocation(-1693.3431,-88.9088,3.5654), GetPlayerDistanceFromPoint(playerid, -1693.3431,-88.9088,3.5654));
                    ShowPlayerDialog(playerid, LokasiHobi, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- GPS", minsty, "Pilih", "Batal");
                }
                case 3:
                {
                    ShowPlayerDialog(playerid, LokasiPertokoan, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- GPS",
                    "Toko Pakaian\
                    \n"GRAY"Toko Elektronik\
                    \n"GRAY"Toko Shop", "Pilih", "Batal");
                }
                case 4:
                {
                    ShowAtmLocation(playerid);
                }
                case 5:
                {
                    ShowGarasiLocation(playerid);
                }
                case 6:
                {
                    ShowTrashLocation(playerid);
                }
                case 7: // Pom bensin
                {
                    if(GetGStationNearest(playerid) <= 0)
						return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Pom Bensin di dekat anda");

					new id, count = GetGStationNearest(playerid), mission[2024], lstr[3024];

					strcat(mission,"No\tLokasi\tJarak\n",sizeof(mission));
					Loop(itt, (count + 1), 1)
					{
						id = ReturnGStationNearestID(playerid, itt);
						if(itt == count)
						{
							format(lstr,sizeof(lstr), "%d\t%s\t%0.0fm\n", itt, GetLocation(gsData[id][gsPosX], gsData[id][gsPosY], gsData[id][gsPosZ]), GetPlayerDistanceFromPoint(playerid, gsData[id][gsPosX], gsData[id][gsPosY], gsData[id][gsPosZ]));
						}
						else format(lstr,sizeof(lstr), "%d\t%s\t%0.0fm\n", itt, GetLocation(gsData[id][gsPosX], gsData[id][gsPosY], gsData[id][gsPosZ]), GetPlayerDistanceFromPoint(playerid, gsData[id][gsPosX], gsData[id][gsPosY], gsData[id][gsPosZ]));
						strcat(mission,lstr,sizeof(mission));
					}
					ShowPlayerDialog(playerid, GPS_NEAREST_GSTATION, DIALOG_STYLE_TABLIST_HEADERS,"Nearest Gas Station",mission,"Select","Cancel");
					return 1;
                }
                case 8: // Bengkel Modshop
                {
                    SetPlayerRaceCheckpoint(playerid, 1, 1101.4049, -1233.4498, 15.8203, 1101.4049, -1233.4498, 15.8203, 5.0);
                    pMapCP[playerid] = true;
                    
                    //(playerid,  1101.4049, -1233.4498, 15.8203, COLOR_BLUE);
                    Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                }
                case 9:// Rumah saya
                {
                    new bool: found = false;
                    foreach(new id : House)
                    {
                        if(House_HaveAccess(playerid, id))
                        {
                            AccountData[playerid][pTrackHoused] = true;
                            SetPlayerRaceCheckpoint(playerid, 1, HouseData[id][hsExtPos][0], HouseData[id][hsExtPos][1], HouseData[id][hsExtPos][2], HouseData[id][hsExtPos][0], HouseData[id][hsExtPos][1], HouseData[id][hsExtPos][2], 4.0);
                            ShowTDN(playerid, NOTIFICATION_INFO, "Lokasi telah ditandai di map!");
                            
                            //(playerid,  HouseData[id][hsExtPos][0], HouseData[id][hsExtPos][1], HouseData[id][hsExtPos][2], COLOR_BLUE);
                            found = true;
                        }
                    }
                    if(!found) ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki/memegang kunci Rumah!");
                }
                case 10: //rumah tersedia
                {
                    ShowHouseTersedia(playerid);
                }
                case 11:
                {
                    ShowWorkshopLocation(playerid);
                }
                case 12:
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menghapus Checkpoint");
                    pMapCP[playerid] = false;
                }
                case 13:
                {
                    if(!IsValidDynamicMapIcon(SharelocSender[playerid]))
                    {
                        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada yang mengirimkan anda share lokasi!");
                    }
                    else
                    {
                        ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menghapus Shareloc!");

                        DestroyDynamicMapIcon(SharelocSender[playerid]);
                        SharelocSender[playerid] = INVALID_STREAMER_ID;
                        SharelocTimer[playerid] = 0;
                    }
                }
            }
        }
        case LokasiHouseTersedia:
        {
            if(!response)
            {
                return ShowPlayerDialog(playerid, LokasiGps, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Lokasi",
                "Lokasi Umum\
                \n"GRAY"Lokasi Pekerjaan\
                \nLokasi Hobi\
                \n"GRAY"Lokasi Warung\
                \nATM Kota\
                \n"GRAY"Garasi Umum\
                \nTong Sampah Kota\
                \nPom Bensin Kota\
                \n"GRAY"Bengkel Modshop\
                \nRumah Saya\
                \nRumah Tersedia\
                \nWorkshop\
                \n"RED"(Disable Checkpoint)\
                \n"RED"(Disable Shareloc)", "Pilih", "Batal");
            }
            if(response)
            {
                new houseid = PlayerHouseList[playerid][listitem];
                if(houseid >= 0 && houseid < MAX_RUMAH)
                {
                    new Float:x = HouseData[houseid][hsExtPos][0];
                    new Float:y = HouseData[houseid][hsExtPos][1];
                    new Float:z = HouseData[houseid][hsExtPos][2];

                    
                    DisablePlayerRaceCheckpoint(playerid);
                    SetPlayerRaceCheckpoint(playerid, 1, x, y, z, x, y, z, 4.0);
                    //(playerid,  x, y, z, COLOR_BLUE);
                    Info(playerid, "Lokasi Rumah telah di tandai di map!");
                }
            }
        }
        case LokasiPertokoan:
        {
            if(!response)
            {
                return ShowPlayerDialog(playerid, LokasiGps, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Lokasi",
                "Lokasi Umum\
                \n"GRAY"Lokasi Pekerjaan\
                \nLokasi Hobi\
                \n"GRAY"Lokasi Warung\
                \nATM Kota\
                \n"GRAY"Garasi Umum\
                \nTong Sampah Kota\
                \nPom Bensin Kota\
                \n"GRAY"Bengkel Modshop\
                \nRumah Saya\
                \nRumah Tersedia\
                \nWorkshop\
                \n"RED"(Disable Checkpoint)\
                \n"RED"(Disable Shareloc)", "Pilih", "Batal");
            }
            if(response)
            {
                switch(listitem)
                {
                    case 0:
                    {
                        ShowClothesLocation(playerid);
                    }
                    case 1:
                    {
                        ShowElekLocation(playerid);
                    }
                    case 2:
                    {
                        ShowShopLocation(playerid);
                    }
                }
            }
        }
        case LokasiPekerjaan:
        {
            if(!response) 
            {
                return ShowPlayerDialog(playerid, LokasiGps, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Lokasi",
                "Lokasi Umum\
                \n"GRAY"Lokasi Pekerjaan\
                \nLokasi Hobi\
                \n"GRAY"Lokasi Warung\
                \nATM Kota\
                \n"GRAY"Garasi Umum\
                \nTong Sampah Kota\
                \nPom Bensin Kota\
                \n"GRAY"Bengkel Modshop\
                \nRumah Saya\
                \nRumah Tersedia\
                \nWorkshop\
                \n"RED"(Disable Checkpoint)\
                \n"RED"(Disable Shareloc)", "Pilih", "Batal");
            }
            if(response)
            {
                switch(listitem)
                {
                    case 0:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, -2521.1821, -621.8853, 132.7418, -2521.1821, -621.8853, 132.7418, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  -2521.1821, -621.8853, 132.7418, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 1:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 96.0680,-272.6256,1.5781, 96.0680,-272.6256,1.5781, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  96.0680,-272.6256,1.5781, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 2:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 1546.5872,28.7098,24.1406, 1546.5872,28.7098,24.1406, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  1546.5872,28.7098,24.1406, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 3:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 1911.8618,164.4111,37.1539, 1911.8618,164.4111,37.1539, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  1911.8618,164.4111,37.1539, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 4:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, -547.7806, -185.1288, 78.4063, -547.7806, -185.1288, 78.4063, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  -547.7806, -185.1288, 78.4063, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 5:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, -376.1269, -1439.9231, 25.7266, -376.1269, -1439.9231, 25.7266, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  -376.1269, -1439.9231, 25.7266, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 6:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 3.9224, 66.8390, 3.1172, 3.9224, 66.8390, 3.1172, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  3.9224, 66.8390, 3.1172, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 7:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, -439.7503, -62.3335, 58.9720, -439.7503, -62.3335, 58.9720, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  -439.7503, -62.3335, 58.9720, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 8:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, -1704.2260, 49.6503, 3.5495, -1704.2260, 49.6503, 3.5495, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  -1704.2260, 49.6503, 3.5495, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 9:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 306.8608,1141.2626,8.5859, 306.8608,1141.2626,8.5859, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  306.8608,1141.2626,8.5859, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 10:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 686.9853,895.7302,-39.5328, 686.9853,895.7302,-39.5328, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid, 686.9853,895.7302,-39.5328, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 11:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, -412.7031, 1197.8976, 2.2932, -412.7031, 1197.8976, 2.2932, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  -412.7031, 1197.8976, 2.2932, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 12:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 2182.6780,-2259.5010,13.3878, 2182.6780,-2259.5010,13.3878, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  2182.6780,-2259.5010,13.3878, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 13:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 2348.7112, -82.1600, 26.3359, 2348.7112, -82.1600, 26.3359, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  2348.7112, -82.1600, 26.3359, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 14:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 676.1796,-619.9467,16.3359, 676.1796,-619.9467,16.3359, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,   676.1796,-619.9467,16.3359, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 15:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 2297.9268, 2764.1992, 10.8203, 2297.9268, 2764.1992, 10.8203, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  2297.9268, 2764.1992, 10.8203, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 16:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, -31.6359, 1386.9554, 9.1719, -31.6359, 1386.9554, 9.1719, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  1-31.6359, 1386.9554, 9.1719, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 17:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 471.9127, 1299.1512, 9.7176, 471.9127, 1299.1512, 9.7176, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  471.9127, 1299.1512, 9.7176, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 18:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 497.5595, 1518.7350, 1.0000, 497.5595, 1518.7350, 1.0000, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  497.5595, 1518.7350, 1.0000, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 19:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 279.6849, 1348.9515, 10.5859, 279.6849, 1348.9515, 10.5859, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  279.6849, 1348.9515, 10.5859, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 20:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 1929.94, -1776.33, 13.5469, 1929.94, -1776.33, 13.5469, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  1929.94, -1776.33, 13.5469, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 21:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 111.3999, -1895.6553, 2.9408, 111.3999, -1895.6553, 2.9408, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  111.3999, -1895.6553, 2.9408, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 22:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 352.4596, -2669.7722, -0.0401, 352.4596, -2669.7722, -0.0401, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  352.4596, -2669.7722, -0.0401, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 23:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 641.2187,1238.3390,11.6796, 641.2187,1238.3390,11.6796, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  641.2187,1238.3390,11.6796, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 24:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 1037.3827, -305.1682, 74.0922, 1037.3827, -305.1682, 74.0922, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  1037.3827, -305.1682, 74.0922, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 25:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 2118.1814, -1188.9286, 23.9358, 2118.1814, -1188.9286, 23.9358, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  2118.1814, -1188.9286, 23.9358, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 26:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 604.9979, -1508.6365, 14.9549, 604.9979, -1508.6365, 14.9549, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  604.9979, -1508.6365, 14.9549, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 27:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 1001.3441, -1445.8391, 13.5469, 1001.3441, -1445.8391,13.5469, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  1001.3441, -1445.8391, 13.5469, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 28:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, -1723.7289, -63.5671, 3.5547, -1723.7289, -63.5671,3.5547, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  -1723.7289, -63.5671, 3.5547, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                }
            }
        }
        case LokasiUmum:
        {
            if(!response)
            {
                return ShowPlayerDialog(playerid, LokasiGps, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Lokasi",
                "Lokasi Umum\
                \n"GRAY"Lokasi Pekerjaan\
                \nLokasi Hobi\
                \n"GRAY"Lokasi Warung\
                \nATM Kota\
                \n"GRAY"Garasi Umum\
                \nTong Sampah Kota\
                \nPom Bensin Kota\
                \n"GRAY"Bengkel Modshop\
                \nRumah Saya\
                \nRumah Tersedia\
                \nWorkshop\
                \n"RED"(Disable Checkpoint)\
                \n"RED"(Disable Shareloc)", "Pilih", "Batal");
            }
            if(response)
            {
                switch(listitem)
                {
                    case 0:
                    {
                        
                        SetPlayerRaceCheckpoint(playerid, 1, 1133.9788, -2036.3195, 69.0078, 1133.9788, -2036.3195, 69.0078, 5.0);
                        //(playerid, 1133.9788, -2036.3195, 69.0078, COLOR_BLUE);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        pMapCP[playerid] = true;
                    }
                    case 1:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 654.3464,-1470.5109,15.4395, 654.3464,-1470.5109,15.4395, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  654.3464,-1470.5109,15.4395, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 2:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1,1346.7227,744.1487,10.6719, 1346.7227,744.1487,10.6719, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  1346.7227,744.1487,10.6719, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 3:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 2851.0793,-1856.4265,11.0816, 2851.0793,-1856.4265,11.0816, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  2851.0793,-1856.4265,11.0816, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 4:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 424.6763,-1322.2543,15.0031, 424.6763,-1322.2543,15.0031, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  424.6763,-1322.2543,15.0031, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 5:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 51.3536, 1222.1011, 18.9170, 51.3536, 1222.1011, 18.9170, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  51.3536, 1222.1011, 18.9170, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 6:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 334.0528,-1815.5964,4.3290, 334.0528,-1815.5964,4.3290, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  334.0528,-1815.5964,4.3290, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 7:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 323.3055,-1833.9069,3.7856, 323.3055,-1833.9069,3.7856, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  323.3055,-1833.9069,3.7856, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 8:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 2422.3745,-1234.7301,24.5338, 2422.3745,-1234.7301,24.5338, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        pMapCP[playerid] = true;
                        //(playerid,  2422.3745,-1234.7301,24.5338, COLOR_BLUE);
                    }
                    case 9:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 2224.1106,-1152.6976,25.7977, 2224.1106,-1152.6976,25.7977, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  2224.1106,-1152.6976,25.7977, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 10:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 88.39, -280.85, 1.57, 88.39, -280.85, 1.57, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  88.39, -280.85, 1.57, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 11:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 1479.5343,713.0022,10.8203, 1479.5343,713.0022,10.8203, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  1479.5343,713.0022,10.8203, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 12:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 557.2151,-1288.9968,17.2483, 557.2151,-1288.9968,17.2483, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  557.2151,-1288.9968,17.2483, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 13:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 2076.8, -2033.33, 13.5469, 2076.8, -2033.33, 13.5469, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  2076.8, -2033.33, 13.5469, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 14:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, -136.0707, 1116.6332, 20.1966, -136.0707, 1116.6332, 20.1966, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  -136.0707, 1116.6332, 20.1966, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 15:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 2223.5115, -1143.1807, 25.7969, 2223.5115, -1143.1807, 25.7969, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  2223.5115, -1143.1807, 25.7969, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 16:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 221.2156, -117.9283, 1.5781, 221.2156, -117.9283, 1.5781, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  221.2156, -117.9283, 1.5781, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 17:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 2183.3953, -1794.7335, 13.3606, 2183.3953, -1794.7335, 13.3606, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  2183.3953, -1794.7335, 13.3606, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 18:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 1386.4347, 293.3129, 19.5469, 1386.4347, 293.3129, 19.5469, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  1386.4347, 293.3129, 19.5469, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 19:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, -3.3894, 1212.4326, 19.3527, -3.3894, 1212.4326, 19.3527, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  -3.3894, 1212.4326, 19.3527, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 20:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 836.0340, -2008.6443, 12.8672, 836.0340, -2008.6443, 12.8672, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  836.0340, -2008.6443, 12.8672, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 21:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 2222.4739, 1837.4940, 10.8203, 2222.4739, 1837.4940, 10.8203, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  2222.4739, 1837.4940, 10.8203, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 22:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, -2442.7500, 755.2680, 35.2719, -2442.7500, 755.2680, 35.2719, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  -2442.7500, 755.2680, 35.2719, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 23:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 2613.9070, 732.6111, 10.8203, 2613.9070, 732.6111, 10.8203, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid, 2613.9070, 732.6111, 10.8203, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 24:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 2819.3628, -1086.1926, 30.7333, 2819.3628, -1086.1926, 30.7333, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  2819.3628, -1086.1926, 30.7333, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 25:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, -2882.8586, 464.0963, 4.9141, -2882.8586, 464.0963, 4.9141, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  -2882.8586, 464.0963, 4.9141, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 26:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 2832.8967, 1903.7570, 10.8203, 2832.8967, 1903.7570, 10.8203, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  2832.8967, 1903.7570, 10.8203, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 27:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 959.2909,2402.5684,10.8203,959.2909,2402.5684,10.8203, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  2832.8967, 1903.7570, 10.8203, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                }
            }
        }
        case LokasiHobi:
        {
            if(!response) 
            {
                return ShowPlayerDialog(playerid, LokasiGps, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Lokasi",
                "Lokasi Umum\
                \n"GRAY"Lokasi Pekerjaan\
                \nLokasi Hobi\
                \n"GRAY"Lokasi Warung\
                \nATM Kota\
                \n"GRAY"Garasi Umum\
                \nTong Sampah Kota\
                \nPom Bensin Kota\
                \n"GRAY"Bengkel Modshop\
                \nRumah Saya\
                \nRumah Tersedia\
                \nWorkshop\
                \n"RED"(Disable Checkpoint)\
                \n"RED"(Disable Shareloc)", "Pilih", "Batal");
            }
            if(response)
            {
                switch(listitem)
                {
                    case 0:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 383.1566,-2075.2007,7.8359, 383.1566,-2075.2007,7.8359, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  383.1566,-2075.2007,7.8359, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 1:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, 359.720977, -2032.062255, 7.835937, 359.720977, -2032.062255, 7.835937, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid, 359.720977, -2032.062255, 7.835937, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 2:
                    {
                        SetPlayerRaceCheckpoint(playerid, 1, -387.3126,-2259.8279,45.5646, -387.3126,-2259.8279,45.5646, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,   -387.3126,-2259.8279,45.5646, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                    case 3:
                    {   
                        SetPlayerRaceCheckpoint(playerid, 1, -1693.3431,-88.9088,3.5654, -1693.3431,-88.9088,3.5654, 5.0);
                        Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda");
                        
                        //(playerid,  -1693.3431,-88.9088,3.5654, COLOR_BLUE);
                        pMapCP[playerid] = true;
                    }
                }
            }
        }
    }
    return 1;
}


/*ShowPlayerTwitterPage(playerid)
{
    mysql_query(g_SQL, "SELECT * FROM `tweets` WHERE `ID`=1 ORDER BY `TwitterDate` ASC LIMIT 30");
    new rows = cache_num_rows(), list[4500], tempTweetFrom[24], tempTweetDate[64], tempTweetText[128];
    if(rows)
    {
        if(rows >= 30)
        {
            mysql_tquery(g_SQL, "DELETE FROM `tweets` WHERE `ID`=1");
        }

        format(list, sizeof(list), "Username\tTanggal\tPostingan\n");
        for(new i; i < rows; ++i)
        {
            cache_get_value_name(i, "TwitterFrom", tempTweetFrom);
            cache_get_value_name(i, "TwitterDate", tempTweetDate);
            cache_get_value_name(i, "TwitterText", tempTweetText);

            format(list, sizeof(list), "%s"VTWITTER"@%s\t"GRAY"%s\t"WHITE"%s\n", list, tempTweetFrom, tempTweetDate, tempTweetText);
        }
        ShowPlayerDialog(playerid, DIALOG_TWITTER_POST, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Tweets", list, "Tweet", "Kembali");
    }
    else 
    {
        format(list, sizeof(list), "Username\tTanggal\tPostingan\n");
        format(list, sizeof(list), "%sJadilah orang pertama yang membagikan Tweet", list);
        ShowPlayerDialog(playerid, DIALOG_TWITTER_POST_EMPTY, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Tweets", list, "Tweet", "Kembali");
    }
	return 1;
}*/

ShowPlayerYellowsPage(playerid)
{
    AccountData[playerid][CurrentlyReadYellow] = true;
    mysql_query(g_SQL, "SELECT * FROM `yellowpages` WHERE `ID`=1 ORDER BY `YellowDate` ASC LIMIT 30");
    new rowcount = cache_num_rows(), list[4500], tempYellowFrom[24], tempYellowDate[64], tempYellowText[128], tempYellowPhone[24];
    if(rowcount)
    {
        if(rowcount >= 30)
        {
            mysql_tquery(g_SQL, "DELETE FROM `yellowpages` WHERE `ID`=1");
        }

        format(list, sizeof(list), "Nama\tTanggal\tIklan\n");
        for(new i; i < rowcount; ++i)
        {
            cache_get_value_name(i, "YellowFrom", tempYellowFrom);
            cache_get_value_name(i, "YellowPhone", tempYellowPhone);
            cache_get_value_name(i, "YellowDate", tempYellowDate);
            cache_get_value_name(i, "YellowText", tempYellowText);
            
            if(strlen(tempYellowText) > 24) {
                format(list, sizeof(list), "%s"YELLOW"%s - %s\t"GRAY"%s\t"WHITE"%.24s...\n", list, tempYellowFrom, tempYellowPhone, tempYellowDate, tempYellowText);
            } else format(list, sizeof(list), "%s"YELLOW"%s - %s\t"GRAY"%s\t"WHITE"%s\n", list, tempYellowFrom, tempYellowPhone, tempYellowDate, tempYellowText);
        }
        ShowPlayerDialog(playerid, DIALOG_YELLOW_PAGE, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Yellow Pages", list, "Iklan", "Kembali");
    }
    else
    {
        format(list, sizeof(list), "Nama\tTanggal\tIklan\n");
        format(list, sizeof(list), "%sJadilah orang pertama yang membuat iklan!", list);
        ShowPlayerDialog(playerid, DIALOG_YELLOW_PAGE_EMPTY, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Yellow Pages", list, "Iklan", "Kembali");
    }
    return 1;
}

forward SearchBankRek(playerid, norekening);
public SearchBankRek(playerid, norekening)
{
    if(!cache_num_rows())
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Nomor rekening tidak terdaftar!");
        return 1;
    }
    else 
    {
        new ownerRek = GetRekeningOwner(norekening);
        if(!IsPlayerConnected(ownerRek)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
        AccountData[playerid][pTransferRek] = norekening;
        ShowPlayerDialog(playerid, DialogTransfer1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Transfer",
        "Mohon masukkan jumlah nominal yang ingin anda kirim ke rekening tersebut:", "Kirim", "Batal");
    }
    return 1;
}

Dialog:DialogLainnya(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                Dialog_Show(playerid, SettingPhone, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Pengaturan",
                "Tentang Ponsel\
                \n"GRAY"Ubah Nada Dering Telepon\
                \nHapus Nada Dering\
                \n"GRAY"%s Mode Pesawat", "Pilih", "Batal", AccountData[playerid][phoneAirplaneMode] ? "Matikan" : "Nyalakan");
            }
            case 1:
            {
                callcmd::myv(playerid, "");
            }
            case 2:
            {
                callcmd::mprice(playerid, "");
            }
        }
    }
    else ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    return 1;
}

Dialog:DialogFactionCall(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                Dialog_Show(playerid, CALLCENTER_POLISI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Darurat Polisi",
                "Masukkan kendala anda yang ingin dilaporkan kepada pihak kepolisian dibawah ini\
                \nJelaskan detail dan kendala yang sedang kamu alami dan ingin lapor ke kepolisian:", "Kirim", "Batal");
            }
            case 1:
            {
                Dialog_Show(playerid, CALLCENTER_EMS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Darurat Rumah Sakit",
                "Masukkan kendala anda yang ingin dilaporkan kepada pihak Rumah Sakit dibawah ini\
                \nJelaskan detail dan kendala yang sedang kamu alami dan ingin lapor ke Rumah Sakit:", "Kirim", "Batal");
            }
            case 2:
            {
                if(AccountData[playerid][phoneAirplaneMode]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone anda sedang Mode Pesawat!");
                if(AccountData[playerid][pTaxiPlayer] != INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang menjadi penumpang di Trans!");
                
                ShowPlayerDialog(playerid, DIALOG_TRANSORDER, DIALOG_STYLE_INPUT, ""TCRP"District "WHITE"- Pesan Transportasi",
                "Hai, kamu ingin memesan Trans, mau kemana hari ini?", "Input", "Batal");
            }
            case 3:
            {
                Dialog_Show(playerid, CALLCENTER_BENGKEL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Bengkel",
                "Masukkan kendala anda yang ingin dilaporkan kepada pihak Bengkel dibawah ini\
                \nJelaskan detail dan kerusakan yang sedang kamu alami agar karyawan Bengkel dapat membantu:", "Kirim", "Batal");
            }
            case 4:
            {
                Dialog_Show(playerid, CALLCENTER_RESTAURANT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Restaurant",
                "Masukkan pesanan atau kebutuhan anda yang ingin dilaporkan kepada pihak Restaurant dibawah ini\
                \nJelaskan detail pesanan atau permintaan agar karyawan Restaurant dapat membantu:", "Kirim", "Batal");
            }
        }
    }
    else ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    return 1;
}

Dialog:SettingPhone(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0: //ttg ponsel
            {
                static minsty[200];
                format(minsty, sizeof(minsty), "Aevhone X25 Milik: %s\
                \nNomor Telepon: %s\
                \nNama Series Model: X25\
                \nNomor Serial: VR81AXS23S33\nIMEI (slot 1): 7182991211\nIMEI (slot 2): 9928192882", ReturnName(playerid), AccountData[playerid][pPhone]);
                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Tentang Ponsel", minsty, "Tutup", "");
            }
            case 1: // Ubah Nada Dering
            {
                Dialog_Show(playerid, PhoneRingtone, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Ubah Nada Dering",
                "Mohon masukkan link mp3 yang sudah anda upload dimanapun itu untuk dijadikan sebagai nada dering saat ada panggilan masuk\
                \nNOTE: Tidak dapat memasukkan link langsung dari YouTube!", "Submit", "Batal");
            }
            case 2: // Hapus Nada Dering
            {
                AccountData[playerid][phoneCallRingtone][0] = EOS;
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menghapus nada dering!");
            }
            case 3: // Mode Pesawat
            {
                switch(AccountData[playerid][phoneAirplaneMode])
                {
                    case false:
                    {
                        AccountData[playerid][phoneAirplaneMode] = true;
                        ShowTDN(playerid, NOTIFICATION_INFO, "Anda mengaktifkan Mode Pesawat");
                    }
                    case true:
                    {
                        AccountData[playerid][phoneAirplaneMode] = false;
                        ShowTDN(playerid, NOTIFICATION_INFO, "Anda menonaktifkan Mode Pesawat");
                    }
                }
            }
        }
    }
    else ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    return 1;
}

Dialog:PhoneRingtone(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        return Dialog_Show(playerid, SettingPhone, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Pengaturan",
        "Tentang Ponsel\
        \nUbah Nada Dering Telepon", "Pilih", "Batal");
    }

    if(isnull(inputtext)) return Dialog_Show(playerid, PhoneRingtone, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Ubah Nada Dering",
    "Error: Tidak dapat diisi kosong!\nMohon masukkan link mp3 yang sudah anda upload dimanapun itu untuk dijadikan sebagai nada dering saat ada panggilan masuk\
    \nNOTE: Tidak dapat memasukkan link langsung dari YouTube!", "Submit", "Batal");
    
    if(IsNumeric(inputtext)) return Dialog_Show(playerid, PhoneRingtone, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Ubah Nada Dering",
    "Error: Tidak dapat diisi angka!\nMohon masukkan link mp3 yang sudah anda upload dimanapun itu untuk dijadikan sebagai nada dering saat ada panggilan masuk\
    \nNOTE: Tidak dapat memasukkan link langsung dari YouTube!", "Submit", "Batal");

    format(AccountData[playerid][phoneCallRingtone], 128, inputtext);
    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengubah nada dering panggilan!");
    return 1;
}

Dialog:GpsMenu(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0: //Lokasi GPS
            {
                ShowPlayerDialog(playerid, LokasiGps, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Lokasi",
                "Lokasi Umum\
                \n"GRAY"Lokasi Pekerjaan\
                \nLokasi Hobi\
                \n"GRAY"Lokasi Warung\
                \nATM Kota\
                \n"GRAY"Garasi Umum\
                \nTong Sampah Kota\
                \nPom Bensin Kota\
                \n"GRAY"Bengkel Modshop\
                \nRumah Saya\
                \nRumah Tersedia\
                \nWorkshop\
                \n"RED"(Disable Checkpoint)\
                \n"RED"(Disable Shareloc)", "Pilih", "Batal");
            }
            case 1: // Emergency Signal
            {
                if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Mitra EMS District !");
                if(!AccountData[playerid][pDutyEms]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang duty EMS!");

                new list[525], count = 0;
                format(list, sizeof(list), "#No\tKorban\tLokasi\n");
                foreach(new i : Player) if (AccountData[i][pSpawned] && SignalExists[i])
                {
                    format(list, sizeof(list), "%s%d\t%s(%d)\t%s\n", list, count, ReturnName(i), i, GetLocation(SignalPos[i][0], SignalPos[i][1], SignalPos[i][2]));
                    ListSignal[playerid][count ++] = i;
                }

                if(count == 0)
                {
                    return Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Emergency Signal",
                    "Tidak ada seseorang manapun yang mengirim Emergency Signal!", "Tutup", "");
                }

                Dialog_Show(playerid, EmergencySignal, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Emergency Signal", list, "Pilih", "Batal");
            }
        }
    }
    return 1;
}

Dialog:EmergencySignal(playerid, response, listitem, inputtext[])
{
    if(response)
    {   
        if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Mitra EMS District !");
        if(!AccountData[playerid][pDutyEms]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang duty EMS!");

        new id = ListSignal[playerid][listitem];
        if(!IsPlayerConnected(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
        if(!SignalExists[id]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Emergency signal sudah tidak ada/dihandle anggota lain!"); 
        // if(!AccountData[id][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Orang yang mengirim signal sudah terbangun dari pingsannya!");
        
        SetPlayerRaceCheckpoint(playerid, 1, SignalPos[id][0], SignalPos[id][1], SignalPos[id][2], 0.0, 0.0, 0.0, 4.0);
        Info(playerid, "Anda telah menerima signal emergency di daerah "YELLOW"%s", GetLocation(SignalPos[id][0], SignalPos[id][1], SignalPos[id][2]));
        Info(id, "Anggota Mitra EMS telah merespon signal emergency yang anda kirim. Harap tunggu di lokasi hingga petugas datang!");
        static str[218];
        format(str, sizeof(str), ""RED"EMS %s | telah menerima Emergency Signal di daerah "YELLOW"%s", AccountData[playerid][pName], GetLocation(SignalPos[id][0], SignalPos[id][1], SignalPos[id][2]));
        SendClientMessageToAll(COLOR_RED, str);
        SignalExists[id] = false;
        SignalPos[id][0] = SignalPos[id][1] = SignalPos[id][2] = 0.0;
        pMapCP[playerid] = true;
    }
    else ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah membatalkan pilihan!");
    return 1;
}

Dialog:CALLCENTER_RESTAURANT(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan panggilan restaurant!");
    new Float:X, Float:Y, Float:Z;
    GetPlayerPos(playerid, X, Y, Z);

    if(isnull(inputtext)) return Dialog_Show(playerid, CALLCENTER_RESTAURANT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggil Karyawan Restaurant",
    "Error: Tidak dapat diisi kosong!\nMasukkan pesanan atau kebutuhan anda yang ingin dilaporkan kepada pihak restaurant dibawah ini\
    \nJelaskan detail pesanan atau permintaan agar karyawan restaurant dapat membantu:", "Kirim", "Batal");

    if(IsNumeric(inputtext)) return Dialog_Show(playerid, CALLCENTER_RESTAURANT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Restaurant",
    "Error: Tidak dapat diisi angka!\nMasukkan pesanan atau kebutuhan anda yang ingin dilaporkan kepada pihak restaurant dibawah ini\
    \nJelaskan detail pesanan atau permintaan agar karyawan restaurant dapat membantu:", "Kirim", "Batal");
    
    if(strlen(inputtext) > 128) return Dialog_Show(playerid, CALLCENTER_RESTAURANT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Restaurant",
    "Error: Tidak dapat lebih dari 128 characters!\nMasukkan pesanan atau kebutuhan anda yang ingin dilaporkan kepada pihak restaurant dibawah ini\
    \nJelaskan detail pesanan atau permintaan agar karyawan restaurant dapat membantu:", "Kirim", "Batal");
    
    if(AccountData[playerid][pHotlineTime] >= gettime()){
        ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Mohon menunggu %d detik untuk menghubungi restaurant kembali", AccountData[playerid][pHotlineTime] - gettime()));
        return 1;
    }
    foreach(new i : Player) {
        if(AccountData[i][pFaction] == FACTION_PEDAGANG && AccountData[i][pDutyPedagang]) { // <-- faction restaurant
            SendClientMessageEx(i, -1, ""GRAY"[Panggilan Restaurant] "WHITE"Permintaan Dari %s (%d) // Lokasi: %s // No Telpon: %s", GetRPName(playerid), playerid, GetLocation(X, Y, Z), AccountData[playerid][pPhone]);
            SendClientMessageEx(i, -1, ""WHITE"-> %s", inputtext);
        }
    }
    AccountData[playerid][pHotlineTime] = gettime() + 180;
    SendClientMessageEx(playerid, -1, ""GRAY"[Panggilan Restaurant] "WHITE"Permintaan Restaurant Dikirim // Lokasi: %s // No Telpon: %s", GetLocation(X, Y, Z), AccountData[playerid][pPhone]);
    SendClientMessageEx(playerid, -1, ""WHITE"-> %s", inputtext);
    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengirim panggilan restaurant!");
    return 1;
}

Dialog:CALLCENTER_BENGKEL(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan panggilan bengkel!");
    new Float:X, Float:Y, Float:Z;
    GetPlayerPos(playerid, X, Y, Z);

    if(isnull(inputtext)) return Dialog_Show(playerid, CALLCENTER_BENGKEL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggil Karyawan Bengkel",
    "Error: Tidak dapat diisi kosong!\nMasukkan kendala anda yang ingin dilaporkan kepada pihak bengkel dibawah ini\
    \nJelaskan detail dan kerusakan yang sedang kamu alami agar karyawan bengkel dapat membantu:", "Kirim", "Batal");

    if(IsNumeric(inputtext)) return Dialog_Show(playerid, CALLCENTER_BENGKEL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Bengkel",
    "Error: Tidak dapat diisi angka!\nMasukkan kendala anda yang ingin dilaporkan kepada pihak bengkel dibawah ini\
    \nJelaskan detail dan kerusakan yang sedang kamu alami agar karyawan bengkel dapat membantu:", "Kirim", "Batal");
    
    if(strlen(inputtext) > 128) return Dialog_Show(playerid, CALLCENTER_BENGKEL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Bengkel",
    "Error: Tidak dapat lebih dari 128 characters!\nMasukkan kendala anda yang ingin dilaporkan kepada pihak bengkel dibawah ini\
    \nJelaskan detail dan kerusakan yang sedang kamu alami agar karyawan bengkel dapat membantu:", "Kirim", "Batal");
    
    if(AccountData[playerid][pHotlineTime] >= gettime()){
		ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Mohon menunggu %d detik untuk menghubungi bengkel kembali", AccountData[playerid][pHotlineTime] - gettime()));
		return 1;
	}
	foreach(new i : Player) {
		if(AccountData[i][pFaction] == FACTION_BENGKEL && AccountData[i][pDutyBengkel]) { // <-- faction mekanik
			SendClientMessageEx(i, -1, ""GRAY"[Panggilan Bengkel] "WHITE"Permintaan Dari %s (%d) // Lokasi: %s // No Telpon: %s", GetRPName(playerid), playerid, GetLocation(X, Y, Z), AccountData[playerid][pPhone]);
			SendClientMessageEx(i, -1, ""WHITE"-> %s", inputtext);
		}
	}
	AccountData[playerid][pHotlineTime] = gettime() + 180;
	SendClientMessageEx(playerid, -1, ""GRAY"[Panggilan Bengkel] "WHITE"Permintaan Bengkel Dikirim // Lokasi: %s // No Telpon: %s", GetLocation(X, Y, Z), AccountData[playerid][pPhone]);
	SendClientMessageEx(playerid, -1, ""WHITE"-> %s", inputtext);
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengirim panggilan bengkel!");
    return 1;
}

Dialog:CALLCENTER_POLISI(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    new Float:X, Float:Y, Float:Z;
    GetPlayerPos(playerid, X, Y, Z);

    if(isnull(inputtext)) return Dialog_Show(playerid, CALLCENTER_POLISI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Darurat Polisi",
    "Error: Tidak dapat diisi kosong!\nMasukkan kendala anda yang ingin dilaporkan kepada pihak kepolisian dibawah ini\
    \nJelaskan detail dan kendala yang sedang kamu alami dan ingin lapor ke kepolisian:", "Kirim", "Batal");

    if(IsNumeric(inputtext)) return Dialog_Show(playerid, CALLCENTER_POLISI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Darurat Polisi",
    "Error: Tidak dapat diisi angka!\nMasukkan kendala anda yang ingin dilaporkan kepada pihak kepolisian dibawah ini\
    \nJelaskan detail dan kendala yang sedang kamu alami dan ingin lapor ke kepolisian:", "Kirim", "Batal");
    
    if(strlen(inputtext) > 128) return Dialog_Show(playerid, CALLCENTER_POLISI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Darurat Polisi",
    "Error: Tidak dapat lebih dari 128 characters!\nMasukkan kendala anda yang ingin dilaporkan kepada pihak kepolisian dibawah ini\
    \nJelaskan detail dan kendala yang sedang kamu alami dan ingin lapor ke kepolisian:", "Kirim", "Batal");
    
    if(AccountData[playerid][pHotlineTime] >= gettime()){
		ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Mohon menunggu %d detik untuk mengirim hotline ke factions kembali", AccountData[playerid][pHotlineTime] - gettime()));
		return 1;
	}
	foreach(new i : Player) {
		if(AccountData[i][pFaction] == 1 && AccountData[i][pDutyPD]) {
			SendClientMessageEx(i, -1, ""GRAY"[Pesan Darurat] "WHITE"Laporan Dari %s (%d) // Lokasi: %s // No Telpon: %s", GetRPName(playerid), playerid, GetLocation(X, Y, Z), AccountData[playerid][pPhone]);
			SendClientMessageEx(i, -1, ""WHITE"-> %s", inputtext);
		}
	}
	AccountData[playerid][pHotlineTime] = gettime() + 180;
	SendClientMessageEx(playerid, -1, ""GRAY"[Pesan Darurat] "WHITE"Laporan Dari %s (%d) // Lokasi: %s // No Telpon: %s", GetRPName(playerid), playerid, GetLocation(X, Y, Z), AccountData[playerid][pPhone]);
	SendClientMessageEx(playerid, -1, ""WHITE"-> %s", inputtext);
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengirim pesan darurat kepolisian!");
    return 1;
}

Dialog:CALLCENTER_EMS(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    new Float:X, Float:Y, Float:Z;
    GetPlayerPos(playerid, X, Y, Z);

    if(isnull(inputtext)) return Dialog_Show(playerid, CALLCENTER_EMS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Darurat Rumah Sakit",
    "Error: Tidak dapat diisi kosong!\nMasukkan kendala anda yang ingin dilaporkan kepada pihak Rumah Sakit dibawah ini\
    \nJelaskan detail dan kendala yang sedang kamu alami dan ingin lapor ke Rumah Sakit:", "Kirim", "Batal");

    if(IsNumeric(inputtext)) return Dialog_Show(playerid, CALLCENTER_EMS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Darurat Rumah Sakit",
    "Error: Tidak dapat diisi angka!\nMasukkan kendala anda yang ingin dilaporkan kepada pihak Rumah Sakit dibawah ini\
    \nJelaskan detail dan kendala yang sedang kamu alami dan ingin lapor ke Rumah Sakit:", "Kirim", "Batal");
    
    if(strlen(inputtext) > 128) return Dialog_Show(playerid, CALLCENTER_EMS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Panggilan Darurat Rumah Sakit",
    "Error: Tidak dapat lebih dari 128 characters!\nMasukkan kendala anda yang ingin dilaporkan kepada pihak Rumah Sakit dibawah ini\
    \nJelaskan detail dan kendala yang sedang kamu alami dan ingin lapor ke Rumah Sakit:", "Kirim", "Batal");
    
    if(AccountData[playerid][pHotlineTime] >= gettime())
	{
		ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Mohon menunggu %d detik untuk mengirim hotline factions kembali!", AccountData[playerid][pHotlineTime] - gettime()));
		return 1;
	}

	foreach(new i : Player) {
		if(AccountData[i][pFaction] == 3 && AccountData[i][pDutyEms]) {
			SendClientMessageEx(i, -1, ""C_DOKTER"[EMS CALL CENTER]"WHITE" Laporan Dari %s (%d) // Lokasi: %s // No Telpon: %s", GetRPName(playerid), playerid, GetLocation(X, Y, Z), AccountData[playerid][pPhone]);
			SendClientMessageEx(i, -1, ""WHITE"-> %s", inputtext);
		}
	}
	AccountData[playerid][pHotlineTime] = gettime() + 180;
	SendClientMessageEx(playerid, -1, ""C_DOKTER"[EMS CALL CENTER]"WHITE" Laporan Dari %s (%d) // Lokasi: %s // No Telpon: %s", GetRPName(playerid), playerid, GetLocation(X, Y, Z), AccountData[playerid][pPhone]);
	SendClientMessageEx(playerid, -1, ""WHITE"-> %s", inputtext);
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengirim pesan darurat Rumah Sakit!");
    return 1;
}

Dialog:CALLCENTER_PEMDA(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
    new Float:X, Float:Y, Float:Z;
    GetPlayerPos(playerid, X, Y, Z);

    if(isnull(inputtext)) return Dialog_Show(playerid, CALLCENTER_PEMDA, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Call Center Pemerintah",
    "Error: Tidak dapat diisi kosong!\nMasukkan kendala anda yang ingin dilaporkan kepada pihak Pemerintah dibawah ini\
    \nJelaskan detail dan kendala yang sedang kamu alami dan ingin lapor ke Pemerintah:", "Kirim", "Batal");

    if(IsNumeric(inputtext)) return Dialog_Show(playerid, CALLCENTER_PEMDA, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Call Center Pemerintah",
    "Error: Tidak dapat diisi angka!\nMasukkan kendala anda yang ingin dilaporkan kepada pihak Pemerintah dibawah ini\
    \nJelaskan detail dan kendala yang sedang kamu alami dan ingin lapor ke Pemerintah:", "Kirim", "Batal");
    
    if(strlen(inputtext) > 128) return Dialog_Show(playerid, CALLCENTER_PEMDA, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Call Center Pemerintah",
    "Error: Tidak dapat lebih dari 128 characters!\nMasukkan kendala anda yang ingin dilaporkan kepada pihak Pemerintah dibawah ini\
    \nJelaskan detail dan kendala yang sedang kamu alami dan ingin lapor ke Pemerintah:", "Kirim", "Batal");
    
    if(AccountData[playerid][pHotlineTime] >= gettime())
	{
		ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Mohon menunggu %d detik untuk mengirim hotline factions kembali!", AccountData[playerid][pHotlineTime] - gettime()));
		return 1;
	}

	foreach(new i : Player) {
		if(AccountData[i][pFaction] == FACTION_PEMERINTAH && AccountData[i][pDutyPemerintah]) {
			SendClientMessageEx(i, -1, ""SKYBLUE"[PEMDA CALL CENTER]"WHITE" Laporan Dari %s (%d) // Lokasi: %s // No Telpon: %s", GetRPName(playerid), playerid, GetLocation(X, Y, Z), AccountData[playerid][pPhone]);
			SendClientMessageEx(i, -1, ""WHITE"-> %s", inputtext);
		}
	}
	AccountData[playerid][pHotlineTime] = gettime() + 180;
	SendClientMessageEx(playerid, -1, ""SKYBLUE"[PEMDA CALL CENTER]"WHITE" Laporan Dari %s (%d) // Lokasi: %s // No Telpon: %s", GetRPName(playerid), playerid, GetLocation(X, Y, Z), AccountData[playerid][pPhone]);
	SendClientMessageEx(playerid, -1, ""WHITE"-> %s", inputtext);
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengirim pesan ke Call Center Pemerintah!");
    return 1;
}

// ------------------------------------------------------------------------------- //
ptask CallTimer_Update[1000](playerid)
{
    if(AccountData[playerid][phoneDurringConversation] && AccountData[playerid][phoneCallingWithPlayerID] != INVALID_PLAYER_ID)
    {
        new times[3];
        GetElapsedTime(AccountData[playerid][phoneCallingTime]++, times[0], times[1], times[2]);
        PlayerTextDrawSetString(playerid, StatusDialingTD[playerid], sprintf("%02d:%02d:%02d", times[0], times[1], times[2]));
        PlayerTextDrawShow(playerid, StatusDialingTD[playerid]);
        if(!AccountData[playerid][phoneShown]){
            PlayerTextDrawHide(playerid, StatusDialingTD[playerid]);
        }
    }
    return 1;
}

ptask SharelocRemove[1000](playerid)
{
    if(SharelocTimer[playerid] > 0)
    {
        SharelocTimer[playerid] --;
        if(!SharelocTimer[playerid])
        {
            if(SharelocSender[playerid] != INVALID_STREAMER_ID)
                DestroyDynamicMapIcon(SharelocSender[playerid]), SharelocSender[playerid] = INVALID_STREAMER_ID;
            
            SharelocTimer[playerid] = 0;
        }
    }
    return 1;
}

ptask PhoneClockTD[1000](playerid)
{
    if(AccountData[playerid][phoneShown])
    {
        static const MonthName[12][] =
        {
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
        };

        new timestring[16], str[64];
        new hours, minutes, seconds;
        new year, month, day;
        
        getdate(year, month, day);
        gettime(hours, minutes, seconds);

        hours += 7;
        if(hours >= 24) hours -= 24;

        format(timestring, sizeof timestring, "%02d:%02d", hours, minutes);
        format(str, sizeof(str), "%d %s %d", day, MonthName[month-1], year);

        PlayerTextDrawSetString(playerid, ATRP_Phone[playerid][15], timestring);
        PlayerTextDrawSetString(playerid, ATRP_Phone[playerid][17], timestring);
        PlayerTextDrawSetString(playerid, ATRP_Phone[playerid][16], str);
        PlayerTextDrawSetString(playerid, ATRP_TwitterNotif[playerid][25], timestring);
        PlayerTextDrawSetString(playerid, ATRP_BankTD[playerid][15], timestring);
        PlayerTextDrawSetString(playerid, ATRP_SpotifyTD[playerid][15], timestring);
        PlayerTextDrawSetString(playerid, ATRP_HomeSpotify[playerid][15], timestring);
    }
    return 1;
}

// DialogPages:ContactListDialog(playerid, response, listitem, inputtext[])
// {
//     if(response)
//     {
//         if(listitem == INVALID_LISTITEM) return 0;

//         new index =  ListedContacts[playerid][listitem];

//         AccountData[playerid][pContact] = index;

//         ShowPlayerDialog(playerid, DialogContactMenu, DIALOG_STYLE_LIST, sprintf(""TCRP"District "WHITE" - %s", ContactData[playerid][AccountData[playerid][pContact]][contactName]),
//         "Panggil\
//         \n"GRAY"Whatsapp\
//         \nShareloc\
//         \n"GRAY"Edit Nama Kontak\
//         \nEdit Nomor Kontak\
//         \n"GRAY"Blokir/Buka Blokir Kontak\
//         \nHapus Kontak", "Pilih", "Batal");
//     }
//     else
//     {
//         ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
//     }

//     for(new i = 0; i < MAX_CONTACTS; i++) {
//         ListedContacts[playerid][i] = -1;
//     }
//     return 1;
// }


forward HidePostTwitter(playerid);
public HidePostTwitter(playerid)
{
    for (new i = 0; i < 38; i++)
    {
        PlayerTextDrawHide(playerid, ATRP_TwitterNotif[playerid][i]);
    }
    ShowHbeTextdraws(playerid, AccountData[playerid][pHUDMode]);
    return 1;
}

ShowPlayerTwitterPageV1(playerid, page = 0)
{
    if (page < 0) page = 0;
    new offset = page * MAX_TWEETS_PER_PAGE;
    new query[256];

    format(query, sizeof(query), "SELECT * FROM tweets WHERE ID=1 ORDER BY TwitterDate ASC LIMIT %d OFFSET %d", MAX_TWEETS_PER_PAGE, offset);
    mysql_tquery(g_SQL, query, "OnTwitterPageLoad", "ii", playerid, page);
    return 1;
}

forward OnTwitterPageLoad(playerid, page);
public OnTwitterPageLoad(playerid, page)
{
    new rows = cache_num_rows();

    for(new x = 0; x < 28; x++)
    {
        PlayerTextDrawShow(playerid, ATRP_TwitterHomepageTD[playerid][x]);
    }

    for(new i = 0; i < 5; i++)
    {
        PlayerTextDrawHide(playerid, ATRP_TwitterHomepageTD[playerid][28 + i]); // box
        PlayerTextDrawHide(playerid, ATRP_TwitterHomepageTD[playerid][33 + i]); // from
        PlayerTextDrawHide(playerid, ATRP_TwitterHomepageTD[playerid][38 + i]); // date
        PlayerTextDrawHide(playerid, ATRP_TwitterHomepageTD[playerid][43 + i]); // text line 1
        PlayerTextDrawHide(playerid, ATRP_TwitterHomepageTD[playerid][53 + i]); // text line 2
    }

    if(rows == 0)
    {
        return 1;
    }

    new tempTweetFrom[24], tempTweetDate[64], tempTweetText[128];

    for(new i = 0; i < rows && i < 5; i++)
    {
        cache_get_value_name(i, "TwitterFrom", tempTweetFrom);
        cache_get_value_name(i, "TwitterDate", tempTweetDate);
        cache_get_value_name(i, "TwitterText", tempTweetText);

        PlayerTextDrawSetString(playerid, ATRP_TwitterHomepageTD[playerid][33 + i], tempTweetFrom);
        PlayerTextDrawSetString(playerid, ATRP_TwitterHomepageTD[playerid][38 + i], tempTweetDate);

        PlayerTextDrawShow(playerid, ATRP_TwitterHomepageTD[playerid][28 + i]); // box
        PlayerTextDrawShow(playerid, ATRP_TwitterHomepageTD[playerid][33 + i]); // from
        PlayerTextDrawShow(playerid, ATRP_TwitterHomepageTD[playerid][38 + i]); // date

        if(strlen(tempTweetText) > 20)
        {
            new firstPart[64], secondPart[64];
            strmid(firstPart, tempTweetText, 0, 20, sizeof(firstPart));
            strmid(secondPart, tempTweetText, 20, strlen(tempTweetText), sizeof(secondPart));

            PlayerTextDrawSetString(playerid, ATRP_TwitterHomepageTD[playerid][43 + i], firstPart);
            PlayerTextDrawSetString(playerid, ATRP_TwitterHomepageTD[playerid][53 + i], secondPart);

            PlayerTextDrawShow(playerid, ATRP_TwitterHomepageTD[playerid][43 + i]);
            PlayerTextDrawShow(playerid, ATRP_TwitterHomepageTD[playerid][53 + i]);
        }
        else
        {
            PlayerTextDrawSetString(playerid, ATRP_TwitterHomepageTD[playerid][43 + i], tempTweetText);
            PlayerTextDrawShow(playerid, ATRP_TwitterHomepageTD[playerid][43 + i]);
            PlayerTextDrawHide(playerid, ATRP_TwitterHomepageTD[playerid][53 + i]);
        }
    }

    new pageString[32];
    format(pageString, sizeof(pageString), "%d/%d", page + 1, ((rows < MAX_TWEETS_PER_PAGE && page == 0) ? 1 : page + 2));
    PlayerTextDrawSetString(playerid, ATRP_TwitterHomepageTD[playerid][52], pageString);
    PlayerTextDrawShow(playerid, ATRP_TwitterHomepageTD[playerid][52]);

    PlayerTextDrawShow(playerid, ATRP_TwitterHomepageTD[playerid][48]); // Next
    PlayerTextDrawShow(playerid, ATRP_TwitterHomepageTD[playerid][49]); // Prev

    pTwitterPage[playerid] = page;
    return 1;
}

Spotify_LoadHistory(playerid)
{
    SpotifyCount[playerid] = 0;
    new query[256];
    format(query, sizeof(query), "SELECT url, title FROM spotify_history WHERE player_id = %d ORDER BY added_at DESC LIMIT %d", AccountData[playerid][pID], MAX_SPOTIFY_HISTORY);
    mysql_tquery(g_SQL, query, "Spotify_OnLoadHistory", "d", playerid);
}

forward Spotify_OnLoadHistory(playerid);
public Spotify_OnLoadHistory(playerid)
{
    new rows = cache_num_rows();

    for(new x = 0; x < 26; x++)
    {
        PlayerTextDrawShow(playerid, ATRP_SpotifyTD[playerid][x]);
    }

    for(new x = 52; x < 57; x++)
    {
        PlayerTextDrawShow(playerid, ATRP_SpotifyTD[playerid][x]);
    }

    for(new i = 0; i < MAX_SPOTIFY_HISTORY; i++) 
    {
        PlayerTextDrawHide(playerid, ATRP_SpotifyTD[playerid][26]);
        PlayerTextDrawHide(playerid, ATRP_SpotifyTD[playerid][27 + i]); //box
        PlayerTextDrawHide(playerid, ATRP_SpotifyTD[playerid][33 + i]); //logo spotify
        PlayerTextDrawHide(playerid, ATRP_SpotifyTD[playerid][39 + i]); //title
        PlayerTextDrawHide(playerid, ATRP_SpotifyTD[playerid][45 + i]); //titik :
    }

    if(rows == 0)
    {
        return 1;
    }

    for(new i = 0; i < rows && i < MAX_SPOTIFY_HISTORY; i++)
    {
        cache_get_value_name(i, "url", SpotifyHistory[playerid][i], 256);
        cache_get_value_name(i, "title", SpotifyTitle[playerid][i], 128);
        SpotifyCount[playerid]++;

        PlayerTextDrawSetString(playerid, ATRP_SpotifyTD[playerid][39 + i], SpotifyTitle[playerid][i]);

        PlayerTextDrawShow(playerid, ATRP_SpotifyTD[playerid][26]);
        PlayerTextDrawShow(playerid, ATRP_SpotifyTD[playerid][27 + i]); //box
        PlayerTextDrawShow(playerid, ATRP_SpotifyTD[playerid][33 + i]); //logo spotify
        PlayerTextDrawShow(playerid, ATRP_SpotifyTD[playerid][39 + i]); //title
        PlayerTextDrawShow(playerid, ATRP_SpotifyTD[playerid][45 + i]); //titik :
    }
    return 1;
}

Spotify_ClearOldHistory(playerid)
{
    new query[512];
    format(query, sizeof(query),
        "DELETE FROM spotify_history WHERE id = ( \
            SELECT id FROM ( \
                SELECT id FROM spotify_history \
                WHERE player_id = %d \
                ORDER BY added_at ASC \
                LIMIT 1 OFFSET %d \
            ) AS temp \
        )",
        AccountData[playerid][pID],
        MAX_SPOTIFY_HISTORY
    );
    mysql_tquery(g_SQL, query);
}