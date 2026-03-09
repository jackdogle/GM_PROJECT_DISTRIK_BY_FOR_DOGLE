// All Callbacks
JavaTR:Rusuns_Load()
{
    new rows = cache_num_rows();

    for (new i = 0; i < rows; i ++)
    {
        Iter_Add(RusunDatas, i);
        cache_get_value_name_int(i, "ID", RusunsData[i][rID]);
        cache_get_value_name_int(i, "Owner", RusunsData[i][rOwnerID]);
        cache_get_value_name(i, "OwnerName", RusunsData[i][rOwner], MAX_PLAYER_NAME);
        cache_get_value_name(i, "RusunName", RusunsData[i][rName], 128);
        cache_get_value_name_int(i, "Price", RusunsData[i][rPrice]);
        cache_get_value_name_int(i, "Vw", RusunsData[i][rVW]);
        cache_get_value_name_int(i, "Int", RusunsData[i][rInterior]);
        cache_get_value_name_int(i, "InteriorInt", RusunsData[i][rInteriorInt]);
        
        cache_get_value_name_float(i, "Pos0", RusunsData[i][rExtPos][0]);
        cache_get_value_name_float(i, "Pos1", RusunsData[i][rExtPos][1]);
        cache_get_value_name_float(i, "Pos2", RusunsData[i][rExtPos][2]);
        cache_get_value_name_float(i, "Pos3", RusunsData[i][rExtPos][3]);
        cache_get_value_name_float(i, "PosInt0", RusunsData[i][rIntPos][0]);
        cache_get_value_name_float(i, "PosInt1", RusunsData[i][rIntPos][1]);
        cache_get_value_name_float(i, "PosInt2", RusunsData[i][rIntPos][2]);
        cache_get_value_name_float(i, "PosInt3", RusunsData[i][rIntPos][3]);
        RusunRefresh(i);
    }

    printf("[Dynamic Rusun]: Jumlah total Rusun yang dimuat %d", rows);
    return 1;
}

JavaTR: OnRusunsDataCreated(id) {
    if (!Iter_Contains(RusunDatas, id))
        return 0;
    
    RusunsData[id][rID] = cache_insert_id();
    RusunSave(id);
    return 1;
}

