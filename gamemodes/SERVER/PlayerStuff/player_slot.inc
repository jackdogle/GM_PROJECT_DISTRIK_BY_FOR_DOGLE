/*
	Slot Machine script by NaS (2011).
	
	For 0.3dRC5-3 (+)
	
	Change MIN_BET for the minimum bet
	
	Change MAX_BET for the maximum bet
	
	Change Bet_STEO for the bet steps (if it's 5 the bets can be: 5,  10,  15,  20 etc up to MAX_BET)


	Do NOT remove this credits.
*/
#include <YSI\y_hooks>

// cherry   x   2
// grapes   x  5
// 69       x  10
// bells    x  15
// bar 1    x 25
// bar 2    x 40

#define WIN_MULTIPLIER_GLOBAL 1.0

#define SLOT_MACHINE_POS_Y 	350.0

#define MIN_BET 5
#define MAX_BET 10

#define BET_STEP 5

#define G_STATE_NOT_GAMBLING    0
#define G_STATE_READY           1
#define G_STATE_GAMBLING        2
#define G_STATE_DISPLAY         3 // Currently displaying the message
#define G_STATE_PLAY_AGAIN      4 // Not used

#define DISPLAY_TIME 750 // Time to display the messages
#define GAMBLE_TIMER 100 // Decrease this if too fast

new Text:VerText;
new Text:ReadyText;
new PlayerText:BetText[MAX_PLAYERS] = {PlayerText:-1, ...};

new Text:Box;

new Text:Digit1[6];
new Text:Digit2[6];
new Text:Digit3[6];

new Slots[MAX_PLAYERS][3];
new SlotCounter[MAX_PLAYERS];
new Gambling[MAX_PLAYERS];

new SlotTimer[MAX_PLAYERS];

new Bet[MAX_PLAYERS];
new Balance[MAX_PLAYERS];

new bool:rdy=false;

Text:CreateSprite(Float:X, Float:Y, Name[], Float:Width, Float:Height)
{
	new Text:RetSprite;
	RetSprite = TextDrawCreate(X,  Y,  Name); // Text is txdfile:texture
	TextDrawFont(RetSprite,  TEXT_DRAW_FONT_SPRITE_DRAW); // Font ID 4 is the sprite draw font
	TextDrawColor(RetSprite, 0xFFFFFFFF);
	TextDrawTextSize(RetSprite, Width, Height); // Text size is the Width:Height
	return RetSprite;
}

Text:CreateSlotBox(Float:X, Float:Y, Float:Width, Float:Height, color)
{
	new Text[500];
	for(new i = floatround(Y); i < floatround(Y+Height);i++)
	{
		strcat(Text, "~n~_");
	}
    new Text:RetSprite;
	RetSprite = TextDrawCreate(X,  Y,  Text); // Text is txdfile:texture
	TextDrawFont(RetSprite,  0); // Font ID 4 is the sprite draw font
	TextDrawColor(RetSprite, 0xFFFFFFFF);
	TextDrawTextSize(RetSprite, Width+X, Height+Y); // Text size is the Width:Height
	TextDrawUseBox(RetSprite, 1);
	TextDrawBoxColor(RetSprite, color);
	TextDrawLetterSize(RetSprite, 0.0001, 0.1158);
	return RetSprite;
}

