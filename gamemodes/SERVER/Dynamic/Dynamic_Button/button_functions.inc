#include <YSI\y_hooks>
#define MAX_DYNAMIC_BUTTON  (50)
#define SOUND   1083

enum e_buttondata
{
    bFactionID,
    bFaction2ID,
    bFamilyID,
    bOwnerID,
    Float:ButtonPos[3],
    Float:ButtonRPos[3],
    Float:DoorcPos[3],
    Float:DoorcRPos[3],
    Float:DooroPos[3],
    Float:DooroRPos[3],
    Float:DoorSpeed,
    STREAMER_TAG_OBJECT:DoorObjectID,
    STREAMER_TAG_OBJECT:ButtonObjectID,
    DoorModelID,
    bWorld,
    bInterior,
    bool: DoorStatus
}
new ButtonData[MAX_DYNAMIC_BUTTON][e_buttondata],
    Iterator:Buttons<MAX_DYNAMIC_BUTTON>;

new 
    Float:EditPosition[MAX_PLAYERS][3],
    Float:EditRPosition[MAX_PLAYERS][3];

Button_Rebuild(id)
{
    if(id != -1)
    {
        if(DestroyDynamicObject(ButtonData[id][DoorObjectID]))
            ButtonData[id][DoorObjectID] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;

        if(DestroyDynamicObject(ButtonData[id][ButtonObjectID]))
            ButtonData[id][ButtonObjectID] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        if(ButtonData[id][ButtonPos][0] != 0.0 || ButtonData[id][ButtonRPos][0] != 0.0)
        {
            ButtonData[id][ButtonObjectID] = CreateDynamicObject(2886, ButtonData[id][ButtonPos][0], ButtonData[id][ButtonPos][1], ButtonData[id][ButtonPos][2], ButtonData[id][ButtonRPos][0], ButtonData[id][ButtonRPos][1], ButtonData[id][ButtonRPos][2], ButtonData[id][bWorld], ButtonData[id][bInterior], -1);
        }
        if(ButtonData[id][DoorcPos][0] != 0.0 || ButtonData[id][DooroPos][0] != 0.0)
        {
            ButtonData[id][DoorObjectID] = CreateDynamicObject(ButtonData[id][DoorModelID], ButtonData[id][DoorcPos][0], ButtonData[id][DoorcPos][1], ButtonData[id][DoorcPos][2], ButtonData[id][DoorcRPos][0], ButtonData[id][DoorcRPos][1], ButtonData[id][DoorcRPos][2], ButtonData[id][bWorld], ButtonData[id][bInterior], -1);
        }
    }
    return 1;
}

Button_Save(id)
{
    new query[1218];
    mysql_format(g_SQL, query, sizeof(query), "UPDATE `buttons` SET `DoorModel`=%d, `Faction`=%d, `Faction2`=%d, `Family`=%d, `Owner`=%d, `Speed`=%f, `ButtonX`=%f, `ButtonY`=%f, `ButtonZ`=%f, `ButtonRX`=%f, `ButtonRY`=%f, `ButtonRZ`=%f,\
    `DoorCX`=%f, `DoorCY`=%f, `DoorCZ`=%f, `DoorCRX`=%f, `DoorCRY`=%f, `DoorCRZ`=%f, `DoorOX`=%f, `DoorOY`=%f, `DoorOZ`=%f, `DoorORX`=%f, `DoorORY`=%f, `DoorORZ`=%f, `World`=%d, `Interior`=%d WHERE `ID`=%d",
    ButtonData[id][DoorModelID], ButtonData[id][bFactionID], ButtonData[id][bFaction2ID], ButtonData[id][bFamilyID], ButtonData[id][bOwnerID], ButtonData[id][DoorSpeed], ButtonData[id][ButtonPos][0], ButtonData[id][ButtonPos][1], ButtonData[id][ButtonPos][2], ButtonData[id][ButtonRPos][0], ButtonData[id][ButtonRPos][1], ButtonData[id][ButtonRPos][2],
    ButtonData[id][DoorcPos][0], ButtonData[id][DoorcPos][1], ButtonData[id][DoorcPos][2], ButtonData[id][DoorcRPos][0], ButtonData[id][DoorcRPos][1], ButtonData[id][DoorcRPos][2], ButtonData[id][DooroPos][0], ButtonData[id][DooroPos][1], ButtonData[id][DooroPos][2], ButtonData[id][DooroRPos][0], ButtonData[id][DooroRPos][1], ButtonData[id][DooroRPos][2],
    ButtonData[id][bWorld], ButtonData[id][bInterior], id);
    mysql_tquery(g_SQL, query);
    return 1;
}

