forward EngineStatus(playerid, vehicleid);
public EngineStatus(playerid, vehicleid)
{
	if(!IsPlayerConnected(playerid))
    {
        AccountData[playerid][pTurningEngine] = false;
        return 0;
    }

    if(!AccountData[playerid][pTurningEngine])
    {
        AccountData[playerid][pTurningEngine] = false;
        return 0;
    }

    if(!IsValidVehicle(vehicleid))
    {
        AccountData[playerid][pTurningEngine] = false;
        return 0;
    }

    if(GetEngineStatus(vehicleid))
    {
        AccountData[playerid][pTurningEngine] = false;
        return 0;
    }

    new Float: f_vHealth;
    GetVehicleHealth(vehicleid, f_vHealth);
    if(f_vHealth < 350.0)
    {
        AccountData[playerid][pTurningEngine] = false;
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Mesin tidak dapat menyala karena sudah rusak!");
    }
    
	if(VehicleCore[vehicleid][vCoreFuel] <= 0)
	{
		AccountData[playerid][pTurningEngine] = false;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Mesin tidak dapat menyala karena sudah bahan bakar habis!");
	}

    if(GetVehicleDriver(vehicleid) == INVALID_VEHICLE_ID)
    {
        AccountData[playerid][pTurningEngine] = false;
        return 1;
    }
    SwitchVehicleEngine(vehicleid, true);

    AccountData[playerid][pTurningEngine] = false;
    SendRPMeAboveHead(playerid, "Mesin menyala", X11_LIGHTGREEN);
    return 1;
}

FUNC::OnPlayerChangeToDriver(playerid)
{
	new Float:POS[3], vehicleid = ChangeSeatVehicleID[playerid];
	GetPlayerPos(playerid, POS[0], POS[1], POS[2]);

	SetPlayerPos(playerid, POS[0], POS[1], POS[2] + 6.0);
	TogglePlayerControllable(playerid, false);
	ShowPlayerFooter(playerid, "Change Seat", 3000, 1);
	SetTimerEx("OnPlayerChangeToDriverUpdate", 3000, false, "dd", playerid, vehicleid);
	return 1;
}

FUNC::InputVehicleToGarage(carid)
{
    if (carid == -1 || carid >= sizeof(PlayerVehicle)) // Pastikan carid valid
    {
        printf("[ERROR] carid tidak valid: %d", carid);
        return 0;
    }
    
    if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]))
    {
        DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
        SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

        DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
        PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
    }
    return 1;
}

FUNC::OnPlayerChangeToDriverUpdate(playerid, vehicleid)
{
	if(vehicleid == -1)
		return 0;
	
	PutPlayerInVehicle(playerid, vehicleid, 0); // Driver Seat
	TogglePlayerControllable(playerid, true);

	IsPlayerChangeSeat[playerid] = false;
	ChangeSeatWithPlayerID[playerid] = INVALID_PLAYER_ID;
	ChangeSeatVehicleID[playerid] = -1;
	return 1;
}

FUNC::OnPlayerChangeToPass(playerid)
{
	new Float:POS[3], vehicleid = ChangeSeatVehicleID[playerid];
	GetPlayerPos(playerid, POS[0], POS[1], POS[2]);

	SetPlayerPos(playerid, POS[0], POS[1], POS[2] + 6.0);
	TogglePlayerControllable(playerid, false);
	ShowPlayerFooter(playerid, "Change Seat", 3000, 1);
	SetTimerEx("OnPlayerChangeToPassUpdate", 3500, false, "dd", playerid, vehicleid);
	return 1;
}

FUNC::OnPlayerChangeToPassUpdate(playerid, vehicleid)
{
	if(vehicleid == -1)
		return 0;
	
	new seatid = GetAvailableSeat(vehicleid, 0);

	if(seatid == -1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada bangku kosong di kendaraan tersebut!");
	
	PutPlayerInVehicle(playerid, vehicleid, seatid);
	TogglePlayerControllable(playerid, true);
	
	IsPlayerChangeSeat[playerid] = false;
	ChangeSeatWithPlayerID[playerid] = INVALID_PLAYER_ID;
	ChangeSeatVehicleID[playerid] = -1;
	return 1;
}

forward RespawnPV(vehicleid);
public RespawnPV(vehicleid)
{
	if(IsValidVehicle(vehicleid))
	{
		SetVehicleToRespawn(vehicleid);
	}
	return 1;
}

Vehicle_ReturnID(vehicleid)
{
    if (!IsValidVehicle(vehicleid))
        return RETURN_INVALID_VEHICLE_ID;
    
    foreach (new index : PvtVehicles)
    {
        if (PlayerVehicle[index][pVehPhysic] == vehicleid)
            return index;
    }

    return RETURN_INVALID_VEHICLE_ID;
}


Vehicle_GetID(vehicleid)
{
	foreach(new i : PvtVehicles) if(PlayerVehicle[i][pVehPhysic] == vehicleid)
	{
		return i;
	}
	return -1;
}

IsVehicleFaction(vehicleid)
{
	new index = RETURN_INVALID_VEHICLE_ID;

	if((index = Vehicle_ReturnID(vehicleid)) != RETURN_INVALID_VEHICLE_ID)
	{
		if(PlayerVehicle[index][pVehFaction] > FACTION_NONE) return 1;
	}
	return 0;
}

GetEngineStatus(vehicleid)
{
	static
	engine,
	lights,
	alarm,
	doors,
	bonnet,
	boot,
	objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if(engine != 1)
		return 0;

	return 1;
}

GetLightStatus(vehicleid)
{
	static
	engine,
	lights,
	alarm,
	doors,
	bonnet,
	boot,
	objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if(lights != 1)
		return 0;

	return 1;
}

stock GetHoodStatus(vehicleid)
{
	static
	engine,
	lights,
	alarm,
	doors,
	bonnet,
	boot,
	objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if(bonnet != 1)
		return 0;

	return 1;
}

stock LockVehicle(vehicleid,status)
{
	new engine,lights,alarm,doors,bonnet,boot,objective;
	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
	SetVehicleParamsEx(vehicleid,engine,lights,alarm,status,bonnet,boot,objective);
}

stock CreateVehicleObject(objectid, vehicleid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new object = CreateDynamicObject(objectid, 0, 0, 0, 0, 0, 0);
	AttachDynamicObjectToVehicle(object, vehicleid, x, y, z, rx, ry, rz);
	return object;
}

stock GetTrunkStatus(vehicleid)
{
	static
	engine,
	lights,
	alarm,
	doors,
	bonnet,
	boot,
	objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if(boot != 1)
		return 0;

	return 1;
}

stock ShowPlayerVehicleImpound(playerid, otherid)
{
	new shstr[525], count = 0;
	format(shstr, sizeof(shstr), "Model Kendaraan\tWaktu\tAlasan\n");
	foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists])
	{
		if(!IsValidVehicle(PlayerVehicle[i][pVehPhysic]) && PlayerVehicle[i][pVehImpounded] && PlayerVehicle[i][pVehOwnerID] == AccountData[otherid][pID])
		{
			new times[125];
			if(PlayerVehicle[i][pVehImpoundDuration] <= gettime()) {
				format(times, sizeof(times), ""GREEN"Tersedia");
			} else format(times, sizeof(times), "%s", RemainingTimelapse(PlayerVehicle[i][pVehImpoundDuration]));

			format(shstr, sizeof(shstr), "%s%s\t%s\t%s\n", shstr, GetVehicleModelName(PlayerVehicle[i][pVehModelID]), times, PlayerVehicle[i][pVehImpoundReason]);
			ListVehImpound[playerid][count ++] = i;
		}
	}
	if(count == 0)
	{
		return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Impound", "Pemain tersebut tidak memiliki kendaraan di impound!", "Tutup", ""), PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	}
	
	if(AccountData[playerid][pFaction] == FACTION_POLISI)
	{
		ShowPlayerDialog(playerid, DIALOG_POLICE_TAKE_IMPOUND, DIALOG_STYLE_TABLIST_HEADERS, sprintf(""TCRP"District  "WHITE"- %s", ReturnName(otherid)), shstr, "Pilih", "Batal");
	} else ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, sprintf(""TCRP"District  "WHITE"- %s", ReturnName(otherid)), shstr, "Pilih", "Batal");
	return 1;
}

GetVehicleModelByName(const name[])
{
	if(IsNumeric(name) && (strval(name) >= 400 && strval(name) <= 611))
		return strval(name);

	for (new i = 0; i < sizeof(g_arrVehicleNames); i ++)
	{
		if(strfind(g_arrVehicleNames[i], name, true) != -1)
		{
			return i + 400;
		}
	}
	return 0;
}

stock Vehicle_Nearest(playerid, Float:range = 3.5)
{
	new Float:fX,
		Float:fY,
		Float:fZ;

	foreach(new i : PvtVehicles)
	{
		if(PlayerVehicle[i][pVehPhysic] != INVALID_VEHICLE_ID)
		{
			GetVehiclePos(PlayerVehicle[i][pVehPhysic], fX, fY, fZ);

			if(IsPlayerInRangeOfPoint(playerid, range, fX, fY, fZ)) 
			{
				return i;
			}
		}
	}
	return -1;
}

Vehicle_Nearest2(playerid)
{
	foreach(new i : PvtVehicles)
	{
		if(PlayerVehicle[i][pVehPhysic] != INVALID_VEHICLE_ID && IsPlayerInAnyVehicle(playerid) && PlayerVehicle[i][pVehPhysic] == GetPlayerVehicleID(playerid))
		{
			return i;
		}
	}
	return -1;
}

forward LoadPVeh();
public LoadPVeh()
{
	foreach(new i : Player) if(AccountData[i][pSpawned]) {
		LoadPlayerVehicle(i);
	}
	return 1;
}

forward ReloadPVeh();
public ReloadPVeh()
{
	foreach(new i : Player) if(AccountData[i][pSpawned]) {
		UnloadPlayerVehicle(i);
	}
	Iter_Clear(PvtVehicles);
	SetTimer("LoadPVeh", 2000, false);
}

stock Vehicle_Inside(playerid)
{
	new carid;

	if (IsPlayerInAnyVehicle(playerid) && (carid = Vehicle_GetID(GetPlayerVehicleID(playerid))) != -1)
		return carid;
	
	return -1;
}

Vehicle_GetStatus(carid)
{
	if(PlayerVehicle[carid][pVehExists])
	{
		if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]) && PlayerVehicle[carid][pVehPhysic] != INVALID_VEHICLE_ID)
		{
			GetVehicleDamageStatus(PlayerVehicle[carid][pVehPhysic], PlayerVehicle[carid][pVehDamage][0], PlayerVehicle[carid][pVehDamage][1], PlayerVehicle[carid][pVehDamage][2], PlayerVehicle[carid][pVehDamage][3]);

			GetVehicleHealth(PlayerVehicle[carid][pVehPhysic], PlayerVehicle[carid][pVehHealth]);
			// if(PlayerVehicle[carid][pVehHealth] < 0.0 || PlayerVehicle[carid][pVehHealth] > 1000.0) PlayerVehicle[carid][pVehHealth] = PlayerVehicle[carid][pVehHealth];

			PlayerVehicle[carid][pVehFuel] = VehicleCore[PlayerVehicle[carid][pVehPhysic]][vCoreFuel];
			PlayerVehicle[carid][pVehWorld] = GetVehicleVirtualWorld(PlayerVehicle[carid][pVehPhysic]);
			PlayerVehicle[carid][pVehInterior] = GetVehicleInterior(PlayerVehicle[carid][pVehPhysic]);

			GetVehiclePos(PlayerVehicle[carid][pVehPhysic], PlayerVehicle[carid][pVehPos][0], PlayerVehicle[carid][pVehPos][1], PlayerVehicle[carid][pVehPos][2]);
			GetVehicleZAngle(PlayerVehicle[carid][pVehPhysic], PlayerVehicle[carid][pVehPos][3]);
		}
	}
	return 1;
}	

Vehicle_AddUpgrade(vehicleid, type)
{
	static index;

	if((index = Vehicle_ReturnID(vehicleid)) != RETURN_INVALID_VEHICLE_ID)
	{
		if(type == 1)
		{
			PlayerVehicle[index][pVehEngineUpgrade] = type; // Engine untuk di database
			PlayerVehicle[vehicleid][pVehEngineUpgrade] = type; // Engine untuk in game
			SavePlayerVehicle(index);
		}
		else if(type == 3)
		{
			PlayerVehicle[index][pVehBodyUpgrade] = type; // Engine untuk di database
			PlayerVehicle[vehicleid][pVehBodyUpgrade] = type; // Engine untuk in game
			SavePlayerVehicle(index);
		}
	}
	return 1;
}

stock Vehicle_IsOwner(playerid, carid)
{
	if(AccountData[playerid][pID] == -1)
		return 0;

	if(Iter_Contains(PvtVehicles, carid) && PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
		return 1;
	
	return 0;
}
CountPlayerVehicleParked(playerid, gpid)
{
	new tmpcount;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehExists] && PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(!IsValidVehicle(PlayerVehicle[id][pVehPhysic]) && PlayerVehicle[id][pVehParked] == gpid)
			{
				tmpcount++;
			}
		}
	}
	return tmpcount;
}

CountPlayerFactVehInGarage(playerid, fid)
{
	new tmpcount;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehExists] && PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(!IsValidVehicle(PlayerVehicle[id][pVehPhysic]) && PlayerVehicle[id][pVehFactStored] == fid)
			{
				tmpcount++;
			}
		}
	}
	return tmpcount;
}

CountPlayerVehicleFamilies(playerid, gfid)
{
	new tmpcount;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehExists] && PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(!IsValidVehicle(PlayerVehicle[id][pVehPhysic]) && PlayerVehicle[id][pVehFamiliesGarage] == gfid)
			{
				tmpcount++;
			}
		}
	}
	return tmpcount;
}

CountPlayerVehicleHoused(playerid, hgid)
{
	new tmpcount;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehExists] && PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(!IsValidVehicle(PlayerVehicle[id][pVehPhysic]) && PlayerVehicle[id][pVehHouseGarage] == hgid)
			{
				tmpcount++;
			}
		}
	}
	return tmpcount;
}

CountPlayerHelipadHoused(playerid, hpid)
{
	new tmpcount;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehExists] && PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(!IsValidVehicle(PlayerVehicle[id][pVehPhysic]) && PlayerVehicle[id][pVehHelipadGarage] == hpid)
			{
				tmpcount++;
			}
		}
	}
	return tmpcount;
}

CountPlayerVehicleInsuranced(playerid)
{
	new tmpcount;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehExists] && PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(PlayerVehicle[id][pVehInsuranced])
			{
				tmpcount ++;
			}
		}
	}
	return tmpcount;
}

CountPlayerVehicleImpound(playerid)
{
	new tmpcount;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehExists] && PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(PlayerVehicle[id][pVehImpounded])
			{
				tmpcount ++;
			}
		}
	}
	return tmpcount;
}

ReturnVehicleIDImpounded(playerid, slot)
{
	new tmpcount = -1;
	if(slot < 0 && slot > MAX_PRIVATE_VEHICLE - 1) return -1;
	foreach(new i : PvtVehicles)
	{
		if(PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(PlayerVehicle[i][pVehImpounded])
			{
				tmpcount ++;
				if(tmpcount == slot)
				{
					return i;
				}
			}
		}
	}
	return -1;
}

ReturnVehicleIDInsuranced(playerid, slot)
{
	new tmpcount = -1;
	if(slot < 0 && slot > MAX_PRIVATE_VEHICLE - 1) return -1;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehExists] && PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(PlayerVehicle[id][pVehInsuranced])
			{
				tmpcount ++;
				if(tmpcount == slot)
				{
					return id;
				}
			}
		}
	}
	return -1;
}

ReturnAnyVehicleFamilies(playerid, slot, gfid)
{
	new tmpcount = -1;
	if(slot < 0 && slot > MAX_PRIVATE_VEHICLE - 1) return -1;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehExists] && PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(PlayerVehicle[id][pVehFamiliesGarage] == gfid && PlayerVehicle[id][pVehFamiliesGarage] > -1)
			{
				tmpcount ++;
				if(tmpcount == slot)
				{
					return id;
				}
			}
		} 
	}
	return -1;
}

GetVehicleIDStoredFactGarage(playerid, slot, factid)
{
	new tmpcount = -1;
	if(slot < 0 && slot > MAX_PRIVATE_VEHICLE - 1) return -1;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehExists] && PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(PlayerVehicle[id][pVehFactStored] == factid)
			{
				tmpcount ++;
				if(tmpcount == slot)
				{
					return id;
				}
			}
		} 
	}
	return -1;
}

GetFactionVehicleIDFromListitem(playerid, slot, factionid)
{
	new tmpcount = -1;
	if(slot < 0 && slot > MAX_PRIVATE_VEHICLE - 1) return -1;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehExists] && PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(PlayerVehicle[id][pVehFaction] == factionid)
			{
				tmpcount ++;
				if(tmpcount == slot)
				{
					return id;
				}
			}
		}
	}
	return -1;
}

ReturnAnyVehicleHoused(playerid, slot, hgid)
{
	new tmpcount = -1;
	if(slot < 0 && slot > MAX_PRIVATE_VEHICLE - 1) return -1;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehExists] && PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(PlayerVehicle[id][pVehHouseGarage] == hgid && PlayerVehicle[id][pVehHouseGarage] > -1)
			{
				tmpcount ++;
				if(tmpcount == slot)
				{
					return id;
				}
			}
		} 
	}
	return -1;
}