hook OnGameModeInitEx()
{
	
	Box = CreateSlotBox(194.0, SLOT_MACHINE_POS_Y-20, 3*64.0 + 3*20, 84, 0x00000077);
	
	// Cherries (x2)
	Digit1[0] = CreateSprite(214.0, SLOT_MACHINE_POS_Y, "LD_SLOT:cherry", 64.0, 64.0);
	Digit2[0] = CreateSprite(288.0, SLOT_MACHINE_POS_Y, "LD_SLOT:cherry", 64.0, 64.0);
	Digit3[0] = CreateSprite(362.0, SLOT_MACHINE_POS_Y, "LD_SLOT:cherry", 64.0, 64.0);
	
	// grapes (x5)
	Digit1[1] = CreateSprite(214.0, SLOT_MACHINE_POS_Y, "LD_SLOT:grapes", 64.0, 64.0);
	Digit2[1] = CreateSprite(288.0, SLOT_MACHINE_POS_Y, "LD_SLOT:grapes", 64.0, 64.0);
	Digit3[1] = CreateSprite(362.0, SLOT_MACHINE_POS_Y, "LD_SLOT:grapes", 64.0, 64);
	
	// 69's (x10)
	Digit1[2] = CreateSprite(214.0, SLOT_MACHINE_POS_Y, "LD_SLOT:r_69", 64.0, 64.0);
	Digit2[2] = CreateSprite(288.0, SLOT_MACHINE_POS_Y, "LD_SLOT:r_69", 64.0, 64.0);
	Digit3[2] = CreateSprite(362.0, SLOT_MACHINE_POS_Y, "LD_SLOT:r_69", 64.0, 64.0);
	
	// bells (x15)
	Digit1[3] = CreateSprite(214.0, SLOT_MACHINE_POS_Y, "LD_SLOT:bell", 64.0, 64.0);
	Digit2[3] = CreateSprite(288.0, SLOT_MACHINE_POS_Y, "LD_SLOT:bell", 64.0, 64.0);
	Digit3[3] = CreateSprite(362.0, SLOT_MACHINE_POS_Y, "LD_SLOT:bell", 64.0, 64.0);
	
	// Bars [1 bar] (x25)
	Digit1[4] = CreateSprite(214.0, SLOT_MACHINE_POS_Y, "LD_SLOT:bar1_o", 64.0, 64.0);
	Digit2[4] = CreateSprite(288.0, SLOT_MACHINE_POS_Y, "LD_SLOT:bar1_o", 64.0, 64.0);
	Digit3[4] = CreateSprite(362.0, SLOT_MACHINE_POS_Y, "LD_SLOT:bar1_o", 64.0, 64.0);
	
	// Bars [2 bar] (x40)
	Digit1[5] = CreateSprite(214.0, SLOT_MACHINE_POS_Y, "LD_SLOT:bar2_o", 64.0, 64.0);
	Digit2[5] = CreateSprite(288.0, SLOT_MACHINE_POS_Y, "LD_SLOT:bar2_o", 64.0, 64.0);
	Digit3[5] = CreateSprite(362.0, SLOT_MACHINE_POS_Y, "LD_SLOT:bar2_o", 64.0, 64.0);
	
	
	ReadyText = TextDrawCreate(320.0, SLOT_MACHINE_POS_Y+1.4, "~w~Ready to play.~n~~b~ ~k~~PED_SPRINT~ ~w~- ~g~gamble~n~~b~~k~~VEHICLE_ENTER_EXIT~ ~w~- ~r~exit~n~~b~~k~~PED_JUMPING~ ~w~- ~y~increase Bet");
	TextDrawUseBox(ReadyText, 1);
	TextDrawFont(ReadyText, 2);
	TextDrawSetShadow(ReadyText, 0);
	TextDrawSetOutline(ReadyText, 1);
	TextDrawLetterSize(ReadyText, 0.3, 1.23);
	TextDrawAlignment(ReadyText, 2);
	TextDrawBoxColor(ReadyText, 0x00000077);
	TextDrawTextSize(ReadyText, 350, 210);
	
	VerText = TextDrawCreate(194.0, SLOT_MACHINE_POS_Y-21, "~r~District ~w~SLOT MACHINE");
	TextDrawFont(VerText, 1);
	TextDrawSetShadow(VerText, 0);
	TextDrawSetOutline(VerText, 1);
	TextDrawLetterSize(VerText, 0.16, 0.65);

	for(new i; i < MAX_PLAYERS; i++) if(IsPlayerConnected(i)) OnPlayerConnect(i); // This will make the slotmachine usable for already connected players!

	return 1;
}

