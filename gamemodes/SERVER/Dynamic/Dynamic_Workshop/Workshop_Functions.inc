#include <YSI\y_hooks>

//saya matikan karna ini ada di gps
/*GetAnyWs()
{
    new tmpcount;
    foreach(new id : Workshop)
    {
        tmpcount++;
    }
    return tmpcount;
}

ReturnWSID(slot)
{
    new tmpcount;
    if(slot < 1 && slot > MAX_WORKSHOP) return -1;
    foreach(new id : Workshop)
    {
        tmpcount++;
        if(tmpcount == slot)
        {
            return id;
        }
    }
    return -1;
}*/

Workshop_Reset(id)
{
    foreach(new i : Player) if(AccountData[i][pWorkshop] != -1) AccountData[i][pWorkshop] = -1;
    format(wsData[id][wOwner], MAX_PLAYER_NAME, "-");
    format(wsEmploy[id][0], MAX_PLAYER_NAME, "-");
    format(wsEmploy[id][1], MAX_PLAYER_NAME, "-");
    format(wsEmploy[id][2], MAX_PLAYER_NAME, "-");
    format(wsEmploy[id][3], MAX_PLAYER_NAME, "-");
    wsData[id][wComp] = 500000;
    wsData[id][wMoney] = 0;
    for(new z = 0; z < MAX_WORKSHOP_EMPLOYEE; z++)
    {
        format(wsEmploy[id][z], MAX_PLAYER_NAME, "-");
    }
    Workshop_Refresh(id);
}


Workshop_Refresh(id)
{
    if(id != -1)
    {
        if(IsValidDynamic3DTextLabel(wsData[id][wText]))
            DestroyDynamic3DTextLabel(wsData[id][wText]);

        if(IsValidDynamicPickup(wsData[id][wPickup]))
            DestroyDynamicPickup(wsData[id][wPickup]);

        new str[316], stats[64];
        if(wsData[id][wStatus] == 1)
        {
            stats = "{7fff00}OPEN{ffffff}";
        }
        else
        {
            stats = "{ff0000}CLOSED{ffffff}";
        }

        format(str, sizeof str,"[Workshop ID:%d]\n{ffffff}Vip Member Only Can Buy This Workshop", id);

        if(strcmp(wsData[id][wOwner], "-", true))
            format(str, sizeof str,"[Workshop ID:%d]\n{ffffff}Workshop Name: %s\n{ffffff}Workshop Owner: %s\n{ffffff}STATUS: %s", id, wsData[id][wName], wsData[id][wOwner], stats);

        wsData[id][wText] = CreateDynamic3DTextLabel(str, ARWIN, wsData[id][wX], wsData[id][wY], wsData[id][wZ]+0.5, 8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, -1, 8.0);
        wsData[id][wPickup] = CreateDynamicPickup(1239, 23, wsData[id][wX], wsData[id][wY], wsData[id][wZ]+0.2, 0, 0, _, 50.0);
    }
}

function LoadWorkshop()
{
    static wid;
    
    new rows = cache_num_rows(), owner[128], name[128];
    if(rows)
    {
        for(new i; i < rows; i++)
        {
            cache_get_value_name_int(i, "id", wid);
            cache_get_value_name(i, "owner", owner);
            format(wsData[wid][wOwner], 128, owner);
            cache_get_value_name(i, "name", name);
            format(wsData[wid][wName], 128, name);
            cache_get_value_name_float(i, "posx", wsData[wid][wX]);
            cache_get_value_name_float(i, "posy", wsData[wid][wY]);
            cache_get_value_name_float(i, "posz", wsData[wid][wZ]);
            cache_get_value_name_int(i, "component", wsData[wid][wComp]);
            cache_get_value_name_int(i, "money", wsData[wid][wMoney]);
            for(new z = 0; z < MAX_WORKSHOP_EMPLOYEE; z++)
            {
                new str[64];
                format(str, sizeof str,"employe%d", z);
                cache_get_value_name(i, str, wsEmploy[wid][z]);
            }
            Workshop_Refresh(wid);
            Iter_Add(Workshop, wid);
        }
        printf("[Workshops] %d Loaded.", rows);
    }
}

Workshop_Save(id)
{
    new query[2248];
    format(query, sizeof query,"UPDATE workshop SET owner='%s', name='%s', component=%d, money=%d, posx='%f', posy='%f', posz='%f', status=%d",
        wsData[id][wOwner],
        wsData[id][wName],
        wsData[id][wComp],
        wsData[id][wMoney],
        wsData[id][wX],
        wsData[id][wY],
        wsData[id][wZ],
        wsData[id][wStatus]);
    for(new z = 0; z < MAX_WORKSHOP_EMPLOYEE; z++)
    {
        format(query, sizeof query,"%s, employe%d='%s'", query, z, wsEmploy[id][z]);
    }
    format(query, sizeof query,"%s WHERE id = %d", query, id);
    return mysql_tquery(g_SQL, query);
}


function OnWorkshopCreated(wid)
{
    Workshop_Save(wid);
    Workshop_Refresh(wid);
    return 1;
}

ShowWorkshopMenu(playerid, id)
{
    new str[256], vstr[64], StatusLocked[30];
    if(wsData[id][wStatus] == 1)
    {
        StatusLocked = "{FFFF00}OPEN{FFFFFF}";
    }
    else
    {
        StatusLocked = "{FF0000}CLOSE{FFFFFF}";
    }
    format(vstr, sizeof vstr,"Workshop (%s) Menu", wsData[id][wName]);
    format(str, sizeof str,"Set Workshop Name\nStatus: %s\nEmploye Menu\nComponent\t(%d/%d)\nMoney\t({7fff00}%s{ffffff})",
        StatusLocked,
        wsData[id][wComp],
        MAX_WORKSHOP_INT,
        FormatMoney(wsData[id][wMoney]));
    ShowPlayerDialog(playerid, WORKSHOP_MENU, DIALOG_STYLE_LIST, vstr, str, "Select", "Cancel");
    return 1;
}

GetOwnedWorkshop(playerid)
{
    new tmpcount;
    foreach(new wid : Workshop)
    {
        if(!strcmp(wsData[wid][wOwner], AccountData[playerid][pName], true))
        {
            tmpcount++;
        }
    }
    return tmpcount;
}

