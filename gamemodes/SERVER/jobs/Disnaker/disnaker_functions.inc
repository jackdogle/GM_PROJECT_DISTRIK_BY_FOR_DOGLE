#include <YSI\y_hooks>

hook OnGameModeInit()
{
    CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Akses Disnaker", -1, 1424.4442,1546.4249,3010.8323, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
    CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Menu Harga Makanan", -1, 319.2026,-1848.7046,5.1282, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
    // CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Membuat KTP", -1, 1376.7292, 1573.6344, 17.0003, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
    return 1;
}

Dialog:DISNAKER_MENU(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        if(!IsPlayerInRangeOfPoint(playerid, 2.0, 1424.4442,1546.4249,3010.8323)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di area disnaker!");
        switch(listitem)
        {
            case 0: // Ambil Job
            {
                new string[666], countpenambang, countpenebang, countbus, countayam, countpenjahit, countminyak, countnelayan, countpemerah, countpetani, countkargo, countrecycler, countmixer;
                foreach(new i : Player) 
                {
                    if(IsPlayerConnected(i) && GetPlayerJob(i) == JOB_MINER) {
                        countpenambang++;
                    }
                    if(IsPlayerConnected(i) && GetPlayerJob(i) == JOB_LUMBERJACK) {
                        countpenebang++;
                    }
                    if(IsPlayerConnected(i) && GetPlayerJob(i) == JOB_BUS) {
                        countbus++;
                    }
                    if(IsPlayerConnected(i) && GetPlayerJob(i) == JOB_BUTCHER) {
                        countayam++;
                    }
                    if(IsPlayerConnected(i) && GetPlayerJob(i) == JOB_TAILOR) {
                        countpenjahit++;
                    }
                    if(IsPlayerConnected(i) && GetPlayerJob(i) == JOB_OILMAN) {
                        countminyak++;
                    }
                    if(IsPlayerConnected(i) && GetPlayerJob(i) == JOB_FISHERMAN) {
                        countnelayan++;
                    }
                    if(IsPlayerConnected(i) && GetPlayerJob(i) == JOB_MILKER) {
                        countpemerah++;
                    }
                    if(IsPlayerConnected(i) && GetPlayerJob(i) == JOB_FARMER) {
                        countpetani++;
                    }
                    if(IsPlayerConnected(i) && GetPlayerJob(i) == JOB_KARGO) {
                        countkargo++;
                    }
                    if(IsPlayerConnected(i) && GetPlayerJob(i) == JOB_RECYCLER) {
                        countrecycler++;
                    }
                    if(IsPlayerConnected(i) && GetPlayerJob(i) == JOB_DRIVER_MIXERS) {
                        countmixer++;
                    }
                }
                format(string, sizeof(string), "Job\tPekerja\
                \nPenambang\t"YELLOW"%d Orang\
                \n"GRAY"Tukang Kayu\t"YELLOW"%d Orang\
                \nSupir Bus\t"YELLOW"%d Orang\
                \n"GRAY"Tukang Ayam\t"YELLOW"%d Orang\
                \nTukang Jahit\t"YELLOW"%d Orang\
                \n"GRAY"Tukang Minyak\t"YELLOW"%d Orang\
                \nNelayan\t"YELLOW"%d Orang\
                \n"GRAY"Pemerah Susu\t"YELLOW"%d Orang\
                \nPetani\t"YELLOW"%d Orang\
                \n"GRAY"Kargo\t"YELLOW"%d Orang\
                \nRecycler/Pendaur Ulang\t"YELLOW"%d Orang\
                \nDriver Mixer\t"YELLOW"%d Orang", 
                countpenambang, 
                countpenebang, 
                countbus, 
                countayam, 
                countpenjahit, 
                countminyak, 
                countnelayan, 
                countpemerah, 
                countpetani, 
                countkargo, 
                countrecycler,
                countmixer);
                ShowPlayerDialog(playerid, DIALOG_DISNAKER, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Disnaker", string, "Pilih", "Batal");
            }
            case 1: // Buat KTP
            {
                if(AccountData[playerid][Ktp]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki KTP!");
                if(AccountData[playerid][pMoney] < 1500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda membutuhkan $1000 untuk membuat KTP!");
                
                new count = 0, price = 1500;
                foreach(new i : Player) if(IsPlayerConnected(i))
                {
                    if(AccountData[i][pDutyPemerintah]) count++;
                }
                if(count >= 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuat KTP otomatis jika ada Pemerintah di kota!"); 
                
                new govShare = (price / 100) * 20; // 20% dari harga
                PemerintahMoneyVault += govShare;

                new icsr[200];
                mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE stuffs SET pemerintahmoneyvault=%d WHERE ID=0", PemerintahMoneyVault);
                mysql_tquery(g_SQL, icsr);

                AccountData[playerid][Ktp] = 1;
                AccountData[playerid][pKtpTime] = gettime() + (14 * 86400); // 30 Hari waktu internasional
                TakeMoney(playerid, price);
                GenerateRandomNIK(playerid);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membuat KTP!");
            }
            case 2:
            {
                if(GetHousesPaytax(playerid) <= 0)
					return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki rumah");
                
				new id, count = GetHousesPaytax(playerid), mission[2024], lstr[3024];

                new price;
                switch(HouseData[id][hsType])
                {
                    case 1: price = 2000;  // Standart
                    case 2: price = 4000;  // Medium
                    case 3: price = 6000;  // Modern
                    case 4, 99: price = 8000; // Mansion
                    default: price = 2000; // fallback aman
                }
					
				strcat(mission,"ID\tType\tLocation\tExpired\tPajak\n",sizeof(mission));
				Loop(itt, (count + 1), 1)
				{
					id = ReturnHousesPaytaxID(playerid, itt);

					if(itt == count)
					{
						format(lstr,sizeof(lstr), "%d\t%s\t%s\t%s\t%d\n", id, GetTypeHouseName(id), GetLocation(HouseData[id][hsExtPos][0], HouseData[id][hsExtPos][1], HouseData[id][hsExtPos][2]), ReturnTimelapse(gettime(), HouseData[id][hVisit]), price);
					}
					else format(lstr,sizeof(lstr), "%d\t%s\t%s\t%s\t%d\n", id, GetLocation(HouseData[id][hsExtPos][0], HouseData[id][hsExtPos][1], HouseData[id][hsExtPos][2]), ReturnTimelapse(gettime(), HouseData[id][hVisit]), price);	
					strcat(mission,lstr,sizeof(mission));
				}
				ShowPlayerDialog(playerid, DIALOG_PAYTAX_HOUSE, DIALOG_STYLE_TABLIST_HEADERS,"Houses Tax",mission,"Select","Cancel");
            }
            case 3: // Sewa Gudang via Disnaker tanpa Iter_Begin
            {
                new count = 0;
                foreach(new i : Player) if(IsPlayerConnected(i))
                {
                    if(AccountData[i][pDutyPemerintah]) count++;
                }
                if(count >= 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menyewa gudang otomatis jika ada Pemerintah di kota!"); 

                static list[4096];
                list[0] = '\0';

                new found = 0;
                for(new id = 0; id < MAX_DYNAMIC_GUDANG; id++)
                {
                    if(!Iter_Contains(Gudang, id)) continue;

                    static tmp[256];
                    format(tmp, sizeof(tmp), "%s\t"GREEN"%s / bulan\n", GudangData[id][gudangName], FormatMoney(GudangData[id][gudangPrice]));
                    strcat(list, tmp, sizeof(list));

                    found++;
                }
                if(found == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Belum ada gudang tersedia!");

                AccountData[playerid][pTempValue] = -1; // belum pilih
                ShowPlayerDialog(playerid, DIALOG_GUDANG_BUY, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Pilih Gudang",list, "Pilih", "Batal");
            }
        }
    }
    else Info(playerid, "Anda telah membatalkan pilihan");
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, 1424.4442,1546.4249,3010.8323))
        {
            Dialog_Show(playerid, DISNAKER_MENU, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Disnaker Menu",
            "Ambil Pekerjaan\n"GRAY"Membuat KTP\n"GRAY"Pajak Rumah\n"GRAY"Sewa Gudang", "Pilih", "Batal");
        }
    }
    return 1;
}
hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_DISNAKER:
        {
            if(!response) return 1;
            switch(listitem)
            {
                case 0:// 
                {
                    UnloadVarsPlayerJob(playerid);
                    AccountData[playerid][pJob] = JOB_MINER;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil pekerjaan menjadi seorang Penambang!");
                    MinerJobStuffs(playerid);
                }
                case 1:// 
                {
                    UnloadVarsPlayerJob(playerid);
                    AccountData[playerid][pJob] = JOB_LUMBERJACK;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil pekerjaan menjadi seorang Tukang Kayu!");
                    LoadVarsLumber(playerid);
                    
                }
                case 2:// 
                {
                    UnloadVarsPlayerJob(playerid);
                    AccountData[playerid][pJob] = JOB_BUS;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil pekerjaan menjadi seorang Supir Bus!");
                    LoadVarsBus(playerid);
                }
                case 3:// 
                {
                    UnloadVarsPlayerJob(playerid);
                    AccountData[playerid][pJob] = JOB_BUTCHER;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil pekerjaan menjadi seorang Tukang Ayam!");
                    LoadVarsButcher(playerid);
                }
                case 4://
                {
                    UnloadVarsPlayerJob(playerid);
                    AccountData[playerid][pJob] = JOB_TAILOR;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil pekerjaan menjadi seorang Tukang Jahit!");
                    LoadVarsTailor(playerid);
                }
                case 5:// 
                {
                    UnloadVarsPlayerJob(playerid);
                    AccountData[playerid][pJob] = JOB_OILMAN;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil pekerjaan menjadi seorang Tukang Minyak!");
                    LoadVarsOilman(playerid);
                }
                case 6:// 
                {
                    UnloadVarsPlayerJob(playerid);
                    AccountData[playerid][pJob] = JOB_FISHERMAN;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil pekerjaan menjadi seorang Nelayan!");
                    LoadVarsFisherman(playerid);
                }
                case 7://
                {
                    UnloadVarsPlayerJob(playerid);
                    AccountData[playerid][pJob] = JOB_MILKER;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil pekerjaan menjadi seorang Pemerah Susu!");
                    LoadVarsMilker(playerid);
                }
                case 8:// 
                {
                    UnloadVarsPlayerJob(playerid);
                    AccountData[playerid][pJob] = JOB_FARMER;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil pekerjaan menjadi seorang Petani!");
                    LoadVarsFarmer(playerid);
                }
                case 9://
                {
                    UnloadVarsPlayerJob(playerid);
                    AccountData[playerid][pJob] = JOB_KARGO;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil pekerjaan Kargo!");
                    LoadVarsKargo(playerid);
                }
                case 10://
                {
                    UnloadVarsPlayerJob(playerid);
                    AccountData[playerid][pJob] = JOB_RECYCLER;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil pekerjaan menjadi seorang Recycler!");
                    LoadVarsDaur(playerid);
                }
                case 11:
                {
                    UnloadVarsPlayerJob(playerid);
                    AccountData[playerid][pJob] = JOB_DRIVER_MIXERS;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil pekerjaan menjadi seorang driver mixer!");
                }
                case 12:// 
                {
                    UnloadVarsPlayerJob(playerid);
                    AccountData[playerid][pJob] = JOB_NONE;
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menjadi seorang Pengangguran!");
                }
                case 13://
                {
                    ShowTDN(playerid, NOTIFICATION_WARNING, "Sedang dalam perbaikan!");
                    // UnloadVarsPlayerJob(playerid);
                    // AccountData[playerid][pJob] = JOB_TRASHMASTER;
                    // ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil pekerjaan menjadi seorang Tukang Sampah!");
                    // LoadVarsTrashmaster(playerid);
                }
            }
        }
        case DIALOG_PAYTAX_HOUSE:
        {
            if(response)
            {
                new id = ReturnHousesPaytaxID(playerid, (listitem + 1));
                new price;

                switch(HouseData[id][hsType])
                {
                    case 1: price = 2000;  // Standart (Dollar Menengah)
                    case 2: price = 4000;  // Medium
                    case 3: price = 6000;  // Modern
                    case 4, 99: price = 8000; // Mansion
                    default: price = 2000;
                }

                if(AccountData[playerid][pMoney] < price)
                {
                    ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup untuk membaya pajak rumah");
                }

                new count = 0;
                foreach(new i : Player) if(IsPlayerConnected(i))
                {
                    if(AccountData[i][pDutyPemerintah]) count++;
                }
                if(count >= 1)
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membayar pajak jika ada Pemerintah sedang bertugas!");

                HouseData[id][hVisit] = gettime() + (86400 * 14);
                HouseRefresh(id);
                HouseSave(id);

                TakeMoney(playerid, price);
                new govShare = (price / 100) * 20; // 20% dari harga
                PemerintahMoneyVault += govShare;

                new icsr[200];
                mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE stuffs SET pemerintahmoneyvault=%d WHERE ID=0", PemerintahMoneyVault);
                mysql_tquery(g_SQL, icsr);

                Info(playerid, "Kamu telah membayar pajak rumah %s (ID: %d) selama 14 hari dengan harga "GREEN_E"$%d"WHITE_E".", GetLocation(HouseData[id][hsExtPos][0], HouseData[id][hsExtPos][1], HouseData[id][hsExtPos][2]), id, price);
            }
            return 1;
        }
    }
    return 1;
}