hook OnGameModeExit()
{
	TextDrawDestroy(Digit1[0]);
	TextDrawDestroy(Digit2[0]);
	TextDrawDestroy(Digit3[0]);
	
	TextDrawDestroy(Digit1[1]);
	TextDrawDestroy(Digit2[1]);
	TextDrawDestroy(Digit3[1]);
	
	TextDrawDestroy(Digit1[2]);
	TextDrawDestroy(Digit2[2]);
	TextDrawDestroy(Digit3[2]);
	
	TextDrawDestroy(Digit1[3]);
	TextDrawDestroy(Digit2[3]);
	TextDrawDestroy(Digit3[3]);
	
	TextDrawDestroy(Digit1[4]);
	TextDrawDestroy(Digit2[4]);
	TextDrawDestroy(Digit3[4]);
	
	TextDrawDestroy(Digit1[5]);
	TextDrawDestroy(Digit2[5]);
	TextDrawDestroy(Digit3[5]);
	
	
	TextDrawDestroy(Box);
	TextDrawDestroy(ReadyText);
	TextDrawDestroy(VerText);

	for(new i; i < MAX_PLAYERS; i++) if(IsPlayerConnected(i)) OnPlayerDisconnect(i, 0);
	
	return 1;
}

hook OnPlayerConnect(playerid)
{
	Gambling[playerid] = G_STATE_NOT_GAMBLING;
	SlotTimer[playerid] = -1;
	
	if(BetText[playerid] == PlayerText:-1)
	{
		BetText[playerid] = CreatePlayerTextDraw(playerid, 195.0, SLOT_MACHINE_POS_Y+58, "~y~Bet: 5$");
		PlayerTextDrawFont(playerid, BetText[playerid], 2);
		PlayerTextDrawLetterSize(playerid, BetText[playerid], 0.35, 0.8);
		PlayerTextDrawSetShadow(playerid, BetText[playerid], 0);
		PlayerTextDrawSetOutline(playerid, BetText[playerid], 1);
	}

	return 1;
}

hook OnPlayerDisconnect(playerid,  reason)
{
    ExitPlayerFromSlotMachine(playerid);
	
	if(SlotTimer[playerid] != -1) KillTimer(SlotTimer[playerid]);

	if(BetText[playerid] != PlayerText:-1)
	{
		PlayerTextDrawDestroy(playerid, BetText[playerid]);
		BetText[playerid] = PlayerText:-1;
	}

	return 1;
}

ShowPlayerSlots(playerid, slot1, slot2, slot3)
{
    TextDrawHideForPlayer(playerid, Digit1[0]);
	TextDrawHideForPlayer(playerid, Digit2[0]);
	TextDrawHideForPlayer(playerid, Digit3[0]);
	
	TextDrawHideForPlayer(playerid, Digit1[1]);
	TextDrawHideForPlayer(playerid, Digit2[1]);
	TextDrawHideForPlayer(playerid, Digit3[1]);
	
	TextDrawHideForPlayer(playerid, Digit1[2]);
	TextDrawHideForPlayer(playerid, Digit2[2]);
	TextDrawHideForPlayer(playerid, Digit3[2]);
	
	TextDrawHideForPlayer(playerid, Digit1[3]);
	TextDrawHideForPlayer(playerid, Digit2[3]);
	TextDrawHideForPlayer(playerid, Digit3[3]);
	
	TextDrawHideForPlayer(playerid, Digit1[4]);
	TextDrawHideForPlayer(playerid, Digit2[4]);
	TextDrawHideForPlayer(playerid, Digit3[4]);
	
	TextDrawHideForPlayer(playerid, Digit1[5]);
	TextDrawHideForPlayer(playerid, Digit2[5]);
	TextDrawHideForPlayer(playerid, Digit3[5]);
	
	
	TextDrawShowForPlayer(playerid, Digit1[slot1]);
	TextDrawShowForPlayer(playerid, Digit2[slot2]);
	TextDrawShowForPlayer(playerid, Digit3[slot3]);
	
	TextDrawShowForPlayer(playerid, Box);
}

