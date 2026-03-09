#include <YSI\y_hooks>

enum e_gangzone
{
	gzSafezone,
};

new GangZoneData[e_gangzone];

enum e_area
{
	STREAMER_TAG_AREA:areaKanpol,
	STREAMER_TAG_AREA:areaHospital,
	STREAMER_TAG_AREA:areaWalkot,
	STREAMER_TAG_AREA:areabengkel,
	STREAMER_TAG_AREA:areaBandara,
	STREAMER_TAG_AREA:areaLadang,
	STREAMER_TAG_AREA:BandaraGreenZone,

	//job disnaker
	STREAMER_TAG_AREA:JobKayu,
	STREAMER_TAG_AREA:JobPenambang[3],
	STREAMER_TAG_AREA:JobBus,
	STREAMER_TAG_AREA:JobAyam[2],
	STREAMER_TAG_AREA:JobPenjahit,
	STREAMER_TAG_AREA:JobTukangSusu,
	STREAMER_TAG_AREA:JobPetani,
	STREAMER_TAG_AREA:JobKargo,
	STREAMER_TAG_AREA:JobRecycle[2],
};
new AreaData[e_area];

enum E_HUNTING
{
	STREAMER_TAG_AREA:Hunting,
	STREAMER_TAG_AREA:Penjahit,
	STREAMER_TAG_3D_TEXT_LABEL:HuntingStore
};
new HuntingArea[E_HUNTING];

enum e_areawarung
{
	STREAMER_TAG_AREA:warungVinewood,
	STREAMER_TAG_AREA:warungTerminal,
	STREAMER_TAG_AREA:warungAnglePine,
	STREAMER_TAG_AREA:warungGanton,
	STREAMER_TAG_AREA:warungSanFiero,
	STREAMER_TAG_AREA:warungAdmin,
	STREAMER_TAG_AREA:warungBengkel,
	STREAMER_TAG_AREA:warungPalomino,
	STREAMER_TAG_AREA:warungSFAriv,
	STREAMER_TAG_AREA:warungLV,
};
new WarungArea[e_areawarung];

hook IsPlayerInArea(playerid, Float:max_x, Float:min_x, Float:max_y, Float:min_y)
{
	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid, X, Y, Z);
	if(X <= max_x && X >= min_x && Y <= max_y && Y >= min_y) return true;
	return false;
}

