#include <YSI\y_hooks>
#define MAX_DYNAMIC_DEER (50)

enum e_hunting
{
    Float:DeerPOS[3],
    Float:DeerROT[3],

    STREAMER_TAG_OBJECT:DeerObject,
    STREAMER_TAG_AREA:HuntArea,
    STREAMER_TAG_3D_TEXT_LABEL:DeerLabel,

    DeerTime,
    DeerInterior,
    DeerWorld,
    DeerShoot,
    DeerLabelText[128]
};
new HuntData[MAX_DYNAMIC_DEER][e_hunting],
    Iterator:Hunt<MAX_DYNAMIC_DEER>;

/* Vars */
new bool: DurringHunting[MAX_PLAYERS];
new pTimerTakeRusa[MAX_PLAYERS] = {-1, ...};
new WeaponHunting = 34;

forward LoadDeer();
public LoadDeer()
{
    new id, rows = cache_num_rows();
    new Cache:Deercache;
    if(rows)
    {
        Deercache = cache_save();

        for(new i = 0; i < rows; i ++)
        {
            cache_get_value_name_int(i, "DeerID", id);

            cache_get_value_name_int(i, "DeerInterior", HuntData[id][DeerInterior]);
            cache_get_value_name_int(i, "DeerWorld", HuntData[id][DeerWorld]);
            cache_get_value_name_int(i, "DeerTime", HuntData[id][DeerTime]);

            cache_get_value_name_float(i, "DeerX", HuntData[id][DeerPOS][0]);
            cache_get_value_name_float(i, "DeerY", HuntData[id][DeerPOS][1]);
            cache_get_value_name_float(i, "DeerZ", HuntData[id][DeerPOS][2]);
            cache_get_value_name_float(i, "DeerRX", HuntData[id][DeerROT][0]);
            cache_get_value_name_float(i, "DeerRY", HuntData[id][DeerROT][1]);
            cache_get_value_name_float(i, "DeerRZ", HuntData[id][DeerROT][2]);
            
            HuntData[id][HuntArea] = CreateDynamicRectangle(-654.199951171875, -2392.10009765625, -399.199951171875, -2217.10009765625);
            HuntRefresh(id);
            Iter_Add(Hunt, id);
        }
        printf("[Dynamic Deer]: Jumlah total Rusa yang dimuat %d", rows);

        if(cache_is_valid(Deercache))
        {
            cache_delete(Deercache);
            printf("[Dynamic Deer]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Deer]: Cache tidak valid atau sudah dihapus.");
        }
    }
    return 1;
}

