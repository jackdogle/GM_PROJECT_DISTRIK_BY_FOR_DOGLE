#include <YSI\y_hooks>
#define MAX_DYNAMIC_OBJECT  (8000)

enum e_dynamicobjectdata
{
    objectModel,
    Float:objectPos[3],
    Float:objectRot[3],
    objectInterior,
    objectWorld,
    STREAMER_TAG_OBJECT:objectPhysic,

    bool: objectExists,
};
new ObjectData[MAX_DYNAMIC_OBJECT][e_dynamicobjectdata],
    Iterator:DynObject<MAX_DYNAMIC_OBJECT>;

new 
    EditDynamicObjectID[MAX_PLAYERS],
    bool: DurringEditDynamicObject[MAX_PLAYERS] = { false, ... },
    Float:ObjectPosition[MAX_PLAYERS][3],
    Float:ObjectRotation[MAX_PLAYERS][3]
;

Object_Saving(id)
{
    new cQuery[598];
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `objects` SET `Model`=%d, `ObjectX`=%f, `ObjectY`=%f, `ObjectZ`=%f, `ObjectRX`=%f, `ObjectRY`=%f, `ObjectRZ`=%f, `ObjectInterior`=%d, `ObjectWorld`=%d WHERE `ID`=%d", \
    ObjectData[id][objectModel], ObjectData[id][objectPos][0], ObjectData[id][objectPos][1], ObjectData[id][objectPos][2], ObjectData[id][objectRot][0], ObjectData[id][objectRot][1], ObjectData[id][objectRot][2], ObjectData[id][objectInterior], ObjectData[id][objectWorld], id);
    mysql_tquery(g_SQL, cQuery);
    return 1;
}

Object_Rebuild(id)
{
    if(id != -1)
    {
        if(DestroyDynamicObject(ObjectData[id][objectPhysic]))
            ObjectData[id][objectPhysic] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        if(ObjectData[id][objectModel] && ObjectData[id][objectPos][0] != 0.0)
        {
            ObjectData[id][objectPhysic] = CreateDynamicObject(ObjectData[id][objectModel], ObjectData[id][objectPos][0], ObjectData[id][objectPos][1], ObjectData[id][objectPos][2], ObjectData[id][objectRot][0], ObjectData[id][objectRot][1], ObjectData[id][objectRot][2], ObjectData[id][objectWorld], ObjectData[id][objectInterior], -1, 300.0, 300.0, -1); 
        }
    }
    return 1;
}

Object_BeingEdited(id)
{
	if(!Iter_Contains(DynObject, id)) return 0;
	foreach(new i : Player) if(EditDynamicObjectID[i] == id) return 1;
	return 0;
}

forward OnObjectAdded(id);
public OnObjectAdded(id)
{
    Object_Saving(id);
    return 1;
}

forward LoadDynamicObject();
public LoadDynamicObject()
{
    new rowscount = cache_num_rows();
    static objid;
    if(rowscount)
    {
        for(new i = 0; i < rowscount; i ++)
        {
            objid = cache_get_field_int(i, "ID");
            ObjectData[objid][objectModel] = cache_get_field_int(i, "Model");
            ObjectData[objid][objectPos][0] = cache_get_field_float(i, "ObjectX");
            ObjectData[objid][objectPos][1] = cache_get_field_float(i, "ObjectY");
            ObjectData[objid][objectPos][2] = cache_get_field_float(i, "ObjectZ");
            ObjectData[objid][objectRot][0] = cache_get_field_float(i, "ObjectRX");
            ObjectData[objid][objectRot][1] = cache_get_field_float(i, "ObjectRY");
            ObjectData[objid][objectRot][2] = cache_get_field_float(i, "ObjectRZ");
            ObjectData[objid][objectInterior] = cache_get_field_int(i, "ObjectInterior");
            ObjectData[objid][objectWorld] = cache_get_field_int(i, "ObjectWorld");

            Object_Rebuild(objid);
            Iter_Add(DynObject, objid);
        }
        printf("[Dynamic Object]: Jumlah total Dynamic Object yang dimuat %d.", rowscount);
    }
}

