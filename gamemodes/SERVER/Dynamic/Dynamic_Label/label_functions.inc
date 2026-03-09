#include <YSI\y_hooks>
#define MAX_DYNAMIC_LABEL   (50)

enum e_labeldata
{
    Float:labelPos[3],
    Float:labelRot[3],
    labelText[128],
    labelInterior,
    labelWorld,
    
    STREAMER_TAG_OBJECT:labelObject
};
new LabelData[MAX_DYNAMIC_LABEL][e_labeldata],
    Iterator:Label<MAX_DYNAMIC_LABEL>;

RefreshLabel(id)
{
    if(id != -1)
    {
        if(IsValidDynamicObject(LabelData[id][labelObject]))
            DestroyDynamicObject(LabelData[id][labelObject]);
        
        if(LabelData[id][labelPos][0] != 0.0 || LabelData[id][labelPos][1] != 0.0 || LabelData[id][labelPos][2] != 0.0)
        {
            static shstr[200];
            format(shstr, sizeof(shstr), ""DEEPSKYBLUE1"%s", LabelData[id][labelText]);
            LabelData[id][labelObject] = CreateDynamicObject(19482, LabelData[id][labelPos][0], LabelData[id][labelPos][1], LabelData[id][labelPos][2], LabelData[id][labelRot][0], LabelData[id][labelRot][1], LabelData[id][labelRot][2], LabelData[id][labelWorld], LabelData[id][labelInterior], -1, 300.00, 300.00); 
            SetDynamicObjectMaterialText(LabelData[id][labelObject], 0, shstr, 130, "Arial", 35, 1, 0x00000000, 0x00000000, 1);
        }
    }
    return 1;
}

forward LoadLabel();
public LoadLabel()
{
    new id, rows = cache_num_rows();
    new Cache:Labelcache;
    if(rows)
    {
        Labelcache = cache_save();

        for(new i = 0; i < rows; i ++)
        {
            id = cache_get_field_int(i, "LabelID");

            cache_get_field_content(i, "LabelText", LabelData[id][labelText], 128);
            
            LabelData[id][labelPos][0] = cache_get_field_float(i, "LabelX");
            LabelData[id][labelPos][1] = cache_get_field_float(i, "LabelY");
            LabelData[id][labelPos][2] = cache_get_field_float(i, "LabelZ");
            LabelData[id][labelRot][0] = cache_get_field_float(i, "LabelRX");
            LabelData[id][labelRot][1] = cache_get_field_float(i, "LabelRY");
            LabelData[id][labelRot][2] = cache_get_field_float(i, "LabelRZ");
            LabelData[id][labelInterior] = cache_get_field_int(i, "LabelInterior");
            LabelData[id][labelWorld] = cache_get_field_int(i, "LabelWorld");

            RefreshLabel(id);
            Iter_Add(Label, id);
        }
        printf("[Dynamic Label Fivem]: Jumlah total Label yang dimuat %d.", rows);

        if(cache_is_valid(Labelcache))
        {
            cache_delete(Labelcache);
            printf("[Dynamic Label]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Label]: Cache tidak valid atau sudah dihapus.");
        }
    }
    return 1;
}

LabelSave(id)
{
    new query[1218];
    mysql_format(g_SQL, query, sizeof(query), "UPDATE `label_fivem` SET `LabelText`='%s', `LabelX`=%f, `LabelY`=%f, `LabelZ`=%f, `LabelRX`=%f, `LabelRY`=%f, `LabelRZ`=%f, `LabelInterior`=%d, `LabelWorld`=%d WHERE `LabelID`=%d",
    LabelData[id][labelText], LabelData[id][labelPos][0], LabelData[id][labelPos][1], LabelData[id][labelPos][2], LabelData[id][labelRot][0], LabelData[id][labelRot][1], LabelData[id][labelRot][2], LabelData[id][labelInterior], LabelData[id][labelWorld], id);
    return mysql_tquery(g_SQL, query);
}


CMD:addlabel(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    new id = Iter_Free(Label), text[128];
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menambah label lagi!");
    if(sscanf(params, "s[128]", text)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addlabel [text]");
    if(strlen(text) < 1 || strlen(text) > 128) return ShowTDN(playerid, NOTIFICATION_ERROR, "Text tidak dapat kurang dari 1 atau lebih dari 128 characters!");

    new Float:x, Float:y, Float:z, Float:angle;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, angle);

    LabelData[id][labelPos][0] = x;
    LabelData[id][labelPos][1] = y;
    LabelData[id][labelPos][2] = z;
    LabelData[id][labelRot][0] = 0.0;
    LabelData[id][labelRot][1] = 0.0;
    LabelData[id][labelRot][2] = angle;
    format(LabelData[id][labelText], sizeof(text), ""DEEPSKYBLUE1"%s", text);
    LabelData[id][labelInterior] = GetPlayerInterior(playerid);
    LabelData[id][labelWorld] = GetPlayerVirtualWorld(playerid);

    RefreshLabel(id);
    Iter_Add(Label, id);

    new query[596];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `label_fivem` SET `LabelID`=%d, `LabelX`=%f, `LabelY`=%f, `LabelZ`=%f, `LabelRX`=0, `LabelRY`=0, `LabelRZ`=%f, `LabelInterior`=%d, `LabelWorld`=%d, `LabelText`='%s'",
    id, LabelData[id][labelPos][0], LabelData[id][labelPos][1], LabelData[id][labelPos][2], LabelData[id][labelRot][2], LabelData[id][labelInterior], LabelData[id][labelWorld], LabelData[id][labelText]);
    mysql_tquery(g_SQL, query, "OnLabelAdded", "dd", playerid, id);
    return 1;
}

CMD:removelabel(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    new id, query[255];
    if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/removelabel [id]");
    if(id < 0 || id >= MAX_DYNAMIC_LABEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Label tidak valid!");
    if(!Iter_Contains(Label, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Label tidak ada!");

    LabelData[id][labelPos][0] = LabelData[id][labelPos][1] = LabelData[id][labelPos][2] = 0.0;
    LabelData[id][labelRot][0] = LabelData[id][labelRot][1] = LabelData[id][labelRot][2] = 0.0;
    LabelData[id][labelInterior] = LabelData[id][labelWorld] = -1;
    format(LabelData[id][labelText], 32, "-");

    RefreshLabel(id);
    Iter_Remove(Label, id);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menghapus Dynamic Label ID: %d.", GetAdminName(playerid), id);

    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `label_fivem` WHERE `LabelID`=%d", id);
    mysql_tquery(g_SQL, query);
    return 1;
}

forward OnLabelAdded(playerid, id);
public OnLabelAdded(playerid, id)
{
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menambahkan label fivem ID: %d", GetAdminName(playerid), id);
    LabelSave(id);
    return 1;
}

CMD:gotolabel(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1) return PermissionError(playerid);

    new id;
    if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotolabel [id]");
    if(!Iter_Contains(Label, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Label ID tidak ada!");
    if(id < 0 || id >= MAX_DYNAMIC_LABEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Label ID tidak valid!");

    SetPlayerPositionEx(playerid, LabelData[id][labelPos][0], LabelData[id][labelPos][1], LabelData[id][labelPos][2], 2000);
    SetPlayerInterior(playerid, LabelData[id][labelInterior]);
    SetPlayerVirtualWorld(playerid, LabelData[id][labelWorld]);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Teleportasi ke Label ID: %d", GetAdminName(playerid), id);
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInBiz] = -1;
    return 1;
}