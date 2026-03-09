#define MAX_ANIM_DATA 100
#define MAX_ANIM_STRING 512

new PlayerText: NamaServer[MAX_PLAYERS][1];
new ServerName[MAX_PLAYERS];

enum E_ANIM_DATA
{
	data_string[MAX_ANIM_STRING],
	data_frame,
	data_chars, 
	data_color[4],
	data_color_1[15],
	data_color_2[15]
}
new AnimData[MAX_ANIM_DATA][E_ANIM_DATA];

static FindFreeAnimDataID()
{
	for (new i = 0; i < MAX_ANIM_DATA; i++) {
		if (strlen(AnimData[i][data_string]) <= 0) {
			return i;
		}
	}
	return -1;
}

stock CreateTextdrawAnimation(playerid, PlayerText:textdraw, frame, color[], string[])
{
	new id = FindFreeAnimDataID();
	if (id == -1) return 1;

	for (new i = 0; i < strlen(string); i++) {
		if (string[i] == ' ') {
			string[i] = '_';
		}
	}

	AnimData[id][data_chars] = 0;
	AnimData[id][data_frame] = frame;
	format (AnimData[id][data_string], MAX_ANIM_STRING, "%s", string);
	format (AnimData[id][data_color], 4, "%s", color);
	format (AnimData[id][data_color_1], 15, "%s~h~~h~~h~", color);
	format (AnimData[id][data_color_2], 15, "%s~h~~h~", color);
	PlayerTextDrawSetString(playerid, textdraw, "");

	SetTimerEx("UpdateTextdrawAnimation", frame, false, "iii", playerid, _:textdraw, id);
	return 1;
}

function UpdateTextdrawAnimation(playerid, PlayerText:textdraw, id)
{
	new tmp[MAX_ANIM_STRING];
	new len = strlen(AnimData[id][data_string]);
	new idx = AnimData[id][data_chars]++;

	if (AnimData[id][data_string][idx] == '~') {
		AnimData[id][data_chars] += 3;
		idx += 3;
	}

	strmid(tmp, AnimData[id][data_string], 0, idx);	

	if (idx < len) {
		if (idx > 2 && (tmp[idx - 2] != '~' && tmp[idx - 1] != '~' && tmp[idx] != '~') ) {
			strins(tmp, AnimData[id][data_color_2], idx - 2);
			strins(tmp, AnimData[id][data_color_1], idx + strlen(AnimData[id][data_color_2]) - 1);
		}

		SetTimerEx("UpdateTextdrawAnimation", AnimData[id][data_frame], false, "iii", playerid, _:textdraw, id);
	} else {
		format (AnimData[id][data_string], MAX_ANIM_STRING, "");
		CallRemoteFunction("OnTextdrawAnimationFinish", "ii", playerid, _:textdraw);
	}

	strins(tmp, AnimData[id][data_color], 0);
	PlayerTextDrawSetString(playerid, textdraw, tmp);
	return 1;
}

function TDWEBACCOUNT(playerid)
{
	PlayerTextDrawHide(playerid, NamaServer[playerid][0]);
	PlayerTextDrawShow(playerid, NamaServer[playerid][0]);
	CreateTextdrawAnimation(playerid, NamaServer[playerid][0], 150, "", "District");
	ServerName[playerid] = 0;
	return 1;
}
 
function TDNAMASERVER(playerid)
{
	PlayerTextDrawHide(playerid, NamaServer[playerid][0]);
	PlayerTextDrawShow(playerid, NamaServer[playerid][0]);
	CreateTextdrawAnimation(playerid, NamaServer[playerid][0], 150, "", "District");
	ServerName[playerid] = 1;
	return 1;
}

function OnTextdrawAnimationFinish(playerid, PlayerText:textdraw)
{
	if(ServerName[playerid] == 0)
	{
		SetTimerEx("TDNAMASERVER", 15000, false, "i", playerid);
	}
	if(ServerName[playerid] == 1)
	{
		SetTimerEx("TDWEBACCOUNT", 15000, false, "i", playerid);
	}
	return 1;
}

stock CreateTextDrawNamaServer(playerid)
{
    NamaServer[playerid][0] = CreatePlayerTextDraw(playerid, 491.000, 8.000, "District");
	PlayerTextDrawLetterSize(playerid, NamaServer[playerid][0], 0.180, 1.098);
	PlayerTextDrawAlignment(playerid, NamaServer[playerid][0], 1);
	PlayerTextDrawColor(playerid, NamaServer[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, NamaServer[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, NamaServer[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, NamaServer[playerid][0], 150);
	PlayerTextDrawFont(playerid, NamaServer[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, NamaServer[playerid][0], 1);

	PlayerTextDrawShow(playerid, NamaServer[playerid][0]);
	CreateTextdrawAnimation(playerid, NamaServer[playerid][0], 150, "", "District");
	ServerName[playerid] = 1;
}
