#include <YSI_Coding\y_hooks>

new SelectedGift[MAX_PLAYERS];
new InviteTarget[MAX_PLAYERS];
new PlayerID[MAX_PLAYERS];

hook OnPlayerConnect(playerid)
{
    InviteTarget[playerid] = 0;
    SelectedGift[playerid] = 0;
    PlayerID[playerid] = playerid;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    InviteTarget[playerid] = 0;
    SelectedGift[playerid] = 0;
    return 1;
}

IsPlayerNearPartner(playerid)
{
    foreach(new i : Player)
    {
        if (i != playerid)
        {
            if (AccountData[playerid][pPartnerID] > 0 && AccountData[playerid][pID] == AccountData[i][pPartnerID])
            {
                return i;
            }
        }
    }
    return -1;
}

IsPlayerNearCouple(playerid)
{
    new Float: love = AccountData[playerid][pLove];
    foreach(new i : Player) 
    {
        if (i != playerid)
        {
            if (AccountData[playerid][pPartnerID] > 0 && AccountData[playerid][pID] == AccountData[i][pPartnerID])
            {
                GetPlayerPos(i, AccountData[i][pPosX], AccountData[i][pPosY], AccountData[i][pPosZ]);
                if (IsPlayerInRangeOfPoint(playerid, 5.0, AccountData[i][pPosX], AccountData[i][pPosY], AccountData[i][pPosZ]))
                {
                    SetPlayerLove(playerid, love+0.5);
                }
            }
        }
    }
    return 1;
}

task IsPartnerNear[60000]()
{
    foreach(new i : Player)
    {
        IsPlayerNearCouple(i);
    }
    return 1;
}

SetPlayerLove(playerid, Float:love)
{
    AccountData[playerid][pLove] = love;

    if(AccountData[playerid][pLove] > 100)
        AccountData[playerid][pLove] = 100;

    else if(AccountData[playerid][pLove] < 0)
        AccountData[playerid][pLove] = 0;
    return 1;
}

