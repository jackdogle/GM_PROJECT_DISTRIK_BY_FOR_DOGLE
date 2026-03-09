#include <YSI\y_hooks>
#define MAX_PUBLIC_GARAGE   (150)

enum e_publicgarage
{
    pgName[64],
    Float:pgPOS[3],
    Float:pgSpawnPOS[4],

    pgInterior,
    pgWorld,

    pgArea,
    pgObject,
    pgIcon
}
new PublicGarage[MAX_PUBLIC_GARAGE][e_publicgarage],
    Iterator:PublicGarage<MAX_PUBLIC_GARAGE>;
    
GarkotNearby(playerid)
{
    for(new i = 0; i < MAX_PUBLIC_GARAGE; i ++)
    {
        if(Iter_Contains(PublicGarage, i))
        {
            new Float:X, Float:Y, Float:Z, Float:dist;
            GetPlayerPos(playerid, X, Y, Z);

            dist = GetDistanceBetweenPoints(PublicGarage[i][pgPOS][0], PublicGarage[i][pgPOS][1], PublicGarage[i][pgPOS][2], X, Y, Z);

            if(dist <= 350.0)
            {
                return i;
            }
        }
    }
    return -1;
}

PublicGarage_Refresh(id)
{
    if(id != -1)
    {
        if(IsValidDynamicObject(PublicGarage[id][pgObject]))
            DestroyDynamicObject(PublicGarage[id][pgObject]);
        
        if(IsValidDynamicMapIcon(PublicGarage[id][pgIcon]))
            DestroyDynamicMapIcon(PublicGarage[id][pgIcon]);
        
        if(IsValidDynamicArea(PublicGarage[id][pgArea]))
            DestroyDynamicArea(PublicGarage[id][pgArea]);

        PublicGarage[id][pgObject] = INVALID_STREAMER_ID;
        PublicGarage[id][pgIcon] = INVALID_STREAMER_ID;
        PublicGarage[id][pgArea] = INVALID_STREAMER_ID;

        if(PublicGarage[id][pgPOS][0] != 0.0 || PublicGarage[id][pgPOS][1] != 0.0 || PublicGarage[id][pgPOS][2] != 0.0)
        {
            PublicGarage[id][pgIcon] = CreateDynamicMapIcon(PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2], 55, -1, PublicGarage[id][pgWorld], PublicGarage[id][pgInterior], -1, 1500.0, MAPICON_LOCAL, -1, 0);
            PublicGarage[id][pgArea] = CreateDynamicSphere(PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2], 2.0, PublicGarage[id][pgInterior], PublicGarage[id][pgWorld]);
            PublicGarage[id][pgObject] = CreateCirclePickup(PICKUP_GREEN, PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2], PublicGarage[id][pgWorld], PublicGarage[id][pgInterior], -1); 
        }
    }
    return 1;
}

forward LoadPublicGarage();
public LoadPublicGarage()
{
    new
        id,
        rows = cache_num_rows();
    
    new Cache:Garkotcache;
    
    if(rows)
    {
        Garkotcache = cache_save();

        for (new i = 0; i < rows; i ++)
        {
            cache_get_value_name_int(i, "pgID", id);
            cache_get_value_name_int(i, "pgInterior", PublicGarage[id][pgInterior]);
            cache_get_value_name_int(i, "pgWorld", PublicGarage[id][pgWorld]);
            
            cache_get_value_name(i, "pgName", PublicGarage[id][pgName]);
            
            cache_get_value_name_float(i, "pgPosX", PublicGarage[id][pgPOS][0]);
            cache_get_value_name_float(i, "pgPosY", PublicGarage[id][pgPOS][1]);
            cache_get_value_name_float(i, "pgPosZ", PublicGarage[id][pgPOS][2]);
            
            cache_get_value_name_float(i, "pgSpawnX", PublicGarage[id][pgSpawnPOS][0]);
            cache_get_value_name_float(i, "pgSpawnY", PublicGarage[id][pgSpawnPOS][1]);
            cache_get_value_name_float(i, "pgSpawnZ", PublicGarage[id][pgSpawnPOS][2]);
            cache_get_value_name_float(i, "pgSpawnA", PublicGarage[id][pgSpawnPOS][3]);

            PublicGarage_Refresh(id);
            Iter_Add(PublicGarage, id);
        }
        printf("[Dynamic Public Garage]: Jumlah total Public Garage yang dimuat %d", rows);

        if(cache_is_valid(Garkotcache))
        {
            cache_delete(Garkotcache);
            printf("[Dynamic Public Garage]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Public Garage]: Cache tidak valid atau sudah dihapus.");
        }
    }
}

PublicGarage_Save(id)
{
    new shstr[596];
    format(shstr, sizeof(shstr), "UPDATE `public_garage` SET `pgName`='%s', `pgPosX`=%f, `pgPosY`=%f, `pgPosZ`=%f, \
    `pgSpawnX`=%f, `pgSpawnY`=%f, `pgSpawnZ`=%f, `pgSpawnA`=%f, `pgInterior`=%d, `pgWorld`=%d WHERE `pgID`=%d", 
    PublicGarage[id][pgName], PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2],
    PublicGarage[id][pgSpawnPOS][0], PublicGarage[id][pgSpawnPOS][1], PublicGarage[id][pgSpawnPOS][2], PublicGarage[id][pgSpawnPOS][3], PublicGarage[id][pgInterior], PublicGarage[id][pgWorld], id);
    return mysql_tquery(g_SQL, shstr);
}

