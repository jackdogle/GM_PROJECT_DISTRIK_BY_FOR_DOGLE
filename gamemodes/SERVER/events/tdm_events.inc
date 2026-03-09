#include <YSI\y_hooks>

new Text:eventTextdraws[21];
new Timer:haupdate[MAX_PLAYERS];    

enum 	_:E_EVENT_TEAM
{
	NONE_TEAM = 0,
	TEAM_A,
	TEAM_B
}

enum    E_EVENT 
{
    bool: eventCreated,
    bool: eventStarted,
    bool: eventOpened,
    
    eventSelectTeam,
    eventWinner,
    eventTargetScore,
    eventPrize,
    eventPrizeParticipation,
    eventTime,

    Float:eventHealth,
    Float:eventArmour,

    eventInterior,
    eventWorld,
    eventWeapon1[2],
    eventWeapon2[2],
    eventWeapon3[2],

    //Team
    eventSkin[2],
    eventTeamScore[2],
    eventScore[2],
    Float:eventSpawnX[2],
    Float:eventSpawnY[2],
    Float:eventSpawnZ[2],
    Float:eventSpawnA[2]
};

new EventData[E_EVENT];

stock IsPlayerInEvent(playerid)
{
    return EventJoin[playerid];
}

stock GiveEventWeaponToPlayer(playerid, weaponid, ammo) {
    GivePlayerWeapon(playerid, weaponid, ammo);
    return 1;
}

stock ResetEventWeapons(playerid) {
    ResetPlayerWeapons(playerid);
    AccountData[playerid][pACTime] = gettime() + 2;
    return 1;
}

stock eventCount()
{
    new count = 0;
    foreach(new i : Player) if (IsPlayerInEvent(i)) {
        count ++;
    }
    return count;
}

stock EventDialogShow(playerid)
{
    new 
        list[1026],
        statuspos1[128],
        statuspos2[128];
    
    if(EventData[eventSpawnX][0] != 0.0 || EventData[eventSpawnY][0] != 0.0 || EventData[eventSpawnZ][0] != 0.0) {
        statuspos1 = ""GREEN"Ready";
    } else {
        statuspos1 = ""RED"Unassigned";
    }
    
    if(EventData[eventSpawnX][1] != 0.0 || EventData[eventSpawnY][1] != 0.0 || EventData[eventSpawnZ][1] != 0.0) {
        statuspos2 = ""GREEN"Ready";
    } else {
        statuspos2 = ""RED"Unassigned";
    }
    
    format(list, sizeof(list), "Implementation\tStatus\n");
    format(list, sizeof(list), "%sRed Team Skin\t%d\n", list, EventData[eventSkin][0]);
    format(list, sizeof(list), "%sRed Team spawn point\t%s\n", list, statuspos1);
    format(list, sizeof(list), "%sRed Team Weapon #1\t%s\n", list, ReturnWeaponName(EventData[eventWeapon1][0]));
    format(list, sizeof(list), "%sRed Team Weapon #2\t%s\n", list, ReturnWeaponName(EventData[eventWeapon2][0]));
    format(list, sizeof(list), "%sRed Team Weapon #3\t%s\n", list, ReturnWeaponName(EventData[eventWeapon3][0]));
    format(list, sizeof(list), "%sBlue Team Skin\t%d\n", list, EventData[eventSkin][1]);
    format(list, sizeof(list), "%sBlue Team spawn point\t%s\n", list, statuspos2);
    format(list, sizeof(list), "%sBlue Team Weapon #1\t%s\n", list, ReturnWeaponName(EventData[eventWeapon1][1]));
    format(list, sizeof(list), "%sBlue Team Weapon #2\t%s\n", list, ReturnWeaponName(EventData[eventWeapon2][1]));
    format(list, sizeof(list), "%sBlue Team Weapon #3\t%s\n", list, ReturnWeaponName(EventData[eventWeapon3][1]));
    format(list, sizeof(list), "%sArena WWID\t%d\n", list, EventData[eventWorld]);
    format(list, sizeof(list), "%sArena Interior\t%d\n", list, EventData[eventInterior]);
    format(list, sizeof(list), "%sTime limitation (minutes)\t%d minute(s)\n", list, EventData[eventTime]);
    format(list, sizeof(list), "%sTarget Score\t%d\n", list, EventData[eventTargetScore]);
    format(list, sizeof(list), "%sHealth Event\t%.2f\n", list, EventData[eventHealth]);
    format(list, sizeof(list), "%sArmour Event\t%.2f\n", list, EventData[eventArmour]);
    format(list, sizeof(list), "%sParticipation Prize\t"GREEN"%s\n", list, FormatMoney(EventData[eventPrizeParticipation]));
    format(list, sizeof(list), "%sWinner Prize\t"GREEN"%s\n", list, FormatMoney(EventData[eventPrize]));
    ShowPlayerDialog(playerid, DIALOG_EVENT_SETTING, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- TDM Event Creator", list, "Setup", "Batal");
    return 1;
}

stock eventTextdraw(playerid)
{
    if(IsPlayerInEvent(playerid)) 
    {
        TextDrawSetString(eventTextdraws[18], sprintf("%d", EventData[eventTargetScore]));
        TextDrawSetString(eventTextdraws[19], sprintf("%d", EventData[eventScore][0]));
        TextDrawSetString(eventTextdraws[20], sprintf("%d", EventData[eventScore][1]));

        TextDrawShowForPlayer(playerid, eventTextdraws[18]);
        TextDrawShowForPlayer(playerid, eventTextdraws[19]);
        TextDrawShowForPlayer(playerid, eventTextdraws[20]);       
    }
    return 1;
}

timer eventSpawnProp[500](playerid)
{
    if(AccountData[playerid][IsLoggedIn] && IsPlayerInEvent(playerid))
    {
        SetPlayerHealth(playerid, EventData[eventHealth]);
        SetPlayerArmour(playerid, EventData[eventArmour]);
    }
}

forward eventSpawnTimer(playerid);
public eventSpawnTimer(playerid)
{
    SetPlayerVirtualWorld(playerid, EventData[eventWorld]);
    TogglePlayerControllable(playerid, 1);
    GameTextForPlayer(playerid, "~g~Mulai", 2000, 6);

    EventWaitingSpawn[playerid] = 0;
    EventSpawn(playerid);
    return 1;
}

stock EventSpawn(playerid)
{
    if(IsPlayerInEvent(playerid))
    {
        Player_ToggleEventAntiCheat(playerid, false);
        SetPlayerPos(playerid, EventData[eventSpawnX][EventTeam[playerid] - 1], EventData[eventSpawnY][EventTeam[playerid] - 1], EventData[eventSpawnZ][EventTeam[playerid] - 1]);
        SetPlayerFacingAngle(playerid, EventData[eventSpawnA][EventTeam[playerid] - 1]);
        SetCameraBehindPlayer(playerid);

        SetPlayerSkin(playerid, EventData[eventSkin][EventTeam[playerid] - 1]);

        SetPlayerInterior(playerid, EventData[eventInterior]);
        SetPlayerVirtualWorld(playerid, EventData[eventWorld]);

        if(EventTeam[playerid] == TEAM_A) {
            SetPlayerColor(playerid, RemoveAlpha(X11_RED));
            GiveEventWeaponToPlayer(playerid, EventData[eventWeapon1][0], 600);
            GiveEventWeaponToPlayer(playerid, EventData[eventWeapon2][0], 600);
            GiveEventWeaponToPlayer(playerid, EventData[eventWeapon3][0], 600);
        } else {
            SetPlayerColor(playerid, RemoveAlpha(COLOR_BLUE));
            GiveEventWeaponToPlayer(playerid, EventData[eventWeapon1][1], 600);
            GiveEventWeaponToPlayer(playerid, EventData[eventWeapon2][1], 600);
            GiveEventWeaponToPlayer(playerid, EventData[eventWeapon3][1], 600);
        }

        haupdate[playerid] = defer eventSpawnProp[500](playerid);

        if(EventWaitingSpawn[playerid])
        {
            SetPlayerVirtualWorld(playerid, (playerid+1));
            TogglePlayerControllable(playerid, 0);
            SetPlayerPos(playerid, EventData[eventSpawnX][EventTeam[playerid] - 1], EventData[eventSpawnY][EventTeam[playerid] - 1], EventData[eventSpawnZ][EventTeam[playerid] - 1]);
            SetTimerEx("eventSpawnTimer", 3000, false, "d", playerid);
        }
    }
    return 1;
}

EventLeave(playerid)
{
    EventTeam[playerid] = NONE_TEAM;
    ResetEventWeapons(playerid);

    EventJoin[playerid] = false;

    for(new id = 0; id != 21; id ++) {
        TextDrawHideForPlayer(playerid, eventTextdraws[id]);
    }
    
    SetPlayerTeam(playerid, NO_TEAM);
    SetPlayerInterior(playerid, AccountData[playerid][pInt]);
    SetPlayerVirtualWorld(playerid, AccountData[playerid][pWorld]);

    if(GetPlayerState(playerid) == PLAYER_STATE_WASTED)
    {
        SetSpawnInfo(playerid, NO_TEAM, AccountData[playerid][pSkin], AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], 0.0, 0, 0, 0, 0, 0, 0);
    }
    SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 2000);

    SetPlayerHealth(playerid, AccountData[playerid][pHealth]);
    SetPlayerArmour(playerid, AccountData[playerid][pArmour]);

    if(AccountData[playerid][pUsingUniform]) 
    {
        SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
    }
    else 
    {
        SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
    }
    SetPlayerColor(playerid, COLOR_WHITE);
    Player_ToggleEventAntiCheat(playerid, true);
    SetTimerEx("TimersSpawn", 7000, false, "d", playerid);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    EventJoin[playerid] = 0;
    EventTeam[playerid] = 0;
    return 1;
}

