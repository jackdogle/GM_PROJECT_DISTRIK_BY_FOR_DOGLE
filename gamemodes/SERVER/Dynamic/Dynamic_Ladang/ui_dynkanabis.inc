#include <YSI\y_hooks>

#define MAX_KANABIS 100

new pTakeKanabis[MAX_PLAYERS] = {-1, ...};
new pOlahKanabis[MAX_PLAYERS] = {-1, ...};

enum e_kanabis
{
	// Load Dari Database Idann
	Float:kanabisX,
	Float:kanabisY,
	Float:kanabisZ,
	Float:kanabisRX,
	Float:kanabisRY,
	Float:kanabisRZ,
	kanabisObjID,
	kanabisInt,
	kanabisWorld,
	STREAMER_TAG_AREA:kanabisArea,

	bool:kanabisExists,
	kanabisTimer,
}
new LadangData[MAX_KANABIS][e_kanabis],
	Iterator:Ladang<MAX_KANABIS>;

forward LoadKanabis();
public LoadKanabis()
{
	new id, rows = cache_num_rows();
	new Cache:Kanbcache;
	if(rows)
	{
		Kanbcache = cache_save();

		for(new x; x < rows; x ++)
		{
			cache_get_value_name_int(x, "id", id);
			cache_get_value_name_float(x, "kanabisX", LadangData[id][kanabisX]);
			cache_get_value_name_float(x, "kanabisY", LadangData[id][kanabisY]);
			cache_get_value_name_float(x, "kanabisZ", LadangData[id][kanabisZ]);
			cache_get_value_name_float(x, "kanabisRY", LadangData[id][kanabisRX]);
			cache_get_value_name_float(x, "kanabisRX", LadangData[id][kanabisRY]);
			cache_get_value_name_float(x, "kanabisRZ", LadangData[id][kanabisRZ]);
			cache_get_value_name_int(x, "interior", LadangData[id][kanabisInt]);
			cache_get_value_name_int(x, "world", LadangData[id][kanabisWorld]);
			cache_get_value_name_int(x, "kanabisTimer", LadangData[id][kanabisTimer]);

			LadangData[id][kanabisExists] = true;
			
			Kanabis_Refresh(id);
			Iter_Add(Ladang, id);
		}
		printf("[Dynamic Kanabis]: Jumlah total Kanabis yang dimuat %d", rows);

		if(cache_is_valid(Kanbcache))
        {
            cache_delete(Kanbcache);
            printf("[Dynamic Kanabis]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Kanabis]: Cache tidak valid atau sudah dihapus.");
        }
	}
}

KanabisNearest(playerid)
{
	foreach(new i : Ladang) if (IsPlayerInRangeOfPoint(playerid, 2.0, LadangData[i][kanabisX], LadangData[i][kanabisY], LadangData[i][kanabisZ]))
	{
		return i;
	}
	return -1;
}

stock Kanabis_Refresh(id)
{
	if(id != -1)
	{
		if(!LadangData[id][kanabisTimer])
		{
			LadangData[id][kanabisObjID] = CreateDynamicObject(19473, LadangData[id][kanabisX], LadangData[id][kanabisY], LadangData[id][kanabisZ], LadangData[id][kanabisRX], LadangData[id][kanabisRY], LadangData[id][kanabisRZ], LadangData[id][kanabisWorld], LadangData[id][kanabisInt], -1, 50.0, 50.0);
			LadangData[id][kanabisArea] = CreateDynamicSphere(LadangData[id][kanabisX], LadangData[id][kanabisY], LadangData[id][kanabisZ], 2.0, LadangData[id][kanabisWorld], LadangData[id][kanabisInt], -1, 0);
		}
	}
	return 1;
}

Ladang_Save(id)
{
	new cQuery[512];
	format(cQuery, sizeof(cQuery), "UPDATE ladang SET kanabisX='%f', kanabisY='%f', kanabisZ='%f', kanabisRX='%f', kanabisRY='%f', kanabisRZ='%f', interior=%d, world=%d, kanabisTimer='%d' WHERE id=%d",
	LadangData[id][kanabisX],
	LadangData[id][kanabisY],
	LadangData[id][kanabisZ],
	LadangData[id][kanabisRX],
	LadangData[id][kanabisRY],
	LadangData[id][kanabisRZ],
	LadangData[id][kanabisInt],
	LadangData[id][kanabisWorld],
	LadangData[id][kanabisTimer],
	id
	);
	return mysql_tquery(g_SQL, cQuery);
}

Ladang_BeingEdited(id)
{
	if(!Iter_Contains(Ladang, id)) return 0;
	foreach(new i : Player) if(AccountData[i][EditingLADANGID] == id) return 1;
	return 0;
}

