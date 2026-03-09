#include <YSI\y_hooks>

new pTakeFish[MAX_PLAYERS] = {-1, ...};
new pSellFish[MAX_PLAYERS] = {-1, ...};

enum E_STUFFNELAYAN
{
    nelayanVehicle,

    STREAMER_TAG_AREA:nelayanBoat,
    STREAMER_TAG_AREA:nelayanMancing,
    STREAMER_TAG_AREA:nelayanJual,
    
    STREAMER_TAG_3D_TEXT_LABEL:nelayanLabel[2],
    STREAMER_TAG_MAP_ICON:nelayanIcon[2],

    bool: DurringFisher,
}
new PlayerVarsMancing[MAX_PLAYERS][E_STUFFNELAYAN];

function LoadVarsNelayan(playerid)
{
    UnloadVarsNelayan(playerid);

    if(AccountData[playerid][pJob] == JOB_FISHERMAN)
    {
        PlayerVarsMancing[playerid][nelayanBoat] = CreateDynamicCircle(2941.4565, -2051.7068, 3.0, 0, 0,_);
        PlayerVarsMancing[playerid][nelayanMancing] = CreateDynamicCircle(3860.0828, -1738.8643, 80.0, 0, 0,_);
        PlayerVarsMancing[playerid][nelayanJual] = CreateDynamicSphere(279.3990, -1434.9664, 13.9662, 3.0, -1, -1, -1, 1);

        PlayerVarsMancing[playerid][nelayanLabel][0] = CreateDynamic3DTextLabel(""GREEN"[Y] "WHITE"Ambil Perahu", -1, 2941.4565, -2051.7068, 3.5480+0.3, 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, playerid);
        PlayerVarsMancing[playerid][nelayanLabel][1] = CreateDynamic3DTextLabel(""GREEN"[Y] "WHITE"Menjual Ikan", -1, 279.3990, -1434.9664, 13.9662+0.3, 3.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, playerid);
        PlayerVarsMancing[playerid][nelayanIcon][0] = CreateDynamicMapIcon(3860.0828, -1738.8643, 0.1244, 9, -1, 0, 0, playerid, 9999.0, MAPICON_GLOBAL, -1, 1);
        PlayerVarsMancing[playerid][nelayanIcon][1] = CreateDynamicMapIcon(279.3990, -1434.9664, 13.9662, 9, -1, 0, 0, playerid, 9999.0, MAPICON_GLOBAL, -1, 1);
    }
}

