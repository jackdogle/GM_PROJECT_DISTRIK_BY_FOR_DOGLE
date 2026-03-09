#include <YSI\y_hooks>

hook OnPlayerDisconnect(playerid, reason)
{
    forex(i, 3)
    {
        PlayerTextDrawDestroy(playerid, PlayerTextdraws[playerid][textdraw_taxi][i]);
    }
    return 1;
}

IsPlayerInsideTaxi(playerid)
{
    new vehicleid = GetPlayerVehicleID(playerid);

    if(GetVehicleModel(vehicleid) == 420 || GetVehicleModel(vehicleid) == 438 || GetVehicleModel(vehicleid) == 561 || GetVehicleModel(vehicleid) == 405)
    {
        foreach(new i : Player)
        {
            if((i != playerid) && (AccountData[i][pFaction] == FACTION_TRANS && AccountData[i][pDutyTrans] && AccountData[i][pTaxiDuty] && GetPlayerState(i) == PLAYER_STATE_DRIVER) && GetPlayerVehicleID(i) == vehicleid)
            {
                return 1;
            }
        }
    }
    return 0;
}

LeaveTaxi(playerid, driverid)
{
    if(driverid != INVALID_PLAYER_ID && IsPlayerConnected(driverid))
    {
        TakeMoney(playerid, AccountData[playerid][pTaxiFee]);
        GiveMoney(driverid, AccountData[playerid][pTaxiFee]);

        SendCustomMessage(playerid, "[Trans Argo]", "Anda telah membayar "GREEN"%s"WHITE" kepada pengemudi Trans", FormatMoney(AccountData[playerid][pTaxiFee]));
        SendCustomMessage(driverid, "[Trans Argo]", "Anda mendapat bayaran "GREEN"%s"WHITE" dari "YELLOW"%s(%d)"WHITE" sebagai penumpang Trans", FormatMoney(AccountData[playerid][pTaxiFee]), ReturnName(playerid), playerid);

        AccountData[playerid][pTaxiFee] = 0;
        AccountData[playerid][pTaxiPlayer] = INVALID_PLAYER_ID;
        AccountData[playerid][pTaxiRunDistance] = 0;
    }
    return 1;
}

Taxi_GUI(playerid, bool:mode)
{
    if(mode)
    {
        PlayerTextDrawShow(playerid, PlayerTextdraws[playerid][textdraw_taxi][0]);
        PlayerTextDrawShow(playerid, PlayerTextdraws[playerid][textdraw_taxi][1]);
        PlayerTextDrawShow(playerid, PlayerTextdraws[playerid][textdraw_taxi][2]);
    }
    else
    {   
        PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][textdraw_taxi][0]);
        PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][textdraw_taxi][1]);
        PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][textdraw_taxi][2]);
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_TRANSORDER:
        {
            if(!response) return 1;
            if(AccountData[playerid][pTaxiPlayer] != INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang menjadi penumpang di Trans!");

            new Float:x, Float:y, Float:z;
            GetPlayerPos(playerid, x, y, z);
            if(isnull(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_TRANSORDER, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Pesan Transportasi",
                "Error: Tidak dapat diisi kosong!\nHai, kamu mau diantar kemana hari ini?", "Input", "Batal");
                return 1;
            }

            if(IsNumeric(inputtext))
            {
                ShowPlayerDialog(playerid, DIALOG_TRANSORDER, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Pesan Transportasi",
                "Error: Tidak dapat diisi angka!\nHai, kamu mau diantar kemana hari ini?", "Input", "Batal");
                return 1;
            }

            foreach(new i : Player) if (AccountData[i][pFaction] == FACTION_TRANS && AccountData[i][pDutyTrans])
            {
                SendCustomMessage(i, "[Trans Request]", "Client: "YELLOW"(id: %d) %s"WHITE" Telp: "LIGHTGREEN"%s"WHITE" Lok: "SKYBLUE"%s", playerid, ReturnName(playerid), AccountData[playerid][pPhone], GetLocation(x, y, z));
                SendCustomMessage(i, "[Pesan]", "[ "ORANGE"%s"WHITE" ]", inputtext);
                SendCustomMessage(i, "NOTE", "Gunakan Command "YELLOW"'/accept taxi [client id]'"WHITE" untuk merespon panggilan");
            }
            AccountData[playerid][pTaxiOrder] = 1;
            SetPVarFloat(playerid, "pX", x);
            SetPVarFloat(playerid, "pY", y);
            SetPVarFloat(playerid, "pZ", z);
            ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil memesan Transportasi");
        }
    }
    return 1;
}

