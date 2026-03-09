    #include <YSI\y_hooks>
    enum e_notify
    {
        notifyIcon,
        notifyMessage[320],
        notifySize
    }
    new NotifInfo[MAX_PLAYERS][4][e_notify];
    new MaxPlayerNotify[MAX_PLAYERS];
    new PlayerText: notifyTextdraws[MAX_PLAYERS][4*10];
    new NotifIndex[MAX_PLAYERS];

    forward NotifyHide(playerid);
    public NotifyHide(playerid)
    {
        if(!NotifIndex[playerid]) return 1;
        -- NotifIndex[playerid];
        MaxPlayerNotify[playerid] --;
        for (new i = -1; ++ i < 10;) PlayerTextDrawDestroy(playerid, notifyTextdraws[playerid][(NotifIndex[playerid] * 10) + i]);
        return 1;
    }


ShowTDN(playerid, notifid, text[])
{
    if(AccountData[playerid][pStyleNotif] == 1) // TD
    {
        switch(notifid)
        {
            case NOTIFICATION_ERROR:
            {
                if(MaxPlayerNotify[playerid] >= 4) return false;
                PlayerPlaySound(playerid, 1085, 0, 0, 0);
                ShowNotify(playerid, text, 2);
            }
            case NOTIFICATION_INFO:
            {
                if(MaxPlayerNotify[playerid] >= 4) return false;
                PlayerPlaySound(playerid, 1139, 0, 0, 0);
                ShowNotify(playerid, text, 1);
            }
            case NOTIFICATION_SUKSES:
            {
                if(MaxPlayerNotify[playerid] >= 4) return false;
                PlayerPlaySound(playerid, 5203, 0, 0, 0);
                ShowNotify(playerid, text, 3);
            }
            case NOTIFICATION_SYNTAX:
            {
                if(MaxPlayerNotify[playerid] >= 4) return false;
                PlayerPlaySound(playerid, 5201, 0, 0, 0);
                ShowNotify(playerid, text, 4);
            }
            case NOTIFICATION_WARNING:
            {
                if(MaxPlayerNotify[playerid] >= 4) return false;
                PlayerPlaySound(playerid, 4203, 0, 0, 0);
                ShowNotify(playerid, text, 5);
            }
        }
    }
    else if(AccountData[playerid][pStyleNotif] == 2)
    {
        switch(notifid)
        {
            case NOTIFICATION_ERROR:
            {
                Error(playerid, "%s", text);
            }
            case NOTIFICATION_INFO:
            {
                Info(playerid, "%s", text);
            }
            case NOTIFICATION_SUKSES:
            {
                Info(playerid, "%s", text);
            }
            case NOTIFICATION_SYNTAX:
            {
                Syntax(playerid, "%s", text);
            }
            case NOTIFICATION_WARNING:
            {
                Warning(playerid, "%s", text);
            }
        }
    }
    return 1;
}

/*stock ShowTDN(playerid, notifid, pesan[])
{
    switch(notifid)
    {
        case NOTIFICATION_ERROR:
		{
            if(MaxPlayerNotify[playerid] >= 4) return false;
			PlayerPlaySound(playerid, 1085, 0, 0, 0);
			ShowNotify(playerid, pesan, 2);
		}
		case NOTIFICATION_INFO:
		{
            if(MaxPlayerNotify[playerid] >= 4) return false;
			PlayerPlaySound(playerid, 1139, 0, 0, 0);
			ShowNotify(playerid, pesan, 1);
		}
		case NOTIFICATION_SUKSES:
		{
            if(MaxPlayerNotify[playerid] >= 4) return false;
			PlayerPlaySound(playerid, 5203, 0, 0, 0);
			ShowNotify(playerid, pesan, 3);
		}
		case NOTIFICATION_SYNTAX:
		{
            if(MaxPlayerNotify[playerid] >= 4) return false;
			PlayerPlaySound(playerid, 5201, 0, 0, 0);
			ShowNotify(playerid, pesan, 4);
		}
		case NOTIFICATION_WARNING:
		{
            if(MaxPlayerNotify[playerid] >= 4) return false;
			PlayerPlaySound(playerid, 4203, 0, 0, 0);
			ShowNotify(playerid, pesan, 5);
		}
    }
    return 1;
}*/

stock ShowNotify(playerid, message[], icon)
{
    if(MaxPlayerNotify[playerid] >= 4) return 1;
    MaxPlayerNotify[playerid] ++;
    for (new x = -1; ++ x < NotifIndex[playerid] && x < 4;)
    {
        for (new i = -1; ++ i < 10;) PlayerTextDrawDestroy(playerid, notifyTextdraws[playerid][(x * 10) + i]);
        NotifInfo[playerid][NotifIndex[playerid] - x] = NotifInfo[playerid][(NotifIndex[playerid] - x) - 1];
    }
    format(NotifInfo[playerid][0][notifyMessage], 320, "%s", message);
    NotifInfo[playerid][0][notifyIcon] = icon;
    NotifInfo[playerid][0][notifySize] = 3;

    ++ NotifIndex[playerid];
    new Float: new_x = 0.0;
    for (new x = -1; ++ x < NotifIndex[playerid];)
    {
        CreateNotify(playerid, x, x * 10, new_x);
        new_x += (NotifInfo[playerid][x][notifySize] * 7.25) + 25.0;
    }
    SetTimerEx("NotifyHide", 2000, false, "d", playerid);
    return 1;
}

