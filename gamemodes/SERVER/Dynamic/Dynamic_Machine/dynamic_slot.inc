#include <YSI\y_hooks>
#define MAX_DYNAMIC_SLOT    100

enum e_slotdata
{
    Float:SlotPos[3],
    Float:SlotRotPos[3],
    SlotInterior,
    SlotWorld,
    STREAMER_TAG_OBJECT: SlotObjectID,
    STREAMER_TAG_3D_TEXT_LABEL: SlotLabel
};
new SlotData[MAX_DYNAMIC_SLOT][e_slotdata],
    Iterator:Slot<MAX_DYNAMIC_SLOT>;

new Float:SlotPosition[MAX_PLAYERS][3],    
    Float:SlotRPosition[MAX_PLAYERS][3];

SlotNearest(playerid, Float:range)
{
    foreach(new id : Slot) if(IsPlayerInRangeOfPoint(playerid, range, SlotData[id][SlotPos][0], SlotData[id][SlotPos][1], SlotData[id][SlotPos][2]) && GetPlayerInterior(playerid) == SlotData[id][SlotInterior] && GetPlayerVirtualWorld(playerid) == SlotData[id][SlotWorld])
    {
        return id;
    }
    return -1;
}

Slot_Refresh(id)
{
    if(id != -1)
    {
        if(DestroyDynamicObject(SlotData[id][SlotObjectID]))
            SlotData[id][SlotObjectID] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        if(DestroyDynamic3DTextLabel(SlotData[id][SlotLabel]))
            SlotData[id][SlotLabel] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID;
        
        if(SlotData[id][SlotPos][0] != 0.0)
        {
            SlotData[id][SlotObjectID] = CreateDynamicObject(1835, SlotData[id][SlotPos][0], SlotData[id][SlotPos][1], SlotData[id][SlotPos][2], SlotData[id][SlotRotPos][0], SlotData[id][SlotRotPos][1], SlotData[id][SlotRotPos][2], SlotData[id][SlotWorld], SlotData[id][SlotInterior], -1);
            SlotData[id][SlotLabel] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Using Slot Machine", -1, SlotData[id][SlotPos][0], SlotData[id][SlotPos][1], SlotData[id][SlotPos][2] + 0.55, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, SlotData[id][SlotWorld], SlotData[id][SlotInterior], -1, 10.0, -1, 0);
        }
    }
    return 1;
}

Slot_Save(id)
{
    new query[596];
    mysql_format(g_SQL, query, sizeof(query), "UPDATE `slotmachine` SET `PosX`=%f, `PosY`=%f, `PosZ`=%f, `RotX`=%f, `RotY`=%f, `RotZ`=%f, `Interior`=%d, `World`=%d WHERE `ID`=%d",
    SlotData[id][SlotPos][0], SlotData[id][SlotPos][1], SlotData[id][SlotPos][2], SlotData[id][SlotRotPos][0], SlotData[id][SlotRotPos][1], SlotData[id][SlotRotPos][2], SlotData[id][SlotInterior], SlotData[id][SlotWorld], id);
    mysql_tquery(g_SQL, query);
    return 1;
}

forward LoadSlotMachine();
public LoadSlotMachine()
{
    new id;
    if(cache_num_rows())
    {
        for(new x; x < cache_num_rows(); x++)
        {
            cache_get_value_name_int(x, "ID", id);
            cache_get_value_name_int(x, "Interior", SlotData[id][SlotInterior]);
            cache_get_value_name_int(x, "World", SlotData[id][SlotWorld]);

            cache_get_value_name_float(x, "PosX", SlotData[id][SlotPos][0]);
            cache_get_value_name_float(x, "PosY", SlotData[id][SlotPos][1]);
            cache_get_value_name_float(x, "PosZ", SlotData[id][SlotPos][2]);
            cache_get_value_name_float(x, "RotX", SlotData[id][SlotRotPos][0]);
            cache_get_value_name_float(x, "RotY", SlotData[id][SlotRotPos][1]);
            cache_get_value_name_float(x, "RotZ", SlotData[id][SlotRotPos][2]);

            Iter_Add(Slot, id);
            
            Slot_Refresh(id);
        }
        printf("[Dynamic Slot]: Total Dynamic Slot yang dimuat %d", cache_num_rows());
    }
}