Dialog:RelationInformation(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                new output[600], partnername[32], Float:partnerlove, Float:totalpercentage;
                new partnerID = AccountData[playerid][pPartnerID];
                new Float:playerlove = AccountData[playerid][pLove];
                new Cache:checkname = mysql_query(g_SQL, sprintf("SELECT `PartnerName` FROM `users` WHERE `pID` = '%d' LIMIT 1;",AccountData[playerid][pID]));
                if(cache_num_rows())
                {
                    cache_get_value_name(0, "PartnerName", partnername, 32);
                    cache_delete(checkname);
                }

                new Cache:checklove = mysql_query(g_SQL, sprintf("SELECT `Love` FROM `users` WHERE `pID` = '%d' LIMIT 1;", AccountData[playerid][pPartnerID]));
                if(cache_num_rows())
                {
                    cache_get_value_name_float(0, "Love", partnerlove);
                    cache_delete(checklove);
                }
                totalpercentage = (playerlove/2) + (partnerlove/2);

                format(output, sizeof(output), ""WHITE"["LIGHTGREEN"Relationship Status"WHITE"]\n\n");
                format(output, sizeof(output), "%s"WHITE"Nama Partner : "RED"%s (%d)\n", output, partnername, partnerID);
                if(AccountData[playerid][pStatus] == 1) 
                {
                    format(output, sizeof(output), "%s"WHITE"Status : "LIGHTGREEN"Dating\n", output); 
                } 
                else if(AccountData[playerid][pStatus] == 2) 
                {
                    format(output, sizeof(output), "%s"WHITE"Status : "LIGHTGREEN"Married\n", output);  
                }
                format(output, sizeof(output), "%s"WHITE"Love Percentage : "YELLOW"%.2f%%\n", output, totalpercentage);

                Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""TCRP"District "WHITE" - Status Hubungan", output, "Close", "");
            }
            case 1:
            {
                new gift_time = SelectedGift[playerid];
                if(gettime() < gift_time)
			        return ShowTDN(playerid, NOTIFICATION, "Kamu perlu menunggu 1x24 jam untuk mengirim hadiah lain!");

                new targetid = IsPlayerNearPartner(playerid);
  
                if(IsPlayerConnected(targetid))
                {
                    if(targetid != INVALID_PLAYER_ID && targetid != playerid && IsPlayerInRangeOfPoint(playerid, 5.0, AccountData[targetid][pPos][0], AccountData[targetid][pPos][1], AccountData[targetid][pPos][2]))
                    { 
                        SetPlayerLove(playerid, AccountData[playerid][pLove]+10);
                        SetPlayerLove(targetid, AccountData[targetid][pLove]+10);
                        new gift_date = gettime() + 86400;
                        mysql_tquery(g_SQL, sprintf("UPDATE `users` SET `PartnerGift` = '%d' WHERE pID = %d;", gift_date, AccountData[playerid][pID]));
                        mysql_tquery(g_SQL, sprintf("UPDATE `users` SET `PartnerGift` = '%d' WHERE pID = %d;", gift_date, AccountData[targetid][pID]));
                        SendCustomMessage(playerid, "Relation", "You send a "RED"gift "WHITE"to your "YELLOW"partner!");
                        SendCustomMessage(targetid, "Relation", "You just receive a "RED"gift "WHITE"from your "YELLOW"partner!");
                    }
                    else ShowTDN(playerid, NOTIFICATION, "You're not close enough to your partner!");
                }
                else
                {
                    new partnerlove;
                    new Cache:checkaccount = mysql_query(g_SQL, sprintf("SELECT `Love` FROM `users` WHERE `pID` = '%d' LIMIT 1;",AccountData[playerid][pPartnerID]));
                    if(cache_num_rows())
                    {
                        cache_get_value_name_int(0, "Love", partnerlove);
                        cache_delete(checkaccount);
                    }
                    SendCustomMessage(playerid, "Relation", "You send a "RED"gift "WHITE"to your "YELLOW"partner when they're not in the city!");
                    SetPlayerLove(playerid, AccountData[playerid][pLove]+10);
                    //Ngeupdate partnergift time nya untuk keduanya
                    new gift_date = gettime() + 86400;
                    mysql_tquery(g_SQL, sprintf("UPDATE `users` SET `PartnerGift` = '%d' WHERE pID = %d;", gift_date, AccountData[playerid][pID]));
                    //Ngeupdate partnertgift timenya ketika offline
                    mysql_tquery(g_SQL, sprintf("UPDATE `users` SET `PartnerGift` = '%d' WHERE pID = %d;", gift_date, AccountData[playerid][pPartnerID]));
                    //Ngeupdate love si partnernya kalau offline
                    mysql_tquery(g_SQL, sprintf("UPDATE `users` SET `Love` = '%d' WHERE pID = %d;", partnerlove+10, AccountData[playerid][pPartnerID]));
                }                
            }
            case 2:
            {
                Dialog_Show(playerid, RelationInvites, DIALOG_STYLE_INPUT, ""TCRP"District "WHITE" - Relation Invite", ""RED"[PERINGATAN] "WHITE"Kamu tidak bisa menjalin hubungan dengan sesama jenis!!!\n\n"YELLOW"(Masukan id/kantong player yang ingin kamu ajak menjalin hubungan)", "Select", "Close");
            }
            case 3:
            {   
                new targetid = IsPlayerNearPartner(playerid);

                if(targetid != INVALID_PLAYER_ID && IsPlayerConnected(targetid))
                {
                    if(targetid != playerid && IsPlayerInRangeOfPoint(playerid, 5.0, AccountData[targetid][pPos][0], AccountData[targetid][pPos][1], AccountData[targetid][pPos][2]))
                    {    
                        new nametarget[MAX_PLAYER_NAME], name[MAX_PLAYER_NAME];
                        GetPlayerName(targetid, nametarget, sizeof(nametarget));
                        GetPlayerName(playerid, name, sizeof(name));
                        SendCustomMessage(playerid, "Divorce","You have "RED" cut off "WHITE" your relationship with "YELLOW"%s!", nametarget);
                        SendCustomMessage(targetid, "Divorce","%s has "RED" broken off "WHITE" ties with your "YELLOW"!", name);

                        AccountData[playerid][pStatus] = 0;
                        AccountData[targetid][pStatus] = 0;

                        SetPlayerLove(targetid, 0);
                        SetPlayerLove(playerid, 0);

                        AccountData[playerid][pPartnerID] = 0;
                        AccountData[targetid][pPartnerID] = 0;

                        format(AccountData[playerid][pPartnerName], 64, "Single");
                        format(AccountData[targetid][pPartnerName], 64, "Single");
                        SQL_SaveCharacter(playerid);
                    }
                    else ShowTDN(playerid, NOTIFICATION, "You're not close enough to your partner to perform this!");
                }
                else
                {
                    mysql_tquery(g_SQL, sprintf("UPDATE `users` SET `Status` = '0', `Love` = '0.0', `PartnerID` = '0', `PartnerName` = 'Single' WHERE pID = %d", AccountData[playerid][pPartnerID]));

                    AccountData[playerid][pStatus] = 0;
                    SetPlayerLove(playerid, 0);
                    AccountData[playerid][pPartnerID] = 0;
                    format(AccountData[playerid][pPartnerName], 64, "Single");
                    SQL_SaveCharacter(playerid);

                    Info(playerid, "Pasangan Kamu tidak online tetapi Kamu memutuskan untuk putus, sekarang Kamu lajang!");
                }                                   
            }
        }
    }
    return 1;
}