HideSlotsForPlayer(playerid)
{
    TextDrawHideForPlayer(playerid, Digit1[0]);
	TextDrawHideForPlayer(playerid, Digit2[0]);
	TextDrawHideForPlayer(playerid, Digit3[0]);

	TextDrawHideForPlayer(playerid, Digit1[1]);
	TextDrawHideForPlayer(playerid, Digit2[1]);
	TextDrawHideForPlayer(playerid, Digit3[1]);

	TextDrawHideForPlayer(playerid, Digit1[2]);
	TextDrawHideForPlayer(playerid, Digit2[2]);
	TextDrawHideForPlayer(playerid, Digit3[2]);

	TextDrawHideForPlayer(playerid, Digit1[3]);
	TextDrawHideForPlayer(playerid, Digit2[3]);
	TextDrawHideForPlayer(playerid, Digit3[3]);

	TextDrawHideForPlayer(playerid, Digit1[4]);
	TextDrawHideForPlayer(playerid, Digit2[4]);
	TextDrawHideForPlayer(playerid, Digit3[4]);

	TextDrawHideForPlayer(playerid, Digit1[5]);
	TextDrawHideForPlayer(playerid, Digit2[5]);
	TextDrawHideForPlayer(playerid, Digit3[5]);
	
	TextDrawHideForPlayer(playerid, Box);
}

PutPlayerInSlotMachine(playerid,  firstBet=MIN_BET,   startBalance=0)
{
	if(Gambling[playerid] != G_STATE_NOT_GAMBLING) return print("Already gambling");
	
	Gambling[playerid] = G_STATE_READY;
	// TextDrawShowForPlayer(playerid, ReadyText);
	PlayerTextDrawShow(playerid, BetText[playerid]);
	TextDrawShowForPlayer(playerid, VerText);
	
	Slots[playerid][0] = random(5);
	Slots[playerid][1] = random(5);
	Slots[playerid][2] = random(5);

	ShowPlayerSlots(playerid, Slots[playerid][0], Slots[playerid][1], Slots[playerid][2]);
	
	Bet[playerid] = firstBet;
	
	// TakeMoney(playerid, startBalance);
	
	Balance[playerid] = startBalance;
	
	UpdateBetText(playerid);
	Inventory_Remove(playerid, "Chip", startBalance);
	
	TogglePlayerControllable(playerid, 0);
	return 1;
}

ExitPlayerFromSlotMachine(playerid)
{
	if(Gambling[playerid] == G_STATE_NOT_GAMBLING) return 0;
	HideSlotsForPlayer(playerid);
	Gambling[playerid] = G_STATE_NOT_GAMBLING;
	
	TogglePlayerControllable(playerid, 1);
	
	// TextDrawHideForPlayer(playerid, ReadyText);
	PlayerTextDrawHide(playerid, BetText[playerid]);
	TextDrawHideForPlayer(playerid, VerText);
	
	// new str[128];
    // if(Balance[playerid] > 0) format(str, sizeof(str), "~g~Your balance: %d$", Balance[playerid]);
    // else format(str, sizeof(str), "~r~You lost your money. Stop playing.", Balance[playerid]);
    // GameTextForPlayer(playerid, str, 5000, 4);

    if(Balance[playerid] > 0) 
	{
		Info(playerid, "Sisa chip anda adalah: "RED"%d$", Balance[playerid]);
		Inventory_Add(playerid, "Chip", 1915, Balance[playerid]);
	}
    else Warning(playerid, "Anda kalah dan kehilangan seluruh chip anda. Berhenti bermain.");
    
	AccountData[playerid][ActivityTime] = 0;
    // GiveMoney(playerid, Balance[playerid]);
    return 1;
}

