#include <YSI\y_hooks>

#define IsTrashmasterWorking(%0)        trashmaster_working[%0]
#define SetTrashmasterWorking(%0,%1)    trashmaster_working[%0] = %1

IsTrashmasterVehicles(vehicleid)
{
    for(new i = 0; i < sizeof(TrashmasterVehicles); i++)
    {
        if(vehicleid == TrashmasterVehicles[i]) return 1;
    }
    return 0;
}

new
    bool:trashmaster_working[MAX_PLAYERS] = {false, ...},
    TrashTaked[MAX_PLAYERS] = {0, ...},
    TrashmasterVehicleID[MAX_PLAYERS] = RETURN_INVALID_VEHICLE_ID,
    TrashmasterRespawnCounter[MAX_PLAYERS] = {0, ...},
    TrashmasterCarryTrash[MAX_PLAYERS] = {0, ...},
    STREAMER_TAG_CP:TrashmasterCheckpoint[MAX_PLAYERS][MAX_DYNAMIC_TRASH],
    STREAMER_TAG_CP:TrashmasterTrunkCP[MAX_PLAYERS];

hook OnPlayerConnect(playerid)
{
    TrashTaked[playerid] = 0;
    TrashmasterVehicleID[playerid] = RETURN_INVALID_VEHICLE_ID;
    TrashmasterRespawnCounter[playerid] = 0;
    SetTrashmasterWorking(playerid, false);
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(IsTrashmasterWorking(playerid))
    {
        TrashmasterRespawnCounter[playerid] = 0;
        SetVehicleToRespawn(TrashmasterVehicleID[playerid]);
        VehicleCore[TrashmasterVehicleID[playerid]][vCoreFuel] = MAX_FUEL_FULL;
        TrashmasterVehicleID[playerid] = RETURN_INVALID_VEHICLE_ID;
        for(new x = 0; x < MAX_DYNAMIC_TRASH; x ++)
        {
            RemovePlayerMapIcon(playerid, x);
            if(DestroyDynamicCP(TrashmasterCheckpoint[playerid][x])) TrashmasterCheckpoint[playerid][x] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        }
    }
    return 1;
}

hook OnGameModeInitEx()
{
    TrashmasterVehicles[0] = AddStaticVehicleEx(408, 1045.1128, -290.4416, 74.6314, 181.0521, 1, 1, -1, 0);
    TrashmasterVehicles[1] = AddStaticVehicleEx(408, 1039.2145, -290.5728, 74.6374, 180.6139, 1, 1, -1, 0);
    TrashmasterVehicles[2] = AddStaticVehicleEx(408, 1032.6494, -290.5948, 74.6364, 177.6104, 1, 1, -1, 0);
    for(new i = 0; i < sizeof(TrashmasterVehicles); i ++)
    {
        VehicleCore[TrashmasterVehicles[i]][vCoreFuel] = MAX_FUEL_FULL;
        SetValidVehicleHealth(TrashmasterVehicles[i], 1000.0);
        SetVehicleNumberPlate(TrashmasterVehicles[i], "TRASHMASTER");
    }
    CreateDynamicPickup(1239, 23, 1050.1172, -287.0053, 74.0922 + 0.15, -1, -1, -1, 10.0);
    CreateDynamic3DTextLabel(""DEEPSKYBLUE1"[Trashmaster Point]", -1, 1050.1172, -287.0053, 74.0922 + 1.0, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER)
    {
        if(!AccountData[playerid][pAdminDuty] && !IsTrashmasterWorking(playerid) && IsTrashmasterVehicles(GetPlayerVehicleID(playerid)))
        {
            if(!AccountData[playerid][pTrashmasterDelay])
            {
                SetCameraBehindPlayer(playerid);
                ShowPlayerDialog(playerid, DIALOG_TRASHMASTER_START, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Trashmaster Sidejob",
                ""WHITE"Pekerjaan ini bertujuan untuk mengambil sampah di setiap garbage.\nAnda bisa temukan sampah sampah yang ada di setiap kota "WHITE"ini. Ikuti petunjuk "RED"radar "WHITE"yang di sediakan.\n Itu merupahan lokasi yang harus anda tuju.\n\
                    \n\n"RED"WARNING: "WHITE"Turun dari kendaraan untuk mengambil sampah dan menaruhnya ke kendaraan.", "Iya", "Tidak");
            }
            else
            {
                ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Anda harus menunggu %d menit untuk bekerja kembali!", AccountData[playerid][pTrashmasterDelay]/60));
                return RemovePlayerFromVehicle(playerid);
            }
        }
        if(IsTrashmasterWorking(playerid) && IsTrashmasterVehicles(GetPlayerVehicleID(playerid)))
        {
            if(GetPlayerVehicleID(playerid) != TrashmasterVehicleID[playerid])
            {
                ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan kendaraan trashmaster anda!");
                return RemovePlayerFromVehicle(playerid);
            }
            TrashmasterVehicleID[playerid] = GetPlayerVehicleID(playerid);
            TrashmasterRespawnCounter[playerid] = 0;
            RemovePlayerAttachedObject(playerid, JOB_SLOT);
            SwitchVehicleObjective(GetPlayerVehicleID(playerid), false);
        }
    }
    if(oldstate == PLAYER_STATE_DRIVER && IsTrashmasterWorking(playerid))
    {
        new Float:cX, Float:cY, Float:cZ;
        SwitchVehicleObjective(TrashmasterVehicleID[playerid], true);
        GetVehicleBoot(TrashmasterVehicleID[playerid], cX, cY, cZ);
        SetPVarFloat(playerid, "TrunkX", cX);
        SetPVarFloat(playerid, "TrunkY", cY);
        SetPVarFloat(playerid, "TrunkZ", cZ);
        TrashmasterRespawnCounter[playerid] = 60;
    }
    return 1;
}

