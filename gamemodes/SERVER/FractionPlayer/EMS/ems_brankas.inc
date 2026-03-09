// INI ADALAH BRANKAS EMS YA ANJING
new 
    MoneySamd,
    Medkit,
    PillStress,
    Bandage,
    Float:PosBrankasEms[3],
    BrankasVirtual,
    BrankasInterior;

BrankasEms_Save()
{
    new sstr[1056];
    format(sstr, sizeof sstr, "UPDATE brankas_ems SET moneysamd='%d',medkit='%d',pillstress='%d',bandage='%d', virtualems='%d', interiorems='%d', posx='%f', posy='%f', posz='%f'  WHERE id=0",
    MoneySamd, Medkit, PillStress, Bandage, BrankasVirtual, BrankasInterior, PosBrankasEms[0], PosBrankasEms[1], PosBrankasEms[2]);
    return mysql_tquery(g_SQL, sstr);
}

function LoadBrankasEms()
{
    cache_get_value_name_int(0, "moneysamd", MoneySamd);
    cache_get_value_name_int(0, "medkit", Medkit);
    cache_get_value_name_int(0, "pillstress", PillStress);
    cache_get_value_name_int(0, "bandage", Bandage);

    cache_get_value_name_int(0, "virtualems", BrankasVirtual);
    cache_get_value_name_int(0, "interiorems", BrankasInterior);

    cache_get_value_float(0, "posx", PosBrankasEms[0]);
    cache_get_value_float(0, "posy", PosBrankasEms[1]);
    cache_get_value_float(0, "posz", PosBrankasEms[2]);
	printf("[Brankas] Loaded Data Kedokteran...");
}

CMD:setbems(playerid, params[])
{
    if(AccountData[playerid][pAdmin] == 7)
    {
        new jumlah, str[128];
        if(sscanf(params, "d", jumlah))
        {
            ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setbems [amount]");
            return 1;
        }

        MoneySamd = jumlah;
        Medkit = jumlah;
        PillStress = jumlah;
        Bandage = jumlah;
        BrankasEms_Save();

        format(str, sizeof str, "Berhasil mengeset Brankas Ems Sejumlah %d", jumlah);
        ShowTDN(playerid, NOTIFICATION_SUKSES, str);
    }
    return 1;
}