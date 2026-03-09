#include <YSI\y_hooks>

new PlayerText: ATRP_RadioTD[MAX_PLAYERS][13];
new PlayerText: ATRP_VoiceTD[MAX_PLAYERS][1];

new bool: ToggleRadio[MAX_PLAYERS] = { false, ... };
new bool: RadioMicOn[MAX_PLAYERS] = { false, ... };
new PlayerInFreq[MAX_PLAYERS];

VoiceSistemLoadTextdraw(playerid)
{
    ATRP_RadioTD[playerid][0] = CreatePlayerTextDraw(playerid, 393.000, 366.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ATRP_RadioTD[playerid][0], 100.000, 90.000);
    PlayerTextDrawAlignment(playerid, ATRP_RadioTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, ATRP_RadioTD[playerid][0], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_RadioTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_RadioTD[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_RadioTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, ATRP_RadioTD[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_RadioTD[playerid][0], 1);

    ATRP_RadioTD[playerid][1] = CreatePlayerTextDraw(playerid, 396.000, 380.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ATRP_RadioTD[playerid][1], 94.000, 34.000);
    PlayerTextDrawAlignment(playerid, ATRP_RadioTD[playerid][1], 1);
    PlayerTextDrawColor(playerid, ATRP_RadioTD[playerid][1], -1448498689);
    PlayerTextDrawSetShadow(playerid, ATRP_RadioTD[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_RadioTD[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_RadioTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, ATRP_RadioTD[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_RadioTD[playerid][1], 1);

    ATRP_RadioTD[playerid][2] = CreatePlayerTextDraw(playerid, 397.000, 414.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ATRP_RadioTD[playerid][2], 30.000, 18.000);
    PlayerTextDrawAlignment(playerid, ATRP_RadioTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, ATRP_RadioTD[playerid][2], 1768516095);
    PlayerTextDrawSetShadow(playerid, ATRP_RadioTD[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_RadioTD[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_RadioTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, ATRP_RadioTD[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_RadioTD[playerid][2], 1);

    ATRP_RadioTD[playerid][3] = CreatePlayerTextDraw(playerid, 459.000, 414.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ATRP_RadioTD[playerid][3], 30.000, 18.000);
    PlayerTextDrawAlignment(playerid, ATRP_RadioTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, ATRP_RadioTD[playerid][3], 1768516095);
    PlayerTextDrawSetShadow(playerid, ATRP_RadioTD[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_RadioTD[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_RadioTD[playerid][3], 255);
    PlayerTextDrawFont(playerid, ATRP_RadioTD[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_RadioTD[playerid][3], 1);

    ATRP_RadioTD[playerid][4] = CreatePlayerTextDraw(playerid, 429.000, 414.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ATRP_RadioTD[playerid][4], 28.000, 18.000);
    PlayerTextDrawAlignment(playerid, ATRP_RadioTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, ATRP_RadioTD[playerid][4], 1768516095);
    PlayerTextDrawSetShadow(playerid, ATRP_RadioTD[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_RadioTD[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_RadioTD[playerid][4], 255);
    PlayerTextDrawFont(playerid, ATRP_RadioTD[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_RadioTD[playerid][4], 1);

    ATRP_RadioTD[playerid][5] = CreatePlayerTextDraw(playerid, 443.000, 366.000, "District lkie");
    PlayerTextDrawLetterSize(playerid, ATRP_RadioTD[playerid][5], 0.170, 1.299);
    PlayerTextDrawAlignment(playerid, ATRP_RadioTD[playerid][5], 2);
    PlayerTextDrawColor(playerid, ATRP_RadioTD[playerid][5], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_RadioTD[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_RadioTD[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_RadioTD[playerid][5], 150);
    PlayerTextDrawFont(playerid, ATRP_RadioTD[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_RadioTD[playerid][5], 1);

    ATRP_RadioTD[playerid][6] = CreatePlayerTextDraw(playerid, 409.000, 383.000, "FREQ");
    PlayerTextDrawLetterSize(playerid, ATRP_RadioTD[playerid][6], 0.180, 1.399);
    PlayerTextDrawAlignment(playerid, ATRP_RadioTD[playerid][6], 2);
    PlayerTextDrawColor(playerid, ATRP_RadioTD[playerid][6], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_RadioTD[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_RadioTD[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_RadioTD[playerid][6], 150);
    PlayerTextDrawFont(playerid, ATRP_RadioTD[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_RadioTD[playerid][6], 1);

    ATRP_RadioTD[playerid][7] = CreatePlayerTextDraw(playerid, 442.000, 391.000, "0");
    PlayerTextDrawLetterSize(playerid, ATRP_RadioTD[playerid][7], 0.369, 1.800);
    PlayerTextDrawAlignment(playerid, ATRP_RadioTD[playerid][7], 2);
    PlayerTextDrawColor(playerid, ATRP_RadioTD[playerid][7], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_RadioTD[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_RadioTD[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_RadioTD[playerid][7], 150);
    PlayerTextDrawFont(playerid, ATRP_RadioTD[playerid][7], 3);
    PlayerTextDrawSetProportional(playerid, ATRP_RadioTD[playerid][7], 1);

    ATRP_RadioTD[playerid][8] = CreatePlayerTextDraw(playerid, 412.000, 415.000, "power");
    PlayerTextDrawLetterSize(playerid, ATRP_RadioTD[playerid][8], 0.180, 1.600);
    PlayerTextDrawTextSize(playerid, ATRP_RadioTD[playerid][8], 11.000, 25.000);
    PlayerTextDrawAlignment(playerid, ATRP_RadioTD[playerid][8], 2);
    PlayerTextDrawColor(playerid, ATRP_RadioTD[playerid][8], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_RadioTD[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_RadioTD[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_RadioTD[playerid][8], 150);
    PlayerTextDrawFont(playerid, ATRP_RadioTD[playerid][8], 2);
    PlayerTextDrawSetProportional(playerid, ATRP_RadioTD[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_RadioTD[playerid][8], 1);

    ATRP_RadioTD[playerid][9] = CreatePlayerTextDraw(playerid, 443.000, 415.000, "ttp");
    PlayerTextDrawLetterSize(playerid, ATRP_RadioTD[playerid][9], 0.180, 1.600);
    PlayerTextDrawTextSize(playerid, ATRP_RadioTD[playerid][9], 11.000, 25.000);
    PlayerTextDrawAlignment(playerid, ATRP_RadioTD[playerid][9], 2);
    PlayerTextDrawColor(playerid, ATRP_RadioTD[playerid][9], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_RadioTD[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_RadioTD[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_RadioTD[playerid][9], 150);
    PlayerTextDrawFont(playerid, ATRP_RadioTD[playerid][9], 2);
    PlayerTextDrawSetProportional(playerid, ATRP_RadioTD[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_RadioTD[playerid][9], 1);

    ATRP_RadioTD[playerid][10] = CreatePlayerTextDraw(playerid, 474.000, 415.000, "setfq");
    PlayerTextDrawLetterSize(playerid, ATRP_RadioTD[playerid][10], 0.180, 1.600);
    PlayerTextDrawTextSize(playerid, ATRP_RadioTD[playerid][10], 11.000, 25.000);
    PlayerTextDrawAlignment(playerid, ATRP_RadioTD[playerid][10], 2);
    PlayerTextDrawColor(playerid, ATRP_RadioTD[playerid][10], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_RadioTD[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_RadioTD[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_RadioTD[playerid][10], 150);
    PlayerTextDrawFont(playerid, ATRP_RadioTD[playerid][10], 2);
    PlayerTextDrawSetProportional(playerid, ATRP_RadioTD[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, ATRP_RadioTD[playerid][10], 1);

    ATRP_RadioTD[playerid][11] = CreatePlayerTextDraw(playerid, 456.000, 356.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ATRP_RadioTD[playerid][11], 21.000, 10.000);
    PlayerTextDrawAlignment(playerid, ATRP_RadioTD[playerid][11], 1);
    PlayerTextDrawColor(playerid, ATRP_RadioTD[playerid][11], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_RadioTD[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_RadioTD[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_RadioTD[playerid][11], 255);
    PlayerTextDrawFont(playerid, ATRP_RadioTD[playerid][11], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_RadioTD[playerid][11], 1);

    ATRP_RadioTD[playerid][12] = CreatePlayerTextDraw(playerid, 480.000, 328.000, "LD_BUM:blkdot");
    PlayerTextDrawTextSize(playerid, ATRP_RadioTD[playerid][12], 9.000, 39.000);
    PlayerTextDrawAlignment(playerid, ATRP_RadioTD[playerid][12], 1);
    PlayerTextDrawColor(playerid, ATRP_RadioTD[playerid][12], 255);
    PlayerTextDrawSetShadow(playerid, ATRP_RadioTD[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_RadioTD[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, ATRP_RadioTD[playerid][12], 255);
    PlayerTextDrawFont(playerid, ATRP_RadioTD[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, ATRP_RadioTD[playerid][12], 1);

    ATRP_VoiceTD[playerid][0] = CreatePlayerTextDraw(playerid, 563.000, 427.000, "VOICE: ~B~NORMAL");
    PlayerTextDrawLetterSize(playerid, ATRP_VoiceTD[playerid][0], 0.220, 1.399);
    PlayerTextDrawAlignment(playerid, ATRP_VoiceTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, ATRP_VoiceTD[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, ATRP_VoiceTD[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, ATRP_VoiceTD[playerid][0], 1);
    PlayerTextDrawBackgroundColor(playerid, ATRP_VoiceTD[playerid][0], 150);
    PlayerTextDrawFont(playerid, ATRP_VoiceTD[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, ATRP_VoiceTD[playerid][0], 1);

    // ATRP_VoiceTD[playerid][0] = CreatePlayerTextDraw(playerid, 398.000, 413.000, "LD_BUM:blkdot");
    // PlayerTextDrawTextSize(playerid, ATRP_VoiceTD[playerid][0], 8.000, 6.000);
    // PlayerTextDrawAlignment(playerid, ATRP_VoiceTD[playerid][0], 1);
    // PlayerTextDrawColor(playerid, ATRP_VoiceTD[playerid][0], -1);
    // PlayerTextDrawSetShadow(playerid, ATRP_VoiceTD[playerid][0], 0);
    // PlayerTextDrawSetOutline(playerid, ATRP_VoiceTD[playerid][0], 0);
    // PlayerTextDrawBackgroundColor(playerid, ATRP_VoiceTD[playerid][0], 255);
    // PlayerTextDrawFont(playerid, ATRP_VoiceTD[playerid][0], 4);
    // PlayerTextDrawSetProportional(playerid, ATRP_VoiceTD[playerid][0], 1);

    // ATRP_VoiceTD[playerid][1] = CreatePlayerTextDraw(playerid, 398.000, 421.000, "LD_BUM:blkdot");
    // PlayerTextDrawTextSize(playerid, ATRP_VoiceTD[playerid][1], 8.000, 6.000);
    // PlayerTextDrawAlignment(playerid, ATRP_VoiceTD[playerid][1], 1);
    // PlayerTextDrawColor(playerid, ATRP_VoiceTD[playerid][1], -1);
    // PlayerTextDrawSetShadow(playerid, ATRP_VoiceTD[playerid][1], 0);
    // PlayerTextDrawSetOutline(playerid, ATRP_VoiceTD[playerid][1], 0);
    // PlayerTextDrawBackgroundColor(playerid, ATRP_VoiceTD[playerid][1], 255);
    // PlayerTextDrawFont(playerid, ATRP_VoiceTD[playerid][1], 4);
    // PlayerTextDrawSetProportional(playerid, ATRP_VoiceTD[playerid][1], 1);

    // ATRP_VoiceTD[playerid][2] = CreatePlayerTextDraw(playerid, 398.000, 429.000, "LD_BUM:blkdot");
    // PlayerTextDrawTextSize(playerid, ATRP_VoiceTD[playerid][2], 8.000, 6.000);
    // PlayerTextDrawAlignment(playerid, ATRP_VoiceTD[playerid][2], 1);
    // PlayerTextDrawColor(playerid, ATRP_VoiceTD[playerid][2], -1);
    // PlayerTextDrawSetShadow(playerid, ATRP_VoiceTD[playerid][2], 0);
    // PlayerTextDrawSetOutline(playerid, ATRP_VoiceTD[playerid][2], 0);
    // PlayerTextDrawBackgroundColor(playerid, ATRP_VoiceTD[playerid][2], 255);
    // PlayerTextDrawFont(playerid, ATRP_VoiceTD[playerid][2], 4);
    // PlayerTextDrawSetProportional(playerid, ATRP_VoiceTD[playerid][2], 1);
}

VoiceSistemUnloadTextdraw(playerid)
{
    for(new x = 0; x < 13; x++)
    {
        PlayerTextDrawDestroy(playerid, ATRP_RadioTD[playerid][x]);
    }
    PlayerTextDrawDestroy(playerid, ATRP_VoiceTD[playerid][0]);
    // PlayerTextDrawDestroy(playerid, ATRP_VoiceTD[playerid][1]);
    // PlayerTextDrawDestroy(playerid, ATRP_VoiceTD[playerid][2]);
}

RadioTextdrawToggle(playerid, bool: toggle)
{
    if(!toggle)
    {
        for(new x; x < 13; x++)
        {
            PlayerTextDrawHide(playerid, ATRP_RadioTD[playerid][x]);
        }
    }
    else
    {
        for(new x; x < 13; x++)
        {
            PlayerTextDrawShow(playerid, ATRP_RadioTD[playerid][x]);
        }
    }
    return 1;
}

//-----------------------------------------------------------------
hook OnPlayerConnect(playerid)
{
    ToggleRadio[playerid] = false;
    RadioMicOn[playerid] = false;
    PlayerInFreq[playerid] = 0;
    VoiceSistemLoadTextdraw(playerid);
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    ToggleRadio[playerid] = false;
    RadioMicOn[playerid] = false;
    PlayerInFreq[playerid] = 0;
    VoiceSistemUnloadTextdraw(playerid);
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    PlayerTextDrawShow(playerid, ATRP_VoiceTD[playerid][0]);
    // PlayerTextDrawShow(playerid, ATRP_VoiceTD[playerid][1]);
    // PlayerTextDrawShow(playerid, ATRP_VoiceTD[playerid][2]);
    return 1;
}

ptask Radio_Timer[1000](playerid)
{
    if (IsPlayerInWater(playerid))
	{
		if (PlayerHasItem(playerid, "Smartphone"))
		{
			Inventory_Remove(playerid, "Smartphone", Inventory_Count(playerid, "Smartphone"));
			Info(playerid, "Smartphone anda rusak karena terkena air!");
		}

		if (PlayerHasItem(playerid, "Radio"))
		{
            if (ToggleRadio[playerid] && PlayerInFreq[playerid] != 0)
            {
                ToggleRadio[playerid] = false;
                RadioMicOn[playerid] = false;
                PlayerInFreq[playerid] = 0;
                CallRemoteFunction("UpdatePlayerVoiceMicToggle", "dd", playerid, false);
                CallRemoteFunction("UpdatePlayerVoiceRadioToggle", "dd", playerid, false);
                CallRemoteFunction("AssignFreqToFSVoice", "ddd", playerid, false, 0);
                PlayerTextDrawSetString(playerid, ATRP_RadioTD[playerid][7], "0");
                RemovePlayerAttachedObject(playerid, 9);
                
                Inventory_Remove(playerid, "Radio", Inventory_Count(playerid, "Radio"));
                Info(playerid, "Radio anda rusak dan saluran terputus karena terkena air!");
            }
            else
            {
                Inventory_Remove(playerid, "Radio", Inventory_Count(playerid, "Radio"));
                Info(playerid, "Radio anda rusak karena terkena air!");
            }
		}
	}
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_RADIO_FREQ:
        {
            if(!response) return 1;
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RADIO_FREQ, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Radio Fx",
            "Error: Tidak dapat diisi kosong!\nMasukkan frekuensi radio yang ingin diterapkan pada kolom dibawah ini\
            \n(Frekuensi harus berada diantara 0 - 9999)\
            \nCatatan: Masukkan frekuensi 0 untuk memutuskan saluran frekuensi/netral", "Submit", "Batal");

            if(!IsNumeric(inputtext)) return ShowPlayerDialog(playerid, DIALOG_RADIO_FREQ, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Radio Fx",
            "Error: Hanya dapat diisi angka!\nMasukkan frekuensi radio yang ingin diterapkan pada kolom dibawah ini\
            \n(Frekuensi harus berada diantara 0 - 9999)\
            \nCatatan: Masukkan frekuensi 0 untuk memutuskan saluran frekuensi/netral", "Submit", "Batal");

            if(strval(inputtext) < 0 || strval(inputtext) > 9999) return ShowPlayerDialog(playerid, DIALOG_RADIO_FREQ, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Radio Fx",
            "Error: Frequency dimulai dari 0 - 9999!\nMasukkan frekuensi radio yang ingin diterapkan pada kolom dibawah ini\
            \n(Frekuensi harus berada diantara 0 - 9999)\
            \nCatatan: Masukkan frekuensi 0 untuk memutuskan saluran frekuensi/netral", "Submit", "Batal");

            new freq = strval(inputtext);
            PlayerInFreq[playerid] = freq;
            
            if(freq == 0)
            {
                ToggleRadio[playerid] = false;
                RadioMicOn[playerid] = false;
                CallRemoteFunction("UpdatePlayerVoiceMicToggle", "dd", playerid, false);
                CallRemoteFunction("UpdatePlayerVoiceRadioToggle", "dd", playerid, false);
                CallRemoteFunction("AssignFreqToFSVoice", "ddd", playerid, false, freq);
                ShowTDN(playerid, NOTIFICATION_SUKSES, "Berhasil memutuskan saluran radio");
            }
            else if(freq == 1)
            {
                if(AccountData[playerid][pFaction] != FACTION_PEMERINTAH) return ShowTDN(playerid, NOTIFICATION_ERROR, "Freq 1 khusus Pihak Pemerintah!");
                
                PlayerTextDrawSetString(playerid, ATRP_RadioTD[playerid][7], "1");
                CallRemoteFunction("AssignFreqToFSVoice", "ddd", playerid, true, freq);
                ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil terhubung ke frequency ~y~%d", freq));
            }
            else if(freq == 2)
            {
                if(AccountData[playerid][pFaction] != FACTION_POLISI) return ShowTDN(playerid, NOTIFICATION_ERROR, "Freq 2 khusus Pihak Kepolisian");
                
                PlayerTextDrawSetString(playerid, ATRP_RadioTD[playerid][7], "1");
                CallRemoteFunction("AssignFreqToFSVoice", "ddd", playerid, true, freq);
                ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil terhubung ke frequency ~y~%d", freq));
            }
            else if(freq == 3)
            {
                if(AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Freq 3 khusus pihak medis");
                
                PlayerTextDrawSetString(playerid, ATRP_RadioTD[playerid][7], "1");
                CallRemoteFunction("AssignFreqToFSVoice", "ddd", playerid, true, freq);
                ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil terhubung ke frequency ~y~%d", freq));
            }
            else if(freq == 4)
            {
                if(AccountData[playerid][pFaction] != FACTION_POLISI && AccountData[playerid][pFaction] != FACTION_EMS) return ShowTDN(playerid, NOTIFICATION_ERROR, "Freq 4 khusus Pihak kepolisian dan juga pihak medis!");
                
                PlayerTextDrawSetString(playerid, ATRP_RadioTD[playerid][7], "1");
                CallRemoteFunction("AssignFreqToFSVoice", "ddd", playerid, true, freq);
                ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil terhubung ke frequency ~y~%d", freq));
            }
            else if(freq == 5)
            {
                if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Freq 5 khusus Pihak Bengkel");
                
                PlayerTextDrawSetString(playerid, ATRP_RadioTD[playerid][7], "1");
                CallRemoteFunction("AssignFreqToFSVoice", "ddd", playerid, true, freq);
                ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil terhubung ke frequency ~y~%d", freq));
            }
            else if(freq == 6)
            {
                if(AccountData[playerid][pFaction] != FACTION_PEDAGANG) return ShowTDN(playerid, NOTIFICATION_ERROR, "Freq 6 khusus Pihak pedagang!");
                
                PlayerTextDrawSetString(playerid, ATRP_RadioTD[playerid][7], "1");
                CallRemoteFunction("AssignFreqToFSVoice", "ddd", playerid, true, freq);
                ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil terhubung ke frequency ~y~%d", freq));
            }
            else if(freq <= 10)
            {
                if(AccountData[playerid][pFaction] != FACTION_POLISI && AccountData[playerid][pFaction] != FACTION_EMS && AccountData[playerid][pFaction] != FACTION_GOJEK) return ShowTDN(playerid, NOTIFICATION_ERROR, "Freq 7 - 10 khusus Saluran Gabungan Polisi dan EMS!");
                
                PlayerTextDrawSetString(playerid, ATRP_RadioTD[playerid][7], "1");
                CallRemoteFunction("AssignFreqToFSVoice", "ddd", playerid, true, freq);
                ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil terhubung ke frequency ~y~%d", freq));
            }
            else
            {
                PlayerTextDrawSetString(playerid, ATRP_RadioTD[playerid][7], "1");
                CallRemoteFunction("AssignFreqToFSVoice", "ddd", playerid, true, freq);
                ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil terhubung ke frequency ~y~%d", freq));
            }
            PlayerTextDrawSetString(playerid, ATRP_RadioTD[playerid][7], sprintf("%d", freq));
            ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
            RemovePlayerAttachedObject(playerid, 9);
            RadioTextdrawToggle(playerid, false);
            CancelSelectTextDraw(playerid);
        }
        case DIALOG_VOICEKEYS:
        {
            if(!response) return 1;
            switch(listitem)
            {
                case 0: // B Default
                {
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Voice Keys berhasil diubah menjadi Tombol B");
                    CallRemoteFunction("UpdatePlayerVoiceKeys", "dd", playerid, 1); // Default
                }
                case 1: // B Default
                {
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Voice Keys berhasil diubah menjadi Tombol R");
                    CallRemoteFunction("UpdatePlayerVoiceKeys", "dd", playerid, 2); // Default
                }
                case 2: // B Default
                {
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Voice Keys berhasil diubah menjadi Tombol X");
                    CallRemoteFunction("UpdatePlayerVoiceKeys", "dd", playerid, 3); // Default
                }
                case 3: // B Default
                {
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Voice Keys berhasil diubah menjadi Tombol Z");
                    CallRemoteFunction("UpdatePlayerVoiceKeys", "dd", playerid, 4); // Default
                }
                case 4: // Tombol Mouse Tengah
                {
                    ShowTDN(playerid, NOTIFICATION_SUKSES, "Voice Keys berhasil diubah menjadi Shift Key");
                    CallRemoteFunction("UpdatePlayerVoiceKeys", "dd", playerid, 5); // Default
                }
            }
        }
        case DIALOG_VOICEMODE:
        {
            if(!response) return 1;
            switch(listitem)
            {
                case 0: // teriak
                {
                    // PlayerTextDrawShow(playerid, ATRP_VoiceTD[playerid][0]);
                    // PlayerTextDrawShow(playerid, ATRP_VoiceTD[playerid][1]);
                    // PlayerTextDrawShow(playerid, ATRP_VoiceTD[playerid][2]);
                    PlayerTextDrawSetString(playerid, ATRP_VoiceTD[playerid][0], "VOICE: ~r~TERIAK");
                    PlayerTextDrawShow(playerid, ATRP_VoiceTD[playerid][0]);
                    Info(playerid, "Berhasil mengubah voice mode menjadi "RED"Teriak");
                    CallRemoteFunction("UpdatePlayerVoiceDistance", "ddf", playerid, 3, 30.0);
                }
                case 1: // Normal
                {
                    // PlayerTextDrawHide(playerid, ATRP_VoiceTD[playerid][0]);
                    // PlayerTextDrawShow(playerid, ATRP_VoiceTD[playerid][1]);
                    // PlayerTextDrawShow(playerid, ATRP_VoiceTD[playerid][2]);
                    PlayerTextDrawSetString(playerid, ATRP_VoiceTD[playerid][0], "VOICE: ~B~NORMAL");
                    PlayerTextDrawShow(playerid, ATRP_VoiceTD[playerid][0]);
                    Info(playerid, "Berhasil mengubah voice mode menjadi "SKYBLUE"Normal");
                    CallRemoteFunction("UpdatePlayerVoiceDistance", "ddf", playerid, 2, 15.0);
                }
                case 2: // Teriak
                {
                    // PlayerTextDrawHide(playerid, ATRP_VoiceTD[playerid][0]);
                    // PlayerTextDrawHide(playerid, ATRP_VoiceTD[playerid][1]);
                    // PlayerTextDrawShow(playerid, ATRP_VoiceTD[playerid][2]);
                    PlayerTextDrawSetString(playerid, ATRP_VoiceTD[playerid][0], "VOICE: ~y~BERBISIK");
                    PlayerTextDrawShow(playerid, ATRP_VoiceTD[playerid][0]);
                    Info(playerid, "Berhasil mengubah voice mode menjadi "YELLOW"Berbisik");
                    CallRemoteFunction("UpdatePlayerVoiceDistance", "ddf", playerid, 1, 8.0);
                }
            }
        }
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if (PRESSED(KEY_WALK) && !IsPlayerInAnyVehicle(playerid) || PRESSED(KEY_YES) && IsPlayerInAnyVehicle(playerid))
    {
        if (PlayerHasItem(playerid, "Radio") && ToggleRadio[playerid] && PlayerInFreq[playerid] >= 1)
        {   
            switch(RadioMicOn[playerid])
            {
                case false:
                {
                    RadioMicOn[playerid] = true;
                    GameTextForPlayer(playerid, "~w~Mic Radio~n~~g~Aktif", 2500, 6);
                    CallRemoteFunction("UpdatePlayerVoiceMicToggle", "dd", playerid, true);
                }
                case true:
                {
                    
                    RadioMicOn[playerid] = false;
                    GameTextForPlayer(playerid, "~w~Mic Radio~n~~r~Mati", 2500, 6);
                    CallRemoteFunction("UpdatePlayerVoiceMicToggle", "dd", playerid, false);
                }
            }
        }
    }
    return 1;
}

CMD:r(playerid, params[])
{
    if (!PlayerHasItem(playerid, "Radio")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Radio!");
    if (IsPlayerInWater(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membuka Radio saat berada di air!");

    SendRPMeAboveHead(playerid, "Membuka radio miliknya", X11_PLUM1);
    if (!IsPlayerInAnyVehicle(playerid))
    {
        ApplyAnimationEx(playerid, "ped", "Jetpack_Idle", 4.1, 0, 0, 0, 1, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 19942, 5, 0.043000, 0.022999, -0.006000, -112.000022, -34.900020, -8.500002, 1.000000, 1.000000, 1.000000);
    }

    Inventory_Close(playerid);
    RadioTextdrawToggle(playerid, true);
    SelectTextDraw(playerid, COLOR_CLIENT);
    return 1;
}

/*CMD:r(playerid, params[])
{
    if(!AccountData[playerid][pRadio]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki radio!");

    SendRPMeAboveHead(playerid, "Membuka Radio miliknya.", X11_PLUM1);
    if(!IsPlayerInAnyVehicle(playerid))
    {
        ApplyAnimation(playerid, "ped", "Jetpack_Idle", 4.1, 0, 0, 0, 1, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 19942, 5, 0.043000, 0.022999, -0.006000, -112.000022, -34.900020, -8.500002, 1.000000, 1.000000, 1.000000);
    }

    RadioTextdrawToggle(playerid, true);
    SelectTextDraw(playerid, 0xFF9999FF);
    return 1;
}*/

CMD:sv(playerid, params[])
{
    if(!IsPlayerConnected(playerid)) return 0;

    ShowPlayerDialog(playerid, DIALOG_VOICEMODE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Voice Range",
    ""RED"Teriak\
    \nNormal\
    \n"YELLOW"Berbisik", "Pilih", "Batal");
    return 1;
}

CMD:vkeys(playerid, params[])
{
    if(!IsPlayerConnected(playerid))
        return 0;
    
    ShowPlayerDialog(playerid, DIALOG_VOICEKEYS, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Voice Keybind",
    "Keybind: B (Default)\
    \n"GRAY"Keybind: R\
    \nKeybind: X\
    \n"GRAY"Keybind: Z\
    \nKeybind: SHIFT", "Pilih", "Batal");
    return 1;
}

/*CMD:giveradio(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);
	
	new otherid;
	if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/giveradio [name/playerid]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(AccountData[otherid][pRadio]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sudah memiliki radio!");

	AccountData[otherid][pRadio] = 1;
	SendClientMessageEx(otherid, X11_ARWIN, "[AdmCmd] "RED"%s"ARWIN1" telah memberikan anda Radio.", AccountData[playerid][pAdminname]);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah memberikan Radio kepada pemain "YELLOW"%s(%d).", AccountData[playerid][pAdminname], AccountData[otherid][pName], otherid);

	new query[255];
	mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_Radio`=1 WHERE `pID`=%d", AccountData[otherid][pID]);
	mysql_tquery(g_SQL, query);
	return 1;
}*/

CMD:atakeradio(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 3) return PermissionError(playerid);

	new 
		otherid
	;
	if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/atakeradio [name/playerid]");
	if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
	if(!PlayerHasItem(otherid, "Radio")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki Radio!");

    Inventory_Remove(otherid, "Radio", Inventory_Count(otherid, "Radio"));
	SendClientMessageEx(otherid, X11_ARWIN, "[AdmCmd] "RED"%s"ARWIN1" telah mengambil Radio anda.", AccountData[playerid][pAdminname]);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah mengambil Radio pemain "YELLOW"%s(%d).", AccountData[playerid][pAdminname], AccountData[otherid][pName], otherid);
    if(ToggleRadio[otherid] || RadioMicOn[otherid])
    {
        ToggleRadio[otherid] = false;
        RadioMicOn[otherid] = false;
        CallRemoteFunction("UpdatePlayerVoiceMicToggle", "dd", otherid, false);
        CallRemoteFunction("UpdatePlayerVoiceRadioToggle", "dd", otherid, false);
        CallRemoteFunction("AssignFreqToFSVoice", "ddd", otherid, true, 0);
        PlayerTextDrawSetString(otherid, ATRP_RadioTD[otherid][7], "0");
    }

	// new query[255];
	// mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET `Char_Radio`=0 WHERE `pID`=%d", AccountData[otherid][pID]);
	// mysql_tquery(g_SQL, query);
	return 1;
}