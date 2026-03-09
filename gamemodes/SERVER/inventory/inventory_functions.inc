#include <YSI\y_hooks>
#define MAX_INVENTORY   20
#define inv::           i_

new ListedInventory[MAX_PLAYERS][MAX_INVENTORY];

enum inventoryData
{
	invID,
	invExists,
	invItem[128 char],
	invModel,
	invQuantity
};
new InventoryData[MAX_PLAYERS][MAX_INVENTORY][inventoryData];

enum e_InventoryItems
{
    e_InventoryItem[128],
    e_InventoryModel
};

// Nama Dan Model Barang
new const g_aInventoryItems[][e_InventoryItems] = 
{
    {"Nasi Goreng", 2355},
    {"Kopi Kenangan", 19835},
	{"Batu Kotor", 3930},
	{"Nasi Uduk", 19567},
    {"Kanabis", 19473},
	{"Batu Bersih", 2936},
	{"Air Mineral", 19570},
	{"Besi", 19809},
	{"Tembaga", 11748},
	{"Berlian", 19941},
    {"Emas", 19941},
    {"Gold", 2784},
	{"Smartphone", 18870},
    {"Race Tablet", 19894},
    {"Earphone", 19424},
    {"Radio", 19942},
	{"Kayu", 19793},
	{"Kayu Potongan", 1463},
	{"Kayu Kemas", 2912},
	{"Marijuana", 1575},
	{"Benang", 1902},
	{"Kain", 11747},
	{"Pakaian", 2399},
	{"Bandage", 11736},
    {"Medkit", 11738},
    {"Alprazolam", 1241},
	{"Ayam Potong", 2804},
	{"Ayam Hidup", 16776},
	{"Ayam Kemas", 2768},
    {"Sampah Makanan", 2840},
    {"Kevlar", 19515},
    {"Botol", 19570},
    {"Petrol", 19621},
    {"Pure Oil", 3632},
    {"GAS", 1650},
    {"Ikan", 19630},
    {"Rokok", 19896},
    {"Pancingan", 18632},
    {"Umpan", 1603},
    {"Hiu", 1608},
    {"Penyu", 1609},
    {"Ikan Tawar", 1599},
    {"Jerigen", 1650},
    {"Tools Kit", 19918},
    {"Repair Kit", 19921},
    {"Uang Merah", 1212},
    {"Linggis", 18634},
    {"Hacking Tools", 19893},
    {"Bomb", 1636},
    {"Kunci T", 334},
    {"Nasi Pecel", 2218},
    {"Es Teh", 1546},
    {"Bubur Pedas", 19568},
    {"Jus Apel", 19564},
    {"Boombox", 2103},
    {"Kebab A5", 2769},
    {"Choco Matcha", 1667},
    {"Bakso", 19567},
    {"Teh Jeruk", 19563},
    {"Susu Murni", 19570},
    {"Susu Olahan", 19570},
    {"Susu Fresh", 19569},
    {"Api Unggun", 19632},
    {"Cabe", 2253},
    {"Padi", 804},
    {"Tebu", 806},
    {"Garam Kristal", 1611},
    {"Gula", 1575},
    {"Beras", 2060},
    {"Sambal", 11722},
    {"Garam", 1279},
    {"Daging", 2806},
    {"Daging Ikan Tawar", 2806},
    {"Daging Hiu", 2806},
    {"Daging Ayam Goreng", 2806},
    {"Tanduk", 6865},
    {"Kulit", 19560},
    {"Bulu", 19517},
    {"Boxmats", 2912},
    {"Baja", 19772},
    {"Material", 19843},
    {"Kaca", 1649},
    {"Karet", 1316},
    {"Plastik", 1264},
    {"Alumunium", 2937},
    {"Backpack", 3026},
    {"Masker", 19036},
    {"Plat Besi", 3117},
    {"Korek Api", 19998},
    {"Bibit Cabe", 2663},
    {"Bibit Padi", 2663},
    {"Bibit Tebu", 2663},
    {"Petasan", 3790},
    {"KTA", 1581},
    {"Tahu Bulat", 19574},
    {"Pilox", 365},
    {"Chip", 1915},
    {"Component", 3096},
    {"Uranium ACD", 3046},
    {"Uranium", 2958},
    {"Senter", 18641}
};

/*Function*/
/*FormatInventoryDigit(amount, const delimiter[2]=",")
{
    #define MAX_Digit_String 16
    new txt[MAX_Digit_String];
    format(txt, MAX_Digit_String, "%d", amount);
    new l = strlen(txt);

    if(l == 1) strins(txt, "0,00", l-1);
    else if(l == 2) strins(txt, "0,0", l-2);
    else if(l == 3) strins(txt, "0,", l-3);
    else if(l > 3) strins(txt,delimiter,l-3);
    return txt;
}

GetItemWeight(const item[])
{
    for (new i; i < sizeof(g_aInventoryItems); i ++) {
        if (strcmp(item, g_aInventoryItems[i][e_InventoryItem], true) == 0)
        {
            return g_aInventoryItems[i][e_InventoryWeight];
        }
    }

    //jika nama item tidak ditemukan, kembalikan nilai 0
    return 0;
}*/

FUNC::Inventory_Clear(playerid)
{
    for(new i = 0; i < MAX_INVENTORY; i++)
    {
        InventoryData[playerid][i][invExists] = false;
        InventoryData[playerid][i][invModel] = 0;
        InventoryData[playerid][i][invQuantity] = 0;
        AccountData[playerid][pBeratItem] = 0;
    }
    return mysql_tquery(g_SQL, sprintf("DELETE FROM `inventory` WHERE `ID` = '%d'", AccountData[playerid][pID]));
}

FUNC::Inventory_GetItemID(playerid, item[])
{
	forex(i, MAX_INVENTORY)
	{
	    if (!InventoryData[playerid][i][invExists])
	        continue;
		if (!strcmp(InventoryData[playerid][i][invItem], item)) return i;
	}
	return -1;
}

FUNC::Inventory_GetFreeID(playerid)
{
	if (Inventory_Items(playerid) >= MAX_INVENTORY)
		return -1;
	forex(i, MAX_INVENTORY)
	{
	    if (!InventoryData[playerid][i][invExists])
	        return i;
	}
	return -1;
}

FUNC::Inventory_Items(playerid)
{
    new count;
    for(new i = 0; i < MAX_INVENTORY; i++) if (InventoryData[playerid][i][invExists]) {
        count++;
    }
    return count;
}

FUNC::Inventory_Count(playerid, item[])
{
    new itemid = Inventory_GetItemID(playerid, item);
    if (itemid != -1)
        return InventoryData[playerid][itemid][invQuantity];
    return 0;
}

FUNC::PlayerHasItem(playerid, item[])
{
    return (Inventory_GetItemID(playerid, item) != -1);
}

FUNC::Inventory_Set(playerid, item[], model, amount)
{
    new itemid = Inventory_GetItemID(playerid, item);
    if (itemid == -1 && amount > 0)
        Inventory_Add(playerid, item, model, amount);
    else if (amount > 0 && itemid != -1)
        Inventory_SetQuantity(playerid, item, amount);
    else if (amount < 1 && itemid != -1)
        Inventory_Remove(playerid, item, Inventory_Count(playerid, item));
    return 1;
}

FUNC::Inventory_SetQuantity(playerid, item[], quantity)
{
    new
        itemid = Inventory_GetItemID(playerid, item);
    if (itemid != -1)
    {
        mysql_tquery(g_SQL, sprintf("UPDATE `inventory` SET `invQuantity` = %d WHERE `ID` = '%d' AND `invID` = '%d'", quantity, AccountData[playerid][pID], InventoryData[playerid][itemid][invID]));
        InventoryData[playerid][itemid][invQuantity] = quantity;
    }
    return 1;
}

