#include <YSI\y_hooks>

enum    e_lemari
{
    lemariID,
    lemariTemp[64],
    lemariModel,
    accModel[4],
    accBone[4],
    Float:accPosX[4],
    Float:accPosY[4],
    Float:accPosZ[4],
    Float:accPosRX[4],
    Float:accPosRY[4],
    Float:accPosRZ[4],
    Float:accPosSX[4],
    Float:accPosSY[4],
    Float:accPosSZ[4],
};
new LemariData[MAX_PLAYERS][e_lemari];

enum e_lemaritoys
{
    accModel,
    accBone,
    Float:accPosX,
    Float:accPosY,
    Float:accPosZ,
    Float:accPosRX,
    Float:accPosRY,
    Float:accPosRZ,
    Float:accPosSX,
    Float:accPosSY,
    Float:accPosSZ,
};
new LemariAcc[MAX_PLAYERS][4][e_lemaritoys];

/* Commands */
CMD:sc(playerid, params[])
{
    if(!IsPlayerConnected(playerid)) return false;

    static 
        string[255];
    
    if(sscanf(params, "s[255]", string)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/sc [nama pakaian]");
    if(IsSameClothes(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pakaian ini sudah ada dilemari!");
    if(CountPlayerClothes(playerid) >= 3) return ShowTDN(playerid, NOTIFICATION_ERROR, "Lemari anda sudah penuh!");

    LemariData[playerid][lemariModel] = GetPlayerSkin(playerid);
    strunpack(LemariData[playerid][lemariTemp], string);

    for(new i = 0; i < 4; i ++)
    {
        if(IsPlayerAttachedObjectSlotUsed(playerid, i))
        {
            LemariAcc[playerid][i][accModel] = pToys[playerid][i][toy_model];
            LemariAcc[playerid][i][accBone] = pToys[playerid][i][toy_bone];
            LemariAcc[playerid][i][accPosX] = pToys[playerid][i][toy_x];
            LemariAcc[playerid][i][accPosY] = pToys[playerid][i][toy_y];
            LemariAcc[playerid][i][accPosZ] = pToys[playerid][i][toy_z];
            LemariAcc[playerid][i][accPosRX] = pToys[playerid][i][toy_rx];
            LemariAcc[playerid][i][accPosRY] = pToys[playerid][i][toy_ry];
            LemariAcc[playerid][i][accPosRZ] = pToys[playerid][i][toy_rz];
            LemariAcc[playerid][i][accPosSX] = pToys[playerid][i][toy_sx];
            LemariAcc[playerid][i][accPosSY] = pToys[playerid][i][toy_sy];
            LemariAcc[playerid][i][accPosSZ] = pToys[playerid][i][toy_sz];
        }
    }

    new cQuery[2118];
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `clothes_wardrobe` SET `IDs`=%d, `clothesName`='%s', `clothesModel`=%d,\
    `acc0_model`=%d, `acc0_bone`=%d, `acc0_posX`=%f, `acc0_posY`=%f, `acc0_posZ`=%f, `acc0_posRX`=%f, `acc0_posRY`=%f, `acc0_posRZ`=%f, `acc0_posSX`=%f, `acc0_posSY`=%f, `acc0_posSZ`=%f,\
    `acc1_model`=%d, `acc1_bone`=%d, `acc1_posX`=%f, `acc1_posY`=%f, `acc1_posZ`=%f, `acc1_posRX`=%f, `acc1_posRY`=%f, `acc1_posRZ`=%f, `acc1_posSX`=%f, `acc1_posSY`=%f, `acc1_posSZ`=%f,\
    `acc2_model`=%d, `acc2_bone`=%d, `acc2_posX`=%f, `acc2_posY`=%f, `acc2_posZ`=%f, `acc2_posRX`=%f, `acc2_posRY`=%f, `acc2_posRZ`=%f, `acc2_posSX`=%f, `acc2_posSY`=%f, `acc2_posSZ`=%f,\
    `acc3_model`=%d, `acc3_bone`=%d, `acc3_posX`=%f, `acc3_posY`=%f, `acc3_posZ`=%f, `acc3_posRX`=%f, `acc3_posRY`=%f, `acc3_posRZ`=%f, `acc3_posSX`=%f, `acc3_posSY`=%f, `acc3_posSZ`=%f",
    AccountData[playerid][pID], LemariData[playerid][lemariTemp], LemariData[playerid][lemariModel],
    LemariAcc[playerid][0][accModel], LemariAcc[playerid][0][accBone], LemariAcc[playerid][0][accPosX], LemariAcc[playerid][0][accPosY], LemariAcc[playerid][0][accPosZ], LemariAcc[playerid][0][accPosRX], LemariAcc[playerid][0][accPosRY], LemariAcc[playerid][0][accPosRZ], LemariAcc[playerid][0][accPosSX], LemariAcc[playerid][0][accPosSY], LemariAcc[playerid][0][accPosSZ],
    LemariAcc[playerid][1][accModel], LemariAcc[playerid][1][accBone], LemariAcc[playerid][1][accPosX], LemariAcc[playerid][1][accPosY], LemariAcc[playerid][1][accPosZ], LemariAcc[playerid][1][accPosRX], LemariAcc[playerid][1][accPosRY], LemariAcc[playerid][1][accPosRZ], LemariAcc[playerid][1][accPosSX], LemariAcc[playerid][1][accPosSY], LemariAcc[playerid][1][accPosSZ],
    LemariAcc[playerid][2][accModel], LemariAcc[playerid][2][accBone], LemariAcc[playerid][2][accPosX], LemariAcc[playerid][2][accPosY], LemariAcc[playerid][2][accPosZ], LemariAcc[playerid][2][accPosRX], LemariAcc[playerid][2][accPosRY], LemariAcc[playerid][2][accPosRZ], LemariAcc[playerid][2][accPosSX], LemariAcc[playerid][2][accPosSY], LemariAcc[playerid][2][accPosSZ],
    LemariAcc[playerid][3][accModel], LemariAcc[playerid][3][accBone], LemariAcc[playerid][3][accPosX], LemariAcc[playerid][3][accPosY], LemariAcc[playerid][3][accPosZ], LemariAcc[playerid][3][accPosRX], LemariAcc[playerid][3][accPosRY], LemariAcc[playerid][3][accPosRZ], LemariAcc[playerid][3][accPosSX], LemariAcc[playerid][3][accPosSY], LemariAcc[playerid][3][accPosSZ]);
    mysql_tquery(g_SQL, cQuery, "OnClothesDeposit", "d", playerid);
    return 1;
}

/* Functions */
forward OnClothesDeposit(playerid);
public OnClothesDeposit(playerid)
{
    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil menyimpan pakaian %s", LemariData[playerid][lemariTemp]));
    LemariData[playerid][lemariID] = -1;
    LemariData[playerid][lemariTemp] = EOS;
    LemariData[playerid][lemariModel] = 0;
    for(new i = 0; i < 4; i ++)
    {
        LemariAcc[playerid][i][accModel] = 0;
        LemariAcc[playerid][i][accBone] = 0;
        LemariAcc[playerid][i][accPosX] = 0;
        LemariAcc[playerid][i][accPosY] = 0;
        LemariAcc[playerid][i][accPosZ] = 0;
        LemariAcc[playerid][i][accPosRX] = 0;
        LemariAcc[playerid][i][accPosRY] = 0;
        LemariAcc[playerid][i][accPosRZ] = 0;
        LemariAcc[playerid][i][accPosSX] = 0;
        LemariAcc[playerid][i][accPosSY] = 0;
        LemariAcc[playerid][i][accPosSZ] = 0;
    }
    return 1;
}

IsSameClothes(playerid)
{
    new dbstr[255], Cache:execute;
    mysql_format(g_SQL, dbstr, sizeof(dbstr), "SELECT * FROM `clothes_wardrobe` WHERE `IDs`=%d", AccountData[playerid][pID]);
    execute = mysql_query(g_SQL, dbstr, true);
    new rows = cache_num_rows();
    if(rows)
    {
        new model;
        for(new x; x < rows; ++x)
        {
            cache_get_value_name_int(x, "clothesModel", model);

            if(GetPlayerSkin(playerid) == model)
                return 1;
        }
    }
    cache_delete(execute);
    return 0;
}

CountPlayerClothes(playerid)
{
    new dbstr[255], count = 0;
    mysql_format(g_SQL, dbstr, sizeof(dbstr), "SELECT * FROM `clothes_wardrobe` WHERE `IDs`=%d", AccountData[playerid][pID]);
    mysql_query(g_SQL, dbstr);
    new rows = cache_num_rows();
    if(rows)
    {
        count = rows;
    }
    return count;
}

ShowPlayerClothes(playerid)
{
    new dbstr[255], Cache:execute;
    mysql_format(g_SQL, dbstr, sizeof(dbstr), "SELECT * FROM `clothes_wardrobe` WHERE `IDs`=%d", AccountData[playerid][pID]);
    execute = mysql_query(g_SQL, dbstr, true);
    new rows = cache_num_rows();
    if(rows)
    {
        new list[500], frmtname[128];
        for(new i; i < rows; ++i)
        {
            cache_get_value_name(i, "clothesName", frmtname);

            format(list, sizeof(list), "%s%s\n", list, frmtname);
        }
        ShowPlayerDialog(playerid, DIALOG_CLOTHES, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Lemari Pakaian", list, "Pilih", "Batal");
    }
    else 
    {
        PlayerPlaySound(playerid, 5206, 0.0, 0.0, 0.0);
        ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Lemari Pakaian",
        "Anda tidak memiliki pakaian tersimpan!", "Tutup", "");
    }
    cache_delete(execute);
    return 1;
}

DropClothesPlayer(playerid)
{
    new dbstr[255];
    mysql_format(g_SQL, dbstr, sizeof(dbstr), "SELECT * FROM `clothes_wardrobe` WHERE `IDs`=%d", AccountData[playerid][pID]);
    mysql_query(g_SQL, dbstr);
    if(cache_num_rows())
    {
        new list[500], frmtname[128];
        for(new i; i < cache_num_rows(); ++ i)
        {
            cache_get_value_name(i, "clothesName", frmtname);
            
            format(list, sizeof(list), "%s%s\n", list, frmtname);
        }
        ShowPlayerDialog(playerid, DIALOG_CLOTHES_DELETE, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Buang Pakaian", list, "Buang", "Batal");
    }
    else 
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak sedang memakai pakaian tersimpan apapun!");
    }
    return 1;
}

/* Dialogs */
hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_CLOTHES:
        {
            if(!response) return 1;
            new dbstr[512];
            mysql_format(g_SQL, dbstr, sizeof(dbstr), "SELECT * FROM `clothes_wardrobe` WHERE `IDs`=%d", AccountData[playerid][pID]);
            mysql_query(g_SQL, dbstr);
            if(cache_num_rows() > 0)
            {
                new clothesname[125], clothesmodel;
                if(listitem >= 0 && listitem < cache_num_rows())
                {
                    cache_get_value_name(listitem, "clothesName", clothesname);
                    cache_get_value_name_int(listitem, "clothesModel", clothesmodel);

                    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil menggunakan pakaian %s", clothesname));
                    SetPlayerSkinEx(playerid, clothesmodel);

                    new accecorisModel[4], accecorisBone[4], Float:accecorisX[4], Float:accecorisY[4], Float:accecorisZ[4], Float:accecorisRX[4], Float:accecorisRY[4], Float:accecorisRZ[4], Float:accecorisSX[4], Float:accecorisSY[4], Float:accecorisSZ[4];
                    
                    // Mengambil data aksesoris
                    cache_get_value_name_int(listitem, "acc0_model", accecorisModel[0]);
                    cache_get_value_name_int(listitem, "acc0_bone", accecorisBone[0]);
                    cache_get_value_name_float(listitem, "acc0_posX", accecorisX[0]);
                    cache_get_value_name_float(listitem, "acc0_posY", accecorisY[0]);
                    cache_get_value_name_float(listitem, "acc0_posZ", accecorisZ[0]);
                    cache_get_value_name_float(listitem, "acc0_posRX", accecorisRX[0]);
                    cache_get_value_name_float(listitem, "acc0_posRY", accecorisRY[0]);
                    cache_get_value_name_float(listitem, "acc0_posRZ", accecorisRZ[0]);
                    cache_get_value_name_float(listitem, "acc0_posSX", accecorisSX[0]);
                    cache_get_value_name_float(listitem, "acc0_posSY", accecorisSY[0]);
                    cache_get_value_name_float(listitem, "acc0_posSZ", accecorisSZ[0]);
                    
                    cache_get_value_name_int(listitem, "acc1_model", accecorisModel[1]);
                    cache_get_value_name_int(listitem, "acc1_bone", accecorisBone[1]);
                    cache_get_value_name_float(listitem, "acc1_posX", accecorisX[1]);
                    cache_get_value_name_float(listitem, "acc1_posY", accecorisY[1]);
                    cache_get_value_name_float(listitem, "acc1_posZ", accecorisZ[1]);
                    cache_get_value_name_float(listitem, "acc1_posRX", accecorisRX[1]);
                    cache_get_value_name_float(listitem, "acc1_posRY", accecorisRY[1]);
                    cache_get_value_name_float(listitem, "acc1_posRZ", accecorisRZ[1]);
                    cache_get_value_name_float(listitem, "acc1_posSX", accecorisSX[1]);
                    cache_get_value_name_float(listitem, "acc1_posSY", accecorisSY[1]);
                    cache_get_value_name_float(listitem, "acc1_posSZ", accecorisSZ[1]);
                    
                    cache_get_value_name_int(listitem, "acc2_model", accecorisModel[2]);
                    cache_get_value_name_int(listitem, "acc2_bone", accecorisBone[2]);
                    cache_get_value_name_float(listitem, "acc2_posX", accecorisX[2]);
                    cache_get_value_name_float(listitem, "acc2_posY", accecorisY[2]);
                    cache_get_value_name_float(listitem, "acc2_posZ", accecorisZ[2]);
                    cache_get_value_name_float(listitem, "acc2_posRX", accecorisRX[2]);
                    cache_get_value_name_float(listitem, "acc2_posRY", accecorisRY[2]);
                    cache_get_value_name_float(listitem, "acc2_posRZ", accecorisRZ[2]);
                    cache_get_value_name_float(listitem, "acc2_posSX", accecorisSX[2]);
                    cache_get_value_name_float(listitem, "acc2_posSY", accecorisSY[2]);
                    cache_get_value_name_float(listitem, "acc2_posSZ", accecorisSZ[2]);

                    cache_get_value_name_int(listitem, "acc3_model", accecorisModel[3]);
                    cache_get_value_name_int(listitem, "acc3_bone", accecorisBone[3]);
                    cache_get_value_name_float(listitem, "acc3_posX", accecorisX[3]);
                    cache_get_value_name_float(listitem, "acc3_posY", accecorisY[3]);
                    cache_get_value_name_float(listitem, "acc3_posZ", accecorisZ[3]);
                    cache_get_value_name_float(listitem, "acc3_posRX", accecorisRX[3]);
                    cache_get_value_name_float(listitem, "acc3_posRY", accecorisRY[3]);
                    cache_get_value_name_float(listitem, "acc3_posRZ", accecorisRZ[3]);
                    cache_get_value_name_float(listitem, "acc3_posSX", accecorisSX[3]);
                    cache_get_value_name_float(listitem, "acc3_posSY", accecorisSY[3]);
                    cache_get_value_name_float(listitem, "acc3_posSZ", accecorisSZ[3]);

                    // Terapkan aksesoris ke karakter pemain
                    if(accecorisModel[0] != 0.0)
                    {
                        SetPlayerAttachedObject(playerid,
                        0,
                        accecorisModel[0],
                        accecorisBone[0],
                        accecorisX[0],
                        accecorisY[0],
                        accecorisZ[0],
                        accecorisRX[0],
                        accecorisRY[0],
                        accecorisRZ[0],
                        accecorisSX[0],
                        accecorisSY[0],
                        accecorisSZ[0]);

                        pToys[playerid][0][toy_model] = accecorisModel[0];
                        pToys[playerid][0][toy_bone] = accecorisBone[0];
                        pToys[playerid][0][toy_x] = accecorisX[0];
                        pToys[playerid][0][toy_y] = accecorisY[0];
                        pToys[playerid][0][toy_z] = accecorisZ[0];
                        pToys[playerid][0][toy_rx] = accecorisRX[0];
                        pToys[playerid][0][toy_ry] = accecorisRY[0];
                        pToys[playerid][0][toy_rz] = accecorisRZ[0];
                        pToys[playerid][0][toy_sx] = accecorisSX[0];
                        pToys[playerid][0][toy_sy] = accecorisSY[0];
                        pToys[playerid][0][toy_sz] = accecorisSZ[0];
                    }
                    
                    if(accecorisModel[1] != 0.0)
                    {
                        SetPlayerAttachedObject(playerid,
                        1,
                        accecorisModel[1],
                        accecorisBone[1],
                        accecorisX[1],
                        accecorisY[1],
                        accecorisZ[1],
                        accecorisRX[1],
                        accecorisRY[1],
                        accecorisRZ[1],
                        accecorisSX[1],
                        accecorisSY[1],
                        accecorisSZ[1]);

                        pToys[playerid][1][toy_model] = accecorisModel[1];
                        pToys[playerid][1][toy_bone] = accecorisBone[1];
                        pToys[playerid][1][toy_x] = accecorisX[1];
                        pToys[playerid][1][toy_y] = accecorisY[1];
                        pToys[playerid][1][toy_z] = accecorisZ[1];
                        pToys[playerid][1][toy_rx] = accecorisRX[1];
                        pToys[playerid][1][toy_ry] = accecorisRY[1];
                        pToys[playerid][1][toy_rz] = accecorisRZ[1];
                        pToys[playerid][1][toy_sx] = accecorisSX[1];
                        pToys[playerid][1][toy_sy] = accecorisSY[1];
                        pToys[playerid][1][toy_sz] = accecorisSZ[1];
                    }

                    if(accecorisModel[2] != 0.0)
                    {
                        SetPlayerAttachedObject(playerid,
                        2,
                        accecorisModel[2],
                        accecorisBone[2],
                        accecorisX[2],
                        accecorisY[2],
                        accecorisZ[2],
                        accecorisRX[2],
                        accecorisRY[2],
                        accecorisRZ[2],
                        accecorisSX[2],
                        accecorisSY[2],
                        accecorisSZ[2]);

                        pToys[playerid][2][toy_model] = accecorisModel[2];
                        pToys[playerid][2][toy_bone] = accecorisBone[2];
                        pToys[playerid][2][toy_x] = accecorisX[2];
                        pToys[playerid][2][toy_y] = accecorisY[2];
                        pToys[playerid][2][toy_z] = accecorisZ[2];
                        pToys[playerid][2][toy_rx] = accecorisRX[2];
                        pToys[playerid][2][toy_ry] = accecorisRY[2];
                        pToys[playerid][2][toy_rz] = accecorisRZ[2];
                        pToys[playerid][2][toy_sx] = accecorisSX[2];
                        pToys[playerid][2][toy_sy] = accecorisSY[2];
                        pToys[playerid][2][toy_sz] = accecorisSZ[2];
                    }

                    if(accecorisModel[3] != 0.0)
                    {
                        SetPlayerAttachedObject(playerid,
                        3,
                        accecorisModel[3],
                        accecorisBone[3],
                        accecorisX[3],
                        accecorisY[3],
                        accecorisZ[3],
                        accecorisRX[3],
                        accecorisRY[3],
                        accecorisRZ[3],
                        accecorisSX[3],
                        accecorisSY[3],
                        accecorisSZ[3]);

                        pToys[playerid][3][toy_model] = accecorisModel[3];
                        pToys[playerid][3][toy_bone] = accecorisBone[3];
                        pToys[playerid][3][toy_x] = accecorisX[3];
                        pToys[playerid][3][toy_y] = accecorisY[3];
                        pToys[playerid][3][toy_z] = accecorisZ[3];
                        pToys[playerid][3][toy_rx] = accecorisRX[3];
                        pToys[playerid][3][toy_ry] = accecorisRY[3];
                        pToys[playerid][3][toy_rz] = accecorisRZ[3];
                        pToys[playerid][3][toy_sx] = accecorisSX[3];
                        pToys[playerid][3][toy_sy] = accecorisSY[3];
                        pToys[playerid][3][toy_sz] = accecorisSZ[3];
                    }
                }
            }
        }
        case DIALOG_CLOTHES_DELETE:
        {
            if(!response) return ShowTDN(playerid, NOTIFICATION_INFO, "Anda telah membatalkan pilihan");
            new dbstr[512];
            mysql_format(g_SQL, dbstr, sizeof(dbstr), "SELECT * FROM `clothes_wardrobe` WHERE `IDs`=%d", AccountData[playerid][pID]);
            mysql_query(g_SQL, dbstr);
            if(cache_num_rows())
            {
                new frmtname[255], clothesmodel;

                cache_get_value_name(listitem, "clothesName", frmtname);
                cache_get_value_name_int(listitem, "clothesModel", clothesmodel);

                ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil membuang pakaian %s", frmtname));

                new query[200];
                mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `clothes_wardrobe` WHERE `clothesModel` = %d", clothesmodel);
                mysql_tquery(g_SQL, query);
            }
        }
    }
    return 1;
}
