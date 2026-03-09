#define TIME_TO_NEXT_CHECK              (30)
#define MAXIMUM_REPORTED_CHEAT          (5)

#include <YSI\y_hooks>

new 
    airbreak_anticheat[MAX_PLAYERS],
    vehairbreak_anticheat[MAX_PLAYERS],
    teleport_anticheat[MAX_PLAYERS],
    vehteleport_anticheat[MAX_PLAYERS],
    vehhealthhack_anticheat[MAX_PLAYERS],
    healthhack_anticheat[MAX_PLAYERS],
    flyhack_anticheat[MAX_PLAYERS],
    vehflyhack_anticheat[MAX_PLAYERS],
    armourhack_anticheat[MAX_PLAYERS],
    //
    tele_pickup_ac[MAX_PLAYERS],
    tele_pickup_ac_report_time[MAX_PLAYERS]
;

Anticheat_GetReportAmount(playerid, code)
{
    if (code == 6)
    {
        return tele_pickup_ac[playerid];
    }

    return 0;
}

bool:Anticheat_IsReportTimeExpired(playerid, code)
{
    new now = GetTickCount();

    if (code == 6)
    {
        return (tele_pickup_ac_report_time[playerid] <= now);
    }

    return true;
}

/*Anticheat_IncreaseReport(playerid, code, amount = 1)
{
    if (code == 6)
    {
        tele_pickup_ac[playerid] += amount;
    }

    return 1;
}*/

Anticheat_SetReport(playerid, code, value)
{
    if (code == 6)
    {
        tele_pickup_ac[playerid] = value;
    }

    return 1;
}

Anticheat_ReduceReport(playerid, code, amount = 1)
{
    if (code == 6)
    {
        new new_value = tele_pickup_ac[playerid] - amount;

        if (new_value < 0)
        {
            tele_pickup_ac[playerid] = 0;
        }
        else
        {
            tele_pickup_ac[playerid] = new_value;
        }
    }

    return 1;
}

Anticheat_SetReportTime(playerid, code, time)
{
    if (code == 6)
    {
        tele_pickup_ac_report_time[playerid] = time;
    }

    return 1;
}

Anticheat_IncreaseReportTime(playerid, code, time = TIME_TO_NEXT_CHECK)
{
    new now = GetTickCount();

    if (code == 6)
    {
        tele_pickup_ac_report_time[playerid] = now + (1000 * time);
    }

    return 1;
}

Anticheat_ResetReport(playerid, code)
{
    if (code == 6)
    {
        Anticheat_SetReport(playerid, code, 0);
        Anticheat_SetReportTime(playerid, code, 0);
    }
}

hook OnPlayerConnect(playerid)
{
    airbreak_anticheat{playerid} = 0;
    vehairbreak_anticheat{playerid} = 0;
    teleport_anticheat{playerid} = 0;
    vehteleport_anticheat{playerid} = 0;
    vehhealthhack_anticheat{playerid} = 0;
    healthhack_anticheat{playerid} = 0;
    flyhack_anticheat{playerid} = 0;
    vehflyhack_anticheat{playerid} = 0;
    armourhack_anticheat{playerid} = 0;
    Anticheat_ResetReport(playerid, 6);
}

forward RestoreHealth(playerid, Float:health);
forward RestoreArmour(playerid, Float:armour);
forward OnCheatDetected(playerid, ip_address[], type, code);


