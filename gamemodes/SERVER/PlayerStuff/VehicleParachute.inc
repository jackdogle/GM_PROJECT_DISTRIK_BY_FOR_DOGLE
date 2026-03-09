
CMD:buypara(playerid, params[])
{
    if(!IsPlayerInRangeOfPoint(playerid, 2.5, -2237.6846, -1743.9290, 480.8447)) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya bisa digunakan di point vehpara!");

    if(AccountData[playerid][pMoney] < 100) 
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup untuk skydive!");

    if(AccountData[playerid][pOwnPara] >= 5) // maksimal 5
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah parasut sudah maksimal (5)!");

    TakeMoney(playerid, 100);
    ShowItemBox(playerid, "Removed $100", "UANG", 1212);
    AccountData[playerid][pOwnPara]++; 
    Info(playerid, ""YELLOW"[Veh Para]: "WHITE"Kamu berhasil membeli parasut! Total parasut: %d", AccountData[playerid][pOwnPara]);
    Info(playerid, ""YELLOW"[Veh Para]: "WHITE"Gunakan "YELLOW"/vehpara "WHITE"untuk memasang parachute di kendaraan");

    return 1;
}

// CMD: Toggle Vehicle Parachute
CMD:vehpara(playerid, params[])
{
    new vid = GetPlayerVehicleID(playerid);

    if(!vid) 
    {
        ShowTDN(playerid,NOTIFICATION_ERROR,"Kamu harus berada di kendaraan!");
        return 1;
    }

    if(AccountData[playerid][pOwnPara] <= 0) 
    {
        ShowTDN(playerid,NOTIFICATION_ERROR,"Kamu belum punya parasut! Beli terlebih dahulu");
        return 1;
    }

    if(IsToggleVehicleParachute(vid))
    {
        ShowTDN(playerid,NOTIFICATION_ERROR,"Kendaraanmu sudah terpasang parasut");
        return 1;
    }

    if(!IsVehicleFlag(GetVehicleFlags(vid),VF_STREET))
    {
        ShowTDN(playerid,NOTIFICATION_ERROR,"Kendaraan ini tidak bisa dipasangi parasut");
        return 1;
    }

    ToggleVehicleParachute(vid,true);
    Info(playerid, ""YELLOW"[Veh Para]: "WHITE"Parasut kendaraan berhasil dipasang! Gunakan "YELLOW"H "WHITE"Jika ingin membuka parachute");
    
    AccountData[playerid][pOwnPara]--;
    Info(playerid, ""YELLOW"[Veh Para]: "WHITE"Sisa parasut: "YELLOW"%d", AccountData[playerid][pOwnPara]);

    return 1;
}

public OnVehicleParachuteThrown(playerid,vehicleid){
    GameTextForPlayer(playerid,"~g~Parachute has been thrown",2500,3);
    return 1;
}

public OnVehicleParachuteOpened(playerid,vehicleid){
    GameTextForPlayer(playerid,"~g~Parachute has been opened",2500,3);
    return 1;
}

public OnVehicleParachuteOpenFail(playerid,vehicleid){
    GameTextForPlayer(playerid,"~g~Cannot use parachute",2500,3);
    return 1;
}