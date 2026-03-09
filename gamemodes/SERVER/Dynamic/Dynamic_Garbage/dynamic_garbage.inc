#include <YSI\y_hooks>
#define MAX_DYNAMIC_TRASH  500
new pTimerTakingTrash[MAX_PLAYERS] = {-1, ...};

enum e_trashdata
{
    Float:trashPos[3],
    Float:trashRot[3],
    trashInt,
    trashWorld,
    trashCooldown,
    trashModelID,

    STREAMER_TAG_3D_TEXT_LABEL:trashDynLabel,
    STREAMER_TAG_OBJECT:trashObject
};
new TrashData[MAX_DYNAMIC_TRASH][e_trashdata],
    Iterator:Trash<MAX_DYNAMIC_TRASH>;

TrashNearest(playerid)
{
    foreach(new id : Trash) if(IsPlayerInRangeOfPoint(playerid, 2.0, TrashData[id][trashPos][0], TrashData[id][trashPos][1], TrashData[id][trashPos][2]) && GetPlayerVirtualWorld(playerid) == TrashData[id][trashWorld] && GetPlayerInterior(playerid) == TrashData[id][trashInt])
    {
        return id;
    }
    return -1;
}

/*NearbyTrash(playerid)
{
    foreach(new id : Trash)
    {
        static Float:X, Float:Y, Float:Z, Float:dist;
        GetPlayerPos(playerid, X, Y, Z);

        dist = GetDistanceBetweenPoints(TrashData[id][trashPos][0], TrashData[id][trashPos][1], TrashData[id][trashPos][2], X, Y, Z);

        if(dist <= 350.0)
        {
            return id;
        }
    }
    return -1;
}*/

