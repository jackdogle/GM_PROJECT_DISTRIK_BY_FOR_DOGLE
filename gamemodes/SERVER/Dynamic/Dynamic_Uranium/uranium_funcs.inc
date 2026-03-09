#include <YSI\y_hooks>
#define MAX_DYNAMIC_URANIUM 150

new pTakeUraniumTimer[MAX_PLAYERS] = { -1, ... },
    pMixUraniumTimer[MAX_PLAYERS] = { -1, ...};

enum e_uraniumdata
{
    Float:UraniumPos[3],
    Float:UraniumRot[3],
    STREAMER_TAG_OBJECT: UraniumObject,
    STREAMER_TAG_AREA: UraniumArea,
    UraniumInt,
    UraniumWorld,
    bool:UraniumExists,
    UraniumTimer,
}
new UraniumData[MAX_DYNAMIC_URANIUM][e_uraniumdata],
    Iterator:Uranium<MAX_DYNAMIC_URANIUM>;

forward Load_Uranium();
public Load_Uranium()
{
    new id;
    if(cache_num_rows())
    {
        for(new x = 0; x < cache_num_rows(); x ++)
        {
            cache_get_value_name_int(x, "ID", id);
            cache_get_value_name_float(x, "UraniumX", UraniumData[id][UraniumPos][0]);
            cache_get_value_name_float(x, "UraniumY", UraniumData[id][UraniumPos][1]);
            cache_get_value_name_float(x, "UraniumZ", UraniumData[id][UraniumPos][2]);
            cache_get_value_name_float(x, "UraniumRX", UraniumData[id][UraniumRot][0]);
            cache_get_value_name_float(x, "UraniumRY", UraniumData[id][UraniumRot][1]);
            cache_get_value_name_float(x, "UraniumRZ", UraniumData[id][UraniumRot][2]);
            cache_get_value_name_int(x, "Interior", UraniumData[id][UraniumInt]);
            cache_get_value_name_int(x, "World", UraniumData[id][UraniumWorld]);
            cache_get_value_name_int(x, "Timer", UraniumData[id][UraniumTimer]);
            UraniumData[id][UraniumExists] = true;

            Uranium_Refresh(id);
            Iter_Add(Uranium, id);
        }
        printf("[Dynamic Uranium]: Jumlah total Uranium yang dimuat %d", cache_num_rows());
    }
}

Uranium_Save(id)
{
    new cQuery[522];
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `uranium` SET `UraniumX`='%f', `UraniumY`='%f', `UraniumZ`='%f', `UraniumRX`='%f', `UraniumRY`='%f', `UraniumRZ`='%f', `Interior`=%d, `World`=%d, `Timer`=%d WHERE `ID`=%d",
    UraniumData[id][UraniumPos][0],
    UraniumData[id][UraniumPos][1],
    UraniumData[id][UraniumPos][2],
    UraniumData[id][UraniumRot][0],
    UraniumData[id][UraniumRot][1],
    UraniumData[id][UraniumRot][2],
    UraniumData[id][UraniumInt],
    UraniumData[id][UraniumWorld],
    UraniumData[id][UraniumTimer],
    id);
    mysql_tquery(g_SQL, cQuery);
    return 1;
}

Uranium_Refresh(id)
{
    if(id != -1)
    {
        if(!UraniumData[id][UraniumTimer])
        {
            if(DestroyDynamicObject(UraniumData[id][UraniumObject]))
                UraniumData[id][UraniumObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
            
            if(DestroyDynamicArea(UraniumData[id][UraniumArea]))
                UraniumData[id][UraniumArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

            UraniumData[id][UraniumObject] = CreateDynamicObject(3632, UraniumData[id][UraniumPos][0], UraniumData[id][UraniumPos][1], UraniumData[id][UraniumPos][2], UraniumData[id][UraniumRot][0], UraniumData[id][UraniumRot][1], UraniumData[id][UraniumRot][2], UraniumData[id][UraniumWorld], UraniumData[id][UraniumInt], -1, 50.0, 50.0, -1);
            UraniumData[id][UraniumArea] = CreateDynamicSphere(UraniumData[id][UraniumPos][0], UraniumData[id][UraniumPos][1], UraniumData[id][UraniumPos][2], 2.0, UraniumData[id][UraniumWorld], UraniumData[id][UraniumInt], -1);
        }
    }
    return 1;
}

CMD:adduranium(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);
    
    new id = Iter_Free(Uranium);
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menambah Dynamic Uranium lagi ke server!");
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    UraniumData[id][UraniumExists] = true;
    UraniumData[id][UraniumPos][0] = x;
    UraniumData[id][UraniumPos][1] = y;
    UraniumData[id][UraniumPos][2] = z;
    UraniumData[id][UraniumRot][0] = 0.0;
    UraniumData[id][UraniumRot][1] = 0.0;
    UraniumData[id][UraniumRot][2] = 0.0;
    UraniumData[id][UraniumInt] = GetPlayerInterior(playerid);
    UraniumData[id][UraniumWorld] = GetPlayerVirtualWorld(playerid);
    UraniumData[id][UraniumTimer] = 0;

    Uranium_Refresh(id);
    Iter_Add(Uranium, id);

    new query[298];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `uranium` (`ID`, `UraniumX`, `UraniumY`, `UraniumZ`, `UraniumRX`, `UraniumRY`, `UraniumRZ`, `Interior`, `World`, `Timer`) VALUES ('%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d')",
    id, UraniumData[id][UraniumPos][0], UraniumData[id][UraniumPos][1], UraniumData[id][UraniumPos][2], UraniumData[id][UraniumRot][0], UraniumData[id][UraniumRot][1], UraniumData[id][UraniumRot][2], UraniumData[id][UraniumInt], UraniumData[id][UraniumWorld], UraniumData[id][UraniumTimer]);
    mysql_tquery(g_SQL, query, "OnUraniumCreated", "ii", playerid, id);
    return 1;
}

