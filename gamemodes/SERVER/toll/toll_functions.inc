#include <YSI\y_hooks>

#define BARRIER_SPEED 	0.100
#define TEAM_NONE       (0)
#define Toll(%1,%2) SendClientMessage(%1, COLOR_YELLOW , "[TOLL]: "WHITE_E""%2)

new gBarrier[10];

enum brInfo
{
	brOrg,
    Float:brPos_X,
    Float:brPos_Y,
    Float:brPos_Z,
    Float:brPos_A,
    bool:brOpen,
    brForBarrierID
};

new BarrierInfo[10][brInfo] =
{
    {TEAM_NONE,     55.746662,  	-1534.411254,  	4.082062,   83.099998,    false, -1},
	{TEAM_NONE, 	56.293292,  	-1529.893798,  	4.082062,   263.100006,    false, -1},
	{TEAM_NONE, 	537.941406,  	459.611785,  	18.059673,  34.500091,     false, -1},
	{TEAM_NONE, 	499.369598,  	490.981292,  	18.059673,  214.500091,    false, -1},
	{TEAM_NONE, 	-174.672866, 	315.192077, 	11.058124, 	-14.799996, 	false, -1},
	{TEAM_NONE, 	-178.089721, 	356.009002, 	11.048127,	165.199996, 	false, -1},
	{TEAM_NONE, 	574.371520, 	-1129.966552,   25.099832, 	67.300003, 		false, -1},
	{TEAM_NONE, 	566.661437, 	-1151.206298,  	26.089841, 	67.300003, 		false, -1},
	{TEAM_NONE, 	1735.220214, 	498.605895, 	28.243370, 	159.199981, 	false, -1},
	{TEAM_NONE, 	1726.414550, 	501.951049, 	28.243370, 	339.199981, 	false, -1}
};

function BarrierClose(barrier)
{
	BarrierInfo[barrier][brOpen] = false;
	MoveDynamicObject(gBarrier[barrier],BarrierInfo[barrier][brPos_X],BarrierInfo[barrier][brPos_Y],BarrierInfo[barrier][brPos_Z]+0.75,BARRIER_SPEED,0.0,90.0,BarrierInfo[barrier][brPos_A]+180);
	new barrierid = BarrierInfo[barrier][brForBarrierID];
	if(barrierid != -1)
	{
		BarrierInfo[barrierid][brOpen] = false;
		MoveDynamicObject(gBarrier[barrierid],BarrierInfo[barrierid][brPos_X],BarrierInfo[barrierid][brPos_Y],BarrierInfo[barrierid][brPos_Z]+0.75,BARRIER_SPEED,0.0,90.0,BarrierInfo[barrierid][brPos_A]+180);
	}
	return true;
}

ShiftCords(style, &Float:x, &Float:y, Float:a, Float:distance)
{
	switch(style)
	{
	case 0:
		{
			x += (distance * floatsin(-a, degrees));
			y += (distance * floatcos(-a, degrees));
		}
	case 1:
		{
			x -= (distance * floatsin(-a, degrees));
			y -= (distance * floatcos(-a, degrees));
		}
	default: return false;
	}
	return true;
}

MuchNumber(...)
{
	new count = numargs(), maxnum;
	for(new i; i < count; i ++)
	{
		new temp = getarg(i);
		if(temp > maxnum) maxnum = temp;
	}
	return maxnum;
}

