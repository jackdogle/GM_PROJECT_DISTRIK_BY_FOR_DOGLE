#include <YSI\y_hooks>
#define MAX_DYNAMIC_GATE (1000)

enum e_gatedata
{
    gateModel,
    gateFaction,
    gPass[36],
    gateFamily,
    gateOwnerID,
    Float:gateSpeed,
    Float:gateclosePos[3],
    Float:gatecloseRot[3],
    Float:gateopenPos[3],
    Float:gateopenRot[3],
    bool: gateStatus,
    STREAMER_TAG_OBJECT:gateObjectID,
    STREAMER_TAG_AREA:gateArea
};
new GateData[MAX_DYNAMIC_GATE][e_gatedata],
    Iterator:Gate<MAX_DYNAMIC_GATE>;

new Float:GatePosition[MAX_PLAYERS][3],
    Float:GateRotation[MAX_PLAYERS][3];

GateSave(id)
{
    new query[2012];
    mysql_format(g_SQL, query, sizeof(query), "UPDATE `gate` SET `Model`=%d, password='%s', `Faction`=%d, `Family`=%d, `Owner`=%d, `Speed`=%f, `cX`=%f, `cY`=%f, `cZ`=%f, `cRX`=%f, `cRY`=%f, `cRZ`=%f,\
    `oX`=%f, `oY`=%f, `oZ`=%f, `oRX`=%f, `oRY`=%f, `oRZ`=%f WHERE `ID`=%d", GateData[id][gateModel], GateData[id][gPass], GateData[id][gateFaction], GateData[id][gateFamily], GateData[id][gateOwnerID], GateData[id][gateSpeed], GateData[id][gateclosePos][0], GateData[id][gateclosePos][1], GateData[id][gateclosePos][2], GateData[id][gatecloseRot][0], GateData[id][gatecloseRot][1], GateData[id][gatecloseRot][2],
    GateData[id][gateopenPos][0], GateData[id][gateopenPos][1], GateData[id][gateopenPos][2], GateData[id][gateopenRot][0], GateData[id][gateopenRot][1], GateData[id][gateopenRot][2], id);
    mysql_tquery(g_SQL, query);
    return 1;
}

