ptask PlayerUpdate[1000](playerid)
{
	if (AccountData[playerid][IsLoggedIn] && AccountData[playerid][pSpawned])
	{
		if(AccountData[playerid][pSpec] != -1)
		{
			new
				targetid = AccountData[playerid][pSpec];
		
			PlayerTextDrawSetString(playerid, SpectatorInfoTD[playerid][1], sprintf("~g~%s_(%d)", ReturnName(targetid), targetid));
			PlayerTextDrawSetString(playerid, SpectatorInfoTD[playerid][2], sprintf("Cash:~y~_%s", FormatMoney(AccountData[targetid][pMoney])));
			PlayerTextDrawSetString(playerid, SpectatorInfoTD[playerid][3], sprintf("HP:~y~_%d.0", GetHealth(targetid)));
			PlayerTextDrawSetString(playerid, SpectatorInfoTD[playerid][4], sprintf("AM:~y~_%d.0", GetArmor(targetid)));
			PlayerTextDrawSetString(playerid, SpectatorInfoTD[playerid][5], sprintf("Int:~y~_%d_~w~WID:~y~_%d", GetPlayerInterior(targetid), GetPlayerVirtualWorld(targetid)));
			PlayerTextDrawSetString(playerid, SpectatorInfoTD[playerid][6], sprintf("Hungry:~y~_%d%%_~w~Thirst:~y~_%d%%", AccountData[targetid][pHunger] , AccountData[targetid][pThirst]));
			PlayerTextDrawSetString(playerid, SpectatorInfoTD[playerid][7], sprintf("FPS:~y~_%d_~w~Ping:~y~_%dms", GetPlayerFPS(targetid), GetPlayerPing(targetid)));
		}
		
		/* Anti Jetpack Hacks */
		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK && !AccountData[playerid][pJetpack])
		{
			SendClientMessageToAllEx(X11_ARWIN, "[AdmCmd] "YELLOW"%s(%d)"ARWIN1" telah ditendang dari server karena menggunakan Jetpack Hacks", ReturnName(playerid), playerid);
			KickEx(playerid);
		}
		if ((Anticheat_GetReportAmount(playerid, 6) > 0) && Anticheat_IsReportTimeExpired(playerid, 6))
        {
            Anticheat_ReduceReport(playerid, 6);
            Anticheat_IncreaseReportTime(playerid, 6);
        }
		/* FPS Info */
		if(AccountData[playerid][ToggleFPS])
		{
			PlayerTextDrawSetString(playerid, FPStextdraws[playerid][0], sprintf("~r~FPS:_~w~%d~n~~r~PL:_~w~%.2f", GetPlayerFPS(playerid), GetPlayerPacketLoss(playerid)));
			PlayerTextDrawShow(playerid, FPStextdraws[playerid][0]);
		}

		/* Weapon Attachment */
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
			for (new i = 6; i <= 8; i++) if (IsPlayerAttachedObjectSlotUsed(playerid, i))
			{
				count = 0;

				for (new j = 22; j <= 38; j++) if (PlayerHasWeapon(playerid, j) && GetWeaponObjectSlot(j) == i)
					count++;

				if(!count) RemovePlayerAttachedObject(playerid, i);
			}
			WeaponTick[playerid] = NetStats_GetConnectedTime(playerid);
		}

		/* Anti Money Hack */
		if(GetPlayerMoney(playerid) != AccountData[playerid][pMoney])
		{
			ResetPlayerMoney(playerid);
			GivePlayerMoney(playerid, AccountData[playerid][pMoney]);
		}
		//Jewelry Store
		if(isRobbing_Jewelry[playerid] == 1)
		{
			ApplyAnimation(playerid,"CAR_CHAT","CAR_Sc4_BL",4.0,1,1,1,0,0,0);
		}

		/* Pengurangan Data */
		if(AccountData[playerid][pJail] <= 0) // jika sedang tidak dipenjara admin
		{
			if(AccountData[playerid][pStress] > 100)
			{
				AccountData[playerid][pStress] = 100;
			}
			if(AccountData[playerid][pStress] < 0)
			{
				AccountData[playerid][pStress] = 0;
			}
			if(AccountData[playerid][pHunger] > 100)
			{
				AccountData[playerid][pHunger] = 100;
			}
			if(AccountData[playerid][pHunger] < 0)
			{
				AccountData[playerid][pHunger] = 0;
			}
			if(AccountData[playerid][pThirst] > 100)
			{
				AccountData[playerid][pThirst] = 100;
			}
			if(AccountData[playerid][pThirst] < 0)
			{
				AccountData[playerid][pThirst] = 0;
			}
		}
		new weaponid = GetPlayerWeaponEx(playerid);
		if (weaponid != 0)
		{
			if (weaponid >= 22 && weaponid <= 46)
			{
				if (AccountData[playerid][pLevel] < 9)
				{
					SendClientMessageEx(playerid, -1, ""RED"[Server] "WHITE"Anda telah di kick karena level di bawah 10!");
					ResetPlayerWeaponsEx(playerid);
					KickEx(playerid);
				}
			}
		}
		// new money = GetPlayerMoney(playerid);

		// if(AccountData[playerid][pLevel] >= 1 && AccountData[playerid][pLevel] < 15 && money > 100000)
		// {
		// 	ResetPlayerMoneyEx(playerid);
		// 	GiveMoney(playerid, 100000);
		// 	SendClientMessageEx(playerid, -1, ""RED"[Server] "WHITE"Anda tidak bisa memegang uang lebih dari "GREEN"100.000!");
		// }
		// else if(AccountData[playerid][pLevel] >= 15 && AccountData[playerid][pLevel] < 25 && money > 200000)
		// {
		// 	ResetPlayerMoneyEx(playerid);
		// 	GiveMoney(playerid, 200000);
		// 	SendClientMessageEx(playerid, -1, ""RED"[Server] "WHITE"Anda tidak bisa memegang uang lebih dari "GREEN"200.000!");
		// }
		// else if(AccountData[playerid][pLevel] >= 25 && AccountData[playerid][pLevel] < 35 && money > 300000)
		// {
		// 	ResetPlayerMoneyEx(playerid);
		// 	GiveMoney(playerid, 300000);
		// 	SendClientMessageEx(playerid, -1, ""RED"[Server] "WHITE"Anda tidak bisa memegang uang lebih dari "GREEN"300.000!");
		// }
		// else if(AccountData[playerid][pLevel] >= 35 && AccountData[playerid][pLevel] < 50 && money > 500000)
		// {
		// 	ResetPlayerMoneyEx(playerid);
		// 	GiveMoney(playerid, 500000);
		// 	SendClientMessageEx(playerid, -1, ""RED"[Server] "WHITE"Anda tidak bisa memegang uang lebih dari "GREEN"500.000!");
		// }
		// else if(AccountData[playerid][pLevel] >= 50 && AccountData[playerid][pLevel] <= 100 && money > 1000000)
		// {
		// 	ResetPlayerMoneyEx(playerid);
		// 	GiveMoney(playerid, 1000000);
		// 	SendClientMessageEx(playerid, -1, ""RED"[Server] "WHITE"Anda tidak bisa memegang uang lebih dari "GREEN"1.000.000!");
		// }
		/* Textdraw Death */
		if(AccountData[playerid][pInjured])
		{
			if(AccountData[playerid][pInjuredTime] > 0)
			{
				static hours, minutes, seconds;
				GetElapsedTime(AccountData[playerid][pInjuredTime] --, hours, minutes, seconds);
				new countems;
				foreach(new i : Player) if (IsPlayerConnected(i))
				{
					if(AccountData[i][pDutyEms]) countems++;
				}
				PlayerTextDrawSetString(playerid, InjuredAgusSamp[playerid][20], sprintf("%02d", minutes));
				PlayerTextDrawSetString(playerid, InjuredAgusSamp[playerid][7], sprintf("%d", countems));
				PlayerTextDrawSetString(playerid, InjuredAgusSamp[playerid][21], sprintf("%02d", seconds));
				ShowTDdeathHapp(playerid, true);
				
				ApplyAnimationEx(playerid, "WUZI", "CS_DEAD_GUY", 4.1, 0, 0, 0, 1, 0, 1);
				SetPlayerHealthEx(playerid, 99999);
			
				if(!AccountData[playerid][pInjuredTime]) 
				{
					SetPlayerHealthEx(playerid, 100.0);
					AccountData[playerid][pHunger] = 100;
					AccountData[playerid][pThirst] = 100;
					AccountData[playerid][pStress] = 0;
					AccountData[playerid][pInjured] = 0;
					AccountData[playerid][pInjuredTime] = 0;
					Inventory_Clear(playerid);
					ResetPlayerWeaponsEx(playerid);

					SendClientMessageEx(playerid, -1, "[i] Anda koma dan dilarikan kerumah sakit, semua barang dan uangmu hilang!");

					SetPlayerPositionEx(playerid, 907.8289, 711.1892, 5010.3184, 358.7794, 5000);
					SetPlayerVirtualWorldEx(playerid, 5);
					SetPlayerInteriorEx(playerid, 5);
				}
			}
		}

		/* Pengurangan Data 2 */
		if(AccountData[playerid][pInjured] == 0 && AccountData[playerid][pGender] != 0) 
		{
			ShowTDdeathHapp(playerid, false);

			if(AccountData[playerid][pStress] < 99)
			{
				TextDrawHideForPlayer(playerid, StressPurple[0]);
			}
			if(++ AccountData[playerid][pStressTime] >= 105 && GetPlayerVIPLevel(playerid) < 3)
			{
				if(AccountData[playerid][pInjured] != 1 && !IsPlayerInEvent(playerid))
				{
					if(!IsAUnstressArea(playerid))
					{
						AccountData[playerid][pStress]++;

						if(AccountData[playerid][pStress] >= 99)
						{
							TextDrawShowForPlayer(playerid, StressPurple[0]);
							SetPlayerDrunkLevel(playerid, 10000);
						}
					}
					else
					{
						AccountData[playerid][pStress] -= 20;

						if(AccountData[playerid][pStress] < 97)
						{
							SetPlayerDrunkLevel(playerid, 0);
							TextDrawHideForPlayer(playerid, StressPurple[0]);
						}
					}
				}
				AccountData[playerid][pStressTime] = 0;
			}
			if(++ AccountData[playerid][pHungerTime] >= 525)
			{
				if(AccountData[playerid][pHunger] > 0 && AccountData[playerid][pInjured] != 1 && !IsPlayerInEvent(playerid))
				{
					AccountData[playerid][pHunger] -= 5;
				}
				else if(AccountData[playerid][pHunger] <= 0 && AccountData[playerid][pInjured] != 1)
				{
					if(IsPlayerInAnyVehicle(playerid))
						RemovePlayerFromVehicle(playerid);
					SetPlayerHealth(playerid, 0.0);
				}
				AccountData[playerid][pHungerTime] = 0;
			}
			if(++ AccountData[playerid][pThirstTime] >= 900)
			{
				if(AccountData[playerid][pThirst] > 0 && AccountData[playerid][pInjured] != 1 && !IsPlayerInEvent(playerid))
				{
					AccountData[playerid][pThirst] -= 1;
				}
				else if(AccountData[playerid][pThirst] <= 0 && AccountData[playerid][pInjured] != 1)
				{
					new Float:p_hp;
					GetPlayerHealth(playerid, p_hp);
					SetPlayerHealth(playerid, p_hp - 3.0); 
					SendClientMessage(playerid, 0xFF0000FF, "Anda merasa sangat dehidrasi, segera cari minum!");

					if(IsPlayerInAnyVehicle(playerid) && p_hp < 10.0)
						RemovePlayerFromVehicle(playerid);
				}
				AccountData[playerid][pThirstTime] = 0;
			}
		}

		/* Admin Duty Timer */
		if(AccountData[playerid][pAdminDuty])
		{
			AccountData[playerid][aDutyTimer] ++;
		}

		/* Masker Label Update */
		if(AccountData[playerid][pMaskOn])
		{
			new Float:health, Float:armor;
			GetPlayerHealth(playerid, health);
			GetPlayerArmour(playerid, armor);
			if(IsValidDynamic3DTextLabel(AccountData[playerid][pMaskLabel]))
			{
				UpdateDynamic3DTextLabelText(AccountData[playerid][pMaskLabel], -1, sprintf("Mask #%d\nH: ["RED_E"%.2f"WHITE"] A: [%.2f]", AccountData[playerid][pMaskID], health, armor));
			}
		}

		/* Taser Update */
		if(AccountData[playerid][pStunned] > 0)
		{
			AccountData[playerid][pStunned]--;

			if(GetPlayerAnimationIndex(playerid) != 388)
				ApplyAnimation(playerid, "CRACK", "crckdeth4", 4.0, 0, 0, 0, 1, 0, 1);
			
			if(!AccountData[playerid][pStunned])
			{
				TogglePlayerControllable(playerid, 1);
				ShowPlayerFooter(playerid, "~w~Anda tidak lagi ~r~tersengat");
			}
		}

		switch(AccountData[playerid][pHUDMode])
		{
			case 1: // Kiri
			{
				if(HbeIndex[playerid])
				{
					new Float:healthvalue, Float:armorvalue, Float:thirstvalue, Float:energyvalue, Float:stressvalue;

					healthvalue = GetHealth(playerid) * -18.0/100;
					armorvalue = GetArmor(playerid) * -18.0/100;

					PlayerTextDrawTextSize(playerid, PUTRABOTAKHBE[playerid][5], 18.0, healthvalue);
					PlayerTextDrawShow(playerid, PUTRABOTAKHBE[playerid][5]);

					PlayerTextDrawTextSize(playerid, PUTRABOTAKHBE[playerid][6], 18.0, armorvalue);
					PlayerTextDrawShow(playerid, PUTRABOTAKHBE[playerid][6]);

					thirstvalue = AccountData[playerid][pHunger] * -18.0/100;
					PlayerTextDrawTextSize(playerid, PUTRABOTAKHBE[playerid][7], 18.0, thirstvalue);
					PlayerTextDrawShow(playerid, PUTRABOTAKHBE[playerid][7]);

					energyvalue = AccountData[playerid][pThirst] * -18.0/100;
					PlayerTextDrawTextSize(playerid, PUTRABOTAKHBE[playerid][8], 18.0, energyvalue);
					PlayerTextDrawShow(playerid, PUTRABOTAKHBE[playerid][8]);

					stressvalue = AccountData[playerid][pStress] * -18.0/100;
					PlayerTextDrawTextSize(playerid, PUTRABOTAKHBE[playerid][9], 18.0, stressvalue);
					PlayerTextDrawShow(playerid, PUTRABOTAKHBE[playerid][9]);

					new StrGuz[64];
					new fname[125], fid = AccountData[playerid][pFamily];
					if(fid != -1)
					{
						format(fname, sizeof(fname), FamData[fid][famName]);
					}
					else 
					{
						format(fname, sizeof(fname), "N/A");
					}
					format(StrGuz, sizeof(StrGuz), "%d/%d", OnlinePlayers, MAX_PLAYERS);
					PlayerTextDrawSetString(playerid, DistrictSTATIC[playerid][22], StrGuz);

					format(StrGuz, sizeof(StrGuz), "#%d", playerid);
					PlayerTextDrawSetString(playerid, DistrictSTATIC[playerid][23], StrGuz);

					format(StrGuz, sizeof(StrGuz), "%s Cash", FormatMoney(AccountData[playerid][pMoney]));
					PlayerTextDrawSetString(playerid, DistrictSTATIC[playerid][24], StrGuz);

					format(StrGuz, sizeof(StrGuz), "%s Bank", FormatMoney(AccountData[playerid][pBankMoney]));
					PlayerTextDrawSetString(playerid, DistrictSTATIC[playerid][25], StrGuz);

					format(StrGuz, sizeof(StrGuz), "%s - %s", GetFactName(playerid), GetPlayerJobName(playerid));
					PlayerTextDrawSetString(playerid, DistrictSTATIC[playerid][26], StrGuz);

					format(StrGuz, sizeof(StrGuz), "%s Family", fname);
					PlayerTextDrawSetString(playerid, DistrictSTATIC[playerid][27], StrGuz);
				}
			}
			case 2: // Tengah
			{
				/* Hunger Bar Update */ 
				new Chess7[258];
				new Hunger, Thirst, Stress;
				Hunger = AccountData[playerid][pHunger];
				Thirst = AccountData[playerid][pThirst];
				Stress = AccountData[playerid][pStress];

				format(Chess7, sizeof(Chess7), "%.0f", AccountData[playerid][pHealth]);
				PlayerTextDrawSetString(playerid, HbeStuffs[playerid][10], Chess7);

				format(Chess7, sizeof(Chess7), "%.0f", AccountData[playerid][pArmour]);
				PlayerTextDrawSetString(playerid, HbeStuffs[playerid][11], Chess7);

				format(Chess7, sizeof(Chess7), "%0d", Hunger);
				PlayerTextDrawSetString(playerid, HbeStuffs[playerid][12], Chess7);

				format(Chess7, sizeof(Chess7), "%0d", Thirst);
				PlayerTextDrawSetString(playerid, HbeStuffs[playerid][13], Chess7);

				format(Chess7, sizeof(Chess7), "%d", Stress);
				PlayerTextDrawSetString(playerid, HbeStuffs[playerid][14], Chess7);

				new StrGuz[64];
				new fname[125], fid = AccountData[playerid][pFamily];
				if(fid != -1)
				{
					format(fname, sizeof(fname), FamData[fid][famName]);
				}
				else 
				{
					format(fname, sizeof(fname), "N/A");
				}
				format(StrGuz, sizeof(StrGuz), "%d/%d", OnlinePlayers, MAX_PLAYERS);
				PlayerTextDrawSetString(playerid, DistrictSTATIC[playerid][22], StrGuz);

				format(StrGuz, sizeof(StrGuz), "#%d", playerid);
				PlayerTextDrawSetString(playerid, DistrictSTATIC[playerid][23], StrGuz);

				format(StrGuz, sizeof(StrGuz), "%s Cash", FormatMoney(AccountData[playerid][pMoney]));
				PlayerTextDrawSetString(playerid, DistrictSTATIC[playerid][24], StrGuz);

				format(StrGuz, sizeof(StrGuz), "%s Bank", FormatMoney(AccountData[playerid][pBankMoney]));
				PlayerTextDrawSetString(playerid, DistrictSTATIC[playerid][25], StrGuz);

				format(StrGuz, sizeof(StrGuz), "%s - %s", GetFactName(playerid), GetPlayerJobName(playerid));
				PlayerTextDrawSetString(playerid, DistrictSTATIC[playerid][26], StrGuz);

				format(StrGuz, sizeof(StrGuz), "%s Family", fname);
				PlayerTextDrawSetString(playerid, DistrictSTATIC[playerid][27], StrGuz);
			}
		}
		
		/* Good Mood Mode */
		if(AccountData[playerid][pGoodMood])
		{
			AccountData[playerid][pHunger] = 100;
			AccountData[playerid][pThirst] = 100;
			AccountData[playerid][pStress] = 0;
		}

		/* Enum Berat */
		if(AccountData[playerid][pBeratItem] <= 0)
		{
			AccountData[playerid][pBeratItem] = 0;
		}
		else if(AccountData[playerid][pBeratItem] > 50)
		{
			AccountData[playerid][pBeratItem] = 50;
		}

		/* Signal EMS */
		if(SignalExists[playerid] && SignalTimer[playerid] > 0)
		{
			SignalTimer[playerid] --;
			if(!SignalTimer[playerid])
			{
				SignalExists[playerid] = false;
				SignalTimer[playerid] = 0;
				SignalPos[playerid][0] = SignalPos[playerid][1] = SignalPos[playerid][2] = 0.0;
				Info(playerid, "Anda sudah dapat mengirim signal kepada EMS kembali!");
			}
		}

		/* Fixme */
		if(FixmeExists[playerid])
		{
			if(FixmeTime[playerid] != 0 && FixmeTime[playerid] <= gettime())
			{
				FixmeExists[playerid] = false;
				FixmeOption[playerid] = 0;
				FixmeTime[playerid] = 0;
				Info(playerid, "Tidak ada yang merespon fixme anda. Anda dapat mengajukannya kembali!");
			}
		}
	}
	return 1;
}

