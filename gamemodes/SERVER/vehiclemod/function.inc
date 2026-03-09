/*
===========================================================
    Vehicle Accesories Script, Author : Revelt
===========================================================*/
#include <YSI\y_hooks>

ModshopVehicleArea(playerid)
{
    if(IsPlayerInRangeOfPoint(playerid, 5.0, 1103.7428, -1246.4520, 15.8362))
        return 1;

    if(IsPlayerInRangeOfPoint(playerid, 5.0, 1093.8877, -1246.2726, 15.8362))
        return 1;

    return 0;
}

// Function ini untuk save object kendaraan ke database dan menyimpan SQL id ke dalam vehObjectID!
forward Vehicle_ObjectDB(vehicleid, slot);
public Vehicle_ObjectDB(vehicleid, slot)
{
	if(VehicleObjects[vehicleid][slot][vehObjectExists] == false)
		return 0;

	VehicleObjects[vehicleid][slot][vehObjectID] = cache_insert_id();


	Vehicle_ObjectSave(vehicleid, slot);
	return 1;
}

// Function untuk ngeload object kendaraan ketika kendraan diload ke dalam server!
JavaTR: Vehicle_ObjectLoad(vehicleid)
{
    new rowscount = cache_num_rows();
    if(rowscount)
    {
        for(new slot = 0; slot != rowscount; slot ++) if (!VehicleObjects[vehicleid][slot][vehObjectExists])
        {
            cache_get_value_name_int(slot, "vehicle", VehicleObjects[vehicleid][slot][vehObjectVehicleIndex]);
            if(VehicleObjects[vehicleid][slot][vehObjectVehicleIndex] == PlayerVehicle[vehicleid][pVehID] && !VehicleObjects[vehicleid][slot][vehObjectExists])
            {
                VehicleObjects[vehicleid][slot][vehObjectExists] = true;
            
                cache_get_value_name(slot, "text", VehicleObjects[vehicleid][slot][vehObjectText], 32);
                cache_get_value_name(slot, "font", VehicleObjects[vehicleid][slot][vehObjectFont], 24);			

                cache_get_value_name_int(slot, "id", VehicleObjects[vehicleid][slot][vehObjectID]);
                cache_get_value_name_int(slot, "type", VehicleObjects[vehicleid][slot][vehObjectType]);
                cache_get_value_name_int(slot, "model", VehicleObjects[vehicleid][slot][vehObjectModel]);
                cache_get_value_name_int(slot, "color", VehicleObjects[vehicleid][slot][vehObjectColor]);

                cache_get_value_name_int(slot, "fontcolor", VehicleObjects[vehicleid][slot][vehObjectFontColor]);
                cache_get_value_name_int(slot, "fontsize", VehicleObjects[vehicleid][slot][vehObjectFontSize]);

                cache_get_value_name_float(slot, "x", VehicleObjects[vehicleid][slot][vehObjectPosX]);
                cache_get_value_name_float(slot, "y", VehicleObjects[vehicleid][slot][vehObjectPosY]);
                cache_get_value_name_float(slot, "z", VehicleObjects[vehicleid][slot][vehObjectPosZ]);

                cache_get_value_name_float(slot, "rx", VehicleObjects[vehicleid][slot][vehObjectPosRX]);
                cache_get_value_name_float(slot, "ry", VehicleObjects[vehicleid][slot][vehObjectPosRY]);
                cache_get_value_name_float(slot, "rz", VehicleObjects[vehicleid][slot][vehObjectPosRZ]);

                // Ketika sudah terload, maka object yang sudah di tampung ke dalam variabel akan di attach berdasarkan slotnya!
                Vehicle_AttachObject(vehicleid, slot);
            }
        }
    }
    return 1;
}

