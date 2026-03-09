#include <YSI\y_hooks>

#define MAX_GSTATION 50
new Text3D:LabelFuel[MAX_PLAYERS];
new bool: DurringRefill[MAX_PLAYERS] = {false, ...};
new pTimerRefill[MAX_PLAYERS] = {-1, ...};

enum gsinfo
{
	gOwner[MAX_PLAYER_NAME],
	gOwnerID,
	gName[128],
	gMoney,
	gPrice,
	gStockPrice,
	gRestock,
	gsStock,
	Float:gsPosX,
	Float:gsPosY,
	Float:gsPosZ,
	Text3D:gsLabel,
	MapIconGas,
};

new gsData[MAX_GSTATION][gsinfo],
	Iterator: GStation<MAX_GSTATION>;

hook OnPlayerConnect(playerid)
{
    /* Reset Vars */
    pTimerRefill[playerid] = -1;
    DurringRefill[playerid] = false;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    /* Reset Vars */
    KillTimer(pTimerRefill[playerid]);
    pTimerRefill[playerid] = -1;
    DurringRefill[playerid] = false;
    return 1;
}
	

stock ShowGasPriceDialog(playerid, gsid)
{
    new str[128];
    format(str, sizeof(str), "Harga gas saat ini: "YELLOW_E"%d\n\n"WHITE_E"Silakan masukkan harga baru per liter:", gsData[gsid][gStockPrice]);
    ShowPlayerDialog(playerid, GS_PRICESET, DIALOG_STYLE_INPUT, "Set Harga Gas Station", str, "Set", "Batal");
}

GStation_Refresh(gsid)
{
	if(gsid != -1)
    {
        if(IsValidDynamic3DTextLabel(gsData[gsid][gsLabel]))
            DestroyDynamic3DTextLabel(gsData[gsid][gsLabel]);
		
		if(IsValidDynamicMapIcon(gsData[gsid][MapIconGas]))
			IsValidDynamicMapIcon(gsData[gsid][MapIconGas]);
		
		gsData[gsid][MapIconGas] = INVALID_STREAMER_ID;

        new string[255];
		if(strcmp(gsData[gsid][gOwner], "-") || gsData[gsid][gOwnerID] != 0)
		{
			format(string, sizeof(string), "[ID: %d]\nPemilik "YELLOW_E"%s\n"WHITE_E"Nama: "YELLOW_E"%s\n"YELLOW_E"Tekan"GREEN_E" H"WHITE_E" untuk mengisi BBM\n"WHITE_E"Stock: "YELLOW_E"%d\n"WHITE_E"Harga Perliter "YELLOW_E"%d", gsid, gsData[gsid][gOwner], gsData[gsid][gName], gsData[gsid][gsStock], gsData[gsid][gStockPrice]);
			gsData[gsid][gsLabel] = CreateDynamic3DTextLabel(string, COLOR_GREEN, gsData[gsid][gsPosX], gsData[gsid][gsPosY], gsData[gsid][gsPosZ]-0.3, 4.5);
			gsData[gsid][MapIconGas] = CreateDynamicMapIcon(gsData[gsid][gsPosX], gsData[gsid][gsPosY], gsData[gsid][gsPosZ], 63, -1, 0, 0, -1, 1500.0, MAPICON_LOCAL, -1, 0);
		}
		else
		{
			format(string, sizeof(string), "{FFFFFF}ID: %d\nGas Station ini di jual\nHarga: {FF8B59}%s\n{8E9FD4}[ALT] {FFFFFF}untuk membeli Gas Station", gsid, FormatMoney(gsData[gsid][gPrice]));
			gsData[gsid][gsLabel] = CreateDynamic3DTextLabel(string, COLOR_GREEN, gsData[gsid][gsPosX], gsData[gsid][gsPosY], gsData[gsid][gsPosZ]-0.3, 4.5);
			gsData[gsid][MapIconGas] = CreateDynamicMapIcon(gsData[gsid][gsPosX], gsData[gsid][gsPosY], gsData[gsid][gsPosZ], 63, -1, 0, 0, -1, 1500.0, MAPICON_LOCAL, -1, 0);
		}
	}
    return 1;
}

