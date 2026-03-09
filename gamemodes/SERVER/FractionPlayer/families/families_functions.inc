#include <YSI\y_hooks>

#define DIALOG_FAMSTAKE_MONEY2      13201
#define DIALOG_CONFIRM_MONEY        13202

new ListedFamItem[MAX_PLAYERS][100];
new pTimerWashRedMoney[MAX_PLAYERS] = {-1, ...};
new pTimerJualMarijuana[MAX_PLAYERS] = {-1, ...};

enum familiesData {
    famID,
    famName[50],
    famLeader[MAX_PLAYER_NAME],
    famType[32],
    famMoney,
    STREAMER_TAG_3D_TEXT_LABEL:famBrankasLabel,
    STREAMER_TAG_3D_TEXT_LABEL:famBosDeskLabel,

    Float:famBosDeskPos[3],
    Float:famBrankasPos[3],
    Float:famExtPos[4],
    Float:famIntPos[4],
    STREAMER_TAG_AREA:famDoorArea,
    famIcon,
    famPickExt,
    famPickInt,
    famInterior,
    Text3D:famLabelExt,
    Text3D:famLabelInt,

    famWeapon[5],
    famAmmo[5],
    famRedMoney,

    Float:famgaragePos[3],
    Float:famgaragespawnPos[4],
    STREAMER_TAG_OBJECT:famgarageObject,
    STREAMER_TAG_AREA:famgarageArea,
    famgarageInt,
    famgarageWorld,
};
new FamData[MAX_FAMILIES][familiesData],
    Iterator:Families<MAX_FAMILIES>;

enum e_familiesstuffs
{
    STREAMER_TAG_AREA:JualMarijuana,
    STREAMER_TAG_AREA:WashRedMoney,
    STREAMER_TAG_AREA:BlackmarketArea,
    STREAMER_TAG_3D_TEXT_LABEL:BlackmarketLabel,
    STREAMER_TAG_OBJECT:WashObjects,
};
new Families_Stuffs[e_familiesstuffs];

static const FamiliesRank[7][] = {
    "N/A",
    "Relasi",
    "Outsider",
    "Insider",
    "Tangan Kanan",
    "Wakil Ketua",
    "Ketua"
};

ShowFamiliesWeapon(playerid, famid)
{
    if(famid == -1) return 0;

    static shstr[596];

    shstr[0] = 0;

    format(shstr, sizeof(shstr), "#\tWeapon\tAmmo\n");
    for (new i = 0; i < 5; i ++) 
    {
        if(!FamData[famid][famWeapon][i])
            format(shstr, sizeof(shstr), "%s"ORANGE"%d\t"ORANGE"Kosong\t"ORANGE"-\n", shstr, i);
        
        else 
            format(shstr, sizeof(shstr), "%s"ORANGE"%d\t"ORANGE"%s\t"ORANGE"%d\n", shstr, i, ReturnWeaponName(FamData[famid][famWeapon][i]), FamData[famid][famAmmo][i]);
    }
    ShowPlayerDialog(playerid, DIALOG_FAMS_WEAPON, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Weapon Chest", shstr, "Pilih", "Batal");
    return 1;
}

GetFamiliesName(playerid)
{
    new frmtname[100];
    format(frmtname, sizeof(frmtname), "%s", FamData[AccountData[playerid][pFamily]][famName]);
    return frmtname;
}

IsPlayerNearGarageFamily(playerid)
{
    foreach(new i : Families) if (IsPlayerInRangeOfPoint(playerid, 2.0, FamData[i][famgaragePos][0], FamData[i][famgaragePos][1], FamData[i][famgaragePos][2]))
    {
        return i;
    }
    return -1;
}

Families_Save(famid)
{
    new query[2046];
    format(query, sizeof(query), "UPDATE families SET F_Name='%s', F_Leader='%s', F_Money='%d', F_Icon='%d', F_BrankasX='%f', F_BrankasY='%f', F_BrankasZ='%f', F_BosDeskX='%f', F_BosDeskY='%f', F_BosDeskZ='%f', F_ExtPosX='%f', F_ExtPosY='%f', F_ExtPosZ='%f', F_ExtPosA='%f', F_IntPosX='%f', F_IntPosY='%f', F_IntPosZ='%f', F_IntPosA='%f', F_Interior='%d', F_Weapon1='%d', F_Weapon2='%d', F_Weapon3='%d', F_Weapon4='%d', F_Weapon5='%d', F_Ammo1='%d', F_Ammo2='%d', F_Ammo3='%d', F_Ammo4='%d', F_Ammo5='%d', F_RedMoney='%d', \
    F_GarageX=%f, F_GarageY=%f, F_GarageZ=%f,  F_GarageSpawnX=%f, F_GarageSpawnY=%f, F_GarageSpawnZ=%f, F_GarageSpawnA=%f, F_GarageInterior=%d, F_GarageWorld=%d, F_Type='%s' WHERE F_ID='%d'",
    FamData[famid][famName],
    FamData[famid][famLeader],
    FamData[famid][famMoney],
    FamData[famid][famIcon],
    FamData[famid][famBrankasPos][0],
    FamData[famid][famBrankasPos][1],
    FamData[famid][famBrankasPos][2],
    FamData[famid][famBosDeskPos][0],
    FamData[famid][famBosDeskPos][1],
    FamData[famid][famBosDeskPos][2],
    FamData[famid][famExtPos][0],
    FamData[famid][famExtPos][1],
    FamData[famid][famExtPos][2],
    FamData[famid][famExtPos][3],
    FamData[famid][famIntPos][0],
    FamData[famid][famIntPos][1],
    FamData[famid][famIntPos][2],
    FamData[famid][famIntPos][3],
    FamData[famid][famInterior],
    FamData[famid][famWeapon][0],
    FamData[famid][famWeapon][1],
    FamData[famid][famWeapon][2],
    FamData[famid][famWeapon][3],
    FamData[famid][famWeapon][4],
    FamData[famid][famAmmo][0],
    FamData[famid][famAmmo][1],
    FamData[famid][famAmmo][2],
    FamData[famid][famAmmo][3],
    FamData[famid][famAmmo][4],
    FamData[famid][famRedMoney],
    FamData[famid][famgaragePos][0],
    FamData[famid][famgaragePos][1],
    FamData[famid][famgaragePos][2],
    FamData[famid][famgaragespawnPos][0],
    FamData[famid][famgaragespawnPos][1],
    FamData[famid][famgaragespawnPos][2],
    FamData[famid][famgaragespawnPos][3],
    FamData[famid][famgarageInt],
    FamData[famid][famgarageWorld],
    FamData[famid][famType],
    famid);
    return mysql_tquery(g_SQL, query);
}

IsDoorMyFamilie(playerid)
{
    foreach(new famid : Families) 
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.0, FamData[famid][famExtPos][0], FamData[famid][famExtPos][1], FamData[famid][famExtPos][2])) {
            return famid;
        }
    }
    return -1;
}

