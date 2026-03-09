#include <YSI\y_hooks>
//Door System By Dandy Bagus Prasetyo
#define	MAX_DOOR	500

enum ddoor
{
	dName[128],
	dPass[32],
	dIcon,
	dLocked,
	dAdmin,
	dOwner,
	dVip,
	dFaction,
	dFamily,
	dGarage,
	dCustom,
	dExtvw,
	dExtint,
	Float:dExtposX,
	Float:dExtposY,
	Float:dExtposZ,
	Float:dExtposA,
	dIntvw,
	dIntint,
	Float:dIntposX,
	Float:dIntposY,
	Float:dIntposZ,
	Float:dIntposA,
	//NotSave
	Text3D:dLabelext,
	Text3D:dLabelint,
	dPickupext,
	dPickupint,
	dMapIconID,
	dMapIcon
};

new DoorData[MAX_DOOR][ddoor],
	Iterator: Doors<MAX_DOOR>;
	

Doors_Save(id)
{
	new dquery[2048];
	mysql_format(g_SQL, dquery, sizeof(dquery), "UPDATE doors SET name='%s', password='%s', icon='%d', locked='%d', admin='%d', owner='%d', vip='%d', faction='%d', family='%d', garage='%d', custom='%d', extvw='%d', extint='%d', extposx='%f', extposy='%f', extposz='%f', extposa='%f', intvw='%d', intint='%d', intposx='%f', intposy='%f', intposz='%f', intposa='%f', mapicon='%d' WHERE ID='%d'",
	DoorData[id][dName], DoorData[id][dPass], DoorData[id][dIcon], DoorData[id][dLocked], DoorData[id][dAdmin], DoorData[id][dOwner], DoorData[id][dVip], DoorData[id][dFaction], DoorData[id][dFamily], DoorData[id][dGarage], DoorData[id][dCustom], DoorData[id][dExtvw], DoorData[id][dExtint], DoorData[id][dExtposX], DoorData[id][dExtposY], DoorData[id][dExtposZ], DoorData[id][dExtposA], DoorData[id][dIntvw], DoorData[id][dIntint],
	DoorData[id][dIntposX], DoorData[id][dIntposY], DoorData[id][dIntposZ], DoorData[id][dIntposA], DoorData[id][dMapIcon], id);
	mysql_tquery(g_SQL, dquery);
	return 1;
}

