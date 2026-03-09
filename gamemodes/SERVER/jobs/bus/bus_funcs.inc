#include <YSI\y_hooks>

new STREAMER_TAG_AREA:BusAirport,
    STREAMER_TAG_AREA:BusHospital,
    STREAMER_TAG_AREA:BusAnglePine,
    STREAMER_TAG_AREA:BusKanpol,
    STREAMER_TAG_OBJECT:BusObject,
    STREAMER_TAG_PICKUP:HaltePickup[15],
    STREAMER_TAG_3D_TEXT_LABEL:HalteAirportLabel[5],
    STREAMER_TAG_3D_TEXT_LABEL:HalteKanpolLabel[6],
    STREAMER_TAG_3D_TEXT_LABEL:HalteHospitalLabel[4],
    CountBusAirport,
    CountBusKanpol,
    CountBusHospital;

new bool: DurringBus[MAX_PLAYERS] = { false, ... },
    BusIndex[MAX_PLAYERS] = { 0, ... },
    BusWaiting[MAX_PLAYERS] = { false, ... },
    BusTime[MAX_PLAYERS] = { 0, ... },
    BusExitTimer[MAX_PLAYERS] = { 0, ... };

#define IsBusWorking(%0)        DurringBus[%0]
#define SetBusWorking(%0,%1)    DurringBus[%0] = %1 

enum 
{
    CHECKPOINT_BUS_INVALID = 0,
    CHECKPOINT_BUS_AIRPORT,
    CHECKPOINT_BUS_HOSPITAL,
    CHECKPOINT_BUS_ANGLEPINE,
    CHECKPOINT_BUS_KANPOL
}

enum e_job_bus_data
{
    STREAMER_TAG_MAP_ICON:BusIcon,
};
new PlayerVarsBus[MAX_PLAYERS][e_job_bus_data];

