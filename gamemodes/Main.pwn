#if defined JVTR
        ___  ________  ___      ___ ________                                    
       |\  \|\   __  \|\  \    /  /|\   __  \
       \ \  \ \  \|\  \ \  \  /  / | \  \|\  \
     __ \ \  \ \   __  \ \  \/  / / \ \   __  \
    |\  \\_\  \ \  \ \  \ \    / /   \ \  \ \  \
    \ \________\ \__\ \__\ \__/ /     \ \__\ \__\
     \|________|\|__|\|__|\|__|/       \|__|\|__|                               
                                                                            
                                                                            
                                                                            
     _________  ___  ___  _______   ________  _________  _______   ________     
    |\___   ___\\  \|\  \|\  ___ \ |\   __  \|\___   ___\\  ___ \ |\   __  \
    \|___ \  \_\ \  \\\  \ \   __/|\ \  \|\  \|___ \  \_\ \   __/|\ \  \|\  \
         \ \  \ \ \   __  \ \  \_|/_\ \   __  \   \ \  \ \ \  \_|/_\ \   _  _\
          \ \  \ \ \  \ \  \ \  \_|\ \ \  \ \  \   \ \  \ \ \  \_|\ \ \  \\  \| 
           \ \__\ \ \__\ \__\ \_______\ \__\ \__\   \ \__\ \ \_______\ \__\\ _\
            \|__|  \|__|\|__|\|_______|\|__|\|__|    \|__|  \|_______|\|__|\|__|

	            Update and optimize by ahmazuqi & fix bug yahiko and ken botak

#endif
#pragma compress 0
#pragma dynamic	 1000000

#pragma warning disable 208
#pragma warning disable 219

#define CGEN_MEMORY 30000
#define YSI_NO_HEAP_MALLOC

/* Includes */
#include <a_samp>

#undef MAX_PLAYERS
#define MAX_PLAYERS 100

#include <memory>
#include <map-zones>

#include <a_mysql>
#include <a_zones>
#include <streamer>
#include <sscanf2> 
#include <gvar>
#include <crashdetect>

#include <YSI_Coding\y_timers>      		//by Y_Less from YSI
#include <YSI_Server\y_colours\x11def>      //by Y_Less from YSI
#include <YSI_Storage\y_ini>				//by Y_Less from YSI
#include <easyDialog> 
#include <Pawn.CMD>
#include <FiTimestamp>
#define ENABLE_3D_TRYG_YSI_SUPPORT
//sendto
#define DIALOG_SENDTO_PLAYER 1000
#define DIALOG_SENDTO_LOC    1001
//#include <colandreas>
#include <3DTryg>
#include <EVF2>

#include <nex-ac>                   //BY Nexus
#include <nex-ac_id.lang> 

#include <strlib>                   //by Slice
#include <sampvoice>
#include <selection>
#include <garageblock>
#include <cb>

#include <textdraw-streamer>
#include <progress2>
#include <a_http>
#define WEBHOOK_ADMIN   "https://discord.com/api/webhooks/1480637893558013953/KlQ6An5gUK23liJKY4-7I93wQ6fX5GQucvyNsj9L7uESBDTTny8G3UwnmY68gk2lBbH-"
#define WEBHOOK_PAY		"https://discord.com/api/webhooks/1480637902588346451/3z2jhtY8syxui0DV95WJU5KZVcE7Jqu9DFsU4M-3aTVFfULPPY3QOIPWaGlAd0OKyPmG"
#define WEBHOOK_DEATH	"https://discord.com/api/webhooks/1480637951095345174/i42T4Xzl6dXIuPU8EUaM8TZWB3zYqP08azK7VXuut1FY4sTr9rYsov2TdIa0GgsadKjT"
//#define MAKE_PELER
#if defined MAKE_PELER
    #include <profiler>
#endif

//#include <WazeGPS>
//#include <GPS>
//#include <VehPara>

// #include <ndialog-pages>

/* Includes 
#include <a_samp>
#include <streamer>					//by Incognito
#include <sscanf2>					//by Y_Less fixed by maddinat0r & Emmet_
#include <a_mysql>
#include <map-zones>

#include <crashdetect>				//by Southclaws
#include <gvar>						//by Incognito

#include <Pawn.CMD> 				//
#include <FiTimestamp>

#include <EVF2>
#include <selection>

#include <YSI\y_timers>      		//by Y_Less from YSI
#include <YSI\y_colours>            //by Y_Less from YSI
#include <YSI\y_ini>				//by Y_Less from YSI

#define ENABLE_3D_TRYG_YSI_SUPPORT
#include <3DTryg>

#include <AC_Black_Diamond>

#include <nex-ac>					//
#include <strlib>					//
#include <easyDialog>				//
#include <sampvoice>
#include <garageblock>
#include <cb>						//by Emmet
// #include <Circulo>
// #include <noclass>
#include <textdraw-streamer>		//by Nex*/
new pUseItemTimer[MAX_PLAYERS] = {-1, ...};
new Count = -1;
new countTimer;
new showCD[MAX_PLAYERS];
new CountText[5][5] =
{
	"~r~1",
	"~y~2",
	"~y~3",
	"~y~4",
	"~y~5"
};

new 
	WorldWeather = 1;

new MySQL: g_SQL;

enum
{
	NOTIFICATION_ERROR,
	NOTIFICATION_SUKSES,
	NOTIFICATION_WARNING,
	NOTIFICATION_INFO,
	NOTIFICATION_SYNTAX
};

enum 
{
	DEFAULT_XP = 5
};

/* Player Enums*/
enum E_PLAYERS
{
	pID,
	pUCP[22],
	pExtraChar,
	pChar,
	pName[MAX_PLAYER_NAME],
	pAdminname[MAX_PLAYER_NAME],
	pIP[16],
	pVerifyCode,
	pPassword[65],
	pSalt[17],
	pAdmin,
	pLevel,
	pLevelUp,
	pVip,
	pVipNameCustom[256],
	pVipTime,
	pExtraVehSlot,
	pHouseSlot,
	pRegDate[50],
	pLastLogin[50],
	pLastSpawn,
	pMoney,
	pRedMoney,
	pMenuType,
	pTransferWS,
	pGpsActive,
	STREAMER_TAG_3D_TEXT_LABEL:pMaskLabel,
	STREAMER_TAG_3D_TEXT_LABEL:pLabelDuty,
	STREAMER_TAG_3D_TEXT_LABEL:LiveStream,
	pBankMoney,
	pSaldoGopay,
	pTargetGopay,
	pJumlahGopay,
	pBankRek,
	Smartphone,
	pPhone[32],
	pContact,
	pCall,
	pHours,
	pMinutes,
	pSeconds,
	pPaycheck,
	pSkin,
	pFacSkin,
	pGender,
	pUniform,
	pUsingUniform,
	pAge[50],
	pOrigin[32],
	pTinggiBadan,
	pBeratBadan,
	pInDoor,
	pInHouse,
	pInRusun,
	pInBiz,
	pInFamily,
	Float: pPosX,
	Float: pPosY,
	Float: pPosZ,
	Float: pPosA,
	pInt,
	pWorld,
	Float:pHealth,
    Float:pArmour,
	pHunger,
	pThirst,
	pHungerTime,
	pThirstTime,
	pStress,
	pStressTime,
	pInjured,
	pInjuredTime,
	pOnDuty,
	pFaction,
	pFactionRank,
	pTazer,
	pTaserGun,
	pLastShot,
	pShotTime,
	pStunned,
	pFamily,
	pFamilyRank,
	pJail,
	pJailTime,
	pJailReason[126],
	pJailBy[MAX_PLAYER_NAME],
	pArrest,
	pArrestTime,
	pWarn,
	pJob,
	pMask,
	pMaskID,
	pMaskOn,
	pHelmet,
	pGuns[13],
    pAmmo[13],
	pWeapon,
	Cache:Cache_ID,
	bool: IsLoggedIn,
	LoginAttempts,
	pSpawned,
	pAdminDuty,
	pAdminHide,

	//HandleGoodside && HandleBadside
	pHandleGoodside,
	pHandleBadside,

	//Handle Banned
	pHandleBanned,

	//admin girl
	pAdminGirl,

	//the star
	pTheStars,
	pTheStarsTime,

	pFreezeTimer,
	pFreeze,
	pSPY,
	pTogPM,
	pTogGlobal,
	pTogWT,
	Text3D:pAdoTag,
	bool:pAdoActive,

	FixVehTimer,
	
	pFlare,
	bool:pFlareActive,
	pFlareIcon[MAX_PLAYERS],

	pTrackCar,
	pTrackHoused,
	pCuffed,
	toySelected,
	bool:PurchasedToy,
	pEditingItem,
	pEditingAmmount,
	pProductModify,
	pCurrSeconds,
	pCurrMinutes,
	pCurrHours,
	pSpec,
	playerSpectated,
	pFriskOffer,
	pDragged,
	pDraggedBy,
	pDragTimer,
	pHelmetOn,
	pSeatBelt,
	pReportTime,
	pAskTime,
	pActivity,
	pActivityStatus,
	pActivityTime,
	Float: ActivityTime,
	Float: NotifyTime,
	pLoadingBar,
	pTimerLoading,
	pDiPesawat,
	//Jobs
	pSideJob,
	pSideJobTime,
	pSweeperTime,
	pBusTime,
	pMowerTime,
	pVehicleFaction,
	pMechVeh,
	EditingSAMPAHID,
	EditingPOMID,
	EditingATMID,
	EditingROBERID,
	EditingLADANGID,
	EditingUraniumID,
	EditingDeerID,
	bool: pOnBusJob,
	pTransfer,
	pTransferRek,
	pTransferName[128],
	gEditID,
	gEdit,
	pHead,
 	pPerut,
 	pLHand,
 	pRHand,
 	pLFoot,
 	pRFoot,
 	pDutyTimer,
	pPark,
	pACWarns,
	pACTime,
	pJetpack,
	pArmorTime,
	pLastUpdate,
	pBus,
	pSweeper,
	pMower,
	pSpeedTime,
	pLoopAnim,
	SelectBandara,
	SelectPelabuhan,
	SelectRusun,
	SelectRumah,
	SelectLastExit,
	pSelectItem,
	pListItem,
	pListItemGudang,
	pBagasiTake,
	pVehListItem,
	pStorageGudang,
	pGiveInv,
	pAmountInv,
	pPmin,
	pPsec,
	pBsec,
	pCSmin,
	pCSsec,
	pDipanggilan,
	pTargetAirdrop[10],
	pNamaAirdrop[32],
	pNomorAirdrop[32],
	pNominal,
	pRekening,
	pTargetFamily[10],
	pOnBadai,
	pGSec,
	pDutyPD,
	pDutyPemerintah,
	pDutyEms,
	pDutyBengkel,
	pDutyPedagang,
	pDutyGojek,
	pDutyTrans,
	pDutyKargo,
	pRespawnVehJob,
	pTimerRespawn,
	pTimerSpawnKanabis,
	pEditingPenumpang,
	pSignalTime,
	pEarphone,
	pRadio,
	pAsapRokok,
	pHisapRokok,
	pMancing,
	Float: pBeratItem,
	Float: pRusunCapacity,
	Float: pGudangCapacity,
	pJerigenUse,
	bool:pActionActive,
	pHasGudangID,
	pGudangRentTime,
	pOwnedRusun,
	Ktp,
	pKtpTime,
	LastSpawn,
	Spawned,
	pRobSec,
	pRobMin,
	pPaycheckTime,
	pSimA,
	pSimB,
	pSimC,
	pSimATime,
	pSimBTime,
	pSimCTime,
	pGunLic,
	pGunLicTime,
	pHuntingLic,
	pHuntingLicTime,
	pStorageSelect,
	DownloadWhatsapp,
	DownloadSpotify,
	DownloadGojek,
	DownloadTwitter,
	EngineOn,
	pSpeedLimit,
	GarkotVehList,
	ClickSpawn,
	pInviteRusun,
	pInviteHouse,
	pInviteAccept,
	pKompensasi,
	pGoodMood,
	pOwnedHouse,
	pOpenBackpackTimer,
	pDealerVeh,
	pTempName[MAX_PLAYER_NAME],
	pTempValue,
	pTempVehID,
	pTempVehJobID,
	pTempSQLFactMemberID,
	pTempSQLFactRank,
	pTempSQLFamMemberID,
	pTempSQLFamRank,
	pTempText[320],
	pTempPlayerID,
	pTempCallNumber,
	pSKS,
	pSKSTime,
	pSKSNameDoc[128],
	pSKSRankDoc[128],
	pSKSReason[128],
	pSKCK,
	pSKCKTime,
	pSKCKNamePol[128],
	pSKCKRankPol[128],
	pSKCKReason[128],
	pBPJS,
	pBPJSTime,
	pBPJSLevel[128],
	pSKWB,
	pSKWBTime,
	pCarSeller,
    pCarOffered,
    pCarValue,
	pTogAutoEngine,
	phoneShown,
	pCaller,
	pDurringKarung,
	pProgress,
	pTarget,
	pVehAudioPlay,
	hsAudioPlay,
	pHotlineTime,
	pTraceTime,
	TwitterName[128],
	TwitterPassword[128],
	Twitter,
	SpotifyName[128],
	SpotifyPassword[128],
	Spotify,
	bool: pTurningEngine,
	bool: UsingDoor,
	bool: CurrentlyReadWA,
	bool: CurrentlyReadYellow,
	bool: CurrentlyReadTwitter,

	bool: EMSDuringReviving,

	pTrashmaster,
	pTrashmasterDelay,
	pLastVehicle,
	pDeliveryTime,
	pForkliftTime,
	pInGas,
	pTrackGs,

	pTempTarget,

	//toys
	bool:PurchasedToyAxp,
	bool:PurchasedDragonToy,
	bool:PurchasedSonicToy,
	bool:PurchasedGrinchToy,
	bool:PurchasedGhostToy,

	/* Dragging */
	pDragOffer,
	pFriendHouseID,

	pFixmeTime,
	pTempOlah,
	pClaimStarterpack,

	//beneffit girl
	pBenefitGirl,

	//benefit boosters
	pBenefitBooster1,
	pBenefitBooster2,

	bEditID,
	bEdit,

	pEditSlotID,

	pBusDelay,

	/* Taxi Stuffs */
	pTaxiDuty,
	pTaxiOrder,
	pTaxiPlayer,
	pTaxiFee,
	pTaxiRunDistance,
	Float:tPos[3],
	
	//saving
	aReceivedReports,
	aDutyTimer,
	pFashionItem,

	pSelectedSlot,
	pFactionEdit,

	pOwnPara,

	//notsave
	bool: AirdropPermission,
	bool:phoneAirplaneMode,
	bool:phoneDurringConversation,
	bool:phoneIncomingCall,
	phoneCallingWithPlayerID,
	phoneCallingTime,
	phoneCallRingtone[128],

	pFactDutyTimer,
	Float:pMapSettings,
	pMapRender,
	pSuspectTimer,
	bool: menuShowed,
	playerClickSpawn,
	pTogSpy,
	OnlineTimer,
	bool: ToggleFPS,
	DokterLokalTimer,
	RobJewelryTimer,
	RobbankCashTimer,

	pLastPay,

	//workshop
	pMechanic,
	pMechColor1,
	pMechColor2,
	pWorkshop,
	pWorkshopRank,
	pWsInvite,
	pWsOffer,

	pCheckpoint,
	pXmasTime,
	pTogAC,
	pStyleNotif,
	
	pShowFooter,
	pFooterTimer,

	//Afk System
	Float:pAFKPos[6],
	pAFK,
	pAFKTime,
	pAFKCode,

	pEditTextObject,
	pHUDMode,
	bool: pNameTagShown,
	bool: pNtagShown,

	bool: pFlashShown,
	bool: pFlashOn,

	pJobVehicle,

	//whatsapp
	pWAMessage,
};
new AccountData[MAX_PLAYERS][E_PLAYERS];

enum
{
	DIALOG_MAKE_CHAR,
	DIALOG_CHARLIST,
	DIALOG_VERIFYCODE,
	DIALOG_UNUSED,
    DIALOG_LOGIN,
    DIALOG_REGISTER,
    DIALOG_AGE,
	DIALOG_ORIGIN,
	DIALOG_TINGGIBADAN,
	DIALOG_BERATBADAN,
	DIALOG_GENDER,
	DIALOG_TOY,
	DIALOG_TOYEDIT,
	DIALOG_TOYEDIT_ANDROID,
	DIALOG_TOYPOSISI,
	DIALOG_TOYPOSISIBUY,
	DIALOG_TOYVIP,
	DIALOG_TOYPOSX,
	DIALOG_TOYPOSY,
	DIALOG_TOYPOSZ,
	DIALOG_TOYPOSRX,
	DIALOG_TOYPOSRY,
	DIALOG_TOYPOSRZ,
	DIALOG_TOYPOSSX,
	DIALOG_TOYPOSSY,
	DIALOG_TOYPOSSZ,
	DIALOG_HELP,
	DIALOG_EDITBONE,
	DIALOG_REPORTS,
	DIALOG_REPORTSREPLY,
	DIALOG_ASKS,
	DIALOG_ASKSREPLY,
	DIALOG_HEALTH,
	DIALOG_TDM,
	DIALOG_DISNAKER,
	DIALOG_MEMBERI,
	DIALOG_SETAMOUNT,
	DIALOG_MODIF,
	DIALOG_MODIF_VELG,
	DIALOG_MODIF_SPOILER,
	DIALOG_MODIF_HOODS,
	DIALOG_MODIF_VENTS,
	DIALOG_MODIF_LIGHTS,
	DIALOG_MODIF_EXHAUSTS,
	DIALOG_MODIF_FRONT_BUMPERS,
	DIALOG_MODIF_REAR_BUMPERS,
	DIALOG_MODIF_ROOFS,
	DIALOG_MODIF_SIDE_SKIRTS,
	DIALOG_MODIF_BULLBARS,
	DIALOG_MODIF_NEON,
	
	DIALOG_STREAMER_CONFIG,
	DANN_RENTAL,
	DANN_UNRENT,
	DANN_ASURANSI,
	DANN_BUYALATSTEAL,
	DANN_PILIHSPAWN,
	DANN_PICKUPVEH,
	DANN_DYNHELP,

	DIALOG_RUSUN,
	DIALOG_RUSUN_OWNED,
	DIALOG_RUSUN_BRANKAS,
	DIALOG_RUSUN_INVITE,
	DIALOG_RUSUN_INVITECONF,
	DIALOG_RUSUN_BROPTION,
	DIALOG_RUSUN_MENU,
	DIALOG_RUSUNOWNED,
	DIALOG_RUSUNOPENSTORAGE,
	DIALOG_RUSUNITEM,

	DIALOG_RUSUNVAULT_DEPOSIT,
	DIALOG_RUSUNVAULT_WITHDRAW,
	DIALOG_RUSUNVAULT_IN,
	DIALOG_RUSUNVAULT_OUT,
	
	DIALOG_KAYU_START,
	DIALOG_SUSU_START,
	DIALOG_MINYAK_START,
	DIALOG_AYAM_START,
	DIALOG_MOWER_START,
	DIALOG_STEAL_SHOP,
	DIALOG_IKEA_MENU,
	DIALOG_IKEA_BESI,
	DIALOG_IKEA_BERLIAN,
	DIALOG_IKEA_EMAS,
	DIALOG_IKEA_TEMBAGA,
	DIALOG_IKEA_AYAMKEMAS,
	DIALOG_IKEA_KAYUKEMAS,
	DIALOG_IKEA_GAS,
	DIALOG_IKEA_PAKAIAN,

	DIALOG_FARMER_OLAH,
	DIALOG_LOUNGES_MASAK,
	DIALOG_HUNTING_SELL,
	DIALOG_BAGASISTORAGE,

	DIALOG_GUDANG,
	DIALOG_GUDANGSTOP,
	DIALOG_GUDANGOPTION,
	DIALOG_GUDANGOWNED,
	DIALOG_GUDANGITEM,
	DIALOG_GUDANGDEPOSIT,
	DIALOG_GUDANGWITHDRAW,

	DIALOG_LIST_ELEK, 
	DIALOG_LIST_CLOTHES,
	
	AdminList,

	LokasiGps,
	LokasiUmum,
	LokasiPekerjaan,
	LokasiHobi,
	LokasiPertokoan,
	LokasiHouseTersedia,
	DialogWarung,
	BeliNasduk,
	BeliAqua,
	BeliUmpan,
	DialogGadget,
	DANN_BOOMBOX,
	DANN_BOOMBOX1,
	DialogSpotify,
	DialogSpotify1,
	DialogSpotifyTitle,
	DialogFish,
	DialogCargo,
	DialogSpawn,
	DialogDropItem,
	DialogTransfer,
	DialogTransfer1,
	DialogBankConfirm,
	DialogElist,
	// -----------
	DialogShowroom,
	DialogAsuransi,
	// -------------
	DialogKontak,
	DialogOpenContact,
	DialogContact,
	DialogTelepon,
	DialogContactMenu,
	DialogGarasiKota,
	DialogMyVeh,
	DialogTrackMyVeh,
	DialogBagasi,
	// -----------
	DialogToyEdit,

	DIALOG_CRAFTING,
	DIALOG_CRAFTINGCONF,
	DIALOG_FAMILY_PANEL,
	DIALOG_FAMSTAKE_REDMONEY,
	DIALOG_FAMSTAKE_MONEY,
	DIALOG_FAMGARAGE_OUT,
	DIALOG_BLACKMARKET,
	
	DIALOG_DEPOSIT_POLICE,
	DIALOG_WITHDRAW_POLICE,

	DIALOG_POLVAULT,
	DIALOG_POLVAULT_DEPOSIT,
	DIALOG_POLVAULT_WITHDRAW,
	DIALOG_POLVAULT_IN,
	DIALOG_POLVAULT_OUT,

	DIALOG_POLICE_PANEL,
	DIALOG_POLICE_BOSDESK,
	DIALOG_POLICESETRANK,
	DIALOG_POLICEKICKMEMBER,
	DIALOG_RANK_SET_POLISI,
	DIALOG_POLICE_INVITE,
	DIALOG_POLICE_GARAGE,
	DIALOG_POLICE_GARAGE_BUY,
	DIALOG_POLICE_GARAGE_DEL,
	DIALOG_POLICE_HELI_GARAGE,
	DIALOG_POLICE_HELI_BUY,
	DIALOG_POLICE_HELI_GARAGE_OUT,
	DIALOG_POLICE_GARAGE_OUT,
	DIALOG_POLICE_IMPOUND,
	DIALOG_POLICE_TAKE_IMPOUND,
	DIALOG_FEDERAL_GARAGE,
	DIALOG_FEDERAL_GARAGE_BUY,
	DIALOG_FEDERAL_GARAGE_OUT,
	DIALOG_PDM,
	DIALOG_PDM_VEHICLE,
	DIALOG_PDM_VEHICLE_IMPOUND,
	DIALOG_PDM_OBJECT,
	DIALOG_ADD_HKRIMINAL,
	DIALOG_REMOVE_HKRIMINAL,
	DIALOG_LOCKER_LIST,
	DIALOG_LOCKER_CONFIRM,
	
	DIALOG_EMS_PANEL,
	DIALOG_EMS_GARAGE,
	DIALOG_EMS_GARAGE_BUY,
	DIALOG_EMS_GARAGE_TAKEOUT,
	DIALOG_EMS_GARAGE_DELETE,
	DIALOG_EMSBRANKAS,
	DIALOG_EMSBKCONFIRM,
	DIALOG_EMS_BOSDESK,
	DIALOG_EMS_INVITE,
	DIALOG_EMS_LOCKER,
	DIALOG_EMS_CLOTHES,
	DIALOG_EMSSETRANK,
	DIALOG_EMSKICKMEMBER,
	DIALOG_RANK_SET_EMS,
	DIALOG_DEPOSIT_EMS,
	DIALOG_WITHDRAW_EMS,

	DIALOG_EMSVAULT,
	DIALOG_EMSVAULT_DEPOSIT,
	DIALOG_EMSVAULT_WITHDRAW,
	DIALOG_EMSVAULT_IN,
	DIALOG_EMSVAULT_OUT,
	// ------------------ PEMERINTAH
	DIALOG_PEMERINTAH_LOCKER,
	DIALOG_PEMERINTAH_LOCKERMALE,
	DIALOG_PEMERINTAH_LOCKERFEMALE,
	DIALOG_PEMERINTAH_PANEL,
	DIALOG_PEMERINTAH_BOSDESK,
	DialogGudangList,
	DialogInputGudang,
	DIALOG_PEMERSETRANK,
	DIALOG_PEMERKICKMEMBER,
	DIALOG_RANK_SET_PEMERINTAH,
	DIALOG_PEMERINTAH_INVITE,
	DIALOG_PEMERINTAH_DEPOSIT,
	DIALOG_PEMERINTAH_WITHDRAW,
	DIALOG_PEMER_GARAGE,
	DIALOG_PEMER_GARAGE_BUY,
	DIALOG_PEMER_GARAGE_TAKEOUT,
	DIALOG_PEMER_GARAGE_DELETE,
	
	DIALOG_PEMERVAULT,
	DIALOG_PEMERVAULT_DEPOSIT,
	DIALOG_PEMERVAULT_WITHDRAW,
	DIALOG_PEMERVAULT_IN,
	DIALOG_PEMERVAULT_OUT,

	DIALOG_PEDSETRANK,
	DIALOG_PEDKICKMEMBER,
	DIALOG_RANK_SET_PEDAGANG,
	DIALOG_LOCKERPEDAGANG,
	DIALOG_PEDAGANG_GARAGE,
	DIALOG_PEDAGANG_GARAGE_BUY,
	DIALOG_PEDAGANG_GARAGE_TAKEOUT,
	DIALOG_PEDAGANG_GARAGE_DELETE,

	DIALOG_BENGKEL_PANEL,
	DIALOG_BENGKEL_LOCKER,
	DIALOG_BENGKEL_CLOTHES,
	DIALOG_BENGKEL_GARAGE,
	DIALOG_MODIF_COLOROPTION,
	DIALOG_MODIF_WARNA1,
	DIALOG_MODIF_WARNA2,
	DIALOG_MODIF_PAINTJOB,
	DIALOG_BENGKELBUYVEH,
	DIALOG_BENGKELTAKEVEH,
	DIALOG_BENGKEL_BRANKASOPTION,
	DIALOG_BENGKEL_BRANKASITEM,
	DIALOG_BENGKEL_BRANKASCONF,
	DIALOG_BENGKEL_BRANKASREPAIRKIT,
	DIALOG_BENGKEL_BRANKASTOOLSKIT,
	DIALOG_BENGKEL_BOSDESK,
	DIALOG_BENGKEL_INVITE,
	DIALOG_BENGKELSETRANK,
	DIALOG_BENGKELKICKMEMBER,
	DIALOG_RANK_SET_BENGKEL,
	DIALOG_BENGKELDELCAR,
	DIALOG_DEPOSIT_BENGKEL,
	DIALOG_WITHDRAW_BENGKEL,

	// WORKSHOP
	WORKSHOP_MENU,
	WORKSHOP_NAME,
	WORKSHOP_INFO,
	WORKSHOP_MONEY,
	WORKSHOP_WITHDRAWMONEY,
	WORKSHOP_DEPOSITMONEY,
	WORKSHOP_COMPONENT,
	WORKSHOP_WITHDRAWCOMPONENT,
	WORKSHOP_DEPOSITCOMPONENT,
	WORKSHOP_SERVICE,
	GPS_NEAREST_WORKSHOP,

	//MECH
	DIALOG_LOCKERMECH,
	DIALOG_SERVICE,
	DIALOG_SERVICE_COLOR,
	DIALOG_SERVICE_COLOR2,
	DIALOG_SERVICE_PAINTJOB,
	DIALOG_SERVICE_WHEELS,
	DIALOG_SERVICE_SPOILER,
	DIALOG_SERVICE_HOODS,
	DIALOG_SERVICE_VENTS,
	DIALOG_SERVICE_LIGHTS,
	DIALOG_SERVICE_EXHAUSTS,
	DIALOG_SERVICE_FRONT_BUMPERS,
	DIALOG_SERVICE_REAR_BUMPERS,
	DIALOG_SERVICE_ROOFS,
	DIALOG_SERVICE_SIDE_SKIRTS,
	DIALOG_SERVICE_BULLBARS,

	DIALOG_BENGVAULT,
	DIALOG_BENGVAULT_DEPOSIT,
	DIALOG_BENGVAULT_WITHDRAW,
	DIALOG_BENGVAULT_IN,
	DIALOG_BENGVAULT_OUT,

	DIALOG_BOSDESK_GOJEK,
	DIALOG_DEPOSIT_GOJEK,
	DIALOG_WITHDRAW_GOJEK,
	DIALOG_RANK_SET_GOJEK,
	DIALOG_GOJEK_INVITECONF,
	DIALOG_GOJEK_LOCKER,

	DIALOG_GOJEK_GARAGE,
	DIALOG_GOJEK_GARAGE_BUY,
	DIALOG_GOJEK_GARAGE_TAKEOUT,
	DIALOG_GOJEK_GARAGE_DELETE,

	DIALOG_GOJVAULT,
	DIALOG_GOJVAULT_DEPOSIT,
	DIALOG_GOJVAULT_WITHDRAW,		
	DIALOG_GOJVAULT_IN,	
	DIALOG_GOJVAULT_OUT,

	DIALOG_PAYGOJEK,
	DIALOG_PAYGOJEKAMOUNT,
	DIALOG_TOPUPGOJEK,
	DIALOG_PESANGORIDE,
	DIALOG_PESANGORIDECONF,
	DIALOG_PESANGOCAR,
	DIALOG_PESANGOCARPENUMPANG,
	DIALOG_PESANGOCARCONF,
	DIALOG_GOPAYWITHDRAW,
	
	DIALOG_GOFOOD_PESAN,
	DIALOG_PESAN_NASIGORENG,
	DIALOG_PESAN_BAKSO,
	DIALOG_PESAN_NASIPECEL,
	DIALOG_PESAN_BUBUR,
	DIALOG_PESAN_SUSU,
	DIALOG_PESAN_ESTEH,
	DIALOG_PESAN_KOPI,
	DIALOG_PESAN_CHOCOMATCH,
	DIALOG_PESAN_NOTES,
	
	DIALOG_ITEM_PICKUP,

	DIALOG_FAMSVAULT,
	DIALOG_FAMSVAULT_DEPOSIT,
	DIALOG_FAMSVAULT_WITHDRAW,
	DIALOG_FAMSRM_VAULT,
	DIALOG_FAMSRM_DEPOSIT,
	DIALOG_FAMSRM_WITHDRAW,
	DIALOG_FAMSVAULT_IN,
	DIALOG_FAMSVAULT_OUT,
	DIALOG_FAMSBRANKAS,
	DIALOG_FAMS_WEAPON,
	DIALOG_FAMILIESSETRANK,
	DIALOG_FAMILIESKICKMEMBER,
	DIALOG_RANK_SET_FAMILIES,

	DIALOG_VEHICLE_MENU,
	DIALOG_VHOLSTER,
	DIALOG_VHOLSTER_WITHDRAW,

	DIALOG_SPORTSTORE,

	//house pajak
	DIALOG_PAYTAX_HOUSE,
	DIALOG_PERPANJANG_HOUSE,

	/* Trans Dialog */
	DIALOG_TRANSORDER,
	DIALOG_TRANS_LOCKER,
	DIALOG_TRANS_DESK,
	DIALOG_TRANSSETRANK,
	DIALOG_TRANSKICKMEMBER,
	DIALOG_RANK_SET_TRANS,
	DIALOG_TRANS_INVITECONF,
	DIALOG_DEPOSIT_TRANS,
	DIALOG_WITHDRAW_TRANS,
	DIALOG_TRANS_GARAGE,
	DIALOG_TRANS_GARAGE_TAKEOUT,
	DIALOG_TRANS_GARAGE_BUY,
	DIALOG_TRANS_GARAGE_DELETE,

	DIALOG_TRANSVAULT,
	DIALOG_TRANSVAULT_DEPOSIT,
	DIALOG_TRANSVAULT_WITHDRAW,
	DIALOG_TRANSVAULT_IN,
	DIALOG_TRANSVAULT_OUT,

	// natal
	DIALOG_LIST_NATAL,

	/*Bagasi Dialog*/
	DIALOG_BAGASI,
	DIALOG_BAGASI_DEPOSIT,
	DIALOG_BAGASI_IN,
	DIALOG_BAGASI_WITHDRAW,
	DIALOG_BAGASI_OUT,

	/*Event Dialog*/
	DIALOG_EVENT_SETTING,
	DIALOG_EVENT_REDSKIN,
	DIALOG_EVENT_REDWEAP1,
	DIALOG_EVENT_REDWEAP2,
	DIALOG_EVENT_REDWEAP3,

	DIALOG_EVENT_BLUESKIN,
	DIALOG_EVENT_BLUEWEAP1,
	DIALOG_EVENT_BLUEWEAP2,
	DIALOG_EVENT_BLUEWEAP3,

	DIALOG_EVENT_WWID,
	DIALOG_EVENT_INTID,
	DIALOG_EVENT_TIME,
	DIALOG_EVENT_TARGETSCORE,
	DIALOG_EVENT_PARTICIPRIZE,
	DIALOG_EVENT_PRIZE,
	DIALOG_EVENT_HEALTH,
	DIALOG_EVENT_ARMOUR,

	/* Dialog Aridrop */
	DIALOG_AIRDROP,
	DIALOG_AIRDROPDISPLAY,
	DIALOG_AIRDROP_CONF,
	DIALOG_ADD_CONTACT,
	DIALOG_ADD_CONTACTNUMB,
	DIALOG_EDIT_CONTACTNAME,
	DIALOG_EDIT_CONTACTNUMBER,

	/* Dialog Garasi Umum */
	DIALOG_GARKOT_OUT,

	/* Dialog Gudang */
	DIALOG_GUDANG_BUY,
	DIALOG_GUDANG_OPTION,
	DIALOG_GUDANGVAULT,
	DIALOG_GUDANGVAULT_DEPOSIT,
	DIALOG_GUDANGVAULT_WITHDRAW,
	DIALOG_GUDANGVAULT_IN,
	DIALOG_GUDANGVAULT_OUT,

	//ROBBANK
	DIALOG_CDROBBANK,

	/* Workshop by Anaxy
	LOCKER_WORKSHOP,
	WORKSHOP_MENU,
	WORKSHOP_NAME,
	WORKSHOP_COMPONENT,
	WORKSHOP_COMPONENT2,
	WORKSHOP_INFO,
	WORKSHOP_MONEY,
	WORKSHOP_SETEMPLOYE,
	WORKSHOP_WITHDRAWMONEY,
	WORKSHOP_DEPOSITMONEY,
	WORKSHOP_SETEMPLOYEE,
	WS_SETOWNERCONFIRM,*/

	/* Score Board Admin Menu */
	DIALOG_CLICKPLAYER,
	DIALOG_BANNEDTIME,
	DIALOG_BANNEDREASON,

	/* Dialog Asuransi */
	DIALOG_ASURANSI_LS,
	DIALOG_ASURANSI_LV,

	/* Dialog Fact Garage */
	DIALOG_FACTION_GARAGE_MENU,
	DIALOG_FACTION_GARAGE1,
	DIALOG_FACTION_GARAGE2,
	DIALOG_FACTION_GARAGE3,
	DIALOG_FACTION_GARAGE4,
	DIALOG_FACTION_GARAGE5,
	DIALOG_FACTION_GARAGE6,

	/* Dialog warung */
	DIALOG_WARUNG,
	DIALOG_WARUNG_ELEKTRONIK, 
	DIALOG_BUY_NASIUDUK,
	DIALOG_BUY_AIRMINERAL, 
	DIALOG_BUY_UMPAN,

	/* Petani Dialog */
	DIALOG_BUY_SEEDS,
	DIALOG_BIBIT_PADI,
	DIALOG_BIBIT_TEBU,
	DIALOG_BIBIT_CABE,