Doors_Updatelabel(id)
{
	if(id != -1)
	{
		if(DestroyDynamic3DTextLabel(DoorData[id][dLabelext]))
            DoorData[id][dLabelext] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        if(DestroyDynamicPickup(DoorData[id][dPickupext]))
            DoorData[id][dPickupext] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(DoorData[id][dLabelint]))
            DoorData[id][dLabelint] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        if(DestroyDynamicPickup(DoorData[id][dPickupint]))
            DoorData[id][dPickupint] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
		
		if(DestroyDynamicMapIcon(DoorData[id][dMapIconID]))
			DoorData[id][dMapIconID] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
		
        if(DoorData[id][dFamily] != -1)
		{
            new mstr[512];
			format(mstr,sizeof(mstr),""GREY"[FID:%d]\n%s\n"LIGHTBLUE"(F){FFFFFF}to Enter", DoorData[id][dFamily], DoorData[id][dName]);
			DoorData[id][dPickupext] = CreateDynamicPickup(DoorData[id][dIcon], 23, DoorData[id][dExtposX], DoorData[id][dExtposY], DoorData[id][dExtposZ], DoorData[id][dExtvw], DoorData[id][dExtint], -1, 50);
			DoorData[id][dLabelext] = CreateDynamic3DTextLabel(mstr, COLOR_WHITE, DoorData[id][dExtposX], DoorData[id][dExtposY], DoorData[id][dExtposZ]+ 0.8, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, DoorData[id][dExtvw], DoorData[id][dExtint]);
			if(DoorData[id][dIntposX] != 0.0 && DoorData[id][dIntposY] != 0.0 && DoorData[id][dIntposZ] != 0.0)
			{
				format(mstr,sizeof(mstr),""GREY"[FID:%d]\n%s\n"LIGHTBLUE"(F){FFFFFF}to Enter", DoorData[id][dFamily], DoorData[id][dName]);
				DoorData[id][dLabelint] = CreateDynamic3DTextLabel(mstr, COLOR_WHITE, DoorData[id][dIntposX], DoorData[id][dIntposY], DoorData[id][dIntposZ]+ 0.8, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, DoorData[id][dIntvw], DoorData[id][dIntint]);
				DoorData[id][dPickupint] = CreateDynamicPickup(DoorData[id][dIcon], 23, DoorData[id][dIntposX], DoorData[id][dIntposY], DoorData[id][dIntposZ], DoorData[id][dIntvw], DoorData[id][dIntint], -1, 50);
			}
		}
		else
		{
			if(DoorData[id][dGarage] == 1)
			{
				new mstr[512];
				format(mstr,sizeof(mstr),"%s", DoorData[id][dName]);
				DoorData[id][dPickupext] = CreateDynamicPickup(DoorData[id][dIcon], 23, DoorData[id][dExtposX], DoorData[id][dExtposY], DoorData[id][dExtposZ], DoorData[id][dExtvw], DoorData[id][dExtint], -1, 50);
				DoorData[id][dLabelext] = CreateDynamic3DTextLabel(mstr, COLOR_WHITE, DoorData[id][dExtposX], DoorData[id][dExtposY], DoorData[id][dExtposZ]+ 0.8, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, DoorData[id][dExtvw], DoorData[id][dExtint]);
			}
			else
			{
				new mstr[512];
				format(mstr,sizeof(mstr),"%s", DoorData[id][dName]);
				DoorData[id][dPickupext] = CreateDynamicPickup(DoorData[id][dIcon], 23, DoorData[id][dExtposX], DoorData[id][dExtposY], DoorData[id][dExtposZ], DoorData[id][dExtvw], DoorData[id][dExtint], -1, 50);
				DoorData[id][dLabelext] = CreateDynamic3DTextLabel(mstr, COLOR_WHITE, DoorData[id][dExtposX], DoorData[id][dExtposY], DoorData[id][dExtposZ]+ 0.8, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, DoorData[id][dExtvw], DoorData[id][dExtint]);
			}
			
			if(DoorData[id][dIntposX] != 0.0 && DoorData[id][dIntposY] != 0.0 && DoorData[id][dIntposZ] != 0.0)
			{
				if(DoorData[id][dGarage] == 1)
				{
					new mstr[512];
					format(mstr,sizeof(mstr),"%s", DoorData[id][dName]);

					DoorData[id][dLabelint] = CreateDynamic3DTextLabel(mstr, COLOR_WHITE, DoorData[id][dIntposX], DoorData[id][dIntposY], DoorData[id][dIntposZ]+ 0.8, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, DoorData[id][dIntvw], DoorData[id][dIntint]);
					DoorData[id][dPickupint] = CreateDynamicPickup(DoorData[id][dIcon], 23, DoorData[id][dIntposX], DoorData[id][dIntposY], DoorData[id][dIntposZ], DoorData[id][dIntvw], DoorData[id][dIntint], -1, 50);
				}
				else
				{
					new mstr[512];
					format(mstr,sizeof(mstr),"%s", DoorData[id][dName]);

					DoorData[id][dLabelint] = CreateDynamic3DTextLabel(mstr, COLOR_WHITE, DoorData[id][dIntposX], DoorData[id][dIntposY], DoorData[id][dIntposZ]+ 0.8, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, DoorData[id][dIntvw], DoorData[id][dIntint]);
					DoorData[id][dPickupint] = CreateDynamicPickup(DoorData[id][dIcon], 23, DoorData[id][dIntposX], DoorData[id][dIntposY], DoorData[id][dIntposZ], DoorData[id][dIntvw], DoorData[id][dIntint], -1, 50);
				}
			}

			if(DoorData[id][dMapIcon])
			{
				DoorData[id][dMapIconID] = CreateDynamicMapIcon(DoorData[id][dExtposX], DoorData[id][dExtposY], DoorData[id][dExtposZ], DoorData[id][dMapIcon], 0, .worldid = DoorData[id][dExtvw], .interiorid = DoorData[id][dExtint]);
			}
	    }
	}
}

/*LoadDoors()
{
	mysql_tquery(D_SQL, "SELECT ID,name,password,icon,locked,admin,vip,faction,family,custom,extvw,extint,extposx,extposy,extposz,extposa,intvw,intint,intposx,intposy,intposz,intposa FROM doors ORDER BY ID", "LoadDoorsData");
}*/

function OnDoorsCreated(playerid, id)
{
	Doors_Save(id);
	Doors_Updatelabel(id);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" membuat Dynamic Door ID: %d.", GetAdminName(playerid), id);
	return 1;
}

