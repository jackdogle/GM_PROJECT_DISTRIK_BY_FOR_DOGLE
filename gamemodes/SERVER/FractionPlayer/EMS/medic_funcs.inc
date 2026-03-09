#include <YSI\y_hooks>

new StretcherEquipped[MAX_PLAYERS];
new StretcherHolding[MAX_PLAYERS];
new StretcherPlayerID[MAX_PLAYERS];
new StretcherTimer[MAX_PLAYERS];

FUNC::Float:DistanceBetweenPoints(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2)
{
	return floatadd(floatadd(floatsqroot(floatpower(floatsub(x1,x2),2)),floatsqroot(floatpower(floatsub(y1,y2),2))),floatsqroot(floatpower(floatsub(z1,z2),2)));
}

FUNC::Float:GetXYInFrontOfPlayer(playerid, &Float:X, &Float:Y, Float:distance)
{
	new Float:A;
	GetPlayerPos(playerid, X, Y, A);

	if(IsPlayerInAnyVehicle(playerid)) GetVehicleZAngle(GetPlayerVehicleID(playerid), A);
	else GetPlayerFacingAngle(playerid, A);

	X += (distance * floatsin(-A, degrees));
	Y += (distance * floatcos(-A, degrees));

	return A;
}

stock SpawnStretcher(playerid)
{
	new Float:angle;
	GetPlayerFacingAngle(playerid, angle);
	SetPlayerFacingAngle(playerid, angle + 180);

	AttachDynamicObjectToPlayer(StretcherEquipped[playerid], playerid, 0.0, 1.4, -1.0, 0.0, 0.0, 180.0);

    Info(playerid, "Sekarang kamu memiliki stretcher. gunakan "YELLOW"'/tandu'"WHITE" untuk actions lainnya.");
	return true;
}

FUNC::DestroyStretcher(playerid, objectid)
{
	DestroyDynamicObject(StretcherEquipped[playerid]);
	StretcherTimer[playerid] = -1;
	StretcherEquipped[playerid] = -1;
	StretcherHolding[playerid] = 0;
    return 1;
}