ptask OnlineTimerUpdate[1500](playerid)
{
	if(!AccountData[playerid][pSpawned])
		return 0;

	AccountData[playerid][OnlineTimer] ++;
	return 1;
}

ptask AlertNeeds_Player[180000](playerid)
{
	if(!AccountData[playerid][pSpawned])
		return 0;

	if(AccountData[playerid][pHunger] <= 20) {
		SendClientMessageEx(playerid, -1, ""VERONADOT"Karakter anda merasakan lapar // %d Persen", AccountData[playerid][pHunger]);
	}
	if(AccountData[playerid][pThirst] <= 20) {
		SendClientMessageEx(playerid, -1, ""VERONADOT"Karakter anda merasakan haus // %d Persen", AccountData[playerid][pThirst]);
	}
	if(AccountData[playerid][pStress] >= 90) {
		SendClientMessageEx(playerid, -1, ""VERONADOT"Karakter anda ingin mengalami stress // %d Persen", AccountData[playerid][pStress]);
	}
	return 1;
}

ptask ac_PlayerUpdate[1000](playerid)
{
	if(!AccountData[playerid][pSpawned] || !AccountData[playerid][IsLoggedIn]) 
		return 0;

	if (GetPlayerWeapon(playerid) != AccountData[playerid][pWeapon])
    {
        AccountData[playerid][pWeapon] = GetPlayerWeapon(playerid);

        if (AccountData[playerid][pWeapon] >= 1 && AccountData[playerid][pWeapon] <= 45 && AccountData[playerid][pWeapon] != 40 && AccountData[playerid][pGuns][g_aWeaponSlots[AccountData[playerid][pWeapon]]] != GetPlayerWeapon(playerid) && !DurringHunting[playerid] && !InPool[playerid] && !IsPlayerInEvent(playerid) && !PlayerTaserOn[playerid] && !AccountData[playerid][menuShowed])
        {
            printf("[debug] OnPlayerWeaponHack (UCP: %s Name: %s WeaponID: %d Ammo: %d)", AccountData[playerid][pUCP], ReturnPlayerName(playerid), GetPlayerWeapon(playerid), GetPlayerAmmo(playerid));

            SendAdminMessage(X11_RED, "[AntiCheat]: "YELLOW"%s(%d)"LIGHTGREY" terdeteksi menggunakan (Weapon Hacks: {FFFF00}%s"LIGHTGREY")", ReturnName(playerid), playerid, ReturnWeaponName(AccountData[playerid][pWeapon]));
            ResetWeapons(playerid);
            KickEx(playerid);
        }
        else if (AccountData[playerid][pWeapon] >= 1 && AccountData[playerid][pWeapon] <= 45 && AccountData[playerid][pWeapon] == 40 && AccountData[playerid][pGuns][g_aWeaponSlots[AccountData[playerid][pWeapon]]] != GetPlayerWeapon(playerid) && !DurringHunting[playerid] && !InPool[playerid] && !IsPlayerInEvent(playerid) && !PlayerTaserOn[playerid] && !AccountData[playerid][menuShowed])
        {
            printf("[debug] OnPlayerCrasher (UCP: %s Name: %s)", AccountData[playerid][pUCP], ReturnPlayerName(playerid));

            SendAdminMessage(X11_RED, "[AntiCheat]: "YELLOW"%s(%d)"LIGHTGREY" telah ditendang dari server karena terdeteksi menggunakan Crasher.luac", ReturnName(playerid), playerid);
            ResetWeapons(playerid);
            KickEx(playerid);
        }
    }
	// static Float:AM;
	// GetPlayerArmour(playerid, AM);
	// if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1 && AccountData[playerid][pFaction] != FACTION_POLISI && !IsPlayerInEvent(playerid))
	// {
	// 	if(AM >= 100)
	// 	{
	// 		SetPlayerArmourEx(playerid, 0);
	// 		SendClientMessageToAllEx(X11_RED, "[AntiCheat]: "YELLOW"[%s] %s (%d)"ARWIN1" terdeteksi menggunakan armour hack "YELLOW"New :[100.0]", AccountData[playerid][pUCP], ReturnName(playerid), playerid);
	// 		KickEx(playerid);
	// 	}
	// }
	new Float:H;
	GetPlayerHealth(playerid, H);
	if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1 && !AccountData[playerid][pInjured] && !IsPlayerInEvent(playerid))
	{
		if(H > 105.0)
		{
			SetPlayerHealthEx(playerid, 100.0);
			SendClientMessage(playerid, -1, "[i] Sistem kami berhasil mengembalikan darah anda tidak lebih dari "YELLOW"100%%");
		}
	}
	return 1;
}

