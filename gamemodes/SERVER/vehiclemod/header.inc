enum E_VEH_OBJECT {
    vehObjectID, // Untuk Menampung ID SQL Vehicle Acc
    vehObjectVehicleIndex, // Untuk mengampung ID SQL Vehicle
    vehObjectType, // Untuk menampung tipe object 
    vehObjectModel, // Untuk menampung model Object 
    vehObjectColor, // Untuk menampung warna object 

    vehObjectText[32], // Untuk menampung Text object
    vehObjectFont[24], // Untuk menampung font object
    vehObjectFontSize, // Untuk menampung size font dari si text 
    vehObjectFontColor, // Untuk menampung warna dari text 

    vehObject, // sebagai STREAMER ID object 
    
    bool:vehObjectExists, // Flagger untuk status object slot, true jika ada, false jika kosong

    Float:vehObjectPosX, // Coordinate dari object ketika attach ke kendaraan 
    Float:vehObjectPosY, // Coordinate dari object ketika attach ke kendaraan
    Float:vehObjectPosZ, // Coordinate dari object ketika attach ke kendaraan
    Float:vehObjectPosRX, // Coordinate dari object ketika attach ke kendaraan
    Float:vehObjectPosRY, // Coordinate dari object ketika attach ke kendaraan
    Float:vehObjectPosRZ // Coordinate dari object ketika attach ke kendaraan
};
new VehicleObjects[MAX_PRIVATE_VEHICLE][MAX_VEHICLE_OBJECT][E_VEH_OBJECT];