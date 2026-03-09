#include <YSI\y_hooks>

new pMasakTimer[MAX_PLAYERS] = {-1, ...};

new const PedagangRank[7][] = {
    "N/A",
    "Magang",
    "Junior",
    "Senior",
    "Manager",
    "Wakil CEO",
    "CEO"
};

enum e_pedagangstuff
{
    STREAMER_TAG_AREA:PdgDuty,
    STREAMER_TAG_AREA:PdgLocker,
    STREAMER_TAG_AREA:PdgGarasi,
    STREAMER_TAG_AREA:PdgCooking,
    STREAMER_TAG_AREA:PdgDesk,
    STREAMER_TAG_AREA:PdgKulkas,
    STREAMER_TAG_AREA:PdgKulkasEms,
    STREAMER_TAG_AREA:PdgCookingEms,

    Float:PdggaragePos[3],
    Float:pdggarageSpawnPos[4],
}
new Pedagang_Stuff[e_pedagangstuff];
new Pedagang_Objects[MAX_PLAYERS][8];

hook OnGameModeInit()
{
    Pedagang_Stuff[PdgDuty] = CreateDynamicSphere(350.9044,-1848.0898,5.3773, 1.5, 0, 0, -1);
    Pedagang_Stuff[PdgLocker] = CreateDynamicSphere(346.7945,-1847.1002,5.3773, 1.5, 0, 0, -1);
    Pedagang_Stuff[PdgGarasi] = CreateDynamicSphere(316.1964,-1801.1807,4.5922, 1.5, 0, 0, -1);
    Pedagang_Stuff[PdgCooking] = CreateDynamicSphere(321.8679,-1851.1921,5.0982, 1.5, 0, 0, -1);
    Pedagang_Stuff[PdgDesk] = CreateDynamicSphere(354.7868,-1846.7720,5.3873, 1.5, 0, 0, -1);
    Pedagang_Stuff[PdgKulkas] = CreateDynamicSphere(327.2828,-1851.7909,5.0982, 1.5, 0, 0, -1);

    Pedagang_Stuff[PdgKulkasEms] = CreateDynamicSphere(856.4885,712.6636,5005.0396, 1.5, 5, 5, -1);
    Pedagang_Stuff[PdgCookingEms] = CreateDynamicSphere(856.7956,717.3268,5005.0396, 1.5, 5, 5, -1);
    
}

