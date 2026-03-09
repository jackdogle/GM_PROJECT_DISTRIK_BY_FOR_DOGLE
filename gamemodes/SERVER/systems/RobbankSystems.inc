#include <YSI\y_hooks>

new BankDoorObj = 0;
new BankBombObj = 0;

hook OnGameModeInit()
{
    SpawnDoorBank();
    LoadTextAreaRobbank();
    return 1;
}

forward SpawnDoorBank();
public SpawnDoorBank()
{
    if(BankDoorObj != 0) return 0;
    BankDoorObj = CreateDynamicObject(2634, 1410.341186, -1121.694946, 11.053359, -0.000004, -180.000000, 89.200256, -1, -1, -1, 300.00, 300.00); 
    CreateExplosion(1410.341186, -1121.694946, 11.053359, 12, 2.0);
    return 1;
}

stock LoadTextAreaRobbank()
{
    for(new i; i < 3; i++) Robbank_Robbed[i] = 2;
    for(new i; i < 3; i++) Robbank_TextCash[i] =  CreateDynamic3DTextLabel(""YELLOW"[Y] "WHITE"Untuk mengambil Gold Bank", -1, Robbank_AreaCash[i][0], Robbank_AreaCash[i][1], Robbank_AreaCash[i][2], 1.5);
    for(new i; i < 3; i++) CreateDynamic3DTextLabel(""YELLOW"[Y] "WHITE"Untuk menukarkan gold", -1, Robbank_Gold[i][0], Robbank_Gold[i][1], Robbank_Gold[i][2], 1.5);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_YES)) //YES
    {
        if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            if(IsPlayerInRangeOfPoint(playerid, 2.5, 1409.8170,-1121.5485,10.5234))
            {
                if(Inventory_Count(playerid, "Hacking Tools") < 1)
					return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Hacking Tools");

                if(Inventory_Count(playerid, "Bomb") < 1)
					return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Bomb");
                
                if(AccountData[playerid][pFamily] == -1) 
					return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya Anggota Family yang dapat Membobol bank!");
                
                if(RobbankColdown)
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Bank sedang cooldown. Tunggu beberapa saat lagi!");
                            
                ShowMinigamePH(playerid, "OnMinigamePHComplete", "RobbankProcces");
                return 1;
            }
        }
        for(new i; i < 3; i++) 
        {
            if(IsPlayerInRangeOfPoint(playerid, 1, Robbank_AreaCash[i][0], Robbank_AreaCash[i][1], Robbank_AreaCash[i][2]))
            {
                if(Robbank_Robbed[i] != 1) return 1;

                if(AccountData[playerid][pFamily] == -1) 
					return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya Anggota Family yang dapat Mengambil gold!");

                ApplyAnimation(playerid,"CAR_CHAT","CAR_Sc4_BL",4.0,1,1,1,0,0,0);
                AccountData[playerid][ActivityTime] = 1;
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL UANG BANK");
				ShowProgressBar(playerid);
                AccountData[playerid][RobbankCashTimer] = SetTimerEx("TakeCashBank", 1000, true, "ii", playerid, i);
            }
        }
        for(new i; i < 3; i++) 
        {
            if(IsPlayerInRangeOfPoint(playerid, 1, Robbank_Gold[i][0], Robbank_Gold[i][1], Robbank_Gold[i][2]))
            {
                if(AccountData[playerid][pFamily] == -1) 
					return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya Anggota Family yang dapat Menjual Gold!");

                new total = Inventory_Count(playerid, "Gold");
                new valuepay = total*888;
                if(Inventory_Count(playerid, "Gold") < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak mempunya gold!");

                Inventory_Remove(playerid, "Gold", total);
                ShowItemBox(playerid, sprintf("Remove %dx", total), "Gold", 2784);
                AccountData[playerid][pRedMoney] += valuepay;
                Info(playerid, "Anda berhasil menukarkan gold dan mendapatkan "RED"Redmoney "WHITE"sebesar "YELLOW"%d", valuepay);
                RemovePlayerAttachedObject(playerid, 9);
				DisablePlayerCheckpoint(playerid);
                IsCoordinatBankGold[playerid] = 0;
            }
        }
    } 
    return 1;
}

