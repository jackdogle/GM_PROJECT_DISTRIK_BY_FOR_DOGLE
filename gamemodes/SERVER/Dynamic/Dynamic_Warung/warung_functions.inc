#include <YSI\y_hooks>
#define MAX_WARUNG 50

enum 	e_warung
{
	warungType,
	Float:warungPOS[3],
	warungInterior,
	warungWorld,

	STREAMER_TAG_MAP_ICON:warungMap,
	STREAMER_TAG_PICKUP:warungPickup,
	STREAMER_TAG_3D_TEXT_LABEL:warungLabel,
};

new WarungData[MAX_WARUNG][e_warung],
	Iterator:Warung<MAX_WARUNG>;

Warung_Refresh(id)
{
	if(id != -1)
	{
		if(DestroyDynamic3DTextLabel(WarungData[id][warungLabel]))
			WarungData[id][warungLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
		
		if(DestroyDynamicPickup(WarungData[id][warungPickup]))
			WarungData[id][warungPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

		if(DestroyDynamicMapIcon(WarungData[id][warungMap]))
			WarungData[id][warungMap] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;

		if(WarungData[id][warungType] == 1) // shop
		{
			WarungData[id][warungLabel] = CreateDynamic3DTextLabel("Tekan "GREEN"[Y]"WHITE" untuk membeli", -1, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2] + 0.55, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, WarungData[id][warungWorld], WarungData[id][warungInterior]);
			WarungData[id][warungMap] = CreateDynamicMapIcon(WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], 17, -1, WarungData[id][warungWorld], WarungData[id][warungInterior], -1, 1500.0, MAPICON_LOCAL, -1, 1);
			WarungData[id][warungPickup] = CreateDynamicPickup(2992, 23, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], WarungData[id][warungWorld], WarungData[id][warungInterior], -1, 2.5, -1, 0);
		}
		else if(WarungData[id][warungType] == 2) // elektronik
		{
			WarungData[id][warungLabel] = CreateDynamic3DTextLabel("Tekan "GREEN"[Y]"WHITE" untuk membeli", -1, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2] + 0.55, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, WarungData[id][warungWorld], WarungData[id][warungInterior]);
			WarungData[id][warungMap] = CreateDynamicMapIcon(WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], 48, -1, WarungData[id][warungWorld], WarungData[id][warungInterior], -1, 1500.0, MAPICON_LOCAL, -1, 1);
			WarungData[id][warungPickup] = CreateDynamicPickup(1277, 23, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], WarungData[id][warungWorld], WarungData[id][warungInterior], -1, 2.5, -1, 0);
		}
		else if(WarungData[id][warungType] == 3) // baju
		{
			WarungData[id][warungLabel] = CreateDynamic3DTextLabel("Tekan "GREEN"[Y]"WHITE" untuk membeli pakaian", -1, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2] + 0.55, 4.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, WarungData[id][warungWorld], WarungData[id][warungInterior]);
			WarungData[id][warungMap] = CreateDynamicMapIcon(WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], 45, -1, WarungData[id][warungWorld], WarungData[id][warungInterior], -1, 1500.0, MAPICON_LOCAL, -1, 1);
			WarungData[id][warungPickup] = CreateDynamicPickup(1275, 23, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], WarungData[id][warungWorld], WarungData[id][warungInterior], -1, 3.0, -1, 0);
		}
	}
	return 1;
}

Warung_Nearest(playerid)
{
	foreach(new i : Warung) if (IsPlayerInRangeOfPoint(playerid, 3.0, WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2]))
	{
		return i;
	}
	return -1;
}

/*WarungNearby(playerid)
{
	foreach(new i : Warung) if (WarungData[i][warungType] == 1)
	{
		static Float:X, Float:Y, Float:Z, Float:dist;
		GetPlayerPos(playerid, X, Y, Z);

		dist = GetDistanceBetweenPoints(WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2], X, Y, Z);

		if(dist <= 350.0)
		{
			return i;
		}
	}
	return -1;
}*/

