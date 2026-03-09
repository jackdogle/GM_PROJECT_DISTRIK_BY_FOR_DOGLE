#include <YSI\y_hooks>
CMD:dice(playerid, params[])
{
	if(AccountData[playerid][pInDoor] != 16 && AccountData[playerid][pInDoor] != 17 && AccountData[playerid][pInDoor] != 18 && AccountData[playerid][pInDoor] != 19) return Error(playerid, "Anda hanya dapat menggunakan dadu di setiap Casino!");
	
	new value;
	if(sscanf(params, "d", value)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/dice [type dice] (1. Satu Dadu | 2. Dua Dadu)");
	if(value < 1 || value > 2) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/dice [type dice] (1. Satu Dadu | 2. Dua Dadu) [Ikuti Format]");

	switch(value)
	{
		case 1: SendNearbyMessage(playerid, 15.0, COLOR_PURPLE, "** %s melempar sebuah dadu ke udara, dan dadu tersebut menunjukkan nilai "RED"%d", ReturnName(playerid), Random(1, 6));
		case 2: SendNearbyMessage(playerid, 15.0, COLOR_PURPLE, "** %s melempar sebuah dadu ke udara, dan dadu tersebut menunjukkan nilai "RED"%d", ReturnName(playerid), Random(1, 12));
	}
	return 1;
}

/*CMD:gacha(playerid, params[]) {
    PlayerTextDrawShow(playerid, tutup[playerid]);
    PlayerTextDrawShow(playerid, pakaigacha[playerid]);
    forex(i, 47) PlayerTextDrawShow(playerid, GachaTextDraw[playerid][i]);
    SelectTextDraw(playerid, COLOR_YELLOW);
    return 1;
}*/

CMD:livestream(playerid, params[])
{
	SendClientMessage(playerid, -1, ""BLUEJEGE"-------- [Player Livestream Channel] --------");

	foreach(new i : Player) if (LivemodeOn[i] && LivemodeTittle[i][0] != EOS) {
		SendClientMessageEx(playerid, -1, ""BLUEJEGE"%s[%d]: "WHITE"%s", AccountData[i][pUCP], i, LivemodeTittle[i]);
	}

	SendClientMessage(playerid, -1, ""BLUEJEGE"---------------------------------------------------------");
	return 1;
}

CMD:livemode(playerid, params[])
{
	new frmtxt[255];
	if(sscanf(params, "s[255]", frmtxt)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/livemode [judul]");
	if(LivemodeOn[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah berada didalam Livemode, hapus terlebih dulu ~y~'/livemodeoff'");

	LivemodeOn[playerid] = true;
	format(LivemodeTittle[playerid], sizeof(frmtxt), ""BLUEJEGE"%s", frmtxt);
	SendClientMessage(playerid, -1, ""BLUEJEGE"LIVESTREAM: "WHITE"Enable");

	AccountData[playerid][LiveStream] = CreateDynamic3DTextLabel(LivemodeTittle[playerid], -1, 0, 0, -10, 10.0, playerid);
	Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, AccountData[playerid][LiveStream], E_STREAMER_ATTACH_OFFSET_Z, 0.30);
	return 1;
}

CMD:livemodeoff(playerid, params[])
{
	if(!LivemodeOn[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang tidak dalam Livestreaming Mode!");

	LivemodeOn[playerid] = false;
	LivemodeTittle[playerid][0] = EOS;
	SendClientMessage(playerid, -1, ""BLUEJEGE"LIVESTREAM: "WHITE"Disabled");

	if(IsValidDynamic3DTextLabel(AccountData[playerid][LiveStream])) DestroyDynamic3DTextLabel(AccountData[playerid][LiveStream]);
	return 1;
}

CMD:fspawn(playerid, params[])
{
	SendStaffMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Fake Spawn", ReturnName(playerid), playerid);
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Fake Spawn", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

CMD:cdm(playerid, params[])
{
	SendStaffMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Fake Spawn", ReturnName(playerid), playerid);
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Fake Spawn", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

CMD:mapstealer(playerid, params[])
{
	SendStaffMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Mapstealer.luac", ReturnName(playerid), playerid);
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Mapstealer.luac", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

CMD:rem(playerid, params[])
{
	SendStaffMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Rem. CS", ReturnName(playerid), playerid);
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Rem. CS", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

CMD:kontol1(playerid, params[])
{
	SendStaffMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan dDos. ", ReturnName(playerid), playerid);
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Ddos.", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

CMD:revter(playerid, params[])
{
	SendStaffMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan revter. ", ReturnName(playerid), playerid);
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan revter.", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

CMD:fakeafk(playerid, params[])
{
	SendStaffMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Fake AFK!", ReturnName(playerid), playerid);
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Fake AFK!", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

CMD:invis(playerid, params[])
{
	SendStaffMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Invisible Hacks", ReturnName(playerid), playerid);
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Invisible Hacks", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

CMD:dgun(playerid, params[])
{
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Weapon Hacks", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

CMD:attachedit(playerid, params[])
{
	CallRemoteFunction("AttachEditFS", "d", playerid);
	return 1;
}


CMD:netstats(playerid, params[])
{
	new hours, minutes, seconds;
	GetElapsedTime(AccountData[playerid][OnlineTimer], hours, minutes, seconds);
	SendClientMessageEx(playerid, -1, "[i] Ping: %d ms | Packet Loss: %.2f | Playtime: %02d:%02d:%02d", GetPlayerPing(playerid), GetPlayerPacketLoss(playerid), hours, minutes, seconds);
	return 1;
}

alias:dokterlokal("medis")
CMD:dokterlokal(playerid, params[])
{
	if(!AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya dapat digunakan saat pingsan!");
	if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");

	new count;
	foreach(new i : Player) if (AccountData[i][IsLoggedIn])
	{
		if(AccountData[i][pFaction] == FACTION_EMS && AccountData[i][pDutyEms]) count ++;
	}
	if(count >= 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat digunakan saat ada EMS Duty!");

	AccountData[playerid][ActivityTime] = 1;
	PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "DOKTER LOKAL");
	ShowProgressBar(playerid);
	
	AccountData[playerid][DokterLokalTimer] = SetTimerEx("UsingDokterLokal", 1000, true, "d", playerid);
	return 1;
}

CMD:fps(playerid, params[])
{
	if(!AccountData[playerid][ToggleFPS])
	{
		AccountData[playerid][ToggleFPS] = true;
		PlayerTextDrawShow(playerid, FPStextdraws[playerid][0]);
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda mengaktifkan FPS Info");
	}
	else
	{
		AccountData[playerid][ToggleFPS] = false;
		PlayerTextDrawHide(playerid, FPStextdraws[playerid][0]);
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda mengaktifkan FPS Info");
	}
	return 1;
}

CMD:exittrunk(playerid, params[])
{
	if(!AccountData[playerid][pSpawned])
		return 0;
	
	if(GetPVarInt(playerid, "PlayerInTrunk") != 1) 
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang berada di dalam bagasi!");
	
	new Float:x, Float:y, Float:z;
	GetVehicleBoot(AccountData[playerid][pTempVehID], x, y, z);
	PlayerSpectateVehicle(playerid, INVALID_VEHICLE_ID);
	
	SendRPMeAboveHead(playerid, "Keluar dari dalam bagasi", X11_PLUM1);
	SetSpawnInfo(playerid, 0, AccountData[playerid][pSkin], x, y, z, 0.0, 0, 0, 0, 0, 0, 0);
	TogglePlayerSpectating(playerid, false);

	SetPlayerHealth(playerid, AccountData[playerid][pHealth]);
	SetPlayerArmour(playerid, AccountData[playerid][pArmour]);
	SetPVarInt(playerid, "PlayerInTrunk", 0);
	TrunkVehEntered[AccountData[playerid][pTempVehID]] = INVALID_PLAYER_ID;
	AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
	return 1;
}

CMD:settings(playerid, params[])
{
	if(!AccountData[playerid][pSpawned])
		return 0;

	if(Dialog_Opened(playerid))
		return 0;

	static list[522];
	format(list, sizeof(list), "Settings\tStatus\
	\n"WHITE"Character ID:\t"RED"%d\
	\n"GRAY"Username Control Panel (UCP):\t"GRAY"%s\
	\n"WHITE"Username Character:\t"WHITE"%s\n\
	\n"GRAY"Dynamic Object Render\t%s\
	\n"WHITE"Auto Engine\t%s\
	\n"GRAY"Private Message\t%s\
	\n"WHITE"Global Message\t%s\
	\n"GRAY"Notif Style\t%s\
	\n"WHITE"HUD Style\t%s", AccountData[playerid][pID], AccountData[playerid][pUCP], AccountData[playerid][pName], GetPlayerRenderName(playerid),
	AccountData[playerid][pTogAutoEngine] ? ""GREEN"Aktif" : ""RED"Nonaktif", AccountData[playerid][pTogPM] ? ""GREEN"Aktif" : ""RED"Nonaktif", AccountData[playerid][pTogGlobal] ? ""GREEN"Aktif" : ""RED"Nonaktif",
	AccountData[playerid][pStyleNotif] == 1 ? ""YELLOW"Textdraw" : ""YELLOW"Chat Logs", AccountData[playerid][pHUDMode] == 1 ? ""YELLOW"Kiri" : ""YELLOW"Tengah");
	Dialog_Show(playerid, DialogToggle, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Settings", list, "Pilih", "Batal");
	return 1;
}

CMD:cl(playerid, params[])
{
	new
		option[24],
		angka1,
		angka2,
		result;
	
	if(sscanf(params, "ds[24]d", angka1, option, angka2))
	{
		ShowTDN(playerid, NOTIFICATION_INFO, "/cl [angka1] [operator] [angka2] (Cth: /cl 25 * 55)");
		return 1;
	}

	// Untuk mengecek apakah operator valid
	if(!strcmp(option, "*", true)) // perkalian
	{
		result = angka1 * angka2;
	}
	else if(!strcmp(option, "/", true)) // pembagian
	{
		result = angka1 / angka2;
	}
	else if(!strcmp(option, "-", true)) // pengurangan
	{
		result = angka1 - angka2;
	}
	else if(!strcmp(option, "+", true)) // Penambahan
	{
		result = angka1 + angka2;
	}
	else 
	{
		Error(playerid, "Operator tidak valid!");
	}

	ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Hasil dari kalkulator: "YELLOW"%d", result));
	return 1;
}

CMD:mywarn(playerid, params[])
{
	new query[255], Cache:execute;
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `warninglogs` WHERE `pID`=%d", AccountData[playerid][pID]);
	execute = mysql_query(g_SQL, query, true);
	new rowscount = cache_num_rows();
	if(rowscount)
	{
		new list[1218], type, typename[125], sender[64], date, reason[128];
		format(list, sizeof(list), "Type\tPenerbit\tTanggal\tAlasan\n");
		for(new x; x < rowscount; ++x)
		{
			cache_get_value_name_int(x, "WarnType", type);
			cache_get_value_name(x, "WarnSender", sender);
			cache_get_value_name_int(x, "WarnTime", date);
			cache_get_value_name(x, "WarnReason", reason);
			switch(type)
			{
				case 1: format(typename, sizeof(typename), ""ORANGE"[Warn]");
				case 2: format(typename, sizeof(typename), ""YELLOW"[Jail]");
				case 3: format(typename, sizeof(typename), ""RED"[BAN]");
			}

			format(list, sizeof(list), "%s%s\t%s\t%s\t%s\n", list, typename, sender, ReturnDateNoTime(date), reason);
		}
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Riwayat Peringatan", list, "Tutup", "");
	}
	else 
	{
		new list[255];
		format(list, sizeof(list), "Type\tPenerbit\tTanggal\tAlasan\n");
		format(list, sizeof(list), "%sTidak ada peringatan yang dapat ditampilkan kepadamu.", list);
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Riwayat Peringatan", list, "Tutup", "");
	}
	cache_delete(execute);
	return 1;
}

CMD:delay(playerid, params[])
{
	if(!SQL_IsCharacterLogged(playerid))
		return 0;
	
	new shstr[255];
	format(shstr, sizeof(shstr), "Kegiatan\tWaktu (Menit)\
	\nMower Sidejob\t%d\
	\n"GRAY"Delivery Sidejob\t"GRAY"%d\
	\nSweeper Sidejob\t%d\
	\n"GRAY"Forklift Sidejob\t"GRAY"%d\
	\nTrashmaster Sidejob\t%d", 
	AccountData[playerid][pMowerTime]/60, 
	AccountData[playerid][pDeliveryTime]/60, 
	AccountData[playerid][pSweeperTime]/60,
	AccountData[playerid][pForkliftTime]/60,
	AccountData[playerid][pTrashmasterDelay]/60);
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Waktu Delay", shstr, "Tutup", "");
	return 1;
}

CMD:sm(playerid, params[])
{
	new 
		list[2046],
		status1[100],
		status2[100],
		status3[100],
		status4[100],
		status5[100],
		status6[100],
		PoliceCount,
		EMSCount
	;
	
	foreach(new i : Player) if (IsPlayerConnected(i)) {
		if(AccountData[i][pDutyPD]) PoliceCount++;
		if(AccountData[i][pDutyEms]) EMSCount++;
	}
	if(PoliceCount >= 4 && EMSCount >= 2) 
	{
		status1 = ""GREEN"Boleh";
		status2 = ""GREEN"Boleh";
		status3 = ""GREEN"Boleh";
		status4 = ""GREEN"Boleh";
	} 
	else 
	{
		status1 = ""ORANGE"Mendung";
		status2 = ""ORANGE"Mendung";
		status3 = ""ORANGE"Mendung";
		status4 = ""ORANGE"Mendung";
	}
	if(PoliceCount >= 5 && EMSCount >= 3) {
		status5 = ""GREEN"Boleh";
	} else {
		status5 = ""ORANGE"Mendung";
	}

	if(PoliceCount >= 15 && EMSCount >= 6) {
		status6 = ""GREEN"Boleh";
	} else {
		status6 = ""ORANGE"Mendung";
	}

	format(list, sizeof(list), "Kegiatan Roleplay\tKeperluan\tStatus\
	\nBegal/Copet/Scam\t4 Polisi & 2 EMS\t%s\
	\n"GRAY"Ladang (Uranium/Kanabis)/Crafting/Cuci Uang\t"GRAY"4 Polisi & 2 EMS\t%s\
	\nCarsteal\t4 Polisi & 2 EMS\t%s\
	\n"GRAY"Rampok Warung\t"GRAY"4 Polisi & 2 EMS\t%s\
	\n"GRAY"Rampok Jewelry\t"GRAY"5 Polisi & 3 EMS\t%s\
	\nPeperangan\t15 Polisi & 6 EMS\t%s", status1, status2, status3, status4, status5, status6);
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Status Mendung", list, "Tutup", "");
	return 1;
}

/*CMD:skydive(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 2.5, -2237.6846, -1743.9290, 480.8447)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya bisa digunakan di point SkyDive!");
	if(AccountData[playerid][pMoney] < 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup untuk skydive!");

	SetPlayerPos(playerid, -2207.0583, -1802.6747, 748.9734);
	ShowItemBox(playerid, "Removed $50", "UANG", 1212);
	TakeMoney(playerid, 50);
	SendClientMessage(playerid, -1, ""YELLOW"SKYDIVE:"WHITE" Jangan lupa untuk membuka parasutmu!");
	
	SetPVarInt(playerid, "DurringSkyDive", 1);
	GivePlayerWeapon(playerid, 46, 1);
	return 1;
}*/

CMD:mask(playerid, params[])
{
	new frmtmask[100], Float:HP, Float:AM;
	GetPlayerHealth(playerid, HP);
	GetPlayerArmour(playerid, AM);

	if(AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang Duty Administrator!");
	if(AccountData[playerid][pLevel] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu harus level 5 untuk menggunakan ini!");
	if(!PlayerHasItem(playerid, "Masker")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Masker!");
	if(!AccountData[playerid][pMaskOn])
	{
		AccountData[playerid][pMaskOn] = 1;
		format(frmtmask, sizeof(frmtmask), "Mask #%d\nH: ["RED"%.2f"WHITE"] A: [%.2f]", AccountData[playerid][pMaskID], HP, AM);
		foreach(new i : Player) if (IsPlayerConnected(i))
		{
			if(IsValidDynamic3DTextLabel(NameTag[i][playerid]))
				DestroyDynamic3DTextLabel(NameTag[i][playerid]);
			
			NameTag[i][playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
		}
		AccountData[playerid][pMaskLabel] = CreateDynamic3DTextLabel(frmtmask, -1, 0.0, 0.0, 0.25, 20.0, playerid, INVALID_VEHICLE_ID, 1, -1, -1, -1, 20.0, -1, 0);
		SendRPMeAboveHead(playerid, "Mengeluarkan masker dan menggunakannya", X11_PLUM1);
	}
	else
	{
		AccountData[playerid][pMaskOn] = 0;
		if(IsValidDynamic3DTextLabel(AccountData[playerid][pMaskLabel])) DestroyDynamic3DTextLabel(AccountData[playerid][pMaskLabel]);
		SendRPMeAboveHead(playerid, "Melepas masker miliknya", X11_PLUM1);
	}
	return 1;
}

CMD:evipname(playerid, params[])
{
	if(!AccountData[playerid][pVip]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pengguna Vip!");	

	ShowPlayerDialog(playerid, DIALOG_VIP_NAME, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Vip Name Custom",
	"Gunakan format dibawah ini untuk menambahkan warna\
	\n- (b) = Warna Biru\
	\n- (p) = Warna Pink\
	\n- (bl) = Warna Hitam\
	\n- (w) = Warna Putih\
	\n- (r) = Warna Merah\
	\n- (g) = Warna Hijau\
	\n- (y) = Warna Kuning\
	\n\nContoh: (r)Merah (y)Kuning (g)Hijau = Warna Akan Merah Kuning Hijau\
	\n(Masukkan nama vip custom anda dibawah ini):", "Submit", "Batal");
	return 1;
}

CMD:mprice(playerid, params[])
{
	if(!AccountData[playerid][IsLoggedIn]) 
		return 0;
	
	static frmtprice[2856];
	format(frmtprice, sizeof(frmtprice), ""YELLOW"========== [Dinas Pekerjaan Kota District ] ==========\
	\n\n"WHITE"------ [Hasil Pertambangan] ------\
	\n"WHITE"~> Harga Tembaga: "RED"%s"ARWIN1"/pcs"WHITE" =>"GREEN" %s"ARWIN1"/pcs\
	\n"WHITE"~> Harga Besi: "RED"%s"ARWIN1"/pcs"WHITE" =>"GREEN" %s"ARWIN1"/pcs\
	\n"WHITE"~> Harga Emas: "RED"%s"ARWIN1"/pcs"WHITE" =>"GREEN" %s"ARWIN1"/pcs\
	\n"WHITE"~> Harga Berlian: "RED"%s"ARWIN1"/pcs"WHITE" =>"GREEN" %s"ARWIN1"/pcs\
	\n"WHITE"~> Harga Material: "RED"%s"ARWIN1"/pcs"WHITE" =>"GREEN" %s"ARWIN1"/pcs\
	\n\n"WHITE"------ [Hasil Recycler] ------\
	\n"WHITE"~> Harga Alumunium: "RED"%s"ARWIN1"/pcs"WHITE" =>"GREEN" %s"ARWIN1"/pcs\
	\n"WHITE"~> Harga Karet: "RED"%s"ARWIN1"/pcs"WHITE" =>"GREEN" %s"ARWIN1"/pcs\
	\n"WHITE"~> Harga Kaca: "RED"%s"ARWIN1"/pcs"WHITE" =>"GREEN" %s"ARWIN1"/pcs\
	\n"WHITE"~> Harga Baja: "RED"%s"ARWIN1"/pcs"WHITE" =>"GREEN" %s"ARWIN1"/pcs\
	\n\n"WHITE"------ [Lainnya] -----\
	\n"WHITE"~> Harga Ayam Kemas: "RED"%s"ARWIN1"/pcs"WHITE" =>"GREEN" %s"ARWIN1"/pcs\
	\n"WHITE"~> Harga Susu Olahan: "RED"%s"ARWIN1"/pcs"WHITE" =>"GREEN" %s"ARWIN1"/pcs\
	\n"WHITE"~> Harga Pakaian: "RED"%s"ARWIN1"/pcs"WHITE" =>"GREEN" %s"ARWIN1"/pcs\
	\n"WHITE"~> Harga Kayu Kemas: "RED"%s"ARWIN1"/pcs"WHITE" =>"GREEN" %s"ARWIN1"/pcs\
	\n"WHITE"~> Harga Gas: "RED"%s"ARWIN1"/pcs"WHITE" =>"GREEN" %s"ARWIN1"/pcs",
	FormatMoney(OldTembagaPrice), FormatMoney(TembagaPrice),
	FormatMoney(OldBesiPrice), FormatMoney(BesiPrice),
	FormatMoney(OldEmasPrice), FormatMoney(EmasPrice),
	FormatMoney(OldBerlianPrice), FormatMoney(BerlianPrice),
	FormatMoney(OldMaterialPrice), FormatMoney(MaterialPrice),
	FormatMoney(OldAlumuniumPrice), FormatMoney(AlumuniumPrice),
	FormatMoney(OldKaretPrice), FormatMoney(KaretPrice),
	FormatMoney(OldKacaPrice), FormatMoney(KacaPrice),
	FormatMoney(OldBajaPrice), FormatMoney(BajaPrice),
	FormatMoney(OldAyamKemasPrice), FormatMoney(AyamKemasPrice),
	FormatMoney(OldSusuOlahPrice), FormatMoney(SusuOlahPrice),
	FormatMoney(OldPakaianPrice), FormatMoney(PakaianPrice),
	FormatMoney(OldKayuKemasPrice), FormatMoney(KayuKemasPrice),
	FormatMoney(OldGasPrice), FormatMoney(GasPrice));
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Harga Penjualan", frmtprice, "Tutup", "");
	return 1;
}

CMD:cmusik(playerid, params[])
{
	if(AccountData[playerid][pVip] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pengguna VIP!");
	new vehicleid = GetPlayerVehicleID(playerid);
	new vehicle_index = Vehicle_ReturnID(vehicleid);

	if(vehicle_index == RETURN_INVALID_VEHICLE_ID)
		return 1;
	
	if(!IsPlayerInAnyVehicle(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya bisa digunakan  didalam kendaraan!");
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu harus pindah ke kursi Driver untuk menggunakan ini!");
	Dialog_Show(playerid, VehicleAudioPlayer, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Vehicle Music", "Spotify - Cerahi Hidupmu Secerah Matahari Di Pagi Hari\n\n"GRAY"Kami sarankan anda untuk upload file mp3 ke discord terlebih dahulu.\n"RED_E"Note: Fitur ini tidak support link Youtube secara langsung!\nMasukan off untuk mematikan lagu!\n\n"YELLOW"(Apabila file mp3 telah di upload ke discord, silahkan copy linknya dan paste dibawah ini):",
	"Input", "Batal");
	return 1;
}

Dialog:VehicleAudioPlayer(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(strlen(inputtext) < 1 || strlen(inputtext) > 128)
			return 	Dialog_Show(playerid, VehicleAudioPlayer, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Vehicle Music", "ERROR, panjang link tidak boleh di bawah 1 maximal 128 karakter!\n\nSpotify - Cerahi Hidupmu Secerah Matahari Di Pagi Hari\n\n"GRAY"Kami sarankan anda untuk upload file mp3 ke discord terlebih dahulu.\n"RED_E"Note: Fitur ini tidak support link Youtube secara langsung!\nMasukan off untuk mematikan lagu!\n\n"YELLOW"(Apabila file mp3 telah di upload ke discord, silahkan copy linknya dan paste dibawah ini):", "Input", "Batal");

		PlayVehicleAudioInCar(playerid, inputtext);
	}
	else ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan!");
	return 1;
}

Dialog:DialogToggle(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(response)
	{
		switch(listitem)
		{
			case 3: // Dynamic Render
			{
				ShowPlayerDialog(playerid, DIALOG_STREAMER_CONFIG, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Setting Render",
				"Priority\tRendered Object\tRadius Multiplayer\
				\nVery Low\t250\t0.2\
				\n"GRAY"Low\t500\t0.5\
				\nMedium\t750\t1.0\
				\n"GRAY"High\t1000\t2.0", "Set", "Batal");
			}
			case 4:// Auto Engine
			{
				switch(AccountData[playerid][pTogAutoEngine])
				{
					case false:
					{
						AccountData[playerid][pTogAutoEngine] = AccountData[playerid][pTogAutoEngine] ? (false) : (true);
						mysql_tquery(g_SQL, sprintf("UPDATE player_characters SET Char_TogAutoEngine = '%d' WHERE pID = '%d'", AccountData[playerid][pTogAutoEngine], GetUCPSQLID(playerid)));
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda Mengaktifkan Auto Engine!");
					}
					case true:
					{
						AccountData[playerid][pTogAutoEngine] = AccountData[playerid][pTogAutoEngine] ? (false) : (true);
						mysql_tquery(g_SQL, sprintf("UPDATE player_characters SET Char_TogAutoEngine = '%d' WHERE pID = '%d'", AccountData[playerid][pTogAutoEngine], GetUCPSQLID(playerid)));
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda Mematikan Auto Engine!");
					}
				}
			}
			case 5:// Toggle Private Message
			{
				switch(AccountData[playerid][pTogPM])
				{
					case false:// Nyalakan
					{
						AccountData[playerid][pTogPM] = AccountData[playerid][pTogPM] ? (false) : (true);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda mengaktifkan Private Message");
						mysql_tquery(g_SQL, sprintf("UPDATE player_characters SET Char_TogPM = '%d' WHERE pID = '%d'", AccountData[playerid][pTogPM], GetUCPSQLID(playerid)));
					}
					case true://
					{
						AccountData[playerid][pTogPM] = AccountData[playerid][pTogPM] ? (false) : (true);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda mematikan Private Message");
						mysql_tquery(g_SQL, sprintf("UPDATE player_characters SET Char_TogPM = '%d' WHERE pID = '%d'", AccountData[playerid][pTogPM], GetUCPSQLID(playerid)));
					}
				}
			}
			case 6:// Toggle Global Message
			{
				switch(AccountData[playerid][pTogGlobal])
				{
					case false:// Nyalakan
					{
						AccountData[playerid][pTogGlobal] = AccountData[playerid][pTogGlobal] ? (false) : (true);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda mengaktifkan Global Message");
						mysql_tquery(g_SQL, sprintf("UPDATE player_characters SET Char_TogPM = '%d' WHERE pID = '%d'", AccountData[playerid][pTogGlobal], GetUCPSQLID(playerid)));
					}
					case true://
					{
						AccountData[playerid][pTogGlobal] = AccountData[playerid][pTogGlobal] ? (false) : (true);
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda mematikan Global Message");
						mysql_tquery(g_SQL, sprintf("UPDATE player_characters SET Char_TogPM = '%d' WHERE pID = '%d'", AccountData[playerid][pTogGlobal], GetUCPSQLID(playerid)));
					}
				}
			}
			case 7:// Toggle Notif Style
			{
				switch(AccountData[playerid][pStyleNotif])
				{
					case 1:// Nyalakan
					{
						AccountData[playerid][pStyleNotif] = 2;
						ShowTDN(playerid, NOTIFICATION_INFO, "Style Notif Berhasil diubah menjadi Chat Logs");
						mysql_tquery(g_SQL, sprintf("UPDATE player_characters SET Char_NotifStyle = '%d' WHERE pID = '%d'", AccountData[playerid][pStyleNotif], GetUCPSQLID(playerid)));
					}
					case 2://
					{
						AccountData[playerid][pStyleNotif] = 1;
						ShowTDN(playerid, NOTIFICATION_INFO, "Style Notif Berhasil diubah menjadi Textdraws");
						mysql_tquery(g_SQL, sprintf("UPDATE player_characters SET Char_NotifStyle = '%d' WHERE pID = '%d'", AccountData[playerid][pStyleNotif], GetUCPSQLID(playerid)));
					}
				}
			}
			case 8: // Hud mode
			{
				switch(AccountData[playerid][pHUDMode])
				{
					case 1: // Kiri
					{
						AccountData[playerid][pHUDMode] = 2;
						ShowHbeTextdraws(playerid, AccountData[playerid][pHUDMode]);
						ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengubah HUD Style Kiri");
					}
					case 2:
					{
						AccountData[playerid][pHUDMode] = 1;
						ShowHbeTextdraws(playerid, AccountData[playerid][pHUDMode]);
						ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengubah HUD Style Tengah");
					}
				}
			}
		}
	}
	return 1;
}

// --------------------- LAPOR KEPADA FACTION-----------------
/*CMD:911(playerid, params[])
{
	static 
		Float:x, Float:y, Float:z;
	
	GetPlayerPos(playerid, x, y, z);

	if(isnull(params))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/911 [message]");

	if(AccountData[playerid][pHotlineTime] >= gettime()){
		ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Mohon menunggu %d detik untuk mengirim hotline ke factions kembali", AccountData[playerid][pHotlineTime] - gettime()));
		return 1;
	}
	foreach(new i : Player) {
		if(AccountData[i][pFaction] == 1 && AccountData[i][pDutyPD]) {
			SendClientMessageEx(i, -1, ""GRAY"[911] "WHITE"Laporan Dari %s (%d) // Lokasi: %s // No Telpon: %s", GetRPName(playerid), playerid, GetLocation(x, y, z), AccountData[playerid][pPhone]);
			SendClientMessageEx(i, -1, ""WHITE"-> %s", params);
		}
	}
	AccountData[playerid][pHotlineTime] = gettime() + 180;
	SendClientMessageEx(playerid, -1, ""GRAY"[911] "WHITE"Laporan Dari %s (%d) // Lokasi: %s // No Telpon: %s", GetRPName(playerid), playerid, GetLocation(x, y, z), AccountData[playerid][pPhone]);
	SendClientMessageEx(playerid, -1, ""WHITE"-> %s", params);
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengirim pesan kepada KEPOLISIAN!");
	return 1;
}
CMD:ems(playerid, params[])
{
	if(isnull(params))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/ems [message]");
	
	if(AccountData[playerid][pHotlineTime] >= gettime())
	{
		ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Mohon menunggu %d detik untuk mengirim hotline factions kembali!", AccountData[playerid][pHotlineTime] - gettime()));
		return 1;
	}

	foreach(new i : Player) {
		if(AccountData[i][pFaction] == 3 && AccountData[i][pDutyEms]) {
			SendClientMessageEx(i, -1, ""C_DOKTER"[EMS CALL CENTER]"WHITE" Laporan Dari %s (%d) // No Telpon: %s", GetRPName(playerid), playerid, AccountData[playerid][pPhone]);
			SendClientMessageEx(i, -1, ""WHITE"-> %s", params);
		}
	}
	AccountData[playerid][pHotlineTime] = gettime() + 180;
	SendClientMessageEx(playerid, -1, ""C_DOKTER"[EMS CALL CENTER]"WHITE" Laporan Dari %s (%d) // No Telpon: %s", GetRPName(playerid), playerid, AccountData[playerid][pPhone]);
	SendClientMessageEx(playerid, -1, ""WHITE"-> %s", params);
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengirim pesan kepada EMS!");
	return 1;
}*/

CMD:rst(playerid, params[])
{
	if(isnull(params))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/rst [message]");
	
	if(AccountData[playerid][pHotlineTime] >= gettime())
	{
		ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Mohon menunggu %d detik untuk mengirim hotline factions kembali!", AccountData[playerid][pHotlineTime] - gettime()));
		return 1;
	}

	foreach(new i : Player) {
		if(AccountData[i][pFaction] == 6 && AccountData[i][pDutyPedagang]) {
			SendClientMessageEx(i, -1, ""C_PEDAGANG"[RESTO CALL CENTER]"WHITE" Pesan Dari %s (%d) // No Telpon: %s", GetRPName(playerid), playerid, AccountData[playerid][pPhone]);
			SendClientMessageEx(i, -1, ""WHITE"-> %s", params);
		}
	}
	AccountData[playerid][pHotlineTime] = gettime() + 180;
	SendClientMessageEx(playerid, -1, ""C_PEDAGANG"[RESTO CALL CENTER]"WHITE" Pesan Dari %s (%d) // No Telpon: %s", GetRPName(playerid), playerid, AccountData[playerid][pPhone]);
	SendClientMessageEx(playerid, -1, ""WHITE"-> %s", params);
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengirim pesan kepada RESTO!");
	return 1;
}
CMD:mek(playerid, params[])
{
	if(isnull(params))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/mek [message]");
	
	if(AccountData[playerid][pHotlineTime] >= gettime())
	{
		ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Mohon menunggu %d detik untuk mengirim hotline factions kembali!", AccountData[playerid][pHotlineTime] - gettime()));
		return 1;
	}

	foreach(new i : Player) {
		if(AccountData[i][pFaction] == FACTION_BENGKEL && AccountData[i][pDutyBengkel]) {
			SendClientMessageEx(i, -1, ""C_BENGKEL"[MEKANIK CALL CENTER]"WHITE" Pesan Dari %s (%d) // No Telpon: %s", GetRPName(playerid), playerid, AccountData[playerid][pPhone]);
			SendClientMessageEx(i, -1, ""WHITE"-> %s", params);
		}
	}
	AccountData[playerid][pHotlineTime] = gettime() + 180;
	SendClientMessageEx(playerid, -1, ""C_BENGKEL"[MEKANIK CALL CENTER]"WHITE" Pesan Dari %s (%d) // No Telpon: %s", GetRPName(playerid), playerid, AccountData[playerid][pPhone]);
	SendClientMessageEx(playerid, -1, ""WHITE"-> %s", params);
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengirim pesan kepada BENGKEL!");
	return 1;
}

/*CMD:pemda(playerid, params[])
{
	if(isnull(params)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/pemda [message]");

	if(AccountData[playerid][pHotlineTime] >= gettime())
	{
		ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Mohon menunggu %d detik untuk mengirim hotline factions kembali!", AccountData[playerid][pHotlineTime] - gettime()));
		return 1;
	}

	foreach(new i : Player) {
		if(AccountData[i][pFaction] == FACTION_PEMERINTAH && AccountData[i][pDutyPemerintah]) {
			SendClientMessageEx(i, -1, ""SKYBLUE"[PEMERINTAH HOTLINE]"WHITE" Pesan Dari %s (%d) // No Telpon: %s", GetRPName(playerid), playerid, AccountData[playerid][pPhone]);
			SendClientMessageEx(i, -1, ""WHITE"-> %s", params);
		}
	}
	AccountData[playerid][pHotlineTime] = gettime() + 180;
	SendClientMessageEx(playerid, -1, ""SKYBLUE"[PEMERINTAH HOTLINE]"WHITE" Pesan Dari %s (%d) // No Telpon: %s", GetRPName(playerid), playerid, AccountData[playerid][pPhone]);
	SendClientMessageEx(playerid, -1, ""WHITE"-> %s", params);
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengirim pesan kepada Pemerintah!");
	return 1;
}*/

CMD:carry(playerid, params[])
{
	if(IsDragging[playerid] != INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang menggendong orang lain!");
	if(AccountData[playerid][pDraggedBy] != INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang digendong oleh orang lain!");
	if(IsPlayerInAnyVehicle(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus diluar dari kendaraan!");

	new otherid;
	if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/carry [name/playerid]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(IsPlayerInAnyVehicle(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut berada di dalam kendaraan!");
	if(!IsPlayerNearPlayer(playerid, otherid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan pemain tersebut!");
	if(otherid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat melakukan ini kepada diri sendiri!");

	foreach(new i : Player) if (IsPlayerConnected(i)) if (i != playerid)
	{
		if(IsDragging[i] == otherid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang digendong oleh orang lain!");
	}
	SendClientMessageEx(otherid, -1, "[i] %s meminta persetujuan carry. "YELLOW"'/accept carry'"WHITE" untuk menerima", ReturnName(playerid));
	SendClientMessageEx(playerid, -1, "[i] Anda meminta persetujuan carry pada %s. harap tunggu respon", ReturnName(otherid));
	AccountData[otherid][pDragOffer] = playerid;
	return 1;
}

CMD:uncarry(playerid, params[])
{
	new carryID = AccountData[playerid][pDraggedBy];
	if(carryID == INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak digendong oleh siapapun/saat diseret paksa tidak bisa uncarry!");
	if(AccountData[playerid][pCuffed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang diborgol!");
	if(IsDragging[carryID] == playerid)
	{
		TogglePlayerControllable(playerid, true);
		IsDragging[carryID] = INVALID_PLAYER_ID;
		AccountData[playerid][pDraggedBy] = INVALID_PLAYER_ID;
		
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda melepaskan gendongan paksa!");
		Warning(carryID, "%s melepaskan gendongan dari anda", ReturnName(playerid));

		if(GetPVarInt(carryID, "OnCarry")) {
			DeletePVar(carryID, "OnCarry");
		}
	}
	return 1;
}

alias:accept("acc")
CMD:accept(playerid, params[])
{
	static
		option[15],
		nextParams[125];
		
	if(isnull(params))
	{
		Syntax(playerid, "/accept [entinity] (taxi, carry, seat, workshop)");
		return 1;
	}
	
	if(sscanf(params, "s[15]S()[125]", option, nextParams))
	{
		Syntax(playerid, "/accept [entinity] (taxi, carry, seat, workshop)");
		return 1;
	}
	/*if(!strcmp(option, "buyveh", true))
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
		}
	}*/
	if(!strcmp(option, "carry", true))
	{
		new targetid = AccountData[playerid][pDragOffer];
		if(targetid == INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada permintaan carry untukmu.");

		IsDragging[targetid] = playerid;
		AccountData[playerid][pDragOffer] = INVALID_PLAYER_ID;
		AccountData[playerid][pDraggedBy] = targetid;
		SendRPMeAboveHead(targetid, "Memegang orang didekatnya dan mulai menyeret", X11_PLUM1);
		SendRPMeAboveHead(playerid, "Tergendong", X11_LIGHTGREEN);
		SendClientMessageEx(targetid, -1, "Anda sekarang menggendong %s", ReturnName(playerid));
		ShowTDN(playerid, NOTIFICATION_INFO, "Gunakan '"YELLOW"/uncarry"WHITE"' untuk melepaskan diri dari gendongan");
	}
	/*else if(!strcmp(option, "boxing", true))
	{
		new otherid;
		if(sscanf(nextParams, "d", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/accept boxing [boxing id]");
		if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
		if(AreaIsFull) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sedang ada yang menggunakan arena, harap tunggu hingga selesai!");
		if(!IsPlayerInRangeOfPoint(playerid, 100.0, 771.8782, -68.1927, 1000.6563)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di area boxing!");
		if(BoxingOffer[playerid] == otherid)
		{
			ResetPlayerWeapons(playerid);
			ResetPlayerWeapons(otherid);
			UpdateWeapons(playerid);
			UpdateWeapons(otherid);
			AreaIsFull = 1;
			DurringBoxing[playerid] = true;
			DurringBoxing[otherid] = true;
			BoxingOfferTime[playerid] = 0;
			SetPlayerFightingStyle(playerid, FIGHT_STYLE_BOXING);
			SetPlayerFightingStyle(otherid, FIGHT_STYLE_BOXING);
			SetPlayerPositionEx(playerid, 766.7020, -66.6718, 1001.5692, 179.7884, 3000);
			SetPlayerPositionEx(otherid, 766.6351, -70.8262, 1001.5692, 358.1788, 3000);
			SetPlayerSkin(playerid, 80);
			SetPlayerSkin(otherid, 81);

			SetPlayerHealth(playerid, 100.0);
			SetPlayerArmour(playerid, 0);
			SetPlayerHealth(otherid, 100.0);
			SetPlayerArmour(otherid, 0);
			foreach(new i : Player) if (IsPlayerConnected(i) && IsPlayerInRangeOfPoint(i, 100.0, 771.8782, -68.1927, 1000.6563))
			{
				GameTextForPlayer(i, sprintf("~r~%s~n~~w~vs~n~~b~%s", ReturnName(playerid), ReturnName(otherid)), 3000, 6);
			}
		}
	}*/
	else if(!strcmp(option, "seat", true))
	{
		new otherid = ChangeSeatWithPlayerID[playerid],
			vehicleid = ChangeSeatVehicleID[playerid];

		if(otherid == INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada yang meminta menukar posisi!");
		if(!IsPlayerInVehicle(otherid, vehicleid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus berada di kendaraan yang sama!");
		if(!IsPlayerNearPlayer(playerid, otherid, 5.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak berada di dekat anda!");

		IsPlayerChangeSeat[playerid] = true;
		IsPlayerChangeSeat[otherid] = true;
		SetTimerEx("OnPlayerChangeToDriver", 100, false, "d", otherid);
		SetTimerEx("OnPlayerChangeToPass", 100, false, "d", playerid);
	}
	else if(!strcmp(option, "taxi", true))
	{
		if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Anggota Transportasi District !");
		if(!AccountData[playerid][pDutyTrans]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang On Duty TRANS!");
		if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menerima panggilan saat pingsan!");
		if(!IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada didalam kendaraan Trans!");

		new otherid;
		if(sscanf(nextParams, "d", otherid)) return Syntax(playerid, "/accept taxi [client id]"); 
		if(!IsPlayerConnected(otherid)) return Error(playerid, "Pemain tersebut tidak terkoneksi ke server!");
		if(!AccountData[otherid][pTaxiOrder]) return Error(playerid, "Pemain tersebut tidak memesan taxi!");
		if(AdminVehicle{GetPlayerVehicleID(playerid)}) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini milik server administrator!");
	
		new vehicleid;
		if((vehicleid = Vehicle_Nearest2(playerid)) != -1)
		{
			if(PlayerVehicle[vehicleid][pVehFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan kendaraan milik Trans!");
			if(PlayerVehicle[vehicleid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
			SetPlayerRaceCheckpoint(playerid, 1, GetPVarFloat(otherid, "pX"), GetPVarFloat(otherid, "pY"), GetPVarFloat(otherid, "pZ"), 0.0, 0.0, 0.0, 4.0);
			AccountData[otherid][pTaxiOrder] = false;

			pMapCP[playerid] = true;
			
			////(playerid, GetPVarFloat(otherid, "pX"), GetPVarFloat(otherid, "pY"), GetPVarFloat(otherid, "pZ"), COLOR_BLUE);
			Info(playerid, "Anda menerima pesanan taxi "YELLOW"%s(%d)", ReturnName(otherid), otherid);
			Info(otherid, ""YELLOW"%s(%d)"WHITE" menerima pesanan taxi anda dan sedang dalam perjalanan.", ReturnName(playerid), playerid);
		}
	}
	else if(!strcmp(option, "workshop", true))
	{
		if(IsPlayerConnected(AccountData[playerid][pWsOffer]))
		{
            if(AccountData[playerid][pWsInvite] > -1)
			{
                AccountData[playerid][pWorkshop] = AccountData[playerid][pWsInvite];
				AccountData[playerid][pWorkshopRank] = 1;
				Info(playerid, "Anda telah menerima invite workshop dari %s", AccountData[AccountData[playerid][pWsOffer]][pName]);
				Info(AccountData[playerid][pWsOffer], "%s telah menerima invite workshop yang anda tawari", AccountData[playerid][pName]);
				AccountData[playerid][pWsInvite] = 0;
				AccountData[playerid][pWsOffer] = -1;
			}
			else
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid workshop id!");
				return 1;
			}
        }
        else
		{
            ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada player yang menawari anda!");
            return 1;
        }
	}
	else return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/accept [entinity] (buyveh, taxi, carry, workshop)");
	return 1;
}

CMD:helpbb(playerid, params[])
{
	if(!AccountData[playerid][IsLoggedIn])	
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu harus login untuk menggunakan ini");

	if(isnull(params))
	{
		ShowTDN(playerid, NOTIFICATION_SYNTAX, "/bb [name]~n~ play, ambil");
		return 1;
	}
	return 1;
}
CMD:takebb(playerid, params[])
{
	if(!AccountData[playerid][IsLoggedIn])
		return 0;
	
	if(Inventory_Count(playerid, "Boombox") < 1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki boombox");

	if(!GetPVarInt(playerid, "PlacedBB"))
	{
		SendClientMessageEx(playerid, -1, "{00ff00}[!]{ffffff}: Kamu tidak menaruh boombox sebelumnya untuk mengambil");
	}
	if(IsPlayerInRangeOfPoint(playerid, 3.0, GetPVarFloat(playerid, "BBX"), GetPVarFloat(playerid, "BBY"), GetPVarFloat(playerid, "BBZ")))
	{
		PickUpBoombox(playerid);
		SendRPMeAboveHead(playerid, "Mengambil boombox dari bawah dan menaruhnya kembali ke tempat semula", X11_PLUM1);
	}
	return 1;
}

CMD:bb(playerid, params[])
{
	if(!AccountData[playerid][IsLoggedIn])
		return 0;
	
	if(Inventory_Count(playerid, "Boombox") < 1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki boombox");
		
	if(!AccountData[playerid][pVip]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pengguna VIP!");

    if(GetPVarType(playerid, "PlacedBB"))
	{
		if(IsPlayerInRangeOfPoint(playerid, 3.0, GetPVarFloat(playerid, "BBX"), GetPVarFloat(playerid, "BBY"), GetPVarFloat(playerid, "BBZ")))
		{
			ShowPlayerDialog(playerid, DANN_BOOMBOX, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Boombox", "Matikan Boombox\nPutar Musik", "Select", "Cancel");
		}
		else
		{
	   		return ShowTDN(playerid, NOTIFICATION_ERROR, "~g~[!]~w~: Kamu tidak berada didekat boombox mu!");
		}
	}
	else
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak menaruh boombox sebelumnya!");
	}  
	return 1;
}

stock StopStream(playerid)
{
	DeletePVar(playerid, "pAudioStream");
    StopAudioStreamForPlayer(playerid);
}

stock PlayStream(playerid, url[], Float:posX = 0.0, Float:posY = 0.0, Float:posZ = 0.0, Float:distance = 50.0, usepos = 0)
{
	if(GetPVarType(playerid, "pAudioStream")) StopAudioStreamForPlayer(playerid);
	else SetPVarInt(playerid, "pAudioStream", 1);
    PlayAudioStreamForPlayer(playerid, url, posX, posY, posZ, distance, usepos);
}

stock PickUpBoombox(playerid)
{
    foreach(new i : Player)
	{
 		if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "BBArea")))
   		{
     		StopStream(i);
		}
	}
	ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
	DeletePVar(playerid, "BBArea");
	DestroyDynamicObject(GetPVarInt(playerid, "PlacedBB"));
	DestroyDynamic3DTextLabel(Text3D:GetPVarInt(playerid, "BBLabel"));
	DeletePVar(playerid, "PlacedBB"); DeletePVar(playerid, "BBLabel");
 	DeletePVar(playerid, "BBX"); DeletePVar(playerid, "BBY"); DeletePVar(playerid, "BBZ");
	DeletePVar(playerid, "BBInt");
	DeletePVar(playerid, "BBVW");
	DeletePVar(playerid, "BBStation");
	return 1;
}

/*CMD:elist(playerid, params[])
{
	if(AccountData[playerid][IsLoggedIn] == false) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus login untuk menggunakan ini");

	ShowPlayerDialog(playerid, DialogElist, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- List Animasi", "Elist\nEprop Anim\nInteraksi Anim", "Pilih", "Batal");
	return 1;
}*/

CMD:flist(playerid, params[])
{
	if(!SQL_IsCharacterLogged(playerid))
		return 0;

	new 
		countpd,
		countpemer,
		countems,
		countbengkel,
		countpdg,
		counttrans;

	foreach(new i : Player) if (IsPlayerConnected(i))
	{
		if(AccountData[i][pDutyPD]) countpd++;
		if(AccountData[i][pDutyPemerintah]) countpemer++;
		if(AccountData[i][pDutyEms]) countems++;
		if(AccountData[i][pDutyBengkel]) countbengkel++;
		if(AccountData[i][pDutyPedagang]) countpdg++;
		if(AccountData[i][pDutyTrans]) counttrans++;
	}

	ShowFlistTD(playerid, true);

	new polis[64], pemerintah[64], medis[64], trans[64], bengkel[64], pedagang[64];

	format(polis, sizeof(polis), "%d", countpd);
	PlayerTextDrawSetString(playerid, FlistTD[playerid][16], polis);
	PlayerTextDrawShow(playerid, FlistTD[playerid][16]);

	format(pemerintah, sizeof(pemerintah), "%d", countpemer);
	PlayerTextDrawSetString(playerid, FlistTD[playerid][17], pemerintah);
	PlayerTextDrawShow(playerid, FlistTD[playerid][17]);

	format(medis, sizeof(medis), "%d", countems);
	PlayerTextDrawSetString(playerid, FlistTD[playerid][18], medis);
	PlayerTextDrawShow(playerid, FlistTD[playerid][18]);

	format(trans, sizeof(trans), "%d", counttrans);
	PlayerTextDrawSetString(playerid, FlistTD[playerid][19], trans);
	PlayerTextDrawShow(playerid, FlistTD[playerid][19]);

	format(bengkel, sizeof(bengkel), "%d", countbengkel);
	PlayerTextDrawSetString(playerid, FlistTD[playerid][20], bengkel);
	PlayerTextDrawShow(playerid, FlistTD[playerid][20]);

	format(pedagang, sizeof(pedagang), "%d", countpdg);
	PlayerTextDrawSetString(playerid, FlistTD[playerid][21], pedagang);
	PlayerTextDrawShow(playerid, FlistTD[playerid][21]);

	Info(playerid, "Gunakan "YELLOW"/fhide "WHITE"untuk menutup Flist");
	return 1;
}

CMD:fhide(playerid, params[])
{
	if(!SQL_IsCharacterLogged(playerid))
		return 0;
	
	ShowFlistTD(playerid, false);
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menutup flist!");
	return 1;
}

ShowFlistTD(playerid, bool:chess7)
{
	if(chess7)
	{
		for(new i = 0; i < 22; i++) PlayerTextDrawShow(playerid, FlistTD[playerid][i]);
	}
	else
	{
		for(new i = 0; i < 22; i++) PlayerTextDrawHide(playerid, FlistTD[playerid][i]);
	}
	return 1;
}

CMD:fixbug(playerid, params[])
{
	if(!AccountData[playerid][IsLoggedIn])
		return false;
	
	Dialog_Show(playerid, DialogFixMe, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Fix Me", "Keluh Kesah\nBeda Visual\nKarakter Stuck Object\nKarakter Freezing", "Pilih", "Batal");
	return 1;
}

Dialog:DialogFixMe(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	{
		switch(listitem)
		{
			case 0:
			{
				if(AccountData[playerid][pInRusun] != -1)
				{
					SetPlayerInteriorEx(playerid, 1);
					SetPlayerVirtualWorldEx(playerid, AccountData[playerid][pInRusun]);
					SetPlayerPositionEx(playerid, 244.2521, 304.9150, 999.1484, 268.6741, 2500);
				}

				else if(AccountData[playerid][pInHouse] != -1)
				{
					SetPlayerInteriorEx(playerid, HouseData[AccountData[playerid][pInHouse]][hsInt]);
					SetPlayerVirtualWorldEx(playerid, AccountData[playerid][pInHouse]);
					SetPlayerPositionEx(playerid, HouseData[AccountData[playerid][pInHouse]][hsIntPos][0], HouseData[AccountData[playerid][pInHouse]][hsIntPos][1], HouseData[AccountData[playerid][pInHouse]][hsIntPos][2], HouseData[AccountData[playerid][pInHouse]][hsIntPos][3], 2500);
				}

				else if(AccountData[playerid][pInDoor] != -1)
				{
					SetPlayerInteriorEx(playerid, DoorData[AccountData[playerid][pInDoor]][dIntint]);
					SetPlayerVirtualWorldEx(playerid, DoorData[AccountData[playerid][pInDoor]][dIntvw]);
					SetPlayerPositionEx(playerid, DoorData[AccountData[playerid][pInDoor]][dIntposX], DoorData[AccountData[playerid][pInDoor]][dIntposY], DoorData[AccountData[playerid][pInDoor]][dIntposZ], DoorData[AccountData[playerid][pInDoor]][dIntposA], 2500);
				}

				else if(AccountData[playerid][pInFamily] != -1)
				{
					SetPlayerInteriorEx(playerid, FamData[AccountData[playerid][pInFamily]][famInterior]);
					SetPlayerVirtualWorldEx(playerid, AccountData[playerid][pInFamily]);
					SetPlayerPositionEx(playerid, FamData[AccountData[playerid][pInFamily]][famIntPos][0], FamData[AccountData[playerid][pInFamily]][famIntPos][1], FamData[AccountData[playerid][pInFamily]][famIntPos][2], FamData[AccountData[playerid][pInFamily]][famIntPos][3], 2500);
				}

				else
				{
					SetPlayerVirtualWorldEx(playerid, 0);
					SetPlayerInteriorEx(playerid, 0);
				}
				ShowTDN(playerid, NOTIFICATION_INFO, "Sistem kami berhasil membantu anda mengatasi masalah Bug Visu");
			}
			case 1:
			{
				new Float: POS[3];
				GetPlayerPos(playerid, POS[0], POS[1], POS[2]);
				SetPlayerPos(playerid, POS[0], POS[1], POS[2] + 9.0);
				if(IsPlayerInAnyVehicle(playerid)) RemovePlayerFromVehicle(playerid);

				ShowTDN(playerid, NOTIFICATION_INFO, "Sistem kami berhasil membantu anda mengatasi masalah Karakter stuck object");
			}
			case 2:
			{
				AccountData[playerid][pFreeze] = 0;
                TogglePlayerControllable(playerid, 1);

				ShowTDN(playerid, NOTIFICATION_INFO, "Sistem kami berhasil membantu anda mengatasi masalah Karakter Freezing");
			}
		}
	}
	return 1;
}

CMD:help(playerid, params[])
{
	if(!AccountData[playerid][IsLoggedIn])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus masuk kedalam server!");
	
	Dialog_Show(playerid, DialogHelp, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Bantuan", "Jenis Bantuan\tKeterangan\
	\nPerintah Dasar\tBerisi beberapa CMD dasar untuk player\
	\n"GRAY"Perintah Kendaraan\t"GRAY"Berisi beberapa CMD seputar kendaraan\
	\nPerintah Roleplay\tBerisi beberapa CMD untuk melengkapi roleplay\
	\n"GRAY"Petunjuk Dasar\tBerisi beberapa petunjuk dasar District \
	\nPetunjuk Lapar Haus\tBerisi beberapa petunjuk tentang kebutuhan karakter", "Pilih", "Batal");	
	return 1;
}

Dialog:DialogHelp(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Perintah Dasar",
				"Jenis Perintah\tKeterangan\
				\n"GRAY"/settings\t"GRAY"Untuk mensettings toggle server\
				\n/drag\tMenggendong pemain lain\
				\n"GRAY"/gum\t"GRAY"Memberikan uang haram kepada pemain lain\
				\n/whisper\tBerbisik kepada orang di sekitar\
				\n"GRAY"/saving\t"GRAY"Menyimpan semua database akun anda ke pusat\
				\n/qa\tUntuk menjawab quiz dari admin kota\
				\n"GRAY"/medis\t"GRAY"Untuk menggunakan Dokter Lokal jika tidak ada EMS Duty di kota\
				\n/fixme\tUntuk Fix Request bug yang terjadi kepada administrator\
				\n"GRAY"/setrender\t"GRAY"Mengatur batasan/jarak padang object server\
				\n/admins\tMelihat daftar Administrator Online di kota\
				\n"GRAY"/elist\t"GRAY"Untuk melihat daftar animasi yang tersedia di server\
				\n/flist\tUntuk melihat daftar Faction On Duty\
				\n"GRAY"/sm\t"GRAY"Untuk melihat status Mendung untuk kegiatan roleplay\
				\n/e\tMelakukan animasi\
				\n"GRAY"/eprop\t"GRAY"Melakukan animasi properti\
				\n/einter\tMelakukan animasi interaksi kepada pemain lain\
				\n"GRAY"/ask\t"GRAY"Bertanya tentang fitur/apapun yang ada di server\
				\n/report\tUntuk melaporkan sesuatu yang terjadi di server kepada admin", "Close", "");
			}
			case 1:
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District "WHITE" - Perintah Kendaraan",
				"Jenis Perintah\tKeterangan\
				\n/sellveh\tMenjual kendaraan kepada pemain lain\
				\n"GRAY"/en\t"GRAY"Menyalakan/Mematikan mesin kendaraan secara manual\
				\n/myv\tMelihat daftar kendaraan milik anda\
				\n"GRAY"/windows\t"GRAY"Membuka jendela kendaraan\
				\n/sl\tMengatur Limit speed kendaraan", "Close", "");
			}
			case 2:
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District "WHITE" - Perintah Roleplay",
				"Jenis Perintah\tKeterangan\
				\n/ado\tMenerangkan situasi dengan label text 3D\
				\n"GRAY"/me\t"GRAY"Menerangkan aktivitas rp dengan memunculkan label diatas kepala\
				\n/do\tMenerangkan suasana rp dengan memunculkan label diatas kepala\
				\n"GRAY"/pm\t"GRAY"Private Message sebagai mana namanya\
				\n/w\tUntuk berbisik kepada pemain lain\
				\n"GRAY"/b\t"GRAY"Lokal Chat OOC\
				\n/o\tGlobal Chat OOC", "Close", "");
			}
			case 3:
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District "WHITE" - Petunjuk Dasar",
				"Jenis Perintah\tKeterangan\
				\n/sv\tUntuk mengganti mode jarak suara\
				\n"GRAY"/e (nama animasi)\t"GRAY"Untuk memainkan animasi\
				\n/eprop (nama animasi properti)\tUntuk memainkan animasi property\
				\n"GRAY"/einter (nama animasi interaksi)\t"GRAY"Untuk memainkan animasi interaksi\
				\nTombol N\tUntuk membuka Radial Menu\
				\n"GRAY"Jongkok + Tombol ALT\t"GRAY"Untuk mengambil item yang berada ditanah\
				\nTombol F\tKeluar masuk interior", "Close", "");
			}
			case 4:
			{
				ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District "WHITE" - Petunjuk Lapar Haus",
				""WHITE"Dikarenakan "TCRP"District "WHITE" merupakan server dengan mode Roleplay, sudah pasti karakter anda\
				\ndapat merasakan lapar dan haus hingga stress.\
				\nBagaimana cara membedakannya dan menemukan dilayar monitor anda?\
				\n\nSecara umum ketiganya terletak dibawah kiri monitor anda,\
				\nLapar ~> Ditandai dengan bar berwarna "YELLOW"Kuning"WHITE" yang terdapat icon makanan\
				\nHaus ~> Ditandai dengan bar berwarna "SKYBLUE"Biru.\
				\n"WHITE"Stress ~> Ditandai dengan bar berwarna "RED"Merah.\
				\n\n"WHITE"Anda harus menggunakan item makanan & minuman untuk mengisi kebutuhan lapar & haus,\
				\napabila "ORANGE"kosong"WHITE" sama sekali maka karakter anda akan pingsan otomatis. Jumlah pada bar stress\
				\nsendiri dirancang cukup unik dimana anda justru mencegahnya penuh, apabila stress mencapai bar tertinggi\
				\nmaka karakter anda akan mengalami "ORANGE"pusing"WHITE" dan layar anda akan ke ungu-unguan.\
				\nUntuk menurunkan stress anda dapat pergi ke "ORANGE"Bahamas"WHITE" atau "ORANGE"Carnaval"WHITE" atau konsumsi marijuana jika\n\
				\nanda memilikinya ataupun mengkonsumsi Alprazolam.", "Close", "");
			}
		}
	}
	return 1;
}

CMD:stopsmoke(playerid, params[])
{
	if(!IsPlayerSmoking[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang tidak merokok");

	ApplyAnimationEx(playerid, "GRENADE", "WEAPON_throw", 4.1, 0, 0, 0, 0, 0, 1);
	IsPlayerSmoking[playerid] = false;
	CountSmoking[playerid] = 0;
	SendRPMeAboveHead(playerid, "Membuang puntung rokok ke tanah", X11_PLUM1);
	return 1;
}

CMD:saving(playerid, params[])
{
	if(IsPlayerInEvent(playerid))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang mengikuti event!");

	if(AccountData[playerid][IsLoggedIn] == false)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu belum login!");
		
	UpdatePlayerData(playerid);
	ShowTDN(playerid, NOTIFICATION_INFO, "Successfully updates your account data to "TCRP"District  Database");
	return 1;
}

CMD:savedatabase(playerid, params[])
{
	foreach(new i : Player)
	{
		UpdatePlayerData(i);
		SendClientMessageToAllEx(-1, "{C6E2FF}[AdmCmd]{FF0000} %s {C6E2FF}Successfully membackup semua account pemain yang online ke {FF9999}District  Database", AccountData[playerid][pAdminname]);
	}
	return 1;
}

CMD:mypos(playerid, params[])
{
	new int, Float:px,Float:py,Float:pz, Float:a;
	GetPlayerPos(playerid, px, py, pz);
	GetPlayerFacingAngle(playerid, a);
	int = GetPlayerInterior(playerid);
	new MapZone:zone = GetPlayerMapZone(playerid);
	new name[MAX_MAP_ZONE_NAME];
	GetMapZoneName(zone, name);
	SendClientMessageEx(playerid, COLOR_WHITE, "Lokasi Anda Saat Ini: %s (%0.3f, %0.3f, %0.3f, %0.3f) Int = %d", name, px, py, pz, a, int);
	return 1;
}

CMD:health(playerid, params[])
{
	new string[400];
	new hh = AccountData[playerid][pHead];
	new hp = AccountData[playerid][pPerut];
	new htk = AccountData[playerid][pRHand];
	new htka = AccountData[playerid][pLHand];
	new hkk = AccountData[playerid][pRFoot];
	new hkka = AccountData[playerid][pLFoot];
	format(string, sizeof string, "Bagian Tubuh\tKondisi\n");
	format(string, sizeof string, "%s "WHITE"Kepala\t%d.0%\n", string, hh);
	format(string, sizeof string, "%s "GRAY"Perut\t%d.0%\n", string, hp);
	format(string, sizeof string, "%s "WHITE"Lengan Kanan\t%d.0%\n", string, htk);
	format(string, sizeof string, "%s "GRAY"Lengan Kiri\t%d.0%\n", string, htka);
	format(string, sizeof string, "%s "WHITE"Kaki Kanan\t%d.0%\n", string, hkk);
	format(string, sizeof string, "%s "GRAY"Kaki Kiri\t%d.0%\n", string, hkka);
	ShowPlayerDialog(playerid, DIALOG_HEALTH, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District "WHITE" - Kesehatan", string, "Tutup", "");
    return 1;
}

CMD:cursor(playerid, params[])
{
	SelectTextDraw(playerid, COLOR_BLUE);
	return 1;
}

CMD:hktp(playerid, params[])
{
	for(new i = 0; i < 61; i ++)
	{
		PlayerTextDrawHide(playerid, ktpTextdraws[playerid][i]);
	}
	CancelSelectTextDraw(playerid);
	return 1;
}

alias:hidekta("hkta")
CMD:hidekta(playerid, params[])
{
	for(new i = 0; i < 41; i ++)
	{
		PlayerTextDrawHide(playerid, KTAtextdraws[playerid][i]);
	}
	return 1;
}

CMD:pay(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid)) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus terkoneksi ke server!");
    
    new 
        money,
        otherid
    ;
    if(sscanf(params, "ud", otherid, money)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/pay [name/playerid] [jumlah]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!IsPlayerNearPlayer(playerid, otherid, 2.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Player tersebut tidak didekat anda!");
    if(otherid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengirim kepada diri sendiri!");
    if(AccountData[playerid][pMoney] < money) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki uang sebanyak itu!");
    if(money < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");
    if(money > 1000000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Max jumlah transaksi 1juta!");
    if(gettime() < AccountData[playerid][pLastPay] + 60) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tunggu 1 menit untuk mengunakan pay kembali!");

    GiveMoney(otherid, money);
    TakeMoney(playerid, money);

    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil memberikan uang %s kepada %s", FormatMoney(money), ReturnName(otherid)));
    ShowTDN(otherid, NOTIFICATION_INFO, sprintf("Anda menerima uang %s", FormatMoney(money)));

    foreach(new i : Player) if (IsPlayerConnected(i)) if (AccountData[i][pAdmin] > 0 || AccountData[i][pTheStars] > 0)
    {
        if(money > 5000)
        {
            SendClientMessageEx(i, -1, ""YELLOW"[RTM Alert]: %s (%d) memberikan %s kepada %s (%d)", AccountData[playerid][pName], playerid, FormatMoney(money), AccountData[otherid][pName], otherid);
        }
        else 
        {
            SendClientMessageEx(i, -1, ""YELLOW"[Pay]: %s (%d) memberikan %s kepada %s (%d)", AccountData[playerid][pName], playerid, FormatMoney(money), AccountData[otherid][pName], otherid);
        }
    }

    new frmxt[255];
    format(frmxt, sizeof(frmxt), "Memberikan uang kepada %s sebesar $%d", AccountData[otherid][pName], money);
    AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], frmxt, money);
    AccountData[playerid][pLastPay] = gettime();

    if(money > 5000)
    {
        new d_msg[512];
        format(d_msg, sizeof(d_msg), "💰 **RTM SECURITY ALERT**\n\n**Pengirim:** %s (%s)\n**Penerima:** %s (%s)\n**Jumlah:** %s\n**Status:** Transaksi di atas $5.000", 
            AccountData[playerid][pName], AccountData[playerid][pUCP], 
            AccountData[otherid][pName], AccountData[otherid][pUCP], 
            FormatMoney(money)
        );
        
        SendDiscordWebhook(WEBHOOK_PAY, d_msg);
    }

    return 1;
}

CMD:gum(playerid, params[])
{
	if(!SQL_IsCharacterLogged(playerid))
		return 0;
	
	new otherid, value;
	if(sscanf(params, "ud", otherid, value)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gun [name/playerid] [jumlah]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!IsPlayerNearPlayer(playerid, otherid, 2.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus dekat dengan pemain tersebut!");
	if(otherid == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengirim ke diri sendiri!");
	if(value < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");
	if(value > AccountData[playerid][pRedMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki uang merah sebanyak itu!");
	
	AccountData[otherid][pRedMoney] += value;
	AccountData[playerid][pRedMoney] -= value;

	ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil memberikan ~g~%s~w~ uang merah", FormatMoney(value)));
	ShowTDN(otherid, NOTIFICATION_INFO, sprintf("Anda menerima uang merah sebesar ~g~%s", FormatMoney(value)));

	new tss[255];
	mysql_format(g_SQL, tss, sizeof(tss), "UPDATE `player_characters` SET `Char_RedMoney` = `Char_RedMoney` + %d WHERE `pID`=%d", value, AccountData[otherid][pID]);
	mysql_tquery(g_SQL, tss);
	
	mysql_format(g_SQL, tss, sizeof(tss), "UPDATE `player_characters` SET `Char_RedMoney` = `Char_RedMoney` - %d WHERE `pID`=%d", value, AccountData[playerid][pID]);
	mysql_tquery(g_SQL, tss);
	return 1;
}

CMD:stats(playerid, params[])
{
	Player_Stats(playerid, playerid);
	return 1;
}

CMD:ado(playerid, params[])
{
	new Float:x, Float:y, Float:z;

	if (isnull(params))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/ado [text] 'off' untuk menghapus text");
	
	if (strlen(params) > 128)	
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Max text can only maximmum 128 characters!");
	
	if (!strcmp(params, "off", true))
	{
		if (!AccountData[playerid][pAdoActive])
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum membuat ADO sebelumnya!");
		
		if (IsValidDynamic3DTextLabel(AccountData[playerid][pAdoTag]))
			DestroyDynamic3DTextLabel(AccountData[playerid][pAdoTag]);
		
		AccountData[playerid][pAdoTag] = Text3D: INVALID_STREAMER_ID;
		AccountData[playerid][pAdoActive] = false;
		ShowTDN(playerid, NOTIFICATION_SUKSES, "Teks berhasil dihapus");
		return 1;
	}

	new name[MAX_PLAYERS + 1];

	if (AccountData[playerid][pMaskOn]) format(name, sizeof(name), "Strangers_#%d", AccountData[playerid][pMaskID]);
	else format(name, sizeof(name), "%s", ReturnName(playerid));

	FixText(params);
	GetPlayerPos(playerid, x, y, z);

	Info(playerid, "ADO: %s", params);
	AccountData[playerid][pAdoActive] = true;

	if (IsValidDynamic3DTextLabel(AccountData[playerid][pAdoTag])) UpdateDynamic3DTextLabelText(AccountData[playerid][pAdoTag], COLOR_CLIENT, sprintf("(( %s ))\n>> %s[%d] <<", params, name, playerid));
	else AccountData[playerid][pAdoTag] = CreateDynamic3DTextLabel(sprintf("(( %s ))\n>> %s[%d] <<", params, name, playerid), COLOR_CLIENT, x, y, z, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
	return 1;
}

CMD:apm(playerid, params[])
{
	static 
		userid,
		text[128]
	;
	if(sscanf(params, "us[128]", userid, text))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/apm [playerid/Name] [pesan]");
	
	if(CheckAdmin(playerid, 2))
		return PermissionError(playerid);
	
	if(userid == INVALID_PLAYER_ID || !IsPlayerConnected(userid))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke dalam server!");
	
	SendClientMessageEx(userid, X11_YELLOW, "((PM From "RED"Admin"WHITE": %s))", text);
	SendClientMessageEx(playerid,  X11_YELLOW, "((PM To %s (%d): %s))", ReturnName(userid), userid, text);
	return 1;
}

CMD:pm(playerid, params[])
{
    new msg[512], userid;

    // Parsing parameter: /pm [playerid/nama] [pesan]
    if(sscanf(params, "us[512]", userid, msg))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/pm [playerid/Name] [pesan]");

    // Cek target valid dulu
    if(userid == INVALID_PLAYER_ID || !IsPlayerConnected(userid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke dalam server!");

    // Cek sender valid
    if(!IsPlayerConnected(playerid) || !AccountData[playerid][IsLoggedIn])
        return ShowTDN(playerid, NOTIFICATION_ERROR , "Anda harus terkoneksi ke dalam server!");
    
    // Cek toggle PM pengirim
    if(!AccountData[playerid][pTogPM])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengaktifkan Private Message terlebih dahulu y'/settings'");

    // Cek admin duty
    if(AccountData[userid][pAdminDuty])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengirim PM kepada admin yang sedang On Duty!");
    
    // Cek kirim ke diri sendiri
    if(userid == playerid)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengirim PM kepada diri sendiri!");

    PlayerPlaySound(playerid, 1085, 0, 0, 0);

    // Kirim PM
    if(AccountData[userid][pTogPM])
    {
        if(strlen(msg) > 64) 
        {
            // Kirim ke target
            SendClientMessageEx(userid, X11_YELLOW, "((PM From %s (%d): %.64s...", GetRPName(playerid), playerid, msg);
            SendClientMessageEx(userid, X11_YELLOW, "... %s))", msg[64]); // kirim sisa pesan mulai index 64

            // Kirim ke pengirim
            SendClientMessageEx(playerid, X11_YELLOW, "((PM To %s (%d): %.64s...", GetRPName(userid), userid, msg);
            SendClientMessageEx(playerid, X11_YELLOW, "... %s))", msg[64]); // kirim sisa pesan mulai index 64
        } 
        else 
        {
            // Pesan pendek
            SendClientMessageEx(playerid, X11_YELLOW, "((PM To %s (%d): %s))", GetRPName(userid), userid, msg);
            SendClientMessageEx(userid, X11_YELLOW, "((PM From %s (%d): %s))", GetRPName(playerid), playerid, msg);
        }
    }
    else ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak mengaktifkan Private Message!");

    // Kirim ke admin spy
    foreach(new i : Player) if (IsPlayerConnected(i) && SQL_IsCharacterLogged(i))
    {
        if(AccountData[i][pAdmin] >= 1 && AccountData[i][pTogSpy])
        {
            if(strlen(msg) > 64)
            {
                SendClientMessageEx(i, X11_YELLOW, "((PM From %s(%d) To %s(%d)): %.64s...", GetRPName(playerid), playerid, GetRPName(userid), userid, msg);
                SendClientMessageEx(i, X11_YELLOW, "... %s))", msg[64]);
            }
            else
            {
                SendClientMessageEx(i, X11_YELLOW, "((PM From %s(%d) To %s(%d)): %s)", GetRPName(playerid), playerid, GetRPName(userid), userid, msg);
            }
        }
    }
    return 1;
}

CMD:w(playerid, params[])
{
	new strings[128], otherid;
	if(sscanf(params, "us[128]", otherid, strings))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/w(hisper) [playerid/Name] [pesan]");
	
	if(!IsPlayerConnected(otherid))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi kedalam server!");
	
	if(otherid == playerid)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengirim ke diri sendiri!");

	if(otherid == INVALID_PLAYER_ID)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi kedalam server!");
	
	if(!NearPlayer(playerid, otherid, 3.0))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan pemain tersebut!");
	
	if(strlen(strings) > 64)
	{
		SendClientMessageEx(otherid, -1, "{7AA6B6}((Whisper From %s (%d): %.64s...", GetRPName(playerid), playerid, strings);
		SendClientMessageEx(otherid, -1, "{7AA6B6}...%s))", strings[64]);

		SendClientMessageEx(playerid, -1, "{7AA6B6}((Whisper To %s (%d): %.64s...", GetRPName(otherid), otherid, strings);
		SendClientMessageEx(playerid, -1, "{7AA6B6}...%s))", strings[64]);
		SendRPMeAboveHead(playerid, "Berbisik kepada orang didekatnya", X11_PLUM1);
	}
	else 
	{
		SendClientMessageEx(playerid, -1, "{7AA6B6}((Whisper To %s (%d): %s))", GetRPName(otherid), otherid, strings);
		SendClientMessageEx(otherid, -1, "{7AA6B6}((Whisper From %s (%d): %s))", GetRPName(playerid), playerid, strings);
		SendRPMeAboveHead(playerid, "Berbisik kepada orang didekatnya", X11_PLUM1);
	}

	foreach(new i : Player) if (IsPlayerConnected(i) && SQL_IsCharacterLogged(i))
	{
		if(AccountData[i][pAdmin] >= 1 && AccountData[i][pTogSpy])
		{
			if(strlen(strings) > 64)
			{
				SendClientMessageEx(i, -1, "{7AA6B6}((Whisper From %s(%d) To %s(%d)): %.64s...", GetRPName(playerid), playerid, GetRPName(otherid), otherid, strings);
				SendClientMessageEx(i, -1, "{7AA6B6}... %s)", strings[64]);
			}
			else
			{
				SendClientMessageEx(i, -1, "{7AA6B6}((Whisper From %s(%d) To %s(%d)): %s)", GetRPName(playerid), playerid, GetRPName(otherid), otherid, strings);
			}
		}
	}
	return 1;
}

CMD:b(playerid, params[])
{
	if(!AccountData[playerid][IsLoggedIn])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus masuk kedalam server!");
	
	if(isnull(params))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/b [local OOC]");
	
	if(AccountData[playerid][pAdminDuty])
	{
		if(strlen(params) > 64)
		{
			SendNearbyMessage(playerid, 20.0, -1, ""WHITE"[L] "YELLOW"%s "WHITE"| %s [%d]: (( %.64s ..", GetStaffRank(playerid), GetAdminName(playerid), playerid, params);
			SendNearbyMessage(playerid, 20.0, -1, ""WHITE".. %s ))", params[64]);
		}
		else
		{
			SendNearbyMessage(playerid, 20.0, -1, ""WHITE"[L] "YELLOW"%s "WHITE"| %s [%d]: (( %s ))", GetStaffRank(playerid), GetUCPName(playerid), playerid, params);
		}
	}
	else 
	{
		if(strlen(params) > 64)
		{
			SendNearbyMessage(playerid, 20.0, -1, ""WHITE"[L] %s"WHITE" | %s [%d]: (( %.64s..", GetPlayerLevelName(playerid), GetUCPName(playerid), playerid, params);
			SendNearbyMessage(playerid, 20.0, -1, ""WHITE".. %s ))", params[64]);
		}
		else 
		{
			SendNearbyMessage(playerid, 20.0, -1, ""WHITE"[L] %s"WHITE" | %s [%d]: (( %s ))", GetPlayerLevelName(playerid), GetUCPName(playerid), playerid, params);
		}
	}
	return 1;
}

alias:clearchat("cc")
CMD:clearchat(playerid, params[])
{
	ClearAllChat(playerid);
	return 1;
}

CMD:gps(playerid, params[])
{
	if(BusIndex[playerid] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang bekerja sebagai supir bus!");
	if(DurringSweeping[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang bekerja sebagai pembersih jalan!");
	//if(PlayerKargoVars[playerid][KargoStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang bekerja sebagai Supir Kargo!");

	if(AccountData[playerid][pFaction] == FACTION_EMS && AccountData[playerid][pDutyEms]) {
		Dialog_Show(playerid, GpsMenu, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Menu Gps",
		"Lokasi GPS\n"GRAY"Signal Emergency (EMS)", "Pilih", "Batal");
	} else {
		ShowPlayerDialog(playerid, LokasiGps, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Lokasi",
		"Lokasi Umum\
		\n"GRAY"Lokasi Pekerjaan\
		\nLokasi Hobi\
		\n"GRAY"Lokasi Warung\
		\nATM Kota\
		\n"GRAY"Garasi Umum\
		\nTong Sampah Kota\
		\nPom Bensin District \
		\n"GRAY"Bengkel Modshop\
		\nRumah Saya\
		\nRumah Tersedia\
		\nWorkshop\
		\n"RED"(Disable Checkpoint)\
		\n"RED"(Disable Shareloc)", "Pilih", "Batal");
	}
	return 1;
}

CMD:fixveh(playerid, params[])
{
    new vehicleid;
    if(sscanf(params, "d", vehicleid)) 
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/fixveh [vehicle id]");

    if(!IsValidVehicle(vehicleid)) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Kendaraan tidak valid!");

    new index = Vehicle_ReturnID(vehicleid);
    if(index == RETURN_INVALID_VEHICLE_ID) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tidak ditemukan!");

    if(PlayerVehicle[index][pVehOwnerID] != AccountData[playerid][pID]) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");

    if(AccountData[playerid][pMoney] < 5000)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup untuk memperbaiki kendaraan ($5.000)!");

    AccountData[playerid][ActivityTime] = 1;
    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMPERBAIKI KENDARAAN");
    ShowProgressBar(playerid);

    isFixingVehicle[playerid] = 1; 
    FixVehicleTarget[playerid] = vehicleid;
    AccountData[playerid][FixVehTimer] = SetTimerEx("UsingFixVehicle", 1000, true, "i", playerid);

    ShowTDN(playerid, NOTIFICATION_INFO, "Anda mulai memperbaiki kendaraan... tunggu 60 detik.");

    return 1;
}

// ===== FORWARD & PUBLIC
forward UsingFixVehicle(playerid);
public UsingFixVehicle(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(AccountData[playerid][FixVehTimer]);
        AccountData[playerid][FixVehTimer] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        isFixingVehicle[playerid] = 0;
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 60) 
    {
        KillTimer(AccountData[playerid][FixVehTimer]);
        AccountData[playerid][FixVehTimer] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        isFixingVehicle[playerid] = 0;

        new vehicleid = FixVehicleTarget[playerid];
        if(IsValidVehicle(vehicleid))
        {
            new index = Vehicle_ReturnID(vehicleid);
            if(index != RETURN_INVALID_VEHICLE_ID)
            {
                ValidRepairVehicle(vehicleid);

                if(PlayerVehicle[index][pVehEngineUpgrade] == 1)
                    SetValidVehicleHealth(vehicleid, 2000);
                else
                    SetValidVehicleHealth(vehicleid, 1000);

                if(PlayerVehicle[index][pVehBodyUpgrade] == 3)
                    PlayerVehicle[index][pVehBodyRepair] = 1000.0;

                TakeMoney(playerid, 5000);
                ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Kendaraan [VID: %d] [%s] berhasil diperbaiki! Biaya: $5.000", vehicleid, GetVehicleName(vehicleid)));
            }
        }
    }
    else
    {
        AccountData[playerid][ActivityTime]++;
        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110.0 / 60.0;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}


CMD:fcrash(playerid, params[])
{
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Crasher.luac", ReturnName(playerid), playerid);
	SendStaffMessage(X11_TOMATO, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Crasher.luac", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

CMD:xgun(playerid, params[])
{
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan /xgun", ReturnName(playerid), playerid);
	SendStaffMessage(X11_TOMATO, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan /xgun", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

CMD:autowalk(playerid, params[])
{
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Autowalk.luac", ReturnName(playerid), playerid);
	SendStaffMessage(X11_TOMATO, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Autowalk.luac", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

CMD:aotot(playerid, params[])
{
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan aotot.luac", ReturnName(playerid), playerid);
	SendStaffMessage(X11_TOMATO, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan aotot.luac", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

CMD:pinmenu(playerid, params[])
{
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan pin menu.luac", ReturnName(playerid), playerid);
	SendStaffMessage(X11_TOMATO, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan pin menu.luac", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

CMD:sion(playerid, params[])
{
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan pin menu.luac", ReturnName(playerid), playerid);
	SendStaffMessage(X11_TOMATO, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan pin menu.luac", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

CMD:duplikat(playerid, params[])
{
	SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan pin menu.luac", ReturnName(playerid), playerid);
	SendStaffMessage(X11_TOMATO, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan pin menu.luac", ReturnName(playerid), playerid);
	KickEx(playerid);
	return 1;
}

