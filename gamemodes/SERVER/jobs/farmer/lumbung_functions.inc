#include <YSI\y_hooks>

new Stock;

Lumbung_Save()
{
    new str[2024];

    format(str, sizeof str, "UPDATE lumbung SET stock='%d' WHERE id=0",
    Stock);
    return mysql_tquery(g_SQL, str);
}

function LoadLumbung()
{
    cache_get_value_name_int(0, "stock", Stock);
    printf("[Lumbung] Loaded Data Lumbung...");
}