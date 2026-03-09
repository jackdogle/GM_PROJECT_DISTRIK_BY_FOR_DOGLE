new g_ServerLocked;
new g_AsuransiAll; 
new g_AsuransiTime; 
new g_RestartServer; 
new g_RestartTime;
new g_RusunTime;
new g_RobberyTime = 0;
new g_Schedule;
new g_ScheduleTime;
new g_Message;
new g_MessageTimer;

/* Voting System */
new OpenVote = 0,
    VoteYes = 0,
    VoteNo = 0,
    VoteTime = 0,
    VoteText[128];

new bool: TogOOC;
new bool:TogOOCVip = true; 

new PlayerChar[MAX_PLAYERS][MAX_CHARS][MAX_PLAYER_NAME + 1];
new HouseMemberName[MAX_PLAYERS][3][MAX_PLAYER_NAME + 1];

new g_RaceCheck[MAX_PLAYERS];

new PlayerListitem[MAX_PLAYERS][200];

new CSelect[MAX_PLAYERS];
new SelectAcc[MAX_PLAYERS];
new BuyClothes[MAX_PLAYERS];
new BuyTopi[MAX_PLAYERS];
new BuyGlasses[MAX_PLAYERS];
new BuyTAksesoris[MAX_PLAYERS];
new BuyBackpack[MAX_PLAYERS];
	
new NearestVehicleID[MAX_PLAYERS];
new ShowroomVeh[MAX_PLAYERS];

new pTwitterPage[MAX_PLAYERS];

new TogIsiBensin[MAX_PLAYERS];
new STREAMER_TAG_AREA:PantaiArea[MAX_PLAYERS];
new STREAMER_TAG_3D_TEXT_LABEL: labelDisconnect[MAX_PLAYERS];
new labelDisconnectTimer[MAX_PLAYERS] = {-1, ...};
new NearestSingle[MAX_PLAYERS];
new ListBosDesk[MAX_PLAYERS][50];
new NearestPlayer[MAX_PLAYERS][MAX_PLAYERS];
new bool: pPassengerClickMap[MAX_PLAYERS];
new bool: pMapCP[MAX_PLAYERS];
new SharelocSender[MAX_PLAYERS];
new SharelocTimer[MAX_PLAYERS] = {0, ...};
new PlayerPressedJump[MAX_PLAYERS];
new bool: VehicleJobLocked[MAX_PLAYERS];
new Smoking[MAX_PLAYERS];
new IsDragging[MAX_PLAYERS];

/* Admin Onduty */
new ClothesDutyAdmin[MAX_PLAYERS];
new DutyStart[MAX_PLAYERS];   
new DutyLastTime[MAX_PLAYERS]; 
new gDutyTimer = 0; 

new Shakehand[MAX_PLAYERS] = {false, ...};
new ShakehandBy[MAX_PLAYERS] = {INVALID_PLAYER_ID, ...};

//billiard
new bool:InPool[MAX_PLAYERS];

// new bool:g_ucpActived[MAX_PLAYERS];

new color_string[3256], object_font[200];

new FixmeOption[MAX_PLAYERS];
new ListFixme[MAX_PLAYERS][MAX_PLAYERS];
new bool: FixmeExists[MAX_PLAYERS],
    FixmeTime[MAX_PLAYERS];

/* Forklift Stuffs */
new ForkliftVehicles[2];

/* Sweeper Stuffs */
new SweeperVehicles[3];
new SweeperIndex[MAX_PLAYERS];
new bool:DurringSweeping[MAX_PLAYERS];

/* Delivery Stuffs */
new DeliveryVehicles[2];
new TrashmasterVehicles[3];

/* Mowing Stuffs */
new MowerVehicles[3];

/* Quiz Stuffs */
new bool: Quiz;
new bool: QuizAnswerMade;
new QuizAnswer[255];
new QuizPrice;

/* Tunjangan */
new bool:PlayerTaserOn[MAX_PLAYERS] = {false, ...};

new bool: SignalExists[MAX_PLAYERS] = { false, ... },
    Float:SignalPos[MAX_PLAYERS][3],
    SignalTimer[MAX_PLAYERS],
    ListSignal[MAX_PLAYERS][MAX_PLAYERS];

