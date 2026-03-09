#include <YSI\y_hooks>

new pTakeBatuTimer[MAX_PLAYERS] = {-1, ...},
	pCuciBatuTimer[MAX_PLAYERS] = {-1, ...},
	pLeburBatuTimer[MAX_PLAYERS] = {-1, ...};

new pCount1[MAX_PLAYERS] = {-1, ...},
	pCount2[MAX_PLAYERS] = {-1, ...},
	pCount3[MAX_PLAYERS] = {-1, ...},
	pCount4[MAX_PLAYERS] = {-1, ...},
	pCount5[MAX_PLAYERS] = {-1, ...},
	pCount6[MAX_PLAYERS] = {-1, ...},
	pCount7[MAX_PLAYERS] = {-1, ...},
	pCount8[MAX_PLAYERS] = {-1, ...},
	pCount9[MAX_PLAYERS] = {-1, ...},
	pCount10[MAX_PLAYERS] = {-1, ...};

enum STUFFMINER
{
	STREAMER_TAG_AREA:TakeBatuArea[10],
	STREAMER_TAG_AREA:LeburBatuArea[3],
	STREAMER_TAG_AREA:CuciBatuArea,
	STREAMER_TAG_3D_TEXT_LABEL:LeburTextLabel[3],
	STREAMER_TAG_MAP_ICON:MinerIcon[3],
};
new PlayerMinerVars[MAX_PLAYERS][STUFFMINER];

VRRP::MinerLabelMap(playerid)
{
	UnloadMinerLabelMap(playerid);

	PlayerMinerVars[playerid][LeburTextLabel][0] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Meleburkan Batu", -1, 2152.3289, -2263.5745, 13.3000+0.4, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, playerid);
	PlayerMinerVars[playerid][LeburTextLabel][1] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Meleburkan Batu", -1, 2147.9492, -2263.9167, 13.2982+0.4, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, playerid);
	PlayerMinerVars[playerid][LeburTextLabel][2] = CreateDynamic3DTextLabel(""GREEN"[Y]"WHITE" Meleburkan Batu", -1, 2152.1406, -2267.9675, 13.3071+0.4, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, -1, -1, playerid);

	PlayerMinerVars[playerid][MinerIcon][0] = CreateDynamicMapIcon(686.5589, 896.8207, - 39.5803, 11, -1, 0, 0, playerid, 9999.0, MAPICON_GLOBAL, -1, 1);
	PlayerMinerVars[playerid][MinerIcon][1] = CreateDynamicMapIcon(-412.7031, 1197.8976, 2.2932, 11, -1, 0, 0, playerid, 9999.0, MAPICON_GLOBAL, -1, 1);
	PlayerMinerVars[playerid][MinerIcon][2] = CreateDynamicMapIcon(2193.07, -2253.17,  13.54, 11, -1, 0, 0, playerid, 9999.0, MAPICON_GLOBAL, -1, 1);

	PlayerMinerVars[playerid][TakeBatuArea][0] = CreateDynamicSphere(672.875183, 932.473022, -39.548580, 2.0, -1, -1, playerid);
	PlayerMinerVars[playerid][TakeBatuArea][1] = CreateDynamicSphere(678.368896, 931.528930, -38.935825, 2.0, -1, -1, playerid);
	PlayerMinerVars[playerid][TakeBatuArea][2] = CreateDynamicSphere(683.770935, 928.128540, -38.488441, 2.0, -1, -1, playerid);
	PlayerMinerVars[playerid][TakeBatuArea][3] = CreateDynamicSphere(688.441589, 922.608642, -38.894218, 2.0, -1, -1, playerid);
	PlayerMinerVars[playerid][TakeBatuArea][4] = CreateDynamicSphere(691.216613, 915.921630, -37.704727, 2.0, -1, -1, playerid);
	PlayerMinerVars[playerid][TakeBatuArea][5] = CreateDynamicSphere(695.673767, 909.328308, -37.277084, 2.0, -1, -1, playerid);
	PlayerMinerVars[playerid][TakeBatuArea][6] = CreateDynamicSphere(699.634948, 903.249511, -37.220737, 2.0, -1, -1, playerid);
	PlayerMinerVars[playerid][TakeBatuArea][7] = CreateDynamicSphere(702.175415, 896.462219, -36.207241, 2.0, -1, -1, playerid);
	PlayerMinerVars[playerid][TakeBatuArea][8] = CreateDynamicSphere(701.845764, 890.099670, -36.374118, 2.0, -1, -1, playerid);
	PlayerMinerVars[playerid][TakeBatuArea][9] = CreateDynamicSphere(700.389465, 883.717895, -36.471256, 2.0, -1, -1, playerid);

	PlayerMinerVars[playerid][LeburBatuArea][0] = CreateDynamicSphere(2152.4473, -2263.5190, 13.3000, 2.5, -1, -1, playerid);
	PlayerMinerVars[playerid][LeburBatuArea][1] = CreateDynamicSphere(2152.1008, -2268.0110, 13.3072, 2.5, -1, -1, playerid);
	PlayerMinerVars[playerid][LeburBatuArea][2] = CreateDynamicSphere(2147.9453, -2263.9194, 13.2982, 2.5, -1, -1, playerid);

	PlayerMinerVars[playerid][CuciBatuArea] = CreateDynamicRectangle(-438.20001220703125, 1188.3999786376953, -416.20001220703125, 1226.3999786376953, -1, -1, playerid);
}

