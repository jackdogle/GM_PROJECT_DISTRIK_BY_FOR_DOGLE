
#include <YSI\y_hooks>
new g_LastDialogResponse[MAX_PLAYERS];
hook OnPlayerSpawn(playerid)
{
    g_LastDialogResponse[playerid] = GetTickCount();
    return 1;
}
hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    new currentTime = GetTickCount();
    new timeDifference = currentTime - g_LastDialogResponse[playerid];
    if (timeDifference < 200)// jeda 200 milidetik
    {
        SendAdminMessage(X11_RED, "[AntiCheat]: "LIGHTGREY"Cheat detected on "YELLOW"%s (%d) "LIGHTGREY"(Spam Dialog)", GetName(playerid), playerid);
        SendClientMessageEx(playerid, X11_RED, "[AntiCheat]:"LIGHTGREY" Anda ditendang karena diduga Spam Dialog!");
        Kick(playerid);
        return 0;
    }
    g_LastDialogResponse[playerid] = currentTime;
    return 1;
}
