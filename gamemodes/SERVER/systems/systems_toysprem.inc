//System premium toys
//Credit: ?

//Remake by: Chess7
//Remake Update database

#include <YSI\y_hooks>

// ==== Enum Data Toys ====
enum eToyData 
{
    tModel,
    tBone,
    Float:toys_X, Float:toys_Y, Float:toys_Z,
    Float:toys_RX, Float:toys_RY, Float:toys_RZ,
    Float:toys_SX, Float:toys_SY, Float:toys_SZ
};


// Toy System

#define MAX_TOYSAXP 6
#define TOYS_TYPE_HEAD 1
#define TOYS_TYPE_MASK 2
#define TOYS_TYPE_HAND 3
#define TOYS_TYPE_NECK 4
#define TOYS_TYPE_PUNDAK 5
#define TOYS_TYPE_BACKPACK 6
enum e_toysaxp
{
	toyaxp_model,
	toyaxp_bone,
	toyaxp_status,
    toysaxp_toystype,
	Float:toyaxp_x,
	Float:toyaxp_y,
	Float:toyaxp_z,
	Float:toyaxp_rx,
	Float:toyaxp_ry,
	Float:toyaxp_rz,
	Float:toyaxp_sx,
	Float:toyaxp_sy,
	Float:toyaxp_sz
}
new pToysAxp[MAX_PLAYERS][MAX_TOYSAXP][e_toysaxp];

MySQL_SavePlayerToysAxp(playerid)
{
	new cQuery[2048];
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `toys_axp` SET `Slot0_Model`=%d, `Slot0_ToysType`=%d, `Slot0_Bone`=%d, `Slot0_Status`=%d, `Slot0_XPos`=%f, `Slot0_YPos`=%f, `Slot0_ZPos`=%f, `Slot0_XRot`=%f, `Slot0_YRot`=%f, `Slot0_ZRot`=%f, `Slot0_XScale`=%f, `Slot0_YScale`=%f, `Slot0_ZScale`=%f,\
	`Slot1_Model`=%d, `Slot1_ToysType`=%d, `Slot1_Bone`=%d, `Slot1_Status`=%d, `Slot1_XPos`=%f, `Slot1_YPos`=%f, `Slot1_ZPos`=%f, `Slot1_XRot`=%f, `Slot1_YRot`=%f, `Slot1_ZRot`=%f, `Slot1_XScale`=%f, `Slot1_YScale`=%f, `Slot1_ZScale`=%f,\
	`Slot2_Model`=%d, `Slot2_ToysType`=%d, `Slot2_Bone`=%d, `Slot2_Status`=%d, `Slot2_XPos`=%f, `Slot2_YPos`=%f, `Slot2_ZPos`=%f, `Slot2_XRot`=%f, `Slot2_YRot`=%f, `Slot2_ZRot`=%f, `Slot2_XScale`=%f, `Slot2_YScale`=%f, `Slot2_ZScale`=%f,\
	`Slot3_Model`=%d, `Slot3_ToysType`=%d, `Slot3_Bone`=%d, `Slot3_Status`=%d, `Slot3_XPos`=%f, `Slot3_YPos`=%f, `Slot3_ZPos`=%f, `Slot3_XRot`=%f, `Slot3_YRot`=%f, `Slot3_ZRot`=%f, `Slot3_XScale`=%f, `Slot3_YScale`=%f, `Slot3_ZScale`=%f,\
    `Slot4_Model`=%d, `Slot4_ToysType`=%d, `Slot4_Bone`=%d, `Slot4_Status`=%d, `Slot4_XPos`=%f, `Slot4_YPos`=%f, `Slot4_ZPos`=%f, `Slot4_XRot`=%f, `Slot4_YRot`=%f, `Slot4_ZRot`=%f, `Slot4_XScale`=%f, `Slot4_YScale`=%f, `Slot4_ZScale`=%f,\
	`Slot5_Model`=%d, `Slot5_ToysType`=%d, `Slot5_Bone`=%d, `Slot5_Status`=%d, `Slot5_XPos`=%f, `Slot5_YPos`=%f, `Slot5_ZPos`=%f, `Slot5_XRot`=%f, `Slot5_YRot`=%f, `Slot5_ZRot`=%f, `Slot5_XScale`=%f, `Slot5_YScale`=%f, `Slot5_ZScale`=%f WHERE `Owner`='%s'",
	pToysAxp[playerid][0][toyaxp_model], pToysAxp[playerid][0][toysaxp_toystype], pToysAxp[playerid][0][toyaxp_bone], pToysAxp[playerid][0][toyaxp_status], pToysAxp[playerid][0][toyaxp_x], pToysAxp[playerid][0][toyaxp_y], pToysAxp[playerid][0][toyaxp_z], pToysAxp[playerid][0][toyaxp_rx], pToysAxp[playerid][0][toyaxp_ry], pToysAxp[playerid][0][toyaxp_rz], pToysAxp[playerid][0][toyaxp_sx], pToysAxp[playerid][0][toyaxp_sy], pToysAxp[playerid][0][toyaxp_sz],
	pToysAxp[playerid][1][toyaxp_model], pToysAxp[playerid][1][toysaxp_toystype], pToysAxp[playerid][1][toyaxp_bone], pToysAxp[playerid][1][toyaxp_status], pToysAxp[playerid][1][toyaxp_x], pToysAxp[playerid][1][toyaxp_y], pToysAxp[playerid][1][toyaxp_z], pToysAxp[playerid][1][toyaxp_rx], pToysAxp[playerid][1][toyaxp_ry], pToysAxp[playerid][1][toyaxp_rz], pToysAxp[playerid][1][toyaxp_sx], pToysAxp[playerid][1][toyaxp_sy], pToysAxp[playerid][1][toyaxp_sz],
	pToysAxp[playerid][2][toyaxp_model], pToysAxp[playerid][2][toysaxp_toystype], pToysAxp[playerid][2][toyaxp_bone], pToysAxp[playerid][2][toyaxp_status], pToysAxp[playerid][2][toyaxp_x], pToysAxp[playerid][2][toyaxp_y], pToysAxp[playerid][2][toyaxp_z], pToysAxp[playerid][2][toyaxp_rx], pToysAxp[playerid][2][toyaxp_ry], pToysAxp[playerid][2][toyaxp_rz], pToysAxp[playerid][2][toyaxp_sx], pToysAxp[playerid][2][toyaxp_sy], pToysAxp[playerid][2][toyaxp_sz],
	pToysAxp[playerid][3][toyaxp_model], pToysAxp[playerid][3][toysaxp_toystype], pToysAxp[playerid][3][toyaxp_bone], pToysAxp[playerid][3][toyaxp_status], pToysAxp[playerid][3][toyaxp_x], pToysAxp[playerid][3][toyaxp_y], pToysAxp[playerid][3][toyaxp_z], pToysAxp[playerid][3][toyaxp_rx], pToysAxp[playerid][3][toyaxp_ry], pToysAxp[playerid][3][toyaxp_rz], pToysAxp[playerid][3][toyaxp_sx], pToysAxp[playerid][3][toyaxp_sy], pToysAxp[playerid][3][toyaxp_sz],
    pToysAxp[playerid][4][toyaxp_model], pToysAxp[playerid][4][toysaxp_toystype], pToysAxp[playerid][4][toyaxp_bone], pToysAxp[playerid][4][toyaxp_status], pToysAxp[playerid][4][toyaxp_x], pToysAxp[playerid][4][toyaxp_y], pToysAxp[playerid][4][toyaxp_z], pToysAxp[playerid][4][toyaxp_rx], pToysAxp[playerid][4][toyaxp_ry], pToysAxp[playerid][4][toyaxp_rz], pToysAxp[playerid][4][toyaxp_sx], pToysAxp[playerid][4][toyaxp_sy], pToysAxp[playerid][4][toyaxp_sz],
	pToysAxp[playerid][5][toyaxp_model], pToysAxp[playerid][5][toysaxp_toystype], pToysAxp[playerid][5][toyaxp_bone], pToysAxp[playerid][5][toyaxp_status], pToysAxp[playerid][5][toyaxp_x], pToysAxp[playerid][5][toyaxp_y], pToysAxp[playerid][5][toyaxp_z], pToysAxp[playerid][5][toyaxp_rx], pToysAxp[playerid][5][toyaxp_ry], pToysAxp[playerid][5][toyaxp_rz], pToysAxp[playerid][5][toyaxp_sx], pToysAxp[playerid][5][toyaxp_sy], pToysAxp[playerid][5][toyaxp_sz], AccountData[playerid][pName]);
	mysql_tquery(g_SQL, cQuery);
    AccountData[playerid][PurchasedToyAxp] = true;
	return 1;
}

forward LoadPlayerToysAxp(playerid);
public LoadPlayerToysAxp(playerid)
{
	new rows = cache_num_rows();
	if(rows)
	{
		AccountData[playerid][PurchasedToyAxp] = true;
		cache_get_value_name_int(0, "Slot0_Model", pToysAxp[playerid][0][toyaxp_model]);
        cache_get_value_name_int(0, "Slot0_ToysType", pToysAxp[playerid][0][toysaxp_toystype]);
  		cache_get_value_name_int(0, "Slot0_Bone", pToysAxp[playerid][0][toyaxp_bone]);
		cache_get_value_name_int(0, "Slot0_Status", pToysAxp[playerid][0][toyaxp_status]);
  		cache_get_value_name_float(0, "Slot0_XPos", pToysAxp[playerid][0][toyaxp_x]);
  		cache_get_value_name_float(0, "Slot0_YPos", pToysAxp[playerid][0][toyaxp_y]);
  		cache_get_value_name_float(0, "Slot0_ZPos", pToysAxp[playerid][0][toyaxp_z]);
  		cache_get_value_name_float(0, "Slot0_XRot", pToysAxp[playerid][0][toyaxp_rx]);
  		cache_get_value_name_float(0, "Slot0_YRot", pToysAxp[playerid][0][toyaxp_ry]);
  		cache_get_value_name_float(0, "Slot0_ZRot", pToysAxp[playerid][0][toyaxp_rz]);
  		cache_get_value_name_float(0, "Slot0_XScale", pToysAxp[playerid][0][toyaxp_sx]);
  		cache_get_value_name_float(0, "Slot0_YScale", pToysAxp[playerid][0][toyaxp_sy]);
		cache_get_value_name_float(0, "Slot0_ZScale", pToysAxp[playerid][0][toyaxp_sz]);
		
		cache_get_value_name_int(0, "Slot1_Model", pToysAxp[playerid][1][toyaxp_model]);
        cache_get_value_name_int(0, "Slot1_ToysType", pToysAxp[playerid][1][toysaxp_toystype]);
  		cache_get_value_name_int(0, "Slot1_Bone", pToysAxp[playerid][1][toyaxp_bone]);
		cache_get_value_name_int(0, "Slot1_Status", pToysAxp[playerid][1][toyaxp_status]);
  		cache_get_value_name_float(0, "Slot1_XPos", pToysAxp[playerid][1][toyaxp_x]);
  		cache_get_value_name_float(0, "Slot1_YPos", pToysAxp[playerid][1][toyaxp_y]);
  		cache_get_value_name_float(0, "Slot1_ZPos", pToysAxp[playerid][1][toyaxp_z]);
  		cache_get_value_name_float(0, "Slot1_XRot", pToysAxp[playerid][1][toyaxp_rx]);
  		cache_get_value_name_float(0, "Slot1_YRot", pToysAxp[playerid][1][toyaxp_ry]);
  		cache_get_value_name_float(0, "Slot1_ZRot", pToysAxp[playerid][1][toyaxp_rz]);
  		cache_get_value_name_float(0, "Slot1_XScale", pToysAxp[playerid][1][toyaxp_sx]);
  		cache_get_value_name_float(0, "Slot1_YScale", pToysAxp[playerid][1][toyaxp_sy]);
		cache_get_value_name_float(0, "Slot1_ZScale", pToysAxp[playerid][1][toyaxp_sz]);
		
		cache_get_value_name_int(0, "Slot2_Model", pToysAxp[playerid][2][toyaxp_model]);
        cache_get_value_name_int(0, "Slot2_ToysType", pToysAxp[playerid][2][toysaxp_toystype]);
  		cache_get_value_name_int(0, "Slot2_Bone", pToysAxp[playerid][2][toyaxp_bone]);
		cache_get_value_name_int(0, "Slot2_Status", pToysAxp[playerid][2][toyaxp_status]);
  		cache_get_value_name_float(0, "Slot2_XPos", pToysAxp[playerid][2][toyaxp_x]);
  		cache_get_value_name_float(0, "Slot2_YPos", pToysAxp[playerid][2][toyaxp_y]);
  		cache_get_value_name_float(0, "Slot2_ZPos", pToysAxp[playerid][2][toyaxp_z]);
  		cache_get_value_name_float(0, "Slot2_XRot", pToysAxp[playerid][2][toyaxp_rx]);
  		cache_get_value_name_float(0, "Slot2_YRot", pToysAxp[playerid][2][toyaxp_ry]);
  		cache_get_value_name_float(0, "Slot2_ZRot", pToysAxp[playerid][2][toyaxp_rz]);
  		cache_get_value_name_float(0, "Slot2_XScale", pToysAxp[playerid][2][toyaxp_sx]);
  		cache_get_value_name_float(0, "Slot2_YScale", pToysAxp[playerid][2][toyaxp_sy]);
		cache_get_value_name_float(0, "Slot2_ZScale", pToysAxp[playerid][2][toyaxp_sz]);
		
		cache_get_value_name_int(0, "Slot3_Model", pToysAxp[playerid][3][toyaxp_model]);
        cache_get_value_name_int(0, "Slot3_ToysType", pToysAxp[playerid][3][toysaxp_toystype]);
  		cache_get_value_name_int(0, "Slot3_Bone", pToysAxp[playerid][3][toyaxp_bone]);
		cache_get_value_name_int(0, "Slot3_Status", pToysAxp[playerid][3][toyaxp_status]);
  		cache_get_value_name_float(0, "Slot3_XPos", pToysAxp[playerid][3][toyaxp_x]);
  		cache_get_value_name_float(0, "Slot3_YPos", pToysAxp[playerid][3][toyaxp_y]);
  		cache_get_value_name_float(0, "Slot3_ZPos", pToysAxp[playerid][3][toyaxp_z]);
  		cache_get_value_name_float(0, "Slot3_XRot", pToysAxp[playerid][3][toyaxp_rx]);
  		cache_get_value_name_float(0, "Slot3_YRot", pToysAxp[playerid][3][toyaxp_ry]);
  		cache_get_value_name_float(0, "Slot3_ZRot", pToysAxp[playerid][3][toyaxp_rz]);
  		cache_get_value_name_float(0, "Slot3_XScale", pToysAxp[playerid][3][toyaxp_sx]);
  		cache_get_value_name_float(0, "Slot3_YScale", pToysAxp[playerid][3][toyaxp_sy]);
		cache_get_value_name_float(0, "Slot3_ZScale", pToysAxp[playerid][3][toyaxp_sz]);

        cache_get_value_name_int(0, "Slot4_Model", pToysAxp[playerid][4][toyaxp_model]);
        cache_get_value_name_int(0, "Slot4_ToysType", pToysAxp[playerid][4][toysaxp_toystype]);
  		cache_get_value_name_int(0, "Slot4_Bone", pToysAxp[playerid][4][toyaxp_bone]);
		cache_get_value_name_int(0, "Slot4_Status", pToysAxp[playerid][4][toyaxp_status]);
  		cache_get_value_name_float(0, "Slot4_XPos", pToysAxp[playerid][4][toyaxp_x]);
  		cache_get_value_name_float(0, "Slot4_YPos", pToysAxp[playerid][4][toyaxp_y]);
  		cache_get_value_name_float(0, "Slot4_ZPos", pToysAxp[playerid][4][toyaxp_z]);
  		cache_get_value_name_float(0, "Slot4_XRot", pToysAxp[playerid][4][toyaxp_rx]);
  		cache_get_value_name_float(0, "Slot4_YRot", pToysAxp[playerid][4][toyaxp_ry]);
  		cache_get_value_name_float(0, "Slot4_ZRot", pToysAxp[playerid][4][toyaxp_rz]);
  		cache_get_value_name_float(0, "Slot4_XScale", pToysAxp[playerid][4][toyaxp_sx]);
  		cache_get_value_name_float(0, "Slot4_YScale", pToysAxp[playerid][4][toyaxp_sy]);
		cache_get_value_name_float(0, "Slot4_ZScale", pToysAxp[playerid][4][toyaxp_sz]);

        cache_get_value_name_int(0, "Slot5_Model", pToysAxp[playerid][5][toyaxp_model]);
        cache_get_value_name_int(0, "Slot5_ToysType", pToysAxp[playerid][5][toysaxp_toystype]);
  		cache_get_value_name_int(0, "Slot5_Bone", pToysAxp[playerid][5][toyaxp_bone]);
		cache_get_value_name_int(0, "Slot5_Status", pToysAxp[playerid][5][toyaxp_status]);
  		cache_get_value_name_float(0, "Slot5_XPos", pToysAxp[playerid][5][toyaxp_x]);
  		cache_get_value_name_float(0, "Slot5_YPos", pToysAxp[playerid][5][toyaxp_y]);
  		cache_get_value_name_float(0, "Slot5_ZPos", pToysAxp[playerid][5][toyaxp_z]);
  		cache_get_value_name_float(0, "Slot5_XRot", pToysAxp[playerid][5][toyaxp_rx]);
  		cache_get_value_name_float(0, "Slot5_YRot", pToysAxp[playerid][5][toyaxp_ry]);
  		cache_get_value_name_float(0, "Slot5_ZRot", pToysAxp[playerid][5][toyaxp_rz]);
  		cache_get_value_name_float(0, "Slot5_XScale", pToysAxp[playerid][5][toyaxp_sx]);
  		cache_get_value_name_float(0, "Slot5_YScale", pToysAxp[playerid][5][toyaxp_sy]);
		cache_get_value_name_float(0, "Slot5_ZScale", pToysAxp[playerid][5][toyaxp_sz]);

		AttachPlayerToysaxp(playerid); // Attach player Toys.
		printf("[Player Toys Axp] Memuat player Toys axp untuk: %s(%d)", AccountData[playerid][pName], playerid);
	}
	return 1;
}
 