VRRP::UnloadMinerLabelMap(playerid)
{
	for(new i = 0; i < 3; i ++)
	{
		if(IsValidDynamicMapIcon(PlayerMinerVars[playerid][MinerIcon][i]))
			DestroyDynamicMapIcon(PlayerMinerVars[playerid][MinerIcon][i]);
		PlayerMinerVars[playerid][MinerIcon][i] = STREAMER_TAG_MAP_ICON:INVALID_STREAMER_ID;
	}

	for(new i = 0; i < 10; i ++)
	{
		if(IsValidDynamicArea(PlayerMinerVars[playerid][TakeBatuArea][i]))
			DestroyDynamicArea(PlayerMinerVars[playerid][TakeBatuArea][i]);
		PlayerMinerVars[playerid][TakeBatuArea][i] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	}

	for(new i = 0; i < 3; i ++)
	{
		if(IsValidDynamicArea(PlayerMinerVars[playerid][LeburBatuArea][i]))
			DestroyDynamicArea(PlayerMinerVars[playerid][LeburBatuArea][i]);
		PlayerMinerVars[playerid][LeburBatuArea][i] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;
	}

	for(new i = 0; i < 3; i ++)
	{
		if(IsValidDynamic3DTextLabel(PlayerMinerVars[playerid][LeburTextLabel][i]))
			DestroyDynamic3DTextLabel(PlayerMinerVars[playerid][LeburTextLabel][i]);
		PlayerMinerVars[playerid][LeburTextLabel][i] = STREAMER_TAG_3D_TEXT_LABEL:INVALID_STREAMER_ID;
	}

	if(IsValidDynamicArea(PlayerMinerVars[playerid][CuciBatuArea]))
		DestroyDynamicArea(PlayerMinerVars[playerid][CuciBatuArea]);
	PlayerMinerVars[playerid][CuciBatuArea] = STREAMER_TAG_AREA:INVALID_STREAMER_ID;

	return 1;
}

hook OnPlayerConnect(playerid)
{
	pTakeBatuTimer[playerid] = -1;
	pCuciBatuTimer[playerid] = -1;
	pLeburBatuTimer[playerid] = -1;
	return 1;
}

hook OnPlayerEnterDynArea(playerid, STREAMER_TAG_AREA:areaid)
{
	if(GetPlayerJob(playerid) == JOB_MINER && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(areaid == PlayerMinerVars[playerid][CuciBatuArea])
		{
			ShowKey(playerid, "[Y] Mencuci Batu");
		}

		if(pCount1[playerid] == -1)
		{
			if(areaid == PlayerMinerVars[playerid][TakeBatuArea][0])
			{
				ShowKey(playerid, "[Y] Ambil Batu");
			}
		}
		
		if(pCount2[playerid] == -1)
		{
			if(areaid == PlayerMinerVars[playerid][TakeBatuArea][1])
			{
				ShowKey(playerid, "[Y] Ambil Batu");
			}
		}
		
		if(pCount3[playerid] == -1)
		{
			if(areaid == PlayerMinerVars[playerid][TakeBatuArea][2])
			{
				ShowKey(playerid, "[Y] Ambil Batu");
			}
		}
		
		if(pCount4[playerid] == -1)
		{
			if(areaid == PlayerMinerVars[playerid][TakeBatuArea][3])
			{
				ShowKey(playerid, "[Y] Ambil Batu");
			}
		}
		
		if(pCount5[playerid] == -1)
		{
			if(areaid == PlayerMinerVars[playerid][TakeBatuArea][4])
			{
				ShowKey(playerid, "[Y] Ambil Batu");
			}
		}
		
		if(pCount6[playerid] == -1)
		{
			if(areaid == PlayerMinerVars[playerid][TakeBatuArea][5])
			{
				ShowKey(playerid, "[Y] Ambil Batu");
			}
		}
		
		if(pCount7[playerid] == -1)
		{
			if(areaid == PlayerMinerVars[playerid][TakeBatuArea][6])
			{
				ShowKey(playerid, "[Y] Ambil Batu");
			}
		}
		
		if(pCount8[playerid] == -1)
		{
			if(areaid == PlayerMinerVars[playerid][TakeBatuArea][7])
			{
				ShowKey(playerid, "[Y] Ambil Batu");
			}
		}
		
		if(pCount9[playerid] == -1)
		{
			if(areaid == PlayerMinerVars[playerid][TakeBatuArea][8])
			{
				ShowKey(playerid, "[Y] Ambil Batu");
			}
		}
		
		if(pCount10[playerid] == -1)
		{
			if(areaid == PlayerMinerVars[playerid][TakeBatuArea][9])
			{
				ShowKey(playerid, "[Y] Ambil Batu");
			}
		}
	}
	return 1;
}

