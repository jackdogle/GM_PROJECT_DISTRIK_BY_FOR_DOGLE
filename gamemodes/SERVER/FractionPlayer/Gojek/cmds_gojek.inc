#include <YSI\y_hooks>

ShowMenuOrderan(playerid, targetid)
{
    static frmtmenu[1218], notes[128];
    static Float:X, Float:Y, Float:Z;
    
    X = GetPVarFloat(targetid, "OrderX");
    Y = GetPVarFloat(targetid, "OrderY");
    Z = GetPVarFloat(targetid, "OrderZ");
    GetPVarString(targetid, "NotesGojek", notes, sizeof(notes));

    format(frmtmenu, sizeof(frmtmenu), ""GREEN"[Gojek]"WHITE" Rincian orderan %s\ 
    \n- [Details] No. HP: %s // Lokasi: %s // Ongkos: %s\ 
    \n- [Menus] Nasi Goreng: %dx\ 
    \n- [Menus] Bakso: %dx\ 
    \n- [Menus] Nasi Pecel: %dx\ 
    \n- [Menus] Bubur Pedas: %dx\ 
    \n- [Menus] Susu: %dx\ 
    \n- [Menus] Es Teh: %dx\ 
    \n- [Menus] Kopi Kenangan: %dx\ 
    \n- [Menus] Choco Matcha: %dx\ 
    \n- [Notes] %s\ 
    \n- [Pembayaran] Gopay // ID Pesanan: %d",
    ReturnName(targetid),
    AccountData[targetid][pPhone],
    GetLocation(X, Y, Z),
    FormatMoney(TotalHarga[targetid]),
    JumlahKeranjang[targetid][0],
    JumlahKeranjang[targetid][1],
    JumlahKeranjang[targetid][2],
    JumlahKeranjang[targetid][3],
    JumlahKeranjang[targetid][4],
    JumlahKeranjang[targetid][5],
    JumlahKeranjang[targetid][6],
    JumlahKeranjang[targetid][7],
    notes,
    targetid);
    ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Gojek App", frmtmenu, "Tutup", "");
    return 1;
}

