#include <YSI\y_hooks>

hook OnGameModeInit()
{
    CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Akses Toko Olahraga", -1, 1386.4347, 293.3129, 19.5469 + 0.3, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.5, 1386.4347, 293.3129, 19.5469))
        {
            if(!Dialog_Opened(playerid))
            {
                ShowPlayerDialog(playerid, DIALOG_SPORTSTORE, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Toko Olahraga", 
                "Nama Item\tHarga\
                \nStick Golf\t$2500\
                \n"GRAY"Baseball\t"GRAY"$3000\
                \nTongkat Satpam\t$2500\
                \n"GRAY"Pisau\t"GRAY"$5000\
                \nShovel\t$3000\
                \n"GRAY"Stick Billiard\t"GRAY"$4000\
                \nKatana\t$10000\
                \n"GRAY"Gagang Payung\t"GRAY"$2500", "Pilih", "Batal");
            }
        }
    }
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_SPORTSTORE:
        {
            if(!response) return InfoBatal(playerid);
            switch(listitem)
            {
                case 0://Stick Golf
                {
                    new value = 2500;
                    new weaponid = 2;
                    new ammo = 1;
                    if(GetPlayerMoney(playerid) < value) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup untuk membeli ini!");

                    TakeMoney(playerid, value);
                    GivePlayerWeaponEx(playerid, weaponid, ammo);
                    ShowItemBox(playerid, "Removed $2500", "UANG", 1212);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membeli Stick Golf seharga $2500");
                }
                case 1://Baseball
                {
                    new value = 3000;
                    new weaponid = 5;
                    new ammo = 1;
                    if(GetPlayerMoney(playerid) < value) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup untuk membeli ini!");

                    TakeMoney(playerid, value);
                    GivePlayerWeaponEx(playerid, weaponid, ammo);
                    ShowItemBox(playerid, "Removed $3000", "UANG", 1212);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membeli Baseball Bat seharga $3000");
                }
                case 2://Tongkat Satpam
                {
                    new value = 2500;
                    new weaponid = 3;
                    new ammo = 1;
                    if(GetPlayerMoney(playerid) < value) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup untuk membeli ini!");

                    TakeMoney(playerid, value);
                    GivePlayerWeaponEx(playerid, weaponid, ammo);
                    ShowItemBox(playerid, "Removed $2500", "UANG", 1212);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membeli Tongkat Satpam seharga $2500");
                }
                case 3://Pisau
                {
                    new value = 5000;
                    new weaponid = 4;
                    new ammo = 1;
                    if(GetPlayerMoney(playerid) < value) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup untuk membeli ini!");

                    TakeMoney(playerid, value);
                    GivePlayerWeaponEx(playerid, weaponid, ammo);
                    ShowItemBox(playerid, "Removed $5000", "UANG", 1212);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membeli Pisau seharga $5000");
                }
                case 4://Shovel
                {
                    new value = 3000;
                    new weaponid = 6;
                    new ammo = 1;
                    if(GetPlayerMoney(playerid) < value) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup untuk membeli ini!");

                    TakeMoney(playerid, value);
                    GivePlayerWeaponEx(playerid, weaponid, ammo);
                    ShowItemBox(playerid, "Removed $3000", "UANG", 1212);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membeli Baseball Bat seharga $3000");
                }
                case 5://Stick Billiard
                {
                    new value = 4000;
                    new weaponid = 7;
                    new ammo = 1;
                    if(GetPlayerMoney(playerid) < value) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup untuk membeli ini!");

                    TakeMoney(playerid, value);
                    GivePlayerWeaponEx(playerid, weaponid, ammo);
                    ShowItemBox(playerid, "Removed $4000", "UANG", 1212);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membeli Stick Billiard seharga $4000");
                }
                case 6://Katana
                {
                    new value = 10000;
                    new weaponid = 8;
                    new ammo = 1;
                    if(GetPlayerMoney(playerid) < value) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup untuk membeli ini!");

                    TakeMoney(playerid, value);
                    GivePlayerWeaponEx(playerid, weaponid, ammo);
                    ShowItemBox(playerid, "Removed $10000", "UANG", 1212);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membeli Katana seharga $10000");
                }
                case 7://Gagang Payung
                {
                    new value = 2500;
                    new weaponid = 15;
                    new ammo = 1;
                    if(GetPlayerMoney(playerid) < value) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup untuk membeli ini!");

                    TakeMoney(playerid, value);
                    GivePlayerWeaponEx(playerid, weaponid, ammo);
                    ShowItemBox(playerid, "Removed $2500", "UANG", 1212);
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil membeli Baseball Bat seharga $2500");
                }
            }
        }
    }
    return 1;
}