// Function untuk ngesave object ke dalam database dari variabel penampung!
Vehicle_ObjectSave(vehicleid, slot)
{
	if(VehicleObjects[vehicleid][slot][vehObjectExists])
    {
        new query[2046];

        format(query, sizeof(query), "UPDATE `vehicle_object` SET `model`='%d', `color`='%d',`type`='%d', `x`='%f',`y`='%f',`z`='%f', `rx`='%f',`ry`='%f',`rz`='%f'",
            VehicleObjects[vehicleid][slot][vehObjectModel],
            VehicleObjects[vehicleid][slot][vehObjectColor],
            VehicleObjects[vehicleid][slot][vehObjectType],
            VehicleObjects[vehicleid][slot][vehObjectPosX], 
            VehicleObjects[vehicleid][slot][vehObjectPosY], 
            VehicleObjects[vehicleid][slot][vehObjectPosZ], 
            VehicleObjects[vehicleid][slot][vehObjectPosRX],
            VehicleObjects[vehicleid][slot][vehObjectPosRY], 
            VehicleObjects[vehicleid][slot][vehObjectPosRZ]
        );

        format(query, sizeof(query), "%s, `text`='%s',`font`='%s', `fontsize`='%d',`fontcolor`='%d' WHERE `id`='%d' AND `vehicle` = '%d'",
            query, 
            VehicleObjects[vehicleid][slot][vehObjectText], 
            VehicleObjects[vehicleid][slot][vehObjectFont], 
            VehicleObjects[vehicleid][slot][vehObjectFontSize], 
            VehicleObjects[vehicleid][slot][vehObjectFontColor], 
            VehicleObjects[vehicleid][slot][vehObjectID],
			VehicleObjects[vehicleid][slot][vehObjectVehicleIndex]
        );
        mysql_tquery(g_SQL, query);
    }
	return 1;
}

// Function untuk menambahkan object untuk vehicle id tersebut
// Model = Object modelnya || Type = 1 / 2, 1 Itu Object, 2 Itu Text
Vehicle_ObjectAddObjects(playerid, vehicleid, model, type)
{
    if(!IsValidVehicle(PlayerVehicle[vehicleid][pVehPhysic]))
        return 0;
    
    new query_string[255];
    for(new slot = 0; slot < MAX_VEHICLE_OBJECT; slot++)
    { 
        if(VehicleObjects[vehicleid][slot][vehObjectExists] == false)
        {
            VehicleObjects[vehicleid][slot][vehObjectExists] = true;

            VehicleObjects[vehicleid][slot][vehObjectType] = type;
            VehicleObjects[vehicleid][slot][vehObjectVehicleIndex] = PlayerVehicle[vehicleid][pVehID];
            VehicleObjects[vehicleid][slot][vehObjectModel] = model;		

            VehicleObjects[vehicleid][slot][vehObjectColor] = 0;

            VehicleObjects[vehicleid][slot][vehObjectPosX] = 0.0;
            VehicleObjects[vehicleid][slot][vehObjectPosY] = 0.0;
            VehicleObjects[vehicleid][slot][vehObjectPosZ] = 0.0;

            VehicleObjects[vehicleid][slot][vehObjectPosRX] = 0.0;
            VehicleObjects[vehicleid][slot][vehObjectPosRY] = 0.0;
            VehicleObjects[vehicleid][slot][vehObjectPosRZ] = 0.0;

            if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_TEXT) //
            {
                format(VehicleObjects[vehicleid][slot][vehObjectText], 32, "TEXT");
                format(VehicleObjects[vehicleid][slot][vehObjectFont], 24, "Arial");
                VehicleObjects[vehicleid][slot][vehObjectFontColor] = 1;
                VehicleObjects[vehicleid][slot][vehObjectFontSize] = 24; 
            }

            Dialog_Show(playerid, DIALOG_MODSHOPMOVE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Modshop", "Position\nPosition (Manual)", "Select", "Close");
            
            TakeMoney(playerid, 30000);
            SendClientMessageEx(playerid, ARWIN, "MODSHOP"WHITE": Anda membeli "YELLOW"%s"WHITE" dengan Harga "GREEN"$30.000", GetVehObjectNameByModel(VehicleObjects[vehicleid][slot][vehObject]));
            format(query_string, sizeof(query_string), "INSERT INTO `vehicle_object` (`vehicle`) VALUES ('%d')", PlayerVehicle[vehicleid][pVehID]);
            mysql_tquery(g_SQL, query_string, "Vehicle_ObjectDB", "dd", vehicleid, slot);
            return 1;
        }
    }
	return 0;
}

