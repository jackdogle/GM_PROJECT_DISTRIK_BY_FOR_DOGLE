#include <YSI\y_hooks>
static const TransRank[6][] = 
{
    "N/A",
    "Magang",
    "Junior",
    "Senior",
    "Kepala Transport",
    "Trans CEO"
};
enum e_stufftrans
{
    STREAMER_TAG_AREA:TransDuty,
    STREAMER_TAG_AREA:TransLocker,
    STREAMER_TAG_AREA:TransGarage,
    STREAMER_TAG_AREA:TransDesk,
    STREAMER_TAG_AREA:TransStorage,
    
    Float:TransgaragePos[3],
    Float:TransgaragespawnPos[4]
};
new Trans_Stuff[e_stufftrans];
new STREAMER_TAG_OBJECT: Trans_Object[MAX_PLAYERS][5];

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pFaction] == FACTION_TRANS)
    {
        if(areaid == Trans_Stuff[TransDuty])
        {
            if(!AccountData[playerid][pDutyTrans])
			{
				ShowKey(playerid, "[Y] ~g~On Duty");
			}
			else 
			{
				ShowKey(playerid, "[Y] ~r~Off Duty");
			}
        }

        if(areaid == Trans_Stuff[TransLocker] && AccountData[playerid][pDutyTrans])
		{
			ShowKey(playerid, "[Y] Locker Trans");
		}

		if(areaid == Trans_Stuff[TransDesk] && AccountData[playerid][pDutyTrans])
		{
			ShowKey(playerid, "[Y] Trans Desk");
		}

		if(areaid == Trans_Stuff[TransStorage] && AccountData[playerid][pDutyTrans])
		{
			ShowKey(playerid, "[Y] Brankas Trans");
		}
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
	if(areaid == Trans_Stuff[TransDuty])
	{
		HideShortKey(playerid);
	}

	if(areaid == Trans_Stuff[TransLocker])
	{
		HideShortKey(playerid);
	}

	if(areaid == Trans_Stuff[TransGarage])
	{
		HideShortKey(playerid);
	}

	if(areaid == Trans_Stuff[TransDesk])
	{
		HideShortKey(playerid);
	}

	if(areaid == Trans_Stuff[TransStorage])
	{
		HideShortKey(playerid);
	}
	return 1;
}