forward RobbankCash(playerid, rbID);
public RobbankCash(playerid, rbID)
{
    UpdateDynamic3DTextLabelText(Robbank_TextCash[rbID], -1, ""YELLOW"Gold "WHITE"has run out, "GRAY"Waiting to minute");
    Robbank_Robbed[rbID] = 0; //kosong

    ClearAnimations(playerid, true);
    StopLoopingAnim(playerid);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

    new rand = RandomEx(5, 10);

    if(IsCoordinatBankGold[playerid] != 1)
    {
        new randCP = random(3);
        
        switch(randCP)
        {
            case 0: SetPlayerCheckpoint(playerid, -1630.6548,-2240.2559,31.4766, 2.0);
            case 1: SetPlayerCheckpoint(playerid, -398.9006,-422.2060,16.2109, 2.0);
            case 2: SetPlayerCheckpoint(playerid, 2006.9318,2908.7336,47.8231, 2.0);
        }
    }
    SetPlayerAttachedObject(playerid, 9, 11745, 1, 0.038000, -0.099001, 0.003001, -108.399993, 17.399995, 50.399974, 0.920999, 1.393999, 1.000000);
    IsCoordinatBankGold[playerid] = 1;
    RobbankColdown = 1;
    RobbankColdownTimeLeft = 3600;

    Inventory_Add(playerid, "Gold", 2784, rand);
    ShowItemBox(playerid, sprintf("Recieved %dx", rand), "Gold", 2784);
    Info(playerid, "Anda berhasil mendapatkan gold sebesar "YELLOW"%d", rand);
    Info(playerid, "Silahkan ikutin cekpoint yang di map, Untuk menukarkan "YELLOW"gold "WHITE"anda!");

    if(AccountData[playerid][RobbankCashTimer] != -1)
    {
        KillTimer(AccountData[playerid][RobbankCashTimer]);
        AccountData[playerid][RobbankCashTimer] = -1;
    }
    AccountData[playerid][ActivityTime] = 0;
    HideProgressBar(playerid);

    RobbankTimer = SetTimer("CountdownBankColdown", 1000, true);
    SetTimer("ResetTextBank", 3600000, false);
}

forward CountdownBankColdown();
public CountdownBankColdown()
{
    if(RobbankColdown == 1)
    {
        RobbankColdownTimeLeft--;

        if(RobbankColdownTimeLeft <= 0)
        {
            RobbankColdown = 0;
            RobbankColdownTimeLeft = 0;
            KillTimer(RobbankTimer);
            return 1;
        }
    }
    return 1;
}

forward ResetTextBank();
public ResetTextBank()
{
    RobbankColdown = 0;
    RobbankColdownTimeLeft = 0;
    for(new i; i < 3; i++) Robbank_Robbed[i] = 2;
    for(new i; i < 3; i++) UpdateDynamic3DTextLabelText(Robbank_TextCash[i], -1, ""YELLOW"[Y] "WHITE"Untuk mengambil uang brankas");
}

CMD:delayrobbank(playerid, params[])
{
    new title[64] = ""TCRP"District  "WHITE"- Delay Robbank";
    new message[128];

    if(!RobbankColdown)
    {
        format(message, sizeof(message), ""GRAY"Bank dapat dibobol sekarang!");
    }
    else
    {
        new jam = RobbankColdownTimeLeft / 3600;
        new menit = (RobbankColdownTimeLeft % 3600) / 60;
        new detik = RobbankColdownTimeLeft % 60;
        format(message, sizeof(message), ""GRAY"Bank sedang cooldown.\nSisa waktu: "YELLOW"%d "WHITE"jam "YELLOW"%d "WHITE"menit "YELLOW"%d "WHITE"detik.", jam, menit, detik);
    }

    ShowPlayerDialog(playerid, DIALOG_CDROBBANK, DIALOG_STYLE_MSGBOX, title, message, "Tutup", "");
    return 1;
}

