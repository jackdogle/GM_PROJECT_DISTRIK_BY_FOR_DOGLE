#include <YSI\y_hooks>
#define MAX_ATM 500

enum    E_ATM
{
	// loaded from db
	Float: atmX,
	Float: atmY,
	Float: atmZ,
	Float: atmRX,
	Float: atmRY,
	Float: atmRZ,
	atmInt,
	atmWorld,
	// temp
	STREAMER_TAG_OBJECT:atmObjID,
	STREAMER_TAG_AREA: atmArea
}

new AtmData[MAX_ATM][E_ATM],
	Iterator:ATMS<MAX_ATM>;
	
stock Atm_Nearest(playerid)
{
	foreach(new i : ATMS) if(IsPlayerInRangeOfPoint(playerid, 2.0, AtmData[i][atmX], AtmData[i][atmY], AtmData[i][atmZ]))
	{
		return i;
	}
	return -1;
}

forward LoadATM();
public LoadATM()
{
	new rows = cache_num_rows(), id;
	new Cache:Atmcache;
	if(rows)
	{
		Atmcache = cache_save();

		for(new i = 0; i < rows; i++)
		{
			cache_get_value_name_int(i, "id", id);
			cache_get_value_name_float(i, "posx", AtmData[id][atmX]);
			cache_get_value_name_float(i, "posy", AtmData[id][atmY]);
			cache_get_value_name_float(i, "posz", AtmData[id][atmZ]);
			cache_get_value_name_float(i, "posrx", AtmData[id][atmRX]);
			cache_get_value_name_float(i, "posry", AtmData[id][atmRY]);
			cache_get_value_name_float(i, "posrz", AtmData[id][atmRZ]);
			cache_get_value_name_int(i, "interior", AtmData[id][atmInt]);
			cache_get_value_name_int(i, "world", AtmData[id][atmWorld]);
			
			Atm_Refresh(id);
			Iter_Add(ATMS, id);
		}
		printf("[Dynamic ATM]: Jumlah total ATM yang dimuat %d", rows);

		if(cache_is_valid(Atmcache))
        {
            cache_delete(Atmcache);
            printf("[Dynamic ATM]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic ATM]: Cache tidak valid atau sudah dihapus.");
        }
	}
}

Atm_Refresh(id)
{
	if(id != -1)
	{
		if(DestroyDynamicObject(AtmData[id][atmObjID]))
			AtmData[id][atmObjID] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
		
		if(DestroyDynamicArea(AtmData[id][atmArea]))
			AtmData[id][atmObjID] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
		
		AtmData[id][atmArea] = CreateDynamicSphere(AtmData[id][atmX], AtmData[id][atmY], AtmData[id][atmZ], 1.5, AtmData[id][atmWorld], AtmData[id][atmInt], -1);
		AtmData[id][atmObjID] = CreateDynamicObject(11688, AtmData[id][atmX], AtmData[id][atmY], AtmData[id][atmZ], AtmData[id][atmRX], AtmData[id][atmRY], AtmData[id][atmRZ], AtmData[id][atmWorld], AtmData[id][atmInt], -1, 300.00, 300.00); 
		SetDynamicObjectMaterial(AtmData[id][atmObjID], 0, 10765, "airportgnd_sfse", "white", 0xFF00FF00);
		SetDynamicObjectMaterial(AtmData[id][atmObjID], 1, 10765, "airportgnd_sfse", "white", 0xFF00FF00);
		SetDynamicObjectMaterial(AtmData[id][atmObjID], 2, 10765, "airportgnd_sfse", "white", 0x00000000);
		SetDynamicObjectMaterial(AtmData[id][atmObjID], 3, 6060, "shops2_law", "atmflat", 0x00000000);
	}
	return 1;
}

Atm_Save(id)
{
	new cQuery[512];
	format(cQuery, sizeof(cQuery), "UPDATE atms SET posx='%f', posy='%f', posz='%f', posrx='%f', posry='%f', posrz='%f', interior='%d', world='%d' WHERE id='%d'",
	AtmData[id][atmX],
	AtmData[id][atmY],
	AtmData[id][atmZ],
	AtmData[id][atmRX],
	AtmData[id][atmRY],
	AtmData[id][atmRZ],
	AtmData[id][atmInt],
	AtmData[id][atmWorld],
	id
	);
	return mysql_tquery(g_SQL, cQuery);
}

Atm_BeingEdited(id)
{
	if(!Iter_Contains(ATMS, id)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingATMID] == id) return 1;
	return 0;
}

/*GetAnyAtm()
{
	new tmpcount;
	foreach(new id : ATMS)
	{
     	tmpcount++;
	}
	return tmpcount;
}*/

