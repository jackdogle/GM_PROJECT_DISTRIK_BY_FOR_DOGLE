#include <YSI\y_hooks>

// Defines
#define IsMowerWorking(%0)      mower_working[%0]
#define SetMowerWorking(%0,%1)   mower_working[%0] = %1

new bool: mower_working[MAX_PLAYERS] = {false, ...},
    MowerRespawnCounter[MAX_PLAYERS] = {0, ...},
    MowerCutGrass[MAX_PLAYERS] = {0, ...},
    MowerVehicleID[MAX_PLAYERS] = {RETURN_INVALID_VEHICLE_ID, ...},
    STREAMER_TAG_OBJECT:MowerGrass[MAX_PLAYERS][107],
    STREAMER_TAG_AREA:MowerGrassArea[MAX_PLAYERS][107];

hook OnPlayerConnect(playerid)
{
    MowerCutGrass[playerid] = 0;
    MowerVehicleID[playerid] = RETURN_INVALID_VEHICLE_ID;
    MowerRespawnCounter[playerid] = 0;
    SetMowerWorking(playerid, false);
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(IsMowerWorking(playerid))
    {
        MowerRespawnCounter[playerid] = 0;
        MowerCutGrass[playerid] = 0;
        SetVehicleToRespawn(MowerVehicleID[playerid]);
        VehicleCore[MowerVehicleID[playerid]][vCoreFuel] = MAX_FUEL_FULL;
        SetValidVehicleHealth(MowerVehicleID[playerid], 1000.0);
        MowerVehicleID[playerid] = RETURN_INVALID_VEHICLE_ID;
        RemoveGrassMower(playerid);
    }
    return 1;
}