// hook OnPlayerDisconnect(playerid)
// {
//     if(IsPlayerInEvent(playerid))
//     {
//         ResetEventWeapons(playerid);
//         EventJoin[playerid] = 0;
//         EventData[eventArmour] = 0;
//         SetPlayerArmour(playerid, EventData[eventArmour]);
//     }
//     return 1;
// }

hook OnGameModeInit()
{
    eventTextdraws[0] = TextDrawCreate(226.000, 16.000, "LD_BEAT:chit");
    TextDrawTextSize(eventTextdraws[0], 14.000, 18.000);
    TextDrawAlignment(eventTextdraws[0], 1);
    TextDrawColor(eventTextdraws[0], -16776961);
    TextDrawSetShadow(eventTextdraws[0], 0);
    TextDrawSetOutline(eventTextdraws[0], 0);
    TextDrawBackgroundColor(eventTextdraws[0], 255);
    TextDrawFont(eventTextdraws[0], 4);
    TextDrawSetProportional(eventTextdraws[0], 1);

    eventTextdraws[1] = TextDrawCreate(234.000, 19.000, "LD_BUM:blkdot");
    TextDrawTextSize(eventTextdraws[1], 37.000, 23.000);
    TextDrawAlignment(eventTextdraws[1], 1);
    TextDrawColor(eventTextdraws[1], -16776961);
    TextDrawSetShadow(eventTextdraws[1], 0);
    TextDrawSetOutline(eventTextdraws[1], 0);
    TextDrawBackgroundColor(eventTextdraws[1], 255);
    TextDrawFont(eventTextdraws[1], 4);
    TextDrawSetProportional(eventTextdraws[1], 1);

    eventTextdraws[2] = TextDrawCreate(264.000, 16.000, "LD_BEAT:chit");
    TextDrawTextSize(eventTextdraws[2], 14.000, 18.000);
    TextDrawAlignment(eventTextdraws[2], 1);
    TextDrawColor(eventTextdraws[2], -16776961);
    TextDrawSetShadow(eventTextdraws[2], 0);
    TextDrawSetOutline(eventTextdraws[2], 0);
    TextDrawBackgroundColor(eventTextdraws[2], 255);
    TextDrawFont(eventTextdraws[2], 4);
    TextDrawSetProportional(eventTextdraws[2], 1);

    eventTextdraws[3] = TextDrawCreate(264.000, 27.000, "LD_BEAT:chit");
    TextDrawTextSize(eventTextdraws[3], 14.000, 18.000);
    TextDrawAlignment(eventTextdraws[3], 1);
    TextDrawColor(eventTextdraws[3], -16776961);
    TextDrawSetShadow(eventTextdraws[3], 0);
    TextDrawSetOutline(eventTextdraws[3], 0);
    TextDrawBackgroundColor(eventTextdraws[3], 255);
    TextDrawFont(eventTextdraws[3], 4);
    TextDrawSetProportional(eventTextdraws[3], 1);

    eventTextdraws[4] = TextDrawCreate(226.000, 27.000, "LD_BEAT:chit");
    TextDrawTextSize(eventTextdraws[4], 14.000, 18.000);
    TextDrawAlignment(eventTextdraws[4], 1);
    TextDrawColor(eventTextdraws[4], -16776961);
    TextDrawSetShadow(eventTextdraws[4], 0);
    TextDrawSetOutline(eventTextdraws[4], 0);
    TextDrawBackgroundColor(eventTextdraws[4], 255);
    TextDrawFont(eventTextdraws[4], 4);
    TextDrawSetProportional(eventTextdraws[4], 1);

    eventTextdraws[5] = TextDrawCreate(228.000, 25.000, "LD_BUM:blkdot");
    TextDrawTextSize(eventTextdraws[5], 48.000, 12.000);
    TextDrawAlignment(eventTextdraws[5], 1);
    TextDrawColor(eventTextdraws[5], -16776961);
    TextDrawSetShadow(eventTextdraws[5], 0);
    TextDrawSetOutline(eventTextdraws[5], 0);
    TextDrawBackgroundColor(eventTextdraws[5], 255);
    TextDrawFont(eventTextdraws[5], 4);
    TextDrawSetProportional(eventTextdraws[5], 1);

    eventTextdraws[6] = TextDrawCreate(282.000, 4.000, "LD_BEAT:chit");
    TextDrawTextSize(eventTextdraws[6], 14.000, 18.000);
    TextDrawAlignment(eventTextdraws[6], 1);
    TextDrawColor(eventTextdraws[6], 255);
    TextDrawSetShadow(eventTextdraws[6], 0);
    TextDrawSetOutline(eventTextdraws[6], 0);
    TextDrawBackgroundColor(eventTextdraws[6], 255);
    TextDrawFont(eventTextdraws[6], 4);
    TextDrawSetProportional(eventTextdraws[6], 1);

    eventTextdraws[7] = TextDrawCreate(290.000, 7.000, "LD_BUM:blkdot");
    TextDrawTextSize(eventTextdraws[7], 37.000, 23.000);
    TextDrawAlignment(eventTextdraws[7], 1);
    TextDrawColor(eventTextdraws[7], 255);
    TextDrawSetShadow(eventTextdraws[7], 0);
    TextDrawSetOutline(eventTextdraws[7], 0);
    TextDrawBackgroundColor(eventTextdraws[7], 255);
    TextDrawFont(eventTextdraws[7], 4);
    TextDrawSetProportional(eventTextdraws[7], 1);

    eventTextdraws[8] = TextDrawCreate(320.000, 4.000, "LD_BEAT:chit");
    TextDrawTextSize(eventTextdraws[8], 14.000, 18.000);
    TextDrawAlignment(eventTextdraws[8], 1);
    TextDrawColor(eventTextdraws[8], 255);
    TextDrawSetShadow(eventTextdraws[8], 0);
    TextDrawSetOutline(eventTextdraws[8], 0);
    TextDrawBackgroundColor(eventTextdraws[8], 255);
    TextDrawFont(eventTextdraws[8], 4);
    TextDrawSetProportional(eventTextdraws[8], 1);

    eventTextdraws[9] = TextDrawCreate(320.000, 15.000, "LD_BEAT:chit");
    TextDrawTextSize(eventTextdraws[9], 14.000, 18.000);
    TextDrawAlignment(eventTextdraws[9], 1);
    TextDrawColor(eventTextdraws[9], 255);
    TextDrawSetShadow(eventTextdraws[9], 0);
    TextDrawSetOutline(eventTextdraws[9], 0);
    TextDrawBackgroundColor(eventTextdraws[9], 255);
    TextDrawFont(eventTextdraws[9], 4);
    TextDrawSetProportional(eventTextdraws[9], 1);

    eventTextdraws[10] = TextDrawCreate(282.000, 15.000, "LD_BEAT:chit");
    TextDrawTextSize(eventTextdraws[10], 14.000, 18.000);
    TextDrawAlignment(eventTextdraws[10], 1);
    TextDrawColor(eventTextdraws[10], 255);
    TextDrawSetShadow(eventTextdraws[10], 0);
    TextDrawSetOutline(eventTextdraws[10], 0);
    TextDrawBackgroundColor(eventTextdraws[10], 255);
    TextDrawFont(eventTextdraws[10], 4);
    TextDrawSetProportional(eventTextdraws[10], 1);

    eventTextdraws[11] = TextDrawCreate(284.000, 13.000, "LD_BUM:blkdot");
    TextDrawTextSize(eventTextdraws[11], 48.000, 12.000);
    TextDrawAlignment(eventTextdraws[11], 1);
    TextDrawColor(eventTextdraws[11], 255);
    TextDrawSetShadow(eventTextdraws[11], 0);
    TextDrawSetOutline(eventTextdraws[11], 0);
    TextDrawBackgroundColor(eventTextdraws[11], 255);
    TextDrawFont(eventTextdraws[11], 4);
    TextDrawSetProportional(eventTextdraws[11], 1);

    eventTextdraws[12] = TextDrawCreate(337.000, 16.000, "LD_BEAT:chit");
    TextDrawTextSize(eventTextdraws[12], 14.000, 18.000);
    TextDrawAlignment(eventTextdraws[12], 1);
    TextDrawColor(eventTextdraws[12], 1097458175);
    TextDrawSetShadow(eventTextdraws[12], 0);
    TextDrawSetOutline(eventTextdraws[12], 0);
    TextDrawBackgroundColor(eventTextdraws[12], 255);
    TextDrawFont(eventTextdraws[12], 4);
    TextDrawSetProportional(eventTextdraws[12], 1);

    eventTextdraws[13] = TextDrawCreate(345.000, 19.000, "LD_BUM:blkdot");
    TextDrawTextSize(eventTextdraws[13], 37.000, 23.000);
    TextDrawAlignment(eventTextdraws[13], 1);
    TextDrawColor(eventTextdraws[13], 1097458175);
    TextDrawSetShadow(eventTextdraws[13], 0);
    TextDrawSetOutline(eventTextdraws[13], 0);
    TextDrawBackgroundColor(eventTextdraws[13], 255);
    TextDrawFont(eventTextdraws[13], 4);
    TextDrawSetProportional(eventTextdraws[13], 1);

    eventTextdraws[14] = TextDrawCreate(375.000, 16.000, "LD_BEAT:chit");
    TextDrawTextSize(eventTextdraws[14], 14.000, 18.000);
    TextDrawAlignment(eventTextdraws[14], 1);
    TextDrawColor(eventTextdraws[14], 1097458175);
    TextDrawSetShadow(eventTextdraws[14], 0);
    TextDrawSetOutline(eventTextdraws[14], 0);
    TextDrawBackgroundColor(eventTextdraws[14], 255);
    TextDrawFont(eventTextdraws[14], 4);
    TextDrawSetProportional(eventTextdraws[14], 1);

    eventTextdraws[15] = TextDrawCreate(375.000, 27.000, "LD_BEAT:chit");
    TextDrawTextSize(eventTextdraws[15], 14.000, 18.000);
    TextDrawAlignment(eventTextdraws[15], 1);
    TextDrawColor(eventTextdraws[15], 1097458175);
    TextDrawSetShadow(eventTextdraws[15], 0);
    TextDrawSetOutline(eventTextdraws[15], 0);
    TextDrawBackgroundColor(eventTextdraws[15], 255);
    TextDrawFont(eventTextdraws[15], 4);
    TextDrawSetProportional(eventTextdraws[15], 1);

    eventTextdraws[16] = TextDrawCreate(337.000, 27.000, "LD_BEAT:chit");
    TextDrawTextSize(eventTextdraws[16], 14.000, 18.000);
    TextDrawAlignment(eventTextdraws[16], 1);
    TextDrawColor(eventTextdraws[16], 1097458175);
    TextDrawSetShadow(eventTextdraws[16], 0);
    TextDrawSetOutline(eventTextdraws[16], 0);
    TextDrawBackgroundColor(eventTextdraws[16], 255);
    TextDrawFont(eventTextdraws[16], 4);
    TextDrawSetProportional(eventTextdraws[16], 1);

    eventTextdraws[17] = TextDrawCreate(339.000, 25.000, "LD_BUM:blkdot");
    TextDrawTextSize(eventTextdraws[17], 48.000, 12.000);
    TextDrawAlignment(eventTextdraws[17], 1);
    TextDrawColor(eventTextdraws[17], 1097458175);
    TextDrawSetShadow(eventTextdraws[17], 0);
    TextDrawSetOutline(eventTextdraws[17], 0);
    TextDrawBackgroundColor(eventTextdraws[17], 255);
    TextDrawFont(eventTextdraws[17], 4);
    TextDrawSetProportional(eventTextdraws[17], 1);

    eventTextdraws[18] = TextDrawCreate(309.000, 11.000, "50");
    TextDrawLetterSize(eventTextdraws[18], 0.300, 1.500);
    TextDrawAlignment(eventTextdraws[18], 2);
    TextDrawColor(eventTextdraws[18], -1);
    TextDrawSetShadow(eventTextdraws[18], 1);
    TextDrawSetOutline(eventTextdraws[18], 1);
    TextDrawBackgroundColor(eventTextdraws[18], 150);
    TextDrawFont(eventTextdraws[18], 3);
    TextDrawSetProportional(eventTextdraws[18], 1);

    eventTextdraws[19] = TextDrawCreate(253.000, 23.000, "50");
    TextDrawLetterSize(eventTextdraws[19], 0.300, 1.500);
    TextDrawAlignment(eventTextdraws[19], 2);
    TextDrawColor(eventTextdraws[19], -1);
    TextDrawSetShadow(eventTextdraws[19], 1);
    TextDrawSetOutline(eventTextdraws[19], 1);
    TextDrawBackgroundColor(eventTextdraws[19], 150);
    TextDrawFont(eventTextdraws[19], 3);
    TextDrawSetProportional(eventTextdraws[19], 1);

    eventTextdraws[20] = TextDrawCreate(364.000, 23.000, "50");
    TextDrawLetterSize(eventTextdraws[20], 0.300, 1.500);
    TextDrawAlignment(eventTextdraws[20], 2);
    TextDrawColor(eventTextdraws[20], -1);
    TextDrawSetShadow(eventTextdraws[20], 1);
    TextDrawSetOutline(eventTextdraws[20], 1);
    TextDrawBackgroundColor(eventTextdraws[20], 150);
    TextDrawFont(eventTextdraws[20], 3);
    TextDrawSetProportional(eventTextdraws[20], 1);
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    if(IsPlayerInEvent(playerid))
    {
        ClearAnimations(playerid);
        if(killerid != INVALID_PLAYER_ID)
        {
            EventData[eventScore][EventTeam[killerid] - 1]++;

            eventTextdraw(playerid);

            if(EventData[eventScore][EventTeam[killerid] - 1] >= EventData[eventTargetScore]) 
            {
                EventData[eventWinner] = EventTeam[killerid];

                SendClientMessageToAllEx(-1, ""YELLOW"[Event]:"WHITE" Event telah selesai dan Team %s "WHITE"sebagai pemenang.", (EventTeam[killerid] == TEAM_A) ? ""RED"Red" : ""BLUE"Blue");

                foreach(new i : Player)  
                {
                    if(IsPlayerInEvent(i))
                    {
                        if(EventTeam[i] == EventData[eventWinner])
                        {
                            GiveMoney(i, EventData[eventPrize]);
                            SendClientMessageEx(i, -1, ""YELLOW"[Event]:"WHITE" Team anda menang dalam event ini dan mendapat hadiah sebanyak "GREEN"%s.", FormatMoney(EventData[eventPrize]));
                        }
                        else 
                        {
                            GiveMoney(i, EventData[eventPrizeParticipation]);
                            SendClientMessageEx(i, -1, ""YELLOW"[Event]:"WHITE" Anda mendapatkan hadiah event sebanyak "GREEN"%s"WHITE" karena telah ikut berpartisipasi.", FormatMoney(EventData[eventPrizeParticipation]));
                        }
                        EventLeave(i);
                    }
                }
                static const empty_player[E_EVENT];
                EventData = empty_player;
            }
            else 
            {
                if(GetPlayerState(playerid) == PLAYER_STATE_WASTED)
                {
                    SetSpawnInfo(playerid, EventTeam[playerid], EventData[eventSkin][EventTeam[playerid] - 1], EventData[eventSpawnX][EventTeam[playerid] - 1], EventData[eventSpawnY][EventTeam[playerid] - 1], EventData[eventSpawnZ][EventTeam[playerid] - 1], 0.0, 0, 0, 0, 0, 0, 0);
                }
                EventWaitingSpawn[playerid] = 1;
            }
        }
    }
    return 1;
}