hook OnPlayerConnect(playerid)
{
    pMasakTimer[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pMasakTimer[playerid]);
    pMasakTimer[playerid] = -1;
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(AccountData[playerid][pFaction] == FACTION_PEDAGANG)
    {
        if(areaid == Pedagang_Stuff[PdgDuty])
        {
            if(!AccountData[playerid][pDutyPedagang])
            {
                ShowKey(playerid, "[Y] ~g~On Duty");
            }
            else
            {
                ShowKey(playerid, "[Y] ~r~Off Duty");
            }
        }

        if(areaid == Pedagang_Stuff[PdgLocker] && AccountData[playerid][pDutyPedagang])
        {
            ShowKey(playerid, "[Y] Locker Pedagang");
        }

        if((areaid == Pedagang_Stuff[PdgCooking] || areaid == Pedagang_Stuff[PdgCookingEms]) && AccountData[playerid][pDutyPedagang])
        {
            ShowKey(playerid, "[Y] Masak");
        }

        if(areaid == Pedagang_Stuff[PdgDesk])
        {
            ShowKey(playerid, "[Y] Pedagang Desk");
        }

        if((areaid == Pedagang_Stuff[PdgKulkas] || areaid == Pedagang_Stuff[PdgKulkasEms])&& AccountData[playerid][pDutyPedagang])
        {
            ShowKey(playerid, "[Y] Kulkas Pedagang");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == Pedagang_Stuff[PdgDuty])
    {
        HideShortKey(playerid);
    }

    if(areaid == Pedagang_Stuff[PdgLocker])
    {
        HideShortKey(playerid);
    }

    if(areaid == Pedagang_Stuff[PdgGarasi])
    {
        HideShortKey(playerid);
    }

    if((areaid == Pedagang_Stuff[PdgCooking] || areaid == Pedagang_Stuff[PdgCookingEms]))
    {
        HideShortKey(playerid);
    }

    if(areaid == Pedagang_Stuff[PdgDesk])
    {
        HideShortKey(playerid);
    }

    if((areaid == Pedagang_Stuff[PdgKulkas] || areaid == Pedagang_Stuff[PdgKulkasEms]))
    {
        HideShortKey(playerid);
    }
    return 1;
}

Dialog:DIALOG_PEDAGANG_PANEL(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        for (new i = 0; i < MAX_PLAYERS; i ++) NearestPlayer[playerid][i] = INVALID_PLAYER_ID;
        AccountData[playerid][pTarget] = INVALID_PLAYER_ID;
        return 1;
    }

    if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pedagang District !");
    new targetid = AccountData[playerid][pTarget];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi kedalam server!");
    if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan player tersebut!");
    if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan, tidak dapat menggunakan Panel!");
    switch(listitem)
    {
        case 0:// invoice belum terbayar
        {
            PeriksaInvoice(playerid, targetid);
        }
        case 1://Cek Identitas
        {
            CekIdentitas(playerid, targetid);
        }
        case 2:// Invoice
        {
            GivePlayerInvoice(playerid, targetid);
        }
        case 3:// Cek Blacklist
        {
            ShowDurringBlacklist(playerid, targetid);
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pFaction] == FACTION_PEDAGANG)
        {
            if(IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgDuty]))
            {
                if(!AccountData[playerid][pDutyPedagang])
                {
                    AccountData[playerid][pDutyPedagang] = true;
                    SetFactionColor(playerid);
                    AccountData[playerid][pDutyTimer] = SetTimerEx("FactDutyHour", 1000, true, "i", playerid);
                    Info(playerid, "Anda sekarang "GREEN"On Duty"WHITE" Pedagang");
                }
                else
                {
                    if(AccountData[playerid][pUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih menggunakan pakaian pedagang!");

                    AccountData[playerid][pDutyPedagang] = false;
                    SetPlayerColor(playerid, COLOR_WHITE);
                    Info(playerid, "Anda sekarang "RED"Off Duty"WHITE" Pedagang");
                }
                RefreshFactionMap(playerid);
                HideShortKey(playerid);
            }

            if(IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgLocker]) && AccountData[playerid][pDutyPedagang])
            {
                ShowPlayerDialog(playerid, DIALOG_LOCKERPEDAGANG, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Locker Pedagang",
                "Baju Biasa\
                \n"GRAY"Pedagang 1\
                \nPedagang 2\
                \n"GRAY"Pedagang 3", "Pilih", "Batal");
                HideShortKey(playerid);
            }

            if((IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCooking]) || IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgCookingEms])) && AccountData[playerid][pDutyPedagang])
            {
                if(!AccountData[playerid][pUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Silahkan ganti pakaian anda terlebih dahulu!");
                ShowPlayerDialog(playerid, DIALOG_LOUNGES_MASAK, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Dapur Pedagang",
                "Nama\tBahan #1\tBahan #2\tBahan #3\
                \nNasi\tBeras\tGaram\tSambal\
                \n"GRAY"Bakso\tIkan\tSambal\tGaram\
                \nNasi Pecel\tBeras\tIkan\tSambal\
                \n"GRAY"Bubur Pedas\tBeras\tSambal\tAyam Kemas\
                \nSusu\tGula\tSusu Olahan\tGula\
                \n"GRAY"Kopi Kenangan\tGula\tAir Mineral\tAir Mineral\
                \nCocho Matcha\tGula\tAir Mineral\t-\
                \n"GRAY"Es Teh\tGula\tGula\tAir Mineral", "Masak", "Batal");
                HideShortKey(playerid);
            }

            if((IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgKulkas]) || IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgKulkasEms])) && AccountData[playerid][pDutyPedagang])
            {
                if(!AccountData[playerid][pUsingUniform]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Silahkan ganti pakaian anda terlebih dahulu!");

                new shstr[1218];
                format(shstr, sizeof(shstr), "Nama Item\tStok\n");
                format(shstr, sizeof(shstr), "%sSambal\t%d\n", shstr, Sambal);
                format(shstr, sizeof(shstr), "%s"GRAY"Beras\t%d\n", shstr, Beras);
                format(shstr, sizeof(shstr), "%sGula\t%d\n", shstr, Gula);
                format(shstr, sizeof(shstr), "%s"GRAY"Garam\t%d\n", shstr, Garam);
                format(shstr, sizeof(shstr), "%sIkan\t%d\n", shstr, Ikan);
                format(shstr, sizeof(shstr), "%s"GRAY"Ayam Kemas\t%d\n", shstr, AyamFillet);
                format(shstr, sizeof(shstr), "%sSusu Olahan\t%d\n", shstr, SusuOlahan);
                format(shstr, sizeof(shstr), "%s"GRAY"Air Mineral\t%d\n", shstr, AirMineral);
                format(shstr, sizeof(shstr), "%sNasi Goreng\t%d\n", shstr, NasiGoreng);
                format(shstr, sizeof(shstr), "%s"GRAY"Bakso\t%d\n", shstr, Bakso);
                format(shstr, sizeof(shstr), "%sNasi Pecel\t%d\n", shstr, NasiPecel);
                format(shstr, sizeof(shstr), "%s"GRAY"Bubur Pedas\t%d\n", shstr, BuburPedas);
                format(shstr, sizeof(shstr), "%sSusu Fresh\t%d\n", shstr, SusuFresh);
                format(shstr, sizeof(shstr), "%s"GRAY"Es Teh\t%d\n", shstr, EsTeh);
                format(shstr, sizeof(shstr), "%sKopi Kenangan\t%d\n", shstr, KopiKenangan);
                format(shstr, sizeof(shstr), "%s"GRAY"Cocho Matcha\t%d\n", shstr, CochoMatcha);
                Dialog_Show(playerid, BrankasLounge, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas Pedagang", shstr, "Pilih", "Batal");
                HideShortKey(playerid);
            }

            /*if(IsPlayerInRangeOfPoint(playerid, 1.5, Pedagang_Stuff[PdggaragePos][0], Pedagang_Stuff[PdggaragePos][1], Pedagang_Stuff[PdggaragePos][2]) && AccountData[playerid][pDutyPedagang])
            {
                ShowPlayerDialog(playerid, DIALOG_PEDAGANG_GARAGE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Garasi Pedagang",
                "Keluarkan Kendaraan\
                \n"GRAY"Simpan Kendaraan\
                \nBeli Kendaraan\
                \n"GRAY"Hapus Kendaraan", "Pilih", "Batal");
                HideShortKey(playerid);
            }*/

            if(IsPlayerInDynamicArea(playerid, Pedagang_Stuff[PdgDesk]))
            {
                if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil CEO untuk akses Desk!");
                Dialog_Show(playerid, BosDesk_Pedagang, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Bos Desk",
                "Invite\
                \n"GRAY"Kelola Jabatan\
                \nKick\
                \n"GRAY"Lihat Anggota\
                \nSaldo Finansial\
                \n"GRAY"Deposit Saldo\
                \nWithdraw Saldo", "Pilih", "Batal");
                HideShortKey(playerid);
            }
        }
    }
    return 1;
}

