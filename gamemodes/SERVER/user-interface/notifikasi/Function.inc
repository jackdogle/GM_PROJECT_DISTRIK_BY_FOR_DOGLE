timer TimerHideTDN[2000](playerid)
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        if(TextDrawsNotification[playerid][cycle][notifyHide] == -1)
        {
            TextDrawsNotification[playerid][cycle][notifyUse] = 0;
            if(TextDrawsNotification[playerid][cycle][notifyTextDraw] != PlayerText:-1)
            {
                PlayerTextDrawDestroys(playerid, TextDrawsNotification[playerid][cycle][notifyTextDraw]);
                TextDrawsNotification[playerid][cycle][notifyLine] = 0;
                TextDrawsNotification[playerid][cycle][notifyText][0] = EOS;
                TextDrawsNotification[playerid][cycle][notifyMinPosY] = 0;
                TextDrawsNotification[playerid][cycle][notifyMaxPosY] = 0;
                TextDrawsNotification[playerid][cycle][notifyTextDraw] = PlayerText:-1;
                TextDrawsNotification[playerid][cycle][notifyTime] = 100;
                forex(txd, 5)
                {
                    PlayerTextDrawDestroys(playerid, TextDrawsNotification[playerid][cycle][textdraw_notification][txd]);
                    TextDrawsNotification[playerid][cycle][textdraw_notification][txd] = PlayerText:-1;
                }
            }
            TextDrawsNotification[playerid][cycle][notifyHide] = -1;
            UpdateTDN(playerid);

            return 1;
        }
    }
    return 0;
}


JavaTR:ShowTDN(playerid, type, const reason[])
{
    if (AccountData[playerid][pStyleNotif] == 1)
    {
        for(new cycle; cycle < MAX_TDN; cycle++)
        {
            if(!TextDrawsNotification[playerid][cycle][notifyUse])
            {
                TextDrawsNotification[playerid][cycle][notifyText][0] = EOS;

                new text[MAX_TDN_TEXT];

                for(new len = strlen(reason), pos; pos < len; pos ++)
                {
                    switch(reason[pos])
                    {
                        // case ' ': text[pos] = '_';
                        case '`': text[pos] = 177;
                        case '&': text[pos] = 38;
                        default:  text[pos] = reason[pos];
                    }
                }
                
                strcat(TextDrawsNotification[playerid][cycle][notifyText], text, MAX_TDN_TEXT);
                TextDrawsNotification[playerid][cycle][notifyTime] = 100;
                TextDrawsNotification[playerid][cycle][notifymode] = type;
    
                TextDrawsNotification[playerid][cycle][notifyUse] = 1;
    
                LinesTDN(playerid, cycle);

                #if defined TDN_MODE_DOWN

                MinPosYTDN(playerid, cycle);
                MaxPosYTDN(playerid, cycle);

                #endif

                #if defined TDN_MODE_UP

                MaxPosYTDN(playerid, cycle);
                MinPosYTDN(playerid, cycle);
                
                #endif

                TextDrawsNotification[playerid][cycle][notifyHide] = -1;

                CreateTDN(playerid, type, cycle);
                switch(type)
                {
                    case NOTIFICATION_ERROR: PlayerPlaySound(playerid, 1085, 0, 0, 0);
                    case NOTIFICATION_SUKSES: PlayerPlaySound(playerid, 5203, 0, 0, 0);
                    case NOTIFICATION_WARNING: PlayerPlaySound(playerid, 4203, 0, 0, 0);
                    case NOTIFICATION_SYNTAX: PlayerPlaySound(playerid, 5201, 0, 0, 0);
                    case NOTIFICATION_INFO: PlayerPlaySound(playerid, 1139, 0, 0, 0);
                }

                defer TimerHideTDN[TDN_TIME](playerid);
                //SetTimerEx("TimerProcess", TDN_TIME / 1, true "i", playerid);

                return 1;
            }
        }
    }
    else
    {
        switch(type)
        {
            case NOTIFICATION_ERROR:
            {
                Error(playerid, "%s", reason);
            }
            case NOTIFICATION_INFO:
            {
                Info(playerid, "%s", reason);
            }
            case NOTIFICATION_SUKSES:
            {
                Info(playerid, "%s", reason);
            }
            case NOTIFICATION_SYNTAX:
            {
                Syntax(playerid, "%s", reason);
            }
            case NOTIFICATION_WARNING:
            {
                Warning(playerid, "%s", reason);
            }
        }
        return 1;
    }
    return -1;
}