CMD:addkanabis(playerid, params[])
{
	if (AccountData[playerid][pAdmin] < 6)
		return PermissionError(playerid);

	new id = Iter_Free(Ladang), query[512];
	if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menambah Kanabis");
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);

	LadangData[id][kanabisExists] = true;
	LadangData[id][kanabisX] = x;
	LadangData[id][kanabisY] = y;
	LadangData[id][kanabisZ] = z;
	LadangData[id][kanabisRX] = LadangData[id][kanabisRY] = LadangData[id][kanabisRZ] = 0.0;
	LadangData[id][kanabisInt] = GetPlayerInterior(playerid);
	LadangData[id][kanabisWorld] = GetPlayerVirtualWorld(playerid);
	LadangData[id][kanabisTimer] = 0;

	LadangData[id][kanabisObjID] = CreateDynamicObject(19473, LadangData[id][kanabisX], LadangData[id][kanabisY], LadangData[id][kanabisZ], LadangData[id][kanabisRX], LadangData[id][kanabisRY], LadangData[id][kanabisRZ], LadangData[id][kanabisWorld], LadangData[id][kanabisInt], -1, 50.0, 50.0);
	LadangData[id][kanabisArea] = CreateDynamicSphere(LadangData[id][kanabisX], LadangData[id][kanabisY], LadangData[id][kanabisZ], 2.0, LadangData[id][kanabisWorld], LadangData[id][kanabisInt], -1);
	Iter_Add(Ladang, id);

	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO ladang SET id=%d, kanabisX='%f', kanabisY='%f', kanabisZ='%f', kanabisRX='%f', kanabisRY='%f', kanabisRZ='%f', interior=%d, world=%d", id, LadangData[id][kanabisX], LadangData[id][kanabisY], LadangData[id][kanabisZ], LadangData[id][kanabisRX], LadangData[id][kanabisRY], LadangData[id][kanabisRZ], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
	mysql_tquery(g_SQL, query, "OnLadangCreated", "ii", playerid, id);
	return 1;
}

FUNC::OnLadangCreated(playerid, id)
{
	Ladang_Save(id);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah Membuat Dynamic Kanabis ID:%d", GetRPName(playerid), id);
	return 1;
}

