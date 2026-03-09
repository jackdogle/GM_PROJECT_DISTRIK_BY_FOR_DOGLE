#include <YSI\y_hooks>
#define MAX_DYNAMIC_FACTION_GARAGE (50)

enum e_factiongarage
{
    bool: fgExists,
    
    fgName[258],
    fgType,
    fgInterior,
    fgWorld,
    
    Float:fgaragePos[3],
    Float:fgarageSpawn[4],
    STREAMER_TAG_PICKUP:fgPickup,
    STREAMER_TAG_3D_TEXT_LABEL:fgLabel,
};
new FactionGarage[MAX_DYNAMIC_FACTION_GARAGE][e_factiongarage],
    Iterator:DynamicFactGarage<MAX_DYNAMIC_FACTION_GARAGE>;

FactGarageNearest(playerid)
{
    foreach(new i : DynamicFactGarage) if(IsPlayerInRangeOfPoint(playerid, 2.0, FactionGarage[i][fgaragePos][0], FactionGarage[i][fgaragePos][1], FactionGarage[i][fgaragePos][2]) && GetPlayerInterior(playerid) == FactionGarage[i][fgInterior] && GetPlayerVirtualWorld(playerid) == FactionGarage[i][fgWorld])
    {
        return i;
    }
    return -1;
}

FactGarageSave(id)
{
    new query[1218];
    mysql_format(g_SQL, query, sizeof(query), "UPDATE `factiongarage` SET `Name`='%s', `Type`=%d, `Interior`=%d, `World`=%d, `PosX`=%f, `PosY`=%f, `PosZ`=%f, `SpawnX`=%f, `SpawnY`=%f, `SpawnZ`=%f, `SpawnA`=%f WHERE `ID`=%d",
    FactionGarage[id][fgName], FactionGarage[id][fgType], FactionGarage[id][fgInterior], FactionGarage[id][fgWorld], FactionGarage[id][fgaragePos][0], FactionGarage[id][fgaragePos][1], FactionGarage[id][fgaragePos][2],
    FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], id);
    mysql_tquery(g_SQL, query);
    return 1;
}

GetFactNameGarage(id)
{
    new frmtname[125];
    if(id != -1)
    {
        if(FactionGarage[id][fgType] == 1) //polisi
        {
            format(frmtname, sizeof(frmtname), ""ROYALBLUE1"[Kepolisian District ]");
        }
        else if(FactionGarage[id][fgType] == 2) // pemerintah
        {
            format(frmtname, sizeof(frmtname), ""LIGHTSKYBLUE1"[Pemerintah Daerah District]");
        }
        else if(FactionGarage[id][fgType] == 3) // EMS
        {
            format(frmtname, sizeof(frmtname), ""VIOLETRED1"[EMS District ]");
        }
        else if(FactionGarage[id][fgType] == 4) // Trans
        {
            format(frmtname, sizeof(frmtname), ""YELLOW"[TRANS District ]");
        }
        else if(FactionGarage[id][fgType] == 5) // Bengkel
        {
            format(frmtname, sizeof(frmtname), ""LIGHTGREEN"[Bengkel District ]");
        }
        else if(FactionGarage[id][fgType] == 6) // EMS
        {
            format(frmtname, sizeof(frmtname), ""TOMATO1"[Pedagang District ]");
        }
        else if(FactionGarage[id][fgType] == 7) // bank
        {
            format(frmtname, sizeof(frmtname), ""TOMATO1"[Bank District ]");
        }
    }
    return frmtname;
}

GetFactGarageType(id)
{
    new frmtname[125];
    if(id != -1)
    {
        if(FactionGarage[id][fgType] == 1) //polisi
        {
            format(frmtname, sizeof(frmtname), "Polisi");
        }
        else if(FactionGarage[id][fgType] == 2) // pemerintah
        {
            format(frmtname, sizeof(frmtname), "Pemerintah");
        }
        else if(FactionGarage[id][fgType] == 3) // EMS
        {
            format(frmtname, sizeof(frmtname), "EMS");
        }
        else if(FactionGarage[id][fgType] == 4) // Trans
        {
            format(frmtname, sizeof(frmtname), "TRANS");
        }
        else if(FactionGarage[id][fgType] == 5) // Bengkel
        {
            format(frmtname, sizeof(frmtname), "Bengkel");
        }
        else if(FactionGarage[id][fgType] == 6) // EMS
        {
            format(frmtname, sizeof(frmtname), "Pedagang");
        }
    }
    return frmtname;
}