Vehicle_TextAdd(playerid, vehicleid, model, type)
{
    if (!IsValidVehicle(PlayerVehicle[vehicleid][pVehPhysic]))
        return 0;
    
    new query_string[255];
    for(new slot = 0; slot < MAX_VEHICLE_OBJECT; slot++)
    { 
        if(VehicleObjects[vehicleid][slot][vehObjectExists] == false)
        {
            VehicleObjects[vehicleid][slot][vehObjectExists] = true;

            VehicleObjects[vehicleid][slot][vehObjectType] = type;
            VehicleObjects[vehicleid][slot][vehObjectVehicleIndex] = PlayerVehicle[vehicleid][pVehID];
            VehicleObjects[vehicleid][slot][vehObjectModel] = model;		

            VehicleObjects[vehicleid][slot][vehObjectColor] = 0;

            VehicleObjects[vehicleid][slot][vehObjectPosX] = 0.0;
            VehicleObjects[vehicleid][slot][vehObjectPosY] = 0.0;
            VehicleObjects[vehicleid][slot][vehObjectPosZ] = 0.0;

            VehicleObjects[vehicleid][slot][vehObjectPosRX] = 0.0;
            VehicleObjects[vehicleid][slot][vehObjectPosRY] = 0.0;
            VehicleObjects[vehicleid][slot][vehObjectPosRZ] = 0.0;

            if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_TEXT) //
            {
                format(VehicleObjects[vehicleid][slot][vehObjectText], 32, "TEXT");
                format(VehicleObjects[vehicleid][slot][vehObjectFont], 24, "Arial");
                VehicleObjects[vehicleid][slot][vehObjectFontColor] = 1;
                VehicleObjects[vehicleid][slot][vehObjectFontSize] = 24; 
            }

            Dialog_Show(playerid, VACCSE1, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nText Name\nText Size\nText Font\nText Color\nRemove Modification", "Select", "Back");
            
            TakeMoney(playerid, 15000);
            SendClientMessageEx(playerid, ARWIN, "MODSHOP"WHITE": Anda membeli "YELLOW"Sticker"WHITE" dengan Harga "GREEN"$15,000");

            format(query_string, sizeof(query_string), "INSERT INTO `vehicle_object` (`vehicle`) VALUES ('%d')", PlayerVehicle[vehicleid][pVehID]);
            mysql_tquery(g_SQL, query_string, "Vehicle_ObjectDB", "dd", vehicleid, slot);
            return 1;
        }
    }
    return 0;
}

Vehicle_SpotLightAdd(playerid, vehicleid, model, type)
{
    if (!IsValidVehicle(PlayerVehicle[vehicleid][pVehPhysic]))
        return 0;
    
    new query_string[255];
    for(new slot = 0; slot < MAX_VEHICLE_OBJECT; slot++)
    { 
        if(VehicleObjects[vehicleid][slot][vehObjectExists] == false)
        {
            if(GetPlayerMoney(playerid) < 5000)
                return Error(playerid, "Untuk membeli vehicle toys kamu harus mempunyai uang $50.00");
            VehicleObjects[vehicleid][slot][vehObjectExists] = true;

            VehicleObjects[vehicleid][slot][vehObjectType] = type;
            VehicleObjects[vehicleid][slot][vehObjectVehicleIndex] = PlayerVehicle[vehicleid][pVehID];
            VehicleObjects[vehicleid][slot][vehObjectModel] = model;		

            VehicleObjects[vehicleid][slot][vehObjectColor] = 0;

            VehicleObjects[vehicleid][slot][vehObjectPosX] = 0.0;
            VehicleObjects[vehicleid][slot][vehObjectPosY] = 0.0;
            VehicleObjects[vehicleid][slot][vehObjectPosZ] = 0.0;

            VehicleObjects[vehicleid][slot][vehObjectPosRX] = 0.0;
            VehicleObjects[vehicleid][slot][vehObjectPosRY] = 0.0;
            VehicleObjects[vehicleid][slot][vehObjectPosRZ] = 0.0;

            Dialog_Show(playerid, DIALOG_SPOTLIGHT, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Modshop", "Position\nPosition (Manual)\nLight Color", "Select", "Close");
            
            TakeMoney(playerid, 10000);
            SendClientMessageEx(playerid, ARWIN, "MODSHOP"WHITE": Anda membeli "YELLOW"Spotlights"WHITE" dengan Harga "GREEN"$10,000");

            format(query_string, sizeof(query_string), "INSERT INTO `vehicle_object` (`vehicle`) VALUES ('%d')", PlayerVehicle[vehicleid][pVehID]);
            mysql_tquery(g_SQL, query_string, "Vehicle_ObjectDB", "dd", vehicleid, slot);
            return 1;
        }
    }
	return 0;
}

// Function untuk attach vehicle object ke kendaraan yang sudah ada di server!
Vehicle_AttachObject(vehicleid, slot)
{
    if(!IsValidVehicle(PlayerVehicle[vehicleid][pVehPhysic]))
        return 0;
    
    new
        model       = VehicleObjects[vehicleid][slot][vehObjectModel]
    ;
    
    if (IsValidDynamicObject(VehicleObjects[vehicleid][slot][vehObject]))
    {
        DestroyDynamicObject(VehicleObjects[vehicleid][slot][vehObject]);
        VehicleObjects[vehicleid][slot][vehObject] = INVALID_STREAMER_ID;
    }
        
    VehicleObjects[vehicleid][slot][vehObject] = CreateDynamicObject(model, VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ], VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);

    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_DRAW_DISTANCE, 50);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_STREAM_DISTANCE, 50);

    if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_BODY)
    {
        Vehicle_ObjectColorSync(vehicleid, slot);
    }
    else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_TEXT)
    {
        Vehicle_ObjectTextSync(vehicleid, slot);
    }
    else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_LIGHT)
    {
        Vehicle_SpotLightDelete(vehicleid, slot);
    }
    
    AttachDynamicObjectToVehicle(VehicleObjects[vehicleid][slot][vehObject], PlayerVehicle[vehicleid][pVehPhysic], VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ], VehicleObjects[vehicleid][slot][vehObjectPosRX], VehicleObjects[vehicleid][slot][vehObjectPosRY], VehicleObjects[vehicleid][slot][vehObjectPosRZ]);
    Vehicle_ObjectUpdate(vehicleid, slot);
    return 0;
}