CMD:spin(playerid, params[])
{
	if(Gambling[playerid] == G_STATE_READY)
	{
		new chip = Inventory_Count(playerid, "Chip");
		if(Bet[playerid] > chip+Balance[playerid])
		{
			Error(playerid, "Anda tidak memiliki cukup chip!");
			return 1;
		}

		if(Balance[playerid] - Bet[playerid] < 0)
		{
			// GameTextForPlayer(playerid, "~r~Your balance is too low!", 5000, 4);
			Error(playerid, "Chip anda terlalu rendah!");
			return 1;
		}
		
		SlotCounter[playerid] = 30+random(18);
		SlotTimer[playerid] = SetTimerEx("Gambler", GAMBLE_TIMER, 1, "d", playerid);
		Gambling[playerid] = G_STATE_GAMBLING;
		
		Balance[playerid]-=Bet[playerid];
		ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 10.0, 0, 0, 0, 0, 0);
		
		new prefix[4];
		if(Balance[playerid] == 0) strcat(prefix, "~y~");
		if(Balance[playerid]  > 0) strcat(prefix, "~g~");
		if(Balance[playerid]  < 0) strcat(prefix, "~r~");

		AccountData[playerid][ActivityTime] = 1;
		UpdateBetText(playerid);
		Inventory_Close(playerid);
		
		// TextDrawHideForPlayer(playerid, ReadyText);
	}
	return 1;
}

CMD:changebet(playerid, params[])
{
	if(Gambling[playerid] == G_STATE_READY)
	{
		Dialog_Show(playerid, ChangeBetSpin, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Change Bet", 
		""WHITE"Bet anda saat ini: "GREEN"%s\n\n"WHITE"Mohon masukkan berapa jumlah yang ingin anda pasang dalam taruhan ini:\nMin Bet: "GREEN"$5\n"WHITE"Max Bet: "GREEN"$10",
		"Bet", "Cancel", FormatMoney(Bet[playerid]));
	} else ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada didalam mode slot!");
	return 1;
}

CMD:cvc(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 6)
		return PermissionError(playerid);
	
	new otherid, value;
	if(sscanf(params, "ud", otherid, value))
		return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/cvc [name/playerid] [ammount (jumlah yang ingin diconvert)]");
		
	if(!IsPlayerConnected(otherid))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	
	if(!IsPlayerNearPlayer(playerid, otherid, 3.0))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dekat pemain tersebut!");
	
	if(value < 1)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat memasukkan nominal dibawah 1!");
	
	if(value > Inventory_Count(otherid, "Chip"))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki chip sebanyak itu!");
	
	new conversionRate = 80; // $ per chip
	new moneyToGive = value * conversionRate;

	// Hapus chip berdasarkan value pada inventory pemain
	Inventory_Remove(otherid, "Chip", value);

	// Berikan Pemain tersebut chip
	GiveMoney(otherid, moneyToGive);

	// Notification
	Info(playerid, "Anda berhasil melakukan conversasi "RED"%dx"WHITE" chip menjadi "GREEN"%s"WHITE" untuk "YELLOW"%s(%d)", value, FormatMoney(moneyToGive), ReturnName(otherid), otherid);
	Info(otherid, "Berhasil mengconversi chip sebanyak "RED"%dx"WHITE" menjadi "GREEN"%s", value, FormatMoney(moneyToGive));
	return 1;
}

Dialog:ChangeBetSpin(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new bet = strval(inputtext);
		if(bet < MIN_BET) return Dialog_Show(playerid, ChangeBetSpin, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Change Bet", 
		""WHITE"ERROR: Minimal Bet $10!\n"WHITE"Bet anda saat ini: "GREEN"%s\n\n"WHITE"Mohon masukkan berapa jumlah yang ingin anda pasang dalam taruhan ini:\nMin Bet: "GREEN"$10\n"WHITE"Max Bet: "GREEN"$10",
		"Bet", "Cancel", FormatMoney(Bet[playerid]));

		if(bet > MAX_BET) return Dialog_Show(playerid, ChangeBetSpin, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Change Bet", 
		""WHITE"ERROR: Chip anda tidak cukup!\n"WHITE"Bet anda saat ini: "GREEN"%s\n\n"WHITE"Mohon masukkan berapa jumlah yang ingin anda pasang dalam taruhan ini:\nMin Bet: "GREEN"$10\n"WHITE"Max Bet: "GREEN"$10",
		"Bet", "Cancel", FormatMoney(Bet[playerid]));

		Bet[playerid] = bet;
		UpdateBetText(playerid);
	}
	else return 0;
	return 1;
}