ReturnAnyVehicleHelipad(playerid, slot, hgid)
{
	new tmpcount = -1;
	if(slot < 0 && slot > MAX_PRIVATE_VEHICLE - 1) return -1;
	foreach(new id : PvtVehicles)
	{
		if(PlayerVehicle[id][pVehExists] && PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
		{
			if(PlayerVehicle[id][pVehHelipadGarage] == hgid && PlayerVehicle[id][pVehHelipadGarage] > -1)
			{
				tmpcount ++;
				if(tmpcount == slot)
				{
					return id;
				}
			}
		} 
	}
	return -1;
}

ReturnAnyVehicleParked(playerid, slot, pgid)
{
    new tmpcount;
    if (slot < 1 && slot > MAX_PRIVATE_VEHICLE) return -1;
    foreach(new id : PvtVehicles)
    {
        if (PlayerVehicle[id][pVehExists] && PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
        {
            if (PlayerVehicle[id][pVehParked] == pgid && PlayerVehicle[id][pVehParked] > -1)
            {
                tmpcount++;	
				if(tmpcount == slot)
				{
					return id;
				}
            }
        } 
    }
    return -1;
}

SetValidVehicleHealth(vehicleid, Float:health) {
	VehicleHealthSecurity[vehicleid] = true;
	SetVehicleHealth(vehicleid, health);
	return 1;
}

ValidRepairVehicle(vehicleid) {
	VehicleHealthSecurity[vehicleid] = true;
	RepairVehicle(vehicleid);
	return 1;
}

forward ForcedPlayerHopInBuyVeh(playerid, vid, seatid);
public ForcedPlayerHopInBuyVeh(playerid, vid, seatid)
{
	if(IsValidVehicle(vid))
	{
		LockVehicle(vid, false);
		PlayerVehicle[vid][pVehLocked] = false;
		SwitchVehicleEngine(vid, true);
		if(!IsPlayerInAnyVehicle(playerid))
		{
			PutPlayerInVehicle(playerid, vid, seatid);
		}

		DestroyVehicle(ShowroomVeh[playerid]);
		ShowroomVeh[playerid] = INVALID_VEHICLE_ID;
	}
	return 1;
}

forward ForcedPlayerHopInVehicle(playerid, vid, seatid);
public ForcedPlayerHopInVehicle(playerid, vid, seatid)
{
	if(IsValidVehicle(vid))
	{
		LockVehicle(vid, false);
		PlayerVehicle[vid][pVehLocked] = false;
		
		if(GetFuel(vid) <= 0)
		{
			SwitchVehicleEngine(vid, false);
			ShowTDN(playerid, NOTIFICATION_ERROR, "Mesin tidak dapat menyala karena bahan bakar habis!");
		}
		else 
		{
			SwitchVehicleEngine(vid, true);
		}

		if(!IsPlayerInAnyVehicle(playerid))
		{
			PutPlayerInVehicle(playerid, vid, seatid);
		}
	}
	return 1;
}	

stock Vehicle_CanSpawn(vehicleid)
{
	if (!PlayerVehicle[vehicleid][pVehImpounded] && !PlayerVehicle[vehicleid][pVehInsuranced] && PlayerVehicle[vehicleid][pVehParked] == -1 && PlayerVehicle[vehicleid][pVehHelipadGarage] == -1 && PlayerVehicle[vehicleid][pVehHouseGarage] == -1 &&  PlayerVehicle[vehicleid][pVehFamiliesGarage] == -1 && PlayerVehicle[vehicleid][pVehFactStored] == -1)
		return 1;
	
	return 0;
}

stock Vehicle_Count(playerid)
{
	new count = 0;
	foreach(new i : PvtVehicles) if(PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID] && PlayerVehicle[i][pVehRental] == -1)
	{
	    count++;
	}
	return count;
}

stock Vehicle_RentalCount(playerid)
{
	new count = 0;
	foreach(new i : PvtVehicles) if(PlayerVehicle[i][pVehRental] != -1 && PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
	{
		count++;
	}
	return count;
}

new const VehFacName[10][] = 
{
	"Tidak",
	"Federal",
	"Pemerintah",
	"EMS",
	"Trans District ",
	"Bengkel",
	"Pedagang",
	"Gojek",
	"Helipad Polda",
	"Polda"
};

GetMyVehicleStatus(pvid, const def[] = "Spawned")
{
	new status[64];
	strcpy(status, def);

	if(PlayerVehicle[pvid][pVehParked] >= 0)
		strcpy(status, sprintf("Garkot %s", PublicGarage[PlayerVehicle[pvid][pVehParked]][pgName]));
	
	if(PlayerVehicle[pvid][pVehFactStored] >= 1)
		strcpy(status, sprintf("Garasi %s", VehFacName[PlayerVehicle[pvid][pVehFactStored]]));

	if(PlayerVehicle[pvid][pVehHouseGarage] >= 0)
		strcpy(status, sprintf("Garasi Rumah %d", PlayerVehicle[pvid][pVehHouseGarage]));
	
	if(PlayerVehicle[pvid][pVehHelipadGarage] >= 0)
		strcpy(status, sprintf("Garasi Helipad %d", PlayerVehicle[pvid][pVehHelipadGarage]));
	
	if(PlayerVehicle[pvid][pVehFamiliesGarage] >= 0)
		strcpy(status, sprintf("Garasi %s", FamData[PlayerVehicle[pvid][pVehFamiliesGarage]][famName]));
	
	if(PlayerVehicle[pvid][pVehInsuranced])
		strcpy(status, "Asuransi");
	
	if(PlayerVehicle[pvid][pVehImpounded])
		strcpy(status, "Samsat");
	
	return status;
}

stock IsVehicleUpsideDown(vehicleid)
{
    new Float:quat_w, Float:quat_x, Float:quat_y, Float:quat_z;
    GetVehicleRotationQuat(vehicleid, quat_w, quat_x, quat_y, quat_z);
    return (
        floatabs(
            atan2(2 * (quat_y * quat_z + quat_w * quat_x),
                quat_w * quat_w - quat_x * quat_x - quat_y * quat_y + quat_z * quat_z
            )
        ) > 90.0
    );
}

/*GetVehicleHood(vehicleid, &Float:x, &Float:y, &Float:z)
{
	if (!GetVehicleModel(vehicleid) || !IsValidVehicle(vehicleid))
		return (x = 0.0, y = 0.0, z = 0.0), 0;

	static 	
		Float:pos[7]
	;
	GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, pos[0], pos[1], pos[2]);
	GetVehiclePos(vehicleid, pos[3], pos[4], pos[5]);
	GetVehicleZAngle(vehicleid, pos[6]);

	x = pos[3] + (floatsqroot(pos[1] + pos[1]) * floatsin(-pos[6], degress));
	y = pos[4] + (floatsqroot(pos[1] + pos[1]) * floatsin(-pos[6], degress));
	z = pos[5];

	return 1;
}

GetVehicleBoot(vehicleid, &Float:x, &Float:y, &Float:z)
{
	if (!GetVehicleModel(vehicleid) || !IsValidVehicle(vehicleid))
		return (x = 0.0, y = 0.0, z = 0.0), 0;

	static 	
		Float:pos[7]
	;
	GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, pos[0], pos[1], pos[2]);
	GetVehiclePos(vehicleid, pos[3], pos[4], pos[5]);
	GetVehicleZAngle(vehicleid, pos[6]);

	x = pos[3] + (floatsqroot(pos[1] + pos[1]) * floatsin(-pos[6], degress));
	y = pos[4] + (floatsqroot(pos[1] + pos[1]) * floatsin(-pos[6], degress));
	z = pos[5];

	return 1;
}*/

Vehicle_ShowBagasi(playerid, vehid)
{
	VehicleBagasi[playerid][vehiclebagasiID] = 0;
	VehicleBagasi[playerid][vehiclebagasiTemp] = EOS;
	VehicleBagasi[playerid][vehiclebagasiModel] = 0;
	VehicleBagasi[playerid][vehiclebagasiQuant] = 0;

	new fhsrs[128], jljs[1218], Cache:execute;
	mysql_format(g_SQL, fhsrs, sizeof(fhsrs), "SELECT * FROM `vehicle_bagasi` WHERE `vID`=%d", PlayerVehicle[vehid][pVehID]);
	execute = mysql_query(g_SQL, fhsrs, true);

	new rows = cache_num_rows(),
		ItemName[32],
		ModelID,
		Quants;
	format(jljs, sizeof(jljs), "Nama Item\tJumlah\tBerat (%.3f/%.0f)\n", PlayerVehicle[vehid][pVehWeight], PlayerVehicle[vehid][pVehCapacity]);
	if(rows)
	{
		for(new i; i < rows; ++i)
		{
			cache_get_value_name(i, "Item", ItemName);
			cache_get_value_name_int(i, "Model", ModelID);
			cache_get_value_name_int(i, "Quantity", Quants);
			
			format(jljs, sizeof(jljs), "%s%s\t%d\t-\n", jljs, ItemName, Quants);
		}
		ShowPlayerDialog(playerid, DIALOG_BAGASI_WITHDRAW, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Bagasi %s", PlayerVehicle[vehid][pVehPlate]), 
		jljs, "Pilih", "Batal");
	}
	else
	{
		IsBagasiOpened[vehid] = false;
		AccountData[playerid][menuShowed] = false;
		SwitchVehicleBoot(PlayerVehicle[vehid][pVehPhysic], false);
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, sprintf("Bagasi %s", PlayerVehicle[vehid][pVehPlate]),
		"Isi bagasi kendaraan ini kosong!", "Tutup", "");
	}

	cache_delete(execute);
	return 1;
}

forward OnBagasiDeposit(playerid);
public OnBagasiDeposit(playerid)
{
	BagasiLastUse[playerid] = 0;
	AccountData[playerid][menuShowed] = false;
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menyimpan barang!");
	VehicleBagasi[playerid][vehiclebagasiID] = 0;
	VehicleBagasi[playerid][vehiclebagasiTemp] = EOS;
	VehicleBagasi[playerid][vehiclebagasiModel] = 0;
	VehicleBagasi[playerid][vehiclebagasiQuant] = 0;
	return 1;
}

forward ToggleVehicleLights(vehicleid, toggle);
public ToggleVehicleLights(vehicleid, toggle)
{
	if(IsValidVehicle(vehicleid))
	{
		if(toggle)
		{
			if(!IsVehicleFlashing(vehicleid))
			{
				vehicleFlashCount[vehicleid] = 0;
				vehicleFlashTimer[vehicleid] = SetTimerEx("ToggleVehicleLightsInterval", 500, true, "d", vehicleid);
			}
		}
		else 
		{
			if(IsVehicleFlashing(vehicleid))
			{
				KillTimer(vehicleFlashTimer[vehicleid]);
				SwitchVehicleLight(vehicleid, false);// menghidupkan lampu
				vehicleFlashCount[vehicleid] = 0;
				vehicleFlashTimer[vehicleid] = -1;
			}
		}
	}
	return 1;
}
forward ToggleVehicleLightsInterval(vehicleid);
public ToggleVehicleLightsInterval(vehicleid)
{
	vehicleFlashCount[vehicleid] ++;
	if(vehicleFlashCount[vehicleid] < 4)
	{
		SwitchVehicleLight(vehicleid, !GetLightStatus(vehicleid));
	}
	else 
	{
		ToggleVehicleLights(vehicleid, false);
	}
	return 1;
}
forward IsVehicleFlashing(vehicleid);
public IsVehicleFlashing(vehicleid)
{
	if(vehicleFlashCount[vehicleid] != 0 || vehicleFlashTimer[vehicleid] != -1)
		return 1;

	return 0;
}

stock Vehicle_Delete(vid)
{
	if(!Iter_Contains(PvtVehicles, vid))
		return 0;

	for(new idx; idx < 23; idx ++)
	{
		if(DestroyDynamicObject(FactionVehObject[PlayerVehicle[vid][pVehPhysic]][idx]))
			FactionVehObject[PlayerVehicle[vid][pVehPhysic]][idx] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	}
	
	for(new idx; idx < 16; idx ++)
	{
		if(DestroyDynamicObject(DonationVehObject[PlayerVehicle[vid][pVehPhysic]][idx]))
			DonationVehObject[PlayerVehicle[vid][pVehPhysic]][idx] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	}

	new query[200];
	mysql_format(g_SQL, query, sizeof(query), "DELETE FROM player_vehicles WHERE id = '%d'", PlayerVehicle[vid][pVehID]);
	mysql_tquery(g_SQL, query);

	for (new i = 0; i < MAX_VEHICLE_OBJECT; i ++) if (VehicleObjects[vid][i][vehObjectExists])
	{
		new dbstr[200];
		mysql_format(g_SQL, dbstr, sizeof(dbstr), "DELETE FROM vehicle_object WHERE vehicle = '%d'", PlayerVehicle[vid][pVehID]);
		mysql_tquery(g_SQL, dbstr);
		Vehicle_ObjectDestroy(vid);
	}

	new vstr[188];
	mysql_format(g_SQL, vstr, sizeof(vstr), "DELETE FROM vehicle_bagasi WHERE vID = '%d'", PlayerVehicle[vid][pVehID]);
	mysql_tquery(g_SQL, vstr);

	PlayerVehicle[vid][pVehExists] = false;
	PlayerVehicle[vid][pVehOwnerID] = -1;

	if(IsValidVehicle(PlayerVehicle[vid][pVehPhysic])) DestroyVehicle(PlayerVehicle[vid][pVehPhysic]);
	PlayerVehicle[vid][pVehPhysic] = INVALID_VEHICLE_ID;
	
	Vehicle_ResetVariable(vid);
	Iter_Remove(PvtVehicles, vid);
	return 1;
}

/*VehicleImport_Create(ownerid, modelid, factionid, Float:x, Float:y, Float:z, Float:a, color1, color2, cost)
{
	static vehicleid;
	if ((vehicleid = Iter_Free(PvtVehicles)) != cellmin)
	{
		Iter_Add(PvtVehicles, vehicleid);

		PlayerVehicle[vehicleid][pVehExists] = true;

		PlayerVehicle[vehicleid][pVehPhysic] = INVALID_VEHICLE_ID;
		PlayerVehicle[vehicleid][pVehOwnerID] = AccountData[ownerid][pID];
		PlayerVehicle[vehicleid][pVehModelID] = modelid;
		PlayerVehicle[vehicleid][pVehColor1] = color1;
		PlayerVehicle[vehicleid][pVehColor2] = color2;
		PlayerVehicle[vehicleid][pVehPaintjob] = -1;
		PlayerVehicle[vehicleid][pVehNeon] = 0;
		PlayerVehicle[vehicleid][cTogNeon] = 0;

		PlayerVehicle[vehicleid][pVehLocked] = false;
		format(PlayerVehicle[vehicleid][pVehPlate], 64, "-");
		PlayerVehicle[vehicleid][pVehPlateTime] = 0;
		PlayerVehicle[vehicleid][pVehPlateOwn] = 0;
		PlayerVehicle[vehicleid][pVehPrice] = cost;
		
		PlayerVehicle[vehicleid][pVehHealth] = 1000.0;
		PlayerVehicle[vehicleid][pVehFuel] = MAX_FUEL_FULL;
		PlayerVehicle[vehicleid][pVehPos][0] = x;
		PlayerVehicle[vehicleid][pVehPos][1] = y;
		PlayerVehicle[vehicleid][pVehPos][2] = z;
		PlayerVehicle[vehicleid][pVehPos][3] = a;

		PlayerVehicle[vehicleid][pVehDamage][0] = 0;
		PlayerVehicle[vehicleid][pVehDamage][1] = 0;
		PlayerVehicle[vehicleid][pVehDamage][2] = 0;
		PlayerVehicle[vehicleid][pVehDamage][3] = 0;
		PlayerVehicle[vehicleid][pVehInterior] = GetPlayerInterior(ownerid);
		PlayerVehicle[vehicleid][pVehWorld] = GetPlayerVirtualWorld(ownerid);
		
		for(new j = 0; j < 17; j++){
			PlayerVehicle[vehicleid][pVehMod][j] = 0;}
		
		PlayerVehicle[vehicleid][pVehRental] = -1;
		PlayerVehicle[vehicleid][pVehRentTime] = 0;
		PlayerVehicle[vehicleid][pVehParked] = -1;
		PlayerVehicle[vehicleid][pVehHouseGarage] = -1;
		PlayerVehicle[vehicleid][pVehHelipadGarage] = -1;
		PlayerVehicle[vehicleid][pVehFamiliesGarage] = -1;
		PlayerVehicle[vehicleid][pVehFactStored] = -1;
		PlayerVehicle[vehicleid][pVehFaction] = factionid;

		PlayerVehicle[vehicleid][pVehEngineUpgrade] = 0;
		PlayerVehicle[vehicleid][pVehBodyUpgrade] = 0;
		PlayerVehicle[vehicleid][pVehBodyRepair] = 0;

		PlayerVehicle[vehicleid][pVehBroken] = 0;
		PlayerVehicle[vehicleid][pVehInsuranced] = false;
		PlayerVehicle[vehicleid][pVehImpounded] = false;
		PlayerVehicle[vehicleid][pVehImpoundDuration] = 0;
		PlayerVehicle[vehicleid][pVehImpoundFee] = 0;
		PlayerVehicle[vehicleid][pVehImpoundReason] = EOS;
		PlayerVehicle[vehicleid][vehDonation] = 0;
		PlayerVehicle[vehicleid][pVehDCTime] = 0;

		for(new wp; wp < 3; wp ++)
		{
			PlayerVehicle[vehicleid][pVehWeapon][wp] = 0;
			PlayerVehicle[vehicleid][pVehAmmo][wp] = 0;
		}
		new Float:defaultCap = 15.0; // fallback
        if(IsLuxuryVeh(modelid)) defaultCap = 30.0;
        else if(IsCompactVeh(modelid)) defaultCap = 20.0;
        else if(IsTruckVeh(modelid)) defaultCap = 60.0;
        PlayerVehicle[vehicleid][pVehCapacity] = defaultCap;
		PlayerVehicle[vehicleid][pVehWeight] = 0.0;

		mysql_tquery(g_SQL, "INSERT INTO `player_vehicles` (`PVeh_Faction`) VALUES ('0')", "OnVehCreated", "i", vehicleid);
		return vehicleid;
	}
	return -1;
}*/

Vehicle_Create(ownerid, modelid, factionid, Float:x, Float:y, Float:z, Float:a, color1, color2, cost)
{
	static vehicleid;
	if ((vehicleid = Iter_Free(PvtVehicles)) != cellmin)
	{
		Iter_Add(PvtVehicles, vehicleid);

		PlayerVehicle[vehicleid][pVehExists] = true;

		PlayerVehicle[vehicleid][pVehOwnerID] = AccountData[ownerid][pID];
		PlayerVehicle[vehicleid][pVehModelID] = modelid;
		PlayerVehicle[vehicleid][pVehColor1] = color1;
		PlayerVehicle[vehicleid][pVehColor2] = color2;
		PlayerVehicle[vehicleid][pVehPaintjob] = -1;
		PlayerVehicle[vehicleid][pVehNeon] = 0;
		PlayerVehicle[vehicleid][cTogNeon] = 0;

		PlayerVehicle[vehicleid][pVehLocked] = false;
		format(PlayerVehicle[vehicleid][pVehPlate], 64, "-");
		PlayerVehicle[vehicleid][pVehPlateTime] = 0;
		PlayerVehicle[vehicleid][pVehPlateOwn] = 0;
		PlayerVehicle[vehicleid][pVehPrice] = cost;
		
		PlayerVehicle[vehicleid][pVehHealth] = 1000.0;
		PlayerVehicle[vehicleid][pVehFuel] = MAX_FUEL_FULL;
		PlayerVehicle[vehicleid][pVehPos][0] = x;
		PlayerVehicle[vehicleid][pVehPos][1] = y;
		PlayerVehicle[vehicleid][pVehPos][2] = z;
		PlayerVehicle[vehicleid][pVehPos][3] = a;

		PlayerVehicle[vehicleid][pVehDamage][0] = 0;
		PlayerVehicle[vehicleid][pVehDamage][1] = 0;
		PlayerVehicle[vehicleid][pVehDamage][2] = 0;
		PlayerVehicle[vehicleid][pVehDamage][3] = 0;
		PlayerVehicle[vehicleid][pVehInterior] = GetPlayerInterior(ownerid);
		PlayerVehicle[vehicleid][pVehWorld] = GetPlayerVirtualWorld(ownerid);
		
		for(new j = 0; j < 17; j++){
			PlayerVehicle[vehicleid][pVehMod][j] = 0;}
		
		PlayerVehicle[vehicleid][pVehRental] = -1;
		PlayerVehicle[vehicleid][pVehRentTime] = 0;
		PlayerVehicle[vehicleid][pVehParked] = -1;
		PlayerVehicle[vehicleid][pVehHouseGarage] = -1;
		PlayerVehicle[vehicleid][pVehHelipadGarage] = -1;
		PlayerVehicle[vehicleid][pVehFamiliesGarage] = -1;
		PlayerVehicle[vehicleid][pVehFactStored] = -1;
		PlayerVehicle[vehicleid][pVehFaction] = factionid;

		PlayerVehicle[vehicleid][pVehEngineUpgrade] = 0;
		PlayerVehicle[vehicleid][pVehBodyUpgrade] = 0;
		PlayerVehicle[vehicleid][pVehBodyRepair] = 0;

		PlayerVehicle[vehicleid][pVehBroken] = 0;
		PlayerVehicle[vehicleid][pVehInsuranced] = false;
		PlayerVehicle[vehicleid][pVehImpounded] = false;
		PlayerVehicle[vehicleid][pVehImpoundDuration] = 0;
		PlayerVehicle[vehicleid][pVehImpoundFee] = 0;
		PlayerVehicle[vehicleid][pVehImpoundReason] = EOS;
		PlayerVehicle[vehicleid][vehDonation] = 0;
		PlayerVehicle[vehicleid][pVehDCTime] = 0;

		for(new wp; wp < 3; wp ++)
		{
			PlayerVehicle[vehicleid][pVehWeapon][wp] = 0;
			PlayerVehicle[vehicleid][pVehAmmo][wp] = 0;
		}
		new Float:defaultCap = 15.0; // fallback
        if(IsLuxuryVeh(modelid)) defaultCap = 30.0;
        else if(IsCompactVeh(modelid)) defaultCap = 20.0;
        else if(IsTruckVeh(modelid)) defaultCap = 60.0;
        PlayerVehicle[vehicleid][pVehCapacity] = defaultCap;
		PlayerVehicle[vehicleid][pVehWeight] = 0.0;
		
		PlayerVehicle[vehicleid][pVehPhysic] = CreateVehicle(PlayerVehicle[vehicleid][pVehModelID], PlayerVehicle[vehicleid][pVehPos][0], PlayerVehicle[vehicleid][pVehPos][1], PlayerVehicle[vehicleid][pVehPos][2], PlayerVehicle[vehicleid][pVehPos][3], PlayerVehicle[vehicleid][pVehColor1], PlayerVehicle[vehicleid][pVehColor2], 60000);
		VehicleCore[PlayerVehicle[vehicleid][pVehPhysic]][vCoreFuel] = PlayerVehicle[vehicleid][pVehFuel];
		SetVehicleNumberPlate(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehPlate]);
		SetVehicleVirtualWorld(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehWorld]);
		LinkVehicleToInterior(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehInterior]);
		OnLoadVehicleMod(vehicleid);

		// mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `player_vehicles` (`PVeh_OwnerID`, `PVeh_ModelID`, `PVeh_Faction`, `PVeh_Price`, `PVeh_Health`, `PVeh_Fuel`, `PVeh_Parked`, `PVeh_Housed`, `PVeh_Families`, `PVeh_FactionGarage`, `PVeh_Rental`, `PVeh_RentTime`, `PVeh_Plate`, \
		// `PVeh_PosX`, `PVeh_PosY`, `PVeh_PosZ`, `PVeh_PosA`, `PVeh_Color1`, `PVeh_Color2`, `PVeh_Paintjob`, `PVeh_World`, `PVeh_Interior`) VALUES (%d, %d, %d, %d, %f, %d, %d, %d, %d, %d, %d, %d, '%s', %f, %f, %f, %f, %d, %d, %d, %d, %d)", PlayerVehicle[vehicleid][pVehOwnerID], PlayerVehicle[vehicleid][pVehModelID], PlayerVehicle[vehicleid][pVehPrice],
		// PlayerVehicle[vehicleid][pVehFaction], PlayerVehicle[vehicleid][pVehHealth], PlayerVehicle[vehicleid][pVehFuel], PlayerVehicle[vehicleid][pVehParked], PlayerVehicle[vehicleid][pVehHouseGarage], PlayerVehicle[vehicleid][pVehFamiliesGarage], PlayerVehicle[vehicleid][pVehFactStored], PlayerVehicle[vehicleid][pVehRental], PlayerVehicle[vehicleid][pVehRentTime], PlayerVehicle[vehicleid][pVehPlate], PlayerVehicle[vehicleid][pVehPos][0],
		// PlayerVehicle[vehicleid][pVehPos][1], PlayerVehicle[vehicleid][pVehPos][2], PlayerVehicle[vehicleid][pVehPos][3], PlayerVehicle[vehicleid][pVehColor1], PlayerVehicle[vehicleid][pVehColor2], PlayerVehicle[vehicleid][pVehPaintjob], PlayerVehicle[vehicleid][pVehWorld], PlayerVehicle[vehicleid][pVehInterior]);
		mysql_tquery(g_SQL, "INSERT INTO `player_vehicles` (`PVeh_Faction`) VALUES('0')", "OnVehCreated", "d", vehicleid);
		return vehicleid;
	}
	return -1;
}

