#include <YSI\y_hooks>

stock IsPlayerInEvent(playerid)
{
	if(eventJoin[playerid])
		return 1;

	return 0;
}
stock EventType(type)
{
	new name[25];
	switch(type)
	{
		case TYPE_TDM: name = "Team Deathmatch";
		case TYPE_JETPACK: name = "Jetpack Race";
		case TYPE_DM: name = "Deathmatch";
		case TYPE_NONE: name = "N/A";
	}
	return name;
}

stock eventCount()
{
	new count = 0;
	foreach(new i : Player) if(IsPlayerInEvent(i)) {
		count++;
	}
	return count;
}

stock SendEventMessageAll(color, message[])
{
	foreach(new i : Player) if(IsPlayerInEvent(i)) 
	{
		SendClientMessage(i, color, message);
	}
	return 1;
}
stock SendEventTeamMessage(playerid, color, message[])
{
	foreach(new i : Player) if(IsPlayerInEvent(i) && eventTeams[playerid] == eventTeams[i]) {
		SendClientMessage(i, color, message);
	}
	return 1;
}

stock eventTextdraw(playerid, text[])
{
	if(IsPlayerInEvent(playerid))
	{
		TextDrawSetString(eventTextdraws[2], sprintf("Target:_%d!", EventData[eventTarget]));
		TextDrawSetString(eventTextdraws[3], sprintf("~r~Team_A:_%d~n~~b~Team_B:_%d", EventData[eventScore][0], EventData[eventScore][1]));

		eventMessageText[0] = eventMessageText[1];
		eventMessageText[1] = eventMessageText[2];
		eventMessageText[2] = eventMessageText[3];
		format(eventMessageText[3], 128, text);

		TextDrawSetString(eventTextdraws[4],eventMessageText[0]);
		TextDrawSetString(eventTextdraws[5],eventMessageText[1]);
		TextDrawSetString(eventTextdraws[6],eventMessageText[2]);
		TextDrawSetString(eventTextdraws[7],eventMessageText[3]);
	}
	return 1;
}

