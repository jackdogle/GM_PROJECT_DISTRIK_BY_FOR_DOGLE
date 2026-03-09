new
    PoliceMoneyVault,
    PemerintahMoneyVault,
    EMSMoneyVault,
    RestoMoneyVault,
    GojekMoneyVault,
    BengkelMoneyVault,
    TransMoneyVault;

forward LoadBrankasGoodside();
public LoadBrankasGoodside()
{
    cache_get_value_name_int(0, "bengkelmoneyvault", BengkelMoneyVault);
    cache_get_value_name_int(0, "policemoneyvault", PoliceMoneyVault);
    cache_get_value_name_int(0, "pemerintahmoneyvault", PemerintahMoneyVault);
    cache_get_value_name_int(0, "emsmoneyvault", EMSMoneyVault);
    cache_get_value_name_int(0, "restomoneyvault", RestoMoneyVault);
    cache_get_value_name_int(0, "gojekmoneyvault", GojekMoneyVault);
    cache_get_value_name_int(0, "transmoneyvault", TransMoneyVault);
    cache_get_value_name_int(0, "globaltime_rusun", g_RusunTime);
    printf("[Saldo Goodside]: Jumlah total Saldo Faction yang dimuat 5.");
}