stock TrashPickup(playerid)
{
    SetPlayerAttachedObject(playerid, JOB_SLOT, 1264, 6, 0.217, -0.094, 0.082, -6.7, -114.4, -76.5, 0.631, 0.709, 0.557);
    TrashmasterCarryTrash[playerid] = 1;
    return 1;
}

stock TrashDrop(playerid)
{
    ClearAnimations(playerid, 1);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    RemovePlayerAttachedObject(playerid, JOB_SLOT);
    TrashmasterCarryTrash[playerid] = 0;
    return 1;
}

CancelTrashmaster(playerid, vehicleid)
{
    if(IsTrashmasterWorking(playerid))
    {
        TrashDrop(playerid);
        TrashmasterVehicleID[playerid] = RETURN_INVALID_VEHICLE_ID;
        TrashTaked[playerid] = 0;
        SetTrashmasterWorking(playerid, false);
        DisablePlayerRaceCheckpoint(playerid);
        SetPVarInt(playerid, "SelesaiTrashmaster", 0);
        SetPVarFloat(playerid, "TrunkX", 0.0);
        SetPVarFloat(playerid, "TrunkY", 0.0);
        SetPVarFloat(playerid, "TrunkZ", 0.0);

        SetVehicleToRespawn(vehicleid);
        VehicleCore[vehicleid][vCoreFuel] = MAX_FUEL_FULL;
        TrashmasterRespawnCounter[playerid] = 0;

        for (new x = 0; x < MAX_DYNAMIC_TRASH; x ++)
        {
            RemovePlayerMapIcon(playerid, x);
            if(DestroyDynamicCP(TrashmasterCheckpoint[playerid][x])) TrashmasterCheckpoint[playerid][x] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        }
    }
    return 1;
}