function LoadGStations()
{
    static gsid;
	
	new rows = cache_num_rows(), owner[128], name[128];
 	if(rows)
  	{
		for(new i; i < rows; i++)
		{
			cache_get_value_name_int(i, "id", gsid);
			cache_get_value_name_int(i, "stock", gsData[gsid][gsStock]);
			cache_get_value_name_float(i, "posx", gsData[gsid][gsPosX]);
			cache_get_value_name_float(i, "posy", gsData[gsid][gsPosY]);
			cache_get_value_name_float(i, "posz", gsData[gsid][gsPosZ]);
			cache_get_value_name(i, "owner", owner);
			format(gsData[gsid][gOwner], 128, owner);
			cache_get_value_name_int(i, "ownerid", gsData[gsid][gOwnerID]);
			cache_get_value_name(i, "name", name);
			format(gsData[gsid][gName], 128, name);
			cache_get_value_name_int(i, "price", gsData[gsid][gPrice]);
			cache_get_value_name_int(i, "money", gsData[gsid][gMoney]);
			cache_get_value_name_int(i, "restock", gsData[gsid][gRestock]);
			cache_get_value_name_int(i, "gsprice", gsData[gsid][gStockPrice]);
			GStation_Refresh(gsid);
			Iter_Add(GStation, gsid);
		}
		printf("[Dynamic Gas Station] Number of Loaded: %d.", rows);
	}
}

GStation_Save(gsid)
{
	new cQuery[512];
	format(cQuery, sizeof(cQuery), "UPDATE gstations SET stock='%d', posx='%f', posy='%f', posz='%f', owner='%s', name='%s', price='%d', money='%d', restock='%d', ownerid='%d', gsprice='%d' WHERE id='%d'",
	gsData[gsid][gsStock],
	gsData[gsid][gsPosX],
	gsData[gsid][gsPosY],
	gsData[gsid][gsPosZ],
	gsData[gsid][gOwner],
	gsData[gsid][gName],
	gsData[gsid][gPrice],
	gsData[gsid][gMoney],
	gsData[gsid][gRestock],
	gsData[gsid][gOwnerID],
	gsData[gsid][gStockPrice],
	gsid
	);
	return mysql_tquery(g_SQL, cQuery);
}

GetOwnedGas(playerid)
{
	new tmpcount;
	foreach(new gsid : GStation) 
	{
	    if(!strcmp(gsData[gsid][gOwner], AccountData[playerid][pName], true) || (gsData[gsid][gOwnerID] == AccountData[playerid][pID]))
	    {
     		tmpcount++;
		}
	}
	return tmpcount;
}

GetGStationNearest(playerid)
{
	new tmpcount;
	foreach(new id : GStation)
	{
	    if(gsData[id][gsStock] > 0)
	    {
	    	if(GetPlayerDistanceFromPoint(playerid, gsData[id][gsPosX], gsData[id][gsPosY], gsData[id][gsPosZ]) < 10000)
	    	{
     			tmpcount++;
	    	}
		}
	}
	return tmpcount;
}