forward LoadButtons();
public LoadButtons()
{
    new id, rows = cache_num_rows();
    new Cache:btnCache; // Cache ID untuk delete nanti

    if(rows)
    {
        btnCache = cache_save(); 

        for(new i = 0; i < rows; i ++)
        {
            cache_get_value_name_int(i, "ID", id);
            cache_get_value_name_int(i, "Faction", ButtonData[id][bFactionID]);
            cache_get_value_name_int(i, "Faction2", ButtonData[id][bFaction2ID]);
            cache_get_value_name_int(i, "Family", ButtonData[id][bFamilyID]);
            cache_get_value_name_int(i, "Owner", ButtonData[id][bOwnerID]);
            cache_get_value_name_int(i, "DoorModel", ButtonData[id][DoorModelID]);
            cache_get_value_name_int(i, "World", ButtonData[id][bWorld]);
            cache_get_value_name_int(i, "Interior", ButtonData[id][bInterior]);

            cache_get_value_name_float(i, "Speed", ButtonData[id][DoorSpeed]);
            cache_get_value_name_float(i, "ButtonX", ButtonData[id][ButtonPos][0]);
            cache_get_value_name_float(i, "ButtonY", ButtonData[id][ButtonPos][1]);
            cache_get_value_name_float(i, "ButtonZ", ButtonData[id][ButtonPos][2]);
            cache_get_value_name_float(i, "ButtonRX", ButtonData[id][ButtonRPos][0]);
            cache_get_value_name_float(i, "ButtonRY", ButtonData[id][ButtonRPos][1]);
            cache_get_value_name_float(i, "ButtonRZ", ButtonData[id][ButtonRPos][2]);

            cache_get_value_name_float(i, "DoorCX", ButtonData[id][DoorcPos][0]);
            cache_get_value_name_float(i, "DoorCY", ButtonData[id][DoorcPos][1]);
            cache_get_value_name_float(i, "DoorCZ", ButtonData[id][DoorcPos][2]);
            cache_get_value_name_float(i, "DoorCRX", ButtonData[id][DoorcRPos][0]);
            cache_get_value_name_float(i, "DoorCRY", ButtonData[id][DoorcRPos][1]);
            cache_get_value_name_float(i, "DoorCRZ", ButtonData[id][DoorcRPos][2]);
            
            cache_get_value_name_float(i, "DoorOX", ButtonData[id][DooroPos][0]);
            cache_get_value_name_float(i, "DoorOY", ButtonData[id][DooroPos][1]);
            cache_get_value_name_float(i, "DoorOZ", ButtonData[id][DooroPos][2]);
            cache_get_value_name_float(i, "DoorORX", ButtonData[id][DooroRPos][0]);
            cache_get_value_name_float(i, "DoorORY", ButtonData[id][DooroRPos][1]);
            cache_get_value_name_float(i, "DoorORZ", ButtonData[id][DooroRPos][2]);

            Iter_Add(Buttons, id);
            Button_Rebuild(id);
        }
        printf("[Dynamic Buttons]: Jumlah total Dynamic Button yang dimuat %d", rows);
        if(cache_is_valid(btnCache))
        {
            cache_delete(btnCache);
            printf("[Dynamic Buttons]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Buttons]: Cache tidak valid atau sudah dihapus.");
        }
    }
}