/*NearestAtm(playerid)
{
	for(new i = 0; i < MAX_ATM; i ++)
	{
		if(Iter_Contains(ATMS, i))
		{
			new Float:X, Float:Y, Float:Z, Float:dist;
			GetPlayerPos(playerid, X, Y, Z);

			dist = GetDistanceBetweenPoints(AtmData[i][atmX], AtmData[i][atmY], AtmData[i][atmZ], X, Y, Z);

			if(dist <= 350.0)
			{
				return i;
			}
		}
	}
	return -1;
}*/

CMD:addatm(playerid, params[])
{
	if(!SQL_IsCharacterLogged(playerid))
		return 0;
	
	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);
		
	new id = Iter_Free(ATMS), query[512];
	if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menambahkan ATM lagi!");
 	new Float: x, Float: y, Float: z;
 	GetPlayerPos(playerid, x, y, z);
	
	AtmData[id][atmX] = x;
	AtmData[id][atmY] = y;
	AtmData[id][atmZ] = z;
	AtmData[id][atmRX] = AtmData[id][atmRY] = AtmData[id][atmRZ] = 0.0;
	AtmData[id][atmInt] = GetPlayerInterior(playerid);
	AtmData[id][atmWorld] = GetPlayerVirtualWorld(playerid);
	
	// new str[128];
	AtmData[id][atmObjID] = CreateDynamicObject(11688, AtmData[id][atmX], AtmData[id][atmY], AtmData[id][atmZ], AtmData[id][atmRX], AtmData[id][atmRY], AtmData[id][atmRZ], AtmData[id][atmWorld], AtmData[id][atmInt], -1, 50.0, 50.0);
	SetDynamicObjectMaterial(AtmData[id][atmObjID], 0, 10765, "airportgnd_sfse", "white", 0xFF55E687);
	SetDynamicObjectMaterial(AtmData[id][atmObjID], 1, 10765, "airportgnd_sfse", "white", 0xFF55E687);
	SetDynamicObjectMaterial(AtmData[id][atmObjID], 2, 10765, "airportgnd_sfse", "white", 0x00000000);
	SetDynamicObjectMaterial(AtmData[id][atmObjID], 3, 6060, "shops2_law", "atmflat", 0x00000000);
	AtmData[id][atmArea] = CreateDynamicSphere(AtmData[id][atmX], AtmData[id][atmY], AtmData[id][atmZ], 1.0, -1, -1);
	Iter_Add(ATMS, id);
	
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO atms SET id='%d', posx='%f', posy='%f', posz='%f', posrx='%f', posry='%f', posrz='%f', interior='%d', world='%d'", id, AtmData[id][atmX], AtmData[id][atmY], AtmData[id][atmZ], AtmData[id][atmRX], AtmData[id][atmRY], AtmData[id][atmRZ], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
	mysql_tquery(g_SQL, query, "OnAtmCreated", "ii", playerid, id);
	return 1;
}

function OnAtmCreated(playerid, id)
{
	Atm_Save(id);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Membuata Dynamic ATM ID: %d", AccountData[playerid][pAdminname], id);
	return 1;
}

CMD:editatm(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);
	
	if(AccountData[playerid][EditingATMID] != -1) return Error(playerid, "You're already editing.");

	new id;
	if(sscanf(params, "i", id)) return Syntax(playerid, "/editatm [id]");
	if(!Iter_Contains(ATMS, id)) return Error(playerid, "Invalid ID.");
	if(!IsPlayerInRangeOfPoint(playerid, 30.0, AtmData[id][atmX], AtmData[id][atmY], AtmData[id][atmZ])) return Error(playerid, "You're not near the atm you want to edit.");
	AccountData[playerid][EditingATMID] = id;
	EditDynamicObject(playerid, AtmData[id][atmObjID]);
	return 1;
}