JavaTR:ShowTDN_Manual(playerid, type, const reason[])
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        if(!TextDrawsNotification[playerid][cycle][notifyUse])
        {
            TextDrawsNotification[playerid][cycle][notifyText][0] = EOS;

            new text[MAX_TDN_TEXT];

            for(new len = strlen(reason), pos; pos < len; pos ++)
            {
                switch(reason[pos])
                {
                    default:  text[pos] = reason[pos];
                }
            }

            strcat(TextDrawsNotification[playerid][cycle][notifyText], text, MAX_TDN_TEXT);
            TextDrawsNotification[playerid][cycle][notifymode] = type;
 
            TextDrawsNotification[playerid][cycle][notifyUse] = 1;
 
            LinesTDN(playerid, cycle);

            #if defined TDN_MODE_DOWN

            MinPosYTDN(playerid, cycle);
            MaxPosYTDN(playerid, cycle);

            #endif

            #if defined TDN_MODE_UP

            MaxPosYTDN(playerid, cycle);
            MinPosYTDN(playerid, cycle);
            
            #endif

            CreateTDN(playerid, type, cycle);

            for(new i; i < MAX_TDN; i++)
            {
                if(used(playerid, notifycounter[playerid]))
                {
                    if(notifycounter[playerid] == MAX_TDN - 1) notifycounter[playerid] = 0;
                    else notifycounter[playerid]++;
                }
                else break;
            }

            new TDN = notifycounter[playerid];

            TextDrawsNotification[playerid][cycle][notifyHide] = TDN;

            if(notifycounter[playerid] == MAX_TDN - 1) notifycounter[playerid] = 0;
            else notifycounter[playerid]++;

            return TDN;
        }
    }
    return -1;
}

stock used(playerid, id)
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        if(TextDrawsNotification[playerid][cycle][notifyHide] == id) return 1;
    }
    return 0;
}

JavaTR:hideTDN(playerid, TDN)
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        if(TextDrawsNotification[playerid][cycle][notifyHide] == TDN)
        {
            TextDrawsNotification[playerid][cycle][notifyUse] = 0;
            if(TextDrawsNotification[playerid][cycle][notifyTextDraw] != PlayerText:-1)
            {
                PlayerTextDrawDestroys(playerid, TextDrawsNotification[playerid][cycle][notifyTextDraw]);
                TextDrawsNotification[playerid][cycle][notifyLine] = 0;
                TextDrawsNotification[playerid][cycle][notifyText][0] = EOS;
                TextDrawsNotification[playerid][cycle][notifyMinPosY] = 0;
                TextDrawsNotification[playerid][cycle][notifyMaxPosY] = 0;
                TextDrawsNotification[playerid][cycle][notifyTextDraw] = PlayerText:-1;
                TextDrawsNotification[playerid][cycle][notifyTime] = 100;
                forex(txd, 5)
                {
                    PlayerTextDrawDestroys(playerid, TextDrawsNotification[playerid][cycle][textdraw_notification][txd]);
                    TextDrawsNotification[playerid][cycle][textdraw_notification][txd] = PlayerText:-1;
                }
            }
            TextDrawsNotification[playerid][cycle][notifyHide] = -1;
            UpdateTDN(playerid);
            return 1;
        }
    }
    return 0;
}