ReturnPlayerWorkshopID(playerid, hslot)
{
    new tmpcount;
    if(hslot < 1 && hslot > LIMIT_PER_PLAYER) return -1;
    foreach(new wid : Workshop)
    {
        if(!strcmp(AccountData[playerid][pName], wsData[wid][wOwner], true))
        {
            tmpcount++;
            if(tmpcount == hslot)
            {
                return wid;
            }
        }
    }
    return -1;
}
CMD:wcreate(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);
    
    new query[512];
    new wid = Iter_Free(Workshop);
    if(wid == -1) return ShowTDN(playerid, NOTIFICATION_INFO, "You cant create more workshop!");

    format(wsData[wid][wOwner], MAX_PLAYER_NAME, "-");
    format(wsEmploy[wid][0], MAX_PLAYER_NAME, "-");
    format(wsEmploy[wid][1], MAX_PLAYER_NAME, "-");
    format(wsEmploy[wid][2], MAX_PLAYER_NAME, "-");
    format(wsData[wid][wName], 24, "-");
    GetPlayerPos(playerid, wsData[wid][wX], wsData[wid][wY], wsData[wid][wZ]);
    wsData[wid][wStatus] = 0;

    Iter_Add(Workshop, wid);

    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO workshop SET id=%d, owner='%s', posx='%f', posy='%f', posz='%f', name='%s'", wid, wsData[wid][wOwner], wsData[wid][wX], wsData[wid][wY], wsData[wid][wZ], wsData[wid][wName]);
    mysql_tquery(g_SQL, query, "OnWorkshopCreated", "i", wid);
    Info(playerid, "Created Workshop ID:%d", wid);
    return 1;
}

CMD:wgoto(playerid, params[])
{
    new wid;
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);
        
    if(sscanf(params, "d", wid))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wgoto [id]");
    if(!Iter_Contains(Workshop, wid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "The Workshop you specified ID of doesn't exist.");
    SetPlayerPos(playerid, wsData[wid][wX], wsData[wid][wY], wsData[wid][wZ]);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;   
    Info(playerid, "You has teleport to Workshop id %d", wid);
    return 1;
}

