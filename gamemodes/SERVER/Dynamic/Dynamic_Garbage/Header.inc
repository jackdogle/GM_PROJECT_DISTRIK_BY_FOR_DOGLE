#define MAX_DYNAMIC_TRASH  500

enum e_trashdata
{
    Float:trashPos[3],
    Float:trashRot[3],
    trashInt,
    trashWorld,
    trashCooldown,
    trashModelID,

    trashDynLabel,
    trashObject
};
new TrashData[MAX_DYNAMIC_TRASH][e_trashdata],
    Iterator:Trash<MAX_DYNAMIC_TRASH>;