hook OnPlayerKeyStateChange(playerid,  newkeys,  oldkeys)
{
	/*if(newkeys & KEY_SPRINT && !(oldkeys & KEY_SPRINT))
	{
	    // Randomize if in Slotmachine
	    if(Gambling[playerid] == G_STATE_READY)
	    {
	        // new money = GetPlayerMoney(playerid);
	        new chip = Inventory_Count(playerid, "Chip");
            if(Bet[playerid] > chip+Balance[playerid])
	        {
	            // GameTextForPlayer(playerid, "~r~You don't have enough money!", 5000, 4);
	            Error(playerid, "Anda tidak memiliki cukup chip!");
                return 1;
	        }
	        
	        if(Balance[playerid] - Bet[playerid] < 0)
	        {
	            // GameTextForPlayer(playerid, "~r~Your balance is too low!", 5000, 4);
	            Error(playerid, "Chip anda terlalu rendah!");
                return 1;
	        }
	        
	        SlotCounter[playerid] = 30+random(18);
            SlotTimer[playerid] = SetTimerEx("Gambler", GAMBLE_TIMER, 1, "d", playerid);
            Gambling[playerid] = G_STATE_GAMBLING;
            
         	Balance[playerid]-=Bet[playerid];
         	
         	new prefix[4];
	        if(Balance[playerid] == 0) strcat(prefix, "~y~");
	        if(Balance[playerid]  > 0) strcat(prefix, "~g~");
	        if(Balance[playerid]  < 0) strcat(prefix, "~r~");

			UpdateBetText(playerid);
         	
         	TextDrawHideForPlayer(playerid, ReadyText);
	    }
	}*/
	
	if(newkeys & KEY_SECONDARY_ATTACK && !(oldkeys & KEY_SECONDARY_ATTACK))
	{
	    if(Gambling[playerid] == G_STATE_READY)
	    {
	    	ExitPlayerFromSlotMachine(playerid);
	    }
	}
	
	/*if(newkeys & KEY_JUMP && !(oldkeys & KEY_JUMP))
	{
	    if(Gambling[playerid] == G_STATE_READY)
	    {
	    	Bet[playerid] = GetNextValidBet(Bet[playerid]);
	    	UpdateBetText(playerid);
	    }
	}*/
	return 1;
}

