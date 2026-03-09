#include <YSI\y_hooks>

#define MAX_OBJECTTEXT  (2000)

enum objectData {
    oID,
    oExists,
    oModel,
    oText[255],
    oFontNames[24],
    Float:oPos[6],
    oFontColor,
    oBackColor,
    oVw,
    oInt,
    STREAMER_TAG_OBJECT:objectText,
    oFontSize
};
new ObjectTextData[MAX_OBJECTTEXT][objectData];

ObjectText_Create(playerid, name[], Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, fontcolor = 0xFFFFFFFF, backcolor = 0x000000FF)
{
    static
        string[128];
    
    for (new i = 0; i != MAX_OBJECTTEXT; i ++) if (!ObjectTextData[i][oExists])
    {
        ObjectTextData[i][oExists] = true;
        FixText(name);
        format(ObjectTextData[i][oText], 255, "%s", name);
        format(ObjectTextData[i][oFontNames], 24, "Arial");

        ObjectTextData[i][oPos][0] = x;
        ObjectTextData[i][oPos][1] = y;
        ObjectTextData[i][oPos][2] = z;
        ObjectTextData[i][oPos][3] = rx;
        ObjectTextData[i][oPos][4] = ry;
        ObjectTextData[i][oPos][5] = rz;

        ObjectTextData[i][oModel] = 18244;

        ObjectTextData[i][oFontColor] = fontcolor;
        ObjectTextData[i][oBackColor] = backcolor;

        ObjectTextData[i][oFontSize] = 130;

        ObjectTextData[i][oInt] = GetPlayerInterior(playerid);
        ObjectTextData[i][oVw] = GetPlayerVirtualWorld(playerid);

        format(string, sizeof(string), "INSERT INTO `objecttext` (`Vw`) VALUES(%d)", ObjectTextData[i][oVw]);
        mysql_tquery(g_SQL, string, "OnObjectTextCreated", "d", i);

        ObjectText_Refresh(i);
        return i;
    }
    return 1;
}

ObjectText_Save(objectid)
{
    new query[2048];
    format(query, sizeof(query), "UPDATE `objecttext` SET `Text`='%q',`PosX`='%.4f',`PosY`='%.4f',`PosZ`='%.4f',`posRX`='%.4f',`posRY`='%.4f',`posRZ`='%.4f',`Vw`='%d',`Int`='%d',`FontColor`='%d',`BackColor`='%d',`FontSize`='%d',`FontNames`='%s',`Model`='%d' WHERE `ID` = '%d'",
        ObjectTextData[objectid][oText],
        ObjectTextData[objectid][oPos][0],
        ObjectTextData[objectid][oPos][1],
        ObjectTextData[objectid][oPos][2],
        ObjectTextData[objectid][oPos][3],
        ObjectTextData[objectid][oPos][4],
        ObjectTextData[objectid][oPos][5],
        ObjectTextData[objectid][oVw],
        ObjectTextData[objectid][oInt],
        ObjectTextData[objectid][oFontColor],
        ObjectTextData[objectid][oBackColor],
        ObjectTextData[objectid][oFontSize],
        ObjectTextData[objectid][oFontNames],
        ObjectTextData[objectid][oModel],
        ObjectTextData[objectid][oID]
    );
    return mysql_tquery(g_SQL, query);
}

ObjectText_Refresh(id)
{
    if(id != -1 && ObjectTextData[id][oExists])
    {
        if(DestroyDynamicObject(ObjectTextData[id][objectText]))
            ObjectTextData[id][objectText] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        ObjectTextData[id][objectText] = CreateDynamicObject(ObjectTextData[id][oModel], ObjectTextData[id][oPos][0], ObjectTextData[id][oPos][1], ObjectTextData[id][oPos][2], ObjectTextData[id][oPos][3], ObjectTextData[id][oPos][4], ObjectTextData[id][oPos][5], ObjectTextData[id][oVw], ObjectTextData[id][oInt], -1, 300, 300);
        SetDynamicObjectMaterialText(ObjectTextData[id][objectText], 0, ObjectTextData[id][oText], ObjectTextData[id][oFontSize], ObjectTextData[id][oFontNames], 32, 1, ObjectTextData[id][oFontColor], ObjectTextData[id][oBackColor], 1);
        ObjectText_Save(id);
    }
    return 1;
}

ObjectText_Delete(id)
{
    if(id != -1 && ObjectTextData[id][oExists])
    {
        if(DestroyDynamicObject(ObjectTextData[id][objectText]))
            ObjectTextData[id][objectText] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        mysql_tquery(g_SQL, sprintf("DELETE FROM `objecttext` WHERE `ID` = '%d'", ObjectTextData[id][oID]));

        ObjectTextData[id][oExists] = false;
        ObjectTextData[id][oText][0] = EOS;
        ObjectTextData[id][objectText] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        ObjectTextData[id][oID] = 0;
    }
    return 1;
}

