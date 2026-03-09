#include <YSI\y_hooks>

CMD:event(playerid, params[])
{
	static
		option[10],
		extendstring[128];

	if(sscanf(params, "s[10]S()[128]", option, extendstring))
	{
		if(AccountData[playerid][pAdmin] > 4) 
		{
			Info(playerid, "/event [entity]");
			Info(playerid, "ENTITY : create/end/open/start/weapon/dmspawn/message");
			return 1;
		}
		else 
		{
			return Info(playerid, "/event [join/leave]");
		}
	}
	if(!strcmp(option, "message")) 
	{
		new message[128];
		if(CheckAdmin(playerid, 4))
			return PermissionError(playerid);
		
		if(!EventData[eventCreated])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		if(sscanf(extendstring, "s[128]", message))
			return Syntax(playerid, "/event message [text]");

		format(EventData[eventMessage], 128, ColouredText(message));
		SendCustomMessage(playerid, "EVENT", "%s", message);
	}
	else if(!strcmp(option, "open")) {
		if(CheckAdmin(playerid, 4))
			return PermissionError(playerid);
		if(!EventData[eventCreated])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		if(EventData[eventType] == TYPE_TDM && (EventData[eventSpawnX][0] == 0.0 || EventData[eventSpawnX][1] == 0.0))
			return Error(playerid, "Lokasi team belum di tentukan, /event [spawn1/2].");

		EventData[eventOpen] = 1;
		eventMessageText[0] = "_";
		eventMessageText[1] = "_";
		eventMessageText[2] = "_";
		eventMessageText[3] = "_";
		EventData[eventTime] = 40;
		if(EventData[eventType] == TYPE_TDM) {
			SendClientMessageToAllEx(-1, ""YELLOW"EVENT: "RED"%s"WHITE" mengadakan %s Event, gunakan '"YELLOW"/event join"WHITE"' untuk berpartisipasi", AccountData[playerid][pAdminname], EventType(EventData[eventType]));
        	SendClientMessageToAllEx(-1, "-> Hadiah Partisipasi: "GREEN"%s"WHITE" // Hadiah Team Pemenang: "GREEN"%s"WHITE" // Target Score: "YELLOW"%d", FormatMoney(EventData[eventBonus]), FormatMoney(EventData[eventWinnerPrice]), EventData[eventTarget]);
		}
		else SendClientMessageToAllEx(-1, ""YELLOW"EVENT: "RED"%s "WHITE"mengadakan %s event, '"YELLOW"/event join "WHITE"' untuk berpartisipasi!.", GetAdminName(playerid), EventType(EventData[eventType]));
	}
	else if(!strcmp(option, "leave")) {
		if(!EventData[eventCreated])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		if(!IsPlayerInEvent(playerid))
			return Error(playerid, "Kamu tidak dalam acara event.");

		if(!EventData[eventStart])
			return Error(playerid, "Event belum di mulai, tidak dapat meninggalkan event.");

		eventLeave(playerid);

        Info(playerid, "Kamu telah meninggalkan event yang sedang berlangsung, kamu tidak mendapatkan bonus dari event.");
	}
	else if(!strcmp(option, "start")) {
		if(CheckAdmin(playerid, 4))
			return PermissionError(playerid);

		if(!EventData[eventCreated])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		if(!EventData[eventOpen])
			return Error(playerid, "Buka partisipasi event terlebih dahulu dengan perintah "WHITE"'/event open'.");

		if(EventData[eventStart])
			return Error(playerid, "Event telah dimulai sebelumnya.");

		if(!eventCount())
			return Error(playerid, "Tidak ada satupun yang ikut berpartisipasi.");

		EventData[eventStart] = 1;
		EventData[eventOpen] = 0;
		EventData[eventTime] = 0;

		foreach(new i : Player) 
		{
			if(IsPlayerInEvent(i)) 
			{
				TogglePlayerControllable(i, 1);
				AccountData[i][pFreeze] = 0;
				SetPlayerVirtualWorld(i, EventData[eventWorld]);

				if(EventData[eventType] == TYPE_JETPACK) {
					AccountData[i][pJetpack] = 1;
					SetPlayerSpecialAction(i, SPECIAL_ACTION_USEJETPACK);
				}
			}
		}

		if(EventData[eventType] == TYPE_JETPACK)
		{
			for(new id = 4; id != 8; id++) {
				TextDrawHideForPlayer(playerid, eventTextdraws[id]);
			}
		}

		SendClientMessageToAllEx(-1, ""YELLOW"EVENT: "RED"%s "WHITE"memulai event "RED"%s"WHITE", tidak dapat bergabung bagi yang belum masuk ke dalam event.", GetAdminName(playerid), EventType(EventData[eventType]));
	}
	else if(!strcmp(option, "join")) 
	{
		if(AccountData[playerid][pInjured])
			return Error(playerid, "Anda sedang pingsan.");

		if(!EventData[eventCreated] || !EventData[eventOpen])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		if(EventData[eventStart])
			return Error(playerid, "Event sedang berlangsung, tidak dapat mengikutinya lagi.");

		if(AccountData[playerid][pJailTime])
			return Error(playerid, "Waktu di penjara belum habis, tidak dapat mengikuti event.");

		if(IsPlayerInEvent(playerid))
			return Error(playerid, "Kamu telah berada dalam event.");

		//Team Selection
		ResetPlayerWeapons(playerid);
		eventJoin[playerid] = 1;
		
		GetPlayerPos(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ]);
		AccountData[playerid][pInt] = GetPlayerInterior(playerid);
		AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
	
		if(EventData[eventType] == TYPE_TDM)
		{
			if(EventData[eventSelectTeam])  {
				EventData[eventSelectTeam] = 0;
				eventTeams[playerid] = TEAM_A;
				SetPlayerColor(playerid, RemoveAlpha(X11_RED));
			}
			else {
				EventData[eventSelectTeam] = 1; 
				eventTeams[playerid] = TEAM_B;
				SetPlayerColor(playerid, RemoveAlpha(COLOR_BLUE));
			}

			SetPlayerTeam(playerid, eventTeams[playerid]);

			//Event textdraw
			for(new id = 0; id != 8; id++) {
				TextDrawShowForPlayer(playerid, eventTextdraws[id]);
			}

			//New event data
			eventSpawn(playerid);
			TogglePlayerControllable(playerid, 0);
			SetPlayerVirtualWorld(playerid, (playerid+1));

			eventTextdraw(playerid, sprintf("%s%s~w~_bergabung dalam event sebagai team %s", eventTeams[playerid] == TEAM_A ? ("~r~") : ("~b~"), ReturnName(playerid), eventTeams[playerid] == TEAM_A ? ("~r~A") : ("~b~B")));
			SendCustomMessage(playerid, "EVENT", "Kamu memasuki event sebagai team %s"WHITE", Kamu akan melihat player lain saat event dimulai.", eventTeams[playerid] == TEAM_A ? (""RED"A") : ("{0049FF}B"));
		}
		else if(EventData[eventType] == TYPE_DM)
		{
			eventTeams[playerid] = NO_TEAM;
			SetPlayerTeam(playerid, eventTeams[playerid]);
			eventSpawn(playerid);
			TogglePlayerControllable(playerid, 0);
			SetPlayerVirtualWorld(playerid, (playerid+1));

			SendCustomMessage(playerid, "EVENT", "Kamu memasuki event"WHITE", Kamu akan melihat player lain saat event dimulai.");
		}
		else if(EventData[eventType] == TYPE_JETPACK)
		{
			SetPlayerSkin(playerid, 5);

			SetPlayerInterior(playerid, EventData[eventInt]);
			SetPlayerVirtualWorld(playerid, (EventData[eventWorld]+playerid));
			SetPlayerColor(playerid, RemoveAlpha(COLOR_ORANGE));

			for(new id = 4; id != 8; id++) {
				TextDrawShowForPlayer(playerid, eventTextdraws[id]);
			}

			eventTextdraw(playerid, sprintf("~y~%s~w~_bergabung dalam ~r~jetpack event", ReturnName(playerid)));
			SendCustomMessage(playerid, "EVENT", "Kamu memasuki jetpack event, Kamu akan melihat player lain saat event dimulai.");

			eventCheckpoint[playerid] = ((EventData[eventJetpackType]*16)-16);

			switch(EventData[eventJetpackType])
			{
				case 1: SetPlayerPos(playerid, 726.0457,-1460.6995,22.2109); 
				case 2: SetPlayerPos(playerid, -1513.5300,-397.7400,7.0781);
				case 3: SetPlayerPos(playerid, 1748.9951,2318.4055,22.8222);
			}
			
			SetCameraBehindPlayer(playerid);
			TogglePlayerControllable(playerid, false);
			AccountData[playerid][pFreeze] = 1;

			SetPlayerRaceCheckpoint(playerid, 4, arrJetEvent[eventCheckpoint[playerid]][jX], arrJetEvent[eventCheckpoint[playerid]][jY], 
				arrJetEvent[eventCheckpoint[playerid]][jZ], arrJetEvent[eventCheckpoint[playerid]+1][jX], arrJetEvent[eventCheckpoint[playerid]+1][jY], 
				arrJetEvent[eventCheckpoint[playerid]+1][jZ], 3
			);
		}
		SendCustomMessage(playerid, "EVENT","%s.", EventData[eventMessage]);
	}
	else if(!strcmp(option, "create")) {
		if(CheckAdmin(playerid, 4))
			return PermissionError(playerid);

		if(EventData[eventStart])
			return Error(playerid, "Event telah berlangsung.");

		if(GetPVarInt(playerid, "EventTDM")) {
			DialogTDMShow(playerid);
		}
        else Dialog_Show(playerid, eventType, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Event Type", "Team Deathmatch\n"GRAY"Jetpack Race\nDeathMatch", "Pilih", "Batal");
	}
	else if(!strcmp(option, "end")) {
		if(CheckAdmin(playerid, 4))
			return PermissionError(playerid);

		static const empty_player[E_EVENT];
	    EventData = empty_player;

	    SendEventMessageAll(-1, sprintf(""YELLOW"EVENT: "RED"%s"WHITE" menghentikan event yang sedang berlangsung.", GetAdminName(playerid)));
	    Info(playerid, "Kamu menghentikan event.");
		SetPVarInt(playerid, "EventTDM", 0);

	    for(new id = 0; id != 8; id++) {
	    TextDrawHideForPlayer(playerid, eventTextdraws[id]);
		}
	    
	    foreach(new i : Player) 
		{
			if(IsPlayerInEvent(i)) 
			{
				eventLeave(i);
			}
		}
	}
	/*else if(!strcmp(option, "tdmspawn1")) {
		if(CheckAdmin(playerid, 4))
			return PermissionError(playerid);

		if(!EventData[eventCreated])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		GetPlayerPos(playerid, EventData[eventSpawnX][0], EventData[eventSpawnY][0], EventData[eventSpawnZ][0]);
		GetPlayerFacingAngle(playerid, EventData[eventSpawnA][0]);
		Info(playerid, "Kamu telah menentukan spawn untuk "RED"team A");
	}
	else if(!strcmp(option, "tdmspawn2")) {
		if(CheckAdmin(playerid, 4))
			return PermissionError(playerid);

		if(!EventData[eventCreated])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		GetPlayerPos(playerid, EventData[eventSpawnX][1], EventData[eventSpawnY][1], EventData[eventSpawnZ][1]);
		GetPlayerFacingAngle(playerid, EventData[eventSpawnA][1]);
		Info(playerid, "Kamu telah menentukan spawn untuk {0049FF}team B");
	}*/
	else if(!strcmp(option, "dmspawn")) {
		if(CheckAdmin(playerid, 4))
			return PermissionError(playerid);

		if(!EventData[eventCreated])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		GetPlayerPos(playerid, EventData[eventSpawnX_DM], EventData[eventSpawnY_DM], EventData[eventSpawnZ_DM]);
		Info(playerid, "Kamu telah menentukan spawn untuk Event DM");
	}
	else if(!strcmp(option, "weapon")) {
		if(CheckAdmin(playerid, 4))
			return PermissionError(playerid);

		if(!EventData[eventCreated])
			return Error(playerid, "Tidak ada event yang di lakukan sekarang.");

		Dialog_Show(playerid, eventWeapon, DIALOG_STYLE_LIST, "Event Weapon", "Weapon 1: %s - %d\nWeapon 2: %s - %d\nWeapon 3: %s - %d", "Edit", "Close", 
			ReturnWeaponName(EventData[eventWeapons][0]),
			EventData[eventAmmo][0],
			ReturnWeaponName(EventData[eventWeapons][1]),
			EventData[eventAmmo][1],
			ReturnWeaponName(EventData[eventWeapons][2]),
			EventData[eventAmmo][2]
		);
	}
	return 1;
}
