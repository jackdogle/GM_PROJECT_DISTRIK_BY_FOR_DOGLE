#include <YSI_Coding\y_hooks>

new bool: IsFlashlightOn[MAX_PLAYERS],
    bool: IsFlashlightOpened[MAX_PLAYERS];

hook OnPlayerConnect(playerid)
{
    IsFlashlightOn[playerid] = false;
    IsFlashlightOpened[playerid] = false;
    return 1;
}

CMD:flashlight(playerid, params[])
{
    if (!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned])
        return 0;
    
    if (IsPlayerInAnyVehicle(playerid))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus diluar kendaraan!");

    switch (IsFlashlightOpened[playerid])
    {
        case false:
        {
            IsFlashlightOpened[playerid] = true;
            SetPlayerAttachedObject(playerid, JOB_SLOT, 18641, 6,  0.080999, 0.042000, -0.034000,  0.000000, 0.000000, 0.000000,  1.000000, 1.000000, 1.000000); // FLashlight Objects
            ApplyAnimationEx(playerid, "ped", "phone_talk", 2.1, 1, 1, 1, 1, 1, 1);
        }
        case true:
        {
            IsFlashlightOpened[playerid] = false;
            StopLoopingAnim(playerid);
            RemovePlayerAttachedObject(playerid, JOB_SLOT);

            if (IsFlashlightOn[playerid]) {
                RemovePlayerAttachedObject(playerid, 5);
                IsFlashlightOn[playerid] = false;
            }
        }
    }
    return 1;
}

// Callbacks
hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if (PRESSED(KEY_CTRL_BACK) && !IsPlayerInAnyVehicle(playerid) && IsFlashlightOpened[playerid])
    {
        switch(IsFlashlightOn[playerid])
        {
            case false:
            {
                IsFlashlightOn[playerid] = true;
                SetPlayerAttachedObject(playerid, 5, 19295, 1,  0.068000, 0.606000, 0.000000,  0.000000, -4.500000, 12.299996,  1.000000, 1.000000, 1.020000); // Light Objects
                ShowPlayerFooter(playerid, "~w~Flashlight~n~~g~Nyala", 3000);
            }
            case true:
            {
                IsFlashlightOn[playerid] = false;
                RemovePlayerAttachedObject(playerid, 5);
                ShowPlayerFooter(playerid, "~w~Flashlight~n~~r~Mati", 3000);
            }
        }
    }
    return 1;
}