#include <YSI\y_hooks>

new PlayerText: i_box[MAX_PLAYERS][MAX_INVENTORY];
new PlayerText: i_model[MAX_PLAYERS][MAX_INVENTORY];
new PlayerText: i_item[MAX_PLAYERS][MAX_INVENTORY];
new PlayerText: i_qwt[MAX_PLAYERS][MAX_INVENTORY];
//new PlayerText: i_string[MAX_PLAYERS][6];
new PlayerText: i_textdraw[MAX_PLAYERS][47];

CreateInventoryTextdraw(playerid)
{
    i_textdraw[playerid][0] = CreatePlayerTextDraw(playerid, 150.000, 113.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][0], 351.000, 222.000);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][0], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][0], 60);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][0], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][0], 1);

    i_textdraw[playerid][1] = CreatePlayerTextDraw(playerid, 150.000, 113.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][1], 351.000, 15.000);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][1], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][1], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][1], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][1], 1);

    i_textdraw[playerid][2] = CreatePlayerTextDraw(playerid, 150.000, 113.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][2], 2.000, 15.000);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][2], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][2], 16777215);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][2], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][2], 1);

    i_box[playerid][0] = CreatePlayerTextDraw(playerid, 152.000, 140.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][0], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][0], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][0], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][0], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][0], 1);

    i_box[playerid][1] = CreatePlayerTextDraw(playerid, 196.000, 140.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][1], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][1], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][1], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][1], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][1], 1);

    i_box[playerid][2] = CreatePlayerTextDraw(playerid, 239.500, 140.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][2], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][2], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][2], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][2], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][2], 1);

    i_box[playerid][3] = CreatePlayerTextDraw(playerid, 283.500, 140.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][3], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][3], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][3], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][3], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][3], 1);

    i_box[playerid][4] = CreatePlayerTextDraw(playerid, 327.500, 140.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][4], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][4], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][4], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][4], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][4], 1);

    i_box[playerid][5] = CreatePlayerTextDraw(playerid, 327.500, 186.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][5], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][5], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][5], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][5], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][5], 1);

    i_box[playerid][6] = CreatePlayerTextDraw(playerid, 283.500, 186.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][6], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][6], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][6], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][6], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][6], 1);

    i_box[playerid][7] = CreatePlayerTextDraw(playerid, 239.500, 186.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][7], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][7], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][7], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][7], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][7], 1);

    i_box[playerid][8] = CreatePlayerTextDraw(playerid, 196.000, 186.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][8], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][8], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][8], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][8], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][8], 1);

    i_box[playerid][9] = CreatePlayerTextDraw(playerid, 152.000, 186.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][9], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][9], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][9], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][9], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][9], 1);

    i_box[playerid][10] = CreatePlayerTextDraw(playerid, 152.000, 232.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][10], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][10], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][10], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][10], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][10], 1);

    i_box[playerid][11] = CreatePlayerTextDraw(playerid, 196.000, 232.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][11], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][11], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][11], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][11], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][11], 1);

    i_box[playerid][12] = CreatePlayerTextDraw(playerid, 239.500, 232.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][12], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][12], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][12], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][12], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][12], 1);

    i_box[playerid][13] = CreatePlayerTextDraw(playerid, 283.500, 232.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][13], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][13], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][13], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][13], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][13], 1);

    i_box[playerid][14] = CreatePlayerTextDraw(playerid, 327.500, 232.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][14], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][14], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][14], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][14], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][14], 1);

    i_box[playerid][15] = CreatePlayerTextDraw(playerid, 327.500, 278.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][15], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][15], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][15], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][15], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][15], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][15], 1);

    i_box[playerid][16] = CreatePlayerTextDraw(playerid, 283.500, 278.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][16], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][16], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][16], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][16], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][16], 1);

    i_box[playerid][17] = CreatePlayerTextDraw(playerid, 239.500, 278.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][17], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][17], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][17], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][17], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][17], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][17], 1);

    i_box[playerid][18] = CreatePlayerTextDraw(playerid, 196.000, 278.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][18], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][18], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][18], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][18], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][18], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][18], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][18], 1);

    i_box[playerid][19] = CreatePlayerTextDraw(playerid, 152.000, 278.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_box[playerid][19], 42.000, 44.000);
    PlayerTextDrawAlignment(playerid, i_box[playerid][19], 1);
    PlayerTextDrawColor(playerid, i_box[playerid][19], 100);
    PlayerTextDrawSetShadow(playerid, i_box[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, i_box[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, i_box[playerid][19], 255);
    PlayerTextDrawFont(playerid, i_box[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, i_box[playerid][19], 1);
    PlayerTextDrawSetSelectable(playerid, i_box[playerid][19], 1);

    i_model[playerid][0] = CreatePlayerTextDraw(playerid, 196.000, 158.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][0], 38.000, 39.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][0], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][0], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][0], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][0], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][0], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][0], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][0], 0, 0);

    i_model[playerid][0] = CreatePlayerTextDraw(playerid, 151.000, 141.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][0], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][0], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][0], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][0], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][0], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][0], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][0], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][0], 0, 0);

    i_model[playerid][1] = CreatePlayerTextDraw(playerid, 195.000, 141.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][1], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][1], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][1], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][1], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][1], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][1], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][1], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][1], 0, 0);

    i_model[playerid][2] = CreatePlayerTextDraw(playerid, 239.000, 141.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][2], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][2], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][2], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][2], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][2], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][2], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][2], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][2], 0, 0);

    i_model[playerid][3] = CreatePlayerTextDraw(playerid, 283.000, 141.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][3], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][3], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][3], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][3], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][3], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][3], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][3], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][3], 0, 0);

    i_model[playerid][4] = CreatePlayerTextDraw(playerid, 327.000, 141.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][4], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][4], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][4], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][4], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][4], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][4], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][4], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][4], 0, 0);

    i_model[playerid][5] = CreatePlayerTextDraw(playerid, 327.000, 188.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][5], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][5], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][5], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][5], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][5], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][5], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][5], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][5], 0, 0);

    i_model[playerid][6] = CreatePlayerTextDraw(playerid, 283.000, 188.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][6], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][6], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][6], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][6], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][6], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][6], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][6], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][6], 0, 0);

    i_model[playerid][7] = CreatePlayerTextDraw(playerid, 239.000, 188.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][7], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][7], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][7], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][7], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][7], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][7], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][7], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][7], 0, 0);

    i_model[playerid][8] = CreatePlayerTextDraw(playerid, 196.000, 188.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][8], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][8], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][8], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][8], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][8], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][8], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][8], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][8], 0, 0);

    i_model[playerid][9] = CreatePlayerTextDraw(playerid, 151.000, 188.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][9], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][9], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][9], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][9], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][9], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][9], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][9], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][9], 0, 0);

    i_model[playerid][10] = CreatePlayerTextDraw(playerid, 151.000, 234.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][10], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][10], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][10], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][10], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][10], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][10], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][10], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][10], 0, 0);

    i_model[playerid][11] = CreatePlayerTextDraw(playerid, 196.000, 234.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][11], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][11], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][11], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][11], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][11], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][11], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][11], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][11], 0, 0);

    i_model[playerid][12] = CreatePlayerTextDraw(playerid, 239.000, 234.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][12], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][12], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][12], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][12], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][12], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][12], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][12], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][12], 0, 0);

    i_model[playerid][13] = CreatePlayerTextDraw(playerid, 283.000, 234.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][13], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][13], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][13], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][13], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][13], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][13], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][13], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][13], 0, 0);

    i_model[playerid][14] = CreatePlayerTextDraw(playerid, 327.000, 234.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][14], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][14], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][14], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][14], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][14], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][14], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][14], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][14], 0, 0);

    i_model[playerid][15] = CreatePlayerTextDraw(playerid, 327.000, 280.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][15], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][15], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][15], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][15], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][15], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][15], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][15], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][15], 0, 0);

    i_model[playerid][16] = CreatePlayerTextDraw(playerid, 283.000, 280.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][16], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][16], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][16], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][16], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][16], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][16], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][16], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][16], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][16], 0, 0);

    i_model[playerid][17] = CreatePlayerTextDraw(playerid, 239.000, 280.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][17], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][17], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][17], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][17], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][17], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][17], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][17], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][17], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][17], 0, 0);

    i_model[playerid][18] = CreatePlayerTextDraw(playerid, 196.000, 280.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][18], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][18], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][18], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][18], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][18], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][18], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][18], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][18], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][18], 0, 0);

    i_model[playerid][19] = CreatePlayerTextDraw(playerid, 151.000, 280.000, "_");
    PlayerTextDrawTextSize(playerid, i_model[playerid][19], 42.000, 36.000);
    PlayerTextDrawAlignment(playerid, i_model[playerid][19], 1);
    PlayerTextDrawColor(playerid, i_model[playerid][19], -1);
    PlayerTextDrawSetShadow(playerid, i_model[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, i_model[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, i_model[playerid][19], 0);
    PlayerTextDrawFont(playerid, i_model[playerid][19], 5);
    PlayerTextDrawSetProportional(playerid, i_model[playerid][19], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_model[playerid][19], 2663);
    PlayerTextDrawSetPreviewRot(playerid, i_model[playerid][19], 0.000, 0.000, 0.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_model[playerid][19], 0, 0);

    i_item[playerid][0] = CreatePlayerTextDraw(playerid, 172.000, 175.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][0], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][0], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][0], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][0], 1);

    i_item[playerid][1] = CreatePlayerTextDraw(playerid, 216.000, 175.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][1], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][1], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][1], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][1], 1);

    i_item[playerid][2] = CreatePlayerTextDraw(playerid, 260.000, 175.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][2], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][2], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][2], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][2], 1);

    i_item[playerid][3] = CreatePlayerTextDraw(playerid, 304.000, 175.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][3], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][3], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][3], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][3], 1);

    i_item[playerid][4] = CreatePlayerTextDraw(playerid, 348.000, 175.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][4], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][4], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][4], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][4], 1);

    i_item[playerid][5] = CreatePlayerTextDraw(playerid, 348.000, 222.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][5], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][5], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][5], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][5], 1);

    i_item[playerid][6] = CreatePlayerTextDraw(playerid, 304.000, 222.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][6], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][6], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][6], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][6], 1);

    i_item[playerid][7] = CreatePlayerTextDraw(playerid, 260.000, 222.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][7], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][7], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][7], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][7], 1);

    i_item[playerid][8] = CreatePlayerTextDraw(playerid, 217.000, 222.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][8], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][8], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][8], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][8], 1);

    i_item[playerid][9] = CreatePlayerTextDraw(playerid, 172.000, 222.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][9], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][9], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][9], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][9], 1);

    i_item[playerid][10] = CreatePlayerTextDraw(playerid, 172.000, 267.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][10], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][10], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][10], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][10], 1);

    i_item[playerid][11] = CreatePlayerTextDraw(playerid, 216.000, 267.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][11], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][11], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][11], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][11], 1);

    i_item[playerid][12] = CreatePlayerTextDraw(playerid, 259.000, 267.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][12], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][12], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][12], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][12], 1);

    i_item[playerid][13] = CreatePlayerTextDraw(playerid, 303.000, 267.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][13], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][13], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][13], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][13], 1);

    i_item[playerid][14] = CreatePlayerTextDraw(playerid, 348.000, 267.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][14], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][14], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][14], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][14], 1);

    i_item[playerid][15] = CreatePlayerTextDraw(playerid, 348.000, 313.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][15], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][15], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][15], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][15], 1);

    i_item[playerid][16] = CreatePlayerTextDraw(playerid, 303.000, 313.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][16], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][16], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][16], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][16], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][16], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][16], 1);

    i_item[playerid][17] = CreatePlayerTextDraw(playerid, 260.000, 313.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][17], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][17], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][17], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][17], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][17], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][17], 1);

    i_item[playerid][18] = CreatePlayerTextDraw(playerid, 216.000, 313.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][18], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][18], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][18], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][18], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][18], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][18], 1);

    i_item[playerid][19] = CreatePlayerTextDraw(playerid, 172.000, 313.000, "Makanan");
    PlayerTextDrawLetterSize(playerid, i_item[playerid][19], 0.150, 0.799);
    PlayerTextDrawAlignment(playerid, i_item[playerid][19], 2);
    PlayerTextDrawColor(playerid, i_item[playerid][19], -1);
    PlayerTextDrawSetShadow(playerid, i_item[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, i_item[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, i_item[playerid][19], 150);
    PlayerTextDrawFont(playerid, i_item[playerid][19], 1);
    PlayerTextDrawSetProportional(playerid, i_item[playerid][19], 1);

    i_qwt[playerid][0] = CreatePlayerTextDraw(playerid, 153.000, 141.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][0], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][0], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][0], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][0], 1);

    i_qwt[playerid][1] = CreatePlayerTextDraw(playerid, 197.000, 141.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][1], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][1], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][1], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][1], 1);

    i_qwt[playerid][2] = CreatePlayerTextDraw(playerid, 241.000, 141.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][2], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][2], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][2], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][2], 1);

    i_qwt[playerid][3] = CreatePlayerTextDraw(playerid, 285.000, 141.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][3], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][3], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][3], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][3], 1);

    i_qwt[playerid][4] = CreatePlayerTextDraw(playerid, 329.000, 141.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][4], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][4], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][4], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][4], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][4], 1);

    i_qwt[playerid][5] = CreatePlayerTextDraw(playerid, 329.000, 187.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][5], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][5], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][5], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][5], 1);

    i_qwt[playerid][6] = CreatePlayerTextDraw(playerid, 285.000, 187.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][6], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][6], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][6], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][6], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][6], 1);

    i_qwt[playerid][7] = CreatePlayerTextDraw(playerid, 241.000, 187.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][7], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][7], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][7], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][7], 1);

    i_qwt[playerid][8] = CreatePlayerTextDraw(playerid, 197.000, 187.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][8], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][8], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][8], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][8], 1);

    i_qwt[playerid][9] = CreatePlayerTextDraw(playerid, 153.000, 187.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][9], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][9], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][9], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][9], 1);

    i_qwt[playerid][10] = CreatePlayerTextDraw(playerid, 153.000, 233.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][10], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][10], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][10], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][10], 1);

    i_qwt[playerid][11] = CreatePlayerTextDraw(playerid, 197.000, 233.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][11], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][11], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][11], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][11], 1);

    i_qwt[playerid][12] = CreatePlayerTextDraw(playerid, 241.000, 233.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][12], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][12], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][12], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][12], 1);

    i_qwt[playerid][13] = CreatePlayerTextDraw(playerid, 284.000, 233.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][13], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][13], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][13], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][13], 1);

    i_qwt[playerid][14] = CreatePlayerTextDraw(playerid, 329.000, 233.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][14], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][14], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][14], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][14], 1);

    i_qwt[playerid][15] = CreatePlayerTextDraw(playerid, 329.000, 279.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][15], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][15], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][15], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][15], 1);

    i_qwt[playerid][16] = CreatePlayerTextDraw(playerid, 285.000, 279.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][16], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][16], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][16], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][16], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][16], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][16], 1);

    i_qwt[playerid][17] = CreatePlayerTextDraw(playerid, 240.000, 279.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][17], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][17], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][17], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][17], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][17], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][17], 1);

    i_qwt[playerid][18] = CreatePlayerTextDraw(playerid, 197.000, 279.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][18], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][18], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][18], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][18], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][18], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][18], 1);

    i_qwt[playerid][19] = CreatePlayerTextDraw(playerid, 153.000, 279.000, "100x");
    PlayerTextDrawLetterSize(playerid, i_qwt[playerid][19], 0.108, 0.598);
    PlayerTextDrawAlignment(playerid, i_qwt[playerid][19], 1);
    PlayerTextDrawColor(playerid, i_qwt[playerid][19], -1);
    PlayerTextDrawSetShadow(playerid, i_qwt[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, i_qwt[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, i_qwt[playerid][19], 150);
    PlayerTextDrawFont(playerid, i_qwt[playerid][19], 1);
    PlayerTextDrawSetProportional(playerid, i_qwt[playerid][19], 1);

    i_textdraw[playerid][3] = CreatePlayerTextDraw(playerid, 153.000, 131.000, "80.6/150.0");
    PlayerTextDrawLetterSize(playerid, i_textdraw[playerid][3], 0.119, 0.699);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][3], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][3], -1);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][3], 150);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][3], 1);

    i_textdraw[playerid][4] = CreatePlayerTextDraw(playerid, 154.000, 117.000, "INVENTORY DISTRICT");
    PlayerTextDrawLetterSize(playerid, i_textdraw[playerid][4], 0.170, 0.799);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][4], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][4], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][4], 150);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][4], 1);

    i_textdraw[playerid][5] = CreatePlayerTextDraw(playerid, 372.000, 142.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][5], 2.000, 181.000);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][5], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][5], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][5], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][5], 1);

    i_textdraw[playerid][6] = CreatePlayerTextDraw(playerid, 372.000, 142.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][6], 2.000, 181.000);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][6], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][6], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][6], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][6], 1);

    i_textdraw[playerid][7] = CreatePlayerTextDraw(playerid, 347.000, 137.000, "_");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][7], 169.000, 164.000);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][7], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][7], -1);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][7], 0);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][7], 5);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][7], 0);
    PlayerTextDrawSetPreviewModel(playerid, i_textdraw[playerid][7], 7);
    PlayerTextDrawSetPreviewRot(playerid, i_textdraw[playerid][7], 0.000, 0.000, -25.000, 1.000);
    PlayerTextDrawSetPreviewVehCol(playerid, i_textdraw[playerid][7], 0, 0);

    i_textdraw[playerid][8] = CreatePlayerTextDraw(playerid, 435.000, 135.000, "District ");
    PlayerTextDrawLetterSize(playerid, i_textdraw[playerid][8], 0.170, 0.799);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][8], 2);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][8], 150);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][8], 1);

    i_textdraw[playerid][9] = CreatePlayerTextDraw(playerid, 435.000, 315.000, "ID: 0");
    PlayerTextDrawLetterSize(playerid, i_textdraw[playerid][9], 0.170, 0.799);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][9], 2);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][9], 150);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][9], 1);

    i_textdraw[playerid][10] = CreatePlayerTextDraw(playerid, 498.000, 139.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][10], 3.000, 181.000);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][10], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][10], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][10], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][10], 1);

    i_textdraw[playerid][11] = CreatePlayerTextDraw(playerid, 150.000, 339.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][11], 351.000, 22.000);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][11], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][11], 60);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][11], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][11], 1);

    i_textdraw[playerid][12] = CreatePlayerTextDraw(playerid, 162.000, 343.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][12], 34.000, 14.000);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][12], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][12], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][12], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][12], 1);

    i_textdraw[playerid][13] = CreatePlayerTextDraw(playerid, 153.000, 339.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][13], 17.000, 20.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][13], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][13], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][13], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][13], 1);

    i_textdraw[playerid][14] = CreatePlayerTextDraw(playerid, 188.000, 339.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][14], 17.000, 20.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][14], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][14], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][14], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][14], 1);

    i_textdraw[playerid][15] = CreatePlayerTextDraw(playerid, 205.000, 339.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][15], 17.000, 20.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][15], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][15], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][15], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][15], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][15], 1);

    i_textdraw[playerid][16] = CreatePlayerTextDraw(playerid, 214.000, 343.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][16], 34.000, 14.000);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][16], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][16], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][16], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][16], 1);

    i_textdraw[playerid][17] = CreatePlayerTextDraw(playerid, 241.000, 339.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][17], 17.000, 20.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][17], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][17], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][17], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][17], 1);

    i_textdraw[playerid][18] = CreatePlayerTextDraw(playerid, 257.000, 339.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][18], 17.000, 20.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][18], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][18], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][18], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][18], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][18], 1);

    i_textdraw[playerid][19] = CreatePlayerTextDraw(playerid, 267.000, 343.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][19], 34.000, 14.000);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][19], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][19], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][19], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][19], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][19], 1);

    i_textdraw[playerid][20] = CreatePlayerTextDraw(playerid, 293.000, 339.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][20], 17.000, 20.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][20], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][20], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][20], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][20], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][20], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][20], 1);

    i_textdraw[playerid][21] = CreatePlayerTextDraw(playerid, 309.000, 339.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][21], 17.000, 20.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][21], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][21], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][21], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][21], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][21], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][21], 1);

    i_textdraw[playerid][22] = CreatePlayerTextDraw(playerid, 318.000, 343.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][22], 34.000, 14.000);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][22], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][22], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][22], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][22], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][22], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][22], 1);

    i_textdraw[playerid][23] = CreatePlayerTextDraw(playerid, 344.000, 339.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][23], 17.000, 20.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][23], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][23], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][23], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][23], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][23], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][23], 1);

    i_textdraw[playerid][24] = CreatePlayerTextDraw(playerid, 481.000, 339.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][24], 17.000, 20.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][24], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][24], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][24], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][24], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][24], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][24], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][24], 1);

    i_textdraw[playerid][25] = CreatePlayerTextDraw(playerid, 455.000, 343.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][25], 34.000, 14.000);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][25], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][25], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][25], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][25], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][25], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][25], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][25], 1);

    i_textdraw[playerid][26] = CreatePlayerTextDraw(playerid, 446.000, 339.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][26], 17.000, 20.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][26], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][26], 2147472639);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][26], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][26], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][26], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][26], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][26], 1);

    i_textdraw[playerid][27] = CreatePlayerTextDraw(playerid, 154.000, 340.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][27], 17.000, 18.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][27], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][27], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][27], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][27], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][27], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][27], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][27], 1);

    i_textdraw[playerid][28] = CreatePlayerTextDraw(playerid, 187.000, 340.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][28], 17.000, 18.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][28], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][28], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][28], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][28], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][28], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][28], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][28], 1);

    i_textdraw[playerid][29] = CreatePlayerTextDraw(playerid, 162.000, 344.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][29], 34.000, 11.800);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][29], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][29], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][29], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][29], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][29], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][29], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][29], 1);
    PlayerTextDrawSetSelectable(playerid, i_textdraw[playerid][29], 1);

    i_textdraw[playerid][30] = CreatePlayerTextDraw(playerid, 214.000, 344.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][30], 34.000, 11.800);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][30], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][30], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][30], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][30], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][30], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][30], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][30], 1);
    PlayerTextDrawSetSelectable(playerid, i_textdraw[playerid][30], 1);

    i_textdraw[playerid][31] = CreatePlayerTextDraw(playerid, 206.000, 340.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][31], 17.000, 18.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][31], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][31], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][31], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][31], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][31], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][31], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][31], 1);

    i_textdraw[playerid][32] = CreatePlayerTextDraw(playerid, 240.000, 340.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][32], 17.000, 18.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][32], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][32], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][32], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][32], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][32], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][32], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][32], 1);

    i_textdraw[playerid][33] = CreatePlayerTextDraw(playerid, 266.000, 344.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][33], 34.000, 11.800);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][33], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][33], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][33], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][33], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][33], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][33], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][33], 1);
    PlayerTextDrawSetSelectable(playerid, i_textdraw[playerid][33], 1);

    i_textdraw[playerid][34] = CreatePlayerTextDraw(playerid, 258.000, 340.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][34], 17.000, 18.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][34], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][34], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][34], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][34], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][34], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][34], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][34], 1);

    i_textdraw[playerid][35] = CreatePlayerTextDraw(playerid, 292.000, 340.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][35], 17.000, 18.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][35], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][35], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][35], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][35], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][35], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][35], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][35], 1);

    i_textdraw[playerid][36] = CreatePlayerTextDraw(playerid, 318.000, 344.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][36], 34.000, 11.800);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][36], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][36], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][36], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][36], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][36], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][36], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][36], 1);
    PlayerTextDrawSetSelectable(playerid, i_textdraw[playerid][36], 1);

    i_textdraw[playerid][37] = CreatePlayerTextDraw(playerid, 310.000, 340.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][37], 17.000, 18.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][37], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][37], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][37], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][37], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][37], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][37], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][37], 1);

    i_textdraw[playerid][38] = CreatePlayerTextDraw(playerid, 343.000, 340.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][38], 17.000, 18.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][38], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][38], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][38], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][38], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][38], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][38], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][38], 1);

    i_textdraw[playerid][39] = CreatePlayerTextDraw(playerid, 455.000, 344.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][39], 34.000, 11.800);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][39], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][39], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][39], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][39], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][39], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][39], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][39], 1);
    PlayerTextDrawSetSelectable(playerid, i_textdraw[playerid][39], 1);

    i_textdraw[playerid][40] = CreatePlayerTextDraw(playerid, 447.000, 340.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][40], 17.000, 18.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][40], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][40], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][40], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][40], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][40], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][40], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][40], 1);

    i_textdraw[playerid][41] = CreatePlayerTextDraw(playerid, 480.000, 340.500, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, i_textdraw[playerid][41], 17.000, 18.500);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][41], 1);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][41], 255);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][41], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][41], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][41], 255);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][41], 4);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][41], 1);

    i_textdraw[playerid][42] = CreatePlayerTextDraw(playerid, 179.000, 345.000, "Use");
    PlayerTextDrawLetterSize(playerid, i_textdraw[playerid][42], 0.170, 0.799);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][42], 2);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][42], -1);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][42], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][42], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][42], 150);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][42], 1);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][42], 1);

    i_textdraw[playerid][43] = CreatePlayerTextDraw(playerid, 232.000, 345.000, "Ammount");
    PlayerTextDrawLetterSize(playerid, i_textdraw[playerid][43], 0.170, 0.799);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][43], 2);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][43], -1);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][43], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][43], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][43], 150);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][43], 1);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][43], 1);

    i_textdraw[playerid][44] = CreatePlayerTextDraw(playerid, 283.000, 345.000, "Give");
    PlayerTextDrawLetterSize(playerid, i_textdraw[playerid][44], 0.170, 0.799);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][44], 2);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][44], -1);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][44], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][44], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][44], 150);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][44], 1);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][44], 1);

    i_textdraw[playerid][45] = CreatePlayerTextDraw(playerid, 335.000, 345.000, "Drop");
    PlayerTextDrawLetterSize(playerid, i_textdraw[playerid][45], 0.170, 0.799);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][45], 2);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][45], -1);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][45], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][45], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][45], 150);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][45], 1);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][45], 1);

    i_textdraw[playerid][46] = CreatePlayerTextDraw(playerid, 473.000, 345.000, "Close");
    PlayerTextDrawLetterSize(playerid, i_textdraw[playerid][46], 0.170, 0.799);
    PlayerTextDrawAlignment(playerid, i_textdraw[playerid][46], 2);
    PlayerTextDrawColor(playerid, i_textdraw[playerid][46], -1);
    PlayerTextDrawSetShadow(playerid, i_textdraw[playerid][46], 0);
    PlayerTextDrawSetOutline(playerid, i_textdraw[playerid][46], 0);
    PlayerTextDrawBackgroundColor(playerid, i_textdraw[playerid][46], 150);
    PlayerTextDrawFont(playerid, i_textdraw[playerid][46], 1);
    PlayerTextDrawSetProportional(playerid, i_textdraw[playerid][46], 1);
}

