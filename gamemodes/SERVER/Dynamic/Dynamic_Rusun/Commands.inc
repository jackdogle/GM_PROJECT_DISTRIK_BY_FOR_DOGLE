#include <YSI_Coding\y_hooks>

CMD:addrusuns(playerid, params[])
{
    if (AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    new price, name[128];
    if (sscanf(params, "ds[128]", price, name)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addrusun [harga 30 hari] [nama rusun]");

    new id;
    id = Rusun_Create(playerid, price, name);

    if (id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Dynamic Rusun telah mencapai limit server!");

    Info(playerid, "Anda telah membuat Dynamic Rusun ID: %d - %s", id, name);
    return 1;
}

CMD:removerusun(playerid, params[])
{
    if (AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);
    
    new id;
    if (sscanf(params, "d", id)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/removerusun [id rusun]");
    if (!Iter_Contains(RusunDatas, id)) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Rusun tidak ditemukan!");

    Rusun_Delete(id);
    Info(playerid, "Anda telah menghapus Dynamic Rusun ID: %d", id);
    return 1;   
}

// All System Player
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        static rsid = -1;

        if(AccountData[playerid][pInRusun] != -1 && IsPlayerInRangeOfPoint(playerid, 1.5, RusunsData[AccountData[playerid][pInRusun]][rIntPos][0], RusunsData[AccountData[playerid][pInRusun]][rIntPos][1], RusunsData[AccountData[playerid][pInRusun]][rIntPos][2]))
        {
            if (AccountData[playerid][ActivityTime] != 0) 
                return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu sampai progress selesai!");
          
            AccountData[playerid][ActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "OUT");
            ShowProgressBar(playerid);
            
            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            EnterRusunTimer[playerid] = SetTimerEx("OutFromRusun", 1000, true, "dd", playerid, AccountData[playerid][pInRusun]);
        }
        
        if(IsPlayerInRangeOfPoint(playerid, 1.5, 2234.7104, -1106.1246, 1050.8828) && GetPlayerVirtualWorld(playerid) == AccountData[playerid][pInRusun])
        {
            Dialog_Show(playerid, RUSUN_BRANKAS, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- %s",
            "Undang\
            \n"GRAY"Pakaian\
            \nMembuang Pakaian\
            \n"GRAY"Brankas", "Pilih", "Batal", RusunsData[AccountData[playerid][pInRusun]][rName]);
        }

        if ((rsid = Rusun_Nearest(playerid)) != -1)
        {
            if (RusunsData[rsid][rOwnerID] != 0)
            {
                if (RusunsData[rsid][rOwnerID] != AccountData[playerid][pID])
                {
                    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
                    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, sprintf(""TCRP"District  "WHITE"- %s", RusunsData[rsid][rName]), 
                    "Sudah dimiliki warga lain!", "Tutup", "");
                }
                else
                {
                    AccountData[playerid][pInRusun] = rsid;
                    Dialog_Show(playerid, RUSUN_OWNED, DIALOG_STYLE_LIST, sprintf(""TCRP"District  "WHITE"- %s", RusunsData[rsid][rName]),
                    "Masuk\
                    \n"GRAY"Cek status sewa", "Pilih", "Batal");
                }
            }
            else
            {
                AccountData[playerid][pInRusun] = rsid;
                Dialog_Show(playerid, RUSUN_MENU, DIALOG_STYLE_TABLIST, sprintf(""TCRP"District  "WHITE"- %s", RusunsData[rsid][rName]),
                "Sewa\t"GREEN"%s / bulan", "Pilih", "Batal", FormatMoney(RusunsData[rsid][rPrice]));
            }
        }
    }
    return 1;
}

Dialog:RUSUN_MENU(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        AccountData[playerid][pInRusun] = -1;
        return 1;
    }

    new id = AccountData[playerid][pInRusun];

    if (AccountData[playerid][pOwnedRusun] == 1)
    {
        AccountData[playerid][pInRusun] = -1;
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah menyewa rusun sebelumnya!");
        return 1;
    }

    if (AccountData[playerid][pMoney] < RusunsData[id][rPrice])
    {
        AccountData[playerid][pInRusun] = -1;
        ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
        return 1;
    }

    TakeMoney(playerid, RusunsData[id][rPrice]);
    GetPlayerName(playerid, RusunsData[id][rOwner], MAX_PLAYER_NAME);
    RusunsData[id][rOwnerID] = AccountData[playerid][pID];
    AccountData[playerid][pOwnedRusun] = true;

    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menyewa rusun");

    RusunRefresh(id);
    RusunSave(id);
    return 1;
}