stock UpdateTDN(playerid)
{
    for(new cycle = 0; cycle < MAX_TDN; cycle ++)
    {
        if(!TextDrawsNotification[playerid][cycle][notifyUse])
        {
            if(cycle != MAX_TDN - 1)
            {
                if(TextDrawsNotification[playerid][cycle + 1][notifyUse])
                {
                    TextDrawsNotification[playerid][cycle][notifyUse] = TextDrawsNotification[playerid][cycle + 1][notifyUse];
                    TextDrawsNotification[playerid][cycle][notifyLine] = TextDrawsNotification[playerid][cycle + 1][notifyLine];
                    strcat(TextDrawsNotification[playerid][cycle][notifyText], TextDrawsNotification[playerid][cycle + 1][notifyText], MAX_TDN_TEXT);
                    TextDrawsNotification[playerid][cycle][notifymode] = TextDrawsNotification[playerid][cycle + 1][notifymode];
                    TextDrawsNotification[playerid][cycle][notifyTextDraw] = TextDrawsNotification[playerid][cycle + 1][notifyTextDraw];
                    TextDrawsNotification[playerid][cycle][notifyHide] = TextDrawsNotification[playerid][cycle + 1][notifyHide];
                    TextDrawsNotification[playerid][cycle][notifyTime] = TextDrawsNotification[playerid][cycle + 1][notifyTime];

                    TextDrawsNotification[playerid][cycle + 1][notifyUse] = 0;
                    TextDrawsNotification[playerid][cycle + 1][notifyLine] = 0;
                    TextDrawsNotification[playerid][cycle + 1][notifyText][0] = EOS;
                    TextDrawsNotification[playerid][cycle + 1][notifyTextDraw] = PlayerText:-1;
                    TextDrawsNotification[playerid][cycle + 1][notifyMinPosY] = 0;
                    TextDrawsNotification[playerid][cycle + 1][notifyMaxPosY] = 0;
                    TextDrawsNotification[playerid][cycle + 1][notifyHide] = -1;
                    TextDrawsNotification[playerid][cycle + 1][notifymode] = -1;
                    TextDrawsNotification[playerid][cycle + 1][notifyTime] = 100;

                    forex(txd, 5)
                    {
                        TextDrawsNotification[playerid][cycle][textdraw_notification][txd] = TextDrawsNotification[playerid][cycle + 1][textdraw_notification][txd];
                        TextDrawsNotification[playerid][cycle + 1][textdraw_notification][txd] = PlayerText:-1;
                    }

                    #if defined TDN_MODE_DOWN

                    MinPosYTDN(playerid, cycle);
                    MaxPosYTDN(playerid, cycle);
                    
                    #endif

                    #if defined TDN_MODE_UP
                    
                    MaxPosYTDN(playerid, cycle);
                    MinPosYTDN(playerid, cycle);
                    
                    #endif       
                }
            }
        }
        else if(TextDrawsNotification[playerid][cycle][notifyUse])
        {
            if(cycle != 0)
            {
                if(!TextDrawsNotification[playerid][cycle - 1][notifyUse])
                {
                    TextDrawsNotification[playerid][cycle - 1][notifyUse] = TextDrawsNotification[playerid][cycle][notifyUse];
                    TextDrawsNotification[playerid][cycle - 1][notifyLine] = TextDrawsNotification[playerid][cycle][notifyLine];
                    strcat(TextDrawsNotification[playerid][cycle - 1][notifyText], TextDrawsNotification[playerid][cycle][notifyText], MAX_TDN_TEXT);
                    TextDrawsNotification[playerid][cycle - 1][notifymode] = TextDrawsNotification[playerid][cycle][notifymode];
                    TextDrawsNotification[playerid][cycle - 1][notifyTextDraw] = TextDrawsNotification[playerid][cycle][notifyTextDraw];
                    TextDrawsNotification[playerid][cycle - 1][notifyHide] = TextDrawsNotification[playerid][cycle][notifyHide];
                    TextDrawsNotification[playerid][cycle - 1][notifyTime] = TextDrawsNotification[playerid][cycle][notifyTime];

                    TextDrawsNotification[playerid][cycle][notifyUse] = 0;
                    TextDrawsNotification[playerid][cycle][notifyLine] = 0;
                    TextDrawsNotification[playerid][cycle][notifyText][0] = EOS;
                    TextDrawsNotification[playerid][cycle][notifymode] = -1;
                    TextDrawsNotification[playerid][cycle][notifyTextDraw] = PlayerText:-1;
                    TextDrawsNotification[playerid][cycle][notifyMinPosY] = 0;
                    TextDrawsNotification[playerid][cycle][notifyMaxPosY] = 0;
                    TextDrawsNotification[playerid][cycle][notifyHide] = -1;
                    TextDrawsNotification[playerid][cycle][notifyTime] = 100;

                    forex(txd, 5)
                    {
                        TextDrawsNotification[playerid][cycle - 1][textdraw_notification][txd] = TextDrawsNotification[playerid][cycle][textdraw_notification][txd];
                        TextDrawsNotification[playerid][cycle][textdraw_notification][txd] = PlayerText:-1;
                    }

                    #if defined TDN_MODE_DOWN

                    MinPosYTDN(playerid, cycle - 1);
                    MaxPosYTDN(playerid, cycle - 1);
                    
                    #endif

                    #if defined TDN_MODE_UP
                    
                    MaxPosYTDN(playerid, cycle - 1);
                    MinPosYTDN(playerid, cycle - 1);
                    
                    #endif
                }
            }
        }
        CreateTDN(playerid, TextDrawsNotification[playerid][cycle][notifymode], cycle);
    }
    return 1;
}