// Function Untuk sync object color yang ada di kendaraan, ketika mengubah warna object!
Vehicle_SpotLightDelete(vehicleid, slot)
{
    if (!IsValidVehicle(PlayerVehicle[vehicleid][pVehPhysic]))
        return 0;
    
    switch(GetLightStatus(vehicleid))
    {
        case false:
        {
            if (IsValidDynamicObject(VehicleObjects[vehicleid][slot][vehObject]))
                DestroyDynamicObject(VehicleObjects[vehicleid][slot][vehObject]);
            
            VehicleObjects[vehicleid][slot][vehObject] = INVALID_STREAMER_ID;
        }
        case true:
        {
            new
                model       = VehicleObjects[vehicleid][slot][vehObjectModel],
                Float:x     = VehicleObjects[vehicleid][slot][vehObjectPosX],
                Float:y     = VehicleObjects[vehicleid][slot][vehObjectPosY],
                Float:z     = VehicleObjects[vehicleid][slot][vehObjectPosZ],
                Float:rx    = VehicleObjects[vehicleid][slot][vehObjectPosRX],
                Float:ry    = VehicleObjects[vehicleid][slot][vehObjectPosRY],
                Float:rz    = VehicleObjects[vehicleid][slot][vehObjectPosRZ],
                Float:vposx,
                Float:vposy,
                Float:vposz
            ;
            if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_LIGHT)
            {
                if (IsValidDynamicObject(VehicleObjects[vehicleid][slot][vehObject]))
                    DestroyDynamicObject(VehicleObjects[vehicleid][slot][vehObject]);
                
                VehicleObjects[vehicleid][slot][vehObject] = INVALID_STREAMER_ID;

                GetVehiclePos(PlayerVehicle[vehicleid][pVehPhysic], vposx, vposy, vposz);

                VehicleObjects[vehicleid][slot][vehObject] = CreateDynamicObject(model, vposx, vposy, vposz, rx, ry, rz);

                Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_DRAW_DISTANCE, 25);
                Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_STREAM_DISTANCE, 25);

                AttachDynamicObjectToVehicle(VehicleObjects[vehicleid][slot][vehObject], PlayerVehicle[vehicleid][pVehPhysic], x, y, z, rx, ry, rz);
                Vehicle_ObjectUpdate(vehicleid, slot);
            }
        }
    }
    return 1;
}

// Function Untuk sync object color yang ada di kendaraan, ketika mengubah warna object!
Vehicle_ObjectColorSync(vehicleid, slot)
{
    if (!IsValidVehicle(PlayerVehicle[vehicleid][pVehPhysic]))
        return 0;
    
    SetDynamicObjectMaterial(VehicleObjects[vehicleid][slot][vehObject], 0, VehicleObjects[vehicleid][slot][vehObjectModel], "none", "none", RGBAToARGB(ColorList[VehicleObjects[vehicleid][slot][vehObjectColor]]));
    return 1;
}

