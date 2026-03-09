#include <YSI\y_hooks>

new 
    SapdMoney;

BrankasPolice_Save()
{
    new str[2024];
    
    format(str, sizeof str, "UPDATE brankas_police SET sapdmoney='%d' WHERE id=0", 
    SapdMoney);
    return mysql_tquery(g_SQL, str);
}

function LoadBrankasPolice()
{
    cache_get_value_name_int(0, "sapdmoney", SapdMoney);
    printf("[Brankas]: Loaded Brankas Police");
}

CMD:setbpolice(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);
    
    new jumlah, str[512];
    if(sscanf(params, "d", jumlah))
    {
        ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setbpolice [jumlah]");
        return 1;
    }

    format(str, sizeof str, "Berhasil mengisi brankas police dengan uang ~g~%s", FormatMoney(jumlah));
    ShowTDN(playerid, NOTIFICATION_SUKSES, str);
    SapdMoney = jumlah;
    BrankasPolice_Save();
    return 1;
}