AttachPlayerToysaxp(playerid)
{	
	if(AccountData[playerid][PurchasedToyAxp] == false) return 1;

	if(pToysAxp[playerid][0][toyaxp_model] != 0)
	{
		if(pToysAxp[playerid][0][toyaxp_status] != 0)
		{
			SetPlayerAttachedObject(playerid,
			0,
			pToysAxp[playerid][0][toyaxp_model],
			pToysAxp[playerid][0][toyaxp_bone],
			pToysAxp[playerid][0][toyaxp_x],
			pToysAxp[playerid][0][toyaxp_y],
			pToysAxp[playerid][0][toyaxp_z],
			pToysAxp[playerid][0][toyaxp_rx],
			pToysAxp[playerid][0][toyaxp_ry],
			pToysAxp[playerid][0][toyaxp_rz],
			pToysAxp[playerid][0][toyaxp_sx],
			pToysAxp[playerid][0][toyaxp_sy],
			pToysAxp[playerid][0][toyaxp_sz]);
		}
	}
	
	if(pToysAxp[playerid][1][toyaxp_model] != 0)
	{
		if(pToysAxp[playerid][1][toyaxp_status] != 0)
		{
			SetPlayerAttachedObject(playerid,
			1,
			pToysAxp[playerid][1][toyaxp_model],
			pToysAxp[playerid][1][toyaxp_bone],
			pToysAxp[playerid][1][toyaxp_x],
			pToysAxp[playerid][1][toyaxp_y],
			pToysAxp[playerid][1][toyaxp_z],
			pToysAxp[playerid][1][toyaxp_rx],
			pToysAxp[playerid][1][toyaxp_ry],
			pToysAxp[playerid][1][toyaxp_rz],
			pToysAxp[playerid][1][toyaxp_sx],
			pToysAxp[playerid][1][toyaxp_sy],
			pToysAxp[playerid][1][toyaxp_sz]);
		}
	}
	
	if(pToysAxp[playerid][2][toyaxp_model] != 0)
	{
		if(pToysAxp[playerid][2][toyaxp_status] != 0)
		{
			SetPlayerAttachedObject(playerid,
			2,
			pToysAxp[playerid][2][toyaxp_model],
			pToysAxp[playerid][2][toyaxp_bone],
			pToysAxp[playerid][2][toyaxp_x],
			pToysAxp[playerid][2][toyaxp_y],
			pToysAxp[playerid][2][toyaxp_z],
			pToysAxp[playerid][2][toyaxp_rx],
			pToysAxp[playerid][2][toyaxp_ry],
			pToysAxp[playerid][2][toyaxp_rz],
			pToysAxp[playerid][2][toyaxp_sx],
			pToysAxp[playerid][2][toyaxp_sy],
			pToysAxp[playerid][2][toyaxp_sz]);
		}
	}
	
	if(pToysAxp[playerid][3][toyaxp_model] != 0)
	{
		if(pToysAxp[playerid][3][toyaxp_status] != 0)
		{
			SetPlayerAttachedObject(playerid,
			3,
			pToysAxp[playerid][3][toyaxp_model],
			pToysAxp[playerid][3][toyaxp_bone],
			pToysAxp[playerid][3][toyaxp_x],
			pToysAxp[playerid][3][toyaxp_y],
			pToysAxp[playerid][3][toyaxp_z],
			pToysAxp[playerid][3][toyaxp_rx],
			pToysAxp[playerid][3][toyaxp_ry],
			pToysAxp[playerid][3][toyaxp_rz],
			pToysAxp[playerid][3][toyaxp_sx],
			pToysAxp[playerid][3][toyaxp_sy],
			pToysAxp[playerid][3][toyaxp_sz]);
		}
	}
    if(pToysAxp[playerid][4][toyaxp_model] != 0)
	{
		if(pToysAxp[playerid][4][toyaxp_status] != 0)
		{
			SetPlayerAttachedObject(playerid,
			4,
			pToysAxp[playerid][4][toyaxp_model],
			pToysAxp[playerid][4][toyaxp_bone],
			pToysAxp[playerid][4][toyaxp_x],
			pToysAxp[playerid][4][toyaxp_y],
			pToysAxp[playerid][4][toyaxp_z],
			pToysAxp[playerid][4][toyaxp_rx],
			pToysAxp[playerid][4][toyaxp_ry],
			pToysAxp[playerid][4][toyaxp_rz],
			pToysAxp[playerid][4][toyaxp_sx],
			pToysAxp[playerid][4][toyaxp_sy],
			pToysAxp[playerid][4][toyaxp_sz]);
		}
	}
    if(pToysAxp[playerid][5][toyaxp_model] != 0)
	{
		if(pToysAxp[playerid][5][toyaxp_status] != 0)
		{
			SetPlayerAttachedObject(playerid,
			5,
			pToysAxp[playerid][5][toyaxp_model],
			pToysAxp[playerid][5][toyaxp_bone],
			pToysAxp[playerid][5][toyaxp_x],
			pToysAxp[playerid][5][toyaxp_y],
			pToysAxp[playerid][5][toyaxp_z],
			pToysAxp[playerid][5][toyaxp_rx],
			pToysAxp[playerid][5][toyaxp_ry],
			pToysAxp[playerid][5][toyaxp_rz],
			pToysAxp[playerid][5][toyaxp_sx],
			pToysAxp[playerid][5][toyaxp_sy],
			pToysAxp[playerid][5][toyaxp_sz]);
		}
	}
	
	return 1;
}
// ==== Settings Toys ====
new HeadToys[][eToyData] = 
{
    {19197, 2, 0.20999899506569, 0.0, 0.0, 0.0, 84.499977111816, 0.0, 0.26599898934364, 0.27300000190735, 0.0},
    {19487, 2, 0.08500000089407, 0.0059989998117089, -0.0039989999495447, 83.900001525879, 67.899978637695, 3.1999990940094, 1.078999042511, 0.96200001239777, 1.0},
    {19352, 2, 0.10999900102615, -0.003000000026077, 0.0, -78.300010681152, 113.10001373291, -13.799969673157, 1.1149990558624, 1.097000002861, 1.0},
    {19094, 2, 0.13699799776077, -0.00099900003988296, -0.0029990000184625, 0.0, 0.0, 0.0, 0.82999902963638, 0.82300001382828, 0.79399901628494},
    {18952, 2, 0.088999003171921, 0.018999999389052, -0.0020000000949949, 0.0, 0.0, -6.2999992370605, 1.2780009508133, 1.1880029439926, 1.2549999952316},
    {19553, 2, 0.15399999916553, -0.018998999148607, 0.0060000000521541, -5.4999980926514, -7.7999949455261, -32.600002288818, 1.1309989690781, 1.4560010433197, 1.2710009813309},
    {19528, 2, 0.1089999973774, -0.0019990000873804, -0.0020000000949949, 0.0, 0.0, -29.199979782104, 1.0, 1.5060019493103, 1.0719989538193},
    {18638, 2, 0.16400299966335, 0.016999000683427, -0.00099900003988296, 0.0, 0.0, -8.399974822998, 0.69499897956848, 0.9279950261116, 1.002995967865},
    {18979, 2, 0.072999000549316, 0.013000000268221, 0.0, 88.600006103516, 91.099998474121, 0.0, 1.1290010213852, 0.97299897670746, 1.0499999523163},
    {18977, 2, 0.072999000549316, 0.013000000268221, 0.0, 88.600006103516, 91.099998474121, 0.0, 1.1290010213852, 0.97299897670746, 1.0499999523163},
    {18978, 2, 0.072999000549316, 0.013000000268221, 0.0, 88.600006103516, 91.099998474121, 0.0, 1.1290010213852, 0.97299897670746, 1.0499999523163},
    {18645, 2, 0.072999000549316, 0.013000000268221, 0.0, 88.600006103516, 91.099998474121, 0.0, 1.1290010213852, 0.97299897670746, 1.0499999523163},
    {19064, 2, 0.12899999320507, 0.0089990003034472, -0.00099900003988296, 3.4000000953674, 87.10001373291, 88.299980163574, 1.1169979572296, 1.3200010061264, 1.0440000295639},
    {19137, 2, 0.10299900174141, 0.013999000191689, 0.0029990000184625, 0.0, 0.0, 0.0, 1.0, 1.027999997139, 1.1619989871979},
    {19520, 2, 0.12200099974871, -0.015999000519514, 0.0040000001899898, -2.0, 0.29999798536301, -7.5999941825867, 0.8489990234375, 1.220999956131, 1.2530039548874},
    {19320, 2, 0.15699900686741, -0.0040000001899898, 0.0, 0.0, 89.799995422363, 0.0, 0.65600001811981, 0.6339989900589, 0.7239990234375},
    {19099, 2, 0.17599999904633, -0.0060000000521541, -0.0029990000184625, 0.0, 0.0, -11.100002288818, 1.0509999990463, 1.1280020475388, 1.1110010147095},
    {1736, 2, 0.057900000363588, -0.018899999558926, -0.0168999992311, 83.799896240234, 18.699899673462, 95.699996948242, 0.97289997339249, 0.87300002574921, 0.61690002679825},
    {6865, 2, 0.0019990000873804, 0.035000000149012, 0.0, -124.29997253418, 105.30003356934, -7.6000080108643, 0.13899900019169, 0.15500000119209, 0.1169999986887},
    {2908, 2, 0.090998999774456, 0.06699900329113, -0.0040000001899898, 178.90003967285, 0.0, 99.700012207031, 1.7029980421066, 1.4359990358353, 1.7010010480881},
    {18636, 2, 0.1410010010004, 0.043999999761581, -0.0049990001134574, 1.5999989509583, 92.800109863281, 82.199951171875, 1.0399980545044, 1.0860049724579, 0.83699798583984},
    {19346, 2, 0.16700500249863, -0.010999999940395, -0.0059989998117089, 95.699905395508, 68.800086975098, -104.89994049072, 2.339998960495, 0.96499902009964, 1.6360000371933},
    {1603, 2, 0.19100299477577, 0.021999999880791, 0.014999000355601, -4.3999991416931, 83.999992370605, 2.299998998642, 0.38400000333786, 0.50099802017212, 0.35999900102615},
    {18782, 2, 0.16700099408627, -0.01799900084734, 0.0019990000873804, -91.000045776367, 116.79998016357, 163.00001525879, 0.020998999476433, 0.01799900084734, 0.054997999221087},
    {19558, 2, 0.14499899744987, -0.0020000000949949, 0.00099900003988296, 0.0, 0.0, -30.400007247925, 1.0, 1.0230000019073, 1.0120010375977},
    {2238, 2, 0.46000000834465, -0.1330000013113, 0.051899999380112, 65.400001525879, 67.099998474121, 21.39999961853, 1.1790000200272, 1.2158999443054, 0.85189998149872},
    {18925, 2, 0.13899800181389, 0.012000000104308, -0.0070009999908507, 0.19999800622463, -5.7000150680542, -8.8000183105469, 1.0740000009537, 1.0269989967346, 1.125},
    {18950, 2, 0.15199799835682, 0.012000000104308, 0.0019990000873804, 0.0, 0.6000030040741, -6.3999819755554, 1.0, 0.99099898338318, 1.0490000247955},
    {19514, 2, 0.0979989990592, -0.0010000000474975, -0.00099900003988296, 0.0, 0.0, -3.4000000953674, 1.1440000534058, 1.0210000276566, 1.08800303936}
};

new MaskToys[][eToyData] = 
{
    {18963, 2, 0.10299900174141, 0.013999000191689, -0.0019990000873804, 87.299995422363, 81.200103759766, 0.0, 1.1790020465851, 1.1350150108337, 1.1570030450821},
    {11704, 2, 0.086000002920628, 0.1140009984374, -0.0060000000521541, 90.200019836426, 83.900115966797, 87.0, 0.28599798679352, 0.41400000452995, 0.37799799442291},
    {19472, 2, -0.0070009999908507, 0.12899899482727, -0.00099900003988296, -2.9000000953674, 88.200019836426, 93.200096130371, 1.0439889431, 1.2140029668808, 1.0960010290146},
    {368, 2, 0.0, 0.10099899768829, -0.0039989999495447, 0.0, 0.0, -1.0999970436096, 1.0, 1.0, 0.98099899291992},
    {11736, 2, -0.017000000923872, 0.064000003039837, -0.0019990000873804, 0.0, 0.0, 11.199993133545, 0.26100000739098, 0.44699901342392, 2.6970009803772},
    {19517, 2, -0.010999999940395, 0.064000003039837, 0.0, 0.0, 0.0, -162.10018920898, 0.33300000429153, 0.60399901866913, 0.57099902629852},
    {1013, 2, 0.16490000486374, 0.0070000002160668, 0.0, 92.499900817871, 178.30000305176, -92.799896240234, 0.10490000247955, 0.78990000486374, 0.22800000011921},
    {19314, 2, 0.086998999118805, 0.0010000000474975, -0.0019990000873804, 0.0, 0.0, -83.199989318848, 0.70799899101257, 0.60199999809265, 0.31999999284744},
    {19351, 2, 0.025999000295997, 0.12199900299311, -0.00099900003988296, 0.0, 0.0, -79.300033569336, 1.0, 1.0, 1.0},
    {19036, 2, 0.11299999803305, 0.026000000536442, -0.0069989999756217, -1.5999979972839, 91.100051879883, 92.199989318848, 1.1469999551773, 1.3199989795685, 1.1560000181198},
    {13667, 2, 0.090899996459484, 0.14990000426769, -0.0038999998942018, 82.099998474121, 78.299896240234, 18.699899673462, 0.051899999380112, 0.025900000706315, 0.025900000706315}
};