RusunRefresh(id)
{
    if (!Iter_Contains(RusunDatas, id))
        return 0;
    
    if (IsValidDynamicPickup(RusunsData[id][rPickup]))
        DestroyDynamicPickup(RusunsData[id][rPickup]);
    
    if (IsValidDynamic3DTextLabel(RusunsData[id][rLabel]))
        DestroyDynamic3DTextLabel(RusunsData[id][rLabel]);
        
    if (IsValidDynamic3DTextLabel(RusunsData[id][rIntLabel]))
        DestroyDynamic3DTextLabel(RusunsData[id][rIntLabel]);

    if (RusunsData[id][rOwnerID] > 0)
    {
        RusunsData[id][rPickup] = CreateDynamicPickup(19524, 23, RusunsData[id][rExtPos][0], RusunsData[id][rExtPos][1], RusunsData[id][rExtPos][2], RusunsData[id][rVW], RusunsData[id][rInterior], -1, 2.0);
        RusunsData[id][rLabel] = CreateDynamic3DTextLabel("[Tekan "GREEN"Y"WHITE" untuk membuka menu]", -1, RusunsData[id][rExtPos][0], RusunsData[id][rExtPos][1], RusunsData[id][rExtPos][2] + 0.35, 2.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, RusunsData[id][rVW], RusunsData[id][rInterior], -1, 2.0, -1, 0);
    }
    else
    {
        RusunsData[id][rPickup] = CreateDynamicPickup(19524, 23, RusunsData[id][rExtPos][0], RusunsData[id][rExtPos][1], RusunsData[id][rExtPos][2], RusunsData[id][rVW], RusunsData[id][rInterior], -1, 2.0);
        RusunsData[id][rLabel] = CreateDynamic3DTextLabel("[Tekan "GREEN"Y"WHITE" untuk membuka menu]", -1, RusunsData[id][rExtPos][0], RusunsData[id][rExtPos][1], RusunsData[id][rExtPos][2] + 0.35, 2.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, RusunsData[id][rVW], RusunsData[id][rInterior], -1, 2.0, -1, 0);
    }
    RusunsData[id][rIntLabel] = CreateDynamic3DTextLabel(""RED"[Y]"WHITE" Keluar", -1, RusunsData[id][rIntPos][0], RusunsData[id][rIntPos][1], RusunsData[id][rIntPos][2] + 0.35, 2.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
    return 1;
}

RusunSave(id)
{
    new query[2024];

    format(query, sizeof(query), "UPDATE `rusuns` SET `Owner` = '%d', `OwnerName` = '%s', `RusunName` = '%s', `Price` = '%d', `Vw` = '%d', `Int` = '%d', `InteriorInt` = '%d', `Pos0` = '%f', `Pos1` = '%f', `Pos2` = '%f', `Pos3` = '%f', `PosInt0` = '%f', `PosInt1` = '%f', `PosInt2` = '%f', `PosInt3` = '%f' WHERE `ID` = '%d'",
    RusunsData[id][rOwnerID],
    RusunsData[id][rOwner],
    RusunsData[id][rName],
    RusunsData[id][rPrice],
    RusunsData[id][rVW],
    RusunsData[id][rInterior],
    RusunsData[id][rInteriorInt],
    RusunsData[id][rExtPos][0],
    RusunsData[id][rExtPos][1],
    RusunsData[id][rExtPos][2],
    RusunsData[id][rExtPos][3],
    RusunsData[id][rIntPos][0],
    RusunsData[id][rIntPos][1],
    RusunsData[id][rIntPos][2],
    RusunsData[id][rIntPos][3],
    RusunsData[id][rID]
    );
    return mysql_tquery(g_SQL, query);
}

Rusun_Create(playerid, price, name[])
{
    new id = -1;

    if ((id = Iter_Free(RusunDatas)) != -1) {
        new Float:POS[4];
        GetPlayerPos(playerid, POS[0], POS[1], POS[2]);
        GetPlayerFacingAngle(playerid, POS[3]);

        RusunsData[id][rOwnerID] = 0;
        format(RusunsData[id][rOwner], MAX_PLAYER_NAME, "-");
        format(RusunsData[id][rName], 128, name);
        RusunsData[id][rPrice] = price;
        RusunsData[id][rVW] = GetPlayerVirtualWorld(playerid);
        RusunsData[id][rInterior] = GetPlayerInterior(playerid);
        RusunsData[id][rInteriorInt] = 5;
        
        RusunsData[id][rExtPos][0] = POS[0];
        RusunsData[id][rExtPos][1] = POS[1];
        RusunsData[id][rExtPos][2] = POS[2];
        RusunsData[id][rExtPos][3] = POS[3];

        RusunsData[id][rIntPos][0] = 2233.7258;
        RusunsData[id][rIntPos][1] = -1115.1895;
        RusunsData[id][rIntPos][2] = 1050.8828;
        RusunsData[id][rIntPos][3] = 0.1506;
        
        Iter_Add(RusunDatas, id);
        RusunRefresh(id);
        
        new cQuery[512];
        format(cQuery, sizeof(cQuery), "INSERT INTO `rusuns` (`Price`) VALUES ('%d')", RusunsData[id][rPrice]);
        mysql_tquery(g_SQL, cQuery, "OnRusunsDataCreated", "d", id);
        
        return id;
    }
    return -1;
}

Rusun_Delete(id) {
    if (Iter_Contains(RusunDatas, id)) {
        Iter_Remove(RusunDatas, id);
        mysql_tquery(g_SQL, sprintf("DELETE FROM `rusuns` WHERE `ID` = '%d'", RusunsData[id][rID]));

        DestroyDynamicPickup(RusunsData[id][rPickup]);
        DestroyDynamic3DTextLabel(RusunsData[id][rLabel]);
        DestroyDynamic3DTextLabel(RusunsData[id][rIntLabel]);

        RusunsData[id][rID] = -1;
        RusunsData[id][rPickup] = INVALID_STREAMER_ID;
        RusunsData[id][rLabel] = RusunsData[id][rIntLabel] = Text3D: INVALID_STREAMER_ID;
        return 1;
    }
    return 0;
}

JavaTR: OnRusunDepo(playerid)
{
    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyimpan item");
    RusunBrankas[playerid][rusunbrankasID] = 0;
    RusunBrankas[playerid][rusunbrankasTemp] = EOS;
    RusunBrankas[playerid][rusunbrankasModel] = 0;
    RusunBrankas[playerid][rusunbrankasQuant] = 0;
    return 1;
}

RusunInside(playerid) 
{
    if(AccountData[playerid][pInRusun] != -1)
    {
        for (new i = 0; i != MAX_RUSUN_ROOM; i ++) if(Iter_Contains(RusunDatas, i) && RusunsData[i][rID] == AccountData[playerid][pInRusun] && GetPlayerInterior(playerid) == RusunsData[i][rInteriorInt] && GetPlayerVirtualWorld(playerid) > 0) {
            return i;
        }
    }
    return -1;
}

Rusun_NearestInt(playerid) 
{
    for (new i = 0; i != MAX_RUSUN_ROOM; i ++) 
    {
        if (Iter_Contains(RusunDatas, i) && IsPlayerInRangeOfPoint(playerid, 2.5, RusunsData[i][rPosInt][0], RusunsData[i][rPosInt][1], RusunsData[i][rPosInt][2]) && (GetPlayerVirtualWorld(playerid) == AccountData[playerid][pInRusun] && GetPlayerInterior(playerid) == RusunsData[i][rInteriorInt]))
        {
            return i;
        }
    }
    return -1;
}

Rusun_Nearest(playerid) {
    for (new i = 0; i != MAX_RUSUN_ROOM; i ++) if (Iter_Contains(RusunDatas, i) && IsPlayerInRangeOfPoint(playerid, 2.5, RusunsData[i][rExtPos][0], RusunsData[i][rExtPos][1], RusunsData[i][rExtPos][2]) && (GetPlayerInterior(playerid) == RusunsData[i][rInterior])) {
        return i;
    }
    return -1;
}

Rusun_IsOwner(playerid, id)
{
    if(!AccountData[playerid][IsLoggedIn] || AccountData[playerid][pID] == -1)
        return 0;

    if((Iter_Contains(RusunDatas, id) && RusunsData[id][rOwnerID] != 0) && RusunsData[id][rOwnerID] == AccountData[playerid][pID])
        return 1;

    return 0;
}

Rusun_GetCount(playerid)
{
    new count = 0;
    for (new i = 0; i != MAX_RUSUN_ROOM; i ++) if(Iter_Contains(RusunDatas, i) && Rusun_IsOwner(playerid, i)) {
        count++;
    }
    return count;
}

RemainingRusunTimes(playerid)
{
    new currentTime = g_RusunTime - gettime();
    new days = currentTime / 86400;
    new hours = (currentTime % 86400) / 3600;
    new minutes = (currentTime % 3600) / 60;
    new seconds = currentTime % 60;

    new shstr[258];
    format(shstr, sizeof(shstr), "Anda memiliki durasi sewa rusun ini selama\
    \n"WHITE"%d hari %d jam %d menit %d detik", days, hours, minutes, seconds);
    
    static rsid = -1;
    if((rsid = Rusun_Nearest(playerid)) != -1)
    {
        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, sprintf(""TCRP"District  "WHITE"- %s", RusunsData[rsid][rName]),
        shstr, "Tutup", "");
    }
    return 1;
}

