#include <YSI\y_hooks>

CMD:awskick(playerid, params[])
{
	if(CheckAdmin(playerid, 5))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak memiliki izin untuk menggunakan perintah ini!");

	new otherid;
    if(sscanf(params, "u", otherid))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/awskick (PlayerID/PartOfName)");
		
	if(!IsPlayerConnected(otherid))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "The player in question was not found");

	AccountData[otherid][pWorkshop] = -1;
	AccountData[otherid][pWorkshopRank] = 0;
	SendClientMessageEx(playerid, X11_ARWIN, "You have removed %s from the workshop.", AccountData[otherid][pName]);
	SendClientMessageEx(otherid, X11_ARWIN, "Administrator {A60000}%s has removed you from the workshop.", GetAdminName(playerid));
	return 1;  
}

CMD:createws(playerid, params[])
{
	if(CheckAdmin(playerid, 5))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak memiliki izin untuk menggunakan perintah ini!");
	
	new query[512];
	new wid = Iter_Free(Workshop);

	if(wid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "You cant create more door!");
	new price;

	if(sscanf(params, "d", price)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/createws [price]");

	format(wData[wid][wLeader], 128, "-");
	format(wData[wid][wName], 128, "No Name");

	wData[wid][wPrice] = price;
	GetPlayerPos(playerid, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]);

	GetPlayerFacingAngle(playerid, wData[wid][wExtposA]);

	wData[wid][wMoney] = 0;
	wData[wid][wStatus] = 1;
	wData[wid][wComponent] = 0;
  	
  	Workshop_Refresh(wid);

	Iter_Add(Workshop, wid);
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO workshop SET ID='%d', leader='%s', name='%s', price='%d'", wid, wData[wid][wLeader], wData[wid][wName], wData[wid][wPrice]);
	mysql_tquery(g_SQL, query, "OnWorkshopCreated", "i", wid);
	return 1;
}

JavaTR: OnWorkshopCreated(wid) 
{
	Workshop_Save(wid);
	return 1;
}

CMD:wsdelete(playerid, params[])
{
 	if(CheckAdmin(playerid, 5))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak memiliki izin untuk menggunakan perintah ini!");

    new wid, query[128];
	if(sscanf(params, "i", wid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wsdelete [wid]");
	if(!Iter_Contains(Workshop, wid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "The you specified ID of doesn't exist.");
	
    format(wData[wid][wName], 50, "None");
	format(wData[wid][wLeader], 50, "None");

	wData[wid][wExtposX] = 0;
	wData[wid][wExtposY] = 0;
	wData[wid][wExtposZ] = 0;
	wData[wid][wExtposA] = 0;

	wData[wid][wComponent] = 0;
	wData[wid][wMoney] = 0;
	
	DestroyDynamic3DTextLabel(wData[wid][wLabel]);
	DestroyDynamicPickup(wData[wid][wPickup]);
	DestroyDynamicMapIcon(wData[wid][wIcon]);
	
	Iter_Remove(Workshop, wid);
	
	mysql_format(g_SQL, query, sizeof(query), "UPDATE users SET workshop=-1,workshoprank=0,OnDuty=0 WHERE workshop=%d", wid);
	mysql_tquery(g_SQL, query);
	
	foreach(new ii : Player)
	{
 		if(AccountData[ii][pWorkshop] == wid)
   		{
			AccountData[ii][pWorkshop]= -1;
			AccountData[ii][pWorkshopRank] = 0;
		}
	}

	mysql_format(g_SQL, query, sizeof(query), "DELETE FROM workshop WHERE ID=%d", wid);
	mysql_tquery(g_SQL, query); 
    SendClientMessageEx(playerid, X11_ARWIN, "Admin %s telah menghapus Workshop ID: %d.", GetAdminName(playerid), wid);
	return 1;
}

CMD:gotows(playerid, params[])
{
	new wid;
	if(CheckAdmin(playerid, 5))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak memiliki izin untuk menggunakan perintah ini!");
		
	if(sscanf(params, "d", wid))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotows [id]");
	if(!Iter_Contains(Workshop, wid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "The Workshop you specified ID of doesn't exist.");
	SetPlayerPosition(playerid, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ], wData[wid][wExtposA]);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
	SendClientMessageEx(playerid, COLOR_WHITE, "You has teleport to workshop id %d", wid);
	//AccountData[playerid][pInDoor] = -1;
	//AccountData[playerid][pInHouse] = -1;
	return 1;
}

CMD:wsedit(playerid, params[])
{
    static
        wid,
        type[24],
        string[128],
		otherid;

    if(CheckAdmin(playerid, 5))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak memiliki izin untuk menggunakan perintah ini!");

    if(sscanf(params, "ds[24]S()[128]", wid, type, string))
    {
        ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wsedit [id] [name]");
        SendClientMessage(playerid, -1, "location, name, leader, position, money, component");
        return 1;
    }

    if((wid < 0 || wid >= MAX_WORKSHOP))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "You have specified an invalid ID.");

	if(!Iter_Contains(Workshop, wid)) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "The you specified ID of doesn't exist.");

    if(!strcmp(type, "name", true))
    {
        new name[50];

        if(sscanf(string, "s[50]", name))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wsedit [id] [name] [Workshop Name]");

        format(wData[wid][wName], 50, name);
		Workshop_Save(wid);
		Workshop_Refresh(wid);

        SendClientMessageEx(playerid, X11_ARWIN, "Admin %s has changed the Workshop name ID: %d to: %s.", GetAdminName(playerid), wid, name);
    }
    else if(!strcmp(type, "leader", true))
    {
        if(sscanf(string, "d", otherid))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wsedit [id] [leader] [playerid]");
		
		if(otherid == INVALID_PLAYER_ID)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "invalid player wid");

        format(wData[wid][wLeader], 50, AccountData[otherid][pName]);
        AccountData[otherid][pWorkshop] = wid;
        AccountData[otherid][pWorkshopRank] = 6;
		Workshop_Save(wid);
		Workshop_Refresh(wid);

        SendClientMessageEx(playerid, X11_ARWIN, "Admin %s has changed the Workshop leader ID: %d to: %s.", GetAdminName(playerid), wid, AccountData[otherid][pName]);
    }
    else if(!strcmp(type, "location", true))
    {
    	GetPlayerFacingAngle(playerid, wData[wid][wExtposA]);
        GetPlayerPos(playerid, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]);
        Workshop_Save(wid);
		Workshop_Refresh(wid);
		
		SendClientMessageEx(playerid, X11_ARWIN, "Admin %s has changed the Workshop safepos ID: %d.", GetAdminName(playerid), wid);
    }
    else if(!strcmp(type, "money", true))
    {
        new money;

        if(sscanf(string, "d", money))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wsedit [id] [money] [ammount]");

        wData[wid][wMoney] = money;
		
        Workshop_Save(wid);
		Workshop_Refresh(wid);
		
		SendClientMessageEx(playerid, X11_ARWIN, "Admin %s has changed the Workshop money ID: %d to %s.", GetAdminName(playerid), wid, FormatNumber(money));   
	}
	else if(!strcmp(type, "component", true))
    {
        new component;

        if(sscanf(string, "d", component))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wsedit [id] [component] [ammount]");

        wData[wid][wComponent] = component;
		
        Workshop_Save(wid);
		Workshop_Refresh(wid);
		
		SendClientMessageEx(playerid, X11_ARWIN, "Admin %s has changed the Workshop component ID: %d to %d.", GetAdminName(playerid), wid, component);   
	}
    return 1;
}

CMD:wshelp(playerid, paramas[])
{
	if(AccountData[playerid][pWorkshop] == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop");

	new str[3500];
	strcat(str, "Commands\tInformation\n");
	strcat(str, "/wsstorage\tUntuk membuka menu/locker list pada workshop\n"); 
	strcat(str, "/wsinvite\tUntuk menginvite seseorang menjadi anggota workshop\n");
	strcat(str, "/wskick\tUntuk mengeluarkan seseorang dari anggota workshop\n");
	strcat(str, "/wssetrank\tUntuk mengatur rank anggota workshop\n");
	strcat(str, "/wservice\tUntuk membuka menu modif kendaraan\n");
	strcat(str, "/wsann\tUntuk mengirim pengumuman di pesan langit\n");
	strcat(str, "/lockws\tUntuk merubah status Open/Closed pada worskhop");
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "Workshop Commands", str, "Close","");
	return 1;
}

