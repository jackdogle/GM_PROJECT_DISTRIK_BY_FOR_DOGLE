CMD:addgarkot(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);
    
    new id = Iter_Free(PublicGarage), name[64], type[16];
    static Float:x, Float:y, Float:z;

    if(id == -1) 
        return Error(playerid, "Tidak dapat menambah garkot di server lagi!");
    
    if(sscanf(params, "s[16]s[64]", type, name)) 
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addgarkot [udara/darat] [nama garkot]");
    
    if(strlen(name) < 5) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 5 karakter!");

    // Simpan posisi
    GetPlayerPos(playerid, x, y, z);
    PublicGarage[id][pgInterior] = GetPlayerInterior(playerid);
    PublicGarage[id][pgWorld] = GetPlayerVirtualWorld(playerid);
    format(PublicGarage[id][pgName], 64, name);

    if(!strcmp(type, "darat", true))
    {
        PublicGarage[id][pgPOS][0] = x;
        PublicGarage[id][pgPOS][1] = y;
        PublicGarage[id][pgPOS][2] = z;

        // spawnpos default
        PublicGarage[id][pgSpawnPOS][0] = x + 3.0;
        PublicGarage[id][pgSpawnPOS][1] = y;
        PublicGarage[id][pgSpawnPOS][2] = z;
        GetPlayerFacingAngle(playerid, PublicGarage[id][pgSpawnPOS][3]);
    }
    else if(!strcmp(type, "udara", true))
    {
        PublicGarage[id][pgUdaraPos][0] = x;
        PublicGarage[id][pgUdaraPos][1] = y;
        PublicGarage[id][pgUdaraPos][2] = z;

        // spawnpos default udara
        PublicGarage[id][pgUdaraSpawn][0] = x + 5.0;
        PublicGarage[id][pgUdaraSpawn][1] = y;
        PublicGarage[id][pgUdaraSpawn][2] = z + 5.0;
        GetPlayerFacingAngle(playerid, PublicGarage[id][pgUdaraSpawn][3]);
    }
    else
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tipe harus 'udara' atau 'darat'.");

    RefreshPublicGarage(id);
    Iter_Add(PublicGarage, id);
    new cQuery[512];
    if(!strcmp(type, "darat", true))
    {
        mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO public_garage SET pgID=%d, pgName='%s', pgPosX=%f, pgPosY=%f, pgPosZ=%f, pgSpawnX=%f, pgSpawnY=%f, pgSpawnZ=%f, pgInterior=%d, pgWorld=%d",id, PublicGarage[id][pgName], PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2],PublicGarage[id][pgSpawnPOS][0], PublicGarage[id][pgSpawnPOS][1], PublicGarage[id][pgSpawnPOS][2],PublicGarage[id][pgInterior], PublicGarage[id][pgWorld]);
    }
    else
    {
        mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO public_garage SET pgID=%d, pgName='%s', udaraPosX=%f, udaraPosY=%f, udaraPosZ=%f, udaraSpawnX=%f, udaraSpawnY=%f, udaraSpawnZ=%f, pgInterior=%d, pgWorld=%d",id, PublicGarage[id][pgName], PublicGarage[id][pgUdaraPos][0], PublicGarage[id][pgUdaraPos][1], PublicGarage[id][pgUdaraPos][2],PublicGarage[id][pgUdaraSpawn][0], PublicGarage[id][pgUdaraSpawn][1], PublicGarage[id][pgUdaraSpawn][2],PublicGarage[id][pgInterior], PublicGarage[id][pgWorld]);
    }
    mysql_tquery(g_SQL, cQuery, "OnPublicGarageAdded", "dd", playerid, id);
    return 1;
}