HuntRefresh(id)
{
    if(id != -1)
    {
        if(IsValidDynamicObject(HuntData[id][DeerObject]))
            DestroyDynamicObject(HuntData[id][DeerObject]);
        
        if(IsValidDynamic3DTextLabel(HuntData[id][DeerLabel]))
            DestroyDynamic3DTextLabel(HuntData[id][DeerLabel]);
        
        if(HuntData[id][DeerPOS][0] != 0.0 || HuntData[id][DeerPOS][1] != 0.0 || HuntData[id][DeerPOS][2] != 0.0)
        {
            HuntData[id][DeerObject] = CreateDynamicObject(19315, HuntData[id][DeerPOS][0], HuntData[id][DeerPOS][1], HuntData[id][DeerPOS][2], HuntData[id][DeerROT][0], HuntData[id][DeerROT][1], HuntData[id][DeerROT][2], HuntData[id][DeerWorld], HuntData[id][DeerInterior], -1, 150.0, 150.0);
            HuntData[id][DeerLabel] = CreateDynamic3DTextLabel("Rusa\n"GREEN"Tersedia", -1, HuntData[id][DeerPOS][0], HuntData[id][DeerPOS][1], HuntData[id][DeerPOS][2] + 0.8, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
        }
    }
    return 1;
}

HuntNearest(playerid)
{
    foreach(new i : Hunt) if (IsPlayerInRangeOfPoint(playerid, 2.5, HuntData[i][DeerPOS][0], HuntData[i][DeerPOS][1], HuntData[i][DeerPOS][2]))
    {
        return i;
    }
    return -1;
}

HuntSave(id)
{
    new shstr[596];
    format(shstr, sizeof(shstr), "UPDATE `hunting` SET `DeerX`=%f, `DeerY`=%f, `DeerZ`=%f, `DeerRX`=%f, `DeerRY`=%f, `DeerRZ`=%f, `DeerInterior`=%d, `DeerWorld`=%d, `DeerTime`=%d WHERE `DeerID`=%d", HuntData[id][DeerPOS][0], HuntData[id][DeerPOS][1], HuntData[id][DeerPOS][2], HuntData[id][DeerROT][0], HuntData[id][DeerROT][1], HuntData[id][DeerROT][2], HuntData[id][DeerInterior], HuntData[id][DeerWorld], HuntData[id][DeerTime],
    id);
    return mysql_tquery(g_SQL, shstr);
}

Hunt_BeingEdited(id)
{
    if(!Iter_Contains(Hunt, id)) 
        return 0;
    
    foreach(new i : Player) if (AccountData[i][EditingDeerID] == id) return 1;
    return 0;
}

CMD:adddeer(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    new 
        id = Iter_Free(Hunt),
        Float:X,
        Float:Y,
        Float:Z,
        twsmk[596];
    
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menambah rusa lagi!");
    GetPlayerPos(playerid, X, Y, Z);

    HuntData[id][DeerPOS][0] = X;
    HuntData[id][DeerPOS][1] = Y;
    HuntData[id][DeerPOS][2] = Z;
    HuntData[id][DeerROT][0] = HuntData[id][DeerROT][1] = HuntData[id][DeerROT][2] = 0.0;
    HuntData[id][DeerInterior] = GetPlayerInterior(playerid);
    HuntData[id][DeerWorld] = GetPlayerVirtualWorld(playerid);
    HuntData[id][DeerTime] = 0;
    HuntData[id][DeerShoot] = 0;

    HuntRefresh(id);
    Iter_Add(Hunt, id);

    mysql_format(g_SQL, twsmk, sizeof(twsmk), "INSERT INTO `hunting` SET `DeerID`=%d, `DeerX`=%f, `DeerY`=%f, `DeerZ`=%f, `DeerRX`=%f, `DeerRY`=%f, `DeerRZ`=%f, \
    `DeerInterior`=%d, `DeerWorld`=%d, `DeerTime`=%d", id, HuntData[id][DeerPOS][0], HuntData[id][DeerPOS][1], HuntData[id][DeerPOS][2], HuntData[id][DeerROT][0],
    HuntData[id][DeerROT][1], HuntData[id][DeerROT][2], HuntData[id][DeerInterior], HuntData[id][DeerWorld],HuntData[id][DeerTime]);
    mysql_tquery(g_SQL, twsmk, "OnDeerCreated", "dd", playerid, id);
    return 1;
}

CMD:editdeer(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);
    if(AccountData[playerid][EditingDeerID] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda masih dalam pengeditan Deer!");
    
    new 
        id
    ;
    if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/edithunt [id deer]");
    if(!Iter_Contains(Hunt, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Deer tidak ada!");
    if(id < 0 || id > MAX_DYNAMIC_DEER) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Deer tidak valid!");
    if(!IsPlayerInRangeOfPoint(playerid, 15.0, HuntData[id][DeerPOS][0], HuntData[id][DeerPOS][1], HuntData[id][DeerPOS][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak didekat dynamic deer!");
    AccountData[playerid][EditingDeerID] = id;
    EditDynamicObject(playerid, HuntData[id][DeerObject]);
    return 1;
}

CMD:removedeer(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    new id, icsr[255];
    if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/removehunt [id]");
    if(!Iter_Contains(Hunt, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Deer tidak ada!");
    if(id < 0 || id > MAX_DYNAMIC_DEER) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Deer tidak valid!");
    if(Hunt_BeingEdited(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda dalam mode pengeditan!");

    HuntData[id][DeerPOS][0] = HuntData[id][DeerPOS][1] = HuntData[id][DeerPOS][2] = 0.0;
    HuntData[id][DeerROT][0] = HuntData[id][DeerROT][1] = HuntData[id][DeerROT][2] = 0.0;
    HuntData[id][DeerInterior] = HuntData[id][DeerWorld] = 0;
    HuntData[id][DeerTime] = 0;

    HuntRefresh(id);
    Iter_Remove(Hunt, id);

    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah Menghapus Dynamic Hunt ID: %d", GetAdminName(playerid), id);
    mysql_format(g_SQL, icsr, sizeof(icsr), "DELETE FROM `hunting` WHERE `DeerID`=%d", id);
    mysql_tquery(g_SQL, icsr);
    return 1;
}

CMD:gotodeer(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 1) return PermissionError(playerid);

    new id;
    if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotodeer [id]");
    if(!Iter_Contains(Hunt, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Rusa tidak ada!");
    if(id < 0 || id >= MAX_DYNAMIC_DEER) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Rusa tidak valid!");

    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" teleportasi ke Dynamic Deer ID: %d.", GetAdminName(playerid), id);
    SetPlayerPos(playerid, HuntData[id][DeerPOS][0], HuntData[id][DeerPOS][1] + 0.2, HuntData[id][DeerPOS][2]);
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    return 1;
}

forward OnDeerCreated(playerid, id);
public OnDeerCreated(playerid, id)
{
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah Membuat Dynamic Deer ID: %d.", GetAdminName(playerid), id);
    HuntSave(id);
    return 1;
}

/* Commands */
CMD:hunt(playerid, params[])
{
    if(!IsPlayerInDynamicArea(playerid, HuntingArea[Hunting])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di zona hunting!");

    if(!DurringHunting[playerid]) // pastikan pemain ini sebelumnya tidak sedang dalam mode hunting
    {
        DurringHunting[playerid] = true;

        //Berikan dia senjata hunting
        GivePlayerWeapon(playerid, WeaponHunting, 100);

        ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil masuk ke mode hunting");
    }
    else ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah didalam mode hunting!");
    return 1;
}

/* Hooks */
hook OnPlayerConnected(playerid)
{
    DurringHunting[playerid] = false;
    pTimerTakeRusa[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(DurringHunting[playerid]) {
        RemovePlayerWeapon(playerid, WeaponHunting);
    }
    KillTimer(pTimerTakeRusa[playerid]);
    DurringHunting[playerid] = false;
    pTimerTakeRusa[playerid] = -1;
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(!DurringHunting[playerid])
    {
        if(areaid == HuntingArea[Hunting])
        {
            SendClientMessageEx(playerid, -1, "[i] Anda memasuki Zona Hunting, gunakan "YELLOW"'/hunt'"WHITE" untuk berburu");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == HuntingArea[Hunting])
    {
        if(DurringHunting[playerid])
        {
            DurringHunting[playerid] = false;
            RemovePlayerWeapon(playerid, WeaponHunting);
            SendClientMessageEx(playerid, -1, "[i] Anda keluar dari Zona huntung dan secara otomatis keluar dari mode berburu");
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new id = HuntNearest(playerid);
        if(id > -1) 
        {
            if(IsPlayerInRangeOfPoint(playerid, 1.5, HuntData[id][DeerPOS][0], HuntData[id][DeerPOS][1], HuntData[id][DeerPOS][2]))
            {
                if(HuntData[id][DeerShoot])
                {
                    if(HuntData[id][DeerTime] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Rusa ini telah dipotong oleh seseorang");
                    if(GetPlayerWeapon(playerid) != 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang memegang pisau!");
                    if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu sebentar!");

                    AccountData[playerid][ActivityTime] = 1;
                    HuntData[id][DeerTime] = 1;
                    pTimerTakeRusa[playerid] = SetTimerEx("ProcessRusa", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMOTONG RUSA");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
                }
            }
        }

        if(IsPlayerInRangeOfPoint(playerid, 2.5, -1692.5179, -88.5486, 3.5670))
        {
            static shstr[522];
            format(shstr, sizeof(shstr), "Nama\tQuantity\tHarga Jual\
            \nDaging\t%dx\t$15\
            \n"GRAY"Tanduk\t"GRAY"%dx\t"GRAY"$20\
            \nKulit\t%dx\t$20",
            Inventory_Count(playerid, "Daging"), Inventory_Count(playerid, "Tanduk"), Inventory_Count(playerid, "Kulit"));

            ShowPlayerDialog(playerid, DIALOG_HUNTING_SELL, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Jual Hasil Buru",
            shstr, "Jual", "Batal");
        }
    }
    return 1;
}

hook OnPlayerShootDynObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z)
{
    for(new id = 0; id < MAX_DYNAMIC_DEER; id ++)
    {
        if(DurringHunting[playerid] && GetPlayerWeapon(playerid) == 34 && HuntData[id][DeerObject] == objectid)
        {
            if(HuntData[id][DeerTime] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Rusa ini sudah mati!");

            HuntData[id][DeerShoot] = 1;
            SetDynamicObjectRot(HuntData[id][DeerObject], HuntData[id][DeerROT][0] + 90.0, HuntData[id][DeerROT][1], HuntData[id][DeerROT][2] - 0.5);
            UpdateDynamic3DTextLabelText(HuntData[id][DeerLabel], -1, "Rusa\n"YELLOW"Tertembak\n"WHITE"Tekan "GREEN"Y"WHITE" untuk memotong daging");
        }
    }
    return 1;
}

hook OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
    if(DurringHunting[playerid] && IsPlayerInDynamicArea(playerid, HuntingArea[Hunting]))
    {
        if(damagedid != INVALID_PLAYER_ID && weaponid == WeaponHunting)
        {
            static Float:health, Float:am;
            GetPlayerArmour(damagedid, am);
            GetPlayerHealth(damagedid, health);

            SetPlayerArmourEx(damagedid, am);
            SetPlayerHealthEx(damagedid, health);
            ShowTDN(playerid, NOTIFICATION_ERROR, "Dilarang menembak kepada pemain lain!");
            SetPlayerArmedWeapon(playerid, 0);
            return 0;
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_HUNTING_SELL:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(!IsPlayerInRangeOfPoint(playerid, 2.5, -1692.5179, -88.5486, 3.5670)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ditempat jual hasil berburu!");
            switch(listitem)
            {
                case 0: //daging
                {
                    if(!PlayerHasItem(playerid, "Daging")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki daging untuk dijual!");
                    
                    new value = Inventory_Count(playerid, "Daging");
                    GiveMoney(playerid, (value*15));
                    Inventory_Remove(playerid, "Daging", value);
                    ShowItemBox(playerid, sprintf("Recieved %sx", FormatMoney((value*15))), "Uang", 1212);
                    SendClientMessageEx(playerid, -1, "[i] Anda menjual daging sebanyak "YELLOW"%dx"WHITE" seharga "GREEN"%s", value, FormatMoney((value*15)));
                }
                case 1: // tandu
                {
                    if(!PlayerHasItem(playerid, "Tanduk")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki tanduk untuk dijual!");
                    
                    new value = Inventory_Count(playerid, "Tanduk");
                    GiveMoney(playerid, (value*20));
                    Inventory_Remove(playerid, "Tanduk", value);
                    ShowItemBox(playerid, sprintf("Recieved %sx", FormatMoney((value*20))), "Uang", 1212);
                    SendClientMessageEx(playerid, -1, "[i] Anda menjual tanduk sebanyak "YELLOW"%dx"WHITE" seharga "GREEN"%s", value, FormatMoney((value*20)));
                }
                case 2: // Kulit
                {
                    if(!PlayerHasItem(playerid, "Kulit")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki kulit untuk dijual!");
                    
                    new value = Inventory_Count(playerid, "Kulit");
                    GiveMoney(playerid, (value*20));
                    Inventory_Remove(playerid, "Kulit", value);
                    ShowItemBox(playerid, sprintf("Recieved %sx", FormatMoney((value*20))), "Uang", 1212);
                    SendClientMessageEx(playerid, -1, "[i] Anda menjual kulit sebanyak "YELLOW"%dx"WHITE" seharga "GREEN"%s", value, FormatMoney((value*20)));
                }
            }
        }
    }
    return 1;
}

task HuntingUpdate[1000]()
{
    new hours, minutes, seconds, icsr[128];
    new timeText[64];

    foreach (new i : Hunt)
    {
        if (HuntData[i][DeerTime] == 0) 
            continue; // Lewati jika DeerTime sudah 0

        HuntData[i][DeerTime]--;

        if (HuntData[i][DeerTime] == 0)
        {
            HuntData[i][DeerShoot] = 0;
            HuntData[i][DeerTime] = 0;

            // Update label hanya jika berubah
            UpdateDynamic3DTextLabelText(HuntData[i][DeerLabel], -1, "Rusa\n"GREEN"Tersedia");
            HuntRefresh(i);

            // Update ke database hanya saat DeerTime benar-benar berubah
            mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `hunting` SET `DeerTime`=0 WHERE `DeerID`=%d", i);
            mysql_tquery(g_SQL, icsr);
        }
        else
        {
            GetElapsedTime(HuntData[i][DeerTime], hours, minutes, seconds);

            // Format string hanya jika diperlukan
            format(timeText, sizeof(timeText), "Rusa\n"RED"Tidak tersedia\n"GREEN"%02d:%02d", minutes, seconds);

            // Update label hanya jika teks waktu berubah
            if (strcmp(timeText, HuntData[i][DeerLabelText], false) != 0)
            {
                UpdateDynamic3DTextLabelText(HuntData[i][DeerLabel], -1, timeText);
                format(HuntData[i][DeerLabelText], 128, timeText);
            }
        }
    }
    return 1;
}



/* Functions */
forward ProcessRusa(playerid);
public ProcessRusa(playerid)
{
    new id = HuntNearest(playerid);
    if(id == -1) return 0;

    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerTakeRusa[playerid]);
        pTimerTakeRusa[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInRangeOfPoint(playerid, 2.0, HuntData[id][DeerPOS][0], HuntData[id][DeerPOS][1], HuntData[id][DeerPOS][2]))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak didekat rusa!");
        KillTimer(pTimerTakeRusa[playerid]);
        pTimerTakeRusa[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(GetTotalWeightFloat(playerid) >= 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
        KillTimer(pTimerTakeRusa[playerid]);
        pTimerTakeRusa[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(GetPlayerWeapon(playerid) != 4)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang memegang pisau!");
        KillTimer(pTimerTakeRusa[playerid]);
        pTimerTakeRusa[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda pingsan saat sedang memotong rusa!");
        KillTimer(pTimerTakeRusa[playerid]);
        pTimerTakeRusa[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 10)
    {
        KillTimer(pTimerTakeRusa[playerid]);
        pTimerTakeRusa[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        new rand = RandomEx(1, 10);
        switch(rand)
        {
            case 0..2:
            {
                Inventory_Add(playerid, "Daging", 2806);
                ShowItemBox(playerid, "Received 1x", "Daging", 2806);
            }
            case 3..5:
            {
                Inventory_Add(playerid, "Kulit", 19560);
                ShowItemBox(playerid, "Received 1x", "Kulit", 19560);
            }
            case 6..8:
            {
                Inventory_Add(playerid, "Tanduk", 6865);
                ShowItemBox(playerid, "Received 1x", "Tanduk", 6865);
            }
            case 9..10:
            {
                new randkulit = RandomEx(1, 5);
                Inventory_Add(playerid, "Kulit", 19560, randkulit);
                ShowItemBox(playerid, sprintf("Received %dx", randkulit), "Kulit", 19560);
            }
        }
        GivePlayerXP(playerid, DEFAULT_XP);
        HuntData[id][DeerTime] = 120;
        HuntSave(id);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/10;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}