	/* Dialog House Keys */
	DIALOG_HKEYS, 
	DIALOG_HKEYS_ADD,
	DIALOG_HKEYS_REMOVE,
	DIALOG_HOUSEGARAGE_OUT,
	DIALOG_HOUSEHELIPAD_OUT,
	DIALOG_HOUSE_BRANKAS,
	DIALOG_HOUSE_INVITE,
	DIALOG_HOUSE_INVITECONF,
	DIALOG_HOUSEVAULT,
	DIALOG_HOUSEVAULT_DEPOSIT,
	DIALOG_HOUSEVAULT_WITHDRAW,
	DIALOG_HOUSEVAULT_IN,
	DIALOG_HOUSEVAULT_OUT,
	DIALOG_WEAPON_CHEST,
	DIALOG_HOUSE_COOKING,

	DIALOG_FIXMEACC,
	DIALOG_ADMIN_HELP,
	DIALOG_DYNAMIC_HELP,

	DIALOG_SWEEPER_START,
	DIALOG_DELIVERY_START,
	DIALOG_FORKLIFT_START,
	DIALOG_RECYCLER_START,
	DIALOG_TRASHMASTER_START,

	/* Dialog Clothes */
	DIALOG_CLOTHES,
	DIALOG_CLOTHES_DELETE,

	/* Atms Dialog */
	DIALOG_ATM_WITHDRAW,
	DIALOG_ATM_DEPOSIT,
	DIALOG_ATM_TRANSFER,
	DIALOG_ATM_TRANSFER1,

	/* Kargo */
	DialogKargoRemake,

	/* Carsteal Dialog */
	DIALOG_CARSTEAL_SHOP,

	/*Whatsapp Dialog*/
	DIALOG_WHATSAPP_CHAT,
	DIALOG_WHATSAPP_CHAT_EMPTY,
	DIALOG_WHATSAPP_SEND,

	/*Yellow Pages*/
	DIALOG_YELLOW_PAGE,
	DIALOG_YELLOW_PAGE_MENU,
	DIALOG_YELLOW_PAGE_EMPTY,
	DIALOG_YELLOW_PAGE_SEND,
	DIALOG_YELLOW_CALL,

	/*Tweets Dialog*/
	DIALOG_TWITTER_SIGN,
	DIALOG_TWITTER_SIGNPASSWORD,
	DIALOG_TWITTER_LOGIN,
	DIALOG_TWITTER_LOGINPASSWORD,
	DIALOG_TWITTER_POST,
	DIALOG_TWITTER_POST_EMPTY,
	DIALOG_TWITTER_POST_SEND,

	/*Spotifyy Dialog*/
	DIALOG_SPOTIFY_SIGN,
	DIALOG_SPOTIFY_SIGNPASSWORD,
	DIALOG_SPOTIFY_LOGIN,
	DIALOG_SPOTIFY_LOGINPASSWORD,

	/*Invoice Dialog*/
	DIALOG_INVOICE_NAME,
    DIALOG_INVOICE_COST,
    DIALOG_PAY_INVOICE,

	/*Player dialog*/
	DIALOG_PLAYER_MENU,
	DIALOG_PLAYER_DOKUMENT,

	/*Job Mixer Dialog*/
	DIALOG_MIXER,

	DIALOG_SELECT_SPAWN,
	DIALOG_SELECT_SPAWNEXPIRED,

	DIALOG_SHOWROOM_MENU,
	DIALOG_SHOWROOM_SELL,

	DIALOG_WEAPONSHOP,
	DIALOG_VIP_NAME,
	DIALOG_SELLFISH_ILEGAL,
	DIALOG_DISPLAYBANNED,
	DIALOG_RADIO_FREQ,
	DIALOG_VOICEMODE,
	DIALOG_VOICEKEYS,
	DIALOG_INVENTORY,
	DIALOG_CHANGE_PASSWORD,
	DIALOG_MYV_MENU,
	DIALOG_VEHICLE_DETAIL,
	DIALOG_VALET_CONFIRM,
	DIALOG_UPGRADE,
	DIALOG_UPGRADEBAGASI,
	DIALOG_MODSHOP,
	DIALOG_UBAHHARGA_LOW,
	DIALOG_UBAHHARGA_MEDIUM,
	DIALOG_UBAHHARGA_HIGH,
	DIALOG_UBAHHARGA_SPECIAL,
	DIALOG_MENUMAKAN,
	DIALOG_TARIKTAMBANG,
	DIALOG_TIMETAMBANG,
	//RACEDIALOGSYSTEM
	DIALOG_RACE_PLAYER_COUNT,
	DIALOG_RACE_LAP_COUNT,
	DIALOG_RACE_INVITE_PLAYER1,
	DIALOG_RACE_INVITE_PLAYER2,
	DIALOG_RACE_INVITE_PLAYER3,
	DIALOG_RACE_INVITE_PLAYER4,
	DIALOG_RACE_INVITE_PLAYER5,
	DIALOG_RACE_INVITE_PLAYER6,
	DIALOG_RACE_CONFIRM_INVITE,
	DIALOG_RACE_VEH_LIST,
	DIALOG_ADMIN_RACE_LAP_COUNT,
	DIALOG_ADMIN_RACE_VEHICLE,
	
	DIALOG_BERANKAS_CODE,

	//gastation
	DIALOG_MY_GS,
	DIALOG_SELL_GS,
	GS_MENU,
	GS_INFO,
	GS_PRICESET,
	GS_NAME,
	GS_VAULT,
	GS_WITHDRAW,
	GS_DEPOSIT,
	GPS_NEAREST_GSTATION,
}

new AksesorisHat[87] =
{
	18953, 18954, 19554, 18960, 18974, 19067, 19068, 19069, 18891, 18892, 18893, 18894, 18895, 18896, 18897, 18898, 18899, 18900, 18908,
	18940, 18939, 18941, 18942, 18943, 19160, 18636, 18926, 18927, 18928, 18929, 18930, 18931, 18932, 18933, 18934, 18935, 18952, 18976, 18977, 
	18979, 19077, 19517, 19161, 19162, 2054, 18961, 18964, 18965, 18966, 19558, 18955, 18956, 18957, 18958, 18959, 18638, 19520, 18947, 18948, 
	19064,19065, 19066, 18975, 19516, 18639, 18645, 18962, 19095, 19096, 19099, 19100, 19487, 19136, 19330, 19331, 19137, 19528, 19093,
	3002, 3000, 3100, 3105, 3104, 3101, 3102, 3103, 3002,
};

new BackpackToys[7] = 
{
	11745, 19559, 1550, 3026, 371, 1210, 11738,
};

new GlassesToys[33] = 
{
	19138, 19139, 19140, 19006, 19007, 19008, 19009, 19010, 19011, 19012, 19013, 19014, 19015, 19016, 19017, 19018,
	19019, 19020, 19021, 19022, 19023, 19024, 19025, 19026, 19027, 19028, 19029, 19030, 19031, 19032, 19033, 19034, 19035,
};

new AksesorisToys[38] = 
{
	19515, 19142, 19621, 19623, 
	19584, 19591, 19592, 2226, 19878, 
	19038, 19036, 19163, 18919, 18912, 
	18913, 18914, 18915, 18916, 18917, 
	18918, 18911, 18920, 11704, 19037, 
	19317, 19318, 336, 339, 325, 19625,
	19801, 19163, 19904, 2226, 2487, 2614,
	11712, 18635,
};

new AksesorisPvt[13] =
{
	1608, 18691, 18690, 18963,
	1736, 1588, 1254, 1248, 1600, 2411,
	19584, 18713, 18687
};

new ClothesSkinMale[49] = 
{
	1,2,5,7,14,15,17,18,19,21,22,23,24,25,26,28,
    29,30,45,47,48,51,52,59,60,78,79,80,81,83,98,99,100,120,122,123,144,170,180,200,240,242,230,291,292,293,294,299,250
};

new ClothesSkinFemale[23] = 
{
	9,10,11,12,13,48,39,40,41,55,56,85,89,91,93,169,190,193,216,224,226,263,304
};

stock const Float: SpawnPelabuhan[][] = {
	{2744.2397,-2449.5349,13.6950,271.9706},
	{2744.3171,-2457.2017,13.6950,268.3150},
	{2738.2039,-2454.5254,13.6950,269.7540}
};

stock const Float: SpawnBandara[][] = {
	{1694.7468, -2332.3428, 13.5469, 0.0377},
	{1698.4928, -2329.6863, 13.5469, 49.2119}
};

stock const Float: SpawnVenturas[][] = {
	{1677.6498, 1447.7649, 10.7757, 271.1616},
	{1674.8794, 1444.2119, 10.7890, 270.9187}
};

#include "SERVER/utils/utils_defines"
#include "SERVER/utils/utils_vehiclevars"
#include "SERVER/utils/utils_enums"
#include "SERVER/utils/utils_variable"
#include "SERVER/utils/utils_colours"
#include "SERVER/utils/utils_textdraws"
#include "SERVER/voucher/voucher_functions"

#include "SERVER/systems/Pickup"
#include "SERVER/systems/JobVehicles"


/*Clothes System*/
#include "SERVER/toys/toys"
#include "SERVER/toys/toys_helmet"
#include "SERVER/clothes/clothes_functions"

#include "SERVER/fuel_system/fuel_functions"
#include "SERVER/PlayerStuff/player_slot"
#include "SERVER/Gym/gym_functions"

#include "SERVER/Dynamic/Dynamic_SpeedCam/core"
#include "SERVER/Dynamic/Dynamic_SpeedCam/funcs"
#include "SERVER/Dynamic/Dynamic_SpeedCam/cmd"
#include "SERVER/Dynamic/Dynamic_Button/button_functions"
#include "SERVER/Dynamic/Dynamic_Actor/ui_dynactor"
#include "SERVER/Dynamic/Dynamic_Warung/warung_functions"
#include "SERVER/Dynamic/Dynamic_Pasar/dyn_pasar"
#include "SERVER/Dynamic/Dynamic_Robbery/robbery_functions"
#include "SERVER/area/area"
#include "SERVER/Dynamic/Dynamic_Hunting/hunting_functions"
#include "SERVER/Dynamic/Dynamic_Ladang/ui_dynkanabis"
#include "SERVER/Dynamic/Dynamic_Ladang/kanabis_olah"
#include "SERVER/Dynamic/Dynamic_Object/object_funcs"
#include "SERVER/Dynamic/Dynamic_Pohonnatal/pohonnatal"


#include "SERVER/Dynamic/Dynamic_GarasiKota/Header"
#include "SERVER/Dynamic/Dynamic_GarasiKota/Function"
#include "SERVER/Dynamic/Dynamic_GarasiKota/Commands"

#include "SERVER/Dynamic/workshop/cmd.inc"
#include "SERVER/Dynamic/workshop/function.inc"
#include "SERVER/Dynamic/workshop/header.inc"
#include "SERVER/Dynamic/workshop/native.inc"
#include "SERVER/Dynamic/workshop/mech.inc"


#include "SERVER/Dynamic/Dynamic_Atm/ui_atm"
#include "SERVER/Dynamic/Dynamic_Garbage/dynamic_garbage"
#include "SERVER/Dynamic/Dynamic_Door/dynamic_doors"
#include "SERVER/Dynamic/Dynamic_Gate/dynamic_gatev2"
#include "SERVER/Dynamic/Dynamic_Gudang/gudang_functions"
#include "SERVER/Dynamic/Dynamic_Label/label_functions"

// Map Icon
#include "SERVER/Dynamic/Dynamic_IconMap/Header"
#include "SERVER/Dynamic/Dynamic_IconMap/Function"
#include "SERVER/Dynamic/Dynamic_IconMap/Commands"

#include "SERVER/Dynamic/Dynamic_Machine/dynamic_slot"
#include "SERVER/Dynamic/Dynamic_ObjectText/objecttext"
#include "SERVER/Dynamic/Dynamic_Uranium/uranium_funcs"
#include "SERVER/Dynamic/Dynamic_FactionStuffs/dynamic_factiongarage.inc"

#include "SERVER/jobs/farmer/petani_functions"

#include "SERVER/inventory/inventory_functions"
#include "SERVER/inventory/inventory_cmds"
#include "SERVER/inventory/inventory_drop"

#include "SERVER/voice/radiosystem"

// ------------------------------------------
#include "SERVER/user-interface/ui_animations"
//#include "SERVER/user-interface/notifikasi/Header"
//#include "SERVER/user-interface/notifikasi/Function"
#include "SERVER/user-interface/notifikasi/box_func"
#include "SERVER/user-interface/notifikasi/notify_functions"
#include "SERVER/user-interface/ui_shortkeys"
#include "SERVER/user-interface/ui_smoking"
#include "SERVER/user-interface/ui_loadingbar.inc"
#include "SERVER/user-interface/ui_radialmenu.inc"
#include "SERVER/user-interface/ui_minigamefish.inc"

#include "SERVER/Dynamic/Dynamic_Rusun/rusun_functions"
#include "SERVER/Dynamic/Dynamic_House/dyn_house"

#include "SERVER/PlayerStuff/PlayerAFK"
#include "SERVER/PlayerStuff/IdleAnimation"
#include "SERVER/PlayerStuff/NameTag"
#include "SERVER/PlayerStuff/player_login"

/*PhoneSystem*/
#include "SERVER/FractionPlayer/FAMILIES/families_functions"
// #include "SERVER/FractionPlayer/FAMILIES/families_garage.inc"

#include "SERVER/jobs/miner/minerv2_functions"
#include "SERVER/jobs/lumberjack/lumber_functions"
#include "SERVER/jobs/bus/HeaderBus"
#include "SERVER/jobs/bus/bus_funcs"
#include "SERVER/jobs/chicken factory/butcher_functions"
#include "SERVER/jobs/milker/milker_functions"
#include "SERVER/jobs/oilman/oilman_function"
#include "SERVER/jobs/fisherman/nelayan_funcs"
#include "SERVER/jobs/delivery/deliveryside_functions"
#include "SERVER/jobs/mowingjob/mowerside_functions"
#include "SERVER/jobs/sweeper/sweeper_functions"
#include "SERVER/jobs/forklift/forkliftside_functions"
#include "SERVER/jobs/tailor/tailorv2_functions"
#include "SERVER/jobs/tailor/tailor_forward"
#include "SERVER/jobs/hauling/kargo_func"
#include "SERVER/jobs/RicycleJob/recycler_functions"
#include "SERVER/jobs/trashmaster/trashmaster_functions"
#include "SERVER/jobs/electrican/electric_funcs"
#include "SERVER/jobs/mixer/callback"

#include "SERVER/Dynamic/Dynamic_Garbage/rongsokan_functions"
#include "SERVER/PlayerSmartphone/smartphone_contacts"
#include "SERVER/PlayerSmartphone/phone_funcs"

#include "SERVER/vehiclemod/modshop"
#include "SERVER/vehicles/vehicles_functions"
#include "SERVER/vehicles/vehicles_cmds"
#include "SERVER/vehicles/vehicles_faction"

#include "SERVER/weapons/weapons_functions"

#include "SERVER/Dynamic/Dynamic_Rental/dyn_rental"

#include "SERVER/FractionPlayer/stuff_goodside"

#include "SERVER/toko-olahraga/business_olahraga"

/* Factions */
#include "SERVER/FractionPlayer/FactionMenu"
#include "SERVER/FractionPlayer/Pemerintah/pemerintah_functions"
#include "SERVER/FractionPlayer/Bengkel/bengkel_brankas"
#include "SERVER/FractionPlayer/Bengkel/bengkel_functions"
//#include "SERVER/Dynamic/Dynamic_Workshop/Workshop_Functions"
#include "SERVER/FractionPlayer/Pedagang/lounges_brankas"
#include "SERVER/FractionPlayer/Pedagang/lounges_vars"
#include "SERVER/FractionPlayer/Pedagang/lounges_functions"
#include "SERVER/FractionPlayer/EMS/ems_brankas"
#include "SERVER/FractionPlayer/EMS/ems"
// #include "SERVER/FractionPlayer/EMS/medic_funcs"
#include "SERVER/FractionPlayer/Police/sapd_functions"
#include "SERVER/FractionPlayer/Police/lockerkepolisian"
// #include "SERVER/FractionPlayer/Police/sapd_taser"
// #include "SERVER/FractionPlayer/Police/sapd_spike"
#include "SERVER/FractionPlayer/trans/trans_functions"
#include "SERVER/FractionPlayer/trans/trans_stuffs"
// #include "SERVER/FractionPlayer/Gojek/cmds_gojek"
// #include "SERVER/FractionPlayer/Gojek/gojek_functions"

#include "SERVER/reports/systems_ask"
#include "SERVER/reports/systems_reports"


#include "SERVER/events/admin_events.inc"
#include "SERVER/events/tariktambang.inc"
#include "SERVER/events/raceChess7.inc"
#include "SERVER/Race/race"
#include "commands/cmds_hooks"
#include "SERVER/systems/systems_dialogs"
#include "SERVER/systems/systems_spawn.inc"
#include "SERVER/systems/systems_functions"
#include "SERVER/systems/systems_native"
#include "SERVER/systems/systems_salju"
#include "SERVER/systems/BarQTE"
#include "SERVER/systems/SystemDrone"
#include "SERVER/systems/RobbankSystems"
#include "SERVER/systems/systems_publicworks"
// #include "SERVER/systems/systems_bombomcar.inc"
#include "SERVER/systems/systems_toysprem.inc"
// #include "SERVER/systems/systems_anticheat.inc"
#include "SERVER/anticheatexeren/antipackexeren"
#include "SERVER/systems/MinigamePanelHacking"
// #include "SERVER/systems/antiremcs_dan.inc"

#include "SERVER/toll/toll_functions"

// #include "SERVER/PlayerSpawn/spawn_functions.inc" Dimatikan sementara
#include "SERVER/jobs/Disnaker/disnaker_functions"

// #include "commands\boxing_funcs.inc"
#include "commands\management"
#include "commands\pengurus"
#include "commands\cmds_faction"
#include "commands\cmds_player"
#include "commands\cmds_admin"
#include "commands\earthquake"
#include "commands\NoClip"

#include "SERVER/carsteal/carsteal_functions"
#include "SERVER/PlayerStuff/player_toystd"
// #include "SERVER/mapping/mapping_server.inc"

#include "SERVER/mapping/mapping_in"

// #include "SERVER/events/xmas.inc"
//#include "SERVER/events/events.inc"

#include "SERVER/showroom/showroom_functions"
#include "SERVER/PlayerStuff/player_actions"
#include "SERVER/PlayerStuff/player_asuransi"
#include "SERVER/PlayerStuff/player_fishingactivity"
#include "SERVER/damages/damagelog_functions"
#include "SERVER/PlayerStuff/ElistUI"
#include "SERVER/PlayerStuff/FpsDisplay"
#include "SERVER/PlayerStuff/JawelRobb"
#include "SERVER/PlayerStuff/ApiUnggun"
#include "SERVER/PlayerStuff/MiniGameKotak"
//#include "SERVER/PlayerStuff/VehicleParachute"

#include "SERVER/tags/core"
#include "SERVER/tags/cmd"
#include "SERVER/tags/funcs"
#include "SERVER/tags/impl"

//#include "commands\DISCORD"

#include "SERVER/PlayerCrafting/crafting_functions.inc"
// ----------------------------------------
#include "SERVER/streamer/streamer"
#include "SERVER/invoices/invoices"
#include "SERVER/blacklist/blacklist_functions"
#include "SERVER/timers/timer_task"
// #include "SERVER/timers/timer_ptask_anticheat.inc"
#include "SERVER/timers/timer_ptask_jail"
#include "SERVER/timers/timer_ptask_update"
#include "SERVER/playermarker/playermark"
#include "SERVER/anticheatexeren/antidupe.pwn"
//#include "SERVER/anticheatexeren/antibeton.pwn"

forward OnGameModeInitEx();
forward OnGameModeExitEx();


main() 
{

}

stock DatabaseConnection()
{
	g_SQL = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE);
	if (g_SQL == MYSQL_INVALID_HANDLE || mysql_errno(g_SQL) != 0)
	{
		print("District : Connection To MYSQL Failed! Server Shutting Down!");
		SendRconCommand("exit");
	}
	else
	{
		print("District : Database successfully connected to MySQL.");
	}
	return 1;
}

public OnGameModeInit()
{
	SetTimer("PesanOtomatisNabil", 1800000, true);

	#if defined MAKE_PELER
	Profiler_Start();
	#endif
	DatabaseConnection();
	ShowNameTags(false);
	EnableTirePopping(0);
	CreateTextDraw();
	// StreamerConfig();
	// LoadMap();
	LoadWarungArea();
	LoadArea();
	LoadGangZone();
	LoadServerPickup();	
	ManualVehicleEngineAndLights();
	EnableStuntBonusForAll(0);
	AllowInteriorWeapons(1);
	DisableInteriorEnterExits();
	LimitPlayerMarkerRadius(15.0);
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);

	SetGameModeText(sprintf("%s", TEXT_GAMEMODE));
	SendRconCommand(sprintf("weburl %s", TEXT_WEBURL));
	SendRconCommand(sprintf("language %s", TEXT_LANGUAGE));
	SendRconCommand("mapname San Andreas");
	BlockGarages(.text="Tutup");

	/* Load From Database */
	mysql_tquery(g_SQL, "SELECT * FROM `brankas_ems`", "LoadBrankasEms");
	mysql_tquery(g_SQL, "SELECT * FROM `brankas_bengkel`", "LoadBrankasBengkel");
	mysql_tquery(g_SQL, "SELECT * FROM `brankas_lounges`", "LoadBrankasLounges");
	mysql_tquery(g_SQL, "SELECT * FROM `buttons`", "LoadButtons");
	mysql_tquery(g_SQL, "SELECT * FROM `doors`", "LoadDoors");
	mysql_tquery(g_SQL, "SELECT * FROM `families`", "Families_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `house`", "LoadRumah");
	mysql_tquery(g_SQL, "SELECT * FROM `gate`", "LoadGate");
	mysql_tquery(g_SQL, "SELECT * FROM `actors`", "Actor_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `bike_rentals`", "Rental_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `public_garage`", "LoadPublicGarage");
	mysql_tquery(g_SQL, "SELECT * FROM `gudang`", "LoadGudang");
	mysql_tquery(g_SQL, "SELECT * FROM `warung`", "LoadWarung");
	mysql_tquery(g_SQL, "SELECT * FROM `workshop`", "LoadWorkshop");
	mysql_tquery(g_SQL, "SELECT * FROM `pasar`", "LoadPasar");
	mysql_tquery(g_SQL, "SELECT * FROM `robbery`", "LoadDynamicRobbery");
	mysql_tquery(g_SQL, "SELECT * FROM `atms`", "LoadATM");
	mysql_tquery(g_SQL, "SELECT * FROM `trash`", "LoadTrash");
	mysql_tquery(g_SQL, "SELECT * FROM `stuffs`", "LoadBrankasGoodside");
	mysql_tquery(g_SQL, "SELECT * FROM `ladang`", "LoadKanabis");
	mysql_tquery(g_SQL, "SELECT * FROM `icons`", "Icons_Load", "");
	mysql_tquery(g_SQL, "SELECT * FROM `label_fivem`", "LoadLabel");
	mysql_tquery(g_SQL, "SELECT * FROM `dynamic_rusun`", "Rusun_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `hunting`", "LoadDeer");
	mysql_tquery(g_SQL, "SELECT * FROM `weeds`", "Weed_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `voucher`", "LoadVoucher");
	mysql_tquery(g_SQL, "SELECT * FROM `objects`", "LoadDynamicObject");
	mysql_tquery(g_SQL, "SELECT * FROM `slotmachine`", "LoadSlotMachine");
	mysql_tquery(g_SQL, "SELECT * FROM `objecttext`", "ObjectText_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `uranium`", "Load_Uranium");
	mysql_tquery(g_SQL, "SELECT * FROM `gstations`", "LoadGStations");
	mysql_tquery(g_SQL, "SELECT * FROM `factiongarage`", "LoadFactionGarage");
	mysql_tquery(g_SQL, "SELECT * FROM `police_locker`", "Locker_Load");
	mysql_tquery(g_SQL, "SELECT * FROM `tags` ORDER BY `tagId` ASC LIMIT "#MAX_DYNAMIC_TAGS";", "Tags_Load");

	for (new i; i < sizeof(ColorList); i++) {
        format(color_string, sizeof(color_string), "%s{%06x}%03d %s", color_string, ColorList[i] >>> 8, i, ((i+1) % 16 == 0) ? ("\n") : (""));
    }

    for (new i; i < sizeof(FontNames); i++) {
        format(object_font, sizeof(object_font), "%s%s\n", object_font, FontNames[i]);
    }
	
	for(new i = 0; i < sizeof(BarrierInfo);i ++)
	{
		new
		Float:X = BarrierInfo[i][brPos_X],
		Float:Y = BarrierInfo[i][brPos_Y];

		ShiftCords(0, X, Y, BarrierInfo[i][brPos_A]+90.0, 3.5);
		CreateDynamicObject(966,BarrierInfo[i][brPos_X],BarrierInfo[i][brPos_Y],BarrierInfo[i][brPos_Z],0.00000000,0.00000000,BarrierInfo[i][brPos_A]);
		if(!BarrierInfo[i][brOpen])
		{
			gBarrier[i] = CreateDynamicObject(968,BarrierInfo[i][brPos_X],BarrierInfo[i][brPos_Y],BarrierInfo[i][brPos_Z]+0.8,0.00000000,90.00000000,BarrierInfo[i][brPos_A]+180);
			MoveObject(gBarrier[i],BarrierInfo[i][brPos_X],BarrierInfo[i][brPos_Y],BarrierInfo[i][brPos_Z]+0.7,BARRIER_SPEED,0.0,0.0,BarrierInfo[i][brPos_A]+180);
			MoveObject(gBarrier[i],BarrierInfo[i][brPos_X],BarrierInfo[i][brPos_Y],BarrierInfo[i][brPos_Z]+0.75,BARRIER_SPEED,0.0,90.0,BarrierInfo[i][brPos_A]+180);
		}
		else gBarrier[i] = CreateDynamicObject(968,BarrierInfo[i][brPos_X],BarrierInfo[i][brPos_Y],BarrierInfo[i][brPos_Z]+0.8,0.00000000,20.00000000,BarrierInfo[i][brPos_A]+180);
	}

	/* Mprice Stuffs*/
	OldTembagaPrice = TembagaPrice;
	OldBesiPrice = BesiPrice;
	OldEmasPrice = EmasPrice;
	OldBerlianPrice = BerlianPrice;
	OldMaterialPrice = MaterialPrice;
	OldAlumuniumPrice = AlumuniumPrice;
	OldKaretPrice = KaretPrice;
	OldKacaPrice = KacaPrice;
	OldBajaPrice = BajaPrice;
	OldAyamKemasPrice = AyamKemasPrice;
	OldSusuOlahPrice = SusuOlahPrice;
	OldPakaianPrice = PakaianPrice;
	OldKayuKemasPrice = KayuKemasPrice;
	OldGasPrice = GasPrice;
	
	SetTimer("WeatherRotator", 1800000, true);
	SetTimer("UpdateJamOoc", 1000, true);
	CallLocalFunction("OnGameModeInitEx", "");

	OpenVote = 0;
    VoteYes = 0;
    VoteNo = 0;
    VoteTime = 0;
    VoteText[0] = EOS;
	return 1;
} 

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	#if defined DEBUG_MODE
	    printf("[debug] OnPlayerInteriorChange(PID : %d New-Int : %d Old-Int : %d)", playerid, newinteriorid, oldinteriorid);
	#endif

	CancelEdit(playerid);

	foreach(new i : Player) if (AccountData[i][pSpec] != INVALID_PLAYER_ID && AccountData[i][pSpec] == playerid)
	{
		SetPlayerInterior(i, GetPlayerInterior(playerid));
		SetPlayerVirtualWorld(i, GetPlayerVirtualWorld(playerid));
	}

	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
    if (!AccountData[playerid][IsLoggedIn])
    {
		GameTextForPlayer(playerid, "~r~Stay in your world bastard!", 2000, 4);
		SendClientMessageEx(playerid, X11_RED, "[AntiCheat]:"LIGHTGREY" Anda ditendang karena diduga Fake Spawn!");
        KickEx(playerid);
    }
    return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	if(SQL_IsCharacterLogged(playerid) && AccountData[playerid][pAdmin] > 0)
	{
		if(!IsPlayerConnected(clickedplayerid)) return 0;
		if(clickedplayerid == playerid) return 0;

		new title[127];
		format(title, sizeof(title), ""TCRP"District  "WHITE"- %s(%d)", ReturnName(clickedplayerid), clickedplayerid);
		ShowPlayerDialog(playerid, DIALOG_CLICKPLAYER, DIALOG_STYLE_LIST, title, 
		""TCRP"Menu Admin\n\
		\nSpectator Pemain\
		\n"GRAY"Tarik Pemain\
		\nTeleport Ke Pemain\
		\n"GRAY"Banned Pemain\
		\nKick Pemain\
		\n"GRAY"Stats Pemain", "Pilih", "Batal");
		ClickPlayerID[playerid] = clickedplayerid;
	}
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetCameraData(playerid);

	if(!AccountData[playerid][IsLoggedIn])
	{		
		new query[268];
		mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `playerucp` WHERE `ucp` = '%s' LIMIT 1", AccountData[playerid][pUCP]);
		mysql_pquery(g_SQL, query, "CheckPlayerUCP", "id", playerid, g_RaceCheck[playerid]);
		SetPlayerColor(playerid, X11_GRAY);
	}
	return 1;
}

public OnGameModeExit()
{
	CreateRoadHole(1760.0, -1890.0, 13.5);
    CreateRoadHole(1955.0, -1750.0, 13.5);
	
	#if defined DEBUG_MODE
	    printf("[debug] OnGameModeExit()");
	#endif

    SaveAll();
	
	foreach(new playerid : Player)
		TerminateConnection(playerid);

	CallLocalFunction("OnGameModeExitEx", "");
	mysql_close(g_SQL);
	#if defined MAKE_PELER
	Profiler_Dump();
	Profiler_Stop();
	#endif
	return 1;
}

forward OnPlayerCarJacking(playerid);
public OnPlayerCarJacking(playerid)
{
	new Float:playerPos[3];
	GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
	AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
	
	SetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2] + 9.0);
	TogglePlayerControllable(playerid, false);
	GameTextForPlayer(playerid, "No Jacking!", 5500, 4);
	SetPlayerVirtualWorld(playerid, (playerid+1));
	SetTimerEx("OnPlayerCarJackingUpdate", 5500, false, "d", playerid);
	return 1;	
}

forward OnPlayerCarJackingUpdate(playerid);
public OnPlayerCarJackingUpdate(playerid)
{
	TogglePlayerControllable(playerid, true);
	SetPlayerVirtualWorld(playerid, AccountData[playerid][pWorld]);
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(!ispassenger)
	{
		new driverid = GetVehicleDriver(vehicleid);
		if(driverid != INVALID_PLAYER_ID && IsPlayerInVehicle(driverid, vehicleid) && !IsVehicleEmpty(vehicleid) && IsPlayerChangeSeat[playerid] == false)
		{
			SetTimerEx("OnPlayerCarJacking", 250, false, "d", playerid);
		}
		new vehicle_near = GetNearestVehicle(playerid);
		if((vehicle_near = Vehicle_ReturnID(vehicleid)) != RETURN_INVALID_VEHICLE_ID)
		{
			if(PlayerVehicle[vehicle_near][pVehFaction] == FACTION_POLISI)
			{
				if(AccountData[playerid][pFaction] != FACTION_POLISI && AccountData[playerid][pFaction] != FACTION_BENGKEL)
				{
					RemovePlayerFromVehicle(playerid);
					new Float:slx, Float:sly, Float:slz;
					GetPlayerPos(playerid, slx, sly, slz);
					SetPlayerPos(playerid, slx, sly, slz);
					ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini milik faction Polisi!");
				}
			}
			else if(PlayerVehicle[vehicle_near][pVehFaction] == FACTION_PEMERINTAH)
			{
				if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH && AccountData[playerid][pFaction] != FACTION_BENGKEL)
				{
					RemovePlayerFromVehicle(playerid);
					new Float:slx, Float:sly, Float:slz;
					GetPlayerPos(playerid, slx, sly, slz);
					SetPlayerPos(playerid, slx, sly, slz);
					ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini milik faction Pemerintah!");
				}
			}
			else if(PlayerVehicle[vehicle_near][pVehFaction] == FACTION_EMS)
			{
				if(AccountData[playerid][pFaction] != FACTION_EMS && AccountData[playerid][pFaction] != FACTION_BENGKEL)
				{
					RemovePlayerFromVehicle(playerid);
					new Float:slx, Float:sly, Float:slz;
					GetPlayerPos(playerid, slx, sly, slz);
					SetPlayerPos(playerid, slx, sly, slz);
					ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini milik faction EMS!");
				}
			}
			else if(PlayerVehicle[vehicle_near][pVehFaction] == FACTION_TRANS)
			{
				if(AccountData[playerid][pFaction] != FACTION_TRANS && AccountData[playerid][pFaction] != FACTION_BENGKEL && AccountData[playerid][pFaction] != FACTION_POLISI)
				{
					RemovePlayerFromVehicle(playerid);
					new Float:slx, Float:sly, Float:slz;
					GetPlayerPos(playerid, slx, sly, slz);
					SetPlayerPos(playerid, slx, sly, slz);
					ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini milik faction Transportasi!");
				}
			}
			else if(PlayerVehicle[vehicle_near][pVehFaction] == FACTION_BENGKEL)
			{
				if(AccountData[playerid][pFaction] != FACTION_POLISI && AccountData[playerid][pFaction] != FACTION_BENGKEL)
				{
					RemovePlayerFromVehicle(playerid);
					new Float:slx, Float:sly, Float:slz;
					GetPlayerPos(playerid, slx, sly, slz);
					SetPlayerPos(playerid, slx, sly, slz);
					ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini milik faction Bengkel!");
				}
			}
			else if(PlayerVehicle[vehicle_near][pVehFaction] == FACTION_PEDAGANG)
			{
				if(AccountData[playerid][pFaction] != FACTION_PEDAGANG && AccountData[playerid][pFaction] != FACTION_BENGKEL)
				{
					RemovePlayerFromVehicle(playerid);
					new Float:slx, Float:sly, Float:slz;
					GetPlayerPos(playerid, slx, sly, slz);
					SetPlayerPos(playerid, slx, sly, slz);
					ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini milik faction Pedagang!");
				}
			}
		}
	}
	return 1;
}

forward TrackSuspect(suspectid, policeid);
public TrackSuspect(suspectid, policeid)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(suspectid, x, y, z);

	DisablePlayerRaceCheckpoint(policeid);
	SetPlayerRaceCheckpoint(policeid, 1, x, y, z, 0.0, 0.0, 0.0, 5.0);
	Info(policeid, "Tracking Suspect Updated!");
	pMapCP[policeid] = true;
	if(IsPlayerInAnyVehicle(policeid) && GetPlayerState(policeid) != PLAYER_STATE_DRIVER)
    {
		DisablePlayerRaceCheckpoint(policeid);
        SetPlayerRaceCheckpoint(policeid, 1, x, y, z, 0.0, 0.0, 0.0, 5.0);
		Info(policeid, "Tracking Suspect Updated!");
		pMapCP[policeid] = true;
    }
	return 1;
}

