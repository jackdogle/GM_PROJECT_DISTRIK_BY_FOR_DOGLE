CreateApiUnggun(playerid, Float:x, Float:y, Float:z)
{
    for(new i = 0; i < MAX_FIRE; i++)
    {
        if(!ApiUnggun[i][aUsed])
        {
            ApiUnggun[i][aObject] = CreateDynamicObject(19632, x, y, z, 0.0, 0.0, 0.0, 
                .worldid = GetPlayerVirtualWorld(playerid), .interiorid = GetPlayerInterior(playerid));

            ApiUnggun[i][aText] = CreateDynamic3DTextLabel("{ffffff}Buka Inventory Lalu Use Ikan/Ayam Di Dekat Api", COLOR_YELLOW, x, y, z+1.2, 5, 
                .worldid = GetPlayerVirtualWorld(playerid), .interiorid = GetPlayerInterior(playerid));

            ApiUnggun[i][aArea] = CreateDynamicSphere(x, y, z, 5.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
            ApiUnggun[i][aX] = x;
            ApiUnggun[i][aY] = y;
            ApiUnggun[i][aZ] = z;
            ApiUnggun[i][aVW] = GetPlayerVirtualWorld(playerid);
            ApiUnggun[i][aInt] = GetPlayerInterior(playerid);
            ApiUnggun[i][aOwner] = playerid;
            ApiUnggun[i][aUsed] = 1;

            return i;
        }
    }
    return -1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_WALK && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DUCK)
    {
        new Float:px, Float:py, Float:pz;
        GetPlayerPos(playerid, px, py, pz);

        for(new i = 0; i < MAX_FIRE; i++)
        {
            if(ApiUnggun[i][aUsed] &&
               IsPlayerInRangeOfPoint(playerid, 1.5, ApiUnggun[i][aX], ApiUnggun[i][aY], ApiUnggun[i][aZ]) &&
               GetPlayerInterior(playerid) == ApiUnggun[i][aInt] &&
               GetPlayerVirtualWorld(playerid) == ApiUnggun[i][aVW])
            {
                if(GetTotalWeightFloat(playerid) >= 50) 
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory telah penuh!");
                if(Inventory_Items(playerid) >= MAX_INVENTORY) 
                    return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot Inventory telah penuh!");

                DestroyDynamicObject(ApiUnggun[i][aObject]);
                DestroyDynamic3DTextLabel(ApiUnggun[i][aText]);
                DestroyDynamicArea(ApiUnggun[i][aArea]);
                ApiUnggun[i][aUsed] = 0;
                
                Inventory_Add(playerid, "Api Unggun", 19632, 1);

                SendRPMeAboveHead(playerid, "Mengambil Api Unggun", X11_PLUM1);
                ApplyAnimation(playerid, "CARRY", "liftup", 3.1, 0, 0, 0, 0, 0, 1);

                return 1;
            }
        }
    }
    return 1;
}

GetNearestFire(playerid)
{
    new Float:px, Float:py, Float:pz;
    GetPlayerPos(playerid, px, py, pz);

    for(new i = 0; i < MAX_FIRE; i++)
    {
        if(ApiUnggun[i][aUsed] &&
           IsPlayerInRangeOfPoint(playerid, 2.0, ApiUnggun[i][aX], ApiUnggun[i][aY], ApiUnggun[i][aZ]) &&
           GetPlayerInterior(playerid) == ApiUnggun[i][aInt] &&
           GetPlayerVirtualWorld(playerid) == ApiUnggun[i][aVW])
        {
            return i;
        }
    }
    return -1;
}

forward CookingDone(timerid, params[]);
public CookingDone(timerid, params[])
{
    new i = params[0];
    if(!Cooking[i][cUsed]) return 1;

    new playerid = Cooking[i][cPlayer];
    DestroyDynamicObject(Cooking[i][cObject]);
    Inventory_Add(playerid, "Daging Ikan Tawar", 2806, 1);
    Info(playerid, "Ikanmu telah matang dan kamu mendapatkan "YELLOW"1x "WHITE"daging ikan tawar!");
    Cooking[i][cUsed] = 0;
    ClearAnimations(playerid, true);
    StopLoopingAnim(playerid);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    return 1;
}

forward CookingDone1(timerid, params[]);
public CookingDone1(timerid, params[])
{
    new i = params[0];
    if(!Cooking[i][cUsed]) return 1;

    new playerid = Cooking[i][cPlayer];
    DestroyDynamicObject(Cooking[i][cObject]);
    Inventory_Add(playerid, "Daging Hiu", 2806, 1);
    Info(playerid, "Hiu telah matang dan kamu mendapatkan "YELLOW"1x "WHITE"daging Hiu!");
    Cooking[i][cUsed] = 0;
    ClearAnimations(playerid, true);
    StopLoopingAnim(playerid);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    return 1;
}

forward CookingDone2(timerid, params[]);
public CookingDone2(timerid, params[])
{
    new i = params[0];
    if(!Cooking[i][cUsed]) return 1;

    new playerid = Cooking[i][cPlayer];
    DestroyDynamicObject(Cooking[i][cObject]);
    Inventory_Add(playerid, "Daging Ayam Goreng", 2806, 1);
    Info(playerid, "Ayam telah matang dan kamu mendapatkan "YELLOW"1x "WHITE"Daging Ayam Goreng!");
    Cooking[i][cUsed] = 0;
    ClearAnimations(playerid, true);
    StopLoopingAnim(playerid);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    return 1;
}