Dialog:RUSUN_OWNED(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        AccountData[playerid][pInRusun] = -1;
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        return 1;
    }

    new id = AccountData[playerid][pInRusun];

    if (AccountData[playerid][pInjured])
    {
        AccountData[playerid][pInRusun] = -1;
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        return 1;
    }

    switch(listitem)
    {
        case 0: // Maasuk
        {
            if (AccountData[playerid][ActivityTime] != 0) 
                return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu sampai progress selesai!");
            
            AccountData[playerid][ActivityTime] = 1;
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "ENTERING");
            ShowProgressBar(playerid);

            ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
            EnterRusunTimer[playerid] = SetTimerEx("EnterToRusun", 1000, true, "dd", playerid, id);
        }
        case 1: 
        {
            RemainingRusunTimes(playerid);
        }
    }
    return 1;
}

Dialog:RUSUN_BRANKAS(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    }

    switch(listitem)
    {
        case 0:
        {
            new id = RusunInside(playerid), frmxt[125], count = 0;
            foreach(new i : Player) if (i != playerid) if(IsPlayerInRangeOfPoint(i, 2.0, RusunsData[id][rExtPos][0], RusunsData[id][rExtPos][1], RusunsData[id][rExtPos][2]))
            {
                format(frmxt, sizeof(frmxt), "%sPlayer ID: %d\n", frmxt, i);
                PlayerRusunInvite[playerid][count++] = i;
            }

            if(count == 0)
            {
                PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Undang Teman",
                "Tidak ada player yang dekat dengan pintu rusun anda!", "Close", "");
            }

            Dialog_Show(playerid, RUSUN_INVITE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Undang Teman", frmxt, "Pilih", "Batal");
        }
        case 1:
        {
            ShowPlayerClothes(playerid);
        }
        case 2:
        {
            DropClothesPlayer(playerid);
        }
        case 3:
        {
            Dialog_Show(playerid, RUSUN_BROPTION, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Brankas",
            "Simpan Barang\n"GRAY"Ambil Barang", "Pilih", "Batal");
        }
    }
    return 1;
}

Dialog:RUSUN_INVITE(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        for (new i = 0; i < MAX_PLAYERS; i ++) 
            PlayerRusunInvite[playerid][i] = INVALID_PLAYER_ID;
        
        return 1;
    }

    new targetid = PlayerRusunInvite[playerid][listitem], id = -1;
    if ((id = RusunInside(playerid)) != -1)
    {
        if (!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
        SetPVarInt(targetid, "RusunID", id);
        Dialog_Show(targetid, RUSUN_INVITECONF, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Undang Teman",
        "Seseorang mengundang anda untuk masuk ke dalam rusunnya", "Terima", "Tolak");
    }
    return 1;
}

Dialog:RUSUN_INVITECONF(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        DeletePVar(playerid, "RusunID");
        ShowTDN(playerid, NOTIFICATION_INFO, "Anda menolak undangan untuk masuk ke dalam rusun");
        return 1;
    }

    new id = -1;
    if ((id = GetPVarInt(playerid, "RusunID")) != -1)
    {
        if (AccountData[playerid][ActivityTime] != 0)
            return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu sampai progress selesai!");
        
        AccountData[playerid][ActivityTime] = 1;
        EnterRusunTimer[playerid] = SetTimerEx("EnterToRusun", 1000, true, "dd", playerid, id);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "ENTERING");
        ShowProgressBar(playerid);
        ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
    }
    return 1;
}

