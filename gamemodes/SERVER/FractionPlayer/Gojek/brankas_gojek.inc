// INI ADALAH BRANKAS GOJEK KORUP YA KONTOL

new 
    MoneyGojek;

BrankasGojek_Save()
{
    new sstr[712];
    format(sstr, sizeof sstr, "UPDATE brankas_gojek SET moneygojek='%d' WHERE id=0",
    MoneyGojek);
    return mysql_tquery(g_SQL, sstr);
}

function LoadBrankasGojek()
{
    cache_get_value_name_int(0, "moneygojek", MoneyGojek);
    printf("[Brankas] Loaded brankas PT GOJEK...");
}

CMD:setbgojek(playerid, params[])
{
    if(AccountData[playerid][pAdmin] >= 7)
    {
        new jumlah, str[512];
        if(sscanf(params, "d", jumlah))
        {
            ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setbgojek [jumlah]");
            return 1;
        }

        MoneyGojek = jumlah;
        BrankasGojek_Save();
        format(str, sizeof str, "Anda mengeset brankas gojek sejumlah %s", FormatMoney(jumlah));
        ShowTDN(playerid, NOTIFICATION_SUKSES, str);
    }
    return 1;
}