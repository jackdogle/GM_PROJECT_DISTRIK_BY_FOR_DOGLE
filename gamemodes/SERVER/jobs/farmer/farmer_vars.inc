#include <YSI\y_hooks>

new PetaniIndex[MAX_PLAYERS];
new pTakeCabaiTimer[MAX_PLAYERS] = {-1, ...};
new pTakeBerasTimer[MAX_PLAYERS] = {-1, ...};
new pTakeTebuTimer[MAX_PLAYERS] = {-1, ...};
new pTakeSaltTimer[MAX_PLAYERS] = {-1, ...};
new pTimerOlah[MAX_PLAYERS] = {-1, ...};

enum E_STUFFFARMER
{
    TraktorBeras,
    TraktorGula,
    TraktorCabai,
    TraktorGaram,

    STREAMER_TAG_AREA:PetaniOlah,
    STREAMER_TAG_AREA:PetaniBeras,
    STREAMER_TAG_AREA:PetaniTebu,
    STREAMER_TAG_AREA:PetaniCabai,
    STREAMER_TAG_AREA:PetaniStore,
    STREAMER_TAG_AREA:PetaniGaram,

    STREAMER_TAG_AREA:PadiArea[25],
    STREAMER_TAG_AREA:TebuArea[25],
    STREAMER_TAG_AREA:CabaiArea[25],
    STREAMER_TAG_AREA:GaramArea[21],

    STREAMER_TAG_OBJECT:GaramObject[21],
    STREAMER_TAG_OBJECT:PadiObject[25],
    STREAMER_TAG_OBJECT:TebuObject[25],
    STREAMER_TAG_OBJECT:CabaiObject[25],

    STREAMER_TAG_PICKUP:PetaniPickup,
    STREAMER_TAG_3D_TEXT_LABEL:StoreLabel,
    STREAMER_TAG_3D_TEXT_LABEL:PetaniOlahLabel,

    bool:DurringTebu,
    bool:DurringCabai,
    bool:DurringBeras,
    bool:DurringGaram,

    bool:NoDurringGaram,
    bool:NoDurringTebu,
    bool:NoDurringCabai,
    bool:NoDurringBeras,
};
new PlayerFarmVars[MAX_PLAYERS][E_STUFFFARMER];

function LoadVarsFarmer(playerid)
{   
    UnloadVarsFarmer(playerid);

    PlayerFarmVars[playerid][PetaniBeras] = CreateDynamicCircle(-40.6610, 102.1019, 2.0, 0, 0, playerid);
    PlayerFarmVars[playerid][PetaniTebu] = CreateDynamicCircle(-52.0804, 102.5144, 2.0, 0, 0, playerid);
    PlayerFarmVars[playerid][PetaniCabai] = CreateDynamicCircle(-49.2528, 106.9065, 2.0, 0, 0, playerid);
    PlayerFarmVars[playerid][PetaniGaram] = CreateDynamicCircle(-43.2573, 97.4948, 2.0, 0, 0, playerid);
    PlayerFarmVars[playerid][PetaniOlah] = CreateDynamicCircle(3.9224, 66.8390, 3.2, 0, 0, playerid);
    PlayerFarmVars[playerid][PetaniOlahLabel] = CreateDynamic3DTextLabel(""GREEN"[Y] "WHITE"Olah Tanaman", -1, 3.9224, 66.8390, 3.1172+0.5, 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, playerid);
}

function UnloadVarsFarmer(playerid)
{
    if(IsValidDynamicArea(PlayerFarmVars[playerid][PetaniBeras]))
        DestroyDynamicArea(PlayerFarmVars[playerid][PetaniBeras]);
    PlayerFarmVars[playerid][PetaniBeras] = STREAMER_TAG_AREA: -1;
        
    if(IsValidDynamicArea(PlayerFarmVars[playerid][PetaniTebu]))
        DestroyDynamicArea(PlayerFarmVars[playerid][PetaniTebu]);
    PlayerFarmVars[playerid][PetaniTebu] = STREAMER_TAG_AREA: -1;
        
    if(IsValidDynamicArea(PlayerFarmVars[playerid][PetaniCabai]))
        DestroyDynamicArea(PlayerFarmVars[playerid][PetaniCabai]);
    PlayerFarmVars[playerid][PetaniCabai] = STREAMER_TAG_AREA: -1;
        
    if(IsValidDynamicArea(PlayerFarmVars[playerid][PetaniGaram]))
        DestroyDynamicArea(PlayerFarmVars[playerid][PetaniGaram]);
    PlayerFarmVars[playerid][PetaniGaram] = STREAMER_TAG_AREA: -1;
        
    if(IsValidDynamicArea(PlayerFarmVars[playerid][PetaniOlah]))
        DestroyDynamicArea(PlayerFarmVars[playerid][PetaniOlah]);
    PlayerFarmVars[playerid][PetaniOlah] = STREAMER_TAG_AREA: -1;
    
    if(IsValidDynamic3DTextLabel(PlayerFarmVars[playerid][PetaniOlahLabel]))
        DestroyDynamic3DTextLabel(PlayerFarmVars[playerid][PetaniOlahLabel]);
    PlayerFarmVars[playerid][PetaniOlahLabel] = STREAMER_TAG_3D_TEXT_LABEL: -1;
}

