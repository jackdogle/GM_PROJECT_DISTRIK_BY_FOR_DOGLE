#include <YSI\y_hooks>
//Business
#define MAX_DYNAMIC_BISNIS 1000

enum bisinfo
{
	bOwner[MAX_PLAYER_NAME],
	bName[128],
	bPrice,
	bType,
	bLocked,
	bMoney,
	bProd,
	bP[12],
	bInt,
	Float:bExtposX,
	Float:bExtposY,
	Float:bExtposZ,
	Float:bExtposA,
	Float:bIntposX,
	Float:bIntposY,
	Float:bIntposZ,
	Float:bIntposA,
	bVisit,
	bRestock,
	Float:bPointX,
	Float:bPointY,
	Float:bPointZ,
	bPName0[128],
	bPName1[128],
	bPName2[128],
	bPName3[128],
	bPName4[128],
	bPName5[128],
	bPName6[128],
	bPName7[128],
	bPName8[128],
	bPName9[128],
	bPName10[128],
	bStream[128],
	bExtInt,
	bExtVw,
	//Not Saved
	STREAMER_TAG_PICKUP:bPickPoint,
	STREAMER_TAG_3D_TEXT_LABEL:bLabelPoint,
	STREAMER_TAG_PICKUP:bPickup,
	STREAMER_TAG_3D_TEXT_LABEL:bLabel,
	BiznisID
};

new BisnisData[MAX_DYNAMIC_BISNIS][bisinfo],
	Iterator: Bisnis<MAX_DYNAMIC_BISNIS>;

Bisnis_Save(id)
{
	new cQuery[2248];
	format(cQuery, sizeof(cQuery), "UPDATE bisnis SET owner='%s', name='%s', price='%d', type='%d', locked='%d', money='%d', prod='%d', bprice0='%d', bprice1='%d', bprice2='%d', bprice3='%d', bprice4='%d', bprice5='%d', bprice6='%d', bprice7='%d', bprice8='%d', bprice9='%d', bprice10='%d', bint='%d', extposx='%f', extposy='%f', extposz='%f', extposa='%f', intposx='%f', intposy='%f', intposz='%f', intposa='%f', pointx='%f', pointy='%f', pointz='%f', visit='%d', restock='%d', bpname0='%s', bpname1='%s', bpname2='%s', bpname3='%s', bpname4='%s', bpname5='%s', bpname6='%s', bpname7='%s', bpname8='%s', bpname9='%s', bpname10='%s', stream='%s', extvw='%d', extint='%d' WHERE ID='%d'",
	BisnisData[id][bOwner],
	BisnisData[id][bName],
	BisnisData[id][bPrice],
	BisnisData[id][bType],
	BisnisData[id][bLocked],
	BisnisData[id][bMoney],
	BisnisData[id][bProd],
	BisnisData[id][bP][0],
	BisnisData[id][bP][1],
	BisnisData[id][bP][2],
	BisnisData[id][bP][3],
	BisnisData[id][bP][4],
	BisnisData[id][bP][5],
	BisnisData[id][bP][6],
	BisnisData[id][bP][7],
	BisnisData[id][bP][8],
	BisnisData[id][bP][9],
	BisnisData[id][bP][10],
	BisnisData[id][bInt],
	BisnisData[id][bExtposX],
	BisnisData[id][bExtposY],
	BisnisData[id][bExtposZ],
	BisnisData[id][bExtposA],
	BisnisData[id][bIntposX],
	BisnisData[id][bIntposY],
	BisnisData[id][bIntposZ],
	BisnisData[id][bIntposA],
	BisnisData[id][bPointX],
	BisnisData[id][bPointY],
	BisnisData[id][bPointZ],
	BisnisData[id][bVisit],
	BisnisData[id][bRestock],
	BisnisData[id][bPName0],
	BisnisData[id][bPName1],
	BisnisData[id][bPName2],
	BisnisData[id][bPName3],
	BisnisData[id][bPName4],
	BisnisData[id][bPName5],
	BisnisData[id][bPName6],
	BisnisData[id][bPName7],
	BisnisData[id][bPName8],
	BisnisData[id][bPName9],
	BisnisData[id][bPName10],
	BisnisData[id][bStream],
	BisnisData[id][bExtVw],
	BisnisData[id][bExtInt],
	id
	);
	return mysql_tquery(g_SQL, cQuery);
}
	
Player_OwnsBisnis(playerid, id)
{
	if(!IsPlayerConnected(playerid)) return 0;
	if(id == -1) return 0;
	if(!strcmp(BisnisData[id][bOwner], AccountData[playerid][pName], true)) return 1;
	return 0;
}

Bisnis_Reset(id)
{
	format(BisnisData[id][bOwner], MAX_PLAYER_NAME, "-");
	BisnisData[id][bLocked] = 1;
    BisnisData[id][bMoney] = 0;
	BisnisData[id][bProd] = 0;
	BisnisData[id][bVisit] = 0;
	BisnisData[id][bRestock] = 0;
	Bisnis_Refresh(id);
}

GetOwnedBisnis(playerid)
{
	new tmpcount;
	foreach(new bid : Bisnis)
	{
	    if(!strcmp(BisnisData[bid][bOwner], AccountData[playerid][pName], true))
	    {
     		tmpcount++;
		}
	}
	return tmpcount;
}

ReturnPlayerBisnisID(playerid, hslot)
{
	new tmpcount;
	if(hslot < 1 && hslot > 2) return -1;
	foreach(new bid : Bisnis)
	{
	    if(!strcmp(AccountData[playerid][pName], BisnisData[bid][bOwner], true))
	    {
     		tmpcount++;
       		if(tmpcount == hslot)
       		{
        		return bid;
  			}
	    }
	}
	return -1;
}