hook OnPlayerLeaveDynArea(playerid,STREAMER_TAG_AREA:areaid)
{
	if(GetPlayerJob(playerid) == JOB_MINER)
	{
		if(areaid == PlayerMinerVars[playerid][CuciBatuArea])
		{
			HideShortKey(playerid);
		}

		for(new i = 0; i < 10; i ++)
		{
			if(areaid == PlayerMinerVars[playerid][TakeBatuArea][i])
			{
				HideShortKey(playerid);
			}
		}
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys & KEY_YES && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		if(GetPlayerJob(playerid) == JOB_MINER)
		{
			if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][0]))
			{
				if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
				if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
				if(pCount1[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pindah Ke Batu Lain! (CD: 25s)");

				AccountData[playerid][ActivityTime] = 1;
				pTakeBatuTimer[playerid] = SetTimerEx("TakeBatu", 1000, true, "d", playerid);
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENAMBANG");
				ShowProgressBar(playerid);
				ApplyAnimation(playerid, "RIOT", "RIOT_ANGRY_B", 4.1, 1, 0, 0, 0, 0, 1);
				SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.028, -0.127, 0.021, 95.800, 94.400, -85.000, 1.000, 1.000, 1.000);
			}

			if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][1]))
			{
				if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
				if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
				if(pCount2[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pindah Ke Batu Lain! (CD: 25s)");

				AccountData[playerid][ActivityTime] = 1;
				pTakeBatuTimer[playerid] = SetTimerEx("TakeBatu2", 1000, true, "d", playerid);
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENAMBANG");
				ShowProgressBar(playerid);
				ApplyAnimation(playerid, "RIOT", "RIOT_ANGRY_B", 4.1, 1, 0, 0, 0, 0, 1);
				SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.028, -0.127, 0.021, 95.800, 94.400, -85.000, 1.000, 1.000, 1.000);
			}

			if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][2]))
			{
				if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
				if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
				if(pCount3[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pindah Ke Batu Lain! (CD: 25s)");

				AccountData[playerid][ActivityTime] = 1;
				pTakeBatuTimer[playerid] = SetTimerEx("TakeBatu3", 1000, true, "d", playerid);
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENAMBANG");
				ShowProgressBar(playerid);
				ApplyAnimation(playerid, "RIOT", "RIOT_ANGRY_B", 4.1, 1, 0, 0, 0, 0, 1);
				SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.028, -0.127, 0.021, 95.800, 94.400, -85.000, 1.000, 1.000, 1.000);
			}

			if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][3]))
			{
				if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
				if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
				if(pCount4[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pindah Ke Batu Lain! (CD: 25s)");

				AccountData[playerid][ActivityTime] = 1;
				pTakeBatuTimer[playerid] = SetTimerEx("TakeBatu4", 1000, true, "d", playerid);
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENAMBANG");
				ShowProgressBar(playerid);
				ApplyAnimation(playerid, "RIOT", "RIOT_ANGRY_B", 4.1, 1, 0, 0, 0, 0, 1);
				SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.028, -0.127, 0.021, 95.800, 94.400, -85.000, 1.000, 1.000, 1.000);
			}

			if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][4]))
			{
				if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
				if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
				if(pCount5[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pindah Ke Batu Lain! (CD: 25s)");

				AccountData[playerid][ActivityTime] = 1;
				pTakeBatuTimer[playerid] = SetTimerEx("TakeBatu5", 1000, true, "d", playerid);
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENAMBANG");
				ShowProgressBar(playerid);
				ApplyAnimation(playerid, "RIOT", "RIOT_ANGRY_B", 4.1, 1, 0, 0, 0, 0, 1);
				SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.028, -0.127, 0.021, 95.800, 94.400, -85.000, 1.000, 1.000, 1.000);
			}

			if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][5]))
			{
				if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
				if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
				if(pCount6[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pindah Ke Batu Lain! (CD: 25s)");

				AccountData[playerid][ActivityTime] = 1;
				pTakeBatuTimer[playerid] = SetTimerEx("TakeBatu6", 1000, true, "d", playerid);
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENAMBANG");
				ShowProgressBar(playerid);
				ApplyAnimation(playerid, "RIOT", "RIOT_ANGRY_B", 4.1, 1, 0, 0, 0, 0, 1);
				SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.028, -0.127, 0.021, 95.800, 94.400, -85.000, 1.000, 1.000, 1.000);
			}

			if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][6]))
			{
				if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
				if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
				if(pCount7[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pindah Ke Batu Lain! (CD: 25s)");

				AccountData[playerid][ActivityTime] = 1;
				pTakeBatuTimer[playerid] = SetTimerEx("TakeBatu7", 1000, true, "d", playerid);
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENAMBANG");
				ShowProgressBar(playerid);
				ApplyAnimation(playerid, "RIOT", "RIOT_ANGRY_B", 4.1, 1, 0, 0, 0, 0, 1);
				SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.028, -0.127, 0.021, 95.800, 94.400, -85.000, 1.000, 1.000, 1.000);
			}

			if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][7]))
			{
				if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
				if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
				if(pCount8[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pindah Ke Batu Lain! (CD: 25s)");

				AccountData[playerid][ActivityTime] = 1;
				pTakeBatuTimer[playerid] = SetTimerEx("TakeBatu8", 1000, true, "d", playerid);
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENAMBANG");
				ShowProgressBar(playerid);
				ApplyAnimation(playerid, "RIOT", "RIOT_ANGRY_B", 4.1, 1, 0, 0, 0, 0, 1);
				SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.028, -0.127, 0.021, 95.800, 94.400, -85.000, 1.000, 1.000, 1.000);
			}

			if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][8]))
			{
				if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
				if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
				if(pCount9[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pindah Ke Batu Lain! (CD: 25s)");

				AccountData[playerid][ActivityTime] = 1;
				pTakeBatuTimer[playerid] = SetTimerEx("TakeBatu9", 1000, true, "d", playerid);
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENAMBANG");
				ShowProgressBar(playerid);
				ApplyAnimation(playerid, "RIOT", "RIOT_ANGRY_B", 4.1, 1, 0, 0, 0, 0, 1);
				SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.028, -0.127, 0.021, 95.800, 94.400, -85.000, 1.000, 1.000, 1.000);
			}

			if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][9]))
			{
				if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
				if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
				if(pCount10[playerid] != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pindah Ke Batu Lain! (CD: 25s)");

				AccountData[playerid][ActivityTime] = 1;
				pTakeBatuTimer[playerid] = SetTimerEx("TakeBatu10", 1000, true, "d", playerid);
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENAMBANG");
				ShowProgressBar(playerid);
				ApplyAnimation(playerid, "RIOT", "RIOT_ANGRY_B", 4.1, 1, 0, 0, 0, 0, 1);
				SetPlayerAttachedObject(playerid, 9, 19631, 6, 0.028, -0.127, 0.021, 95.800, 94.400, -85.000, 1.000, 1.000, 1.000);
			}

			// Cuci Batu
			if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][CuciBatuArea]))
			{
				if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
				if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");

				AccountData[playerid][ActivityTime] = 1;
				pCuciBatuTimer[playerid] = SetTimerEx("CuciBatu", 1000, true, "d", playerid);
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MENCUCI BATU");
				ShowProgressBar(playerid);
				ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
			}

			if(IsALeburArea(playerid))
			{
				if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
				if(IsPlayerInjured(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");

				AccountData[playerid][ActivityTime] = 1;
				pLeburBatuTimer[playerid] = SetTimerEx("LeburBatu", 1000, true, "d", playerid);
				PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MELEBUR BATU");
				ShowProgressBar(playerid);
				ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
			}
		}
	}
	return 1;
}

