#define MAX_PLANT   (500)
#define PADI        (1)
#define TEBU        (2)
#define CABAI       (3)

enum PLANT_DATA
{
    PlantID,
    PlantType,
    PlantTime,
    bool: PlantReady,
    Float: PlantPos[4],
    PlantInt,
    PlantVw,
    PlantObject,
    PlantHarvest,
    PlantExists,
    PlantCP
}
new PlantData[MAX_PLANT][PLANT_DATA],
    Iterator: Plants<MAX_PLANT>;