#include <YSI\y_hooks>

CountPlayerFactVeh(playerid)
{
    new count = 0;
    foreach(new id : PvtVehicles)
    {
        if(PlayerVehicle[id][pVehExists] 
            && PlayerVehicle[id][pVehOwnerID] == AccountData[playerid][pID] 
            && PlayerVehicle[id][pVehFaction] > 0) // hanya faction vehicle
        {
            count ++;
        }
    }
    return count;
}

stock VehicleFaction_Nearest(playerid, Float:range = 3.5)
{
	new Float:fX,
		Float:fY,
		Float:fZ;

	foreach(new i : PvtFVehicles)
	{
		if(PlayerFactionVeh[i][pVehFactPhysic] != INVALID_VEHICLE_ID)
		{
			GetVehiclePos(PlayerFactionVeh[i][pVehFactPhysic], fX, fY, fZ);

			if(IsPlayerInRangeOfPoint(playerid, range, fX, fY, fZ)) 
			{
				return i;
			}
		}
	}
	return -1;
}

forward OnFactionVehicleRespawn(i);
public OnFactionVehicleRespawn(i)
{
    if(PlayerFactionVeh[i][pVehFactFactionID] == FACTION_POLISI || PlayerFactionVeh[i][pVehFactFactionID] == FACTION_EMS)
    {
        PlayerFactionVeh[i][pVehFactPhysic] = CreateVehicle(PlayerFactionVeh[i][pVehFactModelID], PlayerFactionVeh[i][pVehFactPos][0], PlayerFactionVeh[i][pVehFactPos][1], PlayerFactionVeh[i][pVehFactPos][2], PlayerFactionVeh[i][pVehFactPos][3], PlayerFactionVeh[i][pVehFactColor1], PlayerFactionVeh[i][pVehFactColor2], -1, 1);
        VehicleCore[PlayerFactionVeh[i][pVehFactPhysic]][vCoreFuel] = PlayerFactionVeh[i][pVehFactFuel];
        SetVehicleVirtualWorld(PlayerFactionVeh[i][pVehFactPhysic], PlayerFactionVeh[i][pVehFactWorld]);
        LinkVehicleToInterior(PlayerFactionVeh[i][pVehFactPhysic], PlayerFactionVeh[i][pVehFactInterior]);
    }
    else
    {
        PlayerFactionVeh[i][pVehFactPhysic] = CreateVehicle(PlayerFactionVeh[i][pVehFactModelID], PlayerFactionVeh[i][pVehFactPos][0], PlayerFactionVeh[i][pVehFactPos][1], PlayerFactionVeh[i][pVehFactPos][2], PlayerFactionVeh[i][pVehFactPos][3], PlayerFactionVeh[i][pVehFactColor1], PlayerFactionVeh[i][pVehFactColor2], -1);
        VehicleCore[PlayerFactionVeh[i][pVehFactPhysic]][vCoreFuel] = PlayerFactionVeh[i][pVehFactFuel];
        SetVehicleVirtualWorld(PlayerFactionVeh[i][pVehFactPhysic], PlayerFactionVeh[i][pVehFactWorld]);
        LinkVehicleToInterior(PlayerFactionVeh[i][pVehFactPhysic], PlayerFactionVeh[i][pVehFactInterior]);
    }

    for(new x = 0; x < 16; x ++) 
	{
		if(DestroyDynamicObject(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][x]))
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][x] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	}

    if(PlayerFactionVeh[i][pVehFactFactionID] == FACTION_POLISI)
	{
		if(GetVehicleModel(PlayerFactionVeh[i][pVehFactPhysic]) == 560) //Sultan sabhara 16 array
		{
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0], 0, "{FFFF00}------", 130, "Arial", 190, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0], PlayerFactionVeh[i][pVehFactPhysic], -0.030, -0.810, 0.809, 270.000, 0.000, 0.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], 0, "{FFFF00}SABHARA", 130, "Arial", 90, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], PlayerFactionVeh[i][pVehFactPhysic], -0.030, -0.650, 0.817, -88.699, 0.000, 0.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2], 0, "{FFFF00}------", 130, "Arial", 190, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2], PlayerFactionVeh[i][pVehFactPhysic], -0.030, -0.360, 0.816, 270.000, 0.000, 0.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3] = CreateDynamicObject(19620,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3], PlayerFactionVeh[i][pVehFactPhysic], 0.010, -0.040, 0.829, 0.000, 0.000, 0.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][4] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][4], 0, "{FFFF00}|||||||||||", 130, "Arial", 76, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][4], PlayerFactionVeh[i][pVehFactPhysic], 0.000, -2.410, 0.174, 0.000, 0.000, 0.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][5] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][5], 0, "{FFFF00}POLISI", 130, "Arial", 120, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][5], PlayerFactionVeh[i][pVehFactPhysic], 0.000, 2.051, 0.299, -79.000, 0.000, 180.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][6] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][6], 0, "{FFFF00}||||||", 130, "Arial", 76, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][6], PlayerFactionVeh[i][pVehFactPhysic], -1.069, -1.770, 0.174, 0.000, 0.000, 270.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][7] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][7], 0, "{FFFF00}911", 130, "Arial", 150, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][7], PlayerFactionVeh[i][pVehFactPhysic], 0.000, -1.330, 0.614, -61.500, 0.000, 0.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][8] = CreateDynamicObject(1182,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][8], PlayerFactionVeh[i][pVehFactPhysic], -0.920, 2.649, -0.099, 0.000, 0.000, 0.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][9] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][9], 0, "{FFFF00}<", 120, "Arial", 190, 0, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][9], PlayerFactionVeh[i][pVehFactPhysic], -1.077, -0.760, -0.059, 0.000, 0.000, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][10] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][10], 0, "{FFFF00}<", 120, "Arial", 190, 0, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][10], PlayerFactionVeh[i][pVehFactPhysic], -1.077, -0.520, -0.059, 0.000, 0.000, -450.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][11] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][11], 0, "{FFFF00}POLISI", 130, "Arial", 60, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][11], PlayerFactionVeh[i][pVehFactPhysic], -1.077, 0.289, 0.040, 0.000, 0.000, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][12] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][12], 0, "{FFFF00}District ", 130, "Arial", 30, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][12], PlayerFactionVeh[i][pVehFactPhysic], -1.077, 0.289, -0.139, 0.000, 0.000, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][13] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][13], 0, "{FFFF00}>", 120, "Arial", 190, 0, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][13], PlayerFactionVeh[i][pVehFactPhysic], 1.076, -0.760, -0.059, 0.000, 0.000, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][14] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][14], 0, "{FFFF00}>", 120, "Arial", 190, 0, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][14], PlayerFactionVeh[i][pVehFactPhysic], 1.076, -0.570, -0.059, 0.000, 0.000, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][15] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][15], 0, "{FFFF00}POLISI", 130, "Arial", 60, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][15], PlayerFactionVeh[i][pVehFactPhysic], 1.077, 0.289, 0.040, 0.000, 0.000, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][16] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][16], 0, "{FFFF00}District ", 130, "Arial", 30, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][16], PlayerFactionVeh[i][pVehFactPhysic], 1.072, 0.289, -0.139, 0.000, 0.000, 90.000);
		}
		if(GetVehicleModel(PlayerFactionVeh[i][pVehFactPhysic]) == 426) // Premier
		{
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0], 0, "{FFFF00}POLISI", 130, "Arial", 30, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0], PlayerFactionVeh[i][pVehFactPhysic], -1.110, -0.019, 0.000, 0.000, 0.000, 180.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], 0, "{FFFF00}<<", 120, "Arial", 60, 0, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], PlayerFactionVeh[i][pVehFactPhysic], -1.110, -0.880, -0.089, 0.000, 0.000, 180.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2], 0, "{FFFF00}<", 120, "Arial", 60, 0, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2], PlayerFactionVeh[i][pVehFactPhysic], -1.110, 0.889, -0.089, 0.000, 0.000, 180.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3], 0, "{FFFF00}POLDA DISTRICT", 130, "Arial", 18, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3], PlayerFactionVeh[i][pVehFactPhysic], -1.110, -0.019, -0.289, 0.000, 0.000, 180.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][4] = CreateDynamicObject(19620,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][4], PlayerFactionVeh[i][pVehFactPhysic], 0.000, -0.360, 0.850, 0.000, 0.000, 0.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][5] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][5], 0, "{FFFF00}POLISI", 130, "Arial", 40, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][5], PlayerFactionVeh[i][pVehFactPhysic], -0.030, 1.686, 0.275, 0.000, -85.499, -270.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][6] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][6], 0, "{FFFF00}______", 130, "Arial", 40, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][6], PlayerFactionVeh[i][pVehFactPhysic], -0.030, 1.796, 0.267, 0.000, -85.699, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][7] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][7], 0, "{FFFF00}POLISI", 130, "Arial", 30, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][7], PlayerFactionVeh[i][pVehFactPhysic], 1.109, -0.019, 0.000, 0.000, 0.000, 0.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][8] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][8], 0, "{FFFF00}<<", 120, "Arial", 60, 0, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][8], PlayerFactionVeh[i][pVehFactPhysic], 1.115, -0.880, -0.089, 0.000, 0.000, 180.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][9] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][9], 0, "{FFFF00}<", 120, "Arial", 60, 0, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][9], PlayerFactionVeh[i][pVehFactPhysic], 1.119, 0.889, -0.089, 0.000, 0.000, 180.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][10] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][10], 0, "{FFFF00}POLDA DISTRICT", 130, "Arial", 18, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][10], PlayerFactionVeh[i][pVehFactPhysic], 1.109, -0.019, -0.289, 0.000, 0.000, 0.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][11] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][11], 0, "{FFFF00}911", 130, "Arial", 50, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][11], PlayerFactionVeh[i][pVehFactPhysic], 0.059, -1.627, 0.585, 0.000, -54.999, 270.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][13] = CreateDynamicObject(1181,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][13], PlayerFactionVeh[i][pVehFactPhysic], -0.890, 2.520, -0.179, 0.000, 0.000, 0.000);
		}
		if(GetVehicleModel(PlayerFactionVeh[i][pVehFactPhysic]) == 468) // Sanchez PD 
		{
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0], 0, "{FFFF00}POLISI", 130, "Arial", 25, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0], PlayerFactionVeh[i][pVehFactPhysic], -0.120, 0.190, 0.318, 0.000, 45.799, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], 0, "{FFFF00}POLISI", 130, "Arial", 25, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], PlayerFactionVeh[i][pVehFactPhysic], 0.118, 0.153, 0.285, 0.000, -43.799, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2], 0, "{FFFF00}<<", 120, "Arial", 30, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2], PlayerFactionVeh[i][pVehFactPhysic], -0.179, -0.469, 0.119, -3.099, 0.000, -93.299);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3], 0, "{FFFF00}>>", 120, "Arial", 30, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3], PlayerFactionVeh[i][pVehFactPhysic], 0.190, -0.519, 0.119, 0.000, 0.000, 90.000);
		}
	}
	if(PlayerFactionVeh[i][pVehFactFactionID] == FACTION_EMS)
	{
		if(GetVehicleModel(PlayerFactionVeh[i][pVehFactPhysic]) == 468) // sanchez 1 Array
		{
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0] = CreateDynamicObject(2714,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0], 0, "{FFFFFF}EMS", 130, "Arial", 45, 0, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0], PlayerFactionVeh[i][pVehFactPhysic], -0.109, 0.176, 0.328, -3.799, 46.699, 270.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1] = CreateDynamicObject(2714,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], 0, "{FFFFFF}EMS", 130, "Arial", 45, 0, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], PlayerFactionVeh[i][pVehFactPhysic], 0.110, 0.183, 0.321, -4.699, -47.699, 90.000);
		}
	}
	if(PlayerFactionVeh[i][pVehFactFactionID] == FACTION_TRANS)
	{
		if(GetVehicleModel(PlayerFactionVeh[i][pVehFactPhysic]) == 426)
		{
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0] = CreateDynamicObject(19308,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0], PlayerFactionVeh[i][pVehFactPhysic], 0.000, -0.460, 0.938, 0.000, 0.000, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1] = CreateDynamicObject(11744,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], 0, 18646, "matcolours", "grey-93-percent", 0);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], PlayerFactionVeh[i][pVehFactPhysic], 1.149, 0.050, -0.159, 0.000, 90.000, 0.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2], 0, "{FFFFFF}T", 130, "Arial", 80, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2], PlayerFactionVeh[i][pVehFactPhysic], 1.179, 0.029, -0.179, 0.000, 0.000, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3], 0, "{000000}AXI", 130, "Arial", 70, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3], PlayerFactionVeh[i][pVehFactPhysic], 1.140, 0.358, -0.209, 0.000, 0.000, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][4] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][4], 0, "{000000}AXI", 130, "Arial", 70, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][4], PlayerFactionVeh[i][pVehFactPhysic], -1.139, 0.138, -0.209, 0.000, 0.000, 270.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][5] = CreateDynamicObject(11744,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterial(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][5], 0, 18646, "matcolours", "grey-93-percent", 0);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][5], PlayerFactionVeh[i][pVehFactPhysic], -1.115, 0.460, -0.159, 0.000, 90.000, 0.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][6] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][6], 0, "{FFFFFF}T", 130, "Arial", 80, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][6], PlayerFactionVeh[i][pVehFactPhysic], -1.139, 0.479, -0.179, 0.000, 0.000, 270.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][7] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][7], 0, "{FFFFFF})", 130, "Wingdings", 150, 0, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][7], PlayerFactionVeh[i][pVehFactPhysic], 0.350, -1.736, 0.568, -53.200, -90.100, 2.600);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][8] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][8], 0, "{FFFFFF}Trans App", 130, "Arial", 50, 0, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][8], PlayerFactionVeh[i][pVehFactPhysic], -0.290, -1.700, 0.605, -52.399, 0.000, 0.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][9] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][9], 0, "{FFFFFF}Download On PlayStore", 130, "Arial", 30, 0, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][9], PlayerFactionVeh[i][pVehFactPhysic], -0.330, -1.816, 0.512, -51.599, 0.000, -0.900);
		}
	}
	if(PlayerFactionVeh[i][pVehFactFactionID] == FACTION_BENGKEL)
	{
		if(GetVehicleModel(PlayerFactionVeh[i][pVehFactPhysic]) == 525) // towing 14 array
		{
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0], 0, "{FF0000}/", 130, "Arial", 160, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0], PlayerFactionVeh[i][pVehFactPhysic], -1.220, 1.481, 0.220, 0.000, 0.000, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], 0, "{FF0000}/", 130, "Arial", 160, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], PlayerFactionVeh[i][pVehFactPhysic], -1.220, 1.381, 0.220, 0.000, 0.000, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2], 0, "{FFFFFF}/", 130, "Arial", 160, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2], PlayerFactionVeh[i][pVehFactPhysic], -1.220, 1.281, 0.220, 0.000, 0.000, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3], 0, "{FFFFFF}/", 130, "Arial", 160, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3], PlayerFactionVeh[i][pVehFactPhysic], -1.220, 1.171, 0.220, 0.000, 0.000, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][4] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][4], 0, "{FFFFFF}BENGKEL", 130, "Arial", 80, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][4], PlayerFactionVeh[i][pVehFactPhysic], -1.220, 0.520, 0.220, 0.000, 0.000, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][5] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][5], 0, "{FFFFFF}d", 130, "Webdings", 80, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][5], PlayerFactionVeh[i][pVehFactPhysic], -1.220, -0.150, 0.290, 0.000, 0.000, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][6] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][6], 0, "{FFFF00}District ", 130, "Arial", 40, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][6], PlayerFactionVeh[i][pVehFactPhysic], -1.150, 0.550, -0.270, 17.100, 0.000, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][7] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][7], 0, "{FF0000}/", 130, "Arial", 160, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][7], PlayerFactionVeh[i][pVehFactPhysic], 1.211, 1.381, 0.220, 0.000, 0.000, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][8] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][8], 0, "{FF0000}/", 130, "Arial", 160, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][8], PlayerFactionVeh[i][pVehFactPhysic], 1.211, 1.291, 0.220, 0.000, 0.000, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][9] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][9], 0, "{FFFFFF}/", 130, "Arial", 160, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][9], PlayerFactionVeh[i][pVehFactPhysic], 1.212, 1.191, 0.220, 0.000, 0.000, 450.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][10] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][10], 0, "{FFFFFF}/", 130, "Arial", 160, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][10], PlayerFactionVeh[i][pVehFactPhysic], 1.211, 1.091, 0.220, 0.000, 0.000, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][11] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][11], 0, "{FFFFFF}BENGKEL", 130, "Arial", 80, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][11], PlayerFactionVeh[i][pVehFactPhysic], 1.211, 0.450, 0.220, 0.000, 0.000, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][12] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][12], 0, "{FFFFFF}d", 130, "Webdings", 80, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][12], PlayerFactionVeh[i][pVehFactPhysic], 1.210, -0.230, 0.350, 0.000, 0.000, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][13] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][13], 0, "{FFFFFF}Siap Melayani Kendaraan Anda", 130, "Arial", 35, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][13], PlayerFactionVeh[i][pVehFactPhysic], -0.038, 0.820, 1.200, -45.799, 0.000, 180.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][14] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][14], 0, "{000000}u", 130, "Webdings", 100, 0, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][14], PlayerFactionVeh[i][pVehFactPhysic], 1.337, -0.620, 0.172, 3.799, 0.000, 810.000);
		}
		if(GetVehicleModel(PlayerFactionVeh[i][pVehFactPhysic]) == 468) // Sanchez PD 
		{
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0], 0, "{FFB5C5}BENGKEL", 130, "Arial", 25, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0], PlayerFactionVeh[i][pVehFactPhysic], -0.120, 0.190, 0.318, 0.000, 45.799, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], 0, "{FFB5C5}BENGKEL", 130, "Arial", 25, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], PlayerFactionVeh[i][pVehFactPhysic], 0.118, 0.153, 0.285, 0.000, -43.799, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2], 0, "{FFB5C5}>>", 120, "Arial", 30, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2], PlayerFactionVeh[i][pVehFactPhysic], -0.179, -0.469, 0.119, -3.099, 0.000, -93.299);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3], 0, "{FFB5C5}<<", 120, "Arial", 30, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3], PlayerFactionVeh[i][pVehFactPhysic], 0.190, -0.519, 0.119, 0.000, 0.000, 90.000);
		}
	}
	if(PlayerFactionVeh[i][pVehFactFactionID] == FACTION_PEDAGANG)
	{
		if(GetVehicleModel(PlayerFactionVeh[i][pVehFactPhysic]) == 489) 
		{
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0], 0, "{FFFFFF},", 130, "Webdings", 150, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][0], PlayerFactionVeh[i][pVehFactPhysic], -1.220, -0.040, -0.099, 0.000, 0.000, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], 0, "{FFFFFF}Resto", 130, "Arial", 80, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][1], PlayerFactionVeh[i][pVehFactPhysic], -1.220, 0.520, -0.139, 0.000, 0.000, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2], 0, "{FFFFFF}DISTRICT", 130, "Arial", 60, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][2], PlayerFactionVeh[i][pVehFactPhysic], -1.220, 0.369, -0.369, 0.000, 0.000, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3], 0, "{FFFFFF}/", 130, "Webdings", 150, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][3], PlayerFactionVeh[i][pVehFactPhysic], -1.220, -0.899, 0.079, 0.000, 0.000, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][4] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][4], 0, "{FFFF00}/", 130, "Webdings", 150, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][4], PlayerFactionVeh[i][pVehFactPhysic], -1.220, -0.619, 0.079, 0.000, 0.000, -90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][5] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][5], 0, "{FFFFFF}Resto", 130, "Arial", 80, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][5], PlayerFactionVeh[i][pVehFactPhysic], 1.217, -0.030, -0.139, 0.000, 0.000, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][6] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][6], 0, "{FFFFFF},", 130, "Webdings", 120, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][6], PlayerFactionVeh[i][pVehFactPhysic], 1.217, 0.559, -0.119, 0.000, 0.000, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][7] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][7], 0, "{FFFFFF}DISTRICT", 130, "Arial", 60, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][7], PlayerFactionVeh[i][pVehFactPhysic], 1.205, 0.129, -0.369, 0.000, 0.000, 450.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][8] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][8], 0, "{FFFFFF}/", 130, "Webdings", 150, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][8], PlayerFactionVeh[i][pVehFactPhysic], 1.219, -0.969, 0.069, 0.000, 0.000, 90.000);
			FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][9] = CreateDynamicObject(2662,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
			SetDynamicObjectMaterialText(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][9], 0, "{FFFF00}/", 130, "Webdings", 150, 1, 0, 0, 1);
			AttachDynamicObjectToVehicle(FactionVehObject[PlayerFactionVeh[i][pVehFactPhysic]][9], PlayerFactionVeh[i][pVehFactPhysic], 1.219, -0.679, 0.069, 0.000, 0.000, 90.000);
		}
	}

    if(PlayerFactionVeh[i][pVehFactHealth] < 350.0)
    {
        SetValidVehicleHealth(PlayerFactionVeh[i][pVehFactPhysic], 350.0);
    }
    else
    {
        SetValidVehicleHealth(PlayerFactionVeh[i][pVehFactPhysic], PlayerFactionVeh[i][pVehFactHealth]);
    }
    UpdateVehicleDamageStatus(PlayerFactionVeh[i][pVehFactPhysic], PlayerFactionVeh[i][pVehFactDamage][0], PlayerFactionVeh[i][pVehFactDamage][1], PlayerFactionVeh[i][pVehFactDamage][2], PlayerFactionVeh[i][pVehFactDamage][3]);
    if(IsEngineVehicle(PlayerFactionVeh[i][pVehFactPhysic]))
    {
        SwitchVehicleEngine(PlayerFactionVeh[i][pVehFactPhysic], false);
    }
    else
    {
        SwitchVehicleEngine(PlayerFactionVeh[i][pVehFactPhysic], true);
    }
    return 1;
}

