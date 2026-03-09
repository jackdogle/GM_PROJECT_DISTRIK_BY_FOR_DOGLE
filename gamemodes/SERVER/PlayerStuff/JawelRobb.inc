//Stock (Pasang di paling Bawah / Bebas setelah CMD apapun itu)

stock GameModeClearJewelry()
{
    format(JewelryHack_Command, 50, "_");
    JewelryHack_IsOpened = false;
    for(new i; i < 6; i++) JewelryHack_Hack[i] = 0; //1 = berhasil, 0 = gagal / belum
    JewelryHack_Timer = 0;
    JewelryHack_HackSuccess = 0;
    JewelryHack_TimerCount = 0;
    JewelryHack_Timer = -1;
    JewelryHack_CommandRunning = false;
    JewelryHack_CommandChecked = false;
    JewelryHack_Completed = false;
    JewelryHack_Alarm = true; //alarm masih nyala
    JewelryHack_Player = -1;
}

stock ClearJewelryHackDisconnect(playerid)
{
    format(JewelryHack_Command, 50, "_");
    JewelryHack_IsOpened = false;
    for(new i; i < 6; i++) JewelryHack_Hack[i] = 0; //1 = berhasil, 0 = gagal / belum
    JewelryHack_Timer = 0;
    JewelryHack_HackSuccess = 0;
    JewelryHack_TimerCount = 0;
    KillTimer(JewelryHack_Timer);
    JewelryHack_Timer = -1;
    JewelryHack_CommandRunning = false;
    JewelryHack_CommandChecked = false;
    JewelryHack_Player = -1;

    for(new i; i < 9; i++) PlayerTextDrawDestroy(playerid, JewelryHackPTD[playerid][i]);
    for(new i; i < 13; i++) TextDrawHideForPlayer(playerid, JewelryHackTD[i]);
    CancelSelectTextDraw(playerid);
}

stock ClearFailJewelryHack()
{
    for(new i; i < 6; i++) JewelryHack_Hack[i] = 0;
    JewelryHack_Timer = 0;
    JewelryHack_HackSuccess = 0;
    JewelryHack_TimerCount = 0;
    JewelryHack_Timer = -1;
    JewelryHack_CommandRunning = false;
    JewelryHack_CommandChecked = false;

    // for(new i = 0; i < 9; i++) 
    // {
    //     PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][i], "_");
    //     PlayerTextDrawHide(playerid, JewelryHackPTD[playerid][i]);
    // }
}

stock ShowJewelryHack(playerid)
{
    LoadPlayerJewelryHackTD(playerid);
    for(new i; i < 13; i++) TextDrawShowForPlayer(playerid, JewelryHackTD[i]);
    SelectTextDraw(playerid, COLOR_BLUE); //putih
}

stock JewelryHackAllDone()
{
    for(new i = 0; i < 5; i++)
    {
        if(JewelryHack_Hack[i] != 1)
        {
            return 0;
        }
    }
    return 1;
}

forward StartHackJewelry(playerid);
public StartHackJewelry(playerid)
{
    if(strcmp("/close", JewelryHack_Command)  == 0)
    {
        ClearJewelryHackDisconnect(playerid);
        return 1;
    }

    if(JewelryHack_CommandChecked != true) return 1;
    if(JewelryHack_CommandRunning != false) return 1;

    if(strcmp("/hack", JewelryHack_Command) != 0)
    {
        ClearFailJewelryHack();
        return PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][8], "~r~Wrong_Command_-_Try_Again");
    }

    if(JewelryHack_Alarm == false)
    {
        ClearFailJewelryHack();
        return PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][8], "~r~The_alarm_has_already_been_turned_off_for_1_minutes.");
    }

    JewelryHack_Player = playerid; //save pemain yang sedang ngehack
    JewelryHack_Timer = SetTimerEx("TimerHackJewelry", 1000, true, "i", playerid);

    PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][8], "Hacking...");
    format(JewelryHack_Command, 50, "_");
    PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][7], "_");
    JewelryHack_CommandRunning = true;
    return 1;
}