LoadPickupBus()
{
    static frmthalte[666];
    CountBusAirport = 0;
    CountBusKanpol = 0;
    CountBusHospital = 0;

    format(frmthalte, sizeof(frmthalte), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Airport\n%s -> %s\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(118.9531, -1459.3467, 24.3454), GetLocation(415.6029, -1778.9414, 5.5469), CountBusAirport);
    HalteAirportLabel[0] = CreateDynamic3DTextLabel(frmthalte, COLOR_WHITE, 118.9531, -1459.3467, 24.3454 + 1.1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
    format(frmthalte, sizeof(frmthalte), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Airport\n%s -> %s\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(415.6029, -1778.9414, 5.5469), GetLocation(1695.0912, -2247.4392, 13.5469), CountBusAirport);
    HalteAirportLabel[1] = CreateDynamic3DTextLabel(frmthalte, COLOR_WHITE, 415.6029, -1778.9414, 5.5469 + 1.1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
    format(frmthalte, sizeof(frmthalte), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Airport\n%s -> %s\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(1695.0912, -2247.4392, 13.5469), GetLocation(1326.6183, -917.9512, 37.0724), CountBusAirport);
    HalteAirportLabel[2] = CreateDynamic3DTextLabel(frmthalte, COLOR_WHITE, 1695.0912, -2247.4392, 13.5469 + 1.1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
    format(frmthalte, sizeof(frmthalte), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Airport\n%s -> %s\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(1326.6183, -917.9512, 37.0724), GetLocation(275.6585, -179.4285, 1.5781), CountBusAirport);
    HalteAirportLabel[3] = CreateDynamic3DTextLabel(frmthalte, COLOR_WHITE, 1326.6183, -917.9512, 37.0724 + 1.1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
    format(frmthalte, sizeof(frmthalte), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Airport\n%s -> Terminal Kota\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(275.6585, -179.4285, 1.5781), CountBusAirport);
    HalteAirportLabel[4] = CreateDynamic3DTextLabel(frmthalte, COLOR_WHITE, 275.6585, -179.4285, 1.5781 + 1.1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
    
    HaltePickup[0] = CreateDynamicPickup(1239, 23, 118.9531, -1459.3467, 24.3454, 0, 0, -1, 15.0, -1, 0);
    HaltePickup[1] = CreateDynamicPickup(1239, 23, 415.6029, -1778.9414, 5.5469, 0, 0, -1, 15.0, -1, 0);
    HaltePickup[2] = CreateDynamicPickup(1239, 23, 1695.0912, -2247.4392, 13.5469, 0, 0, -1, 15.0, -1, 0);
    HaltePickup[3] = CreateDynamicPickup(1239, 23, 1326.6183, -917.9512, 37.0724, 0, 0, -1, 15.0, -1, 0);
    HaltePickup[4] = CreateDynamicPickup(1239, 23, 275.6585, -179.4285, 1.5781, 0, 0, -1, 15.0, -1, 0);

    format(frmthalte, sizeof(frmthalte), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Kantor Polisi\n%s -> %s\nJumlah Unit Beroperasi: "YELLOW"%d", GetLocation(634.8659, -552.8594, 16.3359), GetLocation(934.6875, -1579.2477, 13.5469), CountBusKanpol);
    HalteKanpolLabel[0] = CreateDynamic3DTextLabel(frmthalte, COLOR_WHITE, 634.8659, -552.8594, 16.3359 + 1.1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
    format(frmthalte, sizeof(frmthalte), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Kantor Polisi\n%s -> %s\nJumlah Unit Beroperasi: "YELLOW"%d", GetLocation(934.6875, -1579.2477, 13.5469), GetLocation(1071.4409, -1718.4834, 13.5469), CountBusKanpol);
    HalteKanpolLabel[1] = CreateDynamic3DTextLabel(frmthalte, COLOR_WHITE, 934.6875, -1579.2477, 13.5469 + 1.1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
    format(frmthalte, sizeof(frmthalte), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Kantor Polisi\n%s -> %s\nJumlah Unit Beroperasi: "YELLOW"%d", GetLocation(1071.4409, -1718.4834, 13.5469), GetLocation(1265.9503, -2005.9641, 59.4531), CountBusKanpol);
    HalteKanpolLabel[2] = CreateDynamic3DTextLabel(frmthalte, COLOR_WHITE, 1071.4409, -1718.4834, 13.5469 + 1.1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
    format(frmthalte, sizeof(frmthalte), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Kantor Polisi\n%s -> %s\nJumlah Unit Beroperasi: "YELLOW"%d", GetLocation(1265.9503, -2005.9641, 59.4531), GetLocation(1201.3481, -1274.0947, 13.5469), CountBusKanpol);
    HalteKanpolLabel[3] = CreateDynamic3DTextLabel(frmthalte, COLOR_WHITE, 1265.9503, -2005.9641, 59.4531 + 1.1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
    format(frmthalte, sizeof(frmthalte), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Kantor Polisi\n%s -> %s\nJumlah Unit Beroperasi: "YELLOW"%d", GetLocation(1201.3481, -1274.0947, 13.5469), GetLocation(1024.7743, -1133.9796, 23.8203), CountBusKanpol);
    HalteKanpolLabel[4] = CreateDynamic3DTextLabel(frmthalte, COLOR_WHITE, 1201.3481, -1274.0947, 13.5469 + 1.1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
    format(frmthalte, sizeof(frmthalte), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Kantor Polisi\n%s -> Terminal Kota\nJumlah Unit Beroperasi: "YELLOW"%d", GetLocation(1024.7743, -1133.9796, 23.8203), CountBusKanpol);
    HalteKanpolLabel[5] = CreateDynamic3DTextLabel(frmthalte, COLOR_WHITE, 1024.7743, -1133.9796, 23.8203 + 1.1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
    
    HaltePickup[5] = CreateDynamicPickup(1239, 23, 634.8659, -552.8594, 16.3359, 0, 0, -1, 15.0, -1, 0);
    HaltePickup[6] = CreateDynamicPickup(1239, 23, 934.6875, -1579.2477, 13.5469, 0, 0, -1, 15.0, -1, 0);
    HaltePickup[7] = CreateDynamicPickup(1239, 23, 1071.4409, -1718.4834, 13.5469, 0, 0, -1, 15.0, -1, 0);
    HaltePickup[8] = CreateDynamicPickup(1239, 23, 1265.9503, -2005.9641, 59.4531, 0, 0, -1, 15.0, -1, 0);
    HaltePickup[9] = CreateDynamicPickup(1239, 23, 1201.3481, -1274.0947, 13.5469, 0, 0, -1, 15.0, -1, 0);
    HaltePickup[10] = CreateDynamicPickup(1239, 23, 1024.7743, -1133.9796, 23.8203, 0, 0, -1, 15.0, -1, 0);

    format(frmthalte, sizeof(frmthalte), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Rumah Sakit\n%s -> %s\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(-118.5932, -1155.1671, 2.2529), GetLocation(313.6201, -1482.1116, 33.6070), CountBusHospital);
    HalteHospitalLabel[0] = CreateDynamic3DTextLabel(frmthalte, COLOR_WHITE, -118.5932, -1155.1671, 2.2529 + 1.1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
    format(frmthalte, sizeof(frmthalte), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Rumah Sakit\n%s -> %s\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(313.6201, -1482.1116, 33.6070), GetLocation(1371.3846, -1084.7994, 24.8435), CountBusHospital);
    HalteHospitalLabel[1] = CreateDynamic3DTextLabel(frmthalte, COLOR_WHITE, 313.6201, -1482.1116, 33.6070 + 1.1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
    format(frmthalte, sizeof(frmthalte), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Rumah Sakit\n%s -> %s\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(1371.3846, -1084.7994, 24.8435), GetLocation(688.6235, -616.1765, 16.3359), CountBusHospital);
    HalteHospitalLabel[2] = CreateDynamic3DTextLabel(frmthalte, COLOR_WHITE, 1371.3846, -1084.7994, 24.8435 + 1.1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
    format(frmthalte, sizeof(frmthalte), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Rumah Sakit\n%s -> Terminal Kota\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(688.6235, -616.1765, 16.3359), CountBusHospital);
    HalteHospitalLabel[3] = CreateDynamic3DTextLabel(frmthalte, COLOR_WHITE, 688.6235, -616.1765, 16.3359 + 1.1, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);

    HaltePickup[9] = CreateDynamicPickup(1239, 23, -118.5932, -1155.1671, 2.2529, 0, 0, -1, 15.0, -1, 0);
    HaltePickup[10] = CreateDynamicPickup(1239, 23, 313.6201, -1482.1116, 33.6070, 0, 0, -1, 15.0, -1, 0);
    HaltePickup[11] = CreateDynamicPickup(1239, 23, 1371.3846, -1084.7994, 24.8435, 0, 0, -1, 15.0, -1, 0);
    HaltePickup[12] = CreateDynamicPickup(1239, 23, 688.6235, -616.1765, 16.3359, 0, 0, -1, 15.0, -1, 0);
}

LoadVarsBus(playerid)
{
    UnloadVarsBus(playerid);

    PlayerVarsBus[playerid][BusIcon] = CreateDynamicMapIcon(78.0562, -298.9631, 1.6756, 61, 0xffffffff, 0, 0, playerid, _, MAPICON_GLOBAL, -1, 0);
    return 1;
}

UnloadVarsBus(playerid)
{
    if(DestroyDynamicMapIcon(PlayerVarsBus[playerid][BusIcon]))
        PlayerVarsBus[playerid][BusIcon] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
    
    return 1;
}

hook OnGameModeInit()
{
    LoadPickupBus();
    BusAirport = CreateDynamicSphere(78.0562, -298.9631, 1.6756, 2.0, 0, 0, -1, 0);
    BusHospital = CreateDynamicSphere(85.4388, -298.2834, 1.6717, 2.0, 0, 0, -1, 0);
    BusAnglePine = CreateDynamicSphere(99.2536, -298.3510, 1.6876, 2.0, 0, 0, -1, 0);
    BusKanpol = CreateDynamicSphere(92.0224, -298.4567, 1.6783, 2.0, 0, 0, -1, 0);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    SetPVarInt(playerid, "BusRute", 0);
    SetBusWorking(playerid, false);
    BusIndex[playerid] = 0;
    BusWaiting[playerid] = false;
    BusTime[playerid] = 0;
    BusExitTimer[playerid] = 0;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(IsBusWorking(playerid))
    {
        DisablePlayerRaceCheckpoint(playerid);
        DestroyJobVehicle(playerid);
        SetBusWorking(playerid, false);
        BusIndex[playerid] = 0;
        BusWaiting[playerid] = false;
        BusTime[playerid] = 0;
        BusExitTimer[playerid] = 0;
        if(GetPVarInt(playerid, "BusRute") == 1) CountBusAirport --; //
        if(GetPVarInt(playerid, "BusRute") == 2) CountBusKanpol --; //
        if(GetPVarInt(playerid, "BusRute") == 3) CountBusHospital --; //
    }
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    if(AccountData[playerid][pJob] == JOB_BUS && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(areaid == BusAirport)
        {
            if(!IsBusWorking(playerid))
            {
                SetPlayerCheckpoint(playerid, 78.0562, -298.9631, 1.6756, 2.0);
                ShowKey(playerid, "[Y] Memulai Bus");
            }
            else
            {
                SetPlayerCheckpoint(playerid, 78.0562, -298.9631, 1.6756, 2.0);
                ShowKey(playerid, "[Y] Memulai Bus");
            }
        }

        if(areaid == BusHospital)
        {
            if(!IsBusWorking(playerid))
            {
                SetPlayerCheckpoint(playerid, 85.4388, -298.2834, 1.6717, 2.0);
                ShowKey(playerid, "[Y] Memulai Bus");
            }
            else
            {
                SetPlayerCheckpoint(playerid, 85.4388, -298.2834, 1.6717, 2.0);
                ShowKey(playerid, "[Y] Memulai Bus");
            }
        }

        if(areaid == BusAnglePine)
        {
            if(!IsBusWorking(playerid))
            {
                SetPlayerCheckpoint(playerid, 99.2536, -298.3510, 1.6876, 2.0);
                ShowKey(playerid, "[Y] Memulai Bus");
            }
            else
            {
                SetPlayerCheckpoint(playerid, 99.2536, -298.3510, 1.6876, 2.0);
                ShowKey(playerid, "[Y] Memulai Bus");
            }
        }

        if(areaid == BusKanpol)
        {
            if(!IsBusWorking(playerid))
            {
                SetPlayerCheckpoint(playerid, 92.0224, -298.4567, 1.6783, 2.0);
                ShowKey(playerid, "[Y] Memulai Bus");
            }
            else
            {
                SetPlayerCheckpoint(playerid, 92.0224, -298.4567, 1.6783, 2.0);
                ShowKey(playerid, "[Y] Memulai Bus");
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    if(areaid == BusAirport)
    {
        DisablePlayerCheckpoint(playerid);
        HideShortKey(playerid);
    }

    if(areaid == BusHospital)
    {
        DisablePlayerCheckpoint(playerid);
        HideShortKey(playerid);
    }

    if(areaid == BusAnglePine)
    {
        DisablePlayerCheckpoint(playerid);
        HideShortKey(playerid);
    }

    if(areaid == BusKanpol)
    {
        DisablePlayerCheckpoint(playerid);
        HideShortKey(playerid);
    }
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_DRIVER && IsBusWorking(playerid) && GetVehicleModel(GetPlayerVehicleID(playerid)) == 431)
    {
        BusExitTimer[playerid] = 0;
        BusTime[playerid] = 10;
    }
    else if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT && IsBusWorking(playerid) && GetVehicleModel(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle]) == 431)
    {
        BusExitTimer[playerid] = 60;
        PlayerTextDrawHide(playerid, BusWait[playerid][0]);
        SendClientMessage(playerid, X11_DARKORANGE, "[Warning]:"WHITE" Anda harus naik ke kendaraan sebelum "RED"60 detik"WHITE" berakhir atau pekerjaan akan gagal");
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_WALK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pJob] == JOB_BUS)
    {
        if(IsPlayerInDynamicArea(playerid, BusKanpol))
        {
            if(!IsBusWorking(playerid))
            {
                CreateJobVehicle(playerid, 431, 92.0224, -298.4567, 1.6783, 179.6553, 13, 13, true, true);
                SwitchVehicleEngine(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], true);

                BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
                AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.330, -3.750, 0.459, 0.000, 0.000, -90.000);
                BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
                AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.330, -2.591, 0.459, 0.000, 0.000, -90.000);
                BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
                AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.351, -3.750, 0.459, 0.000, 0.000, 90.000);
                BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
                AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.350, -2.440, 0.459, 0.000, 0.000, 90.000);
                BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                SetDynamicObjectMaterialText(BusObject, 0, "{000000}u", 130, "Webdings", 170, 0, 0, 0, 1);
                AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.360, -3.679, 0.659, 0.000, 0.000, 90.000);
                BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                SetDynamicObjectMaterialText(BusObject, 0, "{000000}u", 130, "Webdings", 170, 0, 0, 0, 1);
                AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.340, -3.809, 0.659, 0.000, 0.000, -90.000);
                BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                SetDynamicObjectMaterialText(BusObject, 0, "{000000}District", 130, "Arial", 80, 1, 0, 0, 1);
                AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.340, -3.039, 0.719, 0.000, 0.000, -90.000);
                BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                SetDynamicObjectMaterialText(BusObject, 0, "{000000}Transit", 130, "Arial", 80, 1, 0, 0, 1);
                AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.340, -3.059, 0.450, 0.000, 0.000, -90.000);
                BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                SetDynamicObjectMaterialText(BusObject, 0, "{000000}District", 130, "Arial", 80, 1, 0, 0, 1);
                AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.360, -2.919, 0.679, 0.000, 0.000, 90.000);
                BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                SetDynamicObjectMaterialText(BusObject, 0, "{000000}Transit", 130, "Arial", 80, 1, 0, 0, 1);
                AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.360, -2.919, 0.439, 0.000, 0.000, 90.000);
                BusObject = CreateDynamicObject(7313,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                SetDynamicObjectMaterial(BusObject, 1, 9514, "711_sfw", "dt_carpark_line_texture", 0);
                SetDynamicObjectMaterialText(BusObject, 0, "{ff0000}Bus Police Station", 110, "Courier New", 50, 1, 0, 1, 1);
                AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.270, 0.440, -0.039, 0.000, 0.000, 450.000);
                BusObject = CreateDynamicObject(7313,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                SetDynamicObjectMaterial(BusObject, 1, 9514, "711_sfw", "dt_carpark_line_texture", 0);
                SetDynamicObjectMaterialText(BusObject, 0, "{ff0000}Bus Police Station", 110, "Courier New", 50, 1, 0, 1, 1);


                BusIndex[playerid] = 80;
                AccountData[playerid][pCheckpoint] = CHECKPOINT_BUS_KANPOL;
                SetBusWorking(playerid, true);
                SetPlayerRaceCheckpoint(playerid, 0, 92.3999,-232.5221,1.5781, 204.7068,-288.5426,1.4297, 5.0);
                SetPVarInt(playerid, "BusRute", 2); // Kanpol

                CountBusKanpol ++;
            }
            else
            {
                SetBusWorking(playerid, false);
                BusWaiting[playerid] = false;
                BusTime[playerid] = 0;
                BusIndex[playerid] = 0;

                DestroyJobVehicle(playerid);
                DisablePlayerRaceCheckpoint(playerid);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengembalikan bus!");
            }
        }

        if(IsPlayerInDynamicArea(playerid, BusAirport))
        {
            if(!IsBusWorking(playerid))
            {
                CreateJobVehicle(playerid, 431, 78.4014, -298.3891, 1.6819, 179.2272, 0, 0, true, true);
                SwitchVehicleEngine(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], true);

                BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.330, -3.750, 0.459, 0.000, 0.000, -90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.330, -2.591, 0.459, 0.000, 0.000, -90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.351, -3.750, 0.459, 0.000, 0.000, 90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.350, -2.440, 0.459, 0.000, 0.000, 90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}u", 130, "Webdings", 170, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.360, -3.679, 0.659, 0.000, 0.000, 90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}u", 130, "Webdings", 170, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.340, -3.809, 0.659, 0.000, 0.000, -90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}District", 130, "Arial", 80, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.340, -3.039, 0.719, 0.000, 0.000, -90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}Transit", 130, "Arial", 80, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.340, -3.059, 0.450, 0.000, 0.000, -90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}District", 130, "Arial", 80, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.360, -2.919, 0.679, 0.000, 0.000, 90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}Transit", 130, "Arial", 80, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.360, -2.919, 0.439, 0.000, 0.000, 90.000);
				BusObject = CreateDynamicObject(7313,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 1, 9514, "711_sfw", "dt_carpark_line_texture", 0);
				SetDynamicObjectMaterialText(BusObject, 0, "{ff0000}Bus Airport", 110, "Courier New", 50, 1, 0, 1, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.270, 0.440, -0.039, 0.000, 0.000, 450.000);
				BusObject = CreateDynamicObject(7313,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 1, 9514, "711_sfw", "dt_carpark_line_texture", 0);
				SetDynamicObjectMaterialText(BusObject, 0, "{ff0000}Bus Airport", 110, "Courier New", 50, 1, 0, 1, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.253, 0.440, -0.039, 0.000, 0.000, 270.000);

				BusIndex[playerid] = 1;
                AccountData[playerid][pCheckpoint] = CHECKPOINT_BUS_AIRPORT;
                SetBusWorking(playerid, true);
                SetPlayerRaceCheckpoint(playerid, 0, 89.4649,-248.0080,1.6782, 89.4649,-248.0080,1.6782, 5.0);

                SetPVarInt(playerid, "BusRute", 1); // Airport
                CountBusAirport ++;
            }
            else
            {
                SetBusWorking(playerid, false);
                BusWaiting[playerid] = false;
                BusTime[playerid] = 0;
                BusIndex[playerid] = 0;
                
                DestroyJobVehicle(playerid);
                DisablePlayerRaceCheckpoint(playerid);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengembalikan bus!");
            }
        }

        if(IsPlayerInDynamicArea(playerid, BusAnglePine))
        {
            if(!IsBusWorking(playerid))
            {
                CreateJobVehicle(playerid, 431, 99.2536, -298.3510, 1.6876, 180.6935, 1, 126, true, true);
                SwitchVehicleEngine(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], true);
                
                BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.330, -3.750, 0.459, 0.000, 0.000, -90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.330, -2.591, 0.459, 0.000, 0.000, -90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.351, -3.750, 0.459, 0.000, 0.000, 90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.350, -2.440, 0.459, 0.000, 0.000, 90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}u", 130, "Webdings", 170, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.360, -3.679, 0.659, 0.000, 0.000, 90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}u", 130, "Webdings", 170, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.340, -3.809, 0.659, 0.000, 0.000, -90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}District", 130, "Arial", 80, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.340, -3.039, 0.719, 0.000, 0.000, -90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}Transit", 130, "Arial", 80, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.340, -3.059, 0.450, 0.000, 0.000, -90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}District", 130, "Arial", 80, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.360, -2.919, 0.679, 0.000, 0.000, 90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}Transit", 130, "Arial", 80, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.360, -2.919, 0.439, 0.000, 0.000, 90.000);
				BusObject = CreateDynamicObject(7313,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 1, 9514, "711_sfw", "dt_carpark_line_texture", 0);
				SetDynamicObjectMaterialText(BusObject, 0, "{ff0000}Bus Angle Pine", 110, "Courier New", 50, 1, 0, 1, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.270, 0.440, -0.039, 0.000, 0.000, 450.000);
				BusObject = CreateDynamicObject(7313,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 1, 9514, "711_sfw", "dt_carpark_line_texture", 0);
				SetDynamicObjectMaterialText(BusObject, 0, "{ff0000}Bus Angle Pine", 110, "Courier New", 50, 1, 0, 1, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.253, 0.440, -0.039, 0.000, 0.000, 270.000);

				BusIndex[playerid] = 53;
                AccountData[playerid][pCheckpoint] = CHECKPOINT_BUS_ANGLEPINE;
                SetBusWorking(playerid, true);
                SetPlayerRaceCheckpoint(playerid, 0, 94.7228,-241.3779,1.6783, -283.9085,-149.4883,2.0649, 5.0);
            }
            else
            {
                SetBusWorking(playerid, false);
                BusWaiting[playerid] = false;
                BusTime[playerid] = 0;
                BusIndex[playerid] = 0;
                
                DestroyJobVehicle(playerid);
                DisablePlayerRaceCheckpoint(playerid);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengembalikan bus!");
            }
        }

        if(IsPlayerInDynamicArea(playerid, BusHospital))
        {
            if(!IsBusWorking(playerid))
            {
                CreateJobVehicle(playerid, 431, 85.4388, -298.2834, 1.6717, 178.1776, 7, 7, true, true);
                SwitchVehicleEngine(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], true);
                
                BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.330, -3.750, 0.459, 0.000, 0.000, -90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.330, -2.591, 0.459, 0.000, 0.000, -90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.351, -3.750, 0.459, 0.000, 0.000, 90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 0, 10765, "airportgnd_sfse", "white", 0);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.350, -2.440, 0.459, 0.000, 0.000, 90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}u", 130, "Webdings", 170, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.360, -3.679, 0.659, 0.000, 0.000, 90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}u", 130, "Webdings", 170, 0, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.340, -3.809, 0.659, 0.000, 0.000, -90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}District", 130, "Arial", 80, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.340, -3.039, 0.719, 0.000, 0.000, -90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}Transit", 130, "Arial", 80, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.340, -3.059, 0.450, 0.000, 0.000, -90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}District", 130, "Arial", 80, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.360, -2.919, 0.679, 0.000, 0.000, 90.000);
				BusObject = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterialText(BusObject, 0, "{000000}Transit", 130, "Arial", 80, 1, 0, 0, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.360, -2.919, 0.439, 0.000, 0.000, 90.000);
				BusObject = CreateDynamicObject(7313,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 1, 9514, "711_sfw", "dt_carpark_line_texture", 0);
				SetDynamicObjectMaterialText(BusObject, 0, "{ff0000}Bus Hospital", 110, "Courier New", 50, 1, 0, 1, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], 1.270, 0.440, -0.039, 0.000, 0.000, 450.000);
				BusObject = CreateDynamicObject(7313,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
				SetDynamicObjectMaterial(BusObject, 1, 9514, "711_sfw", "dt_carpark_line_texture", 0);
				SetDynamicObjectMaterialText(BusObject, 0, "{ff0000}Bus Hospital", 110, "Courier New", 50, 1, 0, 1, 1);
				AttachDynamicObjectToVehicle(BusObject, JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], -1.253, 0.440, -0.039, 0.000, 0.000, 270.000);

				BusIndex[playerid] = 32;
                AccountData[playerid][pCheckpoint] = CHECKPOINT_BUS_HOSPITAL;
                SetBusWorking(playerid, true);
                SetPlayerRaceCheckpoint(playerid, 0, 69.6886,-254.1934,1.6765, -273.6859,-153.2742,2.5130, 5.0);

                CountBusHospital ++;
                SetPVarInt(playerid, "BusRute", 3); //Hospital
            }
            else
            {
                SetBusWorking(playerid, false);
                BusWaiting[playerid] = false;
                BusTime[playerid] = 0;
                BusIndex[playerid] = 0;
                
                DestroyJobVehicle(playerid);
                DisablePlayerRaceCheckpoint(playerid);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengembalikan bus!");
            }
        }
    }
    return 1;
}

