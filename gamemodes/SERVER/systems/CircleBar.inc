#define MAX_CIRCLE_TD   (52)

new PlayerText:hunger[MAX_PLAYERS][MAX_CIRCLE_TD];
new PlayerText:thirst[MAX_PLAYERS][MAX_CIRCLE_TD];
new PlayerText:stress[MAX_PLAYERS][MAX_CIRCLE_TD];

enum e_circledata
{
    bool:chunger,
    bool:cthirst,
    bool:cstress
};
new CircleData[MAX_PLAYERS][e_circledata];

static stock ctd(Float:angle, Float:distance, Float:sx, Float:sy, & Float:x, & Float:y)
{
	x = sx + (distance * floatsin(-angle, degrees));
	y = sy + (distance * floatcos(angle, degrees));
	return 1;
}

stock ShowPlayerCircleProgress(playerid, value, Float:pos_x, Float:pos_y, color = 0xFF0000FF, background_color = 168432895, Float:size = 9.0, Float:thickness = 0.3)
{
	new count = 0, Float:x, Float:y, percent;
	if (IsPlayerNPC(playerid)) return 0;
	value = value < 0 ? 0 : value;
	value = value > 100 ? 100 : value;
	percent = (60 * value) / 100;

	for(new i = 0; i < MAX_CIRCLE_TD; i ++)
	{
		PlayerTextDrawDestroy(playerid, hunger[playerid][i]);
	}

	for (new Float:i = 0.0; i < 360.0; i += 7.0)
	{
		if(count < MAX_CIRCLE_TD)
		{
			ctd(i + 180.0, size, pos_x, pos_y, x, y);
			hunger[playerid][count] = CreatePlayerTextDraw(playerid, x, y, ".");
			PlayerTextDrawAlignment(playerid, hunger[playerid][count], 2);
			PlayerTextDrawLetterSize(playerid, hunger[playerid][count], thickness, thickness * 3.0);
			PlayerTextDrawSetShadow(playerid, hunger[playerid][count], 0);
			PlayerTextDrawColor(playerid, hunger[playerid][count], percent <= count ? (background_color) : (color));
			PlayerTextDrawShow(playerid, hunger[playerid][count]);
			CircleData[count][chunger] = true;
			count ++;
		}
	}
	return 1;
}

stock ShowPlayerCircleProgress2(playerid, value, Float:pos_x, Float:pos_y, color = 0xFF0000FF, background_color = 168432895, Float:size = 9.0, Float:thickness = 0.3)
{
	new count = 0, Float:x, Float:y, percent;
	if (IsPlayerNPC(playerid)) return 0;
	value = value < 0 ? 0 : value;
	value = value > 100 ? 100 : value;
	percent = (60 * value) / 100;

	for(new i = 0; i < MAX_CIRCLE_TD; i ++)
	{
		PlayerTextDrawDestroy(playerid, thirst[playerid][i]);
	}

	for (new Float:i = 0.0; i < 360.0; i += 7.0)
	{
		if(count < MAX_CIRCLE_TD)
		{
			ctd(i + 180.0, size, pos_x, pos_y, x, y);
			thirst[playerid][count] = CreatePlayerTextDraw(playerid, x, y, ".");
			PlayerTextDrawAlignment(playerid, thirst[playerid][count], 2);
			PlayerTextDrawLetterSize(playerid, thirst[playerid][count], thickness, thickness * 3.0);
			PlayerTextDrawSetShadow(playerid, thirst[playerid][count], 0);
			PlayerTextDrawColor(playerid, thirst[playerid][count], percent <= count ? (background_color) : (color));
			PlayerTextDrawShow(playerid, thirst[playerid][count]);
			CircleData[count][cthirst] = true;
			count ++;
		}
	}
	
	return 1;
}

stock ShowPlayerCircleProgress3(playerid, value, Float:pos_x, Float:pos_y, color = 0xFF0000FF, background_color = 168432895, Float:size = 9.0, Float:thickness = 0.3)
{
	new count = 0, Float:x, Float:y, percent;
	if (IsPlayerNPC(playerid)) return 0;
	value = value < 0 ? 0 : value;
	value = value > 100 ? 100 : value;
	percent = (60 * value) / 100;

	for(new i = 0; i < MAX_CIRCLE_TD; i ++)
	{
		PlayerTextDrawDestroy(playerid, stress[playerid][i]);
	}

	for (new Float:i = 0.0; i < 360.0; i += 7.0)
	{
		if(count < MAX_CIRCLE_TD)
		{
			ctd(i + 180.0, size, pos_x, pos_y, x, y);
			stress[playerid][count] = CreatePlayerTextDraw(playerid, x, y, ".");
			PlayerTextDrawAlignment(playerid, stress[playerid][count], 2);
			PlayerTextDrawLetterSize(playerid, stress[playerid][count], thickness, thickness * 3.0);
			PlayerTextDrawSetShadow(playerid, stress[playerid][count], 0);
			PlayerTextDrawColor(playerid, stress[playerid][count], percent <= count ? (background_color) : (color));
			PlayerTextDrawShow(playerid, stress[playerid][count]);
			CircleData[count][cstress] = true;
			count ++;
		}
	}
	
	return 1;
}

stock DestroyHungerCircleProgress(playerid)
{
	if (IsPlayerNPC(playerid)) return 0;
    

	for (new x = 0; x < MAX_CIRCLE_TD; x++)
	{
		PlayerTextDrawDestroy(playerid, hunger[playerid][x]);
		hunger[playerid][x] = PlayerText:0xFFFF;
		CircleData[x][chunger] = false;

		//
		PlayerTextDrawDestroy(playerid, thirst[playerid][x]);
		thirst[playerid][x] = PlayerText:0xFFFF;
		CircleData[x][cthirst] = false;

		PlayerTextDrawDestroy(playerid, stress[playerid][x]);
		stress[playerid][x] = PlayerText:0xFFFF;
		CircleData[x][cstress] = false;
	}
	return 1;
}