CMD:relationcheck(playerid, params[])
{
    static
        userid;
    if (CheckAdmin(playerid, 3))
        return PermissionError(playerid);

    if(sscanf(params, "u", userid))
        return SendSyntaxMessage(playerid, "/relationcheck [playerid/PartOfName]");

    new output[600], partnername[32], Float:partnerlove, Float:totalpercentage;
    new partnerID = AccountData[userid][pPartnerID];
    new Float:playerlove = AccountData[userid][pLove];
    new Cache:checkname = mysql_query(g_SQL, sprintf("SELECT `PartnerName` FROM `users` WHERE `pID` = '%d' LIMIT 1;",AccountData[userid][pID]));
    if(cache_num_rows())
    {
        cache_get_value_name(0, "PartnerName", partnername, 32);
        cache_delete(checkname);
    }

    new Cache:checklove = mysql_query(g_SQL, sprintf("SELECT `Love` FROM `users` WHERE `pID` = '%d' LIMIT 1;", AccountData[userid][pPartnerID]));
    if(cache_num_rows())
    {
        cache_get_value_name_float(0, "Love", partnerlove);
        cache_delete(checklove);
    }
    totalpercentage = (playerlove/2) + (partnerlove/2);

    format(output, sizeof(output), ""WHITE"["LIGHTGREEN"Relationship Status"WHITE"]\n\n");
    format(output, sizeof(output), "%s"WHITE"Nama Partner : "RED"%s (UniqueID: %d)\n", output, partnername, partnerID);
    if(AccountData[userid][pStatus] == 0) 
    {
        format(output, sizeof(output), "%s"WHITE"Status : "LIGHTGREEN"Single\n", output);
        format(output, sizeof(output), "%s"WHITE"Love Percentage : "YELLOW"%.2f%%\n", output, playerlove); 
    }
    else if(AccountData[userid][pStatus] == 1) 
    {
        format(output, sizeof(output), "%s"WHITE"Status : "LIGHTGREEN"Dating\n", output);
        format(output, sizeof(output), "%s"WHITE"Love Percentage : "YELLOW"%.2f%%\n", output, totalpercentage); 
    } 
    else if(AccountData[userid][pStatus] == 2) 
    {
        format(output, sizeof(output), "%s"WHITE"Status : "LIGHTGREEN"Married\n", output);  
        format(output, sizeof(output), "%s"WHITE"Government Allowance : "LIGHTGREEN"$500\n", output);
        format(output, sizeof(output), "%s"WHITE"Love Percentage : "YELLOW"%.2f%%\n", output, totalpercentage);
    }

    Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""TCRP"District "WHITE" - Status Hubungan", output, "Close", "");
    return 1;
}


