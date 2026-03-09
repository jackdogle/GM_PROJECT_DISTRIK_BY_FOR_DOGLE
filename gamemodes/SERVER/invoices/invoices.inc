#include <YSI\y_hooks>

GivePlayerInvoice(playerid, targetid)
{
    if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Player tersebut tidak terkoneksi kedalam server!");
    if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dekat dengan Player tersebut!");

    ShowPlayerDialog(playerid, DIALOG_INVOICE_NAME, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Invoice", "Mohon masukkan nama untuk tagihan ini:", "Input", "Batal");
    return 1;
}

PeriksaInvoice(playerid, targetid)
{
    new shstr[200];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `invoices` WHERE `Owner`=%d ORDER BY Cost DESC", AccountData[targetid][pID]);
    new Cache:execute = mysql_query(g_SQL, shstr);
    if(cache_num_rows() > 0)
    {
        new invoicename[32], invoicecost, affah[600];
        format(affah, sizeof(affah), "Nama Tagihan\tNominal Tagihan\n");
        for(new x; x < cache_num_rows(); ++x)
        {
            cache_get_value_name(x, "Name", invoicename);
            cache_get_value_name_int(x, "Cost", invoicecost);

            format(affah, sizeof(affah), "%s%s\t"RED"%s\n", affah, invoicename, FormatMoney(invoicecost));
        }
        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Invoice Pending", affah, "Tutup", "");
    }
    else
        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Invoice Pending", "Pemain tersebut tidak memiliki Tagihan.", "Tutup", "");
    
    cache_delete(execute);
    return 1;
}

ShowPlayerInvoice(playerid)
{
    new shstr[200];
    mysql_format(g_SQL, shstr, sizeof(shstr), "SELECT * FROM `invoices` WHERE `Owner`=%d ORDER BY Cost DESC", AccountData[playerid][pID]);
    new Cache:execute = mysql_query(g_SQL, shstr);
    new rows = cache_num_rows();
    if(rows)
    {
        new invoicename[32], invoicecost, affah[600];
        format(affah, sizeof(affah), "Nama Tagihan\tNominal Tagihan\n");
        for(new x; x < rows; ++x)
        {
            cache_get_value_name(x, "Name", invoicename);
            cache_get_value_name_int(x, "Cost", invoicecost);

            format(affah, sizeof(affah), "%s%s\t"RED"%s\n", affah, invoicename, FormatMoney(invoicecost));
        }
        ShowPlayerDialog(playerid, DIALOG_PAY_INVOICE, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Invoice Pending", affah, "Pilih", "Batal");
    }
    else
    {
        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Invoice belum terbayar",
        "Anda tidak memiliki tagihan/invoices apapun.", "Tutup", "");
    }

    cache_delete(execute);
    return 1;
}

forward OnInvoiceCreated(playerid, invoicetarget);
public OnInvoiceCreated(playerid, invoicetarget)
{
    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membuat invoice untuk seseorang!");
    ShowTDN(invoicetarget, NOTIFICATION_INFO, "Anda mendapatkan invoice dari seseorang");
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(dialogid == DIALOG_INVOICE_NAME)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        if(AccountData[playerid][pFaction] == FACTION_NONE && AccountData[playerid][pWorkshop] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak tergabung faction maupun pekerja workshop!");
        if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");

        if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_INVOICE_NAME, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Invoice",
        "Error: Nama tidak boleh kosong!\nMohon masukkan nama untuk tagihan ini:", "Input", "Batal");

        if(IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_INVOICE_NAME, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Invoice",
        "Error: Harus berformat nama, tidak boleh angka!\nMohon masukkan nama untuk tagihan ini:", "Input", "Batal");

        if(strlen(inputtext) < 1 || strlen(inputtext) > 128) return ShowPlayerDialog(playerid, DIALOG_INVOICE_NAME, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Invoice",
        "Error: Nama tidak dapat kurang dari 1 huruf atau lebih dari 125!\nMohon masukkan nama untuk tagihan ini:", "Input", "Batal");

        if(!IsValidFormatText(inputtext)) return ShowPlayerDialog(playerid, DIALOG_INVOICE_NAME, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Invoice",
        "Error: Tidak dapat menggunakan tanda kutip ' '\nMohon masukkan nama untuk tagihan ini:", "Input", "Batal");

        SetPVarString(playerid, "InvoiceName", inputtext);
        ShowPlayerDialog(playerid, DIALOG_INVOICE_COST, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Invoice", "Mohon masukkan nominal tagihan dikolom bawah ini:", "Input", "Batal");
    }
    else if(dialogid == DIALOG_INVOICE_COST)
    {
        if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        if(AccountData[playerid][pFaction] == FACTION_NONE && AccountData[playerid][pWorkshop] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak tergabung faction maupun pekerja workshop!");
        if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");

        new targetid = AccountData[playerid][pTarget];
        if(!IsPlayerConnected(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
        if(!IsPlayerNearPlayer(playerid, targetid, 3.5)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak dekat dengan anda!");

        if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_INVOICE_COST, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Invoice",
        "Error: Nominal tagihan tidak boleh kosong\nMohon masukkan nominal tagihan dikolom bawah ini:", "Input", "Batal");

        if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_INVOICE_COST, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Invoice",
        "Error: Hanya dapat diisi angka!\nMohon masukkan nominal tagihan dikolom bawah ini:", "Input", "Batal");

        if(strval(inputtext) < 1) return ShowPlayerDialog(playerid, DIALOG_INVOICE_COST, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Invoice",
        "Error: Anda tidak dapat memasukkan nominal kurang dari $1 untuk invoices!\nMohon masukkan nominal tagihan dikolom bawah ini:", "Input", "Batal");

        new cost = strval(inputtext), invoicename[125], cQuery[598];
        GetPVarString(playerid, "InvoiceName", invoicename, sizeof(invoicename));
        
        mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `invoices` SET `Name`='%s', `Sender`=%d, `Faction`=%d, `Cost`=%d, `Owner`=%d", invoicename, AccountData[playerid][pID], AccountData[playerid][pFaction], cost, AccountData[targetid][pID]);
        mysql_tquery(g_SQL, cQuery, "OnInvoiceCreated", "dd", playerid, targetid);
    }
    else if(dialogid == DIALOG_PAY_INVOICE)
    {
        if(!response)
        {
            return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
        }

        if(listitem == -1) 
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memilih invoices yang akan dibayar!");
        }

        new cQuery[200];
        mysql_format(g_SQL, cQuery, sizeof(cQuery), "SELECT * FROM `invoices` WHERE `Owner`=%d ORDER BY Cost DESC", AccountData[playerid][pID]);
        new Cache:execute = mysql_query(g_SQL, cQuery);
        if(cache_num_rows() > 0)
        {
            new invid, sender, cost, factid;
            if(listitem >= 0 && listitem < cache_num_rows())
            {
                cache_get_value_name_int(listitem, "invoiceID", invid);
                cache_get_value_name_int(listitem, "Faction", factid);
                cache_get_value_name_int(listitem, "Sender", sender);
                cache_get_value_name_int(listitem, "Cost", cost);

                if(AccountData[playerid][pBankMoney] < cost) return ShowTDN(playerid, NOTIFICATION_ERROR, "Saldo rekening anda tidak cukup untuk membayar invoices!");
  
                if(factid == 1) // Polisi Faction ID
                {
                    new sha[200], icsr[200];
                    foreach(new i : Player)
                    {
                        if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && sender == AccountData[i][pID])
                        {
                            //AccountData[i][pBankMoney] += (cost/100)*10;
                            ShowTDN(i, NOTIFICATION_INFO, "Seseorang telah membayar invoice yang anda berikan");
                            //Info(i, "Saldo rekening anda sekarang "GREEN"%s"WHITE" ~> "GREEN"%s", FormatMoney(AccountData[i][pBankMoney]-(cost/100)*60), FormatMoney(AccountData[i][pBankMoney]));
                        }
                    }
                    //mysql_format(g_SQL, rasberry, sizeof(rasberry), "UPDATE `player_characters` SET `Char_BankMoney` = `Char_BankMoney` + %d WHERE `pID` = %d", (cost/100)*60, sender);
                    // mysql_tquery(g_SQL, rasberry);

                    AccountData[playerid][pBankMoney] -= cost;
                    PoliceMoneyVault += cost; // Penghasilan 20% untuk masuk ke brankas faction tersebut!

                    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil membayar invoice sebesar ~g~%s", FormatMoney(cost)));
                    
                    mysql_format(g_SQL, sha, sizeof(sha), "DELETE FROM `invoices` WHERE `invoiceID`=%d", invid);
                    mysql_tquery(g_SQL, sha);

                    mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `stuffs` SET `policemoneyvault`=%d WHERE `ID`=0", PoliceMoneyVault);
                    mysql_tquery(g_SQL, icsr);

                }
                else if(factid == 2) // Pemerintah Faction ID
                {
                    new sha[200], icsr[200];
                    foreach(new i : Player)
                    {
                        if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && sender == AccountData[i][pID])
                        {
                            //AccountData[i][pBankMoney] += (cost/100)*30;
                            ShowTDN(i, NOTIFICATION_INFO, "Seseorang telah membayar invoice yang anda berikan");
                            //Info(i, "Saldo rekening anda sekarang "GREEN"%s"WHITE" ~> "GREEN"%s", FormatMoney(AccountData[i][pBankMoney]-(cost/100)*30), FormatMoney(AccountData[i][pBankMoney]));
                        }
                    }
                    //mysql_format(g_SQL, rasberry, sizeof(rasberry), "UPDATE `player_characters` SET `Char_BankMoney` = `Char_BankMoney` + %d WHERE `pID` = %d", (cost/100)*30, sender);
                    //mysql_tquery(g_SQL, rasberry);

                    AccountData[playerid][pBankMoney] -= cost;
                    PemerintahMoneyVault += cost; // Penghasilan 20% untuk masuk ke brankas faction tersebut!
                    
                    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil membayar invoice sebesar ~g~%s", FormatMoney(cost)));
                    
                    mysql_format(g_SQL, sha, sizeof(sha), "DELETE FROM `invoices` WHERE `invoiceID`=%d", invid);
                    mysql_tquery(g_SQL, sha);

                    mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `stuffs` SET `pemerintahmoneyvault`=%d WHERE `ID`=0", PemerintahMoneyVault);
                    mysql_tquery(g_SQL, icsr);
                }
                else if(factid == 3) // EMS Faction ID
                {
                    new sha[200], icsr[200];
                    foreach(new i : Player)
                    {
                        if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && sender == AccountData[i][pID])
                        {
                            //AccountData[i][pBankMoney] += (cost/100)*20;
                            ShowTDN(i, NOTIFICATION_INFO, "Seseorang telah membayar invoice yang anda berikan");
                            //Info(i, "Saldo rekening anda sekarang "GREEN"%s"WHITE" ~> "GREEN"%s", FormatMoney(AccountData[i][pBankMoney]-(cost/100)*20), FormatMoney(AccountData[i][pBankMoney]));
                        }
                    }
                    //mysql_format(g_SQL, rasberry, sizeof(rasberry), "UPDATE `player_characters` SET `Char_BankMoney` = `Char_BankMoney` + %d WHERE `pID` = %d", (cost/100)*20, sender);
                    //mysql_tquery(g_SQL, rasberry);

                    AccountData[playerid][pBankMoney] -= cost;
                    EMSMoneyVault += cost; // Penghasilan 20% untuk masuk ke brankas faction tersebut!
                    
                    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil membayar invoice sebesar ~g~%s", FormatMoney(cost)));
                    
                    mysql_format(g_SQL, sha, sizeof(sha), "DELETE FROM `invoices` WHERE `invoiceID`=%d", invid);
                    mysql_tquery(g_SQL, sha);

                    mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `stuffs` SET `emsmoneyvault`=%d WHERE `ID`=0", EMSMoneyVault);
                    mysql_tquery(g_SQL, icsr);
                }
                else if(factid == 5) // Bengkel Faction ID
                {
                    new sha[200], icsr[200];
                    foreach(new i : Player)
                    {
                        if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && sender == AccountData[i][pID])
                        {
                            //AccountData[i][pBankMoney] += (cost/100)*20;
                            ShowTDN(i, NOTIFICATION_INFO, "Seseorang telah membayar invoice yang anda berikan");
                            //Info(i, "Saldo rekening anda sekarang "GREEN"%s"WHITE" ~> "GREEN"%s", FormatMoney(AccountData[i][pBankMoney]-(cost/100)*20), FormatMoney(AccountData[i][pBankMoney]));
                        }
                    }
                    //mysql_format(g_SQL, rasberry, sizeof(rasberry), "UPDATE `player_characters` SET `Char_BankMoney` = `Char_BankMoney` + %d WHERE `pID` = %d", (cost/100)*20, sender);
                    //mysql_tquery(g_SQL, rasberry);

                    AccountData[playerid][pBankMoney] -= cost;
                    BengkelMoneyVault += cost; // Penghasilan 20% untuk masuk ke brankas faction tersebut!
                    
                    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil membayar invoice sebesar ~g~%s", FormatMoney(cost)));
                    
                    mysql_format(g_SQL, sha, sizeof(sha), "DELETE FROM `invoices` WHERE `invoiceID`=%d", invid);
                    mysql_tquery(g_SQL, sha);

                    mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `stuffs` SET `bengkelmoneyvault`=%d WHERE `ID`=0", BengkelMoneyVault);
                    mysql_tquery(g_SQL, icsr);
                }
                else if(factid == 6) // Pedagang Faction ID
                {
                    new sha[200], icsr[200];
                    foreach(new i : Player)
                    {
                        if(AccountData[i][IsLoggedIn] && AccountData[i][pSpawned] && sender == AccountData[i][pID])
                        {
                            //AccountData[i][pBankMoney] += (cost/100)*20;
                            ShowTDN(i, NOTIFICATION_INFO, "Seseorang telah membayar invoice yang anda berikan");
                            //Info(i, "Saldo rekening anda sekarang "GREEN"%s"WHITE" ~> "GREEN"%s", FormatMoney(AccountData[i][pBankMoney]-(cost/100)*20), FormatMoney(AccountData[i][pBankMoney]));
                        }
                    }
                    //mysql_format(g_SQL, rasberry, sizeof(rasberry), "UPDATE `player_characters` SET `Char_BankMoney` = `Char_BankMoney` + %d WHERE `pID` = %d", (cost/100)*20, sender);
                    //mysql_tquery(g_SQL, rasberry);

                    AccountData[playerid][pBankMoney] -= cost;
                    RestoMoneyVault += cost; // Penghasilan 20% untuk masuk ke brankas faction tersebut!

                    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil membayar invoice sebesar ~g~%s", FormatMoney(cost)));
                    
                    mysql_format(g_SQL, sha, sizeof(sha), "DELETE FROM `invoices` WHERE `invoiceID`=%d", invid);
                    mysql_tquery(g_SQL, sha);

                    mysql_format(g_SQL, icsr, sizeof(icsr), "UPDATE `stuffs` SET `restomoneyvault`=%d WHERE `ID`=0", RestoMoneyVault);
                    mysql_tquery(g_SQL, icsr);
                }
                else
                {
                    // Cek apakah invoice milik Workshop
                    new wid = GetPVarInt(playerid, "InvoiceWSID");
                    new senderid = GetPVarInt(playerid, "InvoiceSenderID");

                    if(wid != -1)
                    {
                        // Debug info
                        printf("[DEBUG] Player %s (ID: %d) membayar invoice WorkshopID: %d, Pemberi: %d, Cost: %d",
                            AccountData[playerid][pName], playerid, wid, senderid, cost);

                        // Kurangi saldo pembayar
                        AccountData[playerid][pBankMoney] -= cost;
                        printf("[DEBUG] Saldo %s setelah bayar: %d", AccountData[playerid][pName], AccountData[playerid][pBankMoney]);

                        // Tambahkan ke workshop
                        wData[wid][wMoney] += cost;
                        Workshop_Save(wid);
                        printf("[DEBUG] Workshop ID %d saldo sekarang: %d", wid, wData[wid][wMoney]);

                        // Notif ke pembayar
                        ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Invoice berhasil dibayar, uang masuk ke workshop (%s)", FormatMoney(cost)));

                        // Notif ke pemberi invoice
                        if(IsPlayerConnected(senderid))
                            ShowTDN(senderid, NOTIFICATION_INFO, "Seseorang telah membayar invoice yang anda berikan");

                        // Hapus PVar
                        DeletePVar(playerid, "InvoiceWSID");
                        DeletePVar(playerid, "InvoiceSenderID");

                        // Hapus dari database
                        new sha[200];
                        mysql_format(g_SQL, sha, sizeof(sha), "DELETE FROM invoices WHERE invoiceID=%d", invid);
                        mysql_tquery(g_SQL, sha);
                    }
                }
            }
        }
        cache_delete(execute);
    }
    return 1;
}

// GetSender(sender)
// {
//     foreach(new i : Player) if (IsPlayerConnected(i) && AccountData[i][IsLoggedIn] && AccountData[i][pID] == sender)
//     {
//         return i;
//     }
//     return INVALID_PLAYER_ID;
// }
