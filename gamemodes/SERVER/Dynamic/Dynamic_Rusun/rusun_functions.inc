#include <YSI\y_hooks>
#define MAX_DYNAMIC_RUSUN   600

new pTimerRusun[MAX_PLAYERS] = {-1, ...};
new ListedRusunInvite[MAX_PLAYERS][MAX_PLAYERS];

enum e_rusundata
{
    rusunOwner[MAX_PLAYER_NAME],
    rusunOwnerID,
    rusunName[128],
    rusunPrice,
    rusunInteriorInt,
    rusunInterior,
    rusunWorld,

    Float:rusunExtPos[4],
    Float:rusunIntPos[4],

    STREAMER_TAG_PICKUP:rusunPickup,
    STREAMER_TAG_3D_TEXT_LABEL:rusunExtLabel,
    STREAMER_TAG_3D_TEXT_LABEL:rusunIntLabel
};
new RusunData[MAX_DYNAMIC_RUSUN][e_rusundata],
    Iterator:Rusun<MAX_DYNAMIC_RUSUN>;

RusunNearest(playerid)
{
    foreach(new i : Rusun) if(IsPlayerInRangeOfPoint(playerid, 1.5, RusunData[i][rusunExtPos][0], RusunData[i][rusunExtPos][1], RusunData[i][rusunExtPos][2]) && GetPlayerVirtualWorld(playerid) == RusunData[i][rusunWorld] && GetPlayerInterior(playerid) == RusunData[i][rusunInterior])
    {
        return i;
    }
    return -1;
}

Rusun_Inside(playerid)
{
    if(AccountData[playerid][pInRusun] != -1)
    {
        foreach(new i : Rusun) if(i == AccountData[playerid][pInRusun] && GetPlayerInterior(playerid) == RusunData[i][rusunInteriorInt] && GetPlayerVirtualWorld(playerid) > -1)
        {
            return i;
        }
    }
    return -1;
}

/*Rusun_IsOwner(playerid, id)
{
    if(RusunData[id][rusunOwnerID] != -1 && RusunData[id][rusunOwnerID] == AccountData[playerid][pID])
        return 1;
    
    return 0;
}*/

RemainingTime(playerid)
{
    new currentTime = g_RusunTime - gettime();
    new days = currentTime / 86400;
    new hours = (currentTime % 86400) / 3600;
    new minutes = (currentTime % 3600) / 60;
    new seconds = currentTime % 60;

    new shstr[258];
    format(shstr, sizeof(shstr), "Anda memiliki durasi sewa rusun ini selama\
    \n"WHITE"%d hari %d jam %d menit %d detik", days, hours, minutes, seconds);
    
    new rsid = RusunNearest(playerid);
    if(rsid != -1)
    {
        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, sprintf(""TCRP"District  "WHITE"- %s", RusunData[rsid][rusunName]),
        shstr, "Tutup", "");
    }
    return 1;
}

Rusun_Reset(id)
{
    if(id != -1)
    {
        format(RusunData[id][rusunOwner], MAX_PLAYER_NAME, "N/A");
        RusunData[id][rusunOwnerID] = 0;
        Rusun_Refresh(id);
        Rusun_Save(id);
    }
    return 1;
}

Rusun_Save(id)
{
    new query[1218];
    mysql_format(g_SQL, query, sizeof(query), "UPDATE `dynamic_rusun` SET `RusunOwner`='%s', `RusunOwnerID`=%d, `RusunPrice`=%d, `RusunName`='%s', `RusunInterior`=%d, `RusunExtInterior`=%d, `RusunWorld`=%d,\
    `ExtPosX`=%f, `ExtPosY`=%f, `ExtPosZ`=%f, `ExtPosA`=%f, `IntPosX`=%f, `IntPosY`=%f, `IntPosZ`=%f, `IntPosA`=%f WHERE `rID`=%d", RusunData[id][rusunOwner], RusunData[id][rusunOwnerID], RusunData[id][rusunPrice],
    RusunData[id][rusunName], RusunData[id][rusunInteriorInt], RusunData[id][rusunInterior], RusunData[id][rusunWorld], RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2], RusunData[id][rusunExtPos][3],
    RusunData[id][rusunIntPos][0], RusunData[id][rusunIntPos][1], RusunData[id][rusunIntPos][2], RusunData[id][rusunIntPos][3], id);
    mysql_tquery(g_SQL, query);
    return 1;
}

