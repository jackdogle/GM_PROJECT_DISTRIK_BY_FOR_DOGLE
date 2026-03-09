Dialog:HouseSpawn_Option(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		ShowPlayerDialog(playerid, DIALOG_SELECT_SPAWNEXPIRED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Pilih Lokasi Spawn",
		"Titik Spawn\tDetail\tLokasi\
		\nBandara International\tAnda akan spawn di bandara\tLos Santos\
		\nLast Exit\tAnda akan spawn di Tempat Akhir\tOcean Docs\
		\nBandara Las Venturas\tAnda akan spawn di bandara\tLas Venturas\
		\nCarnaval\tAnda akan spawn di wahana carnaval\tSanta Maria Beach\
		\nHouse\tAnda akan spawn didepan rumah milik anda\t-\
		\nRusun\tAnda akan spawn didepan motel sewaan anda\t-", "Pilih", "");
		return 1;
	}
	if(response)
	{
		switch(listitem)
		{
			case 0: // Pribadi
			{
				foreach(new i : House)
				{
					if(HouseData[i][hsOwnerID] == AccountData[playerid][pID] && !strcmp(HouseData[i][hsOwner], AccountData[playerid][pName], true))
					{
						AccountData[playerid][pPosX] = HouseData[i][hsExtPos][0];
						AccountData[playerid][pPosY] = HouseData[i][hsExtPos][1];
						AccountData[playerid][pPosZ] = HouseData[i][hsExtPos][2];
						AccountData[playerid][pPosA] = HouseData[i][hsExtPos][3];
						SetPlayerInteriorEx(playerid, 0);
						SetPlayerVirtualWorldEx(playerid, 0);

						SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 6000);
					}
				}
			}
			case 1: // Numpang
			{
				foreach(new i : House)
				{
					if(AccountData[playerid][pFriendHouseID] == i)
					{
						AccountData[playerid][pPosX] = HouseData[i][hsExtPos][0];
						AccountData[playerid][pPosY] = HouseData[i][hsExtPos][1];
						AccountData[playerid][pPosZ] = HouseData[i][hsExtPos][2];
						AccountData[playerid][pPosA] = HouseData[i][hsExtPos][3];
						SetPlayerInteriorEx(playerid, 0);
						SetPlayerVirtualWorldEx(playerid, 0);

						SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 6000);
					}
				}
			}
		}
	}
	return 1;
}

Dialog:DialogGpsClothes(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new count = 0;
        for(new i = 0; i < MAX_WARUNG; i++)
        {
            if(WarungData[i][warungType] == 3) // type 3 = toko baju
            {
                if(count == listitem)
                {
                    SetPlayerRaceCheckpoint(playerid, 1, WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2], 0.0, 0.0, 0.0, 5.0);
                    Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda!");
					
					//(playerid,  WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2], COLOR_BLUE);
                    break;
                }
                count++;
            }
        }
    }
    return 1;
}

Dialog:DialogGpsShop(playerid, response, listitem, inputtext[])
{
	if(response)
    {
        new count = 0;
        for(new i = 0; i < MAX_WARUNG; i++)
        {
            if(WarungData[i][warungType] == 1) // type 2 = toko shop
            {
                if(count == listitem)
                {
                    SetPlayerRaceCheckpoint(playerid, 1, WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2], 0.0, 0.0, 0.0, 5.0);
                    Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda!");
					
					//(playerid,  WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2], COLOR_BLUE);
                    break;
                }
                count++;
            }
        }
    }
    return 1;
}

Dialog:DialogGpsElek(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new count = 0;
        for(new i = 0; i < MAX_WARUNG; i++)
        {
            if(WarungData[i][warungType] == 2) // type 2 = toko elektronik
            {
                if(count == listitem)
                {
                    SetPlayerRaceCheckpoint(playerid, 1, WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2], 0.0, 0.0, 0.0, 5.0);
                    Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda!");
					
					//(playerid,  WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2], COLOR_BLUE);
                    break;
                }
                count++;
            }
        }
    }
    return 1;
}

Dialog:DialogGpsAtm(playerid, response, listitem, inputtext[])
{
	if(response)
	{
	    new id = listitem;

        SetPlayerRaceCheckpoint(playerid, 1, AtmData[id][atmX], AtmData[id][atmY], AtmData[id][atmZ], 0.0, 0.0, 0.0, 5.0);
		Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda!");	
		
		//(playerid,  AtmData[id][atmX], AtmData[id][atmY], AtmData[id][atmZ], COLOR_BLUE);
	}
    return 1;
}

Dialog:DialogGpsTrash(playerid, response, listitem, inputtext[])
{
	if(response)
	{
	    new id = listitem;

        SetPlayerRaceCheckpoint(playerid, 1, TrashData[id][trashPos][0], TrashData[id][trashPos][1], TrashData[id][trashPos][2], 0.0, 0.0, 0.0, 5.0);
		Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda!");	
		
		//(playerid,  TrashData[id][trashPos][0], TrashData[id][trashPos][1], TrashData[id][trashPos][2], COLOR_BLUE);
	}
    return 1;
}

