#include <YSI\y_hooks>
#define MAX_PEMERINTAHITEM 100

new ListPemerintahItem[MAX_PLAYERS][100];

enum pemerintahStorage
{
    ItemID,
    ItemExists,
    ItemName[32 char],
    ItemModel,
    ItemQuantity
};
new PemerintahStorage[6][MAX_PEMERINTAHITEM][pemerintahStorage];

stock Pemerintah_OpenStorage(playerid, facid)
{
    if(facid != 2) return false;

    new 
        amount[MAX_PEMERINTAHITEM],
        str[512],
        string[256],
        count3 = 0;
    
    format(str, sizeof(str), "Nama Barang\tJumlah Barang\tBerat (No Limit)\n");
    for(new i = 0; i != MAX_PEMERINTAHITEM; i ++)
    {
        if(PemerintahStorage[facid][i][ItemExists])
        {
            strunpack(string, PemerintahStorage[facid][i][ItemName]);
            amount[i] = PemerintahStorage[facid][i][ItemQuantity];

            if(PemerintahStorage[facid][i][ItemQuantity] > 0)
            {
                format(str, sizeof(str), "%s %s\t%d\t-\n", str, string, amount[i]);
                ListPemerintahItem[playerid][count3 ++] = i;
            }
        }
    }
    if(!count3) return Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Brankas Pemerintah", "Tidak ada barang apapun dibrankas saat ini!", "Tutup", "");
    Dialog_Show(playerid, PemerintahBrankasItem, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Brankas Pemerintah", str, "Pilih", "Batal");
    return 1;
}

stock Pemerintah_GetItemID(facid, item[])
{
	if (facid != 2) return false;

	for (new i = 0; i < MAX_PEMERINTAHITEM; i ++)
	{
	    if (!PemerintahStorage[facid][i][ItemExists])
	        continue;

		if (!strcmp(PemerintahStorage[facid][i][ItemName], item)) return i;
	}
	return -1;
}

stock Pemerintah_GetFreeID(facid)
{
	if (facid != 2) return false;

	for (new i = 0; i < MAX_PEMERINTAHITEM; i ++)
	{
	    if (!PemerintahStorage[facid][i][ItemExists])
	        return i;
	}
	return -1;
}

stock PemerintahItem_Add(facid, item[], model, quantity = 1)
{
    if(facid != 2) return false;
	new
		itemid = Pemerintah_GetItemID(facid, item),
		string[128];

	if (itemid == -1)
	{
	    itemid = Pemerintah_GetFreeID(facid);

	    if (itemid != -1)
	    {
	        PemerintahStorage[facid][itemid][ItemExists] = true;
	        PemerintahStorage[facid][itemid][ItemModel] = model;
	        PemerintahStorage[facid][itemid][ItemQuantity] = quantity;

	        strpack(PemerintahStorage[facid][itemid][ItemName], item, 32 char);

			mysql_format(g_SQL, string, sizeof(string), "INSERT INTO `brankas_pemerintah` (`ID`, `ItemName`, `ItemModel`, `ItemQuantity`) VALUES('%d', '%s', '%d', '%d')", facid, item, model, quantity);
			mysql_tquery(g_SQL, string, "OnPemerintahAddItem", "dd", facid, itemid);

	        return itemid;
		}
		return -1;
	}
	else
	{
	    mysql_format(g_SQL, string, sizeof(string), "UPDATE `brankas_pemerintah` SET `ItemQuantity` = `ItemQuantity` + %d WHERE `ID` = '%d' AND `ItemID` = '%d'", quantity, facid, PemerintahStorage[facid][itemid][ItemID]);
	    mysql_tquery(g_SQL, string);

	    PemerintahStorage[facid][itemid][ItemQuantity] += quantity;
	}
	return itemid;
}

VRRP::OnPemerintahAddItem(facid, itemid)
{
    PemerintahStorage[facid][itemid][ItemID] = cache_insert_id();
    return 1;
}

stock PemerintahItem_Remove(facid, item[], quantity = 1)
{
    if (facid != 2) return false;

	new
		itemid = Pemerintah_GetItemID(facid, item),
		string[128];

	if (itemid != -1)
	{
	    if (PemerintahStorage[facid][itemid][ItemQuantity] > 0)
	    {
	        PemerintahStorage[facid][itemid][ItemQuantity] -= quantity;
		}
		if (quantity == -1 || PemerintahStorage[facid][itemid][ItemQuantity] < 1)
		{
		    PemerintahStorage[facid][itemid][ItemExists] = false;
		    PemerintahStorage[facid][itemid][ItemModel] = 0;
		    PemerintahStorage[facid][itemid][ItemQuantity] = 0;

		    mysql_format(g_SQL, string, sizeof(string), "DELETE FROM `brankas_pemerintah` WHERE `ID` = '%d' AND `ItemID` = '%d'", facid, PemerintahStorage[facid][itemid][ItemID]);
	        mysql_tquery(g_SQL, string);
		}
		else if (quantity != -1 && PemerintahStorage[facid][itemid][ItemQuantity] > 0)
		{
			mysql_format(g_SQL, string, sizeof(string), "UPDATE `brankas_pemerintah` SET `ItemQuantity` = `ItemQuantity` - %d WHERE `ID` = '%d' AND `ItemID` = '%d'", quantity, facid, PemerintahStorage[facid][itemid][ItemID]);
            mysql_tquery(g_SQL, string);
		}
		return 1;
	}
	return 0;
}

VRRP::LoadBrankasPemerintah(facid)
{
    if(facid != 2) return false;

    static 
        str[512];
    
    new rows = cache_num_rows();
    if(rows)
    {
        for(new i; i < rows; i ++)
        {
            PemerintahStorage[facid][i][ItemExists] = true;

            cache_get_value_name_int(i, "ItemID", PemerintahStorage[facid][i][ItemID]);
		    cache_get_value_name_int(i, "ItemModel", PemerintahStorage[facid][i][ItemModel]);
		    cache_get_value_name_int(i, "ItemQuantity", PemerintahStorage[facid][i][ItemQuantity]);
		    cache_get_value_name(i, "ItemName", str);
			strpack(PemerintahStorage[facid][i][ItemName], str, 32 char);
        }
    }
    return 1;
}

Dialog:PemerintahBrankasDeposit(playerid, response, listitem, inputtext[])
{
    new facid = AccountData[playerid][pFaction];

    new 
        itemid = -1,
        string[32];

    itemid = AccountData[playerid][pListItem];
    new model = InventoryData[playerid][itemid][invModel];
    strunpack(string, InventoryData[playerid][itemid][invItem]);

    if(response)
    {
        new amount = floatround(strval(inputtext));

        if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Input");
        if(amount > InventoryData[playerid][itemid][invQuantity]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Barang anda tidak sebanyak itu");

        PemerintahItem_Add(facid, string, InventoryData[playerid][itemid][invModel], amount);
        Inventory_Remove(playerid, string, amount);
        
        ShowItemBox(playerid, sprintf("REMOVED %dx", amount), string, model);
    }
    return 1;
}

Dialog:PemerintahBrankasItem(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new facid = AccountData[playerid][pFaction];
        AccountData[playerid][pListItemGudang] = ListPemerintahItem[playerid][listitem];

        new 
            name[48],
            str[128];

        strunpack(name, PemerintahStorage[facid][AccountData[playerid][pListItemGudang]][ItemName]);

        if(PemerintahStorage[facid][AccountData[playerid][pListItemGudang]][ItemExists])
        {
            format(str, sizeof(str), "Anda akan mengambil barang:\nNama: %s\nJumlah di brankas: %d\nMohon masukan jumlah yang ingin anda ambil:", name, PemerintahStorage[facid][AccountData[playerid][pListItemGudang]][ItemQuantity]);
            Dialog_Show(playerid, PemerintahWithdraw, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Brankas Pemerintah", str, "Submit", "Back");
        }
    }
    return 1;
}

Dialog:PemerintahWithdraw(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new facid = AccountData[playerid][pFaction];
        new 
            itemid = -1,
            string[32];
        
        itemid = AccountData[playerid][pListItemGudang];
        new model = PemerintahStorage[facid][itemid][ItemModel];
        strunpack(string, PemerintahStorage[facid][itemid][ItemName]);

        new amount = floatround(strval(inputtext));

        if(amount < 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Invalid Input");
        if(amount > PemerintahStorage[facid][itemid][ItemQuantity]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Barang dibrankas anda tidak sebanyak itu");

        Inventory_Add(playerid, string, PemerintahStorage[facid][itemid][ItemModel], amount);
        PemerintahItem_Remove(facid, string, amount);
        
        ShowItemBox(playerid, sprintf("ADDED %dx", amount), string, model);
    }
    return 1;
}
