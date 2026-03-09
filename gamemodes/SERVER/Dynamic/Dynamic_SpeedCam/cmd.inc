SSCANF:SpeedMenu(string[])
{
    if(!strcmp(string, "create", true)) return 1;
    else if(!strcmp(string, "delete", true)) return 2;
    else if(!strcmp(string, "position", true)) return 3;
    else if(!strcmp(string, "speed", true)) return 4;
    return 0;
}

CMD:spm(playerid, params[])
{
    return callcmd::speedmenu(playerid, params);
}

CMD:gotospeedcam(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 1)
        return PermissionError(playerid);
    
    new id;
    if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotospeedcam [Speed Cam ID]");
    if(!Speed_IsExists(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Speed Cam tidak ada!");

    SetPlayerPos(playerid, SpeedData[id][speedPos][0], SpeedData[id][speedPos][1], SpeedData[id][speedPos][2]);
    SetPlayerFacingAngle(playerid, SpeedData[id][speedPos][3]);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Teleportasi ke Speed Cam "YELLOW"ID: %d", AccountData[playerid][pAdminname], id);
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
    return 1;
}

CMD:speedmenu(playerid, params[])
{
    static index, action, nextParams[128];

    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    if(sscanf(params, "k<SpeedMenu>S()[128]", action, nextParams))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/speedmenu [create/delete/position/speed]");
    
    switch(action)
    {
        case 1: // create
        {
            new speed;

            if(sscanf(nextParams, "d", speed))
                return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/speedmenu [max speed]");
            
            if((index = Speed_Create(playerid, speed)) != -1) SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Berhasil membuat Speed Cam "YELLOW"ID: %d", AccountData[playerid][pAdminname], index);
            else ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah Speed Cam sudah mencapai batas limit!");
        }
        case 2: //delete
        {
            if(sscanf(nextParams, "d", index))
                return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/speedmenu delete [Speed Cam ID]");
            
            if(Speed_Delete(index)) SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Berhasil menghapus Speed Cam "YELLOW"ID: %d", AccountData[playerid][pAdminname], index);
            else ShowTDN(playerid, NOTIFICATION_ERROR, "ID Speed Cam tidak ada!");
        }
        case 3: // position
        {
            if(sscanf(nextParams, "d", index))
                return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/speedmenu position [Speed Cam ID]");

            if(!Speed_IsExists(index))
                return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Speed Cam tidak ada!");
            
            GetPlayerPos(playerid, SpeedData[index][speedPos][0], SpeedData[index][speedPos][1], SpeedData[index][speedPos][2]);
            GetPlayerFacingAngle(playerid, SpeedData[index][speedPos][3]);

            new Float:x, Float:y;
            GetXYInFrontOfPlayer(playerid, x, y, 1.5);
            SetPlayerPos(playerid, x, y, SpeedData[index][speedPos][2]);

            Speed_Sync(index);
            Speed_Save(index);
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Berhasil memindahkan Speed Cam "YELLOW"ID %d", AccountData[playerid][pAdminname], index);
        }
        case 4: //spedd
        {
            new speed;

			if(sscanf(nextParams, "dd", index, speed))
				return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/speedmenu speed [speed cam ID (/near)] [max speed]");

			if(!Speed_IsExists(index))
				return ShowTDN(playerid, NOTIFICATION_ERROR, "ID speed cam yang kamu input tidak terdaftar!");

			if(speed < 50 || speed > 200)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Batas kecepatan hanya 50 sampai 200 km/h");

			SpeedData[index][speedMax] = speed;
			Speed_Sync(index, true);
			Speed_Save(index, true);

            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Sukses mengubah kecepatan Speed Cam "YELLOW"id: %d "WHITE"menjadi "ORANGE"%d km/h.", AccountData[playerid][pAdminname], index, speed);
        }
    }
    return 1;
}

CMD:togspeedtrap(playerid, params[])
{
	if(AccountData[playerid][pFaction] != FACTION_POLISI)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu bukan seorang polisi!");

	SetPlayerToggleSpeedTrap(playerid, !IsPlayerToggleSpeedTrap(playerid));
	ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Speedtrap log %s", IsPlayerToggleSpeedTrap(playerid) ? (""RED"disabled") : (""GREEN"enable")));
	return 1;
}