CreateInventoryGTextdraw()
{

}

hook OnGameModeInit()
{
    CreateInventoryGTextdraw();
    return 1;
}
hook OnPlayerConnect(playerid)
{
    CreateInventoryTextdraw(playerid);
    return 1;
}

ShowInventoryTD(playerid)
{
    forex(i, 47)
    {
        PlayerTextDrawShow(playerid, inv::textdraw[playerid][i]);
    }
    AccountData[playerid][pAmountInv] = 0;
    PlayerTextDrawSetString(playerid, inv::textdraw[playerid][43], "Amount");
    for(new x = 0; x < 15; x ++) PlayerTextDrawHide(playerid, HbeStuffs[playerid][x]);
    HideHBE(playerid);
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
    new str[256], Float:chess7;
    for(new index; index < MAX_INVENTORY; index ++) 
    {
        PlayerTextDrawShow(playerid, inv::box[playerid][index]);
        if(InventoryData[playerid][index][invExists])
        {
            for (new i; i < sizeof(g_aInventoryItems); i ++) if(!strcmp(g_aInventoryItems[i][e_InventoryItem], InventoryData[playerid][index][invItem], true))
            {
                
                PlayerTextDrawSetPreviewModel(playerid, inv::model[playerid][index], InventoryData[playerid][index][invModel]);
                PlayerTextDrawShow(playerid, inv::model[playerid][index]);

                format(str, sizeof(str), "%s", g_aInventoryItems[i][e_InventoryItem], InventoryData[playerid][index][invQuantity]);
                PlayerTextDrawSetString(playerid, inv::item[playerid][index], str);
                PlayerTextDrawShow(playerid, inv::item[playerid][index]);

                format(str, sizeof(str), "%dx (%.1f)", InventoryData[playerid][index][invQuantity], Float:GetInventoryWeight(g_aInventoryItems[i][e_InventoryItem], InventoryData[playerid][index][invQuantity]));
                PlayerTextDrawSetString(playerid, inv::qwt[playerid][index], str);
                PlayerTextDrawShow(playerid, inv::qwt[playerid][index]);

                //PlayerTextDrawShow(playerid, inv::bar[playerid][index]);
            }
        }
    }

    chess7 = AccountData[playerid][pBeratItem]*181.000000/100.0;

    PlayerTextDrawTextSize(playerid, inv::textdraw[playerid][6], 2.000000, chess7);
    PlayerTextDrawShow(playerid, inv::textdraw[playerid][6]);
    
    format(str, sizeof(str), "%.1f/100.0", AccountData[playerid][pBeratItem]);
    PlayerTextDrawSetString(playerid, inv::textdraw[playerid][3], str);
    PlayerTextDrawShow(playerid, inv::textdraw[playerid][3]);

    format(str, sizeof(str), "ID: %d", playerid);
    PlayerTextDrawSetString(playerid, inv::textdraw[playerid][9], str);
    PlayerTextDrawShow(playerid, inv::textdraw[playerid][9]);

    format(str, sizeof(str), "%s", AccountData[playerid][pName]);
    PlayerTextDrawSetString(playerid, inv::textdraw[playerid][8], str);
    PlayerTextDrawShow(playerid, inv::textdraw[playerid][8]);
    
    SelectTextDraw(playerid, COLOR_BLUE);
    return 1;
}

