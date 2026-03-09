#include <YSI\y_hooks>

new
    STREAMER_TAG_AREA:NetFisherArea[MAX_PLAYERS],
    STREAMER_TAG_MAP_ICON:NetFisherIcon[MAX_PLAYERS],
    STREAMER_TAG_PICKUP:FishermanBoatPickup[MAX_PLAYERS],
    STREAMER_TAG_3D_TEXT_LABEL:FishermanBoatLabel[MAX_PLAYERS],
    FishermanNetTimer[MAX_PLAYERS] = { -1, ... };

LoadVarsFisherman(playerid)
{
    UnloadVarsFisherman(playerid);

    if(AccountData[playerid][pJob] == JOB_FISHERMAN)
    {
        NetFisherArea[playerid] = CreateDynamicRectangle(288, -2734, 586, -2611, 0, 0, playerid);
        NetFisherIcon[playerid] = CreateDynamicMapIcon(352.4596, -2669.7722, -0.0401, 9, X11_YELLOW, 0, 0, playerid, 2000.0, MAPICON_GLOBAL, -1, 0);
        FishermanBoatPickup[playerid] = CreateDynamicPickup(1239, 23, 111.3999, -1895.6553, 2.9408, 0, 0, playerid, 50.0, -1, 0);
        FishermanBoatLabel[playerid] = CreateDynamic3DTextLabel(""LIGHTGREY"[Vehicle Rental]\n"BLUEJEGE"Rental Perahu\n"GREEN"[Y]"WHITE" untuk mengeluarkan perahu nelayan", -1, 111.3999, -1895.6553, 2.9408 + 0.5, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0, playerid, 15.0, -1, 0);
    }
    return 1;
}

UnloadVarsFisherman(playerid)
{
    if(IsValidDynamicArea(NetFisherArea[playerid]))
        DestroyDynamicArea(NetFisherArea[playerid]);
    
    if(IsValidDynamicMapIcon(NetFisherIcon[playerid]))
        DestroyDynamicMapIcon(NetFisherIcon[playerid]);
    
    if(IsValidDynamicPickup(FishermanBoatPickup[playerid]))
        DestroyDynamicPickup(FishermanBoatPickup[playerid]);
    
    if(IsValidDynamic3DTextLabel(FishermanBoatLabel[playerid]))
        DestroyDynamic3DTextLabel(FishermanBoatLabel[playerid]);
    
    NetFisherArea[playerid] = STREAMER_TAG_AREA: INVALID_STREAMER_ID;
    NetFisherIcon[playerid] = STREAMER_TAG_MAP_ICON: INVALID_STREAMER_ID;
    FishermanBoatPickup[playerid] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
    FishermanBoatLabel[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES)
    {
        if(AccountData[playerid][pJob] == JOB_FISHERMAN)
        {
            if(IsPlayerInRangeOfPoint(playerid, 2.0, 111.3999, -1895.6553, 2.9408) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
            {
                Dialog_Show(playerid, FishermanBoatSpawn, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Sewa Perahu",
                "Jenis Perahu\tHarga\
                \nReefer\t$150\
                \n"YELLOW"~> Tekan ini jika sudah selesai menggunakan perahu sewaan", "Sewa", "Batal");
            }

            if(IsPlayerInDynamicArea(playerid, NetFisherArea[playerid]))
            {
                if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda sudah penuh!");
                if(AccountData[playerid][pJob] != JOB_FISHERMAN) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang nelayan!");
                if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus keluar dari kemudi boat untuk mancing!");
                ApplyAnimationEx(playerid, "SWORD", "sword_block", 50.0, 0, 1, 0, 1, 1, 1);
                SetPlayerAttachedObject(playerid, 9,18632,6,0.079376,0.037070,0.007706,181.482910,0.000000,0.000000,1.000000,1.000000,1.000000);

                if(!IsValidBarFish(playerid)) BarFish(playerid, "Anda sedang mancing", "NetFishing");
            }
        }
    }
    return 1;
}

forward NetFishing(playerid);
public NetFishing(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(FishermanNetTimer[playerid]);
        return 0;
    }

    if(!IsValidDynamicArea(NetFisherArea[playerid]))
    {
        KillTimer(FishermanNetTimer[playerid]);
        return 0;
    }

    if(!IsPlayerInDynamicArea(playerid, NetFisherArea[playerid]))
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di area menjangkar!");
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        return 0;
    }

    if(GetTotalWeightFloat(playerid) >= 50)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
        return 0;
    }
        
    AccountData[playerid][pThirst] --;
    Inventory_Add(playerid, "Ikan", 19630, 1);
    ShowItemBox(playerid, "Received 1x", "Ikan", 19630);
    new rands = RandomEx(1, 51), randgaram = RandomEx(1, 3);
    switch(rands)
    {
        case 1..11:
        {
            Inventory_Add(playerid, "Garam Kristal", 1611, randgaram);
            Info(playerid, "Anda mendapatkan "YELLOW"Garam Kristal"WHITE" sebanyak "YELLOW"%dx", randgaram);
        }
        case 12..31:
        {
            Inventory_Add(playerid, "Garam Kristal", 1611, 2);
            Info(playerid, "Anda mendapatkan "YELLOW"Garam Kristal"WHITE" sebanyak "YELLOW"2x");
        }
        case 32..50:
        {
            Inventory_Add(playerid, "Garam Kristal", 1611, randgaram);
            Info(playerid, "Anda mendapatkan "YELLOW"Garam Kristal"WHITE" sebanyak "YELLOW"%dx", randgaram);
        }
    }
    RemovePlayerAttachedObject(playerid, 9);
    GivePlayerXP(playerid, DEFAULT_XP);
    return 1;
}