// ------------- Callback Miner
VRRP::TakeBatu(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(!IsValidDynamicArea(PlayerMinerVars[playerid][TakeBatuArea][0]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(!IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][0]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(Inventory_Count(playerid, "Batu Kotor") >= 25)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Batu Kotor sudah mencapai maksimal! (Max: 25)");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(IsPlayerInjured(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(GetTotalWeightStatus(playerid) >= 50)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 120)
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		
		new rands = RandomEx(1, 101), randbatu = RandomEx(1, 4);
		switch(rands)
		{
			case 1..79:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 80..90:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 91..100:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				Inventory_Add(playerid, "Material", 19843, 1);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
				ShowItemBox(playerid, "ADDED 1x", "MATERIAL", 19843);
			}
		}
		pCount1[playerid] = 25;
		HideShortKey(playerid);
        GivePlayerXP(playerid, DEFAULT_XP);
	}
	else 
	{
		AccountData[playerid][ActivityTime] += 12;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime]*99.000000/140.000000;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		PlayerPlaySound(playerid, 1135, 0, 0, 0);
		return 0;
	}
	return 1;
}

VRRP::TakeBatu2(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(!IsValidDynamicArea(PlayerMinerVars[playerid][TakeBatuArea][1]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(!IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][1]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(Inventory_Count(playerid, "Batu Kotor") >= 25)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Batu Kotor sudah mencapai maksimal! (Max: 25)");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(IsPlayerInjured(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(GetTotalWeightStatus(playerid) >= 50)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 120)
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		
		new rands = RandomEx(1, 101), randbatu = RandomEx(1, 4);
		switch(rands)
		{
			case 1..79:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 80..90:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 91..100:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				Inventory_Add(playerid, "Material", 19843, 1);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
				ShowItemBox(playerid, "ADDED 1x", "MATERIAL", 19843);
			}
		}
		pCount2[playerid] = 25;
		HideShortKey(playerid);
        GivePlayerXP(playerid, DEFAULT_XP);
	}
	else 
	{
		AccountData[playerid][ActivityTime] += 12;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime]*99.000000/140.000000;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		PlayerPlaySound(playerid, 1135, 0, 0, 0);
		return 0;
	}
	return 1;
}