Inventory_Close(playerid)
{
    forex(i, 47)
    {
        PlayerTextDrawHide(playerid, inv::textdraw[playerid][i]);
    }
    forex(i, MAX_INVENTORY)
    {
        PlayerTextDrawHide(playerid, inv::box[playerid][i]);
        PlayerTextDrawHide(playerid, inv::model[playerid][i]);
        PlayerTextDrawHide(playerid, inv::item[playerid][i]);
        PlayerTextDrawHide(playerid, inv::qwt[playerid][i]);
    }
    CancelSelectTextDraw(playerid);
    AccountData[playerid][pSelectItem] = -1;
    AccountData[playerid][pAmountInv] = 0;
    ShowHbeTextdraws(playerid, AccountData[playerid][pHUDMode]);
    return 1;
}


stock SelectItem(playerid, i)
{
    AccountData[playerid][pSelectItem] = i;
    PlayerTextDrawColor(playerid, inv::box[playerid][i], 1768515960);
    PlayerTextDrawShow(playerid, inv::box[playerid][i]);
    PlayerPlaySound(playerid, 1052, 0, 0, 0);
    return 1;
}

stock UnselectItem(playerid)
{
    if(AccountData[playerid][pSelectItem] != -1)
    {
        PlayerTextDrawHide(playerid, inv::box[playerid][AccountData[playerid][pSelectItem]]);
        PlayerTextDrawColor(playerid, inv::box[playerid][AccountData[playerid][pSelectItem]], 135);
		PlayerTextDrawShow(playerid, inv::box[playerid][AccountData[playerid][pSelectItem]]);
    }
    AccountData[playerid][pSelectItem] = -1;
    return 1;
}