CMD:addslot(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    new id = Iter_Free(Slot);
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menambahkan Slot Machine lagi!");

    GetPlayerPos(playerid, SlotData[id][SlotPos][0], SlotData[id][SlotPos][1], SlotData[id][SlotPos][2]);
    SlotData[id][SlotRotPos][0] = 0.0;
    SlotData[id][SlotRotPos][1] = 0.0;
    SlotData[id][SlotRotPos][2] = 0.0;
    SlotData[id][SlotInterior] = GetPlayerInterior(playerid);
    SlotData[id][SlotWorld] = GetPlayerVirtualWorld(playerid);
    
    Iter_Add(Slot, id);
    Info(playerid, "Anda membuat Dynamic Slot ID %d", id);

    new query[255];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `slotmachine` SET `ID`=%d, `PosX`=%f, `PosY`=%f, `PosZ`=%f, `RotX`=%f, `RotY`=%f, `RotZ`=%f, `Interior`=%d, `World`=%d",
    id, SlotData[id][SlotPos][0], SlotData[id][SlotPos][1], SlotData[id][SlotPos][2], SlotData[id][SlotRotPos][0], SlotData[id][SlotRotPos][1], SlotData[id][SlotRotPos][2], SlotData[id][SlotInterior], SlotData[id][SlotWorld]);
    mysql_tquery(g_SQL, query, "OnSlotCreated", "dd", playerid, id);
    return 1;
}