JavaTR: EnterToRusun(playerid, id)
{
    if (!Iter_Contains(RusunDatas, id))
        return 0;
    
    if (!IsPlayerConnected(playerid))
    {
        KillTimer(EnterRusunTimer[playerid]);
        EnterRusunTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if (!IsPlayerInRangeOfPoint(playerid, 1.5, RusunsData[id][rExtPos][0], RusunsData[id][rExtPos][1], RusunsData[id][rExtPos][2]))
    {
        KillTimer(EnterRusunTimer[playerid]);
        EnterRusunTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if (AccountData[playerid][pInjured])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(EnterRusunTimer[playerid]);
        EnterRusunTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if (AccountData[playerid][ActivityTime] >= 5)
    {
        KillTimer(EnterRusunTimer[playerid]);
        EnterRusunTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        
        Player_ToggleTelportAntiCheat(playerid, false);
        SetPlayerPositionEx(playerid, RusunsData[id][rIntPos][0], RusunsData[id][rIntPos][1], RusunsData[id][rIntPos][2], RusunsData[id][rIntPos][3], 6000);
        SetPlayerInterior(playerid, RusunsData[id][rInteriorInt]);
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

forward OutFromRusun(playerid, id);
public OutFromRusun(playerid, id)
{
    if (!Iter_Contains(RusunDatas, id))
        return 0;
    
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(EnterRusunTimer[playerid]);
        EnterRusunTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInRangeOfPoint(playerid, 1.5, RusunsData[id][rIntPos][0], RusunsData[id][rIntPos][1], RusunsData[id][rIntPos][2]))
    {
        KillTimer(EnterRusunTimer[playerid]);
        EnterRusunTimer[playerid] = -1;
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
        KillTimer(EnterRusunTimer[playerid]);
        EnterRusunTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 5)
    {
        KillTimer(EnterRusunTimer[playerid]);
        EnterRusunTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Player_ToggleTelportAntiCheat(playerid, false);
        SetPlayerPositionEx(playerid, RusunsData[id][rExtPos][0], RusunsData[id][rExtPos][1], RusunsData[id][rExtPos][2], RusunsData[id][rExtPos][3], 6000);
        SetPlayerInteriorEx(playerid, 0);
        SetPlayerVirtualWorldEx(playerid, 0);
        AccountData[playerid][pInRusun] = -1;

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