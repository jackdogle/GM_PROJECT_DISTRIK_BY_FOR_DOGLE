CMD:me(playerid, params[])
{
    new flyingtext[156];

    if(isnull(params))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/ame [actions]");
    
    if(strlen(params) > 128)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Max Lenght Actions 128 Character!");

    format(flyingtext, sizeof(flyingtext), ""PLUM1"> %s", params);
    SendClientMessageEx(playerid, -1, sprintf(""WHITE"ACTION:"PLUM1" %s", params));
    SetPlayerChatBubble(playerid, flyingtext, -1, 15.0, 6000);
    return 1;
}

/*CMD:me(playerid, params[])
{
    if(isnull(params)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/me [action]");

    if(strlen(params) > 64)
    {
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s %.64s...", ReturnName(playerid), params);
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "...%s", params[64]);
    }
    else
    {
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s %s", ReturnName(playerid), params);
    }
    return 1;
}*/

/*CMD:do(playerid, params[])
{
    if(isnull(params)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/do [action]");

    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "* %s (( %s ))", params, ReturnName(playerid));
    return 1;
}*/

CMD:do(playerid, params[])
{
    new flyingtext[156];

    if(isnull(params))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/do [actions]");
    
    if(strlen(params) > 128)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Max Lenght Actions 128 Character!");

    format(flyingtext, sizeof(flyingtext), ""LIGHTGREEN"> %s", params);
    SendClientMessageEx(playerid, -1, sprintf(""WHITE"ACTION"LIGHTGREEN" %s", params));
    SetPlayerChatBubble(playerid, flyingtext, -1, 15.0, 6000);
    return 1;
}

SendRPMeAboveHead(playerid, const text[], color)
{
    new frmxt[255];

    format(frmxt, sizeof(frmxt), "> %s", text);
    SetPlayerChatBubble(playerid, frmxt, color, 15.0, 6500);

    //mengirim chatlog kepada player tersebut sebagai penanda actionnya
    SendClientMessageEx(playerid, -1, ""WHITE"ACTION: "PLUM1"%s", text);
    return 1;
}