// Function Untuk sync object color yang ada di kendaraan, ketika mengubah warna object!
Vehicle_LightColorSync(vehicleid, slot, id, playerid)
{
    if (!IsValidVehicle(PlayerVehicle[vehicleid][pVehPhysic]))
        return 0;
    
    new
        Float:x     = VehicleObjects[vehicleid][slot][vehObjectPosX],
        Float:y     = VehicleObjects[vehicleid][slot][vehObjectPosY],
        Float:z     = VehicleObjects[vehicleid][slot][vehObjectPosZ],
        Float:rx    = VehicleObjects[vehicleid][slot][vehObjectPosRX],
        Float:ry    = VehicleObjects[vehicleid][slot][vehObjectPosRY],
        Float:rz    = VehicleObjects[vehicleid][slot][vehObjectPosRZ],
        Float:vposx,
        Float:vposy,
        Float:vposz
    ;
    VehicleObjects[vehicleid][slot][vehObjectModel] = id;
    if (IsValidDynamicObject(VehicleObjects[vehicleid][slot][vehObject]))
        DestroyDynamicObject(VehicleObjects[vehicleid][slot][vehObject]);

    VehicleObjects[vehicleid][slot][vehObject] = INVALID_STREAMER_ID;

    GetVehiclePos(PlayerVehicle[vehicleid][pVehPhysic], vposx, vposy, vposz);
    VehicleObjects[vehicleid][slot][vehObject] = CreateDynamicObject(VehicleObjects[vehicleid][slot][vehObjectModel], vposx+x, vposy+y, vposz+z, rx, ry, rz);   
    
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_DRAW_DISTANCE, 15);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_STREAM_DISTANCE, 15);
    //Vehicle_ObjectSave(vehicleid, slot); // Setelah warna di ubah pastikan selalu di save!
    Dialog_Show(playerid, DIALOG_SPOTLIGHT, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Modshop", "Position\nPosition (Manual)\nLight Color\nSave", "Select", "Close");
    return 1;
}

// Function untuk sync text yang ada di kendaraan ketika mengubah text!
Vehicle_ObjectTextSync(vehicleid, slot)
{
    if (!IsValidVehicle(PlayerVehicle[vehicleid][pVehPhysic]))
        return 0;

    SetDynamicObjectMaterialText(VehicleObjects[vehicleid][slot][vehObject], 0, VehicleObjects[vehicleid][slot][vehObjectText], 130, VehicleObjects[vehicleid][slot][vehObjectFont], VehicleObjects[vehicleid][slot][vehObjectFontSize], 1, RGBAToARGB(ColorList[VehicleObjects[vehicleid][slot][vehObjectFontColor]]), 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
    return 1;
}

// Function ini berguna untuk update posisi object ke dalam variabel setelah di edit menggunakan
// ..- Callback OnPlayerEditDynamicObject!

Vehicle_ObjectUpdate(vehicleid, slot)
{   
    if(!IsValidVehicle(PlayerVehicle[vehicleid][pVehPhysic]))
        return 0;
    
    new
        Float:x     = VehicleObjects[vehicleid][slot][vehObjectPosX],
        Float:y     = VehicleObjects[vehicleid][slot][vehObjectPosY],
        Float:z     = VehicleObjects[vehicleid][slot][vehObjectPosZ],
        Float:rx    = VehicleObjects[vehicleid][slot][vehObjectPosRX],
        Float:ry    = VehicleObjects[vehicleid][slot][vehObjectPosRY],
        Float:rz    = VehicleObjects[vehicleid][slot][vehObjectPosRZ]
    ;

    // Streamer SetFloatData ini berguna untuk memanipulasi data object float yang ada di object streamer dari variabel yang tersimpan
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_X, x);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_Y, y);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_Z, z);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_R_X, rx);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_R_Y, ry);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_R_Z, rz);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_DRAW_DISTANCE, 50);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_STREAM_DISTANCE, 50);
    return 0;
}

// Function ini berguna untuk menghapus object pada kendaraan, berdasarkan slot!
Vehicle_ObjectDelete(vehicleid, slot)
{
    if (!IsValidVehicle(PlayerVehicle[vehicleid][pVehPhysic]))
        return 0;
    
    new query_string[255];

    if (IsValidDynamicObject(VehicleObjects[vehicleid][slot][vehObject]))
        DestroyDynamicObject(VehicleObjects[vehicleid][slot][vehObject]);

    VehicleObjects[vehicleid][slot][vehObject] = INVALID_STREAMER_ID;
    VehicleObjects[vehicleid][slot][vehObjectModel] = 0;
    VehicleObjects[vehicleid][slot][vehObjectExists] = false;

    VehicleObjects[vehicleid][slot][vehObjectColor] = 0;


    VehicleObjects[vehicleid][slot][vehObjectPosX] = VehicleObjects[vehicleid][slot][vehObjectPosY] = VehicleObjects[vehicleid][slot][vehObjectPosZ] = 0.0;
    VehicleObjects[vehicleid][slot][vehObjectPosRX] = VehicleObjects[vehicleid][slot][vehObjectPosRY] = VehicleObjects[vehicleid][slot][vehObjectPosRZ] = 0.0;
    format(query_string, sizeof(query_string), "DELETE FROM `vehicle_object` WHERE `id` = '%d'", VehicleObjects[vehicleid][slot][vehObjectID]);
    mysql_tquery(g_SQL, query_string);
    return 1;
}

