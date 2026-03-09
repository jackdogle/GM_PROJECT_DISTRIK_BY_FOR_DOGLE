#include <YSI_Coding\y_hooks>

stock GetPlantName(value)
{
    static string[126];
    if(value == 1) format(string, sizeof(string), "Padi");
    if(value == 2) format(string, sizeof(string), "Tebu");
    if(value == 3) format(string, sizeof(string), "Cabai");
    return string;
}

stock PlantNearest(playerid)
{
    for (new i = 0; i < MAX_PLANT; i ++) if (PlantData[i][PlantExists] && IsPlayerInRangeOfPoint(playerid, 2.0, PlantData[i][PlantPos][0], PlantData[i][PlantPos][1], PlantData[i][PlantPos][2]))
    {
        if (GetPlayerInterior(playerid) == PlantData[i][PlantInt] && GetPlayerVirtualWorld(playerid) == PlantData[i][PlantVw])
            return i;
    }
    return -1;
}

stock IsAtLadangFarmer(playerid)
{
    if (IsPlayerConnected(playerid))
    {
        if (IsPlayerInDynamicArea(playerid, AreaData[areaLadang]))
        {
            return 1;
        }
    }
    return 0;
}

JavaTR: Plant_Load()
{
    new rows = cache_num_rows();

    if (rows)
    {
        for (new i = 0; i < rows; i ++)
        {
            Iter_Add(Plants, i);

            cache_get_value_name_int(i, "PID", PlantData[i][PlantID]);
            cache_get_value_name_int(i, "PlantType", PlantData[i][PlantType]);
            cache_get_value_name_int(i, "PlantTime", PlantData[i][PlantTime]);
            cache_get_value_name_float(i, "PlantX", PlantData[i][PlantPos][0]);
            cache_get_value_name_float(i, "PlantY", PlantData[i][PlantPos][1]);
            cache_get_value_name_float(i, "PlantZ", PlantData[i][PlantPos][2]);
            cache_get_value_name_float(i, "PlantA", PlantData[i][PlantPos][3]);
            cache_get_value_name_int(i, "PlantInt", PlantData[i][PlantInt]);
            cache_get_value_name_int(i, "PlantVW", PlantData[i][PlantVw]);

            PlantData[i][PlantExists] = true;
            PlantData[i][PlantReady] = false;
            RefreshPlant(i);
        }
        printf("[Plant]: Jumlah total Plant yang dimuat %d", rows);
    }
    return 1;
}

SavePlantData(pid)
{
    new query[400];
    format(query, sizeof(query), "UPDATE `plants` SET `PlantType` = '%d', `PlantTime` = '%d', `PlantX` = '%.4f', `PlantY` = '%.4f', `PlantZ` = '%.4f', `PlantA` = '%.4f', `PlantInt` = '%d', `PlantVW` = '%d' WHERE `PID` = '%d'",
    PlantData[pid][PlantType], PlantData[pid][PlantTime], PlantData[pid][PlantPos][0], PlantData[pid][PlantPos][1], PlantData[pid][PlantPos][2], PlantData[pid][PlantPos][3], PlantData[pid][PlantInt], PlantData[pid][PlantVw], PlantData[pid][PlantID]);

    printf("Plant %d Saved", PlantData[pid][PlantID]);
    return mysql_tquery(g_SQL, query);
}

RefreshPlant(plantid)
{
    if (plantid != -1 && PlantData[plantid][PlantExists])
    {
        if (IsValidDynamicObject(PlantData[plantid][PlantObject])) DestroyDynamicObject(PlantData[plantid][PlantObject]);
        if (IsValidDynamicCP(PlantData[plantid][PlantCP])) DestroyDynamicCP(PlantData[plantid][PlantCP]);

        if (PlantData[plantid][PlantType] == PADI)
        {
            PlantData[plantid][PlantObject] = CreateDynamicObject(804, PlantData[plantid][PlantPos][0], PlantData[plantid][PlantPos][1], PlantData[plantid][PlantPos][2] - 1.0, 0.0, 0.0, PlantData[plantid][PlantPos][3], PlantData[plantid][PlantVw], PlantData[plantid][PlantInt]);
        }
        else if (PlantData[plantid][PlantType] == TEBU)
        {
            PlantData[plantid][PlantObject] = CreateDynamicObject(806, PlantData[plantid][PlantPos][0], PlantData[plantid][PlantPos][1], PlantData[plantid][PlantPos][2] - 1.0, 0.0, 0.0, PlantData[plantid][PlantPos][3], PlantData[plantid][PlantVw], PlantData[plantid][PlantInt]);
        }
        else if (PlantData[plantid][PlantType] == CABAI)
        {
            PlantData[plantid][PlantObject] = CreateDynamicObject(2253, PlantData[plantid][PlantPos][0], PlantData[plantid][PlantPos][1], PlantData[plantid][PlantPos][2] - 1.0, 0.0, 0.0, PlantData[plantid][PlantPos][3], PlantData[plantid][PlantVw], PlantData[plantid][PlantInt]);
        }
        PlantData[plantid][PlantCP] = CreateDynamicCP(PlantData[plantid][PlantPos][0], PlantData[plantid][PlantPos][1], PlantData[plantid][PlantPos][2], 1.5, PlantData[plantid][PlantVw], PlantData[plantid][PlantInt], -1, 5.0);
    }
    return 1;
}