stock LoadHuntingZone()
{
	HuntingArea[Hunting] = CreateDynamicRectangle(-690, -2482.4002075195312, -352, -2141.4002075195312);
	HuntingArea[HuntingStore] = CreateDynamic3DTextLabel(""GREEN"[Y] "WHITE"Menjual Hasil Hunting", -1, -1692.5179, -88.5486, 3.5670+0.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
	HuntingArea[Penjahit] = CreateDynamicRectangle(1734.80029296875, -1811.2001953125, 1813.80029296875, -1738.2001953125);
}

stock LoadAllJewelryRobArea()
{
    for(new i; i < 3; i++) CreateDynamic3DTextLabel("Untuk menukarkan jewelry\n{32ff24}'ALT'", -1, Jewelry_ChangeArea[i][0], Jewelry_ChangeArea[i][1], Jewelry_ChangeArea[i][2], 1.5);
    for(new i; i < 24; i++) Jewelry_Robbed[i] = 2;
    for(new i; i < 24; i++) Jewelry_RobbedText[i] = CreateDynamic3DTextLabel("{32ff24}Filled", -1, Jewelry_RobArea[i][0], Jewelry_RobArea[i][1], Jewelry_RobArea[i][2], 0.8);
}

stock LoadGangZone()
{
	GangZoneData[gzSafezone] = GangZoneCreate(-3000.0, -3000.0, 3000.0, 3000.0);
}

stock LoadArea()
{
	AreaData[areaWalkot] = CreateDynamicRectangle(1118, -2097.39990234375, 1515, -1924.39990234375);
	AreaData[areabengkel] = CreateDynamicRectangle(2222.80029296875, -1977.2001953125, 2321.80029296875, -1883.2001953125);
	AreaData[areaKanpol] = CreateDynamicRectangle(1013.199951171875, -1757.2001953125, 1180.199951171875, -1613.2001953125);
	AreaData[areaHospital] = CreateDynamicRectangle(1985.7877807617188, -1456.550048828125, 2100.7877807617188, -1349.550048828125);
	AreaData[areaBandara] = CreateDynamicRectangle(1555.9999389648438, -2390.4999084472656, 1826.9999389648438, -2183.4999084472656);
	AreaData[JobKayu] = CreateDynamicRectangle( -501.4124755859375, -121.074951171875, -415.4124755859375, -27.074951171875);
	AreaData[JobPenambang][0] = CreateDynamicRectangle(615.75, 806.324951171875, 702.75, 867.324951171875);	
	AreaData[JobPenambang][1] = CreateDynamicRectangle(2138.7877807617188, -2285.83740234375, 2244.7877807617188, -2201.83740234375);
	AreaData[JobPenambang][2] = CreateDynamicRectangle( -441.5250244140625, 1137.4874267578125, -356.5250244140625, 1209.4874267578125);
	AreaData[JobBus] = CreateDynamicRectangle(15.112548828125, -282.112548828125, 172.112548828125, -214.112548828125);
	AreaData[JobAyam][0] = CreateDynamicRectangle(1516.275146484375, -11.949951171875, 1594.275146484375, 59.050048828125);
	AreaData[JobAyam][1] = CreateDynamicRectangle(1887.275146484375, 122.050048828125, 1961.275146484375, 184.050048828125);
	AreaData[JobPenjahit] = CreateDynamicRectangle(2467.7877807617188, -62.987548828125, 2532.7877807617188, -13.987548828125);
	AreaData[JobTukangSusu] = CreateDynamicRectangle(212.875, 1031.3624267578125, 333.875, 1173.3624267578125);
	AreaData[JobPetani] = CreateDynamicRectangle(-330.6500244140625, -1432.58740234375, -158.6500244140625, -1306.58740234375);
	AreaData[JobKargo] = CreateDynamicRectangle(-1741.6875, -11.03759765625, -1673.6875, 66.96240234375);
	AreaData[JobRecycle][0] = CreateDynamicRectangle(2257.7877807617188, 2729, 2359.7877807617188, 2786);
	AreaData[JobRecycle][1] = CreateDynamicRectangle(-46.6875, 1318.449951171875, 57.3125, 1415.449951171875);
}
stock LoadWarungArea()
{
	WarungArea[warungVinewood] = CreateDynamicRectangle(1302.833251953125, -900.333251953125, 1332.833251953125, -857.333251953125);
	WarungArea[warungTerminal] = CreateDynamicRectangle(21.80010986328125, -289.38755798339844, 49.80010986328125, -253.38755798339844);
	WarungArea[warungAnglePine] = CreateDynamicRectangle( -2206.5, -2270, -2178.5, -2239);
	WarungArea[warungGanton] = CreateDynamicRectangle(2498.72216796875, -1539.111083984375, 2537.72216796875, -1511.111083984375);
	WarungArea[warungSanFiero] = CreateDynamicRectangle(-2359.5, 994.22216796875, -2323.5, 1024.22216796875);
	WarungArea[warungAdmin] = CreateDynamicRectangle(1453.27783203125, -1725.33349609375, 1492.27783203125, -1705.33349609375);
	WarungArea[warungBengkel] = CreateDynamicRectangle(33.833251953125, 1119.4444580078125, 59.833251953125, 1151.4444580078125);
	WarungArea[warungPalomino] = CreateDynamicRectangle(2570.72216796875, 51.333251953125, 2604.72216796875, 74.333251953125);
	WarungArea[warungSFAriv] = CreateDynamicRectangle(-2648.5, 1331.4444580078125, -2616.5, 1368.4444580078125);
	WarungArea[warungLV] = CreateDynamicRectangle(2292.72216796875, 934.22216796875, 2338.72216796875, 970.22216796875);
}

stock IsSafeZone(STREAMER_TAG_AREA:areaid)
{
	if(areaid == AreaData[areaBandara] || areaid == AreaData[areaKanpol] || areaid == AreaData[areaHospital] || areaid == AreaData[areaWalkot] || areaid == AreaData[areabengkel] 
		|| areaid == AreaData[JobKargo] || areaid == AreaData[JobPenambang][0] || areaid == AreaData[JobPenambang][1] || areaid == AreaData[JobPenambang][2] || areaid == AreaData[JobBus]
		|| areaid == AreaData[JobAyam][0] || areaid == AreaData[JobAyam][1] || areaid == AreaData[JobPenjahit] || areaid == AreaData[JobTukangSusu] || areaid == AreaData[JobPetani] 
		|| areaid == AreaData[JobKargo] || areaid == AreaData[JobRecycle][0] || areaid == AreaData[JobRecycle][1])
		return 1;

	return 0;
}

hook OnGameModeInit()
{
	LoadHuntingZone();
	LoadAllJewelryRobArea();
	GameModeClearJewelry();
	AreaData[areaLadang] = CreateDynamicRectangle( -331.1666259765625, -1414.444580078125, -167.1666259765625, -1314.444580078125);
	AreaData[BandaraGreenZone] = CreateDynamicRectangle(1572.60009765625, -2337.60009765625, 1744.60009765625, -2235.60009765625);
	return 1;
}

#include <YSI\y_hooks>

hook OnPlayerLeaveDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
	if(areaid == WarungArea[warungVinewood] || areaid == WarungArea[warungTerminal] || areaid == WarungArea[warungAnglePine]
		|| areaid == WarungArea[warungGanton] || areaid == WarungArea[warungSanFiero] || areaid == WarungArea[warungAdmin]
		|| areaid == WarungArea[warungBengkel] || areaid == WarungArea[warungPalomino] || areaid == WarungArea[warungSFAriv]
		|| areaid == WarungArea[warungLV]) 
	{
		if (DurringRobbery[playerid])
		{
			DurringRobbery[playerid] = false;
			AccountData[playerid][pRobMin] = 0;
			g_RobberyTime = 0;
			RobberyShowTD(playerid, "Perampokan warung gagal, anda terlalu~n~jauh dari warung!");
			PlayerTextDrawHide(playerid, RobberyTextTD[playerid][0]);
			SendClientMessageToAllEx(-1, "{201ee5}POLDA"WHITE": Perampokan dinyatakan clear karena tersangka meninggalkan tempat perampokan!");
		}
	}
	return 1;
}