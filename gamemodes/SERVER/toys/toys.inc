// Toy System
enum e_toy_data
{
	toy_model,
	toy_bone,
	toy_status,
	Float:toy_x,
	Float:toy_y,
	Float:toy_z,
	Float:toy_rx,
	Float:toy_ry,
	Float:toy_rz,
	Float:toy_sx,
	Float:toy_sy,
	Float:toy_sz
}
new pToys[MAX_PLAYERS][4][e_toy_data];

forward LoadPlayerToys(playerid);
public LoadPlayerToys(playerid)
{
	new rows = cache_num_rows();
	if(rows)
	{
		AccountData[playerid][PurchasedToy] = true;
		cache_get_value_name_int(0, "Slot0_Model", pToys[playerid][0][toy_model]);
  		cache_get_value_name_int(0, "Slot0_Bone", pToys[playerid][0][toy_bone]);
		cache_get_value_name_int(0, "Slot0_Status", pToys[playerid][0][toy_status]);
  		cache_get_value_name_float(0, "Slot0_XPos", pToys[playerid][0][toy_x]);
  		cache_get_value_name_float(0, "Slot0_YPos", pToys[playerid][0][toy_y]);
  		cache_get_value_name_float(0, "Slot0_ZPos", pToys[playerid][0][toy_z]);
  		cache_get_value_name_float(0, "Slot0_XRot", pToys[playerid][0][toy_rx]);
  		cache_get_value_name_float(0, "Slot0_YRot", pToys[playerid][0][toy_ry]);
  		cache_get_value_name_float(0, "Slot0_ZRot", pToys[playerid][0][toy_rz]);
  		cache_get_value_name_float(0, "Slot0_XScale", pToys[playerid][0][toy_sx]);
  		cache_get_value_name_float(0, "Slot0_YScale", pToys[playerid][0][toy_sy]);
		cache_get_value_name_float(0, "Slot0_ZScale", pToys[playerid][0][toy_sz]);
		
		cache_get_value_name_int(0, "Slot1_Model", pToys[playerid][1][toy_model]);
  		cache_get_value_name_int(0, "Slot1_Bone", pToys[playerid][1][toy_bone]);
		cache_get_value_name_int(0, "Slot1_Status", pToys[playerid][1][toy_status]);
  		cache_get_value_name_float(0, "Slot1_XPos", pToys[playerid][1][toy_x]);
  		cache_get_value_name_float(0, "Slot1_YPos", pToys[playerid][1][toy_y]);
  		cache_get_value_name_float(0, "Slot1_ZPos", pToys[playerid][1][toy_z]);
  		cache_get_value_name_float(0, "Slot1_XRot", pToys[playerid][1][toy_rx]);
  		cache_get_value_name_float(0, "Slot1_YRot", pToys[playerid][1][toy_ry]);
  		cache_get_value_name_float(0, "Slot1_ZRot", pToys[playerid][1][toy_rz]);
  		cache_get_value_name_float(0, "Slot1_XScale", pToys[playerid][1][toy_sx]);
  		cache_get_value_name_float(0, "Slot1_YScale", pToys[playerid][1][toy_sy]);
		cache_get_value_name_float(0, "Slot1_ZScale", pToys[playerid][1][toy_sz]);
		
		cache_get_value_name_int(0, "Slot2_Model", pToys[playerid][2][toy_model]);
  		cache_get_value_name_int(0, "Slot2_Bone", pToys[playerid][2][toy_bone]);
		cache_get_value_name_int(0, "Slot2_Status", pToys[playerid][2][toy_status]);
  		cache_get_value_name_float(0, "Slot2_XPos", pToys[playerid][2][toy_x]);
  		cache_get_value_name_float(0, "Slot2_YPos", pToys[playerid][2][toy_y]);
  		cache_get_value_name_float(0, "Slot2_ZPos", pToys[playerid][2][toy_z]);
  		cache_get_value_name_float(0, "Slot2_XRot", pToys[playerid][2][toy_rx]);
  		cache_get_value_name_float(0, "Slot2_YRot", pToys[playerid][2][toy_ry]);
  		cache_get_value_name_float(0, "Slot2_ZRot", pToys[playerid][2][toy_rz]);
  		cache_get_value_name_float(0, "Slot2_XScale", pToys[playerid][2][toy_sx]);
  		cache_get_value_name_float(0, "Slot2_YScale", pToys[playerid][2][toy_sy]);
		cache_get_value_name_float(0, "Slot2_ZScale", pToys[playerid][2][toy_sz]);
		
		cache_get_value_name_int(0, "Slot3_Model", pToys[playerid][3][toy_model]);
  		cache_get_value_name_int(0, "Slot3_Bone", pToys[playerid][3][toy_bone]);
		cache_get_value_name_int(0, "Slot3_Status", pToys[playerid][3][toy_status]);
  		cache_get_value_name_float(0, "Slot3_XPos", pToys[playerid][3][toy_x]);
  		cache_get_value_name_float(0, "Slot3_YPos", pToys[playerid][3][toy_y]);
  		cache_get_value_name_float(0, "Slot3_ZPos", pToys[playerid][3][toy_z]);
  		cache_get_value_name_float(0, "Slot3_XRot", pToys[playerid][3][toy_rx]);
  		cache_get_value_name_float(0, "Slot3_YRot", pToys[playerid][3][toy_ry]);
  		cache_get_value_name_float(0, "Slot3_ZRot", pToys[playerid][3][toy_rz]);
  		cache_get_value_name_float(0, "Slot3_XScale", pToys[playerid][3][toy_sx]);
  		cache_get_value_name_float(0, "Slot3_YScale", pToys[playerid][3][toy_sy]);
		cache_get_value_name_float(0, "Slot3_ZScale", pToys[playerid][3][toy_sz]);

		AttachPlayerToys(playerid); // Attach player Toys.
		printf("[Player Fashion] Memuat player fashion untuk: %s(%d)", AccountData[playerid][pName], playerid);
	}
	return 1;
}

