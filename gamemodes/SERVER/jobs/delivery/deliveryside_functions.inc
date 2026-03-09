#include <YSI\y_hooks>

/* Defined */
#define IsDeliveryWorking(%0)       delivery_working[%0]
#define SetDeliveryWorking(%0,%1)   delivery_working[%0] = %1

IsDeliveryVehicles(vehicleid)
{
    for(new i = 0; i < sizeof(DeliveryVehicles); i ++)
    {
        if(vehicleid == DeliveryVehicles[i]) return 1;
    }
    return 0;
}
/* Vars */
new
    HouseDelivered[MAX_PLAYERS] = {0, ...},
    bool:delivery_working[MAX_PLAYERS] = {false, ...},
    DeliveryVehicleID[MAX_PLAYERS] = {RETURN_INVALID_VEHICLE_ID, ...},
    DeliveryRespawnCounter[MAX_PLAYERS] = {0, ...},
    DeliveryCarryPacket[MAX_PLAYERS] = {0, ...},
    STREAMER_TAG_CP:DeliveryCheckpoint[MAX_PLAYERS][10] = {INVALID_STREAMER_ID, ...},
    STREAMER_TAG_MAP_ICON:DeliveryIcon[MAX_PLAYERS][10] = {INVALID_STREAMER_ID, ...}
;

static Float:DeliveryPoint[10][3] = 
{
    {725.3630, -1276.2968, 13.6484},
    {841.0327, -1471.5468, 14.2162},
    {1094.9868, -647.7197, 113.6484},
    {2470.3723, -1295.6129, 30.2332},
    {300.0987, -1154.3085, 81.3900},
    {1497.0000, -687.8920, 95.5633},
    {980.3992, -677.3172, 121.9763},
    {2756.3333, -1182.7914, 69.4034},
    {1093.8484, -807.1465, 107.4199},
    {864.8474, -1633.9808, 14.9297}
};

