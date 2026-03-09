#include <YSI\y_hooks>
new Text: GarasiTD[73];
new SelectGarasi[MAX_PLAYERS] = -1;


CMD:avcolor(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 4) 
		return PermissionError(playerid);
	
	new color1, color2, vehicleid = GetPlayerVehicleID(playerid), vehicle_index = RETURN_INVALID_VEHICLE_ID;
	if(sscanf(params, "dd", color1, color2)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/avcolor [pVehcolor1] [pVehcolor2]");
	if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengendarai kendaraan!");
	if(VehicleCore[vehicleid][vehAdmin] || SidejobVehicles(vehicleid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini static!");

	if((vehicle_index = Vehicle_ReturnID(vehicleid)) != RETURN_INVALID_VEHICLE_ID)
	{
		ChangeVehicleColor(vehicleid, color1, color2);

		PlayerVehicle[vehicle_index][pVehColor1] = color1;
		PlayerVehicle[vehicle_index][pVehColor2] = color2;
		SavePlayerVehicle(PlayerVehicle[vehicle_index][pVehPhysic]);
	}
	return 1;
}

CMD:trunkfix(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 3)
		return PermissionError(playerid);
	
	new vehid;
	if(sscanf(params, "d", vehid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/trunkfix [vehicle id]");
	if(!IsValidVehicle(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tidak valid/spawn!");
	foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists])
	{
		if(PlayerVehicle[i][pVehPhysic] == vehid)
		{
			if(PlayerVehicle[i][pVehCapacity] <= 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak bug, hanya 30kg keatas yang dapat di reset!");

			PlayerVehicle[i][pVehCapacity] = 0;
			SavePlayerVehicle(i);
		}
	}

	ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mereset kapasitas bagasi kendaraan tersebut!");
	return 1;
}

CMD:aseat(playerid, params[])
{
	new otherid;
	if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/aseat [driver id]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerInVehicle(otherid, GetPlayerVehicleID(playerid))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus berada di kendaraan yang sama!");
	if(GetVehicleDriver(GetPlayerVehicleID(playerid)) != otherid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut bukan driver!");
	if(!IsPlayerInVehicle(otherid, GetPlayerVehicleID(playerid))) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus berada di kendaraan yang sama!");
	if(otherid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat melakukan ini kepada diri sendiri!");

	ChangeSeatWithPlayerID[otherid] = playerid;
	ChangeSeatVehicleID[otherid] = GetPlayerVehicleID(otherid);
	ChangeSeatVehicleID[playerid] = GetPlayerVehicleID(playerid);
	SendClientMessageEx(otherid, -1, ""SKYBLUE"SWITCH SEAT:"YELLOW" %s(%d)"WHITE" Meminta untuk bertukar kemudi. Gunakan "YELLOW"'/accept seat'"WHITE" untuk menerima", ReturnName(playerid), playerid);
	ShowTDN(playerid, NOTIFICATION_INFO, "Berhasil meminta untuk bertukar posisi kemudi. Tunggu pemain tersebut menerima!");
	return 1;
}

alias:takeoutveh("tov")
CMD:takeoutveh(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1) return PermissionError(playerid);
	
	new vehid, Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	if(sscanf(params, "d", vehid))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/takeoutveh [VID Database]");

	foreach(new iterid : PvtVehicles)
	{
		if(vehid == PlayerVehicle[iterid][pVehID])
		{
			if(!IsValidVehicle(PlayerVehicle[iterid][pVehPhysic]))
			{
				if(PlayerVehicle[iterid][pVehInsuranced]){
					PlayerVehicle[iterid][pVehInsuranced] = false;
				}

				if(PlayerVehicle[iterid][pVehImpounded]){
					PlayerVehicle[iterid][pVehImpounded] = false;
					PlayerVehicle[iterid][pVehImpoundDuration] = 0;
					PlayerVehicle[iterid][pVehImpoundFee] = 0;
					format(PlayerVehicle[iterid][pVehImpoundReason], 64, "N/A");
				}

				if(PlayerVehicle[iterid][pVehParked] >= 0){
					PlayerVehicle[iterid][pVehParked] = -1;
				}

				if(PlayerVehicle[iterid][pVehFamiliesGarage] >= 0) {
					PlayerVehicle[iterid][pVehFamiliesGarage] = -1;
				}

				if(PlayerVehicle[iterid][pVehHouseGarage] >= 0) {
					PlayerVehicle[iterid][pVehHouseGarage] = -1;
				}

				if(PlayerVehicle[iterid][pVehHelipadGarage] >= 0) {
					PlayerVehicle[iterid][pVehHelipadGarage] = -1;
				}

				if(PlayerVehicle[iterid][pVehFactStored] >= 0) {
					PlayerVehicle[iterid][pVehFactStored] = -1;
				}

				PlayerVehicle[iterid][pVehWorld] = GetPlayerVirtualWorld(playerid);
				PlayerVehicle[iterid][pVehInterior] = GetPlayerInterior(playerid);
				
				PlayerVehicle[iterid][pVehPos][0] = x;
				PlayerVehicle[iterid][pVehPos][1] = y;
				PlayerVehicle[iterid][pVehPos][2] = z;

				OnPlayerVehicleRespawn(iterid);
				SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menggunakan Forced Veh pada kendaraan Database ID: "YELLOW"%d", GetAdminName(playerid), vehid);
			}
			else return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut masih spawn!");
		}
	}
	return 1;
}

CMD:agiveplate(playerid, params[])
{
	new vehid = -1;
	if(sscanf(params, "d", vehid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/agiveplate [VID]");
	if(SidejobVehicles(vehid) || VehicleCore[vehid][vehAdmin]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini sidejob/static!");
	if((vehid = Vehicle_Nearest(playerid, 3.0)) != -1)
	{
		if(PlayerVehicle[vehid][pVehRental] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut milik rental!");
		if(!IsValidVehicle(PlayerVehicle[vehid][pVehPhysic])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak valid!");
		if(PlayerVehicle[vehid][pVehPlateOwn]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut sudah memiliki Nomor Plat!");

		new 
			xd1 = random(sizeof(g_Alphabet)),
			xd2 = random(sizeof(g_Alphabet)),
			xd3 = random(sizeof(g_Alphabet));
		
		PlayerVehicle[vehid][pVehPlateOwn] = 1;

		format(PlayerVehicle[vehid][pVehPlate], 64, "AE %d%d%d%d %s%s%s", random(10), random(10), random(10), random(10), g_Alphabet[xd1], g_Alphabet[xd2], g_Alphabet[xd3]);
		SetVehicleNumberPlate(PlayerVehicle[vehid][pVehPhysic], PlayerVehicle[vehid][pVehPlate]);
		SavePlayerVehicle(vehid);
		ShowTDN(playerid, NOTIFICATION_SUKSES, "Plate berhasil terpasang ke kendaraan tersebut!");
	}
	else ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan apapun di sekitar!");
	return 1;
}

alias:setvehdonation("svd")
CMD:setvehdonation(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 7) return PermissionError(playerid);

	new vehid;
	if(sscanf(params, "i", vehid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setvehdonation [pVehID]");
	if(VehicleCore[vehid][vehAdmin] || vehid == INVALID_VEHICLE_ID || SidejobVehicles(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "VID Kendaraan tidak valid!");
	foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehPhysic] == vehid)
	{
		if(!PlayerVehicle[i][vehDonation])
		{
			PlayerVehicle[i][vehDonation] = 1;
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengubah status kendaraan menjadi Donasi!");
		}
	}
	return 1;
}

CMD:setfuel(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 3) return PermissionError(playerid);

	new vehid, fuel;
	if(sscanf(params, "id", vehid, fuel)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setfuel [VID] [amount]");
	if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Kendaraan tidak valid!");

	VehicleCore[vehid][vCoreFuel] = fuel;
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menetapkan Fuel kendaraan VID: "YELLOW"%d"ARWIN1" menjadi %d Liter", GetAdminName(playerid), vehid, fuel);
	return 1;
}

CMD:vinvis(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 3) return PermissionError(playerid);
	
	Info(playerid, "Admin Vehicle Invisible for you is now '%s'", (GetPVarInt(playerid, "vehCollision") != 1) ? ("Disabled") : ("Enabled"));
	SetPVarInt(playerid, "vehCollision", !GetPVarInt(playerid, "vehCollision"));
	DisableRemoteVehicleCollisions(playerid, GetPVarInt(playerid, "vehCollision"));
	return 1;
}

CMD:sellveh(playerid, params[]) 
{
	new otherid, vid, price;
	if(sscanf(params, "udd", otherid, vid, price)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/sellveh [name/playerid] [VID] [harga]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, otherid, 2.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus dekat dengan anda!");
	if(!GetNearestVehicle(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus dekat dengan kendaraan yang ingin dijual!");
	if(price < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal kurang dari $1");

	foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists])
	{
		if(PlayerVehicle[i][pVehPhysic] == vid)
		{
			if(PlayerVehicle[i][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan milik anda!");
			if(PlayerVehicle[i][pVehFaction] > FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan faction tidak dapat dijual!");
			if(PlayerVehicle[i][pVehRental] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat dijual!");
			if(!PlayerVehicle[i][pVehPlateOwn] && !IsABicycle(PlayerVehicle[i][pVehPhysic])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut belum memiliki Nomor Plat!");

			AccountData[otherid][pCarSeller] = playerid;
			AccountData[otherid][pCarOffered] = vid;
			AccountData[otherid][pCarValue] = price;
			format(AccountData[otherid][pTempText], 256, "%s", PlayerVehicle[i][pVehPlate]);
			SetPVarString(otherid, "CarName", GetVehicleName(PlayerVehicle[i][pVehPhysic]));

			Dialog_Show(playerid, SellVehMenu, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Metode Pembayaran", "Cash\nSaldo Rekening", "Pilih", "Batal");
			SetPVarInt(playerid, "CarBuyer", otherid);
		}
	}
	return 1;
}

Dialog:SellVehMenu(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new otherid = GetPVarInt(playerid, "CarBuyer"), string[128];
		GetPVarString(otherid, "CarName", string, sizeof(string));
		
		if(otherid == INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
		if(!IsPlayerNearPlayer(playerid, otherid, 5.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak di dekat anda!");
		switch(listitem)
		{
			case 0: // Cash
			{
				Dialog_Show(otherid, BuyvehCashMenu, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Beli Kendaraan",
				""WHITE"%s menawarkan anda {FFFF00}%s{FFFFFF} seharga {00FF00}%s\
				\n"WHITE"Metode Pembayaran: "YELLOW"Cash\
				\n"WHITE"Tekan "GREEN"Iya"WHITE" untuk membeli kendaraannya\
				\nTekan "RED"Tidak"WHITE" untuk membatalkan pembelian kendaraannya.\
				\n\nNOTE: Uang akan terpotong otomatis jika anda menerima pembelian kendaraan", "Iya", "Tidak", AccountData[playerid][pName], string, FormatMoney(AccountData[otherid][pCarValue]));
			}
			case 1: // Bank
			{
				Dialog_Show(otherid, BuyvehRekeningMenu, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Beli Kendaraan",
				""WHITE"%s menawarkan anda {FFFF00}%s{FFFFFF} seharga {00FF00}%s\
				\n"WHITE"Metode Pembayaran: "YELLOW"Saldo Rekening\
				\n"WHITE"Tekan "GREEN"Iya"WHITE" untuk membeli kendaraannya\
				\nTekan "RED"Tidak"WHITE" untuk membatalkan pembelian kendaraannya.\
				\n\nNOTE: Saldo Rekening akan terpotong otomatis jika anda menerima pembelian kendaraan", "Iya", "Tidak", AccountData[playerid][pName], string, FormatMoney(AccountData[otherid][pCarValue]));
			}
		}
	}
	else
	{
		foreach(new i : Player) if (IsPlayerConnected(i)) 
		{
			if(AccountData[i][pCarSeller] == playerid)
			{
				AccountData[i][pCarSeller] = INVALID_PLAYER_ID;
				AccountData[i][pCarOffered] = -1;
				AccountData[i][pCarValue] = 0;
				AccountData[i][pTempText] = EOS;
				DeletePVar(i, "CarName");
			}
		}
		DeletePVar(playerid, "CarBuyer");
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
	}
	return 1;
}

Dialog:BuyvehCashMenu(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(AccountData[playerid][pCarSeller] == INVALID_PLAYER_ID)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada tawaran kendaraan untukmu!");
		
		new 
			seller = AccountData[playerid][pCarSeller],
			vehicleid = AccountData[playerid][pCarOffered],
			price = AccountData[playerid][pCarValue];
		
		if(!IsPlayerNearPlayer(playerid, seller, 3.0))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada didekat Seller!");
		
		new count = 0;
		foreach(new carid : PvtVehicles)
		{
			if(PlayerVehicle[carid][pVehExists] && PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
				count ++;
		}
		if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");
		if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
		
		new vehicle_index;
		if((vehicle_index = Vehicle_ReturnID(vehicleid)) != RETURN_INVALID_VEHICLE_ID)
		{
			PlayerVehicle[vehicle_index][pVehOwnerID] = AccountData[playerid][pID];
			TakeMoney(playerid, price);
			GiveMoney(seller, price);
			SendClientMessageToAllEx(X11_CORNFLOWERBLUE, "[i] %s Milik %s terjual kepada %s seharga %s", AccountData[playerid][pTempText], GetRPName(seller), GetRPName(playerid), FormatMoney(price));

			new cQuery[598];
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_vehicles` SET `PVeh_OwnerID`=%d WHERE `id`=%d", PlayerVehicle[vehicle_index][pVehOwnerID], PlayerVehicle[vehicle_index][pVehID]);
			mysql_tquery(g_SQL, cQuery);

			static shstr[255];
			format(shstr, sizeof(shstr), "Membeli %s milik %s seharga %s", GetVehicleName(PlayerVehicle[vehicle_index][pVehPhysic]), AccountData[AccountData[playerid][pCarSeller]][pName], FormatMoney(AccountData[playerid][pCarValue]));
			AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, AccountData[playerid][pCarValue]);

			AccountData[playerid][pCarSeller] = INVALID_PLAYER_ID;
			AccountData[playerid][pCarOffered] = -1;
			AccountData[playerid][pCarValue] = 0;
			DeletePVar(playerid, "CarName");
		}
	}
	else
	{
		DeletePVar(AccountData[playerid][pCarSeller], "CarBuyer");

		AccountData[playerid][pCarSeller] = INVALID_PLAYER_ID;
		AccountData[playerid][pCarOffered] = -1;
		AccountData[playerid][pCarValue] = 0;
		AccountData[playerid][pTempText] = EOS;
		DeletePVar(playerid, "CarName");
		ShowTDN(playerid, NOTIFICATION_WARNING, "Anda menolak membeli kendaraan");
	}
	return 1;
}

Dialog:BuyvehRekeningMenu(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(AccountData[playerid][pCarSeller] == INVALID_PLAYER_ID)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada tawaran kendaraan untukmu!");
		
		new 
			seller = AccountData[playerid][pCarSeller],
			vehicleid = AccountData[playerid][pCarOffered],
			price = AccountData[playerid][pCarValue];
		
		if(!IsPlayerNearPlayer(playerid, seller, 3.0))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada didekat Seller!");
		
		new count = 0;
		foreach(new carid : PvtVehicles)
		{
			if(PlayerVehicle[carid][pVehExists] && PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
				count ++;
		}
		if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");
		if(AccountData[playerid][pBankMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo Rekening anda tidak cukup!");
		
		new vehicle_index;
		if((vehicle_index = Vehicle_ReturnID(vehicleid)) != RETURN_INVALID_VEHICLE_ID)
		{
			PlayerVehicle[vehicle_index][pVehOwnerID] = AccountData[playerid][pID];
			AccountData[playerid][pBankMoney] -= price;
			AccountData[seller][pBankMoney] += price;
			// TakeMoney(playerid, price);
			// GiveMoney(seller, price);
			SendClientMessageToAllEx(X11_CORNFLOWERBLUE, "[i] %s Milik %s terjual kepada %s seharga %s", AccountData[playerid][pTempText], GetRPName(seller), GetRPName(playerid), FormatMoney(price));

			new cQuery[598];
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_vehicles` SET `PVeh_OwnerID`=%d WHERE `id`=%d", PlayerVehicle[vehicle_index][pVehOwnerID], PlayerVehicle[vehicle_index][pVehID]);
			mysql_tquery(g_SQL, cQuery);

			static shstr[255];
			format(shstr, sizeof(shstr), "Membeli %s milik %s seharga %s", GetVehicleName(PlayerVehicle[vehicle_index][pVehPhysic]), AccountData[AccountData[playerid][pCarSeller]][pName], FormatMoney(AccountData[playerid][pCarValue]));
			AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, AccountData[playerid][pCarValue]);

			AccountData[playerid][pCarSeller] = INVALID_PLAYER_ID;
			AccountData[playerid][pCarOffered] = -1;
			AccountData[playerid][pCarValue] = 0;
			DeletePVar(playerid, "CarName");
		}
	}
	else
	{
		DeletePVar(AccountData[playerid][pCarSeller], "CarBuyer");

		AccountData[playerid][pCarSeller] = INVALID_PLAYER_ID;
		AccountData[playerid][pCarOffered] = -1;
		AccountData[playerid][pCarValue] = 0;
		AccountData[playerid][pTempText] = EOS;
		DeletePVar(playerid, "CarName");
		ShowTDN(playerid, NOTIFICATION_WARNING, "Anda menolak membeli kendaraan");
	}
	return 1;
}

/*CMD:sellveh(playerid, params[]) 
{
	new otherid, vid, price;
	if(sscanf(params, "udd", otherid, vid, price)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/sellveh [name/playerid] [VID] [harga]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, otherid, 2.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus dekat dengan anda!");
	if(!GetNearestVehicle(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus dekat dengan kendaraan yang ingin dijual!");
	if(price < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal kurang dari $1");

	foreach(new iterid : PvtVehicles) 
	{
		if(vid == PlayerVehicle[iterid][pVehPhysic]) 
		{
			if(PlayerVehicle[iterid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan milik anda!");
			if(PlayerVehicle[iterid][pVehFaction] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan faction tidak dapat dijual!");
			if(PlayerVehicle[iterid][pVehRental] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat dijual!");
			if(!PlayerVehicle[iterid][pVehPlateOwn] && !IsABicycle(PlayerVehicle[iterid][pVehPhysic])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut belum memiliki plate!");

			AccountData[otherid][pCarSeller] = playerid;
			AccountData[otherid][pCarOffered] = vid;
			AccountData[otherid][pCarValue] = price;
			format(AccountData[otherid][pTempText], 256, "%s", PlayerVehicle[iterid][pVehPlate]);
			
			SendClientMessageEx(otherid, -1, "[i] Seseorang %s menawarkan anda {FFFF00}%s{FFFFFF} seharga {00FF00}%s{FFFF00} '/accept buyveh'{FFFFFF} untuk menerima", ReturnName(playerid), GetVehicleName(vid), FormatMoney(price));
			SendClientMessageEx(playerid, -1, "[i] Anda menawarkan {FFFF00}%s{FFFFFF} dengan harga {00FF00}%s{FFFFFF} kepada %s", GetVehicleName(vid), FormatMoney(price), ReturnName(otherid));
		}
	}
	return 1;
}*/

CMD:aeject(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1) return PermissionError(playerid);

	new otherid;
	if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/aeject [name/playerid]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerInAnyVehicle(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak di dalam kendaraan!");

	RemovePlayerFromVehicle(otherid);
	SendClientMessageEx(playerid, -1, "[i] Anda menendang pemain "YELLOW"%s(%d)"WHITE" dari kendaraan", AccountData[otherid][pName], otherid);
	return 1;
}

CMD:sl(playerid, params[])
{
	if(!SQL_IsCharacterLogged(playerid))
		return 0;
	
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new Float:speed;
		if(sscanf(params, "f", speed)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/sl [speed]~n~/sl 0 untuk disable");

		if(speed > 0.0)
		{
			SetVehicleSpeedCap(GetPlayerVehicleID(playerid), speed);
			ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Speed limit diatur ke %.1f", speed));
		}
		else if(speed < 1.0)
		{
			DisableVehicleSpeedCap(GetPlayerVehicleID(playerid));
			ShowTDN(playerid, NOTIFICATION_INFO, "Speed limit dimatikan");
		}
	}
	else return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengemudikan kendaraan!");
	return 1;
}

CMD:eject(playerid, params[])
{
	new vehid = GetPlayerVehicleID(playerid);
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new otherid;
		if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/eject [playerid/Name]");
		if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi kedalam server!");
		
		if(IsPlayerInVehicle(otherid, vehid))
		{
			RemovePlayerFromVehicle(otherid);
			SendRPMeAboveHead(playerid, "Menendang seseorang keluar dari kendaraannya", X11_PLUM1);
			ShowTDN(otherid, NOTIFICATION_WARNING, sprintf("%s telah menendang anda dari kendaraannya", GetRPName(playerid)));
		}
		else 
		{
			ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak didalam kendaraan!");
		}
	}
	else 
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang didalam kendaraan!");
	}
	return 1;
}

CMD:importveh(playerid, params[])
{
	if(CheckAdmin(playerid, 6)) return PermissionError(playerid);

	new 
		model[32],
		color1,
		color2,
		otherid
	;
	if(sscanf(params, "ds[32]I(-1)I(-1)", otherid, model, color1, color2)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/importveh [name/playerid] [model/name] [color1] [color2]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if((model[0] = GetVehicleModelByName(model)) == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle model id!");
	if(color1 < 0 || color1 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");
	if(color2 < 0 || color2 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");
	
	new count = 0;
	foreach(new i : PvtVehicles)
	{
		if(PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehOwnerID] == AccountData[otherid][pID])
			count ++;
	}

	if(count >= GetPlayerVehicleLimit(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan player tersebut telah penuh!");

	new Float:POS[4];
	GetPlayerPos(otherid, POS[0], POS[1], POS[2]);
	GetPlayerFacingAngle(otherid, POS[3]);
	Vehicle_Create(otherid, model[0], FACTION_NONE, POS[0], POS[1], POS[2], POS[3], color1, color2, 10000);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" membuat kendaraan "YELLOW"%s (%d, %d)"GRAY" untuk "YELLOW"%s(%d).", GetAdminName(playerid), GetVehicleModelName(model[0]), color1, color2, GetRPName(otherid), otherid);
	
	static tmp[128];
	format(tmp, sizeof(tmp), "Menggunakan cmd /importveh membuat kendaraan %s dan diberikan kepada %s.", GetVehicleModelName(model[0]), AccountData[otherid][pName]);
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), tmp);
	return 1;
}

CMD:aimportveh(playerid, params[])
{
	if(CheckAdmin(playerid, 7)) return PermissionError(playerid);

	new 
		model[32],
		color1,
		color2,
		otherid
	;
	if(sscanf(params, "ds[32]I(-1)I(-1)", otherid, model, color1, color2)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/importveh [name/playerid] [model/name] [color1] [color2]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if((model[0] = GetVehicleModelByName(model)) == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle model id!");
	if(color1 < 0 || color1 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");
	if(color2 < 0 || color2 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");

	new Float:POS[4];
	GetPlayerPos(otherid, POS[0], POS[1], POS[2]);
	GetPlayerFacingAngle(otherid, POS[3]);
	Vehicle_Create(otherid, model[0], FACTION_NONE, POS[0], POS[1], POS[2], POS[3], color1, color2, 10000);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" membuat kendaraan "YELLOW"%s (%d, %d)"GRAY" untuk "YELLOW"%s(%d).", GetAdminName(playerid), GetVehicleModelName(model[0]), color1, color2, GetRPName(otherid), otherid);
	
	static tmp[128];
	format(tmp, sizeof(tmp), "Menggunakan cmd /aimportveh membuat kendaraan %s dan diberikan kepada %s.", GetVehicleModelName(model[0]), AccountData[otherid][pName]);
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), tmp);
	return 1;
}

alias:createpv("makeveh", "cpv", "makepv", "vcreate")
CMD:createpv(playerid, params[])
{
	if(CheckAdmin(playerid, 6)) return PermissionError(playerid);

	new 
		model[32],
		color1,
		color2,
		otherid
	;
	if(sscanf(params, "ds[32]I(-1)I(-1)", otherid, model, color1, color2)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/createpv [name/playerid] [model/name] [color1] [color2]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if((model[0] = GetVehicleModelByName(model)) == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle model id!");
	if(color1 < 0 || color1 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");
	if(color2 < 0 || color2 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");
	
	new count = 0;
	foreach(new i : PvtVehicles)
	{
		if(PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehOwnerID] == AccountData[otherid][pID])
			count ++;
	}

	if(count >= GetPlayerVehicleLimit(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan player tersebut telah penuh!");

	new Float:POS[4];
	GetPlayerPos(otherid, POS[0], POS[1], POS[2]);
	GetPlayerFacingAngle(otherid, POS[3]);

	Vehicle_Create(otherid, model[0], FACTION_NONE, POS[0], POS[1], POS[2], POS[3], color1, color2, 10000);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" membuat kendaraan "YELLOW"%s (%d, %d)"GRAY" untuk "YELLOW"%s(%d).", GetAdminName(playerid), GetVehicleModelName(model[0]), color1, color2, GetRPName(otherid), otherid);

	static tmp[128];
	format(tmp, sizeof(tmp), "Menggunakan cmd /makepv membuat kendaraan %s dan diberikan kepada %s.", GetVehicleModelName(model[0]), AccountData[otherid][pName]);
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), tmp);
	return 1;
}

CMD:amakepv(playerid, params[])
{
	if(CheckAdmin(playerid, 6)) return PermissionError(playerid);

	new 
		model[32],
		color1,
		color2,
		otherid
	;
	if(sscanf(params, "ds[32]I(-1)I(-1)", otherid, model, color1, color2)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/createpv [name/playerid] [model/name] [color1] [color2]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if((model[0] = GetVehicleModelByName(model)) == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle model id!");
	if(color1 < 0 || color1 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");
	if(color2 < 0 || color2 > 255) return ShowTDN(playerid, NOTIFICATION_ERROR, "Input color tidak valid! (1 - 255)");

	new Float:POS[4];
	GetPlayerPos(otherid, POS[0], POS[1], POS[2]);
	GetPlayerFacingAngle(otherid, POS[3]);

	Vehicle_Create(otherid, model[0], FACTION_NONE, POS[0], POS[1], POS[2], POS[3], color1, color2, 10000);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" membuat kendaraan "YELLOW"%s (%d, %d)"GRAY" untuk "YELLOW"%s(%d).", GetAdminName(playerid), GetVehicleModelName(model[0]), color1, color2, GetRPName(otherid), otherid);

	static tmp[128];
	format(tmp, sizeof(tmp), "Menggunakan cmd /amakepv membuat kendaraan %s dan diberikan kepada %s.", GetVehicleModelName(model[0]), AccountData[otherid][pName]);
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), tmp);
	return 1;
}

alias:deletepv("destroypv", "dpv", "vdelete")
CMD:deletepv(playerid, params[])
{
	if(CheckAdmin(playerid, 4))
		return PermissionError(playerid);
	
	if(isnull(params))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/destroypv [VID Vehicles]");
	
	if(strval(params) == INVALID_VEHICLE_ID)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid VID Vehicles!");
	
	if(Vehicle_GetID(strval(params)) != -1)
	{
		Vehicle_Delete(Vehicle_GetID(strval(params)));
		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menghancurkan kendaraan ID:"YELLOW" %d.", GetAdminName(playerid), strval(params));
	}
	else 
		ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Player Vehicle ID!");
	
	static tmp[128];
	format(tmp, sizeof(tmp), "Menggunakan cmd /deletepv menghapus kendaraan vID: %d.", strval(params));
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), tmp);
	return 1;
}

alias:avehlist("apv")
CMD:avehlist(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1)
		return PermissionError(playerid);
	new 
		otherid,
		CMDString[3056],
		bool: found = false 
	;
	if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/apv [playerid/Name]");
	if(otherid == INVALID_PLAYER_ID || !IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke dalam server!");

	static frmtxt[255];
	format(CMDString,sizeof(CMDString),"VID\tModel Kendaraan(Database ID)\tNomor Plate\t/Rental/Status/\n");
	foreach(new iter : PvtVehicles)
	{
		if(PlayerVehicle[iter][pVehExists])
		{
			if(IsValidVehicle(PlayerVehicle[iter][pVehPhysic]) || !IsValidVehicle(PlayerVehicle[iter][pVehPhysic]))
			{
				if(PlayerVehicle[iter][pVehOwnerID] == GetUCPSQLID(otherid))
				{
					if(strcmp(PlayerVehicle[iter][pVehPlate], "-") || strcmp(PlayerVehicle[iter][pVehPlate], "-"))
					{
						new currentTime = PlayerVehicle[iter][pVehRentTime] - gettime();
						new hours = (currentTime % 86400) / 3600;
						new minutes = (currentTime % 3600) / 60;
						new seconds = currentTime % 60;
						format(frmtxt, sizeof(frmtxt), "%d Jam %d Menit %d Detik", hours, minutes, seconds);

						if(PlayerVehicle[iter][pVehRental] != -1 && PlayerVehicle[iter][pVehRentTime] > 0)
						{
							format(CMDString, sizeof(CMDString), "%s%d\t%s(%d)\t%s\t%s/%s\n", CMDString, PlayerVehicle[iter][pVehPhysic], GetVehicleModelName(PlayerVehicle[iter][pVehModelID]), PlayerVehicle[iter][pVehID], PlayerVehicle[iter][pVehPlate], frmtxt, GetMyVehicleStatus(iter, "Spawned"));
						}
						else 
						{
							format(CMDString, sizeof(CMDString), "%s%d\t%s(%d)\t%s\t"GREEN"Dimiliki"WHITE"/%s\n", CMDString, PlayerVehicle[iter][pVehPhysic], GetVehicleModelName(PlayerVehicle[iter][pVehModelID]), PlayerVehicle[iter][pVehID], PlayerVehicle[iter][pVehPlate], GetMyVehicleStatus(iter, "Spawned"));
						}
						found = true;
					}
					else
					{
						if(PlayerVehicle[iter][pVehRental] != -1 && PlayerVehicle[iter][pVehRentTime] > 0)
						{
							format(CMDString, sizeof(CMDString), "%s%d\t%s(%d)\t%s\t%s/%s\n", CMDString, PlayerVehicle[iter][pVehPhysic], GetVehicleModelName(PlayerVehicle[iter][pVehModelID]), PlayerVehicle[iter][pVehID], PlayerVehicle[iter][pVehPlate], frmtxt, GetMyVehicleStatus(iter, "Spawned"));
						}
						else 
						{
							format(CMDString, sizeof(CMDString), "%s%d\t%s(%d)\t%s\t"GREEN"Dimiliki"WHITE"/%s\n", CMDString, PlayerVehicle[iter][pVehPhysic], GetVehicleModelName(PlayerVehicle[iter][pVehModelID]), PlayerVehicle[iter][pVehID], PlayerVehicle[iter][pVehPlate], GetMyVehicleStatus(iter, "Spawned"));
						}
						found = true;
					}
				}
			}
		}
	}
	if(found)
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Player Vehicle", CMDString, "Tutup", "");
	else 
		ShowTDN(playerid, NOTIFICATION_WARNING, "Pemain tersebut tidak memiliki kendaraan apapun!");
	return 1;
}

CMD:aveh(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	new vehicleid = GetNearestVehicleToPlayer(playerid, 5.0, false);

	if(vehicleid == INVALID_VEHICLE_ID)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak berada didekat Kendaraan apapun.");
	
	SendClientMessageEx(playerid, X11_ARWIN, "[AdmCmd]"RED" %s"ARWIN1" Kendaraan didekatmu VID: "YELLOW"%d - %s(%d).", GetAdminName(playerid), vehicleid, GetVehicleName(vehicleid), GetVehicleModel(vehicleid));
	return 1;
}

CMD:sendveh(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1) return PermissionError(playerid);

	new otherid, VID, Float:x, Float:y, Float:z;
	if(sscanf(params, "ud", otherid, VID)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/sendveh [name/playerid] [vID]~n~/apv - mencari VID pemain");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsValidVehicle(VID)) return ShowTDN(playerid, NOTIFICATION_ERROR, "VID Tidak valid!");

	GetPlayerPos(otherid, x, y, z);
	SetVehiclePos(VID, x, y, z + 0.5);
	SetVehicleVirtualWorld(VID, GetPlayerVirtualWorld(otherid));
	LinkVehicleToInterior(VID, GetPlayerInterior(otherid));
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" mengirim kendaraan "YELLOW"%d - %s(%d)"ARWIN1" kepada "YELLOW"%s(%d) - %s", AccountData[playerid][pAdminname], VID, GetVehicleName(VID), GetVehicleModel(VID), AccountData[otherid][pName], otherid, GetLocation(x, y, z));
	return 1;
}

alias:getveh("vget")
CMD:getveh(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1) return PermissionError(playerid);

	new VID, Float:x, Float:y, Float:z;
	if(sscanf(params, "d", VID)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/getveh [VID]~n~/apv - mencari VID pemain");
	if(VID == INVALID_VEHICLE_ID || !IsValidVehicle(VID)) return ShowTDN(playerid, NOTIFICATION_ERROR, "VID Tidak valid!");
	GetPlayerPos(playerid, z, z, z);

	GetXYInFrontOfPlayer(playerid, x, y, 3.0);
	SetVehiclePos(VID, x, y, z);

	SetVehicleVirtualWorld(VID, GetPlayerVirtualWorld(playerid));
	LinkVehicleToInterior(VID, GetPlayerInterior(playerid));
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menarik kendaraan "YELLOW"%d - %s(%d)"ARWIN1" ke %s", AccountData[playerid][pAdminname], VID, GetVehicleName(VID), GetVehicleModel(VID), GetLocation(x, y, z));
	return 1;
}

CMD:gotoveh(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1)
		return PermissionError(playerid);

	new vehid, Float:posisiX, Float:posisiY, Float:posisiZ;
	if(sscanf(params, "d", vehid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotoveh [vehid] | /apv - for find vehid");
	if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid id");
	if(!IsValidVehicle(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid id");
	
	GetVehiclePos(vehid, posisiX, posisiY, posisiZ);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" teleportasi ke kendaraan "YELLOW"VID %d - %s(%d)"ARWIN1". Lokasi %s", GetAdminName(playerid), vehid, GetVehicleName(vehid), GetVehicleModel(vehid), GetLocation(posisiX, posisiY, posisiZ));
	SetPlayerPosition(playerid, posisiX, posisiY, posisiZ+3.0, 4.0, 0);
	SetPlayerVirtualWorld(playerid, GetVehicleVirtualWorld(vehid));
	AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
	return 1;
}

CMD:respawnveh(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 1)
		return PermissionError(playerid);

	new vehid, Float:posisiX, Float:posisiY, Float:posisiZ;
	if(sscanf(params, "d", vehid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/respawnveh [vehid] | /apv - for find vehid");
	if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid id");
	if(!IsValidVehicle(vehid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid id");
	GetVehiclePos(vehid, posisiX, posisiY, posisiZ);
	if(IsVehicleEmpty(vehid))
	{
		SetTimerEx("RespawnPV", 3000, false, "d", vehid);
		Info(playerid, "Your respawned vehicle location %s (vehicle id: %d).", GetLocation(posisiX, posisiY, posisiZ), vehid);
	}
	else ShowTDN(playerid, NOTIFICATION_ERROR, "This Vehicle in used by someone.");
	return 1;
}

CMD:myv(playerid, params[])
{
	if(!AccountData[playerid][IsLoggedIn]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus terkoneksi ke dalam server!");
	if(!GetOwnedVeh(playerid)) return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kepemilikan Kendaraan", "Anda tidak memiliki kendaraan apapun!", "Tutup", "");

	new count = GetOwnedVeh(playerid);
	static 
		vid,
		list[512],
		CMDString[4056],
		Status1[512],
		StatusSpawn[512],
		PlateStatus[128]
	;

	CMDString = "";
	strcat(CMDString, "VID\tModel(Database ID)\tPlate(Masa Berlaku)\tRental/Status/\n", sizeof(CMDString));
	Loop(itt, (count + 1), 1)
	{
		vid = ReturnPlayerVehID(playerid, itt);

		if(PlayerVehicle[vid][pVehPlateOwn]) {
			format(PlateStatus, sizeof(PlateStatus), "- ("DARKRED"Permanent"WHITE")");
		} else {
			format(PlateStatus, sizeof(PlateStatus), " (Kosong)");
		}

		if(PlayerVehicle[vid][pVehPhysic] == INVALID_VEHICLE_ID) {
			format(StatusSpawn, sizeof(StatusSpawn), "[Despawned]");
		} else {
			format(StatusSpawn, sizeof(StatusSpawn), "%d", PlayerVehicle[vid][pVehPhysic]);
		}

		if(PlayerVehicle[vid][pVehRental] > 0 && PlayerVehicle[vid][pVehRentTime] != 0) {
			new currentTime = PlayerVehicle[vid][pVehRentTime] - gettime();
			new hours = (currentTime % 86400) / 3600;
			new minutes = (currentTime % 3600) / 60;
			new seconds = currentTime % 60;

			format(Status1, sizeof(Status1), "%d Jam %d Menit %d Detik", hours, minutes, seconds);
		} else {
			format(Status1, sizeof(Status1), ""GREEN"Dimiliki");
		}

		if(itt == count)
		{
			format(list, sizeof(list), "%s\t%s [%d]\t%s %s\t%s"WHITE"/%s/\n", StatusSpawn, GetVehicleModelName(PlayerVehicle[vid][pVehModelID]), PlayerVehicle[vid][pVehID], PlayerVehicle[vid][pVehPlate], PlateStatus, Status1, GetMyVehicleStatus(vid, "Spawned"));
		}
		else format(list, sizeof(list), "%s\t%s [%d]\t%s %s\t%s"WHITE"/%s/\n", StatusSpawn, GetVehicleModelName(PlayerVehicle[vid][pVehModelID]), PlayerVehicle[vid][pVehID], PlayerVehicle[vid][pVehPlate], PlateStatus, Status1, GetMyVehicleStatus(vid, "Spawned"));
		strcat(CMDString, list);
	}
	ShowPlayerDialog(playerid, DialogMyVeh, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Kepemilikan Kendaraan", CMDString, "Cari", "Cancel");
	return 1;
}

CMD:en(playerid, params[])
{
	if(AccountData[playerid][pTurningEngine])
		return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang menyalakan mesin, tunggu sebentar!");
	
	new vehid = GetPlayerVehicleID(playerid);
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		if(!IsEngineVehicle(vehid))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan kendaraan bermesin!");
		
		if(GetEngineStatus(vehid))
		{
			SwitchVehicleEngine(vehid, false);
			SendRPMeAboveHead(playerid, "Mesin mati", X11_LIGHTGREEN);
		}
		else 
		{
			SendRPMeAboveHead(playerid, "Mencoba menghidupkan mesin kendaraan", X11_PLUM1);
			AccountData[playerid][pTurningEngine] = true;
			SetTimerEx("EngineStatus", 2500, false, "id", playerid, vehid);
		}
	}
	else ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada didalam kendaraan apapun!");
	return 1;
}

CMD:windows(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);
	new vehicle_index = Vehicle_ReturnID(vehicleid);

	if(vehicle_index == RETURN_INVALID_VEHICLE_ID) return 1;
	if(!IsPlayerInAnyVehicle(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dalam kendaraan untuk menggunakan ini!");
	if(!IsFourWheelVehicle(vehicleid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda hanya dapat menggunakannya di kendaraan roda 4!");

	Dialog_Show(playerid, WindowsControl, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Vehicle Windows Control", "Driver Seat\nPassenger Seat\nBack Left\nBack Right\nClose All", "Choose", "Close");
	return 1;
}

Dialog:WindowsControl(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new vehicleid = GetPlayerVehicleID(playerid),
            driver, passenger, backleft, backright;

        GetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, backright);

        if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            switch(listitem)
            {
                case 0: SetVehicleParamsCarWindows(vehicleid, !driver, passenger, backleft, backright);
                case 1: SetVehicleParamsCarWindows(vehicleid, driver, !passenger, backleft, backright);
                case 2: SetVehicleParamsCarWindows(vehicleid, driver, passenger, !backleft, backright);
                case 3: SetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, !backright);
                default: SetVehicleParamsCarWindows(vehicleid, !driver, !driver, !driver, !driver);
            }
            Info(playerid, "Anda mengaktifkan toggle windows");
        }
    }
    return 1;
}

CMD:tow(playerid, params[]) 
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		new carid = GetPlayerVehicleID(playerid);
		if(IsATowTruck(carid))
		{
			new closestcar = GetClosestCar(playerid, carid);

			if(GetDistanceToCar(playerid, closestcar) <= 8 && !IsTrailerAttachedToVehicle(carid)) 
			{
				ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menderek kendaraan!");
				AttachTrailerToVehicle(closestcar, carid);
				return 1;
			}
		}
		else
		{
			ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengendarai Tow truck.");
			return 1;
		}
	}
	else
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengendarai Tow truck.");
		return 1;
	}
	return 1;
}

CMD:untow(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
		{
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil melepas derekan!");
			DetachTrailerFromVehicle(GetPlayerVehicleID(playerid));
		}
		else
		{
			ShowTDN(playerid, NOTIFICATION_ERROR, "Tow penderek kosong!");
		}
	}
	else
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengendarai Tow truck.");
		return 1;
	}
	return 1;
}

/* Hooks */
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	foreach(new id : PublicGarage)
	{
		if(newkeys & KEY_CROUCH && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.5, PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2]))
			{
				HideShortKey(playerid);
				
				new carid = -1, bool: found = false;
				if((carid = Vehicle_Nearest2(playerid)) != -1)
				{
					if(IsAirVehicle(PlayerVehicle[carid][pVehModelID])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan udara tidak bisa parkir di garkot ini!");
					if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
					if(PlayerVehicle[carid][pVehRental] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat disimpan!");
					if(PlayerVehicle[carid][pVehFaction] != FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan faction tidak dapat disimpan disini!");

					Vehicle_GetStatus(carid);
					PlayerVehicle[carid][pVehParked] = id;

					found = true;

					RemovePlayerFromVehicle(playerid);
					if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]))
					{
						DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
						SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

						DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
						PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
					}
				}
				if(!found) return false;
			} 
			else if(IsPlayerInRangeOfPoint(playerid, 2.5, PublicGarage[id][pgUdaraPos][0], PublicGarage[id][pgUdaraPos][1], PublicGarage[id][pgUdaraPos][2]))
			{
				HideShortKey(playerid);
				
				new carid = -1, bool: found = false;
				if((carid = Vehicle_Nearest2(playerid)) != -1)
				{
					if(!IsAirVehicle(PlayerVehicle[carid][pVehModelID])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan darat tidak bisa parkir di garkot ini!");
					if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
					if(PlayerVehicle[carid][pVehRental] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat disimpan!");
					if(PlayerVehicle[carid][pVehFaction] != FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan faction tidak dapat disimpan disini!");

					Vehicle_GetStatus(carid);
					PlayerVehicle[carid][pVehParked] = id;

					found = true;

					RemovePlayerFromVehicle(playerid);
					if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]))
					{
						DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
						SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

						DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
						PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
					}
				}
				if(!found) return false;
			}
		}	
		if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.5, PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2]))
			{
				HideShortKey(playerid);
				
				if(!CountPlayerVehicleParked(playerid, id)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun di garasi ini!");

				for(new x = 0; x < 15; x ++) PlayerTextDrawHide(playerid, HbeStuffs[playerid][x]);
				HideHBE(playerid);
				ShowGarasiTD(playerid, true);
                SelectTextDraw(playerid, X11_ARWIN);

				new vehid, count = CountPlayerVehicleParked(playerid, id);
				Loop(itt, (count + 1), 1)
				{
					vehid = ReturnAnyVehicleParked(playerid, itt, id);
					//if(vehid == -1) continue; // Cegah error kalau kendaraan gak valid

					printf("Vehicle ID: %d, Model ID: %d", vehid, PlayerVehicle[vehid][pVehModelID]);

					TextDrawSetPreviewModel(GarasiTD[44 + (itt - 1) * 3], PlayerVehicle[vehid][pVehModelID]);
					TextDrawSetString(GarasiTD[32 + (itt - 1) * 2], GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]));

					TextDrawShowForPlayer(playerid, GarasiTD[24 + (itt - 1)]);
                    TextDrawShowForPlayer(playerid, GarasiTD[28 + (itt - 1)]);
                    TextDrawShowForPlayer(playerid, GarasiTD[32 + (itt - 1) * 2]);
                    TextDrawShowForPlayer(playerid, GarasiTD[33 + (itt - 1) * 2]);
					TextDrawShowForPlayer(playerid, GarasiTD[40 + (itt - 1)]);
                    TextDrawShowForPlayer(playerid, GarasiTD[44 + (itt - 1) * 3]);
                    TextDrawShowForPlayer(playerid, GarasiTD[45 + (itt - 1) * 3]);
                    TextDrawShowForPlayer(playerid, GarasiTD[46 + (itt - 1) * 3]);
				}
				AccountData[playerid][pPark] = id;
				//ShowPlayerDialog(playerid, DIALOG_GARKOT_OUT, DIALOG_STYLE_TABLIST_HEADERS, "Garasi Umum - Ambil Kendaraan", lstr, "Pilih", "Batal");
			}
			else if(IsPlayerInRangeOfPoint(playerid, 2.5, PublicGarage[id][pgUdaraPos][0], PublicGarage[id][pgUdaraPos][1], PublicGarage[id][pgUdaraPos][2]))
			{
				HideShortKey(playerid);
				
				if(!CountPlayerVehicleParked(playerid, id)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun di garasi ini!");

				for(new x = 0; x < 15; x ++) PlayerTextDrawHide(playerid, HbeStuffs[playerid][x]);
				HideHBE(playerid);
				ShowGarasiTD(playerid, true);
                SelectTextDraw(playerid, X11_ARWIN);

				new vehid, count = CountPlayerVehicleParked(playerid, id);
				Loop(itt, (count + 1), 1)
				{
					vehid = ReturnAnyVehicleParked(playerid, itt, id);
					//if(vehid == -1) continue; // Cegah error kalau kendaraan gak valid

					printf("Vehicle ID: %d, Model ID: %d", vehid, PlayerVehicle[vehid][pVehModelID]);

					TextDrawSetPreviewModel(GarasiTD[44 + (itt - 1) * 3], PlayerVehicle[vehid][pVehModelID]);
					TextDrawSetString(GarasiTD[32 + (itt - 1) * 2], GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]));

					TextDrawShowForPlayer(playerid, GarasiTD[24 + (itt - 1)]);
                    TextDrawShowForPlayer(playerid, GarasiTD[28 + (itt - 1)]);
                    TextDrawShowForPlayer(playerid, GarasiTD[32 + (itt - 1) * 2]);
                    TextDrawShowForPlayer(playerid, GarasiTD[33 + (itt - 1) * 2]);
					TextDrawShowForPlayer(playerid, GarasiTD[40 + (itt - 1)]);
                    TextDrawShowForPlayer(playerid, GarasiTD[44 + (itt - 1) * 3]);
                    TextDrawShowForPlayer(playerid, GarasiTD[45 + (itt - 1) * 3]);
                    TextDrawShowForPlayer(playerid, GarasiTD[46 + (itt - 1) * 3]);
				}
				AccountData[playerid][pPark] = id;
			}
		}
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case DIALOG_GARKOT_OUT:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
			if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
			if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan yang ingin dikeluarkan!");

			new id = ReturnAnyVehicleParked(playerid, listitem, AccountData[playerid][pPark]);
			if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan yang ingin dikeluarkan!");

			if(!IsPlayerInRangeOfPoint(playerid, 2.5, PublicGarage[AccountData[playerid][pPark]][pgPOS][0], PublicGarage[AccountData[playerid][pPark]][pgPOS][1], PublicGarage[AccountData[playerid][pPark]][pgPOS][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak didekat Garasi Umum!");
			if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
			PlayerVehicle[id][pVehParked] = -1;
			PlayerVehicle[id][pVehHouseGarage] = -1;
			PlayerVehicle[id][pVehHelipadGarage] = -1;
			PlayerVehicle[id][pVehFamiliesGarage] = -1;
			PlayerVehicle[id][pVehFactStored] = -1;

			if(PlayerVehicle[id][pVehLocked])
				PlayerVehicle[id][pVehLocked] = false;

			PlayerVehicle[id][pVehPos][0] = PublicGarage[AccountData[playerid][pPark]][pgSpawnPOS][0];
			PlayerVehicle[id][pVehPos][1] = PublicGarage[AccountData[playerid][pPark]][pgSpawnPOS][1];
			PlayerVehicle[id][pVehPos][2] = PublicGarage[AccountData[playerid][pPark]][pgSpawnPOS][2];
			PlayerVehicle[id][pVehPos][3] = PublicGarage[AccountData[playerid][pPark]][pgSpawnPOS][3];

			PlayerVehicle[id][pVehWorld] = PublicGarage[AccountData[playerid][pPark]][pgWorld];
            PlayerVehicle[id][pVehInterior] = PublicGarage[AccountData[playerid][pPark]][pgInterior];

			PlayerVehicle[id][pVehFuel] = PlayerVehicle[id][pVehFuel];
			PlayerVehicle[id][pVehHealth] = PlayerVehicle[id][pVehHealth];

			OnPlayerVehicleRespawn(id);

			SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
		}
	}
	return 1;
}

hook OnClickDynTextDraw(playerid, Text:textid)
{
	if(textid == GarasiTD[24]) //mobil 1
	{
		SelectGarasi[playerid] = 1;

		new vehid = ReturnAnyVehicleParked(playerid, SelectGarasi[playerid], AccountData[playerid][pPark]);

		new string[256], vehName[32];
		format(vehName, sizeof(vehName), GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]));

		new Float:vehHealth;
		format(string, sizeof(string), "Models: %s\nHealth: %.0f%%", vehName, vehHealth / 10.0);

		TextDrawSetString(GarasiTD[72], string);
		for(new i = 56; i < 73; i++)
		{
			TextDrawShowForPlayer(playerid, GarasiTD[i]);
		}
	}
	if(textid == GarasiTD[25]) // mobil 2
	{
		SelectGarasi[playerid] = 2;

		new vehid = ReturnAnyVehicleParked(playerid, SelectGarasi[playerid], AccountData[playerid][pPark]);

		new string[256], vehName[32];
		format(vehName, sizeof(vehName), GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]));

		new Float:vehHealth;
		format(string, sizeof(string), "Models: %s\nHealth: %.0f%%", vehName, vehHealth / 10.0);

		TextDrawSetString(GarasiTD[72], string);
		for(new i = 56; i < 73; i++)
		{
			TextDrawShowForPlayer(playerid, GarasiTD[i]);
		}
	}
	if(textid == GarasiTD[26]) // mobil 3
	{
		SelectGarasi[playerid] = 3;

		new vehid = ReturnAnyVehicleParked(playerid, SelectGarasi[playerid], AccountData[playerid][pPark]);

		new string[256], vehName[32];
		format(vehName, sizeof(vehName), GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]));

		new Float:vehHealth;
		format(string, sizeof(string), "Models: %s\nHealth: %.0f%%", vehName, vehHealth / 10.0);

		TextDrawSetString(GarasiTD[72], string);
		for(new i = 56; i < 73; i++)
		{
			TextDrawShowForPlayer(playerid, GarasiTD[i]);
		}
	}
	if(textid == GarasiTD[27]) // mobil 4
	{
		SelectGarasi[playerid] = 4;

		new vehid = ReturnAnyVehicleParked(playerid, SelectGarasi[playerid], AccountData[playerid][pPark]);

		new string[256], vehName[32];
		format(vehName, sizeof(vehName), GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]));

		new Float:vehHealth;
		format(string, sizeof(string), "Models: %s\nHealth: %.0f%%", vehName, vehHealth / 10.0);

		TextDrawSetString(GarasiTD[72], string);
		for(new i = 56; i < 73; i++)
		{
			TextDrawShowForPlayer(playerid, GarasiTD[i]);
		}
	}
	if(textid == GarasiTD[22]) //exit
	{
		ShowGarasiTD(playerid, false);
		ShowHbeTextdraws(playerid, AccountData[playerid][pHUDMode]);
		CancelSelectTextDraw(playerid);
	}
	if(textid == GarasiTD[22]) //exit
	{
		ShowGarasiTD(playerid, false);
		ShowHbeTextdraws(playerid, AccountData[playerid][pHUDMode]);
		CancelSelectTextDraw(playerid);
	}
	if(textid == GarasiTD[68]) //takeout
	{
		new vid = ReturnAnyVehicleParked(playerid, SelectGarasi[playerid], AccountData[playerid][pPark]);

		OnPlayerVehicleRespawn(vid);

		PlayerVehicle[vid][pVehParked] = -1;
		PlayerVehicle[vid][pVehHouseGarage] = -1;
		PlayerVehicle[vid][pVehHelipadGarage] = -1;
		PlayerVehicle[vid][pVehFamiliesGarage] = -1;
		PlayerVehicle[vid][pVehFactStored] = -1;

		if(PlayerVehicle[vid][pVehLocked])
			PlayerVehicle[vid][pVehLocked] = false;

		new pgid = AccountData[playerid][pPark];
		new Float:spawnX, Float:spawnY, Float:spawnZ, Float:spawnA;

		// Pilih posisi spawn sesuai tipe garkot
		if(PublicGarage[pgid][pgUdaraPos][0] != 0.0) // ada udara
		{
			spawnX = PublicGarage[pgid][pgUdaraSpawn][0];
			spawnY = PublicGarage[pgid][pgUdaraSpawn][1];
			spawnZ = PublicGarage[pgid][pgUdaraSpawn][2];
			spawnA = PublicGarage[pgid][pgUdaraSpawn][3];
		}
		else // default darat
		{
			spawnX = PublicGarage[pgid][pgSpawnPOS][0];
			spawnY = PublicGarage[pgid][pgSpawnPOS][1];
			spawnZ = PublicGarage[pgid][pgSpawnPOS][2];
			spawnA = PublicGarage[pgid][pgSpawnPOS][3];
		}

		// Set posisi kendaraan
		PlayerVehicle[vid][pVehPos][0] = spawnX;
		PlayerVehicle[vid][pVehPos][1] = spawnY;
		PlayerVehicle[vid][pVehPos][2] = spawnZ;
		PlayerVehicle[vid][pVehPos][3] = spawnA;

		PlayerVehicle[vid][pVehWorld] = PublicGarage[AccountData[playerid][pPark]][pgWorld];
        PlayerVehicle[vid][pVehInterior] = PublicGarage[AccountData[playerid][pPark]][pgInterior];

		PlayerVehicle[vid][pVehFuel] = PlayerVehicle[vid][pVehFuel];
		PlayerVehicle[vid][pVehHealth] = PlayerVehicle[vid][pVehHealth];

		SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[vid][pVehPhysic], 0);
		SetCameraBehindPlayer(playerid);
		ShowGarasiTD(playerid, false);
		ShowHbeTextdraws(playerid, AccountData[playerid][pHUDMode]);
		CancelSelectTextDraw(playerid);
	}
	return 1;
}

stock ShowGarasiTD(playerid, show)
{
    new shownCount = 0, hiddenCount = 0; // Variabel untuk menghitung jumlah TextDraw

    if(show)
    {
        for(new i = 1; i < 73; i++)
        {
            TextDrawShowForPlayer(playerid, GarasiTD[i]);
            shownCount++;

            TextDrawHideForPlayer(playerid, GarasiTD[72]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[71]); hiddenCount++;

            TextDrawHideForPlayer(playerid, GarasiTD[24]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[28]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[32]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[33]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[40]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[44]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[45]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[46]); hiddenCount++;

            TextDrawHideForPlayer(playerid, GarasiTD[25]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[29]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[34]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[35]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[41]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[47]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[48]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[49]); hiddenCount++;

            TextDrawHideForPlayer(playerid, GarasiTD[26]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[30]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[36]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[37]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[42]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[50]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[51]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[52]); hiddenCount++;

            TextDrawHideForPlayer(playerid, GarasiTD[27]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[31]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[38]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[39]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[43]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[53]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[54]); hiddenCount++;
            TextDrawHideForPlayer(playerid, GarasiTD[55]); hiddenCount++;

            for(new b = 56; b < 73; b++)
            {
                TextDrawHideForPlayer(playerid, GarasiTD[b]);
                hiddenCount++;
            }
        }

        printf("ShowGarasiTD: %d TextDraws ditampilkan, %d TextDraws disembunyikan.", shownCount, hiddenCount);
    }
    else
    {
        for(new i = 1; i < 73; i++)
        {
            TextDrawHideForPlayer(playerid, GarasiTD[i]);
            hiddenCount++;
        }

        printf("ShowGarasiTD: %d TextDraws disembunyikan.", hiddenCount);
    }
}

CreateGarasiTD()
{
    GarasiTD[0] = TextDrawCreate(181.000, -209.000, "LD_BEAT:chit");
    TextDrawTextSize(GarasiTD[0], 711.000, 876.000);
    TextDrawAlignment(GarasiTD[0], 1);
    TextDrawColor(GarasiTD[0], 0);
    TextDrawSetShadow(GarasiTD[0], 0);
    TextDrawSetOutline(GarasiTD[0], 0);
    TextDrawBackgroundColor(GarasiTD[0], 255);
    TextDrawFont(GarasiTD[0], 4);
    TextDrawSetProportional(GarasiTD[0], 1);

    GarasiTD[1] = TextDrawCreate(450.000, 102.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[1], 164.000, 260.000);
    TextDrawAlignment(GarasiTD[1], 1);
    TextDrawColor(GarasiTD[1], 5864447);
    TextDrawSetShadow(GarasiTD[1], 0);
    TextDrawSetOutline(GarasiTD[1], 0);
    TextDrawBackgroundColor(GarasiTD[1], 255);
    TextDrawFont(GarasiTD[1], 4);
    TextDrawSetProportional(GarasiTD[1], 1);

    GarasiTD[2] = TextDrawCreate(444.000, 111.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[2], 176.000, 241.000);
    TextDrawAlignment(GarasiTD[2], 1);
    TextDrawColor(GarasiTD[2], 5864447);
    TextDrawSetShadow(GarasiTD[2], 0);
    TextDrawSetOutline(GarasiTD[2], 0);
    TextDrawBackgroundColor(GarasiTD[2], 255);
    TextDrawFont(GarasiTD[2], 4);
    TextDrawSetProportional(GarasiTD[2], 1);

    GarasiTD[3] = TextDrawCreate(440.000, 97.000, "LD_BEAT:chit");
    TextDrawTextSize(GarasiTD[3], 23.000, 30.000);
    TextDrawAlignment(GarasiTD[3], 1);
    TextDrawColor(GarasiTD[3], 5864447);
    TextDrawSetShadow(GarasiTD[3], 0);
    TextDrawSetOutline(GarasiTD[3], 0);
    TextDrawBackgroundColor(GarasiTD[3], 255);
    TextDrawFont(GarasiTD[3], 4);
    TextDrawSetProportional(GarasiTD[3], 1);

    GarasiTD[4] = TextDrawCreate(601.000, 97.000, "LD_BEAT:chit");
    TextDrawTextSize(GarasiTD[4], 23.000, 30.000);
    TextDrawAlignment(GarasiTD[4], 1);
    TextDrawColor(GarasiTD[4], 5864447);
    TextDrawSetShadow(GarasiTD[4], 0);
    TextDrawSetOutline(GarasiTD[4], 0);
    TextDrawBackgroundColor(GarasiTD[4], 255);
    TextDrawFont(GarasiTD[4], 4);
    TextDrawSetProportional(GarasiTD[4], 1);

    GarasiTD[5] = TextDrawCreate(601.000, 336.000, "LD_BEAT:chit");
    TextDrawTextSize(GarasiTD[5], 23.000, 31.000);
    TextDrawAlignment(GarasiTD[5], 1);
    TextDrawColor(GarasiTD[5], 5864447);
    TextDrawSetShadow(GarasiTD[5], 0);
    TextDrawSetOutline(GarasiTD[5], 0);
    TextDrawBackgroundColor(GarasiTD[5], 255);
    TextDrawFont(GarasiTD[5], 4);
    TextDrawSetProportional(GarasiTD[5], 1);

    GarasiTD[6] = TextDrawCreate(440.000, 336.000, "LD_BEAT:chit");
    TextDrawTextSize(GarasiTD[6], 23.000, 31.000);
    TextDrawAlignment(GarasiTD[6], 1);
    TextDrawColor(GarasiTD[6], 5864447);
    TextDrawSetShadow(GarasiTD[6], 0);
    TextDrawSetOutline(GarasiTD[6], 0);
    TextDrawBackgroundColor(GarasiTD[6], 255);
    TextDrawFont(GarasiTD[6], 4);
    TextDrawSetProportional(GarasiTD[6], 1);

    GarasiTD[7] = TextDrawCreate(457.000, 185.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[7], 1.000, 155.000);
    TextDrawAlignment(GarasiTD[7], 1);
    TextDrawColor(GarasiTD[7], -1);
    TextDrawSetShadow(GarasiTD[7], 0);
    TextDrawSetOutline(GarasiTD[7], 0);
    TextDrawBackgroundColor(GarasiTD[7], 255);
    TextDrawFont(GarasiTD[7], 4);
    TextDrawSetProportional(GarasiTD[7], 1);

    GarasiTD[8] = TextDrawCreate(457.000, 184.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[8], 6.000, 1.000);
    TextDrawAlignment(GarasiTD[8], 1);
    TextDrawColor(GarasiTD[8], -1);
    TextDrawSetShadow(GarasiTD[8], 0);
    TextDrawSetOutline(GarasiTD[8], 0);
    TextDrawBackgroundColor(GarasiTD[8], 255);
    TextDrawFont(GarasiTD[8], 4);
    TextDrawSetProportional(GarasiTD[8], 1);

    GarasiTD[9] = TextDrawCreate(464.000, 185.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[9], -1.000, -9.000);
    TextDrawAlignment(GarasiTD[9], 1);
    TextDrawColor(GarasiTD[9], -1);
    TextDrawSetShadow(GarasiTD[9], 0);
    TextDrawSetOutline(GarasiTD[9], 0);
    TextDrawBackgroundColor(GarasiTD[9], 255);
    TextDrawFont(GarasiTD[9], 4);
    TextDrawSetProportional(GarasiTD[9], 1);

    GarasiTD[10] = TextDrawCreate(464.000, 176.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[10], 137.000, 1.000);
    TextDrawAlignment(GarasiTD[10], 1);
    TextDrawColor(GarasiTD[10], -1);
    TextDrawSetShadow(GarasiTD[10], 0);
    TextDrawSetOutline(GarasiTD[10], 0);
    TextDrawBackgroundColor(GarasiTD[10], 255);
    TextDrawFont(GarasiTD[10], 4);
    TextDrawSetProportional(GarasiTD[10], 1);

    GarasiTD[11] = TextDrawCreate(602.000, 185.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[11], -1.000, -9.000);
    TextDrawAlignment(GarasiTD[11], 1);
    TextDrawColor(GarasiTD[11], -1);
    TextDrawSetShadow(GarasiTD[11], 0);
    TextDrawSetOutline(GarasiTD[11], 0);
    TextDrawBackgroundColor(GarasiTD[11], 255);
    TextDrawFont(GarasiTD[11], 4);
    TextDrawSetProportional(GarasiTD[11], 1);

    GarasiTD[12] = TextDrawCreate(601.000, 184.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[12], 6.000, 1.000);
    TextDrawAlignment(GarasiTD[12], 1);
    TextDrawColor(GarasiTD[12], -1);
    TextDrawSetShadow(GarasiTD[12], 0);
    TextDrawSetOutline(GarasiTD[12], 0);
    TextDrawBackgroundColor(GarasiTD[12], 255);
    TextDrawFont(GarasiTD[12], 4);
    TextDrawSetProportional(GarasiTD[12], 1);

    GarasiTD[13] = TextDrawCreate(606.000, 185.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[13], 1.000, 155.000);
    TextDrawAlignment(GarasiTD[13], 1);
    TextDrawColor(GarasiTD[13], -1);
    TextDrawSetShadow(GarasiTD[13], 0);
    TextDrawSetOutline(GarasiTD[13], 0);
    TextDrawBackgroundColor(GarasiTD[13], 255);
    TextDrawFont(GarasiTD[13], 4);
    TextDrawSetProportional(GarasiTD[13], 1);

    GarasiTD[14] = TextDrawCreate(457.000, 340.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[14], 6.000, 1.000);
    TextDrawAlignment(GarasiTD[14], 1);
    TextDrawColor(GarasiTD[14], -1);
    TextDrawSetShadow(GarasiTD[14], 0);
    TextDrawSetOutline(GarasiTD[14], 0);
    TextDrawBackgroundColor(GarasiTD[14], 255);
    TextDrawFont(GarasiTD[14], 4);
    TextDrawSetProportional(GarasiTD[14], 1);

    GarasiTD[15] = TextDrawCreate(602.000, 349.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[15], -1.000, -9.000);
    TextDrawAlignment(GarasiTD[15], 1);
    TextDrawColor(GarasiTD[15], -1);
    TextDrawSetShadow(GarasiTD[15], 0);
    TextDrawSetOutline(GarasiTD[15], 0);
    TextDrawBackgroundColor(GarasiTD[15], 255);
    TextDrawFont(GarasiTD[15], 4);
    TextDrawSetProportional(GarasiTD[15], 1);

    GarasiTD[16] = TextDrawCreate(464.000, 348.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[16], 137.000, 1.000);
    TextDrawAlignment(GarasiTD[16], 1);
    TextDrawColor(GarasiTD[16], -1);
    TextDrawSetShadow(GarasiTD[16], 0);
    TextDrawSetOutline(GarasiTD[16], 0);
    TextDrawBackgroundColor(GarasiTD[16], 255);
    TextDrawFont(GarasiTD[16], 4);
    TextDrawSetProportional(GarasiTD[16], 1);

    GarasiTD[17] = TextDrawCreate(601.000, 340.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[17], 6.000, 1.000);
    TextDrawAlignment(GarasiTD[17], 1);
    TextDrawColor(GarasiTD[17], -1);
    TextDrawSetShadow(GarasiTD[17], 0);
    TextDrawSetOutline(GarasiTD[17], 0);
    TextDrawBackgroundColor(GarasiTD[17], 255);
    TextDrawFont(GarasiTD[17], 4);
    TextDrawSetProportional(GarasiTD[17], 1);

    GarasiTD[18] = TextDrawCreate(464.000, 349.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[18], -1.000, -9.000);
    TextDrawAlignment(GarasiTD[18], 1);
    TextDrawColor(GarasiTD[18], -1);
    TextDrawSetShadow(GarasiTD[18], 0);
    TextDrawSetOutline(GarasiTD[18], 0);
    TextDrawBackgroundColor(GarasiTD[18], 255);
    TextDrawFont(GarasiTD[18], 4);
    TextDrawSetProportional(GarasiTD[18], 1);

    GarasiTD[19] = TextDrawCreate(454.000, 109.000, "Garasi District....");
    TextDrawLetterSize(GarasiTD[19], 0.150, 0.898);
    TextDrawAlignment(GarasiTD[19], 1);
    TextDrawColor(GarasiTD[19], -196921601);
    TextDrawSetShadow(GarasiTD[19], 0);
    TextDrawSetOutline(GarasiTD[19], 0);
    TextDrawBackgroundColor(GarasiTD[19], 150);
    TextDrawFont(GarasiTD[19], 1);
    TextDrawSetProportional(GarasiTD[19], 1);

    GarasiTD[20] = TextDrawCreate(454.000, 120.000, "Garasi");
    TextDrawLetterSize(GarasiTD[20], 0.289, 2.197);
    TextDrawAlignment(GarasiTD[20], 1);
    TextDrawColor(GarasiTD[20], -196921601);
    TextDrawSetShadow(GarasiTD[20], 0);
    TextDrawSetOutline(GarasiTD[20], 0);
    TextDrawBackgroundColor(GarasiTD[20], 150);
    TextDrawFont(GarasiTD[20], 1);
    TextDrawSetProportional(GarasiTD[20], 1);

    GarasiTD[21] = TextDrawCreate(455.000, 141.000, "Ambil Kendaran anda di garasi ini.");
    TextDrawLetterSize(GarasiTD[21], 0.119, 0.799);
    TextDrawAlignment(GarasiTD[21], 1);
    TextDrawColor(GarasiTD[21], -196921601);
    TextDrawSetShadow(GarasiTD[21], 0);
    TextDrawSetOutline(GarasiTD[21], 0);
    TextDrawBackgroundColor(GarasiTD[21], 150);
    TextDrawFont(GarasiTD[21], 1);
    TextDrawSetProportional(GarasiTD[21], 1);

    GarasiTD[22] = TextDrawCreate(574.000, 126.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[22], 30.000, 13.000);
    TextDrawAlignment(GarasiTD[22], 1);
    TextDrawColor(GarasiTD[22], -196921601);
    TextDrawSetShadow(GarasiTD[22], 0);
    TextDrawSetOutline(GarasiTD[22], 0);
    TextDrawBackgroundColor(GarasiTD[22], 255);
    TextDrawFont(GarasiTD[22], 4);
    TextDrawSetProportional(GarasiTD[22], 1);
    TextDrawSetSelectable(GarasiTD[22], 1);

    GarasiTD[23] = TextDrawCreate(589.000, 129.000, "Exit");
    TextDrawLetterSize(GarasiTD[23], 0.119, 0.799);
    TextDrawAlignment(GarasiTD[23], 2);
    TextDrawColor(GarasiTD[23], -1);
    TextDrawSetShadow(GarasiTD[23], 0);
    TextDrawSetOutline(GarasiTD[23], 0);
    TextDrawBackgroundColor(GarasiTD[23], 150);
    TextDrawFont(GarasiTD[23], 1);
    TextDrawSetProportional(GarasiTD[23], 1);

    GarasiTD[24] = TextDrawCreate(467.000, 186.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[24], 56.000, 53.000);
    TextDrawAlignment(GarasiTD[24], 1);
    TextDrawColor(GarasiTD[24], -126);
    TextDrawSetShadow(GarasiTD[24], 0);
    TextDrawSetOutline(GarasiTD[24], 0);
    TextDrawBackgroundColor(GarasiTD[24], 255);
    TextDrawFont(GarasiTD[24], 4);
    TextDrawSetProportional(GarasiTD[24], 1);
    TextDrawSetSelectable(GarasiTD[24], 1);

    GarasiTD[25] = TextDrawCreate(541.000, 186.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[25], 56.000, 53.000);
    TextDrawAlignment(GarasiTD[25], 1);
    TextDrawColor(GarasiTD[25], -126);
    TextDrawSetShadow(GarasiTD[25], 0);
    TextDrawSetOutline(GarasiTD[25], 0);
    TextDrawBackgroundColor(GarasiTD[25], 255);
    TextDrawFont(GarasiTD[25], 4);
    TextDrawSetProportional(GarasiTD[25], 1);
    TextDrawSetSelectable(GarasiTD[25], 1);

    GarasiTD[26] = TextDrawCreate(468.000, 266.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[26], 56.000, 53.000);
    TextDrawAlignment(GarasiTD[26], 1);
    TextDrawColor(GarasiTD[26], -126);
    TextDrawSetShadow(GarasiTD[26], 0);
    TextDrawSetOutline(GarasiTD[26], 0);
    TextDrawBackgroundColor(GarasiTD[26], 255);
    TextDrawFont(GarasiTD[26], 4);
    TextDrawSetProportional(GarasiTD[26], 1);
    TextDrawSetSelectable(GarasiTD[26], 1);

    GarasiTD[27] = TextDrawCreate(541.000, 266.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[27], 56.000, 53.000);
    TextDrawAlignment(GarasiTD[27], 1);
    TextDrawColor(GarasiTD[27], -126);
    TextDrawSetShadow(GarasiTD[27], 0);
    TextDrawSetOutline(GarasiTD[27], 0);
    TextDrawBackgroundColor(GarasiTD[27], 255);
    TextDrawFont(GarasiTD[27], 4);
    TextDrawSetProportional(GarasiTD[27], 1);
    TextDrawSetSelectable(GarasiTD[27], 1);

    GarasiTD[28] = TextDrawCreate(468.000, 261.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[28], 56.000, 1.000);
    TextDrawAlignment(GarasiTD[28], 1);
    TextDrawColor(GarasiTD[28], -196921601);
    TextDrawSetShadow(GarasiTD[28], 0);
    TextDrawSetOutline(GarasiTD[28], 0);
    TextDrawBackgroundColor(GarasiTD[28], 255);
    TextDrawFont(GarasiTD[28], 4);
    TextDrawSetProportional(GarasiTD[28], 1);

    GarasiTD[29] = TextDrawCreate(541.000, 261.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[29], 56.000, 1.000);
    TextDrawAlignment(GarasiTD[29], 1);
    TextDrawColor(GarasiTD[29], -196921601);
    TextDrawSetShadow(GarasiTD[29], 0);
    TextDrawSetOutline(GarasiTD[29], 0);
    TextDrawBackgroundColor(GarasiTD[29], 255);
    TextDrawFont(GarasiTD[29], 4);
    TextDrawSetProportional(GarasiTD[29], 1);

    GarasiTD[30] = TextDrawCreate(469.000, 342.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[30], 56.000, 1.000);
    TextDrawAlignment(GarasiTD[30], 1);
    TextDrawColor(GarasiTD[30], -196921601);
    TextDrawSetShadow(GarasiTD[30], 0);
    TextDrawSetOutline(GarasiTD[30], 0);
    TextDrawBackgroundColor(GarasiTD[30], 255);
    TextDrawFont(GarasiTD[30], 4);
    TextDrawSetProportional(GarasiTD[30], 1);

    GarasiTD[31] = TextDrawCreate(541.000, 342.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[31], 56.000, 1.000);
    TextDrawAlignment(GarasiTD[31], 1);
    TextDrawColor(GarasiTD[31], -196921601);
    TextDrawSetShadow(GarasiTD[31], 0);
    TextDrawSetOutline(GarasiTD[31], 0);
    TextDrawBackgroundColor(GarasiTD[31], 255);
    TextDrawFont(GarasiTD[31], 4);
    TextDrawSetProportional(GarasiTD[31], 1);

    GarasiTD[32] = TextDrawCreate(467.000, 241.000, "Supra MK4");
    TextDrawLetterSize(GarasiTD[32], 0.187, 1.199);
    TextDrawAlignment(GarasiTD[32], 1);
    TextDrawColor(GarasiTD[32], -196921601);
    TextDrawSetShadow(GarasiTD[32], 0);
    TextDrawSetOutline(GarasiTD[32], 0);
    TextDrawBackgroundColor(GarasiTD[32], 150);
    TextDrawFont(GarasiTD[32], 1);
    TextDrawSetProportional(GarasiTD[32], 1);

    GarasiTD[33] = TextDrawCreate(467.000, 252.000, "Stored");
    TextDrawLetterSize(GarasiTD[33], 0.150, 0.898);
    TextDrawAlignment(GarasiTD[33], 1);
    TextDrawColor(GarasiTD[33], -196921601);
    TextDrawSetShadow(GarasiTD[33], 0);
    TextDrawSetOutline(GarasiTD[33], 0);
    TextDrawBackgroundColor(GarasiTD[33], 150);
    TextDrawFont(GarasiTD[33], 1);
    TextDrawSetProportional(GarasiTD[33], 1);

    GarasiTD[34] = TextDrawCreate(541.000, 241.000, "RX7");
    TextDrawLetterSize(GarasiTD[34], 0.187, 1.199);
    TextDrawAlignment(GarasiTD[34], 1);
    TextDrawColor(GarasiTD[34], -196921601);
    TextDrawSetShadow(GarasiTD[34], 0);
    TextDrawSetOutline(GarasiTD[34], 0);
    TextDrawBackgroundColor(GarasiTD[34], 150);
    TextDrawFont(GarasiTD[34], 1);
    TextDrawSetProportional(GarasiTD[34], 1);

    GarasiTD[35] = TextDrawCreate(541.000, 252.000, "Stored");
    TextDrawLetterSize(GarasiTD[35], 0.150, 0.898);
    TextDrawAlignment(GarasiTD[35], 1);
    TextDrawColor(GarasiTD[35], -196921601);
    TextDrawSetShadow(GarasiTD[35], 0);
    TextDrawSetOutline(GarasiTD[35], 0);
    TextDrawBackgroundColor(GarasiTD[35], 150);
    TextDrawFont(GarasiTD[35], 1);
    TextDrawSetProportional(GarasiTD[35], 1);

    GarasiTD[36] = TextDrawCreate(468.000, 320.000, "BMW E46");
    TextDrawLetterSize(GarasiTD[36], 0.187, 1.199);
    TextDrawAlignment(GarasiTD[36], 1);
    TextDrawColor(GarasiTD[36], -196921601);
    TextDrawSetShadow(GarasiTD[36], 0);
    TextDrawSetOutline(GarasiTD[36], 0);
    TextDrawBackgroundColor(GarasiTD[36], 150);
    TextDrawFont(GarasiTD[36], 1);
    TextDrawSetProportional(GarasiTD[36], 1);

    GarasiTD[37] = TextDrawCreate(468.000, 331.000, "Stored");
    TextDrawLetterSize(GarasiTD[37], 0.150, 0.898);
    TextDrawAlignment(GarasiTD[37], 1);
    TextDrawColor(GarasiTD[37], -196921601);
    TextDrawSetShadow(GarasiTD[37], 0);
    TextDrawSetOutline(GarasiTD[37], 0);
    TextDrawBackgroundColor(GarasiTD[37], 150);
    TextDrawFont(GarasiTD[37], 1);
    TextDrawSetProportional(GarasiTD[37], 1);

    GarasiTD[38] = TextDrawCreate(541.000, 320.000, "GTR 34");
    TextDrawLetterSize(GarasiTD[38], 0.187, 1.199);
    TextDrawAlignment(GarasiTD[38], 1);
    TextDrawColor(GarasiTD[38], -196921601);
    TextDrawSetShadow(GarasiTD[38], 0);
    TextDrawSetOutline(GarasiTD[38], 0);
    TextDrawBackgroundColor(GarasiTD[38], 150);
    TextDrawFont(GarasiTD[38], 1);
    TextDrawSetProportional(GarasiTD[38], 1);

    GarasiTD[39] = TextDrawCreate(541.000, 331.000, "Stored");
    TextDrawLetterSize(GarasiTD[39], 0.150, 0.898);
    TextDrawAlignment(GarasiTD[39], 1);
    TextDrawColor(GarasiTD[39], -196921601);
    TextDrawSetShadow(GarasiTD[39], 0);
    TextDrawSetOutline(GarasiTD[39], 0);
    TextDrawBackgroundColor(GarasiTD[39], 150);
    TextDrawFont(GarasiTD[39], 1);
    TextDrawSetProportional(GarasiTD[39], 1);

    GarasiTD[40] = TextDrawCreate(456.000, 221.000, "LD_BEAT:chit");
    TextDrawTextSize(GarasiTD[40], 79.000, 19.000);
    TextDrawAlignment(GarasiTD[40], 1);
    TextDrawColor(GarasiTD[40], -196921676);
    TextDrawSetShadow(GarasiTD[40], 0);
    TextDrawSetOutline(GarasiTD[40], 0);
    TextDrawBackgroundColor(GarasiTD[40], 255);
    TextDrawFont(GarasiTD[40], 4);
    TextDrawSetProportional(GarasiTD[40], 1);

    GarasiTD[41] = TextDrawCreate(530.000, 221.000, "LD_BEAT:chit");
    TextDrawTextSize(GarasiTD[41], 79.000, 19.000);
    TextDrawAlignment(GarasiTD[41], 1);
    TextDrawColor(GarasiTD[41], -196921676);
    TextDrawSetShadow(GarasiTD[41], 0);
    TextDrawSetOutline(GarasiTD[41], 0);
    TextDrawBackgroundColor(GarasiTD[41], 255);
    TextDrawFont(GarasiTD[41], 4);
    TextDrawSetProportional(GarasiTD[41], 1);

    GarasiTD[42] = TextDrawCreate(456.000, 301.000, "LD_BEAT:chit");
    TextDrawTextSize(GarasiTD[42], 79.000, 19.000);
    TextDrawAlignment(GarasiTD[42], 1);
    TextDrawColor(GarasiTD[42], -196921676);
    TextDrawSetShadow(GarasiTD[42], 0);
    TextDrawSetOutline(GarasiTD[42], 0);
    TextDrawBackgroundColor(GarasiTD[42], 255);
    TextDrawFont(GarasiTD[42], 4);
    TextDrawSetProportional(GarasiTD[42], 1);

    GarasiTD[43] = TextDrawCreate(530.000, 301.000, "LD_BEAT:chit");
    TextDrawTextSize(GarasiTD[43], 79.000, 19.000);
    TextDrawAlignment(GarasiTD[43], 1);
    TextDrawColor(GarasiTD[43], -196921676);
    TextDrawSetShadow(GarasiTD[43], 0);
    TextDrawSetOutline(GarasiTD[43], 0);
    TextDrawBackgroundColor(GarasiTD[43], 255);
    TextDrawFont(GarasiTD[43], 4);
    TextDrawSetProportional(GarasiTD[43], 1);

    GarasiTD[44] = TextDrawCreate(461.000, 184.000, "_");
    TextDrawTextSize(GarasiTD[44], 71.000, 76.000);
    TextDrawAlignment(GarasiTD[44], 1);
    TextDrawColor(GarasiTD[44], -1);
    TextDrawSetShadow(GarasiTD[44], 0);
    TextDrawSetOutline(GarasiTD[44], 0);
    TextDrawBackgroundColor(GarasiTD[44], 0);
    TextDrawFont(GarasiTD[44], 5);
    TextDrawSetProportional(GarasiTD[44], 0);
    TextDrawSetPreviewModel(GarasiTD[44], 558);
    TextDrawSetPreviewRot(GarasiTD[44], -7.000, -2.000, -43.000, 1.000);
    TextDrawSetPreviewVehCol(GarasiTD[44], 0, 0);

    GarasiTD[45] = TextDrawCreate(470.000, 191.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[45], 9.000, 2.000);
    TextDrawAlignment(GarasiTD[45], 1);
    TextDrawColor(GarasiTD[45], -196921601);
    TextDrawSetShadow(GarasiTD[45], 0);
    TextDrawSetOutline(GarasiTD[45], 0);
    TextDrawBackgroundColor(GarasiTD[45], 255);
    TextDrawFont(GarasiTD[45], 4);
    TextDrawSetProportional(GarasiTD[45], 1);

    GarasiTD[46] = TextDrawCreate(469.000, 191.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[46], 2.000, 10.000);
    TextDrawAlignment(GarasiTD[46], 1);
    TextDrawColor(GarasiTD[46], -196921601);
    TextDrawSetShadow(GarasiTD[46], 0);
    TextDrawSetOutline(GarasiTD[46], 0);
    TextDrawBackgroundColor(GarasiTD[46], 255);
    TextDrawFont(GarasiTD[46], 4);
    TextDrawSetProportional(GarasiTD[46], 1);

    GarasiTD[47] = TextDrawCreate(536.000, 184.000, "_");
    TextDrawTextSize(GarasiTD[47], 71.000, 76.000);
    TextDrawAlignment(GarasiTD[47], 1);
    TextDrawColor(GarasiTD[47], -1);
    TextDrawSetShadow(GarasiTD[47], 0);
    TextDrawSetOutline(GarasiTD[47], 0);
    TextDrawBackgroundColor(GarasiTD[47], 0);
    TextDrawFont(GarasiTD[47], 5);
    TextDrawSetProportional(GarasiTD[47], 0);
    TextDrawSetPreviewModel(GarasiTD[47], 451);
    TextDrawSetPreviewRot(GarasiTD[47], -7.000, -2.000, -43.000, 1.000);
    TextDrawSetPreviewVehCol(GarasiTD[47], 0, 0);

    GarasiTD[48] = TextDrawCreate(545.000, 191.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[48], 9.000, 2.000);
    TextDrawAlignment(GarasiTD[48], 1);
    TextDrawColor(GarasiTD[48], -196921601);
    TextDrawSetShadow(GarasiTD[48], 0);
    TextDrawSetOutline(GarasiTD[48], 0);
    TextDrawBackgroundColor(GarasiTD[48], 255);
    TextDrawFont(GarasiTD[48], 4);
    TextDrawSetProportional(GarasiTD[48], 1);

    GarasiTD[49] = TextDrawCreate(544.000, 191.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[49], 2.000, 10.000);
    TextDrawAlignment(GarasiTD[49], 1);
    TextDrawColor(GarasiTD[49], -196921601);
    TextDrawSetShadow(GarasiTD[49], 0);
    TextDrawSetOutline(GarasiTD[49], 0);
    TextDrawBackgroundColor(GarasiTD[49], 255);
    TextDrawFont(GarasiTD[49], 4);
    TextDrawSetProportional(GarasiTD[49], 1);

    GarasiTD[50] = TextDrawCreate(462.000, 264.000, "_");
    TextDrawTextSize(GarasiTD[50], 71.000, 76.000);
    TextDrawAlignment(GarasiTD[50], 1);
    TextDrawColor(GarasiTD[50], -1);
    TextDrawSetShadow(GarasiTD[50], 0);
    TextDrawSetOutline(GarasiTD[50], 0);
    TextDrawBackgroundColor(GarasiTD[50], 0);
    TextDrawFont(GarasiTD[50], 5);
    TextDrawSetProportional(GarasiTD[50], 0);
    TextDrawSetPreviewModel(GarasiTD[50], 560);
    TextDrawSetPreviewRot(GarasiTD[50], -7.000, -2.000, -43.000, 1.000);
    TextDrawSetPreviewVehCol(GarasiTD[50], 0, 0);

    GarasiTD[51] = TextDrawCreate(471.000, 271.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[51], 9.000, 2.000);
    TextDrawAlignment(GarasiTD[51], 1);
    TextDrawColor(GarasiTD[51], -196921601);
    TextDrawSetShadow(GarasiTD[51], 0);
    TextDrawSetOutline(GarasiTD[51], 0);
    TextDrawBackgroundColor(GarasiTD[51], 255);
    TextDrawFont(GarasiTD[51], 4);
    TextDrawSetProportional(GarasiTD[51], 1);

    GarasiTD[52] = TextDrawCreate(470.000, 271.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[52], 2.000, 10.000);
    TextDrawAlignment(GarasiTD[52], 1);
    TextDrawColor(GarasiTD[52], -196921601);
    TextDrawSetShadow(GarasiTD[52], 0);
    TextDrawSetOutline(GarasiTD[52], 0);
    TextDrawBackgroundColor(GarasiTD[52], 255);
    TextDrawFont(GarasiTD[52], 4);
    TextDrawSetProportional(GarasiTD[52], 1);

    GarasiTD[53] = TextDrawCreate(536.000, 264.000, "_");
    TextDrawTextSize(GarasiTD[53], 71.000, 76.000);
    TextDrawAlignment(GarasiTD[53], 1);
    TextDrawColor(GarasiTD[53], -1);
    TextDrawSetShadow(GarasiTD[53], 0);
    TextDrawSetOutline(GarasiTD[53], 0);
    TextDrawBackgroundColor(GarasiTD[53], 0);
    TextDrawFont(GarasiTD[53], 5);
    TextDrawSetProportional(GarasiTD[53], 0);
    TextDrawSetPreviewModel(GarasiTD[53], 562);
    TextDrawSetPreviewRot(GarasiTD[53], -7.000, -2.000, -43.000, 1.000);
    TextDrawSetPreviewVehCol(GarasiTD[53], 0, 0);

    GarasiTD[54] = TextDrawCreate(545.000, 271.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[54], 9.000, 2.000);
    TextDrawAlignment(GarasiTD[54], 1);
    TextDrawColor(GarasiTD[54], -196921601);
    TextDrawSetShadow(GarasiTD[54], 0);
    TextDrawSetOutline(GarasiTD[54], 0);
    TextDrawBackgroundColor(GarasiTD[54], 255);
    TextDrawFont(GarasiTD[54], 4);
    TextDrawSetProportional(GarasiTD[54], 1);

    GarasiTD[55] = TextDrawCreate(545.000, 271.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[55], 2.000, 10.000);
    TextDrawAlignment(GarasiTD[55], 1);
    TextDrawColor(GarasiTD[55], -196921601);
    TextDrawSetShadow(GarasiTD[55], 0);
    TextDrawSetOutline(GarasiTD[55], 0);
    TextDrawBackgroundColor(GarasiTD[55], 255);
    TextDrawFont(GarasiTD[55], 4);
    TextDrawSetProportional(GarasiTD[55], 1);

    GarasiTD[56] = TextDrawCreate(17.000, 144.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[56], 118.000, 169.000);
    TextDrawAlignment(GarasiTD[56], 1);
    TextDrawColor(GarasiTD[56], 5864447);
    TextDrawSetShadow(GarasiTD[56], 0);
    TextDrawSetOutline(GarasiTD[56], 0);
    TextDrawBackgroundColor(GarasiTD[56], 255);
    TextDrawFont(GarasiTD[56], 4);
    TextDrawSetProportional(GarasiTD[56], 1);

    GarasiTD[57] = TextDrawCreate(10.000, 154.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[57], 132.000, 149.000);
    TextDrawAlignment(GarasiTD[57], 1);
    TextDrawColor(GarasiTD[57], 5864447);
    TextDrawSetShadow(GarasiTD[57], 0);
    TextDrawSetOutline(GarasiTD[57], 0);
    TextDrawBackgroundColor(GarasiTD[57], 255);
    TextDrawFont(GarasiTD[57], 4);
    TextDrawSetProportional(GarasiTD[57], 1);

    GarasiTD[58] = TextDrawCreate(6.000, 139.000, "LD_BEAT:chit");
    TextDrawTextSize(GarasiTD[58], 23.000, 30.000);
    TextDrawAlignment(GarasiTD[58], 1);
    TextDrawColor(GarasiTD[58], 5864447);
    TextDrawSetShadow(GarasiTD[58], 0);
    TextDrawSetOutline(GarasiTD[58], 0);
    TextDrawBackgroundColor(GarasiTD[58], 255);
    TextDrawFont(GarasiTD[58], 4);
    TextDrawSetProportional(GarasiTD[58], 1);

    GarasiTD[59] = TextDrawCreate(123.000, 139.000, "LD_BEAT:chit");
    TextDrawTextSize(GarasiTD[59], 23.000, 30.000);
    TextDrawAlignment(GarasiTD[59], 1);
    TextDrawColor(GarasiTD[59], 5864447);
    TextDrawSetShadow(GarasiTD[59], 0);
    TextDrawSetOutline(GarasiTD[59], 0);
    TextDrawBackgroundColor(GarasiTD[59], 255);
    TextDrawFont(GarasiTD[59], 4);
    TextDrawSetProportional(GarasiTD[59], 1);

    GarasiTD[60] = TextDrawCreate(123.000, 288.000, "LD_BEAT:chit");
    TextDrawTextSize(GarasiTD[60], 23.000, 30.000);
    TextDrawAlignment(GarasiTD[60], 1);
    TextDrawColor(GarasiTD[60], 5864447);
    TextDrawSetShadow(GarasiTD[60], 0);
    TextDrawSetOutline(GarasiTD[60], 0);
    TextDrawBackgroundColor(GarasiTD[60], 255);
    TextDrawFont(GarasiTD[60], 4);
    TextDrawSetProportional(GarasiTD[60], 1);

    GarasiTD[61] = TextDrawCreate(6.000, 288.000, "LD_BEAT:chit");
    TextDrawTextSize(GarasiTD[61], 23.000, 30.000);
    TextDrawAlignment(GarasiTD[61], 1);
    TextDrawColor(GarasiTD[61], 5864447);
    TextDrawSetShadow(GarasiTD[61], 0);
    TextDrawSetOutline(GarasiTD[61], 0);
    TextDrawBackgroundColor(GarasiTD[61], 255);
    TextDrawFont(GarasiTD[61], 4);
    TextDrawSetProportional(GarasiTD[61], 1);

    GarasiTD[62] = TextDrawCreate(22.000, 198.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[62], -1.000, 101.000);
    TextDrawAlignment(GarasiTD[62], 1);
    TextDrawColor(GarasiTD[62], -1);
    TextDrawSetShadow(GarasiTD[62], 0);
    TextDrawSetOutline(GarasiTD[62], 0);
    TextDrawBackgroundColor(GarasiTD[62], 255);
    TextDrawFont(GarasiTD[62], 4);
    TextDrawSetProportional(GarasiTD[62], 1);

    GarasiTD[63] = TextDrawCreate(22.000, 198.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[63], 108.000, 1.000);
    TextDrawAlignment(GarasiTD[63], 1);
    TextDrawColor(GarasiTD[63], -1);
    TextDrawSetShadow(GarasiTD[63], 0);
    TextDrawSetOutline(GarasiTD[63], 0);
    TextDrawBackgroundColor(GarasiTD[63], 255);
    TextDrawFont(GarasiTD[63], 4);
    TextDrawSetProportional(GarasiTD[63], 1);

    GarasiTD[64] = TextDrawCreate(131.000, 198.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[64], -1.000, 101.000);
    TextDrawAlignment(GarasiTD[64], 1);
    TextDrawColor(GarasiTD[64], -1);
    TextDrawSetShadow(GarasiTD[64], 0);
    TextDrawSetOutline(GarasiTD[64], 0);
    TextDrawBackgroundColor(GarasiTD[64], 255);
    TextDrawFont(GarasiTD[64], 4);
    TextDrawSetProportional(GarasiTD[64], 1);

    GarasiTD[65] = TextDrawCreate(22.000, 298.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[65], 108.000, 1.000);
    TextDrawAlignment(GarasiTD[65], 1);
    TextDrawColor(GarasiTD[65], -1);
    TextDrawSetShadow(GarasiTD[65], 0);
    TextDrawSetOutline(GarasiTD[65], 0);
    TextDrawBackgroundColor(GarasiTD[65], 255);
    TextDrawFont(GarasiTD[65], 4);
    TextDrawSetProportional(GarasiTD[65], 1);

    GarasiTD[66] = TextDrawCreate(16.000, 147.000, "Pilih Kendaran");
    TextDrawLetterSize(GarasiTD[66], 0.150, 0.898);
    TextDrawAlignment(GarasiTD[66], 1);
    TextDrawColor(GarasiTD[66], -16776961);
    TextDrawSetShadow(GarasiTD[66], 0);
    TextDrawSetOutline(GarasiTD[66], 0);
    TextDrawBackgroundColor(GarasiTD[66], 150);
    TextDrawFont(GarasiTD[66], 1);
    TextDrawSetProportional(GarasiTD[66], 1);

    GarasiTD[67] = TextDrawCreate(17.000, 156.000, "Details");
    TextDrawLetterSize(GarasiTD[67], 0.289, 2.197);
    TextDrawAlignment(GarasiTD[67], 1);
    TextDrawColor(GarasiTD[67], -16776961);
    TextDrawSetShadow(GarasiTD[67], 0);
    TextDrawSetOutline(GarasiTD[67], 0);
    TextDrawBackgroundColor(GarasiTD[67], 150);
    TextDrawFont(GarasiTD[67], 1);
    TextDrawSetProportional(GarasiTD[67], 1);

    GarasiTD[68] = TextDrawCreate(24.000, 205.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[68], 104.000, 18.000);
    TextDrawAlignment(GarasiTD[68], 1);
    TextDrawColor(GarasiTD[68], -83);
    TextDrawSetShadow(GarasiTD[68], 0);
    TextDrawSetOutline(GarasiTD[68], 0);
    TextDrawBackgroundColor(GarasiTD[68], 255);
    TextDrawFont(GarasiTD[68], 4);
    TextDrawSetProportional(GarasiTD[68], 1);
    TextDrawSetSelectable(GarasiTD[68], 1);

    GarasiTD[69] = TextDrawCreate(75.000, 209.000, "TAKE OUT");
    TextDrawLetterSize(GarasiTD[69], 0.150, 0.898);
    TextDrawAlignment(GarasiTD[69], 2);
    TextDrawColor(GarasiTD[69], -16776961);
    TextDrawSetShadow(GarasiTD[69], 0);
    TextDrawSetOutline(GarasiTD[69], 0);
    TextDrawBackgroundColor(GarasiTD[69], 150);
    TextDrawFont(GarasiTD[69], 1);
    TextDrawSetProportional(GarasiTD[69], 1);

    GarasiTD[70] = TextDrawCreate(24.000, 227.000, "LD_SPAC:white");
    TextDrawTextSize(GarasiTD[70], 104.000, 22.000);
    TextDrawAlignment(GarasiTD[70], 1);
    TextDrawColor(GarasiTD[70], -83);
    TextDrawSetShadow(GarasiTD[70], 0);
    TextDrawSetOutline(GarasiTD[70], 0);
    TextDrawBackgroundColor(GarasiTD[70], 255);
    TextDrawFont(GarasiTD[70], 4);
    TextDrawSetProportional(GarasiTD[70], 1);

    GarasiTD[71] = TextDrawCreate(54.000, 230.000, "STATUS VEHICLE");
    TextDrawLetterSize(GarasiTD[71], 0.167, 0.898);
    TextDrawAlignment(GarasiTD[71], 1);
    TextDrawColor(GarasiTD[71], -16776961);
    TextDrawSetShadow(GarasiTD[71], 0);
    TextDrawSetOutline(GarasiTD[71], 0);
    TextDrawBackgroundColor(GarasiTD[71], 150);
    TextDrawFont(GarasiTD[71], 1);
    TextDrawSetProportional(GarasiTD[71], 1);

    GarasiTD[72] = TextDrawCreate(35.000, 239.000, "Stored - Fuel : 100 - Body : 1000");
    TextDrawLetterSize(GarasiTD[72], 0.137, 0.799);
    TextDrawAlignment(GarasiTD[72], 1);
    TextDrawColor(GarasiTD[72], -16776961);
    TextDrawSetShadow(GarasiTD[72], 0);
    TextDrawSetOutline(GarasiTD[72], 0);
    TextDrawBackgroundColor(GarasiTD[72], 150);
    TextDrawFont(GarasiTD[72], 1);
    TextDrawSetProportional(GarasiTD[72], 1);
}

hook OnPlayerConnect(playerid)
{
	CreateGarasiTD();
	return 1;
}

hook OnPlayerDisconnect(playerid)
{
	if(IsValidVehicle(PreviewVehicle[playerid]))
	{
		printf("DEBUG: menghancurkan kendaraan preview ID: %d untuk player %d", PreviewVehicle[playerid], playerid);
		DestroyVehicle(PreviewVehicle[playerid]);
		PreviewVehicle[playerid] = INVALID_VEHICLE_ID;
	}
	if (PlayerCameraTimer[playerid] > 0) // Tambahkan ini
	{
		KillTimer(PlayerCameraTimer[playerid]);
		PlayerCameraTimer[playerid] = 0;
	}
	return 1;
}

hook OnGameModeExitEx()
{
	for(new b = 0; b < 73; b++)
	{
		TextDrawDestroy(GarasiTD[b]);
	}
	for(new i = 0; i < 84; i++)
	{
		TextDrawDestroy(ClothesHapp[i]);
	}
	return 1;
}

forward RotateCameraAroundVehicle(playerid);
public RotateCameraAroundVehicle(playerid)
{
    new Float:x, Float:y, Float:z;
    GetVehiclePos(PreviewVehicle[playerid], x, y, z);

    CameraRotation[playerid] += 1.5;
    if (CameraRotation[playerid] >= 360.0) CameraRotation[playerid] = 0.0;

    new Float:ccamX = x + (7.0 * floatsin(CameraRotation[playerid], degrees));
    new Float:ccamY = y + (7.0 * floatcos(CameraRotation[playerid], degrees));
    new Float:ccamZ = z + 2.0;

    SetPlayerCameraPos(playerid, ccamX, ccamY, ccamZ);
    SetPlayerCameraLookAt(playerid, x, y, z);
    return 1;
}
