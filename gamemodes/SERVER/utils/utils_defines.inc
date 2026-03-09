#define TEXT_GAMEMODE	"DTRP NEW ERA"
#define TEXT_WEBURL		"https://discord.gg/Au3eycytXP"
#define TEXT_LANGUAGE	"Bahasa Indonesia"
#define SERVER_BOT      "District  Security"
#define SERVER_NAME     "District "
    

#define		MYSQL_HOST 			"167.71.197.62"
#define		MYSQL_USER 			"u10_kvfaZHayte"
#define		MYSQL_PASSWORD 		"daG.ffSZHdTZmStA2zfW@yo."
#define		MYSQL_DATABASE 		"s10_hapy"


// #define		MYSQL_HOST 			"localhost"
// #define		MYSQL_USER 			"root"
// #define		MYSQL_PASSWORD 		""
// #define		MYSQL_DATABASE 		"rayyzix"

#define Loop(%0,%1,%2) for(new %0 = %2; %0 < %1; %0++)
#define GetUCPSQLID(%0)                 AccountData[%0][pID]
#define GetAdminLevel(%0)               AccountData[%0][pAdmin]
#define CheckAdmin(%0,%1)               AccountData[%0][pAdmin] < %1
#define AdminLevel(%0,%1)               AccountData[%0][pAdmin] == %1
#define GetAdminName(%0)                AccountData[%0][pAdminname]
#define GetUCPName(%0)                  AccountData[%0][pUCP]

#define GetPlayerVIPLevel(%0)           AccountData[%0][pVip]
#define GetPlayerJob(%0)                AccountData[%0][pJob]
#define GetPlayerFaction(%0)            AccountData[%0][pFaction]
#define IsPlayerInjured(%0)             AccountData[%0][pInjured]
#define InfoBatal(%0)                   ShowTDN(%0, NOTIFICATION_INFO, "Anda membatalkan pilihan!")
#define GetTotalWeightStatus(%0)        AccountData[%0][pBeratItem]
#define GetTotalWeightFloat(%0)        AccountData[%0][pBeratItem]
#define GetTotalWeightGudang(%0)        AccountData[%0][pGudangCapacity]

#define Info(%1,%2) SendClientMessageEx(%1, 0x2E8B57AA, "[Info]: "WHITE""%2)
#define Success(%1,%2) SendClientMessageEx(%1, X11_LIGHTGREEN, "[Success]: "WHITE""%2)
#define Syntax(%1,%2) SendClientMessageEx(%1, X11_GRAY, "[Syntax]: "WHITE""%2)
#define Error(%1,%2) SendClientMessageEx(%1, 0x8B000000, "[Error]: "WHITE""%2)
#define Warning(%1,%2) SendClientMessageEx(%1, X11_DARKORANGE, "[Warning]: "WHITE""%2)
#define SendCustomMessage(%0,%1,%2)     SendClientMessageEx(%0, 0xFF9999FF, %1": "WHITE""%2)

#define function%0(%1) forward %0(%1); public %0(%1)
#define forex(%0,%1) for(new %0 = 0; %0 != %1; %0++)
#define PermissionError(%0) ShowTDN(%0, NOTIFICATION_ERROR, "Anda tidak memiliki akses untuk menggunakan perintah tersebut!")

#define SM(%0,%1) \
    SendClientMessageEx(%0, COLOR_YELLOW, "»"WHITE_E" "%1)