CreateNotify(playerid, index, i, Float:new_x)
{
    new lines = NotifInfo[playerid][index][notifySize];
    new Float:x = (lines * 10) + new_x;
    new Float:newpos = x - 25.0;
    if(NotifInfo[playerid][index][notifyIcon] == 1)
    {
        notifyTextdraws[playerid][i] = CreatePlayerTextDraw(playerid, 529.000, 202.000+newpos, "LD_SPAC:white");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 90.000, 23.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 527.000, 196.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 14.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 607.000, 196.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 12.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 607.000, 219.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 12.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 527.000, 219.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 12.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 534.000, 198.000+newpos, "LD_SPAC:white");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 80.000, 31.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 526.000, 194.000+newpos, "LD_POOL:ball");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 14.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 16744447);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 532.000, 194.000+newpos, "/");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.349, 0.999);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 533.000, 198.000+newpos, "/");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], -0.270, 0.499);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 543.000, 204.000+newpos, NotifInfo[playerid][index][notifyMessage]);
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.133, 0.949);
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 600.000, 21.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);
    }
    if(NotifInfo[playerid][index][notifyIcon] == 2)
    {
        notifyTextdraws[playerid][i] = CreatePlayerTextDraw(playerid, 491.000, 114.000+newpos, "LD_SPAC:white");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 113.000, 35.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 488.500, 107.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 14.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 592.500, 107.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 12.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 592.500, 143.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 12.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 489.000, 143.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 12.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 494.000, 109.000+newpos, "LD_SPAC:white");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 106.000, 44.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 493.000, 111.000+newpos, "LD_POOL:ball");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 14.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -2147483393);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 496.000, 112.000+newpos, "/");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.388, 0.798);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 502.000, 112.000+newpos, "/");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], -0.429, 0.799);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 506.000, 121.000+newpos, NotifInfo[playerid][index][notifyMessage]);
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.133, 0.949);
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 600.000, 21.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);
    }
    if(NotifInfo[playerid][index][notifyIcon] == 3)
    {
        notifyTextdraws[playerid][i] = CreatePlayerTextDraw(playerid, 491.000, 114.000+newpos, "LD_SPAC:white");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 113.000, 35.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 488.500, 107.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 14.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 592.500, 107.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 12.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 592.500, 143.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 12.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 489.000, 143.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 12.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 494.000, 109.000+newpos, "LD_SPAC:white");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 106.000, 44.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 493.000, 111.000+newpos, "LD_POOL:ball");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 14.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 16744447);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 499.000, 111.000+newpos, "/");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.349, 0.999);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 501.000, 116.000+newpos, "/");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], -0.270, 0.499);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 506.000, 121.000+newpos, NotifInfo[playerid][index][notifyMessage]);
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.133, 0.949);
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 600.000, 21.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);
    }
    if(NotifInfo[playerid][index][notifyIcon] == 4)
    {
        notifyTextdraws[playerid][i] = CreatePlayerTextDraw(playerid, 491.000, 114.000+newpos, "LD_SPAC:white");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 113.000, 35.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 488.500, 107.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 14.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 592.500, 107.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 12.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 592.500, 143.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 12.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 489.000, 143.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 12.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 494.000, 109.000+newpos, "LD_SPAC:white");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 106.000, 44.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 493.000, 111.000+newpos, "LD_POOL:ball");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 14.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 1768516095);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 498.000, 114.000+newpos, "/");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.388, 0.798);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 501.000, 114.000+newpos, "/");
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], -0.250, 0.499);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 506.000, 121.000+newpos, NotifInfo[playerid][index][notifyMessage]);
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.133, 0.949);
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 600.000, 21.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);
    }
    if(NotifInfo[playerid][index][notifyIcon] == 5)
    {
        notifyTextdraws[playerid][i] = CreatePlayerTextDraw(playerid, 491.000, 114.000+newpos, "LD_SPAC:white");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 113.000, 35.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 488.500, 107.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 14.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 592.500, 107.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 12.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 592.500, 143.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 12.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 489.000, 143.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 12.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 494.000, 109.000+newpos, "LD_SPAC:white");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 106.000, 44.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], 6143);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 493.000, 111.000+newpos, "LD_POOL:ball");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 14.000, 14.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -65281);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 499.000, 115.000+newpos, "LD_SPAC:white");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 1.000, 7.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 498.000, 112.000+newpos, "LD_BEAT:chit");
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 3.000, 3.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 255);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);

        notifyTextdraws[playerid][++i] = CreatePlayerTextDraw(playerid, 506.000, 121.000+newpos, NotifInfo[playerid][index][notifyMessage]);
        PlayerTextDrawLetterSize(playerid, notifyTextdraws[playerid][i], 0.133, 0.949);
        PlayerTextDrawTextSize(playerid, notifyTextdraws[playerid][i], 600.000, 21.000);
        PlayerTextDrawAlignment(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawColor(playerid, notifyTextdraws[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, notifyTextdraws[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, notifyTextdraws[playerid][i], 150);
        PlayerTextDrawFont(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, notifyTextdraws[playerid][i], 1);
        PlayerTextDrawShow(playerid, notifyTextdraws[playerid][i]);
    }
}