CMD:editkanabis(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5)
		return PermissionError(playerid);
	
	if(AccountData[playerid][EditingLADANGID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "You're already editing.");

	new id;
	if(sscanf(params, "i", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editkanabis [id]");
	if(!Iter_Contains(Ladang, id)) return Error(playerid, "Invalid ID.");
	if(!IsPlayerInRangeOfPoint(playerid, 30.0, LadangData[id][kanabisX], LadangData[id][kanabisY], LadangData[id][kanabisZ])) return ShowTDN(playerid, NOTIFICATION_ERROR, "You're not near the atm you want to edit.");
	AccountData[playerid][EditingLADANGID] = id;
	EditDynamicObject(playerid, LadangData[id][kanabisObjID]);
	return 1;
}

CMD:removekanabis(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);
		
	new id, query[512];
	if(sscanf(params, "i", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/removekanabis [id kanabis]");
	if(!Iter_Contains(Ladang, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Kanabis tidak valid!");
	
	if(Ladang_BeingEdited(id)) return Error(playerid, "Can't remove specified Kanabis because its being edited.");
	DestroyDynamicObject(LadangData[id][kanabisObjID]);
	// DestroyDynamic3DTextLabel(AtmData[id][atmLabel]);

	if(DestroyDynamicArea(LadangData[id][kanabisArea]))
		LadangData[id][kanabisArea] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	
	LadangData[id][kanabisExists] = false;
	LadangData[id][kanabisX] = LadangData[id][kanabisY] = LadangData[id][kanabisZ] = LadangData[id][kanabisRX] = LadangData[id][kanabisRY] = LadangData[id][kanabisRZ] = 0.0;
	LadangData[id][kanabisInt] = LadangData[id][kanabisWorld] = 0;
	LadangData[id][kanabisObjID] = -1;
	Iter_Remove(Ladang, id);
	
	mysql_format(g_SQL, query, sizeof(query), "DELETE FROM ladang WHERE id=%d", id);
	mysql_tquery(g_SQL, query);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menghapus Kanabis ID: %d.", GetRPName(playerid), id);
	return 1;
}

CMD:gotokanabis(playerid, params[])
{
	new id;
	if(AccountData[playerid][pAdmin] < 3)
        return PermissionError(playerid);
		
	if(sscanf(params, "d", id))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotokanabis [ID]");
	if(!Iter_Contains(Ladang, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kanabis ID tidak ada.");
	
	SetPlayerPosition(playerid, LadangData[id][kanabisX], LadangData[id][kanabisY], LadangData[id][kanabisZ], 2.0);
    SetPlayerInterior(playerid, LadangData[id][kanabisInt]);
    SetPlayerVirtualWorld(playerid, LadangData[id][kanabisWorld]);
	AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Teleport ke Kanabis ID: %d.", GetRPName(playerid), id);
	// Servers(playerid, "Teleport ke ID ATM %d", id);
	return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
	foreach(new i : Ladang)
	{
		if(areaid == LadangData[i][kanabisArea])
		{
			if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
			{
				ShowKey(playerid, "[Y]- Ambil Kanabis");
			}
		}
	}
	return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
	foreach(new i : Ladang)
	{
		if(areaid == LadangData[i][kanabisArea])
		{
			HideShortKey(playerid);
		}
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		new kid = KanabisNearest(playerid);
		if(kid != -1 && LadangData[kid][kanabisArea] != STREAMER_TAG_AREA: INVALID_STREAMER_ID)
		{
			new count, ems;
			foreach(new i : Player) if (AccountData[i][IsLoggedIn])
			{
				if(AccountData[i][pDutyPD]) count++;
				if(AccountData[i][pDutyEms]) ems++;
			}
			if(count >= 4 && ems >= 2) 
			{
				if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
				if(!LadangData[kid][kanabisExists]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kanabis ini sudah diambil orang lain!");

				AccountData[playerid][ActivityTime] = 0;
				LadangData[kid][kanabisExists] = false;
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMETIK KANABIS");
				ShowProgressBar(playerid);

				ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
				pTakeKanabis[playerid] = SetTimerEx("TakingKanabis", 1000, true, "dd", playerid, kid);
			}
			else return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 Polisi Duty & 2 EMS Duty");
		}
	}
	return 1;
}

forward TakingKanabis(playerid, x);
public TakingKanabis(playerid, x)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pTakeKanabis[playerid]);
		pTakeKanabis[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(!IsValidDynamicArea(LadangData[x][kanabisArea]))
	{
		KillTimer(pTakeKanabis[playerid]);
		pTakeKanabis[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		LadangData[x][kanabisExists] = true;
		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(!IsPlayerInDynamicArea(playerid, LadangData[x][kanabisArea]))
	{
		KillTimer(pTakeKanabis[playerid]);
		pTakeKanabis[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		LadangData[x][kanabisExists] = true;
		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(AccountData[playerid][pInjured])
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
		KillTimer(pTakeKanabis[playerid]);
		pTakeKanabis[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		LadangData[x][kanabisExists] = true;
		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(Inventory_Count(playerid, "Kanabis") >= 100)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Kanabis telah maksimal di inventory anda!");
		KillTimer(pTakeKanabis[playerid]);
		pTakeKanabis[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		LadangData[x][kanabisExists] = true;
		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(GetTotalWeightFloat(playerid) > 50)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
		KillTimer(pTakeKanabis[playerid]);
		pTakeKanabis[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		LadangData[x][kanabisExists] = true;
		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 8)
	{
		KillTimer(pTakeKanabis[playerid]);
		pTakeKanabis[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		
		Inventory_Add(playerid, "Kanabis", 19473);
		ShowItemBox(playerid, "Received 1x", "Kanabis", 19473);
		if(DestroyDynamicObject(LadangData[x][kanabisObjID]))
			LadangData[x][kanabisObjID] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

		if(DestroyDynamicArea(LadangData[x][kanabisArea]))
			LadangData[x][kanabisArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
		
		LadangData[x][kanabisTimer] = 120;
		Ladang_Save(x);
		GivePlayerXP(playerid, 1);
	}
	else
	{
		AccountData[playerid][ActivityTime] ++;

		static Float:progressvalue;
		progressvalue = AccountData[playerid][ActivityTime] * 103/8;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		return 0;
	}
	return 1;
}

task KanabisUpdate[1000]()
{
    foreach (new i : Ladang)
    {
        // Kurangi timer hanya jika lebih besar dari 0
        if (LadangData[i][kanabisTimer] > 0)
        {
            LadangData[i][kanabisTimer]--;
            
            // Jika timer mencapai 0, reset dan refresh data
            if (LadangData[i][kanabisTimer] == 0)
            {
                LadangData[i][kanabisExists] = true;
                Kanabis_Refresh(i);
                Ladang_Save(i);
            }
        }
    }
    return 1;
}


hook OnPlayerConnect(playerid)
{
	pTakeKanabis[playerid] = -1;
	pOlahKanabis[playerid] = -1;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	KillTimer(pTakeKanabis[playerid]);
	KillTimer(pOlahKanabis[playerid]);
	pTakeKanabis[playerid] = -1;
	pOlahKanabis[playerid] = -1;
	return 1;
}