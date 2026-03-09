
new
	eventJoin[MAX_PLAYERS] = {0, ...},
	eventTeams[MAX_PLAYERS] = {0, ...},
	eventWaitingSpawn[MAX_PLAYERS] = {0, ...},
	eventCheckpoint[MAX_PLAYERS] = {0, ...},
	Text:eventTextdraws[8],
	eventMessageText[4][128],
  	eventScore_DM[MAX_PLAYERS] = {0, ...}
;

#include "SERVER/events/enumerations.inc"
#include "SERVER/events/function.inc"
#include "SERVER/events/callback.inc"
#include "SERVER/events/command.inc"
#include "SERVER/events/dialog.inc"