Vehicle_Backpack(ownerid, modelid, factionid, Float:x, Float:y, Float:z, Float:a, color1, color2, cost)
{
	static vehicleid;
	if ((vehicleid = Iter_Free(PvtVehicles)) != cellmin)
	{
		Iter_Add(PvtVehicles, vehicleid);

		PlayerVehicle[vehicleid][pVehExists] = true;

		PlayerVehicle[vehicleid][pVehOwnerID] = AccountData[ownerid][pID];
		PlayerVehicle[vehicleid][pVehModelID] = modelid;
		PlayerVehicle[vehicleid][pVehColor1] = color1;
		PlayerVehicle[vehicleid][pVehColor2] = color2;
		PlayerVehicle[vehicleid][pVehPaintjob] = -1;
		PlayerVehicle[vehicleid][pVehNeon] = 0;
		PlayerVehicle[vehicleid][cTogNeon] = 0;

		PlayerVehicle[vehicleid][pVehLocked] = false;
		format(PlayerVehicle[vehicleid][pVehPlate], 64, "-");
		PlayerVehicle[vehicleid][pVehPlateTime] = 0;
		PlayerVehicle[vehicleid][pVehPlateOwn] = 0;
		PlayerVehicle[vehicleid][pVehPrice] = cost;
		
		PlayerVehicle[vehicleid][pVehHealth] = 1000.0;
		PlayerVehicle[vehicleid][pVehFuel] = MAX_FUEL_FULL;
		PlayerVehicle[vehicleid][pVehPos][0] = x;
		PlayerVehicle[vehicleid][pVehPos][1] = y;
		PlayerVehicle[vehicleid][pVehPos][2] = z;
		PlayerVehicle[vehicleid][pVehPos][3] = a;

		PlayerVehicle[vehicleid][pVehDamage][0] = 0;
		PlayerVehicle[vehicleid][pVehDamage][1] = 0;
		PlayerVehicle[vehicleid][pVehDamage][2] = 0;
		PlayerVehicle[vehicleid][pVehDamage][3] = 0;
		PlayerVehicle[vehicleid][pVehInterior] = GetPlayerInterior(ownerid);
		PlayerVehicle[vehicleid][pVehWorld] = GetPlayerVirtualWorld(ownerid);
		
		for(new j = 0; j < 17; j++){
			PlayerVehicle[vehicleid][pVehMod][j] = 0;}
		
		PlayerVehicle[vehicleid][pVehRental] = -1;
		PlayerVehicle[vehicleid][pVehRentTime] = 0;
		PlayerVehicle[vehicleid][pVehParked] = -1;
		PlayerVehicle[vehicleid][pVehHouseGarage] = -1;
		PlayerVehicle[vehicleid][pVehHelipadGarage] = -1;
		PlayerVehicle[vehicleid][pVehFamiliesGarage] = -1;
		PlayerVehicle[vehicleid][pVehFactStored] = -1;
		PlayerVehicle[vehicleid][pVehFaction] = factionid;

		PlayerVehicle[vehicleid][pVehEngineUpgrade] = 0;
		PlayerVehicle[vehicleid][pVehBodyUpgrade] = 0;
		PlayerVehicle[vehicleid][pVehBodyRepair] = 0;

		PlayerVehicle[vehicleid][pVehBroken] = 0;
		PlayerVehicle[vehicleid][pVehInsuranced] = false;
		PlayerVehicle[vehicleid][pVehImpounded] = false;
		PlayerVehicle[vehicleid][pVehImpoundDuration] = 0;
		PlayerVehicle[vehicleid][pVehImpoundFee] = 0;
		PlayerVehicle[vehicleid][pVehImpoundReason] = EOS;
		PlayerVehicle[vehicleid][vehDonation] = 0;
		PlayerVehicle[vehicleid][pVehDCTime] = 0;

		for(new wp; wp < 3; wp ++)
		{
			PlayerVehicle[vehicleid][pVehWeapon][wp] = 0;
			PlayerVehicle[vehicleid][pVehAmmo][wp] = 0;
		}
		new Float:defaultCap = 15.0; // fallback
        if(IsLuxuryVeh(modelid)) defaultCap = 30.0;
        else if(IsCompactVeh(modelid)) defaultCap = 20.0;
        else if(IsTruckVeh(modelid)) defaultCap = 60.0;
        PlayerVehicle[vehicleid][pVehCapacity] = defaultCap;
		PlayerVehicle[vehicleid][pVehWeight] = 0.0;
		
		PlayerVehicle[vehicleid][pVehPhysic] = CreateVehicle(PlayerVehicle[vehicleid][pVehModelID], PlayerVehicle[vehicleid][pVehPos][0], PlayerVehicle[vehicleid][pVehPos][1], PlayerVehicle[vehicleid][pVehPos][2], PlayerVehicle[vehicleid][pVehPos][3], PlayerVehicle[vehicleid][pVehColor1], PlayerVehicle[vehicleid][pVehColor2], 60000);
		VehicleCore[PlayerVehicle[vehicleid][pVehPhysic]][vCoreFuel] = PlayerVehicle[vehicleid][pVehFuel];
		SetVehicleNumberPlate(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehPlate]);
		SetVehicleVirtualWorld(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehWorld]);
		LinkVehicleToInterior(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehInterior]);
		OnLoadVehicleMod(vehicleid);
		PutPlayerInVehicle(ownerid, PlayerVehicle[vehicleid][pVehPhysic], 0);

		// mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `player_vehicles` (`PVeh_OwnerID`, `PVeh_ModelID`, `PVeh_Faction`, `PVeh_Price`, `PVeh_Health`, `PVeh_Fuel`, `PVeh_Parked`, `PVeh_Housed`, `PVeh_Families`, `PVeh_FactionGarage`, `PVeh_Rental`, `PVeh_RentTime`, `PVeh_Plate`, \
		// `PVeh_PosX`, `PVeh_PosY`, `PVeh_PosZ`, `PVeh_PosA`, `PVeh_Color1`, `PVeh_Color2`, `PVeh_Paintjob`, `PVeh_World`, `PVeh_Interior`) VALUES (%d, %d, %d, %d, %f, %d, %d, %d, %d, %d, %d, %d, '%s', %f, %f, %f, %f, %d, %d, %d, %d, %d)", PlayerVehicle[vehicleid][pVehOwnerID], PlayerVehicle[vehicleid][pVehModelID], PlayerVehicle[vehicleid][pVehPrice],
		// PlayerVehicle[vehicleid][pVehFaction], PlayerVehicle[vehicleid][pVehHealth], PlayerVehicle[vehicleid][pVehFuel], PlayerVehicle[vehicleid][pVehParked], PlayerVehicle[vehicleid][pVehHouseGarage], PlayerVehicle[vehicleid][pVehFamiliesGarage], PlayerVehicle[vehicleid][pVehFactStored], PlayerVehicle[vehicleid][pVehRental], PlayerVehicle[vehicleid][pVehRentTime], PlayerVehicle[vehicleid][pVehPlate], PlayerVehicle[vehicleid][pVehPos][0],
		// PlayerVehicle[vehicleid][pVehPos][1], PlayerVehicle[vehicleid][pVehPos][2], PlayerVehicle[vehicleid][pVehPos][3], PlayerVehicle[vehicleid][pVehColor1], PlayerVehicle[vehicleid][pVehColor2], PlayerVehicle[vehicleid][pVehPaintjob], PlayerVehicle[vehicleid][pVehWorld], PlayerVehicle[vehicleid][pVehInterior]);
		mysql_tquery(g_SQL, "INSERT INTO `player_vehicles` (`PVeh_Faction`) VALUES('0')", "OnVehCreated", "d", vehicleid);
		return vehicleid;
	}
	return -1;
}

VehicleFaction_Create(ownerid, modelid, factionid, Float:x, Float:y, Float:z, Float:a, color1, color2)
{
	static vehicleid;
	if ((vehicleid = Iter_Free(PvtVehicles)) != cellmin)
	{
		Iter_Add(PvtVehicles, vehicleid);

		PlayerVehicle[vehicleid][pVehExists] = true;

		PlayerVehicle[vehicleid][pVehOwnerID] = AccountData[ownerid][pID];
		PlayerVehicle[vehicleid][pVehModelID] = modelid;
		PlayerVehicle[vehicleid][pVehColor1] = color1;
		PlayerVehicle[vehicleid][pVehColor2] = color2;
		PlayerVehicle[vehicleid][pVehPaintjob] = -1;
		PlayerVehicle[vehicleid][pVehNeon] = 0;
		PlayerVehicle[vehicleid][cTogNeon] = 0;

		PlayerVehicle[vehicleid][pVehLocked] = false;
		format(PlayerVehicle[vehicleid][pVehPlate], 64, "-");
		PlayerVehicle[vehicleid][pVehPlateTime] = 0;
		PlayerVehicle[vehicleid][pVehPlateOwn] = 0;
		//PlayerVehicle[vehicleid][pVehPrice] = cost;
		
		PlayerVehicle[vehicleid][pVehHealth] = 1000.0;
		PlayerVehicle[vehicleid][pVehFuel] = MAX_FUEL_FULL;
		PlayerVehicle[vehicleid][pVehPos][0] = x;
		PlayerVehicle[vehicleid][pVehPos][1] = y;
		PlayerVehicle[vehicleid][pVehPos][2] = z;
		PlayerVehicle[vehicleid][pVehPos][3] = a;

		PlayerVehicle[vehicleid][pVehDamage][0] = 0;
		PlayerVehicle[vehicleid][pVehDamage][1] = 0;
		PlayerVehicle[vehicleid][pVehDamage][2] = 0;
		PlayerVehicle[vehicleid][pVehDamage][3] = 0;
		PlayerVehicle[vehicleid][pVehInterior] = GetPlayerInterior(ownerid);
		PlayerVehicle[vehicleid][pVehWorld] = GetPlayerVirtualWorld(ownerid);
		
		for(new j = 0; j < 17; j++){
			PlayerVehicle[vehicleid][pVehMod][j] = 0;}
		
		PlayerVehicle[vehicleid][pVehRental] = -1;
		PlayerVehicle[vehicleid][pVehRentTime] = 0;
		PlayerVehicle[vehicleid][pVehParked] = -1;
		PlayerVehicle[vehicleid][pVehHouseGarage] = -1;
		PlayerVehicle[vehicleid][pVehHelipadGarage] = -1;
		PlayerVehicle[vehicleid][pVehFamiliesGarage] = -1;
		PlayerVehicle[vehicleid][pVehFactStored] = -1;
		PlayerVehicle[vehicleid][pVehFaction] = factionid;

		PlayerVehicle[vehicleid][pVehBroken] = 0;
		PlayerVehicle[vehicleid][pVehInsuranced] = false;
		PlayerVehicle[vehicleid][pVehImpounded] = false;
		PlayerVehicle[vehicleid][pVehImpoundDuration] = 0;
		PlayerVehicle[vehicleid][pVehImpoundFee] = 0;
		PlayerVehicle[vehicleid][pVehImpoundReason] = EOS;
		PlayerVehicle[vehicleid][vehDonation] = 0;
		PlayerVehicle[vehicleid][pVehDCTime] = 0;

		forex(wp, 3)
		{
			PlayerVehicle[vehicleid][pVehWeapon][wp] = 0;
			PlayerVehicle[vehicleid][pVehAmmo][wp] = 0;
		}
		new Float:defaultCap = 15.0; // fallback
        if(IsLuxuryVeh(modelid)) defaultCap = 30.0;
        else if(IsCompactVeh(modelid)) defaultCap = 20.0;
        else if(IsTruckVeh(modelid)) defaultCap = 60.0;
        PlayerVehicle[vehicleid][pVehCapacity] = defaultCap;
		PlayerVehicle[vehicleid][pVehWeight] = 0.0;

		if(PlayerVehicle[vehicleid][pVehFaction] == FACTION_POLISI || PlayerVehicle[vehicleid][pVehFaction] == FACTION_EMS)
		{
			PlayerVehicle[vehicleid][pVehPhysic] = CreateVehicle(PlayerVehicle[vehicleid][pVehModelID], PlayerVehicle[vehicleid][pVehPos][0], PlayerVehicle[vehicleid][pVehPos][1], PlayerVehicle[vehicleid][pVehPos][2], PlayerVehicle[vehicleid][pVehPos][3], PlayerVehicle[vehicleid][pVehColor1], PlayerVehicle[vehicleid][pVehColor2], 60000, 1);
			VehicleCore[PlayerVehicle[vehicleid][pVehPhysic]][vCoreFuel] = PlayerVehicle[vehicleid][pVehFuel];
			SetVehicleNumberPlate(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehPlate]);
			SetVehicleVirtualWorld(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehWorld]);
			LinkVehicleToInterior(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehInterior]);
		}
		else
		{
			PlayerVehicle[vehicleid][pVehPhysic] = CreateVehicle(PlayerVehicle[vehicleid][pVehModelID], PlayerVehicle[vehicleid][pVehPos][0], PlayerVehicle[vehicleid][pVehPos][1], PlayerVehicle[vehicleid][pVehPos][2], PlayerVehicle[vehicleid][pVehPos][3], PlayerVehicle[vehicleid][pVehColor1], PlayerVehicle[vehicleid][pVehColor2], 60000, 0);
			VehicleCore[PlayerVehicle[vehicleid][pVehPhysic]][vCoreFuel] = PlayerVehicle[vehicleid][pVehFuel];
			SetVehicleNumberPlate(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehPlate]);
			SetVehicleVirtualWorld(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehWorld]);
			LinkVehicleToInterior(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehInterior]);
		}
		OnLoadVehicleMod(vehicleid);

		mysql_tquery(g_SQL, sprintf("INSERT INTO `player_vehicles` (`PVeh_Faction`) VALUES(%d)", PlayerVehicle[vehicleid][pVehFaction]), "OnVehFactionCreated", "ii", ownerid, vehicleid);
		return vehicleid;
	}
	return -1;
}

