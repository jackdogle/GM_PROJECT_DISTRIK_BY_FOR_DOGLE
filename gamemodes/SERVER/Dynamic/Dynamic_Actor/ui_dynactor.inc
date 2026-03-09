#include <YSI\y_hooks>

enum e_dynactor
{
    aID,
    Float: aPos[4],
    aInterior,
    aWorld,
    aSkin,
    aAnim,
    aName[MAX_PLAYER_NAME],
    STREAMER_TAG_ACTOR:aModel,
    STREAMER_TAG_3D_TEXT_LABEL:aLabel
};
new aData[MAX_ACTORSS][e_dynactor];
new Iterator:DynamicActor<MAX_ACTORSS>;

stock Actor_Nearest(playerid)
{
    foreach(new aid : DynamicActor) {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, aData[aid][aPos][0], aData[aid][aPos][1], aData[aid][aPos][2])) {
            return aid;
        }
    }
    return -1;
}

stock Actor_Create(skin, Float:x, Float:y, Float:z, Float:a, world, interior, anim = 0, name[] = "")
{
    new id = Iter_Free(DynamicActor);
    if(id != INVALID_ITERATOR_SLOT)
    {
        aData[id][aPos][0] = x;
        aData[id][aPos][1] = y;
        aData[id][aPos][2] = z;
        aData[id][aPos][3] = a;
        aData[id][aSkin] = skin;
        aData[id][aInterior] = interior;
        aData[id][aWorld] = world;
        aData[id][aAnim] = anim;
        format(aData[id][aName], MAX_PLAYER_NAME, name);

        Iter_Add(DynamicActor, id);
        Actor_Spawn(id);
        mysql_tquery(g_SQL, "INSERT INTO `actors` (`Skin`) VALUES(0)", "OnActorCreated", "d", id);
		return id;
    }
    return INVALID_ITERATOR_SLOT;
}

FUNC::OnActorCreated(id)
{
	aData[id][aID] = cache_insert_id();
	Actor_Save(id);
}