stock LoadLumbng(playerid)
{
    static 
        sstr[712];

    format(sstr, sizeof sstr, ""YELLOW"[Lumbung Petani]\n\n"YELLOW"`/sellplant`"WHITE" -> Jual semua tanaman.\n"YELLOW"[Harga Jual]:\n"WHITE"Sambal "VERONA_GREEN"$18/sambal\n"WHITE"Beras "VERONA_GREEN"$18/beras\n"WHITE"Gula "VERONA_GREEN"$18/Gula\n"WHITE"Garam "VERONA_GREEN"$18/Garam\n\n"YELLOW"`/buyplant` "WHITE"-> Beli tanaman.\n"YELLOW"[Harga Beli];\n"WHITE"Sambal "VERONA_GREEN"$3/Sambal\n"WHITE"Beras "VERONA_GREEN"$3/Beras\n"WHITE"Gula "VERONA_GREEN"$3/Gula\n"WHITE"Garam "VERONA_GREEN"$3/Garam\n\n"YELLOW"[Stock]: %dx", Stock);
    PlayerFarmVars[playerid][PetaniStore] = CreateDynamicCircle(-84.9263, -1.3630, 3.0, 0, 0, playerid);
    PlayerFarmVars[playerid][PetaniPickup] = CreateDynamicPickup(1221, 23, -84.9263, -1.3630, 3.1172+0.1, 0, 0, 0, 5.0);
    PlayerFarmVars[playerid][StoreLabel] = CreateDynamic3DTextLabel(sstr, -1, -84.9263, -1.3630, 3.1172+1.6, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
}

hook OnPlayerConnect(playerid)
{
    LoadLumbng(playerid);
    pTakeCabaiTimer[playerid] = -1;
    pTakeBerasTimer[playerid] = -1;
    pTakeTebuTimer[playerid] = -1;
    pTakeSaltTimer[playerid] = -1;
    pTimerOlah[playerid] = -1;
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(GetPlayerJob(playerid) == JOB_FARMER && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(!PlayerFarmVars[playerid][DurringGaram])
        {
            if(areaid == PlayerFarmVars[playerid][PetaniGaram])
            {
                SetPlayerCheckpoint(playerid, -43.2573, 97.4948, 3.0778, 2.5);
                ShowKey(playerid, "[Y]- Traktor Garam");
            }
        }

        if(!PlayerFarmVars[playerid][DurringCabai])
        {
            if(areaid == PlayerFarmVars[playerid][PetaniCabai])
            {
                SetPlayerCheckpoint(playerid, -49.2528, 106.9065, 3.0845, 2.5);
                ShowKey(playerid, "[Y]- Traktor Cabai");
            }
        }
        if(!PlayerFarmVars[playerid][DurringTebu])
        {
            if(areaid == PlayerFarmVars[playerid][PetaniTebu])
            {
                SetPlayerCheckpoint(playerid, -52.0804, 102.5144, 3.0834, 2.5);
                ShowKey(playerid, "[Y]- Traktor Gula");
            }
        }
        if(!PlayerFarmVars[playerid][DurringBeras])
        {
            if(areaid == PlayerFarmVars[playerid][PetaniBeras])
            {
                SetPlayerCheckpoint(playerid, -41.5297, 102.4031, 3.0809, 2.5);
                ShowKey(playerid, "[Y]- Traktor Beras");
            }
        }

        if(PlayerFarmVars[playerid][NoDurringBeras])
        {
            if(areaid == PlayerFarmVars[playerid][PetaniBeras])
            {
                SetPlayerCheckpoint(playerid, -41.5297, 102.4031, 3.0809, 2.5);
                ShowKey(playerid, "[Y]- Selesai Panen");
            }
        }

        if(PlayerFarmVars[playerid][NoDurringTebu])
        {
            if(areaid == PlayerFarmVars[playerid][PetaniTebu])
            {
                SetPlayerCheckpoint(playerid, -52.0804, 102.5144, 3.0834, 2.5);
                ShowKey(playerid, "[Y]- Selesai Panen");
            }
        }
        
        if(PlayerFarmVars[playerid][NoDurringCabai])
        {
            if(areaid == PlayerFarmVars[playerid][PetaniCabai])
            {
                SetPlayerCheckpoint(playerid, -49.2528, 106.9065, 3.0845, 2.5);
                ShowKey(playerid, "[Y]- Selesai Panen");
            }
        }

        if(PlayerFarmVars[playerid][NoDurringGaram])
        {
            if(areaid == PlayerFarmVars[playerid][PetaniGaram])
            {
                SetPlayerCheckpoint(playerid, -43.2573, 97.4948, 3.0778, 2.5);
                ShowKey(playerid, "[Y]- Selesai Panen");
            }
        }
        
    }
    for(new i = 0; i < 25; i ++)
    {
        if(PlayerFarmVars[playerid][DurringBeras] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            if(areaid == PlayerFarmVars[playerid][PadiArea][i])
            {
                ShowKey(playerid, "[Y]- Ambil Padi");
            }
        }

        if(PlayerFarmVars[playerid][DurringCabai] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            if(areaid == PlayerFarmVars[playerid][CabaiArea][i])
            {
                ShowKey(playerid, "[Y]- Ambil Cabai");
            }
        }

        if(PlayerFarmVars[playerid][DurringTebu] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            if(areaid == PlayerFarmVars[playerid][TebuArea][i])
            {
                ShowKey(playerid, "[Y]- Ambil Tebu");
            }
        }
    }
    for(new g = 0; g < 21; g++)
    {
        if(PlayerFarmVars[playerid][DurringGaram] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            if(areaid == PlayerFarmVars[playerid][GaramArea][g])
            {
                ShowKey(playerid, "[Y]- Ambil Gatam Kristal");
            }
        }
    }
    return 1;
}
hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    for(new i = 0; i < 25; i ++)
    {
        if(areaid == PlayerFarmVars[playerid][PadiArea][i])
        {
            HideShortKey(playerid);
        }

        if(areaid == PlayerFarmVars[playerid][CabaiArea][i])
        {
            HideShortKey(playerid);
        }

        if(areaid == PlayerFarmVars[playerid][TebuArea][i])
        {
            HideShortKey(playerid);
        }
    }

    for(new g = 0; g < 21; g++)
    {
        if(areaid == PlayerFarmVars[playerid][GaramArea][g])
        {
            HideShortKey(playerid);
        }
    }

    if(areaid == PlayerFarmVars[playerid][PetaniBeras])
    {
        HideShortKey(playerid);
        DisablePlayerCheckpoint(playerid);
    }
    if(areaid == PlayerFarmVars[playerid][PetaniTebu])
    {
        HideShortKey(playerid);
        DisablePlayerCheckpoint(playerid);
    }
    if(areaid == PlayerFarmVars[playerid][PetaniCabai])
    {
        HideShortKey(playerid);
        DisablePlayerCheckpoint(playerid);
    }
    if(areaid == PlayerFarmVars[playerid][PetaniGaram])
    {
        HideShortKey(playerid);
        DisablePlayerCheckpoint(playerid);
    }
    return 1;
}