Gate_Rebuild(id)
{
    if(id != -1)
    {
        if(DestroyDynamicObject(GateData[id][gateObjectID]))
            GateData[id][gateObjectID] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        if(DestroyDynamicArea(GateData[id][gateArea]))
            GateData[id][gateArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        
        if(GateData[id][gateclosePos][0] != 0.0 || GateData[id][gateopenPos][0] != 0.0)
        {
            GateData[id][gateObjectID] = CreateDynamicObject(GateData[id][gateModel], GateData[id][gateclosePos][0], GateData[id][gateclosePos][1], GateData[id][gateclosePos][2], GateData[id][gatecloseRot][0], GateData[id][gatecloseRot][1], GateData[id][gatecloseRot][2], -1, -1, -1, 50.0, 50.0);
            GateData[id][gateArea] = CreateDynamicSphere(GateData[id][gateclosePos][0], GateData[id][gateclosePos][1], GateData[id][gateclosePos][2], 8.5, -1, -1, -1);
        }
    }
    return 1;
}
forward LoadGate();
public LoadGate()
{
    new rows;
    cache_get_row_count(rows);
    new Cache:Gatecache;
    if(rows)
    {
        new id, x = 0, password[36];
        Gatecache = cache_save();
        while(x < rows)
        {
            cache_get_value_name_int(x, "ID", id);
            cache_get_value_name_int(x, "Model", GateData[id][gateModel]);
            cache_get_value_name(x, "password", password);
			format(GateData[id][gPass], 36, password);
            cache_get_value_name_int(x, "Faction", GateData[id][gateFaction]);
            cache_get_value_name_int(x, "Family", GateData[id][gateFamily]);
            cache_get_value_name_int(x, "Owner", GateData[id][gateOwnerID]);
            
            cache_get_value_name_float(x, "Speed", GateData[id][gateSpeed]);
            cache_get_value_name_float(x, "cX", GateData[id][gateclosePos][0]);
            cache_get_value_name_float(x, "cY", GateData[id][gateclosePos][1]);
            cache_get_value_name_float(x, "cZ", GateData[id][gateclosePos][2]);
            cache_get_value_name_float(x, "cRX", GateData[id][gatecloseRot][0]);
            cache_get_value_name_float(x, "cRY", GateData[id][gatecloseRot][1]);
            cache_get_value_name_float(x, "cRZ", GateData[id][gatecloseRot][2]);
            
            cache_get_value_name_float(x, "oX", GateData[id][gateopenPos][0]);
            cache_get_value_name_float(x, "oY", GateData[id][gateopenPos][1]);
            cache_get_value_name_float(x, "oZ", GateData[id][gateopenPos][2]);
            cache_get_value_name_float(x, "oRX", GateData[id][gateopenRot][0]);
            cache_get_value_name_float(x, "oRY", GateData[id][gateopenRot][1]);
            cache_get_value_name_float(x, "oRZ", GateData[id][gateopenRot][2]);
            
            Iter_Add(Gate, id);
            Gate_Rebuild(id);
            GateData[id][gateStatus] = false;
            GateData[id][gateArea] = CreateDynamicSphere(GateData[id][gateclosePos][0], GateData[id][gateclosePos][1], GateData[id][gateclosePos][2], 5.0, -1, -1, -1);
            x++;
        }
        printf("[Dynamic Gate]: Jumlah total Gate yang dimuat %d", rows);

        if(cache_is_valid(Gatecache))
        {
            cache_delete(Gatecache);
            printf("[Dynamic Gate]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Gate]: Cache tidak valid atau sudah dihapus.");
        }
    }
}

CMD:addgate(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    new object, id = Iter_Free(Gate);
    if(id == -1) return Error(playerid, "Anda tidak dapat menambah Dynamic gate lagi!");
    if(sscanf(params, "i", object)) return Syntax(playerid, "/addgate [model id]");

    GetPlayerPos(playerid, GateData[id][gateclosePos][0], GateData[id][gateclosePos][1], GateData[id][gateclosePos][2]);
    GateData[id][gateModel] = object;
    GateData[id][gateclosePos][0] = GateData[id][gateclosePos][0] + 2;
    GateData[id][gateclosePos][1] = GateData[id][gateclosePos][1] + 2;
    GateData[id][gatecloseRot][0] = 0;
    GateData[id][gatecloseRot][1] = 0;
    GateData[id][gatecloseRot][2] = 0;
    GetPlayerPos(playerid, GateData[id][gateopenPos][0], GateData[id][gateopenPos][1], GateData[id][gateopenPos][2]);
    GateData[id][gateopenPos][0] = GateData[id][gateopenPos][0] + 2;
    GateData[id][gateopenPos][1] = GateData[id][gateopenPos][1] + 2;
    GateData[id][gateopenRot][0] = 0;
    GateData[id][gateopenRot][1] = 0;
    GateData[id][gateopenRot][2] = 0;
    GateData[id][gateStatus] = false;
    GateData[id][gateFaction] = 0;
    GateData[id][gateFamily] = -1;
    GateData[id][gateOwnerID] = -1;
    format(GateData[id][gPass], 36, "");
    GateData[id][gateSpeed] = 2.0;

    Gate_Rebuild(id);
    Iter_Add(Gate, id);
    Info(playerid, "Anda membuat Dynamic Gate ID %d", id);

    new query[555];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `gate` SET ID=%d, `model`=%d, `cX`=%f, `cY`=%f, `cZ`=%f, `cRX`=%f, `cRY`=%f, `cRZ`=%f, `oX`=%f, `oY`=%f, `oZ`=%f, `oRX`=%f, `oRY`=%f, `oRZ`=%f",
    id, GateData[id][gateModel], GateData[id][gateclosePos][0], GateData[id][gateclosePos][1], GateData[id][gateclosePos][2], GateData[id][gatecloseRot][0], GateData[id][gatecloseRot][1], GateData[id][gatecloseRot][2], GateData[id][gateopenPos][0], GateData[id][gateopenPos][1], GateData[id][gateopenPos][2], GateData[id][gateopenRot][0], GateData[id][gateopenRot][1], GateData[id][gateopenRot][2]);
    mysql_tquery(g_SQL, query, "OnGatesCreated", "d", id);
    return 1;
}

FUNC::OnGatesCreated(id)
{
    GateSave(id);
    return 1;
}

