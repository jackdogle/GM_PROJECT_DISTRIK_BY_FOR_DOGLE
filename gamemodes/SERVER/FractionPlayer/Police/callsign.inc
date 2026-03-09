/* Variables */

#define IsCallSignActive(%0)        gVehicleCallsign[%0]
#define ReturnCallsignLabelID(%0)   gVehicleCallsignLabel[%0]

new
    gVehicleCallsignText[MAX_VEHICLES][64],
    bool:gVehicleCallsign[MAX_VEHICLES] = { false, ... },
    STREAMER_TAG_3D_TEXT_LABEL:gVehicleCallsignLabel[MAX_VEHICLES] = { STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID, ... };

/* Event */
hook OnVehicleDestroyed(vehicleid)
{
    Callsign_Remove(vehicleid);
    return 1;
}

/* Functions */
Callsign_Remove(vehicleid)
{
    if(IsCallSignActive(vehicleid))
    {
        if(IsValidDynamic3DTextLabel(gVehicleCallsignLabel[vehicleid]))
            DestroyDynamic3DTextLabel(gVehicleCallsignLabel[vehicleid]);
        
        gVehicleCallsign[vehicleid] = false;
        gVehicleCallsignText[vehicleid][0] = EOS;
        gVehicleCallsignLabel[vehicleid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    }
    return 1;
}

Callsign_Create(vehicleid, const text[])
{
    if(IsCallSignActive(vehicleid))
    {
        format(gVehicleCallsignText[vehicleid], 64, text);

        if(IsValidDynamic3DTextLabel(gVehicleCallsignLabel[vehicleid])) UpdateDynamic3DTextLabelText(gVehicleCallsignLabel[vehicleid], -1, text);
        else gVehicleCallsignLabel[vehicleid] = CreateDynamic3DTextLabel(text, -1, -0.7, -1.9, -0.3, 10, INVALID_PLAYER_ID, vehicleid, 1);
    }
    return 1;
}

CMD:callsign(playerid, params[])
{
    new
        vehicle_index,
        vehicleid = GetPlayerVehicleID(playerid);
    
    if(AccountData[playerid][pFaction] != FACTION_POLISI)
        return Error(playerid, "Anda bukan anggota kepolisian!");
    
    if(!IsPlayerInAnyVehicle(playerid))
        return Error(playerid, "Anda tidak berada di dalam kendaraan!");
    
    // if(!AccountData[playerid][pDutyPD])
    //     return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang on duty!");

    if((vehicle_index = Vehicle_ReturnID(vehicleid)) != RETURN_INVALID_VEHICLE_ID)
    {
        if(PlayerVehicle[vehicle_index][pVehFaction] != FACTION_POLISI)
            return Error(playerid, "Kendaraan tersebut bukan milik kepolisian!");
        
        if(PlayerVehicle[vehicle_index][pVehOwnerID] != AccountData[playerid][pID])     
            return Error(playerid, "Kendaraan ini bukan milik anda!");
    }

    if(isnull(params))
        return Syntax(playerid, "/callsign [text] 'off' untuk menghapus");

    if(strlen(params) > 64)
        return Error(playerid, "Minimal 64 karakter yang diperbolehkan!");

    if(!strcmp(params, "off", true))
    {
        Callsign_Remove(vehicleid);
        Info(playerid, "Callsign berhasil dihapus!");
        return 1;
    }

    gVehicleCallsign[vehicleid] = true;
    Callsign_Create(vehicleid, params);

    Info(playerid, "Callsign: %s", params);
    return 1;
}