/*MySQL_CreatePlayerToy(playerid)
{
	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `toys` (`Owner`) VALUES ('%s')", AccountData[playerid][pName]);
	mysql_tquery(g_SQL, query);
	AccountData[playerid][PurchasedToy] = true;

	for(new i = 0; i < 4; i++)
	{
		pToys[playerid][i][toy_model] = 0;
		pToys[playerid][i][toy_bone] = 1;
		pToys[playerid][i][toy_status] = 1;
		pToys[playerid][i][toy_x] = 0.0;
		pToys[playerid][i][toy_y] = 0.0;
		pToys[playerid][i][toy_z] = 0.0;
		pToys[playerid][i][toy_rx] = 0.0;
		pToys[playerid][i][toy_ry] = 0.0;
		pToys[playerid][i][toy_rz] = 0.0;
		pToys[playerid][i][toy_sx] = 1.0;
		pToys[playerid][i][toy_sy] = 1.0;
		pToys[playerid][i][toy_sz] = 1.0;
	}
}*/

AttachPlayerToys(playerid)
{	
	if(AccountData[playerid][PurchasedToy] == false) return 1;

	if(pToys[playerid][0][toy_model] != 0)
	{
		if(pToys[playerid][0][toy_status] != 0)
		{
			SetPlayerAttachedObject(playerid,
			0,
			pToys[playerid][0][toy_model],
			pToys[playerid][0][toy_bone],
			pToys[playerid][0][toy_x],
			pToys[playerid][0][toy_y],
			pToys[playerid][0][toy_z],
			pToys[playerid][0][toy_rx],
			pToys[playerid][0][toy_ry],
			pToys[playerid][0][toy_rz],
			pToys[playerid][0][toy_sx],
			pToys[playerid][0][toy_sy],
			pToys[playerid][0][toy_sz]);
		}
	}
	
	if(pToys[playerid][1][toy_model] != 0)
	{
		if(pToys[playerid][1][toy_status] != 0)
		{
			SetPlayerAttachedObject(playerid,
			1,
			pToys[playerid][1][toy_model],
			pToys[playerid][1][toy_bone],
			pToys[playerid][1][toy_x],
			pToys[playerid][1][toy_y],
			pToys[playerid][1][toy_z],
			pToys[playerid][1][toy_rx],
			pToys[playerid][1][toy_ry],
			pToys[playerid][1][toy_rz],
			pToys[playerid][1][toy_sx],
			pToys[playerid][1][toy_sy],
			pToys[playerid][1][toy_sz]);
		}
	}
	
	if(pToys[playerid][2][toy_model] != 0)
	{
		if(pToys[playerid][2][toy_status] != 0)
		{
			SetPlayerAttachedObject(playerid,
			2,
			pToys[playerid][2][toy_model],
			pToys[playerid][2][toy_bone],
			pToys[playerid][2][toy_x],
			pToys[playerid][2][toy_y],
			pToys[playerid][2][toy_z],
			pToys[playerid][2][toy_rx],
			pToys[playerid][2][toy_ry],
			pToys[playerid][2][toy_rz],
			pToys[playerid][2][toy_sx],
			pToys[playerid][2][toy_sy],
			pToys[playerid][2][toy_sz]);
		}
	}
	
	if(pToys[playerid][3][toy_model] != 0)
	{
		if(pToys[playerid][3][toy_status] != 0)
		{
			SetPlayerAttachedObject(playerid,
			3,
			pToys[playerid][3][toy_model],
			pToys[playerid][3][toy_bone],
			pToys[playerid][3][toy_x],
			pToys[playerid][3][toy_y],
			pToys[playerid][3][toy_z],
			pToys[playerid][3][toy_rx],
			pToys[playerid][3][toy_ry],
			pToys[playerid][3][toy_rz],
			pToys[playerid][3][toy_sx],
			pToys[playerid][3][toy_sy],
			pToys[playerid][3][toy_sz]);
		}
	}
	
	return 1;
}

