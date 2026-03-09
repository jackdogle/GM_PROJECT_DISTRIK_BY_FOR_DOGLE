#include <YSI\y_hooks>

stock bool:IsPlayerPolice(playerid)
{
    return (AccountData[playerid][pFaction] == FACTION_POLISI);
}

stock Locker_Save(id)
{
    if(id < 0 || id >= lockerCount)
        return 1;

    new query[512];
    mysql_format(g_SQL, query, sizeof(query),
        "UPDATE police_locker SET WeaponID='%d', Ammo='%d', Owner='%s' WHERE ID='%d'",
        lockerData[id][lWeapon],
        lockerData[id][lAmmo],
        lockerData[id][lOwner],
        lockerData[id][lID]
    );
    mysql_query(g_SQL, query, true);
    return 1;
}

forward Locker_Load();
public Locker_Load()
{
    new rows = cache_num_rows();
    new Cache:lockerCache;

    if(rows)
    {
        lockerCache = cache_save();

        for(new i = 0; i < rows; i++)
        {
            cache_get_value_name_int(i, "ID", lockerData[i][lID]);
            cache_get_value_name_int(i, "WeaponID", lockerData[i][lWeapon]);
            cache_get_value_name_int(i, "Ammo", lockerData[i][lAmmo]);
            cache_get_value_name(i, "Owner", lockerData[i][lOwner]);

            lockerCount++;
        }

        printf("[LOCKER] Loaded %d senjata dari database", rows);

        if(cache_is_valid(lockerCache))
        {
            cache_delete(lockerCache);
            printf("[LOCKER]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[LOCKER]: Cache tidak valid atau sudah dihapus.");
        }
    }
    return 1;
}

stock Locker_AddItem(playerid, weaponid, ammo)
{
    if(lockerCount >= MAX_LOCKER)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Locker penuh!");

    new name[24];
    GetPlayerName(playerid, name, sizeof(name));

    // Cek duplicate di array internal
    for(new i = 0; i < lockerCount; i++)
    {
        if(lockerData[i][lWeapon] == weaponid && strcmp(lockerData[i][lOwner], name, true) == 0)
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Senjata ini sudah ada di locker!");
        }
    }

    // Insert ke database
    new query[256];
    mysql_format(g_SQL, query, sizeof(query),"INSERT IGNORE INTO police_locker (WeaponID, Ammo, Owner) VALUES ('%d','%d','%s')",weaponid, ammo, name);
    mysql_tquery(g_SQL, query);

    // Masukkan ke array internal
    lockerData[lockerCount][lID] = -1; // ID dummy, tidak dipakai
    lockerData[lockerCount][lWeapon] = weaponid;
    lockerData[lockerCount][lAmmo] = ammo;
    format(lockerData[lockerCount][lOwner], 24, "%s", name);
    lockerCount++;

    return ShowTDN(playerid, NOTIFICATION_SUKSES, "Senjata berhasil disimpan di locker polisi.");
}

stock Locker_RemoveAt(index)
{
    if(index < 0 || index >= lockerCount)
        return 0;

    // Gunakan Owner + WeaponID sebagai key delete
    new query[256];
    mysql_format(g_SQL, query, sizeof(query),"DELETE FROM police_locker WHERE Owner='%s' AND WeaponID='%d' LIMIT 1",lockerData[index][lOwner],lockerData[index][lWeapon]);
    mysql_tquery(g_SQL, query);

    // Geser array internal
    for(new i = index; i < lockerCount - 1; i++)
    {
        lockerData[i][lID] = lockerData[i + 1][lID];
        lockerData[i][lWeapon] = lockerData[i + 1][lWeapon];
        lockerData[i][lAmmo] = lockerData[i + 1][lAmmo];
        format(lockerData[i][lOwner], 24, "%s", lockerData[i + 1][lOwner]);
    }
    lockerCount--;
    return 1;
}

stock ResetPlayerCurrentWeapon(playerid)
{
    new weaponid = GetPlayerWeaponEx(playerid);
    if(weaponid == 0) return 0; 

    new weaps[13], ammo[13];
    for(new i = 0; i < 13; i++)
    {
        GetPlayerWeaponData(playerid, i, weaps[i], ammo[i]);
    }

    ResetPlayerWeaponsEx(playerid);
    for(new i = 0; i < 13; i++)
    {
        if(weaps[i] != 0 && weaps[i] != weaponid)
        {
            GivePlayerWeaponEx(playerid, weaps[i], ammo[i]);
        }
    }
    return 1;
}

stock GetWeaponNameById(weaponid, name[], len)
{
    switch (weaponid)
    {
        case 24: format(name, len, "Desert Eagle");
        case 29: format(name, len, "MP5");
        case 30: format(name, len, "AK-47");
        case 31: format(name, len, "M4");
        case 25: format(name, len, "Shotgun");
        default: format(name, len, "Senjata Tidak Dikenal");
    }
    return 1;
}

stock ShowLockerDialog(playerid)
{
    new list[2048], tmp[128];

    if(lockerCount == 0)
    {
        format(list, sizeof(list), "Locker kosong.\n");
    }
    else
    {
        for(new i = 0; i < lockerCount; i++)
        {
            new wname[32];
            GetWeaponNameById(lockerData[i][lWeapon], wname, sizeof(wname));
            format(tmp, sizeof(tmp), ""GRAY"%s %d ammo ("YELLOW"%s)\n", wname, lockerData[i][lAmmo], lockerData[i][lOwner]);
            strcat(list, tmp);
        }
    }

    ShowPlayerDialog(playerid, DIALOG_LOCKER_LIST, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Locker Senjata Polisi", list, "Ambil", "Tutup");
}