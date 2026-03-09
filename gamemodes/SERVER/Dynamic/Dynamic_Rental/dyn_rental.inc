#include <YSI\y_hooks>
#define MAX_DYNAMIC_RENTAL 20

enum eRental {
    Float:RentalPos[3],
    Float:RentalSpawn[4],
    RentalInterior,
    RentalVW,
    RentalTimer,
    RentalType,
    
    STREAMER_TAG_3D_TEXT_LABEL:RentalLabel,
    STREAMER_TAG_PICKUP: RentalPickup
};
new RentalData[MAX_DYNAMIC_RENTAL][eRental],
    Iterator: DynamicRents<MAX_DYNAMIC_RENTAL>;

RentalRefresh(rentid)
{
    if(rentid != -1)
    {
        if(DestroyDynamic3DTextLabel(RentalData[rentid][RentalLabel]))
            RentalData[rentid][RentalLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        
        if(DestroyDynamicPickup(RentalData[rentid][RentalPickup]))
            RentalData[rentid][RentalPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
        
        new string[100];
        switch(RentalData[rentid][RentalType])
        {
            case 1: string = "Vehicle Rental";
            case 2: string = "Boat Rental";
        }

        RentalData[rentid][RentalPickup] = CreateDynamicPickup(1239, 23, RentalData[rentid][RentalPos][0], RentalData[rentid][RentalPos][1], RentalData[rentid][RentalPos][2] + 0.20, RentalData[rentid][RentalVW], RentalData[rentid][RentalInterior], -1, 50.0);
        RentalData[rentid][RentalLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[%s]\n"BLUEJEGE"Rental Vehicle\n"GREEN"[Y]"WHITE" untuk mengakses rental vehicle", string), COLOR_WHITE, RentalData[rentid][RentalPos][0], RentalData[rentid][RentalPos][1], RentalData[rentid][RentalPos][2] + 0.55, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
    }
    return 1;
}

stock RentalNearest(playerid)
{
    foreach(new rentid : DynamicRents)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, RentalData[rentid][RentalPos][0], RentalData[rentid][RentalPos][1], RentalData[rentid][RentalPos][2])) 
        {
            return rentid;
        }
    }
    return -1;
}

forward Rental_Load();
public Rental_Load()
{
    new
        rentid,
        rows = cache_num_rows();
    
    new Cache:Rentcache;
    
    if(rows)
    {
        Rentcache = cache_save();

        for (new i = 0; i < rows; i ++)
        {
            rentid = cache_get_field_int(i, "RentID");
            RentalData[rentid][RentalPos][0] = cache_get_field_float(i, "RentalX");
            RentalData[rentid][RentalPos][1] = cache_get_field_float(i, "RentalY");
            RentalData[rentid][RentalPos][2] = cache_get_field_float(i, "RentalZ");

            RentalData[rentid][RentalSpawn][0] = cache_get_field_float(i, "RentSpawnX");
            RentalData[rentid][RentalSpawn][1] = cache_get_field_float(i, "RentSpawnY");
            RentalData[rentid][RentalSpawn][2] = cache_get_field_float(i, "RentSpawnZ");
            RentalData[rentid][RentalSpawn][3] = cache_get_field_float(i, "RentSpawnA");
            
            RentalData[rentid][RentalInterior] = cache_get_field_int(i, "RentInterior");
            RentalData[rentid][RentalVW] = cache_get_field_int(i, "RentVW");
            RentalData[rentid][RentalTimer] = cache_get_field_int(i, "RentTime");
            RentalData[rentid][RentalType] = cache_get_field_int(i, "RentType");
            
            RentalRefresh(rentid);
            Iter_Add(DynamicRents, rentid);
        }
        printf("[Dynamic Rental]: Jumlah total Rental yang dimuat %d", rows);
        if(cache_is_valid(Rentcache))
        {
            cache_delete(Rentcache);
            printf("[Dynamic Rental]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Rental]: Cache tidak valid atau sudah dihapus.");
        }
    }
}