new HandToys[][eToyData] = 
{
    {364, 6, 0.078998997807503, 0.018999999389052, 0.0089990003034472, 0.0, -93.299949645996, 5.0000028610229, 1.0, 1.0, 1.0},
    {1366, 14, 0.046900000423193, 0.016000000759959, -0.039900001138449, 17.200000762939, 175.99969482422, 114.30000305176, 2.7000000476837, 1.3128999471664, 0.038899999111891},
    {1877, 14, 0.31290000677109, -0.58490002155304, -0.12890000641346, 105.40000152588, 0.0, 0.0, 0.086900003254414, 0.103900000453, 1.779000043869},
    {1882, 14, 0.31290000677109, -0.58490002155304, -0.12890000641346, 105.40000152588, 0.0, 0.0, 0.086900003254414, 0.103900000453, 1.779000043869},
    {1878, 14, 0.31290000677109, -0.58490002155304, -0.12890000641346, 105.40000152588, 0.0, 0.0, 0.086900003254414, 0.103900000453, 1.779000043869},
    {1880, 14, 0.31290000677109, -0.58490002155304, -0.12890000641346, 105.40000152588, 0.0, 0.0, 0.086900003254414, 0.103900000453, 1.779000043869},
    {1879, 14, 0.31290000677109, -0.58490002155304, -0.12890000641346, 105.40000152588, 0.0, 0.0, 0.086900003254414, 0.103900000453, 1.779000043869},
    {1881, 14, 0.31290000677109, -0.58490002155304, -0.12890000641346, 105.40000152588, 0.0, 0.0, 0.086900003254414, 0.103900000453, 1.779000043869},
    {3801, 13, 0.67589998245239, -0.80400002002716, 0.071900002658367, -90.199897766113, 65.899803161621, -5.7999000549316, 5.476900100708, 0.24590000510216, 0.44290000200272},
    {2805, 13, 0.62300002574921, 0.020899999886751, 0.0, -2.5999000072479, -93.999900817871, 109.69989776611, 1.0808999538422, 0.69489997625351, 0.36800000071526},
    {2901, 1, 0.10999999940395, 0.36000001430511, 0.0, 0.0, 90.0, 0.0, 1.0, 1.0, 1.0}
};

new NeckToys[][eToyData] = 
{
    {1274, 1, 0.12700000405312, 0.13500000536442, -0.0019990000873804, -88.600067138672, 106.29999542236, -95.799903869629, 0.23600000143051, 1.5169999599457, 0.21400000154972},
    {1240, 1, 0.12290000170469, 0.15289999544621, -0.0040000001899898, 87.299896240234, 78.199897766113, -89.599899291992, 0.6370000243187, 0.86890000104904, 0.61000001430511},
    {1240, 1, 0.23999899625778, 0.10000000149012, 0.0049990001134574, -87.300003051758, 121.90032958984, -90.299980163574, 0.3209989964962, 0.60100001096725, 0.2790000140667},
    {19623, 1, 0.20100000500679, 0.17199899256229, -0.0089990003034472, 79.79997253418, 60.200038909912, 97.800003051758, 0.61599898338318, 0.71599900722504, 0.59200000762939},
    {11712, 1, 0.2660000026226, 0.125, -0.0059989998117089, 87.900009155273, 60.300243377686, 0.0, 1.4189989566803, 0.56699997186661, 0.47299998998642},
    {19621, 1, -0.093000002205372, 0.086998999118805, -0.19699999690056, 0.0, 69.999984741211, -145.90000915527, 0.658999979496, 0.7239990234375, 0.81299901008606},
    {19130, 1, 0.13600000739098, 0.13500000536442, -0.0168999992311, 79.199897766113, 66.299797058105, 6.9998998641968, 0.82889997959137, 0.49790000915527, 0.13600000739098}
};

new PundakToys[][eToyData] = 
{
    {19079, 1, 0.29200100898743, -0.054999001324177, 0.12799899280071, 0.0, -20.699991226196, 0.12, 0.53399902582169, 0.64999997615814, 0.64700001478195},
    {16776, 1, 0.30399999022484, -0.012999000027776, 0.14299899339676, 3.8000090122223, 79.100120544434, -179.59983825684, 0.0070000002160668, 0.0060000000521541, 0.0099980002269149},
    {16778, 1, 0.13189999759197, 0.0020000000949949, 0.11200000345707, 0.0, 70.699996948242, 98.099899291992, 0.041000001132488, 0.037000000476837, 0.040899999439716},
    {19332, 1, 0.35399898886681, -0.017000000923872, 0.18599900603294, 0.0, 86.599998474121, 0.0, 0.0089999996125698, 0.0089990003034472, 0.0089990003034472},
    {19333, 1, 0.35399898886681, -0.017000000923872, 0.18599900603294, 0.0, 86.599998474121, 0.0, 0.0089999996125698, 0.0089990003034472, 0.0089990003034472},
    {19334, 1, 0.35399898886681, -0.017000000923872, 0.18599900603294, 0.0, 86.599998474121, 0.0, 0.0089999996125698, 0.0089990003034472, 0.0089990003034472},
    {19335, 1, 0.35399898886681, -0.017000000923872, 0.18599900603294, 0.0, 86.599998474121, 0.0, 0.0089999996125698, 0.0089990003034472, 0.0089990003034472},
    {19336, 1, 0.35399898886681, -0.017000000923872, 0.18599900603294, 0.0, 86.599998474121, 0.0, 0.0089999996125698, 0.0089990003034472, 0.0089990003034472},
    {19337, 1, 0.35399898886681, -0.017000000923872, 0.18599900603294, 0.0, 86.599998474121, 0.0, 0.0089999996125698, 0.0089990003034472, 0.0089990003034472},
    {19338, 1, 0.35399898886681, -0.017000000923872, 0.18599900603294, 0.0, 86.599998474121, 0.0, 0.0089999996125698, 0.0089990003034472, 0.0089990003034472},
    {19315, 1, 0.21189999580383, 0.10000000149012, -0.1630000025034, 87.699897766113, 80.999900817871, 1.8998999595642, 1.0, 1.0, 1.0},
    {14467, 1, 0.45590001344681, 0.018899999558926, 0.17689999938011, 0.0, 85.39990234375, -178.0, 0.090899996459484, 0.10400000214577, 0.082900002598763},
    {19076, 16, 0.17790000140667, -0.014899999834597, 0.0, 2.7999000549316, -176.89990234375, 0.0, 0.046000000089407, 0.050000000745058, 0.041000001132488},
    {19076, 1, 0.30500799417496, -0.012000000104308, 0.15699900686741, 0.0, 88.400009155273, 0.0, 0.019999999552965, 0.025999000295997, 0.018999999389052}
};

new BackpToys[][eToyData] = 
{
    {337, 1, -0.061999000608921, -0.179000005126, -0.082000002264977, -1.2000000476837, 59.700004577637, 97.69994354248, 1.0, 1.0, 1.0},
    {1212, 1, 0.12599900364876, -0.077999003231525, -0.0049999998882413, 90.499923706055, 0.0, -23.599962234497, 2.0409979820251, 2.689001083374, 1.4119999408722},
    {1575, 1, 0.061997998505831, -0.030999999493361, 0.002998000010848, 89.900100708008, 0.0, 0.0, 0.73000001907349, 0.73999798297882, 0.95300000905991},
    {19636, 1, -0.093998000025749, -0.20499999821186, 0.0049999998882413, -0.30000001192093, 89.300079345703, -1.299998998642, 0.46299800276756, 0.20299799740314, 2.5520000457764},
    {2805, 1, 0.12799899280071, -0.1799979954958, 0.0089990003034472, 0.0, 74.400016784668, 0.0, 0.59399998188019, 0.63599902391434, 0.42799898982048},
    {19840, 1, -0.40090000629425, -0.25490000844002, 0.025000000372529, 94.699897766113, 59.499900817871, -96.999900817871, 0.054900001734495, 0.072899997234344, 0.12389999628067},
    {18637, 1, 0.077999003231525, -0.034999001771212, 0.12099999934435, 87.19994354248, -0.9, -73.0, 0.71499997377396, 0.78600001335144, 1.0479990243912},
    {339, 1, 0.30299898982048, -0.12000100314617, -0.21399900317192, 0.19999699294567, -53.899978637695, -5.4999890327454, 1.0, 1.0, 0.79699999094009},
    {19590, 1, 0.29499799013138, -0.11, 0.14299799501896, -1.0999330282211, 147.3000793457, 89.601707458496, 0.96199697256088, 0.95099902153015, 0.7239990234375},
    {362, 1, 0.52799898386002, -0.18199899792671, -0.0049990001134574, 176.59999084473, -178.39958190918, 0.0, 0.65299999713898, 0.77699899673462, 0.82700002193451},
    {361, 1, 0.54399901628494, -0.15599900484085, -0.10300000011921, -177.3000793457, 176.40005493164, 0.0, 0.76800000667572, 0.7059999704361, 0.74899899959564},
    {341, 1, 0.47899800539017, -0.15499299764633, 0.13199900090694, 0.0, 174.4002532959, 0.0, 1.0, 1.0, 1.0},
    {19620, 1, 0.0, -0.11089999973774, 0.0059000002220273, 86.900001525879, 5.1999998092651, -33.700000762939, 1.8008999824524, 0.11100000143051, 0.20990000665188},
    {19806, 1, -0.33889999985695, -0.13889999687672, -0.046000000089407, -162.89999389648, -88.099899291992, -81.199897766113, 0.50900000333786, 2.1559000015259, 1.335000038147},
    {1603, 1, 0.3619000017643, -0.0080000003799796, 0.0, 0.0, 91.39990234375, 0.0, 1.2740000486374, 0.66689997911453, 1.0},
    {1609, 1, 0.12099900096655, -0.15099799633026, 0.0049990001134574, 90.900001525879, -1.1000020503998, -86.100006103516, 0.19799999892712, 0.19499999284744, 0.19300000369549},
    {7392, 1, 0.028899999335408, -0.12690000236034, -0.036899998784065, -92.299896240234, 95.599899291992, 0.0, 0.062899999320507, 0.047899998724461, 0.041900001466274},
    {19874, 1, 0.032000001519918, -0.079899996519089, -0.014000000432134, 84.39990234375, 5.0998997688293, 0.0, 3.4618999958038, 3.0659000873566, 4.6719999313354},
    {326, 1, 0.32299900054932, -0.13600200414658, -0.34299901127815, -9.1000032424927, -45.499980926514, 0.0, 1.0, 1.0, 1.0},
    {1228, 1, 0.0, -0.11490000039339, 0.014000000432134, 2.2000000476837, 33.599998474121, -89.199897766113, 1.0, 1.4428999423981, 0.22390000522137},
    {19317, 1, 0.17599999904633, -0.10800000280142, -0.052999000996351, 4.1999940872192, 119.29999542236, -4.7000007629395, 0.68800002336502, 1.0, 0.69599997997284},
    {19318, 1, 0.17599999904633, -0.10800000280142, -0.052999000996351, 4.1999940872192, 119.29999542236, -4.7000007629395, 0.68800002336502, 1.0, 0.69599997997284},
    {19319, 1, 0.15000000596046, -0.1169990003109, -0.014999000355601, 4.1999940872192, 119.29999542236, -4.7000007629395, 0.68800002336502, 1.0, 0.69599997997284},
    {336, 1, -0.12599900364876, -0.14299799501896, -0.13099899888039, 0.0, 47.100002288818, 0.0, 1.0, 1.0, 1.0},
    {19057, 1, 0.10999999940395, -0.18699899315834, 0.0, 0.0, 85.89998626709, 0.0, 0.23999999463558, 0.18099999427795, 0.39899900555611},
    {8492, 1, 0.054999001324177, -0.11100000143051, -0.0019990000873804, -91.699813842773, -96.099952697754, -109.60003662109, 0.057000000029802, 0.034000001847744, 0.090000003576279},
    {1177, 1, -0.10989999771118, -0.15500000119209, 0.4239000082016, -89.800003051758, -0.799899995327, 88.300003051758, 0.46889999508858, 1.8400000333786, 0.30790001153946},
    {322, 1, -0.0089999996125698, -0.18399800360203,  0.082999996840954, 0.0, 69.499992370605, 0.0, 1.6199990510941, 1.6379990577698, 2.549998998642},
    {2226, 1, 0.080999001860619, -0.2039940059185, -0.062999002635479, 0.0, 34.5, 0.0, 0.67599999904633, 0.783999979496, 0.7599989771843},
    {19878, 1, 0.10499999672174, -0.15600000321865, -0.010999999940395, -90.699935913086, -6.0000061988831, 158.2999420166, 0.68699997663498, 0.69799900054932, 1.0},
    {2404, 1, 0.050999000668526, -0.10700000077486, -0.040998999029398, 3.0, 56.20002746582, -6.899995803833, 0.56399899721146, 0.88999897241592, 0.46999898552895},
    {2405, 1, 0.050999000668526, -0.10700000077486, -0.040998999029398, 3.0, 56.20002746582, -6.899995803833, 0.56399899721146, 0.88999897241592, 0.46999898552895},
    {2406, 1, 0.050999000668526, -0.10700000077486, -0.040998999029398, 3.0, 56.20002746582, -6.899995803833, 0.56399899721146, 0.88999897241592, 0.46999898552895},
    {2102, 1, 0.043999001383781, -0.15599900484085, -0.076999001204967, 0.0, 31.199995040894, 0.0, 0.75400000810623, 0.76299899816513, 0.7119989991188},
    {3272, 1, 0.082000002264977, -0.089900001883507, -0.008899999782443, -85.39990234375, 178.69999694824, -89.099998474121, 0.26300001144409, 0.24089999496937, 0.064000003039837},
    {1371, 1, 0.14800000190735, -0.21690000593662, 0.0, 4.0998997688293, 88.0, 0.0, 0.44290000200272, 0.3740000128746, 0.41490000486374},
    {2690, 1, 0.076999001204967, -0.14599600434303, 0.0089999996125698, 0.0, 62.5, 0.0, 0.77300000190735, 0.64999997615814, 0.83499997854233},
    {2712, 1, 0.087999999523163, -0.16799999773502, 0.11999999731779, -13.400010108948, 103.39999389648, -1.0999989509583, 0.84299898147583, 1.0, 0.98299902677536},
    {2045, 1, 0.052999000996351, -0.10999900102615, -0.03999999910593, 5.4000000953674, -30.800043106079, -88.699951171875, 1.0, 1.0, 1.0},
    {7093, 1, 0.0, 0.46590000391006, -0.0658999979496, 0.0, 92.400001525879, -5.4998998641968, 0.11289999634027, 0.19990000128746, 0.1368999928236},    
    {19578, 1, -0.012900000438094, -0.18690000474453, 0.0, 0.0, 0.0, -24.39999961853, 1.9299000501633, 3.2000000476837, 4.9070000648499},
    {1607, 1, 0.12189999967813, -0.23989999294281, 0.008899999782443, 87.599998474121, 21.89999961853, -91.199996948242, 0.25090000033379, 0.14990000426769, 0.20600000023842}
};
// === Toys Dragon Vip ===
#define DRAGON_COUNT 3
enum eDtoysData
{
    dModel,
    dBone,
    Float:dX,
    Float:dY,
    Float:dZ,
    Float:dRX,
    Float:dRY,
    Float:dRZ,
    Float:dSX,
    Float:dSY,
    Float:dSZ,
    dStatus // bisa digunakan untuk status attach
}
new pToysDragon[MAX_PLAYERS][DRAGON_COUNT][eDtoysData];


new DragonToys[DRAGON_COUNT][eToyData] = 
{
    {3528, 2, 0.064000003039837, 0.082999996840954, -0.034000001847744, 0.0, 81.399971008301, 80.599983215332, 0.068998997807503, 0.083998998403549, 0.080999998152256},
    {3528, 1, 0.15599900484085, -0.1870000064373, 0.29500100016594, -159.30004882813, 0.0, 0.0, 0.25, 0.0079990001395345, 0.16699899733067},
    {3528, 1, 0.15599900484085, -0.1870000064373, -0.34599900245667, -21.599996566772, 0.0, 0.0, 0.25, 0.0079990001395345, 0.16699899733067}
};