// stock MoveItemToNewSlot(playerid, b, a)
// {
//     //textdraw slot before moving
// 	PlayerTextDrawSetPreviewModel(playerid, inv::model[playerid][b], 11477);
// 	PlayerTextDrawSetString(playerid, inv::item[playerid][b], "_");
// 	PlayerTextDrawSetString(playerid, inv::qwt[playerid][b], "_");
//     //var inv item
// 	InventoryData[playerid][a][invExists] = true;
// 	InventoryData[playerid][a][invModel] = InventoryData[playerid][b][invModel];
// 	InventoryData[playerid][a][invQuantity] = InventoryData[playerid][b][invQuantity];
// 	strpack(InventoryData[playerid][a][invItem], InventoryData[playerid][b][invItem], 32 char);
//     //var after inv item
// 	InventoryData[playerid][b][invExists] = false;
// 	InventoryData[playerid][b][invModel] = 0;
// 	InventoryData[playerid][b][invQuantity] = 0;
// 	strpack(InventoryData[playerid][b][invItem], "", 32 char);
//     //textdrawslot after moving
// 	new invStr[64];
// 	format(invStr, 64, "%dx (%.1f)", InventoryData[playerid][a][invQuantity], Float:GetInventoryWeight(InventoryData[playerid][a][invItem], InventoryData[playerid][a][invQuantity]));
// 	PlayerTextDrawSetPreviewModel(playerid, inv::model[playerid][a], InventoryData[playerid][a][invModel]);
// 	PlayerTextDrawSetString(playerid, inv::item[playerid][a], InventoryData[playerid][a][invItem]);
// 	PlayerTextDrawSetString(playerid, inv::qwt[playerid][a], invStr);
// 	//all show and hide slot textdraw
// 	PlayerTextDrawHide(playerid, inv::box[playerid][b]);
// 	PlayerTextDrawHide(playerid, inv::model[playerid][b]);
// 	PlayerTextDrawHide(playerid, inv::qwt[playerid][b]);
// 	PlayerTextDrawHide(playerid, inv::item[playerid][b]);
// 	PlayerTextDrawShow(playerid, inv::box[playerid][a]);
// 	PlayerTextDrawShow(playerid, inv::model[playerid][a]);
// 	PlayerTextDrawShow(playerid, inv::qwt[playerid][a]);
// 	PlayerTextDrawShow(playerid, inv::item[playerid][a]);
//     return 1;
// }