CMD:wsstorage(playerid, const params[])
{
	if(AccountData[playerid][pWorkshop] == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop!");

	new wsid = AccountData[playerid][pWorkshop];

	if(IsPlayerInRangeOfPoint(playerid, 2.5, wData[wsid][wExtposX], wData[wsid][wExtposY], wData[wsid][wExtposZ]))
	{
		new string[254];
		format(string, sizeof(string), "Workshop Info\nToggle Duty\nMoney Storage ({00FF00}$%d)\nComponent Storage(%d)\nCreate Repairkit", wData[wsid][wMoney], wData[wsid][wComponent]);
		ShowPlayerDialog(playerid, WORKSHOP_MENU, DIALOG_STYLE_LIST, "Workshop Menu", string,"Next","Close");
	}
	else return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop ini!");
	return 1;
}

CMD:setplate(playerid, params[])
{
	if(CheckAdmin(playerid, 4))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak memiliki izin untuk menggunakan perintah ini!");


	new vehid, platename[5];	
	if(sscanf(params, "us[1028]", vehid, platename))
	{
		ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setplate <Vehicle ID> <Plate>");
		return true;
	}

	if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid id");
	if(!IsValidVehicle(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid veh id");

	foreach(new ii : PvtVehicles)
	{
		if(IsValidVehicle(PlayerVehicle[ii][pVehID])) 
		{
			format(PlayerVehicle[ii][pVehPlate], 32, platename);
			SetVehicleNumberPlate(PlayerVehicle[ii][pVehID], PlayerVehicle[ii][pVehPlate]);
			SendClientMessageEx(playerid, X11_ARWIN, "Plat number kendaraan tersebut, berhasil di ganti menjadi %s", PlayerVehicle[ii][pVehPlate]);
		}
	}
	return 1;
}

CMD:lockws(playerid, const params[])
{
	if(AccountData[playerid][pWorkshopRank] < 5)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya rank 5 dan 6 yang bisa menutup workshop");

	foreach(new wid : Workshop)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
		{
			if(!Player_OwnsWorkshop(playerid, wid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "You don't own this workshop.");
			if(!wData[wid][wStatus])
			{
				wData[wid][wStatus] = 1;
				Workshop_Save(wid);
				Workshop_Refresh(wid);

				ShowTDN(playerid, NOTIFICATION_SUKSES, "You have ~r~closed~w~ your workshop!");
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
			else
			{
				wData[wid][wStatus] = 0;
				Workshop_Save(wid);
				Workshop_Refresh(wid);

				ShowTDN(playerid, NOTIFICATION_SUKSES, "You have ~g~opened~w~ your workshop!");
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
		}
	}
	return 1;
}

CMD:wsinvite(playerid, params[])
{
	if(AccountData[playerid][pWorkshop] == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak bergabung workshop manapun");
		
	if(AccountData[playerid][pWorkshopRank] < 5)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "You must workshop rank 5 - 6!");
	
	new otherid;
    if(sscanf(params, "u", otherid))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wsinvite [playerid/PartOwName]");
		
	if(!IsPlayerConnected(otherid))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ID.");
	
	if(otherid == playerid)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ID.");
		
	if(!IsPlayerNearPlayer(playerid, otherid, 5.0))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "You must be near this player.");
	
	if(AccountData[otherid][pWorkshop] != -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Player tersebut sudah bergabung workshop lain!");
		
	if(AccountData[otherid][pFaction] != 0)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak bisa menginvite anggota faction");

	AccountData[otherid][pWsInvite] = AccountData[playerid][pWorkshop];
	AccountData[otherid][pWsOffer] = playerid;
	SendClientMessageEx(playerid, X11_ARWIN, "Anda telah menginvite %s untuk menjadi anggota workshop.", AccountData[otherid][pName]);
	SendClientMessageEx(otherid, X11_ARWIN, "%s telah menginvite anda untuk menjadi anggota workshop. Type: /accept workshop", AccountData[playerid][pName]);
	return 1;
}

CMD:wskick(playerid, params[])
{
	if(AccountData[playerid][pWorkshop] == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "You are not in Workshop!");
		
	if(AccountData[playerid][pWorkshopRank] < 5)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "You must Workshop level 5 - 6!");
	
	new otherid;
    if(sscanf(params, "u", otherid))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wskick [playerid/PartOwName]");
		
	if(!IsPlayerConnected(otherid))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ID.");
	
	if(otherid == playerid)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ID.");
	
	if(AccountData[otherid][pWorkshopRank] > AccountData[playerid][pWorkshopRank])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "You cant kick him.");
		
	AccountData[otherid][pWorkshopRank] = 0;
	AccountData[otherid][pWorkshop] = -1;
	SendClientMessageEx(playerid, X11_ARWIN, "Anda telah mengeluarkan %s dari anggota Workshop.", AccountData[otherid][pName]);
	SendClientMessageEx(otherid, X11_ARWIN, "%s telah mengeluarkan anda dari anggota Workshop.", AccountData[playerid][pName]);
	return 1;
}

CMD:wssetrank(playerid, params[])
{
	new rank, otherid;
	if(AccountData[playerid][pWorkshopRank] < 6)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "You must Workshop leader!");
		
	if(sscanf(params, "ud", otherid, rank))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wssetrank [playerid/PartOwName] [rank 1-6]");
	
	if(!IsPlayerConnected(otherid))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ID.");
	
	if(otherid == playerid)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ID.");
	
	if(AccountData[otherid][pWorkshop] != AccountData[playerid][pWorkshop])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "This player is not in your Workshop!");
	
	if(rank < 1 || rank > 6)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "rank must 1 - 6 only");
	
	AccountData[otherid][pWorkshopRank] = rank;
	SendClientMessageEx(playerid, X11_ARWIN, "You has set %s Workshop rank to level %d", AccountData[otherid][pName], rank);
	SendClientMessageEx(otherid, X11_ARWIN, "%s has set your Workshop rank to level %d", AccountData[playerid][pName], rank);
	return 1;
}

CMD:wsann(playerid, params[])
{
	if(AccountData[playerid][pWorkshop] == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pekerja workshop");

	new lstr[1024];
	format(lstr, sizeof(lstr), "{8D6D48}[WORKSHOP] %s {FFFFFF}: "BLUE"%s", AccountData[playerid][pName], params);
	va_SendClientMessageToAll(-1, lstr);
	return 1;
}

CMD:buyws(playerid, paramas[])
{
	foreach(new wid : Workshop)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
		{
			new price;
			price = wData[wid][wPrice];
			
			if(AccountData[playerid][pMoney]< price)
				return ShowTDN(playerid, NOTIFICATION_ERROR,"Not enough money, you can't afford this workshop.");

			if(strcmp(wData[wid][wLeader], "-")) 
				return ShowTDN(playerid, NOTIFICATION_ERROR,"Someone already owns this workshop.");

			if(AccountData[playerid][pVip] == 1)
			{
			    #if LIMIT_PER_PLAYER > 0
				if(Player_WorkshopCount(playerid) + 1 > 1) return ShowTDN(playerid, NOTIFICATION_ERROR,"You can't buy any more workshop.");
				#endif
			}
			else if(AccountData[playerid][pVip] == 2)
			{
			    #if LIMIT_PER_PLAYER > 0
				if(Player_WorkshopCount(playerid) + 1 > 1) return ShowTDN(playerid, NOTIFICATION_ERROR,"You can't buy any more workshop.");
				#endif
			}
			else if(AccountData[playerid][pVip] == 3)
			{
			    #if LIMIT_PER_PLAYER > 0
				if(Player_WorkshopCount(playerid) + 1 > 1) return ShowTDN(playerid, NOTIFICATION_ERROR,"You can't buy any more workshop.");
				#endif
			}
			else
			{
				#if LIMIT_PER_PLAYER > 0
				if(Player_WorkshopCount(playerid) + 1 > 1) return ShowTDN(playerid, NOTIFICATION_ERROR,"You can't buy any more workshop.");
				#endif
			}

			if(AccountData[playerid][pWorkshop] != -1) 
				return ShowTDN(playerid, NOTIFICATION_ERROR,"Kamu harus keluar dari anggota workshop lain!");

			GiveMoney(playerid, -wData[wid][wPrice]);
			//Server_AddMoney(wData[wid][wPrice]);
			format(wData[wid][wLeader], MAX_PLAYER_NAME, AccountData[playerid][pName]);
			Workshop_Save(wid);
			Workshop_Refresh(wid);

			AccountData[playerid][pWorkshop] = wid;
			AccountData[playerid][pWorkshopRank] = 6;
			//UpdatePlayerData(playerid);
		}
	}
	return 1;
}

