#include <YSI\y_hooks>

static Float:ElectricanPoint[][] = 
{
    {-2190.3354, -2276.8242, 30.6250},
    {-2184.3342, -2298.7539, 30.6250},
    {-2148.5894, -2327.5417, 30.6250},
    {-2130.4409, -2277.1179, 30.6250},
    {-2106.5620, -2271.4280, 30.6250},
    {-2178.1440, -2415.1418, 35.2969},
    {-2192.4419, -2426.2112, 35.5162},
    {-2180.6367, -2431.6433, 35.5234},
    {-2220.6235, -2475.2468, 30.6139},
    {-2131.6074, -2430.3279, 30.6250},
    
    {223.9914, -246.5235, 1.5781},
    {225.8676, -196.4063, 1.5781},
    {262.3879, -183.6392, 8.5786},
    {258.5279, -198.7893, 7.0613},
    {247.5627, -169.3586, 10.0963},
    {242.2371, -107.5575, 1.5781},
    {223.4564, -86.1347, 1.5781},
    {241.8296, -61.7668, 1.5781},
    {253.1825, -54.7106, 5.8828},
    {192.8220, -30.9871, 1.5781},

    {-54.3380, 1034.7932, 19.7422},
    {-48.2281, 987.8119, 19.8003},
    {-46.5270, 1178.8593, 19.3911},
    {-166.9717, 1107.2544, 19.7422},
    {-168.7734, 1078.3673, 19.7422},
    {-2311.8408, -79.2167, 35.3203},
    {-2362.5996, -79.4669, 35.3203},
    {-2506.7708, -60.5819, 25.6172},
    {-2012.4132, 158.1430, 27.6875},
    {-1999.7120, -104.7226, 35.8594}
};

#define IsElectricanWorking(%0)         PlayerElectricJob[%0][DurringElectricJob]
#define SetElectricanWorking(%0,%1)     PlayerElectricJob[%0][DurringElectricJob] = %1

new ToggleElectric = 0;

enum e_electricjob {
    ElectricGroup[128],
    ElectricGroupID,
    ElectricWithPlayerID,
    ElectricVehicle,
    bool: ElectricLocked,
    ElectricFixCount,
    ElectricLeader,

    bool:DurringElectricJob
};
new PlayerElectricJob[MAX_PLAYERS][e_electricjob];

new
    STREAMER_TAG_CP:ElectricCheckpoint[MAX_PLAYERS][30],
    STREAMER_TAG_MAP_ICON:ElectricMapIcon[MAX_PLAYERS][30],
    STREAMER_TAG_RACE_CP:ElectricFinishPoint[MAX_PLAYERS];

CMD:toggleelectric(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 4) 
        return PermissionError(playerid);

    new reason[64];
    if(sscanf(params, "s[64]", reason)) 
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/toggleelectric [alasan (kenapa ditutup/dibuka)]");
    
    if(strlen(reason) < 5) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Setidaknya alasan lebih dari 5 huruf!");
    
    if(!ToggleElectric)
    {
        ToggleElectric = 1;
        SendClientMessageToAllEx(X11_ARWIN, "[AdmCmd]"RED" %s"ARWIN1" telah menutup job electric. Alasan: "RED"%s", AccountData[playerid][pAdminname], reason);
    }
    else
    {
        ToggleElectric = 0;
        SendClientMessageToAllEx(X11_ARWIN, "[AdmCmd]"RED" %s"ARWIN1" telah membuka job electric. Alasan: "RED"%s", AccountData[playerid][pAdminname], reason);
    }
    return 1;
}

