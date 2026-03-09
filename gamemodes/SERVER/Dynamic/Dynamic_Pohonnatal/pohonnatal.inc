#include <YSI_Coding\y_hooks>

#define MAX_XTREE 200
#define XMAS_DELAY (1 * 3600) // 1 jam (dalam detik)
new EditingXTree[MAX_PLAYERS] = { -1, ... };
new nataldelay[MAX_PLAYERS];
enum xtreeData
{
    bool:xtExists,
    xtSQL,
    Float:xtX,
    Float:xtY,
    Float:xtZ,
    xtObject,
    xtReward,
    Text3D:xtLabel // <-- TAMBAHAN INI
};
new XTree[MAX_XTREE][xtreeData];

hook OnGameModeInit()
{
    LoadXTree();
    return 1;
}

LoadXTree()
{
    mysql_tquery(g_SQL, "SELECT * FROM xmas_tree", "OnXTreeLoaded");
}

forward OnXTreeLoaded();
public OnXTreeLoaded()
{
    new rows = cache_num_rows();
    if(!rows) return 1;

    for(new i = 0; i < rows; i++)
    {
        XTree[i][xtExists] = true;
        cache_get_value_int(i, "id", XTree[i][xtSQL]);
        cache_get_value_float(i, "posx", XTree[i][xtX]);
        cache_get_value_float(i, "posy", XTree[i][xtY]);
        cache_get_value_float(i, "posz", XTree[i][xtZ]);
        cache_get_value_int(i, "reward", XTree[i][xtReward]);

        XTree[i][xtObject] = CreateDynamicObject(
            19076,
            XTree[i][xtX],
            XTree[i][xtY],
            XTree[i][xtZ]-1,
            0.0, 0.0, 0.0
        );

        new label[128];
        format(label, sizeof(label), "ID: %d\n/xcrismast", i);
        XTree[i][xtLabel] = CreateDynamic3DTextLabel(
            label,
            0x00FF00FF,
            XTree[i][xtX],
            XTree[i][xtY],
            XTree[i][xtZ] + 1.5,
            10.0,
            INVALID_PLAYER_ID,
            INVALID_VEHICLE_ID,
            0
        );
    }
    printf("[XMAS] Loaded %d Christmas Trees", rows);
    return 1;
}

CMD:createnatal(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new id = -1;
    for(new i=0;i<MAX_XTREE;i++)
    {
        if(!XTree[i][xtExists])
        {
            id = i;
            break;
        }
    }
    if(id == -1) return Error(playerid, "Slot pohon penuh!");

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    XTree[id][xtExists] = true;
    XTree[id][xtX] = x;
    XTree[id][xtY] = y;
    XTree[id][xtZ] = z;
    XTree[id][xtReward] = 1000;

    XTree[id][xtObject] = CreateDynamicObject(19076, x, y, z-1, 0, 0, 0);

    new label[128];
    format(label, sizeof(label), "ID: %d\n/xcrismast", id);
    XTree[id][xtLabel] = CreateDynamic3DTextLabel(
        label,
        0x00FF00FF,
        x,
        y,
        z + 1.5,
        10.0,
        INVALID_PLAYER_ID,
        INVALID_VEHICLE_ID,
        0
    );

    new query[256];
    mysql_format(g_SQL, query, sizeof(query),"INSERT INTO xmas_tree (posx, posy, posz, reward) VALUES (%f,%f,%f,%d)",x, y, z, 1000);
    mysql_tquery(g_SQL, query, "OnXTreeCreated", "d", id);

    SendClientMessage(playerid, -1, "{0EF134}Pohon Natal berhasil dibuat & tersimpan!");
    return 1;
}

forward OnXTreeCreated(id);
public OnXTreeCreated(id)
{
    XTree[id][xtSQL] = cache_insert_id();
    return 1;
}
CMD:deletenatal(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new id;
    if(sscanf(params, "d", id))
        return SendClientMessage(playerid, -1, "Gunakan: /deletenatal [id]");

    if(id < 0 || id >= MAX_XTREE)
        return Error(playerid, "ID pohon tidak valid!");

    if(!XTree[id][xtExists])
        return Error(playerid, "Pohon natal ini tidak ada!");

    // destroy object
    if(IsValidDynamicObject(XTree[id][xtObject]))
        DestroyDynamicObject(XTree[id][xtObject]);

    // destroy label
    if(IsValidDynamic3DTextLabel(XTree[id][xtLabel]))
        DestroyDynamic3DTextLabel(XTree[id][xtLabel]);

    // reset data
    XTree[id][xtExists] = false;
    XTree[id][xtObject] = INVALID_STREAMER_ID;
    XTree[id][xtLabel]  = Text3D:INVALID_3DTEXT_ID;
    XTree[id][xtX] = 0.0;
    XTree[id][xtY] = 0.0;
    XTree[id][xtZ] = 0.0;
    XTree[id][xtReward] = 0;

    // hapus dari database
    new query[256];
    mysql_format(g_SQL, query, sizeof(query),
        "DELETE FROM xmas_tree WHERE id = %d",
        id
    );
    mysql_tquery(g_SQL, query);

    SendClientMessage(playerid, -1, "{FF5555}Pohon Natal berhasil dihapus!");
    return 1;
}

CMD:editreward(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new id, money;
    if(sscanf(params, "dd", id, money))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editreward [treeid] [money]");

    if(id < 0 || id >= MAX_XTREE || !XTree[id][xtExists])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tree ID tidak valid!");

    XTree[id][xtReward] = money;

    new query[128];
    mysql_format(g_SQL, query, sizeof(query),
        "UPDATE xmas_tree SET reward=%d WHERE id=%d",
        money, XTree[id][xtSQL]
    );
    mysql_tquery(g_SQL, query);

    new str[128];
    format(str, sizeof(str), "{F10707}Reward pohon %d diubah menjadi {3AF50C}$%d", id, money);
    SendClientMessage(playerid, -1, str);
    return 1;
}