stock MoveItemToNewSlot(playerid, fromSlot, toSlot)
{
    // Validasi input
    if(!InventoryData[playerid][fromSlot][invExists])
        return 0;
    
    if(InventoryData[playerid][toSlot][invExists])
        return 0;

    if(fromSlot < 0 || fromSlot >= MAX_INVENTORY || toSlot < 0 || toSlot >= MAX_INVENTORY) return 0;
    if(fromSlot == toSlot) return 0;
    
    new tempExists = InventoryData[playerid][fromSlot][invExists];
    new tempModel = InventoryData[playerid][fromSlot][invModel];
    new tempQuantity = InventoryData[playerid][fromSlot][invQuantity];
    new tempItem[32];
    strunpack(tempItem, InventoryData[playerid][fromSlot][invItem]);
    
    InventoryData[playerid][fromSlot][invExists] = false;
    InventoryData[playerid][fromSlot][invModel] = 0;
    InventoryData[playerid][fromSlot][invQuantity] = 0;
    strpack(InventoryData[playerid][fromSlot][invItem], "", 32 char);
    
    InventoryData[playerid][toSlot][invExists] = tempExists;
    InventoryData[playerid][toSlot][invModel] = tempModel;
    InventoryData[playerid][toSlot][invQuantity] = tempQuantity;
    strpack(InventoryData[playerid][toSlot][invItem], tempItem, 32 char);
    
    PlayerTextDrawSetPreviewModel(playerid, inv::model[playerid][fromSlot], 11477);
    PlayerTextDrawSetString(playerid, inv::item[playerid][fromSlot], "_");
    PlayerTextDrawSetString(playerid, inv::qwt[playerid][fromSlot], "_");
    
    new invStr[64];
    format(invStr, 64, "%dx (%.1f)", tempQuantity, Float:GetInventoryWeight(tempItem, tempQuantity));
    PlayerTextDrawSetPreviewModel(playerid, inv::model[playerid][toSlot], tempModel);
    PlayerTextDrawSetString(playerid, inv::item[playerid][toSlot], tempItem);
    PlayerTextDrawSetString(playerid, inv::qwt[playerid][toSlot], invStr);
    
    RefreshInventorySlot(playerid, fromSlot);
    RefreshInventorySlot(playerid, toSlot);
    
    return 1;
}

stock RefreshInventorySlot(playerid, slot)
{
    PlayerTextDrawHide(playerid, inv::box[playerid][slot]);
    PlayerTextDrawHide(playerid, inv::model[playerid][slot]);
    PlayerTextDrawHide(playerid, inv::qwt[playerid][slot]);
    PlayerTextDrawHide(playerid, inv::item[playerid][slot]);
    
    PlayerTextDrawShow(playerid, inv::box[playerid][slot]);
    PlayerTextDrawShow(playerid, inv::model[playerid][slot]);
    PlayerTextDrawShow(playerid, inv::qwt[playerid][slot]);
    PlayerTextDrawShow(playerid, inv::item[playerid][slot]);
}