new ClickPlayerID[MAX_PLAYERS];

new PlayerTextdraws[MAX_PLAYERS][playerTextdraws];

// mprice changed price
new TembagaPrice = 3;
new BesiPrice = 2;
new EmasPrice = 4;
new BerlianPrice = 100;
new MaterialPrice = 5;
new AlumuniumPrice = 13;
new KaretPrice = 5;
new KacaPrice = 10;
new BajaPrice = 12;
new AyamKemasPrice = 13;
new SusuOlahPrice = 13;
new PakaianPrice = 25;
new KayuKemasPrice = 21;
new GasPrice = 5;

new OldTembagaPrice;
new OldBesiPrice;
new OldEmasPrice;
new OldBerlianPrice;
new OldMaterialPrice;
new OldAlumuniumPrice;
new OldKaretPrice;
new OldKacaPrice;
new OldBajaPrice;
new OldAyamKemasPrice;
new OldSusuOlahPrice;
new OldPakaianPrice;
new OldKayuKemasPrice;
new OldGasPrice;

new bool: IsPlayerSmoking[MAX_PLAYERS] = { false, ... };
new CountSmoking[MAX_PLAYERS] = { 0, ... };
new SmokingDelayTime[MAX_PLAYERS] = { 0, ... };

new STREAMER_TAG_OBJECT: FireworkObject[MAX_PLAYERS];
new FireworkTimer[MAX_PLAYERS] = {-1, ...};

// Live mode
new bool: LivemodeOn[MAX_PLAYERS] = { false, ... };
new LivemodeTittle[MAX_PLAYERS][255];
new LoginTimer[MAX_PLAYERS];
new LoginAttemps[MAX_PLAYERS];

new Float:CameraRotation[MAX_PLAYERS];
new PlayerCameraTimer[MAX_PLAYERS];
new PreviewVehicle[MAX_PLAYERS];

//chosekarakter
new SelectCharIndex[MAX_PLAYERS], CharSkin[MAX_PLAYERS][MAX_CHARS];

new WarningTimer[MAX_PLAYERS],
    bool: ShowWarning[MAX_PLAYERS];

new bool:IsPlayerChangeSeat[MAX_PLAYERS] = { false, ... },
    ChangeSeatWithPlayerID[MAX_PLAYERS] = { INVALID_PLAYER_ID, ... },
    ChangeSeatVehicleID[MAX_PLAYERS] = { -1, ... };

new bool: PlayerVoting[MAX_PLAYERS] = { false, ... };

new ListedVehObject[MAX_PLAYERS][MAX_VEHICLE_OBJECT], // Untuk menyimpan index id array vehicle object ke playerid
    Player_EditingObject[MAX_PLAYERS], // Sebagai flagger untuk menandakan player sedang edit object atau tidak 
    Player_EditVehicleObject[MAX_PLAYERS], // Variable Holder
    Player_EditVehicleObjectSlot[MAX_PLAYERS] // Variable Holder
;

//showroomwarna
new pWarna1[MAX_PLAYERS], pWarna2[MAX_PLAYERS];

// new CircleHunger[MAX_PLAYERS],
//     CircleThirst[MAX_PLAYERS],
//     CircleStress[MAX_PLAYERS]
// ;

new bool:g_RSLeftDoorOpened,
    STREAMER_TAG_AREA:RSLeftDoorSensor,
    STREAMER_TAG_OBJECT:RSDoor[2];

new hargalow,
    hargamedium,
    hargahigh,
    hargaspecial;

new PlayerNIK[MAX_PLAYERS][17];
new CamZoomLevel[MAX_PLAYERS];
new PlayerUfo_Veh[MAX_PLAYERS],
    PlayerUfo_Obj[MAX_PLAYERS];


#define MAX_RACE_PLAYERS 6
#define MAX_RACE_CP 10

new bool:gAdminRaceActive = false;
new gAdminRaceLapCount;
new gAdminRaceVehicleModel;
new gAdminRacePlayers[MAX_PLAYERS];
new gAdminRaceTotalPlayers;
new bool:gRaceVehicleAdm[MAX_VEHICLES];
new gRaceFinishRank[3];
new gRaceFinishCount = 0;
new Float:gRaceStartPos[MAX_PLAYERS][4];

