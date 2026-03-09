ptask PlayerJail_Update[1000](playerid)
{
    if(!AccountData[playerid][pSpawned])
        return 0;
    
    if(AccountData[playerid][pArrest])
    {
        if(AccountData[playerid][pArrestTime] != 0)
        {
            AccountData[playerid][pArrestTime] --;
            GameTextForPlayer(playerid, sprintf("%d", AccountData[playerid][pArrestTime]), 1000, 4);
            if(!AccountData[playerid][pArrestTime])
            {
                AccountData[playerid][pArrest] = 0;
                AccountData[playerid][pArrestTime] = 0;
                SetPlayerPositionEx(playerid, 135.0716, 1943.8336, 19.3363, 356.8318, 6000);
                ClearAnimations(playerid, 1);
                SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                SendClientMessage(playerid, X11_GRAY, "[Federal] Kamu telah dibebaskan dari penjara federal");

                new query[255];
                mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_Jail`=0, `Char_JailTime`=0 WHERE `pID`=%d", AccountData[playerid][pID]);
                mysql_tquery(g_SQL, query);
            }
        }
    }

    if(AccountData[playerid][pJail])
    {
        if(AccountData[playerid][pJailTime] != 0)
        {
            AccountData[playerid][pJailTime] --;
            GameTextForPlayer(playerid, sprintf("%d", AccountData[playerid][pJailTime]), 1000, 4);
            if(!AccountData[playerid][pJailTime])
            {
                AccountData[playerid][pJail] = 0;
                AccountData[playerid][pJailTime] = 0;
                AccountData[playerid][pJailReason][0] = EOS;
                AccountData[playerid][pJailBy][0] = EOS;
                SetPlayerPositionEx(playerid, 1482.0356,-1724.5726,13.5469,750, 2000);
                SetPlayerInteriorEx(playerid, 0);
                SetPlayerVirtualWorldEx(playerid, 0);
                ClearAnimations(playerid, 1);
                SendClientMessage(playerid, X11_ARWIN, "[AdmCmd] Anda telah terbebas dari hukuman jail admin!");

                new cQuery[178];
                mysql_format(g_SQL, cQuery, sizeof(cQuery), "DELETE FROM `warninglogs` WHERE `WarnType` = 2 AND `pID` = '%d'", AccountData[playerid][pID]);
                mysql_query(g_SQL, cQuery, false);
            }
        }
    }
    return 1;
}