/*ClothesStoreNearby(playerid)
{
	foreach(new i : Warung) if (WarungData[i][warungType] == 3)
	{
		static Float:X, Float:Y, Float:Z, Float:dist;
		GetPlayerPos(playerid, X, Y, Z);

		dist = GetDistanceBetweenPoints(WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2], X, Y, Z);

		if(dist <= 350.0)
		{
			return i;
		}
	}
	return -1;
}

ElectronicStoreNearby(playerid)
{
	foreach(new i : Warung) if (WarungData[i][warungType] == 2)
	{
		static Float:X, Float:Y, Float:Z, Float:dist;
		GetPlayerPos(playerid, X, Y, Z);

		dist = GetDistanceBetweenPoints(WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2], X, Y, Z);

		if(dist <= 350.0)
		{
			return i;
		}
	}
	return -1;
}*/

forward LoadWarung();
public LoadWarung()
{
	new id, rows = cache_num_rows();
	new Cache:Wrgcache;
	if(rows)
	{
		Wrgcache = cache_save();

		for(new i = 0; i < rows; i ++)
		{
			id = cache_get_field_int(i, "ShopID");
			WarungData[id][warungPOS][0] = cache_get_field_float(i, "ShopX");
			WarungData[id][warungPOS][1] = cache_get_field_float(i, "ShopY");
			WarungData[id][warungPOS][2] = cache_get_field_float(i, "ShopZ");
			WarungData[id][warungInterior] = cache_get_field_int(i, "ShopInterior");
			WarungData[id][warungWorld] = cache_get_field_int(i, "ShopWorld");
			WarungData[id][warungType] = cache_get_field_int(i, "ShopType");
			
			Warung_Refresh(id);
			Iter_Add(Warung, id);
		}
		printf("[Dynamic Warung]: Jumlah total Warung yang dimuat %d.", rows);
		if(cache_is_valid(Wrgcache))
        {
            cache_delete(Wrgcache);
            printf("[Dynamic Warung]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Warung]: Cache tidak valid atau sudah dihapus.");
        }
	}
	return 1;
}

Warung_Save(id)
{
	new cQuery[525];
	format(cQuery, sizeof(cQuery), "UPDATE `warung` SET \ 
	`ShopX` = %f, `ShopY` = %f, `ShopZ` = %f, `ShopInterior` = %d, `ShopWorld` = %d \ 
	WHERE `ShopID` = %d", WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], 
	WarungData[id][warungWorld], WarungData[id][warungInterior], id);
	return mysql_tquery(g_SQL, cQuery);
}

