//Weapon Attach
enum weaponSettings
{
    Float:Position[6],
    Bone,
    Hidden
}
new WeaponSettings[MAX_PLAYERS][17][weaponSettings], WeaponTick[MAX_PLAYERS], EditingWeapon[MAX_PLAYERS];
 
GetWeaponObjectSlot(weaponid)
{
    new objectslot;
 
    switch (weaponid)
    {
        case 22..24: objectslot = 4;	// Handguns
        case 25..27: objectslot = 5;	// Shotguns
        case 28, 29, 32: objectslot = 6;	//Sub-Machineguns
        case 30, 31: objectslot = 7;	//Machineguns
        case 33, 34: objectslot = 8;	//Rifles
        //case 35..38: objectslot = 9; //Heavy Weapons
    }
    return objectslot;
}
 
GetWeaponModel(weaponid) //Will only return the model of wearable weapons (22-38)
{
    new model;
   
    switch(weaponid)
    {
        case 22..29: model = 324 + weaponid;
        case 30: model = 355;
        case 31: model = 356;
        case 32: model = 372;
        case 33..38: model = 324 + weaponid;
    }
    return model;
}
 
PlayerHasWeapon(playerid, weaponid)
{
    new weapon, ammo;
 
    for (new i; i < 13; i++)
    {
        GetPlayerWeaponData(playerid, i, weapon, ammo);
        if (weapon == weaponid && ammo) return 1;
    }
    return 0;
}
 
IsWeaponWearable(weaponid)
    return (weaponid >= 22 && weaponid <= 38);
 
IsWeaponHideable(weaponid)
    return (weaponid >= 22 && weaponid <= 24 || weaponid == 28 || weaponid == 32);
	
//Drop Weapon
#define MAX_DROP_WEAPON 5000
enum droppedweapons {
    WeapID,
    WeapPlayer[24],
	WeapModel,
	WeaponID,
	WeapAmmo,
    Float:WeapPos[3],
	WeapInt,
	WeapWorld,
    WeapObject
};
new DropWeap[MAX_DROP_WEAPON][droppedweapons];

DropWeapon(player[], model, weaponid = 0, ammo = 0, Float:x, Float:y, Float:z, interior, world)
{
    for (new i = 0; i != MAX_DROP_WEAPON; i ++) if(!DropWeap[i][WeapModel])
    {
        format(DropWeap[i][WeapPlayer], 24, player);

        DropWeap[i][WeapModel] = model;
        DropWeap[i][WeaponID] = weaponid;
        DropWeap[i][WeapAmmo] = ammo;
        DropWeap[i][WeapPos][0] = x;
        DropWeap[i][WeapPos][1] = y;
        DropWeap[i][WeapPos][2] = z;

        DropWeap[i][WeapInt] = interior;
        DropWeap[i][WeapWorld] = world;

        if(IsWeaponModel(model)) 
		{
            DropWeap[i][WeapObject] = CreateDynamicObject(model, x, y, z, 93.7, 120.0, 120.0, world, interior);
        } 
		else 
		{
            DropWeap[i][WeapObject] = CreateDynamicObject(model, x, y, z, 0.0, 0.0, 0.0, world, interior);
        }
        return i;
    }
    return -1;
}

NearWeapon(playerid)
{
    for (new i = 0; i != MAX_DROP_WEAPON; i ++) if(DropWeap[i][WeapModel] && IsPlayerInRangeOfPoint(playerid, 1.5, DropWeap[i][WeapPos][0], DropWeap[i][WeapPos][1], DropWeap[i][WeapPos][2]))
    {
        if(GetPlayerInterior(playerid) == DropWeap[i][WeapInt] && GetPlayerVirtualWorld(playerid) == DropWeap[i][WeapWorld])
        return i;
    }
    return -1;
}

DeleteWeapon(itemid)
{
    if(itemid != -1 && DropWeap[itemid][WeapModel])
    {
        DropWeap[itemid][WeapModel] = 0;
        DropWeap[itemid][WeapPos][0] = 0.0;
        DropWeap[itemid][WeapPos][1] = 0.0;
        DropWeap[itemid][WeapPos][2] = 0.0;
        DropWeap[itemid][WeapInt] = 0;
        DropWeap[itemid][WeapWorld] = 0;

        DestroyDynamicObject(DropWeap[itemid][WeapObject]);
    }
    return 1;
}