function UnloadVarsNelayan(playerid)
{
    if(IsValidDynamicArea(PlayerVarsMancing[playerid][nelayanBoat]))
        DestroyDynamicArea(PlayerVarsMancing[playerid][nelayanBoat]);
    PlayerVarsMancing[playerid][nelayanBoat] = STREAMER_TAG_AREA: -1;
    
    if(IsValidDynamicArea(PlayerVarsMancing[playerid][nelayanMancing]))
        DestroyDynamicArea(PlayerVarsMancing[playerid][nelayanMancing]);
    PlayerVarsMancing[playerid][nelayanMancing] = STREAMER_TAG_AREA: -1;

    if(IsValidDynamicArea(PlayerVarsMancing[playerid][nelayanJual]))
        DestroyDynamicArea(PlayerVarsMancing[playerid][nelayanJual]);
    PlayerVarsMancing[playerid][nelayanJual] = STREAMER_TAG_AREA: -1;
    
    if(IsValidDynamic3DTextLabel(PlayerVarsMancing[playerid][nelayanLabel][0]))
        DestroyDynamic3DTextLabel(PlayerVarsMancing[playerid][nelayanLabel][0]);
    PlayerVarsMancing[playerid][nelayanLabel][0] = STREAMER_TAG_3D_TEXT_LABEL: -1;    

    if(IsValidDynamic3DTextLabel(PlayerVarsMancing[playerid][nelayanLabel][1]))
        DestroyDynamic3DTextLabel(PlayerVarsMancing[playerid][nelayanLabel][1]);
    PlayerVarsMancing[playerid][nelayanLabel][1] = STREAMER_TAG_3D_TEXT_LABEL: -1;

    if(IsValidDynamicMapIcon(PlayerVarsMancing[playerid][nelayanIcon][0]))
        DestroyDynamicMapIcon(PlayerVarsMancing[playerid][nelayanIcon][0]);
    PlayerVarsMancing[playerid][nelayanIcon][0] = STREAMER_TAG_MAP_ICON: -1;    

    if(IsValidDynamicMapIcon(PlayerVarsMancing[playerid][nelayanIcon][1]))
        DestroyDynamicMapIcon(PlayerVarsMancing[playerid][nelayanIcon][1]);
    PlayerVarsMancing[playerid][nelayanIcon][1] = STREAMER_TAG_MAP_ICON: -1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(AccountData[playerid][pJob] != 17) return 0;
        if(AccountData[playerid][pInjured]) return 0;
        
        if(IsPlayerInDynamicArea(playerid, PlayerVarsMancing[playerid][nelayanBoat]))
        {
            if(PlayerVarsMancing[playerid][DurringFisher]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telah mengeluarkan perahu nelayan");
            PlayerVarsMancing[playerid][nelayanVehicle] = CreateVehicle(484, 2947.6318, -2049.9382, 0.0431, 357.1097, 0, 0, 60000, 0);

            VehicleCore[PlayerVarsMancing[playerid][nelayanVehicle]][vCoreFuel] = 100;
            SetVehicleHealth(PlayerVarsMancing[playerid][nelayanVehicle], 1000);
            PutPlayerInVehicle(playerid, PlayerVarsMancing[playerid][nelayanVehicle], 0);

            PlayerVarsMancing[playerid][DurringFisher] = true;
        }

        if(IsPlayerInDynamicArea(playerid, PlayerVarsMancing[playerid][nelayanJual]))
        {
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
            
            AccountData[playerid][ActivityTime] = 1;
            pSellFish[playerid] = SetTimerEx("SellFish", 1000, true, "i", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENJUAL IKAN");
            ShowProgressBar(playerid);
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
        }
    }
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
    {
        if(AccountData[playerid][pInjured]) return 0;
        if(IsPlayerInDynamicArea(playerid, PlayerVarsMancing[playerid][nelayanMancing]))
        {
            if(!PlayerVarsMancing[playerid][DurringFisher]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu belum mengambil perahu, dan dinyatakan belum memulai memancing");
            if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
            
            AccountData[playerid][ActivityTime] = 1;
            pTakeFish[playerid] = SetTimerEx("TakeFish", 1000, true, "i", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENJARING IKAN");
            ShowProgressBar(playerid);
        }
    }
    return 1;
}
function TakeFish(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pTakeFish[playerid]);
        pTakeFish[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerVarsMancing[playerid][nelayanMancing]))
    {
        KillTimer(pTakeFish[playerid]);
        pTakeFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerVarsMancing[playerid][nelayanMancing]))
    {
        KillTimer(pTakeFish[playerid]);
        pTakeFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(AccountData[playerid][pBeratItem] >= 50.0)
    {
        KillTimer(pTakeFish[playerid]);
        pTakeFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory kamu penuh!");
        return 0;
    }

    if(Inventory_Count(playerid, "Ikan") >= 100)
    {
        KillTimer(pTakeFish[playerid]);
        pTakeFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        ShowTDN(playerid, NOTIFICATION_ERROR, "Ikan sudah mencapai batas (Max: 100)");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 132)
    {
        KillTimer(pTakeFish[playerid]);
        pTakeFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        new randfish = RandomEx(1, 6);
        ShowItemBox(playerid, sprintf("ADDED %dx", randfish), "IKAN", 19630);
        Inventory_Add(playerid, "Ikan", 19630, randfish);
        GivePlayerXP(playerid, DEFAULT_XP);
    }   
    else 
    {
        AccountData[playerid][ActivityTime] += 8.8;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/132;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

function SellFish(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pSellFish[playerid]);
        pSellFish[playerid] = -1;
        HideProgressBar(playerid);
        return 0;
    }

    if(!IsValidDynamicArea(PlayerVarsMancing[playerid][nelayanJual]))
    {
        KillTimer(pSellFish[playerid]);
        pSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, PlayerVarsMancing[playerid][nelayanJual]))
    {
        KillTimer(pSellFish[playerid]);
        pSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        KillTimer(pSellFish[playerid]);
        pSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(Inventory_Count(playerid, "Ikan") < 1)
    {
        KillTimer(pSellFish[playerid]);
        pSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki ikan!");

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 132)
    {
        KillTimer(pSellFish[playerid]);
        pSellFish[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        
        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        new total = Inventory_Count(playerid, "Ikan");
        new pay = total * 8;
        
        GiveMoney(playerid, pay);
        ShowItemBox(playerid, sprintf("ADDED %dx", pay), "UANG", 1212);
        Inventory_Remove(playerid, "Ikan", total);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 13.2;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/132;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}