// Function ini berguna untuk menghapus object pada kendaraan secara keseluruhan!
Vehicle_ObjectDestroy(vehicleid)
{
    if(!IsValidVehicle(PlayerVehicle[vehicleid][pVehPhysic]))
        return 0;
    
    for(new slot = 0; slot < MAX_VEHICLE_OBJECT; slot++)
    {
        if(IsValidDynamicObject(VehicleObjects[vehicleid][slot][vehObject]))
            DestroyDynamicObject(VehicleObjects[vehicleid][slot][vehObject]);

        VehicleObjects[vehicleid][slot][vehObject] = INVALID_STREAMER_ID;
        VehicleObjects[vehicleid][slot][vehObjectModel] = 0;
        VehicleObjects[vehicleid][slot][vehObjectExists] = false;

        VehicleObjects[vehicleid][slot][vehObjectColor] = 1;

        VehicleObjects[vehicleid][slot][vehObjectPosX] = VehicleObjects[vehicleid][slot][vehObjectPosY] = VehicleObjects[vehicleid][slot][vehObjectPosZ] = 0.0;
        VehicleObjects[vehicleid][slot][vehObjectPosRX] = VehicleObjects[vehicleid][slot][vehObjectPosRY] = VehicleObjects[vehicleid][slot][vehObjectPosRZ] = 0.0;
    }
    return 1;
}

// Function ini berguna dan akan terpanggil ketika kita "ingin" meng-edit kordinat dari object kita ke kendaraan.
Vehicle_ObjectEdit(playerid, vehicleid, slot, bool:text = false)
{
    if(!IsValidVehicle(PlayerVehicle[vehicleid][pVehPhysic]))
        return 0;
        
    new
        Float:x     = VehicleObjects[vehicleid][slot][vehObjectPosX],
        Float:y     = VehicleObjects[vehicleid][slot][vehObjectPosY],
        Float:z     = VehicleObjects[vehicleid][slot][vehObjectPosZ],
        Float:rx    = VehicleObjects[vehicleid][slot][vehObjectPosRX],
        Float:ry    = VehicleObjects[vehicleid][slot][vehObjectPosRY],
        Float:rz    = VehicleObjects[vehicleid][slot][vehObjectPosRZ],
        Float:vposx,
        Float:vposy,
        Float:vposz
    ;
    if (IsValidDynamicObject(VehicleObjects[vehicleid][slot][vehObject]))
        DestroyDynamicObject(VehicleObjects[vehicleid][slot][vehObject]);
        
    VehicleObjects[vehicleid][slot][vehObject] = INVALID_STREAMER_ID;
    GetVehiclePos(PlayerVehicle[vehicleid][pVehPhysic], vposx, vposy, vposz);
    VehicleObjects[vehicleid][slot][vehObject] = CreateDynamicObject(VehicleObjects[vehicleid][slot][vehObjectModel], vposx+x, vposy+y, vposz+z, rx, ry, rz);   

    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_DRAW_DISTANCE, 15);
    Streamer_SetFloatData(STREAMER_TYPE_OBJECT, VehicleObjects[vehicleid][slot][vehObject], E_STREAMER_STREAM_DISTANCE, 15);
    Player_EditVehicleObject[playerid] = vehicleid;
    Player_EditVehicleObjectSlot[playerid] = slot;
    Player_EditingObject[playerid] = 1;
    if(text) 
    {
        Vehicle_ObjectTextSync(vehicleid, slot);
    }
    EditDynamicObject(playerid, VehicleObjects[vehicleid][slot][vehObject]);
    return 1;
}

// Function ini akan terpanggil ketika cancel editing object
ResetEditing(playerid)
{
    if(Player_EditingObject[playerid])
    {
        if(Player_EditVehicleObject[playerid] != -1 && Player_EditVehicleObjectSlot[playerid] != -1){
            Vehicle_AttachObject(Player_EditVehicleObject[playerid], Player_EditVehicleObjectSlot[playerid]);
            Vehicle_ObjectUpdate(Player_EditVehicleObject[playerid], Player_EditVehicleObjectSlot[playerid]);
            
            Player_EditVehicleObject[playerid] = -1;
            Player_EditVehicleObjectSlot[playerid] = -1;
        }
    }
    Player_EditingObject[playerid] = 0;
    return 1;
}