PickupWeapon(playerid, itemid)
{
    if(itemid != -1 && DropWeap[itemid][WeapModel])
    {
        GivePlayerWeaponEx(playerid, DropWeap[itemid][WeaponID], DropWeap[itemid][WeapAmmo]);
		SendClientMessageEx(playerid, -1, ""YELLOW"[!]"WHITE" Anda telah mengambil senjata %s", ReturnWeaponName(DropWeap[itemid][WeaponID]));
        DeleteWeapon(itemid);
    }
    return 1;
}
	
//Weapon Attach System
forward OnWeaponsLoaded(playerid);
public OnWeaponsLoaded(playerid)
{
    new rows, weaponid, index;
    cache_get_row_count(rows);

	new Cache:weaponCache;

	weaponCache = cache_save();

    for (new i = 0; i < rows; i++)
    {
        cache_get_value_name_int(i, "WeaponID", weaponid);
        index = weaponid - 22;

        cache_get_value_name_float(i, "PosX", WeaponSettings[playerid][index][Position][0]);
        cache_get_value_name_float(i, "PosY", WeaponSettings[playerid][index][Position][1]);
        cache_get_value_name_float(i, "PosZ", WeaponSettings[playerid][index][Position][2]);

        cache_get_value_name_float(i, "RotX", WeaponSettings[playerid][index][Position][3]);
        cache_get_value_name_float(i, "RotY", WeaponSettings[playerid][index][Position][4]);
        cache_get_value_name_float(i, "RotZ", WeaponSettings[playerid][index][Position][5]);

        cache_get_value_name_int(i, "Bone", WeaponSettings[playerid][index][Bone]);
        cache_get_value_name_int(i, "Hidden", WeaponSettings[playerid][index][Hidden]);
    }
    if(cache_is_valid(weaponCache))
    {
        cache_delete(weaponCache);
        printf("[Weapons] Cache ID berhasil dihapus untuk playerid");
    }
    else
    {
        printf("[Weapons] Cache ID tidak valid atau sudah dihapus.");
    }
}