public OnPlayerText(playerid, text[])
{
	if(!AccountData[playerid][IsLoggedIn] || !AccountData[playerid][pSpawned])
		return 0;

	if(AccountData[playerid][pAdmin] > 0 && AccountData[playerid][pAdminDuty])
	{
		if(strlen(text) > 64)
		{
			SendNearbyMessage(playerid, 15.0, -1, "Admin "RED"%s"WHITE": (( %.64s...", AccountData[playerid][pAdminname], text);
			SendNearbyMessage(playerid, 15.0, -1, "...%s ))", text[64]);
		}
		else 
		{
			SendNearbyMessage(playerid, 15.0, -1, "Admin "RED"%s"WHITE": (( %s ))", AccountData[playerid][pAdminname], text);
		}
	}
	return 0;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
	if (result != -1 && !AccountData[playerid][IsLoggedIn])
	{
		SendClientMessage(playerid, -1, ""RED"[AntiCheat]"ARWIN1" Anda ditendang dari server karena menggunakan CMD dalam keadaan tidak login!");
		return KickEx(playerid);
	}
	
    if (result == -1)
    {
		if(AccountData[playerid][pStyleNotif] == 1) //TD
		{
			ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Perintah ~y~'/%s'~w~ tidak diketahui, ~y~'/help'~w~ untuk info lanjut!", cmd));
		}
		else
		{
			ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Perintah "YELLOW"'/%s'"WHITE" tidak diketahui, "YELLOW"'/help'"WHITE" untuk info lanjut!", cmd));
		}
		return 0;
    }
	return 1;
}
forward PlayWelcomeAudio(playerid);
public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
	return 1;
}

public PlayWelcomeAudio(playerid)
{
    if(IsPlayerConnected(playerid))
    {
        PlayAudioStreamForPlayer(playerid, "http://h.top4top.io/m_3633ukhvu0.mp3");
    }
    return 1;
}

public OnPlayerConnect(playerid)
{
	//logoserver
	TextDrawShowForPlayer(playerid, TdLogoDistrict[0]);
	TextDrawShowForPlayer(playerid, TdLogoDistrict[1]);
	//TextDrawShowForPlayer(playerid, TdLogoDistrict[2]);
	
	g_RaceCheck[playerid] ++;
	OnlinePlayers++;
	ResetVariables(playerid);
	ReturnIP(playerid);
	CreatePlayerTextDraws(playerid);
	OnLoadMixerProperty(playerid);
	Player_ToggleTelportAntiCheat(playerid, false);
	Player_ToggleAntiHealthHack(playerid, false);
	Player_ToggleDisableAntiCheat(playerid, false);
	EnableAntiCheatForPlayer(playerid, 11, true);
	EnableAntiCheatForPlayer(playerid, 19, true);
	EnableAntiCheatForPlayer(playerid, 4, true);
	PlayerSpawn[playerid] = 0;
	SetTimerEx("PlayWelcomeAudio", 3000, false, "i", playerid);

	if(g_RestartServer)
	{
		for(new i = 0; i < 17; i++)
		{
		   	TextDrawShowForPlayer(playerid, TdBadaiHapp[i]);
		}
	}
	if(g_RestartServer)
	{
		for(new i = 0; i < 16; i++)
		{
		   	TextDrawShowForPlayer(playerid, InsuKelHapp[i]);
		}
	}

	GetPlayerName(playerid, AccountData[playerid][pUCP], MAX_PLAYER_NAME + 1);

    if(AccountData[playerid][pHead] < 0) return AccountData[playerid][pHead] = 20;
    if(AccountData[playerid][pPerut] < 0) return AccountData[playerid][pPerut] = 20;
    if(AccountData[playerid][pRFoot] < 0) return AccountData[playerid][pRFoot] = 20;
    if(AccountData[playerid][pLFoot] < 0) return AccountData[playerid][pLFoot] = 20;
    if(AccountData[playerid][pLHand] < 0) return AccountData[playerid][pLHand] = 20;
    if(AccountData[playerid][pRHand] < 0) return AccountData[playerid][pRHand] = 20;
	
	PantaiArea[playerid] = CreateDynamicRectangle(345.3125, -2094.787811279297, 415.3125, -2007.7878112792969);
	PlayerUfo_Veh[playerid] = 0;
	PlayerUfo_Obj[playerid] = 0;
	gAdminRacePlayers[playerid] = INVALID_PLAYER_ID;
    gRacePlayerReady[playerid] = false;

    gRacePlayerData[playerid][rVehicleAdm] = INVALID_VEHICLE_ID;
    gRacePlayerData[playerid][rCheckpoint] = 0;
    gRacePlayerData[playerid][rLap] = 0;
    gRacePlayerData[playerid][rFinished] = false;
    CreateTDRacing(playerid);
	SetPVarInt( playerid, "DroneSpawned", 0 );
 	SetPVarFloat( playerid, "OldPosX", 0 );
	SetPVarFloat( playerid, "OldPosY", 0 );
	SetPVarFloat( playerid, "OldPosZ", 0 );

	//Jewelry Store
	isRobbing_Jewelry[playerid] = 0;
	isHaveJewelry[playerid] = 0;
	isCoordinat_ChangeJewelry[playerid] = 0;
	IsCoordinatBankGold[playerid] = 0;
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	//logoserver
	TextDrawHideForPlayer(playerid, TdLogoDistrict[0]);
	TextDrawHideForPlayer(playerid, TdLogoDistrict[1]);
	TextDrawHideForPlayer(playerid, TdLogoDistrict[2]);

    new Float:pX, Float:pY, Float:pZ, Float:pA;
    GetPlayerPos(playerid, pX, pY, pZ);
    GetPlayerFacingAngle(playerid, pA);

    if(IsPlayerInAnyVehicle(playerid))
    {
        RemovePlayerFromVehicle(playerid);
    }
    OnlinePlayers--;

    KillTimer(AccountData[playerid][DokterLokalTimer]);
    KillTimer(AccountData[playerid][RobJewelryTimer]);
    if(AccountData[playerid][RobbankCashTimer] != -1)
    {
        KillTimer(AccountData[playerid][RobbankCashTimer]);
        AccountData[playerid][RobbankCashTimer] = -1;
    }
    AccountData[playerid][ActivityTime] = 0;
    KillTimer(AccountData[playerid][pDutyTimer]);
    RemoveDrag(playerid);
    CheckDrag(playerid);
    Report_Clear(playerid);
    Ask_Clear(playerid);

    g_RaceCheck[playerid] ++;

    if (AccountData[playerid][IsLoggedIn])
    {
        AccountData[playerid][pPosX] = pX;
        AccountData[playerid][pPosY] = pY;
        AccountData[playerid][pPosZ] = pZ;
        AccountData[playerid][pPosA] = pA;
        AccountData[playerid][pInt] = GetPlayerInterior(playerid);
        AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);

        UpdatePlayerData(playerid);
        UnloadPlayerVehicle(playerid);

        if (AccountData[playerid][pJobVehicle] != 0)
        {
            DestroyJobVehicle(playerid);
            AccountData[playerid][pJobVehicle] = 0;
        }
    }

    if(IsValidDynamic3DTextLabel(AccountData[playerid][pAdoTag])) DestroyDynamic3DTextLabel(AccountData[playerid][pAdoTag]);
    if(IsValidDynamic3DTextLabel(AccountData[playerid][pMaskLabel])) DestroyDynamic3DTextLabel(AccountData[playerid][pMaskLabel]);

    if(AccountData[playerid][pAdminDuty] == 1)
        if(IsValidDynamic3DTextLabel(AccountData[playerid][pLabelDuty]))
            DestroyDynamic3DTextLabel(AccountData[playerid][pLabelDuty]);

    if(LivemodeOn[playerid])
        if(IsValidDynamic3DTextLabel(AccountData[playerid][LiveStream]))
            DestroyDynamic3DTextLabel(AccountData[playerid][LiveStream]);

    new reasontext[526], frmxt[255];

    switch(reason)
    {
        case 0: format(reasontext, sizeof(reasontext), "Timeout/Crash");
        case 1: format(reasontext, sizeof(reasontext), "Quit");
        case 2: format(reasontext, sizeof(reasontext), "Kicked/Banned");
    }

    if(DestroyDynamic3DTextLabel(labelDisconnect[playerid])) 
        labelDisconnect[playerid] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

    format(frmxt, sizeof(frmxt), "Player ["YELLOW"%d"WHITE"]"YELLOW" %s | %s"WHITE" Telah keluar dari server.\nReason: "RED"%s", playerid, AccountData[playerid][pName], AccountData[playerid][pUCP], reasontext);
    labelDisconnect[playerid] = CreateDynamic3DTextLabel(frmxt, -1, pX, pY, pZ, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 15.0, -1, 0);
    labelDisconnectTimer[playerid] = SetTimerEx("DestroyLabelOut", 30000, false, "i", playerid);
    
    if(AccountData[playerid][phoneDurringConversation])
    {
        CutCallingLine(playerid);
    }
    TerminateConnection(playerid);
    if(PlayerUfo_Veh[playerid] != 0)
    {
        DestroyVehicle(PlayerUfo_Veh[playerid]);
        DestroyObject(PlayerUfo_Obj[playerid]);
    }
    PlayerUfo_Veh[playerid] = 0;
    PlayerUfo_Obj[playerid] = 0;
    KargoRemakeUsed[playerid] = 0;
    if(gRacePlayerData[playerid][rVehicleAdm] != INVALID_VEHICLE_ID)
    {
        DestroyVehicle(gRacePlayerData[playerid][rVehicleAdm]);
        gRacePlayerData[playerid][rVehicleAdm] = INVALID_VEHICLE_ID;
    }
    gAdminRacePlayers[playerid] = INVALID_PLAYER_ID;
    gRacePlayerReady[playerid] = false;
    gRacePlayerData[playerid][rCheckpoint] = 0;
    gRacePlayerData[playerid][rLap] = 0;
    gRacePlayerData[playerid][rFinished] = false;
    DisableRemoteVehicleCollisions(playerid, false);
    DisablePlayerRaceCheckpoint(playerid);
    DestroyTDRacing(playerid);
    for(new i = 0; i < MAX_RACE_PLAYERS; i++)
    {
        if(gRacePlayers[i] == playerid)
        {
            gRacePlayers[i] = INVALID_PLAYER_ID;
            break;
        }
    }
    PlayerTDDestroy(playerid);
    DestroyVehicle( Drones[playerid] );
    if(playerid == JewelryHack_Player)
    {
        ClearJewelryHackDisconnect(playerid);
    }
    for(new i = 0; i < MAX_FIRE; i++)
    {
        if(ApiUnggun[i][aUsed] && ApiUnggun[i][aOwner] == playerid)
        {
            DestroyDynamicObject(ApiUnggun[i][aObject]);
            DestroyDynamic3DTextLabel(ApiUnggun[i][aText]);
            DestroyDynamicArea(ApiUnggun[i][aArea]);
            ApiUnggun[i][aUsed] = 0;
        }
    }
    return 1;
}	

public OnPlayerSpawn(playerid)
{
    if(AccountData[playerid][pGender] == 0)
    {
        TogglePlayerControllable(playerid, 0);
        SetPlayerHealth(playerid, 100.0);
        SetPlayerArmour(playerid, 0.0);
        SetPlayerCameraPos(playerid, 304.3501, 307.4839, 1004.5970);
        SetPlayerCameraLookAt(playerid, 306.2174, 304.1349, 1003.3);
        SetPlayerVirtualWorld(playerid, 1000 + playerid);
        SetPlayerInterior(playerid, 4);
        ClearAnimations(playerid);
        SetTimerEx("AnimChar", 500, false, "d", playerid);
    }
    else
    {
        if(!AccountData[playerid][pSpawned])
        {
            AccountData[playerid][pSpawned] = 1;
            SetCameraBehindPlayer(playerid);
            Streamer_ToggleIdleUpdate(playerid, true);
            StopAudioStreamForPlayer(playerid);
            
            // Set posisi, interior, dan world SEGERA saat spawn
            SetPlayerPos(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ] + 0.3);
            SetPlayerFacingAngle(playerid, AccountData[playerid][pPosA]);
            SetPlayerInterior(playerid, AccountData[playerid][pInt]);
            SetPlayerVirtualWorld(playerid, AccountData[playerid][pWorld]);

            GivePlayerMoney(playerid, AccountData[playerid][pMoney]);
            SetPlayerScore(playerid, AccountData[playerid][pLevel]);
            SetPlayerHealth(playerid, AccountData[playerid][pHealth]);
            SetPlayerArmour(playerid, AccountData[playerid][pArmour]);
            PreloadAnimations(playerid);

            TogglePlayerControllable(playerid, false);
            
            new Float:X, Float:Y, Float:Z;
            GetPlayerPos(playerid, X, Y, Z);
            
            ShowPlayerFooter(playerid, "~y~MEMUAT OBJECT", 7000);
            AccountData[playerid][pFreeze] = 1;
            AccountData[playerid][pFreezeTimer] = SetTimerEx("SetPlayerToUnfreeze", 7000, false, "iffff", playerid, X, Y, Z);
            
            Player_ToggleTelportAntiCheat(playerid, true);
            for(new x = 0; x < 28; x ++) PlayerTextDrawShow(playerid, DistrictSTATIC[playerid][x]);

            SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 999);
            SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 999);
            SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 1);
            SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 999);
            SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 999);
            SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 999);
            SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 999);
            SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 999);

            SendClientMessageEx(playerid, -1, ""BLUEJEGE"SERVER: "WHITE"Selamat datang "YELLOW"%s.", ReturnName(playerid));
            SendClientMessageEx(playerid, -1, ""BLUEJEGE"SERVER: "WHITE"Today is "YELLOW"%s", ReturnTime());
            SendClientMessage(playerid, -1, ""LIGHTSKYBLUE"MOTD: "WHITE"Selamat bermain dan memulai cerita di "TCRP"District ");

            if(PlayerKargoVars[playerid][KargoStarted])
            {
                Info(playerid, ""GRAY"Kamu punya kargo aktif, Gunakan "YELLOW"/startkargo "GRAY"untuk melanjutkan");
            }

            new vQuery[300];
            mysql_format(g_SQL, vQuery, sizeof(vQuery), "SELECT * FROM `player_vehicles` WHERE `PVeh_OwnerID` = '%d' ORDER BY `id` ASC", AccountData[playerid][pID]);
            mysql_tquery(g_SQL, vQuery, "Vehicle_Load", "d", playerid);

            if(AccountData[playerid][pDutyPD] || AccountData[playerid][pDutyPemerintah] || AccountData[playerid][pDutyEms] 
                || AccountData[playerid][pDutyBengkel] || AccountData[playerid][pDutyTrans] || AccountData[playerid][pDutyPedagang])
            {
                AccountData[playerid][pDutyTimer] = SetTimerEx("FactDutyHour", 1000, true, "d", playerid);
            }
        }

        if(IsPlayerInEvent(playerid))
            return 0;
        
        if(AccountData[playerid][pUsingUniform])
        {
            SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
        }
        else
        {
            SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
        }

        // Jika player sedang injured, paksa posisinya lagi
        if(AccountData[playerid][pInjured] == 1 && AccountData[playerid][pInjuredTime] != 0)
        {
            TogglePlayerControllable(playerid, false);
            SetPlayerPos(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ]);
            SetPlayerFacingAngle(playerid, AccountData[playerid][pPosA]);
            SetPlayerInterior(playerid, AccountData[playerid][pInt]);
            SetPlayerVirtualWorld(playerid, AccountData[playerid][pWorld]);
        }

        if(AccountData[playerid][pDutyPD] >= 1 || AccountData[playerid][pDutyPemerintah] >= 1 || AccountData[playerid][pDutyEms] >= 1 || AccountData[playerid][pDutyBengkel] >= 1 || AccountData[playerid][pDutyPedagang] >= 1 || AccountData[playerid][pDutyTrans] >= 1)
        {
            SetFactionColor(playerid);
        }

        SetTimerEx("TimersSpawn", 5000, false, "d", playerid);
    }
    
    if(PlayerNIK[playerid][0] == '\0')
    {
        GenerateRandomNIK(playerid);
    }
    return 1;
}

public TimersSpawn(playerid)
{
    if(!AccountData[playerid][pSpawned])
        return 0;

    if(AccountData[playerid][pJail] > 0)
    {
        SpawnPlayerInJail(playerid);
    }
    else if(AccountData[playerid][pArrestTime] > 0)
    {
        SetPlayerArrest(playerid, AccountData[playerid][pArrest]);
    }
    else 
    {
        // Unfreeze dan pastikan posisi terakhir
        TogglePlayerControllable(playerid, 1);
        SetPlayerPos(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ] + 0.2);
    }

    SetPlayerInterior(playerid, AccountData[playerid][pInt]);
    SetPlayerVirtualWorld(playerid, AccountData[playerid][pWorld]);
    
    AttachPlayerToys(playerid);
    AttachPlayerToysaxp(playerid);
    AttachPlayerToysDragon(playerid);
    AttachPlayerToysSonic(playerid);
    AttachPlayerToysGrinch(playerid);
    AttachPlayerToysGhost(playerid);
    SetWeapons(playerid);
    return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	if(killerid != INVALID_PLAYER_ID)
	{
		new d_msg[512];
		format(d_msg, sizeof(d_msg), "💀 **DEATH LOG**\n**Korban:** %s\n**Pembunuh:** %s\n**Senjata:** %s (ID: %d)", 
			AccountData[playerid][pName], 
			AccountData[killerid][pName], 
			ReturnWeaponName(reason), 
			reason
		);
		SendDiscordWebhook(WEBHOOK_DEATH, d_msg);
	}
	if(!AccountData[playerid][pSpawned])
		return 0;

	foreach(new i : Player) if (IsPlayerConnected(i))
	{
		if(AccountData[i][pAdmin] > 0 && AccountData[i][pTheStars] > 0)
		{
			SendDeathMessageToPlayer(i, killerid, playerid, reason);
			return 1;
		}
	}
	new reasontext[596];
	switch(reason)
	{
		case 0: reasontext = "Tangan Kosong";
		case 1: reasontext = "Brass Knuckles";
		case 2: reasontext = "Golf Club";
		case 3: reasontext = "Nite Stick";
		case 4: reasontext = "Knife";
		case 5: reasontext = "Basebal Bat";
		case 6: reasontext = "Shovel";
		case 7: reasontext = "Pool Cue";
		case 8: reasontext = "Katana";
		case 9: reasontext = "Chain Shaw";
		case 14: reasontext = "Cane";
		case 18: reasontext = "Molotov";
		case 22: reasontext = "Colt 45";
		case 23: reasontext = "SLC";
		case 24: reasontext = "Desert Eagle";
		case 25: reasontext = "Shotgun";
		case 26: reasontext = "Sawnoff Shotgun";
		case 27: reasontext = "Combat Shotgun";
		case 28: reasontext = "Micro SMG/Uzi";
		case 29: reasontext = "MP5";
		case 30: reasontext = "AK-47";
		case 31: reasontext = "M4";
		case 32: reasontext = "Tec-9";
		case 33: reasontext = "Coutry Rifle";
		case 38: reasontext = "Mini Gun";
		case 49: reasontext = "Tertabrak Kendaraan";
		case 50: reasontext = "Helicopter Blades";
		case 51: reasontext = "Explode";
		case 53: reasontext = "Drowned";
		case 54: reasontext = "Splat";
		case 255: reasontext = "Suicide";
	}

	SetPlayerArmedWeapon(playerid, 0);
	KillTimer(AccountData[playerid][pMechanic]);
	AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
	if( GetPVarInt( playerid, "DroneSpawned" ) == 1 ) 
    {
    	SetPVarInt( playerid, "DroneSpawned", 0 );
    	DestroyVehicle( Drones[playerid] );
    	SendClientMessage( playerid, COLOR_GREEN, "Your drone was automatically shut down as you have died." );
	}
	return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ )
{
	new weaponid = EditingWeapon[playerid];
	if(response)
	{
		if(weaponid)
		{
			new enum_index = weaponid - 22, weaponname[18], string[340];
 
            GetWeaponName(weaponid, weaponname, sizeof(weaponname));
           
            WeaponSettings[playerid][enum_index][Position][0] = fOffsetX;
            WeaponSettings[playerid][enum_index][Position][1] = fOffsetY;
            WeaponSettings[playerid][enum_index][Position][2] = fOffsetZ;
            WeaponSettings[playerid][enum_index][Position][3] = fRotX;
            WeaponSettings[playerid][enum_index][Position][4] = fRotY;
            WeaponSettings[playerid][enum_index][Position][5] = fRotZ;
 
            RemovePlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid));
            SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModel(weaponid), WeaponSettings[playerid][enum_index][Bone], fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, 1.0, 1.0, 1.0);
 
			ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil merubah posisi letak %s", weaponname));
           
			EditingWeapon[playerid] = 0;
            mysql_format(g_SQL, string, sizeof(string), "INSERT INTO weaponsettings (Owner, WeaponID, PosX, PosY, PosZ, RotX, RotY, RotZ) VALUES ('%d', %d, %.3f, %.3f, %.3f, %.3f, %.3f, %.3f) ON DUPLICATE KEY UPDATE PosX = VALUES(PosX), PosY = VALUES(PosY), PosZ = VALUES(PosZ), RotX = VALUES(RotX), RotY = VALUES(RotY), RotZ = VALUES(RotZ)", AccountData[playerid][pID], weaponid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ);
            mysql_tquery(g_SQL, string);
		}

		if(AccountData[playerid][toySelected] != -1)
		{
			new id = AccountData[playerid][toySelected];
			pToys[playerid][id][toy_x] = fOffsetX;
			pToys[playerid][id][toy_y] = fOffsetY;
			pToys[playerid][id][toy_z] = fOffsetZ;
			pToys[playerid][id][toy_rx] = fRotX;
			pToys[playerid][id][toy_ry] = fRotY;
			pToys[playerid][id][toy_rz] = fRotZ;
			pToys[playerid][id][toy_sx] = fScaleX;
			pToys[playerid][id][toy_sy] = fScaleY;
			pToys[playerid][id][toy_sz] = fScaleZ;
			
			MySQL_SavePlayerToys(playerid);
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menyimpan kordinat baru.");
			AccountData[playerid][toySelected] = -1;
		}
	}
	else
	{
		if(EditingWeapon[playerid])
		{
			new enum_index = weaponid - 22;
			SetPlayerAttachedObject(playerid, GetWeaponObjectSlot(weaponid), GetWeaponModel(weaponid), WeaponSettings[playerid][enum_index][Bone], fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, 1.0, 1.0, 1.0);
			EditingWeapon[playerid] = 0;
		}

		if(AccountData[playerid][toySelected] != -1)
		{
			new id = AccountData[playerid][toySelected];
			SetPlayerAttachedObject(playerid,
				id,
				modelid,
				boneid,
				pToys[playerid][id][toy_x],
				pToys[playerid][id][toy_y],
				pToys[playerid][id][toy_z],
				pToys[playerid][id][toy_rx],
				pToys[playerid][id][toy_ry],
				pToys[playerid][id][toy_rz],
				pToys[playerid][id][toy_sx],
				pToys[playerid][id][toy_sy],
				pToys[playerid][id][toy_sz]);
			AccountData[playerid][toySelected] = -1;
		}
	}
	SetPVarInt(playerid, "UpdatedToy", 1);
	return 1;
}