CMD:gotogate(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1) return PermissionError(playerid);

    new id;
    if(id < 0 || id >= MAX_DYNAMIC_GATE) return Error(playerid, "ID Gate tidak valid!");
    if(sscanf(params, "i", id)) return Syntax(playerid, "/gotogate [id]");
    if(!Iter_Contains(Gate, id)) return Error(playerid, "ID Gate tidak ada!");
    
    SetPlayerPos(playerid, GateData[id][gateclosePos][0], GateData[id][gateclosePos][1], GateData[id][gateclosePos][2]);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    Info(playerid, "Anda teleportasi ke Dynamic Gate ID %d", id);
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInBiz] = -1;
    return 1;
}

CMD:editgate(playerid, params[])
{
    static
        id,
        option[24],
        nextParams[128];
    
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[125]", id, option, nextParams))
    {
        Syntax(playerid, "/editgate [id] [name] (model, faction, family, owner, close, open, speed, password)");
        return 1;
    }
    if(id < 0 || id >= MAX_DYNAMIC_GATE) return Error(playerid, "ID Gate tidak valid!");
    if(!Iter_Contains(Gate, id)) return Error(playerid, "ID Gate tidak ada!");

    if(!strcmp(option, "model", true))
    {
        new obj;
        if(sscanf(nextParams, "d", obj)) return Syntax(playerid, "/editgate [id] [model] [model id]");

        GateData[id][gateModel] = obj;
        Gate_Rebuild(id);
        GateSave(id);
        Info(playerid, "Anda mengubah Model Dynamic Gate ID %d menjadi Object Model %d", id, obj);
    }
    else if(!strcmp(option, "faction", true))
    {
        new fid;
        if(sscanf(nextParams, "d", fid)) return Syntax(playerid, "/editgate [id] [faction] [faction id] (1.Kepolisian 2.Pemerintahan 3.EMS 4.Trans 5.Bengkel 6.Pedagang)");
        if(fid < 0 || fid > 6) return Error(playerid, "ID Faction tidak valid!");

        GateData[id][gateFaction] = fid;
        GateSave(id);
        Info(playerid, "Anda menetapkan Dynamic Gate ID %d untuk Faction ID %d", id, fid);
    }
    else if(!strcmp(option, "family", true))
    {
        new fid;
        if(sscanf(nextParams, "d", fid)) return Syntax(playerid, "/editgate [id] [faction] [family id]");
        if(fid < -1) return Error(playerid, "ID Faction tidak valid!");

        GateData[id][gateFamily] = fid;
        GateSave(id);
        Info(playerid, "Anda menetapkan Dynamic Gate ID %d untuk Family ID %d", id, fid);
    }
    else if(!strcmp(option, "owner", true))
    {
        new otherid;
        if(sscanf(nextParams, "u", otherid)) return Syntax(playerid, "/editgate [id] [owner] [name/playerid] (Kembalikan ke -1 untuk menghapus owner)");
        if(!IsPlayerConnected(otherid)) return Error(playerid, "Pemain tersebut tidak terkoneksi ke server!");

        GateData[id][gateOwnerID] = AccountData[otherid][pID];
        GateSave(id);
        Info(playerid, "Anda menetapkan Dynamic Gate ID %d menjadi Milik %s(%d)", id, AccountData[otherid][pName], otherid);
    }
    else if(!strcmp(option, "speed", true))
    {
        new Float:speed;

        if(sscanf(nextParams, "f", speed)) return Syntax(playerid, "/editgate [id] [speed] [speed]");

        GateData[id][gateSpeed] = speed;
        GateSave(id);
        Info(playerid, "Anda menetapkan Dynamic Gate ID %d dengan Speed %.1f", id, speed);
    }
    else if(!strcmp(option, "close", true))
    {
        AccountData[playerid][gEdit] = 1;
        AccountData[playerid][gEditID] = id;
        GetDynamicObjectPos(GateData[id][gateObjectID], GatePosition[playerid][0], GatePosition[playerid][1], GatePosition[playerid][2]);
		GetDynamicObjectRot(GateData[id][gateObjectID], GateRotation[playerid][0], GateRotation[playerid][1], GateRotation[playerid][2]);
		EditDynamicObject(playerid, GateData[id][gateObjectID]);
        Info(playerid, "Anda sekarang mengedit Posisi tertutup Dynamic Gate ID %d", id);
        GateSave(id);
    }
    else if(!strcmp(option, "open", true))
    {
        AccountData[playerid][gEdit] = 2;
        AccountData[playerid][gEditID] = id;
        GetDynamicObjectPos(GateData[id][gateObjectID], GatePosition[playerid][0], GatePosition[playerid][1], GatePosition[playerid][2]);
		GetDynamicObjectRot(GateData[id][gateObjectID], GateRotation[playerid][0], GateRotation[playerid][1], GateRotation[playerid][2]);
		EditDynamicObject(playerid, GateData[id][gateObjectID]);
        Info(playerid, "Anda sekarang mengedit Posisi terbuka Dynamic Gate ID %d", id);
        GateSave(id);
    }
    else if(!strcmp(option, "delete", true))
    {
        GateData[id][gateModel] = 0;
        GateData[id][gateclosePos][0] = GateData[id][gateclosePos][1] = GateData[id][gateclosePos][2] = 0;
        GateData[id][gatecloseRot][0] = GateData[id][gatecloseRot][1] = GateData[id][gatecloseRot][2] = 0;
        GateData[id][gateopenPos][0] = GateData[id][gateopenPos][1] = GateData[id][gateopenPos][2] = 0;
        GateData[id][gateopenRot][0] = GateData[id][gateopenRot][1] = GateData[id][gateopenRot][2] = 0;
        GateData[id][gateStatus] = false;
        format(GateData[id][gPass], 36, "");
        GateData[id][gateSpeed] = 0;

        Gate_Rebuild(id);
        Iter_Remove(Gate, id);
        Info(playerid, "Anda menghapus Dynamic Gate ID %d", id);

        new query[125];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `gate` WHERE `ID`=%d", id);
        mysql_tquery(g_SQL, query);
    }
    else if(!strcmp(option, "password", true))
    {
		new password[36];

        if(sscanf(nextParams, "s[36]", password))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editgate [id] [password] [gate pass] (use 'none' to disable)");

        if(!strcmp(password, "none", true)) {
            format(GateData[id][gPass], 36, "");
        }
        else {
            format(GateData[id][gPass], 36, password);
        }
        GateSave(id);
        Info(playerid, "You has adjusted the password of gate ID: %d to %s", id, password);
	}
    return 1;
}