ResetVariableElectric(playerid)
{
    SetElectricanWorking(playerid, false);
    PlayerElectricJob[playerid][ElectricGroup][0] = EOS;
    PlayerElectricJob[playerid][ElectricGroupID] = -1;
    PlayerElectricJob[playerid][ElectricLeader] = INVALID_PLAYER_ID;
    PlayerElectricJob[playerid][ElectricWithPlayerID] = INVALID_PLAYER_ID;
    PlayerElectricJob[playerid][ElectricVehicle] = INVALID_VEHICLE_ID;
    PlayerElectricJob[playerid][ElectricLocked] = false;
    PlayerElectricJob[playerid][ElectricFixCount] = 0;
    for(new i = 0; i < 30; i ++)
    {
        if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
            ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
            ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
    }
    if(DestroyDynamicRaceCP(ElectricFinishPoint[playerid]))
        ElectricFinishPoint[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
    return 1;
}

SetElectricanSkin(playerid, gender)
{
    switch(gender)
    {
        case 1: // Laki
        {
            SetPlayerSkin(playerid, 16);
        }
        case 2: // Cew
        {
            SetPlayerSkin(playerid, 157);
        }
    }
    return 1;
}

hook OnGameModeInitEx()
{
    ToggleElectric = 0;
    CreateDynamicPickup(1210, 23, -2520.9807, -624.4470, 132.7828, 0, 0, -1, 50.0, -1, 0);
    CreateDynamic3DTextLabel(""LIGHTGREY"[Electric Job]\n"GREEN"[Y]"WHITE" untuk akses electrican job", -1, -2520.9807, -624.4470, 132.7828 + 0.5, 50.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, -1, 50.0, -1, 0);
    return 1;
}

hook OnPlayerConnect(playerid)
{
    ResetVariableElectric(playerid);
    return 1;
}

hook OnVehicleSpawn(vehicleid)
{
    foreach(new playerid : Player) if (IsPlayerConnected(playerid))
    {
        if(PlayerElectricJob[playerid][ElectricVehicle] == vehicleid)
        {
            if(PlayerElectricJob[playerid][ElectricVehicle] != INVALID_VEHICLE_ID)
                DestroyVehicle(PlayerElectricJob[playerid][ElectricVehicle]);
                

            PlayerElectricJob[playerid][ElectricVehicle] = INVALID_VEHICLE_ID;
            PlayerElectricJob[playerid][ElectricLocked] = false;
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(IsElectricanWorking(playerid))
    {
        SetElectricanWorking(playerid, false);

        for(new i = 0; i < 30; i ++) {
            if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
            
            if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            
        }
        if(DestroyDynamicRaceCP(ElectricFinishPoint[playerid]))
            ElectricFinishPoint[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
        
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] != INVALID_PLAYER_ID && PlayerElectricJob[playerid][ElectricLeader] == playerid)
        {
            new TeamID = PlayerElectricJob[playerid][ElectricWithPlayerID];
            PlayerElectricJob[TeamID][ElectricVehicle] = PlayerElectricJob[playerid][ElectricVehicle];
            PlayerElectricJob[TeamID][ElectricLocked] = PlayerElectricJob[playerid][ElectricLocked];
            PlayerElectricJob[playerid][ElectricVehicle] = INVALID_VEHICLE_ID;
            PlayerElectricJob[playerid][ElectricLocked] = false;
            Info(TeamID, "Leader dari pekerjaan Electric anda terputus dari server. Kendaraan dialihkan ke anda!");
        }
        else if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID && PlayerElectricJob[playerid][ElectricLeader] == playerid)
        {
            if(IsValidVehicle(PlayerElectricJob[playerid][ElectricVehicle]))
            {
                DestroyVehicle(PlayerElectricJob[playerid][ElectricVehicle]);
                PlayerElectricJob[playerid][ElectricVehicle] = INVALID_PLAYER_ID;
                PlayerElectricJob[playerid][ElectricLocked] = false;
            }
        }
    }
    ResetVariableElectric(playerid);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.5, -2520.9807, -624.4470, 132.7828))
        {
            if(ToggleElectric == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Job Electric sedang dimatikan karena alasan tertentu.");
            
            Dialog_Show(playerid, ElectricanMenu, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Electrican Job",
            "Membuat group baru\
            \nUndang ke dalam group\
            \nKeluarkan dari group\
            \nJoin Group\
            \nMulai Pekerjaan\
            \nBerhenti pekerjaan", "Pilih", "Batal");
        }
    }
    return 1;
}

hook OnPlayerEnterDynRaceCP(playerid, STREAMER_TAG_RACE_CP:checkpointid)
{
    if(IsElectricanWorking(playerid))
    {
        if(checkpointid == ElectricFinishPoint[playerid])
        {
            if(PlayerElectricJob[playerid][ElectricLeader] == playerid)
            {
                DestroyVehicle(PlayerElectricJob[playerid][ElectricVehicle]);
                PlayerElectricJob[playerid][ElectricVehicle] = INVALID_VEHICLE_ID;
                PlayerElectricJob[playerid][ElectricLocked] = false;
            }

            SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
            ResetVariableElectric(playerid);
        }
    }
    return 1;
}

