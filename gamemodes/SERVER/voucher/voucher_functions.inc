#define MAX_VOUCHER 1

enum e_voucherdata
{
    voucherID,
    voucherFee,
    voucherTime,

    //not save
    bool: voucherExists
}
new VoucherData[MAX_VOUCHER][e_voucherdata];

forward LoadVoucher();
public LoadVoucher()
{
    new rows = cache_num_rows();
    if(rows)
    {
        forex(i, rows)
        {
            VoucherData[i][voucherExists] = true;

            VoucherData[i][voucherID] = cache_get_field_int(i, "VoucherID");
            VoucherData[i][voucherFee] = cache_get_field_int(i, "VoucherFee");
            VoucherData[i][voucherTime] = cache_get_field_int(i, "VoucherTime");
        }
        printf("[Voucher]: Jumlah kompensasi yang dimuat adalah %d", rows);
    }
}

/* Command */
CMD:addkompensasi(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);
    
    new fee, expiredTime,  cQuery[200];
    if(sscanf(params, "dd", fee, expiredTime)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/addkompensasi [kompensasi] [expired time [hari]]");
    if(VoucherData[0][voucherExists]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Sudah ada kompensasi yang dikeluarkan, hapus dulu '/removekompensasi'");
    if(fee < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal dibawah $1 untuk kompensasi!");
    if(expiredTime < 1 || expiredTime >= 30) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan dibawah 1 atau lebih dari 30 hari!");

    VoucherData[0][voucherExists] = true;
    VoucherData[0][voucherID] = 0;
    VoucherData[0][voucherFee] = fee;
    VoucherData[0][voucherTime] = gettime() + (expiredTime * 86400); //value dikalikan 24 jam dalam detik
    SendClientMessageToAllEx(X11_ARWIN, "[AdmCmd] "RED"%s"ARWIN1" Menambahkan kompensasi server sejumlah "GREEN"%s"ARWIN1" gunakan '/klaimkompensasi' untuk mengambilnya", AccountData[playerid][pAdminname], FormatMoney(fee));
    foreach(new i : Player) if (IsPlayerConnected(i))
    {
        AccountData[i][pKompensasi] = 0;
    }
    mysql_tquery(g_SQL, "UPDATE `player_characters` SET `Char_Kompensasi` = 0");
    
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `voucher` SET `VoucherID`=%d, `VoucherFee`=%d, `VoucherTime`=%d", VoucherData[0][voucherID], VoucherData[0][voucherFee], VoucherData[0][voucherTime]);
    mysql_tquery(g_SQL, cQuery);
    return 1;
}

CMD:removekompensasi(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    if(!VoucherData[0][voucherExists]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kompensasi yang dikeluarkan oleh server!");

    VoucherData[0][voucherExists] = false;
    VoucherData[0][voucherFee] = 0;
    VoucherData[0][voucherTime] = 0;
    VoucherData[0][voucherID] = 0;
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menghapus kompensasi yang dikeluarkan server!", AccountData[playerid][pAdminname]);
    mysql_tquery(g_SQL, "DELETE FROM `voucher` WHERE `VoucherID`=0");
    return 1;
}

CMD:klaimkompensasi(playerid, params[])
{
    if(!VoucherData[0][voucherExists]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kompensasi yang dikeluarkan oleh server!");
    if(AccountData[playerid][pKompensasi]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah mengklaim kompensasi sebelumnya!");

    GiveMoney(playerid, VoucherData[0][voucherFee]);
    ShowItemBox(playerid, sprintf("Received %s", FormatMoney(VoucherData[0][voucherFee])), "Uang", 1212);
    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil mengklaim kompensasi sejumlah %s", FormatMoney(VoucherData[0][voucherFee])));
    AccountData[playerid][pKompensasi] = 1;
    return 1;
}

task KompensasiUpdate[1000]()
{
    if (!VoucherData[0][voucherExists] || VoucherData[0][voucherTime] == 0) 
        return 1;

    if (VoucherData[0][voucherTime] <= gettime()) 
    {
        VoucherData[0][voucherExists] = false;
        VoucherData[0][voucherTime] = 0;
        VoucherData[0][voucherID] = 0;

        mysql_tquery(g_SQL, "DELETE FROM `voucher` WHERE `VoucherID` = 0", "", "");
    }
    return 1;
}