stock MySQL_SavePlayerDragonToys(playerid)
{
    new cQuery[2048];
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `dragon_toys` SET `Slot0_Model`=%d, `Slot0_Bone`=%d, `Slot0_Status`=%d, `Slot0_XPos`=%f, `Slot0_YPos`=%f, `Slot0_ZPos`=%f, `Slot0_XRot`=%f, `Slot0_YRot`=%f, `Slot0_ZRot`=%f, `Slot0_XScale`=%f, `Slot0_YScale`=%f, `Slot0_ZScale`=%f,\
	`Slot1_Model`=%d, `Slot1_Bone`=%d, `Slot1_Status`=%d, `Slot1_XPos`=%f, `Slot1_YPos`=%f, `Slot1_ZPos`=%f, `Slot1_XRot`=%f, `Slot1_YRot`=%f, `Slot1_ZRot`=%f, `Slot1_XScale`=%f, `Slot1_YScale`=%f, `Slot1_ZScale`=%f,\
	`Slot2_Model`=%d, `Slot2_Bone`=%d, `Slot2_Status`=%d, `Slot2_XPos`=%f, `Slot2_YPos`=%f, `Slot2_ZPos`=%f, `Slot2_XRot`=%f, `Slot2_YRot`=%f, `Slot2_ZRot`=%f, `Slot2_XScale`=%f, `Slot2_YScale`=%f, `Slot2_ZScale`=%f WHERE `Owner`='%s'",
	pToysDragon[playerid][0][dModel], pToysDragon[playerid][0][dBone], pToysDragon[playerid][0][dStatus], pToysDragon[playerid][0][dX], pToysDragon[playerid][0][dY], pToysDragon[playerid][0][dZ], pToysDragon[playerid][0][dRX], pToysDragon[playerid][0][dRY], pToysDragon[playerid][0][dRZ], pToysDragon[playerid][0][dSX], pToysDragon[playerid][0][dSY], pToysDragon[playerid][0][dSZ],
    pToysDragon[playerid][1][dModel], pToysDragon[playerid][1][dBone], pToysDragon[playerid][1][dStatus], pToysDragon[playerid][1][dX], pToysDragon[playerid][1][dY], pToysDragon[playerid][1][dZ], pToysDragon[playerid][1][dRX], pToysDragon[playerid][1][dRY], pToysDragon[playerid][1][dRZ], pToysDragon[playerid][1][dSX], pToysDragon[playerid][1][dSY], pToysDragon[playerid][1][dSZ],
    pToysDragon[playerid][2][dModel], pToysDragon[playerid][2][dBone], pToysDragon[playerid][2][dStatus], pToysDragon[playerid][2][dX], pToysDragon[playerid][2][dY], pToysDragon[playerid][2][dZ], pToysDragon[playerid][2][dRX], pToysDragon[playerid][2][dRY], pToysDragon[playerid][2][dRZ], pToysDragon[playerid][2][dSX], pToysDragon[playerid][2][dSY], pToysDragon[playerid][2][dSZ], AccountData[playerid][pName]);
	mysql_tquery(g_SQL, cQuery, "OnSaveDragonToys");
    printf("Memanggil save toys dragon untuk playerid %d", playerid);
    return 1;
}


forward LoadPlayerDragonToys(playerid);
public LoadPlayerDragonToys(playerid)
{
    new rows = cache_num_rows();
    if(rows)
    {
        AccountData[playerid][PurchasedDragonToy] = true;
        cache_get_value_name_int(0, "Slot0_Model", pToysDragon[playerid][0][dModel]);
  		cache_get_value_name_int(0, "Slot0_Bone", pToysDragon[playerid][0][dBone]);
		cache_get_value_name_int(0, "Slot0_Status", pToysDragon[playerid][0][dStatus]);
  		cache_get_value_name_float(0, "Slot0_XPos", pToysDragon[playerid][0][dX]);
  		cache_get_value_name_float(0, "Slot0_YPos", pToysDragon[playerid][0][dY]);
  		cache_get_value_name_float(0, "Slot0_ZPos", pToysDragon[playerid][0][dZ]);
  		cache_get_value_name_float(0, "Slot0_XRot", pToysDragon[playerid][0][dRX]);
  		cache_get_value_name_float(0, "Slot0_YRot", pToysDragon[playerid][0][dRY]);
  		cache_get_value_name_float(0, "Slot0_ZRot", pToysDragon[playerid][0][dRZ]);
  		cache_get_value_name_float(0, "Slot0_XScale", pToysDragon[playerid][0][dSX]);
  		cache_get_value_name_float(0, "Slot0_YScale", pToysDragon[playerid][0][dSY]);
		cache_get_value_name_float(0, "Slot0_ZScale", pToysDragon[playerid][0][dSZ]);
		
		cache_get_value_name_int(0, "Slot1_Model", pToysDragon[playerid][1][dModel]);
  		cache_get_value_name_int(0, "Slot1_Bone", pToysDragon[playerid][1][dBone]);
		cache_get_value_name_int(0, "Slot1_Status", pToysDragon[playerid][1][dStatus]);
  		cache_get_value_name_float(0, "Slot1_XPos", pToysDragon[playerid][1][dX]);
  		cache_get_value_name_float(0, "Slot1_YPos", pToysDragon[playerid][1][dY]);
  		cache_get_value_name_float(0, "Slot1_ZPos", pToysDragon[playerid][1][dZ]);
  		cache_get_value_name_float(0, "Slot1_XRot", pToysDragon[playerid][1][dRX]);
  		cache_get_value_name_float(0, "Slot1_YRot", pToysDragon[playerid][1][dRY]);
  		cache_get_value_name_float(0, "Slot1_ZRot", pToysDragon[playerid][1][dRZ]);
  		cache_get_value_name_float(0, "Slot1_XScale", pToysDragon[playerid][1][dSX]);
  		cache_get_value_name_float(0, "Slot1_YScale", pToysDragon[playerid][1][dSY]);
		cache_get_value_name_float(0, "Slot1_ZScale", pToysDragon[playerid][1][dSZ]);
		
		cache_get_value_name_int(0, "Slot2_Model", pToysDragon[playerid][2][dModel]);
  		cache_get_value_name_int(0, "Slot2_Bone", pToysDragon[playerid][2][dBone]);
		cache_get_value_name_int(0, "Slot2_Status", pToysDragon[playerid][2][dStatus]);
  		cache_get_value_name_float(0, "Slot2_XPos", pToysDragon[playerid][2][dX]);
  		cache_get_value_name_float(0, "Slot2_YPos", pToysDragon[playerid][2][dY]);
  		cache_get_value_name_float(0, "Slot2_ZPos", pToysDragon[playerid][2][dZ]);
  		cache_get_value_name_float(0, "Slot2_XRot", pToysDragon[playerid][2][dRX]);
  		cache_get_value_name_float(0, "Slot2_YRot", pToysDragon[playerid][2][dRY]);
  		cache_get_value_name_float(0, "Slot2_ZRot", pToysDragon[playerid][2][dRZ]);
  		cache_get_value_name_float(0, "Slot2_XScale", pToysDragon[playerid][2][dSX]);
  		cache_get_value_name_float(0, "Slot2_YScale", pToysDragon[playerid][2][dSY]);
		cache_get_value_name_float(0, "Slot2_ZScale", pToysDragon[playerid][2][dSZ]);

        AttachPlayerToysDragon(playerid);
        printf("[Player Fashion] Memuat Dragon Toys untuk: %s(%d)", AccountData[playerid][pName], playerid);
    }
    return 1;
}

AttachPlayerToysDragon(playerid)
{
    if(AccountData[playerid][PurchasedDragonToy] == false) return 1;
    for(new i = 0; i < DRAGON_COUNT; i++)
    {
        if(pToysDragon[playerid][i][dStatus] != 0)
        {
            SetPlayerAttachedObject(playerid, 0 + i,
                pToysDragon[playerid][i][dModel], pToysDragon[playerid][i][dBone],
                pToysDragon[playerid][i][dX], pToysDragon[playerid][i][dY], pToysDragon[playerid][i][dZ],
                pToysDragon[playerid][i][dRX], pToysDragon[playerid][i][dRY], pToysDragon[playerid][i][dRZ],
                pToysDragon[playerid][i][dSX], pToysDragon[playerid][i][dSY], pToysDragon[playerid][i][dSZ]);
        }
    }
    printf("memanggil attac player dragon toys ke playerid %d", playerid);
    return 1;
}
// === Toys Sonic Vip ===
#define SONIC_COUNT 6

enum e_toyssonic
{
    sModel,
    sBone,
    Float:sX,
    Float:sY,
    Float:sZ,
    Float:sRX,
    Float:sRY,
    Float:sRZ,
    Float:sSX,
    Float:sSY,
    Float:sSZ,
    sStatus // bisa digunakan untuk status attach
}
new pToysSonic[MAX_PLAYERS][SONIC_COUNT][e_toyssonic];

new SonicToys[SONIC_COUNT][eToyData] = 
{
    {3100, 2, 0.068000003695488, 0.0020000000949949, 0.0040000001899898, 82.599998474121, 0.20000000298023, 99.499900817871, 3.5158998966217, 3.9498999118805, 4.0079002380371},
    {3100, 2, 0.11500000208616, -0.10189999639988, 0.0040000001899898, 80.199996948242, 147.60000610352, 99.499900817871, 2.8568999767303, 1.8839000463486, 4.0079002380371},
    {3100, 2, -0.019899999722838, -0.11389999836683, 0.0040000001899898, 84.599998474121, 128.80000305176, 99.499900817871, 2.275899887085, 1.4838999509811, 3.9309000968933},
    {19094, 2, 0.0098999999463558, 0.059000000357628, -0.003000000026077, 178.29989624023, 7.5998997688293, -85.599899291992, 0.97990000247955, 0.34589999914169, 0.57200002670288},
    {1254, 2, 0.063000001013279, 0.11689999699593, -0.037900000810623, -17.499900817871, 144.10000610352, -2.2000000476837, 0.36489999294281, 0.27090001106262, 0.47490000724792},
    {1254, 2, 0.056000001728535,  0.11389999836683, 0.037900000810623, 17.60000038147, 18.499900817871, 9.0999002456665, 0.36489999294281, 0.27090001106262, 0.47490000724792}
};

stock MySQL_SavePlayerSonicToys(playerid)
{
    new cQuery[2048];
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `sonic_toys` SET `Slot0_Model`=%d, `Slot0_Bone`=%d, `Slot0_Status`=%d, `Slot0_XPos`=%f, `Slot0_YPos`=%f, `Slot0_ZPos`=%f, `Slot0_XRot`=%f, `Slot0_YRot`=%f, `Slot0_ZRot`=%f, `Slot0_XScale`=%f, `Slot0_YScale`=%f, `Slot0_ZScale`=%f,\
	`Slot1_Model`=%d, `Slot1_Bone`=%d, `Slot1_Status`=%d, `Slot1_XPos`=%f, `Slot1_YPos`=%f, `Slot1_ZPos`=%f, `Slot1_XRot`=%f, `Slot1_YRot`=%f, `Slot1_ZRot`=%f, `Slot1_XScale`=%f, `Slot1_YScale`=%f, `Slot1_ZScale`=%f,\
	`Slot2_Model`=%d, `Slot2_Bone`=%d, `Slot2_Status`=%d, `Slot2_XPos`=%f, `Slot2_YPos`=%f, `Slot2_ZPos`=%f, `Slot2_XRot`=%f, `Slot2_YRot`=%f, `Slot2_ZRot`=%f, `Slot2_XScale`=%f, `Slot2_YScale`=%f, `Slot2_ZScale`=%f WHERE `Owner`='%s'",
	pToysSonic[playerid][0][sModel], pToysSonic[playerid][0][sBone], pToysSonic[playerid][0][sStatus], pToysSonic[playerid][0][sX], pToysSonic[playerid][0][sY], pToysSonic[playerid][0][sZ], pToysSonic[playerid][0][sRX], pToysSonic[playerid][0][sRY], pToysSonic[playerid][0][sRZ], pToysSonic[playerid][0][sSX], pToysSonic[playerid][0][sSY], pToysSonic[playerid][0][sSZ],
    pToysSonic[playerid][1][sModel], pToysSonic[playerid][1][sBone], pToysSonic[playerid][1][sStatus], pToysSonic[playerid][1][sX], pToysSonic[playerid][1][sY], pToysSonic[playerid][1][sZ], pToysSonic[playerid][1][sRX], pToysSonic[playerid][1][sRY], pToysSonic[playerid][1][sRZ], pToysSonic[playerid][1][sSX], pToysSonic[playerid][1][sSY], pToysSonic[playerid][1][sSZ],
    pToysSonic[playerid][2][sModel], pToysSonic[playerid][2][sBone], pToysSonic[playerid][2][sStatus], pToysSonic[playerid][2][sX], pToysSonic[playerid][2][sY], pToysSonic[playerid][2][sZ], pToysSonic[playerid][2][sRX], pToysSonic[playerid][2][sRY], pToysSonic[playerid][2][sRZ], pToysSonic[playerid][2][sSX], pToysSonic[playerid][2][sSY], pToysSonic[playerid][2][sSZ], AccountData[playerid][pName]);
	mysql_tquery(g_SQL, cQuery, "OnSaveSonicToys");
    printf("Memanggil save toys sonic untuk playerid %d", playerid);
    return 1;
}

forward OnSaveSonicToys(playerid, result, affected_rows);
public OnSaveSonicToys(playerid, result, affected_rows)
{
    AccountData[playerid][PurchasedSonicToy] = true;
    printf("Save sonic Toys playerid %d berhasil, affected_rows=%d", playerid, affected_rows);
    return 1;
}