ptask PlayerDragging_Update[1000](playerid)
{
    if (!AccountData[playerid][pSpawned])
        return 0;

    new targetid = IsDragging[playerid];
    if (targetid != INVALID_PLAYER_ID)
    {
        // Mengambil informasi yang sering digunakan
        new playerInterior = GetPlayerInterior(playerid);
        new playerVirtualWorld = GetPlayerVirtualWorld(playerid);

        // Menyalin data bisnis, rumah, dan pintu
        AccountData[targetid][pInBiz] = AccountData[playerid][pInBiz];
        AccountData[targetid][pInHouse] = AccountData[playerid][pInHouse];
        AccountData[targetid][pInDoor] = AccountData[playerid][pInDoor];

        // Mengambil posisi dan sudut pemain
        new Float:X, Float:Y, Float:Z, Float:Ang;
        GetPlayerPos(playerid, X, Y, Z);
        GetPlayerFacingAngle(playerid, Ang);

        // Memindahkan target berdasarkan posisi pemain
        X += (0.75 * -floatsin(-Ang, degrees));
        Y += (0.75 * -floatcos(-Ang, degrees));
        SetPlayerPos(targetid, X, Y, Z);

        // Menyesuaikan interior dan virtual world hanya jika berbeda
        if (GetPlayerInterior(targetid) != playerInterior)
        {
            SetPlayerInterior(targetid, playerInterior);
        }

        if (GetPlayerVirtualWorld(targetid) != playerVirtualWorld)
        {
            SetPlayerVirtualWorld(targetid, playerVirtualWorld);
        }
    }

    return 1;
}


