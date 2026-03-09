stock ShowPlayerRadial1(playerid, bool: status)
{
	if (status)
	{
		for(new x = 0; x < 15; x ++) PlayerTextDrawHide(playerid, HbeStuffs[playerid][x]);
        HideHBE(playerid);
        forex (txd, 82) PlayerTextDrawShow(playerid, RadialFertod[playerid][txd]);
		SelectTextDraw(playerid, COLOR_CLIENT);
	}
	else
	{
		forex (txd, 82) PlayerTextDrawHide(playerid, RadialFertod[playerid][txd]);
		CancelSelectTextDraw(playerid);
		ShowHbeTextdraws(playerid, AccountData[playerid][pHUDMode]);
	}
	return 1;
}