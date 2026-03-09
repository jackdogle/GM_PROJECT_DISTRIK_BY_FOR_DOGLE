#include <YSI\y_hooks>

enum e_robberydata
{
    Float:robberyPos[3],
    Float:robberyRot[3],

    STREAMER_TAG_OBJECT:robberyObjectID,
    robberyInt,
    robberyWorld,
}
new RobberyData[MAX_DYNAMIC_ROBBERY][e_robberydata],
    Iterator:Robbery<MAX_DYNAMIC_ROBBERY>;

new bool: DurringRobbery[MAX_PLAYERS] = {false, ...};

Robbery_Rebuild(id)
{
    if(id != -1)
    {
        if(DestroyDynamicObject(RobberyData[id][robberyObjectID]))
            RobberyData[id][robberyObjectID] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        if(RobberyData[id][robberyPos][0] != 0.0)
        {
            RobberyData[id][robberyObjectID] = CreateDynamicObject(2332, RobberyData[id][robberyPos][0], RobberyData[id][robberyPos][1], RobberyData[id][robberyPos][2], RobberyData[id][robberyRot][0], RobberyData[id][robberyRot][1], RobberyData[id][robberyRot][2], RobberyData[id][robberyWorld], RobberyData[id][robberyInt], -1, 50.0, 50.0, -1);
        }
    }
    return 1;
}

Robbery_Save(id)
{
    new cQuery[1048];
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `robbery` SET `RobberyX`=%f, `RobberyY`=%f, `RobberyZ`=%f, `RobberyRX`=%f, `RobberyRY`=%f, `RobberyRZ`=%f, `RobberyInterior`=%d, `RobberyWorld`=%d WHERE `RobberyID`=%d",
    RobberyData[id][robberyPos][0], RobberyData[id][robberyPos][1], RobberyData[id][robberyPos][2], RobberyData[id][robberyRot][0], RobberyData[id][robberyRot][1], RobberyData[id][robberyRot][2], RobberyData[id][robberyInt], RobberyData[id][robberyWorld], id);
    mysql_tquery(g_SQL, cQuery);
    return 1;
}

forward LoadDynamicRobbery();
public LoadDynamicRobbery()
{
    new id, rows = cache_num_rows();
    new Cache:Robbcache;
    if(rows)
    {
        Robbcache = cache_save();

        for(new i = 0; i < rows; i ++)
        {
            id = cache_get_field_int(i, "RobberyID");
            RobberyData[id][robberyPos][0] = cache_get_field_float(i, "RobberyX");
            RobberyData[id][robberyPos][1] = cache_get_field_float(i, "RobberyY");
            RobberyData[id][robberyPos][2] = cache_get_field_float(i, "RobberyZ");
            RobberyData[id][robberyRot][0] = cache_get_field_float(i, "RobberyRX");
            RobberyData[id][robberyRot][1] = cache_get_field_float(i, "RobberyRY");
            RobberyData[id][robberyRot][2] = cache_get_field_float(i, "RobberyRZ");
            RobberyData[id][robberyInt] = cache_get_field_int(i, "RobberyInterior");
            RobberyData[id][robberyWorld] = cache_get_field_int(i, "RobberyWorld");

            Robbery_Rebuild(id);
            Iter_Add(Robbery, id);
        }
        printf("[Dynamic Robbery]: Jumlah total dynamic robbery yang dimuat %d", rows);

        if(cache_is_valid(Robbcache))
        {
            cache_delete(Robbcache);
            printf("[Dynamic Robbery]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Robbery]: Cache tidak valid atau sudah dihapus.");
        }
    }
    return 1;
}