stock MinPosYTDN(playerid, TDN)
{
    #if defined TDN_MODE_DOWN

    if(TDN == 0)
    {
        TextDrawsNotification[playerid][TDN][notifyMinPosY] = TDN_POS_Y;
    }
    else
    {
        TextDrawsNotification[playerid][TDN][notifyMinPosY] = TextDrawsNotification[playerid][TDN - 1][notifyMaxPosY] + TDN_DISTANCE;
    }
    return 1;

    #endif

    #if defined TDN_MODE_UP

    TextDrawsNotification[playerid][TDN][notifyMinPosY] = TextDrawsNotification[playerid][TDN][notifyMaxPosY] - ((TDN_LETTER_SIZE_Y * 2) + 2) - ((TDN_LETTER_SIZE_Y * 5.75) * TINGGI_BOX) - ((TINGGI_BOX - 1) * ((TDN_LETTER_SIZE_Y * 2) + 2 + TDN_LETTER_SIZE_Y)) - (TDN_LETTER_SIZE_Y + 3);
    return 1;

    #endif
}

stock MaxPosYTDN(playerid, TDN)
{
    #if defined TDN_MODE_DOWN

    TextDrawsNotification[playerid][TDN][notifyMaxPosY] = TextDrawsNotification[playerid][TDN][notifyMinPosY] + (TDN_LETTER_SIZE_Y * 2) + 2 + (TDN_LETTER_SIZE_Y * 5.75 * TINGGI_BOX) + ((TINGGI_BOX - 1) * ((TDN_LETTER_SIZE_Y * 2) + 2 + TDN_LETTER_SIZE_Y)) + TDN_LETTER_SIZE_Y + 3;
    return 1;

    #endif

    #if defined TDN_MODE_UP

    if(TDN == 0)
    {
        TextDrawsNotification[playerid][TDN][notifyMaxPosY] = TDN_POS_Y;
    }
    else
    {
        TextDrawsNotification[playerid][TDN][notifyMaxPosY] = TextDrawsNotification[playerid][TDN - 1][notifyMinPosY] - TDN_DISTANCE;
    }
    return 1;

    #endif
}