hook OnPlayerEnterDynamicCP(playerid, STREAMER_TAG_CP:checkpointid)
{
    if(IsElectricanWorking(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && GetPVarInt(playerid, "IsPlayerHaveKit") == 1)
    {
        if(checkpointid == ElectricCheckpoint[playerid][0])
        {
            Dialog_Show(playerid, FixElectric1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"RED"[KUNING] "GREEN"[BIRU]" ""WHITE"[MERAH]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][1])
        {
            Dialog_Show(playerid, FixElectric2, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"GREEN"[MERAH] "YELLOW"[HIJAU]" ""RED"[UNGU]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][2])
        {
            Dialog_Show(playerid, FixElectric3, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"PURPLE"[ABU] "RED"[KUNING]" ""YELLOW"[UNGU]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }

        if(checkpointid == ElectricCheckpoint[playerid][3])
        {
            Dialog_Show(playerid, FixElectric4, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"RED"[HIJAU] "YELLOW"[UNGU]" ""GREEN"[MERAH]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }

        if(checkpointid == ElectricCheckpoint[playerid][4])
        {
            Dialog_Show(playerid, FixElectric5, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"YELLOW"[KUNING] "PURPLE"[UNGU]" ""RED"[KUNING]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }

        if(checkpointid == ElectricCheckpoint[playerid][5])
        {
            Dialog_Show(playerid, FixElectric6, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"PURPLE"[KUNING] "PURPLE"[BIRU]" ""RED"[HIJAU]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }

        if(checkpointid == ElectricCheckpoint[playerid][6])
        {
            Dialog_Show(playerid, FixElectric7, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"RED"[KUNING] "BLACK"[BIRU]" ""GREEN"[MERAH]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }

        if(checkpointid == ElectricCheckpoint[playerid][7])
        {
            Dialog_Show(playerid, FixElectric8, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"BLUE"[HIJAU] "PURPLE"[KUNING]" ""GREEN"[MERAH]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }

        if(checkpointid == ElectricCheckpoint[playerid][8])
        {
            Dialog_Show(playerid, FixElectric9, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"BLUE"[KUNING] "RED"[UNGU]" ""GREEN"[MERAH]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }

        if(checkpointid == ElectricCheckpoint[playerid][9])
        {
            Dialog_Show(playerid, FixElectric10, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"RED"[KUNING] "GREEN"[BIRU]" ""PURPLE"[MERAH]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][10])
        {
            Dialog_Show(playerid, FixElectric11, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"YELLOW"[UNGU] "YELLOW"[BIRU]" ""RED"[ORANGE]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][11])
        {
            Dialog_Show(playerid, FixElectric12, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"LIGHTGREY"[ABU] "GREEN"[BIRU]" ""RED"[YELLOW]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][12])
        {
            Dialog_Show(playerid, FixElectric13, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"ORANGE"[MERAH] "GREEN"[OREN]" ""PURPLE"[ABU]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][13])
        {
            Dialog_Show(playerid, FixElectric14, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"WHITE"[KUNING] "BLUE"[HIJAU]" ""YELLOW"[MERAH]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][14])
        {
            Dialog_Show(playerid, FixElectric15, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"ORANGE"[OREN] "RED"[BIRU]" ""YELLOW"[MERAH]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][15])
        {
            Dialog_Show(playerid, FixElectric16, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"RED"[KUNING] "BLUE"[HIJAU]" ""GREEN"[OREN]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][16])
        {
            Dialog_Show(playerid, FixElectric17, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"RED"[KUNING] "LIGHTGREY"[UNGU]" ""PURPLE"[HIJAU]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][17])
        {
            Dialog_Show(playerid, FixElectric18, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"BLUE"[OREN] "RED"[BIRU]" ""YELLOW"[MERAH]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][18])
        {
            Dialog_Show(playerid, FixElectric19, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"PURPLE"[HIJAU] "RED"[KUNING]" ""PURPLE"[MERAH]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][19])
        {
            Dialog_Show(playerid, FixElectric20, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"RED"[KUNING] "RED"[BIRU]" ""PURPLE"[OREN]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][20])
        {
            Dialog_Show(playerid, FixElectric21, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"YELLOW"[UNGU] "RED"[OREN]" ""ORANGE"[HITAM]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][21])
        {
            Dialog_Show(playerid, FixElectric22, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"GREEN"[PUTIH] "GREEN"[UNGU]" ""ORANGE"[OREN]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][22])
        {
            Dialog_Show(playerid, FixElectric23, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"WHITE"[PUTIH] "YELLOW"[BIRU]" ""RED"[KUNING]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][23])
        {
            Dialog_Show(playerid, FixElectric24, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"ORANGE"[OREN] "RED"[MERAH]" ""GREEN"[KUNING]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][24])
        {
            Dialog_Show(playerid, FixElectric25, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"BLUE"[KUNING] "ORANGE"[BIRU]" ""PURPLE"[HITAM]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][25])
        {
            Dialog_Show(playerid, FixElectric26, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"YELLOW"[KUNING] "PURPLE"[MERAH]" ""LIGHTGREY"[ABU]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][26])
        {
            Dialog_Show(playerid, FixElectric27, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"RED"[KUNING] "GREEN"[BIRU]" ""PURPLE"[MERAH]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][27])
        {
            Dialog_Show(playerid, FixElectric28, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"PURPLE"[KUNING] "YELLOW"[BIRU]" ""BLUE"[MERAH]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][28])
        {
            Dialog_Show(playerid, FixElectric29, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"GREEN"[KUNING] "WHITE"[BIRU]" ""ORANGE"[MERAH]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
        
        if(checkpointid == ElectricCheckpoint[playerid][29])
        {
            Dialog_Show(playerid, FixElectric30, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
            "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
            \n\n"YELLOW"[KUNING] "YELLOW"[BIRU]" ""PURPLE"[MERAH]\
            \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
        }
    }
    return 1;
}

Dialog:ElectricanMenu(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        switch(listitem)
        {
            case 0: // Buat Group Baru
            {
                Dialog_Show(playerid, ElectricanInputGroup, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Create Group",
                "Harap masukkan nama group anda dibawah sini:", "Input", "Cancel");
            }
            case 1: // Invite orang
            {
                Dialog_Show(playerid, ElectricInvite, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Create Group",
                "Harap masukkan player id yang ingin kamu undang ke group:", "Invite", "Cancel");
            }
            case 2: // Kick Group Member
            {
                Dialog_Show(playerid, ElectricKick, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Create Group",
                "Harap masukkan player id yang ingin kamu kick dari group anda:", "Invite", "Cancel");
            }
            case 3: // Join Group Member
            {
                Dialog_Show(playerid, ElectricJoinGroup, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Create Group",
                "Harap masukkan group id job yang ingin anda ikuti:", "Invite", "Cancel");
            }
            case 4: // Start Job
            {
                if(PlayerElectricJob[playerid][ElectricGroup][0] == EOS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum membuat group!");
                if(IsElectricanWorking(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memulai pekerjaan ini sebelumnya!");
                if(PlayerElectricJob[playerid][ElectricWithPlayerID] != INVALID_PLAYER_ID) // bEr 2
                {
                    new TeamID = PlayerElectricJob[playerid][ElectricWithPlayerID];
                    SetElectricanWorking(TeamID, true); // Vars Team
                    SetElectricanWorking(playerid, true);
                    SetElectricanSkin(playerid, AccountData[playerid][pGender]);
                    SetElectricanSkin(TeamID, AccountData[TeamID][pGender]); // Vars Team
                    
                    PlayerElectricJob[playerid][ElectricVehicle] = CreateVehicle(552, -2532.0229, -601.6449, 132.2643, 177.5118, 1, 1, 60000);
                    PlayerElectricJob[playerid][ElectricLocked] = false;
                    VehicleCore[PlayerElectricJob[playerid][ElectricVehicle]][vCoreFuel] = MAX_FUEL_FULL;
                    SetValidVehicleHealth(PlayerElectricJob[playerid][ElectricVehicle], 2000.0);
                    SwitchVehicleEngine(PlayerElectricJob[playerid][ElectricVehicle], true);
                    SwitchVehicleLight(PlayerElectricJob[playerid][ElectricVehicle], true);

                    PutPlayerInVehicle(playerid, PlayerElectricJob[playerid][ElectricVehicle], 0); // Leader Sebagai Supir
                    PutPlayerInVehicle(TeamID, PlayerElectricJob[playerid][ElectricVehicle], 1); // Team sebagai penumpang

                    PlayerElectricJob[TeamID][ElectricVehicle] = PlayerElectricJob[playerid][ElectricVehicle];

                    PlayerElectricJob[playerid][ElectricGroupID] = -1;
                    PlayerElectricJob[TeamID][ElectricGroupID] = -1;
                    for(new i = 0; i < 30; i ++)
                    {
                        ElectricCheckpoint[playerid][i] = CreateDynamicCP(ElectricanPoint[i][0], ElectricanPoint[i][1], ElectricanPoint[i][2], 2.0, 0, 0, playerid, 25.0);
                        ElectricMapIcon[playerid][i] = CreateDynamicMapIcon(ElectricanPoint[i][0], ElectricanPoint[i][1], ElectricanPoint[i][2], 0, X11_RED, 0, 0, playerid, 5000.0, MAPICON_GLOBAL);
                        
                        ElectricCheckpoint[TeamID][i] = CreateDynamicCP(ElectricanPoint[i][0], ElectricanPoint[i][1], ElectricanPoint[i][2], 2.0, 0, 0, TeamID, 25.0);
                        ElectricMapIcon[TeamID][i] = CreateDynamicMapIcon(ElectricanPoint[i][0], ElectricanPoint[i][1], ElectricanPoint[i][2], 0, X11_RED, 0, 0, TeamID, 5000.0, MAPICON_GLOBAL);
                    }
                    Info(playerid, "Silahkan menuju ke cek point yang ada di map radar anda, lalu gunakan /takekit sebelum turun dari mobil");
                    Info(TeamID, "Silahkan menuju ke cek point yang ada di map radar anda, lalu gunakan /takekit sebelum turun dari mobil");
                }
                else
                {
                    SetElectricanWorking(playerid, true);
                    SetElectricanSkin(playerid, AccountData[playerid][pGender]);
                    
                    PlayerElectricJob[playerid][ElectricVehicle] = CreateVehicle(552, -2532.0229, -601.6449, 132.2643, 177.5118, 1, 1, 60000);
                    PlayerElectricJob[playerid][ElectricLocked] = false;
                    VehicleCore[PlayerElectricJob[playerid][ElectricVehicle]][vCoreFuel] = MAX_FUEL_FULL;
                    SetValidVehicleHealth(PlayerElectricJob[playerid][ElectricVehicle], 2000.0);
                    SwitchVehicleEngine(PlayerElectricJob[playerid][ElectricVehicle], true);
                    SwitchVehicleLight(PlayerElectricJob[playerid][ElectricVehicle], true);

                    PutPlayerInVehicle(playerid, PlayerElectricJob[playerid][ElectricVehicle], 0); // Leader Sebagai Supir
                    
                    PlayerElectricJob[playerid][ElectricGroupID] = -1;
                    for(new i = 0; i < 30; i ++)
                    {
                        ElectricCheckpoint[playerid][i] = CreateDynamicCP(ElectricanPoint[i][0], ElectricanPoint[i][1], ElectricanPoint[i][2], 2.0, 0, 0, playerid, 25.0);
                        ElectricMapIcon[playerid][i] = CreateDynamicMapIcon(ElectricanPoint[i][0], ElectricanPoint[i][1], ElectricanPoint[i][2], 0, X11_RED, 0, 0, playerid, 5000.0, MAPICON_GLOBAL);
                    }
                }
            }
            case 5: // Berhenti pekerjaan
            {
                if(!IsElectricanWorking(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini sebelumnya!");

                for(new i = 0; i < 30; i ++)
                {
                    if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                        ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                    
                    if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                        ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
                }
                if(DestroyDynamicRaceCP(ElectricFinishPoint[playerid]))
                    ElectricFinishPoint[playerid] = STREAMER_TAG_RACE_CP: INVALID_STREAMER_ID;
                
                if(PlayerElectricJob[playerid][ElectricWithPlayerID] != INVALID_PLAYER_ID && PlayerElectricJob[playerid][ElectricLeader] == playerid)
                {
                    new TeamID = PlayerElectricJob[playerid][ElectricWithPlayerID];
                    PlayerElectricJob[TeamID][ElectricVehicle] = PlayerElectricJob[playerid][ElectricVehicle];
                    PlayerElectricJob[TeamID][ElectricLocked] = PlayerElectricJob[playerid][ElectricLocked];

                    PlayerElectricJob[playerid][ElectricVehicle] = INVALID_VEHICLE_ID;
                    PlayerElectricJob[playerid][ElectricLocked] = false;
                }
                else
                {
                    if(IsValidVehicle(PlayerElectricJob[playerid][ElectricVehicle]))
                    {
                        DestroyVehicle(PlayerElectricJob[playerid][ElectricVehicle]);  
                        PlayerElectricJob[playerid][ElectricVehicle] = INVALID_VEHICLE_ID;
                        PlayerElectricJob[playerid][ElectricLocked] = false;
                    }
                }
                SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
                ResetVariableElectric(playerid);
            }
        }
    }
    else Info(playerid, "Anda telah membatalkan pilihan!");
    return 1;
}

Dialog:ElectricJoinGroup(playerid, response, listitem, inputtext[])
{
    if(!response) return Info(playerid, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
    if(PlayerElectricJob[playerid][ElectricWithPlayerID] != INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah berada di dalam grup!");
    
    if(isnull(inputtext)) return Dialog_Show(playerid, ElectricJoinGroup, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Create Group",
    "Error: Tidak dapat diisi kosong!\nHarap masukkan group id job yang ingin anda ikuti:", "Invite", "Cancel");

    if(!IsNumeric(inputtext)) return Dialog_Show(playerid, ElectricJoinGroup, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Create Group",
    "Error: Hanya dapat diisi angka!\nHarap masukkan group id job yang ingin anda ikuti:", "Invite", "Cancel");
    
    new bool: found = false;
    foreach(new i : Player) if (IsPlayerConnected(i))
    {
        if(PlayerElectricJob[i][ElectricGroupID] == strval(inputtext))
        {
            if(PlayerElectricJob[i][ElectricWithPlayerID] != INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah memiliki team!");

            Info(i, ""YELLOW"%s(%d)"WHITE" telah bergabung dengan group anda", ReturnName(playerid), playerid);
            Info(playerid, "Anda berhasil bergabung ke dalam group, "YELLOW"%s [Group ID: %d]", PlayerElectricJob[i][ElectricGroup], PlayerElectricJob[i][ElectricGroupID]);
            PlayerElectricJob[i][ElectricWithPlayerID] = playerid;
            PlayerElectricJob[playerid][ElectricWithPlayerID] = i;
            format(PlayerElectricJob[playerid][ElectricGroup], 128, "%s", PlayerElectricJob[i][ElectricGroup]);
            PlayerElectricJob[i][ElectricGroupID] = -1;
            found = true;
        }
    }

    if(!found) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Group tidak ada!");
    return 1;
}

Dialog:ElectricKick(playerid, response, listitem, inputtext[])
{
    if(!response) return Info(playerid, "Anda telah membatalkan pilihan!");
    if(PlayerElectricJob[playerid][ElectricGroup][0] == EOS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki group di pekerjaan ini!");

    if(isnull(inputtext)) return Dialog_Show(playerid, ElectricKick, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Create Group",
    "Error: Tidak dapat diisi kosong!\nHarap masukkan player id yang ingin kamu kick dari group anda:", "Invite", "Cancel");

    if(!IsNumeric(inputtext)) return Dialog_Show(playerid, ElectricKick, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Create Group",
    "Error: Hanya dapat diisi angka!\nHarap masukkan player id yang ingin kamu kick dari group anda:", "Invite", "Cancel");    

    new otherid = strval(inputtext);

    if(PlayerElectricJob[otherid][ElectricWithPlayerID] != playerid) return Dialog_Show(playerid, ElectricKick, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Create Group",
    "Error: Pemain tersebut tidak berada di dalam group anda!\nHarap masukkan player id yang ingin kamu kick dari group anda:", "Invite", "Cancel");

    PlayerElectricJob[playerid][ElectricWithPlayerID] = INVALID_PLAYER_ID;
    PlayerElectricJob[otherid][ElectricWithPlayerID] = INVALID_PLAYER_ID;
    Info(playerid, "Anda berhasil mengeluarkan "YELLOW"%s(%d)"WHITE" dari group anda", ReturnName(otherid), otherid);
    Warning(otherid, ""YELLOW"%s(%d)"WHITE" telah mengeluarkan anda dari group electric job", ReturnName(playerid), playerid);
    return 1;
}

Dialog:ElectricanInputGroup(playerid, response, listitem, inputtext[])
{
    if(!response) return Info(playerid, "Anda telah membatalkan pilihan!");
    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");

    if(isnull(inputtext)) return Dialog_Show(playerid, ElectricanInputGroup, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Create Group",
    "Error: Tidak dapat diisi kosong!\nHarap masukkan nama group anda dibawah sini:", "Input", "Cancel");

    if(IsNumeric(inputtext)) return Dialog_Show(playerid, ElectricanInputGroup, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Create Group",
    "Error: Tidak dapat diisi angka!\nHarap masukkan nama group anda dibawah sini:", "Input", "Cancel");

    if(strlen(inputtext) < 7) return Dialog_Show(playerid, ElectricanInputGroup, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Create Group",
    "Error: Nama Group setidaknya lebih dari 7 huruf!\nHarap masukkan nama group anda dibawah sini:", "Input", "Cancel");

    PlayerElectricJob[playerid][ElectricLeader] = playerid;
    PlayerElectricJob[playerid][ElectricGroupID] = Random(1, 100);
    format(PlayerElectricJob[playerid][ElectricGroup], 128, "%s", inputtext);
    Info(playerid, "Anda berhasil membuat group baru, "YELLOW"%s [Group ID: %d]", inputtext, PlayerElectricJob[playerid][ElectricGroupID]);
    return 1;
}

Dialog:ElectricInvite(playerid, response, listitem, inputtext[])
{
    if(!response) return Info(playerid, "Anda telah membatalkan pilihan!");
    if(PlayerElectricJob[playerid][ElectricGroup][0] == EOS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus membuat group terlebih dahulu!");

    if(isnull(inputtext)) return Dialog_Show(playerid, ElectricInvite, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Invite Group",
    "Error: Tidak dapat diisi kosong!\nHarap masukkan player id yang ingin kamu undang ke group:", "Input", "Cancel");

    if(!IsNumeric(inputtext)) return Dialog_Show(playerid, ElectricInvite, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Invite Group",
    "Error: Hanya dapat memasukkan angka!\nHarap masukkan player id yang ingin kamu undang ke group:", "Input", "Cancel");

    if(strval(inputtext) == INVALID_PLAYER_ID || !IsPlayerConnected(strval(inputtext))) return Dialog_Show(playerid, ElectricInvite, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Invite Group",
    "Error: Pemain yang anda undang tidak berada di dalam server!\nHarap masukkan player id yang ingin kamu undang ke group:", "Input", "Cancel");

    new otherid = strval(inputtext);

    if(!IsPlayerNearPlayer(playerid, otherid, 5.0)) return Dialog_Show(playerid, ElectricInvite, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Invite Group",
    "Error: Pemain tersebut harus berada di dekat anda!\nHarap masukkan player id yang ingin kamu undang ke group:", "Input", "Cancel");

    Info(playerid, "Anda mengundang "YELLOW"%s(%d)"WHITE" ke group. Harap tunggu respon darinya", ReturnName(otherid), otherid);
    Warning(otherid, ""YELLOW"%s(%d)"WHITE" mengundang anda untuk masuk ke dalam group", ReturnName(playerid), playerid);
    SendClientMessage(otherid, -1, "Gunakan "YELLOW"'/group accept'"WHITE" untuk menerima");
    SetPVarInt(otherid, "ElectricInviteID", PlayerElectricJob[playerid][ElectricGroupID]);
    return 1;
}

CMD:takekit(playerid, params[])
{
    if(!IsElectricanWorking(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang bekerja sebagai tukang listrik!");
    
    static Float:x, Float:y, Float:z;
    GetVehiclePos(PlayerElectricJob[playerid][ElectricVehicle], x, y, z);
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di kendaraan job anda!");

    SetPlayerAttachedObject(playerid, JOB_SLOT, 19921, 6,  0.000000, 0.000000, 0.000000,  87.199996, -0.099994, -86.900009,  1.000000, 1.000000, 1.000000); // 
    SetPVarInt(playerid, "IsPlayerHaveKit", 1);    
    return 1;
}

CMD:group(playerid, params[])
{
    static
        type[24],
        nextParams[128];
    
    if(sscanf(params, "s[24]S()[128]", type, nextParams))
    {
        Syntax(playerid, "/group (accept | decline)");
        return 1;
    }
    if(!strcmp(type, "accept", true))
    {
        new groupid = GetPVarInt(playerid, "ElectricInviteID");
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] != INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah bergabung dalam group orang lain sebelumnya!");
        
        foreach(new i : Player) if (IsPlayerConnected(i)) 
        {
            if(PlayerElectricJob[i][ElectricGroupID] == groupid)
            {
                new LeaderID = i;
                Info(playerid, "Anda berhasil masuk ke dalam group, "YELLOW"%s [Group ID: %d]", PlayerElectricJob[i][ElectricGroup], PlayerElectricJob[i][ElectricGroupID]);
                Info(LeaderID, ""YELLOW"%s(%d)"WHITE" telah menerima undangan group electric job anda", ReturnName(playerid), playerid);
                PlayerElectricJob[LeaderID][ElectricWithPlayerID] = playerid;
                PlayerElectricJob[playerid][ElectricWithPlayerID] = LeaderID;

                format(PlayerElectricJob[playerid][ElectricGroup], 128, "%s", PlayerElectricJob[LeaderID][ElectricGroup]);
            }
        }
    }
    else Syntax(playerid, "/group (accept | decline)");
    return 1;
}

Dialog:FixElectric1(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Merah";
    new truecolor2[] = "Hijau";
    new truecolor3[] = "Putih";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric1, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"RED"[KUNING] "GREEN"[BIRU]", ""WHITE"[MERAH]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][0]))
            ElectricCheckpoint[playerid][0] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][0]))
            ElectricMapIcon[playerid][0] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric2(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Hijau";
    new truecolor2[] = "Kuning";
    new truecolor3[] = "Merah";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric2, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"GREEN"[MERAH] "YELLOW"[HIJAU]" ""RED"[UNGU]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][1]))
            ElectricCheckpoint[playerid][1] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][1]))
            ElectricMapIcon[playerid][1] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric3(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Ungu";
    new truecolor2[] = "Merah";
    new truecolor3[] = "Kuning";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric3, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"PURPLE"[ABU] "RED"[KUNING]" ""YELLOW"[UNGU]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][2]))
            ElectricCheckpoint[playerid][2] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][2]))
            ElectricMapIcon[playerid][2] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric4(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Merah";
    new truecolor2[] = "Kuning";
    new truecolor3[] = "Hijau";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric4, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"RED"[HIJAU] "YELLOW"[UNGU]" ""GREEN"[MERAH]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][3]))
            ElectricCheckpoint[playerid][3] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][3]))
            ElectricMapIcon[playerid][3] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric5(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Kuning";
    new truecolor2[] = "Ungu";
    new truecolor3[] = "Merah";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric5, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"YELLOW"[KUNING] "PURPLE"[UNGU]" ""RED"[KUNING]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][4]))
            ElectricCheckpoint[playerid][4] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][4]))
            ElectricMapIcon[playerid][4] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric6(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Ungu";
    new truecolor2[] = "Ungu";
    new truecolor3[] = "Merah";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric6, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"PURPLE"[KUNING] "PURPLE"[BIRU]" ""RED"[HIJAU]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][5]))
            ElectricCheckpoint[playerid][5] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][5]))
            ElectricMapIcon[playerid][5] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric7(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Merah";
    new truecolor2[] = "Hitam";
    new truecolor3[] = "Hijau";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric7, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"RED"[KUNING] "BLACK"[BIRU]" ""GREEN"[MERAH]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][6]))
            ElectricCheckpoint[playerid][6] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][6]))
            ElectricMapIcon[playerid][6] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric8(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Biru";
    new truecolor2[] = "Ungu";
    new truecolor3[] = "Hijau";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric8, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"BLUE"[HIJAU] "PURPLE"[KUNING]" ""GREEN"[MERAH]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][7]))
            ElectricCheckpoint[playerid][7] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][7]))
            ElectricMapIcon[playerid][7] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric9(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Biru";
    new truecolor2[] = "Merah";
    new truecolor3[] = "Hijau";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric9, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"BLUE"[KUNING] "RED"[UNGU]" ""GREEN"[MERAH]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][8]))
            ElectricCheckpoint[playerid][8] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][8]))
            ElectricMapIcon[playerid][8] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric10(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Merah";
    new truecolor2[] = "Hijau";
    new truecolor3[] = "Ungu";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric10, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"RED"[KUNING] "GREEN"[BIRU]" ""PURPLE"[MERAH]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][9]))
            ElectricCheckpoint[playerid][9] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][9]))
            ElectricMapIcon[playerid][9] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric11(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Kuning";
    new truecolor2[] = "Kuning";
    new truecolor3[] = "Merah";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric11, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"YELLOW"[UNGU] "YELLOW"[BIRU]" ""RED"[ORANGE]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][10]))
            ElectricCheckpoint[playerid][10] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][10]))
            ElectricMapIcon[playerid][10] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric12(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Abu";
    new truecolor2[] = "Hijau";
    new truecolor3[] = "Merah";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric12, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"LIGHTGREY"[ABU] "GREEN"[BIRU]" ""RED"[YELLOW]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][11]))
            ElectricCheckpoint[playerid][11] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][11]))
            ElectricMapIcon[playerid][11] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric13(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Oren";
    new truecolor2[] = "Hijau";
    new truecolor3[] = "Ungu";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric13, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"ORANGE"[MERAH] "GREEN"[OREN]" ""PURPLE"[ABU]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][12]))
            ElectricCheckpoint[playerid][12] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][12]))
            ElectricMapIcon[playerid][12] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric14(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Putih";
    new truecolor2[] = "Biru";
    new truecolor3[] = "Kuning";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric14, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"WHITE"[KUNING] "BLUE"[HIJAU]" ""YELLOW"[MERAH]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][13]))
            ElectricCheckpoint[playerid][13] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][13]))
            ElectricMapIcon[playerid][13] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric15(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Oren";
    new truecolor2[] = "Merah";
    new truecolor3[] = "Kuning";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric15, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"ORANGE"[OREN] "RED"[BIRU]" ""YELLOW"[MERAH]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][14]))
            ElectricCheckpoint[playerid][14] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][14]))
            ElectricMapIcon[playerid][14] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric16(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Merah";
    new truecolor2[] = "Biru";
    new truecolor3[] = "Hijau";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric16, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"RED"[KUNING] "BLUE"[HIJAU]" ""GREEN"[OREN]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][15]))
            ElectricCheckpoint[playerid][15] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][15]))
            ElectricMapIcon[playerid][15] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric17(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Merah";
    new truecolor2[] = "Abu";
    new truecolor3[] = "Ungu";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric17, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"RED"[KUNING] "LIGHTGREY"[UNGU]" ""PURPLE"[HIJAU]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][16]))
            ElectricCheckpoint[playerid][16] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][16]))
            ElectricMapIcon[playerid][16] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric18(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Biru";
    new truecolor2[] = "Merah";
    new truecolor3[] = "Kuning";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric18, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"BLUE"[OREN] "RED"[BIRU]" ""YELLOW"[MERAH]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][17]))
            ElectricCheckpoint[playerid][17] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][17]))
            ElectricMapIcon[playerid][17] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric19(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Ungu";
    new truecolor2[] = "Merah";
    new truecolor3[] = "Ungu";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric19, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"PURPLE"[HIJAU] "RED"[KUNING]" ""PURPLE"[MERAH]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][18]))
            ElectricCheckpoint[playerid][18] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][18]))
            ElectricMapIcon[playerid][18] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric20(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Merah";
    new truecolor2[] = "Merah";
    new truecolor3[] = "Ungu";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric20, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"RED"[KUNING] "RED"[BIRU]" ""PURPLE"[OREN]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][19]))
            ElectricCheckpoint[playerid][19] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][19]))
            ElectricMapIcon[playerid][19] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric21(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Kuning";
    new truecolor2[] = "Merah";
    new truecolor3[] = "Oren";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric21, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"YELLOW"[UNGU] "RED"[OREN]" ""ORANGE"[HITAM]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][20]))
            ElectricCheckpoint[playerid][20] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][20]))
            ElectricMapIcon[playerid][20] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric22(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Hijau";
    new truecolor2[] = "Hijau";
    new truecolor3[] = "Oren";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric22, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"GREEN"[PUTIH] "GREEN"[UNGU]" ""ORANGE"[OREN]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][21]))
            ElectricCheckpoint[playerid][21] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][21]))
            ElectricMapIcon[playerid][21] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric23(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Putih";
    new truecolor2[] = "Kuning";
    new truecolor3[] = "Merah";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric23, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"WHITE"[PUTIH] "YELLOW"[BIRU]" ""RED"[KUNING]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][22]))
            ElectricCheckpoint[playerid][22] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][22]))
            ElectricMapIcon[playerid][22] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric24(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Oren";
    new truecolor2[] = "Merah";
    new truecolor3[] = "Hijau";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric24, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"ORANGE"[OREN] "RED"[MERAH]" ""GREEN"[KUNING]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][23]))
            ElectricCheckpoint[playerid][23] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][23]))
            ElectricMapIcon[playerid][23] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric25(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Biru";
    new truecolor2[] = "Oren";
    new truecolor3[] = "Ungu";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric25, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"BLUE"[KUNING] "ORANGE"[BIRU]" ""PURPLE"[HITAM]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][24]))
            ElectricCheckpoint[playerid][24] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][24]))
            ElectricMapIcon[playerid][24] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric26(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Kuning";
    new truecolor2[] = "Ungu";
    new truecolor3[] = "Abu";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric26, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"YELLOW"[KUNING] "PURPLE"[MERAH]" ""LIGHTGREY"[ABU]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][25]))
            ElectricCheckpoint[playerid][25] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][25]))
            ElectricMapIcon[playerid][25] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric27(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Merah";
    new truecolor2[] = "Hijau";
    new truecolor3[] = "Ungu";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric27, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"RED"[KUNING] "GREEN"[BIRU]" ""PURPLE"[MERAH]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][26]))
            ElectricCheckpoint[playerid][26] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][26]))
            ElectricMapIcon[playerid][26] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric28(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Ungu";
    new truecolor2[] = "Kuning";
    new truecolor3[] = "Biru";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric28, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"PURPLE"[KUNING] "YELLOW"[BIRU]" ""BLUE"[MERAH]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][27]))
            ElectricCheckpoint[playerid][27] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][27]))
            ElectricMapIcon[playerid][27] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric29(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Hijau";
    new truecolor2[] = "Putih";
    new truecolor3[] = "Oren";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric29, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"GREEN"[KUNING] "WHITE"[BIRU]" ""ORANGE"[MERAH]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][28]))
            ElectricCheckpoint[playerid][28] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][28]))
            ElectricMapIcon[playerid][28] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