Trash_Rebuild(id)
{
    if(id != -1)
    {
        if(DestroyDynamic3DTextLabel(TrashData[id][trashDynLabel]))
            TrashData[id][trashDynLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        
        if(DestroyDynamicObject(TrashData[id][trashObject]))
            TrashData[id][trashObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        if(TrashData[id][trashModelID] && TrashData[id][trashPos][0] != 0.0)
        {
            TrashData[id][trashObject] = CreateDynamicObject(TrashData[id][trashModelID], TrashData[id][trashPos][0], TrashData[id][trashPos][1], TrashData[id][trashPos][2], TrashData[id][trashRot][0], TrashData[id][trashRot][1], TrashData[id][trashRot][2], TrashData[id][trashWorld], TrashData[id][trashInt], -1, 50.0);
            TrashData[id][trashDynLabel] = CreateDynamic3DTextLabel("Tekan "GREEN"[Y]"WHITE" untuk memungut sampah!\nDrop item disini untuk membuang!", -1, TrashData[id][trashPos][0], TrashData[id][trashPos][1], TrashData[id][trashPos][2] + 1.5, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, TrashData[id][trashWorld], TrashData[id][trashInt], -1, 3.0);
        }
    }
    return 1;
}

Trash_Save(id)
{
    new query[596];
    mysql_format(g_SQL, query, sizeof(query), "UPDATE `trash` SET `Model`=%d, `Cooldown`=%d, `PosX`=%f, `PosY`=%f, `PosZ`=%f, `RotX`=%f, `RotY`=%f, `RotZ`=%f, `Interior`=%d, `World`=%d WHERE `ID`=%d",
    TrashData[id][trashModelID], TrashData[id][trashCooldown], TrashData[id][trashPos][0], TrashData[id][trashPos][1], TrashData[id][trashPos][2],
    TrashData[id][trashRot][0], TrashData[id][trashRot][1], TrashData[id][trashRot][2], TrashData[id][trashInt], TrashData[id][trashWorld], id);
    mysql_tquery(g_SQL, query);
    return 1;
}
forward LoadTrash();
public LoadTrash()
{
    new rows;
    cache_get_row_count(rows);
    new Cache:Trascache;
    if(rows)
    {
        Trascache = cache_save();

        new id, x = 0;
        while(x < rows)
        {
            cache_get_value_name_int(x, "ID", id);
            cache_get_value_name_int(x, "Model", TrashData[id][trashModelID]);
            cache_get_value_name_int(x, "Cooldown", TrashData[id][trashCooldown]);
            cache_get_value_name_int(x, "Interior", TrashData[id][trashInt]);
            cache_get_value_name_int(x, "World", TrashData[id][trashWorld]);

            cache_get_value_name_float(x, "PosX", TrashData[id][trashPos][0]);
            cache_get_value_name_float(x, "PosY", TrashData[id][trashPos][1]);
            cache_get_value_name_float(x, "PosZ", TrashData[id][trashPos][2]);
            cache_get_value_name_float(x, "RotX", TrashData[id][trashRot][0]);
            cache_get_value_name_float(x, "RotY", TrashData[id][trashRot][1]);
            cache_get_value_name_float(x, "RotZ", TrashData[id][trashRot][2]);

            Trash_Rebuild(id);
            Iter_Add(Trash, id);
            x++;
        }
        printf("[Dynamic Trash]: Jumlah total Trash yang dimuat %d", rows);

        if(cache_is_valid(Trascache))
        {
            cache_delete(Trascache);
            printf("[Dynamic Trash]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Trash]: Cache tidak valid atau sudah dihapus.");
        }
    }
}

TrashBeingEdited(id)
{
    if(!Iter_Contains(Trash, id)) return 0;
    foreach(new i : Player) if(AccountData[i][EditingSAMPAHID] == id) return 1;
    return 0;
}

forward OnTrashCreated(id);
public OnTrashCreated(id)
{
    Trash_Save(id);
    return 1;
}

/* Command */
CMD:addtrash(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    new id = Iter_Free(Trash);
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menambah Dynamic Trash lagi!");
    GetPlayerPos(playerid, TrashData[id][trashPos][0], TrashData[id][trashPos][1], TrashData[id][trashPos][2]);

    TrashData[id][trashModelID] = 1300;
    TrashData[id][trashPos][0] = TrashData[id][trashPos][0] + 2;
    TrashData[id][trashRot][0] = 0;
    TrashData[id][trashRot][1] = 0;
    TrashData[id][trashRot][2] = 0;
    TrashData[id][trashCooldown] = 0;
    TrashData[id][trashInt] = GetPlayerInterior(playerid);
    TrashData[id][trashWorld] = GetPlayerVirtualWorld(playerid);

    Iter_Add(Trash, id);
    Trash_Rebuild(id);
    Info(playerid, "Anda menambah Dynamic Trash ID %d", id);

    new query[598];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `trash` SET `ID`=%d, `Model`=%d, `Cooldown`=%d, `PosX`=%f, `PosY`=%f, `PosZ`=%f, `RotX`=%f, `RotY`=%f, `RotZ`=%f,\
    `Interior`=%d, `World`=%d", id, TrashData[id][trashModelID], TrashData[id][trashCooldown], TrashData[id][trashPos][0], TrashData[id][trashPos][1], TrashData[id][trashPos][2],
    TrashData[id][trashRot][0], TrashData[id][trashRot][1], TrashData[id][trashRot][2], TrashData[id][trashInt], TrashData[id][trashWorld]);
    mysql_tquery(g_SQL, query, "OnTrashCreated", "d", id);
    return 1;
}

CMD:gototrash(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1) return PermissionError(playerid);

    new id;
    if(id < 0 || id >= MAX_DYNAMIC_TRASH) return Error(playerid, "ID Trash tidak valid!");
    if(sscanf(params, "d", id)) return Syntax(playerid, "/gototrash [id]");
    if(!Iter_Contains(Trash, id)) return Error(playerid, "ID Trash tidak ada!");

    SetPlayerPos(playerid, TrashData[id][trashPos][0], TrashData[id][trashPos][1], TrashData[id][trashPos][2]);
    SetPlayerInterior(playerid, TrashData[id][trashInt]);
    SetPlayerVirtualWorld(playerid, TrashData[id][trashWorld]);
    Info(playerid, "Anda teleportasi ke Dynamic Trash ID %d", id);

    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
    return 1;
}