stock LinesTDN(playerid, TDN)
{
    new lines = 1, Float:width, lastspace = -1, supr, len = strlen(TextDrawsNotification[playerid][TDN][notifyText]);
 
    for(new i = 0; i < len; i ++)
    {
        if(TextDrawsNotification[playerid][TDN][notifyText][i] == '~')
        {
            if(supr == 0)
            {
                supr = 1;
                if(TextDrawsNotification[playerid][TDN][notifyText][i+2] != '~') SendClientMessage(playerid, -1, "Error: '~' used incorrectly'");
            }
            else if(supr == 1) supr = 0;
        }
        else
        {
            if(supr == 1)
            {
                if(TextDrawsNotification[playerid][TDN][notifyText][i] == 'n')
                {
                    lines ++;
                    lastspace = -1;
                    width = 0;
                }
            }
            else
            {
                if(TextDrawsNotification[playerid][TDN][notifyText][i] == ' ') lastspace = i;
 
                width += TDN_LETTER_SIZE_X * GetTextDrawCharacterWidth(TextDrawsNotification[playerid][TDN][notifyText][i], TDN_FONT, bool:TDN_PROPORTIONAL);

                if(width > TDN_SIZE - 3)
                {
                    if(lastspace != i && lastspace != -1)
                    {
                        lines ++;
                        i = lastspace;
                        lastspace = -1;
                        width = 0;
                    }
                    else
                    {
                        lines ++;
                        lastspace = -1;
                        width = 0;
                    }
                }
            }
        }
    }
    
    TextDrawsNotification[playerid][TDN][notifyLine] = lines;
 
    return 1;
}

stock PlayerTextDrawDestroys(playerid, PlayerText:textid)
{
    if(IsValidDynamicPlayerTextDraw(playerid, PlayerText:textid))
        PlayerTextDrawDestroy(playerid, PlayerText:textid);
    return 1;
}

