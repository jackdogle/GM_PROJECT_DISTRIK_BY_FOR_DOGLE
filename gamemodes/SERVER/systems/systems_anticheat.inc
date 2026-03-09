#include <YSI\y_hooks>

new AntiCheatKontol = 1;
#define MAX_ANTICHEAT_WARNINGS   	2

public OnPlayerTeleport(playerid, Float:distance)
{
	if((AntiCheatKontol) && AccountData[playerid][pAdmin] < 1)
	{
		if(AccountData[playerid][UsingDoor] == false)
		{
			if(!IsPlayerInRangeOfPoint(playerid, 10.0, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ]))
			{
				AccountData[playerid][pACWarns]++;

				if(AccountData[playerid][pACWarns] < MAX_ANTICHEAT_WARNINGS)
				{
					if(IsPlayerInAnyVehicle(playerid))
					{
						SendStaffMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"GRAY" diduga menggunakan Teleport Hack. "YELLOW"[D: %.3f m] [%s]", AccountData[playerid][pName], playerid, distance, GetVehicleModelName(GetPlayerVehicleID(playerid)));
					}
					else 
					{
						SendStaffMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"GRAY" diduga menggunakan Teleport Hack. "YELLOW"[D: %.3f m]", AccountData[playerid][pName], playerid, distance);
					}
				}
				else
				{
					SendClientMessageToAllEx(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"GRAY" telah ditendang dari server karena menggunakan Teleport Hack!", AccountData[playerid][pName], playerid);
					KickEx(playerid);
				}
			}
		}
	}
	return 1;
}

public OnPlayerAirbreak(playerid)
{
	if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1)
	{
		AccountData[playerid][pACWarns] ++;

		if(AccountData[playerid][pACWarns] < MAX_ANTICHEAT_WARNINGS)
		{
			SendStaffMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" diduga menggunakan Air Break Hacks", AccountData[playerid][pName], playerid);
		}
		else 
		{
			SendClientMessageToAllEx(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" ditendang dari server karena diduga menggunakan Air Break Hacks.", AccountData[playerid][pName], playerid);
			KickEx(playerid);
		}
	}
	return 1;
}

NgecekCiter(playerid)
{
	if(gettime() > AccountData[playerid][pACTime])
	{
	    // Speedhacking
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && GetVehicleSpeed(GetPlayerVehicleID(playerid)) > 350.0 && AccountData[playerid][pAdmin] < 2)
		{
			SendClientMessageToAllEx(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Vehicle Speed Hack "YELLOW"[%.1f Kmh] - %s", AccountData[playerid][pName], playerid, GetVehicleSpeed(GetPlayerVehicleID(playerid)), GetVehicleModelName(GetPlayerVehicleID(playerid)));
			KickEx(playerid);
		}
		// Jetpack
		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK && AccountData[playerid][pAdmin] < 2 && !AccountData[playerid][pJetpack])
		{
			SendClientMessageToAllEx(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Jetpack Hacks!", AccountData[playerid][pName], playerid);
			KickEx(playerid);
		}
		// Armor hacks
		if(!IsPlayerInEvent(playerid))
		{
		    new
   				Float:armor;

			GetPlayerArmour(playerid, armor);

  			if(!(gettime() - AccountData[playerid][pLastUpdate] > 5))
  			{
				if(floatround(armor) > floatround(AccountData[playerid][pArmour]) && gettime() > AccountData[playerid][pACTime] && gettime() > AccountData[playerid][pArmorTime] && AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pFaction] != FACTION_POLISI)
				{
		            AccountData[playerid][pACWarns]++;
	    	        AccountData[playerid][pArmorTime] = gettime() + 10;

				    if(AccountData[playerid][pACWarns] < MAX_ANTICHEAT_WARNINGS)
				    {
						SendStaffMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" diduga menggunakan Armor Hack, [Old: %.2f New: %.2f]", AccountData[playerid][pName], playerid, AccountData[playerid][pArmour], armor);
					}
					else
					{
						SendClientMessageToAllEx(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Armour Hacks!", AccountData[playerid][pName], playerid);
                        KickEx(playerid);
					}
				}
			}

			AccountData[playerid][pArmour] = armor;
		}
	}
	// Ammo hacks
	if(!IsPlayerInEvent(playerid))
	{
	    new
			weapon,
			ammo;

		GetPlayerWeaponData(playerid, 8, weapon, ammo);

		if((16 <= weapon <= 18) && ammo <= 0)
		{
			RemovePlayerWeapon(playerid, weapon);
		}
	}

	// Warping into vehicles while locked
	/*if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && GetVehicleParams(GetPlayerVehicleID(playerid), VEHICLE_DOORS) && (!IsVehicleOwner(playerid, GetPlayerVehicleID(playerid)) && AccountData[playerid][pVehicleKeys] != GetPlayerVehicleID(playerid)))
    {
        new
            Float:x,
            Float:y,
            Float:z;
        GetPlayerPos(playerid, x, y, z);
        SetPlayerPos(playerid, x, y, z + 1.0);
        GameTextForPlayer(playerid, "~r~This vehicle is locked!", 3000, 3);
    }*/
}

RemovePlayerWeapon(playerid, weaponid)
{
	// Reset the player's weapons.
	ResetPlayerWeapons(playerid);
	// Set the armed slot to zero.
	SetPlayerArmedWeapon(playerid, 0);
	// Set the weapon in the slot to zero.
	AccountData[playerid][pACTime] = gettime() + 2;
	AccountData[playerid][pGuns][g_aWeaponSlots[weaponid]] = 0;
	// Set the player's weapons.
	SetWeapons(playerid);
}