hook OnPlayerConnect(playerid)
{
    HouseDelivered[playerid] = 0;
    DeliveryVehicleID[playerid] = RETURN_INVALID_VEHICLE_ID;
    DeliveryRespawnCounter[playerid] = 0;
    DeliveryCarryPacket[playerid] = 0;
    SetDeliveryWorking(playerid, false);
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(IsDeliveryWorking(playerid))
    {
        DeliveryRespawnCounter[playerid] = 0;
        SetVehicleToRespawn(DeliveryVehicleID[playerid]);
        SetValidVehicleHealth(DeliveryVehicleID[playerid], 1000.0);
        VehicleCore[DeliveryVehicleID[playerid]][vCoreFuel] = MAX_FUEL_FULL;
        DeliveryVehicleID[playerid] = RETURN_INVALID_VEHICLE_ID;
        for(new x = 0; x < 10; x ++)
        {
            if(DestroyDynamicCP(DeliveryCheckpoint[playerid][x])) DeliveryCheckpoint[playerid][x] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
            if(DestroyDynamicMapIcon(DeliveryIcon[playerid][x])) DeliveryIcon[playerid][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            // RemovePlayerMapIcon(playerid, x);
        }
    }
    return 1;
}

hook OnScriptInit()
{
    static tmpobjid;
    DeliveryVehicles[0] = AddStaticVehicleEx(609, 993.8989, -1434.7814, 13.6210, 182.1553, 1, 126, 60000);
    DeliveryVehicles[1] = AddStaticVehicleEx(609, 987.5372, -1434.7346, 13.6179, 178.9966, 1, 126, 60000);
    forex(i, sizeof(DeliveryVehicles))
    {
        VehicleCore[DeliveryVehicles[i]][vCoreFuel] = MAX_FUEL_FULL;
        SetVehicleNumberPlate(DeliveryVehicles[i], "ShopeeXpress");
        tmpobjid = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
        SetDynamicObjectMaterialText(tmpobjid, 0, "{FFFFFF}Shopee", 130, "Arial", 50, 0, 0, 0, 1);
        AttachDynamicObjectToVehicle(tmpobjid, DeliveryVehicles[i], -1.210, -0.150, 1.069, 0.000, 0.000, 180.000);
        tmpobjid = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
        SetDynamicObjectMaterialText(tmpobjid, 0, "{FFFFFF}X", 130, "Arial", 60, 1, 0, 0, 1);
        AttachDynamicObjectToVehicle(tmpobjid, DeliveryVehicles[i], -1.210, -1.130, 1.069, 0.000, 0.000, 180.000);
        tmpobjid = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
        SetDynamicObjectMaterialText(tmpobjid, 0, "{FFFFFF}PRESS", 130, "Arial", 40, 1, 0, 0, 1);
        AttachDynamicObjectToVehicle(tmpobjid, DeliveryVehicles[i], -1.210, -1.949, 1.009, 0.000, 0.000, 180.000);
        tmpobjid = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
        SetDynamicObjectMaterialText(tmpobjid, 0, "{FFFFFF}______", 130, "Arial", 40, 1, 0, 0, 1);
        AttachDynamicObjectToVehicle(tmpobjid, DeliveryVehicles[i], -1.210, -1.589, 1.489, 0.000, 0.000, 180.000);
        tmpobjid = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
        SetDynamicObjectMaterialText(tmpobjid, 0, "{FFFFFF}Shopee", 130, "Arial", 50, 0, 0, 0, 1);
        AttachDynamicObjectToVehicle(tmpobjid, DeliveryVehicles[i], 1.209, -1.971, 1.069, 0.000, 0.000, 0.000);
        tmpobjid = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
        SetDynamicObjectMaterialText(tmpobjid, 0, "{FFFFFF}X", 130, "Arial", 60, 1, 0, 0, 1);
        AttachDynamicObjectToVehicle(tmpobjid, DeliveryVehicles[i], 1.229, -0.990, 1.069, 0.000, 0.000, 0.000);
        tmpobjid = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
        SetDynamicObjectMaterialText(tmpobjid, 0, "{FFFFFF}PRESS", 130, "Arial", 40, 1, 0, 0, 1);
        AttachDynamicObjectToVehicle(tmpobjid, DeliveryVehicles[i], 1.230, -0.119, 1.009, 0.000, 0.000, 0.000);
        tmpobjid = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
        SetDynamicObjectMaterialText(tmpobjid, 0, "{FFFFFF}______", 130, "Arial", 40, 1, 0, 0, 1);
        AttachDynamicObjectToVehicle(tmpobjid, DeliveryVehicles[i], 1.240, -0.550, 1.489, 0.000, 0.000, 0.000);
        SetValidVehicleHealth(DeliveryVehicles[i], 1000.0);
    }
    CreateDynamicPickup(1239, 23, 1000.6937, -1432.9775, 13.5469 + 0.15, -1, -1, -1, 10.0);
    CreateDynamic3DTextLabel(""DEEPSKYBLUE1"[Delivery Point]", -1, 1000.6937, -1432.9775, 13.5469 + 1.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(!AccountData[playerid][pAdminDuty] && !IsDeliveryWorking(playerid) && IsDeliveryVehicles(vehicleid))
        {
            if(AccountData[playerid][pDeliveryTime] == 0)
            {
                SetCameraBehindPlayer(playerid);
                ShowPlayerDialog(playerid, DIALOG_DELIVERY_START, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Delivery Sidejob",
                ""WHITE"Pekerjaan ini bertujuan untuk mengantarkan paket ke setiap rumah.\nAnda bisa temukan rumah rumah yang ada di setiap kota "WHITE"ini. Ikuti petunjuk "RED"radar "WHITE"yang di sediakan.\n Itu merupahan lokasi yang harus anda tuju.\n\
                    \n\n"RED"WARNING: "WHITE"Turun dari kendaraan untuk mengambil box packet dan menaruhnya ke depan rumah.", "Iya", "Tidak");
            }
            else
            {
                ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Anda harus menunggu %d menit untuk bekerja kembali!", AccountData[playerid][pDeliveryTime]/60));
                return RemovePlayerFromVehicle(playerid);
            }
        }
        if(IsDeliveryWorking(playerid) && IsDeliveryVehicles(GetPlayerVehicleID(playerid)))
        {
            if(vehicleid != DeliveryVehicleID[playerid])
            {
                ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan kendaraan delivery anda!");
                return RemovePlayerFromVehicle(playerid);
            }
            DeliveryVehicleID[playerid] = vehicleid;
            DeliveryRespawnCounter[playerid] = 0;
            RemovePlayerAttachedObject(playerid, JOB_SLOT);
        }
    }
    if(oldstate == PLAYER_STATE_DRIVER && IsDeliveryWorking(playerid))
    {
        SendCustomMessage(playerid, "HINT", "Tekan "RED"H"WHITE" Di dekat kendaraan untuk mengambil paket yang ingin diantarkan kedepan rumah");
        SwitchVehicleObjective(DeliveryVehicleID[playerid], true);
        DeliveryRespawnCounter[playerid] = 90;
    }

    return 1;
}

stock DeliveryPickup(playerid)
{
    SetPlayerAttachedObject(playerid, JOB_SLOT, 1271, 1,0.237980,0.473312,-0.066999, 1.099999,88.000007,-177.400085, 0.716000,0.572999,0.734000);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
	DeliveryCarryPacket[playerid] = 1;
	return 1;
}

stock DeliveryDrop(playerid)
{
    ClearAnimations(playerid, 1);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    RemovePlayerAttachedObject(playerid, JOB_SLOT);
    DeliveryCarryPacket[playerid] = 0;
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CTRL_BACK && IsDeliveryWorking(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new vehicle_nearest = GetNearestVehicleToPlayer(playerid, 3.0, false);
        if(GetVehicleModel(vehicle_nearest) == 609 && vehicle_nearest == DeliveryVehicleID[playerid])
        {
            if(!DeliveryCarryPacket[playerid])
            {
                DeliveryPickup(playerid);
            }
            else
            {
                DeliveryDrop(playerid);
            }
        }
    }
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(IsDeliveryWorking(playerid))
    {
        for(new i = 0; i < sizeof(DeliveryPoint); i ++)
        {
            if(checkpointid == DeliveryCheckpoint[playerid][i])
            {
                if(!DeliveryCarryPacket[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ambil dulu paket yang berada didalam kendaraan!");
                if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus turun dari kendaraan!");
                if(DestroyDynamicCP(DeliveryCheckpoint[playerid][i])) DeliveryCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                if(DestroyDynamicMapIcon(DeliveryIcon[playerid][i])) DeliveryIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
                // RemovePlayerMapIcon(playerid, i);
                HouseDelivered[playerid] ++;

                if(HouseDelivered[playerid] < 10)
                {
                    DeliveryDrop(playerid);
                    ShowPlayerFooter(playerid, sprintf("~y~%d/10~w~ paket telah diantarkan", HouseDelivered[playerid]), 5000);
                }
                else
                {
                    HouseDelivered[playerid] = 10;
                    DeliveryDrop(playerid);
                    Info(playerid, "Semua paket telah habis diantarkan, ikuti tanda di map untuk mengambl gaji anda!");
                    SetPVarInt(playerid, "SelesaiDelivery", 1);
                    SetPlayerRaceCheckpoint(playerid, 1, 996.8121, -1445.0454, 13.5469, 996.8121, -1445.0454, 13.5469, 5.0);
                }
            }
        }
    }
    return 1;
}

CancelDelivery(playerid, vehicleid)
{
    if(IsDeliveryWorking(playerid))
    {
        DeliveryDrop(playerid);
        DeliveryVehicleID[playerid] = RETURN_INVALID_VEHICLE_ID;
        HouseDelivered[playerid] = 0;
        SetDeliveryWorking(playerid, false);
        DisablePlayerRaceCheckpoint(playerid);
        SetPVarInt(playerid, "SelesaiDelivery", 0);

        SetVehicleToRespawn(vehicleid);
        SwitchVehicleObjective(vehicleid, false);
        VehicleCore[vehicleid][vCoreFuel] = MAX_FUEL_FULL;
        SetValidVehicleHealth(vehicleid, 1000.0);
        DeliveryRespawnCounter[playerid] = 0;

        for(new x = 0; x < 10; x ++) 
        {
            // RemovePlayerMapIcon(playerid, x);

            if(DestroyDynamicMapIcon(DeliveryIcon[playerid][x])) 
                DeliveryIcon[playerid][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

            if(DestroyDynamicCP(DeliveryCheckpoint[playerid][x])) 
                DeliveryCheckpoint[playerid][x] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        }
    }
    return 1;
}

hook OnPlayerEnterRaceCP(playerid)
{
    if(IsDeliveryWorking(playerid) && GetPVarInt(playerid, "SelesaiDelivery") == 1)
    {
        if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengendarai kendaraan delivery!");
        GiveMoney(playerid, 1500);
        ShowItemBox(playerid, "Received $1,500", "Uang", 1212);
        AccountData[playerid][pDeliveryTime] = 1800;

        CancelDelivery(playerid, GetPlayerVehicleID(playerid));
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_DELIVERY_START:
        {
            if(response)
            {
                DeliveryVehicleID[playerid] = GetPlayerVehicleID(playerid);
                SwitchVehicleEngine(GetPlayerVehicleID(playerid), true);

                SendCustomMessage(playerid, "HINT", "Ikuti tanda radar di map, itu merupakan lokasi untuk menemukan rumah");
                SendCustomMessage(playerid, "HINT", "Tekan "YELLOW"H "WHITE"Di dekat kendaraan delivery dan bawa paket ke checkpoint rumah");
                SendClientMessage(playerid, X11_WHITE, "Setelah semuanya selesai anda akan kembali ke tempat awal anda mengambil kendaraan untuk..");
                SendClientMessage(playerid, X11_WHITE, ".. mengambil upah anda");

                for (new i; i < sizeof(DeliveryPoint); i ++)
                {
                    // RemovePlayerMapIcon(playerid, i);
                    if(DestroyDynamicMapIcon(DeliveryIcon[playerid][i])) DeliveryIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
                    if(DestroyDynamicCP(DeliveryCheckpoint[playerid][i])) DeliveryCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;

                    DeliveryCheckpoint[playerid][i] = CreateDynamicCP(DeliveryPoint[i][0], DeliveryPoint[i][1], DeliveryPoint[i][2], 2.0, 0, 0, playerid, 5.0, -1, 0);
                    DeliveryIcon[playerid][i] = CreateDynamicMapIcon(DeliveryPoint[i][0], DeliveryPoint[i][1], DeliveryPoint[i][2], 0, 0xFF0000FF, 0, 0, playerid, 6000.0, MAPICON_GLOBAL, -1, 0);
                    // SetPlayerMapIcon(playerid, i, DeliveryPoint[i][0], DeliveryPoint[i][1], DeliveryPoint[i][2], 0, 0xFF0000FF, MAPICON_GLOBAL);
                }
                SetDeliveryWorking(playerid, true);
                ShowPlayerFooter(playerid, "~g~Sidejob Delivery: ~w~Pergi dan antarkan ~y~10~n~~y~paket~w~ ke tempat yang telah ditandai~n~dengan ~r~icon~w~ pada map!", 5000);
            }
            else
            {
                Info(playerid, "Anda menolak bekerja sebagai delivery driver!");
                RemovePlayerFromVehicle(playerid);
            }
        } 
    }
    return 1;
}

ptask RespawnDeliveryVehicle[1000](playerid)
{
    if(SQL_IsCharacterLogged(playerid) && IsDeliveryWorking(playerid))
    {
        if(DeliveryRespawnCounter[playerid] != 0)
        {
            DeliveryRespawnCounter[playerid] --;
            if(DeliveryRespawnCounter[playerid] == 0)
            {
                CancelDelivery(playerid, DeliveryVehicleID[playerid]);
                SendCustomMessage(playerid, "ERROR", "Anda telah gagal menjalankan misi sebagai delivery!");
            }
            PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
            GameTextForPlayer(playerid, sprintf("~y~Kembali ke kendaraan~n~~r~%d detik", DeliveryRespawnCounter[playerid]), 1000, 6);
        }
    }
    return 1;
}

forward HideNotifDelivery(playerid);
public HideNotifDelivery(playerid)
{
    PlayerTextDrawHide(playerid, BusWait[playerid][0]);
    return 1;
}