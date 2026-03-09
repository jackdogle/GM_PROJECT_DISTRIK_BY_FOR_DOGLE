#include <YSI\y_hooks>

enum _:playerdamage
{
    bool:dlogExists,

    dlogOwnerID,
    dlogOwner[MAX_PLAYER_NAME],
    dlogWeapon,
    dlogBodyPart,
    Float:dlogAmount,
    dlogSender[MAX_PLAYER_NAME],
    dlogTime   
};
new DamageData[MAX_PLAYERS][playerdamage];
new GetDamageID[MAX_PLAYERS] = INVALID_PLAYER_ID;

forward LoadPlayerDamage(playerid);
public LoadPlayerDamage(playerid)
{
    new Cache:Dmgcache;
    if(cache_num_rows())
    {
        Dmgcache = cache_save();

        for(new i = 0; i < cache_num_rows(); i++)
        {
            cache_get_value_name_int(i, "IDs", DamageData[playerid][dlogOwnerID]);
            cache_get_value_name(i, "Owner", DamageData[playerid][dlogOwner]);
            cache_get_value_name_int(i, "Weapon", DamageData[playerid][dlogWeapon]);
            cache_get_value_name_int(i, "BodyPart", DamageData[playerid][dlogBodyPart]);
            cache_get_value_name_float(i, "Amount", DamageData[playerid][dlogAmount]);
            cache_get_value_name(i, "Sender", DamageData[playerid][dlogSender]);
            cache_get_value_name_int(i, "Time", DamageData[playerid][dlogTime]);
            
            DamageData[playerid][dlogExists] = true;
        }
        printf("[Damage Log]: Sistem telah meload damage logs %s(%d)", AccountData[playerid][pName], playerid);

        if(cache_is_valid(Dmgcache))
        {
            cache_delete(Dmgcache);
            printf("[Dynamic Damage Log]: Cache berhasil dihapus.");
        }
        else
        {
            printf("[Dynamic Damage Log]: Cache tidak valid atau sudah dihapus.");
        }
    }
    return 1;
}

hook OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	if(damagedid != INVALID_PLAYER_ID)
	{
		GetDamageID[damagedid] = playerid;
	}
	return 1;
}

hook OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
    if(!AccountData[playerid][pSpawned])
        return 0;
    
    if(IsPlayerInEvent(playerid))
        return 0;

    static issuer[64];
    if(GetDamageID[playerid] != INVALID_PLAYER_ID)
    {
        format(issuer, MAX_PLAYER_NAME, ReturnName(issuerid));
    }
    else
    {
        format(issuer, MAX_PLAYER_NAME, "Diri sendiri");
    }
    
    DamageData[playerid][dlogExists] = true;
    DamageData[playerid][dlogOwnerID] = AccountData[playerid][pID];
    format(DamageData[playerid][dlogOwner], MAX_PLAYER_NAME, AccountData[playerid][pName]);
    DamageData[playerid][dlogWeapon] = weaponid;
    DamageData[playerid][dlogBodyPart] = bodypart;
    DamageData[playerid][dlogAmount] = amount;
    format(DamageData[playerid][dlogSender], MAX_PLAYER_NAME, issuer);
    DamageData[playerid][dlogTime] = gettime();
    
    mysql_tquery(g_SQL, sprintf("INSERT INTO `damages` SET `IDs`=%d, `Owner`='%s', `Weapon`=%d, `BodyPart`=%d, `Amount`='%.1f', `Sender`='%s', `Time`=%d", 
    DamageData[playerid][dlogOwnerID], DamageData[playerid][dlogOwner], DamageData[playerid][dlogWeapon], DamageData[playerid][dlogBodyPart], DamageData[playerid][dlogAmount], DamageData[playerid][dlogSender], DamageData[playerid][dlogTime]));
    return 1;
}

Damage_Show(playerid, player)
{
    if(DamageData[player][dlogExists])
    {
        new list[4096];
    }
}