#include <YSI\y_hooks>

enum _:EFarmerData
{
    STREAMER_TAG_MAP_ICON:FarmerIcon[3],
    STREAMER_TAG_3D_TEXT_LABEL:FarmerOlahLabel,
    STREAMER_TAG_3D_TEXT_LABEL:FarmerStoreLabel,
    STREAMER_TAG_AREA:FarmerOlahArea,
};
new PlayerFarmerVars[MAX_PLAYERS][_:EFarmerData];

enum _:EWeedData
{
    weedID,
    weedType,
    bool: weedExists,
    bool: weedHarvest,
    Float: weedPos[3],
    weedTime,
    STREAMER_TAG_OBJECT: weedObject,
    STREAMER_TAG_AREA: weedArea,
};
new WeedData[MAX_WEED][_:EWeedData],
    Iterator:Weeds<MAX_WEED>;

new pTimerHarvest[MAX_PLAYERS] = {-1, ...};
new pTimerOlah[MAX_PLAYERS] = {-1, ...};
new PlayerText: WeedInfoTD[MAX_PLAYERS][1];

LoadVarsFarmer(playerid)
{
    UnloadVarsFarmer(playerid);

    PlayerFarmerVars[playerid][FarmerOlahArea] = CreateDynamicSphere(3.9224, 66.8390, 3.1172, 2.0, -1, -1, playerid);
    PlayerFarmerVars[playerid][FarmerIcon][0] = CreateDynamicMapIcon(-550.636, -184.643, 78.4062, 62, -1, -1, -1, playerid, 8000.0, MAPICON_GLOBAL);
    PlayerFarmerVars[playerid][FarmerIcon][1] = CreateDynamicMapIcon(3.9224, 66.8390, 3.1172, 62, -1, -1, -1, playerid, 8000.0, MAPICON_GLOBAL);
    PlayerFarmerVars[playerid][FarmerIcon][2] = CreateDynamicMapIcon(-376.1269, -1439.9231, 25.7266, 62, -1, -1, -1, playerid, 8000.0, MAPICON_GLOBAL);
    PlayerFarmerVars[playerid][FarmerOlahLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Olah Tanaman", -1, 3.9224, 66.8390, 3.1172 + 0.25, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, playerid);
    PlayerFarmerVars[playerid][FarmerStoreLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Membeli bibit", -1, -547.7806, -185.1288, 78.4063, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, playerid);
}

UnloadVarsFarmer(playerid)
{   
    if(DestroyDynamic3DTextLabel(PlayerFarmerVars[playerid][FarmerOlahLabel]))
        PlayerFarmerVars[playerid][FarmerOlahLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        
    if(DestroyDynamic3DTextLabel(PlayerFarmerVars[playerid][FarmerStoreLabel]))
        PlayerFarmerVars[playerid][FarmerStoreLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    
    forex(x, 3)
    {
        if(DestroyDynamicMapIcon(PlayerFarmerVars[playerid][FarmerIcon][x]))
            PlayerFarmerVars[playerid][FarmerIcon][x] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
    }
    return 1;
}

stock IsALadangField(playerid)
{
    if(IsPlayerInDynamicArea(playerid, AreaData[areaLadang]))
        return 1;
    
    return 0;
}

stock IsPlayerStandInPlant(playerid, range)
{
    if(!IsPlayerConnected(playerid))
        return 0;
    
    foreach(new i:Weeds) if (WeedData[i][weedExists])
    {
        if(IsPlayerInRangeOfPoint(playerid, range, WeedData[i][weedPos][0], WeedData[i][weedPos][1], WeedData[i][weedPos][2]))
        {
            return i;
        }
    }
    return -1;
}

stock Weed_Delete(id)
{
    if(!WeedData[id][weedExists])
        return 0;
    
    mysql_tquery(g_SQL, sprintf("DELETE FROM `weeds` WHERE `ID` = '%d'", WeedData[id][weedID]));

    if(DestroyDynamicObject(WeedData[id][weedObject]))
        WeedData[id][weedObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
    
    if(DestroyDynamicArea(WeedData[id][weedArea]))
        WeedData[id][weedArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
    
    WeedData[id][weedExists] = false;
    WeedData[id][weedType] = 0;
    WeedData[id][weedID] = 0;
    Iter_Remove(Weeds,id);
    return 1;
}

forward HarvestWeed(playerid, wid);
public HarvestWeed(playerid, wid)
{
    if(!WeedData[wid][weedExists])
        return 0;
    
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerHarvest[playerid]);
        pTimerHarvest[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, WeedData[wid][weedArea]))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada didekat tanaman!");
        KillTimer(pTimerHarvest[playerid]);
        pTimerHarvest[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        WeedData[wid][weedHarvest] = false;
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pTimerHarvest[playerid]);
        pTimerHarvest[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        WeedData[wid][weedHarvest] = false;
        return 0;
    }

    if(GetPlayerWeapon(playerid) != WEAPON_KNIFE)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memegang pisau!");
        KillTimer(pTimerHarvest[playerid]);
        pTimerHarvest[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        WeedData[wid][weedHarvest] = false;
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pTimerHarvest[playerid]);
        pTimerHarvest[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        new rands = RandomEx(10, 15);
        if(WeedData[wid][weedType] == 1) //beras
        {
            Inventory_Add(playerid, "Padi", 804, rands);
            ShowItemBox(playerid, sprintf("Received %dx", rands), "Padi", 804);
        }
        else if(WeedData[wid][weedType] == 2) // Tebu
        {
            Inventory_Add(playerid, "Tebu", 806, rands);
            ShowItemBox(playerid, sprintf("Received %dx", rands), "Tebu", 806);
        }
        else if(WeedData[wid][weedType] == 3) // Cabai
        {
            Inventory_Add(playerid, "Cabe", 2253, rands);
            ShowItemBox(playerid, sprintf("Received %dx", rands), "Cabe", 2253);
        }
        Weed_Delete(wid);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        static Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/15;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

stock Weed_Nearest(playerid)
{
    foreach(new i:Weeds) if (WeedData[i][weedExists])
    {
        if(IsPlayerInDynamicArea(playerid, WeedData[i][weedArea]))
        {
            return i;
        }
    }
    return -1;
}

stock Weed_Count()
{
    new count = 0;
    foreach(new i:Weeds) if(WeedData[i][weedExists])
    {
        count++;
    }
    return count;
}

FUNC::PlantWeed(playerid, type)
{
    if(Weed_Count() >= MAX_WEED)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Ladang sudah mencapai batas maksimal tanaman! (M: 1000)");
    
    ClearAnimations(playerid, 1);
    Weed_Create(playerid, type);

    static Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    Streamer_UpdateEx(playerid, x, y, z);
    return 1;
}

stock Weed_Create(playerid, type)
{
    new Float:x, Float:y, Float:z;
    if(GetPlayerPos(playerid, x, y, z))
    {
        forex(i, MAX_WEED) if(!WeedData[i][weedExists])
        {
            WeedData[i][weedExists] = true;
            WeedData[i][weedPos][0] = x;
            WeedData[i][weedPos][1] = y;
            WeedData[i][weedPos][2] = z;
            WeedData[i][weedTime] = 300;
            WeedData[i][weedType] = type;
            WeedData[i][weedHarvest] = false;

            Weed_Refresh(i);
            Iter_Add(Weeds, i);
            new query[178];
            mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `weeds` (`Time`) VALUES ('%d')", WeedData[i][weedTime]);
            mysql_tquery(g_SQL, query, "OnWeedCreated", "d", i);    
            return i;
        }
    }
    return -1;
}

FUNC::OnWeedCreated(id)
{
    WeedData[id][weedID] = cache_insert_id();
    Weed_Save(id);
}

stock Weed_Refresh(plantid)
{
    if(plantid != -1 && WeedData[plantid][weedExists])
    {
        if(DestroyDynamicObject(WeedData[plantid][weedObject]))
            WeedData[plantid][weedObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        if(DestroyDynamicArea(WeedData[plantid][weedArea]))
            WeedData[plantid][weedArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        
        
        if(WeedData[plantid][weedType] == 1) //beras
        {
            WeedData[plantid][weedObject] = CreateDynamicObject(804, WeedData[plantid][weedPos][0], WeedData[plantid][weedPos][1], WeedData[plantid][weedPos][2] + 0.10, 0.0, 0.0, 0.0, -1, -1);
            WeedData[plantid][weedArea] = CreateDynamicSphere( WeedData[plantid][weedPos][0], WeedData[plantid][weedPos][1], WeedData[plantid][weedPos][2], 1.5);
        }
        else if(WeedData[plantid][weedType] == 2) //tebu
        {
            WeedData[plantid][weedObject] = CreateDynamicObject(806, WeedData[plantid][weedPos][0], WeedData[plantid][weedPos][1], WeedData[plantid][weedPos][2] + 0.25, 0.0, 0.0, 0.0, -1, -1);
            WeedData[plantid][weedArea] = CreateDynamicSphere( WeedData[plantid][weedPos][0], WeedData[plantid][weedPos][1], WeedData[plantid][weedPos][2], 1.5);
        }
        else if(WeedData[plantid][weedType] == 3) //cabai
        {
            WeedData[plantid][weedObject] = CreateDynamicObject(2253, WeedData[plantid][weedPos][0], WeedData[plantid][weedPos][1], WeedData[plantid][weedPos][2] - 0.85, 0.0, 0.0, 0.0, -1, -1);
            WeedData[plantid][weedArea] = CreateDynamicSphere( WeedData[plantid][weedPos][0], WeedData[plantid][weedPos][1], WeedData[plantid][weedPos][2], 1.5);
        }
        else if(WeedData[plantid][weedType] == 4) //garam
        {
            WeedData[plantid][weedObject] = CreateDynamicObject(1611, WeedData[plantid][weedPos][0], WeedData[plantid][weedPos][1], WeedData[plantid][weedPos][2] - 0.95, 0.0, 0.0, 0.0, -1, -1);
            WeedData[plantid][weedArea] = CreateDynamicSphere( WeedData[plantid][weedPos][0], WeedData[plantid][weedPos][1], WeedData[plantid][weedPos][2], 1.5);
        }
    }
    return 1;
}

forward Weed_Load();
public Weed_Load()
{
    new rows = cache_num_rows();
    new Cache:Weedcache;
    if(rows)
    {
        Weedcache = cache_save();

        forex(i, rows)
        {
            WeedData[i][weedExists] = true;

            WeedData[i][weedID] = cache_get_field_int(i, "ID");
            WeedData[i][weedType] = cache_get_field_int(i, "Type");
            WeedData[i][weedTime] = cache_get_field_int(i, "Time");
            WeedData[i][weedPos][0] = cache_get_field_float(i, "PosX");
            WeedData[i][weedPos][1] = cache_get_field_float(i, "PosY");
            WeedData[i][weedPos][2] = cache_get_field_float(i, "PosZ");
            Iter_Add(Weeds, i);
            Weed_Refresh(i);
        }
        printf("[Ladang Petani]: Jumlah Tanaman ladang petani yang dimuat %d", rows);

        if(cache_is_valid(Weedcache))
        {
            cache_delete(Weedcache);
            printf("[Dynamic Petani]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Petani]: Cache tidak valid atau sudah dihapus.");
        }
    }
}

stock Weed_Save(id)
{
    new query[596];
    mysql_format(g_SQL, query, sizeof(query), "UPDATE `weeds` SET ");
    mysql_format(g_SQL, query, sizeof(query), "%s`PosX`='%f', ", query, WeedData[id][weedPos][0]);
    mysql_format(g_SQL, query, sizeof(query), "%s`PosY`='%f', ", query, WeedData[id][weedPos][1]);
    mysql_format(g_SQL, query, sizeof(query), "%s`PosZ`='%f', ", query, WeedData[id][weedPos][2]);
    mysql_format(g_SQL, query, sizeof(query), "%s`Time`='%d', ", query, WeedData[id][weedTime]);
    mysql_format(g_SQL, query, sizeof(query), "%s`Type`='%d' ", query, WeedData[id][weedType]);
    mysql_format(g_SQL, query, sizeof(query), "%sWHERE `ID` = '%d'", query, WeedData[id][weedID]);
    mysql_query(g_SQL, query, true);
    return 1;
}

stock GetNameWeed(wid)
{
    new shstr[125];
    if(wid != -1)
    {
        if(WeedData[wid][weedType] == 1)
        {
            shstr = "Tanaman Padi";
        }
        else if(WeedData[wid][weedType] == 2)
        {
            shstr = "Tanaman Tebu";
        }
        else if(WeedData[wid][weedType] == 3)
        {
            shstr = "Tanaman Cabe";
        }
    }
    return shstr;
}

LoadWeedTD(playerid)
{
    WeedInfoTD[playerid][0] = CreatePlayerTextDraw(playerid, 320.000, 351.000, "~w~Waiting_Time:_10~n~~r~NOTE~w~: Tunggu untuk lanjut ke rute berikutnya");
    PlayerTextDrawLetterSize(playerid, WeedInfoTD[playerid][0], 0.300, 1.500);
    PlayerTextDrawAlignment(playerid, WeedInfoTD[playerid][0], 2);
    PlayerTextDrawColor(playerid, WeedInfoTD[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, WeedInfoTD[playerid][0], 1);
    PlayerTextDrawSetOutline(playerid, WeedInfoTD[playerid][0], 1);
    PlayerTextDrawBackgroundColor(playerid, WeedInfoTD[playerid][0], 150);
    PlayerTextDrawFont(playerid, WeedInfoTD[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, WeedInfoTD[playerid][0], 1);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    LoadWeedTD(playerid);
    pTimerHarvest[playerid] = -1;
    pTimerOlah[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pTimerHarvest[playerid]);
    KillTimer(pTimerOlah[playerid]);
    pTimerHarvest[playerid] = -1;
    pTimerOlah[playerid] = -1;
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, -547.7806, -185.1288, 78.4063))
        {
            ShowPlayerDialog(playerid, DIALOG_BUY_SEEDS, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District "WHITE" - Beli Bibit",
            "Jenis Bibit\tHarga\
            \nCabe\t"DARKGREEN"$7\
            \nTebu\t"DARKGREEN"$10\
            \nPadi\t"DARKGREEN"$8", "Pilih", "Batal");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmerVars[playerid][FarmerOlahArea]))
        {
            if(AccountData[playerid][pJob] == JOB_FARMER)
            {
                ShowPlayerDialog(playerid, DIALOG_FARMER_OLAH, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Olah Tanaman",
                "Item\tReqruitment\
                \nSambal\tCabe: 4 | Botol: 1\
                \n"GRAY"Beras\t"GRAY"Padi: 4 | Kain: 1\
                \nGula\tTebu: 4 | Kain: 1\
                \n"GRAY"Garam\t"GRAY"Garam Kristal: 4 | Botol: 1", "Pilih", "Batal");
            }
        }
    }
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && AccountData[playerid][pJob] == JOB_FARMER)
    {
        new wid = Weed_Nearest(playerid);
        if(wid != -1 && IsPlayerInDynamicArea(playerid, WeedData[wid][weedArea]))
        {
            if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus di onfoot!");
            if(WeedData[wid][weedTime] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tanaman ini belum siap panen!");
            if(WeedData[wid][weedHarvest]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tanaman ini sedang dipanen!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
            if(GetPlayerWeapon(playerid) != WEAPON_KNIFE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus memegang pisau!");
            
            SetPlayerFace(playerid, WeedData[wid][weedPos][0], WeedData[wid][weedPos][1]);
            ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 4.1, 1, 0, 0, 1, 0, 1);
            WeedData[wid][weedHarvest] = true;
            AccountData[playerid][ActivityTime] = 1;
            pTimerHarvest[playerid] = SetTimerEx("HarvestWeed", 1000, true, "dd", playerid, wid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMANEN");
            ShowProgressBar(playerid);
            SendRPMeAboveHead(playerid, sprintf("Memanen %s dengan bantuan tangan dan pisau", GetNameWeed(wid)), X11_PLUM1);
        }   
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_BUY_SEEDS:
        {
            if(!response) return 1;
            if(!IsPlayerInRangeOfPoint(playerid, 2.0, -547.7806, -185.1288, 78.4063)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat pembelian bibit!");
            switch(listitem)
            {
                case 0:// cabe
                {
                    ShowPlayerDialog(playerid, DIALOG_BIBIT_CABE, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Bibit Cabe", 
                    ""WHITE"Anda akan membeli "YELLOW"bibit cabe"WHITE" seharga "DARKGREEN"$7/bibit\
                    \n"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
                }
                case 1:// tebu
                {
                    ShowPlayerDialog(playerid, DIALOG_BIBIT_TEBU, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Bibit Tebu", 
                    ""WHITE"Anda akan membeli "YELLOW"bibit tebu"WHITE" seharga "DARKGREEN"$10/bibit\
                    \n"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
                }
                case 2:// padi
                {
                    ShowPlayerDialog(playerid, DIALOG_BIBIT_PADI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Bibit Padi", 
                    ""WHITE"Anda akan membeli "YELLOW"bibit padi"WHITE" seharga "DARKGREEN"$8/bibit\
                    \n"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
                }
            }
        }
        case DIALOG_BIBIT_CABE:
        {
            if(!response) return 1;
            
            if(isnull(inputtext))
            {
                return ShowPlayerDialog(playerid, DIALOG_BIBIT_CABE, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Bibit Cabe", 
                ""WHITE"ERROR: Tidak dapat diisi kosong!\nAnda akan membeli "YELLOW"bibit cabe"WHITE" seharga "DARKGREEN"$7/bibit\
                \n"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
            }

            if(!IsNumeric(inputtext))
            {
                return ShowPlayerDialog(playerid, DIALOG_BIBIT_CABE, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Bibit Cabe", 
                ""WHITE"ERROR: Hanya dapat diisi angka!\nAnda akan membeli "YELLOW"bibit cabe"WHITE" seharga "DARKGREEN"$7/bibit\
                \n"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
            }

            if(strval(inputtext) < 1 || strval(inputtext) > strval(inputtext) * 7)
            {
                return ShowPlayerDialog(playerid, DIALOG_BIBIT_CABE, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Bibit Cabe", 
                ""WHITE"ERROR: Jumlah tidak valid atau uang anda tidak cukup!\nAnda akan membeli "YELLOW"bibit cabe"WHITE" seharga "DARKGREEN"$7/bibit\
                \n"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
            }
            new quantity = strval(inputtext);
            new value = quantity * 7;
            
            if(AccountData[playerid][pMoney] < value) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
            if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
            TakeMoney(playerid, value);

            Inventory_Add(playerid, "Bibit Cabe", 2663, quantity);
            ShowItemBox(playerid, sprintf("Received %dx", quantity), "Bibit Cabe", 2663);
        }
        case DIALOG_BIBIT_TEBU:
        {
            if(!response) return 1;
            
            if(isnull(inputtext))
            {
                return ShowPlayerDialog(playerid, DIALOG_BIBIT_TEBU, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Bibit Tebu", 
                ""WHITE"ERROR: Tidak dapat diisi kosong!\nAnda akan membeli "YELLOW"bibit tebu"WHITE" seharga "DARKGREEN"$10/bibit\
                \n"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
            }

            if(!IsNumeric(inputtext))
            {
                return ShowPlayerDialog(playerid, DIALOG_BIBIT_TEBU, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Bibit Tebu", 
                ""WHITE"ERROR: Hanya dapat diisi angka!\nAnda akan membeli "YELLOW"bibit tebu"WHITE" seharga "DARKGREEN"$10/bibit\
                \n"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
            }

            if(strval(inputtext) < 1 || strval(inputtext) > strval(inputtext) * 10)
            {
                return ShowPlayerDialog(playerid, DIALOG_BIBIT_TEBU, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Bibit Tebu", 
                ""WHITE"ERROR: Jumlah tidak valid atau uang anda tidak cukup!\nAnda akan membeli "YELLOW"bibit tebu"WHITE" seharga "DARKGREEN"$10/bibit\
                \n"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
            }
            new quantity = strval(inputtext);
            new value = quantity * 10;
            
            if(AccountData[playerid][pMoney] < value) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
            if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
            TakeMoney(playerid, value);

            Inventory_Add(playerid, "Bibit Tebu", 2663, quantity);
            ShowItemBox(playerid, sprintf("Received %dx", quantity), "Bibit Tebu", 2663);
        }
        case DIALOG_BIBIT_PADI:
        {
            if(!response) return 1;
            
            if(isnull(inputtext))
            {
                return ShowPlayerDialog(playerid, DIALOG_BIBIT_PADI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Bibit Padi", 
                ""WHITE"ERROR: Tidak dapat diisi kosong!\nAnda akan membeli "YELLOW"bibit padi"WHITE" seharga "DARKGREEN"$8/bibit\
                \n"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
            }

            if(!IsNumeric(inputtext))
            {
                return ShowPlayerDialog(playerid, DIALOG_BIBIT_PADI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Bibit Padi", 
                ""WHITE"ERROR: Hanya dapat diisi angka!\nAnda akan membeli "YELLOW"bibit padi"WHITE" seharga "DARKGREEN"$8/bibit\
                \n"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
            }

            if(strval(inputtext) < 1 || strval(inputtext) > strval(inputtext) * 8)
            {
                return ShowPlayerDialog(playerid, DIALOG_BIBIT_PADI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Bibit Padi", 
                ""WHITE"ERROR: Jumlah tidak valid!\nAnda akan membeli "YELLOW"bibit padi"WHITE" seharga "DARKGREEN"$8/bibit\
                \n"YELLOW"(Masukkan berapa banyak bibit yang ingin anda beli):", "Input", "Batal");
            }
            new quantity = strval(inputtext);
            new value = quantity * 8;
            
            if(AccountData[playerid][pMoney] < value) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
            if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
            TakeMoney(playerid, value);

            Inventory_Add(playerid, "Bibit Padi", 2663, quantity);
            ShowItemBox(playerid, sprintf("Received %dx", quantity), "Bibit Padi", 2663);
        }
        case DIALOG_FARMER_OLAH:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pJob] != JOB_FARMER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
            switch(listitem)
            {
                case 0: //sambal
                {
                    if(Inventory_Count(playerid, "Cabe") < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Cabe tidak mencukupi!");

                    AccountData[playerid][ActivityTime] = 1;
                    pTimerOlah[playerid] = SetTimerEx("PlantProcessed", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH TANAMAN");
                    ShowProgressBar(playerid);
                    ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
                case 1: // Beras
                {
                    if(Inventory_Count(playerid, "Padi") < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Padi tidak mencukupi!");

                    AccountData[playerid][ActivityTime] = 1;
                    pTimerOlah[playerid] = SetTimerEx("PlantProcessed", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH TANAMAN");
                    ShowProgressBar(playerid);
                    ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
                case 2: //Gula
                {
                    if(Inventory_Count(playerid, "Tebu") < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tebu tidak mencukupi!");

                    AccountData[playerid][ActivityTime] = 1;
                    pTimerOlah[playerid] = SetTimerEx("PlantProcessed", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH TANAMAN");
                    ShowProgressBar(playerid);
                    ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
                case 3: // Garam
                {
                    if(Inventory_Count(playerid, "Garam Kristal") < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Garam Kristal tidak mencukupi!");

                    AccountData[playerid][ActivityTime] = 1;
                    pTimerOlah[playerid] = SetTimerEx("PlantProcessed", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH TANAMAN");
                    ShowProgressBar(playerid);
                    ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
            }
            AccountData[playerid][pTempOlah] = listitem;
        }
    }
    return 1;
}

ptask WeedUpdate[1000](playerid)
{
    foreach(new i:Weeds) if (WeedData[i][weedExists])
    {
        new times[3];
        if(--WeedData[i][weedTime] > 0)
        {
            GetElapsedTime(WeedData[i][weedTime], times[0], times[1], times[2]);
            if(!WeedData[i][weedTime])
            {
                WeedData[i][weedTime] = 0;
                Weed_Save(i);
            }
            
        }
    }
    return 1;
}

ptask PlantTimerCheck[1000](playerid)
{
    if(!AccountData[playerid][pSpawned])
        return 0;

    if(IsPlayerStandInPlant(playerid, 2) != -1)
    {
        static 
            hours, minutes, seconds,
            plantid, display[125];
        
        plantid = IsPlayerStandInPlant(playerid, 2);
        GetElapsedTime(WeedData[plantid][weedTime], hours, minutes, seconds);

        if(WeedData[plantid][weedTime] > 0) format(display, sizeof(display), "~y~%s~n~~p~Pertumbuhan: ~b~%02d:%02d", GetNameWeed(plantid), minutes, seconds);
        else format(display, sizeof(display), "~y~%s~n~~g~Siap Panen!", GetNameWeed(plantid));

        PlayerTextDrawSetString(playerid, WeedInfoTD[playerid][0], display);
        PlayerTextDrawShow(playerid, WeedInfoTD[playerid][0]);
    }
    else 
    {
        PlayerTextDrawHide(playerid, WeedInfoTD[playerid][0]);
    }
    return 1;
}

forward PlantProcessed(playerid);
public PlantProcessed(playerid)
{
    if(!IsPlayerConnected(playerid))    
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerFarmerVars[playerid][FarmerOlahArea]))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak diarea pengolahan!");
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 145)
    {
        KillTimer(pTimerOlah[playerid]);
        pTimerOlah[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
        switch(AccountData[playerid][pTempOlah])
        {
            case 0: //Sambal
            {
                Inventory_Remove(playerid, "Cabe", 4);
                Inventory_Add(playerid, "Sambal", 11722);
                ShowItemBox(playerid, "Removed 4x", "Cabe", 2253);
                ShowItemBox(playerid, "Received 1x", "Sambal", 11722);
            }
            case 1: // beras
            {
                Inventory_Remove(playerid, "Padi", 4);
                Inventory_Add(playerid, "Beras", 2060);
                ShowItemBox(playerid, "Removed 4x", "Padi", 804);
                ShowItemBox(playerid, "Received 1x", "Beras", 2060);
            }
            case 2: //Tebu
            {
                Inventory_Remove(playerid, "Tebu", 4);
                Inventory_Add(playerid, "Gula", 1575);
                ShowItemBox(playerid, "Removed 4x", "Tebu", 806);
                ShowItemBox(playerid, "Received 1x", "Gula", 1575);
            }
            case 3: // Garam
            {
                Inventory_Remove(playerid, "Garam Kristal", 4);
                Inventory_Add(playerid, "Garam", 1279);
                ShowItemBox(playerid, "Removed 4x", "Garam Kristal", 1611);
                ShowItemBox(playerid, "Received 1x", "Garam", 1279);
            }
        }
        AccountData[playerid][pTempOlah] = -1;
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 14.5;

        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/145;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}