stock Inventory_Remove(playerid, item[], quantity = 1)
{
	new
		itemid = Inventory_GetItemID(playerid, item);

	if (itemid != -1)
	{
	    if (InventoryData[playerid][itemid][invQuantity] > 0)
	    {
            AccountData[playerid][pBeratItem] -= Float:GetInventoryWeight(item, quantity);
	        InventoryData[playerid][itemid][invQuantity] -= quantity;
		}
		if (quantity == -1 || InventoryData[playerid][itemid][invQuantity] < 1)
		{
		    InventoryData[playerid][itemid][invExists] = false;
		    InventoryData[playerid][itemid][invModel] = 0;
		    InventoryData[playerid][itemid][invQuantity] = 0;
	        mysql_tquery(g_SQL, sprintf("DELETE FROM `inventory` WHERE `ID` = '%d' AND `invID` = '%d'", AccountData[playerid][pID], InventoryData[playerid][itemid][invID]));
		}
		else if (quantity != -1 && InventoryData[playerid][itemid][invQuantity] > 0)
		{
            mysql_tquery(g_SQL, sprintf("UPDATE `inventory` SET `invQuantity` = `invQuantity` - %d WHERE `ID` = '%d' AND `invID` = '%d'", quantity, AccountData[playerid][pID], InventoryData[playerid][itemid][invID]));
		}
		return 1;
	}
	return 0;
}
FUNC::TambahkanBerat(playerid, item[], quantity)
{
    if(AccountData[playerid][pBeratItem] >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh"), Inventory_Close(playerid);

    AccountData[playerid][pBeratItem] += Float:GetInventoryWeight(item, quantity);
    return 1;
}

/*stock Inventory_Add(playerid, item[], model, quantity = 1)
{
	new
		itemid = Inventory_GetItemID(playerid, item);

	if (itemid == -1)
	{
	    itemid = Inventory_GetFreeID(playerid);

	    if (itemid != -1)
	    {
            TambahkanBerat(playerid, item, quantity);
	        InventoryData[playerid][itemid][invExists] = true;
	        InventoryData[playerid][itemid][invModel] = model;
	        InventoryData[playerid][itemid][invQuantity] = quantity;

	        strpack(InventoryData[playerid][itemid][invItem], item, 32 char);

            mysql_tquery(g_SQL, sprintf("INSERT INTO `inventory` (`ID`, `invItem`, `invModel`, `invQuantity`) VALUES('%d', '%s', '%d', '%d')", AccountData[playerid][pID], item, model, quantity),"OnInventoryAdd", "dd", playerid, itemid);
	        return itemid;
		}
		return -1;
	}
	else
	{
        if(GetTotalWeightFloat(playerid) > 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!"), Inventory_Close(playerid);
        
        if(!strcmp(item, "Nasi Goreng"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Kopi Kenangan"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Batu Kotor"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.030;
        }
        else if(!strcmp(item, "Nasi Uduk"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Kanabis"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Batu Bersih"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.030;
        }
        else if(!strcmp(item, "Air Mineral"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Besi"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Tembaga"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Berlian"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.25;
        }
        else if(!strcmp(item, "Emas"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.10;
        }
        else if(!strcmp(item, "Smartphone"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.25;
        }
        else if(!strcmp(item, "Radio"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.15;
        }
        else if(!strcmp(item, "Kayu"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.06;
        }
        else if(!strcmp(item, "Kayu Potongan"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.05;
        }
        else if(!strcmp(item, "Kayu Kemas"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.08;
        }
        else if(!strcmp(item, "Marijuana"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.02;
        }
        else if(!strcmp(item, "Benang"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Kain"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.04;
        }
        else if(!strcmp(item, "Pakaian"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.04;
        }
        else if(!strcmp(item, "Bandage"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.02;
        }
        else if(!strcmp(item, "Medkit"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.05;
        }
        else if(!strcmp(item, "Alprazolam"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Ayam Hidup"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.15;
        }
        else if(!strcmp(item, "Ayam Potong"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.10;
        }
        else if(!strcmp(item, "Ayam Kemas"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.05;
        }
        else if(!strcmp(item, "Sampah Makanan"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.005;
        }
        else if(!strcmp(item, "Kevlar"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.90;
        }
        else if(!strcmp(item, "Botol"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Petrol"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.50;
        }
        else if(!strcmp(item, "Pure Oil"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.50;
        }
        else if(!strcmp(item, "GAS"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.60;
        }
        else if(!strcmp(item, "Ikan"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.02;
        }
        else if(!strcmp(item, "Rokok"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Pancingan"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.08;
        }
        else if(!strcmp(item, "Umpan"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.02;
        }
        else if(!strcmp(item, "Hiu"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.90;
        }
        else if(!strcmp(item, "Penyu"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.80;
        }
        else if(!strcmp(item, "Ikan Tawar"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.03;
        }
        else if(!strcmp(item, "Jerigen"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.25;
        }
        else if(!strcmp(item, "Tools Kit"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.30;
        }
        else if(!strcmp(item, "Repair Kit"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.35;
        }
        else if(!strcmp(item, "Linggis"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.05;
        }
        else if(!strcmp(item, "Hacking Tools"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.05;
        }
        else if(!strcmp(item, "Kunci T"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.05;
        }
        else if(!strcmp(item, "Nasi Pecel"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Bubur Pedas"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Es Teh"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Jus Apel"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Boombox"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.20;
        }
        else if(!strcmp(item, "Kebab A5"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Bakso"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Choco Matcha"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Teh Jeruk"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Susu Murni"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.02;
        }
        else if(!strcmp(item, "Susu Olahan"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Susu Fresh"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Cabe"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Padi"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Garam Kristal"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.006;
        }
        else if(!strcmp(item, "Tebu"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Beras"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.04;
        }
        else if(!strcmp(item, "Sambal"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.02;
        }
        else if(!strcmp(item, "Gula"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Garam"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Daging"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.02;
        }
        else if(!strcmp(item, "Tanduk"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.03;
        }
        else if(!strcmp(item, "Kulit"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Bulu"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.01;
        }
        else if(!strcmp(item, "Boxmats"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.04;
        }
        else if(!strcmp(item, "Baja"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.05;
        }
        else if(!strcmp(item, "Material"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.025;
        }
        else if(!strcmp(item, "Kaca"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.015;
        }
        else if(!strcmp(item, "Karet"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.006;
        }
        else if(!strcmp(item, "Plastik"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.005;
        }
        else if(!strcmp(item, "Alumunium"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.010;
        }
        else if(!strcmp(item, "Backpack"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.50;
        }
        else if(!strcmp(item, "Masker"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.005;
        }
        else if(!strcmp(item, "Plat Besi"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.025;
        }
        else if(!strcmp(item, "Korek Api"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.010;
        }
        else if(!strcmp(item, "Bibit Tebu"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.015;
        }
        else if(!strcmp(item, "Bibit Padi"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.015;
        }
        else if(!strcmp(item, "Bibit Cabe"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.015;
        }
        else if(!strcmp(item, "Petasan"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.010;
        }
        else if(!strcmp(item, "KTA"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.005;
        }
        else if(!strcmp(item, "Tahu Bulat"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.005;
        }
        else if(!strcmp(item, "Pilox"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.005;
        }
        else if(!strcmp(item, "Uranium ACD"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.020;
        }
        else if(!strcmp(item, "Uranium"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.010;
        }
        else if(!strcmp(item, "Senter"))
        {
            AccountData[playerid][pBeratItem] += quantity*0.006;
        }
	    InventoryData[playerid][itemid][invQuantity] += quantity;
        mysql_tquery(g_SQL, sprintf("UPDATE player_characters SET Char_BackpackWeight = '%.3f' WHERE pID = '%d'", AccountData[playerid][pBeratItem], AccountData[playerid][pID]));

	    mysql_tquery(g_SQL, sprintf("UPDATE `inventory` SET `invQuantity` = `invQuantity` + %d WHERE `ID` = '%d' AND `invID` = '%d'", quantity, AccountData[playerid][pID], InventoryData[playerid][itemid][invID]));
    }
	return itemid;
}*/

stock Inventory_Add(playerid, item[], model, quantity = 1)
{
    new itemid = Inventory_GetItemID(playerid, item);

    if (itemid == -1)
    {
        itemid = Inventory_GetFreeID(playerid);

        if (itemid != -1)
        {
            if(quantity > 1000)
            {
                quantity = 1000;
                ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah max per item adalah 100!");
            }
            TambahkanBerat(playerid, item, quantity);
            InventoryData[playerid][itemid][invExists] = true;
            InventoryData[playerid][itemid][invModel] = model;
            InventoryData[playerid][itemid][invQuantity] = quantity;

            strpack(InventoryData[playerid][itemid][invItem], item, 32 char);
            mysql_tquery(g_SQL, sprintf("INSERT INTO inventory (ID, invItem, invModel, invQuantity) VALUES('%d', '%s', '%d', '%d')",AccountData[playerid][pID], item, model, quantity), "OnInventoryAdd", "dd", playerid, itemid);
            return itemid;
        }
        return -1;
    }
    else
    {
        if(GetTotalWeightFloat(playerid) > 50)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Anda Penuh!"), Inventory_Close(playerid);

        new currentQty = InventoryData[playerid][itemid][invQuantity];
        new newQty = currentQty + quantity;

        if(newQty > 1000)
        {
            newQty = 1000;
            ShowTDN(playerid, NOTIFICATION_ERROR, "Jumlah max per item adalah 100!");
        }

        new added = newQty - currentQty; 
        if(added > 0)
        {
            if(!strcmp(item, "Nasi Goreng"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Kopi Kenangan"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Batu Kotor"))
            {
                AccountData[playerid][pBeratItem] += added * 0.030;
            }
            else if(!strcmp(item, "Nasi Uduk"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Kanabis"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Batu Bersih"))
            {
                AccountData[playerid][pBeratItem] += added * 0.030;
            }
            else if(!strcmp(item, "Air Mineral"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Besi"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Tembaga"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Berlian"))
            {
                AccountData[playerid][pBeratItem] += added * 0.25;
            }
            else if(!strcmp(item, "Emas"))
            {
                AccountData[playerid][pBeratItem] += added * 0.10;
            }
            else if(!strcmp(item, "Gold"))
            {
                AccountData[playerid][pBeratItem] += added * 0.10;
            }
            else if(!strcmp(item, "Smartphone"))
            {
                AccountData[playerid][pBeratItem] += added * 0.25;
            }
            else if(!strcmp(item, "Race Tablet"))
            {
                AccountData[playerid][pBeratItem] += added * 0.25;
            }
            else if(!strcmp(item, "Radio"))
            {
                AccountData[playerid][pBeratItem] += added * 0.15;
            }
            else if(!strcmp(item, "Kayu"))
            {
                AccountData[playerid][pBeratItem] += added * 0.06;
            }
            else if(!strcmp(item, "Kayu Potongan"))
            {
                AccountData[playerid][pBeratItem] += added * 0.05;
            }
            else if(!strcmp(item, "Kayu Kemas"))
            {
                AccountData[playerid][pBeratItem] += added * 0.08;
            }
            else if(!strcmp(item, "Marijuana"))
            {
                AccountData[playerid][pBeratItem] += added * 0.02;
            }
            else if(!strcmp(item, "Benang"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Kain"))
            {
                AccountData[playerid][pBeratItem] += added * 0.04;
            }
            else if(!strcmp(item, "Pakaian"))
            {
                AccountData[playerid][pBeratItem] += added * 0.04;
            }
            else if(!strcmp(item, "Bandage"))
            {
                AccountData[playerid][pBeratItem] += added * 0.02;
            }
            else if(!strcmp(item, "Medkit"))
            {
                AccountData[playerid][pBeratItem] += added * 0.05;
            }
            else if(!strcmp(item, "Alprazolam"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Ayam Hidup"))
            {
                AccountData[playerid][pBeratItem] += added * 0.15;
            }
            else if(!strcmp(item, "Ayam Potong"))
            {
                AccountData[playerid][pBeratItem] += added * 0.10;
            }
            else if(!strcmp(item, "Ayam Kemas"))
            {
                AccountData[playerid][pBeratItem] += added * 0.05;
            }
            else if(!strcmp(item, "Sampah Makanan"))
            {
                AccountData[playerid][pBeratItem] += added * 0.005;
            }
            else if(!strcmp(item, "Kevlar"))
            {
                AccountData[playerid][pBeratItem] += added * 0.90;
            }
            else if(!strcmp(item, "Botol"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Petrol"))
            {
                AccountData[playerid][pBeratItem] += added * 0.50;
            }
            else if(!strcmp(item, "Pure Oil"))
            {
                AccountData[playerid][pBeratItem] += added * 0.50;
            }
            else if(!strcmp(item, "GAS"))
            {
                AccountData[playerid][pBeratItem] += added * 0.60;
            }
            else if(!strcmp(item, "Ikan"))
            {
                AccountData[playerid][pBeratItem] += added * 0.02;
            }
            else if(!strcmp(item, "Rokok"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Pancingan"))
            {
                AccountData[playerid][pBeratItem] += added * 0.08;
            }
            else if(!strcmp(item, "Umpan"))
            {
                AccountData[playerid][pBeratItem] += added * 0.02;
            }
            else if(!strcmp(item, "Hiu"))
            {
                AccountData[playerid][pBeratItem] += added * 0.90;
            }
            else if(!strcmp(item, "Penyu"))
            { 
                AccountData[playerid][pBeratItem] += added * 0.80;
            }
            else if(!strcmp(item, "Ikan Tawar"))
            { 
                AccountData[playerid][pBeratItem] += added * 0.03;
            }
            else if(!strcmp(item, "Jerigen"))
            { 
                AccountData[playerid][pBeratItem] += added * 0.25;
            }
            else if(!strcmp(item, "Tools Kit"))
            {
                AccountData[playerid][pBeratItem] += added * 0.30;
            }
            else if(!strcmp(item, "Repair Kit"))
            {
                AccountData[playerid][pBeratItem] += added * 0.35;
            }
            else if(!strcmp(item, "Linggis"))
            {
                AccountData[playerid][pBeratItem] += added * 0.05;
            }
            else if(!strcmp(item, "Hacking Tools"))
            {
                AccountData[playerid][pBeratItem] += added * 0.20;
            }
            else if(!strcmp(item, "Bomb"))
            {
                AccountData[playerid][pBeratItem] += added * 0.50;
            }
            else if(!strcmp(item, "Kunci T"))
            {
                AccountData[playerid][pBeratItem] += added * 0.05;
            }
            else if(!strcmp(item, "Nasi Pecel"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Bubur Pedas"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Es Teh"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Jus Apel"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Boombox"))
            {
                AccountData[playerid][pBeratItem] += added * 0.20;
            }
            else if(!strcmp(item, "Api Unggun"))
            {
                AccountData[playerid][pBeratItem] += added * 0.10;
            }
            else if(!strcmp(item, "Kebab A5"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Bakso"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Choco Matcha"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Teh Jeruk"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Susu Murni"))
            {
                AccountData[playerid][pBeratItem] += added * 0.02;
            }
            else if(!strcmp(item, "Susu Olahan"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Susu Fresh"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Cabe"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Padi"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Garam Kristal"))
            {
                AccountData[playerid][pBeratItem] += added * 0.006;
            }
            else if(!strcmp(item, "Tebu"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Beras"))
            {
                AccountData[playerid][pBeratItem] += added * 0.04;
            }
            else if(!strcmp(item, "Sambal"))
            {
                AccountData[playerid][pBeratItem] += added * 0.02;
            }
            else if(!strcmp(item, "Gula"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Garam"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Daging"))
            {
                AccountData[playerid][pBeratItem] += added * 0.02;
            }
            else if(!strcmp(item, "Daging Ikan Tawar"))
            {
                AccountData[playerid][pBeratItem] += added * 0.02;
            }
            else if(!strcmp(item, "Daging Ayam Goreng"))
            {
                AccountData[playerid][pBeratItem] += added * 0.02;
            }
            else if(!strcmp(item, "Daging Hiu"))
            {
                AccountData[playerid][pBeratItem] += added * 0.09;
            }
            else if(!strcmp(item, "Tanduk"))
            {
                AccountData[playerid][pBeratItem] += added * 0.03;
            }
            else if(!strcmp(item, "Kulit"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Bulu"))
            {
                AccountData[playerid][pBeratItem] += added * 0.01;
            }
            else if(!strcmp(item, "Boxmats"))
            {
                AccountData[playerid][pBeratItem] += added * 0.04;
            }
            else if(!strcmp(item, "Baja"))
            {
                AccountData[playerid][pBeratItem] += added * 0.05;
            }
            else if(!strcmp(item, "Material"))
            {
                AccountData[playerid][pBeratItem] += added * 0.025;
            }
            else if(!strcmp(item, "Kaca"))
            {
                AccountData[playerid][pBeratItem] += added * 0.015;
            }
            else if(!strcmp(item, "Karet"))
            {
                AccountData[playerid][pBeratItem] += added * 0.006;
            }
            else if(!strcmp(item, "Plastik"))
            {
                AccountData[playerid][pBeratItem] += added * 0.005;
            }
            else if(!strcmp(item, "Alumunium"))
            {
                AccountData[playerid][pBeratItem] += added * 0.010;
            }
            else if(!strcmp(item, "Backpack"))
            {
                AccountData[playerid][pBeratItem] += added * 0.50;
            }
            else if(!strcmp(item, "Masker"))
            {
                AccountData[playerid][pBeratItem] += added * 0.005;
            }
            else if(!strcmp(item, "Plat Besi"))
            {
                AccountData[playerid][pBeratItem] += added * 0.025;
            }
            else if(!strcmp(item, "Korek Api"))
            {
                AccountData[playerid][pBeratItem] += added * 0.010;
            }
            else if(!strcmp(item, "Bibit Tebu"))
            {
                AccountData[playerid][pBeratItem] += added * 0.015;
            }
            else if(!strcmp(item, "Bibit Padi"))
            {
                AccountData[playerid][pBeratItem] += added * 0.015;
            }
            else if(!strcmp(item, "Bibit Cabe"))
            {
                AccountData[playerid][pBeratItem] += added * 0.015;
            }
            else if(!strcmp(item, "Petasan"))
            {
                AccountData[playerid][pBeratItem] += added * 0.010;
            }
            else if(!strcmp(item, "KTA"))
            {
                AccountData[playerid][pBeratItem] += added * 0.005;
            }
            else if(!strcmp(item, "Tahu Bulat"))
            {
                AccountData[playerid][pBeratItem] += added * 0.005;
            }
            else if(!strcmp(item, "Pilox"))
            {
                AccountData[playerid][pBeratItem] += added * 0.005;
            }
            else if(!strcmp(item, "Uranium ACD"))
            {
                AccountData[playerid][pBeratItem] += added * 0.020;
            }
            else if(!strcmp(item, "Uranium"))
            {
                AccountData[playerid][pBeratItem] += added * 0.010;
            }
            else if(!strcmp(item, "Senter"))
            {
                AccountData[playerid][pBeratItem] = added * 0.006;
            }
        }
        InventoryData[playerid][itemid][invQuantity] = newQty;
        mysql_tquery(g_SQL, sprintf("UPDATE player_characters SET Char_BackpackWeight = '%.3f' WHERE pID = '%d'",AccountData[playerid][pBeratItem], AccountData[playerid][pID]));
        mysql_tquery(g_SQL, sprintf("UPDATE inventory SET invQuantity = '%d' WHERE ID = '%d' AND invID = '%d'",newQty, AccountData[playerid][pID], InventoryData[playerid][itemid][invID]));
    }
    return itemid;
}

forward OpenInventory(playerid);
public OpenInventory(playerid)
{
    new
        itemname[24],
        shstr[255],
        count = 0;
    
    strcat(shstr, "Nama Item\tJumlah\tBerat (-)\n");
    for (new i = 0; i < MAX_INVENTORY; i ++) if (InventoryData[playerid][i][invExists])
    {
        strunpack(itemname, InventoryData[playerid][i][invItem]);
        strcat(shstr, sprintf("%s\t%d\t-\n", itemname, InventoryData[playerid][i][invQuantity]));
        ListedInventory[playerid][count ++] = i;
    }
    if(count)
    {
        AccountData[playerid][pStorageSelect] = 0;
        ShowPlayerDialog(playerid, DIALOG_INVENTORY, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Inventory", shstr, "Pilih", "Batal");
        return 1;
    }
    ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki item apapun di inventory!");
    return 1;
}

ItemCantUse(const item[])
{
    if(!strcmp(item, "Batu Kotor", true)) return 1;
    if(!strcmp(item, "Batu Bersih", true)) return 1;
    if(!strcmp(item, "Sampah Makanan", true)) return 1;
    //if(!strcmp(item, "Hiu", true)) return 1;
    if(!strcmp(item, "Umpan", true)) return 1;
    if(!strcmp(item, "Besi", true)) return 1;
    if(!strcmp(item, "Tembaga", true)) return 1;
    if(!strcmp(item, "Emas", true)) return 1;
    if(!strcmp(item, "Gold", true)) return 1;
    if(!strcmp(item, "Berlian", true)) return 1;
    if(!strcmp(item, "Alumunium", true)) return 1;
    if(!strcmp(item, "Plastik", true)) return 1;
    if(!strcmp(item, "Karet", true)) return 1;
    if(!strcmp(item, "Kayu", true)) return 1;
    if(!strcmp(item, "Kayu Potongan", true)) return 1;
    if(!strcmp(item, "Kayu Kemas", true)) return 1;
    if(!strcmp(item, "Benang", true)) return 1;
    if(!strcmp(item, "Kain", true)) return 1;
    if(!strcmp(item, "Pakaian", true)) return 1;
    if(!strcmp(item, "Botol", true)) return 1;
    if(!strcmp(item, "Petrol", true)) return 1;
    if(!strcmp(item, "Pure Oil", true)) return 1;
    if(!strcmp(item, "GAS", true)) return 1;
    if(!strcmp(item, "Ikan", true)) return 1;
    //if(!strcmp(item, "Penyu", true)) return 1;
    //if(!strcmp(item, "Ikan Tawar", true)) return 1;
    if(!strcmp(item, "Daging", true)) return 1;
    if(!strcmp(item, "Tanduk", true)) return 1;
    if(!strcmp(item, "Chip", true)) return 1;
    return 0;
}

forward OnPlayerUseItem(playerid, itemid, itemname[]);
public OnPlayerUseItem(playerid, itemid, itemname[])
{
    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
    if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
    if(ItemCantUse(itemname)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak dapat digunakan!");

    if(!strcmp(itemname, "Repair Kit", true))
    {
        new vehicleid = GetNearestVehicle(playerid, 3.5);
        if(vehicleid == INVALID_VEHICLE_ID)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di dekat kendaraan!");

        if(IsPlayerInAnyVehicle(playerid))
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak bisa melakukan ini di dalam kendaraan!");

        new Float:v_hp;
        GetVehicleHealth(vehicleid, v_hp);

        if(v_hp >= 750.0)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Mesin kendaraan masih dalam kondisi cukup baik!");

        AccountData[playerid][ActivityTime] = 0; 
        
        new engine, lights, alarm, doors, bonnet, boot, objective;
        GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
        SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, 1, boot, objective);

        ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
        
        ShowTDN(playerid, NOTIFICATION_INFO, "Sedang memperbaiki mesin & bodi...");
        Inventory_Close(playerid);
        pUseItemTimer[playerid] = SetTimerEx("FinishRepairKit", 1000, true, "dd", playerid, vehicleid);
        return 1;
    }
    if(AccountData[playerid][pInjured]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
    if(ItemCantUse(itemname)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Item tersebut tidak dapat digunakan!");
    if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, tunggu hingga progress selesai!");
    if(!strcmp(itemname, "Nasi Goreng", true))
    {
        if(AccountData[playerid][pHunger] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");
        if(Inventory_Count(playerid, "Sampah Makanan") >= 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Buang sampah anda terlebih dahulu!");

        AccountData[playerid][pHunger] += 45;
        Inventory_Remove(playerid, "Nasi Goreng");
        Inventory_Add(playerid, "Sampah Makanan", 2840);
        ShowItemBox(playerid, "Removed 1x", "Nasi Goreng", 2355);
        ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 2355, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil nasi goreng lalu memakannya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MAKAN");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Petasan", true))
    {
        if(!PlayerHasItem(playerid, "Korek Api")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki korek api!");
        ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        
        if(FireworkTimer[playerid] != -1)
        {
            KillTimer(FireworkTimer[playerid]);
            FireworkTimer[playerid] = -1;
            if(DestroyDynamicObject(FireworkObject[playerid])) FireworkObject[playerid] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
        }
        FireworkObject[playerid] = CreateDynamicObject(345, x, y, z - 0.4, 90.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), -1, 100.0, 100.0);
        FireworkTimer[playerid] = SetTimerEx("FireUp", 5000, false, "d", playerid);
        SetPVarFloat(playerid, "FireX", x);
        SetPVarFloat(playerid, "FireY", y);
        SetPVarFloat(playerid, "FireZ", z);

        Inventory_Close(playerid);
        Inventory_Remove(playerid, "Petasan");
    }
    else if(!strcmp(itemname, "Nasi Pecel", true))
    {
        if(AccountData[playerid][pHunger] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");
        if(Inventory_Count(playerid, "Sampah Makanan") >= 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Buang sampah anda terlebih dahulu!");

        AccountData[playerid][pHunger] += 30;
        Inventory_Remove(playerid, "Nasi Pecel");
        Inventory_Add(playerid, "Sampah Makanan", 2840);
        ShowItemBox(playerid, "Removed 1x", "Nasi Pecel", 2218);
        ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 2218, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil nasi pecel lalu memakannya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MAKAN");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Bibit Padi", true))
    {
        new wid = Weed_Nearest(playerid);
        new type = 1;

        if(!IsALadangField(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada diladang!");        
        if(AccountData[playerid][pJob] != JOB_FARMER) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu harus on-foot!");
        if(wid != -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Terlalu dekat dengan tanaman lain!");        
        if(Weed_Count() >= MAX_WEED) return ShowTDN(playerid, NOTIFICATION_ERROR, "Ladang sudah mencapai batas maskimal tanaman! (M: 1000)");
        
        Inventory_Remove(playerid, "Bibit Padi");
        SetTimerEx("PlantWeed", 3000, false, "dd", playerid, type);
        SendRPMeAboveHead(playerid, "Menanam bibit padi", X11_PLUM1);
        ApplyAnimation(playerid, "BOMBER", "BOM_Plant_Loop", 4.1, 1, 0, 0, 1, 0, 1);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Bibit Tebu", true))
    {
        new wid = Weed_Nearest(playerid);
        new type = 2;

        if(!IsALadangField(playerid))   
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada diladang!");

        if(AccountData[playerid][pJob] != JOB_FARMER)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");
        
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu harus on-foot!");

        if(wid != -1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Terlalu dekat dengan tanaman lain!");
        
        if(Weed_Count() >= MAX_WEED)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Ladang sudah mencapai batas maskimal tanaman! (M: 1000)");
        
        Inventory_Remove(playerid, "Bibit Tebu");
        SetTimerEx("PlantWeed", 3000, false, "dd", playerid, type);
        SendRPMeAboveHead(playerid, "Menanam bibit tebu", X11_PLUM1);
        ApplyAnimation(playerid, "BOMBER", "BOM_Plant_Loop", 4.1, 1, 0, 0, 1, 0, 1);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Bibit Cabe", true))
    {
        new wid = Weed_Nearest(playerid);
        new type = 3;

        if(!IsALadangField(playerid))   
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak berada diladang!");

        if(AccountData[playerid][pJob] != JOB_FARMER)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan seorang petani!");

        
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu harus on-foot!");

        if(wid != -1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Terlalu dekat dengan tanaman lain!");
        
        if(Weed_Count() >= MAX_WEED)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Ladang sudah mencapai batas maskimal tanaman! (M: 1000)");
        
        Inventory_Remove(playerid, "Bibit Cabe");
        SetTimerEx("PlantWeed", 3000, false, "dd", playerid, type);
        SendRPMeAboveHead(playerid, "Menanam bibit cabe", X11_PLUM1);
        ApplyAnimation(playerid, "BOMBER", "BOM_Plant_Loop", 4.1, 1, 0, 0, 1, 0, 1);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "KTA", true))
    {
        Inventory_Close(playerid);
        SendRPMeAboveHead(playerid, "Menunjukkan Kartu Tanda Anggota", X11_PLUM1);
        foreach(new i : Player) if (IsPlayerNearPlayer(playerid, i, 2.5))
        {
            ShowKTA(playerid, i);
        }
    }
    else if(!strcmp(itemname, "Smartphone", true))
    {
        Inventory_Close(playerid);
        ShowingSmartphone(playerid);
    }
    else if(!strcmp(itemname, "Race Tablet", true))
    {
        PlayerPlaySound(playerid, 21000, 0.0, 0.0, 0.0);
        Inventory_Close(playerid);
        ShowUiTablet(playerid);
        if(!IsPlayerInAnyVehicle(playerid)) {
            SetPlayerAttachedObject(playerid, 9, 19894, 6, 0.1070, 0.0230, 0.0920, -87.4999, -12.0999, 163.8000, 1.0000, 1.0000, 1.0000, 0xFFFFFFFF, 0xFFFFFFFF);
            ApplyAnimation(playerid, "CASINO", "CARDS_LOOP", 4.1, 0, 0, 0, 1, 0, 1);
        }
    }
    else if(!strcmp(itemname, "Senter", true))
    {
        if (IsPlayerInAnyVehicle(playerid))
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada diluar kendaraan!");
        
        if (AccountData[playerid][ActivityTime] != 0)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menggunakan ini ketika progress acivity berjalan!");
        
        if (AccountData[playerid][pInjured])
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukan ini ketika sedang pingsan!");
        
        if (AccountData[playerid][phoneShown])
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang membuka Smartphone!");
        
        switch (AccountData[playerid][pFlashShown])
        {
            case false:
            {
                AccountData[playerid][pFlashShown] = true;
                ApplyAnimationEx(playerid, "ped", "phone_talk", 1.1, 1, 1, 1, 1, 1, 1);
                SetPlayerAttachedObject(playerid, JOB_SLOT, 18641, 6,  0.080999, 0.042000, -0.034000,  0.000000, 0.000000, 0.000000,  1.000000, 1.000000, 1.000000); // FLashlight Objects
                SendRPMeAboveHead(playerid, "Mengambil senter dari dalam tas", X11_PLUM1);
            }
            case true:
            {
                AccountData[playerid][pFlashShown] = false;
                StopLoopingAnim(playerid);
                RemovePlayerAttachedObject(playerid, JOB_SLOT);
                if (AccountData[playerid][pFlashOn]) {
                    AccountData[playerid][pFlashOn] = false;
                    RemovePlayerAttachedObject(playerid, 5);
                }
                SendRPMeAboveHead(playerid, "Memasukkan senter ke dalam tas", X11_PLUM1);
            }
        }
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Radio", true))
    {
        if(!PlayerHasItem(playerid, "Radio")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki radio!");
        if(IsPlayerInWater(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat membuka Radio di dalam air!");

        SendRPMeAboveHead(playerid, "Membuka Radio miliknya.", X11_PLUM1);
        if(!IsPlayerInAnyVehicle(playerid))
        {
            ApplyAnimation(playerid, "ped", "Jetpack_Idle", 4.1, 0, 0, 0, 1, 0, 1);
            SetPlayerAttachedObject(playerid, 9, 19942, 5, 0.043000, 0.022999, -0.006000, -112.000022, -34.900020, -8.500002, 1.000000, 1.000000, 1.000000);
        }
        
        Inventory_Close(playerid);
        RadioTextdrawToggle(playerid, true);
        SelectTextDraw(playerid, 0xFF9999FF);
        return 1;
    }
    else if(!strcmp(itemname, "Backpack", true))
    {
        if(!IsPlayerInRangeOfPoint(playerid, 10.0, 1675.340087, -2326.237548, 13.546875)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus berada di luar bandara!");
        if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
        SendRPMeAboveHead(playerid, "Membuka Backpack dan mengeluarkan barangnya", X11_PLUM1);
    
        AccountData[playerid][ActivityTime] = 1;
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMBUKA");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
        AccountData[playerid][pOpenBackpackTimer] = SetTimerEx("OpeningBackpack", 1000, true, "i", playerid);
    }
    else if(!strcmp(itemname, "Bubur Pedas", true))
    {
        if(AccountData[playerid][pHunger] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");
        if(Inventory_Count(playerid, "Sampah Makanan") >= 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Buang sampah anda terlebih dahulu!");

        AccountData[playerid][pHunger] += 20;
        Inventory_Remove(playerid, "Bubur Pedas");
        Inventory_Add(playerid, "Sampah Makanan", 2840);
        ShowItemBox(playerid, "Removed 1x", "Bubur Pedas", 19568);
        ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 19568, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil bubur pedas lalu memakannya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MAKAN");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Jus Apel", true))
    {
        if(AccountData[playerid][pThirst] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");
        if(Inventory_Count(playerid, "Sampah Makanan") >= 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Buang sampah anda terlebih dahulu!");

        AccountData[playerid][pThirst] += 20;
        Inventory_Remove(playerid, "Jus Apel");
        Inventory_Add(playerid, "Sampah Makanan", 2840);
        ShowItemBox(playerid, "Removed 1x", "Jus Apel", 19564);
        ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 19564, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil jus apel lalu meminumnya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MINUM");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Susu Fresh", true))
    {
        if(Inventory_Count(playerid, "Sampah Makanan") >= 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Buang sampah mu terlebih dahulu");

        if(GetPlayerDrunkLevel(playerid) > 0)
        {
            AccountData[playerid][pThirst] += 15;
            SetPlayerDrunkLevel(playerid, 0);
            Inventory_Remove(playerid, "Susu Fresh");
            Inventory_Add(playerid, "Sampah Makanan", 2840);
            ShowItemBox(playerid, "Removed 1x", "Susu Fresh", 19569);
            ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);

            ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
            SetPlayerAttachedObject(playerid, 9, 19569, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
            SendRPMeAboveHead(playerid, "Mengambil susu fresh lalu meminumnya", X11_PLUM1);

            AccountData[playerid][ActivityTime] = 1;
            pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MINUM");
            ShowProgressBar(playerid);
        }
        else 
        {
            AccountData[playerid][pThirst] += 15;
            Inventory_Remove(playerid, "Susu Fresh");
            Inventory_Add(playerid, "Sampah Makanan", 2840);
            ShowItemBox(playerid, "Removed 1x", "Susu Fresh", 19569);
            ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);

            ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
            SetPlayerAttachedObject(playerid, 9, 19569, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
            SendRPMeAboveHead(playerid, "Mengambil susu fresh lalu meminumnya", X11_PLUM1);

            AccountData[playerid][ActivityTime] = 1;
            pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
            PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MINUM");
            ShowProgressBar(playerid);
        }
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Es Teh", true))
    {
        if(AccountData[playerid][pThirst] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");
        if(Inventory_Count(playerid, "Sampah Makanan") >= 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Buang sampah anda terlebih dahulu!");

        AccountData[playerid][pThirst] += 25;
        Inventory_Remove(playerid, "Es Teh");
        Inventory_Add(playerid, "Sampah Makanan", 2840);
        ShowItemBox(playerid, "Removed 1x", "Es Teh", 1546);
        ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 1546, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil es teh lalu meminumnya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MINUM");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Nasi Uduk", true))
    {
        if(AccountData[playerid][pHunger] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");
        if(Inventory_Count(playerid, "Sampah Makanan") >= 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Buang sampah anda terlebih dahulu!");

        AccountData[playerid][pHunger] += 15;
        Inventory_Remove(playerid, "Nasi Uduk");
        Inventory_Add(playerid, "Sampah Makanan", 2840);
        ShowItemBox(playerid, "Removed 1x", "Nasi Uduk", 19567);
        ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 19567, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil nasi uduk lalu memakannya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MAKAN");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Tahu Bulat", true))
    {
        if(AccountData[playerid][pHunger] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");
        if(Inventory_Count(playerid, "Sampah Makanan") >= 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Buang sampah anda terlebih dahulu!");

        AccountData[playerid][pHunger] += 5;
        Inventory_Remove(playerid, "Tahu Bulat");
        Inventory_Add(playerid, "Sampah Makanan", 2840);
        ShowItemBox(playerid, "Removed 1x", "Tahu Bulat", 19574);
        ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 19574, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil tahu bulat lalu memakannya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MAKAN");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Kopi Kenangan", true))
    {
        if(AccountData[playerid][pThirst] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");
        if(Inventory_Count(playerid, "Sampah Makanan") >= 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Buang sampah anda terlebih dahulu!");

        AccountData[playerid][pThirst] += 45;
        Inventory_Remove(playerid, "Kopi Kenangan");
        Inventory_Add(playerid, "Sampah Makanan", 2840);
        ShowItemBox(playerid, "Removed 1x", "Kopi Kenangan", 19835);
        ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 19835, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil kopi kenangan lalu meminumnya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MINUM");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Air Mineral", true))
    {
        if(AccountData[playerid][pThirst] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");
        if(Inventory_Count(playerid, "Sampah Makanan") >= 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Buang sampah anda terlebih dahulu!");

        AccountData[playerid][pThirst] += 25;
        Inventory_Remove(playerid, "Air Mineral");
        Inventory_Add(playerid, "Sampah Makanan", 2840);
        ShowItemBox(playerid, "Removed 1x", "Air Mineral", 19570);
        ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 19570, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil air mineral lalu meminumnya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MINUM");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Choco Matcha", true))
    {
        if(AccountData[playerid][pThirst] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");
        if(Inventory_Count(playerid, "Sampah Makanan") >= 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Buang sampah anda terlebih dahulu!");

        AccountData[playerid][pThirst] += 20;
        Inventory_Remove(playerid, "Choco Matcha");
        Inventory_Add(playerid, "Sampah Makanan", 2840);
        ShowItemBox(playerid, "Removed 1x", "Choco Matcha", 1667);
        ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 1667, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil choco matcha lalu meminumnya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MINUM");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Teh Jeruk", true))
    {
        if(AccountData[playerid][pThirst] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");
        if(Inventory_Count(playerid, "Sampah Makanan") >= 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Buang sampah anda terlebih dahulu!");

        AccountData[playerid][pThirst] += 20;
        Inventory_Remove(playerid, "Teh Jeruk");
        Inventory_Add(playerid, "Sampah Makanan", 2840);
        ShowItemBox(playerid, "Removed 1x", "Teh Jeruk", 19563);
        ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 19563, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil teh jeruk lalu meminumnya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MINUM");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Kebab A5", true))
    {
        if(AccountData[playerid][pHunger] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");
        if(Inventory_Count(playerid, "Sampah Makanan") >= 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Buang sampah anda terlebih dahulu!");

        AccountData[playerid][pHunger] += 20;
        Inventory_Remove(playerid, "Kebab A5");
        Inventory_Add(playerid, "Sampah Makanan", 2840);
        ShowItemBox(playerid, "Removed 1x", "Kebab A5", 2769);
        ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 2769, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil kebab a5 lalu memakannya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MAKAN");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Bakso", true))
    {
        if(AccountData[playerid][pHunger] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");
        if(Inventory_Count(playerid, "Sampah Makanan") >= 15) return ShowTDN(playerid, NOTIFICATION_ERROR, "Buang sampah anda terlebih dahulu!");

        AccountData[playerid][pHunger] += 20;
        Inventory_Remove(playerid, "Bakso");
        Inventory_Add(playerid, "Sampah Makanan", 2840);
        ShowItemBox(playerid, "Removed 1x", "Bakso", 19567);
        ShowItemBox(playerid, "Received 1x", "Sampah Makanan", 2840);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 19567, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil bakso lalu memakannya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MAKAN");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Bandage", true))
    {
        new Float:health;
        GetPlayerHealth(playerid, health);
        
        if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
        if(health >= 95.0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");

        ApplyAnimation(playerid, "COP_AMBIENT", "Copbrowse_loop", 4.1, 1, 0, 0, 0, 0, 1);
        Inventory_Close(playerid);
        SendRPMeAboveHead(playerid, "Mengambil perban lalu menggunakannya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("UseBandage", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "USE BANDAGE");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Alprazolam", true))
    {
        if(AccountData[playerid][pStress] < 1) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda tidak sedang stress!");
        if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
        
        ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SendRPMeAboveHead(playerid, "Mengambil Alprazolam lalu menggunakannya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "i", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "USING");
        ShowProgressBar(playerid);

        AccountData[playerid][pStress] -= 25;
        Inventory_Remove(playerid, "Alprazolam");
        ShowItemBox(playerid, "Removed 1x", "Alprazolam", 1241);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Marijuana", true))
    {
        if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
        
        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("UseMarijuana", 1000, true, "i", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "USING");
        ShowProgressBar(playerid);

        new Float: Armour;
        GetPlayerArmour(playerid, Armour);
        Armour += 15.0;
        if(Armour >= 15.0)
        {
            Armour = 15.0;
        }
        SetPlayerArmourEx(playerid, Armour);
        ApplyAnimation(playerid, "SMOKING", "M_smk_drag", 4.1, 1, 0, 0, 0, 0, 1);
        SendRPMeAboveHead(playerid, "Mengambil marijuana lalu sebat", X11_PLUM1);
        ShowItemBox(playerid, "Removed 1x", "Marijuana", 1575);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Uranium", true))
    {
        if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
        
        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("UseUranium", 1000, true, "i", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "USING");
        ShowProgressBar(playerid);

        ApplyAnimation(playerid, "VENDING", "VEND_Drink2_P", 4.1, 1, 0, 0, 0, 0, 1);
        SendRPMeAboveHead(playerid, "Mengambil uranium lalu menggunakannya", X11_PLUM1);
        ShowItemBox(playerid, "Removed 1x", "Uranium", 2958);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Kevlar", true))
    {
        if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
        new Float:AM;
        GetPlayerArmour(playerid, AM);
        if(AM >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kevlar anda masih di 95%, tidak dapat menggunakan lagi!");

        pUseItemTimer[playerid] = SetTimerEx("UseKevlar", 1000, true, "i", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMAKAI KEVLAR");
        ShowProgressBar(playerid);
        
        AccountData[playerid][ActivityTime] = 1;
        ApplyAnimationEx(playerid, "COP_AMBIENT", "Copbrowse_loop", 4.1, 1, 0, 0, 0, 0, 1);
        SendRPMeAboveHead(playerid, "Mengambil Kevlar lalu menggunakannya", X11_PLUM1);
        ShowItemBox(playerid, "Removed 1x", "Kevlar", 19515);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Rokok", true))
    {
        if(!PlayerHasItem(playerid, "Korek Api")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki korek api!");

        Inventory_Remove(playerid, "Rokok");
        ShowItemBox(playerid, "Removed 1x", "Rokok", 19896);
        ApplyAnimation(playerid, "SMOKING", "M_smk_in", 4.1, 0, 0, 0, 0, 0, 1);
        SendRPMeAboveHead(playerid, "Mengambil sebatang rokok lalu membakarnya menggunakan korek api", X11_PLUM1);
        SendClientMessageEx(playerid, -1, ""WHITE"[i] Gunakan "GREEN"`Y`"WHITE" untuk menghisap rokok "YELLOW"`/stopsmoke'`"WHITE" untuk membuang rokok");
        Inventory_Close(playerid);

        IsPlayerSmoking[playerid] = true;
        CountSmoking[playerid] = 10;
    }   
    else if(!strcmp(itemname, "Jerigen", true))
    {
        new vehid = GetNearestVehicleToPlayer(playerid, 3.0, false);
        if(vehid == INVALID_VEHICLE_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak didekat kendaraan manapun!");
    
        Info(playerid, ""GREEN"[Y] "WHITE"Untuk mengisi bbm");
        AccountData[playerid][pJerigenUse] = true;
        AccountData[playerid][pTempVehID] = vehid;

        Inventory_Remove(playerid, "Jerigen");
        ShowItemBox(playerid, "Removed 1x", "Jerigen", 1650);
        SetPlayerAttachedObject(playerid, 9, 1650, 6, 0.127, 0.015, 0.042, 0.000, -96.900, -11.000, 1.000, 1.000, 1.000);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Tools Kit", true))
    {
        if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");

        new vehid = -1, bool: found = false;
        if((vehid = Vehicle_Nearest(playerid)) != -1)
        {
            if(PlayerVehicle[vehid][pVehExists] && IsValidVehicle(PlayerVehicle[vehid][pVehPhysic]))
            {
                AccountData[playerid][ActivityTime] = 1;
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMPERBAIKI KENDARAAN");
                ShowProgressBar(playerid);

                ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                Inventory_Close(playerid);
                pUseItemTimer[playerid] = SetTimerEx("UsingToolkit", 1000, true, "dd", playerid, PlayerVehicle[vehid][pVehPhysic]);
                found = true;
            }
        }
        if(!found) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan apapun disekitar!");
    }
    else if(!strcmp(itemname, "Repair Kit", true))
    {
        if(AccountData[playerid][ActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_WARNING, "Anda sedang melakukan sesuatu, harap tunggu!");
        if(AccountData[playerid][pFaction] != FACTION_BENGKEL) return ShowTDN(playerid, NOTIFICATION_ERROR, "Hanya anggota Bengkel yang dapat menggunakan ini!");

        new vehid = -1, bool: found = false;
        if((vehid = Vehicle_Nearest(playerid)) != -1)
        {
            if(PlayerVehicle[vehid][pVehExists] && IsValidVehicle(PlayerVehicle[vehid][pVehPhysic]))
            {
                AccountData[playerid][ActivityTime] = 1;
                PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MEMPERBAIKI KENDARAAN");
                ShowProgressBar(playerid);

                ApplyAnimationEx(playerid, "BD_FIRE", "wash_up", 4.1, 1, 0, 0, 0, 0, 1);
                Inventory_Close(playerid);
                pUseItemTimer[playerid] = SetTimerEx("UsingRepairKit", 1000, true, "dd", playerid, PlayerVehicle[vehid][pVehPhysic]);
                found = true;
            }
        }
        if(!found) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada kendaraan apapun disekitar!");
    }
    else if(!strcmp(itemname, "Boombox", true))
    {
        new str[128], Float:BBCoord[4], pNames[MAX_PLAYER_NAME];
        GetPlayerPos(playerid, BBCoord[0], BBCoord[1], BBCoord[2]);
        GetPlayerFacingAngle(playerid, BBCoord[3]);
        SetPVarFloat(playerid, "BBX", BBCoord[0]);
        SetPVarFloat(playerid, "BBY", BBCoord[1]);
        SetPVarFloat(playerid, "BBZ", BBCoord[2]);
        GetPlayerName(playerid, pNames, sizeof(pNames));
        BBCoord[0] += (2 * floatsin(-BBCoord[3], degrees));
        BBCoord[1] += (2 * floatcos(-BBCoord[3], degrees));
        BBCoord[2] -= 1.0;
        if(GetPVarInt(playerid, "PlacedBB")) return SendClientMessageEx(playerid, -1, "{00ff00}[!]{ffffff}: Kamu Sudah Memasang Boombox");
        foreach(new i : Player)
        {
            if(GetPVarType(i, "PlacedBB"))
            {
                if(IsPlayerInRangeOfPoint(playerid, 30.0, GetPVarFloat(i, "BBX"), GetPVarFloat(i, "BBY"), GetPVarFloat(i, "BBZ")))
                {
                    SendClientMessageEx(playerid, COLOR_WHITE, "{00ff00}[!]{ffffff}: Tidak dapat memasang, karena terdapat boombox orang lain disini");
                    return 1;
                }
            }
        }
        SendRPMeAboveHead(playerid, "Mengeluarkan Boombox", X11_PLUM1);
        SetPVarInt(playerid, "PlacedBB", CreateDynamicObject(2103, BBCoord[0], BBCoord[1], BBCoord[2], 0.0, 0.0, 0.0, .worldid = GetPlayerVirtualWorld(playerid), .interiorid = GetPlayerInterior(playerid)));
        format(str, sizeof(str), "{ffffff}Pemilik: {ffff00}%s", pNames);
        SetPVarInt(playerid, "BBLabel", _:CreateDynamic3DTextLabel(str, COLOR_YELLOW, BBCoord[0], BBCoord[1], BBCoord[2]+0.6, 5, .worldid = GetPlayerVirtualWorld(playerid), .interiorid = GetPlayerInterior(playerid)));
        SetPVarInt(playerid, "BBArea", CreateDynamicSphere(BBCoord[0], BBCoord[1], BBCoord[2], 30.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid)));
        SetPVarInt(playerid, "BBInt", GetPlayerInterior(playerid));
        SetPVarInt(playerid, "BBVW", GetPlayerVirtualWorld(playerid));
        ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0,0,0,0,0);
        ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0,0,0,0,0);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Api Unggun", true))
    {
        new Float:x, Float:y, Float:z, Float:angle;
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, angle);

        x += (2 * floatsin(-angle, degrees));
        y += (2 * floatcos(-angle, degrees));
        z -= 1.0;

        for(new i = 0; i < MAX_FIRE; i++)
        {
            if(ApiUnggun[i][aUsed] &&
            IsPlayerInRangeOfPoint(playerid, 5.0, ApiUnggun[i][aX], ApiUnggun[i][aY], ApiUnggun[i][aZ]))
            {
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat memasang, karena terdapat Api Unggun orang lain disini");
            }
        }

        CreateApiUnggun(playerid, x, y, z);
        SendRPMeAboveHead(playerid, "Menyalakan Api Unggun", X11_PLUM1);
        ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0,0,0,0,0);

        Inventory_Remove(playerid, "Api Unggun", 1);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Ikan Tawar", true))
    {
        new fireIndex = GetNearestFire(playerid);
        if(fireIndex == -1)
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Api Unggun di dekatmu!");
        }

        for(new i = 0; i < MAX_COOKING; i++) 
            if(Cooking[i][cUsed] && Cooking[i][cPlayer] == playerid)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu sudah memasak sesuatu!");

        if(Inventory_Count(playerid, "Ikan Tawar") < 1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory tidak memiliki Ikan Tawar!");

        SendRPMeAboveHead(playerid, "Mulai membakar ikan", X11_PLUM1);
        ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0,0,0,0,0);

        new objectid = CreateDynamicObject(2806, ApiUnggun[fireIndex][aX], ApiUnggun[fireIndex][aY], ApiUnggun[fireIndex][aZ]+0.5, 0.0, 0.0, 0.0,
            .worldid = ApiUnggun[fireIndex][aVW], .interiorid = ApiUnggun[fireIndex][aInt]);

        for(new i = 0; i < MAX_COOKING; i++)
        {
            if(!Cooking[i][cUsed])
            {
                Cooking[i][cPlayer] = playerid;
                Cooking[i][cFireIndex] = fireIndex;
                Cooking[i][cFishType] = 0;
                Cooking[i][cObject] = objectid;
                Cooking[i][cUsed] = 1;
                Cooking[i][cTimer] = SetTimerEx("CookingDone", 10000, false, "i", i);
                break;
            }
        }
        Inventory_Remove(playerid, "Ikan Tawar", 1);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Daging Ikan Tawar", true))
    {
        if(AccountData[playerid][pHunger] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");

        new rand = RandomEx(1, 5);
        AccountData[playerid][pHunger] += rand;
        Inventory_Remove(playerid, "Daging Ikan Tawar");
        ShowItemBox(playerid, "Removed 1x", "Daging Ikan Tawar", 2806);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 2806, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil daging ikan tawar lalu memakannya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MAKAN");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Hiu", true))
    {
        new fireIndex = GetNearestFire(playerid);
        if(fireIndex == -1)
        {
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
            SetPlayerAttachedObject(playerid, 9, 1608, 1, 0.395000, 0.380999, -0.510999, 153.199951, 84.100151, -67.899971, 0.262999, 0.345000, 0.390000);
            Info(playerid, "Kamu sedang membawa seekor "YELLOW"Hiu. "GRAY"Gunakan "YELLOW"[Y] "WHITE"untuk memasukan kembali hiu ke inventory");
            Inventory_Close(playerid);
            Inventory_Remove(playerid, "Hiu", 1);
            pHiu[playerid] = true;
            return 1;
        }

        for(new i = 0; i < MAX_COOKING; i++) 
            if(Cooking[i][cUsed] && Cooking[i][cPlayer] == playerid)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu sudah memasak sesuatu!");

        if(Inventory_Count(playerid, "Hiu") < 1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory tidak memiliki Hiu!");
 
        SendRPMeAboveHead(playerid, "Mulai membakar Hiu", X11_PLUM1);
        ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0,0,0,0,0);

        new objectid = CreateDynamicObject(2806, ApiUnggun[fireIndex][aX], ApiUnggun[fireIndex][aY], ApiUnggun[fireIndex][aZ]+0.5, 0.0, 0.0, 0.0,
            .worldid = ApiUnggun[fireIndex][aVW], .interiorid = ApiUnggun[fireIndex][aInt]);

        for(new i = 0; i < MAX_COOKING; i++)
        {
            if(!Cooking[i][cUsed])
            {
                Cooking[i][cPlayer] = playerid;
                Cooking[i][cFireIndex] = fireIndex;
                Cooking[i][cFishType] = 1;
                Cooking[i][cObject] = objectid;
                Cooking[i][cUsed] = 1;
                Cooking[i][cTimer] = SetTimerEx("CookingDone1", 10000, false, "i", i);
                break;
            }
        }
        Inventory_Remove(playerid, "Hiu", 1);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Ayam Potong", true))
    {
        new fireIndex = GetNearestFire(playerid);
        if(fireIndex == -1)
        {
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Api Unggun di dekatmu!");
        }

        for(new i = 0; i < MAX_COOKING; i++) 
            if(Cooking[i][cUsed] && Cooking[i][cPlayer] == playerid)
                return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu sudah memasak sesuatu!");

        if(Inventory_Count(playerid, "Ayam Potong") < 1)
            return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory tidak memiliki Ayam Potong!");

        SendRPMeAboveHead(playerid, "Mulai membakar Ayam Potong", X11_PLUM1);
        ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0,0,0,0,0);

        new objectid = CreateDynamicObject(2806, ApiUnggun[fireIndex][aX], ApiUnggun[fireIndex][aY], ApiUnggun[fireIndex][aZ]+0.5, 0.0, 0.0, 0.0,
            .worldid = ApiUnggun[fireIndex][aVW], .interiorid = ApiUnggun[fireIndex][aInt]);

        for(new i = 0; i < MAX_COOKING; i++)
        {
            if(!Cooking[i][cUsed])
            {
                Cooking[i][cPlayer] = playerid;
                Cooking[i][cFireIndex] = fireIndex;
                Cooking[i][cFishType] = 2;
                Cooking[i][cObject] = objectid;
                Cooking[i][cUsed] = 1;
                Cooking[i][cTimer] = SetTimerEx("CookingDone2", 10000, false, "i", i);
                break;
            }
        }
        Inventory_Remove(playerid, "Ayam Potong", 1);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Daging Hiu", true))
    {
        if(AccountData[playerid][pHunger] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");

        new rand = RandomEx(5, 10);
        AccountData[playerid][pHunger] += rand;
        Inventory_Remove(playerid, "Daging Hiu");
        ShowItemBox(playerid, "Removed 1x", "Daging Hiu", 2806);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 2806, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil Daging Hiu lalu memakannya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MAKAN");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    else if(!strcmp(itemname, "Daging Ayam Goreng", true))
    {
        if(AccountData[playerid][pHunger] >= 95) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memerlukannya saat ini!");

        new rand = RandomEx(5, 15);
        AccountData[playerid][pHunger] += rand;
        Inventory_Remove(playerid, "Daging Ayam Goreng");
        ShowItemBox(playerid, "Removed 1x", "Daging Ayam Goreng", 2806);

        ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SetPlayerAttachedObject(playerid, 9, 2806, 6, 0.038, 0.014, 0.031, 0.000, 0.000, 0.000, 1.000, 1.000, 1.000);
        SendRPMeAboveHead(playerid, "Mengambil Daging Ayam Goreng lalu memakannya", X11_PLUM1);

        AccountData[playerid][ActivityTime] = 1;
        pUseItemTimer[playerid] = SetTimerEx("EatingProgress", 1000, true, "d", playerid);
        PlayerTextDrawSetString(playerid, ProgressBar[playerid][2], "MAKAN");
        ShowProgressBar(playerid);
        Inventory_Close(playerid);
    }
    return true;
}

CMD:asetitem(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

	new
		item[32],
		amount;
	if (sscanf(params, "ds[32]", amount, item))
	    return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setitem [jumlah] [nama item]");
	for (new i = 0; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], item, true))
	{
        Inventory_Add(playerid, g_aInventoryItems[i][e_InventoryItem], g_aInventoryItems[i][e_InventoryModel], amount);
        return SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" men-set item %s sejumlah %d untuk diri sendiri", AccountData[playerid][pAdminname], item, amount);
        // return SendClientMessageEx(playerid, X11_GRAY, "[AdmCmd] berhasil mengset item %s sejumlah %d", item, amount);
	}
	ShowTDN(playerid, NOTIFICATION_WARNING, "Invalid Item Name, Cek /itemlist");
    PlayerPlaySound(playerid, 5205, 0, 0, 0);
	return 1;
}

CMD:aremoveinv(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    new otherid, itemname[32];
    if(sscanf(params, "us[32]", otherid, itemname)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/aremoveinv [name/playerid] [item name]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    if(!PlayerHasItem(otherid, itemname)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak memiliki item tersebut!");
    
    Inventory_Remove(otherid, itemname, Inventory_Count(otherid, itemname));
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menghapus item %s dari inventory "YELLOW"%s(%d)", AccountData[playerid][pAdminname], itemname, AccountData[otherid][pName], otherid);
    SendClientMessageEx(otherid, X11_ARWIN, "[AdmCmd] "RED"%s"ARWIN1" Menghapus item %s dari inventory anda", AccountData[playerid][pAdminname], itemname, AccountData[otherid][pName], otherid);
    return 1;
}

CMD:giveitem(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    new otherid, itemname[32], amount;
    if(sscanf(params, "uds[32]", otherid, amount, itemname)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/giveitem [name/playerid] [amount] [item name]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");
    for(new i = 0; i < sizeof(g_aInventoryItems); i++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], itemname, true))
    {
        Inventory_Add(otherid, g_aInventoryItems[i][e_InventoryItem], g_aInventoryItems[i][e_InventoryModel], amount);
        SendClientMessageEx(otherid, X11_ARWIN, "[AdmCmd]"RED" %s"ARWIN1" telah memberikan anda "YELLOW"%s"ARWIN1" sejumlah "YELLOW"%d", AccountData[playerid][pAdminname], itemname, amount);
        return SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" memberikan "YELLOW"%s(%d)"ARWIN1" %s sejumlah %d", AccountData[playerid][pAdminname], AccountData[otherid][pName], otherid, itemname, amount);
    }
	ShowTDN(playerid, NOTIFICATION_WARNING, "Invalid Item Name, Cek /itemlist");

    static shstr[125];
	format(shstr, sizeof(shstr), "Menggunakan cmd /giveitem %s(%d amount) kepada pemain %s.", itemname, amount, AccountData[otherid][pName]);
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), shstr);
	return 1;
}

alias:giveitemall("gim")
CMD:giveitemall(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5) return PermissionError(playerid);

    new itemname[32], amounts, bool: found = false;
    if(sscanf(params, "ds[32]", amounts, itemname)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/giveitemall [amounts] [item name]");
    for (new i = 0; i < sizeof(g_aInventoryItems); i++)
    {
        if(!strcmp(g_aInventoryItems[i][e_InventoryItem], itemname, true))
        {
            foreach(new player : Player) if (IsPlayerConnected(player) && SQL_IsCharacterLogged(player))
            {
                Inventory_Add(player, g_aInventoryItems[i][e_InventoryItem], g_aInventoryItems[i][e_InventoryModel], amounts);
                ShowItemBox(player, sprintf("Received %dx", amounts), g_aInventoryItems[i][e_InventoryItem], g_aInventoryItems[i][e_InventoryModel]);
            }
            SendClientMessageToAllEx(X11_ARWIN, "[AdmCmd]"RED" %s"ARWIN1" Memberikan "YELLOW"%s"ARWIN1" sejumlah "YELLOW"%d"ARWIN1" kepada seluruh pemain online", AccountData[playerid][pAdminname], g_aInventoryItems[i][e_InventoryItem], amounts);
            found = true;
        }
    }
    if(!found) ShowTDN(playerid, NOTIFICATION_WARNING, "Item tidak ditemukan, gunakan '/itemlist'");

    static shstr[125];
	format(shstr, sizeof(shstr), "Menggunakan cmd /giveitemall %s(%d) kepada seluruh pemain online.", itemname, amounts);
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), shstr);
    return 1;
}

CMD:setitem(playerid, params[])
{
    new 
        userid,
        item[32],
        amount;
    
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);
    
    if(sscanf(params,"uds[32]", userid, amount, item))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setitem [playerid/Name] [jumlah] [nama item]");

    for(new i = 0; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], item, true))
    {
        Inventory_Set(userid, g_aInventoryItems[i][e_InventoryItem], g_aInventoryItems[i][e_InventoryModel], amount);

        SendClientMessageEx(userid, X11_ARWIN, "[AdmCmd]"RED" %s"ARWIN1" memberikan anda %s sejumlah %d", AccountData[playerid][pAdminname], item, amount);
        return SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" memberikan "YELLOW"%s(%d)"ARWIN1" %s sejumlah %d", AccountData[playerid][pAdminname], AccountData[userid][pName], userid, item, amount);
    }
    ShowTDN(playerid, NOTIFICATION_WARNING, "Invalid item name~n~gunakan ~y~'/itemlist'~w~ untuk melihat list");
   
    static shstr[125];
	format(shstr, sizeof(shstr), "Menggunakan cmd /setitem %s(%d amount) kepada pemain %s.", item, amount, AccountData[userid][pName]);
	AddAdminLog(AccountData[playerid][pName], AccountData[playerid][pUCP], GetStaffRank(playerid), shstr);
	return 1;
}

CMD:clearitems(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 6) return PermissionError(playerid);

    new otherid;
    if(sscanf(params, "u", otherid)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/clearitems [name/playerid]");
    if(!IsPlayerConnected(otherid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke server!");

    Inventory_Clear(otherid);
    SendClientMessageEx(otherid, X11_ARWIN, "[AdmCmd] Admin "RED"%s "ARWIN1"telah menghapus barang barang di inventory anda.", GetAdminName(playerid));
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menghapus barang inventory milik "YELLOW"%s(%d).", GetAdminName(playerid), GetRPName(otherid), otherid);
    return 1;
}

CMD:itemlist(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1) return PermissionError(playerid);

    new
        string[1024];

    if (!strlen(string)) {
        for (new i = 0; i < sizeof(g_aInventoryItems); i ++) {
            format(string, sizeof(string), "%s%s\n", string, g_aInventoryItems[i][e_InventoryItem]);
        }
    }
    return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Nama Barang", string, "Select", "Cancel");
}

forward LoadPlayerInventory(playerid);
public LoadPlayerInventory(playerid)
{
    new rows = cache_num_rows(), itemname[128];
    if(rows)
    {
        for(new i = 0; i < rows; i ++)
        {
            InventoryData[playerid][i][invExists] = true;
            cache_get_value_name_int(i, "invID", InventoryData[playerid][i][invID]);
            cache_get_value_name_int(i, "invModel", InventoryData[playerid][i][invModel]);
            cache_get_value_name_int(i, "invQuantity", InventoryData[playerid][i][invQuantity]);
            cache_get_value_name(i, "invItem", itemname, sizeof(itemname));
            strpack(InventoryData[playerid][i][invItem], itemname, 32 char);
        }
    }
    return 1;
}

FUNC::OnInventoryAdd(playerid, itemid)
{
	InventoryData[playerid][itemid][invID] = cache_insert_id();
	return 1;
}


forward OpeningBackpack(playerid);
public OpeningBackpack(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(AccountData[playerid][pOpenBackpackTimer]);
        AccountData[playerid][pOpenBackpackTimer] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(IsPlayerInjured(playerid))
    {
        KillTimer(AccountData[playerid][pOpenBackpackTimer]);
        AccountData[playerid][pOpenBackpackTimer] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 115)
    {
        KillTimer(AccountData[playerid][pOpenBackpackTimer]);
        AccountData[playerid][pOpenBackpackTimer] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            ClearAnimations(playerid, 1);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        }

        Inventory_Remove(playerid, "Backpack");
        Inventory_Add(playerid, "Smartphone", 18870, 1);
        Inventory_Add(playerid, "Nasi Goreng", 2355, 10);
        Inventory_Add(playerid, "Es Teh", 1546, 10);
        ShowItemBox(playerid, "Received 1x", "Smartphone", 18870);
        ShowItemBox(playerid, "Received 10x", "Nasi Goreng", 2355);
        ShowItemBox(playerid, "Received 10x", "Es Teh", 1546);
        AccountData[playerid][pVip] = 2;
		AccountData[playerid][pVipTime] = gettime() + (3 * 24 * 60 * 60);
        new Float:x, Float:y, Float:z, Float:a;
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);
        Vehicle_Backpack(playerid, 468, FACTION_NONE, x, y, z, a, 0, 0, 10000);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 23;

        new Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime]*110/115;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward UseUranium(playerid);
public UseUranium(playerid)
{
    if(!IsPlayerConnected(playerid))
	{
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(AccountData[playerid][pInjured])
	{
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 5)
	{
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            ClearAnimations(playerid, 1);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        }

        static Float:health;
        GetPlayerHealth(playerid, health);
        health += 40;
        if(health > 100)
        {
            health = 100.0;
        }

        SetPlayerHealthEx(playerid, health);
        AccountData[playerid][pHunger] += 50;
        AccountData[playerid][pThirst] += 50;
        Inventory_Remove(playerid, "Uranium");
        ShowItemBox(playerid, "Removed 1x", "Uranium", 2958);
	}
	else
	{
		AccountData[playerid][ActivityTime] ++;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime] * 103/5;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		return 0;
	}
	return 1;
}

forward UseMarijuana(playerid);
public UseMarijuana(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(AccountData[playerid][pInjured])
	{
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 5)
	{
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            ClearAnimations(playerid, 1);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        }

		Inventory_Remove(playerid, "Marijuana");
		AccountData[playerid][pStress] -= 25;
        TextDrawHideForPlayer(playerid, StressPurple[0]);
	}
	else
	{
		AccountData[playerid][ActivityTime] ++;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime] * 103/5;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		return 0;
	}
	return 1;
}

forward UseBandage(playerid);
public UseBandage(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(AccountData[playerid][pInjured])
	{
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 8)
	{
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

        if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            ClearAnimations(playerid, 1);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        }

		new Float: health;
		GetPlayerHealth(playerid, health);
        health += 20;
        if(health > 100.0)
        {
            health = 100.0;
        }
        SetPlayerHealthEx(playerid, health);

		Inventory_Remove(playerid, "Bandage", 1);
	}
	else
	{
		AccountData[playerid][ActivityTime] ++;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime] * 103/8;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		return 0;
	}
	return 1;
}

forward EatingProgress(playerid);
public EatingProgress(playerid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pUseItemTimer[playerid]);
        pUseItemTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }
    if(AccountData[playerid][pInjured])
    {
        KillTimer(pUseItemTimer[playerid]);
        pUseItemTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
		RemovePlayerAttachedObject(playerid, 9);
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak dapat melakukannya saat ini!");
        return 0;
    }
    if(AccountData[playerid][ActivityTime] >= 3)
    {
        KillTimer(pUseItemTimer[playerid]);
        pUseItemTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            ClearAnimations(playerid, 1);
            StopLoopingAnim(playerid);
            ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);
        }
        RemovePlayerAttachedObject(playerid, 9);
    }
    else 
    {
        AccountData[playerid][ActivityTime] ++;

        static Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/3;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward UsingRepairKit(playerid, vehicleid);
public UsingRepairKit(playerid, vehicleid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(vehicleid == INVALID_VEHICLE_ID)
	{
		ShowTDN(playerid, NOTIFICATION_ERROR, "Anda terlalu jauh dari kendaraan!");
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(AccountData[playerid][pInjured])
	{
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 10)
	{
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

        new index = Vehicle_ReturnID(vehicleid);

        ValidRepairVehicle(vehicleid);
        if(PlayerVehicle[index][pVehEngineUpgrade] == 1)
        {
            SetValidVehicleHealth(vehicleid, 2000);
        }
        else if(PlayerVehicle[index][pVehEngineUpgrade] == 0)
        {
            SetValidVehicleHealth(vehicleid, 1000);
        }

        if(PlayerVehicle[index][pVehBodyUpgrade] == 3)
        {
            PlayerVehicle[index][pVehBodyRepair] = 1000.0;
        }

        Inventory_Remove(playerid, "Repair Kit");
        ShowItemBox(playerid, "Removed 1x", "Repair Kit", 19921);
	}
	else
	{
		AccountData[playerid][ActivityTime] ++;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime] * 103/10;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		return 0;
	}
	return 1;
}

forward UsingToolkit(playerid, vehicleid);
public UsingToolkit(playerid, vehicleid)
{
    if(!IsPlayerConnected(playerid))
    {
        KillTimer(pUseItemTimer[playerid]);
        pUseItemTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);
        return 0;
    }

    if(vehicleid == INVALID_VEHICLE_ID)
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda telalu jauh dari kendaraan!");
        KillTimer(pUseItemTimer[playerid]);
        pUseItemTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][pInjured])
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang pingsan!");
        KillTimer(pUseItemTimer[playerid]);
        pUseItemTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        return 0;
    }

    if(AccountData[playerid][ActivityTime] >= 130)
    {
        KillTimer(pUseItemTimer[playerid]);
        pUseItemTimer[playerid] = -1;
        AccountData[playerid][ActivityTime] = 0;
        HideProgressBar(playerid);

        ClearAnimations(playerid, 1);
        StopLoopingAnim(playerid);
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        
        SetValidVehicleHealth(vehicleid, 1000);
        Inventory_Remove(playerid, "Tools Kit");
        ShowItemBox(playerid, "Removed 1x", "Tools Kit", 19918);
    }
    else 
    {
        AccountData[playerid][ActivityTime] += 16.25;

        static Float: progressvalue;
        progressvalue = AccountData[playerid][ActivityTime] * 103/130;
        PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
        PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
        return 0;
    }
    return 1;
}

forward UseKevlar(playerid);
public UseKevlar(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);
		return 0;
	}

	if(AccountData[playerid][pInjured])
	{
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		ClearAnimations(playerid, 1);
		StopLoopingAnim(playerid);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		return 0;
	}

	if(AccountData[playerid][ActivityTime] >= 3)
	{
		KillTimer(pUseItemTimer[playerid]);
		pUseItemTimer[playerid] = -1;
		AccountData[playerid][ActivityTime] = 0;
		HideProgressBar(playerid);

		if(!IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
        {
            ClearAnimations(playerid, 1);
            StopLoopingAnim(playerid);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        }

		new Float: Armour;
		GetPlayerArmour(playerid, Armour);
        Armour += 99.0;
        if(Armour >= 99.0)
        {
            Armour = 99.0;
        }
        SetPlayerArmourEx(playerid, Armour);
		Inventory_Remove(playerid, "Kevlar");
        ShowItemBox(playerid, "Removed 1x", "Kevlar", 19515);
	}
	else
	{
		AccountData[playerid][ActivityTime] ++;

		new Float: progressvalue;
		progressvalue = AccountData[playerid][ActivityTime] * 103/3;
		PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], progressvalue, 3.0);
		PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
		return 0;
	}
	return 1;
}

hook OnPlayerConnect(playerid)
{
    pUseItemTimer[playerid] = -1;
    AccountData[playerid][pOpenBackpackTimer] = -1;
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    KillTimer(pUseItemTimer[playerid]);
    KillTimer(AccountData[playerid][pOpenBackpackTimer]);
    AccountData[playerid][pOpenBackpackTimer] = -1;
    pUseItemTimer[playerid] = -1;
    return 1;
}
forward Float:GetInventoryWeight(item[], quantity);
public Float:GetInventoryWeight(item[], quantity)
{
    static Float:totalweight;
    if(!strcmp(item, "Nasi Goreng"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Kopi Kenangan"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Batu Kotor"))
    {
        totalweight = quantity*0.030;
    }
    else if(!strcmp(item, "Nasi Uduk"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Kanabis"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Batu Bersih"))
    {
        totalweight = quantity*0.030;
    }
    else if(!strcmp(item, "Air Mineral"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Besi"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Tembaga"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Berlian"))
    {
        totalweight = quantity*0.25;
    }
    else if(!strcmp(item, "Emas"))
    {
        totalweight = quantity*0.10;
    }
    else if(!strcmp(item, "Gold"))
    {
        totalweight = quantity*0.10;
    }
    else if(!strcmp(item, "Smartphone"))
    {
        totalweight = quantity*0.25;
    }
    else if(!strcmp(item, "Radio"))
    {
        totalweight = quantity*0.15;
    }
    else if(!strcmp(item, "Kayu"))
    {
        totalweight = quantity*0.06;
    }
    else if(!strcmp(item, "Kayu Potongan"))
    {
        totalweight = quantity*0.05;
    }
    else if(!strcmp(item, "Kayu Kemas"))
    {
        totalweight = quantity*0.08;
    }
    else if(!strcmp(item, "Marijuana"))
    {
        totalweight = quantity*0.02;
    }
    else if(!strcmp(item, "Benang"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Kain"))
    {
        totalweight = quantity*0.04;
    }
    else if(!strcmp(item, "Pakaian"))
    {
        totalweight = quantity*0.04;
    }
    else if(!strcmp(item, "Bandage"))
    {
        totalweight = quantity*0.02;
    }
    else if(!strcmp(item, "Medkit"))
    {
        totalweight = quantity*0.05;
    }
    else if(!strcmp(item, "Alprazolam"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Ayam Hidup"))
    {
        totalweight = quantity*0.15;
    }
    else if(!strcmp(item, "Ayam Potong"))
    {
        totalweight = quantity*0.10;
    }
    else if(!strcmp(item, "Ayam Kemas"))
    {
        totalweight = quantity*0.05;
    }
    else if(!strcmp(item, "Sampah Makanan"))
    {
        totalweight = quantity*0.005;
    }
    else if(!strcmp(item, "Kevlar"))
    {
        totalweight = quantity*0.90;
    }
    else if(!strcmp(item, "Botol"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Petrol"))
    {
        totalweight = quantity*0.50;
    }
    else if(!strcmp(item, "Pure Oil"))
    {
        totalweight = quantity*0.50;
    }
    else if(!strcmp(item, "GAS"))
    {
        totalweight = quantity*0.60;
    }
    else if(!strcmp(item, "Ikan"))
    {
        totalweight = quantity*0.02;
    }
    else if(!strcmp(item, "Rokok"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Pancingan"))
    {
        totalweight = quantity*0.08;
    }
    else if(!strcmp(item, "Umpan"))
    {
        totalweight = quantity*0.02;
    }
    else if(!strcmp(item, "Hiu"))
    {
        totalweight = quantity*0.90;
    }
    else if(!strcmp(item, "Penyu"))
    {
        totalweight = quantity*0.80;
    }
    else if(!strcmp(item, "Ikan Tawar"))
    {
        totalweight = quantity*0.03;
    }
    else if(!strcmp(item, "Jerigen"))
    {
        totalweight = quantity*0.25;
    }
    else if(!strcmp(item, "Tools Kit"))
    {
        totalweight = quantity*0.30;
    }
    else if(!strcmp(item, "Repair Kit"))
    {
        totalweight = quantity*0.35;
    }
    else if(!strcmp(item, "Linggis"))
    {
        totalweight = quantity*0.05;
    }
    else if(!strcmp(item, "Hacking Tools"))
    {
        totalweight = quantity*0.20;
    }
    else if(!strcmp(item, "Bomb"))
    {
        totalweight = quantity*0.50;
    }
    else if(!strcmp(item, "Kunci T"))
    {
        totalweight = quantity*0.05;
    }
    else if(!strcmp(item, "Nasi Pecel"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Bubur Pedas"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Es Teh"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Jus Apel"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Api Unggun"))
    {
        totalweight = quantity*0.10;
    }
    else if(!strcmp(item, "Boombox"))
    {
        totalweight = quantity*0.20;
    }
    else if(!strcmp(item, "Kebab A5"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Bakso"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Choco Matcha"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Teh Jeruk"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Susu Murni"))
    {
        totalweight = quantity*0.02;
    }
    else if(!strcmp(item, "Susu Olahan"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Susu Fresh"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Cabe"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Padi"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Garam Kristal"))
    {
        totalweight = quantity*0.006;
    }
    else if(!strcmp(item, "Tebu"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Beras"))
    {
        totalweight = quantity*0.04;
    }
    else if(!strcmp(item, "Sambal"))
    {
        totalweight = quantity*0.02;
    }
    else if(!strcmp(item, "Gula"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Garam"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Daging"))
    {
        totalweight = quantity*0.02;
    }
    else if(!strcmp(item, "Daging Ikan Tawar"))
    {
        totalweight = quantity*0.02;
    }
    else if(!strcmp(item, "Daging Ayam Goreng"))
    {
        totalweight = quantity*0.02;
    }
    else if(!strcmp(item, "Daging Hiu"))
    {
        totalweight = quantity*0.09;
    }
    else if(!strcmp(item, "Tanduk"))
    {
        totalweight = quantity*0.03;
    }
    else if(!strcmp(item, "Kulit"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Bulu"))
    {
        totalweight = quantity*0.01;
    }
    else if(!strcmp(item, "Boxmats"))
    {
        totalweight = quantity*0.04;
    }
    else if(!strcmp(item, "Baja"))
    {
        totalweight = quantity*0.05;
    }
    else if(!strcmp(item, "Material"))
    {
        totalweight = quantity*0.025;
    }
    else if(!strcmp(item, "Kaca"))
    {
        totalweight = quantity*0.015;
    }
    else if(!strcmp(item, "Karet"))
    {
        totalweight = quantity*0.006;
    }
    else if(!strcmp(item, "Plastik"))
    {
        totalweight = quantity*0.005;
    }
    else if(!strcmp(item, "Alumunium"))
    {
        totalweight = quantity*0.010;
    }
    else if(!strcmp(item, "Backpack"))
    {
        totalweight = quantity*0.50;
    }
    else if(!strcmp(item, "Masker"))
    {
        totalweight = quantity*0.005;
    }
    else if(!strcmp(item, "Plat Besi"))
    {
        totalweight = quantity*0.025;
    }
    else if(!strcmp(item, "Korek Api"))
    {
        totalweight = quantity*0.010;
    }
    else if(!strcmp(item, "Bibit Tebu"))
    {
        totalweight = quantity*0.015;
    }
    else if(!strcmp(item, "Bibit Padi"))
    {
        totalweight = quantity*0.015;
    }
    else if(!strcmp(item, "Bibit Cabe"))
    {
        totalweight = quantity*0.015;
    }
    else if(!strcmp(item, "Petasan"))
    {
        totalweight = quantity*0.010;
    }
    else if(!strcmp(item, "KTA"))
    {
        totalweight = quantity*0.005;
    }
    else if(!strcmp(item, "Tahu Bulat"))
    {
        totalweight = quantity*0.005;
    }
    else if(!strcmp(item, "Pilox"))
    {
        totalweight = quantity*0.005;
    }
    else if(!strcmp(item, "Uranium ACD"))
    {
        totalweight = quantity*0.020;
    }
    else if(!strcmp(item, "Uranium"))
    {
        totalweight = quantity*0.010;
    }
    else if(!strcmp(item, "Senter"))
    {
        totalweight = quantity*0.006;
    }
    return totalweight;
}