static Float:GrassPos[][] = 
{
    {2053.505615, -1197.612792, 22.780832, 0.000000, 0.000000, 0.000000},
    {2051.433105, -1202.598876, 22.650829, 0.000000, 0.000000, 22.199996},
    {2054.811767, -1207.909912, 22.780832, -0.099999, 0.000000, 22.299999},
    {2052.125000, -1192.402709, 22.720829, 0.000000, 0.000000, -42.000000},
    {2053.235107, -1187.722778, 22.720829, 0.000000, 0.000000, 56.399997},
    {2044.584594, -1198.242797, 22.530826, 0.000000, -2.399999, 0.000000},
    {2044.584594, -1193.733032, 22.530826, 0.000000, -2.399999, -19.499998},
    {2045.543701, -1190.343261, 22.571027, 0.000000, -2.399999, 8.899999},
    {2043.414916, -1202.891601, 22.355173, -2.499999, -2.399999, 41.599994},
    {2040.242309, -1201.853271, 21.939840, 0.000000, -9.500000, 0.000000},
    {2039.534545, -1197.847412, 21.808198, -8.799999, -8.399999, 94.399993},
    {2040.588500, -1193.520385, 22.033800, 0.000000, -8.399999, 18.400001},
    {2040.915161, -1188.631103, 22.196874, 0.000000, -8.399999, 22.500000},
    {2049.308349, -1225.251586, 22.620712, 0.000000, -1.999906, -13.000000},
    {2053.305175, -1224.162597, 22.748098, 0.000000, -1.999906, -13.000000},
    {2053.119628, -1219.009277, 22.701339, 0.000000, -1.999906, -13.000000},
    {2051.443359, -1229.932128, 22.620023, 0.000000, -1.999906, -13.000000},
    {2046.632690, -1231.243286, 22.467140, 0.000000, -7.999906, -13.000000},
    {2045.334594, -1226.520507, 22.140077, 0.000000, -7.999906, -13.000000},
    {2047.160522, -1221.126342, 22.245851, 0.000000, -7.999906, -40.799995},
    {2049.652099, -1215.652587, 22.387807, 0.000000, -7.999906, -31.399999},
    {2049.833007, -1206.602294, 22.445421, -0.099999, 0.000000, 22.299999},
    {2048.502441, -1242.845214, 22.700807, -0.112491, -1.512646, -29.799505},
    {2052.644287, -1242.958129, 22.793310, -0.112491, -1.512646, -29.799505},
    {2053.955566, -1237.971069, 22.748172, -0.112491, -1.512646, -29.799505},
    {2049.193359, -1247.943115, 22.681486, -0.112491, -1.512646, -29.799505},
    {2044.207885, -1247.807495, 22.570589, -0.112491, -7.512646, -29.799505},
    {2044.327514, -1242.910400, 22.254867, -0.112491, -7.512646, -29.799505},
    {2047.635498, -1238.274414, 22.344703, -0.326757, -7.621347, -57.598892},
    {2051.604003, -1233.754760, 22.464912, -0.260542, -7.573062, -48.199008},
    {2034.661865, -1242.453979, 22.423521, -1.568473, -1.682430, -40.781494},
    {2038.707397, -1243.352172, 22.476993, -1.568473, -1.682430, -40.781494},
    {2040.942993, -1238.708374, 22.301376, -1.568473, -1.682430, -40.781494},
    {2034.369873, -1247.589355, 22.517158, -1.568473, -1.682430, -40.781494},
    {2029.500000, -1246.508544, 22.453256, -1.568473, -7.682430, -40.781494},
    {2030.544799, -1241.731811, 22.021249, -1.568473, -7.682430, -40.781494},
    {2034.675537, -1237.810180, 21.968740, -1.535462, -8.450770, -68.591873},
    {2039.432617, -1234.128295, 21.942695, -1.588477, -8.193876, -59.188529},
    {2021.984252, -1237.952270, 21.853507, -1.568478, -1.682424, -58.481491},
    {2025.565185, -1240.037841, 21.906980, -1.568478, -1.682424, -58.481491},
    {2029.106811, -1236.293579, 21.731363, -1.568478, -1.682424, -58.481491},
    {2020.144653, -1242.755737, 21.947145, -1.568478, -1.682424, -58.481491},
    {2015.833984, -1240.245483, 21.883243, -1.568478, -7.682424, -58.481491},
    {2018.281616, -1236.012573, 21.451236, -1.568478, -7.682424, -58.481491},
    {2023.409179, -1233.532470, 21.398727, -1.535469, -8.450767, -86.291862},
    {2029.060424, -1231.471069, 21.372682, -1.588483, -8.193872, -76.888519},
    {2021.984252, -1225.888793, 21.211269, 0.576496, 1.812092, -58.451213},
    {2025.565185, -1227.973022, 21.115491, 0.576496, 1.812092, -58.451213},
    {2029.106811, -1224.225708, 21.208028, 0.576496, 1.812092, -58.451213},
    {2020.144653, -1230.686767, 20.961233, 0.576496, 1.812092, -58.451213},
    {2015.833984, -1228.178344, 21.076969, 0.576496, -4.187906, -58.451213},
    {2018.281616, -1223.925415, 20.948711, 0.576496, -4.187906, -58.451213},
    {2023.409179, -1221.447875, 21.073656, -1.266616, -4.358335, -86.191741},
    {2029.060424, -1219.389892, 21.195062, -0.655304, -4.200643, -76.810287},
    {2037.555908, -1225.420043, 21.820796, 1.743634, 0.273162, -25.309028},
    {2041.694824, -1225.209594, 21.863006, 1.743634, 0.273162, -25.309028},
    {2042.610229, -1220.137084, 22.020944, 1.743634, 0.273162, -25.309028},
    {2038.644165, -1230.442138, 21.571739, 1.743634, 0.273162, -25.309028},
    {2033.662231, -1230.695922, 21.521375, 1.743634, -5.726837, -25.309028},
    {2033.392822, -1225.795898, 21.418107, 1.743634, -5.726837, -25.309028},
    {2036.328125, -1220.921020, 21.673759, 0.482795, -5.176326, -53.086303},
    {2039.930908, -1216.111572, 21.947450, 0.937309, -5.292950, -43.696567},
    {2033.224731, -1203.477661, 21.420011, -0.740774, -6.193567, 17.157323},
    {2036.113891, -1200.529296, 21.788591, -0.740774, -6.193567, 17.157323},
    {2033.371826, -1196.166748, 21.579584, -0.740774, -6.193567, 17.157323},
    {2037.413330, -1206.451660, 21.701194, -0.740774, -6.193567, 17.157323},
    {2033.935913, -1210.000976, 21.258026, -0.740774, -12.193565, 17.157323},
    {2030.471923, -1206.567382, 20.705989, -0.740774, -12.193565, 17.157323},
    {2029.331542, -1200.987060, 20.779586, 1.298809, -12.055824, -10.569517},
    {2028.722167, -1195.004516, 20.932435, 0.619559, -12.213147, -1.192732},
    {2022.113037, -1188.190307, 20.298437, 6.838222, 1.410870, -78.032859},
    {2024.784057, -1191.355834, 20.442510, 6.838222, 1.410870, -78.032859},
    {2029.338989, -1189.020019, 21.068225, 6.838222, 1.410870, -78.032859},
    {2018.819702, -1192.085449, 19.626821, 6.838222, 1.410870, -78.032859},
    {2015.604003, -1188.275390, 19.453805, 6.838222, -4.589127, -78.032859},
    {2019.326049, -1185.092163, 19.780216, 6.838222, -4.589127, -78.032859},
    {2024.940673, -1184.485839, 20.526386, 4.460627, -1.793450, -105.870933},
    {2030.906127, -1184.450561, 21.298171, 5.412963, -2.603059, -96.484298},
    {2035.425781, -1190.362304, 21.572568, -0.740774, -6.193567, 17.157323},
    {2024.899780, -1201.846557, 20.223121, 1.298809, -9.655824, -10.569517},
    {2023.346069, -1196.454223, 20.109920, 1.298809, -7.555824, -58.569503},
    {2018.199829, -1197.608886, 19.446096, -4.201190, -7.555824, 23.230493},
    {2018.786743, -1202.720581, 19.589544, -7.201189, -7.555824, 47.730491},
    {2049.677490, -1176.125610, 22.602046, -0.372837, -1.661748, 19.699846},
    {2052.453125, -1173.048950, 22.695138, -0.372837, -1.661748, 19.699846},
    {2049.512695, -1168.813232, 22.623893, -0.372837, -1.661748, 19.699846},
    {2054.002929, -1178.910888, 22.609416, -0.372837, -1.661748, 19.699846},
    {2050.662353, -1182.614257, 22.497812, -0.372837, -7.661748, 19.699846},
    {2047.017456, -1179.343994, 22.156454, -0.372837, -7.661748, 19.699846},
    {2045.640380, -1173.817504, 22.222015, -0.487516, -7.874667, -8.100689},
    {2044.780395, -1167.864013, 22.318561, -0.460515, -7.796722, 1.299568},
    {2037.220581, -1177.220947, 22.292041, -0.372834, -1.661741, 38.799839},
    {2038.836669, -1173.405395, 22.385133, -0.372834, -1.661741, 38.799839},
    {2034.672119, -1170.364990, 22.313888, -0.372834, -1.661741, 38.799839},
    {2042.219238, -1178.437500, 22.299411, -0.372834, -1.661741, 38.799839},
    {2040.274536, -1183.030151, 22.187807, -0.372834, -7.661741, 38.799839},
    {2035.760131, -1181.132568, 21.846448, -0.372834, -7.661741, 38.799839},
    {2032.650512, -1176.360839, 21.912010, -0.487517, -7.874659, 10.999300},
    {2029.889770, -1171.016601, 22.008556, -0.460515, -7.796714, 20.399559},
    {2029.400634, -1157.987915, 21.942035, -0.372830, -1.661735, 69.799819},
    {2028.820800, -1153.884887, 22.035127, -0.372830, -1.661735, 69.799819},
    {2023.685058, -1153.423706, 21.963882, -0.372830, -1.661735, 69.799819},
    {2034.311889, -1156.456176, 21.949405, -0.372830, -1.661735, 69.799819},
    {2035.010375, -1161.394409, 21.837800, -0.372830, -7.661735, 69.799819},
    {2030.163330, -1162.093017, 21.496442, -0.372830, -7.661735, 69.799819},
    {2025.040405, -1159.604370, 21.562004, -0.487516, -7.874651, 41.999290},
    {2019.921386, -1156.445312, 21.658550, -0.460512, -7.796707, 51.399547}
};

