#include <YSI\y_hooks>

/*SetPlayerStreamerSettings(playerid) {
	switch (AccountData[playerid][pStreamer]) {
		case 0: {
			Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 250, playerid);
			Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, 0.3, playerid);
		}
		case 1: {
			Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 350, playerid);
			Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, 0.6, playerid);
		} 
		case 2: {
			Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 700, playerid);
			Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, 1.0, playerid);
		}
		case 3: {
			Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 800, playerid);
			Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, 1.5, playerid);
		} 
		case 4: {
			Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 950, playerid);
			Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, 2.0, playerid);
		}
		default: {
			Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 950, playerid);
			Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, 1.0, playerid);
		}
	}
}

new const StreamerSettingName[5][] = {
	"Potato",
	"Soft",
	"Normal",
	"High",
	"Max"
};

Dialog:StreamerSetting(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan!");
	if(response) {
		AccountData[playerid][pStreamer] = listitem;
		SetPlayerStreamerSettings(playerid);
		ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Render setting berhasi diubah menjadi %s", StreamerSettingName[listitem]));
	}
	return 1;	
}

CMD:setrender(playerid, params[])
{
	if(!IsPlayerConnected(playerid))
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus terkoneksi ke dalam server!");
	
	new str[512];
	strcat(str, "Setting\tObject Limit\tMultiplier\n");
	strcat(str, "Potato\t250\t0.3\n");
	strcat(str, "Soft\t350\t0.6\n");
	strcat(str, "Normal\t700 (default)\t1.0\n");
	strcat(str, "High\t800\t1.5\n");
	strcat(str, "Max\t950\t2.0\n");
	Dialog_Show(playerid, StreamerSetting, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Render Setting", str, "Pilih", "Batal");
	return 1;
}*/

stock StreamerConfig()
{
	Streamer_MaxItems(STREAMER_TYPE_OBJECT, 990000);
	Streamer_MaxItems(STREAMER_TYPE_MAP_ICON, 2000);
	Streamer_MaxItems(STREAMER_TYPE_PICKUP, 2000);
	for(new playerid = (GetMaxPlayers() - 1); playerid != -1; playerid--)
	{
		Streamer_DestroyAllVisibleItems(playerid, 0);
	}
	return 1;
}

GetPlayerRenderName(playerid)
{
	static frmtname[125];
	if(AccountData[playerid][pMapRender] == 250)
	{
		frmtname = ""RED"Very Low";
	}
	else if(AccountData[playerid][pMapRender] == 500)
	{
		frmtname = ""DARKORANGE"Low";
	}
	else if(AccountData[playerid][pMapRender] == 750)
	{
		frmtname = ""SKYBLUE"Medium";
	}
	else if(AccountData[playerid][pMapRender] == 1000)
	{
		frmtname = ""GREEN"High";
	}
	return frmtname;
}

/*CMD:setrender(playerid, params[])
{
	if(!SQL_IsCharacterLogged(playerid))
		return 0;
	
	ShowPlayerDialog(playerid, DIALOG_STREAMER_CONFIG, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Render Settings",
	"Jenis\tRadius\
	\nSoft\t300.0\
	\n"GRAY"Medium\t500.0\
	\nHigh\t1000.0 (default)", "Pilih", "Batal");
	return 1;
}*/

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case DIALOG_STREAMER_CONFIG:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
			switch(listitem)
			{
				case 0: // soft
				{
					AccountData[playerid][pMapSettings] = 0.25;
					AccountData[playerid][pMapRender] = 250;
					Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, AccountData[playerid][pMapRender], playerid);
					Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, AccountData[playerid][pMapSettings], playerid);
					Info(playerid, "Anda berhasil mengubah dynamic render object to "GREEN"Very Low");
				}
				case 1: // soft
				{
					AccountData[playerid][pMapSettings] = 0.5;
					AccountData[playerid][pMapRender] = 500;
					Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, AccountData[playerid][pMapRender], playerid);
					Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, AccountData[playerid][pMapSettings], playerid);
					Info(playerid, "Anda berhasil mengubah dynamic render object to "GREEN"Low");
				}
				case 2: //medium
				{
					AccountData[playerid][pMapSettings] = 1.0;
					AccountData[playerid][pMapRender] = 750;
					Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, AccountData[playerid][pMapRender], playerid);
					Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, AccountData[playerid][pMapSettings], playerid);
					Info(playerid, "Anda berhasil mengubah dynamic render object to "GREEN"Medium");
				}
				case 3: //High
				{
					AccountData[playerid][pMapSettings] = 2.0;
					AccountData[playerid][pMapRender] = 1000;
					Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, AccountData[playerid][pMapRender], playerid);
					Streamer_SetRadiusMultiplier(STREAMER_TYPE_OBJECT, AccountData[playerid][pMapSettings], playerid);
					Info(playerid, "Anda berhasil mengubah dynamic render object to "GREEN"High");
				}
			}
			Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
			// Streamer_ToggleIdleUpdate(playerid, true);
		}
	}
	return 1;
}

// hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
// {
// 	switch(dialogid)
// 	{
// 		case DIALOG_STREAMER_CONFIG:
// 		{
// 			if(!response) return 0;
// 			if(response)
// 			{
// 				switch(listitem)
// 				{
// 					case 0:
// 					{
// 						new config = 300;
						
// 						Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, config, playerid);
// 						ShowTDN(playerid, NOTIFICATION_SUKSES, "Render setting berhasil diubah menjadi soft!");
// 					}
// 					case 1:
// 					{
// 						new config = 500;
						
// 						Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, config, playerid);
// 						ShowTDN(playerid, NOTIFICATION_SUKSES, "Render setting berhasil diubah menjadi medium!");
// 					}
// 					case 2:
// 					{
// 						new config = 1000;
						
// 						Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, config, playerid);
// 						ShowTDN(playerid, NOTIFICATION_SUKSES, "Render setting berhasil diubah menjadi high!");
// 					}
// 				}
// 			}
// 		}
// 	}
// 	return 1;
// }
