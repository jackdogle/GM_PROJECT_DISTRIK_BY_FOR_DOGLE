#define MAX_RUSUN_ROOM   (1000)

#define MAX_OWNED_RUSUN 1

new EnterRusunTimer[MAX_PLAYERS] = { -1, ... };
new PlayerRusunInvite[MAX_PLAYERS][MAX_PLAYERS];

enum rusunRoom {
    rID,
    rOwner[MAX_PLAYER_NAME],
    rOwnerID,
    rName[128],
    rPrice,
    rInteriorInt,
    rInterior,
    rVW,

    Float:rExtPos[4],
    Float:rIntPos[4],

    rPickup,
    Text3D: rLabel,
    Text3D: rIntLabel
};

new RusunsData[MAX_RUSUN_ROOM][rusunRoom],
    Iterator:RusunDatas<MAX_RUSUN_ROOM>;