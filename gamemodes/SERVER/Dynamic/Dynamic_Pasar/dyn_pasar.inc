#include <YSI\y_hooks>
#define MAX_PASAR   20

enum e_pasar
{
    Float:pasarPos[3],
    pasarType,
    pasarInt,
    pasarWorld,
    Text3D:pasarLabel,
    STREAMER_TAG_AREA:pasarArea,
}
new PasarData[MAX_PASAR][e_pasar],
    Iterator:PASAR<MAX_PASAR>;

forward LoadPasar();
public LoadPasar()
{
    new id, rows = cache_num_rows();
    new Cache:Psrcache;
    if(rows)
    {
        Psrcache = cache_save();

        for(new i = 0; i < rows; i ++)
        {
            id = cache_get_field_int(i, "id");
            PasarData[id][pasarPos][0] = cache_get_field_float(i, "posx");
			PasarData[id][pasarPos][1] = cache_get_field_float(i, "posy");
			PasarData[id][pasarPos][2] = cache_get_field_float(i, "posz");
			PasarData[id][pasarType] = cache_get_field_int(i, "type");
			PasarData[id][pasarInt] = cache_get_field_int(i, "interior");
			PasarData[id][pasarWorld] = cache_get_field_int(i, "world");
            
            Iter_Add(PASAR, id);
            Pasar_Refresh(id);
        }
        printf("[Dynamic PASAR]: Jumlah total Pasar yang dimuat %d", rows);

        if(cache_is_valid(Psrcache))
        {
            cache_delete(Psrcache);
            printf("[Dynamic PASAR]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic PASAR]: Cache tidak valid atau sudah dihapus.");
        }
    }
    return 1;
}

Pasar_Refresh(id)
{
    if(id != -1)
    {
        if(PasarData[id][pasarType] == 1)
        {
            PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual Susu Olahan", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
        }
        else if(PasarData[id][pasarType] == 2)
        {
            PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual Hasil Tambang", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
        }
        else if(PasarData[id][pasarType] == 3)
        {
            PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual Kayu Kemas", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
        }
        else if(PasarData[id][pasarType] == 4)
        {
            PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual Ayam Kemas", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
        }
        else if(PasarData[id][pasarType] == 5)
        {
            PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual Hasil Daur", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
        }
        else if(PasarData[id][pasarType] == 6)
        {
            PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual/membeli Hasil Tani", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
        }
        else if(PasarData[id][pasarType] == 7)
        {
            PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual Pakaian", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
        }
        else if(PasarData[id][pasarType] == 8)
        {
            PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual GAS", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
        }
        else if(PasarData[id][pasarType] == 9)
        {
            PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual Ikan Nelayan", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
        }
    }
    return 1;
}

Pasar_Save(id)
{
    new cQuery[1056];
    format(cQuery, sizeof(cQuery), "UPDATE pasar SET posx='%f', posy='%f', posz='%f', type='%d', interior='%d', world='%d' WHERE id='%d'",
    PasarData[id][pasarPos][0],
    PasarData[id][pasarPos][1],
    PasarData[id][pasarPos][2],
    PasarData[id][pasarType],
    PasarData[id][pasarInt],
    PasarData[id][pasarWorld],
    id
    );
    return mysql_tquery(g_SQL, cQuery);
}

