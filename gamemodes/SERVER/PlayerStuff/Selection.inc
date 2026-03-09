public OnPlayerSelectionMenuResponse(playerid, extraid, response, listitem, modelid)
{
    switch(extraid)
    {
        case MODEL_SELECTION_Waa:
	    {
	        if(response)
	        {
                new
                price = 5000,
                vehicleid
                ;

                if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
                    return Error(playerid, "You need to be inside vehicle as driver");

                vehicleid = Vehicle_Nearest(playerid);

                if(vehicleid == -1)
                    return 0;

                Vehicle_ObjectAddObjects(playerid, vehicleid, modelid, OBJECT_TYPE_BODY);

                SendClientMessageEx(playerid, ARWIN,"MODSHOP: "WHITE_E"You have purchased a {00FFFF}%s "WHITE_E"for "GREEN_E"$%s.", GetVehObjectNameByModel(modelid), FormatMoney(price));
            }
        } 
        case MODEL_SELECTION_Loco:
	    {
	        if(response)
	        {
                new
                price = 5000,
                vehicleid
                ;

                if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
                    return Error(playerid, "You need to be inside vehicle as driver");

                vehicleid = Vehicle_Nearest(playerid);

                if(vehicleid == -1)
                    return 0;

                Vehicle_ObjectAddObjects(playerid, vehicleid, modelid, OBJECT_TYPE_BODY);

                SendClientMessageEx(playerid, ARWIN,"MODSHOP: "WHITE_E"You have purchased a {00FFFF}%s "WHITE_E"for "GREEN_E"$%s.", GetVehObjectNameByModel(modelid), FormatMoney(price));
            }
        } 
        case MODEL_SELECTION_Transfender:
	    {
	        if(response)
	        {
                new
                price = 5000,
                vehicleid
                ;

                if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
                    return Error(playerid, "You need to be inside vehicle as driver");

                vehicleid = Vehicle_Nearest(playerid);

                if(vehicleid == -1)
                    return 0;

                Vehicle_ObjectAddObjects(playerid, vehicleid, modelid, OBJECT_TYPE_BODY);

                SendClientMessageEx(playerid, ARWIN,"MODSHOP: "WHITE_E"You have purchased a {00FFFF}%s "WHITE_E"for "GREEN_E"$%s.", GetVehObjectNameByModel(modelid), FormatMoney(price));
            }
        } 
    }
    return 1;
}