//Weapon Attach System
alias:weapon("gun")
CMD:weapon(playerid, params[])
{
	new weaponid = GetPlayerWeaponEx(playerid);
	new ammo = GetPlayerAmmoEx(playerid);
	
	new name[20], give[128];
	if(sscanf(params, "s[20]S()[128]", name, give))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gun [name]~n~ give, drop, pickup, pos, bone, hide");

	if(!strcmp(name, "pos", true))
	{
		if (!weaponid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memegang senjata!");
		if(!IsWeaponWearable(weaponid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Senjata ini tidak bisa di edit!");
		if(EditingWeapon[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang dalam pengeditan!");
		if(IsPlayerInEvent(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang berada di dalam event!");

		new index = weaponid - 22;
		SetPlayerArmedWeapon(playerid, 0);
		SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModel(weaponid), WeaponSettings[playerid][index][Bone], WeaponSettings[playerid][index][Position][0], WeaponSettings[playerid][index][Position][1], WeaponSettings[playerid][index][Position][2], WeaponSettings[playerid][index][Position][3], WeaponSettings[playerid][index][Position][4], WeaponSettings[playerid][index][Position][5], 1.0, 1.0, 1.0);
		EditAttachedObject(playerid, GetWeaponObjectSlot(weaponid));
	   
		EditingWeapon[playerid] = weaponid;
	}
	else if (!strcmp(name, "bone", true))
	{
		if (!weaponid)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak memegang senjata!");

		if (!IsWeaponWearable(weaponid))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Senjata ini tidak bisa diedit");
			
		if (EditingWeapon[playerid])
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu sedang dalam pengeditan!");

		if(IsPlayerInEvent(playerid)) 
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang berada di dalam event!");

		ShowPlayerDialog(playerid, DIALOG_EDITBONE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Tulang", "Spine\nHead\nLeft upper arm\nRight upper arm\nLeft hand\nRight hand\nLeft thigh\nRight thigh\nLeft foot\nRight foot\nRight calf\nLeft calf\nLeft forearm\nRight forearm\nLeft shoulder\nRight shoulder\nNeck\nJaw", "Choose", "Cancel");
		EditingWeapon[playerid] = weaponid;
	}
	else if (!strcmp(name, "hide", true))
	{
		if (!weaponid)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak memegang senjata!");

		if (!IsWeaponWearable(weaponid))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Senjata ini tidak bisa diedit");
			
		if (EditingWeapon[playerid])
			return ShowTDN(playerid, NOTIFICATION_ERROR, "You cannot hide a weapon while you are editing it.");

		if (!IsWeaponHideable(weaponid))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "This weapon cannot be hidden.");

		if(IsPlayerInEvent(playerid)) 
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang berada di dalam event!");

		new index = weaponid - 22, weaponname[18], string[150];

		GetWeaponName(weaponid, weaponname, sizeof(weaponname));
	   
		if (WeaponSettings[playerid][index][Hidden])
		{
			format(string, sizeof(string), "You have set your %s to show.", weaponname);
			WeaponSettings[playerid][index][Hidden] = false;
		}
		else
		{
			if (IsPlayerAttachedObjectSlotUsed(playerid, GetWeaponObjectSlot(weaponid)))
				RemovePlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid));

			format(string, sizeof(string), "You have set your %s not to show.", weaponname);
			WeaponSettings[playerid][index][Hidden] = true;
		}
		SendClientMessage(playerid, -1, string);
	   
		mysql_format(g_SQL, string, sizeof(string), "INSERT INTO weaponsettings (Owner, WeaponID, Hidden) VALUES ('%d', %d, %d) ON DUPLICATE KEY UPDATE Hidden = VALUES(Hidden)", AccountData[playerid][pID], weaponid, WeaponSettings[playerid][index][Hidden]);
		mysql_tquery(g_SQL, string);
	}
	else if(!strcmp(name, "give", true))
	{

		if (!weaponid || ammo <= 0)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak memegang senjata atau tidak ada peluru!");

		if (IsPlayerInEvent(playerid)) 
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang berada di dalam event!");

		new otherid, amount;
		if (sscanf(give, "ud", otherid, amount)) {
			ShowTDN(playerid, NOTIFICATION_SYNTAX, "/weapon give [playerid] [ammo]");
			return 1;
		}

		if (otherid == INVALID_PLAYER_ID || otherid == playerid || !NearPlayer(playerid, otherid, 5.0))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "You must be near the target player.");

		if (amount <= 0 || amount > ammo)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah peluru tidak valid!");

		ResetWeapon(playerid, weaponid);
		GivePlayerWeaponEx(playerid, weaponid, ammo - amount);

		GivePlayerWeaponEx(otherid, weaponid, amount);
		SendClientMessageEx(playerid, -1, ""YELLOW"[!] Anda telah memberikan %d peluru dari %s kepada %s.", amount, ReturnWeaponName(weaponid), ReturnName(otherid));
		SendClientMessageEx(otherid, -1, ""YELLOW"[!] %s telah memberikan %d peluru dari %s kepada anda.", ReturnName(playerid), amount, ReturnWeaponName(weaponid));
	}
	else if(!strcmp(name, "drop", true))
	{
		if (!weaponid)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak memegang senjata!");

		if(IsPlayerInEvent(playerid)) 
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang berada di dalam event!");
			
		static
			Float:x,
			Float:y,
			Float:z,
			Float:angle;

		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, angle);

		x += 1 * floatsin(-angle, degrees);
		y += 1 * floatcos(-angle, degrees);

		DropWeapon(AccountData[playerid][pName], GetWeaponModel(weaponid), weaponid, GetPlayerAmmoEx(playerid), x, y, z - 1, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
		ResetWeapon(playerid, weaponid);

		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);
		SendRPMeAboveHead(playerid, sprintf("Mengambil %s dan menaruhnya dibawah lantai", ReturnWeaponName(weaponid)), X11_PLUM1);
		// SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s takes out a %s and drops it on the floor.", ReturnName(playerid), ReturnWeaponName(weaponid));
	}
	else if(!strcmp(name, "pickup", true))
	{
		if(IsPlayerInEvent(playerid)) 
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang berada di dalam event!");
		
		new wid = NearWeapon(playerid);
		if(wid != -1)
        {
			PickupWeapon(playerid, wid);
			SendRPMeAboveHead(playerid, sprintf("Mengambil %s dari bawah lantai", ReturnWeaponName(wid)), X11_PLUM1);
			// SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s has picked up a %s.", ReturnName(playerid), ReturnWeaponName(DropWeap[wid][WeaponID]));
			ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);
		}
	}
	else ShowTDN(playerid, NOTIFICATION_ERROR, "You have specified an invalid option.");
	return 1;
}