Bisnis_BuyMenu(playerid, bizid)
{
    if(bizid <= -1 )
        return 0;

    static
        string[512];

    switch(BisnisData[bizid][bType])
    {
		case 1:
        {
            format(string, sizeof(string), "%s (Menu +12)  - $%s\n%s (Menu +45)  - $%s\n%s (Menu +60)  - $%s\n%s (Energy Drink) - $%s",
                BisnisData[bizid][bPName0],
				FormatMoney(BisnisData[bizid][bP][0]),
				BisnisData[bizid][bPName1],
                FormatMoney(BisnisData[bizid][bP][1]),
				BisnisData[bizid][bPName2],
                FormatMoney(BisnisData[bizid][bP][2]),
				BisnisData[bizid][bPName3],
                FormatMoney(BisnisData[bizid][bP][3])
            );
            ShowPlayerDialog(playerid, BISNIS_BUYPROD, DIALOG_STYLE_LIST, BisnisData[bizid][bName], string, "Buy", "Cancel");
        }
        case 2:
        {
            format(string, sizeof(string), "%s (Snack) - $%s\n%s (Water) - $%s\n%s (Bandage) - $%s\n%s (Pack of Cigaretes) - $%s\n%s (Toll Card (50)) - $%s",
                BisnisData[bizid][bPName0],
				FormatMoney(BisnisData[bizid][bP][0]),
				BisnisData[bizid][bPName1],
                FormatMoney(BisnisData[bizid][bP][1]),
				BisnisData[bizid][bPName2],
                FormatMoney(BisnisData[bizid][bP][2]),
				BisnisData[bizid][bPName3],
                FormatMoney(BisnisData[bizid][bP][3]),
				BisnisData[bizid][bPName4],
				FormatMoney(BisnisData[bizid][bP][4])
            );
            ShowPlayerDialog(playerid, BISNIS_BUYPROD, DIALOG_STYLE_LIST, BisnisData[bizid][bName], string, "Buy", "Cancel");
        }
        case 3:
        {
            format(string, sizeof(string), "%s (Clothes) - $%s\n%s (Caps) - $%s\n%s (Bandana) - $%s\n%s (Mask) - $%s\n%s (Helmet) - $%s\n%s (Watch) - $%s\n%s (Glasses) - $%s\n%s (Hair) - $%s\n%s (Misc) - $%s",
                BisnisData[bizid][bPName0],
				FormatMoney(BisnisData[bizid][bP][0]),
				BisnisData[bizid][bPName1],
                FormatMoney(BisnisData[bizid][bP][1]),
				BisnisData[bizid][bPName2],
                FormatMoney(BisnisData[bizid][bP][2]),
				BisnisData[bizid][bPName3],
                FormatMoney(BisnisData[bizid][bP][3]),
				BisnisData[bizid][bPName4],
                FormatMoney(BisnisData[bizid][bP][4]),
				BisnisData[bizid][bPName5],
                FormatMoney(BisnisData[bizid][bP][5]),
				BisnisData[bizid][bPName6],
                FormatMoney(BisnisData[bizid][bP][6])
            );
            ShowPlayerDialog(playerid, BISNIS_BUYPROD, DIALOG_STYLE_LIST, BisnisData[bizid][bName], string, "Buy", "Cancel");
        }
        case 4:
        {
            format(string, sizeof(string), "%s (Baseball bat) - $%s\n%s (Shovel) - $%s\n%s (Cane) - $%s\n%s (Fish Tool)- $%s\n%s (Mask)- $%s",
                BisnisData[bizid][bPName0],
				FormatMoney(BisnisData[bizid][bP][0]),
				BisnisData[bizid][bPName1],
                FormatMoney(BisnisData[bizid][bP][1]),
				BisnisData[bizid][bPName2],
                FormatMoney(BisnisData[bizid][bP][2]),
				BisnisData[bizid][bPName3],
                FormatMoney(BisnisData[bizid][bP][3]),
				BisnisData[bizid][bPName4],
                FormatMoney(BisnisData[bizid][bP][4])
            );
            ShowPlayerDialog(playerid, BISNIS_BUYPROD, DIALOG_STYLE_LIST, BisnisData[bizid][bName], string, "Buy", "Cancel");
        }
		case 5:
        {
            format(string, sizeof(string), "%s (Handphone) - $%s\n%s (GPS) - $%s\n%s (Phone Credit (1000)) - $%s\n%s (Walkie Talkie)- $%s",
                BisnisData[bizid][bPName0],
				FormatMoney(BisnisData[bizid][bP][0]),
				BisnisData[bizid][bPName1],
                FormatMoney(BisnisData[bizid][bP][1]),
				BisnisData[bizid][bPName2],
                FormatMoney(BisnisData[bizid][bP][2]),
				BisnisData[bizid][bPName3],
                FormatMoney(BisnisData[bizid][bP][3])
            );
            ShowPlayerDialog(playerid, BISNIS_BUYPROD, DIALOG_STYLE_LIST, BisnisData[bizid][bName], string, "Buy", "Cancel");
        }
    }
    return 1;
}

Bisnis_ProductMenu(playerid, bizid)
{
    if(bizid <= -1)
        return 0;

    static
        string[512];

    switch (BisnisData[bizid][bType])
    {
        case 1:
        {
            format(string, sizeof(string), "%s (Menu +12)  - $%s\n%s (Menu +45)  - $%s\n%s (Menu +60)  - $%s\n%s (Energy Drink) - $%s",
                BisnisData[bizid][bPName0],
				FormatMoney(BisnisData[bizid][bP][0]),
				BisnisData[bizid][bPName1],
                FormatMoney(BisnisData[bizid][bP][1]),
				BisnisData[bizid][bPName2],
                FormatMoney(BisnisData[bizid][bP][2]),
				BisnisData[bizid][bPName3],
                FormatMoney(BisnisData[bizid][bP][3])
            );
            ShowPlayerDialog(playerid, BISNIS_EDITPROD, DIALOG_STYLE_LIST, BisnisData[bizid][bName], string, "Buy", "Cancel");
        }
        case 2:
        {
            format(string, sizeof(string), "%s (Snack) - $%s\n%s (Water) - $%s\n%s (Bandage) - $%s\n%s (Pack of Cigaretes) - $%s\n%s (Toll Card (50)) - $%s",
                BisnisData[bizid][bPName0],
				FormatMoney(BisnisData[bizid][bP][0]),
				BisnisData[bizid][bPName1],
                FormatMoney(BisnisData[bizid][bP][1]),
				BisnisData[bizid][bPName2],
                FormatMoney(BisnisData[bizid][bP][2]),
				BisnisData[bizid][bPName3],
                FormatMoney(BisnisData[bizid][bP][3]),
				BisnisData[bizid][bPName4],
				FormatMoney(BisnisData[bizid][bP][4])
            );
            ShowPlayerDialog(playerid, BISNIS_EDITPROD, DIALOG_STYLE_LIST, BisnisData[bizid][bName], string, "Buy", "Cancel");
        }
        case 3:
        {
            format(string, sizeof(string), "%s (Clothes) - $%s\n%s (Caps) - $%s\n%s (Bandana) - $%s\n%s (Mask) - $%s\n%s (Helmet) - $%s\n%s (Watch) - $%s\n%s (Glasses) - $%s\n%s (Hair) - $%s\n%s (Misc) - $%s",
                BisnisData[bizid][bPName0],
				FormatMoney(BisnisData[bizid][bP][0]),
				BisnisData[bizid][bPName1],
                FormatMoney(BisnisData[bizid][bP][1]),
				BisnisData[bizid][bPName2],
                FormatMoney(BisnisData[bizid][bP][2]),
				BisnisData[bizid][bPName3],
                FormatMoney(BisnisData[bizid][bP][3]),
				BisnisData[bizid][bPName4],
                FormatMoney(BisnisData[bizid][bP][4]),
				BisnisData[bizid][bPName5],
                FormatMoney(BisnisData[bizid][bP][5]),
				BisnisData[bizid][bPName6],
                FormatMoney(BisnisData[bizid][bP][6])
            );
            ShowPlayerDialog(playerid, BISNIS_BUYPROD, DIALOG_STYLE_LIST, BisnisData[bizid][bName], string, "Buy", "Cancel");
        }
        case 4:
        {
            format(string, sizeof(string), "%s (Baseball bat) - $%s\n%s (Shovel) - $%s\n%s (Cane) - $%s\n%s (Fish Tool)- $%s\n%s (Mask)- $%s",
                BisnisData[bizid][bPName0],
				FormatMoney(BisnisData[bizid][bP][0]),
				BisnisData[bizid][bPName1],
                FormatMoney(BisnisData[bizid][bP][1]),
				BisnisData[bizid][bPName2],
                FormatMoney(BisnisData[bizid][bP][2]),
				BisnisData[bizid][bPName3],
                FormatMoney(BisnisData[bizid][bP][3]),
				BisnisData[bizid][bPName4],
                FormatMoney(BisnisData[bizid][bP][4])
            );
            ShowPlayerDialog(playerid, BISNIS_EDITPROD, DIALOG_STYLE_LIST, BisnisData[bizid][bName], string, "Buy", "Cancel");
        }
		case 5:
        {
            format(string, sizeof(string), "%s (Handphone) - $%s\n%s (GPS) - $%s\n%s (Phone Credit (1000)) - $%s\n%s (Walkie Talkie)- $%s",
                BisnisData[bizid][bPName0],
				FormatMoney(BisnisData[bizid][bP][0]),
				BisnisData[bizid][bPName1],
                FormatMoney(BisnisData[bizid][bP][1]),
				BisnisData[bizid][bPName2],
                FormatMoney(BisnisData[bizid][bP][2]),
				BisnisData[bizid][bPName3],
                FormatMoney(BisnisData[bizid][bP][3])
            );
            ShowPlayerDialog(playerid, BISNIS_EDITPROD, DIALOG_STYLE_LIST, BisnisData[bizid][bName], string, "Buy", "Cancel");
        }
    }
    return 1;
}