forward LoadPlayerSonicToys(playerid);
public LoadPlayerSonicToys(playerid)
{
    new rows = cache_num_rows();
    if(rows)
    {
        AccountData[playerid][PurchasedSonicToy] = true;
        cache_get_value_name_int(0, "Slot0_Model", pToysSonic[playerid][0][sModel]);
  		cache_get_value_name_int(0, "Slot0_Bone", pToysSonic[playerid][0][sBone]);
		cache_get_value_name_int(0, "Slot0_Status", pToysSonic[playerid][0][sStatus]);
  		cache_get_value_name_float(0, "Slot0_XPos", pToysSonic[playerid][0][sX]);
  		cache_get_value_name_float(0, "Slot0_YPos", pToysSonic[playerid][0][sY]);
  		cache_get_value_name_float(0, "Slot0_ZPos", pToysSonic[playerid][0][sZ]);
  		cache_get_value_name_float(0, "Slot0_XRot", pToysSonic[playerid][0][sRX]);
  		cache_get_value_name_float(0, "Slot0_YRot", pToysSonic[playerid][0][sRY]);
  		cache_get_value_name_float(0, "Slot0_ZRot", pToysSonic[playerid][0][sRZ]);
  		cache_get_value_name_float(0, "Slot0_XScale", pToysSonic[playerid][0][sSX]);
  		cache_get_value_name_float(0, "Slot0_YScale", pToysSonic[playerid][0][sSY]);
		cache_get_value_name_float(0, "Slot0_ZScale", pToysSonic[playerid][0][sSZ]);
		
		cache_get_value_name_int(0, "Slot1_Model", pToysSonic[playerid][1][sModel]);
  		cache_get_value_name_int(0, "Slot1_Bone", pToysSonic[playerid][1][sBone]);
		cache_get_value_name_int(0, "Slot1_Status", pToysSonic[playerid][1][sStatus]);
  		cache_get_value_name_float(0, "Slot1_XPos", pToysSonic[playerid][1][sX]);
  		cache_get_value_name_float(0, "Slot1_YPos", pToysSonic[playerid][1][sY]);
  		cache_get_value_name_float(0, "Slot1_ZPos", pToysSonic[playerid][1][sZ]);
  		cache_get_value_name_float(0, "Slot1_XRot", pToysSonic[playerid][1][sRX]);
  		cache_get_value_name_float(0, "Slot1_YRot", pToysSonic[playerid][1][sRY]);
  		cache_get_value_name_float(0, "Slot1_ZRot", pToysSonic[playerid][1][sRZ]);
  		cache_get_value_name_float(0, "Slot1_XScale", pToysSonic[playerid][1][sSX]);
  		cache_get_value_name_float(0, "Slot1_YScale", pToysSonic[playerid][1][sSY]);
		cache_get_value_name_float(0, "Slot1_ZScale", pToysSonic[playerid][1][sSZ]);
		
		cache_get_value_name_int(0, "Slot2_Model", pToysSonic[playerid][2][sModel]);
  		cache_get_value_name_int(0, "Slot2_Bone", pToysSonic[playerid][2][sBone]);
		cache_get_value_name_int(0, "Slot2_Status", pToysSonic[playerid][2][sStatus]);
  		cache_get_value_name_float(0, "Slot2_XPos", pToysSonic[playerid][2][sX]);
  		cache_get_value_name_float(0, "Slot2_YPos", pToysSonic[playerid][2][sY]);
  		cache_get_value_name_float(0, "Slot2_ZPos", pToysSonic[playerid][2][sZ]);
  		cache_get_value_name_float(0, "Slot2_XRot", pToysSonic[playerid][2][sRX]);
  		cache_get_value_name_float(0, "Slot2_YRot", pToysSonic[playerid][2][sRY]);
  		cache_get_value_name_float(0, "Slot2_ZRot", pToysSonic[playerid][2][sRZ]);
  		cache_get_value_name_float(0, "Slot2_XScale", pToysSonic[playerid][2][sSX]);
  		cache_get_value_name_float(0, "Slot2_YScale", pToysSonic[playerid][2][sSY]);
		cache_get_value_name_float(0, "Slot2_ZScale", pToysSonic[playerid][2][sSZ]);

        AttachPlayerToysSonic(playerid);
        printf("[Player Fashion] Memuat sonic Toys untuk: %s(%d)", AccountData[playerid][pName], playerid);
    }
    return 1;
}
AttachPlayerToysSonic(playerid)
{
    if(AccountData[playerid][PurchasedSonicToy] == false) return 1;
    for(new i = 0; i < SONIC_COUNT; i++)
    {
        if(pToysSonic[playerid][i][sStatus] != 0)
        {
            SetPlayerAttachedObject(playerid, 0 + i,
                pToysSonic[playerid][i][sModel], pToysSonic[playerid][i][sBone],
                pToysSonic[playerid][i][sX], pToysSonic[playerid][i][sY], pToysSonic[playerid][i][sZ],
                pToysSonic[playerid][i][sRX], pToysSonic[playerid][i][sRY], pToysSonic[playerid][i][sRZ],
                pToysSonic[playerid][i][sSX], pToysSonic[playerid][i][sSY], pToysSonic[playerid][i][sSZ]);
        }
    }
    printf("memanggil attac player sonic toys ke playerid %d", playerid);
    return 1;
}


// === Toys Grinch Vip ===
#define GRINCH_COUNT 7

enum e_toysgrinch
{
    gModel,
    gBone,
    Float:gX,
    Float:gY,
    Float:gZ,
    Float:gRX,
    Float:gRY,
    Float:gRZ,
    Float:gSX,
    Float:gSY,
    Float:gSZ,
    gStatus // bisa digunakan untuk status attach
}
new pToysGrinch[MAX_PLAYERS][GRINCH_COUNT][e_toysgrinch];
new GrinchToys[GRINCH_COUNT][eToyData] = 
{
    {19576, 2, 0.15389999747276, 0.008899999782443, 0.0080000003799796, 0.0, -89.299896240234, 176.60000610352, 2.4858999252319, 2.7650001049042, 3.7630000114441},
    {19570, 2, 0.20100000500679, 0.1009000018239, 0.030899999663234, -89.399803161621, 13.5, 7.8998999595642, 0.26489999890327, 0.49790000915527, 0.061900001019239},
    {19570, 2, 0.20290000736713,  0.096900001168251, -0.016000000759959, -103.5, 14.399900436401, -11.800000190735, 0.26800000667572, 0.51389998197556, 0.061900001019239},
    {19576, 2, 0.099899999797344, 0.035900000482798, 0.0049000000581145, 79.599998474121, -144.2998046875, -85.499900817871, 3.5090000629425,  3.0060000419617, 2.914999961853},
    {19078, 2,  0.29690000414848, 0.0, 0.0049000000581145, 176.39999389648, -176.19990539551, -51.799900054932, 0.5048999786377, 0.55290001630783, 0.55900001525879},
    {19576, 1, 0.040899999439716,  0.0098999999463558, -0.010900000110269, 13.900099754333, -91.999702453613, -160.69979858398, 5.0939002037048, 4.4000000953674, 7.5529999732971},
    {2788, 1, 0.31090000271797, 0.030899999663234, -0.024900000542402, 84.799896240234, -88.199996948242, -89.5, 0.58600002527237, 0.54900002479553, 1.7079000473022}
};

stock MySQL_SavePlayerGrinchToys(playerid)
{
    new cQuery[2048];
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `grinch_toys` SET `Slot0_Model`=%d, `Slot0_Bone`=%d, `Slot0_Status`=%d, `Slot0_XPos`=%f, `Slot0_YPos`=%f, `Slot0_ZPos`=%f, `Slot0_XRot`=%f, `Slot0_YRot`=%f, `Slot0_ZRot`=%f, `Slot0_XScale`=%f, `Slot0_YScale`=%f, `Slot0_ZScale`=%f,\
	`Slot1_Model`=%d, `Slot1_Bone`=%d, `Slot1_Status`=%d, `Slot1_XPos`=%f, `Slot1_YPos`=%f, `Slot1_ZPos`=%f, `Slot1_XRot`=%f, `Slot1_YRot`=%f, `Slot1_ZRot`=%f, `Slot1_XScale`=%f, `Slot1_YScale`=%f, `Slot1_ZScale`=%f,\
	`Slot2_Model`=%d, `Slot2_Bone`=%d, `Slot2_Status`=%d, `Slot2_XPos`=%f, `Slot2_YPos`=%f, `Slot2_ZPos`=%f, `Slot2_XRot`=%f, `Slot2_YRot`=%f, `Slot2_ZRot`=%f, `Slot2_XScale`=%f, `Slot2_YScale`=%f, `Slot2_ZScale`=%f WHERE `Owner`='%s'",
	pToysGrinch[playerid][0][gModel], pToysGrinch[playerid][0][gBone], pToysGrinch[playerid][0][gStatus], pToysGrinch[playerid][0][gX], pToysGrinch[playerid][0][gY], pToysGrinch[playerid][0][gZ], pToysGrinch[playerid][0][gRX], pToysGrinch[playerid][0][gRY], pToysGrinch[playerid][0][gRZ], pToysGrinch[playerid][0][gSX], pToysGrinch[playerid][0][gSY], pToysGrinch[playerid][0][gSZ],
    pToysGrinch[playerid][1][gModel], pToysGrinch[playerid][1][gBone], pToysGrinch[playerid][1][gStatus], pToysGrinch[playerid][1][gX], pToysGrinch[playerid][1][gY], pToysGrinch[playerid][1][gZ], pToysGrinch[playerid][1][gRX], pToysGrinch[playerid][1][gRY], pToysGrinch[playerid][1][gRZ], pToysGrinch[playerid][1][gSX], pToysGrinch[playerid][1][gSY], pToysGrinch[playerid][1][gSZ],
    pToysGrinch[playerid][2][gModel], pToysGrinch[playerid][2][gBone], pToysGrinch[playerid][2][gStatus], pToysGrinch[playerid][2][gX], pToysGrinch[playerid][2][gY], pToysGrinch[playerid][2][gZ], pToysGrinch[playerid][2][gRX], pToysGrinch[playerid][2][gRY], pToysGrinch[playerid][2][gRZ], pToysGrinch[playerid][2][gSX], pToysGrinch[playerid][2][gSY], pToysGrinch[playerid][2][gSZ], AccountData[playerid][pName]);
    printf("Memanggil save toys grinch untuk playerid %d", playerid);
    return 1;
}

forward LoadPlayerGrinchToys(playerid);
public LoadPlayerGrinchToys(playerid)
{
    new rows = cache_num_rows();
    if(rows)
    {
        AccountData[playerid][PurchasedGrinchToy] = true;
        cache_get_value_name_int(0, "Slot0_Model", pToysGrinch[playerid][0][gModel]);
  		cache_get_value_name_int(0, "Slot0_Bone", pToysGrinch[playerid][0][gBone]);
		cache_get_value_name_int(0, "Slot0_Status", pToysGrinch[playerid][0][gStatus]);
  		cache_get_value_name_float(0, "Slot0_XPos", pToysGrinch[playerid][0][gX]);
  		cache_get_value_name_float(0, "Slot0_YPos", pToysGrinch[playerid][0][gY]);
  		cache_get_value_name_float(0, "Slot0_ZPos", pToysGrinch[playerid][0][gZ]);
  		cache_get_value_name_float(0, "Slot0_XRot", pToysGrinch[playerid][0][gRX]);
  		cache_get_value_name_float(0, "Slot0_YRot", pToysGrinch[playerid][0][gRY]);
  		cache_get_value_name_float(0, "Slot0_ZRot", pToysGrinch[playerid][0][gRZ]);
  		cache_get_value_name_float(0, "Slot0_XScale", pToysGrinch[playerid][0][gSX]);
  		cache_get_value_name_float(0, "Slot0_YScale", pToysGrinch[playerid][0][gSY]);
		cache_get_value_name_float(0, "Slot0_ZScale", pToysGrinch[playerid][0][gSZ]);
		
		cache_get_value_name_int(0, "Slot1_Model", pToysGrinch[playerid][1][gModel]);
  		cache_get_value_name_int(0, "Slot1_Bone", pToysGrinch[playerid][1][gBone]);
		cache_get_value_name_int(0, "Slot1_Status", pToysGrinch[playerid][1][gStatus]);
  		cache_get_value_name_float(0, "Slot1_XPos", pToysGrinch[playerid][1][gX]);
  		cache_get_value_name_float(0, "Slot1_YPos", pToysGrinch[playerid][1][gY]);
  		cache_get_value_name_float(0, "Slot1_ZPos", pToysGrinch[playerid][1][gZ]);
  		cache_get_value_name_float(0, "Slot1_XRot", pToysGrinch[playerid][1][gRX]);
  		cache_get_value_name_float(0, "Slot1_YRot", pToysGrinch[playerid][1][gRY]);
  		cache_get_value_name_float(0, "Slot1_ZRot", pToysGrinch[playerid][1][gRZ]);
  		cache_get_value_name_float(0, "Slot1_XScale", pToysGrinch[playerid][1][gSX]);
  		cache_get_value_name_float(0, "Slot1_YScale", pToysGrinch[playerid][1][gSY]);
		cache_get_value_name_float(0, "Slot1_ZScale", pToysGrinch[playerid][1][gSZ]);
		
		cache_get_value_name_int(0, "Slot2_Model", pToysGrinch[playerid][2][gModel]);
  		cache_get_value_name_int(0, "Slot2_Bone", pToysGrinch[playerid][2][gBone]);
		cache_get_value_name_int(0, "Slot2_Status", pToysGrinch[playerid][2][gStatus]);
  		cache_get_value_name_float(0, "Slot2_XPos", pToysGrinch[playerid][2][gX]);
  		cache_get_value_name_float(0, "Slot2_YPos", pToysGrinch[playerid][2][gY]);
  		cache_get_value_name_float(0, "Slot2_ZPos", pToysGrinch[playerid][2][gZ]);
  		cache_get_value_name_float(0, "Slot2_XRot", pToysGrinch[playerid][2][gRX]);
  		cache_get_value_name_float(0, "Slot2_YRot", pToysGrinch[playerid][2][gRY]);
  		cache_get_value_name_float(0, "Slot2_ZRot", pToysGrinch[playerid][2][gRZ]);
  		cache_get_value_name_float(0, "Slot2_XScale", pToysGrinch[playerid][2][gSX]);
  		cache_get_value_name_float(0, "Slot2_YScale", pToysGrinch[playerid][2][gSY]);
		cache_get_value_name_float(0, "Slot2_ZScale", pToysGrinch[playerid][2][gSZ]);

        AttachPlayerToysGrinch(playerid);
        printf("[Player Fashion] Memuat Grinch untuk: %s(%d)", AccountData[playerid][pName], playerid);
    }
    return 1;
}
AttachPlayerToysGrinch(playerid)
{
    if(AccountData[playerid][PurchasedGrinchToy] == false) return 1;
    for(new i = 0; i < GRINCH_COUNT; i++)
    {
        if(pToysGrinch[playerid][i][gStatus] != 0)
        {
            SetPlayerAttachedObject(playerid, 0 + i,
                pToysGrinch[playerid][i][gModel], pToysGrinch[playerid][i][gBone],
                pToysGrinch[playerid][i][gX], pToysGrinch[playerid][i][gY], pToysGrinch[playerid][i][gZ],
                pToysGrinch[playerid][i][gRX], pToysGrinch[playerid][i][gRY], pToysGrinch[playerid][i][gRZ],
                pToysGrinch[playerid][i][gSX], pToysGrinch[playerid][i][gSY], pToysGrinch[playerid][i][gSZ]);
        }
    }
    printf("memanggil attac player gricnch toys ke playerid %d", playerid);
    return 1;
}

// === Toys Ghost Vip ===
#define GHOST_COUNT 5

enum e_ghosttoys
{
    gsModel,
    gsBone,
    Float:gsX,
    Float:gsY,
    Float:gsZ,
    Float:gsRX,
    Float:gsRY,
    Float:gsRZ,
    Float:gsSX,
    Float:gsSY,
    Float:gsSZ,
    gsStatus // bisa digunakan untuk status attach
}
new pToysGhost[MAX_PLAYERS][GHOST_COUNT][e_ghosttoys];
new GhostToys[GHOST_COUNT][eToyData] = 
{
    {19200, 1, -0.16290000081062, 0.013899999670684, -0.12489999830723, -99.800003051758, -178.10000610352, -173.69990539551, 5.4299001693726, 2.2039000988007, 2.3589000701904},
    {19200, 1, -0.19390000402927, -0.0049000000581145, 0.10400000214577,  94.099899291992, -178.10000610352, -173.69990539551, 5.7838997840881, 2.4639000892639, 2.5678999423981},
    {19200, 1, 0.082000002264977, -0.0010000000474975, 0.0, -4.4000000953674, 176.49989318848, 176.60000610352, 5.7838997840881, 1.5938999652863, 2.1278998851776},
    {11741, 1, 0.46189999580383, 0.17890000343323, -0.046900000423193, 79.199897766113, 0.0, -59.799900054932, 0.24789999425411, 0.4869000017643, 1.0},
    {11741, 1, 0.46189999580383, 0.17890000343323, 0.060899998992682, 95.799896240234, -5.9998998641968, -117.69999694824, 0.24789999425411, 0.4869000017643, 1.0}
};