stock PlayerCompassUpdate(playerid, vehid)
{
	static Float:X, Float:Y, Float:Z, Float:Ang;
	GetPlayerPos(playerid, X, Y, Z);

	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		GetVehicleZAngle(vehid, Ang);
	}
	else
	{
		GetPlayerFacingAngle(playerid, Ang);
	}

	static frmtcompass[258];
	if (Ang >= 348.75 || Ang < 11.25) frmtcompass = "Utara";
	else if (Ang >= 258.75 && Ang < 281.25) frmtcompass = "Timur";
	else if (Ang >= 303.75 && Ang < 326.25) frmtcompass = "Timur Laut";
	else if (Ang >= 168.75 && Ang < 191.25) frmtcompass = "Selatan";
	else if (Ang >= 213.75 && Ang < 236.25) frmtcompass = "Tenggara";
	else if (Ang >= 78.75 && Ang < 101.25) frmtcompass = "Barat";
	else if (Ang >= 33.75 && Ang < 56.25) frmtcompass = "Barat Laut";
	else if (Ang >= 123.25 && Ang < 146.25) frmtcompass = "Barat Daya";
	PlayerTextDrawSetString(playerid, Speedo_Location[playerid], sprintf("%s_I_%s", frmtcompass, GetLocation(X, Y, Z)));
	return 1;
}