forward OnVehFactionCreated(playerid, carid);
public OnVehFactionCreated(playerid, carid)
{
	if(carid == -1 || !PlayerVehicle[carid][pVehExists])
		return 0;
	
	PlayerVehicle[carid][pVehID] = cache_insert_id();
	PlayerVehicle[carid][pVehExists] = true;
	SavePlayerVehicle(carid);

	PutPlayerInVehicle(playerid, PlayerVehicle[carid][pVehPhysic], 0);
	return 1;
}

forward OnVehRentalCreated(playerid, carid);
public OnVehRentalCreated(playerid, carid)
{
	if(carid == -1 || !PlayerVehicle[carid][pVehExists])
		return 0;
	
	PlayerVehicle[carid][pVehID] = cache_insert_id();
	PlayerVehicle[carid][pVehExists] = true;
	SavePlayerVehicle(carid);

	PutPlayerInVehicle(playerid, PlayerVehicle[carid][pVehPhysic], 0);
	// SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[carid][pVehPhysic], 0);
	return 1;
}

forward OnVehBuyCreated(playerid, carid);
public OnVehBuyCreated(playerid, carid)
{
	if(carid == -1 || !PlayerVehicle[carid][pVehExists])
		return 0;

	PlayerVehicle[carid][pVehID] = cache_insert_id();
	PlayerVehicle[carid][pVehExists] = true;
	SavePlayerVehicle(carid);

	SetTimerEx("ForcedPlayerHopInBuyVeh", 1500, false, "idd", playerid, PlayerVehicle[carid][pVehPhysic], 0);
	return 1;
}

forward OnVehCreated(carid);
public OnVehCreated(carid)
{
	if(carid == -1 || !PlayerVehicle[carid][pVehExists])
		return 0;
	
	PlayerVehicle[carid][pVehID] = cache_insert_id();
	PlayerVehicle[carid][pVehExists] = true;
	SavePlayerVehicle(carid);
	return 1;
}

forward OnPlayerVehicleRespawn(i);
public OnPlayerVehicleRespawn(i)
{
	if(PlayerVehicle[i][pVehFaction] == FACTION_POLISI || PlayerVehicle[i][pVehFaction] == FACTION_EMS)
	{
		PlayerVehicle[i][pVehPhysic] = CreateVehicle(PlayerVehicle[i][pVehModelID], PlayerVehicle[i][pVehPos][0], PlayerVehicle[i][pVehPos][1], PlayerVehicle[i][pVehPos][2], PlayerVehicle[i][pVehPos][3], PlayerVehicle[i][pVehColor1], PlayerVehicle[i][pVehColor2], 60000, 1);
		VehicleCore[PlayerVehicle[i][pVehPhysic]][vCoreFuel] = PlayerVehicle[i][pVehFuel];
		SetVehicleNumberPlate(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehPlate]);
		SetVehicleVirtualWorld(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehWorld]);
		LinkVehicleToInterior(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehInterior]);
	}
	else 
	{
		PlayerVehicle[i][pVehPhysic] = CreateVehicle(PlayerVehicle[i][pVehModelID], PlayerVehicle[i][pVehPos][0], PlayerVehicle[i][pVehPos][1], PlayerVehicle[i][pVehPos][2], PlayerVehicle[i][pVehPos][3], PlayerVehicle[i][pVehColor1], PlayerVehicle[i][pVehColor2], 60000);
		VehicleCore[PlayerVehicle[i][pVehPhysic]][vCoreFuel] = PlayerVehicle[i][pVehFuel];
		SetVehicleNumberPlate(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehPlate]);
		SetVehicleVirtualWorld(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehWorld]);
		LinkVehicleToInterior(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehInterior]);
	}

	if(PlayerVehicle[i][pVehHealth] < 350.0)
	{
		SetValidVehicleHealth(PlayerVehicle[i][pVehPhysic], 350.0);
	}
	else 
	{
		SetValidVehicleHealth(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehHealth]);
	}
	UpdateVehicleDamageStatus(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehDamage][0], PlayerVehicle[i][pVehDamage][1], PlayerVehicle[i][pVehDamage][2], PlayerVehicle[i][pVehDamage][3]);
	if(PlayerVehicle[i][pVehPaintjob] != -1)
	{
		ChangeVehiclePaintjob(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehPaintjob]);
	}
	OnLoadVehicleMod(i);

	for (new idx = 0; idx < MAX_VEHICLE_OBJECT; idx ++) if (VehicleObjects[i][idx][vehObjectVehicleIndex] == PlayerVehicle[i][pVehID] && VehicleObjects[i][idx][vehObjectExists])
	{
		Vehicle_AttachObject(i, idx);
	}

	for(new z = 0; z < 17; z ++)
	{
		if(PlayerVehicle[i][pVehMod][z]) AddVehicleComponent(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehMod][z]);
	}
	
	if(PlayerVehicle[i][pVehLocked])
	{
		LockVehicle(PlayerVehicle[i][pVehPhysic], true);
	}
	else 
	{
		LockVehicle(PlayerVehicle[i][pVehPhysic], false);
	}

	if(IsEngineVehicle(PlayerVehicle[i][pVehPhysic]))
	{
		SwitchVehicleEngine(PlayerVehicle[i][pVehPhysic], false);
	}
	else 
	{
		SwitchVehicleEngine(PlayerVehicle[i][pVehPhysic], true);
	}
	return 1;
}