forward LoadDoors();
public LoadDoors()
{
    new did, rows = cache_num_rows();
    new Cache:doorCache; // Cache ID untuk delete nanti

    if(rows)
    {
        static name[128], password[128];
        doorCache = cache_save();

        for(new i = 0; i < rows; i++)
        {
            cache_get_value_name_int(i, "ID", did);
            cache_get_value_name(i, "name", name);
            format(DoorData[did][dName], 128, name);

            cache_get_value_name(i, "password", password);
            format(DoorData[did][dPass], 128, password);

            cache_get_value_name_int(i, "icon", DoorData[did][dIcon]);
            cache_get_value_name_int(i, "mapicon", DoorData[did][dMapIcon]);
            cache_get_value_name_int(i, "locked", DoorData[did][dLocked]);
            cache_get_value_name_int(i, "admin", DoorData[did][dAdmin]);
            cache_get_value_name_int(i, "owner", DoorData[did][dOwner]);
            cache_get_value_name_int(i, "vip", DoorData[did][dVip]);
            cache_get_value_name_int(i, "faction", DoorData[did][dFaction]);
            cache_get_value_name_int(i, "family", DoorData[did][dFamily]);
            cache_get_value_name_int(i, "garage", DoorData[did][dGarage]);
            cache_get_value_name_int(i, "custom", DoorData[did][dCustom]);
            cache_get_value_name_int(i, "extvw", DoorData[did][dExtvw]);
            cache_get_value_name_int(i, "extint", DoorData[did][dExtint]);
            cache_get_value_name_float(i, "extposx", DoorData[did][dExtposX]);
            cache_get_value_name_float(i, "extposy", DoorData[did][dExtposY]);
            cache_get_value_name_float(i, "extposz", DoorData[did][dExtposZ]);
            cache_get_value_name_float(i, "extposa", DoorData[did][dExtposA]);
            cache_get_value_name_int(i, "intvw", DoorData[did][dIntvw]);
            cache_get_value_name_int(i, "intint", DoorData[did][dIntint]);
            cache_get_value_name_float(i, "intposx", DoorData[did][dIntposX]);
            cache_get_value_name_float(i, "intposy", DoorData[did][dIntposY]);
            cache_get_value_name_float(i, "intposz", DoorData[did][dIntposZ]);
            cache_get_value_name_float(i, "intposa", DoorData[did][dIntposA]);

            DoorData[did][dMapIconID] = -1;

            Iter_Add(Doors, did);
            Doors_Updatelabel(did);
        }
        printf("[Dynamic Door]: Jumlah total Doors yang dimuat %d.", rows);

        if(cache_is_valid(doorCache))
        {
            cache_delete(doorCache);
            printf("[Dynamic Door]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Door]: Cache tidak valid atau sudah dihapus.");
        }
    }
}

IsPlayerStandInDoor(playerid)
{
	foreach(new i : Doors) if (IsPlayerInRangeOfPoint(playerid, 3, DoorData[i][dExtposX], DoorData[i][dExtposY], DoorData[i][dExtposZ]))
	{
		return i;
	}
	return -1;
}

CMD:lockdoor(playerid, params[])
{
	new did = IsPlayerStandInDoor(playerid);
	if(did > -1)
	{
		if (IsPlayerInRangeOfPoint(playerid, 3, DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ]))
		{
			if(DoorData[did][dOwner] == AccountData[playerid][pID])
			{
				if(!DoorData[did][dLocked])
				{
					DoorData[did][dLocked] = 1;
					PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
					ShowPlayerFooter(playerid, "Pintu ~r~Terkunci");
					mysql_tquery(g_SQL, sprintf("UPDATE doors SET locked=%d WHERE ID=%d", DoorData[did][dLocked], did));
				}
				else
				{
					DoorData[did][dLocked] = 0;
					PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
					ShowPlayerFooter(playerid, "Pintu ~g~Terbuka");
					mysql_tquery(g_SQL, sprintf("UPDATE doors SET locked=%d WHERE ID=%d", DoorData[did][dLocked], did));
				}
			}
		}
	}
	return 1;
}

CMD:createdoor(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 3)
		return PermissionError(playerid);
	
	new did = Iter_Free(Doors), mstr[128], query[248];
	if(did == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuat pintu lagi!");
	new name[128];
	if(sscanf(params, "s[128]", name)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/createdoor [name]");
	format(DoorData[did][dName], 128, name);
	GetPlayerPos(playerid, DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ]);
	GetPlayerFacingAngle(playerid, DoorData[did][dExtposA]);
	DoorData[did][dExtvw] = GetPlayerVirtualWorld(playerid);
	DoorData[did][dExtint] = GetPlayerInterior(playerid);
	format(DoorData[did][dPass], 32, "");
	DoorData[did][dIcon] = 19197;
	DoorData[did][dLocked] = 0;
	DoorData[did][dAdmin] = 0;
	DoorData[did][dOwner] = -1;
	DoorData[did][dVip] = 0;
	DoorData[did][dFaction] = 0;
	DoorData[did][dFamily] = -1;
	DoorData[did][dGarage] = 0;
	DoorData[did][dCustom] = 0;
	DoorData[did][dIntvw] = 0;
	DoorData[did][dIntint] = 0;
	DoorData[did][dIntposX] = 0;
	DoorData[did][dIntposY] = 0;
	DoorData[did][dIntposZ] = 0;
	DoorData[did][dIntposA] = 0;
	DoorData[did][dMapIcon] = 0;
	DoorData[did][dMapIconID] = -1;
	
	format(mstr,sizeof(mstr),"[ID: %d]\n{FFFFFF}%s\n{FFFFFF}Press {FF0000}ENTER {FFFFFF}to enter", did, DoorData[did][dName]);
	DoorData[did][dPickupext] = CreateDynamicPickup(DoorData[did][dIcon], 23, DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ], DoorData[did][dExtvw], DoorData[did][dExtint], -1, 50);
	DoorData[did][dLabelext] = CreateDynamic3DTextLabel( mstr, COLOR_YELLOW, DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ]+ 0.8, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, DoorData[did][dExtvw], DoorData[did][dExtint]);
    Doors_Updatelabel(did);
	Iter_Add(Doors, did);

	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO doors SET ID=%d, extvw=%d, extint=%d, extposx=%f, extposy=%f, extposz=%f, extposa=%f, name='%s'", did, DoorData[did][dExtvw], DoorData[did][dExtint], DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ], DoorData[did][dExtposA], name);
	mysql_tquery(g_SQL, query, "OnDoorsCreated", "ii", playerid, did);
	return 1;
}

