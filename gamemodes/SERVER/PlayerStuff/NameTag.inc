#include <YSI_Coding\y_hooks>

new STREAMER_TAG_3D_TEXT_LABEL: NameTag[MAX_PLAYERS][MAX_PLAYERS];
new STREAMER_TAG_3D_TEXT_LABEL: AdminNameTag[MAX_PLAYERS][MAX_PLAYERS];

hook OnPlayerConnect(playerid)
{
    for (new i = 0; i < MAX_PLAYERS; i ++)
    {
        if (IsValidDynamic3DTextLabel(NameTag[playerid][i])) DestroyDynamic3DTextLabel(NameTag[playerid][i]), NameTag[playerid][i] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        if (IsValidDynamic3DTextLabel(AdminNameTag[playerid][i])) DestroyDynamic3DTextLabel(AdminNameTag[playerid][i]), AdminNameTag[playerid][i] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }
    return 1;
}

DisplayAdminNameTag(playerid)
{
    if (!AccountData[playerid][pNtagShown])
    {
        static string[300];
        foreach(new i : Player) if (IsPlayerConnected(i) && AccountData[i][pSpawned])
        {
            new Float:health, Float:am;
            GetPlayerHealth(i, health);
            GetPlayerArmour(i, am);

            format(string, sizeof(string), "%s | %s (PID: %d)\n"RED"%.2f"WHITE" | %.2f", AccountData[i][pName], AccountData[i][pUCP], i, health, am);
            if (AdminNameTag[playerid][i] == STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID) AdminNameTag[playerid][i] = CreateDynamic3DTextLabel(string, -1, 0.0, 0.0, 0.30, 25.0, i, INVALID_VEHICLE_ID, 0, -1, -1, playerid, 25.0, -1, 0);
        }
        AccountData[playerid][pNtagShown] = true;
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Name NTAG ID telah diaktifkan");
    }
    else
    {
        foreach(new i : Player) if (IsPlayerConnected(i))
        {
            if (AdminNameTag[playerid][i] != STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID) DestroyDynamic3DTextLabel(AdminNameTag[playerid][i]), AdminNameTag[playerid][i] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        }
        AccountData[playerid][pNtagShown] = false;
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Name NTAG ID telah dimatikan");
    }
    return 1;
}

DisplayPlayerNameTag(playerid)
{
    if (!AccountData[playerid][pNameTagShown])
    {
        new string[300];
        foreach (new i : Player) if (IsPlayerConnected(i) && AccountData[i][pSpawned])
        {
            format(string, sizeof(string), "%s (PID: %d)", AccountData[i][pUCP], i);
            if (NameTag[playerid][i] == STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID) NameTag[playerid][i] = CreateDynamic3DTextLabel(string, COLOR_CLIENT, 0.0, 0.0, 0.30, 15.0, i, INVALID_VEHICLE_ID, 1, -1, -1, playerid, 15.0, -1, 0);
        }
        AccountData[playerid][pNameTagShown] = true;
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Name SID telah diaktifkan");
    }
    else
    {
        foreach (new i : Player) if (IsPlayerConnected(i))
        {
            if (NameTag[playerid][i] != STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID) DestroyDynamic3DTextLabel(NameTag[playerid][i]), NameTag[playerid][i] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        }
        AccountData[playerid][pNameTagShown] = false;
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Name SID telah dimatikan");
    }
    return 1;
}

ResetSIDTag(playerid)
{
	foreach(new i : Player) if (IsPlayerConnected(i))
	{
		if (AccountData[i][pNameTagShown])
		{
			if (IsValidDynamic3DTextLabel(NameTag[i][playerid])) DestroyDynamic3DTextLabel(NameTag[i][playerid]), NameTag[i][playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
		}
	}

	if (AccountData[playerid][pNameTagShown])
	{
		foreach(new i : Player) if (IsPlayerConnected(i))
		{
			if (IsValidDynamic3DTextLabel(NameTag[playerid][i])) DestroyDynamic3DTextLabel(NameTag[playerid][i]), NameTag[playerid][i] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
		}
		
		AccountData[playerid][pNameTagShown] = false;
	}
	return 1;
}

ResetAdminTag(playerid)
{
    foreach(new i : Player) if (IsPlayerConnected(i))
    {
        if (AccountData[i][pNtagShown])
        {
            if (IsValidDynamic3DTextLabel(AdminNameTag[i][playerid])) DestroyDynamic3DTextLabel(AdminNameTag[i][playerid]), AdminNameTag[i][playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        }
    }

    if (AccountData[playerid][pNtagShown])
    {
        foreach(new i : Player) if (IsPlayerConnected(i))
        {
            if (IsValidDynamic3DTextLabel(AdminNameTag[playerid][i])) DestroyDynamic3DTextLabel(AdminNameTag[playerid][i]), AdminNameTag[playerid][i] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        }

        AccountData[playerid][pNtagShown] = false;
    }
    return 1;
}

CMD:sid(playerid, params[])
{
    if (AccountData[playerid][pNtagShown]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Matikan terlebih dahulu '/ntag'!");

    DisplayPlayerNameTag(playerid);
    return 1;
}

CMD:ntag(playerid, params[])
{
    if (AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1)
        return PermissionError(playerid);

    if (AccountData[playerid][pNameTagShown]) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Matikan terlebih dahulu '/sid'!");   

    DisplayAdminNameTag(playerid);
    return 1;
}

ptask AdminLabelUpdate[1000](playerid)
{
    if (AccountData[playerid][pNtagShown])
    {
        new Float:health, Float:am;
        foreach(new i : Player) if (IsPlayerConnected(i) && i != playerid)
        {
            GetPlayerHealth(i, health);
            GetPlayerArmour(i, am);

            if (IsValidDynamic3DTextLabel(AdminNameTag[playerid][i]))
            {
                static string[300];
                format(string, sizeof(string), "%s | %s (PID: %d)\n"RED"%.2f"WHITE" | %.2f", AccountData[i][pName], AccountData[i][pUCP], i, health, am);
                UpdateDynamic3DTextLabelText(AdminNameTag[playerid][i], -1, string);
            }
        }
    }
    return 1;
}