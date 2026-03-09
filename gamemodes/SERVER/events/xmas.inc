#include <YSI\y_hooks>

new STREAMER_TAG_3D_TEXT_LABEL:ChristmastLabel[4];

hook OnGameModeInit()
{
	ChristmastLabel[0] = CreateDynamic3DTextLabel(""YELLOW"'/xmas'", -1, 1603.327758, -2311.205810, 12.570240 + 2.0, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	ChristmastLabel[1] = CreateDynamic3DTextLabel(""YELLOW"'/xmas'", -1, 2753.635498, -2424.200927, 12.583185 + 2.0, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	ChristmastLabel[2] = CreateDynamic3DTextLabel(""YELLOW"'/xmas'", -1, 2426.088623, -1247.288940, 22.838201 + 2.0, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	ChristmastLabel[3] = CreateDynamic3DTextLabel(""YELLOW"'/xmas'", -1, 1510.782104, -1723.617065, 12.546875 + 2.0, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	ChristmastLabel[3] = CreateDynamic3DTextLabel(""YELLOW"'/xmas'", -1, 377.438049, -2008.618530, 6.830090 + 2.0, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	ChristmastLabel[3] = CreateDynamic3DTextLabel(""YELLOW"'/xmas'", -1, -54.555156, 1061.601074, 18.752178 + 2.0, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 20.0, -1, 0);
	return 1;
}

ChrismastTreeArea(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 3.0, 1603.327758, -2311.205810, 12.570240)) return 1;	
	if(IsPlayerInRangeOfPoint(playerid, 3.0, 2753.635498, -2424.200927, 12.583185)) return 1;
	if(IsPlayerInRangeOfPoint(playerid, 3.0, 2426.088623, -1247.288940, 22.838201)) return 1;
	if(IsPlayerInRangeOfPoint(playerid, 3.0, 1510.782104, -1723.617065, 12.546875)) return 1;
	if(IsPlayerInRangeOfPoint(playerid, 3.0, 377.438049, -2008.618530, 6.830090)) return 1;
	if(IsPlayerInRangeOfPoint(playerid, 3.0, -54.555156, 1061.601074, 18.752178)) return 1;
	return 0;
}

CMD:xmas(playerid, params[])
{
	if(AccountData[playerid][pXmasTime] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah mengambil hadiah XMAS!");
	if(!ChrismastTreeArea(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada didekat Pohon Natal!");

	new rands = RandomEx(1, 100);
	switch(rands)
	{
		case 1..5:
		{
			new randomweapon = RandomEx(1, 8);
			GivePlayerWeaponEx(playerid, randomweapon, 1);
		}
		case 6..9:
		{
			GiveMoney(playerid, 550);
			ShowItemBox(playerid, "Received $550", "Uang", 1212);
		}
		case 10..13:
		{
			GiveMoney(playerid, 1500);
			ShowItemBox(playerid, "Received $1,500", "Uang", 1212);
		}
		case 14..20:
		{
			Inventory_Add(playerid, "Nasi Goreng", 2355, 10);
			Inventory_Add(playerid, "Kopi Kenangan", 19835, 10);
			ShowItemBox(playerid, "Received 10x", "Nasi Goreng", 2355);
			ShowItemBox(playerid, "Received 10x", "Kopi Kenangan", 19835);
		}
		case 21..56:
		{
			Inventory_Add(playerid, "Pancingan", 18632, 5);
			Inventory_Add(playerid, "Umpan", 1603, 50);
			ShowItemBox(playerid, "Received 5x", "Pancingan", 18632);
			ShowItemBox(playerid, "Received 50x", "Umpan", 1603);
		}
		case 57..90:
		{
			GiveMoney(playerid, 550);
			ShowItemBox(playerid, "Received $550", "Uang", 1212);
		}
		case 91..99:
		{
			Inventory_Add(playerid, "Nasi Goreng", 2355, 5);
			Inventory_Add(playerid, "Kopi Kenangan", 19835, 5);
			ShowItemBox(playerid, "Received 5x", "Nasi Goreng", 2355);
			ShowItemBox(playerid, "Received 5x", "Kopi Kenangan", 19835);
		}
	}	
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil mengambil hadiah natal!");
	AccountData[playerid][pXmasTime] = gettime() + 43200; // 12 jam 
	return 1;
}