Dialog:RUSUN_BROPTION(playerid, response, listitem, inputtext[])
{
    if(!response) 
    {
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    }
    new id = RusunInside(playerid);

    if(id == -1)
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang didalam rusun!");
    }

    switch(listitem)
    {
        case 0: //deposit
        {
            RusunBrankas[playerid][rusunbrankasID] = 0;
            RusunBrankas[playerid][rusunbrankasTemp] = EOS;
            RusunBrankas[playerid][rusunbrankasModel] = 0;
            RusunBrankas[playerid][rusunbrankasQuant] = 0;

            new str[1218], amounts, itemname[32], tss[128], Cache:execute;

            format(str, sizeof(str), "Nama Item\tJumlah\tBerat (%.3f/80kg)\n", AccountData[playerid][pRusunCapacity]);
            mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM inventory WHERE ID=%d", AccountData[playerid][pID]);
            execute = mysql_query(g_SQL, tss, true);

            if(cache_num_rows(execute) > 0)
            {
                for(new x = 0; x < cache_num_rows(execute); ++x)
                {
                    cache_get_value_name(x, "invItem", itemname, execute);
                    cache_get_value_name_int(x, "invQuantity", amounts, execute);

                    format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                }

                Dialog_Show(playerid, RUSUNVAULT_DEPOSIT, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas", str, "Pilih", "Batal");
            }
            else 
            {
                PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
                cache_delete(execute); // pastikan cache dihapus sebelum return
                return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas","Anda tidak memiliki barang untuk disimpan!", "Tutup", "");
            }

            cache_delete(execute); // hapus cache setelah semua selesai
        }
        case 1: //withdraw
        {
            new str[2108], amounts, itemname[64], icsr[225], Cache:execute;
            format(str, sizeof(str), "Nama Item\tJumlah\tBerat (%.3f/80kg)\n", AccountData[playerid][pRusunCapacity]);
            mysql_format(g_SQL, icsr, sizeof(icsr), "SELECT * FROM `player_rusunstorage` WHERE `ID`=%d", AccountData[playerid][pID]);
            execute = mysql_query(g_SQL, icsr, true);
            if(cache_num_rows() > 0)
            {
                for(new x; x < cache_num_rows(); ++x)
                {
                    cache_get_value_name(x, "rsItemName", itemname);
                    cache_get_value_name_int(x, "rsItemQuantity", amounts);

                    format(str, sizeof(str), "%s%s\t%d\t-\n", str, itemname, amounts);
                }
                Dialog_Show(playerid, RUSUNVAULT_WITHDRAW, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas", str, "Pilih", "Batal");
            }
            else 
            {
                return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas",
                "Tidak ada barang brankas!", "Tutup", "");
            }
            cache_delete(execute);
        }
    }
    return 1;
}

Dialog:RUSUNVAULT_DEPOSIT(playerid, response, listitem, inputtext[])
{
    new id = RusunInside(playerid);
    if(id == -1)
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang didalam rusun!");
    }

    if(!response)
    {
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    }

    if(listitem == -1)
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih barang!");
    }

    new tss[712], Cache:execute;
    mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `inventory` WHERE `ID`=%d", AccountData[playerid][pID]);
    execute = mysql_query(g_SQL, tss, true);
    if(cache_num_rows() > 0)
    {
        if(listitem >= 0 && listitem < cache_num_rows())
        {
            cache_get_value_name(listitem, "invItem", RusunBrankas[playerid][rusunbrankasTemp]);
            cache_get_value_name_int(listitem, "invModel", RusunBrankas[playerid][rusunbrankasModel]);
            cache_get_value_name_int(listitem, "invQuantity", RusunBrankas[playerid][rusunbrankasQuant]);

            new shstr[529];
            format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nMohon masukkan berapa jumlah yang ingin di simpan:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
            Dialog_Show(playerid, RUSUNVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
            shstr, "Input", "Batal");
        }
    }
    cache_delete(execute);
    return 1;
}