FactGarage_Rebuild(id)
{
    if(id != -1)
    {
        if(DestroyDynamicPickup(FactionGarage[id][fgPickup]))
            FactionGarage[id][fgPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
        
        if(DestroyDynamic3DTextLabel(FactionGarage[id][fgLabel]))
            FactionGarage[id][fgLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        
        if(FactionGarage[id][fgaragePos][0] != 0.0)
        {
            new shstr[598];
            format(shstr, sizeof(shstr), "%s\n"GREEN"%s"WHITE"\nFaction Garage\nGunakan "YELLOW"'[Y]'"WHITE" untuk akses menu garasi", GetFactNameGarage(id), FactionGarage[id][fgName]);
            FactionGarage[id][fgPickup] = CreateDynamicPickup(2485, 23, FactionGarage[id][fgaragePos][0], FactionGarage[id][fgaragePos][1], FactionGarage[id][fgaragePos][2], FactionGarage[id][fgWorld], FactionGarage[id][fgInterior], -1, 20.0);
            FactionGarage[id][fgLabel] = CreateDynamic3DTextLabel(shstr, -1, FactionGarage[id][fgaragePos][0], FactionGarage[id][fgaragePos][1], FactionGarage[id][fgaragePos][2] + 0.65, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, FactionGarage[id][fgWorld], FactionGarage[id][fgInterior], -1);
        }
    }
    return 1;
}

forward LoadFactionGarage();
public LoadFactionGarage()
{
    new Cache:Fctcache;
    if(cache_num_rows())
    {
        Fctcache = cache_save();

        new fid;
        for(new x; x < cache_num_rows(); x ++)
        {
            cache_get_value_name_int(x, "ID", fid);
            cache_get_value_name(x, "Name", FactionGarage[fid][fgName]);
            cache_get_value_name_int(x, "Type", FactionGarage[fid][fgType]);
            cache_get_value_name_int(x, "Interior", FactionGarage[fid][fgWorld]);
            cache_get_value_name_int(x, "World", FactionGarage[fid][fgInterior]);

            cache_get_value_name_float(x, "PosX", FactionGarage[fid][fgaragePos][0]);
            cache_get_value_name_float(x, "PosY", FactionGarage[fid][fgaragePos][1]);
            cache_get_value_name_float(x, "PosZ", FactionGarage[fid][fgaragePos][2]);
            
            cache_get_value_name_float(x, "SpawnX", FactionGarage[fid][fgarageSpawn][0]);
            cache_get_value_name_float(x, "SpawnY", FactionGarage[fid][fgarageSpawn][1]);
            cache_get_value_name_float(x, "SpawnZ", FactionGarage[fid][fgarageSpawn][2]);
            cache_get_value_name_float(x, "SpawnA", FactionGarage[fid][fgarageSpawn][3]);

            FactionGarage[fid][fgExists] = true;
            FactGarage_Rebuild(fid);
            Iter_Add(DynamicFactGarage, fid);
        }
        printf("[Dynamic Faction Garage]: Jumlah total garasi faction yang dimuat %d", cache_num_rows());

        if(cache_is_valid(Fctcache))
        {
            cache_delete(Fctcache);
            printf("[Dynamic Faction Garage]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Faction Garage]: Cache tidak valid atau sudah dihapus.");
        }
    }
}

FUNC::OnFactionGarageCreated(playerid, id)
{
    FactGarageSave(id);
    Info(playerid, "Berhasil membuat Dynamic Faction Garage ID: %d Dengan Faction ID: %d", id, FactionGarage[id][fgType]);
    Info(playerid, "Gunakan "YELLOW"/editfgarage "WHITE"untuk menyesuaikan spawn kendaraan faction!");
    return 1;
}

CMD:addfgarage(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    new id = Iter_Free(DynamicFactGarage);
    if(id == -1) return Error(playerid, "Tidak dapat menambah Dynamic Fact Garage lagi!");
    
    new type, frmxt[258];
    if(sscanf(params, "ds[258]", type, frmxt)) return Syntax(playerid, "/addfgarage [faction id] [name] (1.Kepolisian 2.Pemerintah 3.EMS 4.Trans 5.Bengkel 6.Pedagang)");
    if(type < 1 || type > 6) return Error(playerid, "ID Faction tidak valid!");

    GetPlayerPos(playerid, FactionGarage[id][fgaragePos][0], FactionGarage[id][fgaragePos][1], FactionGarage[id][fgaragePos][2]);
    FactionGarage[id][fgType] = type;
    strunpack(FactionGarage[id][fgName], frmxt, sizeof(frmxt));
    FactionGarage[id][fgInterior] = GetPlayerInterior(playerid);
    FactionGarage[id][fgWorld] = GetPlayerVirtualWorld(playerid);
    FactionGarage[id][fgarageSpawn][0] = 0.0;
    FactionGarage[id][fgarageSpawn][1] = 0.0;
    FactionGarage[id][fgarageSpawn][2] = 0.0;
    FactionGarage[id][fgarageSpawn][3] = 0.0;
    FactionGarage[id][fgExists] = true;

    FactGarage_Rebuild(id);
    Iter_Add(DynamicFactGarage, id);

    new query[712];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `factiongarage` SET `ID`=%d, `Name`='%s', `Type`=%d, `Interior`=%d, `World`=%d, `PosX`=%f, `PosY`=%f, `PosZ`=%f, `SpawnX`=%f, `SpawnY`=%f, `SpawnZ`=%f, `SpawnA`=%f",
    id, FactionGarage[id][fgName], FactionGarage[id][fgType], FactionGarage[id][fgInterior], FactionGarage[id][fgWorld], FactionGarage[id][fgaragePos][0], FactionGarage[id][fgaragePos][1], FactionGarage[id][fgaragePos][2],
    FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3]);
    mysql_tquery(g_SQL, query, "OnFactionGarageCreated", "dd", playerid, id);
    return 1;
}