ObjectText_NearRefresh(id)
{
    foreach(new i : Player) if(IsPlayerInRangeOfPoint(i, 80, ObjectTextData[id][oPos][0], ObjectTextData[id][oPos][1], ObjectTextData[id][oPos][2])) {
        Streamer_Update(i, STREAMER_TYPE_OBJECT);
    }
    return 1;
}

FUNC::OnObjectTextCreated(objectid)
{
    if(objectid == -1 || !ObjectTextData[objectid][oExists])
        return 0;
    
    ObjectTextData[objectid][oID] = cache_insert_id();

    ObjectText_Save(objectid);
    return 1;
}

FUNC::ObjectText_Load()
{
    static
        rows,
        fields;
    
    cache_get_data(rows, fields);

    for (new i = 0; i < rows; i ++) if (i < MAX_OBJECTTEXT)
    {
        ObjectTextData[i][oExists] = true;
        ObjectTextData[i][oID] = cache_get_field_int(i, "ID");

        cache_get_field_content(i, "Text", ObjectTextData[i][oText], 255);
        cache_get_field_content(i, "FontNames", ObjectTextData[i][oFontNames]);

        ObjectTextData[i][oVw] = cache_get_field_int(i, "Vw");
        ObjectTextData[i][oInt] = cache_get_field_int(i, "Int");
        ObjectTextData[i][oFontColor] = cache_get_field_int(i, "FontColor");
        ObjectTextData[i][oBackColor] = cache_get_field_int(i, "BackColor");
        ObjectTextData[i][oFontSize] = cache_get_field_int(i, "FontSize");
        ObjectTextData[i][oModel] = cache_get_field_int(i, "Model");

        ObjectTextData[i][oPos][0] = cache_get_field_float(i, "PosX");
        ObjectTextData[i][oPos][1] = cache_get_field_float(i, "PosY");
        ObjectTextData[i][oPos][2] = cache_get_field_float(i, "PosZ");
        ObjectTextData[i][oPos][3] = cache_get_field_float(i, "posRX");
        ObjectTextData[i][oPos][4] = cache_get_field_float(i, "posRY");
        ObjectTextData[i][oPos][5] = cache_get_field_float(i, "posRZ");

        ObjectText_Refresh(i);
    }
    printf("[Dynamic Object Text]: Jumlah total dynamic object text yang dimuat %d.", rows);
    return 1;
}

Dialog:PilihWarna(playerid, response, listitem, inputtext[])
{
    new id = GetPVarInt(playerid, "BackColor");

    if(response)
    {
        ObjectTextData[id][oBackColor] = AvailableColor[listitem][0];
        ObjectText_Refresh(id);
        ObjectText_NearRefresh(id);
        Info(playerid, "Anda mengupdate backcolor object ini menjadi %s", AvailableColor[listitem][1]);
    }
    return 1;
}

Dialog:MasukkanWarna(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new id = GetPVarInt(playerid, "BackColor"),
            hax;

        if(sscanf(inputtext,"h", hax))
            return Error(playerid, "Invalid hax color");

        ObjectTextData[id][oBackColor] = hax;
        ObjectText_Refresh(id);
        ObjectText_NearRefresh(id);
        Info(playerid, "Anda mengupdate backcolor object ini.");
    }
    return 1;
}

Dialog:WarnaBelakang(playerid, response, listitem, inputtext[])
{
    new id = GetPVarInt(playerid, "BackColor"),
        string[128];

    if(response)
    {
        switch(listitem)
        {
            case 0: Dialog_Show(playerid, MasukkanWarna, DIALOG_STYLE_INPUT,"Custom Backcolor","Enter a hex value for the font color (ARGB)\nFormat example: 0xFFFFFFFF for white","Submit","Close");
            case 1:
            {
                for (new i = 0, j = sizeof(AvailableColor); i < j; i++)
                {
                        format(string,sizeof(string),"%s%s\n",string, AvailableColor[i][1]);
                }
                Dialog_Show(playerid, PilihWarna, DIALOG_STYLE_LIST,"Available Color",string,"Select","Close");
            }
            case 2:
            {
                ObjectTextData[id][oBackColor] = 0x00000000;
                ObjectText_Refresh(id);
                ObjectText_NearRefresh(id);
                Info(playerid, "Anda mengupdate backcolor object ini menjadi transparant!");
            }
        }
    }
    return 1;
}

Dialog:FontSizes(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new id = GetPVarInt(playerid, "FontSizes");

        ObjectTextData[id][oFontSize] = FontSizes[listitem][0];
        ObjectText_Refresh(id);
        ObjectText_NearRefresh(id);
        Info(playerid, "Anda mengupdate fontsize object ini (%s)", FontSizes[listitem][1]);
    }
    return 1;
}