stock Player_ToggleEventAntiCheat(playerid, bool:toggle)
{
    if (!IsPlayerConnected(playerid))
    {
        return 0;
    }
	EnableAntiCheatForPlayer(playerid, 2, toggle);
	EnableAntiCheatForPlayer(playerid, 3, toggle);
	EnableAntiCheatForPlayer(playerid, 4, toggle);
	EnableAntiCheatForPlayer(playerid, 5, toggle);
	EnableAntiCheatForPlayer(playerid, 6, toggle);
	EnableAntiCheatForPlayer(playerid, 15, toggle);
	EnableAntiCheatForPlayer(playerid, 16, toggle);
	EnableAntiCheatForPlayer(playerid, 17, toggle);
	EnableAntiCheatForPlayer(playerid, 18, toggle);
	EnableAntiCheatForPlayer(playerid, 19, toggle);
	EnableAntiCheatForPlayer(playerid, 20, toggle);
	EnableAntiCheatForPlayer(playerid, 21, toggle);
	return 1;
}
stock eventSpawn(playerid)
{
	if(IsPlayerInEvent(playerid))
	{
		if(EventData[eventType] == TYPE_TDM)
		{
			Player_ToggleEventAntiCheat(playerid, false);
			SetPlayerPos(playerid, EventData[eventSpawnX][eventTeams[playerid]-1], EventData[eventSpawnY][eventTeams[playerid]-1], EventData[eventSpawnZ][eventTeams[playerid]-1]);
			SetPlayerFacingAngle(playerid, EventData[eventSpawnA][eventTeams[playerid]-1]);
			SetCameraBehindPlayer(playerid);

			SetPlayerSkin(playerid, EventData[eventSkin][eventTeams[playerid]-1]);

			SetPlayerInterior(playerid, EventData[eventInt]);
			SetPlayerVirtualWorld(playerid, EventData[eventWorld]);

			for(new i = 0; i != 3; i++) 
			{
				if(EventData[eventWeapons][i]) 
				{
					GivePlayerEventWeapon(playerid, EventData[eventWeapons][i], EventData[eventAmmo][i]);
				}
			}
			Info(playerid, "You're spawn to the event.");

			SetTimerEx("eventSpawnProp", 500, false, "i", playerid);

		}
		else if(EventData[eventType] == TYPE_DM)
		{
			Player_ToggleEventAntiCheat(playerid, false);

			SetPlayerTeam(playerid, NO_TEAM);
			SetPlayerPos(playerid, EventData[eventSpawnX_DM], EventData[eventSpawnY_DM], EventData[eventSpawnZ_DM]);
			SetCameraBehindPlayer(playerid);

			SetPlayerInterior(playerid, EventData[eventInt]);
			SetPlayerVirtualWorld(playerid, EventData[eventWorld]);

			for(new i = 0; i != 3; i++) 
			{
				if(EventData[eventWeapons][i]) 
				{
					GivePlayerEventWeapon(playerid, EventData[eventWeapons][i], EventData[eventAmmo][i]);
				}
			}
			Info(playerid, "You're spawn to the event.");

			SetTimerEx("eventSpawnProp", 500, false, "i", playerid);
		}
        AttachPlayerToys(playerid);
		AttachPlayerToysaxp(playerid);
		AttachPlayerToysDragon(playerid);
		AttachPlayerToysSonic(playerid);
		AttachPlayerToysGrinch(playerid);
		AttachPlayerToysGhost(playerid);
	}
	return 1;
}
stock GivePlayerEventWeapon(playerid, weaponid, ammo)
{
	if(IsPlayerInEvent(playerid))
	{
		GivePlayerWeapon(playerid, weaponid, ammo);
	}
	return 1;
}
stock eventLeave(playerid)
{
	ResetPlayerWeapons(playerid);
	eventTeams[playerid] = TEAM_NONE;
	for(new id = 0; id != 8; id++) 
	{
		TextDrawHideForPlayer(playerid, eventTextdraws[id]);
	}

	Player_ToggleEventAntiCheat(playerid, true);

	eventScore_DM[playerid] = 0;
	eventJoin[playerid] = 0;
	AccountData[playerid][pACTime] = gettime() + 5;

	SetPlayerTeam(playerid, 1);
    SetPlayerInterior(playerid, AccountData[playerid][pInt]);
	SetPlayerVirtualWorld(playerid, AccountData[playerid][pWorld]);

	if(GetPlayerState(playerid) == PLAYER_STATE_WASTED)
	{
		SetSpawnInfo(playerid, 1, AccountData[playerid][pSkin], AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], 0.0, 0, 0, 0, 0, 0, 0);
	}

	SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 7000);

	SetPlayerHealth(playerid, AccountData[playerid][pHealth]);
	SetPlayerArmour(playerid, AccountData[playerid][pArmour]);

	if(AccountData[playerid][pAdminDuty]) 
	{
		SetPlayerSkin(playerid, AccountData[playerid][pSkin]); 
		SetPlayerColor(playerid, X11_RED);
	}
	else if(AccountData[playerid][pUsingUniform]) 
    {
        SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
    }
	else 
	{
		SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
		SetPlayerColor(playerid, COLOR_WHITE);
	}
    SetWeapons(playerid);
    AttachPlayerToys(playerid);
	AttachPlayerToysaxp(playerid);
	AttachPlayerToysDragon(playerid);
	AttachPlayerToysSonic(playerid);
	AttachPlayerToysGrinch(playerid);
	AttachPlayerToysGhost(playerid);
	DisablePlayerRaceCheckpoint(playerid);
	return 1;
}

task eventStartTime[1000]()
{
    if (EventData[eventTime] > 0)
    {
        EventData[eventTime]--; // Kurangi waktu event

        new timeLeft = EventData[eventTime];

        foreach (new i : Player)
        {
            if (IsPlayerInEvent(i))
            {
                new text[24];
                format(text, sizeof(text), "~w~Harap Tunggu~n~~y~%02d", timeLeft);
                GameTextForPlayer(i, text, 1000, 6);
                PlayerPlaySound(i, 1149, 0.0, 0.0, 0.0);
            }
        }

        if (timeLeft == 0) // Saat waktu habis, mulai event
        {
            EventData[eventStart] = 1;
            EventData[eventOpen] = 0;

            foreach (new i : Player)
            {
                if (IsPlayerInEvent(i))
                {
                    AccountData[i][pFreeze] = 0;
                    TogglePlayerControllable(i, 1);
                    SetPlayerVirtualWorld(i, EventData[eventWorld]);
                    GameTextForPlayer(i, "~g~Mulai", 1000, 6);

                    if (EventData[eventType] == TYPE_JETPACK)
                    {
                        AccountData[i][pJetpack] = 1;
                        SetPlayerSpecialAction(i, SPECIAL_ACTION_USEJETPACK);
                    }
                }
            }

            new message[128];
            format(message, sizeof(message), ""YELLOW"EVENT:"WHITE" Event "RED"%s"WHITE" telah dimulai, tidak dapat bergabung bagi yang belum masuk ke dalam event.", EventType(EventData[eventType]));
            SendClientMessageToAllEx(-1, message);
        }
    }
    return 1;
}

forward eventSpawnProp(playerid);
public eventSpawnProp(playerid)
{
    if(SQL_IsCharacterLogged(playerid) && IsPlayerInEvent(playerid))
    {
        SetPlayerHealth(playerid, EventData[eventHealth]);
        SetPlayerArmour(playerid, EventData[eventArmor]);
    }
    return 1;
}