public OnCheatDetected(playerid, ip_address[], type, code)
{
    if(!IsPlayerConnected(playerid))
        return 0;

    switch(code)
    {
        case 0: {
            SendAdminMessage(X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" kemungkinan menggunakan foot airbreak hack.", ReturnName(playerid), playerid);
        }
        case 1: {
            SendAdminMessage(X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" kemungkinan menggunakan vehicle airbreak hack.", ReturnName(playerid), playerid);
        }
        case 2: {
            if (!AccountData[playerid][pSpawned])
                return 0;
                
            new Float:x, Float:y, Float:z;
            new vw, int;
            AntiCheatGetPos(playerid, x, y, z);
            int = GetPlayerInterior(playerid); 
            vw = GetPlayerVirtualWorld(playerid);
            SetPlayerPos(playerid, x, y, z);
            SetPlayerVirtualWorld(playerid, vw);
            SetPlayerInterior(playerid, int);

            if(!AccountData[playerid][UsingDoor] && AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1)
            {
                if(teleport_anticheat{playerid}++ > 2) 
                {
                    AccountData[playerid][pInt] = int;
                    AccountData[playerid][pWorld] = vw;
                    SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan teleport hacks"YELLOW" [D: %.2f m]", ReturnName(playerid), playerid, GetPlayerDistanceFromPoint(playerid, x, y, z));
                    SendAdminMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan teleport hacks"YELLOW" [D: %.2f m]", ReturnName(playerid), playerid, GetPlayerDistanceFromPoint(playerid, x, y, z));
                    KickEx(playerid);
                }
                else 
                {
                    SendAdminMessage(X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" kemungkinan menggunakan teleport hack"YELLOW" [D: %.2f m]", ReturnName(playerid), playerid, GetPlayerDistanceFromPoint(playerid, x, y, z));
                }
            }
        }
        case 3: {
            new Float:x, Float:y, Float:z;
            new vw, int;
            AntiCheatGetVehiclePos(GetPlayerVehicleID(playerid), x, y, z);
            int = GetPlayerInterior(playerid);
            vw = GetPlayerVirtualWorld(playerid);
            SetVehiclePos(GetPlayerVehicleID(playerid), x, y, z);
            SetVehicleVirtualWorld(GetPlayerVehicleID(playerid), vw);
            LinkVehicleToInterior(GetPlayerVehicleID(playerid), int);

            if(teleport_anticheat{playerid}++ > 2 && AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1) 
            {
                AccountData[playerid][pInt] = int;
                AccountData[playerid][pWorld] = vw;
                SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan teleport hack "YELLOW"[D: %.2f m] [%s]", ReturnName(playerid), playerid, GetPlayerDistanceFromPoint(playerid, x, y, z), GetVehicleName(GetPlayerVehicleID(playerid)));
                SendAdminMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan teleport hack "YELLOW"[D: %.2f m] [%s]", ReturnName(playerid), playerid, GetPlayerDistanceFromPoint(playerid, x, y, z), GetVehicleName(GetPlayerVehicleID(playerid)));
                KickEx(playerid);
            }
            else 
            {
                SendAdminMessage(X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" diduga menggunakan teleport hack "YELLOW"[D: %.2f m] [%s]", ReturnName(playerid), playerid, GetPlayerDistanceFromPoint(playerid, x, y, z), GetVehicleName(GetPlayerVehicleID(playerid)));
            }
        }
        //case 4: SendAdminMessage(X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" kemungkinan menggunakan Overlight / Sobeit. Spec Firts!", ReturnName(playerid), playerid);
        case 4:
        {
            new vehicleid = GetPlayerVehicleID(playerid),
                vehindex = RETURN_INVALID_VEHICLE_ID;
            
            if((vehindex = Vehicle_ReturnID(vehicleid)) != RETURN_INVALID_VEHICLE_ID)
            {
                if(PlayerVehicle[vehindex][pVehLocked]) return 0;
            }

            if(vehicleid == JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle] || vehicleid == ShowroomVeh[playerid] || VehicleCore[vehicleid][vehAdmin])
                return 0;

            SendAdminMessage(X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" kemungkinan diduga menggunakan Troll Car / Sobeit. [Spec First!].", ReturnName(playerid), playerid);
        }
        case 5: SendAdminMessage(X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" kemungkinan menggunakan vehicle to player hack (sobeit)", ReturnName(playerid), playerid);
        case 7: {
            SendAdminMessage(X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" kemungkinan menggunakan fly hack.", ReturnName(playerid), playerid);
        }    
        case 8: {
           SendAdminMessage(X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" kemungkinan menggunakan vehicle fly hack.", ReturnName(playerid), playerid);
        }
        case 9: SendAdminMessage(X11_RED, "[AntiCheat]: "YELLOW"%s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan onfoot airbreak / teleport.", ReturnName(playerid), playerid), SendClientMessageEx(playerid, X11_RED, "[AntiCheat]: "YELLOW"%s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan onfoot airbreak / teleport.", ReturnName(playerid), playerid), KickEx(playerid);
        case 10: SendClientMessageEx(playerid, X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan vehicle speed hack.", ReturnName(playerid), playerid), SendAdminMessage(X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan vehicle speed hack.", ReturnName(playerid), playerid), KickEx(playerid);
        case 11: 
        {
            new Float:health;
            new vehicleid = AntiCheatGetVehicleID(playerid);
            if(vehicleid != ShowroomVeh[playerid])
            {
                AntiCheatGetVehicleHealth(vehicleid, health);
                SetValidVehicleHealth(vehicleid, health);
                SendAdminMessage(X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" kemungkinan menggunakan Vehicle Repair Hack "YELLOW"[%.1f]", ReturnName(playerid), playerid, health);
            }
        }
        case 12: 
        {
            new Float:health;
            AntiCheatGetHealth(playerid, health);
            SetTimerEx("RestoreHealth", 10, 0, "df", playerid, health);
        }
        /*case 13: 
        {
            new Float:armor;
            AntiCheatGetArmour(playerid, armor);
            SetTimerEx("RestoreArmour", 10, 0, "df", playerid, armor);

            SendAdminMessage(X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" kemungkinan menggunakan armour hack (Armour++).", ReturnName(playerid), playerid);
        }*///MarkhereAC
        case 14: return 0;
        case 15: 
        {
            if(gettime() > AccountData[playerid][pACTime] && AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1 && !AccountData[playerid][pInjured] && !IsPlayerInEvent(playerid) && !DurringHunting[playerid] && !InPool[playerid])
            {
                SendClientMessageEx(playerid, X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" diduga menggunakan weapon hack.", ReturnName(playerid), playerid);
                SendAdminMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" diduga menggunakan weapon hack.", ReturnName(playerid), playerid);
                KickEx(playerid);
            }
        }
        case 16: 
        {
            SendClientMessageEx(playerid, X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" diduga menggunakan add ammo hack.", ReturnName(playerid), playerid);
            SendAdminMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" diduga menggunakan add ammo hack.", ReturnName(playerid), playerid);
            //KickEx(playerid);
        }
        case 17: SendClientMessageEx(playerid, X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan infinite ammo hack.", ReturnName(playerid), playerid), SendAdminMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan infinite ammo hack.", ReturnName(playerid), playerid); //KickEx(playerid);
        case 19:
        {
            SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" diduga menggunakan Beton CS!", ReturnName(playerid), playerid);
            SendAdminMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" diduga menggunakan Beton CS!", ReturnName(playerid), playerid);
            //KickEx(playerid);
        }
        case 21: SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Invisible Hacks!", ReturnName(playerid), playerid), SendAdminMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Invisible Hacks!", ReturnName(playerid), playerid), KickEx(playerid);
        case 26: return 0;
        /*case 26:
        {
            if(!IsPlayerInEvent(playerid))
            {
                SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Rapid Fire!", ReturnName(playerid), playerid);
                SendAdminMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan Rapid Fire!", ReturnName(playerid), playerid);
                KickEx(playerid);
            }
        }*/
        case 27:
        {
            if(gettime() > AccountData[playerid][pACTime])
            {
                SendClientMessageEx(playerid, X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga Fake Spawn!", ReturnName(playerid), playerid);
                SendAdminMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga Fake Spawn!", ReturnName(playerid), playerid);
                KickEx(playerid);
            }
        }
        case 40: return 0;
        case 43..46: SendClientMessageEx(playerid, X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan crasher hack.", ReturnName(playerid), playerid), SendAdminMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan crasher hack.", ReturnName(playerid), playerid), KickEx(playerid);
        case 47: 
        {
            if(gettime() > AccountData[playerid][pACTime] && !IsPlayerInEvent(playerid) && !DurringHunting[playerid] && !InPool[playerid])
            {
                SendClientMessageEx(playerid, X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan fake weapon hack", ReturnName(playerid), playerid);
                SendAdminMessage(X11_RED, "[AntiCheat]"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena diduga menggunakan fake weapon hack", ReturnName(playerid), playerid);
                KickEx(playerid);
            }
        }
        case 52: return 0;

        default: 
        {
            new Float:x, Float:y, Float:z;
            new vw, int;
            //ngesave VW dan Interior
            //Masuk ke bank > set pos interior bank > anticheatgetpos(last position) > setplayerpos ke last position yang di get anti cheat, tapi tidak di set vw dan interior. 
            //bisa kena anti cheat karena jarak perpindahan dari luar ke dalam terlalu jauh
            AntiCheatGetPos(playerid, x, y, z);
            int = GetPlayerInterior(playerid);
            vw = GetPlayerVirtualWorld(playerid);
            SetPlayerVirtualWorld(playerid, vw);
            SetPlayerInterior(playerid, int);
            SetPlayerPos(playerid, x, y, z);


            AntiCheatKickWithDesync(playerid, code);
            SendAdminMessage(X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" (%s) type: %d code %d", ReturnName(playerid), playerid, ip_address, type, code);
        }
    }    
    return 1;
}

public RestoreHealth(playerid, Float:health)
{
    if(IsPlayerConnected(playerid))
        SetPlayerHealth(playerid, health);
}

public RestoreArmour(playerid, Float:armour)
{
    if(IsPlayerConnected(playerid))
        SetPlayerArmour(playerid, armour);
}