SaveFactVeh(i)
{
    VehicleFact_GetStatus(i);
    new cQuery[2248];

    mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_factionvehicle` SET ");
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_OwnerID`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactOwnerID]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_PosX`='%f', ", cQuery, PlayerFactionVeh[i][pVehFactPos][0]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_PosY`='%f', ", cQuery, PlayerFactionVeh[i][pVehFactPos][1]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_PosZ`='%f', ", cQuery, PlayerFactionVeh[i][pVehFactPos][2]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_PosA`='%f', ", cQuery, PlayerFactionVeh[i][pVehFactPos][3]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Health`='%f', ",cQuery, PlayerFactionVeh[i][pVehFactHealth]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Fuel`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactFuel]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Interior`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactInterior]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_World`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactWorld]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Damage0`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactDamage][0]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Damage1`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactDamage][1]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Damage2`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactDamage][2]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Damage3`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactDamage][3]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_ModelID`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactModelID]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Color1`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactColor1]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Color2`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactColor2]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_DCTime`=%d, ", cQuery, gettime() + 3600);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Faction`=%d ", cQuery, PlayerFactionVeh[i][pVehFactFactionID]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sWHERE `vID`= '%d'", cQuery, PlayerFactionVeh[i][pVehFactID]);
    mysql_query(g_SQL, cQuery, true);
    return 1;
}

/*RemoveFactionVehicle(playerid)
{
    foreach(new i : PvtFVehicles)
    {
        if(PlayerFactionVeh[i][pVehFactExists] && PlayerFactionVeh[i][pVehFactOwnerID] == AccountData[playerid][pID])
        {
            VehicleFact_GetStatus(i);
            new cQuery[2248];

            mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_factionvehicle` SET ");
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_OwnerID`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactOwnerID]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_PosX`='%f', ", cQuery, PlayerFactionVeh[i][pVehFactPos][0]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_PosY`='%f', ", cQuery, PlayerFactionVeh[i][pVehFactPos][1]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_PosZ`='%f', ", cQuery, PlayerFactionVeh[i][pVehFactPos][2]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_PosA`='%f', ", cQuery, PlayerFactionVeh[i][pVehFactPos][3]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Health`='%f', ",cQuery, PlayerFactionVeh[i][pVehFactHealth]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Fuel`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactFuel]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Interior`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactInterior]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_World`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactWorld]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Damage0`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactDamage][0]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Damage1`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactDamage][1]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Damage2`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactDamage][2]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Damage3`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactDamage][3]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_ModelID`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactModelID]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Color1`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactColor1]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Color2`=%d, ", cQuery, PlayerFactionVeh[i][pVehFactColor2]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_DCTime`=%d, ", cQuery, gettime() + 3600);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PFVeh_Faction`=%d ", cQuery, PlayerFactionVeh[i][pVehFactFactionID]);
            mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sWHERE `vID`=%d", cQuery, PlayerFactionVeh[i][pVehFactID]);
            mysql_query(g_SQL, cQuery, true);

            if(IsValidVehicle(PlayerFactionVeh[i][pVehFactPhysic]))
            {
                DisableVehicleSpeedCap(PlayerFactionVeh[i][pVehFactPhysic]);
                DestroyVehicle(PlayerFactionVeh[i][pVehFactPhysic]);
                PlayerFactionVeh[i][pVehFactPhysic] = INVALID_VEHICLE_ID;
            }

            PlayerFactionVeh[i][pVehFactOwnerID] = -1;
            PlayerFactionVeh[i][pVehFactExists] = false;
            Iter_Remove(PvtFVehicles, i);
        }
    }
    return 1;
}*/

VehicleFaction_Delete(playerid)
{
    foreach(new i : PvtVehicles)
    {
        if(PlayerVehicle[i][pVehExists] && IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
        {
            if(PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID] && PlayerVehicle[i][pVehFaction] > 0)
            {
                new strgbg[128];
                new hvid = PlayerVehicle[i][pVehID]; // pastikan lu punya penyimpanan ID database di struct ini

                // hapus di array
                PlayerVehicle[i][pVehExists] = false;
                if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                {
                    DisableVehicleSpeedCap(PlayerVehicle[i][pVehPhysic]);
                    SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], false, PlayerVehicle[i][pVehNeon], 0);

                    DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
                }
                PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;

                // hapus di DB
                mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM player_vehicles WHERE id=%d", hvid);
                mysql_tquery(g_SQL, strgbg);

                // hapus dari iterator
                Iter_Remove(PvtVehicles, i);
            }
        }
    }
    return 1;
}

/*VehicleFaction_Create1(ownerid, modelid, factionid, Float:x, Float:y, Float:z, Float:a, color1, color2)
{
    new i = Iter_Free(PvtFVehicles);

    if(i == INVALID_ITERATOR_SLOT)
        return printf("Unable to create player fact vehicle!");

    PlayerFactionVeh[i][pVehFactExists] = true;
    PlayerFactionVeh[i][pVehFactModelID] = modelid;
    PlayerFactionVeh[i][pVehFactOwnerID] = AccountData[ownerid][pID];

    PlayerFactionVeh[i][pVehFactPos][0] = x;
    PlayerFactionVeh[i][pVehFactPos][1] = y;
    PlayerFactionVeh[i][pVehFactPos][2] = z;
    PlayerFactionVeh[i][pVehFactPos][3] = a;

    PlayerFactionVeh[i][pVehFactColor1] = color1;
    PlayerFactionVeh[i][pVehFactColor2] = color2;

    PlayerFactionVeh[i][pVehFactDCTime] = 0;
    PlayerFactionVeh[i][pVehFactHealth] = 1000.0;
    PlayerFactionVeh[i][pVehFactFuel] = MAX_FUEL_FULL;
    PlayerFactionVeh[i][pVehFactFactionID] = factionid;
    
    PlayerFactionVeh[i][pVehFactDamage][0] = 0;
	PlayerFactionVeh[i][pVehFactDamage][1] = 0;
	PlayerFactionVeh[i][pVehFactDamage][2] = 0;
	PlayerFactionVeh[i][pVehFactDamage][3] = 0;
    PlayerFactionVeh[i][pVehFactInterior] = 0;
    PlayerFactionVeh[i][pVehFactWorld] = 0;

    OnFactionVehicleRespawn(i);
    Iter_Add(PvtFVehicles, i);
    PutPlayerInVehicle(ownerid, PlayerFactionVeh[i][pVehFactPhysic], 0);
    mysql_tquery(g_SQL, "INSERT INTO `player_factionvehicle` (`PFVeh_ModelID`) VALUES (0)", "OnFactVehCreated", "d", i);
    return 1;
}*/


forward OnFactVehCreated(carid);
public OnFactVehCreated(carid)
{
    if(carid == -1 || !PlayerFactionVeh[carid][pVehFactExists])
        return false;
    
    PlayerFactionVeh[carid][pVehFactID] = cache_insert_id();
    PlayerFactionVeh[carid][pVehFactExists] = true;
    SaveFactVeh(carid);
    return 1;
}

VehicleFact_GetStatus(carid)
{
    if(PlayerFactionVeh[carid][pVehFactExists])
    {
        if(IsValidVehicle(PlayerFactionVeh[carid][pVehFactPhysic]) && PlayerFactionVeh[carid][pVehFactPhysic] != INVALID_VEHICLE_ID)
        {
            GetVehicleDamageStatus(PlayerFactionVeh[carid][pVehFactPhysic], PlayerFactionVeh[carid][pVehFactDamage][0], PlayerFactionVeh[carid][pVehFactDamage][1], PlayerFactionVeh[carid][pVehFactDamage][2], PlayerFactionVeh[carid][pVehFactDamage][3]);
            GetVehicleHealth(PlayerFactionVeh[carid][pVehFactPhysic], PlayerFactionVeh[carid][pVehFactHealth]);
            if(PlayerFactionVeh[carid][pVehFactHealth] < 0.0 || PlayerFactionVeh[carid][pVehFactHealth] > 1000.0) PlayerFactionVeh[carid][pVehFactHealth] = PlayerFactionVeh[carid][pVehFactHealth];

            PlayerFactionVeh[carid][pVehFactFuel] = VehicleCore[PlayerFactionVeh[carid][pVehFactPhysic]][vCoreFuel];
            PlayerFactionVeh[carid][pVehFactWorld] = GetVehicleVirtualWorld(PlayerFactionVeh[carid][pVehFactPhysic]);
            PlayerFactionVeh[carid][pVehFactInterior] = GetVehicleInterior(PlayerFactionVeh[carid][pVehFactPhysic]);

            GetVehiclePos(PlayerFactionVeh[carid][pVehFactPhysic], PlayerFactionVeh[carid][pVehFactPos][0], PlayerFactionVeh[carid][pVehFactPos][1], PlayerFactionVeh[carid][pVehFactPos][2]);
            GetVehicleZAngle(PlayerFactionVeh[carid][pVehFactPhysic], PlayerFactionVeh[carid][pVehFactPos][3]);
        }
    }
    return 1;
}

forward LoadPlayerFactionVehicle(playerid);
public LoadPlayerFactionVehicle(playerid)
{
    new query[125];
    mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_factionvehicle` WHERE `PFVeh_OwnerID`=%d", AccountData[playerid][pID]);
    mysql_query(g_SQL, query, true);
    new count = cache_num_rows();
    if(count > 0)
    {
        for(new x = 0; x < count; x ++)
        {
            new i = Iter_Free(PvtFVehicles);

            PlayerFactionVeh[i][pVehFactExists] = true;
            cache_get_value_name_int(x, "vID", PlayerFactionVeh[i][pVehFactID]);
            cache_get_value_name_int(x, "PFVeh_OwnerID", PlayerFactionVeh[i][pVehFactOwnerID]);
            cache_get_value_name_float(x, "PFVeh_PosX", PlayerFactionVeh[i][pVehFactPos][0]);
            cache_get_value_name_float(x, "PFVeh_PosY", PlayerFactionVeh[i][pVehFactPos][1]);
            cache_get_value_name_float(x, "PFVeh_PosZ", PlayerFactionVeh[i][pVehFactPos][2]);
            cache_get_value_name_float(x, "PFVeh_PosA", PlayerFactionVeh[i][pVehFactPos][3]);
            cache_get_value_name_float(x, "PFVeh_Health", PlayerFactionVeh[i][pVehFactHealth]);
            cache_get_value_name_int(x, "PFVeh_Fuel", PlayerFactionVeh[i][pVehFactFuel]);
            cache_get_value_name_int(x, "PFVeh_Interior", PlayerFactionVeh[i][pVehFactInterior]);
            cache_get_value_name_int(x, "PFVeh_World", PlayerFactionVeh[i][pVehFactWorld]);
            cache_get_value_name_int(x, "PFVeh_Damage0", PlayerFactionVeh[i][pVehFactDamage][0]);
            cache_get_value_name_int(x, "PFVeh_Damage1", PlayerFactionVeh[i][pVehFactDamage][1]);
            cache_get_value_name_int(x, "PFVeh_Damage2", PlayerFactionVeh[i][pVehFactDamage][2]);
            cache_get_value_name_int(x, "PFVeh_Damage3", PlayerFactionVeh[i][pVehFactDamage][3]);
            cache_get_value_name_int(x, "PFVeh_Color1", PlayerFactionVeh[i][pVehFactColor1]);
            cache_get_value_name_int(x, "PFVeh_Color2", PlayerFactionVeh[i][pVehFactColor2]);
            cache_get_value_name_int(x, "PFVeh_ModelID", PlayerFactionVeh[i][pVehFactModelID]);
            cache_get_value_name_int(x, "PFVeh_DCTime", PlayerFactionVeh[i][pVehFactDCTime]);
            cache_get_value_name_int(x, "PFVeh_Faction", PlayerFactionVeh[i][pVehFactFactionID]);
        
            UpdateVehicleDamageStatus(PlayerFactionVeh[i][pVehFactPhysic], PlayerFactionVeh[i][pVehFactDamage][0], PlayerFactionVeh[i][pVehFactDamage][1], PlayerFactionVeh[i][pVehFactDamage][2], PlayerFactionVeh[i][pVehFactDamage][3]);
            Iter_Add(PvtFVehicles, i);

            if(gettime() > PlayerFactionVeh[i][pVehFactDCTime])
            {
                PlayerFactionVeh[i][pVehFactDCTime] = 0;
                PlayerFactionVeh[i][pVehFactPhysic] = INVALID_VEHICLE_ID;
                new icsr[255];
                mysql_format(g_SQL, icsr, sizeof(icsr), "DELETE FROM `player_factionvehicle` WHERE `vID`=%d", PlayerFactionVeh[i][pVehFactID]);
                mysql_tquery(g_SQL, icsr);
            }
            else
            {
                PlayerFactionVeh[i][pVehFactDCTime] = 0;
                OnFactionVehicleRespawn(i);
            }
        }
        new time = GetTickCount();
        printf("[Faction Statis Vehicle]: Loaded %s (%d) - %d ms", AccountData[playerid][pName], playerid, time);
    }
    return 1;
}

hook OnVehicleSpawn(vehicleid)
{
	foreach(new i : PvtFVehicles)
	{
		if(PlayerFactionVeh[i][pVehFactPhysic] == vehicleid)
		{
			PlayerFactionVeh[i][pVehFactExists] = false;
			if(IsValidVehicle(PlayerFactionVeh[i][pVehFactPhysic])) DestroyVehicle(PlayerFactionVeh[i][pVehFactPhysic]);
			PlayerFactionVeh[i][pVehFactPhysic] = INVALID_VEHICLE_ID;

			foreach(new pid : Player) if(PlayerFactionVeh[i][pVehFactOwnerID] == AccountData[pid][pID])
			{
				Info(pid, "Kendaraan faction kamu hancur, kendaraan otomatis dihilangkan");
			}
			new shstr[255];
			mysql_format(g_SQL, shstr, sizeof(shstr), "DELETE FROM `player_factionvehicle` WHERE `vID` = %d", PlayerFactionVeh[i][pVehFactID]);
			mysql_tquery(g_SQL, shstr);
			Iter_Remove(PvtFVehicles, i);
		}
	}
    return 1;
}