Rusun_Refresh(id)
{
    if(id != -1)
    {
        if(DestroyDynamic3DTextLabel(RusunData[id][rusunExtLabel])) RusunData[id][rusunExtLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        if(DestroyDynamic3DTextLabel(RusunData[id][rusunIntLabel])) RusunData[id][rusunIntLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        if(DestroyDynamicPickup(RusunData[id][rusunPickup])) RusunData[id][rusunPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

        if(RusunData[id][rusunExtPos][0] != 0.0)
        {
            RusunData[id][rusunPickup] = CreateDynamicPickup(19524, 23, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2], RusunData[id][rusunWorld], RusunData[id][rusunInterior], -1, 2.0);
            RusunData[id][rusunExtLabel] = CreateDynamic3DTextLabel("[Tekan "GREEN"Y"WHITE" untuk membuka menu]", -1, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2] + 0.35, 2.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, RusunData[id][rusunWorld], RusunData[id][rusunInterior], -1, 2.0, -1, 0);
        }

        if(RusunData[id][rusunIntPos][0] != 0.0)
        {
            RusunData[id][rusunIntLabel] = CreateDynamic3DTextLabel(""RED"[Y]"WHITE" Keluar", -1, RusunData[id][rusunIntPos][0], RusunData[id][rusunIntPos][1], RusunData[id][rusunIntPos][2] + 0.35, 2.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
        }
    }
    return 1;
}

JavaTR: Rusun_Load()
{
    new rows = cache_num_rows(), id = -1;
    new Cache:Rusncache;
    
    if (rows)
    {
        Rusncache = cache_save();

        for (new i; i < rows; i ++) 
        {
            cache_get_value_name_int(i, "rID", id);
            cache_get_value_name(i, "RusunOwner", RusunData[id][rusunOwner]);
            cache_get_value_name(i, "RusunName", RusunData[id][rusunName]);
            cache_get_value_name_int(i, "RusunOwnerID", RusunData[id][rusunOwnerID]);
            cache_get_value_name_int(i, "RusunPrice", RusunData[id][rusunPrice]);
            cache_get_value_name_int(i, "RusunInterior", RusunData[id][rusunInteriorInt]);
            cache_get_value_name_int(i, "RusunExtInterior", RusunData[id][rusunInterior]);
            cache_get_value_name_int(i, "RusunWorld", RusunData[id][rusunWorld]);
            
            cache_get_value_name_float(i, "ExtPosX", RusunData[id][rusunExtPos][0]);
            cache_get_value_name_float(i, "ExtPosY", RusunData[id][rusunExtPos][1]);
            cache_get_value_name_float(i, "ExtPosZ", RusunData[id][rusunExtPos][2]);
            cache_get_value_name_float(i, "ExtPosA", RusunData[id][rusunExtPos][3]);
            
            cache_get_value_name_float(i, "IntPosX", RusunData[id][rusunIntPos][0]);
            cache_get_value_name_float(i, "IntPosY", RusunData[id][rusunIntPos][1]);
            cache_get_value_name_float(i, "IntPosZ", RusunData[id][rusunIntPos][2]);
            cache_get_value_name_float(i, "IntPosA", RusunData[id][rusunIntPos][3]);

            Rusun_Refresh(id);
            Iter_Add(Rusun, id);
        }
        printf("[Dynamic Rusun]: Jumlah total Rusun yang dimuat %d", rows);

        if(cache_is_valid(Rusncache))
        {
            cache_delete(Rusncache);
            printf("[Dynamic Rusun]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Rusun]: Cache tidak valid atau sudah dihapus.");
        }
    }
    return 1;
}

CMD:addrusun(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    new id = Iter_Free(Rusun);
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menambahkan rusun lagi!");
    
    new
        price,
        name[125],
        Float:x,
        Float:y,
        Float:z,
        Float:a;
    
    if(sscanf(params, "ds[125]", price, name)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addrusun [harga 30 hari] [nama rusun]");
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    format(RusunData[id][rusunName], sizeof(name), name);
    format(RusunData[id][rusunOwner], 16, "N/A");
    RusunData[id][rusunOwnerID] = 0;
    RusunData[id][rusunPrice] = price;
    RusunData[id][rusunExtPos][0] = x;
    RusunData[id][rusunExtPos][1] = y;
    RusunData[id][rusunExtPos][2] = z;
    RusunData[id][rusunExtPos][3] = a;
    RusunData[id][rusunIntPos][0] = 2233.7258;
    RusunData[id][rusunIntPos][1] = -1115.1895;
    RusunData[id][rusunIntPos][2] = 1050.8828;
    RusunData[id][rusunIntPos][3] = 0.1506;
    RusunData[id][rusunInteriorInt] = 5;
    RusunData[id][rusunInterior] = GetPlayerInterior(playerid);
    RusunData[id][rusunWorld] = GetPlayerVirtualWorld(playerid);
    
    Rusun_Refresh(id);
    Iter_Add(Rusun, id);

    new query[596];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `dynamic_rusun` SET `rID`=%d, `RusunOwner`='%s', `RusunOwnerID`=%d, `RusunPrice`=%d, `RusunName`='%s', `ExtPosX`=%f, `ExtPosY`=%f, `ExtPosZ`=%f, `ExtPosA`=%f,\
    `IntPosX`=%f, `IntPosY`=%f, `IntPosZ`=%f, `IntPosA`=%f, `RusunInterior`=%d", id, RusunData[id][rusunOwner], RusunData[id][rusunOwnerID], RusunData[id][rusunPrice], RusunData[id][rusunName], RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2], RusunData[id][rusunExtPos][3],
    RusunData[id][rusunIntPos][0], RusunData[id][rusunIntPos][1], RusunData[id][rusunIntPos][2], RusunData[id][rusunIntPos][3], RusunData[id][rusunInteriorInt]);
    mysql_tquery(g_SQL, query, "OnRusunCreated", "dd", playerid, id);
    return 1;
}

forward OnRusunCreated(playerid, id);
public OnRusunCreated(playerid, id)
{
    Rusun_Save(id);
    Info(playerid, "Anda membuat Dynamic Rusun ID: %d dengan Nama: %s", id, RusunData[id][rusunName]);
    return 1;
}

CMD:gotorusun(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1) return PermissionError(playerid);

    new id;
    if(id < 0 || id >= MAX_DYNAMIC_RUSUN) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Rusun tidak valid!");
    if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotorusun [id]");
    if(!Iter_Contains(Rusun, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Rusun tidak ada!");

    Info(playerid, "Anda teleportasi ke Dynamic Rusun ID: %d", id);
    SetPlayerPosition(playerid, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2], RusunData[id][rusunExtPos][3]);
    SetPlayerInterior(playerid, RusunData[id][rusunInterior]);
    SetPlayerVirtualWorld(playerid, RusunData[id][rusunWorld]);
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
    return 1;
}

CMD:editrusun(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    static
        id,
        option[24],
        nextParams[125];
    
    if(sscanf(params, "ds[24]S()[125]", id, option, nextParams)) 
    {
        Syntax(playerid, "/editrusun [id] [name] (location, price, reset, delete)");
        return 1;
    }
    if(id < 0 || id >= MAX_DYNAMIC_RUSUN) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Rusun tidak valid!");
    if(!Iter_Contains(Rusun, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Rusun tidak ada!");

    if(!strcmp(option, "location", true))
    {
        GetPlayerPos(playerid, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2]);
        GetPlayerFacingAngle(playerid, RusunData[id][rusunExtPos][3]);

        Rusun_Refresh(id);
        Rusun_Save(id);
        Info(playerid, "Anda telah mengubah Posisi Exterior Dynamic Rusun ID: %d", id);
    }
    else if(!strcmp(option, "price", true))
    {
        new value;
        if(sscanf(nextParams, "d", value)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editrusun [id] [price] [harga 30 hari]");

        RusunData[id][rusunPrice] = value;
        Rusun_Refresh(id);
        Rusun_Save(id);
        Info(playerid, "Anda telah mengubah Harga Dynamic Rusun ID %d menjadi "GREEN"%s", id, FormatMoney(value));
    }
    else if(!strcmp(option, "reset", true))
    {
        new playerName[24];
        foreach(new i : Player) if (IsPlayerConnected(i))
        {
            GetPlayerName(i, playerName, MAX_PLAYER_NAME);

            if(strfind(AccountData[i][pName], playerName, true) != -1)
            {
                AccountData[i][pOwnedRusun] = -1;
            }
        }
        mysql_tquery(g_SQL, sprintf("UPDATE `player_characters` SET `Char_HasRusunID`=-1 WHERE `pID`=%d", RusunData[id][rusunOwnerID]));
        Rusun_Reset(id);
        Rusun_Refresh(id);
        Rusun_Save(id);
        Info(playerid, "Anda telah mereset Dynamic Rusun ID %d", id);
    }
    else if(!strcmp(option, "delete", true))
    {
        new playerName[32];
        foreach(new i : Player) if (IsPlayerConnected(i))
        {
            GetPlayerName(i, playerName, MAX_PLAYER_NAME);
            
            if(strfind(AccountData[i][pName], playerName, true) != -1)
            {
                AccountData[i][pOwnedRusun] = -1;
            }
        }
        mysql_tquery(g_SQL, sprintf("UPDATE `player_characters` SET `Char_HasRusunID`=-1 WHERE `pID`=%d", RusunData[id][rusunOwnerID]));

        if(DestroyDynamicPickup(RusunData[id][rusunPickup])) RusunData[id][rusunPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
        if(DestroyDynamic3DTextLabel(RusunData[id][rusunExtLabel])) RusunData[id][rusunExtLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        if(DestroyDynamic3DTextLabel(RusunData[id][rusunIntLabel])) RusunData[id][rusunIntLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        
        RusunData[id][rusunExtPos][0] = RusunData[id][rusunExtPos][1] = RusunData[id][rusunExtPos][2] = RusunData[id][rusunExtPos][3] = 0;
        RusunData[id][rusunIntPos][0] = RusunData[id][rusunIntPos][1] = RusunData[id][rusunIntPos][2] = RusunData[id][rusunIntPos][3] = 0;
        RusunData[id][rusunPrice] = RusunData[id][rusunInterior] = RusunData[id][rusunInteriorInt] = RusunData[id][rusunWorld] = 0;
        
        Iter_Remove(Rusun, id);
        Rusun_Reset(id);
        Rusun_Refresh(id);
        Rusun_Save(id);

        new query[178];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `dynamic_rusun` WHERE `rID`=%d", id);
        mysql_tquery(g_SQL, query);
    }
    return 1;
}

/* Hook System */
hook OnPlayerConnect(playerid)
{
    pTimerRusun[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pTimerRusun[playerid]);
    pTimerRusun[playerid] = -1;
    return 1;
}

hook OnGameModeInit()
{
    CreateDynamicPickup(1275, 23, 2234.7104, -1106.1246, 1050.8828, -1, 5, -1, 10.0);
    CreateDynamic3DTextLabel("[Tekan "GREEN"Y"WHITE" untuk membuka brankas]", -1, 2234.7104, -1106.1246, 1050.8828, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pInRusun] != -1 && IsPlayerInRangeOfPoint(playerid, 1.5, RusunData[AccountData[playerid][pInRusun]][rusunIntPos][0], RusunData[AccountData[playerid][pInRusun]][rusunIntPos][1], RusunData[AccountData[playerid][pInRusun]][rusunIntPos][2]))
        {
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu sampai progress selesai!");
            AccountData[playerid][ActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "KELUAR");
            ShowProgressBar(playerid);
            
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            pTimerRusun[playerid] = SetTimerEx("OutOfRusun", 1000, true, "dd", playerid, AccountData[playerid][pInRusun]);
        }

        if(IsPlayerInRangeOfPoint(playerid, 1.5, 2234.7104, -1106.1246, 1050.8828) && GetPlayerVirtualWorld(playerid) == AccountData[playerid][pInRusun])
        {
            ShowPlayerDialog(playerid, DIALOG_RUSUN_BRANKAS, DIALOG_STYLE_LIST, sprintf(""TCRP"District  "WHITE"- %s", RusunData[AccountData[playerid][pInRusun]][rusunName]),
            "Undang\
            \n"GRAY"Pakaian\
            \nMembuang Pakaian\
            \n"GRAY"Brankas", "Pilih", "Batal");
        }

        new rsid = RusunNearest(playerid), srss[258];
        if(rsid != -1)
        {
            if(RusunData[rsid][rusunOwnerID] != 0)
            {
                if(RusunData[rsid][rusunOwnerID] != AccountData[playerid][pID])
                {
                    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
                    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, sprintf(""TCRP"District  "WHITE"- %s", RusunData[rsid][rusunName]), 
                    "Sudah dimiliki warga lain!", "Tutup", "");
                }
                else
                {
                    AccountData[playerid][pInRusun] = rsid;
                    ShowPlayerDialog(playerid, DIALOG_RUSUN_OWNED, DIALOG_STYLE_LIST, sprintf(""TCRP"District  "WHITE"- %s", RusunData[rsid][rusunName]), 
                    "Masuk\
                    \n"GRAY"Cek status sewa", "Pilih", "Batal");
                }
            }
            else
            {
                AccountData[playerid][pInRusun] = rsid;
                format(srss, sizeof(srss), "Sewa\t"GREEN"%s / bulan", FormatMoney(RusunData[rsid][rusunPrice]));
                ShowPlayerDialog(playerid, DIALOG_RUSUN, DIALOG_STYLE_TABLIST, sprintf(""TCRP"District  "WHITE"- %s", RusunData[rsid][rusunName]),
                srss, "Pilih", "Batal");
            }
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(dialogid == DIALOG_RUSUN)
    {
        if(!response) 
        {
            AccountData[playerid][pInRusun] = -1;
            return 1;    
        }
        new id = AccountData[playerid][pInRusun];

        if(AccountData[playerid][pOwnedRusun] == 1)
        {
            AccountData[playerid][pInRusun] = -1;
            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah menyewa rusun!");
            return 1;
        }
        
        if(AccountData[playerid][pMoney] < RusunData[id][rusunPrice])
        {
            AccountData[playerid][pInRusun] = -1;
            ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
            return 1;
        }

        TakeMoney(playerid, RusunData[id][rusunPrice]);
        GetPlayerName(playerid, RusunData[id][rusunOwner], MAX_PLAYER_NAME);
        RusunData[id][rusunOwnerID] = AccountData[playerid][pID];
        AccountData[playerid][pOwnedRusun] = true;
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menyewa rusun");

        Rusun_Refresh(id);
        Rusun_Save(id);
    }
    else if(dialogid == DIALOG_RUSUN_OWNED)
    {
        if(!response)
        {
            AccountData[playerid][pInRusun] = -1;
            ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            return 1;
        }
        new rsid = AccountData[playerid][pInRusun];

        if(AccountData[playerid][pInjured]) 
        {
            AccountData[playerid][pInRusun] = -1;
            ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            return 1;
        }

        switch(listitem)
        {
            case 0: //entering
            {
                if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu sampai progress selesai!");
                AccountData[playerid][ActivityTime] = 1;
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MASUK");
                ShowProgressBar(playerid);

                ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                pTimerRusun[playerid] = SetTimerEx("EnteringRusun", 1000, true, "dd", playerid, rsid);
            }
            case 1: //cek status sewa
            {
                RemainingTime(playerid);
            }
        }
    }
    else if(dialogid == DIALOG_RUSUN_BRANKAS)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        switch(listitem)
        {
            case 0:
            {
                new id = Rusun_Inside(playerid), frmxt[125], count = 0;
                foreach(new i : Player) if (i != playerid) if(IsPlayerInRangeOfPoint(i, 2.0, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2]))
                {
                    format(frmxt, sizeof(frmxt), "%sPlayer ID: %d\n", frmxt, i);
                    ListedRusunInvite[playerid][count++] = i;
                }

                if(count == 0)
                {
                    PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Undang Teman",
                    "Tidak ada player yang dekat dengan pintu rusun anda!", "Close", "");
                }

                ShowPlayerDialog(playerid, DIALOG_RUSUN_INVITE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Undang Teman", frmxt, "Pilih", "Batal");
            }
            case 1:
            {
                ShowPlayerClothes(playerid);
            }
            case 2:
            {
                DropClothesPlayer(playerid);
            }
            case 3:
            {
                ShowPlayerDialog(playerid, DIALOG_RUSUN_BROPTION, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Brankas",
                "Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Batal");
            }
        }
    }
    else if(dialogid == DIALOG_RUSUN_BROPTION)
    {
        if(!response) 
        {
            return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        }
        new id = Rusun_Inside(playerid);

        if(id == -1)
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang didalam rusun!");
        }

        switch(listitem)
        {
            case 0: //deposit
            {
                RusunBrankas[playerid][rusunbrankasID] = 0;
                RusunBrankas[playerid][rusunbrankasTemp] = EOS;
                RusunBrankas[playerid][rusunbrankasModel] = 0;
                RusunBrankas[playerid][rusunbrankasQuant] = 0;

                new str[1218], amounts, itemname[32], tss[128], Cache:execute;
                format(str, sizeof(str), "Nama Item\tJumlah\tBerat (%.3f/80kg)\n", AccountData[playerid][pRusunCapacity]);
                mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
                execute = mysql_query(g_SQL, tss, true);
                if(cache_num_rows() > 0)
                {
                    for(new x; x < cache_num_rows(); ++x)
                    {
                        cache_get_value_name(x, "invItem", itemname);
                        cache_get_value_name_int(x, "invQuantity", amounts);

                        format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                    }
                    ShowPlayerDialog(playerid, DIALOG_RUSUNVAULT_DEPOSIT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas", str, "Pilih", "Batal");
                }
                else 
                {
                    PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas",
                    "Anda tidak memiliki barang untuk disimpan!", "Tutup", "");
                }
                cache_delete(execute);
            }
            case 1: //withdraw
            {
                new str[2108], amounts, itemname[64], icsr[225], Cache:execute;
                format(str, sizeof(str), "Nama Item\tJumlah\tBerat (%.3f/80kg)\n", AccountData[playerid][pRusunCapacity]);
                mysql_format(g_SQL, icsr, sizeof(icsr), "SELECT * FROM `player_rusunstorage` WHERE `ID`=%d", AccountData[playerid][pID]);
                execute = mysql_query(g_SQL, icsr, true);
                if(cache_num_rows() > 0)
                {
                    for(new x; x < cache_num_rows(); ++x)
                    {
                        cache_get_value_name(x, "rsItemName", itemname);
                        cache_get_value_name_int(x, "rsItemQuantity", amounts);

                        format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                    }
                    ShowPlayerDialog(playerid, DIALOG_RUSUNVAULT_WITHDRAW, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas", str, "Pilih", "Batal");
                }
                else 
                {
                    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas",
                    "Tidak ada barang brankas!", "Tutup", "");
                }
                cache_delete(execute);
            }
        }
    }
    else if(dialogid == DIALOG_RUSUN_INVITE)
    {
        if(!response) return 1;

        new targetid = ListedRusunInvite[playerid][listitem], rsid = Rusun_Inside(playerid);
        if(rsid > -1)
        {
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
            SetPVarInt(targetid, "RusunInviteID", rsid);
            ShowPlayerDialog(targetid, DIALOG_RUSUN_INVITECONF, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Undang Teman",
            "Seseorang mengundang kamu untuk masuk ke dalam rusunnya", "Terima", "Tolak");
        }
    }
    else if(dialogid == DIALOG_RUSUN_INVITECONF)
    {
        if(!response) return 1;
        new rsid = GetPVarInt(playerid, "RusunInviteID");
        if(rsid == -1) return 0;

        if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu sampai progress selesai!");
        AccountData[playerid][ActivityTime] = 1;
        pTimerRusun[playerid] = SetTimerEx("EnteringRusun", 1000, true, "dd", playerid, rsid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MASUK");
        ShowProgressBar(playerid);
        ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
    }
    else if(dialogid == DIALOG_RUSUNVAULT_DEPOSIT)
    {
        new id = Rusun_Inside(playerid);
        if(id == -1)
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang didalam rusun!");
        }

        if(!response)
        {
            return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        }

        if(listitem == -1)
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih barang!");
        }

        new tss[712], Cache:execute;
        mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
        execute = mysql_query(g_SQL, tss, true);
        if(cache_num_rows() > 0)
        {
            if(listitem >= 0 && listitem < cache_num_rows())
            {
                cache_get_value_name(listitem, "invItem", RusunBrankas[playerid][rusunbrankasTemp]);
                cache_get_value_name_int(listitem, "invModel", RusunBrankas[playerid][rusunbrankasModel]);
                cache_get_value_name_int(listitem, "invQuantity", RusunBrankas[playerid][rusunbrankasQuant]);

                new shstr[529];
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon masukkan berapa jumlah yang ingin di simpan:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_RUSUNVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
                shstr, "Input", "Batal");
            }
        }
        cache_delete(execute);
    }
    else if(dialogid == DIALOG_RUSUNVAULT_IN)
    {
        new id = Rusun_Inside(playerid);
        if(id == -1)
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang didalam rusun!");
        }

        if(!response)
        {
            return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        }

        new shstr[512];
        if(isnull(inputtext))
        {
            format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nTidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin di simpan:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_RUSUNVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
            shstr, "Input", "Batal");
            return 1;
        }

        if(!IsNumeric(inputtext))
        {
            format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin di simpan:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_RUSUNVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
            shstr, "Input", "Batal");
            return 1;
        }

        if(strval(inputtext) < 1 || strval(inputtext) > RusunBrankas[playerid][rusunbrankasQuant])
        {
            format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin di simpan:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_RUSUNVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
            shstr, "Input", "Batal");
            return 1;
        }

        new quantity = strval(inputtext);

        if(AccountData[playerid][pRusunCapacity] >= 80)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Brankas rusun anda telah penuh!");
        
        Inventory_Remove(playerid, RusunBrankas[playerid][rusunbrankasTemp], quantity);
        ShowItemBox(playerid, sprintf("Removed %dx", quantity), RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasModel]);
        AddCapacityRusun(playerid, RusunBrankas[playerid][rusunbrankasTemp], quantity);

        new invstr[1218];
        mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `player_rusunstorage` WHERE `ID`=%d AND `rsItemName`='%s'", AccountData[playerid][pID], RusunBrankas[playerid][rusunbrankasTemp]);
        mysql_query(g_SQL, shstr);
        if(cache_num_rows() > 0)
        {
            mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `player_rusunstorage` SET `rsItemQuantity` = `rsItemQuantity` + %d WHERE `ID`=%d AND `rsItemName`='%s'", quantity, AccountData[playerid][pID], RusunBrankas[playerid][rusunbrankasTemp]);
            mysql_tquery(g_SQL, invstr, "OnRusunDeposit", "d", playerid);
        }
        else
        {
            mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `player_rusunstorage` SET `ID`=%d, `rsItemName`='%s', `rsItemModel`=%d, `rsItemQuantity`=%d", AccountData[playerid][pID], RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasModel], quantity);
            mysql_tquery(g_SQL, invstr, "OnRusunDeposit", "d", playerid);
        }
    }
    else if(dialogid == DIALOG_RUSUNVAULT_WITHDRAW)
    {
        new id = Rusun_Inside(playerid);
        if(id == -1)
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang didalam rusun!");
        }

        if(!response)
        {
            return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        }

        if(listitem == -1)
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih barang!");
        }

        new tss[1218], Cache:execute;
        mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `player_rusunstorage` WHERE `ID`=%d", AccountData[playerid][pID]);
        execute = mysql_query(g_SQL, tss, true);
        if(cache_num_rows() > 0)
        {
            if(listitem >= 0 && listitem < cache_num_rows())
            {
                cache_get_value_name_int(listitem, "rsItemID", RusunBrankas[playerid][rusunbrankasID]);
                cache_get_value_name(listitem, "rsItemName", RusunBrankas[playerid][rusunbrankasTemp]);
                cache_get_value_name_int(listitem, "rsItemModel", RusunBrankas[playerid][rusunbrankasModel]);
                cache_get_value_name_int(listitem, "rsItemQuantity", RusunBrankas[playerid][rusunbrankasQuant]);

                new shstr[528];
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nMohon masukkan berapa jumlah yang ingin anda ambil dari brankas:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_RUSUNVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
                shstr, "Input", "Batal");
            }
        }
        cache_delete(execute);
    }
    else if(dialogid == DIALOG_RUSUNVAULT_OUT)
    {
        new id = Rusun_Inside(playerid);
        if(id == -1)
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang didalam rusun!");
        }

        if(!response)
        {
            return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        }

        new shstr[512];
        if(isnull(inputtext))
        {
            format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nTidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin anda ambil dari brankas:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_RUSUNVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
            shstr, "Input", "Batal");
            return 1;
        }

        if(!IsNumeric(inputtext))
        {
            format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin anda ambil dari brankas:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_RUSUNVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
            shstr, "Input", "Batal");
            return 1;
        }

        if(strval(inputtext) < 1 || strval(inputtext) > RusunBrankas[playerid][rusunbrankasQuant])
        {
            format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin anda ambil dari brankas:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_RUSUNVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
            shstr, "Input", "Batal");
            return 1;
        }

        new quantity = strval(inputtext), tss[155];
        if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");

        RusunBrankas[playerid][rusunbrankasQuant] -= quantity;
        if(RusunBrankas[playerid][rusunbrankasQuant] > 0)
        {
            mysql_format(g_SQL, tss, sizeof(tss), "UPDATE `player_rusunstorage` SET `rsItemQuantity`=%d WHERE `rsItemID`=%d", RusunBrankas[playerid][rusunbrankasQuant], RusunBrankas[playerid][rusunbrankasID]);
            mysql_tquery(g_SQL, tss);
        } 
        else 
        {
            mysql_format(g_SQL, tss, sizeof(tss), "DELETE FROM `player_rusunstorage` WHERE `rsItemID`=%d", RusunBrankas[playerid][rusunbrankasID]);
            mysql_tquery(g_SQL, tss);
        }
        Inventory_Add(playerid, RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasModel], quantity);
        ShowItemBox(playerid, sprintf("Received %dx", quantity), RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasModel]);
        ReduceCapacityRusun(playerid, RusunBrankas[playerid][rusunbrankasTemp], quantity);

        RusunBrankas[playerid][rusunbrankasID] = 0;
        RusunBrankas[playerid][rusunbrankasTemp] = EOS;
        RusunBrankas[playerid][rusunbrankasModel] = 0;
        RusunBrankas[playerid][rusunbrankasQuant] = 0;
    }
    return 1;
}