CMD:addpasar(playerid, params[])
{
    if(CheckAdmin(playerid, 6))
        return PermissionError(playerid);
    
    new id = Iter_Free(PASAR), query[512];
    new type;

    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat menambah pasar lagi!");
    if(sscanf(params, "d", type))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addpasar [type] [1 - 9]");
    
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    PasarData[id][pasarPos][0] = x;
    PasarData[id][pasarPos][1] = y;
    PasarData[id][pasarPos][2] = z;
    PasarData[id][pasarType] = type;
    PasarData[id][pasarInt] = GetPlayerInterior(playerid);
    PasarData[id][pasarWorld] = GetPlayerVirtualWorld(playerid);
    if(type == 1)
    {
        PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual Susu Olahan", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
    }
    else if(type == 2)
    {
        PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual Hasil Tambang", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
    }
    else if(type == 3)
    {
        PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual Kayu Kemas", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
    }
    else if(type == 4)
    {
        PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual Ayam Kemas", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
    }
    else if(type == 5)
    {
        PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual Hasil Daur", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
    }
    else if(type == 6)
    {
        PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual/membeli Hasil Tani", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
    }
    else if(type == 7)
    {
        PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual Pakaian", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
    }
    else if(type == 8)
    {
        PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual Gas", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
    }
    else if(type == 9)
    {
        PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf(""LIGHTGREY"[PID: %d]\n"WHITE"Tekan"VERONA_GREEN" [Y]"WHITE" untuk menjual Ikan Nelayan", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
    }
    else
    {
        PasarData[id][pasarLabel] = CreateDynamic3DTextLabel(sprintf("Unknows", id), -1, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2] + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
    }
    Iter_Add(PASAR, id);

    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah membuat Dynamic Pasar ID: %d.", GetAdminName(playerid), id);
    mysql_format(g_SQL, query, sizeof(query), "INSERT INTO pasar SET id=%d, posx='%f', posy='%f', posz='%f', type='%d', interior=%d, world=%d", id, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2], PasarData[id][pasarType], PasarData[id][pasarInt], PasarData[id][pasarWorld]);
	mysql_tquery(g_SQL, query, "OnPasarCreated", "ii", playerid, id);
	return 1;
}

VRRP::OnPasarCreated(playerid, id)
{
    Pasar_Save(id);
    SendClientMessageEx(playerid, -1, "[!]: Kamu membuat Dynamic pasar ID %d", id);
    return 1;
}