#include <YSI\y_hooks>
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && GetPlayerJob(playerid) == JOB_FARMER && !AccountData[playerid][pInjured])
    {
        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PetaniOlah]))
        {
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            new str[512], sstr[200];
            format(str, sizeof str, "Item\tReqruitmen\n");
            strcat(sstr, ""WHITE"Sambal\t"WHITE"Cabe: 4 | Botol: 1\n");
            strcat(sstr, ""WHITE"Beras\t"WHITE"Padi: 4 | Kain: 1\n");
            strcat(sstr, ""WHITE"Gula\t"WHITE"Tebu: 4 | Kain: 1\n");
            strcat(sstr, ""WHITE"Garam\t"WHITE"Garam Kristal: 4 | Botol: 1\n");
            strcat(str, sstr, sizeof sstr);
            ShowPlayerDialog(playerid, DIALOG_FARMER_OLAH, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Mengolah Tanaman", str, "Pilih", "Batal");   
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PetaniTebu]) && !PlayerFarmVars[playerid][DurringTebu])
        {
            if(PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak bisa menggunakan ini jika kamu sedang tugas tanaman yang lain!");
            if(PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak bisa menggunakan ini jika kamu sedang tugas tanaman yang lain!");
            if(PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah mengambil Traktor Gula!");
            PlayerFarmVars[playerid][TraktorGula] = CreateVehicle(531, -52.0804, 102.5144, 3.0834, 240.0631, 16, 16, 60000, 0);

            SwitchVehicleEngine(PlayerFarmVars[playerid][TraktorGula], true);
            SetPlayerSkin(playerid, 161);
            PutPlayerInVehicle(playerid, PlayerFarmVars[playerid][TraktorGula], 0);
            VehicleCore[PlayerFarmVars[playerid][TraktorGula]][vCoreFuel] = 100;
            SetVehicleHealth(PlayerFarmVars[playerid][TraktorGula], 1000);
            PlayerFarmVars[playerid][DurringTebu] = true;

            SetPlayerRaceCheckpoint(playerid, 0, -203.2865, 107.9895, 2.8668, -227.5175, 77.1930, 2.3787, 5.0);
            PetaniIndex[playerid] = 8;
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PetaniBeras]) && !PlayerFarmVars[playerid][DurringBeras])
        {
            if(PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak bisa menggunakan ini jika kamu sedang tugas tanaman yang lain!");
            if(PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak bisa menggunakan ini jika kamu sedang tugas tanaman yang lain!");
            if(PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah mengambil traktor Beras!");
            PlayerFarmVars[playerid][TraktorBeras] = CreateVehicle(531, -41.5297, 102.4031, 3.0809, 60.9345, 13, 13, 60000, 0);

            SwitchVehicleEngine(PlayerFarmVars[playerid][TraktorBeras], true);
            SetPlayerSkin(playerid, 161);
            PutPlayerInVehicle(playerid, PlayerFarmVars[playerid][TraktorBeras], 0);
            VehicleCore[PlayerFarmVars[playerid][TraktorBeras]][vCoreFuel] = 100;
            SetVehicleHealth(PlayerFarmVars[playerid][TraktorBeras], 1000);
            PlayerFarmVars[playerid][DurringBeras] = true;

            SetPlayerRaceCheckpoint(playerid, 0, -203.2865, 107.9895, 2.8668, -227.5175, 77.1930, 2.3787, 5.0);
            PetaniIndex[playerid] = 1;
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PetaniGaram]) && !PlayerFarmVars[playerid][DurringGaram])
        {
            if(PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak bisa menggunakan ini jika kamu sedang tugas tanaman yang lain!");
            if(PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak bisa menggunakan ini jika kamu sedang tugas tanaman yang lain!");
            if(PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak bisa menggunakan ini jika kamu sedang tugas tanaman yang lain!");
            if(PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah mengambil Traktor Garam!");
            PlayerFarmVars[playerid][TraktorGaram] = CreateVehicle(531, -43.2573, 97.4948, 3.0778, 58.7648, 147, 13, 60000, 0);

            SwitchVehicleEngine(PlayerFarmVars[playerid][TraktorGaram], true);
            SetPlayerSkin(playerid, 161);
            PutPlayerInVehicle(playerid, PlayerFarmVars[playerid][TraktorGaram], 0);
            VehicleCore[PlayerFarmVars[playerid][TraktorGaram]][vCoreFuel] = 100;
            SetVehicleHealth(PlayerFarmVars[playerid][TraktorGaram], 1000);
            PlayerFarmVars[playerid][DurringGaram] = true;

            SetPlayerRaceCheckpoint(playerid, 0, -29.4511, 163.4615, 2.3947, -68.4138, 217.7635, 2.4562, 5.0);
            PetaniIndex[playerid] = 22;
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PetaniCabai]) && !PlayerFarmVars[playerid][DurringCabai])
        {
            if(PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak bisa menggunakan ini jika kamu sedang tugas tanaman yang lain!");
            if(PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak bisa menggunakan ini jika kamu sedang tugas tanaman yang lain!");
            if(PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah mengambil Traktor Cabai!");
            PlayerFarmVars[playerid][TraktorCabai] = CreateVehicle(531, -49.2528, 106.9065, 3.0845, 241.3910, 3, 3, 60000, 0);

            SwitchVehicleEngine(PlayerFarmVars[playerid][TraktorCabai], true);
            SetPlayerSkin(playerid, 161);
            PutPlayerInVehicle(playerid, PlayerFarmVars[playerid][TraktorCabai], 0);
            VehicleCore[PlayerFarmVars[playerid][TraktorCabai]][vCoreFuel] = 100;
            SetVehicleHealth(PlayerFarmVars[playerid][TraktorCabai], 1000);
            PlayerFarmVars[playerid][DurringCabai] = true;

            SetPlayerRaceCheckpoint(playerid, 0, -203.2865, 107.9895, 2.8668, -227.5175, 77.1930, 2.3787, 5.0);
            PetaniIndex[playerid] = 15;
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PetaniGaram]) && PlayerFarmVars[playerid][NoDurringGaram])
        {
            SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
            PlayerFarmVars[playerid][DurringGaram] = false;
            PlayerFarmVars[playerid][NoDurringGaram] = false;
            DestroyVehicle(PlayerFarmVars[playerid][TraktorGaram]);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menyelesaikan Panen");
            for(new i = 0; i < 21; i++)
            {
                if(IsValidDynamicObject(PlayerFarmVars[playerid][GaramObject][i]))
                    DestroyDynamicObject(PlayerFarmVars[playerid][GaramObject][i]);
                
                PlayerFarmVars[playerid][GaramObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;

                if(IsValidDynamicArea(PlayerFarmVars[playerid][GaramArea][i]))
                    DestroyDynamicArea(PlayerFarmVars[playerid][GaramArea][i]);
                
                PlayerFarmVars[playerid][GaramArea] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
            }
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PetaniCabai]) && PlayerFarmVars[playerid][NoDurringCabai])
        {
            SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
            PlayerFarmVars[playerid][DurringCabai] = false;
            PlayerFarmVars[playerid][NoDurringCabai] = false;
            DestroyVehicle(PlayerFarmVars[playerid][TraktorCabai]);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menyelesaikan Panen");
            for(new i = 0; i < 25; i ++)
            {
                if(IsValidDynamicObject(PlayerFarmVars[playerid][CabaiObject][i]))
                    DestroyDynamicObject(PlayerFarmVars[playerid][CabaiObject][i]);
                
                PlayerFarmVars[playerid][CabaiObject] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;

                if(IsValidDynamicArea(PlayerFarmVars[playerid][CabaiArea][i]))
                    DestroyDynamicArea(PlayerFarmVars[playerid][CabaiArea][i]);
                
                PlayerFarmVars[playerid][CabaiArea] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
            }
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PetaniBeras]) && PlayerFarmVars[playerid][NoDurringBeras])
        {
            SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
            PlayerFarmVars[playerid][DurringBeras] = false;
            PlayerFarmVars[playerid][NoDurringBeras] = false;
            DestroyVehicle(PlayerFarmVars[playerid][TraktorBeras]);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menyelesaikan Panen");
            for(new i = 0; i < 25; i ++)
            {
                if(IsValidDynamicObject(PlayerFarmVars[playerid][PadiObject][i]))
                    DestroyDynamicObject(PlayerFarmVars[playerid][PadiObject][i]);
                
                if(IsValidDynamicArea(PlayerFarmVars[playerid][PadiArea][i]))
                    DestroyDynamicArea(PlayerFarmVars[playerid][PadiArea][i]);
            }
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PetaniTebu]) && PlayerFarmVars[playerid][NoDurringTebu])
        {
            SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
            PlayerFarmVars[playerid][DurringTebu] = false;
            PlayerFarmVars[playerid][NoDurringTebu] = false;
            DestroyVehicle(PlayerFarmVars[playerid][TraktorGula]);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menyelesaikan Panen");
            for(new i = 0; i < 25; i ++)
            {
                if(IsValidDynamicObject(PlayerFarmVars[playerid][TebuObject][i]))
                    DestroyDynamicObject(PlayerFarmVars[playerid][TebuObject][i]);
                
                if(IsValidDynamicArea(PlayerFarmVars[playerid][TebuArea][i]))
                    DestroyDynamicArea(PlayerFarmVars[playerid][TebuArea][i]);
            }
        }
        

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][0]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][1]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi1", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][2]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi2", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][3]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi3", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][4]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi4", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][5]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi5", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][6]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi6", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][7]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi7", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][8]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi8", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][9]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi9", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][10]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi10", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][11]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi11", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][12]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi12", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][13]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi13", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][14]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi14", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][15]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi15", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][16]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi16", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][17]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi17", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][18]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi18", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][19]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi19", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][20]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi20", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][21]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi21", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][22]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi22", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][23]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi23", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PadiArea][24]))
        {
            if(!PlayerFarmVars[playerid][DurringBeras]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeBerasTimer[playerid] = SetTimerEx("TakePadi24", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL PADI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
            callcmd::me(playerid, "Mengambil Tanaman Padi");
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][0]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][1]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu1", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][2]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu2", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][3]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu3", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][4]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu4", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][5]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu5", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][6]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu6", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][7]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu7", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][8]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu8", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][9]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu9", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][10]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu10", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][11]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu11", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][12]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu12", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][13]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu13", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][14]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu14", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][15]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu15", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][16]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu16", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][17]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu17", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][18]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu18", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][19]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu19", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][20]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu20", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][21]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu21", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][22]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu22", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][23]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu23", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][TebuArea][24]))
        {
            if(!PlayerFarmVars[playerid][DurringTebu]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeTebuTimer[playerid] = SetTimerEx("TakeTebu24", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL TEBU");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][0]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][1]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai1", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][2]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai2", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][3]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai3", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][4]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai4", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][5]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai5", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][6]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai6", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][7]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai7", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][8]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai8", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][9]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai9", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][10]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai10", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][11]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai11", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][12]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai12", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][13]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai13", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][14]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai14", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][15]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai15", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][16]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai16", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][17]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai17", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][18]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai18", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][19]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai19", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][20]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai20", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][21]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai21", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][22]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai22", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][23]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai23", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][CabaiArea][24]))
        {
            if(!PlayerFarmVars[playerid][DurringCabai]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeCabaiTimer[playerid] = SetTimerEx("TakeCabai24", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL CABAI");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][0]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][1]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt1", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][2]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt2", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][3]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt3", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][4]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt4", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][5]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt5", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][6]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt6", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][7]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt7", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][8]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt8", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][9]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt9", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][10]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt10", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][11]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt11", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][12]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt12", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][13]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt13", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][14]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt14", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][15]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt15", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][16]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt16", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][17]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt17", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][18]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt18", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }
        
        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][19]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt19", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }

        if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][GaramArea][20]))
        {
            if(!PlayerFarmVars[playerid][DurringGaram]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memulai pekerjaan ini!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

            HideShortKey(playerid);
            AccountData[playerid][ActivityTime] = 1;
            pTakeSaltTimer[playerid] = SetTimerEx("TakeSalt20", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL GARAM KRISTAL");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 1, 0, 0, 0, 0, 1);
        }
    }
    return 0;
}