/* Other Functions */
forward EnteringRusun(playerid, id);
public EnteringRusun(playerid, id)
{
    if(id == -1)
        return 0;
    
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerRusun[playerid]);
        pTimerRusun[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInRangeOfPoint(playerid, 1.5, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2]))
    {
        KillTimer(pTimerRusun[playerid]);
        pTimerRusun[playerid] = -1;
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
        KillTimer(pTimerRusun[playerid]);
        pTimerRusun[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 5)
    {
        KillTimer(pTimerRusun[playerid]);
        pTimerRusun[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Player_ToggleTelportAntiCheat(playerid, false);
        SetPlayerPositionEx(playerid, RusunData[id][rusunIntPos][0], RusunData[id][rusunIntPos][1], RusunData[id][rusunIntPos][2], RusunData[id][rusunIntPos][3], 6000);
        SetPlayerInterior(playerid, RusunData[id][rusunInteriorInt]);
        SetPlayerVirtualWorld(playerid, id);
        AccountData[playerid][pInRusun] = id;
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        static Float: progressvalue; 
        progressvalue = AccountData[playerid][ActivityTime]*110/5;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward OutOfRusun(playerid, id);
public OutOfRusun(playerid, id)
{
    if(id == -1)
        return 0;
    
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerRusun[playerid]);
        pTimerRusun[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInRangeOfPoint(playerid, 1.5, RusunData[id][rusunIntPos][0], RusunData[id][rusunIntPos][1], RusunData[id][rusunIntPos][2]))
    {
        KillTimer(pTimerRusun[playerid]);
        pTimerRusun[playerid] = -1;
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
        KillTimer(pTimerRusun[playerid]);
        pTimerRusun[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 5)
    {
        KillTimer(pTimerRusun[playerid]);
        pTimerRusun[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Player_ToggleTelportAntiCheat(playerid, false);
        if(AccountData[playerid][pInRusun] != -1)
        {
            SetPlayerPositionEx(playerid, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2], RusunData[id][rusunExtPos][3], 6000);
            SetPlayerInteriorEx(playerid, RusunData[id][rusunInterior]);
            SetPlayerVirtualWorldEx(playerid, 0);
            AccountData[playerid][pInRusun] = -1;
        }
        else
        {
            SetPlayerPositionEx(playerid, RusunData[id][rusunExtPos][0], RusunData[id][rusunExtPos][1], RusunData[id][rusunExtPos][2], RusunData[id][rusunExtPos][3], 6000);
            SetPlayerInteriorEx(playerid, 0);
            SetPlayerVirtualWorldEx(playerid, 0);
            AccountData[playerid][pInRusun] = -1;
        }

        SetCameraBehindPlayer(playerid);
        SetPlayerWeather(playerid, WorldWeather);
        Player_ToggleTelportAntiCheat(playerid, true);
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/5;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

/* Storage system */
forward OnRusunDeposit(playerid);
public OnRusunDeposit(playerid)
{
    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyimpan item");
    RusunBrankas[playerid][rusunbrankasID] = 0;
    RusunBrankas[playerid][rusunbrankasTemp] = EOS;
    RusunBrankas[playerid][rusunbrankasModel] = 0;
    RusunBrankas[playerid][rusunbrankasQuant] = 0;
    return 1;
}

AddCapacityRusun(playerid, const item[], quantity)
{
    if(!strcmp(item, "Nasi Goreng"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Kopi Kenangan"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Batu Kotor"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.030;
    }
    else if(!strcmp(item, "Nasi Uduk"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Kanabis"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Batu Bersih"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.030;
    }
    else if(!strcmp(item, "Air Mineral"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Besi"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Tembaga"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Berlian"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.25;
    }
    else if(!strcmp(item, "Emas"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.10;
    }
    else if(!strcmp(item, "Gold"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.10;
    }
    else if(!strcmp(item, "Smartphone"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.25;
    }
    else if(!strcmp(item, "Radio"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.15;
    }
    else if(!strcmp(item, "Kayu"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.06;
    }
    else if(!strcmp(item, "Kayu Potongan"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Kayu Kemas"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.08;
    }
    else if(!strcmp(item, "Marijuana"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Benang"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Kain"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.04;
    }
    else if(!strcmp(item, "Pakaian"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.04;
    }
    else if(!strcmp(item, "Bandage"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Medkit"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Alprazolam"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Ayam Hidup"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.15;
    }
    else if(!strcmp(item, "Ayam Potong"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.10;
    }
    else if(!strcmp(item, "Ayam Kemas"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Sampah Makanan"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.005;
    }
    else if(!strcmp(item, "Kevlar"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.90;
    }
    else if(!strcmp(item, "Botol"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Petrol"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.50;
    }
    else if(!strcmp(item, "Pure Oil"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.50;
    }
    else if(!strcmp(item, "GAS"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.60;
    }
    else if(!strcmp(item, "Ikan"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Rokok"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Pancingan"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.08;
    }
    else if(!strcmp(item, "Umpan"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Hiu"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.90;
    }
    else if(!strcmp(item, "Penyu"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.80;
    }
    else if(!strcmp(item, "Ikan Tawar"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.03;
    }
    else if(!strcmp(item, "Jerigen"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.25;
    }
    else if(!strcmp(item, "Tools Kit"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.30;
    }
    else if(!strcmp(item, "Repair Kit"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.35;
    }
    else if(!strcmp(item, "Linggis"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Kunci T"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Nasi Pecel"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Bubur Pedas"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Es Teh"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Jus Apel"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Boombox"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.20;
    }
    else if(!strcmp(item, "Kebab A5"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Bakso"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Choco Matcha"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Teh Jeruk"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Susu Murni"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Susu Olahan"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Susu Fresh"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Cabe"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Padi"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Garam Kristal"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.006;
    }
    else if(!strcmp(item, "Tebu"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Beras"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.04;
    }
    else if(!strcmp(item, "Sambal"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Gula"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Garam"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Daging"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Daging Ikan Tawar"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Daging Ayam Goreng"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Daging Hiu"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.09;
    }
    else if(!strcmp(item, "Tanduk"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.03;
    }
    else if(!strcmp(item, "Kulit"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Bulu"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Boxmats"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.04;
    }
    else if(!strcmp(item, "Baja"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Material"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.025;
    }
    else if(!strcmp(item, "Kaca"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.015;
    }
    else if(!strcmp(item, "Karet"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.006;
    }
    else if(!strcmp(item, "Plastik"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.005;
    }
    else if(!strcmp(item, "Alumunium"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.010;
    }
    else if(!strcmp(item, "Backpack"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.50;
    }
    else if(!strcmp(item, "Masker"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.005;
    }
    else if(!strcmp(item, "Plat Besi"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.025;
    }
    else if(!strcmp(item, "Korek Api"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.010;
    }
    else if(!strcmp(item, "Bibit Padi"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.015;
    }
    else if(!strcmp(item, "Bibit Tebu"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.015;
    }
    else if(!strcmp(item, "Bibit Cabe"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.015;
    }
    else if(!strcmp(item, "Pilox"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.005;
    }
    else if(!strcmp(item, "Uranium ACD"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.020;
    }
    else if(!strcmp(item, "Uranium"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.010;
    }
    else if(!strcmp(item, "Senter"))
    {
        AccountData[playerid][pRusunCapacity] += quantity*0.006;
    }
    new sctr[596];
    mysql_format(g_SQL, sctr, sizeof(sctr), "UPDATE `player_characters` SET `Char_RusunStorage`=%f WHERE `pID`=%d", AccountData[playerid][pRusunCapacity], AccountData[playerid][pID]);
    mysql_tquery(g_SQL, sctr);
    return 1;
}

ReduceCapacityRusun(playerid, const item[], quantity)
{
    if(!strcmp(item, "Nasi Goreng"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Kopi Kenangan"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Batu Kotor"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.030;
    }
    else if(!strcmp(item, "Nasi Uduk"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Kanabis"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Batu Bersih"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.030;
    }
    else if(!strcmp(item, "Air Mineral"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Besi"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Tembaga"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Berlian"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.25;
    }
    else if(!strcmp(item, "Emas"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.10;
    }
    else if(!strcmp(item, "Gold"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.10;
    }
    else if(!strcmp(item, "Smartphone"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.25;
    }
    else if(!strcmp(item, "Radio"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.15;
    }
    else if(!strcmp(item, "Kayu"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.06;
    }
    else if(!strcmp(item, "Kayu Potongan"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Kayu Kemas"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.08;
    }
    else if(!strcmp(item, "Marijuana"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Benang"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Kain"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.04;
    }
    else if(!strcmp(item, "Pakaian"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.04;
    }
    else if(!strcmp(item, "Bandage"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Medkit"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Alprazolam"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Ayam Hidup"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.15;
    }
    else if(!strcmp(item, "Ayam Potong"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.10;
    }
    else if(!strcmp(item, "Ayam Kemas"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Sampah Makanan"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.005;
    }
    else if(!strcmp(item, "Kevlar"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.90;
    }
    else if(!strcmp(item, "Botol"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Petrol"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.50;
    }
    else if(!strcmp(item, "Pure Oil"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.50;
    }
    else if(!strcmp(item, "GAS"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.60;
    }
    else if(!strcmp(item, "Ikan"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Rokok"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Pancingan"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.08;
    }
    else if(!strcmp(item, "Umpan"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Hiu"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.90;
    }
    else if(!strcmp(item, "Penyu"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.80;
    }
    else if(!strcmp(item, "Ikan Tawar"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.03;
    }
    else if(!strcmp(item, "Jerigen"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.25;
    }
    else if(!strcmp(item, "Tools Kit"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.30;
    }
    else if(!strcmp(item, "Repair Kit"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.35;
    }
    else if(!strcmp(item, "Linggis"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Kunci T"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Nasi Pecel"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Bubur Pedas"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Es Teh"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Jus Apel"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Boombox"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.20;
    }
    else if(!strcmp(item, "Kebab A5"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Bakso"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Choco Matcha"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Teh Jeruk"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Susu Murni"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Susu Olahan"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Susu Fresh"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Cabe"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Padi"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Garam Kristal"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.006;
    }
    else if(!strcmp(item, "Tebu"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Beras"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.04;
    }
    else if(!strcmp(item, "Sambal"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Gula"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Garam"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Daging"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Daging Ikan Tawar"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Daging Ayam Goreng"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Daging Hiu"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.09;
    }
    else if(!strcmp(item, "Tanduk"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.03;
    }
    else if(!strcmp(item, "Kulit"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Bulu"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Boxmats"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.04;
    }
    else if(!strcmp(item, "Baja"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Material"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.025;
    }
    else if(!strcmp(item, "Kaca"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.015;
    }
    else if(!strcmp(item, "Karet"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.006;
    }
    else if(!strcmp(item, "Plastik"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.005;
    }
    else if(!strcmp(item, "Alumunium"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.010;
    }
    else if(!strcmp(item, "Backpack"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.50;
    }
    else if(!strcmp(item, "Masker"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.005;
    }
    else if(!strcmp(item, "Plat Besi"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.025;
    }
    else if(!strcmp(item, "Korek Api"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.010;
    }
    else if(!strcmp(item, "Bibit Padi"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.015;
    }
    else if(!strcmp(item, "Bibit Tebu"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.015;
    }
    else if(!strcmp(item, "Bibit Cabe"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.015;
    }
    else if(!strcmp(item, "Pilox"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.005;
    }
    else if(!strcmp(item, "Uranium ACD"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.020;
    }
    else if(!strcmp(item, "Uranium"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.010;
    }
    else if(!strcmp(item, "Senter"))
    {
        AccountData[playerid][pRusunCapacity] -= quantity*0.006;
    }
    if(AccountData[playerid][pRusunCapacity] < 0) {
        AccountData[playerid][pRusunCapacity] = 0;
    }
    new sctr[596];
    mysql_format(g_SQL, sctr, sizeof(sctr), "UPDATE `player_characters` SET `Char_RusunStorage`=%f WHERE `pID`=%d", AccountData[playerid][pRusunCapacity], AccountData[playerid][pID]);
    mysql_tquery(g_SQL, sctr);
    return 1;
}