Bisnis_ProductMenuName(playerid, bizid)
{
    if(bizid <= -1)
        return 0;

    static
        string[512];

    switch (BisnisData[bizid][bType])
    {
        case 1:
        {
            format(string, sizeof(string), "%s (Menu +12)  - $%s\n%s (Menu +45)  - $%s\n%s (Menu +60)  - $%s\n%s (Energy Drink) - $%s",
                BisnisData[bizid][bPName0],
				FormatMoney(BisnisData[bizid][bP][0]),
				BisnisData[bizid][bPName1],
                FormatMoney(BisnisData[bizid][bP][1]),
				BisnisData[bizid][bPName2],
                FormatMoney(BisnisData[bizid][bP][2]),
				BisnisData[bizid][bPName3],
                FormatMoney(BisnisData[bizid][bP][3])
            );
            ShowPlayerDialog(playerid, BISNIS_EDITPROD, DIALOG_STYLE_LIST, BisnisData[bizid][bName], string, "Buy", "Cancel");
        }
        case 2:
        {
            format(string, sizeof(string), "%s (Snack) - $%s\n%s (Water) - $%s\n%s (Bandage) - $%s\n%s (Pack of Cigaretes) - $%s\n%s (Toll Card (50)) - $%s",
                BisnisData[bizid][bPName0],
				FormatMoney(BisnisData[bizid][bP][0]),
				BisnisData[bizid][bPName1],
                FormatMoney(BisnisData[bizid][bP][1]),
				BisnisData[bizid][bPName2],
                FormatMoney(BisnisData[bizid][bP][2]),
				BisnisData[bizid][bPName3],
                FormatMoney(BisnisData[bizid][bP][3]),
				BisnisData[bizid][bPName4],
				FormatMoney(BisnisData[bizid][bP][4])
            );
            ShowPlayerDialog(playerid, BISNIS_EDITPROD, DIALOG_STYLE_LIST, BisnisData[bizid][bName], string, "Buy", "Cancel");
        }
        case 3:
        {
            format(string, sizeof(string), "%s (Clothes) - $%s\n%s (Caps) - $%s\n%s (Bandana) - $%s\n%s (Mask) - $%s\n%s (Helmet) - $%s\n%s (Watch) - $%s\n%s (Glasses) - $%s\n%s (Hair) - $%s\n%s (Misc) - $%s",
                BisnisData[bizid][bPName0],
				FormatMoney(BisnisData[bizid][bP][0]),
				BisnisData[bizid][bPName1],
                FormatMoney(BisnisData[bizid][bP][1]),
				BisnisData[bizid][bPName2],
                FormatMoney(BisnisData[bizid][bP][2]),
				BisnisData[bizid][bPName3],
                FormatMoney(BisnisData[bizid][bP][3]),
				BisnisData[bizid][bPName4],
                FormatMoney(BisnisData[bizid][bP][4]),
				BisnisData[bizid][bPName5],
                FormatMoney(BisnisData[bizid][bP][5]),
				BisnisData[bizid][bPName6],
                FormatMoney(BisnisData[bizid][bP][6])
            );
            ShowPlayerDialog(playerid, BISNIS_BUYPROD, DIALOG_STYLE_LIST, BisnisData[bizid][bName], string, "Buy", "Cancel");
        }
        case 4:
        {
            format(string, sizeof(string), "%s (Baseball bat) - $%s\n%s (Shovel) - $%s\n%s (Cane) - $%s\n%s (Fish Tool)- $%s\n%s (Mask)- $%s",
                BisnisData[bizid][bPName0],
				FormatMoney(BisnisData[bizid][bP][0]),
				BisnisData[bizid][bPName1],
                FormatMoney(BisnisData[bizid][bP][1]),
				BisnisData[bizid][bPName2],
                FormatMoney(BisnisData[bizid][bP][2]),
				BisnisData[bizid][bPName3],
                FormatMoney(BisnisData[bizid][bP][3]),
				BisnisData[bizid][bPName4],
                FormatMoney(BisnisData[bizid][bP][4])
            );
            ShowPlayerDialog(playerid, BISNIS_EDITPROD, DIALOG_STYLE_LIST, BisnisData[bizid][bName], string, "Buy", "Cancel");
        }
		case 5:
        {
            format(string, sizeof(string), "%s (Handphone) - $%s\n%s (GPS) - $%s\n%s (Phone Credit (1000)) - $%s\n%s (Walkie Talkie)- $%s",
                BisnisData[bizid][bPName0],
				FormatMoney(BisnisData[bizid][bP][0]),
				BisnisData[bizid][bPName1],
                FormatMoney(BisnisData[bizid][bP][1]),
				BisnisData[bizid][bPName2],
                FormatMoney(BisnisData[bizid][bP][2]),
				BisnisData[bizid][bPName3],
                FormatMoney(BisnisData[bizid][bP][3])
            );
            ShowPlayerDialog(playerid, BISNIS_EDITPROD, DIALOG_STYLE_LIST, BisnisData[bizid][bName], string, "Buy", "Cancel");
        }
    }
    return 1;
}