Dialog:FishermanBoatSpawn(playerid, response, listitem, inputtext[])
{
    if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
    if(AccountData[playerid][pJob] != JOB_FISHERMAN) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang nelayan!");
    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
    switch(listitem)
    {
        case 0: // sewa
        {
            if(AccountData[playerid][pMoney] < 150) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");

            TakeMoney(playerid, 150);
            VehicleRental_Create(playerid, 453, 3600, 1, 115.6808, -1899.8322, -0.2283, 90.2587, random(255), random(255), 150, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
            Info(playerid, "Anda berhasil menyewa perahu, silahkan ke tanda "RED"Jangkar"WHITE" yang berada di tengah laut");
        }
        case 1: // Kembalikan
        {
            if(Vehicle_RentalCount(playerid) < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki kendaraan rental apapun!");
            foreach(new i : PvtVehicles) if(PlayerVehicle[i][pVehExists]) if(IsValidVehicle(PlayerVehicle[i][pVehPhysic]) && IsABoat(PlayerVehicle[i][pVehPhysic]))
            {
                if(PlayerVehicle[i][pVehOwnerID] == AccountData[playerid][pID])
                {
                    if(PlayerVehicle[i][pVehRental] != -1 && PlayerVehicle[i][pVehRentTime] != 0)
                    {
                        PlayerVehicle[i][pVehExists] = false;
                        PlayerVehicle[i][pVehRental] = -1;
                        PlayerVehicle[i][pVehOwnerID] = -1;
                        PlayerVehicle[i][pVehRentTime] = 0;

                        if(IsValidVehicle(PlayerVehicle[i][pVehPhysic])) 
                        {
                            DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
                            PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;
                        }
                        
                        mysql_tquery(g_SQL, sprintf("DELETE FROM player_vehicles WHERE id = '%d'", PlayerVehicle[i][pVehID]));
                        
                        Vehicle_ResetVariable(i);
                        Iter_Remove(PvtVehicles, i);
                    }
                }
            }

            ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengembalikan perahu sewaan anda!");
        }
    }
    return 1;
}