forward TimerHackJewelry(playerid);
public TimerHackJewelry(playerid)
{
    JewelryHack_TimerCount++;

    // Lebih cepat: trigger setelah 6 tick (sebelumnya 10)
    if (JewelryHack_TimerCount >= 5)
    {
        if (JewelryHackAllDone())
        {
            KillTimer(JewelryHack_Timer);
            PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][6], "The_alarm_is_turned_~r~off_for_1_minutes.");
            PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][JewelryHack_HackSuccess], "Hacking..._Success");
            JewelryHack_Alarm = false; // alarm mati
            JewelryHack_Completed = true;
            Info(playerid, "Alarm jewel berhasil dihack! segera hancurkan kaca Jewel mengunakan baseball sebelum "BLUE"Polisi "WHITE"datang!");

            ShowItemBox(playerid, "Removed 1x", "Hacking Tools", 19893);
            Inventory_Remove(playerid, "Hacking Tools", 1);
            ClearFailJewelryHack();

            SetTimer("JewelryAlarmDelay", 60000, false); // 1 menit = 1800 detik * 1000
        }
        else
        {
            JewelryHack_TimerCount = 0;

            // Aturan chance yang lebih mudah: 10% gagal, 90% sukses
            if (JewelryHack_HackSuccess == 0)
            {
                if (JewelryHack_Hack[0] == 0)
                {
                    new rand = random(99); // 0..99

                    // Gagal jika rand < 10 -> 10% chance
                    if (rand < 10)
                    {
                        JewelryHack_Hack[0] = 0;
                        PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][8], "Hacking...~r~Failed-_Try_Again");
                        KillTimer(JewelryHack_Timer);
                        ClearFailJewelryHack();
                        return 1;
                    }
                    else
                    {
                        JewelryHack_Hack[0] = 1;
                        PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][8], "Hacking..._Success");
                        JewelryHack_HackSuccess = 1;
                        PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][1], "Hacking...");
                    }
                }
            }
            else
            {
                if (JewelryHack_Hack[JewelryHack_HackSuccess] == 0)
                {
                    new rand = random(99); // 0..99

                    if (rand < 10) // 10% gagal
                    {
                        JewelryHack_Hack[JewelryHack_HackSuccess] = 0;
                        PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][JewelryHack_HackSuccess], "Hacking...~r~Failed-_Try_Again");
                        KillTimer(JewelryHack_Timer);
                        ClearFailJewelryHack();
                        return 1;
                    }
                    else
                    {
                        JewelryHack_Hack[JewelryHack_HackSuccess] = 1;
                        new new_JewelryHack_HackSuccess = JewelryHack_HackSuccess + 1;
                        PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][JewelryHack_HackSuccess], "Hacking..._Success");

                        JewelryHack_HackSuccess = new_JewelryHack_HackSuccess;
                        PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][new_JewelryHack_HackSuccess], "Hacking...");
                    }
                }

            }
        }
    }
    return 1;
}

forward JewelryAlarmDelay();
public JewelryAlarmDelay()
{
    // Alarm nyala kembali
    JewelryHack_Alarm = true;
}

forward ResetTextJewelry();
public ResetTextJewelry()
{
    // Reset 3D Text semua jewelry ke "Filled"
	for(new i; i < 24; i++) Jewelry_Robbed[i] = 2;
	for(new i; i < 24; i++) UpdateDynamic3DTextLabelText(Jewelry_RobbedText[i], -1, "{32ff24}Filled");
}

forward RobJewelry(playerid, jwID);
public RobJewelry(playerid, jwID)
{
    UpdateDynamic3DTextLabelText(Jewelry_RobbedText[jwID], -1, "{e10000}Empty");
    Jewelry_Robbed[jwID] = 0; //kosong

    new rand = RandomEx(1, 6);

    isRobbing_Jewelry[playerid] = 0;
    isHaveJewelry[playerid] += rand;

    ClearAnimations(playerid, true);
    StopLoopingAnim(playerid);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

    if(isCoordinat_ChangeJewelry[playerid] != 1)
    {
        new randCP = random(3);
        
        switch(randCP)
        {
            case 0: SetPlayerCheckpoint(playerid, 297.5253,-169.6326,1.5781, 5.0);
            case 1: SetPlayerCheckpoint(playerid, -2434.1377,2293.4856,4.9844, 5.0);
            case 2: SetPlayerCheckpoint(playerid, -300.4551,2658.3723,63.1989, 5.0);
        }
    }
    SetPlayerAttachedObject(playerid, 9, 11745, 1, 0.038000, -0.099001, 0.003001, -108.399993, 17.399995, 50.399974, 0.920999, 1.393999, 1.000000);
    isCoordinat_ChangeJewelry[playerid] = 1;

    SendClientMessageEx(playerid, -1, "{e1c900}Anda mendapatkan {32ff24}%d Jewelry", rand);
    SendClientMessageEx(playerid, -1, "{e1c900}Untuk menukarkannya, ikuti checkpoint");
    SetTimer("ResetTextJewelry", 3600000, false);
}


forward UsingRobJewelry(playerid, jwID);
public UsingRobJewelry(playerid, jwID)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(AccountData[playerid][RobJewelryTimer]);
        AccountData[playerid][RobJewelryTimer] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        isRobbing_Jewelry[playerid] = 0;
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 15) // 15 detik total
    {
        KillTimer(AccountData[playerid][RobJewelryTimer]);
        AccountData[playerid][RobJewelryTimer] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        RobJewelry(playerid, jwID);
    }
    else
    {
        AccountData[playerid][ActivityTime]++;
        
        static Float:progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 110.0 / 15.0;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}