stock Actor_Spawn(id)
{
    new animlib[32], animname[32];

    if(!IsValidDynamicActor(aData[id][aModel]))
    {
        aData[id][aModel] = CreateDynamicActor(aData[id][aSkin], aData[id][aPos][0], aData[id][aPos][1], aData[id][aPos][2], aData[id][aPos][3], 1, 100.0, aData[id][aWorld], aData[id][aInterior], -1, 55.0, -1, 0);
        aData[id][aLabel] = CreateDynamic3DTextLabel(sprintf("%s", aData[id][aName]), COLOR_WHITE, aData[id][aPos][0], aData[id][aPos][1], aData[id][aPos][2] + 1.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
        if(aData[id][aAnim] != 0)
        {
            GetAnimationName(aData[id][aAnim], animlib, 32, animname, 32);
            ApplyDynamicActorAnimation(aData[id][aModel], animlib, animname, 4.1, 1, 0, 0, 1, 0);
        }
    }
    return 1;
}

stock Actor_Save(id)
{
    if(!Iter_Contains(DynamicActor, id))
        return 1;

    new query[1012];
	mysql_format(g_SQL, query, sizeof(query), "UPDATE `actors` SET ");
	mysql_format(g_SQL, query, sizeof(query), "%s`Skin` = '%d', ", query, aData[id][aSkin]);
	mysql_format(g_SQL, query, sizeof(query), "%s`PosX` = '%f', ", query, aData[id][aPos][0]);
	mysql_format(g_SQL, query, sizeof(query), "%s`PosY` = '%f', ", query, aData[id][aPos][1]);
	mysql_format(g_SQL, query, sizeof(query), "%s`PosZ` = '%f', ", query, aData[id][aPos][2]);
	mysql_format(g_SQL, query, sizeof(query), "%s`PosA` = '%f', ", query, aData[id][aPos][3]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Anim` = '%d', ", query, aData[id][aAnim]);
	mysql_format(g_SQL, query, sizeof(query), "%s`World` = '%d', ", query, aData[id][aWorld]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Interior` = '%d', ", query, aData[id][aInterior]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Name` = '%s' ", query, aData[id][aName]);
	mysql_format(g_SQL, query, sizeof(query), "%sWHERE `ID` = '%d'", query, aData[id][aID]);
	mysql_query(g_SQL, query, true);
	return 1;
}
stock Actor_Delete(id)
{
    if(Iter_Contains(DynamicActor, id))
    {
        mysql_tquery(g_SQL, sprintf("DELETE FROM `actors` WHERE `ID` = '%d'", aData[id][aID]));

        if(DestroyDynamicActor(aData[id][aModel]))
            aData[id][aModel] = STREAMER_TAG_ACTOR: INVALID_STREAMER_ID;
        
        if(DestroyDynamic3DTextLabel(aData[id][aLabel]))
            aData[id][aLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            
        aData[id][aID] = 0;
        Iter_Remove(DynamicActor, id);
    }
    return 1;
}

stock Actor_Refresh(id)
{
    if(Iter_Contains(DynamicActor, id))
    {
        SetDynamicActorPos(aData[id][aModel], aData[id][aPos][0], aData[id][aPos][1], aData[id][aPos][2]);
        SetDynamicActorFacingAngle(aData[id][aModel], aData[id][aPos][3]);

        Streamer_SetPosition(STREAMER_TYPE_3D_TEXT_LABEL, aData[id][aLabel], aData[id][aPos][0], aData[id][aPos][1], aData[id][aPos][2] + 1.0);
        UpdateDynamic3DTextLabelText(aData[id][aLabel], X11_WHITE, sprintf("%s", aData[id][aName]));

        Streamer_SetIntData(STREAMER_TYPE_ACTOR, aData[id][aModel], E_STREAMER_MODEL_ID, aData[id][aSkin]);
        if(aData[id][aAnim] != 0)
        {
            new animlib[32], animname[32];
            GetAnimationName(aData[id][aAnim], animlib, 32, animname, 32);
            ApplyDynamicActorAnimation(aData[id][aModel], animlib, animname, 4.1, 1, 0, 0, 1, 0);

        }
    }
    return 1;
}

forward Actor_Load();
public Actor_Load()
{
    new rows = cache_num_rows();
    new Cache:Actorcache;
    if(rows)
    {
        Actorcache = cache_save();

        for(new x = 0; x < rows; x++)
        {
            cache_get_value_name_int(x, "ID", aData[x][aID]);
			cache_get_value_name(x, "Name", aData[x][aName]);
			cache_get_value_name_int(x, "Anim", aData[x][aAnim]);
			cache_get_value_name_int(x, "Skin", aData[x][aSkin]);
			cache_get_value_name_int(x, "World", aData[x][aWorld]);
			cache_get_value_name_int(x, "Interior", aData[x][aInterior]);
			cache_get_value_name_float(x, "PosX", aData[x][aPos][0]);
			cache_get_value_name_float(x, "PosY", aData[x][aPos][1]);
			cache_get_value_name_float(x, "PosZ", aData[x][aPos][2]);
			cache_get_value_name_float(x, "PosA", aData[x][aPos][3]);

			Iter_Add(DynamicActor, x);

			Actor_Spawn(x);
        }
        printf("[Dynamic Actor] Loaded %d Dynamic Actor from database", rows);
        if(cache_is_valid(Actorcache))
        {
            cache_delete(Actorcache);
            printf("[Dynamic Actor]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Actor]: Cache tidak valid atau sudah dihapus.");
        }
    }
}

CMD:addactor(playerid, params[])
{
    if(CheckAdmin(playerid, 6))
        return PermissionError(playerid);
    
    new name[MAX_PLAYER_NAME], skinid, Float:x, Float:y, Float:z, Float:a;
    if(sscanf(params, "ds[24]", skinid, name))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addactor [skinid] [name]");
    
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);

    new id = Actor_Create(skinid, x, y, z, a, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), 0, name);

    if(id == INVALID_ITERATOR_SLOT)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menambah Actor Lagi!");
    
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah membuat Dynamic Actor ID: %d", GetAdminName(playerid), id);
    SetPlayerPos(playerid, x + 1, y, z);
    return 1;
}

