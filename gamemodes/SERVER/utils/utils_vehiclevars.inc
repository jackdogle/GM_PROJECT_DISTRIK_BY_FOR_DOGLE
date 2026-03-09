new bool:VehicleHealthSecurity[MAX_VEHICLES] = false, Float:VehicleHealthSecurityData[MAX_VEHICLES] = 1000.0;
new AdminVehicle[MAX_VEHICLES char];
new ListVehImpound[MAX_PLAYERS][MAX_PRIVATE_VEHICLE];
new ListHolster[MAX_PLAYERS][50];

#define MAX_FACTION_VEHICLE 100

new vehicleFlashTimer[MAX_PRIVATE_VEHICLE] = {-1, ...};
new vehicleFlashCount[MAX_PRIVATE_VEHICLE] = {0, ...}; 

new gELMTimer[MAX_VEHICLES];
new gELMCount[MAX_VEHICLES] = {0, ...};
new bool:gToggleELM[MAX_VEHICLES] = {false, ...};

new	STREAMER_TAG_OBJECT: FactionVehObject[MAX_PRIVATE_VEHICLE][23];
new STREAMER_TAG_OBJECT: DonationVehObject[MAX_PRIVATE_VEHICLE][16];

new bool: IsBagasiOpened[MAX_PRIVATE_VEHICLE] = { false, ... };
new TrunkVehEntered[MAX_PRIVATE_VEHICLE];
new BagasiLastUse[MAX_PLAYERS];
new BrankasLastUse[MAX_PLAYERS];
new BrankasHouseLastUse[MAX_PLAYERS];

SSCANF:VehicleSiren(string[]) 
{
	if(!strcmp(string,"roof",true)) return 1;
	else if(!strcmp(string,"dashboard",true)) return 2;
	else if(!strcmp(string,"mid",true)) return 3;
	else if(!strcmp(string,"off",true)) return 4;
	return 0;
}

forward ToggleELM(vehicleid);
public ToggleELM(vehicleid)
{
	if(gToggleELM[vehicleid])
	{
		static panels, doors, lights, tires;
	    GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);

	    switch(gELMCount[vehicleid])
	    {
	        case 0: UpdateVehicleDamageStatus(vehicleid, panels, doors, 2, tires);
	        case 1: UpdateVehicleDamageStatus(vehicleid, panels, doors, 5, tires);
	        case 2: UpdateVehicleDamageStatus(vehicleid, panels, doors, 2, tires);
	        case 3: UpdateVehicleDamageStatus(vehicleid, panels, doors, 4, tires);
	        case 4: UpdateVehicleDamageStatus(vehicleid, panels, doors, 5, tires);
	        case 5: UpdateVehicleDamageStatus(vehicleid, panels, doors, 4, tires);
	    }

	    if(gELMCount[vehicleid] >= 5) gELMCount[vehicleid] = 0;
	    gELMCount[vehicleid]++;
	}
    return 1;
}

enum pvehfactdata
{
    pVehFactID,
    pVehFactFactionID,
    pVehFactOwnerID,
	pVehFactModelID,
	pVehFactColor1,
	pVehFactColor2,
    Float:pVehFactHealth,
    Float:pVehFactPos[4],
    pVehFactDamage[4],
    pVehFactFuel,
    pVehFactInterior,
    pVehFactWorld,
    pVehFactDCTime,

    // not save
    bool: pVehFactExists,
    pVehFactPhysic
};
new PlayerFactionVeh[MAX_FACTION_VEHICLE][pvehfactdata],
    Iterator:PvtFVehicles<MAX_FACTION_VEHICLE + 1>;

enum pvehdata
{
	pVehID,
	pVehOwnerID,
	pVehModelID,
	pVehColor1,
	pVehColor2,
	pVehPaintjob,
	pVehNeon,
	cTogNeon,
	bool: pVehLocked,
	pVehPlate[256],
	pVehPlateTime,
	pVehPlateOwn,
	pVehPrice,
	Float:pVehHealth,
	pVehFuel,
	Float:pVehPos[4],
	pVehDamage[4],
	pVehInterior,
	pVehWorld,
	pVehMod[17],
	pVehRental,
	pVehRentTime,
	pVehParked,
	pVehHouseGarage,
	pVehHelipadGarage,
	pVehFamiliesGarage,
	pVehBroken,
	pVehInsuranced,
	pVehFaction,
	pVehFactStored,
	bool:pVehImpounded,
	pVehImpoundDuration,
	pVehImpoundFee,
	pVehImpoundReason[128],
	vehDonation,
	pVehDCTime,
	pVehWeapon[3],
	pVehAmmo[3],
	Float: pVehCapacity,
	Float: pVehWeight,

