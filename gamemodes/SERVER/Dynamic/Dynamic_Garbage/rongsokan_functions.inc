#include <YSI\y_hooks>

stock LoadVarsRongsok()
{
    CreateDynamicPickup(19570, 23, 2183.0188, -1986.7108, 13.1645, -1, -1, -1, 10.0);
    CreateDynamic3DTextLabel(""YELLOW"[Rongsokan]\n\n"WHITE"Botol "VERONA_GREEN"$4/botol\n\n"VERONA_GREEN"[Y] "WHITE"Menjual Botol", -1, 2183.0188, -1986.7108, 13.1645+1.4, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
}

hook OnGameModeInit()
{
    LoadVarsRongsok();
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 2183.0188, -1986.7108, 13.1645))
        {
            if(!PlayerHasItem(playerid, "Botol")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Botol!");
            new total = Inventory_Count(playerid, "Botol");
            new pay = total * 4;

            GiveMoney(playerid, pay);
            Inventory_Remove(playerid, "Botol", total);
            ShowItemBox(playerid, sprintf("Received %s", FormatMoney(pay)), "UANG", 1212);
            SendClientMessageEx(playerid, -1, ""YELLOW"[!]"WHITE": Anda menjual botol sebanyak %dx", total);
        }
    }
    return 1;
}