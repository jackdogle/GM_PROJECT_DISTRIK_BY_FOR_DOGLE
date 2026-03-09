#include <YSI_Coding\y_hooks>

#define MAX_VEHICLE_JOB     (200)

new JobVehicleCount;

enum e_job_vehicle
{
    Vehicle,
    bool: Locked
}
new JobVehicle[MAX_VEHICLE_JOB][e_job_vehicle];

stock CreateJobVehicle(playerid, modelid, Float:x, Float:y, Float:z, Float:a, color1 = 1, color2 = 2, put = true, objective = false)
{
    if (JobVehicleCount >= MAX_VEHICLE_JOB)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Max Job Vehicles!");
        return 1;
    }
    else for (new iter = 1; iter < sizeof(JobVehicle); iter ++) if (JobVehicle[iter][Vehicle] == INVALID_VEHICLE_ID)
    {
        JobVehicle[iter][Vehicle] = CreateVehicle(modelid, x, y, z, a, color1, color2, -1);

        VehicleCore[JobVehicle[iter][Vehicle]][vCoreFuel] = MAX_FUEL_FULL;

        AccountData[playerid][pJobVehicle] = iter;

        if (GetPlayerInterior(playerid) != 0)
            LinkVehicleToInterior(JobVehicle[iter][Vehicle], GetPlayerInterior(playerid));

        if (GetPlayerVirtualWorld(playerid) != 0)
            SetVehicleVirtualWorld(JobVehicle[iter][Vehicle], GetPlayerVirtualWorld(playerid));

        if (put)
        {
            PutPlayerInVehicle(playerid, JobVehicle[iter][Vehicle], 0);
        }
        JobVehicle[iter][Locked] = false;
        LockVehicle(JobVehicle[iter][Vehicle], false);
        SetVehicleHealth(JobVehicle[iter][Vehicle], 1000.0);

        JobVehicleCount ++;
        if (objective) SetVehicleParamsForPlayer(JobVehicle[iter][Vehicle], playerid, 1, 0);
        SetVehicleNumberPlate(JobVehicle[iter][Vehicle], "JOB");
        return 1;
    }
    return 1;
}

stock DestroyJobVehicle(playerid, force = false)
{
    if (JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle] != INVALID_VEHICLE_ID)
    {
        JobVehicle[AccountData[playerid][pJobVehicle]][Locked] = false;
        LockVehicle(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], false);

        DestroyVehicle(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle]);
        JobVehicleCount --;
        JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle] = INVALID_VEHICLE_ID;

        AccountData[playerid][pJobVehicle] = 0;
        printf("[Vehicle Job]: Kendaraan Job milik %s dihancurkan", ReturnName(playerid));
    }

    if (force)
    {
        JobVehicle[AccountData[playerid][pJobVehicle]][Locked] = false;
        LockVehicle(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], false);

        DestroyVehicle(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle]);
        JobVehicleCount --;
        JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle] = INVALID_VEHICLE_ID;

        AccountData[playerid][pJobVehicle] = 0;
        printf("[Vehicle Job]: Kendaraan Job milik %s dihancurkan", ReturnName(playerid));
    }
    return 1;
}

hook OnGameModeInitEx()
{
    for (new i = 0; i < sizeof(JobVehicle); i ++) 
    {
        JobVehicle[i][Vehicle] = INVALID_VEHICLE_ID;
    }
    return 1;
}

hook OnGameModeExitEx()
{
    for (new i = 0; i < sizeof(JobVehicle); i ++)
    {
        JobVehicle[i][Vehicle] = INVALID_VEHICLE_ID;
    }
    return 1;
}