hook OnGameModeInit()
{
    Trans_Stuff[TransDuty] = CreateDynamicSphere(1547.8783, -2163.1912, 13.7381, 1.5, 0, 0, -1);
    Trans_Stuff[TransDesk] = CreateDynamicSphere(1555.9905, -2179.6467, 13.7381, 1.5, 0, 0, -1);
    Trans_Stuff[TransLocker] = CreateDynamicSphere(1549.8779, -2179.3242, 13.7381, 1.5, 0, 0, -1);
    Trans_Stuff[TransStorage] = CreateDynamicSphere(1557.0094, -2170.8276, 13.7381, 1.5, 0, 0, -1);
    Trans_Stuff[TransGarage] = CreateDynamicSphere(1501.7401, -2160.7627, 13.5650, 1.5, 0, 0, -1);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pFaction] == FACTION_TRANS)
        {
            if(IsPlayerInDynamicArea(playerid, Trans_Stuff[TransDuty]))
            {
                if(!AccountData[playerid][pDutyTrans])
                {
                    AccountData[playerid][pDutyTrans] = true;
                    SetFactionColor(playerid);
                    AccountData[playerid][pDutyTimer] = SetTimerEx("FactDutyHour", 1000, true, "i", playerid);
                    ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~g~On Duty~w~ Trans");
                }
                else
                {
                    if(AccountData[playerid][pUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih menggunakan seragam kerja!");
                    AccountData[playerid][pDutyTrans] = false;
                    SetPlayerColor(playerid, COLOR_WHITE);
                    ShowTDN(playerid, NOTIFICATION_INFO, "Anda sekarang ~r~Off Duty~w~ Trans");
                }
                RefreshFactionMap(playerid);
            }

            if(IsPlayerInDynamicArea(playerid, Trans_Stuff[TransStorage]) && AccountData[playerid][pDutyTrans])
            {
                if(NearPlayerOpenStorage(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain disekitar sedang membuka brankas!");
                if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Kepala Transport untuk akses Brankas!");

                AccountData[playerid][menuShowed] = true;
                ShowPlayerDialog(playerid, DIALOG_TRANSVAULT, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Brankas Trans",
                "Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, Trans_Stuff[TransLocker]) && AccountData[playerid][pDutyTrans])
            {
                ShowPlayerDialog(playerid, DIALOG_TRANS_LOCKER, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Locker Trans",
                "Baju Biasa\n"GRAY"Baju 1\nBaju 2", "Pilih", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, Trans_Stuff[TransDesk]) && AccountData[playerid][pDutyTrans])
            {
                if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Kepala Transport untuk akses desk!");

				ShowPlayerDialog(playerid, DIALOG_TRANS_DESK, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Bos Desk",
				"Invite\
				\n"GRAY"Kelola Jabatan\
				\nKick\
				\n"GRAY"Lihat Anggota\
				\nSaldo Finansial\
				\n"GRAY"Deposit\
				\nWithdraw", "Pilih", "Batal");
            }

            /*if(IsPlayerInRangeOfPoint(playerid, 2.0, Trans_Stuff[TransgaragePos][0], Trans_Stuff[TransgaragePos][1], Trans_Stuff[TransgaragePos][2]) && AccountData[playerid][pDutyTrans])
            {
                ShowPlayerDialog(playerid, DIALOG_TRANS_GARAGE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Garasi Trans",
                "Keluarkan Kendaraan\
                \n"GRAY"Simpan Kendaraan\
                \nBeli Kendaraan\
                \n"GRAY"Hapus Kendaraan", "Pilih", "Batal");
            }*/
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_TRANS_DESK:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Transportasi District !");
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Kepala Transport untuk akses desk!");
            switch(listitem)
            {
                case 0:
                {
                    new frmxt[525], count = 0;

                    foreach(new i : Player) if((i != playerid) && IsPlayerNearPlayer(playerid, i, 1.5))
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

					ShowPlayerDialog(playerid, DIALOG_TRANS_INVITECONF, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Invite", frmxt, "Pilih", "Batal");
                }
                case 1:
                {
                    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 4 ORDER BY `Char_FactionRank` DESC");

					new rows = cache_num_rows();
					if(rows)
					{
						new fckname[64], fckrank, fcklastlogin[30], shstr[2048];

						format(shstr, sizeof(shstr), "Nama\tRank\tLast Online\n");
						for(new i; i < rows; ++i)
						{
							cache_get_value_name(i, "Char_Name", fckname);
							cache_get_value_name_int(i, "Char_FactionRank", fckrank);
							cache_get_value_name(i, "Char_LastLogin", fcklastlogin);

							format(shstr, sizeof(shstr), "%s%s\t%s\t%s\n", shstr, fckname, TransRank[fckrank], fcklastlogin);
						}
						ShowPlayerDialog(playerid, DIALOG_TRANSSETRANK, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Set Jabatan", shstr, "Pilih", "Batal");
					}
					else 
					{
						PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
						return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Set Jabatan", "Tidak ada Anggota Trans!", "Tutup", "");
					}
                }
                case 2:
                {
                    mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 4 ORDER BY Char_FactionRank DESC");

					new rows = cache_num_rows();
					if(rows)
					{
						new fckname[64], fckrank, fcklastlogin[30], shstr[2048];

						format(shstr, sizeof(shstr), "Nama\tRank\tLast Online\n");
						for(new i; i < rows; ++i)
						{
							cache_get_value_name(i, "Char_Name", fckname);
							cache_get_value_name_int(i, "Char_FactionRank", fckrank);
							cache_get_value_name(i, "Char_LastLogin", fcklastlogin);

							format(shstr, sizeof(shstr), "%s%s\t%s\t%s\n", shstr, fckname, TransRank[fckrank], fcklastlogin);
						}
						ShowPlayerDialog(playerid, DIALOG_TRANSKICKMEMBER, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Kick Anggota", shstr, "Kick", "Batal");
					}
					else 
					{
						PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
						return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota", "Tidak ada Anggota Trans!", "Tutup", "");
					}
                }
                case 3:
                {
                    new list[1218];
					format(list, sizeof(list), "Nama\tRank\tStatus\n");
					foreach(new i : Player) if(AccountData[i][pFaction] == FACTION_TRANS)
					{
						format(list, sizeof(list), "%s%s\t%s\t%s\n", list, AccountData[i][pName], GetFactionRank(i), AccountData[i][pDutyTrans] ? ""GREEN"On Duty" : ""DARKRED"Off Duty");
					}
					ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Anggota", list, "Tutup", "");
                }
                case 4:
                {
                    new frmxt[158];
					format(frmxt, sizeof(frmxt), "Perusahaan Transportasi District  saat ini memiliki saldo sebesar\
					\n"DARKGREEN"%s", FormatMoney(TransMoneyVault));
					ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Trans Money", frmxt, "Tutup", "");
                }
				case 5:
				{
					ShowPlayerDialog(playerid, DIALOG_DEPOSIT_TRANS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Trans Deposit",
					"Mohon masukkan nominal deposit untuk saldo perusahaan:", "Input", "Batal");
				}
				case 6:
				{
					ShowPlayerDialog(playerid, DIALOG_WITHDRAW_TRANS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Trans Withdraw",
					"Mohon masukkan nominal penarikan tunai dari saldo perusahaan:", "Input", "Batal");
				}
            }
        }
        case DIALOG_TRANS_LOCKER:
        {
            if(!response) return 0;
            if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Transportasi District !");

            switch(listitem)
            {
                case 0: SetPlayerSkin(playerid, AccountData[playerid][pSkin]), AccountData[playerid][pUsingUniform] = false;
                case 1: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (20) : (76), SetPlayerSkin(playerid, AccountData[playerid][pUniform]), AccountData[playerid][pUsingUniform] = true;
                case 2: AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (142) : (41), SetPlayerSkin(playerid, AccountData[playerid][pUniform]), AccountData[playerid][pUsingUniform ] = true;
            }
        }
        case DIALOG_TRANS_INVITECONF:
        {
            static icsr[855];
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Transportasi District !");
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Kepala Transport untuk akses desk!");

            new targetid = NearestPlayer[playerid][listitem];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            AccountData[targetid][pFaction] = FACTION_TRANS;
            AccountData[targetid][pFactionRank] = 1;
            RefreshFactionMap(targetid);
            mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`=4, `Char_FactionRank`=1 WHERE `pID`=%d", AccountData[targetid][pID]);
            mysql_tquery(g_SQL, icsr);
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil invite faction %s", AccountData[targetid][pName]));
        }
        case DIALOG_TRANSSETRANK:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Tansportasi District !");
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Kepala Transport untuk akses desk!");

            mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction`= 4 ORDER BY `Char_FactionRank` DESC");
            new rows = cache_num_rows();
            if(rows)
            {
                cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
                cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
                if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak dapat mengatur jabatan sendiri!");
                if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengatur jabatan rank diatasmu!");
                ShowPlayerDialog(playerid, DIALOG_RANK_SET_TRANS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan",
                "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\
                \n1. Magang\
                \n2. Junior\
                \n3. Senior\
                \n4. Kepala Transport\
                \n5. Trans CEO", "Set", "Batal");
            }
        }
        case DIALOG_TRANSKICKMEMBER:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Transportasi District !");
            if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Kepala Transport untuk mengakses Bos Desk!");

            mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 4 ORDER BY `Char_FactionRank` DESC");
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
                mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_OwnerID`=%d AND `PVeh_Faction` = 4", pidrow);
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
                                if(PlayerVehicle[pvid][pVehFaction] == FACTION_TRANS)
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
                        if(AccountData[i][pDutyTrans])
                            AccountData[i][pDutyTrans] = false;
                        if(AccountData[i][pUsingUniform])
                            AccountData[i][pUsingUniform] = false;
                        SetPlayerSkin(i, AccountData[i][pSkin]);
                        RefreshFactionMap(i);
                        ShowTDN(i, NOTIFICATION_WARNING, "Anda telah dikeluarkan dari faction Transportasi District !");
                    }
                }
                mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`=0, `Char_FactionRank`=0, `Char_UsingUniform`=0 WHERE `pID`=%d", pidrow);
                mysql_tquery(g_SQL, icsr);
                format(kckstr, sizeof(kckstr), "Anda telah berhasil menendang anggota:\
                \nNama: %s\
                \nRank: %s\
                \nLast Online: %s", fckname, TransRank[fckrank], fcklastlogin);
                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota",
                kckstr, "Tutup", "");

                AccountData[playerid][pTempSQLFactMemberID] = -1;
                AccountData[playerid][pTempSQLFactRank] = 0;
            }
        }
        case DIALOG_RANK_SET_TRANS:
		{
			if(!response) return 1;
			if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Transportasi District !");
			if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal Rank Kepala Transport untuk akses desk!");

			if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_TRANS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
			"Error: Tidak dapat diisi kosong!\n\
			Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\
			\n1. Magang\
			\n2. Junior\
			\n3. Senior\
			\n4. Kepala Transport\
			\n5. Trans CEO", "Set", "Batal");

			if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_TRANS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
			"Error: Hanya dapat diisi angka!\n\
			Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\
			\n1. Magang\
			\n2. Junior\
			\n3. Senior\
			\n4. Kepala Transport\
			\n5. Trans CEO", "Set", "Batal");

			if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pFactionRank]) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_TRANS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
			"Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
			Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\
			\n1. Magang\
			\n2. Junior\
			\n3. Senior\
			\n4. Kepala Transport\
			\n5. Trans CEO", "Set", "Batal");

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
        case DIALOG_DEPOSIT_TRANS:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
			if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Transportasi District !");
			if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal Rank Kepala Transport untuk akses desk!");
			new depocash = strval(inputtext), frmtmny[128];
			if(depocash > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak sebanyak itu!");
			if(depocash < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal kurang dari $1 untuk deposit!");
			TakeMoney(playerid, depocash);
			TransMoneyVault += depocash;
			mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `transmoneyvault` = %d WHERE `ID` = 0", TransMoneyVault);
			mysql_tquery(g_SQL, frmtmny);
			ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil deposit %s untuk Trans District ", FormatMoney(depocash)));
		}
		case DIALOG_WITHDRAW_TRANS:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
			if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Transportasi District !");
			if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal Rank Kepala Transport untuk akses desk!");
			new withdrawcash = strval(inputtext), frmtmny[128];
			if(withdrawcash > TransMoneyVault) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang perusahaan tidak sebanyak itu!");
			if(withdrawcash < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal kurang dari $1 untuk withdraw!");
			TransMoneyVault -= withdrawcash;
			GiveMoney(playerid, withdrawcash);

			mysql_format(g_SQL, frmtmny, sizeof(frmtmny), "UPDATE `stuffs` SET `transmoneyvault` = %d WHERE `ID` = 0", TransMoneyVault);
			mysql_tquery(g_SQL, frmtmny);

			AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], withdrawcash, "Trans");

			ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil withdraw %s dari Trans District ", FormatMoney(withdrawcash)));
		}
        case DIALOG_TRANS_GARAGE:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Transportasi District !");

            switch(listitem)
            {
                case 0: //takeout
                {
                    if(CountPlayerFactVehInGarage(playerid, FACTION_TRANS) < 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun di garasi ini!");

                    new id, count = CountPlayerFactVehInGarage(playerid, FACTION_TRANS), list[596];
                    format(list,sizeof(list),"No\tModel Kendaraan\tNomor Plat\n");
                    for(new x = 0; x < count; x ++)
                    {
                        id = GetVehicleIDStoredFactGarage(playerid, x, FACTION_TRANS);
                        if(x == count)
						{
							format(list,sizeof(list),"%s%d\t%s\t%s",list,x+1,GetVehicleModelName(PlayerVehicle[id][pVehModelID]),PlayerVehicle[id][pVehPlate]);
						} else format(list,sizeof(list),"%s%d\t%s\t%s\n",list,x+1,GetVehicleModelName(PlayerVehicle[id][pVehModelID]),PlayerVehicle[id][pVehPlate]);
                    }
                    ShowPlayerDialog(playerid, DIALOG_TRANS_GARAGE_TAKEOUT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Garasi Trans", list, "Pilih", "Batal");
                }
                case 1:// in
				{
					new carid = -1, bool: foundnearby = false;
					if((carid = Vehicle_Nearest(playerid, 10.0)) != -1)
					{
						if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
						if(PlayerVehicle[carid][pVehRental] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat disimpan digarasi Faction!");
						if(PlayerVehicle[carid][pVehFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan kendaraan Trans District !");
						
						Vehicle_GetStatus(carid);
						PlayerVehicle[carid][pVehFactStored] = FACTION_TRANS;

						foundnearby = true;

						if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]))
						{
							DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
							SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

							DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
							PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
						}
					}
					if(!foundnearby) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan dari Transportasi District  milik anda di sekitar!");
				}
                case 2: //buy
                {
                    ShowPlayerDialog(playerid, DIALOG_TRANS_GARAGE_BUY, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Beli Kendaraan",
                    "Model\tHarga\
                    \nTaxi\t$8500\
                    \n"GRAY"Cabbie\t"GRAY"$5000\
                    \nStratum\t$15000\
                    \n"GRAY"Sentinel Taxi\t"GRAY"$8000", "Pilih", "Batal");
                }
                case 3:// Hapus Kendaraan
				{
					new frmtdel[158];
					mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 4 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
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
						ShowPlayerDialog(playerid, DIALOG_TRANS_GARAGE_DELETE, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Hapus Kendaraan", list, "Hapus", "Batal");
					}
					else 
					{
						PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
						return Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Kendaraan", "Anda tidak memiliki kendaraan Trans", "Tutup", "");
					}
				}
            }
        }
        case DIALOG_TRANS_GARAGE_TAKEOUT:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Transportasi District !");
            if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            new id = GetVehicleIDStoredFactGarage(playerid, listitem, FACTION_TRANS);
            if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            if(!IsPlayerInRangeOfPoint(playerid, 2.0, Trans_Stuff[TransgaragePos][0], Trans_Stuff[TransgaragePos][1], Trans_Stuff[TransgaragePos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat Garasi Trans!");
            if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
            PlayerVehicle[id][pVehParked] = -1;
            PlayerVehicle[id][pVehHouseGarage] = -1;
            PlayerVehicle[id][pVehHelipadGarage] = -1;
            PlayerVehicle[id][pVehFamiliesGarage] = -1;
            PlayerVehicle[id][pVehFactStored] = -1;

            PlayerVehicle[id][pVehWorld] = GetPlayerVirtualWorld(playerid);
            PlayerVehicle[id][pVehInterior] = GetPlayerInterior(playerid);
            
			if(PlayerVehicle[id][pVehLocked])
				PlayerVehicle[id][pVehLocked] = false;

            PlayerVehicle[id][pVehPos][0] = Trans_Stuff[TransgaragespawnPos][0];
            PlayerVehicle[id][pVehPos][1] = Trans_Stuff[TransgaragespawnPos][1];
            PlayerVehicle[id][pVehPos][2] = Trans_Stuff[TransgaragespawnPos][2];
            PlayerVehicle[id][pVehPos][3] = Trans_Stuff[TransgaragespawnPos][3];

            OnPlayerVehicleRespawn(id);

            SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
        }
        case DIALOG_TRANS_GARAGE_BUY:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Transportasi District !");
            if(!IsPlayerInRangeOfPoint(playerid, 2.0, Trans_Stuff[TransgaragePos][0], Trans_Stuff[TransgaragePos][1], Trans_Stuff[TransgaragePos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat Garasi Trans!");

            // new count = 0;
            // foreach(new carid : PvtVehicles)
            // {
            //     if(PlayerVehicle[carid][pVehExists] && PlayerVehicle[carid][pVehOwnerID] == AccountData[playerid][pID])
            //         count ++;
            // }
            // if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda sudah penuh!");

            switch(listitem)
            {
                case 0:// Taxi
                {
                    if(AccountData[playerid][pMoney] < 8500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 8500);
                   // VehicleFaction_Create(playerid, 420, FACTION_TRANS, Trans_Stuff[TransgaragespawnPos][0], Trans_Stuff[TransgaragespawnPos][1], Trans_Stuff[TransgaragespawnPos][2], Trans_Stuff[TransgaragespawnPos][3], 6, 6, 8500);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
                }
                case 1:// Cabbie
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 5000);
                    //VehicleFaction_Create(playerid, 438, FACTION_TRANS, Trans_Stuff[TransgaragespawnPos][0], Trans_Stuff[TransgaragespawnPos][1], Trans_Stuff[TransgaragespawnPos][2], Trans_Stuff[TransgaragespawnPos][3], 6, 6, 5000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
                }
                case 2:// Stratum
                {
                    if(AccountData[playerid][pMoney] < 15000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 15000);
                   // VehicleFaction_Create(playerid, 561, FACTION_TRANS, Trans_Stuff[TransgaragespawnPos][0], Trans_Stuff[TransgaragespawnPos][1], Trans_Stuff[TransgaragespawnPos][2], Trans_Stuff[TransgaragespawnPos][3], 6, 6, 15000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
                }
                case 3:// Sentinel
                {
                    if(AccountData[playerid][pMoney] < 8000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 8000);
                   // VehicleFaction_Create(playerid, 405, FACTION_TRANS, Trans_Stuff[TransgaragespawnPos][0], Trans_Stuff[TransgaragespawnPos][1], Trans_Stuff[TransgaragespawnPos][2], Trans_Stuff[TransgaragespawnPos][3], 6, 6, 8000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan");
                }
            }
        }
        case DIALOG_TRANS_GARAGE_DELETE:
		{
			if(!response) return 1;
			if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda bukan anggota Transportasi District ");

			new frmtdel[158], Cache:execute;
			mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 4 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
			execute = mysql_query(g_SQL, frmtdel, true);

			new rows = cache_num_rows();
			if(rows)
			{
				new havpid, havmods, havprice, kckstr[255], strgbg[128];
				
                if(listitem >= 0 && listitem < rows)
                {
                    cache_get_value_name_int(listitem, "id", havpid);
                    cache_get_value_name_int(listitem, "PVeh_ModelID", havmods);
                    cache_get_value_name_int(listitem, "PVeh_Price", havprice);

                    format(kckstr, sizeof(kckstr), "Anda berhasil menghapus kendaraan:\
                    \nDatabase ID: %d\
                    \nModel: %s", havpid, GetVehicleModelName(havmods));
                    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Kendaraan", kckstr, "Tutup", "");

                    new pvid = GetFactionVehicleIDFromListitem(playerid, listitem, FACTION_TRANS);

                    PlayerVehicle[pvid][pVehExists] = false;
                    if(IsValidVehicle(PlayerVehicle[pvid][pVehPhysic]))
                    {
                        DisableVehicleSpeedCap(PlayerVehicle[pvid][pVehPhysic]);
                        SetVehicleNeonLights(PlayerVehicle[pvid][pVehPhysic], false, PlayerVehicle[pvid][pVehNeon], 0);

                        DestroyVehicle(PlayerVehicle[pvid][pVehPhysic]);
                        PlayerVehicle[pvid][pVehPhysic] = INVALID_VEHICLE_ID;
                    }
                    GiveMoney(playerid, havprice);
                    mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `id` = %d", havpid);
                    mysql_tquery(g_SQL, strgbg);

                    Iter_Remove(PvtVehicles, pvid);
                }
			}
            cache_delete(execute);
		}
        case DIALOG_TRANSVAULT:
		{
			if(!response) 
            {
                AccountData[playerid][menuShowed] = false;
                return 1;
            }
			if(AccountData[playerid][pFaction] != FACTION_TRANS) 
            {
                AccountData[playerid][menuShowed] = false;   
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Transportasi District !");
            }
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
                        ShowPlayerDialog(playerid, DIALOG_TRANSVAULT_DEPOSIT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas Trans", str, "Pilih", "Batal");
                    }
                    else 
                    {
                        AccountData[playerid][menuShowed] = false;
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas Trans",
                        "Anda tidak memiliki barang untuk disimpan!", "Tutup", "");
                    }
                }
                case 1: //withdraw
                {
                    new str[128], amounts, itemname[64];
                    format(str, sizeof(str), "Nama Item\tJumlah\tBerat (-/-)\n");
                    mysql_query(g_SQL, "SELECT * FROM `trans_brankas` WHERE `PID`=0");
                    if(cache_num_rows() > 0)
                    {
                        for(new x; x < cache_num_rows(); ++x)
                        {
                            cache_get_value_name(x, "Item", itemname);
                            cache_get_value_name_int(x, "Quantity", amounts);

                            format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                        }
                        ShowPlayerDialog(playerid, DIALOG_TRANSVAULT_WITHDRAW, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas Trans", str, "Pilih", "Batal");
                    }
                    else 
                    {
                        AccountData[playerid][menuShowed] = false;
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas Trans",
                        "Tidak ada barang di brankas saat ini!", "Tutup", "");
                    }
                }
			}
		}
        case DIALOG_TRANSVAULT_DEPOSIT:
		{
			if(!response)
            {
                AccountData[playerid][menuShowed] = false;
                return 1;
            }

            if(listitem == -1)
            {
                AccountData[playerid][menuShowed] = false;
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
                ShowPlayerDialog(playerid, DIALOG_TRANSVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Trans",
                shstr, "Input", "Batal");
            }
		}
		case DIALOG_TRANSVAULT_IN:
		{
			if(!response)
            {
                AccountData[playerid][menuShowed] = false;
                return 1;
            }

            new shstr[512];
            if(isnull(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nTidak dapat diisi kosong!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_TRANSVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Trans",
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_TRANSVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Trans",
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[playerid][factionBrankasQuant])
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_TRANSVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Trans",
                shstr, "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);
            Inventory_Remove(playerid, FactionBrankas[playerid][factionBrankasTemp], quantity);
            ShowItemBox(playerid, sprintf("Removed %dx", quantity), FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel]);

            new invstr[1028];
            mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `trans_brankas` WHERE `PID`=0 AND `Item` = '%s'", FactionBrankas[playerid][factionBrankasTemp]);
            mysql_query(g_SQL, shstr);
            new rows = cache_num_rows();
            if(rows > 0)
            {
                mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `trans_brankas` SET `Quantity` = `Quantity` + %d WHERE `PID` = 0 AND `Item`='%s'", quantity, FactionBrankas[playerid][factionBrankasTemp]);
                mysql_tquery(g_SQL, invstr, "OnTransDeposit", "i", playerid);
            }
            else 
            {
                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `trans_brankas` SET `PID`=0, `Item`='%s', `Model`=%d, `Quantity`=%d", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel], quantity);
                mysql_tquery(g_SQL, invstr, "OnTransDeposit", "i", playerid);
            }
            AccountData[playerid][menuShowed] = false;
		}
        case DIALOG_TRANSVAULT_WITHDRAW:
		{
			if(!response)
            {
                AccountData[playerid][menuShowed] = false;
                return 1;
            }

            if(listitem == -1)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item!");
            }

            new shstr[1218];
            mysql_query(g_SQL, "SELECT * FROM `trans_brankas` WHERE `PID`=0");
            if(cache_num_rows() > 0)
            {
                cache_get_value_name_int(listitem, "ID", FactionBrankas[playerid][factionBrankasID]);
                cache_get_value_name(listitem, "Item", FactionBrankas[playerid][factionBrankasTemp]);
                cache_get_value_name_int(listitem, "Model", FactionBrankas[playerid][factionBrankasModel]);
                cache_get_value_name_int(listitem, "Quantity", FactionBrankas[playerid][factionBrankasQuant]);

                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_TRANSVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Trans",
                shstr, "Input", "Batal");
            }
            else 
            {
                AccountData[playerid][menuShowed] = false;
                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas Trans",
                "Brankas ini isinya kosong!", "Tutup", "");
            }
		}
		case DIALOG_TRANSVAULT_OUT:
		{
			if(!response)
            {
                AccountData[playerid][menuShowed] = false;
                return 1;
            }

            new shstr[512];
            if(isnull(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nTidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_TRANSVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Trans",
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_TRANSVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Trans",
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[playerid][factionBrankasQuant])
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah tersimpan: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_TRANSVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Trans",
                shstr, "Input", "Batal");
                return 1;
            }
            new quantity = strval(inputtext), jts[150];

            if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!"), AccountData[playerid][menuShowed] = false;

            FactionBrankas[playerid][factionBrankasQuant] -= quantity;
            if(FactionBrankas[playerid][factionBrankasQuant] > 0)
            {
                mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `trans_brankas` SET `Quantity`=%d WHERE `ID`=%d", FactionBrankas[playerid][factionBrankasQuant], FactionBrankas[playerid][factionBrankasID]);
                mysql_tquery(g_SQL, jts);
            }
            else 
            {
                mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `trans_brankas` WHERE `ID`=%d", FactionBrankas[playerid][factionBrankasID]);
                mysql_tquery(g_SQL, jts);
            }
            Inventory_Add(playerid, FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel], quantity);
            ShowItemBox(playerid, sprintf("Received %dx", quantity), FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel]);
        
            FactionBrankas[playerid][factionBrankasID] = 0;
            FactionBrankas[playerid][factionBrankasTemp] = EOS;
            FactionBrankas[playerid][factionBrankasModel] = 0;
            FactionBrankas[playerid][factionBrankasQuant] = 0;
            AccountData[playerid][menuShowed] = false;
		}
    }
    return 1;
}

