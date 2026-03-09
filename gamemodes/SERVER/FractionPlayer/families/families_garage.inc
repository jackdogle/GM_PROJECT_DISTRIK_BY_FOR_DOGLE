#include <YSI\y_hooks>
#define MAX_FAMILIES_GARKOT 20
enum _:EFamiliesGarage
{
    gFamID,
    gFamName[32],
    Float:gFamPOS[3],
    Float:gFamSpawn[4],
    gFamInterior,
    gFamWorld,

    STREAMER_TAG_OBJECT:gFamObject,
    STREAMER_TAG_AREA:gFamArea,
};
new FamiliesGarage[MAX_FAMILIES_GARKOT][_:EFamiliesGarage],
    Iterator:FamiliesGarkot<MAX_FAMILIES_GARKOT>;

gFamRefresh(id)
{
    if(id != -1)
    {
        if(IsValidDynamicObject(FamiliesGarage[id][gFamObject]))
            DestroyDynamicObject(FamiliesGarage[id][gFamObject]);
        
        if(IsValidDynamicArea(FamiliesGarage[id][gFamArea]))
            DestroyDynamicArea(FamiliesGarage[id][gFamArea]);

        if(FamiliesGarage[id][gFamPOS][0] != 0.0 || FamiliesGarage[id][gFamPOS][1] != 0.0 || FamiliesGarage[id][gFamPOS][2] != 0.0)
        {
            FamiliesGarage[id][gFamObject] = CreateDynamicObject(1316, FamiliesGarage[id][gFamPOS][0], FamiliesGarage[id][gFamPOS][1], FamiliesGarage[id][gFamPOS][2] - 0.90, 0.000000, 0.000000, 0.000000, FamiliesGarage[id][gFamWorld], FamiliesGarage[id][gFamInterior], -1, 300.00, 300.00); 
            SetDynamicObjectMaterial(FamiliesGarage[id][gFamObject], 0, 10765, "airportgnd_sfse", "white", 0xFFFF99CC);
            FamiliesGarage[id][gFamArea] = CreateDynamicSphere(FamiliesGarage[id][gFamPOS][0], FamiliesGarage[id][gFamPOS][1], FamiliesGarage[id][gFamPOS][2], 2.0, FamiliesGarage[id][gFamWorld], FamiliesGarage[id][gFamInterior], -1);
        }
    }
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    foreach(new id : FamiliesGarkot)
    {
        if(IsPlayerInDynamicArea(playerid, FamiliesGarage[id][gFamArea]))
        {
            if(areaid == FamiliesGarage[id][gFamArea])
            {
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
                {
                    ShowKey(playerid, "[H] Simpan Kendaraan");
                }
                else 
                {
                    ShowKey(playerid, "[Y] Garasi Families");
                }
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    foreach(new id : FamiliesGarkot)
    {
        if(areaid == FamiliesGarage[id][gFamArea])
        {
            HideShortKey(playerid);
        }
    }
    return 1;
}

forward LoadFamiliesGarkot();
public LoadFamiliesGarkot()
{
    new rows;
    cache_get_row_count(rows);
    new Cache:FamGarCache;
    if(rows)
    {
        FamGarCache = cache_save();

        new id, i = 0;
        while(i < rows)
        {
            cache_get_value_int(i, "ID", id);
            cache_get_value_int(i, "gFamiliesID", FamiliesGarage[id][gFamID]);
            
            cache_get_value(i, "gFamiliesName", FamiliesGarage[id][gFamName]);

            cache_get_value_float(i, "gFamiliesPOSX", FamiliesGarage[id][gFamPOS][0]);
            cache_get_value_float(i, "gFamiliesPOSY", FamiliesGarage[id][gFamPOS][1]);
            cache_get_value_float(i, "gFamiliesPOSZ", FamiliesGarage[id][gFamPOS][2]);
            
            cache_get_value_float(i, "gFamiliesSpawnX", FamiliesGarage[id][gFamSpawn][0]);
            cache_get_value_float(i, "gFamiliesSpawnY", FamiliesGarage[id][gFamSpawn][1]);
            cache_get_value_float(i, "gFamiliesSpawnZ", FamiliesGarage[id][gFamSpawn][2]);
            cache_get_value_float(i, "gFamiliesSpawnA", FamiliesGarage[id][gFamSpawn][3]);

            cache_get_value_int(i, "gFamiliesInterior", FamiliesGarage[id][gFamInterior]);
            cache_get_value_int(i, "gFamiliesWorld", FamiliesGarage[id][gFamWorld]);

            gFamRefresh(id);
            Iter_Add(FamiliesGarkot, id);
            i++;
        }
        printf("[Dynamic Families Garage]: Jumlah total Garasi Families yang dimuat %d.", i);

        if(cache_is_valid(FamGarCache))
        {
            cache_delete(FamGarCache);
            printf("[Dynamic Families Garage]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Families Garage]: Cache tidak valid atau sudah dihapus.");
        }
    }
}
forward OnFamiliesGarageCreated(playerid, id);
public OnFamiliesGarageCreated(playerid, id)
{
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" membuat Families Garage ID: %d", GetAdminName(playerid), id);
    FamiliesGarkot_Save(id);
    return 1;
}

FamiliesGarkot_Save(id)
{
    new query[512];
    format(query, sizeof(query), "UPDATE families_garage SET gFamiliesID = '%d', gFamiliesName = '%s', gFamiliesPOSX = '%f', gFamiliesPOSY = '%f', gFamiliesPOSZ = '%f', gFamiliesSpawnX = '%f', gFamiliesSpawnY = '%f', gFamiliesSpawnZ = '%f', gFamiliesSpawnA = '%f', gFamiliesInterior = '%d', gFamiliesWorld = '%d' WHERE ID = '%d'",
    FamiliesGarage[id][gFamID],
    FamiliesGarage[id][gFamName],
    FamiliesGarage[id][gFamPOS][0],
    FamiliesGarage[id][gFamPOS][1],
    FamiliesGarage[id][gFamPOS][2],
    FamiliesGarage[id][gFamSpawn][0],
    FamiliesGarage[id][gFamSpawn][1],
    FamiliesGarage[id][gFamSpawn][2],
    FamiliesGarage[id][gFamSpawn][3],
    FamiliesGarage[id][gFamInterior],
    FamiliesGarage[id][gFamWorld],
    id
    );
    return mysql_tquery(g_SQL, query);
}

/*Commands*/
CMD:addfamgarkot(playerid, params[])
{
    if(CheckAdmin(playerid, 3))
        return PermissionError(playerid);
    
    new id = Iter_Free(FamiliesGarkot), query[512];
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak bisa menambah Garkot Families lagi!");
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    FamiliesGarage[id][gFamPOS][0] = x;
    FamiliesGarage[id][gFamPOS][1] = y;
    FamiliesGarage[id][gFamPOS][2] = z;
    FamiliesGarage[id][gFamID] = -1;
    FamiliesGarage[id][gFamInterior] = GetPlayerInterior(playerid);
    FamiliesGarage[id][gFamWorld] = GetPlayerVirtualWorld(playerid);
    format(FamiliesGarage[id][gFamName], 32, "N/A");
    Iter_Add(FamiliesGarkot, id);

    gFamRefresh(id);

    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO families_garage SET ID = '%d', gFamiliesName = '%s', gFamiliesPOSX = '%f', gFamiliesPOSY = '%f', gFamiliesPOSZ = '%f', gFamiliesInterior = '%d', gFamiliesWorld = '%d'", id, FamiliesGarage[id][gFamName], FamiliesGarage[id][gFamPOS][0], FamiliesGarage[id][gFamPOS][1], FamiliesGarage[id][gFamPOS][2], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
    mysql_tquery(g_SQL, query, "OnFamiliesGarageCreated", "dd", playerid, id);
    return 1;
}

CMD:gotofamgarage(playerid, params[])
{
    new 
        id
    ;
    if(!IsPlayerConnected(playerid)) return false;
    if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotofamgarage [id]");
    if(CheckAdmin(playerid, 3)) return PermissionError(playerid);
    if(!Iter_Contains(FamiliesGarkot, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Families Garage tidak ditemukan!");
    if(id < 0 || id >= MAX_FAMILIES_GARKOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid ID Families Garage!");

    SetPlayerPos(playerid, FamiliesGarage[id][gFamPOS][0], FamiliesGarage[id][gFamPOS][1], FamiliesGarage[id][gFamPOS][2]);
    SetPlayerVirtualWorld(playerid, FamiliesGarage[id][gFamWorld]);
    SetPlayerInterior(playerid, FamiliesGarage[id][gFamInterior]);
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInRusun] = -1;
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Teleportasi ke Families Garage ID: %d", GetAdminName(playerid), id);
    return 1;
}

CMD:editfamgarkot(playerid, params[])
{
    if(CheckAdmin(playerid, 3))
        return PermissionError(playerid);
    
    static 
        id,
        type[24],
        string[128];
    
    if(sscanf(params, "ds[24]S()[128]", id, type, string))
    {
        ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editfamgarkot [id] [name]~n~famid, delete, position, spawnpos");
        return 1;
    }
    if(id < 0 || id >= MAX_FAMILIES_GARKOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Families Garage ID!");
    if(!Iter_Contains(FamiliesGarkot, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Families Garage tidak ditemukan!");

    if(!strcmp(type, "famid", true))
    {
        new famid, fgname[128];
        if(sscanf(string, "d", famid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editfamgarkot [id] [famid] [famid]");
        if(!Iter_Contains(Families, famid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Families tidak ditemukan!");

        FamiliesGarage[id][gFamID] = famid;
        if(famid != -1)
        {
            format(fgname, 128, FamData[famid][famName]);
        }

        strunpack(FamiliesGarage[id][gFamName], fgname);
        gFamRefresh(id);
        FamiliesGarkot_Save(id);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menetapkan Families Garkot ID: %d menjadi milik Families ID: %d", GetAdminName(playerid), id, famid);
    }
    else if(!strcmp(type, "position", true))
    {
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);

        FamiliesGarage[id][gFamPOS][0] = x;
        FamiliesGarage[id][gFamPOS][1] = y;
        FamiliesGarage[id][gFamPOS][2] = z;
        FamiliesGarage[id][gFamInterior] = GetPlayerInterior(playerid);
        FamiliesGarage[id][gFamWorld] = GetPlayerVirtualWorld(playerid);

        gFamRefresh(id);
        FamiliesGarkot_Save(id);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" mengubah posisi Families Garkot ID: %d", GetAdminName(playerid), id);
    }
    else if(!strcmp(type, "delete", true))
    {
        DestroyDynamicObject(FamiliesGarage[id][gFamObject]);
        DestroyDynamicArea(FamiliesGarage[id][gFamArea]);

        FamiliesGarage[id][gFamPOS][0] = FamiliesGarage[id][gFamPOS][1] = FamiliesGarage[id][gFamPOS][2] = 0.0;
        FamiliesGarage[id][gFamInterior] = FamiliesGarage[id][gFamWorld] = 0;
        FamiliesGarage[id][gFamID] = -1;
        Iter_Remove(FamiliesGarkot, id);

        new query[200];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `families_garage` WHERE `ID` = '%d'", id);
        mysql_tquery(g_SQL, query);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menghapus Families Garkot ID: %d", GetAdminName(playerid), id);
    }
    else if(!strcmp(type, "spawnpos", true))
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        new Float:x, Float:y, Float:z, Float: angle;
        if(IsPlayerInAnyVehicle(playerid)) {
            GetVehiclePos(vehicleid, x, y, z);
            GetVehicleZAngle(vehicleid, angle);

            FamiliesGarage[id][gFamSpawn][0] = x;
            FamiliesGarage[id][gFamSpawn][1] = y;
            FamiliesGarage[id][gFamSpawn][2] = z;
            FamiliesGarage[id][gFamSpawn][3] = angle;

            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menetapkan lokasi spawn Families Garkot ID:%d", ReturnName(playerid), id);
            FamiliesGarkot_Save(id);
        } else {
            GetPlayerPos(playerid, x, y, z);
            GetPlayerFacingAngle(playerid, angle);

            FamiliesGarage[id][gFamSpawn][0] = x;
            FamiliesGarage[id][gFamSpawn][1] = y;
            FamiliesGarage[id][gFamSpawn][2] = z;
            FamiliesGarage[id][gFamSpawn][3] = angle;

            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menetapkan lokasi spawn Families Garkot ID: %d", ReturnName(playerid), id);
            FamiliesGarkot_Save(id);
        }
    }
    return 1;
}

/*Key State*/
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CROUCH && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        foreach(new id : FamiliesGarkot)
        {
            if(IsPlayerInRangeOfPoint(playerid, 2.0, FamiliesGarage[id][gFamPOS][0], FamiliesGarage[id][gFamPOS][1], FamiliesGarage[id][gFamPOS][2]))
            {
                if(AccountData[playerid][pFamily] != FamiliesGarage[id][gFamID])
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Khusus anggota Families!");
                
                new 
                    carid = -1,
                    found = 0;
                
                if((carid = Vehicle_Nearest2(playerid)) != -1)
                {
                    if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
                    if(PlayerVehicle[carid][pVehRental] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat memasukan kendaraan Rental ke Garasi Families!");
                    if(PlayerVehicle[carid][pVehFaction] != FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan faction tidak dapat dimasukkan ke garasi families!");

                    GetVehicleHealth(PlayerVehicle[carid][pVehPhysic], PlayerVehicle[carid][pVehHealth]);
                    RemovePlayerFromVehicle(playerid);

                    PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
                    PlayerVehicle[carid][pVehFamiliesGarage] = id;
                    AccountData[playerid][pPark] = id;
                    SetPlayerArmedWeapon(playerid, 0);
                    found++;
                    SavePlayerVehicle(carid);
                    if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]))
                    {
                        DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
                        PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
                    }
                    HideShortKey(playerid);
                }
            }
        }
    }
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        foreach(new i : FamiliesGarkot)
        {
            if(IsPlayerInRangeOfPoint(playerid, 2.0, FamiliesGarage[i][gFamPOS][0], FamiliesGarage[i][gFamPOS][1], FamiliesGarage[i][gFamPOS][2]))
            {
                if(AccountData[playerid][pFamily] == FamiliesGarage[i][gFamID])
                {
                    new twsmk[512], tmpcount = 0;
                    AccountData[playerid][pPark] = i;
                    format(twsmk, sizeof(twsmk), "No\tModel Kendaraan\tNomor Plat\n");
                    if(!CountPlayerVehicleFamilies(playerid, i)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun di garasi ini!");
                    foreach(new id : PvtVehicles)
                    {
                        if(PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID])
                        {
                            if(!IsValidVehicle(PlayerVehicle[id][pVehPhysic]))
                            {
                                if(PlayerVehicle[id][pVehFamiliesGarage] == AccountData[playerid][pPark])
                                {
                                    tmpcount++;
                                    format(twsmk, sizeof(twsmk), "%s%d\t%s\t%s\n", twsmk, tmpcount, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                                }
                            }
                        }
                    }
                    Dialog_Show(playerid, DialogFamiliesGarage, DIALOG_STYLE_TABLIST_HEADERS, sprintf(""TCRP"District  "WHITE"- Garasi %s", FamiliesGarage[i][gFamName]), twsmk, "Pilih", "Batal");
                } else ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya families terkait yang dapat menggunakan Garasi!");
                HideShortKey(playerid);
            }
        }
    }
    return 1;
}

/*Dialogs*/
Dialog:DialogFamiliesGarage(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;
    if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "anda sedang pingsan!");
    if(response)
    {
        new id = AccountData[playerid][pPark];
        if(id == -1) return 0;

        new i = ReturnAnyVehicleFamilies(playerid, (listitem), id);

        PlayerVehicle[i][pVehParked] = -1;
        PlayerVehicle[i][pVehHouseGarage] = -1;
        PlayerVehicle[i][pVehHelipadGarage] = -1;
        PlayerVehicle[i][pVehFamiliesGarage] = -1;
        PlayerVehicle[i][pVehFactStored] = -1;

        if(PlayerVehicle[i][pVehLocked]) {
            PlayerVehicle[i][pVehLocked] = false;
        }

        PlayerVehicle[i][pVehWorld] = GetPlayerVirtualWorld(playerid);
        PlayerVehicle[i][pVehInterior] = GetPlayerInterior(playerid);

        PlayerVehicle[i][pVehPos][0] = FamiliesGarage[id][gFamSpawn][0];
        PlayerVehicle[i][pVehPos][1] = FamiliesGarage[id][gFamSpawn][1];
        PlayerVehicle[i][pVehPos][2] = FamiliesGarage[id][gFamSpawn][2];
        PlayerVehicle[i][pVehPos][3] = FamiliesGarage[id][gFamSpawn][3];

        OnPlayerVehicleRespawn(i);
        SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[i][pVehPhysic], 0);
    }
    return 1;
}
