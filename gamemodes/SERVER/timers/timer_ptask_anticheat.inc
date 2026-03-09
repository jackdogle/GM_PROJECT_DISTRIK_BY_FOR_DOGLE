#include <YSI\y_hooks>

ptask AntiCheat_Update[999](playerid)
{
    //Anti-Cheat Vehicle health hack
	if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1)
	{
		for(new v, j = GetVehiclePoolSize(); v <= j; v++) if(GetVehicleModel(v))
		{
			new Float:health;
			GetVehicleHealth(v, health);
			if( (health > VehicleHealthSecurityData[v]) && VehicleHealthSecurity[v] == false && v != ShowroomVeh[playerid])
			{
				if(GetPlayerVehicleID(playerid) == v)
				{
					new playerState = GetPlayerState(playerid);
					if(playerState == PLAYER_STATE_DRIVER)
					{
						SetValidVehicleHealth(v, VehicleHealthSecurityData[v]);
						SendClientMessageToAllEx(Y_YELLOW, "VeronaSecurity: %s telah di tendang dari server karena menggunakan Auto Repair Vehicle!", AccountData[playerid][pName]);
						KickEx(playerid);
					}
				}
			}
			if(VehicleHealthSecurity[v] == true)
			{
				VehicleHealthSecurity[v] = false;
			}
			VehicleHealthSecurityData[v] = health;
		}
	}
	//Anti-Money Hack
	if(GetPlayerMoney(playerid) > AccountData[playerid][pMoney])
	{
		ResetPlayerMoney(playerid);
		GivePlayerMoney(playerid, AccountData[playerid][pMoney]);
		//SendAdminMessage(COLOR_RED, "Possible money hacks detected on %s(%i). Check on this player. "LG_E"($%d).", AccountData[playerid][pName], playerid, GetPlayerMoney(playerid) - AccountData[playerid][pMoney]);
	}
	//Anti Armour Hacks
	new Float:A;
	GetPlayerArmour(playerid, A);
	if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pFaction] != FACTION_POLISI && !IsPlayerInEvent(playerid))
	{
		if(A > 105.0)
		{
			SetPlayerArmourEx(playerid, 0);
			SendClientMessageToAllEx(COLOR_RED, "[ANTICHEAT]: "GREY2_E"%s(%i) has been auto kicked for armour hacks!", AccountData[playerid][pName], playerid);
			KickEx(playerid);
		}
	}
	//Weapon AC
	if(AccountData[playerid][pAdmin] < 2 && GetPlayerFaction(playerid) != FACTION_POLISI)
	{
		if(AccountData[playerid][pSpawned] == 1 && !IsPlayerInEvent(playerid))
		{
			if(GetPlayerWeapon(playerid) != AccountData[playerid][pWeapon] || GetPlayerWeapon(playerid) != WeaponFaction[playerid])
			{
				AccountData[playerid][pWeapon] = GetPlayerWeapon(playerid);

				if(AccountData[playerid][pWeapon] >= 1 && AccountData[playerid][pWeapon] <= 45 && AccountData[playerid][pWeapon] != 40 && AccountData[playerid][pWeapon] != 2 && AccountData[playerid][pGuns][g_aWeaponSlots[AccountData[playerid][pWeapon]]] != GetPlayerWeapon(playerid))
				{
					AccountData[playerid][pACWarns]++;

					if(AccountData[playerid][pACWarns] < MAX_ANTICHEAT_WARNINGS)
					{
						SendAnticheat(COLOR_RED, "%s(%d) has possibly used weapon hacks (%s), Please to check /spec this player first!", AccountData[playerid][pName], playerid, ReturnWeaponName(AccountData[playerid][pWeapon]));
						SetWeapons(playerid); 				
					}
					else
					{
						new PlayerIP[16];
						SendClientMessageToAllEx(COLOR_RED, "[ANTICHEAT]: %s"WHITE_E" telah dibanned otomatis oleh %s, Alasan: Weapon hacks", AccountData[playerid][pName], SERVER_BOT);

						GetPlayerIp(playerid, PlayerIP, sizeof(PlayerIP));
						new query[300], tmp[40], ban_time = 0;
						format(tmp, sizeof (tmp), "Weapon Hack (%s)", ReturnWeaponName(AccountData[playerid][pWeapon]));
						mysql_format(g_SQL, query, sizeof(query), "INSERT INTO player_bans(name, ip, admin, reason, ban_date, ban_expire) VALUES ('%s', '%s', '%s', '%s', %i, %d)", AccountData[playerid][pUCP], PlayerIP, SERVER_BOT, tmp, gettime(), ban_time);
						mysql_tquery(g_SQL, query);
						KickEx(playerid);
					}
				}
			}
		}
	}
	//Weapon Atth
	if(NetStats_GetConnectedTime(playerid) - WeaponTick[playerid] >= 250)
	{
		static weaponid, ammo, objectslot, count, index;
 
		for (new i = 2; i <= 7; i++) //Loop only through the slots that may contain the wearable weapons
		{
			GetPlayerWeaponData(playerid, i, weaponid, ammo);
			index = weaponid - 22;
		   
			if (weaponid && ammo && !WeaponSettings[playerid][index][Hidden] && IsWeaponWearable(weaponid) && EditingWeapon[playerid] != weaponid)
			{
				objectslot = GetWeaponObjectSlot(weaponid);
 
				if (GetPlayerWeapon(playerid) != weaponid)
					SetPlayerAttachedObject(playerid, objectslot, GetWeaponModel(weaponid), WeaponSettings[playerid][index][Bone], WeaponSettings[playerid][index][Position][0], WeaponSettings[playerid][index][Position][1], WeaponSettings[playerid][index][Position][2], WeaponSettings[playerid][index][Position][3], WeaponSettings[playerid][index][Position][4], WeaponSettings[playerid][index][Position][5], 1.0, 1.0, 1.0);
 
				else if (IsPlayerAttachedObjectSlotUsed(playerid, objectslot)) RemovePlayerAttachedObject(playerid, objectslot);
			}
		}
		for (new i = 4; i <= 8; i++) if (IsPlayerAttachedObjectSlotUsed(playerid, i))
		{
			count = 0;
 
			for (new j = 22; j <= 38; j++) if (PlayerHasWeapon(playerid, j) && GetWeaponObjectSlot(j) == i)
				count++;
 
			if(!count) RemovePlayerAttachedObject(playerid, i);
		}
		WeaponTick[playerid] = NetStats_GetConnectedTime(playerid);
	}
    return 1;
}