Dialog:RUSUNVAULT_IN(playerid, response, listitem, inputtext[])
{
    new id = RusunInside(playerid);
    if(id == -1)
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang didalam rusun!");
    }

    if(!response)
    {
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    }

    new shstr[512];
    if(isnull(inputtext))
    {
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nTidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin di simpan:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
        Dialog_Show(playerid, RUSUNVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumeric(inputtext))
    {
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin di simpan:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
        Dialog_Show(playerid, RUSUNVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > RusunBrankas[playerid][rusunbrankasQuant])
    {
        format(shstr, sizeof(shstr), "Anda akan menyimpan item:\nNama: %s\nJumlah di tas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin di simpan:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
        Dialog_Show(playerid, RUSUNVAULT_IN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext);

    if(AccountData[playerid][pRusunCapacity] >= 80)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Brankas rusun anda telah penuh!");
    
    Inventory_Remove(playerid, RusunBrankas[playerid][rusunbrankasTemp], quantity);
    ShowItemBox(playerid, sprintf("Removed %dx", quantity), RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasModel]);
    AddCapacityRusun(playerid, RusunBrankas[playerid][rusunbrankasTemp], quantity);

    new invstr[1218];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `player_rusunstorage` WHERE `ID`=%d AND `rsItemName`='%s'", AccountData[playerid][pID], RusunBrankas[playerid][rusunbrankasTemp]);
    mysql_query(g_SQL, shstr);
    if(cache_num_rows() > 0)
    {
        mysql_format(g_SQL, invstr, sizeof(invstr), "UPDATE `player_rusunstorage` SET `rsItemQuantity` = `rsItemQuantity` + %d WHERE `ID`=%d AND `rsItemName`='%s'", quantity, AccountData[playerid][pID], RusunBrankas[playerid][rusunbrankasTemp]);
        mysql_tquery(g_SQL, invstr, "OnRusunDepo", "d", playerid);
    }
    else
    {
        mysql_format(g_SQL, invstr, sizeof(invstr), "INSERT INTO `player_rusunstorage` SET `ID`=%d, `rsItemName`='%s', `rsItemModel`=%d, `rsItemQuantity`=%d", AccountData[playerid][pID], RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasModel], quantity);
        mysql_tquery(g_SQL, invstr, "OnRusunDepo", "d", playerid);
    }
    return 1;
}

Dialog:RUSUNVAULT_WITHDRAW(playerid, response, listitem, inputtext[])
{
    new id = RusunInside(playerid);
    if(id == -1)
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang didalam rusun!");
    }

    if(!response)
    {
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    }

    if(listitem == -1)
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih barang!");
    }

    new tss[1218], Cache:execute;
    mysql_format(g_SQL, tss, sizeof(tss), "SELECT * FROM `player_rusunstorage` WHERE `ID`=%d", AccountData[playerid][pID]);
    execute = mysql_query(g_SQL, tss, true);
    if(cache_num_rows() > 0)
    {
        if(listitem >= 0 && listitem < cache_num_rows())
        {
            cache_get_value_name_int(listitem, "rsItemID", RusunBrankas[playerid][rusunbrankasID]);
            cache_get_value_name(listitem, "rsItemName", RusunBrankas[playerid][rusunbrankasTemp]);
            cache_get_value_name_int(listitem, "rsItemModel", RusunBrankas[playerid][rusunbrankasModel]);
            cache_get_value_name_int(listitem, "rsItemQuantity", RusunBrankas[playerid][rusunbrankasQuant]);

            new shstr[528];
            format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nMohon masukkan berapa jumlah yang ingin anda ambil dari brankas:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
            Dialog_Show(playerid, RUSUNVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
            shstr, "Input", "Batal");
        }
    }
    cache_delete(execute);
    return 1;
}

Dialog:RUSUNVAULT_OUT(playerid, response, listitem, inputtext[])
{
    new id = RusunInside(playerid);
    if(id == -1)
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang didalam rusun!");
    }

    if(!response)
    {
        return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    }

    new shstr[512];
    if(isnull(inputtext))
    {
        format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nTidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin anda ambil dari brankas:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
        Dialog_Show(playerid, RUSUNVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
        shstr, "Input", "Batal");
        return 1;
    }

    if(!IsNumeric(inputtext))
    {
        format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nHanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin anda ambil dari brankas:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
        Dialog_Show(playerid, RUSUNVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
        shstr, "Input", "Batal");
        return 1;
    }

    if(strval(inputtext) < 1 || strval(inputtext) > RusunBrankas[playerid][rusunbrankasQuant])
    {
        format(shstr, sizeof(shstr), "Anda akan mengambil item:\nNama: %s\nJumlah di brankas: %d\nJumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin anda ambil dari brankas:", RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasQuant]);
        Dialog_Show(playerid, RUSUNVAULT_OUT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas",
        shstr, "Input", "Batal");
        return 1;
    }

    new quantity = strval(inputtext), tss[155];
    if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");

    RusunBrankas[playerid][rusunbrankasQuant] -= quantity;
    if(RusunBrankas[playerid][rusunbrankasQuant] > 0)
    {
        mysql_format(g_SQL, tss, sizeof(tss), "UPDATE `player_rusunstorage` SET `rsItemQuantity`=%d WHERE `rsItemID`=%d", RusunBrankas[playerid][rusunbrankasQuant], RusunBrankas[playerid][rusunbrankasID]);
        mysql_tquery(g_SQL, tss);
    } 
    else 
    {
        mysql_format(g_SQL, tss, sizeof(tss), "DELETE FROM `player_rusunstorage` WHERE `rsItemID`=%d", RusunBrankas[playerid][rusunbrankasID]);
        mysql_tquery(g_SQL, tss);
    }
    Inventory_Add(playerid, RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasModel], quantity);
    ShowItemBox(playerid, sprintf("Received %dx", quantity), RusunBrankas[playerid][rusunbrankasTemp], RusunBrankas[playerid][rusunbrankasModel]);
    ReduceCapacityRusun(playerid, RusunBrankas[playerid][rusunbrankasTemp], quantity);

    RusunBrankas[playerid][rusunbrankasID] = 0;
    RusunBrankas[playerid][rusunbrankasTemp] = EOS;
    RusunBrankas[playerid][rusunbrankasModel] = 0;
    RusunBrankas[playerid][rusunbrankasQuant] = 0;
    return 1;
}