CMD:removefgarage(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    new id;
    if(id < 0 || id >= MAX_DYNAMIC_FACTION_GARAGE) return Error(playerid, "ID Faction Garage tidak valid!");
    if(sscanf(params, "d", id)) return Syntax(playerid, "/removefgarage [id]");
    if(!Iter_Contains(DynamicFactGarage, id)) return Error(playerid, "ID Faction Garage tidak ada!");

    FactionGarage[id][fgExists] = false;
    FactionGarage[id][fgType] = FactionGarage[id][fgInterior] = FactionGarage[id][fgWorld] = 0;
    FactionGarage[id][fgarageSpawn][0] = FactionGarage[id][fgarageSpawn][1] = FactionGarage[id][fgarageSpawn][2] = FactionGarage[id][fgarageSpawn][3] = 0.0;
    FactionGarage[id][fgaragePos][0] = FactionGarage[id][fgaragePos][1] = FactionGarage[id][fgaragePos][2] = 0.0;
    format(FactionGarage[id][fgName], 32, "None");
    
    FactGarage_Rebuild(id);
    Iter_Remove(DynamicFactGarage, id);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menghapus Faction Garage ID %d", AccountData[playerid][pAdminname], id);

    new query[125];
    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `factiongarage` WHERE `ID`=%d", id);
    mysql_tquery(g_SQL, query);
    return 1;
}

