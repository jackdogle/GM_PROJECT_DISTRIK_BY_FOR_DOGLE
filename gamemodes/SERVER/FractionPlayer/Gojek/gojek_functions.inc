#include <YSI\y_hooks>
static const GojekRank[7][] = {
	"N/A",
	"Magang",
	"Junior",
	"Senior",
	"Bendahara",
	"Asisten Bos",
	"Bos Gojek"
};
enum e_stuffgojek
{
	STREAMER_TAG_AREA:GojekDuty,
	STREAMER_TAG_AREA:GojekLocker,
	STREAMER_TAG_AREA:GojekGarage,
	STREAMER_TAG_AREA:GojekDesk,
	STREAMER_TAG_AREA:GojekBrankas,

	Float:GojekGaragePOS[3],
	Float:GojekSpawnPOS[4]
};
new Gojek_Stuff[e_stuffgojek];
new Gojek_Object[MAX_PLAYERS][5];

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
	if(AccountData[playerid][pFaction] == FACTION_GOJEK)
	{
		if(areaid == Gojek_Stuff[GojekDuty])
		{
			if(!AccountData[playerid][pDutyGojek])
			{
				ShowKey(playerid, "[Y] ~g~On Duty");
			}
			else 
			{
				ShowKey(playerid, "[Y] ~r~Off Duty");
			}
		}

		if(areaid == Gojek_Stuff[GojekLocker] && AccountData[playerid][pDutyGojek])
		{
			ShowKey(playerid, "[Y] Locker Gojek");
		}

		if(areaid == Gojek_Stuff[GojekGarage] && AccountData[playerid][pDutyGojek])
		{
			ShowKey(playerid, "[Y] Garasi Gojek");
		}

		if(areaid == Gojek_Stuff[GojekDesk] && AccountData[playerid][pDutyGojek])
		{
			ShowKey(playerid, "[Y] Gojek Desk");
		}

		if(areaid == Gojek_Stuff[GojekBrankas] && AccountData[playerid][pDutyGojek])
		{
			ShowKey(playerid, "[Y] Brankas Gojek");
		}
	}
	return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
	if(areaid == Gojek_Stuff[GojekDuty])
	{
		HideShortKey(playerid);
	}

	if(areaid == Gojek_Stuff[GojekLocker])
	{
		HideShortKey(playerid);
	}

	if(areaid == Gojek_Stuff[GojekGarage])
	{
		HideShortKey(playerid);
	}

	if(areaid == Gojek_Stuff[GojekDesk])
	{
		HideShortKey(playerid);
	}

	if(areaid == Gojek_Stuff[GojekBrankas])
	{
		HideShortKey(playerid);
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(AccountData[playerid][pFaction] == FACTION_GOJEK)
		{
			if(IsPlayerInDynamicArea(playerid, Gojek_Stuff[GojekDuty]))
			{
				if(!AccountData[playerid][pDutyGojek])
				{
					AccountData[playerid][pDutyGojek] = true;
					ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang telah ~g~On Duty");
				}
				else 
				{
					AccountData[playerid][pDutyGojek] = false;
					ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang telah ~r~Off Duty");
				}
                AccountData[playerid][pDutyTimer] = SetTimerEx("FactDutyHour", 1000, true, "i", playerid);
				RefreshFactionMap(playerid);
			}

			if(IsPlayerInDynamicArea(playerid, Gojek_Stuff[GojekBrankas]) && AccountData[playerid][pDutyGojek])
			{
				ShowPlayerDialog(playerid, DIALOG_GOJVAULT, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Brankas Gojek",
				"Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Batal");
			}

			if(IsPlayerInDynamicArea(playerid, Gojek_Stuff[GojekLocker]) && AccountData[playerid][pDutyGojek])
			{
				ShowPlayerDialog(playerid, DIALOG_GOJEK_LOCKER, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Locker Gojek",
				"Baju Warga\n"GRAY"Baju Kerja", "Pilih", "Batal");
			}

			if(IsPlayerInDynamicArea(playerid, Gojek_Stuff[GojekDesk]) && AccountData[playerid][pDutyGojek])
			{
				if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Bendahara untuk akses desk!");

				ShowPlayerDialog(playerid, DIALOG_BOSDESK_GOJEK, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Bos Desk",
				"Invite\ 
				\n"GRAY"Kelola Jabatan\ 
				\nKick\ 
				\n"GRAY"Lihat Anggota\ 
				\nSaldo Finansial\ 
				\n"GRAY"Deposit\ 
				\nWithdraw", "Pilih", "Batal");
			}

			if(IsPlayerInRangeOfPoint(playerid, 2.0, Gojek_Stuff[GojekGaragePOS][0], Gojek_Stuff[GojekGaragePOS][1], Gojek_Stuff[GojekGaragePOS][2]) && AccountData[playerid][pDutyGojek])
			{
				ShowPlayerDialog(playerid, DIALOG_GOJEK_GARAGE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Garasi Gojek",
				"Keluarkan Kendaraan\ 
				\n"GRAY"Simpan Kendaraan\ 
				\nBeli Kendaraan\ 
				\n"GRAY"Hapus Kendaraan", "Pilih", "Batal");
			}
		}
	}
	return 1;
}

VarsDoorGojek()
{
	Gojek_Stuff[GojekDuty] = CreateDynamicSphere(1526.4541,-2162.7046,13.5798, 2.0, -1, -1, -1);
	Gojek_Stuff[GojekLocker] = CreateDynamicSphere(1492.7103,-2178.9375,13.5788, 2.0, -1, -1, -1);
	Gojek_Stuff[GojekGarage] = CreateDynamicSphere(1501.3788,-2182.6367,13.5669, 2.0, -1, -1, -1);
	Gojek_Stuff[GojekDesk] = CreateDynamicSphere(1494.7322,-2180.8149,19.3028, 2.0, -1, -1, -1);
	Gojek_Stuff[GojekBrankas] = CreateDynamicSphere(1491.5472,-2176.1311,13.5788, 2.0, -1, -1, -1);

	Gojek_Stuff[GojekGaragePOS][0] = 1501.3788;
	Gojek_Stuff[GojekGaragePOS][1] = -2182.6367;
	Gojek_Stuff[GojekGaragePOS][2] = 13.5669;
	
	Gojek_Stuff[GojekSpawnPOS][0] = 1503.1768;
	Gojek_Stuff[GojekSpawnPOS][1] = -2173.6721;
	Gojek_Stuff[GojekSpawnPOS][2] = 13.3105;
	Gojek_Stuff[GojekSpawnPOS][3] = 269.7935;
}

hook OnGameModeInit()
{
	VarsDoorGojek();
	return 1;
}

DialogPages:GojekSetRank(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Gojek Verona!");
    if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Asisten Bos untuk mengakses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 7 ORDER BY `Char_FactionRank` DESC");
    new rows = cache_num_rows();
    if(rows)
    {
        cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
        cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak dapat mengatur jabatan sendiri!");
        if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengatur jabatan rank diatasmu!");
        ShowPlayerDialog(playerid, DIALOG_RANK_SET_GOJEK, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan",
		"Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\ 
		\n1. Magang\ 
		\n2. Junior\ 
		\n3. Senior\ 
		\n4. Bendahara\ 
		\n5. Asisten Bos\ 
		\n6. Bos Gojek", "Set", "Batal");
    }
    return 1;
}

DialogPages:GojekKickMember(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Gojek Verona!");
    if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Asisten Bos untuk mengakses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 7 ORDER BY `Char_FactionRank` DESC");
    if(cache_num_rows())
    {
        new pidrow, fckname[64], fckrank, fcklastlogin[30], kckstr[225], icsr[128];

        cache_get_value_name_int(listitem, "pID", pidrow);
        cache_get_value_name(listitem, "Char_Name", fckname);
        cache_get_value_name_int(listitem, "Char_FactionRank", fckrank);
        cache_get_value_name(listitem, "Char_LastLogin", fcklastlogin);

        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat kick diri sendiri!");
        if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat kick pangkat diatasmu!");

        /* kendaraan pribadi yg milik faction di cek*/
        new strgbg[158];
        mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_OwnerID`=%d AND `PVeh_Faction` = 7", pidrow);
        mysql_tquery(g_SQL, strgbg);

        foreach(new i : Player)
        {
            if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && pidrow == AccountData[i][pID])
            {
                AccountData[i][pFaction] = 0;
                AccountData[i][pFactionRank] = 0;

                //jika kendaraan pribadi ada di server dan player sedang online, maka kendaraan fisik dihapus
                foreach(new pvid : PvtVehicles)
                {
                    if(PlayerVehicle[pvid][pVehExists] && PlayerVehicle[pvid][pVehOwnerID] == AccountData[i][pID])
                    {
                        if(PlayerVehicle[pvid][pVehFaction] == FACTION_GOJEK)
                        {
                            PlayerVehicle[pvid][pVehExists] = false;

                            if(IsValidVehicle(PlayerVehicle[pvid][pVehPhysic]))
                            {
                                DisableVehicleSpeedCap(PlayerVehicle[pvid][pVehPhysic]);
                                SetVehicleNeonLights(PlayerVehicle[pvid][pVehPhysic], false, PlayerVehicle[pvid][pVehNeon], 0);

                                DestroyVehicle(PlayerVehicle[pvid][pVehPhysic]);
                                PlayerVehicle[pvid][pVehPhysic] = INVALID_VEHICLE_ID;
                            }

                            Iter_Remove(PvtVehicles, pvid);
                        }
                    }
                }
                if(AccountData[i][pDutyGojek])
                    AccountData[i][pDutyGojek] = false;
				if(AccountData[i][pUsingUniform])
					AccountData[i][pUsingUniform] = false;
				SetPlayerSkin(i, AccountData[i][pSkin]);
				RefreshFactionMap(i);
                ShowTDN(i, NOTIFICATION_WARNING, "Anda telah dikeluarkan dari faction Gojek Verona!");
            }
        }
        mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`=0, `Char_FactionRank`=0, `Char_UsingUniform`=0 WHERE `pID`=%d", pidrow);
        mysql_tquery(g_SQL, icsr);
        format(kckstr, sizeof(kckstr), "Anda telah berhasil menendang anggota:\n \
        Nama: %s\n\
        Rank: %s\n\
        Last Online: %s", fckname, GojekRank[fckrank], fcklastlogin);
        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota",
        kckstr, "Tutup", "");

		AccountData[playerid][pTempSQLFactMemberID] = -1;
        AccountData[playerid][pTempSQLFactRank] = 0;
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case DIALOG_BOSDESK_GOJEK:
		{
			if(!response) return 1;
			if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Gojek!");
			if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Bendahara untuk akses desk!");
			switch(listitem)
			{
				case 0:
				{
					new frmxt[522], count = 0;

					foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 1.5))
					{
						format(frmxt, sizeof(frmxt), "%sPlayer ID: %d\n", frmxt, i);
						NearestPlayer[playerid][count++] = i;
					}

					if(count == 0)
					{
						PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
						return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Invite",
						"Tidak ada orang di sekitar anda!", "Tutup", "");
					}

					ShowPlayerDialog(playerid, DIALOG_GOJEK_INVITECONF, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Invite", frmxt, "Pilih", "Batal");
				}
				case 1:
				{
					mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 7 ORDER BY Char_FactionRank DESC");

					new rows = cache_num_rows();
					if(rows)
					{
						new fckname[64], fckrank, fcklastlogin[30];

						AddDialogListitem(playerid, "Nama\tRank\tLast Online");
						for(new i; i < rows; ++i)
						{
							cache_get_value_name(i, "Char_Name", fckname);
							cache_get_value_name_int(i, "Char_FactionRank", fckrank);
							cache_get_value_name(i, "Char_LastLogin", fcklastlogin);

							AddDialogListitem(playerid, "%s\t%s\t%s", fckname, GojekRank[fckrank], fcklastlogin);
						}
						ShowPlayerDialogPages(playerid, "GojekSetRank", DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Set Jabatan", "Pilih", "Batal", 15, ""GREEN">> Lanjut", ""ORANGE"<< Kembali");
					}
					else 
					{
						PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
						return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Set Jabatan", "Tidak ada Anggota Gojek!", "Tutup", "");
					}
				}
				case 2:
				{
					mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 7 ORDER BY Char_FactionRank DESC");

					new rows = cache_num_rows();
					if(rows)
					{
						new fckname[64], fckrank, fcklastlogin[30];

						AddDialogListitem(playerid, "Nama\tRank\tLast Online");
						for(new i; i < rows; ++i)
						{
							cache_get_value_name(i, "Char_Name", fckname);
							cache_get_value_name_int(i, "Char_FactionRank", fckrank);
							cache_get_value_name(i, "Char_LastLogin", fcklastlogin);

							AddDialogListitem(playerid, "%s\t%s\t%s", fckname, GojekRank[fckrank], fcklastlogin);
						}
						ShowPlayerDialogPages(playerid, "GojekKickMember", DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Kick Anggota", "Kick", "Batal", 15, ""GREEN">> Lanjut", ""ORANGE"<< Kembali");
					}
					else 
					{
						PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
						return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota", "Tidak ada Anggota Gojek!", "Tutup", "");
					}
				}
				case 3:
				{
					new list[1218];
					format(list, sizeof(list), "Nama\tRank\tStatus\n");
					foreach(new i : Player) if(AccountData[i][pFaction] == FACTION_GOJEK)
					{
						format(list, sizeof(list), "%s%s\t%s\t%s\n", list, AccountData[i][pName], GetFactionRank(i), AccountData[i][pDutyPD] ? ""GREEN"On Duty" : ""DARKRED"Off Duty");
					}
					ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Anggota", list, "Tutup", "");
				}
				case 4:
				{
					new frmxt[158];
					format(frmxt, sizeof(frmxt), "Perusahaan Gojek Verona saat ini memiliki saldo sebesar\ 
					\n"DARKGREEN"%s", FormatMoney(GojekMoneyVault));
					ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Gojek Money", frmxt, "Tutup", "");
				}
				case 5:
				{
					ShowPlayerDialog(playerid, DIALOG_DEPOSIT_GOJEK, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek Deposit",
					"Mohon masukkan nominal deposit untuk saldo perusahaan:", "Input", "Batal");
				}
				case 6:
				{
					ShowPlayerDialog(playerid, DIALOG_WITHDRAW_GOJEK, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek Withdraw",
					"Mohon masukkan nominal penarikan tunai dari saldo perusahaan:", "Input", "Batal");
				}
			}
		}
		case DIALOG_GOJEK_LOCKER:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
			if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Gojek Verona!");
			
			switch(listitem)
			{
				case 0:
				{
					SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
					AccountData[playerid][pUsingUniform] = false;
				}
				case 1:
				{
					AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (188) : (224);
					SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
					AccountData[playerid][pUsingUniform] = true;
					ShowTDN(playerid, NOTIFICATION_INFO, "Sekarang anda menggunakan baju kerja");
				}
			}
		}
		case DIALOG_GOJEK_INVITECONF:
		{
			static icsr[855];
			if(!response) return 1;
			if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Gojek!");
			if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Bendahara untuk akses desk!");

			new targetid = NearestPlayer[playerid][listitem];
			if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
			AccountData[targetid][pFaction] = FACTION_GOJEK;
			AccountData[targetid][pFactionRank] = 1;
			RefreshFactionMap(targetid);
			mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`= 7, `Char_FactionRank` = 1 WHERE `pID`=%d", AccountData[targetid][pID]);
			mysql_tquery(g_SQL, icsr);
			ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil invite faction %s", AccountData[targetid][pName]));
		}
		case DIALOG_RANK_SET_GOJEK:
		{
			if(!response) return 1;
			if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Gojek Verona!");
			if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal Rank Asisten Bos untuk akses Bos Desk!");

			if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_GOJEK, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
			"Error: Tidak dapat diisi kosong!\n\
			Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
			1. Magang\n\
			2. Junior\n\
			3. Senior\n\
			4. Bendahara\n\
			5. Asisten Bos\n\
			6. Bos Gojek", "Set", "Batal");

			if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_GOJEK, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
			"Error: Hanya dapat diisi angka!\n\
			Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
			1. Magang\n\
			2. Junior\n\
			3. Senior\n\
			4. Bendahara\n\
			5. Asisten Bos\n\
			6. Bos Gojek", "Set", "Batal");

			if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pFactionRank]) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_GOJEK, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
			"Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
			Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
			1. Magang\n\
			2. Junior\n\
			3. Senior\n\
			4. Bendahara\n\
			5. Asisten Bos\n\
			6. Bos Gojek", "Set", "Batal");

			new affah[128];
			mysql_format(g_SQL, affah, sizeof(affah), "UPDATE `player_characters` SET `Char_FactionRank`=%d WHERE `pID`=%d", strval(inputtext), AccountData[playerid][pTempSQLFactMemberID]);
			mysql_tquery(g_SQL, affah);

			foreach(new i : Player)
			{
				if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && AccountData[playerid][pTempSQLFactMemberID] == AccountData[i][pID])
				{
					AccountData[i][pFactionRank] = strval(inputtext);
					ShowTDN(i, NOTIFICATION_INFO, "Jabatan baru anda di faction telah diubah");
				}
			}

			ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengubah jabatan faction player tersebut");
		}
		case DIALOG_DEPOSIT_GOJEK:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
			if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Gojek!");
			if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Bendahara untuk akses desk!");
			new depocash = strval(inputtext), frmtmny[128];
			if(depocash > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak sebanyak itu!");
			if(depocash < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal kurang dari $1 untuk deposit!");
			TakeMoney(playerid, depocash);
			GojekMoneyVault += depocash;
			mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `gojekmoneyvault` = %d WHERE `ID` = 0", GojekMoneyVault);
			mysql_tquery(g_SQL, frmtmny);
			ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil deposit %s untuk Gojek Verona", FormatMoney(depocash)));
		}
		case DIALOG_WITHDRAW_GOJEK:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
			if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Gojek!");
			if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Bendahara untuk akses desk!");
			new withdrawcash = strval(inputtext), frmtmny[128];
			if(withdrawcash > GojekMoneyVault) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang perusahaan tidak sebanyak itu!");
			if(withdrawcash < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal kurang dari $1 untuk withdraw!");
			GojekMoneyVault -= withdrawcash;
			GiveMoney(playerid, withdrawcash);

			mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `gojekmoneyvault` = %d WHERE `ID` = 0", GojekMoneyVault);
			mysql_tquery(g_SQL, frmtmny);

			AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], withdrawcash, "Gojek");

			ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil withdraw %s dari Gojek Verona", FormatMoney(withdrawcash)));
		}
		case DIALOG_GOJEK_GARAGE:
		{
			if(!response) return 1;
			if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda bukan anggota Gojek Verona");

			switch(listitem)
			{
				case 0: // Keluarkan
				{
					if(CountPlayerFactVehInGarage(playerid, FACTION_GOJEK) < 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun di garasi ini!");

					new id, count = CountPlayerFactVehInGarage(playerid, FACTION_GOJEK), list[596];
					format(list,sizeof(list),"No\tModel Kendaraan\tNomor Plat\n");
					for(new iter = 0; iter < count; iter++)
					{
						id = GetVehicleIDStoredFactGarage(playerid, iter, FACTION_GOJEK);
						if(iter == count)
						{
							format(list,sizeof(list),"%s%d\t%s\t%s",list,iter+1,GetVehicleModelName(PlayerVehicle[id][pVehModelID]),PlayerVehicle[id][pVehPlate]);
						} else format(list,sizeof(list),"%s%d\t%s\t%s\n",list,iter+1,GetVehicleModelName(PlayerVehicle[id][pVehModelID]),PlayerVehicle[id][pVehPlate]);
					}
					ShowPlayerDialog(playerid, DIALOG_GOJEK_GARAGE_TAKEOUT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Garasi Gojek", list, "Pilih", "Batal");
				}
				case 1:// Simpan Vehicle
				{
					new carid = -1, bool: foundnearby = false;
					if((carid = Vehicle_Nearest(playerid, 10.0)) != -1)
					{
						if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
						if(PlayerVehicle[carid][pVehRental] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat disimpan digarasi Faction!");
						if(PlayerVehicle[carid][pVehFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan kendaraan Gojek!");
						
						Vehicle_GetStatus(carid);
						PlayerVehicle[carid][pVehFactStored] = FACTION_GOJEK;

						foundnearby = true;

						if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]))
						{
							DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
							SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

							DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
							PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
						}
					}
					if(!foundnearby) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan dari PT.Gojek Verona milik anda di sekitar!");
				}
				case 2://Beli Kendaraan
				{
					ShowPlayerDialog(playerid, DIALOG_GOJEK_GARAGE_BUY, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Beli Kendaraan",
					"Model\tHarga\ 
					\nWayfarer\t$4000\ 
					\n"GRAY"FCR-900\t"GRAY"$5000\ 
					\nBF-400\t$5000\ 
					\n"GRAY"Stratum\t"GRAY"$8000", "Pilih", "Batal");	
				}
				case 3:// Hapus Kendaraan
				{
					new frmtdel[158];
					mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 7 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
					mysql_query(g_SQL, frmtdel);

					new rows = cache_num_rows();
					if(rows)
					{
						new list[255], havpid, havmod;
						
						format(list, sizeof(list), "Database ID\tModel\n");
						for(new x; x < rows; ++x)
						{
							cache_get_value_name_int(x, "id", havpid);
							cache_get_value_name_int(x, "PVeh_ModelID", havmod);

							format(list, sizeof(list), "%s%d\t%s\n", list, havpid, GetVehicleModelName(havmod));
						}
						ShowPlayerDialog(playerid, DIALOG_GOJEK_GARAGE_DELETE, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Hapus Kendaraan", list, "Hapus", "Batal");
					}
					else 
					{
						PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
						return Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Kendaraan", "Anda tidak memiliki kendaraan Gojek", "Tutup", "");
					}
				}
			}
		}
		case DIALOG_GOJEK_GARAGE_TAKEOUT:
		{
			if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Gojek!");
            if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            new id = GetVehicleIDStoredFactGarage(playerid, listitem, FACTION_GOJEK);
            if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            if(!IsPlayerInRangeOfPoint(playerid, 2.0, Gojek_Stuff[GojekGaragePOS][0], Gojek_Stuff[GojekGaragePOS][1], Gojek_Stuff[GojekGaragePOS][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat Garasi Gojek!");
            if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
            PlayerVehicle[id][pVehParked] = -1;
            PlayerVehicle[id][pVehHouseGarage] = -1;
			PlayerVehicle[id][pVehHelipadGarage] = -1;
            PlayerVehicle[id][pVehFamiliesGarage] = -1;
            PlayerVehicle[id][pVehFactStored] = -1;

			if(PlayerVehicle[id][pVehLocked])
				PlayerVehicle[id][pVehLocked] = false;

            PlayerVehicle[id][pVehPos][0] = Gojek_Stuff[GojekSpawnPOS][0];
            PlayerVehicle[id][pVehPos][1] = Gojek_Stuff[GojekSpawnPOS][1];
            PlayerVehicle[id][pVehPos][2] = Gojek_Stuff[GojekSpawnPOS][2];
            PlayerVehicle[id][pVehPos][3] = Gojek_Stuff[GojekSpawnPOS][3];

            OnPlayerVehicleRespawn(id);

            SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
		}
		case DIALOG_GOJEK_GARAGE_BUY:
		{
			if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Gojek!");
            if(!IsPlayerInRangeOfPoint(playerid, 2.0, Gojek_Stuff[GojekGaragePOS][0], Gojek_Stuff[GojekGaragePOS][1], Gojek_Stuff[GojekGaragePOS][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat Garasi Gojek!");

            new count = 0;
            foreach(new carid : PvtVehicles)
            {
                if(PlayerVehicle[carid][pVehExists] && PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
                    count ++;
            }
            if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");

			switch(listitem)
			{
				case 0: //wayfarer
				{
					if(AccountData[playerid][pMoney] < 4000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 4000);
					//VehicleFaction_Create(playerid, 586, FACTION_GOJEK, Gojek_Stuff[GojekSpawnPOS][0], Gojek_Stuff[GojekSpawnPOS][1], Gojek_Stuff[GojekSpawnPOS][2], Gojek_Stuff[GojekSpawnPOS][3], 86, 86);
					ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan!");
				}
				case 1: //fcr 900
				{
					if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 5000);
					//VehicleFaction_Create(playerid, 521, FACTION_GOJEK, Gojek_Stuff[GojekSpawnPOS][0], Gojek_Stuff[GojekSpawnPOS][1], Gojek_Stuff[GojekSpawnPOS][2], Gojek_Stuff[GojekSpawnPOS][3], 86, 86);
					ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan!");
				}
				case 2: //bf
				{
					if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 5000);
					//VehicleFaction_Create(playerid, 581, FACTION_GOJEK, Gojek_Stuff[GojekSpawnPOS][0], Gojek_Stuff[GojekSpawnPOS][1], Gojek_Stuff[GojekSpawnPOS][2], Gojek_Stuff[GojekSpawnPOS][3], 86, 86);
					ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan!");
				}
				case 3: //stratum
				{
					if(AccountData[playerid][pMoney] < 8000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
					TakeMoney(playerid, 8000);
					//VehicleFaction_Create(playerid, 561, FACTION_GOJEK, Gojek_Stuff[GojekSpawnPOS][0], Gojek_Stuff[GojekSpawnPOS][1], Gojek_Stuff[GojekSpawnPOS][2], Gojek_Stuff[GojekSpawnPOS][3], 86, 86);
					ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan!");
				}
			}
		}
		case DIALOG_GOJEK_GARAGE_DELETE:
		{
			if(!response) return 1;
			if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda bukan anggota Gojek Verona");

			new frmtdel[158];
			mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 7 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
			mysql_query(g_SQL, frmtdel);

			new rows = cache_num_rows();
			if(rows)
			{
				new havpid, havmods, kckstr[255], strgbg[128];
				
				cache_get_value_name_int(listitem, "id", havpid);
				cache_get_value_name_int(listitem, "PVeh_ModelID", havmods);

				format(kckstr, sizeof(kckstr), "Anda berhasil menghapus kendaraan:\
				\nDatabase ID: %d\
				\nModel: %s", havpid, GetVehicleModelName(havmods));
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Kendaraan", kckstr, "Tutup", "");

				new pvid = GetFactionVehicleIDFromListitem(playerid, listitem, FACTION_GOJEK);

				PlayerVehicle[pvid][pVehExists] = false;
				if(IsValidVehicle(PlayerVehicle[pvid][pVehPhysic]))
				{
					DisableVehicleSpeedCap(PlayerVehicle[pvid][pVehPhysic]);
					SetVehicleNeonLights(PlayerVehicle[pvid][pVehPhysic], false, PlayerVehicle[pvid][pVehNeon], 0);

					DestroyVehicle(PlayerVehicle[pvid][pVehPhysic]);
					PlayerVehicle[pvid][pVehPhysic] = INVALID_VEHICLE_ID;
				}
				mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `id` = %d", havpid);
				mysql_tquery(g_SQL, strgbg);

				Iter_Remove(PvtVehicles, pvid);
			}
		}
		case DIALOG_GOJVAULT:
		{
			if(!response) return 0;
			if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Gojek!");
			switch(listitem)
			{
				case 0: //deposit
                {
                    FactionBrankas[playerid][factionBrankasID] = 0;
                    FactionBrankas[playerid][factionBrankasTemp] = EOS;
                    FactionBrankas[playerid][factionBrankasModel] = 0;
                    FactionBrankas[playerid][factionBrankasQuant] = 0;

                    new str[1218], amounts, itemname[64], tss[125];
                    format(str, sizeof(str), "Nama Item\tJumlah\tBerat (-/-)\n");
                    mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
                    mysql_query(g_SQL, tss);
                    new rows = cache_num_rows();
                    if(rows) 
                    {
                        for(new x; x < rows; ++x)
                        {
                            cache_get_value_name(x, "invItem", itemname);
                            cache_get_value_name_int(x, "invQuantity", amounts);

                            format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                        }
                        ShowPlayerDialog(playerid, DIALOG_GOJVAULT_DEPOSIT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas Gojek", str, "Pilih", "Batal");
                    }
                    else 
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas Gojek",
                        "Anda tidak memiliki barang untuk disimpan!", "Tutup", "");
                    }
                }
                case 1: //withdraw
                {
                    new str[128], amounts, itemname[64];
                    format(str, sizeof(str), "Nama Item\tJumlah\tBerat (-/-)\n");
                    mysql_query(g_SQL, "SELECT * FROM `gojek_brankas` WHERE `PID`=0");
                    if(cache_num_rows() > 0)
                    {
                        for(new x; x < cache_num_rows(); ++x)
                        {
                            cache_get_value_name(x, "Item", itemname);
                            cache_get_value_name_int(x, "Quantity", amounts);

                            format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                        }
                        ShowPlayerDialog(playerid, DIALOG_GOJVAULT_WITHDRAW, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas Gojek", str, "Pilih", "Batal");
                    }
                    else 
                    {
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas Gojek",
                        "Tidak ada barang di brankas saat ini!", "Tutup", "");
                    }
                }
			}
		}
		case DIALOG_GOJVAULT_DEPOSIT:
		{
			if(!response)
            {
                return 1;
            }

            if(listitem == -1)
            {
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item!");
            }

            new tss[128];
            mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
            mysql_query(g_SQL, tss);
            if(cache_num_rows() > 0)
            {
                cache_get_value_name(listitem, "invItem", FactionBrankas[playerid][factionBrankasTemp]);
                cache_get_value_name_int(listitem, "invModel", FactionBrankas[playerid][factionBrankasModel]);
                cache_get_value_name_int(listitem, "invQuantity", FactionBrankas[playerid][factionBrankasQuant]);

                new shstr[528];
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_GOJVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Gojek",
                shstr, "Input", "Batal");
            }
		}
		case DIALOG_GOJVAULT_IN:
		{
			if(!response)
            {
                return 1;
            }

            new shstr[512];
            if(isnull(inputtext))
            {
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nTidak dapat diisi kosong!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_GOJVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Gojek",
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_GOJVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Gojek",
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[playerid][factionBrankasQuant])
            {
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_GOJVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Gojek",
                shstr, "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);
            Inventory_Remove(playerid, FactionBrankas[playerid][factionBrankasTemp], quantity);
            ShowItemBox(playerid, sprintf("Removed %dx", quantity), FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel]);

            new invstr[1028];
            mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `gojek_brankas` WHERE `PID`=0 AND `Item` = '%s'", FactionBrankas[playerid][factionBrankasTemp]);
            mysql_query(g_SQL, shstr);
            new rows = cache_num_rows();
            if(rows > 0)
            {
                mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `gojek_brankas` SET `Quantity` = `Quantity` + %d WHERE `PID` = 0 AND `Item`='%s'", quantity, FactionBrankas[playerid][factionBrankasTemp]);
                mysql_tquery(g_SQL, invstr, "OnGojekDeposit", "i", playerid);
            }
            else 
            {
                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `gojek_brankas` SET `PID`=0, `Item`='%s', `Model`=%d, `Quantity`=%d", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel], quantity);
                mysql_tquery(g_SQL, invstr, "OnGojekDeposit", "i", playerid);
            }
		}
		case DIALOG_GOJVAULT_WITHDRAW:
		{
			if(!response)
            {
                return 1;
            }

            if(listitem == -1)
            {
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item!");
            }

            new shstr[1218];
            mysql_query(g_SQL, "SELECT * FROM `gojek_brankas` WHERE `PID`=0");
            if(cache_num_rows() > 0)
            {
                cache_get_value_name_int(listitem, "ID", FactionBrankas[playerid][factionBrankasID]);
                cache_get_value_name(listitem, "Item", FactionBrankas[playerid][factionBrankasTemp]);
                cache_get_value_name_int(listitem, "Model", FactionBrankas[playerid][factionBrankasModel]);
                cache_get_value_name_int(listitem, "Quantity", FactionBrankas[playerid][factionBrankasQuant]);

                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_GOJVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Gojek",
                shstr, "Input", "Batal");
            }
            else 
            {
                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas Gojek",
                "Brankas ini isinya kosong!", "Tutup", "");
            }
		}
		case DIALOG_GOJVAULT_OUT:
		{
			if(!response)
            {
                return 1;
            }

            new shstr[512];
            if(isnull(inputtext))
            {
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nTidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_GOJVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Gojek",
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_GOJVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Gojek",
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[playerid][factionBrankasQuant])
            {
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_GOJVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Gojek",
                shstr, "Input", "Batal");
                return 1;
            }
            new quantity = strval(inputtext), jts[150];

            if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");

            FactionBrankas[playerid][factionBrankasQuant] -= quantity;
            if(FactionBrankas[playerid][factionBrankasQuant] > 0)
            {
                mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `gojek_brankas` SET `Quantity`=%d WHERE `ID`=%d", FactionBrankas[playerid][factionBrankasQuant], FactionBrankas[playerid][factionBrankasID]);
                mysql_tquery(g_SQL, jts);
            }
            else 
            {
                mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `gojek_brankas` WHERE `ID`=%d", FactionBrankas[playerid][factionBrankasID]);
                mysql_tquery(g_SQL, jts);
            }
            Inventory_Add(playerid, FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel], quantity);
            ShowItemBox(playerid, sprintf("Received %dx", quantity), FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel]);
        
            FactionBrankas[playerid][factionBrankasID] = 0;
            FactionBrankas[playerid][factionBrankasTemp] = EOS;
            FactionBrankas[playerid][factionBrankasModel] = 0;
            FactionBrankas[playerid][factionBrankasQuant] = 0;
		}
	}
	return 1;
}

forward OnGojekDeposit(playerid);
public OnGojekDeposit(playerid)
{
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyimpan item");
    FactionBrankas[playerid][factionBrankasID] = 0;
    FactionBrankas[playerid][factionBrankasTemp] = EOS;
    FactionBrankas[playerid][factionBrankasModel] = 0;
    FactionBrankas[playerid][factionBrankasQuant] = 0;
    return 1;
}
