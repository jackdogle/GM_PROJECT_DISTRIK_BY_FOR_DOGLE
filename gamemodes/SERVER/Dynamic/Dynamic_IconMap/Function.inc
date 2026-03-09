CreateDynamicIcon(playerid, type)
{
    static 
        Float: x,
        Float: y,
        Float: z;

    if (GetPlayerPos(playerid, x, y, z))
    {
        for (new i = 0; i != MAX_DYNAMIC_ICON; i ++)
        {
            if (!IconInfo[i][iconExists])
            {
                IconInfo[i][iconExists] = true;
                IconInfo[i][iconModel] = type;

                IconInfo[i][iconLocation][0] = x;
                IconInfo[i][iconLocation][1] = y;
                IconInfo[i][iconLocation][2] = z;

                IconInfo[i][iconInterior] = GetPlayerInterior(playerid);
                IconInfo[i][iconWorld] = GetPlayerVirtualWorld(playerid);

                RefreshDynamicIcon(i);
                mysql_tquery(g_SQL, "INSERT INTO `icons` (`iconInterior`) VALUES(0)", "OnIconCreated", "d", i);

                return i;
            }
        }
    }
    return -1;
}

JavaTR: Icons_Load()
{
    new rows = cache_num_rows();

    new Cache:Icncache;

    if (rows)
    {
        Icncache = cache_save();

        for (new i; i < rows; i ++)
        {
            cache_get_value_name_int(i, "iconID", IconInfo[i][iconID]);
            cache_get_value_name_int(i, "iconType", IconInfo[i][iconModel]);
            cache_get_value_name_float(i, "iconLocationX", IconInfo[i][iconLocation][0]);
            cache_get_value_name_float(i, "iconLocationY", IconInfo[i][iconLocation][1]);
            cache_get_value_name_float(i, "iconLocationZ", IconInfo[i][iconLocation][2]);
            cache_get_value_name_int(i, "iconInterior", IconInfo[i][iconInterior]);
            cache_get_value_name_int(i, "iconWorld", IconInfo[i][iconWorld]);
            IconInfo[i][iconExists] = true;
            RefreshDynamicIcon(i);
        }
        printf("[Dynamic Map Icon]: Jumlah total Icon Map yang dimuat %d.", rows);

        if(cache_is_valid(Icncache))
        {
            cache_delete(Icncache);
            printf("[Dynamic Map Icon]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Map Icon]: Cache tidak valid atau sudah dihapus.");
        }
    }
    return 1;
}

SaveDynamicIcon(iconid)
{
    new query[400];
	format(query, sizeof(query), "UPDATE `icons` SET `iconType` = '%d', `iconLocationX` = '%.4f', `iconLocationY` = '%.4f', `iconLocationZ` = '%.4f', `iconInterior` = '%d', `iconWorld` = '%d' WHERE `iconID` = '%d'",
	    IconInfo[iconid][iconModel],
	    IconInfo[iconid][iconLocation][0],
	    IconInfo[iconid][iconLocation][1],
	    IconInfo[iconid][iconLocation][2],
	    IconInfo[iconid][iconInterior],
	    IconInfo[iconid][iconWorld],
	    IconInfo[iconid][iconID]
	);
	return mysql_tquery(g_SQL, query);
}

DeleteDynamicIcon(iconid)
{
    if (iconid != -1 && IconInfo[iconid][iconExists])
    {
        new
            string[64];
        
        format(string, sizeof(string), "DELETE FROM `icons` WHERE `iconID` = '%d'", IconInfo[iconid][iconID]);
        mysql_tquery(g_SQL, string);

        if (IsValidDynamicMapIcon(IconInfo[iconid][iconObject]))
            DestroyDynamicMapIcon(IconInfo[iconid][iconObject]);

        IconInfo[iconid][iconExists] = false;
        IconInfo[iconid][iconModel] = 0;
        IconInfo[iconid][iconID] = 0;
    }
    return 1;
}

RefreshDynamicIcon(iconid)
{
	if (iconid != -1 && IconInfo[iconid][iconExists])
	{
        for (new i = 0; i < 3; i ++) {
            if(IsValidDynamicMapIcon(IconInfo[iconid][iconObject]))
                DestroyDynamicMapIcon(IconInfo[iconid][iconObject]);
		}

        IconInfo[iconid][iconObject] = CreateDynamicMapIcon(IconInfo[iconid][iconLocation][0], IconInfo[iconid][iconLocation][1], IconInfo[iconid][iconLocation][2], IconInfo[iconid][iconModel], -1, IconInfo[iconid][iconWorld], IconInfo[iconid][iconInterior], -1, 500.0, MAPICON_GLOBAL, -1, 1);
	}
	return 1;
}