forward TakeCashBank(playerid, rbID);
public TakeCashBank(playerid, rbID)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(AccountData[playerid][RobbankCashTimer]);
        AccountData[playerid][RobbankCashTimer] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, Robbank_AreaCash[rbID][0], Robbank_AreaCash[rbID][1], Robbank_AreaCash[rbID][2]))
    {
        KillTimer(AccountData[playerid][RobbankCashTimer]);
        AccountData[playerid][RobbankCashTimer] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        Info(playerid, "Proses pengambilan gold dibatalkan karena kamu meninggalkan area bank!");
        return 0;
    }

    if(Robbank_Robbed[rbID] != 1)
    {
        KillTimer(AccountData[playerid][RobbankCashTimer]);
        AccountData[playerid][RobbankCashTimer] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 20) // 15 detik total
    {
        KillTimer(AccountData[playerid][RobbankCashTimer]);
        AccountData[playerid][RobbankCashTimer] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        RobbankCash(playerid, rbID);
    }
    else
    {
        AccountData[playerid][ActivityTime]++;
        
        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110.0 / 20.0;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward ProccesExplodeBank(playerid);
public ProccesExplodeBank(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTimerRobbank[playerid]);
        pTimerRobbank[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        BankDoorObj = 0;
        return 0;
    }
    if(AccountData[playerid][pInjured])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pTimerRobbank[playerid]);
        pTimerRobbank[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        BankDoorObj = 0;

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    }
    if(AccountData[playerid][ActivityTime] >= 10)
    {
        KillTimer(pTimerRobbank[playerid]);
        pTimerRobbank[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        Info(playerid, "Berhasil memasang bomb di gerbang. Bank akan meledak dalam waktu 5 detik!");
        BankBombObj = CreateDynamicObject(1636, 1410.09, -1121.7, 11.4834, 0, 0, -89, -1, -1, -1, 300.00, 300.00); 
        SetTimerEx("ExplodeBankDoor", 5000, false, "i", playerid);
    }
    else
    {
        AccountData[playerid][ActivityTime] ++;

        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/10;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward ExplodeBankDoor(playerid);
public ExplodeBankDoor(playerid)
{
    if(BankDoorObj != 0)
    {
        new Float:ox, Float:oy, Float:oz;
        GetDynamicObjectPos(BankDoorObj, ox, oy, oz);

        DestroyDynamicObject(BankBombObj);
        DestroyDynamicObject(BankDoorObj);
        BankDoorObj = 0;

        CreateExplosion(ox, oy, oz, 12, 0.0);          // pusat
        CreateExplosion(ox+1.5, oy, oz, 14, 0.0);      // samping kanan
        CreateExplosion(ox-1.5, oy, oz, 14, 0.0);      // samping kiri
        CreateExplosion(ox, oy+1.5, oz, 12, 0.0);      // depan
        CreateExplosion(ox, oy-1.5, oz, 14, 0.0);      // belakang
        CreateExplosion(ox+0.8, oy+0.8, oz, 12, 0.0);  // sudut
        CreateExplosion(ox-0.8, oy-0.8, oz, 14, 0.0);  // sudut
        CreateExplosion(ox+0.5, oy-0.5, oz, 12, 0.0);  // variasi kecil

        Info(playerid, "Pintu berhasil di ledakan, segera ambil semua uang yang ada di brankas!");
        SendClientMessageToAll(-1, "{db7b00}============ PERHATIAN ============");
		SendClientMessageToAll(-1, "Telah Terjadinya perampokan Bank Besar "TCRP"District"); 
		SendClientMessageToAll(-1, "{db1700}Catatan: {ffffff}Seluruh warga harap menjauh dari lokasi perampokan!"); 
		SendClientMessageToAll(-1, "{db7b00}===================================");
        
        for(new i = 0; i < 3; i++) Robbank_Robbed[i] = 1; // pecah
        SetTimer("SpawnDoorBank", 3600000, false);
    }
    return 1;
}