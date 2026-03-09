SSCANF:UndergroundMenu(string[]) 
{
 	if(!strcmp(string,"create",true)) return 1;
 	else if(!strcmp(string,"delete",true)) return 2;
 	else if(!strcmp(string,"enter",true)) return 3;
 	else if(!strcmp(string,"exit",true)) return 4;
 	return 0;
}

CMD:basement(playerid, params[])
{
    static 
        index, action, nextParams[128];

    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    if(sscanf(params, "k<UndergroundMenu>S()[128]", action, nextParams))
        return Syntax(playerid, "/basement (create, delete, enter, exit)");
    
    switch(action)
    {
        case 1: //create
        {
            if(GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0)  
                return Error(playerid, "Pastikan kondisi interior/wid anda berada di angka 0!");
            
            if((index = Underground_Create(playerid)) != -1) SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" membuat Basement ID "YELLOW"%d", AccountData[playerid][pAdminname], index);
            else Error(playerid, "Gagal membuat Basement, sudah mencapai batas maksimal!");
        }
        case 2: //delete
        {
            if(sscanf(nextParams, "d", index))
                return Syntax(playerid, "/basement delete [basement id]");
            
            if(!Underground_IsExists(index))
                return Error(playerid, "ID Basement tidak ada!");
            
            Underground_Delete(index);
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menghapus Basement ID "YELLOW"%d", AccountData[playerid][pAdminname], index);
        }
        case 3: //enter
        {
            if(GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0)
                return Error(playerid, "Pastikan kondisi interior/wid anda berada di angka 0!");
            
            if(sscanf(nextParams, "d", index))
                return Syntax(playerid, "/basement enter [basement id]");
            
            if(!Underground_IsExists(index))
                return Error(playerid, "ID Basement tidak ada!");
            
            GetPlayerPos(playerid, UndergroundData[index][underEnter][0], UndergroundData[index][underEnter][1], UndergroundData[index][underEnter][2]);

            Underground_Sync(index);
            Underground_Save(index);
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" mengubah posisi masuk Basement ID "YELLOW"%d", AccountData[playerid][pAdminname], index);
        }
        case 4: //exit
        {
            if(GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0)
                return Error(playerid, "Pastikan kondisi interior/wid anda berada di angka 0!");
            
            if(sscanf(nextParams, "d", index))
                return Syntax(playerid, "/basement enter [basement id]");
            
            if(!Underground_IsExists(index))
                return Error(playerid, "ID Basement tidak ada!");
            
            GetPlayerPos(playerid, UndergroundData[index][underExitSpawn][0], UndergroundData[index][underExitSpawn][1], UndergroundData[index][underExitSpawn][2]);
            GetPlayerFacingAngle(playerid, UndergroundData[index][underExitSpawn][3]);

            Underground_Sync(index);
            Underground_Save(index);
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" mengubah posisi keluar Basement ID "YELLOW"%d", AccountData[playerid][pAdminname], index);
        }
        default: Syntax(playerid, "/basement (create, delete, enter, exit)");
    }
    return 1;
}