#define PRESSED(%0) \
    (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

//Converter
#define minplus(%1) \
        (((%1) < 0) ? (-(%1)) : ((%1)))

// AntiCaps
#define UpperToLower(%1) for( new ToLowerChar; ToLowerChar < strlen( %1 ); ToLowerChar ++ ) if ( %1[ ToLowerChar ]> 64 && %1[ ToLowerChar ] < 91 ) %1[ ToLowerChar ] += 32

// Function
#define JavaTR:%0(%1) forward %0(%1); public %0(%1)
#define FUNC::%0(%1) forward %0(%1); public %0(%1)
#define VRRP::%0(%1) forward %0(%1); public %0(%1)

// player_bans
const BAN_MASK = (-1 << (32 - (/*this is the CIDR ip detection range [def: 26]*/26)));

#define MAX_ACTORSS   300
#define LIMIT_PER_PLAYER        3

#define MAX_WORKSHOP_INT        8000
#define MAX_WORKSHOP            100
#define MAX_WORKSHOP_EMPLOYEE   4

#define JOB_NONE           0
#define JOB_BUS            1
#define JOB_MINER          2
#define JOB_LUMBERJACK     3
#define JOB_BUTCHER        4
#define JOB_TAILOR         5
#define JOB_OILMAN         6
#define JOB_FISHERMAN      7
#define JOB_MILKER         8
#define JOB_FARMER         9
#define JOB_KARGO          10
#define JOB_RECYCLER       11
#define JOB_TRASHMASTER    12
#define JOB_DRIVER_MIXERS  13

#define FACTION_NONE            0
#define FACTION_POLISI          1
#define FACTION_PEMERINTAH      2
#define FACTION_EMS             3
#define FACTION_TRANS           4
#define FACTION_BENGKEL         5
#define FACTION_PEDAGANG        6 
#define FACTION_GOJEK           7

#define MAX_LOCKER 256

#define RETURN_INVALID_VEHICLE_ID   65535
#define SOUND_LOCK_CAR_DOOR 24600
#define MIN_VIRTUAL_WORLD				(1000000)
#define MAX_VIRTUAL_WORLD				(1200000)
#define MAX_CHARS 3

#define MAX_GARBAGE_BINS                (50)

#define MAX_PRIVATE_VEHICLE 3000
#define MAX_VEHICLE_OBJECT  10

#define OBJECT_TYPE_BODY 1
#define OBJECT_TYPE_TEXT 2
#define OBJECT_TYPE_LIGHT 3

#define MAX_PLAYER_VEHICLE 3
#define MAX_FUEL_FULL   100
#define MAX_WEAPON_SLOT 13

#define MAX_BUS_ROUTE   5   // contoh max 5 rute bus
#define MAX_BUS_CPS     50  // max checkpoint per rute

#define SERVER_TEXTDRAW_COLOR 293063423

#define MAX_FAMILIES 30
/*Stuff Bodypart*/
#define BODY_PART_TORSO                 (3)
#define BODY_PART_GROIN                 (4)
#define BODY_PART_RIGHT_ARM             (5)
#define BODY_PART_LEFT_ARM              (6)
#define BODY_PART_RIGHT_LEG             (7)
#define BODY_PART_LEFT_LEG              (8)
#define BODY_PART_HEAD                  (9)

/* Weed Stuufs */
#define MAX_WEED                        1000
#define JOB_SLOT                    (4)

/* Modshop */
#define MODEL_SELECTION_Loco    14
#define MODEL_SELECTION_Waa     15
#define MODEL_SELECTION_Transfender     16

#define LIMIT_PER_PLAYER 3
#define MAX_DYNAMIC_ROBBERY 100

#define MAX_TWEETS_PER_PAGE 5

stock SetPlayerSpeed(playerid, Float:speed, bool:kmh = true)
{
    new Float:pPos[4];
    
    GetPlayerVelocity(playerid,pPos[0],pPos[1],pPos[2]);
    GetPlayerFacingAngle(playerid, pPos[3]);
    speed = (kmh ? (speed / 136.666667) : (speed / 85.4166672));
    return SetVehicleVelocity(vehicleid, speed * floatsin(-vPos[3], degrees), speed * floatcos(-vPos[3], degrees), (vPos[2]-0.005));
}
stock Float:GetPlayerOnFootSpeed(playerid, bool:kmh = true, Float:velx = 0.0, Float:vely = 0.0, Float:velz = 0.0)
{
    if( velx == 0.0 && vely == 0.0 && velz == 0.0)
        GetPlayerVelocity(playerid, velx, vely, velz);

    return float(floatround((floatsqroot(((velx * velx) + (vely * vely)) + (velz * velz)) * (kmh ? (136.666667) : (85.4166672))), floatround_round));
}

FUNC::Float:GetXYInFrontOfPlayer(playerid, &Float:X, &Float:Y, Float:distance)
{
	new Float:A;
	GetPlayerPos(playerid, X, Y, A);

	if(IsPlayerInAnyVehicle(playerid)) GetVehicleZAngle(GetPlayerVehicleID(playerid), A);
	else GetPlayerFacingAngle(playerid, A);

	X += (distance * floatsin(-A, degrees));
	Y += (distance * floatcos(-A, degrees));

	return A;
}

stock Float:cache_get_field_float(row, const field_name[])
{
    new
        str[16];

    cache_get_field_content(row, field_name, str, sizeof(str));
    return floatstr(str);
}

cache_get_data(&rows, &fields)
{
	cache_get_row_count(rows);//lastupdate
	cache_get_field_count(fields);
	//cache_get_result_count(dest);
}

cache_get_field_int(row, const field_name[])
{
    new val;
    cache_get_value_name_int(row, field_name, val);
    return val;
}

cache_get_field_content(row, const field_name[], destination[], max_len = sizeof(destination))
{
    cache_get_value_name(row, field_name, destination, max_len);
}