hook OnPlayerEnterRaceCP(playerid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        if(GetPlayerJob(playerid) == JOB_FARMER)
        {
            new vehicleid = GetPlayerVehicleID(playerid);
            if(GetVehicleModel(vehicleid) == 531)
            {
                if(PetaniIndex[playerid] == 1)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -227.5175, 77.1930, 2.3787, -268.2854, -45.7135, 3.0817, 5.0);
                    PetaniIndex[playerid] = 2;
                }
                else if(PetaniIndex[playerid] == 2)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -268.2854, -45.7135, 3.0817, -221.5706, 77.9441, 2.5693, 5.0);
                    PetaniIndex[playerid] = 3;
                }
                else if(PetaniIndex[playerid] == 3)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -221.5706, 77.9441, 2.5693, -259.2574, -41.8947, 3.0852, 5.0);
                    PetaniIndex[playerid] = 4;
                }
                else if(PetaniIndex[playerid] == 4)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -259.2574, -41.8947, 3.0852, -214.4924, 71.4195, 2.8969, 5.0);
                    PetaniIndex[playerid] = 5;
                }
                else if(PetaniIndex[playerid] == 5)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -214.4924, 71.4195, 2.8969, -251.4437, -43.8195, 3.0834, 5.0);
                    PetaniIndex[playerid] = 6;
                }
                else if(PetaniIndex[playerid] == 6)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 1, -251.4437, -43.8195, 3.0834, -251.4437, -43.8195, 3.0834, 5.0);
                    PetaniIndex[playerid] = 7;
                }
                else if(PetaniIndex[playerid] == 7)
                {
                    if(IsPlayerInAnyVehicle(playerid))
                    {
                        DestroyVehicle(PlayerFarmVars[playerid][TraktorBeras]);
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerFarmVars[playerid][NoDurringBeras] = true;
                        PetaniIndex[playerid] = 0;
                    }
                    PlayerFarmVars[playerid][PadiObject][0] = CreateDynamicObject(804, -269.075927, -46.980606, 3.197186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][1] = CreateDynamicObject(804, -266.329559, -39.656703, 3.077186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][2] = CreateDynamicObject(804, -264.322265, -33.157264, 2.727186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][3] = CreateDynamicObject(804, -261.176605, -24.054414, 2.537187, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][4] = CreateDynamicObject(804, -258.400665, -15.256098, 2.537187, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][5] = CreateDynamicObject(804, -255.823440, -6.927602, 2.537187, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][6] = CreateDynamicObject(804, -252.830123, 4.056349, 2.537187, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][7] = CreateDynamicObject(804, -250.284332, 12.117441, 2.537187, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][8] = CreateDynamicObject(804, -247.016220, 21.795953, 2.537187, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][9] = CreateDynamicObject(804, -243.372985, 32.358428, 2.537187, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][10] = CreateDynamicObject(804, -236.769454, 30.126550, 2.757186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][11] = CreateDynamicObject(804, -261.815216, -49.884689, 3.197186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][12] = CreateDynamicObject(804, -259.402923, -42.427093, 3.167186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][13] = CreateDynamicObject(804, -257.312194, -35.961093, 3.167186, -0.000002, 0.000007, -19.299995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][14] = CreateDynamicObject(804, -254.621536, -26.676267, 3.187186, -0.000002, -4.899992, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][15] = CreateDynamicObject(804, -251.752731, -17.915098, 2.787186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][16] = CreateDynamicObject(804, -249.175460, -9.586598, 2.807186, -0.000002, 0.000007, -18.399997, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][17] = CreateDynamicObject(804, -246.228759, 1.415925, 2.777186, -0.000001, 0.000007, -15.099994, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][18] = CreateDynamicObject(804, -243.599258, 9.443593, 2.787186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][19] = CreateDynamicObject(804, -240.126846, 19.040409, 2.767186, -0.000002, 0.000007, -18.799997, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][20] = CreateDynamicObject(804, -228.795959, 26.527956, 3.097186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][21] = CreateDynamicObject(804, -232.146560, 16.323709, 3.087186, -0.000002, 0.000007, -18.799997, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][22] = CreateDynamicObject(804, -235.586624, 6.238689, 3.077186, -0.000002, 0.000007, -18.500000, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][23] = CreateDynamicObject(804, -237.887100, -0.834833, 3.087186, -0.000002, 0.000007, -17.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][PadiObject][24] = CreateDynamicObject(804, -241.717193, -12.067602, 3.157186, -0.000002, 0.000007, -18.399997, -1, -1, playerid, 300.00, 300.00);
                    
                    PlayerFarmVars[playerid][PadiArea][0] = CreateDynamicCircle(-269.075927, -46.980606, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][1] = CreateDynamicCircle(-266.329559, -39.656703, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][2] = CreateDynamicCircle(-264.322265, -33.157264, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][3] = CreateDynamicCircle(-261.176605, -24.054414, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][4] = CreateDynamicCircle(-258.400665, -15.256098, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][5] = CreateDynamicCircle(-255.823440, -6.927602, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][6] = CreateDynamicCircle(-252.830123, 4.056349, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][7] = CreateDynamicCircle(-250.284332, 12.117441, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][8] = CreateDynamicCircle(-247.016220, 21.795953, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][9] = CreateDynamicCircle(-243.372985, 32.358428, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][10] = CreateDynamicCircle(-236.769454, 30.126550, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][11] = CreateDynamicCircle(-261.815216, -49.884689, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][12] = CreateDynamicCircle(-259.402923, -42.427093, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][13] = CreateDynamicCircle(-257.312194, -35.961093, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][14] = CreateDynamicCircle(-254.621536, -26.676267, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][15] = CreateDynamicCircle(-251.752731, -17.915098, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][16] = CreateDynamicCircle(-249.175460, -9.586598, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][17] = CreateDynamicCircle(-246.228759, 1.415925, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][18] = CreateDynamicCircle(-243.599258, 9.443593, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][19] = CreateDynamicCircle(-240.126846, 19.040409, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][20] = CreateDynamicCircle(-228.795959, 26.527956, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][21] = CreateDynamicCircle(-232.146560, 16.323709, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][22] = CreateDynamicCircle(-235.586624, 6.238689, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][23] = CreateDynamicCircle(-237.887100, -0.834833, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][PadiArea][24] = CreateDynamicCircle(-241.717193, -12.067602, 2.5, 0, 0, playerid);
                }

                if(PetaniIndex[playerid] == 8)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -227.5175, 77.1930, 2.3787, -268.2854, -45.7135, 3.0817, 5.0);
                    PetaniIndex[playerid] = 9;
                }
                else if(PetaniIndex[playerid] == 9)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -268.2854, -45.7135, 3.0817, -221.5706, 77.9441, 2.5693, 5.0);
                    PetaniIndex[playerid] = 10;
                }
                else if(PetaniIndex[playerid] == 10)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -221.5706, 77.9441, 2.5693, -259.2574, -41.8947, 3.0852, 5.0);
                    PetaniIndex[playerid] = 11;
                }
                else if(PetaniIndex[playerid] == 11)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -259.2574, -41.8947, 3.0852, -214.4924, 71.4195, 2.8969, 5.0);
                    PetaniIndex[playerid] = 12;
                }
                else if(PetaniIndex[playerid] == 12)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -214.4924, 71.4195, 2.8969, -251.4437, -43.8195, 3.0834, 5.0);
                    PetaniIndex[playerid] = 13;
                }
                else if(PetaniIndex[playerid] == 13)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 1, -251.4437, -43.8195, 3.0834, -251.4437, -43.8195, 3.0834, 5.0);
                    PetaniIndex[playerid] = 14;
                }
                else if(PetaniIndex[playerid] == 14)
                {
                    if(IsPlayerInAnyVehicle(playerid))
                    {
                        DestroyVehicle(PlayerFarmVars[playerid][TraktorGula]);
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerFarmVars[playerid][NoDurringTebu] = true;
                        PetaniIndex[playerid] = 0;
                    }
                    PlayerFarmVars[playerid][TebuObject][0] = CreateDynamicObject(806, -269.075927, -46.980606, 3.197186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][1] = CreateDynamicObject(806, -266.329559, -39.656703, 3.077186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][2] = CreateDynamicObject(806, -264.322265, -33.157264, 2.727186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][3] = CreateDynamicObject(806, -261.176605, -24.054414, 2.537187, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][4] = CreateDynamicObject(806, -258.400665, -15.256098, 2.537187, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][5] = CreateDynamicObject(806, -255.823440, -6.927602, 2.537187, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][6] = CreateDynamicObject(806, -252.830123, 4.056349, 2.537187, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][7] = CreateDynamicObject(806, -250.284332, 12.117441, 2.537187, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][8] = CreateDynamicObject(806, -247.016220, 21.795953, 2.537187, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][9] = CreateDynamicObject(806, -243.372985, 32.358428, 2.537187, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][10] = CreateDynamicObject(806, -236.769454, 30.126550, 2.757186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][11] = CreateDynamicObject(806, -261.815216, -49.884689, 3.197186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][12] = CreateDynamicObject(806, -259.402923, -42.427093, 3.167186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][13] = CreateDynamicObject(806, -257.312194, -35.961093, 3.167186, -0.000002, 0.000007, -19.299995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][14] = CreateDynamicObject(806, -254.621536, -26.676267, 3.187186, -0.000002, -4.899992, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][15] = CreateDynamicObject(806, -251.752731, -17.915098, 2.787186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][16] = CreateDynamicObject(806, -249.175460, -9.586598, 2.807186, -0.000002, 0.000007, -18.399997, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][17] = CreateDynamicObject(806, -246.228759, 1.415925, 2.777186, -0.000001, 0.000007, -15.099994, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][18] = CreateDynamicObject(806, -243.599258, 9.443593, 2.787186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][19] = CreateDynamicObject(806, -240.126846, 19.040409, 2.767186, -0.000002, 0.000007, -18.799997, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][20] = CreateDynamicObject(806, -228.795959, 26.527956, 3.097186, -0.000002, 0.000007, -21.799995, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][21] = CreateDynamicObject(806, -232.146560, 16.323709, 3.087186, -0.000002, 0.000007, -18.799997, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][22] = CreateDynamicObject(806, -235.586624, 6.238689, 3.077186, -0.000002, 0.000007, -18.500000, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][23] = CreateDynamicObject(806, -237.887100, -0.834833, 3.087186, -0.000002, 0.000007, -17.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][TebuObject][24] = CreateDynamicObject(806, -241.717193, -12.067602, 3.157186, -0.000002, 0.000007, -18.399997, -1, -1, playerid, 300.00, 300.00);
                    
                    PlayerFarmVars[playerid][TebuArea][0] =  CreateDynamicCircle(-269.075927, -46.980606, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][1] =  CreateDynamicCircle(-266.329559, -39.656703, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][2] =  CreateDynamicCircle(-264.322265, -33.157264, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][3] =  CreateDynamicCircle(-261.176605, -24.054414, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][4] =  CreateDynamicCircle(-258.400665, -15.256098, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][5] =  CreateDynamicCircle(-255.823440, -6.927602, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][6] =  CreateDynamicCircle(-252.830123, 4.056349, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][7] =  CreateDynamicCircle(-250.284332, 12.117441, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][8] =  CreateDynamicCircle(-247.016220, 21.795953, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][9] =  CreateDynamicCircle(-243.372985, 32.358428, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][10] = CreateDynamicCircle(-236.769454, 30.126550, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][11] = CreateDynamicCircle(-261.815216, -49.884689, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][12] = CreateDynamicCircle(-259.402923, -42.427093, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][13] = CreateDynamicCircle(-257.312194, -35.961093, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][14] = CreateDynamicCircle(-254.621536, -26.676267, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][15] = CreateDynamicCircle(-251.752731, -17.915098, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][16] = CreateDynamicCircle(-249.175460, -9.586598, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][17] = CreateDynamicCircle(-246.228759, 1.415925, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][18] = CreateDynamicCircle(-243.599258, 9.443593, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][19] = CreateDynamicCircle(-240.126846, 19.040409, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][20] = CreateDynamicCircle(-228.795959, 26.527956, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][21] = CreateDynamicCircle(-232.146560, 16.323709, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][22] = CreateDynamicCircle(-235.586624, 6.238689, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][23] = CreateDynamicCircle(-237.887100, -0.834833, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][TebuArea][24] = CreateDynamicCircle(-241.717193, -12.067602, 2.5, 0, 0, playerid);
                }

                if(PetaniIndex[playerid] == 15)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -227.5175, 77.1930, 2.3787, -268.2854, -45.7135, 3.0817, 5.0);
                    PetaniIndex[playerid] = 16;
                }
                else if(PetaniIndex[playerid] == 16)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -268.2854, -45.7135, 3.0817, -221.5706, 77.9441, 2.5693, 5.0);
                    PetaniIndex[playerid] = 17;
                }
                else if(PetaniIndex[playerid] == 17)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -221.5706, 77.9441, 2.5693, -259.2574, -41.8947, 3.0852, 5.0);
                    PetaniIndex[playerid] = 18;
                }
                else if(PetaniIndex[playerid] == 18)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -259.2574, -41.8947, 3.0852, -214.4924, 71.4195, 2.8969, 5.0);
                    PetaniIndex[playerid] = 19;
                }
                else if(PetaniIndex[playerid] == 19)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -214.4924, 71.4195, 2.8969, -251.4437, -43.8195, 3.0834, 5.0);
                    PetaniIndex[playerid] = 20;
                }
                else if(PetaniIndex[playerid] == 20)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 1, -251.4437, -43.8195, 3.0834, -251.4437, -43.8195, 3.0834, 5.0);
                    PetaniIndex[playerid] = 21;
                }
                else if(PetaniIndex[playerid] == 21)
                {
                    if(IsPlayerInAnyVehicle(playerid))
                    {
                        DestroyVehicle(PlayerFarmVars[playerid][TraktorCabai]);
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerFarmVars[playerid][NoDurringCabai] = true;
                        PetaniIndex[playerid] = 0;
                    }
                    PlayerFarmVars[playerid][CabaiObject][0] = CreateDynamicObject(2253, -269.075927, -46.980606, 2.387187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][1] = CreateDynamicObject(2253, -266.329559, -39.656703, 2.267187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][2] = CreateDynamicObject(2253, -264.322265, -33.157264, 1.917187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][3] = CreateDynamicObject(2253, -261.176605, -24.054414, 1.727187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][4] = CreateDynamicObject(2253, -258.400665, -15.256098, 1.727187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][5] = CreateDynamicObject(2253, -255.823440, -6.927602, 1.727187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][6] = CreateDynamicObject(2253, -252.830123, 4.056349, 1.727187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][7] = CreateDynamicObject(2253, -250.284332, 12.117441, 1.727187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][8] = CreateDynamicObject(2253, -247.016220, 21.795953, 1.727187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][9] = CreateDynamicObject(2253, -243.372985, 32.358428, 1.727187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][10] = CreateDynamicObject(2253, -236.769454, 30.126552, 1.947187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][11] = CreateDynamicObject(2253, -261.815216, -49.884685, 2.387187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][12] = CreateDynamicObject(2253, -259.402923, -42.427093, 2.357187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][13] = CreateDynamicObject(2253, -257.312194, -35.961093, 2.357187, 0.000000, 0.000000, -19.300001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][14] = CreateDynamicObject(2253, -254.621536, -26.676267, 2.377187, 0.000000, -4.899999, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][15] = CreateDynamicObject(2253, -251.752731, -17.915098, 1.977187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][16] = CreateDynamicObject(2253, -249.175460, -9.586598, 1.997187, 0.000000, 0.000000, -18.399999, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][17] = CreateDynamicObject(2253, -246.228759, 1.415924, 1.967187, 0.000000, 0.000000, -15.099997, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][18] = CreateDynamicObject(2253, -243.599258, 9.443593, 1.977187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][19] = CreateDynamicObject(2253, -240.126846, 19.040409, 1.957187, 0.000000, 0.000000, -18.799997, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][20] = CreateDynamicObject(2253, -228.795959, 26.527957, 2.287187, 0.000000, 0.000000, -21.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][21] = CreateDynamicObject(2253, -232.146560, 16.323709, 2.277187, 0.000000, 0.000000, -18.799997, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][22] = CreateDynamicObject(2253, -235.586624, 6.238689, 2.267187, 0.000000, 0.000000, -18.500000, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][23] = CreateDynamicObject(2253, -237.887100, -0.834833, 2.277187, 0.000000, 0.000000, -17.800001, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][CabaiObject][24] = CreateDynamicObject(2253, -241.717193, -12.067602, 2.347187, 0.000000, 0.000000, -18.399999, -1, -1, playerid, 300.00, 300.00);
                    
                    PlayerFarmVars[playerid][CabaiArea][0] =  CreateDynamicCircle(-269.075927, -46.980606, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][1] =  CreateDynamicCircle(-266.329559, -39.656703, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][2] =  CreateDynamicCircle(-264.322265, -33.157264, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][3] =  CreateDynamicCircle(-261.176605, -24.054414, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][4] =  CreateDynamicCircle(-258.400665, -15.256098, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][5] =  CreateDynamicCircle(-255.823440, -6.927602, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][6] =  CreateDynamicCircle(-252.830123, 4.056349, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][7] =  CreateDynamicCircle(-250.284332, 12.117441, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][8] =  CreateDynamicCircle(-247.016220, 21.795953, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][9] =  CreateDynamicCircle(-243.372985, 32.358428, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][10] = CreateDynamicCircle(-236.769454, 30.126552, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][11] = CreateDynamicCircle(-261.815216, -49.884685, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][12] = CreateDynamicCircle(-259.402923, -42.427093, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][13] = CreateDynamicCircle(-257.312194, -35.961093, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][14] = CreateDynamicCircle(-254.621536, -26.676267, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][15] = CreateDynamicCircle(-251.752731, -17.915098, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][16] = CreateDynamicCircle(-249.175460, -9.586598, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][17] = CreateDynamicCircle(-246.228759, 1.415924, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][18] = CreateDynamicCircle(-243.599258, 9.443593, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][19] = CreateDynamicCircle(-240.126846, 19.040409, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][20] = CreateDynamicCircle(-228.795959, 26.527957, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][21] = CreateDynamicCircle(-232.146560, 16.323709, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][22] = CreateDynamicCircle(-235.586624, 6.238689, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][23] = CreateDynamicCircle(-237.887100, -0.834833, 2.5, 0, 0, playerid);
                    PlayerFarmVars[playerid][CabaiArea][24] = CreateDynamicCircle(-241.717193, -12.067602, 2.5, 0, 0, playerid);
                }

                else if(PetaniIndex[playerid] == 22)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -68.4138, 217.7635, 2.4562, 22.4618, 164.4134, 2.3530, 5.0);
                    PetaniIndex[playerid] = 23;
                }
                else if(PetaniIndex[playerid] == 23)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, 22.4618, 164.4134, 2.3530, -59.9101, 217.2119, 2.0538, 5.0);
                    PetaniIndex[playerid] = 24;
                }
                else if(PetaniIndex[playerid] == 24)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, -59.9101, 217.2119, 2.0538, 20.4742, 173.0184, 1.9230, 5.0);
                    PetaniIndex[playerid] = 25;
                }
                else if(PetaniIndex[playerid] == 25)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 0, 20.4742, 173.0184, 1.9230, -73.3060, 222.7676, 2.5259, 5.0);
                    PetaniIndex[playerid] = 26;
                }
                else if(PetaniIndex[playerid] == 26)
                {
                    DisablePlayerRaceCheckpoint(playerid);
                    PlayerPlaySound(playerid, 1139, 0, 0, 0);
                    SetPlayerRaceCheckpoint(playerid, 1, -73.3060, 222.7676, 2.5259, -73.3060, 222.7676, 2.5259, 5.0);
                    PetaniIndex[playerid] = 27;
                }
                else if(PetaniIndex[playerid] == 27)
                {
                    if(IsPlayerInAnyVehicle(playerid))
                    {
                        DestroyVehicle(PlayerFarmVars[playerid][TraktorGaram]);
                        DisablePlayerRaceCheckpoint(playerid);
                        PlayerFarmVars[playerid][NoDurringGaram] = true;
                        PetaniIndex[playerid] = 0;
                    }
                    PlayerFarmVars[playerid][GaramObject][0] =  CreateDynamicObject(1611, -87.578872, 230.830139, 2.323263, 0.000000, 0.000000, -33.399990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][1] =  CreateDynamicObject(1611, -78.846328, 225.072113, 1.683263, 0.000000, 0.000000, -33.399990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][2] =  CreateDynamicObject(1611, -68.899101, 220.992691, 1.563263, 0.000000, 0.000000, -33.399990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][3] =  CreateDynamicObject(1611, -58.152515, 214.601425, 1.423264, 0.000000, 0.000000, -33.399990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][4] =  CreateDynamicObject(1611, -48.468708, 211.527862, 1.053263, -19.499998, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][5] =  CreateDynamicObject(1611, -40.902606, 207.503097, 1.090969, -22.400003, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][6] =  CreateDynamicObject(1611, -28.616977, 200.852493, 0.896814, -22.400003, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][7] =  CreateDynamicObject(1611, -20.534372, 193.952255, 1.431900, -1.100000, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][8] =  CreateDynamicObject(1611, -7.699423, 187.099029, 1.431900, -1.100000, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][9] =  CreateDynamicObject(1611, 2.727315, 181.531677, 1.431900, -1.100000, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][10] = CreateDynamicObject(1611, 14.530655, 174.742126, 1.450153, -1.100000, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][11] = CreateDynamicObject(1611, 23.358150, 169.427947, 1.460328, -1.100000, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][12] = CreateDynamicObject(1611, 24.403676, 171.386123, 0.582826, -33.700000, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][13] = CreateDynamicObject(1611, 19.250391, 174.367263, 0.616073, -33.700000, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][14] = CreateDynamicObject(1611, 15.262496, 176.707336, 0.696473, -33.700000, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][15] = CreateDynamicObject(1611, 5.391102, 182.465591, 0.818432, -33.700000, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][16] = CreateDynamicObject(1611, -6.413714, 188.806594, 0.868349, -33.700000, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][17] = CreateDynamicObject(1611, -15.103727, 193.889968, 0.715739, -33.700000, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][18] = CreateDynamicObject(1611, -21.181570, 197.135238, 0.715739, -33.700000, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);
                    PlayerFarmVars[playerid][GaramObject][19] = CreateDynamicObject(1611, -29.611364, 198.799133, 1.441898, -1.100000, 0.000000, -28.099990, -1, -1, playerid, 300.00, 300.00);

                    PlayerFarmVars[playerid][GaramArea][0] =  CreateDynamicCircle(-87.578872, 230.830139, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][1] =  CreateDynamicCircle(-78.846328, 225.072113, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][2] =  CreateDynamicCircle(-68.899101, 220.992691, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][3] =  CreateDynamicCircle(-58.152515, 214.601425, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][4] =  CreateDynamicCircle(-48.468708, 211.527862, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][5] =  CreateDynamicCircle(-40.902606, 207.503097, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][6] =  CreateDynamicCircle(-28.616977, 200.852493, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][7] =  CreateDynamicCircle(-20.534372, 193.952255, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][8] =  CreateDynamicCircle(-7.699423, 187.099029, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][9] =  CreateDynamicCircle(2.727315, 181.531677, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][10] = CreateDynamicCircle(14.530655, 174.742126, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][11] = CreateDynamicCircle(23.358150, 169.427947, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][12] = CreateDynamicCircle(24.403676, 171.386123, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][13] = CreateDynamicCircle(19.250391, 174.367263, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][14] = CreateDynamicCircle(15.262496, 176.707336, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][15] = CreateDynamicCircle(5.391102, 182.465591, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][16] = CreateDynamicCircle(-6.413714, 188.806594, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][17] = CreateDynamicCircle(-15.103727, 193.889968, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][18] = CreateDynamicCircle(-21.181570, 197.135238, 2.0, 0, 0, playerid);
                    PlayerFarmVars[playerid][GaramArea][19] = CreateDynamicCircle(-29.611364, 198.799133, 2.0, 0, 0, playerid);
                }
            }
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_FARMER_OLAH:
        {
            if(!response) return 0;
            switch(listitem)
            {
                case 0:
                {
                    AccountData[playerid][ActivityTime] = 1;
                    pTimerOlah[playerid] = SetTimerEx("ProcessSambel", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH CABE");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
                case 1:
                {
                    AccountData[playerid][ActivityTime] = 1;
                    pTimerOlah[playerid] = SetTimerEx("ProcessBeras", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH PADI");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
                case 2:
                {
                    AccountData[playerid][ActivityTime] = 1;
                    pTimerOlah[playerid] = SetTimerEx("ProcessGula", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH TEBU");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
                case 3:
                {
                    AccountData[playerid][ActivityTime] = 1;
                    pTimerOlah[playerid] = SetTimerEx("ProcessGaram", 1000, true, "d", playerid);
                    PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGOLAH GARAM KRISTAL");
                    ShowProgressBar(playerid);
                    ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                }
            }
        }
    }
    return 0;
}
CMD:buyplant(playerid, params[])
{
    new name[32], total;
    if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PetaniStore]))
    {
        if(sscanf(params, "ds[32]", total, name))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/buyplant [jumlah] [nama tanaman]");

        if(strcmp(name, "Gula", true) == 0)
        {
            new price = 3;
            new pay = total * price;
            if(Stock < total) return ShowTDN(playerid, NOTIFICATION_ERROR, "Stock tidak ada!");
            if(GetPlayerMoney(playerid) < total) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
            
            Inventory_Add(playerid, "Gula", 1575, total);
            ShowItemBox(playerid, sprintf("ADDED %dx", total), "GULA", 1575);
            Stock -= total;
            Lumbung_Save();
            GiveMoney(playerid, -pay);
            
            static
                sstr[10000];

            format(sstr, sizeof sstr, ""YELLOW"[Lumbung Petani]\n\n"YELLOW"`/sellplant`"WHITE" -> Jual semua tanaman.\n"YELLOW"[Harga Jual]:\n"WHITE"Sambal "VERONA_GREEN"$18/sambal\n"WHITE"Beras "VERONA_GREEN"$18/beras\n"WHITE"Gula "VERONA_GREEN"$18/Gula\n"WHITE"Garam "VERONA_GREEN"$18/Garam\n\n"YELLOW"`/buyplant` "WHITE"-> Beli tanaman.\n"YELLOW"[Harga Beli];\n"WHITE"Sambal "VERONA_GREEN"$3/Sambal\n"WHITE"Beras "VERONA_GREEN"$3/Beras\n"WHITE"Gula "VERONA_GREEN"$3/Gula\n"WHITE"Garam "VERONA_GREEN"$3/Garam\n\n"YELLOW"[Stock]: %dx", Stock);
            UpdateDynamic3DTextLabelText(PlayerFarmVars[playerid][StoreLabel], -1, sstr);
        }
        else if(strcmp(name, "Beras", true) == 0)
        {
            new price = 3;
            new pay = total * price;
            if(Stock < total) return ShowTDN(playerid, NOTIFICATION_ERROR, "Stock tidak ada!");
            if(GetPlayerMoney(playerid) < total) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
            
            Inventory_Add(playerid, "Beras", 2060, total);
            ShowItemBox(playerid, sprintf("ADDED %dx", total), "BERAS", 2060);
            Stock -= total;
            Lumbung_Save();
            GiveMoney(playerid, -pay);
            
            static
                sstr[10000];

            format(sstr, sizeof sstr, ""YELLOW"[Lumbung Petani]\n\n"YELLOW"`/sellplant`"WHITE" -> Jual semua tanaman.\n"YELLOW"[Harga Jual]:\n"WHITE"Sambal "VERONA_GREEN"$18/sambal\n"WHITE"Beras "VERONA_GREEN"$18/beras\n"WHITE"Gula "VERONA_GREEN"$18/Gula\n"WHITE"Garam "VERONA_GREEN"$18/Garam\n\n"YELLOW"`/buyplant` "WHITE"-> Beli tanaman.\n"YELLOW"[Harga Beli];\n"WHITE"Sambal "VERONA_GREEN"$3/Sambal\n"WHITE"Beras "VERONA_GREEN"$3/Beras\n"WHITE"Gula "VERONA_GREEN"$3/Gula\n"WHITE"Garam "VERONA_GREEN"$3/Garam\n\n"YELLOW"[Stock]: %dx", Stock);
            UpdateDynamic3DTextLabelText(PlayerFarmVars[playerid][StoreLabel], -1, sstr);
        }
        else if(strcmp(name, "Sambal", true) == 0)
        {
            new price = 3;
            new pay = total * price;
            if(Stock < total) return ShowTDN(playerid, NOTIFICATION_ERROR, "Stock tidak ada!");
            if(GetPlayerMoney(playerid) < total) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
            
            Inventory_Add(playerid, "Sambal", 11722, total);
            ShowItemBox(playerid, sprintf("ADDED %dx", total), "SAMBAL", 11722);
            Stock -= total;
            Lumbung_Save();
            GiveMoney(playerid, -pay);
            
            static
                sstr[10000];

            format(sstr, sizeof sstr, ""YELLOW"[Lumbung Petani]\n\n"YELLOW"`/sellplant`"WHITE" -> Jual semua tanaman.\n"YELLOW"[Harga Jual]:\n"WHITE"Sambal "VERONA_GREEN"$18/sambal\n"WHITE"Beras "VERONA_GREEN"$18/beras\n"WHITE"Gula "VERONA_GREEN"$18/Gula\n"WHITE"Garam "VERONA_GREEN"$18/Garam\n\n"YELLOW"`/buyplant` "WHITE"-> Beli tanaman.\n"YELLOW"[Harga Beli];\n"WHITE"Sambal "VERONA_GREEN"$3/Sambal\n"WHITE"Beras "VERONA_GREEN"$3/Beras\n"WHITE"Gula "VERONA_GREEN"$3/Gula\n"WHITE"Garam "VERONA_GREEN"$3/Garam\n\n"YELLOW"[Stock]: %dx", Stock);
            UpdateDynamic3DTextLabelText(PlayerFarmVars[playerid][StoreLabel], -1, sstr);
        }
        else if(strcmp(name, "Garam", true) == 0)
        {
            new price = 3;
            new pay = total * price;
            if(Stock < total) return ShowTDN(playerid, NOTIFICATION_ERROR, "Stock tidak ada!");
            if(GetPlayerMoney(playerid) < total) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup!");
            
            Inventory_Add(playerid, "Garam", 1279, total);
            ShowItemBox(playerid, sprintf("ADDED %dx", total), "GARAM", 1279);
            Stock -= total;
            Lumbung_Save();
            GiveMoney(playerid, -pay);
            
            static
                sstr[10000];

            format(sstr, sizeof sstr, ""YELLOW"[Lumbung Petani]\n\n"YELLOW"`/sellplant`"WHITE" -> Jual semua tanaman.\n"YELLOW"[Harga Jual]:\n"WHITE"Sambal "VERONA_GREEN"$18/sambal\n"WHITE"Beras "VERONA_GREEN"$18/beras\n"WHITE"Gula "VERONA_GREEN"$18/Gula\n"WHITE"Garam "VERONA_GREEN"$18/Garam\n\n"YELLOW"`/buyplant` "WHITE"-> Beli tanaman.\n"YELLOW"[Harga Beli];\n"WHITE"Sambal "VERONA_GREEN"$3/Sambal\n"WHITE"Beras "VERONA_GREEN"$3/Beras\n"WHITE"Gula "VERONA_GREEN"$3/Gula\n"WHITE"Garam "VERONA_GREEN"$3/Garam\n\n"YELLOW"[Stock]: %dx", Stock);
            UpdateDynamic3DTextLabelText(PlayerFarmVars[playerid][StoreLabel], -1, sstr);
        }
    }
    return 1;
}

CMD:setlumbung(playerid, params[])
{
    if(CheckAdmin(playerid, 6))
        return PermissionError(playerid);

    new jumlah;
    if(sscanf(params, "d", jumlah))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setlumbung [jumlah]");
    
    Stock += jumlah;
    Lumbung_Save();
    static
        sstr[10000];

    format(sstr, sizeof sstr, ""YELLOW"[Lumbung Petani]\n\n"YELLOW"`/sellplant`"WHITE" -> Jual semua tanaman.\n"YELLOW"[Harga Jual]:\n"WHITE"Sambal "VERONA_GREEN"$18/sambal\n"WHITE"Beras "VERONA_GREEN"$18/beras\n"WHITE"Gula "VERONA_GREEN"$18/Gula\n"WHITE"Garam "VERONA_GREEN"$18/Garam\n\n"YELLOW"`/buyplant` "WHITE"-> Beli tanaman.\n"YELLOW"[Harga Beli];\n"WHITE"Sambal "VERONA_GREEN"$3/Sambal\n"WHITE"Beras "VERONA_GREEN"$3/Beras\n"WHITE"Gula "VERONA_GREEN"$3/Gula\n"WHITE"Garam "VERONA_GREEN"$3/Garam\n\n"YELLOW"[Stock]: %dx", Stock);
    UpdateDynamic3DTextLabelText(PlayerFarmVars[playerid][StoreLabel], -1, sstr);
    return 1;
}

CMD:sellplant(playerid, params[])
{
    static 
        sstr[10000];
        
    new name[32], str[128];
    if(IsPlayerInDynamicArea(playerid, PlayerFarmVars[playerid][PetaniStore]))
    {
        if(sscanf(params, "s[32]", name))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/sellplant [nama tanaman]");

        if(strcmp(name, "Gula", true) == 0)
        {
            if(Inventory_Count(playerid, "Gula") < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki gula!");
            new total = Inventory_Count(playerid, "Gula");
            new pay = total * 18;

            Inventory_Remove(playerid, "Gula", total);
            format(str, sizeof str, ""GREEN"[!] "WHITE"Anda berhasil menjual gula anda sebanyak "YELLOW"%dx "WHITE"seharga "VERONA_GREEN"%s", total, FormatMoney(pay));
            GiveMoney(playerid, pay);
            SendClientMessageEx(playerid, COLOR_WHITE, str);
            ShowItemBox(playerid, sprintf("ADDED %dx", pay), "UANG", 1212);
            Stock += total;
            Lumbung_Save();

            format(sstr, sizeof sstr, ""YELLOW"[Lumbung Petani]\n\n"YELLOW"`/sellplant`"WHITE" -> Jual semua tanaman.\n"YELLOW"[Harga Jual]:\n"WHITE"Sambal "VERONA_GREEN"$18/sambal\n"WHITE"Beras "VERONA_GREEN"$18/beras\n"WHITE"Gula "VERONA_GREEN"$18/Gula\n"WHITE"Garam "VERONA_GREEN"$18/Garam\n\n"YELLOW"`/buyplant` "WHITE"-> Beli tanaman.\n"YELLOW"[Harga Beli];\n"WHITE"Sambal "VERONA_GREEN"$3/Sambal\n"WHITE"Beras "VERONA_GREEN"$3/Beras\n"WHITE"Gula "VERONA_GREEN"$3/Gula\n"WHITE"Garam "VERONA_GREEN"$3/Garam\n\n"YELLOW"[Stock]: %dx", Stock);
            UpdateDynamic3DTextLabelText(PlayerFarmVars[playerid][StoreLabel], -1, sstr);
        }
        else if(strcmp(name, "Beras", true) == 0)
        {
            if(Inventory_Count(playerid, "Beras") < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki beras!");
            new total = Inventory_Count(playerid, "Beras");
            new pay = total * 18;

            Inventory_Remove(playerid, "Beras", total);
            format(str, sizeof str, ""GREEN"[!] "WHITE"Anda berhasil menjual beras anda sebanyak "YELLOW"%dx "WHITE"seharga "VERONA_GREEN"%s", total, FormatMoney(pay));
            GiveMoney(playerid, pay);
            SendClientMessageEx(playerid, -1, str);
            ShowItemBox(playerid, sprintf("ADDED %dx", pay), "UANG", 1212);
            Stock += total;
            Lumbung_Save();

            format(sstr, sizeof sstr, ""YELLOW"[Lumbung Petani]\n\n"YELLOW"`/sellplant`"WHITE" -> Jual semua tanaman.\n"YELLOW"[Harga Jual]:\n"WHITE"Sambal "VERONA_GREEN"$18/sambal\n"WHITE"Beras "VERONA_GREEN"$18/beras\n"WHITE"Gula "VERONA_GREEN"$18/Gula\n"WHITE"Garam "VERONA_GREEN"$18/Garam\n\n"YELLOW"`/buyplant` "WHITE"-> Beli tanaman.\n"YELLOW"[Harga Beli];\n"WHITE"Sambal "VERONA_GREEN"$3/Sambal\n"WHITE"Beras "VERONA_GREEN"$3/Beras\n"WHITE"Gula "VERONA_GREEN"$3/Gula\n"WHITE"Garam "VERONA_GREEN"$3/Garam\n\n"YELLOW"[Stock]: %dx", Stock);
            UpdateDynamic3DTextLabelText(PlayerFarmVars[playerid][StoreLabel], -1, sstr);
        }
        else if(strcmp(name, "Garam", true) == 0)
        {
            if(Inventory_Count(playerid, "Garam") < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Garam!");
            new total = Inventory_Count(playerid, "Garam");
            new pay = total * 18;

            Inventory_Remove(playerid, "Garam", total);
            format(str, sizeof str, ""GREEN"[!] "WHITE"Anda berhasil menjual Garam anda sebanyak "YELLOW"%dx "WHITE"seharga "VERONA_GREEN"%s", total, FormatMoney(pay));
            GiveMoney(playerid, pay);
            SendClientMessageEx(playerid, -1, str);
            ShowItemBox(playerid, sprintf("ADDED %dx", pay), "UANG", 1212);
            Stock += total;
            Lumbung_Save();

            format(sstr, sizeof sstr, ""YELLOW"[Lumbung Petani]\n\n"YELLOW"`/sellplant`"WHITE" -> Jual semua tanaman.\n"YELLOW"[Harga Jual]:\n"WHITE"Sambal "VERONA_GREEN"$18/sambal\n"WHITE"Beras "VERONA_GREEN"$18/beras\n"WHITE"Gula "VERONA_GREEN"$18/Gula\n"WHITE"Garam "VERONA_GREEN"$18/Garam\n\n"YELLOW"`/buyplant` "WHITE"-> Beli tanaman.\n"YELLOW"[Harga Beli];\n"WHITE"Sambal "VERONA_GREEN"$3/Sambal\n"WHITE"Beras "VERONA_GREEN"$3/Beras\n"WHITE"Gula "VERONA_GREEN"$3/Gula\n"WHITE"Garam "VERONA_GREEN"$3/Garam\n\n"YELLOW"[Stock]: %dx", Stock);
            UpdateDynamic3DTextLabelText(PlayerFarmVars[playerid][StoreLabel], -1, sstr);
        }
        else if(strcmp(name, "Sambal", true) == 0)
        {
            if(Inventory_Count(playerid, "Sambal") < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Sambal!");
            new total = Inventory_Count(playerid, "Sambal");
            new pay = total * 18;

            Inventory_Remove(playerid, "Sambal", total);
            format(str, sizeof str, ""GREEN"[!] "WHITE"Anda berhasil menjual Sambal anda sebanyak "YELLOW"%dx "WHITE"seharga "VERONA_GREEN"%s", total, FormatMoney(pay));
            GiveMoney(playerid, pay);
            SendClientMessageEx(playerid, -1, str);
            ShowItemBox(playerid, sprintf("ADDED %dx", pay), "UANG", 1212);
            Stock += total;
            Lumbung_Save();

            format(sstr, sizeof sstr, ""YELLOW"[Lumbung Petani]\n\n"YELLOW"`/sellplant`"WHITE" -> Jual semua tanaman.\n"YELLOW"[Harga Jual]:\n"WHITE"Sambal "VERONA_GREEN"$18/sambal\n"WHITE"Beras "VERONA_GREEN"$18/beras\n"WHITE"Gula "VERONA_GREEN"$18/Gula\n"WHITE"Garam "VERONA_GREEN"$18/Garam\n\n"YELLOW"`/buyplant` "WHITE"-> Beli tanaman.\n"YELLOW"[Harga Beli];\n"WHITE"Sambal "VERONA_GREEN"$3/Sambal\n"WHITE"Beras "VERONA_GREEN"$3/Beras\n"WHITE"Gula "VERONA_GREEN"$3/Gula\n"WHITE"Garam "VERONA_GREEN"$3/Garam\n\n"YELLOW"[Stock]: %dx", Stock);
            UpdateDynamic3DTextLabelText(PlayerFarmVars[playerid][StoreLabel], -1, sstr);
        }
    }
    return 1;
}