stock MySQL_SavePlayerGhostToys(playerid)
{
    new cQuery[2048];
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `ghost_toys` SET `Slot0_Model`=%d, `Slot0_Bone`=%d, `Slot0_Status`=%d, `Slot0_XPos`=%f, `Slot0_YPos`=%f, `Slot0_ZPos`=%f, `Slot0_XRot`=%f, `Slot0_YRot`=%f, `Slot0_ZRot`=%f, `Slot0_XScale`=%f, `Slot0_YScale`=%f, `Slot0_ZScale`=%f,\
	`Slot1_Model`=%d, `Slot1_Bone`=%d, `Slot1_Status`=%d, `Slot1_XPos`=%f, `Slot1_YPos`=%f, `Slot1_ZPos`=%f, `Slot1_XRot`=%f, `Slot1_YRot`=%f, `Slot1_ZRot`=%f, `Slot1_XScale`=%f, `Slot1_YScale`=%f, `Slot1_ZScale`=%f,\
	`Slot2_Model`=%d, `Slot2_Bone`=%d, `Slot2_Status`=%d, `Slot2_XPos`=%f, `Slot2_YPos`=%f, `Slot2_ZPos`=%f, `Slot2_XRot`=%f, `Slot2_YRot`=%f, `Slot2_ZRot`=%f, `Slot2_XScale`=%f, `Slot2_YScale`=%f, `Slot2_ZScale`=%f WHERE `Owner`='%s'",
	pToysGhost[playerid][0][gsModel], 
    pToysGhost[playerid][0][gsBone], 
    pToysGhost[playerid][0][gsStatus], 
    pToysGhost[playerid][0][gsX], 
    pToysGhost[playerid][0][gsY], 
    pToysGhost[playerid][0][gsZ], 
    pToysGhost[playerid][0][gsRX], 
    pToysGhost[playerid][0][gsRY], 
    pToysGhost[playerid][0][gsRZ], 
    pToysGhost[playerid][0][gsSX], 
    pToysGhost[playerid][0][gsSY], 
    pToysGhost[playerid][0][gsSZ],
    pToysGhost[playerid][1][gsModel], 
    pToysGhost[playerid][1][gsBone], 
    pToysGhost[playerid][1][gsStatus], 
    pToysGhost[playerid][1][gsX], 
    pToysGhost[playerid][1][gsY], 
    pToysGhost[playerid][1][gsZ], 
    pToysGhost[playerid][1][gsRX], 
    pToysGhost[playerid][1][gsRY], 
    pToysGhost[playerid][1][gsRZ], 
    pToysGhost[playerid][1][gsSX], 
    pToysGhost[playerid][1][gsSY], 
    pToysGhost[playerid][1][gsSZ],
    pToysGhost[playerid][2][gsModel], 
    pToysGhost[playerid][2][gsBone], 
    pToysGhost[playerid][2][gsStatus], 
    pToysGhost[playerid][2][gsX], 
    pToysGhost[playerid][2][gsY], 
    pToysGhost[playerid][2][gsZ], 
    pToysGhost[playerid][2][gsRX], 
    pToysGhost[playerid][2][gsRY], 
    pToysGhost[playerid][2][gsRZ], 
    pToysGhost[playerid][2][gsSX], 
    pToysGhost[playerid][2][gsSY], 
    pToysGhost[playerid][2][gsSZ], 
    AccountData[playerid][pName]);
    printf("Memanggil save toys ghost untuk playerid %d", playerid);
    return 1;
}

forward LoadPlayerGhostToys(playerid);
public LoadPlayerGhostToys(playerid)
{
    new rows = cache_num_rows();
    if(rows)
    {
        AccountData[playerid][PurchasedGhostToy] = true;
        cache_get_value_name_int(0, "Slot0_Model", pToysGhost[playerid][0][gsModel]);
  		cache_get_value_name_int(0, "Slot0_Bone", pToysGhost[playerid][0][gsBone]);
		cache_get_value_name_int(0, "Slot0_Status", pToysGhost[playerid][0][gsStatus]);
  		cache_get_value_name_float(0, "Slot0_XPos", pToysGhost[playerid][0][gsX]);
  		cache_get_value_name_float(0, "Slot0_YPos", pToysGhost[playerid][0][gsY]);
  		cache_get_value_name_float(0, "Slot0_ZPos", pToysGhost[playerid][0][gsZ]);
  		cache_get_value_name_float(0, "Slot0_XRot", pToysGhost[playerid][0][gsRX]);
  		cache_get_value_name_float(0, "Slot0_YRot", pToysGhost[playerid][0][gsRY]);
  		cache_get_value_name_float(0, "Slot0_ZRot", pToysGhost[playerid][0][gsRZ]);
  		cache_get_value_name_float(0, "Slot0_XScale", pToysGhost[playerid][0][gsSX]);
  		cache_get_value_name_float(0, "Slot0_YScale", pToysGhost[playerid][0][gsSY]);
		cache_get_value_name_float(0, "Slot0_ZScale", pToysGhost[playerid][0][gsSZ]);
		
		cache_get_value_name_int(0, "Slot1_Model", pToysGhost[playerid][1][gsModel]);
  		cache_get_value_name_int(0, "Slot1_Bone", pToysGhost[playerid][1][gsBone]);
		cache_get_value_name_int(0, "Slot1_Status", pToysGhost[playerid][1][gsStatus]);
  		cache_get_value_name_float(0, "Slot1_XPos", pToysGhost[playerid][1][gsX]);
  		cache_get_value_name_float(0, "Slot1_YPos", pToysGhost[playerid][1][gsY]);
  		cache_get_value_name_float(0, "Slot1_ZPos", pToysGhost[playerid][1][gsZ]);
  		cache_get_value_name_float(0, "Slot1_XRot", pToysGhost[playerid][1][gsRX]);
  		cache_get_value_name_float(0, "Slot1_YRot", pToysGhost[playerid][1][gsRY]);
  		cache_get_value_name_float(0, "Slot1_ZRot", pToysGhost[playerid][1][gsRZ]);
  		cache_get_value_name_float(0, "Slot1_XScale", pToysGhost[playerid][1][gsSX]);
  		cache_get_value_name_float(0, "Slot1_YScale", pToysGhost[playerid][1][gsSY]);
		cache_get_value_name_float(0, "Slot1_ZScale", pToysGhost[playerid][1][gsSZ]);
		
		cache_get_value_name_int(0, "Slot2_Model", pToysGhost[playerid][2][gsModel]);
  		cache_get_value_name_int(0, "Slot2_Bone", pToysGhost[playerid][2][gsBone]);
		cache_get_value_name_int(0, "Slot2_Status", pToysGhost[playerid][2][gsStatus]);
  		cache_get_value_name_float(0, "Slot2_XPos", pToysGhost[playerid][2][gsX]);
  		cache_get_value_name_float(0, "Slot2_YPos", pToysGhost[playerid][2][gsY]);
  		cache_get_value_name_float(0, "Slot2_ZPos", pToysGhost[playerid][2][gsZ]);
  		cache_get_value_name_float(0, "Slot2_XRot", pToysGhost[playerid][2][gsRX]);
  		cache_get_value_name_float(0, "Slot2_YRot", pToysGhost[playerid][2][gsRY]);
  		cache_get_value_name_float(0, "Slot2_ZRot", pToysGhost[playerid][2][gsRZ]);
  		cache_get_value_name_float(0, "Slot2_XScale", pToysGhost[playerid][2][gsSX]);
  		cache_get_value_name_float(0, "Slot2_YScale", pToysGhost[playerid][2][gsSY]);
		cache_get_value_name_float(0, "Slot2_ZScale", pToysGhost[playerid][2][gsSZ]);

        AttachPlayerToysGhost(playerid);
        printf("[Player Fashion] Memuat sonic Grinch untuk: %s(%d)", AccountData[playerid][pName], playerid);
    }
    return 1;
}
AttachPlayerToysGhost(playerid)
{
    if(AccountData[playerid][PurchasedGrinchToy] == false) return 1;
    for(new i = 0; i < GHOST_COUNT; i++)
    {
        if(pToysGhost[playerid][i][gsStatus] != 0)
        {
            SetPlayerAttachedObject(playerid, 0 + i,
                pToysGhost[playerid][i][gsModel], pToysGhost[playerid][i][gsBone],
                pToysGhost[playerid][i][gsX], pToysGhost[playerid][i][gsY], pToysGhost[playerid][i][gsZ],
                pToysGhost[playerid][i][gsRX], pToysGhost[playerid][i][gsRY], pToysGhost[playerid][i][gsRZ],
                pToysGhost[playerid][i][gsSX], pToysGhost[playerid][i][gsSY], pToysGhost[playerid][i][gsSZ]);
        }
    }
    printf("memanggil attac player ghost toys ke playerid %d", playerid);
    return 1;
}

// === Fungsi Remove ===
stock RemoveFSToysPremium(playerid, setid)
{
    switch(setid)
    {
        case 0:
        {
            if(AccountData[playerid][PurchasedDragonToy] == true)
            {
                for(new i = 0; i < DRAGON_COUNT; i++)
                {
                    pToysDragon[playerid][i][dModel] = 0;
					pToysDragon[playerid][i][dBone] = 1;
					pToysDragon[playerid][i][dStatus] = 0;
					pToysDragon[playerid][i][dX] = 0.0;
					pToysDragon[playerid][i][dY] = 0.0;
					pToysDragon[playerid][i][dZ] = 0.0;
					pToysDragon[playerid][i][dRX] = 0.0;
					pToysDragon[playerid][i][dRY] = 0.0;
					pToysDragon[playerid][i][dRZ] = 0.0;
					pToysDragon[playerid][i][dSX] = 1.0;
					pToysDragon[playerid][i][dSY] = 1.0;
					pToysDragon[playerid][i][dSZ] = 1.0;

                    if(IsPlayerAttachedObjectSlotUsed(playerid, i))
                        RemovePlayerAttachedObject(playerid, i);
                }
                    
                new string[128];
                mysql_format(g_SQL, string, sizeof(string), "DELETE FROM dragon_toys WHERE Owner = '%s'", AccountData[playerid][pName]);
                mysql_tquery(g_SQL, string);
                AccountData[playerid][PurchasedDragonToy] = false;
                Info(playerid, "Anda berhasil menghapus toys premium dragon");
            }
        }
        case 1:
        {
            if(AccountData[playerid][PurchasedSonicToy] == true)
            {
                for(new i = 0; i < SONIC_COUNT; i++)
                {
                    pToysSonic[playerid][i][sModel] = 0;
					pToysSonic[playerid][i][sBone] = 1;
					pToysSonic[playerid][i][sStatus] = 0;
					pToysSonic[playerid][i][sX] = 0.0;
					pToysSonic[playerid][i][sY] = 0.0;
					pToysSonic[playerid][i][sZ] = 0.0;
					pToysSonic[playerid][i][sRX] = 0.0;
					pToysSonic[playerid][i][sRY] = 0.0;
					pToysSonic[playerid][i][sRZ] = 0.0;
					pToysSonic[playerid][i][sSX] = 1.0;
					pToysSonic[playerid][i][sSY] = 1.0;
					pToysSonic[playerid][i][sSZ] = 1.0;

                    if(IsPlayerAttachedObjectSlotUsed(playerid, i))
                        RemovePlayerAttachedObject(playerid, i);
                }
                    
                new string[128];
                mysql_format(g_SQL, string, sizeof(string), "DELETE FROM sonic_toys WHERE Owner = '%s'", AccountData[playerid][pName]);
                mysql_tquery(g_SQL, string);
                AccountData[playerid][PurchasedSonicToy] = false;
                Info(playerid, "Anda berhasil menghapus toys premium sonic");
            }
        }
        case 2:
        {
            if(AccountData[playerid][PurchasedGrinchToy] == true)
            {
                for(new i = 0; i < GRINCH_COUNT; i++)
                {
                    pToysGrinch[playerid][i][gModel] = 0;
					pToysGrinch[playerid][i][gBone] = 1;
					pToysGrinch[playerid][i][gStatus] = 0;
					pToysGrinch[playerid][i][gX] = 0.0;
					pToysGrinch[playerid][i][gY] = 0.0;
					pToysGrinch[playerid][i][gZ] = 0.0;
					pToysGrinch[playerid][i][gRX] = 0.0;
					pToysGrinch[playerid][i][gRY] = 0.0;
					pToysGrinch[playerid][i][gRZ] = 0.0;
					pToysGrinch[playerid][i][gSX] = 1.0;
					pToysGrinch[playerid][i][gSY] = 1.0;
					pToysGrinch[playerid][i][gSZ] = 1.0;

                    if(IsPlayerAttachedObjectSlotUsed(playerid, i))
                        RemovePlayerAttachedObject(playerid, i);
                }
                    
                new string[128];
                mysql_format(g_SQL, string, sizeof(string), "DELETE FROM grinch_toys WHERE Owner = '%s'", AccountData[playerid][pName]);
                mysql_tquery(g_SQL, string);
                AccountData[playerid][PurchasedGrinchToy] = false;
                Info(playerid, "Anda berhasil menghapus toys premium grinch");
            }
        }
        case 3:
        {
            if(AccountData[playerid][PurchasedGhostToy] == true)
            {
                for(new i = 0; i < GHOST_COUNT; i++)
                {
                    pToysGhost[playerid][i][gsModel] = 0;
					pToysGhost[playerid][i][gsBone] = 1;
					pToysGhost[playerid][i][gsStatus] = 0;
					pToysGhost[playerid][i][gsX] = 0.0;
					pToysGhost[playerid][i][gsY] = 0.0;
					pToysGhost[playerid][i][gsZ] = 0.0;
					pToysGhost[playerid][i][gsRX] = 0.0;
					pToysGhost[playerid][i][gsRY] = 0.0;
					pToysGhost[playerid][i][gsRZ] = 0.0;
					pToysGhost[playerid][i][gsSX] = 1.0;
					pToysGhost[playerid][i][gsSY] = 1.0;
					pToysGhost[playerid][i][gsSZ] = 1.0;

                    if(IsPlayerAttachedObjectSlotUsed(playerid, i))
                        RemovePlayerAttachedObject(playerid, i);
                }
                    
                new string[128];
                mysql_format(g_SQL, string, sizeof(string), "DELETE FROM ghost_toys WHERE Owner = '%s'", AccountData[playerid][pName]);
                mysql_tquery(g_SQL, string);
                AccountData[playerid][PurchasedGhostToy] = false;
                Info(playerid, "Anda berhasil menghapus toys premium ghost");
            }
        }
    }
    return 1;
}

stock RemoveFSToys(playerid)
{
    for(new i = 0; i <= 9; i++)
    {
        if(IsPlayerAttachedObjectSlotUsed(playerid, i))
            RemovePlayerAttachedObject(playerid, i);
    }
    new string[256];

    mysql_format(g_SQL, string, sizeof(string), "DELETE FROM toys_axp WHERE Owner = '%s'", AccountData[playerid][pName]);
    mysql_tquery(g_SQL, string);
    AccountData[playerid][PurchasedToyAxp] = false;
    return 1;
}