forward OnTransDeposit(playerid);
public OnTransDeposit(playerid)
{
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyimpan item");
    FactionBrankas[playerid][factionBrankasID] = 0;
    FactionBrankas[playerid][factionBrankasTemp] = EOS;
    FactionBrankas[playerid][factionBrankasModel] = 0;
    FactionBrankas[playerid][factionBrankasQuant] = 0;
    return 1;
}

/*DialogPages:TransSetRank(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Tansportasi District !");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Kepala Transport untuk akses desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction`= 4 ORDER BY `Char_FactionRank` DESC");
    new rows = cache_num_rows();
    if(rows)
    {
        cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
        cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak dapat mengatur jabatan sendiri!");
        if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengatur jabatan rank diatasmu!");
        ShowPlayerDialog(playerid, DIALOG_RANK_SET_TRANS, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan",
		"Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\
		\n1. Magang\
		\n2. Junior\
		\n3. Senior\
		\n4. Kepala Transport\
		\n5. Trans CEO", "Set", "Batal");
    }
    return 1;
}

DialogPages:TransKickMember(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Transportasi District !");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Kepala Transport untuk mengakses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 4 ORDER BY `Char_FactionRank` DESC");
    if(cache_num_rows())
    {
        new pidrow, fckname[64], fckrank, fcklastlogin[30], kckstr[225], icsr[128];

        cache_get_value_name_int(listitem, "pID", pidrow);
        cache_get_value_name(listitem, "Char_Name", fckname);
        cache_get_value_name_int(listitem, "Char_FactionRank", fckrank);
        cache_get_value_name(listitem, "Char_LastLogin", fcklastlogin);

        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat kick diri sendiri!");
        if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat kick pangkat diatasmu!");

        // kendaraan pribadi yg milik faction di cek
        new strgbg[158];
        mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_OwnerID`=%d AND `PVeh_Faction` = 4", pidrow);
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
                        if(PlayerVehicle[pvid][pVehFaction] == FACTION_TRANS)
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
                if(AccountData[i][pDutyTrans])
                    AccountData[i][pDutyTrans] = false;
				if(AccountData[i][pUsingUniform])
					AccountData[i][pUsingUniform] = false;
				SetPlayerSkin(i, AccountData[i][pSkin]);
				RefreshFactionMap(i);
                ShowTDN(i, NOTIFICATION_WARNING, "Anda telah dikeluarkan dari faction Transportasi District !");
            }
        }
        mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`=0, `Char_FactionRank`=0, `Char_UsingUniform`=0 WHERE `pID`=%d", pidrow);
        mysql_tquery(g_SQL, icsr);
        format(kckstr, sizeof(kckstr), "Anda telah berhasil menendang anggota:\
        \nNama: %s\
        \nRank: %s\
        \nLast Online: %s", fckname, TransRank[fckrank], fcklastlogin);
        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota",
        kckstr, "Tutup", "");

		AccountData[playerid][pTempSQLFactMemberID] = -1;
        AccountData[playerid][pTempSQLFactRank] = 0;
    }
    return 1;
}*/