RentalSave(rentid)
{
    new query[498];
    format(query, sizeof(query), "UPDATE bike_rentals SET RentalX='%f', RentalY='%f', RentalZ='%f', RentSpawnX='%f', RentSpawnY='%f', RentSpawnZ='%f', RentSpawnA='%f', RentTime=%d, RentInterior=%d, RentVW=%d, RentType=%d WHERE RentID=%d",
    RentalData[rentid][RentalPos][0],
    RentalData[rentid][RentalPos][1],
    RentalData[rentid][RentalPos][2],
    RentalData[rentid][RentalSpawn][0],
    RentalData[rentid][RentalSpawn][1],
    RentalData[rentid][RentalSpawn][2],
    RentalData[rentid][RentalSpawn][3],
    RentalData[rentid][RentalTimer],
    RentalData[rentid][RentalInterior],
    RentalData[rentid][RentalVW],
    RentalData[rentid][RentalType],
    rentid);
    return mysql_tquery(g_SQL, query);
}

CMD:addrental(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5)  
        return PermissionError(playerid);
    
    new rentid = Iter_Free(DynamicRents), type;
    if(rentid == INVALID_ITERATOR_SLOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Dynamic Rental sudah mencapai Limit Server!");
    if(sscanf(params, "d", type)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addrental [type] ( 1.Motocycle 2.Boat )");
    if(type < 1 || type > 2) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addrental [type] ( 1.Motocycle 2.Boat )"); 
    switch(type)
    {
        case 1: // Motor
        {
            GetPlayerPos(playerid, RentalData[rentid][RentalPos][0], RentalData[rentid][RentalPos][1], RentalData[rentid][RentalPos][2]);
            RentalData[rentid][RentalInterior] = GetPlayerInterior(playerid);
            RentalData[rentid][RentalVW] = GetPlayerVirtualWorld(playerid);
            RentalData[rentid][RentalSpawn][0] = RentalData[rentid][RentalSpawn][1] = RentalData[rentid][RentalSpawn][2] = RentalData[rentid][RentalSpawn][3] = 0.0;
            RentalData[rentid][RentalTimer] = 1800;
            RentalData[rentid][RentalType] = 1;
            RentalRefresh(rentid);
            Iter_Add(DynamicRents, rentid);
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah Membuat Dynamic Rental Motocycle ID: "YELLOW"%d", GetAdminName(playerid), rentid);
        }
        case 2: // Boat
        {
            GetPlayerPos(playerid, RentalData[rentid][RentalPos][0], RentalData[rentid][RentalPos][1], RentalData[rentid][RentalPos][2]);
            RentalData[rentid][RentalInterior] = GetPlayerInterior(playerid);
            RentalData[rentid][RentalVW] = GetPlayerVirtualWorld(playerid);
            RentalData[rentid][RentalSpawn][0] = RentalData[rentid][RentalSpawn][1] = RentalData[rentid][RentalSpawn][2] = RentalData[rentid][RentalSpawn][3] = 0.0;
            RentalData[rentid][RentalTimer] = 1800;
            RentalData[rentid][RentalType] = 2;
            RentalRefresh(rentid);
            Iter_Add(DynamicRents, rentid);
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah Membuat Dynamic Rental Boat ID: "YELLOW"%d", GetAdminName(playerid), rentid);
        }
    }

    new query[178];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO bike_rentals SET RentID='%d', RentalX='%f', RentalY='%f', RentalZ='%f', RentTime='%d', RentInterior='%d', RentVW='%d', RentType='%d'", rentid, RentalData[rentid][RentalPos][0], RentalData[rentid][RentalPos][1], RentalData[rentid][RentalPos][2], RentalData[rentid][RentalTimer], RentalData[rentid][RentalInterior], RentalData[rentid][RentalVW], RentalData[rentid][RentalType]);
	mysql_tquery(g_SQL, query, "OnBikeRentalCreated", "i", rentid);
    return 1;
}

FUNC::OnBikeRentalCreated(rentid)
{
    RentalSave(rentid);
    return 1;
}

CMD:gotorent(playerid, params[])
{
    new rentid;
    if(CheckAdmin(playerid, 3))
        return PermissionError(playerid);
    
    if(sscanf(params, "d", rentid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotorent [id rental]");
    if(!Iter_Contains(DynamicRents, rentid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Rental tidak ada!");
    SetPlayerPosition(playerid, RentalData[rentid][RentalPos][0], RentalData[rentid][RentalPos][1], RentalData[rentid][RentalPos][2], 2.0);
    SetPlayerInterior(playerid, RentalData[rentid][RentalInterior]);
    SetPlayerVirtualWorld(playerid, RentalData[rentid][RentalVW]);
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
	
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Teleportasi ke Dynamic Rental ID: %d", GetAdminName(playerid), rentid);
	return 1;
}

CMD:editrent(playerid, params[])
{
    static 
        rentid,
        type[24],
        string[128];
    
    if(CheckAdmin(playerid, 6)) 
        return PermissionError(playerid);
    
    if(sscanf(params, "ds[24]S()[128]", rentid, type, string))
    {
        ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editrent [id] [name]:~n~location, delete, spawnpos, time");
        return 1;
    }
    if(rentid < 0 || rentid >= MAX_DYNAMIC_RENTAL)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Rental ID!");
    if(!Iter_Contains(DynamicRents, rentid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Rental tidak ada!");

    if(!strcmp(type, "location", true))
    {
        GetPlayerPos(playerid, RentalData[rentid][RentalPos][0], RentalData[rentid][RentalPos][1], RentalData[rentid][RentalPos][2]);
        RentalData[rentid][RentalInterior] = GetPlayerInterior(playerid);
        RentalData[rentid][RentalVW] = GetPlayerVirtualWorld(playerid);

        RentalRefresh(rentid);
        RentalSave(rentid);

        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" mengubah titik lokasi dynamic rental id: %d", GetAdminName(playerid), rentid);
    }
    else if(!strcmp(type, "type", true))
    {
        new renttype;
        if(sscanf(string, "d", renttype)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editrent [id] [type] ( 1.Motocycle 2.Boat )");
        if(renttype < 1 || renttype > 2) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editrent [id] [type] ( 1.Motocycle 2.Boat )");

        RentalData[rentid][RentalType] = renttype;
        RentalRefresh(rentid);
        RentalSave(rentid);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Mengubah Type Rental ID: %d menjadi Rental "YELLOW"%s", rentid, RentalData[rentid][RentalType] == 1 ? "Motocycle" : "Boat");
    }
    else if(!strcmp(type, "time", true))
    {
        new time;
        if(sscanf(string, "d", time)) return Syntax(playerid, "/editrent [id] [time] [durasi rental [menit]]");

        RentalData[rentid][RentalTimer] = time*60;
        RentalRefresh(rentid);
        RentalSave(rentid);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Mengubah Durasi Rental ID: %d menjadi %d menit", rentid, time);
    }
    else if(!strcmp(type, "delete", true))
    {
        DestroyDynamic3DTextLabel(RentalData[rentid][RentalLabel]);
        DestroyDynamicPickup(RentalData[rentid][RentalPickup]);
        RentalData[rentid][RentalPos][0] = RentalData[rentid][RentalPos][1] = RentalData[rentid][RentalPos][2] = 0.0;
        RentalData[rentid][RentalInterior] = RentalData[rentid][RentalVW] = 0;
        RentalData[rentid][RentalLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        RentalData[rentid][RentalPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
        
        Iter_Remove(DynamicRents, rentid);
        mysql_tquery(g_SQL, sprintf("DELETE FROM bike_rentals WHERE RentID='%d'", rentid));
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah Menghapus Dynamic Rental ID: %d.", GetAdminName(playerid), rentid);
    }
    else if(!strcmp(type, "spawnpos", true))
    {
        new vehid = GetPlayerVehicleID(playerid);
        if(IsPlayerInAnyVehicle(playerid))
        {
            GetVehiclePos(vehid, RentalData[rentid][RentalSpawn][0], RentalData[rentid][RentalSpawn][1], RentalData[rentid][RentalSpawn][2]);
            GetVehicleZAngle(vehid, RentalData[rentid][RentalSpawn][3]);        
        }
        else 
        {
            GetPlayerPos(playerid, RentalData[rentid][RentalSpawn][0], RentalData[rentid][RentalSpawn][1], RentalData[rentid][RentalSpawn][2]);
            GetPlayerFacingAngle(playerid, RentalData[rentid][RentalSpawn][3]);

        }
        RentalRefresh(rentid);
        RentalSave(rentid);

        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah Menetapkan lokasi spawn sepeda Rental ID: %d", GetAdminName(playerid), rentid);
    }
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
    {
        static iterid = -1;

        if((iterid = Vehicle_Nearest2(playerid)) != -1)
        {
            if(Vehicle_IsOwner(playerid, iterid) && PlayerVehicle[iterid][pVehRental] != -1)
            {
                new currentTime = PlayerVehicle[iterid][pVehRentTime] - gettime();
                new hours = (currentTime % 86400) / 3600;
                new minutes = (currentTime % 3600) / 60;
                new seconds = currentTime % 60;

                Info(playerid, "Sisa waktu rental %d jam %d menit %d detik", hours, minutes, seconds);
            }
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new count = 0, rentid = RentalNearest(playerid);
        foreach(new i : Player) if (AccountData[i][IsLoggedIn])
        {
            if(AccountData[i][pDutyTrans]) count ++;
        }
        if(rentid != -1)
        {
            switch(RentalData[rentid][RentalType])
            {
                case 1: // Motorcycle
                {
                    if(count >= 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menggunakan Rental jika Trans Duty lebih dari 2 orang!");
                    
                    new title[100];
                    format(title, sizeof(title), ""TCRP"District  "WHITE"- Rental %02d", rentid);
                    Dialog_Show(playerid, DialogRents, DIALOG_STYLE_TABLIST_HEADERS, title, 
                    "Jenis Kendaraan\tHarga Rental\
                    \nFaggio\t$1000\
                    \n"GRAY"Wayfarer\t"GRAY"$1500\
                    \n"YELLOW"> Pilih ini untuk mengembalikan kendaraan yang disewa dari negara.", "Pilih", "Batal");
                }
                case 2: // Boat
                {
                    new title[100];
                    format(title, sizeof(title), ""TCRP"District  "WHITE"- Rental %02d", rentid);
                    Dialog_Show(playerid, DialogRents, DIALOG_STYLE_TABLIST_HEADERS, title, 
                    "Jenis Kendaraan\tHarga Rental\
                    \nSpeeder\t$1500\
                    \n"GRAY"Jetmax\t"GRAY"$2000\
                    \n"YELLOW"> Pilih ini untuk mengembalikan kendaraan yang disewa dari negara.", "Pilih", "Batal");
                }
            }

        }
    }
    return 1;
}

Dialog:DialogRents(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;
    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
    new id = RentalNearest(playerid);
    if(id == -1) return 0;
    switch(RentalData[id][RentalType])
    {
        case 1: // Motor
        {
            switch(listitem)
            {
                case 0://
                {
                    if(AccountData[playerid][pMoney] < 1000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    new count = 0;
                    foreach(new i : PvtVehicles)
                    {
                        if(PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
                            count ++;
                    }

                    if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");

                    TakeMoney(playerid, 1000);
                    VehicleRental_Create(playerid, 462, RentalData[id][RentalTimer], id, RentalData[id][RentalSpawn][0], RentalData[id][RentalSpawn][1], RentalData[id][RentalSpawn][2], RentalData[id][RentalSpawn][3], random(225), random(225), 1000, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
                }
                case 1:
                {
                    if(AccountData[playerid][pMoney] < 1500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    new count = 0;
                    foreach(new i : PvtVehicles)
                    {
                        if(PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
                            count ++;
                    }

                    if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");

                    TakeMoney(playerid, 1500);
                    VehicleRental_Create(playerid, 586, RentalData[id][RentalTimer], id, RentalData[id][RentalSpawn][0], RentalData[id][RentalSpawn][1], RentalData[id][RentalSpawn][2], RentalData[id][RentalSpawn][3], random(225), random(225), 1500, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
                }
                case 2: //Kembalikan
                {
                    if(Vehicle_RentalCount(playerid) < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki kendaraan rental apapun!");
                    foreach(new i : PvtVehicles) if(PlayerVehicle[i][pVehExists]) if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]) && !IsABoat(PlayerVehicle[i][pVehPhysic]))
                    {
                        if(PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
                        {
                            if(PlayerVehicle[i][pVehRental] != -1 && PlayerVehicle[i][pVehRentTime] != 0)
                            {
                                PlayerVehicle[i][pVehExists] = false;
                                PlayerVehicle[i][pVehRental] = -1;
                                PlayerVehicle[i][pVehOwnerID] = -1;
                                PlayerVehicle[i][pVehRentTime] = 0;

                                if(IsValidVehicle(PlayerVehicle[i][pVehPhysic])) DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
                                PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;

                                ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengembalikan semua kendaraan rental anda!");

                                mysql_tquery(g_SQL, sprintf("DELETE FROM player_vehicles WHERE id = '%d'", PlayerVehicle[i][pVehID]));
                                
                                Vehicle_ResetVariable(i);
                                Iter_Remove(PvtVehicles, i);
                            }
                        }
                    }
                }
            }
        }
        case 2: // Boat
        {
            switch(listitem)
            {
                case 0://
                {
                    if(AccountData[playerid][pMoney] < 1500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    new count = 0;
                    foreach(new i : PvtVehicles)
                    {
                        if(PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
                            count ++;
                    }

                    if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");

                    TakeMoney(playerid, 1500);
                    VehicleRental_Create(playerid, 452, RentalData[id][RentalTimer], id, RentalData[id][RentalSpawn][0], RentalData[id][RentalSpawn][1], RentalData[id][RentalSpawn][2], RentalData[id][RentalSpawn][3], random(225), random(225), 1500, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
                }
                case 1:
                {
                    if(AccountData[playerid][pMoney] < 2000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    new count = 0;
                    foreach(new i : PvtVehicles)
                    {
                        if(PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
                            count ++;
                    }

                    if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");

                    TakeMoney(playerid, 2000);
                    VehicleRental_Create(playerid, 493, RentalData[id][RentalTimer], id, RentalData[id][RentalSpawn][0], RentalData[id][RentalSpawn][1], RentalData[id][RentalSpawn][2], RentalData[id][RentalSpawn][3], random(225), random(225), 2000, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
                }
                case 2: //Kembalikan
                {
                    if(Vehicle_RentalCount(playerid) < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki kendaraan rental apapun!");
                    foreach(new i : PvtVehicles) if(PlayerVehicle[i][pVehExists]) if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]) && IsABoat(PlayerVehicle[i][pVehPhysic]))
                    {
                        if(PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
                        {
                            if(PlayerVehicle[i][pVehRental] != -1 && PlayerVehicle[i][pVehRentTime] != 0)
                            {
                                PlayerVehicle[i][pVehExists] = false;
                                PlayerVehicle[i][pVehRental] = -1;
                                PlayerVehicle[i][pVehOwnerID] = -1;
                                PlayerVehicle[i][pVehRentTime] = 0;

                                if(IsValidVehicle(PlayerVehicle[i][pVehPhysic])) DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
                                PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;

                                ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengembalikan semua kendaraan rental anda!");

                                mysql_tquery(g_SQL, sprintf("DELETE FROM player_vehicles WHERE id = '%d'", PlayerVehicle[i][pVehID]));
                                
                                Vehicle_ResetVariable(i);
                                Iter_Remove(PvtVehicles, i);
                            }
                        }
                    }
                }
            }
        }
    }
    return 1;
}

VehicleRental_Create(playerid, modelid, rentaltime, rentalid, Float:x, Float:y, Float:z, Float:angle, color1, color2, price, worldid, interiorid)
{
    new i = Iter_Free(PvtVehicles), cQuery[1048];

    if (i == INVALID_ITERATOR_SLOT)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuat kendaraan player!");
    
    PlayerVehicle[i][pVehExists] = true;

    PlayerVehicle[i][pVehOwnerID] = AccountData[playerid][pID];
    PlayerVehicle[i][pVehModelID] = modelid;
    PlayerVehicle[i][pVehParked] = -1;
    PlayerVehicle[i][pVehFactStored] = -1;
    PlayerVehicle[i][pVehHouseGarage] = -1;
    PlayerVehicle[i][pVehHelipadGarage] = -1;
    PlayerVehicle[i][pVehFamiliesGarage] = -1;

    format(PlayerVehicle[i][pVehPlate], 64, "Rental");

    PlayerVehicle[i][pVehRental] = rentalid;
    PlayerVehicle[i][pVehRentTime] = gettime() + rentaltime;

    PlayerVehicle[i][pVehPos][0] = x;
    PlayerVehicle[i][pVehPos][1] = y;
    PlayerVehicle[i][pVehPos][2] = z;
    PlayerVehicle[i][pVehPos][3] = angle;

    PlayerVehicle[i][pVehColor1] = color1;
    PlayerVehicle[i][pVehColor2] = color2;
    PlayerVehicle[i][pVehPaintjob] = -1;
    PlayerVehicle[i][pVehPrice] = price;

    PlayerVehicle[i][pVehLocked] = false;
	PlayerVehicle[i][pVehFuel] = MAX_FUEL_FULL;
	PlayerVehicle[i][pVehHealth] = 1500.0;
	PlayerVehicle[i][pVehFaction] = FACTION_NONE;

	PlayerVehicle[i][pVehNeon] = 0;
	PlayerVehicle[i][cTogNeon] = 0;
	
	PlayerVehicle[i][pVehDamage][0] = 0;
	PlayerVehicle[i][pVehDamage][1] = 0;
	PlayerVehicle[i][pVehDamage][2] = 0;
	PlayerVehicle[i][pVehDamage][3] = 0;

	PlayerVehicle[i][pVehPlateTime] = 0;
	PlayerVehicle[i][pVehPlateOwn] = 0;
	PlayerVehicle[i][pVehInterior] = interiorid;
	PlayerVehicle[i][pVehWorld] = worldid;

    PlayerVehicle[i][pVehEngineUpgrade] = 0;
	PlayerVehicle[i][pVehBodyUpgrade] = 0;
	PlayerVehicle[i][pVehBodyRepair] = 0;
	
	PlayerVehicle[i][pVehBroken] = 0;
	PlayerVehicle[i][pVehInsuranced] = false;
    PlayerVehicle[i][pVehImpounded] = false;
    PlayerVehicle[i][pVehImpoundReason] = EOS;

	PlayerVehicle[i][vehDonation] = 0;
	PlayerVehicle[i][pVehCapacity] = 0;
	PlayerVehicle[i][pVehDCTime] = 0;
    
    PlayerVehicle[i][pVehWeapon][0] = 0;
	PlayerVehicle[i][pVehWeapon][1] = 0;
	PlayerVehicle[i][pVehWeapon][2] = 0;
	PlayerVehicle[i][pVehAmmo][0] = 0;
	PlayerVehicle[i][pVehAmmo][1] = 0;
	PlayerVehicle[i][pVehAmmo][2] = 0;

    for(new m = 0; m < 17; m++){
		PlayerVehicle[i][pVehMod][m] = 0;}

    PlayerVehicle[i][pVehPhysic] = CreateVehicle(PlayerVehicle[i][pVehModelID], PlayerVehicle[i][pVehPos][0], PlayerVehicle[i][pVehPos][1], PlayerVehicle[i][pVehPos][2], PlayerVehicle[i][pVehPos][3], PlayerVehicle[i][pVehColor1], PlayerVehicle[i][pVehColor2], 60000, 0);
    VehicleCore[PlayerVehicle[i][pVehPhysic]][vCoreFuel] = PlayerVehicle[i][pVehFuel];
    SetVehicleNumberPlate(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehPlate]);
    SetVehicleVirtualWorld(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehWorld]);
    LinkVehicleToInterior(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehInterior]);
    SetValidVehicleHealth(PlayerVehicle[i][pVehPhysic], PlayerVehicle[i][pVehHealth]);

    Iter_Add(PvtVehicles, i);

    mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `player_vehicles` (`PVeh_OwnerID`, `PVeh_ModelID`, `PVeh_Parked`, `PVeh_Housed`, `PVeh_RentTime`, `PVeh_Rental`, `PVeh_Plate`, `PVeh_Health`, `PVeh_Fuel`, `PVeh_PosX`, `PVeh_PosY`, `PVeh_PosZ`, `PVeh_PosA`, \
    `PVeh_Color1`, `PVeh_Color2`, `PVeh_Paintjob`, `PVeh_World`, `PVeh_Interior`) VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%s', '%f', '%d', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '%d')", PlayerVehicle[i][pVehOwnerID], PlayerVehicle[i][pVehModelID], PlayerVehicle[i][pVehParked], PlayerVehicle[i][pVehHouseGarage], 
    PlayerVehicle[i][pVehRentTime], PlayerVehicle[i][pVehRental], PlayerVehicle[i][pVehPlate], PlayerVehicle[i][pVehHealth], PlayerVehicle[i][pVehFuel], PlayerVehicle[i][pVehPos][0], PlayerVehicle[i][pVehPos][1], PlayerVehicle[i][pVehPos][2], PlayerVehicle[i][pVehPos][3], PlayerVehicle[i][pVehColor1], PlayerVehicle[i][pVehColor2], PlayerVehicle[i][pVehPaintjob], PlayerVehicle[i][pVehWorld], PlayerVehicle[i][pVehInterior]);
    mysql_tquery(g_SQL, cQuery, "OnVehRentalCreated", "ii", playerid, i);
    return 1;
}

ptask VehRent_Update[1000](playerid)
{
    // Iterasi langsung pada array PvtVehicles
    foreach(new i:PvtVehicles)
    {
        // Cek apakah kendaraan valid dan milik pemain
        if (PlayerVehicle[i][pVehExists])
        {
            if(PlayerVehicle[i][pVehRental] >= 0 && PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
            {
                // Jika waktu sewa sudah habiss
                if (PlayerVehicle[i][pVehRentTime] != 0 && PlayerVehicle[i][pVehRentTime] <= gettime())
                {
                    // Reset variabel kendaraan
                    PlayerVehicle[i][pVehExists] = false;
                    PlayerVehicle[i][pVehRental] = -1;
                    PlayerVehicle[i][pVehRentTime] = 0;
                    PlayerVehicle[i][pVehOwnerID] = -1;

                    // Hapus kendaraan fisik jika ada
                    if (IsValidVehicle(PlayerVehicle[i][pVehPhysic])) 
                    {
                        DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
                        PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;
                    }

                    // Persiapkan query untuk menghapus kendaraan dari database
                    new query[200];
                    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `player_vehicles` WHERE `id`= %d", PlayerVehicle[i][pVehID]);
                    mysql_tquery(g_SQL, query);

                    // Reset variabel kendaraan dan hapus dari array PvtVehicles
                    Vehicle_ResetVariable(i);
                    Iter_Remove(PvtVehicles, i);
                }
            }
        }
    }
    return 1;
}