VRRP::TakeBatu3(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(!IsValidDynamicArea(PlayerMinerVars[playerid][TakeBatuArea][2]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(Inventory_Count(playerid, "Batu Kotor") >= 25)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Batu Kotor sudah mencapai maksimal! (Max: 25)");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(!IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][2]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(IsPlayerInjured(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(GetTotalWeightStatus(playerid) >= 50)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 120)
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		
		new rands = RandomEx(1, 101), randbatu = RandomEx(1, 4);
		switch(rands)
		{
			case 1..79:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 80..90:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 91..100:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				Inventory_Add(playerid, "Material", 19843, 1);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
				ShowItemBox(playerid, "ADDED 1x", "MATERIAL", 19843);
			}
		}
		pCount3[playerid] = 25;
		HideShortKey(playerid);
        GivePlayerXP(playerid, DEFAULT_XP);
	}
	else 
	{
		AccountData[playerid][ActivityTime] += 12;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime]*99.000000/140.000000;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		PlayerPlaySound(playerid, 1135, 0, 0, 0);
		return 0;
	}
	return 1;
}

VRRP::TakeBatu4(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(!IsValidDynamicArea(PlayerMinerVars[playerid][TakeBatuArea][3]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(!IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][3]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(Inventory_Count(playerid, "Batu Kotor") >= 25)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Batu Kotor sudah mencapai maksimal! (Max: 25)");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(IsPlayerInjured(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(GetTotalWeightStatus(playerid) >= 50)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 120)
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		
		new rands = RandomEx(1, 101), randbatu = RandomEx(1, 4);
		switch(rands)
		{
			case 1..79:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 80..90:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 91..100:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				Inventory_Add(playerid, "Material", 19843, 1);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
				ShowItemBox(playerid, "ADDED 1x", "MATERIAL", 19843);
			}
		}
		pCount4[playerid] = 25;
		HideShortKey(playerid);
        GivePlayerXP(playerid, DEFAULT_XP);
	}
	else 
	{
		AccountData[playerid][ActivityTime] += 12;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime]*99.000000/140.000000;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		PlayerPlaySound(playerid, 1135, 0, 0, 0);
		return 0;
	}
	return 1;
}