/*CMD:gotodoor(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1) return PermissionError(playerid);

	static shstr[525];
	format(shstr, sizeof(shstr), "#ID\tDoor Name\n");
	forex(i, MAX_DOOR) if (DoorData[i][dExtposX] != 0.0)
	{
		format(shstr, sizeof(shstr), "%s#%d\t%s\n", shstr, i, DoorData[i][dName]);
	}
	Dialog_Show(playerid, DIALOG_GOTO_DOOR, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Door", shstr, "Select", "Cancel");
	return 1;
}

Dialog:DIALOG_GOTO_DOOR(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		SetPlayerPositionEx(playerid, DoorData[listitem][dExtposX], DoorData[listitem][dExtposY], DoorData[listitem][dExtposZ], DoorData[listitem][dExtposA], 6000);
		SetPlayerInterior(playerid, DoorData[listitem][dExtint]);
		SetPlayerVirtualWorld(playerid, DoorData[listitem][dExtvw]);
		AccountData[playerid][pInDoor] = -1;
		AccountData[playerid][pInHouse] = -1;
		AccountData[playerid][pInBiz] = -1;
		AccountData[playerid][pInFamily] = -1;
		AccountData[playerid][pInRusun] = -1;
		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" teleportasi ke Door ID: %d.", GetAdminName(playerid), listitem);
	}
	else Info(playerid, "Anda telah membatalkan pilihan");
	return 1;
}*/

CMD:gotodoor(playerid, params[])
{
	new did;
	if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1)
        return PermissionError(playerid);
		
	if(sscanf(params, "d", did))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotodoor [id]");
	if(!Iter_Contains(Doors, did)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Pintu yang kamu tuju tidak ada.");
	SetPlayerPositionEx(playerid, DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ], DoorData[did][dExtposA], 6000);
    SetPlayerInterior(playerid, DoorData[did][dExtint]);
    SetPlayerVirtualWorld(playerid, DoorData[did][dExtvw]);
	AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" teleportasi ke Door ID: %d.", GetAdminName(playerid), did);
	return 1;
}