CMD:addgarkot(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);
    
    new id = Iter_Free(PublicGarage), name[64], Float:x, Float:y, Float:z;
    if(id == -1) return Error(playerid, "Tidak dapat menambah garkot di server lagi!");
    if(sscanf(params, "s[64]", name)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addgarkot [nama garkot]");
    if(strlen(name) < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 5 karakter!");

    GetPlayerPos(playerid, x, y, z);
    PublicGarage[id][pgPOS][0] = x;
    PublicGarage[id][pgPOS][1] = y;
    PublicGarage[id][pgPOS][2] = z;
    PublicGarage[id][pgInterior] = GetPlayerInterior(playerid);
    PublicGarage[id][pgWorld] = GetPlayerVirtualWorld(playerid);
    format(PublicGarage[id][pgName], 64, name);

    PublicGarage_Refresh(id);
    Iter_Add(PublicGarage, id);

    new cQuery[255];
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `public_garage` SET `pgID`=%d, `pgName`='%s', `pgPosX`=%f, `pgPosY`=%f, `pgPosZ`=%f, `pgSpawnX`=%f, `pgSpawnY`=%f, `pgSpawnZ`=%f, `pgInterior`=%d, `pgWorld`=%d",
    id, PublicGarage[id][pgName], PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2], PublicGarage[id][pgSpawnPOS][0], PublicGarage[id][pgSpawnPOS][1], PublicGarage[id][pgSpawnPOS][2], PublicGarage[id][pgSpawnPOS][3], PublicGarage[id][pgInterior], PublicGarage[id][pgWorld]);
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
        ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editgarkot [id] [enitity]~n~location, spawnpos, name, delete");
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

        PublicGarage_Refresh(did);
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
        PublicGarage_Refresh(did);
        PublicGarage_Save(did);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan spawn pos Garkot %s ID %d", AccountData[playerid][pAdminname], PublicGarage[did][pgName], did);
    }
    else if(!strcmp(type, "name", true))
    {
        new frmtname[65];
        if(sscanf(string, "s[65]", frmtname)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editgarkot [id] [name] [garkot name]");

        format(PublicGarage[did][pgName], sizeof(frmtname), frmtname);
        PublicGarage_Refresh(did);
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

        Iter_Remove(PublicGarage, did);
        PublicGarage_Refresh(did);
        Info(playerid, "Anda menghapus Dynamic Garkot ID %d", did);

        new query[125];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `public_garage` WHERE `pgID`=%d", did);
        mysql_tquery(g_SQL, query); 
    }
    return 1;
}

/*CMD:gotogarkot(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 1) return PermissionError(playerid);

    static shstr[512];
    format(shstr, sizeof(shstr), "#ID\tGarkot Name\n");
    forex(i, MAX_PUBLIC_GARAGE) if (PublicGarage[i][pgPOS][0] != 0.0)
    {
        format(shstr, sizeof(shstr), "%s#%d\t%s\n", shstr, i, PublicGarage[i][pgName]);
    }
    Dialog_Show(playerid, DIALOG_GOTO_GARKOT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Garkot", shstr, "Select", "Batal");
    return 1;
}

Dialog:DIALOG_GOTO_GARKOT(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        SetPlayerPos(playerid, PublicGarage[listitem][pgPOS][0], PublicGarage[listitem][pgPOS][1], PublicGarage[listitem][pgPOS][2]);
        SetPlayerInterior(playerid, PublicGarage[listitem][pgInterior]);
        SetPlayerVirtualWorld(playerid, PublicGarage[listitem][pgWorld]);
        AccountData[playerid][pInDoor] = -1;
        AccountData[playerid][pInHouse] = -1;
        AccountData[playerid][pInBiz] = -1;
        AccountData[playerid][pInFamily] = -1;
        AccountData[playerid][pInRusun] = -1;
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" teleportasi ke Public Garage ID: "YELLOW"%d - %s.", GetAdminName(playerid), listitem, PublicGarage[listitem][pgName]);
    }
    else Info(playerid, "Anda telah membatalkan pilihan");
    return 1;
}*/

CMD:gotogarkot(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;

    new id;
    if(AccountData[playerid][pAdmin] < 1) return PermissionError(playerid);

    if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotogarkot [id]");
    if(!Iter_Contains(PublicGarage, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Garkot tidak ditemukan");
    
    SetPlayerPos(playerid, PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2]);
    SetPlayerInterior(playerid, PublicGarage[id][pgInterior]);
    SetPlayerVirtualWorld(playerid, PublicGarage[id][pgWorld]);
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" teleportasi ke Public Garage ID: "YELLOW"%d - %s.", GetAdminName(playerid), id, PublicGarage[id][pgName]);
	return 1;
}

forward OnPublicGarageAdded(playerid, pgid);
public OnPublicGarageAdded(playerid, pgid)
{
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah membuat Public Garage ID: %d dengan nama %s.", GetAdminName(playerid), pgid, PublicGarage[pgid][pgName]);
    PublicGarage_Save(pgid);

    new shstr[125];
	format(shstr, sizeof(shstr), "Menggunakan CMD /addgarkot dengan ID: %d - %s", pgid, PublicGarage[pgid][pgName]);
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), shstr);
    return 1;
}

/* Hooks */
hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    foreach(new i : PublicGarage)
    {
        if(areaid == PublicGarage[i][pgArea])
        {
            if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
            {
                ShowKey(playerid, "[Y] Akses Garasi Umum");
            }
            else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
            {
                ShowKey(playerid, "[H] Simpan Kendaraan");
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    foreach(new i : PublicGarage)
    {
        if(areaid == PublicGarage[i][pgArea])
        {
            HideShortKey(playerid);
        }
    }
    return 1;
}