hook OnPlayerEnterRaceCP(playerid)
{
    switch(AccountData[playerid][pCheckpoint])
    {
        case CHECKPOINT_BUS_HOSPITAL:
        {
            if(IsBusWorking(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 431)
                {
                    if(BusIndex[playerid] == 32)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -273.6859,-153.2742,2.5130, -74.1208,-435.4034,1.1779, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 33;
                    }
                    else if(BusIndex[playerid] == 33)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -74.1208,-435.4034,1.1779, -109.5937,-952.3293,22.7272, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 34;
                    }
                    else if(BusIndex[playerid] == 34)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -109.5937,-952.3293,22.7272, -115.2140,-1155.6555,2.1268, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 35;
                    }
                    else if(BusIndex[playerid] == 35)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -115.2140,-1155.6555,2.1268, -9.6364,-1524.4979,2.3418, 2.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 36;
                    }
                    else if(BusIndex[playerid] == 36)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 37)
                    {
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        DisablePlayerRaceCheckpoint(playerid);
                        SetPlayerRaceCheckpoint(playerid, 0, 172.6937,-1541.7325,12.6236, 310.5742,-1480.3171,33.3742, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 38;
                    }
                    else if(BusIndex[playerid] == 38)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 310.5742,-1480.3171,33.3742, 413.1094,-1446.2328,31.4077, 2.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 39;
                    }
                    else if(BusIndex[playerid] == 39)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 40)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 869.0794,-1407.2970,13.0327, 1263.6222,-1369.0153,13.3465, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 41;
                    }
                    else if(BusIndex[playerid] == 41)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1263.6222,-1369.0153,13.3465, 1325.3833,-1283.3413,13.4833, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 42;
                    }
                    else if(BusIndex[playerid] == 42)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1325.3833,-1283.3413,13.4833, 1367.4031,-1085.0889,24.7867, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 43;
                    }
                    else if(BusIndex[playerid] == 43)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1367.4031,-1085.0889,24.7867, 1314.3898,-925.8003,38.2064, 2.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 44;
                    }
                    else if(BusIndex[playerid] == 44)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 45)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 798.8291,-1003.4207,30.1350, 685.1666,-616.9871,16.2831, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 46;
                    }
                    else if(BusIndex[playerid] == 46)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 685.1666,-616.9871,16.2831, 662.3487,-482.8038,16.2851, 2.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 47;
                    }
                    else if(BusIndex[playerid] == 47)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 48)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 545.5098,-412.1735,28.5848, 186.1240,-229.6381,1.5313, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 49;
                    }
                    else if(BusIndex[playerid] == 49)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 186.1240,-229.6381,1.5313, 75.3205,-242.3378,1.6800, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 50;
                    }
                    else if(BusIndex[playerid] == 50)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 75.3205,-242.3378,1.6800, 85.0369,-299.3788,1.6797, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 51;
                    }
                    else if(BusIndex[playerid] == 51)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 1, 85.0369,-299.3788,1.6797, 85.0369,-299.3788,1.6797, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 52;
                    }
                    else if(BusIndex[playerid] == 52)
                    {
                        SetBusWorking(playerid, false);
                        BusWaiting[playerid] = false;
                        AccountData[playerid][pCheckpoint] = CHECKPOINT_BUS_INVALID;
                        
                        DestroyJobVehicle(playerid);
                        DisablePlayerRaceCheckpoint(playerid);
                        
                        CountBusHospital --;
                        SetPVarInt(playerid, "BusRute", 0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        GivePlayerXP(playerid, DEFAULT_XP);
                    }
                }
            }
        }
        case CHECKPOINT_BUS_ANGLEPINE:
        {
            if(IsBusWorking(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 431)
                {
                    if(BusIndex[playerid] == 53)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -283.9085,-149.4883,2.0649, -207.6026,215.2931,11.6893, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 54;
                    }
                    else if(BusIndex[playerid] == 54)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -207.6026,215.2931,11.6893, -844.0803,-47.8933,42.4670, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 55;
                    }
                    else if(BusIndex[playerid] == 55)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -844.0803,-47.8933,42.4670, -766.3112,-89.4049,65.7976, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 56;
                    }
                    else if(BusIndex[playerid] == 56)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -766.3112,-89.4049,65.7976, -960.4075,-289.5359,36.5512, 2.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 57;
                    }
                    else if(BusIndex[playerid] == 57)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 58)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -1215.2813,-750.0646,61.8660, -1758.7012,-602.5632,16.3245, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 59;
                    }
                    else if(BusIndex[playerid] == 59)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -1758.7012,-602.5632,16.3245, -1923.5822,-604.5061,25.2457, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 60;
                    }
                    else if(BusIndex[playerid] == 60)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -1923.5822,-604.5061,25.2457, -1911.9205,-1042.0327,38.3922, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 61;
                    }
                    else if(BusIndex[playerid] == 61)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -1911.9205,-1042.0327,38.3922, -1911.8625,-1352.0985,40.4729, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 62;
                    }
                    else if(BusIndex[playerid] == 62)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -1911.8625,-1352.0985,40.4729, -1548.4135,-1586.6697,37.8325, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 63;
                    }
                    else if(BusIndex[playerid] == 63)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -1548.4135,-1586.6697,37.8325, -1905.5469,-1770.4061,29.6322, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 64;
                    }
                    else if(BusIndex[playerid] == 64)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -1905.5469,-1770.4061,29.6322, -2232.0400,-2256.2053,30.3266, 2.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 65;
                    }
                    else if(BusIndex[playerid] == 65)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 66)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -2179.5137,-2342.9849,30.5680, -2098.7969,-2452.3965,30.5595, 2.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 67;
                    }
                    else if(BusIndex[playerid] == 67)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 68)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 69)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -979.8699,-2871.4629,67.0867, -193.9389,-2873.6489,39.2829, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 70;
                    }
                    else if(BusIndex[playerid] == 70)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -193.9389,-2873.6489,39.2829, -229.0609,-2289.8477,28.3172, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 71;
                    }
                    else if(BusIndex[playerid] == 71)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -229.0609,-2289.8477,28.3172, -15.7218,-1419.0569,10.5612, 2.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 72;
                    }
                    else if(BusIndex[playerid] == 72)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 73)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 6.2545,-1529.1285,3.4320, 525.9114,-1270.0645,16.2475, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 74;
                    }
                    else if(BusIndex[playerid] == 74)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 525.9114,-1270.0645,16.2475, 798.8906,-999.2177,31.0381, 2.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 75;
                    }
                    else if(BusIndex[playerid] == 75)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 76)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 565.5526,-412.2194,28.0132, 106.9106,-208.3385,1.5314, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 77;
                    }
                    else if(BusIndex[playerid] == 77)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        SetPlayerRaceCheckpoint(playerid, 0, 106.9106,-208.3385,1.5314, 98.9817,-299.1543,1.6696, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 78;
                    }
                    else if(BusIndex[playerid] == 78)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        SetPlayerRaceCheckpoint(playerid, 1, 98.9817,-299.1543,1.6696, 98.9817,-299.1543,1.6696, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 79;
                    }
                    else if(BusIndex[playerid] == 79)
                    {
                        SetBusWorking(playerid, false);
                        BusWaiting[playerid] = false;
                        AccountData[playerid][pCheckpoint] = CHECKPOINT_BUS_INVALID;
                        
                        DestroyJobVehicle(playerid);
                        DisablePlayerRaceCheckpoint(playerid);
                        
                        GiveMoney(playerid, 300);
                        ShowItemBox(playerid, "Received $300", "Uang", 1212);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        GivePlayerXP(playerid, DEFAULT_XP);
                    }
                }
            }
        }
        case CHECKPOINT_BUS_AIRPORT:
        {
            if(IsBusWorking(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 431)
                {
                    if(BusIndex[playerid] == 1)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 179.9168,-248.6260,1.5310, 445.9030,-408.7904,28.1035, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 2;
                    }
                    else if(BusIndex[playerid] == 2)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 445.9030,-408.7904,28.1035, 389.6937,-670.1260,26.5923, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 3;
                    }
                    else if(BusIndex[playerid] == 3)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 389.6937,-670.1260,26.5923, 224.6529,-1064.3547,61.2358, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 4;
                    }
                    else if(BusIndex[playerid] == 4)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 224.6529,-1064.3547,61.2358, 152.0972,-1388.0200,49.0849, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 5;
                    }
                    else if(BusIndex[playerid] == 5)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 152.0972,-1388.0200,49.0849, 122.3802,-1460.4767,24.2885, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 6;
                    }
                    else if(BusIndex[playerid] == 6)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 122.3802,-1460.4767,24.2885, 115.7602,-1609.5221,10.4715, 2.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 7;
                    }
                    else if(BusIndex[playerid] == 7)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 8)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 414.6135,-1775.9048,5.3755, 626.9605,-1747.7344,13.3627, 2.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 9;
                    }
                    else if(BusIndex[playerid] == 9)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 10)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 987.7833,-1804.6042,14.1609, 1066.2089,-2332.5205,12.7565, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 11;
                    }
                    else if(BusIndex[playerid] == 11)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1066.2089,-2332.5205,12.7565, 1360.7100,-2438.2649,8.1529, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 12;
                    }
                    else if(BusIndex[playerid] == 12)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1360.7100,-2438.2649,8.1529, 1364.3325,-2294.5962,13.4878, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 13;
                    }
                    else if(BusIndex[playerid] == 13)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1364.3325,-2294.5962,13.4878, 1487.1716,-2334.1235,13.4858, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 14;
                    }
                    else if(BusIndex[playerid] == 14)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1487.1716,-2334.1235,13.4858, 1642.2184,-2321.7688,13.4836, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 15;
                    }
                    else if(BusIndex[playerid] == 15)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1642.2184,-2321.7688,13.4836, 1735.5060,-2279.5496,13.4761, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 16;
                    }
                    else if(BusIndex[playerid] == 16)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1735.5060,-2279.5496,13.4761, 1696.1708,-2250.8074,13.4870, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 17;
                    }
                    else if(BusIndex[playerid] == 17)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1696.1708,-2250.8074,13.4870, 1548.4612,-2283.3728,13.4815, 2.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 18;
                    }
                    else if(BusIndex[playerid] == 18)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 19)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1379.9990,-2282.7942,13.4309, 1569.9825,-2120.6152,16.1809, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 20;
                    }
                    else if(BusIndex[playerid] == 20)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1569.9825,-2120.6152,16.1809, 1612.5999,-1535.2872,28.6864, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 21;
                    }
                    else if(BusIndex[playerid] == 21)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1612.5999,-1535.2872,28.6864, 1671.6648,-1131.7931,59.2196, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 22;
                    }
                    else if(BusIndex[playerid] == 22)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1671.6648,-1131.7931,59.2196, 1327.9952,-922.2906,36.8436, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 23;
                    }
                    else if(BusIndex[playerid] == 23)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1327.9952,-922.2906,36.8436, 1159.5959,-901.1819,42.7490, 2.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 24;
                    }
                    else if(BusIndex[playerid] == 24)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 25)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1223.1686,-251.2162,23.6118, 1084.7848,-183.7294,39.4679, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 26;
                    }
                    else if(BusIndex[playerid] == 26)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1084.7848,-183.7294,39.4679, 466.3721,-137.6863,26.3356, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 27;
                    }
                    else if(BusIndex[playerid] == 27)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 466.3721,-137.6863,26.3356, 279.4392,-178.2524,1.5298, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 28;
                    }
                    else if(BusIndex[playerid] == 28)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 279.4392,-178.2524,1.5298, 73.1662,-245.4490,1.6749, 2.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 29;
                    }
                    else if(BusIndex[playerid] == 29)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 30)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        SetPlayerRaceCheckpoint(playerid, 2, 77.4550,-299.0801,1.6755, 77.4550,-299.0801,1.6755, 5.0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        BusIndex[playerid] = 31;
                    }
                    else if(BusIndex[playerid] == 31)
                    {
                        SetBusWorking(playerid, false);
                        BusWaiting[playerid] = false;
                        AccountData[playerid][pCheckpoint] = CHECKPOINT_BUS_INVALID;
                        
                        DestroyJobVehicle(playerid);
                        DisablePlayerRaceCheckpoint(playerid);
                        
                        CountBusAirport --;
                        SetPVarInt(playerid, "BusRute", 0);
                        GiveMoney(playerid, 60);
                        ShowItemBox(playerid, "Received $60", "Uang", 1212);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        GivePlayerXP(playerid, DEFAULT_XP);
                    }
                }
            }
        }
        case CHECKPOINT_BUS_KANPOL:
        {
            if(IsBusWorking(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
            {
                if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 431)
                {
                    if(BusIndex[playerid] == 80)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 204.7068,-288.5426,1.4297, 632.1907,-417.6755,16.1875, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 81;
                    }
                    else if(BusIndex[playerid] == 81)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 632.1907,-417.6755,16.1875, 638.2797,-552.0702,16.1875, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 82;
                    }
                    else if(BusIndex[playerid] == 82)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 638.2797,-552.0702,16.1875, 682.3107,-791.2142,33.8053, 2.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 83;
                    }
                    else if(BusIndex[playerid] == 83)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 84)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 793.1075,-1025.8230,25.8031, 794.1853,-1379.0216,13.4744, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 85;
                    }
                    else if(BusIndex[playerid] == 85)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 794.1853,-1379.0216,13.4744, 914.9197,-1418.0079,13.2162, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 86;
                    }
                    else if(BusIndex[playerid] == 86)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 914.9197,-1418.0079,13.2162, 933.7965,-1575.5983,13.3828, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 87;
                    }
                    else if(BusIndex[playerid] == 87)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 933.7965,-1575.5983,13.3828, 1034.3263,-1584.6193,13.3828, 2.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 88;
                    }
                    else if(BusIndex[playerid] == 88)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 89)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1070.5468,-1715.2983,13.3828, 1294.7834,-1722.2269,13.3906, 2.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 90;
                    }
                    else if(BusIndex[playerid] == 90)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 91)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1308.2179,-1855.0807,13.3828, 1423.9498,-1878.8542,13.3828, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 92;
                    }
                    else if(BusIndex[playerid] == 92)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1423.9498,-1878.8542,13.3828, 1248.1713,-1918.7787,31.1185, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 93;
                    }
                    else if(BusIndex[playerid] == 93)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1248.1713,-1918.7787,31.1185, 1266.6886,-2009.7734,59.2635, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 94;
                    }
                    else if(BusIndex[playerid] == 94)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1266.6886,-2009.7734,59.2635, 1309.9088,-2059.1707,58.0681, 2.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 95;
                    }
                    else if(BusIndex[playerid] == 95)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 96)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1252.5984,-1923.3146,31.2505, 1429.1202,-1884.8777,13.4507, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 97;
                    }
                    else if(BusIndex[playerid] == 97)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1429.1202,-1884.8777,13.4507, 1314.9207,-1831.5137,13.3828, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 98;
                    }
                    else if(BusIndex[playerid] == 98)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        SetPlayerRaceCheckpoint(playerid, 0, 1314.9207,-1831.5137,13.3828, 1293.3440,-1392.8809,13.2621, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 99;
                    }
                    else if(BusIndex[playerid] == 99)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1293.3440,-1392.8809,13.2621, 1202.3069,-1277.9476,13.3828, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 100;
                    }
                    else if(BusIndex[playerid] == 100)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1202.3069,-1277.9476,13.3828, 1064.3705,-1263.4731,14.1464, 2.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 101;
                    }
                    else if(BusIndex[playerid] == 101)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 102)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 1025.5914,-1137.3575,23.6563, 812.9864,-1138.5229,23.7905, 2.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 103;
                    }
                    else if(BusIndex[playerid] == 103)
                    {
                        BusWaiting[playerid] = true;
                        BusTime[playerid] = 10;
                    }
                    else if(BusIndex[playerid] == 104)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 797.4849,-1028.7705,25.4220, 689.2512,-805.9697,38.2737, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 105;
                    }
                    else if(BusIndex[playerid] == 105)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 689.2512,-805.9697,38.2737, 663.2259,-658.7592,16.3022, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 106;
                    }
                    else if(BusIndex[playerid] == 106)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 663.2259,-658.7592,16.3022, 405.9166,-580.7236,38.0806, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 107;
                    }
                    else if(BusIndex[playerid] == 107)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 405.9166,-580.7236,38.0806, 172.5882,-675.8779,10.8004, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 108;
                    }
                    else if(BusIndex[playerid] == 108)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 172.5882,-675.8779,10.8004, 40.8441,-636.3796,2.9970, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 109;
                    }
                    else if(BusIndex[playerid] == 109)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 40.8441,-636.3796,2.9970, -294.2030,-152.6470,1.2689, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 110;
                    }
                    else if(BusIndex[playerid] == 110)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, -294.2030,-152.6470,1.2689, 65.8807,-223.3382,1.5781, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 111;
                    }
                    else if(BusIndex[playerid] == 111)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 0, 65.8807,-223.3382,1.5781, 92.1431,-297.3812,1.5781, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 112;
                    }
                    else if(BusIndex[playerid] == 112)
                    {
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        SetPlayerRaceCheckpoint(playerid, 1, 92.1431,-297.3812,1.5781, 92.1431,-297.3812,1.5781, 5.0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        BusIndex[playerid] = 113;
                    }
                    else if(BusIndex[playerid] == 113)
                    {
                        SetBusWorking(playerid, false);
                        BusWaiting[playerid] = false;
                        AccountData[playerid][pCheckpoint] = CHECKPOINT_BUS_INVALID;
                        
                        DestroyJobVehicle(playerid);
                        DisablePlayerRaceCheckpoint(playerid);
                        
                        CountBusKanpol --;
                        SetPVarInt(playerid, "BusRute", 0);
                        GiveMoney(playerid, 50);
                        ShowItemBox(playerid, "Received $50", "Uang", 1212);
                        PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
                        GivePlayerXP(playerid, DEFAULT_XP);
                    }
                }
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveRaceCP(playerid)
{
    if(IsBusWorking(playerid) && GetVehicleModel(GetPlayerVehicleID(playerid)) == 431)
    {
        BusWaiting[playerid] = false;
        PlayerTextDrawHide(playerid, BusWait[playerid][0]);
    }
    return 1;
}

