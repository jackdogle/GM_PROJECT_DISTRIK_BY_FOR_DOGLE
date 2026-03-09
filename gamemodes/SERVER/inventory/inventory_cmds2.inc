#include <YSI\y_hooks>

new PlayerText: InventoryTD[MAX_PLAYERS][38];
new PlayerText: ExistsInv[MAX_PLAYERS][MAX_INVENTORY];
new PlayerText: NameInv[MAX_PLAYERS][MAX_INVENTORY];
new PlayerText: PrevMod[MAX_PLAYERS][MAX_INVENTORY];
new PlayerText: QuantityInv[MAX_PLAYERS][MAX_INVENTORY];

CreateInventoryTextdraw(playerid)
{
    InventoryTD[playerid][0] = CreatePlayerTextDraw(playerid, 121.000, 96.000, "Cecep_Sugeni");
    PlayerTextDrawLetterSize(playerid, InventoryTD[playerid][0], 0.190, 1.099);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][0], 150);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][0], 1);

    InventoryTD[playerid][1] = CreatePlayerTextDraw(playerid, 122.000, 108.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][1], 234.000, 5.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][1], 150);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][1], 1);

    InventoryTD[playerid][2] = CreatePlayerTextDraw(playerid, 122.000, 108.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][2], 234.000, 5.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][2], -6710785);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][2], 1);

    InventoryTD[playerid][3] = CreatePlayerTextDraw(playerid, 326.000, 96.000, "0,150/50");
    PlayerTextDrawLetterSize(playerid, InventoryTD[playerid][3], 0.190, 1.099);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][3], 150);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][3], 1);

    InventoryTD[playerid][4] = CreatePlayerTextDraw(playerid, 122.000, 116.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][4], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][4], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][4], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][4], 1);

    InventoryTD[playerid][5] = CreatePlayerTextDraw(playerid, 169.000, 116.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][5], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][5], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][5], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][5], 1);

    InventoryTD[playerid][6] = CreatePlayerTextDraw(playerid, 216.000, 116.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][6], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][6], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][6], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][6], 1);

    InventoryTD[playerid][7] = CreatePlayerTextDraw(playerid, 263.000, 116.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][7], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][7], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][7], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][7], 1);

    InventoryTD[playerid][8] = CreatePlayerTextDraw(playerid, 310.000, 116.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][8], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][8], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][8], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][8], 1);

    InventoryTD[playerid][9] = CreatePlayerTextDraw(playerid, 122.000, 175.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][9], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][9], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][9], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][9], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][9], 1);

    InventoryTD[playerid][10] = CreatePlayerTextDraw(playerid, 169.000, 175.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][10], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][10], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][10], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][10], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][10], 1);

    InventoryTD[playerid][11] = CreatePlayerTextDraw(playerid, 216.000, 175.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][11], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][11], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][11], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][11], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][11], 1);

    InventoryTD[playerid][12] = CreatePlayerTextDraw(playerid, 263.000, 175.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][12], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][12], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][12], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][12], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][12], 1);

    InventoryTD[playerid][13] = CreatePlayerTextDraw(playerid, 310.000, 175.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][13], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][13], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][13], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][13], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][13], 1);

    InventoryTD[playerid][14] = CreatePlayerTextDraw(playerid, 122.000, 234.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][14], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][14], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][14], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][14], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][14], 1);

    InventoryTD[playerid][15] = CreatePlayerTextDraw(playerid, 169.000, 234.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][15], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][15], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][15], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][15], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][15], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][15], 1);

    InventoryTD[playerid][16] = CreatePlayerTextDraw(playerid, 216.000, 234.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][16], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][16], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][16], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][16], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][16], 1);

    InventoryTD[playerid][17] = CreatePlayerTextDraw(playerid, 263.000, 234.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][17], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][17], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][17], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][17], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][17], 1);

    InventoryTD[playerid][18] = CreatePlayerTextDraw(playerid, 310.000, 234.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][18], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][18], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][18], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][18], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][18], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][18], 1);

    InventoryTD[playerid][19] = CreatePlayerTextDraw(playerid, 122.000, 294.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][19], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][19], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][19], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][19], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][19], 1);

    InventoryTD[playerid][20] = CreatePlayerTextDraw(playerid, 169.000, 294.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][20], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][20], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][20], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][20], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][20], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][20], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][20], 1);

    InventoryTD[playerid][21] = CreatePlayerTextDraw(playerid, 216.000, 294.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][21], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][21], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][21], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][21], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][21], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][21], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][21], 1);

    InventoryTD[playerid][22] = CreatePlayerTextDraw(playerid, 263.000, 294.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][22], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][22], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][22], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][22], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][22], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][22], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][22], 1);

    InventoryTD[playerid][23] = CreatePlayerTextDraw(playerid, 310.000, 294.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][23], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][23], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][23], 180);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][23], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][23], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][23], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][23], 1);

    InventoryTD[playerid][24] = CreatePlayerTextDraw(playerid, 375.000, 163.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][24], 73.000, 27.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][24], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][24], 150);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][24], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][24], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][24], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][24], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][24], 1);

    InventoryTD[playerid][25] = CreatePlayerTextDraw(playerid, 375.000, 192.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][25], 73.000, 27.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][25], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][25], 150);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][25], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][25], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][25], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][25], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][25], 1);

    InventoryTD[playerid][26] = CreatePlayerTextDraw(playerid, 375.000, 221.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][26], 73.000, 27.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][26], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][26], 150);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][26], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][26], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][26], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][26], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][26], 1);

    InventoryTD[playerid][27] = CreatePlayerTextDraw(playerid, 375.000, 250.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][27], 73.000, 27.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][27], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][27], 150);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][27], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][27], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][27], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][27], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][27], 1);

    InventoryTD[playerid][28] = CreatePlayerTextDraw(playerid, 375.000, 150.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][28], 73.000, 11.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][28], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][28], -6710785);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][28], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][28], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][28], 255);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][28], 4);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][28], 1);

    InventoryTD[playerid][29] = CreatePlayerTextDraw(playerid, 396.000, 150.000, "District");
    PlayerTextDrawLetterSize(playerid, InventoryTD[playerid][29], 0.190, 1.099);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][29], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][29], -1);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][29], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][29], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][29], 150);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][29], 1);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][29], 1);

    InventoryTD[playerid][30] = CreatePlayerTextDraw(playerid, 426.000, 148.000, "/");
    PlayerTextDrawLetterSize(playerid, InventoryTD[playerid][30], 0.190, 1.399);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][30], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][30], 255);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][30], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][30], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][30], 150);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][30], 1);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][30], 1);

    InventoryTD[playerid][31] = CreatePlayerTextDraw(playerid, 427.000, 148.000, "/");
    PlayerTextDrawLetterSize(playerid, InventoryTD[playerid][31], 0.190, 1.399);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][31], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][31], -1);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][31], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][31], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][31], 150);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][31], 1);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][31], 1);

    InventoryTD[playerid][32] = CreatePlayerTextDraw(playerid, 428.000, 148.000, "/");
    PlayerTextDrawLetterSize(playerid, InventoryTD[playerid][32], 0.190, 1.399);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][32], 1);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][32], 255);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][32], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][32], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][32], 150);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][32], 1);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][32], 1);

    InventoryTD[playerid][33] = CreatePlayerTextDraw(playerid, 412.000, 169.000, "Ammount");
    PlayerTextDrawLetterSize(playerid, InventoryTD[playerid][33], 0.260, 1.500);
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][33], 15.000, 72.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][33], 2);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][33], -1);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][33], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][33], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][33], 150);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][33], 1);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][33], 1);
    PlayerTextDrawSetSelectable(playerid, InventoryTD[playerid][33], 1);

    InventoryTD[playerid][34] = CreatePlayerTextDraw(playerid, 412.000, 197.000, "Use");
    PlayerTextDrawLetterSize(playerid, InventoryTD[playerid][34], 0.260, 1.500);
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][34], 15.000, 72.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][34], 2);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][34], -1);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][34], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][34], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][34], 150);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][34], 1);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][34], 1);
    PlayerTextDrawSetSelectable(playerid, InventoryTD[playerid][34], 1);

    InventoryTD[playerid][35] = CreatePlayerTextDraw(playerid, 412.000, 226.000, "Give");
    PlayerTextDrawLetterSize(playerid, InventoryTD[playerid][35], 0.260, 1.500);
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][35], 15.000, 72.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][35], 2);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][35], -1);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][35], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][35], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][35], 150);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][35], 1);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][35], 1);
    PlayerTextDrawSetSelectable(playerid, InventoryTD[playerid][35], 1);

    InventoryTD[playerid][36] = CreatePlayerTextDraw(playerid, 412.000, 256.000, "Drop");
    PlayerTextDrawLetterSize(playerid, InventoryTD[playerid][36], 0.260, 1.500);
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][36], 15.000, 72.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][36], 2);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][36], -1);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][36], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][36], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][36], 150);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][36], 1);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][36], 1);
    PlayerTextDrawSetSelectable(playerid, InventoryTD[playerid][36], 1);

    InventoryTD[playerid][37] = CreatePlayerTextDraw(playerid, 412.000, 284.000, "Close");
    PlayerTextDrawLetterSize(playerid, InventoryTD[playerid][37], 0.260, 1.500);
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][37], 15.000, 72.000);
    PlayerTextDrawAlignment(playerid, InventoryTD[playerid][37], 2);
    PlayerTextDrawColor(playerid, InventoryTD[playerid][37], -1);
    PlayerTextDrawSetShadow(playerid, InventoryTD[playerid][37], 0);
    PlayerTextDrawSetOutline(playerid, InventoryTD[playerid][37], 0);
    PlayerTextDrawBackgroundColor(playerid, InventoryTD[playerid][37], 150);
    PlayerTextDrawFont(playerid, InventoryTD[playerid][37], 1);
    PlayerTextDrawSetProportional(playerid, InventoryTD[playerid][37], 1);
    PlayerTextDrawSetSelectable(playerid, InventoryTD[playerid][37], 1);

    ExistsInv[playerid][0] = CreatePlayerTextDraw(playerid, 122.000, 168.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][0], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][0], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][0], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][0], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][0], 1);

    ExistsInv[playerid][1] = CreatePlayerTextDraw(playerid, 169.000, 168.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][1], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][1], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][1], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][1], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][1], 1);

    ExistsInv[playerid][2] = CreatePlayerTextDraw(playerid, 216.000, 168.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][2], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][2], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][2], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][2], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][2], 1);

    ExistsInv[playerid][3] = CreatePlayerTextDraw(playerid, 263.000, 168.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][3], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][3], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][3], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][3], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][3], 1);

    ExistsInv[playerid][4] = CreatePlayerTextDraw(playerid, 310.000, 168.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][4], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][4], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][4], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][4], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][4], 1);

    ExistsInv[playerid][5] = CreatePlayerTextDraw(playerid, 122.000, 227.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][5], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][5], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][5], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][5], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][5], 1);

    ExistsInv[playerid][6] = CreatePlayerTextDraw(playerid, 169.000, 227.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][6], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][6], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][6], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][6], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][6], 1);

    ExistsInv[playerid][7] = CreatePlayerTextDraw(playerid, 216.000, 227.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][7], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][7], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][7], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][7], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][7], 1);

    ExistsInv[playerid][8] = CreatePlayerTextDraw(playerid, 263.000, 227.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][8], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][8], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][8], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][8], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][8], 1);

    ExistsInv[playerid][9] = CreatePlayerTextDraw(playerid, 310.000, 227.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][9], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][9], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][9], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][9], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][9], 1);

    ExistsInv[playerid][10] = CreatePlayerTextDraw(playerid, 122.000, 286.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][10], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][10], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][10], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][10], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][10], 1);

    ExistsInv[playerid][11] = CreatePlayerTextDraw(playerid, 169.000, 286.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][11], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][11], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][11], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][11], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][11], 1);

    ExistsInv[playerid][12] = CreatePlayerTextDraw(playerid, 216.000, 286.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][12], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][12], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][12], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][12], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][12], 1);

    ExistsInv[playerid][13] = CreatePlayerTextDraw(playerid, 263.000, 286.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][13], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][13], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][13], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][13], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][13], 1);

    ExistsInv[playerid][14] = CreatePlayerTextDraw(playerid, 310.000, 286.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][14], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][14], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][14], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][14], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][14], 1);

    ExistsInv[playerid][15] = CreatePlayerTextDraw(playerid, 122.000, 346.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][15], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][15], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][15], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][15], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][15], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][15], 1);

    ExistsInv[playerid][16] = CreatePlayerTextDraw(playerid, 169.000, 346.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][16], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][16], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][16], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][16], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][16], 1);

    ExistsInv[playerid][17] = CreatePlayerTextDraw(playerid, 216.000, 346.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][17], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][17], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][17], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][17], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][17], 1);

    ExistsInv[playerid][18] = CreatePlayerTextDraw(playerid, 263.000, 346.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][18], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][18], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][18], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][18], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][18], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][18], 1);

    ExistsInv[playerid][19] = CreatePlayerTextDraw(playerid, 310.000, 346.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ExistsInv[playerid][19], 45.000, 3.000);
    PlayerTextDrawAlignment(playerid, ExistsInv[playerid][19], 1);
    PlayerTextDrawColor(playerid, ExistsInv[playerid][19], -6710785);
    PlayerTextDrawSetShadow(playerid, ExistsInv[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, ExistsInv[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, ExistsInv[playerid][19], 255);
    PlayerTextDrawFont(playerid, ExistsInv[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, ExistsInv[playerid][19], 1);

    NameInv[playerid][0] = CreatePlayerTextDraw(playerid, 124.000, 117.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][0], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][0], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][0], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][0], 1);

    NameInv[playerid][1] = CreatePlayerTextDraw(playerid, 171.000, 117.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][1], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][1], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][1], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][1], 1);

    NameInv[playerid][2] = CreatePlayerTextDraw(playerid, 218.000, 117.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][2], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][2], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][2], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][2], 1);

    NameInv[playerid][3] = CreatePlayerTextDraw(playerid, 265.000, 117.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][3], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][3], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][3], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][3], 1);

    NameInv[playerid][4] = CreatePlayerTextDraw(playerid, 312.000, 117.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][4], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][4], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][4], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][4], 1);

    NameInv[playerid][5] = CreatePlayerTextDraw(playerid, 124.000, 177.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][5], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][5], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][5], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][5], 1);

    NameInv[playerid][6] = CreatePlayerTextDraw(playerid, 171.000, 177.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][6], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][6], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][6], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][6], 1);

    NameInv[playerid][7] = CreatePlayerTextDraw(playerid, 218.000, 177.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][7], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][7], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][7], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][7], 1);

    NameInv[playerid][8] = CreatePlayerTextDraw(playerid, 265.000, 177.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][8], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][8], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][8], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][8], 1);

    NameInv[playerid][9] = CreatePlayerTextDraw(playerid, 312.000, 177.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][9], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][9], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][9], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][9], 1);

    NameInv[playerid][10] = CreatePlayerTextDraw(playerid, 124.000, 236.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][10], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][10], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][10], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][10], 1);

    NameInv[playerid][11] = CreatePlayerTextDraw(playerid, 171.000, 236.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][11], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][11], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][11], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][11], 1);

    NameInv[playerid][12] = CreatePlayerTextDraw(playerid, 218.000, 236.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][12], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][12], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][12], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][12], 1);

    NameInv[playerid][13] = CreatePlayerTextDraw(playerid, 265.000, 236.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][13], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][13], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][13], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][13], 1);

    NameInv[playerid][14] = CreatePlayerTextDraw(playerid, 312.000, 236.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][14], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][14], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][14], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][14], 1);

    NameInv[playerid][15] = CreatePlayerTextDraw(playerid, 124.000, 295.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][15], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][15], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][15], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][15], 1);

    NameInv[playerid][16] = CreatePlayerTextDraw(playerid, 171.000, 295.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][16], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][16], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][16], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][16], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][16], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][16], 1);

    NameInv[playerid][17] = CreatePlayerTextDraw(playerid, 218.000, 295.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][17], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][17], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][17], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][17], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][17], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][17], 1);

    NameInv[playerid][18] = CreatePlayerTextDraw(playerid, 265.000, 295.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][18], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][18], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][18], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][18], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][18], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][18], 1);

    NameInv[playerid][19] = CreatePlayerTextDraw(playerid, 312.000, 295.000, "Nasi Goreng");
    PlayerTextDrawLetterSize(playerid, NameInv[playerid][19], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, NameInv[playerid][19], 1);
    PlayerTextDrawColor(playerid, NameInv[playerid][19], -1);
    PlayerTextDrawSetShadow(playerid, NameInv[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, NameInv[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, NameInv[playerid][19], 150);
    PlayerTextDrawFont(playerid, NameInv[playerid][19], 1);
    PlayerTextDrawSetProportional(playerid, NameInv[playerid][19], 1);

    PrevMod[playerid][0] = CreatePlayerTextDraw(playerid, 122.000, 116.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][0], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][0], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][0], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][0], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][0], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][0], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][0], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][0], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][0], 1);

    PrevMod[playerid][1] = CreatePlayerTextDraw(playerid, 169.000, 116.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][1], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][1], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][1], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][1], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][1], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][1], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][1], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][1], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][1], 1);

    PrevMod[playerid][2] = CreatePlayerTextDraw(playerid, 216.000, 116.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][2], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][2], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][2], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][2], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][2], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][2], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][2], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][2], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][2], 1);

    PrevMod[playerid][3] = CreatePlayerTextDraw(playerid, 263.000, 116.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][3], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][3], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][3], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][3], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][3], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][3], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][3], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][3], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][3], 1);

    PrevMod[playerid][4] = CreatePlayerTextDraw(playerid, 310.000, 116.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][4], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][4], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][4], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][4], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][4], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][4], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][4], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][4], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][4], 1);

    PrevMod[playerid][5] = CreatePlayerTextDraw(playerid, 122.000, 175.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][5], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][5], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][5], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][5], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][5], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][5], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][5], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][5], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][5], 1);

    PrevMod[playerid][6] = CreatePlayerTextDraw(playerid, 169.000, 175.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][6], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][6], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][6], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][6], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][6], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][6], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][6], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][6], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][6], 1);

    PrevMod[playerid][7] = CreatePlayerTextDraw(playerid, 216.000, 175.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][7], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][7], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][7], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][7], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][7], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][7], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][7], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][7], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][7], 1);

    PrevMod[playerid][8] = CreatePlayerTextDraw(playerid, 263.000, 175.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][8], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][8], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][8], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][8], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][8], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][8], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][8], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][8], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][8], 1);

    PrevMod[playerid][9] = CreatePlayerTextDraw(playerid, 310.000, 175.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][9], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][9], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][9], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][9], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][9], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][9], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][9], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][9], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][9], 1);

    PrevMod[playerid][10] = CreatePlayerTextDraw(playerid, 122.000, 234.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][10], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][10], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][10], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][10], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][10], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][10], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][10], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][10], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][10], 1);

    PrevMod[playerid][11] = CreatePlayerTextDraw(playerid, 169.000, 234.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][11], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][11], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][11], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][11], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][11], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][11], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][11], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][11], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][11], 1);

    PrevMod[playerid][12] = CreatePlayerTextDraw(playerid, 216.000, 234.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][12], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][12], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][12], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][12], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][12], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][12], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][12], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][12], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][12], 1);

    PrevMod[playerid][13] = CreatePlayerTextDraw(playerid, 263.000, 234.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][13], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][13], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][13], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][13], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][13], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][13], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][13], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][13], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][13], 1);

    PrevMod[playerid][14] = CreatePlayerTextDraw(playerid, 310.000, 234.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][14], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][14], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][14], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][14], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][14], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][14], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][14], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][14], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][14], 1);

    PrevMod[playerid][15] = CreatePlayerTextDraw(playerid, 122.000, 294.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][15], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][15], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][15], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][15], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][15], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][15], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][15], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][15], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][15], 1);

    PrevMod[playerid][16] = CreatePlayerTextDraw(playerid, 169.000, 294.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][16], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][16], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][16], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][16], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][16], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][16], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][16], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][16], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][16], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][16], 1);

    PrevMod[playerid][17] = CreatePlayerTextDraw(playerid, 216.000, 294.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][17], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][17], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][17], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][17], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][17], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][17], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][17], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][17], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][17], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][17], 1);

    PrevMod[playerid][18] = CreatePlayerTextDraw(playerid, 263.000, 294.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][18], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][18], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][18], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][18], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][18], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][18], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][18], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][18], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][18], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][18], 1);

    PrevMod[playerid][19] = CreatePlayerTextDraw(playerid, 310.000, 294.000, "_");
    PlayerTextDrawTextSize(playerid, PrevMod[playerid][19], 45.000, 55.000);
    PlayerTextDrawAlignment(playerid, PrevMod[playerid][19], 1);
    PlayerTextDrawColor(playerid, PrevMod[playerid][19], -1);
    PlayerTextDrawSetShadow(playerid, PrevMod[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, PrevMod[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][19], 0);
    PlayerTextDrawFont(playerid, PrevMod[playerid][19], 5);
    PlayerTextDrawSetProportional(playerid, PrevMod[playerid][19], 0);
    PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][19], 2355);
    PlayerTextDrawSetPreviewRot(playerid, PrevMod[playerid][19], -12.000, 0.000, 0.000, 1.300);
    PlayerTextDrawSetPreviewVehCol(playerid, PrevMod[playerid][19], 0, 0);
    PlayerTextDrawSetSelectable(playerid, PrevMod[playerid][19], 1);

    QuantityInv[playerid][0] = CreatePlayerTextDraw(playerid, 124.000, 158.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][0], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][0], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][0], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][0], 1);

    QuantityInv[playerid][1] = CreatePlayerTextDraw(playerid, 171.000, 158.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][1], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][1], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][1], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][1], 1);

    QuantityInv[playerid][2] = CreatePlayerTextDraw(playerid, 218.000, 158.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][2], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][2], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][2], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][2], 1);

    QuantityInv[playerid][3] = CreatePlayerTextDraw(playerid, 265.000, 158.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][3], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][3], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][3], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][3], 1);

    QuantityInv[playerid][4] = CreatePlayerTextDraw(playerid, 312.000, 158.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][4], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][4], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][4], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][4], 1);

    QuantityInv[playerid][5] = CreatePlayerTextDraw(playerid, 124.000, 217.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][5], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][5], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][5], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][5], 1);

    QuantityInv[playerid][6] = CreatePlayerTextDraw(playerid, 171.000, 217.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][6], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][6], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][6], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][6], 1);

    QuantityInv[playerid][7] = CreatePlayerTextDraw(playerid, 218.000, 217.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][7], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][7], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][7], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][7], 1);

    QuantityInv[playerid][8] = CreatePlayerTextDraw(playerid, 265.000, 217.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][8], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][8], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][8], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][8], 1);

    QuantityInv[playerid][9] = CreatePlayerTextDraw(playerid, 312.000, 217.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][9], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][9], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][9], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][9], 1);

    QuantityInv[playerid][10] = CreatePlayerTextDraw(playerid, 124.000, 276.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][10], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][10], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][10], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][10], 1);

    QuantityInv[playerid][11] = CreatePlayerTextDraw(playerid, 171.000, 276.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][11], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][11], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][11], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][11], 1);

    QuantityInv[playerid][12] = CreatePlayerTextDraw(playerid, 218.000, 276.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][12], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][12], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][12], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][12], 1);

    QuantityInv[playerid][13] = CreatePlayerTextDraw(playerid, 265.000, 276.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][13], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][13], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][13], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][13], 1);

    QuantityInv[playerid][14] = CreatePlayerTextDraw(playerid, 312.000, 276.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][14], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][14], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][14], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][14], 1);

    QuantityInv[playerid][15] = CreatePlayerTextDraw(playerid, 124.000, 337.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][15], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][15], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][15], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][15], 1);

    QuantityInv[playerid][16] = CreatePlayerTextDraw(playerid, 171.000, 337.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][16], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][16], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][16], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][16], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][16], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][16], 1);

    QuantityInv[playerid][17] = CreatePlayerTextDraw(playerid, 218.000, 337.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][17], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][17], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][17], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][17], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][17], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][17], 1);

    QuantityInv[playerid][18] = CreatePlayerTextDraw(playerid, 265.000, 337.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][18], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][18], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][18], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][18], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][18], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][18], 1);

    QuantityInv[playerid][19] = CreatePlayerTextDraw(playerid, 312.000, 337.000, "100x");
    PlayerTextDrawLetterSize(playerid, QuantityInv[playerid][19], 0.140, 0.899);
    PlayerTextDrawAlignment(playerid, QuantityInv[playerid][19], 1);
    PlayerTextDrawColor(playerid, QuantityInv[playerid][19], -1);
    PlayerTextDrawSetShadow(playerid, QuantityInv[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, QuantityInv[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, QuantityInv[playerid][19], 150);
    PlayerTextDrawFont(playerid, QuantityInv[playerid][19], 1);
    PlayerTextDrawSetProportional(playerid, QuantityInv[playerid][19], 1);
}

hook OnPlayerConnect(playerid)
{
    CreateInventoryTextdraw(playerid);
    return 1;
}

ShowInventoryTD(playerid)
{
    for(new i; i < 38; i ++)
    {
        PlayerTextDrawShow(playerid, InventoryTD[playerid][i]);
    }
    for(new i; i < 20; i ++)
    {
        PlayerTextDrawBackgroundColor(playerid, PrevMod[playerid][i], 0);
    }
    AccountData[playerid][pAmountInv] = 0;
    PlayerTextDrawSetString(playerid, InventoryTD[playerid][33], "Ammount");
}

Inventory_Show(playerid)
{
    if(!IsPlayerConnected(playerid)) return 0;

    SendClientMessage(playerid, -1, " ");
    SendClientMessage(playerid, -1, " ");
    SendClientMessage(playerid, -1, " ");
    SendClientMessage(playerid, -1, " ");
    SendClientMessage(playerid, -1, " ");
    SendClientMessage(playerid, -1, " ");
    SendClientMessage(playerid, -1, " ");
    SendClientMessage(playerid, -1, " ");
    SendClientMessage(playerid, -1, " ");
    SendClientMessage(playerid, -1, " ");

    ShowInventoryTD(playerid);
    new str[120], Float:jumlahbar;
    for(new index; index < MAX_INVENTORY; index ++) 
    {
        if(InventoryData[playerid][index][invExists])
        {
            for (new i; i < sizeof(g_aInventoryItems); i ++) if(!strcmp(g_aInventoryItems[i][e_InventoryItem], InventoryData[playerid][index][invItem], true))
            {
                PlayerTextDrawSetPreviewModel(playerid, PrevMod[playerid][index], InventoryData[playerid][index][invModel]);
                PlayerTextDrawShow(playerid, PrevMod[playerid][index]);

                format(str, sizeof(str), "%s", g_aInventoryItems[i][e_InventoryItem], InventoryData[playerid][index][invQuantity]);
                PlayerTextDrawSetString(playerid, NameInv[playerid][index], str);
                PlayerTextDrawShow(playerid, NameInv[playerid][index]);

                format(str, sizeof(str), "%dx", InventoryData[playerid][index][invQuantity]);
                PlayerTextDrawSetString(playerid, QuantityInv[playerid][index], str);
                PlayerTextDrawShow(playerid, QuantityInv[playerid][index]);

                PlayerTextDrawShow(playerid, ExistsInv[playerid][index]);
            }
        }
    }
    jumlahbar = AccountData[playerid][pBeratItem]*234.000000/50.0;
    PlayerTextDrawTextSize(playerid, InventoryTD[playerid][2], jumlahbar, 5.000000);
    PlayerTextDrawShow(playerid, InventoryTD[playerid][2]);

    format(str, sizeof(str), "%s", AccountData[playerid][pName]);
    PlayerTextDrawSetString(playerid, InventoryTD[playerid][0], str);
    PlayerTextDrawShow(playerid, InventoryTD[playerid][0]);

    format(str, sizeof(str), "%.3f/50", AccountData[playerid][pBeratItem]);
    PlayerTextDrawSetString(playerid, InventoryTD[playerid][3], str);
    PlayerTextDrawShow(playerid, InventoryTD[playerid][3]);
    
    SelectTextDraw(playerid, 0xFF9999FF);
    return 1;
}

Inventory_Close(playerid)
{
    forex(i, 38)
    {
        PlayerTextDrawHide(playerid, InventoryTD[playerid][i]);
    }
    forex(i, MAX_INVENTORY)
    {
        PlayerTextDrawHide(playerid, PrevMod[playerid][i]);
        PlayerTextDrawHide(playerid, NameInv[playerid][i]);
        PlayerTextDrawHide(playerid, QuantityInv[playerid][i]);
        PlayerTextDrawHide(playerid, ExistsInv[playerid][i]);
    }
    CancelSelectTextDraw(playerid);
    AccountData[playerid][pSelectItem] = -1;
    AccountData[playerid][pAmountInv] = 0;
    return 1;
}