CMD:editdoor(playerid, params[])
{
    static
        did,
        type[24],
        string[128];

    if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", did, type, string))
    {
        ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editdoor [id] [name]~n~location, interior, password, name,~n~ locked, pickup, admin, vip, faction, family, custom, virtual, iconmap");
        return 1;
    }
    if((did < 0 || did >= MAX_DOOR))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "You have specified an invalid entrance ID.");
	if(!Iter_Contains(Doors, did)) return ShowTDN(playerid, NOTIFICATION_ERROR, "The doors you specified ID of doesn't exist.");

    if(!strcmp(type, "location", true))
    {
		GetPlayerPos(playerid, DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ]);
		GetPlayerFacingAngle(playerid, DoorData[did][dExtposA]);

        DoorData[did][dExtvw] = GetPlayerVirtualWorld(playerid);
		DoorData[did][dExtint] = GetPlayerInterior(playerid);
        Doors_Save(did);
		Doors_Updatelabel(did);

		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengubah posisi spawn Exterior Door ID: %d.", GetAdminName(playerid), did);
    }
	else if(!strcmp(type, "pickup", true))
	{
		new idp;
		if(sscanf(string, "d", idp))
			return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editdoor [id] [pickup] [id pickup]");
		
		DoorData[did][dIcon] = idp;
		Doors_Save(did);
		Doors_Updatelabel(did);
		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah Pickup ID Door ID: %d menjadi ID: %d", GetAdminName(playerid), did, idp);
	}
    else if(!strcmp(type, "interior", true))
    {
        GetPlayerPos(playerid, DoorData[did][dIntposX], DoorData[did][dIntposY], DoorData[did][dIntposZ]);
		GetPlayerFacingAngle(playerid, DoorData[did][dIntposA]);

        DoorData[did][dIntvw] = GetPlayerVirtualWorld(playerid);
		DoorData[did][dIntint] = GetPlayerInterior(playerid);
        Doors_Save(did);
		Doors_Updatelabel(did);
		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan posisi spawn Interior Door ID: %d.", GetAdminName(playerid), did);
    }
    else if(!strcmp(type, "custom", true))
    {
        new status;

        if(sscanf(string, "d", status))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editdoor [id] [custom] [0/1]");

        if(status < 0 || status > 1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "You must specify at least 0 or 1.");

        DoorData[did][dCustom] = status;
        Doors_Save(did);
		Doors_Updatelabel(did);

        if(status) {
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" has enabled custom interior mode for entrance ID: %d.", AccountData[playerid][pAdminname], did);
        }
        else {
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" has disabled custom interior mode for entrance ID: %d.", AccountData[playerid][pAdminname], did);
        }
    }
    else if(!strcmp(type, "virtual", true))
    {
        new worldid;

        if(sscanf(string, "d", worldid))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editdoor [id] [virtual] [interior world]");

        DoorData[did][dExtvw] = worldid;

        Doors_Save(did);
		Doors_Updatelabel(did);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengubah WWID Door ID: %d menjadi %d.", GetAdminName(playerid), did, worldid);
    }
    else if(!strcmp(type, "password", true))
    {
        new password[32];

        if(sscanf(string, "s[32]", password))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editdoor [id] [password] [entrance pass] (use 'none' to disable)");

        if(!strcmp(password, "none", true)) {
            format(DoorData[did][dPass], 32, "");
        }
        else {
            format(DoorData[did][dPass], 32, password);
        }
        Doors_Save(did);
		Doors_Updatelabel(did);
		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengubah menetapkan password Door ID: "YELLOW"%d - (%s).", GetAdminName(playerid), did, password);
    }
    else if(!strcmp(type, "locked", true))
    {
        new locked;

        if(sscanf(string, "d", locked))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editdoor [id] [locked] [locked 0/1]");

        if(locked < 0 || locked > 1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid value. Use 0 for unlocked and 1 for locked.");

        DoorData[did][dLocked] = locked;
        Doors_Save(did);
		Doors_Updatelabel(did);

        if(locked) {
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengunci Door ID: %d.", GetAdminName(playerid), did);
        } else {
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah membuka kunci Door ID: %d.", GetAdminName(playerid), did);
        }
    }
    else if(!strcmp(type, "name", true))
    {
        new name[128];

        if(sscanf(string, "s[128]", name))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editdoor [id] [name] [new name]");

        format(DoorData[did][dName], 128, ColouredText(name));

        Doors_Save(did);
		Doors_Updatelabel(did);

		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengubah nama Door ID: %d to \"%s\".", GetAdminName(playerid), did, ColouredText(name));
    }
	else if(!strcmp(type, "admin", true))
    {
        new level;

        if(sscanf(string, "d", level))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editdoor [id] [admin] [level]");

        if(level < 0 || level > 5)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid value. Use 0 - 5 for level.");

        DoorData[did][dAdmin] = level;
        Doors_Save(did);
		Doors_Updatelabel(did);

		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan Door ID: %d untuk Admin level %d.", GetAdminName(playerid), did, level);
    }
	else if(!strcmp(type, "owner", true))
	{
		new owner;
		if(sscanf(string, "d", owner))
			return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editdoor [id] [owner] [name/playerid]");
		
		if(owner == -1) {
			DoorData[did][dOwner] = -1;
			Doors_Save(did);
			Doors_Updatelabel(did);
			return 1;
		}

		if(!IsPlayerConnected(owner))	
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
		
		DoorData[did][dOwner] = AccountData[owner][pID];
		Doors_Save(did);
		Doors_Updatelabel(did);
		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan Owner Door ID: %d untuk "YELLOW"%s(%d)", GetAdminName(playerid), did, ReturnName(owner), owner);
	}
	else if(!strcmp(type, "vip", true))
    {
        new level;

        if(sscanf(string, "d", level))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editdoor [id] [VIP] [level]");

        if(level < 0 || level > 3)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid value. Use 0 - 3 for level.");

        DoorData[did][dVip] = level;
        Doors_Save(did);
		Doors_Updatelabel(did);

		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan Door ID: %d untuk VIP Level %d.", GetAdminName(playerid), did, level);
    }
	else if(!strcmp(type, "faction", true))
    {
        new fid;

        if(sscanf(string, "d", fid))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editdoor [id] [faction] [faction id]");

        if(fid < 0 || fid > 4)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid value. Use 0 - 4 for type.");

        DoorData[did][dFaction] = fid;
        Doors_Save(did);
		Doors_Updatelabel(did);

		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan Door ID: %d untuk Faction ID: %d.", GetAdminName(playerid), did, fid);
    }
	else if(!strcmp(type, "family", true))
    {
        new fid;

        if(sscanf(string, "d", fid))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editdoor [id] [family] [family id]");

        if(fid < -1 || fid > MAX_FAMILIES)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid value. Use -1 for family id.");

        DoorData[did][dFamily] = fid;
        Doors_Save(did);
		Doors_Updatelabel(did);

		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan Door ID: %d untuk Families ID: %d.", GetAdminName(playerid), did, fid);
    }
	else if(!strcmp(type, "garage", true))
	{
		new gid;

        if(sscanf(string, "d", gid))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editdoor [id] [garage] [0 - 1]");

        if(gid < 0 || gid > 1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid value! Use 0 to disable, 1 to enable.");
		
		if(gid == 0)
		{
			DoorData[did][dGarage] = 0;
			SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" has set entrance ID: %d to garage vehicle disable.", AccountData[playerid][pAdminname], did);
		}
		else
		{
			DoorData[did][dGarage] = 1;
			SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" has set entrance ID: %d to garage vehicle enable.", AccountData[playerid][pAdminname], did);
		}
		Doors_Save(gid);
		Doors_Updatelabel(gid);
	}
	else if(!strcmp(type, "iconmap", true))
	{
		new iconid;
	    if(sscanf(string, "i", iconid))
	    {
	        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editdoor [id] [iconmap] [iconid (0-63)]");
		}
		if(!(0 <= iconid <= 63))
		{
		    return ShowTDN(playerid, NOTIFICATION_ERROR, "Ikon peta tidak valid..");
		}

		DoorData[did][dMapIcon] = iconid;

		Doors_Save(did);
		Doors_Updatelabel(did);

	    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" has set entrance ID: %d to Map Icon id %d.", AccountData[playerid][pAdminname], did, iconid);
	}
	else if(!strcmp(type, "delete", true))
    {
		DestroyDynamic3DTextLabel(DoorData[did][dLabelext]);
		DestroyDynamicPickup(DoorData[did][dPickupext]);
		DestroyDynamic3DTextLabel(DoorData[did][dLabelint]);
		DestroyDynamicPickup(DoorData[did][dPickupint]);
		DestroyDynamicMapIcon(DoorData[did][dMapIconID]);
			
		DoorData[did][dExtposX] = 0;
		DoorData[did][dExtposY] = 0;
		DoorData[did][dExtposZ] = 0;
		DoorData[did][dExtposA] = 0;
		DoorData[did][dExtvw] = 0;
		DoorData[did][dExtint] = 0;
		format(DoorData[did][dPass], 32, "");
		DoorData[did][dIcon] = 0;
		DoorData[did][dLocked] = 0;
		DoorData[did][dAdmin] = 0;
		DoorData[did][dOwner] = -1;
		DoorData[did][dVip] = 0;
		DoorData[did][dFaction] = 0;
		DoorData[did][dFamily] = -1;
		DoorData[did][dGarage] = 0;
		DoorData[did][dCustom] = 0;
		DoorData[did][dIntvw] = 0;
		DoorData[did][dIntint] = 0;
		DoorData[did][dIntposX] = 0;
		DoorData[did][dIntposY] = 0;
		DoorData[did][dIntposZ] = 0;
		DoorData[did][dIntposA] = 0;
		DoorData[did][dMapIconID] = -1;
		DoorData[did][dMapIcon] = 0;
		
		DoorData[did][dLabelext] = Text3D: INVALID_3DTEXT_ID;
		DoorData[did][dLabelint] = Text3D: INVALID_3DTEXT_ID;
		DoorData[did][dPickupext] = -1;
		DoorData[did][dPickupint] = -1;
		
		Iter_Remove(Doors, did);
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "DELETE FROM doors WHERE ID=%d", did);
		mysql_tquery(g_SQL, query);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menghapus Dynamic Door ID %d.", AccountData[playerid][pAdminname], did);
	}
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_SECONDARY_ATTACK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		foreach(new did : Doors)
		{
			if(IsPlayerInRangeOfPoint(playerid, 1.5, DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ]))
			{
				if(DoorData[did][dIntposX] == 0.0 && DoorData[did][dIntposY] == 0.0 && DoorData[did][dIntposZ] == 0.0)
					return ShowTDN(playerid, NOTIFICATION_ERROR, "Administrator belum menerapkan interior pada pintu ini.");

				if(DoorData[did][dLocked])
					return ShowTDN(playerid, NOTIFICATION_ERROR, "Pintu ini dikunci!.");
					
				if(DoorData[did][dFaction] > 0)
				{
					if(DoorData[did][dFaction] != AccountData[playerid][pFaction])
						return ShowTDN(playerid, NOTIFICATION_ERROR, "Pintu ini khusus anggota salah satu faction!");
				}

				if(DoorData[did][dFamily] > -1)
				{
					if(DoorData[did][dFamily] != AccountData[playerid][pFamily] || AccountData[playerid][pFamily] == -1)
						return ShowTDN(playerid, NOTIFICATION_ERROR, "Pintu ini khusus untuk anggota salah satu Family!");
				}
				
				if(DoorData[did][dVip] > AccountData[playerid][pVip])
					return ShowTDN(playerid, NOTIFICATION_ERROR, "Level VIP Kamu tidak mencukupi persyaratan masuk ke pintu ini.");
				
				if(DoorData[did][dAdmin] > AccountData[playerid][pAdmin])
					return ShowTDN(playerid, NOTIFICATION_ERROR, "Rank Admin Kamu tidak mencukupi persyaratan masuk ke pintu ini.");
					
				if(strlen(DoorData[did][dPass]))
				{
					new params[256];
					if(sscanf(params, "s[256]", params)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/enter [password]");
					if(strcmp(params, DoorData[did][dPass])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid door password.");
					
					if(DoorData[did][dCustom])
					{
						Player_ToggleTelportAntiCheat(playerid, false);
						SetPlayerPositionEx(playerid, DoorData[did][dIntposX], DoorData[did][dIntposY], DoorData[did][dIntposZ], DoorData[did][dIntposA], 5000);
					}
					else
					{
						SetPlayerPositionEx(playerid, DoorData[did][dIntposX], DoorData[did][dIntposY], DoorData[did][dIntposZ], DoorData[did][dIntposA], 5000);
					}
				}
				else
				{
					if(DoorData[did][dCustom])
					{
						Player_ToggleTelportAntiCheat(playerid, false);
						SetPlayerPositionEx(playerid, DoorData[did][dIntposX], DoorData[did][dIntposY], DoorData[did][dIntposZ], DoorData[did][dIntposA], 5000);
					}
					else
					{
						SetPlayerPositionEx(playerid, DoorData[did][dIntposX], DoorData[did][dIntposY], DoorData[did][dIntposZ], DoorData[did][dIntposA], 5000);
					}
				}
				AccountData[playerid][pInDoor] = did;
				AccountData[playerid][UsingDoor] = true;
				SetPlayerInterior(playerid, DoorData[did][dIntint]);
				SetPlayerVirtualWorld(playerid, DoorData[did][dIntvw]);
				SetCameraBehindPlayer(playerid);
				SetPlayerWeather(playerid, 0);
			}
			new doorid = AccountData[playerid][pInDoor];
			if(AccountData[playerid][pInDoor] != -1 && IsPlayerInRangeOfPoint(playerid, 1.5, DoorData[doorid][dIntposX], DoorData[doorid][dIntposY], DoorData[doorid][dIntposZ]))
			{
				if(DoorData[doorid][dFaction] > 0)
				{
					if(DoorData[doorid][dFaction] != AccountData[playerid][pFaction])
						return ShowTDN(playerid, NOTIFICATION_ERROR, "Pintu ini khusus untuk anggota salah satu faction!");
				}
				
				if(DoorData[doorid][dCustom])
				{
					SetPlayerPositionEx(playerid, DoorData[doorid][dExtposX], DoorData[doorid][dExtposY], DoorData[doorid][dExtposZ], DoorData[doorid][dExtposA], 5000);
				}
				else
				{
					SetPlayerPositionEx(playerid, DoorData[doorid][dExtposX], DoorData[doorid][dExtposY], DoorData[doorid][dExtposZ], DoorData[doorid][dExtposA], 5000);
				}
				SetPlayerInterior(playerid, DoorData[doorid][dExtint]);
				SetPlayerVirtualWorld(playerid, DoorData[doorid][dExtvw]);
				SetCameraBehindPlayer(playerid);
				SetPlayerWeather(playerid, WorldWeather);
				AccountData[playerid][pInDoor] = -1;
				AccountData[playerid][UsingDoor] = true;
			}
        }
	}

	if(newkeys & KEY_CROUCH && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		foreach(new did : Doors)
		{
			if(IsPlayerInRangeOfPoint(playerid, 3.0, DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ]))
			{
				if(DoorData[did][dGarage] == 1)
				{
					if(DoorData[did][dGarage] == 1)
					{
						if(DoorData[did][dIntposX] == 0.0 && DoorData[did][dIntposY] == 0.0 && DoorData[did][dIntposZ] == 0.0)
							return ShowTDN(playerid, NOTIFICATION_ERROR, "Interior entrance masih kosong, atau tidak memiliki interior.");

						if(DoorData[did][dLocked])
							return ShowTDN(playerid, NOTIFICATION_ERROR, "This entrance is locked at the moment.");
							
						if(DoorData[did][dFaction] > 0)
						{
							if(DoorData[did][dFaction] != AccountData[playerid][pFaction])
								return ShowTDN(playerid, NOTIFICATION_ERROR, "This door only for faction.");
						}
						if(DoorData[did][dFamily] > 0)
						{
							if(DoorData[did][dFamily] != AccountData[playerid][pFamily])
								return ShowTDN(playerid, NOTIFICATION_ERROR, "This door only for family.");
						}
						
						if(DoorData[did][dVip] > AccountData[playerid][pVip])
							return ShowTDN(playerid, NOTIFICATION_ERROR, "Your VIP level not enough to enter this door.");
						
						if(DoorData[did][dAdmin] > AccountData[playerid][pAdmin])
							return ShowTDN(playerid, NOTIFICATION_ERROR, "Your admin level not enough to enter this door.");
							
						if(strlen(DoorData[did][dPass]))
						{
							new params[256];
							if(sscanf(params, "s[256]", params)) return ShowTDN(playerid, NOTIFICATION_ERROR, "/enter [password]");
							if(strcmp(params, DoorData[did][dPass])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid door password.");
							
							if(DoorData[did][dCustom])
							{
								SetVehiclePosition(playerid, GetPlayerVehicleID(playerid), DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ], DoorData[did][dExtposA]);
							}
							else
							{
								SetVehiclePosition(playerid, GetPlayerVehicleID(playerid), DoorData[did][dIntposX], DoorData[did][dIntposY], DoorData[did][dIntposZ], DoorData[did][dIntposA]);
							}
							AccountData[playerid][pInDoor] = did;
							SetPlayerInterior(playerid, DoorData[did][dIntint]);
							SetPlayerVirtualWorld(playerid, DoorData[did][dIntvw]);
							SetCameraBehindPlayer(playerid);
							SetPlayerWeather(playerid, 0);
						}
						else
						{
							if(DoorData[did][dCustom])
							{
								SetVehiclePosition(playerid, GetPlayerVehicleID(playerid), DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ], DoorData[did][dExtposA]);
							}
							else
							{
								SetVehiclePosition(playerid, GetPlayerVehicleID(playerid), DoorData[did][dIntposX], DoorData[did][dIntposY], DoorData[did][dIntposZ], DoorData[did][dIntposA]);
							}
							AccountData[playerid][pInDoor] = did;
							SetPlayerInterior(playerid, DoorData[did][dIntint]);
							SetPlayerVirtualWorld(playerid, DoorData[did][dIntvw]);
							SetCameraBehindPlayer(playerid);
							SetPlayerWeather(playerid, 0);
							LinkVehicleToInterior(GetPlayerVehicleID(playerid), DoorData[did][dIntint]);
							SetVehicleVirtualWorld(GetPlayerVehicleID(playerid), DoorData[did][dIntvw]);

							foreach(new i : Player) if(IsPlayerConnected(i) && i != playerid)
							{
								if(IsPlayerInVehicle(i, GetPlayerVehicleID(playerid)))
								{
									SetPlayerInterior(i, DoorData[did][dIntint]);
									SetPlayerVirtualWorld(i, DoorData[did][dIntvw]);
								}
							}
						}
					}
				}
			}
			if(IsPlayerInRangeOfPoint(playerid, 3.0, DoorData[did][dIntposX], DoorData[did][dIntposY], DoorData[did][dIntposZ]))
			{
				if(DoorData[did][dGarage] == 1)
				{
					if(DoorData[did][dFaction] > 0)
					{
						if(DoorData[did][dFaction] != AccountData[playerid][pFaction])
							return ShowTDN(playerid, NOTIFICATION_ERROR, "This door only for faction.");
					}
				
					if(DoorData[did][dCustom])
					{
						SetVehiclePosition(playerid, GetPlayerVehicleID(playerid), DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ], DoorData[did][dExtposA]);
					}
					else
					{
						SetVehiclePosition(playerid, GetPlayerVehicleID(playerid), DoorData[did][dExtposX], DoorData[did][dExtposY], DoorData[did][dExtposZ], DoorData[did][dExtposA]);
					}
					AccountData[playerid][pInDoor] = -1;
					SetPlayerInterior(playerid, DoorData[did][dExtint]);
					SetPlayerVirtualWorld(playerid, DoorData[did][dExtvw]);
					SetCameraBehindPlayer(playerid);
					SetPlayerWeather(playerid, WorldWeather);
					LinkVehicleToInterior(GetPlayerVehicleID(playerid), DoorData[did][dExtint]);
					SetVehicleVirtualWorld(GetPlayerVehicleID(playerid), DoorData[did][dExtvw]);

					foreach(new i : Player) if(IsPlayerConnected(i) && i != playerid)
					{
						if(IsPlayerInVehicle(i, GetPlayerVehicleID(playerid)))
						{
							SetPlayerInterior(i, DoorData[did][dExtint]);
							SetPlayerVirtualWorld(i, DoorData[did][dExtvw]);
						}
					}
				}
			}
		}
	}
	return 1;
}