FUNC::OnButtonCreated(playerid, id)
{
    Button_Save(id);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah membuat Dynamic Buttons ID: %d", AccountData[playerid][pAdminname], id);
    return 1;
}

CMD:addbutton(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 4) return PermissionError(playerid);

    new id = Iter_Free(Buttons);
    if(id == -1) return Error(playerid, "Anda tidak dapat menambahkan Dynamic Button lagi!"); //ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menambah button lagi!");

    GetPlayerPos(playerid, ButtonData[id][ButtonPos][0], ButtonData[id][ButtonPos][1], ButtonData[id][ButtonPos][2]);
    ButtonData[id][ButtonPos][0] = ButtonData[id][ButtonPos][0] + 2;
    ButtonData[id][ButtonPos][1] = ButtonData[id][ButtonPos][1] + 2;
    ButtonData[id][ButtonRPos][0] = 0.0;
    ButtonData[id][ButtonRPos][1] = 0.0;
    ButtonData[id][ButtonRPos][2] = 0.0;
    ButtonData[id][bFactionID] = FACTION_NONE;
    ButtonData[id][bFaction2ID] = FACTION_NONE;
    ButtonData[id][bFamilyID] = -1;
    ButtonData[id][bOwnerID] = -1;
    ButtonData[id][DoorStatus] = false;
    ButtonData[id][bWorld] = GetPlayerVirtualWorld(playerid);
    ButtonData[id][bInterior] = GetPlayerInterior(playerid);

    Button_Rebuild(id);
    Iter_Add(Buttons, id);

    new query[596];
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `buttons` SET `ID`=%d, `ButtonX`=%f, `ButtonY`=%f, `ButtonZ`=%f, `ButtonRX`=%f, `ButtonRY`=%f, `ButtonRZ`=%f, `Faction`=0, `Faction2`=0, `Family`=-1, `World`=%d, `Interior`=%d",
    id, ButtonData[id][ButtonPos][0], ButtonData[id][ButtonPos][1], ButtonData[id][ButtonPos][2], ButtonData[id][ButtonRPos][0], ButtonData[id][ButtonRPos][1], ButtonData[id][ButtonRPos][2], ButtonData[id][bWorld], ButtonData[id][bInterior]);
    mysql_tquery(g_SQL, query, "OnButtonCreated", "dd", playerid, id);
    return 1;
}

CMD:gotobutton(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1) return PermissionError(playerid);

    new id;
    if(id < 0 || id >= MAX_DYNAMIC_BUTTON) return Error(playerid, "ID Button tidak valid!"); //ShowTDN(playerid, NOTIFICATION_ERROR, "ID Button tidak valid!");
    if(sscanf(params, "d", id)) return Syntax(playerid, "/gotobutton [button id]"); //ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotobutton [id]");
    if(!Iter_Contains(Buttons, id)) return Error(playerid, "ID Button tidak ada!"); //ShowTDN(playerid, NOTIFICATION_ERROR, "ID Button tidak ada!");

    SetPlayerPos(playerid, ButtonData[id][ButtonPos][0], ButtonData[id][ButtonPos][1], ButtonData[id][ButtonPos][2]);
    SetPlayerVirtualWorldEx(playerid, ButtonData[id][bWorld]);
    SetPlayerInteriorEx(playerid, ButtonData[id][bInterior]);
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInDoor] = -1;
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Teleportasi ke Dynamic Button ID: %d", AccountData[playerid][pAdminname], id);
    return 1;
}

