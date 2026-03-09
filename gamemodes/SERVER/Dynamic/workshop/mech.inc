// Private Vehicle Components

#include <YSI\y_hooks>


//Mech JOB 
JavaTR: CheckCar(playerid, vehicleid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(AccountData[playerid][pWorkshop] != -1)
	{
		if(GetNearestVehicleToPlayer(playerid, 3.5, false) == vehicleid)
		{
			if(IsValidVehicle(vehicleid))
			{
				AccountData[playerid][pMechVeh] = vehicleid;
				ShowTDN(playerid, NOTIFICATION_SUKSES, "Checking done!"); 
				ClearAnimations(playerid);
				return 1;
			}
		}
	}
	return 1;
}

JavaTR: BodyFix(playerid, vehicleid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(AccountData[playerid][pWorkshop] != -1)
	{
		if(GetNearestVehicleToPlayer(playerid, 3.5, false) == vehicleid)
		{
			if(IsValidVehicle(vehicleid))
			{
				new panels, doors, light, tires;	
				GetVehicleDamageStatus(vehicleid, panels, doors, light, tires);		
				UpdateVehicleDamageStatus(vehicleid, 0, 0, 0, tires);
				ValidRepairVehicle(vehicleid);
				ShowTDN(playerid, NOTIFICATION_SUKSES, "Fix body done!");
				AccountData[playerid][pMechVeh] = vehicleid;
				ClearAnimations(playerid);
				return 1;
			}
		}
	}
	return 1;
}

JavaTR: EngineUpgrade(playerid, vehicleid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(AccountData[playerid][pWorkshop] != -1)
	{
		if(GetNearestVehicleToPlayer(playerid, 3.8, false) == vehicleid)
		{
			if(IsValidVehicle(vehicleid))
			{
				SetVehicleHealth(vehicleid, 2000);
				ShowTDN(playerid, NOTIFICATION_SUKSES, "Upgrade engine done!");
				AccountData[playerid][pMechVeh] = vehicleid;
				ClearAnimations(playerid);
				return 1;
			}
		}
	}
	return 1;
}

JavaTR: EngineFix(playerid, vehicleid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(AccountData[playerid][pWorkshop] != -1)
	{
		if(GetNearestVehicleToPlayer(playerid, 3.8, false) == vehicleid)
		{
			if(IsValidVehicle(vehicleid))
			{
				SetVehicleHealth(vehicleid, 1000);
				ShowTDN(playerid, NOTIFICATION_SUKSES, "Fix engine done!");
				AccountData[playerid][pMechVeh] = vehicleid;
				ClearAnimations(playerid);
				return 1;
			}
		}
	}
	return 1;
}

JavaTR: SprayCar(playerid, vehicleid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(AccountData[playerid][pWorkshop] != -1)
	{
		if(GetNearestVehicleToPlayer(playerid, 3.8, false) == vehicleid)
		{
			if(IsValidVehicle(vehicleid))
			{
				
				ChangeVehicleColor(vehicleid, AccountData[playerid][pMechColor1], AccountData[playerid][pMechColor2]);
				foreach(new ii : PvtVehicles)
				{
					if(vehicleid == PlayerVehicle[ii][pVehPhysic])
					{
						PlayerVehicle[ii][pVehColor1] = AccountData[playerid][pMechColor1];
						PlayerVehicle[ii][pVehColor2] = AccountData[playerid][pMechColor2];
					}
				}
				ShowTDN(playerid, NOTIFICATION_SUKSES, "Spraying done!");
				AccountData[playerid][pMechVeh] = vehicleid;
				ClearAnimations(playerid);
				return 1;
			}
		}
	}
	return 1;
}

JavaTR: PaintjobCar(playerid, vehicleid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(AccountData[playerid][pWorkshop] != -1)
	{
		if(GetNearestVehicleToPlayer(playerid, 3.8, false) == vehicleid)
		{
			if(IsValidVehicle(vehicleid))
			{
				
				ChangeVehiclePaintjob(vehicleid, AccountData[playerid][pMechColor1]);
				foreach(new ii : PvtVehicles)
				{
					if(vehicleid == PlayerVehicle[ii][pVehPhysic])
					{
						PlayerVehicle[ii][pVehPaintjob] = AccountData[playerid][pMechColor1];
					}
				}
				ShowTDN(playerid, NOTIFICATION_SUKSES, "Painting done!");
				AccountData[playerid][pMechVeh] = vehicleid;
				ClearAnimations(playerid);
				return 1;
			}
		}
	}
	return 1;
}

JavaTR: ModifCar(playerid, vehicleid)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(AccountData[playerid][pWorkshop] != -1)
	{
		if(GetNearestVehicleToPlayer(playerid, 3.8, false) == vehicleid)
		{
			if(IsValidVehicle(vehicleid))
			{
				
				AddVehicleComponent(vehicleid, AccountData[playerid][pMechColor1]);
				SavePVComponents(vehicleid, AccountData[playerid][pMechColor1]);
				if(AccountData[playerid][pMechColor2] != 0)
				{
					AddVehicleComponent(vehicleid, AccountData[playerid][pMechColor2]);
					SavePVComponents(vehicleid, AccountData[playerid][pMechColor2]);
				}
				
				ShowTDN(playerid, NOTIFICATION_SUKSES, "Modif done!");
				AccountData[playerid][pMechVeh] = vehicleid;
				ClearAnimations(playerid);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				return 1;
			}
		}
	}
	return 1;
}
