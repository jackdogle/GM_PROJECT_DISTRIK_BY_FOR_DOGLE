#include <YSI\y_hooks>

enum poolBall
{
    STREAMER_TAG_OBJECT:bObject,
    bExisting
}

new
	PlayingPool[MAX_PLAYERS],
	bool:InBar[MAX_PLAYERS], //Ovo na Pickupu za ulaz u Bar stavi na true a na izlazu false i tjt.
	PoolCamera[MAX_PLAYERS],
	UsingChalk[MAX_PLAYERS],
	PoolScore[MAX_PLAYERS],
	Float:AimAngle[MAX_PLAYERS][2],
	AimObject,
	PoolStarted,
	bool:PoolRunning,
	Player1,
	Player2,
	NextShoot,
	PoolAimer = -1,
	PoolLastShooter = -1,
	PoolLastScore,
	PoolBall[16][poolBall],
	Text:PoolTD[4],
	Float:PoolPower,
	PoolDir;


// Player Connect
hook OnPlayerConnect(playerid)
{
    InBar[playerid] = false;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(PoolAimer == playerid)
	{
		PoolAimer = -1;
		TextDrawHideForPlayer(playerid, PoolTD[0]);
		TextDrawHideForPlayer(playerid, PoolTD[1]);
		TextDrawHideForPlayer(playerid, PoolTD[2]);
		TextDrawHideForPlayer(playerid, PoolTD[3]);
		DestroyObject(AimObject);
	}	
	if(PlayingPool[playerid])
	{
		new
			count = GetPoolPlayersCount();
		if(count >= 1)
		{
			PlayingPool[playerid] = 0;
			PoolStarted = false;
			PoolRunning = false;
			Player2 = INVALID_PLAYER_ID;
			Player1 = INVALID_PLAYER_ID;
			NextShoot = INVALID_PLAYER_ID;
			RespawnPoolBalls();
			if(count >= 2)
			{
			    PlayingPool[Player2] = 0;
				PlayingPool[Player1] = 0;
			}
		}
	}
	return 1;
}

hook OnPlayerDeath(playerid, killerid, reason)
{
    if(PoolAimer == playerid)
	{
		PoolAimer = -1;
		TextDrawHideForPlayer(playerid, PoolTD[0]);
		TextDrawHideForPlayer(playerid, PoolTD[1]);
		TextDrawHideForPlayer(playerid, PoolTD[2]);
		TextDrawHideForPlayer(playerid, PoolTD[3]);
		DestroyObject(AimObject);
	}
	if(PlayingPool[playerid])
	{
		new count = GetPoolPlayersCount();
        if(count >= 1)
	    {
		        PlayingPool[playerid] = 0;
		        PoolStarted = false;
		        PoolRunning = false;
		        Player2 = INVALID_PLAYER_ID;
		        Player1 = INVALID_PLAYER_ID;
		        NextShoot = INVALID_PLAYER_ID;
		        RespawnPoolBalls();
		        if(count >= 2)
		        {
			        PlayingPool[Player2] = 0;
		            PlayingPool[Player1] = 0;
		        }
	    }
	}
	return 1;
}

hook OnPlayerSpawn(playerid)
{
    PreloadAnimLib(playerid, "POOL");

	if(PoolAimer == playerid)
	{
		PoolAimer = -1;
		TextDrawHideForPlayer(playerid, PoolTD[0]);
		TextDrawHideForPlayer(playerid, PoolTD[1]);
		TextDrawHideForPlayer(playerid, PoolTD[2]);
		TextDrawHideForPlayer(playerid, PoolTD[3]);
		DestroyObject(AimObject);
	}
	if(PlayingPool[playerid])
	{
		PlayingPool[playerid] = 0;
		new
			count = GetPoolPlayersCount();
		if(count <= 0)
		{
			PoolStarted = 0;
			RespawnPoolBalls();
		}
	}
	return 1;
}

hook OnGameModeInitEx()
{
    LoadPool();
    return 1;
}