CMD:editbutton(playerid, params[])
{
    static 
        id,
        type[24],
        string[128];
    
    if(AccountData[playerid][pAdmin] < 4) return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", id, type, string))
    {
        Syntax(playerid, "/editbutton [id] [name] (doormodel, buttonpos, faction, family, close, open, speed)");
        return 1;
    }
    if((id < 0 || id >= MAX_DYNAMIC_BUTTON)) return Error(playerid, "ID Button tidak valid!"); //ShowTDN(playerid, NOTIFICATION_ERROR, "ID Button tidak valid!");
    if(!Iter_Contains(Buttons, id)) return Error(playerid, "ID Button tidak ada!"); //ShowTDN(playerid, NOTIFICATION_ERROR, "ID Button tidak ada!");

    if(!strcmp(type, "doormodel", true))
    {
        new objid;

        if(sscanf(string, "d", objid)) return Syntax(playerid, "/editbutton [id] [doormodel] [model id]"); //ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editbutton [id] [doormodel] [model id]");
        GetPlayerPos(playerid, ButtonData[id][DoorcPos][0], ButtonData[id][DoorcPos][1], ButtonData[id][DoorcPos][2]);
        ButtonData[id][DoorModelID] = objid;
        ButtonData[id][DoorcPos][0] = ButtonData[id][DoorcPos][0] + 2;
        ButtonData[id][DoorcPos][1] = ButtonData[id][DoorcPos][1] + 2;
        Button_Rebuild(id);
        Button_Save(id);
    }
    else if(!strcmp(type, "faction", true))
    {
        new fid;
        
        if(sscanf(string, "d", fid)) return Syntax(playerid, "/editbutton [id] [faction] [faction id] (1.POLDA, 2.Pemerintah, 3.EMS, 4.NOTHING, 5.Bengkel, 6.Pedagang, 7.Gojek)");
        
        if(fid < 0 || fid > 7) return Error(playerid, "ID Faction tidak valid!"); //ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Faction ID!");

        ButtonData[id][bFactionID] = fid;
        Success(playerid, "Anda menetapkan Button ID: %d untuk Faction ID: %d", id, fid);
        Button_Save(id);
    }
    else if(!strcmp(type, "faction2", true))
    {
        new fid;
        
        if(sscanf(string, "d", fid)) return Syntax(playerid, "/editbutton [id] [faction] [faction id] (1.POLDA, 2.Pemerintah, 3.EMS, 4.NOTHING, 5.Bengkel, 6.Pedagang, 7.Gojek)");
        
        if(fid < 0 || fid > 7) return Error(playerid, "ID Faction tidak valid!"); //ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Faction ID!");

        ButtonData[id][bFaction2ID] = fid;
        Success(playerid, "Anda menetapkan Button ID: %d untuk Faction ID: %d", id, fid);
        Button_Save(id);
    }
    else if(!strcmp(type, "family", true))
    {
        new fid;
        
        if(sscanf(string, "d", fid)) return Syntax(playerid, "/editbutton [id] [family] [family id] (Use: -1 untuk None)");
        
        if(fid < -1) return Error(playerid, "ID Family tidak valid!"); //ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Family ID!");

        ButtonData[id][bFamilyID] = fid;
        Success(playerid, "Anda menetapkan Button ID: %d untuk Family ID: %d", id, fid);
        Button_Save(id);
    }
    else if(!strcmp(type, "owner", true))
    {
        new otherid;
        if(sscanf(string, "u", otherid)) return Syntax(playerid, "/editbutton [id] [owner] [name/playerid] (Use: -1 untuk none)");
        if(!IsPlayerConnected(otherid)) return Error(playerid, "Pemain tersebut tidak terkoneksi ke server!");

        ButtonData[id][bOwnerID] = AccountData[otherid][pID];
        Info(playerid, "Anda menetapkan Button ID: %d menjadi milik %s(%d)", id, AccountData[otherid][pName], otherid);
        Button_Save(id);
    }
    else if(!strcmp(type, "speed", true))
    {
        new Float:speed;

        if(sscanf(string, "f", speed)) return Syntax(playerid, "/editbutton [id] [speed] [level]");

        ButtonData[id][DoorSpeed] = speed;
        Success(playerid, "Anda menetapkan Button ID: %d dengan speed %.1f", id, speed);
        Button_Save(id);
    }
    else if(!strcmp(type, "buttonpos", true))
    {
        AccountData[playerid][bEdit] = 1; // Edit Button
        AccountData[playerid][bEditID] = id;
        GetDynamicObjectPos(ButtonData[id][ButtonObjectID], EditPosition[playerid][0], EditPosition[playerid][1], EditPosition[playerid][2]);
        GetDynamicObjectRot(ButtonData[id][ButtonObjectID], EditRPosition[playerid][0], EditRPosition[playerid][1], EditRPosition[playerid][2]);
        EditDynamicObject(playerid, ButtonData[id][ButtonObjectID]);
        Info(playerid, "Anda sekarang sedang dalam mode pengeditan Button ID %d", id);
    }
    else if(!strcmp(type, "close", true))
    {
        AccountData[playerid][bEdit] = 2;// close edit door
        AccountData[playerid][bEditID] = id;
        GetDynamicObjectPos(ButtonData[id][DoorObjectID], EditPosition[playerid][0], EditPosition[playerid][1], EditPosition[playerid][2]);
        GetDynamicObjectRot(ButtonData[id][DoorObjectID], EditRPosition[playerid][0], EditRPosition[playerid][1], EditRPosition[playerid][2]);
        EditDynamicObject(playerid, ButtonData[id][DoorObjectID]);
        Info(playerid, "Anda sekarang sedang dalam mode pengeditan Button Door ID %d Close Position", id);
    }
    else if(!strcmp(type, "open", true))
    {
        AccountData[playerid][bEdit] = 3;// open edit door
        AccountData[playerid][bEditID] = id;
        GetDynamicObjectPos(ButtonData[id][DoorObjectID], EditPosition[playerid][0], EditPosition[playerid][1], EditPosition[playerid][2]);
        GetDynamicObjectRot(ButtonData[id][DoorObjectID], EditRPosition[playerid][0], EditRPosition[playerid][1], EditRPosition[playerid][2]);
        EditDynamicObject(playerid, ButtonData[id][DoorObjectID]);
        Info(playerid, "Anda sekarang sedang dalam mode pengeditan Button Door ID %d Open Position", id);
    }
    return 1;
}