CMD:taxiduty(playerid, params[])
{
    if(AccountData[playerid][pFaction] != FACTION_TRANS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Transportasi District !");
    if(!AccountData[playerid][pDutyTrans]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus duty Trans terlebih dahulu!");
    if(!IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus mengemudikan kendaraan menggunakan ini!");

    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 420 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 438 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 405)
    {
        if(!AccountData[playerid][pTaxiDuty])
        {
            AccountData[playerid][pTaxiDuty] = 1;
            Info(playerid, "Anda telah "GREEN"Mengaktifkan"WHITE" argo");
            Taxi_GUI(playerid, true);
        }
        else
        {
            AccountData[playerid][pTaxiDuty] = 0;
            Info(playerid, "Anda telah "RED"Menonaktifkan"WHITE" argo");
            Taxi_GUI(playerid, false);
        }
    }
    else ShowTDN(playerid, NOTIFICATION_ERROR, "Ini bukan kendaraan Trans!");
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_ONFOOT && oldstate == PLAYER_STATE_DRIVER)
    {
        if(AccountData[playerid][pDutyTrans] && AccountData[playerid][pTaxiDuty] && AccountData[playerid][pFaction] == FACTION_TRANS)
        {
            /*foreach (new i : Player) if (AccountData[i][pTaxiPlayer] == playerid && IsPlayerInVehicle(i, GetPlayerVehicleID(playerid))) {
                LeaveTaxi(i, playerid);
            }*/

            Taxi_GUI(playerid, false);
        }
    }
    if(newstate == PLAYER_STATE_DRIVER && AccountData[playerid][pFaction] == FACTION_TRANS)
    {
        if(AccountData[playerid][pDutyTrans] && AccountData[playerid][pTaxiDuty])
        {
            if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 420 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 438 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 405)
            {
                Taxi_GUI(playerid, true);
            }
        }
    }
    if(newstate == PLAYER_STATE_PASSENGER && IsPlayerInsideTaxi(playerid)) 
    {
        if(AccountData[playerid][pMoney] < 1)
        {
            RemovePlayerFromVehicle(playerid);
            SendClientMessageEx(playerid, X11_ORANGE1, "Taxi: "WHITE"Keluar dari taxi, uang yang anda miliki tidak mencukupi!");
            return 1;
        }
        new driverid = GetVehicleDriver(GetPlayerVehicleID(playerid));

        AccountData[playerid][pTaxiFee] = 0;
        AccountData[playerid][pTaxiPlayer] = driverid;

        Info(driverid, ""YELLOW"%s(%d)"WHITE" masuk sebagai penumpang.", ReturnName(playerid), playerid);
        Info(playerid, "Anda memasuki taxi milik "YELLOW"%s(%d)", ReturnName(driverid), driverid);
        GetPlayerPos(playerid, AccountData[playerid][tPos][0], AccountData[playerid][tPos][1], AccountData[playerid][tPos][2]);
    }
    if(oldstate == PLAYER_STATE_PASSENGER && AccountData[playerid][pTaxiFee] > 0 && AccountData[playerid][pTaxiPlayer] != INVALID_PLAYER_ID)
    {
        LeaveTaxi(playerid, AccountData[playerid][pTaxiPlayer]);
        forex(i, 3) PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][textdraw_taxi][i]);
    }
    return 1;
}