CMD:gate(playerid, params[])
{
    if(!AccountData[playerid][pSpawned]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum spawn!");
    foreach(new id : Gate)
    {
        if(GateData[id][gateModel] && IsPlayerInDynamicArea(playerid, GateData[id][gateArea]))
        {
            if(GateData[id][gateFaction] > FACTION_NONE)
            {
                if(GateData[id][gateFaction] != AccountData[playerid][pFaction]) return Error(playerid, "Gerbang ini khusus salah satu anggota Faction!");
            }
            if(GateData[id][gateFamily] > -1)
            {
                if(GateData[id][gateFamily] != AccountData[playerid][pFamily]) return Error(playerid, "Gerbang ini khusus salah satu anggota Family!");
            }
            if(GateData[id][gateOwnerID] > -1)
            {
                if(GateData[id][gateOwnerID] != AccountData[playerid][pID]) return Error(playerid, "Gerbang ini bukan milik anda!");
            }
            if(strlen(GateData[id][gPass]))
	        {
	            if(sscanf(params, "s[36]", params)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gate [password]");
	            if(strcmp(params, GateData[id][gPass])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid gate password.");
	            if(!GateData[id][gateStatus])
		        {
		            GateData[id][gateStatus] = true;
		            MoveDynamicObject(GateData[id][gateObjectID], GateData[id][gateopenPos][0], GateData[id][gateopenPos][1], GateData[id][gateopenPos][2], GateData[id][gateSpeed]);
		            SetDynamicObjectRot(GateData[id][gateObjectID], GateData[id][gateopenRot][0], GateData[id][gateopenRot][1], GateData[id][gateopenRot][2]);
		        }
		        else
		        {
		            GateData[id][gateStatus] = false;
		            MoveDynamicObject(GateData[id][gateObjectID], GateData[id][gateclosePos][0], GateData[id][gateclosePos][1], GateData[id][gateclosePos][2], GateData[id][gateSpeed]);
		            SetDynamicObjectRot(GateData[id][gateObjectID], GateData[id][gatecloseRot][0], GateData[id][gatecloseRot][1], GateData[id][gatecloseRot][2]);
		        }
	        }
            else
            {
                if(!GateData[id][gateStatus])
                {
                    GateData[id][gateStatus] = true;
                    MoveDynamicObject(GateData[id][gateObjectID], GateData[id][gateopenPos][0], GateData[id][gateopenPos][1], GateData[id][gateopenPos][2], GateData[id][gateSpeed]);
                    SetDynamicObjectRot(GateData[id][gateObjectID], GateData[id][gateopenRot][0], GateData[id][gateopenRot][1], GateData[id][gateopenRot][2]);
                }
                else
                {
                    GateData[id][gateStatus] = false;
                    MoveDynamicObject(GateData[id][gateObjectID], GateData[id][gateclosePos][0], GateData[id][gateclosePos][1], GateData[id][gateclosePos][2], GateData[id][gateSpeed]);
                    SetDynamicObjectRot(GateData[id][gateObjectID], GateData[id][gatecloseRot][0], GateData[id][gatecloseRot][1], GateData[id][gatecloseRot][2]);
                }
            }
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if((newkeys & KEY_CROUCH))
    {
        foreach(new id : Gate)
        {
            if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsPlayerInAnyVehicle(playerid))
            {
                if(GateData[id][gateModel] && IsPlayerInDynamicArea(playerid, GateData[id][gateArea]))
                {
                    callcmd::gate(playerid, "");   
                }
            }
        }
    }
    return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    if(AccountData[playerid][gEditID] != -1 && Iter_Contains(Gate, AccountData[playerid][gEditID]))
	{
		new id = AccountData[playerid][gEditID];
		if(response == EDIT_RESPONSE_UPDATE)
		{
			SetDynamicObjectPos(objectid, x, y, z);
			SetDynamicObjectRot(objectid, rx, ry, rz);
		}
		else if(response == EDIT_RESPONSE_CANCEL)
		{
			SetDynamicObjectPos(objectid, GatePosition[playerid][0], GatePosition[playerid][1], GatePosition[playerid][2]);
			SetDynamicObjectRot(objectid, GateRotation[playerid][0], GateRotation[playerid][1], GateRotation[playerid][2]);
			GatePosition[playerid][0] = 0; GatePosition[playerid][1] = 0; GatePosition[playerid][2] = 0;
			GateRotation[playerid][0] = 0; GateRotation[playerid][1] = 0; GateRotation[playerid][2] = 0;
			Info(playerid, "Kamu membatalkan pengeditan gate id %d", id);
			GateSave(id);
		}
		else if(response == EDIT_RESPONSE_FINAL)
		{
			SetDynamicObjectPos(objectid, x, y, z);
			SetDynamicObjectRot(objectid, rx, ry, rz);
			if(AccountData[playerid][gEdit] == 1)
			{
				GateData[id][gateclosePos][0] = x;
				GateData[id][gateclosePos][1] = y;
				GateData[id][gateclosePos][2] = z;
				GateData[id][gatecloseRot][0] = rx;
				GateData[id][gatecloseRot][1] = ry;
				GateData[id][gatecloseRot][2] = rz;
				
				AccountData[playerid][gEditID] = -1;
				AccountData[playerid][gEdit] = 0;
				Info(playerid, "Berhasil mengedit posisi tertutup Gate ID: %d", id);
				GateData[id][gateStatus] = false;
                Gate_Rebuild(id);
				GateSave(id);
			}
			else if(AccountData[playerid][gEdit] == 2)
			{
				GateData[id][gateopenPos][0] = x;
				GateData[id][gateopenPos][1] = y;
				GateData[id][gateopenPos][2] = z;
				GateData[id][gateopenRot][0] = rx;
				GateData[id][gateopenRot][1] = ry;
				GateData[id][gateopenRot][2] = rz;
				
				AccountData[playerid][gEditID] = -1;
				AccountData[playerid][gEdit] = 0;
				Info(playerid, "Berhasil mengedit posisi terbuka Gate ID: %d", id);
				GateData[id][gateStatus] = false;
                Gate_Rebuild(id);
				GateSave(id);
			}
		}
    }
    return 1;
}