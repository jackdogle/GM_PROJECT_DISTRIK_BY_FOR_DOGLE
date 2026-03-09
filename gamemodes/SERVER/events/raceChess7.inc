///---[Racing Street Systems]--
//Creator by: Chess7
//Store: Juragan Store

new PlayerText: BalapanTD[MAX_PLAYERS][25];

stock bool:AllRacersReady()
{
    new readyCount = 0;
    for (new i = 0; i < gRaceTotalPlayers; i++)
    {
        if (gRacePlayerReady[gRacePlayers[i]] == true)
            readyCount++;
    }
    return (readyCount == gRaceTotalPlayers);
}

CMD:balap(playerid, params[])
{
    if(gAdminRaceActive) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak bisa membuat race player selama event balap admin berlangsung!");
    if(!IsPlayerInRangeOfPoint(playerid, 150.0, -858.9254, -130.1109, 60.0591)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di lembah!");
    if(gRaceStarted) return ShowTDN(playerid, NOTIFICATION_ERROR, "Race sudah berlangsung!");

    for(new i = 0; i < sizeof(gRacePlayers); i++)
    {
        gRacePlayers[i] = INVALID_PLAYER_ID;
    }
    ShowPlayerDialog(playerid, DIALOG_RACE_PLAYER_COUNT, DIALOG_STYLE_LIST, "Pilih jumlah pemain", "2 Pemain\n4 Pemain\n6 Pemain", "Pilih", "Batal");
    return 1;
}

CMD:joinrace(playerid, params[])
{
    if(!IsPlayerInRangeOfPoint(playerid, 150.0, -858.9254,-130.1109,60.0591)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di lembah!");
    if(gRaceStarted) return ShowTDN(playerid, NOTIFICATION_ERROR, "Race sudah berlangsung!");

    new bool:invited = false;
    for(new i = 0; i < sizeof(gRacePlayers); i++)
    {
        if(gRacePlayers[i] == playerid)
        {
            invited = true;
            break;
        }
    }
    if(!invited) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak menerima undangan race!");

    ShowRaceVehicleList(playerid);
    return 1;
}

forward RaceCountdown();
public RaceCountdown()
{
    raceCountdown--;
    for (new i = 0; i < gRaceTotalPlayers; i++)
    {
        new id = gRacePlayers[i];
        if (!IsPlayerConnected(id)) continue;

        if (raceCountdown > 0)
        {
            new msg[16];
            format(msg, sizeof(msg), "~y~%d", raceCountdown);
            GameTextForPlayer(id, msg, 1000, 3);
        }
        else if (raceCountdown == 0)
        {
            GameTextForPlayer(id, "~g~GO!", 1000, 3);
            TogglePlayerControllable(id, true);
            DisableRemoteVehicleCollisions(id, true);
            gInRaceNow[id] = true;

            gRacePlayerData[id][rCheckpoint] = 0;
            gRacePlayerData[id][rLap] = 1;
            gRacePlayerData[id][rFinished] = false;

            SetPlayerRaceCheckpoint(id, 1, gRaceCP[0][0], gRaceCP[0][1], gRaceCP[0][2], gRaceCP[1][0], gRaceCP[1][1], gRaceCP[1][2], 10.0);
        }
    }
    if (raceCountdown <= 0)
    {
        KillTimer(countdownTimer);
        countdownTimer = -1;
        gRaceStarted = true;
        for(new i = 0; i < MAX_PLAYERS; i++)
            rLastCPTime[i] = 0;
    }
    return 1;
}

stock ResetRacePlayer()
{
    gRaceStarted = false;
    gRaceTotalPlayers = 0;
    gRaceLapCount = 0;
    gRaceFinishCount = 0;
    raceCountdown = 5;
    raceWinnerDeclared = false;
    for(new i = 0; i < MAX_RACE_PLAYERS; i++)
    {
        gRacePlayers[i] = INVALID_PLAYER_ID;
        gRacePlayerReady[i] = false;

        gRacePlayerData[i][rCheckpoint] = 0;
        gRacePlayerData[i][rLap] = 0;
        gRacePlayerData[i][rFinished] = false;
        TogglePlayerControllable(i, true);
        DisableRemoteVehicleCollisions(i, false);
        DisablePlayerRaceCheckpoint(i);
        gInRaceNow[i] = false;
        ShowTDBalapan(i, false);
        rLastCPTime[i] = 0;
    }
    gRaceFinishRank[0] = INVALID_PLAYER_ID;
    gRaceFinishRank[1] = INVALID_PLAYER_ID;
    gRaceFinishRank[2] = INVALID_PLAYER_ID;
}

stock ResetRaceAdm()
{
    gAdminRaceActive = false;
    gAdminRaceTotalPlayers = 0;
    gRaceLapCount = 0;
    gRaceFinishCount = 0;
    raceCountdown = 5;
    raceWinnerDeclared = false;

    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        gAdminRacePlayers[i] = INVALID_PLAYER_ID;
        gRacePlayerReady[i] = false;
        gRacePlayerData[i][rCheckpoint] = 0;
        gRacePlayerData[i][rLap] = 0;
        gRacePlayerData[i][rFinished] = false;
        gInRaceNow[i] = false;
        ShowTDBalapan(i, false);
        rLastCPTime[i] = 0;

        if(gRacePlayerData[i][rVehicleAdm] != INVALID_VEHICLE_ID)
        {
            SetPlayerPos(i, gRaceStartPos[i][0], gRaceStartPos[i][1], gRaceStartPos[i][2]);
            SetPlayerFacingAngle(i, gRaceStartPos[i][3]);
            TogglePlayerControllable(i, true);
            DisableRemoteVehicleCollisions(i, false);

            DestroyVehicle(gRacePlayerData[i][rVehicleAdm]);
            gRacePlayerData[i][rVehicleAdm] = INVALID_VEHICLE_ID;
        }
        DisablePlayerRaceCheckpoint(i);
    }
    for(new v = 0; v < MAX_VEHICLES; v++)
    {
        gRaceVehicleAdm[v] = false;
    }
    gRaceFinishRank[0] = INVALID_PLAYER_ID;
    gRaceFinishRank[1] = INVALID_PLAYER_ID;
    gRaceFinishRank[2] = INVALID_PLAYER_ID;
}

CMD:resetbalap(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

    ResetRaceAdm();
    ResetRacePlayer();
    SendClientMessageToAllEx(-1, ""RED_E"[BALAPAN]: "WHITE_E"Event balap telah direset oleh admin %s.", AccountData[playerid][pAdminname]);
    return 1;
}

stock ShowRaceVehicleList(playerid)
{
	if(!GetOwnedVeh(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki kendaraan!");

	new count = GetOwnedVeh(playerid);
	static 
		vid,
		list[512],
		CMDString[4056],
		Status1[512],
		StatusSpawn[512],
		PlateStatus[128]
	;

	CMDString = "";
	strcat(CMDString, "VID\tModel(Database ID)\tPlate(Masa Berlaku)\tRental/Status/\n", sizeof(CMDString));
	Loop(itt, (count + 1), 1)
	{
		vid = ReturnPlayerVehID(playerid, itt);

		if(PlayerVehicle[vid][pVehPlateOwn]) {
			format(PlateStatus, sizeof(PlateStatus), "- ("DARKRED"Permanent"WHITE")");
		} else {
			format(PlateStatus, sizeof(PlateStatus), " (Kosong)");
		}

		if(PlayerVehicle[vid][pVehPhysic] == INVALID_VEHICLE_ID) {
			format(StatusSpawn, sizeof(StatusSpawn), "[Despawned]");
		} else {
			format(StatusSpawn, sizeof(StatusSpawn), "%d", PlayerVehicle[vid][pVehPhysic]);
		}

		if(PlayerVehicle[vid][pVehRental] > 0 && PlayerVehicle[vid][pVehRentTime] != 0) {
			new currentTime = PlayerVehicle[vid][pVehRentTime] - gettime();
			new hours = (currentTime % 86400) / 3600;
			new minutes = (currentTime % 3600) / 60;
			new seconds = currentTime % 60;

			format(Status1, sizeof(Status1), "%d Jam %d Menit %d Detik", hours, minutes, seconds);
		} else {
			format(Status1, sizeof(Status1), ""GREEN"Dimiliki");
		}

		if(itt == count)
		{
			format(list, sizeof(list), "%s\t%s [%d]\t%s %s\t%s"WHITE"/%s/\n", StatusSpawn, GetVehicleModelName(PlayerVehicle[vid][pVehModelID]), PlayerVehicle[vid][pVehID], PlayerVehicle[vid][pVehPlate], PlateStatus, Status1, GetMyVehicleStatus(vid, "Spawned"));
		}
		else format(list, sizeof(list), "%s\t%s [%d]\t%s %s\t%s"WHITE"/%s/\n", StatusSpawn, GetVehicleModelName(PlayerVehicle[vid][pVehModelID]), PlayerVehicle[vid][pVehID], PlayerVehicle[vid][pVehPlate], PlateStatus, Status1, GetMyVehicleStatus(vid, "Spawned"));
		strcat(CMDString, list);
	}
	ShowPlayerDialog(playerid, DIALOG_RACE_VEH_LIST, DIALOG_STYLE_TABLIST_HEADERS, ""GREEN"Pilih Kendaraan Balap", CMDString, "Pilih", "Batal");
    return 1;
}

stock GetRaceSlotForPlayer(playerid)
{
    for (new i = 0; i < gRaceTotalPlayers; i++)
    {
        if (gRacePlayers[i] == playerid)
            return i;
    }
    return -1;
}


//====[EVENT BALAPAN RACE KHUSUS ADMIN]====

CMD:createrace(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

    if(gAdminRaceActive) return ShowTDN(playerid, NOTIFICATION_ERROR, "Event balap sedang berlangsung!");

    ShowPlayerDialog(playerid, DIALOG_ADMIN_RACE_LAP_COUNT, DIALOG_STYLE_LIST, "Jumlah Lap Balapan", "1 Lap\n2 Lap\n3 Lap", "Pilih", "Batal");
    return 1;
}

CMD:joinbalap(playerid, params[])
{
    if(!gAdminRaceActive) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada event balap yang aktif!");
    if(gAdminRaceTotalPlayers >= MAX_PLAYERS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot balapan penuh!");

    for(new i = 0; i < gAdminRaceTotalPlayers; i++)
    {
        if(gAdminRacePlayers[i] == playerid)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu sudah bergabung dalam balapan.");
    }
    new Float:x, Float:y, Float:z, Float:a;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid,a);
    gRaceStartPos[playerid][0] = x;
    gRaceStartPos[playerid][1] = y;
    gRaceStartPos[playerid][2] = z;
    gRaceStartPos[playerid][3] = a;

    new vehicleid = CreateVehicle(gAdminRaceVehicleModel, -858.9254,-130.1109,60.0591,284.3603, RandomEx(1, 100), RandomEx(1, 100), 60000);
    PutPlayerInVehicle(playerid, vehicleid, 0);
    TogglePlayerControllable(playerid, false);
    DisableRemoteVehicleCollisions(playerid, true);
    SwitchVehicleEngine(vehicleid, true);
    SetVehicleHealth(vehicleid, 5000);
    VehicleCore[vehicleid][vCoreFuel]  = 100;
    gRaceVehicleAdm[vehicleid] = true;
    gInRaceNow[playerid] = true;

    gRacePlayerData[playerid][rVehicleAdm] = vehicleid;
    gAdminRacePlayers[gAdminRaceTotalPlayers++] = playerid;

    SendClientMessage(playerid, -1, ""RED_E"[WARNING!]: "WHITE_E"Kamu telah bergabung dalam event balapan. Tunggu instruksi admin!");
    return 1;
}

CMD:mulaibalap(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

    if(!gAdminRaceActive) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada event balapan aktif.");

    for(new i = 0; i < gAdminRaceTotalPlayers; i++)
    {
        new id = gAdminRacePlayers[i];
        GameTextForPlayer(id, "~r~Countdown~n~Dimulai!", 2000, 3);
        ShowTDBalapan(id, true);

        PlayerTextDrawSetString(id, BalapanTD[id][11], "-");
        PlayerTextDrawSetString(id, BalapanTD[id][18], "-");
        PlayerTextDrawSetString(id, BalapanTD[id][19], "-");
        PlayerTextDrawSetString(id, BalapanTD[id][20], "-");

        PlayerTextDrawSetString(id, BalapanTD[id][12], "0/%d", gAdminRaceLapCount);
        PlayerTextDrawSetString(id, BalapanTD[id][21], "0/%d", gAdminRaceLapCount);
        PlayerTextDrawSetString(id, BalapanTD[id][22], "0/%d", gAdminRaceLapCount);
        PlayerTextDrawSetString(id, BalapanTD[id][23], "0/%d", gAdminRaceLapCount);
    }
    raceCountdown = 5;
    countdownTimer = SetTimer("RaceCountdown_Admin", 1000, true);
    return 1;
}

forward RaceCountdown_Admin();
public RaceCountdown_Admin()
{
    raceCountdown--;
    for (new i = 0; i < gAdminRaceTotalPlayers; i++)
    {
        new id = gAdminRacePlayers[i];
        if (!IsPlayerConnected(id)) continue;

        if (raceCountdown > 0)
        {
            new msg[16];
            format(msg, sizeof(msg), "~y~%d", raceCountdown);
            GameTextForPlayer(id, msg, 1000, 3);
        }
        else if (raceCountdown == 0)
        {
            GameTextForPlayer(id, "~g~GO!", 1000, 3);
            TogglePlayerControllable(id, true);
            DisableRemoteVehicleCollisions(id, true);

            gRacePlayerData[id][rCheckpoint] = 0;
            gRacePlayerData[id][rLap] = 1;
            gRacePlayerData[id][rFinished] = false;

            SetPlayerRaceCheckpoint(id, 1, gRaceCP[0][0], gRaceCP[0][1], gRaceCP[0][2], gRaceCP[1][0], gRaceCP[1][1], gRaceCP[1][2], 10.0);
        }
    }
    if (raceCountdown <= 0)
    {
        KillTimer(countdownTimer);
        countdownTimer = -1;
        gAdminRaceActive = true;
        for(new i = 0; i < MAX_PLAYERS; i++)
            rLastCPTime[i] = 0;
    }
    return 1;
}

stock IsPlayerInRace(playerid)
{
    for(new i = 0; i < gRaceTotalPlayers; i++)
    {
        if(gRacePlayers[i] == playerid)
            return 1;
    }
    for(new i = 0; i < gAdminRaceTotalPlayers; i++)
    {
        if(gAdminRacePlayers[i] == playerid)
            return 1;
    }
    return 0;
}


hook OnGameModeInit() 
{
    for(new i = 0; i < MAX_RACE_PLAYERS; i++)
        gRacePlayers[i] = INVALID_PLAYER_ID;
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    if(gInRaceNow[playerid])
    {
        SetPlayerPos(playerid, gRaceStartPos[playerid][0], gRaceStartPos[playerid][1], gRaceStartPos[playerid][2]);
        SetPlayerFacingAngle(playerid, gRaceStartPos[playerid][3]);
        gInRaceNow[playerid] = false;
    }
    return 1;
}

// hook OnPlayerEnterRaceCP(playerid)
// {
//     DisablePlayerRaceCheckpoint(playerid);
// 	if(gRaceStarted && !gRacePlayerData[playerid][rFinished]) // BALAPAN PLAYER BIASA
// 	{
// 		new cp = gRacePlayerData[playerid][rCheckpoint];
// 		cp++;
// 		if(cp >= MAX_RACE_CP)
// 		{
// 			cp = 0;
// 			gRacePlayerData[playerid][rLap]++;
// 			if(gRacePlayerData[playerid][rLap] > gRaceLapCount)
// 			{
// 				gRacePlayerData[playerid][rFinished] = true;
// 				DisablePlayerRaceCheckpoint(playerid);

// 				if(gRaceFinishCount < 3)
// 				{
// 					gRaceFinishRank[gRaceFinishCount] = playerid;
// 					gRaceFinishCount++;

// 					new message[128];
// 					switch(gRaceFinishCount)
// 					{
// 						case 1: format(message, sizeof(message), ""YELLOW_E"[BALAPAN]: %s "WHITE_E"berhasil finis balapan dengan posisi "YELLOW_E"pertama!", ReturnName(playerid));
// 						case 2: format(message, sizeof(message), ""YELLOW_E"[BALAPAN]: %s "WHITE_E"berhasil finis balapan dengan posisi "YELLOW_E"kedua!", ReturnName(playerid));
// 						case 3: format(message, sizeof(message), ""YELLOW_E"[BALAPAN]: %s "WHITE_E"berhasil finis balapan dengan posisi "YELLOW_E"ketiga!", ReturnName(playerid));
// 					}
// 					SendClientMessageToAll(-1, message);
// 				}
// 				if(!raceWinnerDeclared)
// 				{
// 					SendClientMessage(playerid, -1, ""YELLOW_E"[INFO]: "WHITE_E"Anda berhasil menang dalam balapan!");
// 					raceWinnerDeclared = true;
// 				}
// 				else SendClientMessage(playerid, -1, ""RED_E"[INFO]: "WHITE_E"Anda telah menyelesaikan balapan!");

// 				new finishedCount = 0;
// 				for(new i = 0; i < gRaceTotalPlayers; i++)
// 					if(gRacePlayerData[gRacePlayers[i]][rFinished]) finishedCount++;

// 				if(finishedCount >= gRaceTotalPlayers && gRaceTotalPlayers > 0)
// 				{
// 					ResetRacePlayer();
// 					raceWinnerDeclared = false;
// 					gRaceStarted = false;
// 				}
// 				return 1;
// 			}
// 		}
// 		gRacePlayerData[playerid][rCheckpoint] = cp;
//         rLastCPTime[playerid] = GetTickCount();
// 		new next = cp + 1;
// 		if(next >= MAX_RACE_CP) next = 0;
// 		SetPlayerRaceCheckpoint(playerid, 1, gRaceCP[cp][0], gRaceCP[cp][1], gRaceCP[cp][2], gRaceCP[next][0], gRaceCP[next][1], gRaceCP[next][2], 10.0);
//         UpdateRaceTDAll();
// 		return 1;
// 	}
// 	else if(gAdminRaceActive && !gRacePlayerData[playerid][rFinished]) // BALAPAN EVENT RACE
// 	{
// 		new cp = gRacePlayerData[playerid][rCheckpoint];
// 		cp++;
// 		if(cp >= MAX_RACE_CP)
// 		{
// 			cp = 0;
// 			gRacePlayerData[playerid][rLap]++;

// 			if(gRacePlayerData[playerid][rLap] > gAdminRaceLapCount)
// 			{
// 				gRacePlayerData[playerid][rFinished] = true;
// 				DisablePlayerRaceCheckpoint(playerid);

// 				if(gRaceFinishCount < 3)
// 				{
// 					gRaceFinishRank[gRaceFinishCount] = playerid;
// 					gRaceFinishCount++;

// 					new message[128];
// 					switch(gRaceFinishCount)
// 					{
// 						case 1: format(message, sizeof(message), ""YELLOW_E"[EVENT]: %s "WHITE_E"finish pertama!", ReturnName(playerid));
// 						case 2: format(message, sizeof(message), ""YELLOW_E"[EVENT]: %s "WHITE_E"finish kedua!", ReturnName(playerid));
// 						case 3: format(message, sizeof(message), ""YELLOW_E"[EVENT]: %s "WHITE_E"finish ketiga!", ReturnName(playerid));
// 					}
// 					SendClientMessageToAll(-1, message);
// 				}
// 				if(!raceWinnerDeclared)
// 				{
// 					SendClientMessage(playerid, -1, ""YELLOW_E"[INFO]: "WHITE_E"Anda berhasil menang dalam event balapan!");
// 					raceWinnerDeclared = true;
// 				}
// 				else SendClientMessage(playerid, -1, ""RED_E"[INFO]: "WHITE_E"Anda telah menyelesaikan balapan event!");

// 				new AdmfinishedCount = 0;
// 				for(new i = 0; i < gAdminRaceTotalPlayers; i++)
// 					if(gRacePlayerData[gAdminRacePlayers[i]][rFinished]) AdmfinishedCount++;

// 				if(AdmfinishedCount >= gAdminRaceTotalPlayers && gAdminRaceTotalPlayers > 0)
// 				{
// 					ResetRaceAdm();
// 					raceWinnerDeclared = false;
// 					gAdminRaceActive = false;
// 					SendClientMessageToAll(-1, ""YELLOW_E"[EVENT RACE]: "WHITE_E"Event balap selesai, semua kendaraan event akan dihapus!");
// 				}
// 				return 1;
// 			}
// 		}
// 		gRacePlayerData[playerid][rCheckpoint] = cp;
//         rLastCPTime[playerid] = GetTickCount();
// 		new next = cp + 1;
// 		if(next >= MAX_RACE_CP) next = 0;
// 		SetPlayerRaceCheckpoint(playerid, 1, gRaceCP[cp][0], gRaceCP[cp][1], gRaceCP[cp][2], gRaceCP[next][0], gRaceCP[next][1], gRaceCP[next][2], 10.0);
//         UpdateRaceTDAdmAll();
// 		return 1;
// 	}
// 	return 1; 
// }

stock UpdateRaceTDAdmAll()
{
    new sorted[MAX_PLAYERS], count = 0;

    // Masukin semua peserta aktif ke array
    for(new i = 0; i < gAdminRaceTotalPlayers; i++)
    {
        new pid = gAdminRacePlayers[i];
        if(!gRacePlayerData[pid][rFinished])
            sorted[count++] = pid;
    }

    // Sorting berdasarkan lap, checkpoint, lalu waktu tempuh
    for(new x = 0; x < count - 1; x++)
    {
        for(new y = x + 1; y < count; y++)
        {
            if(
                gRacePlayerData[sorted[y]][rLap] > gRacePlayerData[sorted[x]][rLap] ||
                (
                    gRacePlayerData[sorted[y]][rLap] == gRacePlayerData[sorted[x]][rLap] &&
                    gRacePlayerData[sorted[y]][rCheckpoint] > gRacePlayerData[sorted[x]][rCheckpoint]
                ) ||
                (
                    gRacePlayerData[sorted[y]][rLap] == gRacePlayerData[sorted[x]][rLap] &&
                    gRacePlayerData[sorted[y]][rCheckpoint] == gRacePlayerData[sorted[x]][rCheckpoint] &&
                    rLastCPTime[sorted[y]] < rLastCPTime[sorted[x]]
                )
            )
            {
                new temp = sorted[x];
                sorted[x] = sorted[y];
                sorted[y] = temp;
            }
        }
    }

    // Update TD untuk semua pemain
    for(new i = 0; i < gAdminRaceTotalPlayers; i++)
    {
        new pid = gAdminRacePlayers[i];
        new str[32];

        // Posisi 1
        if(count >= 1)
        {
            PlayerTextDrawSetString(pid, BalapanTD[pid][11], "%s", ReturnName(sorted[0]));
            PlayerTextDrawShow(pid, BalapanTD[pid][11]);
            format(str, sizeof(str), "%d/%d", gRacePlayerData[sorted[0]][rLap], gAdminRaceLapCount);
            PlayerTextDrawSetString(pid, BalapanTD[pid][12], str);
            PlayerTextDrawShow(pid, BalapanTD[pid][12]);
        }

        // Posisi 2
        if(count >= 2)
        {
            PlayerTextDrawSetString(pid, BalapanTD[pid][18], "%s", ReturnName(sorted[1]));
            PlayerTextDrawShow(pid, BalapanTD[pid][18]);
            format(str, sizeof(str), "%d/%d", gRacePlayerData[sorted[1]][rLap], gAdminRaceLapCount);
            PlayerTextDrawSetString(pid, BalapanTD[pid][21], str);
            PlayerTextDrawShow(pid, BalapanTD[pid][21]);
        }

        // Posisi 3
        if(count >= 3)
        {
            PlayerTextDrawSetString(pid, BalapanTD[pid][19], "%s", ReturnName(sorted[2]));
            PlayerTextDrawShow(pid, BalapanTD[pid][19]);
            format(str, sizeof(str), "%d/%d", gRacePlayerData[sorted[2]][rLap], gAdminRaceLapCount);
            PlayerTextDrawSetString(pid, BalapanTD[pid][22], str);
            PlayerTextDrawShow(pid, BalapanTD[pid][22]);
        }

        // Posisi 4
        if(count >= 4)
        {
            PlayerTextDrawSetString(pid, BalapanTD[pid][20], "%s", ReturnName(sorted[3]));
            PlayerTextDrawShow(pid, BalapanTD[pid][20]);
            format(str, sizeof(str), "%d/%d", gRacePlayerData[sorted[3]][rLap], gAdminRaceLapCount);
            PlayerTextDrawSetString(pid, BalapanTD[pid][23], str);
            PlayerTextDrawShow(pid, BalapanTD[pid][23]);
        }
    }
}

stock UpdateRaceTDAll()
{
    new sorted[MAX_PLAYERS], count = 0;

    // Masukin semua peserta aktif ke array
    for(new i = 0; i < gRaceTotalPlayers; i++)
    {
        new pid = gRacePlayers[i];
        if(!gRacePlayerData[pid][rFinished])
            sorted[count++] = pid;
    }

    // Sorting berdasarkan lap, checkpoint, lalu waktu tempuh checkpoint terakhir
    for(new x = 0; x < count - 1; x++)
    {
        for(new y = x + 1; y < count; y++)
        {
            if(
                gRacePlayerData[sorted[y]][rLap] > gRacePlayerData[sorted[x]][rLap] ||
                (
                    gRacePlayerData[sorted[y]][rLap] == gRacePlayerData[sorted[x]][rLap] &&
                    gRacePlayerData[sorted[y]][rCheckpoint] > gRacePlayerData[sorted[x]][rCheckpoint]
                ) ||
                (
                    gRacePlayerData[sorted[y]][rLap] == gRacePlayerData[sorted[x]][rLap] &&
                    gRacePlayerData[sorted[y]][rCheckpoint] == gRacePlayerData[sorted[x]][rCheckpoint] &&
                    rLastCPTime[sorted[y]] < rLastCPTime[sorted[x]]
                )
            )
            {
                new temp = sorted[x];
                sorted[x] = sorted[y];
                sorted[y] = temp;
            }
        }
    }

    // Update TD untuk semua pemain
    for(new i = 0; i < gRaceTotalPlayers; i++)
    {
        new pid = gRacePlayers[i];
        new str[32];

        // Posisi 1
        if(count >= 1)
        {
            PlayerTextDrawSetString(pid, BalapanTD[pid][11], "%s", ReturnName(sorted[0]));
            PlayerTextDrawShow(pid, BalapanTD[pid][11]);
            format(str, sizeof(str), "%d/%d", gRacePlayerData[sorted[0]][rLap], gRaceLapCount);
            PlayerTextDrawSetString(pid, BalapanTD[pid][12], str);
            PlayerTextDrawShow(pid, BalapanTD[pid][12]);
        }

        // Posisi 2
        if(count >= 2)
        {
            PlayerTextDrawSetString(pid, BalapanTD[pid][18], "%s", ReturnName(sorted[1]));
            PlayerTextDrawShow(pid, BalapanTD[pid][18]);
            format(str, sizeof(str), "%d/%d", gRacePlayerData[sorted[1]][rLap], gRaceLapCount);
            PlayerTextDrawSetString(pid, BalapanTD[pid][21], str);
            PlayerTextDrawShow(pid, BalapanTD[pid][21]);
        }

        // Posisi 3
        if(count >= 3)
        {
            PlayerTextDrawSetString(pid, BalapanTD[pid][19], "%s", ReturnName(sorted[2]));
            PlayerTextDrawShow(pid, BalapanTD[pid][19]);
            format(str, sizeof(str), "%d/%d", gRacePlayerData[sorted[2]][rLap], gRaceLapCount);
            PlayerTextDrawSetString(pid, BalapanTD[pid][22], str);
            PlayerTextDrawShow(pid, BalapanTD[pid][22]);
        }

        // Posisi 4
        if(count >= 4)
        {
            PlayerTextDrawSetString(pid, BalapanTD[pid][20], "%s", ReturnName(sorted[3]));
            PlayerTextDrawShow(pid, BalapanTD[pid][20]);
            format(str, sizeof(str), "%d/%d", gRacePlayerData[sorted[3]][rLap], gRaceLapCount);
            PlayerTextDrawSetString(pid, BalapanTD[pid][23], str);
            PlayerTextDrawShow(pid, BalapanTD[pid][23]);
        }
    }
}

CreateTDRacing(playerid)
{
    BalapanTD[playerid][0] = CreatePlayerTextDraw(playerid, 495.000, 145.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, BalapanTD[playerid][0], 126.000, 90.000);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][0], 512819199);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][0], 1);

    BalapanTD[playerid][1] = CreatePlayerTextDraw(playerid, 490.000, 127.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, BalapanTD[playerid][1], 33.000, 35.000);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][1], 512819199);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][1], 1);

    BalapanTD[playerid][2] = CreatePlayerTextDraw(playerid, 593.000, 127.000, "LD_BEAT:chit");
    PlayerTextDrawTextSize(playerid, BalapanTD[playerid][2], 33.000, 35.000);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][2], 512819199);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][2], 1);

    BalapanTD[playerid][3] = CreatePlayerTextDraw(playerid, 505.000, 132.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, BalapanTD[playerid][3], 104.000, 83.000);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][3], 512819199);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][3], 255);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][3], 1);

    BalapanTD[playerid][4] = CreatePlayerTextDraw(playerid, 495.000, 162.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, BalapanTD[playerid][4], 126.000, 1.000);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][4], 10495);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][4], 255);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][4], 1);

    BalapanTD[playerid][5] = CreatePlayerTextDraw(playerid, 495.000, 182.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, BalapanTD[playerid][5], 126.000, 1.000);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][5], 10495);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][5], 255);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][5], 1);

    BalapanTD[playerid][6] = CreatePlayerTextDraw(playerid, 495.000, 200.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, BalapanTD[playerid][6], 126.000, 1.000);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][6], 10495);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][6], 255);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][6], 1);

    BalapanTD[playerid][7] = CreatePlayerTextDraw(playerid, 495.000, 218.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, BalapanTD[playerid][7], 126.000, 1.000);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][7], 10495);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][7], 255);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][7], 1);

    BalapanTD[playerid][8] = CreatePlayerTextDraw(playerid, 510.000, 162.000, "LD_SPAC:white");
    PlayerTextDrawTextSize(playerid, BalapanTD[playerid][8], 1.000, 73.000);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][8], 10495);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][8], 255);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][8], 1);

    BalapanTD[playerid][9] = CreatePlayerTextDraw(playerid, 502.000, 149.000, "No.");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][9], 0.160, 0.899);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][9], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][9], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][9], 1);

    BalapanTD[playerid][10] = CreatePlayerTextDraw(playerid, 538.000, 149.000, "Name:");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][10], 0.160, 0.899);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][10], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][10], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][10], 1);

    BalapanTD[playerid][11] = CreatePlayerTextDraw(playerid, 541.000, 167.000, "Ronnie Varquez");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][11], 0.160, 0.899);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][11], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][11], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][11], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][11], 1);

    BalapanTD[playerid][12] = CreatePlayerTextDraw(playerid, 608.000, 166.000, "1/3");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][12], 0.160, 0.899);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][12], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][12], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][12], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][12], 1);

    BalapanTD[playerid][13] = CreatePlayerTextDraw(playerid, 608.000, 149.000, "Lap:");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][13], 0.160, 0.899);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][13], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][13], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][13], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][13], 1);

    BalapanTD[playerid][14] = CreatePlayerTextDraw(playerid, 503.000, 165.000, "1.");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][14], 0.280, 1.199);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][14], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][14], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][14], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][14], 3);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][14], 1);

    BalapanTD[playerid][15] = CreatePlayerTextDraw(playerid, 503.000, 183.000, "2.");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][15], 0.280, 1.199);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][15], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][15], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][15], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][15], 3);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][15], 1);

    BalapanTD[playerid][16] = CreatePlayerTextDraw(playerid, 503.000, 202.000, "3.");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][16], 0.280, 1.199);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][16], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][16], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][16], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][16], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][16], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][16], 3);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][16], 1);

    BalapanTD[playerid][17] = CreatePlayerTextDraw(playerid, 503.000, 220.000, "4.");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][17], 0.280, 1.199);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][17], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][17], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][17], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][17], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][17], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][17], 3);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][17], 1);

    BalapanTD[playerid][18] = CreatePlayerTextDraw(playerid, 541.000, 186.000, "Ronnie Varquez");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][18], 0.160, 0.899);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][18], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][18], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][18], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][18], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][18], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][18], 1);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][18], 1);

    BalapanTD[playerid][19] = CreatePlayerTextDraw(playerid, 541.000, 204.000, "Ronnie Varquez");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][19], 0.160, 0.899);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][19], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][19], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][19], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][19], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][19], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][19], 1);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][19], 1);

    BalapanTD[playerid][20] = CreatePlayerTextDraw(playerid, 541.000, 222.000, "Ronnie Varquez");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][20], 0.160, 0.899);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][20], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][20], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][20], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][20], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][20], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][20], 1);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][20], 1);

    BalapanTD[playerid][21] = CreatePlayerTextDraw(playerid, 608.000, 185.000, "1/3");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][21], 0.160, 0.899);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][21], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][21], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][21], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][21], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][21], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][21], 1);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][21], 1);

    BalapanTD[playerid][22] = CreatePlayerTextDraw(playerid, 608.000, 203.000, "1/3");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][22], 0.160, 0.899);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][22], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][22], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][22], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][22], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][22], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][22], 1);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][22], 1);

    BalapanTD[playerid][23] = CreatePlayerTextDraw(playerid, 608.000, 221.000, "1/3");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][23], 0.160, 0.899);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][23], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][23], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][23], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][23], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][23], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][23], 1);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][23], 1);

    BalapanTD[playerid][24] = CreatePlayerTextDraw(playerid, 560.000, 134.000, "Balapan Lembah District");
    PlayerTextDrawLetterSize(playerid, BalapanTD[playerid][24], 0.180, 1.099);
    PlayerTextDrawAlignment(playerid, BalapanTD[playerid][24], 2);
    PlayerTextDrawColor(playerid, BalapanTD[playerid][24], -1);
    PlayerTextDrawSetShadow(playerid, BalapanTD[playerid][24], 0);
    PlayerTextDrawSetOutline(playerid, BalapanTD[playerid][24], 0);
    PlayerTextDrawBackgroundColor(playerid, BalapanTD[playerid][24], 150);
    PlayerTextDrawFont(playerid, BalapanTD[playerid][24], 1);
    PlayerTextDrawSetProportional(playerid, BalapanTD[playerid][24], 1);
    return 1;
}

DestroyTDRacing(playerid)
{
    for(new i = 0; i < 25; i++)
    {
        PlayerTextDrawDestroy(playerid, BalapanTD[playerid][i]);
    }
    return 1;
}

ShowTDBalapan(playerid, bool:Chess7)
{
    if(Chess7)
    {
        for(new i = 0; i < 25; i++)
        {
            PlayerTextDrawShow(playerid, BalapanTD[playerid][i]);
        }
    }
    else
    {
        for(new i = 0; i < 25; i++)
        {
            PlayerTextDrawHide(playerid, BalapanTD[playerid][i]);
        }
    }
    return 1;
}