CMD:event(playerid, params[])
{
    static 
        option[10],
        extendstring[128];
    
    if(sscanf(params, "s[10]S()[128]", option, extendstring))
    {
        if(AccountData[playerid][pAdmin] > 3) 
        {
            SendClientMessageEx(playerid, -1, "/event [entinity]");
            SendClientMessageEx(playerid, -1, ""YELLOW"-> "WHITE"create/end/open/start/setup");
            return 1;
        }
        else
        {
            SendClientMessageEx(playerid, -1, "/event [join/leave]");
            return 1;
        }
    }
    if(!strcmp(option, "create"))
    {
        if(CheckAdmin(playerid, 3)) return PermissionError(playerid);
        if(EventData[eventCreated]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Event telah dibuat sebelumnya!");
        if(EventData[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Event sedang berlangsung!");
        
        EventData[eventCreated] = true;
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membuat event");
    }
    else if(!strcmp(option, "leave"))
    {
        if(!EventData[eventCreated]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada event yang dilakukan sekarang!");
        if(!IsPlayerInEvent(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang tidak berada didalam Event!");
        if(!EventData[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Event belum dimulai, tidak dapat meninggalkan event!");

        EventLeave(playerid);
        SendClientMessageEx(playerid, -1, ""YELLOW"[Event]:"WHITE" Anda telah meninggalkan event yang sedang berlangsung, kamu tidak mendapatkan apa apa dari event.");
    }
    else if(!strcmp(option, "start"))
    {
        if(CheckAdmin(playerid, 3)) return PermissionError(playerid);
        if(!EventData[eventCreated]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada event yang dilakukan sekarang!");
        if(!EventData[eventOpened]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Buka partisipasi event terlebuh dahulu dengan ~y~/event open!");
        if(EventData[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Event sudah dimulai sebelumnya!");
        if(!eventCount()) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada satupun yang berpartisipasi!");

        EventData[eventStarted] = true;
        EventData[eventOpened] = false;

        foreach(new i : Player) if (IsPlayerInEvent(i)) {
            TogglePlayerControllable(i, 1);
            SetPlayerVirtualWorld(i, EventData[eventWorld]);
            GameTextForPlayer(i, "~g~Mulai", 2500, 6);
        }

        SendClientMessageToAllEx(-1, ""YELLOW"[Event]:"WHITE" "RED"%s"WHITE" memulai event TDM, tidak dapat bergabung lagi bagi yang belum masuk ke event.", GetAdminName(playerid));
    }
    else if(!strcmp(option, "end"))
    {
        if(CheckAdmin(playerid, 3)) return PermissionError(playerid);
        
        static const empty_player[E_EVENT];
        EventData = empty_player;

        SendClientMessageToAllEx(-1, ""YELLOW"[Event]:"WHITE" %s menghentikan event yang sedang berlangsung", GetAdminName(playerid));
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menghentikan event!");

        foreach(new i : Player) {
            if(IsPlayerInEvent(i)) {
                for(new id = 0; id != 21; id ++) {
                    TextDrawHideForPlayer(i, eventTextdraws[id]);
                }
                EventLeave(i);
            }
        }
    }
    else if(!strcmp(option, "join"))
    {
        if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang melakukan sesuatu, tunggu hingga selesai!");
        if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan, tidak dapat mengikuti event!");
        if(!EventData[eventCreated] || !EventData[eventOpened]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada event yang sedang berlangsung!");
        if(AccountData[playerid][pJailTime] || AccountData[playerid][pArrestTime]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih memiliki waktu jail!");
        if(IsPlayerInEvent(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah berada di dalam event!");

        if(AccountData[playerid][pTaserGun]) AccountData[playerid][pTaserGun] = 0;
        
        // UpdatePlayerData(playerid);
        ResetPlayerWeapons(playerid);
        EventJoin[playerid] = 1;

        for(new id = 0; id != 21; id ++) {
            TextDrawShowForPlayer(playerid, eventTextdraws[id]);
            TextDrawSetString(eventTextdraws[18], sprintf("%d", EventData[eventTargetScore]));
            TextDrawSetString(eventTextdraws[19], sprintf("%d", EventData[eventScore][0]));
            TextDrawSetString(eventTextdraws[20], sprintf("%d", EventData[eventScore][1]));
            
            TextDrawShowForPlayer(playerid, eventTextdraws[18]);
            TextDrawShowForPlayer(playerid, eventTextdraws[19]);
            TextDrawShowForPlayer(playerid, eventTextdraws[20]);
        }

        GetPlayerPos(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ]);
        GetPlayerFacingAngle(playerid, AccountData[playerid][pPosA]);

        AccountData[playerid][pInt] = GetPlayerInterior(playerid);
        AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);

        if(EventData[eventSelectTeam]) {
            EventData[eventSelectTeam] = 0;
            EventTeam[playerid] = TEAM_A;
            SetPlayerColor(playerid, RemoveAlpha(X11_RED));
        } else {
            EventData[eventSelectTeam] = 1;
            EventTeam[playerid] = TEAM_B;
            SetPlayerColor(playerid, RemoveAlpha(COLOR_BLUE));
        }

        SetPlayerTeam(playerid, EventTeam[playerid]);

        EventSpawn(playerid);
        TogglePlayerControllable(playerid, 0);
        SetPlayerVirtualWorld(playerid, (playerid+1));

        SendClientMessageEx(playerid, -1, ""YELLOW"[Event]:"WHITE" Anda tergabung sebagai Team %s"WHITE", kamu akan melihat player lain saat event dimulai.", EventTeam[playerid] == TEAM_A ? ""RED"Red" : ""BLUE"Blue");
    }
    else if(!strcmp(option, "setup"))
    {
        if(CheckAdmin(playerid, 3)) return PermissionError(playerid);
        if(!EventData[eventCreated]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada event yang sedang dibuat!");
        if(EventData[eventStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Event sedang berlangsung!");

        EventDialogShow(playerid);
    }
    else if(!strcmp(option, "open"))
    {
        if(CheckAdmin(playerid, 3)) return PermissionError(playerid);
        if(!EventData[eventCreated]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada event yang dilakukan sekarang!");
        if(!EventData[eventHealth]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Event health harus disetup!");
        if(!EventData[eventPrize]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Event Prize harus disetup!");
        if(!EventData[eventPrizeParticipation]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Event Participation Prize harus disetup!");
        
        EventData[eventOpened] = true;
        SendClientMessageToAllEx(-1, ""YELLOW"[Event]:"WHITE" Team Deatmatch akan segera dimulai, gunakan '"RED"/event join"WHITE"' untuk berpartisipasi");
        SendClientMessageToAllEx(-1, "-> Hadiah Partisipasi: "GREEN"%s"WHITE" // Hadiah Team Pemenang: "GREEN"%s"WHITE" // Target Score: "YELLOW"%d", FormatMoney(EventData[eventPrizeParticipation]), FormatMoney(EventData[eventPrize]), EventData[eventTargetScore]);
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_EVENT_SETTING:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");
            switch(listitem)
            {
                case 0://Red Team Skin
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_REDSKIN, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Skin", "Mohon masukkan id skin untuk red team dibawah ini:", "Setup", "Batal");
                }
                case 1:// Red Team position
                {
                    GetPlayerPos(playerid, EventData[eventSpawnX][0], EventData[eventSpawnY][0], EventData[eventSpawnZ][0]);
                    GetPlayerFacingAngle(playerid, EventData[eventSpawnA][0]);
                    SendClientMessageEx(playerid, -1, ""YELLOW"[Event]:"WHITE" Anda berhasil menetapkan position spawn untuk tim "RED"Red");
                }
                case 2:// Red Team Weapon 1
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_REDWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Weapon 1", "Mohon masukkan id weapon untuk red team dibawah ini:", "Set", "Batal");
                }
                case 3:// Red Team Weapon 2
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_REDWEAP2, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Weapon 2", "Mohon masukkan id weapon untuk red team dibawah ini:", "Set", "Batal");
                }
                case 4:// Red Team Weapon 3
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_REDWEAP3, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Weapon 3", "Mohon masukkan id weapon untuk red team dibawah ini:", "Set", "Batal");
                }
                case 5:// Blue Team Skin
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_BLUESKIN, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Skin", "Mohon masukkan id skin untuk blue team dibawah ini:", "Setup", "Batal");  
                }
                case 6:// Blue Team position
                {
                    GetPlayerPos(playerid, EventData[eventSpawnX][1], EventData[eventSpawnY][1], EventData[eventSpawnZ][1]);
                    GetPlayerFacingAngle(playerid, EventData[eventSpawnA][1]);
                    SendClientMessageEx(playerid, -1, ""YELLOW"[Event]:"WHITE" Anda berhasil menetapkan position spawn untuk tim "BLUE"Blue");
                }
                case 7:// Blue Team Weapon 1
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_BLUEWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Weapon 1", "Mohon masukkan id weapon untuk blue team dibawah ini:", "Set", "Batal");
                }
                case 8:// Blue Team Weapon 2
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_BLUEWEAP2, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Weapon 2", "Mohon masukkan id weapon untuk blue team dibawah ini:", "Set", "Batal");
                }
                case 9:// Blue Team Weapon 3
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_BLUEWEAP3, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Weapon 3", "Mohon masukkan id weapon untuk blue team dibawah ini:", "Set", "Batal");
                }
                case 10:// Arena WWID
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_WWID, DIALOG_STYLE_INPUT, "TDM Event Creator - Arena WWID", "Mohon masukkan World ID untuk area yang ingin ditetapkan di dibawah ini:", "Set", "Batal");
                }
                case 11:// Arena Interior
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_INTID, DIALOG_STYLE_INPUT, "TDM Event Creator - Arena Interior", "Mohon masukkan Interior ID untuk area yang ingin ditetapkan di dibawah ini:", "Set", "Batal");
                }
                case 12:// Limitation Minutes
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_TIME, DIALOG_STYLE_INPUT, "TDM Event Creator - Limit Minutes", "Mohon masukkan Waktu Limit (Minutes) untuk Event dibawah ini:", "Set", "Batal");
                }
                case 13:// Target Score
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_TARGETSCORE, DIALOG_STYLE_INPUT, "TDM Event Creator - Target Score", "Mohon masukkan target score untuk event dibawah ini:", "Set", "Batal");
                }
                case 14:// Health
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_HEALTH, DIALOG_STYLE_INPUT, "TDM Event Creator - Health Event", "Mohon masukkan berapa jumlah health untuk event dibawah ini:", "Set", "Batal");
                }
                case 15:// Armour
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_ARMOUR, DIALOG_STYLE_INPUT, "TDM Event Creator - Armour Event", "Mohon masukkan berapa jumlah armour untuk event dibawah ini:", "Set", "Batal");
                }
                case 16:// Partisi Prize
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_PARTICIPRIZE, DIALOG_STYLE_INPUT, "TDM Event Creator - Participation Prize", "Mohon masukkan hadiah untuk orang yang mengikuti event dibawah ini:", "Set", "Batal");
                }
                case 17:// Team Prize
                {
                    ShowPlayerDialog(playerid, DIALOG_EVENT_PRIZE, DIALOG_STYLE_INPUT, "TDM Event Creator - Prize Pool", "Mohon masukkan hadiah untuk team yang memenangkan event dibawah ini:", "Set", "Batal");
                }
            }
        }
        case DIALOG_EVENT_REDSKIN:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");
            
            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_REDSKIN, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Skin", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan id skin untuk red team dibawah ini:", "Setup", "Batal");
            
            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_REDSKIN, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Skin", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan id skin untuk red team dibawah ini:", "Setup", "Batal");

            if(strval(inputtext) < 1 || strval(inputtext) > 299) return ShowPlayerDialog(playerid, DIALOG_EVENT_REDSKIN, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Skin", 
            "Error: Skin ID dimulai dari 1 - 299!\nMohon masukkan id skin untuk red team dibawah ini:", "Setup", "Batal");

            EventData[eventSkin][0] = strval(inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil setup skin Red Team!");
        }
        case DIALOG_EVENT_REDWEAP1:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_REDWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Weapon 1", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan id weapon untuk red team dibawah ini:", "Set", "Batal");
            
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_REDWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Weapon 1", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan id weapon untuk red team dibawah ini:", "Set", "Batal");
        
            if(strval(inputtext) < 0 || strval(inputtext) > 37) return ShowPlayerDialog(playerid, DIALOG_EVENT_REDWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Weapon 1", 
            "Error: ID Weapon dimulai dari 0 - 37!\nMohon masukkan id weapon untuk red team dibawah ini:", "Set", "Batal");

            EventData[eventWeapon1][0] = strval(inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil setup senjata 1 untuk Red Team!");
        }
        case DIALOG_EVENT_REDWEAP2:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_REDWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Weapon 1", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan id weapon untuk red team dibawah ini:", "Set", "Batal");
            
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_REDWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Weapon 1", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan id weapon untuk red team dibawah ini:", "Set", "Batal");
        
            if(strval(inputtext) < 0 || strval(inputtext) > 37) return ShowPlayerDialog(playerid, DIALOG_EVENT_REDWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Weapon 1", 
            "Error: ID Weapon dimulai dari 0 - 37!\nMohon masukkan id weapon untuk red team dibawah ini:", "Set", "Batal");

            EventData[eventWeapon2][0] = strval(inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil setup senjata 2 untuk Red Team!");
        }
        case DIALOG_EVENT_REDWEAP3:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_REDWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Weapon 1", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan id weapon untuk red team dibawah ini:", "Set", "Batal");
            
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_REDWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Weapon 1", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan id weapon untuk red team dibawah ini:", "Set", "Batal");
        
            if(strval(inputtext) < 0 || strval(inputtext) > 37) return ShowPlayerDialog(playerid, DIALOG_EVENT_REDWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Red Weapon 1", 
            "Error: ID Weapon dimulai dari 0 - 37!\nMohon masukkan id weapon untuk red team dibawah ini:", "Set", "Batal");

            EventData[eventWeapon3][0] = strval(inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil setup senjata 3 untuk Red Team!");
        }
        case DIALOG_EVENT_BLUESKIN:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");
            
            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_BLUESKIN, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Skin", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan id skin untuk blue team dibawah ini:", "Setup", "Batal");
            
            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_BLUESKIN, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Skin", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan id skin untuk blue team dibawah ini:", "Setup", "Batal");

            if(strval(inputtext) < 1 || strval(inputtext) > 299) return ShowPlayerDialog(playerid, DIALOG_EVENT_BLUESKIN, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Skin", 
            "Error: Skin ID dimulai dari 1 - 299!\nMohon masukkan id skin untuk blue team dibawah ini:", "Setup", "Batal");

            EventData[eventSkin][1] = strval(inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil setup skin Blue Team!");
        }
        case DIALOG_EVENT_BLUEWEAP1:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_BLUEWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Weapon 1", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan id weapon untuk blue team dibawah ini:", "Set", "Batal");
            
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_BLUEWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Weapon 1", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan id weapon untuk blue team dibawah ini:", "Set", "Batal");
        
            if(strval(inputtext) < 0 || strval(inputtext) > 37) return ShowPlayerDialog(playerid, DIALOG_EVENT_BLUEWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Weapon 1", 
            "Error: ID Weapon dimulai dari 0 - 37!\nMohon masukkan id weapon untuk blue team dibawah ini:", "Set", "Batal");

            EventData[eventWeapon1][1] = strval(inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil setup senjata 1 untuk Blue Team!");
        }
        case DIALOG_EVENT_BLUEWEAP2:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_BLUEWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Weapon 1", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan id weapon untuk blue team dibawah ini:", "Set", "Batal");
            
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_BLUEWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Weapon 1", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan id weapon untuk blue team dibawah ini:", "Set", "Batal");
        
            if(strval(inputtext) < 0 || strval(inputtext) > 37) return ShowPlayerDialog(playerid, DIALOG_EVENT_BLUEWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Weapon 1", 
            "Error: ID Weapon dimulai dari 0 - 37!\nMohon masukkan id weapon untuk blue team dibawah ini:", "Set", "Batal");

            EventData[eventWeapon2][1] = strval(inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil setup senjata 2 untuk Blue Team!");
        }
        case DIALOG_EVENT_BLUEWEAP3:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_BLUEWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Weapon 1", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan id weapon untuk blue team dibawah ini:", "Set", "Batal");
            
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_BLUEWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Weapon 1", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan id weapon untuk blue team dibawah ini:", "Set", "Batal");
        
            if(strval(inputtext) < 0 || strval(inputtext) > 37) return ShowPlayerDialog(playerid, DIALOG_EVENT_BLUEWEAP1, DIALOG_STYLE_INPUT, "TDM Event Creator - Blue Weapon 1", 
            "Error: ID Weapon dimulai dari 0 - 37!\nMohon masukkan id weapon untuk blue team dibawah ini:", "Set", "Batal");

            EventData[eventWeapon3][1] = strval(inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil setup senjata 3 untuk Blue Team!");
        }
        case DIALOG_EVENT_WWID:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_WWID, DIALOG_STYLE_INPUT, "TDM Event Creator - Arena WWID", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan World ID untuk area yang ingin ditetapkan di dibawah ini:", "Set", "Batal");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_WWID, DIALOG_STYLE_INPUT, "TDM Event Creator - Arena WWID", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan World ID untuk area yang ingin ditetapkan di dibawah ini:", "Set", "Batal");

            if(strval(inputtext) < 0) return ShowPlayerDialog(playerid, DIALOG_EVENT_WWID, DIALOG_STYLE_INPUT, "TDM Event Creator - Arena WWID", 
            "Error: WWID Tidak dapat kurang dari 0!\nMohon masukkan World ID untuk area yang ingin ditetapkan di dibawah ini:", "Set", "Batal");

            EventData[eventWorld] = strval(inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil setup Arena WWID!");
        }
        case DIALOG_EVENT_INTID:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_INTID, DIALOG_STYLE_INPUT, "TDM Event Creator - Arena Interior", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan World ID untuk area yang ingin ditetapkan di dibawah ini:", "Set", "Batal");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_INTID, DIALOG_STYLE_INPUT, "TDM Event Creator - Arena Interior", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan World ID untuk area yang ingin ditetapkan di dibawah ini:", "Set", "Batal");

            if(strval(inputtext) < 0) return ShowPlayerDialog(playerid, DIALOG_EVENT_INTID, DIALOG_STYLE_INPUT, "TDM Event Creator - Arena Interior", 
            "Error: Interior Tidak dapat kurang dari 0!\nMohon masukkan World ID untuk area yang ingin ditetapkan di dibawah ini:", "Set", "Batal");

            EventData[eventInterior] = strval(inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil setup Arena Interior!");
        }
        case DIALOG_EVENT_TIME:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_TIME, DIALOG_STYLE_INPUT, "TDM Event Creator - Limit Minutes", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan Waktu Limit (Minutes) untuk Event dibawah ini:", "Set", "Batal");
            
            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_TIME, DIALOG_STYLE_INPUT, "TDM Event Creator - Limit Minutes", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan Waktu Limit (Minutes) untuk Event dibawah ini:", "Set", "Batal");
        
            if(strval(inputtext) < 1 || strval(inputtext) >= 60) return ShowPlayerDialog(playerid, DIALOG_EVENT_TIME, DIALOG_STYLE_INPUT, "TDM Event Creator - Limit Minutes", 
            "Error: Waktu tidak dapat kurang dari 1 atau lebih dari 60 menit!\nMohon masukkan Waktu Limit (Minutes) untuk Event dibawah ini:", "Set", "Batal");
        
            EventData[eventTime] = strval(inputtext) * 60;
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil setup Time Limit Event!");
        }
        case DIALOG_EVENT_TARGETSCORE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_TARGETSCORE, DIALOG_STYLE_INPUT, "TDM Event Creator - Target Score", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan target score untuk event dibawah ini:", "Set", "Batal");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_TARGETSCORE, DIALOG_STYLE_INPUT, "TDM Event Creator - Target Score", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan target score untuk event dibawah ini:", "Set", "Batal");

            if(strval(inputtext) < 10) return ShowPlayerDialog(playerid, DIALOG_EVENT_TARGETSCORE, DIALOG_STYLE_INPUT, "TDM Event Creator - Target Score", 
            "Error: Score tidak dapat kurang dari 10!\nMohon masukkan target score untuk event dibawah ini:", "Set", "Batal");

            EventData[eventTargetScore] = strval(inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil setup Target Score!");
        }
        case DIALOG_EVENT_HEALTH:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_HEALTH, DIALOG_STYLE_INPUT, "TDM Event Creator - Health Event", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan berapa jumlah health untuk event dibawah ini:", "Set", "Batal");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_HEALTH, DIALOG_STYLE_INPUT, "TDM Event Creator - Health Event", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan berapa jumlah health untuk event dibawah ini:", "Set", "Batal");

            if(strval(inputtext) < 1 || strval(inputtext) > 150) return ShowPlayerDialog(playerid, DIALOG_EVENT_HEALTH, DIALOG_STYLE_INPUT, "TDM Event Creator - Health Event", 
            "Error: Health tidak dapat dibawah 1 atau lebih dari 150!\nMohon masukkan berapa jumlah health untuk event dibawah ini:", "Set", "Batal");

            EventData[eventHealth] = strval(inputtext);
            SendClientMessageEx(playerid, -1, ""YELLOW"[Event]:"WHITE" Berhasil setup health untuk event kali ini "GREEN"%d.00", strval(inputtext));
        }
        case DIALOG_EVENT_ARMOUR:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_ARMOUR, DIALOG_STYLE_INPUT, "TDM Event Creator - Armour Event", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan berapa jumlah Armour untuk event dibawah ini:", "Set", "Batal");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_ARMOUR, DIALOG_STYLE_INPUT, "TDM Event Creator - Armour Event", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan berapa jumlah Armour untuk event dibawah ini:", "Set", "Batal");

            if(strval(inputtext) < 1 || strval(inputtext) > 99) return ShowPlayerDialog(playerid, DIALOG_EVENT_ARMOUR, DIALOG_STYLE_INPUT, "TDM Event Creator - Armour Event", 
            "Error: Armour tidak dapat dibawah 1 atau lebih dari 99!\nMohon masukkan berapa jumlah Armour untuk event dibawah ini:", "Set", "Batal");

            EventData[eventArmour] = strval(inputtext);
            SendClientMessageEx(playerid, -1, ""YELLOW"[Event]:"WHITE" Berhasil setup Armour untuk event kali ini "GREEN"%d.00", strval(inputtext));
        }
        case DIALOG_EVENT_PARTICIPRIZE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_PARTICIPRIZE, DIALOG_STYLE_INPUT, "TDM Event Creator - Participation Prize", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan hadiah untuk orang yang mengikuti event dibawah ini:", "Set", "Batal");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_PARTICIPRIZE, DIALOG_STYLE_INPUT, "TDM Event Creator - Participation Prize", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan hadiah untuk orang yang mengikuti event dibawah ini:", "Set", "Batal");

            if(strval(inputtext) < 1) return ShowPlayerDialog(playerid, DIALOG_EVENT_PARTICIPRIZE, DIALOG_STYLE_INPUT, "TDM Event Creator - Participation Prize", 
            "Error: Hadiah tidak dapat kurang dari $1!\nMohon masukkan hadiah untuk orang yang mengikuti event dibawah ini:", "Set", "Batal");

            EventData[eventPrizeParticipation] = strval(inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil setup Hadiah Partisipasi!");
        }
        case DIALOG_EVENT_PRIZE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(CheckAdmin(playerid, 3)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berhak untuk mengatur ini!");

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_PRIZE, DIALOG_STYLE_INPUT, "TDM Event Creator - Prize Pool", 
            "Error: Harus diisi tidak dapat kosong!\nMohon masukkan hadiah untuk team yang memenangkan event dibawah ini:", "Set", "Batal");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_EVENT_PRIZE, DIALOG_STYLE_INPUT, "TDM Event Creator - Prize Pool", 
            "Error: Hanya dapat diisi angka!\nMohon masukkan hadiah untuk team yang memenangkan event dibawah ini:", "Set", "Batal");
        
            if(strval(inputtext) < 1) return ShowPlayerDialog(playerid, DIALOG_EVENT_PRIZE, DIALOG_STYLE_INPUT, "TDM Event Creator - Prize Pool", 
            "Error: Hadiah tidak dapat kurang dari $1!\nMohon masukkan hadiah untuk team yang memenangkan event dibawah ini:", "Set", "Batal");

            EventData[eventPrize] = strval(inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil setup Hadiah Event!");
        }
    }
    return 1;
}

task EventTimeLimit[1000]()
{
    if(EventData[eventStarted])
    {
        if(EventData[eventTime] > 0)
        {
            EventData[eventTime] --;
            if(!EventData[eventTime])
            {
                foreach(new i : Player) 
                {
                    if(IsPlayerInEvent(i)) 
                    {
                        EventLeave(i);
                        EventJoin[i] = 0;
                        for(new id = 0; id != 21; id ++) {
                            TextDrawHideForPlayer(i, eventTextdraws[id]);
                        }
                        SendClientMessageEx(i, -1, ""YELLOW"[Event]:"WHITE" Waktu limit event sudah habis. event dibubarkan!");
                    }
                    static const empty_player[E_EVENT];
                    EventData = empty_player;
                }
            }
        }
    }
    return 1;
}