// ==== Fungsi Toys Vip ====
stock ApplyToySet(playerid, setid)
{
    new string[256];

    mysql_format(g_SQL, string, sizeof(string), "DELETE FROM dragon_toys WHERE Owner = '%s'", AccountData[playerid][pName]);
    mysql_tquery(g_SQL, string);

    mysql_format(g_SQL, string, sizeof(string), "DELETE FROM sonic_toys WHERE Owner = '%s'", AccountData[playerid][pName]);
    mysql_tquery(g_SQL, string);

    mysql_format(g_SQL, string, sizeof(string), "DELETE FROM grinch_toys WHERE Owner = '%s'", AccountData[playerid][pName]);
    mysql_tquery(g_SQL, string);

    mysql_format(g_SQL, string, sizeof(string), "DELETE FROM ghost_toys WHERE Owner = '%s'", AccountData[playerid][pName]);
    mysql_tquery(g_SQL, string);

    // Reset semua flags pembelian
    AccountData[playerid][PurchasedDragonToy] = false;
    AccountData[playerid][PurchasedSonicToy] = false;
    AccountData[playerid][PurchasedGrinchToy] = false;
    AccountData[playerid][PurchasedGhostToy] = false;
    switch(setid)
    {
        case 0: // Dragon
        {
            new cQuery[256];
            mysql_format(g_SQL, cQuery, sizeof(cQuery),"INSERT INTO dragon_toys (Owner) VALUES ('%s') ON DUPLICATE KEY UPDATE Owner=Owner",AccountData[playerid][pName]);
            mysql_tquery(g_SQL, cQuery);
            for(new i = 0; i < DRAGON_COUNT; i++)
            {
                SetPlayerAttachedObject(playerid, 0 + i,
                    DragonToys[i][tModel], DragonToys[i][tBone],
                    DragonToys[i][toys_X], DragonToys[i][toys_Y], DragonToys[i][toys_Z],
                    DragonToys[i][toys_RX], DragonToys[i][toys_RY], DragonToys[i][toys_RZ],
                    DragonToys[i][toys_SX], DragonToys[i][toys_SY], DragonToys[i][toys_SZ]);
                
                pToysDragon[playerid][i][dModel] = DragonToys[i][tModel];
                pToysDragon[playerid][i][dBone] = DragonToys[i][tBone];
                pToysDragon[playerid][i][dStatus] = 1;
                pToysDragon[playerid][i][dX] = DragonToys[i][toys_X];
                pToysDragon[playerid][i][dY] = DragonToys[i][toys_Y];
                pToysDragon[playerid][i][dZ] = DragonToys[i][toys_Z];
                pToysDragon[playerid][i][dRX] = DragonToys[i][toys_RX];
                pToysDragon[playerid][i][dRY] = DragonToys[i][toys_RY];
                pToysDragon[playerid][i][dRZ] = DragonToys[i][toys_RZ];
                pToysDragon[playerid][i][dSX] = DragonToys[i][toys_SX];
                pToysDragon[playerid][i][dSY] = DragonToys[i][toys_SY];
                pToysDragon[playerid][i][dSZ] = DragonToys[i][toys_SZ];
            }
            AccountData[playerid][PurchasedDragonToy] = true;
            MySQL_SavePlayerDragonToys(playerid);
            SendClientMessage(playerid, -1, "{ffff00}===>> Toys Vip Dragon Set berhasil dipasang!");
        }
        case 1: // Sonic
        {
            new cQuery[256];
            mysql_format(g_SQL, cQuery, sizeof(cQuery),"INSERT INTO sonic_toys (Owner) VALUES ('%s') ON DUPLICATE KEY UPDATE Owner=Owner",AccountData[playerid][pName]);
            mysql_tquery(g_SQL, cQuery);
            for(new i = 0; i < SONIC_COUNT; i++)
            {
                SetPlayerAttachedObject(playerid, 0 + i,
                    SonicToys[i][tModel], SonicToys[i][tBone],
                    SonicToys[i][toys_X], SonicToys[i][toys_Y], SonicToys[i][toys_Z],
                    SonicToys[i][toys_RX], SonicToys[i][toys_RY], SonicToys[i][toys_RZ],
                    SonicToys[i][toys_SX], SonicToys[i][toys_SY], SonicToys[i][toys_SZ]);

                pToysSonic[playerid][i][sModel] = SonicToys[i][tModel];
                pToysSonic[playerid][i][sBone] = SonicToys[i][tBone];
                pToysSonic[playerid][i][sStatus] = 1;
                pToysSonic[playerid][i][sX] = SonicToys[i][toys_X];
                pToysSonic[playerid][i][sY] = SonicToys[i][toys_Y];
                pToysSonic[playerid][i][sZ] = SonicToys[i][toys_Z];
                pToysSonic[playerid][i][sRX] = SonicToys[i][toys_RX];
                pToysSonic[playerid][i][sRY] = SonicToys[i][toys_RY];
                pToysSonic[playerid][i][sRZ] = SonicToys[i][toys_RZ];
                pToysSonic[playerid][i][sSX] = SonicToys[i][toys_SX];
                pToysSonic[playerid][i][sSY] = SonicToys[i][toys_SY];
                pToysSonic[playerid][i][sSZ] = SonicToys[i][toys_SZ];
            }
            AccountData[playerid][PurchasedSonicToy] = true;
            MySQL_SavePlayerSonicToys(playerid);
            SendClientMessage(playerid, -1, "{ffff00}===>> Toys Vip Sonic Set berhasil dipasang!");
        }
        case 2: // Grinch
        {
            new cQuery[256];
            mysql_format(g_SQL, cQuery, sizeof(cQuery),"INSERT INTO grinch_toys (Owner) VALUES ('%s') ON DUPLICATE KEY UPDATE Owner=Owner",AccountData[playerid][pName]);
            mysql_tquery(g_SQL, cQuery);
            for(new i = 0; i < GRINCH_COUNT; i++)
            {
                SetPlayerAttachedObject(playerid, 0 + i,
                    GrinchToys[i][tModel], GrinchToys[i][tBone],
                    GrinchToys[i][toys_X], GrinchToys[i][toys_Y], GrinchToys[i][toys_Z],
                    GrinchToys[i][toys_RX], GrinchToys[i][toys_RY], GrinchToys[i][toys_RZ],
                    GrinchToys[i][toys_SX], GrinchToys[i][toys_SY], GrinchToys[i][toys_SZ]);
                
                pToysGrinch[playerid][i][gModel] = GrinchToys[i][tModel];
                pToysGrinch[playerid][i][gBone] = GrinchToys[i][tBone];
                pToysGrinch[playerid][i][gStatus] = 1;
                pToysGrinch[playerid][i][gX] = GrinchToys[i][toys_X];
                pToysGrinch[playerid][i][gY] = GrinchToys[i][toys_Y];
                pToysGrinch[playerid][i][gZ] = GrinchToys[i][toys_Z];
                pToysGrinch[playerid][i][gRX] = GrinchToys[i][toys_RX];
                pToysGrinch[playerid][i][gRY] = GrinchToys[i][toys_RY];
                pToysGrinch[playerid][i][gRZ] = GrinchToys[i][toys_RZ];
                pToysGrinch[playerid][i][gSX] = GrinchToys[i][toys_SX];
                pToysGrinch[playerid][i][gSY] = GrinchToys[i][toys_SY];
                pToysGrinch[playerid][i][gSZ] = GrinchToys[i][toys_SZ];
            }
            AccountData[playerid][PurchasedGrinchToy] = true;
            MySQL_SavePlayerGrinchToys(playerid);
            SendClientMessage(playerid, -1, "{ffff00}===>> Toys Vip Grinch Set berhasil dipasang!");
        }
        case 3: // Ghost
        {
            new cQuery[256];
            mysql_format(g_SQL, cQuery, sizeof(cQuery),"INSERT INTO ghost_toys (Owner) VALUES ('%s') ON DUPLICATE KEY UPDATE Owner=Owner",AccountData[playerid][pName]);
            mysql_tquery(g_SQL, cQuery);
            for(new i = 0; i < GHOST_COUNT; i++)
            {
                SetPlayerAttachedObject(playerid, 0 + i,
                    GhostToys[i][tModel], GhostToys[i][tBone],
                    GhostToys[i][toys_X], GhostToys[i][toys_Y], GhostToys[i][toys_Z],
                    GhostToys[i][toys_RX], GhostToys[i][toys_RY], GhostToys[i][toys_RZ],
                    GhostToys[i][toys_SX], GhostToys[i][toys_SY], GhostToys[i][toys_SZ]);
                
                pToysGhost[playerid][i][gsModel] = GhostToys[i][tModel];
                pToysGhost[playerid][i][gsBone] = GhostToys[i][tBone];
                pToysGhost[playerid][i][gsStatus] = 1;
                pToysGhost[playerid][i][gsX] = GhostToys[i][toys_X];
                pToysGhost[playerid][i][gsY] = GhostToys[i][toys_Y];
                pToysGhost[playerid][i][gsZ] = GhostToys[i][toys_Z];
                pToysGhost[playerid][i][gsRX] = GhostToys[i][toys_RX];
                pToysGhost[playerid][i][gsRY] = GhostToys[i][toys_RY];
                pToysGhost[playerid][i][gsRZ] = GhostToys[i][toys_RZ];
                pToysGhost[playerid][i][gsSX] = GhostToys[i][toys_SX];
                pToysGhost[playerid][i][gsSY] = GhostToys[i][toys_SY];
                pToysGhost[playerid][i][gsSZ] = GhostToys[i][toys_SZ];
            }
            AccountData[playerid][PurchasedGhostToy] = true;
            MySQL_SavePlayerGhostToys(playerid);
            SendClientMessage(playerid, -1, "{ffff00}===>> Toys Vip Ghost Set berhasil dipasang!");
        }
    }
    return 1;
}