CMD:removebutton(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 4) return PermissionError(playerid);

    new id;
    if(id < 0 || id >= MAX_DYNAMIC_BUTTON) return Error(playerid, "ID Button tidak valid!"); //ShowTDN(playerid, NOTIFICATION_ERROR, "ID Button tidak valid!");
    if(sscanf(params, "d", id)) return Syntax(playerid, "/removebutton [button id]"); //ShowTDN(playerid, NOTIFICATION_SYNTAX, "/removebutton [id button]");
    if(!Iter_Contains(Buttons, id)) return Error(playerid, "ID Button tidak ada!"); //ShowTDN(playerid, NOTIFICATION_ERROR, "ID Button tidak ada!");

    if(DestroyDynamicObject(ButtonData[id][ButtonObjectID]))
        ButtonData[id][ButtonObjectID] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
    if(DestroyDynamicObject(ButtonData[id][DoorObjectID]))
        ButtonData[id][DoorObjectID] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
    
    ButtonData[id][DoorModelID] = 0;
    ButtonData[id][bFactionID] = 0;
    ButtonData[id][bFamilyID] = -1;
    ButtonData[id][bOwnerID] = -1;
    ButtonData[id][DoorStatus] = false;
    ButtonData[id][ButtonPos][0] = ButtonData[id][ButtonPos][1] = ButtonData[id][ButtonPos][2] = 0.0;
    ButtonData[id][ButtonRPos][0] = ButtonData[id][ButtonRPos][1] = ButtonData[id][ButtonRPos][2] = 0.0;
    ButtonData[id][DoorcPos][0] = ButtonData[id][DoorcPos][1] = ButtonData[id][DoorcPos][2] = 0.0;
    ButtonData[id][DoorcRPos][0] = ButtonData[id][DoorcRPos][1] = ButtonData[id][DoorcRPos][2] = 0.0;
    ButtonData[id][DooroPos][0] = ButtonData[id][DooroPos][1] = ButtonData[id][DooroPos][2] = 0.0;
    ButtonData[id][DooroRPos][0] = ButtonData[id][DooroRPos][1] = ButtonData[id][DooroRPos][2] = 0.0;

    Success(playerid, "Berhasil menghapus Dynamic Button ID: %d", id);
    Iter_Remove(Buttons, id);

    new query[255];
    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `buttons` WHERE `ID`=%d", id);
    mysql_tquery(g_SQL, query);

    AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), sprintf("Menghapus Dynamic Button ID: %d", id));
    return 1;
}