CMD:editslot(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    new id;
    if(id < 0 || id >= MAX_DYNAMIC_SLOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Slot tidak valid!");
    if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editslot [id]");
    if(!Iter_Contains(Slot, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Slot tidak ada!");

    AccountData[playerid][pEditSlotID] = id;
    GetDynamicObjectPos(SlotData[id][SlotObjectID], SlotPosition[playerid][0], SlotPosition[playerid][1], SlotPosition[playerid][2]);
    GetDynamicObjectRot(SlotData[id][SlotObjectID], SlotRPosition[playerid][0], SlotRPosition[playerid][1], SlotRPosition[playerid][2]);
    EditDynamicObject(playerid, SlotData[id][SlotObjectID]);
    return 1;
}

CMD:gotoslot(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 1) return PermissionError(playerid);

	new id;
	if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotoslot [id]");
	if(!Iter_Contains(Slot, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Slot tidak ada!");
	if(id < 0 || id > MAX_DYNAMIC_SLOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Slot tidak valid!");

	SetPlayerPositionEx(playerid, SlotData[id][SlotPos][0], SlotData[id][SlotPos][1], SlotData[id][SlotPos][2], 0.0, 500);
	SetPlayerInterior(playerid, SlotData[id][SlotInterior]);
	SetPlayerVirtualWorld(playerid, SlotData[id][SlotWorld]);
	AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Teleportasi ke Slot ID:%d", GetAdminName(playerid), id);
    return 1;
}

CMD:removeslot(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    new id;
    if(id < 0 || id >= MAX_DYNAMIC_SLOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Slot tidak valid!");
    if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editslot [id]");
    if(!Iter_Contains(Slot, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Slot tidak ada!");

    SlotData[id][SlotPos][0] = SlotData[id][SlotPos][1] = SlotData[id][SlotPos][2] = 0;
    SlotData[id][SlotRotPos][0] = SlotData[id][SlotRotPos][1] = SlotData[id][SlotRotPos][2] = 0;
    Slot_Refresh(id);
    Iter_Remove(Slot, id);

    Info(playerid, "Anda menghapus Dynamic Slot ID: %d", id);

    new query[200];
    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `slotmachine` WHERE `ID`=%d", id);
    mysql_tquery(g_SQL, query);
    return 1;
}

FUNC::OnSlotCreated(playerid, id)
{
    Slot_Refresh(id);
    Slot_Save(id);
    return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    if(AccountData[playerid][pEditSlotID] != -1 && Iter_Contains(Slot, AccountData[playerid][pEditSlotID]))
    {
        new id = AccountData[playerid][pEditSlotID];
        if(response == EDIT_RESPONSE_UPDATE)
        {
            SetDynamicObjectPos(objectid, x, y, z);
            SetDynamicObjectRot(objectid, rx, ry, rz);
        }
        else if(response == EDIT_RESPONSE_CANCEL)
        {
            SetDynamicObjectPos(objectid, SlotPosition[playerid][0], SlotPosition[playerid][1], SlotPosition[playerid][2]);
            SetDynamicObjectRot(objectid, SlotRPosition[playerid][0], SlotRPosition[playerid][1], SlotRPosition[playerid][2]);
            SlotPosition[playerid][0] = SlotPosition[playerid][1] = SlotPosition[playerid][2] = 0.0;
            SlotRPosition[playerid][0] = SlotRPosition[playerid][1] = SlotRPosition[playerid][2] = 0.0;
            Info(playerid, "Anda membatalkan pengeditan Slot ID %d", id);
            Slot_Save(id);
        }
        else if(response == EDIT_RESPONSE_FINAL)
        {
            SetDynamicObjectPos(objectid, x, y, z);
            SetDynamicObjectRot(objectid, rx, ry, rz);
            SlotData[id][SlotPos][0] = x;
            SlotData[id][SlotPos][1] = y;
            SlotData[id][SlotPos][2] = z;
            SlotData[id][SlotRotPos][0] = rx;
            SlotData[id][SlotRotPos][1] = ry;
            SlotData[id][SlotRotPos][2] = rz;
            
            Slot_Refresh(id);
            Slot_Save(id);
            AccountData[playerid][pEditSlotID] = -1;
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new id = SlotNearest(playerid, 2.0);
        if(id > -1) 
        {
            SendClientMessage(playerid, -1, "");
            SendClientMessage(playerid, -1, "");
            SendClientMessage(playerid, -1, "");
            SendClientMessage(playerid, -1, "");
            SendClientMessage(playerid, -1, "");
            SendClientMessage(playerid, -1, "");
            SendClientMessage(playerid, -1, "");
            SendClientMessage(playerid, -1, "");
            SendClientMessage(playerid, -1, "");
            SendClientMessage(playerid, -1, "");
            SendClientMessage(playerid, -1, "");

            Info(playerid, "SLOT SYSTEM. PERHATIKAN COMMAND DIBAWAH INI!");
            Info(playerid, "~> '/spin' '/changebet'. Jika ingin keluar dari mode slot gunakan tombol "GREEN"F/Enter");
            PutPlayerInSlotMachine(playerid, _, Inventory_Count(playerid, "Chip"));
        }
    }
    return 1;
}

// hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
// {
//     switch(dialogid)
//     {
//         case DIALOG_SLOT_BID:
//         {
//             new id = SlotNearest(playerid, 1.5);
//             if(id == -1) return 0;
//             if(!response) return 1;

//             new title[100];
//             if(isnull(inputtext))
//             {
//                 format(title, sizeof(title), ""TCRP"District  "WHITE"- Mesin %02d", id+1);
//                 ShowPlayerDialog(playerid, DIALOG_SLOT_BID, DIALOG_STYLE_INPUT, title, 
//                 "Error: Tidak dapat diisi kosong!\nMasukkan berapa jumlah uang yang ingin anda bid:", "Bid", "Batal");
//                 return 1;
//             }

//             if(!IsNumeric(inputtext))
//             {
//                 format(title, sizeof(title), ""TCRP"District  "WHITE"- Mesin %02d", id+1);
//                 ShowPlayerDialog(playerid, DIALOG_SLOT_BID, DIALOG_STYLE_INPUT, title, 
//                 "Error: Hanya dapat diisi angka!\nMasukkan berapa jumlah uang yang ingin anda bid:", "Bid", "Batal");
//                 return 1;
//             }

//             if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pMoney])
//             {
//                 format(title, sizeof(title), ""TCRP"District  "WHITE"- Mesin %02d", id+1);
//                 ShowPlayerDialog(playerid, DIALOG_SLOT_BID, DIALOG_STYLE_INPUT, title, 
//                 "Error: Jumlah tidak valid!\nMasukkan berapa jumlah uang yang ingin anda bid:", "Bid", "Batal");
//                 return 1;
//             }
//             new bidcash = strval(inputtext);
//         }
//     }
//     return 1;
// }