CMD:tandu(playerid, params[])
{
    if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota EMS!");
    if(!AccountData[playerid][pDutyEms]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus duty terlebih dahulu!");
		
	new action[24], playa = -1, string[128];
	if (sscanf(params, "s[24]S()[128]", action, string))
	{
        Syntax(playerid, "/tandu [entinity] (equip, drop, pickup, destroy, load, unload, ambulance)");
	    return 1;
	}
	new Float:pX,Float:pY,Float:pZ, Float:oX,Float:oY,Float:oZ;
	GetPlayerPos(playerid, pX, pY, pZ);
			
	if(!strcmp(action, "equip", true))
	{
        new vehicleid = GetNearestVehicle(playerid), Float:x, Float:y, Float:z;
        GetVehicleBoot(vehicleid, x, y, z);

        if(StretcherEquipped[playerid] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah menggunakan tandu!");
        if(!IsPlayerInRangeOfPoint(playerid, 2.5, x, y, z)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada dibelakang kendaraan EMS!");
        if(GetVehicleModel(vehicleid) != 416 && GetVehicleModel(vehicleid) != 442 && GetVehicleModel(vehicleid) != 490) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan tersebut bukan kendaraan EMS!");
			
		StretcherEquipped[playerid] = CreateDynamicObject(1997, pX, pY + 1.5, pZ - 1.0, 0.0, 0.0, 100.0);//2146
		StretcherHolding[playerid] = 1;
        SendRPMeAboveHead(playerid, "Mengeluarkan tandu dari kendaraan.", X11_PLUM1);
	}
	else if(!strcmp(action, "drop", true))
	{
		new Float:pXb, Float:pYb;
		new Float:Ang = GetXYInFrontOfPlayer(playerid, pXb, pYb, 1.7);

		if(StretcherHolding[playerid] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang tidak menggunakan Tandu!");
		if(StretcherPlayerID[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melepas tandu dengan pemain diatasnya!");

		DestroyDynamicObject(StretcherEquipped[playerid]);
		StretcherEquipped[playerid] = CreateDynamicObject(1997, pXb, pYb, pZ-1.0, 0.0, 0.0, Ang+180);
		StretcherHolding[playerid] = 0;
		StretcherTimer[playerid] = SetTimerEx("DestroyStretcher", 300000, 0, "ii", playerid, StretcherEquipped[playerid]);
		Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
        
        SendRPMeAboveHead(playerid, "Mengunci roda Tandu ditempatnya.", X11_PLUM1);
	}
	else if(!strcmp(action, "pickup", true))
	{
		GetDynamicObjectPos(StretcherEquipped[playerid],oX,oY,oZ);
		new Float:distance = DistanceBetweenPoints(pX,pY,pZ,oX,oY,oZ);
		
		if(!IsValidDynamicObject(StretcherEquipped[playerid])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus memiliki tandu!");
		if(StretcherPlayerID[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengambil tandu dengan pemain diatasnya!");
		if(StretcherHolding[playerid] == 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang menggunakan tandu!");
		if(distance > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus dekat dengan tandu!");

		KillTimer(StretcherTimer[playerid]);
		StretcherTimer[playerid] = -1;
		StretcherHolding[playerid] = 2;
	}
	else if(!strcmp(action, "destroy", true))
	{
		if(!IsValidDynamicObject(StretcherEquipped[playerid])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki tandu untuk dimasukkan ke kendaraan!");
		if(StretcherPlayerID[playerid] >= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Harap turunkan tandu sebelum menyimpannya!");

		new Float:vX, Float:vY, Float:vZ;
		for(new v = 1, x = GetVehiclePoolSize(); v <= x; v++)
		{
			if(GetVehicleModel(v) == 416 && GetVehicleModel(v) == 442 && GetVehicleModel(v) == 490)
			{
				GetVehiclePos(v, vX, vY, vZ);
				if(IsPlayerInRangeOfPoint(playerid, 10.0, vX, vY, vZ))
				{
					DestroyDynamicObject(StretcherEquipped[playerid]);
					StretcherEquipped[playerid] = 0;
					StretcherHolding[playerid] = 0;
                    SendRPMeAboveHead(playerid, "Memasukkan tandu kedalam kendaraan", X11_PLUM1);
                    return 1;
				}
			}
		}
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada didekat kendaraan EMS untuk menyimpan tandu!");
	}
	else if(!strcmp(action, "load", true))
	{
		if(!IsValidDynamicObject(StretcherEquipped[playerid])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengeluarkan tandu untuk meletakkan seseorang diatasnya!");
		if(StretcherPlayerID[playerid] >= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah meletakkan orang lain di atas tandu!");
	    if (sscanf(string, "u", playa)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/tandu load [name/playerid]");	 
		if(playa == INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
		if(playa == playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat meletakkan diri anda sendiri ke tandu!");
		if(StretcherEquipped[playa] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak boleh menempatkan seseorang dengan tandu di atas tandu!");
	    if(StretcherHolding[playerid] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus memegang tandu!");

		new Float:tX,Float:tY,Float:tZ;
		GetPlayerPos(playa,tX,tY,tZ);
		
		if(!IsPlayerInRangeOfPoint(playerid,3.5,tX,tY,tZ))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus dekat dengan pemain tersebut!");

		StretcherPlayerID[playerid] = playa;
		ApplyAnimation(playa,"BEACH", "bather", 4.0, 1, 0, 0, 1, -1, 1);
        SendRPMeAboveHead(playerid, "Meletakkan seseorang ke atas tandu.", X11_PLUM1);
        Info(playerid, "%s sekarang berada di atas tandu milik anda. Gunakan "YELLOW"'/tandu unload'"WHITE" untuk menurunkan pemain tersebut!", ReturnName(StretcherPlayerID[playerid]));
		Info(StretcherPlayerID[playerid] ,"%s meletakkan anda ke atas Tandu.",ReturnName(playerid));
	}
	else if(!strcmp(action, "unload", true))
	{
		if(!IsValidDynamicObject(StretcherEquipped[playerid])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengeluarkan tandu untuk menggunakan ini!");
		if(StretcherPlayerID[playerid] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada pemain manapun diatas tandu anda!");
		if(StretcherHolding[playerid] == 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus memegang tandu!");

		new Float:playerpos[4];
		TogglePlayerControllable(StretcherPlayerID[playerid], 1);
		GetPlayerPos(playerid, playerpos[0], playerpos[1], playerpos[2]);
		GetXYInFrontOfPlayer(playerid, playerpos[0], playerpos[1], -2);
		SetPlayerPos(StretcherPlayerID[playerid], playerpos[0], playerpos[1], playerpos[2]);
		ClearAnimations(StretcherPlayerID[playerid], 1);
        Info(playerid, "%s telah anda turunkan dari atas Tandu anda.", ReturnName(StretcherPlayerID[playerid]));
        Info(StretcherPlayerID[playerid], "%s telah menurunkan anda dari atas tandunya", ReturnName(playerid));
		StretcherPlayerID[playerid] = -1;
	}
	else if(!strcmp(action, "ambulance", true))
	{
		if(!IsValidDynamicObject(StretcherEquipped[playerid])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengeluarkan tandu untuk menggunakan ini!");
		if(StretcherPlayerID[playerid] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada pemain manapun diatas tandu anda!");

		new Float:vX, Float:vY, Float:vZ;
		for(new v = 1, x = GetVehiclePoolSize(); v <= x; v++)
		{
			if(GetVehicleModel(v) == 416)
			{
				GetVehiclePos(v, vX, vY, vZ);
				if(IsPlayerInRangeOfPoint(playerid, 10.0, vX, vY, vZ))
				{
					new seatid = 2;
					foreach(new i : Player)
					{
						if(GetPlayerVehicleID(i) == v)
						{
							if(GetPlayerVehicleSeat(i) == 2) seatid = 3;
							if(GetPlayerVehicleSeat(i) == 3 && seatid == 3) seatid = -1;
						}
					}
					if(seatid == -1)
						return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kursi kosong di belakang Ambulans ini!");

					PutPlayerInVehicle(StretcherPlayerID[playerid], v, seatid);
					TogglePlayerControllable(StretcherPlayerID[playerid], 1);
                    SendRPMeAboveHead(playerid, "Memasukkan seseorang ke dalam mobil Ambulance", X11_PLUM1);

					DestroyDynamicObject(StretcherEquipped[playerid]);
					StretcherEquipped[playerid] = 0;
					StretcherPlayerID[playerid] = -1;
					StretcherHolding[playerid] = 0;
				}
			}
		}
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada didekat kendaraan Ambulance untuk memasukkan seseorang!");
		return 1;
	}

	return 1;
}

hook OnPlayerConnect(playerid)
{
    DestroyDynamicObject(StretcherEquipped[playerid]);
	StretcherTimer[playerid] = -1;
	StretcherEquipped[playerid] = -1;
	StretcherHolding[playerid] = 0;
    StretcherPlayerID[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(IsValidDynamicObject(StretcherEquipped[playerid])) DestroyDynamicObject(StretcherEquipped[playerid]);
	StretcherTimer[playerid] = -1;
	StretcherEquipped[playerid] = -1;
	StretcherHolding[playerid] = 0;
    StretcherPlayerID[playerid] = -1;
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    if(IsValidDynamicObject(StretcherEquipped[playerid]))
	{
		DestroyDynamicObject(StretcherEquipped[playerid]);
		StretcherHolding[playerid] = 0;
		if(StretcherPlayerID[playerid] >= 0)
		{
			TogglePlayerControllable(StretcherPlayerID[playerid], 1);
			ClearAnimations(StretcherPlayerID[playerid], 1);
			StretcherPlayerID[playerid] = -1;
		}
	}
    return 1;
}

hook OnPlayerUpdate(playerid)
{
    if(StretcherHolding[playerid] == 2)
	{
		new Float:zX, Float:zY, Float:zZ, Float:Ang;
		GetPlayerPos(playerid, zX, zY, zZ);
		GetXYInFrontOfPlayer(playerid, zX, zY, 1.6);
		GetPlayerFacingAngle(playerid, Ang);

		SetDynamicObjectPos(StretcherEquipped[playerid], zX, zY, zZ - 1.0);
		SetDynamicObjectRot(StretcherEquipped[playerid], 0.0, 0.0, Ang-180.0);
	}
	if(IsValidDynamicObject(StretcherEquipped[playerid]) && StretcherPlayerID[playerid] >= 0)
	{
		if(IsPlayerConnected(StretcherPlayerID[playerid]))
		{
			new Float:playerpos[4];
			TogglePlayerControllable(StretcherPlayerID[playerid], 0);
			GetPlayerFacingAngle(playerid, playerpos[3]);
			SetPlayerFacingAngle(StretcherPlayerID[playerid], playerpos[3]);
			GetPlayerPos(playerid, playerpos[0], playerpos[1], playerpos[2]);
			GetXYInFrontOfPlayer(playerid, playerpos[0], playerpos[1], 2.0);
			SetPlayerPos(StretcherPlayerID[playerid], playerpos[0], playerpos[1], playerpos[2] + 0.5);
			SetCameraBehindPlayer(StretcherPlayerID[playerid]);
			SetPlayerVirtualWorld(StretcherPlayerID[playerid], GetPlayerVirtualWorld(playerid));
			SetPlayerInterior(StretcherPlayerID[playerid], GetPlayerInterior(playerid));
			ApplyAnimation(StretcherPlayerID[playerid],"BEACH", "bather", 4.0, 1, 0, 0, 1, -1, 1);
		}
		else StretcherPlayerID[playerid] = -1;
	}
    return 1;
}