	/* Vehicle Upgrade */
	pVehEngineUpgrade,
	pVehBodyUpgrade,
	Float:pVehBodyRepair,

    // not save
	bool:pVehExists,
	pVehPhysic,
	
    vehURL[128],
	vehAudio,
	vehSirenObject,
	vehSirenOn,
};
new PlayerVehicle[MAX_PRIVATE_VEHICLE][pvehdata],
Iterator:PvtVehicles<MAX_PRIVATE_VEHICLE + 1>;

enum e_vehiclebagasi
{
	vehiclebagasiID,
	vehiclebagasiTemp[32],
	vehiclebagasiModel,
	vehiclebagasiQuant
};
new VehicleBagasi[MAX_PLAYERS][e_vehiclebagasi];

enum vCore
{
    Float:vCoreHealth,
    vCoreFuel,
	bool: vehAdmin,
	vehAdminPhysic,
};
new VehicleCore[MAX_VEHICLES][vCore];

//Private Vehicle Player System Native
new const g_arrVehicleNames[212][] = {
	"Landstalker", "Bravura", "Buffalo", "Linerunner", "Perrenial", "Sentinel", "Dumper", "Firetruck", "Trashmaster",
	"Stretch", "Manana", "Infernus", "Voodoo", "Pony", "Mule", "Cheetah", "Ambulance", "Leviathan", "Moonbeam",
	"Esperanto", "Taxi", "Washington", "Bobcat", "Whoopee", "BF Injection", "Hunter", "Premier", "Enforcer",
	"Securicar", "Banshee", "Predator", "Bus", "Rhino", "Barracks", "Hotknife", "Trailer", "Previon", "Coach",
	"Cabbie", "Stallion", "Rumpo", "RC Bandit", "Romero", "Packer", "Monster", "Admiral", "Squalo", "Seasparrow",
	"Pizzaboy", "Tram", "Trailer", "Turismo", "Speeder", "Reefer", "Tropic", "Flatbed", "Yankee", "Caddy", "Solair",
	"Berkley's RC Van", "Skimmer", "PCJ-600", "Faggio", "Freeway", "RC Baron", "RC Raider", "Glendale", "Oceanic",
	"Sanchez", "Sparrow", "Patriot", "Quad", "Coastguard", "Dinghy", "Hermes", "Sabre", "Rustler", "ZR-350", "Walton",
	"Regina", "Comet", "BMX", "Burrito", "Camper", "Marquis", "Baggage", "Dozer", "Maverick", "News Chopper", "Rancher",
	"FBI Rancher", "Virgo", "Greenwood", "Jetmax", "Hotring", "Sandking", "Blista Compact", "Police Maverick",
	"Boxville", "Benson", "Mesa", "RC Goblin", "Hotring Racer A", "Hotring Racer B", "Bloodring Banger", "Rancher",
	"Super GT", "Elegant", "Journey", "Bike", "Mountain Bike", "Beagle", "Cropduster", "Stunt", "Tanker", "Roadtrain",
	"Nebula", "Majestic", "Buccaneer", "Shamal", "Hydra", "FCR-900", "NRG-500", "HPV1000", "Cement Truck", "Tow Truck",
	"Fortune", "Cadrona", "SWAT Truck", "Willard", "Forklift", "Tractor", "Combine", "Feltzer", "Remington", "Slamvan",
	"Blade", "Streak", "Freight", "Vortex", "Vincent", "Bullet", "Clover", "Sadler", "Firetruck", "Hustler", "Intruder",
	"Primo", "Cargobob", "Tampa", "Sunrise", "Merit", "Utility", "Nevada", "Yosemite", "Windsor", "Monster", "Monster",
	"Uranus", "Jester", "Sultan", "Stratum", "Elegy", "Raindance", "RC Tiger", "Flash", "Tahoma", "Savanna", "Bandito",
	"Freight Flat", "Streak Carriage", "Kart", "Mower", "Dune", "Sweeper", "Broadway", "Tornado", "AT-400", "DFT-30",
	"Huntley", "Stafford", "BF-400", "News Van", "Tug", "Trailer", "Emperor", "Wayfarer", "Euros", "Hotdog", "Club",
	"Freight Box", "Trailer", "Andromada", "Dodo", "RC Cam", "Launch", "LSPD Car", "SFPD Car", "LVPD Car",
	"Police Rancher", "Picador", "S.W.A.T", "Alpha", "Phoenix", "Glendale", "Sadler", "Luggage", "Luggage", "Stairs",
	"Boxville", "Tiller", "Utility Trailer"
};
new const g_Alphabet[26][] = {
	"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
	"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
};