GetVehObjectNameByModel(model)
{
    new
        name[32];

    for (new i = 0; i < sizeof(VehObject); i ++) 
    if(VehObject[i][Model] == model) 
    {
        strcat(name, VehObject[i][ovName]);
        break;
    }
    return name;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(dialogid == DIALOG_MODSHOP)
    {
        if(response)
        {
            switch(listitem)
            {
                case 0:
				{   
					ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Transfender, "MODSHOP", transfender, sizeof(transfender));
				}
				case 1:
				{   
					ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Waa, "MODSHOP", waa, sizeof(waa));
			    }
				case 2:
				{   
					ShowPlayerSelectionMenu(playerid, MODEL_SELECTION_Loco, "MODSHOP", loco, sizeof(loco));
			    }
				case 3:
				{
                    if(AccountData[playerid][pMoney] < 10000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi! ($10,000)");

				    static 
				        vehicle;
				    
				    vehicle = Vehicle_Nearest(playerid);
				    if(vehicle != INVALID_VEHICLE_ID) 
				    {
				    	Vehicle_TextAdd(playerid, vehicle, 18661, OBJECT_TYPE_TEXT);
				    	return 1;
				    } 
				    else ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle id.");
				    
				}
				case 4:
				{
				    if(AccountData[playerid][pMoney] < 7000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi! ($7,000)");

				    static 
				        vehicle;
				    
				    vehicle = Vehicle_Nearest(playerid);
				    if(vehicle != INVALID_VEHICLE_ID) 
				    {
				    	Vehicle_SpotLightAdd(playerid, vehicle, 19281, OBJECT_TYPE_LIGHT);
				    	return 1;
				    } 
				    else ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid vehicle id.");
				}
                case 5:
                {
                    Dialog_Show(playerid, MODSHOP_CUSTOM, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Modshop",
                    "Mohon masukkan ID Object/Aksesoris yang ingin anda Pasang\nNOTE: Anda dapat melihat ID Object di: https://dev.prineside.com/en/gtasa_samp_model_id/", "Input", "Batal");
                }
            }
        }
    }
    return 1;
}

public OnPlayerSelectionMenuResponse(playerid, extraid, response, listitem, modelid)
{
    switch(extraid)
    {
        case MODEL_SELECTION_Waa:
	    {
	        if(response)
	        {
                new
                price = 20000,
                vehicleid
                ;

                if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
                    return Error(playerid, "You need to be inside vehicle as driver");

                if(AccountData[playerid][pMoney] < 20000)  
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi! ($20,000)");

                vehicleid = Vehicle_Nearest(playerid);

                if(vehicleid == -1)
                    return 0;

                Vehicle_ObjectAddObjects(playerid, vehicleid, modelid, OBJECT_TYPE_BODY);   
                
                SendCustomMessage(playerid, "MODSHOP", "Anda membeli "YELLOW"%s"WHITE" seharga "GREEN"%s", GetVehObjectNameByModel(modelid), FormatMoney(price));
            }
        } 
        case MODEL_SELECTION_Loco:
	    {
	        if(response)
	        {
                new
                price = 20000,
                vehicleid
                ;

                if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
                    return Error(playerid, "You need to be inside vehicle as driver");

                if(AccountData[playerid][pMoney] < 20000)  
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi! ($20,000)");

                vehicleid = Vehicle_Nearest(playerid);

                if(vehicleid == -1)
                    return 0;

                Vehicle_ObjectAddObjects(playerid, vehicleid, modelid, OBJECT_TYPE_BODY);

                SendCustomMessage(playerid, "MODSHOP", "Anda membeli "YELLOW"%s"WHITE" seharga "GREEN"%s", GetVehObjectNameByModel(modelid), FormatMoney(price));
            }
        } 
        case MODEL_SELECTION_Transfender:
	    {
	        if(response)
	        {
                new
                price = 20000,
                vehicleid
                ;

                if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
                    return Error(playerid, "You need to be inside vehicle as driver");

                if(AccountData[playerid][pMoney] < 20000)  
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi! ($20,000)");

                vehicleid = Vehicle_Nearest(playerid);

                if(vehicleid == -1)
                    return 0;

                Vehicle_ObjectAddObjects(playerid, vehicleid, modelid, OBJECT_TYPE_BODY);

                SendCustomMessage(playerid, "MODSHOP", "Anda membeli "YELLOW"%s"WHITE" seharga "GREEN"%s", GetVehObjectNameByModel(modelid), FormatMoney(price));
            }
        } 
    }
    return 1;
}