stock Float:SafeFloat(Float:value)
{
    // deteksi NaN (karena NaN != NaN selalu true)
    if(value != value) return 0.0;

    // batasi nilai ekstrem biar gak bikin error MySQL
    if(value > 100000.0 || value < -100000.0) return 0.0;

    return value;
}

MySQL_SavePlayerToys(playerid)
{
    new cQuery[4096]; // perbesar dikit karena lebih panjang
    mysql_format(g_SQL, cQuery, sizeof(cQuery),
        "UPDATE toys SET \
        Slot0_Model=%d, Slot0_Bone=%d, Slot0_Status=%d, Slot0_XPos=%f, Slot0_YPos=%f, Slot0_ZPos=%f, Slot0_XRot=%f, Slot0_YRot=%f, Slot0_ZRot=%f, Slot0_XScale=%f, Slot0_YScale=%f, Slot0_ZScale=%f,\
        Slot1_Model=%d, Slot1_Bone=%d, Slot1_Status=%d, Slot1_XPos=%f, Slot1_YPos=%f, Slot1_ZPos=%f, Slot1_XRot=%f, Slot1_YRot=%f, Slot1_ZRot=%f, Slot1_XScale=%f, Slot1_YScale=%f, Slot1_ZScale=%f,\
        Slot2_Model=%d, Slot2_Bone=%d, Slot2_Status=%d, Slot2_XPos=%f, Slot2_YPos=%f, Slot2_ZPos=%f, Slot2_XRot=%f, Slot2_YRot=%f, Slot2_ZRot=%f, Slot2_XScale=%f, Slot2_YScale=%f, Slot2_ZScale=%f,\
        Slot3_Model=%d, Slot3_Bone=%d, Slot3_Status=%d, Slot3_XPos=%f, Slot3_YPos=%f, Slot3_ZPos=%f, Slot3_XRot=%f, Slot3_YRot=%f, Slot3_ZRot=%f, Slot3_XScale=%f, Slot3_YScale=%f, Slot3_ZScale=%f \
        WHERE Owner='%s'",

        // Slot 0
        pToys[playerid][0][toy_model],
        pToys[playerid][0][toy_bone],
        pToys[playerid][0][toy_status],
        SafeFloat(pToys[playerid][0][toy_x]),
        SafeFloat(pToys[playerid][0][toy_y]),
        SafeFloat(pToys[playerid][0][toy_z]),
        SafeFloat(pToys[playerid][0][toy_rx]),
        SafeFloat(pToys[playerid][0][toy_ry]),
        SafeFloat(pToys[playerid][0][toy_rz]),
        SafeFloat(pToys[playerid][0][toy_sx]),
        SafeFloat(pToys[playerid][0][toy_sy]),
        SafeFloat(pToys[playerid][0][toy_sz]),

        // Slot 1
        pToys[playerid][1][toy_model],
        pToys[playerid][1][toy_bone],
        pToys[playerid][1][toy_status],
        SafeFloat(pToys[playerid][1][toy_x]),
        SafeFloat(pToys[playerid][1][toy_y]),
        SafeFloat(pToys[playerid][1][toy_z]),
        SafeFloat(pToys[playerid][1][toy_rx]),
        SafeFloat(pToys[playerid][1][toy_ry]),
        SafeFloat(pToys[playerid][1][toy_rz]),
        SafeFloat(pToys[playerid][1][toy_sx]),
        SafeFloat(pToys[playerid][1][toy_sy]),
        SafeFloat(pToys[playerid][1][toy_sz]),

        // Slot 2
        pToys[playerid][2][toy_model],
        pToys[playerid][2][toy_bone],
        pToys[playerid][2][toy_status],
        SafeFloat(pToys[playerid][2][toy_x]),
        SafeFloat(pToys[playerid][2][toy_y]),
        SafeFloat(pToys[playerid][2][toy_z]),
        SafeFloat(pToys[playerid][2][toy_rx]),
        SafeFloat(pToys[playerid][2][toy_ry]),
        SafeFloat(pToys[playerid][2][toy_rz]),
        SafeFloat(pToys[playerid][2][toy_sx]),
        SafeFloat(pToys[playerid][2][toy_sy]),
        SafeFloat(pToys[playerid][2][toy_sz]),

        // Slot 3
        pToys[playerid][3][toy_model],
        pToys[playerid][3][toy_bone],
        pToys[playerid][3][toy_status],
        SafeFloat(pToys[playerid][3][toy_x]),
        SafeFloat(pToys[playerid][3][toy_y]),
        SafeFloat(pToys[playerid][3][toy_z]),
        SafeFloat(pToys[playerid][3][toy_rx]),
        SafeFloat(pToys[playerid][3][toy_ry]),
        SafeFloat(pToys[playerid][3][toy_rz]),
        SafeFloat(pToys[playerid][3][toy_sx]),
        SafeFloat(pToys[playerid][3][toy_sy]),
        SafeFloat(pToys[playerid][3][toy_sz]),

        AccountData[playerid][pName]
    );

    mysql_tquery(g_SQL, cQuery);
    return 1;
}

CMD:fashion(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus turun dari kendaraan");
	if(AccountData[playerid][IsLoggedIn] == false) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu harus login!");
	new string[350];
	if(pToys[playerid][0][toy_model] == 0)
	{
	    strcat(string, ""WHITE"Hat/Helmet\n");
	}
	else strcat(string, ""WHITE"Hat/Helmet\n");

	if(pToys[playerid][1][toy_model] == 0)
	{
	    strcat(string, ""VERONA_ARWIN"Kacamata\n");
	}
	else strcat(string, ""VERONA_ARWIN"Kacamata\n");

	if(pToys[playerid][2][toy_model] == 0)
	{
	    strcat(string, ""WHITE"Aksesoris\n");
	}
	else strcat(string, ""WHITE"Aksesoris\n");

	if(pToys[playerid][3][toy_model] == 0)
	{
	    strcat(string, ""VERONA_ARWIN"Tas/Koper\n");
	}
	else strcat(string, ""VERONA_ARWIN"Tas/Koper\n");

	ShowPlayerDialog(playerid, DIALOG_TOY, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Edit Fashion", string, "Select", "Cancel");
	return 1;
}
