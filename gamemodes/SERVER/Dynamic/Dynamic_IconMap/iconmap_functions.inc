#include <YSI\y_hooks>
#define MAX_DYNAMIC_ICON    (50)

enum e_iconmapdata
{
    iconID,
    iconInterior,
    iconWorld,
    Float:iconMapPos[3],
    STREAMER_TAG_MAP_ICON:iconMap
};
new IconData[MAX_DYNAMIC_ICON][e_iconmapdata],
    Iterator:Icon<MAX_DYNAMIC_ICON>;

RefreshIconMap(id)
{
    if(id != -1)
    {
        if(IsValidDynamicMapIcon(IconData[id][iconMap]))
            DestroyDynamicMapIcon(IconData[id][iconMap]);
        
        if(IconData[id][iconMapPos][0] != 0.0 || IconData[id][iconMapPos][1] != 0.0 || IconData[id][iconMapPos][2] != 0.0)
        {
            IconData[id][iconMap] = CreateDynamicMapIcon(IconData[id][iconMapPos][0], IconData[id][iconMapPos][1], IconData[id][iconMapPos][2], IconData[id][iconID], -1, IconData[id][iconWorld], IconData[id][iconInterior], -1, STREAMER_MAP_ICON_SD, MAPICON_GLOBAL);
        }
    }
    return 1;
}

IconMapSave(id)
{
    new query[1218];
    mysql_format(g_SQL, query, sizeof(query), "UPDATE `iconmaps` SET `IconX`=%f, `IconY`=%f, `IconZ`=%f, `IconID`=%d, `IconInterior`=%d, `IconWorld`=%d WHERE `ID`=%d",
    IconData[id][iconMapPos][0], IconData[id][iconMapPos][1], IconData[id][iconMapPos][2], IconData[id][iconID], IconData[id][iconInterior], IconData[id][iconWorld], id);
    return mysql_tquery(g_SQL, query);
}

forward LoadMapIcon();
public LoadMapIcon()
{
    new Cache:Mapcache;

    new id, rows = cache_num_rows();
    if(rows)
    {
        Mapcache = cache_save();

        for(new i; i < rows; i ++)
        {
            cache_get_value_name_int(i, "ID", id);
            cache_get_value_name_int(i, "IconID", IconData[id][iconID]);
            cache_get_value_name_int(i, "IconInterior", IconData[id][iconInterior]);
            cache_get_value_name_int(i, "IconWorld", IconData[id][iconWorld]);

            cache_get_value_name_float(i, "IconX", IconData[id][iconMapPos][0]);
            cache_get_value_name_float(i, "IconY", IconData[id][iconMapPos][1]);
            cache_get_value_name_float(i, "IconZ", IconData[id][iconMapPos][2]);

            RefreshIconMap(id);
            Iter_Add(Icon, id);
        }
        printf("[Dynamic Map Icon]: Jumlah total Icon Map yang dimuat %d.", rows);

        if(cache_is_valid(Mapcache))
        {
            cache_delete(Mapcache);
            printf("[Dynamic Map Icon]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Map Icon]: Cache tidak valid atau sudah dihapus.");
        }
    }
}

function OnIconAdded(playerid, id)
{
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menambahkan Dynamic Map Icon ID: %d", GetAdminName(playerid), id);
    IconMapSave(id);
    return 1;
}

CMD:addicon(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if (AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);
    
    new 
        id = Iter_Free(Icon), 
        iconid;
    
    if(id == -1) return false;
    if(sscanf(params, "d", iconid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addicon [map icon]");
    if(iconid < 0 || iconid > 63) return ShowTDN(playerid, NOTIFICATION_ERROR, "Icon ID Tidak valid!");

    IconData[id][iconID] = iconid;
    GetPlayerPos(playerid, IconData[id][iconMapPos][0], IconData[id][iconMapPos][1], IconData[id][iconMapPos][2]);
    IconData[id][iconInterior] = GetPlayerInterior(playerid);
    IconData[id][iconWorld] = GetPlayerVirtualWorld(playerid);

    RefreshIconMap(id);
    Iter_Add(Icon, id);
    
    new shstr[596];
    mysql_format(g_SQL, shstr, sizeof(shstr), "INSERT INTO `iconmaps` SET `ID`=%d, `IconX`=%f, `IconY`=%f, `IconZ`=%f, `IconID`=%d, `IconInterior`=%d, `IconWorld`=%d",
    id, IconData[id][iconMapPos][0], IconData[id][iconMapPos][1], IconData[id][iconMapPos][2], IconData[id][iconID], IconData[id][iconInterior], IconData[id][iconWorld]);
    mysql_tquery(g_SQL, shstr, "OnIconAdded", "dd", playerid, id);
    return 1;
}

CMD:editicon(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if (AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    static 
        id,
        type[24],
        string[128];
    
    if(sscanf(params, "ds[24]S()[128]", id, type, string)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editicon [id] [entinity]~n~delete, iconid, location");
    if(!Iter_Contains(Icon, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Map Icon tidak ada!");
    if(id < 0 || id >= MAX_DYNAMIC_ICON) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Map Icon tidak valid!");

    if(!strcmp(type, "location", true))
    {
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        
        IconData[id][iconMapPos][0] = x;
        IconData[id][iconMapPos][1] = y;
        IconData[id][iconMapPos][2] = z;

        RefreshIconMap(id);
        IconMapSave(id);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Mengubah posisi Dynamic Icon ID: %d", GetAdminName(playerid), id);
    }
    else if(!strcmp(type, "delete", true))
    {
        DestroyDynamicMapIcon(IconData[id][iconMap]);

        IconData[id][iconMapPos][0] = IconData[id][iconMapPos][1] = IconData[id][iconMapPos][2] = 0.0;
        IconData[id][iconInterior] = IconData[id][iconWorld] = IconData[id][iconID] = -1;

        RefreshIconMap(id);
        IconMapSave(id);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menghapus Dynamic Icon ID: %d", GetAdminName(playerid), id);
        Iter_Remove(Icon, id);

        new query[200];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `iconmaps` WHERE `ID`=%d", id);
        mysql_tquery(g_SQL, query);
    }
    else if(!strcmp(type, "iconid", true))
    {
        new icon;
        if(sscanf(string, "d", icon)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editicon [id] [iconid] [icon id]");

        IconData[id][iconID] = icon;

        RefreshIconMap(id);
        IconMapSave(id);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Mengubah Icon Dynamic Icon ID: %d Menjadi Icon: %d", GetAdminName(playerid), id, icon);
    }
    return 1;
}

CMD:gotoicon(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1) return PermissionError(playerid);

    new id;
    if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotoicon [id]");
    if(!Iter_Contains(Icon, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Icon Map tidak ada!");
    if(id < 0 || id >= MAX_DYNAMIC_ICON) return ShowTDN(playerid, NOTIFICATION_ERROR, "Icon Map tidak valid!");

    SetPlayerPos(playerid, IconData[id][iconMapPos][0], IconData[id][iconMapPos][1], IconData[id][iconMapPos][2]);
    SetPlayerInterior(playerid, IconData[id][iconInterior]);
    SetPlayerVirtualWorld(playerid, IconData[id][iconWorld]);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Teleportasi ke Dynamic Map Icon ID: %d", GetAdminName(playerid), id);
    AccountData[playerid][pInHouse] = -1;    
    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInBiz] = -1;
    return 1;
}