Dialog:RelationInvites(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    new userid = strval(inputtext);

    if(userid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, userid, 5.0))
        return ShowTDN(playerid, NOTIFICATION, "Pemain itu terputus atau tidak di dekat Kamu.");

    if(userid == playerid)
        return ShowTDN(playerid, NOTIFICATION, "Kamu tidak bisa berkencan dengan diri sendiri!.");

    if(AccountData[playerid][pGender] == AccountData[userid][pGender])
        return ShowTDN(playerid, NOTIFICATION, "Kamu tidak dapat berkencan dengan jenis kelamin yang sama dengan Kamu!");

    InviteTarget[playerid] = userid;
    Dialog_Show(playerid, RelationMenu, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Relationship Invitation", "Invite to date\nMarry her!", "Select", "Cancel");
    return 1;
}
Dialog:RelationMenu(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new userid = InviteTarget[playerid], name[MAX_PLAYER_NAME], nametarget[MAX_PLAYER_NAME];
        GetPlayerName(userid, nametarget, sizeof(nametarget));
        GetPlayerName(playerid, name, sizeof(name));
        switch(listitem)
        {
            case 0:
            {
                if(AccountData[playerid][pStatus] >= 1)
                    return ShowTDN(playerid, NOTIFICATION, "Kamu sedang menjalin hubungan!.");
                    
                if(AccountData[userid][pStatus] >= 1)
                    return ShowTDN(playerid, NOTIFICATION, "Pemain itu sedang menjalin hubungan!.");

                SendClientMessageEx(playerid, COLOR_WHITE, "Kamu telah mengundang "RED"%s"WHITE" untuk berkencan dengan Kamu!", nametarget);

                //Untuk nyimpen playerid si player di dalam InviteTarget si target.
                InviteTarget[userid] = playerid;

                Dialog_Show(userid, RelationInvite, DIALOG_STYLE_MSGBOX, ""TCRP"District "WHITE" - Relationship Invitation", ""RED"%s "WHITE"has invited you to date them", "Accept", "Decline", name);
            }
            case 1:
            {
                if(IsPlayerInRangeOfPoint(playerid, 10.0, 1220.0037, -1446.7375, 45.2224))
                {
                    if(AccountData[playerid][pLove] == 100 && AccountData[userid][pLove] == 100)
                    {
                        if(AccountData[playerid][pPartnerID] == AccountData[userid][pID])
                        {
                            InviteTarget[userid] = playerid;
                            SendClientMessageEx(playerid, COLOR_WHITE, "You have proposed"RED" %s "WHITE"to marry you!", nametarget);
                            Dialog_Show(userid, RelationInviteMarry, DIALOG_STYLE_MSGBOX, ""TCRP"District "WHITE" - Relationship Invitation", ""RED"%s "WHITE"has proposed you to marry them", "Accept", "Decline", name);               
                        }
                        else return SendClientMessageEx(playerid, COLOR_WHITE, "This player is not your partner!");
                    }
                    else return ShowTDN(playerid, NOTIFICATION, "Both of you need to gain full love percentage bar to propose this player!");
                }
                else return ShowTDN(playerid, NOTIFICATION, "You're not inside the church!");
            }
        }
    }
    return 1;
}