alias:createobject("co")
CMD:createobject(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 7) return PermissionError(playerid);

    new model, id = Iter_Free(DynObject);
    if(id == -1) return Error(playerid, "Tidak dapat menambah object lagi ke server!");
    if(sscanf(params, "d", model)) return Syntax(playerid, "/createobject [model id]");

    GetPlayerPos(playerid, ObjectData[id][objectPos][0], ObjectData[id][objectPos][1], ObjectData[id][objectPos][2]);
    ObjectData[id][objectModel] = model;
    ObjectData[id][objectPos][0] = ObjectData[id][objectPos][0] + 2;
    ObjectData[id][objectRot][0] = ObjectData[id][objectRot][1] = ObjectData[id][objectRot][2] = 0.0;
    ObjectData[id][objectInterior] = GetPlayerInterior(playerid);
    ObjectData[id][objectWorld] = GetPlayerVirtualWorld(playerid);

    Object_Rebuild(id);
    Iter_Add(DynObject, id);
    SendClientMessageEx(playerid, -1, ""BLUEJEGE"OBJECT:"WHITE" Object ID %d created with "BLUEJEGE"Model %d", id, model);

    new cQuery[598];
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `objects` SET `ID`=%d, `Model`=%d, `ObjectX`=%f, `ObjectY`=%f, `ObjectZ`=%f, `ObjectRX`=%f, `ObjectRY`=%f, `ObjectRZ`=%f, `ObjectInterior`=%d, `ObjectWorld`=%d",
    id, ObjectData[id][objectModel], ObjectData[id][objectPos][0], ObjectData[id][objectPos][1], ObjectData[id][objectPos][2], ObjectData[id][objectRot][0], ObjectData[id][objectRot][1], ObjectData[id][objectRot][2], ObjectData[id][objectInterior], ObjectData[id][objectWorld]);
    mysql_tquery(g_SQL, cQuery, "OnObjectAdded", "d", id);
    return 1;
}

CMD:ogoto(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 1) return PermissionError(playerid);

    new id;
    if(sscanf(params, "d", id)) return Syntax(playerid, "/ogoto [object id]");
    if(id < 0 || id >= MAX_DYNAMIC_OBJECT) return Error(playerid, "Object ID tidak valid!");
    if(!Iter_Contains(DynObject, id)) return Error(playerid, "Object ID tidak ada!");

    SetPlayerPositionEx(playerid, ObjectData[id][objectPos][0], ObjectData[id][objectPos][1], ObjectData[id][objectPos][2], SetPlayerFace(playerid, ObjectData[id][objectPos][0], ObjectData[id][objectPos][1]));
    SetPlayerVirtualWorldEx(playerid, ObjectData[id][objectWorld]);
    SetPlayerInteriorEx(playerid, ObjectData[id][objectInterior]);

    SendClientMessageEx(playerid, -1, ""BLUEJEGE"OBJECT:"WHITE" You has teleported to "BLUEJEGE"Object ID %d", id);
    return 1;
}

alias:editobject("eo")
CMD:editobject(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 7) return PermissionError(playerid);

    static id;
    if(sscanf(params, "d", id)) return Syntax(playerid, "/editobject [object id]");
    if(id < 0 || id >= MAX_DYNAMIC_OBJECT) return Error(playerid, "ID Object tidak valid.");
    if(!Iter_Contains(DynObject, id)) return Error(playerid, "ID Object tersebut tidak ada di server");
    if(Object_BeingEdited(id)) return Error(playerid, "Object tersebut sedang dalam masa pengeditan!");
    if(!IsPlayerInRangeOfPoint(playerid, 30.0, ObjectData[id][objectPos][0], ObjectData[id][objectPos][1], ObjectData[id][objectPos][2])) return Error(playerid, "Anda harus berada di dekat object yang ingin anda edit!");

    DurringEditDynamicObject[playerid] = true;
    EditDynamicObjectID[playerid] = id;
    GetDynamicObjectPos(ObjectData[id][objectPhysic], ObjectPosition[playerid][0], ObjectPosition[playerid][1], ObjectPosition[playerid][2]);
    GetDynamicObjectRot(ObjectData[id][objectPhysic], ObjectRotation[playerid][0], ObjectRotation[playerid][1], ObjectRotation[playerid][2]);
    EditDynamicObject(playerid, ObjectData[id][objectPhysic]);
    SendClientMessageEx(playerid, -1, ""BLUEJEGE"OBJECT:"WHITE" You being edited "BLUEJEGE"Object ID %d", id);
    return 1;
}