Dialog:FontNames(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new id = GetPVarInt(playerid, "FontNames");

        format(ObjectTextData[id][oFontNames], 24, inputtext);

        ObjectText_Refresh(id);
        ObjectText_NearRefresh(id);
        Info(playerid, "Anda mengupdate font name object ini menjadi (%s).", inputtext);
    }
    return 1;
}

Dialog:ObjectList(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new id = GetPVarInt(playerid, "ObjectList");

        ObjectTextData[id][oModel] = ObjectList[listitem][0];

        ObjectText_Refresh(id);
        ObjectText_NearRefresh(id);
        Info(playerid, "Anda mengupdate object ini menjadi object %d", ObjectList[listitem][0]);
    }
    return 1;
}

alias:createobjecttext("cot")
CMD:createobjecttext(playerid, params[])
{
    static 
        text[128],
        backcolor,
        fontcolor,
        Float:x,
        Float:y,
        Float:z,
        Float:angle,
        id;
    
    if(AccountData[playerid][pAdmin] < 5) 
        return PermissionError(playerid);
    
    if(sscanf(params, "hhs[128]", fontcolor, backcolor, text))
    {
        Syntax(playerid, "/createobjecttext [font color (0xFFFFFFFF)] [back color (0xFFFFFFFF)] [text]");
        Syntax(playerid, "Untuk text anda dapat menggunakan format '\n' (line baru) '\t' (tab baru)");
        return 1;
    }

    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, angle);

    x += 1.5 * floatsin(-angle, degrees);
    y += 1.5 * floatsin(-angle, degrees);

    if(strlen(text) > 128)
        return Error(playerid, "Text terlalu panjang, maximum character adalah 128!");
    
    id = ObjectText_Create(playerid, ColouredText(text), x, y, z, 0, 0, 0, fontcolor, backcolor);

    if(id == -1)
        return Error(playerid, "The server has reached the limit for object.");

    AccountData[playerid][pEditTextObject] = id;
    EditDynamicObject(playerid, ObjectTextData[id][objectText]);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" membuat object text ID: %d", AccountData[playerid][pAdminname], id);
    // Info(playerid, "You have successfully created object ID: %d", id);
    return 1;
}

CMD:gotoobjecttext(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 1) return PermissionError(playerid);

	new id;
	if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotoobjecttext [id]");
	if((id < 0 || id >= MAX_OBJECTTEXT) || !ObjectTextData[id][oExists]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda memasukkan ID Object Text yang tidak valid!");

	SetPlayerPositionEx(playerid, ObjectTextData[id][oPos][0], ObjectTextData[id][oPos][1], ObjectTextData[id][oPos][2], 0.0, 500);
	SetPlayerInterior(playerid, ObjectTextData[id][oInt]);
	SetPlayerVirtualWorld(playerid, ObjectTextData[id][oVw]);
	AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Teleportasi ke Object Text ID:%d", GetAdminName(playerid), id);
    return 1;
}

alias:destroyobjecttext("dot")
CMD:destroyobjecttext(playerid, params[])
{
    static
        id = 0;
    
    if(AccountData[playerid][pAdmin] < 5) 
        return PermissionError(playerid);
    
    if(sscanf(params, "d", id))
        return Syntax(playerid, "/destroyobjecttext [object id]");
    
    if((id < 0 || id >= MAX_OBJECTTEXT) || !ObjectTextData[id][oExists])
        return Error(playerid, "Anda memasukkan ID Object Text yang tidak valid!");
    
    ObjectText_Delete(id);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" menghapus dynamic object text ID: %d", AccountData[playerid][pAdminname], id);
    return 1;
}