CMD:addrobbery(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    new id = Iter_Free(Robbery);
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menambah Dynamic Robbery lagi!");
    
    GetPlayerPos(playerid, RobberyData[id][robberyPos][0], RobberyData[id][robberyPos][1], RobberyData[id][robberyPos][2]);
    RobberyData[id][robberyPos][0] = RobberyData[id][robberyPos][0];
    RobberyData[id][robberyPos][1] = RobberyData[id][robberyPos][1];
    RobberyData[id][robberyPos][2] = RobberyData[id][robberyPos][2];
    RobberyData[id][robberyRot][0] = RobberyData[id][robberyRot][1] = RobberyData[id][robberyRot][2] = 0.0;
    RobberyData[id][robberyWorld] = GetPlayerVirtualWorld(playerid);
    RobberyData[id][robberyInt] = GetPlayerInterior(playerid);
    
    Robbery_Rebuild(id);
    Iter_Add(Robbery, id);

    new cQuery[1048];
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `robbery` SET `RobberyID`=%d, `RobberyX`=%f, `RobberyY`=%f, `RobberyZ`=%f, `RobberyRX`=%f, `RobberyRY`=%f, `RobberyRZ`=%f, `RobberyInterior`=%d, `RobberyWorld`=%d",
    id, RobberyData[id][robberyPos][0], RobberyData[id][robberyPos][1], RobberyData[id][robberyPos][2], RobberyData[id][robberyRot][0], RobberyData[id][robberyRot][1], RobberyData[id][robberyRot][2], RobberyData[id][robberyInt], RobberyData[id][robberyWorld]);
    mysql_tquery(g_SQL, cQuery, "OnRobberyAdded", "dd", playerid, id);
    return 1;
}

forward OnRobberyAdded(playerid, id);
public OnRobberyAdded(playerid, id)
{
    Robbery_Save(id);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" membuat Dynamic Robbery ID %d", AccountData[playerid][pAdminname], id);
    return 1;
}