CMD:removepasar(playerid, params[])
{
    if(CheckAdmin(playerid, 6))
        return PermissionError(playerid);
    
    new id;
    if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/removepasar [id]");
    if(!Iter_Contains(PASAR, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Pasar tidak ditemukan");

    DestroyDynamic3DTextLabel(PasarData[id][pasarLabel]);
    Iter_Remove(PASAR, id);

    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menghapus Dynamic Pasar ID: %d.", GetAdminName(playerid), id);
    mysql_tquery(g_SQL, sprintf("DELETE FROM pasar WHERE id='%d'", id));
    return 1;
}

CMD:gotopasar(playerid, params[])
{
    new id;
    if (CheckAdmin(playerid, 5))
        return PermissionError(playerid);
    
    if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotopasar [id]");
    if(!Iter_Contains(PASAR, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Pasar tersebut tidak ada!");

    SetPlayerPos(playerid, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2]);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Teleportasi ke Dynamic Pasar ID: %d", GetAdminName(playerid), id);
    AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(!IsPlayerConnected(playerid)) return false;
        foreach(new id : PASAR)
        {
            if(IsPlayerInRangeOfPoint(playerid, 2.0, PasarData[id][pasarPos][0], PasarData[id][pasarPos][1], PasarData[id][pasarPos][2]))
            {
                if(PasarData[id][pasarType] == 1)
                {
                    new total = Inventory_Count(playerid, "Susu Olahan");
                    new valuepay = total*SusuOlahPrice;
                    if(!PlayerHasItem(playerid, "Susu Olahan")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Susu Olahan!");

                    Inventory_Remove(playerid, "Susu Olahan", total);
                    GiveMoney(playerid, valuepay);
                    ShowItemBox(playerid, sprintf("REMOVED %dx", total), "SUSU OLAHAN", 19570);
                    ShowItemBox(playerid, sprintf("ADDED %dx", valuepay), "UANG", 1212);
                }
                else if(PasarData[id][pasarType] == 2)
                {
                    Dialog_Show(playerid, Pasar_HasilTambang, DIALOG_STYLE_TABLIST, ""TCRP"District  "WHITE"- Jual Hasil Tambang",
                    "Besi\t"GREEN"%s"ARWIN1"/pcs\
                    \n"GRAY"Tembaga\t"GREEN"%s"ARWIN1"/pcs\
                    \nEmas\t"GREEN"%s"ARWIN1"/pcs\
                    \n"GRAY"Berlian\t"GREEN"%s"ARWIN1"/pcs\
                    \nMaterial\t"GREEN"%s"ARWIN1"/pcs", "Pilih", "Batal", FormatMoney(BesiPrice), FormatMoney(TembagaPrice), FormatMoney(EmasPrice), FormatMoney(BerlianPrice), FormatMoney(MaterialPrice));
                }
                else if(PasarData[id][pasarType] == 3)
                {
                    new total = Inventory_Count(playerid, "Kayu Kemas");
                    new valuepay = total*KayuKemasPrice;
                    if(!PlayerHasItem(playerid, "Kayu Kemas")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Kayu Kemasan!");

                    Inventory_Remove(playerid, "Kayu Kemas", total);
                    GiveMoney(playerid, valuepay);
                    ShowItemBox(playerid, sprintf("REMOVED %dx", total), "KAYU KEMAS", 2912);
                    ShowItemBox(playerid, sprintf("ADDED %dx", valuepay), "UANG", 1212);
                }
                else if(PasarData[id][pasarType] == 4)
                {
                    new total = Inventory_Count(playerid, "Ayam Kemas");
                    new valuepay = total*AyamKemasPrice;
                    if(!PlayerHasItem(playerid, "Ayam Kemas")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Ayam Kemas!");

                    Inventory_Remove(playerid, "Ayam Kemas", total);
                    GiveMoney(playerid, valuepay);
                    ShowItemBox(playerid, sprintf("REMOVED %dx", total), "AYAM KEMAS", 2768);
                    ShowItemBox(playerid, sprintf("ADDED $%d", valuepay), "UANG", 1212);
                }
                else if(PasarData[id][pasarType] == 5)
                {
                    Dialog_Show(playerid, Pasar_HasilDaur, DIALOG_STYLE_TABLIST, ""TCRP"District  "WHITE"- Jual Hasil Recycler",
                    "Baja\t"GREEN"%s"ARWIN1"/pcs\
                    \n"GRAY"Kaca\t"GREEN"%s"ARWIN1"/pcs\
                    \nKaret\t"GREEN"%s"ARWIN1"/pcs\
                    \n"GRAY"Alumunium\t"GREEN"%s"ARWIN1"/pcs", "Pilih", "Batal", FormatMoney(BajaPrice), FormatMoney(KacaPrice), FormatMoney(KaretPrice), FormatMoney(AlumuniumPrice));
                }
                else if(PasarData[id][pasarType] == 7)
                {
                    new total = Inventory_Count(playerid, "Pakaian");
                    new valuepay = total*PakaianPrice;
                    if(!PlayerHasItem(playerid, "Pakaian")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Pakaian!");

                    Inventory_Remove(playerid, "Pakaian", total);
                    GiveMoney(playerid, valuepay);
                    ShowItemBox(playerid, sprintf("REMOVED %dx", total), "PAKAIAN", 2399);
                    ShowItemBox(playerid, sprintf("ADDED $%d", valuepay), "UANG", 1212);
                }
                else if(PasarData[id][pasarType] == 8)
                {
                    new total = Inventory_Count(playerid, "GAS");
                    new hasil = total*GasPrice;
                    if(!PlayerHasItem(playerid, "GAS")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki GAS!");

                    Inventory_Remove(playerid, "GAS", total);
                    GiveMoney(playerid, hasil);
                    ShowItemBox(playerid, sprintf("Removed %dx", total), "GAS", 1650);
                    ShowItemBox(playerid, sprintf("Received %dx", hasil), "UANG", 1212);
                }
                else if(PasarData[id][pasarType] == 9)
                {
                    new total = Inventory_Count(playerid, "Ikan");
                    new hasil = total*8;
                    if(!PlayerHasItem(playerid, "Ikan")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Ikan!");

                    Inventory_Remove(playerid, "Ikan", total);
                    GiveMoney(playerid, hasil);
                    ShowItemBox(playerid, sprintf("Removed %dx", total), "Ikan", 19630);
                    ShowItemBox(playerid, sprintf("Received %s", FormatMoney(hasil)), "Uang", 1212);
                }
            }
        }
    }
    return 1;
}

Dialog:Pasar_HasilDaur(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    switch(listitem)
    {
        case 0://Baja
        {
            new total = Inventory_Count(playerid, "Baja");
            new value = total*BajaPrice;
            if(!PlayerHasItem(playerid, "Baja")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Baja!");

            Inventory_Remove(playerid, "Baja", total);
            GiveMoney(playerid, value);
            ShowItemBox(playerid, sprintf("REMOVED %dx", total), "BAJA", 19772);
            ShowItemBox(playerid, sprintf("ADDED $%d", value), "UANG", 1212);
        }
        case 1://Kaca
        {
            new total = Inventory_Count(playerid, "Kaca");
            new value = total*KacaPrice;
            if(!PlayerHasItem(playerid, "Kaca")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Kaca!");

            Inventory_Remove(playerid, "Kaca", total);
            GiveMoney(playerid, value);
            ShowItemBox(playerid, sprintf("REMOVED %dx", total), "KACA", 1649);
            ShowItemBox(playerid, sprintf("ADDED $%d", value), "UANG", 1212);
        }
        case 2://Karet
        {
            new total = Inventory_Count(playerid, "Karet");
            new value = total*KaretPrice;
            if(!PlayerHasItem(playerid, "Karet")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Karet!");

            Inventory_Remove(playerid, "Karet", total);
            GiveMoney(playerid, value);
            ShowItemBox(playerid, sprintf("REMOVED %dx", total), "KARET", 1316);
            ShowItemBox(playerid, sprintf("ADDED $%d", value), "UANG", 1212);
        }
        case 3://alumunium
        {
            new total = Inventory_Count(playerid, "Alumunium");
            new valuepay = total*AlumuniumPrice;
            if(!PlayerHasItem(playerid, "Alumunium")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Alumunium!");

            Inventory_Remove(playerid, "Alumunium", total);
            GiveMoney(playerid, valuepay);
            ShowItemBox(playerid, sprintf("REMOVED %dx", total), "ALUMUNIUM", 2937);
            ShowItemBox(playerid, sprintf("ADDED $%d", valuepay), "UANG", 1212);
        }
    }
    return 1;
}

Dialog:Pasar_HasilTambang(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    switch(listitem)
    {
        case 0://Besi
        {
            new total = Inventory_Count(playerid, "Besi");
            new valuepay = total*BesiPrice;
            if(!PlayerHasItem(playerid, "Besi")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Besi!");

            Inventory_Remove(playerid, "Besi", total);
            GiveMoney(playerid, valuepay);
            ShowItemBox(playerid, sprintf("REMOVED %dx", total), "BESI", 19809);
            ShowItemBox(playerid, sprintf("ADDED $%d", valuepay), "UANG", 1212); 
        }
        case 1://Tembaga
        {
            new total = Inventory_Count(playerid, "Tembaga");
            new valuepay = total*TembagaPrice;
            if(!PlayerHasItem(playerid, "Tembaga")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Tembaga!");

            Inventory_Remove(playerid, "Tembaga", total);
            GiveMoney(playerid, valuepay);
            ShowItemBox(playerid, sprintf("REMOVED %dx", total), "TEMBAGA", 11748);
            ShowItemBox(playerid, sprintf("ADDED $%d", valuepay), "UANG", 1212); 
        }
        case 2://Emas
        {
            new total = Inventory_Count(playerid, "Emas");
            new valuepay = total*EmasPrice;
            if(!PlayerHasItem(playerid, "Emas")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Emas!");

            Inventory_Remove(playerid, "Emas", total);
            GiveMoney(playerid, valuepay);
            ShowItemBox(playerid, sprintf("REMOVED %dx", total), "EMAS", 19941);
            ShowItemBox(playerid, sprintf("ADDED $%d", valuepay), "UANG", 1212); 
        }
        case 3://Berlian
        {
            new total = Inventory_Count(playerid, "Berlian");
            new valuepay = total*BerlianPrice;
            if(!PlayerHasItem(playerid, "Berlian")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Berlian!");

            Inventory_Remove(playerid, "Berlian", total);
            GiveMoney(playerid, valuepay);
            ShowItemBox(playerid, sprintf("REMOVED %dx", total), "BERLIAN", 19941);
            ShowItemBox(playerid, sprintf("ADDED $%d", valuepay), "UANG", 1212); 
        }
        case 4://Material
        {
            new total = Inventory_Count(playerid, "Material");
            new valuepay = total*MaterialPrice;
            if(!PlayerHasItem(playerid, "Material")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Material!");

            Inventory_Remove(playerid, "Material", total);
            GiveMoney(playerid, valuepay);
            ShowItemBox(playerid, sprintf("REMOVED %dx", total), "MATERIAL", 19843);
            ShowItemBox(playerid, sprintf("ADDED $%d", valuepay), "UANG", 1212);
        }
    }
    return 1;
}