forward Gambler(playerid);
public Gambler(playerid)
{
	if(Gambling[playerid] != G_STATE_GAMBLING)
	{
	    print("Strange error @ gambler");
	    KillTimer(SlotTimer[playerid]);
	    SlotTimer[playerid] = -1;
	    Gambling[playerid] = G_STATE_NOT_GAMBLING;
	    return 0;
	}
	SlotCounter[playerid] -= 1;
	
	new slot = SlotCounter[playerid];
	
	if(slot < 10)
	{
	    Slots[playerid][2]+=random(3)+1;
	}
	else if(slot < 20)
	{
	    Slots[playerid][1]+=random(3)+1;
	    Slots[playerid][2]+=random(3)+1;
	}
	else
	{
	    Slots[playerid][0]+=random(3)+1;
	    Slots[playerid][1]+=random(3)+1;
	    Slots[playerid][2]+=random(3)+1;
	}
	if(Slots[playerid][0] >= 6) Slots[playerid][0] = 0;
	if(Slots[playerid][1] >= 6) Slots[playerid][1] = 0;
	if(Slots[playerid][2] >= 6) Slots[playerid][2] = 0;
	
	ShowPlayerSlots(playerid, Slots[playerid][0], Slots[playerid][1], Slots[playerid][2]);
	
	if(SlotCounter[playerid] == 0)
	{
	    KillTimer(SlotTimer[playerid]);
	    SlotTimer[playerid] = -1;
		Gambling[playerid] = G_STATE_DISPLAY;
		
	    if(Slots[playerid][0] == Slots[playerid][1] && Slots[playerid][0] == Slots[playerid][2])
	    {
	        //printf("player %d won with %d", playerid, Slots[playerid][0]); // Uncomment this line for seeing all wins
	        
	        new Multiplier=1;
	        
	        switch(Slots[playerid][0])
	        {
	            case 0: Multiplier = 2;    // Cherries
	            case 1: Multiplier = 5;   // Grapes
	            case 2: Multiplier = 10;   // 69's
	            case 3: Multiplier = 15;   // Bells
	            case 4: Multiplier = 25;  // Bar
	            case 5: Multiplier = 40;  // Double Bars
	        }
	        
	        // new str[128];
	        // format(str, sizeof(str), "~w~Winner: ~g~%d$~w~!", money);
	        // GameTextForPlayer(playerid, str, 5000, 4);
	        new money = Bet[playerid] * Multiplier; //floatround(Bet[playerid] * Multiplier * WIN_MULTIPLIER_GLOBAL);
            Info(playerid, "Anda memenangkan spin ini sebesar "GREEN"%s", FormatMoney(money));
	        
	        Balance[playerid] += money;
	        
	        UpdateBetText(playerid);
	        
	        Slots[playerid][0] = random(5); // Randomize the slots again
			Slots[playerid][1] = random(5);
			Slots[playerid][2] = random(5);
	    }
	    else
	    {
	        if(Slots[playerid][0] == Slots[playerid][1] || Slots[playerid][1] == Slots[playerid][2] || Slots[playerid][0] == Slots[playerid][2]) GameTextForPlayer(playerid, "~y~Hampir!", 3000, 4);
	        else GameTextForPlayer(playerid, "~r~Rungkad!", 3000, 4);
	    }
	    
	    SetTimerEx("PlayAgainTimer", DISPLAY_TIME, 0, "d", playerid);
		AccountData[playerid][ActivityTime] = 0;
	    return 1;
	}
	//printf("Counter: %d", SlotCounter[playerid]);
	return 0;
}

forward PlayAgainTimer(playerid);
public PlayAgainTimer(playerid)
{
	Gambling[playerid] = G_STATE_READY;
	// TextDrawShowForPlayer(playerid, ReadyText);
	
	// Remove the following 3 lines to disable the ability to hold down SPRINT
	new keys, lr, ud;
	GetPlayerKeys(playerid, keys, ud, lr);
	if(keys & KEY_SPRINT) OnPlayerKeyStateChange(playerid, KEY_SPRINT, 0);
}

/*GetNextValidBet(value)
{
	if(value + BET_STEP > MAX_BET) return MIN_BET;
	return value + BET_STEP;
}*/

UpdateBetText(playerid)
{
    new str[128];
    new prefix[4];
    if(Balance[playerid] == 0) strcat(prefix, "~r~");
    if(Balance[playerid]  > 0) strcat(prefix, "~g~");
    
    format(str, sizeof(str), "~w~Bet: ~g~%d$_____~w~Chip Anda: %s%d$", Bet[playerid], prefix, Balance[playerid]);
	PlayerTextDrawSetString(playerid, BetText[playerid], str);
}

task RDYBLINK[1000]() // Dipanggil setiap 1 detik
{
    static const text1[] = "~w~Pasang ~y~Taruhan ~w~anda~w~!~n~~b~ ~k~~PED_SPRINT~ ~w~- ~g~gamble~n~~b~~k~~VEHICLE_ENTER_EXIT~ ~w~- ~r~exit~n~~b~~k~~PED_JUMPING~ ~w~- ~y~increase Bet";
    static const text2[] = "_~n~~b~ ~k~~PED_SPRINT~ ~w~- ~g~gamble~n~~b~~k~~VEHICLE_ENTER_EXIT~ ~w~- ~r~exit~n~~b~~k~~PED_JUMPING~ ~w~- ~y~increase Bet";

    rdy = !rdy; // Toggle nilai rdy
    if (rdy) TextDrawSetString(ReadyText, text1);
    else TextDrawSetString(ReadyText, text2);
}


stock strtok(const string[],  &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[128]; // modified to 128
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}