CMD:gotouraniummixer(playerid, params[])
{
	if(CheckAdmin(playerid, 2)) return PermissionError(playerid);
	
	SetPlayerPositionEx(playerid, -953.216, -494.536, 25.960, 0.0, 1500);
	SetPlayerVirtualWorldEx(playerid, 0);
	SetPlayerInteriorEx(playerid, 0);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Teleportasi ke Uranium Mixer", GetAdminName(playerid));
	AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
	return 1;
}

CMD:edituranium(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);
    
    new id, option[24], nextparams[128];
    if(sscanf(params, "ds[24]S()[128]", id, option, nextparams)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/edituranium [id] [entinity] (delete, pos)");
    if((id < 0 || id >= MAX_DYNAMIC_URANIUM)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Uranium tidak valid!");
    if(!Iter_Contains(Uranium, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Uranium tidak ada!");

    if(!strcmp(option, "delete", true))
    {
        if(DestroyDynamicObject(UraniumData[id][UraniumObject]))
            UraniumData[id][UraniumObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        if(DestroyDynamicArea(UraniumData[id][UraniumArea]))
            UraniumData[id][UraniumArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        
        UraniumData[id][UraniumExists] = false;
        UraniumData[id][UraniumTimer] = 0;
        for(new i = 0; i < 3; i ++) {
            UraniumData[id][UraniumPos][i] = 0.0;
            UraniumData[id][UraniumRot][i] = 0.0;
        }

        Iter_Remove(Uranium, id);
        mysql_tquery(g_SQL, sprintf("DELETE FROM `uranium` WHERE `ID`=%d", id));
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menghapus Dynamic Uranium ID %d", AccountData[playerid][pAdminname], id);
    }
    else if(!strcmp(option, "pos", true))
    {
        if(!IsPlayerInRangeOfPoint(playerid, 20.0, UraniumData[id][UraniumPos][0], UraniumData[id][UraniumPos][1], UraniumData[id][UraniumPos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada didekat uranium yang ingin anda edit!");
        if(Uranium_BeingEdited(id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Dynamic Object tersebut sedang di edit posisinya!");

        AccountData[playerid][EditingUraniumID] = id;
        EditDynamicObject(playerid, UraniumData[id][UraniumObject]);
    }
    else ShowTDN(playerid, NOTIFICATION_SYNTAX, "/edituranium [id] [entinity] (delete, pos)");
    return 1;
}

Uranium_BeingEdited(id)
{
    if(!Iter_Contains(Uranium, id)) return 0;
    foreach(new i : Player) if (AccountData[i][EditingUraniumID] == id) return 1;
    return 0;
}

PlayerNearUranium(playerid)
{
    foreach(new i : Uranium) if (UraniumData[i][UraniumPos][0] != 0.0)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, UraniumData[i][UraniumPos][0], UraniumData[i][UraniumPos][1], UraniumData[i][UraniumPos][2]))
        {
            return i;
        }
    }
    return -1;
}

FUNC::OnUraniumCreated(playerid, id)
{
    Uranium_Save(id);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" membuat Dynamic Uranium ID %d", AccountData[playerid][pAdminname], id);
    return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    if(AccountData[playerid][EditingUraniumID] != -1 && Iter_Contains(Uranium, AccountData[playerid][EditingUraniumID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new etid = AccountData[playerid][EditingUraniumID];
	        UraniumData[etid][UraniumPos][0] = x;
	        UraniumData[etid][UraniumPos][1] = y;
	        UraniumData[etid][UraniumPos][2] = z;
	        UraniumData[etid][UraniumRot][0] = rx;
	        UraniumData[etid][UraniumRot][1] = ry;
	        UraniumData[etid][UraniumRot][2] = rz;

	        SetDynamicObjectPos(objectid, UraniumData[etid][UraniumPos][0], UraniumData[etid][UraniumPos][1], UraniumData[etid][UraniumPos][2]);
	        SetDynamicObjectRot(objectid, UraniumData[etid][UraniumRot][0], UraniumData[etid][UraniumRot][1], UraniumData[etid][UraniumRot][2]);

            Uranium_Refresh(etid);
		    Uranium_Save(etid);
	        AccountData[playerid][EditingUraniumID] = -1;
	    }

	    if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new etid = AccountData[playerid][EditingUraniumID];
	        SetDynamicObjectPos(objectid, UraniumData[etid][UraniumPos][0], UraniumData[etid][UraniumPos][1], UraniumData[etid][UraniumPos][2]);
	        SetDynamicObjectRot(objectid, UraniumData[etid][UraniumRot][0], UraniumData[etid][UraniumRot][1], UraniumData[etid][UraniumRot][2]);
	        
            Uranium_Refresh(etid);
            AccountData[playerid][EditingUraniumID] = -1;
	    }
	}
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    for(new i = 0; i < MAX_DYNAMIC_URANIUM; i ++) if (UraniumData[i][UraniumPos][0] != 0.0)
    {
        if(areaid == UraniumData[i][UraniumArea] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            ShowKey(playerid, "[Y] - Take Uranium");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    for(new i = 0; i < MAX_DYNAMIC_URANIUM; i ++) if (UraniumData[i][UraniumPos][0] != 0.0)
    {
        if(areaid == UraniumData[i][UraniumArea])
        {
            HideShortKey(playerid);
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new id = PlayerNearUranium(playerid);
        if(id > -1 && UraniumData[id][UraniumArea] != STREAMER_TAG_AREA: INVALID_STREAMER_ID)
        {
            new count, count2;
            foreach(new i : Player) if (IsPlayerConnected(i) && AccountData[i][pSpawned])
            {
                if(AccountData[i][pDutyPD]) count ++;
                if(AccountData[i][pDutyEms]) count2 ++;
            }
            if(count < 4 && count2 < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 Polisi dan 2 EMS!");
           
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
            if(!UraniumData[id][UraniumExists]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uranium tersebut sudah diambil orang lain!");

            AccountData[playerid][ActivityTime] = 1;
            UraniumData[id][UraniumExists] = false;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL URANIUM");
            ShowProgressBar(playerid);

            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            pTakeUraniumTimer[playerid] = SetTimerEx("TakeUranium", 1000, true, "dd", playerid, id);
        }

        if(IsPlayerInRangeOfPoint(playerid, 2.0, -953.216, -494.536, 25.960))
        {
            if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya Anggota Family yang dapat mengambil Uranium!");
            if(AccountData[playerid][pLevel] < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus memiliki level 15 untuk mengambil Uranium!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");

            Dialog_Show(playerid, MixerUraniumConf, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Make Uranium",
            "Apakah anda yakin ingin membuat Uranium dengan bahan sebagai berikut?\n\n"ORANGE"Uranium ACD (%d/5)\nGaram (%d/15)\nBotol (%d/1)\nAir Mineral (%d/5)", "Iya", "Tidak",
            Inventory_Count(playerid, "Uranium ACD"), Inventory_Count(playerid, "Garam"), Inventory_Count(playerid, "Botol"), Inventory_Count(playerid, "Air Mineral"));
        }
        /*if(IsPlayerInRangeOfPoint(playerid, 2.0, -953.216, -494.536, 25.960))
        {
            if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya Anggota Family yang dapat mengambil Uranium!");
            if(AccountData[playerid][pLevel] < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus memiliki level 15 untuk mengambil Uranium!");
            if(!PlayerHasItem(playerid, "Uranium ACD")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Uranium ACD!");
            if(!PlayerHasItem(playerid, "GAS")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki GAS!");
            if(!PlayerHasItem(playerid, "Botol")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Botol!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
            
            AccountData[playerid][ActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH URANIUM");
            ShowProgressBar(playerid);

            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            pMixUraniumTimer[playerid] = SetTimerEx("MixUranium", 1000, true, "d", playerid);
        }*/
    }
    return 1;
}

Dialog:MixerUraniumConf(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya Anggota Family yang dapat mengambil Uranium!");
    if(AccountData[playerid][pLevel] < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus memiliki level 15 untuk mengambil Uranium!");
    if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");

    AccountData[playerid][ActivityTime] = 1;
    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH URANIUM");
    ShowProgressBar(playerid);

    ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
    pMixUraniumTimer[playerid] = SetTimerEx("MixUranium", 1000, true, "d", playerid);
    return 1;
}

forward MixUranium(playerid);
public MixUranium(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pMixUraniumTimer[playerid]);
        pMixUraniumTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInRangeOfPoint(playerid, 2.0, -953.216, -494.536, 25.960))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di area olah!");
        KillTimer(pMixUraniumTimer[playerid]);
        pMixUraniumTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Uranium ACD") < 5)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Uranium ACD tidak cukup, minimal 5!");
        KillTimer(pMixUraniumTimer[playerid]);
        pMixUraniumTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Garam") < 15)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Garam tidak cukup, minimal 15!");
        KillTimer(pMixUraniumTimer[playerid]);
        pMixUraniumTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Air Mineral") < 5)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Air Mineral tidak cukup, minimal 5!");
        KillTimer(pMixUraniumTimer[playerid]);
        pMixUraniumTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Botol") < 1)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Botol tidak cukup, minimal 1!");
        KillTimer(pMixUraniumTimer[playerid]);
        pMixUraniumTimer[playerid] = -1;
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
        KillTimer(pMixUraniumTimer[playerid]);
        pMixUraniumTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
        KillTimer(pMixUraniumTimer[playerid]);
        pMixUraniumTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pMixUraniumTimer[playerid]);
        pMixUraniumTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        Inventory_Remove(playerid, "Uranium ACD", 5);
        Inventory_Remove(playerid, "Garam", 15);
        Inventory_Remove(playerid, "Air Mineral", 5);
        Inventory_Remove(playerid, "Botol");
        Inventory_Add(playerid, "Uranium", 2958);
        ShowItemBox(playerid, "Received 1x", "Uranium", 2958);

        GivePlayerXP(playerid, 1);
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

		static Float:progressvalue;
		progressvalue = AccountData[playerid][ActivityTime] * 103/15;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		return 0;
    }
    return 1;
}

forward TakeUranium(playerid, id);
public TakeUranium(playerid, id)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeUraniumTimer[playerid]);
        pTakeUraniumTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(UraniumData[id][UraniumArea]))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak di area uranium!");
        KillTimer(pTakeUraniumTimer[playerid]);
        pTakeUraniumTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        UraniumData[id][UraniumExists] = true;
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, UraniumData[id][UraniumArea]))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak di dekat uranium!");
        KillTimer(pTakeUraniumTimer[playerid]);
        pTakeUraniumTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        UraniumData[id][UraniumExists] = true;
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pTakeUraniumTimer[playerid]);
        pTakeUraniumTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        UraniumData[id][UraniumExists] = true;
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(GetTotalWeightFloat(playerid) > 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
        KillTimer(pTakeUraniumTimer[playerid]);
        pTakeUraniumTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        UraniumData[id][UraniumExists] = true;
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pTakeUraniumTimer[playerid]);
        pTakeUraniumTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        if(DestroyDynamicObject(UraniumData[id][UraniumObject])) UraniumData[id][UraniumObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        if(DestroyDynamicArea(UraniumData[id][UraniumArea])) UraniumData[id][UraniumArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        
        Inventory_Add(playerid, "Uranium ACD", 3046);
        ShowItemBox(playerid, "Received 1x", "Uranium ACD", 3046);

        UraniumData[id][UraniumTimer] = 120;
        Uranium_Save(id);
        GivePlayerXP(playerid, 1);
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

		static Float:progressvalue;
		progressvalue = AccountData[playerid][ActivityTime] * 103/15;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		return 0;
    }
    return 1;
}

task UraniumUpdate[1000]()
{
    foreach(new i:Uranium) if (UraniumData[i][UraniumPos][0] != 0.0)
    {
        if(--UraniumData[i][UraniumTimer] > 0)
        {
            if(!UraniumData[i][UraniumTimer])
            {
                UraniumData[i][UraniumTimer] = 0;
                UraniumData[i][UraniumExists] = true;
                Uranium_Refresh(i);
                Uranium_Save(i);
            }
        }
        
    }
    return 1;
}

hook OnGameModeInitEx()
{
    CreateDynamic3DTextLabel(""LIGHTGREY"[Uranium Lab]\n"YELLOW"[Y]"WHITE" To Make Uranium", -1, -953.216, -494.536, 25.960, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 10.0, -1, 0);
}

hook OnPlayerConnect(playerid)
{
	pTakeUraniumTimer[playerid] = -1;
    pMixUraniumTimer[playerid] = -1;
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	KillTimer(pTakeUraniumTimer[playerid]);
    KillTimer(pMixUraniumTimer[playerid]);
	pTakeUraniumTimer[playerid] = -1;
    pMixUraniumTimer[playerid] = -1;
	return 1;
}