forward OnLoadVehicleMod(vehid);
public OnLoadVehicleMod(vehid)
{
	if(IsValidVehicle(PlayerVehicle[vehid][pVehPhysic]))
	{
		if(PlayerVehicle[vehid][vehDonation] == 1)
		{
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 535) // Slamvan
			{
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, "{FF0000}_________________", 130, "Arial", 25, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], -1.150, -1.370, 0.269, 0.000, 0.000, 0.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, "{000000}__________________", 130, "Arial", 25, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], -1.159, -1.290, 0.219, 0.000, 0.000, 0.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][2] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, "{FF0000}_________________", 130, "Arial", 25, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][2], PlayerVehicle[vehid][pVehPhysic], 1.152, -1.370, 0.269, 0.000, 0.000, 0.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][3] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, "{000000}__________________", 130, "Arial", 25, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][3], PlayerVehicle[vehid][pVehPhysic], 1.163, -1.290, 0.219, 0.000, 0.000, 0.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][4] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, "{000000}Classic Never Die", 130, "Monotype Corsiva", 50, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][4], PlayerVehicle[vehid][pVehPhysic], -0.590, -2.670, -0.389, 0.000, 0.000, 0.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][5] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, "{000000}Get Away From Me! Fucker", 130, "Monotype Corsiva", 40, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][5], PlayerVehicle[vehid][pVehPhysic], -1.184, 0.191, -0.419, 0.000, 0.000, -90.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][6] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][6], 0, "{FF0000}35", 130, "Arial", 100, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][6], PlayerVehicle[vehid][pVehPhysic], 1.219, 0.120, -0.069, 0.000, 0.000, 90.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][7] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][7], 0, "{FFFFFF}35", 130, "Arial", 100, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][7], PlayerVehicle[vehid][pVehPhysic], 1.229, 0.130, -0.059, 0.000, 0.000, 90.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][8] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][8], 0, "{FF0000}35", 130, "Arial", 100, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][8], PlayerVehicle[vehid][pVehPhysic], -1.201, 0.120, -0.069, 0.000, 0.000, -90.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][9] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][9], 0, "{FFFFFF}35", 130, "Arial", 100, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][9], PlayerVehicle[vehid][pVehPhysic], -1.203, 0.130, -0.059, 0.000, 0.000, -90.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][10] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][10], PlayerVehicle[vehid][pVehPhysic], 0.680, 0.848, 0.494, -10.800, 0.000, 180.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][11] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][11], 0, "{000000}Situ {ff0000}Sultan ?", 130, "Arial", 30, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][11], PlayerVehicle[vehid][pVehPhysic], 1.212, -0.120, -0.349, 0.000, 0.000, 90.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][12] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][12], 0, "{000000}Aku Si {FF0000}Slamvan :3", 130, "Arial", 30, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][12], PlayerVehicle[vehid][pVehPhysic], 1.212, -0.020, -0.449, 360.000, 0.000, 90.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][13] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][13], 0, "{FF0000}ATMADJA", 130, "Arial", 100, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][13], PlayerVehicle[vehid][pVehPhysic], -0.033, 1.495, 0.447, -85.199, 0.000, -179.099);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][14] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][14], 0, "{FFFFFF}ATMADJA", 130, "Arial", 100, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][14], PlayerVehicle[vehid][pVehPhysic], -0.003, 1.505, 0.448, -85.099, 0.000, 180.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][15] = CreateDynamicObject(1003,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][15], PlayerVehicle[vehid][pVehPhysic], 0.000, -2.580, 0.369, 0.000, 0.000, 0.000);
			}
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 424) // BF
			{
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(1003,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], 0.000, -1.570, 0.449, 0.000, 0.000, 0.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, "{FF0000}BEJO", 130, "Arial", 100, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], 0.000, 1.330, 0.247, -66.400, 0.000, 180.000);
				DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][2] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, "{FF0000}A", 130, "Wingdings", 100, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(DonationVehObject[PlayerVehicle[vehid][pVehPhysic]][2], PlayerVehicle[vehid][pVehPhysic], -0.270, 1.083, 0.371, -75.600, 360.000, 180.000);
			}
		}
		if(PlayerVehicle[vehid][pVehFaction] == FACTION_POLISI)
		{
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 560) // Sultan Memet 23 array
			{
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, "{ffe14d} POLISI ", 130, "Arial Black", 60, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], 1.060, 0.000, 0.000, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, "{ffe14d} POLISI ", 130, "Arial Black", 60, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], -1.060, 0.000, 0.000, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, "{ffe14d} District ", 130, "Arial Black", 40, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], PlayerVehicle[vehid][pVehPhysic], 1.060, 0.000, -0.200, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, "{ffe14d} District ", 130, "Arial Black", 40, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], PlayerVehicle[vehid][pVehPhysic], -1.060, 0.000, -0.200, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, "{ffff00}POLUM", 130, "Arial Black", 60, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], PlayerVehicle[vehid][pVehPhysic], 0.000, -0.700, 0.790, 180.000, 90.000, 90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, "{ffe14d}_______", 130, "Arial Black", 90, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], PlayerVehicle[vehid][pVehPhysic], -0.010, -0.650, 0.789, 180.000, 90.000, 90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], 0, "{ffe14d}_______", 130, "Arial Black", 90, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], PlayerVehicle[vehid][pVehPhysic], -0.003, -0.432, 0.792, 180.000, 90.000, 90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], 0, "{ffe14d} POLISI ", 130, "Arial Black", 70, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], PlayerVehicle[vehid][pVehPhysic], 0.029, 2.100, 0.270, 539.989, 99.000, 270.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8], PlayerVehicle[vehid][pVehPhysic], -0.670, 2.690, -0.220, 180.000, 0.000, 360.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9], PlayerVehicle[vehid][pVehPhysic], -0.670, -2.430, -0.170, 23.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], 0, "{ffff4d} /", 130, "Arial Black", 120, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], PlayerVehicle[vehid][pVehPhysic], 1.060, 0.749, -0.069, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], 0, "{ffff4d} /", 130, "Arial Black", 120, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], PlayerVehicle[vehid][pVehPhysic], -1.060, 0.749, -0.069, 0.000, 0.000, -180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][12] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][12], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][12], 0, "{ff0000}/", 130, "Arial Black", 120, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][12], PlayerVehicle[vehid][pVehPhysic], 1.060, 0.720, -0.069, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][13] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][13], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][13], 0, "{ff0000}/", 130, "Arial Black", 120, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][13], PlayerVehicle[vehid][pVehPhysic], -1.060, 0.720, -0.069, 0.000, 0.000, -180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][14] = CreateDynamicObject(19620,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][14], PlayerVehicle[vehid][pVehPhysic], 0.000, -0.300, 0.900, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][15] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][15], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][15], 0, "{ffc0cb}/", 130, "Arial Black", 120, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][15], PlayerVehicle[vehid][pVehPhysic], 1.060, 0.759, -0.069, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][16] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][16], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][16], 0, "{ffc0cb}/", 130, "Arial Black", 120, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][16], PlayerVehicle[vehid][pVehPhysic], -1.060, 0.759, -0.069, 0.000, 0.000, -180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][17] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][17], PlayerVehicle[vehid][pVehPhysic], 0.670, -2.430, -0.170, 517.000, 0.000, 540.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][18] = CreateDynamicObject(19893,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][18], PlayerVehicle[vehid][pVehPhysic], 0.000, 0.439, -0.170, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][19] = CreateDynamicObject(1185,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][19], 0, 10101, "2notherbuildsfe", "ferry_build14", 0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][19], 1, -1, "none", "none", -13434880);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][19], PlayerVehicle[vehid][pVehPhysic], 1.000, 2.590, -0.220, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][20] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][20], PlayerVehicle[vehid][pVehPhysic], 0.670, 2.690, -0.220, 0.000, 0.000, -180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][21] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][21], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][21], 0, "{ffff00} 110", 130, "Arial Black", 120, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][21], PlayerVehicle[vehid][pVehPhysic], -0.069, -1.269, 0.617, 0.000, 297.000, 270.000);
			}
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 415) // Cheetah 
			{
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, "{0000ff} POLISI", 130, "Arial Black", 50, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], 1.014, -0.900, 0.029, -5.000, -11.000, 1.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, "{0000ff} POLISI", 130, "Arial Black", 50, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], -1.014, -0.840, 0.029, 367.000, 710.000, 1259.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, "{0000ff} District ", 130, "Arial Black", 24, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], PlayerVehicle[vehid][pVehPhysic], 1.032, -0.860, -0.109, -5.000, -8.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, "{0000ff} District ", 130, "Arial Black", 24, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], PlayerVehicle[vehid][pVehPhysic], -1.033, -0.814, -0.110, 367.000, 349.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, "{0000ff} SPEED HUNTER", 130, "Arial Black", 25, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], PlayerVehicle[vehid][pVehPhysic], 0.019, 2.500, -0.059, 360.000, 287.000, 90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, "{0000ff}POLUTAS", 130, "Arial Black", 25, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], PlayerVehicle[vehid][pVehPhysic], 0.000, 0.300, 0.463, 0.000, -67.000, 90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], 0, "{0000ff}POLUTAS", 130, "Arial Black", 30, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], PlayerVehicle[vehid][pVehPhysic], 0.000, -0.960, 0.550, 0.000, -83.800, -90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], 0, "{ffffff} 110", 130, "Arial Black", 65, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], PlayerVehicle[vehid][pVehPhysic], -0.049, -1.060, 0.420, 0.000, -22.000, 270.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8], 0, "{0000ff}\\", 130, "Arial Black", 85, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8], PlayerVehicle[vehid][pVehPhysic], 1.014, -0.420, -0.061, -5.240, -10.449, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9], 0, "{0000ff}\\", 130, "Arial Black", 85, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9], PlayerVehicle[vehid][pVehPhysic], -1.024, -0.420, -0.071, -5.240, 10.449, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], 0, "{ff0000}\\", 130, "Arial Black", 85, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], PlayerVehicle[vehid][pVehPhysic], 1.014, -0.450, -0.058, -5.000, -10.189, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], 0, "{ff0000}\\", 130, "Arial Black", 85, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], PlayerVehicle[vehid][pVehPhysic], -1.024, -0.448, -0.068, -5.000, 10.189, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][12] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][12], PlayerVehicle[vehid][pVehPhysic], 0.200, 2.650, -0.210, -14.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][13] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][13], PlayerVehicle[vehid][pVehPhysic], -0.200, 2.650, -0.210, -14.000, 0.000, -180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][14] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][14], PlayerVehicle[vehid][pVehPhysic], -0.700, -2.430, -0.190, 5.000, 0.000, 360.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][15] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][15], PlayerVehicle[vehid][pVehPhysic], 0.700, -2.430, -0.190, 5.000, 0.000, -360.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][16] = CreateDynamicObject(19620,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][16], PlayerVehicle[vehid][pVehPhysic], 0.000, -0.580, 0.639, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][17] = CreateDynamicObject(1185,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][17], 1, -1, "none", "none", -16764058);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][17], PlayerVehicle[vehid][pVehPhysic], 1.009, 2.650, -0.382, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][18] = CreateDynamicObject(364,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][18], PlayerVehicle[vehid][pVehPhysic], 0.589, -1.240, 0.349, 180.000, 90.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][19] = CreateDynamicObject(19893,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][19], PlayerVehicle[vehid][pVehPhysic], 0.000, 0.159, -0.270, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][20] = CreateDynamicObject(19917,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][20], PlayerVehicle[vehid][pVehPhysic], 0.000, -1.530, -0.459, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][21] = CreateDynamicObject(1003,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][21], PlayerVehicle[vehid][pVehPhysic], 0.000, -2.259, 0.100, 0.000, 0.000, 0.000);
			}
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 541) // Bullet Speed Hunter
			{
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(1002,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], 0.000, -2.100, 0.300, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, "{ffff00} POLISI", 130, "Arial Black", 45, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], 0.989, -0.099, -0.000, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, "{ffff00} POLISI", 130, "Arial Black", 45, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], PlayerVehicle[vehid][pVehPhysic], -0.989, -0.049, -0.000, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, "{ffff00} District ", 130, "Arial Black", 25, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], PlayerVehicle[vehid][pVehPhysic], 0.986, -0.150, -0.129, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, "{ffff00} District ", 130, "Arial Black", 25, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], PlayerVehicle[vehid][pVehPhysic], -0.986, -0.150, -0.129, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, "{ffff00}POLUM", 130, "Arial Black", 40, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], PlayerVehicle[vehid][pVehPhysic], 0.009, -0.850, 0.542, 0.000, -80.799, 270.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], 0, "{ffffff} 110", 130, "Arial Black", 100, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], PlayerVehicle[vehid][pVehPhysic], -0.059, -1.120, 0.497, 0.000, -78.499, 270.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], 0, "{ffffff} SPEED", 130, "Arial Black", 22, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], PlayerVehicle[vehid][pVehPhysic], 0.419, 2.289, 0.035, 0.000, -64.000, 90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8], PlayerVehicle[vehid][pVehPhysic], -0.400, -2.250, 0.089, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9], PlayerVehicle[vehid][pVehPhysic], 0.400, -2.250, 0.089, 180.000, 0.000, 540.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10] = CreateDynamicObject(1185,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], 0, -1, "none", "none", -16777063);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], 1, -1, "none", "none", -13434880);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], PlayerVehicle[vehid][pVehPhysic], 1.010, 2.359, -0.240, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], PlayerVehicle[vehid][pVehPhysic], -0.679, 2.459, -0.240, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][12] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][12], PlayerVehicle[vehid][pVehPhysic], 0.679, 2.459, -0.240, 180.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][13] = CreateDynamicObject(19620,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][13], PlayerVehicle[vehid][pVehPhysic], 0.000, -0.429, 0.670, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][14] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][14], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][14], 0, "{ffffff} lu kontol", 130, "Arial Black", 11, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][14], PlayerVehicle[vehid][pVehPhysic], -0.499, 0.500, 0.360, 0.000, 0.000, 270.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][15] = CreateDynamicObject(19893,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][15], PlayerVehicle[vehid][pVehPhysic], 0.000, 0.119, -0.099, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][16] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][16], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][16], 0, "{ffffff} HUNTER", 130, "Arial Black", 22, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][16], PlayerVehicle[vehid][pVehPhysic], -0.440, 2.289, 0.035, 0.000, -64.000, 90.000);
			}
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 426) // Premier
			{
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, "{FFFF00}POLISI", 130, "Arial", 30, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], -1.110, -0.019, 0.000, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, "{FFFF00}<<", 120, "Arial", 60, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], -1.110, -0.880, -0.089, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, "{FFFF00}<", 120, "Arial", 60, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], PlayerVehicle[vehid][pVehPhysic], -1.110, 0.889, -0.089, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, "{FFFF00}POLDA DISTRICT", 130, "Arial", 18, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], PlayerVehicle[vehid][pVehPhysic], -1.110, -0.019, -0.289, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4] = CreateDynamicObject(19620,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], PlayerVehicle[vehid][pVehPhysic], 0.000, -0.360, 0.850, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, "{FFFF00}POLISI", 130, "Arial", 40, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], PlayerVehicle[vehid][pVehPhysic], -0.030, 1.686, 0.275, 0.000, -85.499, -270.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], 0, "{FFFF00}______", 130, "Arial", 40, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], PlayerVehicle[vehid][pVehPhysic], -0.030, 1.796, 0.267, 0.000, -85.699, 90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], 0, "{FFFF00}POLISI", 130, "Arial", 30, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], PlayerVehicle[vehid][pVehPhysic], 1.109, -0.019, 0.000, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8], 0, "{FFFF00}<<", 120, "Arial", 60, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8], PlayerVehicle[vehid][pVehPhysic], 1.115, -0.880, -0.089, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9], 0, "{FFFF00}<", 120, "Arial", 60, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9], PlayerVehicle[vehid][pVehPhysic], 1.119, 0.889, -0.089, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], 0, "{FFFF00}POLDA DISTRICT", 130, "Arial", 18, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], PlayerVehicle[vehid][pVehPhysic], 1.109, -0.019, -0.289, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], 0, "{FFFF00}911", 130, "Arial", 50, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], PlayerVehicle[vehid][pVehPhysic], 0.059, -1.627, 0.585, 0.000, -54.999, 270.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][13] = CreateDynamicObject(1181,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][13], PlayerVehicle[vehid][pVehPhysic], -0.890, 2.520, -0.179, 0.000, 0.000, 0.000);
			}
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 468) // Sanchez PD 
			{
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, "{FFFF00}POLISI", 130, "Arial", 25, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], -0.120, 0.190, 0.318, 0.000, 45.799, -90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, "{FFFF00}POLISI", 130, "Arial", 25, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], 0.118, 0.153, 0.285, 0.000, -43.799, 90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, "{FFFF00}<<", 120, "Arial", 30, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], PlayerVehicle[vehid][pVehPhysic], -0.179, -0.469, 0.119, -3.099, 0.000, -93.299);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, "{FFFF00}>>", 120, "Arial", 30, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], PlayerVehicle[vehid][pVehPhysic], 0.190, -0.519, 0.119, 0.000, 0.000, 90.000);
			}
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 601) // Baracuda
			{
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(1424,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, -1, "none", "none", -13421773);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 1, -1, "none", "none", -16777216);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], 0.000, 3.199, 0.300, 180.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(1424,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, -1, "none", "none", -13421773);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 1, -1, "none", "none", -16777216);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], 0.000, 3.199, 1.000, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], PlayerVehicle[vehid][pVehPhysic], 0.544, -3.089, 0.259, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, "{ffffff} DISTRICT", 130, "Arial Black", 40, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], PlayerVehicle[vehid][pVehPhysic], 1.240, -1.200, 0.930, 0.000, -24.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, "{ffffff} DISTRICT", 130, "Arial Black", 40, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], PlayerVehicle[vehid][pVehPhysic], -1.240, -1.200, 0.930, 0.000, -29.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], PlayerVehicle[vehid][pVehPhysic], -0.005, 3.218, 0.259, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], PlayerVehicle[vehid][pVehPhysic], -0.005, 3.218, 1.050, 0.000, 0.000, 180.000);
			}
		}
		if(PlayerVehicle[vehid][pVehFaction] == FACTION_PEMERINTAH)
		{
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 561) // Straatum
			{
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, "{ff5b77}PEMERINTAH", 130, "Arial Black", 50, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], 1.070, -0.089, 0.009, -0.100, -7.000, 0.150);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, "{ff5b77}PEMERINTAH", 130, "Arial Black", 50, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], -1.070, -0.089, 0.009, -0.100, -7.000, 179.860);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, "{ff5b77}District ", 130, "Arial Black", 30, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], PlayerVehicle[vehid][pVehPhysic], 1.084, -0.099, -0.170, 0.100, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, "{ff5b77}District ", 130, "Arial Black", 30, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], PlayerVehicle[vehid][pVehPhysic], -1.084, -0.099, -0.170, 0.100, 0.000, 180.000);
			}
		}
		if(PlayerVehicle[vehid][pVehFaction] == FACTION_EMS)
		{
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 468) // sanchez 1 Array
			{
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(2714,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, "{FFFFFF}EMS", 130, "Arial", 45, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], -0.109, 0.176, 0.328, -3.799, 46.699, 270.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(2714,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, "{FFFFFF}EMS", 130, "Arial", 45, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], 0.110, 0.183, 0.321, -4.699, -47.699, 90.000);
			}
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 416) // Ambulance
			{
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, "{ebebeb} District ", 130, "Arial Black", 65, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], 1.291, -1.600, 1.400, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(19940,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, 16093, "a51_ext", "cabin5", -6750208);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], 1.269, -1.450, 1.400, 0.000, 90.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2] = CreateDynamicObject(19940,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, 16093, "a51_ext", "cabin5", -6750208);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], PlayerVehicle[vehid][pVehPhysic], 1.270, -1.650, 1.400, 0.000, 90.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3] = CreateDynamicObject(19940,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, 16093, "a51_ext", "cabin5", -6750208);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], PlayerVehicle[vehid][pVehPhysic], -1.270, -1.650, 1.400, 0.000, -90.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4] = CreateDynamicObject(19940,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, 16093, "a51_ext", "cabin5", -6750208);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], PlayerVehicle[vehid][pVehPhysic], -1.269, -1.450, 1.400, 0.000, -90.000, -180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, "{ebebeb} District ", 130, "Arial Black", 65, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], PlayerVehicle[vehid][pVehPhysic], -1.291, -1.510, 1.400, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6] = CreateDynamicObject(1115,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], PlayerVehicle[vehid][pVehPhysic], 0.000, 3.008, -0.496, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], PlayerVehicle[vehid][pVehPhysic], 0.740, 2.970, -0.200, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8], PlayerVehicle[vehid][pVehPhysic], -0.740, 2.970, -0.200, 360.000, 180.000, -180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9], PlayerVehicle[vehid][pVehPhysic], -1.040, -3.649, -0.200, -360.000, 360.000, 360.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], PlayerVehicle[vehid][pVehPhysic], 1.040, -3.649, -0.200, 0.000, 180.000, -360.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], 0, "{0000ff}CALL CENTER 118", 130, "Arial Black", 55, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], PlayerVehicle[vehid][pVehPhysic], 1.291, -0.640, -0.339, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][12] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][12], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][12], 0, "{0000ff}CALL CENTER 118", 130, "Arial Black", 55, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][12], PlayerVehicle[vehid][pVehPhysic], -1.291, -0.640, -0.339, 360.000, 0.000, 180.000);
			}
		}
		if(PlayerVehicle[vehid][pVehFaction] == FACTION_BENGKEL)
		{
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 525) // towing 11 array
			{
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, "{ffffff} BENGKEL", 130, "Arial Black", 40, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], 1.190, 0.509, 0.339, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, "{ffffff} BENGKEL", 130, "Arial Black", 40, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], -1.190, 0.509, 0.339, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, "{ffffff} BENNYS DISTRICT", 130, "Arial Black", 40, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], PlayerVehicle[vehid][pVehPhysic], 1.190, 0.500, 0.200, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, "{ffffff} BENNYS DISTRICT", 130, "Arial Black", 40, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], PlayerVehicle[vehid][pVehPhysic], -1.190, 0.500, 0.200, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, "{0000ff} #SOBATOLI", 130, "Arial Black", 30, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], PlayerVehicle[vehid][pVehPhysic], 1.310, -2.399, 0.380, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, "{0000ff} #SOBATOLI", 130, "Arial Black", 30, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], PlayerVehicle[vehid][pVehPhysic], -1.310, -2.399, 0.380, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], 0, "{0000ff} MEKANIK KELILING", 130, "Arial Black", 30, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], PlayerVehicle[vehid][pVehPhysic], 0.000, -2.980, 0.100, 0.000, -40.000, 270.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7] = CreateDynamicObject(19900,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], PlayerVehicle[vehid][pVehPhysic], -0.400, -0.900, 0.000, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8] = CreateDynamicObject(19900,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8], PlayerVehicle[vehid][pVehPhysic], 0.400, -0.900, 0.000, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9] = CreateDynamicObject(18646,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9], PlayerVehicle[vehid][pVehPhysic], 0.700, 0.189, 1.410, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], 0, "{000000} HILUX", 130, "Impact", 30, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], PlayerVehicle[vehid][pVehPhysic], 0.000, 3.030, 0.610, 0.000, -35.000, 90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], 0, "{ffffff} HOTLINE /MEK", 130, "Impact", 30, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], PlayerVehicle[vehid][pVehPhysic], 0.000, -0.614, 1.245, 0.000, -16.000, 270.000);
			}
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 468) // Sanchez PD 
			{
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, "{FFB5C5}BENGKEL", 130, "Arial", 25, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], -0.120, 0.190, 0.318, 0.000, 45.799, -90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, "{FFB5C5}BENGKEL", 130, "Arial", 25, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], 0.118, 0.153, 0.285, 0.000, -43.799, 90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, "{FFB5C5}>>", 120, "Arial", 30, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], PlayerVehicle[vehid][pVehPhysic], -0.179, -0.469, 0.119, -3.099, 0.000, -93.299);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, "{FFB5C5}<<", 120, "Arial", 30, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], PlayerVehicle[vehid][pVehPhysic], 0.190, -0.519, 0.119, 0.000, 0.000, 90.000);
			}
		}
		if(PlayerVehicle[vehid][pVehFaction] == FACTION_PEDAGANG)
		{
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 489) 
			{
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, "{FFFFFF},", 130, "Webdings", 150, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], -1.220, -0.040, -0.099, 0.000, 0.000, -90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, "{FFFFFF}Resto", 130, "Arial", 80, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], -1.220, 0.520, -0.139, 0.000, 0.000, -90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, "{FFFFFF}Notowijoyo", 130, "Arial", 60, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], PlayerVehicle[vehid][pVehPhysic], -1.220, 0.369, -0.369, 0.000, 0.000, -90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, "{FFFFFF}/", 130, "Webdings", 150, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], PlayerVehicle[vehid][pVehPhysic], -1.220, -0.899, 0.079, 0.000, 0.000, -90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, "{FFFF00}/", 130, "Webdings", 150, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], PlayerVehicle[vehid][pVehPhysic], -1.220, -0.619, 0.079, 0.000, 0.000, -90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, "{FFFFFF}Resto", 130, "Arial", 80, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], PlayerVehicle[vehid][pVehPhysic], 1.217, -0.030, -0.139, 0.000, 0.000, 90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], 0, "{FFFFFF},", 130, "Webdings", 120, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], PlayerVehicle[vehid][pVehPhysic], 1.217, 0.559, -0.119, 0.000, 0.000, 90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], 0, "{FFFFFF}Notowijoyo", 130, "Arial", 60, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], PlayerVehicle[vehid][pVehPhysic], 1.205, 0.129, -0.369, 0.000, 0.000, 450.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8], 0, "{FFFFFF}/", 130, "Webdings", 150, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8], PlayerVehicle[vehid][pVehPhysic], 1.219, -0.969, 0.069, 0.000, 0.000, 90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9], 0, "{FFFF00}/", 130, "Webdings", 150, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9], PlayerVehicle[vehid][pVehPhysic], 1.219, -0.679, 0.069, 0.000, 0.000, 90.000);
			}
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 483) // Camper 14 Array
			{
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(1445,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], 0.000, -1.400, 1.540, 0.000, 0.000, 90.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(1116,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], 0.000, 2.999, -0.649, 15.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, "{ffffff} RESTAURANT", 130, "Arial Black", 40, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], PlayerVehicle[vehid][pVehPhysic], 0.915, -1.580, -0.039, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, "{ffffff} RESTAURANT", 130, "Arial Black", 40, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], PlayerVehicle[vehid][pVehPhysic], -0.915, -1.580, -0.039, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, "{ffffff} DISTRICT", 130, "Arial Black", 40, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], PlayerVehicle[vehid][pVehPhysic], 0.920, -1.580, -0.200, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, "{ffffff} DISTRICT", 130, "Arial Black", 40, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], PlayerVehicle[vehid][pVehPhysic], -0.920, -1.580, -0.200, 0.000, 0.000, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6] = CreateDynamicObject(2453,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], 1, 16093, "a51_ext", "des_backdoor1", 0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], PlayerVehicle[vehid][pVehPhysic], 0.300, -3.019, -0.100, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7] = CreateDynamicObject(2453,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], 1, 16093, "a51_ext", "des_backdoor1", 0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], PlayerVehicle[vehid][pVehPhysic], -0.300, -3.019, -0.100, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8] = CreateDynamicObject(2425,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8], 4, 16093, "a51_ext", "des_backdoor1", 0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8], PlayerVehicle[vehid][pVehPhysic], 0.250, -2.850, 0.274, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9] = CreateDynamicObject(2702,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9], PlayerVehicle[vehid][pVehPhysic], 0.000, 2.835, 0.000, 92.000, 354.000, 450.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], 0, "{ff0000} Q", 130, "GTAWEAPON3", 90, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], PlayerVehicle[vehid][pVehPhysic], 0.820, -2.439, 0.600, 5.000, -9.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], 0, "{ff0000} Q", 130, "GTAWEAPON3", 90, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], PlayerVehicle[vehid][pVehPhysic], -0.820, -2.439, 0.600, 5.000, 9.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][12] = CreateDynamicObject(19580,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][12], PlayerVehicle[vehid][pVehPhysic], 0.920, -0.750, -0.140, 0.000, 88.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][13] = CreateDynamicObject(19580,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][13], PlayerVehicle[vehid][pVehPhysic], -0.920, -0.750, -0.140, 0.000, -88.000, 0.000);
			}
		}
		if(PlayerVehicle[vehid][pVehFaction] == FACTION_TRANS)
		{
			if(GetVehicleModel(PlayerVehicle[vehid][pVehPhysic]) == 405) // Sentinel
			{
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0] = CreateDynamicObject(19311,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], 0, -1, "none", "none", -16777216);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][0], PlayerVehicle[vehid][pVehPhysic], 0.000, -0.399, 0.840, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], 0, "{ff748c} TRANS", 130, "Arial Black", 35, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][1], PlayerVehicle[vehid][pVehPhysic], 0.072, -0.400, 0.850, 0.000, -7.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], 0, "{ff748c} TRANS", 130, "Arial Black", 35, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][2], PlayerVehicle[vehid][pVehPhysic], -0.066, -0.400, 0.850, 0.000, -8.509, 180.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], 0, "{ff748c} PESAN MELALUI", 130, "Arial Black", 18, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][3], PlayerVehicle[vehid][pVehPhysic], 0.000, -1.241, 0.619, 0.100, -64.000, 270.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], 0, "{ff748c} SMARTPHONE", 130, "Arial Black", 21, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][4], PlayerVehicle[vehid][pVehPhysic], 0.000, -1.320, 0.582, 0.000, -63.000, 270.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], 0, "{ff748c} AMAN SAMPAI TUJUAN", 130, "Arial Black", 15, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][5], PlayerVehicle[vehid][pVehPhysic], 0.979, -1.900, 0.109, 1.000, -18.000, -0.610);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6] = CreateDynamicObject(19483,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0);
				SetDynamicObjectMaterialText(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], 0, "{ff748c} AMAN SAMPAI TUJUAN", 130, "Arial Black", 15, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][6], PlayerVehicle[vehid][pVehPhysic], -0.977, -1.850, 0.109, 1.000, -22.000, 181.610);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7] = CreateDynamicObject(1174,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], 7, -1, "none", "none", -6736999);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], 7, -1, "none", "none", -13421773);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][7], PlayerVehicle[vehid][pVehPhysic], -0.918, 2.539, -0.430, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8] = CreateDynamicObject(18646,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8], 1, 10101, "2notherbuildsfe", "ferry_build14", -1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][8], PlayerVehicle[vehid][pVehPhysic], 0.000, 0.139, 0.790, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9] = CreateDynamicObject(18646,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9], 1, 10101, "2notherbuildsfe", "ferry_build14", -1);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][9], PlayerVehicle[vehid][pVehPhysic], 0.000, -0.940, 0.790, 0.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], 0, 5397, "barrio1_lae", "carwash_256", 0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][10], PlayerVehicle[vehid][pVehPhysic], 0.000, 2.350, 0.119, 83.000, 0.000, 0.000);
				FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11] = CreateDynamicObject(19797,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], 0, 5397, "barrio1_lae", "carwash_256", 0);
				AttachDynamicObjectToVehicle(FactionVehObject[PlayerVehicle[vehid][pVehPhysic]][11], PlayerVehicle[vehid][pVehPhysic], 0.000, -2.150, 0.260, -82.000, 0.000, 0.000);
			}
		}
	}
	return 1;
}

