#include <YSI\y_hooks>

#define MAX_LISTED_ITEMS 10
#define MAX_DROPPED_ITEMS 1000

new NearestItems[MAX_PLAYERS][MAX_LISTED_ITEMS];
enum droppedItems
{
    droppedID,
	droppedItem[32],
	droppedPlayer[24],
	droppedModel,
	droppedQuantity,
	Float:droppedPos[3],
	droppedInt,
	droppedWorld,
	STREAMER_TAG_OBJECT:droppedObject,
	STREAMER_TAG_3D_TEXT_LABEL:droppedText3D
};

new DroppedItems[MAX_DROPPED_ITEMS][droppedItems];

Float: GetItemWeight(itemname[], quantity)
{
	new Float: weight = 0.0; // inisialisasi berat awal adalah 0.0

	if(!strcmp(itemname, "Nasi Goreng"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Kopi Kenangan"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Batu Kotor"))
    {
        weight = quantity*0.030;
    }
    else if(!strcmp(itemname, "Nasi Uduk"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Kanabis"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Batu Bersih"))
    {
        weight = quantity*0.030;
    }
    else if(!strcmp(itemname, "Air Mineral"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Besi"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Tembaga"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Berlian"))
    {
        weight = quantity*0.25;
    }
    else if(!strcmp(itemname, "Emas"))
    {
        weight = quantity*0.10;
    }
    else if(!strcmp(itemname, "Gold"))
    {
        weight = quantity*0.10;
    }
    else if(!strcmp(itemname, "Smartphone"))
    {
        weight = quantity*0.25;
    }
    else if(!strcmp(itemname, "Race Tablet"))
    {
        weight = quantity*0.25;
    }
    else if(!strcmp(itemname, "Radio"))
    {
        weight = quantity*0.15;
    }
    else if(!strcmp(itemname, "Kayu"))
    {
        weight = quantity*0.06;
    }
    else if(!strcmp(itemname, "Kayu Potongan"))
    {
        weight = quantity*0.05;
    }
    else if(!strcmp(itemname, "Kayu Kemas"))
    {
        weight = quantity*0.08;
    }
    else if(!strcmp(itemname, "Marijuana"))
    {
        weight = quantity*0.02;
    }
    else if(!strcmp(itemname, "Benang"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Kain"))
    {
        weight = quantity*0.04;
    }
    else if(!strcmp(itemname, "Pakaian"))
    {
        weight = quantity*0.04;
    }
    else if(!strcmp(itemname, "Bandage"))
    {
        weight = quantity*0.02;
    }
    else if(!strcmp(itemname, "Medkit"))
    {
        weight = quantity*0.05;
    }
    else if(!strcmp(itemname, "Alprazolam"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Ayam Hidup"))
    {
        weight = quantity*0.15;
    }
    else if(!strcmp(itemname, "Ayam Potong"))
    {
        weight = quantity*0.10;
    }
    else if(!strcmp(itemname, "Ayam Kemas"))
    {
        weight = quantity*0.05;
    }
    else if(!strcmp(itemname, "Sampah Makanan"))
    {
        weight = quantity*0.005;
    }
    else if(!strcmp(itemname, "Kevlar"))
    {
        weight = quantity*0.90;
    }
    else if(!strcmp(itemname, "Botol"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Petrol"))
    {
        weight = quantity*0.50;
    }
    else if(!strcmp(itemname, "Pure Oil"))
    {
        weight = quantity*0.50;
    }
    else if(!strcmp(itemname, "GAS"))
    {
        weight = quantity*0.60;
    }
    else if(!strcmp(itemname, "Ikan"))
    {
        weight = quantity*0.02;
    }
    else if(!strcmp(itemname, "Rokok"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Pancingan"))
    {
        weight = quantity*0.08;
    }
    else if(!strcmp(itemname, "Umpan"))
    {
        weight = quantity*0.02;
    }
    else if(!strcmp(itemname, "Hiu"))
    {
        weight = quantity*0.90;
    }
    else if(!strcmp(itemname, "Penyu"))
    {
        weight = quantity*0.80;
    }
    else if(!strcmp(itemname, "Ikan Tawar"))
    {
        weight = quantity*0.03;
    }
    else if(!strcmp(itemname, "Jerigen"))
    {
        weight = quantity*0.25;
    }
    else if(!strcmp(itemname, "Tools Kit"))
    {
        weight = quantity*0.30;
    }
    else if(!strcmp(itemname, "Repair Kit"))
    {
        weight = quantity*0.35;
    }
    else if(!strcmp(itemname, "Linggis"))
    {
        weight = quantity*0.05;
    }
    else if(!strcmp(itemname, "Hacking Tools"))
    {
        weight = quantity*0.20;
    }
    else if(!strcmp(itemname, "Kunci T"))
    {
        weight = quantity*0.05;
    }
    else if(!strcmp(itemname, "Nasi Pecel"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Bubur Pedas"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Es Teh"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Jus Apel"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Boombox"))
    {
        weight = quantity*0.20;
    }
    else if(!strcmp(itemname, "Api Unggun"))
    {
        weight = quantity*0.10;
    }
    else if(!strcmp(itemname, "Kebab A5"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Bakso"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Choco Matcha"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Teh Jeruk"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Susu Murni"))
    {
        weight = quantity*0.02;
    }
    else if(!strcmp(itemname, "Susu Olahan"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Susu Fresh"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Cabe"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Padi"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Garam Kristal"))
    {
        weight = quantity*0.006;
    }
    else if(!strcmp(itemname, "Tebu"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Beras"))
    {
        weight = quantity*0.04;
    }
    else if(!strcmp(itemname, "Sambal"))
    {
        weight = quantity*0.02;
    }
    else if(!strcmp(itemname, "Gula"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Garam"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Daging"))
    {
        weight = quantity*0.02;
    }
    else if(!strcmp(itemname, "Daging Ikan Tawar"))
    {
        weight = quantity*0.02;
    }
    else if(!strcmp(itemname, "Daging Ayam Goreng"))
    {
        weight = quantity*0.02;
    }
    else if(!strcmp(itemname, "Daging Hiu"))
    {
        weight = quantity*0.09;
    }
    else if(!strcmp(itemname, "Tanduk"))
    {
        weight = quantity*0.03;
    }
    else if(!strcmp(itemname, "Kulit"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Bulu"))
    {
        weight = quantity*0.01;
    }
    else if(!strcmp(itemname, "Boxmats"))
    {
        weight = quantity*0.04;
    }
    else if(!strcmp(itemname, "Baja"))
    {
        weight = quantity*0.05;
    }
    else if(!strcmp(itemname, "Material"))
    {
        weight = quantity*0.025;
    }
    else if(!strcmp(itemname, "Kaca"))
    {
        weight = quantity*0.015;
    }
    else if(!strcmp(itemname, "Karet"))
    {
        weight = quantity*0.006;
    }
    else if(!strcmp(itemname, "Plastik"))
    {
        weight = quantity*0.005;
    }
    else if(!strcmp(itemname, "Alumunium"))
    {
        weight = quantity*0.010;
    }
    else if(!strcmp(itemname, "Backpack"))
    {
        weight = quantity*0.50;
    }
    else if(!strcmp(itemname, "Masker"))
    {
        weight = quantity*0.005;
    }
    else if(!strcmp(itemname, "Plat Besi"))
    {
        weight = quantity*0.025;
    }
    else if(!strcmp(itemname, "Korek Api"))
    {
        weight = quantity*0.010;
    }
    else if(!strcmp(itemname, "Bibit Padi"))
    {
        weight = quantity*0.015;
    }
    else if(!strcmp(itemname, "Bibit Tebu"))
    {
        weight = quantity*0.015;
    }
    else if(!strcmp(itemname, "Bibit Cabe"))
    {
        weight = quantity*0.015;
    }
    else if(!strcmp(itemname, "Pilox"))
    {
        weight = quantity*0.005;
    }
    else if(!strcmp(itemname, "Uranium ACD"))
    {
        weight = quantity*0.020;
    }
    else if(!strcmp(itemname, "Uranium"))
    {
        weight = quantity*0.010;
    }
    else if(!strcmp(itemname, "Senter"))
    {
        weight = quantity*0.006;
    }
	
	return weight;
}

stock Item_Delete(itemid)
{
    new
	    query[64];

    if (itemid != -1 && DroppedItems[itemid][droppedModel])
	{
        DroppedItems[itemid][droppedModel] = 0;
		DroppedItems[itemid][droppedQuantity] = 0;
	    DroppedItems[itemid][droppedPos][0] = 0.0;
	    DroppedItems[itemid][droppedPos][1] = 0.0;
	    DroppedItems[itemid][droppedPos][2] = 0.0;
	    DroppedItems[itemid][droppedInt] = 0;
	    DroppedItems[itemid][droppedWorld] = 0;

	    DestroyDynamicObject(DroppedItems[itemid][droppedObject]);
	    DestroyDynamic3DTextLabel(DroppedItems[itemid][droppedText3D]);

	    mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `dropped` WHERE `ID` = '%d'", DroppedItems[itemid][droppedID]);
	    mysql_tquery(g_SQL, query);
	}
	return 1;
}

stock Item_Nearest(playerid)
{
    for (new i = 0; i != MAX_DROPPED_ITEMS; i ++) if (DroppedItems[i][droppedModel] && IsPlayerInRangeOfPoint(playerid, 1.5, DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2]))
	{
	    if (GetPlayerInterior(playerid) == DroppedItems[i][droppedInt] && GetPlayerVirtualWorld(playerid) == DroppedItems[i][droppedWorld])
	        return i;
	}
	return -1;
}

stock PickupItem(playerid, itemid)
{
	if (itemid != -1 && DroppedItems[itemid][droppedModel])
	{
	    new id = Inventory_Add(playerid, DroppedItems[itemid][droppedItem], DroppedItems[itemid][droppedModel], DroppedItems[itemid][droppedQuantity]);
		new str[32];
		new model = DroppedItems[itemid][droppedModel];
		format(str, sizeof str, "%s", DroppedItems[itemid][droppedItem]);
		ShowItemBox(playerid, sprintf("Received %dx", DroppedItems[itemid][droppedQuantity]), str, model);

	    if (id == -1)
	        return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory Kamu Penuh!");

	    Item_Delete(itemid);
	}
	return 1;
}
forward Dropped_Load();
public Dropped_Load()
{
	new rows = cache_num_rows();
 	if(rows)
  	{
    	forex(i, rows)
		{
		    cache_get_value_name_int(i, "ID", DroppedItems[i][droppedID]);

			cache_get_value_name(i, "itemName", DroppedItems[i][droppedItem]);
			cache_get_value_name(i, "itemPlayer", DroppedItems[i][droppedPlayer]);

			cache_get_value_name_int(i, "itemModel", DroppedItems[i][droppedModel]);
			cache_get_value_name_int(i, "itemQuantity", DroppedItems[i][droppedQuantity]);
			cache_get_value_name_float(i, "itemX", DroppedItems[i][droppedPos][0]);
			cache_get_value_name_float(i, "itemY", DroppedItems[i][droppedPos][1]);
			cache_get_value_name_float(i, "itemZ", DroppedItems[i][droppedPos][2]);
			cache_get_value_name_int(i, "itemInt", DroppedItems[i][droppedInt]);
			cache_get_value_name_int(i, "itemWorld", DroppedItems[i][droppedWorld]);

            new shstr[255];
            format(shstr, sizeof(shstr), ""DEEPSKYBLUE1"%s | %d | (%.3f kg)", DroppedItems[i][droppedItem], DroppedItems[i][droppedQuantity], GetItemWeight(DroppedItems[i][droppedItem], DroppedItems[i][droppedQuantity]));
			DroppedItems[i][droppedObject] = CreateDynamicObject(DroppedItems[i][droppedModel], DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2], 0.0, 0.0, 0.0, DroppedItems[i][droppedWorld], DroppedItems[i][droppedInt]);
			DroppedItems[i][droppedText3D] = CreateDynamic3DTextLabel(shstr, -1, DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2]+0.60, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, DroppedItems[i][droppedWorld], DroppedItems[i][droppedInt]);
		}
		printf("[Drop Item] Jumlah total Item Drooped yang dimuat %d.", rows);
	}
	return 1;
}

DropItem(item[], player[], model, quantity, Float:x, Float:y, Float:z, interior, world)
{
	new
	    query[300], string[256];

	forex(i, MAX_DROPPED_ITEMS) if (!DroppedItems[i][droppedModel])
	{
	    format(DroppedItems[i][droppedItem], 32, item);
	    format(DroppedItems[i][droppedPlayer], 24, player);

		DroppedItems[i][droppedModel] = model;
		DroppedItems[i][droppedQuantity] = quantity;
		DroppedItems[i][droppedPos][0] = x;
		DroppedItems[i][droppedPos][1] = y;
		DroppedItems[i][droppedPos][2] = z;

		DroppedItems[i][droppedInt] = interior;
		DroppedItems[i][droppedWorld] = world;

		DroppedItems[i][droppedObject] = CreateDynamicObject(2663, x, y, z + 0.2, 0.0, 0.0, 0.0, world, interior);

		strunpack(string, DroppedItems[i][droppedItem]);

		new Float:berat = GetItemWeight(string, quantity);
		DroppedItems[i][droppedText3D] = CreateDynamic3DTextLabel(sprintf(""DEEPSKYBLUE1"%s | %dx | (%.3f kg)", string, quantity, berat), -1, x, y, z + 0.60, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, world, interior);

 		format(query, sizeof(query), "INSERT INTO `dropped` (`itemName`, `itemPlayer`, `itemModel`, `itemQuantity`, `itemX`, `itemY`, `itemZ`, `itemInt`, `itemWorld`) VALUES('%s', '%s', '%d', '%d', '%.4f', '%.4f', '%.4f', '%d', '%d')", item, player, model, quantity, x, y, z, interior, world);
		mysql_tquery(g_SQL, query, "OnDroppedItem", "d", i);
		return i;
	}
	return -1;
}

FUNC::OnDroppedItem(itemid)
{
	if (itemid == -1 || !DroppedItems[itemid][droppedModel])
	    return 0;

	DroppedItems[itemid][droppedID] = cache_insert_id();
	return 1;
}

DropPlayerItem(playerid, itemid, quantity = 1)
{
	if (itemid == -1 || !InventoryData[playerid][itemid][invExists])
	    return 0;

    new
		Float:x,
  		Float:y,
    	Float:z,
		Float:angle,
		string[32],
        query[256];

	strunpack(string, InventoryData[playerid][itemid][invItem]);

    if(Inventory_Count(playerid, string) < AccountData[playerid][pAmountInv]) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Anda tidak memiliki %s sebanyak itu!", string));
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);

	DropItem(string, ReturnName(playerid), InventoryData[playerid][itemid][invModel], quantity, x, y, z - 0.9, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
 	Inventory_Remove(playerid, string, quantity);

    mysql_format(g_SQL, query, sizeof(query),"UPDATE inventory SET invQuantity = GREATEST(invQuantity - %d, 0) WHERE ID=%d AND invItem='%e'",quantity, AccountData[playerid][pID], string);
    mysql_tquery(g_SQL, query);

    mysql_format(g_SQL, query, sizeof(query),"DELETE FROM inventory WHERE invQuantity <= 0 AND ID=%d AND invItem='%e'",AccountData[playerid][pID], string);
    mysql_tquery(g_SQL, query);

	ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, 0, 0, 0, 0, 0, 1);
	Inventory_Close(playerid);
    if(AccountData[playerid][menuShowed])
    {
        ShowPlayerDialog(playerid, -1, DIALOG_STYLE_MSGBOX, "", "", "", "");
    }

	SendRPMeAboveHead(playerid, sprintf("Menjatuhkan %s ke tanah", string), X11_PLUM1);
	return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case DialogDropItem:
		{
			if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan");
			new 
				itemid = AccountData[playerid][pSelectItem],
				str[32],
				string[256];

			strunpack(string, InventoryData[playerid][itemid][invItem]);

			if(response)
			{
				if(isnull(inputtext))
				return format(str, sizeof str, "Item: %s - Jumlah : %dx\n\nMohon masukan jumlah yang ingin anda drop:", string, InventoryData[playerid][itemid][invQuantity]);
				ShowPlayerDialog(playerid, DialogDropItem, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Drop Barang", str, "Drop", "Cancel");

				if(strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][itemid][invQuantity])
				return format(str, sizeof str, "ERROR: Kamu tidak memiliki barang sebanyak itu\n\nItem: %s - Jumlah : %dx\n\nMohon masukan jumlah yang ingin anda drop:", string, InventoryData[playerid][itemid][invQuantity]);
				ShowPlayerDialog(playerid, DialogDropItem, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Drop Barang", str, "Drop", "Cancel");

				DropPlayerItem(playerid, itemid, strval(inputtext));
			}
		}
		case DIALOG_ITEM_PICKUP:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");

            new id = NearestItems[playerid][listitem];
            if(id != -1 && DroppedItems[id][droppedModel])
            {
                if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
                if(Inventory_Items(playerid) >= MAX_INVENTORY) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot Inventory anda telah penuh!");
                
                if(PickupItem(playerid, id))
                {
                    SendRPMeAboveHead(playerid, "Mengutip sesuatu dari tanah", X11_PLUM1);
                    ApplyAnimation(playerid, "CARRY", "liftup", 3.1, 0, 0, 0, 0, 0, 1);
                }
                else ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
            }
            else ShowTDN(playerid, NOTIFICATION_ERROR, "Barang tersebut sudah tidak ada!");
		}
	}
	return 0;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(newkeys & KEY_WALK && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DUCK)
    {
        new count = 0, id, shstr[320];

        id = Item_Nearest(playerid);
        if(id != -1)
        {
            if(GetTotalWeightFloat(playerid) >= 50) return ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
            if(Inventory_Items(playerid) >= MAX_INVENTORY) return ShowTDN(playerid, NOTIFICATION_ERROR, "Slot Inventory anda telah penuh!");
            shstr = "";

            format(shstr, sizeof(shstr), "Nama Item\tJumlah Item\tBerat Item (kg)\n");
            for(new i = 0; i < MAX_DROPPED_ITEMS; i++) if (count < MAX_LISTED_ITEMS && DroppedItems[i][droppedModel] && IsPlayerInRangeOfPoint(playerid, 1.5, DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2]) && GetPlayerInterior(playerid) == DroppedItems[i][droppedInt] && GetPlayerVirtualWorld(playerid) == DroppedItems[i][droppedWorld])
            {
                format(shstr, sizeof(shstr), "%s%s\t%d\t%.3f kg\n", shstr, DroppedItems[i][droppedItem], DroppedItems[i][droppedQuantity], GetItemWeight(DroppedItems[i][droppedItem], DroppedItems[i][droppedQuantity]));
                NearestItems[playerid][count++] = i;
            }
            if(count == 1)
            {
                if(PickupItem(playerid, id))
                {
                    SendRPMeAboveHead(playerid, "Mengutip sesuatu dari tanah", X11_PLUM1);
                    ApplyAnimation(playerid, "CARRY", "liftup", 3.1, 0, 0, 0, 0, 0, 1);
                }
                else ShowTDN(playerid, NOTIFICATION_ERROR, "Inventory anda telah penuh!");
            }
            else ShowPlayerDialog(playerid, DIALOG_ITEM_PICKUP, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Pickup Item", shstr, "Ambil", "Batal");
        }
    }
	return 1;
}
