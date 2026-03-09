#include <YSI\y_hooks>

// Variable
new GetDamageID[MAX_PLAYERS] = { INVALID_PLAYER_ID, ... };

hook OnPlayerConnect(playerid)
{
    GetDamageID[playerid] = INVALID_PLAYER_ID;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	GetDamageID[playerid] = INVALID_PLAYER_ID;
	return 1;
}

/*hook OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    switch(weaponid)
    {
        // Invalid Weapon
        case 0..18, 39..54: return 1;
    }
    if(weaponid <= weaponid <= 46)
    {
        if(hittype == 1 && GetDamageID[hitid] == INVALID_PLAYER_ID)
		{
			GetDamageID[hitid] = playerid;
		}
    }
    return 1;
}

hook OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	new issuer[64];
	if(GetDamageID[playerid] != INVALID_PLAYER_ID)
	{
		format(issuer, MAX_PLAYER_NAME, ReturnName(GetDamageID[playerid]));
	}
	else
	{
		format(issuer, MAX_PLAYER_NAME, "-");
	}
	new query[255];
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `damagelogs` (`IDs`, `dWeapon`, `dBodyPart`, `dAmount`, `dIssuer`, `dTime`) VALUES ('%d', '%d', '%d', '%.1f', '%s', CURRENT_TIMESTAMP())", AccountData[playerid][pID], weaponid, bodypart, Float:amount, issuer);
	mysql_tquery(g_SQL, query);
	return 1;
}*/

hook OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	if(damagedid != INVALID_PLAYER_ID)
	{
		GetDamageID[damagedid] = playerid;
	}
	return 1;
}

hook OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	if(!AccountData[playerid][pSpawned])
		return 0;

	if(IsPlayerInEvent(playerid))
		return 0;

	static issuer[64];
	if(GetDamageID[playerid] != INVALID_PLAYER_ID)
	{
		format(issuer, MAX_PLAYER_NAME, ReturnName(issuerid));
	}
	else
	{
		format(issuer, MAX_PLAYER_NAME, "Diri Sendiri");
	}
	new query[300];
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `damagelogs` SET `IDs`=%d, `dWeapon`=%d, `dBodyPart`=%d, `dAmount`='%.1f', `dIssuer`='%s', `dTime`=CURRENT_TIMESTAMP()", AccountData[playerid][pID], weaponid, bodypart, Float:amount, issuer);
	mysql_tquery(g_SQL, query);
	return 1;
}

Damage_Show(playerid)
{
	new dbstr[255], Cache:execute;
	mysql_format(g_SQL, dbstr, sizeof(dbstr), "SELECT * FROM `damagelogs` WHERE `IDs`=%d ORDER BY `dTime` ASC", AccountData[playerid][pID]);
	execute = mysql_query(g_SQL, dbstr, true);
	new rows = cache_num_rows();
	if(rows)
	{
		if(rows >= 50)
		{
			mysql_tquery(g_SQL, sprintf("DELETE FROM `damagelogs` WHERE `IDs`=%d", AccountData[playerid][pID]));
		}

		new list[4096], date[64], weaponid, Float:damage, bodypart;
		
		format(list, sizeof(list), "Tanggal\tSenjata\tDamage\n");
		for(new x; x < rows; ++x)
		{
			cache_get_value_name(x, "dTime", date);
			cache_get_value_name_int(x, "dWeapon", weaponid);
			cache_get_value_name_float(x, "dAmount", damage);
			cache_get_value_name_int(x, "dBodyPart", bodypart);

			format(list, sizeof(list), "%s%s\t%s\t%.1f-%s\n", list, date, ReturnWeaponName(weaponid), damage, GetBodyPartName(bodypart));
		}
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Damage Log", list, "Tutup", "");
	}
	else 
	{
		new list[108];
		format(list, sizeof(list), "Tanggal\tSenjata\tDamage\n");
		format(list, sizeof(list), "%sBelum ada Damage Log yang dapat ditampilkan kepadamu!", list);
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Damage Log", list, "Tutup", "");
	}

	cache_delete(execute);
	return 1;
}