Families_Refresh(id)
{
    if(id != -1)
    {
        if(DestroyDynamicArea(FamData[id][famgarageArea]))
            FamData[id][famgarageArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
        
        if(DestroyDynamicObject(FamData[id][famgarageObject]))
            FamData[id][famgarageObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        
        if(DestroyDynamic3DTextLabel(FamData[id][famBrankasLabel]))
            FamData[id][famBrankasLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            
        if(DestroyDynamic3DTextLabel(FamData[id][famBosDeskLabel]))
            FamData[id][famBosDeskLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        if(DestroyDynamic3DTextLabel(FamData[id][famLabelExt]))
            FamData[id][famLabelExt] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
            
        if(DestroyDynamic3DTextLabel(FamData[id][famLabelInt]))
            FamData[id][famLabelInt] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        if(DestroyDynamicPickup(FamData[id][famPickExt]))
            FamData[id][famPickExt] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
            
        if(DestroyDynamicPickup(FamData[id][famPickInt]))
            FamData[id][famPickInt] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;

        new minsty[512];
        format(minsty, sizeof(minsty), "DO NOT ENTER!");
        FamData[id][famPickExt] = CreateDynamicPickup(FamData[id][famIcon], 23, FamData[id][famExtPos][0], FamData[id][famExtPos][1], FamData[id][famExtPos][2], 0, 0, -1, 50);
        FamData[id][famLabelExt] = CreateDynamic3DTextLabel(minsty, COLOR_WHITE, FamData[id][famExtPos][0], FamData[id][famExtPos][1], FamData[id][famExtPos][2] + 0.35, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0);
        FamData[id][famDoorArea] = CreateDynamicSphere(FamData[id][famExtPos][0], FamData[id][famExtPos][1], FamData[id][famExtPos][2], 2.5, 0, 0);

        if(FamData[id][famIntPos][0] != 0.0 && FamData[id][famIntPos][1] != 0.0 && FamData[id][famIntPos][2] != 0.0)
        {
            format(minsty, sizeof(minsty), "DO NOT ENTER!");

            FamData[id][famLabelInt] = CreateDynamic3DTextLabel(minsty, COLOR_WHITE, FamData[id][famIntPos][0], FamData[id][famIntPos][1], FamData[id][famIntPos][2]+0.35, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, id, FamData[id][famInterior], -1, 5.0, -1, 0);
            FamData[id][famPickInt] = CreateDynamicPickup(FamData[id][famIcon], 23, FamData[id][famIntPos][0], FamData[id][famIntPos][1], FamData[id][famIntPos][2], id, FamData[id][famInterior], -1, 50);
        }

        if(FamData[id][famBrankasPos][0] != 0.0)
        {
            FamData[id][famBrankasLabel] = CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE" Brankas", -1, FamData[id][famBrankasPos][0], FamData[id][famBrankasPos][1],FamData[id][famBrankasPos][2] + 0.25, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, id, FamData[id][famInterior], -1);
        }

        if(FamData[id][famBosDeskPos][0] != 0.0 && FamData[id][famBosDeskPos][1] != 0.0 && FamData[id][famBosDeskPos][2] != 0.0)
        {
            FamData[id][famBosDeskLabel] = CreateDynamic3DTextLabel(""YELLOW"[Y]"WHITE" Families Desk", -1, FamData[id][famBosDeskPos][0], FamData[id][famBosDeskPos][1], FamData[id][famBosDeskPos][2] + 0.25, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, id, FamData[id][famInterior], -1);
        }

        if(FamData[id][famgaragePos][0] != 0.0)
        {
            FamData[id][famgarageObject] = CreateCirclePickup(0xFFFF99CC, FamData[id][famgaragePos][0], FamData[id][famgaragePos][1], FamData[id][famgaragePos][2], FamData[id][famgarageWorld], FamData[id][famgarageInt], -1); 

            FamData[id][famgarageArea] = CreateDynamicSphere(FamData[id][famgaragePos][0], FamData[id][famgaragePos][1], FamData[id][famgaragePos][2], 2.0, FamData[id][famgarageWorld], FamData[id][famgarageInt], -1, 0);
        }
    }
    return 1;
}

stock Families_GedelahFiture(playerid, targetid)
{
    new 
        amount[MAX_INVENTORY],
        str[512],
        string[256],
        count2 = 0;
    
    format(str, sizeof(str), "Nama Barang\tJumlah\n");
    forex(i, MAX_INVENTORY)
    {
        if(InventoryData[targetid][i][invExists])
        {
            strunpack(string, InventoryData[targetid][i][invItem]);
            amount[i] = InventoryData[targetid][i][invQuantity];

            if(InventoryData[targetid][i][invQuantity] > 0)
            {
                format(str, sizeof(str), "%s %s\t%d\n", str, string, amount[i]);
                ListedFamItem[playerid][count2 ++] = i;
            }
        }
    }
    if(!count2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki Barang apapun!");
    Dialog_Show(playerid, FamiliesGeledah, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Geledah", str, "Select", "Close");
    return 1;
}

VRRP::OnFamiliesCreated(id)
{
    Families_Save(id);
    Families_Refresh(id);
    return 1;
}
forward Families_Load();
public Families_Load()
{
    new rows;
    cache_get_row_count(rows);
    new Cache:famcache;
    if(rows)
    {
        new fid, name[50], leader[MAX_PLAYER_NAME], i = 0;
        famcache = cache_save();
        while(i < rows)
        {
            cache_get_value_name_int(i, "F_ID", fid);
            cache_get_value_name(i, "F_Name", name);
            format(FamData[fid][famName], 50, name);
            cache_get_value_name(i, "F_Leader", leader);
            cache_get_value_name(i, "F_Type", FamData[fid][famType]);
            format(FamData[fid][famLeader], MAX_PLAYER_NAME, leader);
            cache_get_value_name_int(i, "F_Money", FamData[fid][famMoney]);
            cache_get_value_name_int(i, "F_Icon", FamData[fid][famIcon]);
            cache_get_value_name_float(i, "F_BrankasX", FamData[fid][famBrankasPos][0]);
            cache_get_value_name_float(i, "F_BrankasY", FamData[fid][famBrankasPos][1]);
            cache_get_value_name_float(i, "F_BrankasZ", FamData[fid][famBrankasPos][2]);
            cache_get_value_name_float(i, "F_BosDeskX", FamData[fid][famBosDeskPos][0]);
            cache_get_value_name_float(i, "F_BosDeskY", FamData[fid][famBosDeskPos][1]);
            cache_get_value_name_float(i, "F_BosDeskZ", FamData[fid][famBosDeskPos][2]);
            cache_get_value_name_float(i, "F_ExtPosX", FamData[fid][famExtPos][0]);
            cache_get_value_name_float(i, "F_ExtPosY", FamData[fid][famExtPos][1]);
            cache_get_value_name_float(i, "F_ExtPosZ", FamData[fid][famExtPos][2]);
            cache_get_value_name_float(i, "F_ExtPosA", FamData[fid][famExtPos][3]);
            cache_get_value_name_float(i, "F_IntPosX", FamData[fid][famIntPos][0]);
            cache_get_value_name_float(i, "F_IntPosY", FamData[fid][famIntPos][1]);
            cache_get_value_name_float(i, "F_IntPosZ", FamData[fid][famIntPos][2]);
            cache_get_value_name_float(i, "F_IntPosA", FamData[fid][famIntPos][3]);
            cache_get_value_name_int(i, "F_Interior", FamData[fid][famInterior]);
            cache_get_value_name_int(i, "F_Weapon1", FamData[fid][famWeapon][0]);
            cache_get_value_name_int(i, "F_Weapon2", FamData[fid][famWeapon][1]);
            cache_get_value_name_int(i, "F_Weapon3", FamData[fid][famWeapon][2]);
            cache_get_value_name_int(i, "F_Weapon4", FamData[fid][famWeapon][3]);
            cache_get_value_name_int(i, "F_Weapon5", FamData[fid][famWeapon][4]);
            cache_get_value_name_int(i, "F_Ammo1", FamData[fid][famAmmo][0]);
            cache_get_value_name_int(i, "F_Ammo2", FamData[fid][famAmmo][1]);
            cache_get_value_name_int(i, "F_Ammo3", FamData[fid][famAmmo][2]);
            cache_get_value_name_int(i, "F_Ammo4", FamData[fid][famAmmo][3]);
            cache_get_value_name_int(i, "F_Ammo5", FamData[fid][famAmmo][4]);
            cache_get_value_name_int(i, "F_RedMoney", FamData[fid][famRedMoney]);

            cache_get_value_name_float(i, "F_GarageX", FamData[fid][famgaragePos][0]);
            cache_get_value_name_float(i, "F_GarageY", FamData[fid][famgaragePos][1]);
            cache_get_value_name_float(i, "F_GarageZ", FamData[fid][famgaragePos][2]);
            cache_get_value_name_float(i, "F_GarageSpawnX", FamData[fid][famgaragespawnPos][0]);
            cache_get_value_name_float(i, "F_GarageSpawnY", FamData[fid][famgaragespawnPos][1]);
            cache_get_value_name_float(i, "F_GarageSpawnZ", FamData[fid][famgaragespawnPos][2]);
            cache_get_value_name_float(i, "F_GarageSpawnA", FamData[fid][famgaragespawnPos][3]);
            cache_get_value_int(i, "F_GarageWorld", FamData[fid][famgarageWorld]);
            cache_get_value_int(i, "F_GarageInterior", FamData[fid][famgarageInt]);

            cache_get_value_name(i, "F_Type", FamData[fid][famType]);
            
            Iter_Add(Families, fid);
            Families_Refresh(fid);
            i++;
        }
        printf("[Families]: Jumlah total Families yang dimuat %d", rows);
        if(cache_is_valid(famcache))
        {
            cache_delete(famcache);
            printf("[Families]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Families]: Cache tidak valid atau sudah dihapus.");
        }
    }
}

#include <YSI\y_hooks>

CMD:f(playerid, params[])
{
    new text[128];
    
    if(AccountData[playerid][pFamily] == -1)
        return Error(playerid, "You must in family member to use this command");
            
    if(sscanf(params,"s[128]",text))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/f [text]");

    if(strval(text) > 128)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Text too long.");
    
    SendFamilyMessage(AccountData[playerid][pFamily], COLOR_FAMILY, ""FAMILY_E"* %s %s: %s *", GetFamilyRank(playerid), AccountData[playerid][pName], params);
    return 1;
}

CMD:setfamilies(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 3 && AccountData[playerid][pHandleBadside] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Management & Handle Badside!");
    
    if(!AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty untuk menggunakan perintah ini!");

    new otherid, famid, rank;
    if(sscanf(params, "udd", otherid, famid, rank))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setfamilies [playerid/Name] [Families ID] [Rank 1 - 6]");
    if(!Iter_Contains(Families, famid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Families tidak ada!");
    if(famid >= MAX_FAMILIES) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Families ID!");
    if(rank < 1 || rank > 6) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak bisa kurang dari 1 atau lebih dari 6!");
    if(otherid == INVALID_PLAYER_ID || !IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi kedalam server!");
    if(AccountData[otherid][pFaction] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah tergabung dengan faction goodside!");

    if(famid == -1)
    {
        AccountData[otherid][pFamily] = -1;
        AccountData[otherid][pFamilyRank] = rank;
    }
    else 
    {
        AccountData[otherid][pFamily] = famid;
        AccountData[otherid][pFamilyRank] = rank;
    }

    SendClientMessageEx(playerid, -1, ""VERONADOT"Anda menjadikan %s sebagai Families: %s dengan Rank: %s", ReturnName(otherid), FamData[famid][famName], GetFamilyRank(rank));
    SendClientMessageEx(otherid, -1, ""VERONADOT"Admin %s menjadikan anda bagian dari Families: %s dengan Rank: %s", GetAdminName(playerid), FamData[famid][famName], GetFamilyRank(rank));
    return 1;
}

CMD:famcreate(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 3 && AccountData[playerid][pHandleBadside] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Management & Handle Badside!");
    
    if(!AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty untuk menggunakan perintah ini!");

    new id = Iter_Free(Families);
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membuat families lagi!");

    new name[50], type[24], otherid, query[200];
    if(sscanf(params, "us[50]s[24]", otherid, name, type)) 
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/famcreate [playerid/Name] [Families Name] [Type]");
    
    if(otherid == INVALID_PLAYER_ID)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi kedalam server!");
    
    if(AccountData[otherid][pFamily] != -1)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut telah tergabung dengan keluarga!");
    
    if(AccountData[otherid][pFaction] != 0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut telah tergabung Factions!");

    if(!(
        strcmp(type, "Mafia", true) == 0 ||
        strcmp(type, "Street Gang", true) == 0 ||
        strcmp(type, "JDM", true) == 0 ||
        strcmp(type, "Cartel", true) == 0 ||
        strcmp(type, "MC", true) == 0
    )) {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tipe keluarga tidak valid! Gunakan: Mafia, Street Gang, JDM, Cartel, atau MC.");
    }

    AccountData[otherid][pFamily] = id;
    AccountData[otherid][pFamilyRank] = 6;

    format(FamData[id][famName], 50, name);
    format(FamData[id][famLeader], 50, AccountData[otherid][pName]);
    format(FamData[id][famType], 24, type);

    FamData[id][famBrankasPos][0] = 0.0;
    FamData[id][famBrankasPos][1] = 0.0;
    FamData[id][famBrankasPos][2] = 0.0;
    
    FamData[id][famBosDeskPos][0] = 0.0;
    FamData[id][famBosDeskPos][1] = 0.0;
    FamData[id][famBosDeskPos][2] = 0.0;

    FamData[id][famExtPos][0] = 0.0;
    FamData[id][famExtPos][1] = 0.0;
    FamData[id][famExtPos][2] = 0.0;
    FamData[id][famExtPos][3] = 0.0;

    FamData[id][famIntPos][0] = 0.0;
    FamData[id][famIntPos][1] = 0.0;
    FamData[id][famIntPos][2] = 0.0;
    FamData[id][famIntPos][3] = 0.0;
    
    FamData[id][famgaragePos][0] = 0.0;
    FamData[id][famgaragePos][1] = 0.0;
    FamData[id][famgaragePos][2] = 0.0;
    FamData[id][famgaragespawnPos][0] = 0.0;
    FamData[id][famgaragespawnPos][1] = 0.0;
    FamData[id][famgaragespawnPos][2] = 0.0;
    FamData[id][famgaragespawnPos][3] = 0.0;
    FamData[id][famgarageWorld] = 0;
    FamData[id][famgarageInt] = 0;
    
    FamData[id][famIcon] = 1330;
    FamData[id][famMoney] = 0;
    FamData[id][famRedMoney] = 0;

    forex(i, 5)
    {
        FamData[id][famWeapon][i] = 0;
        FamData[id][famAmmo][i] = 0;
    }

    Iter_Add(Families, id);

    SendClientMessageEx(otherid, -1, ""VERONADOT"Admin %s telah membuatkan Families: %s [%s], dan anda sebagai Leadernya", GetAdminName(playerid), name, type);
    SendStaffMessage(X11_TOMATO, "%s memuat Families ID: "YELLOW"%d %s [%s]"ARWIN1" dan "YELLOW"%s"ARWIN1" sebagai leadernya.", AccountData[playerid][pAdminname], id, name, type, AccountData[otherid][pName]);

    new icsr[200];
    mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Family`=%d, `Char_FamilyRank`=6 WHERE `pID`=%d", id, AccountData[otherid][pID]);
    mysql_tquery(g_SQL, icsr);

    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `families` SET `F_ID` = %d, `F_Name` = '%e', `F_Leader` = '%e', `F_Type` = '%e'", id, name, AccountData[otherid][pName], type);
    mysql_tquery(g_SQL, query, "OnFamiliesCreated", "d", id);
    return 1;
}

CMD:famedit(playerid, params[])
{
    static 
        fid,
        type[24],
        string[128],
        otherid;
    
    if(AccountData[playerid][pAdmin] < 3 && AccountData[playerid][pHandleBadside] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Management & Handle Badside!");

    if(!AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty untuk menggunakan perintah ini!");

    if (sscanf(params, "ds[24]S()[128]", fid, type, string))
    {
        Syntax(playerid, "/famedit [id] [entity] (location, interior, name, leader, bosdesk, brankas, money, garage, garagespawn, type, resetbrankas)");
        return 1;
    }
    if(fid < 0 || fid >= MAX_FAMILIES)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Input tidak Valid!");
    if(!Iter_Contains(Families, fid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Families ID Tidak ada!");
    
    if(!strcmp(type, "location", true))
    {
        GetPlayerPos(playerid, FamData[fid][famExtPos][0], FamData[fid][famExtPos][1], FamData[fid][famExtPos][2]);
        GetPlayerFacingAngle(playerid, FamData[fid][famExtPos][3]);

        Families_Save(fid);
        Families_Refresh(fid);

        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan Exterior Door untuk Families: %s ID: %d", GetAdminName(playerid), FamData[fid][famName], fid);
    }
    else if(!strcmp(type, "interior", true))
    {
        new intType;
        if(sscanf(string, "d", intType)) 
            return Syntax(playerid, "/famedit [fid] interior [1 Gangster || 2 Mafia || 3 MC || 4 Cartel]");

        if(intType < 1 || intType > 4)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Interior hanya tersedia 1 atau 4!");
        
        if(intType == 1) 
        {
            FamData[fid][famIntPos][0] = 2317.8333;
            FamData[fid][famIntPos][1] = -1558.8365;
            FamData[fid][famIntPos][2] = 1052.6489;
            FamData[fid][famIntPos][3] = 177.5998;
            FamData[fid][famInterior] = 2;
        }
        else if(intType == 2) 
        {
            FamData[fid][famIntPos][0] = -830.2601;
            FamData[fid][famIntPos][1] = 1115.1855;
            FamData[fid][famIntPos][2] = 1497.1621;
            FamData[fid][famIntPos][3] = 359.1467;
            FamData[fid][famInterior] = 7;
        }
        else if(intType == 3) 
        {
            FamData[fid][famIntPos][0] = 876.9809;
            FamData[fid][famIntPos][1] = -1793.8124;
            FamData[fid][famIntPos][2] = 5001.0859;
            FamData[fid][famIntPos][3] = 275.5217;
            FamData[fid][famInterior] = 5;
        }
        else if(intType == 4) 
        {
            FamData[fid][famIntPos][0] = 1569.1752;
            FamData[fid][famIntPos][1] = -4.4546;
            FamData[fid][famIntPos][2] = 1100.9153;
            FamData[fid][famIntPos][3] = 173.2110;
            FamData[fid][famInterior] = 5;
        }
        Families_Save(fid);
        Families_Refresh(fid);

        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan Interior Door untuk Families: %s ID: %d", GetAdminName(playerid), FamData[fid][famName], fid);
    }
    else if(!strcmp(type, "name", true))
    {
        new name[50];

        if(sscanf(string, "s[50]", name))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/famedit [id] [name] [fam name]");
        
        format(FamData[fid][famName], 50, name);
        Families_Save(fid);
        Families_Refresh(fid);

        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengubah nama Families ID: %d menjadi %s", GetAdminName(playerid), fid, name);
    }
    else if(!strcmp(type, "leader", true))
    {
        if(sscanf(string, "u", otherid))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/famedit [id] [leader] [playerid]");
        
        if(otherid == INVALID_PLAYER_ID || !IsPlayerConnected(otherid))
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi kedalam server!");
        
        format(FamData[fid][famLeader], MAX_PLAYER_NAME, AccountData[otherid][pName]);
        Families_Save(fid);
        Families_Refresh(fid);

        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah telah mengubah Leader Families: %s dan %s menjadi Leader barunya", GetAdminName(playerid), FamData[fid][famName], AccountData[otherid][pName]);
    }
    else if(!strcmp(type, "brankas", true))
    {
        GetPlayerPos(playerid, FamData[fid][famBrankasPos][0], FamData[fid][famBrankasPos][1], FamData[fid][famBrankasPos][2]);

        Families_Save(fid);
        Families_Refresh(fid);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan brankas Families ID: %d", GetAdminName(playerid), fid);
    }
    else if(!strcmp(type, "bosdesk", true))
    {
        GetPlayerPos(playerid, FamData[fid][famBosDeskPos][0], FamData[fid][famBosDeskPos][1], FamData[fid][famBosDeskPos][2]);

        Families_Save(fid);
        Families_Refresh(fid);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan bos desk Families ID: %d", GetAdminName(playerid), fid);
    }
    else if(!strcmp(type, "icon", true))
    {
        new icon;

        if(sscanf(string, "d", icon))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/famedit [id] [icon] [icon id]");
        
        FamData[fid][famIcon] = icon;
        Families_Save(fid);
        Families_Refresh(fid);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan icon Families ID: %s menjadi %d", GetAdminName(playerid), FamData[fid][famName], icon);
    }
    else if(!strcmp(type, "money", true))
    {
        new money;

        if(sscanf(string, "d", money))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/famedit [id] [money] [ammount]");

        FamData[fid][famMoney] = money;

        Families_Save(fid);
        Families_Refresh(fid);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menetapkan uang Families ID: %s menjadi %s", GetAdminName(playerid), FamData[fid][famName], FormatMoney(money));
    }
    else if(!strcmp(type, "garage", true))
    {
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);

        FamData[fid][famgaragePos][0] = x;
        FamData[fid][famgaragePos][1] = y;
        FamData[fid][famgaragePos][2] = z;
        FamData[fid][famgarageInt] = GetPlayerInterior(playerid);
        FamData[fid][famgarageWorld] = GetPlayerVirtualWorld(playerid);

        Families_Save(fid);
        Families_Refresh(fid);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menetapkan Garasi Family ID: %d", AccountData[playerid][pAdminname], fid);
    }
    else if(!strcmp(type, "garagespawn", true))
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        new Float:x, Float:y, Float:z, Float:a;
        if(IsPlayerInAnyVehicle(playerid))
        {
            GetVehiclePos(vehicleid, x, y, z);
            GetVehicleZAngle(vehicleid, a);

            FamData[fid][famgaragespawnPos][0] = x;
            FamData[fid][famgaragespawnPos][1] = y;
            FamData[fid][famgaragespawnPos][2] = z;
            FamData[fid][famgaragespawnPos][3] = a;

            Families_Save(fid);
            Families_Refresh(fid);
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menetapkan Garasi Spawn Family ID: %d", AccountData[playerid][pAdminname], fid);
        }
        else 
        {
            GetPlayerPos(playerid, x, y, z);
            GetPlayerFacingAngle(playerid, a);

            FamData[fid][famgaragespawnPos][0] = x;
            FamData[fid][famgaragespawnPos][1] = y;
            FamData[fid][famgaragespawnPos][2] = z;
            FamData[fid][famgaragespawnPos][3] = a;

            Families_Save(fid);
            Families_Refresh(fid);
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menetapkan Garasi Spawn Family ID: %d", AccountData[playerid][pAdminname], fid);
        }
    }
    else if(!strcmp(type, "garagedelete", true))
    {
        if(DestroyDynamicObject(FamData[fid][famgarageObject])) FamData[fid][famgarageObject] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        if(DestroyDynamicArea(FamData[fid][famgarageArea])) FamData[fid][famgarageArea] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;

        FamData[fid][famgaragePos][0] = FamData[fid][famgaragePos][1] = FamData[fid][famgaragePos][2] = 0.0;
        FamData[fid][famgaragespawnPos][0] = FamData[fid][famgaragespawnPos][1] = FamData[fid][famgaragespawnPos][2] = FamData[fid][famgaragespawnPos][3] = 0.0;
        
        Families_Save(fid);
        Families_Refresh(fid);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menghapus Garasi Family ID: %d", AccountData[playerid][pAdminname], fid);
    }
    else if(!strcmp(type, "type", true))
    {
        new famtype[32];
        if(sscanf(string, "s[32]", famtype))
            return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/famedit [id] [type] [JDM/Mafia/Cartel/MC/Street Gang]");

        if(!(strcmp(famtype, "JDM", true) == 0 || strcmp(famtype, "Mafia", true) == 0 || strcmp(famtype, "Cartel", true) == 0 ||
            strcmp(famtype, "MC", true) == 0 || strcmp(famtype, "Street Gang", true) == 0))
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Tipe families tidak valid! Gunakan: JDM, Mafia, Cartel, MC, Street Gang");
        }

        format(FamData[fid][famType], 32, famtype);
        Families_Save(fid);
        Families_Refresh(fid);

        SendStaffMessage(X11_TOMATO, "%s telah mengubah Type Families ID: %d menjadi %s", GetAdminName(playerid), fid, famtype);
    }
    else if(!strcmp(type, "resetbrankas", true))
    {
        new query[256];
        mysql_format(g_SQL, query, sizeof(query),"DELETE FROM `badside_brankas` WHERE `ID`=%d", fid);
        mysql_tquery(g_SQL, query);

        Families_Save(fid);
        Families_Refresh(fid);

        SendStaffMessage(X11_TOMATO, "%s telah mereset brankas Families ID: %d", GetAdminName(playerid), fid);
    }
    return 1;
}
CMD:gotofamdoor(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 3 && AccountData[playerid][pHandleBadside] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Management & Handle Badside!");
    
    if(!AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty untuk menggunakan perintah ini!");

    new fdid;
    if(sscanf(params, "d", fdid))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotofamdoor [id]");
    
    if(fdid == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Families ID!");
    if(!Iter_Contains(Families, fdid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Families tidak ditemukan!");
    
    if(FamData[fdid][famExtPos][0] == 0.0 && FamData[fdid][famExtPos][1] == 0.0 && FamData[fdid][famExtPos][2] == 0.0)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Families itu belum memiliki Door Ext!");
        return 1;
    }
    else 
    {
        SetPlayerPos(playerid, FamData[fdid][famExtPos][0], FamData[fdid][famExtPos][1], FamData[fdid][famExtPos][2]);
        SetPlayerFacingAngle(playerid, FamData[fdid][famExtPos][3]);

        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Teleportasi ke Door Families: %s, Families ID: %d", GetAdminName(playerid), FamData[fdid][famName], fdid);
        SetPlayerVirtualWorldEx(playerid, 0);
        SetPlayerInteriorEx(playerid, 0);
        
        AccountData[playerid][pInFamily] = -1;
        AccountData[playerid][pInRusun] = -1;
        AccountData[playerid][pInHouse] = -1;
        AccountData[playerid][pInDoor] = -1;
        AccountData[playerid][pInBiz] = -1;
    }
    return 1;
}

CMD:famdelete(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 3 && AccountData[playerid][pHandleBadside] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ini Khusus Management & Handle Badside!");
    if(!AccountData[playerid][pAdminDuty]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus On Duty untuk menggunakan perintah ini!");

    new fid, query[128];
    if(sscanf(params, "i", fid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/famdelete [families id]");
    if(!Iter_Contains(Families, fid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Families ID!");

    format(FamData[fid][famName], 50, "N/A");
    format(FamData[fid][famLeader], 50, "N/A");

    DestroyDynamicArea(FamData[fid][famDoorArea]);
    DestroyDynamic3DTextLabel(FamData[fid][famBrankasLabel]);
    DestroyDynamic3DTextLabel(FamData[fid][famBosDeskLabel]);
    DestroyDynamicPickup(FamData[fid][famPickExt]);
    DestroyDynamicPickup(FamData[fid][famPickInt]);
    DestroyDynamic3DTextLabel(FamData[fid][famLabelExt]);
    DestroyDynamic3DTextLabel(FamData[fid][famLabelInt]);
    DestroyDynamicObject(FamData[fid][famgarageObject]);
    DestroyDynamicArea(FamData[fid][famgarageArea]);

    FamData[fid][famgaragePos][0] = 0.0;
    FamData[fid][famgaragePos][1] = 0.0;
    FamData[fid][famgaragePos][2] = 0.0;
    FamData[fid][famgaragespawnPos][0] = 0.0;
    FamData[fid][famgaragespawnPos][1] = 0.0;
    FamData[fid][famgaragespawnPos][2] = 0.0;
    FamData[fid][famgaragespawnPos][3] = 0.0;

    FamData[fid][famBrankasPos][0] = 0.0;
    FamData[fid][famBrankasPos][1] = 0.0;
    FamData[fid][famBrankasPos][2] = 0.0;
    
    FamData[fid][famBosDeskPos][0] = 0.0;
    FamData[fid][famBosDeskPos][1] = 0.0;
    FamData[fid][famBosDeskPos][2] = 0.0;
    
    FamData[fid][famExtPos][0] = 0.0;
    FamData[fid][famExtPos][1] = 0.0;
    FamData[fid][famExtPos][2] = 0.0;
    FamData[fid][famExtPos][3] = 0.0;
    
    FamData[fid][famIntPos][0] = 0.0;
    FamData[fid][famIntPos][1] = 0.0;
    FamData[fid][famIntPos][2] = 0.0;
    FamData[fid][famIntPos][3] = 0.0;
    FamData[fid][famInterior] = 0;
    FamData[fid][famMoney] = 0;

    Iter_Remove(Families, fid);

    foreach(new i : Player) if (IsPlayerConnected(i) && AccountData[i][pSpawned])
    {
        if(AccountData[i][pFamily] == fid)
        {
            AccountData[i][pFamily] = -1;
            AccountData[i][pFamilyRank] = 0;
        }
    }

    mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_Family`=-1, `Char_FamilyRank`=0 WHERE `Char_Family`=%d", fid);
    mysql_tquery(g_SQL, query);

    mysql_format(g_SQL, query, sizeof(query),"DELETE FROM `badside_brankas` WHERE `ID`=%d", fid);
    mysql_tquery(g_SQL, query);

    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM families WHERE F_ID ='%d'", fid);
    mysql_tquery(g_SQL, query);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menghapus Families: "YELLOW"%s"GRAY" Families ID: "YELLOW"%d.", GetAdminName(playerid), FamData[fid][famName], fid);
    return 1;
}

GetFamiliesOnlineCount(famid)
{
    new onlinecount = 0;

    foreach(new i : Player)
    {
        if(IsPlayerConnected(i) && AccountData[i][pFamily] == famid)
        {
            onlinecount ++;
        }
    }

    return onlinecount;
}

alias:families("famlist")
CMD:families(playerid, params[])
{
    new id, famname[126], famleader[MAX_PLAYER_NAME], famtype[64], famonline, Cache:execute;
    execute = mysql_query(g_SQL, "SELECT `F_ID`, `F_Name`, `F_Leader`, `F_Type` FROM `families` ORDER BY `F_ID` ASC", true);

    if (cache_num_rows())
    {
        new list[4096]; // Pastikan cukup besar
        format(list, sizeof(list), "FID\tName (Type)\tOnline\tLeader\n");

        for (new i = 0; i < cache_num_rows(); i++)
        {
            cache_get_value_name_int(i, "F_ID", id);
            cache_get_value_name(i, "F_Name", famname);
            cache_get_value_name(i, "F_Leader", famleader);
            cache_get_value_name(i, "F_Type", famtype);

            famonline = GetFamiliesOnlineCount(id);

            // Ganti warna berdasarkan jenis fam
            new type_colored[96];
            if (strcmp(famtype, "Mafia", true) == 0)
                format(type_colored, sizeof(type_colored), ""YELLOW"(%s)"WHITE"", famtype);
            else if (strcmp(famtype, "Street Gang", true) == 0)
                format(type_colored, sizeof(type_colored), ""YELLOW"(%s)"WHITE"", famtype);
            else if (strcmp(famtype, "JDM", true) == 0)
                format(type_colored, sizeof(type_colored), ""YELLOW"(%s)"WHITE"", famtype);
            else if (strcmp(famtype, "MC", true) == 0)
                format(type_colored, sizeof(type_colored), ""YELLOW"(%s)"WHITE"", famtype); // abu2
            else if (strcmp(famtype, "Cartel", true) == 0)
                format(type_colored, sizeof(type_colored), ""YELLOW"(%s)"WHITE"", famtype); // abu2
            else
                format(type_colored, sizeof(type_colored), "(unknown)");

            // Format akhir
            format(list, sizeof(list), "%s%d\t%s %s\t%d\t%s\n", list, id, famname, type_colored, famonline, famleader);
        }

        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District "WHITE" - Fam List", list, "Tutup", "");
    }
    else
    {
        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Official Family", "Tidak ada Families Official Kota untuk saat ini.", "Tutup", "");
    }

    cache_delete(execute);
    return 1;
}

hook OnScriptInit()
{
    Families_Stuffs[JualMarijuana] = CreateDynamicSphere(-1435.9803,-964.6420,201.0257, 2.0, 0, 0, -1, 0);
    Families_Stuffs[WashRedMoney] = CreateDynamicSphere(-1499.9821, 1960.0963, 49.0234, 3.0, 0, 0, -1, 0);
    Families_Stuffs[BlackmarketArea] = CreateDynamicSphere(263.6431, 2895.4861, 10.5314, 2.0, 0, 0, -1, 0);
    Families_Stuffs[BlackmarketLabel] = CreateDynamic3DTextLabel(""RED"[Y]"WHITE" Blackmarket", -1, 263.6431, 2895.4861, 10.5314, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 15.0, -1, 0);
    Families_Stuffs[WashObjects] = CreateDynamicObject(1317, -1499.9821, 1960.0963, 49.0234 - 1.2, 0.000000, 0.000000, 0.000000, 0, 0, -1, 300.00, 300.00); 
    SetDynamicObjectMaterial(Families_Stuffs[WashObjects], 0, 10765, "airportgnd_sfse", "white", 0xE16AF6E6);
}

hook OnPlayerConnect(playerid)
{
    pTimerJualMarijuana[playerid] = -1;
    pTimerWashRedMoney[playerid] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pTimerWashRedMoney[playerid]);
    KillTimer(pTimerJualMarijuana[playerid]);
    pTimerJualMarijuana[playerid] = -1;
    pTimerWashRedMoney[playerid] = -1;
    return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == Families_Stuffs[JualMarijuana])
    {
        ShowKey(playerid, "[Y] Jual Marijuana");
    }

    if(areaid == Families_Stuffs[WashRedMoney])
    {
        ShowKey(playerid, "[Y] Cuci Uang");
    }
    
    foreach(new i : Families) if (areaid == FamData[i][famgarageArea])
    {
        if(IsPlayerInAnyVehicle(playerid))
        {
            ShowKey(playerid, "[H] Garasi Families");
        }
        else
        {
            ShowKey(playerid, "[Y] Garasi Families");
        }
    }
    return 1;
}

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
    if(areaid == Families_Stuffs[JualMarijuana])
    {
        HideShortKey(playerid);
    }
    
    if(areaid == Families_Stuffs[WashRedMoney])
    {
        HideShortKey(playerid);
    }

    foreach(new i : Families) if (areaid == FamData[i][famgarageArea])
    {
        HideShortKey(playerid);
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_CROUCH && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        new gid = IsPlayerNearGarageFamily(playerid);
        if(gid > -1)
        {
            if(AccountData[playerid][pFamily] != gid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Families Ini!");
            new carid = -1, bool: found = false;
            if((carid = Vehicle_Nearest2(playerid)) != -1)
            {
                if(PlayerVehicle[carid][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
                if(PlayerVehicle[carid][pVehRental] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat memasukkan kendaraan rental!");

                HideShortKey(playerid);
                Vehicle_GetStatus(carid);
                PlayerVehicle[carid][pVehFamiliesGarage] = gid;
                found = true;

                RemovePlayerFromVehicle(playerid);
                SetTimerEx("InputVehicleToGarage", 2000, false, "d", carid);
            }
            if(!found) return false;
        }
    }
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new gid = IsPlayerNearGarageFamily(playerid);
        if(gid > -1)
        {
            if(AccountData[playerid][pFamily] != gid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Families Ini!");
            if(CountPlayerVehicleFamilies(playerid, gid) < 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak menyimpan kendaraan apapun di garasi ini!");
            
            new vehid, count = CountPlayerVehicleFamilies(playerid, gid), list[598];
            format(list, sizeof(list), "No\tModel Kendaraan\tNomor Plat\n");
            for(new itt; itt < count; itt ++)
            {
                vehid = ReturnAnyVehicleFamilies(playerid, itt, gid);
                if(itt == count)
                {
                    format(list, sizeof(list), "%s%d\t%s\t%s", list, itt+1, GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]);
                } else format(list, sizeof(list), "%s%d\t%s\t%s\n", list, itt+1, GetVehicleModelName(PlayerVehicle[vehid][pVehModelID]), PlayerVehicle[vehid][pVehPlate]);
            }
            AccountData[playerid][pPark] = gid;
            ShowPlayerDialog(playerid, DIALOG_FAMGARAGE_OUT, DIALOG_STYLE_TABLIST_HEADERS, sprintf(""TCRP"District "WHITE" - Garasi %s", FamData[gid][famName]), list, "Pilih", "Batal");
            HideShortKey(playerid);
        }

        if(IsPlayerInDynamicArea(playerid, Families_Stuffs[WashRedMoney]))
        {
            if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak tergabung dengan families manapun!");
            
            new countpd, countems;
            foreach(new i : Player) if (AccountData[i][IsLoggedIn])
            {
                if(AccountData[i][pDutyPD]) countpd ++;
                if(AccountData[i][pDutyEms]) countems ++;
            }
            if(countpd <= 4 && countems <= 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 4 Polisi Duty dan 2 EMS Duty!");

            if(AccountData[playerid][pRedMoney] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki uang merah!");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");

            AccountData[playerid][ActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "WASHING");
            ShowProgressBar(playerid);

            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            pTimerWashRedMoney[playerid] = SetTimerEx("WashingRedMoney", 1000, true, "d", playerid);
        }

        if(IsPlayerInDynamicArea(playerid, Families_Stuffs[BlackmarketArea]))
        {
            if(AccountData[playerid][pLevel] < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Level anda masih terlalu rendah untuk dapat mengakses BlackMarket! (Min: 15)");
            ShowPlayerDialog(playerid, DIALOG_BLACKMARKET, DIALOG_STYLE_TABLIST, ""TCRP"District  "WHITE"- BlackMarket Store",
            "Desert Eagle\t"RED"$80,000\
            \n"GRAY"Shotgun\t"RED"$100,000\
            \nTec 9\t"RED"$145,000\
            \n"GRAY"Mp 5\t"RED"$180,000\
            \nAK 47\t"RED"$250,000", "Pilih", "Batal");
        }

        if(IsPlayerInDynamicArea(playerid, Families_Stuffs[JualMarijuana]))
        {
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
            if(!PlayerHasItem(playerid, "Marijuana")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Marijuana!");

            AccountData[playerid][ActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENJUAL MARIJUANA");
            ShowProgressBar(playerid);

            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            pTimerJualMarijuana[playerid] = SetTimerEx("SellMarjun", 1000, true, "d", playerid);
        }

        new bosid = AccountData[playerid][pFamily];
        if(bosid > -1)
        {
            if(IsPlayerInRangeOfPoint(playerid, 2.0, FamData[bosid][famBosDeskPos][0], FamData[bosid][famBosDeskPos][1], FamData[bosid][famBosDeskPos][2]))
            {
                if(AccountData[playerid][pFamily] == bosid)
                {
                    if(AccountData[playerid][pFamilyRank] >= 4)
                    {
                        Dialog_Show(playerid, Bosdesk_Family, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Bos Desk", ""WHITE"Invite\n"VERONA_ARWIN"Kelola Jabatan\n"WHITE"Kick\n"WHITE"Cek Keuangan\n"VERONA_ARWIN"Taruh/Ambil Uang", "Pilih", "Batal");
                    }
                    else ShowTDN(playerid, NOTIFICATION_ERROR, "Peringkat anda terlalu rendah!");
                }
                else ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya keluarga terkait yang dapat membuka Brankas!");
            }
        }

        new fid = AccountData[playerid][pFamily];
        if(fid > -1)
        {
            if(IsPlayerInRangeOfPoint(playerid, 2.0, FamData[fid][famBrankasPos][0], FamData[fid][famBrankasPos][1], FamData[fid][famBrankasPos][2]))
            {
                if(AccountData[playerid][pFamily] == fid)
                {
                    if(AccountData[playerid][pFamilyRank] < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Insider untuk akses brankas!");
                    
                    ShowPlayerDialog(playerid, DIALOG_FAMSBRANKAS, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Brankas Families",
                    "Penyimpanan Uang Merah\
                    \n"GRAY"Penyimpanan Senjata\
                    \nPenyimpanan Barang", "Pilih", "Batal");
                    SetPVarInt(playerid, "FamiliesID", fid);
                } else ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Families ini!");
            }
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_FAMGARAGE_OUT:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
            if(listitem == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");
        
            new id = ReturnAnyVehicleFamilies(playerid, listitem, AccountData[playerid][pPark]);
            if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih kendaraan untuk dikeluarkan!");

            if(!IsPlayerInRangeOfPoint(playerid, 2.0, FamData[AccountData[playerid][pPark]][famgaragePos][0], FamData[AccountData[playerid][pPark]][famgaragePos][1], FamData[AccountData[playerid][pPark]][famgaragePos][2])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak didekat Garasi Families!");
            if(PlayerVehicle[id][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
            PlayerVehicle[id][pVehParked] = -1;
			PlayerVehicle[id][pVehHouseGarage] = -1;
            PlayerVehicle[id][pVehHelipadGarage] = -1;
			PlayerVehicle[id][pVehFamiliesGarage] = -1;
			PlayerVehicle[id][pVehFactStored] = -1;

            if(PlayerVehicle[id][pVehLocked])
				PlayerVehicle[id][pVehLocked] = false;

			PlayerVehicle[id][pVehPos][0] = FamData[AccountData[playerid][pPark]][famgaragespawnPos][0];
			PlayerVehicle[id][pVehPos][1] = FamData[AccountData[playerid][pPark]][famgaragespawnPos][1];
			PlayerVehicle[id][pVehPos][2] = FamData[AccountData[playerid][pPark]][famgaragespawnPos][2];
			PlayerVehicle[id][pVehPos][3] = FamData[AccountData[playerid][pPark]][famgaragespawnPos][3];
            
            PlayerVehicle[id][pVehWorld] = FamData[AccountData[playerid][pPark]][famgarageWorld];
            PlayerVehicle[id][pVehInterior] = FamData[AccountData[playerid][pPark]][famgarageInt];

			OnPlayerVehicleRespawn(id);

            AccountData[playerid][pPark] = -1;
			SetTimerEx("ForcedPlayerHopInVehicle", 1500, false, "idd", playerid, PlayerVehicle[id][pVehPhysic], 0);
        }
        case DIALOG_FAMSBRANKAS:
        {
            new famid = AccountData[playerid][pFamily];
            if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak bergabung dengan families manapun!");
            if(AccountData[playerid][pFamily] != famid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari families ini!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0: // Uang Merah
                {       
                    ShowPlayerDialog(playerid, DIALOG_FAMSRM_VAULT, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Red Money Storage",
                    "Cek Uang Merah\
                    \n"GRAY"Deposit\
                    \nWithdraw", "Pilih", "Batal");
                }
                case 1: //Senjata
                {
                    ShowFamiliesWeapon(playerid, famid);
                }
                case 2: //ambil
                {
                    if(NearPlayerOpenStorage(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain disekitar sedang membuka brankas!");
                    
                    AccountData[playerid][menuShowed] = true;
                    ShowPlayerDialog(playerid, DIALOG_FAMSVAULT, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Brankas Families",
                    "Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Batal");
                }
            }
        }
        case DIALOG_FAMSRM_VAULT:
        {
            new famid = AccountData[playerid][pFamily];
            if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak bergabung dengan families manapun!");
            if(AccountData[playerid][pFamily] != famid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari families ini!");
            if(!response) return 1;
            switch(listitem)
            {
                case 0: // cek
                {
                    static frmtmoney[255];
                    format(frmtmoney, sizeof(frmtmoney), "Saat ini Families %s memiliki uang merah sebanyak\
                    \n"RED"%s.", FamData[famid][famName], FormatMoney(FamData[famid][famRedMoney]));
                    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Red Money", frmtmoney, "Tutup", "");
                }
                case 1: //
                {
                    ShowPlayerDialog(playerid, DIALOG_FAMSRM_DEPOSIT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Deposit",
                    "Mohon masukkan jumlah uang merah yang ingin anda simpan dibrankas families:", "Input", "Batal");
                }
                case 2: //
                {
                    ShowPlayerDialog(playerid, DIALOG_FAMSRM_WITHDRAW, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Deposit",
                    "Mohon masukkan jumlah uang merah yang ingin anda ambil dari brankas families:", "Input", "Batal");
                }
            }
        }
        case DIALOG_FAMSRM_WITHDRAW:
        {
            new famid = AccountData[playerid][pFamily];
            if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak bergabung dengan families manapun!");
            if(AccountData[playerid][pFamily] != famid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari families ini!");
            if(!response) return 1;

            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_FAMSRM_WITHDRAW, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Deposit",
                "Error: Tidak dapat diisi kosong!\nMohon masukkan jumlah uang merah yang ingin anda ambil dari brankas families:", "Input", "Batal");
                return 1;
            }
            
            if(!IsNumeric(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_FAMSRM_WITHDRAW, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Deposit",
                "Error: Hanya dapat di isi angka!\nMohon masukkan jumlah uang merah yang ingin anda ambil dari brankas families:", "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > FamData[famid][famRedMoney])
            {
                ShowPlayerDialog(playerid, DIALOG_FAMSRM_WITHDRAW, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Deposit",
                "Error: Jumlah tidak valid atau uang merah brankas tidak sebanyak itu!\nMohon masukkan jumlah uang merah yang ingin anda ambil dari brankas families:", "Input", "Batal");
                return 1;
            }

            new quants = strval(inputtext);

            AccountData[playerid][pRedMoney] += quants;
            FamData[famid][famRedMoney] -= quants;
            Families_Save(famid);
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda mengambil uang merah sejumlah %s", FormatMoney(quants)));
        }
        case DIALOG_FAMSRM_DEPOSIT:
        {
            new famid = AccountData[playerid][pFamily];
            if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak bergabung dengan families manapun!");
            if(AccountData[playerid][pFamily] != famid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari families ini!");
            if(!response) return 1;

            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_FAMSRM_DEPOSIT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Deposit",
                "Error: Tidak dapat diisi kosong!\nMohon masukkan jumlah uang merah yang ingin anda simpan dibrankas families:", "Input", "Batal");
                return 1;
            }
            
            if(!IsNumeric(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_FAMSRM_DEPOSIT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Deposit",
                "Error: Hanya dapat di isi angka!\nMohon masukkan jumlah uang merah yang ingin anda simpan dibrankas families:", "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pRedMoney])
            {
                ShowPlayerDialog(playerid, DIALOG_FAMSRM_DEPOSIT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Deposit",
                "Error: Jumlah tidak valid atau uang merah anda tidak sebanyak itu!\nMohon masukkan jumlah uang merah yang ingin anda simpan dibrankas families:", "Input", "Batal");
                return 1;
            }

            new quants = strval(inputtext);

            AccountData[playerid][pRedMoney] -= quants;
            FamData[famid][famRedMoney] += quants;
            Families_Save(famid);
            ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda memasukkan uang merah sejumlah %s", FormatMoney(quants)));
        }
        case DIALOG_FAMS_WEAPON:
        {
            new famid = AccountData[playerid][pFamily];
            if(!response) return 1;

            if(FamData[famid][famWeapon][listitem] != 0)
            {
                GivePlayerWeaponEx(playerid, FamData[famid][famWeapon][listitem], FamData[famid][famAmmo][listitem]);
                ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda mengambil %s dari chest!", ReturnWeaponName(FamData[famid][famWeapon][listitem])));
                FamData[famid][famWeapon][listitem] = 0;
                FamData[famid][famAmmo][listitem] = 0;

                Families_Save(famid);
                ShowFamiliesWeapon(playerid, famid);
            }
            else 
            {
                new 
                    weaponid = GetPlayerWeapon(playerid),
                    ammo = GetPlayerAmmo(playerid);
                
                if(!weaponid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memegang senjata apapun/slot chest tersebut kosong!");

                ResetWeapon(playerid, weaponid);
                ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda menyimpan %s ke dalam chest!", ReturnWeaponName(weaponid)));

                FamData[famid][famWeapon][listitem] = weaponid;
                FamData[famid][famAmmo][listitem] = ammo;

                Families_Save(famid);
                ShowFamiliesWeapon(playerid, famid);
            }
        }
        case DIALOG_BLACKMARKET:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(!IsPlayerInDynamicArea(playerid, Families_Stuffs[BlackmarketArea])) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada di area BlackMarket!");
            if(AccountData[playerid][pLevel] < 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Level anda masih terlalu rendah untuk dapat mengakses BlackMarket! (Min: 15)");
            switch(listitem)
            {
                case 0: // DE
                {
                    if(AccountData[playerid][pRedMoney] < 80000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang merah tidak mencukupi!");
                    AccountData[playerid][pRedMoney] -= 80000;
                    GivePlayerWeaponEx(playerid, 24, 250);
                    ShowItemBox(playerid, "Removed $80,000", "Uang Merah", 1212);
                    ShowItemBox(playerid, "Received 1x", "Desert Eagle", 348);
                }
                case 1: // Shotgun
                {
                    if(AccountData[playerid][pRedMoney] < 100000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang merah tidak mencukupi!");
                    AccountData[playerid][pRedMoney] -= 100000;
                    GivePlayerWeaponEx(playerid, 25, 100);
                    ShowItemBox(playerid, "Removed $100,000", "Uang Merah", 1212);
                    ShowItemBox(playerid, "Received 1x", "Shotgun", 349);
                }
                case 2: //TEC 9
                {
                    if(AccountData[playerid][pRedMoney] < 145000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang merah tidak mencukupi!");
                    AccountData[playerid][pRedMoney] -= 145000;
                    GivePlayerWeaponEx(playerid, 32, 300);
                    ShowItemBox(playerid, "Removed $145,000", "Uang Merah", 1212);
                    ShowItemBox(playerid, "Received 1x", "TEC 9", 372);
                }
                case 3: //MP 5
                {
                    if(AccountData[playerid][pRedMoney] < 180000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang merah tidak mencukupi!");
                    AccountData[playerid][pRedMoney] -= 180000;
                    GivePlayerWeaponEx(playerid, 29, 250);
                    ShowItemBox(playerid, "Removed $180,000", "Uang Merah", 1212);
                    ShowItemBox(playerid, "Received 1x", "MP 5", 353);
                }
                case 4: //AK 47
                {
                    if(AccountData[playerid][pRedMoney] < 250000) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang merah tidak mencukupi!");
                    AccountData[playerid][pRedMoney] -= 250000;
                    GivePlayerWeaponEx(playerid, 30, 250);
                    ShowItemBox(playerid, "Removed $250,000", "Uang Merah", 1212);
                    ShowItemBox(playerid, "Received 1x", "AK 47", 355);
                }
            }
        }
        case DIALOG_FAMSTAKE_MONEY:
        {
            if(!response)
            {
                SetPVarInt(playerid, "TargetFamsID", INVALID_PLAYER_ID);
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
                return 1;
            }
            new targetid = GetPVarInt(playerid, "TargetFamsID");

            if(!IsPlayerConnected(targetid))
            {
                SetPVarInt(playerid, "TargetFamsID", INVALID_PLAYER_ID);
                ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
                return 1;
            }

            if(!IsPlayerNearPlayer(playerid, targetid, 3.0))
            {
                SetPVarInt(playerid, "TargetFamsID", INVALID_PLAYER_ID);
                ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");
                return 1;
            }

            if(isnull(inputtext)) 
            {
                new frmxt[225];
                format(frmxt, sizeof(frmxt), ""WHITE"Error: Tidak dapat diisi kosong!\nJumlah uang yang dimiliki: "DARKGREEN"%s"WHITE"\nMohon masukkan jumlah yang ingin anda ambil paksa:", FormatMoney(AccountData[targetid][pMoney]));
                return ShowPlayerDialog(playerid, DIALOG_FAMSTAKE_MONEY, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Ambil Uang", frmxt, "Input", "Batal");
            }

            if(!IsNumeric(inputtext))
            {
                new frmxt[225];
                format(frmxt, sizeof(frmxt), ""WHITE"Error: Hanya dapat diisi angka!\nJumlah uang yang dimiliki: "DARKGREEN"%s"WHITE"\nMohon masukkan jumlah yang ingin anda ambil paksa:", FormatMoney(AccountData[targetid][pMoney]));
                return ShowPlayerDialog(playerid, DIALOG_FAMSTAKE_MONEY, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Ambil Uang", frmxt, "Input", "Batal");
            }

            if(strval(inputtext) < 1 || strval(inputtext) >= AccountData[targetid][pMoney])
            {
                new frmxt[225];
                format(frmxt, sizeof(frmxt), ""WHITE"Error: Jumlah tidak valid/melebihi yang dimiliki pemain tersebut!\nJumlah uang yang dimiliki: "DARKGREEN"%s"WHITE"\nMohon masukkan jumlah yang ingin anda ambil paksa:", FormatMoney(AccountData[targetid][pMoney]));
                return ShowPlayerDialog(playerid, DIALOG_FAMSTAKE_MONEY, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Ambil Uang", frmxt, "Input", "Batal");
            }
            new value = strval(inputtext);

            AccountData[playerid][pMoney] += value;
            AccountData[targetid][pMoney] -= value;
            SendRPMeAboveHead(playerid, "Mengambil uang secara paksa.", X11_PLUM1);
            Warning(targetid, "(Player ID: %d) telah mengambil uang anda sebanyak "RED"%s", FormatMoney(value));

            new frmxt[268];
            format(frmxt, sizeof(frmxt), "Mengambil Uang Cash milik %s sejumlah %s", AccountData[targetid][pName], FormatMoney(value));
            AddFamiliesLog(AccountData[playerid][pName], AccountData[playerid][pUCP], frmxt, GetFamiliesName(playerid));
        }
        case DIALOG_FAMSTAKE_MONEY2:
        {
            if(!response) return 1;

            new targetid = GetPVarInt(playerid, "TargetFamsID");

            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tidak valid.");

            new amount = strval(inputtext);
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid.");
            if(AccountData[targetid][pMoney] < amount) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang target tidak mencukupi.");

            SetPVarInt(targetid, "ConfirmRobberID", playerid);
            SetPVarInt(targetid, "ConfirmRobAmount", amount);

            new msg[256];
            format(msg, sizeof(msg), ""WHITE"Pemain "GREEN"%s "WHITE"ingin mengambil uangmu secara paksa sebesar "RED"%s"WHITE".\nApakah kamu setuju?", ReturnPlayerName(playerid), FormatMoney(amount));
            ShowPlayerDialog(targetid, DIALOG_CONFIRM_MONEY, DIALOG_STYLE_MSGBOX, ""YELLOW"Persetujuan Pengambilan Uang", msg, "Setuju", "Tolak");

            ShowTDN(playerid, NOTIFICATION_INFO, "Meminta persetujuan dari target...");
            return 1;
        }
        case DIALOG_CONFIRM_MONEY:
        {
            new fromid = GetPVarInt(playerid, "ConfirmRobberID");
            new amount = GetPVarInt(playerid, "ConfirmRobAmount");

            if(!IsPlayerConnected(fromid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pelaku tidak valid.");

            if(!response)
            {
                SendRPMeAboveHead(playerid, "Menolak memberikan uang", X11_PLUM1);
                return 1;
            }

            if(AccountData[playerid][pMoney] < amount)
            {
                ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak lagi memiliki uang sebanyak itu.");
                ShowTDN(fromid, NOTIFICATION_ERROR, "Transaksi gagal. Uang target tidak cukup.");
                return 1;
            }

            // Lanjut ambil uang
            AccountData[playerid][pMoney] -= amount;
            AccountData[fromid][pMoney] += amount;

            ShowTDN(playerid, NOTIFICATION_INFO, sprintf("Kamu memberikan uang sebesar %s kepada %s.", FormatMoney(amount), GetRPName(fromid)));
            ShowTDN(fromid, NOTIFICATION_SUKSES, sprintf("Kamu berhasil mengambil uang sebesar %s dari %s.", FormatMoney(amount), GetRPName(playerid)));

            // Cleanup
            DeletePVar(playerid, "ConfirmRobberID");
            DeletePVar(playerid, "ConfirmRobAmount");
            return 1;
        }
        case DIALOG_FAMSTAKE_REDMONEY:
        {
            if(!response)
            {
                SetPVarInt(playerid, "TargetFamsID", INVALID_PLAYER_ID);
                ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
                return 1;
            }
            new targetid = GetPVarInt(playerid, "TargetFamsID");

            if(!IsPlayerConnected(targetid))
            {
                SetPVarInt(playerid, "TargetFamsID", INVALID_PLAYER_ID);
                ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
                return 1;
            }

            if(!IsPlayerNearPlayer(playerid, targetid, 3.0))
            {
                SetPVarInt(playerid, "TargetFamsID", INVALID_PLAYER_ID);
                ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");
                return 1;
            }

            if(isnull(inputtext)) 
            {
                new frmxt[225];
                format(frmxt, sizeof(frmxt), ""WHITE"Error: Tidak dapat diisi kosong!\nJumlah uang merah yang dimiliki: "RED"%s"WHITE"\nMohon masukkan jumlah yang ingin anda ambil paksa:", FormatMoney(AccountData[targetid][pRedMoney]));
                return ShowPlayerDialog(playerid, DIALOG_FAMSTAKE_REDMONEY, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Ambil Uang Merah", frmxt, "Input", "Batal");
            }

            if(!IsNumeric(inputtext))
            {
                new frmxt[225];
                format(frmxt, sizeof(frmxt), ""WHITE"Error: Hanya dapat diisi angka!\nJumlah uang merah yang dimiliki: "RED"%s"WHITE"\nMohon masukkan jumlah yang ingin anda ambil paksa:", FormatMoney(AccountData[targetid][pRedMoney]));
                return ShowPlayerDialog(playerid, DIALOG_FAMSTAKE_REDMONEY, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Ambil Uang Merah", frmxt, "Input", "Batal");
            }

            if(strval(inputtext) < 1 || strval(inputtext) >= AccountData[targetid][pRedMoney])
            {
                new frmxt[225];
                format(frmxt, sizeof(frmxt), ""WHITE"Error: Jumlah tidak valid/melebihi yang dimiliki pemain tersebut!\nJumlah uang merah yang dimiliki: "RED"%s"WHITE"\nMohon masukkan jumlah yang ingin anda ambil paksa:", FormatMoney(AccountData[targetid][pRedMoney]));
                return ShowPlayerDialog(playerid, DIALOG_FAMSTAKE_REDMONEY, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Ambil Uang Merah", frmxt, "Input", "Batal");
            }
            new value = strval(inputtext);

            AccountData[playerid][pRedMoney] += value;
            AccountData[targetid][pRedMoney] -= value;
            SendRPMeAboveHead(playerid, "Mengambil uang kotor secara paksa.", X11_PLUM1);
            Warning(targetid, "(Player ID: %d) telah mengambil uang kotor anda sebanyak "RED"%s", FormatMoney(value));

            new frmxt[268];
            format(frmxt, sizeof(frmxt), "Mengambil Uang Merah milik %s sejumlah %s", AccountData[targetid][pName], FormatMoney(value));
            AddFamiliesLog(AccountData[playerid][pName], AccountData[playerid][pUCP], frmxt, GetFamiliesName(playerid));
        }
        case DIALOG_FAMSVAULT:
        {
            if(!response) 
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            }

            if(AccountData[playerid][pFamily] == -1) 
            {
                AccountData[playerid][menuShowed] = false;    
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Families!");
            }

            switch(listitem)
            {
                case 0: //deposit
                {
                    if(AccountData[playerid][pFamilyRank] < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Outsider untuk Memasukkan Barang!");

                    FactionBrankas[playerid][factionBrankasID] = 0;
                    FactionBrankas[playerid][factionBrankasTemp] = EOS;
                    FactionBrankas[playerid][factionBrankasModel] = 0;
                    FactionBrankas[playerid][factionBrankasQuant] = 0;

                    new str[1218], amounts, itemname[64], tss[128];
                    format(str, sizeof(str), "Nama Item\tJumlah\tBerat (0.000/-)\n");
                    mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
                    mysql_query(g_SQL, tss);
                    new rows = cache_num_rows();
                    if(rows)
                    {
                        for(new x; x < rows; ++x)
                        {
                            cache_get_value_name(x, "invItem", itemname);
                            cache_get_value_name_int(x, "invQuantity", amounts);

                            format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                        }
                        ShowPlayerDialog(playerid, DIALOG_FAMSVAULT_DEPOSIT, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Brankas %s", FamData[AccountData[playerid][pFamily]][famName]), str, "Pilih", "Batal");
                    }
                    else
                    {
                        AccountData[playerid][menuShowed] = false;
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, sprintf("Brankas %s", FamData[AccountData[playerid][pFamily]][famName]), 
                        "Anda tidak memiliki barang untuk disimpan!", "Tutup", "");
                    }
                }
                case 1: //withdraw
                {
                    if(AccountData[playerid][pFamilyRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Tangan Kanan untuk Mengambil Barang!");

                    new list[4036], amounts, itemname[64], icsr[125];
                    format(list, sizeof(list), "Nama Item\tJumlah\tBerat (0.000/-)\n");
                    mysql_format(g_SQL, icsr, sizeof(icsr), "SELECT * FROM `badside_brankas` WHERE `ID`=%d", AccountData[playerid][pFamily]);
                    mysql_query(g_SQL, icsr);
                    if(cache_num_rows() > 0)
                    {
                        for(new x; x < cache_num_rows(); ++x)
                        {
                            cache_get_value_name(x, "fItemName", itemname);
                            cache_get_value_name_int(x, "fItemQuantity", amounts);
                            
                            format(list, sizeof(list), "%s%s\t%d\t-\n", list, itemname, amounts);
                        }
                        ShowPlayerDialog(playerid, DIALOG_FAMSVAULT_WITHDRAW, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Brankas %s", FamData[AccountData[playerid][pFamily]][famName]), list, "Pilih", "Batal");
                    }
                    else
                    {
                        AccountData[playerid][menuShowed] = false;
                        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, sprintf("Brankas %s", FamData[AccountData[playerid][pFamily]][famName]),
                        "Tidak ada barang dibrankas saat ini!", "Tutup", "");
                    }
                }
            }
        }
        case DIALOG_FAMSVAULT_DEPOSIT:
        {
            if(AccountData[playerid][pFamily] == -1)
            {
                AccountData[playerid][menuShowed] = false;
                BrankasLastUse[playerid] = 0;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Families!");
            }
            new famid = AccountData[playerid][pFamily];
            
            if(!response)
            {
                AccountData[playerid][menuShowed] = false;
                BrankasLastUse[playerid] = 0;
                return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            }

            new tss[188];
            mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
            mysql_query(g_SQL, tss);
            if(cache_num_rows() > 0)
            {
                if(listitem >= 0 && listitem < cache_num_rows())
                {
                    cache_get_value_name(listitem, "invItem", FactionBrankas[playerid][factionBrankasTemp]);
                    cache_get_value_name_int(listitem, "invModel", FactionBrankas[playerid][factionBrankasModel]);
                    cache_get_value_name_int(listitem, "invQuantity", FactionBrankas[playerid][factionBrankasQuant]);

                    new shstr[528];
                    format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon masukkan jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                    ShowPlayerDialog(playerid, DIALOG_FAMSVAULT_IN, DIALOG_STYLE_INPUT, sprintf("Brankas %s", FamData[famid][famName]), 
                    shstr, "Input", "Batal");
                }
            }
        }
        case DIALOG_FAMSVAULT_IN:
        {
            if(GetTickCount() - BrankasLastUse[playerid] < 2000)
            {
                AccountData[playerid][menuShowed] = false;
                ShowTDN(playerid, NOTIFICATION_ERROR, "mohon tunggu sebentar!");
                return 1;
            }
            BrankasLastUse[playerid] = GetTickCount();
            if(AccountData[playerid][pFamily] == -1)
            {
                AccountData[playerid][menuShowed] = false;
                BrankasLastUse[playerid] = 0;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Families!");
            }
            new famid = AccountData[playerid][pFamily];
            
            if(!response)
            {
                AccountData[playerid][menuShowed] = false;
                BrankasLastUse[playerid] = 0;
                return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            }

            new shstr[512];
            if(isnull(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nTidak dapat diisi kosong!\nMohon masukkan jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_FAMSVAULT_IN, DIALOG_STYLE_INPUT, sprintf("Brankas %s", FamData[famid][famName]), 
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nHanya dapat diisi angka!\nMohon masukkan jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_FAMSVAULT_IN, DIALOG_STYLE_INPUT, sprintf("Brankas %s", FamData[famid][famName]), 
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[playerid][factionBrankasQuant])
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan jumlah item yang ingin disimpan:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_FAMSVAULT_IN, DIALOG_STYLE_INPUT, sprintf("Brankas %s", FamData[famid][famName]), 
                shstr, "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);

            Inventory_Remove(playerid, FactionBrankas[playerid][factionBrankasTemp], quantity);
            ShowItemBox(playerid, sprintf("Removed %dx", quantity), FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel]);

            new invstr[1028];
            mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `badside_brankas` WHERE `ID`=%d AND `fItemName`='%s'", AccountData[playerid][pFamily], FactionBrankas[playerid][factionBrankasTemp]);
            mysql_query(g_SQL, shstr);
            new rows = cache_num_rows();
            if(rows > 0)
            {
                mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `badside_brankas` SET `fItemQuantity` = `fItemQuantity` + %d WHERE `ID`=%d AND `fItemName`='%s'", quantity, AccountData[playerid][pFamily], FactionBrankas[playerid][factionBrankasTemp]);
                mysql_tquery(g_SQL, invstr, "OnBadsideDeposit", "i", playerid);
            }
            else 
            {
                mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `badside_brankas` SET `ID`=%d, `fItemName`='%s', `fItemModel`=%d, `fItemQuantity`=%d", AccountData[playerid][pFamily], FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel], quantity);
                mysql_tquery(g_SQL, invstr, "OnBadsideDeposit", "i", playerid);
            }
            AccountData[playerid][menuShowed] = false;
        }
        case DIALOG_FAMSVAULT_WITHDRAW:
        {
            if(AccountData[playerid][pFamily] == -1)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Families!");
            }
            
            if(!response)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            }

            if(listitem == -1)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih barang!");
            }

            new tss[188];
            mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `badside_brankas` WHERE `ID`=%d", AccountData[playerid][pFamily]);
            mysql_query(g_SQL, tss);
            if(cache_num_rows() > 0)
            {
                cache_get_value_name_int(listitem, "fItemID", FactionBrankas[playerid][factionBrankasID]);
                cache_get_value_name(listitem, "fItemName", FactionBrankas[playerid][factionBrankasTemp]);
                cache_get_value_name_int(listitem, "fItemModel", FactionBrankas[playerid][factionBrankasModel]);
                cache_get_value_name_int(listitem, "fItemQuantity", FactionBrankas[playerid][factionBrankasQuant]);

                new shstr[528];
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nMohon masukkan berapa jumlah item yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_FAMSVAULT_OUT, DIALOG_STYLE_INPUT, sprintf("Brankas %s", FamData[AccountData[playerid][pFamily]][famName]),
                shstr, "Input", "Batal");
            }
        }
        case DIALOG_FAMSVAULT_OUT:
        {
            if(AccountData[playerid][pFamily] == -1)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Families!");
            }
            new famid = AccountData[playerid][pFamily];
            
            if(!response)
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            }

            new shstr[512];
            if(isnull(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nTidak dapat diisi kosong!\nMohon masukkan berapa jumlah item yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_FAMSVAULT_OUT, DIALOG_STYLE_INPUT, sprintf("Brankas %s", FamData[famid][famName]),
                shstr, "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah item yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_FAMSVAULT_OUT, DIALOG_STYLE_INPUT, sprintf("Brankas %s", FamData[famid][famName]),
                shstr, "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > FactionBrankas[playerid][factionBrankasQuant])
            {
                AccountData[playerid][menuShowed] = true;
                format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah item yang ingin anda ambil:", FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasQuant]);
                ShowPlayerDialog(playerid, DIALOG_FAMSVAULT_OUT, DIALOG_STYLE_INPUT, sprintf("Brankas %s", FamData[famid][famName]),
                shstr, "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext), jts[155];

            if(GetTotalWeightFloat(playerid) >= 50) 
            {
                AccountData[playerid][menuShowed] = false;
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
            }
            
            FactionBrankas[playerid][factionBrankasQuant] -= quantity;
            if(FactionBrankas[playerid][factionBrankasQuant] > 0)
            {
                mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `badside_brankas` SET `fItemQuantity`=%d WHERE `fItemID`=%d", FactionBrankas[playerid][factionBrankasQuant], FactionBrankas[playerid][factionBrankasID]);
                mysql_tquery(g_SQL, jts);
            }
            else 
            {
                mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `badside_brankas` WHERE `fItemID`=%d", FactionBrankas[playerid][factionBrankasID]);
                mysql_tquery(g_SQL, jts);
            }
            Inventory_Add(playerid, FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel], quantity);
            ShowItemBox(playerid, sprintf("Received %dx", quantity), FactionBrankas[playerid][factionBrankasTemp], FactionBrankas[playerid][factionBrankasModel]);
            
            new frmxt[268];
            format(frmxt, sizeof(frmxt), "Mengambil %d %s dari brankas families", quantity, FactionBrankas[playerid][factionBrankasTemp]);
            AddFamiliesLog(AccountData[playerid][pName], AccountData[playerid][pUCP], frmxt, GetFamiliesName(playerid));
            
            FactionBrankas[playerid][factionBrankasID] = 0;
            FactionBrankas[playerid][factionBrankasTemp] = EOS;
            FactionBrankas[playerid][factionBrankasModel] = 0;
            FactionBrankas[playerid][factionBrankasQuant] = 0;
            AccountData[playerid][menuShowed] = false;
        }
        case DIALOG_FAMILIESSETRANK:
        {
            new famid = AccountData[playerid][pFamily];
            if(famid == -1) return false;

            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFamily] != famid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari keluarga ini!");
            if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak tergabung dengan keluarga manapun!");

            mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `Char_Family` = %d ORDER BY `Char_FamilyRank` DESC", famid));
            new rows = cache_num_rows();
            if(rows)
            {
                cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFamMemberID]);
                cache_get_value_name_int(listitem, "Char_FamilyRank", AccountData[playerid][pTempSQLFamRank]);
                if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFamMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengatur jabatan diri sendiri!");
                if(AccountData[playerid][pTempSQLFamRank] >= AccountData[playerid][pFamilyRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengatur jabatan pangkat diatasmu!");
                ShowPlayerDialog(playerid, DIALOG_RANK_SET_FAMILIES, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Set Jabatan",
                "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
                1. Relasi\n\
                2. Outsider\n\
                3. Insider\n\
                4. Tangan Kanan\n\
                5. Wakil Ketua\n\
                6. Ketua", "Set", "Batal");
            }
        }
        case DIALOG_FAMILIESKICKMEMBER:
        {
            new famid = AccountData[playerid][pFamily];
            if(famid == -1) return false;

            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFamily] != famid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari keluarga ini!");
            if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak tergabung dengan keluarga manapun!");

            mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `Char_Family` = %d ORDER BY `Char_FamilyRank` DESC", famid));
            if(cache_num_rows())
            {
                new pidrow, fckname[64], fckrank, fcklastlogin[30], kckstr[225], icsr[128];

                cache_get_value_name_int(listitem, "pID", pidrow);
                cache_get_value_name(listitem, "Char_Name", fckname);
                cache_get_value_name_int(listitem, "Char_FamilyRank", fckrank);
                cache_get_value_name(listitem, "Char_LastLogin", fcklastlogin);

                if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFamMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat kick diri sendiri!");
                if(AccountData[playerid][pTempSQLFamRank] >= AccountData[playerid][pFamilyRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat kick pangkat diatasmu!");

                foreach(new i : Player) 
                {
                    if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && pidrow == AccountData[i][pID])
                    {
                        AccountData[i][pFamily] = -1;
                        AccountData[i][pFamilyRank] = 0;

                        ShowTDN(i, NOTIFICATION_WARNING, sprintf("Anda telah dikeluarkan dari Keluarga %s", FamData[famid][famName]));
                    }
                }
                mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Family`=-1, `Char_FamilyRank`=0 WHERE `pID`=%d", pidrow);
                mysql_tquery(g_SQL, icsr);
                format(kckstr, sizeof(kckstr), "Anda telah berhasil menendang anggota:\n\
                Nama: %s\n\
                Rank: %s\n\
                Last Online: %s", fckname, FamiliesRank[fckrank], fcklastlogin);
                ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota",
                kckstr, "Tutup", "");
            }
        }
        case DIALOG_RANK_SET_FAMILIES:
        {
            new famid = AccountData[playerid][pFamily];
            if(famid == -1) return false;

            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            if(AccountData[playerid][pFamily] != famid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Families ini!");
            if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak tergabung Families manapun!");
            if(AccountData[playerid][pFamilyRank] < 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal Rank Wakil Ketua untuk akses Bos Desk!");

            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_FAMILIES, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Error: Tidak dapat diisi kosong!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Relasi\n\
            2. Outsider\n\
            3. Insider\n\
            4. Tangan Kanan\n\
            5. Wakil Ketua\n\
            6. Ketua", "Set", "Batal");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_FAMILIES, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Error: Hanya dapat diisi angka!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Relasi\n\
            2. Outsider\n\
            3. Insider\n\
            4. Tangan Kanan\n\
            5. Wakil Ketua\n\
            6. Ketua", "Set", "Batal");

            if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pFamilyRank]) return ShowPlayerDialog(playerid, DIALOG_RANK_SET_FAMILIES, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Kelola Jabatan", \
            "Error: Tidak dapat diisi dibawah 1 atau lebih tinggi dari jabatan anda!\n\
            Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
            1. Relasi\n\
            2. Outsider\n\
            3. Insider\n\
            4. Tangan Kanan\n\
            5. Wakil Ketua\n\
            6. Ketua", "Set", "Batal");

            new affah[128];
            mysql_format(g_SQL, affah, sizeof(affah), "UPDATE `player_characters` SET `Char_FamilyRank`=%d WHERE `pID`=%d", strval(inputtext), AccountData[playerid][pTempSQLFamMemberID]);
            mysql_tquery(g_SQL, affah);

            foreach(new i : Player)
            {
                if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && AccountData[playerid][pTempSQLFamMemberID] == AccountData[i][pID])
                {
                    AccountData[i][pFamilyRank] = strval(inputtext);
                    ShowTDN(i, NOTIFICATION_INFO, "Jabatan baru anda di families telah diubah");
                }
            }

            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengubah jabatan families player tersebut");
        }
        case DIALOG_FAMILY_PANEL:
        {
            if(!response) return 1;
            if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak tergabung di keluarga manapun!");
            if(IsPlayerInjured(playerid) == 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan, tidak dapat menggunakan Panel!");
            new targetid = AccountData[playerid][pTarget];
            if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke dalam server!");
            if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak didekat anda!");
            switch(listitem)
            {
                case 0:// Geledah
                {
                    if(AccountData[playerid][pFamilyRank] < 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Insider untuk menggeledah!");
                    if(IsPlayerPlayingAnimation(targetid, "ROB_BANK", "SHP_HandsUp_Scr") || AccountData[targetid][pInjured])
                    {
                        Families_GedelahFiture(playerid, targetid);
                        SendRPMeAboveHead(playerid, "Menggeledah paksa orang didepan", X11_PLUM1);
                        ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 3000, 1);
                    }
                    else return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak mengangkat tangannya!");
                }
                case 1:// Ikat
                {
                    AccountData[targetid][pCuffed] = 1;
                    SetPlayerSpecialAction(targetid, SPECIAL_ACTION_CUFFED);
                    SendRPMeAboveHead(playerid, "Mengikat orang didepannya menggunakan tali", X11_PLUM1);
                    ShowTDN(targetid, NOTIFICATION_WARNING, "Anda sedang diikat!");
                }
                case 2:// Lepas Ikatan
                {
                    AccountData[targetid][pCuffed] = 0;
                    SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
                    SendRPMeAboveHead(playerid, "Melepaskan ikatan orang didepan", X11_PLUM1);
                    ShowTDN(targetid, NOTIFICATION_WARNING, "Ikatan anda telah dilepaskan!");
                }
                case 3:// Seret
                {
                    if(AccountData[targetid][pCuffed] != 1)
                        return ShowTDN(playerid, NOTIFICATION_ERROR, "Orang tersebut belum diikat!");

                    CarryPlayerNearest(playerid, targetid);
                    SendRPMeAboveHead(playerid, "Menyeret paksa orang didepan", X11_PLUM1);
                }
                case 4:// Lepas Seret
                {
                    new oncarry = IsDragging[playerid];
                    TogglePlayerControllable(oncarry, true);
                    AccountData[oncarry][pDraggedBy] = INVALID_PLAYER_ID;
                    IsDragging[playerid] = INVALID_PLAYER_ID;
                    SendRPMeAboveHead(playerid, "Melepaskan seretan", X11_LIGHTGREEN);
                }
                case 5:// Masukkan kedalam mobil
                {
                    new vehicleid = GetNearestVehicleToPlayer(playerid, 3.0, false);

                    if(AccountData[targetid][pCuffed] != 1)	
                        return ShowTDN(playerid, NOTIFICATION_ERROR, "Orang itu belum di ikat!.");
                    
                    if(vehicleid == INVALID_VEHICLE_ID)
                        return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak berada didekat kendaraan apapun!.");
                    
                    if(GetVehicleMaxSeats(vehicleid) < 2)
                        return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak dapat memasukan orang kedalam kendaraan ini!");

                    if(!IsPlayerInVehicle(targetid, vehicleid))
                    {
                        new seatid = GetAvailableSeat(vehicleid, 2);

                        if(seatid == -1)
                            return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada bangku kosong lagi!.");

                        new
                            string[64];

                        format(string, sizeof(string), "Kamu dimasukan paksa kedalam mobil oleh seseorang");
                        ShowTDN(targetid, NOTIFICATION_WARNING, string);
                        TogglePlayerControllable(targetid, 0);

                        PutPlayerInVehicle(targetid, vehicleid, seatid);
                    }
                }
                case 6:// Keluarkan paksa dari mobil
                {
                    new vehicleid = GetNearestVehicleToPlayer(playerid, 3.0, false);

                    if(IsPlayerInVehicle(targetid, vehicleid))
                    {
                        TogglePlayerControllable(targetid, 1);

                        RemoveFromVehicle(targetid);
                        SendRPMeAboveHead(playerid, "Mengeluarkan paksa seseorang dari kendaraan", X11_PLUM1);
                    }
                }
                case 7:// karung
                {
                    if(AccountData[targetid][pDurringKarung]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut telah dikarungi!");

					SendRPMeAboveHead(playerid, "Memakaikan karung ke kepala orang didepan", X11_PLUM1);
					SetPlayerAttachedObject(targetid, 9, 2060, 2, -0.096, 0.000, -0.017, -101.300, 0.000, -5.600, 0.623, 1.000, 1.302);
					ShowKarungTD(targetid);
					AccountData[targetid][pDurringKarung] = true;
                }
                case 8:// Lepas Karung
                {
                    if(!AccountData[targetid][pDurringKarung]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut belum dikarungi!");

					if(AccountData[targetid][pDurringKarung]) {
						HideKarungTD(targetid);
						AccountData[targetid][pDurringKarung] = false;
						RemovePlayerAttachedObject(targetid, 9);
					}
					SendRPMeAboveHead(playerid, "Melepaskan karung dari kepala orang didepan", X11_PLUM1);
                }
                case 9: // Ambil Uang Kotor
                {
                    if(AccountData[targetid][pRedMoney] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki uang kotor!");
                    
                    new frmxt[225];
                    format(frmxt, sizeof(frmxt), ""WHITE"Jumlah uang merah yang dimiliki: "RED"%s"WHITE"\nMohon masukkan jumlah yang ingin anda ambil paksa:", FormatMoney(AccountData[targetid][pRedMoney]));
                    ShowPlayerDialog(playerid, DIALOG_FAMSTAKE_REDMONEY, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Ambil Uang Merah", frmxt, "Input", "Batal");
                    SetPVarInt(playerid, "TargetFamsID", targetid);
                }
                case 10: // ambil uang
                {
                    // Lanjutkan proses ambil uang
                    if(AccountData[targetid][pMoney] < 1)
                        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki uang!");

                    // Buka dialog input jumlah
                    new frmxt[225];
                    format(frmxt, sizeof(frmxt), ""WHITE"Jumlah uang yang dimiliki: "DARKGREEN"%s"WHITE"\nMohon masukkan jumlah yang ingin anda ambil paksa:", FormatMoney(AccountData[targetid][pMoney]));
                    ShowPlayerDialog(playerid, DIALOG_FAMSTAKE_MONEY2, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Ambil Uang", frmxt, "Input", "Batal");
                    SetPVarInt(playerid, "TargetFamsID", targetid);
                }
                case 11: // Cek Senjata
                {
                    CheckTargetWeapon(playerid, targetid);
                }
            }
        }
    }
    return 1;
}

Dialog:FamiliesKantongList(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        for (new i = 0; i < MAX_PLAYERS; i ++)
            NearestPlayer[playerid][i] = INVALID_PLAYER_ID;
        return 1;
    }
    
    new targetid = NearestPlayer[playerid][listitem];
    if (!IsPlayerConnected(targetid)) 
    {
        for (new i = 0; i < MAX_PLAYERS; i ++)
            NearestPlayer[playerid][i] = INVALID_PLAYER_ID;
        
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    }

    if (targetid != INVALID_PLAYER_ID)
    {
        AccountData[playerid][pTarget] = targetid;
        DisplayFactionMenu(playerid);
    }
    return 1;
}

Dialog:Bosdesk_Family(playerid, response, listitem, inputtext[])
{
    new id = AccountData[playerid][pFamily];
    if(id == -1) return 0;

    if(!response) return 1;
    if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak termasuk Keluarga manapun!");
    if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan, tidak dapat melakukan ini!");
    switch(listitem)
    {
        case 0:// Invite
        {
            new str[512], sstr[512], count = 0;
            foreach(new i : Player) if (i != playerid && IsPlayerConnected(i)) {
                if(IsPlayerNearPlayer(playerid, i, 3.0)) {
                    format(str, sizeof(str), "Kantong: %d\n", i);
                    strcat(sstr, str, sizeof(sstr));
                    ListBosDesk[playerid][count ++] = i;
                }
            }
            if(!count) return Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Invite", "Tidak ada orang yang dekat dengan anda!", "Close", "");
            Dialog_Show(playerid, FamiliesInvite, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Invite", sstr, "Pilih", "Batal");
        }
        case 1:// Kelola Jabatan Online / Offline
        {
            mysql_query(g_SQL, sprintf("SELECT * FROM player_characters WHERE Char_Family = %d ORDER BY Char_FamilyRank DESC", AccountData[playerid][pFamily]));

            new rows = cache_num_rows();
            if(rows)
            {
                new fckname[64], fckrank, fcklastlogin[30], shstr[2048];

                format(shstr, sizeof(shstr), "Nama\tRank\tLast Online\n");
                for(new i; i < rows; ++i)
                {
                    cache_get_value_name(i, "Char_Name", fckname);
                    cache_get_value_name_int(i, "Char_FamilyRank", fckrank);
                    cache_get_value_name(i, "Char_LastLogin", fcklastlogin);

                    format(shstr, sizeof(shstr), "%s%s\t%s\t%s\n", shstr, fckname, FamiliesRank[fckrank], fcklastlogin);
                }
                ShowPlayerDialog(playerid, DIALOG_FAMILIESSETRANK, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Set Jabatan", shstr, "Pilih", "Batal");
            }
            else 
            {
                PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Set Jabatan", "Tidak ada Anggota Families!", "Tutup", "");
            }
        }
        case 2:// Offline Kick / Online
        {
            mysql_query(g_SQL, sprintf("SELECT * FROM player_characters WHERE Char_Family = %d ORDER BY Char_FamilyRank DESC", AccountData[playerid][pFamily]));

            new rows = cache_num_rows();
            if(rows)
            {
                new fckname[64], fckrank, fcklastlogin[30], shstr[2048];

                format(shstr, sizeof(shstr), "Nama\tRank\tLast Online\n");
                for(new i; i < rows; ++i)
                {
                    cache_get_value_name(i, "Char_Name", fckname);
                    cache_get_value_name_int(i, "Char_FamilyRank", fckrank);
                    cache_get_value_name(i, "Char_LastLogin", fcklastlogin);

                    format(shstr, sizeof(shstr), "%s%s\t%s\t%s\n", shstr, fckname, FamiliesRank[fckrank], fcklastlogin);
                }
                ShowPlayerDialog(playerid, DIALOG_FAMILIESKICKMEMBER, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Kick Member", shstr, "Kick", "Batal");
            }
            else 
            {
                PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Member", "Tidak ada Anggota Families!", "Tutup", "");
            }
        }
        case 3:// cek keuangan
        {
            new sstr[512];
            format(sstr, sizeof(sstr), "Keluarga kita saat ini memiliki uang sebesar %s\nSiapapun yang mengambil uang tanpa sepengetahuan bersama akan mendapatkan hukumannya", FormatMoney(FamData[id][famMoney]));
            Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Keuangan Families", sstr, "Tutup", "");
        }
        case 4:// Ambil atau taruh uang
        {
            new sstr[512];
            format(sstr, sizeof sstr, "Mohon ikuti format berikut:\nGunakanlah format ambil [jumlah] atau depo [jumlah] untuk mengambil atau menaruh uang\nGunakan tanpa tanda ][ pada kolom dibawah ini:");
            Dialog_Show(playerid, FamiliesKeuangan, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Keuangan Families", sstr, "Input", "Batal");
        }
    }
    return 1;
}
Dialog:FamiliesKeuangan(playerid, response, listitem, inputtext[])
{
    new id = AccountData[playerid][pFamily];
    if(id == -1) return 0;
    if(response)
    {
        new option[128], amount;
        if(sscanf(inputtext, "s[128]d", option, amount))
        {
            new sstr[512];
            format(sstr, sizeof sstr, "Mohon ikuti format berikut:\nGunakanlah format ambil [jumlah] atau depo [jumlah] untuk mengambil atau menaruh uang\nGunakan tanpa tanda ][ pada kolom dibawah ini:");
            Dialog_Show(playerid, FamiliesKeuangan, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Keuangan Families", sstr, "Input", "Batal");
        }

        if(!strcmp(option, "ambil", true))
        {
            if(amount > FamData[id][famMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang di brankas tidak sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Input");

            FamData[id][famMoney] -= amount;
            GiveMoney(playerid, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda mengambil uang dari Brankas");
            Families_Save(id);
        }
        else if(!strcmp(option, "depo", true))
        {
            if(amount > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak sebanyak itu!");
            if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid input!");

            FamData[id][famMoney] += amount;
            TakeMoney(playerid, amount);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda menyimpan uang ke Brankas");
            Families_Save(id);
        }
    }
    return 1;
}

Dialog:FamiliesInvite(playerid, response, listitem, inputtext[])
{
    new id = ListBosDesk[playerid][listitem];
    if(response) 
    {
        if(AccountData[id][pFaction] != 0)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut berada di Factions lain!");
        if(AccountData[id][pFamily] != -1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut telah tergabung dengan Keluarga!");
        
        AccountData[id][pFamily] = AccountData[playerid][pFamily];
        AccountData[id][pFamilyRank] = 1;
        ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda menjadikan %s bagian dari keluarga!", GetRPName(id)));
        ShowTDN(id, NOTIFICATION_INFO, sprintf("%s Menjadikan anda bagian dari keluarganya", GetRPName(playerid)));
        
        new icsr[200];
        mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Family`=%d, `Char_FamilyRank`=1 WHERE `pID`=%d", AccountData[playerid][pFamily], AccountData[id][pID]);
        mysql_tquery(g_SQL, icsr);
    }
    return 1;
}

Dialog:FamiliesGeledah(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new targetid = AccountData[playerid][pTarget];
        AccountData[playerid][pListItemGudang] = ListedFamItem[playerid][listitem];

        new 
            name[48],
            str[128];
        
        strunpack(name, InventoryData[targetid][listitem][invItem]);
        if(InventoryData[targetid][listitem][invExists])
        {
            format(str, sizeof(str), "Anda akan mengambil barang:\nNama: %s\nJumlah: %d\nMohon masukan jumlah yang ingin anda ambil:", name, InventoryData[targetid][listitem][invQuantity]);
            Dialog_Show(playerid, FamiliesTakeBarang, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Geledah", str, "Input", "Back");
        }
    }
    return 1;
}

Dialog:FamiliesTakeBarang(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new targetid = AccountData[playerid][pTarget];
        if(AccountData[targetid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Pemain tersebut sedang melakukan sesuatu, harap tunggu!");
        if(AccountData[targetid][menuShowed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang ingin menyimpan sesuatu!");

        new 
            itemid = -1,
            string[32];
        
        itemid = AccountData[playerid][pListItemGudang];
        new model = InventoryData[targetid][itemid][invModel];
        strunpack(string, InventoryData[targetid][itemid][invItem]);

        new amount = floatround(strval(inputtext));

        if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Input");
        if(amount > InventoryData[targetid][itemid][invQuantity]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Barang pemain tersebut tidak sebanyak itu");
        if(!strcmp(string, "Radio", true))
        {
            if(ToggleRadio[targetid] || RadioMicOn[targetid])
            {
                ToggleRadio[targetid] = false;
                RadioMicOn[targetid] = false;
                CallRemoteFunction("UpdatePlayerVoiceMicToggle", "dd", targetid, false);
                CallRemoteFunction("UpdatePlayerVoiceRadioToggle", "dd", targetid, false);
                CallRemoteFunction("AssignFreqToFSVoice", "ddd", targetid, true, 0);
                PlayerTextDrawSetString(targetid, ATRP_RadioTD[targetid][7], "0");
            }
        }

        Inventory_Add(playerid, string, InventoryData[targetid][itemid][invModel], amount);
        Inventory_Remove(targetid, string, amount);
        
        ShowItemBox(playerid, sprintf("Received %dx", amount), string, model);
        ShowItemBox(targetid, sprintf("Removed %dx", amount), string, model);
        SendRPMeAboveHead(playerid, "Mengambil paksa barang orang didepan", X11_PLUM1);
        SendClientMessageEx(targetid, -1, "[i] "YELLOW"%s(%d)"WHITE" mengambil item "ORANGE"%s"WHITE" anda sebanyak "ORANGE"%dx", AccountData[playerid][pName], playerid, string, amount);

        new frmxt[268];
        format(frmxt, sizeof(frmxt), "Mengambil barang %s milik %s sejumlah %d", string, AccountData[targetid][pName], amount);
        AddFamiliesLog(AccountData[playerid][pName], AccountData[playerid][pUCP], frmxt, GetFamiliesName(playerid));
    }
    return 1;
}

forward SellMarjun(playerid);
public SellMarjun(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerJualMarijuana[playerid]);
        pTimerJualMarijuana[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!PlayerHasItem(playerid, "Marijuana"))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Marijuana!");
        KillTimer(pTimerJualMarijuana[playerid]);
        pTimerJualMarijuana[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pTimerJualMarijuana[playerid]);
        pTimerJualMarijuana[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        new total = Inventory_Count(playerid, "Marijuana");
        new pay = total * 25;

        Inventory_Remove(playerid, "Marijuana", total);
        GiveMoney(playerid, pay);
        ShowItemBox(playerid, sprintf("Removed %dx", total), "MARIJUANA", 1575);
        ShowItemBox(playerid, sprintf("Received %s", FormatMoney(pay)), "UANG", 1212);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/15;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward WashingRedMoney(playerid);
public WashingRedMoney(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerWashRedMoney[playerid]);
        pTimerWashRedMoney[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
    }

    if(!IsValidDynamicArea(Families_Stuffs[WashRedMoney]))
    {
        KillTimer(pTimerWashRedMoney[playerid]);
        pTimerWashRedMoney[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, Families_Stuffs[WashRedMoney]))
    {
        KillTimer(pTimerWashRedMoney[playerid]);
        pTimerWashRedMoney[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pTimerWashRedMoney[playerid]);
        pTimerWashRedMoney[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pRedMoney] < 1)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Uang Merah!");
        KillTimer(pTimerWashRedMoney[playerid]);
        pTimerWashRedMoney[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15)
    {
        KillTimer(pTimerWashRedMoney[playerid]);
        pTimerWashRedMoney[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        new value = (AccountData[playerid][pRedMoney] / 100) * 85;
        AccountData[playerid][pRedMoney] = 0;
        GiveMoney(playerid, value);
        ShowItemBox(playerid, sprintf("Received %s", FormatMoney(value)), "Uang", 1212);
        Info(playerid, "Anda mendapatkan "GREEN"%s"WHITE" (85 persen) dari hasil pencucian uang", FormatMoney(value));
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/15;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

/*DialogPages:FamiliesSetRank(playerid, response, listitem, inputtext[])
{
    new famid = AccountData[playerid][pFamily];
    if(famid == -1) return false;

    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pFamily] != famid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari keluarga ini!");
    if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak tergabung dengan keluarga manapun!");

    mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `Char_Family` = %d ORDER BY `Char_FamilyRank` DESC", famid));
    new rows = cache_num_rows();
    if(rows)
    {
        cache_get_value_name_int(listitem, "pID", AccountData[playerid][pTempSQLFamMemberID]);
        cache_get_value_name_int(listitem, "Char_FamilyRank", AccountData[playerid][pTempSQLFamRank]);
        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFamMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat mengatur jabatan diri sendiri!");
        if(AccountData[playerid][pTempSQLFamRank] >= AccountData[playerid][pFamilyRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat mengatur jabatan pangkat diatasmu!");
        ShowPlayerDialog(playerid, DIALOG_RANK_SET_FAMILIES, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Set Jabatan",
        "Silahkan pilih jabatan untuk ditetapkan (masukkan angka saja):\n\
        1. Relasi\n\
        2. Outsider\n\
        3. Insider\n\
        4. Tangan Kanan\n\
        5. Wakil Ketua\n\
        6. Ketua", "Set", "Batal");
    }
    return 1;
}

DialogPages:FamiliesKickMember(playerid, response, listitem, inputtext[])
{
    new famid = AccountData[playerid][pFamily];
    if(famid == -1) return false;

    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pFamily] != famid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari keluarga ini!");
    if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak tergabung dengan keluarga manapun!");

    mysql_query(g_SQL, sprintf("SELECT * FROM `player_characters` WHERE `Char_Family` = %d ORDER BY `Char_FamilyRank` DESC", famid));
    if(cache_num_rows())
    {
        new pidrow, fckname[64], fckrank, fcklastlogin[30], kckstr[225], icsr[128];

        cache_get_value_name_int(listitem, "pID", pidrow);
        cache_get_value_name(listitem, "Char_Name", fckname);
        cache_get_value_name_int(listitem, "Char_FamilyRank", fckrank);
        cache_get_value_name(listitem, "Char_LastLogin", fcklastlogin);

        if(AccountData[playerid][pID] == AccountData[playerid][pTempSQLFamMemberID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat kick diri sendiri!");
        if(AccountData[playerid][pTempSQLFamRank] >= AccountData[playerid][pFamilyRank]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat kick pangkat diatasmu!");

        foreach(new i : Player) 
        {
            if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && pidrow == AccountData[i][pID])
            {
                AccountData[i][pFamily] = -1;
                AccountData[i][pFamilyRank] = 0;

                ShowTDN(i, NOTIFICATION_WARNING, sprintf("Anda telah dikeluarkan dari Keluarga %s", FamData[famid][famName]));
            }
        }
        mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Family`=-1, `Char_FamilyRank`=0 WHERE `pID`=%d", pidrow);
        mysql_tquery(g_SQL, icsr);
        format(kckstr, sizeof(kckstr), "Anda telah berhasil menendang anggota:\n\
        Nama: %s\n\
        Rank: %s\n\
        Last Online: %s", fckname, FamiliesRank[fckrank], fcklastlogin);
        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kick Anggota",
        kckstr, "Tutup", "");
    }
    return 1;
}*/

forward OnBadsideDeposit(playerid);
public OnBadsideDeposit(playerid)
{
    AccountData[playerid][menuShowed] = false;
    BrankasLastUse[playerid] = 0;
    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyimpan barang!");
    FactionBrankas[playerid][factionBrankasID] = 0;
    FactionBrankas[playerid][factionBrankasTemp] = EOS;
    FactionBrankas[playerid][factionBrankasModel] = 0;
    FactionBrankas[playerid][factionBrankasQuant] = 0;
    return 1;
}