CheckXmasDelay(playerid, treeIndex)
{
    if(AccountData[playerid][pID] <= 0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Akun belum siap, relog!");

    if(XTree[treeIndex][xtSQL] <= 0)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tree belum tersinkron database!");

    new query[256];
    mysql_format(g_SQL, query, sizeof(query),"SELECT last_claim FROM xmas_claim WHERE player_uid=%d AND tree_id=%d",AccountData[playerid][pID],XTree[treeIndex][xtSQL]);
    mysql_tquery(g_SQL, query, "OnCheckXmasDelay", "dd", playerid, treeIndex);
    return 1;
}

forward OnCheckXmasDelay(playerid, treeIndex);
public OnCheckXmasDelay(playerid, treeIndex)
{
    if(cache_num_rows() > 0)
    {
        new sisa;
        cache_get_value_int(0, "last_claim", sisa);

        if(sisa > 0)
        {
            new sisa = nataldelay[playerid] / 60;
            new sisadetik = nataldelay[playerid] % 60;
            Info(playerid, "Waktu claim kembali benefi natal anda "YELLOW "%d menit %d detik", sisa, sisadetik);
            return 1;
        }

        // reward
        GiveMoney(playerid, XTree[treeIndex][xtReward]);
        nataldelay[playerid] = 3600;

        new q[256];
        mysql_format(g_SQL, q, sizeof(q),"UPDATE xmas_claim SET last_claim=%d WHERE player_uid=%d AND tree_id=%d",nataldelay[playerid],AccountData[playerid][pID],XTree[treeIndex][xtSQL]);
        mysql_tquery(g_SQL, q);
    }
    else
    {
        // pertama kali claim
        GiveMoney(playerid, XTree[treeIndex][xtReward]);
        nataldelay[playerid] = 3600;

        new q[256];
        mysql_format(g_SQL, q, sizeof(q),"INSERT INTO xmas_claim (player_uid, tree_id, last_claim) VALUES (%d,%d,%d)",AccountData[playerid][pID],XTree[treeIndex][xtSQL],nataldelay[playerid]);
        mysql_tquery(g_SQL, q);
    }

    new str[128];
    format(str, sizeof(str),"{15B4DB}Kamu mendapatkan $%d dari Pohon Natal!",XTree[treeIndex][xtReward]);
    SendClientMessage(playerid, -1, str);

    return 1;
}

CMD:xcrismast(playerid, params[])
{
    for(new i = 0; i < MAX_XTREE; i++)
    {
        if(XTree[i][xtExists])
        {
            if(IsPlayerInRangeOfPoint(playerid, 3.0,
                XTree[i][xtX],
                XTree[i][xtY],
                XTree[i][xtZ]))
            {
                CheckXmasDelay(playerid, i);
                return 1;
            }
        }
    }
    return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu tidak berada dekat Pohon Natal!");
}

CMD:editnatal(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new id;
    if(sscanf(params, "d", id))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/editnatal [treeid]");

    if(id < 0 || id >= MAX_XTREE || !XTree[id][xtExists])
        return ShowTDN(playerid, NOTIFICATION_ERROR, "ID pohon tidak valid!");

    if(!IsValidDynamicObject(XTree[id][xtObject]))
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Object pohon tidak valid!");

    EditingXTree[playerid] = id;

    EditDynamicObject(playerid, XTree[id][xtObject]);

    SendClientMessage(playerid, -1, "{F8E90E}Gunakan mouse untuk memindahkan pohon, lalu klik untuk menyimpan.");
    return 1;
}
CMD:listpohonnatal(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 5)
        return PermissionError(playerid);

    new list[2048], line[64];
    strcat(list, "ID\tReward\n");

    for(new i = 0; i < MAX_XTREE; i++)
    {
        if(XTree[i][xtExists])
        {
            format(line, sizeof(line), "%d\t$%d\n", i, XTree[i][xtReward]);
            strcat(list, line);
        }
    }

    ShowPlayerDialog(playerid, DIALOG_LIST_NATAL, DIALOG_STYLE_TABLIST_HEADERS, "List Pohon Natal", list, "Teleport", "Tutup");
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    //bagian dialog
    if(dialogid == DIALOG_LIST_NATAL)
    {
        if(!response) return 1;

        new count = -1;
        for(new i = 0; i < MAX_XTREE; i++)
        {
            if(XTree[i][xtExists])
            {
                count++;
                if(count == listitem)
                {
                    // ✅ TELEPORT KE POHON
                    SetPlayerPos(
                        playerid,
                        XTree[i][xtX],
                        XTree[i][xtY],
                        XTree[i][xtZ] + 1.0
                    );

                    new msg[128];
                    format(msg, sizeof(msg),
                        "{1DF516}Kamu diteleport ke Pohon Natal ID %d (Reward $%d)",
                        i, XTree[i][xtReward]
                    );
                    SendClientMessage(playerid, -1, msg);
                    break;
                }
            }
        }
    }
    return 1;
}

ptask UpdateNatalBenefit[1000](playerid)
{
    if(nataldelay[playerid] && nataldelay[playerid] > 0)
	{
		nataldelay[playerid]--;
		if(nataldelay[playerid] == 0)
		{
			nataldelay[playerid] = 0;
            Info(playerid, "Anda sudah dapat claim benefit natal kembali!");
		}
	}
    return 1;
}