aDamage_Show(playerid, player)
{
	new dbstr[255], Cache:execute;
	mysql_format(g_SQL, dbstr, sizeof(dbstr), "SELECT * FROM `damagelogs` WHERE `IDs`=%d ORDER BY `dTime` ASC", AccountData[player][pID]);
	execute = mysql_query(g_SQL, dbstr, true);
	new rows = cache_num_rows();
	if(rows)
	{
		if(rows >= 50)
		{
			mysql_tquery(g_SQL, sprintf("DELETE FROM `damagelogs` WHERE `IDs`=%d", AccountData[player][pID]));
		}

		new list[4096], date[64], issuer[64], weaponid, Float:damage, bodypart;
		
		format(list, sizeof(list), "Tanggal\tIssuer\tSenjata\tDamage\n");
		for(new x; x < rows; ++x)
		{
			cache_get_value_name(x, "dTime", date);
			cache_get_value_name(x, "dIssuer", issuer);
			cache_get_value_name_int(x, "dWeapon", weaponid);
			cache_get_value_name_float(x, "dAmount", damage);
			cache_get_value_name_int(x, "dBodyPart", bodypart);

			format(list, sizeof(list), "%s%s\t%s\t%s\t%.1f-%s\n", list, date, issuer, ReturnWeaponName(weaponid), damage, GetBodyPartName(bodypart));
		}
		new title[108];
		format(title, sizeof(title), "Damage Logs - "YELLOW"%s", ReturnName(player));
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, title, list, "Tutup", ""); 
	}
	else 
	{
		new list[108], title[108];
		format(list, sizeof(list), "Tanggal\tSenjata\tDamage\n");
		format(list, sizeof(list), "%sBelum ada Damage Log pemain ini yang dapat ditampilkan kepadamu!", list);
		format(title, sizeof(title), "Damage Logs - "YELLOW"%s", ReturnName(player));
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, title, list, "Tutup", ""); 
	}

	cache_delete(execute);
	return 1;
}

forward DamageShowOffline(playerid, const NamePlayer[]);
public DamageShowOffline(playerid, const NamePlayer[])
{
	if(!cache_num_rows())
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Nama %s tidak ditemukan di database!", NamePlayer));
		return 1;
	}
	else 
	{
		new playerdbID;
		cache_get_value_index_int(0, 0, playerdbID);
		
		mysql_query(g_SQL, sprintf("SELECT * FROM `damagelogs` WHERE `IDs`=%d", playerdbID));
		new rows = cache_num_rows();
		if(rows)
		{
			new list[1000], date[64], issuer[24], weaponid, bodypart, Float:damage;
			
			format(list, sizeof(list), "Tanggal\tIssuer\tSenjata\tDamage\n");
			for(new x; x < rows; ++x)
			{
				cache_get_value_name(x, "dTime", date);
				cache_get_value_name(x, "dIssuer", issuer);
				cache_get_value_name_int(x, "dWeapon", weaponid);
				cache_get_value_name_int(x, "dBodyPart", bodypart);
				cache_get_value_name_float(x, "dAmount", damage);

				format(list, sizeof(list), "%s%s\t%s\t%s\t%.1f-%s\n", list, date, issuer, ReturnWeaponName(weaponid), damage, GetBodyPartName(bodypart));
			}
			ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Damage Log -"YELLOW"%s", NamePlayer), list, "Tutup", "");
		}
		else 
		{
			new list[108];
			format(list, sizeof(list), "Tanggal\tIssuer\tSenjata\tDamage\n");
			format(list, sizeof(list), "%sBelum ada Damage Log pemain ini yang dapat ditampilkan kepadamu", list);
			ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Damage Log -"YELLOW"%s", NamePlayer), list, "Tutup", "");
		}
	}
	return 1;
}

CMD:dlogoff(playerid, params[])
{
	new playerName[100], PlayersName[MAX_PLAYER_NAME];
	if(!AccountData[playerid][IsLoggedIn]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus terkoneksi ke dalam server!");
	if(CheckAdmin(playerid, 1)) return PermissionError(playerid);
	if(sscanf(params, "s[100]", playerName)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/dlogoff [player name]");
	
	
	foreach(new i : Player)
	{
		GetPlayerName(i, PlayersName, MAX_PLAYER_NAME);

		if(strfind(PlayersName, playerName, true) != -1)
		{
			ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang online, gunakan /adlog!");
			return 1;
		}
	}

	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT `pID` FROM `player_characters` WHERE `Char_Name`='%s'", playerName);
	mysql_tquery(g_SQL, query, "DamageShowOffline", "ds", playerid, playerName);
	return 1;
}

CMD:adlog(playerid, params[])
{
	new otherid;
	if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1) return PermissionError(playerid);
	if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/adlog [playerid/Name]");
	if(otherid == INVALID_PLAYER_ID || !IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke dalam server!");

	aDamage_Show(playerid, otherid);
	return 1;
}

CMD:dlog(playerid, params[])
{
	if(!AccountData[playerid][IsLoggedIn])
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus terkoneksi ke dalam server!");
	
	Damage_Show(playerid);
	return 1;
}