task LabelHalte_Update[1000]()
{
    new shstr[666], lastcountbandara = 0, lastcountkanpol = 0, lastcounthospital = 0;
    if(lastcountbandara != CountBusAirport)
    {
        format(shstr, sizeof(shstr), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Airport\n%s -> %s\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(118.9531, -1459.3467, 24.3454), GetLocation(415.6029, -1778.9414, 5.5469), CountBusAirport);
        UpdateDynamic3DTextLabelText(HalteAirportLabel[0], COLOR_WHITE, shstr);

        format(shstr, sizeof(shstr), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Airport\n%s -> %s\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(415.6029, -1778.9414, 5.5469), GetLocation(1695.0912, -2247.4392, 13.5469), CountBusAirport);
        UpdateDynamic3DTextLabelText(HalteAirportLabel[1], COLOR_WHITE, shstr);

        format(shstr, sizeof(shstr), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Airport\n%s -> %s\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(1695.0912, -2247.4392, 13.5469), GetLocation(1326.6183, -917.9512, 37.0724), CountBusAirport);
        UpdateDynamic3DTextLabelText(HalteAirportLabel[2], COLOR_WHITE, shstr);

        format(shstr, sizeof(shstr), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Airport\n%s -> %s\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(1326.6183, -917.9512, 37.0724), GetLocation(275.6585, -179.4285, 1.5781), CountBusAirport);
        UpdateDynamic3DTextLabelText(HalteAirportLabel[3], COLOR_WHITE, shstr);

        format(shstr, sizeof(shstr), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Airport\n%s -> Terminal Kota\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(275.6585, -179.4285, 1.5781), CountBusAirport);
        UpdateDynamic3DTextLabelText(HalteAirportLabel[4], COLOR_WHITE, shstr);
        lastcountbandara = CountBusAirport;
    }
    if(lastcountkanpol != CountBusKanpol)
    {
        format(shstr, sizeof(shstr), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Kantor Polisi\n%s -> %s\nJumlah Unit Beroperasi: "YELLOW"%d", GetLocation(634.8659, -552.8594, 16.3359), GetLocation(934.6875, -1579.2477, 13.5469), CountBusKanpol);
        UpdateDynamic3DTextLabelText(HalteKanpolLabel[0], COLOR_WHITE, shstr);

        format(shstr, sizeof(shstr), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Kantor Polisi\n%s -> %s\nJumlah Unit Beroperasi: "YELLOW"%d", GetLocation(934.6875, -1579.2477, 13.5469), GetLocation(1071.4409, -1718.4834, 13.5469), CountBusKanpol);
        UpdateDynamic3DTextLabelText(HalteKanpolLabel[1], COLOR_WHITE, shstr);

        format(shstr, sizeof(shstr), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Kantor Polisi\n%s -> %s\nJumlah Unit Beroperasi: "YELLOW"%d", GetLocation(1071.4409, -1718.4834, 13.5469), GetLocation(1265.9503, -2005.9641, 59.4531), CountBusKanpol);
        UpdateDynamic3DTextLabelText(HalteKanpolLabel[2], COLOR_WHITE, shstr);

        format(shstr, sizeof(shstr), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Kantor Polisi\n%s -> %s\nJumlah Unit Beroperasi: "YELLOW"%d", GetLocation(1265.9503, -2005.9641, 59.4531), GetLocation(1201.3481, -1274.0947, 13.5469), CountBusKanpol);
        UpdateDynamic3DTextLabelText(HalteKanpolLabel[3], COLOR_WHITE, shstr);

        format(shstr, sizeof(shstr), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Kantor Polisi\n%s -> %s\nJumlah Unit Beroperasi: "YELLOW"%d", GetLocation(1201.3481, -1274.0947, 13.5469), GetLocation(1024.7743, -1133.9796, 23.8203), CountBusKanpol);
        UpdateDynamic3DTextLabelText(HalteKanpolLabel[4], COLOR_WHITE, shstr);

        format(shstr, sizeof(shstr), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Kantor Polisi\n%s -> Terminal Kota\nJumlah Unit Beroperasi: "YELLOW"%d", GetLocation(1024.7743, -1133.9796, 23.8203), CountBusKanpol);
        UpdateDynamic3DTextLabelText(HalteKanpolLabel[5], COLOR_WHITE, shstr);
        lastcountkanpol = CountBusKanpol;
    }
    if(lastcounthospital != CountBusHospital)
    {
        format(shstr, sizeof(shstr), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Rumah Sakit\n%s -> %s\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(-118.5932, -1155.1671, 2.2529), GetLocation(313.6201, -1482.1116, 33.6070), CountBusHospital);
        UpdateDynamic3DTextLabelText(HalteHospitalLabel[0], COLOR_WHITE, shstr);
        format(shstr, sizeof(shstr), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Rumah Sakit\n%s -> %s\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(313.6201, -1482.1116, 33.6070), GetLocation(1371.3846, -1084.7994, 24.8435), CountBusHospital);
        UpdateDynamic3DTextLabelText(HalteHospitalLabel[1], COLOR_WHITE, shstr);
        format(shstr, sizeof(shstr), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Rumah Sakit\n%s -> %s\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(1371.3846, -1084.7994, 24.8435), GetLocation(688.6235, -616.1765, 16.3359), CountBusHospital);
        UpdateDynamic3DTextLabelText(HalteHospitalLabel[2], COLOR_WHITE, shstr);
        format(shstr, sizeof(shstr), ""GRAY"[District Halte]\n\n"WHITE"Halte Bus Rumah Sakit\n%s -> Terminal Kota\nJumlah Unit Bus Beroperasi: "YELLOW"%d", GetLocation(688.6235, -616.1765, 16.3359), CountBusHospital);
        UpdateDynamic3DTextLabelText(HalteHospitalLabel[3], COLOR_WHITE, shstr);
        lastcounthospital = CountBusHospital;
    }
    return 1;
}

ptask BusWaitingDelay[1000](playerid)
{
    if(BusExitTimer[playerid] > 0 && (IsBusWorking(playerid)))
    {
        BusExitTimer[playerid] --;
        GameTextForPlayer(playerid, sprintf("%d", BusExitTimer[playerid]), 1000, 4);
        if(!BusExitTimer[playerid])
        {
            DestroyJobVehicle(playerid);
            DisablePlayerRaceCheckpoint(playerid);
            SetBusWorking(playerid, false);
            BusWaiting[playerid] = false;
            BusTime[playerid] = 0;
            BusExitTimer[playerid] = 0;
            BusIndex[playerid] = 0;
            if(GetPVarInt(playerid, "BusRute") == 1) CountBusAirport --;
            if(GetPVarInt(playerid, "BusRute") == 2) CountBusKanpol --;
            if(GetPVarInt(playerid, "BusRute") == 3) CountBusHospital --;

            SendClientMessage(playerid, X11_DARKORANGE, "[Warning]:"WHITE" Waktu telah berakhir, anda gagal menjalankan pekerjaan sebagai supir bus");
        }
    }

    if(IsBusWorking(playerid) && BusWaiting[playerid])
    {
        if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 431)
        {
            if(BusTime[playerid] > 0)
            {
                BusTime[playerid] --; 
                PlayerTextDrawSetString(playerid, BusWait[playerid][0], sprintf("~w~Waiting_Time:_%d~n~~r~NOTE~w~: Tunggu untuk lanjut ke rute berikutnya", BusTime[playerid]));
                PlayerTextDrawShow(playerid, BusWait[playerid][0]);
                PlayerPlaySound(playerid, 43000, 0.0, 0.0, 0.0);
            }
            else if(BusIndex[playerid] == 36) // Hospital
			{
				BusIndex[playerid] = 37;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, -9.6364,-1524.4979,2.3418, 172.6937,-1541.7325,12.6236, 5.0);
                GiveMoney(playerid, 65);
                ShowItemBox(playerid, "Received $65", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 39)
			{
				BusIndex[playerid] = 40;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, 413.1094,-1446.2328,31.4077, 869.0794,-1407.2970,13.0327, 5.0);
                GiveMoney(playerid, 65);
                ShowItemBox(playerid, "Received $65", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 44)
			{
				BusIndex[playerid] = 45;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, 1314.3898,-925.8003,38.2064, 798.8291,-1003.4207,30.1350, 5.0);
                GiveMoney(playerid, 65);
                ShowItemBox(playerid, "Received $65", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 47)
			{
				BusIndex[playerid] = 48;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, 662.3487,-482.8038,16.2851, 545.5098,-412.1735,28.5848, 5.0);
                GiveMoney(playerid, 65);
                ShowItemBox(playerid, "Received $65", "Uang", 1212);
			}
            else if(BusIndex[playerid] == 57) // Angle Pine
			{
				BusIndex[playerid] = 58;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, -960.4075,-289.5359,36.5512, -1215.2813,-750.0646,61.8660, 5.0);
                GiveMoney(playerid, 75);
                ShowItemBox(playerid, "Received $75", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 65)
			{
				BusIndex[playerid] = 66;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, -2232.0400,-2256.2053,30.3266, -2179.5137,-2342.9849,30.5680, 5.0);
                GiveMoney(playerid, 75);
                ShowItemBox(playerid, "Received $75", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 67)
			{
				BusIndex[playerid] = 68;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, -2098.7969,-2452.3965,30.5595, -1863.3921,-2692.3953,54.1923, 5.0);
                GiveMoney(playerid, 75);
                ShowItemBox(playerid, "Received $75", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 68)
			{
				BusIndex[playerid] = 69;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, -1863.3921,-2692.3953,54.1923, -979.8699,-2871.4629,67.0867, 5.0);
                GiveMoney(playerid, 75);
                ShowItemBox(playerid, "Received $75", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 72)
			{
				BusIndex[playerid] = 73;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, -15.7218,-1419.0569,10.5612, 6.2545,-1529.1285,3.4320, 5.0);
                GiveMoney(playerid, 75);
                ShowItemBox(playerid, "Received $75", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 75)
			{
				BusIndex[playerid] = 76;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, 798.8906,-999.2177,31.0381, 565.5526,-412.2194,28.0132, 5.0);
                GiveMoney(playerid, 75);
                ShowItemBox(playerid, "Received $75", "Uang", 1212);
			}
            else if(BusIndex[playerid] == 7) // Airport
			{
				BusIndex[playerid] = 8;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				SetPlayerRaceCheckpoint(playerid, 0, 115.7602,-1609.5221,10.4715, 414.6135,-1775.9048,5.3755, 5.0);
                GiveMoney(playerid, 75);
                ShowItemBox(playerid, "Received $75", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 9)
			{
				BusIndex[playerid] = 10;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, 626.9605,-1747.7344,13.3627, 987.7833,-1804.6042,14.1609, 5.0);
                GiveMoney(playerid, 75);
                ShowItemBox(playerid, "Received $75", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 18)
			{
				BusIndex[playerid] = 19;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, 1548.4612,-2283.3728,13.4815, 1379.9990,-2282.7942,13.4309, 5.0);
                GiveMoney(playerid, 75);
                ShowItemBox(playerid, "Received $75", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 24)
			{
				BusIndex[playerid] = 25;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, 1159.5959,-901.1819,42.7490, 1223.1686,-251.2162,23.6118, 5.0);
                GiveMoney(playerid, 75);
                ShowItemBox(playerid, "Received $75", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 29)
			{
				BusIndex[playerid] = 30;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, 73.1662,-245.4490,1.6749, 77.4550,-299.0801,1.6755, 5.0);
                GiveMoney(playerid, 75);
                ShowItemBox(playerid, "Received $75", "Uang", 1212);
			}
            else if(BusIndex[playerid] == 83) // Kanpol
			{
				BusIndex[playerid] = 84;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, 682.3107,-791.2142,33.8053, 793.1075,-1025.8230,25.8031, 5.0);
                GiveMoney(playerid, 60);
                ShowItemBox(playerid, "Received $60", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 88)
			{
				BusIndex[playerid] = 89;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, 1034.3263,-1584.6193,13.3828, 1070.5468,-1715.2983,13.3828, 5.0);
                GiveMoney(playerid, 60);
                ShowItemBox(playerid, "Received $60", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 90)
			{
				BusIndex[playerid] = 91;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, 1294.7834,-1722.2269,13.3906, 1308.2179,-1855.0807,13.3828, 5.0);
                GiveMoney(playerid, 60);
                ShowItemBox(playerid, "Received $60", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 95)
			{
				BusIndex[playerid] = 96;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, 1309.9088,-2059.1707,58.0681, 1252.5984,-1923.3146,31.2505, 5.0);
                GiveMoney(playerid, 60);
                ShowItemBox(playerid, "Received $60", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 101)
			{
				BusIndex[playerid] = 102;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, 1064.3705,-1263.4731,14.1464, 1025.5914,-1137.3575,23.6563, 5.0);
                GiveMoney(playerid, 60);
                ShowItemBox(playerid, "Received $60", "Uang", 1212);
			}
			else if(BusIndex[playerid] == 103)
			{
				BusIndex[playerid] = 104;
				BusWaiting[playerid] = false;
				BusTime[playerid] = 0;
				DisablePlayerRaceCheckpoint(playerid);
				PlayerPlaySound(playerid, 1139, 0.0, 0.0, 0.0);
				PlayerTextDrawHide(playerid, BusWait[playerid][0]);
				SetPlayerRaceCheckpoint(playerid, 0, 812.9864,-1138.5229,23.7905, 797.4849,-1028.7705,25.4220, 5.0);
                GiveMoney(playerid, 60);
                ShowItemBox(playerid, "Received $60", "Uang", 1212);
			}
        }
    }
    return 1;   
}