ReturnGStationNearestID(playerid, slot)
{
	new tmpcount;
	if(slot < 1 && slot > MAX_GSTATION) return -1;
	foreach(new id : GStation)
	{
	    if(gsData[id][gsStock] > 0)
	    {
	    	if(GetPlayerDistanceFromPoint(playerid, gsData[id][gsPosX], gsData[id][gsPosY], gsData[id][gsPosZ]) < 10000)
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

ReturnPlayerGasStationID(playerid, hslot)
{
	new tmpcount;
	if(hslot < 1 && hslot > LIMIT_PER_PLAYER) return -1;
	foreach(new gsid : GStation)
	{
	    if(!strcmp(AccountData[playerid][pName], gsData[gsid][gOwner], true) || (gsData[gsid][gOwnerID] == AccountData[playerid][pID]))
	    {
     		tmpcount++;
       		if(tmpcount == hslot)
       		{
        		return gsid;
  			}
	    }
	}
	return -1;
}

Player_OwnsGas(playerid, id)
{
	return (gsData[id][gOwnerID] == AccountData[playerid][pID]) || (!strcmp(gsData[id][gOwner], AccountData[playerid][pName], true));
}

Gas_Reset(id)
{
	format(gsData[id][gOwner], MAX_PLAYER_NAME, "-");
	format(gsData[id][gName], 128, "-");
	gsData[id][gOwnerID] = -1;
	gsData[id][gMoney] = 0;
	gsData[id][gRestock] = 0;
	GStation_Refresh(id);
}

stock GetPlayerGasStationID(playerid)
{
    foreach(new i : GStation)
    {
        if(gsData[i][gOwnerID] == AccountData[playerid][pID] || !strcmp(gsData[i][gOwner], AccountData[playerid][pName], true))
        {
            return i;
        }
    }
    return -1;
}
CMD:creategs(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 4)
		return PermissionError(playerid);
	
	new gsid = Iter_Free(GStation), query[512], address[128];
	if(gsid == -1) return Error(playerid, "You cant create more gs!");
	new stok, price;
	if(sscanf(params, "dd", price, stok)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/creategs [price] [stock - max: 10000/liters]");
	
	if(stok < 1 || stok > 10000) return Error(playerid, "Invagsid stok.");
	
	GetPlayerPos(playerid, gsData[gsid][gsPosX], gsData[gsid][gsPosY], gsData[gsid][gsPosZ]);
	gsData[gsid][gsStock] = stok;
	format(gsData[gsid][gOwner], 128, "-");
	gsData[gsid][gOwnerID] = -1;
	gsData[gsid][gPrice] = price;
	gsData[gsid][gMoney] = 0;
	gsData[gsid][gRestock] = 1000;
	gsData[gsid][gStockPrice] = 10;
	address = GetLocation(gsData[gsid][gsPosX], gsData[gsid][gsPosY], gsData[gsid][gsPosZ]);
	format(gsData[gsid][gName], 128, address);
    GStation_Refresh(gsid);
	Iter_Add(GStation, gsid);

	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO gstations SET id='%d', stock='%d', posx='%f', posy='%f', posz='%f', owner='%s', ownerid='%d', price='%d', money='%d', restock='%d', name='%s', gsprice='%d'", gsid, gsData[gsid][gsStock], gsData[gsid][gsPosX], gsData[gsid][gsPosY], gsData[gsid][gsPosZ], gsData[gsid][gOwner], gsData[gsid][gOwnerID], gsData[gsid][gPrice], gsData[gsid][gMoney], gsData[gsid][gRestock], gsData[gsid][gName], gsData[gsid][gStockPrice]);
	mysql_tquery(g_SQL, query, "OnGstationCreated", "i", gsid);
	return 1;
}

function OnGstationCreated(gsid)
{
	GStation_Save(gsid);
	return 1;
}

CMD:gotogs(playerid, params[])
{
	new gsid;
	if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);
		
	if(sscanf(params, "d", gsid))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotogs [id]");
		
	if(!Iter_Contains(GStation, gsid)) return Error(playerid, "The gs you specified ID of doesn't exist.");
	SetPlayerPosition(playerid, gsData[gsid][gsPosX], gsData[gsid][gsPosY], gsData[gsid][gsPosZ], 2.0);
    SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 0);
	AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
	Info(playerid, "You has teleport to gs id %d", gsid);
	return 1;
}

CMD:editgs(playerid, params[])
{
    static
        gsid,
        type[24],
        string[128];

    if(AccountData[playerid][pAdmin] < 4)
        return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", gsid, type, string))
    {
        ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editgs [id] [name]");
        Info(playerid, "location, stock, delete, owner, restock, price, money");
        return 1;
    }
    if((gsid < 0 || gsid >= MAX_GSTATION))
        return Error(playerid, "You have specified an invagsid ID.");
	if(!Iter_Contains(GStation, gsid)) return Error(playerid, "The doors you specified ID of doesn't exist.");

    if(!strcmp(type, "location", true))
    {
		GetPlayerPos(playerid, gsData[gsid][gsPosX], gsData[gsid][gsPosY], gsData[gsid][gsPosZ]);
        GStation_Save(gsid);
		GStation_Refresh(gsid);

        SendAdminMessage(COLOR_RED, "%s has adjusted the location of gs ID: %d.", AccountData[playerid][pAdminname], gsid);
    }
    else if(!strcmp(type, "stock", true))
    {
        new stok;

        if(sscanf(string, "d", stok))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editgs [id] [type] [stock - 10000]");

        if(stok < 1 || stok > 10000)
            return Error(playerid, "You must specify at least 1 - 5.");

        gsData[gsid][gsStock] = stok;
        GStation_Save(gsid);
		GStation_Refresh(gsid);

        SendAdminMessage(COLOR_RED, "%s has set gs ID: %d stock to %d.", AccountData[playerid][pAdminname], gsid, stok);
    }
	else if(!strcmp(type, "restock", true))
    {
        new prod;

        if(sscanf(string, "d", prod))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editgs [id] [restock] [0-1]");
		
		if(prod == 0)
		{
			gsData[gsid][gRestock] = 0;
			
			new query[128];
			mysql_format(g_SQL, query, sizeof(query), "UPDATE gstations SET restock='%d' WHERE ID='%d'", gsData[gsid][gRestock], gsid);
			mysql_tquery(g_SQL, query);

			GStation_Refresh(gsid);
			SendAdminMessage(COLOR_RED, "%s has adjusted the restock of gas station ID: %d to disable.", AccountData[playerid][pAdminname], gsid);
		}
		else if(prod == 1)
		{
			gsData[gsid][gRestock] = 1;
			
			new query[128];
			mysql_format(g_SQL, query, sizeof(query), "UPDATE gstations SET restock='%d' WHERE ID='%d'", gsData[gsid][gRestock], gsid);
			mysql_tquery(g_SQL, query);

			GStation_Refresh(gsid);
			SendAdminMessage(COLOR_RED, "%s has adjusted the restock of gas station ID: %d to enable.", AccountData[playerid][pAdminname], gsid);
		}
		else return Error(playerid, "Hanya id 0-1");
    }
	else if(!strcmp(type, "price", true))
    {
        new price;

        if(sscanf(string, "d", price))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editgs [id] [Price] [Amount]");

        gsData[gsid][gPrice] = price;
		
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE gstations SET price='%d' WHERE ID='%d'", gsData[gsid][gPrice], gsid);
		mysql_tquery(g_SQL, query);

		GStation_Refresh(gsid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the price of bisnis ID: %d to %d.", AccountData[playerid][pAdminname], gsid, price);
    }
	else if(!strcmp(type, "owner", true))
    {
        new otherid;
        if(sscanf(string, "d", otherid))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editgs [id] [owner] [playerid] (use '-1' to no owner/ reset)");
		if(otherid == -1)
			return format(gsData[gsid][gOwner], MAX_PLAYER_NAME, "-");

        format(gsData[gsid][gOwner], MAX_PLAYER_NAME, AccountData[otherid][pName]);
		gsData[gsid][gOwnerID] = AccountData[otherid][pID];

		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE gstations SET owner='%s', ownerid='%d' WHERE ID='%d'", gsData[gsid][gOwner], gsData[gsid][gOwnerID], gsid);
		mysql_tquery(g_SQL, query);

		GStation_Refresh(gsid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the owner of gas station ID: %d to %s", AccountData[playerid][pAdminname], gsid, AccountData[otherid][pName]);
    }
	else if(!strcmp(type, "money", true))
    {
        new money;

        if(sscanf(string, "d", money))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editgs [id] [money] [Ammount]");

        gsData[gsid][gMoney] = money;
		
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE gstations SET money='%d' WHERE ID='%d'", gsData[gsid][gMoney], gsid);
		mysql_tquery(g_SQL, query);

		GStation_Refresh(gsid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the money of bisnis ID: %d to %s.", AccountData[playerid][pAdminname], gsid, FormatMoney(money));
    }
    else if(!strcmp(type, "delete", true))
    {
		Gas_Reset(gsid); 

		if(IsValidDynamicMapIcon(gsData[gsid][MapIconGas]))
        {
            DestroyDynamicMapIcon(gsData[gsid][MapIconGas]);
            gsData[gsid][MapIconGas] = INVALID_STREAMER_ID;
        }
		
		new query[128];
		DestroyDynamic3DTextLabel(gsData[gsid][gsLabel]);
		gsData[gsid][gsPosX] = 0;
		gsData[gsid][gsPosY] = 0;
		gsData[gsid][gsPosY] = 0;
		gsData[gsid][gsStock] = 0;
		gsData[gsid][gPrice] = 0;
		gsData[gsid][gsLabel] = Text3D: INVALID_3DTEXT_ID;
		Iter_Remove(GStation, gsid);
		mysql_format(g_SQL, query, sizeof(query), "DELETE FROM gstations WHERE id=%d", gsid);
		mysql_tquery(g_SQL, query);
        SendAdminMessage(COLOR_RED, "%s has delete gs ID: %d.", AccountData[playerid][pAdminname], gsid);
    }
    return 1;
}

CMD:sellgs(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 3.0, 1487.868408,-1789.390747,-34.880939)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di kantor pemerintah");
	if(GetOwnedGas(playerid) == -1) return Error(playerid, "Anda tidak memiliki Gas Station.");
	new gsid, _tmpstring[128], count = GetOwnedGas(playerid), CMDSString[512];
	CMDSString = "";
	Loop(itt, (count + 1), 1)
	{
	    gsid = ReturnPlayerGasStationID(playerid, itt);

		if(itt == count)
		{
		    format(_tmpstring, sizeof(_tmpstring), ""LB_E"%d.\t{FFFF2A}%s\n", itt, gsData[gsid][gName]);
		}
		else format(_tmpstring, sizeof(_tmpstring), ""LB_E"%d.\t{FFFF2A}%s\n", itt, gsData[gsid][gName]);
		strcat(CMDSString, _tmpstring);
	}
	ShowPlayerDialog(playerid, DIALOG_SELL_GS, DIALOG_STYLE_LIST, "Sell Gas Station", CMDSString, "Sell", "Cancel");
	return 1;
}

CMD:mygs(playerid)
{
	if(GetOwnedGas(playerid) == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki gas station.");
	new gsid, _tmpstring[128], count = GetOwnedGas(playerid), CMDSString[512];
	CMDSString = "";
	Loop(itt, (count + 1), 1)
	{
	    gsid = ReturnPlayerGasStationID(playerid, itt);

		if(itt == count)
		{
		    format(_tmpstring, sizeof(_tmpstring), "%d.\t%s\n", itt, gsData[gsid][gName]);
		}
		else format(_tmpstring, sizeof(_tmpstring), "%d.\t%s\n", itt, gsData[gsid][gName]);
		strcat(CMDSString, _tmpstring);
	}
	ShowPlayerDialog(playerid, DIALOG_MY_GS, DIALOG_STYLE_LIST, ""BLUE_E"Nova Shine "WHITE_E"- Gas Station Saya", CMDSString, "Pilih", "Batal");
	return 1;
}

CMD:gsmenu(playerid, params[])
{
	foreach(new id : GStation)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, gsData[id][gsPosX], gsData[id][gsPosY], gsData[id][gsPosZ]))
		{
			AccountData[playerid][pInGas] = id;
			if(!Player_OwnsGas(playerid, id)) return Error(playerid, "Gas Station ini bukan milik anda!");
			ShowPlayerDialog(playerid, GS_MENU, DIALOG_STYLE_LIST, "Gas Station Manage", "Gas Information\nGas Change Name\nGas Vault\nGas SetPrice\nRestock Gas", "Select", "Cancel");
		}
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CROUCH && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        foreach(new gsid : GStation)
        {
            new carid = GetNearestVehicleToPlayer(playerid, 2.0, false);
            if(IsPlayerInRangeOfPoint(playerid, 1.5, gsData[gsid][gsPosX], gsData[gsid][gsPosY], gsData[gsid][gsPosZ]))
            {
                if(carid != INVALID_VEHICLE_ID)
                {
                    if(!DurringRefill[playerid])
                    {
                        if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                        if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                        if(GetEngineStatus(carid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mematikan mesin!");
                        if(GetFuel(carid) >= 100) return ShowTDN(playerid, NOTIFICATION_WARNING, "Bensin kendaraan ini full!");
                        if(GetPlayerMoney(playerid) < gsData[gsid][gStockPrice])
						    return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");

                        AccountData[playerid][pInGas] = gsid;

                        SendRPMeAboveHead(playerid, "Mengisi bensin", X11_PLUM1);

                        DestroyDynamic3DTextLabel(LabelFuel[playerid]);
                                
                        DurringRefill[playerid] = true;
                        AccountData[playerid][ActivityTime] = 1;
                        AccountData[playerid][pTempVehID] = carid;
                        ShowProgressBensin(playerid);
                        LabelFuel[playerid] = CreateDynamic3DTextLabel("0%", -1, 0.0, 0.0, 1.1, 5.0, INVALID_PLAYER_ID, carid, 1, 0, 0, -1, 5.0, -1, 0);
                        pTimerRefill[playerid] = SetTimerEx("VehicleRefill", 550, true, "dd", playerid, carid);
                    }
                    else 
                    {
                        KillTimer(pTimerRefill[playerid]);
                        pTimerRefill[playerid] = -1;
                        AccountData[playerid][pInGas] = -1;
                        DurringRefill[playerid] = false;
                        HideProgressBensin(playerid);
                        AccountData[playerid][ActivityTime] = 0;

                        DestroyDynamic3DTextLabel(LabelFuel[playerid]);

                        //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                        ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengisi bbm");
                    }
                }    
            }        
        }   
    }
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        foreach(new gsid : GStation)
        {
            if(IsPlayerInRangeOfPoint(playerid, 1.5, gsData[gsid][gsPosX], gsData[gsid][gsPosY], gsData[gsid][gsPosZ]))
            {
                if(AccountData[playerid][pMoney] < 1500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                if(GetTotalWeightFloat(playerid) > 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
                TakeMoney(playerid, 1500);

                Inventory_Add(playerid, "Jerigen", 1650);
                ShowItemBox(playerid, "Recieved 1x", "Jerigen", 1650);
                ShowItemBox(playerid, "Removed $1500", "Uang", 1212);
            }
        }
    }
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pJerigenUse])
        {
            new carid = GetNearestVehicleToPlayer(playerid, 3.5, false);
            if(carid != INVALID_VEHICLE_ID)
            {
                if(!DurringRefill[playerid])
                {
                    if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
                    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
                    if(GetEngineStatus(carid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mematikan mesin!");
                    if(GetFuel(carid) >= 100) return ShowTDN(playerid, NOTIFICATION_WARNING, "Bensin kendaraan ini full!");

                    ApplyAnimationEx(playerid,"CAMERA","camstnd_idleloop", 4.1, 1, 0, 0, 0, 0, 0);
                    SendRPMeAboveHead(playerid, "Mengisi bahan bakar kendaraan didepan", X11_PLUM1);
           
                    DurringRefill[playerid] = true;
                    AccountData[playerid][ActivityTime] = 1;
                    ShowProgressBensin(playerid);
                    pTimerRefill[playerid] = SetTimerEx("VehicleRefillJerigen", 550, true, "dd", playerid, carid);
                }
                else 
                {
                    KillTimer(pTimerRefill[playerid]);
                    pTimerRefill[playerid] = -1;
                    DurringRefill[playerid] = false;
                    AccountData[playerid][pJerigenUse] = false;
                    HideProgressBensin(playerid);
                    AccountData[playerid][ActivityTime] = 0;
                    
                    Inventory_Remove(playerid, "Jerigen");
                    RemovePlayerAttachedObject(playerid, 9);
                    ClearAnimations(playerid, 1);
                    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengisi bbm");
                }
            }
        }
    }
    return 1;
}
forward VehicleRefillJerigen(playerid, vehicleid);
public VehicleRefillJerigen(playerid, vehicleid) 
{
    if(vehicleid == -1) return 0;
    
    new FuelCount = GetFuel(vehicleid);

    if(GetNearestVehicleToPlayer(playerid, 3.0, false) != vehicleid)
    {
        KillTimer(pTimerRefill[playerid]);
        pTimerRefill[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        DurringRefill[playerid] = false;
        AccountData[playerid][pJerigenUse] = false;
        HideProgressBensin(playerid);

        ClearAnimations(playerid, 1);
        RemovePlayerAttachedObject(playerid, 9);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        Error(playerid, "Anda terlalu jauh dari kendaraan");
        AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        return 0;
    }

    if(vehicleid == AccountData[playerid][pTempVehID])
    {        
        FuelCount ++;
        static Float: progressvalue;
        progressvalue = FuelCount*-119/100;
        PlayerTextDrawTextSize(playerid, BensinKirp[playerid][1], 21.000000, progressvalue);
        PlayerTextDrawShow(playerid, BensinKirp[playerid][1]);

        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        VehicleCore[AccountData[playerid][pTempVehID]][vCoreFuel] += 1;

        if(FuelCount >= 100)
        {
            DurringRefill[playerid] = false;
            KillTimer(pTimerRefill[playerid]);
            pTimerRefill[playerid] = -1;
            AccountData[playerid][pJerigenUse] = false;
            AccountData[playerid][ActivityTime] = 0;
            HideProgressBensin(playerid);

            ClearAnimations(playerid, 1);
            RemovePlayerAttachedObject(playerid, 9);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengisi bbm");
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        }
    }
    return 1;
}

forward VehicleRefill(playerid, vehicleid);
public VehicleRefill(playerid, vehicleid)
{
    if(vehicleid == -1) return 0;
    
    new FuelCount = GetFuel(vehicleid);

    if(GetNearestVehicleToPlayer(playerid, 3.0, false) != vehicleid)
    {
        KillTimer(pTimerRefill[playerid]);
        pTimerRefill[playerid] = -1;
        DurringRefill[playerid] = false;
        HideProgressBensin(playerid);
        AccountData[playerid][ActivityTime] = 0;

        //ClearAnimations(playerid, 1);
        //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        Error(playerid, "Anda terlalu jauh dari kendaraan");
        AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        return 0;
    }

    if(AccountData[playerid][pTempVehID] == vehicleid)
    {
        if(FuelCount >= 100)
        {
            DestroyDynamic3DTextLabel(LabelFuel[playerid]);

            new gsid = AccountData[playerid][pInGas];
            if(gsid != -1 && Iter_Contains(GStation, gsid))
            {
                new stockPrice = gsData[gsid][gStockPrice];
				new cost = FuelCount * stockPrice;

                if(gsData[gsid][gsStock] < FuelCount)
                {
                    Info(playerid, "Gas station kehabisan stok bensin.");
                    DestroyDynamic3DTextLabel(LabelFuel[playerid]);
                    KillTimer(pTimerRefill[playerid]);
                    pTimerRefill[playerid] = -1;
                    DurringRefill[playerid] = false;
                    HideProgressBensin(playerid);
                    AccountData[playerid][ActivityTime] = 0;
                    return 1;
                }
                gsData[gsid][gMoney] += cost;                                
				GStation_Refresh(gsid); 
            }
            KillTimer(pTimerRefill[playerid]);
            pTimerRefill[playerid] = -1;
            DurringRefill[playerid] = false;
            HideProgressBensin(playerid);
            AccountData[playerid][ActivityTime] = 0;

            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengisi bbm");
            AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
        }
        else if(FuelCount < 100)
        {
            new gsid = AccountData[playerid][pInGas];
			new hargaPerLiter = 1000;

            if(gsid != -1 && Iter_Contains(GStation, gsid))
            {
                hargaPerLiter = gsData[gsid][gStockPrice];
				if(gsData[gsid][gsStock] <= 0)
                {
                    Info(playerid, "Stok bensin di SPBU ini telah habis.");
                    KillTimer(pTimerRefill[playerid]);
                    pTimerRefill[playerid] = -1;
                    DurringRefill[playerid] = false;
                    HideProgressBensin(playerid);
                    AccountData[playerid][ActivityTime] = 0;
                    DestroyDynamic3DTextLabel(LabelFuel[playerid]);
                    GStation_Refresh(gsid); 
                }
            }
            if(GetPlayerMoney(playerid) >= hargaPerLiter)
            {
                FuelCount ++;
                if(gsid != -1 && Iter_Contains(GStation, gsid))
					gsData[gsid][gsStock]--;

                static Float: progressvalue;
                progressvalue = FuelCount*-119/100;
                PlayerTextDrawTextSize(playerid, BensinKirp[playerid][1], 21.000000, progressvalue);
                PlayerTextDrawShow(playerid, BensinKirp[playerid][1]);

                PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
                TakeMoney(playerid, hargaPerLiter);
                VehicleCore[AccountData[playerid][pTempVehID]][vCoreFuel] += 1;
                UpdateDynamic3DTextLabelText(LabelFuel[playerid], COLOR_WHITE, sprintf("%d%", FuelCount));
            }
            else
            {
                Info(playerid, "Uang kamu tidak cukup. Bensin berhasil diisi sebanyak %d liter.", FuelCount);
                KillTimer(pTimerRefill[playerid]);
                pTimerRefill[playerid] = -1;
                DurringRefill[playerid] = false;
                HideProgressBensin(playerid);
                AccountData[playerid][ActivityTime] = 0;
                DestroyDynamic3DTextLabel(LabelFuel[playerid]);
                GStation_Refresh(gsid); 
            }
        }
        else
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda gagal mengisi bahan bakar kendaraan");
            KillTimer(pTimerRefill[playerid]);
            GivePlayerMoney(playerid, FuelCount*10000);
            pTimerRefill[playerid] = -1;
            DurringRefill[playerid] = false;
            HideProgressBensin(playerid);
            AccountData[playerid][ActivityTime] = 0;
            DestroyDynamic3DTextLabel(LabelFuel[playerid]);
        }
    }
    return 1;
}

Player_GasCount(playerid)
{
	#if LIMIT_PER_PLAYER != 0
    new count;
	foreach(new i : GStation)
	{
		if(Player_OwnsGas(playerid, i)) count++;
	}

	return count;
	#else
	return 0;
	#endif
}

stock ShowProgressBensin(playerid)
{
    PlayerTextDrawTextSize(playerid, BensinKirp[playerid][1], 21.0, 0);

	PlayerTextDrawShow(playerid, BensinKirp[playerid][0]);
	PlayerTextDrawShow(playerid, BensinKirp[playerid][1]);
	PlayerTextDrawShow(playerid, BensinKirp[playerid][2]);
	PlayerTextDrawShow(playerid, BensinKirp[playerid][3]);
    return 1;
}

HideProgressBensin(playerid)
{
    for(new i = 0; i < 4; i++)
    {
        PlayerTextDrawHide(playerid, BensinKirp[playerid][i]);
    }
    return 1;
}
