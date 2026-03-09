CMD:addicon(playerid, params[])
{
    static
        type,
        id = -1;
    
    if (!AccountData[playerid][IsLoggedIn]) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus login!");
    
    if (AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);
    
    if (sscanf(params, "d", type))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addicon [type]");

    id = CreateDynamicIcon(playerid, type);

    if (id == -1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "The server has reached the limit for icons!");
    
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah membuat Dynamic Icon ID: %d", AccountData[playerid][pAdminname], id);
    return 1;
}

CMD:gotoicon(playerid, params[])
{
    static
        id = 0;
    
    if (!AccountData[playerid][IsLoggedIn]) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus login!");
    
    if (AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);
    
    if (sscanf(params, "d", id))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/destroyicon [icon id]");

    if ((id < 0 || id >= MAX_DYNAMIC_ICON) || !IconInfo[id][iconExists])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Icon tidak ditemukan!");

    SetPlayerPos(playerid, IconInfo[id][iconLocation][0], IconInfo[id][iconLocation][1], IconInfo[id][iconLocation][2]);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" teleportasi ke Dynamic Icon ID: %d", AccountData[playerid][pAdminname], id);
    return 1;
}

CMD:destroyicon(playerid, params[])
{
    static
        id = 0;
    
    if (!AccountData[playerid][IsLoggedIn]) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus login!");
    
    if (AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);
    
    if (sscanf(params, "d", id))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/destroyicon [icon id]");

    if ((id < 0 || id >= MAX_DYNAMIC_ICON) || !IconInfo[id][iconExists])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Icon tidak ditemukan!");
    
    DeleteDynamicIcon(id);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menghapus Dynamic Icon ID: %d", AccountData[playerid][pAdminname], id);
    return 1;
}