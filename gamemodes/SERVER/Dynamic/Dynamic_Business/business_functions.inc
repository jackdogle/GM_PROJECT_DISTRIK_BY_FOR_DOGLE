#include <YSI\y_hooks>
#define MAX_DYNAMIC_BISNIS  100

enum E_BizInfo 
{
    bizOwner[MAX_PLAYER_NAME],
    bizName[128],
    bizType,
    bizLocked,
    bizMoney,
    bizVisit,
    bizRestock,
    Float:bizPoint[3],
    bizP[6],
    bizExtInt,
    bizExtVw,
    
    // not save
    STREAMER_TAG_3D_TEXT_LABEL:bizLabel,
};
new BisnisData[MAX_DYNAMIC_BISNIS][E_BizInfo],
    Iterator:Bisnis<MAX_DYNAMIC_BISNIS>;

stock Bisnis_Save(id)
{
    new cQuery[1048];
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `business` SET `Owner`='%s', ",  BisnisData[id][bizOwner]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Name`='%s', " cQuery, BisnisData[id][bizName]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Type`='%d', ", cQuery, BisnisData[id][bizType]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Locked`='%d', ", cQuery, BisnisData[id][bizLocked]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Money`='%d', ", cQuery, BisnisData[id][bizMoney]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PointX`='%f', ", cQuery, BisnisData[id][bizPoint][0]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PointY`='%f', ", cQuery, BisnisData[id][bizPoint][1]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`PointZ`='%f', ", cQuery, BisnisData[id][bizPoint][2]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Visit`='%d', ", cQuery, BisnisData[id][bizVisit]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ExtVW`='%d', ", cQuery, BisnisData[id][bizExtVw]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`ExtInt`='%d' ", cQuery, BisnisData[id][bizExtInt]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%sWHERE `ID` = '%d'", cQuery, id);
    
    return mysql_tquery(g_SQL, cQuery);
}

Bisnis_Refresh(id)
{
    if(id != -1)
    {
        if(DestroyDynamic3DTextLabel(BisnisData[id][bizLabel]))
            BisnisData[id][bizLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
        
        new sha[255], type[178];
        switch(BisnisData[id][bizType])
        {
            case 1: format(type, sizeof(type), "Warung");
            case 2: format(type, sizeof(type), "Toko Baju");
            case 3: format(type, sizeof(type), "Toko Olahraga");
            case 4: format(type, sizeof(type), "iBox Store");
        }
        if(stcmp(BisnisData[id][bizOwner], "-"))
        {
            format(sha, sizeof(sha), ""LIGHTGREY"[%s]\n"YELLOW"Unknows\n"WHITE"Tekan "GREEN"[Y]"WHITE" untuk Membeli", type);
        }
        else
        {
            format(sha, sizeof(sha), ""LIGHTGREY"[%s]\n"YELLOW"%s\n"WHITE"%s\nTekan "GREEN"[Y]"WHITE" untuk Membeli", type, BisnisData[id][bizName], BisnisData[id][bizOwner]);
        }

        if(BisnisData[id][bizPoint][0] != 0.0)
        {
            BisnisData[id][bizLabel] = CreateDynamic3DTextLabel(sha, -1, BisnisData[id][bizPoint][0], BisnisData[id][bizPoint][1], BisnisData[id][bizPoint][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, BisnisData[id][bizExtVw], BisnisData[id][bizExtInt], -1, 10.0, -1, 0);
        }
    }
    return 1;
}

Bisnis_Reset(id)
{
    format(BisnisData[id][bizOwner], MAX_PLAYER_NAME, "-");
    BisnisData[id][bizLocked] = 1;
    BisnisData[id][bizMoney] = 0;
    BisnisData[id][bizProd] = 0;
    BisnisData[id][bizVisit] = 0;
    BisnisData[id][bizRestock] = 0;
    Bisnis_Refresh(id);
}

CMD:bisnis(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 6)
        return PermissionError(playerid);
    
    new id = Iter_Free(Bisnis), query[512];
    if(id == -1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menambah Bisnis lagi!");
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    BisnisData[id][bizPoint][0] = x;
    BisnisData[id][bizPoint][1] = y;
    BisnisData[id][bizPoint][2] = z;
    format(BisnisData[id][bizName], 64, "-");
    BisnisData[id][bizExtInt] = GetPlayerInterior(playerid);
    BisnisData[id][bizExtVw] = GetPlayerVirtualWorld(playerid);
    BisnisData[id][bizLocked] = 0;
    BisnisData[id][bizMoney] = 0;
    BisnisData[id][bizProd] = 1000;
    BisnisData[id][bizVisit] = 0;
    BisnisData[id][bizRestock] = 1;
    return 1;
}