CMD:editrobbery(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    new id, option[24];
    if(sscanf(params, "ds[24]", id, option)) 
    {
        Syntax(playerid, "/editrobbery [id] (position, delete)");
        return 1;
    }
    if(id < 0 || id >= MAX_DYNAMIC_ROBBERY) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Robbery tidak valid!");
    if(!Iter_Contains(Robbery, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Robbery tidak ada!");
    if(!strcmp(option, "position", true))
    {
        if(AccountData[playerid][EditingROBERID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang dalam mode pengeditan!");
        if(!IsPlayerInRangeOfPoint(playerid, 25.0, RobberyData[id][robberyPos][0], RobberyData[id][robberyPos][1], RobberyData[id][robberyPos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada didekat dynamic tersebut!");

        AccountData[playerid][EditingROBERID] = id;
        EditDynamicObject(playerid, RobberyData[id][robberyObjectID]);
    }
    else if(!strcmp(option, "delete", true))
    {
        RobberyData[id][robberyPos][0] = 0.0;
        RobberyData[id][robberyPos][1] = 0.0;
        RobberyData[id][robberyPos][2] = 0.0;
        RobberyData[id][robberyRot][0] = RobberyData[id][robberyRot][1] = RobberyData[id][robberyRot][2] = 0.0;
        RobberyData[id][robberyWorld] = 0;
        RobberyData[id][robberyInt] = 0;
        if(DestroyDynamicObject(RobberyData[id][robberyObjectID])) RobberyData[id][robberyObjectID] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        Iter_Remove(Robbery, id);

        new query[200];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `robbery` WHERE `RobberyID` = %d", id);
        mysql_tquery(g_SQL, query);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menghapus Dynamic Robbery ID: %d", AccountData[playerid][pAdminname], id);
    }
    return 1;
}

CMD:gotorobbery(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1) return PermissionError(playerid);

    new id;
    if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotorobbery [id]");
    if(id < 0 || id >= MAX_DYNAMIC_ROBBERY) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Robbery tidak valid!");
    if(!Iter_Contains(Robbery, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Robbery tidak ada!");

    SetPlayerPositionEx(playerid, RobberyData[id][robberyPos][0], RobberyData[id][robberyPos][1], RobberyData[id][robberyPos][2], 0.0, 5000);
    SetPlayerInteriorEx(playerid, RobberyData[id][robberyInt]);
    SetPlayerVirtualWorldEx(playerid, RobberyData[id][robberyWorld]);
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInBiz] = -1;
    Info(playerid, "Anda teleportasi ke Dynamic Robbery ID %d", id);
    return 1;
}

CMD:resetrobbery(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);
	if(!g_RobberyTime) return ShowTDN(playerid, NOTIFICATION_ERROR, "Waktu Robbery Tidak Sedang Delay!");

	g_RobberyTime = 0;
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mereset delay robbery", AccountData[playerid][pAdminname]);
	return 1;
}

hook OnPlayerShootDynObj(playerid, weaponid, STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z)
{
	for (new id = 0; id < MAX_DYNAMIC_ROBBERY; id ++)
	{
		if (GetPlayerWeapon(playerid) >= 22 && GetPlayerWeapon(playerid) <= 45 && RobberyData[id][robberyObjectID] == objectid)
        {
            new count, count2, Float:px, Float:py, Float:pz;
            GetPlayerPos(playerid, px, py, pz);

            foreach(new i : Player) if (AccountData[i][pSpawned])
            {
                if(AccountData[i][pFaction] == FACTION_POLISI && AccountData[i][pDutyPD]) count ++;
                if(AccountData[i][pFaction] == FACTION_EMS && AccountData[i][pDutyEms]) count2 ++;
            }
            if(count >= 0 && count2 >= 1) 
            {
                if(DurringRobbery[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang merampok warung!");
                if(g_RobberyTime != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Robbery Sedang Delay, anda harus menunggu %d menit untuk bisa robbery kembali!", g_RobberyTime/60));

                DurringRobbery[playerid] = true;
                AccountData[playerid][pRobMin] = 420;
                g_RobberyTime = 2400;
                SendClientMessageToAllEx(-1, "{201EE5}POLICE:{FFFFFF} Telah terjadi perampokan di %s. Warga harap menjauh dari area perampokan!", GetLocation(px, py, pz));
                
                foreach(new i : Player) if (AccountData[i][pSpawned])
                {
                    if(AccountData[i][pFaction] == FACTION_POLISI && AccountData[i][pDutyPD])
                    {
                        static shstr[255];
                        format(shstr, sizeof(shstr), "Telah terjadi perampokan warung di~n~%s", GetLocation(px, py, pz));
                        RobberyShowTD(i, shstr);
                        
                        SetPlayerRaceCheckpoint(i, 1, px, py, pz, 0.0, 0.0, 0.0, 5.0);
                        Warning(i, "Lokasi warung yang sedang dirampok telah ditandai pada blip di map!");
                    }
                }
            }
            else return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 Polisi Duty & 2 EMS Duty");
        }
    }
    return 1;
}
/*hook OnPlayerShootDynObj(playerid, weaponid, STREAMER_TAG_OBJECT:objectid, Float:x, Float:y, Float:z)
{
    for (new id = 0; id < MAX_DYNAMIC_ROBBERY; id ++)
    {
        if (GetPlayerWeapon(playerid) >= 22 && GetPlayerWeapon(playerid) <= 45 && RobberyData[id][robberyObjectID] == objectid)
        {
            new Float:px, Float:py, Float:pz;
            GetPlayerPos(playerid, px, py, pz);

            if(DurringRobbery[playerid]) 
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang merampok warung!");

            if(g_RobberyTime != 0) 
                return ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Robbery Sedang Delay, anda harus menunggu %d menit untuk bisa robbery kembali!", g_RobberyTime/60));

            DurringRobbery[playerid] = true;
            AccountData[playerid][pRobMin] = 100;
            g_RobberyTime = 2400;

            SendClientMessageToAllEx(-1, "{201EE5}POLICE:{FFFFFF} Telah terjadi perampokan di %s. Warga harap menjauh dari area perampokan!", GetLocation(px, py, pz));

            foreach(new i : Player) 
            {
                if (AccountData[i][pSpawned] && AccountData[i][pFaction] == FACTION_POLISI && AccountData[i][pDutyPD])
                {
                    static shstr[255];
                    format(shstr, sizeof(shstr), "Telah terjadi perampokan warung di~n~%s", GetLocation(px, py, pz));
                    RobberyShowTD(i, shstr);
                    
                    SetPlayerRaceCheckpoint(i, 1, px, py, pz, 0.0, 0.0, 0.0, 5.0);
                    Warning(i, "Lokasi warung yang sedang dirampok telah ditandai pada blip di map!");
                }
            }
        }
    }
    return 1;
}*/
hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    if(AccountData[playerid][EditingROBERID] != -1 && Iter_Contains(Robbery, AccountData[playerid][EditingROBERID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new etid = AccountData[playerid][EditingROBERID];
	        RobberyData[etid][robberyPos][0] = x;
	        RobberyData[etid][robberyPos][1] = y;
	        RobberyData[etid][robberyPos][2] = z;
	        RobberyData[etid][robberyRot][0] = rx;
	        RobberyData[etid][robberyRot][1] = ry;
	        RobberyData[etid][robberyRot][2] = rz;

	        SetDynamicObjectPos(objectid, RobberyData[etid][robberyPos][0], RobberyData[etid][robberyPos][1], RobberyData[etid][robberyPos][2]);
	        SetDynamicObjectRot(objectid, RobberyData[etid][robberyRot][0], RobberyData[etid][robberyRot][1], RobberyData[etid][robberyRot][2]);

            Robbery_Rebuild(etid);
		    Robbery_Save(etid);
	        AccountData[playerid][EditingROBERID] = -1;
	    }
	    if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new etid = AccountData[playerid][EditingROBERID];
	        SetDynamicObjectPos(objectid, RobberyData[etid][robberyPos][0], RobberyData[etid][robberyPos][1], RobberyData[etid][robberyPos][2]);
	        SetDynamicObjectRot(objectid, RobberyData[etid][robberyRot][0], RobberyData[etid][robberyRot][1], RobberyData[etid][robberyRot][2]);
	        AccountData[playerid][EditingROBERID] = -1;
	    }
	}
    return 1;
}

FUNC::RobberyShowTD(playerid, text[])
{
	if (GetPVarInt(playerid, "ShowRobbery") != -1)
	{
		TextDrawHideForPlayer(playerid, RobberyGlobalTD[0]);
		TextDrawHideForPlayer(playerid, RobberyGlobalTD[1]);
		TextDrawHideForPlayer(playerid, RobberyGlobalTD[2]);
		TextDrawHideForPlayer(playerid, RobberyGlobalTD[3]);
		TextDrawHideForPlayer(playerid, RobberyGlobalTD[4]);
		KillTimer(GetPVarInt(playerid, "ShowRobbery"));
	}
	TextDrawSetString(RobberyGlobalTD[4], text);
	TextDrawShowForPlayer(playerid, RobberyGlobalTD[0]);
	TextDrawShowForPlayer(playerid, RobberyGlobalTD[1]);
	TextDrawShowForPlayer(playerid, RobberyGlobalTD[2]);
	TextDrawShowForPlayer(playerid, RobberyGlobalTD[3]);
	TextDrawShowForPlayer(playerid, RobberyGlobalTD[4]);
	SetPVarInt(playerid, "ShowRobbery", SetTimerEx("HideRobbery", 10000, false, "d", playerid));
	return 1;
}

FUNC::HideRobbery(playerid)
{
	SetPVarInt(playerid, "ShowRobbery", -1);
	TextDrawHideForPlayer(playerid, RobberyGlobalTD[0]);
	TextDrawHideForPlayer(playerid, RobberyGlobalTD[1]);
	TextDrawHideForPlayer(playerid, RobberyGlobalTD[2]);
	TextDrawHideForPlayer(playerid, RobberyGlobalTD[3]);
	TextDrawHideForPlayer(playerid, RobberyGlobalTD[4]);
}

ptask Robbery_Update[1000](playerid)
{
    if(!AccountData[playerid][IsLoggedIn] ||
        !AccountData[playerid][pSpawned]) return 0;

    if(DurringRobbery[playerid])
    {
        if(AccountData[playerid][pRobMin] > 0)
        {
            AccountData[playerid][pRobMin]--; 

            if(AccountData[playerid][pRobMin] <= 0) 
            {
                new rands = RandomEx(2500, 4000);
                AccountData[playerid][pRedMoney] += rands;
                AccountData[playerid][pRobMin] = 0;
                DurringRobbery[playerid] = false;
                PlayerTextDrawHide(playerid, RobberyTextTD[playerid][0]);

                SendClientMessageEx(playerid, -1, "[i] Anda berhasil merampok warung, dan anda mendapatkan "RED"%s"WHITE" uang merah hasil merampok", FormatMoney(rands));
            }
            else
            {
                static string[512];
                new hours, minutes, seconds;
                GetElapsedTime(AccountData[playerid][pRobMin], hours, minutes, seconds);
                format(string, sizeof string, "Mohon tetap diwarung~n~selama %02d menit %02d detik", minutes, seconds);
                PlayerTextDrawSetString(playerid, RobberyTextTD[playerid][0], string);
                PlayerTextDrawShow(playerid, RobberyTextTD[playerid][0]);
            }
        }
    }
    return 1;
}

task RobberyDelay_Update[1000]()
{
	if(g_RobberyTime > 0)
	{
		g_RobberyTime --;
		if(!g_RobberyTime)
		{
			g_RobberyTime = 0;
		}
	}
	return 1;
}