Dialog:DialogGpsGarasi(playerid, response, listitem, inputtext[])
{
    if(response)
	{
	    new id = listitem;

        SetPlayerRaceCheckpoint(playerid, 1, PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2], 0.0, 0.0, 0.0, 5.0);
		Info(playerid, "Silahkan ikuti tanda blip yang sudah ditandai pada map anda!");	
		
		//(playerid,  PublicGarage[id][pgPOS][0], PublicGarage[id][pgPOS][1], PublicGarage[id][pgPOS][2], COLOR_BLUE);
	}
    return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	printf("[OnDialogResponse]: %s(%d) has used dialog id: %d Listitem: %d", AccountData[playerid][pUCP], playerid, dialogid, listitem);
	if(dialogid == DIALOG_REGISTER)
    {
		if (!response) return Kick(playerid);
	
		if (strlen(inputtext) <= 5) return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Register - "TCRP"District ", ""WHITE"Buatlah kata sandi anda dengan benar\n"WHITE"NOTE: Kata sandi minimal 5 Karakter!\n\n"YELLOW"(Mohon isi dan selalu ingat Password anda di bawah ini):", "Register", "Tolak");
		
		if(!IsValidPassword(inputtext))
		{
			Error(playerid, "Sandi valid : A-Z, a-z, 0-9, _, [ ], ( )");
			ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Register - "TCRP"District ", ""WHITE"Kata sandi yang anda gunakan mengandung karakter yang tidak valid!\n\n"YELLOW"(Mohon isi dan selalu ingat Password anda di bawah ini):", "Register", "Tolak");
			return 1;
		}
		
		for (new i = 0; i < 16; i++) AccountData[playerid][pSalt][i] = random(94) + 33;
		SHA256_PassHash(inputtext, AccountData[playerid][pSalt], AccountData[playerid][pPassword], 65);

		new query[842], PlayerIP[16];
		GetPlayerIp(playerid, PlayerIP, sizeof(PlayerIP));
		AccountData[playerid][pExtraChar] = 0;
		mysql_format(g_SQL, query, sizeof query, "UPDATE playerucp SET password = '%s', salt = '%e', extrac = '%d' WHERE ucp = '%e'", AccountData[playerid][pPassword], AccountData[playerid][pSalt], AccountData[playerid][pExtraChar], AccountData[playerid][pUCP]);
		mysql_tquery(g_SQL, query, "CheckCharacters", "d", playerid);
		return 1;
	}
	if(dialogid == DIALOG_LOGIN)
	{
		if(!response) return KickEx(playerid);
		
		new hashed_pass[65], frmxtdialog[598];
		SHA256_PassHash(inputtext, AccountData[playerid][pSalt], hashed_pass, 65);

		SetPVarInt(playerid, "UCPBlacklist", 1);

		if (strcmp(hashed_pass, AccountData[playerid][pPassword]) == 0)
		{
			if(!Blacklist_Check(playerid, "name", AccountData[playerid][pUCP])) {
				CheckCharacters(playerid);
				DeletePVar(playerid, "UCPBlacklist");
				Info(playerid, "Sistem kami berhasil memproses akun anda. Silahkan pilih karakter yang akan dimainkan");
			}
		}
		else
		{
			LoginAttemps[playerid] ++;

			if(LoginAttemps[playerid] >= 3)
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "UCP - Login", "Kata Sandi yang anda masukkan salah!\n\n"YELLOW"Anda ditendang dari server!", "Keluar", "");
				KickEx(playerid);
			}
			else
			{
				format(frmxtdialog, sizeof(frmxtdialog), ""WHITE"Selamat datang di "TCRP"District \n"RED"Error: Kata Sandi Salah! Kesempatan Login %d/3\n"WHITE"UCP ini telah terdaftar!\nNama UCP: "LIGHTGREEN"%s\
				\n"WHITE"Version: "TCRP""TEXT_GAMEMODE"\n"YELLOW"(Silahkan masukkan kata sandi anda untuk login):", LoginAttemps[playerid], AccountData[playerid][pUCP]);
				ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "UCP - Login", frmxtdialog, "Input", "Keluar");
			}
		}
	}
	if(dialogid == DIALOG_SENDTO_PLAYER)
    {
        if(!response) return 1;
        
        static otherid;
        if(sscanf(inputtext, "u", otherid))
            return ShowPlayerDialog(playerid, DIALOG_SENDTO_PLAYER, DIALOG_STYLE_INPUT, "Send To: Target", "ERROR: Masukkan ID/Nama yang valid!\n\nMasukkan ID atau Nama Pemain:", "Next", "Close");
        
        if(!IsPlayerConnected(otherid))
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

        SetPVarInt(playerid, "SendToTarget", otherid);
        
        new str[600];
        strcat(str, "Los Santos\n");
        strcat(str, "Las Venturas\n");
        strcat(str, "San Fierro\n");
        strcat(str, "Asuransi\n");
        strcat(str, "Carnaval\n");
        strcat(str, "Bandara\n");
        strcat(str, "Rumah Sakit District\n");
        strcat(str, "Balai Kota\n");
        strcat(str, "Kepolisian District\n");
        strcat(str, "Bengkel Kota District");
        
        ShowPlayerDialog(playerid, DIALOG_SENDTO_LOC, DIALOG_STYLE_LIST, "Pilih Lokasi Teleport", str, "Teleport", "Back");
        return 1;
    }

    if(dialogid == DIALOG_SENDTO_LOC)
    {
        if(!response) 
        {
            ShowPlayerDialog(playerid, DIALOG_SENDTO_PLAYER, DIALOG_STYLE_INPUT, "Send To: Target", "Masukkan ID atau Nama Pemain:", "Next", "Close");
            return 1;
        }
        
        new otherid = GetPVarInt(playerid, "SendToTarget");
        if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain target sudah disconnect!");

        new Float:x, Float:y, Float:z, Float:a, locname[64];
        
        switch(listitem)
        {
            case 0: { x = 1482.0356; y = -1724.5726; z = 13.5469; a = 179.4088; locname = "Los Santos"; }
            case 1: { x = 1686.0118; y = 1448.9471; z = 10.7695; a = 179.4088; locname = "Las Venturas"; }
            case 2: { x = -1425.8307; y = -292.4445; z = 14.1484; a = 179.4088; locname = "San Fierro"; }
            case 3: { x = 421.6674; y = -1324.8463; z = 14.9786; a = 179.4088; locname = "Asuransi"; }
            case 4: { x = 384.6206; y = -2067.2222; z = 7.8359; a = 179.4088; locname = "Carnaval"; }
            case 5: { x = 1684.1560; y = -2323.5259; z = 13.3828; a = 3.8330; locname = "Bandara"; }
            case 6: { x = 1347.2042; y = 743.7079; z = 10.6719; a = 34.7099; locname = "Rumah Sakit District"; }
            case 7: { x = 1246.8817; y = -2047.2511; z = 60.1056; a = 269.0607; locname = "Balai Kota"; }
            case 8: { x = 652.8056; y = -1470.6399; z = 15.4395; a = 292.9807; locname = "Kepolisian District"; }
            case 9: { x = 2846.7720; y = -1846.4277; z = 11.0770; a = 173.4037; locname = "Bengkel Kota District"; }
        }

        if(GetPlayerState(otherid) == PLAYER_STATE_DRIVER) 
        {
            SetVehiclePos(GetPlayerVehicleID(otherid), x, y, z);
            SetVehicleZAngle(GetPlayerVehicleID(otherid), a);
        }
        else 
        {
            SetPlayerPositionEx(otherid, x, y, z, a, 2000);
        }

        SetPlayerInterior(otherid, 0);
        SetPlayerVirtualWorld(otherid, 0);
        
        SendClientMessageEx(playerid, X11_ARWIN, "[AdmCmd] "YELLOW"%s(%d)"ARWIN1" telah berhasil di teleportasikan ke %s.", AccountData[otherid][pName], otherid, locname);
        SendClientMessageEx(otherid, X11_ARWIN, "[AdmCmd] "RED"%s"ARWIN1" telah menteleportasikan anda ke %s.", AccountData[playerid][pAdminname], locname);
        
        AccountData[otherid][pInDoor] = -1;
        AccountData[otherid][pInHouse] = -1;
        AccountData[otherid][pInRusun] = -1;
        AccountData[otherid][pInBiz] = -1;
        AccountData[otherid][pInFamily] = -1;
        
        DeletePVar(playerid, "SendToTarget");
        return 1;
    }
	if(dialogid == DIALOG_FIXMEACC)
	{
		new id = ListFixme[playerid][listitem];
		if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
		if(response)
		{
			if(!IsPlayerConnected(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
			switch(FixmeOption[id])
			{
				case 1:
				{
					if(AccountData[id][pInRusun] != -1)
					{
						SetPlayerInteriorEx(id, 5);
						SetPlayerVirtualWorldEx(id, AccountData[id][pInRusun]);
						SetPlayerPositionEx(id, 2233.7300, -1115.1899, 1050.8828, 0.1506, 2500);
					}

					else if(AccountData[id][pInHouse] != -1)
					{
						SetPlayerInteriorEx(id, HouseData[AccountData[id][pInHouse]][hsInt]);
						SetPlayerVirtualWorldEx(id, AccountData[id][pInHouse]);
						SetPlayerPositionEx(id, HouseData[AccountData[id][pInHouse]][hsIntPos][0], HouseData[AccountData[id][pInHouse]][hsIntPos][1], HouseData[AccountData[id][pInHouse]][hsIntPos][2], HouseData[AccountData[id][pInHouse]][hsIntPos][3], 2500);
					}

					else if(AccountData[id][pInDoor] != -1)
					{
						SetPlayerInteriorEx(id, DoorData[AccountData[id][pInDoor]][dIntint]);
						SetPlayerVirtualWorldEx(id, DoorData[AccountData[id][pInDoor]][dIntvw]);
						SetPlayerPositionEx(id, DoorData[AccountData[id][pInDoor]][dIntposX], DoorData[AccountData[id][pInDoor]][dIntposY], DoorData[AccountData[id][pInDoor]][dIntposZ], DoorData[AccountData[id][pInDoor]][dIntposA], 2500);
					}

					else if(AccountData[id][pInFamily] != -1)
					{
						SetPlayerInteriorEx(id, FamData[AccountData[id][pInFamily]][famInterior]);
						SetPlayerVirtualWorldEx(id, AccountData[id][pInFamily]);
						SetPlayerPositionEx(id, FamData[AccountData[id][pInFamily]][famIntPos][0], FamData[AccountData[id][pInFamily]][famIntPos][1], FamData[AccountData[id][pInFamily]][famIntPos][2], FamData[AccountData[id][pInFamily]][famIntPos][3], 2500);
					}

					else
					{
						SetPlayerVirtualWorldEx(id, 0);
						SetPlayerInteriorEx(id, 0);
					}
					FixmeExists[id] = false;
					FixmeOption[id] = -1;
					FixmeTime[id] = 0;
					SendClientMessageEx(id, X11_ARWIN, "[AmdCmd] "RED"%s"ARWIN1" telah menanggapi fix request anda", AccountData[playerid][pAdminname]);
					SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menanggapi fix request dari "YELLOW"%s(%d).", AccountData[playerid][pAdminname], AccountData[id][pName], id);
				}
				case 2: // stuck
				{
					if(AccountData[id][pArrest] != 0 && AccountData[id][pArrestTime] > 0)
						return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang dalam masa tahanan!");
						
					new Float:POS[3];
					GetPlayerPos(id, POS[0], POS[1], POS[2]);
					SetPlayerPos(id, POS[0], POS[1], POS[2] + 9.0);
					if(IsPlayerInAnyVehicle(id)) 
					{
						RemovePlayerFromVehicle(id);
					}
					FixmeExists[id] = false;
					FixmeOption[id] = -1;
					FixmeTime[id] = 0;
					SendClientMessageEx(id, X11_ARWIN, "[AmdCmd] "RED"%s"ARWIN1" telah menanggapi fix request anda", AccountData[playerid][pAdminname]);
					SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menanggapi fix request dari "YELLOW"%s(%d).", AccountData[playerid][pAdminname], AccountData[id][pName], id);
				}
				case 3: //freezing
				{
					if(AccountData[id][pStunned]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang ter-stun karena taser!");

					AccountData[id][pFreeze] = 0;
					TogglePlayerControllable(id, 1);
				
					FixmeExists[id] = false;
					FixmeOption[id] = -1;
					FixmeTime[id] = 0;
					SendClientMessageEx(id, X11_ARWIN, "[AmdCmd] "RED"%s"ARWIN1" telah menanggapi fix request anda", AccountData[playerid][pAdminname]);
					SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menanggapi fix request dari "YELLOW"%s(%d).", AccountData[playerid][pAdminname], AccountData[id][pName], id);
				}
			}
			if(id != playerid)
			{
				AccountData[playerid][aReceivedReports] ++;
			}
		}
	}
	if(dialogid == DIALOG_CHARLIST)
	{
		if(!response) 
		{
			SendClientMessage(playerid, X11_DARKORANGE, "[i] Anda ditendang dari server karena membatalkan pemilihan karakter");
			return KickEx(playerid);
		}
		else
		{
			if(PlayerChar[playerid][listitem][0] == EOS) return ShowPlayerDialog(playerid, DIALOG_MAKE_CHAR, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Pembuatan Karakter",
			""WHITE"Selamat Datang di "TCRP"District \n"WHITE"Sebelum bermain anda harus membuat karakter terlebih dahulu\
			\nMasukkan nama karakter hanya dengan nama orang Indonesia\nCth: Dudung_Sutarman, Aldy_Firmansyah", "Input", "");
			
			AccountData[playerid][pChar] = listitem;
			SetPlayerName(playerid, PlayerChar[playerid][listitem]);
			StopStream(playerid);
			
			if(!Blacklist_Check(playerid, "name", PlayerChar[playerid][listitem])) 
			{
				mysql_tquery(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `Char_Name` = '%s' LIMIT 1;", PlayerChar[playerid][AccountData[playerid][pChar]]), "LoadPlayerData", "d", playerid);
			}
		}
		/*new query[255];
		mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_characters` WHERE `Char_Name`= '%s' LIMIT 1;", PlayerChar[playerid][AccountData[playerid][pChar]]);
		mysql_tquery(g_SQL, query, "LoadPlayerData", "d", playerid);*/
	}
	if(dialogid == DIALOG_MAKE_CHAR)
	{
		new shstr[596];
		format(shstr, sizeof(shstr), ""WHITE"Selamat datang di "TCRP"District \nSebelum bermain anda harus membuat karakter terlebih dahulu\
		\nMasukkan nama karakter hanya dengan nama orang indonesia\n\nCth: Ucok_Siregar, Dadang_Sucipto");
		if(!response) return KickEx(playerid);

		if(strlen(inputtext) < 1 || strlen(inputtext) > 24)
		{
			ShowPlayerDialog(playerid, DIALOG_MAKE_CHAR, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Pembuatan Karakter",
			""WHITE"Selamat datang di "TCRP"District \n"WHITE"Error: Nama tidak dapat kurang dari 1 huruf atau lebih dari 24\nSebelum bermain anda harus membuat karakter terlebih dahulu\
			\nMasukkan nama karakter hanya dengan nama orang indonesia\n\nCth: Ucok_Siregar, Dadang_Sucipto", "Input", "Kembali");
			return 1;
		}

		if(!IsValidRoleplayName(inputtext))
		{
			ShowPlayerDialog(playerid, DIALOG_MAKE_CHAR, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Pembuatan Karakter",
			""WHITE"Selamat datang di "TCRP"District \n"WHITE"Error: Nama tidak valid!\nSebelum bermain anda harus membuat karakter terlebih dahulu\
			\nMasukkan nama karakter hanya dengan nama orang indonesia\n\nCth: Ucok_Siregar, Dadang_Sucipto", "Input", "Kembali");
			return 1;
		}

		new cQuery[225];
		mysql_format(g_SQL, cQuery, sizeof(cQuery), "SELECT * FROM `player_characters` WHERE `Char_Name` = '%s'", inputtext);
		mysql_tquery(g_SQL, cQuery, "InsertPlayerName", "ds", playerid, inputtext);
		format(AccountData[playerid][pUCP], 22, GetName(playerid));
	}
	if(dialogid == DIALOG_AGE)
    {
		if(!response) 
		{
			return ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Tanggal Lahir", "Mohon masukkan tanggal lahir sesuai format hh/bb/tttt cth: (25/09/2001)", "Input", "");
		}
		if(response)
		{
			new
				iDay,
				iMonth,
				iYear,
				day,
				month,
				year;
				
			getdate(year, month, day);

			static const
					arrMonthDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

			if(sscanf(inputtext, "p</>ddd", iDay, iMonth, iYear)) {
				ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Tanggal Lahir", "Mohon masukkan tanggal lahir sesuai format hh/bb/tttt cth: (25/09/2001)", "Input", "");
			}
			else if(iYear < 1900 || iYear > year) {
				ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Tahun Lahir", "ERROR: Invalid Tahun Lahir\nMohon masukkan tanggal lahir sesuai format hh/bb/tttt cth: (25/09/2001)", "Input", "");
			}
			else if(iMonth < 1 || iMonth > 12) {
				ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Bulan Lahir", "ERROR: Invalid Bulan Lahir\nMohon masukkan tanggal lahir sesuai format hh/bb/tttt cth: (25/09/2001)", "Input", "");
			}
			else if(iDay < 1 || iDay > arrMonthDays[iMonth - 1]) {
				ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Tanggal Lahir", "ERROR: Invalid Tanggal Lahir\nMohon masukkan tanggal lahir sesuai format hh/bb/tttt cth: (25/09/2001)", "Input", "");
			}
			else 
			{
				SetPVarInt(playerid, "CreateAge", 1);
				format(AccountData[playerid][pAge], 50, inputtext);
				new AtmInfo[256];
				format(AtmInfo,1000,"%s", inputtext);
				PlayerTextDrawSetString(playerid, RegisterHapp[playerid][32], AtmInfo);
				PlayerTextDrawShow(playerid, RegisterHapp[playerid][32]);
				CreateCharStepDone[playerid][1] = true;
				//ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Negara Kelahiran", "Mohon masukkan kembali negara asal kelahiran karakter.\nPerhatian: Masukkan nama negara yang valid (cth: Indonesia).", "Input", "");
			}
		}
		return 1;
	}
	if(dialogid == DIALOG_ORIGIN)
	{
		if(response)
		{
			if(isnull(inputtext) || IsNumeric(inputtext))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengandung angka/nomor!");
				return ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Negara Kelahiran", "Mohon masukkan kembali negara asal kelahiran karakter.\nPerhatian: Masukkan nama negara yang valid (cth: Indonesia).", "Input", "");
			}
			
			if (isnull(inputtext) || strlen(inputtext) > 50) 
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Negara kelahiran terlalu panjang!");
		        return ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Negara Kelahiran", "Mohon masukkan kembali negara asal kelahiran karakter.\nPerhatian: Masukkan nama negara yang valid (cth: Indonesia).", "Input", "");
			}
			else for (new i = 0, len = strlen(inputtext); i != len; i ++) {
			    if ((inputtext[i] >= 'A' && inputtext[i] <= 'Z') || (inputtext[i] >= 'a' && inputtext[i] <= 'z') || (inputtext[i] >= '0' && inputtext[i] <= '9') || (inputtext[i] == ' ') || (inputtext[i] == ',') || (inputtext[i] == '.'))
					continue;

				else return ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Negara Kelahiran", "Mohon masukkan kembali negara asal kelahiran karakter.\nPerhatian: Masukkan nama negara yang valid (cth: Indonesia).", "Input", "");
			}
			format(AccountData[playerid][pOrigin], 32, inputtext);
			SetPVarInt(playerid, "CreateOrigin", 1);
			CreateCharStepDone[playerid][2] = true;

            new AtmInfo[128];
			format(AtmInfo,1000,"%s", inputtext);
			PlayerTextDrawSetString(playerid, RegisterHapp[playerid][31], AtmInfo);

			//ShowPlayerDialog(playerid, DIALOG_TINGGIBADAN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE" - Tinggi Badan (cm)", "Mohon masukkan tinggi badan (cm) karakter!\nPerhatian: Format hanya berupa angka satuan cm (cth: 163).", "Input", "");
		}
		else ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Negara Kelahiran", "Mohon masukkan kembali negara asal kelahiran karakter.\nPerhatian: Masukkan nama negara yang valid (cth: Indonesia).", "Input", "");
	}
	if(dialogid == DIALOG_TINGGIBADAN)
	{
		if(response)
		{
			new tinggi = floatround(strval(inputtext));
			if(isnull(inputtext) || !IsNumeric(inputtext))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Format hanya berupa angka satuan cm!");
				return ShowPlayerDialog(playerid, DIALOG_TINGGIBADAN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE" - Tinggi Badan (cm)", "Mohon masukkan tinggi badan (cm) karakter!\nPerhatian: Format hanya berupa angka satuan cm (cth: 163).", "Input", "");
			}
			
			if(tinggi <= 150 || tinggi >= 200)
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tinggi Badan minimal 150 cm dan maksimal 200 cm");
				return ShowPlayerDialog(playerid, DIALOG_TINGGIBADAN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE" - Tinggi Badan (cm)", "Mohon masukkan tinggi badan (cm) karakter!\nPerhatian: Format hanya berupa angka satuan cm (cth: 163).", "Input", "");
			}
			AccountData[playerid][pTinggiBadan] = tinggi;
			SetPVarInt(playerid, "CreateHeight", 1);
			new AtmInfo[256];
			format(AtmInfo,1000,"%s Cm", inputtext);
			PlayerTextDrawSetString(playerid, RegisterHapp[playerid][29], AtmInfo);
			CreateCharStepDone[playerid][3] = true;
			//ShowPlayerDialog(playerid, DIALOG_BERATBADAN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE" - Berat Badan (kg)", "Mohon masukkan berat badan (kg) karakter!\nPerhatian: Format hanya berupa angka satuan kg (cth: 75).", "Input", "");
		}
		else return ShowPlayerDialog(playerid, DIALOG_TINGGIBADAN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE" - Tinggi Badan", "Mohon masukkan tinggi badan karakter!\nPerhatian: format berupa angka minimal 165-180cm (cth: 160)", "Input", "Back");
	}
	if(dialogid == DIALOG_BERATBADAN)
	{
		if(response)
		{
			new berat = floatround(strval(inputtext));
			if(isnull(inputtext) || !IsNumeric(inputtext))
				return ShowPlayerDialog(playerid, DIALOG_BERATBADAN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE" - Berat Badan (kg)", "Mohon masukkan berat badan (kg) karakter!\nPerhatian: Format hanya berupa angka satuan kg (cth: 75).", "Input", "");
			
			if(berat <= 40)
				return ShowPlayerDialog(playerid, DIALOG_BERATBADAN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE" - Berat Badan (kg)", "Tidak dapat dibawah 40kg!", "Input", "");

			if(berat >= 95)
				return ShowPlayerDialog(playerid, DIALOG_BERATBADAN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE" - Berat Badan (kg)", "Tidak dapat diatas 95kg!", "Input", "");

			AccountData[playerid][pBeratBadan] = berat;
			SetPVarInt(playerid, "CreateWeight", 1);
			new AtmInfo[256];
			format(AtmInfo,1000,"%s Kg", inputtext);
			PlayerTextDrawSetString(playerid, RegisterHapp[playerid][30], AtmInfo);
			CreateCharStepDone[playerid][4] = true;
			//ShowPlayerDialog(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Jenis Kelamin", ""WHITE"Laki-Laki\n"GRAY"Perempuan", "Pilih", "");
		}
	}
	if(dialogid == DIALOG_GENDER)
    {
		if(response)
		{
			AccountData[playerid][pGender] = listitem + 1;
			AccountData[playerid][pSkin] = (listitem) ? (193) : (59);

			ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembuatan karakter berhasil!");
			SetPlayerCameraPos(playerid, 534.065, -2102.218, 98.480);
			SetPlayerCameraLookAt(playerid, 531.651, -2098.260, 96.606);
			// ShowPlayerDialog(playerid, DIALOG_SELECT_SPAWN, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Pilih Lokasi Spawn",
			// "Titik Spawn\tDetail\tLokasi\
			// \nLos Santos International Airport\tAnda mendarat dengan pesawat\tLos Santos\
			// \n"GRAY"Pelabuhan Merak ( Ocean Docks )\tAnda mendarat dengan kapal laut\tLos Santos", "Pilih", "");
		}
		SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], 1694.7468, -2332.3428, 13.5469, 0.0377, 0, 0, 0, 0, 0, 0);

		new characterQuery[178];
		if(GetPVarInt(playerid, "CreateName") && GetPVarInt(playerid, "CreateOrigin") && GetPVarInt(playerid, "CreateAge") && GetPVarInt(playerid, "CreateHeight") && GetPVarInt(playerid, "CreateWeight"))
		{
			mysql_format(g_SQL, characterQuery, sizeof(characterQuery), "INSERT INTO player_characters (Char_Name, Char_UCP, Char_Skin, Char_RegisterDate) VALUES ('%s', '%s', %d, CURRENT_TIMESTAMP())", AccountData[playerid][pTempName], AccountData[playerid][pUCP], AccountData[playerid][pSkin]);
			mysql_tquery(g_SQL, characterQuery, "OnPlayerRegister", "d", playerid);
			SetPlayerName(playerid, AccountData[playerid][pTempName]);
		}
		return 1;
	}
	if(dialogid == DialogTrackMyVeh)
	{
		if(!response)
		{
			return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
		}

		if(PlayerKargoVars[playerid][KargoStarted])
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang bekerja sebagai Supir Kargo!");

		new
			Float:POS[3];
		
		if(isnull(inputtext))
		{
			ShowPlayerDialog(playerid, DialogTrackMyVeh, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Lacak Kendaraan",
			"Error: Tidak dapat diisi kosong!\nCari Kendaraan\n"YELLOW"(Masukkan VID Kendaraan yang ingin anda cari):", "Input", "Batal");
			return 1;
		}

		if(!IsNumeric(inputtext))
		{
			ShowPlayerDialog(playerid, DialogTrackMyVeh, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Lacak Kendaraan",
			"Error: Hanya dapat diisi angka!\nCari Kendaraan\n"YELLOW"(Masukkan VID Kendaraan yang ingin anda cari):", "Input", "Batal");
			return 1;
		}

		foreach(new i : PvtVehicles) if (PlayerVehicle[i][pVehExists])
		{
			if(strval(inputtext) == PlayerVehicle[i][pVehID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut tidak ter-spawn!");
			if(PlayerVehicle[i][pVehPhysic] == strval(inputtext))
			{
				if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
				{
					if(PlayerVehicle[i][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
					
					GetVehiclePos(PlayerVehicle[i][pVehPhysic], POS[0], POS[1], POS[2]);
					AccountData[playerid][pTrackCar] = 1;

					SetPlayerRaceCheckpoint(playerid, 1, POS[0], POS[1], POS[2], 0.0, 0.0, 0.0, 3.5);
					//(playerid,  POS[0], POS[1], POS[2], COLOR_BLUE);
					
					SendClientMessageEx(playerid, -1, "[i] Sistem kami telah membantu anda mencari kendaraan anda yang hilang. Ikuti tanda di map!");
				}
			}
		}
	}
	if(dialogid == DIALOG_TOY)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0: //slot 1
				{
					new status[256], status2[256];
					if(pToys[playerid][0][toy_status] == 1)
					{
						status = ""VERONA_ARWIN"Sembunyikan";
						status2 = ""VERONA_ARWIN"(Jika ingin disembunyikan)";
					}
					else 
					{
						status = ""VERONA_ARWIN"Perlihatkan";
						status2 = ""VERONA_ARWIN"(Jika ingin diperlihatkan)";
					}

					AccountData[playerid][toySelected] = 0;
					if(pToys[playerid][0][toy_model] == 0)
					{
						ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memiliki Topi / Helmet");
					}
					else
					{
						new string[1800];
						format(string, sizeof string, "Pengaturan\tParameter\n");
						format(string, sizeof string, "%s"WHITE"Edit Posisi\t(Khusus PC)\n", string);
						format(string, sizeof string, "%s"VERONA_ARWIN"Edit Posisi\t(Khusus Android)\n", string);
						format(string, sizeof string, "%s"WHITE"Ubah Posisi Tulang\t(Bone)\n", string);
						format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_x]);
						format(string, sizeof string, "%s"WHITE"Sumbu Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_y]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_z]);
						format(string, sizeof string, "%s"WHITE"Rotasi X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rx]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Rotasi Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_ry]);
						format(string, sizeof string, "%s"WHITE"Rotasi Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Skala X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sx]);
						format(string, sizeof string, "%s"WHITE"Skala Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sy]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Skala Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
						format(string, sizeof string, "%s"WHITE"Hapus\t(Pilih jika anda ingin menghapus permanent)\n", string);
						format(string, sizeof string, "%s"VERONA_ARWIN"%s\t%s\n", string, status, status2);
						ShowPlayerDialog(playerid, DialogToyEdit, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Edit Fashion (Topi/Helmet)", string, "Select", "Cancel");
					}
				}
				case 1: //slot 2
				{
					new status[256], status2[256];
					if(pToys[playerid][1][toy_status] == 1)
					{
						status = ""VERONA_ARWIN"Sembunyikan";
						status2 = ""VERONA_ARWIN"(Jika ingin disembunyikan)";
					}
					else 
					{
						status = ""VERONA_ARWIN"Perlihatkan";
						status2 = ""VERONA_ARWIN"(Jika ingin diperlihatkan)";
					}
					
					AccountData[playerid][toySelected] = 1;
					if(pToys[playerid][1][toy_model] == 0)
					{
						ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memiliki Kacamata!");
					}
					else
					{
						new string[1800];
						format(string, sizeof string, "Pengaturan\tParameter\n");
						format(string, sizeof string, "%s"WHITE"Edit Posisi\t(Khusus PC)\n", string);
						format(string, sizeof string, "%s"VERONA_ARWIN"Edit Posisi\t(Khusus Android)\n", string);
						format(string, sizeof string, "%s"WHITE"Ubah Posisi Tulang\t(Bone)\n", string);
						format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_x]);
						format(string, sizeof string, "%s"WHITE"Sumbu Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_y]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_z]);
						format(string, sizeof string, "%s"WHITE"Rotasi X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rx]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Rotasi Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_ry]);
						format(string, sizeof string, "%s"WHITE"Rotasi Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Skala X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sx]);
						format(string, sizeof string, "%s"WHITE"Skala Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sy]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Skala Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
						format(string, sizeof string, "%s"WHITE"Hapus\t(Pilih jika anda ingin menghapus permanent)\n", string);
						format(string, sizeof string, "%s"VERONA_ARWIN"%s\t%s\n", string, status, status2);
						ShowPlayerDialog(playerid, DialogToyEdit, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Edit Fashion (Kacamata)", string, "Select", "Cancel");
					}
				}
				case 2: //slot 3
				{
					new status[256], status2[256];
					if(pToys[playerid][2][toy_status] == 1)
					{
						status = ""VERONA_ARWIN"Sembunyikan";
						status2 = ""VERONA_ARWIN"(Jika ingin disembunyikan)";
					}
					else 
					{
						status = ""VERONA_ARWIN"Perlihatkan";
						status2 = ""VERONA_ARWIN"(Jika ingin diperlihatkan)";
					}

					AccountData[playerid][toySelected] = 2;
					if(pToys[playerid][2][toy_model] == 0)
					{
						ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memiliki Aksesoris");
					}
					else
					{
						new string[1800];
						format(string, sizeof string, "Pengaturan\tParameter\n");
						format(string, sizeof string, "%s"WHITE"Edit Posisi\t(Khusus PC)\n", string);
						format(string, sizeof string, "%s"VERONA_ARWIN"Edit Posisi\t(Khusus Android)\n", string);
						format(string, sizeof string, "%s"WHITE"Ubah Posisi Tulang\t(Bone)\n", string);
						format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_x]);
						format(string, sizeof string, "%s"WHITE"Sumbu Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_y]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_z]);
						format(string, sizeof string, "%s"WHITE"Rotasi X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rx]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Rotasi Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_ry]);
						format(string, sizeof string, "%s"WHITE"Rotasi Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Skala X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sx]);
						format(string, sizeof string, "%s"WHITE"Skala Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sy]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Skala Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
						format(string, sizeof string, "%s"WHITE"Hapus\t(Pilih jika anda ingin menghapus permanent)\n", string);
						format(string, sizeof string, "%s"VERONA_ARWIN"%s\t%s\n", string, status, status2);
						ShowPlayerDialog(playerid, DialogToyEdit, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Edit Fashion (Aksesoris)", string, "Select", "Cancel");
					}
				}
				case 3: //slot 4
				{
					new status[256], status2[256];
					if(pToys[playerid][3][toy_status] == 1)
					{
						status = ""VERONA_ARWIN"Sembunyikan";
						status2 = ""VERONA_ARWIN"(Jika ingin disembunyikan)";
					}
					else 
					{
						status = ""VERONA_ARWIN"Perlihatkan";
						status2 = ""VERONA_ARWIN"(Jika ingin diperlihatkan)";
					}

					AccountData[playerid][toySelected] = 3;
					if(pToys[playerid][3][toy_model] == 0)
					{
						ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memiliki Tas / Koper");
					}
					else
					{
						new string[1800];
						format(string, sizeof string, "Pengaturan\tParameter\n");
						format(string, sizeof string, "%s"WHITE"Edit Posisi\t(Khusus PC)\n", string);
						format(string, sizeof string, "%s"VERONA_ARWIN"Edit Posisi\t(Khusus Android)\n", string);
						format(string, sizeof string, "%s"WHITE"Ubah Posisi Tulang\t(Bone)\n", string);
						format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_x]);
						format(string, sizeof string, "%s"WHITE"Sumbu Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_y]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_z]);
						format(string, sizeof string, "%s"WHITE"Rotasi X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rx]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Rotasi Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_ry]);
						format(string, sizeof string, "%s"WHITE"Rotasi Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Skala X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sx]);
						format(string, sizeof string, "%s"WHITE"Skala Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sy]);
						format(string, sizeof string, "%s"VERONA_ARWIN"Skala Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
						format(string, sizeof string, "%s"WHITE"Hapus\t(Pilih jika anda ingin menghapus permanent)\n", string);
						format(string, sizeof string, "%s"VERONA_ARWIN"%s\t%s\n", string, status, status2);
						ShowPlayerDialog(playerid, DialogToyEdit, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Edit Fashion (Tas/Koper)", string, "Select", "Cancel");
					}
				}
				case 4:
				{
					if(AccountData[playerid][PurchasedToy] == true)
					{
						for(new i = 0; i < 4; i++)
						{
							pToys[playerid][i][toy_model] = 0;
							pToys[playerid][i][toy_bone] = 1;
							pToys[playerid][i][toy_status] = 1;
							pToys[playerid][i][toy_x] = 0.0;
							pToys[playerid][i][toy_y] = 0.0;
							pToys[playerid][i][toy_z] = 0.0;
							pToys[playerid][i][toy_rx] = 0.0;
							pToys[playerid][i][toy_ry] = 0.0;
							pToys[playerid][i][toy_rz] = 0.0;
							pToys[playerid][i][toy_sx] = 1.0;
							pToys[playerid][i][toy_sy] = 1.0;
							pToys[playerid][i][toy_sz] = 1.0;
							
							if(IsPlayerAttachedObjectSlotUsed(playerid, i))
							{
								RemovePlayerAttachedObject(playerid, i);
							}
						}
						new string[128];
						mysql_format(g_SQL, string, sizeof(string), "DELETE FROM toys WHERE Owner = '%s'", AccountData[playerid][pName]);
						mysql_tquery(g_SQL, string);
						AccountData[playerid][PurchasedToy] = false;
						GameTextForPlayer(playerid, "~r~~h~All Toy Rested!~y~!", 3000, 4);
					}
				}
			}
		}
		return 1;
	}
	if(dialogid == DialogToyEdit)
	{
		new id = AccountData[playerid][toySelected];
		if(response)
		{
			switch(listitem)
			{
				case 0: // Edit Pc
				{
					if(EditingWeapon[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang dalam mode pengeditan!");

					if(IsPlayerAttachedObjectSlotUsed(playerid, id))
					{
						EditAttachedObject(playerid, id);
					}
					else ShowTDN(playerid, NOTIFICATION_ERROR, "Toys not attached!");
				}
				case 1: // Edit Android
				{
					ShowTDToys(playerid);
				}
				case 2: // change bone
				{
					ShowPlayerDialog(playerid, DIALOG_TOYPOSISI, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Ubah Tulang(Bone)",
					"Spine\
					\n"GRAY"Head\
					\nLeft Upper Arm\
					\n"GRAY"Right Upper Arm\
					\nLeft Hand\
					\n"GRAY"Right Hand\
					\nLeft Thigh\
					\n"GRAY"Right Thigh\
					\nLeft Foot\
					\n"GRAY"Right Foot\
					\nRight Calf\
					\n"GRAY"Left Calf\
					\nLeft Forearm\
					\n"GRAY"Right Forearm\
					\nLeft Clavicle\
					\n"GRAY"Right Clavicle\
					\nNeck\
					\n"GRAY"Jaw", "Select", "Cancel");
				}
				case 3:
				{
					new mstr[128];
					format(mstr, sizeof mstr, ""WHITE"Sumbu X (saat ini): %f\n"YELLOW"(Masukkan Sumbu X yang baru):", pToys[playerid][AccountData[playerid][toySelected]][toy_x]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSX, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Sumbu X", mstr, "Edit", "Cancel");
				}
				case 4:
				{
					new mstr[128];
					format(mstr, sizeof mstr, ""WHITE"Sumbu Y (saat ini): %f\n"YELLOW"(Masukkan Sumbu Y yang baru):", pToys[playerid][AccountData[playerid][toySelected]][toy_y]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSY, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Sumbu X", mstr, "Edit", "Cancel");
				}
				case 5:
				{
					new mstr[128];
					format(mstr, sizeof mstr, ""WHITE"Sumbu Z (saat ini): %f\n"YELLOW"(Masukkan Sumbu Z yang baru):", pToys[playerid][AccountData[playerid][toySelected]][toy_z]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSZ, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Sumbu Z", mstr, "Edit", "Cancel");
				}
				case 6:
				{
					new mstr[128];
					format(mstr, sizeof mstr, ""WHITE"Rotasi X (saat ini): %f\n"YELLOW"(Masukkan Rotasi X yang baru):", pToys[playerid][AccountData[playerid][toySelected]][toy_rx]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSRX, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Rotasi X", mstr, "Edit", "Cancel");
				}
				case 7:
				{
					new mstr[128];
					format(mstr, sizeof mstr, ""WHITE"Rotasi Y (saat ini): %f\n"YELLOW"(Masukkan Rotasi Y yang baru):", pToys[playerid][AccountData[playerid][toySelected]][toy_ry]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSRY, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Rotasi Y", mstr, "Edit", "Cancel");
				}
				case 8:
				{
					new mstr[128];
					format(mstr, sizeof mstr, ""WHITE"Rotasi Z (saat ini): %f\n"YELLOW"(Masukkan Rotasi Z yang baru):", pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSRZ, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Rotasi Z", mstr, "Edit", "Cancel");
				}
				case 9:
				{
					new mstr[128];
					format(mstr, sizeof mstr, ""WHITE"Skala X (saat ini): %f\n"YELLOW"(Masukkan Skala X yang baru):", pToys[playerid][AccountData[playerid][toySelected]][toy_sx]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSSX, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Skala X", mstr, "Edit", "Cancel");
				}
				case 10:
				{
					new mstr[128];
					format(mstr, sizeof mstr, ""WHITE"Skala Y (saat ini): %f\n"YELLOW"(Masukkan Skala Y yang baru):", pToys[playerid][AccountData[playerid][toySelected]][toy_sy]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSSY, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Skala Y", mstr, "Edit", "Cancel");
				}
				case 11:
				{
					new mstr[128];
					format(mstr, sizeof mstr, ""WHITE"Skala Z (saat ini): %f\n"YELLOW"(Masukkan Skala Z yang baru):", pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSSZ, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Edit Skala Z", mstr, "Edit", "Cancel");
				}
				case 12: // remove toy
				{
					if(IsPlayerAttachedObjectSlotUsed(playerid, AccountData[playerid][toySelected]))
					{
						RemovePlayerAttachedObject(playerid, AccountData[playerid][toySelected]);
					}
					pToys[playerid][AccountData[playerid][toySelected]][toy_model] = 0;
					ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menghapus Aksesoris");
					SetPVarInt(playerid, "UpdatedToy", 1);
					TogglePlayerControllable(playerid, true);
				}
				case 13:
				{
					if(pToys[playerid][AccountData[playerid][toySelected]][toy_status] == 1)
					{
						if(IsPlayerAttachedObjectSlotUsed(playerid, AccountData[playerid][toySelected]))
						{
							RemovePlayerAttachedObject(playerid, AccountData[playerid][toySelected]);
						}
						pToys[playerid][AccountData[playerid][toySelected]][toy_status] = 0;
						ShowTDN(playerid, NOTIFICATION_INFO, "Toys tersebut telah disembunyikan!");
					}
					else
					{
						SetPlayerAttachedObject(playerid,
							AccountData[playerid][toySelected],
							pToys[playerid][AccountData[playerid][toySelected]][toy_model],
							pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
							pToys[playerid][AccountData[playerid][toySelected]][toy_x],
							pToys[playerid][AccountData[playerid][toySelected]][toy_y],
							pToys[playerid][AccountData[playerid][toySelected]][toy_z],
							pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
							pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
							pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
							pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
							pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
							pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);

						SetPVarInt(playerid, "UpdatedToy", 1);
						pToys[playerid][AccountData[playerid][toySelected]][toy_status] = 1;
						ShowTDN(playerid, NOTIFICATION_INFO, "Toys tersebut telah ditampilkan!");
					}
				}
				case 14:	//share toy pos
				{
					SendNearbyMessage(playerid, 10.0, -1, ""VERONA_ARWIN"[Cordinate By %s] "WHITE_E"PosX: %.3f | PosY: %.3f | PosZ: %.3f | PosRX: %.3f | PosRY: %.3f | PosRZ: %.3f",
					AccountData[playerid][pName], pToys[playerid][AccountData[playerid][toySelected]][toy_x], pToys[playerid][AccountData[playerid][toySelected]][toy_y], pToys[playerid][AccountData[playerid][toySelected]][toy_z],
					pToys[playerid][AccountData[playerid][toySelected]][toy_rx], pToys[playerid][AccountData[playerid][toySelected]][toy_ry], pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
				}
			}
		}
		else
		{
			new string[350];
			if(pToys[playerid][0][toy_model] == 0)
			{
				strcat(string, ""WHITE"Hat/Helmet\n");
			}
			else strcat(string, ""WHITE"Hat/Helmet\n");

			if(pToys[playerid][1][toy_model] == 0)
			{
				strcat(string, ""VERONA_ARWIN"Kacamata\n");
			}
			else strcat(string, ""VERONA_ARWIN"Kacamata\n");

			if(pToys[playerid][2][toy_model] == 0)
			{
				strcat(string, ""WHITE"Aksesoris\n");
			}
			else strcat(string, ""WHITE"Aksesoris\n");

			if(pToys[playerid][3][toy_model] == 0)
			{
				strcat(string, ""VERONA_ARWIN"Tas/Koper\n");
			}
			else strcat(string, ""VERONA_ARWIN"Tas/Koper\n");

			ShowPlayerDialog(playerid, DIALOG_TOY, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Edit Fashion", string, "Select", "Cancel");
		}
		return 1;
	}
	if(dialogid == DIALOG_TOYEDIT_ANDROID)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0: //Pos X
				{
					new mstr[128];
					format(mstr, sizeof(mstr), ""WHITE_E"Current Toy PosX: %f\nInput new Toy PosX:(Float)", pToys[playerid][AccountData[playerid][toySelected]][toy_x]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSX, DIALOG_STYLE_INPUT, "Toy PosX", mstr, "Edit", "Cancel");
				}
				case 1: //Pos Y
				{
					new mstr[128];
					format(mstr, sizeof(mstr), ""WHITE_E"Current Toy PosY: %f\nInput new Toy PosY:(Float)", pToys[playerid][AccountData[playerid][toySelected]][toy_y]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSY, DIALOG_STYLE_INPUT, "Toy PosY", mstr, "Edit", "Cancel");
				}
				case 2: //Pos Z
				{
					new mstr[128];
					format(mstr, sizeof(mstr), ""WHITE_E"Current Toy PosZ: %f\nInput new Toy PosZ:(Float)", pToys[playerid][AccountData[playerid][toySelected]][toy_z]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSZ, DIALOG_STYLE_INPUT, "Toy PosZ", mstr, "Edit", "Cancel");
				}
				case 3: //Pos RX
				{
					new mstr[128];
					format(mstr, sizeof(mstr), ""WHITE_E"Current Toy PosRX: %f\nInput new Toy PosRX:(Float)", pToys[playerid][AccountData[playerid][toySelected]][toy_rx]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSRX, DIALOG_STYLE_INPUT, "Toy PosRX", mstr, "Edit", "Cancel");
				}
				case 4: //Pos RY
				{
					new mstr[128];
					format(mstr, sizeof(mstr), ""WHITE_E"Current Toy PosRY: %f\nInput new Toy PosRY:(Float)", pToys[playerid][AccountData[playerid][toySelected]][toy_ry]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSRY, DIALOG_STYLE_INPUT, "Toy PosRY", mstr, "Edit", "Cancel");
				}
				case 5: //Pos RZ
				{
					new mstr[128];
					format(mstr, sizeof(mstr), ""WHITE_E"Current Toy PosRZ: %f\nInput new Toy PosRZ:(Float)", pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSRZ, DIALOG_STYLE_INPUT, "Toy PosRZ", mstr, "Edit", "Cancel");
				}
				case 6: //Pos ScaleX
				{
					new mstr[128];
					format(mstr, sizeof(mstr), ""WHITE_E"Current Toy ScaleX: %f\nInput new Toy ScaleX:(Float)", pToys[playerid][AccountData[playerid][toySelected]][toy_sx]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSSX, DIALOG_STYLE_INPUT, "Toy ScaleX", mstr, "Edit", "Cancel");
				}
				case 7: //Pos ScaleY
				{
					new mstr[128];
					format(mstr, sizeof(mstr), ""WHITE_E"Current Toy ScaleY: %f\nInput new Toy ScaleY:(Float)", pToys[playerid][AccountData[playerid][toySelected]][toy_sy]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSSY, DIALOG_STYLE_INPUT, "Toy ScaleY", mstr, "Edit", "Cancel");
				}
				case 8: //Pos ScaleZ
				{
					new mstr[128];
					format(mstr, sizeof(mstr), ""WHITE_E"Current Toy ScaleZ: %f\nInput new Toy ScaleZ:(Float)", pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSSZ, DIALOG_STYLE_INPUT, "Toy ScaleZ", mstr, "Edit", "Cancel");
				}
			}
		}
		else
		{
			new string[512];
			format(string, sizeof(string), ""dot"Edit Toy Position(PC Only)\n"dot"Edit Toy Coordinat(Android)\n"dot"Change Bone\n"dot""GREY_E"Remove Toy\n"dot"Share Toy Pos");
			ShowPlayerDialog(playerid, DIALOG_TOYEDIT, DIALOG_STYLE_LIST, ""WHITE_E"Player Toys", string, "Select", "Cancel");
		}
	}
	if(dialogid == DIALOG_TOYPOSISI)
	{
		if(response)
		{
			listitem++;
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone] = listitem;
			if(IsPlayerAttachedObjectSlotUsed(playerid, AccountData[playerid][toySelected]))
			{
				RemovePlayerAttachedObject(playerid, AccountData[playerid][toySelected]);
			}
			listitem = AccountData[playerid][toySelected];
			SetPlayerAttachedObject(playerid,
					listitem,
					pToys[playerid][listitem][toy_model],
					pToys[playerid][listitem][toy_bone],
					pToys[playerid][listitem][toy_x],
					pToys[playerid][listitem][toy_y],
					pToys[playerid][listitem][toy_z],
					pToys[playerid][listitem][toy_rx],
					pToys[playerid][listitem][toy_ry],
					pToys[playerid][listitem][toy_rz],
					pToys[playerid][listitem][toy_sx],
					pToys[playerid][listitem][toy_sy],
					pToys[playerid][listitem][toy_sz]);
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengganti Bone fashion tersebut!");
			// GameTextForPlayer(playerid, "~g~~h~Bone Changed~y~!", 3000, 4);
			SetPVarInt(playerid, "UpdatedToy", 1);
		}
		return 1;
	}
	if(dialogid == DIALOG_TOYPOSISIBUY)
	{
		if(response)
		{
			listitem++;
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone] = listitem;
			SetPlayerAttachedObject(playerid, AccountData[playerid][toySelected], pToys[playerid][AccountData[playerid][toySelected]][toy_model], listitem);
			if(AccountData[playerid][PurchasedToy] == false)
			{
				new query[255];
				mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `toys` (`Owner`) VALUES ('%s')" , AccountData[playerid][pName]);
				mysql_tquery(g_SQL, query);
			}
			
			MySQL_SavePlayerToys(playerid);
		}
		return 1;
	}
	if(dialogid == DIALOG_TOYPOSX)
	{
		if(response)
		{
			new Float:posisi = floatstr(inputtext);

			SetPlayerAttachedObject(playerid,
				AccountData[playerid][toySelected],
				pToys[playerid][AccountData[playerid][toySelected]][toy_model],
				pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
				posisi,
				pToys[playerid][AccountData[playerid][toySelected]][toy_y],
				pToys[playerid][AccountData[playerid][toySelected]][toy_z],
				pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
				pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
				pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			
			pToys[playerid][AccountData[playerid][toySelected]][toy_x] = posisi;
			SetPVarInt(playerid, "UpdatedToy", 1);
			//MySQL_SavePlayerToys(playerid);

			new minsty[612];
			if(AccountData[playerid][toySelected] == 0)
			{
				minsty = "Topi/Helmet";
			}
			else if(AccountData[playerid][toySelected] == 1)
			{
				minsty = "Kacamata";
			}
			else if(AccountData[playerid][toySelected] == 2)
			{
				minsty = "Aksesoris";
			}
			else if(AccountData[playerid][toySelected] == 3)
			{
				minsty = "Tas/Koper";
			}
			new string[1800], toys[128];
			format(toys, sizeof(toys), ""TCRP"District "WHITE" - Edit Fashion (%s)", minsty);
			format(string, sizeof string, "Pengaturan\tParameter\n");
			format(string, sizeof string, "%s"WHITE"Edit Posisi\t(Khusus PC)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Edit Posisi\t(Khusus Android)\n", string);
			format(string, sizeof string, "%s"WHITE"Ubah Posisi Tulang\t(Bone)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_x]);
			format(string, sizeof string, "%s"WHITE"Sumbu Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_y]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_z]);
			format(string, sizeof string, "%s"WHITE"Rotasi X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rx]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Rotasi Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_ry]);
			format(string, sizeof string, "%s"WHITE"Rotasi Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sx]);
			format(string, sizeof string, "%s"WHITE"Skala Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sy]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			format(string, sizeof string, "%s"WHITE"Hapus\t(Pilih jika anda ingin menghapus permanent)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sembunyikan\t(Jika ingin disembunyikan)\n", string);
			ShowPlayerDialog(playerid, DialogToyEdit, DIALOG_STYLE_TABLIST_HEADERS, toys, string, "Select", "Cancel");
		}
	}
	if(dialogid == DIALOG_TOYPOSY)
	{
		if(response)
		{
			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				AccountData[playerid][toySelected],
				pToys[playerid][AccountData[playerid][toySelected]][toy_model],
				pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
				pToys[playerid][AccountData[playerid][toySelected]][toy_x],
				posisi,
				pToys[playerid][AccountData[playerid][toySelected]][toy_z],
				pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
				pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
				pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			
			pToys[playerid][AccountData[playerid][toySelected]][toy_y] = posisi;
			SetPVarInt(playerid, "UpdatedToy", 1);
			//MySQL_SavePlayerToys(playerid);
			
			new minsty[612];
			if(AccountData[playerid][toySelected] == 0)
			{
				minsty = "Topi/Helmet";
			}
			else if(AccountData[playerid][toySelected] == 1)
			{
				minsty = "Kacamata";
			}
			else if(AccountData[playerid][toySelected] == 2)
			{
				minsty = "Aksesoris";
			}
			else if(AccountData[playerid][toySelected] == 3)
			{
				minsty = "Tas/Koper";
			}
			new string[1800], toys[128];
			format(toys, sizeof(toys), ""TCRP"District "WHITE" - Edit Fashion (%s)", minsty);
			format(string, sizeof string, "Pengaturan\tParameter\n");
			format(string, sizeof string, "%s"WHITE"Edit Posisi\t(Khusus PC)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Edit Posisi\t(Khusus Android)\n", string);
			format(string, sizeof string, "%s"WHITE"Ubah Posisi Tulang\t(Bone)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_x]);
			format(string, sizeof string, "%s"WHITE"Sumbu Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_y]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_z]);
			format(string, sizeof string, "%s"WHITE"Rotasi X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rx]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Rotasi Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_ry]);
			format(string, sizeof string, "%s"WHITE"Rotasi Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sx]);
			format(string, sizeof string, "%s"WHITE"Skala Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sy]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			format(string, sizeof string, "%s"WHITE"Hapus\t(Pilih jika anda ingin menghapus permanent)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sembunyikan\t(Jika ingin disembunyikan)\n", string);
			ShowPlayerDialog(playerid, DialogToyEdit, DIALOG_STYLE_TABLIST_HEADERS, toys, string, "Select", "Cancel");
		}
	}
	if(dialogid == DIALOG_TOYPOSZ)
	{
		if(response)
		{
			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				AccountData[playerid][toySelected],
				pToys[playerid][AccountData[playerid][toySelected]][toy_model],
				pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
				pToys[playerid][AccountData[playerid][toySelected]][toy_x],
				pToys[playerid][AccountData[playerid][toySelected]][toy_y],
				posisi,
				pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
				pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
				pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			
			pToys[playerid][AccountData[playerid][toySelected]][toy_z] = posisi;
			SetPVarInt(playerid, "UpdatedToy", 1);
			//MySQL_SavePlayerToys(playerid);
			
			new minsty[612];
			if(AccountData[playerid][toySelected] == 0)
			{
				minsty = "Topi/Helmet";
			}
			else if(AccountData[playerid][toySelected] == 1)
			{
				minsty = "Kacamata";
			}
			else if(AccountData[playerid][toySelected] == 2)
			{
				minsty = "Aksesoris";
			}
			else if(AccountData[playerid][toySelected] == 3)
			{
				minsty = "Tas/Koper";
			}
			new string[1800], toys[128];
			format(toys, sizeof(toys), ""TCRP"District "WHITE" - Edit Fashion (%s)", minsty);
			format(string, sizeof string, "Pengaturan\tParameter\n");
			format(string, sizeof string, "%s"WHITE"Edit Posisi\t(Khusus PC)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Edit Posisi\t(Khusus Android)\n", string);
			format(string, sizeof string, "%s"WHITE"Ubah Posisi Tulang\t(Bone)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_x]);
			format(string, sizeof string, "%s"WHITE"Sumbu Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_y]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_z]);
			format(string, sizeof string, "%s"WHITE"Rotasi X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rx]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Rotasi Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_ry]);
			format(string, sizeof string, "%s"WHITE"Rotasi Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sx]);
			format(string, sizeof string, "%s"WHITE"Skala Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sy]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			format(string, sizeof string, "%s"WHITE"Hapus\t(Pilih jika anda ingin menghapus permanent)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sembunyikan\t(Jika ingin disembunyikan)\n", string);
			ShowPlayerDialog(playerid, DialogToyEdit, DIALOG_STYLE_TABLIST_HEADERS, toys, string, "Select", "Cancel");
		}
	}
	if(dialogid == DIALOG_TOYPOSRX)
	{
		if(response)
		{
			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				AccountData[playerid][toySelected],
				pToys[playerid][AccountData[playerid][toySelected]][toy_model],
				pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
				pToys[playerid][AccountData[playerid][toySelected]][toy_x],
				pToys[playerid][AccountData[playerid][toySelected]][toy_y],
				pToys[playerid][AccountData[playerid][toySelected]][toy_z],
				posisi,
				pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
				pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx] = posisi;
			SetPVarInt(playerid, "UpdatedToy", 1);
			//MySQL_SavePlayerToys(playerid);
			
			new minsty[612];
			if(AccountData[playerid][toySelected] == 0)
			{
				minsty = "Topi/Helmet";
			}
			else if(AccountData[playerid][toySelected] == 1)
			{
				minsty = "Kacamata";
			}
			else if(AccountData[playerid][toySelected] == 2)
			{
				minsty = "Aksesoris";
			}
			else if(AccountData[playerid][toySelected] == 3)
			{
				minsty = "Tas/Koper";
			}
			new string[1800], toys[128];
			format(toys, sizeof(toys), ""TCRP"District "WHITE" - Edit Fashion (%s)", minsty);
			format(string, sizeof string, "Pengaturan\tParameter\n");
			format(string, sizeof string, "%s"WHITE"Edit Posisi\t(Khusus PC)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Edit Posisi\t(Khusus Android)\n", string);
			format(string, sizeof string, "%s"WHITE"Ubah Posisi Tulang\t(Bone)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_x]);
			format(string, sizeof string, "%s"WHITE"Sumbu Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_y]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_z]);
			format(string, sizeof string, "%s"WHITE"Rotasi X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rx]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Rotasi Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_ry]);
			format(string, sizeof string, "%s"WHITE"Rotasi Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sx]);
			format(string, sizeof string, "%s"WHITE"Skala Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sy]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			format(string, sizeof string, "%s"WHITE"Hapus\t(Pilih jika anda ingin menghapus permanent)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sembunyikan\t(Jika ingin disembunyikan)\n", string);
			ShowPlayerDialog(playerid, DialogToyEdit, DIALOG_STYLE_TABLIST_HEADERS, toys, string, "Select", "Cancel");
		}
	}
	if(dialogid == DIALOG_TOYPOSRY)
	{
		if(response)
		{
			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				AccountData[playerid][toySelected],
				pToys[playerid][AccountData[playerid][toySelected]][toy_model],
				pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
				pToys[playerid][AccountData[playerid][toySelected]][toy_x],
				pToys[playerid][AccountData[playerid][toySelected]][toy_y],
				pToys[playerid][AccountData[playerid][toySelected]][toy_z],
				pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
				posisi,
				pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry] = posisi;
			SetPVarInt(playerid, "UpdatedToy", 1);
			//MySQL_SavePlayerToys(playerid);
			
			new minsty[612];
			if(AccountData[playerid][toySelected] == 0)
			{
				minsty = "Topi/Helmet";
			}
			else if(AccountData[playerid][toySelected] == 1)
			{
				minsty = "Kacamata";
			}
			else if(AccountData[playerid][toySelected] == 2)
			{
				minsty = "Aksesoris";
			}
			else if(AccountData[playerid][toySelected] == 3)
			{
				minsty = "Tas/Koper";
			}
			new string[1800], toys[128];
			format(toys, sizeof(toys), ""TCRP"District "WHITE" - Edit Fashion (%s)", minsty);
			format(string, sizeof string, "Pengaturan\tParameter\n");
			format(string, sizeof string, "%s"WHITE"Edit Posisi\t(Khusus PC)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Edit Posisi\t(Khusus Android)\n", string);
			format(string, sizeof string, "%s"WHITE"Ubah Posisi Tulang\t(Bone)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_x]);
			format(string, sizeof string, "%s"WHITE"Sumbu Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_y]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_z]);
			format(string, sizeof string, "%s"WHITE"Rotasi X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rx]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Rotasi Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_ry]);
			format(string, sizeof string, "%s"WHITE"Rotasi Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sx]);
			format(string, sizeof string, "%s"WHITE"Skala Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sy]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			format(string, sizeof string, "%s"WHITE"Hapus\t(Pilih jika anda ingin menghapus permanent)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sembunyikan\t(Jika ingin disembunyikan)\n", string);
			ShowPlayerDialog(playerid, DialogToyEdit, DIALOG_STYLE_TABLIST_HEADERS, toys, string, "Select", "Cancel");
		}
	}
	if(dialogid == DIALOG_TOYPOSRZ)
	{
		if(response)
		{
			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				AccountData[playerid][toySelected],
				pToys[playerid][AccountData[playerid][toySelected]][toy_model],
				pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
				pToys[playerid][AccountData[playerid][toySelected]][toy_x],
				pToys[playerid][AccountData[playerid][toySelected]][toy_y],
				pToys[playerid][AccountData[playerid][toySelected]][toy_z],
				pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
				pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
				posisi,
				pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz] = posisi;
			SetPVarInt(playerid, "UpdatedToy", 1);
			//MySQL_SavePlayerToys(playerid);
			
			new minsty[612];
			if(AccountData[playerid][toySelected] == 0)
			{
				minsty = "Topi/Helmet";
			}
			else if(AccountData[playerid][toySelected] == 1)
			{
				minsty = "Kacamata";
			}
			else if(AccountData[playerid][toySelected] == 2)
			{
				minsty = "Aksesoris";
			}
			else if(AccountData[playerid][toySelected] == 3)
			{
				minsty = "Tas/Koper";
			}
			new string[1800], toys[128];
			format(toys, sizeof(toys), ""TCRP"District "WHITE" - Edit Fashion (%s)", minsty);
			format(string, sizeof string, "Pengaturan\tParameter\n");
			format(string, sizeof string, "%s"WHITE"Edit Posisi\t(Khusus PC)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Edit Posisi\t(Khusus Android)\n", string);
			format(string, sizeof string, "%s"WHITE"Ubah Posisi Tulang\t(Bone)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_x]);
			format(string, sizeof string, "%s"WHITE"Sumbu Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_y]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_z]);
			format(string, sizeof string, "%s"WHITE"Rotasi X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rx]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Rotasi Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_ry]);
			format(string, sizeof string, "%s"WHITE"Rotasi Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sx]);
			format(string, sizeof string, "%s"WHITE"Skala Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sy]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			format(string, sizeof string, "%s"WHITE"Hapus\t(Pilih jika anda ingin menghapus permanent)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sembunyikan\t(Jika ingin disembunyikan)\n", string);
			ShowPlayerDialog(playerid, DialogToyEdit, DIALOG_STYLE_TABLIST_HEADERS, toys, string, "Select", "Cancel");
		}
		
	}
	if(dialogid == DIALOG_TOYPOSSX)
	{
		if(response)
		{
			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				AccountData[playerid][toySelected],
				pToys[playerid][AccountData[playerid][toySelected]][toy_model],
				pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
				pToys[playerid][AccountData[playerid][toySelected]][toy_x],
				pToys[playerid][AccountData[playerid][toySelected]][toy_y],
				pToys[playerid][AccountData[playerid][toySelected]][toy_z],
				pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
				pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
				pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
				posisi,
				pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx] = posisi;
			SetPVarInt(playerid, "UpdatedToy", 1);
			//MySQL_SavePlayerToys(playerid);
			
			new minsty[612];
			if(AccountData[playerid][toySelected] == 0)
			{
				minsty = "Topi/Helmet";
			}
			else if(AccountData[playerid][toySelected] == 1)
			{
				minsty = "Kacamata";
			}
			else if(AccountData[playerid][toySelected] == 2)
			{
				minsty = "Aksesoris";
			}
			else if(AccountData[playerid][toySelected] == 3)
			{
				minsty = "Tas/Koper";
			}
			new string[1800], toys[128];
			format(toys, sizeof(toys), ""TCRP"District "WHITE" - Edit Fashion (%s)", minsty);
			format(string, sizeof string, "Pengaturan\tParameter\n");
			format(string, sizeof string, "%s"WHITE"Edit Posisi\t(Khusus PC)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Edit Posisi\t(Khusus Android)\n", string);
			format(string, sizeof string, "%s"WHITE"Ubah Posisi Tulang\t(Bone)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_x]);
			format(string, sizeof string, "%s"WHITE"Sumbu Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_y]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_z]);
			format(string, sizeof string, "%s"WHITE"Rotasi X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rx]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Rotasi Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_ry]);
			format(string, sizeof string, "%s"WHITE"Rotasi Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sx]);
			format(string, sizeof string, "%s"WHITE"Skala Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sy]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			format(string, sizeof string, "%s"WHITE"Hapus\t(Pilih jika anda ingin menghapus permanent)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sembunyikan\t(Jika ingin disembunyikan)\n", string);
			ShowPlayerDialog(playerid, DialogToyEdit, DIALOG_STYLE_TABLIST_HEADERS, toys, string, "Select", "Cancel");
		}
	}
	if(dialogid == DIALOG_TOYPOSSY)
	{
		if(response)
		{
			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				AccountData[playerid][toySelected],
				pToys[playerid][AccountData[playerid][toySelected]][toy_model],
				pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
				pToys[playerid][AccountData[playerid][toySelected]][toy_x],
				pToys[playerid][AccountData[playerid][toySelected]][toy_y],
				pToys[playerid][AccountData[playerid][toySelected]][toy_z],
				pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
				pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
				pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
				posisi,
				pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy] = posisi;
			SetPVarInt(playerid, "UpdatedToy", 1);
			//MySQL_SavePlayerToys(playerid);
			
			new minsty[612];
			if(AccountData[playerid][toySelected] == 0)
			{
				minsty = "Topi/Helmet";
			}
			else if(AccountData[playerid][toySelected] == 1)
			{
				minsty = "Kacamata";
			}
			else if(AccountData[playerid][toySelected] == 2)
			{
				minsty = "Aksesoris";
			}
			else if(AccountData[playerid][toySelected] == 3)
			{
				minsty = "Tas/Koper";
			}
			new string[1800], toys[128];
			format(toys, sizeof(toys), ""TCRP"District "WHITE" - Edit Fashion (%s)", minsty);
			format(string, sizeof string, "Pengaturan\tParameter\n");
			format(string, sizeof string, "%s"WHITE"Edit Posisi\t(Khusus PC)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Edit Posisi\t(Khusus Android)\n", string);
			format(string, sizeof string, "%s"WHITE"Ubah Posisi Tulang\t(Bone)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_x]);
			format(string, sizeof string, "%s"WHITE"Sumbu Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_y]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_z]);
			format(string, sizeof string, "%s"WHITE"Rotasi X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rx]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Rotasi Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_ry]);
			format(string, sizeof string, "%s"WHITE"Rotasi Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sx]);
			format(string, sizeof string, "%s"WHITE"Skala Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sy]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			format(string, sizeof string, "%s"WHITE"Hapus\t(Pilih jika anda ingin menghapus permanent)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sembunyikan\t(Jika ingin disembunyikan)\n", string);
			ShowPlayerDialog(playerid, DialogToyEdit, DIALOG_STYLE_TABLIST_HEADERS, toys, string, "Select", "Cancel");
		}
	}
	if(dialogid == DIALOG_TOYPOSSZ)
	{
		if(response)
		{
			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				AccountData[playerid][toySelected],
				pToys[playerid][AccountData[playerid][toySelected]][toy_model],
				pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
				pToys[playerid][AccountData[playerid][toySelected]][toy_x],
				pToys[playerid][AccountData[playerid][toySelected]][toy_y],
				pToys[playerid][AccountData[playerid][toySelected]][toy_z],
				pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
				pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
				pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
				pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
				posisi);
			
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz] = posisi;
			SetPVarInt(playerid, "UpdatedToy", 1);
			//MySQL_SavePlayerToys(playerid);
			
			new minsty[612];
			if(AccountData[playerid][toySelected] == 0)
			{
				minsty = "Topi/Helmet";
			}
			else if(AccountData[playerid][toySelected] == 1)
			{
				minsty = "Kacamata";
			}
			else if(AccountData[playerid][toySelected] == 2)
			{
				minsty = "Aksesoris";
			}
			else if(AccountData[playerid][toySelected] == 3)
			{
				minsty = "Tas/Koper";
			}
			new string[1800], toys[128];
			format(toys, sizeof(toys), ""TCRP"District "WHITE" - Edit Fashion (%s)", minsty);
			format(string, sizeof string, "Pengaturan\tParameter\n");
			format(string, sizeof string, "%s"WHITE"Edit Posisi\t(Khusus PC)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Edit Posisi\t(Khusus Android)\n", string);
			format(string, sizeof string, "%s"WHITE"Ubah Posisi Tulang\t(Bone)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_x]);
			format(string, sizeof string, "%s"WHITE"Sumbu Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_y]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sumbu Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_z]);
			format(string, sizeof string, "%s"WHITE"Rotasi X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rx]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Rotasi Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_ry]);
			format(string, sizeof string, "%s"WHITE"Rotasi Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_rz]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala X:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sx]);
			format(string, sizeof string, "%s"WHITE"Skala Y:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sy]);
			format(string, sizeof string, "%s"VERONA_ARWIN"Skala Z:\t%f\n", string, pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
			format(string, sizeof string, "%s"WHITE"Hapus\t(Pilih jika anda ingin menghapus permanent)\n", string);
			format(string, sizeof string, "%s"VERONA_ARWIN"Sembunyikan\t(Jika ingin disembunyikan)\n", string);
			ShowPlayerDialog(playerid, DialogToyEdit, DIALOG_STYLE_TABLIST_HEADERS, toys, string, "Select", "Cancel");
		}
	}
	if(dialogid == DIALOG_EDITBONE)
	{
		if(response)
		{
			new weaponid = EditingWeapon[playerid], weaponname[18], string[150];
	 
			GetWeaponName(weaponid, weaponname, sizeof(weaponname));
		   
			WeaponSettings[playerid][weaponid - 22][Bone] = listitem + 1;

			ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil mengubah posisi tulang untuk %s", weaponname));
			// SendClientMessageEx(playerid, -1, ""GREEN"[!] "WHITE"You have successfully changed the bone of your %s.", weaponname);
		   
			mysql_format(g_SQL, string, sizeof(string), "INSERT INTO weaponsettings (Owner, WeaponID, Bone) VALUES ('%d', %d, %d) ON DUPLICATE KEY UPDATE Bone = VALUES(Bone)", AccountData[playerid][pID], weaponid, listitem + 1);
			mysql_tquery(g_SQL, string);
		}
		EditingWeapon[playerid] = 0;
	}
	if(dialogid == DIALOG_DYNAMIC_HELP)
	{
		if(!response) return 1;
		if(AccountData[playerid][pAdmin] < 1) return PermissionError(playerid);
		switch(listitem)
		{
			case 0:// Actor
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Actor",
				"Perintah\tKeterangan\n\
				/addactor [skinid] [name]\tMembuat Actor\n\
				"GRAY"/editactor [id] [model] [new model]\t"GRAY"Mengganti Skin Model Actor\n\
				/editactor [id] [name] [new name]\tMengganti Nama Actor\n\
				"GRAY"/editactor [id] [pos]\t"GRAY"Mengubah posisi letak Actor\n\
				/editactor [id] [anim] [anim index]\tMengubah Animasi Actor\n\
				"GRAY"/editactor [id] [clearanim]\t"GRAY"Menghapus Animasi Pada Actor\n\
				/gotoactor [id]\tTeleportasi ke Actor\n\
				"GRAY"/destroyactor [id]\t"GRAY"Menghapus Dynamic Actor", "Tutup", "");
			}
			case 1: // Dynamic Rental
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Rents",
				"Perintah\tKeterangan\n\
				/addrent\tMenambahkan Dynamic Rents\n\
				"GRAY"/editrent [id] [location]\t"GRAY"Mengubah Posisi Letak Dynamic Rents\n\
				/editrent [id] [delete]\tMenghapus Dynamic Rents\n\
				"GRAY"/editrent [id] [spawnpos]\t"GRAY"Menetapkan posisi spawn kendaraan Rents", "Tutup", "");
			}
			case 2: // Dynamic Door
			{
				static str[4046];

				format(str, sizeof(str), "Perintah\tKeterangan\n\
				/createdoor [nama]\tMembuat Dynamic Door\n\
				"GRAY"/gotodoor [id]\t"GRAY"Teleportasi Ke Dynamic Door\n\
				/editdoor [id] [location]\tMengubah Posisi Door Exterior\n\
				"GRAY"/editdoor [id] [interior]\t"GRAY"Mengubah Posisi Door Interior\n\
				/editdoor [id] [password] [input]\tMemberi Password Dynamic Door\n\
				"GRAY"/editdoor [id] [locked] [0/1]\t"GRAY"Membuka atau Mengunci Dynamic Door\n\
				/editdoor [id] [name] [new name]\tMengubah Nama Pada Dynamic Door\n\
				"GRAY"/editdoor [id] [admin] [level] [1 - 7]\t"GRAY"Membuat Akses Dynamic Door Khusus Admin\n\
				/editdoor [id] [vip]\tMembuat Dynamic VIP Door\n\
				"GRAY"/editdoor [id] [faction] [id faction]\t"GRAY"Membuat Akses Dynamic Door Khusus Faction\n\
				/editdoor [id] [family] [id family]\tMembuat Akses Dynamic Door Khusus Family\n\
				"GRAY"/editdoor [id] [garage] [0 - 1]\t"GRAY"Membuat Akses Door Menjadi Garage\n\
				/editdoor [id] [iconmap] [0 - 63]\tMembuat Icon Dynamic Door Pada Map\n\
				"GRAY"/editdoor [id] [delete]\t"GRAY"Menghapus Keberadaan Dynamic Door");
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Door", str, "Tutup", "");
			}
			case 3: // Fivem Label
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Label",
				"Perintah\tKeterangan\n\
				/addlabel [text]\tMenambahkan label menggunakan Text\n\
				"GRAY"/gotolabel [id]\t"GRAY"Teleportasi ke Dynamic Label\n\
				/removelabel [id]\tMenghapus Dynamic Label", "Tutup", "");
			}
			case 4: //public garage
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Public Garage",
				"Perintah\tKeterangan\n\
				/addgarkot\tMenambah Dynamic Garasi Umum\n\
				"GRAY"/editgarkot [id] [name]\t"GRAY"Mengubah nama Garasi Umum\n\
				/editgarkot [id] [location]\tMengubah Posisi letak Garasi Umum\n\
				"GRAY"/editgarkot [id] [spawnpos]\t"GRAY"Mengubah posisi Spawn kendaraan Garasi Umum", "Tutup", "");
			}
			case 5: //Tong Sampah
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Trash",
				"Perintah\tKeterangan\n\
				/addtrash\tMembuat Dynamic Trash\n\
				"GRAY"/edittrash [id] [model] [model id]\t"GRAY"Mengubah Object ID Dynamic Trash\n\
				/edittrash [id] [position]\tMengubah Posisi Dynamic Trash\n\
				"GRAY"/edittrash [id] [delete]\t"GRAY"Menghapus Dynamic Trash\n\
				/gototrash [id]\tTeleportasi ke Dynamic Trash", "Tutup", "");
			}
			case 6: //Dynamic ATM
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic ATM",
				"Perintah\tKeterangan\n\
				/createatm\tMembuat Dynamic ATM\n\
				"GRAY"/editatm [id]\t"GRAY"Mengedit posisi letak Dynamic ATM\n\
				/gotoatm [id]\tTeleportasi ke Dynamic ATM\n\
				"GRAY"/removeatm [id]\t"GRAY"Menghapus Dynamic ATM", "Tutup", "");
			}
			case 7: //Kanabis
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Ladang",
				"Perintah\tKeterangan\n\
				/addkanabis\tMembuat Dynamic Kanabis\n\
				"GRAY"/editkanabis [id]\t"GRAY"Mengedit posisi letak Dynamic Kanabis\n\
				/gotokanabis [id]\tTeleportasi ke Dynamic Kanabis\n\
				"GRAY"/removekanabis [id]\t"GRAY"Menghapus Dynamic Kanabis", "Tutup", "");
			}
			case 8: //Rampok Warung
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Robbery",
				"Perintah\tKeterangan\n\
				/createrobber\tMembuat Dynamic Rampok Warung\n\
				"GRAY"/editrobbery [id]\t"GRAY"Mengedit posisi letak Dynamic Rampok Warung\n\
				/gotorobbery [id]\tTeleportasi ke Dynamic Rampok Warung\n\
				"GRAY"/removerobbery [id]\t"GRAY"Menghapus Dynamic Rampok Warung", "Tutup", "");
			}
			case 9: //Warung
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Robbery",
				"Perintah\tKeterangan\n\
				/addwarung [type 1 - 3]\tMembuat Dynamic Warung Dengan Pilihan Type\n\
				"GRAY"/gotowarung [id]\t"GRAY"Teleportasi ke Dynamic Warung\n\
				/removewarung [id]\tMenghapus Dynamic Warung", "Tutup", "");
			}
			case 10: //Hunting
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Hunting",
				"Perintah\tKeterangan\n\
				/adddeer\tMembuat Dynamic Rusa\n\
				"GRAY"/editdeer [id]\t"GRAY"Mengedit posisi letak Dynamic Rusa\n\
				/gotodeer [id]\tTeleportasi ke Dynamic Rusa\n\
				"GRAY"/removedeer [id]\t"GRAY"Menghapus Dynamic Rusa", "Tutup", "");
			}
			case 11: //Gudang
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Gudang",
				"Perintah\tKeterangan\n\
				/addgudang [nama gudang] [harga sewa 30 hari]\tMenambah Dynamic Gudang\n\
				"GRAY"/gotogudang [id]\t"GRAY"Teleportasi ke Dynamic Gudang\n\
				/removegudang [id]\tMenghapus Dynamic Gudang", "Tutup", "");
			}
			case 12: //Garasi Families
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Gudang",
				"Perintah\tKeterangan\n\
				/addfamgarkot\tMenambah Dynamic Garasi Families\n\
				"GRAY"/editfamgarkot [id] [famid] [id families]\t"GRAY"Menetapkan Garasi itu Milik Families ID Berapa\n\
				/editfamgarkot [id] [position]\tMengubah Letak Posisi Dynamic Garasi Families\n\
				"GRAY"/editfamgarkot [id] [spawnpos]\t"GRAY"Mengubah posisi Spawn kendaraan Garasi Families\n\
				/editfamgarkot [id] [delete]\tMenghapus Dynamic Garasi Families\n\
				"GRAY"/gotofamgarkot [id]\t"GRAY"Teleportasi ke Dynamic Garasi Families", "Tutup", "");
			}
			case 13: //Dynamic Rumah
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Houses",
				"Perintah\tKeterangan\n\
				/addhouse [type]\tMenambahkan Dynamic Rumah Berdasarkan Type\n\
				"GRAY"/edithouse [id] [garage]\t"GRAY"Menambahkan Garasi Pada Dynamic House\n\
				/edithouse [id] [garagespawn]\tMengubah posisi Spawn Dynamic Garasi House\n\
				"GRAY"/edithouse [id] [garageremove]\t"GRAY"Menghapus Garasi pada Dynamic House\n\
				/edithouse [id] [type\tMengubah type Dynamic House\n\
				"GRAY"/edithouse [id] [delete]\t"GRAY"Menghapus Dynamic House\n\
				/gotohouse [id]\tTeleportasi ke Dynamic House", "Tutup", "");
			}
			case 14: //Dynamic Map Icon
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Icon",
				"Perintah\tKeterangan\n\
				/addicon [icon id]\tMenambah Dynamic Map Icon Berdasarkan Icon ID\n\
				"GRAY"/destroyicon [id]\t"GRAY"Menghapus Dynamic Map Icon", "Tutup", "");
			}
			case 15: //Dynamic Button
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Buttons",
				"Perintah\tKeterangan\n\
				/addbutton\tMenambah Dynamic Button\n\
				"GRAY"/editbutton [id] [buttonpos]\t"GRAY"Mengubah posisi letak Dynamic Button\n\
				/editbutton [id] [doormodel] [model id]\tMenambah Pintu pada Dynamic Button\n\
				"GRAY"/editbutton [id] [close]\t"GRAY"Mengubah letak pintu untuk posisi tertutup\n\
				/editbutton [id] [open]\tMengubah letak pintu untuk posisi terbuka\n\
				"GRAY"/editbutton [id] [speed] [speed]\t"GRAY"Menetapkan seberapa cepat/lambat pintu terbuka/tertutup\n\
				/editbutton [id] [faction] [faction id]\tMenetapkan bahwa Dynamic tersebut hanya dapat diakses Faction tertentu\n\
				"GRAY"/editbutton [id] [family] [family id]\t"GRAY"Menetapkan bahwa Dynamic tersebut hanya dapat diakses Family tertentu\n\
				/removebutton [id]\tMenghapus dynamic button", "Tutup", "");
			}
			case 16: // Object
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Object",
				"Perintah\tKeterangan\n\
				/createobject [model id]\tMenambah suatu object berdasarkan model yang anda input\n\
				"GRAY"/editobject [id object]\t"GRAY"Untuk mengedit posisi letak object tersebut\n\
				/clone [id object]\tUntuk mengclone object yang ingin anda cloning\n\
				"GRAY"/deleteobject\t"GRAY"Untuk menghapus object yang sudah dibuat dari server\n\
				/oswap [id object] [model id]\tUntuk mengubah model object yang sudah dibuat", "Tutup", "");
			}
			case 17: // Uranium
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dynamic Object",
				"Perintah\tKeterangan\n\
				/adduranium\tUntuk menambahkan Dynamic Uranium\
				\n"GRAY"/edituranium [id] [delete]\t"GRAY"Untuk menghapus Dynamic Uranium\
				\n/edituranium [id] [pos]\tUntuk mengedit posisi Dynamic Uranium", "Tutup", "");
			}
		}
	}
	if(dialogid == DIALOG_ADMIN_HELP)
	{
		if(!response) return 1;
		switch(listitem)
		{
			case 0: // Trial & The Stars
			{
				if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Trial Admin dan The Stars!");

				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Trial Admin",
				"Perintah\tKeterangan\n\
				/a\tAkses Chat Staff\n\
				"GRAY"/aduty\t"GRAY"On Duty Sebagai Admin / The Stars\n\
				/ans\tMenjawab pertanyaan yang ada di server\n\
				"GRAY"/ar\t"GRAY"Menjawab report yang ada di server\n\
				/asks\tMelihat list pertanyaan yang ada di server\n\
				"GRAY"/reports\t"GRAY"Melihat list report yang ada di server\n\
				/spec\tMemantau player\n\
				"GRAY"/astats\t"GRAY"Melihat stats player\n\
				/ostats\tMelihat stats player (offline)\n\
				"GRAY"/checkucp\t"GRAY"Melihat UCP player beserta list karakter yang dimiliki\n\
				/avehlist\tMelihat list kendaraan yang dimiliki player\n\
				"GRAY"/ntag\t"GRAY"Lihat nickname dan UCP semua player\n\
				/gotoveh\tTeleportasi ke kendaraan\n\
				"GRAY"/getveh\t"GRAY"Menarik kendaraan\n\
				/gotols\tTeleportasi ke Los Santos\n\
				"GRAY"/goto\t"GRAY"Teleportasi ke player\n\
				/gethere\tMenarik player lain\n\
				"GRAY"/getip\t"GRAY"Mendapatkan IP player\n\
				/sendto\tKirim player ke suatu tempat\n\
				"GRAY"/dveh\t"GRAY"Hancurkan kendaraan (asuransikan)\n\
				/kick\tMenendang player dari server\n\
				"GRAY"/slap\t"GRAY"Slap player\n\
				/ainv\tCek Inventory Player\n\
				"GRAY"/jail\t"GRAY"Penjarakan player\n\
				/unjail\tMenghapus status jail player\n\
				"GRAY"/arevive\t"GRAY"Menghidupkan player pingsan\n\
				/takeoutveh\tMenspawn paksa kendaraan yang Despawned (Bukan untuk TheStars)", "Tutup", "");
			}
			case 1: //AL2
			{
				if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Helper!");
				
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Helper",
				"Perintah\tKeterangan\n\
				/makequiz\tMembuat quiz server\n\
				"GRAY"/togooc\t"GRAY"Membuka Chat Global Server\n\
				/unfreeze\tMembuat karakter tidak freezing\n\
				"GRAY"/freeze\t"GRAY"Membekukan player / freezing\n\
				/reviveall\tMenghidupkan semua player yang pingsan\n\
				"GRAY"/owarn\t"GRAY"Memberikan warning ke player (offline)\n\
				/ojail\tPenjarakan player (offline)\n\
				"GRAY"/ann\t"GRAY"Membuat Annoucement di layar semua pemain\n\
				/banip\tMemblokir IP Player dari server\n\
				"GRAY"/unbanip\t"GRAY"Menghapus status Blokir IP Player", "Tutup", "");
			}
			case 2:// AL3
			{
				if(AccountData[playerid][pAdmin] < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Admin I!");
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Admin I",
				"Perintah\tKeterangan\n\
				/makewargaoff\tMembuat status Faction dan Families menjadi warga (offline)\n\
				"GRAY"/makewarga\t"GRAY"Membuat status Faction dan Families menjadi warga\n\
				/near\tMelihat ID Dynamic Object disekitar\n\
				"GRAY"/peject\t"GRAY"Menendang paksa player dari kendaraan\n\
				/acuff\tMemborgol player\n\
				"GRAY"/auncuff\t"GRAY"Melepaskan borgol player\n\
				/ban\tMembanned account player dari server\n\
				"GRAY"/unban\t"GRAY"Menghapus status banned player dari server\n\
				/unbanucp\tMenghapus status banned UCP player dari server\n\
				"GRAY"/sethp\t"GRAY"Mengeset jumlah darah merah player\n\
				/sethpall\tMengeset jumlah darah merah semua player online\n\
				"GRAY"/setam\t"GRAY"Mengeset jumlah darah putih player\n\
				/afix\tMemperbaiki kesehatan kendaraan\n\
				"GRAY"/setskin\t"GRAY"Mengubah model skin player\n\
				/reloadweap\tMereload weapon player jika tidak ada / tidak terload\n\
				"GRAY"/resetweap\t"GRAY"Mereset semua senjata milik player\n\
				/setstress\tMengeset jumlah stress player\n\
				"GRAY"/setstressall\t"GRAY"Mengeset jumlah stress semua player online\n\
				/sethbe\tMengeset jumlah lapar haus player\n\
				"GRAY"/sethbeall\t"GRAY"Mengeset jumlah lapar haus semua player online\n\
				/takemoney\tMengambil uang player\n\
				"GRAY"/explode\t"GRAY"Meledakkan player", "Tutup", "");
			}
			case 3: //AL4
			{
				if(AccountData[playerid][pAdmin] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Admin II!");
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Admin II",
				"Perintah\tKeterangan\n\
				/ntag\tMemperlihatkan Name Tag disertai Nama, UCP, ID, Darah, Armour\n\
				"GRAY"/aduty\t"GRAY"Untuk mulai tugas menjadi administrator\n\
				/arevive\tMenghidupkan pemain yang pingsan\n\
				"GRAY"/sethpall\t"GRAY"Menetapkan tingkat health pada semua pemain online\n\
				/setstressall\tMenetapkan tingkat stress pada semua pemain online\n\
				"GRAY"/setvw\t"GRAY"Menetapkan virtual world id pemain\n\
				/setint\tMenetapkan interior id pemain\n\
				"GRAY"/fixes\t"GRAY"Melihat Fixme request pemain\n\
				/asks\tMelihat list pertanyaan pada server\n\
				"GRAY"/reports\t"GRAY"Melihat list laporan pada server\n\
				/reviveall\tMenghidupkan semua pemain yang pingsan\n\
				"GRAY"/sethp\t"GRAY"Menetapkan tingkat health kepada pemain\n\
				/setbone\tMenetapkan tingkat kesehatan tulang pemain\n\
				"GRAY"/sethbe\t"GRAY"Menetapkan Lapar Haus Pemain\n\
				/sethbeall\tMenetapkan lapar harus semua pemain online\n\
				"GRAY"/takemoney\t"GRAY"Mengambil uang pemain\n\
				/dveh\tMenghancurkan kendaraan ke asuransi\n\
				"GRAY"/setam\t"GRAY"Menetapkan tingkat armour kepada pemain\n\
				/setskin\tMengubah model skin id kepada pemain\n\
				"GRAY"/explode\t"GRAY"Memberikan efek ledakan kepada pemain\n\
				/clearask\tMenghapus semua pertanyaan pada sever\n\
				"GRAY"/clearreports\t"GRAY"Menghapus semua laporan pada server\n\
				/setmoney\tMenetapkan jumlah uang pemain\n\
				"GRAY"/givemoney\t"GRAY"Memberikan uang kepada pemain\n\
				/givemoneyall\tMemberikan uang kepada semua pemain online\n\
				"GRAY"/dpv\t"GRAY"Menghapus kendaraan player dari database", "Tutup", "");
			}
			case 4: // AL5
			{
				if(AccountData[playerid][pAdmin] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Admin III!");
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Admin III",
				"Perintah\tKeterangan\n\
				/setfaction\tMenjadikan status player menjadi Faction tertentu\n\
				"GRAY"/playnearsong\t"GRAY"Memutar musik dan didengar player di sekitar\n\
				/fightstyle\tMengubah gaya berkelahi\n\
				"GRAY"/addkompensasi\t"GRAY"Menambahkan kompensasi server\n\
				/expiredallkompensasi\tMenghapus semua kompensasi yang ada di server\n\
				"GRAY"/restart\t"GRAY"Merestart server\n\
				/avehall\tMembuat Asuransi Keliling sesuai waktu yang ditentukan\n\
				"GRAY"/oreco\t"GRAY"Mereset ekonomi player (offline)\n\
				/reco\tMereset ekonomi player\n\
				"GRAY"/playsong\t"GRAY"Memutar musik untuk didengar sendiri\n\
				/saveallplayer\tMenyimpan semua data player ke database", "Tutup", "");
			}
			case 5: //
			{
				if(AccountData[playerid][pAdmin] < 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Pengurus!");
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Pengurus",
				"Perintah\tKeterangan\n\
				/setadminname\tMengubah nama Administrator player\n\
				"GRAY"/setadmin\t"GRAY"Mengeset level Administrator player\n\
				/kickall\tMenendang semua player online dari server\n\
				"GRAY"/panel\t"GRAY"Setting Kebutuhan server\n\
				/setvip\tMengeset level Vip player\n\
				"GRAY"/makepv\t"GRAY"Membuat kendaraan player", "Tutup", "");
			}
			case 6: //management
			{
				if(AccountData[playerid][pAdmin] < 7) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Management!");
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Management",
				"Perintah\tKeterangan\n\
				/dynhelp\tSemua dapat anda akses", "Tutup", "");
			}
			case 7: //goodside
			{
				if(AccountData[playerid][pAdmin] < 7 && AccountData[playerid][pHandleGoodside] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Management & Handle Goodside!");
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Management",
				"Perintah\tKeterangan\n\
				/setfaction\tAnda dapat mengeset player menjadi faction dengan batasan memberikan 2 rank", "Tutup", "");
			}
			case 8: //badside
			{
				if(AccountData[playerid][pAdmin] < 7 && AccountData[playerid][pHandleBadside] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Management & Handle Badside!");
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Management",
				"Perintah\tKeterangan\n\
				/famcreate\tAnda dapat membuat sebuah family\n\
				/famedit\tAnda dapat mengeset semua kecuali items dan juga senjata\n\
				/gotofamdoor\tAnda dapat teleportasi ke family yang ingin anda tujus\n\
				/famdelete\tAnda dapat menghapus family\n\
				/setfamilies\tAnda dapat Mengset player menjadi anggota family\n\
				/setskin\tuntuk menetapkan skin player\n\
				/setkevlar\tuntuk memberikan kevlar ke player", "Tutup", "");
			}
			case 9: //admin girl
			{
				if(AccountData[playerid][pAdmin] < 7 && AccountData[playerid][pAdminGirl] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Management & Admin Girl!");
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Admin Girl",
				"Perintah\tKeterangan\n\
				/setbenefitgirl\tUntuk memberikan benefit girl sesuai di web discord\n\
				Memiliki Akses yang sama seperti Admin II", "Tutup", "");
			}
		}
	}
	if(dialogid == DIALOG_SETAMOUNT)
	{
		if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");

		if(isnull(inputtext))
		{
			ShowPlayerDialog(playerid, DIALOG_SETAMOUNT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Set Amount",
			"Error: Tidak dapat diisi kosong!\nMohon masukkan berapa jumlah item yang akan diberikan:", "Set", "Batal");
			return 1;
		}

		if(!IsNumeric(inputtext))
		{
			ShowPlayerDialog(playerid, DIALOG_SETAMOUNT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Set Amount",
			"Error: Hanya dapat diisi angka!\nMohon masukkan berapa jumlah item yang akan diberikan:", "Set", "Batal");
			return 1;
		}

		if(strval(inputtext) < 1) 
		{
			ShowPlayerDialog(playerid, DIALOG_SETAMOUNT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Set Amount",
			"Error: Jumlah tidak valid!\nMohon masukkan berapa jumlah item yang akan diberikan:", "Set", "Batal");
			return 1;
		}

		AccountData[playerid][pAmountInv] = strval(inputtext);
		PlayerTextDrawSetString(playerid, inv::textdraw[playerid][43], inputtext);
		PlayerTextDrawShow(playerid, inv::textdraw[playerid][43]);
	}
	if(dialogid == DIALOG_MEMBERI)
	{
		if(!response)
		{
			return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
		}
		new itemid = AccountData[playerid][pSelectItem];
		new amount = AccountData[playerid][pAmountInv];
		new model = InventoryData[playerid][itemid][invModel];
		static itemname[125];
		strunpack(itemname, InventoryData[playerid][itemid][invItem]);

		new targetid = NearestPlayer[playerid][listitem];
		if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
		if(GetTotalWeightFloat(targetid) > 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory pemain tersebut penuh!");
		if(Inventory_Items(targetid) >= MAX_INVENTORY) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki slot kosong pada inventorynya!");
		if(itemid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item!");
		if(amount > InventoryData[playerid][itemid][invQuantity]) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda tidak memiliki %s sebanyak itu!", itemname));

		Inventory_Remove(playerid, itemname, amount);
		Inventory_Add(targetid, itemname, model, amount);

		ShowItemBox(playerid, sprintf("Removed %dx", amount), itemname, model);
		ShowItemBox(targetid, sprintf("Received %dx", amount), itemname, model);
		Inventory_Close(playerid);
	}
	if(dialogid == DIALOG_GOPAYWITHDRAW)
	{
		if(!response) return true;
		new amount = floatround(strval(inputtext));
		if(amount > AccountData[playerid][pSaldoGopay]) return ShowPlayerDialog(playerid, DIALOG_GOPAYWITHDRAW, DIALOG_STYLE_INPUT, ""TCRP"District "WHITE" - Tarik Saldo Gopay", "ERROR: Anda tidak memiliki saldo sebanyak itu\n\nInput jumlah saldo gopay yang ingin kamu tarik:", "Submit", "Cancel");
		if(amount < 1) return ShowPlayerDialog(playerid, DIALOG_GOPAYWITHDRAW, DIALOG_STYLE_INPUT, ""TCRP"District "WHITE" - Tarik Saldo Gopay", "ERROR: Anda memasukan angka yang tidak Valid!\n\nInput jumlah saldo gopay yang ingin kamu tarik:", "Submit", "Cancel");

		else
		{
			new query[512];
			AccountData[playerid][pSaldoGopay] -= amount;
			GiveMoney(playerid, amount);
			mysql_format(g_SQL, query, sizeof(query), "UPDATE player_characters SET Char_Money=%d,Char_Gopay=%d WHERE pID=%d", AccountData[playerid][pMoney], AccountData[playerid][pSaldoGopay], AccountData[playerid][pID]);
			mysql_tquery(g_SQL, query);

			new str[100];
			format(str, sizeof(str), "Berhasil menarik saldo gopay sejumlah ~g~%s", FormatMoney(amount));
			ShowTDN(playerid, NOTIFICATION_SUKSES, str);
		}
	}
	if(dialogid == DialogElist)
	{
		if(!response) return 0;
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new str[15000];
					
					strcat(str, "liptang\nliptang2\nliptang3\nliptang4\nrokok\nrokok2\nrokok3\nmedis\nmedis2\n");
					strcat(str, "cium\ncium2\ncium3\ncium4\ncium5\ncium6\njoget\njoget2\njoget3\njoget4\njoget5\n");
					strcat(str, "joget6\njoget7\njoget8\njoget9\njoget10\nonani\nonani2\nonani3\nangtang\n");
					strcat(str, "baseball\nbaseball2\nbaseball3\nbaseball4\nbaseball5\ntampar\n");
					strcat(str, "bartender\nbartender2\nbartender3\nbartender4\nbartender5\nbartender6\nbartender7\nbartender8\n");
					strcat(str, "geledah\nsantai\nsantai2\nsantai3\nsantai4\nsantai5\ngatal\ngang\ngang2\ngang3\ngang4\ngang5\ngang6\ngang7\ngang8\n");
					strcat(str, "bicara\nbicara2\nbicara3\nbicara4\nbicara5\nbicara6\n");
					strcat(str, "angkat\nangkat2\nangkat3\nangkat4\nkesakitan\nturu\nturu2\nlompat\bmuntah\n");
					strcat(str, "sorak\nsorak2\nsorak3\nsorak4\nsorak5\nsorak6\nsorak7\nsorak8\n");
					strcat(str, "lambai\nlambai2\nlambai3\nkerja\nkerja2\nkerja3\nkerja4\nkerja5\nkerja6\ntusuk\ntusuk2\ntertusuk\n");
					strcat(str, "dj\ndj2\ndj3\nnodong\nnodong2\nnodong3\nnodong4\nkungfu\nnunduk\nnunjuk\nmabuk\nnangis\nlelah\nlelah2\n");
					strcat(str, "duduk\nduduk2\nduduk3\nduduk4\nduduk5\nduduk6\njarteng\n");
					strcat(str, "pusing\nped\nped2\nped3\nped4\nped5\nped6\nped7\nped8\nped9\nped10\nped11\nped12\nped13\nped14\nped15\nped15\nkencing\nx\n");
					ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - List Animasi", str, "Close", "");
				}
				case 1:
				{
					ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Emote Property",
					"TV\
					\nBan\
					\nBesbol\
					\nBasket\
					\nBunga\
					\nBox\
					\nBox1\
					\nBox2\
					\nBox3\
					\nBox 4\
					\nBendera\
					\nBendera2\
					\nBumper\
					\nGuitar\
					\nKamera\
					\nKamera2\
					\nKamera3\
					\nKursi\
					\nKursi2\
					\nNitro\
					\nMic", "Close", "");
				}
				case 2:
				{
					new str[512];
					format(str, sizeof(str), "Peluk\n"GRAY"Salam\n");
					ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- List Animasi Interaksi", str, "Close", "");
				}
			}
		}
	}
	if(dialogid == DIALOG_VERIFYCODE)
	{
		if(!response) return KickEx(playerid);

		new shstr[525];
		if(isnull(inputtext))
		{
			format(shstr, sizeof(shstr), ""WHITE"Error: Tidak dapat diisi kosong!\n"WHITE"Selamat datang di "TCRP"District \n"WHITE"UCP Ini telah terdaftar!\nNama UCP: "LIGHTGREEN"%s\
			\n"WHITE"Version: "TCRP""TEXT_GAMEMODE"\n"YELLOW"(Silahkan masukkan PIN yang dikirimkan oleh Bot District  ke Discord anda dibawah ini):", AccountData[playerid][pUCP]);
			ShowPlayerDialog(playerid, DIALOG_VERIFYCODE, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Verifikasi Akun",
			shstr, "Input", "Batal");
			return 1;
		}
		
		if(!IsNumeric(inputtext))
		{
			format(shstr, sizeof(shstr), ""WHITE"Error: Hanya dapat diisi angka!\n"WHITE"Selamat datang di "TCRP"District \n"WHITE"UCP Ini telah terdaftar!\nNama UCP: "LIGHTGREEN"%s\
			\n"WHITE"Version: "TCRP""TEXT_GAMEMODE"\n"YELLOW"(Silahkan masukkan PIN yang dikirimkan oleh Bot District  ke Discord anda dibawah ini):", AccountData[playerid][pUCP]);
			ShowPlayerDialog(playerid, DIALOG_VERIFYCODE, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Verifikasi Akun",
			shstr, "Input", "Batal");
			return 1;
		}

		if(strval(inputtext) == AccountData[playerid][pVerifyCode])
		{
			format(shstr, sizeof(shstr), ""WHITE"Selamat datang di "TCRP"District "WHITE"\nUCP ini telah terdaftar!\nNama UCP: "LIGHTGREEN"%s\n"WHITE"Version: "TCRP""TEXT_GAMEMODE"\n"YELLOW"(Silahkan untuk membuat password baru dibawah ini):", AccountData[playerid][pUCP]);
			ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, ""TCRP"District  "WHITE"- Pembuatan Password",
			shstr, "Input", "Batal");
			printf("[debug] OnPlayerVerifyCode(PID: %d UCP: %s) terpanggil", playerid, ReturnName(playerid));
			return 1;
		}

		format(shstr, sizeof(shstr), ""WHITE"Selamat datang di "TCRP"District \n"WHITE"UCP Ini telah terdaftar!\nNama UCP: "LIGHTGREEN"%s\
		\n"WHITE"Version: "TCRP""TEXT_GAMEMODE"\n"YELLOW"(Silahkan masukkan PIN yang dikirimkan oleh Bot District  ke Discord anda dibawah ini):", AccountData[playerid][pUCP]);
		return ShowPlayerDialog(playerid, DIALOG_VERIFYCODE, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Verifikasi Akun",
		shstr, "Input", "Batal");
	}
	/*if(dialogid == DialogMyVeh)
	{
		if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
		ShowPlayerDialog(playerid, DialogTrackMyVeh, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Lacak Kendaraan",
		""WHITE"Cari kendaraan\n"YELLOW"(Masukkan VID Kendaraan yang ingin anda cari):", "Input", "Batal");
		return 1;
	}*/
	if(dialogid == DialogMyVeh)
	{
		if(!response) return Info(playerid, "Anda telah membatalkan pilihan");
		SetPVarInt(playerid, "ClickVehicle", ReturnPlayerVehID(playerid, (listitem+1)));

		ShowPlayerDialog(playerid, DIALOG_MYV_MENU, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Kendaraan Saya",
			"Cari Kendaraan\n"GRAY"Detail Kendaraan\n"WHITE"Panggil Valet ($1,000)", "Pilih", "Batal");
		return 1;
	}
	if(dialogid == DIALOG_MYV_MENU)
	{
		if(!response) return Info(playerid, "Anda telah membatalkan pilihan");
		switch(listitem)
		{
			case 0: // cari Kendaraan
			{
				ShowPlayerDialog(playerid, DialogTrackMyVeh, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Lacak Kendaraan",
				""WHITE"Cari kendaraan\n"YELLOW"(Masukkan VID Kendaraan yang ingin anda cari):", "Input", "Batal");
			}
			case 1: // Detail kendaraan
			{
				static strings[3048], Float:vHealth;
				new vehid = GetPVarInt(playerid, "ClickVehicle");
				if(!IsValidVehicle(PlayerVehicle[vehid][pVehPhysic])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut belum spawn!");
				if(GetNearestVehicle(playerid) != PlayerVehicle[vehid][pVehPhysic]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak didekat kendaraan yang ingin anda cek detailnya!");

				GetVehicleHealth(PlayerVehicle[vehid][pVehPhysic], vHealth);

				format(strings, sizeof(strings), ""DEEPSKYBLUE1"Utama\
				\n"WHITE"VID (Database):"YELLOW" %d\
				\n"WHITE"Kendaraan:"YELLOW" %s\
				\n"WHITE"Nomor Plat"YELLOW" %s\
				\n\n"DEEPSKYBLUE1"Upgrade:\
				\n"WHITE"- Engine Upgrade %s\
				\n"WHITE"- Body Upgrade %s\
				\n\n"DEEPSKYBLUE1"Selebihnya\
				\n"WHITE"Fuel Capacity:"YELLOW" %d.0/100.0\
				\n"WHITE"Max Vehicle Health:"YELLOW" %.1f/%s\
				\n"WHITE"Vehicle Body Health:"YELLOW" %.1f/1000.0\
				\n\nMasukkan Player ID atau Nama Player untuk memperlihatkan informasi ini kepadanya"LIGHTGREEN" (Input)", PlayerVehicle[vehid][pVehID], GetVehicleName(PlayerVehicle[vehid][pVehPhysic]), PlayerVehicle[vehid][pVehPlate],
				(PlayerVehicle[vehid][pVehEngineUpgrade] != 1) ? ""RED"None" : ""GREEN"Upgrade", (PlayerVehicle[vehid][pVehBodyUpgrade] != 3) ? ""RED"None" : ""GREEN"Upgrade",
				GetFuel(PlayerVehicle[vehid][pVehPhysic]), vHealth, (PlayerVehicle[vehid][pVehEngineUpgrade] != 1) ? "1000.0" : "2000.0", PlayerVehicle[vehid][pVehBodyRepair]);
				ShowPlayerDialog(playerid, DIALOG_VEHICLE_DETAIL, DIALOG_STYLE_INPUT, sprintf(""TCRP"District  "WHITE"- %s Vehicle Details", AccountData[playerid][pName]), strings, "Submit", "Batal");
			}
			case 2: //VALET
			{
				new vehid = GetPVarInt(playerid, "ClickVehicle");
				new strings[128];
				
				format(strings, sizeof(strings), ""WHITE"Apakah Anda yakin ingin memanggil valet untuk kendaraan "YELLOW"%s"WHITE"?\n\nBiaya: "GREEN"$1,000", GetVehicleName(PlayerVehicle[vehid][pVehPhysic]));
				ShowPlayerDialog(playerid, DIALOG_VALET_CONFIRM, DIALOG_STYLE_MSGBOX, ""TCRP"District "WHITE"- Konfirmasi Valet", strings, "Ya", "Batal");
			}
		}
	}
	if(dialogid == DIALOG_VALET_CONFIRM)
	{
		if(!response) return 1;

		new vehid = GetPVarInt(playerid, "ClickVehicle");
		
		if(AccountData[playerid][pMoney] < 1000)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang Anda tidak cukup ($1,000)!");
		new VID = PlayerVehicle[vehid][pVehPhysic];

		if(!IsValidVehicle(VID))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan harus di-spawn terlebih dahulu melalui garasi!");

		new Float:v_PosX, Float:v_PosY, Float:v_PosZ, Float:v_Angle;
		GetPlayerPos(playerid, v_PosX, v_PosY, v_PosZ);
		GetPlayerFacingAngle(playerid, v_Angle);
		
		v_PosX += (3.5 * floatsin(-v_Angle, degrees));
		v_PosY += (3.5 * floatcos(-v_Angle, degrees));

		SetVehiclePos(VID, v_PosX, v_PosY, v_PosZ);
		SetVehicleZAngle(VID, v_Angle);
		SetVehicleVirtualWorld(VID, GetPlayerVirtualWorld(playerid));
		LinkVehicleToInterior(VID, GetPlayerInterior(playerid));

		AccountData[playerid][pMoney] -= 1000;
		GivePlayerMoney(playerid, -1000);
		
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_Money` = %d WHERE `pID` = %d", AccountData[playerid][pMoney], AccountData[playerid][pID]);
		mysql_tquery(g_SQL, query);

		ShowTDN(playerid, NOTIFICATION_SUKSES, "Valet: Kendaraan Anda sudah diantarkan! ($5,000)");
		PlayerPlaySound(playerid, 1052, 0.0, 0.0, 0.0);
		
		DeletePVar(playerid, "ClickVehicle");
		return 1;
	}
	if(dialogid == DIALOG_VEHICLE_DETAIL)
	{
		if(!response) return Info(playerid, "Anda telah membatalkan pilihan");
		new otherid = strval(inputtext);
		if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
		if(!IsPlayerNearPlayer(playerid, otherid, 4.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dekat pemain tersebut!");

		static strings[3048], Float:vHealth;
		new vehid = GetPVarInt(playerid, "ClickVehicle");
		if(!IsValidVehicle(PlayerVehicle[vehid][pVehPhysic])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut belum spawn!");
		if(GetNearestVehicle(playerid) != PlayerVehicle[vehid][pVehPhysic]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak didekat kendaraan yang ingin anda cek detailnya!");

		GetVehicleHealth(PlayerVehicle[vehid][pVehPhysic], vHealth);

		format(strings, sizeof(strings), ""DEEPSKYBLUE1"Utama\
		\n"WHITE"VID (Database):"YELLOW" %d\
		\n"WHITE"Kendaraan:"YELLOW" %s\
		\n"WHITE"Nomor Plat"YELLOW" %s\
		\n\n"DEEPSKYBLUE1"Upgrade:\
		\n"WHITE"- Engine Upgrade %s\
		\n"WHITE"- Body Upgrade %s\
		\n\n"DEEPSKYBLUE1"Selebihnya\
		\n"WHITE"Fuel Capacity:"YELLOW" %d.0/100.0\
		\n"WHITE"Max Vehicle Health:"YELLOW" %.1f/%s\
		\n"WHITE"Vehicle Body Health:"YELLOW" %.1f/1000.0", PlayerVehicle[vehid][pVehID], GetVehicleName(PlayerVehicle[vehid][pVehPhysic]), PlayerVehicle[vehid][pVehPlate],
		(PlayerVehicle[vehid][pVehEngineUpgrade] != 1) ? ""RED"None" : ""GREEN"Upgrade", (PlayerVehicle[vehid][pVehBodyUpgrade] != 3) ? ""RED"None" : ""GREEN"Upgrade",
		GetFuel(PlayerVehicle[vehid][pVehPhysic]), vHealth, (PlayerVehicle[vehid][pVehEngineUpgrade] != 1) ? "1000.0" : "2000.0", PlayerVehicle[vehid][pVehBodyRepair]);
		ShowPlayerDialog(otherid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, sprintf(""TCRP"District  "WHITE"- %s Vehicle Details", AccountData[playerid][pName]), strings, "Tutup", "");
	}
	if(dialogid == DIALOG_SELECT_SPAWNEXPIRED)
	{
		if(!response) 
		{
			ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menetapkan lokasi spawn!");
			ShowPlayerDialog(playerid, DIALOG_SELECT_SPAWNEXPIRED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Pilih Lokasi Spawn",
			"Titik Spawn\tDetail\tLokasi\
			\nBandara International\tAnda akan spawn di bandara\tLos Santos\
			\nLast Exit\tAnda akan spawn di Tempat Akhir\tOcean Docs\
			\nBandara Las Venturas\tAnda akan spawn di bandara\tLas Venturas\
			\nCarnaval\tAnda akan spawn di wahana carnaval\tSanta Maria Beach\
			\nHouse\tAnda akan spawn didepan rumah milik anda\t-\
			\nRusun\tAnda akan spawn didepan motel sewaan anda\t-", "Pilih", "");
			return 1;
		}

		switch(listitem)
		{
			case 0: //bandara
			{
				new rand = random(sizeof(SpawnBandara));
				AccountData[playerid][pPosX] = SpawnBandara[rand][0];
				AccountData[playerid][pPosY] = SpawnBandara[rand][1];
				AccountData[playerid][pPosZ] = SpawnBandara[rand][2];
				AccountData[playerid][pPosA] = SpawnBandara[rand][3];
				SetPlayerInteriorEx(playerid, 0);
				SetPlayerVirtualWorldEx(playerid, 0);

				SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 6000);
			}
			case 1: //Pelabuhan
			{
				SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 0, 0, 0, 0, 0, 0);
				SpawnPlayer(playerid);
				Streamer_UpdateEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ]);
				SetPlayerVirtualWorldEx(playerid, AccountData[playerid][pWorld]);
				SetPlayerInteriorEx(playerid, AccountData[playerid][pInt]);
				SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 6000);
			}
			case 2: //Bandara Las Venturas
			{
				new rand = random(sizeof(SpawnVenturas));
				AccountData[playerid][pPosX] = SpawnVenturas[rand][0];
				AccountData[playerid][pPosY] = SpawnVenturas[rand][1];
				AccountData[playerid][pPosZ] = SpawnVenturas[rand][2];
				AccountData[playerid][pPosA] = SpawnVenturas[rand][3];
				SetPlayerInteriorEx(playerid, 0);
				SetPlayerVirtualWorldEx(playerid, 0);

				SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 6000);
			}
			case 3: // Carnaval
			{
				AccountData[playerid][pPosX] = 375.5105;
				AccountData[playerid][pPosY] = -1899.5723;
				AccountData[playerid][pPosZ] = 7.8359;
				AccountData[playerid][pPosA] = 88.7574;
				SetPlayerInteriorEx(playerid, 0);
				SetPlayerVirtualWorldEx(playerid, 0);

				SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 6000);
			}
			case 4: // Rumah
			{
				foreach(new hid : House) 
				{
					if(AccountData[playerid][pOwnedHouse] == -1 && AccountData[playerid][pFriendHouseID] == -1)
					{
						ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki rumah!");
						ShowPlayerDialog(playerid, DIALOG_SELECT_SPAWNEXPIRED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Pilih Lokasi Spawn",
						"Titik Spawn\tDetail\tLokasi\
						\nBandara International\tAnda akan spawn di bandara\tLos Santos\
						\nLast Exit\tAnda akan spawn di Tempat Akhir\tOcean Docs\
						\nBandara Las Venturas\tAnda akan spawn di bandara\tLas Venturas\
						\nCarnaval\tAnda akan spawn di wahana carnaval\tSanta Maria Beach\
						\nHouse\tAnda akan spawn didepan rumah milik anda\t-\
						\nRusun\tAnda akan spawn didepan motel sewaan anda\t-", "Pilih", "");
						return 1;
					}
					else if(AccountData[playerid][pOwnedHouse] != -1 && AccountData[playerid][pFriendHouseID] == -1)
					{
						if(HouseData[hid][hsOwnerID] == AccountData[playerid][pID] && !strcmp(HouseData[hid][hsOwner], AccountData[playerid][pName], true))
						{
							AccountData[playerid][pPosX] = HouseData[hid][hsExtPos][0];
							AccountData[playerid][pPosY] = HouseData[hid][hsExtPos][1];
							AccountData[playerid][pPosZ] = HouseData[hid][hsExtPos][2];
							AccountData[playerid][pPosA] = HouseData[hid][hsExtPos][3];
							SetPlayerInteriorEx(playerid, 0);
							SetPlayerVirtualWorldEx(playerid, 0);

							SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 6000);
						}
					}
					else if(AccountData[playerid][pOwnedHouse] == -1 && AccountData[playerid][pFriendHouseID] == hid)
					{
						AccountData[playerid][pPosX] = HouseData[AccountData[playerid][pFriendHouseID]][hsExtPos][0];
						AccountData[playerid][pPosY] = HouseData[AccountData[playerid][pFriendHouseID]][hsExtPos][1];
						AccountData[playerid][pPosZ] = HouseData[AccountData[playerid][pFriendHouseID]][hsExtPos][2];
						AccountData[playerid][pPosA] = HouseData[AccountData[playerid][pFriendHouseID]][hsExtPos][3];
						SetPlayerInteriorEx(playerid, 0);
						SetPlayerVirtualWorldEx(playerid, 0);

						SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 6000);
					}
					else if(AccountData[playerid][pOwnedHouse] != -1 && AccountData[playerid][pFriendHouseID] != -1)
					{
						Dialog_Show(playerid, HouseSpawn_Option, DIALOG_STYLE_TABLIST, ""TCRP"District  "WHITE"- House Opsi", "Rumah Pribadi\n"GRAY"Rumah Teman", "Pilih", "Batal");
					}
				}
			}
			case 5: // rusun
			{
				if(AccountData[playerid][pOwnedRusun] == -1) 
				{
					ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki rusun!");
					ShowPlayerDialog(playerid, DIALOG_SELECT_SPAWNEXPIRED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Pilih Lokasi Spawn",
					"Titik Spawn\tDetail\tLokasi\
					\nBandara International\tAnda akan spawn di bandara\tLos Santos\
					\nLast Exit\tAnda akan spawn di Tempat Akhir\tOcean Docs\
					\nBandara Las Venturas\tAnda akan spawn di bandara\tLas Venturas\
					\nCarnaval\tAnda akan spawn di wahana carnaval\tSanta Maria Beach\
					\nHouse\tAnda akan spawn didepan rumah milik anda\t-\
					\nRusun\tAnda akan spawn didepan motel sewaan anda\t-", "Pilih", "");
					return 1;
				}

				foreach(new rsid : Rusun) 
				{
					if(RusunData[rsid][rusunOwnerID] == AccountData[playerid][pID])
					{
						AccountData[playerid][pPosX] = RusunData[rsid][rusunExtPos][0];
						AccountData[playerid][pPosY] = RusunData[rsid][rusunExtPos][1];
						AccountData[playerid][pPosZ] = RusunData[rsid][rusunExtPos][2];
						AccountData[playerid][pPosA] = RusunData[rsid][rusunExtPos][3];
						SetPlayerInteriorEx(playerid, 0);
						SetPlayerVirtualWorldEx(playerid, 0);

						SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 6000);
					}
				}
			}
		}
		AccountData[playerid][playerClickSpawn] = 1;
		// SetPVarInt(playerid, "SpawnExpired", 1);
	}
	if(dialogid == DIALOG_SELECT_SPAWN)
	{
		if(!response)
		{
			ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menetapkan lokasi spawn!");
			ShowPlayerDialog(playerid, DIALOG_SELECT_SPAWN, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Pilih Lokasi Spawn",
			"Titik Spawn\tDetail\tLokasi\nBandara International\tAnda akan spawn di bandara\tLos Santos\n", "Pilih", "");
			return 1;
		}

		switch(listitem)
		{
			case 0: //bandara
			{
				Login::Screen_Show(playerid, 1);
			}
			/*case 1: //pelabuhan
			{
				new rand = random(sizeof(SpawnPelabuhan));
				AccountData[playerid][pPosX] = SpawnPelabuhan[rand][0];
				AccountData[playerid][pPosY] = SpawnPelabuhan[rand][1];
				AccountData[playerid][pPosZ] = SpawnPelabuhan[rand][2];
				AccountData[playerid][pPosA] = SpawnPelabuhan[rand][3];
				SetPlayerVirtualWorldEx(playerid, 0);
				SetPlayerInteriorEx(playerid, 0);
			}*/
		}
	} 
	if(dialogid == DialogGudangList)
	{
		if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");

        new idx = 0, id;
        for(id = 0; id < MAX_DYNAMIC_GUDANG; id++)
        {
            if(!Iter_Contains(Gudang, id)) continue;

            if(idx == listitem)
            {
                AccountData[playerid][pTempValue] = id;
                break;
            }
            idx++;
        }

        if(AccountData[playerid][pTempValue] == -1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Gudang tidak valid!");

        ShowPlayerDialog(playerid, DialogInputGudang, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Masukkan ID Player yang ingin disewakan gudang ini", "Contoh ID 1", "OK", "Batal");
	}
	if(dialogid == DialogInputGudang)
	{
		if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan input PlayerID");

        new targetid = strval(inputtext); // konversi input ke integer
        if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "PlayerID tidak valid atau tidak online!");

        new id = AccountData[playerid][pTempValue]; // ID gudang
        if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Gudang tidak valid!");

        if(AccountData[targetid][pHasGudangID] != -1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Player %s sudah menyewa gudang %s", AccountData[targetid][pName], GudangData[AccountData[targetid][pHasGudangID]][gudangName]));

        // Set sewa langsung ke player
        AccountData[targetid][pHasGudangID] = id;
        AccountData[targetid][pGudangRentTime] = gettime() + (3600 * 24 * 30); // 30 hari

        ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil menyewakan Gudang %s ke %s selama 30 hari", GudangData[id][gudangName], AccountData[targetid][pName]));
        ShowTDN(targetid, NOTIFICATION_SUKSES, sprintf("Anda mendapatkan sewa Gudang %s selama 30 hari dari pemerintah", GudangData[id][gudangName]));

        new query[256];
        mysql_format(g_SQL, query, sizeof(query), "UPDATE player_characters SET Char_HasGudangID=%d WHERE pID=%d", id, AccountData[targetid][pID]);
        mysql_tquery(g_SQL, query);

        AccountData[playerid][pTempValue] = -1; // reset
	}
	if(dialogid == DIALOG_LOCKER_LIST)
    {
        if(!response) return 1;
        if(listitem < 0 || listitem >= lockerCount) return 1;

        new pname[24];
        GetPlayerName(playerid, pname, sizeof(pname));

        if(strcmp(pname, lockerData[listitem][lOwner], true) != 0)
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan senjata anda!");
            return 1;
        }

        g_PendingTake[playerid] = listitem;

        new wname[32];
        GetWeaponNameById(lockerData[listitem][lWeapon], wname, sizeof(wname));

        new msg[128];
        format(msg, sizeof(msg), "Ambil %s (%d ammo)?", wname, lockerData[listitem][lAmmo]);
        ShowPlayerDialog(playerid, DIALOG_LOCKER_CONFIRM, DIALOG_STYLE_MSGBOX, "Konfirmasi Ambil", msg, "Ya", "Tidak");
        return 1;
    }
	if(dialogid == DIALOG_LOCKER_CONFIRM)
    {
        if(!response) return 1;
        new idx = g_PendingTake[playerid];
        if(idx < 0 || idx >= lockerCount) return 1;

        new pname[24];
        GetPlayerName(playerid, pname, sizeof(pname));
        if(strcmp(pname, lockerData[idx][lOwner], true) != 0)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan senjata anda!");

        GivePlayerWeaponEx(playerid, lockerData[idx][lWeapon], lockerData[idx][lAmmo]);
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Senjata berhasil diambil dari locker.");
        Locker_RemoveAt(idx);
        g_PendingTake[playerid] = -1;
        return 1;
    }
	if(dialogid == DIALOG_MY_GS)
	{
		if(!response) return true;
		SetPVarInt(playerid, "ClickedGs", ReturnPlayerGasStationID(playerid, (listitem + 1)));
		ShowPlayerDialog(playerid, GS_INFO, DIALOG_STYLE_LIST, "{FF8B59}My Gas Station", "Show Information\nTrack Bisnis", "Pilih", "Batal");
		return 1;
	}
	if(dialogid == GS_INFO)
	{
		if(!response) return true;
		new gsid = GetPVarInt(playerid, "ClickedGs");
		switch(listitem)
		{
			case 0:
			{
				new line9[900];
	
				format(line9, sizeof(line9), "Gas Station ID: %d\nGas Station Owner: %s\nGas Staion Name: %s\nGas Station Price: %s\nGas Station stock: %d",
				gsid, gsData[gsid][gOwner], gsData[gsid][gName], FormatMoney(gsData[gsid][gPrice]), gsData[gsid][gsStock]);

				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, "Gas Staion Info", line9, "Tutup","");
			}
			case 1:
			{
				AccountData[playerid][pTrackGs] = 1;
				SetPlayerRaceCheckpoint(playerid,1, gsData[gsid][gsPosX], gsData[gsid][gsPosY], gsData[gsid][gsPosZ], 0.0, 0.0, 0.0, 3.5);
				//SetPlayerCheckpoint(playerid, bData[bid][bExtpos][0], bData[bid][bExtpos][1], bData[bid][bExtpos][2], 4.0);
				Info(playerid, "Ikuti checkpoint untuk menemukan bisnis anda!");
				
				//(playerid,  gsData[gsid][gsPosX], gsData[gsid][gsPosY], gsData[gsid][gsPosZ], COLOR_BLUE);
			}
		}
		return 1;
	}
	if(dialogid == GS_MENU)
	{
		if(response)
		{
			new gsid = AccountData[playerid][pInGas];
			if(gsid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Gas station tidak di temukan!");
			switch(listitem)
			{
				case 0:
				{
					new mstr[248], lstr[512];
					format(mstr,sizeof(mstr),"Gas ID %d", gsid);
					format(lstr,sizeof(lstr),"Gas Name:\t%s\nGas Stock:\t%d\nGas Vault:\t%s", gsData[gsid][gName], gsData[gsid][gsStock], FormatMoney(gsData[gsid][gMoney]));
					ShowPlayerDialog(playerid, GS_INFO, DIALOG_STYLE_TABLIST, mstr, lstr,"Back","Close");
				}
				case 1:
				{
					new mstr[248];
					format(mstr,sizeof(mstr),"Nama sebelumnya: %s\n\nMasukkan nama bisnis yang kamu inginkan\nMaksimal 32 karakter untuk nama bisnis", gsData[gsid][gName]);
					ShowPlayerDialog(playerid, GS_NAME, DIALOG_STYLE_INPUT,"Gas Name", mstr,"Done","Back");
				}
				case 2: ShowPlayerDialog(playerid, GS_VAULT, DIALOG_STYLE_LIST,"Gas Vault","Deposit\nWithdraw","Next","Back");
				case 3:
				{
					ShowGasPriceDialog(playerid, gsid);
			  	}
				case 4:
				{
					if(gsData[gsid][gsStock] > 2000)
						return Error(playerid, "Bisnis ini masih memiliki cukup stock.");
					if(gsData[gsid][gMoney] < 10000)
						return Error(playerid, "Setidaknya anda mempunyai uang dalam bisnis anda senilai $10000 untuk merestock product.");
					gsData[gsid][gRestock] = 1;
					Info(playerid, "Anda berhasil request untuk mengisi stock gas kepada trucker, harap tunggu sampai pekerja trucker melayani.");
				}
			}
		}
		return 1;
	}
	//Jewelry Store
	if(dialogid == JewelryHack_Input)
    {
        if(response)
        {
            new textCommand[50];
            if(sscanf(inputtext, "s[50]", textCommand))
                return ShowPlayerDialog(playerid, JewelryHack_Input, DIALOG_STYLE_INPUT, "{32ff24}Command", "Masukkan Command:", "Terapkan", "Batal");

            PlayerTextDrawShow(playerid, JewelryHackPTD[playerid][7]);
            format(JewelryHack_Command, 50, "%s", textCommand);
            PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][7], JewelryHack_Command);
        }
        return 1;
    }
	if(dialogid == GS_PRICESET)
	{
		if (!response) return 1;
		new gsid = AccountData[playerid][pInGas];

		if(!Player_OwnsGas(playerid, AccountData[playerid][pInGas])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pemilik gas station ini");

		new harga = strval(inputtext);
		if (harga < 10 || harga > 10000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Harga gas harus antara 10.000 - 5.000.000.");

		gsData[gsid][gStockPrice] = harga;

		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "UPDATE gstations SET gsprice='%d' WHERE ID='%d'", gsData[gsid][gStockPrice], gsid);
		mysql_tquery(g_SQL, query);

		GStation_Refresh(gsid);

		new msg[128];
		format(msg, sizeof(msg), "Harga gas telah diubah menjadi "GREEN_E"%d", harga);
		SendClientMessage(playerid, -1, msg);
	}
	if(dialogid == GS_INFO)
	{
		if(response)
		{
			return callcmd::gsmenu(playerid, "\0");
		}
		return 1;
	}
	if(dialogid == GS_NAME)
	{
		if(response)
		{
			new gsid = AccountData[playerid][pInGas];

			if(!Player_OwnsGas(playerid, AccountData[playerid][pInGas])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pemilik gas station ini");
			
			if (isnull(inputtext))
			{
				new mstr[512];
				format(mstr,sizeof(mstr),""RED_E"NOTE: "WHITE_E"Nama Gas Station tidak di perbolehkan kosong!\n\n"WHITE_E"Nama sebelumnya: %s\n\nMasukkan nama Gas Station yang kamu inginkan\nMaksimal 32 karakter untuk nama Gas Station", gsData[gsid][gName]);
				ShowPlayerDialog(playerid, GS_NAME, DIALOG_STYLE_INPUT,"Bisnis Name", mstr,"Done","Kembali");
				return 1;
			}
			if(strlen(inputtext) > 32 || strlen(inputtext) < 5)
			{
				new mstr[512];
				format(mstr,sizeof(mstr),""RED_E"NOTE: "WHITE_E"Nama Gas Station harus 5 sampai 32 karakter.\n\n"WHITE_E"Nama sebelumnya: %s\n\nMasukkan nama Gas Station yang kamu inginkan\nMaksimal 32 karakter untuk nama Gas Station", gsData[gsid][gName]);
				ShowPlayerDialog(playerid, GS_NAME, DIALOG_STYLE_INPUT,"Gas Station Name", mstr,"Done","Kembali");
				return 1;
			}
			format(gsData[gsid][gName], 32, ColouredText(inputtext));

			new query[128];
			mysql_format(g_SQL, query, sizeof(query), "UPDATE gstations SET name='%s' WHERE ID='%d'", gsData[gsid][gName], gsid);
			mysql_tquery(g_SQL, query);

			GStation_Refresh(gsid);

			Info(playerid, "Gas Station name set to: \"%s\".", gsData[gsid][gName]);
		}
		else return callcmd::gsmenu(playerid, "\0");
		return 1;
	}
	if(dialogid == GS_VAULT)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0:
				{
					new mstr[512];
					format(mstr,sizeof(mstr),"Uang kamu: %s.\n\nMasukkan berapa banyak uang yang akan kamu simpan di dalam Gas Station ini", FormatMoney(AccountData[playerid][pMoney]));
					ShowPlayerDialog(playerid, GS_DEPOSIT, DIALOG_STYLE_INPUT, "Deposit", mstr, "Deposit", "Kembali");
				}
				case 1:
				{
					new mstr[512];
					format(mstr,sizeof(mstr),"Business Vault: %s\n\nMasukkan berapa banyak uang yang akan kamu ambil di dalam Gas Station ini", FormatMoney(gsData[AccountData[playerid][pInGas]][gMoney]));
					ShowPlayerDialog(playerid, GS_WITHDRAW, DIALOG_STYLE_INPUT,"Withdraw", mstr,"Withdraw","Kembali");
				}
			}
		}
		return 1;
	}
	if(dialogid == GS_WITHDRAW)
	{
		if(response)
		{
			new bid = AccountData[playerid][pInGas];
			new amount = floatround(strval(inputtext));
			if(amount < 1 || amount > gsData[bid][gMoney])
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah uang salah");

			gsData[bid][gMoney] -= amount;
			
			new query[128];
			mysql_format(g_SQL, query, sizeof(query), "UPDATE gstations SET money='%d' WHERE ID='%d'", gsData[bid][gMoney], bid);
			mysql_tquery(g_SQL, query);

			GivePlayerMoney(playerid, amount);

			SendClientMessageEx(playerid, COLOR_LBLUE,"GAS STATION: "WHITE_E"You have withdrawn "GREEN_E"%s "WHITE_E"from the gas station vault.", FormatMoney(strval(inputtext)));
		}
		else
			ShowPlayerDialog(playerid, GS_VAULT, DIALOG_STYLE_LIST,"Gas Station Vault","Deposit\nWithdraw","Next","Kembali");
		return 1;
	}
	if(dialogid == GS_DEPOSIT)
	{
		if(response)
		{
			new bid = AccountData[playerid][pInGas];
			new amount = floatround(strval(inputtext));
			if(amount < 1 || amount > AccountData[playerid][pMoney])
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah uang salah");

			gsData[bid][gMoney] += amount;

			new query[128];
			mysql_format(g_SQL, query, sizeof(query), "UPDATE gstations SET money='%d' WHERE ID='%d'", gsData[bid][gMoney], bid);
			mysql_tquery(g_SQL, query);

			TakeMoney(playerid, amount);
			
			SendClientMessageEx(playerid, COLOR_LBLUE,"BUSINESS: "WHITE_E"You have deposit "GREEN_E"%s "WHITE_E"into the business vault.", FormatMoney(strval(inputtext)));
		}
		else
			ShowPlayerDialog(playerid, GS_VAULT, DIALOG_STYLE_LIST,"Business Vault","Deposit\nWithdraw","Next","Kembali");
		return 1;
	}
	if(dialogid == DIALOG_SELL_GS)
	{
		if(!response) return 1;
		new str[248];
		SetPVarInt(playerid, "SellingGs", ReturnPlayerGasStationID(playerid, (listitem + 1)));
		format(str, sizeof(str), "Are you sure you will sell gas station id: %d", GetPVarInt(playerid, "SellingGs"));
				
		ShowPlayerDialog(playerid, DIALOG_SELL_GS, DIALOG_STYLE_MSGBOX, "Sell Gas Station", str, "Sell", "Batal");
	}
	if(dialogid == DIALOG_SELL_GS)
	{
		if(response)
		{
			new bid = GetPVarInt(playerid, "SellingGs"), price;
			price = gsData[bid][gPrice] / 2;
			GivePlayerMoney(playerid, price);
			Info(playerid, "Anda berhasil menjual gas station id (%d) dengan setengah harga("LG_E"%s"WHITE_E") pada saat anda membelinya.", bid, FormatMoney(price));
			Gas_Reset(bid);
			GStation_Save(bid);
			GStation_Refresh(bid);
		}
		DeletePVar(playerid, "SellingGs");
		return 1;
	}
	if(dialogid == GPS_NEAREST_GSTATION)
	{
		if(response)
		{
			new id = ReturnGStationNearestID(playerid, (listitem+1));
			DisablePlayerRaceCheckpoint(playerid);
			SetPlayerRaceCheckpoint(playerid, 1, gsData[id][gsPosX], gsData[id][gsPosY], gsData[id][gsPosZ], 0.0, 0.0, 0.0, 7.0); //GPS GAS STATION
			Info(playerid, "GPS Active! Gas Station yang berjarak %0.0fm berlokasi di %s telah ditandai", GetPlayerDistanceFromPoint(playerid, gsData[id][gsPosX], gsData[id][gsPosY], gsData[id][gsPosZ]), GetLocation(gsData[id][gsPosX], gsData[id][gsPosY], gsData[id][gsPosZ]));
		}
	}
	if(dialogid == DIALOG_BERANKAS_CODE)
	{
		if(response)
		{
			new id = g_PlayerRobbery[playerid];
			if(id == -1) return 1;

			new coderob = strval(inputtext);
			if(coderob == g_BerankasCode[id])
			{
				if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

				Info(playerid, "Anda berhasil memasukan code hack!");
                
                AccountData[playerid][ActivityTime] = 1;
                pTimerOpenRobb[playerid] = SetTimerEx("OpenRobbery", 1000, true, "dd", playerid);
				ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 1, 1, 1, 0, 1);
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "Membuka Berankas");
                ShowProgressBar(playerid);
			}
			else
			{
				new retry = g_RobberyTime = 30;
				SendClientMessageEx(playerid, -1, ""YELLOW"[Robbery]: "WHITE"Anda gagal memasukan code berankas, Silahkan coba kembali dalam waktu %d detik", retry);
				DurringRobbery[playerid] = false;
				g_BerankasCode[id] = 0;
				//UpdateRobberyTextLabel(id);
			
				new Float:px, Float:py, Float:pz;
    			GetPlayerPos(playerid, px, py, pz);

				SendClientMessageToAllEx(-1, "{201EE5}POLICE:{FFFFFF} Telah terjadi perampokan di %s. Warga harap menjauh dari area perampokan!", GetLocation(px, py, pz));
				foreach(new i : Player) 
				{
					if (AccountData[i][pSpawned] && AccountData[i][pFaction] == FACTION_POLISI && AccountData[i][pDutyPD])
					{
						static shstr[255];
						format(shstr, sizeof(shstr), "Telah terjadi perampokan warung di~n~%s", GetLocation(px, py, pz));
						//RobberyShowTD(i, shstr);
									
						SetPlayerRaceCheckpoint(i, 1, px, py, pz, 0.0, 0.0, 0.0, 5.0);
						Warning(i, "Lokasi warung yang sedang dirampok telah ditandai pada blip di map!");
					}
				}
			}
		}
	}
	if(dialogid == DIALOG_MENUMAKAN)
    {
        if(!response) return 1;

        if(AccountData[playerid][pFaction] != FACTION_PEDAGANG)
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya pedagang yang bisa mengubah harga menu.");
            ShowMenuMakanan(playerid);
            return 1;
        }
        if(AccountData[playerid][pFactionRank] < 6)
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank 5-6 untuk bisa ubah harga menu!");
            ShowMenuMakanan(playerid);
            return 1;
        }
        switch(listitem)
        {
            case 0: ShowUbahHargaLow(playerid); 
            case 1: ShowUbahHargaMedium(playerid); 
            case 2: ShowUbahHargaHigh(playerid); 
			case 3: ShowUbahHargaSpecial(playerid);
            default:ShowMenuMakanan(playerid); 
        }
        return 1;
    }
    if(dialogid == DIALOG_UBAHHARGA_LOW)
    {
        if(!response) return 1;
        new hargabaru = strval(inputtext);
        if(hargabaru < 1)
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Harga tidak valid!");
            return 1;
        }
        hargalow = hargabaru;
		new query[128];
		format(query, sizeof(query), "UPDATE brankas_lounges SET hargalows='%d' WHERE id=0",hargalow);
		mysql_tquery(g_SQL, query);
		ShowTDN(playerid, NOTIFICATION_SUKSES, "Harga Hargalow menu makanan berhasil diubah!");
    }
    if(dialogid == DIALOG_UBAHHARGA_MEDIUM)
    {
        if(!response) return 1;
        new hargabaru = strval(inputtext);
        if(hargabaru < 1)
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Harga tidak valid!");
            return 1;
        }
        hargamedium = hargabaru;
		new query[128];
		format(query, sizeof(query), "UPDATE brankas_lounges SET hargamediums='%d' WHERE id=0",hargamedium);
		mysql_tquery(g_SQL, query);
		ShowTDN(playerid, NOTIFICATION_SUKSES, "Harga Medium menu makanan berhasil diubah!");
    }
    if(dialogid == DIALOG_UBAHHARGA_HIGH)
    {
        if(!response) return 1;
        new hargabaru = strval(inputtext);
        if(hargabaru < 1)
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Harga tidak valid!");
            return 1;
        }
        hargahigh = hargabaru;
		new query[128];
		format(query, sizeof(query), "UPDATE brankas_lounges SET hargahighs='%d' WHERE id=0",hargahigh);
		mysql_tquery(g_SQL, query);
		ShowTDN(playerid, NOTIFICATION_SUKSES, "Harga High menu makanan berhasil diubah!");
    }
	if(dialogid == DIALOG_UBAHHARGA_SPECIAL)
    {
        if(!response) return 1;
        new hargabaru = strval(inputtext);
        if(hargabaru < 1)
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Harga tidak valid!");
            return 1;
        }
        hargaspecial = hargabaru;
		new query[128];
		format(query, sizeof(query), "UPDATE brankas_lounges SET hargaspecialis='%d' WHERE id=0",hargaspecial);
		mysql_tquery(g_SQL, query);
		ShowTDN(playerid, NOTIFICATION_SUKSES, "Harga Special menu makanan berhasil diubah!");
    }
	if(dialogid == DialogKargoRemake)
	{
		if(response)
		{
			switch(listitem)
			{
				case 0: 
				{
					new Float:px, Float:py, Float:pz, Float:pa;
					GetPlayerPos(playerid, px, py, pz);
					GetPlayerFacingAngle(playerid, pa);

					// Spawn trailer & job vehicle
					PlayerKargoVars[playerid][KargoTrailer] = CreateVehicle(584, px, py, pz, pa, -1, -1, 60000, 0);
					CreateJobVehicle(playerid, 515, px+4.0, py+4.0, pz, 316.0, -1, -1, true, false);

					PlayerKargoVars[playerid][PertaminaObject] = CreateDynamicObject(19482,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
					SetDynamicObjectMaterialText(PlayerKargoVars[playerid][PertaminaObject], 0, "{000000}PERTAMINA", 130, "Arial", 60, 1, 0, 0, 1);
					AttachDynamicObjectToVehicle(PlayerKargoVars[playerid][PertaminaObject], PlayerKargoVars[playerid][KargoTrailer], -1.085, -0.650, 0.765, 0.0, -39.799, 180.0);

					// Fuel & Engine
					new randsbensin = RandomEx(55, 100);
					VehicleCore[JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle]][vCoreFuel] = randsbensin;
					SwitchVehicleEngine(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], true);
					AttachTrailerToVehicle(PlayerKargoVars[playerid][KargoTrailer], JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle]);

					// Set checkpoint terakhir dari index
					if(KargoSaveCP[playerid] >= 0 && KargoSaveCP[playerid] < MAX_KARGO)
					{
						new Float:x, Float:y, Float:z;
						GetKargoCheckpointPos(KargoSaveCP[playerid], x, y, z);
						SetPlayerRaceCheckpoint(playerid, 1, x, y, z, x, y, z, 5.0);
						KargoIndex[playerid] = 1;
					}
					if(KargoIndex[playerid] == 2)
					{
						SendClientMessageEx(playerid, -1, ""YELLOW"[i]"WHITE_E": Bawa mautan kargo kembali ke pelabuhan "YELLOW"Tanjung Priok. "WHITE_E"Ikutilah tanda yang diberikan!");
						SetPlayerRaceCheckpoint(playerid, 1, -1547.1716, 125.6070, 3.5547, -1547.1716, 125.6070, 3.5547, 5.0);
						KargoIndex[playerid] = 2;
					}
					
					Info(playerid, ""GRAY"Kargo dilanjutkan dari checkpoint terakhir.");
				}
				case 1:
				{
					// Reset kargo
					if(IsValidVehicle(PlayerKargoVars[playerid][KargoTrailer]))
						DestroyVehicle(PlayerKargoVars[playerid][KargoTrailer]);

					DestroyJobVehicle(playerid);

					if(IsValidDynamicObject(PlayerKargoVars[playerid][PertaminaObject]))
						DestroyDynamicObject(PlayerKargoVars[playerid][PertaminaObject]);

					PlayerKargoVars[playerid][KargoStarted] = false;
					KargoIndex[playerid] = -1;

					SendClientMessage(playerid, COLOR_YELLOW, "Kargo telah direset.");
				}
			}
		}
	}
	if(dialogid == DIALOG_CLICKPLAYER)
	{
		if(!response)
		{
			ClickPlayerID[playerid] = -1;
			ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
			return 1;
		}

		if(ClickPlayerID[playerid] == -1)
		{
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih pemain manapun!");
		}

		new targetid = ClickPlayerID[playerid];
		if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
		switch(listitem)
		{
			case 2:// spectator
			{
				if(AccountData[playerid][pAdmin] < AccountData[targetid][pAdmin]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat melakukan ini kepada Admin Atasan anda!");
				if(!AccountData[targetid][pSpawned]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut dalam keadaan tidak spawn!");
				if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
				{
					GetPlayerPos(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ]);
					GetPlayerFacingAngle(playerid, AccountData[playerid][pPosA]);

					AccountData[playerid][pInt] = GetPlayerInterior(playerid);
					AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
				}
				SetPlayerInterior(playerid, GetPlayerInterior(targetid));
				SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
				TogglePlayerSpectating(playerid, true);

				if(IsPlayerInAnyVehicle(targetid))
				{
					new vehid = GetPlayerVehicleID(targetid);
					PlayerSpectateVehicle(playerid, GetPlayerVehicleID(targetid));
					if(GetPlayerState(targetid) == PLAYER_STATE_DRIVER)
					{
						SendClientMessageEx(playerid, X11_ARWIN, "[AdmCmd] Anda sekarang sedang memantau "YELLOW"%s(%d)"ARWIN1" yang sedang mengemudikan "YELLOW"%s(%d)", AccountData[targetid][pName], targetid, GetVehicleModelName(GetPlayerVehicleID(targetid)), vehid);
					}
					else
					{
						SendClientMessageEx(playerid, X11_ARWIN, "[AdmCmd] Anda sekarang sedang memantau "YELLOW"%s(%d)"ARWIN1" yang merupakan penumpang di "YELLOW"%s(%d)", AccountData[targetid][pName], targetid, GetVehicleModelName(GetPlayerVehicleID(targetid)), vehid);
					}
				}
				else
				{
					PlayerSpectatePlayer(playerid, targetid);
				}
				AccountData[targetid][playerSpectated] ++;
				AccountData[playerid][pSpec] = targetid;
				ShowSpectatorInfo(playerid, true);
				SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" sedang memantau "YELLOW"%s(%d)", AccountData[playerid][pAdminname], AccountData[targetid][pName], targetid);
			}
			case 3:// Gethere
			{
				if(AccountData[targetid][pJail]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang dalam jail admin!");
				if(AccountData[targetid][pArrest]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang dalam jail kepolisian!");
				if(AccountData[playerid][pAdmin] < AccountData[targetid][pAdmin]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat melakukan ini kepada Admin Atasan anda!");

				SendPlayerToPlayer(targetid, playerid);
				SendClientMessageEx(playerid, X11_ARWIN, "[AdmCmd]"YELLOW" %s(%d)"ARWIN1" telah ditarik keposisi anda!", AccountData[targetid][pName], targetid);
				SendClientMessageEx(targetid, X11_ARWIN, "[AdmCmd]"RED" %s"ARWIN1" telah menarik anda keposisinya", AccountData[playerid][pAdminname]);
			}
			case 4:// Goto
			{
				SendPlayerToPlayer(playerid, targetid);
				SendClientMessageEx(playerid, X11_ARWIN, "[AdmCmd] Anda teleportasi ke posisi "YELLOW"%s(%d)", AccountData[targetid][pName], targetid);
				SendClientMessageEx(targetid, X11_ARWIN, "[AdmCmd]"RED" %s"ARWIN1" telah teleportasi keposisi anda", AccountData[playerid][pAdminname]);
			}
			case 5: // banned
			{
				if(AccountData[playerid][pAdmin] < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya level 3 keatas yang dapat menggunakan perintah ini!");
				if(AccountData[playerid][pAdmin] < AccountData[targetid][pAdmin]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat melakukan ini kepada Admin Atasan anda!");
				if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

				new title[100];
				format(title, sizeof(title), "Banned Time - %s(%d)", ReturnName(targetid), targetid);
				ShowPlayerDialog(playerid, DIALOG_BANNEDTIME, DIALOG_STYLE_INPUT, title, "Mohon masukkan berapa hari pemain tersebut akan dibanned [masukkan 0 untuk permanent]\n"YELLOW"(Mohon masukkan value dibawah ini):", "Input", "Batal");
			}
			case 6:// kick
			{
				if(AccountData[playerid][pAdmin] < AccountData[targetid][pAdmin]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat melakukan ini kepada Admin Atasan anda!");
				SendClientMessageToAllEx(X11_ARWIN, "[AdmCmd]"YELLOW" %s(%d)"ARWIN1" telah ditendang dari server oleh "RED"%s.", AccountData[targetid][pName], targetid, AccountData[playerid][pAdminname]);
				SendClientMessageToAllEx(X11_ARWIN, "~> Alasan: .");
				KickEx(targetid);
			}
			case 7: //statistik
			{
				Player_Stats(playerid, targetid);
			}
		}
	}
	if(dialogid == DIALOG_BANNEDTIME)
	{
		if(!response)
		{
			ClickPlayerID[playerid] = -1;
			ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
			return 1;
		}
		
		new time = strval(inputtext);
		if(time < 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan waktu dibawah 0!");
		if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1)
		{
			if(time > 10 || time <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda hanya dapat membanned selama 1 sampai 10 hari!");
		}
		
		SetPVarInt(playerid, "BannedTime", time);
		new title[100];
		format(title, sizeof(title), "Banned Reason - %s(%d)", ReturnName(ClickPlayerID[playerid]), ClickPlayerID[playerid]);
		ShowPlayerDialog(playerid, DIALOG_BANNEDREASON, DIALOG_STYLE_INPUT, title, "Mohon masukkan alasan kenapa pemain ini dibanned\n"YELLOW"(Mohon masukkan dibawah ini):", "Input", "Batal");
	}
	if(dialogid == DIALOG_BANNEDREASON)
	{
		if(!response)
		{
			ClickPlayerID[playerid] = -1;
			ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
			return 1;
		}

		new time = GetPVarInt(playerid, "BannedTime");
		new banTime;

		if(strlen(inputtext) > 128)
		{
			new title[100];
			format(title, sizeof(title), "Banned Reason - %s(%d)", ReturnName(ClickPlayerID[playerid]), ClickPlayerID[playerid]);
			ShowPlayerDialog(playerid, DIALOG_BANNEDREASON, DIALOG_STYLE_INPUT, title, "Error: Anda tidak dapat memasukkan lebih dari 128 kata!\nMohon masukkan alasan kenapa pemain ini dibanned\n"YELLOW"(Mohon masukkan dibawah ini):", "Input", "Batal");
			return 1;
		}

		new PlayerIP[16], PlayerName[32];
		GetPlayerName(ClickPlayerID[playerid], PlayerName, sizeof(PlayerName));
		GetPlayerIp(ClickPlayerID[playerid], PlayerIP, sizeof(PlayerIP));

		if(time != 0)
		{
			SendClientMessageToAllEx(X11_ARWIN, "[AdmCmd]"RED" %s"ARWIN1" telah membanned pemain"YELLOW" %s(%d)"ARWIN1" selama "YELLOW"%d hari", AccountData[playerid][pAdminname], PlayerName, ClickPlayerID[playerid], time);
			SendClientMessageToAllEx(X11_ARWIN, "~> Alasan: %s", inputtext);

			new shstr[128];
			format(shstr, sizeof(shstr), "Membanned %s selama %d hari dengan alasan %s", PlayerName, time, inputtext);
			AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), shstr);
		}
		else
		{
			SendClientMessageToAllEx(X11_ARWIN, "[AdmCmd]"RED" %s"ARWIN1" telah membanned "RED"Permanent"ARWIN1" pemain"YELLOW" %s(%d)", AccountData[playerid][pAdminname], PlayerName, ClickPlayerID[playerid]);
			SendClientMessageToAllEx(X11_ARWIN, "~> Alasan: %s", inputtext);

			new shstr[128];
			format(shstr, sizeof(shstr), "Membanned %s selama permanent dengan alasan %s", PlayerName, inputtext);
			AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), shstr);
		}
		if(time != 0)
		{
			banTime = gettime() + (time * 86400);
			SendClientMessageEx(ClickPlayerID[playerid], X11_ARWIN, "[AdmCmd] Akun anda telah dibanned selama "YELLOW"%d hari"ARWIN1" dengan alasan: %s", time, inputtext);
		}
		else
		{
			SendClientMessageEx(ClickPlayerID[playerid], X11_ARWIN, "[AdmCmd] Akun anda telah dibanned "RED"Permanent "ARWIN1" dengan alasan: %s", inputtext);
			banTime = time;
		}
		new query[248], date;
		date = gettime();
		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `player_bans` (`name`, `ip`, `admin`, `reason`, `ban_date`, `ban_expire`) VALUES ('%s', '%s', '%s', '%s', '%d', '%d')", AccountData[ClickPlayerID[playerid]][pUCP], PlayerIP, AccountData[playerid][pAdminname], inputtext, gettime(), banTime);
		mysql_tquery(g_SQL, query);

		mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `warninglogs` SET `pID`=%d, `WarnTime`=%d, `WarnType`=3, `WarnSender`='%s', `WarnReason`='%s'", AccountData[ClickPlayerID[playerid]][pID], date, AccountData[playerid][pAdminname], inputtext);
		mysql_tquery(g_SQL, query);

		new Status[128];
		if(time != 0) {
			format(Status, sizeof(Status), "%d Hari", time);
		} else {
			format(Status, sizeof(Status), "Permanent");
		}
		// format(shstr, sizeof(shstr), "**Admin:** %s\n**UCP Banned:** %s\n**Durasi Banned:** %s\n**Tanggal Banned:** %s\n**Alasan:** %s", AccountData[playerid][pAdminname], AccountData[ClickPlayerID[playerid]][pUCP], Status, ReturnDate(gettime()), inputtext);
		// SendEmbedMessage("District ", shstr, "Kemanan District  #1", "", "", "1152229209498980392", 0xff8fd5);
		KickEx(ClickPlayerID[playerid]);

		SetPVarInt(playerid, "BannedTime", -1);
		ClickPlayerID[playerid] = -1;
	}
	if(dialogid == DIALOG_VIP_NAME)
	{
		if(!response) return 1;
		if(!AccountData[playerid][pVip]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pengguna VIP!");

		if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_VIP_NAME, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Vip Name Custom",
		"Error: Tidak dapat diisi kosong!\nGunakan format dibawah ini untuk menambahkan warna\
		\n- (b) = Warna Biru\
		\n- (p) = Warna Pink\
		\n- (bl) = Warna Hitam\
		\b- (w) = Warna Putih\
		\n- (r) = Warna Merah\
		\n- (g) = Warna Hijau\
		\n- (y) = Warna Kuning\
		\n\nContoh: (r)Merah (y)Kuning (g)Hijau = Warna Akan Merah Kuning Hijau\
		\n(Masukkan nama vip custom anda dibawah ini):", "Submit", "Batal");

		format(AccountData[playerid][pVipNameCustom], 256, ReplaceString(inputtext));
		ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengubah Tag Vip Name!");
	}
	if(dialogid == DIALOG_DISPLAYBANNED)
	{
		if(!response) return KickEx(playerid);

		KickEx(playerid);
	}
	if(dialogid == DIALOG_MIXER)
	{
		if(!response) return SelectTextDraw(playerid, X11_DEEPSKYBLUE1);
        if(isnull(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Takaran tidak boleh kosong!");
		if(!IsNumeric(inputtext)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya angka!");
		if(strval(inputtext) < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Takaran tidak boleh kurang dari 1!");
		switch(jobs::mixer[playerid][mixerSelectCase])
		{
			case 1:
			{
                PlayerTextDrawSetString(playerid, jobs::Pmixer[playerid][5], inputtext);
				jobs::mixer[playerid][mixerConfirm][0] = strval(inputtext);
				ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menetapkan takaran semen");
			}
			case 2:
			{
                PlayerTextDrawSetString(playerid, jobs::Pmixer[playerid][6], inputtext);
				jobs::mixer[playerid][mixerConfirm][1] = strval(inputtext);
				ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menetapkan takaran pasir");
			}
			case 3:
			{
                PlayerTextDrawSetString(playerid, jobs::Pmixer[playerid][7], inputtext);
				jobs::mixer[playerid][mixerConfirm][2] = strval(inputtext);
				ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menetapkan takaran kerikil 1-2");
			}
			case 4:
			{
                PlayerTextDrawSetString(playerid, jobs::Pmixer[playerid][8], inputtext);
				jobs::mixer[playerid][mixerConfirm][3] = strval(inputtext);
				ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menetapkan takaran kerikil 2-3");
			}
			case 5:
			{
                PlayerTextDrawSetString(playerid, jobs::Pmixer[playerid][9], inputtext);
				jobs::mixer[playerid][mixerConfirm][4] = strval(inputtext);
				ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menetapkan takaran air");
			}
		}
		SelectTextDraw(playerid, X11_DEEPSKYBLUE1);
	}
    return 1;
}