SpawnGrassMower(playerid)
{
    for(new i = 0; i < 107; i ++)
    {
        MowerGrass[playerid][i] = CreateDynamicObject(14402, GrassPos[i][0], GrassPos[i][1], GrassPos[i][2], GrassPos[i][3], GrassPos[i][4], GrassPos[i][5], 0, 0, playerid, 50.0, 50.0, -1);
        MowerGrassArea[playerid][i] = CreateDynamicSphere(GrassPos[i][0], GrassPos[i][1], GrassPos[i][2], 1.8, 0, 0, playerid);
    }
    return 1;
}

RemoveGrassMower(playerid)
{
    for(new i = 0; i < 107; i ++)
    {
        if(DestroyDynamicObject(MowerGrass[playerid][i]))
            MowerGrass[playerid][i] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        if(DestroyDynamicArea(MowerGrassArea[playerid][i]))
            MowerGrassArea[playerid][i] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
    }
    return 1;
}

hook OnScriptInit()
{
    MowerVehicles[0] = AddStaticVehicleEx(572, 2122.9150, -1182.3804, 23.6142, 92.6620, 126, 126, 60000, 0);
	MowerVehicles[1] = AddStaticVehicleEx(572, 2122.9841, -1179.1329, 23.6166, 90.0594, 126, 126, 60000, 0);
	MowerVehicles[2] = AddStaticVehicleEx(572, 2122.9663, -1175.8353, 23.6915, 90.3885, 126, 126, 60000, 0);
    for(new i = 0; i < sizeof(MowerVehicles); i ++)
    {
        VehicleCore[MowerVehicles[i]][vCoreFuel] = MAX_FUEL_FULL;
        SetValidVehicleHealth(MowerVehicles[i], 1000.0);
        SetVehicleNumberPlate(MowerVehicles[i], "MOWING");
    }

    /* Mapping Mower */
    static tmpobjid;
    tmpobjid = CreateDynamicObject(970, 2113.670898, -1185.412963, 23.410762, 0.039101, -1.399432, 89.200439, 0, 0, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 1649, "wglass", "carshowwin2", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 18646, "matcolours", "grey-93-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(970, 2113.728271, -1181.274414, 23.511877, 0.039101, -1.399432, 89.200439, 0, 0, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 1649, "wglass", "carshowwin2", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 18646, "matcolours", "grey-93-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(970, 2113.786376, -1177.135864, 23.612991, 0.039101, -1.399432, 89.200439, 0, 0, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 1649, "wglass", "carshowwin2", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 18646, "matcolours", "grey-93-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(2662, 2124.583251, -1178.859741, 26.545028, 0.000000, 0.000000, 270.000000, 0, 0, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-93-percent", 0x00000000);
	SetDynamicObjectMaterialText(tmpobjid, 0, "{ffffff}Verona Mower", 130, "Arial", 60, 0, 0x00000000, 0x00000001, 1);
}

IsMowerVehicles(vehicleid)
{
    for(new i = 0; i < sizeof(MowerVehicles); i++)
    {
        if(vehicleid == MowerVehicles[i]) return 1;
    }
    return 0;
}

CancelMower(playerid, vehicleid)
{
    if(IsMowerWorking(playerid))
    {
        MowerVehicleID[playerid] = RETURN_INVALID_VEHICLE_ID;
        MowerCutGrass[playerid] = 0;
        MowerRespawnCounter[playerid] = 0;
        SetMowerWorking(playerid, false);
        PlayerTextDrawHide(playerid, BusWait[playerid][0]);
        
        SetVehicleToRespawn(vehicleid);
        VehicleCore[vehicleid][vCoreFuel] = MAX_FUEL_FULL;
        SetValidVehicleHealth(vehicleid, 1000.0);
        RemoveGrassMower(playerid);
    }
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(newstate == PLAYER_STATE_DRIVER && !IsMowerWorking(playerid) && IsMowerVehicles(vehicleid))
    {
        if(!AccountData[playerid][pMowerTime])
        {
            SetCameraBehindPlayer(playerid);
            ShowPlayerDialog(playerid, DIALOG_MOWER_START, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Mower Sidejob",
            "Apakah anda ingin memulai tugas mowing?\nAnda akan menerima bayaran berdasarkan rumput yang anda potong", "Iya", "Tidak");   
        }
        else
        {
            ShowTDN(playerid, NOTIFICATION_WARNING, sprintf("Anda harus menunggu %d menit untuk bekerja kembali!", AccountData[playerid][pMowerTime]/60));
            return RemovePlayerFromVehicle(playerid);
        }
    }   
    if(oldstate == PLAYER_STATE_DRIVER && IsMowerWorking(playerid))
    {
        CancelMower(playerid, MowerVehicleID[playerid]);
        SendClientMessage(playerid, -1, "[i] Anda turun dari kendaraan mowing, tugas anda sebagai pemotong rumput telah gagal!");
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_MOWER_START:
        {
            if(response)
            {
                MowerVehicleID[playerid] = GetPlayerVehicleID(playerid);
                MowerRespawnCounter[playerid] = 80;
                SpawnGrassMower(playerid);
                SetMowerWorking(playerid, true);
                PlayerTextDrawSetString(playerid, BusWait[playerid][0], "~g~Sidejob Mowing: ~w~Pergi dan ~y~potong rumput~n~~w~ sebanyak banyaknya!");
                PlayerTextDrawShow(playerid, BusWait[playerid][0]);
                SetTimerEx("HideNotifDelivery", 10000, false, "d", playerid);
            }
            else
            {
                Info(playerid, "Anda menolak bekerja sebagai Pemotong Rumput!");
                RemovePlayerFromVehicle(playerid);
            }
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA: areaid)
{
    if(IsMowerWorking(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        for (new i = 0; i < 107; i++)
        {
            if(areaid == MowerGrassArea[playerid][i])
            {
                if(IsValidDynamicArea(MowerGrassArea[playerid][i])) 
                {
                    DestroyDynamicArea(MowerGrassArea[playerid][i]);
                    MowerGrassArea[playerid][i] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
                }
                
                if(IsValidDynamicObject(MowerGrass[playerid][i])) 
                {
                    DestroyDynamicObject(MowerGrass[playerid][i]);
                    MowerGrass[playerid][i] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
                }

                MowerCutGrass[playerid] += 6;
                PlayerTextDrawSetString(playerid, BusWait[playerid][0], sprintf("~w~%d ~g~Rumput", MowerCutGrass[playerid]));
                PlayerTextDrawShow(playerid, BusWait[playerid][0]);
            }
        }
    }
    return 1;
}

ptask RespawnMowerVehicle[1000](playerid)
{
    if(IsMowerWorking(playerid))
    {
        if(MowerRespawnCounter[playerid] > 0)
        {
            MowerRespawnCounter[playerid] --;
            if(!MowerRespawnCounter[playerid])
            {
                new value = MowerCutGrass[playerid] * 4;
                GiveMoney(playerid, value);
                Info(playerid, "Tugas mowing sudah selesai, anda mendapatkan "GREEN"%s", FormatMoney(value));
                PlayerPlaySound(playerid, 1138, 0.0, 0.0, 0.0);
                
                AccountData[playerid][pMowerTime] = 1800;
                CancelMower(playerid, MowerVehicleID[playerid]);
            }
            GameTextForPlayer(playerid, sprintf("%d", MowerRespawnCounter[playerid]), 1000, 4);
        }
    }
    return 1;
}

task MowingVehicle[1000]()
{
    static Float:maxspeed = 30.0;
    if(IsValidVehicle(MowerVehicles[0]))
    {
        SetVehicleSpeedCap(MowerVehicles[0], maxspeed);
    }
    if(IsValidVehicle(MowerVehicles[1]))
    {
        SetVehicleSpeedCap(MowerVehicles[1], maxspeed);
    }
    if(IsValidVehicle(MowerVehicles[2]))
    {
        SetVehicleSpeedCap(MowerVehicles[2], maxspeed);
    }
    return 1;
}