hook OnGameModeInit()
{
	CreateDynamic3DTextLabel(""DEEPSKYBLUE1"[Gerbang Toll Point]\n"LIGHTGREY"Gunakan tombol "YELLOW"klakson"LIGHTGREY" disini unuk membuka gerbang!", -1, 60.1277, -1527.3390, 4.5334 + 0.55, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
	CreateDynamic3DTextLabel(""DEEPSKYBLUE1"[Gerbang Toll Point]\n"LIGHTGREY"Gunakan tombol "YELLOW"klakson"LIGHTGREY" disini unuk membuka gerbang!", -1, 50.6772, -1537.1597, 4.7119 + 0.55, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
	CreateDynamic3DTextLabel(""DEEPSKYBLUE1"[Gerbang Toll Point]\n"LIGHTGREY"Gunakan tombol "YELLOW"klakson"LIGHTGREY" disini unuk membuka gerbang!", -1, 537.2600, 454.4145, 18.5988 + 0.55, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
	CreateDynamic3DTextLabel(""DEEPSKYBLUE1"[Gerbang Toll Point]\n"LIGHTGREY"Gunakan tombol "YELLOW"klakson"LIGHTGREY" disini unuk membuka gerbang!", -1, 500.0012, 496.6064, 18.5911 + 0.55, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
	CreateDynamic3DTextLabel(""DEEPSKYBLUE1"[Gerbang Toll Point]\n"LIGHTGREY"Gunakan tombol "YELLOW"klakson"LIGHTGREY" disini unuk membuka gerbang!", -1, -173.5992, 358.3904, 12.1705 + 0.55, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
	CreateDynamic3DTextLabel(""DEEPSKYBLUE1"[Gerbang Toll Point]\n"LIGHTGREY"Gunakan tombol "YELLOW"klakson"LIGHTGREY" disini unuk membuka gerbang!", -1, -179.0582, 312.7829, 12.1705 + 0.55, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
	CreateDynamic3DTextLabel(""DEEPSKYBLUE1"[Gerbang Toll Point]\n"LIGHTGREY"Gunakan tombol "YELLOW"klakson"LIGHTGREY" disini unuk membuka gerbang!", -1, 579.8929, -1136.4073, 25.5710 + 0.55, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
	CreateDynamic3DTextLabel(""DEEPSKYBLUE1"[Gerbang Toll Point]\n"LIGHTGREY"Gunakan tombol "YELLOW"klakson"LIGHTGREY" disini unuk membuka gerbang!", -1, 559.2356, -1151.5155, 27.5269 + 0.55, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
	CreateDynamic3DTextLabel(""DEEPSKYBLUE1"[Gerbang Toll Point]\n"LIGHTGREY"Gunakan tombol "YELLOW"klakson"LIGHTGREY" disini unuk membuka gerbang!", -1, 1736.3079, 491.6081, 29.4648 + 0.55, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
	CreateDynamic3DTextLabel(""DEEPSKYBLUE1"[Gerbang Toll Point]\n"LIGHTGREY"Gunakan tombol "YELLOW"klakson"LIGHTGREY" disini unuk membuka gerbang!", -1, 1724.9844, 508.3641, 28.9483 + 0.55, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
	return 1;
}

// CMD:opengate(playerid, params[])
// {
// 	if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
// 	{
// 		new forcount = MuchNumber(sizeof(BarrierInfo));
// 		for(new i;i < forcount;i ++)
// 		{
// 			if(i < sizeof(BarrierInfo))
// 			{
// 				if(IsPlayerInRangeOfPoint(playerid,8,BarrierInfo[i][brPos_X],BarrierInfo[i][brPos_Y],BarrierInfo[i][brPos_Z]))
// 				{
// 					if(BarrierInfo[i][brOrg] == TEAM_NONE)
// 					{
// 						if(!BarrierInfo[i][brOpen])
// 						{
// 							if(AccountData[playerid][pMoney] < 5)
// 							{
// 								Toll(playerid, "Uangmu tidak cukup untuk membayar toll");
// 							}
// 							else
// 							{
// 								MoveDynamicObject(gBarrier[i],BarrierInfo[i][brPos_X],BarrierInfo[i][brPos_Y],BarrierInfo[i][brPos_Z]+0.7,BARRIER_SPEED,0.0,0.0,BarrierInfo[i][brPos_A]+180);
// 								SetTimerEx("BarrierClose",15000,0,"i",i);
// 								BarrierInfo[i][brOpen] = true;
// 								Toll(playerid, "Cepat!!! Toll akan menutup Kembali setelah 15 detik");
// 								GiveMoney(playerid, -5);
// 								if(BarrierInfo[i][brForBarrierID] != -1)
// 								{
// 									new barrierid = BarrierInfo[i][brForBarrierID];
// 									MoveDynamicObject(gBarrier[barrierid],BarrierInfo[barrierid][brPos_X],BarrierInfo[barrierid][brPos_Y],BarrierInfo[barrierid][brPos_Z]+0.7,BARRIER_SPEED,0.0,0.0,BarrierInfo[barrierid][brPos_A]+180);
// 									BarrierInfo[barrierid][brOpen] = true;

// 								}
// 							}
// 						}
// 					}
// 					else Toll(playerid, "Kamu tidak bisa membuka pintu Toll ini!");
// 					break;
// 				}
// 			}
// 		}
// 	}
// 	return true;
// }