VRRP::TakeBatu5(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(!IsValidDynamicArea(PlayerMinerVars[playerid][TakeBatuArea][4]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(!IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][4]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(IsPlayerInjured(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(Inventory_Count(playerid, "Batu Kotor") >= 25)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Batu Kotor sudah mencapai maksimal! (Max: 25)");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(GetTotalWeightStatus(playerid) >= 50)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 120)
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		
		new rands = RandomEx(1, 101), randbatu = RandomEx(1, 4);
		switch(rands)
		{
			case 1..79:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 80..90:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 91..100:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				Inventory_Add(playerid, "Material", 19843, 1);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
				ShowItemBox(playerid, "ADDED 1x", "MATERIAL", 19843);
			}
		}
		pCount5[playerid] = 25;
		HideShortKey(playerid);
        GivePlayerXP(playerid, DEFAULT_XP);
	}
	else 
	{
		AccountData[playerid][ActivityTime] += 12;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime]*99.000000/140.000000;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		PlayerPlaySound(playerid, 1135, 0, 0, 0);
		return 0;
	}
	return 1;
}

VRRP::TakeBatu6(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(!IsValidDynamicArea(PlayerMinerVars[playerid][TakeBatuArea][5]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(!IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][5]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(IsPlayerInjured(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(Inventory_Count(playerid, "Batu Kotor") >= 25)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Batu Kotor sudah mencapai maksimal! (Max: 25)");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(GetTotalWeightStatus(playerid) >= 50)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 120)
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		
		new rands = RandomEx(1, 101), randbatu = RandomEx(1, 4);
		switch(rands)
		{
			case 1..79:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 80..90:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 91..100:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				Inventory_Add(playerid, "Material", 19843, 1);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
				ShowItemBox(playerid, "ADDED 1x", "MATERIAL", 19843);
			}
		}
		pCount6[playerid] = 25;
		HideShortKey(playerid);
        GivePlayerXP(playerid, DEFAULT_XP);
	}
	else 
	{
		AccountData[playerid][ActivityTime] += 12;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime]*99.000000/140.000000;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		PlayerPlaySound(playerid, 1135, 0, 0, 0);
		return 0;
	}
	return 1;
}

VRRP::TakeBatu7(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(!IsValidDynamicArea(PlayerMinerVars[playerid][TakeBatuArea][6]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(!IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][6]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(IsPlayerInjured(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(Inventory_Count(playerid, "Batu Kotor") >= 25)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Batu Kotor sudah mencapai maksimal! (Max: 25)");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(GetTotalWeightStatus(playerid) >= 50)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 120)
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		
		new rands = RandomEx(1, 101), randbatu = RandomEx(1, 4);
		switch(rands)
		{
			case 1..79:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 80..90:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 91..100:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				Inventory_Add(playerid, "Material", 19843, 1);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
				ShowItemBox(playerid, "ADDED 1x", "MATERIAL", 19843);
			}
		}
		pCount7[playerid] = 25;
		HideShortKey(playerid);
        GivePlayerXP(playerid, DEFAULT_XP);
	}
	else 
	{
		AccountData[playerid][ActivityTime] += 12;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime]*99.000000/140.000000;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		PlayerPlaySound(playerid, 1135, 0, 0, 0);
		return 0;
	}
	return 1;
}

VRRP::TakeBatu8(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(!IsValidDynamicArea(PlayerMinerVars[playerid][TakeBatuArea][7]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(!IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][7]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(IsPlayerInjured(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(Inventory_Count(playerid, "Batu Kotor") >= 25)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Batu Kotor sudah mencapai maksimal! (Max: 25)");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(GetTotalWeightStatus(playerid) >= 50)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 120)
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		
		new rands = RandomEx(1, 101), randbatu = RandomEx(1, 4);
		switch(rands)
		{
			case 1..79:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 80..90:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 91..100:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				Inventory_Add(playerid, "Material", 19843, 1);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
				ShowItemBox(playerid, "ADDED 1x", "MATERIAL", 19843);
			}
		}
		pCount8[playerid] = 25;
		HideShortKey(playerid);
        GivePlayerXP(playerid, DEFAULT_XP);
	}
	else 
	{
		AccountData[playerid][ActivityTime] += 12;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime]*99.000000/140.000000;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		PlayerPlaySound(playerid, 1135, 0, 0, 0);
		return 0;
	}
	return 1;
}

VRRP::TakeBatu9(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(!IsValidDynamicArea(PlayerMinerVars[playerid][TakeBatuArea][8]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(!IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][8]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(IsPlayerInjured(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(Inventory_Count(playerid, "Batu Kotor") >= 25)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Batu Kotor sudah mencapai maksimal! (Max: 25)");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(GetTotalWeightStatus(playerid) >= 50)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 120)
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		
		new rands = RandomEx(1, 101), randbatu = RandomEx(1, 4);
		switch(rands)
		{
			case 1..79:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 80..90:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 91..100:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				Inventory_Add(playerid, "Material", 19843, 1);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
				ShowItemBox(playerid, "ADDED 1x", "MATERIAL", 19843);
			}
		}
		pCount9[playerid] = 25;
		HideShortKey(playerid);
        GivePlayerXP(playerid, DEFAULT_XP);
	}
	else 
	{
		AccountData[playerid][ActivityTime] += 12;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime]*99.000000/140.000000;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		PlayerPlaySound(playerid, 1135, 0, 0, 0);
		return 0;
	}
	return 1;
}

VRRP::TakeBatu10(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(!IsValidDynamicArea(PlayerMinerVars[playerid][TakeBatuArea][9]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(!IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][TakeBatuArea][9]))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(IsPlayerInjured(playerid))
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(Inventory_Count(playerid, "Batu Kotor") >= 25)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Batu Kotor sudah mencapai maksimal! (Max: 25)");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(GetTotalWeightStatus(playerid) >= 50)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 120)
	{
		KillTimer(pTakeBatuTimer[playerid]);
		pTakeBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		RemovePlayerAttachedObject(playerid, 9);
		
		new rands = RandomEx(1, 101), randbatu = RandomEx(1, 4);
		switch(rands)
		{
			case 1..79:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 80..90:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
			}
			case 91..100:
			{
				Inventory_Add(playerid, "Batu Kotor", 3930, randbatu);
				Inventory_Add(playerid, "Material", 19843, 1);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbatu), "BATU KOTOR", 3930);
				ShowItemBox(playerid, "ADDED 1x", "MATERIAL", 19843);
			}
		}
		pCount10[playerid] = 25;
		HideShortKey(playerid);
        GivePlayerXP(playerid, DEFAULT_XP);
	}
	else 
	{
		AccountData[playerid][ActivityTime] += 12;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime]*99.000000/140.000000;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		PlayerPlaySound(playerid, 1135, 0, 0, 0);
		return 0;
	}
	return 1;
}

VRRP::CuciBatu(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pCuciBatuTimer[playerid]);
		pCuciBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(!IsValidDynamicArea(PlayerMinerVars[playerid][CuciBatuArea]))
	{
		KillTimer(pCuciBatuTimer[playerid]);
		pCuciBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(!IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][CuciBatuArea]))
	{
		KillTimer(pCuciBatuTimer[playerid]);
		pCuciBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(IsPlayerInjured(playerid))
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
		KillTimer(pCuciBatuTimer[playerid]);
		pCuciBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(GetTotalWeightStatus(playerid) >= 50)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
		KillTimer(pCuciBatuTimer[playerid]);
		pCuciBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(Inventory_Count(playerid, "Batu Kotor") < 2)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Batu kotor tidak cukup! (Min: 2)");
		KillTimer(pCuciBatuTimer[playerid]);
		pCuciBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(Inventory_Count(playerid, "Batu Bersih") >= 25)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Batu Bersih sudah mencapai batas Maksimal! (Max: 25)");
		KillTimer(pCuciBatuTimer[playerid]);
		pCuciBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 126)
	{
		KillTimer(pCuciBatuTimer[playerid]);
		pCuciBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		
		Inventory_Remove(playerid, "Batu Kotor", 2);
		Inventory_Add(playerid, "Batu Bersih", 2936, 2);
		ShowItemBox(playerid, "Received 2x", "BATU BERSIH", 2936);
	}
	else 
	{
		AccountData[playerid][ActivityTime] += 15.75;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime]*99.000000/126.000000;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		return 0;
	}
	return 1;
}