Dialog:RelationInvite(playerid, response, listitem, inputtext[])
{
    //Pindahin InviteTarget si player yang accept ke userid
    new userid = InviteTarget[playerid] , name[MAX_PLAYER_NAME], nametarget[MAX_PLAYER_NAME];
    GetPlayerName(userid, nametarget, sizeof(nametarget));
    GetPlayerName(playerid, name, sizeof(name));
    if(response)
    {
        SendCustomMessage(userid, "Partner", ""RED"%s "WHITE"accepted you to become your "LIGHTGREEN"partner", name);
        SendCustomMessage(playerid, "Partner", ""RED"You "WHITE"accepted %s to become your "LIGHTGREEN"partner", nametarget);
        AccountData[playerid][pStatus] = 1;
        AccountData[userid][pStatus] = 1;
    
        GetPlayerName(playerid, AccountData[userid][pPartnerName], MAX_PLAYER_NAME);
        GetPlayerName(userid, AccountData[playerid][pPartnerName], MAX_PLAYER_NAME);

        //Simpen ID SQL satu sama lain
        AccountData[playerid][pPartnerID] = AccountData[userid][pID];
        AccountData[userid][pPartnerID] = AccountData[playerid][pID];

        SQL_SaveCharacter(playerid);
        SQL_SaveCharacter(userid);

        InviteTarget[playerid] = 0;
        InviteTarget[userid] = 0; 
    }
    else
    {
        SendCustomMessage(userid, "Partner", ""RED"%s "WHITE"denied you to become your "LIGHTGREEN"partner", name);
        SendCustomMessage(playerid, "Partner", ""RED"You "WHITE"denied %s to become your "LIGHTGREEN"partner", nametarget);
        AccountData[playerid][pStatus] = 0;
        AccountData[userid][pStatus] = 0;
        InviteTarget[playerid] = 0;
        InviteTarget[userid] = 0; 
    }
    return 1;
}

Dialog:RelationInviteMarry(playerid, response, listitem, inputtext[])
{
    //Pindahin InviteTarget si player yang accept ke userid
    new userid = InviteTarget[playerid] , name[MAX_PLAYER_NAME], nametarget[MAX_PLAYER_NAME];
    GetPlayerName(userid, nametarget, sizeof(nametarget));
    GetPlayerName(playerid, name, sizeof(name));
    if(response)
    {
        SendCustomMessage(userid, "Married", ""RED"%s "WHITE"accepted you to become your "LIGHTGREEN"lifetime partner", name);
        SendCustomMessage(playerid, "Married", ""RED"You "WHITE"accepted %s to become your "LIGHTGREEN"lifetime partner", nametarget);

        // Status nikah
        AccountData[playerid][pStatus] = 2;
        AccountData[userid][pStatus] = 2;
        
        // Reset Love kedua player sesudah nikah
        SetPlayerLove(playerid, 0);
        SetPlayerLove(userid, 0);

        //Simpen Nama ketika sudah nikah
        GetPlayerName(playerid, AccountData[userid][pPartnerName], MAX_PLAYER_NAME);
        GetPlayerName(userid, AccountData[playerid][pPartnerName], MAX_PLAYER_NAME);

        //Simpen ID SQL satu sama lain
        AccountData[playerid][pPartnerID] = AccountData[userid][pID];
        AccountData[userid][pPartnerID] = AccountData[playerid][pID];

        SendClientMessageToAllEx(COLOR_WHITE, ""YELLOW"[Church] "RED"%s "WHITE"Telah menikah dan menjadi pasangan resmi "RED"%s", name, nametarget);

        SQL_SaveCharacter(playerid);
        SQL_SaveCharacter(userid);

        //Reset Invitation.
        InviteTarget[playerid] = 0;
        InviteTarget[userid] = 0; 
    }
    else
    {
        SendCustomMessage(userid, "Married", ""RED"%s "WHITE"denied you to become your "LIGHTGREEN"lifetime partner", name);
        SendCustomMessage(playerid, "Married", ""RED"You "WHITE"denied %s to become your "LIGHTGREEN"lifetime partner", nametarget);
        AccountData[playerid][pStatus] = 0;
        AccountData[userid][pStatus] = 0;
        InviteTarget[playerid] = 0;
        InviteTarget[userid] = 0; 
    }
    return 1;
}