public OnPlayerEditDynamicObject(playerid, STREAMER_TAG_OBJECT: objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if(AccountData[playerid][EditingDeerID] != -1 && Iter_Contains(Hunt, AccountData[playerid][EditingDeerID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new etid = AccountData[playerid][EditingDeerID];
	        HuntData[etid][DeerPOS][0] = x;
	        HuntData[etid][DeerPOS][1] = y;
	        HuntData[etid][DeerPOS][2] = z;
	        HuntData[etid][DeerROT][0] = rx;
	        HuntData[etid][DeerROT][1] = ry;
	        HuntData[etid][DeerROT][2] = rz;

	        SetDynamicObjectPos(objectid, HuntData[etid][DeerPOS][0], HuntData[etid][DeerPOS][1], HuntData[etid][DeerPOS][2]);
	        SetDynamicObjectRot(objectid, HuntData[etid][DeerROT][0], HuntData[etid][DeerROT][1], HuntData[etid][DeerROT][2]);

			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, HuntData[etid][DeerLabel], E_STREAMER_X, HuntData[etid][DeerPOS][0]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, HuntData[etid][DeerLabel], E_STREAMER_Y, HuntData[etid][DeerPOS][1]);
			Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, HuntData[etid][DeerLabel], E_STREAMER_Z, HuntData[etid][DeerPOS][2] + 1.1);

		    HuntSave(etid);
	        AccountData[playerid][EditingDeerID] = -1;
	    }
	    if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new etid = AccountData[playerid][EditingDeerID];
	        SetDynamicObjectPos(objectid, HuntData[etid][DeerPOS][0], HuntData[etid][DeerPOS][1], HuntData[etid][DeerPOS][2]);
	        SetDynamicObjectRot(objectid, HuntData[etid][DeerROT][0], HuntData[etid][DeerROT][1], HuntData[etid][DeerROT][2]);
	        AccountData[playerid][EditingDeerID] = -1;
	    }
	}
	else if(AccountData[playerid][EditingLADANGID] != -1 && Iter_Contains(Ladang, AccountData[playerid][EditingLADANGID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new etid = AccountData[playerid][EditingLADANGID];
	        LadangData[etid][kanabisX] = x;
	        LadangData[etid][kanabisY] = y;
	        LadangData[etid][kanabisZ] = z;
	        LadangData[etid][kanabisRX] = rx;
	        LadangData[etid][kanabisRY] = ry;
	        LadangData[etid][kanabisRZ] = rz;

	        SetDynamicObjectPos(objectid, LadangData[etid][kanabisX], LadangData[etid][kanabisY], LadangData[etid][kanabisZ]);
	        SetDynamicObjectRot(objectid, LadangData[etid][kanabisRX], LadangData[etid][kanabisRY], LadangData[etid][kanabisRZ]);

		    Ladang_Save(etid);
	        AccountData[playerid][EditingLADANGID] = -1;
	    }

	    if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new etid = AccountData[playerid][EditingLADANGID];
	        SetDynamicObjectPos(objectid, LadangData[etid][kanabisX], LadangData[etid][kanabisY], LadangData[etid][kanabisZ]);
	        SetDynamicObjectRot(objectid, LadangData[etid][kanabisRX], LadangData[etid][kanabisRY], LadangData[etid][kanabisRZ]);
	        AccountData[playerid][EditingLADANGID] = -1;
	    }
	}
	else if(AccountData[playerid][EditingATMID] != -1 && Iter_Contains(ATMS, AccountData[playerid][EditingATMID]))
	{
		if(response == EDIT_RESPONSE_FINAL)
	    {
	        new etid = AccountData[playerid][EditingATMID];
	        AtmData[etid][atmX] = x;
	        AtmData[etid][atmY] = y;
	        AtmData[etid][atmZ] = z;
	        AtmData[etid][atmRX] = rx;
	        AtmData[etid][atmRY] = ry;
	        AtmData[etid][atmRZ] = rz;

	        SetDynamicObjectPos(objectid, AtmData[etid][atmX], AtmData[etid][atmY], AtmData[etid][atmZ]);
	        SetDynamicObjectRot(objectid, AtmData[etid][atmRX], AtmData[etid][atmRY], AtmData[etid][atmRZ]);

		  	Atm_Refresh(etid);
		    Atm_Save(etid);
	        AccountData[playerid][EditingATMID] = -1;
	    }

	    if(response == EDIT_RESPONSE_CANCEL)
	    {
	        new etid = AccountData[playerid][EditingATMID];
	        SetDynamicObjectPos(objectid, AtmData[etid][atmX], AtmData[etid][atmY], AtmData[etid][atmZ]);
	        SetDynamicObjectRot(objectid, AtmData[etid][atmRX], AtmData[etid][atmRY], AtmData[etid][atmRZ]);
	        AccountData[playerid][EditingATMID] = -1;
	    }
	}
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	if(AccountData[playerid][pGpsActive] == 1)
	{
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil menemukan Ws Anda");
		DisablePlayerRaceCheckpoint(playerid);
		
		AccountData[playerid][pGpsActive] = 0;
	}
	if(pMapCP[playerid])
	{
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil sampai ke lokasi tujuan");
		DisablePlayerRaceCheckpoint(playerid);
		
		pMapCP[playerid] = false;
	}
	if(AccountData[playerid][pTrackCar] == 1)
	{
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil sampai ke lokasi tujuan");
		AccountData[playerid][pTrackCar] = 0;
		
		DisablePlayerRaceCheckpoint(playerid);
	}
	if(AccountData[playerid][pTrackHoused] == 1)
	{
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda berhasil sampai ke lokasi tujuan");
		AccountData[playerid][pTrackHoused] = 0;
		DisablePlayerRaceCheckpoint(playerid);
		
	}
	if(AccountData[playerid][pDiPesawat])
	{
		DisablePlayerCheckpoint(playerid);
		AccountData[playerid][pDiPesawat] = false;
		AccountData[playerid][pPosX] = 1660.7273;
		AccountData[playerid][pPosY] = -2152.7925;
		AccountData[playerid][pPosZ] = 1029.0175;
		AccountData[playerid][pPosA] = 178.3975;
		AccountData[playerid][pInDoor] = 7;
		SetPlayerVirtualWorldEx(playerid, 0);
		SetPlayerInteriorEx(playerid, 0);
		SetPlayerPositionEx(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ], AccountData[playerid][pPosA], 6000);
	}
	if(jobs::mixer[playerid][mixerDuty][1])
    {
        DisablePlayerCheckpoint(playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENUMPAHKAN");
        ShowProgressBar(playerid);
        jobs::mixer[playerid][mixerDuty][1] = false;
        jobs::mixer[playerid][mixerTimer] = SetTimerEx("CorLokasi", 1000, true, "i", playerid);
		
    }
    if(jobs::mixer[playerid][mixerDuty][2])
    {
        if(IsPlayerInAnyVehicle(playerid))
        {
            RemovePlayerFromVehicle(playerid);
            DestroyVehicle(GetPlayerVehicleID(playerid));
            GiveMoney(playerid, 150);
            jobs::mixer[playerid][mixerDuty][2] = false;
            jobs::mixer_reset_enum(playerid);
        }
        
    }
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

Dialog:DeathRespawnConf(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(!IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang Pingsan!");

	SetPlayerHealthEx(playerid, 100.0);
	AccountData[playerid][pHunger] = 100;
	AccountData[playerid][pThirst] = 100;
	AccountData[playerid][pStress] = 0;
	AccountData[playerid][pInjured] = 0;
	AccountData[playerid][pInjuredTime] = 0;
	Inventory_Clear(playerid);
	ResetPlayerWeaponsEx(playerid);
	
	ShowTDN(playerid, NOTIFICATION_INFO, "Kamu koma dan dilarikan ke Rumah Sakit");

	SetPlayerPositionEx(playerid, 907.8289, 711.1892, 5010.3184, 358.7794, 5000);
	SetPlayerVirtualWorldEx(playerid, 5);
	SetPlayerInteriorEx(playerid, 5);

	foreach(new pid : Player) {
		if(AccountData[pid][pFaction] == FACTION_EMS && AccountData[pid][pDutyEms]) {
			SendClientMessageEx(pid, -1, ""YELLOW"[Koma]"WHITE_E" %s telah terbangun di ruang koma", ReturnName(playerid));
		}
	}

	AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], "KOMA", 0);
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(PRESSED(KEY_WALK)) //ALT
    {
        if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            if(IsPlayerInRangeOfPoint(playerid, 0.5, 990.8473,-1463.8655,13.8521))
            {
				if(AccountData[playerid][pFamily] == -1) 
					return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya Anggota Family yang dapat Hack Jewel!");
				
				/*new count, count2;
				foreach(new i : Player) if (IsPlayerConnected(i) && AccountData[i][pSpawned])
				{
					if(AccountData[i][pDutyPD]) count ++;
					if(AccountData[i][pDutyEms]) count2 ++;
				}
				if(count < 4 && count2 < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal 5 Polisi dan 3 EMS!");*/

				if(Inventory_Count(playerid, "Hacking Tools") < 1)
					return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Hacking Tools");

                if(JewelryHack_IsOpened == true) return 1;

                ShowJewelryHack(playerid);
                JewelryHack_IsOpened = true;
				if(!IsPlayerInAnyVehicle(playerid))
				{
					SetPlayerAttachedObject(playerid, 9, 19786, 5, 0.182999, 0.048999, -0.112999, -66.699935, -23.799949, -116.699996, 0.130999, 0.136000, 0.142000, 0, 0);
					ApplyAnimation(playerid, "INT_SHOP","shop_loop", 4.1, true, false, false, true, 0, true);
				}
            }

            for(new i; i < 24; i++) 
            {
                if(IsPlayerInRangeOfPoint(playerid, 1, Jewelry_RobArea[i][0], Jewelry_RobArea[i][1], Jewelry_RobArea[i][2]))
                {
					if(AccountData[playerid][pFamily] == -1) 
						return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya Anggota Family yang dapat mengambil Jewel!");

                    if(JewelryHack_IsOpened != false) return 1; //seseorang masih sedang membuka hack
                    if(Jewelry_Robbed[i] != 1) return 1;
                    if(isRobbing_Jewelry[playerid] == 1) return 1;

                    ApplyAnimation(playerid,"CAR_CHAT","CAR_Sc4_BL",4.0,1,1,1,0,0,0);

                    AccountData[playerid][ActivityTime] = 1;
					PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENGAMBIL JEWEL");
					ShowProgressBar(playerid);
					isRobbing_Jewelry[playerid] = 1;
					AccountData[playerid][RobJewelryTimer] = SetTimerEx("UsingRobJewelry", 1000, true, "ii", playerid, i);
                    return 1;
                }
            }

            for(new i; i < 3; i++) 
            {
                if(IsPlayerInRangeOfPoint(playerid, 1.5, Jewelry_ChangeArea[i][0], Jewelry_ChangeArea[i][1], Jewelry_ChangeArea[i][2]))
                {
					if(AccountData[playerid][pFamily] == -1) 
						return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya Anggota Family yang dapat menjual Jewel!");

                    if(isHaveJewelry[playerid] == 0) 
						return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki jewel!");

					new maxTukaran = 35000;
                    new totalTukaran = isHaveJewelry[playerid] * 150;
					if(totalTukaran > maxTukaran)
					{
						totalTukaran = maxTukaran;
					}

                    //berikan logika untuk memberikan uang
                    GiveMoney(playerid, totalTukaran);
                    AccountData[playerid][pMoney] += totalTukaran; //contoh dalam inferno

                    new tks[200];
                    format(tks, sizeof(tks), "{e1c900}[Jewel]: "WHITE"Anda berhasil mendapatkan {32ff24}%d", totalTukaran);
                    SendClientMessageEx(playerid, -1, tks);

                    RemovePlayerAttachedObject(playerid, 9);
					DisablePlayerCheckpoint(playerid);
                    isHaveJewelry[playerid] = 0;
                    isCoordinat_ChangeJewelry[playerid] = 0;
					GameModeClearJewelry();
                    return 1;
                }
            }
        }
    }
    if(PRESSED(KEY_FIRE))
    {
        if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            for(new i; i < 24; i++) 
            {
                if(IsPlayerInRangeOfPoint(playerid, 1, Jewelry_RobArea[i][0], Jewelry_RobArea[i][1], Jewelry_RobArea[i][2]))
				{
					if(AccountData[playerid][pFamily] == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya Anggota Family yang dapat menghancurkan kaca Jewel!");
					if(!JewelryHack_Completed) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus menyelesaikan hacking alarm jewel terlebih dahulu!");
					if(JewelryHack_IsOpened != false) return 1;
					if(GetPlayerWeaponEx(playerid) != WEAPON_BAT) return 1;
					if(Jewelry_Robbed[i] != 2) return 1;

					UpdateDynamic3DTextLabelText(Jewelry_RobbedText[i], -1, "{ffe000}'ALT'");
					Jewelry_Robbed[i] = 1; // pecah

					if(JewelryHack_Alarm != false) // alarm masih nyala
					{
						// Kirim peringatan ke semua warga
						SendClientMessageToAll(-1, "{db7b00}============ PERHATIAN ============");
						SendClientMessageToAll(-1, "Telah Terjadinya perampokan di toko "YELLOW"Jewelry"); 
						SendClientMessageToAll(-1, "{db1700}Catatan: {ffffff}Seluruh warga harap menjauh dari lokasi perampokan!"); 
						SendClientMessageToAll(-1, "{db7b00}===================================");

						// Kirim lokasi ke polisi on duty
						new Float:px = Jewelry_RobArea[i][0];
						new Float:py = Jewelry_RobArea[i][1];
						new Float:pz = Jewelry_RobArea[i][2];
						JewelryHack_Alarm = false;
						SetTimer("JewelryAlarmDelay", 60000, false);

						foreach(new j : Player) if (AccountData[j][pSpawned])
						{
							if(AccountData[j][pFaction] == FACTION_POLISI && AccountData[j][pDutyPD])
							{
								static shstr[255];
								format(shstr, sizeof(shstr), "Telah terjadi perampokan jewel di~n~%s", GetLocation(px, py, pz));
								
								DisablePlayerRaceCheckpoint(j);
								SetPlayerRaceCheckpoint(j, 1, px, py, pz, 0.0, 0.0, 0.0, 5.0);
								Warning(j, "Lokasi jewel yang sedang dirampok telah ditandai pada blip di map!");
							}
						}
					}
					return 1;
				}
            }
        }
    }
	if((newkeys & KEY_CROUCH) && IsPlayerPolice(playerid))
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.0, 662.5468,-1493.5961,20.9623))
		{
			new weaponid = GetPlayerWeaponEx(playerid);
			if(weaponid == 0)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak memegang senjata.");

			new ammo = GetPlayerAmmoEx(playerid);
			if(ammo <= 0)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Senjata kamu tidak punya peluru.");

			Locker_AddItem(playerid, weaponid, ammo);
			ResetPlayerCurrentWeapon(playerid);
		}
	}
	/* Job Mixer */
	if(PRESSED(KEY_YES) && IsPlayerInRangeOfPoint(playerid, 2.0, 641.2187,1238.3390,11.6796))
    {
		if(jobs::mixer[playerid][mixerDuty][0]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah memulai pekerjaan");
        if(GetPlayerJob(playerid) != JOB_DRIVER_MIXERS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pekerja supir mixer");
        jobs::mixer[playerid][mixerVehicle] = CreateVehicle(524, 639.8187,1250.2065,11.6333,306.5278, 5, 5, 60000, false);
		if(IsValidVehicle(jobs::mixer[playerid][mixerVehicle]))
		{
			VehicleCore[jobs::mixer[playerid][mixerVehicle]][vCoreFuel]=MAX_FUEL_FULL;
		    PutPlayerInVehicle(playerid, jobs::mixer[playerid][mixerVehicle], 0);
			jobs::mixer[playerid][mixerDuty][0] = true;
		}
        ShowPlayerFooter(playerid, "~w~~h~Isi kendaraan dengan ~g~beton ~w~di~n~belakang", 3000, 1);
    }
    if(PRESSED(KEY_CROUCH) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsPlayerInRangeOfPoint(playerid, 3.0, 590.0992,1243.8767,11.7188))
    {
        if(GetPlayerJob(playerid) != JOB_DRIVER_MIXERS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pekerja supir mixer");
        ShowMixTD(playerid);
    }
	/* Senter */
	if(PRESSED(KEY_CTRL_BACK) && AccountData[playerid][pFlashShown] && !IsPlayerInAnyVehicle(playerid))
	{
		switch(AccountData[playerid][pFlashOn])
		{
			case false:
            {
				if (!IsPlayerPlayingAnimation(playerid, "ped", "phone_talk"))
				{
					ApplyAnimationEx(playerid, "ped", "phone_talk", 1.1, 1, 1, 1, 1, 1, 1);
				}
				
                AccountData[playerid][pFlashOn] = true;
                SetPlayerAttachedObject(playerid, 5, 19295, 1,  0.068000, 0.606000, 0.000000,  0.000000, -4.500000, 12.299996,  1.000000, 1.000000, 1.020000); // Light Objects
                ShowPlayerFooter(playerid, "~w~Senter ~g~Nyala", 3000);
            }
            case true:
            {
                AccountData[playerid][pFlashOn] = false;
                RemovePlayerAttachedObject(playerid, 5);
                ShowPlayerFooter(playerid, "~w~Senter ~r~Mati", 3000);
            }
		}
	}

	/* Greenzone */
	if(newkeys & KEY_FIRE && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && IsPlayerInDynamicArea(playerid, AreaData[BandaraGreenZone]))
	{
		ClearAnimations(playerid, 1);
        SetPlayerArmedWeapon(playerid, 0);

        SetPVarInt(playerid, "GreenzoneWarning", GetPVarInt(playerid, "GreenzoneWarning")+1);
		Info(playerid, "Anda tidak dapat memukul / menembak di Area Greenzone. "RED"%d/5"WHITE" anda akan ditendang dari server.", GetPVarInt(playerid, "GreenzoneWarning"));

        if(GetPVarInt(playerid, "GreenzoneWarning") == 5) {
			Warning(playerid, "Anda telah ditendang dari server karena mendapatkan "RED"5"WHITE" peringatan Greenzone!");
			DeletePVar(playerid, "GreenzoneWarning");
            KickEx(playerid);
        }
	}

	if((newkeys & KEY_JUMP) && !IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && !IsPlayerInEvent(playerid) && !DurringHunting[playerid] && !AccountData[playerid][pAdminDuty])
	{
		PlayerPressedJump[playerid] ++;
		SetTimerEx("PressJumpReset", 3000, false, "d", playerid); // Makes it where if they dont spam the jump key, they wont fall

		if(PlayerPressedJump[playerid] >= 3)
		{
			new Float: POS[3];
			GetPlayerPos(playerid, POS[0], POS[1], POS[2]);
			SetPlayerPos(playerid, POS[0], POS[1], POS[2] - 0.2);
			ApplyAnimationEx(playerid, "PED", "FALL_collapse", 4.1, 0, 1, 0, 0, 0, 1); // applies the fallover animation
			PlayerPlayNearbySound(playerid, 1163);
			PlayerPressedJump[playerid] = 0;
		}
	}

	/* Voting Systemm */
	if(newkeys & KEY_JUMP && !(oldkeys & KEY_JUMP) && !AccountData[playerid][pInjured])
	{
		if(AccountData[playerid][pRFoot] < 50 || AccountData[playerid][pLFoot] < 50)
		{
			ApplyAnimation(playerid, "GYMNASIUM", "gym_jog_falloff", 4.1, 0, 1, 1, 0, 0);
		}
	}
	if((newkeys & KEY_WALK))
	{
		foreach(new id : GStation)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.5, gsData[id][gsPosX], gsData[id][gsPosY], gsData[id][gsPosZ]) && !strcmp(gsData[id][gOwner], "-"))
			{
				if(gsData[id][gPrice] > AccountData[playerid][pMoney]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak cukup, anda tidak dapat membeli gas station ini");
				if(strcmp(gsData[id][gOwner], "-")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Seseorang sudah memiliki gas station ini");
				if(AccountData[playerid][pVip] == 1)
				{
					#if LIMIT_PER_PLAYER > 0
					if(Player_GasCount(playerid) + 1 > 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membeli gas station lagi");
					#endif
				}
				else if(AccountData[playerid][pVip] == 2)
				{
					#if LIMIT_PER_PLAYER > 0
					if(Player_GasCount(playerid) + 1 > 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membeli gas station lagi");
					#endif
				}
				else if(AccountData[playerid][pVip] == 3)
				{
					#if LIMIT_PER_PLAYER > 0
					if(Player_GasCount(playerid) + 1 > 4) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membeli gas station lagi");
					#endif
				}
				else if(AccountData[playerid][pVip] == 4)
				{
					#if LIMIT_PER_PLAYER > 0
					if(Player_GasCount(playerid) + 1 > 5) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membeli gas station lagi");
					#endif
				}
				else
				{
					#if LIMIT_PER_PLAYER > 0
					if(Player_GasCount(playerid) + 1 > 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membeli gas station lagi");
					#endif
				}
				TakeMoney(playerid, gsData[id][gPrice]);
				GetPlayerName(playerid, gsData[id][gOwner], MAX_PLAYER_NAME);
				gsData[id][gOwnerID] = AccountData[playerid][pID];
				new str[522], query[500];
				format(str,sizeof(str),"[GAS STATION]: %s membeli Gas station id %d seharga %s!", GetRPName(playerid), id, FormatMoney(gsData[id][gPrice]));
				SendClientMessageEx(playerid, -1, str);
				mysql_format(g_SQL, query, sizeof(query), "UPDATE gstations SET owner='%s', ownerid='%d' WHERE ID='%d'", gsData[id][gOwner], gsData[id][gOwnerID], id);
				mysql_tquery(g_SQL, query);
				GStation_Save(id);
				GStation_Refresh(id);
			}
		}
	}
	if(newkeys & KEY_YES && OpenVote == 1 && !PlayerVoting[playerid] && !AccountData[playerid][ActivityTime])
	{

		ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda Setuju untuk Voting yang sedang berjalan");

		PlayerVoting[playerid] = true;
		VoteYes += 1;
		SendClientMessageToAllEx(-1, ""YELLOW"VOTE:"WHITE" %s // Yes: "GREEN"%d"WHITE" // No: "RED"%d", VoteText, VoteYes, VoteNo);
		SendClientMessageToAllEx(-1, "~> Gunakan "GREEN"Y"WHITE" untuk Yes & "RED"N"WHITE" untuk Tidak");
	}

	if(newkeys & KEY_NO && OpenVote == 1 && !PlayerVoting[playerid] && !AccountData[playerid][ActivityTime])
	{

		ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda Tidak Setuju untuk Voting yang sedang berjalan");

		PlayerVoting[playerid] = true;
		VoteNo += 1;
		SendClientMessageToAllEx(-1, ""YELLOW"VOTE:"WHITE" %s // Yes: "GREEN"%d"WHITE" // No: "RED"%d", VoteText, VoteYes, VoteNo);
		SendClientMessageToAllEx(-1, "~> Gunakan "GREEN"Y"WHITE" untuk Yes & "RED"N"WHITE" untuk Tidak");
	}

	/* Anti Bike Hopping */
	if(PRESSED(KEY_ACTION))
	{
		static vehicleid;

		if(IsPlayerInAnyVehicle(playerid) && ((vehicleid = GetPlayerVehicleID(playerid)) != INVALID_VEHICLE_ID))
		{
			if(GetVehicleModel(vehicleid) == 509 || GetVehicleModel(vehicleid) == 481 || GetVehicleModel(vehicleid) == 510)
			{
				new Float:x, Float:y, Float:z;
				GetPlayerPos(playerid, x, y, z);
				SetPlayerPos(playerid, x, y, z);

				ApplyAnimationEx(playerid, "PED", "BIKE_fall_off", 4.1, 0, 1, 1, 1, 0, 1);
			}
		}
	}

	if(newkeys & KEY_JUMP && !(oldkeys & KEY_JUMP) && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED && !AccountData[playerid][pInjured])
	{
		ApplyAnimation(playerid, "GYMNASIUM", "gym_jog_falloff", 4.1, 0, 1, 1, 0, 0);
	}
	if(newkeys & KEY_YES)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.0, 1675.340087, -2326.237548, 13.546875)) 
		{
			if(AccountData[playerid][pClaimStarterpack] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sudah klaim starterpack sebelumnya");

			AccountData[playerid][pClaimStarterpack] = 1;
			
			Inventory_Add(playerid, "Smartphone", 18870, 1);
			Inventory_Add(playerid, "Nasi Goreng", 2355, 5);
			Inventory_Add(playerid, "Es Teh", 1546, 5);
			
			ShowItemBox(playerid, "Received 1x", "Smartphone", 18870);
			ShowItemBox(playerid, "Received 5x", "Nasi Goreng", 2355);
			ShowItemBox(playerid, "Received 5x", "Es Teh", 1546);

			new Float:x, Float:y, Float:z, Float:a, modelid;
			modelid = 422; 
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, a);
			Vehicle_Backpack(playerid, modelid, FACTION_NONE, x, y, z, a, 0, 0, 10000);

			GiveMoney(playerid, 6000);
			AccountData[playerid][pBankMoney] += 2000;

			Info(playerid, "Anda berhasil claim starterpack dan mendapatkan 1x "YELLOW_E"Smartphone "WHITE_E"5x "YELLOW_E"Nasi Goreng, Es Teh");
			Info(playerid, "Uang Saku: "GREEN_E"$6000 "WHITE_E"| Uang Bank: "GREEN_E"$2000");
			Info(playerid, "Kendaraan mobil "YELLOW_E"Bobcat");
		}
	}
	if(newkeys & KEY_YES)
	{
		if(AccountData[playerid][pInjured])
		{
		    Dialog_Show(playerid, DeathRespawnConf, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Konfirmasi Koma",
		    "Apakah anda benar benar yakin ingin melakukan tindakan ini?\n"RED"NOTE: Tindakan ini dapat menghilangkan semua barang di tas termasuk uang cash", "Iya", "Tidak");
		}
	}
	if(newkeys & KEY_YES)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, 319.2026,-1848.7046,5.1282))
		{
			ShowMenuMakanan(playerid);
		}
	}
	if((newkeys & KEY_SECONDARY_ATTACK) && !IsPlayerInAnyVehicle(playerid))
    {
        if(PlayerUfo_Veh[playerid] != 0)
        {
            new Float:px, Float:py, Float:pz;
            GetPlayerPos(playerid, px, py, pz);

            new Float:vx, Float:vy, Float:vz;
            GetVehiclePos(PlayerUfo_Veh[playerid], vx, vy, vz);

            if(GetDistanceBetweenPoints(px, py, pz, vx, vy, vz) < 5.0)
            {
                PutPlayerInVehicle(playerid, PlayerUfo_Veh[playerid], 0);
                SetTimerEx("HideUfoVehicle", 100, false, "ii", playerid, PlayerUfo_Veh[playerid]);
            }
        }
    }
	if(newkeys & KEY_SECONDARY_ATTACK && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
		foreach(new famid : Families)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.5, FamData[famid][famExtPos][0], FamData[famid][famExtPos][1], FamData[famid][famExtPos][2]))
			{
				if(IsDoorMyFamilie(playerid) == AccountData[playerid][pFamily])
				{
					if(FamData[famid][famIntPos][0] == 0.0 && FamData[famid][famIntPos][1] == 0.0 && FamData[famid][famIntPos][2] == 0.0)
						return ShowTDN(playerid, NOTIFICATION_ERROR, "Interior ini masih kosong!");

					if(AccountData[playerid][pFaction] == FACTION_NONE)
						if(AccountData[playerid][pFamily] == -1)
							return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak memiliki Akses untuk masuk kedalam sini!");
					
					AccountData[playerid][UsingDoor] = true;
					Player_ToggleTelportAntiCheat(playerid, false);
					SetPlayerPositionEx(playerid, FamData[famid][famIntPos][0], FamData[famid][famIntPos][1], FamData[famid][famIntPos][2], FamData[famid][famIntPos][3], 5000);

					SetPlayerInterior(playerid, FamData[famid][famInterior]);
					SetPlayerVirtualWorld(playerid, famid);
					SetCameraBehindPlayer(playerid);
					SetPlayerWeather(playerid, 0);
					AccountData[playerid][pInFamily] = famid;
				}
				else ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan bagian dari Families ini!");
			}
			new infamily = AccountData[playerid][pInFamily];
			if(AccountData[playerid][pInFamily] != -1 && IsPlayerInRangeOfPoint(playerid, 2.5, FamData[infamily][famIntPos][0], FamData[infamily][famIntPos][1],FamData[infamily][famIntPos][2]))
			{
				AccountData[playerid][pInFamily] = -1;
				AccountData[playerid][UsingDoor] = true;
				Player_ToggleTelportAntiCheat(playerid, false);
				SetPlayerPositionEx(playerid, FamData[infamily][famExtPos][0], FamData[infamily][famExtPos][1], FamData[infamily][famExtPos][2], FamData[infamily][famExtPos][3], 5000);

				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetCameraBehindPlayer(playerid);
				SetPlayerWeather(playerid, WorldWeather);
				Player_ToggleTelportAntiCheat(playerid, true);
			}
		}
	}
	
	if(newkeys & KEY_LOOK_BEHIND)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) return 0;

		new vehid = GetNearestVehicleToPlayer(playerid, 3.0, false);
		if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan apapun di sekitar!");

		foreach(new iter : PvtVehicles)
		{
			if(PlayerVehicle[iter][pVehExists])
			{
				if(PlayerVehicle[iter][pVehPhysic] == vehid)
				{
					if(PlayerVehicle[iter][pVehOwnerID] != AccountData[playerid][pID]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini bukan milik anda!");
					
					PlayerPlaySound(playerid, 1147, 0.0, 0.0, 0.0);
					PlayerVehicle[iter][pVehLocked] = !(PlayerVehicle[iter][pVehLocked]);

					PlayerPlayNearbySound(playerid, SOUND_LOCK_CAR_DOOR);
					LockVehicle(PlayerVehicle[iter][pVehPhysic], PlayerVehicle[iter][pVehLocked]);
					ToggleVehicleLights(PlayerVehicle[iter][pVehPhysic], PlayerVehicle[iter][pVehLocked]);
					GameTextForPlayer(playerid, sprintf("~w~%s %s", GetVehicleName(PlayerVehicle[iter][pVehPhysic]), PlayerVehicle[iter][pVehLocked] ? ("~r~Locked") : ("~g~Unlocked")), 4000, 4);
					return 1;
				}
			}
		}

		if(AccountData[playerid][pJobVehicle] != 0)
		{
			if (vehid == JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle])
			{
				PlayerPlaySound(playerid, 1147, 0.0, 0.0, 0.0);
				JobVehicle[AccountData[playerid][pJobVehicle]][Locked] = !(JobVehicle[AccountData[playerid][pJobVehicle]][Locked]);

				PlayerPlayNearbySound(playerid, SOUND_LOCK_CAR_DOOR);
				LockVehicle(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], JobVehicle[AccountData[playerid][pJobVehicle]][Locked]);
				ToggleVehicleLights(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle], JobVehicle[AccountData[playerid][pJobVehicle]][Locked]);
				GameTextForPlayer(playerid, sprintf("~w~%s %s", GetVehicleName(JobVehicle[AccountData[playerid][pJobVehicle]][Vehicle]), JobVehicle[AccountData[playerid][pJobVehicle]][Locked] ? ("~r~Locked") : ("~g~Unlocked")), 4000, 4);
			}
			return 1;
		}

		if(PlayerElectricJob[playerid][ElectricVehicle] == vehid)
		{
			PlayerPlaySound(playerid, 1147, 0.0, 0.0, 0.0);
			PlayerElectricJob[playerid][ElectricLocked] = !(PlayerElectricJob[playerid][ElectricLocked]);

			PlayerPlayNearbySound(playerid, SOUND_LOCK_CAR_DOOR);
			LockVehicle(PlayerElectricJob[playerid][ElectricVehicle], PlayerElectricJob[playerid][ElectricLocked]);
			ToggleVehicleLights(PlayerElectricJob[playerid][ElectricVehicle], PlayerElectricJob[playerid][ElectricLocked]);
			GameTextForPlayer(playerid, sprintf("~w~%s %s", GetVehicleName(PlayerElectricJob[playerid][ElectricVehicle]), PlayerElectricJob[playerid][ElectricLocked] ? ("~r~Locked") : ("~g~Unlocked")), 4000, 4);
			return 1;
		}
	}
	if(newkeys & KEY_CTRL_BACK)
	{
		if(IsPlayerInjured(playerid))
		{
		    SetPlayerInterior(playerid, 0);
		    SetPlayerVirtualWorld(playerid, 0);
		}
	}
	if(PRESSED(KEY_NO))
	{
		if(AccountData[playerid][pInjured])
		{
			if(SignalExists[playerid]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sudah mengirim signal, tunggu hingga EMS merespon!");
			
			GetPlayerPos(playerid, SignalPos[playerid][0], SignalPos[playerid][1], SignalPos[playerid][2]);
			SignalExists[playerid] = true;
			SignalTimer[playerid] = 120;
			
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil mengirim sinyal kepada EMS!");
			
			foreach(new i : Player)
			{
				if(AccountData[i][pSpawned] && AccountData[i][pFaction] == FACTION_EMS && AccountData[i][pDutyEms])
				{
					SendClientMessageEx(i, -1, ""RED"[Emergency Signal] "WHITE"Signal telah diterima dari daerah "YELLOW"%s", GetLocation(SignalPos[playerid][0], SignalPos[playerid][1], SignalPos[playerid][2]));
					Info(i, "Buka Smartphone ~> GPS ~> Signal Emergency (EMS) jika ingin merespon signal");
				}
			}
		}
	}
	if((newkeys & KEY_NO) && aOfferID[playerid] == INVALID_PLAYER_ID)
	{
		if (AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Tidak dapat membuka radial saat actvitity berjalan!");
		if (AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak ddapat melakukan ini ketika sedang pingsan!");
		
		ShowPlayerRadial1(playerid, true);
	}
	if(PRESSED(KEY_YES))
    {
        if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			if(pHiu[playerid])
			{
				RemovePlayerAttachedObject(playerid, 9);
				ClearAnimations(playerid);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				pHiu[playerid] = false;
				Inventory_Add(playerid, "Hiu", 1608, 1);
				Info(playerid, ""GRAY"Kamu memasukkan kembali Hiu ke dalam tas.");
			}
		}
    }
	//-----[ Toll System ]-----	
	if(newkeys & KEY_CROUCH)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new forcount = MuchNumber(sizeof(BarrierInfo));
			for(new i = 0; i < forcount; i++)
			{
				if(i < sizeof(BarrierInfo))
				{
					if(IsPlayerInRangeOfPoint(playerid, 8.0, BarrierInfo[i][brPos_X], BarrierInfo[i][brPos_Y], BarrierInfo[i][brPos_Z]))
					{
						if(!BarrierInfo[i][brOpen])
						{
							SetPVarInt(playerid, "NearBarrierID", i);
							for(new td = 0; td < 19; td++)
							{
								TextDrawShowForPlayer(playerid, OpenTollTD[td]);
								SelectTextDraw(playerid, COLOR_BLUE);
							}
						}
						break;
					}
				}
			}
		}
	}
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if((oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER) && AccountData[playerid][pTogAutoEngine])
	{
		if(!GetEngineStatus(vehicleid))
		{
			if(IsEngineVehicle(vehicleid) && !IsADealerVehicle(playerid, vehicleid))
			{
				AccountData[playerid][pTurningEngine] = true;
				SetTimerEx("EngineStatus", 2500, false, "id", playerid, vehicleid);
				SendRPMeAboveHead(playerid, "Mencoba menghidupkan mesin kendaraan", X11_PLUM1);
			}
		}
	}
	// if(newstate == PLAYER_STATE_PASSENGER)
	// {
	// 	if(IsABike(vehicleid)) //jika motor
	// 	{
	// 		if(IsEngineVehicle(vehicleid)) //motor mesin
	// 		{
	// 			new randhelmet = random(5);
	// 			switch(randhelmet)
	// 			{
	// 				case 0:
	// 				{
	// 					SetPlayerAttachedObject(playerid,0,18978,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
	// 				}
	// 				case 1:
	// 				{
	// 					SetPlayerAttachedObject(playerid,0,18977,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
	// 				}
	// 				case 2:
	// 				{
	// 					SetPlayerAttachedObject(playerid,0,18979,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
	// 				}
	// 				case 4:
	// 				{
	// 					SetPlayerAttachedObject(playerid,0,18645,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
	// 				}
	// 				default:
	// 				{
	// 					SetPlayerAttachedObject(playerid,0,18978,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
	// 				}
	// 			}
	// 		}
	// 		else //sepeda
	// 		{
	// 			SetPlayerAttachedObject(playerid,0,19102,2,0.15,0.00,0.00,0.0,0.0,0.0,1.14,1.10,1.11);
	// 		}
	// 		pHelmetin[playerid] = true;
	// 	}
	// }
	if(newstate == PLAYER_STATE_WASTED && AccountData[playerid][pJail] < 1)
    {	
		if(IsPlayerInEvent(playerid))
			return 1;

		SetPlayerArmedWeapon(playerid, 0);
		ResetPlayer(playerid);

		if(!AccountData[playerid][pInjured] && !IsPlayerInEvent(playerid))
		{
			AccountData[playerid][pInjured] = 1;
			AccountData[playerid][pInjuredTime] = 1800;
			
			AccountData[playerid][pInt] = GetPlayerInterior(playerid);
			AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);

			GetPlayerPos(playerid, AccountData[playerid][pPosX], AccountData[playerid][pPosY], AccountData[playerid][pPosZ]);
			GetPlayerFacingAngle(playerid, AccountData[playerid][pPosA]);
		}
	}
	//Spec Player
	if(newstate == PLAYER_STATE_ONFOOT)
	{
		if(AccountData[playerid][playerSpectated] != 0)
		{
			foreach(new ii : Player)
			{
				if(AccountData[ii][pSpec] == playerid)
				{
					PlayerSpectatePlayer(ii, playerid);
					SendClientMessageEx(ii, -1, ""YELLOW"SPEC:"WHITE" %s(%d) sekarang berjalan kaki.", AccountData[playerid][pName], playerid);
				}
			}
		}
	}
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
    {
		if(AccountData[playerid][pInjured] == 1)
        {
            //RemoveFromVehicle(playerid);
			RemovePlayerFromVehicle(playerid);
            SetPlayerHealthEx(playerid, 99999);
        }
		foreach (new ii : Player) if(AccountData[ii][pSpec] == playerid) 
		{
            PlayerSpectateVehicle(ii, GetPlayerVehicleID(playerid));
        }
		GangZoneHideForPlayer(playerid, GangZoneData[gzSafezone]);
	}
    
	new vehicle_index = -1;
	if((vehicle_index = Vehicle_ReturnID(vehicleid)) != RETURN_INVALID_VEHICLE_ID)
	{
		if((newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER) && PlayerVehicle[vehicle_index][vehAudio])
		{
			PlayVehicleAudio(playerid, vehicle_index);
		}
	}
	
	if((oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER) && AccountData[playerid][pVehAudioPlay])
	{
		StopAudioStreamForPlayer(playerid);
		AccountData[playerid][pVehAudioPlay] = 0;
	}
	if(oldstate == PLAYER_STATE_DRIVER)
    {	
		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CARRY || GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED)
            return RemovePlayerFromVehicle(playerid);/*RemoveFromVehicle(playerid);*/
		
		HideSpedo(playerid);
	}
	if(oldstate == PLAYER_STATE_PASSENGER)
	{
		//GangZoneShowForPlayer(playerid, GangZoneData[gzSafezone], 0xFFB6C1EE);
	}
	else if(newstate == PLAYER_STATE_DRIVER)
    {	
		static pviterid = -1;

		if((pviterid = Vehicle_Nearest2(playerid)) != -1)
		{
			if(IsABike(PlayerVehicle[pviterid][pVehPhysic]) || GetVehicleModel(PlayerVehicle[pviterid][pVehPhysic]) == 424)
			{
				if(PlayerVehicle[pviterid][pVehLocked])
				{
					RemovePlayerFromVehicle(playerid);
					ClearAnimations(playerid, 1);
					ShowTDN(playerid, NOTIFICATION_ERROR, "Kendaraan ini terkunci!");
					return 1;
				}
			}
		}
		if(!IsEngineVehicle(vehicleid))
        {
            SwitchVehicleEngine(vehicleid, true);
        }
		
		ShowSpedo(playerid);

		new Float:health;
        GetVehicleHealth(GetPlayerVehicleID(playerid), health);
        VehicleHealthSecurityData[GetPlayerVehicleID(playerid)] = health;
        VehicleHealthSecurity[GetPlayerVehicleID(playerid)] = true;
		
		if(AccountData[playerid][playerSpectated] != 0)
  		{
			foreach(new ii : Player)
			{
    			if(AccountData[ii][pSpec] == playerid)
			    {
        			PlayerSpectateVehicle(ii, vehicleid);
					SendClientMessageEx(ii, -1, ""YELLOW"SPEC:"WHITE" %s(%d) sekarang mengendarai %s(%d).", AccountData[playerid][pName], playerid, GetVehicleModelName(GetVehicleModel(vehicleid)), vehicleid);
				}
			}
		}
		SetPVarInt(playerid, "LastVehicleID", vehicleid);

		// if(IsABike(vehicleid)) //jika motor
		// {
		// 	if(IsEngineVehicle(vehicleid)) //motor mesin
		// 	{
		// 		new randhelmet = random(5);
		// 		switch(randhelmet)
		// 		{
		// 			case 0:
		// 			{
		// 				SetPlayerAttachedObject(playerid,0,18978,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
		// 			}
		// 			case 1:
		// 			{
		// 				SetPlayerAttachedObject(playerid,0,18977,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
		// 			}
		// 			case 2:
		// 			{
		// 				SetPlayerAttachedObject(playerid,0,18979,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
		// 			}
		// 			case 4:
		// 			{
		// 				SetPlayerAttachedObject(playerid,0,18645,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
		// 			}
		// 			default:
		// 			{
		// 				SetPlayerAttachedObject(playerid,0,18978,2,0.06,0.02,0.00,0.0,89.0,89.0,1.10,0.89,1.00);
		// 			}
		// 		}
		// 	}
		// 	else //sepeda
		// 	{
		// 		SetPlayerAttachedObject(playerid,0,19102,2,0.15,0.00,0.00,0.0,0.0,0.0,1.14,1.10,1.11);
		// 	}
		// 	pHelmetin[playerid] = true;
		// }
	}
	// if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT) //turun
	// {
	// 	if(pHelmetin[playerid])
	// 	{
	// 		RemovePlayerAttachedObject(playerid, 0);
	// 		pHelmetin[playerid] = false;
	// 	}
	// }
	// if(oldstate == PLAYER_STATE_PASSENGER && newstate == PLAYER_STATE_ONFOOT) //turun penumpang
	// {
	// 	if(pHelmetin[playerid])
	// 	{
	// 		RemovePlayerAttachedObject(playerid, 0);
	// 		pHelmetin[playerid] = false;
	// 	}
	// }
	return 1;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	switch(weaponid){ case 0..18, 39..54: return 1;} //invalid weapons
	if(1 <= weaponid <= 46 && AccountData[playerid][pGuns][g_aWeaponSlots[weaponid]] == weaponid)
	{
		AccountData[playerid][pAmmo][g_aWeaponSlots[weaponid]]--;
		if(AccountData[playerid][pGuns][g_aWeaponSlots[weaponid]] != 0 && !AccountData[playerid][pAmmo][g_aWeaponSlots[weaponid]])
		{
			AccountData[playerid][pGuns][g_aWeaponSlots[weaponid]] = 0;
		}
	}

	if(PlayerHasTazer(playerid) && AccountData[playerid][pFaction] == FACTION_POLISI)
	{
		SetPlayerArmedWeapon(playerid, 0);
		PlayerPlayNearbySound(playerid, 6003);
	}
	return 1;
}

stock GivePlayerHealth(playerid,Float:Health)
{
	new Float:health; GetPlayerHealth(playerid,health);
	SetPlayerHealth(playerid,health+Health);
}

/*public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	new
        Float: vehicleHealth,
        playerVehicleId = GetPlayerVehicleID(playerid);

    new Float:health = GetPlayerHealth(playerid, health);
    GetVehicleHealth(playerVehicleId, vehicleHealth);
    if(AccountData[playerid][pSeatBelt] == 0 || AccountData[playerid][pHelmetOn] == 0)
    {
    	if(GetVehicleSpeed(vehicleid) <= 20)
    	{
    		new asakit = RandomEx(0, 1);
    		new bsakit = RandomEx(0, 1);
    		new csakit = RandomEx(0, 1);
    		AccountData[playerid][pLFoot] -= csakit;
    		AccountData[playerid][pLHand] -= bsakit;
    		AccountData[playerid][pRFoot] -= csakit;
    		AccountData[playerid][pRHand] -= bsakit;
    		AccountData[playerid][pHead] -= asakit;
    		GivePlayerHealth(playerid, -1);
    		return 1;
    	}
    	if(GetVehicleSpeed(vehicleid) <= 50)
    	{
    		new asakit = RandomEx(0, 2);
    		new bsakit = RandomEx(0, 2);
    		new csakit = RandomEx(0, 2);
    		new dsakit = RandomEx(0, 2);
    		AccountData[playerid][pLFoot] -= dsakit;
    		AccountData[playerid][pLHand] -= bsakit;
    		AccountData[playerid][pRFoot] -= csakit;
    		AccountData[playerid][pRHand] -= dsakit;
    		AccountData[playerid][pHead] -= asakit;
    		GivePlayerHealth(playerid, -2);
    		return 1;
    	}
    	if(GetVehicleSpeed(vehicleid) <= 90)
    	{
    		new asakit = RandomEx(0, 3);
    		new bsakit = RandomEx(0, 3);
    		new csakit = RandomEx(0, 3);
    		new dsakit = RandomEx(0, 3);
    		AccountData[playerid][pLFoot] -= csakit;
    		AccountData[playerid][pLHand] -= csakit;
    		AccountData[playerid][pRFoot] -= dsakit;
    		AccountData[playerid][pRHand] -= bsakit;
    		AccountData[playerid][pHead] -= asakit;
    		GivePlayerHealth(playerid, -5);
    		return 1;
    	}
    	return 1;
    }
    if(AccountData[playerid][pSeatBelt] == 1 || AccountData[playerid][pHelmetOn] == 1)
    {
    	if(GetVehicleSpeed(vehicleid) <= 20)
    	{
    		new asakit = RandomEx(0, 1);
    		new bsakit = RandomEx(0, 1);
    		new csakit = RandomEx(0, 1);
    		AccountData[playerid][pLFoot] -= csakit;
    		AccountData[playerid][pLHand] -= bsakit;
    		AccountData[playerid][pRFoot] -= csakit;
    		AccountData[playerid][pRHand] -= bsakit;
    		AccountData[playerid][pHead] -= asakit;
    		GivePlayerHealth(playerid, -1);
    		return 1;
    	}
    	if(GetVehicleSpeed(vehicleid) <= 50)
    	{
    		new asakit = RandomEx(0, 1);
    		new bsakit = RandomEx(0, 1);
    		new csakit = RandomEx(0, 1);
    		new dsakit = RandomEx(0, 1);
    		AccountData[playerid][pLFoot] -= dsakit;
    		AccountData[playerid][pLHand] -= bsakit;
    		AccountData[playerid][pRFoot] -= csakit;
    		AccountData[playerid][pRHand] -= dsakit;
    		AccountData[playerid][pHead] -= asakit;
    		GivePlayerHealth(playerid, -1);
    		return 1;
    	}
    	if(GetVehicleSpeed(vehicleid) <= 90)
    	{
    		new asakit = RandomEx(0, 1);
    		new bsakit = RandomEx(0, 1);
    		new csakit = RandomEx(0, 1);
    		new dsakit = RandomEx(0, 1);
    		AccountData[playerid][pLFoot] -= csakit;
    		AccountData[playerid][pLHand] -= csakit;
    		AccountData[playerid][pRFoot] -= dsakit;
    		AccountData[playerid][pRHand] -= bsakit;
    		AccountData[playerid][pHead] -= asakit;
    		GivePlayerHealth(playerid, -3);
    		return 1;
    	}
    }
    return 1;
}*/

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	if(damagedid != INVALID_PLAYER_ID && weaponid == WEAPON_CHAINSAW) {
        TogglePlayerControllable(playerid, 0);
        SetPlayerArmedWeapon(playerid, 0);
        TogglePlayerControllable(playerid, 1);
        SetCameraBehindPlayer(playerid);

        SetPVarInt(playerid, "ChainsawWarning", GetPVarInt(playerid, "ChainsawWarning")+1);

        if(GetPVarInt(playerid, "ChainsawWarning") == 3) {
			SendClientMessageToAllEx(X11_RED, "[AntiCheat]:"YELLOW" %s(%d)"LIGHTGREY" telah ditendang dari server karena Abusing Chainsaw!", ReturnName(playerid), playerid);
            DeletePVar(playerid, "ChainsawWarning");
            KickEx(playerid);
        }
    }
	else if(damagedid != INVALID_PLAYER_ID)
	{
		AccountData[damagedid][pLastShot] = playerid;
		AccountData[damagedid][pShotTime] = gettime();
		if(AccountData[playerid][pFaction] == FACTION_POLISI && PlayerHasTazer(playerid) && !AccountData[damagedid][pStunned])
		{
			if(GetPlayerState(damagedid) != PLAYER_STATE_ONFOOT)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus keadaan onfoot untuk dilumpuhkan!");
			
			if(GetPlayerDistanceFromPlayer(playerid, damagedid) > 5.0)
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu harus lebih dekat untuk melumpuhkan pemain tersebut!");
			
			AccountData[damagedid][pStunned] = 10;
			TogglePlayerControllable(damagedid, 0);
			
			ApplyAnimation(damagedid, "CRACK", "crckdeth4", 4.0, 0, 0, 0, 1, 0, 1);
			ShowTDN(damagedid, NOTIFICATION_WARNING, "Kamu terkena stun gun / taser!");
		}
	}
	return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	if(!IsPlayerInEvent(playerid))
	{
		new sakit = RandomEx(1, 4);
		new asakit = RandomEx(1, 5);
		new bsakit = RandomEx(1, 7);
		new csakit = RandomEx(1, 4);
		if(issuerid != INVALID_PLAYER_ID && GetPlayerWeapon(issuerid) && bodypart == 9)
		{
			AccountData[playerid][pHead] -= 20;
		}
		if(issuerid != INVALID_PLAYER_ID && GetPlayerWeapon(issuerid) && bodypart == 3)
		{
			AccountData[playerid][pPerut] -= sakit;
		}
		if(issuerid != INVALID_PLAYER_ID && GetPlayerWeapon(issuerid) && bodypart == 6)
		{
			AccountData[playerid][pRHand] -= bsakit;
		}
		if(issuerid != INVALID_PLAYER_ID && GetPlayerWeapon(issuerid) && bodypart == 5)
		{
			AccountData[playerid][pLHand] -= asakit;
		}
		if(issuerid != INVALID_PLAYER_ID && GetPlayerWeapon(issuerid) && bodypart == 8)
		{
			AccountData[playerid][pRFoot] -= csakit;
		}
		if(issuerid != INVALID_PLAYER_ID && GetPlayerWeapon(issuerid) && bodypart == 7)
		{
			AccountData[playerid][pLFoot] -= bsakit;	
		}
	}
	if(issuerid != INVALID_PLAYER_ID && bodypart == 3 && weaponid >= 22 && weaponid <= 45)
	{
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		foreach(new i : Player) if (IsPlayerConnected(i)) if (SQL_IsCharacterLogged(i))
		{
			if(AccountData[i][pFaction] == FACTION_POLISI && AccountData[i][pDutyPD])
			{
				SendClientMessageEx(i, X11_ORANGE1, "[WAR ALERT]"WHITE" Terdeteksi penembakan di daerah %s. "RED"(ID: %d)", GetLocation(x, y, z), playerid);
				SendClientMessageEx(i, X11_ARWIN, "Gunakan "YELLOW"/suspect [id]"WHITE" untuk melacak penembakan");
			}
		}
	}
    return 1;
}