ShowGofoodMenu(playerid)
{
    static frmtmenu[1218];

    format(frmtmenu, sizeof(frmtmenu), "Nama Item\tHarga\tKeranjang\ 
    \nNasi Goreng\t$40/pcs\t%dx\ 
    \n"GRAY"Bakso\t"GRAY"$20/pcs\t%dx\ 
    \nNasi Pecel\t$35/pcs\t%dx\ 
    \n"GRAY"Bubur Pedas\t"GRAY"$30/pcs\t%dx\ 
    \nSusu\t$80/pcs\t%dx\ 
    \n"GRAY"Es Teh\t"GRAY"$50/pcs\t%dx\ 
    \nKopi Kenangan\t$35/pcs\t%dx\ 
    \n"GRAY"Choco Matcha\t"GRAY"$30/pcs\t%dx\ 
    \nTagihan\t"GREEN"%s\t"WHITE"%dx\ 
    \n"GRAY"Selesaikan Pesanan",
    JumlahKeranjang[playerid][0],
    JumlahKeranjang[playerid][1],
    JumlahKeranjang[playerid][2],
    JumlahKeranjang[playerid][3],
    JumlahKeranjang[playerid][4],
    JumlahKeranjang[playerid][5],
    JumlahKeranjang[playerid][6],
    JumlahKeranjang[playerid][7],
    FormatMoney(TotalHarga[playerid]),
    TotalKeranjang[playerid]);
    ShowPlayerDialog(playerid, DIALOG_GOFOOD_PESAN, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Gojek App", frmtmenu, "Pilih", "Batal");
    return 1;
}

/* Commands */
CMD:ag(playerid, params[])
{
    if(!IsPlayerConnected(playerid)) return false;
    if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Gojek!");
    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan, tidak dapat mengambil orderan!");
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengendarai kendaraan PT.Gojek Verona!");        
    if(PenumpangAvaible[playerid] != INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memiliki orderan, selesaikan terlebih dahulu!");

    new 
        orderID,
        Float:x,
        Float:y,
        Float:z
    ;

    if(sscanf(params, "i", orderID)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/ag [id pesanan]");
    if(!IsPlayerConnected(orderID)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(OrderGojek[orderID] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Pesanan kadaluarsa / sudah diambil driver lain!");

    new Plate[125];
    foreach(new iter : PvtVehicles)
    {
        if(PlayerVehicle[iter][pVehExists])
        {
            if(PlayerVehicle[iter][pVehPhysic] == GetPlayerVehicleID(playerid))
            {
                if(PlayerVehicle[iter][pVehPlateOwn])
                {
                    format(Plate, sizeof(Plate), "%s", PlayerVehicle[iter][pVehPlate]);
                }
                else
                {
                    format(Plate, sizeof(Plate), "-");
                }
            }
        }
    }

    x = GetPVarFloat(orderID, "OrderX");
    y = GetPVarFloat(orderID, "OrderY");
    z = GetPVarFloat(orderID, "OrderZ");
    if(OrderGojek[orderID] == 1)
    {
        SetPlayerRaceCheckpoint(playerid, 2, x, y, z, x, y, z, 5.0);
        SendClientMessageEx(orderID, -1, ""GREEN"[Gojek]:"WHITE" Driver %s telah menerima orderan anda, harap tunggu dilokasi", ReturnName(playerid));
        SendClientMessageEx(orderID, -1, "- [Details]: No HP Driver: %s // Plat: %s // Kendaraan: %s", AccountData[playerid][pPhone], Plate, GetVehicleName(GetPlayerVehicleID(playerid)), PlayerVehicle[GetPlayerVehicleID(playerid)][pVehPlate]);
        SendClientMessageEx(orderID, -1, "- [Pembayaran]: Gopay: %s", FormatMoney(TarifOngkos[orderID]));
        OrderGojek[orderID] = -1;
        
        PenumpangAvaible[playerid] = orderID;
        DriverAvaible[orderID] = playerid;
        OrderDelayTimer[orderID] = 0;
        ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil mengambil orderan %s, lokasi sudah ditandai di map!", ReturnName(orderID)));
    }
    else if(OrderGojek[orderID] == 2)
    {
        SetPlayerRaceCheckpoint(playerid, 2, x, y, z, x, y, z, 5.0);
        SendClientMessageEx(orderID, -1, ""GREEN"[Gojek]:"WHITE" Driver %s telah menerima orderan anda, harap tunggu dilokasi", ReturnName(playerid));
        SendClientMessageEx(orderID, -1, "- [Details]: No HP Driver: %s // Plat: %s // Kendaraan: %s", AccountData[playerid][pPhone], Plate, GetVehicleName(GetPlayerVehicleID(playerid)), PlayerVehicle[GetPlayerVehicleID(playerid)][pVehPlate]);
        SendClientMessageEx(orderID, -1, "- [Pembayaran]: Gopay: %s", FormatMoney(TarifOngkos[orderID]));
        OrderGojek[orderID] = -1;
        
        PenumpangAvaible[playerid] = orderID;
        DriverAvaible[orderID] = playerid;
        OrderDelayTimer[orderID] = 0;
        ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil mengambil orderan %s, lokasi sudah ditandai di map!", ReturnName(orderID)));
    }
    else if(OrderGojek[orderID] == 3)
    {
        SetPlayerRaceCheckpoint(playerid, 2, x, y, z, x, y, z, 5.0);
        SendClientMessageEx(orderID, -1, ""GREEN"[Gojek]:"WHITE" Driver %s telah menerima orderan anda, harap tunggu dilokasi", ReturnName(playerid));
        SendClientMessageEx(orderID, -1, "- [Details]: No HP Driver: %s // Plat: %s // Kendaraan: %s", AccountData[playerid][pPhone], Plate, GetVehicleName(GetPlayerVehicleID(playerid)), PlayerVehicle[GetPlayerVehicleID(playerid)][pVehPlate]);
        
        PenumpangAvaible[playerid] = orderID;
        DriverAvaible[orderID] = playerid;
        OrderDelayTimer[orderID] = 0;
        ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil mengambil orderan %s, lokasi sudah ditandai di map!", ReturnName(orderID)));
    }
    return 1;
}

CMD:cg(playerid, params[])
{
    if(!IsPlayerConnected(playerid)) return false;
    if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Gojek!");
    if(!AccountData[playerid][pDutyGojek]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum duty gojek!");

    new otherid;
    if(sscanf(params, "d", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/cg [id pesanan]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(DriverAvaible[otherid] != playerid) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Pesanan tersebut bukan customer anda!");
    if(OrderGojek[otherid] != 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "ID Pesanan tersebut bukan memesan GoFood!");

    ShowMenuOrderan(playerid, otherid);
    return 1;
}

CMD:eg(playerid, params[])
{
    if(!IsPlayerConnected(playerid)) return false;
    if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Gojek!");
    if(!AccountData[playerid][pDutyGojek]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum duty gojek!");

    new otherid;
    if(sscanf(params, "d", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/eg [id pesanan]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!IsPlayerNearPlayer(playerid, otherid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak didekat anda!");

    if(PenumpangAvaible[playerid] == otherid)
    {
        new value = TarifOngkos[otherid];

        AccountData[playerid][pSaldoGopay] += value;
        AccountData[otherid][pSaldoGopay] -= value;
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda telah menyelesaikan orderan");
        SendClientMessageEx(otherid, -1, ""GREEN"[Gojek]:"WHITE" Driver %s telah menyelesaikan orderan mu, jangan lupa untuk memberikan rating!", ReturnName(playerid));
        SendClientMessageEx(playerid, -1, ""GREEN"[Gojek]:"WHITE" Anda menyelesaikan orderan, saldo gopay bertambah %s", FormatMoney(value));   
    
        PenumpangAvaible[playerid] = INVALID_PLAYER_ID;
        DriverAvaible[otherid] = INVALID_PLAYER_ID;
        OrderGojek[otherid] = -1;
        OrderDelayTimer[otherid] = 0;
        TarifOngkos[otherid] = 0;

        new icstr[125];
        mysql_format(g_SQL, icstr, sizeof(icstr), "UPDATE `player_characters` SET `Char_Gopay` = `Char_Gopay` + %d WHERE `pID`=%d", value, AccountData[playerid][pID]);
        mysql_tquery(g_SQL, icstr);

        mysql_format(g_SQL, icstr, sizeof(icstr), "UPDATE `player_characters` SET `Char_Gopay` = `Char_Gopay` - %d WHERE `pID`=%d", value, AccountData[otherid][pID]);
        mysql_tquery(g_SQL, icstr);
    } else return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum mengambil orderan tersebut!");
    return 1;
}

CMD:cgopay(playerid, params[])
{
    if(!IsPlayerConnected(playerid)) return false;
    if(AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota gojek!");
    if(AccountData[playerid][pFactionRank] < 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank Bendahara untuk menarik saldo gopay!");

    new customerID, value;
    if(sscanf(params, "ud", customerID, value)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/cgopay [playerd/Name] [jumlah]");
    if(!IsPlayerConnected(customerID)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!IsPlayerNearPlayer(playerid, customerID, 1.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak didekat anda!");
    if(value < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");
    if(value > AccountData[customerID][pSaldoGopay]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo Gopay customer tersebut tidak sebanyak itu!");

    AccountData[customerID][pSaldoGopay] -= value;
    GiveMoney(playerid, value);
    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil mencairkan saldo gopay sejumlah ~g~%s", FormatMoney(value)));
    SendClientMessageEx(customerID, -1, ""GREEN"[Gojek]:"WHITE" Saldo Gopay anda: -"GREEN"%s", FormatMoney(value));

    new icsr[125];
    mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `player_characters` SET `Char_Gopay` = `Char_Gopay` - %d WHERE `pID` = %d", value, AccountData[customerID][pID]);
    mysql_tquery(g_SQL, icsr);
    return 1;
}

/* Dialogs Response */
hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_PESANGORIDE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            
            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESANGORIDE, DIALOG_STYLE_INPUT, ""TCRP"District "WHITE"- Gojek App",
                "ERROR: Tidak dapat diisi kosong!\nHai, kamu akan memesan GoRide. Mau kemana hari ini?", "Input", "Batal");
                return 1;
            }

            if(IsNumeric(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESANGORIDE, DIALOG_STYLE_INPUT, ""TCRP"District "WHITE"- Gojek App",
                "ERROR: Tidak dapat diisi angka!\nHai, kamu akan memesan GoRide. Mau kemana hari ini?", "Input", "Batal");
                return 1;
            }

            if(strlen(inputtext) < 1 || strlen(inputtext) > 128)
            {
                ShowPlayerDialog(playerid, DIALOG_PESANGORIDE, DIALOG_STYLE_INPUT, ""TCRP"District "WHITE"- Gojek App",
                "ERROR: Huruf tidak dapat kurang dari 1 atau lebih dari 128 characters!\nHai, kamu akan memesan GoRide. Mau kemana hari ini?", "Input", "Batal");
                return 1;
            }

            strpack(AccountData[playerid][pEditingItem], inputtext, 64);
            ShowPlayerDialog(playerid, DIALOG_PESANGORIDECONF, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
            sprintf("Baik kamu ingin ke %s\nMohon masukkan berapa tawaran ongkos yang ingin kamu berikan:", inputtext), "Submit", "Batal");
        }
        case DIALOG_PESANGORIDECONF:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");

            new shstr[256], frmtloc[128];
            
            strunpack(frmtloc, AccountData[playerid][pEditingItem]);

            if(isnull(inputtext))
            {
                format(shstr, sizeof(shstr), "Error: Tidak dapat diisi kosong!\nBaik kamu ingin ke %s\nMohon masukkan berapa tawaran ongkos yang ingin kamu berikan:", frmtloc);
                ShowPlayerDialog(playerid, DIALOG_PESANGORIDECONF, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                shstr, "Submit", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                format(shstr, sizeof(shstr), "Error: Hanya dapat diisi angka!\nBaik kamu ingin ke %s\nMohon masukkan berapa tawaran ongkos yang ingin kamu berikan:", frmtloc);
                ShowPlayerDialog(playerid, DIALOG_PESANGORIDECONF, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                shstr, "Submit", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pSaldoGopay])
            {
                format(shstr, sizeof(shstr), "Error: Jumlah tidak valid atau saldo gopay tidak cukup!\nBaik kamu ingin ke %s\nMohon masukkan berapa tawaran ongkos yang ingin kamu berikan:", frmtloc);
                ShowPlayerDialog(playerid, DIALOG_PESANGORIDECONF, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                shstr, "Submit", "Batal");
                return 1;
            }

            static Float:x, Float:y, Float:z;
            GetPlayerPos(playerid, x, y, z);
            foreach(new i : Player) if(IsPlayerConnected(i)) if(AccountData[i][pFaction] == FACTION_GOJEK)
            {
                if(AccountData[i][pDutyGojek])
                {
                    new 
                        MapZone: zone = GetPlayerMapZone(playerid),
                        ZoneName[MAX_MAP_ZONE_NAME];
                    
                    GetMapZoneName(zone, ZoneName);
                    SendClientMessageEx(i, -1, ""GREEN"[GoRide]:"WHITE" Orderan masuk atas nama %s", ReturnName(playerid));
                    SendClientMessageEx(i, -1, "- [Details] No.HP: %s // Lokasi: %s - Tujuan: %s // Ongkos: %s", AccountData[playerid][pPhone], ZoneName, frmtloc, FormatMoney(strval(inputtext)));
                    SendClientMessageEx(i, -1, "- [Pembayaran] Gopay // ID Pesanan: %d", playerid);
                    pMapCP[i] = true;
                }
            }
            OrderGojek[playerid] = 1;// Goride
            OrderDelayTimer[playerid] = 120;
            TarifOngkos[playerid] = strval(inputtext);
            SetPVarFloat(playerid, "OrderX", x);
            SetPVarFloat(playerid, "OrderY", y);
            SetPVarFloat(playerid, "OrderZ", z);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil memesan GoRide");
        }
        case DIALOG_PESANGOCAR:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");

            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESANGOCAR, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "ERROR: Tidak dapat diisi kosong!\n\nHai, kamu akan memesan GoCar. Mau kemana hari ini?", "Input", "Batal");
                return 1;
            }

            if(IsNumeric(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESANGOCAR, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "ERROR: Tidak dapat angka!\n\nHai, kamu akan memesan GoCar. Mau kemana hari ini?", "Input", "Batal");
                return 1;
            }

            strpack(AccountData[playerid][pEditingItem], inputtext, 64);
            ShowPlayerDialog(playerid, DIALOG_PESANGOCARPENUMPANG, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
            "Masukkan jumlah orang yang ingin naik gocar (Maksimal 3 orang):", "Submit", "Batal");
        }
        case DIALOG_PESANGOCARPENUMPANG:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");

            new frmtloc[64], twsmk[255];

            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESANGOCARPENUMPANG, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Tidak dapat diisi kosong!\nMasukkan jumlah orang yang ingin naik gocar (Maksimal 3 orang):", "Submit", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext)) 
            {
                ShowPlayerDialog(playerid, DIALOG_PESANGOCARPENUMPANG, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Hanya dapat diisi angka!\nMasukkan jumlah orang yang ingin naik gocar (Maksimal 3 orang):", "Submit", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > 3)
            {
                ShowPlayerDialog(playerid, DIALOG_PESANGOCARPENUMPANG, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Minimal 1 orang dan maksimal 3 orang!\nMasukkan jumlah orang yang ingin naik gocar (Maksimal 3 orang):", "Submit", "Batal");
                return 1;
            }

            strunpack(frmtloc, AccountData[playerid][pEditingItem]);
            strpack(AccountData[playerid][pEditingPenumpang], inputtext, 32);

            format(twsmk, sizeof(twsmk), "Baik kamu ingin ke %s dan berjumlah %s orang\nMohon masukkan ongkos yang ingin kamu tawarkan kepada driver:", frmtloc, inputtext);
            ShowPlayerDialog(playerid, DIALOG_PESANGOCARCONF, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
            twsmk, "Submit", "Batal");
        }
        case DIALOG_PESANGOCARCONF:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");

            new shstr[256], frmtloc[128], passenger[128];
            
            strunpack(frmtloc, AccountData[playerid][pEditingItem]);
            strunpack(passenger, AccountData[playerid][pEditingPenumpang]);

            if(isnull(inputtext))
            {
                format(shstr, sizeof(shstr), "Error: Tidak dapat diisi kosong!\nBaik kamu ingin ke %s dan berjumlah %s orang\nMohon masukkan ongkos yang ingin kamu tawarkan kepada driver:", frmtloc, inputtext);
                ShowPlayerDialog(playerid, DIALOG_PESANGOCARCONF, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                shstr, "Submit", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                format(shstr, sizeof(shstr), "Error: Hanya dapat diisi angka!\nBaik kamu ingin ke %s dan berjumlah %s orang\nMohon masukkan ongkos yang ingin kamu tawarkan kepada driver:", frmtloc, inputtext);
                ShowPlayerDialog(playerid, DIALOG_PESANGOCARCONF, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                shstr, "Submit", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1 || strval(inputtext) > AccountData[playerid][pSaldoGopay])
            {
                format(shstr, sizeof(shstr), "Error: Jumlah tidak valid atau saldo gopay tidak cukup!\nBaik kamu ingin ke %s dan berjumlah %s orang\nMohon masukkan ongkos yang ingin kamu tawarkan kepada driver:", frmtloc, inputtext);
                ShowPlayerDialog(playerid, DIALOG_PESANGOCARCONF, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                shstr, "Submit", "Batal");
                return 1;
            }

            foreach(new i : Player) if (IsPlayerConnected(i)) if(AccountData[i][pFaction] == FACTION_GOJEK)
            {
                if(AccountData[i][pDutyGojek]) 
                {
                    new 
                        MapZone: zone = GetPlayerMapZone(playerid),
                        ZoneName[MAX_MAP_ZONE_NAME],
                        Float:x, Float:y, Float:z;
                    
                    GetPlayerPos(playerid, x, y, z);
                    GetMapZoneName(zone, ZoneName);

                    SendClientMessageEx(i, -1, ""GREEN"[GoCar]:"WHITE" Orderan masuk atas nama: %s", ReturnName(playerid));
                    SendClientMessageEx(i, -1, "- [Details]: No.HP: %s // Lokasi: %s - Tujuan: %s // Ongkos: %s", AccountData[playerid][pPhone], ZoneName, frmtloc, FormatMoney(strval(inputtext)));
                    SendClientMessageEx(i, -1, "- [Pembayaran]: Gopay // Penumpang: %s // ID Pesanan: %d", passenger, playerid);
                    pMapCP[i] = true;
                }
            }
            OrderGojek[playerid] = 2;
            OrderDelayTimer[playerid] = 120;

            TarifOngkos[playerid] = strval(inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil memesan GoCar!");
        }
        case DIALOG_GOFOOD_PESAN:
        {
            if(!response) 
            {
                for(new i = 0; i < 8; i ++) {
                    JumlahKeranjang[playerid][i] = 0;
                    HargaKeranjang[playerid][i] = 0;
                }
                TotalHarga[playerid] = 0;
                TotalKeranjang[playerid] = 0;
                return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            }

            switch(listitem)
            {
                case 0: //Nasi Goreng
                {
                    ShowPlayerDialog(playerid, DIALOG_PESAN_NASIGORENG, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App", "Mohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                }
                case 1: //Bakso
                {
                    ShowPlayerDialog(playerid, DIALOG_PESAN_BAKSO, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App", "Mohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                }
                case 2: //Pecel
                {
                    ShowPlayerDialog(playerid, DIALOG_PESAN_NASIPECEL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App", "Mohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                }
                case 3: //Bubur
                {
                    ShowPlayerDialog(playerid, DIALOG_PESAN_BUBUR, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App", "Mohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                }
                case 4: //susu
                {
                    ShowPlayerDialog(playerid, DIALOG_PESAN_SUSU, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App", "Mohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                }
                case 5: //ESTEH
                {
                    ShowPlayerDialog(playerid, DIALOG_PESAN_ESTEH, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App", "Mohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                }
                case 6: //Kopi
                {
                    ShowPlayerDialog(playerid, DIALOG_PESAN_KOPI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App", "Mohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                }
                case 7: //Choco
                {
                    ShowPlayerDialog(playerid, DIALOG_PESAN_CHOCOMATCH, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App", "Mohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                }
                case 8: // 
                {
                    ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat dipilih!");
                    ShowGofoodMenu(playerid);
                }
                case 9: // selesaikan pesanan
                {
                    if(TotalHarga[playerid] == 0) 
                    {
                        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih menu GoFood!");
                    }
                    
                    if(AccountData[playerid][pSaldoGopay] < TotalHarga[playerid]) 
                    {
                        for(new i = 0; i < 8; i ++) {
                            JumlahKeranjang[playerid][i] = 0;
                            HargaKeranjang[playerid][i] = 0;
                        }
                        TotalHarga[playerid] = 0;
                        TotalKeranjang[playerid] = 0;
                        return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo Gopay anda tidak cukup!");
                    }
                    
                    ShowPlayerDialog(playerid, DIALOG_PESAN_NOTES, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App", "Kemana pesanan ini diantarkan? (Tuliskan catatan kamu kepada driver)", "Input", "Batal");
                }
            }
        }
        case DIALOG_PESAN_NASIGORENG:
        {
            if(!response) return false;

            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_NASIGORENG, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Tidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_NASIGORENG, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Hanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1)
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_NASIGORENG, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);

            JumlahKeranjang[playerid][0] = quantity;
            HargaKeranjang[playerid][0] = quantity * 40; // Jumlah pesanan dikalikan harga

            TotalHarga[playerid] = 0;
            TotalKeranjang[playerid] = 0;
            for (new i = 0; i < 8; i ++) {
                TotalHarga[playerid] += HargaKeranjang[playerid][i];
                TotalKeranjang[playerid] += JumlahKeranjang[playerid][i];
            }
            ShowGofoodMenu(playerid);
        }
        case DIALOG_PESAN_BAKSO:
        {
            if(!response) return false;

            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_BAKSO, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Tidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_BAKSO, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Hanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1)
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_BAKSO, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);

            JumlahKeranjang[playerid][1] = quantity;
            HargaKeranjang[playerid][1] = quantity * 20; // Jumlah pesanan dikalikan harga
            
            TotalHarga[playerid] = 0;
            TotalKeranjang[playerid] = 0;
            for (new i = 0; i < 8; i ++) {
                TotalHarga[playerid] += HargaKeranjang[playerid][i];
                TotalKeranjang[playerid] += JumlahKeranjang[playerid][i];
            }
            ShowGofoodMenu(playerid);
        }
        case DIALOG_PESAN_NASIPECEL:
        {
            if(!response) return false;

            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_NASIPECEL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Tidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_NASIPECEL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Hanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1)
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_NASIPECEL, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);

            JumlahKeranjang[playerid][2] = quantity;
            HargaKeranjang[playerid][2] = quantity * 35; // Jumlah pesanan dikalikan harga
            
            TotalHarga[playerid] = 0;
            TotalKeranjang[playerid] = 0;
            for (new i = 0; i < 8; i ++) {
                TotalHarga[playerid] += HargaKeranjang[playerid][i];
                TotalKeranjang[playerid] += JumlahKeranjang[playerid][i];
            }
            ShowGofoodMenu(playerid);
        }
        case DIALOG_PESAN_BUBUR:
        {
            if(!response) return false;

            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_BUBUR, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Tidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_BUBUR, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Hanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1)
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_BUBUR, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);

            JumlahKeranjang[playerid][3] = quantity;
            HargaKeranjang[playerid][3] = quantity * 30; // Jumlah pesanan dikalikan harga
            
            TotalHarga[playerid] = 0;
            TotalKeranjang[playerid] = 0;
            for (new i = 0; i < 8; i ++) {
                TotalHarga[playerid] += HargaKeranjang[playerid][i];
                TotalKeranjang[playerid] += JumlahKeranjang[playerid][i];
            }
            ShowGofoodMenu(playerid);
        }
        case DIALOG_PESAN_SUSU:
        {
            if(!response) return false;

            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_SUSU, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Tidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_SUSU, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Hanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1)
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_SUSU, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);

            JumlahKeranjang[playerid][4] = quantity;
            HargaKeranjang[playerid][4] = quantity * 80; // Jumlah pesanan dikalikan harga
            
            TotalHarga[playerid] = 0;
            TotalKeranjang[playerid] = 0;
            for (new i = 0; i < 8; i ++) {
                TotalHarga[playerid] += HargaKeranjang[playerid][i];
                TotalKeranjang[playerid] += JumlahKeranjang[playerid][i];
            }
            ShowGofoodMenu(playerid);
        }
        case DIALOG_PESAN_ESTEH:
        {
            if(!response) return false;

            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_ESTEH, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Tidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_ESTEH, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Hanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1)
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_ESTEH, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);

            JumlahKeranjang[playerid][5] = quantity;
            HargaKeranjang[playerid][5] = quantity * 50; // Jumlah pesanan dikalikan harga
            
            TotalHarga[playerid] = 0;
            TotalKeranjang[playerid] = 0;
            for (new i = 0; i < 8; i ++) {
                TotalHarga[playerid] += HargaKeranjang[playerid][i];
                TotalKeranjang[playerid] += JumlahKeranjang[playerid][i];
            }
            ShowGofoodMenu(playerid);
        }
        case DIALOG_PESAN_KOPI:
        {
            if(!response) return false;

            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_KOPI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Tidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_KOPI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Hanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1)
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_KOPI, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);

            JumlahKeranjang[playerid][6] = quantity;
            HargaKeranjang[playerid][6] = quantity * 35; // Jumlah pesanan dikalikan harga
            
            TotalHarga[playerid] = 0;
            TotalKeranjang[playerid] = 0;
            for (new i = 0; i < 8; i ++) {
                TotalHarga[playerid] += HargaKeranjang[playerid][i];
                TotalKeranjang[playerid] += JumlahKeranjang[playerid][i];
            }
            ShowGofoodMenu(playerid);
        }
        case DIALOG_PESAN_CHOCOMATCH:
        {
            if(!response) return false;

            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_CHOCOMATCH, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Tidak dapat diisi kosong!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(!IsNumeric(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_CHOCOMATCH, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Hanya dapat diisi angka!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            if(strval(inputtext) < 1)
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_CHOCOMATCH, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Jumlah tidak valid!\nMohon masukkan berapa jumlah yang ingin dibeli:", "Input", "Batal");
                return 1;
            }

            new quantity = strval(inputtext);

            JumlahKeranjang[playerid][7] = quantity;
            HargaKeranjang[playerid][7] = quantity * 30; // Jumlah pesanan dikalikan harga
            
            TotalHarga[playerid] = 0;
            TotalKeranjang[playerid] = 0;
            for (new i = 0; i < 8; i ++) {
                TotalHarga[playerid] += HargaKeranjang[playerid][i];
                TotalKeranjang[playerid] += JumlahKeranjang[playerid][i];
            }
            ShowGofoodMenu(playerid);
        }
        case DIALOG_PESAN_NOTES:
        {
            if(!response)
            {
                return ShowGofoodMenu(playerid);
            }

            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_NOTES, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Tidak dapat diisi kosong!\nKemana pesanan ini diantarkan? (Tuliskan catatan kamu kepada driver)", "Input", "Batal");
                return 1;
            }

            if(IsNumeric(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_NOTES, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Tidak dapat diisi angka!\nKemana pesanan ini diantarkan? (Tuliskan catatan kamu kepada driver)", "Input", "Batal");
                return 1;
            }

            if(strlen(inputtext) < 1 || strlen(inputtext) > 128)
            {
                ShowPlayerDialog(playerid, DIALOG_PESAN_NOTES, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Gojek App",
                "Error: Huruf tidak dapat kurang dari 1 atau lebih dari 128 characters!\nKemana pesanan ini diantarkan? (Tuliskan catatan kamu kepada driver)", "Input", "Batal");
                return 1;
            }

            new Float:x, Float:y, Float:z;
            GetPlayerPos(playerid, x, y, z);
            foreach(new i : Player) if(IsPlayerConnected(i)) if (AccountData[i][pFaction] == FACTION_GOJEK)
            {
                if(AccountData[i][pDutyGojek])
                {
                    new 
                        MapZone: zone = GetPlayerMapZone(playerid),
                        ZoneName[MAX_MAP_ZONE_NAME];
                    
                    GetMapZoneName(zone, ZoneName);

                    SendClientMessageEx(i, -1, ""GREEN"[GoFood]:"WHITE" Orderan masuk atas nama: %s", ReturnName(playerid));
                    SendClientMessageEx(i, -1, "- [Details]: No.HP: %s // Lokasi: %s // Ongkos: %s", AccountData[playerid][pPhone], ZoneName, FormatMoney(TotalHarga[playerid]));
                    SendClientMessageEx(i, -1, "- [Notes]: %s", inputtext);
                    SendClientMessageEx(i, -1, "- [Pembayaran]: Gopay // ID Pesanan: %d", playerid);
                    pMapCP[i] = true;
                }
            }
            OrderGojek[playerid] = 3; // Gofood
            OrderDelayTimer[playerid] = 120;
            TarifOngkos[playerid] = TotalHarga[playerid];
            SetPVarFloat(playerid, "OrderX", x);
            SetPVarFloat(playerid, "OrderY", y);
            SetPVarFloat(playerid, "OrderZ", z);
            SetPVarString(playerid, "NotesGojek", inputtext);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil memesan GoFood!");
        }
    }
    return 1;
}

/*hook OnPlayerEnterRaceCP(playerid)
{
    if(PenumpangAvaible[playerid] != INVALID_PLAYER_ID)
    {
        DisablePlayerRaceCheckpoint(playerid);
    }
    return 1;
}*/

/* Timer Delay */
ptask DelayOrderGojek[1000](playerid)
{
    if(OrderDelayTimer[playerid] != 0)
    {
        OrderDelayTimer[playerid] --;
        if(!OrderDelayTimer[playerid])
        {
            OrderGojek[playerid] = -1;
            OrderDelayTimer[playerid] = 0;
            TarifOngkos[playerid] = 0;
            SetPVarFloat(playerid, "OrderX", 0.0);
            SetPVarFloat(playerid, "OrderY", 0.0);
            SetPVarFloat(playerid, "OrderZ", 0.0);
            SendClientMessageEx(playerid, -1, "[i] Anda sudah bisa order gojek kembali!");
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    foreach(new i : Player) if (IsPlayerConnected(i)) 
    {
        if(DriverAvaible[i] == playerid)
        {
            OrderGojek[i] = -1;
            DriverAvaible[i] = INVALID_PLAYER_ID;
        }
    }
    return 1;
}