CMD:edittrash(playerid, params[])
{
    static
        id,
        option[24],
        nextParams[125];
    
    if(AccountData[playerid][pAdmin] < 4) return PermissionError(playerid);
    if(id < 0 || id >= MAX_DYNAMIC_TRASH) return Error(playerid, "ID Trash tidak valid!");
    if(sscanf(params, "ds[24]S()[125]", id, option, nextParams)) return Syntax(playerid, "/edittrash [id] [name] (model, position, delete)");
    if(!Iter_Contains(Trash, id)) return Error(playerid, "ID Trash tidak ada!");
    if(!strcmp(option, "model", true))
    {
        new model;
        if(sscanf(nextParams, "d", model)) return Syntax(playerid, "/edittrash [id] [model] [model id]");

        TrashData[id][trashModelID] = model;
        Trash_Rebuild(id);
        Trash_Save(id);
        Info(playerid, "Anda mengubah Model Dynamic Trash ID %d menjadi Model %d", id, model);
    }
    else if(!strcmp(option, "position", true))
    {
        if(!IsPlayerInRangeOfPoint(playerid, 30.0, TrashData[id][trashPos][0], TrashData[id][trashPos][1], TrashData[id][trashPos][2])) return Error(playerid, "Anda tidak berada didekat Dynamic Trash tersebut!");
        if(TrashBeingEdited(playerid)) return Error(playerid, "Anda sedang dalam pengeditan!");
        AccountData[playerid][EditingSAMPAHID] = id;
        EditDynamicObject(playerid, TrashData[id][trashObject]);
        Info(playerid, "Anda sekarang sedang dalam mode pengeditan posisi Trash!");
    }
    else if(!strcmp(option, "delete", true))
    {
        if(DestroyDynamic3DTextLabel(TrashData[id][trashDynLabel])) TrashData[id][trashDynLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        if(DestroyDynamicObject(TrashData[id][trashObject])) TrashData[id][trashObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        TrashData[id][trashModelID] = 0;
        TrashData[id][trashCooldown] = 0;
        TrashData[id][trashInt] = TrashData[id][trashWorld] = 0;
        TrashData[id][trashPos][0] = TrashData[id][trashPos][1] = TrashData[id][trashPos][2] = 0;
        TrashData[id][trashRot][0] = TrashData[id][trashRot][1] = TrashData[id][trashRot][2] = 0;
        
        Iter_Remove(Trash, id);
        Info(playerid, "Anda menghapus Dynamic Trash ID %d", id);

        new query[125];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `trash` WHERE `ID`=%d", id);
        mysql_tquery(g_SQL, query); 
    }
    return 1;
}

/* Trash Functions */
forward TakingTrash(playerid, id);
public TakingTrash(playerid, id)
{
    if(id == -1) return 0;

    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerTakingTrash[playerid]);
        pTimerTakingTrash[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInRangeOfPoint(playerid, 2.0, TrashData[id][trashPos][0], TrashData[id][trashPos][1], TrashData[id][trashPos][2]))
    {
        KillTimer(pTimerTakingTrash[playerid]);
        pTimerTakingTrash[playerid] = -1;
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
        KillTimer(pTimerTakingTrash[playerid]);
        pTimerTakingTrash[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 3)
    {
        KillTimer(pTimerTakingTrash[playerid]);
        pTimerTakingTrash[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        new rands = RandomEx(1, 31), randbotol = RandomEx(1, 6);
        switch(rands)
        {
            case 1..24:
            {
                Inventory_Add(playerid, "Botol", 19570, randbotol);
                ShowItemBox(playerid, sprintf("Received %dx", randbotol), "Botol", 19570);
            }
            case 25..30:
            {
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda tidak mendapatkan apa apa");
            }
        }
        TrashData[id][trashCooldown] = 300;
        Trash_Save(id);
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float:progressvalue;
		progressvalue = AccountData[playerid][ActivityTime] * 103/3;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0; 
    }
    return 1;
}

/* Hook */
hook OnPlayerConnect(playerid)
{
    pTimerTakingTrash[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pTimerTakingTrash[playerid]);
    pTimerTakingTrash[playerid] = -1;
    return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    if(AccountData[playerid][EditingSAMPAHID] != -1 && Iter_Contains(Trash, AccountData[playerid][EditingSAMPAHID]))
    {
        new id = AccountData[playerid][EditingSAMPAHID];
        if(response == EDIT_RESPONSE_FINAL)
        {
            TrashData[id][trashPos][0] = x;
            TrashData[id][trashPos][1] = y;
            TrashData[id][trashPos][2] = z;
            TrashData[id][trashRot][0] = rx;
            TrashData[id][trashRot][1] = ry;
            TrashData[id][trashRot][2] = rz;

            SetDynamicObjectPos(objectid, x, y, z);
            SetDynamicObjectRot(objectid, rx, ry, rz);
            Trash_Rebuild(id);
            Trash_Save(id);
            AccountData[playerid][EditingSAMPAHID] = -1;
        }
        else if(response == EDIT_RESPONSE_CANCEL)
        {
            SetDynamicObjectPos(objectid, x, y, z);
            SetDynamicObjectRot(objectid, rx, ry, rz);
            AccountData[playerid][EditingSAMPAHID] = -1;
        }
    }
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new trashid = TrashNearest(playerid);
        if(trashid != -1)
        {
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
            if(GetGVarInt("TrashTaked", trashid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tempat ini baru saja dipulung orang lain!");

            AccountData[playerid][ActivityTime] = 1;
            SetGVarInt("TrashTaked", 1, trashid);
            
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMULUNG");
            ShowProgressBar(playerid);
            
            pTimerTakingTrash[playerid] = SetTimerEx("TakingTrash", 1000, true, "dd", playerid, trashid);
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            SendRPMeAboveHead(playerid, "Memulung tong sampah didepannya", X11_PLUM1);
        }
    }
    return 1;
}

task TrashCooldown_Update[1000]()
{
    foreach(new id : Trash)
    {
        if(--TrashData[id][trashCooldown] > 0)
        {
            if(!TrashData[id][trashCooldown])
            {
                SetGVarInt("TrashTaked", 0, id);
                TrashData[id][trashCooldown] = 0;
                new query[255];
                mysql_format(g_SQL, query, sizeof(query), "UPDATE `trash` SET `Cooldown`=%d WHERE `ID`=%d", TrashData[id][trashCooldown], id);
                mysql_tquery(g_SQL, query);
            }
        }
        
    }
    return 1;
}