alias:editobjecttext("eot")
CMD:editobjecttext(playerid, params[])
{
    static
        id,
        type[24],
        string[128];

    if (AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", id, type, string))
    {
        Syntax(playerid, "/editobjecttext [id] [name]");
        SendClientMessage(playerid, X11_YELLOW_2, "[NAMES]:"WHITE" position, name, fontcolor, backcolor, duplicate, fontsize, font, model");
        return 1;
    }
    if((id < 0 || id >= MAX_OBJECTTEXT) || !ObjectTextData[id][oExists])
        return Error(playerid, "Anda memasukkan ID Object Text yang tidak valid.");

    if(!strcmp(type, "position", true))
    {
        AccountData[playerid][pEditTextObject] = id;
        EditDynamicObject(playerid, ObjectTextData[id][objectText]);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" now edit object text ID: %d.", AccountData[playerid][pAdminname], id);
    }
    else if(!strcmp(type, "name", true))
    {
        new name[128];
        if(sscanf(string,"s[128]", name))
            return Syntax(playerid, "/editobjecttext [id] [name] [text]");

        FixText(name);
        format(ObjectTextData[id][oText], 255, ColouredText(name));
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" has edited name of object text ID: %d.", AccountData[playerid][pAdminname], id);
        ObjectText_Refresh(id);
    }
    else if(!strcmp(type, "fontcolor", true))
    {
        new hax;
        if(sscanf(string,"h", hax))
            return Syntax(playerid, "/editobjecttext [id] [fontcolor] [hax color]");

        ObjectTextData[id][oFontColor] = hax;
        ObjectText_Refresh(id);
    }
    else if(!strcmp(type, "fontsize", true))
    {
        SetPVarInt(playerid, "FontSizes",id);

        for (new i = 0, j = sizeof(FontSizes); i < j; i++)
        {
            format(string,sizeof(string),"%s%s\n",string,FontSizes[i][1]);
        }
        Dialog_Show(playerid, FontSizes, DIALOG_STYLE_LIST, "FontSize", string, "Select","Close");
    }
    else if(!strcmp(type, "font", true))
    {
        SetPVarInt(playerid, "FontNames",id);
        Dialog_Show(playerid, FontNames, DIALOG_STYLE_LIST, "Font Name's", object_font, "Select","Close");
    }
    else if(!strcmp(type, "model", true))
    {
        new textModel[256];

        SetPVarInt(playerid, "ObjectList",id);

        for (new i = 0, j = sizeof(ObjectList); i < j; i++)
        {
            strcat(textModel, sprintf("%d\t%s\n", ObjectList[i][0], ObjectList[i][1]));
        }
        Dialog_Show(playerid, ObjectList, DIALOG_STYLE_LIST, "Object's Model", textModel, "Select","Close");
    }
    else if(!strcmp(type, "backcolor", true))
    {
        SetPVarInt(playerid, "BackColor",id);
        Dialog_Show(playerid, WarnaBelakang, DIALOG_STYLE_LIST,"BackColor","Custom Color\nAvailable Color\nTransparant","Next","Close");
    }
    else if(!strcmp(type, "duplicate", true))
    {
        new name[128], ids;
        if(sscanf(string,"s[128]", name))
            return Syntax(playerid, "/editobjecttext [id] [duplicate] [name]");

        if(strlen(name) > 128)
            return Error(playerid, "The name to long, maximum character is 128.");

        ids = ObjectText_Create(playerid, ColouredText(name), ObjectTextData[id][oPos][0], ObjectTextData[id][oPos][1], ObjectTextData[id][oPos][2], ObjectTextData[id][oPos][3], ObjectTextData[id][oPos][4], ObjectTextData[id][oPos][5], ObjectTextData[id][oFontColor], ObjectTextData[id][oBackColor]);

        if(ids == -1)
            return Error(playerid, "The server has reached the limit for object.");

        EditDynamicObject(playerid, ObjectTextData[ids][objectText]);
        AccountData[playerid][pEditTextObject] = ids;
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" has duplicate object text ID: %d, new object text (id %d).", AccountData[playerid][pAdminname], id, ids);
    }
    ObjectText_NearRefresh(id);
    return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    if(AccountData[playerid][pEditTextObject] != -1 && ObjectTextData[AccountData[playerid][pEditTextObject]][oExists])
    {
        if(response == EDIT_RESPONSE_FINAL)
        {
            ObjectTextData[AccountData[playerid][pEditTextObject]][oPos][0] = x;
            ObjectTextData[AccountData[playerid][pEditTextObject]][oPos][1] = y;
            ObjectTextData[AccountData[playerid][pEditTextObject]][oPos][2] = z;
            ObjectTextData[AccountData[playerid][pEditTextObject]][oPos][3] = rx;
            ObjectTextData[AccountData[playerid][pEditTextObject]][oPos][4] = ry;
            ObjectTextData[AccountData[playerid][pEditTextObject]][oPos][5] = rz;

            ObjectText_Refresh(AccountData[playerid][pEditTextObject]);
            ObjectText_NearRefresh(AccountData[playerid][pEditTextObject]);
            ObjectText_Save(AccountData[playerid][pEditTextObject]);

            Info(playerid, "You have edited the position of object text ID: %d.", AccountData[playerid][pEditTextObject]);

            AccountData[playerid][pEditTextObject] = -1;
            
            if(AccountData[playerid][pEditTextObject] != -1) {
                ObjectText_Refresh(AccountData[playerid][pEditTextObject]);
                AccountData[playerid][pEditTextObject] = -1;
            }
        }
        if(response == EDIT_RESPONSE_CANCEL)
        {
            if(AccountData[playerid][pEditTextObject] != -1) {
                ObjectText_Refresh(AccountData[playerid][pEditTextObject]);
                ObjectText_NearRefresh(AccountData[playerid][pEditTextObject]);
                AccountData[playerid][pEditTextObject] = -1;
            }
        }
    }
    return 1;
}