JavaTR: OnPlantCreated(id)
{
    if (id == -1 && !PlantData[id][PlantExists])
        return 0;
    
    PlantData[id][PlantID] = cache_insert_id();
    SavePlantData(id);
    return 1;
}

JavaTR: CreatePlant(playerid, type, time)
{
    new id, Float:x, Float:y, Float:z, Float:ang;
}

timer CreatePlant[3000](playerid, type, time)
{
    new 
        id,
        Float:x,
        Float:y,
        Float:z,
        Float:ang;
    
    TogglePlayerControllable(playerid, 1);
    AccountData[playerid][pHarvest] = -1;
    if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, ang))
    {
        if ((id = Iter_Free(Plants)) != -1)
        {
            Iter_Add(Plants, id);
            PlantData[id][PlantExists] = true;
            PlantData[id][PlantType] = type;

            PlantData[id][PlantPos][0] = x;
            PlantData[id][PlantPos][1] = y;
            PlantData[id][PlantPos][2] = z;
            PlantData[id][PlantPos][3] = ang;
            PlantData[id][PlantTime] = time;

            PlantData[id][PlantInt] = GetPlayerInterior(playerid);
            PlantData[id][PlantVw] = GetPlayerVirtualWorld(playerid);

            mysql_tquery(g_SQL, "INSERT INTO `plants` (`PlantInt`) VALUES(0)", "OnPlantCreated", "d", id);
            RefreshPlant(id);
            return id;
        }
    }
    return -1;
}

stock DestroyPlant(plantid)
{
    if (plantid != -1 && PlantData[plantid][PlantExists])
    {
        static
            string[64];
        
        format(string, sizeof(string), "DELETE FROM `plants` WHERE `PID` = '%d'", PlantData[plantid][PlantID]);
        mysql_tquery(g_SQL, string);

        if (IsValidDynamicObject(PlantData[plantid][PlantObject])) DestroyDynamicObject(PlantData[plantid][PlantObject]);
        if (IsValidDynamicCP(PlantData[plantid][PlantCP])) DestroyDynamicCP(PlantData[plantid][PlantCP]);

        Iter_Remove(Plants, plantid);
        PlantData[plantid][PlantExists] = false;
        PlantData[plantid][PlantID] = 0;
    }
    return 1;
}

timer HarvestPlant[3000](playerid, plantid)
{
    if (PlantNearest(playerid) != plantid && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DUCK && !PlantData[plantid][PlantExists])
        return 0;
    
    TogglePlayerControllable(playerid, 1);
    switch (PlantData[plantid][PlantType])
    {
        case PADI:
        {
            new rand = Random(10, 15);
            Inventory_Add(playerid, "Padi", 804, rand);
            ShowItemBox(playerid, sprintf("Received %dx", rand), "Padi", 804);

            DestroyPlant(plantid);
            AccountData[playerid][pHarvest] = -1;
            PlantData[plantid][PlantHarvest] = 0;
        }
        case TEBU:
        {
            new rand = Random(10, 15);
            Inventory_Add(playerid, "Tebu", 806, rand);
            ShowItemBox(playerid, sprintf("Received %dx", rand), "Tebu", 806);

            DestroyPlant(plantid);
            AccountData[playerid][pHarvest] = -1;
            PlantData[plantid][PlantHarvest] = 0;
        }
        case CABAI:
        {
            new rand = Random(10, 15);
            Inventory_Add(playerid, "Cabe", 2253, rand);
            ShowItemBox(playerid, sprintf("Received %dx", rand), "Cabe", 2253);

            DestroyPlant(plantid);
            AccountData[playerid][pHarvest] = -1;
            PlantData[plantid][PlantHarvest] = 0;
        }
    }
    return 1;
}