CMD:editgarkot(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    static 
        did,
        type[24],
        string[125];
    
    if(sscanf(params, "ds[24]S()[128]", did, type, string))
    {
        ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editgarkot [id] [entity]~n~location, spawnpos, udaralocation, udarapos, name, delete");
        return 1;
    }
    if((did < 0 || did >= MAX_PUBLIC_GARAGE)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Garkot tidak valid!");
    if(!Iter_Contains(PublicGarage, did)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Garkot tidak ada!");

    if(!strcmp(type, "location", true))
    {
        static Float:X, Float:Y, Float:Z;
        GetPlayerPos(playerid, X, Y, Z);

        PublicGarage[did][pgPOS][0] = X;
        PublicGarage[did][pgPOS][1] = Y;
        PublicGarage[did][pgPOS][2] = Z;
        PublicGarage[did][pgInterior] = GetPlayerInterior(playerid);
        PublicGarage[did][pgWorld] = GetPlayerVirtualWorld(playerid);

        RefreshPublicGarage(did);
        PublicGarage_Save(did);
    }
    else if(!strcmp(type, "spawnpos", true))
    {
        if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            GetVehiclePos(GetPlayerVehicleID(playerid), PublicGarage[did][pgSpawnPOS][0], PublicGarage[did][pgSpawnPOS][1], PublicGarage[did][pgSpawnPOS][2]);
            GetVehicleZAngle(GetPlayerVehicleID(playerid), PublicGarage[did][pgSpawnPOS][3]);
        }
        else
        {
            GetPlayerPos(playerid, PublicGarage[did][pgSpawnPOS][0], PublicGarage[did][pgSpawnPOS][1], PublicGarage[did][pgSpawnPOS][2]);
            GetPlayerFacingAngle(playerid, PublicGarage[did][pgSpawnPOS][3]);
        }
        RefreshPublicGarage(did);
        PublicGarage_Save(did);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan spawn pos darat Garkot %s ID %d", AccountData[playerid][pAdminname], PublicGarage[did][pgName], did);
    }
    else if(!strcmp(type, "udaralocation", true))
    {
        static Float:X, Float:Y, Float:Z;
        GetPlayerPos(playerid, X, Y, Z);

        PublicGarage[did][pgUdaraPos][0] = X;
        PublicGarage[did][pgUdaraPos][1] = Y;
        PublicGarage[did][pgUdaraPos][2] = Z;
        PublicGarage[did][pgInterior] = GetPlayerInterior(playerid);
        PublicGarage[did][pgWorld] = GetPlayerVirtualWorld(playerid);

        RefreshPublicGarage(did);
        PublicGarage_Save(did);
    }
    else if(!strcmp(type, "udarapos", true))
    {
        if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            GetVehiclePos(GetPlayerVehicleID(playerid), PublicGarage[did][pgUdaraSpawn][0], PublicGarage[did][pgUdaraSpawn][1], PublicGarage[did][pgUdaraSpawn][2]);
            GetVehicleZAngle(GetPlayerVehicleID(playerid), PublicGarage[did][pgUdaraSpawn][3]);
        }
        else
        {
            GetPlayerPos(playerid, PublicGarage[did][pgUdaraSpawn][0], PublicGarage[did][pgUdaraSpawn][1], PublicGarage[did][pgUdaraSpawn][2]);
            GetPlayerFacingAngle(playerid, PublicGarage[did][pgUdaraSpawn][3]);
        }
        RefreshPublicGarage(did);
        PublicGarage_Save(did);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan spawn pos udara Garkot %s ID %d", AccountData[playerid][pAdminname], PublicGarage[did][pgName], did);
    }
    else if(!strcmp(type, "name", true))
    {
        new frmtname[65];
        if(sscanf(string, "s[65]", frmtname)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editgarkot [id] [name] [garkot name]");

        format(PublicGarage[did][pgName], sizeof(frmtname), frmtname);
        RefreshPublicGarage(did);
        PublicGarage_Save(did);
    }
    else if(!strcmp(type, "delete", true))
    {
        if(IsValidDynamicObject(PublicGarage[did][pgObject])) 
        {
            DestroyDynamicObject(PublicGarage[did][pgObject]);
            PublicGarage[did][pgObject] = INVALID_STREAMER_ID;
        }

        if(IsValidDynamicArea(PublicGarage[did][pgArea]))
        {
            DestroyDynamicArea(PublicGarage[did][pgArea]);
            PublicGarage[did][pgArea] = INVALID_STREAMER_ID;
        }

        if(IsValidDynamicMapIcon(PublicGarage[did][pgIcon]))
        {
            DestroyDynamicMapIcon(PublicGarage[did][pgIcon]);
            PublicGarage[did][pgIcon] = INVALID_STREAMER_ID;
        }

        format(PublicGarage[did][pgName], 32, "N/A");
        PublicGarage[did][pgInterior] = PublicGarage[did][pgWorld] = 0;

        PublicGarage[did][pgPOS][0] = PublicGarage[did][pgPOS][1] = PublicGarage[did][pgPOS][2] = 0.0;
        PublicGarage[did][pgSpawnPOS][0] = PublicGarage[did][pgSpawnPOS][1] = PublicGarage[did][pgSpawnPOS][2] = 0.0;
        PublicGarage[did][pgUdaraPos][0] = PublicGarage[did][pgUdaraPos][1] = PublicGarage[did][pgUdaraPos][2] = 0.0;
        PublicGarage[did][pgUdaraSpawn][0] = PublicGarage[did][pgUdaraSpawn][1] = PublicGarage[did][pgUdaraSpawn][2] = 0.0;

        Iter_Remove(PublicGarage, did);
        RefreshPublicGarage(did);
        Info(playerid, "Anda menghapus Dynamic Garkot ID %d", did);

        new query[125];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM public_garage WHERE pgID=%d", did);
        mysql_tquery(g_SQL, query); 
    }
    return 1;
}

CMD:gotogarkot(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;

    if(AccountData[playerid][pAdmin] < 1) return PermissionError(playerid);

    new id, type[16];
    if(sscanf(params, "ds[16]", id, type))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotogarkot [id] [darat/udara]");

    if(!Iter_Contains(PublicGarage, id))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Garkot tidak ditemukan");

    if(!strcmp(type, "darat", true))
    {
        SetPlayerPos(playerid, PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2]);
    }
    else if(!strcmp(type, "udara", true))
    {
        SetPlayerPos(playerid, PublicGarage[id][pgUdaraPos][0], PublicGarage[id][pgUdaraPos][1], PublicGarage[id][pgUdaraPos][2]);
    }
    else
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tipe harus 'darat' atau 'udara'.");
    }

    SetPlayerInterior(playerid, PublicGarage[id][pgInterior]);
    SetPlayerVirtualWorld(playerid, PublicGarage[id][pgWorld]);

    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;

    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" teleportasi ke Public Garage ID: "YELLOW"%d - %s (%s).", 
        GetAdminName(playerid), id, PublicGarage[id][pgName], type);

    return 1;
}