new bool:gRaceStarted;
new gRaceTotalPlayers;
new gRaceLapCount;
new gRacePlayers[MAX_RACE_PLAYERS];
new bool: raceWinnerDeclared = false;
new bool:gRacePlayerReady[MAX_PLAYERS];
new bool:gInRaceNow[MAX_PLAYERS];
new rLastCPTime[MAX_PLAYERS];

new Float:gRaceSpawnPos[MAX_RACE_PLAYERS][4] =
{
    {-858.9254,-130.1109,60.0591,284.3603},
    {-860.3360,-125.1663,60.0573,284.3603},
    {-868.2737,-126.3832,59.2729,284.3603},
    {-866.1514,-132.5015,59.3088,284.3603},
    {-874.1900,-131.5294,58.7336,284.3603},
    {-883.3556,-133.4204,57.9914,284.3603}
};

new Float:gRaceCP[MAX_RACE_CP][3] = {
    {-811.6147,-113.1818,63.3311},
    {-678.9883,-31.7449,70.4910},
    {-887.3073,-40.5796,34.1407},
    {-684.2618,101.9558,21.2076},
    {-735.4508,212.4000,2.4450},
    {-258.4902,253.6758,8.6892},
    {-301.5826,-172.8701,1.0781},
    {-492.2440,-273.7877,49.1391},
    {-943.3107,-216.0252,40.0363},
    {-833.2092,-120.0987,62.4399}
};

new raceCountdown = 5;
new countdownTimer;

//TDINDEX
new bool:HbeIndex[MAX_PLAYERS];
new GudangLastUse[MAX_PLAYERS];

new g_BerankasCode[MAX_DYNAMIC_ROBBERY];
//new Text3D:g_BerankasLabel[MAX_DYNAMIC_ROBBERY];
new g_PlayerRobbery[MAX_PLAYERS]; // -1 kalau gak sedang rampok
new pTimerOpenRobb[MAX_PLAYERS] = {-1, ...};

new Drones[MAX_PLAYERS];
new pUpgradeBagasiTimer[MAX_PLAYERS];

//Jewelry Store
#define JewelryHack_Input (15312)
new bool:JewelryHack_IsOpened;
new JewelryHack_Hack[6];
new JewelryHack_Command[50];
new bool:JewelryHack_CommandRunning;
new bool:JewelryHack_CommandChecked;
new JewelryHack_TimerCount;
new JewelryHack_Timer;
new JewelryHack_HackSuccess;
new bool:JewelryHack_Alarm;
new JewelryHack_Player;
new bool:JewelryHack_Completed;

//Jewelry Store Area
new Jewelry_Robbed[24];
new Text3D:Jewelry_RobbedText[24];
new Float:Jewelry_RobArea[24][3] = {
    {963.3287, -1470.1110, 13.8521},
    {963.2708, -1466.1947, 13.8521},
    {963.3546, -1462.2048, 13.8521},
    {966.3413, -1462.2821, 13.8521},
    {966.3499, -1466.2981, 13.8521},
    {966.3652, -1470.0925, 13.8521},
    {969.6666, -1467.0049, 13.8521},
    {969.6389, -1462.9927, 13.8521},
    {969.6581, -1458.9386, 13.8521},
    {972.6834, -1458.9669, 13.8521},
    {972.6473, -1463.1176, 13.8521},
    {972.7037, -1467.1292, 13.8521},
    {976.3317, -1470.0948, 13.8521},
    {976.3176, -1466.0374, 13.8521},
    {976.3005, -1462.0776, 13.8521},
    {979.3088, -1462.0653, 13.8521},
    {979.3423, -1466.2300, 13.8521},
    {979.3350, -1470.1029, 13.8521},
    {982.6064, -1467.2024, 13.8521},
    {982.6147, -1463.1522, 13.8521},
    {982.6365, -1458.9709, 13.8521},
    {985.6215, -1458.9683, 13.8521},
    {985.6393, -1463.0977, 13.8521},
    {985.6312, -1466.9940, 13.8521}
};
new Float: Jewelry_ChangeArea[3][3] = {
    {297.5253,-169.6326,1.5781},
    {-2434.1377,2293.4856,4.9844},
    {-300.4551,2658.3723,63.1989}
};