ptask PlayerVehUpdate[1000](playerid)
{
	if(!AccountData[playerid][pSpawned])
		return 0;

    new vehid = GetPlayerVehicleID(playerid);
	if(IsValidVehicle(vehid))
	{
		if(!GetEngineStatus(vehid) && IsEngineVehicle(vehid) && !IsABike(vehid))
		{
			SwitchVehicleEngine(vehid, false);
		}
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new Float:vHealth;
			GetVehicleHealth(vehid, vHealth);
			if(IsValidVehicle(vehid) && vHealth <= 350.0)
			{
				SwitchVehicleEngine(vehid, false);
				ShowPlayerFooter(playerid, "~w~Engine~r~ Totalled", 2000);
			}
		}
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{

			if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			{
				HideSpedo(playerid);
			}
			new vehicleid = GetPlayerVehicleID(playerid);
			new model = GetVehicleModel(vehicleid);
			new Float: FUELVEHBAR = VehicleCore[vehicleid][vCoreFuel];
			new Float:health;
			GetVehicleHealth(vehicleid, health);
			if(model)
			{
				new str[256], bensin[256];
				PlayerTextDrawSetString(playerid, SpeedoSimpel[playerid][3], sprintf("%.0f", GetVehicleSpeed(vehid)));
				format(str, sizeof(str), "%.0f", health);
				PlayerTextDrawSetString(playerid, SpeedoSimpel[playerid][7], str);
				format(bensin, sizeof(bensin), "%.0f", FUELVEHBAR);
			    PlayerTextDrawSetString(playerid, SpeedoSimpel[playerid][4], bensin);
				
			}
		}
	}
	return 1;
}

ptask UpTime[60000]()
{
	static h,m,s,lasth;
    gettime(h,m,s);
	if(lasth != h)
	{
		SetWorldTime(h);
		lasth = h;
	}
}