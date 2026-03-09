#define MAX_INVENTORY   (20)

enum inventoryData {
	invExists,
	invID,
	invItem[32 char],
	invModel,
	invQuantity
};

new InventoryData[MAX_PLAYERS][MAX_INVENTORY][inventoryData];