VRRP::LeburBatu(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pLeburBatuTimer[playerid]);
		pLeburBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(!IsALeburArea(playerid))
	{
		KillTimer(pLeburBatuTimer[playerid]);
		pLeburBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(IsPlayerInjured(playerid))
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
		KillTimer(pLeburBatuTimer[playerid]);
		pLeburBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(GetTotalWeightStatus(playerid) > 50)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
		KillTimer(pLeburBatuTimer[playerid]);
		pLeburBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(!PlayerHasItem(playerid, "Batu Bersih"))
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki batu bersih!");
		KillTimer(pLeburBatuTimer[playerid]);
		pLeburBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 126)
	{
		KillTimer(pLeburBatuTimer[playerid]);
		pLeburBatuTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

		new rands = RandomEx(1, 58);
		new randbesi = RandomEx(1, 8);
		new randtembaga = RandomEx(1, 8);
		new randemas = RandomEx(1, 8);
		new randberlian = RandomEx(1, 2);
		switch(rands) 
		{
			case 1..50:
			{
				Inventory_Add(playerid, "Besi", 19809, randbesi);
				Inventory_Add(playerid, "Tembaga", 11748, randtembaga);
				Inventory_Remove(playerid, "Batu Bersih", 1);
				ShowItemBox(playerid, sprintf("ADDED %dx", randtembaga), "TEMBAGA", 11748);
				ShowItemBox(playerid, sprintf("ADDED %dx", randbesi), "BESI", 19809);
			}
			case 51..55:
			{
				Inventory_Add(playerid, "Emas", 19941, randemas);
				Inventory_Add(playerid, "Besi", 19809, 5);
				Inventory_Remove(playerid, "Batu Bersih", 1);
				ShowItemBox(playerid, "ADDED 5x", "BESI", 11748);
				ShowItemBox(playerid, sprintf("ADDED %dx", randemas), "EMAS", 19809);
			}
			case 56..58:
			{
				Inventory_Add(playerid, "Berlian", 19941, randberlian);
				Inventory_Remove(playerid, "Batu Bersih", 1);
				ShowItemBox(playerid, sprintf("ADDED %dx", randberlian), "BERLIAN", 19941);
				ShowItemBox(playerid, "REMOVED 1x", "BATU BERSIH", 2936);
			}
		}
		GivePlayerXP(playerid, DEFAULT_XP);
	}
	else 
	{
		AccountData[playerid][ActivityTime] += 21;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime]*99.000000/126.000000;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.000000);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		return 0;
	}
	return 1;
}

