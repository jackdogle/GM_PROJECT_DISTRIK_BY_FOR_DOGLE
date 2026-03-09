#include <YSI\y_hooks>
new PlayerText: SpawnHapp[MAX_PLAYERS][18];

CreateSpawnTextdraws(playerid)
{
    SpawnHapp[playerid][0] = CreatePlayerTextDraw(playerid, 251.000, 110.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, SpawnHapp[playerid][0], 136.000, 203.000);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][0], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][0], 512819004);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][0], 255);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][0], 1);

    SpawnHapp[playerid][1] = CreatePlayerTextDraw(playerid, 251.000, 212.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, SpawnHapp[playerid][1], 48.000, 1.000);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][1], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][1], 255);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][1], 1);

    SpawnHapp[playerid][2] = CreatePlayerTextDraw(playerid, 339.000, 212.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, SpawnHapp[playerid][2], 48.000, 1.000);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][2], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][2], 255);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][2], 1);

    SpawnHapp[playerid][3] = CreatePlayerTextDraw(playerid, 262.000, 116.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, SpawnHapp[playerid][3], 115.000, 26.000);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][3], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][3], 1116206336);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][3], 255);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, SpawnHapp[playerid][3], 1);

    SpawnHapp[playerid][4] = CreatePlayerTextDraw(playerid, 262.000, 143.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, SpawnHapp[playerid][4], 115.000, 26.000);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][4], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][4], 1116206336);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][4], 255);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, SpawnHapp[playerid][4], 1);

    SpawnHapp[playerid][5] = CreatePlayerTextDraw(playerid, 262.000, 170.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, SpawnHapp[playerid][5], 115.000, 26.000);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][5], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][5], 1116206336);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][5], 255);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, SpawnHapp[playerid][5], 1);

    SpawnHapp[playerid][6] = CreatePlayerTextDraw(playerid, 262.000, 226.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, SpawnHapp[playerid][6], 115.000, 26.000);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][6], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][6], 1116206336);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][6], 255);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, SpawnHapp[playerid][6], 1);

    SpawnHapp[playerid][7] = CreatePlayerTextDraw(playerid, 262.000, 253.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, SpawnHapp[playerid][7], 115.000, 26.000);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][7], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][7], 1116206336);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][7], 255);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, SpawnHapp[playerid][7], 1);

    SpawnHapp[playerid][8] = CreatePlayerTextDraw(playerid, 262.000, 280.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, SpawnHapp[playerid][8], 115.000, 26.000);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][8], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][8], 1116206336);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][8], 255);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, SpawnHapp[playerid][8], 1);

    SpawnHapp[playerid][9] = CreatePlayerTextDraw(playerid, 251.000, 316.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, SpawnHapp[playerid][9], 136.000, 26.000);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][9], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][9], 1097457980);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][9], 255);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, SpawnHapp[playerid][9], 1);

    SpawnHapp[playerid][10] = CreatePlayerTextDraw(playerid, 302.000, 124.000, "Bandara");
    PlayerTextDrawLetterSize(playerid, SpawnHapp[playerid][10], 0.238, 0.999);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][10], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][10], 150);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][10], 1);

    SpawnHapp[playerid][11] = CreatePlayerTextDraw(playerid, 285.000, 151.000, "Pelabuhan Merak");
    PlayerTextDrawLetterSize(playerid, SpawnHapp[playerid][11], 0.238, 0.999);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][11], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][11], 150);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][11], 1);

    SpawnHapp[playerid][12] = CreatePlayerTextDraw(playerid, 301.000, 177.000, "Carnaval");
    PlayerTextDrawLetterSize(playerid, SpawnHapp[playerid][12], 0.238, 0.999);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][12], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][12], 150);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][12], 1);

    SpawnHapp[playerid][13] = CreatePlayerTextDraw(playerid, 306.000, 233.000, "Rumah");
    PlayerTextDrawLetterSize(playerid, SpawnHapp[playerid][13], 0.238, 0.999);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][13], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][13], 150);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][13], 1);

    SpawnHapp[playerid][14] = CreatePlayerTextDraw(playerid, 298.000, 261.000, "Rusun");
    PlayerTextDrawLetterSize(playerid, SpawnHapp[playerid][14], 0.238, 0.999);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][14], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][14], 150);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][14], 1);

    SpawnHapp[playerid][15] = CreatePlayerTextDraw(playerid, 304.000, 288.000, "Last Exit");
    PlayerTextDrawLetterSize(playerid, SpawnHapp[playerid][15], 0.238, 0.999);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][15], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][15], 150);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][15], 1);

    SpawnHapp[playerid][16] = CreatePlayerTextDraw(playerid, 304.000, 321.000, "Spawn");
    PlayerTextDrawLetterSize(playerid, SpawnHapp[playerid][16], 0.289, 1.299);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][16], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][16], -1);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][16], 150);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][16], 1);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][16], 1);

    SpawnHapp[playerid][17] = CreatePlayerTextDraw(playerid, 301.000, 207.000, "PILIHAN SPAWN");
    PlayerTextDrawLetterSize(playerid, SpawnHapp[playerid][17], 0.119, 0.898);
    PlayerTextDrawAlignment(playerid, SpawnHapp[playerid][17], 1);
    PlayerTextDrawColor(playerid, SpawnHapp[playerid][17], -1);
    PlayerTextDrawSetShadow(playerid, SpawnHapp[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, SpawnHapp[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, SpawnHapp[playerid][17], 150);
    PlayerTextDrawFont(playerid, SpawnHapp[playerid][17], 2);
    PlayerTextDrawSetProportional(playerid, SpawnHapp[playerid][17], 1);
}

hook OnPlayerConnect(playerid)
{
    CreateSpawnTextdraws(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    for(new x = 0; x < 18; x++)
    {
        PlayerTextDrawDestroy(playerid, SpawnHapp[playerid][x]);
    }
    return 1;
}

ShowSpawnTextdraws(playerid)
{
    for(new x = 0; x < 18; x++)
    {
        PlayerTextDrawShow(playerid, SpawnHapp[playerid][x]);
        SelectTextDraw(playerid, COLOR_BLUE);
    }
    Info(playerid, "Gunakan "VERONA"'/cursor'"WHITE" jika cursor menghilang / textdraw tidak dapat ditekan");
    return 1;
}

HideSpawnTextdraws(playerid)
{
    for(new x = 0; x < 18; x++)
    {
        PlayerTextDrawHide(playerid, SpawnHapp[playerid][x]);
    }
    CancelSelectTextDraw(playerid);
    return 1;
}

hook OnClickDynPlayerTextDraw(playerid, PlayerText:textid)
{
    if(textid == SpawnHapp[playerid][3]) // Bandara
    {
        SetPVarInt(playerid, "SelectSpawn", 1); // Bandara
        SetPlayerCameraPos(playerid, 1665.321, -2295.758, 168.306);
        SetPlayerCameraLookAt(playerid, 1665.319, -2295.322, 163.325);
        InterpolateCameraPos(playerid, 1665.321, -2295.758, 168.306+150.0, 1665.321, -2295.758, 168.306, 2500, CAMERA_MOVE);
        PlayerPlaySound(playerid, 1054, 0, 0, 0);
    }
    if(textid == SpawnHapp[playerid][8]) // lasexit
    {
        SetPVarInt(playerid, "SelectSpawn", 2); //pelabuhan
        SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 0, 0, 0, 0, 0, 0);
        SpawnPlayer(playerid);
        Streamer_UpdateEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ]);
        SetPlayerVirtualWorldEx(playerid, AccountData[playerid][pWorld]);
        SetPlayerInteriorEx(playerid, AccountData[playerid][pInt]);
        PlayerPlaySound(playerid, 1054, 0, 0, 0);
    }
    if(textid == SpawnHapp[playerid][7]) //rusun
    {
        if(AccountData[playerid][pOwnedRusun] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memiliki rusun!");
        SetPVarInt(playerid, "SelectSpawn", 3); //rusun
        foreach(new id : Rusun)
        {
            if(RusunData[id][rusunOwnerID] == AccountData[playerid][pID])
            {
                SetPlayerCameraPos(playerid, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2] + 120.0);
                SetPlayerCameraLookAt(playerid, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2] + 90.0);
                InterpolateCameraPos(playerid, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2] + 200.0, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2] + 120.0, 2500, CAMERA_MOVE);
                PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
            }
        }
    }
    if(textid == SpawnHapp[playerid][6]) // rumah pribadi
    {
        if(AccountData[playerid][pOwnedHouse] == -1 && AccountData[playerid][pFriendHouseID] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki rumah!");
        SetPVarInt(playerid, "SelectSpawn", 4); // Rumah
        foreach(new hid : House)
        {
            if(HouseData[hid][hsOwnerID] == AccountData[playerid][pID] || AccountData[playerid][pFriendHouseID] == hid)
            {
                SetPlayerCameraPos(playerid, HouseData[hid][hsExtPos][0], HouseData[hid][hsExtPos][1], HouseData[hid][hsExtPos][2] + 120.0);
                SetPlayerCameraLookAt(playerid, HouseData[hid][hsExtPos][0], HouseData[hid][hsExtPos][1], HouseData[hid][hsExtPos][2] + 90.0);
                InterpolateCameraPos(playerid, HouseData[hid][hsExtPos][0], HouseData[hid][hsExtPos][1], HouseData[hid][hsExtPos][2] + 200.0, HouseData[hid][hsExtPos][0], HouseData[hid][hsExtPos][1], HouseData[hid][hsExtPos][2] + 120.0, 2500, CAMERA_MOVE);
                PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
            }
        }
    }
    if(textid == SpawnHapp[playerid][4]) //pelabuhan
    {
        SetPVarInt(playerid, "SelectSpawn", 5); //pelabuhan
        SetPlayerCameraPos(playerid, 2736.289, -2453.198, 164.569);
        SetPlayerCameraLookAt(playerid, 2736.725, -2453.193, 159.588);
        InterpolateCameraPos(playerid, 2736.289, -2453.198, 164.569+150.0, 2736.289, -2453.198, 164.569, 2500, CAMERA_MOVE);
        PlayerPlaySound(playerid, 1054, 0, 0, 0);
    }
    if(textid == SpawnHapp[playerid][5]) //karnaval
    {
        SetPVarInt(playerid, "SelectSpawn", 6); //carnaval
        SetPlayerCameraPos(playerid, 389.4873,-1782.5055,26.9447);
        SetPlayerCameraLookAt(playerid, 420.8488, -1777.6002, 25.2446);
        InterpolateCameraPos(playerid, 389.4873,-1782.5055,26.9447+150.0, 420.8488, -1777.6002, 25.2446, 2500, CAMERA_MOVE);
        PlayerPlaySound(playerid, 1054, 0, 0, 0);
    }
    if(textid == SpawnHapp[playerid][9]) // spawn
    {
        if(GetPVarInt(playerid, "SelectSpawn") == 1) // Bandara
        {
            new rand = random(sizeof(SpawnBandara));
            AccountData[playerid][pPosX] = SpawnBandara[rand][0];
            AccountData[playerid][pPosY] = SpawnBandara[rand][1];
            AccountData[playerid][pPosZ] = SpawnBandara[rand][2];
            AccountData[playerid][pPosA] = SpawnBandara[rand][3];
            SetPlayerInteriorEx(playerid, 0);
            SetPlayerVirtualWorldEx(playerid, 0);

            SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 8000);
            HideSpawnTextdraws(playerid);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil spawn di Bandara.");
        }
        else if(GetPVarInt(playerid, "SelectSpawn") == 2) // lastexit
        {
            AccountData[playerid][pPosX] = AccountData[playerid][pPosX];
			AccountData[playerid][pPosY] = AccountData[playerid][pPosY];
			AccountData[playerid][pPosZ] = AccountData[playerid][pPosZ];
			AccountData[playerid][pPosA] = AccountData[playerid][pPosA];

			if(AccountData[playerid][pInRusun] != -1)
			{
				SetPlayerInteriorEx(playerid, 1);
				SetPlayerVirtualWorldEx(playerid, AccountData[playerid][pInRusun]);
				SetPlayerPositionEx(playerid, 244.2521, 304.9150, 999.1484, 268.6741, 2500);
			}
				
			else if(AccountData[playerid][pInHouse] != -1) 
			{
				SetPlayerInteriorEx(playerid, HouseData[AccountData[playerid][pInHouse]][hsInt]);
				SetPlayerVirtualWorldEx(playerid, AccountData[playerid][pInHouse]);
				SetPlayerPositionEx(playerid, HouseData[AccountData[playerid][pInHouse]][hsIntPos][0], HouseData[AccountData[playerid][pInHouse]][hsIntPos][1], HouseData[AccountData[playerid][pInHouse]][hsIntPos][2], HouseData[AccountData[playerid][pInHouse]][hsIntPos][3], 2500);
			}
				
			else if(AccountData[playerid][pInDoor] != -1)
			{
				SetPlayerInteriorEx(playerid, DoorData[AccountData[playerid][pInDoor]][dIntint]);
				SetPlayerVirtualWorldEx(playerid, DoorData[AccountData[playerid][pInDoor]][dIntvw]);
				SetPlayerPositionEx(playerid, DoorData[AccountData[playerid][pInDoor]][dIntposX], DoorData[AccountData[playerid][pInDoor]][dIntposY], DoorData[AccountData[playerid][pInDoor]][dIntposZ], DoorData[AccountData[playerid][pInDoor]][dIntposA], 2500);
			}

			else if(AccountData[playerid][pInFamily] != -1)
			{
				SetPlayerInteriorEx(playerid, FamData[AccountData[playerid][pInFamily]][famInterior]);
				SetPlayerVirtualWorldEx(playerid, AccountData[playerid][pInFamily]);
				SetPlayerPositionEx(playerid, FamData[AccountData[playerid][pInFamily]][famIntPos][0], FamData[AccountData[playerid][pInFamily]][famIntPos][1], FamData[AccountData[playerid][pInFamily]][famIntPos][2], FamData[AccountData[playerid][pInFamily]][famIntPos][3], 2500);
			}

			else
			{
				SetPlayerVirtualWorldEx(playerid, AccountData[playerid][pWorld]);
				SetPlayerInteriorEx(playerid, AccountData[playerid][pInt]);
			}
			SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 6000);
            HideSpawnTextdraws(playerid);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil spawn di Lokasi Terakhir.");
        }
        else if(GetPVarInt(playerid, "SelectSpawn") == 3) // Rusun Pribadi
        {
            if(AccountData[playerid][pOwnedRusun] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memiliki rusun!");
            foreach(new rsid : Rusun)
            {
                if(RusunData[rsid][rusunOwnerID] == AccountData[playerid][pID])
                {
                    AccountData[playerid][pPosX] =  RusunData[rsid][rusunExtPos][0];
                    AccountData[playerid][pPosY] =  RusunData[rsid][rusunExtPos][1];
                    AccountData[playerid][pPosZ] =  RusunData[rsid][rusunExtPos][2];
                    AccountData[playerid][pPosA] =  RusunData[rsid][rusunExtPos][3];
                    SetPlayerInteriorEx(playerid, 0);
                    SetPlayerVirtualWorldEx(playerid, 0);

                    SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 8000);
                    HideSpawnTextdraws(playerid);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil spawn di Rusun Pribadi.");
                }
            }
        }
        else if(GetPVarInt(playerid, "SelectSpawn") == 4) // Rumah Pribadi
        {
            if(AccountData[playerid][pOwnedHouse] == -1 && AccountData[playerid][pFriendHouseID] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki rumah!");
            foreach(new hid : House)
            {
                if(HouseData[hid][hsOwnerID] == AccountData[playerid][pID] || AccountData[playerid][pFriendHouseID] == hid)
                {
                    AccountData[playerid][pPosX] =  HouseData[hid][hsExtPos][0];
                    AccountData[playerid][pPosY] =  HouseData[hid][hsExtPos][1];
                    AccountData[playerid][pPosZ] =  HouseData[hid][hsExtPos][2];
                    AccountData[playerid][pPosA] =  HouseData[hid][hsExtPos][3];
                    SetPlayerInteriorEx(playerid, 0);
                    SetPlayerVirtualWorldEx(playerid, 0);

                    SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 8000);
                    HideSpawnTextdraws(playerid);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil spawn di Rumah Pribadi.");
                }
            }
        }
        else if(GetPVarInt(playerid, "SelectSpawn") == 5) // pelabuhan
        {
            new rand = random(sizeof(SpawnPelabuhan));
            AccountData[playerid][pPosX] = SpawnPelabuhan[rand][0];
            AccountData[playerid][pPosY] = SpawnPelabuhan[rand][1];
            AccountData[playerid][pPosZ] = SpawnPelabuhan[rand][2];
            AccountData[playerid][pPosA] = SpawnPelabuhan[rand][3];
            SetPlayerInteriorEx(playerid, 0);
            SetPlayerVirtualWorldEx(playerid, 0);

            SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 8000);
            HideSpawnTextdraws(playerid);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil spawn di Pelabuhan Merak.");
        }
        else if(GetPVarInt(playerid, "SelectSpawn") == 6) //carnaval
        {
            AccountData[playerid][pPosX] = 375.5105;
			AccountData[playerid][pPosY] = -1899.5723;
			AccountData[playerid][pPosZ] = 7.8359;
			AccountData[playerid][pPosA] = 88.7574;
			SetPlayerInteriorEx(playerid, 0);
			SetPlayerVirtualWorldEx(playerid, 0);

			SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 6000);
            HideSpawnTextdraws(playerid);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil spawn di Carnaval.");
        }
        else 
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum menetapkan lokasi spawn!");
        }
        SetPVarInt(playerid, "SelectSpawn", 0);
        AccountData[playerid][playerClickSpawn] = 1;
        //SetPVarInt(playerid, "SpawnExpired", 1);
    }
    return 1;
}