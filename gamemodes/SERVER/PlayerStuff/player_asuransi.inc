#include <YSI\y_hooks>

hook OnGameModeInit()
{
	CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Asuransi Kendaraan", -1, 424.42, -1318.80, 14.99 + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);// LS
	CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE"- Asuransi Kendaraan", -1, 51.3536, 1222.1011, 18.9170 + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);// LV

	CreateDynamicPickup(1080, 23, 405.2360, -1314.1396, 14.5725 + 0.2, 0, 0, -1, 15.0);
	CreateDynamic3DTextLabel(""RED"[Peringatan]\n"WHITE"Dilarang parkir di area ini, ini adalah area spawn asuransi", -1, 405.2360, -1314.1396, 14.5725 + 0.8, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);

	CreateDynamicPickup(1080, 23, 38.8462, 1226.8042, 18.8938 + 0.2, 0, 0, -1, 15.0);
	CreateDynamic3DTextLabel(""RED"[Peringatan]\n"WHITE"Dilarang parkir di area ini, ini adalah area spawn asuransi", -1, 38.8462, 1226.8042, 18.8938 + 0.8, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(IsPlayerInRangeOfPoint(playerid, 1.5, 424.42, -1318.80, 14.99))
		{
			if(!CountPlayerVehicleInsuranced(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki kendaraan yang sedang di asuransi!");
			
			new id, count = CountPlayerVehicleInsuranced(playerid), lstr[596];
			format(lstr, sizeof(lstr), "No\tModel Kendaraan\tNomor Plat\tBiaya Pelepasan\n");
			for(new itt; itt < count; itt++)
			{
				id = ReturnVehicleIDInsuranced(playerid, itt);
				if(itt == count)
				{
					format(lstr, sizeof(lstr), "%s%d\t%s\t%s\t$700", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
				}
				else format(lstr, sizeof(lstr), "%s%d\t%s\t%s\t$700\n", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
			}
			ShowPlayerDialog(playerid, DIALOG_ASURANSI_LS, DIALOG_STYLE_TABLIST_HEADERS, "Asuransi - Ambil Kendaraan", lstr, "Pilih", "Batal");
		}
		if(IsPlayerInRangeOfPoint(playerid, 1.5, 51.3536, 1222.1011, 18.9170))
		{
			if(!CountPlayerVehicleInsuranced(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki kendaraan yang sedang di asuransi!");
			
			new id, count = CountPlayerVehicleInsuranced(playerid), lstr[596];
			format(lstr, sizeof(lstr), "No\tModel Kendaraan\tNomor Plat\tBiaya Pelepasan\n");
			for(new itt; itt < count; itt++)
			{
				id = ReturnVehicleIDInsuranced(playerid, itt);
				if(itt == count)
				{
					format(lstr, sizeof(lstr), "%s%d\t%s\t%s\t$700", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
				}
				else format(lstr, sizeof(lstr), "%s%d\t%s\t%s\t$700\n", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
			}
			ShowPlayerDialog(playerid, DIALOG_ASURANSI_LV, DIALOG_STYLE_TABLIST_HEADERS, "Asuransi - Ambil Kendaraan", lstr, "Pilih", "Batal");
		}
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == DIALOG_ASURANSI_LS)
	{
		if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
		if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
		if(AccountData[playerid][pMoney] < 700) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
		
		new iter = ReturnVehicleIDInsuranced(playerid, listitem);
		if(iter == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan yang ingin ditebus!");

		if(!IsPlayerInRangeOfPoint(playerid, 2.5, 424.42, -1318.80, 14.99)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak di titik asuransi!");
		if(PlayerVehicle[iter][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
		TakeMoney(playerid, 700);

		PlayerVehicle[iter][pVehInsuranced] = false;
		PlayerVehicle[iter][pVehParked] = -1;
		PlayerVehicle[iter][pVehHouseGarage] = -1;
		PlayerVehicle[iter][pVehHelipadGarage] = -1;
		PlayerVehicle[iter][pVehFamiliesGarage] = -1;
		PlayerVehicle[iter][pVehFactStored] = -1;

		// PlayerVehicle[iter][pVehDamage][0] = 0;
		// PlayerVehicle[iter][pVehDamage][1] = 0;
		// PlayerVehicle[iter][pVehDamage][2] = 0;
		// PlayerVehicle[iter][pVehDamage][3] = 0;

		PlayerVehicle[iter][pVehPos][0] = 405.2360;
		PlayerVehicle[iter][pVehPos][1] = -1314.1396;
		PlayerVehicle[iter][pVehPos][2] = 14.5725;
		PlayerVehicle[iter][pVehPos][3] = 213.2121;

		PlayerVehicle[iter][pVehFuel] = MAX_FUEL_FULL;
		PlayerVehicle[iter][pVehHealth] = 800.0;
		PlayerVehicle[iter][pVehInterior] = GetPlayerInterior(playerid);
		PlayerVehicle[iter][pVehWorld] = GetPlayerVirtualWorld(playerid);

		if(PlayerVehicle[iter][pVehLocked]) {
			PlayerVehicle[iter][pVehLocked] = false;
		}

		OnPlayerVehicleRespawn(iter);
		ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil mengambil kendaraan %s seharga $700", GetVehicleName(PlayerVehicle[iter][pVehPhysic])));

		SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[iter][pVehPhysic], 0);
	}
	else if(dialogid == DIALOG_ASURANSI_LV)
	{
		if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
		if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
		if(AccountData[playerid][pMoney] < 700) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
		
		new iter = ReturnVehicleIDInsuranced(playerid, listitem);
		if(iter == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan yang ingin ditebus!");

		if(!IsPlayerInRangeOfPoint(playerid, 2.5, 51.3536, 1222.1011, 18.9170)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak di titik asuransi!");
		if(PlayerVehicle[iter][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
		TakeMoney(playerid, 700);

		PlayerVehicle[iter][pVehInsuranced] = false;
		PlayerVehicle[iter][pVehParked] = -1;
		PlayerVehicle[iter][pVehHouseGarage] = -1;
		PlayerVehicle[iter][pVehHelipadGarage] = -1;
		PlayerVehicle[iter][pVehFamiliesGarage] = -1;
		PlayerVehicle[iter][pVehFactStored] = -1;

		// PlayerVehicle[iter][pVehDamage][0] = 0;
		// PlayerVehicle[iter][pVehDamage][1] = 0;
		// PlayerVehicle[iter][pVehDamage][2] = 0;
		// PlayerVehicle[iter][pVehDamage][3] = 0;

		PlayerVehicle[iter][pVehPos][0] = 38.8462;
		PlayerVehicle[iter][pVehPos][1] = 1226.8042;
		PlayerVehicle[iter][pVehPos][2] = 18.8938;
		PlayerVehicle[iter][pVehPos][3] = 183.2933;

		PlayerVehicle[iter][pVehFuel] = MAX_FUEL_FULL;
		PlayerVehicle[iter][pVehHealth] = 800.0;
		PlayerVehicle[iter][pVehInterior] = GetPlayerInterior(playerid);
		PlayerVehicle[iter][pVehWorld] = GetPlayerVirtualWorld(playerid);

		if(PlayerVehicle[iter][pVehLocked]) {
			PlayerVehicle[iter][pVehLocked] = false;
		}

		OnPlayerVehicleRespawn(iter);
		ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil mengambil kendaraan %s seharga $700", GetVehicleName(PlayerVehicle[iter][pVehPhysic])));

		SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[iter][pVehPhysic], 0);
	}
	return 1;
}