Bisnis_ProductNameRefresh(id)
{
    if(id != -1)
    {
		switch(BisnisData[id][bType])
		{
			case 1:
			{
				if(strcmp(BisnisData[id][bPName0], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName0], 128, "Fried Chicken(+25)");
				}
				if(strcmp(BisnisData[id][bPName1], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName1], 128, "Pizza Stack(+45)");
				}
				if(strcmp(BisnisData[id][bPName2], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName2], 128, "Patty Burger(+60)");
				}
				if(strcmp(BisnisData[id][bPName3], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName3], 128, "Sprunk(+45)");
				}
			}
			case 2:
			{
				if(strcmp(BisnisData[id][bPName0], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName0], 128, "Snack");
				}
				if(strcmp(BisnisData[id][bPName1], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName1], 128, "Sprunk");
				}
				if(strcmp(BisnisData[id][bPName2], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName2], 128, "Bandage");
				}
				if(strcmp(BisnisData[id][bPName3], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName3], 128, "Cigarretes");
				}
				if(strcmp(BisnisData[id][bPName4], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName4], 128, "Toll Card");
				}
			}	
			case 3:
			{
				if(strcmp(BisnisData[id][bPName0], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName0], 128, "Clothes");
				}
				if(strcmp(BisnisData[id][bPName1], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName1], 128, "Hats");
				}
				if(strcmp(BisnisData[id][bPName2], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName2], 128, "Glasses");
				}
				if(strcmp(BisnisData[id][bPName3], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName3], 128, "Helm");
				}
				if(strcmp(BisnisData[id][bPName4], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName4], 128, "Accessory");
				}
				if(strcmp(BisnisData[id][bPName5], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName5], 128, "Mask (Accessory)");
				}
				if(strcmp(BisnisData[id][bPName6], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName6], 128, "Hairs");
				}
			}
			case 4:
			{	
				if(strcmp(BisnisData[id][bPName0], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName0], 128, "Baseball Bat");
				}
				if(strcmp(BisnisData[id][bPName1], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName1], 128, "Shovel");
				}
				if(strcmp(BisnisData[id][bPName2], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName2], 128, "Cane");
				}
				if(strcmp(BisnisData[id][bPName3], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName3], 128, "Fishing Tools");
				}
				if(strcmp(BisnisData[id][bPName4], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName4], 128, "Mask");
				}
			}
			case 5:
			{	
				if(strcmp(BisnisData[id][bPName0], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName0], 128, "Handphone");
				}
				if(strcmp(BisnisData[id][bPName1], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName1], 128, "GPS");
				}
				if(strcmp(BisnisData[id][bPName2], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName2], 128, "Phone credit");
				}
				if(strcmp(BisnisData[id][bPName3], "-"))
				{
				}
				else
				{
					format(BisnisData[id][bPName3], 128, "Walkie talkie");
				}
			}
		}	
        
    }
    return 1;
}

Bisnis_Type(bisid)
{
	if(BisnisData[bisid][bType] == 1) // Fast Food
	{
	    switch(random(2))
		{
			case 0:
			{
				BisnisData[bisid][bIntposX] = 363.22;
				BisnisData[bisid][bIntposY] = -74.86;
				BisnisData[bisid][bIntposZ] = 1001.50;
				BisnisData[bisid][bIntposA] = 319.72;
				BisnisData[bisid][bInt] = 10;
				BisnisData[bisid][bPointX] = 376.8142;
				BisnisData[bisid][bPointY] = -68.0401;
				BisnisData[bisid][bPointZ] = 1001.5151;
			}
			case 1: // ,,
			{
				BisnisData[bisid][bIntposX] = 372.34;
				BisnisData[bisid][bIntposY] = -133.25;
				BisnisData[bisid][bIntposZ] = 1001.49;
				BisnisData[bisid][bIntposA] = 4.80;
				BisnisData[bisid][bInt] = 5;
				BisnisData[bisid][bPointX] = 375.4402;
				BisnisData[bisid][bPointY] = -119.9117;
				BisnisData[bisid][bPointZ] = 1001.4995;
			} 
		}
	}
	if(BisnisData[bisid][bType] == 2) //Market
	{
	    switch(random(2))
		{
			case 0: // 1.9983,-29.0117,1003.5494
			{
				BisnisData[bisid][bIntposX] = 5.73;
				BisnisData[bisid][bIntposY] = -31.04;
				BisnisData[bisid][bIntposZ] = 1003.54;
				BisnisData[bisid][bIntposA] = 355.73;
				BisnisData[bisid][bInt] = 10;
				BisnisData[bisid][bPointX] = 1.9983;
				BisnisData[bisid][bPointY] = -29.0117;
				BisnisData[bisid][bPointZ] = 1003.5494;
			}
			case 1: //-23.4406,-55.6324,1003.5469
			{
				BisnisData[bisid][bIntposX] = -26.68;
				BisnisData[bisid][bIntposY] = -57.92;
				BisnisData[bisid][bIntposZ] = 1003.54;
				BisnisData[bisid][bIntposA] = 357.58;
				BisnisData[bisid][bInt] = 6;
				BisnisData[bisid][bPointX] = -23.4406;
				BisnisData[bisid][bPointY] = -55.6324;
				BisnisData[bisid][bPointZ] = 1003.5469;
			}
		}
	}
	if(BisnisData[bisid][bType] == 3) //Clothes
	{
	    switch(random(2))
		{
			case 0: // 207.5234,-100.7358,1005.2578
			{
				BisnisData[bisid][bIntposX] = 207.55;
				BisnisData[bisid][bIntposY] = -110.67;
				BisnisData[bisid][bIntposZ] = 1005.13;
				BisnisData[bisid][bIntposA] = 0.16;
				BisnisData[bisid][bInt] = 15;
				BisnisData[bisid][bPointX] = 207.5234;
				BisnisData[bisid][bPointY] = -100.7358;
				BisnisData[bisid][bPointZ] = 1005.2578;
			}
			case 1: // 204.3724,-159.6976,1000.5234
			{
				BisnisData[bisid][bIntposX] = 204.49;
				BisnisData[bisid][bIntposY] = -168.26;
				BisnisData[bisid][bIntposZ] = 1000.52;
				BisnisData[bisid][bIntposA] = 358.74;
				BisnisData[bisid][bInt] = 14;
				BisnisData[bisid][bPointX] = 204.3724;
				BisnisData[bisid][bPointY] = -159.6976;
				BisnisData[bisid][bPointZ] = 1000.5234;
			}
		}
	}
	if(BisnisData[bisid][bType] == 4) // Sportshop
	{ //203.7197,-50.0292,1001.8047,5.1475
		BisnisData[bisid][bIntposX] = 203.7197;
		BisnisData[bisid][bIntposY] = -50.0292;
		BisnisData[bisid][bIntposZ] = 1001.8047;
		BisnisData[bisid][bIntposA] = 5.1475;
		BisnisData[bisid][bInt] = 1;
		BisnisData[bisid][bPointX] = 203.8431;
		BisnisData[bisid][bPointY] = -43.2778;
		BisnisData[bisid][bPointZ] = 1001.8047;
	}
	if(BisnisData[bisid][bType] == 5) // Electronic
	{ //-2240.468505,137.060440,1035.414062	
		BisnisData[bisid][bIntposX] = -2240.3938;
		BisnisData[bisid][bIntposY] = 137.3993;
		BisnisData[bisid][bIntposZ] = 1035.4141;
		BisnisData[bisid][bIntposA] = 270.2590;
		BisnisData[bisid][bInt] = 6;
		BisnisData[bisid][bPointX] = -2235.4143;
		BisnisData[bisid][bPointY] = 130.1577;
		BisnisData[bisid][bPointZ] = 1035.4141;
	}
}