CMD:editfgarage(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    static
        id, 
        option[24],
        nextParams[128];
    
    if(id < 0 || id >= MAX_DYNAMIC_FACTION_GARAGE) return Error(playerid, "ID Faction Garage tidak valid!");
    if(sscanf(params, "ds[24]S()[128]", id, option, nextParams))
    {
        Syntax(playerid, "/editfgarage [id] [name] (position, spawnveh, name, faction)");
        return 1;
    }
    if(!Iter_Contains(DynamicFactGarage, id)) return Error(playerid, "ID Faction Garage tidak ada!");
    if(!strcmp(option, "position", true))
    {
        GetPlayerPos(playerid, FactionGarage[id][fgaragePos][0], FactionGarage[id][fgaragePos][1], FactionGarage[id][fgaragePos][2]);
        FactionGarage[id][fgInterior] = GetPlayerInterior(playerid);
        FactionGarage[id][fgWorld] = GetPlayerVirtualWorld(playerid);

        FactGarage_Rebuild(id);
        FactGarageSave(id);
        Info(playerid, "Anda mengubah posisi Faction Garage ID %d", id);
    }
    else if(!strcmp(option, "spawnveh", true))
    {
        GetPlayerPos(playerid, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2]);
        GetPlayerFacingAngle(playerid, FactionGarage[id][fgarageSpawn][3]);
        FactionGarage[id][fgInterior] = GetPlayerInterior(playerid);
        FactionGarage[id][fgWorld] = GetPlayerVirtualWorld(playerid);

        FactGarage_Rebuild(id);
        FactGarageSave(id);
        Info(playerid, "Anda mengubah posisi spawn kendaraan Faction Garage ID %d", id);
    }
    else if(!strcmp(option, "name", true))
    {
        new frmxt[258];
        if(sscanf(nextParams, "s[258]", frmxt)) return Syntax(playerid, "/editfgarage [id] [name] [new name]");
        if(strlen(frmxt) < 1) return Error(playerid, "Nama tidak dapat kurang dari 1 huruf!");

        strunpack(FactionGarage[id][fgName], frmxt, sizeof(frmxt));
        FactGarage_Rebuild(id);
        FactGarageSave(id);
        Info(playerid, "Anda mengubah nama Faction Garage ID %d menjadi %s", id, frmxt);
    }
    else if(!strcmp(option, "faction", true))
    {
        new type;
        if(sscanf(nextParams, "d", type)) return Syntax(playerid, "/editfgarage [id] [faction] [new faction] (1.Kepolisian 2.Pemerintah 3.EMS 4.Trans 5.Bengkel 6.Pedagang)");

        FactionGarage[id][fgType] = type;
        FactGarage_Rebuild(id);
        FactGarageSave(id);
        Info(playerid, "Anda mengubah Faction Dynamic Faction Garage ID %d menjadi %d", id, type);
    }
    return 1;
}

