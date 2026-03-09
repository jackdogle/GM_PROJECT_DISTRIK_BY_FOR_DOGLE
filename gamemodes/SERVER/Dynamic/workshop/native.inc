Workshop_Save(id)
{
	new dquery[2048];
	format(dquery, sizeof(dquery), "UPDATE workshop SET name='%s', leader='%s', price='%d', status='%d',extposx='%f', extposy='%f', extposz='%f', extposa='%f'",
	wData[id][wName],
	wData[id][wLeader],
	wData[id][wPrice],
	wData[id][wStatus],
	wData[id][wExtposX],
	wData[id][wExtposY],
	wData[id][wExtposZ],
	wData[id][wExtposA]);

	format(dquery, sizeof(dquery), "%s, money='%d', component='%d' WHERE ID='%d'",
	dquery,
	wData[id][wMoney],
	wData[id][wComponent],
	id);

	return mysql_tquery(g_SQL, dquery);
}


Workshop_Refresh(id)
{
	if(id != -1)
	{
		if(IsValidDynamic3DTextLabel(wData[id][wLabel]))
            DestroyDynamic3DTextLabel(wData[id][wLabel]);

        if(IsValidDynamicPickup(wData[id][wPickup]))
            DestroyDynamicPickup(wData[id][wPickup]);

        if(IsValidDynamicMapIcon(wData[id][wIcon]))
        	DestroyDynamicMapIcon(wData[id][wIcon]);

		new status[128];
		if(wData[id][wStatus] == 1)
		{
			status = "{FF0000}Closed";
		}
		else
		{
			status = "{00FF00}Opened";
		}
		new tstr[254];
        if(strcmp(wData[id][wLeader], "-"))
        {
			format(tstr, sizeof(tstr), "[WORKSHOP ID: %d]\n{ffffff}Workshop Name: {00ff00}%s\n{ffffff}Workshop Status: %s\n{ffffff}Owned by %s\n/wsstorage ", id, wData[id][wName], status, wData[id][wLeader]);
            wData[id][wPickup] = CreateDynamicPickup(1239, 23, wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]+0.2, 0, 0, _, 50.0);
            wData[id][wLabel] = CreateDynamic3DTextLabel(tstr, COLOR_YELLOW, wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]+0.7, 5.0);
            wData[id][wIcon] = CreateDynamicMapIcon(wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ], 27, -1, -1, -1, -1, 100.0);
        }
		else
		{
			format(tstr, sizeof(tstr), "[WORKSHOP ID: %d]\n{00FF00}This workshop for sell\n{FFFFFF}Location: {FFFF00}%s\n{FFFFFF}Price: {00FF00}%s\n"WHITE_E"Type /buy to purchase", id, GetLocation(wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]), FormatNumber(wData[id][wPrice]));
            wData[id][wPickup] = CreateDynamicPickup(1239, 23, wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]+0.2, 0, 0, _, 50.0);
            wData[id][wLabel] = CreateDynamic3DTextLabel(tstr, COLOR_YELLOW, wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]+0.7, 5.0);
            wData[id][wIcon] = CreateDynamicMapIcon(wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ], 27, -1, -1, -1, -1, 100.0);
		}
	}		
	return 1;
}

/*LoadWorkshop()
{
	mysql_tquery(g_SQL, "SELECT ID,name,leader,motd,color,extposx,extposy,extposz,extposa,intposx,intposy,intposz,intposa,wInt,safex,safey,safez,money,marijuana FROM WORKSHOPS ORDER BY ID", "LoadWorkshopData");
}*/
Player_OwnsWorkshop(playerid, id)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(id == -1) return 0;
	if(!strcmp(wData[id][wLeader], AccountData[playerid][pName], true)) return 1;
	return 0;
}

Player_WorkshopCount(playerid)
{
	#if LIMIT_PER_PLAYER != 0
    new count;
	foreach(new i : Workshop)
	{
		if(Player_OwnsWorkshop(playerid, i)) count++;
	}

	return count;
	#else
	return 0;
	#endif
}