IsALeburArea(playerid)
{
	if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][LeburBatuArea][0]))
		return 1;

	if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][LeburBatuArea][1]))
		return 1;

	if(IsPlayerInDynamicArea(playerid, PlayerMinerVars[playerid][LeburBatuArea][2]))
		return 1;

	return 0;
}

ptask MinerStone_Cooldown[1000](playerid)
{
	if(IsPlayerConnected(playerid))
	{
		if(GetPlayerJob(playerid) == JOB_MINER)
		{
			if(pCount1[playerid] > 0) {
				pCount1[playerid]--;

				if(pCount1[playerid] == 0) {
					pCount1[playerid] = -1;
				}
			}

			if(pCount2[playerid] > 0) {
				pCount2[playerid]--;

				if(pCount2[playerid] == 0) {
					pCount2[playerid] = -1;
				}
			}

			if(pCount3[playerid] > 0) {
				pCount3[playerid]--;

				if(pCount3[playerid] == 0) {
					pCount3[playerid] = -1;
				}
			}

			if(pCount4[playerid] > 0) {
				pCount4[playerid]--;

				if(pCount4[playerid] == 0) {
					pCount4[playerid] = -1;
				}
			}

			if(pCount5[playerid] > 0) {
				pCount5[playerid]--;

				if(pCount5[playerid] == 0) {
					pCount5[playerid] = -1;
				}
			}

			if(pCount6[playerid] > 0) {
				pCount6[playerid]--;

				if(pCount6[playerid] == 0) {
					pCount6[playerid] = -1;
				}
			}

			if(pCount7[playerid] > 0) {
				pCount7[playerid]--;

				if(pCount7[playerid] == 0) {
					pCount7[playerid] = -1;
				}
			}

			if(pCount8[playerid] > 0) {
				pCount8[playerid]--;

				if(pCount8[playerid] == 0) {
					pCount8[playerid] = -1;
				}
			}

			if(pCount9[playerid] > 0) {
				pCount9[playerid]--;

				if(pCount9[playerid] == 0) {
					pCount9[playerid] = -1;
				}
			}

			if(pCount10[playerid] > 0) {
				pCount10[playerid]--;

				if(pCount10[playerid] == 0) {
					pCount10[playerid] = -1;
				}
			}
		}
	}
	return 1;
}