stock CreateTDN(playerid, type, TDN)
{
    if(TextDrawsNotification[playerid][TDN][notifyUse] == 1)
    {
        TextDrawsNotification[playerid][TDN][notifyWidth] = 0.0;
        TextDrawsNotification[playerid][TDN][notifymode] = type;
        if(TextDrawsNotification[playerid][TDN][notifyTextDraw] != PlayerText:-1)
        {
            if(IsValidDynamicPlayerTextDraw(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw]))
                PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw]);
            forex(txd, 5)
            {
                if(IsValidDynamicPlayerTextDraw(playerid, PlayerText:TextDrawsNotification[playerid][TDN][textdraw_notification][txd]))
                    PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][txd]);
            }
        }
        new lines = 1, supr, len = strlen(TextDrawsNotification[playerid][TDN][notifyText]);
 
        for(new i = 0; i < len; i ++)
        {
            if(TextDrawsNotification[playerid][TDN][notifyText][i] == '~')
            {
                if(supr == 0)
                {
                    supr = 1;
                    if(TextDrawsNotification[playerid][TDN][notifyText][i+2] != '~') SendClientMessage(playerid, -1, "Error: '~' used incorrectly'");
                }
                else if(supr == 1) supr = 0;
            }
            else
            {
                if(supr == 1)
                {
                    if(TextDrawsNotification[playerid][TDN][notifyText][i] == 'n')
                    {
                        lines ++;
                        TextDrawsNotification[playerid][TDN][notifyWidth] = 0;
                    }
                }
                else
                {
                    TextDrawsNotification[playerid][TDN][notifyWidth] += TDN_LETTER_SIZE_X * GetTextDrawCharacterWidth(TextDrawsNotification[playerid][TDN][notifyText][i], TDN_FONT, bool:TDN_PROPORTIONAL);
                }
            }
        }

        new row = TDN + 1;
        
        if(TextDrawsNotification[playerid][TDN][notifyWidth] < 200.0000)
        {
            if(TextDrawsNotification[playerid][TDN][notifyWidth] == 200)
            {
                TextDrawsNotification[playerid][TDN][notifyGanjil] = true;
            }
            else
            {
                if((row % 2) == 0) TextDrawsNotification[playerid][TDN][notifyGanjil] = false;
                else TextDrawsNotification[playerid][TDN][notifyGanjil] = true;
            }

            TextDrawsNotification[playerid][TDN][notifyWidth] += 10.0000;
        }
        else
        {
            TextDrawsNotification[playerid][TDN][notifyGanjil] = true;
        }

        new color;

        switch(type)
        {
            case NOTIFICATION_ERROR:
            {
                color = -1052226817;
            }
            case NOTIFICATION_SUKSES:
            {
                color = 1018393087;
            }
            case NOTIFICATION_WARNING:
            {
                color = -626712321;
            }
            case NOTIFICATION_SYNTAX:
            {
                color = -2139062017;
            }
            case NOTIFICATION_INFO:
            {
                color = 1097458175;
            }
        }
        if(TextDrawsNotification[playerid][TDN][notifyGanjil])
        {
            if(TDN > 1)
            {
                new Float:kurangi;
                if(!TextDrawsNotification[playerid][TDN - 1][notifyGanjil])
                {
                    kurangi += 30.0000;
                }
                if(!TextDrawsNotification[playerid][TDN - 2][notifyGanjil])
                {
                    kurangi += 30.0000;
                }
                TextDrawsNotification[playerid][TDN][notifyMinPosY] = TextDrawsNotification[playerid][TDN][notifyMinPosY] - kurangi;

                TextDrawsNotification[playerid][TDN][textdraw_notification][0] = CreatePlayerTextDraw(playerid, 342.000000, TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - -1.000000), "ld_beat:chit");
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 4);
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0.600000, 2.000000);
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 3.000000, 23.000000);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], color);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 255);
                PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 50);
                PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
                PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);

                TextDrawsNotification[playerid][TDN][textdraw_notification][1] = CreatePlayerTextDraw(playerid, 343.000000, TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 3.000000), "ld_bum:blkdot");
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 4);
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0.600000, 2.000000);
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], (TextDrawsNotification[playerid][TDN][notifyWidth] / 1.8) + 3.0, 15.000000);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], color);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 572732415);
                PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 50);
                PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
                PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);

                TextDrawsNotification[playerid][TDN][textdraw_notification][2] = CreatePlayerTextDraw(playerid, 344.000000, TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 3.000000), "ld_bum:blkdot");
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 4);
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0.600000, 2.000000);
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], TextDrawsNotification[playerid][TDN][notifyWidth] / 1.8, 15.000000);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 255);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 572732415);
                PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 50);
                PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
                PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);

                TextDrawsNotification[playerid][TDN][textdraw_notification][3] = CreatePlayerTextDraw(playerid, 345.000000, TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 4.000000), "ld_beat:chit");
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 4);
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0.600000, 2.000000);
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 11.000000, 13.500000);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], color);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 255);
                PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 50);
                PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
                PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);

                TextDrawsNotification[playerid][TDN][textdraw_notification][4] = CreatePlayerTextDraw(playerid, 349.000000, TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 6.000000), "i");
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0.254166, 0.900000);
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 400.000000, 17.000000);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 255);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 255);
                PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 50);
                PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
                PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);

                TextDrawsNotification[playerid][TDN][notifyTextDraw] = CreatePlayerTextDraw(playerid, 358.000000, TextDrawsNotification[playerid][TDN][notifyMinPosY], TextDrawsNotification[playerid][TDN][notifyText]);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 1);
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0.120833, 0.700000);
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 675.000000, 17.000000);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], -1);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 255);
                PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 50);
                PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 1);
                PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0);
            }
            else
            {
                TextDrawsNotification[playerid][TDN][textdraw_notification][0] = CreatePlayerTextDraw(playerid, 342.000000, TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - -1.000000), "ld_beat:chit");
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 4);
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0.600000, 2.000000);
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 3.000000, 23.000000);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], color);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 255);
                PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 50);
                PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
                PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);

                TextDrawsNotification[playerid][TDN][textdraw_notification][1] = CreatePlayerTextDraw(playerid, 343.000000, TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 3.000000), "ld_bum:blkdot");
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 4);
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0.600000, 2.000000);
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], (TextDrawsNotification[playerid][TDN][notifyWidth] / 1.8) + 3.0, 15.000000);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], color);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 572732415);
                PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 50);
                PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
                PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);

                TextDrawsNotification[playerid][TDN][textdraw_notification][2] = CreatePlayerTextDraw(playerid, 344.000000, TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 3.000000), "ld_bum:blkdot");
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 4);
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0.600000, 2.000000);
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], TextDrawsNotification[playerid][TDN][notifyWidth] / 1.8, 15.000000);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 255);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 572732415);
                PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 50);
                PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
                PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);

                TextDrawsNotification[playerid][TDN][textdraw_notification][3] = CreatePlayerTextDraw(playerid, 345.000000, TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 4.000000), "ld_beat:chit");
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 4);
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0.600000, 2.000000);
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 11.000000, 13.500000);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], color);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 255);
                PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 50);
                PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
                PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);

                TextDrawsNotification[playerid][TDN][textdraw_notification][4] = CreatePlayerTextDraw(playerid, 349.000000, TextDrawsNotification[playerid][TDN][notifyMinPosY] - (TDN_POS_Y - 6.000000), "i");
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0.254166, 0.900000);
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 400.000000, 17.000000);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 255);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 255);
                PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 50);
                PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
                PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);

                TextDrawsNotification[playerid][TDN][notifyTextDraw] = CreatePlayerTextDraw(playerid, 358.000000, TextDrawsNotification[playerid][TDN][notifyMinPosY], TextDrawsNotification[playerid][TDN][notifyText]);
                PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 1);
                PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0.120833, 0.700000);
                PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 675.000000, 17.000000);
                PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0);
                PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0);
                PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 1);
                PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], -1);
                PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 255);
                PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 50);
                PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0);
                PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 1);
                PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0);
            }
        }
        else
        {
            //
            TextDrawsNotification[playerid][TDN][textdraw_notification][0] = CreatePlayerTextDraw(playerid, 342.000000 + ((TextDrawsNotification[playerid][TDN - 1][notifyWidth] / 1.8) + 5.0000), TextDrawsNotification[playerid][TDN - 1][notifyMinPosY] - (TDN_POS_Y - -1.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 3.000000, 23.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], color);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][1] = CreatePlayerTextDraw(playerid, 343.000000 + ((TextDrawsNotification[playerid][TDN - 1][notifyWidth] / 1.8) + 5.0000), TextDrawsNotification[playerid][TDN - 1][notifyMinPosY] - (TDN_POS_Y - 3.000000), "ld_bum:blkdot");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], (TextDrawsNotification[playerid][TDN][notifyWidth] / 1.8) + 3.0, 15.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], color);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 572732415);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][2] = CreatePlayerTextDraw(playerid, 344.000000 + ((TextDrawsNotification[playerid][TDN - 1][notifyWidth] / 1.8) + 5.0000), TextDrawsNotification[playerid][TDN - 1][notifyMinPosY] - (TDN_POS_Y - 3.000000), "ld_bum:blkdot");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], TextDrawsNotification[playerid][TDN][notifyWidth] / 1.8, 15.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 255);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 572732415);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][3] = CreatePlayerTextDraw(playerid, 345.000000 + ((TextDrawsNotification[playerid][TDN - 1][notifyWidth] / 1.8) + 5.0000), TextDrawsNotification[playerid][TDN - 1][notifyMinPosY] - (TDN_POS_Y - 4.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 11.000000, 13.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], color);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][4] = CreatePlayerTextDraw(playerid, 349.000000 + ((TextDrawsNotification[playerid][TDN - 1][notifyWidth] / 1.8) + 5.0000), TextDrawsNotification[playerid][TDN - 1][notifyMinPosY] - (TDN_POS_Y - 6.000000), "i");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0.254166, 0.900000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 400.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 255);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);

            TextDrawsNotification[playerid][TDN][notifyTextDraw] = CreatePlayerTextDraw(playerid, 358.000000 + ((TextDrawsNotification[playerid][TDN - 1][notifyWidth] / 1.8) + 5.0000), TextDrawsNotification[playerid][TDN - 1][notifyMinPosY], TextDrawsNotification[playerid][TDN][notifyText]);
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 1);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0.120833, 0.700000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 675.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], -1);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw], 0);
        }

        forex(txd, 5)
        {
            PlayerTextDrawShow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][txd]);
        }
        PlayerTextDrawShow(playerid, TextDrawsNotification[playerid][TDN][notifyTextDraw]);
    }
    return 1;
}