forward UnloadRentalVehicle(carid);
public UnloadRentalVehicle(carid)
{
	if(carid == -1 || !PlayerVehicle[carid][pVehExists])
		return 0;
	
	if(IsValidVehicle(carid))
	{
		if(PlayerVehicle[carid][pVehRental] != -1 || PlayerVehicle[carid][pVehRentTime] > 0)
		{
			PlayerVehicle[carid][pVehRental] = -1;
			PlayerVehicle[carid][pVehRentTime] = 0;
			PlayerVehicle[carid][pVehExists] = false;

			new strgbg[256];
			mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `id` = %d", PlayerVehicle[carid][pVehID]);
			mysql_tquery(g_SQL, strgbg);

			Iter_Remove(PvtVehicles, carid);
		}
	}
	return 1;
}

JavaTR: Vehicle_Load(playerid)
{
	new vehicleid, tempname[64], tempImpound[256];
	new Cache:vehicleCache = cache_save();

	for (new i = 0; i != cache_num_rows(); i ++)
	{
		if ((vehicleid = Iter_Free(PvtVehicles)) != cellmin)
		{
			Iter_Add(PvtVehicles, vehicleid);
			
			PlayerVehicle[vehicleid][pVehExists] = true;
			cache_get_value_name_int(i, "id", PlayerVehicle[vehicleid][pVehID]);
			//PlayerVehicle[vehicleid][VehicleOwned] = true;
			cache_get_value_name_int(i, "PVeh_OwnerID", PlayerVehicle[vehicleid][pVehOwnerID]);
			cache_get_value_name_int(i, "PVeh_Locked", PlayerVehicle[vehicleid][pVehLocked]);
			cache_get_value_name_float(i, "PVeh_PosX", PlayerVehicle[vehicleid][pVehPos][0]);
			cache_get_value_name_float(i, "PVeh_PosY", PlayerVehicle[vehicleid][pVehPos][1]);
			cache_get_value_name_float(i, "PVeh_PosZ", PlayerVehicle[vehicleid][pVehPos][2]);
			cache_get_value_name_float(i, "PVeh_PosA", PlayerVehicle[vehicleid][pVehPos][3]);

			cache_get_value_name_float(i, "PVeh_Health", PlayerVehicle[vehicleid][pVehHealth]);
			// if(PlayerVehicle[vehicleid][pVehHealth] < 0.0 || PlayerVehicle[vehicleid][pVehHealth] > 1000.0) PlayerVehicle[vehicleid][pVehHealth] = 1000.0;

			cache_get_value_name_float(i, "PVeh_Capacity", PlayerVehicle[vehicleid][pVehCapacity]);
			cache_get_value_name_float(i, "PVeh_Weigh", PlayerVehicle[vehicleid][pVehWeight]);
			cache_get_value_name_int(i, "PVeh_Fuel", PlayerVehicle[vehicleid][pVehFuel]);
			cache_get_value_name_int(i, "PVeh_Interior", PlayerVehicle[vehicleid][pVehInterior]);
			cache_get_value_name_int(i, "PVeh_World", PlayerVehicle[vehicleid][pVehWorld]);
			cache_get_value_name_int(i, "PVeh_Damage0", PlayerVehicle[vehicleid][pVehDamage][0]);
			cache_get_value_name_int(i, "PVeh_Damage1", PlayerVehicle[vehicleid][pVehDamage][1]);
			cache_get_value_name_int(i, "PVeh_Damage2", PlayerVehicle[vehicleid][pVehDamage][2]);
			cache_get_value_name_int(i, "PVeh_Damage3", PlayerVehicle[vehicleid][pVehDamage][3]);
			cache_get_value_name_int(i, "PVeh_Color1", PlayerVehicle[vehicleid][pVehColor1]);
			cache_get_value_name_int(i, "PVeh_Color2", PlayerVehicle[vehicleid][pVehColor2]);
			cache_get_value_name_int(i, "PVeh_Paintjob", PlayerVehicle[vehicleid][pVehPaintjob]);
			cache_get_value_name_int(i, "PVeh_Neon", PlayerVehicle[vehicleid][pVehNeon]);
			PlayerVehicle[vehicleid][cTogNeon] = 0;
			cache_get_value_name_int(i, "PVeh_Price", PlayerVehicle[vehicleid][pVehPrice]);
			cache_get_value_name_int(i, "PVeh_ModelID", PlayerVehicle[vehicleid][pVehModelID]);
			cache_get_value_name(i, "PVeh_Plate", tempname);
			format(PlayerVehicle[vehicleid][pVehPlate], 256, tempname);
			cache_get_value_name_int(i, "PVeh_PlateTime", PlayerVehicle[vehicleid][pVehPlateTime]);
			cache_get_value_name_int(i, "PVeh_PlateOwned", PlayerVehicle[vehicleid][pVehPlateOwn]);

			cache_get_value_name_int(i, "PVeh_Mod0", PlayerVehicle[vehicleid][pVehMod][0]);
			cache_get_value_name_int(i, "PVeh_Mod1", PlayerVehicle[vehicleid][pVehMod][1]);
			cache_get_value_name_int(i, "PVeh_Mod2", PlayerVehicle[vehicleid][pVehMod][2]);
			cache_get_value_name_int(i, "PVeh_Mod3", PlayerVehicle[vehicleid][pVehMod][3]);
			cache_get_value_name_int(i, "PVeh_Mod4", PlayerVehicle[vehicleid][pVehMod][4]);
			cache_get_value_name_int(i, "PVeh_Mod5", PlayerVehicle[vehicleid][pVehMod][5]);
			cache_get_value_name_int(i, "PVeh_Mod6", PlayerVehicle[vehicleid][pVehMod][6]);
			cache_get_value_name_int(i, "PVeh_Mod7", PlayerVehicle[vehicleid][pVehMod][7]);
			cache_get_value_name_int(i, "PVeh_Mod8", PlayerVehicle[vehicleid][pVehMod][8]);
			cache_get_value_name_int(i, "PVeh_Mod9", PlayerVehicle[vehicleid][pVehMod][9]);
			cache_get_value_name_int(i, "PVeh_Mod10", PlayerVehicle[vehicleid][pVehMod][10]);
			cache_get_value_name_int(i, "PVeh_Mod11", PlayerVehicle[vehicleid][pVehMod][11]);
			cache_get_value_name_int(i, "PVeh_Mod12", PlayerVehicle[vehicleid][pVehMod][12]);
			cache_get_value_name_int(i, "PVeh_Mod13", PlayerVehicle[vehicleid][pVehMod][13]);
			cache_get_value_name_int(i, "PVeh_Mod14", PlayerVehicle[vehicleid][pVehMod][14]);
			cache_get_value_name_int(i, "PVeh_Mod15", PlayerVehicle[vehicleid][pVehMod][15]);
			cache_get_value_name_int(i, "PVeh_Mod16", PlayerVehicle[vehicleid][pVehMod][16]);
			
			// vehicle Upgrade 
			cache_get_value_name_int(i, "PVeh_EngineUpgrade", PlayerVehicle[vehicleid][pVehEngineUpgrade]);
			cache_get_value_name_int(i, "PVeh_BodyUpgrade", PlayerVehicle[vehicleid][pVehBodyUpgrade]);
			cache_get_value_name_float(i, "PVeh_BodyRepair", PlayerVehicle[vehicleid][pVehBodyRepair]);

			cache_get_value_name_int(i, "PVeh_Weapon1", PlayerVehicle[vehicleid][pVehWeapon][0]);
			cache_get_value_name_int(i, "PVeh_Weapon2", PlayerVehicle[vehicleid][pVehWeapon][1]);
			cache_get_value_name_int(i, "PVeh_Weapon3", PlayerVehicle[vehicleid][pVehWeapon][2]);
			cache_get_value_name_int(i, "PVeh_Ammo1", PlayerVehicle[vehicleid][pVehAmmo][0]);
			cache_get_value_name_int(i, "PVeh_Ammo2", PlayerVehicle[vehicleid][pVehAmmo][1]);
			cache_get_value_name_int(i, "PVeh_Ammo3", PlayerVehicle[vehicleid][pVehAmmo][2]);
            
			cache_get_value_name_int(i, "PVeh_Rental", PlayerVehicle[vehicleid][pVehRental]);
			cache_get_value_name_int(i, "PVeh_RentTime", PlayerVehicle[vehicleid][pVehRentTime]);
			cache_get_value_name_int(i, "PVeh_Parked", PlayerVehicle[vehicleid][pVehParked]);
			cache_get_value_name_int(i, "PVeh_Housed", PlayerVehicle[vehicleid][pVehHouseGarage]);
			cache_get_value_name_int(i, "PVeh_Helipad", PlayerVehicle[vehicleid][pVehHelipadGarage]);
			cache_get_value_name_int(i, "PVeh_Families", PlayerVehicle[vehicleid][pVehFamiliesGarage]);
			cache_get_value_name_int(i, "PVeh_FactionGarage", PlayerVehicle[vehicleid][pVehFactStored]);
			cache_get_value_name_int(i, "PVeh_Broken", PlayerVehicle[vehicleid][pVehBroken]);
			cache_get_value_name_int(i, "PVeh_Insuranced", PlayerVehicle[vehicleid][pVehInsuranced]);
			cache_get_value_name_int(i, "PVeh_Faction", PlayerVehicle[vehicleid][pVehFaction]);
			cache_get_value_name_int(i, "PVeh_Donation", PlayerVehicle[vehicleid][vehDonation]);
			cache_get_value_name_int(i, "PVeh_Impounded", PlayerVehicle[vehicleid][pVehImpounded]);
			cache_get_value_name_int(i, "PVeh_ImpoundedTime", PlayerVehicle[vehicleid][pVehImpoundDuration]);
			cache_get_value_name_int(i, "PVeh_ImpoundedPrice", PlayerVehicle[vehicleid][pVehImpoundFee]);
			cache_get_value_name_int(i, "PVeh_DCTime", PlayerVehicle[vehicleid][pVehDCTime]);
			cache_get_value_name(i, "PVeh_ImpoundedReason", tempImpound);
			format(PlayerVehicle[vehicleid][pVehImpoundReason], 256, tempImpound);

			UpdateVehicleDamageStatus(PlayerVehicle[vehicleid][pVehPhysic], PlayerVehicle[vehicleid][pVehDamage][0], PlayerVehicle[vehicleid][pVehDamage][1], PlayerVehicle[vehicleid][pVehDamage][2], PlayerVehicle[vehicleid][pVehDamage][3]);

			new vQuery[300];
			mysql_format(g_SQL, vQuery, sizeof(vQuery), "SELECT * FROM `vehicle_object` WHERE `vehicle` = '%d' ORDER BY `id` ASC LIMIT %d", PlayerVehicle[vehicleid][pVehID], MAX_VEHICLE_OBJECT);
			mysql_tquery(g_SQL, vQuery, "Vehicle_ObjectLoad", "d", vehicleid);

			if(PlayerVehicle[vehicleid][pVehImpounded] || PlayerVehicle[vehicleid][pVehInsuranced] || PlayerVehicle[vehicleid][pVehParked] > -1 || PlayerVehicle[vehicleid][pVehHelipadGarage] > -1 || PlayerVehicle[vehicleid][pVehHouseGarage] > -1 || PlayerVehicle[vehicleid][pVehFamiliesGarage] > -1 || PlayerVehicle[vehicleid][pVehFactStored] > -1)
			{
				PlayerVehicle[vehicleid][pVehPhysic] = INVALID_VEHICLE_ID;
			}
			else //jika kendaraan tidak di impound maka dicek disconnect time
			{	
				OnPlayerVehicleRespawn(vehicleid);
			}
		}
	}
	printf("[Player Vehicle] Memuat player vehicle untuk: %s(%d)", AccountData[playerid][pName], playerid);
	if(cache_is_valid(vehicleCache))
    {
        cache_delete(vehicleCache);
        printf("[Vehicle] Cache ID  berhasil dihapus.");
    }
    else
    {
        printf("[Vehicle] Cache ID tidak valid atau sudah dihapus.");
    }

	return 1;
}