CMD:wsinvoice(playerid, params[])
{
    new targetid = AccountData[playerid][pTarget];

    if(AccountData[playerid][pWorkshop] == -1) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan pekerja workshop");

    if(AccountData[playerid][pOnDuty] == 0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu harus on duty");
    
    if(sscanf(params, "u", targetid)) 
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wsinvoice [name/playerid]");

    if(!IsPlayerConnected(targetid)) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    if(!IsPlayerNearPlayer(playerid, targetid, 5.5)) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan player tersebut!");

    if(IsPlayerInjured(playerid)) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan, tidak dapat memberikan invoice!");

    SetPVarInt(targetid, "InvoiceWSID", AccountData[playerid][pWorkshop]);
    SetPVarInt(targetid, "InvoiceSenderID", playerid);

    GivePlayerInvoice(playerid, targetid);

    printf("[DEBUG] %s (ID: %d) memberi invoice ke %d untuk workshop ID %d", AccountData[playerid][pName], playerid, targetid, AccountData[playerid][pWorkshop]);
    return 1;
}

CMD:wservice(playerid, params[])
{
	if(AccountData[playerid][pWorkshop] == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan pekerja workshop");
	{
		if(AccountData[playerid][pOnDuty] == 0)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu harus on duty");
		{
			if(AccountData[playerid][pMechVeh] == INVALID_VEHICLE_ID)
			{
				new vehicleid = GetNearestVehicleToPlayer(playerid, 3.5, false);
				
				if(vehicleid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "You not in near any vehicles.");
				if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
				if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
				ShowTDN(playerid, NOTIFICATION_INFO, "Don't move from your position or you will failed to checking this vehicle!");
				ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 1, 1, 1, 0, 1);
				ShowProgressbar(playerid, "Examining", 10);
				AccountData[playerid][pMechanic] = SetTimerEx("CheckCar", 10000, false, "dd", playerid, vehicleid);
				return 1;
			}
			
			if(GetNearestVehicleToPlayer(playerid, 3.5, false) == AccountData[playerid][pMechVeh])
			{
				new Dstring[800], Float:health, engine;
				new panels, doors, light, tires, body;
        		GetVehicleHealth(AccountData[playerid][pMechVeh], health);
				if(health > 100.0) health = 100.0;
				if(health > 0.0) health *= -1;
				engine = floatround(health, floatround_round) / 10 + 100;
				
				GetVehicleDamageStatus(AccountData[playerid][pMechVeh], panels, doors, light, tires);
			    new cpanels = panels / 1000000;
			    new lights = light / 2;
			    new pintu;
			    if(doors != 0) pintu = 5;
			    if(doors == 0) pintu = 0;
			    body = cpanels + lights + pintu + 20;
				format(Dstring, sizeof(Dstring), "Service Name\tComponent\n");
				format(Dstring, sizeof(Dstring), "%sEngine Fix\t%d\n", Dstring, engine);
				format(Dstring, sizeof(Dstring), "%sBody Fix\t%d\n", Dstring, body);
				format(Dstring, sizeof(Dstring), "%sEngine Upgrade\t300\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sSpray Car\t12\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sPaint Job Car\t30\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sWheels Car\t25\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sSpoiler Car\t21\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sHood Car\t21\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sVents Car\t21\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sLights Car\t21\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sExhausts\t24\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sFront bumpers\t30\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sRear Bumpers\t30\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sRoofs Car\t21\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sSide skirts\t27\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sBullbars\t15\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sStereo\t45\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sHydraulics\t45\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sNitro 1\t75\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sNitro 2\t112\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sNitro 3\t150\n", Dstring);
				format(Dstring, sizeof(Dstring), "%sNeon\t135", Dstring);
				ShowPlayerDialog(playerid, WORKSHOP_SERVICE, DIALOG_STYLE_TABLIST_HEADERS, "Workshop Service", Dstring, "Service", "Cancel");
			}
			else
			{
				KillTimer(AccountData[playerid][pMechanic]);
				
				
				AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
				AccountData[playerid][pActivityTime] = 0;
				ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
				return 1;
			}
		}
	}
	return 1;
}


stock LockWs(playerid)
{
	if(AccountData[playerid][pWorkshopRank] < 5)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya rank 5 dan 6 yang bisa menutup workshop");

	foreach(new wid : Workshop)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
		{
			if(!Player_OwnsWorkshop(playerid, wid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "You don't own this workshop.");
			if(!wData[wid][wStatus])
			{
				wData[wid][wStatus] = 1;
				Workshop_Save(wid);
				Workshop_Refresh(wid);

				ShowTDN(playerid, NOTIFICATION_INFO, "You have ~r~closed~w~ your workshop!");
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
			else
			{
				wData[wid][wStatus] = 0;
				Workshop_Save(wid);
				Workshop_Refresh(wid);

				ShowTDN(playerid, NOTIFICATION_INFO, "You have ~g~opened~w~ your workshop!");
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
		}
	}
	return 1;
}

stock WsStoragee(playerid)
{
	if(AccountData[playerid][pWorkshop] == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop!");

	new wsid = AccountData[playerid][pWorkshop];

	if(IsPlayerInRangeOfPoint(playerid, 2.5, wData[wsid][wExtposX], wData[wsid][wExtposY], wData[wsid][wExtposZ]))
	{
		new string[254];
		format(string, sizeof(string), "Workshop Info\nToggle Duty\nMoney Storage ({00FF00}$%d)\nComponent Storage(%d)\nCreate Repairkit", wData[wsid][wMoney], wData[wsid][wComponent]);
		ShowPlayerDialog(playerid, WORKSHOP_MENU, DIALOG_STYLE_LIST, "Workshop Menu", string,"Next","Close");
	}
	else return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop ini!");
	return 1;
}


hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == WORKSHOP_MENU)
	{
		if(!response) return 1;
		new wid = AccountData[playerid][pWorkshop];

		new status[128];
		if(wData[wid][wStatus] == 1)
		{
			status = "{FF0000}Closed";
		}
		else
		{
			status = "{00FF00}Opened";
		}
		switch(listitem) 
		{
			case 0:
			{
				new mstr[248], lstr[512];
				format(mstr,sizeof(mstr),""WHITE_E"Workshop ID %d", wid);
				format(lstr,sizeof(lstr),""WHITE_E"Workshop Name:\t"RED"%s\n"WHITE_E"Workshop Status:\t%s\nWorkshop Member\t", wData[wid][wName], status);
				ShowPlayerDialog(playerid, WORKSHOP_INFO, DIALOG_STYLE_TABLIST, mstr, lstr,"Select","Close");
			}
			case 1:
			{
				if(AccountData[playerid][pOnDuty] == 1)
				{
					AccountData[playerid][pOnDuty] = 0;
					SetPlayerColor(playerid, COLOR_WHITE);
					SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s mengganti pakaian kerja dengan pakaian biasa", ReturnName(playerid));
				}
				else
				{
					AccountData[playerid][pOnDuty] = 1;
					new Coklat = 0x8B4513;
					SetPlayerColor(playerid, Coklat);
					if(AccountData[playerid][pGender] == 1)
					{
						SetPlayerSkin(playerid, 268);
						AccountData[playerid][pFacSkin] = 268;
					}
					else
					{
						SetPlayerSkin(playerid, 69); //194
						AccountData[playerid][pFacSkin] = 69; //194
					}
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s mengambil pakaian kerja dari dalam locker dan langsung memakainya", ReturnName(playerid));
				}
			}
			case 2:
			{
				//Workshop Money
				ShowPlayerDialog(playerid, WORKSHOP_MONEY, DIALOG_STYLE_LIST, "Workshop Money", "Withdraw Money\nDeposit Money", "Select", "Back");
			}
			case 3:
			{
				//Workshop Component
				ShowPlayerDialog(playerid, WORKSHOP_COMPONENT, DIALOG_STYLE_LIST, "Workshop Component", "Withdraw Component\nDeposit Component", "Select", "Back");
			}
			case 4:
			{
				if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
				if(Inventory_Count(playerid, "Component") < 100)
					return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus memiliki 100 component untuk membuat ini");

				if(AccountData[playerid][pActivityTime] > 5)
					return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity progress");

				TogglePlayerControllable(playerid, 0);
				
				AccountData[playerid][pMechanic] = SetTimerEx("WorkshopCreateRepairkit", 10000, false, "id", playerid, AccountData[playerid][pWorkshop]);
				ShowProgressbar(playerid, "Creating...", 10);
			}
		}
		return 1;
	}
	if(dialogid == WORKSHOP_NAME)
	{
		if(response)
		{
			new wid = AccountData[playerid][pWorkshop];

			if(!Player_OwnsWorkshop(playerid, wid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "You don't own this workshop.");
			
			if (isnull(inputtext))
			{
				new mstr[512];
				format(mstr,sizeof(mstr),""RED"NOTE: "WHITE_E"Nama Workshop tidak di perbolehkan kosong!\n\n"WHITE_E"Nama Workshop: "RED"%s\n\n"WHITE_E"Masukkan nama Workshop yang kamu inginkan\nMaksimal 32 karakter untuk nama Bisnis", wData[wid][wName]);
				ShowPlayerDialog(playerid, WORKSHOP_NAME, DIALOG_STYLE_INPUT,"Workshop Name", mstr,"Done","Back");
				return 1;
			}
			if(strlen(inputtext) > 32 || strlen(inputtext) < 5)
			{
				new mstr[512];
				format(mstr,sizeof(mstr),""RED"NOTE: "WHITE_E"Nama Workshop harus 5 sampai 32 karakter.\n\n"WHITE_E"Nama Workshop: "RED"%s\n\n"WHITE_E"Masukkan nama Workshop yang kamu inginkan\nMaksimal 32 karakter untuk nama Bisnis", wData[wid][wName]);
				ShowPlayerDialog(playerid, WORKSHOP_NAME, DIALOG_STYLE_INPUT,"Workshop Name", mstr,"Done","Back");
				return 1;
			}
			format(wData[wid][wName], 32, ColouredText(inputtext));

			Workshop_Refresh(wid);
			Workshop_Save(wid);

			SendClientMessageEx(playerid, COLOR_CLIENT, "Workshop name set to: \"%s\".", wData[wid][wName]); 
		}
		else return WsStoragee(playerid);
		return 1;
	}
	if(dialogid == WORKSHOP_INFO)
	{
		new wid = AccountData[playerid][pWorkshop];
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					if(AccountData[playerid][pWorkshopRank] < 6)
					return ShowTDN(playerid, NOTIFICATION_ERROR,"Hanya rank 6 yang bisa mengubah nama.");

					new mstr[248];
					format(mstr,sizeof(mstr),""WHITE_E"Nama Workshop: "RED"%s\n\n"WHITE_E"Masukkan nama workshop yang kamu inginkan\nMaksimal 32 karakter untuk nama workshop", wData[wid][wName]);
					ShowPlayerDialog(playerid, WORKSHOP_NAME, DIALOG_STYLE_INPUT,"Workshop Name", mstr,"Done","Back");
				}
				case 1:
				{
					return LockWs(playerid);
				}
				case 2:
				{
					if(AccountData[playerid][pWorkshop] == -1)
						return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop!");

					new query[512];
					mysql_format(g_SQL, query, sizeof(query), "SELECT Char_Name,workshoprank FROM player_characters WHERE workshop = %d", AccountData[playerid][pWorkshop]);
					mysql_tquery(g_SQL, query, "ShowWorkshopMember", "i", playerid);
				}
			}
		}
		return 1;
	}
	if(dialogid == WORKSHOP_MONEY)
	{
		if(response)
		{
			new wid = AccountData[playerid][pWorkshop];
			if(wid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop!");
			if(response)
			{
				switch (listitem)
				{
					case 0: 
					{
						if(AccountData[playerid][pWorkshopRank] < 5)
							return ShowTDN(playerid, NOTIFICATION_SUKSES, "Hanya rank 5 dan 6 yang bisa mengambil ini!");
							
						new str[128];
						format(str, sizeof(str), ""WHITE_E"Money Balance: "GREEN"%s/$1.500,000\n\n"WHITE_E"Please enter how much money you wish to withdraw from the safe:", FormatNumber(wData[wid][wMoney]));
						ShowPlayerDialog(playerid, WORKSHOP_WITHDRAWMONEY, DIALOG_STYLE_INPUT, "Withdraw Money", str, "Withdraw", "Back");
					}
					case 1: 
					{
						new str[128];
						format(str, sizeof(str), ""WHITE_E"Money Balance: "GREEN"%s/$1.500,000\n\n"WHITE_E"Please enter how much money you wish to deposit into the safe:", FormatNumber(wData[wid][wMoney]));
						ShowPlayerDialog(playerid, WORKSHOP_DEPOSITMONEY, DIALOG_STYLE_INPUT, "Deposit Money", str, "Deposit", "Back");
					}
				}
			}
			else WsStoragee(playerid);
		}
		return 1;
	}
	if(dialogid == WORKSHOP_WITHDRAWMONEY)
	{
		new wid = AccountData[playerid][pWorkshop];
		if(wid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop!");
		
		if(response)
		{
			new amount = strval(inputtext);

			if(isnull(inputtext))
			{
				new str[128];
				format(str, sizeof(str), ""WHITE_E"Money Balance: "GREEN"%s/$1.500,000\n\n"WHITE_E"Please enter how much money you wish to withdraw from the safe:", FormatNumber(wData[wid][wMoney]));
				ShowPlayerDialog(playerid, WORKSHOP_WITHDRAWMONEY, DIALOG_STYLE_INPUT, "Withdraw Money", str, "Withdraw", "Back");
				return 1;
			}
			if(amount < 1 || amount > wData[wid][wMoney])
			{
				new str[128];
				format(str, sizeof(str), ""RED"ERROR: "WHITE_E"Insufficient funds.\n\nMoney Balance: "GREEN"%s/$1.500,000\n\n"WHITE_E"Please enter how much money you wish to withdraw from the safe:", FormatNumber(wData[wid][wMoney]));
				ShowPlayerDialog(playerid, WORKSHOP_WITHDRAWMONEY, DIALOG_STYLE_INPUT, "Withdraw Money", str, "Withdraw", "Back");
				return 1;
			}
			wData[wid][wMoney] -= amount;
			GiveMoney(playerid, amount);

			Workshop_Save(wid);
			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has withdrawn %s money from storage.", ReturnName(playerid), FormatNumber(amount));
			WsStoragee(playerid);
			return 1;
		}
		else WsStoragee(playerid);
		return 1;
	}
	if(dialogid == WORKSHOP_DEPOSITMONEY)
	{
		new wid = AccountData[playerid][pWorkshop];
		if(wid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop.");
		if(wData[wid][wMoney] > 1500000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Penyimpanan sudah penuh!");

		if(response)
		{
			new amount = strval(inputtext);

			if(isnull(inputtext))
			{
				new str[128];
				format(str, sizeof(str), ""WHITE_E"Money Balance: "GREEN"%s/$1.500,000\n\n"WHITE_E"Please enter how much money you wish to deposit into the safe:", FormatNumber(wData[wid][wMoney]));
				ShowPlayerDialog(playerid, WORKSHOP_DEPOSITMONEY, DIALOG_STYLE_INPUT, "Deposit Money", str, "Deposit", "Back");
				return 1;
			}
			if(amount < 1 || amount > AccountData[playerid][pMoney])
			{
				new str[128];
				format(str, sizeof(str), ""RED"ERROR: "WHITE_E"Insufficient funds.\n\nMoney Balance: "GREEN"%s/$1.500,000\n\n"WHITE_E"Please enter how much money you wish to deposit into the safe:", FormatNumber(wData[wid][wMoney]));
				ShowPlayerDialog(playerid, WORKSHOP_DEPOSITMONEY, DIALOG_STYLE_INPUT, "Deposit Money", str, "Deposit", "Back");
				return 1;
			}
			wData[wid][wMoney] += amount;
			GiveMoney(playerid, -amount);

			Workshop_Save(wid);
			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has deposited %s money into storage.", ReturnName(playerid), FormatNumber(amount));
		}
		else WsStoragee(playerid);
		return 1;
	}
	if(dialogid == WORKSHOP_COMPONENT)
	{
		if(response)
		{
			new wid = AccountData[playerid][pWorkshop];
			if(wid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop!");
			if(response)
			{
				switch (listitem)
				{
					case 0: 
					{
						if(AccountData[playerid][pWorkshopRank] < 5)
							return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya rank 5 dan 6 yang bisa mengambil ini!");
							
						new str[128];
						format(str, sizeof(str), ""WHITE_E"Component Balance: "GREEN"%d/10.000\n\n"WHITE_E"Please enter how much component you wish to withdraw from the safe:", wData[wid][wComponent]);
						ShowPlayerDialog(playerid, WORKSHOP_WITHDRAWCOMPONENT, DIALOG_STYLE_INPUT, "Withdraw Component", str, "Withdraw", "Back");
					}
					case 1: 
					{
						new str[128];
						format(str, sizeof(str), ""WHITE_E"Component Balance: "GREEN"%d/10.000\n\n"WHITE_E"Please enter how much component you wish to deposit into the safe:", wData[wid][wComponent]);
						ShowPlayerDialog(playerid, WORKSHOP_DEPOSITCOMPONENT, DIALOG_STYLE_INPUT, "Deposit Component", str, "Deposit", "Back");
					}
				}
			}
			else WsStoragee(playerid);
		}
		return 1;
	}
	if(dialogid == WORKSHOP_WITHDRAWCOMPONENT)
	{
		new wid = AccountData[playerid][pWorkshop];
		if(wid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop!");
		
		if(response)
		{
			new amount = strval(inputtext);

			if(isnull(inputtext))
			{
				new str[128];
				format(str, sizeof(str), ""WHITE_E"Component Balance: "GREEN"%d/10.000\n\n"WHITE_E"Please enter how much component you wish to withdraw from the safe:", wData[wid][wComponent]);
				ShowPlayerDialog(playerid, WORKSHOP_WITHDRAWCOMPONENT, DIALOG_STYLE_INPUT, "Withdraw Component", str, "Withdraw", "Back");
				return 1;
			}
			if(amount < 1 || amount > wData[wid][wComponent])
			{
				new str[128];
				format(str, sizeof(str), ""RED"ERROR: "WHITE_E"Insufficient funds.\n\nComponent Balance: "GREEN"%d/10.000\n\n"WHITE_E"Please enter how much component you wish to withdraw from the safe:", wData[wid][wComponent]);
				ShowPlayerDialog(playerid, WORKSHOP_WITHDRAWCOMPONENT, DIALOG_STYLE_INPUT, "Withdraw Component", str, "Withdraw", "Back");
				return 1;
			}
			wData[wid][wComponent] -= amount;
			Inventory_Add(playerid, "Component", 19627, amount);

			Workshop_Save(wid);
			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has withdrawn %d component from storage.", ReturnName(playerid), amount);
			WsStoragee(playerid);
			return 1;
		}
		else WsStoragee(playerid);
		return 1;
	}
	if(dialogid == WORKSHOP_DEPOSITCOMPONENT)
	{
		new wid = AccountData[playerid][pWorkshop];
		if(wid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan anggota workshop.");
		if(wData[wid][wComponent] > 10000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Penyimpanan sudah penuh!");

		if(response)
		{
			new amount = strval(inputtext);

			if(isnull(inputtext))
			{
				new str[128];
				format(str, sizeof(str), ""WHITE_E"Component Balance: "GREEN"%d/10.000\n\n"WHITE_E"Please enter how much component you wish to deposit into the safe:", wData[wid][wComponent]);
				ShowPlayerDialog(playerid, WORKSHOP_DEPOSITCOMPONENT, DIALOG_STYLE_INPUT, "Deposit Component", str, "Deposit", "Back");
				return 1;
			}
			if(amount < 1 || amount > Inventory_Count(playerid, "Component"))
			{
				new str[128];
				format(str, sizeof(str), ""RED"ERROR: "WHITE_E"Insufficient funds.\n\nComponent Balance: "GREEN"%d/10.000\n\n"WHITE_E"Please enter how much component you wish to deposit into the safe:", wData[wid][wComponent]);
				ShowPlayerDialog(playerid, WORKSHOP_DEPOSITCOMPONENT, DIALOG_STYLE_INPUT, "Deposit Component", str, "Deposit", "Back");
				return 1;
			}
			wData[wid][wComponent] += amount;
			Inventory_Remove(playerid, "Component", amount);

			Workshop_Save(wid);
			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has deposited %d component into storage.", ReturnName(playerid), amount);
		}
		else WsStoragee(playerid);
		return 1;
	}
	if(dialogid == DIALOG_SERVICE_COLOR)
	{
		if(response)
		{
			AccountData[playerid][pMechColor1] = floatround(strval(inputtext));
			
			if(AccountData[playerid][pMechColor1] < 0 || AccountData[playerid][pMechColor1] > 255)
				return ShowPlayerDialog(playerid, DIALOG_SERVICE_COLOR, DIALOG_STYLE_INPUT, "Color ID 1", "Enter the color id 1:(0 - 255)", "Next", "Close");
			
			ShowPlayerDialog(playerid, DIALOG_SERVICE_COLOR2, DIALOG_STYLE_INPUT, "Color ID 2", "Enter the color id 2:(0 - 255)", "Next", "Close");
		}
		return 1;
	}
	if(dialogid == DIALOG_SERVICE_COLOR2)
	{
		if(response)  
		{
			AccountData[playerid][pMechColor2] = floatround(strval(inputtext)); 
			if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
			if(AccountData[playerid][pMechColor2] < 0 || AccountData[playerid][pMechColor2] > 255)
				return ShowPlayerDialog(playerid, DIALOG_SERVICE_COLOR2, DIALOG_STYLE_INPUT, "Color ID 2", "Enter the color id 2:(0 - 255)", "Next", "Close");
			
			if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
			if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
			{	
				if(Inventory_Count(playerid, "Component") < 12) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
				Inventory_Remove(playerid, "Component", 12);
				ShowTDN(playerid, NOTIFICATION_INFO, "Anda mengganti warna kendaraan dengan "RED"12 component.");
				
				AccountData[playerid][pMechanic] = SetTimerEx("SprayCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
				ShowProgressbar(playerid, "Modifying...", 10);
			}
			else
			{
				KillTimer(AccountData[playerid][pMechanic]);
				
				
				AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
				AccountData[playerid][pMechColor1] = 0;
				AccountData[playerid][pMechColor2] = 0;
				AccountData[playerid][pActivityTime] = 0;
				ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
				return 1;
			}
		}
		return 1;
	}
	if(dialogid == DIALOG_SERVICE_PAINTJOB)
	{
		if(response)
		{
			AccountData[playerid][pMechColor1] = floatround(strval(inputtext));
			
			if(AccountData[playerid][pMechColor1] < 0 || AccountData[playerid][pMechColor1] > 3)
				return ShowPlayerDialog(playerid, DIALOG_SERVICE_PAINTJOB, DIALOG_STYLE_INPUT, "Paintjob", "Enter the vehicle paintjob id:(0 - 2 | 3 - Remove paintJob)", "Paintjob", "Close");
			if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
			if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
			if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
			{	
				if(Inventory_Count(playerid, "Component") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
				Inventory_Remove(playerid, "Component", 30);
				ShowTDN(playerid, NOTIFICATION_INFO, "Anda mengganti paintjob kendaraan dengan "RED"30 component.");
				AccountData[playerid][pMechanic] = SetTimerEx("PaintjobCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
				ShowProgressbar(playerid, "Spraying...", 10);
			}
			else
			{
				KillTimer(AccountData[playerid][pMechanic]);
				
				
				AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
				AccountData[playerid][pMechColor1] = 0;
				AccountData[playerid][pMechColor2] = 0;
				AccountData[playerid][pActivityTime] = 0;
				ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
				return 1;
			}
		}
		return 1;
	}
	if(dialogid == DIALOG_SERVICE_WHEELS)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					AccountData[playerid][pMechColor1] = 1025;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 1:
				{
					AccountData[playerid][pMechColor1] = 1074;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 2:
				{
					AccountData[playerid][pMechColor1] = 1076;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 3:
				{
					AccountData[playerid][pMechColor1] = 1078;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 4:
				{
					AccountData[playerid][pMechColor1] = 1081;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 5:
				{
					AccountData[playerid][pMechColor1] = 1082;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 6:
				{
					AccountData[playerid][pMechColor1] = 1085;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 7:
				{
					AccountData[playerid][pMechColor1] = 1096;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 8:
				{
					AccountData[playerid][pMechColor1] = 1097;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 9:
				{
					AccountData[playerid][pMechColor1] = 1098;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 10:
				{
					AccountData[playerid][pMechColor1] = 1084;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 11:
				{
					AccountData[playerid][pMechColor1] = 1073;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 12:
				{
					AccountData[playerid][pMechColor1] = 1075;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 13:
				{
					AccountData[playerid][pMechColor1] = 1077;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 14:
				{
					AccountData[playerid][pMechColor1] = 1079;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 15:
				{
					AccountData[playerid][pMechColor1] = 1080;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 16:
				{
					AccountData[playerid][pMechColor1] = 1083;
					AccountData[playerid][pMechColor2] = 0;
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{	
						if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						Inventory_Remove(playerid, "Component", 25);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"25 component.");
						
						AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Modifying...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
			}
		}
		return 1;
	}
	if(dialogid == DIALOG_SERVICE_SPOILER)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 562 ||
						VehicleModel == 565 ||
						VehicleModel == 559 ||
						VehicleModel == 561 ||
						VehicleModel == 558 ||
						VehicleModel == 560)
						{
							if(VehicleModel == 562)
							{
								AccountData[playerid][pMechColor1] = 1147;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 565)
							{
								AccountData[playerid][pMechColor1] = 1049;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 559)
							{
								AccountData[playerid][pMechColor1] = 1162;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 561)
							{
								AccountData[playerid][pMechColor1] = 1058;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 558)
							{
								AccountData[playerid][pMechColor1] = 1164;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 560)
							{
								AccountData[playerid][pMechColor1] = 1138;
								AccountData[playerid][pMechColor2] = 0;
							}
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 1:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 562 ||
						VehicleModel == 565 ||
						VehicleModel == 559 ||
						VehicleModel == 561 ||
						VehicleModel == 558 ||
						VehicleModel == 560)
						{
							if(VehicleModel == 562)
							{
								AccountData[playerid][pMechColor1] = 1146;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 565)
							{
								AccountData[playerid][pMechColor1] = 1050;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 559)
							{
								AccountData[playerid][pMechColor1] = 1158;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 561)
							{
								AccountData[playerid][pMechColor1] = 1060;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 558)
							{
								AccountData[playerid][pMechColor1] = 1163;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 560)
							{
								AccountData[playerid][pMechColor1] = 1139;
								AccountData[playerid][pMechColor2] = 0;
							}
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 2:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 401 ||
						VehicleModel == 518 ||
						VehicleModel == 527 ||
						VehicleModel == 415 ||
						VehicleModel == 546 ||
						VehicleModel == 603 ||
						VehicleModel == 426 ||
						VehicleModel == 436 ||
						VehicleModel == 405 ||
						VehicleModel == 477 ||
						VehicleModel == 580 ||
						VehicleModel == 550 ||
						VehicleModel == 549)
						{
				
							AccountData[playerid][pMechColor1] = 1001;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 3:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 518 ||
						VehicleModel == 415 ||
						VehicleModel == 546 ||
						VehicleModel == 517 ||
						VehicleModel == 603 ||
						VehicleModel == 405 ||
						VehicleModel == 477 ||
						VehicleModel == 580 ||
						VehicleModel == 550 ||
						VehicleModel == 549)
						{
				
							AccountData[playerid][pMechColor1] = 1023;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 4:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 518 ||
						VehicleModel == 415 ||
						VehicleModel == 401 ||
						VehicleModel == 517 ||
						VehicleModel == 426 ||
						VehicleModel == 436 ||
						VehicleModel == 477 ||
						VehicleModel == 547 ||
						VehicleModel == 550 ||
						VehicleModel == 549)
						{
				
							AccountData[playerid][pMechColor1] = 1003;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 5:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 589 ||
						VehicleModel == 492 ||
						VehicleModel == 547 ||
						VehicleModel == 405)
						{
				
							AccountData[playerid][pMechColor1] = 1000;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 6:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 527 ||
						VehicleModel == 542 ||
						VehicleModel == 405)
						{
				
							AccountData[playerid][pMechColor1] = 1014;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 7:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 527 ||
						VehicleModel == 542)
						{
				
							AccountData[playerid][pMechColor1] = 1015;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 8:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 546 ||
						VehicleModel == 517)
						{
				
							AccountData[playerid][pMechColor1] = 1002;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
			}
		}
	}
	if(dialogid == DIALOG_SERVICE_HOODS)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(
						VehicleModel == 401 ||
						VehicleModel == 518 ||
						VehicleModel == 589 ||
						VehicleModel == 492 ||
						VehicleModel == 426 ||
						VehicleModel == 550)
						{
				
							AccountData[playerid][pMechColor1] = 1005;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 1:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(
						VehicleModel == 401 ||
						VehicleModel == 402 ||
						VehicleModel == 546 ||
						VehicleModel == 426 ||
						VehicleModel == 550)
						{
				
							AccountData[playerid][pMechColor1] = 1004;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 2:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 401)
						{
				
							AccountData[playerid][pMechColor1] = 1011;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 3:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 549)
						{
				
							AccountData[playerid][pMechColor1] = 1012;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
			}
		}
		return 1;
	}
	if(dialogid == DIALOG_SERVICE_VENTS)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 401 ||
						VehicleModel == 518 ||
						VehicleModel == 546 ||
						VehicleModel == 517 ||
						VehicleModel == 603 ||
						VehicleModel == 547 ||
						VehicleModel == 439 ||
						VehicleModel == 550 ||
						VehicleModel == 549)
						{
				
							AccountData[playerid][pMechColor1] = 1142;
							AccountData[playerid][pMechColor2] = 1143;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 1:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 401 ||
						VehicleModel == 518 ||
						VehicleModel == 589 ||
						VehicleModel == 546 ||
						VehicleModel == 517 ||
						VehicleModel == 603 ||
						VehicleModel == 439 ||
						VehicleModel == 550 ||
						VehicleModel == 549)
						{
				
							AccountData[playerid][pMechColor1] = 1144;
							AccountData[playerid][pMechColor2] = 1145;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
			}
		}
	}
	if(dialogid == DIALOG_SERVICE_LIGHTS)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 401 ||
						VehicleModel == 518 ||
						VehicleModel == 589 ||
						VehicleModel == 400 ||
						VehicleModel == 436 ||
						VehicleModel == 439)
						{
				
							AccountData[playerid][pMechColor1] = 1013;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 1:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 589 ||
						VehicleModel == 603 ||
						VehicleModel == 400)
						{
				
							AccountData[playerid][pMechColor1] = 1024;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
			}
		}
		return 1;
	}
	if(dialogid == DIALOG_SERVICE_EXHAUSTS)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 562 ||
						VehicleModel == 565 ||
						VehicleModel == 559 ||
						VehicleModel == 558 ||
						VehicleModel == 561 ||
						VehicleModel == 560)
						{
							if(VehicleModel == 562)
							{
								AccountData[playerid][pMechColor1] = 1034;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 565)
							{
								AccountData[playerid][pMechColor1] = 1046;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 559)
							{
								AccountData[playerid][pMechColor1] = 1065;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 561)
							{
								AccountData[playerid][pMechColor1] = 1064;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 560)
							{
								AccountData[playerid][pMechColor1] = 1028;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 558)
							{
								AccountData[playerid][pMechColor1] = 1089;
								AccountData[playerid][pMechColor2] = 0;
							}
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 1:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 562 ||
						VehicleModel == 565 ||
						VehicleModel == 559 ||
						VehicleModel == 558 ||
						VehicleModel == 561 ||
						VehicleModel == 560)
						{
							if(VehicleModel == 562)
							{
								AccountData[playerid][pMechColor1] = 1037;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 565)
							{
								AccountData[playerid][pMechColor1] = 1045;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 559)
							{
								AccountData[playerid][pMechColor1] = 1066;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 561)
							{
								AccountData[playerid][pMechColor1] = 1059;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 560)
							{
								AccountData[playerid][pMechColor1] = 1029;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 558)
							{
								AccountData[playerid][pMechColor1] = 1092;
								AccountData[playerid][pMechColor2] = 0;
							}
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 2:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 575 ||
						VehicleModel == 534 ||
						VehicleModel == 567 ||
						VehicleModel == 536 ||
						VehicleModel == 576 ||
						VehicleModel == 535)
						{
							if(VehicleModel == 575)
							{
								AccountData[playerid][pMechColor1] = 1044;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 534)
							{
								AccountData[playerid][pMechColor1] = 1126;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 567)
							{
								AccountData[playerid][pMechColor1] = 1129;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 536)
							{
								AccountData[playerid][pMechColor1] = 1104;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 576)
							{
								AccountData[playerid][pMechColor1] = 1113;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 535)
							{
								AccountData[playerid][pMechColor1] = 1136;
								AccountData[playerid][pMechColor2] = 0;
							}
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 3:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 575 ||
						VehicleModel == 534 ||
						VehicleModel == 567 ||
						VehicleModel == 536 ||
						VehicleModel == 576 ||
						VehicleModel == 535)
						{
							if(VehicleModel == 575)
							{
								AccountData[playerid][pMechColor1] = 1043;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 534)
							{
								AccountData[playerid][pMechColor1] = 1127;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 567)
							{
								AccountData[playerid][pMechColor1] = 1132;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 536)
							{
								AccountData[playerid][pMechColor1] = 1105;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 576)
							{
								AccountData[playerid][pMechColor1] = 1135;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 535)
							{
								AccountData[playerid][pMechColor1] = 1114;
								AccountData[playerid][pMechColor2] = 0;
							}
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 4:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(
						VehicleModel == 401 ||
						VehicleModel == 518 ||
						VehicleModel == 527 ||
						VehicleModel == 542 ||
						VehicleModel == 589 ||
						VehicleModel == 400 ||
						VehicleModel == 517 ||
						VehicleModel == 603 ||
						VehicleModel == 426 ||
						VehicleModel == 547 ||
						VehicleModel == 405 ||
						VehicleModel == 580 ||
						VehicleModel == 550 ||
						VehicleModel == 549 ||
						VehicleModel == 477)
						{
							
							AccountData[playerid][pMechColor1] = 1020;
							AccountData[playerid][pMechColor2] = 0;
								
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 5:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(
						VehicleModel == 527 ||
						VehicleModel == 542 ||
						VehicleModel == 400 ||
						VehicleModel == 426 ||
						VehicleModel == 436 ||
						VehicleModel == 547 ||
						VehicleModel == 405 ||
						VehicleModel == 477)
						{
							
							AccountData[playerid][pMechColor1] = 1021;
							AccountData[playerid][pMechColor2] = 0;
								
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 6:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 436)
						{
							
							AccountData[playerid][pMechColor1] = 1022;
							AccountData[playerid][pMechColor2] = 0;
								
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 7:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(
						VehicleModel == 518 ||
						VehicleModel == 415 ||
						VehicleModel == 542 ||
						VehicleModel == 546 ||
						VehicleModel == 400 ||
						VehicleModel == 517 ||
						VehicleModel == 603 ||
						VehicleModel == 426 ||
						VehicleModel == 436 ||
						VehicleModel == 547 ||
						VehicleModel == 405 ||
						VehicleModel == 550 ||
						VehicleModel == 549 ||
						VehicleModel == 477)
						{
							
							AccountData[playerid][pMechColor1] = 1019;
							AccountData[playerid][pMechColor2] = 0;
								
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 8:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(
						VehicleModel == 401 ||
						VehicleModel == 518 ||
						VehicleModel == 415 ||
						VehicleModel == 542 ||
						VehicleModel == 546 ||
						VehicleModel == 400 ||
						VehicleModel == 517 ||
						VehicleModel == 603 ||
						VehicleModel == 426 ||
						VehicleModel == 415 ||
						VehicleModel == 547 ||
						VehicleModel == 405 ||
						VehicleModel == 550 ||
						VehicleModel == 549 ||
						VehicleModel == 477)
						{
							
							AccountData[playerid][pMechColor1] = 1018;
							AccountData[playerid][pMechColor2] = 0;
								
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
			}
		}
		return 1;
	}
	if(dialogid == DIALOG_SERVICE_EXHAUSTS)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 562 ||
						VehicleModel == 565 ||
						VehicleModel == 559 ||
						VehicleModel == 558 ||
						VehicleModel == 561 ||
						VehicleModel == 560)
						{
							if(VehicleModel == 562)
							{
								AccountData[playerid][pMechColor1] = 1034;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 565)
							{
								AccountData[playerid][pMechColor1] = 1046;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 559)
							{
								AccountData[playerid][pMechColor1] = 1065;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 561)
							{
								AccountData[playerid][pMechColor1] = 1064;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 560)
							{
								AccountData[playerid][pMechColor1] = 1028;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 558)
							{
								AccountData[playerid][pMechColor1] = 1089;
								AccountData[playerid][pMechColor2] = 0;
							}
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 1:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 562 ||
						VehicleModel == 565 ||
						VehicleModel == 559 ||
						VehicleModel == 558 ||
						VehicleModel == 561 ||
						VehicleModel == 560)
						{
							if(VehicleModel == 562)
							{
								AccountData[playerid][pMechColor1] = 1037;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 565)
							{
								AccountData[playerid][pMechColor1] = 1045;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 559)
							{
								AccountData[playerid][pMechColor1] = 1066;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 561)
							{
								AccountData[playerid][pMechColor1] = 1059;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 560)
							{
								AccountData[playerid][pMechColor1] = 1029;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 558)
							{
								AccountData[playerid][pMechColor1] = 1092;
								AccountData[playerid][pMechColor2] = 0;
							}
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 2:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 575 ||
						VehicleModel == 534 ||
						VehicleModel == 567 ||
						VehicleModel == 536 ||
						VehicleModel == 576 ||
						VehicleModel == 535)
						{
							if(VehicleModel == 575)
							{
								AccountData[playerid][pMechColor1] = 1044;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 534)
							{
								AccountData[playerid][pMechColor1] = 1126;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 567)
							{
								AccountData[playerid][pMechColor1] = 1129;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 536)
							{
								AccountData[playerid][pMechColor1] = 1104;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 576)
							{
								AccountData[playerid][pMechColor1] = 1113;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 535)
							{
								AccountData[playerid][pMechColor1] = 1136;
								AccountData[playerid][pMechColor2] = 0;
							}
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 3:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 575 ||
						VehicleModel == 534 ||
						VehicleModel == 567 ||
						VehicleModel == 536 ||
						VehicleModel == 576 ||
						VehicleModel == 535)
						{
							if(VehicleModel == 575)
							{
								AccountData[playerid][pMechColor1] = 1043;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 534)
							{
								AccountData[playerid][pMechColor1] = 1127;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 567)
							{
								AccountData[playerid][pMechColor1] = 1132;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 536)
							{
								AccountData[playerid][pMechColor1] = 1105;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 576)
							{
								AccountData[playerid][pMechColor1] = 1135;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 535)
							{
								AccountData[playerid][pMechColor1] = 1114;
								AccountData[playerid][pMechColor2] = 0;
							}
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 4:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(
						VehicleModel == 401 ||
						VehicleModel == 518 ||
						VehicleModel == 527 ||
						VehicleModel == 542 ||
						VehicleModel == 589 ||
						VehicleModel == 400 ||
						VehicleModel == 517 ||
						VehicleModel == 603 ||
						VehicleModel == 426 ||
						VehicleModel == 547 ||
						VehicleModel == 405 ||
						VehicleModel == 580 ||
						VehicleModel == 550 ||
						VehicleModel == 549 ||
						VehicleModel == 477)
						{
							
							AccountData[playerid][pMechColor1] = 1020;
							AccountData[playerid][pMechColor2] = 0;
								
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 5:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(
						VehicleModel == 527 ||
						VehicleModel == 542 ||
						VehicleModel == 400 ||
						VehicleModel == 426 ||
						VehicleModel == 436 ||
						VehicleModel == 547 ||
						VehicleModel == 405 ||
						VehicleModel == 477)
						{
							
							AccountData[playerid][pMechColor1] = 1021;
							AccountData[playerid][pMechColor2] = 0;
								
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 6:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 436)
						{
							
							AccountData[playerid][pMechColor1] = 1022;
							AccountData[playerid][pMechColor2] = 0;
								
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 7:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(
						VehicleModel == 518 ||
						VehicleModel == 415 ||
						VehicleModel == 542 ||
						VehicleModel == 546 ||
						VehicleModel == 400 ||
						VehicleModel == 517 ||
						VehicleModel == 603 ||
						VehicleModel == 426 ||
						VehicleModel == 436 ||
						VehicleModel == 547 ||
						VehicleModel == 405 ||
						VehicleModel == 550 ||
						VehicleModel == 549 ||
						VehicleModel == 477)
						{
							
							AccountData[playerid][pMechColor1] = 1019;
							AccountData[playerid][pMechColor2] = 0;
								
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 8:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(
						VehicleModel == 401 ||
						VehicleModel == 518 ||
						VehicleModel == 415 ||
						VehicleModel == 542 ||
						VehicleModel == 546 ||
						VehicleModel == 400 ||
						VehicleModel == 517 ||
						VehicleModel == 603 ||
						VehicleModel == 426 ||
						VehicleModel == 415 ||
						VehicleModel == 547 ||
						VehicleModel == 405 ||
						VehicleModel == 550 ||
						VehicleModel == 549 ||
						VehicleModel == 477)
						{
							
							AccountData[playerid][pMechColor1] = 1018;
							AccountData[playerid][pMechColor2] = 0;
								
							Inventory_Remove(playerid, "Component", 24);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"24 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
			}
		}
		return 1;
	}
	if(dialogid == DIALOG_SERVICE_FRONT_BUMPERS)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 562 ||
						VehicleModel == 565 ||
						VehicleModel == 559 ||
						VehicleModel == 561 ||
						VehicleModel == 558 ||
						VehicleModel == 560)
						{
							if(VehicleModel == 562)
							{
								AccountData[playerid][pMechColor1] = 1171;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 565)
							{
								AccountData[playerid][pMechColor1] = 1153;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 559)
							{
								AccountData[playerid][pMechColor1] = 1160;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 561)
							{
								AccountData[playerid][pMechColor1] = 1155;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 558)
							{
								AccountData[playerid][pMechColor1] = 1166;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 560)
							{
								AccountData[playerid][pMechColor1] = 1169;
								AccountData[playerid][pMechColor2] = 0;
							}
							
							Inventory_Remove(playerid, "Component", 30);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"30 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 1:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 562 ||
						VehicleModel == 565 ||
						VehicleModel == 559 ||
						VehicleModel == 561 ||
						VehicleModel == 558 ||
						VehicleModel == 560)
						{
							if(VehicleModel == 562)
							{
								AccountData[playerid][pMechColor1] = 1172;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 565)
							{
								AccountData[playerid][pMechColor1] = 1152;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 559)
							{
								AccountData[playerid][pMechColor1] = 1173;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 561)
							{
								AccountData[playerid][pMechColor1] = 1157;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 558)
							{
								AccountData[playerid][pMechColor1] = 1165;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 560)
							{
								AccountData[playerid][pMechColor1] = 1170;
								AccountData[playerid][pMechColor2] = 0;
							}
							
							Inventory_Remove(playerid, "Component", 30);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"30 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 2:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 575 ||
						VehicleModel == 534 ||
						VehicleModel == 567 ||
						VehicleModel == 536 ||
						VehicleModel == 576 ||
						VehicleModel == 535)
						{
							if(VehicleModel == 575)
							{
								AccountData[playerid][pMechColor1] = 1174;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 534)
							{
								AccountData[playerid][pMechColor1] = 1179;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 567)
							{
								AccountData[playerid][pMechColor1] = 1189;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 536)
							{
								AccountData[playerid][pMechColor1] = 1182;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 576)
							{
								AccountData[playerid][pMechColor1] = 1191;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 535)
							{
								AccountData[playerid][pMechColor1] = 1115;
								AccountData[playerid][pMechColor2] = 0;
							}
							
							Inventory_Remove(playerid, "Component", 30);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"30 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 3:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 575 ||
						VehicleModel == 534 ||
						VehicleModel == 567 ||
						VehicleModel == 536 ||
						VehicleModel == 576 ||
						VehicleModel == 535)
						{
							if(VehicleModel == 575)
							{
								AccountData[playerid][pMechColor1] = 1175;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 534)
							{
								AccountData[playerid][pMechColor1] = 1185;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 567)
							{
								AccountData[playerid][pMechColor1] = 1188;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 536)
							{
								AccountData[playerid][pMechColor1] = 1181;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 576)
							{
								AccountData[playerid][pMechColor1] = 1190;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 535)
							{
								AccountData[playerid][pMechColor1] = 1116;
								AccountData[playerid][pMechColor2] = 0;
							}
							
							Inventory_Remove(playerid, "Component", 30);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"30 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
			}
		}
		return 1;
	}
	if(dialogid == DIALOG_SERVICE_REAR_BUMPERS)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]); 
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 562 ||
						VehicleModel == 565 ||
						VehicleModel == 559 ||
						VehicleModel == 561 ||
						VehicleModel == 558 ||
						VehicleModel == 560)
						{
							if(VehicleModel == 562)
							{
								AccountData[playerid][pMechColor1] = 1149;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 565)
							{
								AccountData[playerid][pMechColor1] = 1150;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 559)
							{
								AccountData[playerid][pMechColor1] = 1159;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 561)
							{
								AccountData[playerid][pMechColor1] = 1154;
								AccountData[playerid][pMechColor2] = 0; 
							}
							if(VehicleModel == 558)
							{
								AccountData[playerid][pMechColor1] = 1168;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 560)
							{
								AccountData[playerid][pMechColor1] = 1141;
								AccountData[playerid][pMechColor2] = 0;
							}
							
							Inventory_Remove(playerid, "Component", 30);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"30 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 1:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 562 ||
						VehicleModel == 565 ||
						VehicleModel == 559 ||
						VehicleModel == 561 ||
						VehicleModel == 558 ||
						VehicleModel == 560)
						{
							if(VehicleModel == 562)
							{
								AccountData[playerid][pMechColor1] = 1148;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 565)
							{
								AccountData[playerid][pMechColor1] = 1151;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 559)
							{
								AccountData[playerid][pMechColor1] = 1161;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 561)
							{
								AccountData[playerid][pMechColor1] = 1156;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 558)
							{
								AccountData[playerid][pMechColor1] = 1167;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 560)
							{
								AccountData[playerid][pMechColor1] = 1140;
								AccountData[playerid][pMechColor2] = 0;
							}
							
							Inventory_Remove(playerid, "Component", 30);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"30 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 2:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 575 ||
						VehicleModel == 534 ||
						VehicleModel == 567 ||
						VehicleModel == 536 ||
						VehicleModel == 576 ||
						VehicleModel == 535)
						{
							if(VehicleModel == 575)
							{
								AccountData[playerid][pMechColor1] = 1176;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 534)
							{
								AccountData[playerid][pMechColor1] = 1180;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 567)
							{
								AccountData[playerid][pMechColor1] = 1187;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 536)
							{
								AccountData[playerid][pMechColor1] = 1184;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 576)
							{
								AccountData[playerid][pMechColor1] = 1192;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 535)
							{
								AccountData[playerid][pMechColor1] = 1109;
								AccountData[playerid][pMechColor2] = 0;
							}
							
							Inventory_Remove(playerid, "Component", 30);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"30 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 3:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 575 ||
						VehicleModel == 534 ||
						VehicleModel == 567 ||
						VehicleModel == 536 ||
						VehicleModel == 576 ||
						VehicleModel == 535)
						{
							if(VehicleModel == 575)
							{
								AccountData[playerid][pMechColor1] = 1177;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 534)
							{
								AccountData[playerid][pMechColor1] = 1178;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 567)
							{
								AccountData[playerid][pMechColor1] = 1186;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 536)
							{
								AccountData[playerid][pMechColor1] = 1183;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 576)
							{
								AccountData[playerid][pMechColor1] = 1193;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 535)
							{
								AccountData[playerid][pMechColor1] = 1110;
								AccountData[playerid][pMechColor2] = 0;
							}
							
							Inventory_Remove(playerid, "Component", 30);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"30 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
			}
		}
		return 1;
	}
	if(dialogid == DIALOG_SERVICE_ROOFS)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 562 ||
						VehicleModel == 565 ||
						VehicleModel == 559 ||
						VehicleModel == 561 ||
						VehicleModel == 558 ||
						VehicleModel == 560)
						{
							if(VehicleModel == 562)
							{
								AccountData[playerid][pMechColor1] = 1038;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 565)
							{
								AccountData[playerid][pMechColor1] = 1054;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 559)
							{
								AccountData[playerid][pMechColor1] = 1067;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 561)
							{
								AccountData[playerid][pMechColor1] = 1055;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 558)
							{
								AccountData[playerid][pMechColor1] = 1088;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 560)
							{
								AccountData[playerid][pMechColor1] = 1032;
								AccountData[playerid][pMechColor2] = 0;
							}
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 1:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 562 ||
						VehicleModel == 565 ||
						VehicleModel == 559 ||
						VehicleModel == 561 ||
						VehicleModel == 558 ||
						VehicleModel == 560)
						{
							if(VehicleModel == 562)
							{
								AccountData[playerid][pMechColor1] = 1038;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 565)
							{
								AccountData[playerid][pMechColor1] = 1053;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 559)
							{
								AccountData[playerid][pMechColor1] = 1068;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 561)
							{
								AccountData[playerid][pMechColor1] = 1061;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 558)
							{
								AccountData[playerid][pMechColor1] = 1091;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 560)
							{
								AccountData[playerid][pMechColor1] = 1033;
								AccountData[playerid][pMechColor2] = 0;
							}
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 2:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 567 ||
						VehicleModel == 536)
						{
							if(VehicleModel == 567)
							{
								AccountData[playerid][pMechColor1] = 1130;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 536)
							{
								AccountData[playerid][pMechColor1] = 1128;
								AccountData[playerid][pMechColor2] = 0;
							}
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 3:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 567 ||
						VehicleModel == 536)
						{
							if(VehicleModel == 567)
							{
								AccountData[playerid][pMechColor1] = 1131;
								AccountData[playerid][pMechColor2] = 0;
							}
							if(VehicleModel == 536)
							{
								AccountData[playerid][pMechColor1] = 1103;
								AccountData[playerid][pMechColor2] = 0;
							}
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 4:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(
						VehicleModel == 401 ||
						VehicleModel == 518 ||
						VehicleModel == 589 ||
						VehicleModel == 492 ||
						VehicleModel == 546 ||
						VehicleModel == 603 ||
						VehicleModel == 426 ||
						VehicleModel == 436 ||
						VehicleModel == 580 ||
						VehicleModel == 550 ||
						VehicleModel == 477)
						{

							AccountData[playerid][pMechColor1] = 1006;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 21);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"21 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
			}
		}
		return 1;
	}
	if(dialogid == DIALOG_SERVICE_SIDE_SKIRTS)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]); 
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 27) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 562 ||
						VehicleModel == 565 ||
						VehicleModel == 559 ||
						VehicleModel == 561 ||
						VehicleModel == 558 ||
						VehicleModel == 560)
						{
							if(VehicleModel == 562)
							{
								AccountData[playerid][pMechColor1] = 1036;
								AccountData[playerid][pMechColor2] = 1040;
							}
							if(VehicleModel == 565)
							{
								AccountData[playerid][pMechColor1] = 1047;
								AccountData[playerid][pMechColor2] = 1051;
							}
							if(VehicleModel == 559)
							{
								AccountData[playerid][pMechColor1] = 1069;
								AccountData[playerid][pMechColor2] = 1071;
							}
							if(VehicleModel == 561)
							{
								AccountData[playerid][pMechColor1] = 1056;
								AccountData[playerid][pMechColor2] = 1062;
							}
							if(VehicleModel == 558)
							{
								AccountData[playerid][pMechColor1] = 1090;
								AccountData[playerid][pMechColor2] = 1094;
							}
							if(VehicleModel == 560)
							{
								AccountData[playerid][pMechColor1] = 1026;
								AccountData[playerid][pMechColor2] = 1027;
							}
							
							Inventory_Remove(playerid, "Component", 27); 
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"27 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 1:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 27) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 562 ||
						VehicleModel == 565 ||
						VehicleModel == 559 ||
						VehicleModel == 561 ||
						VehicleModel == 558 ||
						VehicleModel == 560)
						{
							if(VehicleModel == 562)
							{
								AccountData[playerid][pMechColor1] = 1039;
								AccountData[playerid][pMechColor2] = 1041;
							}
							if(VehicleModel == 565)
							{
								AccountData[playerid][pMechColor1] = 1048;
								AccountData[playerid][pMechColor2] = 1052;
							}
							if(VehicleModel == 559)
							{
								AccountData[playerid][pMechColor1] = 1070;
								AccountData[playerid][pMechColor2] = 1072;
							}
							if(VehicleModel == 561)
							{
								AccountData[playerid][pMechColor1] = 1057;
								AccountData[playerid][pMechColor2] = 1063;
							}
							if(VehicleModel == 558)
							{
								AccountData[playerid][pMechColor1] = 1093;
								AccountData[playerid][pMechColor2] = 1095;
							}
							if(VehicleModel == 560)
							{
								AccountData[playerid][pMechColor1] = 1031;
								AccountData[playerid][pMechColor2] = 1030;
							}
							
							Inventory_Remove(playerid, "Component", 27);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"27 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 2:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 27) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 575 ||
						VehicleModel == 536 ||
						VehicleModel == 576 ||
						VehicleModel == 567)
						{
							if(VehicleModel == 575)
							{
								AccountData[playerid][pMechColor1] = 1042;
								AccountData[playerid][pMechColor2] = 1099;
							}
							if(VehicleModel == 536)
							{
								AccountData[playerid][pMechColor1] = 1108;
								AccountData[playerid][pMechColor2] = 1107;
							}
							if(VehicleModel == 576)
							{
								AccountData[playerid][pMechColor1] = 1134;
								AccountData[playerid][pMechColor2] = 1137;
							}
							if(VehicleModel == 567)
							{
								AccountData[playerid][pMechColor1] = 1102;
								AccountData[playerid][pMechColor2] = 1133;
							}
							
							Inventory_Remove(playerid, "Component", 27);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"27 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 3:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 27) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 534)
						{
				
							AccountData[playerid][pMechColor1] = 1102;
							AccountData[playerid][pMechColor2] = 1101;
							
							Inventory_Remove(playerid, "Component", 27);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"27 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 4:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 27) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 534)
						{
				
							AccountData[playerid][pMechColor1] = 1106;
							AccountData[playerid][pMechColor2] = 1124;
							
							Inventory_Remove(playerid, "Component", 27);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"27 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 5:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 27) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 535)
						{
				
							AccountData[playerid][pMechColor1] = 1118;
							AccountData[playerid][pMechColor2] = 1120;
							
							Inventory_Remove(playerid, "Component", 27);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"27 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 6:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 27) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 535)
						{
				
							AccountData[playerid][pMechColor1] = 1119;
							AccountData[playerid][pMechColor2] = 1121;
							
							Inventory_Remove(playerid, "Component", 27);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"27 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 7:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 27) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(
						VehicleModel == 401 ||
						VehicleModel == 518 ||
						VehicleModel == 527 ||
						VehicleModel == 415 ||
						VehicleModel == 589 ||
						VehicleModel == 546 ||
						VehicleModel == 517 ||
						VehicleModel == 603 ||
						VehicleModel == 436 ||
						VehicleModel == 439 ||
						VehicleModel == 580 ||
						VehicleModel == 549 ||
						VehicleModel == 477)
						{
				
							AccountData[playerid][pMechColor1] = 1007;
							AccountData[playerid][pMechColor2] = 1017;
							
							Inventory_Remove(playerid, "Component", 27);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"27 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
			}
		}
		return 1;
	}
	if(dialogid == DIALOG_SERVICE_BULLBARS)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 534)
						{
				
							AccountData[playerid][pMechColor1] = 1100;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 15);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"15 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 1:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 534)
						{
				
							AccountData[playerid][pMechColor1] = 1123;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 15);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"15 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 2:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 534)
						{
				
							AccountData[playerid][pMechColor1] = 1125;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 15);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"15 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 3:
				{
					new VehicleModel = GetVehicleModel(AccountData[playerid][pMechVeh]);
					if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						if(Inventory_Count(playerid, "Component") < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(VehicleModel == 534)
						{
				
							AccountData[playerid][pMechColor1] = 1117;
							AccountData[playerid][pMechColor2] = 0;
							
							Inventory_Remove(playerid, "Component", 15);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"15 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle is not supported!");
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pMechColor1] = 0;
						AccountData[playerid][pMechColor2] = 0;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
			}
		}
		return 1;
	}
	//--------[ DIALOG SERVICE WORKSHOP]
	if(dialogid == WORKSHOP_SERVICE)
	{
		new wid = AccountData[playerid][pWorkshop];
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						new Float:health, comp;
						GetVehicleHealth(AccountData[playerid][pMechVeh], health);
						if(health > 2000.0) health = 2000.0;
						if(health > 1000.0) health = 2000.0;
						if(health > 0.0) health *= -1;
						comp = floatround(health, floatround_round) / 10 + 100;
						if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
						if(Inventory_Count(playerid, "Component") < comp) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(comp <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle can't be fixing.");
						Inventory_Remove(playerid, "Component", comp);
						SendClientMessageEx(playerid, COLOR_CLIENT, "Anda memperbaiki mesin kendaraan dengan "RED"%d component.", comp);
						AccountData[playerid][pMechanic] = SetTimerEx("EngineFix", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Fixing...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 1:
				{
					if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
					if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
					{
						new panels, doors, light, tires, comp;
						
						GetVehicleDamageStatus(AccountData[playerid][pMechVeh], panels, doors, light, tires);
						new cpanels = panels / 1000000;
						new lights = light / 2;
						new pintu;
						if(doors != 0) pintu = 5;
						if(doors == 0) pintu = 0;
						comp = cpanels + lights + pintu + 20;
						if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
						if(Inventory_Count(playerid, "Component") < comp) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
						if(comp <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "This vehicle can't be fixing.");
						Inventory_Remove(playerid, "Component", comp);
						SendClientMessageEx(playerid, COLOR_CLIENT, "Anda memperbaiki body kendaraan dengan "RED"%d component.", comp);
						
						AccountData[playerid][pMechanic] = SetTimerEx("BodyFix", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
						ShowProgressbar(playerid, "Fixing...", 10);
					}
					else
					{
						KillTimer(AccountData[playerid][pMechanic]);
						
						AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
						AccountData[playerid][pActivityTime] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
						return 1;
					}
				}
				case 2:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{
							if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
							if(Inventory_Count(playerid, "Component") < 300) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							Inventory_Remove(playerid, "Component", 300);
							AccountData[playerid][pMechanic] = SetTimerEx("EngineUpgrade", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Fixing...", 10);
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");

							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 3:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{
							if(Inventory_Count(playerid, "Component") < 12) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							ShowPlayerDialog(playerid, DIALOG_SERVICE_COLOR, DIALOG_STYLE_INPUT, "Color ID 1", "Enter the color id 1:(0 - 255)", "Next", "Close");
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 4:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
					
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{
							if(Inventory_Count(playerid, "Component") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							ShowPlayerDialog(playerid, DIALOG_SERVICE_PAINTJOB, DIALOG_STYLE_INPUT, "Paintjob", "Enter the vehicle paintjob id:(0 - 2 | 3 - Remove paintJob)", "Paintjob", "Close");
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 5:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
					
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{
							if(Inventory_Count(playerid, "Component") < 25) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							ShowPlayerDialog(playerid, DIALOG_SERVICE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar", "Confirm", "back");
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 6:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
					
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{
							if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							ShowPlayerDialog(playerid, DIALOG_SERVICE_SPOILER,DIALOG_STYLE_LIST,"Choose below","Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n","Choose","back");
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 7:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
					
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{
							if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							ShowPlayerDialog(playerid, DIALOG_SERVICE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n", "Confirm", "back");
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 8:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
					
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{
							if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							ShowPlayerDialog(playerid, DIALOG_SERVICE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n", "Confirm", "back");
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 9:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
					
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{
							if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							ShowPlayerDialog(playerid, DIALOG_SERVICE_LIGHTS, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n", "Confirm", "back");
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 10:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
					
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{
							if(Inventory_Count(playerid, "Component") < 24) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							ShowPlayerDialog(playerid, DIALOG_SERVICE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust", "Confirm", "back");
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 11:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
					
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{
							if(Inventory_Count(playerid, "Component") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							ShowPlayerDialog(playerid, DIALOG_SERVICE_FRONT_BUMPERS, DIALOG_STYLE_LIST, "Front bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper", "Confirm", "back");
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 12:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
					
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{
							if(Inventory_Count(playerid, "Component") < 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							ShowPlayerDialog(playerid, DIALOG_SERVICE_REAR_BUMPERS, DIALOG_STYLE_LIST, "Rear bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper", "Confirm", "back");
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 13:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
					
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{
							if(Inventory_Count(playerid, "Component") < 21) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							ShowPlayerDialog(playerid, DIALOG_SERVICE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop", "Confirm", "back");
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 14:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
					
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{
							if(Inventory_Count(playerid, "Component") < 27) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							ShowPlayerDialog(playerid, DIALOG_SERVICE_SIDE_SKIRTS, DIALOG_STYLE_LIST, "Side skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt", "Confirm", "back");
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
					ShowTDN(playerid, NOTIFICATION_INFO, "Side blm ada.");
				}
				case 15:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
					
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{
							if(Inventory_Count(playerid, "Component") < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							ShowPlayerDialog(playerid, DIALOG_SERVICE_BULLBARS, DIALOG_STYLE_LIST, "Bull bars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar", "Confirm", "back");
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 16:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
					
						AccountData[playerid][pMechColor1] = 1086;
						AccountData[playerid][pMechColor2] = 0;
						
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{	
							if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
							if(Inventory_Count(playerid, "Component") < 45) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							Inventory_Remove(playerid, "Component", 45);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"45 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pMechColor1] = 0;
							AccountData[playerid][pMechColor2] = 0;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 17:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
					
						AccountData[playerid][pMechColor1] = 1087;
						AccountData[playerid][pMechColor2] = 0;
						
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{	
							if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
							if(Inventory_Count(playerid, "Component") < 45) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							Inventory_Remove(playerid, "Component", 45);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"45 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pMechColor1] = 0;
							AccountData[playerid][pMechColor2] = 0;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 18:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
						AccountData[playerid][pMechColor1] = 1009;
						AccountData[playerid][pMechColor2] = 0;
						
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{	
							if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
							if(Inventory_Count(playerid, "Component") < 75) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							Inventory_Remove(playerid, "Component", 75);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"75 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pMechColor1] = 0;
							AccountData[playerid][pMechColor2] = 0;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 19:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
					
						AccountData[playerid][pMechColor1] = 1008;
						AccountData[playerid][pMechColor2] = 0;
						
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{	
							if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
							if(Inventory_Count(playerid, "Component") < 112) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							Inventory_Remove(playerid, "Component", 112);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"112 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pMechColor1] = 0;
							AccountData[playerid][pMechColor2] = 0;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 20:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
						AccountData[playerid][pMechColor1] = 1010;
						AccountData[playerid][pMechColor2] = 0;
						
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{	
							if(AccountData[playerid][pProgress] == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki activity Progress, silahkan tunggu");
							if(Inventory_Count(playerid, "Component") < 150) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							Inventory_Remove(playerid, "Component", 150);
							ShowTDN(playerid, NOTIFICATION_INFO, "Anda memodif kendaraan dengan "RED"150 component.");
							
							AccountData[playerid][pMechanic] = SetTimerEx("ModifCar", 10000, false, "id", playerid, AccountData[playerid][pMechVeh]);
							ShowProgressbar(playerid, "Modifying...", 10);
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pMechColor1] = 0;
							AccountData[playerid][pMechColor2] = 0;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
				case 21:
				{
					if(IsPlayerInRangeOfPoint(playerid, 50.0, wData[wid][wExtposX], wData[wid][wExtposY], wData[wid][wExtposZ]))
					{
						if(AccountData[playerid][pActivityTime] > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "You already checking vehicle!");
						if(!IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada didalam kendaraan!");
						if(GetNearestVehicleToPlayer(playerid, 3.8, false) == AccountData[playerid][pMechVeh])
						{
							if(Inventory_Count(playerid, "Component") < 135) return ShowTDN(playerid, NOTIFICATION_ERROR, "Component anda kurang!");
							Dialog_Show(playerid, SelectNeon, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Install Neon", "Red Neon\nBlue Neon\nGreen Neon\nYellow Neon\nPink Neon\nWhite Neon\n"RED"Remove Neon", "Install", "Close");
						}
						else
						{
							KillTimer(AccountData[playerid][pMechanic]);
							
							
							AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
							AccountData[playerid][pActivityTime] = 0;
							ShowTDN(playerid, NOTIFICATION_INFO, "Kendaraan pelanggan anda yang sebelumnya sudah terlalu jauh.");
							return 1;
						}
					}
					else return ShowTDN(playerid, NOTIFICATION_ERROR, "kamu harus berjarak 10 meter dari point workshopmu");
				}
			}
		}
	}
	if(dialogid == GPS_NEAREST_WORKSHOP)
	{
		if(response)
		{
			new id = ReturnWorkshopNearestID((listitem+1));
			DisablePlayerRaceCheckpoint(playerid);
			//SetPlayerWaypoint(playerid, "WORKSHOP", wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]);
			SetPlayerRaceCheckpoint(playerid, 1, wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ], 0.0, 0.0, 0.0, 7.0); //GPS WORKSHOP
			SendClientMessageEx(playerid, COLOR_CLIENT, "GPS Active! Workshop yang berjarak %0.0fm berlokasi di %s telah ditandai", GetPlayerDistanceFromPoint(playerid, wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]), GetLocation(wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]));
			
			////(playerid, wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ], COLOR_BLUE);
		}
	}
	return 1;
}

Dialog:SelectNeon(playerid, response, listitem, inputtext[])
{
    if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
    if(!response) return 1;
    switch(listitem)
    {
        case 0:
		{
            new vehid = GetPlayerVehicleID(playerid);
			foreach(new i : PvtVehicles)
			{
                if(vehid == PlayerVehicle[i][pVehPhysic])
                {
                    SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, RED_NEON, 0);

                    PlayerVehicle[i][pVehNeon] = RED_NEON;

                    if(PlayerVehicle[i][pVehNeon] == 0)
                    {
                        PlayerVehicle[i][cTogNeon] = 0;
                    }
                    else 
                    {
                        PlayerVehicle[i][cTogNeon] = 1;
                    }
                }
			}
            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		case 1:
		{
			new vehid = GetPlayerVehicleID(playerid);
			foreach(new i : PvtVehicles)
			{
                if(vehid == PlayerVehicle[i][pVehPhysic])
                {
                    SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, BLUE_NEON, 0);

                    PlayerVehicle[i][pVehNeon] = BLUE_NEON;

                    if(PlayerVehicle[i][pVehNeon] == 0)
                    {
                        PlayerVehicle[i][cTogNeon] = 0;
                    }
                    else 
                    {
                        PlayerVehicle[i][cTogNeon] = 1;
                    }
                }
			}
            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		case 2:
		{
            new vehid = GetPlayerVehicleID(playerid);
			foreach(new i : PvtVehicles)
			{
                if(vehid == PlayerVehicle[i][pVehPhysic])
                {
                    SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, GREEN_NEON, 0);

                    PlayerVehicle[i][pVehNeon] = GREEN_NEON;

                    if(PlayerVehicle[i][pVehNeon] == 0)
                    {
                        PlayerVehicle[i][cTogNeon] = 0;
                    }
                    else 
                    {
                        PlayerVehicle[i][cTogNeon] = 1;
                    }
                }
			}
            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		case 3:
		{
            new vehid = GetPlayerVehicleID(playerid);
			foreach(new i : PvtVehicles)
			{
                if(vehid == PlayerVehicle[i][pVehPhysic])
                {
                    SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, YELLOW_NEON, 0);

                    PlayerVehicle[i][pVehNeon] = YELLOW_NEON;

                    if(PlayerVehicle[i][pVehNeon] == 0)
                    {
                        PlayerVehicle[i][cTogNeon] = 0;
                    }
                    else 
                    {
                        PlayerVehicle[i][cTogNeon] = 1;
                    }
                }
			}
            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		case 4:
		{
            new vehid = GetPlayerVehicleID(playerid);
			foreach(new i : PvtVehicles)
			{
                if(vehid == PlayerVehicle[i][pVehPhysic])
                {
                    SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, PINK_NEON, 0);

                    PlayerVehicle[i][pVehNeon] = PINK_NEON;

                    if(PlayerVehicle[i][pVehNeon] == 0)
                    {
                        PlayerVehicle[i][cTogNeon] = 0;
                    }
                    else 
                    {
                        PlayerVehicle[i][cTogNeon] = 1;
                    }
                }
			}
            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
		case 5:
		{
            new vehid = GetPlayerVehicleID(playerid);
			foreach(new i : PvtVehicles)
			{
                if(vehid == PlayerVehicle[i][pVehPhysic])
                {
                    SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, WHITE_NEON, 0);

                    PlayerVehicle[i][pVehNeon] = WHITE_NEON;

                    if(PlayerVehicle[i][pVehNeon] == 0)
                    {
                        PlayerVehicle[i][cTogNeon] = 0;
                    }
                    else 
                    {
                        PlayerVehicle[i][cTogNeon] = 1;
                    }
                }
			}
            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		}
        case 6:
        {
            new vehid = GetPlayerVehicleID(playerid),
            index = RETURN_INVALID_VEHICLE_ID;
                
            if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
            {
                if(IsValidVehicle(vehid))
                {
                    SetVehicleNeonLights(vehid, false, PlayerVehicle[index][pVehNeon], 0);
                    RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehNeon]);
                    PlayerVehicle[index][pVehNeon] = 0;
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                    SavePlayerVehicle(index);
                }
            }
        }
	}
    return 1;
}