ptask Inspike_Timer[1000](playerid)
{
	if(!AccountData[playerid][pSpawned]) 
		return 0;

	static s_Keys, s_UpDown, s_LeftRight;
    GetPlayerKeys( playerid, s_Keys, s_UpDown, s_LeftRight );

    if ( AccountData[playerid][pFreeze] && ( s_Keys || s_UpDown || s_LeftRight ) )
        return 0;

	CheckPlayerInSpike(playerid);
    return 1;
}

task VehicleUpdate[30000]()
{
	foreach(new i: Vehicle)
	{
		if(gRaceVehicleAdm[i]) continue;

		if (IsEngineVehicle(i) && GetEngineStatus(i))
		{
			if (GetFuel(i) > 0)
			{
				VehicleCore[i][vCoreFuel] --;
				if (GetFuel(i) <= 0)
				{
					SwitchVehicleEngine(i, false);
					VehicleCore[i][vCoreFuel] = 0;
				}
			}
		}
	}
	return 1;
}

timer Vehicle_UpdatePosition[2000](vehicleid)
{
	new
		Float:x,
		Float:y,
		Float:z,
		Float:a
	;

	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, a);

	SetVehiclePos(vehicleid, x, y, z);
	SetVehicleZAngle(vehicleid, a);
	return 1;
}

public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{
	new vehicle_index; // Index = Vehicle id ingame, vehicleid = Index DB
    vehicle_index = Vehicle_ReturnID(vehicleid);
    if(vehicle_index != RETURN_INVALID_VEHICLE_ID)
    {
		new panels, doors, lights, tires;
		GetVehicleDamageStatus(PlayerVehicle[vehicle_index][pVehPhysic], panels, doors, lights, tires);
		if(PlayerVehicle[vehicle_index][pVehBodyUpgrade] == 3 && PlayerVehicle[vehicle_index][pVehBodyRepair] > 0)
		{
			panels = doors = lights = tires = 0;
            UpdateVehicleDamageStatus(PlayerVehicle[vehicle_index][pVehPhysic], panels, doors, lights, tires);
			PlayerVehicle[vehicle_index][pVehBodyRepair] -= 50.0;
		}
		else if(PlayerVehicle[vehicle_index][pVehBodyRepair] <= 0)
		{
			PlayerVehicle[vehicle_index][pVehBodyRepair] = 0;
		}
	}
	if(GetPlayerJob(playerid) == JOB_DRIVER_MIXERS){
		if(jobs::mixer[playerid][mixerSlump] > 0 && IsValidVehicle(vehicleid))
		{
			new rand = RandomEx(2,4);
			jobs::mixer[playerid][mixerSlump]-=rand;

			new Float: progressvalue; 
			progressvalue = jobs::mixer[playerid][mixerSlump]*61/100;
			PlayerTextDrawTextSize(playerid, jobs::PBMixer[playerid], progressvalue, 13.0);
			PlayerTextDrawShow(playerid, jobs::PBMixer[playerid]);
		}
	}
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	new Float: vhealth;

	AntiCheatGetVehicleHealth(vehicleid, vhealth);
	SetVehicleHealth(vehicleid, vhealth);
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	defer Vehicle_UpdatePosition(vehicleid);

	for (new vid = 1; vid < sizeof(JobVehicle); vid ++) if (JobVehicle[vid][Vehicle] != INVALID_VEHICLE_ID)
	{
		if (vehicleid == JobVehicle[vid][Vehicle])
		{
			foreach(new i : Player)
			{
				if (AccountData[i][pJobVehicle] == JobVehicle[vid][Vehicle])
				{
					if (AccountData[i][pJobVehicle] != 0)
					{
						DestroyJobVehicle(i);
						AccountData[i][pJobVehicle] = 0;
						break;
					}
				}
			}
		}
	}

	foreach(new i : PvtVehicles) if (vehicleid == PlayerVehicle[i][pVehPhysic] && IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
	{
		if (PlayerVehicle[i][pVehRental] == -1)
		{
			PlayerVehicle[i][pVehInsuranced] = true;
			
			foreach(new pid : Player) if(PlayerVehicle[i][pVehOwnerID] == AccountData[pid][pID])
			{
				Syntax(pid, "Kendaraan anda rusak dan sudah dikirimkan ke Asuransi!");
			}
			
			for (new slot = 0; slot < MAX_VEHICLE_OBJECT; slot ++) if (VehicleObjects[i][slot][vehObjectExists])
			{
				if (VehicleObjects[i][slot][vehObject] != INVALID_STREAMER_ID)
					DestroyDynamicObject(VehicleObjects[i][slot][vehObject]);
				
				VehicleObjects[i][slot][vehObject] = INVALID_STREAMER_ID;
			}

			if (IsValidVehicle(PlayerVehicle[i][pVehPhysic]))
				DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
			
			PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;
		}
		else
		{
			PlayerVehicle[i][pVehRental] = -1;
			PlayerVehicle[i][pVehRentTime] = 0;
			PlayerVehicle[i][pVehExists] = false;

			foreach(new pid : Player) if(PlayerVehicle[i][pVehOwnerID] == AccountData[pid][pID])
			{
				Info(pid, "Kendaaraanmu rental anda telah hancur. Anda dikenakan denda sebesar "GREEN"%s!", FormatMoney(PlayerVehicle[i][pVehPrice]/2));
				TakeMoney(pid, (PlayerVehicle[i][pVehPrice]/2));
			}

			if(IsValidVehicle(PlayerVehicle[i][pVehPhysic])) 
			{
				DestroyVehicle(PlayerVehicle[i][pVehPhysic]);
				PlayerVehicle[i][pVehPhysic] = INVALID_VEHICLE_ID;
			}

			new cQuery[200];
			mysql_format(g_SQL, cQuery, sizeof(cQuery), "DELETE FROM `player_vehicles` WHERE `id` = '%d'", PlayerVehicle[i][pVehID]);
			mysql_tquery(g_SQL, cQuery);

			Vehicle_ResetVariable(i);
			Iter_Remove(PvtVehicles, i);
		}
	}

	//ini untuk menghapus kendaraan yang dispawn oleh admin
	if(VehicleCore[vehicleid][vehAdmin])
	{
		DestroyVehicle(VehicleCore[vehicleid][vehAdminPhysic]);
		VehicleCore[vehicleid][vehAdminPhysic] = INVALID_VEHICLE_ID;
		VehicleCore[vehicleid][vehAdmin] = false;
	}
	return 1;
}

public OnVehicleSirenStateChange(playerid, vehicleid, newstate)
{
	if(newstate)
	{
		SwitchVehicleLight(vehicleid, true);
		vehicleid = GetPlayerVehicleID(playerid);
		
		foreach(new i : PvtVehicles)
		{
			if(vehicleid == PlayerVehicle[i][pVehPhysic])
			{
				if(PlayerVehicle[i][pVehFaction] != FACTION_POLISI && PlayerVehicle[i][pVehFaction] != FACTION_EMS) 
					return 0;

				gToggleELM[vehicleid] = true;
				gELMTimer[vehicleid] = SetTimerEx("ToggleELM", 80, true, "d", vehicleid);
			}
		}
	}
	else 
	{
		static panels, doors, lights, tires;

		gToggleELM[vehicleid] = false;
		KillTimer(gELMTimer[vehicleid]);

		GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
		UpdateVehicleDamageStatus(vehicleid, panels, doors, 0, tires);
	}
	return 1;
}

hook OnVehicleCreated(vehicleid)
{
	TrunkVehEntered[vehicleid] = INVALID_PLAYER_ID;
	return 1;
}

/*hook OnVehicleDestroyed(vehicleid)
{
	new index = -1;
    new playerid = GetVehicleDriver(vehicleid);
	if((index = Vehicle_GetID(vehicleid)) != -1)
	{
		if(PlayerVehicle[index][vehSirenOn])
		{
			PlayerVehicle[index][vehSirenOn] = false;
			if(IsValidDynamicObject(PlayerVehicle[index][vehSirenObject]))
			{
				DestroyDynamicObject(PlayerVehicle[index][vehSirenObject]);
				PlayerVehicle[index][vehSirenObject] = INVALID_STREAMER_ID;
			}
		}

		if(IsBagasiOpened[PlayerVehicle[index][pVehPhysic]])
		{
			IsBagasiOpened[PlayerVehicle[index][pVehPhysic]] = false;
		}

		if(TrunkVehEntered[PlayerVehicle[index][pVehPhysic]] != INVALID_PLAYER_ID)
		{
			new Float:x, Float:y, Float:z;
			GetVehicleBoot(vehicleid, x, y, z);
			PlayerSpectateVehicle(TrunkVehEntered[PlayerVehicle[index][pVehPhysic]], INVALID_VEHICLE_ID);

			SetSpawnInfo(TrunkVehEntered[PlayerVehicle[index][pVehPhysic]], 0, AccountData[TrunkVehEntered[PlayerVehicle[index][pVehPhysic]]][pSkin], x, y, z, 0.0, 0, 0, 0, 0, 0, 0);
			TogglePlayerSpectating(TrunkVehEntered[PlayerVehicle[index][pVehPhysic]], false);
			SetPVarInt(TrunkVehEntered[PlayerVehicle[index][pVehPhysic]], "PlayerInTrunk", 0);
			AccountData[TrunkVehEntered[PlayerVehicle[index][pVehPhysic]]][pTempVehID] = INVALID_VEHICLE_ID;
			TrunkVehEntered[PlayerVehicle[index][pVehPhysic]] = INVALID_PLAYER_ID;
		}

		for (new slot = 0; slot < MAX_VEHICLE_OBJECT; slot ++) if (VehicleObjects[index][slot][vehObjectExists])
		{
			if (VehicleObjects[index][slot][vehObject] != INVALID_STREAMER_ID)
				DestroyDynamicObject(VehicleObjects[index][slot][vehObject]);
			
			VehicleObjects[index][slot][vehObject] = INVALID_STREAMER_ID;
		}
		
		PlayerVehicle[index][pVehPhysic] = INVALID_VEHICLE_ID;
	}

	if(gToggleELM[vehicleid])
	{
		gToggleELM[vehicleid] = false;
		KillTimer(gELMTimer[vehicleid]);
	}
	if(jobs::mixer[playerid][mixerDuty][0] && IsValidVehicle(jobs::mixer[playerid][mixerVehicle]))
	{
		for(new i; i<3; i++)
        {
            TextDrawHideForPlayer(playerid, jobs::GBMixer[i]);
        }
        PlayerTextDrawHide(playerid, jobs::PBMixer[playerid]);
		jobs::mixer_reset_enum(playerid);
		ShowTDN(playerid, NOTIFICATION_WARNING, "Anda gagal mengirimkan beton karena kendaraan anda hancur!");
	}
	return 1;
}*/

hook OnVehicleDestroyed(vehicleid)
{
    if(vehicleid == INVALID_VEHICLE_ID || vehicleid >= MAX_VEHICLES) return 1;

    new index = Vehicle_GetID(vehicleid);
    if(index == -1) return 1;

    new playerid = GetVehicleDriver(vehicleid);
    if(playerid == INVALID_PLAYER_ID) playerid = -1;

    // --- Siren check
    if(PlayerVehicle[index][vehSirenOn])
    {
        PlayerVehicle[index][vehSirenOn] = false;
        if(IsValidDynamicObject(PlayerVehicle[index][vehSirenObject]))
        {
            DestroyDynamicObject(PlayerVehicle[index][vehSirenObject]);
            PlayerVehicle[index][vehSirenObject] = INVALID_STREAMER_ID;
        }
    }

    // --- Bagasi check (cek valid dulu)
    if(PlayerVehicle[index][pVehPhysic] != INVALID_VEHICLE_ID
        && IsBagasiOpened[PlayerVehicle[index][pVehPhysic]])
    {
        IsBagasiOpened[PlayerVehicle[index][pVehPhysic]] = false;
    }

    // --- Trunk check (cek valid dulu)
    if(PlayerVehicle[index][pVehPhysic] != INVALID_VEHICLE_ID
        && TrunkVehEntered[PlayerVehicle[index][pVehPhysic]] != INVALID_PLAYER_ID)
    {
        new trunkid = PlayerVehicle[index][pVehPhysic];
        new targetid = TrunkVehEntered[trunkid];

        new Float:x, Float:y, Float:z;
        GetVehicleBoot(vehicleid, x, y, z);

        PlayerSpectateVehicle(targetid, INVALID_VEHICLE_ID);
        SetSpawnInfo(targetid, 0, AccountData[targetid][pSkin], x, y, z, 0.0, 0,0,0,0,0,0);
        TogglePlayerSpectating(targetid, false);

        SetPVarInt(targetid, "PlayerInTrunk", 0);
        AccountData[targetid][pTempVehID] = INVALID_VEHICLE_ID;
        TrunkVehEntered[trunkid] = INVALID_PLAYER_ID;
    }

    // --- Vehicle objects cleanup
    for (new slot = 0; slot < MAX_VEHICLE_OBJECT; slot++)
    {
        if(VehicleObjects[index][slot][vehObjectExists])
        {
            if(IsValidDynamicObject(VehicleObjects[index][slot][vehObject]))
                DestroyDynamicObject(VehicleObjects[index][slot][vehObject]);
            
            VehicleObjects[index][slot][vehObject] = INVALID_STREAMER_ID;
            VehicleObjects[index][slot][vehObjectExists] = false;
        }
    }

    PlayerVehicle[index][pVehPhysic] = INVALID_VEHICLE_ID;

    // --- ELM
    if(vehicleid >= 0 && vehicleid < MAX_VEHICLES && gToggleELM[vehicleid])
    {
        gToggleELM[vehicleid] = false;
        KillTimer(gELMTimer[vehicleid]);
    }

    // --- Mixer job
    if(playerid != -1 && jobs::mixer[playerid][mixerDuty][0]
        && IsValidVehicle(jobs::mixer[playerid][mixerVehicle]))
    {
        for(new i; i<3; i++) TextDrawHideForPlayer(playerid, jobs::GBMixer[i]);
        PlayerTextDrawHide(playerid, jobs::PBMixer[playerid]);

        jobs::mixer_reset_enum(playerid);
        ShowTDN(playerid, NOTIFICATION_WARNING, "Anda gagal mengirimkan beton karena kendaraan anda hancur!");
    }
    return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	if(AccountData[playerid][pTogAutoEngine] && !IsABicycle(vehicleid))
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			if(GetEngineStatus(vehicleid)) 
			{
				AccountData[playerid][pTempVehID] = vehicleid;
				SetTimerEx("EngineTurnOff", 1500, false, "dd", playerid, vehicleid);
			}
		}
	}
	if( vehicleid == Drones[playerid] ) 
    {
	    SendClientMessage( playerid, COLOR_RED, "You can't exit the drone! Use /drone remove or /drone detonate." );
	}
	return 1;
}

forward EngineTurnOff(playerid, vehicleid);
public EngineTurnOff(playerid, vehicleid)
{
	if(AccountData[playerid][pTempVehID] == vehicleid)
	{
		SwitchVehicleEngine(vehicleid, false);
		SendRPMeAboveHead(playerid, "Mesin mati", X11_LIGHTGREEN);	
	
		AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
	}
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
   	if((AccountData[playerid][pAdmin] >= 1 || AccountData[playerid][pTheStars] >= 1) && AccountData[playerid][pAdminDuty] == 1)
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(vehicleid > 0 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            SetVehiclePos(vehicleid, fX, fY, fZ+10);
        }
        else
        {
            SetPlayerPosFindZ(playerid, fX, fY, 999.0);
            SetPlayerVirtualWorld(playerid, 0);
            SetPlayerInterior(playerid, 0);
        }
    }

	if(AccountData[playerid][pAdmin] >= 1 || AccountData[playerid][pTheStars] >= 1)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(vehicleid > 0 && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			SetPVarFloat(playerid, "tpX", fX);
			SetPVarFloat(playerid, "tpY", fY);
			SetPVarFloat(playerid, "tpZ", fZ + 5.0);
		}
		else 
		{
			SetPVarFloat(playerid, "tpX", fX);
			SetPVarFloat(playerid, "tpY", fY);
			SetPVarFloat(playerid, "tpZ", fZ);
		}
	}
    return 1;
}

Dialog:DOKUMENT_MENU(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
		return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
	}

	switch(listitem)
	{
		case 1: // lihat ktp
		{
			if(!AccountData[playerid][Ktp]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki KTP!");
			ShowKTPTD(playerid);
		}
		case 2: // Tunjukan KTP
		{
			if(!AccountData[playerid][Ktp]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki KTP!");
			foreach(new i : Player) if (IsPlayerConnected(i)) if (i != playerid)
			{
				if(IsPlayerNearPlayer(playerid, i, 3.0))
				{
					PlayerTextDrawSetPreviewModel(i, ktpTextdraws[i][29], AccountData[playerid][pSkin]);
                    PlayerTextDrawShow(i, ktpTextdraws[i][29]);
					ShowMyKTPTD(playerid, i);
				}
			}
		}
		case 3: // Lihat SIM
		{
			DisplayLicensi(playerid, playerid);
		}
		case 4: // Tunjukan SIM
		{
			foreach(new i : Player) if (IsPlayerConnected(i)) if (i != playerid)
			{
				if(IsPlayerNearPlayer(playerid, i, 3.0))
				{
					DisplayLicensi(i, playerid);
				}
			}
		}
		case 5: // Lihat SKWB
		{
			if (!AccountData[playerid][pSKWB]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SKWB!");

			DisplaySKWB(playerid, playerid);
		}
		case 6: // tunjukan SKWB
		{
			if(!AccountData[playerid][pSKWB]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SKWB!");
			
			foreach(new i : Player) if (IsPlayerConnected(i))
			{
				if(IsPlayerNearPlayer(playerid, i, 3.0))
				{
					DisplaySKWB(playerid, i);
				}
			}
		}

		case 8: //lihat bpjs
		{
			if(!AccountData[playerid][pBPJS]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki BPJS/Expired!");
			DisplayBPJS(playerid, playerid);
		}
		case 9: //tunjukan bpjs
		{
			if(!AccountData[playerid][pBPJS]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki BPJS/Expired!");
			foreach(new i : Player) if (IsPlayerConnected(i)) if (i != playerid)
			{   
				if(IsPlayerNearPlayer(playerid, i, 3.0))
				{
					DisplayBPJS(i, playerid);
				}
			}
		}
		case 10: //lihat skck
		{
			if(!AccountData[playerid][pSKCK]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SKCK/Expired!");
			DisplaySKCK(playerid, playerid);
		}
		case 11: //tunjuk skck
		{
			if(!AccountData[playerid][pSKCK]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki SKCK/Expired!");
			foreach(new i : Player) if (IsPlayerConnected(i)) if (i != playerid)
			{   
				if(IsPlayerNearPlayer(playerid, i, 3.0))
				{
					DisplaySKCK(i, playerid);
				}
			}
		}
		case 12: //lihat sks
		{
			if(!AccountData[playerid][pSKS]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Surat Keterangan Sehat/Expired!");
			DisplaySKS(playerid, playerid);
		}
		case 13: //tunjuk sks
		{
			if(!AccountData[playerid][pSKS]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Surat Keterangan Sehat/Expired!");
			foreach(new i : Player) if (IsPlayerConnected(i)) if (i != playerid)
			{   
				if(IsPlayerNearPlayer(playerid, i, 3.0))
				{
					DisplaySKS(i, playerid);
				}
			}
		}
	}
	return 1;
}

public OnClickDynamicTextDraw(playerid, Text:textid)
{
	//Jewelry Store
    if(textid == JewelryHackTD[7])
    {
        ShowPlayerDialog(playerid, JewelryHack_Input, DIALOG_STYLE_INPUT, "{32ff24}Command", "Masukkan Command:", "Terapkan", "Batal");
    }
	if(textid == JewelryHackTD[11])
	{
		ClearJewelryHackDisconnect(playerid);
		ClearAnimations(playerid, true);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
	}
    if(textid == JewelryHackTD[8])
    {
        if(JewelryHack_CommandChecked != false) return 1;

        for(new i = 0; i < 9; i++) 
        {
            if(i == 8) 
            {
                PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][i], "Command_Check...");
            }
            else if(i == 7)
            {
                PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][i], JewelryHack_Command);
            }
            else 
            {
                PlayerTextDrawSetString(playerid, JewelryHackPTD[playerid][i], "_");
            }
            PlayerTextDrawShow(playerid, JewelryHackPTD[playerid][i]);
        }

        JewelryHack_CommandChecked = true;
        SetTimerEx("StartHackJewelry", 5000, false, "i", playerid);
    }
	/* Clothes System */
	if (textid == ClothesHapp[54]) // next clothes male
	{
		if (BuyClothes[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pria!");

			if (CSelect[playerid] == sizeof(ClothesSkinMale) - 1)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else CSelect[playerid]++;

			SetPlayerSkin(playerid, ClothesSkinMale[CSelect[playerid]]);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", CSelect[playerid] + 1, sizeof(ClothesSkinMale));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][10], minsty);

			format(chess7, sizeof(chess7), "%d", CSelect[playerid] + 1, sizeof(ClothesSkinMale));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][0], chess7);
		}
	}
	if (textid == ClothesHapp[58]) // next topi male
	{
		if(BuyTopi[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pria!");

			if(SelectAcc[playerid] == sizeof(AksesorisHat) - 1)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] ++;

			SetPlayerAttachedObject(playerid, 9, AksesorisHat[SelectAcc[playerid]], 2, 0.269, 0.000, 0.000, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
				
			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisHat));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][12], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(AksesorisHat));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][2], chess7);
		}
	}
	if (textid == ClothesHapp[62]) // next GlassesToys male
	{
		if(BuyGlasses[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pria!");

			if(SelectAcc[playerid] == sizeof(GlassesToys) - 1)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] ++;

			SetPlayerAttachedObject(playerid, 9, GlassesToys[SelectAcc[playerid]], 2, 0.35, 0.24, -0.19, 0.0, 90.5, 86.0, 1.0, 1.0, 1.0);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(GlassesToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][14], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(GlassesToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][4], chess7);
		}
	}
	if (textid == ClothesHapp[66]) // next Aksesoris male
	{
		if(BuyTAksesoris[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pria!");

			if(SelectAcc[playerid] == sizeof(AksesorisToys) - 1)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] ++;

			SetPlayerAttachedObject(playerid, 9, AksesorisToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][16], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(AksesorisToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][6], chess7);
		}
	}
	if (textid == ClothesHapp[70]) // next Backpack male
	{
		if(BuyBackpack[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pria!");
			
			if(SelectAcc[playerid] == sizeof(BackpackToys) - 1)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] ++;

			SetPlayerAttachedObject(playerid, 9, BackpackToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(BackpackToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][8], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(BackpackToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][18], chess7);
		}
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
	}
	if (textid == ClothesHapp[53]) // Prev Cloth male
	{
		if (BuyClothes[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pria!");

			if (CSelect[playerid] == 0)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else CSelect[playerid]--;

			SetPlayerSkin(playerid, ClothesSkinMale[CSelect[playerid]]);
 
			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", CSelect[playerid] + 1, sizeof(ClothesSkinMale));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][10], minsty);

			format(chess7, sizeof(chess7), "%d", CSelect[playerid] + 1, sizeof(ClothesSkinMale));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][0], chess7);
		}
	}
	if (textid == ClothesHapp[57]) // Prev topi male
	{
		if(BuyTopi[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pria!");

			if(SelectAcc[playerid] == 0)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] --;

			SetPlayerAttachedObject(playerid, 9, AksesorisHat[SelectAcc[playerid]], 2, 0.269, 0.000, 0.000, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisHat));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][12], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(AksesorisHat));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][2], chess7);
		}
	}
	if (textid == ClothesHapp[61]) // Prev GlassesToys male
	{
		if(BuyGlasses[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pria!");

			if(SelectAcc[playerid] == 0)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] --;

			SetPlayerAttachedObject(playerid, 9, GlassesToys[SelectAcc[playerid]], 2, 0.35, 0.24, -0.19, 0.0, 90.5, 86.0, 1.0, 1.0, 1.0);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(GlassesToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][14], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(GlassesToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][4], chess7);
		}
	}
	if (textid == ClothesHapp[65]) // Prev Aksesoris male
	{
		if(BuyTAksesoris[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pria!");

			if(SelectAcc[playerid] == 0)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] --;

			SetPlayerAttachedObject(playerid, 9, AksesorisToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][16], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(AksesorisToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][6], chess7);
		}
	}
	if (textid == ClothesHapp[69]) // Prev Backpack male
	{
		if(BuyBackpack[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pria!");
			
			if(SelectAcc[playerid] == 0)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] --;

			SetPlayerAttachedObject(playerid, 9, BackpackToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(BackpackToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][18], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(BackpackToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][8], chess7);
		}
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
	}
	if (textid == ClothesHapp[56]) // next clothes Female
	{
		if (BuyClothes[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan wanita!");

			if (CSelect[playerid] == sizeof(ClothesSkinFemale) - 1)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else CSelect[playerid]++;

			SetPlayerSkin(playerid, ClothesSkinFemale[CSelect[playerid]]);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", CSelect[playerid] + 1, sizeof(ClothesSkinFemale));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][1], minsty);

			format(chess7, sizeof(chess7), "%d", CSelect[playerid] + 1, sizeof(ClothesSkinFemale));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][11], chess7);
		}
	}
	if (textid == ClothesHapp[60]) // next topi Female
	{
		if(BuyTopi[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan wanita!");

			if(SelectAcc[playerid] == sizeof(AksesorisHat) - 1)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] ++;

			SetPlayerAttachedObject(playerid, 9, AksesorisHat[SelectAcc[playerid]], 2, 0.269, 0.000, 0.000, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
				
			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisHat));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][13], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(AksesorisHat));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][3], chess7);
		}
	}
	if (textid == ClothesHapp[64]) // next GlassesToys Female
	{
		if(BuyGlasses[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan wanita!");

			if(SelectAcc[playerid] == sizeof(GlassesToys) - 1)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] ++;

			SetPlayerAttachedObject(playerid, 9, GlassesToys[SelectAcc[playerid]], 2, 0.35, 0.24, -0.19, 0.0, 90.5, 86.0, 1.0, 1.0, 1.0);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(GlassesToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][15], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(GlassesToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][5], chess7);
		}
	}
    if (textid == ClothesHapp[68]) // next Aksesoris Female
	{	
		if(BuyTAksesoris[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan wanita!");

			if(SelectAcc[playerid] == sizeof(AksesorisToys) - 1)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] ++;

			SetPlayerAttachedObject(playerid, 9, AksesorisToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][17], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(AksesorisToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][7], chess7);
		}
	}
    if (textid == ClothesHapp[72]) // next Backpack Female
	{
		if(BuyBackpack[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan wanita!");

			if(SelectAcc[playerid] == sizeof(BackpackToys) - 1)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] ++;

			SetPlayerAttachedObject(playerid, 9, BackpackToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(BackpackToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][19], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(BackpackToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][9], chess7);
		}
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
	}
	if (textid == ClothesHapp[55]) // Prev Cloth Female
	{
		if (BuyClothes[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan wanita!");

			if (CSelect[playerid] == 0)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else CSelect[playerid]--;

			SetPlayerSkin(playerid, ClothesSkinFemale[CSelect[playerid]]);
 
			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", CSelect[playerid] + 1, sizeof(ClothesSkinFemale));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][11], minsty);

			format(chess7, sizeof(chess7), "%d", CSelect[playerid] + 1, sizeof(ClothesSkinFemale));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][1], chess7);
		}
	}
	if (textid == ClothesHapp[59]) // Prev topi Female
	{
		if(BuyTopi[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan wanita!");

			if(SelectAcc[playerid] == 0)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] --;

			SetPlayerAttachedObject(playerid, 9, AksesorisHat[SelectAcc[playerid]], 2, 0.269, 0.000, 0.000, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisHat));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][13], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(AksesorisHat));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][3], chess7);
		}
	}
	if (textid == ClothesHapp[63]) // Prev GlassesToys Female
	{
		if(BuyGlasses[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan wanita!");

			if(SelectAcc[playerid] == 0)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] --;

			SetPlayerAttachedObject(playerid, 9, GlassesToys[SelectAcc[playerid]], 2, 0.35, 0.24, -0.19, 0.0, 90.5, 86.0, 1.0, 1.0, 1.0);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(GlassesToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][15], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(GlassesToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][5], chess7);
		}
	}
	if (textid == ClothesHapp[67]) // Prev Aksesoris Female
	{
		if(BuyTAksesoris[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan wanita!");

			if(SelectAcc[playerid] == 0)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] --;

			SetPlayerAttachedObject(playerid, 9, AksesorisToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][17], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(AksesorisToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][7], chess7);
		}
	}
	if (textid == ClothesHapp[71]) // Prev Backpack Female
	{
		if(BuyBackpack[playerid] == 1)
		{
			if (AccountData[playerid][pGender] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan wanita!");

			if(SelectAcc[playerid] == 0)
			{
				PlayerPlaySound(playerid, 4203, 0, 0, 0);
				return 0;
			}
			else SelectAcc[playerid] --;

			SetPlayerAttachedObject(playerid, 9, BackpackToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

			static minsty[128], chess7[128];
			format(minsty, sizeof(minsty), "%02d/%d", SelectAcc[playerid] + 1, sizeof(BackpackToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][19], minsty);

			format(chess7, sizeof(chess7), "%d", SelectAcc[playerid] + 1, sizeof(BackpackToys));
			PlayerTextDrawSetString(playerid, ClothesString[playerid][9], chess7);
		}
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
	}
	if (textid == ClothesHapp[43]) // Pakaian male
	{
		if(AccountData[playerid][pGender] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pria!");

		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerCameraPos(playerid, x, y + 2.5, z - 0.25);
	    SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.15);

		BuyClothes[playerid] = 1;
		BuyTopi[playerid] = 0;
		CSelect[playerid] = 0;
		SelectAcc[playerid] = 0;
		BuyGlasses[playerid] = 0;
		BuyTAksesoris[playerid] = 0;
		BuyBackpack[playerid] = 0;

		SetPlayerSkin(playerid, ClothesSkinMale[CSelect[playerid]]);

		static minsty[128];
		format(minsty, sizeof(minsty), "%02d/%d", CSelect[playerid] + 1, sizeof(ClothesSkinMale));
		PlayerTextDrawSetString(playerid, ClothesString[playerid][0], minsty);

		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		SelectTextDraw(playerid, COLOR_RED);
	}
	if (textid == ClothesHapp[44]) // Pakaian Female
	{
		if (AccountData[playerid][pGender] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan wanita!");

		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerCameraPos(playerid, x, y + 2.5, z - 0.25);
	    SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.15);

		BuyClothes[playerid] = 1;
		BuyTopi[playerid] = 0;
		BuyGlasses[playerid] = 0;
		BuyTAksesoris[playerid] = 0;
		BuyBackpack[playerid] = 0;
		CSelect[playerid] = 0;
		SelectAcc[playerid] = 0;

		SetPlayerSkin(playerid, ClothesSkinFemale[CSelect[playerid]]);

		static minsty[128];
		format(minsty, sizeof(minsty), "%02d/%d", CSelect[playerid] + 1, sizeof(ClothesSkinFemale));
		PlayerTextDrawSetString(playerid, ClothesString[playerid][10], minsty);

		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		SelectTextDraw(playerid, COLOR_RED);
	}
	if(textid == ClothesHapp[45]) // Topi Dan Helmet male
	{
		if(AccountData[playerid][pGender] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pria!");
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerCameraPos(playerid, x, y + 2.5, z - 0.25);
	    SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.15);

		BuyClothes[playerid] = 0;
		BuyTopi[playerid] = 1;
		BuyGlasses[playerid] = 0;
		BuyTAksesoris[playerid] = 0;
		BuyBackpack[playerid] = 0;
		SelectAcc[playerid] = 0;

		RemovePlayerAttachedObject(playerid, 0);
		SetPlayerAttachedObject(playerid, 9, AksesorisHat[SelectAcc[playerid]], 2, 0.356, 0.005, -0.004, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);

		static minsty[128];
		format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisHat));
		PlayerTextDrawSetString(playerid, ClothesString[playerid][12], minsty);

		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		SelectTextDraw(playerid, 0x72D172FF);
	}
	if(textid == ClothesHapp[46]) // Topi Dan Helmet Female
	{
		if (AccountData[playerid][pGender] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan wanita!");
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerCameraPos(playerid, x, y + 2.5, z - 0.25);
	    SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.15);

		BuyClothes[playerid] = 0;
		BuyTopi[playerid] = 1;
		BuyGlasses[playerid] = 0;
		BuyTAksesoris[playerid] = 0;
		BuyBackpack[playerid] = 0;
		SelectAcc[playerid] = 0;

		RemovePlayerAttachedObject(playerid, 0);
		SetPlayerAttachedObject(playerid, 9, AksesorisHat[SelectAcc[playerid]], 2, 0.356, 0.005, -0.004, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);

		static minsty[128];
		format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisHat));
		PlayerTextDrawSetString(playerid, ClothesString[playerid][13], minsty);

		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		SelectTextDraw(playerid, 0x72D172FF);
	}
	if(textid == ClothesHapp[47]) // Kacamata Toys male
	{
		if(AccountData[playerid][pGender] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pria!");
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerCameraPos(playerid, x, y + 2.5, z - 0.25);
	    SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.15);

		BuyClothes[playerid] = 0;
		BuyTopi[playerid] = 0;
		BuyGlasses[playerid] = 1;
		BuyTAksesoris[playerid] = 0;
		BuyBackpack[playerid] = 0;
		CSelect[playerid] = 0;
		SelectAcc[playerid] = 0;

		RemovePlayerAttachedObject(playerid, 1);
		SetPlayerAttachedObject(playerid, 9, GlassesToys[SelectAcc[playerid]], 2, 0.35, 0.24, -0.19, 0.0, 90.5, 86.0, 1.0, 1.0, 1.0);

		static minsty[128];
		format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(GlassesToys));
		PlayerTextDrawSetString(playerid, ClothesString[playerid][14], minsty);

		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		SelectTextDraw(playerid, COLOR_GREY);
	}
	if(textid == ClothesHapp[48]) // Kacamata Toys Female
	{
		if (AccountData[playerid][pGender] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan wanita!");
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerCameraPos(playerid, x, y + 2.5, z - 0.25);
	    SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.15);

		BuyClothes[playerid] = 0;
		BuyTopi[playerid] = 0;
		BuyGlasses[playerid] = 1;
		BuyTAksesoris[playerid] = 0;
		BuyBackpack[playerid] = 0;
		CSelect[playerid] = 0;
		SelectAcc[playerid] = 0;

		RemovePlayerAttachedObject(playerid, 1);
		SetPlayerAttachedObject(playerid, 9, GlassesToys[SelectAcc[playerid]], 2, 0.35, 0.24, -0.19, 0.0, 90.5, 86.0, 1.0, 1.0, 1.0);

		static minsty[128];
		format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(GlassesToys));
		PlayerTextDrawSetString(playerid, ClothesString[playerid][15], minsty);

		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		SelectTextDraw(playerid, COLOR_GREY);
	}
	if(textid == ClothesHapp[49]) // Aksesoris male
	{
		if(AccountData[playerid][pGender] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pria!");
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerCameraPos(playerid, x, y + 2.5, z - 0.25);
	    SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.15);
		
		BuyClothes[playerid] = 0;
		BuyTopi[playerid] = 0;
		BuyGlasses[playerid] = 0;
		BuyTAksesoris[playerid] = 1;
		BuyBackpack[playerid] = 0;
		CSelect[playerid] = 0;
		SelectAcc[playerid] = 0;

		RemovePlayerAttachedObject(playerid, 2);
		SetPlayerAttachedObject(playerid, 9, AksesorisToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

		static minsty[128];
		format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisToys));
		PlayerTextDrawSetString(playerid, ClothesString[playerid][16], minsty);

		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		SelectTextDraw(playerid, 0x72D172FF);
	}
	if(textid == ClothesHapp[50]) // Aksesoris Female
	{
		if (AccountData[playerid][pGender] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan wanita!");
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerCameraPos(playerid, x, y + 2.5, z - 0.25);
	    SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.15);
		
		BuyClothes[playerid] = 0;
		BuyTopi[playerid] = 0;
		BuyGlasses[playerid] = 0;
		BuyTAksesoris[playerid] = 1;
		BuyBackpack[playerid] = 0;
		CSelect[playerid] = 0;
		SelectAcc[playerid] = 0;

		RemovePlayerAttachedObject(playerid, 2);
		SetPlayerAttachedObject(playerid, 9, AksesorisToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

		static minsty[128];
		format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisToys));
		PlayerTextDrawSetString(playerid, ClothesString[playerid][17], minsty);

		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		SelectTextDraw(playerid, 0x72D172FF);
	}
	if(textid == ClothesHapp[51]) // Tas / Backpack male
	{
		if(AccountData[playerid][pGender] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan Pria!");
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerCameraPos(playerid, x, y + 2.5, z - 0.25);
	    SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.15);

		BuyClothes[playerid] = 0;
		BuyTopi[playerid] = 0;
		BuyGlasses[playerid] = 0;
		BuyTAksesoris[playerid] = 0;
		BuyBackpack[playerid] = 1;
		CSelect[playerid] = 0;
		SelectAcc[playerid] = 0;

		RemovePlayerAttachedObject(playerid, 3);
		SetPlayerAttachedObject(playerid, 9, BackpackToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

		static minsty[128];
		format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(BackpackToys));
		PlayerTextDrawSetString(playerid, ClothesString[playerid][18], minsty);

		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		SelectTextDraw(playerid, 0x72D172FF);
	}
	if(textid == ClothesHapp[52]) // Tas / Backpack Female
	{
		if (AccountData[playerid][pGender] != 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan wanita!");
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);
		SetPlayerCameraPos(playerid, x, y + 2.5, z - 0.25);
	    SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.15);

		BuyClothes[playerid] = 0;
		BuyTopi[playerid] = 0;
		BuyGlasses[playerid] = 0;
		BuyTAksesoris[playerid] = 0;
		BuyBackpack[playerid] = 1;
		CSelect[playerid] = 0;
		SelectAcc[playerid] = 0;

		RemovePlayerAttachedObject(playerid, 3);
		SetPlayerAttachedObject(playerid, 9, BackpackToys[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

		static minsty[128];
		format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(BackpackToys));
		PlayerTextDrawSetString(playerid, ClothesString[playerid][19], minsty);

		PlayerPlaySound(playerid, 1053, 0, 0, 0);
		SelectTextDraw(playerid, 0x72D172FF);
	}
	if(textid == ClothesHapp[75]) // Tombol Close
	{
		for(new txd = 0; txd < 84; txd++)
		{
			TextDrawHideForPlayer(playerid, ClothesHapp[txd]);
		}

		for(new i = 0; i < 20; i++)
		{
			PlayerTextDrawHide(playerid, ClothesString[playerid][i]);
		}

		TogglePlayerControllable(playerid, 1);
		CancelSelectTextDraw(playerid);
		SetCameraBehindPlayer(playerid);

		if(AccountData[playerid][pUsingUniform])
		{
			SetPlayerSkin(playerid, AccountData[playerid][pUniform]);
		}
		else 
		{
			SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
		}

		BuyClothes[playerid] = 0;
		BuyTopi[playerid] = 0;
		BuyGlasses[playerid] = 0;
		BuyTAksesoris[playerid] = 0;
		BuyBackpack[playerid] = 0;
		CSelect[playerid] = 0;
		SelectAcc[playerid] = 0;

		RemovePlayerAttachedObject(playerid, 9);

		AttachPlayerToys(playerid);
		AttachPlayerToysaxp(playerid);
		AttachPlayerToysDragon(playerid);
		AttachPlayerToysSonic(playerid);
		AttachPlayerToysGrinch(playerid);
		AttachPlayerToysGhost(playerid);
	}
	if (textid == ClothesHapp[73]) // Kamera Zoom
	{
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);

		CamZoomLevel[playerid]++;
		if (CamZoomLevel[playerid] > 2) CamZoomLevel[playerid] = 0;

		switch (CamZoomLevel[playerid])
		{
			case 0: // Zoom normal
			{
				SetPlayerCameraPos(playerid, x, y + 2.5, z - 0.25);
				SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.15);
			}
			case 1: // Zoom agak jauh
			{
				SetPlayerCameraPos(playerid, x, y + 3.5, z + 0.0); 
				SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.15);
			}
			case 2: // Zoom jauh
			{
				SetPlayerCameraPos(playerid, x, y + 4.5, z + 0.3); 
				SetPlayerCameraLookAt(playerid, x, y - 1.0, z + 0.15);
			}
		}
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
	}
	if(textid == ClothesHapp[74]) // Beli Clothes
	{
		if(BuyClothes[playerid] == 1)
		{
			new price = 200;

			if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang tidak cukup! (Price: $200)");
			TakeMoney(playerid, price);
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda membeli baju seharga ~g~$200");
			
			AccountData[playerid][pSkin] = GetPlayerSkin(playerid);
			for(new txd; txd < 84; txd ++)
			{
				TextDrawHideForPlayer(playerid, ClothesHapp[txd]);
			}
			for(new i = 0; i < 20; i++)
			{
				PlayerTextDrawHide(playerid, ClothesString[playerid][i]);
			}
			BuyClothes[playerid] = 0;
			SetPlayerSkin(playerid, AccountData[playerid][pSkin]);
			CancelSelectTextDraw(playerid);
			SetCameraBehindPlayer(playerid);
			TogglePlayerControllable(playerid, 1);
		}

		if(BuyTopi[playerid] == 1)
		{
			AccountData[playerid][toySelected] = 0;

			new price = 80;
			if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang kamu tidak cukup! (Price: $80)");
			TakeMoney(playerid, price);
			pToys[playerid][AccountData[playerid][toySelected]][toy_model] = AksesorisHat[SelectAcc[playerid]];
			pToys[playerid][AccountData[playerid][toySelected]][toy_status] = 1;
			pToys[playerid][AccountData[playerid][toySelected]][toy_x] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_y] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_z] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz] = 1.0;
			
			ShowPlayerDialog(playerid, DIALOG_TOYPOSISIBUY, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Ubah Tulang(Bone)", 
			"Spine\
			\n"GRAY"Head\
			\nLeft Upper Arm\
			\n"GRAY"Right Upper Arm\
			\nLeft Hand\
			\n"GRAY"Right Hand\
			\nLeft Thigh\
			\n"GRAY"Right Thigh\
			\nLeft Foot\
			\n"GRAY"Right Foot\
			\nRight Calf\
			\n"GRAY"Left Calf\
			\nLeft Forearm\
			\n"GRAY"Right Forearm\
			\nLeft Clavicle\
			\n"GRAY"Right Clavicle\
			\nNeck\
			\n"GRAY"Jaw", "Select", "Cancel");

			SetCameraBehindPlayer(playerid);
			TogglePlayerControllable(playerid, 1);
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda membeli Topi seharga ~g~$80");
			for(new txd; txd < 84; txd ++)
			{
				TextDrawHideForPlayer(playerid, ClothesHapp[txd]);
			}
			for(new i = 0; i < 20; i++)
			{
				PlayerTextDrawHide(playerid, ClothesString[playerid][i]);
			}
			BuyTopi[playerid] = 0;
			RemovePlayerAttachedObject(playerid, 9);
			CancelSelectTextDraw(playerid);
		}

		if(BuyGlasses[playerid] == 1)
		{
			AccountData[playerid][toySelected] = 1;

			new price = 50;
			if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang kamu tidak cukup! (Price: $50)");
			TakeMoney(playerid, price);
			pToys[playerid][AccountData[playerid][toySelected]][toy_model] = GlassesToys[SelectAcc[playerid]];
			pToys[playerid][AccountData[playerid][toySelected]][toy_status] = 1;
			pToys[playerid][AccountData[playerid][toySelected]][toy_x] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_y] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_z] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz] = 1.0;
			
			ShowPlayerDialog(playerid, DIALOG_TOYPOSISIBUY, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Ubah Tulang(Bone)", 
			"Spine\
			\n"GRAY"Head\
			\nLeft Upper Arm\
			\n"GRAY"Right Upper Arm\
			\nLeft Hand\
			\n"GRAY"Right Hand\
			\nLeft Thigh\
			\n"GRAY"Right Thigh\
			\nLeft Foot\
			\n"GRAY"Right Foot\
			\nRight Calf\
			\n"GRAY"Left Calf\
			\nLeft Forearm\
			\n"GRAY"Right Forearm\
			\nLeft Clavicle\
			\n"GRAY"Right Clavicle\
			\nNeck\
			\n"GRAY"Jaw", "Select", "Cancel");

			SetCameraBehindPlayer(playerid);
			TogglePlayerControllable(playerid, 1);
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda membeli Kacamata seharga ~g~$50");
			for(new txd; txd < 84; txd ++)
			{
				TextDrawHideForPlayer(playerid, ClothesHapp[txd]);
			}
			for(new i = 0; i < 20; i++)
			{
				PlayerTextDrawHide(playerid, ClothesString[playerid][i]);
			}
			BuyGlasses[playerid] = 0;
			RemovePlayerAttachedObject(playerid, 9);
			CancelSelectTextDraw(playerid);
		}

		if(BuyTAksesoris[playerid] == 1)
		{
			AccountData[playerid][toySelected] = 2;

			new price = 100;
			if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang kamu tidak cukup! (Price: $100)");
			TakeMoney(playerid, price);
			pToys[playerid][AccountData[playerid][toySelected]][toy_model] = AksesorisToys[SelectAcc[playerid]];
			pToys[playerid][AccountData[playerid][toySelected]][toy_status] = 1;
			pToys[playerid][AccountData[playerid][toySelected]][toy_x] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_y] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_z] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz] = 1.0;
			
			ShowPlayerDialog(playerid, DIALOG_TOYPOSISIBUY, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Ubah Tulang(Bone)", 
			"Spine\
			\n"GRAY"Head\
			\nLeft Upper Arm\
			\n"GRAY"Right Upper Arm\
			\nLeft Hand\
			\n"GRAY"Right Hand\
			\nLeft Thigh\
			\n"GRAY"Right Thigh\
			\nLeft Foot\
			\n"GRAY"Right Foot\
			\nRight Calf\
			\n"GRAY"Left Calf\
			\nLeft Forearm\
			\n"GRAY"Right Forearm\
			\nLeft Clavicle\
			\n"GRAY"Right Clavicle\
			\nNeck\
			\n"GRAY"Jaw", "Select", "Cancel");

			SetCameraBehindPlayer(playerid);
			TogglePlayerControllable(playerid, 1);
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda membeli Aksesoris seharga ~g~$100");
			for(new txd; txd < 84; txd ++)
			{
				TextDrawHideForPlayer(playerid, ClothesHapp[txd]);
			}
			for(new i = 0; i < 20; i++)
			{
				PlayerTextDrawHide(playerid, ClothesString[playerid][i]);
			}
			BuyTAksesoris[playerid] = 0;
			RemovePlayerAttachedObject(playerid, 9);
			CancelSelectTextDraw(playerid);
		}

		if(BuyBackpack[playerid] == 1)
		{
			AccountData[playerid][toySelected] = 3;

			new price = 100;
			if(AccountData[playerid][pMoney] < price) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang kamu tidak cukup! (Price: 100)");
			TakeMoney(playerid, price);
			pToys[playerid][AccountData[playerid][toySelected]][toy_model] = BackpackToys[SelectAcc[playerid]];
			pToys[playerid][AccountData[playerid][toySelected]][toy_status] = 1;
			pToys[playerid][AccountData[playerid][toySelected]][toy_x] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_y] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_z] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz] = 0.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy] = 1.0;
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz] = 1.0;
			
			ShowPlayerDialog(playerid, DIALOG_TOYPOSISIBUY, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Ubah Tulang(Bone)", 
			"Spine\
			\n"GRAY"Head\
			\nLeft Upper Arm\
			\n"GRAY"Right Upper Arm\
			\nLeft Hand\
			\n"GRAY"Right Hand\
			\nLeft Thigh\
			\n"GRAY"Right Thigh\
			\nLeft Foot\
			\n"GRAY"Right Foot\
			\nRight Calf\
			\n"GRAY"Left Calf\
			\nLeft Forearm\
			\n"GRAY"Right Forearm\
			\nLeft Clavicle\
			\n"GRAY"Right Clavicle\
			\nNeck\
			\n"GRAY"Jaw", "Select", "Cancel");

			SetCameraBehindPlayer(playerid);
			TogglePlayerControllable(playerid, 1);
			ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda membeli Tas seharga ~g~$100");
			for(new txd; txd < 84; txd ++)
			{
				TextDrawHideForPlayer(playerid, ClothesHapp[txd]);
			}
			for(new i = 0; i < 20; i++)
			{
				PlayerTextDrawHide(playerid, ClothesString[playerid][i]);
			}
			BuyBackpack[playerid] = 0;
			RemovePlayerAttachedObject(playerid, 9);
			CancelSelectTextDraw(playerid);
		}
		PlayerPlaySound(playerid, 1053, 0, 0, 0);
	}
	if(textid == OpenTollTD[16])
	{
		for(new i = 0; i < 22; i++)
		{
			TextDrawShowForPlayer(playerid, OpenTollTD[i]);
			SelectTextDraw(playerid, COLOR_BLUE);
		}
		StopAudioStreamForPlayer(playerid);
		TextDrawSetString(OpenTollTD[20], "HARAP TUNGGU");
		TextDrawShowForPlayer(playerid, OpenTollTD[20]);
		TextDrawHideForPlayer(playerid, OpenTollTD[21]);
		SetTimerEx("TollTD", 500, false, "d", playerid);
	}
	return 1;
}

