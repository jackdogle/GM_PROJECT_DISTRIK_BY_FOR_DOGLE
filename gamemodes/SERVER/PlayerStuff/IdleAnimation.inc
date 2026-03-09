new PlayerIdleTime[MAX_PLAYERS];

new Float:PlayerX[MAX_PLAYERS], Float:PlayerY[MAX_PLAYERS], Float:PlayerZ[MAX_PLAYERS];

#include <YSI\y_hooks>

hook OnPlayerConnect(playerid)
{
    PlayerIdleTime[playerid] = 0;
    return 1;
}

IsPlayerIdle(playerid)
{
    new
        index = GetPlayerAnimationIndex(playerid)
    ;

    return ((index == 1275) || (1181 <= index <= 1192) || (index == 1151));
}

ptask IdleAnimation[1000](playerid)
{
    new keys, updown, leftright;
    GetPlayerKeys(playerid, keys, updown, leftright);

    // Hentikan jika tidak memenuhi syarat untuk animasi idle
    if (!AnimationCheck(playerid) || IsPlayerInAnyVehicle(playerid) || GetPlayerSpecialAction(playerid) != PLAYER_ACTION_NONE ||
        !AccountData[playerid][pSpawned] || GetPlayerWeapon(playerid) || IsPlayerInWater(playerid))
    {
        return 0;
    }

    // Reset waktu idle jika tombol tertentu ditekan
    if (keys & (KEY_WALK | KEY_SPRINT | KEY_JUMP)) 
    {
        PlayerIdleTime[playerid] = 0;
        return 1;
    }

    // Hanya hitung jika pemain cukup dekat dengan titik tertentu
    if (IsPlayerInRangeOfPoint(playerid, 1.0, PlayerX[playerid], PlayerY[playerid], PlayerZ[playerid]))
    {
        // Jika pemain idle atau tidak memiliki special action, reset waktu idle
        if (!IsPlayerIdle(playerid) || GetPlayerSpecialAction(playerid) != PLAYER_ACTION_NONE)
        {
            PlayerIdleTime[playerid] = 0;
        }

        // Cek jika idle time mencapai batas (misal 30 detik)
        if (PlayerIdleTime[playerid] > 30)
        {
            if (IsPlayerIdle(playerid) || GetPlayerSpecialAction(playerid) == PLAYER_ACTION_NONE)
            {
                // Pilih animasi secara acak dan terapkan
                new type = random(4);  // Perbaiki range random (0-3)
                switch (type)
                {
                    case 0: ApplyAnimation(playerid, "PLAYIDLES", "SHIFT", 4.1, 0, 0, 0, 0, 0, 1); 
                    case 1: ApplyAnimation(playerid, "GANGS", "Invite_No", 4.1, 0, 0, 0, 0, 0, 1); 
                    case 2: ApplyAnimation(playerid, "DEALER", "DEALER_IDLE_02", 4.1, 0, 0, 0, 0, 0, 1); 
                    case 3: ApplyAnimation(playerid, "DEALER", "DEALER_IDLE_01", 4.1, 0, 0, 0, 0, 0, 1); 
                }
            }
            PlayerIdleTime[playerid] = 0;  // Reset waktu idle setelah animasi
        }
        else
        {
            PlayerIdleTime[playerid]++;  // Increment waktu idle
        }
    }
    else
    {
        PlayerIdleTime[playerid] = 0;  // Reset jika pemain terlalu jauh
    }

    // Update posisi pemain (hanya jika diperlukan)
    GetPlayerPos(playerid, PlayerX[playerid], PlayerY[playerid], PlayerZ[playerid]);

    return 1;
}