//Jewelry Store (Player)
new isRobbing_Jewelry[MAX_PLAYERS];
new isHaveJewelry[MAX_PLAYERS];
new isCoordinat_ChangeJewelry[MAX_PLAYERS];

new PlayerText:JewelryHackPTD[MAX_PLAYERS][9];


new Robbank_Robbed[3];
new Text3D:Robbank_TextCash[3];
new RobbankColdown = 0;
new RobbankColdownTimeLeft = 0;
new RobbankTimer;
new Float: Robbank_AreaCash[3][3] = {
    {1416.1708,-1123.3528,10.5234},
    {1421.1434,-1124.8334,10.5234},
    {1420.9835,-1123.0837,10.5234}
};

new Float: Robbank_Gold[3][3] = {
    {-1630.6548,-2240.2559,31.4766},
    {-398.9006,-422.2060,16.2109},
    {2006.9318,2908.7336,47.8231}
};

new IsCoordinatBankGold[MAX_PLAYERS];

#define MAX_FIRE 50
enum ApiUnggun_t 
{
    STREAMER_TAG_OBJECT:aObject,
    STREAMER_TAG_3D_TEXT_LABEL:aText,
    STREAMER_TAG_AREA:aArea,
    Float:aX,
    Float:aY,
    Float:aZ,
    aVW,
    aInt,
    aOwner,
    aUsed
};
new ApiUnggun[MAX_FIRE][ApiUnggun_t]; 

#define MAX_COOKING 50
enum Cooking_t 
{
    cPlayer,
    cFireIndex,
    cFishType,
    STREAMER_TAG_OBJECT:cObject,
    cTimer,
    cUsed
};
new Cooking[MAX_COOKING][Cooking_t]; 

new isFixingVehicle[MAX_PLAYERS];
new FixVehicleTarget[MAX_PLAYERS];

new pCookingTimer[MAX_PLAYERS];
new bool:Minigame_Locked[MAX_PLAYERS];
new bool:MinigamePH_Locked[MAX_PLAYERS];
new pTimerRobbank[MAX_PLAYERS];


/*Spotify Systems*/
#define MAX_SPOTIFY_HISTORY 6

new SpotifyHistory[MAX_PLAYERS][MAX_SPOTIFY_HISTORY][256]; // URL lagu
new SpotifyTitle[MAX_PLAYERS][MAX_SPOTIFY_HISTORY][128];   // Judul lagu
new SpotifyCount[MAX_PLAYERS];                              // Jumlah history aktif
new tempSpotifyURL[MAX_PLAYERS][256];                 // URL sementara sebelum input judul

#define MAX_RUMAH 1000
new PlayerHouseList[MAX_PLAYERS][MAX_RUMAH]; 

new pSelectWarungUse[MAX_PLAYERS];
new pUnselectWarungUse[MAX_PLAYERS];
new const WarungHarga[11] = {
    250,
    200,
    55,
    150,
    80,
    18,
    150,
    650,
    1000,
    55,
    2200
};

new bool:pHelmetin[MAX_PLAYERS];
new bool:pHiu[MAX_PLAYERS];

#define MAX_KARGO 3

new Float:KargoCheckpoint[MAX_KARGO][3] = {
    {-1324.5941, 2690.4990, 50.0625},      // Solar
    {1945.1184, -1772.5514, 13.3906},     // Dexlite
    {-2405.2263, 975.4719, 45.2969}       // Pertamax
};

new KargoRemakeUsed[MAX_PLAYERS];


enum lockerDataEnum {
    lID,
    lWeapon,
    lAmmo,
    lOwner[24]
}
new lockerData[MAX_LOCKER][lockerDataEnum];
new lockerCount;
new g_PendingTake[MAX_PLAYERS];

new PlayerSpawn[MAX_PLAYERS];

new bool:CreateCharStepDone[MAX_PLAYERS][5];

new LootWeapons[MAX_PLAYERS][MAX_WEAPON_SLOT];
new LootAmmo[MAX_PLAYERS][MAX_WEAPON_SLOT];
new LootMap[MAX_PLAYERS][MAX_WEAPON_SLOT];