Bisnis_Refresh(id)
{
    if(id != -1)
    {
        if(DestroyDynamic3DTextLabel(BisnisData[id][bLabel]))
            BisnisData[id][bLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        if(DestroyDynamicPickup(BisnisData[id][bPickup]))
            BisnisData[id][bPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
			
		if(DestroyDynamic3DTextLabel(BisnisData[id][bLabelPoint]))
            BisnisData[id][bLabelPoint] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;

        if(DestroyDynamicPickup(BisnisData[id][bPickPoint]))
            BisnisData[id][bPickPoint] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
	
        static
        string[255], tstr[128];
		
		new type[128];
		if(BisnisData[id][bType] == 1)
		{
			type= "Fast Food";
		}
		else if(BisnisData[id][bType] == 2)
		{
			type= "Market";
		}
		else if(BisnisData[id][bType] == 3)
		{
			type= "Clothes";
		}
		else if(BisnisData[id][bType] == 4)
		{
			type= "Toko Olahraga";
		}
		else if(BisnisData[id][bType] == 5)
		{
			type= "iBox Store";
		}
		else
		{
			type= "Unknow";
		}
        if(strcmp(BisnisData[id][bOwner], "-"))
		{
			format(string, sizeof(string), ""LIGHTGREY"[%s]\n"YELLOW"%s\n"WHITE"%s\nMarket\nBiaya Masuk $50\n%s", type, BisnisData[id][bName], BisnisData[id][bOwner], BisnisData[id][bLocked] == 1 ? ""RED"Tutup" : ""GREEN"Buka");
			BisnisData[id][bPickup] = CreateDynamicPickup(19133, 23, BisnisData[id][bExtposX], BisnisData[id][bExtposY], BisnisData[id][bExtposZ]+0.2, 0, 0, _, 8.0);
        }
        else
        {
			format(string, sizeof(string), ""LIGHTGREY"[%s]\n"YELLOW"Bisnis ini masih tersegel\n"WHITE"Unknows\nMarket\nBiaya Masuk $0\n%s", type, BisnisData[id][bLocked] == 1 ? ""RED"Tutup" : ""GREEN"Buka");
            BisnisData[id][bPickup] = CreateDynamicPickup(19133, 23, BisnisData[id][bExtposX], BisnisData[id][bExtposY], BisnisData[id][bExtposZ]+0.2, 0, 0, _, 8.0);
        }
		BisnisData[id][bPickPoint] = CreateDynamicPickup(1274, 23, BisnisData[id][bPointX], BisnisData[id][bPointY], BisnisData[id][bPointZ]+0.2, id, BisnisData[id][bInt], _, 4);
		
		format(tstr, 128, "{00FFFF}[id:%d]\n"RED_E"Bisnis Point\n"LG_E"use '/buy' here", id);
		BisnisData[id][bLabelPoint] = CreateDynamic3DTextLabel(tstr, COLOR_YELLOW, BisnisData[id][bPointX], BisnisData[id][bPointY], BisnisData[id][bPointZ]+0.5, 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, id, BisnisData[id][bInt]);
        BisnisData[id][bLabel] = CreateDynamic3DTextLabel(string, COLOR_GREEN, BisnisData[id][bExtposX], BisnisData[id][bExtposY], BisnisData[id][bExtposZ]+0.5, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, 0, 0);
	}
    return 1;
}

function LoadBisnis()
{
    static bid;
	
	new rows = cache_num_rows(), owner[128], name[128], bpname0[128], bpname1[128], bpname2[128], bpname3[128], bpname4[128], bpname5[128], bpname6[128], bpname7[128], bpname8[128], bpname9[128], bpname10[128], stream[128];
 	if(rows)
  	{
		for(new i; i < rows; i++)
		{
			cache_get_value_name_int(i, "ID", bid);
			cache_get_value_name(i, "owner", owner);
			format(BisnisData[bid][bOwner], 128, owner);
			cache_get_value_name(i, "name", name);
			format(BisnisData[bid][bName], 128, name);
			cache_get_value_name_int(i, "type", BisnisData[bid][bType]);
			cache_get_value_name_int(i, "price", BisnisData[bid][bPrice]);
			cache_get_value_name_float(i, "extposx", BisnisData[bid][bExtposX]);
			cache_get_value_name_float(i, "extposy", BisnisData[bid][bExtposY]);
			cache_get_value_name_float(i, "extposz", BisnisData[bid][bExtposZ]);
			cache_get_value_name_float(i, "extposa", BisnisData[bid][bExtposA]);
			cache_get_value_name_float(i, "intposx", BisnisData[bid][bIntposX]);
			cache_get_value_name_float(i, "intposy", BisnisData[bid][bIntposY]);
			cache_get_value_name_float(i, "intposz", BisnisData[bid][bIntposZ]);
			cache_get_value_name_float(i, "intposa", BisnisData[bid][bIntposA]);
			cache_get_value_name_int(i, "bint", BisnisData[bid][bInt]);
			cache_get_value_name_int(i, "money", BisnisData[bid][bMoney]);
			cache_get_value_name_int(i, "locked", BisnisData[bid][bLocked]);
			cache_get_value_name_int(i, "prod", BisnisData[bid][bProd]);
			cache_get_value_name_int(i, "bprice0", BisnisData[bid][bP][0]);
			cache_get_value_name_int(i, "bprice1", BisnisData[bid][bP][1]);
			cache_get_value_name_int(i, "bprice2", BisnisData[bid][bP][2]);
			cache_get_value_name_int(i, "bprice3", BisnisData[bid][bP][3]);
			cache_get_value_name_int(i, "bprice4", BisnisData[bid][bP][4]);
			cache_get_value_name_int(i, "bprice5", BisnisData[bid][bP][5]);
			cache_get_value_name_int(i, "bprice6", BisnisData[bid][bP][6]);
			cache_get_value_name_int(i, "bprice7", BisnisData[bid][bP][7]);
			cache_get_value_name_int(i, "bprice8", BisnisData[bid][bP][8]);
			cache_get_value_name_int(i, "bprice9", BisnisData[bid][bP][9]);
			cache_get_value_name_int(i, "bprice10", BisnisData[bid][bP][10]);
			cache_get_value_name_float(i, "pointx", BisnisData[bid][bPointX]);
			cache_get_value_name_float(i, "pointy", BisnisData[bid][bPointY]);
			cache_get_value_name_float(i, "pointz", BisnisData[bid][bPointZ]);
			cache_get_value_name_int(i, "visit", BisnisData[bid][bVisit]);
			cache_get_value_name_int(i, "restock", BisnisData[bid][bRestock]);
			cache_get_value_name(i, "bpname0", bpname0);
			format(BisnisData[bid][bPName0], 128, bpname0);
			cache_get_value_name(i, "bpname1", bpname1);
			format(BisnisData[bid][bPName1], 128, bpname1);
			cache_get_value_name(i, "bpname2", bpname2);
			format(BisnisData[bid][bPName2], 128, bpname2);
			cache_get_value_name(i, "bpname3", bpname3);
			format(BisnisData[bid][bPName3], 128, bpname3);
			cache_get_value_name(i, "bpname4", bpname4);
			format(BisnisData[bid][bPName4], 128, bpname4);
			cache_get_value_name(i, "bpname5", bpname5);
			format(BisnisData[bid][bPName5], 128, bpname5);
			cache_get_value_name(i, "bpname6", bpname6);
			format(BisnisData[bid][bPName6], 128, bpname6);
			cache_get_value_name(i, "bpname7", bpname7);
			format(BisnisData[bid][bPName7], 128, bpname7);
			cache_get_value_name(i, "bpname8", bpname8);
			format(BisnisData[bid][bPName8], 128, bpname8);
			cache_get_value_name(i, "bpname9", bpname9);
			format(BisnisData[bid][bPName9], 128, bpname9);
			cache_get_value_name(i, "bpname10", bpname10);
			format(BisnisData[bid][bPName10], 128, bpname10);
			cache_get_value_name(i, "stream", stream);
			format(BisnisData[bid][bStream], 128, stream);
			cache_get_value_name_int(i, "extvw", BisnisData[bid][bExtVw]);
			cache_get_value_name_int(i, "extint", BisnisData[bid][bExtInt]);

			BisnisData[bid][BiznisID] = bid;
			Bisnis_Refresh(bid);
			Iter_Add(Bisnis, bid);
		}
		printf("*** [Database: Loaded] bisnis data (%d count).", rows);
	}
}

//------------[ Bisnis Command ]------------
//Bisnis System
CMD:createbisnis(playerid, params[])
{
	if(AccountData[playerid][pAdmin] < 6)
		return PermissionError(playerid);
	
	new query[512];
	new bid = Iter_Free(Bisnis), address[128];
	if(bid == -1) return Error(playerid, "You cant create more door!");
	new type;
	if(sscanf(params, "d", type)) return ShowTDN(playerid, NOTIFICATION_INFO, "/createbisnis [type, 1.Fastfood 2.Market 3.Clothes 4.Sportshop 5.Electronic]");
	format(BisnisData[bid][bOwner], 128, "-");
	GetPlayerPos(playerid, BisnisData[bid][bExtposX], BisnisData[bid][bExtposY], BisnisData[bid][bExtposZ]);
	GetPlayerFacingAngle(playerid, BisnisData[bid][bExtposA]);
	BisnisData[bid][bExtVw] = GetPlayerVirtualWorld(playerid);
	BisnisData[bid][bExtInt] = GetPlayerInterior(playerid);
	BisnisData[bid][bPrice] = 5500000;
	BisnisData[bid][bType] = type;
	address = GetLocation(BisnisData[bid][bExtposX], BisnisData[bid][bExtposY], BisnisData[bid][bExtposZ]);
	format(BisnisData[bid][bName], 128, address);
	BisnisData[bid][bLocked] = 0;
	BisnisData[bid][bInt] = 0;
	BisnisData[bid][bIntposX] = 0;
	BisnisData[bid][bIntposY] = 0;
	BisnisData[bid][bIntposZ] = 0;
	BisnisData[bid][bIntposA] = 0;
	BisnisData[bid][bVisit] = 0;
	BisnisData[bid][bRestock] = 1;
	BisnisData[bid][bMoney] = 0;
	BisnisData[bid][bProd] = 1000;

	if(type == 1)
	{
		BisnisData[bid][bP][0] = 75;
		BisnisData[bid][bP][1] = 300;
		BisnisData[bid][bP][2] = 350;
		BisnisData[bid][bP][3] = 375;
	}
	else if(type == 2)
	{
		BisnisData[bid][bP][0] = 100;
		BisnisData[bid][bP][1] = 100;
		BisnisData[bid][bP][2] = 2250;
		BisnisData[bid][bP][3] = 2250;
		BisnisData[bid][bP][4] = 2500;
	}
	else if(type == 3)
	{
		BisnisData[bid][bP][0] = 2500;
		BisnisData[bid][bP][1] = 1000;
		BisnisData[bid][bP][2] = 1000;
		BisnisData[bid][bP][3] = 1000;
		BisnisData[bid][bP][4] = 1000;
		BisnisData[bid][bP][5] = 1000;
	}
	else if(type == 4)
	{
		BisnisData[bid][bP][0] = 375;
		BisnisData[bid][bP][1] = 375;
		BisnisData[bid][bP][2] = 375;
		BisnisData[bid][bP][3] = 3750;
		BisnisData[bid][bP][4] = 3750;
	}
	else if(type == 5)
	{
		BisnisData[bid][bP][0] = 2250;
		BisnisData[bid][bP][1] = 3500;
		BisnisData[bid][bP][2] = 750;
		BisnisData[bid][bP][3] = 3750;
	}
	Bisnis_ProductNameRefresh(bid);
	Bisnis_Type(bid);
    Bisnis_Refresh(bid);
	Iter_Add(Bisnis, bid);
	SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah membuat Bisnis ID "YELLOW"%d", AccountData[playerid][pAdminname], bid);
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO bisnis SET ID='%d', owner='%s', price='%d', type='%d', extposx='%f', extposy='%f', extposz='%f', extposa='%f', name='%s'", bid, BisnisData[bid][bOwner], BisnisData[bid][bPrice], BisnisData[bid][bType], BisnisData[bid][bExtposX], BisnisData[bid][bExtposY], BisnisData[bid][bExtposZ], BisnisData[bid][bExtposA], BisnisData[bid][bName]);
	mysql_tquery(g_SQL, query, "OnBisnisCreated", "i", bid);
	return 1;
}

function OnBisnisCreated(bid)
{
	Bisnis_Save(bid);
	return 1;
}

CMD:gotobisnis(playerid, params[])
{
	new bid;
	if(AccountData[playerid][pAdmin] < 2 && AccountData[playerid][pAdminGirl ]< 1)
        return PermissionError(playerid);
		
	if(sscanf(params, "d", bid))
		return ShowTDN(playerid, NOTIFICATION_INFO, "/gotobisnis [id]");
	if(!Iter_Contains(Bisnis, bid)) return Error(playerid, "The Bisnis you specified ID of doesn't exist.");
	SetPlayerPosition(playerid, BisnisData[bid][bExtposX], BisnisData[bid][bExtposY], BisnisData[bid][bExtposZ], BisnisData[bid][bExtposA]);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
	SendClientMessageEx(playerid, COLOR_WHITE, "You has teleport to bisnis id %d", bid);
	AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
	AccountData[playerid][pInBiz] = -1;
	return 1;
}

CMD:editbisnis(playerid, params[])
{
    static
        bid,
        type[24],
        string[128];

    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);

    if(sscanf(params, "ds[24]S()[128]", bid, type, string))
    {
        ShowTDN(playerid, NOTIFICATION_INFO, "/editbisnis [id] [name]");
        SendClientMessage(playerid, COLOR_YELLOW, "[NAMES]:{FFFFFF} location, interior, locked, owner, point, price, type, product, restock, reset");
        return 1;
    }
    if((bid < 0 || bid >= MAX_DYNAMIC_BISNIS))
        return Error(playerid, "You have specified an invalid ID.");
	if(!Iter_Contains(Bisnis, bid)) return Error(playerid, "The bisnis you specified ID of doesn't exist.");

    if(!strcmp(type, "location", true))
    {
		GetPlayerPos(playerid, BisnisData[bid][bExtposX], BisnisData[bid][bExtposY], BisnisData[bid][bExtposZ]);
		GetPlayerFacingAngle(playerid, BisnisData[bid][bExtposA]);
        Bisnis_Save(bid);
		Bisnis_Refresh(bid);

        SendAdminMessage(COLOR_RED, "%s has adjusted the location of bisnis ID: %d.", AccountData[playerid][pAdminname], bid);
    }
    else if(!strcmp(type, "interior", true))
    {
        GetPlayerPos(playerid, BisnisData[bid][bIntposX], BisnisData[bid][bIntposY], BisnisData[bid][bIntposZ]);
		GetPlayerFacingAngle(playerid, BisnisData[bid][bIntposA]);
		BisnisData[bid][bInt] = GetPlayerInterior(playerid);

        Bisnis_Save(bid);
		Bisnis_Refresh(bid);

        SendAdminMessage(COLOR_RED, "%s has adjusted the interior spawn of bisnis ID: %d.", AccountData[playerid][pAdminname], bid);
    }
    else if(!strcmp(type, "locked", true))
    {
        new locked;

        if(sscanf(string, "d", locked))
            return ShowTDN(playerid, NOTIFICATION_INFO, "/editbisnis [id] [locked] [0/1]");

        if(locked < 0 || locked > 1)
            return Error(playerid, "You must specify at least 0 or 1.");

        BisnisData[bid][bLocked] = locked;
        Bisnis_Save(bid);
		Bisnis_Refresh(bid);

        if(locked) {
            SendAdminMessage(COLOR_RED, "%s has locked bisnis ID: %d.", AccountData[playerid][pAdminname], bid);
        }
        else {
            SendAdminMessage(COLOR_RED, "%s has unlocked bisnis ID: %d.", AccountData[playerid][pAdminname], bid);
        }
    }
    else if(!strcmp(type, "price", true))
    {
        new price;

        if(sscanf(string, "d", price))
            return ShowTDN(playerid, NOTIFICATION_INFO, "/editbisnis [id] [Price] [Amount]");

        BisnisData[bid][bPrice] = price;

        Bisnis_Save(bid);
		Bisnis_Refresh(bid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the price of bisnis ID: %d to %d.", AccountData[playerid][pAdminname], bid, price);
    }
	else if(!strcmp(type, "type", true))
    {
        new btype;

        if(sscanf(string, "d", btype))
            return ShowTDN(playerid, NOTIFICATION_INFO, "/editbisnis [id] [Type] [1.Fastfood 2.Market 3.Clothes 4.Equipment]");

        BisnisData[bid][bType] = btype;
		Bisnis_Type(bid);
        Bisnis_Save(bid);
		Bisnis_Refresh(bid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the type of bisnis ID: %d to %d.", AccountData[playerid][pAdminname], bid, btype);
    }
	else if(!strcmp(type, "product", true))
    {
        new prod;

        if(sscanf(string, "d", prod))
            return ShowTDN(playerid, NOTIFICATION_INFO, "/editbisnis [id] [product] [Ammount]");

        BisnisData[bid][bProd] = prod;
        Bisnis_Save(bid);
		Bisnis_Refresh(bid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the product of bisnis ID: %d to %d.", AccountData[playerid][pAdminname], bid, prod);
    }
	else if(!strcmp(type, "money", true))
    {
        new money;

        if(sscanf(string, "d", money))
            return ShowTDN(playerid, NOTIFICATION_INFO, "/editbisnis [id] [money] [Ammount]");

        BisnisData[bid][bMoney] = money;
        Bisnis_Save(bid);
		Bisnis_Refresh(bid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the money of bisnis ID: %d to %s.", AccountData[playerid][pAdminname], bid, FormatMoney(money));
    }
	else if(!strcmp(type, "restock", true))
    {
        new prod;

        if(sscanf(string, "d", prod))
            return ShowTDN(playerid, NOTIFICATION_INFO, "/editbisnis [id] [restock] [0-1]");
		
		if(prod == 0)
		{
			BisnisData[bid][bRestock] = 0;
			Bisnis_Save(bid);
			Bisnis_Refresh(bid);
			SendAdminMessage(COLOR_RED, "%s has adjusted the restock of bisnis ID: %d to disable.", AccountData[playerid][pAdminname], bid);
		}
		else if(prod == 1)
		{
			BisnisData[bid][bRestock] = 1;
			Bisnis_Save(bid);
			Bisnis_Refresh(bid);
			SendAdminMessage(COLOR_RED, "%s has adjusted the restock of bisnis ID: %d to enable.", AccountData[playerid][pAdminname], bid);
		}
		else return Error(playerid, "Hanya id 0-1");
    }
    else if(!strcmp(type, "owner", true))
    {
        new owners[MAX_PLAYER_NAME];

        if(sscanf(string, "s[32]", owners))
            return ShowTDN(playerid, NOTIFICATION_INFO, "/editbisnis [id] [owner] [player name] (use '-' to no owner)");

        format(BisnisData[bid][bOwner], MAX_PLAYER_NAME, owners);
  
        Bisnis_Save(bid);
		Bisnis_Refresh(bid);
        SendAdminMessage(COLOR_RED, "%s has adjusted the owner of bisnis ID: %d to %s", AccountData[playerid][pAdminname], bid, owners);
    }
    else if(!strcmp(type, "reset", true))
    {
        Bisnis_Reset(bid);
		Bisnis_Save(bid);
		Bisnis_Refresh(bid);
        SendAdminMessage(COLOR_RED, "%s has reset bisnis ID: %d.", AccountData[playerid][pAdminname], bid);
    }
	else if(!strcmp(type, "point", true))
    {
		new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
		BisnisData[bid][bPointX] = x;
		BisnisData[bid][bPointY] = y;
		BisnisData[bid][bPointZ] = z;
		Bisnis_Save(bid);
		Bisnis_Refresh(bid);
        SendAdminMessage(COLOR_RED, "%s has edit bisnis point ID: %d.", AccountData[playerid][pAdminname], bid);
    }
	else if(!strcmp(type, "delete", true))
    {
		Bisnis_Reset(bid);
		
		DestroyDynamic3DTextLabel(BisnisData[bid][bLabel]);
        DestroyDynamicPickup(BisnisData[bid][bPickup]);
		
		BisnisData[bid][bExtposX] = 0;
		BisnisData[bid][bExtposY] = 0;
		BisnisData[bid][bExtposZ] = 0;
		BisnisData[bid][bExtposA] = 0;
		BisnisData[bid][bPrice] = 0;
		BisnisData[bid][bInt] = 0;
		BisnisData[bid][bIntposX] = 0;
		BisnisData[bid][bIntposY] = 0;
		BisnisData[bid][bIntposZ] = 0;
		BisnisData[bid][bIntposA] = 0;
		BisnisData[bid][bLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
		BisnisData[bid][bPickup] = STREAMER_TAG_PICKUP: INVALID_STREAMER_ID;
		
		Iter_Remove(Bisnis, bid);
		new query[128];
		mysql_format(g_SQL, query, sizeof(query), "DELETE FROM bisnis WHERE ID=%d", bid);
		mysql_tquery(g_SQL, query);
        SendAdminMessage(COLOR_RED, "%s has delete bisnis ID: %d.", AccountData[playerid][pAdminname], bid);
	}
    return 1;
}

CMD:lockbisnis(playerid, params[])
{
	foreach(new bid : Bisnis)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.5, BisnisData[bid][bExtposX], BisnisData[bid][bExtposY], BisnisData[bid][bExtposZ]))
		{
			if(!Player_OwnsBisnis(playerid, bid)) return Error(playerid, "You don't own this bisnis.");
			if(!BisnisData[bid][bLocked])
			{
				BisnisData[bid][bLocked] = 1;
				Bisnis_Save(bid);
				Bisnis_Refresh(bid);

				ShowPlayerFooter(playerid, "Berhasil ~r~Mengunci~w~ Bisnis anda", 7000);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
			else
			{
				BisnisData[bid][bLocked] = 0;
				Bisnis_Save(bid);
				Bisnis_Refresh(bid);

				ShowPlayerFooter(playerid, "Berhasil ~g~Membuka~w~ Bisnis anda", 7000);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
		}
	}
	return 1;
}

CMD:bm(playerid, params[])
{
	if(AccountData[playerid][pInBiz] == -1) return 0;
	if(!Player_OwnsBisnis(playerid, AccountData[playerid][pInBiz])) return Error(playerid, "You don't own this bisnis.");
    Dialog_Show(playerid, BISNIS_MENU, DIALOG_STYLE_LIST, "Bisnis Menu","Bisnis Info\nChange Name\nProduct Menu\nChange Name Product Menu\nRequest Restock\nRadio URL(Music)","Next","Close");
    return 1;
}

CMD:bwithdraw(playerid, params[])
{
	if(AccountData[playerid][pInBiz] == -1) return 0;
	if(!Player_OwnsBisnis(playerid, AccountData[playerid][pInBiz])) return Error(playerid, "You don't own this bisnis.");

	new bid = AccountData[playerid][pInBiz];
	new String[512], amount[32], dollars, cents, duit[32];

	if(sscanf(params, "s[32]", amount))
	{
		SendClientMessageEx(playerid, -1, "KEGUNAAN: /bwithdraw [Jumlah]");
		format(String, sizeof(String), "Anda memiliki uang sebesar %s di dalam Akun bisnis Anda.", FormatMoney(BisnisData[bid][bMoney]));
		SendClientMessageEx(playerid, -1, String);
		return 1;
	}
	if(strfind(amount, ".", true) != 1)
	{
	   	sscanf(amount, "p<.>dd", dollars, cents);
	    format(duit, sizeof(duit), "%d%02d", dollars, cents);
		if(strval(duit) > BisnisData[bid][bMoney])
		{
			SendClientMessageEx(playerid, -1, "Anda tidak memiliki uang sebesar itu di dalam Akun bisnis anda!");
			return 1;
		}
		if(strval(duit) < 0) return SendClientMessageEx(playerid, COLOR_GREY, "Tidak bisa dibawah $0.00");
		GiveMoney(playerid,strval(duit));
		BisnisData[bid][bMoney]=BisnisData[bid][bMoney]-strval(duit);
		format(String, sizeof(String), "BISNIS: {ffffff}You've withdrawn {ffff00}$%s{ffffff} from your bisnis account", FormatMoney(strval(duit)));
		SendClientMessageEx(playerid, ARWIN, String);
		format(String, sizeof(String), "BISNIS: {ffff00}$%s",FormatMoney(BisnisData[bid][bMoney]));
		SendClientMessageEx(playerid, ARWIN, String);
	}
	else
	{
	   	sscanf(amount, "d", dollars);
	    format(duit, sizeof(duit), "%d00", dollars);
		if(strval(duit) > BisnisData[bid][bMoney])
		{
			SendClientMessageEx(playerid, -1, "Anda tidak memiliki uang sebesar itu di dalam Akun bisnis anda!");
			return 1;
		}
		if(strval(duit) < 0) return SendClientMessageEx(playerid, COLOR_GREY, "Tidak bisa dibawah $0.00");
		GiveMoney(playerid,strval(duit));
		BisnisData[bid][bMoney]=BisnisData[bid][bMoney]-strval(duit);
		format(String, sizeof(String), "BISNIS: {ffffff}You've withdrawn {ffff00}$%s{ffffff} from your bisnis account", FormatMoney(strval(duit)));
		SendClientMessageEx(playerid, ARWIN, String);
		format(String, sizeof(String), "BISNIS: {ffff00}$%s",FormatMoney(BisnisData[bid][bMoney]));
		SendClientMessageEx(playerid, ARWIN, String);
	}
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if((newkeys & KEY_SECONDARY_ATTACK) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
	{
		foreach(new bid : Bisnis)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.8, BisnisData[bid][bExtposX], BisnisData[bid][bExtposY], BisnisData[bid][bExtposZ]))
			{
				if(BisnisData[bid][bIntposX] == 0.0 && BisnisData[bid][bIntposY] == 0.0 && BisnisData[bid][bIntposZ] == 0.0)
					return ShowTDN(playerid, NOTIFICATION_ERROR, "Interior bisnis masih kosong, atau tidak memiliki interior.");

				if(BisnisData[bid][bLocked])
					return GameTextForPlayer(playerid, "~w~Biz ~r~Terkunci!", 1000, 5);
				AccountData[playerid][pInBiz] = bid;
				SetPlayerPositionEx(playerid, BisnisData[bid][bIntposX], BisnisData[bid][bIntposY], BisnisData[bid][bIntposZ], BisnisData[bid][bIntposA]);
				
				SetPlayerInterior(playerid, BisnisData[bid][bInt]);
				SetPlayerVirtualWorld(playerid, bid);
				SetCameraBehindPlayer(playerid);
				SetPlayerWeather(playerid, 0);
				PlayStream(playerid, BisnisData[bid][bStream], BisnisData[bid][bIntposX], BisnisData[bid][bIntposY], BisnisData[bid][bIntposZ], 30.0, 1);
			}
        }
		new inbisnisid = AccountData[playerid][pInBiz];
		if(AccountData[playerid][pInBiz] != -1 && IsPlayerInRangeOfPoint(playerid, 2.8, BisnisData[inbisnisid][bIntposX], BisnisData[inbisnisid][bIntposY], BisnisData[inbisnisid][bIntposZ]))
		{
			AccountData[playerid][pInBiz] = -1;
			SetPlayerPositionEx(playerid, BisnisData[inbisnisid][bExtposX], BisnisData[inbisnisid][bExtposY], BisnisData[inbisnisid][bExtposZ], BisnisData[inbisnisid][bExtposA]);
			
			SetPlayerInterior(playerid, BisnisData[inbisnisid][bExtInt]);
			SetPlayerVirtualWorld(playerid, BisnisData[inbisnisid][bExtVw]);
			SetCameraBehindPlayer(playerid);
			SetPlayerWeather(playerid, WorldWeather);
			StopStream(playerid);
			AccountData[playerid][pInt] = 0;
			AccountData[playerid][pWorld] = 0;
		}	
	}
	return 1;
}