JavaTR:LoadPlayerVehicle(playerid)
{
    new query[128], tempname[64], Cache:execute;
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_vehicles` WHERE `PVeh_OwnerID` = '%d' ORDER BY `id` ASC", AccountData[playerid][pID]);
	execute = mysql_query(g_SQL, query, true);
	new count = cache_num_rows(), tempImpound[256];
	if(count > 0)
	{
		for(new z = 0; z < count; z ++)
		{
			new i = Iter_Free(PvtVehicles);
			
			PlayerVehicle[i][pVehExists] = true;
			cache_get_value_name_int(z, "id", PlayerVehicle[i][pVehID]);
			//PlayerVehicle[i][VehicleOwned] = true;
			cache_get_value_name_int(z, "PVeh_OwnerID", PlayerVehicle[i][pVehOwnerID]);
			cache_get_value_name_int(z, "PVeh_Locked", PlayerVehicle[i][pVehLocked]);
			cache_get_value_name_float(z, "PVeh_PosX", PlayerVehicle[i][pVehPos][0]);
			cache_get_value_name_float(z, "PVeh_PosY", PlayerVehicle[i][pVehPos][1]);
			cache_get_value_name_float(z, "PVeh_PosZ", PlayerVehicle[i][pVehPos][2]);
			cache_get_value_name_float(z, "PVeh_PosA", PlayerVehicle[i][pVehPos][3]);

			cache_get_value_name_float(z, "PVeh_Health", PlayerVehicle[i][pVehHealth]);
			// if(PlayerVehicle[i][pVehHealth] < 0.0 || PlayerVehicle[i][pVehHealth] > 1000.0) PlayerVehicle[i][pVehHealth] = 1000.0;

			cache_get_value_name_float(z, "PVeh_Capacity", PlayerVehicle[i][pVehCapacity]);
			cache_get_value_name_float(z, "PVeh_Weigh", PlayerVehicle[i][pVehWeight]);
			cache_get_value_name_int(z, "PVeh_Fuel", PlayerVehicle[i][pVehFuel]);
			cache_get_value_name_int(z, "PVeh_Interior", PlayerVehicle[i][pVehInterior]);
			cache_get_value_name_int(z, "PVeh_World", PlayerVehicle[i][pVehWorld]);
			cache_get_value_name_int(z, "PVeh_Damage0", PlayerVehicle[i][pVehDamage][0]);
			cache_get_value_name_int(z, "PVeh_Damage1", PlayerVehicle[i][pVehDamage][1]);
			cache_get_value_name_int(z, "PVeh_Damage2", PlayerVehicle[i][pVehDamage][2]);
			cache_get_value_name_int(z, "PVeh_Damage3", PlayerVehicle[i][pVehDamage][3]);
			cache_get_value_name_int(z, "PVeh_Color1", PlayerVehicle[i][pVehColor1]);
			cache_get_value_name_int(z, "PVeh_Color2", PlayerVehicle[i][pVehColor2]);
			cache_get_value_name_int(z, "PVeh_Paintjob", PlayerVehicle[i][pVehPaintjob]);
			cache_get_value_name_int(z, "PVeh_Neon", PlayerVehicle[i][pVehNeon]);
			PlayerVehicle[i][cTogNeon] = 0;
			cache_get_value_name_int(z, "PVeh_Price", PlayerVehicle[i][pVehPrice]);
			cache_get_value_name_int(z, "PVeh_ModelID", PlayerVehicle[i][pVehModelID]);
			cache_get_value_name(z, "PVeh_Plate", tempname);
			format(PlayerVehicle[i][pVehPlate], 256, tempname);
			cache_get_value_name_int(z, "PVeh_PlateTime", PlayerVehicle[i][pVehPlateTime]);
			cache_get_value_name_int(z, "PVeh_PlateOwned", PlayerVehicle[i][pVehPlateOwn]);

			cache_get_value_name_int(z, "PVeh_Mod0", PlayerVehicle[i][pVehMod][0]);
			cache_get_value_name_int(z, "PVeh_Mod1", PlayerVehicle[i][pVehMod][1]);
			cache_get_value_name_int(z, "PVeh_Mod2", PlayerVehicle[i][pVehMod][2]);
			cache_get_value_name_int(z, "PVeh_Mod3", PlayerVehicle[i][pVehMod][3]);
			cache_get_value_name_int(z, "PVeh_Mod4", PlayerVehicle[i][pVehMod][4]);
			cache_get_value_name_int(z, "PVeh_Mod5", PlayerVehicle[i][pVehMod][5]);
			cache_get_value_name_int(z, "PVeh_Mod6", PlayerVehicle[i][pVehMod][6]);
			cache_get_value_name_int(z, "PVeh_Mod7", PlayerVehicle[i][pVehMod][7]);
			cache_get_value_name_int(z, "PVeh_Mod8", PlayerVehicle[i][pVehMod][8]);
			cache_get_value_name_int(z, "PVeh_Mod9", PlayerVehicle[i][pVehMod][9]);
			cache_get_value_name_int(z, "PVeh_Mod10", PlayerVehicle[i][pVehMod][10]);
			cache_get_value_name_int(z, "PVeh_Mod11", PlayerVehicle[i][pVehMod][11]);
			cache_get_value_name_int(z, "PVeh_Mod12", PlayerVehicle[i][pVehMod][12]);
			cache_get_value_name_int(z, "PVeh_Mod13", PlayerVehicle[i][pVehMod][13]);
			cache_get_value_name_int(z, "PVeh_Mod14", PlayerVehicle[i][pVehMod][14]);
			cache_get_value_name_int(z, "PVeh_Mod15", PlayerVehicle[i][pVehMod][15]);
			cache_get_value_name_int(z, "PVeh_Mod16", PlayerVehicle[i][pVehMod][16]);
			
			/* vehicle Upgrade */
			cache_get_value_name_int(z, "PVeh_EngineUpgrade", PlayerVehicle[i][pVehEngineUpgrade]);
			cache_get_value_name_int(z, "PVeh_BodyUpgrade", PlayerVehicle[i][pVehBodyUpgrade]);
			cache_get_value_name_float(z, "PVeh_BodyRepair", PlayerVehicle[i][pVehBodyRepair]);

			cache_get_value_name_int(z, "PVeh_Weapon1", PlayerVehicle[i][pVehWeapon][0]);
			cache_get_value_name_int(z, "PVeh_Weapon2", PlayerVehicle[i][pVehWeapon][1]);
			cache_get_value_name_int(z, "PVeh_Weapon3", PlayerVehicle[i][pVehWeapon][2]);
			cache_get_value_name_int(z, "PVeh_Ammo1", PlayerVehicle[i][pVehAmmo][0]);
			cache_get_value_name_int(z, "PVeh_Ammo2", PlayerVehicle[i][pVehAmmo][1]);
			cache_get_value_name_int(z, "PVeh_Ammo3", PlayerVehicle[i][pVehAmmo][2]);
            
			cache_get_value_name_int(z, "PVeh_Rental", PlayerVehicle[i][pVehRental]);
			cache_get_value_name_int(z, "PVeh_RentTime", PlayerVehicle[i][pVehRentTime]);
			cache_get_value_name_int(z, "PVeh_Parked", PlayerVehicle[i][pVehParked]);
			cache_get_value_name_int(z, "PVeh_Housed", PlayerVehicle[i][pVehHouseGarage]);
			cache_get_value_name_int(z, "PVeh_Helipad", PlayerVehicle[i][pVehHelipadGarage]);
			cache_get_value_name_int(z, "PVeh_Families", PlayerVehicle[i][pVehFamiliesGarage]);
			cache_get_value_name_int(z, "PVeh_FactionGarage", PlayerVehicle[i][pVehFactStored]);
			cache_get_value_name_int(z, "PVeh_Broken", PlayerVehicle[i][pVehBroken]);
			cache_get_value_name_int(z, "PVeh_Insuranced", PlayerVehicle[i][pVehInsuranced]);
			cache_get_value_name_int(z, "PVeh_Faction", PlayerVehicle[i][pVehFaction]);
			cache_get_value_name_int(z, "PVeh_Donation", PlayerVehicle[i][vehDonation]);
			cache_get_value_name_int(z, "PVeh_Impounded", PlayerVehicle[i][pVehImpounded]);
			cache_get_value_name_int(z, "PVeh_ImpoundedTime", PlayerVehicle[i][pVehImpoundDuration]);
			cache_get_value_name_int(z, "PVeh_ImpoundedPrice", PlayerVehicle[i][pVehImpoundFee]);
			cache_get_value_name_int(z, "PVeh_DCTime", PlayerVehicle[i][pVehDCTime]);
			cache_get_value_name(z, "PVeh_ImpoundedReason", tempImpound);
			format(PlayerVehicle[i][pVehImpoundReason], 256, tempImpound);

			UpdateVehicleDamageStatus(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehDamage][0], PlayerVehicle[i][pVehDamage][1], PlayerVehicle[i][pVehDamage][2], PlayerVehicle[i][pVehDamage][3]);
			
			Iter_Add(PvtVehicles, i);

			new vQuery[300];
			mysql_format(g_SQL, vQuery, sizeof(vQuery), "SELECT * FROM `vehicle_object` WHERE `vehicle` = '%d' ORDER BY `id` ASC LIMIT %d", PlayerVehicle[i][pVehID], MAX_VEHICLE_OBJECT);
			mysql_tquery(g_SQL, vQuery, "Vehicle_ObjectLoad", "d", i);

			if(PlayerVehicle[i][pVehImpounded] || PlayerVehicle[i][pVehInsuranced] || PlayerVehicle[i][pVehParked] > -1 || PlayerVehicle[i][pVehHelipadGarage] > -1 || PlayerVehicle[i][pVehHouseGarage] > -1 || PlayerVehicle[i][pVehFamiliesGarage] > -1 || PlayerVehicle[i][pVehFactStored] > -1)
			{
				PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;
			}
			else //jika kendaraan tidak di impound maka dicek disconnect time
			{	
				OnPlayerVehicleRespawn(i);
			}
		}
		printf("[Player Vehicle] Memuat player vehicle untuk: %s(%d)", AccountData[playerid][pName], playerid);
	}
	cache_delete(execute);
	return 1;
}

stock SavePlayerVehicle(i)
{
	Vehicle_GetStatus(i);
	new cQuery[2248];

	mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_vehicles` SET ");
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ModelID`=%d, ", cQuery, PlayerVehicle[i][pVehModelID]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_OwnerID`=%d, ", cQuery, PlayerVehicle[i][pVehOwnerID]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Price`=%d, ", cQuery, PlayerVehicle[i][pVehPrice]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Parked`=%d, ", cQuery, PlayerVehicle[i][pVehParked]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Housed`=%d, ", cQuery, PlayerVehicle[i][pVehHouseGarage]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Helipad`=%d, ", cQuery, PlayerVehicle[i][pVehHelipadGarage]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Families`=%d, ", cQuery, PlayerVehicle[i][pVehFamiliesGarage]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_FactionGarage`=%d, ", cQuery, PlayerVehicle[i][pVehFactStored]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Faction`=%d, ", cQuery, PlayerVehicle[i][pVehFaction]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_RentTime`=%d, ", cQuery, PlayerVehicle[i][pVehRentTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Rental`=%d, ", cQuery, PlayerVehicle[i][pVehRental]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Plate`='%e', ", cQuery, PlayerVehicle[i][pVehPlate]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PlateTime`=%d, ", cQuery, PlayerVehicle[i][pVehPlateTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PlateOwned`=%d, ", cQuery, PlayerVehicle[i][pVehPlateOwn]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Health`='%f', ", cQuery, PlayerVehicle[i][pVehHealth]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Fuel`=%d, ", cQuery, PlayerVehicle[i][pVehFuel]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Locked`=%d, ", cQuery, PlayerVehicle[i][pVehLocked]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod0`=%d, ", cQuery, PlayerVehicle[i][pVehMod][0]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod1`=%d, ", cQuery, PlayerVehicle[i][pVehMod][1]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod2`=%d, ", cQuery, PlayerVehicle[i][pVehMod][2]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod3`=%d, ", cQuery, PlayerVehicle[i][pVehMod][3]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod4`=%d, ", cQuery, PlayerVehicle[i][pVehMod][4]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod5`=%d, ", cQuery, PlayerVehicle[i][pVehMod][5]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod6`=%d, ", cQuery, PlayerVehicle[i][pVehMod][6]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod7`=%d, ", cQuery, PlayerVehicle[i][pVehMod][7]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod8`=%d, ", cQuery, PlayerVehicle[i][pVehMod][8]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod9`=%d, ", cQuery, PlayerVehicle[i][pVehMod][9]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod10`=%d, ", cQuery, PlayerVehicle[i][pVehMod][10]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod11`=%d, ", cQuery, PlayerVehicle[i][pVehMod][11]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod12`=%d, ", cQuery, PlayerVehicle[i][pVehMod][12]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod13`=%d, ", cQuery, PlayerVehicle[i][pVehMod][13]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod14`=%d, ", cQuery, PlayerVehicle[i][pVehMod][14]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod15`=%d, ", cQuery, PlayerVehicle[i][pVehMod][15]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Mod16`=%d, ", cQuery, PlayerVehicle[i][pVehMod][16]);

	/* Vehicle Upgrade */
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_EngineUpgrade`=%d, ", cQuery, PlayerVehicle[i][pVehEngineUpgrade]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_BodyUpgrade`=%d, ", cQuery, PlayerVehicle[i][pVehBodyUpgrade]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_BodyRepair`=%.3f, ", cQuery, PlayerVehicle[i][pVehBodyRepair]);

	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Weapon1`=%d, ", cQuery, PlayerVehicle[i][pVehWeapon][0]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Weapon2`=%d, ", cQuery, PlayerVehicle[i][pVehWeapon][1]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Weapon3`=%d, ", cQuery, PlayerVehicle[i][pVehWeapon][2]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Ammo1`=%d, ", cQuery, PlayerVehicle[i][pVehAmmo][0]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Ammo2`=%d, ", cQuery, PlayerVehicle[i][pVehAmmo][1]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Ammo3`=%d, ", cQuery, PlayerVehicle[i][pVehAmmo][2]);
    
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage0`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][0]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage1`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][1]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage2`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][2]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage3`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][3]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosX`='%f', ", cQuery, PlayerVehicle[i][pVehPos][0]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosY`='%f', ", cQuery, PlayerVehicle[i][pVehPos][1]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosZ`='%f', ", cQuery, PlayerVehicle[i][pVehPos][2]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosA`='%f', ", cQuery, PlayerVehicle[i][pVehPos][3]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Neon`=%d, ", cQuery, PlayerVehicle[i][pVehNeon]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Paintjob`=%d, ", cQuery, PlayerVehicle[i][pVehPaintjob]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Color1`=%d, ", cQuery, PlayerVehicle[i][pVehColor1]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Color2`=%d, ", cQuery, PlayerVehicle[i][pVehColor2]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_World`=%d, ", cQuery, PlayerVehicle[i][pVehWorld]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Interior`=%d, ", cQuery, PlayerVehicle[i][pVehInterior]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Impounded`=%d, ", cQuery, PlayerVehicle[i][pVehImpounded]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ImpoundedTime`=%d, ", cQuery, PlayerVehicle[i][pVehImpoundDuration]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ImpoundedPrice`=%d, ", cQuery, PlayerVehicle[i][pVehImpoundFee]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ImpoundedReason`='%s', ", cQuery, PlayerVehicle[i][pVehImpoundReason]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Insuranced`=%d, ", cQuery, PlayerVehicle[i][pVehInsuranced]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Donation`=%d, ", cQuery, PlayerVehicle[i][vehDonation]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_DCTime`=%d, ", cQuery, gettime() + 3600);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Capacity`=%f ", cQuery, PlayerVehicle[i][pVehCapacity]);
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s, `PVeh_Weigh`=%f", cQuery, PlayerVehicle[i][pVehWeight]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sWHERE `id` = '%d'", cQuery, PlayerVehicle[i][pVehID]);
    mysql_query(g_SQL, cQuery, true);
	return 1;
}

// RemovePlayerVehicle(playerid)
// {
// 	foreach(new i : PvtVehicles)
// 	{
// 		if (PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
// 		{
// 			Vehicle_GetStatus(i);
// 			new cQuery[2248];

// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_vehicles` SET ");
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosX`='%f', ", cQuery, PlayerVehicle[i][pVehPos][0]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosY`='%f', ", cQuery, PlayerVehicle[i][pVehPos][1]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosZ`='%f', ", cQuery, PlayerVehicle[i][pVehPos][2]+0.1);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosA`='%f', ", cQuery, PlayerVehicle[i][pVehPos][3]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Health`='%f', ", cQuery, PlayerVehicle[i][pVehHealth]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Fuel`=%d, ", cQuery, PlayerVehicle[i][pVehFuel]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Interior`=%d, ", cQuery, PlayerVehicle[i][pVehInterior]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Price`=%d, ", cQuery, PlayerVehicle[i][pVehPrice]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_World`=%d, ", cQuery, PlayerVehicle[i][pVehWorld]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage0`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][0]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage1`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][1]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage2`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][2]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage3`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][3]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ModelID`=%d, ", cQuery, PlayerVehicle[i][pVehModelID]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Locked`=%d, ", cQuery, PlayerVehicle[i][pVehLocked]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Plate`='%e', ", cQuery, PlayerVehicle[i][pVehPlate]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PlateTime`='%d', ", cQuery, PlayerVehicle[i][pVehPlateTime]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PlateOwned`='%d', ", cQuery, PlayerVehicle[i][pVehPlateOwn]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Color1`='%d', ", cQuery, PlayerVehicle[i][pVehColor1]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Color2`='%d', ", cQuery, PlayerVehicle[i][pVehColor2]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Paintjob`='%d', ", cQuery, PlayerVehicle[i][pVehPaintjob]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Neon`='%d', ", cQuery, PlayerVehicle[i][pVehNeon]);
// 			new tempString[56];
// 			for(new z = 0; z < 17; z++)
// 			{
// 				format(tempString, sizeof(tempString), "PVeh_Mod%d", z);
// 				mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`%s`='%d', ", cQuery, tempString, PlayerVehicle[i][pVehMod][z]);
// 			}

// 			/* Vehicle Upgrade */
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_EngineUpgrade`='%d', ", cQuery, PlayerVehicle[i][pVehEngineUpgrade]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_BodyUpgrade`='%d', ", cQuery, PlayerVehicle[i][pVehBodyUpgrade]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_BodyRepair`='%.3f', ", cQuery, PlayerVehicle[i][pVehBodyRepair]);

// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Weapon1`='%d', ", cQuery, PlayerVehicle[i][pVehWeapon][0]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Weapon2`='%d', ", cQuery, PlayerVehicle[i][pVehWeapon][1]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Weapon3`='%d', ", cQuery, PlayerVehicle[i][pVehWeapon][2]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Ammo1`='%d', ", cQuery, PlayerVehicle[i][pVehAmmo][0]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Ammo2`='%d', ", cQuery, PlayerVehicle[i][pVehAmmo][1]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Ammo3`='%d', ", cQuery, PlayerVehicle[i][pVehAmmo][2]);

// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Rental`='%d', ", cQuery, PlayerVehicle[i][pVehRental]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_RentTime`='%d', ", cQuery, PlayerVehicle[i][pVehRentTime]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Parked`='%d', ", cQuery, PlayerVehicle[i][pVehParked]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Broken`='%d', ", cQuery, PlayerVehicle[i][pVehBroken]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Housed`='%d', ", cQuery, PlayerVehicle[i][pVehHouseGarage]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Helipad`='%d', ", cQuery, PlayerVehicle[i][pVehHelipadGarage]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Families`='%d', ", cQuery, PlayerVehicle[i][pVehFamiliesGarage]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_FactionGarage`='%d', ", cQuery, PlayerVehicle[i][pVehFactStored]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Insuranced`='%d', ", cQuery, PlayerVehicle[i][pVehInsuranced]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Faction`='%d', ", cQuery, PlayerVehicle[i][pVehFaction]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Donation`='%d', ", cQuery, PlayerVehicle[i][vehDonation]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_DCTime`='%d', ", cQuery, gettime() + 3600);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Capacity`=%f, ", cQuery, PlayerVehicle[i][pVehCapacity]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Impounded`='%d', ", cQuery, PlayerVehicle[i][pVehImpounded]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ImpoundedTime`='%d',", cQuery, PlayerVehicle[i][pVehImpoundDuration]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ImpoundedPrice`='%d',", cQuery, PlayerVehicle[i][pVehImpoundFee]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ImpoundedReason`='%s' ", cQuery, PlayerVehicle[i][pVehImpoundReason]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sWHERE `id` = '%d'", cQuery, PlayerVehicle[i][pVehID]);
// 			mysql_query(g_SQL, cQuery, true);