forward PressButtonDelay(playerid, buttonid);
public PressButtonDelay(playerid, buttonid)
{
    #if defined SOUND
        PlayerPlayNearbySound(playerid, SOUND); 
    #endif
    CallLocalFunction("PressButon", "ii", playerid, buttonid);
    return 1;
}

forward PressButon(playerid, buttonid);
public PressButon(playerid, buttonid)
{
    PlayerPlayNearbySound(playerid, SOUND);

    if(ButtonData[buttonid][bFactionID] > FACTION_NONE || ButtonData[buttonid][bFaction2ID] > FACTION_NONE)
    {
        if(ButtonData[buttonid][bFactionID] != AccountData[playerid][pFaction] && ButtonData[buttonid][bFaction2ID] != AccountData[playerid][pFaction]) 
            return Error(playerid, "Pintu ini khusus anggota salah satu Faction!"); //ShowTDN(playerid, NOTIFICATION_ERROR, "Pintu ini khusus anggota salah satu Faction!");
    }
    if(ButtonData[buttonid][bFamilyID] > -1)
    {
        if(ButtonData[buttonid][bFamilyID] != AccountData[playerid][pFamily])
            return Error(playerid, "Pintu ini khusus anggota salah satu Families!"); //ShowTDN(playerid, NOTIFICATION_ERROR, "Pintu ini khusus anggota salah satu Families!");
    }
    if(ButtonData[buttonid][bOwnerID] > -1)
    {
        if(ButtonData[buttonid][bOwnerID] != AccountData[playerid][pID])
            return Error(playerid, "Pintu ini khusus pemiliknya!");
    }

    if(!ButtonData[buttonid][DoorStatus])
    {
        ButtonData[buttonid][DoorStatus] = true;
        MoveDynamicObject(ButtonData[buttonid][DoorObjectID], ButtonData[buttonid][DooroPos][0], ButtonData[buttonid][DooroPos][1], ButtonData[buttonid][DooroPos][2], ButtonData[buttonid][DoorSpeed]);
        SetDynamicObjectRot(ButtonData[buttonid][DoorObjectID], ButtonData[buttonid][DooroRPos][0], ButtonData[buttonid][DooroRPos][1], ButtonData[buttonid][DooroRPos][2]);
    }
    else
    {
        ButtonData[buttonid][DoorStatus] = false;
        MoveDynamicObject(ButtonData[buttonid][DoorObjectID], ButtonData[buttonid][DoorcPos][0], ButtonData[buttonid][DoorcPos][1], ButtonData[buttonid][DoorcPos][2], ButtonData[buttonid][DoorSpeed]);
        SetDynamicObjectRot(ButtonData[buttonid][DoorObjectID], ButtonData[buttonid][DoorcRPos][0], ButtonData[buttonid][DoorcRPos][1], ButtonData[buttonid][DoorcRPos][2]);
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_SECONDARY_ATTACK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        foreach(new id : Buttons)
        {
            if(ButtonData[id][DoorModelID] && IsPlayerInRangeOfPoint(playerid, 1.3, ButtonData[id][ButtonPos][0], ButtonData[id][ButtonPos][1], ButtonData[id][ButtonPos][2]))
            {
                SetPlayerFace(playerid, ButtonData[id][ButtonPos][0], ButtonData[id][ButtonPos][1]);
                ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 10.0, 0, 0, 0, 0, 0);
                SetTimerEx("PressButtonDelay", 500, false, "dd", playerid, id);
                // SetPlayerPos(playerid, ButtonData[id][ButtonPos][0], ButtonData[id][ButtonPos][1] - 0.65, ButtonData[id][ButtonPos][2] - 0.63);
            }
        }
    }
    return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT:objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    if(AccountData[playerid][bEditID] != -1 && Iter_Contains(Buttons, AccountData[playerid][bEditID]))
    {
        new id = AccountData[playerid][bEditID];
        if(response == EDIT_RESPONSE_UPDATE)
        {
            SetDynamicObjectPos(objectid, x, y, z);
            SetDynamicObjectRot(objectid, rx, ry, rz);
        }
        else if(response == EDIT_RESPONSE_CANCEL)
        {
            SetDynamicObjectPos(objectid, EditPosition[playerid][0], EditPosition[playerid][1], EditPosition[playerid][2]);
            SetDynamicObjectRot(objectid, EditRPosition[playerid][0], EditRPosition[playerid][1], EditRPosition[playerid][2]);
            EditPosition[playerid][0] = EditPosition[playerid][1] = EditPosition[playerid][2] = 0.0;
            EditRPosition[playerid][0] = EditRPosition[playerid][1] = EditRPosition[playerid][2] = 0.0;
            Info(playerid, "Anda membatalkan pengeditan Button ID %d", id);

            AccountData[playerid][bEditID] = -1;
            AccountData[playerid][bEdit] = 0;
            Button_Save(id);
        }
        else if(response == EDIT_RESPONSE_FINAL)
        {
            SetDynamicObjectPos(objectid, x, y, z);
            SetDynamicObjectRot(objectid, rx, ry, rz);
            if(AccountData[playerid][bEdit] == 1) // Button
            {
                ButtonData[id][ButtonPos][0] = x;
                ButtonData[id][ButtonPos][1] = y;
                ButtonData[id][ButtonPos][2] = z;
                ButtonData[id][ButtonRPos][0] = rx;
                ButtonData[id][ButtonRPos][1] = ry;
                ButtonData[id][ButtonRPos][2] = rz;
                Button_Rebuild(id);

                AccountData[playerid][bEditID] = -1;
                AccountData[playerid][bEdit] = 0;
                Success(playerid, "Berhasil Mengedit Posisi Button ID: %d", id);
                ButtonData[id][DoorStatus] = false;
                Button_Save(id);
            }
            else if(AccountData[playerid][bEdit] == 2) // close
            {
                ButtonData[id][DoorcPos][0] = x;
                ButtonData[id][DoorcPos][1] = y;
                ButtonData[id][DoorcPos][2] = z;
                ButtonData[id][DoorcRPos][0] = rx;
                ButtonData[id][DoorcRPos][1] = ry;
                ButtonData[id][DoorcRPos][2] = rz;
                Button_Rebuild(id);

                AccountData[playerid][bEditID] = -1;
                AccountData[playerid][bEdit] = 0;
                Success(playerid, "Berhasil Mengedit Posisi Tertutup Button Door ID: %d", id);
                ButtonData[id][DoorStatus] = false;
                Button_Save(id);
            }
            else if(AccountData[playerid][bEdit] == 3) // open
            {
                ButtonData[id][DooroPos][0] = x;
                ButtonData[id][DooroPos][1] = y;
                ButtonData[id][DooroPos][2] = z;
                ButtonData[id][DooroRPos][0] = rx;
                ButtonData[id][DooroRPos][1] = ry;
                ButtonData[id][DooroRPos][2] = rz;
                Button_Rebuild(id);

                AccountData[playerid][bEditID] = -1;
                AccountData[playerid][bEdit] = 0;
                Success(playerid, "Berhasil Mengedit Posisi Terbuka Button Door ID: %d", id);
                ButtonData[id][DoorStatus] = false;
                Button_Save(id);
            }
        }
    }
    return 1;
}