CMD:wedit(playerid, params[])
{
    static
        wid,
        type[24],
        string[128];

    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", wid, type, string))
    {
        ShowTDN(playerid, NOTIFICATION_SYNTAX, "/wedit [id] [name]");
        SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} location, status, owner, money, component");
        return 1;
    }
    if((wid < 0 || wid >= MAX_WORKSHOP))
        return Error(playerid, "You have specified an invalid ID.");
    if(!Iter_Contains(Workshop, wid)) return Error(playerid, "The Workshop you specified ID of doesn't exist.");

    if(!strcmp(type, "location", true))
    {
        GetPlayerPos(playerid, wsData[wid][wX], wsData[wid][wY], wsData[wid][wZ]);
        Workshop_Save(wid);
        Workshop_Refresh(wid);

        SendAdminMessage(COLOR_RED, "%s has adjusted the location of Workshop ID: %d.", AccountData[playerid][pAdminname], wid);
    }
    else if(!strcmp(type, "status", true))
    {
        new locked;

        if(sscanf(string, "d", locked))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editws [id] [locked] [0/1]");

        if(locked < 0 || locked > 1)
            return Error(playerid, "You must specify at least 0 or 1.");

        wsData[wid][wStatus] = locked;
        Workshop_Save(wid);
        Workshop_Refresh(wid);

        if(locked) {
            SendAdminMessage(COLOR_RED, "%s has Opened Workshop ID: %d.", AccountData[playerid][pAdminname], wid);
        }
        else {
            SendAdminMessage(COLOR_RED, "%s has Closed Workshop ID: %d.", AccountData[playerid][pAdminname], wid);
        }
    }
    else if(!strcmp(type, "money", true))
    {
        new money;

        if(sscanf(string, "d", money))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editws [id] [money] [Ammount]");

        wsData[wid][wMoney] = money;
        Workshop_Save(wid);
        Workshop_Refresh(wid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the money of Workshop ID: %d to %s.", AccountData[playerid][pAdminname], wid, FormatMoney(money));
    }
    else if(!strcmp(type, "component", true))
    {
        new amount;

        if(sscanf(string, "d", amount))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editws [id] [Comp] [Ammount]");

        wsData[wid][wComp] = amount;
        Workshop_Save(wid);
        Workshop_Refresh(wid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the component of Workshop ID: %d to %d.", AccountData[playerid][pAdminname], wid, amount);
    }
    else if(!strcmp(type, "owner", true))
    {
        new otherid;
        if(sscanf(string, "d", otherid))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editws [id] [owner] [playerid] (use '-1' to no owner/ reset)");
        if(otherid == -1)
            return format(wsData[wid][wOwner], MAX_PLAYER_NAME, "-");

        format(wsData[wid][wOwner], MAX_PLAYER_NAME, AccountData[otherid][pName]);
        
        AccountData[otherid][pWorkshop] = wid;
        Workshop_Save(wid);
        Workshop_Refresh(wid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the owner of Workshop ID: %d to %s", AccountData[playerid][pAdminname], wid, AccountData[otherid][pName]);
    }
    else if(!strcmp(type, "reset", true))
    {
        Workshop_Reset(wid);
        Workshop_Save(wid);
        Workshop_Refresh(wid);
        SendAdminMessage(COLOR_RED, "%s has reset Workshop ID: %d.", AccountData[playerid][pAdminname], wid);
    }
    else if(!strcmp(type, "delete", true))
    {
        Workshop_Reset(wid);
        
        DestroyDynamic3DTextLabel(wsData[wid][wText]);
        DestroyDynamicPickup(wsData[wid][wPickup]);
        
        wsData[wid][wX] = 0;
        wsData[wid][wY] = 0;
        wsData[wid][wZ] = 0;
        wsData[wid][wText] = Text3D: INVALID_3DTEXT_ID;
        wsData[wid][wPickup] = -1;
        
        Iter_Remove(Workshop, wid);
        new query[128];
        mysql_format(g_SQL, query, sizeof(query), "DELETE FROM workshop WHERE ID=%d", wid);
        mysql_tquery(g_SQL, query);
        SendAdminMessage(COLOR_RED, "%s has delete Workshop ID: %d.", AccountData[playerid][pAdminname], wid);
    }
    return 1;
}

CMD:myws(playerid)
{
    if(!GetOwnedWorkshop(playerid)) return Error(playerid, "You don't have any Workshop.");
    new wid, _tmpstring[128], count = GetOwnedWorkshop(playerid), CMDSString[512];
    CMDSString = "";
    new lock[128];
    strcat(CMDSString,"No\tName(Status)\tLocation\n",sizeof(CMDSString));
    Loop(itt, (count + 1), 1)
    {
        wid = ReturnPlayerWorkshopID(playerid, itt);
        if(wsData[wid][wStatus] == 1)
        {
            lock = "{7FFF00}Open{ffffff}";
        }
        else
        {
            lock = "{FF0000}Closed{ffffff}";
        }
        if(itt == count)
        {
            format(_tmpstring, sizeof(_tmpstring), "%d\t%s{ffffff}(%s)\t%s{ffffff}\n", itt, wsData[wid][wName], lock, GetLocation(wsData[wid][wX], wsData[wid][wY], wsData[wid][wZ]));
        }
        else format(_tmpstring, sizeof(_tmpstring), "%d\t%s{ffffff}(%s)\t%s{ffffff}\n", itt, wsData[wid][wName], lock, GetLocation(wsData[wid][wX], wsData[wid][wY], wsData[wid][wZ]));
        strcat(CMDSString, _tmpstring);
    }
    ShowPlayerDialog(playerid, WORKSHOP_INFO, DIALOG_STYLE_TABLIST_HEADERS, "My Workshop", CMDSString, "Track", "Cancel");
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if((newkeys & KEY_SECONDARY_ATTACK) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        foreach(new id : Workshop)
        {
            if(IsPlayerInRangeOfPoint(playerid, 4.0, wsData[id][wX], wsData[id][wY], wsData[id][wZ]))
            {
                if(!IsWorkshopOwner(playerid, id) && !IsWorkshopEmploye(playerid, id)) return 1;

                ShowPlayerDialog(playerid, LOCKER_WORKSHOP, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Workshop Menu",
                "Duty Mekanik\
                \n"GRAY"Informasi workshop", "Select", "Cancel");
            }
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case LOCKER_WORKSHOP:
        {
            if(!response) return 1;

            switch(listitem)
            {
                case 0:
                {
                    if(AccountData[playerid][pDutyBengkel] == 0)
                    {
                        AccountData[playerid][pDutyBengkel] = 1;

                        SetPlayerColor(playerid, COLOR_ORANGE);
                        if(AccountData[playerid][pGender] == 1)
                        {
                            SetPlayerSkin(playerid, 268);
                        }
                        else if(AccountData[playerid][pGender] == 2)
                        {
                            SetPlayerSkin(playerid, 157);
                        }
                        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah On dari Workshop!");
                    }
                    else
                    {
                        AccountData[playerid][pDutyBengkel] = 0;
                        SetPlayerColor(playerid, COLOR_WHITE);
                        SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
                        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah off dari Workshop!");
                    }
                }
                case 1:
                {
                    ShowWorkshopMenu(playerid, AccountData[playerid][pWorkshop]);
                }
            }
        }
        case WORKSHOP_NAME:
        {
            if(response)
            {
                new id = AccountData[playerid][pWorkshop];

                if(!IsWorkshopOwner(playerid, id))
                    return Error(playerid, "Only Workshop Owner who can use this");

                if(strlen(inputtext) > 24) 
                    return Error(playerid, "Maximal 24 Character");

                if(strfind(inputtext, "'", true) != -1)
                    return Error(playerid, "You can't put ' in Workshop Name");
                
                SendClientMessageEx(playerid, ARWIN, "WORKSHOP: {ffffff}You've successfully set Workshop Name from {ffff00}%s{ffffff} to {7fffd4}%s", wsData[id][wName], inputtext);
                format(wsData[id][wName], 24, inputtext);
                Workshop_Save(id);
                Workshop_Refresh(id);
            }
        }
        case WORKSHOP_MENU:
        {
            if(response)
            {
                new wid = AccountData[playerid][pWorkshop];
                switch(listitem)
                {
                    case 0:
                    {
                        if(!IsWorkshopOwner(playerid, wid))
                            return ShowTDN(playerid, NOTIFICATION_ERROR, "Only Workshop Owner who can use this");

                        new str[256];
                        format(str, sizeof str,"Current Workshop Name:\n%s\n\nInput new name to Change Workshop Name", wsData[wid][wName]);
                        ShowPlayerDialog(playerid, WORKSHOP_NAME, DIALOG_STYLE_INPUT, "Change Workshop Name", str,"Change","Cancel");
                    }
                    case 1:
                    {
                        if(IsPlayerInRangeOfPoint(playerid, 3.5, wsData[wid][wX], wsData[wid][wY], wsData[wid][wZ]))
                        {
                            if(!IsWorkshopOwner(playerid, wid) && !IsWorkshopEmploye(playerid, wid)) return Error(playerid, "Kamu bukan pengurus Workshop ini.");
                            if(!wsData[wid][wStatus])
                            {
                                wsData[wid][wStatus] = 1;
                                Workshop_Save(wid);
                                ShowWorkshopMenu(playerid, wid);

                                GameTextForPlayer(playerid, "Workshop anda berhasil ~g~Dibuka!", 2500, 6);
                                PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                wsData[wid][wStatus] = 0;
                                Workshop_Save(wid);
                                ShowWorkshopMenu(playerid, wid);

                                GameTextForPlayer(playerid,"Workshop anda berhasil ~r~Ditutup", 2500, 6);
                                PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
                            }
                            Workshop_Refresh(wid);
                        }
                        return 1;
                    }
                    case 2:
                    {
                        new str[556];
                        format(str, sizeof str,"Name\tRank\n(%s)\tOwner\n",wsData[wid][wOwner]);
                        for(new z = 0; z < MAX_WORKSHOP_EMPLOYEE; z++)
                        {
                            format(str, sizeof str,"%s(%s)\tEmploye\n", str, wsEmploy[wid][z]);
                        }
                        ShowPlayerDialog(playerid, WORKSHOP_SETEMPLOYE, DIALOG_STYLE_TABLIST_HEADERS, "Employe Menu", str, "Change","Cancel");
                    }
                    case 3:
                    {
                        ShowPlayerDialog(playerid, WORKSHOP_COMPONENT, DIALOG_STYLE_LIST, "Workshop Component", "Withdraw\nDeposit", "Select","Cancel");
                    }
                    case 4:
                    {
                        ShowPlayerDialog(playerid, WORKSHOP_MONEY, DIALOG_STYLE_LIST, "Workshop Money", "Withdraw\nDeposit", "Select","Cancel");
                    }
                }
            }
        }

        case WORKSHOP_MONEY:
        {
            if(response)
            {
                new str[264], id = AccountData[playerid][pWorkshop];
                switch(listitem)
                {
                    case 0:
                    {
                        if(!IsWorkshopOwner(playerid, id))
                            return Error(playerid, "Only Workshop Owner who can use this");

                        format(str, sizeof str, "Current Money:\n{7fff00}%s\n\n{ffffff}Input Amount to Withdraw", FormatMoney(wsData[id][wMoney]));
                        ShowPlayerDialog(playerid, WORKSHOP_WITHDRAWMONEY, DIALOG_STYLE_INPUT, "Withdraw Workshop Money",str,"Withdraw","Cancel");
                    }
                    case 1:
                    {
                        format(str, sizeof str, "Current Money:\n{7fff00}%s\n\n{ffffff}Input Amount to Deposit", FormatMoney(wsData[id][wMoney]));
                        ShowPlayerDialog(playerid, WORKSHOP_DEPOSITMONEY, DIALOG_STYLE_INPUT, "Deposit Workshop Money",str,"Deposit","Cancel");
                    }
                }
            }
        }

        case WORKSHOP_WITHDRAWMONEY:
        {
            if(response)
            {
                new amount = strval(inputtext), id = AccountData[playerid][pWorkshop];

                if(amount < 1)
                    return Error(playerid, "Minimum amount is $1");

                if(wsData[id][wMoney] < amount)
                    return Error(playerid, "Not Enough Workshop Money");

                GiveMoney(playerid, amount);
                wsData[id][wMoney] -= amount;
                Workshop_Save(id);
            }
        }

        case WORKSHOP_INFO:
        {
            if(!response) return 1;
            new id = ReturnPlayerWorkshopID(playerid, (listitem + 1));
            SetPlayerRaceCheckpoint(playerid,1, wsData[id][wX], wsData[id][wY], wsData[id][wZ], 0.0, 0.0, 0.0, 3.5);
            Info(playerid, "Ikuti checkpoint untuk menemukan farm anda!");
            AccountData[playerid][pGpsActive] = 1;
            
           // //(playerid, wsData[id][wX], wsData[id][wY], wsData[id][wZ], COLOR_BLUE);
            return 1;
        }

        case WORKSHOP_DEPOSITMONEY:
        {
            if(response)
            {
                new amount = strval(inputtext), id = AccountData[playerid][pWorkshop];
                
                if(amount < 1)
                    return Error(playerid, "Minimum amount is $1");

                if(AccountData[playerid][pMoney] < amount)
                    return Error(playerid, "Not Enough Money");

                GiveMoney(playerid, -amount);
                wsData[id][wMoney] += amount;
                Workshop_Save(id);
            }
        }

        case WORKSHOP_COMPONENT:
        {
            if(response)
            {
                new str[256], id = AccountData[playerid][pWorkshop];
                switch(listitem)
                {
                    case 0:
                    {
                        AccountData[playerid][pMenuType] = 1;
                        format(str, sizeof str,"Current Component: %d\n\nPlease Input amount to Withdraw", wsData[id][wComp]);
                    }
                    case 1:
                    {
                        AccountData[playerid][pMenuType] = 2;
                        format(str, sizeof str,"Current Component: %d\n\nPlease Input amount to Deposit", wsData[id][wComp]);
                    }
                }
                ShowPlayerDialog(playerid, WORKSHOP_COMPONENT2, DIALOG_STYLE_INPUT, "Component Menu", str, "Input","Cancel");
            }
        }

        case WORKSHOP_COMPONENT2:
        {
            if(response)
            {
                new amount = strval(inputtext), id = AccountData[playerid][pWorkshop];
                if(AccountData[playerid][pMenuType] == 1)
                {
                    if(amount < 1)
                        return Error(playerid, "Minimum amount is 1");

                    if(wsData[id][wComp] < amount) return Error(playerid, "Not Enough Workshop Component");

                    if((Inventory_Count(playerid, "Component") + amount) >= 701)
                        return Error(playerid, "You've reached maximum of Component");

                    Inventory_Add(playerid, "Component", 3096, amount);
                    wsData[id][wComp] -= amount;
                    Workshop_Save(id);
                    Info(playerid, "You've successfully withdraw %d Component from Workshop", amount);
                }
                else if(AccountData[playerid][pMenuType] == 2)
                {
                    if(amount < 1)
                        return Error(playerid, "Minimum amount is 1");

                    if(Inventory_Count(playerid, "Component") < amount) return Error(playerid, "Not Enough Component");

                    if((wsData[id][wComp] + amount) >= MAX_WORKSHOP_INT)
                        return Error(playerid, "You've reached maximum of Component");

                    Inventory_Remove(playerid, "Component", amount);
                    wsData[id][wComp] += amount;
                    Workshop_Save(id);
                    Info(playerid, "You've successfully deposit %d Component to Workshop", amount);
                }
            }
        }


        case WORKSHOP_SETEMPLOYE:
        {
            if(response)
            {
                new id = AccountData[playerid][pWorkshop], str[256];

                if(!IsWorkshopOwner(playerid, id))
                    return Error(playerid, "Only Workshop Owner who can use this");

                switch(listitem)
                {
                    case 0:
                    {
                        AccountData[playerid][pMenuType] = 0;
                        format(str, sizeof str, "Current Owner:\n%s\n\nInput Player ID/Name to Change Ownership", wsData[id][wOwner]);
                    }
                    case 1:
                    {
                        AccountData[playerid][pMenuType] = 1;
                        format(str, sizeof str, "Current Employe:\n%s\n\nInput Player ID/Name to Change", wsEmploy[id][0]);
                    }
                    case 2:
                    {
                        AccountData[playerid][pMenuType] = 2;
                        format(str, sizeof str, "Current Employe:\n%s\n\nInput Player ID/Name to Change", wsEmploy[id][1]);
                    }
                    case 3:
                    {
                        AccountData[playerid][pMenuType] = 3;
                        format(str, sizeof str, "Current Employe:\n%s\n\nInput Player ID/Name to Change", wsEmploy[id][2]);
                    }
                    case 4:
                    {
                        AccountData[playerid][pMenuType] = 4;
                        format(str, sizeof str, "Current Employe:\n%s\n\nInput Player ID/Name to Change", wsEmploy[id][3]);
                    }
                }
                ShowPlayerDialog(playerid, WORKSHOP_SETEMPLOYEE, DIALOG_STYLE_INPUT, "Employe Menu", str, "Change", "Cancel");
            }
        }

        case WORKSHOP_SETEMPLOYEE:
        {
            if(response)
            {
                new otherid, id = AccountData[playerid][pWorkshop], eid = AccountData[playerid][pMenuType];
                if(!strcmp(inputtext, "-", true))
                {
                    SendClientMessageEx(playerid, ARWIN, "WORKSHOP: {ffffff}You've successfully removed %s from Workshop", wsEmploy[id][(eid - 1)]);
                    format(wsEmploy[id][(eid - 1)], MAX_PLAYER_NAME, "-");
                    Workshop_Save(id);
                    return 1;
                }

                if(sscanf(inputtext,"u", otherid))
                    return Error(playerid, "You must put Player ID/Name");

                if(!IsWorkshopOwner(playerid, id))
                    return Error(playerid, "Only Workshop Owner who can use this");

                if(otherid == INVALID_PLAYER_ID || !NearPlayer(playerid, otherid, 5.0))
                    return Error(playerid, "Player itu Disconnect or not near you.");

                if(otherid == playerid)
                    return Error(playerid, "You can't set to yourself as owner.");

                if(eid == 0)
                {
                    new str[128];
                    AccountData[playerid][pTransferWS] = otherid;
                    format(str, sizeof str,"Are you sure want to transfer ownership to %s?", ReturnName(otherid));
                    ShowPlayerDialog(playerid, WS_SETOWNERCONFIRM, DIALOG_STYLE_MSGBOX, "Transfer Ownership", str,"Confirm","Cancel");
                }
                else if(eid > 0 && eid < 5)
                {
                    format(wsEmploy[id][(eid - 1)], MAX_PLAYER_NAME, AccountData[otherid][pName]);
                    SendClientMessageEx(playerid, ARWIN, "WORKSHOP: {ffffff}You've successfully add %s to Workshop", AccountData[otherid][pName]);
                    SendClientMessageEx(otherid, ARWIN, "WORKSHOP: {ffffff}You've been hired in Workshop %s by %s", wsData[id][wName], AccountData[playerid][pName]);
                    Workshop_Save(id);
                }
                Workshop_Save(id);
                Workshop_Refresh(id);
            }
        }

        case WS_SETOWNERCONFIRM:
        {
            if(!response) 
                AccountData[playerid][pTransferWS] = INVALID_PLAYER_ID;

            new otherid = AccountData[playerid][pTransferWS], id = AccountData[playerid][pWorkshop];
            if(response)
            {
                if(otherid == INVALID_PLAYER_ID || !NearPlayer(playerid, otherid, 5.0))
                    return Error(playerid, "Player itu Disconnect or not near you.");

                SendClientMessageEx(playerid, ARWIN, "WORKSHOP: {ffffff}You've successfully transfered %s Workshop to %s",wsData[id][wName], AccountData[otherid][pName]);
                SendClientMessageEx(otherid, ARWIN, "WORKSHOP: {ffffff}You've been transfered to owner in %s Workshop by %s", wsData[id][wName], AccountData[playerid][pName]);
                format(wsData[id][wOwner], MAX_PLAYER_NAME, AccountData[otherid][pName]);
                Workshop_Save(id);
                Workshop_Refresh(id);
            }
        }

        //modif
        case DIALOG_MODIF:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_COLOROPTION, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Ganti Warna Kendaraan", "Ganti Warna Kendaraan\nPaint Job Kendaraan", "Pilih", "Batal");
                }
                case 1:
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_VELG, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Velg", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n"RED"> Kembalikan Menjadi Standart", "Confirm", "back");
                }
                case 2:
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_SPOILER,DIALOG_STYLE_LIST,""TCRP"District "WHITE" - Spoiler","Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n"RED"> Kembalikan Menjadi Standart","Choose","back");
                }
                case 3:
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_HOODS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Hoods", "Fury\nChamp\nRace\nWorx\n", "Confirm", "back");
                }
                case 4:
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_VENTS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Venst", "Oval\nSquare\n", "Confirm", "back");
                }
                case 5:
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_LIGHTS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Lights", "Round\nSquare\n", "Confirm", "back");
                }
                case 6:
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_EXHAUSTS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Exhaust", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n"RED"> Kembalikan Menjadi Standart", "Confirm", "back");
                }
                case 7:
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_FRONT_BUMPERS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Front Bumper", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n"RED"> Kembalikan Menjadi Standart", "Confirm", "back");
                }
                case 8:
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_REAR_BUMPERS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Rear Bumper", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n"RED"> Kembalikan Menjadi Standart", "Confirm", "back");
                }
                case 9:
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_ROOFS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n"RED"> Kembalikan Menjadi Standart", "Confirm", "back");
                }
                case 10:
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_SIDE_SKIRTS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Side Kirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n"RED"> Kembalikan Menjadi Standart", "Confirm", "back");
                }
                case 11:
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_BULLBARS, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Bullbas", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar", "Confirm", "back");
                }
                case 12:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1087);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1087);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 13:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1009);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1009);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 14:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1008);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1008);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 15:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1010);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1010);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 16:
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_NEON, DIALOG_STYLE_LIST,""TCRP"District "WHITE" - Neon", 
                    "Merah\
                    \n"GRAY"Biru\
                    \nHijau\
                    \n"GRAY"Kuning\
                    \nPink\
                    \n"GRAY"Putih\
                    \n"RED"> Remove Neon", "Pilih", "Batal");
                }
                case 17:
                {
                    ShowPlayerDialog(playerid, DIALOG_UPGRADE, DIALOG_STYLE_TABLIST, ""TCRP"District "WHITE"- Upgrade Kendaraan",
                    "Engine Upgrade\t$1000\
                    \n"GRAY"Body Upgrade\t"GRAY"$5000", "Upgrade", "Cancel");
                }
                case 18:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][11]);
                            PlayerVehicle[index][pVehMod][11] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
                case 19:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][1]);
                            PlayerVehicle[index][pVehMod][1] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_WARNA1:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            
            AccountData[playerid][pMechColor1] = floatround(strval(inputtext));

            if(AccountData[playerid][pMechColor1] < 0 || AccountData[playerid][pMechColor1] > 255)
                return ShowPlayerDialog(playerid, DIALOG_MODIF_WARNA1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warna 1", "Mohon masukkan ID Color Dimulai Dari Angka 1 - 255\n"YELLOW"(Masukkan Dibawah Sini):", "Input", "Batal");
            
            ShowPlayerDialog(playerid, DIALOG_MODIF_WARNA2, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warna 2", color_string, "Input", "Batal");
            // ShowPlayerDialog(playerid, DIALOG_MODIF_WARNA2, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warna 2", "Mohon masukkan ID Color Dimulai Dari Angka 1 - 255\n"YELLOW"(Masukkan Dibawah Sini):", "Input", "Batal");
        }
        case DIALOG_MODIF_WARNA2:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;

            AccountData[playerid][pMechColor2] = floatround(strval(inputtext));

            if(AccountData[playerid][pMechColor2] < 0 || AccountData[playerid][pMechColor2] > 255)
                return ShowPlayerDialog(playerid, DIALOG_MODIF_WARNA2, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warna 2", "Mohon masukkan ID Color Dimulai Dari Angka 1 - 255\n"YELLOW"(Masukkan Dibawah Sini):", "Input", "Batal");

            new vehicleid = GetPlayerVehicleID(playerid);
            foreach(new ii : PvtVehicles)
            {
                ChangeVehicleColor(vehicleid, AccountData[playerid][pMechColor1], AccountData[playerid][pMechColor2]);
                if(vehicleid == PlayerVehicle[ii][pVehPhysic])
                {
                    PlayerVehicle[ii][pVehColor1] = AccountData[playerid][pMechColor1];
                    PlayerVehicle[ii][pVehColor2] = AccountData[playerid][pMechColor2];
                }
            }
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda Berhasil Mengganti Warna Kendaraan!");
        }
        case DIALOG_MODIF_PAINTJOB:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;

            AccountData[playerid][pMechColor1] = floatround(strval(inputtext));

            if(AccountData[playerid][pMechColor1] < 0 || AccountData[playerid][pMechColor1] > 3)
                return ShowPlayerDialog(playerid, DIALOG_MODIF_PAINTJOB, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Paint Job", "ERROR: 0 - 1- 2 (3 untuk mengembalikan ke Semula)\n\nMohon masukkan ID Paintjob kendaraan dikolom bawah ini:", "Input", "Batal");

            new vehicleid = GetPlayerVehicleID(playerid);
            foreach(new ii : PvtVehicles)
            {
                ChangeVehiclePaintjob(vehicleid, AccountData[playerid][pMechColor1]);
                if(vehicleid == PlayerVehicle[ii][pVehPhysic])
                {
                    PlayerVehicle[ii][pVehPaintjob] = AccountData[playerid][pMechColor1];
                }
            }
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda Berhasil Mengganti Paintjob Kendaraan!");
        }
        case DIALOG_MODIF_COLOROPTION:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:// Ganti Warna
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_WARNA1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warna 1", color_string, "Input", "Batal");
                    // ShowPlayerDialog(playerid, DIALOG_MODIF_WARNA1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Warna 1", "Mohon masukkan ID Color Dimulai Dari Angka 1 - 255\n"YELLOW"(Masukkan Dibawah Sini):", "Input", "Batal");
                }
                case 1:// Paintjob
                {
                    ShowPlayerDialog(playerid, DIALOG_MODIF_PAINTJOB, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Paint Job", "Mohon masukkan ID Paintjob kendaraan dikolom bawah ini:\n"YELLOW"(0 - 1 - 2 (3 Untuk Mengembalikan Ke Default))", "Input", "Batal");
                }
            }
        }

        case DIALOG_MODIF_VELG:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1025);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1025);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 1:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1074);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1074);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 2:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1076);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1076);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 3:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1078);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1078);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 4:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1081);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1081);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 5:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1082);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1082);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 6:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1085);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1085);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 7:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1096);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1096);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 8:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1097);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1097);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 9:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1098);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1098);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 10:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1084);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1084);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 11:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1073);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1073);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 12:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1075);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1075);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 13:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1077);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1077);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 14:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1079);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1079);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 15:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1080);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1080);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 16:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1083);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1083);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 17:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][15]);
                            PlayerVehicle[index][pVehMod][15] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_SPOILER:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1147);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1147);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1049);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1049);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1162);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1162);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1058);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1058);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1164);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1164);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1138);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1138);
                                }
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 1:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1146);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1146);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1050);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1050);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1158);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1158);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1060);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1060);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1163);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1163);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1139);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1139);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 2:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic]) 
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 527 ||
                            VehicleModel == 415 ||
                            VehicleModel == 546 ||
                            VehicleModel == 603 ||
                            VehicleModel == 426 ||
                            VehicleModel == 436 ||
                            VehicleModel == 405 ||
                            VehicleModel == 477 ||
                            VehicleModel == 580 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1001);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1001);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 3:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic]) 
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 518 ||
                            VehicleModel == 415 ||
                            VehicleModel == 546 ||
                            VehicleModel == 517 ||
                            VehicleModel == 603 ||
                            VehicleModel == 405 ||
                            VehicleModel == 477 ||
                            VehicleModel == 580 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1023);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1023);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 4:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 518 ||
                            VehicleModel == 415 ||
                            VehicleModel == 401 ||
                            VehicleModel == 517 ||
                            VehicleModel == 426 ||
                            VehicleModel == 436 ||
                            VehicleModel == 477 ||
                            VehicleModel == 547 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1003);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1003);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 5:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 589 ||
                            VehicleModel == 492 ||
                            VehicleModel == 547 ||
                            VehicleModel == 405)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1000);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1000);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 6:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 527 ||
                            VehicleModel == 542 ||
                            VehicleModel == 405)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1014);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1014);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 7:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 527 ||
                            VehicleModel == 542)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1015);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1015);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 8:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 546 ||
                            VehicleModel == 517)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1002);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1002);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 9:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][0]);
                            PlayerVehicle[index][pVehMod][0] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_HOODS:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 589 ||
                            VehicleModel == 492 ||
                            VehicleModel == 426 ||
                            VehicleModel == 550)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1005);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1005);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 1:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 401 ||
                            VehicleModel == 402 ||
                            VehicleModel == 546 ||
                            VehicleModel == 426 ||
                            VehicleModel == 550)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1004);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1004);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 2:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 401)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1011);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1011);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 3:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 549)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1012);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1012);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_VENTS:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 546 ||
                            VehicleModel == 517 ||
                            VehicleModel == 603 ||
                            VehicleModel == 547 ||
                            VehicleModel == 439 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1142);
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1443);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1142);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1143);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 1:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 589 ||
                            VehicleModel == 546 ||
                            VehicleModel == 517 ||
                            VehicleModel == 603 ||
                            VehicleModel == 439 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1144);
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1145);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1144);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1145);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_LIGHTS:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 589 ||
                            VehicleModel == 400 ||
                            VehicleModel == 436 ||
                            VehicleModel == 439)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1013);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1013);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 1:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 589 ||
                            VehicleModel == 603 ||
                            VehicleModel == 400)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1024);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1024);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_EXHAUSTS:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 558 ||
                            VehicleModel == 561 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1034);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1034);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1046);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1046);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1065);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1065);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1064);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1064);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1028);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1028);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1089);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1089);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 1:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 558 ||
                            VehicleModel == 561 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1037);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1037);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1045);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1045);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1066);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1066);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1059);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1059);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1029);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1029);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1092);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1092);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                else
                                {
                                    ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                                }
                            }
                        }
                    }
                }
                case 2:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 575 ||
                            VehicleModel == 534 ||
                            VehicleModel == 567 ||
                            VehicleModel == 536 ||
                            VehicleModel == 576 ||
                            VehicleModel == 535)
                            {
                                if(VehicleModel == 575)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1044);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1044);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 534)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1126);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1126);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1129);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1129);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1104);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1104);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 576)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1113);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1113);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 535)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1136);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1136);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                else
                                {
                                    ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                                }
                            }
                        }
                    }
                }
                case 3:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 575 ||
                            VehicleModel == 534 ||
                            VehicleModel == 567 ||
                            VehicleModel == 536 ||
                            VehicleModel == 576 ||
                            VehicleModel == 535)
                            {
                                if(VehicleModel == 575)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1043);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1043);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 534)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1127);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1127);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1132);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1132);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1105);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1105);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 576)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1135);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1135);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 535)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1114);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1114);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                else
                                {
                                    ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                                }
                            }
                        }
                    }
                }
                case 4:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 527 ||
                            VehicleModel == 542 ||
                            VehicleModel == 589 ||
                            VehicleModel == 400 ||
                            VehicleModel == 517 ||
                            VehicleModel == 603 ||
                            VehicleModel == 426 ||
                            VehicleModel == 547 ||
                            VehicleModel == 405 ||
                            VehicleModel == 580 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549 ||
                            VehicleModel == 477)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1020);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1020);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 5:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 527 ||
                            VehicleModel == 542 ||
                            VehicleModel == 400 ||
                            VehicleModel == 426 ||
                            VehicleModel == 436 ||
                            VehicleModel == 547 ||
                            VehicleModel == 405 ||
                            VehicleModel == 477)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1021);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1021);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 6:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 436)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1022);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1022);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 7:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 518 ||
                            VehicleModel == 415 ||
                            VehicleModel == 542 ||
                            VehicleModel == 546 ||
                            VehicleModel == 400 ||
                            VehicleModel == 517 ||
                            VehicleModel == 603 ||
                            VehicleModel == 426 ||
                            VehicleModel == 436 ||
                            VehicleModel == 547 ||
                            VehicleModel == 405 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549 ||
                            VehicleModel == 477)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1019);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1019);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 8:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 415 ||
                            VehicleModel == 542 ||
                            VehicleModel == 546 ||
                            VehicleModel == 400 ||
                            VehicleModel == 517 ||
                            VehicleModel == 603 ||
                            VehicleModel == 426 ||
                            VehicleModel == 415 ||
                            VehicleModel == 547 ||
                            VehicleModel == 405 ||
                            VehicleModel == 550 ||
                            VehicleModel == 549 ||
                            VehicleModel == 477)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1018);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1018);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                            else
                            {
                                ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini tidak support!.");
                            }
                        }
                    }
                }
                case 9:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][4]);
                            PlayerVehicle[index][pVehMod][4] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_FRONT_BUMPERS:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1171);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1171);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1153);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1153);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1160);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1160);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1155);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1155);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1166);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1166);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1169);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1169);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 1:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1172);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1172);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1152);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1152);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1173);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1173);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1157);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1157);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1165);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1165);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1170);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1170);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 2:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 575 ||
                            VehicleModel == 534 ||
                            VehicleModel == 567 ||
                            VehicleModel == 536 ||
                            VehicleModel == 576 ||
                            VehicleModel == 535)
                            {
                                if(VehicleModel == 575)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1174);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1174);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 534)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1179);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1179);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1189);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1189);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1182);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1182);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 576)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1191);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1191);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 535)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1115);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1115);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 3:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 575 ||
                            VehicleModel == 534 ||
                            VehicleModel == 567 ||
                            VehicleModel == 536 ||
                            VehicleModel == 576 ||
                            VehicleModel == 535)
                            {
                                if(VehicleModel == 575)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1175);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1175);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 534)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1185);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1185);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1188);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1188);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1181);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1181);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 576)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1190);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1190);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 535)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1116);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1116);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 4:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][2]);
                            PlayerVehicle[index][pVehMod][2] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_REAR_BUMPERS:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1149);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1149);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1150);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1150);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1159);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1159);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1154);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1154);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1168);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1168);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1141);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1141);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 1:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1148);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1148);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1151);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1151);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1161);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1161);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1156);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1156);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1167);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1167);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1140);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1140);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 2:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 575 ||
                            VehicleModel == 534 ||
                            VehicleModel == 567 ||
                            VehicleModel == 536 ||
                            VehicleModel == 576 ||
                            VehicleModel == 535)
                            {
                                if(VehicleModel == 575)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1176);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1176);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 534)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1180);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1180);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1187);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1187);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1184);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1184);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 576)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1192);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1192);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 535)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1109);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1109);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 3:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 575 ||
                            VehicleModel == 534 ||
                            VehicleModel == 567 ||
                            VehicleModel == 536 ||
                            VehicleModel == 576 ||
                            VehicleModel == 535)
                            {
                                if(VehicleModel == 575)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1177);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1177);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 534)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1178);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1178);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1186);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1186);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1183);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1183);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 576)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1193);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1193);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 535)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1110);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1110);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 4:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][3]);
                            PlayerVehicle[index][pVehMod][3] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_ROOFS:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1038);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1038);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1054);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1054);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1067);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1067);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1055);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1055);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1088);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1088);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1032);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1032);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 1:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1038);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1038);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1053);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1053);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1068);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1068);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1061);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1061);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1091);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1091);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1033);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1033);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 2:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 567 ||
                            VehicleModel == 536)
                            {
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1130);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1130);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1128);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1128);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 3:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 567 ||
                            VehicleModel == 536)
                            {
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1131);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1131);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1103);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1103);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 4:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 589 ||
                            VehicleModel == 492 ||
                            VehicleModel == 546 ||
                            VehicleModel == 603 ||
                            VehicleModel == 426 ||
                            VehicleModel == 436 ||
                            VehicleModel == 580 ||
                            VehicleModel == 550 ||
                            VehicleModel == 477)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1006);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1006);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 5:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][8]);
                            PlayerVehicle[index][pVehMod][8] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_SIDE_SKIRTS:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1036);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1040);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1036);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1040);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1047);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1051);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1047);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1051);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1069);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1071);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1069);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1071);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1056);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1062);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1056);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1062);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1090);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1094);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1090);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1094);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1026);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1027);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1026);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1027);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 1:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 562 ||
                            VehicleModel == 565 ||
                            VehicleModel == 559 ||
                            VehicleModel == 561 ||
                            VehicleModel == 558 ||
                            VehicleModel == 560)
                            {
                                if(VehicleModel == 562)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1039);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1041);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1039);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1041);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 565)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1048);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1052);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1048);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1052);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 559)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1070);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1072);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1070);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1072);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 561)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1057);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1063);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1057);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1063);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 558)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1093);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1095);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1093);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1095);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 560)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1031);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1030);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1031);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1030);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 2:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 575 ||
                            VehicleModel == 536 ||
                            VehicleModel == 576 ||
                            VehicleModel == 567)
                            {
                                if(VehicleModel == 575)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1042);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1099);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1042);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1099);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 536)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1108);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1107);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1108);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1107);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 576)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1134);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1137);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1134);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1137);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                                if(VehicleModel == 567)
                                {
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1102);
                                    AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1133);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1102);
                                    SavePVComponents(PlayerVehicle[i][pVehPhysic], 1133);
                                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                                }
                            }
                        }
                    }
                }
                case 3:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 534)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1102);
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1101);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1102);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1101);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 4:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 534)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1106);
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1124);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1106);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1124);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 5:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 535)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1118);
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1120);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1118);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1120);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 6:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 535)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1119);
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1121);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1119);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1121);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 7:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(
                            VehicleModel == 401 ||
                            VehicleModel == 518 ||
                            VehicleModel == 527 ||
                            VehicleModel == 415 ||
                            VehicleModel == 589 ||
                            VehicleModel == 546 ||
                            VehicleModel == 517 ||
                            VehicleModel == 603 ||
                            VehicleModel == 436 ||
                            VehicleModel == 439 ||
                            VehicleModel == 580 ||
                            VehicleModel == 549 ||
                            VehicleModel == 477)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1007);
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1017);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1007);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1017);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 8:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][9]);
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehMod][10]);
                            PlayerVehicle[index][pVehMod][9] = 0;
                            PlayerVehicle[index][pVehMod][10] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
        case DIALOG_MODIF_BULLBARS:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 534)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1100);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1100);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 1:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 534)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1123);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1123);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 2:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 534)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1125);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1125);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
                case 3:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            new VehicleModel = GetVehicleModel(PlayerVehicle[i][pVehPhysic]);
                            if(VehicleModel == 534)
                            {
                                AddVehicleComponent(PlayerVehicle[i][pVehPhysic], 1117);
                                SavePVComponents(PlayerVehicle[i][pVehPhysic], 1117);
                                PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            }
                        }
                    }
                }
            }
        }
        case DIALOG_UPGRADE:
        {
            if(!response) return 1;
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            switch(listitem)
            {
                case 0: // Engine
                {
                    if(AccountData[playerid][pMoney] < 10000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    
                    new vehid = GetPlayerVehicleID(playerid);
                    Vehicle_AddUpgrade(vehid, 1);
                    TakeMoney(playerid, 10000);
                    Info(playerid, "Anda mengupgrade engine "YELLOW"%s"WHITE" Max Health Kendaraan sekarang "YELLOW"2000.0", GetVehicleName(vehid));
                }
                case 1: // Body
                {
                    if(AccountData[playerid][pMoney] < 5000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                    
                    new vehid = GetPlayerVehicleID(playerid);
                    Vehicle_AddUpgrade(vehid, 3);
                    TakeMoney(playerid, 5000);
                    Info(playerid, "Anda mengupgrade body "YELLOW"%s"WHITE" Body kendaraan sekarang tidak mudah hancur", GetVehicleName(vehid));
                }
            }
            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
        }
        case DIALOG_MODIF_NEON:
        {
            if(!IsWorkshopOwner(playerid, AccountData[playerid][pWorkshop]) || !IsWorkshopEmploye(playerid, AccountData[playerid][pWorkshop])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Karyawan Workshop!");
            if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, RED_NEON, 0);

                            PlayerVehicle[i][pVehNeon] = RED_NEON;

                            if(PlayerVehicle[i][pVehNeon] == 0)
                            {
                                PlayerVehicle[i][cTogNeon] = 0;
                            }
                            else 
                            {
                                PlayerVehicle[i][cTogNeon] = 1;
                            }
                        }
                    }
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                }
                case 1:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, BLUE_NEON, 0);

                            PlayerVehicle[i][pVehNeon] = BLUE_NEON;

                            if(PlayerVehicle[i][pVehNeon] == 0)
                            {
                                PlayerVehicle[i][cTogNeon] = 0;
                            }
                            else 
                            {
                                PlayerVehicle[i][cTogNeon] = 1;
                            }
                        }
                    }
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                }
                case 2:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, GREEN_NEON, 0);

                            PlayerVehicle[i][pVehNeon] = GREEN_NEON;

                            if(PlayerVehicle[i][pVehNeon] == 0)
                            {
                                PlayerVehicle[i][cTogNeon] = 0;
                            }
                            else 
                            {
                                PlayerVehicle[i][cTogNeon] = 1;
                            }
                        }
                    }
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                }
                case 3:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, YELLOW_NEON, 0);

                            PlayerVehicle[i][pVehNeon] = YELLOW_NEON;

                            if(PlayerVehicle[i][pVehNeon] == 0)
                            {
                                PlayerVehicle[i][cTogNeon] = 0;
                            }
                            else 
                            {
                                PlayerVehicle[i][cTogNeon] = 1;
                            }
                        }
                    }
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                }
                case 4:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, PINK_NEON, 0);

                            PlayerVehicle[i][pVehNeon] = PINK_NEON;

                            if(PlayerVehicle[i][pVehNeon] == 0)
                            {
                                PlayerVehicle[i][cTogNeon] = 0;
                            }
                            else 
                            {
                                PlayerVehicle[i][cTogNeon] = 1;
                            }
                        }
                    }
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                }
                case 5:
                {
                    new vehid = GetPlayerVehicleID(playerid);
                    foreach(new i : PvtVehicles)
                    {
                        if(vehid == PlayerVehicle[i][pVehPhysic])
                        {
                            SetVehicleNeonLights(PlayerVehicle[i][pVehPhysic], true, WHITE_NEON, 0);

                            PlayerVehicle[i][pVehNeon] = WHITE_NEON;

                            if(PlayerVehicle[i][pVehNeon] == 0)
                            {
                                PlayerVehicle[i][cTogNeon] = 0;
                            }
                            else 
                            {
                                PlayerVehicle[i][cTogNeon] = 1;
                            }
                        }
                    }
                    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                }
                case 6:
                {
                    new vehid = GetPlayerVehicleID(playerid),
                        index = RETURN_INVALID_VEHICLE_ID;
                    
                    if((index = Vehicle_ReturnID(vehid)) != RETURN_INVALID_VEHICLE_ID)
                    {
                        if(IsValidVehicle(vehid))
                        {
                            SetVehicleNeonLights(vehid, false, PlayerVehicle[index][pVehNeon], 0);
                            RemoveVehicleComponent(vehid, PlayerVehicle[index][pVehNeon]);
                            PlayerVehicle[index][pVehNeon] = 0;
                            PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
                            SavePlayerVehicle(index);
                        }
                    }
                }
            }
        }
    }
    return 1;
}