Dialog:FixElectric30(playerid, response, listitem, inputtext[])
{
    if(!response) return 0;

    if(!IsElectricanWorking(playerid)) return 0;

    new truecolor1[] = "Kuning";
    new truecolor2[] = "Kuning";
    new truecolor3[] = "Ungu";

    new color1[64], color2[64], color3[64];
    if(sscanf(inputtext, "s[64]s[64]s[64]", color1, color2, color3))
    {
        return Dialog_Show(playerid, FixElectric30, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fix Kelistrikan",
        "harap berikan nama warna dalam bahasa indonesia yang sesuai dengan warna di sekitar teks di bawah ini\
        \n\n"YELLOW"[KUNING] "YELLOW"[BIRU]" ""PURPLE"[MERAH]\
        \n"RED"(Harap berikan nama warna saja berdasarkan warna teks di atas tanpa '[' atau ']')", "Input", "Cancel");
    }

    if(!strcmp(color1, truecolor1, true) && !strcmp(color2, truecolor2, true) && !strcmp(color3, truecolor3, true))
    {
        if(PlayerElectricJob[playerid][ElectricWithPlayerID] == INVALID_PLAYER_ID)
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 63);
            ShowItemBox(playerid, "Received $63", "Uang", 1212);
        }
        else 
        {
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 5000, 1);
            PlayerPlayNearbySound(playerid, 32000);
            GiveMoney(playerid, 83);
            ShowItemBox(playerid, "Received $83", "Uang", 1212);
        }
        PlayerElectricJob[playerid][ElectricFixCount] ++;

        if(DestroyDynamicCP(ElectricCheckpoint[playerid][29]))
            ElectricCheckpoint[playerid][29] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
        
        if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][29]))
            ElectricMapIcon[playerid][29] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
        
        RemovePlayerAttachedObject(playerid, JOB_SLOT);
        DeletePVar(playerid, "IsPlayerHaveKit");

        if(PlayerElectricJob[playerid][ElectricFixCount] >= 30)
        {
            for(new i = 0; i < 30; i++) {
                if(DestroyDynamicCP(ElectricCheckpoint[playerid][i]))
                    ElectricCheckpoint[playerid][i] = STREAMER_TAG_CP: INVALID_STREAMER_ID;
                
                if(DestroyDynamicMapIcon(ElectricMapIcon[playerid][i]))
                    ElectricMapIcon[playerid][i] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
            }
            
            ElectricFinishPoint[playerid] = CreateDynamicRaceCP(1, -2532.7063, -612.3835, 132.5625, 0.0, 0.0, 0.0, 4.0, 0, 0, playerid, 1000.0, -1, 0);
            Info(playerid, "Anda telah memperbaiki seluruh listrik yang bermasalah. Silahkan kembali ke tempat awal untuk menyelesaikan pekerjaan!");
        }
    }
    else
    {
        ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 1, 1);
        SetTimerEx("WakeUpElectric", 3000, false, "d", playerid);
        PlayerPlayNearbySound(playerid, 6003);
    }
    return 1;
}

FUNC::WakeUpElectric(playerid)
{
    ClearAnimations(playerid, 1);
    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
    return 1;
}