hook OnPlayerEditDynObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    if(response == EDIT_RESPONSE_FINAL)
    {
        if(Player_EditingObject[playerid])
        {
            new
                vehicleid = Player_EditVehicleObject[playerid],
                vehid = GetPlayerVehicleID(playerid),
                slot = Player_EditVehicleObjectSlot[playerid],
                Float:vx,
                Float:vy,
                Float:vz,
                Float:va,
                Float:real_x,
                Float:real_y,
                Float:real_z,
                Float:real_a
            ;

            GetVehiclePos(vehid, vx, vy, vz);
            GetVehicleZAngle(vehid, va); // Coba lagi

            real_x = x - vx;
            real_y = y - vy;
            real_z = z - vz;
            real_a = rz - va;

            new Float:v_size[3];
            GetVehicleModelInfo(PlayerVehicle[vehicleid][pVehModelID], VEHICLE_MODEL_INFO_SIZE, v_size[0], v_size[1], v_size[2]);
            if(	(real_x >= v_size[0] || -v_size[0] >= real_x) ||
                (real_y >= v_size[1] || -v_size[1] >= real_y) ||
                (real_z >= v_size[2] || -v_size[2] >= real_z))
            {
                SendCustomMessage(playerid, "MODSHOP", "Posisi object terlalu jauh dari body kendaraan!");
                ResetEditing(playerid);
                return 1;
            }

            VehicleObjects[vehicleid][slot][vehObjectPosX] = real_x;
            VehicleObjects[vehicleid][slot][vehObjectPosY] = real_y;
            VehicleObjects[vehicleid][slot][vehObjectPosZ] = real_z;
            VehicleObjects[vehicleid][slot][vehObjectPosRX] = rx;
            VehicleObjects[vehicleid][slot][vehObjectPosRY] = ry;
            VehicleObjects[vehicleid][slot][vehObjectPosRZ] = real_a;
		
			// Streamer_UpdateEx(playerid, VehicleObjects[vehicleid][slot][vehObjectPosX], VehicleObjects[vehicleid][slot][vehObjectPosY], VehicleObjects[vehicleid][slot][vehObjectPosZ]);
			if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_BODY)
			{
				SetDynamicObjectMaterial(VehicleObjects[vehicleid][slot][vehObject], 0, VehicleObjects[vehicleid][slot][vehObjectModel], "none", "none", RGBAToARGB(ColorList[VehicleObjects[vehicleid][slot][vehObjectColor]]));
			}
			else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_TEXT)
			{
				SetDynamicObjectMaterialText(VehicleObjects[vehicleid][slot][vehObject], 0, VehicleObjects[vehicleid][slot][vehObjectText], 130, VehicleObjects[vehicleid][slot][vehObjectFont], VehicleObjects[vehicleid][slot][vehObjectFontSize], 1, RGBAToARGB(ColorList[VehicleObjects[vehicleid][slot][vehObjectFontColor]]), 0, OBJECT_MATERIAL_TEXT_ALIGN_CENTER);
			}
			AttachDynamicObjectToVehicle(VehicleObjects[vehicleid][slot][vehObject], PlayerVehicle[vehicleid][pVehPhysic], real_x, real_y, real_z, rx, ry, real_a);
        	Vehicle_ObjectUpdate(vehicleid, slot);
            Vehicle_ObjectSave(vehicleid, slot);
			
            if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_BODY)
            {
                Dialog_Show(playerid, VACCSE, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nChange Color\nRemove Modification\nSave", "Select", "Back");
            }
            else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_TEXT)
            {
                Dialog_Show(playerid, VACCSE1, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nText Name\nText Size\nText Font\nText Color\nRemove Modification\nSave", "Select", "Back");
            }
            else if(VehicleObjects[vehicleid][slot][vehObjectType] == OBJECT_TYPE_LIGHT)
            {
                Dialog_Show(playerid, VACCSE2, DIALOG_STYLE_LIST, "Edit Component", "Position\nPosition (Manual)\nRemove Modification\nSave", "Select", "Back");
            }
			return 1;
		}
    }
    if(response == EDIT_RESPONSE_CANCEL)
    {
        if(Player_EditingObject[playerid])
        {
            ResetEditing(playerid);
			return 1;
        }
    }
    return 1;
}