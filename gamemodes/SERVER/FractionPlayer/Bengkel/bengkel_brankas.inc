#include <YSI\y_hooks>

new repairkit,
    toolskit;

BrankasBengkel_Save()
{
    new sstr[512];
    format(sstr, sizeof(sstr), "UPDATE brankas_bengkel SET RepairKit='%d', ToolsKit='%d' WHERE id=0",
    repairkit, toolskit);
    return mysql_tquery(g_SQL, sstr);
}

function LoadBrankasBengkel()
{
    cache_get_value_name_int(0, "RepairKit", repairkit);
    cache_get_value_name_int(0, "ToolsKit", toolskit);
	printf("[Brankas] Loaded Data Brankas Bengkel...");
}

CMD:setbrankasbengkel(playerid, params[])
{
    new jumlah;
    if(CheckAdmin(playerid, 6))
        return PermissionError(playerid);
    
    if(sscanf(params, "d", jumlah))
        return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/setbrankasbengkel [jumlah]");

    repairkit = jumlah;
    toolskit = jumlah;
    BrankasBengkel_Save();
    ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Berhasil mengeset brankas sejumlah %d", jumlah));
    return 1;
}