ptask Player_TaxiUpdate[1000](playerid)
{
    if (!SQL_IsCharacterLogged(playerid))
        return 0;

    static Float:bonusDistance = 100.0;
    static fareIncrement = 30;
    static bonusAmount = 150;
    static maxRunDistance = 5;

    new earned = 0;

    // Taxi GUI Display
    if (AccountData[playerid][pFaction] == FACTION_TRANS && AccountData[playerid][pDutyTrans])
    {
        new vehicleID = GetPlayerVehicleID(playerid);
        foreach (new i : Player)
        {
            if (IsPlayerInVehicle(i, vehicleID) && AccountData[i][pTaxiPlayer] == playerid)
            {
                earned += AccountData[i][pTaxiFee];
            }
        }
        PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][textdraw_taxi][2], FormatMoney(earned));
    }

    if (IsPlayerInsideTaxi(playerid))
    {
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);

        new Float:distance = GetDistanceBetweenPoints(AccountData[playerid][tPos][0], AccountData[playerid][tPos][1], AccountData[playerid][tPos][2], x, y, z);

        if (distance > bonusDistance)
        {
            // Update posisi terakhir dan tambahkan tarif
            AccountData[playerid][tPos][0] = x;
            AccountData[playerid][tPos][1] = y;
            AccountData[playerid][tPos][2] = z;

            AccountData[playerid][pTaxiFee] += fareIncrement;

            if (++AccountData[playerid][pTaxiRunDistance] == maxRunDistance)
            {
                GiveMoney(AccountData[playerid][pTaxiPlayer], bonusAmount);
                Info(AccountData[playerid][pTaxiPlayer], "Anda mendapatkan bonus $150 dari pemerintah untuk 100 meter perjalanan.");
                AccountData[playerid][pTaxiRunDistance] = 0;
            }
        }

        new formattedMoney[32];
        format(formattedMoney, sizeof(formattedMoney), "%s", FormatMoney(AccountData[playerid][pTaxiFee]));

        for (new i = 0; i < 3; i++)
        {
            PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][textdraw_taxi][2], formattedMoney);
            PlayerTextDrawShow(playerid, PlayerTextdraws[playerid][textdraw_taxi][i]);
        }
    }
    return 1;
}


/*CMD:122(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid)) return 0;
    
    new notes[125];
    if(sscanf(params, "s[125]", notes)) return Syntax(playerid, "/122 [mau diantar kemana?]");
    if(strlen(params) < 0) return Error(playerid, "Pesan tidak dapat kosong!");
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    foreach(new i : Player) if (AccountData[i][pJob] == JOB_TAXI && AccountData[i][pJobDuty])
    {
        SendCustomMessage(i, "[Taxi Request]", "Client: "YELLOW"(id: %d) %s"WHITE" Telp: "LIGHTGREEN"%s"WHITE" Lok: "SKYBLUE"%s", playerid, ReturnName(playerid), AccountData[playerid][pPhone], GetLocation(x, y, z));
        SendCustomMessage(i, "[Message]", "[ "ORANGE"%s"WHITE" ]", notes);
        SendCustomMessage(i, "NOTE", "Gunakan Command "YELLOW"'/accept taxi [client id]'"WHITE" untuk merespon panggilan");
    }
    AccountData[playerid][pTaxiOrder] = 1;
    SetPVarFloat(playerid, "pX", x);
    SetPVarFloat(playerid, "pY", y);
    SetPVarFloat(playerid, "pZ", z);
    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil memesan Taxi, tunggu respon driver!");
    return 1;
}

CMD:jobduty(playerid, params[])
{
    if(AccountData[playerid][pJob] != JOB_TAXI)
        return Error(playerid, "Anda bukan seorang supir taxi!");
    
    if(AccountData[playerid][pInjured])
        return Error(playerid, "Anda tidak dapat duty ketika sedang pingsan!");
    
    if(AccountData[playerid][pMaskOn])
        return Error(playerid, "Lepas topeng terlebih dahulu!");
    
    if(AccountData[playerid][pJobDuty])
    {
        AccountData[playerid][pJobDuty] = 0;
        Taxi_GUI(playerid, false);
        Info(playerid, "Anda sekarang "RED"Off Duty"WHITE" sebagai taxi driver");
    }
    else
    {
        new modelid = GetVehicleModel(GetPlayerVehicleID(playerid));

        if(modelid != 420 && modelid != 438)
            return Error(playerid, "Kamu harus didalam kendaraan taxi!");
        
        if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
            return Error(playerid, "Anda harus menjadi Driver jika ingin Duty Taxi!");
        
        foreach (new i : Player) if (AccountData[i][pTaxiPlayer] == playerid && IsPlayerInVehicle(i, GetPlayerVehicleID(playerid))) {
            LeaveTaxi(i, playerid);
        }

        Info(playerid, "Anda sekarang "GREEN"On Duty"WHITE" sebagai taxi driver");

        Taxi_GUI(playerid, true);
        AccountData[playerid][pJobDuty] = 1;
    }
    return 1;
}*/