Dialog:BosDesk_Pedagang(playerid, response, listitem, inputtext[])
{
    if(response)
    {
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

                Dialog_Show(playerid, Pedagang_Invite, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Bos Desk", frmxt, "Pilih", "Batal");
            }
            case 1: // Kelola Jabatan offline / online
			{
                mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 6 ORDER BY Char_FactionRank DESC");

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

                        format(shstr, sizeof(shstr), "%s%s\t%s\t%s\n", shstr, fckname, PedagangRank[fckrank], fcklastlogin);
                    }
                    ShowPlayerDialog(playerid, DIALOG_PEDSETRANK, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Set Jabatan", shstr, "Pilih", "Batal");
                }
                else 
                {
                    PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Set Jabatan", "Tidak ada Anggota Pedagang!", "Tutup", "");
                }
			}
			case 2:
			{
                mysql_query(g_SQL, "SELECT * FROM player_characters WHERE Char_Faction = 6 ORDER BY Char_FactionRank DESC");

                new rows = cache_num_rows();
                if(rows)
                {
                    new shstr[2048], fckname[64], fckrank, fcklastlogin[30];

                    format(shstr, sizeof(shstr), "Nama\tRank\tLast Online\n");
                    for(new i; i < rows; ++i)
                    {
                        cache_get_value_name(i, "Char_Name", fckname);
                        cache_get_value_name_int(i, "Char_FactionRank", fckrank);
                        cache_get_value_name(i, "Char_LastLogin", fcklastlogin);

                        format(shstr, sizeof(shstr), "%s%s\t%s\t%s\n", shstr, fckname, PedagangRank[fckrank], fcklastlogin);
                    }
                    ShowPlayerDialog(playerid, DIALOG_PEDKICKMEMBER, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Kick Anggota", shstr, "Kick", "Batal");
                }
                else 
                {
                    PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota", "Tidak ada Anggota Bengkel!", "Tutup", "");
                }
			}
			case 3:
			{
				new duty[128], lstr[1024];
				format(lstr, sizeof lstr, "Nama\tRank\tStatus Duty\n");
				foreach(new i : Player) {
					if(AccountData[i][pFaction] == 6) {
						switch(AccountData[i][pDutyPedagang])
						{
							case 0:
							{
								duty = ""RED_E"Off Duty";
							}
							case 1:
							{
								duty = ""GREEN"On Duty";
							}
						}
						format(lstr, sizeof lstr, "%s%s(%d)\t%s\t%s", lstr, GetRPName(i), i, GetFactionRank(i), duty);
						format(lstr, sizeof lstr, "%s\n", lstr);
					}
				}
				format(lstr, sizeof lstr, "%s\n", lstr);
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Anggota", lstr, "Close", "");
			}
			case 4:
			{
				new sstr[512];
				format(sstr, sizeof sstr, "Saldo Finansial Pedagang saat ini memiliki saldo sebesar %s\nSiapapun yang melakukan korupsi pada uang PT akan dikenakan sanksi bahkan\ndapat dikeluarkan!", FormatMoney(RestoMoneyVault));
				Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Saldo Finansial", sstr, "Close", "");
			}
			case 5:
			{
				new sstr[512];
				format(sstr, sizeof sstr, "Mohon ikuti format berikut:\nGunakanlah format depo [jumlah] untuk deposit ke Brankas\nGunakan tanpa tanda ][ pada kolom dibawah ini:");
				Dialog_Show(playerid, SaldoPedagangDeposit, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", sstr, "Input", "Batal");
			}
			case 6:
			{
				new sstr[512];
				format(sstr, sizeof sstr, "Mohon ikuti format berikut:\nGunakanlah format ambil [jumlah] untuk menarik saldo dari Brankas\nGunakan tanpa tanda ][ pada kolom dibawah ini:");
				Dialog_Show(playerid, SaldoPedagangWithdraw, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", sstr, "Input", "Batal");
			}
        }
    }
    else InfoBatal(playerid);
    return 1;
}
Dialog:SaldoPedagangDeposit(playerid, response, listitem, inputtext[])
{
    if(!response) return false;
    if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari pedagang kota verona!");
    if(response)
    {
        new string[128], amount;
        if(sscanf(inputtext, "s[128]d", string, amount))
        {
            new sstr[512];
            format(sstr, sizeof sstr, "Mohon ikuti format berikut:\nGunakanlah format depo [jumlah] untuk deposit ke Brankas\nGunakan tanpa tanda ][ pada kolom dibawah ini:");
            Dialog_Show(playerid, SaldoPedagangDeposit, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", sstr, "Input", "Batal");
            return 1;
        }
        if(!strcmp(string, "depo", true))
        {
            if(amount > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

            RestoMoneyVault += amount;
            TakeMoney(playerid, amount);
            ShowItemBox(playerid, sprintf("Removed %s", FormatMoney(amount)), "UANG", 1212);
            
            new query[255];
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `stuffs` SET `restomoneyvault` = %d WHERE `ID` = 0", RestoMoneyVault);
            mysql_tquery(g_SQL, query);
            // BrankasFaction_Save();
        }
    }
    return 1;
}

Dialog:SaldoPedagangWithdraw(playerid, response, listitem, inputtext[])
{
    if(!response) return false;
    if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari pedagang kota verona!");
    if(response)
    {
        new string[128], amount;
        if(sscanf(inputtext, "s[128]d", string, amount))
        {
            new sstr[512];
            format(sstr, sizeof sstr, "Mohon ikuti format berikut:\nGunakanlah format ambil [jumlah] untuk menarik saldo dari Brankas\nGunakan tanpa tanda ][ pada kolom dibawah ini:");
            Dialog_Show(playerid, SaldoPedagangWithdraw, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", sstr, "Input", "Batal");
            return 1;
        }
        if(!strcmp(string, "ambil", true))
        {
            if(amount > RestoMoneyVault) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo brankas tidak sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

            RestoMoneyVault -= amount;
            GiveMoney(playerid, amount);
            ShowItemBox(playerid, sprintf("Received %s", FormatMoney(amount)), "UANG", 1212);
            
            // BrankasFaction_Save();
            new query[255];
            mysql_format(g_SQL, query, sizeof(query), "UPDATE `stuffs` SET `restomoneyvault` = %d WHERE `ID` = 0", RestoMoneyVault);
            mysql_tquery(g_SQL, query);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, "Pedagang");
        }
    }
    return 1;
}

Dialog:Pedagang_Invite(playerid, response, listitem, inputtext[])
{
    static icsr[855];
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pedagang!");
    if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil CEO untuk akses bos desk!");

    new targetid = NearestPlayer[playerid][listitem];
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    AccountData[targetid][pFaction] = FACTION_PEDAGANG;
    AccountData[targetid][pFactionRank] = 1;
    RefreshFactionMap(targetid);
    mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`= 6, `Char_FactionRank` = 1 WHERE `pID`=%d", AccountData[targetid][pID]);
    mysql_tquery(g_SQL, icsr);
    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil invite faction %s", AccountData[targetid][pName]));
    return 1;
}

Dialog:BrankasLounge(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                Dialog_Show(playerid, BrankasSambal, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 1:
            {
                Dialog_Show(playerid, BrankasBeras, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 2:
            {
                Dialog_Show(playerid, BrankasGula, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 3:
            {
                Dialog_Show(playerid, BrankasGaram, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 4:
            {
                Dialog_Show(playerid, BrankasIkan, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 5:
            {
                Dialog_Show(playerid, BrankasAyamFillet, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 6:
            {
                Dialog_Show(playerid, BrankasSusuOlahan, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 7:
            {
                Dialog_Show(playerid, BrankasAirMineral, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 8:
            {
                Dialog_Show(playerid, BrankasNasgor, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 9:
            {
                Dialog_Show(playerid, BrankasBakso, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 10:
            {
                Dialog_Show(playerid, BrankasNasiPecel, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 11:
            {
                Dialog_Show(playerid, BrankasBuburPedas, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 12:
            {
                Dialog_Show(playerid, BrankasSusuFresh, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 13:
            {
                Dialog_Show(playerid, BrankasEsTeh, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 14:
            {
                Dialog_Show(playerid, BrankasKopiKenangan, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
            case 15:
            {
                Dialog_Show(playerid, BrankasCochoMatcha, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            }
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
}

Dialog:BrankasSambal(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasSambal, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > Sambal) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada sambal sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            Sambal -= amount;
            Inventory_Add(playerid, "Sambal", 11722, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Sambal!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Sambal sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Sambal")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki sambal sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            Sambal += amount;
            Inventory_Remove(playerid, "Sambal", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Sambal!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Sambal sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BrankasBeras(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasBeras, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > Beras) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Beras sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            Beras -= amount;
            Inventory_Add(playerid, "Beras", 2060, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Beras!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Beras sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Beras")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Beras sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            Beras += amount;
            Inventory_Remove(playerid, "Beras", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Beras!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Beras sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BrankasGula(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasGula, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > Gula) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Gula sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            Gula -= amount;
            Inventory_Add(playerid, "Gula", 1575, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Gula!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Gula sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Gula")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Gula sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            Gula += amount;
            Inventory_Remove(playerid, "Gula", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Gula!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Gula sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BrankasGaram(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasGaram, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > Garam) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Garam sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            Garam -= amount;
            Inventory_Add(playerid, "Garam", 1279, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Garam!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Garam sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Garam")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Gula sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            Garam += amount;
            Inventory_Remove(playerid, "Garam", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Garam!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Garam sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BrankasIkan(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasIkan, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > Ikan) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Ikan sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            Ikan -= amount;
            Inventory_Add(playerid, "Ikan", 19630, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Ikan!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Ikan sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Ikan")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Gula sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            Ikan += amount;
            Inventory_Remove(playerid, "Ikan", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Ikan!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Ikan sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BrankasAyamFillet(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasAyamFillet, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > AyamFillet) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Ayam Kemas sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            AyamFillet -= amount;
            Inventory_Add(playerid, "Ayam Kemas", 2768, amount);
            ShowItemBox(playerid, sprintf("Received %dx", amount), "Ayam Kemas", 2768);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Ayam Kemas!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Ayam Kemas sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Ayam Kemas")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Ayam Kemas sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            AyamFillet += amount;
            Inventory_Remove(playerid, "Ayam Kemas", amount);
            ShowItemBox(playerid, sprintf("Removed %dx", amount), "Ayam Kemas", 2768);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Ayam Kemas!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Ayam Kemas sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BrankasSusuOlahan(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasSusuOlahan, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > SusuOlahan) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Susu Olahan sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            SusuOlahan -= amount;
            Inventory_Add(playerid, "Susu Olahan", 19570, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Susu Olahan!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Susu Olahan sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Susu Olahan")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Susu Olahan sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            SusuOlahan += amount;
            Inventory_Remove(playerid, "Susu Olahan", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Susu Olahan!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Susu Olahan sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BrankasAirMineral(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasAirMineral, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > AirMineral) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Air Mineral sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            AirMineral -= amount;
            Inventory_Add(playerid, "Air Mineral", 19570, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Air Mineral!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Air Mineral sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Air Mineral")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Air Mineral sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            AirMineral += amount;
            Inventory_Remove(playerid, "Air Mineral", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Air Mineral!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Air Mineral sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BrankasNasgor(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasNasgor, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > NasiGoreng) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Nasi Goreng sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            NasiGoreng -= amount;
            Inventory_Add(playerid, "Nasi Goreng", 2355, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Nasi Goreng!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Nasi Goreng sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Nasi Goreng")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Nasi Goreng sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            NasiGoreng += amount;
            Inventory_Remove(playerid, "Nasi Goreng", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Nasi Goreng!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Nasi Goreng sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BrankasBakso(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasBakso, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > Bakso) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Bakso sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            Bakso -= amount;
            Inventory_Add(playerid, "Bakso", 19567, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Bakso!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Bakso sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Bakso")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Bakso sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            Bakso += amount;
            Inventory_Remove(playerid, "Bakso", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Bakso!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Bakso sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BrankasNasiPecel(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasNasiPecel, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > NasiPecel) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Nasi Pecel sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            NasiPecel -= amount;
            Inventory_Add(playerid, "Nasi Pecel", 2218, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Nasi Pecel!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Nasi Pecel sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Nasi Pecel")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Nasi Pecel sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            NasiPecel += amount;
            Inventory_Remove(playerid, "Nasi Pecel", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Nasi Pecel!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Nasi Pecel sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BrankasBuburPedas(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasBuburPedas, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > BuburPedas) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Bubur Pedas sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            BuburPedas -= amount;
            Inventory_Add(playerid, "Bubur Pedas", 19568, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Bubur Pedas!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Bubur Pedas sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Bubur Pedas")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Bubur Pedas sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            BuburPedas += amount;
            Inventory_Remove(playerid, "Bubur Pedas", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Bubur Pedas!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Bubur Pedas sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BrankasSusuFresh(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasSusuFresh, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > SusuFresh) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Susu Fresh sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            SusuFresh -= amount;
            Inventory_Add(playerid, "Susu Fresh", 19569, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Susu Fresh!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Susu Fresh sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Susu Fresh")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Susu Fresh sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            SusuFresh += amount;
            Inventory_Remove(playerid, "Susu Fresh", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Susu Fresh!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Susu Fresh sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BrankasEsTeh(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasEsTeh, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > EsTeh) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Es Teh sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            EsTeh -= amount;
            Inventory_Add(playerid, "Es Teh", 1546, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Es Teh!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Es Teh sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Es Teh")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Es Teh sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            EsTeh += amount;
            Inventory_Remove(playerid, "Es Teh", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Es Teh!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Es Teh sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BrankasKopiKenangan(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasKopiKenangan, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > KopiKenangan) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Kopi Kenangan sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            KopiKenangan -= amount;
            Inventory_Add(playerid, "Kopi Kenangan", 19835, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Kopi Kenangan!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Kopi Kenangan sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Kopi Kenangan")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Kopi Kenangan sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            KopiKenangan += amount;
            Inventory_Remove(playerid, "Kopi Kenangan", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Kopi Kenangan!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Kopi Kenangan sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

Dialog:BrankasCochoMatcha(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext,"s[128]d", option, amount))
        {
            Dialog_Show(playerid, BrankasCochoMatcha, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pedagang", "Mohon ikuti format berikut\n[ambil] [jumlah] atau [depo] [jumlah]\nMasukkan tanpa tanda ][ pada kolom dibawah ini:", "Input", "Batal");
            return 1;
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > CochoMatcha) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Choco Matcha sebanyak itu dibrankas!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            CochoMatcha -= amount;
            Inventory_Add(playerid, "Choco Matcha", 1667, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil Choco Matcha!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Mengambil Choco Matcha sebanyak %d dari Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > Inventory_Count(playerid, "Choco Matcha")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Choco Matcha sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            CochoMatcha += amount;
            Inventory_Remove(playerid, "Choco Matcha", amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan Choco Matcha!");
            BrankasLounge_Save();

            static frmtx[255];
            format(frmtx, sizeof(frmtx), "PEDAGANG - Memasukkan Choco Matcha sebanyak %d ke Kulkas", amount);
            AddFMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], amount, frmtx);
        }
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_LOCKERPEDAGANG:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Resto District !");

            switch(listitem)
            {
                case 0: // Biasa
                {
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengganti pakaian biasa.");
                    SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
                    AccountData[playerid][pUsingUniform] = false;
                }
                case 1:
                {
                    AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (167) : (205);
                    SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
                    AccountData[playerid][pUsingUniform] = true;
                }
                case 2: 
                {
                    AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (155) : (172);
                    SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
                    AccountData[playerid][pUsingUniform] = true;
                }
                case 3: 
                {
                    AccountData[playerid][pUniform] = (AccountData[playerid][pGender] == 1) ? (189) : (263);
                    SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
                    AccountData[playerid][pUsingUniform] = true;
                }
            }
        }
        case DIALOG_PEDAGANG_GARAGE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Pedagang District !");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");

            switch(listitem)
            {
                case 0:// Keluarkan Kendaraan
                {   
                    if(!CountPlayerFactVehInGarage(playerid, FACTION_PEDAGANG)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun di garasi ini!");

                    new id, count = CountPlayerFactVehInGarage(playerid, FACTION_PEDAGANG), lstr[596];
                    format(lstr, sizeof(lstr), "No\tModel Kendaraan\tNomor Plat\n");
                    for(new itt = 0; itt < count; itt++)
                    {
                        id = GetVehicleIDStoredFactGarage(playerid, itt, FACTION_PEDAGANG);
                        if(itt == count)
                        {
                            format(lstr, sizeof(lstr), "%s%d\t%s\t%s", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                        } else format(lstr, sizeof(lstr), "%s%d\t%s\t%s\n", lstr, itt+1, GetVehicleModelName(PlayerVehicle[id][pVehModelID]), PlayerVehicle[id][pVehPlate]);
                    }
                    ShowPlayerDialog(playerid, DIALOG_PEDAGANG_GARAGE_TAKEOUT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Garasi Pedagang", lstr, "Pilih", "Batal");
                }
                case 1:// Simpan Kendaraan
                {
                    new carid = -1, bool: foundnearby = false;
                    if((carid = Vehicle_Nearest(playerid, 15.0)) != -1)
                    {
                        if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
                        if(PlayerVehicle[carid][pVehRental] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan rental tidak dapat disimpan digarasi Faction!");
                        if(PlayerVehicle[carid][pVehFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan kendaraan Pedagang!");
                        Vehicle_GetStatus(carid);
                        PlayerVehicle[carid][pVehFactStored] = FACTION_PEDAGANG;

                        foundnearby = true;

                        if(IsValidVehicle(PlayerVehicle[carid][pVehPhysic]))
                        {
                            DisableVehicleSpeedCap(PlayerVehicle[carid][pVehPhysic]);
                            SetVehicleNeonLights(PlayerVehicle[carid][pVehPhysic], false, PlayerVehicle[carid][pVehNeon], 0);

                            DestroyVehicle(PlayerVehicle[carid][pVehPhysic]);
                            PlayerVehicle[carid][pVehPhysic] = INVALID_VEHICLE_ID;
                        }
                    }
                    if(!foundnearby) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan dari Pedagang District  milik anda di sekitar!");
                }
                case 2:// Buy Kendaraan
                {
                    ShowPlayerDialog(playerid, DIALOG_PEDAGANG_GARAGE_BUY, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Beli Kendaraan",
                    "Model\tHarga\
                    \nRancher Resto\t$6000\
                    \n"GRAY"Sanchez\t"GRAY"$4000\
                    \nVans Hotdogs\t$8000\
                    \nCamper Delivery\t$10000", "Pilih", "Batal");
                }
                case 3:// Hapus Kendaraan
                {
                    new frmtdel[158];
                    mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 6 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
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
                        ShowPlayerDialog(playerid, DIALOG_PEDAGANG_GARAGE_DELETE, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Hapus Kendaraan", list, "Hapus", "Batal");
                    }
                    else 
                    {
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Kendaraan", "Anda tidak memiliki kendaraan Pedagang", "Tutup", "");
                    }
                }
            }
        }
        case DIALOG_PEDAGANG_GARAGE_BUY:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pedagang!");
            
            // new count = 0;
            // foreach(new i : PvtVehicles)
            // {
            //     if(PlayerVehicle[i][pVehExists] && PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
            //         count ++;
            // }

            // if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot kendaraan anda telah penuh!");

            switch(listitem)
            {
                case 0:// Rancher
                {
                    if(AccountData[playerid][pMoney] < 6000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 6000);
                    
                   // VehicleFaction_Create(playerid, 489, FACTION_PEDAGANG, Pedagang_Stuff[pdggarageSpawnPos][0], Pedagang_Stuff[pdggarageSpawnPos][1], Pedagang_Stuff[pdggarageSpawnPos][2], Pedagang_Stuff[pdggarageSpawnPos][3], 82, 82, 6000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan!");
                }
                case 1:// sanchez
                {
                    if(AccountData[playerid][pMoney] < 4000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 4000);
                    
                   // VehicleFaction_Create(playerid, 468, FACTION_PEDAGANG, Pedagang_Stuff[pdggarageSpawnPos][0], Pedagang_Stuff[pdggarageSpawnPos][1], Pedagang_Stuff[pdggarageSpawnPos][2], Pedagang_Stuff[pdggarageSpawnPos][3], 82, 82, 4000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan!");
                }
                case 2:// sanchez
                {
                    if(AccountData[playerid][pMoney] < 8000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 8000);
                    
                   // VehicleFaction_Create(playerid, 588, FACTION_PEDAGANG, Pedagang_Stuff[pdggarageSpawnPos][0], Pedagang_Stuff[pdggarageSpawnPos][1], Pedagang_Stuff[pdggarageSpawnPos][2], Pedagang_Stuff[pdggarageSpawnPos][3], 82, 82, 8000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan!");
                }
                case 3:// Camper Delivery
                {
                    if(AccountData[playerid][pMoney] < 10000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    TakeMoney(playerid, 10000);
                    
                   // VehicleFaction_Create(playerid, 483, FACTION_PEDAGANG, Pedagang_Stuff[pdggarageSpawnPos][0], Pedagang_Stuff[pdggarageSpawnPos][1], Pedagang_Stuff[pdggarageSpawnPos][2], Pedagang_Stuff[pdggarageSpawnPos][3], 6, 3, 10000);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan!");
                }
            }
        }
        case DIALOG_PEDAGANG_GARAGE_TAKEOUT:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Resto District !");
            if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            new id = GetVehicleIDStoredFactGarage(playerid, listitem, FACTION_PEDAGANG);
            if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            if(!IsPlayerInRangeOfPoint(playerid, 2.0, Pedagang_Stuff[PdggaragePos][0], Pedagang_Stuff[PdggaragePos][1], Pedagang_Stuff[PdggaragePos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di garasi pedagang!");
            if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
            PlayerVehicle[id][pVehParked] = -1;
            PlayerVehicle[id][pVehHouseGarage] = -1;
            PlayerVehicle[id][pVehHelipadGarage] = -1;
            PlayerVehicle[id][pVehFamiliesGarage] = -1;
            PlayerVehicle[id][pVehFactStored] = -1;

            PlayerVehicle[id][pVehWorld] = GetPlayerVirtualWorld(playerid);
            PlayerVehicle[id][pVehInterior] = GetPlayerInterior(playerid);

            if(PlayerVehicle[id][pVehLocked]) {
                PlayerVehicle[id][pVehLocked] = false;
            }

            PlayerVehicle[id][pVehPos][0] = Pedagang_Stuff[pdggarageSpawnPos][0];
            PlayerVehicle[id][pVehPos][1] = Pedagang_Stuff[pdggarageSpawnPos][1];
            PlayerVehicle[id][pVehPos][2] = Pedagang_Stuff[pdggarageSpawnPos][2];
            PlayerVehicle[id][pVehPos][3] = Pedagang_Stuff[pdggarageSpawnPos][3];

            OnPlayerVehicleRespawn(id);
            SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
        }
        case DIALOG_PEDAGANG_GARAGE_DELETE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda bukan anggota Pedagang District ");

            new frmtdel[158], Cache:execute;
            mysql_format(g_SQL, frmtdel, sizeof(frmtdel), "SELECT * FROM `player_vehicles` WHERE `PVeh_Faction` = 6 AND `PVeh_OwnerID` = %d", AccountData[playerid][pID]);
            execute = mysql_query(g_SQL, frmtdel, true);
            if(cache_num_rows())
            {
                new havpid, havmods, havprice, kckstr[255], strgbg[128];
                
                if(listitem >= 0 && listitem < cache_num_rows())
                {
                    cache_get_value_name_int(listitem, "id", havpid);
                    cache_get_value_name_int(listitem, "PVeh_ModelID", havmods);
                    cache_get_value_name_int(listitem, "PVeh_Price", havprice);

                    format(kckstr, sizeof(kckstr), "Anda berhasil menghapus kendaraan:\
                    \nDatabase ID: %d\
                    \nModel: %s", havpid, GetVehicleModelName(havmods));
                    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Hapus Kendaraan", kckstr, "Tutup", "");

                    new pvid = GetFactionVehicleIDFromListitem(playerid, listitem, FACTION_PEDAGANG);

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
        case DIALOG_RANK_SET_PEDAGANG:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pedagang District !");
            if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal Rank Wakil CEO untuk akses Bos Desk!");

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_PEDAGANG, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Error: Tidak dapat diisi kosong!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Magang\n\
            2. Junior\n\
            3. Senior\n\
            4. Manager\n\
            5. Wakil CEO\n\
            6. CEO", "Set", "Batal");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_PEDAGANG, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Error: Hanya dapat diisi angka!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Magang\n\
            2. Junior\n\
            3. Senior\n\
            4. Manager\n\
            5. Wakil CEO\n\
            6. CEO", "Set", "Batal");

            if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pFactionRank]) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_PEDAGANG, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Magang\n\
            2. Junior\n\
            3. Senior\n\
            4. Manager\n\
            5. Wakil CEO\n\
            6. CEO", "Set", "Batal");

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
        case DIALOG_PEDKICKMEMBER:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pedagang District !");
            if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil CEO untuk mengakses Bos Desk!");

            mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 6 ORDER BY `Char_FactionRank` DESC");
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
                mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_OwnerID`=%d AND `PVeh_Faction` = 6", pidrow);
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
                                if(PlayerVehicle[pvid][pVehFaction] == FACTION_PEDAGANG)
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
                        if(AccountData[i][pDutyPedagang])
                            AccountData[i][pDutyPedagang] = false;
                        if(AccountData[i][pUsingUniform])
                            AccountData[i][pUsingUniform] = false;
                        SetPlayerSkin(i, AccountData[i][pSkin]);
                        RefreshFactionMap(i);
                        ShowTDN(i, NOTIFICATION_WARNING, "Anda telah dikeluarkan dari faction Pedagang District !");
                    }
                }
                mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`=0, `Char_FactionRank`=0, `Char_UsingUniform`=0 WHERE `pID`=%d", pidrow);
                mysql_tquery(g_SQL, icsr);
                format(kckstr, sizeof(kckstr), "Anda telah berhasil menendang anggota:\n\
                Nama: %s\n\
                Rank: %s\n\
                Last Online: %s", fckname, PedagangRank[fckrank], fcklastlogin);
                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota",
                kckstr, "Tutup", "");

                AccountData[playerid][pTempSQLFactMemberID] = -1;
                AccountData[playerid][pTempSQLFactRank] = 0;
            }
        }
        case DIALOG_PEDSETRANK:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pedagang District !");
            if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil CEO untuk mengakses Bos Desk!");

            mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 6 ORDER BY `Char_FactionRank` DESC");
            new rows = cache_num_rows();
            if(rows)
            {
                cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
                cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
                if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak dapat mengatur jabatan sendiri!");
                if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengatur jabatan rank diatasmu!");
                ShowPlayerDialog(playerid, DIALOG_RANK_SET_PEDAGANG, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
                "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
                1. Magang\n\
                2. Junior\n\
                3. Senior\n\
                4. Manager\n\
                5. Wakil CEO\n\
                6. CEO", "Set", "Batal");
            }
        }
        case DIALOG_LOUNGES_MASAK:
        {
            if(!response) return 0;
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
            if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pedagang!");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            switch(listitem)
            {
                case 0:
                {
                    AccountData[playerid][ActivityTime] = 1;
                    pMasakTimer[playerid] = SetTimerEx("ProcessNasiGoreng", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMASAK");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
                case 1:
                {
                    AccountData[playerid][ActivityTime] = 1;
                    pMasakTimer[playerid] = SetTimerEx("ProcessBakso", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMASAK");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
                case 2:
                {
                    AccountData[playerid][ActivityTime] = 1;
                    pMasakTimer[playerid] = SetTimerEx("ProcessNasiPecel", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMASAK");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
                case 3:
                {
                    AccountData[playerid][ActivityTime] = 1;
                    pMasakTimer[playerid] = SetTimerEx("ProcessBurdas", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMASAK");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
                case 4:
                {
                    AccountData[playerid][ActivityTime] = 1;
                    pMasakTimer[playerid] = SetTimerEx("ProcessSusuFresh", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMASAK");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
                case 5:
                {
                    AccountData[playerid][ActivityTime] = 1;
                    pMasakTimer[playerid] = SetTimerEx("ProcessKopiKenangan", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMASAK");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
                case 6:
                {
                    AccountData[playerid][ActivityTime] = 1;
                    pMasakTimer[playerid] = SetTimerEx("ProcessMatcha", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMASAK");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
                case 7:
                {
                    AccountData[playerid][ActivityTime] = 1;
                    pMasakTimer[playerid] = SetTimerEx("ProcessEsTeh", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMASAK");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
            }
        }
    }
    return 0;
}

ShowMenuMakanan(playerid)
{
    new str[256];
    format(str, sizeof(str),"1. Paket Low\t" YELLOW_E "%d\n"GRAY "2. Paket Medium\t" YELLOW_E "%d\n"GRAY"3. Paket High\t" YELLOW_E "%d\n"GRAY"4. Paket Special\t"YELLOW"%d",hargalow, hargamedium, hargahigh, hargaspecial);
    ShowPlayerDialog(playerid, DIALOG_MENUMAKAN, DIALOG_STYLE_LIST,"Menu Makanan - Daftar Harga", str, "Tutup", "Tutup");
}

ShowUbahHargaLow(playerid)
{
    new str[64];
    format(str, sizeof(str), "Masukkan harga baru untuk Paket Low:");
    ShowPlayerDialog(playerid, DIALOG_UBAHHARGA_LOW, DIALOG_STYLE_INPUT,"Ubah Harga Paket Low", str, "Ubah", "Batal");
}

ShowUbahHargaMedium(playerid)
{
    new str[64];
    format(str, sizeof(str), "Masukkan harga baru untuk Paket Medium:");
    ShowPlayerDialog(playerid, DIALOG_UBAHHARGA_MEDIUM, DIALOG_STYLE_INPUT,"Ubah Harga Paket Medium", str, "Ubah", "Batal");
}

ShowUbahHargaHigh(playerid)
{
    new str[64];
    format(str, sizeof(str), "Masukkan harga baru untuk Paket High:");
    ShowPlayerDialog(playerid, DIALOG_UBAHHARGA_HIGH, DIALOG_STYLE_INPUT, "Ubah Harga Paket High", str, "Ubah", "Batal");
}

ShowUbahHargaSpecial(playerid)
{
    new str[64];
    format(str, sizeof(str), "Masukkan harga baru untuk Paket Special:");
    ShowPlayerDialog(playerid, DIALOG_UBAHHARGA_SPECIAL, DIALOG_STYLE_INPUT, "Ubah Harga Paket Special", str, "Ubah", "Batal");
}

/*DialogPages:PedagangSetRank(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pedagang District !");
    if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil CEO untuk mengakses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 6 ORDER BY `Char_FactionRank` DESC");
    new rows = cache_num_rows();
    if(rows)
    {
        cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFactMemberID]);
        cache_get_value_name_int(listitem, "Char_FactionRank", AccountData[playerid][pTempSQLFactRank]);
        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFactMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak dapat mengatur jabatan sendiri!");
        if(AccountData[playerid][pTempSQLFactRank] >= AccountData[playerid][pFactionRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengatur jabatan rank diatasmu!");
        ShowPlayerDialog(playerid, DIALOG_RANK_SET_PEDAGANG, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
        "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
        1. Magang\n\
        2. Junior\n\
        3. Senior\n\
        4. Manager\n\
        5. Wakil CEO\n\
        6. CEO", "Set", "Batal");
    }
    return 1;
}

DialogPages:PedagangKickMember(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Pedagang District !");
    if(AccountData[playerid][pFactionRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Wakil CEO untuk mengakses Bos Desk!");

    mysql_query(g_SQL, "SELECT * FROM `player_characters` WHERE `Char_Faction` = 6 ORDER BY `Char_FactionRank` DESC");
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
        mysql_format(g_SQL, strgbg, sizeof(strgbg), "DELETE FROM `player_vehicles` WHERE `PVeh_OwnerID`=%d AND `PVeh_Faction` = 6", pidrow);
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
                        if(PlayerVehicle[pvid][pVehFaction] == FACTION_PEDAGANG)
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
                if(AccountData[i][pDutyPedagang])
                    AccountData[i][pDutyPedagang] = false;
                if(AccountData[i][pUsingUniform])
                    AccountData[i][pUsingUniform] = false;
                SetPlayerSkin(i, AccountData[i][pSkin]);
                RefreshFactionMap(i);
                ShowTDN(i, NOTIFICATION_WARNING, "Anda telah dikeluarkan dari faction Pedagang District !");
            }
        }
        mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Faction`=0, `Char_FactionRank`=0, `Char_UsingUniform`=0 WHERE `pID`=%d", pidrow);
        mysql_tquery(g_SQL, icsr);
        format(kckstr, sizeof(kckstr), "Anda telah berhasil menendang anggota:\n\
        Nama: %s\n\
        Rank: %s\n\
        Last Online: %s", fckname, PedagangRank[fckrank], fcklastlogin);
        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota",
        kckstr, "Tutup", "");

        AccountData[playerid][pTempSQLFactMemberID] = -1;
        AccountData[playerid][pTempSQLFactRank] = 0;
    }
    return 1;
}*/
