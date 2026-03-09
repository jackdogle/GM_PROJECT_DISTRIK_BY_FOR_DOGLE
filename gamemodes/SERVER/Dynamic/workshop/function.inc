JavaTR:LoadWorkshop()
{
    new rows = cache_num_rows();
	new Cache:Wrgcache;
 	if(rows)
  	{
		Wrgcache = cache_save();

   		new wid, name[50], leader[MAX_PLAYER_NAME];
		for(new i; i < rows; i++)
		{
  			cache_get_value_name_int(i, "ID", wid);
	    	cache_get_value_name(i, "name", name);
			format(wData[wid][wName], 50, name);
		    cache_get_value_name(i, "leader", leader);
			format(wData[wid][wLeader], MAX_PLAYER_NAME, leader);
			cache_get_value_name_int(i, "price", wData[wid][wPrice]);
			cache_get_value_name_int(i, "status", wData[wid][wStatus]);
		    cache_get_value_name_float(i, "extposx", wData[wid][wExtposX]);
		    cache_get_value_name_float(i, "extposy", wData[wid][wExtposY]);
		    cache_get_value_name_float(i, "extposz", wData[wid][wExtposZ]);
		    cache_get_value_name_float(i, "extposa", wData[wid][wExtposA]);
			cache_get_value_name_int(i, "money", wData[wid][wMoney]);
			cache_get_value_name_int(i, "component", wData[wid][wComponent]);

			/*for (new j = 0; j < 10; j ++)
			{
				format(str, 24, "Weapon%d", j + 1);
				cache_get_value_name_int(i, str, wData[wid][wGun][j]);

				format(str, 24, "Ammo%d", j + 1);
				cache_get_value_name_int(i, str, wData[wid][wAmmo][j]);
			}*/
			Workshop_Refresh(wid);
			Iter_Add(Workshop, wid);
	    }
	    printf("[DATABASE] Number of Workshop loaded: %d.", rows);
		
		if(cache_is_valid(Wrgcache))
        {
            cache_delete(Wrgcache);
            printf("[Dynamic Warung]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Warung]: Cache tidak valid atau sudah dihapus.");
        }
		//Profiler_Stop();
	}
}

JavaTR: WorkshopCreateRepairkit(playerid, wsid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(AccountData[playerid][pWorkshop] == wsid)
	{
		{
			if(IsPlayerInRangeOfPoint(playerid, 4.5, wData[wsid][wExtposX], wData[wsid][wExtposY], wData[wsid][wExtposZ]))
			{
				TogglePlayerControllable(playerid, 1);
				ShowTDN(playerid, NOTIFICATION_INFO, "Kamu telah selesai membuat 1 repairkit.");
				AccountData[playerid][pThirst] -= 3;
				Inventory_Remove(playerid, "Component", 100);
				Inventory_Add(playerid, "Repair Kit", 920, 1);
				ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 0, 0, 0, 0, 1);
			}
		}
	}
	return 1;
}

JavaTR:ShowWorkshopInfo(playerid)
{
	new rows = cache_num_rows();
 	if(rows)
  	{
 		new wname[50],
 			wleader[50],
			wmoney,
			string[512];
			
		cache_get_value_index(0, 0, wname);
		cache_get_value_index(0, 1, wleader);
		cache_get_value_index_int(0, 2, wmoney);

		format(string, sizeof(string), "Workshop ID: %d\nWorkshop Name: %s\nWorkshop Leader: %s\nWorkshop Money: %s",
		AccountData[playerid][pWorkshop], wname, wleader, FormatNumber(wmoney));
		
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Workshop Info", string, "Okay", "");
	}
}

JavaTR:ShowWorkshopMember(playerid)
{
	new rows = cache_num_rows(), pid, username[50], frank, query[1048];
 	if(rows)
  	{
		for(new i = 0; i != rows; i++)
		{
			cache_get_value_index(i, 0, username);
			pid = GetID(username);
			
			format(query, sizeof(query), "%s"WHITE_E"%d. %s ", query, (i+1), username);
			
			if(IsPlayerConnected(pid))
				strcat(query, ""GREEN"(ONLINE)");
			else
				strcat(query, ""RED"(OFFLINE) ");
			
			cache_get_value_index_int(i, 1, frank);
			if(frank == 1)
			{
				strcat(query, ""WHITE_E"Trial Service(1)");
			}
			else if(frank == 2)
			{
				strcat(query, ""WHITE_E"Mechanic(2)");
			}
			else if(frank == 3)
			{
				strcat(query, ""WHITE_E"Pro Mechanic(3)");
			}
			else if(frank == 4)
			{
				strcat(query, ""WHITE_E"Staff(4)");
			}
			else if(frank == 5)
			{
				strcat(query, ""WHITE_E"Assistan Manager(5)");
			}
			else if(frank == 6)
			{
				strcat(query, ""WHITE_E"Manager(6)");
			}
			else
			{
				strcat(query, ""WHITE_E"None(0)");
			}
			strcat(query, "\n{FFFFFF}");
		}
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Workshop Member", query, "Okay", "");
	}
}