CMD:clone(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 7) return PermissionError(playerid);

    new sourceID, newID = Iter_Free(DynObject);
    if(newID == -1) return Error(playerid, "Tidak dapat menambah object lagi ke server.");
    if(sscanf(params, "d", sourceID)) return Syntax(playerid, "/clone [id object]");
    if(sourceID < 0 || sourceID >= MAX_DYNAMIC_OBJECT) return Error(playerid, "ID Objek Sumber tidak valid.");
    if(!Iter_Contains(DynObject, sourceID)) return Error(playerid, "Objek Sumber tidak ada di server");
    if(!IsPlayerInRangeOfPoint(playerid, 30.0, ObjectData[sourceID][objectPos][0], ObjectData[sourceID][objectPos][1], ObjectData[sourceID][objectPos][2])) return Error(playerid, "Anda harus berada di dekat object yang ingin anda edit!");

    // Dapatkan posisi dan rotasi objek sumber
    GetDynamicObjectPos(ObjectData[sourceID][objectPhysic], ObjectPosition[playerid][0], ObjectPosition[playerid][1], ObjectPosition[playerid][2]);
    GetDynamicObjectRot(ObjectData[sourceID][objectPhysic], ObjectRotation[playerid][0], ObjectRotation[playerid][1], ObjectRotation[playerid][2]);

    // Buat objek dinamis baru di posisi dan rotasi yang sama
    ObjectData[newID][objectModel] = ObjectData[sourceID][objectModel];
    ObjectData[newID][objectPos][0] = ObjectPosition[playerid][0];
    ObjectData[newID][objectPos][1] = ObjectPosition[playerid][1];
    ObjectData[newID][objectPos][2] = ObjectPosition[playerid][2];
    ObjectData[newID][objectRot][0] = ObjectRotation[playerid][0];
    ObjectData[newID][objectRot][1] = ObjectRotation[playerid][1];
    ObjectData[newID][objectRot][2] = ObjectRotation[playerid][2];
    ObjectData[newID][objectInterior] = ObjectData[sourceID][objectInterior];
    ObjectData[newID][objectWorld] = ObjectData[sourceID][objectWorld];

    Object_Rebuild(newID);
    Iter_Add(DynObject, newID);
    SendClientMessageEx(playerid, -1, ""BLUEJEGE"OBJECT:"WHITE" Succesfully Clone "BLUEJEGE"Object ID %d To Object ID %d", sourceID, newID);

    new cQuery[598];
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `objects` SET `ID`=%d, `Model`=%d, `ObjectX`=%f, `ObjectY`=%f, `ObjectZ`=%f, `ObjectRX`=%f, `ObjectRY`=%f, `ObjectRZ`=%f, `ObjectInterior`=%d, `ObjectWorld`=%d",
    newID, ObjectData[newID][objectModel], ObjectData[newID][objectPos][0], ObjectData[newID][objectPos][1], ObjectData[newID][objectPos][2], ObjectData[newID][objectRot][0], ObjectData[newID][objectRot][1], ObjectData[newID][objectRot][2], ObjectData[newID][objectInterior], ObjectData[newID][objectWorld]);
    mysql_tquery(g_SQL, cQuery, "OnObjectAdded", "d", newID);
    return 1;
}