CMD:addwarung(playerid, params[])
{
	if(CheckAdmin(playerid, 6)) return PermissionError(playerid);

	new 
		id = Iter_Free(Warung),
		type,
		tss[525],
		Float:x,
		Float:y,
		Float:z
	;
	GetPlayerPos(playerid, x, y, z);

	if(sscanf(params, "d", type)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addshop [type]~n~1. Warung 2. Elektronik 3. Pakaian");
	if(type < 1 || type > 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Type!");
	if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menambah warung lagi!");

	if(type == 1) 
	{
		WarungData[id][warungPOS][0] = x;
		WarungData[id][warungPOS][1] = y;
		WarungData[id][warungPOS][2] = z;
		WarungData[id][warungType] = 1;
		WarungData[id][warungInterior] = GetPlayerInterior(playerid);
		WarungData[id][warungWorld] = GetPlayerVirtualWorld(playerid);

		Warung_Refresh(id);
		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah Membuat Dynamic Warung ID: %d", GetAdminName(playerid), id);
	}
	else if(type == 2)
	{
		WarungData[id][warungPOS][0] = x;
		WarungData[id][warungPOS][1] = y;
		WarungData[id][warungPOS][2] = z;
		WarungData[id][warungType] = 2;
		WarungData[id][warungInterior] = GetPlayerInterior(playerid);
		WarungData[id][warungWorld] = GetPlayerVirtualWorld(playerid);

		Warung_Refresh(id);
		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah Membuat Dynamic Warung Elektronik ID: %d", GetAdminName(playerid), id);
	}
	else if(type == 3)
	{
		WarungData[id][warungPOS][0] = x;
		WarungData[id][warungPOS][1] = y;
		WarungData[id][warungPOS][2] = z;
		WarungData[id][warungType] = 3;
		WarungData[id][warungInterior] = GetPlayerInterior(playerid);
		WarungData[id][warungWorld] = GetPlayerVirtualWorld(playerid);

		Warung_Refresh(id);
		SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Membuat Dynamic Toko Baju ID: %d", GetAdminName(playerid), id);
	}
	Iter_Add(Warung, id);

	mysql_format(g_SQL, tss, sizeof(tss), "INSERT INTO `warung` SET `ShopID`=%d, `ShopX`=%f, `ShopY`=%f, `ShopZ`=%f, `ShopInterior`=%d, `ShopWorld`=%d, `ShopType`=%d",
	id, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2], WarungData[id][warungInterior], WarungData[id][warungWorld], WarungData[id][warungType]);
	mysql_tquery(g_SQL, tss, "OnWarungCreated", "dd", playerid, id);
	return 1;
}

CMD:removewarung(playerid, params[])
{
	if(CheckAdmin(playerid, 6)) return PermissionError(playerid);

	new id, icsr[255];
	if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/removewarung [id]");
	if(!Iter_Contains(Warung, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Warung tidak ada!");
	if(id < 0 || id > MAX_WARUNG) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Warung tidak valid!");

	WarungData[id][warungPOS][0] = WarungData[id][warungPOS][1] = WarungData[id][warungPOS][2] = 0.0;
	WarungData[id][warungInterior] = WarungData[id][warungWorld] = WarungData[id][warungType] = 0;

	Warung_Refresh(id);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah Menghapus Dynamic Warung ID: %d", GetAdminName(playerid), id);

	Iter_Remove(Warung, id);
	mysql_format(g_SQL, icsr, sizeof(icsr), "DELETE FROM `warung` WHERE `ShopID` = %d", id);
	mysql_tquery(g_SQL, icsr);
	return 1;
}

CMD:gotowarung(playerid, params[])
{
	if(CheckAdmin(playerid, 6)) return PermissionError(playerid);

	new id;
	if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotowarung [id]");
	if(!Iter_Contains(Warung, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Warung tidak ada!");
	if(id < 0 || id > MAX_WARUNG) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Warung tidak valid!");

	SetPlayerPos(playerid, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2]);
	SetPlayerInterior(playerid, WarungData[id][warungInterior]);
	SetPlayerVirtualWorld(playerid, WarungData[id][warungWorld]);
	AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Teleportasi ke Warung ID:%d", GetAdminName(playerid), id);
	return 1;
}

forward OnWarungCreated(playerid, id);
public OnWarungCreated(playerid, id)
{
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membuat warung!");
	Warung_Save(id);
	return 1;
}

/* Hook */
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		new id = Warung_Nearest(playerid);
		if(id > -1)
		{
			if(IsPlayerInRangeOfPoint(playerid, 1.5, WarungData[id][warungPOS][0], WarungData[id][warungPOS][1], WarungData[id][warungPOS][2]))
			{
				if(WarungData[id][warungType] == 1)
				{
					ShowWarungTD(playerid, true);

					for(new i = 11; i < 22; i++)
						PlayerTextDrawHide(playerid, WarungTD[playerid][i]);

					new modelID[11] = {19567, 19570, 19896, 19998, 18632, 1603, 18979, 19036, 365, 18641, 19632};
					for(new i = 0; i < 11; i++)
					{
						PlayerTextDrawSetPreviewModel(playerid, WarungTD[playerid][11 + i], modelID[i]);
						PlayerTextDrawShow(playerid, WarungTD[playerid][11 + i]);
					}

					new stringItemName[11][32] = {
						"Nasi Uduk", "Air Mineral", "Rokok", "Korek Api", "Pancingan",
						"Umpan", "Helm", "Masker", "Pilox", "Senter", "Api Unggun"
					};
					for(new i = 0; i < 11; i++)
					{
						PlayerTextDrawSetString(playerid, WarungTD[playerid][35 + i], stringItemName[i]);
						PlayerTextDrawShow(playerid, WarungTD[playerid][35 + i]);
					}

					for(new i = 22; i < 28; i++)
						PlayerTextDrawHide(playerid, WarungTD[playerid][i]);

					PlayerTextDrawShow(playerid, WarungTD[playerid][22]);
					PlayerTextDrawShow(playerid, WarungTD[playerid][26]);
					for(new i = 0; i < 10; i++)
					{
						if(pUnselectWarungUse[playerid] != -1 && pUnselectWarungUse[playerid] != i)
						{
							PlayerTextDrawColor(playerid, WarungTD[playerid][pUnselectWarungUse[playerid]], 59);
							PlayerTextDrawShow(playerid, WarungTD[playerid][pUnselectWarungUse[playerid]]);
						}
					}
				}
				else if(WarungData[id][warungType] == 2)
				{
					ShowPlayerDialog(playerid, DIALOG_WARUNG_ELEKTRONIK, DIALOG_STYLE_TABLIST_HEADERS, sprintf(""TCRP"District  "WHITE"- Warung No.%02d", id),
					"Nama Item\tHarga\
					\nVervhone (Smartphone)\t$1800\
					\n"GRAY"Radio\t"GRAY"$950\
					\nEarphone\t$300\
					\n"GRAY"Boombox\t"GRAY"$500\
					\nRace Tablet\t"GRAY"$2000\
					\nRepair Kit\t$10000", "Pilih", "Batal");
				}
				else if(WarungData[id][warungType] == 3)
				{
					SetPlayerCameraFacingStore(playerid);
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
		case DIALOG_WARUNG_ELEKTRONIK:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
			switch(listitem)
			{
				case 0:
				{
					if(AccountData[playerid][pMoney] < 1800) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 1800);
					Inventory_Add(playerid, "Smartphone", 18870);
					ShowItemBox(playerid, "Received 1x", "Smartphone", 18870);
				}
				case 1:
				{
					if(AccountData[playerid][pMoney] < 950) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 950);
					Inventory_Add(playerid, "Radio", 19942);
					ShowItemBox(playerid, "Received 1x", "Radio", 19942);
					ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil");
				}
				case 2:
				{
					if(AccountData[playerid][pEarphone]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki earphone!"); 
					if(AccountData[playerid][pMoney] < 300) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 300);
					AccountData[playerid][pEarphone] = 1;
					ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil");
					new icsr[125];
					mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Earphone`=1 WHERE `pID`=%d", AccountData[playerid][pID]);
					mysql_tquery(g_SQL, icsr);
				}
				case 3:
				{
					if(AccountData[playerid][pVip] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pengguna VIP!");
					if(AccountData[playerid][pMoney] < 500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					if(PlayerHasItem(playerid, "Boombox")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki boombox!");
					TakeMoney(playerid, 500);
					Inventory_Add(playerid, "Boombox", 2103);
					ShowItemBox(playerid, "Received 1x", "Boombox", 2103);
				}
				case 4:
				{
					if(AccountData[playerid][pMoney] < 2000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					if(PlayerHasItem(playerid, "Race Tablet")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki Race Tablet!");
					TakeMoney(playerid, 2000);
					Inventory_Add(playerid, "Race Tablet", 19894);
					ShowItemBox(playerid, "Received 1x", "Race Tablet", 19894);
				}
				case 5:
				{
					if(AccountData[playerid][pMoney] < 10000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					Inventory_Add(playerid, "Repair Kit", 19918, 1); 
					
					TakeMoney(playerid, 10000);
					ShowItemBox(playerid, "Received 1x", "Repair Kit", 19918);
					ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil");
				}
			}
		}
		case DIALOG_WARUNG:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
			switch(listitem)
			{
				case 0: // nasi uduk
				{
					ShowPlayerDialog(playerid, DIALOG_BUY_NASIUDUK, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warung", 
					"Anda akan membeli nasi uduk seharga "GREEN"$250/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
				}
				case 1: //airmineral
				{
					ShowPlayerDialog(playerid, DIALOG_BUY_AIRMINERAL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warung", 
					"Anda akan membeli air mineral seharga "GREEN"$200/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
				}
				case 2: //Rokok
				{
					if(AccountData[playerid][pMoney] < 55) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 55);

					Inventory_Add(playerid, "Rokok", 19896, 12);
					ShowItemBox(playerid, "Received 12x", "Rokok", 19896);
				}
				case 3: //Korek api
				{
					if(AccountData[playerid][pMoney] < 150) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 150);

					Inventory_Add(playerid, "Korek Api", 19998);
					ShowItemBox(playerid, "Received 1x", "Korek Api", 19998);
				}
				case 4: // Pancingan
				{
					if(AccountData[playerid][pMoney] < 80) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 80);

					Inventory_Add(playerid, "Pancingan", 18632);
					ShowItemBox(playerid, "Received 1x", "Pancingan", 18632);
				}
				case 5: // Umpan
				{
					ShowPlayerDialog(playerid, DIALOG_BUY_UMPAN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warung", 
					"Anda akan membeli umpan seharga "GREEN"$18/umpan\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli)", "Beli", "Batal");
				}
				case 6: //Helm
				{
					if(AccountData[playerid][pHelmet]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki helm!");
					if(AccountData[playerid][pMoney] < 150) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 150);
					AccountData[playerid][pHelmet] = 1;
					ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil");	
				}
				case 7: // masker
				{
					if(AccountData[playerid][pMoney] < 650) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 650);

					Inventory_Add(playerid, "Masker", 19036);
					ShowItemBox(playerid, "Received 1x", "Masker", 19036);
				}
				case 8:
				{
					if(AccountData[playerid][pMoney] < 10000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 10000);

					Inventory_Add(playerid, "Pilox", 365);
					ShowItemBox(playerid, "Received 1x", "Pilox", 365);
				}
				case 9:
				{
					if(AccountData[playerid][pMoney] < 1000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 1000);

					Inventory_Add(playerid, "Senter", 18641);
					ShowItemBox(playerid, "Received 1x", "Senter", 18641);
				}
				case 10:
				{
					if(AccountData[playerid][pVip] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pengguna VIP!");
					if(AccountData[playerid][pMoney] < 2500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 2500);

					Inventory_Add(playerid, "Api Unggun", 19632);
					ShowItemBox(playerid, "Received 1x", "Api Unggun", 19632);
				}
			}
		}
		case DIALOG_BUY_NASIUDUK:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		
			if(isnull(inputtext))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_NASIUDUK, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warung",
				"Error: Tidak dapat diisi kosong!\nAnda akan membeli nasi uduk seharga "GREEN"$250/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}

			if(!IsNumeric(inputtext))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_NASIUDUK, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warung",
				"Error: Hanya dapat diisi angka!\nAnda akan membeli nasi uduk seharga "GREEN"$250/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}

			if(strval(inputtext) < 1 || strval(inputtext) > (strval(inputtext) * 250))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_NASIUDUK, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warung",
				"Error: Jumlah tidak valid!\nAnda akan membeli nasi uduk seharga "GREEN"$250/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}
			new quantity = strval(inputtext);
			new value = quantity * 250;

			if(value > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
			if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
			TakeMoney(playerid, value);

			Inventory_Add(playerid, "Nasi Uduk", 19567, quantity);
			ShowItemBox(playerid, sprintf("Received %dx", quantity), "Nasi Uduk", 19567);
		}
		case DIALOG_BUY_AIRMINERAL:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		
			if(isnull(inputtext))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_AIRMINERAL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warung",
				"Error: Tidak dapat diisi kosong!\nAnda akan membeli air mineral seharga "GREEN"$200/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}

			if(!IsNumeric(inputtext))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_AIRMINERAL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warung",
				"Error: Hanya dapat diisi angka!\nAnda akan membeli air mineral seharga "GREEN"$200/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}

			if(strval(inputtext) < 1 || strval(inputtext) > (strval(inputtext) * 200))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_AIRMINERAL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warung",
				"Error: Jumlah tidak valid!\nAnda akan membeli air mineral seharga "GREEN"$200/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}
			new quantity = strval(inputtext);
			new value = quantity * 200;

			if(value > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
			if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
			TakeMoney(playerid, value);

			Inventory_Add(playerid, "Air Mineral", 19570, quantity);
			ShowItemBox(playerid, sprintf("Received %dx", quantity), "Air Mineral", 19570);
		}
		case DIALOG_BUY_UMPAN:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
		
			if(isnull(inputtext))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_UMPAN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warung",
				"Error: Tidak dapat diisi kosong!\nAnda akan membeli umpan seharga "GREEN"$18/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}

			if(!IsNumeric(inputtext))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_UMPAN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warung",
				"Error: Hanya dapat diisi angka!\nAnda akan membeli umpan seharga "GREEN"$18/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}

			if(strval(inputtext) < 1 || strval(inputtext) > (strval(inputtext) * 18))
			{
				return ShowPlayerDialog(playerid, DIALOG_BUY_UMPAN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warung",
				"Error: Jumlah tidak valid!\nAnda akan membeli umpan seharga "GREEN"$18/pcs\n"YELLOW"(Masukkan berapa banyak yang ingin anda beli):", "Beli", "Batal");
			}
			new quantity = strval(inputtext);
			new value = quantity * 18;

			if(AccountData[playerid][pMoney] < value) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
			if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
			TakeMoney(playerid, value);

			Inventory_Add(playerid, "Umpan", 1603, quantity);
			ShowItemBox(playerid, sprintf("Received %dx", quantity), "Umpan", 1603);
		}
	}
	return 1;
}

ShowWarungTD(playerid, bool:Chess7)
{
	if(Chess7)
	{
		for(new i = 0; i < 46; i++)
		{
			PlayerTextDrawShow(playerid, WarungTD[playerid][i]);
			SelectTextDraw(playerid, COLOR_BLUE);
		}
	}
	else
	{
		for(new i = 0; i < 46; i++)
		{
			PlayerTextDrawHide(playerid, WarungTD[playerid][i]);
			CancelSelectTextDraw(playerid);
		}
	}
	return 1;
}

stock BuyProdukWarung(playerid, itemid)
{
	new harga = WarungHarga[itemid];
	if(harga > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");

	switch(itemid)
	{
		case 0:
		{
			if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
			TakeMoney(playerid, harga);

			Inventory_Add(playerid, "Nasi Uduk", 19567, 1);
			ShowItemBox(playerid, "Received 1x", "Nasi Uduk", 19567);
			Info(playerid, "Anda berhasil membeli nasi uduk 1");
			pSelectWarungUse[playerid] = -1;
			pUnselectWarungUse[playerid] = -1;
		}
		case 1:
		{
			if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
			TakeMoney(playerid, harga);

			Inventory_Add(playerid, "Air Mineral", 19570, 1);
			ShowItemBox(playerid, "Received 1x", "Air Mineral", 19570);
			Info(playerid, "Anda berhasil membeli air mineral 1");
			pSelectWarungUse[playerid] = -1;
			pUnselectWarungUse[playerid] = -1;
		}
		case 2:
		{
			TakeMoney(playerid, harga);
			Inventory_Add(playerid, "Rokok", 19896, 12);
			ShowItemBox(playerid, "Received 12x", "Rokok", 19896);
			Info(playerid, "Anda berhasil membeli Rokok 1");
			pSelectWarungUse[playerid] = -1;
			pUnselectWarungUse[playerid] = -1;
		}
		case 3:
		{
			TakeMoney(playerid, harga);
			Inventory_Add(playerid, "Korek Api", 19998);
			ShowItemBox(playerid, "Received 1x", "Korek Api", 19998);
			Info(playerid, "Anda berhasil membeli Korek Api 1");
			pSelectWarungUse[playerid] = -1;
			pUnselectWarungUse[playerid] = -1;
		}
		case 4:
		{
			TakeMoney(playerid, harga);
			Inventory_Add(playerid, "Pancingan", 18632);
			ShowItemBox(playerid, "Received 1x", "Pancingan", 18632);
			Info(playerid, "Anda berhasil membeli Pancingan 1");
			pSelectWarungUse[playerid] = -1;
			pUnselectWarungUse[playerid] = -1;
		}
		case 5:
		{
			if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
			TakeMoney(playerid, harga);

			Inventory_Add(playerid, "Umpan", 1603, 1);
			ShowItemBox(playerid, "Received 1x", "Umpan", 1603);
			Info(playerid, "Anda berhasil membeli Umpan 1");
			pSelectWarungUse[playerid] = -1;
			pUnselectWarungUse[playerid] = -1;
		}
		case 6:
		{
			if(AccountData[playerid][pHelmet]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki helm!");
			TakeMoney(playerid, harga);
			AccountData[playerid][pHelmet] = 1;
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil");	
			Info(playerid, "Anda berhasil membeli Helm");
			pSelectWarungUse[playerid] = -1;
			pUnselectWarungUse[playerid] = -1;
		}
		case 7:
		{
			TakeMoney(playerid, harga);
			Inventory_Add(playerid, "Masker", 19036);
			ShowItemBox(playerid, "Received 1x", "Masker", 19036);
			Info(playerid, "Anda berhasil membeli masker");
			pSelectWarungUse[playerid] = -1;
			pUnselectWarungUse[playerid] = -1;
		}
		case 8:
		{
			TakeMoney(playerid, harga);
			Inventory_Add(playerid, "Pilox", 365);
			ShowItemBox(playerid, "Received 1x", "Pilox", 365);
			Info(playerid, "Anda berhasil membeli Pilox");
			pSelectWarungUse[playerid] = -1;
			pUnselectWarungUse[playerid] = -1;
		}
		case 9:
		{
			TakeMoney(playerid, 1000);
			Inventory_Add(playerid, "Senter", 18641);
			ShowItemBox(playerid, "Received 1x", "Senter", 18641);
			Info(playerid, "Anda berhasil membeli Senter");
			pSelectWarungUse[playerid] = -1;
			pUnselectWarungUse[playerid] = -1;
		}
		case 10:
		{
			if(AccountData[playerid][pVip] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pengguna VIP!");
			TakeMoney(playerid, harga);

			Inventory_Add(playerid, "Api Unggun", 19632);
			ShowItemBox(playerid, "Received 1x", "Api Unggun", 19632);
			Info(playerid, "Anda berhasil membeli Api Unggun");
			pSelectWarungUse[playerid] = -1;
			pUnselectWarungUse[playerid] = -1;
		}
	}
	return 1;
}

forward FinishRepairKit(playerid, vehicleid);
public FinishRepairKit(playerid, vehicleid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pUseItemTimer[playerid]);
        pUseItemTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(AccountData[playerid][pInjured] || !IsValidVehicle(vehicleid))
    {
        KillTimer(pUseItemTimer[playerid]);
        pUseItemTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        ClearAnimations(playerid, 1);
        
        new engine, lights, alarm, doors, bonnet, boot, objective;
        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
        SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, 0, boot, objective);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 5)
    {
        KillTimer(pUseItemTimer[playerid]);
        pUseItemTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        ClearAnimations(playerid, 1);

        RepairVehicle(vehicleid);
        SetVehicleHealth(vehicleid, 1000.0);

        new engine, lights, alarm, doors, bonnet, boot, objective;
        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
        SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, 0, boot, objective);

        Inventory_Remove(playerid, "Repair Kit", 1);
        ShowItemBox(playerid, "Removed 1x", "Repair Kit", 19918);
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Kendaraan diperbaiki!");
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/5; 
        
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}