CMD:removeatm(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);
		
	new id, query[512];
	if(sscanf(params, "i", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/removeatm [id atm]");
	if(!Iter_Contains(ATMS, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID atm tidak valid!");
	
	if(Atm_BeingEdited(id)) return Error(playerid, "Can't remove specified atm because its being edited.");
	DestroyDynamicObject(AtmData[id][atmObjID]);
	
	AtmData[id][atmX] = AtmData[id][atmY] = AtmData[id][atmZ] = AtmData[id][atmRX] = AtmData[id][atmRY] = AtmData[id][atmRZ] = 0.0;
	AtmData[id][atmInt] = AtmData[id][atmWorld] = 0;
	AtmData[id][atmObjID] = -1;
	Iter_Remove(ATMS, id);
	
	mysql_format(g_SQL, query, sizeof(query), "DELETE FROM atms WHERE id=%d", id);
	mysql_tquery(g_SQL, query);
	Info(playerid, "Anda berhasil menghapus Dynamic ATM ID %d.", id);
	return 1;
}

CMD:gotoatm(playerid, params[])
{
	new id;
	if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);
		
	if(sscanf(params, "d", id))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotoatm [ID atm]");
	if(!Iter_Contains(ATMS, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ATM ID tidak ada.");
	
	SetPlayerPosition(playerid, AtmData[id][atmX], AtmData[id][atmY], AtmData[id][atmZ], 2.0);
    SetPlayerInterior(playerid, AtmData[id][atmInt]);
    SetPlayerVirtualWorld(playerid, AtmData[id][atmWorld]);
	AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Teleportasi Ke ATM ID: %d.", GetAdminName(playerid), id);
	return 1;
}


hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		new id = Atm_Nearest(playerid);
		if(id == -1) return false;

		if(id > -1)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.0, AtmData[id][atmX], AtmData[id][atmY], AtmData[id][atmZ]))
			{
				ShowATMTD(playerid);
				HideShortKey(playerid);
			}
		}
	}
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case DIALOG_ATM_TRANSFER:
		{
			if(!response) return 1;

			if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fleeca Bank", 
			"Error: Harus diisi tidak dapat kosong!\nMohon masukkan nomor rekening yang ingin anda transfer:", "Submit", "Batal");

			if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fleeca Bank", 
			"Error: Hanya dapat diisi angka!\nMohon masukkan nomor rekening yang ingin anda transfer:", "Submit", "Batal");

			new query[128];
			mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `player_characters` WHERE `Char_BankRek` = %d", strval(inputtext));
			mysql_tquery(g_SQL, query, "SearchRekening", "dd", playerid, strval(inputtext));
			return 1;	
		}
		case DIALOG_ATM_TRANSFER1:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");

			if(isnull(inputtext)) 
			{
				return ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fleeca Bank", 
				"Error: Harus diisi tidak dapat kosong!\nMohon masukkan nominal uang yang ingin anda transfer:", "Submit", "Batal");
			}

			if(!IsNumeric(inputtext)) 
			{
				return ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fleeca Bank", 
				"Error: Hanya dapat diisi angka!\nMohon masukkan nominal uang yang ingin anda transfer:", "Submit", "Batal");
			}

			if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pBankMoney]) 
			{
				return ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fleeca Bank", 
				"Error: Jumlah tidak valid!\nMohon masukkan nominal uang yang ingin anda transfer:", "Submit", "Batal");
			}

			new ownerRek = GetRekeningOwner(AccountData[playerid][pTransferRek]);
			if(!IsPlayerConnected(ownerRek)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
			
			AccountData[ownerRek][pBankMoney] += strval(inputtext);
			AccountData[playerid][pBankMoney] -= strval(inputtext);
			SendClientMessageEx(ownerRek, -1, "[i] Anda mendapatkan transfer dari // Nama Rek: %s // Jumlah Transfer: "GREEN"%s", AccountData[playerid][pName], FormatMoney(strval(inputtext)));
			ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil mengirim %s ke nomor rekening %d", FormatMoney(strval(inputtext)), AccountData[playerid][pTransferRek]));
			
			foreach(new i : Player) if (AccountData[i][pAdmin] >= 1 && IsPlayerConnected(i))
			{
				SendClientMessageEx(i, -1, ""YELLOW"[Transfer Logs]: %s(%d) Mentransfer uang sebesar %s kepada %s(%d)", AccountData[playerid][pName], playerid, FormatMoney(strval(inputtext)), AccountData[ownerRek][pName], ownerRek);
			}
			new frmxt[255];
			format(frmxt, sizeof(frmxt), "Mentransfer uang kepada rekening %d sebesar $%d", AccountData[playerid][pTransferRek], strval(inputtext));
			AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], frmxt, strval(inputtext));
			AccountData[playerid][pTransferRek] = 0;
		}
		case DIALOG_ATM_DEPOSIT:
		{
			if(!response) return 1;
			
			if(isnull(inputtext))
			{
				ShowPlayerDialog(playerid, DIALOG_ATM_DEPOSIT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fleeca Bank", 
				"Error: Tidak dapat diisi kosong!\nMohon masukan berapa jumlah uang yang ingin anda masukkan:", "Submit", "Batal");
				return 1;
			}

			if(!IsNumeric(inputtext))
			{
				ShowPlayerDialog(playerid, DIALOG_ATM_DEPOSIT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fleeca Bank", 
				"Error: Hanya dapat diisi angka!\nMohon masukan berapa jumlah uang yang ingin anda masukkan:", "Submit", "Batal");
				return 1;
			}

			new value = strval(inputtext);
			// Cek limit berdasarkan level
			if(AccountData[playerid][pLevel] >= 1 && AccountData[playerid][pLevel] < 15 && value > 100000)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Level anda hanya dapat menyimpan max $100.000 di ATM!");

			else if(AccountData[playerid][pLevel] >= 15 && AccountData[playerid][pLevel] < 25 && value > 200000)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Level anda hanya dapat menyimpan max $200.000 di ATM!");

			else if(AccountData[playerid][pLevel] >= 25 && AccountData[playerid][pLevel] < 35 && value > 300000)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Level anda hanya dapat menyimpan max $300.000 di ATM!");

			else if(AccountData[playerid][pLevel] >= 35 && AccountData[playerid][pLevel] < 50 && value > 500000)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Level anda hanya dapat menyimpan max $500.000 di ATM!");

			else if(AccountData[playerid][pLevel] >= 50 && AccountData[playerid][pLevel] <= 100 && value > 1000000)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Level anda hanya dapat menyimpan max $1.000.000 di ATM!");

			if(value > AccountData[playerid][pMoney])
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak sebanyak itu!");

			if(value < 1)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal dibawah $1 untuk deposit!");

			TakeMoney(playerid, value);
			AccountData[playerid][pBankMoney] += value;
			ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil memasukkan %s", FormatMoney(value)));
			PlayerTextDrawSetString(playerid, VR_ATMTD[playerid][30], sprintf("%s", FormatMoney(AccountData[playerid][pBankMoney])));
			PlayerTextDrawShow(playerid, VR_ATMTD[playerid][30]);

			new query[200];
			mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_BankMoney`=%d, `Char_Money`=%d WHERE `pID`=%d", AccountData[playerid][pBankMoney], AccountData[playerid][pMoney], AccountData[playerid][pID]);
			mysql_tquery(g_SQL, query);
		}
		case DIALOG_ATM_WITHDRAW:
		{
			if(!response) return 1;

			if(isnull(inputtext))
			{
				ShowPlayerDialog(playerid, DIALOG_ATM_WITHDRAW, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fleeca Bank", 
				"Error: Tidak dapat diisi kosong!\nMohon masukan berapa jumlah uang yang anda ingin anda ambil:", "Submit", "Batal");
				return 1;
			}

			if(!IsNumeric(inputtext))
			{
				ShowPlayerDialog(playerid, DIALOG_ATM_WITHDRAW, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fleeca Bank", 
				"Error: Hanya dapat diisi angka!\nMohon masukan berapa jumlah uang yang anda ingin anda ambil:", "Submit", "Batal");
				return 1;
			}

			new value = strval(inputtext);
			if(value > AccountData[playerid][pBankMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo anda tidak sebanyak itu!");
			if(value < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal dibawah $1 untuk withdraw!");

			GiveMoney(playerid, value);
			AccountData[playerid][pBankMoney] -= value;
			PlayerTextDrawSetString(playerid, VR_ATMTD[playerid][30], sprintf("%s", FormatMoney(AccountData[playerid][pBankMoney])));
			PlayerTextDrawShow(playerid, VR_ATMTD[playerid][30]);
			ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil mengambil uang %s", FormatMoney(value)));

			new query[200];
			mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_BankMoney`=%d, `Char_Money`=%d WHERE `pID`=%d", AccountData[playerid][pBankMoney], AccountData[playerid][pMoney], AccountData[playerid][pID]);
			mysql_tquery(g_SQL, query);
		}
	}
	return 1;
}

FUNC::SearchRekening(playerid, norek)
{
	if(!cache_num_rows())
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Nomor rekening tersebut tidak terdaftar!");
		return 1;
	}
	else 
	{
		new ownerRek = GetRekeningOwner(norek);
        if(!IsPlayerConnected(ownerRek)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
		AccountData[playerid][pTransferRek] = norek;
		ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fleeca Bank", "Mohon masukkan nominal uang yang ingin anda transfer:", "Submit", "Batal");
	}
	return 1;
}

hook OnPlayerEnterDynArea(playerid, areaid)
{
	foreach(new i : ATMS)
	{
		if(areaid == AtmData[i][atmArea])
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
			{
				ShowKey(playerid, "[Y]- Akses ATM");
			}
		}
	}
	return 1;
}

hook OnPlayerLeaveDynArea(playerid, areaid)
{
	foreach(new i : ATMS)
	{
		if(areaid == AtmData[i][atmArea])
		{
			HideShortKey(playerid);
		}
	}
	return 1;
}