// 			if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
// 			{
// 				SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], false, PlayerVehicle[i][pVehNeon], 0);

// 				for(new x; x < 23; x ++)
// 				{
// 					if(DestroyDynamicObject(FactionVehObject[PlayerVehicle[i][pVehPhysic]][x]))
// 						FactionVehObject[PlayerVehicle[i][pVehPhysic]][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
// 				}

// 				for(new x; x < 16; x ++ )
// 				{
// 					if(DestroyDynamicObject(DonationVehObject[PlayerVehicle[i][pVehPhysic]][x]))
// 						DonationVehObject[PlayerVehicle[i][pVehPhysic]][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
// 				}

// 				DisableVehicleSpeedCap(PlayerVehicle[i][pVehPhysic]);
// 				DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
// 				PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;
// 			}

// 			/*if(PlayerVehicle[i][pVehRental] != -1 || PlayerVehicle[i][pVehRentTime] > 0)
// 			{
// 				PlayerVehicle[i][pVehRental] = -1;
// 				PlayerVehicle[i][pVehRentTime] = 0;

// 				mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `id` = %d", PlayerVehicle[i][pVehID]);
// 				mysql_tquery(g_SQL, strgbg);
// 			}*/
// 			PlayerVehicle[i][pVehOwnerID] = -1;
// 			PlayerVehicle[i][pVehExists] = false;
// 			Iter_Remove(PvtVehicles, i);	
// 			Vehicle_ResetVariable(i);
// 		}
// 	}
// 	return 1;
// }

UnloadPlayerVehicle(playerid)
{
	foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists])
	{
		if(PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
		{
			SavePlayerVehicle(i);

			if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
			{
				SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], false, PlayerVehicle[i][pVehNeon], 0);

				for(new x; x < 23; x ++)
				{
					if(DestroyDynamicObject(FactionVehObject[PlayerVehicle[i][pVehPhysic]][x]))
						FactionVehObject[PlayerVehicle[i][pVehPhysic]][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
				}

				for(new x; x < 16; x ++ )
				{
					if(DestroyDynamicObject(DonationVehObject[PlayerVehicle[i][pVehPhysic]][x]))
						DonationVehObject[PlayerVehicle[i][pVehPhysic]][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
				}

				for(new slot = 0; slot < MAX_VEHICLE_OBJECT; slot ++) if (VehicleObjects[i][slot][vehObjectExists])
				{
					if(IsValidDynamicObject(VehicleObjects[i][slot][vehObject]))
						DestroyDynamicObject(VehicleObjects[i][slot][vehObject]),  VehicleObjects[i][slot][vehObject] = INVALID_STREAMER_ID;

					VehicleObjects[i][slot][vehObjectModel] = 0;

					VehicleObjects[i][slot][vehObjectPosX] = VehicleObjects[i][slot][vehObjectPosY] = VehicleObjects[i][slot][vehObjectPosZ] = 0.0;
					VehicleObjects[i][slot][vehObjectPosRX] = VehicleObjects[i][slot][vehObjectPosRY] = VehicleObjects[i][slot][vehObjectPosRZ] = 0.0;

					VehicleObjects[i][slot][vehObjectID] = 0;
					VehicleObjects[i][slot][vehObjectVehicleIndex] = 0;
					VehicleObjects[i][slot][vehObjectExists] = false;
				}

				DisableVehicleSpeedCap(PlayerVehicle[i][pVehPhysic]);
				DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
				PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;
			}

			PlayerVehicle[i][pVehExists] = false;
			Iter_Remove(PvtVehicles, i);
		}
	}
	return 1;
}

/*UnloadPlayerVehicle(playerid)
{
	foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists])
	{
		if(PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
		{
			SavePlayerVehicle(i);

			if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
			{
				SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], false, PlayerVehicle[i][pVehNeon], 0);

				for(new x; x < 23; x ++)
				{
					if(DestroyDynamicObject(FactionVehObject[PlayerVehicle[i][pVehPhysic]][x]))
						FactionVehObject[PlayerVehicle[i][pVehPhysic]][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
				}

				for(new x; x < 16; x ++ )
				{
					if(DestroyDynamicObject(DonationVehObject[PlayerVehicle[i][pVehPhysic]][x]))
						DonationVehObject[PlayerVehicle[i][pVehPhysic]][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
				}

				for(new slot = 0; slot < MAX_VEHICLE_OBJECT; slot ++) if (VehicleObjects[i][slot][vehObjectExists])
				{
					if(IsValidDynamicObject(VehicleObjects[i][slot][vehObject]))
						DestroyDynamicObject(VehicleObjects[i][slot][vehObject]),  VehicleObjects[i][slot][vehObject] = INVALID_STREAMER_ID;

					VehicleObjects[i][slot][vehObjectModel] = 0;

					VehicleObjects[i][slot][vehObjectPosX] = VehicleObjects[i][slot][vehObjectPosY] = VehicleObjects[i][slot][vehObjectPosZ] = 0.0;
					VehicleObjects[i][slot][vehObjectPosRX] = VehicleObjects[i][slot][vehObjectPosRY] = VehicleObjects[i][slot][vehObjectPosRZ] = 0.0;

					VehicleObjects[i][slot][vehObjectID] = 0;
					VehicleObjects[i][slot][vehObjectVehicleIndex] = 0;
					VehicleObjects[i][slot][vehObjectExists] = false;
				}

				DisableVehicleSpeedCap(PlayerVehicle[i][pVehPhysic]);
				DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
				PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;
			}

			PlayerVehicle[i][pVehExists] = false;
			Iter_Remove(PvtVehicles, i);
		}
	}
	return 1;
}*/

// RemovePlayerVehicle(playerid)
// {
// 	foreach(new i : PvtVehicles) if(PlayerVehicle[i][pVehExists])
// 	{
// 		if(PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
// 		{
// 			Vehicle_GetStatus(i);
// 			new cQuery[2248];
//             PlayerVehicle[i][pVehOwnerID] = -1;
// 			PlayerVehicle[i][pVehExists] = false;
			
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_vehicles` SET ");
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosX`='%f', ", cQuery, PlayerVehicle[i][pVehPos][0]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosY`='%f', ", cQuery, PlayerVehicle[i][pVehPos][1]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosZ`='%f', ", cQuery, PlayerVehicle[i][pVehPos][2]+0.1);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PosA`='%f', ", cQuery, PlayerVehicle[i][pVehPos][3]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Health`='%f', ", cQuery, PlayerVehicle[i][pVehHealth]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Fuel`=%d, ", cQuery, PlayerVehicle[i][pVehFuel]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Interior`=%d, ", cQuery, PlayerVehicle[i][pVehInterior]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Price`=%d, ", cQuery, PlayerVehicle[i][pVehPrice]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_World`=%d, ", cQuery, PlayerVehicle[i][pVehWorld]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage0`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][0]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage1`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][1]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage2`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][2]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Damage3`=%d, ", cQuery, PlayerVehicle[i][pVehDamage][3]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ModelID`=%d, ", cQuery, PlayerVehicle[i][pVehModelID]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Locked`=%d, ", cQuery, PlayerVehicle[i][pVehLocked]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Plate`='%e', ", cQuery, PlayerVehicle[i][pVehPlate]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PlateTime`='%d', ", cQuery, PlayerVehicle[i][pVehPlateTime]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_PlateOwned`='%d', ", cQuery, PlayerVehicle[i][pVehPlateOwn]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Color1`='%d', ", cQuery, PlayerVehicle[i][pVehColor1]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Color2`='%d', ", cQuery, PlayerVehicle[i][pVehColor2]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Paintjob`='%d', ", cQuery, PlayerVehicle[i][pVehPaintjob]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Neon`='%d', ", cQuery, PlayerVehicle[i][pVehNeon]);
// 			new tempString[56];
// 			for(new z = 0; z < 17; z++)
// 			{
// 				format(tempString, sizeof(tempString), "PVeh_Mod%d", z);
// 				mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`%s`='%d', ", cQuery, tempString, PlayerVehicle[i][pVehMod][z]);
// 			}

// 			/* Vehicle Upgrade */
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_EngineUpgrade`='%d', ", cQuery, PlayerVehicle[i][pVehEngineUpgrade]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_BodyUpgrade`='%d', ", cQuery, PlayerVehicle[i][pVehBodyUpgrade]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_BodyRepair`='%.3f', ", cQuery, PlayerVehicle[i][pVehBodyRepair]);

// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Weapon1`='%d', ", cQuery, PlayerVehicle[i][pVehWeapon][0]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Weapon2`='%d', ", cQuery, PlayerVehicle[i][pVehWeapon][1]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Weapon3`='%d', ", cQuery, PlayerVehicle[i][pVehWeapon][2]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Ammo1`='%d', ", cQuery, PlayerVehicle[i][pVehAmmo][0]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Ammo2`='%d', ", cQuery, PlayerVehicle[i][pVehAmmo][1]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Ammo3`='%d', ", cQuery, PlayerVehicle[i][pVehAmmo][2]);

// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Rental`='%d', ", cQuery, PlayerVehicle[i][pVehRental]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_RentTime`='%d', ", cQuery, PlayerVehicle[i][pVehRentTime]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Parked`='%d', ", cQuery, PlayerVehicle[i][pVehParked]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Broken`='%d', ", cQuery, PlayerVehicle[i][pVehBroken]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Housed`='%d', ", cQuery, PlayerVehicle[i][pVehHouseGarage]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Helipad`='%d', ", cQuery, PlayerVehicle[i][pVehHelipadGarage]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Families`='%d', ", cQuery, PlayerVehicle[i][pVehFamiliesGarage]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_FactionGarage`='%d', ", cQuery, PlayerVehicle[i][pVehFactStored]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Insuranced`='%d', ", cQuery, PlayerVehicle[i][pVehInsuranced]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Faction`='%d', ", cQuery, PlayerVehicle[i][pVehFaction]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Donation`='%d', ", cQuery, PlayerVehicle[i][vehDonation]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_DCTime`='%d', ", cQuery, gettime() + 3600);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Capacity`=%f, ", cQuery, PlayerVehicle[i][pVehCapacity]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_Impounded`='%d', ", cQuery, PlayerVehicle[i][pVehImpounded]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ImpoundedTime`='%d',", cQuery, PlayerVehicle[i][pVehImpoundDuration]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ImpoundedPrice`='%d',", cQuery, PlayerVehicle[i][pVehImpoundFee]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PVeh_ImpoundedReason`='%s' ", cQuery, PlayerVehicle[i][pVehImpoundReason]);
// 			mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sWHERE `id` = '%d'", cQuery, PlayerVehicle[i][pVehID]);
// 			mysql_query(g_SQL, cQuery, true);

// 			if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
// 			{
// 				SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], false, PlayerVehicle[i][pVehNeon], 0);

// 				for(new x; x < 23; x ++)
// 				{
// 					if(DestroyDynamicObject(FactionVehObject[PlayerVehicle[i][pVehPhysic]][x]))
// 						FactionVehObject[PlayerVehicle[i][pVehPhysic]][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
// 				}

// 				for(new x; x < 16; x ++ )
// 				{
// 					if(DestroyDynamicObject(DonationVehObject[PlayerVehicle[i][pVehPhysic]][x]))
// 						DonationVehObject[PlayerVehicle[i][pVehPhysic]][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
// 				}

// 				DisableVehicleSpeedCap(PlayerVehicle[i][pVehPhysic]);
// 				DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
// 				PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;
// 			}

// 			/*if(PlayerVehicle[i][pVehRental] != -1 || PlayerVehicle[i][pVehRentTime] > 0)
// 			{
// 				PlayerVehicle[i][pVehRental] = -1;
// 				PlayerVehicle[i][pVehRentTime] = 0;

// 				mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `id` = %d", PlayerVehicle[i][pVehID]);
// 				mysql_tquery(g_SQL, strgbg);
// 			}*/
// 			Vehicle_ResetVariable(i);
// 			Iter_Remove(PvtVehicles, i);
// 		}
// 	}
// 	return 1;
// }

Vehicle_ResetVariable(vehicleid)
{
	new tmp_VehicleData[pvehdata];
	PlayerVehicle[vehicleid] = tmp_VehicleData;

	PlayerVehicle[vehicleid][pVehPhysic] = INVALID_VEHICLE_ID;
	return 1;
}

Vehicle_GetIterID(vehicleid)
{
	foreach(new i : PvtVehicles) if(PlayerVehicle[i][pVehPhysic] == vehicleid) 
	{
		return i;
	}
	return -1;
}

RespawnVehicle(vehicleid)
{
	if(IsValidVehicle(vehicleid))
	{
		new id = Vehicle_GetIterID(vehicleid), strgbg[255];

		if(id != -1)
		{
			Vehicle_GetStatus(id);

			if(IsValidVehicle(PlayerVehicle[id][pVehPhysic]))
			{
				for(new x; x < 23; x ++) 
				{
					if(DestroyDynamicObject(FactionVehObject[PlayerVehicle[id][pVehPhysic]][x]))
						FactionVehObject[PlayerVehicle[id][pVehPhysic]][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
				}

				DisableVehicleSpeedCap(PlayerVehicle[id][pVehPhysic]);
				SetVehicleNeonLights(PlayerVehicle[id][pVehPhysic], false, PlayerVehicle[id][pVehNeon], 0);

				DestroyVehicle(PlayerVehicle[id][pVehPhysic]);
				PlayerVehicle[id][pVehPhysic] = INVALID_VEHICLE_ID;
			}

			if(PlayerVehicle[id][pVehRental] != -1 || PlayerVehicle[id][pVehRentTime] > 0)
			{
				PlayerVehicle[id][pVehRental] = -1;
				PlayerVehicle[id][pVehRentTime] = 0;
				PlayerVehicle[id][pVehExists] = false;

				mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `id` = %d", PlayerVehicle[id][pVehID]);
				mysql_tquery(g_SQL, strgbg);

				Iter_Remove(PvtVehicles, id);
			}
			else 
			{
				OnPlayerVehicleRespawn(id);
			}
		}
		else 
		{
			SetVehicleToRespawn(vehicleid);
			SetValidVehicleHealth(vehicleid, 1000.0);
			VehicleCore[vehicleid][vCoreFuel] = MAX_FUEL_FULL;
		}
	}
	return 1;
}

GetDistanceToCar(playerid, veh, Float: posX = 0.0, Float: posY = 0.0, Float: posZ = 0.0) 
{
	new
	Float: Floats[2][3];

	if(posX == 0.0 && posY == 0.0 && posZ == 0.0) {
		if(!IsPlayerInAnyVehicle(playerid)) GetPlayerPos(playerid, Floats[0][0], Floats[0][1], Floats[0][2]);
		else GetVehiclePos(GetPlayerVehicleID(playerid), Floats[0][0], Floats[0][1], Floats[0][2]);
	}
	else 
	{
		Floats[0][0] = posX;
		Floats[0][1] = posY;
		Floats[0][2] = posZ;
	}
	GetVehiclePos(veh, Floats[1][0], Floats[1][1], Floats[1][2]);
	return floatround(floatsqroot((Floats[1][0] - Floats[0][0]) * (Floats[1][0] - Floats[0][0]) + (Floats[1][1] - Floats[0][1]) * (Floats[1][1] - Floats[0][1]) + (Floats[1][2] - Floats[0][2]) * (Floats[1][2] - Floats[0][2])));
}

GetClosestCar(playerid, exception = INVALID_VEHICLE_ID) 
{

	new
	Float: Distance,
	target = -1,
	Float: vPos[3];

	if(!IsPlayerInAnyVehicle(playerid)) GetPlayerPos(playerid, vPos[0], vPos[1], vPos[2]);
	else GetVehiclePos(GetPlayerVehicleID(playerid), vPos[0], vPos[1], vPos[2]);

	for(new v; v < MAX_VEHICLES; v++) if(GetVehicleModel(v) >= 400) 
	{
		if(v != exception && (target < 0 || Distance > GetDistanceToCar(playerid, v, vPos[0], vPos[1], vPos[2]))) 
		{
			target = v;
            Distance = GetDistanceToCar(playerid, v, vPos[0], vPos[1], vPos[2]); // Before the rewrite, we'd be running GetPlayerPos 2000 times...
        }
    }
    return target;
}

GetOwnedVeh(playerid)
{
	new tmpcount;
	foreach(new vid : PvtVehicles)
	{
	    if(PlayerVehicle[vid][pVehOwnerID] == AccountData[playerid][pID])
	    {
     		tmpcount++;
		}
	}
	return tmpcount;
}

GetPlayerVehicleLimit(playerid)
{
	return (MAX_PLAYER_VEHICLE + AccountData[playerid][pVip] + AccountData[playerid][pExtraVehSlot]);
}

ReturnPlayerVehID(playerid, hslot)
{
	new tmpcount;
	if(hslot < 1 && hslot > MAX_PLAYER_VEHICLE) return -1;
	foreach(new vid : PvtVehicles) if(PlayerVehicle[vid][pVehExists])
	{
	    if(PlayerVehicle[vid][pVehOwnerID] == AccountData[playerid][pID])
	    {
     		tmpcount++;
       		if(tmpcount == hslot)
       		{
        		return vid;
  			}
	    }
	}
	return -1;
}

/*task HeartTenMinute[600000]()
{
	foreach(new playerid : Player) {
		if(AccountData[playerid][pSpawned]) {
			UpdatePlayerData(playerid);
		}
	}
	foreach(new pv : PvtVehicles) {
		SavePlayerVehicle(pv);
	}
	return 1;
}*/