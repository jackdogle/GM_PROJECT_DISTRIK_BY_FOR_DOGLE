#include <YSI\y_hooks>
#define MAX_DYNAMIC_GUDANG  50

enum  e_gudang
{
    gudangName[100],
    Float: gudangPOS[3],
    gudangInterior,
    gudangWorld,
    gudangPrice,

    STREAMER_TAG_MAP_ICON:gudangIcon,
    STREAMER_TAG_PICKUP:gudangPickup,
    STREAMER_TAG_3D_TEXT_LABEL:gudangLabel
};
new GudangData[MAX_DYNAMIC_GUDANG][e_gudang],
    Iterator:Gudang<MAX_DYNAMIC_GUDANG>;

Gudang_Refresh(id)
{
    if(id != -1)
    {
        if(IsValidDynamicPickup(GudangData[id][gudangPickup]))
            DestroyDynamicPickup(GudangData[id][gudangPickup]);
        
        if(IsValidDynamic3DTextLabel(GudangData[id][gudangLabel]))
            DestroyDynamic3DTextLabel(GudangData[id][gudangLabel]);
        
        if(IsValidDynamicMapIcon(GudangData[id][gudangIcon]))
            DestroyDynamicMapIcon(GudangData[id][gudangIcon]);

        if(GudangData[id][gudangPOS][0] != 0.0 || GudangData[id][gudangPOS][1] != 0.0 || GudangData[id][gudangPOS][2] != 0.0)
        {
            static frmtname[128];

            format(frmtname, sizeof(frmtname), "| Gudang %s |\n[Tekan "GREEN"Y"WHITE" untuk akses gudang]", GudangData[id][gudangName]);
            GudangData[id][gudangLabel] = CreateDynamic3DTextLabel(frmtname, -1, GudangData[id][gudangPOS][0], GudangData[id][gudangPOS][1], GudangData[id][gudangPOS][2] + 1.2, 4.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
            GudangData[id][gudangIcon] = CreateDynamicMapIcon(GudangData[id][gudangPOS][0], GudangData[id][gudangPOS][1], GudangData[id][gudangPOS][2], 16, -1, -1, -1, -1, 1000.0, MAPICON_GLOBAL, -1, 1);
            GudangData[id][gudangPickup] = CreateDynamicPickup(19134, 23, GudangData[id][gudangPOS][0], GudangData[id][gudangPOS][1], GudangData[id][gudangPOS][2], GudangData[id][gudangWorld], GudangData[id][gudangInterior], -1, 4.0, -1, 0);
        }
    }
    return 1;
}

GudangNearest(playerid)
{
    foreach(new i : Gudang) if(IsPlayerInRangeOfPoint(playerid, 2.0, GudangData[i][gudangPOS][0], GudangData[i][gudangPOS][1], GudangData[i][gudangPOS][2]))
    {
        return i;
    }
    return -1;
}

forward LoadGudang();
public LoadGudang()
{
    new id, rows = cache_num_rows();

    new Cache:GdgCache;

    if(rows)
    {
        GdgCache = cache_save();

        for(new i = 0; i < rows; i ++)
        {
            cache_get_value_name_int(i, "GudangID", id);
            cache_get_value_name(i, "GudangName", GudangData[id][gudangName]);

            cache_get_value_name_int(i, "GudangPrice", GudangData[id][gudangPrice]);
            cache_get_value_name_float(i, "GudangX", GudangData[id][gudangPOS][0]);
            cache_get_value_name_float(i, "GudangY", GudangData[id][gudangPOS][1]);
            cache_get_value_name_float(i, "GudangZ", GudangData[id][gudangPOS][2]);
            
            cache_get_value_name_int(i, "GudangInterior", GudangData[id][gudangInterior]);
            cache_get_value_name_int(i, "GudangWorld", GudangData[id][gudangWorld]);

            Gudang_Refresh(id);
            Iter_Add(Gudang, id);
        }
        printf("[Dynamic Gudang]: Jumlah total Gudang yang dimuat: %d", rows);

        if(cache_is_valid(GdgCache))
        {
            cache_delete(GdgCache);
            printf("[Dynamic Gudang]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Gudang]: Cache tidak valid atau sudah dihapus.");
        }
    }
    return 1;
}

GudangSave(id)
{
    new shstr[596];
    format(shstr, sizeof(shstr), "UPDATE `gudang` SET `GudangName`='%s', `GudangPrice`=%d, `GudangX`=%f, `GudangY`=%f, `GudangZ`=%f, `GudangInterior`=%d, `GudangWorld`=%f WHERE `GudangID`=%d",
    GudangData[id][gudangName], GudangData[id][gudangPrice], GudangData[id][gudangPOS][0], GudangData[id][gudangPOS][1], GudangData[id][gudangPOS][2], GudangData[id][gudangInterior], GudangData[id][gudangWorld], id);
    return mysql_tquery(g_SQL, shstr);
}

CMD:addgudang(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    new id = Iter_Free(Gudang),
        frmtname[125],
        price,
        Float:X,
        Float:Y,
        Float:Z;
    
    if(sscanf(params, "ds[125]", price, frmtname)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addgudang [harga 30 hari] [nama gudang]");
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menambah gudang lagi!");
    
    GetPlayerPos(playerid, X, Y, Z);

    strunpack(GudangData[id][gudangName], frmtname);
    GudangData[id][gudangPOS][0] = X;
    GudangData[id][gudangPOS][1] = Y;
    GudangData[id][gudangPOS][2] = Z;
    GudangData[id][gudangInterior] = GetPlayerInterior(playerid);
    GudangData[id][gudangWorld] = GetPlayerVirtualWorld(playerid);
    GudangData[id][gudangPrice] = price;

    Gudang_Refresh(id);
    Iter_Add(Gudang, id);
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" membuat Dynamic Gudang ID: %d.", GetAdminName(playerid), id);

    new tss[596];
    mysql_format(g_SQL, tss, sizeof(tss), "INSERT INTO `gudang` SET `GudangID`=%d, `GudangName`='%s', `GudangPrice`=%d, `GudangX`=%f, `GudangY`=%f, `GudangZ`=%f, `GudangInterior`=%d, `GudangWorld`=%d",
    id, GudangData[id][gudangName], GudangData[id][gudangPrice], GudangData[id][gudangPOS][0], GudangData[id][gudangPOS][1], GudangData[id][gudangPOS][2], GudangData[id][gudangInterior], GudangData[id][gudangWorld]);
    mysql_tquery(g_SQL, tss, "OnGudangCreated", "dd", playerid, id);
    return 1;
}

CMD:editgudang(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    static
        id,
        type[24],
        frmtx[128];
    
    if(sscanf(params, "ds[24]S()[128]", id, type, frmtx)) return Syntax(playerid, "/editgudang [id] [entinity] (price, location)");
    if(id < 0 || id >= MAX_DYNAMIC_GUDANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Gudang tidak valid!");
    if(!Iter_Contains(Gudang, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Gudang tidak ada!");
    
    if(!strcmp(type, "price", true))
    {
        new price;
        if(sscanf(frmtx, "d", price)) return Syntax(playerid, "/editgudang [id] [price] [new price]");

        GudangData[id][gudangPrice] = price;
        Gudang_Refresh(id);
        GudangSave(id);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengubah harga Gudang ID %d menjadi "DARKGREEN"%s", AccountData[playerid][pAdminname], id, FormatMoney(price));
    } 
    else if(!strcmp(type, "name", true))
    {
        new oldname[32], gname[32];
        if(sscanf(frmtx, "s[32]", gname)) return Syntax(playerid, "/editgudang [id] [name] [new name]");
        if(strlen(gname) < 1) return Error(playerid, "Nama tidak dapat di kosongkan!");

        format(oldname, 32, GudangData[id][gudangName]);
        format(GudangData[id][gudangName], 32, gname);
        Gudang_Refresh(id);
        GudangSave(id);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengubah Nama Gudang ID %d "YELLOW"%s ~> %s", AccountData[playerid][pAdminname], id, oldname, gname);
    }
    else if(!strcmp(type, "location", true))
    {
        static Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);

        GudangData[id][gudangPOS][0] = x;
        GudangData[id][gudangPOS][1] = y;
        GudangData[id][gudangPOS][2] = z;
        Gudang_Refresh(id);
        GudangSave(id);
        SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengubah lokasi Gudang ID %d ke X:%.2f Y:%.2f Z:%.2f", AccountData[playerid][pAdminname], id, x, y, z);
    }
    return 1;
}

CMD:removegudang(playerid, params[])
{
	if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

	new id, icsr[255];
	if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/removegudang [id gudang]");
	if(!Iter_Contains(Gudang, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Gudang tidak ada!");
	if(id < 0 || id > MAX_DYNAMIC_GUDANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Gudang tidak valid!");

	GudangData[id][gudangPOS][0] = GudangData[id][gudangPOS][1] = GudangData[id][gudangPOS][2] = 0.0;
	GudangData[id][gudangInterior] = GudangData[id][gudangWorld] = GudangData[id][gudangPrice] = 0;

	Gudang_Refresh(id);
	Iter_Remove(Gudang, id);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menghapus Dynamic Gudang ID: %d", GetAdminName(playerid), id);

	mysql_format(g_SQL, icsr, sizeof(icsr), "DELETE FROM `gudang` WHERE `GudangID` = %d", id);
	mysql_tquery(g_SQL, icsr);
	return 1;
}

CMD:gotogudang(playerid, params[])
{
	if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

	new id;
	if(sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/gotogudang [id]");
	if(!Iter_Contains(Gudang, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Gudang tidak ada!");
	if(id < 0 || id > MAX_DYNAMIC_GUDANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Gudang tidak valid!");

	SetPlayerPos(playerid, GudangData[id][gudangPOS][0], GudangData[id][gudangPOS][1], GudangData[id][gudangPOS][2]);
	SetPlayerInterior(playerid, GudangData[id][gudangInterior]);
	SetPlayerVirtualWorld(playerid, GudangData[id][gudangWorld]);
	AccountData[playerid][pInDoor] = -1;
    AccountData[playerid][pInHouse] = -1;
    AccountData[playerid][pInBiz] = -1;
    AccountData[playerid][pInFamily] = -1;
    AccountData[playerid][pInRusun] = -1;
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" teleportasi ke Gudang ID: %d.", GetAdminName(playerid), id);
	return 1;
}

forward OnGudangCreated(playerid, id);
public OnGudangCreated(playerid, id)
{
	ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Gudang %s berhasil dibuat", GudangData[id][gudangName]));
    GudangSave(id);
	return 1;
}

/* Hooks */
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        new id = GudangNearest(playerid);
        if(id > -1)
        {
            if(IsPlayerInRangeOfPoint(playerid, 2.0, GudangData[id][gudangPOS][0], GudangData[id][gudangPOS][1], GudangData[id][gudangPOS][2]))
            {
                if(AccountData[playerid][pHasGudangID] == id)
                {
                    AccountData[playerid][pTempValue] = id;
                    AccountData[playerid][menuShowed] = true;
                    ShowPlayerDialog(playerid, DIALOG_GUDANG_OPTION, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Gudang",
                    "Buka Gudang\n"GRAY"Berhenti menyewa gudang\nCek status sewa", "Pilih", "Batal");
                }
                /*else 
                {
                    static shstr[255];
                    format(shstr, sizeof(shstr), "Sewa\t"GREEN"%s / bulan", FormatMoney(GudangData[id][gudangPrice]));

                    AccountData[playerid][pTempValue] = id;
                    ShowPlayerDialog(playerid, DIALOG_GUDANG_BUY, DIALOG_STYLE_LIST, sprintf(""TCRP"District  "WHITE"- Gudang %s", GudangData[id][gudangName]),
                    shstr, "Pilih", "Batal");
                }*/
            }
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(dialogid == DIALOG_GUDANG_BUY)
    {
        if(!response)
        {
            AccountData[playerid][pTempValue] = -1;
            return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        }

        // Cari ID gudang berdasarkan index listitem
        new idx = 0, id;
        for(id = 0; id < MAX_DYNAMIC_GUDANG; id++)
        {
            if(!Iter_Contains(Gudang, id)) continue;

            if(idx == listitem)
            {
                AccountData[playerid][pTempValue] = id;
                break;
            }
            idx++;
        }

        if(AccountData[playerid][pTempValue] == -1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Gudang tidak valid!");

        if(AccountData[playerid][pHasGudangID] != -1)
        {
            AccountData[playerid][pTempValue] = -1;
            return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda sudah menyewa di Gudang %s", GudangData[AccountData[playerid][pHasGudangID]][gudangName]));
        }

        // Proses sewa
        id = AccountData[playerid][pTempValue];
        if(AccountData[playerid][pMoney] < GudangData[id][gudangPrice])
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");

        TakeMoney(playerid, GudangData[id][gudangPrice]);
        AccountData[playerid][pHasGudangID] = id;
        AccountData[playerid][pGudangRentTime] = gettime() + (3600 * 24 * 30); // 30 hari

        ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyewa gudang selama 30 hari");

        new query[256];
        mysql_format(g_SQL, query, sizeof(query), "UPDATE player_characters SET Char_HasGudangID=%d WHERE pID=%d", id, AccountData[playerid][pID]);
        mysql_tquery(g_SQL, query);

        AccountData[playerid][pTempValue] = -1;
    }
    else if(dialogid == DIALOG_GUDANG_OPTION)
    {
        if(!response)
        {
            AccountData[playerid][pTempValue] = -1;
            AccountData[playerid][menuShowed] = false;
            return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        }

        if(AccountData[playerid][pTempValue] == -1)
        {
            AccountData[playerid][menuShowed] = false;
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang akses Gudang!");
        }
        if(AccountData[playerid][pHasGudangID] == -1) 
        {
            AccountData[playerid][menuShowed] = false;
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki gudang!"); 
        }

        switch(listitem)
        {
            case 0:// Buka gudang
            {
                AccountData[playerid][menuShowed] = true;
                ShowPlayerDialog(playerid, DIALOG_GUDANGVAULT, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Gudang",
                "Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Batal");
            }
            case 1: //berhenti sewa
            {
                Dialog_Show(playerid, GUDANG_STOPCONF, DIALOG_STYLE_MSGBOX, ""TCRP"District ", 
                "Anda yakin ingin berhenti menyewa gudang?\nBarang barang anda akan tersimpan aman. Tidak akan hilang", "Iya", "Tidak");
            }
            case 2: //status sewa
            {
                new currentTime = AccountData[playerid][pGudangRentTime] - gettime();
                new days = currentTime / 86400;
                new hours = (currentTime % 86400) / 3600;
                new minutes = (currentTime % 3600) / 60;

                new shstr[258];
                format(shstr, sizeof(shstr), "Anda memiliki durasi sewa gudang ini selama\
                \n"WHITE"%d hari %d jam %d menit", days, hours, minutes);
                
                new gdid = GudangNearest(playerid);
                if(gdid != -1)
                {
                    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, sprintf(""TCRP"District  "WHITE"- %s", GudangData[gdid][gudangName]),
                    shstr, "Tutup", "");
                }
            }
        }
    }
    else if(dialogid == DIALOG_GUDANGVAULT)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan"), AccountData[playerid][menuShowed] = false;
        if(AccountData[playerid][pHasGudangID] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki gudang!"), AccountData[playerid][menuShowed] = false;
        switch(listitem)
        {
            case 0: //deposit
            {
                GudangBrankas[playerid][gudangBrankasID] = 0;
                GudangBrankas[playerid][gudangBrankasTemp] = EOS;
                GudangBrankas[playerid][gudangBrankasModel] = 0;
                GudangBrankas[playerid][gudangBrankasQuant] = 0;

                new str[1218], amounts, itemname[64], tss[125], Cache:execute;
                format(str, sizeof(str), "Nama Item\tJumlah\tBerat (%.3f/500kg)\n", AccountData[playerid][pGudangCapacity]);
                mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
                execute = mysql_query(g_SQL, tss, true);
                new rows = cache_num_rows();
                if(rows)
                {
                    for(new x; x < rows; ++x)
                    {
                        cache_get_value_name(x, "invItem", itemname);
                        cache_get_value_name_int(x, "invQuantity", amounts);

                        format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                    }
                    ShowPlayerDialog(playerid, DIALOG_GUDANGVAULT_DEPOSIT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Gudang", str, "Pilih", "Batal");
                }
                else
                {
                    PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Gudang",
                    "Anda tidak memiliki barang untuk disimpan!", "Tutup", "");
                }
                cache_delete(execute);
            }
            case 1: //withdraw
            {
                new shstr[1218], amounts, itemname[64], jss[255], Cache:execute;
                format(shstr, sizeof(shstr), "Nama Item\tJumlah\tBerat (%.3f/500kg)\n", AccountData[playerid][pGudangCapacity]);
                mysql_format(g_SQL, jss, sizeof(jss), "SELECT * FROM `player_gudang` WHERE `ID`=%d", AccountData[playerid][pID]);
                execute = mysql_query(g_SQL, jss, true);
                if(cache_num_rows() > 0)
                {
                    for(new x; x < cache_num_rows(); ++x)
                    {
                        cache_get_value_name(x, "itemName", itemname);
                        cache_get_value_name_int(x, "itemQuantity", amounts);

                        format(shstr, sizeof(shstr), "%s%s\t%d\t-\n", shstr, itemname, amounts);
                    }
                    ShowPlayerDialog(playerid, DIALOG_GUDANGVAULT_WITHDRAW, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Gudang", shstr, "Pilih", "Batal");
                }
                else 
                {
                    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Gudang",
                    "Tidak ada barang di gudang saat ini!", "Tutup", "");
                }
                cache_delete(execute);
            }
        }
    }
    else if(dialogid == DIALOG_GUDANGVAULT_DEPOSIT)
    {
        if(!response)
        {
            GudangLastUse[playerid] = 0;
            AccountData[playerid][menuShowed] = false;
            return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        }

        if(listitem == -1)
        {
            GudangLastUse[playerid] = 0;
            AccountData[playerid][menuShowed] = false;
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih barang!");
        }

        new tss[125], Cache:execute;
        mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
        execute = mysql_query(g_SQL, tss, true);
        if(cache_num_rows() > 0)
        {
            cache_get_value_name(listitem, "invItem", GudangBrankas[playerid][gudangBrankasTemp]);
            cache_get_value_name_int(listitem, "invModel", GudangBrankas[playerid][gudangBrankasModel]);
            cache_get_value_name_int(listitem, "invQuantity", GudangBrankas[playerid][gudangBrankasQuant]);

            new shstr[526];
            format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon masukkan berapa jumlah item yang ingin disimpan:", GudangBrankas[playerid][gudangBrankasTemp], GudangBrankas[playerid][gudangBrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_GUDANGVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gudang", shstr, "Input", "Batal");
        }
        cache_delete(execute);
    }
    else if(dialogid == DIALOG_GUDANGVAULT_IN)
    {
        if(GetTickCount() - GudangLastUse[playerid] < 2000)
        {
            AccountData[playerid][menuShowed] = false;
            ShowTDN(playerid, NOTIFICATION_ERROR, "mohon tunggu sebentar!");
            return 1;
        }
        GudangLastUse[playerid] = GetTickCount();

        if(!response)
        {
            GudangLastUse[playerid] = 0;
            AccountData[playerid][menuShowed] = false;
            return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        }

        new shstr[526];
        if(isnull(inputtext))
        {
            AccountData[playerid][menuShowed] = true;
            format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nTidak dapat diisi kosong!\nMohon masukkan berapa jumlah item yang ingin disimpan:", GudangBrankas[playerid][gudangBrankasTemp], GudangBrankas[playerid][gudangBrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_GUDANGVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gudang", 
            shstr, "Input", "Batal");
            return 1;
        }

        if(!IsNumeric(inputtext))
        {
            AccountData[playerid][menuShowed] = true;
            format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah item yang ingin disimpan:", GudangBrankas[playerid][gudangBrankasTemp], GudangBrankas[playerid][gudangBrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_GUDANGVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gudang", 
            shstr, "Input", "Batal");
            return 1;
        }

        if(strval(inputtext) < 1 || strval(inputtext) > GudangBrankas[playerid][gudangBrankasQuant])
        {
            AccountData[playerid][menuShowed] = true;
            format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah item yang ingin disimpan:", GudangBrankas[playerid][gudangBrankasTemp], GudangBrankas[playerid][gudangBrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_GUDANGVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gudang", 
            shstr, "Input", "Batal");
            return 1;
        }
        if(GetTotalWeightGudang(playerid) >= 500) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kapasitas gudang anda telah penuh!"), AccountData[playerid][menuShowed] = false;

        new quantity = strval(inputtext);
        AddCapacityGudang(playerid, GudangBrankas[playerid][gudangBrankasTemp], quantity);
        Inventory_Remove(playerid, GudangBrankas[playerid][gudangBrankasTemp], quantity);
        ShowItemBox(playerid, sprintf("Removed %dx", quantity), GudangBrankas[playerid][gudangBrankasTemp], GudangBrankas[playerid][gudangBrankasModel]);

        new invstr[1028];
        mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `player_gudang` WHERE `ID`=%d AND `itemName`='%s'", AccountData[playerid][pID], GudangBrankas[playerid][gudangBrankasTemp]);
        mysql_query(g_SQL, shstr);
        if(cache_num_rows() > 0)
        {
            mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `player_gudang` SET `itemQuantity` = `itemQuantity` + %d WHERE `ID`=%d AND `itemName`='%s'", quantity, AccountData[playerid][pID], GudangBrankas[playerid][gudangBrankasTemp]);
            mysql_tquery(g_SQL, invstr, "OnGudangDeposit", "d", playerid);
        }
        else 
        {
            mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `player_gudang` SET `ID`=%d, `itemName`='%s', `itemModel`=%d, `itemQuantity`=%d", AccountData[playerid][pID], GudangBrankas[playerid][gudangBrankasTemp], GudangBrankas[playerid][gudangBrankasModel], quantity);
            mysql_tquery(g_SQL, invstr, "OnGudangDeposit", "d", playerid);
        }
    }
    else if(dialogid == DIALOG_GUDANGVAULT_WITHDRAW)
    {
        if(!response)
        {
            AccountData[playerid][menuShowed] = false;
            return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        }

        if(listitem == -1)
        {
            AccountData[playerid][menuShowed] = false;
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih item!");
        }

        new shstr[1218], tss[255], Cache:execute;
        mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `player_gudang` WHERE `ID`=%d", AccountData[playerid][pID]);
        execute = mysql_query(g_SQL, tss, true);
        if(cache_num_rows() > 0)
        {
            cache_get_value_name_int(listitem, "itemID", GudangBrankas[playerid][gudangBrankasID]);
            cache_get_value_name(listitem, "itemName", GudangBrankas[playerid][gudangBrankasTemp]);
            cache_get_value_name_int(listitem, "itemModel", GudangBrankas[playerid][gudangBrankasModel]);
            cache_get_value_name_int(listitem, "itemQuantity", GudangBrankas[playerid][gudangBrankasQuant]);

            format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di gudang: %d\nMohon masukkan berapa jumlah yang ingin anda ambil:", GudangBrankas[playerid][gudangBrankasTemp], GudangBrankas[playerid][gudangBrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_GUDANGVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gudang",
            shstr, "Input", "Batal");
        }
        cache_delete(execute);
    }
    else if(dialogid == DIALOG_GUDANGVAULT_OUT)
    {
        if(!response)
        {
            AccountData[playerid][menuShowed] = false;
            return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        }

        new shstr[512];
        if(isnull(inputtext))
        {
            AccountData[playerid][menuShowed] = true;
            format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di gudang: %d\nTidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin anda ambil:", GudangBrankas[playerid][gudangBrankasTemp], GudangBrankas[playerid][gudangBrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_GUDANGVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gudang",
            shstr, "Input", "Batal");
            return 1;
        }

        if(!IsNumeric(inputtext))
        {
            AccountData[playerid][menuShowed] = true;
            format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di gudang: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin anda ambil:", GudangBrankas[playerid][gudangBrankasTemp], GudangBrankas[playerid][gudangBrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_GUDANGVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gudang",
            shstr, "Input", "Batal");
            return 1;
        }

        if(strval(inputtext) < 1 || strval(inputtext) > GudangBrankas[playerid][gudangBrankasQuant])
        {
            AccountData[playerid][menuShowed] = true;
            format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di gudang: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin anda ambil:", GudangBrankas[playerid][gudangBrankasTemp], GudangBrankas[playerid][gudangBrankasQuant]);
            ShowPlayerDialog(playerid, DIALOG_GUDANGVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gudang",
            shstr, "Input", "Batal");
            return 1;
        }

        new quantity = strval(inputtext), jts[255];

        if(GetTotalWeightFloat(playerid) >= 50) 
        {
            AccountData[playerid][menuShowed] = false;
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
        }

        GudangBrankas[playerid][gudangBrankasQuant] -= quantity;
        if(GudangBrankas[playerid][gudangBrankasQuant] > 0)
        {
            mysql_format(g_SQL, jts, sizeof(jts), "UPDATE `player_gudang` SET `itemQuantity`=%d WHERE `itemID`=%d", GudangBrankas[playerid][gudangBrankasQuant], GudangBrankas[playerid][gudangBrankasID]);
            mysql_tquery(g_SQL, jts);
        }
        else
        {
            mysql_format(g_SQL, jts, sizeof(jts), "DELETE FROM `player_gudang` WHERE `itemID`=%d", GudangBrankas[playerid][gudangBrankasID]);
            mysql_tquery(g_SQL, jts);
        }
        Inventory_Add(playerid, GudangBrankas[playerid][gudangBrankasTemp], GudangBrankas[playerid][gudangBrankasModel], quantity);
        ReduceCapacityGudang(playerid, GudangBrankas[playerid][gudangBrankasTemp], quantity);
        ShowItemBox(playerid, sprintf("Received %dx", quantity), GudangBrankas[playerid][gudangBrankasTemp], GudangBrankas[playerid][gudangBrankasModel]);

        GudangBrankas[playerid][gudangBrankasID] = 0;
        GudangBrankas[playerid][gudangBrankasTemp] = EOS;
        GudangBrankas[playerid][gudangBrankasModel] = 0;
        GudangBrankas[playerid][gudangBrankasQuant] = 0;
        AccountData[playerid][menuShowed] = false;
    }
    return 1;
}

Dialog:GUDANG_STOPCONF(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        AccountData[playerid][pHasGudangID] = -1;
        AccountData[playerid][pGudangRentTime] = 0;
        AccountData[playerid][pTempValue] = -1;
        AccountData[playerid][menuShowed] = false;

        ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil berhenti sewa gudang!");

        new tss[255];
        mysql_format(g_SQL, tss, sizeof(tss), "UPDATE `player_characters` SET `Char_HasGudangID`=-1, `Char_GudangRentTime`=0 WHERE `pID`=%d", AccountData[playerid][pID]);
        mysql_tquery(g_SQL, tss);
    }
    else
    {
        return ShowPlayerDialog(playerid, DIALOG_GUDANG_OPTION, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Gudang",
        "Buka Gudang\n"GRAY"Berhenti menyewa gudang\nCek status sewa", "Pilih", "Batal");
    }
    return 1;
}

forward OnGudangDeposit(playerid);
public OnGudangDeposit(playerid)
{
    AccountData[playerid][menuShowed] = false;
    ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil menyimpan barang");
    GudangBrankas[playerid][gudangBrankasID] = 0;
    GudangBrankas[playerid][gudangBrankasTemp] = EOS;
    GudangBrankas[playerid][gudangBrankasModel] = 0;
    GudangBrankas[playerid][gudangBrankasQuant] = 0;
    return 1;
}

AddCapacityGudang(playerid, const item[], quantity)
{
    if(!strcmp(item, "Nasi Goreng"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Kopi Kenangan"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Batu Kotor"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.030;
    }
    else if(!strcmp(item, "Nasi Uduk"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Kanabis"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Batu Bersih"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.030;
    }
    else if(!strcmp(item, "Air Mineral"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Besi"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Tembaga"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Berlian"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.25;
    }
    else if(!strcmp(item, "Emas"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.10;
    }
    else if(!strcmp(item, "Gold"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.10;
    }
    else if(!strcmp(item, "Smartphone"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.25;
    }
    else if(!strcmp(item, "Radio"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.15;
    }
    else if(!strcmp(item, "Kayu"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.06;
    }
    else if(!strcmp(item, "Kayu Potongan"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Kayu Kemas"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.08;
    }
    else if(!strcmp(item, "Marijuana"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Benang"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Kain"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.04;
    }
    else if(!strcmp(item, "Pakaian"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.04;
    }
    else if(!strcmp(item, "Bandage"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Medkit"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Alprazolam"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Ayam Hidup"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.15;
    }
    else if(!strcmp(item, "Ayam Potong"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.10;
    }
    else if(!strcmp(item, "Ayam Kemas"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Sampah Makanan"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.005;
    }
    else if(!strcmp(item, "Kevlar"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.90;
    }
    else if(!strcmp(item, "Botol"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Petrol"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.50;
    }
    else if(!strcmp(item, "Pure Oil"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.50;
    }
    else if(!strcmp(item, "GAS"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.60;
    }
    else if(!strcmp(item, "Ikan"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Rokok"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Pancingan"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.08;
    }
    else if(!strcmp(item, "Umpan"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Hiu"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.90;
    }
    else if(!strcmp(item, "Penyu"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.80;
    }
    else if(!strcmp(item, "Ikan Tawar"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.03;
    }
    else if(!strcmp(item, "Jerigen"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.25;
    }
    else if(!strcmp(item, "Tools Kit"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.30;
    }
    else if(!strcmp(item, "Repair Kit"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.35;
    }
    else if(!strcmp(item, "Linggis"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Hacking Tools"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Kunci T"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Nasi Pecel"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Bubur Pedas"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Es Teh"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Jus Apel"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Boombox"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.20;
    }
    else if(!strcmp(item, "Api Unggun"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.10;
    }
    else if(!strcmp(item, "Kebab A5"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Bakso"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Choco Matcha"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Teh Jeruk"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Susu Murni"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Susu Olahan"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Susu Fresh"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Cabe"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Padi"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Garam Kristal"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.006;
    }
    else if(!strcmp(item, "Tebu"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Beras"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.04;
    }
    else if(!strcmp(item, "Sambal"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Gula"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Garam"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Daging"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Daging Ikan Tawar"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Daging Ayam Goreng"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.02;
    }
    else if(!strcmp(item, "Daging Hiu"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.09;
    }
    else if(!strcmp(item, "Tanduk"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.03;
    }
    else if(!strcmp(item, "Kulit"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Bulu"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.01;
    }
    else if(!strcmp(item, "Boxmats"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.04;
    }
    else if(!strcmp(item, "Baja"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.05;
    }
    else if(!strcmp(item, "Material"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.025;
    }
    else if(!strcmp(item, "Kaca"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.015;
    }
    else if(!strcmp(item, "Karet"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.006;
    }
    else if(!strcmp(item, "Plastik"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.005;
    }
    else if(!strcmp(item, "Alumunium"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.010;
    }
    else if(!strcmp(item, "Backpack"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.50;
    }
    else if(!strcmp(item, "Masker"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.005;
    }
    else if(!strcmp(item, "Plat Besi"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.025;
    }
    else if(!strcmp(item, "Korek Api"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.010;
    }
    else if(!strcmp(item, "Bibit Padi"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.015;
    }
    else if(!strcmp(item, "Bibit Tebu"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.015;
    }
    else if(!strcmp(item, "Bibit Cabe"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.015;
    }
    else if(!strcmp(item, "Pilox"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.005;
    }
    else if(!strcmp(item, "Uranium ACD"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.020;
    }
    else if(!strcmp(item, "Uranium"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.010;
    }
    else if(!strcmp(item, "Senter"))
    {
        AccountData[playerid][pGudangCapacity] += quantity*0.006;
    }
    new sctr[596];
    mysql_format(g_SQL, sctr, sizeof(sctr), "UPDATE `player_characters` SET `Char_GudangStorage`=%f WHERE `pID`=%d", AccountData[playerid][pGudangCapacity], AccountData[playerid][pID]);
    mysql_tquery(g_SQL, sctr);
    return 1;
}

ReduceCapacityGudang(playerid, const item[], quantity)
{
    if(!strcmp(item, "Nasi Goreng"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Kopi Kenangan"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Batu Kotor"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.030;
    }
    else if(!strcmp(item, "Nasi Uduk"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Kanabis"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Batu Bersih"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.030;
    }
    else if(!strcmp(item, "Air Mineral"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Besi"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Tembaga"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Berlian"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.25;
    }
    else if(!strcmp(item, "Emas"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.10;
    }
    else if(!strcmp(item, "Gold"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.10;
    }
    else if(!strcmp(item, "Smartphone"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.25;
    }
    else if(!strcmp(item, "Radio"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.15;
    }
    else if(!strcmp(item, "Kayu"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.06;
    }
    else if(!strcmp(item, "Kayu Potongan"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Kayu Kemas"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.08;
    }
    else if(!strcmp(item, "Marijuana"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Benang"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Kain"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.04;
    }
    else if(!strcmp(item, "Pakaian"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.04;
    }
    else if(!strcmp(item, "Bandage"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Medkit"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Alprazolam"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Ayam Hidup"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.15;
    }
    else if(!strcmp(item, "Ayam Potong"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.10;
    }
    else if(!strcmp(item, "Ayam Kemas"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Sampah Makanan"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.005;
    }
    else if(!strcmp(item, "Kevlar"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.90;
    }
    else if(!strcmp(item, "Botol"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Petrol"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.50;
    }
    else if(!strcmp(item, "Pure Oil"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.50;
    }
    else if(!strcmp(item, "GAS"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.60;
    }
    else if(!strcmp(item, "Ikan"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Rokok"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Pancingan"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.08;
    }
    else if(!strcmp(item, "Umpan"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Hiu"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.90;
    }
    else if(!strcmp(item, "Penyu"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.80;
    }
    else if(!strcmp(item, "Ikan Tawar"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.03;
    }
    else if(!strcmp(item, "Jerigen"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.25;
    }
    else if(!strcmp(item, "Tools Kit"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.30;
    }
    else if(!strcmp(item, "Repair Kit"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.35;
    }
    else if(!strcmp(item, "Linggis"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Hacking Tools"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Kunci T"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Nasi Pecel"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Bubur Pedas"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Es Teh"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Jus Apel"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Boombox"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.20;
    }
    else if(!strcmp(item, "Api Unggun"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.10;
    }
    else if(!strcmp(item, "Kebab A5"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Bakso"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Choco Matcha"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Teh Jeruk"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Susu Murni"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Susu Olahan"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Susu Fresh"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Cabe"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Padi"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Garam Kristal"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.006;
    }
    else if(!strcmp(item, "Tebu"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Beras"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.04;
    }
    else if(!strcmp(item, "Sambal"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Gula"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Garam"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Daging"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Daging Ikan Tawar"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Daging Ayam Goreng"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.02;
    }
    else if(!strcmp(item, "Daging Hiu"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.09;
    }
    else if(!strcmp(item, "Tanduk"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.03;
    }
    else if(!strcmp(item, "Kulit"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Bulu"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.01;
    }
    else if(!strcmp(item, "Boxmats"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.04;
    }
    else if(!strcmp(item, "Baja"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.05;
    }
    else if(!strcmp(item, "Material"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.025;
    }
    else if(!strcmp(item, "Kaca"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.015;
    }
    else if(!strcmp(item, "Karet"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.006;
    }
    else if(!strcmp(item, "Plastik"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.005;
    }
    else if(!strcmp(item, "Alumunium"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.010;
    }
    else if(!strcmp(item, "Backpack"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.50;
    }
    else if(!strcmp(item, "Masker"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.005;
    }
    else if(!strcmp(item, "Plat Besi"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.025;
    }
    else if(!strcmp(item, "Korek Api"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.010;
    }
    else if(!strcmp(item, "Bibit Padi"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.015;
    }
    else if(!strcmp(item, "Bibit Tebu"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.015;
    }
    else if(!strcmp(item, "Bibit Cabe"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.015;
    }
    else if(!strcmp(item, "Pilox"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.005;
    }
    else if(!strcmp(item, "Uranium ACD"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.020;
    }
    else if(!strcmp(item, "Uranium"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.010;
    }
    else if(!strcmp(item, "Senter"))
    {
        AccountData[playerid][pGudangCapacity] -= quantity*0.006;
    }
    if(AccountData[playerid][pGudangCapacity] <= 0) {
        AccountData[playerid][pGudangCapacity] = 0;
    }
    new sctr[596];
    mysql_format(g_SQL, sctr, sizeof(sctr), "UPDATE `player_characters` SET `Char_GudangStorage`=%f WHERE `pID`=%d", AccountData[playerid][pGudangCapacity], AccountData[playerid][pID]);
    mysql_tquery(g_SQL, sctr);
    return 1;
}