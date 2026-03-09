#include <YSI\y_hooks>

Dialog:eventWeapon(playerid, response, listitem, inputtext[])
{
	if(response) {
		SetPVarInt(playerid, "selectWeapon", listitem);
		Dialog_Show(playerid, editWeaponId, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Weapon ID", "Masukkan Weapon ID:", "Set", "Back");
	}
	return 1;
}

Dialog:editWeaponId(playerid, response, listitem, inputtext[])
{
	if(response) {
		new id = GetPVarInt(playerid, "selectWeapon");

		if(strval(inputtext) <= 0 || strval(inputtext) > 46 || (strval(inputtext) >= 19 && strval(inputtext) <= 21))
			return Dialog_Show(playerid, editWeaponId, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Weapon ID", "You have specified an invalid weapon!\n\nInsert Weapon ID:", "Set", "Back");

		EventData[eventWeapons][id] = strval(inputtext);
		Dialog_Show(playerid, editWeaponAmmo, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Weapon Ammo", "Insert the ammo for %s:", "Set", "Back", ReturnWeaponName(EventData[eventWeapons][id]));
	}
	else callcmd::event(playerid, "weapon");
	return 1;
}

Dialog:editWeaponAmmo(playerid, response, listitem, inputtext[])
{
	if(response) {
		new id = GetPVarInt(playerid, "selectWeapon");

		if(strval(inputtext) < 1 || strval(inputtext) > 1000)
			return Dialog_Show(playerid, editWeaponId, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Weapon ID", "You have specified an invalid weapon ammo, 1 - 1,000!\n\nInsert the ammo for %s:", "Set", "Back", EventData[eventWeapons][id]);

		EventData[eventAmmo][id] = strval(inputtext);
		DeletePVar(playerid, "selectWeapon");

		callcmd::event(playerid, "weapon");
	}
	else Dialog_Show(playerid, editWeaponId, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Weapon ID", "Insert Weapon ID:", "Set", "Back");
	return 1;
}

DialogTDMShow(playerid)
{
	new 
		list[1046],
		status1[128],
		status2[128];
	
	if(EventData[eventSpawnX][0] != 0.0 || EventData[eventSpawnY][0] != 0.0 || EventData[eventSpawnZ][0] != 0.0)
	{
		status1 = ""GREEN"Assigned";
	}
	else status1 = ""RED"Unassigned";

	if(EventData[eventSpawnX][1] != 0.0 || EventData[eventSpawnY][1] != 0.0 || EventData[eventSpawnZ][1] != 0.0)
	{
		status2 = ""GREEN"Assigned";
	}
	else status2 = ""RED"Unassigned";

	format(list, sizeof(list), "Implementation\tStatus\n");
    format(list, sizeof(list), "%sRed Team Skin\t%d\n", list, EventData[eventSkin][0]);
    format(list, sizeof(list), "%sRed Team spawn point\t%s\n", list, status1);
    format(list, sizeof(list), "%sBlue Team Skin\t%d\n", list, EventData[eventSkin][1]);
    format(list, sizeof(list), "%sBlue Team spawn point\t%s\n", list, status2);
    format(list, sizeof(list), "%sArena WWID\t%d\n", list, EventData[eventWorld]);
    format(list, sizeof(list), "%sArena Interior\t%d\n", list, EventData[eventInt]);
    format(list, sizeof(list), "%sTarget Score\t%d\n", list, EventData[eventTarget]);
    format(list, sizeof(list), "%sHealth Event\t%.2f\n", list, EventData[eventHealth]);
    format(list, sizeof(list), "%sArmour Event\t%.2f\n", list, EventData[eventArmor]);
    format(list, sizeof(list), "%sEvent Weapon #1\t%s - %d Ammo\n", list, ReturnWeaponName(EventData[eventWeapons][0]), EventData[eventAmmo][0]);
    format(list, sizeof(list), "%sEvent Weapon #2\t%s - %d Ammo\n", list, ReturnWeaponName(EventData[eventWeapons][1]), EventData[eventAmmo][1]);
    format(list, sizeof(list), "%sEvent Weapon #3\t%s - %d Ammo\n", list, ReturnWeaponName(EventData[eventWeapons][2]), EventData[eventAmmo][2]);
    format(list, sizeof(list), "%sParticipation Prize\t"GREEN"%s\n", list, FormatMoney(EventData[eventBonus]));
    format(list, sizeof(list), "%sWinner Prize\t"GREEN"%s\n", list, FormatMoney(EventData[eventWinnerPrice]));
	format(list, sizeof(list), "%sEvent Finish Setup\n", list);
	format(list, sizeof(list), "%sEvent Cancel Setup", list);
	Dialog_Show(playerid, eventTdmSetups, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Event TDM Setup", list, "Set", "Batal");
	return 1;
}

/* TDM Event Dialog */
Dialog:eventTdmSetups(playerid, response, listitem, inputtext[])
{
	if(AccountData[playerid][pAdmin] < 3) return PermissionError(playerid);
	if(!response) return Info(playerid, "Anda telah membatalkan pilihan!");
	switch(listitem)
	{
		case 0: // Red Team Skin
		{
			Dialog_Show(playerid, TdmRedSkin, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Skin Team Red", "Mohon masukkan ID Skin untuk digunakan Team Red pada Event:", "Set", "Batal");
		}
		case 1: // Red Team Pos
		{
			GetPlayerPos(playerid, EventData[eventSpawnX][0], EventData[eventSpawnY][0], EventData[eventSpawnZ][0]);
			GetPlayerFacingAngle(playerid, EventData[eventSpawnA][0]);
			Info(playerid, "Kamu telah menentukan spawn untuk "RED"team A");
			DialogTDMShow(playerid);
		}
		case 2: // Blue Team Skin
		{
			Dialog_Show(playerid, TdmBlueSkin, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Skin Team Blue", "Mohon masukkan ID Skin untuk digunakan Team Blue pada Event:", "Set", "Batal");
		}
		case 3: // Blue Team Pos
		{
			GetPlayerPos(playerid, EventData[eventSpawnX][1], EventData[eventSpawnY][1], EventData[eventSpawnZ][1]);
			GetPlayerFacingAngle(playerid, EventData[eventSpawnA][1]);
			Info(playerid, "Kamu telah menentukan spawn untuk {0049FF}team B");
			DialogTDMShow(playerid);
		}
		case 4: // Area WWID
		{
			Dialog_Show(playerid, TdmWorld, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event World", "Mohon masukkan World ID untuk digunakan pada Event TDM:", "Set", "Batal");
		}
		case 5: // Interior 
		{
			Dialog_Show(playerid, TdmInterior, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Interior", "Mohon masukkan Interior ID untuk digunakan pada Event TDM:", "Set", "Batal");
		}
		case 6: // Target Score
		{
			Dialog_Show(playerid, TdmTargetScore, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Target Score", "Mohon masukkan berapa target yang harus dicapai pada Event:", "Set", "Batal");
		}
		case 7: // Health Event
		{
			Dialog_Show(playerid, TdmHealth, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Health", "Mohon masukkan berapa value darah merah yang ingin digunakan pada Event:", "Set", "Batal");
		}
		case 8 : // Armour
		{
			Dialog_Show(playerid, TdmArmour, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Armour", "Mohon masukkan berapa value armour / darah putih yang ingin digunakan pada Event:", "Set", "Batal");
		}
		case 9: // Weapon 1
		{
			Dialog_Show(playerid, TdmWeap1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Senjata 1", "Mohon masukkan ID Weapon yang ingin digunakan untuk Event:", "Set", "Batal");
		}
		case 10: // Weapon 2
		{
			Dialog_Show(playerid, TdmWeap2, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Senjata 2", "Mohon masukkan ID Weapon yang ingin digunakan untuk Event:", "Set", "Batal");
		}
		case 11: // Weapon 3
		{
			Dialog_Show(playerid, TdmWeap3, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Senjata 3", "Mohon masukkan ID Weapon yang ingin digunakan untuk Event:", "Set", "Batal");
		}
		case 12: //Hadiah Partisipasi
		{
			Dialog_Show(playerid, TdmPartisiFee, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Participation Price", "Mohon masukkan berapa jumlah hadiah untuk pengikut event:", "Set", "Batal");
		}
		case 13: // Hadiah Pemenang
		{
			Dialog_Show(playerid, TdmWinnerFee, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Winner Price", "Mohon masukkan berapa jumlah hadiah untuk pemenang Event:", "Set", "Batal");
		}
		case 14: // Finish Setup
		{
			if(!EventData[eventSkin][0]) return Error(playerid, "Skin Team Red belum anda isi!"), DialogTDMShow(playerid);
			if(EventData[eventSpawnX][0] == 0.0 || EventData[eventSpawnY][0] == 0.0 || EventData[eventSpawnZ][0] == 0.0) return Error(playerid, "Anda belum menetapkan Spawn untuk Team "RED"Red!"), DialogTDMShow(playerid);
			if(EventData[eventSpawnX][1] == 0.0 || EventData[eventSpawnY][1] == 0.0 || EventData[eventSpawnZ][1] == 0.0) return Error(playerid, "Anda belum menetapkan Spawn untuk Team {0049FF}Blue!"), DialogTDMShow(playerid);
			if(!EventData[eventTarget]) return Error(playerid, "Anda harus melengkapi jumlah Target Score event terlebih dahulu!"), DialogTDMShow(playerid);
			if(!EventData[eventHealth]) return Error(playerid, "Anda harus melengkapi jumlah Health event terlebih dahulu!"), DialogTDMShow(playerid);
			if(!EventData[eventBonus]) return Error(playerid, "Anda harus melengkapi jumlah hadiah partisipasi event terlebih dahulu!"), DialogTDMShow(playerid);
			if(!EventData[eventWinnerPrice]) return Error(playerid, "Anda harus melengkapi jumlah hadiah pemenang event terlebih dahulu!"), DialogTDMShow(playerid);

			EventData[eventCreated] = 1;
			Info(playerid, "Anda telah membuat Event TDM, gunakan "YELLOW"'/event open'"WHITE" untuk membuka event");
		}
		case 15: // Cancel Setup
		{
			SetPVarInt(playerid, "EventTDM", 0);
			EventData[eventSkin][0] = EventData[eventSkin][1] = 0;
			EventData[eventSpawnX][0] = EventData[eventSpawnY][0] = EventData[eventSpawnZ][0] = 0.0;
			EventData[eventSpawnX][1] = EventData[eventSpawnY][1] = EventData[eventSpawnZ][1] = 0.0;
			EventData[eventWorld] = EventData[eventInt] = EventData[eventTarget] = 0;
			EventData[eventHealth] = EventData[eventArmor] = 0;
			EventData[eventWeapons][0] = EventData[eventWeapons][1] = EventData[eventWeapons][2] = 0;
			EventData[eventAmmo][0] = EventData[eventAmmo][1] = EventData[eventAmmo][2] = 0;
			EventData[eventBonus] = EventData[eventWinnerPrice] = 0;
			Info(playerid, "Anda berhasil membatalkan membuat Event Team Deathmatch");
		}
	}
	return 1;
}

Dialog:TdmRedSkin(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 311)
			return Dialog_Show(playerid, TdmRedSkin, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Skin Team Red", "Error: ID Skin tidak valid!\nMohon masukkan ID Skin untuk digunakan Team Red pada Event:", "Set", "Batal");

		EventData[eventSkin][0] = strval(inputtext);
		DialogTDMShow(playerid);
		// Dialog_Show(playerid, eventSkin, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Skin Event", "Team 1: %d\nTeam 2: %d\nNext", "Set", "Back", EventData[eventSkin][0], EventData[eventSkin][1]);	
	}
	else DialogTDMShow(playerid);
	return 1;
}

Dialog:TdmBlueSkin(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 311)
			return Dialog_Show(playerid, TdmBlueSkin, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Skin Team Blue", "Error: ID Skin tidak valid!\nMohon masukkan ID Skin untuk digunakan Team Blue pada Event:", "Set", "Batal");

		EventData[eventSkin][1] = strval(inputtext);
		DialogTDMShow(playerid);
		// Dialog_Show(playerid, eventSkin, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Skin Event", "Team 1: %d\nTeam 2: %d\nNext", "Set", "Back", EventData[eventSkin][0], EventData[eventSkin][1]);	
	}
	else DialogTDMShow(playerid);
	return 1;
}

Dialog:TdmWorld(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 100)
			return Dialog_Show(playerid, TdmWorld, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event World", "Error: World ID tidak dapat dibawah 1 atau lebih dari 100!\nMohon masukkan World ID untuk digunakan pada Event TDM:", "Set", "Batal");

		EventData[eventWorld] = strval(inputtext);
		DialogTDMShow(playerid);
	}
	else DialogTDMShow(playerid);
	return 1;
}

Dialog:TdmInterior(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 0 || strval(inputtext) > 100)
			return Dialog_Show(playerid, TdmInterior, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Interior", "Error: Interior ID tidak dapat dibawah 0 atau lebih dari 100!\nMohon masukkan World ID untuk digunakan pada Event TDM:", "Set", "Batal");

		EventData[eventInt] = strval(inputtext);
		DialogTDMShow(playerid);
	}
	else DialogTDMShow(playerid);
	return 1;
}

Dialog:TdmTargetScore(playerid, response, listitem, inputtext[])
{
	if(response) 
	{
		if(strval(inputtext) < 1 || strval(inputtext) > 150)
			return Dialog_Show(playerid, TdmTargetScore, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Target Score", "Error: Target score must beetween 1 - 150!\nMohon masukkan berapa target yang harus dicapai pada Event:", "Set", "Batal");

		EventData[eventTarget] = strval(inputtext);
		DialogTDMShow(playerid);
	}
	else DialogTDMShow(playerid);
	return 1;
}

Dialog:TdmHealth(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 100)
			return Dialog_Show(playerid, TdmHealth, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Health", "Error: Health must beetween 1 - 100%%!\nMohon masukkan berapa value darah merah yang ingin digunakan pada Event:", "Set", "Batal");

		EventData[eventHealth] = floatstr(inputtext);
		DialogTDMShow(playerid);
	}
	else DialogTDMShow(playerid);
	return 1;
}

Dialog:TdmArmour(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 99)
			return Dialog_Show(playerid, TdmArmour, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Armour", "Error: Armour must beetween 1 - 100%%!\nMohon masukkan berapa value armour / darah putih yang ingin digunakan pada Event:", "Set", "Batal");

		EventData[eventArmor] = floatstr(inputtext);
		DialogTDMShow(playerid);
	}
	else DialogTDMShow(playerid);
	return 1;
}

Dialog:TdmWeap1(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) <= 0 || strval(inputtext) > 46 || (strval(inputtext) >= 19 && strval(inputtext) <= 21))
			return Dialog_Show(playerid, TdmWeap1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Senjata 1", "Error: Invalid ID Weapon For Event!\nMohon masukkan ID Weapon yang ingin digunakan untuk Event:", "Set", "Batal");

		EventData[eventWeapons][0] = strval(inputtext);
		Dialog_Show(playerid, editWeaponAmmo1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Weapon Ammo", "Masukkan berapa jumlah ammo untuk %s:", "Set", "Back", ReturnWeaponName(EventData[eventWeapons][0]));
	}
	else DialogTDMShow(playerid);
	return 1;
}

Dialog:editWeaponAmmo1(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 1000)
			return Dialog_Show(playerid, editWeaponAmmo1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Weapon ID", "Error: Ammo hanya bisa di 1 - 1,000!\n\nMasukkan berapa jumlah ammo untuk %s:", "Set", "Back", EventData[eventWeapons][0]);

		EventData[eventAmmo][0] = strval(inputtext);
		DialogTDMShow(playerid);
	}
	else DialogTDMShow(playerid);
	return 1;
}

Dialog:TdmWeap2(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) <= 0 || strval(inputtext) > 46 || (strval(inputtext) >= 19 && strval(inputtext) <= 21))
			return Dialog_Show(playerid, TdmWeap2, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Senjata 2", "Error: Invalid ID Weapon For Event!\nMohon masukkan ID Weapon yang ingin digunakan untuk Event:", "Set", "Batal");

		EventData[eventWeapons][1] = strval(inputtext);
		Dialog_Show(playerid, editWeaponAmmo2, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Weapon Ammo", "Masukkan berapa jumlah ammo untuk %s:", "Set", "Back", ReturnWeaponName(EventData[eventWeapons][1]));
	}
	else DialogTDMShow(playerid);
	return 1;
}

Dialog:editWeaponAmmo2(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 1000)
			return Dialog_Show(playerid, editWeaponAmmo2, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Weapon ID", "Error: Ammo hanya bisa di 1 - 1,000!\n\nMasukkan berapa jumlah ammo untuk %s:", "Set", "Back", EventData[eventWeapons][1]);

		EventData[eventAmmo][1] = strval(inputtext);
		DialogTDMShow(playerid);
	}
	else DialogTDMShow(playerid);
	return 1;
}

Dialog:TdmWeap3(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) <= 0 || strval(inputtext) > 46 || (strval(inputtext) >= 19 && strval(inputtext) <= 21))
			return Dialog_Show(playerid, TdmWeap3, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Senjata 2", "Error: Invalid ID Weapon For Event!\nMohon masukkan ID Weapon yang ingin digunakan untuk Event:", "Set", "Batal");

		EventData[eventWeapons][2] = strval(inputtext);
		Dialog_Show(playerid, editWeaponAmmo3, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Weapon Ammo", "Masukkan berapa jumlah ammo untuk %s:", "Set", "Back", ReturnWeaponName(EventData[eventWeapons][2]));
	}
	else DialogTDMShow(playerid);
	return 1;
}

Dialog:editWeaponAmmo3(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 1000)
			return Dialog_Show(playerid, editWeaponAmmo3, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Weapon ID", "Error: Ammo hanya bisa di 1 - 1,000!\n\nMasukkan berapa jumlah ammo untuk %s:", "Set", "Back", EventData[eventWeapons][2]);

		EventData[eventAmmo][2] = strval(inputtext);
		DialogTDMShow(playerid);
	}
	else DialogTDMShow(playerid);
	return 1;
}

Dialog:TdmPartisiFee(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 1)
			return Dialog_Show(playerid, TdmPartisiFee, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Participation Price", "Error: Tidak dapat memasukkan nominal kurang dari $1!\nMohon masukkan berapa jumlah hadiah untuk pengikut event:", "Set", "Batal");

		EventData[eventBonus] = strval(inputtext);
		DialogTDMShow(playerid);
	}
	else DialogTDMShow(playerid);
	return 1;
}

Dialog:TdmWinnerFee(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 1)
			return Dialog_Show(playerid, TdmWinnerFee, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Winner Price", "Error: Tidak dapat memasukkan nominal kurang dari $1!\nMohon masukkan berapa jumlah hadiah untuk pemenang event:", "Set", "Batal");

		EventData[eventWinnerPrice] = strval(inputtext);
		DialogTDMShow(playerid);
	}
	else DialogTDMShow(playerid);
	return 1;
}

// -------------------------------------------------------------
Dialog:eventType(playerid, response, listitem, inputtext[])
{
	if(response) 
	{
		EventData[eventType] = (listitem+1);

		if(EventData[eventType] == TYPE_TDM)
			DialogTDMShow(playerid), SetPVarInt(playerid, "EventTDM", 1); //Dialog_Show(playerid, eventTarget, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Target Score", "Masukkan berapa target score event:", "Set", "Back");

		if(EventData[eventType] == TYPE_JETPACK)
			Dialog_Show(playerid, eventBonus, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Bonus", "Masukkan berapa bonus yang akan di berikan:", "Set", "Back");

		if(EventData[eventType] == TYPE_DM)
			Dialog_Show(playerid, eventTarget, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Target Score", "Masukkan berapa target score event:", "Set", "Back");
	}
	return 1;
}

Dialog:eventTarget(playerid, response, listitem, inputtext[])
{
	if(response) 
	{
		if(strval(inputtext) < 1 || strval(inputtext) > 150)
			return Dialog_Show(playerid, eventTarget, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Target Score", "Target score must be betweed 1 - 150\n\nMasukkan berapa target score event:", "Set", "Back");

		EventData[eventTarget] = strval(inputtext);

		if(EventData[eventType] == TYPE_TDM)
			Dialog_Show(playerid, eventSkin, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Skin Event", "Team 1: %d\nTeam 2: %d\nNext", "Set", "Back", EventData[eventSkin][0], EventData[eventSkin][1]);
		else if(EventData[eventType] == TYPE_DM)
			Dialog_Show(playerid, eventHealth, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Health", "Masukkan value darah yang akan di berikan:", "Set", "Back");

	}
	else callcmd::event(playerid, "create");
	return 1;
}

Dialog:eventSkin(playerid, response, listitem, inputtext[])
{
	if(response) {
		switch(listitem)
		{
			case 0: Dialog_Show(playerid, eventSkin1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Skin Team 1", "Masukkan id skin:", "Set", "Back");
			case 1: Dialog_Show(playerid, eventSkin2, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Skin Team 2", "Masukkan id skin:", "Set", "Back");
			case 2: 
			{
				if(!EventData[eventSkin][0] || !EventData[eventSkin][1])
					return Dialog_Show(playerid, eventSkin, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Skin can't 0", "Team 1: %d\nTeam 2: %d\nNext", "Set", "Back", EventData[eventSkin][0], EventData[eventSkin][1]);

				Dialog_Show(playerid, eventHealth, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Health", "Masukkan value darah yang akan di berikan:", "Set", "Back");
			}
		}
	}
	else Dialog_Show(playerid, eventTarget, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Target Score", "Masukkan berapa target score event:", "Set", "Back");
	return 1;
}

Dialog:eventSkin1(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 311)
			return Dialog_Show(playerid, eventSkin1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Skin Team 1", "Id skin tidak sesuai\n\nMasukkan id skin:", "Set", "Back");

		EventData[eventSkin][0] = strval(inputtext);
		Dialog_Show(playerid, eventSkin, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Skin Event", "Team 1: %d\nTeam 2: %d\nNext", "Set", "Back", EventData[eventSkin][0], EventData[eventSkin][1]);	
	}
	else Dialog_Show(playerid, eventSkin, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Skin Event", "Team 1: %d\nTeam 2: %d\nNext", "Set", "Back", EventData[eventSkin][0], EventData[eventSkin][1]);
	return 1;
}

Dialog:eventSkin2(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 311)
			return Dialog_Show(playerid, eventSkin2, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Skin Team 2", "Id skin tidak sesuai\n\nMasukkan id skin:", "Set", "Back");

		EventData[eventSkin][1] = strval(inputtext);
		Dialog_Show(playerid, eventSkin, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Skin Event", "Team 1: %d\nTeam 2: %d\nNext", "Set", "Back", EventData[eventSkin][0], EventData[eventSkin][1]);	
	}
	else Dialog_Show(playerid, eventSkin, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Skin Event", "Team 1: %d\nTeam 2: %d\nNext", "Set", "Back", EventData[eventSkin][0], EventData[eventSkin][1]);
	return 1;
}

Dialog:eventHealth(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 100)
			return Dialog_Show(playerid, eventHealth, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Health", "Health must between 0 - 100\n\nMasukkan value darah yang akan di berikan:", "Set", "Back");

		EventData[eventHealth] = floatstr(inputtext);
		Dialog_Show(playerid, eventArmor, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Armor", "Masukkan value darah putih:", "Set", "Back");

	}
	else 
	{
		if(EventData[eventType] == TYPE_TDM)
			Dialog_Show(playerid, eventSkin, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Skin Event", "Team 1: %d\nTeam 2: %d\nNext", "Set", "Back", EventData[eventSkin][0], EventData[eventSkin][1]);
		else if(EventData[eventType] == TYPE_DM)
			Dialog_Show(playerid, eventHealth, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Health", "Masukkan value darah yang akan di berikan:", "Set", "Back");
	}
	return 1;
}

Dialog:eventArmor(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 100)
			return Dialog_Show(playerid, eventArmor, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Armor", "Darah putih harus berada di antara 0 - 100\n\nMasukkan value darah putih:", "Set", "Back");

		EventData[eventArmor] = floatstr(inputtext);
		Dialog_Show(playerid, eventBonus, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Bonus", "Masukkan berapa bonus yang akan di berikan:", "Set", "Back");
	}
	else Dialog_Show(playerid, eventHealth, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Event Health", "Masukkan value darah yang akan di berikan:", "Set", "Back");
	return 1;
}

Dialog:eventBonus(playerid, response, listitem, inputtext[])
{
	if(response) {
		if(strval(inputtext) < 1 || strval(inputtext) > 1000)
			return Dialog_Show(playerid, eventBonus, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Bonus", "Value bonus harus di antara 0 - 1,000\n\nMasukkan berapa bonus yang akan di berikan:", "Set", "Back");

		EventData[eventBonus] = strval(inputtext);

		if(EventData[eventType] == TYPE_TDM)
		{
			Dialog_Show(playerid, eventFinal, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Event Information", "Score Target\t"YELLOW"%d"WHITE"\nSkin Team 1\t"YELLOW"%d"WHITE"\nSkin Team 2\t"YELLOW"%d"WHITE"\nHealth Spawn\t"YELLOW"%.1f"WHITE"\nArmor Spawn\t"YELLOW"%.1f\n"WHITE"Event Bonus\t"GREEN"%s", "Start", "Back", 
				EventData[eventTarget],
				EventData[eventSkin][0],
				EventData[eventSkin][1],
				EventData[eventHealth],
				EventData[eventArmor],
				FormatMoney(EventData[eventBonus])
			);
		}

		if(EventData[eventType] == TYPE_JETPACK)
			Dialog_Show(playerid, jetpackLoc, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Jetpack Location", "Los Santos\nSan Fierro\nLas Venturas", "Select", "Back");

		if(EventData[eventType] == TYPE_DM)
		{
			Dialog_Show(playerid, eventFinal, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Event Information", "Score Target\t"YELLOW"%d"WHITE"\nHealth Spawn\t"YELLOW"%.1f"WHITE"\nArmor Spawn\t"YELLOW"%.1f\n"WHITE"Event Bonus\t"GREEN"%s", "Start", "Back", 
				EventData[eventTarget],
				EventData[eventHealth],
				EventData[eventArmor],
				FormatMoney(EventData[eventBonus])
			);
		}
	}
	else 
	{
		if(EventData[eventType] == TYPE_TDM) 
			Dialog_Show(playerid, eventHealth, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Health", "Masukkan value darah yang akan di berikan:", "Set", "Back");
		else if(EventData[eventType] == TYPE_DM)
			Dialog_Show(playerid, eventHealth, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Health", "Masukkan value darah yang akan di berikan:", "Set", "Back");
		else Dialog_Show(playerid, eventType, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Event Type", "Team DeathMatch\n"GRAY"Jetpack Race\nDeathMatch", "Select", "Close");
	}
	return 1;
}

Dialog:jetpackLoc(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0: SetPlayerPos(playerid,725.12,-1460.74,22.21); 
			case 1: SetPlayerPos(playerid, -1513.53,-397.74,7.07);
			case 2: SetPlayerPos(playerid, 1749.01, 2318.74, 22.82);
		}
		EventData[eventInt] = GetPlayerInterior(playerid);
		EventData[eventWorld] = GetPlayerVirtualWorld(playerid);

		SetPlayerInterior(playerid, EventData[eventInt]);
		SetPlayerVirtualWorld(playerid, EventData[eventWorld]);

		EventData[eventJetpackType] = (listitem+1);
		Info(playerid, "~b~[INFO]~n~~w~Kamu di tempatkan di spawn jetpack pertama.");

		new loc[13];

		switch(EventData[eventJetpackType])
		{
			case 1: loc = "Los Santos";
			case 2: loc = "San Fierro";
			case 3: loc = "Las Venturas";
		}

		Dialog_Show(playerid, eventFinal, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Event Information", "Event Type\t"YELLOW"Jetpack"WHITE"\nEvent Location\t"YELLOW"%s"WHITE"\nEvent Bonus\t"GREEN"%s", "Start", "Back", 
			loc,
			FormatMoney(EventData[eventBonus])
		);
	}
	else Dialog_Show(playerid, eventBonus, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Bonus", ""GREEN"Pada event jetpack, bonus hanya untuk partisipasi, bonus pemenang di beri admin secara manual\n\n"WHITE"Masukkan berapa bonus yang akan di berikan:", "Set", "Back");
	return 1;
}

Dialog:eventFinal(playerid, response, listitem, inputtext[])
{
	if(response) {
		EventData[eventCreated] = 1;
		EventData[eventWorld] = GetPlayerVirtualWorld(playerid);
		EventData[eventInt] = GetPlayerInterior(playerid);

		Info(playerid, "You've create the event, /event open to open the event.");
	}
	else Dialog_Show(playerid, eventBonus, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Event Bonus", "Masukkan berapa bonus yang akan di berikan:", "Set", "Back");
	return 1;
}