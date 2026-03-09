CMD:buymod(playerid, params[])
{
    new vehicleid, string[1024], count;

    if(!ModshopVehicleArea(playerid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak ada di Area Modshop!");

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengendarai kendaraan!");
    
    if(!AccountData[playerid][pVip]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pengguna Vip!");
    
    vehicleid = Vehicle_Nearest(playerid);

    if(vehicleid == -1)
        return 0;
    
    if(Vehicle_IsOwner(playerid, vehicleid))
    {
        format(string, sizeof(string), "#Slot\tMod Aksesoris\tModel\n");
        if(AccountData[playerid][pVip] == 1)
        {
            for (new i = 0; i < 5; i ++)
            {
                if(VehicleObjects[vehicleid][i][vehObjectExists])
                {
                    if(VehicleObjects[vehicleid][i][vehObjectType] == OBJECT_TYPE_BODY)
                    {
                        format(string,sizeof(string),"%s#%d\t"GREEN_E"Mod\t%s\n", string, i, GetVehObjectNameByModel(VehicleObjects[vehicleid][i][vehObjectModel]));
                    }
                    else if(VehicleObjects[vehicleid][i][vehObjectType] == OBJECT_TYPE_TEXT)
                    {
                        format(string,sizeof(string),"%s#%d\t"GREEN_E"Sticker\t%s\n", string, i, VehicleObjects[vehicleid][i][vehObjectText]);
                    }
                    else if(VehicleObjects[vehicleid][i][vehObjectType] == OBJECT_TYPE_LIGHT)
                    {
                        format(string,sizeof(string),"%s#%d\t"GREEN_E"SpotLight\t%s\n", string, i, VehicleObjects[vehicleid][i][vehObjectText]);
                    }
                }
                else
                {
                    format(string, sizeof(string), "%s#New\tMod\n", string);
                }
                if (count < 10)
                {
                    ListedVehObject[playerid][count] = i;
                    count = count + 1;
                }
            }
        }
        else if(AccountData[playerid][pVip] == 2)
        {
            for (new i = 0; i < 8; i ++)
            {
                if(VehicleObjects[vehicleid][i][vehObjectExists])
                {
                    if(VehicleObjects[vehicleid][i][vehObjectType] == OBJECT_TYPE_BODY)
                    {
                        format(string,sizeof(string),"%s#%d\t"GREEN_E"Mod\t%s\n", string, i, GetVehObjectNameByModel(VehicleObjects[vehicleid][i][vehObjectModel]));
                    }
                    else if(VehicleObjects[vehicleid][i][vehObjectType] == OBJECT_TYPE_TEXT)
                    {
                        format(string,sizeof(string),"%s#%d\t"GREEN_E"Sticker\t%s\n", string, i, VehicleObjects[vehicleid][i][vehObjectText]);
                    }
                    else if(VehicleObjects[vehicleid][i][vehObjectType] == OBJECT_TYPE_LIGHT)
                    {
                        format(string,sizeof(string),"%s#%d\t"GREEN_E"SpotLight\t%s\n", string, i, VehicleObjects[vehicleid][i][vehObjectText]);
                    }
                }
                else
                {
                    format(string, sizeof(string), "%s#New\tMod\n", string);
                }
                if (count < 10)
                {
                    ListedVehObject[playerid][count] = i;
                    count = count + 1;
                }
            }
        }
        else if(AccountData[playerid][pVip] == 3)
        {
            for (new i = 0; i < MAX_VEHICLE_OBJECT; i ++)
            {
                if(VehicleObjects[vehicleid][i][vehObjectExists])
                {
                    if(VehicleObjects[vehicleid][i][vehObjectType] == OBJECT_TYPE_BODY)
                    {
                        format(string,sizeof(string),"%s#%d\t"GREEN_E"Mod\t%s\n", string, i, GetVehObjectNameByModel(VehicleObjects[vehicleid][i][vehObjectModel]));
                    }
                    else if(VehicleObjects[vehicleid][i][vehObjectType] == OBJECT_TYPE_TEXT)
                    {
                        format(string,sizeof(string),"%s#%d\t"GREEN_E"Sticker\t%s\n", string, i, VehicleObjects[vehicleid][i][vehObjectText]);
                    }
                    else if(VehicleObjects[vehicleid][i][vehObjectType] == OBJECT_TYPE_LIGHT)
                    {
                        format(string,sizeof(string),"%s#%d\t"GREEN_E"SpotLight\t%s\n", string, i, VehicleObjects[vehicleid][i][vehObjectText]);
                    }
                }
                else
                {
                    format(string, sizeof(string), "%s#New\tMod\n", string);
                }
                if (count < 10)
                {
                    ListedVehObject[playerid][count] = i;
                    count = count + 1;
                }
            }
        }
        else
        {
            for (new i = 0; i < 3; i ++)
            {
                if(VehicleObjects[vehicleid][i][vehObjectExists])
                {
                    if(VehicleObjects[vehicleid][i][vehObjectType] == OBJECT_TYPE_BODY)
                    {
                        format(string,sizeof(string),"%s#%d\t"GREEN_E"Mod\t%s\n", string, i, GetVehObjectNameByModel(VehicleObjects[vehicleid][i][vehObjectModel]));
                    }
                    else if(VehicleObjects[vehicleid][i][vehObjectType] == OBJECT_TYPE_TEXT)
                    {
                        format(string,sizeof(string),"%s#%d\t"GREEN_E"Sticker\t%s\n", string, i, VehicleObjects[vehicleid][i][vehObjectText]);
                    }
                    else if(VehicleObjects[vehicleid][i][vehObjectType] == OBJECT_TYPE_LIGHT)
                    {
                        format(string,sizeof(string),"%s#%d\t"GREEN_E"SpotLight\t%s\n", string, i, VehicleObjects[vehicleid][i][vehObjectText]);
                    }
                }
                else
                {
                    format(string, sizeof(string), "%s#New\tMod\n", string);
                }
                if (count < 10)
                {
                    ListedVehObject[playerid][count] = i;
                    count = count + 1;
                }
            }
        }
    
        if(!count) 
        {
            ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada aksesoris terpasang di kendaraan anda!");
        }
        else 
        {
            Player_EditVehicleObject[playerid] = vehicleid;
            Dialog_Show(playerid, EditingVehObject, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Modshop", string, "Select", "Exit");
        }
    }
    return 1;
}