/* Command */
/*CMD:fgarage(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid)) return 0;
    new fgid = FactGarageNearest(playerid);
    if(fgid != -1)
    {
        if(AccountData[playerid][pFaction] != FactionGarage[fgid][fgType]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garasi ini untuk salah satu anggota faction!");
        if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        ShowPlayerDialog(playerid, DIALOG_FACTION_GARAGE_MENU, DIALOG_STYLE_LIST, sprintf(""TCRP"District  "WHITE"- %s Garage", GetFactGarageType(fgid)), "Keluarkan Kendaraan\n"GRAY"Simpan Kendaraan", "Pilih", "Batal");
    }
    else ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak didekat garasi faction!");
    return 1;
}*/

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(!SQL_IsCharacterLogged(playerid)) return 0;
        new fgid = FactGarageNearest(playerid);
        if(fgid != -1)
        {
            if(AccountData[playerid][pFaction] != FactionGarage[fgid][fgType]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garasi ini untuk salah satu anggota faction!");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            ShowPlayerDialog(playerid, DIALOG_FACTION_GARAGE_MENU, DIALOG_STYLE_LIST, sprintf(""TCRP"District  "WHITE"- %s Garage", GetFactGarageType(fgid)), "Keluarkan Kendaraan\n"GRAY"Simpan Kendaraan", "Pilih", "Batal");
        }
        //else ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak didekat garasi faction!");
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_FACTION_GARAGE1:
        {
            new id = FactGarageNearest(playerid);
            if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada didekat garasi faction!");
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FactionGarage[id][fgType]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garasi ini khusus untuk anggota salah satu faction!");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(CountPlayerFactVeh(playerid) >= 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengeluarkan kendaraan!");
            switch(listitem)
            {
                case 0: //sultan
                {
                    VehicleFaction_Create(playerid, 560, FACTION_POLISI, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 1: //Sanchez
                {
                    VehicleFaction_Create(playerid, 468, FACTION_POLISI, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 2: //
                {
                    VehicleFaction_Create(playerid, 490, FACTION_POLISI, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 3: //
                {
                    VehicleFaction_Create(playerid, 427, FACTION_POLISI, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 4: //
                {
                    VehicleFaction_Create(playerid, 523, FACTION_POLISI, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 5: //
                {
                    VehicleFaction_Create(playerid, 426, FACTION_POLISI, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 6: //
                {
                    VehicleFaction_Create(playerid, 601, FACTION_POLISI, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 7: //
                {
                    VehicleFaction_Create(playerid, 528, FACTION_POLISI, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
            }
        }
        case DIALOG_FACTION_GARAGE2:
        {
            new id = FactGarageNearest(playerid);
            if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada didekat garasi faction!");
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FactionGarage[id][fgType]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garasi ini khusus untuk anggota salah satu faction!");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(CountPlayerFactVeh(playerid) >= 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengeluarkan kendaraan!");
            switch(listitem)
            {
                case 0: //Stretch
                {
                    VehicleFaction_Create(playerid, 409, FACTION_PEMERINTAH, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 1: //Admiral
                {
                    VehicleFaction_Create(playerid, 445, FACTION_PEMERINTAH, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 2: //Romero
                {
                    VehicleFaction_Create(playerid, 442, FACTION_PEMERINTAH, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
            }
        }
        case DIALOG_FACTION_GARAGE3:
        {
            new id = FactGarageNearest(playerid);
            if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada didekat garasi faction!");
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FactionGarage[id][fgType]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garasi ini khusus untuk anggota salah satu faction!");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(CountPlayerFactVeh(playerid) >= 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengeluarkan kendaraan!");
            switch(listitem)
            {
                case 0: //Ambulance
                {
                    VehicleFaction_Create(playerid, 416, FACTION_EMS, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 1: //FBI Rancher
                {
                    VehicleFaction_Create(playerid, 490, FACTION_EMS, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 2: //Sanchez EMS
                {
                    VehicleFaction_Create(playerid, 468, FACTION_EMS, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 3: //Mobil Jenazah
                {
                    VehicleFaction_Create(playerid, 442, FACTION_EMS, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
            }
        }
        case DIALOG_FACTION_GARAGE4:
        {
            new id = FactGarageNearest(playerid);
            if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada didekat garasi faction!");
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FactionGarage[id][fgType]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garasi ini khusus untuk anggota salah satu faction!");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(CountPlayerFactVeh(playerid) >= 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengeluarkan kendaraan!");
            switch(listitem)
            {
                case 0: //Taxi
                {
                    VehicleFaction_Create(playerid, 420, FACTION_TRANS, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 1: //Cabbie
                {
                    VehicleFaction_Create(playerid, 438, FACTION_TRANS, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 2: //Premier Trans
                {
                    VehicleFaction_Create(playerid, 561, FACTION_TRANS, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 3: //Premier Trans
                {
                    VehicleFaction_Create(playerid, 405, FACTION_TRANS, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
            }
        }
        case DIALOG_FACTION_GARAGE5:
        {
            new id = FactGarageNearest(playerid);
            if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada didekat garasi faction!");
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FactionGarage[id][fgType]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garasi ini khusus untuk anggota salah satu faction!");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(CountPlayerFactVeh(playerid) >= 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengeluarkan kendaraan!");
            switch(listitem)
            {
                case 0: //Mobil Derek
                {
                    VehicleFaction_Create(playerid, 525, FACTION_BENGKEL, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 1: //Sanchez
                {
                    VehicleFaction_Create(playerid, 440, FACTION_BENGKEL, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 2: //Mobil Derek
                {
                    VehicleFaction_Create(playerid, 468, FACTION_BENGKEL, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 3: //Sanchez
                {
                    VehicleFaction_Create(playerid, 504, FACTION_BENGKEL, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
            }
        }
        case DIALOG_FACTION_GARAGE6:
        {
            new id = FactGarageNearest(playerid);
            if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada didekat garasi faction!");
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FactionGarage[id][fgType]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garasi ini khusus untuk anggota salah satu faction!");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(CountPlayerFactVeh(playerid) >= 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengeluarkan kendaraan!");
            switch(listitem)
            {
                case 0: //Mobil Derek
                {
                    VehicleFaction_Create(playerid, 489, FACTION_PEDAGANG, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 1: //Sanchez
                {
                    VehicleFaction_Create(playerid, 468, FACTION_PEDAGANG, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 2: //Mobil Derek
                {
                    VehicleFaction_Create(playerid, 588, FACTION_PEDAGANG, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
                case 3: //Sanchez
                {
                    VehicleFaction_Create(playerid, 483, FACTION_PEDAGANG, FactionGarage[id][fgarageSpawn][0], FactionGarage[id][fgarageSpawn][1], FactionGarage[id][fgarageSpawn][2], FactionGarage[id][fgarageSpawn][3], 36, 36);
                }
            }
        }
        case DIALOG_FACTION_GARAGE_MENU:
        {
            new fgid = FactGarageNearest(playerid);
            if(fgid == -1) return 0;
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FactionGarage[fgid][fgType]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garasi ini khusus untuk anggota salah satu faction!");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            switch(listitem)
            {
                case 0: //keluarkan
                {
                    switch(FactionGarage[fgid][fgType])
                    {
                        case 1: //polisi
                        {
                            ShowPlayerDialog(playerid, DIALOG_FACTION_GARAGE1, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Keluarkan Kendaraan",
                            "Sultan Sabhara\
                            \n"GRAY"Sanchez Sabhara\
                            \nFBI Rancher\
                            \n"GRAY"Mobil Tahanan\
                            \nHPV 1000\
                            \n"GRAY"Mobil Patwal\
                            \nBarracuda\
                            \n"GRAY"Insurgent", "Pilih", "Batal");
                        }
                        case 2: //pemerintah
                        {
                            ShowPlayerDialog(playerid, DIALOG_FACTION_GARAGE2, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Keluarkan Kendaraan",
                            "Stretch Mobil Gubernur\
                            \n"GRAY"Admiral\
                            \nRomero", "Pilih", "Batal");
                        }
                        case 3: //EMS
                        {
                            ShowPlayerDialog(playerid, DIALOG_FACTION_GARAGE3, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Keluarkan Kendaraan",
                            "Ambulance\
                            \n"GRAY"FBI Rancher\
                            \nSanchez EMS\
                            \n"GRAY"Mobil Jenazah", "Pilih", "Batal");
                        }
                        case 4: //Trans
                        {
                            ShowPlayerDialog(playerid, DIALOG_FACTION_GARAGE4, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Keluarkan Kendaraan",
                            "Taxi\
                            \n"GRAY"Cabbie\
                            \n"GRAY"Stratum Trans\
                            \n"GRAY"Sentinel", "Pilih", "Batal");
                        }
                        case 5: // Bengkel
                        {
                            ShowPlayerDialog(playerid, DIALOG_FACTION_GARAGE5, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Keluarkan Kendaraan",
                            "Mobil Derek\
                            \n"GRAY"Rumpo\
                            \n"GRAY"Sanchez\
                            \n"GRAY"Bloody", "Pilih", "Batal");
                        }
                        case 6: //pedagang
                        {
                            ShowPlayerDialog(playerid, DIALOG_FACTION_GARAGE6, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Keluarkan Kendaraan",
                            "Rancher\
                            \n"GRAY"Sanchez\
                            \n"GRAY"Hotdog\
                            \n"GRAY"Camper Delivery", "Pilih", "Batal");
                        }
                    }
                }
                case 1: // Store vehicle
                {
                    if(!CountPlayerFactVeh(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak mengeluarkan kendaraan sebelumnya!");
                    VehicleFaction_Delete(playerid);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Kendaraan berhasil dikembalikan ke garasi faction.");
                }
            }
        }
    }
    return 1;
}