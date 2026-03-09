/* Weapon Factions System */

#include <YSI\y_hooks>

/* Local Functions */
hook OnPlayerDisconnect(playerid, reason)
{
    if(AccountData[playerid][pDutyPD] && AccountData[playerid][pDutyPemerintah] && AccountData[playerid][pDutyEms]
        && AccountData[playerid][pDutyBengkel] && AccountData[playerid][pDutyGojek])
    {
        SaveFactionWeapons(playerid);
    }
    return 1;
}

hook OnPlayerDeath(playerid)
{
    if(SQL_IsCharacterLogged(playerid))
    {
        if(AccountData[playerid][pDutyPD] && AccountData[playerid][pDutyPemerintah] && AccountData[playerid][pDutyEms]
            && AccountData[playerid][pDutyBengkel] && AccountData[playerid][pDutyGojek])
        {
            SaveFactionWeapons(playerid);
        }
    }
    return 1;
}

/* Callback */
SQL_FactionWeapons(playerid)
{
    if(AccountData[playerid][pDutyPD] && AccountData[playerid][pDutyPemerintah] && AccountData[playerid][pDutyEms]
        && AccountData[playerid][pDutyBengkel] && AccountData[playerid][pDutyGojek])
    {
        mysql_tquery(g_SQL, sprintf("SELECT * FROM `weapon_factions` WHERE `Owner_ID`=%d", AccountData[playerid][pID]), "OnLoadPlayerFactWeapons", "d", playerid);
    }
    return 1;
}

GiveFactionWeapon(playerid, weaponid, ammo)
{
    if(AccountData[playerid][pDutyPD] && AccountData[playerid][pDutyPemerintah] && AccountData[playerid][pDutyEms]
        && AccountData[playerid][pDutyBengkel] && AccountData[playerid][pDutyGojek])
    {
        if(!(0 <= weaponid <= 46)) 
        {
            return printf("[Debug] invalid Weapon ID (%d)]", weaponid);
        }

        GivePlayerWeapon(playerid, weaponid, ammo);
        mysql_tquery(g_SQL, sprintf("DELETE FROM `weapon_factions` WHERE `Slot`=%d", g_aWeaponSlots[weaponid]));

        new 
            query[165]
        ;
        mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `weapon_factions` VALUES ('%d', '%d', '%d', '%d', '%d') ON DUPLICATE KEY UPDATE ammo = %d, created %d", GetPlayerSQLID(playerid), weaponid, ammo, gettime(), g_aWeaponSlots[weaponid], ammo, gettime());
        return mysql_tquery(g_SQL, query);
    }
    return 1;
}

SaveFactionWeapons(playerid)
{
    static 
        weaponid,
        ammo
    ;
    for(new i = 1; i < MAX_WEAPON_SLOT; i++) {
        GetPlayerWeaponData(playerid, i, weaponid, ammo);

        if(!weaponid) continue;

        new 
            query[165]
        ;
        mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `weapon_factions` VALUES ('%d', '%d', '%d', '%d', '%d') ON DUPLICATE KEY UPDATE ammo = %d, created = %d", GetPlayerSQLID(playerid), weaponid, ammo, gettime(), g_aWeaponSlots[weaponid], ammo, gettime());
        mysql_tquery(g_SQL, query);
    }
    return 1;
}

ResetFactionWeapon(playerid) {
    if(AccountData[playerid][pDutyPD] && AccountData[playerid][pDutyPemerintah] && AccountData[playerid][pDutyEms]
        && AccountData[playerid][pDutyBengkel] && AccountData[playerid][pDutyGojek])
    {
        ResetPlayerWeapons(playerid);
        return mysql_tquery(g_SQL, sprintf("DELETE FROM `weapon_factions` WHERE `Owner_ID`=%d", AccountData[playerid][pID]));
    }
    return 0;
}

/* Functions */
forward OnLoadPlayerFactWeapons(playerid);
public OnLoadPlayerFactWeapons(playerid)
{
    static 
        weaponid,
        ammo
    ;

    for(new i = 0; i < cache_num_rows(); i++)
    {
        weaponid = cache_get_value_name_int(i, "Weapon");
        ammo = cache_get_value_name_int(i, "Ammo");

        if(!(0 <= weaponid <= 46))
        {
            printf("[Warning] OnLoadPlayerFactWeapons - Unknow Weaponid '%d'. Skipping", weaponid);
            continue;
        }
        GivePlayerWeapon(playerid, weaponid, ammo);
    }
    SetPlayerArmedWeapon(playerid, 0);
    return 1;
}