CMD:oswap(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 7) return PermissionError(playerid);

    static id, model;
    if(sscanf(params, "dd", id, model)) return Syntax(playerid, "/oswap [object id] [model id]");
    if(id < 0 || id >= MAX_DYNAMIC_OBJECT) return Error(playerid, "ID Object tidak valid.");
    if(!Iter_Contains(DynObject, id)) return Error(playerid, "ID Object tersebut tidak ada di server");

    ObjectData[id][objectModel] = model;
    Object_Rebuild(id);
    Object_Saving(id);
    SendClientMessageEx(playerid, -1, ""BLUEJEGE"OBJECT:"WHITE" Model has changed to "BLUEJEGE"%d"WHITE" for Object ID %d", model, id);
    return 1;
}

alias:deleteobject("dobject")
CMD:deleteobject(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 7) return PermissionError(playerid);

    static id;
    if(sscanf(params, "d", id)) return Syntax(playerid, "/deleteobject [object id]");
    if(id < 0 || id >= MAX_DYNAMIC_OBJECT) return Error(playerid, "ID Object tidak valid.");
    if(!Iter_Contains(DynObject, id)) return Error(playerid, "ID Object tersebut tidak ada di server");

    ObjectData[id][objectModel] = 0;
    ObjectData[id][objectPos][0] = ObjectData[id][objectPos][1] = ObjectData[id][objectPos][2] = 0.0;
    ObjectData[id][objectRot][0] = ObjectData[id][objectRot][1] = ObjectData[id][objectRot][2] = 0.0;
    ObjectData[id][objectInterior] = ObjectData[id][objectWorld] = 0;

    Object_Rebuild(id);
    Iter_Remove(DynObject, id);
    SendClientMessageEx(playerid, -1, ""BLUEJEGE"OBJECT:"WHITE" You removing "BLUEJEGE"Object ID %d from Server", id);
    mysql_tquery(g_SQL, sprintf("DELETE FROM `objects` WHERE `ID`=%d", id));
    return 1;
}

hook OnPlayerConnect(playerid)
{
    DurringEditDynamicObject[playerid] = false;
    EditDynamicObjectID[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    DurringEditDynamicObject[playerid] = false;
    EditDynamicObjectID[playerid] = -1;
    return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    if(DurringEditDynamicObject[playerid] && EditDynamicObjectID[playerid] != -1 && Iter_Contains(DynObject, EditDynamicObjectID[playerid]))
	{
		new id = EditDynamicObjectID[playerid];
		if(response == EDIT_RESPONSE_UPDATE)
		{
			SetDynamicObjectPos(objectid, x, y, z);
			SetDynamicObjectRot(objectid, rx, ry, rz);
		}
		else if(response == EDIT_RESPONSE_CANCEL)
		{
            DurringEditDynamicObject[playerid] = false;
            EditDynamicObjectID[playerid] = -1;
			SetDynamicObjectPos(objectid, ObjectPosition[playerid][0], ObjectPosition[playerid][1], ObjectPosition[playerid][2]);
			SetDynamicObjectRot(objectid, ObjectRotation[playerid][0], ObjectRotation[playerid][1], ObjectRotation[playerid][2]);
			ObjectPosition[playerid][0] = 0; ObjectPosition[playerid][1] = 0; ObjectPosition[playerid][2] = 0;
			ObjectRotation[playerid][0] = 0; ObjectRotation[playerid][1] = 0; ObjectRotation[playerid][2] = 0;
			Error(playerid, "Anda membatalkan pengeditan object id %d", id);
			Object_Saving(id);
		}
		else if(response == EDIT_RESPONSE_FINAL)
		{
			SetDynamicObjectPos(objectid, x, y, z);
			SetDynamicObjectRot(objectid, rx, ry, rz);

            ObjectData[id][objectPos][0] = x;
            ObjectData[id][objectPos][1] = y;
            ObjectData[id][objectPos][2] = z;
            ObjectData[id][objectRot][0] = rx;
            ObjectData[id][objectRot][1] = ry;
            ObjectData[id][objectRot][2] = rz;

            DurringEditDynamicObject[playerid] = false;
            EditDynamicObjectID[playerid] = -1;
            SendClientMessageEx(playerid, -1, ""BLUEJEGE"OBJECT:"WHITE" You saving positioning "BLUEJEGE"Object ID %d", id);
            Object_Rebuild(id);
            Object_Saving(id);
		}
    }
    return 1;
}