hook OnPlayerEnterRaceCP(playerid)
{
    if(IsTrashmasterWorking(playerid) && GetPVarInt(playerid, "SelesaiTrashmaster") == 1)
    {
        if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada dikemudi kendaraan!");
        GiveMoney(playerid, 3500);
        ShowItemBox(playerid, "Received $3,000", "Uang", 1212);
        AccountData[playerid][pTrashmasterDelay] = 2700;

        CancelTrashmaster(playerid, GetPlayerVehicleID(playerid));
    }
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(IsTrashmasterWorking(playerid))
    {
        for (new i = 0; i < MAX_DYNAMIC_TRASH; i++)
        {
            if(checkpointid == TrashmasterCheckpoint[playerid][i] && IsPlayerInDynamicCP(playerid, TrashmasterCheckpoint[playerid][i]))
            {
                if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada diluar kendaraan!");    
                if(TrashTaked[playerid] < 25)
                {
                    TrashTaked[playerid] += 1;
                    if(DestroyDynamicCP(TrashmasterCheckpoint[playerid][i])) TrashmasterCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                    RemovePlayerMapIcon(playerid, i);

                    new Float:cX, Float:cY, Float:cZ;
                    cX = GetPVarFloat(playerid, "TrunkX");
                    cY = GetPVarFloat(playerid, "TrunkY");
                    cZ = GetPVarFloat(playerid, "TrunkZ");
                    ApplyAnimationEx(playerid, "PED", "WALK_armed", 4.1, 1, 1, 1, 1, 1, 1);
                    TrashPickup(playerid);
                    TrashmasterTrunkCP[playerid] = CreateDynamicCP(cX, cY, cZ, 1.5, 0, 0, playerid, 20.0, -1, 0);
                }
            }
        }
        
        if(checkpointid == TrashmasterTrunkCP[playerid] && IsPlayerInDynamicCP(playerid, TrashmasterTrunkCP[playerid]))
        {
            if(TrashTaked[playerid] < 25)
            {
                if(DestroyDynamicCP(TrashmasterTrunkCP[playerid])) TrashmasterTrunkCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                ApplyAnimationEx(playerid, "GRENADE", "WEAPON_throwu", 4.1, 0, 0, 0, 0, 0, 1);
                RemovePlayerAttachedObject(playerid, JOB_SLOT);
                PlayerTextDrawSetString(playerid, BusWait[playerid][0], sprintf("~y~%d/25~w~ Sampah ~r~Terkumpul", TrashTaked[playerid]));
                PlayerTextDrawShow(playerid, BusWait[playerid][0]);
                SetTimerEx("HideNotifDelivery", 6000, false, "d", playerid);
            }
            else
            {
                if(DestroyDynamicCP(TrashmasterTrunkCP[playerid])) TrashmasterTrunkCP[playerid] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                TrashTaked[playerid] = 25;
                TrashDrop(playerid);
                Info(playerid, "25 sampah telah terkumpul di kendaraan ini. Silahkan ikuti checkpoint untuk mengambil gaji");
                SetPVarInt(playerid, "SelesaiTrashmaster", 1);
                SetPlayerRaceCheckpoint(playerid, 1, 1014.4263, -307.2356, 74.0922, 0.0, 0.0, 0.0, 5.0);

                for(new x = 0; x < MAX_DYNAMIC_TRASH; x ++)
                {
                    if(DestroyDynamicCP(TrashmasterCheckpoint[playerid][x]))
                        TrashmasterCheckpoint[playerid][x] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                    
                    RemovePlayerMapIcon(playerid, x);
                }
            }
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_TRASHMASTER_START:
        {
            if(response)
            {
                TrashmasterVehicleID[playerid] = GetPlayerVehicleID(playerid);
                SwitchVehicleEngine(GetPlayerVehicleID(playerid), true);

                for (new x = 0; x < MAX_DYNAMIC_TRASH; x ++)
                {
                    if(DestroyDynamicCP(TrashmasterCheckpoint[playerid][x])) TrashmasterCheckpoint[playerid][x] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                    RemovePlayerMapIcon(playerid, x);

                    if(TrashData[x][trashPos][0] != 0.0 && TrashData[x][trashInt] == 0)
                    {
                        TrashmasterCheckpoint[playerid][x] = CreateDynamicCP(TrashData[x][trashPos][0], TrashData[x][trashPos][1] - 0.35, TrashData[x][trashPos][2], 2.0, 0, 0, playerid, 10.0, -1, 0);
                        SetPlayerMapIcon(playerid, x, TrashData[x][trashPos][0], TrashData[x][trashPos][1], TrashData[x][trashPos][2], 0, 0xFF0000FF, MAPICON_GLOBAL);
                    }
                    SetPVarInt(playerid, "TrashWork", 1);
                    SetTrashmasterWorking(playerid, true);
                    PlayerTextDrawSetString(playerid, BusWait[playerid][0], "~g~Sidejob Trash Collector: ~w~Pergi dan angkut ~y~25~n~~y~trash~w~ ke tempat yang telah ditandai~n~dengan ~r~icon~w~ pada map!");
                    PlayerTextDrawShow(playerid, BusWait[playerid][0]);
                    SetTimerEx("HideNotifDelivery", 10000, false, "d", playerid);
                }
            }
            else
            {
                Error(playerid, "Anda menolak bekerja sebagai trash collector");
                RemovePlayerFromVehicle(playerid);
            }
        }
    }
    return 1;
}
ptask RespawnTrashmasterVehicle[1000](playerid)
{
    if (SQL_IsCharacterLogged(playerid) && IsTrashmasterWorking(playerid))
    {
        // Simpan nilai counter dalam variabel lokal untuk mengurangi akses array berulang
        new counter = TrashmasterRespawnCounter[playerid];
        
        // Hanya lanjutkan jika counter tidak nol
        if (counter > 0)
        {
            counter--;
            
            // Jika counter mencapai nol, hentikan misi dan beri pesan
            if (counter == 0)
            {
                CancelTrashmaster(playerid, TrashmasterVehicleID[playerid]);
                Error(playerid, "Anda telah gagal menjadi pekerja Trash Collector!");
            }
            
            // Mainkan suara dan beri pesan kepada pemain
            PlayerPlaySound(playerid, 1056, 0.0, 0.0, 0.0);
            GameTextForPlayer(playerid, sprintf("~y~Kembali ke kendaraan~n~~r~%d detik", TrashmasterRespawnCounter[playerid]), 1000, 6);
        }
    }
    return 1;
}