public OnClickDynamicPlayerTextDraw(playerid, PlayerText: textid)
{
	new showroomID = GetPVarInt(playerid, "SelectShowroomID");
    if(textid == DistrictDealer[playerid][28]) // Next Veh
    {
        if(showroomID != 0)
        {
            if(showroomID == 1) // Truk
            {
                if(SelectVeh[playerid] == sizeof(TrukShowroom) - 1)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] ++;
                VehicleTruckSelect(playerid);

                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][25], sprintf("%s~n~", GetVehicleModelName(TrukShowroom[SelectVeh[playerid]])));
                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][26], sprintf("%s~g~", FormatMoney(TrukCost(playerid))));
            }
            else if(showroomID == 2) // Suv
            {
                if(SelectVeh[playerid] == sizeof(SuvShowroom) - 1)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] ++;
                VehicleSuvSelect(playerid);

                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][25], sprintf("%s~n~", GetVehicleModelName(SuvShowroom[SelectVeh[playerid]])));
                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][26], sprintf("%s~g~", FormatMoney(SuvCost(playerid))));
            }
            else if(showroomID == 3) // Motor
            {
                if(SelectVeh[playerid] == sizeof(MotorShowroom) - 1)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] ++;
                VehicleMotorSelect(playerid);

                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][25], sprintf("%s~n~", GetVehicleModelName(MotorShowroom[SelectVeh[playerid]])));
                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][26], sprintf("%s~g~", FormatMoney(MotorCost(playerid))));
            }
            else if(showroomID == 4) // Low ride
            {
                if(SelectVeh[playerid] == sizeof(ClassicShowroom) - 1)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] ++;
                VehicleLowriderSelect(playerid);

                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][25], sprintf("%s~n~", GetVehicleModelName(ClassicShowroom[SelectVeh[playerid]])));
                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][26], sprintf("%s~g~", FormatMoney(ClassicCost(playerid))));
            }
            else if(showroomID == 5) // Compact
            {
                if(SelectVeh[playerid] == sizeof(CompactShowroom) - 1)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] ++;
                VehicleCompactSelect(playerid);

                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][25], sprintf("%s~n~", GetVehicleModelName(CompactShowroom[SelectVeh[playerid]])));
                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][26], sprintf("%s~g~", FormatMoney(CompactCost(playerid))));
            }
            else if(showroomID == 6) // Luxury
            {
                if(SelectVeh[playerid] == sizeof(LuxuryShowroom) - 1)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] ++;
                VehicleLuxurySelect(playerid);

                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][25], sprintf("%s~n~", GetVehicleModelName(LuxuryShowroom[SelectVeh[playerid]])));
                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][26], sprintf("%s~g~", FormatMoney(LuxuryCost(playerid))));
            }
        }
    }
    else if(textid == DistrictDealer[playerid][27]) // Previous veh
    {
        if(showroomID != 0)
        {
            if(showroomID == 1) // truk
            {
                if(SelectVeh[playerid] == 0)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] --;
                VehicleTruckSelect(playerid);

                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][25], sprintf("%s~n~", GetVehicleModelName(TrukShowroom[SelectVeh[playerid]])));
                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][26], sprintf("%s~g~", FormatMoney(TrukCost(playerid))));
            }
            else if(showroomID == 2) // Suv
            {
                if(SelectVeh[playerid] == 0)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] --;
                VehicleSuvSelect(playerid);

                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][25], sprintf("%s~n~", GetVehicleModelName(SuvShowroom[SelectVeh[playerid]])));
                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][26], sprintf("%s~g~", FormatMoney(SuvCost(playerid))));
            }
            else if(showroomID == 3) // Motor
            {
                if(SelectVeh[playerid] == 0)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] --;
                VehicleMotorSelect(playerid);

                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][25], sprintf("%s~n~", GetVehicleModelName(MotorShowroom[SelectVeh[playerid]])));
                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][26], sprintf("%s~g~", FormatMoney(MotorCost(playerid))));
            }
            else if(showroomID == 4) // Lowrider
            {
                if(SelectVeh[playerid] == 0)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] --;
                VehicleLowriderSelect(playerid);

                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][25], sprintf("%s~n~", GetVehicleModelName(ClassicShowroom[SelectVeh[playerid]])));
                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][26], sprintf("%s~g~", FormatMoney(ClassicCost(playerid))));
            }
            else if(showroomID == 5) // Compact
            {
                if(SelectVeh[playerid] == 0)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] --;
                VehicleCompactSelect(playerid);

                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][25], sprintf("%s~n~", GetVehicleModelName(CompactShowroom[SelectVeh[playerid]])));
                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][26], sprintf("%s~g~", FormatMoney(CompactCost(playerid))));
            }
            else if(showroomID == 6) // Luxury
            {
                if(SelectVeh[playerid] == 0)
                {
                    PlayerPlaySound(playerid, 4203, 0.0, 0.0, 0.0);
                    return 0;
                }
                else SelectVeh[playerid] --;
                VehicleLuxurySelect(playerid);

                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][25], sprintf("%s~n~", GetVehicleModelName(LuxuryShowroom[SelectVeh[playerid]])));
                PlayerTextDrawSetString(playerid, DistrictDealer[playerid][26], sprintf("%s~g~", FormatMoney(LuxuryCost(playerid))));
            }
        }
    }
   	else if(textid == DistrictDealer[playerid][24]) // Keluar Showroom
    {
        EnableAntiCheatForPlayer(playerid, 4, true);
        DestroyVehicle(ShowroomVeh[playerid]);
        ShowroomVeh[playerid] = INVALID_VEHICLE_ID;


		SetPVarInt(playerid, "SelectShowroomID", 0);
        SelectVeh[playerid] = 0;
        CancelSelectTextDraw(playerid);
        Toggle_ShowroomTD(playerid, false);
        SetPlayerPositionEx(playerid, 1042.3744, 234.2350, 15.5392, 265.1649, 1500);
        SetPlayerVirtualWorld(playerid, DoorData[AccountData[playerid][pInDoor]][dIntvw]);
        SetCameraBehindPlayer(playerid);
		pWarna1[playerid] = 0;
        pWarna2[playerid] = 0;
    }
    else if(textid == DistrictDealer[playerid][23]) // Buy
    {
        if(showroomID != 0)
        {
            if(showroomID == 1) // Truk
            {
                new count = 0, modelid = TrukShowroom[SelectVeh[playerid]], cost = TrukCost(playerid);
                if(modelid <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Model ID Kendaraan tidak valid!");
                if(AccountData[playerid][pMoney] < cost) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                foreach(new iter : PvtVehicles) if (PlayerVehicle[iter][pVehExists])
                {
                    if(PlayerVehicle[iter][pVehOwnerID] == AccountData[playerid][pID])
                    {
                        count ++;
                    }
                }

                if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Slot kendaraan anda sudah penuh!");
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan.");
                TakeMoney(playerid, cost);
                ShowroomVehicle_Create(playerid, modelid, 520.8042, -1290.4095, 16.9476, 278.6836, pWarna1[playerid], pWarna2[playerid], cost);
                static shstr[128];
                format(shstr, sizeof(shstr), "Membeli kendaraan %s seharga %s", GetVehicleModelName(modelid), FormatMoney(cost));
                AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, cost);
                
                Toggle_ShowroomTD(playerid, false);
                SetPVarInt(playerid, "SelectShowroomID", 0);
                SelectVeh[playerid] = 0;
            }
            else if(showroomID == 2) // Suv
            {
                new count = 0, modelid = SuvShowroom[SelectVeh[playerid]], cost = SuvCost(playerid);
                if(modelid <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Model ID Kendaraan tidak valid!");
                if(AccountData[playerid][pMoney] < cost) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                foreach(new iter : PvtVehicles) if (PlayerVehicle[iter][pVehExists])
                {
                    if(PlayerVehicle[iter][pVehOwnerID] == AccountData[playerid][pID])
                    {
                        count ++;
                    }
                }

                if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Slot kendaraan anda sudah penuh!");
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan.");
                TakeMoney(playerid, cost);
                ShowroomVehicle_Create(playerid, modelid, 520.8042, -1290.4095, 16.9476, 278.6836, pWarna1[playerid], pWarna2[playerid], cost);
                static shstr[128];
                format(shstr, sizeof(shstr), "Membeli kendaraan %s seharga %s", GetVehicleModelName(modelid), FormatMoney(cost));
                AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, cost);
                
                Toggle_ShowroomTD(playerid, false);
                SetPVarInt(playerid, "SelectShowroomID", 0);
                SelectVeh[playerid] = 0;
            }
            else if(showroomID == 3) // Motor
            {
                new count = 0, modelid = MotorShowroom[SelectVeh[playerid]], cost = MotorCost(playerid);
                if(modelid <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Model ID Kendaraan tidak valid!");
                if(AccountData[playerid][pMoney] < cost) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                foreach(new iter : PvtVehicles) if (PlayerVehicle[iter][pVehExists])
                {
                    if(PlayerVehicle[iter][pVehOwnerID] == AccountData[playerid][pID])
                    {
                        count ++;
                    }
                }

                if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Slot kendaraan anda sudah penuh!");
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan.");
                TakeMoney(playerid, cost);
                ShowroomVehicle_Create(playerid, modelid, 520.8042, -1290.4095, 16.9476, 278.6836, pWarna1[playerid], pWarna2[playerid], cost);
                static shstr[128];
                format(shstr, sizeof(shstr), "Membeli kendaraan %s seharga %s", GetVehicleModelName(modelid), FormatMoney(cost));
                AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, cost);
                
                Toggle_ShowroomTD(playerid, false);
                SetPVarInt(playerid, "SelectShowroomID", 0);
                SelectVeh[playerid] = 0;
            }
            else if(showroomID == 4) // Low
            {
                new count = 0, modelid = ClassicShowroom[SelectVeh[playerid]], cost = ClassicCost(playerid);
                if(modelid <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Model ID Kendaraan tidak valid!");
                if(AccountData[playerid][pMoney] < cost) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                foreach(new iter : PvtVehicles) if (PlayerVehicle[iter][pVehExists])
                {
                    if(PlayerVehicle[iter][pVehOwnerID] == AccountData[playerid][pID])
                    {
                        count ++;
                    }
                }

                if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Slot kendaraan anda sudah penuh!");
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan.");
                TakeMoney(playerid, cost);
                ShowroomVehicle_Create(playerid, modelid, 520.8042, -1290.4095, 16.9476, 278.6836, pWarna1[playerid], pWarna2[playerid], cost);
                static shstr[128];
                format(shstr, sizeof(shstr), "Membeli kendaraan %s seharga %s", GetVehicleModelName(modelid), FormatMoney(cost));
                AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, cost);
                
                Toggle_ShowroomTD(playerid, false);
                SetPVarInt(playerid, "SelectShowroomID", 0);
                SelectVeh[playerid] = 0;
            }
            else if(showroomID == 5) // Compact
            {
                new count = 0, modelid = CompactShowroom[SelectVeh[playerid]], cost = CompactCost(playerid);
                if(modelid <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Model ID Kendaraan tidak valid!");
                if(AccountData[playerid][pMoney] < cost) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                foreach(new iter : PvtVehicles) if (PlayerVehicle[iter][pVehExists])
                {
                    if(PlayerVehicle[iter][pVehOwnerID] == AccountData[playerid][pID])
                    {
                        count ++;
                    }
                }

                if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Slot kendaraan anda sudah penuh!");
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan.");
                TakeMoney(playerid, cost);
                ShowroomVehicle_Create(playerid, modelid, 520.8042, -1290.4095, 16.9476, 278.6836, pWarna1[playerid], pWarna2[playerid], cost);
                static shstr[128];
                format(shstr, sizeof(shstr), "Membeli kendaraan %s seharga %s", GetVehicleModelName(modelid), FormatMoney(cost));
                AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, cost);
                
                Toggle_ShowroomTD(playerid, false);
                SetPVarInt(playerid, "SelectShowroomID", 0);
                SelectVeh[playerid] = 0;
            }
            else if(showroomID == 6) // Luxury
            {
                new count = 0, modelid = LuxuryShowroom[SelectVeh[playerid]], cost = LuxuryCost(playerid);
                if(modelid <= 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Model ID Kendaraan tidak valid!");
                if(AccountData[playerid][pMoney] < cost) return ShowTDN(playerid, NOTIFICATION_ERROR, "Uang anda tidak mencukupi!");
                foreach(new iter : PvtVehicles) if (PlayerVehicle[iter][pVehExists])
                {
                    if(PlayerVehicle[iter][pVehOwnerID] == AccountData[playerid][pID])
                    {
                        count ++;
                    }
                }

                if(count >= GetPlayerVehicleLimit(playerid)) return ShowTDN(playerid, NOTIFICATION_WARNING, "Slot kendaraan anda sudah penuh!");
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Pembelian berhasil dilakukan.");
                TakeMoney(playerid, cost);
                ShowroomVehicle_Create(playerid, modelid, 520.8042, -1290.4095, 16.9476, 278.6836, pWarna1[playerid], pWarna2[playerid], cost);
                static shstr[128];
                format(shstr, sizeof(shstr), "Membeli kendaraan %s seharga %s", GetVehicleModelName(modelid), FormatMoney(cost));
                AddPMoneyLog(AccountData[playerid][pName], AccountData[playerid][pUCP], shstr, cost);
                
                Toggle_ShowroomTD(playerid, false);
                SetPVarInt(playerid, "SelectShowroomID", 0);
                SelectVeh[playerid] = 0;
            }
        }
    }
	if(textid == DistrictDealer[playerid][29])
	{
		pWarna1[playerid] = 3; pWarna2[playerid] = 3;
	}
	else if(textid == DistrictDealer[playerid][30])
	{
		pWarna1[playerid] = 1; pWarna2[playerid] = 1;
	}
	else if(textid == DistrictDealer[playerid][31])
	{
		pWarna1[playerid] = 86; pWarna2[playerid] = 86;
	}
	else if(textid == DistrictDealer[playerid][32])
	{
		pWarna1[playerid] = 15; pWarna2[playerid] = 15;
	}
	else if(textid == DistrictDealer[playerid][33])
	{
		pWarna1[playerid] = 0; pWarna2[playerid] = 0;
	}
	else if(textid == DistrictDealer[playerid][34])
	{
		pWarna1[playerid] = 6; pWarna2[playerid] = 6;
	}
	else if(textid == DistrictDealer[playerid][35])
	{
		pWarna1[playerid] = 2; pWarna2[playerid] = 2;
	}
	else if(textid == DistrictDealer[playerid][36])
	{
		pWarna1[playerid] = 126; pWarna2[playerid] = 126;
	}
	if(IsValidVehicle(ShowroomVeh[playerid]))
    {
        ChangeVehicleColor(ShowroomVeh[playerid], pWarna1[playerid], pWarna2[playerid]);
    }
	//register Happ
	if(textid == RegisterHapp[playerid][26])
	{
		if(!AllStepDone(playerid))
		{
			ShowTDN(playerid, NOTIFICATION_ERROR, "Mohon untuk mengisi data karakter Anda!");
			return 1;
		}

		// Hide semua TextDraw pembuatan karakter
		for(new i = 0; i < 55; i++)
		{
			PlayerTextDrawHide(playerid, RegisterHapp[playerid][i]);
		}
		CancelSelectTextDraw(playerid);

		Info(playerid, "Pembuatan karakter berhasil!");

		// Set camera dan spawn awal
		SetPlayerCameraPos(playerid, 534.065, -2102.218, 98.480);
		SetPlayerCameraLookAt(playerid, 531.651, -2098.260, 96.606);
		new characterQuery[178];
        if(GetPVarInt(playerid, "CreateName") && GetPVarInt(playerid, "CreateGender") && GetPVarInt(playerid, "CreateOrigin") && GetPVarInt(playerid, "CreateAge") && GetPVarInt(playerid, "CreateHeight") && GetPVarInt(playerid, "CreateWeight"))
        {
            mysql_format(g_SQL, characterQuery, sizeof(characterQuery), "INSERT INTO `player_characters` (`Char_Name`, `Char_UCP`, `Char_RegisterDate`) VALUES ('%e', '%e', CURRENT_TIMESTAMP())", AccountData[playerid][pTempName], AccountData[playerid][pUCP]);
            mysql_tquery(g_SQL, characterQuery, "OnPlayerRegister", "d", playerid);
            SetPlayerName(playerid, AccountData[playerid][pTempName]);
        }
	}
	if(textid == RegisterHapp[playerid][17])
    {
		PlayerTextDrawHide(playerid, RegisterHapp[playerid][17]);
        PlayerTextDrawColor(playerid, RegisterHapp[playerid][17], 461004191);
        PlayerTextDrawShow(playerid, RegisterHapp[playerid][17]);
        PlayerTextDrawHide(playerid, RegisterHapp[playerid][18]);
        PlayerTextDrawColor(playerid, RegisterHapp[playerid][18], -125);
        PlayerTextDrawShow(playerid, RegisterHapp[playerid][18]);

        AccountData[playerid][pGender] = 1;
		AccountData[playerid][pSkin] = 137;
		SetPVarInt(playerid, "CreateGender", 1);
		ClearAnimations(playerid);
		SetTimerEx("AnimChar", 500, false, "d", playerid);
		Info(playerid, "Anda memilih gender Pria");
    }
    if(textid == RegisterHapp[playerid][18])
    {
		PlayerTextDrawHide(playerid, RegisterHapp[playerid][17]);
        PlayerTextDrawColor(playerid, RegisterHapp[playerid][17], -125);
        PlayerTextDrawShow(playerid, RegisterHapp[playerid][17]);
        PlayerTextDrawHide(playerid, RegisterHapp[playerid][18]);
        PlayerTextDrawColor(playerid, RegisterHapp[playerid][18], 461004191);
        PlayerTextDrawShow(playerid, RegisterHapp[playerid][18]);

        AccountData[playerid][pGender] = 2;
		AccountData[playerid][pSkin] = 93;
		SetPVarInt(playerid, "CreateGender", 1);
		ClearAnimations(playerid);
		SetTimerEx("AnimChar", 500, false, "d", playerid);
		Info(playerid, "Anda memilih gender Wanita");
    }
	if(textid == RegisterHapp[playerid][21])
    {
        ShowPlayerDialog(playerid, DIALOG_MAKE_CHAR, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Pembuatan Karakter",
			""WHITE"Selamat Datang di "TCRP"District \n"WHITE"Sebelum bermain anda harus membuat karakter terlebih dahulu\
			\nMasukkan nama karakter hanya dengan nama orang Indonesia\nCth: Ronnie_Varquez, Aldy_Firmansyah", "Input", "");
    }
    if(textid == RegisterHapp[playerid][25])//tanggal lahir
	{
	    ShowPlayerDialog(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Tanggal Lahir", "Mohon masukkan tanggal lahir sesuai format hh/bb/tttt cth: (25/09/2001)", "Input", "");
	}
	if(textid == RegisterHapp[playerid][22])//tinggi
	{
	    ShowPlayerDialog(playerid, DIALOG_TINGGIBADAN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE" - Tinggi Badan (cm)", "Mohon masukkan tinggi badan (cm) karakter!\nPerhatian: Format hanya berupa angka satuan cm (cth: 163).", "Input", "");
	}
	if(textid == RegisterHapp[playerid][23])//berat
	{
	    ShowPlayerDialog(playerid, DIALOG_BERATBADAN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE" - Berat Badan (kg)", "Mohon masukkan berat badan (kg) karakter!\nPerhatian: Format hanya berupa angka satuan kg (cth: 75).", "Input", "");
	}
	if(textid == RegisterHapp[playerid][24])//negara
	{
	   	ShowPlayerDialog(playerid, DIALOG_ORIGIN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Negara Kelahiran", "Mohon masukkan kembali negara asal kelahiran karakter.\nPerhatian: Masukkan nama negara yang valid (cth: Indonesia).", "Input", "");
	}
	//warung TD
	for(new i = 0; i <= 10; i++)
	{
		if(textid == WarungTD[playerid][i])
		{
			if(pUnselectWarungUse[playerid] != -1 && pUnselectWarungUse[playerid] != i)
			{
				PlayerTextDrawColor(playerid, WarungTD[playerid][pUnselectWarungUse[playerid]], 59);
				PlayerTextDrawShow(playerid, WarungTD[playerid][pUnselectWarungUse[playerid]]);
			}

			pSelectWarungUse[playerid] = i;

			PlayerTextDrawColor(playerid, WarungTD[playerid][i], 512819199);
			PlayerTextDrawShow(playerid, WarungTD[playerid][i]);
			PlayerPlaySound(playerid, 1052, 0, 0, 0);

			new str[64];
			format(str, sizeof(str), "%s", FormatMoney(WarungHarga[pSelectWarungUse[playerid]]));
			PlayerTextDrawSetString(playerid, WarungTD[playerid][27], str);
			PlayerTextDrawShow(playerid, WarungTD[playerid][27]);
			for(new j = 22; j < 28; j++)
				PlayerTextDrawShow(playerid, WarungTD[playerid][j]);

			pUnselectWarungUse[playerid] = i;
		}
	}
	if(textid == WarungTD[playerid][23]) //buy warung
	{
		if(pSelectWarungUse[playerid] == -1)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belom memilih produk mana pun!");
		
		BuyProdukWarung(playerid, pSelectWarungUse[playerid]);
		return 1;
	}
	if(textid == WarungTD[playerid][22]) //close warung
	{
		ShowWarungTD(playerid, false);
		pSelectWarungUse[playerid] = -1;
		pUnselectWarungUse[playerid] = -1;
	}
	if(Minigame_Active[playerid])
    {
		if(Minigame_Locked[playerid]) return 1;
        for(new i = 0; i < 9; i++)
        {
            if(textid == Minigame_Buttons[playerid][i])
            {                
                if(Minigame_Color[playerid][i] == COLOR_RED && !Minigame_Clicked[playerid][i])
                {
                    // Kotak merah yang belum diklik
                    Minigame_Clicked[playerid][i] = true;
                    PlayerTextDrawColor(playerid, Minigame_Buttons[playerid][i], COLOR_GREEN);
                    PlayerTextDrawShow(playerid, Minigame_Buttons[playerid][i]);
                    Minigame_Success[playerid]++;
                                        
                    if(Minigame_Success[playerid] >= 4)
                    {
                        HideMinigame(playerid);
                        CancelSelectTextDraw(playerid);
                        Minigame_Active[playerid] = false;
                        
                        // Panggil callback jika ada
                        if(strlen(Minigame_Callback[playerid]) > 0)
                        {
                            CallLocalFunction("OnMinigameComplete", "iss", playerid, Minigame_Callback[playerid], Minigame_CallbackParams[playerid]);
                        }
                        else
                        {
                            // Jika tidak ada callback, tampilkan progress bar
                            ShowProgressBar(playerid);
                        }
                        
                        return 1;
                    }
                }
                else if(Minigame_Color[playerid][i] != COLOR_RED || Minigame_Clicked[playerid][i])
                {
                    Minigame_Errors[playerid]++;
                                        
                    if(Minigame_Errors[playerid] >= 3)
                    {
                        HideMinigame(playerid);
                        CancelSelectTextDraw(playerid);
                        Minigame_Active[playerid] = false;
                        SendClientMessageEx(playerid, COLOR_WHITE, ""RED_E"Too many mistakes! "WHITE_E"You failed the minigame");
                        return 1;
                    }
                }
                return 1;
            }
        }
    }
	if(MinigamePH_Active[playerid])
    {
		if(MinigamePH_Locked[playerid]) return 1;
        for(new i = 2; i < 27; i++)
        {
            if(textid == MinigamePanelHacking[playerid][i])
            {                
                if(MinigamePH_Color[playerid][i] == COLOR_RED && !MinigamePH_Clicked[playerid][i])
                {
                    // Kotak merah yang belum diklik
                    MinigamePH_Clicked[playerid][i] = true;
                    PlayerTextDrawColor(playerid, MinigamePanelHacking[playerid][i], COLOR_BLUE);
                    PlayerTextDrawShow(playerid, MinigamePanelHacking[playerid][i]);
                    MinigamePH_Success[playerid]++;
                                        
                    if(MinigamePH_Success[playerid] >= 12)
                    {
                        HideMinigamePH(playerid);
                        CancelSelectTextDraw(playerid);
                        MinigamePH_Active[playerid] = false;
                        
                        // Panggil callback jika ada
                        if(strlen(MinigamePH_Callback[playerid]) > 0)
                        {
                            CallLocalFunction("OnMinigamePHComplete", "iss", playerid, MinigamePH_Callback[playerid], MinigamePH_CallbackParams[playerid]);
                        }
                        else
                        {
                            ShowProgressBar(playerid);
                        }
                        
                        return 1;
                    }
                }
                else if(MinigamePH_Color[playerid][i] != COLOR_RED || MinigamePH_Clicked[playerid][i])
                {
                    MinigamePH_Errors[playerid]++;
                                        
                    if(MinigamePH_Errors[playerid] >= 3)
                    {
                        HideMinigamePH(playerid);
                        CancelSelectTextDraw(playerid);
                        MinigamePH_Active[playerid] = false;
                        SendClientMessageEx(playerid, COLOR_WHITE, ""RED_E"Too many mistakes! "WHITE_E"You failed the minigame");
                        return 1;
                    }
                }
                return 1;
            }
        }
    }
	if(textid == P_CLOTHESSELECT[playerid][14])
	{
		for(new txd; txd < 16; txd ++)
		{
			PlayerTextDrawHide(playerid, P_CLOTHESSELECT[playerid][txd]);
			CancelSelectTextDraw(playerid);
		}
		SelectAcc[playerid] = 0;
		SetCameraBehindPlayer(playerid);
		TogglePlayerControllable(playerid, 1);
		AttachPlayerToys(playerid);
		AttachPlayerToysaxp(playerid);
		AttachPlayerToysDragon(playerid);
		AttachPlayerToysSonic(playerid);
		AttachPlayerToysGrinch(playerid);
		AttachPlayerToysGhost(playerid);
		RemovePlayerAttachedObject(playerid, 9);
		Info(playerid, "Anda memilih batal");
	}
	if(textid == P_CLOTHESSELECT[playerid][12])
	{
		if(SelectAcc[playerid] == sizeof(AksesorisPvt) - 1)
		{
			PlayerPlaySound(playerid, 4203, 0, 0, 0);
			return 0;
		}
		else SelectAcc[playerid] ++;

		SetPlayerAttachedObject(playerid, 9, AksesorisPvt[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

		static minsty[128];
		format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisPvt));
		PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);
	}
	if(textid == P_CLOTHESSELECT[playerid][11])
	{
		if(SelectAcc[playerid] == 0)
		{
			PlayerPlaySound(playerid, 4203, 0, 0, 0);
			return 0;
		}
		else SelectAcc[playerid] --;

		SetPlayerAttachedObject(playerid, 9, AksesorisPvt[SelectAcc[playerid]], 2, -0.392, 0.362, 0.000, 0.000, 0.000, 0.0000, 1.000, 1.000, 1.000);

		static minsty[128];
		format(minsty, sizeof minsty, "%02d/%d", SelectAcc[playerid] + 1, sizeof(AksesorisPvt));
		PlayerTextDrawSetString(playerid, P_CLOTHESSELECT[playerid][15], minsty);
	}
	if(textid == P_CLOTHESSELECT[playerid][13])
	{
		AccountData[playerid][toySelected] = 2;

		pToys[playerid][AccountData[playerid][toySelected]][toy_model] = AksesorisPvt[SelectAcc[playerid]];
		pToys[playerid][AccountData[playerid][toySelected]][toy_status] = 1;
		pToys[playerid][AccountData[playerid][toySelected]][toy_x] = 0.0;
		pToys[playerid][AccountData[playerid][toySelected]][toy_y] = 0.0;
		pToys[playerid][AccountData[playerid][toySelected]][toy_z] = 0.0;
		pToys[playerid][AccountData[playerid][toySelected]][toy_rx] = 0.0;
		pToys[playerid][AccountData[playerid][toySelected]][toy_ry] = 0.0;
		pToys[playerid][AccountData[playerid][toySelected]][toy_rz] = 0.0;
		pToys[playerid][AccountData[playerid][toySelected]][toy_sx] = 1.0;
		pToys[playerid][AccountData[playerid][toySelected]][toy_sy] = 1.0;
		pToys[playerid][AccountData[playerid][toySelected]][toy_sz] = 1.0;
			
		ShowPlayerDialog(playerid, DIALOG_TOYPOSISIBUY, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Ubah Tulang(Bone)", 
		"Spine\
		\n"GRAY"Head\
		\nLeft Upper Arm\
		\n"GRAY"Right Upper Arm\
		\nLeft Hand\
		\n"GRAY"Right Hand\
		\nLeft Thigh\
		\n"GRAY"Right Thigh\
		\nLeft Foot\
		\n"GRAY"Right Foot\
		\nRight Calf\
		\n"GRAY"Left Calf\
		\nLeft Forearm\
		\n"GRAY"Right Forearm\
		\nLeft Clavicle\
		\n"GRAY"Right Clavicle\
		\nNeck\
		\n"GRAY"Jaw", "Select", "Cancel");

		SetCameraBehindPlayer(playerid);
		TogglePlayerControllable(playerid, 1);
		ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil memilih toys");
		for(new txd; txd < 16; txd++)
		{
			PlayerTextDrawHide(playerid, P_CLOTHESSELECT[playerid][txd]);
		}
		RemovePlayerAttachedObject(playerid, 9);
		CancelSelectTextDraw(playerid);
	}
	if(textid == RadialFertod[playerid][9]) //close
    {
        PlayerPlaySound(playerid, 21001, 0.0, 0.0, 0.0);
        ShowPlayerRadial1(playerid, false);
    }
    if(textid == RadialFertod[playerid][0]) //dokument
    {
        PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		ShowPlayerRadial1(playerid, false);
		Dialog_Show(playerid, DOKUMENT_MENU, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Dokument",
		""YELLOW"Identitas:\
		\n\n> Lihat KTP\
		\n"GRAY"> Tunjukan KTP\
		\n> Lihat SIM\
		\n"GRAY"> Tunjukan SIM\
		\n> Lihat SKWB\
		\n"GRAY"> Tunjukan SKWB\
		\n\n"YELLOW"Dokument:\
		\n\n> Lihat BPJS\
		\n"GRAY"> Perlihatkan BPJS\
		\n> Lihat SKCK\
		\n"GRAY"> Perlihatkan SKCK\
		\n> Lihat SKS\
		\n"GRAY"> Perlihatkan SKS", "Pilih", "Batal");
    }
    if(textid == RadialFertod[playerid][1]) //Payment 
    {
        PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		ShowPlayerRadial1(playerid, false);
		ShowPlayerInvoice(playerid);
    }
    if(textid == RadialFertod[playerid][2]) //vehicle 
    {
        PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		ShowPlayerRadial1(playerid, false);
		new vehid = GetNearestVehicleToPlayer(playerid, 6.5, false);
		if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan apapun di sekitar!"), CancelSelectTextDraw(playerid);
		
		static string[178];
		NearestVehicleID[playerid] = vehid;
		format(string, sizeof(string), "Kunci\
		\n"GRAY"Lampu\
		\nHood buka/tutup\
		\n"GRAY"Trunk buka/tutup\
		\nBagasi\
		\n"GRAY"Holster\
		\nMasuk ke dalam bagasi");
		
		ShowPlayerDialog(playerid, DIALOG_VEHICLE_MENU, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Vehicle Menu",
		string, "Pilih", "Batal");
    }
    if(textid == RadialFertod[playerid][3]) //Inventory
    {
        PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		ShowPlayerRadial1(playerid, false);

		if(AccountData[playerid][ActivityTime] != 0)
		{
			CancelSelectTextDraw(playerid);
			return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu sampai progress selesai!");
		}
		PlayerTextDrawSetPreviewModel(playerid, inv::textdraw[playerid][7], AccountData[playerid][pSkin]);
        PlayerTextDrawShow(playerid, inv::textdraw[playerid][7]);
		Inventory_Show(playerid);
		PlayerPlaySound(playerid, 1039, 0.0, 0.0, 0.0);
    }

    if(textid == RadialFertod[playerid][4]) //Phone   
    {
        PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
		ShowPlayerRadial1(playerid, false);
		ShowingSmartphone(playerid);
    }
    if(textid == RadialFertod[playerid][5]) //Radio
    {
        if(!PlayerHasItem(playerid, "Radio")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki radio!");
        if(IsPlayerInWater(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membuka Radio di dalam air!");

        SendRPMeAboveHead(playerid, "Membuka Radio miliknya.", X11_PLUM1);
        if(!IsPlayerInAnyVehicle(playerid))
        {
            ApplyAnimation(playerid, "ped", "Jetpack_Idle", 4.1, 0, 0, 0, 1, 0, 1);
            SetPlayerAttachedObject(playerid, 9, 19942, 5, 0.043000, 0.022999, -0.006000, -112.000022, -34.900020, -8.500002, 1.000000, 1.000000, 1.000000);
        }
        ShowPlayerRadial1(playerid, false);
        RadioTextdrawToggle(playerid, true);
        SelectTextDraw(playerid, 0xFF9999FF);
    }
    if(textid == RadialFertod[playerid][6]) //Aksesoris
    {
		ShowPlayerRadial1(playerid, false);
        callcmd::fashion(playerid, "");
    }
    if(textid == RadialFertod[playerid][7]) //Action
    {
        new frmtx[300], count = 0;

		foreach(new i : Player) if (i != playerid) if (IsPlayerNearPlayer(playerid, i, 2.5))
		{
			format(frmtx, sizeof(frmtx), "%sPlayer ID: %d\n", frmtx, i);
			NearestPlayer[playerid][count++] = i;
		}
			
		if (AccountData[playerid][pFaction] == FACTION_NONE && AccountData[playerid][pFamily] == -1)
		{
			Dialog_Show(playerid, PANEL_NONE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Menu Warga", "Drag/Undrag Person", "Pilih", "Batal");
			ShowPlayerRadial1(playerid, false);
		}
		else if (AccountData[playerid][pFaction] == FACTION_TRANS && AccountData[playerid][pFamily] == -1)
		{
			Dialog_Show(playerid, PANEL_NONE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Menu Warga", "Drag/Undrag Person", "Pilih", "Batal");
			ShowPlayerRadial1(playerid, false);
		}
		else
		{
			if (count > 0)
			{
				Dialog_Show(playerid, DialogKantongPanel, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Faction Panel", frmtx, "Pilih", "Batal");
			}
			else ShowTDN(playerid, NOTIFICATION_WARNING, "Tidak ada orang disekitar anda!");
			
			return ShowPlayerRadial1(playerid, false);
		}
		
		if (AccountData[playerid][pFamily] > -1 && AccountData[playerid][pFamilyRank] > 1)
		{
			if (count > 0)
			{
				Dialog_Show(playerid, FamiliesKantongList, DIALOG_STYLE_LIST, ""TCRP"District "WHITE" - Faction Panel (Gang)", frmtx, "Pilih", "Batal");
			}
			else ShowTDN(playerid, NOTIFICATION_WARNING, "Tidak ada orang disekitar anda!");
			return ShowPlayerRadial1(playerid, false);
		}
	}
    if(textid == RadialFertod[playerid][8]) //Emote
    {
        callcmd::elist(playerid, "");
		forex (txd, 82) PlayerTextDrawHide(playerid, RadialFertod[playerid][txd]);
    }
	//innventory
	if(textid == inv::textdraw[playerid][39])//close
	{
		Inventory_Close(playerid);
	}
	if(textid == inv::textdraw[playerid][30])//amount
	{
		if(AccountData[playerid][pSelectItem] == -1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum memilih item!");
		ShowPlayerDialog(playerid, DIALOG_SETAMOUNT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Set Amount",
		"Mohon masukkan berapa jumlah item yang akan diberikan:", "Set", "Batal");
	}
	if(textid == inv::textdraw[playerid][29])//use
	{
		new
			itemid = AccountData[playerid][pSelectItem],
			string[64];

		if(AccountData[playerid][pSelectItem] == -1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum memilih barang!");
		strunpack(string, InventoryData[playerid][itemid][invItem]);
			
		if(ItemCantUse(string)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak bisa digunakan!");
		OnPlayerUseItem(playerid, itemid, string);
	}
	if(textid == inv::textdraw[playerid][33])//give
	{
		if(AccountData[playerid][pSelectItem] == -1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum memilih barang!");
		if(AccountData[playerid][pAmountInv] == 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum input jumlah yang akan diberikan!");
		
		new frmxt[355], string[512];
		strunpack(string, InventoryData[playerid][AccountData[playerid][pSelectItem]][invItem]);
		

		if(!strcmp(string, "Sampah Makanan"))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat memberikan sampah kepada orang lain!");
		
		if(!strcmp(string, "Boombox"))
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat memberikan Boombox kepada orang lain!");

		new count = 0;
		foreach(new i : Player) if(i != playerid) if(IsPlayerNearPlayer(playerid, i, 2.5))
		{
			format(frmxt, sizeof(frmxt), "%sPlayer ID: %d\n", frmxt, i);
			NearestPlayer[playerid][count++] = i;
		}
		
		if(count == 0)
		{
			PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
			Inventory_Close(playerid);
			return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Give Item",
			"Tidak ada player yang dekat dengan anda!", "Tutup", "");
		}

		ShowPlayerDialog(playerid, DIALOG_MEMBERI, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Give Item", frmxt, "Pilih", "Close");
	}
	if(textid == inv::textdraw[playerid][36])//drop
	{
		if(AccountData[playerid][pSelectItem] < 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum memilih barang!");
		if(AccountData[playerid][pAmountInv] == 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda belum menentukan jumlah barang!");
		if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
		
		new itemid = AccountData[playerid][pSelectItem],
			amount = AccountData[playerid][pAmountInv],
			model = InventoryData[playerid][AccountData[playerid][pSelectItem]][invModel],
			string[ 256 ];
		
		strunpack(string, InventoryData[playerid][itemid][invItem]);
		
		new trash_nearest = TrashNearest(playerid);
		if(trash_nearest != -1)
		{
			if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");
			if(amount > InventoryData[playerid][AccountData[playerid][pSelectItem]][invQuantity]) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda tidak memiliki %s sebanyak itu!", string));
			Inventory_Remove(playerid, string, amount);
			Inventory_Close(playerid);
			ShowItemBox(playerid, sprintf("Removed %dx", amount), string, model);
			ApplyAnimation(playerid, "GRENADE", "WEAPON_throwu", 4.1, 0, 0, 0, 0, 0, 1);

			SendRPMeAboveHead(playerid, sprintf("Membuang %d %s miliknya ke tong sampah", amount, string), X11_PLUM1);
		}
		else if(IsPeleburanArea(playerid))
		{
			if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota kepolisian!");
			if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
			if(amount < 1 || amount > InventoryData[playerid][AccountData[playerid][pSelectItem]][invQuantity]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah tidak valid!");

			Inventory_Remove(playerid, string, amount);
			Inventory_Close(playerid);
			ShowItemBox(playerid, sprintf("Removed %dx", amount), string, model);
			ApplyAnimation(playerid, "GRENADE", "WEAPON_throwu", 4.1, 0, 0, 0, 0, 0, 1);
			
			SendRPMeAboveHead(playerid, sprintf("Melempar %d %s ke tempat peleburan", amount, string), X11_PLUM1);
		}
		else
		{
			if(!strcmp(string, "Sampah Makanan"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang sampah sembarangan!");
				return 1;
			}
			else if(!strcmp(string, "Hiu"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Penyu"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Kayu"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Kayu Potongan"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Ayam Hidup"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Ayam Potongan"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Bulu"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Boxmats"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Pancingan"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Umpan"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Batu Kotor"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Batu Bersih"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Petrol"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}
			else if(!strcmp(string, "Pure Oil"))
			{
				ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat membuang item ini!");
				return 1;
			}

			if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah input tidak valid!");
			if(amount > InventoryData[playerid][itemid][invQuantity]) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda tidak memiliki %s sebanyak itu!", string));
			
			if(!strcmp(string, "Radio", true))
			{
				if(ToggleRadio[playerid] || RadioMicOn[playerid])
				{
					ToggleRadio[playerid] = false;
					RadioMicOn[playerid] = false;
					CallRemoteFunction("UpdatePlayerVoiceMicToggle", "dd", playerid, false);
					CallRemoteFunction("UpdatePlayerVoiceRadioToggle", "dd", playerid, false);
					CallRemoteFunction("AssignFreqToFSVoice", "ddd", playerid, true, 0);
					PlayerTextDrawSetString(playerid, ATRP_RadioTD[playerid][7], "0");
				}
			}
			DropPlayerItem(playerid, itemid, amount);
		}
	}
	//job mixer
	if(textid == jobs::Pmixer[playerid][5])
	{
		jobs::mixer_select_case(playerid, 1);
	}
	if(textid == jobs::Pmixer[playerid][6])
	{
		jobs::mixer_select_case(playerid, 2);
	}
	if(textid == jobs::Pmixer[playerid][7])
	{
		jobs::mixer_select_case(playerid, 3);
	}
	if(textid == jobs::Pmixer[playerid][8])
	{
		jobs::mixer_select_case(playerid, 4);
	}
	if(textid == jobs::Pmixer[playerid][9])
	{
		jobs::mixer_select_case(playerid, 5);
	}
	if(textid == jobs::Pmixer[playerid][10])//confirm
	{
		jobs::mixer_confirm(playerid);
	}
	//phone_funcs
	
	if(textid == ATRP_Phone[playerid][23]) //Close
    {
        Toggle_PhoneTD(playerid, false);
        CancelSelectTextDraw(playerid);
        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
        RemovePlayerAttachedObject(playerid, 9);
        AccountData[playerid][phoneShown] = false;
        SendRPMeAboveHead(playerid, "Menutup HP Miliknya.", X11_PLUM1);
    }

    if(textid == ATRP_Phone[playerid][28]) //kontak
    {
        ShowPlayerDialog(playerid, DialogOpenContact, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Kontak", "Tambahkan Kontak Baru\nLihat Daftar Kontak", "Pilih", "Batal");
    }

    if(textid == ATRP_Phone[playerid][33]) //Gps
    {
        if(BusIndex[playerid] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang bekerja sebagai supir bus!");
        if(DurringSweeping[playerid]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang bekerja sebagai pembersih jalan!");
        //if(PlayerKargoVars[playerid][KargoStarted]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang bekerja sebagai Supir Kargo!");

        if(AccountData[playerid][pFaction] == FACTION_EMS && AccountData[playerid][pDutyEms]) {
            Dialog_Show(playerid, GpsMenu, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Menu Gps",
            "Lokasi GPS\n"GRAY"Signal Emergency (EMS)", "Pilih", "Batal");
        } else {
            ShowPlayerDialog(playerid, LokasiGps, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Lokasi",
            "Lokasi Umum\
            \n"GRAY"Lokasi Pekerjaan\
            \nLokasi Hobi\
            \n"GRAY"Lokasi Warung\
            \nATM Kota\
            \n"GRAY"Garasi Umum Kota\
            \nTong Sampah Kota\
            \nPom Bensin Kota\
            \n"GRAY"Bengkel Modshop\
            \nRumah Saya\
			\nRumah Tersedia\
			\nWorkshop\
            \n"RED"(Disable Checkpoint)\
            \n"RED"(Disable Shareloc)", "Pilih", "Batal");
        }
    }

    if(textid == ATRP_Phone[playerid][35]) //airdrop
    {
        new strings[255];
        format(strings, sizeof(strings), "Status: %s\
        \nShare Contacts", AccountData[playerid][AirdropPermission] ? ""LIGHTGREEN"Share Contact diizinkan" : ""RED"Share Contact tidak diizinkan");
        
        ShowPlayerDialog(playerid, DIALOG_AIRDROPDISPLAY, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Airdrop", strings, "Pilih", "Batal");
    }

    if(textid == ATRP_Phone[playerid][36]) //lainnya 
    {
        Dialog_Show(playerid, DialogLainnya, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Aplikasi Lainnya",
		"Settings\
		\n"GRAY"Vehicle\
		\nHarga Pasar", "Pilih", "Batal");
    }

    if(textid == ATRP_Phone[playerid][27]) //whatsapp_chats
    {
        ShowContactList(playerid);
    }

    if(textid == ATRP_Phone[playerid][34]) //iklan
    {
        if(AccountData[playerid][phoneAirplaneMode]) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone sedang dalam Mode Pesawat!");

        ShowPlayerDialog(playerid, DIALOG_YELLOW_PAGE_MENU, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Yellow Pages",
        "Melihat antrian iklan\nKirim iklan baru", "Pilih", "Batal");
    }

    if(textid == ATRP_Phone[playerid][29]) //Telpon
    {
        ShowPlayerDialog(playerid, DialogTelepon, DIALOG_STYLE_INPUT, ""TCRP"District "WHITE"- Telepon", "Mohon masukan nomor telepon yang ingin anda hubungi:", "Telfon", "Batal");
    }

    if(textid == ATRP_Phone[playerid][25]) //bank
    {
        Toggle_PhoneTD(playerid, false);
        Toggle_BankTD(playerid, true);
    }

    if(textid == CloseCallButton[playerid])
    {
        Toggle_CallTD(playerid, false);
        PlayerTextDrawHide(playerid, RedButtonincomingCall[playerid]);
        PlayerTextDrawHide(playerid, GreenButtonincomingCall[playerid]);
        PlayerTextDrawHide(playerid, RedButtonoutComingCall[playerid]);
        CancelSelectTextDraw(playerid);
        AccountData[playerid][phoneShown] = false;
    }

    if(textid == ATRP_Phone[playerid][26]) //faction
    {
        Dialog_Show(playerid, DialogFactionCall, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"Faction Call", ""GRAY"Kepolisian\nMedis\nTrans\nBengkel\nFood", "Pilih", "Batal");
    }

    if(textid == ATRP_BankTD[playerid][21])
    {
        Toggle_BankTD(playerid, false);
        Toggle_PhoneTD(playerid, true);
    }
	if(textid == ATRP_BankTD[playerid][36])
    {
        ShowPlayerDialog(playerid, DialogTransfer, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Transfer",
        "Mohon masukkan nomor rekening yang ingin anda transfer:", "Submit", "Batal");
    }

    if(textid == CloseTwitterHome[playerid])
    {
        Toggle_TwitterHome(playerid, false);
        Toggle_PhoneTD(playerid, true);
    }
    
    if(textid == CloseTwitterHomePage[playerid])
    {
        Toggle_TwitterHomepage(playerid, false);
        Toggle_PhoneTD(playerid, true);
    }
	if(textid == ATRP_Phone[playerid][30]) //kalkulator
    {
        Info(playerid, "Come song!");
    }

	if(textid == ATRP_Phone[playerid][31]) //twitter
    {
        Toggle_PhoneTD(playerid, false);
        if(!AccountData[playerid][Twitter])
        {
            Toggle_TwitterHome(playerid, true);
        }
        else
        {
            Toggle_TwitterHomepage(playerid, true);
        }
    }

    if(textid == ATRP_Phone[playerid][32]) //Spotify
    {
        Toggle_PhoneTD(playerid, false);
        if(!AccountData[playerid][Spotify])
        {
            Toggle_SpotifyHomeTD(playerid, true);
        }
        else
        {
            Toggle_SpotifyTD(playerid, true);
        }
    }
    if(textid == ATRP_SpotifyTD[playerid][52]) // Earphone
    {
        if(AccountData[playerid][pEarphone] != 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Earphone!");
        
        ShowPlayerDialog(playerid, DialogSpotify, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Spotify", "Matikan Musik\nPutar Musik", "Select", "Cancel");
    }
	if(textid == ATRP_SpotifyTD[playerid][21]) //close
    {
        Toggle_SpotifyTD(playerid, false);
        Toggle_PhoneTD(playerid, true);
    }
	if(textid == ATRP_SpotifyTD[playerid][24]) //logout spotify
    {
        Toggle_SpotifyTD(playerid, false);
        Toggle_SpotifyHomeTD(playerid, true);
    }
	for(new i = 0; i < SpotifyCount[playerid]; i++)
	{
		if(textid == ATRP_SpotifyTD[playerid][27 + i]) //klik box
		{
			PlayStream(playerid, SpotifyHistory[playerid][i], 0.0, 0.0, 0.0, 1, 0);
			SendRPMeAboveHead(playerid, "Memutar ulang lagu dari history spotify", X11_PLUM1);
			return 1;
		}
	}

    /*if(textid == ATRP_SpotifyTD[playerid][18]) // boomboox
    {
        if(!AccountData[playerid][pVip]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pengguna VIP!");

        if(GetPVarType(playerid, "PlacedBB"))
		{
			if(IsPlayerInRangeOfPoint(playerid, 3.0, GetPVarFloat(playerid, "BBX"), GetPVarFloat(playerid, "BBY"), GetPVarFloat(playerid, "BBZ")))
			{
				ShowPlayerDialog(playerid, DANN_BOOMBOX, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Boombox", "Matikan Boombox\nPutar Musik", "Select", "Cancel");
			}
			else
			{
	   			return ShowTDN(playerid, NOTIFICATION_ERROR, "~g~[!]~w~: Kamu tidak berada didekat boombox mu!");
			}
	    }
	    else
	    {
	    	ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak menaruh boombox sebelumnya!");
		}  
    }*/
	if(textid == ATRP_HomeSpotify[playerid][29]) //daftar spotify
	{
		if(AccountData[playerid][phoneAirplaneMode]) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone sedang dalam Mode Pesawat!");

        ShowPlayerDialog(playerid, DIALOG_SPOTIFY_SIGN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Daftar Spotify",
		"Hai, selamat datang di Spotify!\
		\nSilahkan masukkan username Spotify kamu, ini akan ditampilkan pada setiap daftar atau aktivitas musik kamu:\
		\nIngat: Username hanya dapat berupa huruf dan angka, tidak menggunakan simbol!\
		\nPanjang username 7 - 24 karakter!", "Set", "Batal");
	}

	if(textid == ATRP_HomeSpotify[playerid][30]) //login spotify
	{
		if(AccountData[playerid][phoneAirplaneMode]) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone sedang dalam Mode Pesawat!");

        ShowPlayerDialog(playerid, DIALOG_SPOTIFY_LOGIN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Login Spotify",
		"Hai, selamat datang di Spotify!\
		\nSilahkan masukkan username Spotify kamu yang telah terdaftar:", "Input", "Batal");
	}
	if(textid == ATRP_HomeSpotify[playerid][21])
    {
        Toggle_SpotifyHomeTD(playerid, false);
        Toggle_PhoneTD(playerid, true);
		AccountData[playerid][Spotify] = false;
    }

    if(textid == ATRP_TwitterHomeTD[playerid][24]) // Daftar
    {
        if(AccountData[playerid][phoneAirplaneMode]) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone sedang dalam Mode Pesawat!");

        ShowPlayerDialog(playerid, DIALOG_TWITTER_SIGN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Daftar Twitter",
        "Hai, selamat datang di Twitter!\
        \nSilahkan masukkan username Twitter kamu, ini akan ditampilkan pada setiap post tweet yang kamu buat:\
        \nIngat: Username hanya dapat berupa huruf dan angka, tidak menggunakan simbol!\
        \nPanjang username 7 - 24 karakter!", "Set", "Batal");
    }

    if(textid == ATRP_TwitterHomeTD[playerid][23]) // Login Jika sudah punya akun twitter
    {
        if(AccountData[playerid][phoneAirplaneMode]) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone sedang dalam Mode Pesawat!");

        ShowPlayerDialog(playerid, DIALOG_TWITTER_LOGIN, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Login Twitter",
        "Hai, selamat datang di Twitter!\
        \nSilahkan masukkan username Twitter kamu yang telah terdaftar:", "Input", "Batal");
    }
	if(textid == ATRP_TwitterHomeTD[playerid][21])
    {
        Toggle_TwitterHome(playerid, false);
        Toggle_PhoneTD(playerid, true);
		AccountData[playerid][Twitter] = false;
    }

    if(textid == ATRP_TwitterHomepageTD[playerid][26]) // Tweet
    {
        if(AccountData[playerid][phoneAirplaneMode]) 
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Smartphone sedang dalam Mode Pesawat!");

        ShowPlayerDialog(playerid, DIALOG_TWITTER_POST_SEND, DIALOG_STYLE_INPUT, ""TCRP"District  "GRAY"- Kirim Tweet", "Masukkan Tweet yang ingin anda buat dibawah sini:", "Kirim", "Kembali");
        AccountData[playerid][CurrentlyReadTwitter] = true;
    }
	if(textid == ATRP_TwitterHomepageTD[playerid][24]) // Logout Twitter
    {
        Toggle_TwitterHomepage(playerid, false);
        Toggle_TwitterHome(playerid, true);
    }
    if(textid == ATRP_TwitterHomepageTD[playerid][21])
    {
        Toggle_TwitterHomepage(playerid, false);
        Toggle_PhoneTD(playerid, true);
    }
	if(textid == ATRP_TwitterHomepageTD[playerid][48]) //next
	{
	    ShowPlayerTwitterPageV1(playerid, pTwitterPage[playerid] + 1);	
	}
	else if(textid == ATRP_TwitterHomepageTD[playerid][49]) //prev
	{
		if(pTwitterPage[playerid] > 0)
		{
		    ShowPlayerTwitterPageV1(playerid, pTwitterPage[playerid] - 1);
		}
	}

    if(textid == RedButtonincomingCall[playerid])
    {
        foreach(new i : Player) if(IsPlayerConnected(i) && AccountData[i][phoneCallingWithPlayerID] == playerid)
        {
            new phoneCallFromID = i;
            ApplyAnimation(phoneCallFromID, "ped", "phone_out", 4.0, 0, 0, 0, 0, 0, 1);
            RemovePlayerAttachedObject(phoneCallFromID, 9);
            
            ApplyAnimation(playerid, "ped", "phone_out", 4.0, 0, 0, 0, 0, 0, 1);
            RemovePlayerAttachedObject(playerid, 9);

            if(AccountData[playerid][phoneShown]) {
                AccountData[playerid][phoneShown] = false;
            }
            
            if(AccountData[phoneCallFromID][phoneShown]) {
                AccountData[phoneCallFromID][phoneShown] = false;
            }

            HideAllSmartphone(playerid), HideAllSmartphone(phoneCallFromID);
            Toggle_CallTD(playerid, false), Toggle_CallTD(phoneCallFromID, false);
            CancelSelectTextDraw(playerid), CancelSelectTextDraw(phoneCallFromID);
            PlayerTextDrawHide(playerid, RedButtonincomingCall[playerid]);
            PlayerTextDrawHide(playerid, GreenButtonincomingCall[playerid]);
            PlayerTextDrawHide(phoneCallFromID, RedButtonoutComingCall[playerid]);
            StopAudioStreamForPlayer(playerid);
            
            AccountData[playerid][phoneCallingTime] = 0;
            AccountData[playerid][phoneCallingWithPlayerID] = INVALID_PLAYER_ID;
            AccountData[playerid][phoneIncomingCall] = false;
            AccountData[playerid][phoneIncomingCall] = false;
            
            AccountData[phoneCallFromID][phoneCallingTime] = 0;
            AccountData[phoneCallFromID][phoneCallingWithPlayerID] = INVALID_PLAYER_ID;
            AccountData[phoneCallFromID][phoneIncomingCall] = false;
            AccountData[phoneCallFromID][phoneIncomingCall] = false;
        }
    }

    if(textid == GreenButtonincomingCall[playerid])
    {
        if(AccountData[playerid][phoneDurringConversation]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang dalam percakapan!");
        if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan tidak dapat mengangkat panggilan!");
        foreach(new i : Player) if (IsPlayerConnected(i) && AccountData[i][phoneCallingWithPlayerID] == playerid)
        {
            new callingWithPlayerID = i;
            AccountData[playerid][phoneDurringConversation] = true;
            AccountData[playerid][phoneIncomingCall] = false;
            AccountData[playerid][phoneCallingTime] = 0;
            AccountData[playerid][phoneCallingWithPlayerID] = callingWithPlayerID;

            AccountData[callingWithPlayerID][phoneDurringConversation] = true;
            AccountData[callingWithPlayerID][phoneIncomingCall] = false;
            AccountData[callingWithPlayerID][phoneCallingTime] = 0;
            AccountData[callingWithPlayerID][phoneCallingWithPlayerID] = playerid;

            ApplyAnimationEx(playerid, "ped", "phone_talk", 3.1, 0, 1, 0, 1, 1, 1);
            SetPlayerAttachedObject(playerid, 9, 18870, 6,  0.099000, 0.009999, 0.000000,  78.200027, 179.000061, -1.500000,  1.000000, 1.000000, 1.000000); // 276
            
            ApplyAnimationEx(callingWithPlayerID, "ped", "phone_talk", 3.1, 0, 1, 0, 1, 1, 1);
            SetPlayerAttachedObject(callingWithPlayerID, 9, 18870, 6,  0.099000, 0.009999, 0.000000,  78.200027, 179.000061, -1.500000,  1.000000, 1.000000, 1.000000); // 276
            
            static contnstr[25];
            format(contnstr, sizeof(contnstr), "%s", AccountData[callingWithPlayerID][pPhone]);
            for(new cid; cid < MAX_CONTACTS; ++cid)
            {
                if(ContactData[playerid][cid][contactExists])
                {
                    if(!strcmp(ContactData[playerid][cid][contactNumber], AccountData[callingWithPlayerID][pPhone], false))
                    {
                        format(contnstr, sizeof(contnstr), "%s", ContactData[playerid][cid][contactName]);
                    }
                }
            }
            PlayerTextDrawSetString(playerid, ContactNameTD[playerid], contnstr);
            StopAudioStreamForPlayer(playerid);

            HideAllSmartphone(playerid), HideAllSmartphone(callingWithPlayerID);
            PlayerTextDrawHide(playerid, GreenButtonincomingCall[playerid]);
            PlayerTextDrawHide(playerid, RedButtonincomingCall[playerid]);
            PlayerTextDrawShow(playerid, RedButtonoutComingCall[playerid]);
            Toggle_CallTD(playerid, true), Toggle_CallTD(callingWithPlayerID, true);
            CancelSelectTextDraw(playerid), CancelSelectTextDraw(callingWithPlayerID);
            CallRemoteFunction("ConnectPlayerCalling", "dd", playerid, callingWithPlayerID);
        }
    }

    if(textid == RedButtonoutComingCall[playerid])
    {
        new callDurringWithPlayerID = AccountData[playerid][phoneCallingWithPlayerID];
        if(!AccountData[playerid][phoneIncomingCall] && callDurringWithPlayerID != INVALID_PLAYER_ID)
        {
            if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
            {
                ClearAnimations(playerid, 1);
                ApplyAnimation(playerid, "ped", "phone_out", 4.0, 0, 0, 0, 0, 0, 1);
            }
            
            if(!IsPlayerInAnyVehicle(callDurringWithPlayerID) && GetPlayerState(callDurringWithPlayerID) == PLAYER_STATE_ONFOOT)
            {
                ClearAnimations(callDurringWithPlayerID, 1);
                ApplyAnimation(callDurringWithPlayerID, "ped", "phone_out", 4.0, 0, 0, 0, 0, 0, 1);
            }
            RemovePlayerAttachedObject(playerid, 9);
            RemovePlayerAttachedObject(callDurringWithPlayerID, 9);
            CallRemoteFunction("DisconnectPlayerCalling", "dd", playerid, callDurringWithPlayerID);

            if(AccountData[playerid][phoneShown]) {
                AccountData[playerid][phoneShown] = false;
            }
            
            if(AccountData[callDurringWithPlayerID][phoneShown]) {
                AccountData[callDurringWithPlayerID][phoneShown] = false;
            }

            HideAllSmartphone(playerid), HideAllSmartphone(callDurringWithPlayerID);
            Toggle_CallTD(playerid, false), Toggle_CallTD(callDurringWithPlayerID, false);
            PlayerTextDrawHide(playerid, RedButtonoutComingCall[playerid]), PlayerTextDrawHide(callDurringWithPlayerID, RedButtonoutComingCall[callDurringWithPlayerID]);
            PlayerTextDrawHide(callDurringWithPlayerID, RedButtonincomingCall[callDurringWithPlayerID]), PlayerTextDrawHide(callDurringWithPlayerID, GreenButtonincomingCall[callDurringWithPlayerID]);
            CancelSelectTextDraw(playerid), CancelSelectTextDraw(callDurringWithPlayerID);
            StopAudioStreamForPlayer(callDurringWithPlayerID);
            AccountData[playerid][phoneCallingWithPlayerID] = INVALID_PLAYER_ID;
            AccountData[playerid][phoneDurringConversation] = false;
            AccountData[playerid][phoneIncomingCall] = false;
            AccountData[playerid][phoneCallingTime] = 0;
            
            AccountData[callDurringWithPlayerID][phoneCallingWithPlayerID] = INVALID_PLAYER_ID;
            AccountData[callDurringWithPlayerID][phoneDurringConversation] = false;
            AccountData[callDurringWithPlayerID][phoneIncomingCall] = false;
            AccountData[callDurringWithPlayerID][phoneCallingTime] = 0;
            Info(playerid, "Telepon terputus...");
            Info(callDurringWithPlayerID, "Telepon terputus...");
        }
        else
        {
            ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
            RemovePlayerAttachedObject(playerid, 9);

            if(AccountData[playerid][phoneShown]) {
                AccountData[playerid][phoneShown] = false;
            }
            PlayerTextDrawHide(playerid, RedButtonoutComingCall[playerid]);
            HideAllSmartphone(playerid);
            Toggle_CallTD(playerid, false);
            CancelSelectTextDraw(playerid);
            AccountData[playerid][phoneCallingWithPlayerID] = INVALID_PLAYER_ID;
            AccountData[playerid][phoneDurringConversation] = false;
            AccountData[playerid][phoneIncomingCall] = false;
            AccountData[playerid][phoneCallingTime] = 0;
            Info(playerid, "Nomor tersebut berada di panggilan lain/tidak aktif...");
        }
    }
	//radio
	if(textid == ATRP_RadioTD[playerid][10]) //set freq
    {   
        ShowPlayerDialog(playerid, DIALOG_RADIO_FREQ, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Radio Fx",
        "Masukkan frekuensi radio yang ingin diterapkan pada kolom dibawah ini\
        \n(Frekuensi harus berada diantara 0 - 9999)\
        \nCatatan: Masukkan frekuensi 0 untuk memutuskan saluran frekuensi/netral", "Submit", "Batal");
    }
    else if(textid == ATRP_RadioTD[playerid][9]) // Close
    {
        SendRPMeAboveHead(playerid, "Menutup Radio miliknya.", X11_PLUM1);
        if(!IsPlayerInAnyVehicle(playerid))
        {
            ClearAnimations(playerid, 1);
            ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        }
        RemovePlayerAttachedObject(playerid, 9);
        RadioTextdrawToggle(playerid, false);
        CancelSelectTextDraw(playerid);
    }
    else if(textid == ATRP_RadioTD[playerid][8]) // Power
    {
        RadioMicOn[playerid] = false;
        CallRemoteFunction("UpdatePlayerVoiceMicToggle", "dd", playerid, false);
        switch(ToggleRadio[playerid])
        {
            case false:
            {
                ToggleRadio[playerid] = true;
                CallRemoteFunction("UpdatePlayerVoiceRadioToggle", "dd", playerid, true);
                if(!IsPlayerInAnyVehicle(playerid))
                {
                    ClearAnimations(playerid, 1);
                    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
                }
                RemovePlayerAttachedObject(playerid, 9);
                ShowTDN(playerid, NOTIFICATION_INFO, "Berhasil menyalakan radio");
                
                CancelSelectTextDraw(playerid);
                RadioTextdrawToggle(playerid, false);
            }
            case true:
            {
                ToggleRadio[playerid] = false;
                CallRemoteFunction("UpdatePlayerVoiceRadioToggle", "dd", playerid, false);
                if(!IsPlayerInAnyVehicle(playerid))
                {
                    ClearAnimations(playerid, 1);
                    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
                }
                RemovePlayerAttachedObject(playerid, 9);
                ShowTDN(playerid, NOTIFICATION_INFO, "Berhasil mematikan radio");
                
                CancelSelectTextDraw(playerid);
                RadioTextdrawToggle(playerid, false);
            }
        }
    }
	//toys
	if(textid == P_TOYS[playerid][1]) // X Minus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_x] -= 0.020;
	
		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][2]) // X Plus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_x] += 0.020;
	
		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][4]) // Y Minus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_y] -= 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][5]) // Y Plus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_y] += 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][7]) // Z Minus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_z] -= 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][8]) // Z Plus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_z] += 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][10]) // Rot x Minus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_rx] -= 3.0;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][11]) // Rot x Minus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_rx] += 3.0;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][13]) // Rot y Minus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_ry] -= 3.0;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][14]) // Rot y Minus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_ry] += 3.0;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][16]) // rot z min 
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_rz] -= 3.0;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][17]) // rot z plus 
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_rz] += 3.0;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][19]) // skale x min 
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_sx] -= 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][20]) // skale x plus
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_sx] += 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][22]) // skale y min 
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_sy] -= 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][23]) // skale y plus 
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_sy] += 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][25]) // skale z min 
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_sz] -= 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][26]) // skale z plus 
	{
		pToys[playerid][AccountData[playerid][toySelected]][toy_sz] += 0.020;

		SetPlayerAttachedObject(playerid,
			AccountData[playerid][toySelected],
			pToys[playerid][AccountData[playerid][toySelected]][toy_model],
			pToys[playerid][AccountData[playerid][toySelected]][toy_bone],
			pToys[playerid][AccountData[playerid][toySelected]][toy_x],
			pToys[playerid][AccountData[playerid][toySelected]][toy_y],
			pToys[playerid][AccountData[playerid][toySelected]][toy_z],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_ry],
			pToys[playerid][AccountData[playerid][toySelected]][toy_rz],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sx],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sy],
			pToys[playerid][AccountData[playerid][toySelected]][toy_sz]);
		
		SetPVarInt(playerid, "UpdatedToy", 1);
	}
	if(textid == P_TOYS[playerid][27]) // Keluar
	{
		HideTDToys(playerid);
		MySQL_SavePlayerToys(playerid);
		ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil menyimpan Kordinat Baru");
	}
	//atm
	if(textid == VR_ATMTD[playerid][36])// Withdraw
	{
		ShowPlayerDialog(playerid, DIALOG_ATM_WITHDRAW, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fleeca Bank", "Mohon masukan berapa jumlah uang yang anda ingin anda ambil:", "Submit", "Batal");
	}
	if(textid == VR_ATMTD[playerid][37])// Deposit
	{
		ShowPlayerDialog(playerid, DIALOG_ATM_DEPOSIT, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fleeca Bank", "Mohon masukan berapa jumlah uang yang ingin anda masukkan:", "Submit", "Batal");
	}
	if(textid == VR_ATMTD[playerid][38])// Transfer
	{
		ShowPlayerDialog(playerid, DIALOG_ATM_TRANSFER, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Fleeca Bank", "Mohon masukkan nomor rekening yang ingin anda transfer:", "Submit", "Batal");
	}
	if(textid == VR_ATMTD[playerid][43])// Log Out
	{
		HideATMTD(playerid);
	}
	// Inventory
	for(new x; x < MAX_INVENTORY; x++)
	{
		if(textid == inv::box[playerid][x])
		{
			new Old = AccountData[playerid][pSelectItem];
			
			if(InventoryData[playerid][x][invExists])
			{
				UnselectItem(playerid);
				SelectItem(playerid, x);
			}
			// else
			// {
			// 	PlayerPlaySound(playerid, 1052, 0, 0, 0);
			// 	if(Old != -1 && InventoryData[playerid][Old][invExists])
			// 	{
			// 		if(InventoryData[playerid][x][invExists])
			// 			return 0;
					
			// 		MoveItemToNewSlot(playerid, Old, x);
			// 		UnselectItem(playerid);
					
			// 		AccountData[playerid][pSelectItem] = -1;
			// 	}
			// }
			break;
		}
	}
	if(textid == ChoseKarakter[playerid][0]) //karakter1
	{
		if(PlayerChar[playerid][0][0] == EOS)
		{
			Register(playerid);
			HideMenuKarakter(playerid);
			for(new i = 0; i < 5; i++)
			{
				CreateCharStepDone[playerid][i] = false;
			}
			return 1;
		}
		AccountData[playerid][pChar] = 0;
		SetPlayerSkin(playerid, CharSkin[playerid][AccountData[playerid][pChar]]);
		ClearAnimations(playerid);
		SetTimerEx("AnimChar", 500, false, "d", playerid);
        //InterpolateCameraPos(playerid, 1522.5615, -2172.2637, 19.8191, 1522.5615, -2162.2637, 18.3191, 5000, CAMERA_MOVE);
        //InterpolateCameraLookAt(playerid, 1522.5615, -2159.2637, 17.8191, 1522.5615, -2159.2637, 17.8191, 5000, CAMERA_MOVE);
	}
	if(textid == ChoseKarakter[playerid][1]) //karakter2
	{
		if(PlayerChar[playerid][1][0] == EOS)
		{
			Register(playerid);
			HideMenuKarakter(playerid);
			for(new i = 0; i < 5; i++)
			{
				CreateCharStepDone[playerid][i] = false;
			}
			return 1;
		}
		
		AccountData[playerid][pChar] = 1;
		SetPlayerSkin(playerid, CharSkin[playerid][AccountData[playerid][pChar]]);
		ClearAnimations(playerid);
		SetTimerEx("AnimChar", 500, false, "d", playerid);
		//InterpolateCameraPos(playerid, 1522.5615, -2172.2637, 19.8191, 1522.5615, -2162.2637, 18.3191, 5000, CAMERA_MOVE);
        //InterpolateCameraLookAt(playerid, 1522.5615, -2159.2637, 17.8191, 1522.5615, -2159.2637, 17.8191, 5000, CAMERA_MOVE);
	}
	if(textid == ChoseKarakter[playerid][2]) //karakter3
	{
		if(PlayerChar[playerid][2][0] == EOS)
		{
			Register(playerid);
			HideMenuKarakter(playerid);
			for(new i = 0; i < 5; i++)
			{
				CreateCharStepDone[playerid][i] = false;
			}
			return 1;
		}
		AccountData[playerid][pChar] = 2;
		SetPlayerSkin(playerid, CharSkin[playerid][AccountData[playerid][pChar]]);
		ClearAnimations(playerid);
		SetTimerEx("AnimChar", 500, false, "d", playerid);
		//InterpolateCameraPos(playerid, 1522.5615, -2172.2637, 19.8191, 1522.5615, -2162.2637, 18.3191, 5000, CAMERA_MOVE);
        //InterpolateCameraLookAt(playerid, 1522.5615, -2159.2637, 17.8191, 1522.5615, -2159.2637, 17.8191, 5000, CAMERA_MOVE);
	}
	if(textid == ChoseKarakter[playerid][3]) //karakterspawn
	{
		if(AccountData[playerid][pChar] == -1)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Pilih dahulu karakternya!!");

		new pname[MAX_PLAYER_NAME];
		format(pname, sizeof pname, "%s", PlayerChar[playerid][AccountData[playerid][pChar]]);

		if(strlen(pname) < 3)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Nama karakter terlalu pendek!");

		if(strlen(pname) > 23)
			return ShowTDN(playerid, NOTIFICATION_ERROR, "Nama karakter terlalu panjang!");

		for(new i = 0; i < strlen(pname); i++)
		{
			if( !( (pname[i] >= 'A' && pname[i] <= 'Z') || (pname[i] >= 'a' && pname[i] <= 'z') || (pname[i] >= '0' && pname[i] <= '9') || (pname[i] == '_') ) )
			{
				return ShowTDN(playerid, NOTIFICATION_ERROR, "Nama karakter hanya boleh huruf, angka, dan underscore!");
			}
		}
		SetPlayerName(playerid, pname);
		PlayerSpawn[playerid] = 1;

		mysql_tquery(g_SQL, sprintf("SELECT * FROM player_characters WHERE Char_Name = '%s' LIMIT 1;", pname), "LoadPlayerData", "d", playerid);

		TogglePlayerSpectating(playerid, 0);
		HideMenuKarakter(playerid);
	}

	return 1;
}

forward AnimChar(playerid);
public AnimChar(playerid)
{
	ApplyAnimationEx(playerid, "CRIB", "PED_Console_Loop", 4.1, 1, 0, 0, 0, 0);
	return 1;
}

RemovePlayerWeapon(playerid, weaponid)
{
	// Reset the player's weapons.
	ResetPlayerWeapons(playerid);
	// Set the armed slot to zero.
	SetPlayerArmedWeapon(playerid, 0);
	// Set the weapon in the slot to zero.
	AccountData[playerid][pGuns][g_aWeaponSlots[weaponid]] = 0;
	AccountData[playerid][pACTime] = gettime() + 2;
	// Set the player's weapons.
	SetWeapons(playerid);
	return 1;
}

SetCameraData(playerid)
{
	switch(random(2))
	{
		case 0: //customer parking ganton
		{
			SetPlayerCameraPos(playerid, 902.991, -901.185, 94.368);
			SetPlayerCameraLookAt(playerid, 898.424, -899.630, 93.054);
			InterpolateCameraPos(playerid, 902.991, -901.185, 94.368, 852.659, -880.944, 88.302, 30000, CAMERA_MOVE);
		}
		case 1: // vinewood
		{
			SetPlayerCameraPos(playerid, 485.642, -2111.710, 68.742);
			SetPlayerCameraLookAt(playerid, 483.018, -2107.744, 67.201);
			InterpolateCameraPos(playerid, 485.642, -2111.710, 68.742, 470.870, -2081.438, 61.609, 25000, CAMERA_MOVE);
		}
	}
	return 1;
}

forward TollTD(playerid);
public TollTD(playerid)
{
	for(new i = 0; i < 22; i++)
	{
		TextDrawShowForPlayer(playerid, OpenTollTD[i]);
		SelectTextDraw(playerid, COLOR_BLUE);
	}
	TextDrawSetString(OpenTollTD[20], "Succes");
	TextDrawShowForPlayer(playerid, OpenTollTD[20]);
	TextDrawShowForPlayer(playerid, OpenTollTD[21]);

	SetTimerEx("OpenGateToll", 500, false, "d", playerid);
	return 1;
}

forward OpenGateToll(playerid);
public OpenGateToll(playerid)
{
	new i = GetPVarInt(playerid, "NearBarrierID");
	if(i != -1 && i < sizeof(BarrierInfo))
	{
		if(IsPlayerInRangeOfPoint(playerid, 8.0, BarrierInfo[i][brPos_X], BarrierInfo[i][brPos_Y], BarrierInfo[i][brPos_Z]))
		{
			if(BarrierInfo[i][brOrg] == TEAM_NONE)
			{
				if(!BarrierInfo[i][brOpen])
				{
					if(AccountData[playerid][pMoney] < 100 && !IsVehicleFaction(GetPlayerVehicleID(playerid)))
					{
						ShowTDN(playerid, NOTIFICATION_INFO, "Anda membutuhkan "YELLOW"$100"WHITE" untuk membayar Toll");
					}
					else if(IsVehicleFaction(GetPlayerVehicleID(playerid)))
					{
						// Buka barrier gratis
						MoveDynamicObject(gBarrier[i], BarrierInfo[i][brPos_X], BarrierInfo[i][brPos_Y], BarrierInfo[i][brPos_Z]+0.7, BARRIER_SPEED, 0.0, 0.0, BarrierInfo[i][brPos_A]+180);
						SetTimerEx("BarrierClose", 15000, 0, "i", i);
						BarrierInfo[i][brOpen] = true;
						ShowTDN(playerid, NOTIFICATION_INFO, "Hati hati dijalan, Pintu akan tertutup selama 15 detik");
						if(BarrierInfo[i][brForBarrierID] != -1)
						{
							new barrierid = BarrierInfo[i][brForBarrierID];
							MoveDynamicObject(gBarrier[barrierid], BarrierInfo[barrierid][brPos_X], BarrierInfo[barrierid][brPos_Y], BarrierInfo[barrierid][brPos_Z]+0.7, BARRIER_SPEED, 0.0, 0.0, BarrierInfo[barrierid][brPos_A]+180);
							BarrierInfo[barrierid][brOpen] = true;
						}
					}
					else
					{
						MoveDynamicObject(gBarrier[i], BarrierInfo[i][brPos_X], BarrierInfo[i][brPos_Y], BarrierInfo[i][brPos_Z]+0.7, BARRIER_SPEED, 0.0, 0.0, BarrierInfo[i][brPos_A]+180);
						SetTimerEx("BarrierClose", 15000, 0, "i", i);
						BarrierInfo[i][brOpen] = true;
						ShowTDN(playerid, NOTIFICATION_INFO, "Hati hati dijalan, Pintu akan tertutup selama 15 detik");
						ShowItemBox(playerid, "Removed $100", "Uang", 1212);
						TakeMoney(playerid, 100);
						if(BarrierInfo[i][brForBarrierID] != -1)
						{
							new barrierid = BarrierInfo[i][brForBarrierID];
							MoveDynamicObject(gBarrier[barrierid], BarrierInfo[barrierid][brPos_X], BarrierInfo[barrierid][brPos_Y], BarrierInfo[barrierid][brPos_Z]+0.7, BARRIER_SPEED, 0.0, 0.0, BarrierInfo[barrierid][brPos_A]+180);
							BarrierInfo[barrierid][brOpen] = true;
						}
					}
				}
			}
			else ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membuka toll ini!");
		}
	}
	ShowTollTD(playerid, false);
	DeletePVar(playerid, "NearBarrierID");
	
	return 1;
}

GetID(const name[])
{
	foreach(new i : Player)
	{
		if(!strcmp(name, AccountData[i][pName]))
			return i;
	}
	return -1;
}

forward OnS0beitDetected(playerid);
forward OnSilentAimDetected(playerid);
forward OnBypassDetected(playerid);
forward OnModsDetected(playerid);
forward OnImprovedDeagleDetected(playerid);
forward OnExtraWsDetected(playerid);

public OnS0beitDetected(playerid)
{
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    printf("[AC] S0beit Detected from %s (ID: %d)", name, playerid);

    SendClientMessage(playerid, 0xFF0000FF, "[AC] Cheating detected: S0beit. You have been kicked.");
    Kick(playerid);
    return 1;
}

public OnSilentAimDetected(playerid)
{
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    printf("[AC] Silent Aim Detected from %s (ID: %d)", name, playerid);

    SendClientMessage(playerid, 0xFF0000FF, "[AC] Cheating detected: Silent Aim. You have been kicked.");
    Kick(playerid);
    return 1;
}

public OnBypassDetected(playerid)
{
    SendClientMessage(playerid, 0xFF0000FF, "[AC] Anti-Cheat Bypass detected. You have been kicked.");
    Kick(playerid);
    return 1;
}

public OnModsDetected(playerid)
{
    SendClientMessage(playerid, 0xFF0000FF, "[AC] CLEO or illegal mod detected. You have been kicked.");
    Kick(playerid);
    return 1;
}

public OnImprovedDeagleDetected(playerid)
{
	SendClientMessage(playerid, 0xFF0000FF, "[AC] Anti-Cheat Bypass detected. You have been kicked.");
    Kick(playerid);
    return 1;
}

public OnExtraWsDetected(playerid)
{
	SendClientMessage(playerid, 0xFF0000FF, "[AC] Anti-Cheat Bypass detected. You have been kicked.");
    Kick(playerid);
    return 1;
}

public OnPlayerEnterDynamicArea(playerid, STREAMER_TAG_AREA:areaid)
{
	if(areaid == RSLeftDoorSensor)
	{
		if(!g_RSLeftDoorOpened)
		{
			g_RSLeftDoorOpened = true;
			MoveDynamicObject(RSDoor[0], 1337.177612, 745.832702, 9.912506, 0.6, 0.000000, 0.000000, 270.000000);
			MoveDynamicObject(RSDoor[1], 1337.207641, 739.822937, 9.912506, 0.6, 0.000000, 0.000000, 90.000000);
		}
	}
	return 1;
}

public OnPlayerLeaveDynamicArea(playerid, STREAMER_TAG_AREA:areaid)
{
	if(areaid == RSLeftDoorSensor)
	{
		if(g_RSLeftDoorOpened)
		{
			g_RSLeftDoorOpened = false;
			MoveDynamicObject(RSDoor[0], 1337.177612, 744.322692, 9.912506, 0.6, 0.000000, 0.000000, 270.000000);
			MoveDynamicObject(RSDoor[1], 1337.207641, 741.302856, 9.912506, 0.6, 0.000000, 0.000000, 90.000000);		
		}
	}
	return 1;
}

forward OnPlayerStartPool(playerid);
public OnPlayerStartPool(playerid)
{
	InPool[playerid] = true;
	AccountData[playerid][pGuns][g_aWeaponSlots[7]] = 7;
	return 1;
}

forward OnPlayerStopPool(playerid);
public OnPlayerStopPool(playerid)
{
	InPool[playerid] = false;
	ResetWeapons(playerid);
	return 1;
}

stock LoadPlayerJewelryHackTD(playerid)
{
    JewelryHackPTD[playerid][0] = CreatePlayerTextDraw(playerid, 192.000000, 133.000000, "");
    PlayerTextDrawFont(playerid, JewelryHackPTD[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, JewelryHackPTD[playerid][0], 0.179166, 1.149999);
    PlayerTextDrawTextSize(playerid, JewelryHackPTD[playerid][0], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, JewelryHackPTD[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, JewelryHackPTD[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, JewelryHackPTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, JewelryHackPTD[playerid][0], 12458495);
    PlayerTextDrawBackgroundColor(playerid, JewelryHackPTD[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, JewelryHackPTD[playerid][0], 50);
    PlayerTextDrawUseBox(playerid, JewelryHackPTD[playerid][0], 0);
    PlayerTextDrawSetProportional(playerid, JewelryHackPTD[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, JewelryHackPTD[playerid][0], 0);

    JewelryHackPTD[playerid][8] = CreatePlayerTextDraw(playerid, 192.000000, 133.000000, "");
    PlayerTextDrawFont(playerid, JewelryHackPTD[playerid][8], 1);
    PlayerTextDrawLetterSize(playerid, JewelryHackPTD[playerid][8], 0.179166, 1.149999);
    PlayerTextDrawTextSize(playerid, JewelryHackPTD[playerid][8], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, JewelryHackPTD[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, JewelryHackPTD[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, JewelryHackPTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, JewelryHackPTD[playerid][8], 12458495);
    PlayerTextDrawBackgroundColor(playerid, JewelryHackPTD[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, JewelryHackPTD[playerid][8], 50);
    PlayerTextDrawUseBox(playerid, JewelryHackPTD[playerid][8], 0);
    PlayerTextDrawSetProportional(playerid, JewelryHackPTD[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, JewelryHackPTD[playerid][8], 0);

    JewelryHackPTD[playerid][1] = CreatePlayerTextDraw(playerid, 192.000000, 146.000000, "");
    PlayerTextDrawFont(playerid, JewelryHackPTD[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, JewelryHackPTD[playerid][1], 0.179166, 1.149999);
    PlayerTextDrawTextSize(playerid, JewelryHackPTD[playerid][1], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, JewelryHackPTD[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, JewelryHackPTD[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, JewelryHackPTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, JewelryHackPTD[playerid][1], 12458495);
    PlayerTextDrawBackgroundColor(playerid, JewelryHackPTD[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, JewelryHackPTD[playerid][1], 50);
    PlayerTextDrawUseBox(playerid, JewelryHackPTD[playerid][1], 0);
    PlayerTextDrawSetProportional(playerid, JewelryHackPTD[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, JewelryHackPTD[playerid][1], 0);

    JewelryHackPTD[playerid][2] = CreatePlayerTextDraw(playerid, 192.000000, 160.000000, "");
    PlayerTextDrawFont(playerid, JewelryHackPTD[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, JewelryHackPTD[playerid][2], 0.179166, 1.149999);
    PlayerTextDrawTextSize(playerid, JewelryHackPTD[playerid][2], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, JewelryHackPTD[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, JewelryHackPTD[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, JewelryHackPTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, JewelryHackPTD[playerid][2], 12458495);
    PlayerTextDrawBackgroundColor(playerid, JewelryHackPTD[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, JewelryHackPTD[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, JewelryHackPTD[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, JewelryHackPTD[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, JewelryHackPTD[playerid][2], 0);

    JewelryHackPTD[playerid][3] = CreatePlayerTextDraw(playerid, 192.000000, 174.000000, "");
    PlayerTextDrawFont(playerid, JewelryHackPTD[playerid][3], 1);
    PlayerTextDrawLetterSize(playerid, JewelryHackPTD[playerid][3], 0.179166, 1.149999);
    PlayerTextDrawTextSize(playerid, JewelryHackPTD[playerid][3], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, JewelryHackPTD[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, JewelryHackPTD[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, JewelryHackPTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, JewelryHackPTD[playerid][3], 12458495);
    PlayerTextDrawBackgroundColor(playerid, JewelryHackPTD[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, JewelryHackPTD[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, JewelryHackPTD[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, JewelryHackPTD[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, JewelryHackPTD[playerid][3], 0);

    JewelryHackPTD[playerid][4] = CreatePlayerTextDraw(playerid, 192.000000, 189.000000, "");
    PlayerTextDrawFont(playerid, JewelryHackPTD[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, JewelryHackPTD[playerid][4], 0.179166, 1.149999);
    PlayerTextDrawTextSize(playerid, JewelryHackPTD[playerid][4], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, JewelryHackPTD[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, JewelryHackPTD[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, JewelryHackPTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, JewelryHackPTD[playerid][4], 12458495);
    PlayerTextDrawBackgroundColor(playerid, JewelryHackPTD[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, JewelryHackPTD[playerid][4], 50);
    PlayerTextDrawUseBox(playerid, JewelryHackPTD[playerid][4], 0);
    PlayerTextDrawSetProportional(playerid, JewelryHackPTD[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, JewelryHackPTD[playerid][4], 0);

    JewelryHackPTD[playerid][5] = CreatePlayerTextDraw(playerid, 192.000000, 203.000000, "");
    PlayerTextDrawFont(playerid, JewelryHackPTD[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, JewelryHackPTD[playerid][5], 0.179166, 1.149999);
    PlayerTextDrawTextSize(playerid, JewelryHackPTD[playerid][5], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, JewelryHackPTD[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, JewelryHackPTD[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, JewelryHackPTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, JewelryHackPTD[playerid][5], 12458495);
    PlayerTextDrawBackgroundColor(playerid, JewelryHackPTD[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, JewelryHackPTD[playerid][5], 50);
    PlayerTextDrawUseBox(playerid, JewelryHackPTD[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, JewelryHackPTD[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, JewelryHackPTD[playerid][5], 0);

    JewelryHackPTD[playerid][6] = CreatePlayerTextDraw(playerid, 192.000000, 218.000000, ""); //status
    PlayerTextDrawFont(playerid, JewelryHackPTD[playerid][6], 1);
    PlayerTextDrawLetterSize(playerid, JewelryHackPTD[playerid][6], 0.179166, 1.149999);
    PlayerTextDrawTextSize(playerid, JewelryHackPTD[playerid][6], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, JewelryHackPTD[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, JewelryHackPTD[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, JewelryHackPTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, JewelryHackPTD[playerid][6], 12458495);
    PlayerTextDrawBackgroundColor(playerid, JewelryHackPTD[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, JewelryHackPTD[playerid][6], 50);
    PlayerTextDrawUseBox(playerid, JewelryHackPTD[playerid][6], 0);
    PlayerTextDrawSetProportional(playerid, JewelryHackPTD[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, JewelryHackPTD[playerid][6], 0);

    JewelryHackPTD[playerid][7] = CreatePlayerTextDraw(playerid, 196.000000, 279.000000, "");
    PlayerTextDrawFont(playerid, JewelryHackPTD[playerid][7], 1);
    PlayerTextDrawLetterSize(playerid, JewelryHackPTD[playerid][7], 0.179166, 1.149999);
    PlayerTextDrawTextSize(playerid, JewelryHackPTD[playerid][7], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, JewelryHackPTD[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, JewelryHackPTD[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, JewelryHackPTD[playerid][7], 1);
    PlayerTextDrawColor(playerid, JewelryHackPTD[playerid][7], 353703423);
    PlayerTextDrawBackgroundColor(playerid, JewelryHackPTD[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, JewelryHackPTD[playerid][7], 50);
    PlayerTextDrawUseBox(playerid, JewelryHackPTD[playerid][7], 0);
    PlayerTextDrawSetProportional(playerid, JewelryHackPTD[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, JewelryHackPTD[playerid][7], 0);
}

forward PesanOtomatisNabil();
public PesanOtomatisNabil()
{
    new hour, minute, second;
    gettime(hour, minute, second);
    new string[256];

    if(hour >= 3 && hour < 5) 
    {
        format(string, sizeof(string), "{00FFFF}[NABIL] {FFFFFF}Waktunya sahur guys! Makan yang bener biar kuat narik di kota nanti siang.");
    }
    else if(hour >= 5 && hour < 11) 
    {
        format(string, sizeof(string), "{00FFFF}[NABIL] {FFFFFF}Selamat pagi! Baru mulai puasa jangan udah nanya kapan imsak ya, semangat!");
    }
    else if(hour >= 11 && hour < 15) 
    {
        format(string, sizeof(string), "{00FFFF}[NABIL] {FFFFFF}Jam kritis nih, liat botol minum di dashboard berasa liat osis. Tahan ya, jangan mokel!");
    }
    else if(hour >= 15 && hour < 18) 
    {
        format(string, sizeof(string), "{00FFFF}[NABIL] {FFFFFF}Dah sore, kuy ngabuburit keliling kota! Yang penting jangan ngerob pas lagi nunggu buka ya.");
    }
    else if(hour >= 18 && hour < 19) 
    {
        format(string, sizeof(string), "{00FFFF}[NABIL] {FFFFFF}Selamat berbuka puasa! Jangan lupa minum yang manis-manis, asal jangan janji manis mantan.");
    }
    else if(hour >= 19 && hour < 23) 
    {
        format(string, sizeof(string), "{00FFFF}[NABIL] {FFFFFF}Habis kenyang jangan lupa istirahat atau lanjut RP, biar besok makin semangat puasanya!");
    }
    else // Jam 11 malam keatas (00-02 subuh)
    {
        format(string, sizeof(string), "{00FFFF}[NABIL] {FFFFFF}Sudah larut malam, yang mau tidur silakan, yang mau begadang nunggu sahur jangan lupa jaga kesehatan.");
    }

    SendClientMessageToAll(-1, string);
    return 1;
}
stock SendDiscordWebhook(url[], message[])
{
    new content[1024];
    format(content, sizeof(content), "content=%s", message);
    HTTP(0, HTTP_POST, url, content, "OnWebhookResponse");
    return 1;
}

forward OnWebhookResponse(index, response_code, data[]);
public OnWebhookResponse(index, response_code, data[])
{
    return 1;
}