CMD:destroyactor(playerid, params[])
{
    if(CheckAdmin(playerid, 6))
        return PermissionError(playerid);
    
    if(isnull(params))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/removeactor [id actor]");
    
    if(!IsNumeric(params))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "removeactor [id actor]");
    
    if(!Iter_Contains(DynamicActor, strval(params)))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid actor ID!");
    
    Actor_Delete(strval(params));
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah Menghapus Dynamic Actor ID: %d", GetAdminName(playerid), strval(params));
    return 1;
}

CMD:editactor(playerid, params[])
{
    new 
        id,
        type[24],
        string[128];
    
    if(CheckAdmin(playerid, 6))
        return PermissionError(playerid);
    
    if (sscanf(params, "ds[24]S()[128]", id, type, string))
    {
        ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editactor [id] [name]~n~pos, model, name, anim, animclear");
        return 1;
    }
    if(!Iter_Contains(DynamicActor, id))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Actor ID!");
    
    if(!strcmp(type, "pos", true))
    {
        GetPlayerPos(playerid, aData[id][aPos][0], aData[id][aPos][1], aData[id][aPos][2]);
        GetPlayerFacingAngle(playerid, aData[id][aPos][3]);

        Actor_Refresh(id);
        Actor_Save(id);

        SetPlayerPos(playerid, aData[id][aPos][0] + 1, aData[id][aPos][1], aData[id][aPos][2]);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengubah posisi Dynamic Actor ID: %d", GetAdminName(playerid), id);
    }
    else if(!strcmp(type, "animclear", true))
    {
        aData[id][aAnim] = 0;
        ClearDynamicActorAnimations(aData[id][aModel]);

        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menghapus animasi Dynamic Actor ID: %d", GetAdminName(playerid), id);
        Actor_Save(id);
        Actor_Refresh(id);
    }
    else if(!strcmp(type, "model", true))
    {
        if(isnull(string))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editactor [id] [model] [new skin model]");
        
        if(!IsNumeric(string))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editactor [id] [model] [new skin model]");
        
        aData[id][aSkin] = strval(string);
        Actor_Refresh(id);
        Actor_Save(id);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengubah model Dynamic Actor ID: %d menjadi Model ID: %d", GetAdminName(playerid), id, strval(string));
    }
    else if(!strcmp(type, "name", true))
    {
        if(isnull(string))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editactor [id] [name] [new actor name]");
        
        format(aData[id][aName], MAX_PLAYER_NAME, string);
        Actor_Refresh(id);
        Actor_Save(id);

        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengubah nama Dynamic Actor ID: %d Menjadi %s", GetAdminName(playerid), id, string);
    }
    else if(!strcmp(type, "anim", true))
    {
        if(isnull(string))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editactor [id] [anim] [animation index]");

        if(!IsNumeric(string))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editactor [id] [anim] [animation index]");

        if(strval(string) < 1 || strval(string) > 1812)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Animation Index! Search in Open.mp!");
        
        ClearDynamicActorAnimations(aData[id][aModel]);

        new animlib[32], animname[32];
        aData[id][aAnim] = strval(string);
        GetAnimationName(aData[id][aAnim], animlib, 32, animname, 32);
        ApplyDynamicActorAnimation(aData[id][aModel], animlib, animname, 4.1, 1, 0, 0, 1, 0);

        Actor_Save(id);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan animasi Actor ID: %d menjadi Anim Index: %d", GetAdminName(playerid), id, strval(string));
    }
    return 1;
}

CMD:gotoactor(playerid, params[])
{
    new id;
    if(CheckAdmin(playerid, 6))
        return PermissionError(playerid);
    if(sscanf(params, "d", id))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotoactor [id]");
    if(!Iter_Contains(DynamicActor, id))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Actor ID!");
    
    SetPlayerPos(playerid, aData[id][aPos][0] + 1, aData[id][aPos][1], aData[id][aPos][2]);
    SetPlayerInterior(playerid, aData[id][aInterior]);
    SetPlayerVirtualWorld(playerid, aData[id][aWorld]);
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
    
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" teleportasi ke Dynamic Actor ID: %d.", GetAdminName(playerid), id);
    return 1;
}