CMD:axp(playerid, params[])
{
    if(AccountData[playerid][pVip] < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pengguna VIP!");
    Dialog_Show(playerid, DIALOG_TOYSPREM, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Menu Toys", 
        "Kepala\nMasker\nTangan\nDada/Neck\nBahu/Pundak\nPunggung/Tas\n{E91E1E}Remove All Toys", 
        "Pilih", "Batal");
    return 1;
}

CMD:toysaxp(playerid, params[])
{
    if(AccountData[playerid][pVip] < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pengguna VIP!");
    Dialog_Show(playerid, DIALOG_TOYSPREM2, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Toys Vip",
        "Dragon/Naga\nKepla Sonic\nGrinch\nGhost/Hantu",
        "Pilih", "Batal");
    return 1;
}

CMD:dtoys(playerid, params[])
{
    if(AccountData[playerid][pVip] < 2) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan pengguna VIP!");
    Dialog_Show(playerid, DialogRemoveToys, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Remove Toys Vip",
        "Dragon/Naga\nKepla Sonic\nGrinch\nGhost/Hantu",
        "Pilih", "Batal");
    return 1;
}

// === Handler Dialog ===
Dialog:DIALOG_TOYSPREM(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    switch(listitem)
    {
        case 0: // Kepala
        {
            Dialog_Show(playerid, DIALOG_TOYSPREM3, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Toys Kepala",
            "Piring Kuning\nTopi Pesulap\nTopi Pesulap-2\nTopi Burger\nPelindung Tinju\nTopi Petani\nTopi Penyihir\nHelm Pembangun\nHelm Pink\nHelm Merah\nHelm 1 Warna\
            \nHelm Merah Putih\nTopi Santa\nKepala Ayam\nTopi Polisi\nLabu\nTopi Polisi Cowboy\nKepala Rusa\nTopeng Banteng\nKepala Zombie\nTopi\nHot Dog\nTopi Emas\
            \nTopi Kue\nTopi Pizza\nTopi Rocket\nBaret Merah\nTopi Merah\nHelm SWAT", 
            "Pilih", "Batal");
        }
        case 1: // masker
        {
            Dialog_Show(playerid, DIALOG_TOYSPREM4, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Toys Masker", 
            "Kepala CJ\nTopeng Setan\nAlat Pernafasan\nNVG\nMasker Medis\nJenggot\nTelinga Batman\
            \nTanduk\nKumis\nTopeng Hoki\nTopeng Monyet", 
            "Pilih", "Batal");
        }
        case 2: // tangan
        {
            Dialog_Show(playerid, DIALOG_TOYSPREM5, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Toys Tangan",
            "Remote R/C\nPerisai Abu Abu\nLightSaber (Orange)\nLightSaber (Ungu)\nLightSaber (Kuning)\
            \nLightSaber (Biru)\nLightSaber (Hijau)\nLightSaber (Merah)\nKapak Panjang\nTas Dengan Hati\nJerami",
            "Pilih", "Batal");
        }
        case 3: // dada
        {
            Dialog_Show(playerid, DIALOG_TOYSPREM6, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Toys Neck", 
            "Dolar\nLove (B)\nLove (M)\nKamera\nSilang\nKaleng\nPanah", 
            "Pilih", "Batal");
        }
        case 4: // Pundak
        {
            Dialog_Show(playerid, DIALOG_TOYSPREM7, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Toys Pundak", 
            "Burung\nAyam\nUFO\nBalon (1)\nBalon (2)\nBalon (3)\nBalon (4)\nBalon (5)\nBalon (6)\nBalon (7)\
            \nRusa\nBigSmoke\nPohon Natal (Besar)\nPohon Natal (Kecil)", 
            "Pilih", "Batal");
        }
        case 5: // backpack/punggung
        {
            Dialog_Show(playerid, DIALOG_TOYSPREM8, DIALOG_STYLE_LIST, ""TCRP"District "WHITE"- Toys Punggung/Tas",
            "Skop\nDolar\nPaket Ilegal\nKotak Kayu\nSekantong Daging\nAir Mancur\nTameng\nKatana\nPedang\
            \nMini Gun\nPenyebur Api\nGergaji\nTongkat\nSayap Lampu\nJubah Emas\nPenyu\nGadis\nRansel (Sabun)\
            \nTongkat Kakek\nPenghalang Jalan\nGitar (Merah)\nGitar (Putih)\nGitar (Hitam)\nTongkat BaseBall\nKado\
            \nSayap (1)\nSayap (2)\nDildo\nBoombox\nSkateBoard\nPapan Luncur (1)\nPapan Luncur (2)\nPapan Luncur (3)\nRadio\
            \nLaba-Laba\nRansel (Kuda nill)\nAlat Pemadam Api\nSapu\nTongkat Berduri\nPermen Hati\nTas Pisang\nLumba-Lumba",
            "Pilih", "Batal");
        }
        case 6: // Hapus Semua Toys
        {
            RemoveFSToys(playerid);
            Info(playerid, "Semua Toys berhasil di remove!");
        }
    }
    return 1;
}
Dialog:DIALOG_TOYSPREM3(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    // reset slot 0
    pToysAxp[playerid][0][toyaxp_model] = 0;
    pToysAxp[playerid][0][toyaxp_bone] = 1;
    pToysAxp[playerid][0][toysaxp_toystype] = 0;
    pToysAxp[playerid][0][toyaxp_status] = 0;
    pToysAxp[playerid][0][toyaxp_x] = 0.0;
    pToysAxp[playerid][0][toyaxp_y] = 0.0;
    pToysAxp[playerid][0][toyaxp_z] = 0.0;
    pToysAxp[playerid][0][toyaxp_rx] = 0.0;
    pToysAxp[playerid][0][toyaxp_ry] = 0.0;
    pToysAxp[playerid][0][toyaxp_rz] = 0.0;
    pToysAxp[playerid][0][toyaxp_sx] = 1.0;
    pToysAxp[playerid][0][toyaxp_sy] = 1.0;
    pToysAxp[playerid][0][toyaxp_sz] = 1.0;

    // pasang head baru
    new toyid = listitem;
    SetPlayerAttachedObject(playerid, 0, 
        HeadToys[toyid][tModel], 
        HeadToys[toyid][tBone],
        HeadToys[toyid][toys_X], HeadToys[toyid][toys_Y], HeadToys[toyid][toys_Z],
        HeadToys[toyid][toys_RX], HeadToys[toyid][toys_RY], HeadToys[toyid][toys_RZ],
        HeadToys[toyid][toys_SX], HeadToys[toyid][toys_SY], HeadToys[toyid][toys_SZ]);

    // update array slot 0
    pToysAxp[playerid][0][toyaxp_model] = HeadToys[toyid][tModel];
    pToysAxp[playerid][0][toyaxp_bone] = HeadToys[toyid][tBone];
    pToysAxp[playerid][0][toysaxp_toystype] = TOYS_TYPE_HEAD;
    pToysAxp[playerid][0][toyaxp_status] = 1;
    pToysAxp[playerid][0][toyaxp_x] = HeadToys[toyid][toys_X];
    pToysAxp[playerid][0][toyaxp_y] = HeadToys[toyid][toys_Y];
    pToysAxp[playerid][0][toyaxp_z] = HeadToys[toyid][toys_Z];
    pToysAxp[playerid][0][toyaxp_rx] = HeadToys[toyid][toys_RX];
    pToysAxp[playerid][0][toyaxp_ry] = HeadToys[toyid][toys_RY];
    pToysAxp[playerid][0][toyaxp_rz] = HeadToys[toyid][toys_RZ];
    pToysAxp[playerid][0][toyaxp_sx] = HeadToys[toyid][toys_SX];
    pToysAxp[playerid][0][toyaxp_sy] = HeadToys[toyid][toys_SY];
    pToysAxp[playerid][0][toyaxp_sz] = HeadToys[toyid][toys_SZ];

    // cek dulu record di database
    new query[256];
    mysql_format(g_SQL, query, sizeof(query),"SELECT Owner FROM toys_axp WHERE Owner='%s'", AccountData[playerid][pName]);
    mysql_tquery(g_SQL, query, "OnCheckToysAxpExist");

    return 1;
}

forward OnCheckToysAxpExist(playerid, result[], affected, num_rows);
public OnCheckToysAxpExist(playerid, result[], affected, num_rows)
{
    new query[1024];
    num_rows = cache_num_rows();
    if(num_rows == 0) 
    {
        mysql_format(g_SQL, query, sizeof(query),"INSERT INTO toys_axp (Owner) VALUES ('%s')", AccountData[playerid][pName]);
        mysql_tquery(g_SQL, query);
    }
    MySQL_SavePlayerToysAxp(playerid);
    return 1;
}

Dialog:DIALOG_TOYSPREM4(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    // reset slot 1
    pToysAxp[playerid][1][toyaxp_model] = 0;
    pToysAxp[playerid][1][toyaxp_bone] = 1;
    pToysAxp[playerid][1][toysaxp_toystype] = 0;
    pToysAxp[playerid][1][toyaxp_status] = 0;
    pToysAxp[playerid][1][toyaxp_x] = 0.0;
    pToysAxp[playerid][1][toyaxp_y] = 0.0;
    pToysAxp[playerid][1][toyaxp_z] = 0.0;
    pToysAxp[playerid][1][toyaxp_rx] = 0.0;
    pToysAxp[playerid][1][toyaxp_ry] = 0.0;
    pToysAxp[playerid][1][toyaxp_rz] = 0.0;
    pToysAxp[playerid][1][toyaxp_sx] = 1.0;
    pToysAxp[playerid][1][toyaxp_sy] = 1.0;
    pToysAxp[playerid][1][toyaxp_sz] = 1.0;

    new toyid = listitem; // index dari MaskToys
    SetPlayerAttachedObject(playerid, 1, 
    MaskToys[toyid][tModel], 
    MaskToys[toyid][tBone],
    MaskToys[toyid][toys_X], MaskToys[toyid][toys_Y], MaskToys[toyid][toys_Z],
    MaskToys[toyid][toys_RX], MaskToys[toyid][toys_RY], MaskToys[toyid][toys_RZ],
    MaskToys[toyid][toys_SX], MaskToys[toyid][toys_SY], MaskToys[toyid][toys_SZ]);

    // update array slot 1
    pToysAxp[playerid][1][toyaxp_model] = MaskToys[toyid][tModel];
    pToysAxp[playerid][1][toyaxp_bone] = MaskToys[toyid][tBone];
    pToysAxp[playerid][1][toysaxp_toystype] = TOYS_TYPE_MASK;
    pToysAxp[playerid][1][toyaxp_status] = 1;
    pToysAxp[playerid][1][toyaxp_x] = MaskToys[toyid][toys_X];
    pToysAxp[playerid][1][toyaxp_y] = MaskToys[toyid][toys_Y];
    pToysAxp[playerid][1][toyaxp_z] = MaskToys[toyid][toys_Z];
    pToysAxp[playerid][1][toyaxp_rx] = MaskToys[toyid][toys_RX];
    pToysAxp[playerid][1][toyaxp_ry] = MaskToys[toyid][toys_RY];
    pToysAxp[playerid][1][toyaxp_rz] = MaskToys[toyid][toys_RZ];
    pToysAxp[playerid][1][toyaxp_sx] = MaskToys[toyid][toys_SX];
    pToysAxp[playerid][1][toyaxp_sy] = MaskToys[toyid][toys_SY];
    pToysAxp[playerid][1][toyaxp_sz] = MaskToys[toyid][toys_SZ];

    // cek dulu record di database
    new query[256];
    mysql_format(g_SQL, query, sizeof(query),"SELECT Owner FROM toys_axp WHERE Owner='%s'", AccountData[playerid][pName]);
    mysql_tquery(g_SQL, query, "OnCheckToysAxpExist");

    Info(playerid, " Toys Masker berhasil dipasang!");
        
    return 1;
}

Dialog:DIALOG_TOYSPREM5(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    // reset slot 2
    pToysAxp[playerid][2][toyaxp_model] = 0;
    pToysAxp[playerid][2][toyaxp_bone] = 1;
    pToysAxp[playerid][2][toysaxp_toystype] = 0;
    pToysAxp[playerid][2][toyaxp_status] = 0;
    pToysAxp[playerid][2][toyaxp_x] = 0.0;
    pToysAxp[playerid][2][toyaxp_y] = 0.0;
    pToysAxp[playerid][2][toyaxp_z] = 0.0;
    pToysAxp[playerid][2][toyaxp_rx] = 0.0;
    pToysAxp[playerid][2][toyaxp_ry] = 0.0;
    pToysAxp[playerid][2][toyaxp_rz] = 0.0;
    pToysAxp[playerid][2][toyaxp_sx] = 1.0;
    pToysAxp[playerid][2][toyaxp_sy] = 1.0;
    pToysAxp[playerid][2][toyaxp_sz] = 1.0;

    new toyid = listitem; // index dari HandToys
    SetPlayerAttachedObject(playerid, 2, 
    HandToys[toyid][tModel], 
    HandToys[toyid][tBone],
    HandToys[toyid][toys_X], HandToys[toyid][toys_Y], HandToys[toyid][toys_Z],
    HandToys[toyid][toys_RX], HandToys[toyid][toys_RY], HandToys[toyid][toys_RZ],
    HandToys[toyid][toys_SX], HandToys[toyid][toys_SY], HandToys[toyid][toys_SZ]);

    // update array slot 2
    pToysAxp[playerid][2][toyaxp_model] = HandToys[toyid][tModel];
    pToysAxp[playerid][2][toyaxp_bone] = HandToys[toyid][tBone];
    pToysAxp[playerid][2][toysaxp_toystype] = TOYS_TYPE_HAND;
    pToysAxp[playerid][2][toyaxp_status] = 1;
    pToysAxp[playerid][2][toyaxp_x] = HandToys[toyid][toys_X];
    pToysAxp[playerid][2][toyaxp_y] = HandToys[toyid][toys_Y];
    pToysAxp[playerid][2][toyaxp_z] = HandToys[toyid][toys_Z];
    pToysAxp[playerid][2][toyaxp_rx] = HandToys[toyid][toys_RX];
    pToysAxp[playerid][2][toyaxp_ry] = HandToys[toyid][toys_RY];
    pToysAxp[playerid][2][toyaxp_rz] = HandToys[toyid][toys_RZ];
    pToysAxp[playerid][2][toyaxp_sx] = HandToys[toyid][toys_SX];
    pToysAxp[playerid][2][toyaxp_sy] = HandToys[toyid][toys_SY];
    pToysAxp[playerid][2][toyaxp_sz] = HandToys[toyid][toys_SZ];

    // cek dulu record di database
    new query[256];
    mysql_format(g_SQL, query, sizeof(query),"SELECT Owner FROM toys_axp WHERE Owner='%s'", AccountData[playerid][pName]);
    mysql_tquery(g_SQL, query, "OnCheckToysAxpExist");

    Info(playerid, " Toys Tangan berhasil dipasang!");
        
    return 1;
}

Dialog:DIALOG_TOYSPREM6(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    // reset slot 3
    pToysAxp[playerid][3][toyaxp_model] = 0;
    pToysAxp[playerid][3][toyaxp_bone] = 1;
    pToysAxp[playerid][3][toysaxp_toystype] = 0;
    pToysAxp[playerid][3][toyaxp_status] = 0;
    pToysAxp[playerid][3][toyaxp_x] = 0.0;
    pToysAxp[playerid][3][toyaxp_y] = 0.0;
    pToysAxp[playerid][3][toyaxp_z] = 0.0;
    pToysAxp[playerid][3][toyaxp_rx] = 0.0;
    pToysAxp[playerid][3][toyaxp_ry] = 0.0;
    pToysAxp[playerid][3][toyaxp_rz] = 0.0;
    pToysAxp[playerid][3][toyaxp_sx] = 1.0;
    pToysAxp[playerid][3][toyaxp_sy] = 1.0;
    pToysAxp[playerid][3][toyaxp_sz] = 1.0;

    new toyid = listitem; // index dari NeckToys
    SetPlayerAttachedObject(playerid, 3, 
    NeckToys[toyid][tModel], 
    NeckToys[toyid][tBone],
    NeckToys[toyid][toys_X], NeckToys[toyid][toys_Y], NeckToys[toyid][toys_Z],
    NeckToys[toyid][toys_RX], NeckToys[toyid][toys_RY], NeckToys[toyid][toys_RZ],
    NeckToys[toyid][toys_SX], NeckToys[toyid][toys_SY], NeckToys[toyid][toys_SZ]);

    // update array slot 3
    pToysAxp[playerid][3][toyaxp_model] = NeckToys[toyid][tModel];
    pToysAxp[playerid][3][toyaxp_bone] = NeckToys[toyid][tBone];
    pToysAxp[playerid][3][toysaxp_toystype] = TOYS_TYPE_NECK;
    pToysAxp[playerid][3][toyaxp_status] = 1;
    pToysAxp[playerid][3][toyaxp_x] = NeckToys[toyid][toys_X];
    pToysAxp[playerid][3][toyaxp_y] = NeckToys[toyid][toys_Y];
    pToysAxp[playerid][3][toyaxp_z] = NeckToys[toyid][toys_Z];
    pToysAxp[playerid][3][toyaxp_rx] = NeckToys[toyid][toys_RX];
    pToysAxp[playerid][3][toyaxp_ry] = NeckToys[toyid][toys_RY];
    pToysAxp[playerid][3][toyaxp_rz] = NeckToys[toyid][toys_RZ];
    pToysAxp[playerid][3][toyaxp_sx] = NeckToys[toyid][toys_SX];
    pToysAxp[playerid][3][toyaxp_sy] = NeckToys[toyid][toys_SY];
    pToysAxp[playerid][3][toyaxp_sz] = NeckToys[toyid][toys_SZ];

    // cek dulu record di database
    new query[256];
    mysql_format(g_SQL, query, sizeof(query),"SELECT Owner FROM toys_axp WHERE Owner='%s'", AccountData[playerid][pName]);
    mysql_tquery(g_SQL, query, "OnCheckToysAxpExist");

    Info(playerid, " Toys Dada berhasil dipasang!");
        
    return 1;
}

Dialog:DIALOG_TOYSPREM7(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    // reset slot 4
    pToysAxp[playerid][4][toyaxp_model] = 0;
    pToysAxp[playerid][4][toyaxp_bone] = 1;
    pToysAxp[playerid][4][toysaxp_toystype] = 0;
    pToysAxp[playerid][4][toyaxp_status] = 0;
    pToysAxp[playerid][4][toyaxp_x] = 0.0;
    pToysAxp[playerid][4][toyaxp_y] = 0.0;
    pToysAxp[playerid][4][toyaxp_z] = 0.0;
    pToysAxp[playerid][4][toyaxp_rx] = 0.0;
    pToysAxp[playerid][4][toyaxp_ry] = 0.0;
    pToysAxp[playerid][4][toyaxp_rz] = 0.0;
    pToysAxp[playerid][4][toyaxp_sx] = 1.0;
    pToysAxp[playerid][4][toyaxp_sy] = 1.0;
    pToysAxp[playerid][4][toyaxp_sz] = 1.0;

    new toyid = listitem; // index dari PundakToys
    SetPlayerAttachedObject(playerid, 4, 
    PundakToys[toyid][tModel], 
    PundakToys[toyid][tBone],
    PundakToys[toyid][toys_X], PundakToys[toyid][toys_Y], PundakToys[toyid][toys_Z],
    PundakToys[toyid][toys_RX], PundakToys[toyid][toys_RY], PundakToys[toyid][toys_RZ],
    PundakToys[toyid][toys_SX], PundakToys[toyid][toys_SY], PundakToys[toyid][toys_SZ]);

    // update array slot 4
    pToysAxp[playerid][4][toyaxp_model] = PundakToys[toyid][tModel];
    pToysAxp[playerid][4][toyaxp_bone] = PundakToys[toyid][tBone];
    pToysAxp[playerid][4][toysaxp_toystype] = TOYS_TYPE_PUNDAK;
    pToysAxp[playerid][4][toyaxp_status] = 1;
    pToysAxp[playerid][4][toyaxp_x] = PundakToys[toyid][toys_X];
    pToysAxp[playerid][4][toyaxp_y] = PundakToys[toyid][toys_Y];
    pToysAxp[playerid][4][toyaxp_z] = PundakToys[toyid][toys_Z];
    pToysAxp[playerid][4][toyaxp_rx] = PundakToys[toyid][toys_RX];
    pToysAxp[playerid][4][toyaxp_ry] = PundakToys[toyid][toys_RY];
    pToysAxp[playerid][4][toyaxp_rz] = PundakToys[toyid][toys_RZ];
    pToysAxp[playerid][4][toyaxp_sx] = PundakToys[toyid][toys_SX];
    pToysAxp[playerid][4][toyaxp_sy] = PundakToys[toyid][toys_SY];
    pToysAxp[playerid][4][toyaxp_sz] = PundakToys[toyid][toys_SZ];

    // cek dulu record di database
    new query[256];
    mysql_format(g_SQL, query, sizeof(query),"SELECT Owner FROM toys_axp WHERE Owner='%s'", AccountData[playerid][pName]);
    mysql_tquery(g_SQL, query, "OnCheckToysAxpExist");

    Info(playerid, " Toys Pundak berhasil dipasang!");
        
    return 1;
}

Dialog:DIALOG_TOYSPREM8(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    // reset slot 5
    pToysAxp[playerid][5][toyaxp_model] = 0;
    pToysAxp[playerid][5][toyaxp_bone] = 1;
    pToysAxp[playerid][5][toysaxp_toystype] = 0;
    pToysAxp[playerid][5][toyaxp_status] = 0;
    pToysAxp[playerid][5][toyaxp_x] = 0.0;
    pToysAxp[playerid][5][toyaxp_y] = 0.0;
    pToysAxp[playerid][5][toyaxp_z] = 0.0;
    pToysAxp[playerid][5][toyaxp_rx] = 0.0;
    pToysAxp[playerid][5][toyaxp_ry] = 0.0;
    pToysAxp[playerid][5][toyaxp_rz] = 0.0;
    pToysAxp[playerid][5][toyaxp_sx] = 1.0;
    pToysAxp[playerid][5][toyaxp_sy] = 1.0;
    pToysAxp[playerid][5][toyaxp_sz] = 1.0;

    new toyid = listitem; // index dari BackpToys
    SetPlayerAttachedObject(playerid, 5, 
    BackpToys[toyid][tModel], 
    BackpToys[toyid][tBone],
    BackpToys[toyid][toys_X], BackpToys[toyid][toys_Y], BackpToys[toyid][toys_Z],
    BackpToys[toyid][toys_RX], BackpToys[toyid][toys_RY], BackpToys[toyid][toys_RZ],
    BackpToys[toyid][toys_SX], BackpToys[toyid][toys_SY], BackpToys[toyid][toys_SZ]);

    // update array slot 5
    pToysAxp[playerid][5][toyaxp_model] = BackpToys[toyid][tModel];
    pToysAxp[playerid][5][toyaxp_bone] = BackpToys[toyid][tBone];
    pToysAxp[playerid][5][toysaxp_toystype] = TOYS_TYPE_BACKPACK;
    pToysAxp[playerid][5][toyaxp_status] = 1;
    pToysAxp[playerid][5][toyaxp_x] = BackpToys[toyid][toys_X];
    pToysAxp[playerid][5][toyaxp_y] = BackpToys[toyid][toys_Y];
    pToysAxp[playerid][5][toyaxp_z] = BackpToys[toyid][toys_Z];
    pToysAxp[playerid][5][toyaxp_rx] = BackpToys[toyid][toys_RX];
    pToysAxp[playerid][5][toyaxp_ry] = BackpToys[toyid][toys_RY];
    pToysAxp[playerid][5][toyaxp_rz] = BackpToys[toyid][toys_RZ];
    pToysAxp[playerid][5][toyaxp_sx] = BackpToys[toyid][toys_SX];
    pToysAxp[playerid][5][toyaxp_sy] = BackpToys[toyid][toys_SY];
    pToysAxp[playerid][5][toyaxp_sz] = BackpToys[toyid][toys_SZ];

    // cek dulu record di database
    new query[256];
    mysql_format(g_SQL, query, sizeof(query),"SELECT Owner FROM toys_axp WHERE Owner='%s'", AccountData[playerid][pName]);
    mysql_tquery(g_SQL, query, "OnCheckToysAxpExist");

    Info(playerid, " Toys Punggung berhasil dipasang!");
        
    return 1;
}

Dialog:DIALOG_TOYSPREM2(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    ApplyToySet(playerid, listitem);
    return 1;
}
Dialog:DialogRemoveToys(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    RemoveFSToysPremium(playerid, listitem);
        
    return 1;
}