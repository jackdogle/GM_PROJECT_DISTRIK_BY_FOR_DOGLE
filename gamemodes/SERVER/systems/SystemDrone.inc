///---[Drone Systems]---

CMD:drone(playerid, params[])
{
    if(AccountData[playerid][pSpawned] == 0)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "You must be spawned or logged to Use command.");
    
    if(AccountData[playerid][pFaction] != FACTION_POLISI)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan faction kepolisian!");

	if(AccountData[playerid][pFaction] == FACTION_POLISI)
	{
		if(AccountData[playerid][pFactionRank] < 11) return ShowTDN(playerid, NOTIFICATION_ERROR, "Minimal rank KOMBES untuk mengakses ini!");
	}
	new str[128];
 	if( sscanf( params, "s[128]", str ) ) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "USAGE: /drone [spawn/end]" );

  	if( strcmp( str, "spawn" ) == 0 ) {
  	    if( GetPVarInt( playerid, "DroneSpawned" ) == 0 ) {
  	        new Float:Health;
  	        GetPlayerHealth( playerid, Health );

  	        if(Health != 0) {
	  	        new Float:PosX, Float:PosY, Float:PosZ;
	  	        GetPlayerPos( playerid, PosX, PosY, PosZ );
	            SetPVarFloat( playerid, "OldPosX", PosX );
				SetPVarFloat( playerid, "OldPosY", PosY );
				SetPVarFloat( playerid, "OldPosZ", PosZ );
		 	    SetPVarInt( playerid, "DroneSpawned", 1 );
		 	    SendClientMessage( playerid, COLOR_GREEN, "You have successfully spawned a drone." );
		 	    Drones[playerid] = CreateVehicle( 465, PosX, PosY, PosZ + 20, 0, 0, 0, 0, -1 );
		 	    PutPlayerInVehicle( playerid, Drones[playerid], 0 );
                SwitchVehicleEngine(Drones[playerid], true);
			}
	  	} else {
	  	    SendClientMessage( playerid, COLOR_RED, "You already have a drone spawned in!" );
	  	}
 	} else {
 	    if( strcmp( str, "ex" ) == 0 ) {
	  	    if( GetPVarInt( playerid, "DroneSpawned" ) == 1 ) {
	  	        new Float:PosX, Float:PosY, Float:PosZ;
	  	        GetVehiclePos( Drones[playerid], PosX, PosY, PosZ );

		 	    SetPVarInt( playerid, "DroneSpawned", 0 );
		 	    SendClientMessage( playerid, COLOR_GREEN, "Drone successfully detonated." );
				DestroyVehicle( Drones[playerid] );

				CreateExplosion( PosX, PosY, PosZ, 7, 25 );

				SetPlayerPos(playerid, GetPVarFloat( playerid, "OldPosX" ), GetPVarFloat( playerid, "OldPosY" ), GetPVarFloat( playerid, "OldPosZ" ));
		  	} else {
		  	    SendClientMessage( playerid, COLOR_RED, "You need to have a drone spawned in!" );
		  	}
	 	} else {
	 	    if( strcmp( str, "end" ) == 0 ) {
		  	    if( GetPVarInt( playerid, "DroneSpawned" ) == 1 ) {
			 	    SetPVarInt( playerid, "DroneSpawned", 0 );
			 	    SendClientMessage( playerid, COLOR_GREEN, "You have shut your drone down." );
			 	    DestroyVehicle( Drones[playerid] );

			 	    SetPlayerPos(playerid, GetPVarFloat( playerid, "OldPosX" ), GetPVarFloat( playerid, "OldPosY" ), GetPVarFloat( playerid, "OldPosZ" ));
			  	} else {
			  	    SendClientMessage( playerid, COLOR_RED, "You need to have a drone spawned in!" );
			  	}
		 	}
	 	}
 	}
 	return 1;
}