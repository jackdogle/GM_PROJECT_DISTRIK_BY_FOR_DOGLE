RGBAToARGB(rgba)
    return rgba >>> 8 | rgba << 24;

HideProgressBar(playerid)
{
	for(new i = 0; i < 3; i ++)
	{
		PlayerTextDrawHide(playerid, ProgressBar[playerid][i]);
	}
	return 1;
}

ShowProgressBar(playerid)
{
	PlayerTextDrawTextSize(playerid, ProgressBar[playerid][1], 0, 3.0);

	PlayerTextDrawShow(playerid, ProgressBar[playerid][0]);
	PlayerTextDrawShow(playerid, ProgressBar[playerid][1]);
	PlayerTextDrawShow(playerid, ProgressBar[playerid][2]);
	return 1;
}


ShowKTA(playerid, targetid)
{
	if(AccountData[playerid][pFaction] == FACTION_NONE) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda bukan anggota Faction manapun!");
	if(!PlayerHasItem(playerid, "KTA")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak memiliki Kartu Tanda Anggota!");

	PlayerTextDrawSetString(targetid, KTAtextdraws[targetid][25], sprintf("%s", GetFactName(playerid)));
	PlayerTextDrawSetString(targetid, KTAtextdraws[targetid][34], sprintf("%s", ReturnName(playerid)));
	PlayerTextDrawSetString(targetid, KTAtextdraws[targetid][35], sprintf("%s", GetFactionRank(playerid)));
	PlayerTextDrawSetPreviewModel(targetid, KTAtextdraws[targetid][36], AccountData[playerid][pSkin]);
	for(new i = 0; i < 41; i ++) 
	{
		PlayerTextDrawShow(targetid, KTAtextdraws[targetid][i]);
	}
	Info(targetid, "Gunakan "VERONA"'/hidekta'"WHITE" untuk menghilangkan/menutup textdraw KTA");
	return 1;
}

/*GasFuelNearby(playerid)
{
	for(new i = 0; i < sizeof(PomNearest); i++)
	{
		new Float:X, Float:Y, Float:Z;
		GetPlayerPos(playerid, X, Y, Z);
		new Float:dist = GetDistanceBetweenPoints(PomNearest[i][0], PomNearest[i][1], PomNearest[i][2], X, Y, Z);

		if(dist <= 350.0)
		{
			return i;
		}
	}
	return -1;
}*/

NearPlayerOpenStorage(playerid)
{
	foreach(new i : Player) if (IsPlayerConnected(i)) if (i != playerid) if (IsPlayerNearPlayer(playerid, i, 3.0))
	{
		if(AccountData[i][menuShowed]) return 1;
	}
	return 0;
}

stock const FactName[8][] = 
{
	"Warga",
	"Kepolisian District ",
	"Pemerintah District ",
	"EMS Kota District ",
	"Transportasi District ",
	"Bengkel District ",
	"Pedagang District ",
	"Tentara District "
};

stock const FamsRankName[7][] = 
{
	"N/A",
	"Relasi",
	"Outsider",
	"Insider",
	"Tangan Kanan",
	"Wakil Ketua",
	"Ketua"
};

stock SetPlayerFace(playerid, Float:X, Float:Y)
{
	new Float:pX, Float:pY, Float:pZ, Float:ang;
	GetPlayerPos(playerid, pX, pY, pZ);

	if(Y > pY) ang = (-acos((X - pX) / floatsqroot((X - pX)*(X - pX) + (Y - pY)*(Y - pY))) - 90.0);
	else if(Y < pY && X < pX) ang = (acos((X - pX) / floatsqroot((X - pX)*(X - pX) + (Y - pY)*(Y - pY))) - 450.0);
	else if(Y < pY) ang = (acos((X - pX) / floatsqroot((X - pX)*(X - pX) + (Y - pY)*(Y - pY))) - 90.0);

	if(X > pX) ang = (floatabs(floatabs(ang) + 180.0));
	else ang = (floatabs(ang) - 180.0);

	SetPlayerFacingAngle(playerid, ang);
	return false;
}

stock ShowBox(playerid, const text[] = "")
{
	PlayerTextDrawSetString(playerid, BusWait[playerid][0], text);
	PlayerTextDrawShow(playerid, BusWait[playerid][0]);
	SetTimerEx("HideBoxText", 5000, false, "d", playerid);
	return 1;
}

FUNC::HideBoxText(playerid)
{
	PlayerTextDrawHide(playerid, BusWait[playerid][0]);
	return 1;
}

SidejobVehicles(vehicleid)
{
	for(new i = 0; i < sizeof(ForkliftVehicles); i++)
	{
		if(vehicleid == ForkliftVehicles[i]) return 1;
	}
	for(new i = 0; i < sizeof(SweeperVehicles); i++)
	{
		if(vehicleid == SweeperVehicles[i]) return 1;
	}
	for(new i = 0; i < sizeof(DeliveryVehicles); i++)
	{
		if(vehicleid == DeliveryVehicles[i]) return 1;
	}
	for(new i = 0; i < sizeof(MowerVehicles); i++)
	{
		if(vehicleid == MowerVehicles[i]) return 1;
	}
	for(new i = 0; i < sizeof(TrashmasterVehicles); i++)
	{
		if(vehicleid == TrashmasterVehicles[i]) return 1;
	}
	return 0;
}

GetRekeningOwner(rekening)
{
    foreach(new i : Player) if (AccountData[i][pBankRek] == rekening)
    {
        return i;
    }
    return -1;
}

SavePlayerWeapon(playerid)
{
	new query[529];
	mysql_format(g_SQL, query, sizeof(query), "UPDATE `player_characters` SET ");
	mysql_format(g_SQL, query, sizeof(query), "%s`Gun1` = %d, ", query, AccountData[playerid][pGuns][0]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Gun2` = %d, ", query, AccountData[playerid][pGuns][1]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Gun3` = %d, ", query, AccountData[playerid][pGuns][2]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Gun4` = %d, ", query, AccountData[playerid][pGuns][3]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Gun5` = %d, ", query, AccountData[playerid][pGuns][4]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Gun6` = %d, ", query, AccountData[playerid][pGuns][5]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Gun7` = %d, ", query, AccountData[playerid][pGuns][6]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Gun8` = %d, ", query, AccountData[playerid][pGuns][7]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Gun9` = %d, ", query, AccountData[playerid][pGuns][8]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Gun10` = %d, ", query, AccountData[playerid][pGuns][9]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Gun11` = %d, ", query, AccountData[playerid][pGuns][10]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Gun12` = %d, ", query, AccountData[playerid][pGuns][11]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Gun13` = %d, ", query, AccountData[playerid][pGuns][12]);
	
	mysql_format(g_SQL, query, sizeof(query), "%s`Ammo1` = %d, ", query, AccountData[playerid][pAmmo][0]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Ammo2` = %d, ", query, AccountData[playerid][pAmmo][1]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Ammo3` = %d, ", query, AccountData[playerid][pAmmo][2]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Ammo4` = %d, ", query, AccountData[playerid][pAmmo][3]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Ammo5` = %d, ", query, AccountData[playerid][pAmmo][4]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Ammo6` = %d, ", query, AccountData[playerid][pAmmo][5]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Ammo7` = %d, ", query, AccountData[playerid][pAmmo][6]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Ammo8` = %d, ", query, AccountData[playerid][pAmmo][7]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Ammo9` = %d, ", query, AccountData[playerid][pAmmo][8]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Ammo10` = %d, ", query, AccountData[playerid][pAmmo][9]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Ammo11` = %d, ", query, AccountData[playerid][pAmmo][10]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Ammo12` = %d, ", query, AccountData[playerid][pAmmo][11]);
	mysql_format(g_SQL, query, sizeof(query), "%s`Ammo13` = %d ", query, AccountData[playerid][pAmmo][12]);
	mysql_format(g_SQL, query, sizeof(query), "%sWHERE `pID` = %d", query, AccountData[playerid][pID]);
	return mysql_tquery(g_SQL, query);
}

/*System Native*/
UpdatePlayerData(playerid)
{
    if(!AccountData[playerid][pSpawned])
        return 0;
        
    new
        cQuery[5000], PlayerIP[16];
    
    if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING && !IsPlayerInEvent(playerid))
    {
        /* Pengambilan posisi (GetPlayerPos) dihapus dari sini.
           Script akan menggunakan nilai pPosX, pPosY, pPosZ yang 
           sudah kita set di OnPlayerDisconnect sebelum fungsi ini dipanggil.
        */

        GetPlayerHealth(playerid, AccountData[playerid][pHealth]);
        GetPlayerArmour(playerid, AccountData[playerid][pArmour]);
        AccountData[playerid][pWorld] = GetPlayerVirtualWorld(playerid);
        AccountData[playerid][pInt] = GetPlayerInterior(playerid);

        if(!AccountData[playerid][pInjured] && AccountData[playerid][pHealth] == 0.0) {
            AccountData[playerid][pHealth] = 100.0;
        }
    }
    GetPlayerIp(playerid, PlayerIP, sizeof (PlayerIP));
    
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "UPDATE `player_characters` SET ");
    
    forex(i, 13)
    {
        mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Gun%d` = %d, `Ammo%d` = %d, ", cQuery, i + 1, AccountData[playerid][pGuns][i], i + 1, AccountData[playerid][pAmmo][i]);
    }

    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Name` = '%e', ", cQuery, AccountData[playerid][pName]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_AdminName` = '%e', ", cQuery, AccountData[playerid][pAdminname]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_IP` = '%s', ", cQuery, PlayerIP);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Admin` = '%d', ", cQuery, AccountData[playerid][pAdmin]);

    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_TheStars` = '%d', ", cQuery, AccountData[playerid][pTheStars]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_TheStarsTime` = '%d', ", cQuery, AccountData[playerid][pTheStarsTime]);

    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_HandleGoodside` = '%d', ", cQuery, AccountData[playerid][pHandleGoodside]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_HandleBadside` = '%d', ", cQuery, AccountData[playerid][pHandleBadside]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_HandleBanned` = '%d', ", cQuery, AccountData[playerid][pHandleBanned]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_AdminGirl` = '%d', ", cQuery, AccountData[playerid][pAdminGirl]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_AdminToggle` = '%d', ", cQuery, AccountData[playerid][pTogAC]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_AdminPoint` = '%d', ", cQuery, AccountData[playerid][aReceivedReports]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Level` = '%d', ", cQuery, AccountData[playerid][pLevel]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_LevelUp` = '%d', ", cQuery, AccountData[playerid][pLevelUp]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Vip` = '%d', ", cQuery, AccountData[playerid][pVip]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_VipTime` = '%d', ", cQuery, AccountData[playerid][pVipTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Slotveh` = '%d', ", cQuery, AccountData[playerid][pExtraVehSlot]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SlotHouse` = '%d', ", cQuery, AccountData[playerid][pHouseSlot]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Money` = '%d', ", cQuery, AccountData[playerid][pMoney]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_BankMoney` = '%d', ", cQuery, AccountData[playerid][pBankMoney]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_RedMoney` = '%d', ", cQuery, AccountData[playerid][pRedMoney]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Gopay` = '%d', ", cQuery, AccountData[playerid][pSaldoGopay]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_BankRek` = '%d', ", cQuery, AccountData[playerid][pBankRek]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_PhoneNum` = '%s', ", cQuery, AccountData[playerid][pPhone]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Hours` = '%d', ", cQuery, AccountData[playerid][pHours]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Minutes` = '%d', ", cQuery, AccountData[playerid][pMinutes]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Seconds` = '%d', ", cQuery, AccountData[playerid][pSeconds]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Payday` = '%d', ", cQuery, AccountData[playerid][pPaycheck]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Skin` = '%d', ", cQuery, AccountData[playerid][pSkin]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Gender` = '%d', ", cQuery, AccountData[playerid][pGender]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Age` = '%s', ", cQuery, AccountData[playerid][pAge]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Origin` = '%s', ", cQuery, AccountData[playerid][pOrigin]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_BodyHeight` = '%d', ", cQuery, AccountData[playerid][pTinggiBadan]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_BodyWeight` = '%d', ", cQuery, AccountData[playerid][pBeratBadan]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_InDoor` = '%d', ", cQuery, AccountData[playerid][pInDoor]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_InHouse` = '%d', ", cQuery, AccountData[playerid][pInHouse]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_InRusun` = '%d', ", cQuery, AccountData[playerid][pInRusun]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_InBiz` = '%d', ", cQuery, AccountData[playerid][pInBiz]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_InFamily` = '%d', ", cQuery, AccountData[playerid][pInFamily]);
    
    // Posisi menggunakan data murni dari variabel AccountData
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_PosX` = '%f', ", cQuery, AccountData[playerid][pPosX]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_PosY` = '%f', ", cQuery, AccountData[playerid][pPosY]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_PosZ` = '%f', ", cQuery, AccountData[playerid][pPosZ]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_PosA` = '%f', ", cQuery, AccountData[playerid][pPosA]);
    
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_IntID` = '%d', ", cQuery, AccountData[playerid][pInt]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_WID` = '%d', ", cQuery, AccountData[playerid][pWorld]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Health` = '%f', ", cQuery, AccountData[playerid][pHealth]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Armour` = '%f', ", cQuery, AccountData[playerid][pArmour]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Hunger` = '%d', ", cQuery, AccountData[playerid][pHunger]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Thirst` = '%d', ", cQuery, AccountData[playerid][pThirst]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Stress` = '%d', ", cQuery, AccountData[playerid][pStress]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_KnockDown` = '%d', ", cQuery, AccountData[playerid][pInjured]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_OnDuty` = '%d', ", cQuery, AccountData[playerid][pOnDuty]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Faction` = '%d', ", cQuery, AccountData[playerid][pFaction]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_FactionRank` = '%d', ", cQuery, AccountData[playerid][pFactionRank]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Family` = '%d', ", cQuery, AccountData[playerid][pFamily]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_FamilyRank` = '%d', ", cQuery, AccountData[playerid][pFamilyRank]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Jail` = '%d', ", cQuery, AccountData[playerid][pJail]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_JailTime` = '%d', ", cQuery, AccountData[playerid][pJailTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_JailReason` = '%s', ", cQuery, AccountData[playerid][pJailReason]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_JailBy` = '%s', ", cQuery, AccountData[playerid][pJailBy]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Arrest` = '%d', ", cQuery, AccountData[playerid][pArrest]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_ArrestTime` = '%d', ", cQuery, AccountData[playerid][pArrestTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_AskTime` = '%d', ", cQuery, AccountData[playerid][pAskTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Warn` = '%d', ", cQuery, AccountData[playerid][pWarn]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Job` = '%d', ", cQuery, AccountData[playerid][pJob]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_MowerTime` = '%d', ", cQuery, AccountData[playerid][pMowerTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Helmet` = '%d', ", cQuery, AccountData[playerid][pHelmet]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_TogPM` = '%d', ", cQuery, AccountData[playerid][pTogPM]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_TogGlobal` = '%d', ", cQuery, AccountData[playerid][pTogGlobal]);
    
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Head` = '%d', ", cQuery, AccountData[playerid][pHead]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Stomach` = '%d', ", cQuery, AccountData[playerid][pPerut]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_LeftArm` = '%d', ", cQuery, AccountData[playerid][pLHand]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_RightArm` = '%d', ", cQuery, AccountData[playerid][pRHand]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_LeftFoot` = '%d', ", cQuery, AccountData[playerid][pLFoot]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_RightFoot` = '%d', ", cQuery, AccountData[playerid][pRFoot]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_BackpackWeight` = '%.3f', ", cQuery, AccountData[playerid][pBeratItem]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_RusunStorage` = '%f', ", cQuery, AccountData[playerid][pRusunCapacity]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_GudangStorage` = '%f', ", cQuery, AccountData[playerid][pGudangCapacity]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_HasRusunID` = '%d', ", cQuery, AccountData[playerid][pOwnedRusun]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SimA` = '%d', ", cQuery, AccountData[playerid][pSimA]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SimB` = '%d', ", cQuery, AccountData[playerid][pSimB]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SimC` = '%d', ", cQuery, AccountData[playerid][pSimC]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SimATime` = '%d', ", cQuery, AccountData[playerid][pSimATime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SimBTime` = '%d', ", cQuery, AccountData[playerid][pSimBTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SimCTime` = '%d', ", cQuery, AccountData[playerid][pSimCTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_WeaponLic` = '%d', ", cQuery, AccountData[playerid][pGunLic]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_WeaponLicTime` = '%d', ", cQuery, AccountData[playerid][pGunLicTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_HuntingLic` = '%d', ", cQuery, AccountData[playerid][pHuntingLic]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_HuntingLicTime` = '%d', ", cQuery, AccountData[playerid][pHuntingLicTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Earphone` = '%d', ", cQuery, AccountData[playerid][pEarphone]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_VehPara` = '%d', ", cQuery, AccountData[playerid][pOwnPara]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Radio` = '%d', ", cQuery, AccountData[playerid][pRadio]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_KnockTime` = '%d', ", cQuery, AccountData[playerid][pInjuredTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Ktp` = '%d', ", cQuery, AccountData[playerid][Ktp]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_KtpTime` = '%d', ", cQuery, AccountData[playerid][pKtpTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_HasGudangID` = '%d', ", cQuery, AccountData[playerid][pHasGudangID]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_GudangRentTime` = '%d', ", cQuery, AccountData[playerid][pGudangRentTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_DownloadWhatsapp` = '%d', ", cQuery, AccountData[playerid][DownloadWhatsapp]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_DownloadGojek` = '%d', ", cQuery, AccountData[playerid][DownloadGojek]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_DownloadSpotify` = '%d', ", cQuery, AccountData[playerid][DownloadSpotify]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_DownloadTwitter` = '%d', ", cQuery, AccountData[playerid][DownloadTwitter]);
    
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Uniform` = '%d', ", cQuery, AccountData[playerid][pUniform]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_UsingUniform` = '%d', ", cQuery, AccountData[playerid][pUsingUniform]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_DutyPD` = '%d', ", cQuery, AccountData[playerid][pDutyPD]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_DutyPemerintah` = '%d', ", cQuery, AccountData[playerid][pDutyPemerintah]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_DutyEms` = '%d', ", cQuery, AccountData[playerid][pDutyEms]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_DutyBengkel` = '%d', ", cQuery, AccountData[playerid][pDutyBengkel]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_DutyPedagang` = '%d', ", cQuery, AccountData[playerid][pDutyPedagang]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_DutyTrans` = '%d', ", cQuery, AccountData[playerid][pDutyTrans]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Kompensasi` = '%d', ", cQuery, AccountData[playerid][pKompensasi]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_AdminHide` = '%d', ", cQuery, AccountData[playerid][pAdminHide]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_OwnedHouse` = '%d', ", cQuery, AccountData[playerid][pOwnedHouse]);

    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_BPJS` = '%d', ", cQuery, AccountData[playerid][pBPJS]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_BPJSTime` = '%d', ", cQuery, AccountData[playerid][pBPJSTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_BPJSLevel` = '%s', ", cQuery, AccountData[playerid][pBPJSLevel]);
    
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SKS` = '%d', ", cQuery, AccountData[playerid][pSKS]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SKSTime` = '%d', ", cQuery, AccountData[playerid][pSKSTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SKSNameDoc` = '%s', ", cQuery, AccountData[playerid][pSKSNameDoc]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SKSRankDoc` = '%s', ", cQuery, AccountData[playerid][pSKSRankDoc]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SKSReason` = '%s', ", cQuery, AccountData[playerid][pSKSReason]);

    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SKCK` = '%d', ", cQuery, AccountData[playerid][pSKCK]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SKCKTime` = '%d', ", cQuery, AccountData[playerid][pSKCKTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SKCKNamePol` = '%s', ", cQuery, AccountData[playerid][pSKCKNamePol]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SKCKRankPol` = '%s', ", cQuery, AccountData[playerid][pSKCKRankPol]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SKCKReason` = '%s', ", cQuery, AccountData[playerid][pSKCKReason]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_TogAutoEngine` = '%d', ", cQuery, AccountData[playerid][pTogAutoEngine]);
    
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_VipName` = '%s', ", cQuery, AccountData[playerid][pVipNameCustom]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Twitter` = '%d', ", cQuery, AccountData[playerid][Twitter]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_TwitterName` = '%s', ", cQuery, AccountData[playerid][TwitterName]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_TwitterPassword` = '%s', ", cQuery, AccountData[playerid][TwitterPassword]);

    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Spotify` = '%d', ", cQuery, AccountData[playerid][Spotify]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SpotifyName` = '%s', ", cQuery, AccountData[playerid][SpotifyName]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SpotifyPassword` = '%s', ", cQuery, AccountData[playerid][SpotifyPassword]);

    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_MaskID` = '%d', ", cQuery, AccountData[playerid][pMaskID]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_DelayTrashmaster` = '%d', ", cQuery, AccountData[playerid][pTrashmasterDelay]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_FriendHouse` = '%d', ", cQuery, AccountData[playerid][pFriendHouseID]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SweeperDelay` = '%d', ", cQuery, AccountData[playerid][pSweeperTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_DeliveryDelay` = '%d', ", cQuery, AccountData[playerid][pDeliveryTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_ForkliftDelay` = '%d', ", cQuery, AccountData[playerid][pForkliftTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_ClaimSP` = '%d', ", cQuery, AccountData[playerid][pClaimStarterpack]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_BenefitGirl` = '%d', ", cQuery, AccountData[playerid][pBenefitGirl]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Booster1` = '%d', ", cQuery, AccountData[playerid][pBenefitBooster1]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Booster2` = '%d', ", cQuery, AccountData[playerid][pBenefitBooster2]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Render` = '%f', ", cQuery, AccountData[playerid][pMapSettings]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_RenderValue` = '%d', ", cQuery, AccountData[playerid][pMapRender]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_Spy` = '%d', ", cQuery, AccountData[playerid][pTogSpy]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_OnlineTimer` = '%d', ", cQuery, AccountData[playerid][OnlineTimer]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_XmasGift` = '%d', ", cQuery, AccountData[playerid][pXmasTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SKWB` = '%d', ", cQuery, AccountData[playerid][pSKWB]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_SKWBTime` = '%d', ", cQuery, AccountData[playerid][pSKWBTime]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_CallRingtone` = '%s', ", cQuery, AccountData[playerid][phoneCallRingtone]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_NotifStyle` = '%d', ", cQuery, AccountData[playerid][pStyleNotif]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_AirplaneMode` = '%d', ", cQuery, AccountData[playerid][phoneAirplaneMode]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_HUDMode` = '%d', ", cQuery, AccountData[playerid][pHUDMode]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`workshop` = '%d', ", cQuery, AccountData[playerid][pWorkshop]);
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`workshoprank` = '%d', ", cQuery, AccountData[playerid][pWorkshopRank]);

    if(AccountData[playerid][playerClickSpawn])
    {
        new currentTime = gettime();
        mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_DCTime`= '%d', ", cQuery, currentTime + 3600);
    }
    mysql_format(g_SQL, cQuery, sizeof(cQuery), "%s`Char_LastLogin` = CURRENT_TIMESTAMP() WHERE `pID` = '%d'", cQuery, AccountData[playerid][pID]);
    mysql_tquery(g_SQL, cQuery);
    
    MySQL_SavePlayerToys(playerid);
    return 1;
}

/* Anti Cheat Stuffs */
Player_ToggleTelportAntiCheat(playerid, bool:toggle)
{
    if (!IsPlayerConnected(playerid))
    {
        return 0;
    }

    EnableAntiCheatForPlayer(playerid, 2, toggle);
    EnableAntiCheatForPlayer(playerid, 3, toggle);
    // EnableAntiCheatForPlayer(playerid, 6, toggle); // Code 6 reason.
    return 1;
}
Player_ToggleDisableAntiCheat(playerid, bool:toggle)
{
	EnableAntiCheatForPlayer(playerid, 18, toggle);
	EnableAntiCheatForPlayer(playerid, 27, toggle);
	EnableAntiCheatForPlayer(playerid, 26, toggle);
	EnableAntiCheatForPlayer(playerid, 29, toggle);
	EnableAntiCheatForPlayer(playerid, 32, toggle);
	EnableAntiCheatForPlayer(playerid, 35, toggle);
	EnableAntiCheatForPlayer(playerid, 38, toggle);
	EnableAntiCheatForPlayer(playerid, 39, toggle);
	EnableAntiCheatForPlayer(playerid, 41, toggle);
	EnableAntiCheatForPlayer(playerid, 42, toggle);
	EnableAntiCheatForPlayer(playerid, 44, toggle);
	EnableAntiCheatForPlayer(playerid, 48, toggle);
	EnableAntiCheatForPlayer(playerid, 49, toggle);
	EnableAntiCheatForPlayer(playerid, 50, toggle);
	EnableAntiCheatForPlayer(playerid, 5, toggle);
	EnableAntiCheatForPlayer(playerid, 6, toggle);
	EnableAntiCheatForPlayer(playerid, 9, toggle);
	return 1;
}

Player_ToggleAntiHealthHack(playerid, bool:toggle)
{
    EnableAntiCheatForPlayer(playerid, 11, toggle);
    EnableAntiCheatForPlayer(playerid, 12, toggle);
    EnableAntiCheatForPlayer(playerid, 13, toggle);
    return 1;
}

ShowKarungTD(playerid)
{
	PlayerTextDrawShow(playerid, VR_KARUNG[playerid][0]);
	return 1;
}

HideKarungTD(playerid)
{
	PlayerTextDrawHide(playerid, VR_KARUNG[playerid][0]);
	return 1;
}

KickEx(playerid, time = 1000)
{
	SetTimerEx("_KickPlayerDelayed", time, false, "i", playerid);
	return 1;
}

IsValidRoleplayName(const name[]) {
    if(!name[0] || strfind(name, "_") == -1)
        return 0;

    else for (new i = 0, len = strlen(name); i != len; i ++) {
    if((i == 0) && (name[i] < 'A' || name[i] > 'Z'))
            return 0;

        else if((i != 0 && i < len  && name[i] == '_') && (name[i + 1] < 'A' || name[i + 1] > 'Z'))
            return 0;

        else if((name[i] < 'A' || name[i] > 'Z') && (name[i] < 'a' || name[i] > 'z') && name[i] != '_' && name[i] != '.')
            return 0;
    }
    return 1;
}

IsValidName(const name[])
{
	new len = strlen(name);

	for(new ch = 0; ch != len; ch++)
	{
		switch(name[ch])
		{
			case 'A' .. 'Z', 'a' .. 'z', '0' .. '9', ']', '[', '(', ')', '_', '.': continue;
			default: return false;
		}
	}
	return true;
}

IsValidPassword(const name[])
{
	new len = strlen(name);

	for(new ch = 0; ch != len; ch++)
	{
		switch(name[ch])
		{
			case 'A' .. 'Z', 'a' .. 'z', '0' .. '9', ']', '[', '(', ')', '_', '.', '@', '#': continue;
			default: return false;
		}
	}
	return true;
}

IsValidFormatText(const name[])
{
    new len = strlen(name);

    for(new ch = 0; ch != len; ch++)
    {
        if(name[ch] == '\'')
        {
            return false; // Mengembalikan false jika tanda kutip (') ditemukan.
        }
    }
    
    return true; // Jika tidak ada tanda kutip (') ditemukan, maka mengembalikan true.
}

SendFamilyMessage(familyid, color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 12)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 12); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string
        #emit PUSH.C args

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player) if(AccountData[i][pFamily] == familyid /*&& !AccountData[i][pDisableFaction]*/) {
                SendClientMessage(i, color, string);
        }
        return 1;
    }
    foreach (new i : Player) if(AccountData[i][pFamily] == familyid /*&& !AccountData[i][pDisableFaction]*/) {
        SendClientMessage(i, color, str);
    }
    return 1;
}

FixText(text[])
{
    new len = strlen(text);
    if(len > 1)
    {
        for (new i = 0; i < len; i++)
        {
            if(text[i] == 92)
            {
                if(text[i+1] == 'n')
                {
                    text[i] = '\n';
                    for (new j = i+1; j < len; j++) text[j] = text[j+1], text[j+1] = 0;
                    continue;
                }
                if(text[i+1] == 't')
                {
                    text[i] = '\t';
                    for (new j = i+1; j < len-1; j++) text[j] = text[j+1], text[j+1] = 0;
                    continue;
                }

                if(text[i+1] == 92)
                {
                    text[i] = 92;
                    for (new j = i+1; j < len-1; j++) text[j] = text[j+1], text[j+1] = 0;
                }
            }
        }
    }
    return 1;
}


/*IsValidNameUCP(const name[])
{
	new len = strlen(name);

	for(new ch = 0; ch != len; ch++)
	{
		switch(name[ch])
		{
			case 'A' .. 'Z', 'a' .. 'z', '0' .. '9': continue;
			default: return false;
		}
	}
	return true;
}*/

//----------[ Anti-Cheat Native ]------
IsAUnstressArea(playerid)
{
	// LS Bahamas
	if(IsPlayerInRangeOfPoint(playerid, 100.00, 1211.6067, -7.8026, 1000.9219) && GetPlayerVirtualWorld(playerid) == 55 && GetPlayerInterior(playerid) == 2)
		return 1;

	// Pantai
	if(IsPlayerInDynamicArea(playerid, PantaiArea[playerid]) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
		return 1;
	
	// karnaval
	if(IsPlayerInRangeOfPoint(playerid, 50.0, 298.4348,-1896.5387,2.4481) && GetPlayerVirtualWorld(playerid) == 0 && GetPlayerInterior(playerid) == 0)
		return 1;
	
	// LV BAHAMAS
	if(IsPlayerInRangeOfPoint(playerid, 150.0, -2659.7283, 1409.9412, 910.1703) && GetPlayerVirtualWorld(playerid) == 100 && GetPlayerInterior(playerid) == 3)
		return 1;
	
	// BAHAMAS SF
	if(IsPlayerInRangeOfPoint(playerid, 150.0, 487.1639, -13.7924, 1000.6797) && GetPlayerInterior(playerid) == 17 && GetPlayerVirtualWorld(playerid) == 55)
		return 1;
	
	return 0;
}

IsPlayerInWater(playerid)
{
	new index = GetPlayerAnimationIndex(playerid);
	return ((index >= 1538 && index <= 1542) || index == 1544 || index == 1250);
}

stock GiveMoney(playerid, amount)
{
	AccountData[playerid][pMoney] += amount;
	GivePlayerMoney(playerid, amount);
	ShowItemBox(playerid, sprintf("Received %s", FormatMoney(amount)), "UANG", 1212);
}

stock TakeMoney(playerid, amount)
{
	AccountData[playerid][pMoney] -= amount;
	GivePlayerMoney(playerid, -amount);
	ShowItemBox(playerid, sprintf("Removed %s", FormatMoney(amount)), "UANG", 1212);
}

stock ResetPlayerMoneyEx(playerid)
{
	ShowItemBox(playerid, sprintf("Removed %s", FormatMoney(AccountData[playerid][pMoney])), "UANG", 1212);
	AccountData[playerid][pMoney] = 0;
	ResetPlayerMoney(playerid);
}

//Anti Health and Armour Hack
SetPlayerSkinEx(playerid, skinid)
{
	AccountData[playerid][pSkin] = skinid;
	SetPlayerSkin(playerid, skinid);
}

SetPlayerInteriorEx(playerid, interior)
{
	AccountData[playerid][pInt] = interior;
	SetPlayerInterior(playerid, interior);
}

SetPlayerVirtualWorldEx(playerid, wid)
{
	AccountData[playerid][pWorld] = wid;
	SetPlayerVirtualWorld(playerid, wid);
}

SetPlayerHealthEx(playerid, Float:heal)
{
	AccountData[playerid][pHealth] = heal;
	SetPlayerHealth(playerid, heal);
}

SetPlayerArmourEx(playerid, Float:armor)
{
	AccountData[playerid][pACTime] = gettime() + 5;
	AccountData[playerid][pArmorTime] = gettime() + 5;
	AccountData[playerid][pArmour] = armor;
	SetPlayerArmour(playerid, armor);
}

//Anti Weapon Hack
new const g_aWeaponSlots[] = {
    0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 10, 10, 10, 10, 10, 10, 8, 8, 8, 0, 0, 0, 2, 2, 2, 3, 3, 3, 4, 4, 5, 5, 4, 6, 6, 7, 7, 7, 7, 8, 12, 9, 9, 9, 11, 11, 11
};

ResetPlayerWeaponsEx(playerid)
{
    ResetPlayerWeapons(playerid);

    for (new i = 0; i < 13; i ++) {
        AccountData[playerid][pGuns][i] = 0;
        AccountData[playerid][pAmmo][i] = 0;
    }
    return 1;
}

ResetWeapons(playerid)
{
	ResetPlayerWeapons(playerid);

	forex(i, 13)
	{
		AccountData[playerid][pGuns][i] = 0;
		AccountData[playerid][pAmmo][i] = 0;
	}
	return 1;
}

ResetWeapon(playerid, weaponid)
{
	ResetPlayerWeapons(playerid);
	
    for (new i = 0; i < 13; i ++) {
        if(AccountData[playerid][pGuns][i] != weaponid) 
		{
            GivePlayerWeapon(playerid, AccountData[playerid][pGuns][i], AccountData[playerid][pAmmo][i]);
        }
        else 
		{
            AccountData[playerid][pGuns][i] = 0;
            AccountData[playerid][pAmmo][i] = 0;
        }
    }
	AccountData[playerid][pACTime] = gettime() + 2;
    return 1;
}

UpdateWeapons(playerid)
{
    for(new i = 0; i < 13; i ++)
	{
		if(AccountData[playerid][pGuns][i])
		{
			GetPlayerWeaponData(playerid, i, AccountData[playerid][pGuns][i], AccountData[playerid][pAmmo][i]);

			if(AccountData[playerid][pGuns][i] != 0 && !AccountData[playerid][pAmmo][i]) 
			{
					AccountData[playerid][pGuns][i] = 0;
			}
		}
	}
    return 1;
}

IsWeaponModel(model) {
    new const g_aWeaponModels[] = {
        0, 331, 333, 334, 335, 336, 337, 338, 339, 341, 321, 322, 323, 324,
        325, 326, 342, 343, 344, 0, 0, 0, 346, 347, 348, 349, 350, 351, 352,
        353, 355, 356, 372, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366,
        367, 368, 368, 371
    };
    for (new i = 0; i < sizeof(g_aWeaponModels); i ++) if(g_aWeaponModels[i] == model) {
        return 1;
    }
    return 0;
}

SetWeapons(playerid)
{
    ResetPlayerWeapons(playerid);

    for (new i = 0; i < 13; i ++) if(AccountData[playerid][pGuns][i] > 0 && AccountData[playerid][pAmmo][i] > 0) {
        GivePlayerWeapon(playerid, AccountData[playerid][pGuns][i], AccountData[playerid][pAmmo][i]);
		AccountData[playerid][pWeapon] = GetPlayerWeapon(playerid);
    }
    return 1;
}

GetPlayerWeaponEx(playerid)
{
    new weaponid = GetPlayerWeapon(playerid);

    if(1 <= weaponid <= 46 && AccountData[playerid][pGuns][g_aWeaponSlots[weaponid]] == weaponid)
        return weaponid;

    return 0;
}

GetPlayerAmmoEx(playerid)
{
	new weaponid = GetPlayerWeapon(playerid);
	new ammo = AccountData[playerid][pAmmo][g_aWeaponSlots[weaponid]];
	if(1 <= weaponid <= 46 && AccountData[playerid][pGuns][g_aWeaponSlots[weaponid]] == weaponid)
	{
		if(AccountData[playerid][pGuns][g_aWeaponSlots[weaponid]] != 0 && AccountData[playerid][pAmmo][g_aWeaponSlots[weaponid]] > 0)
		{
			return ammo;
		}
	}
	return 0;
}

GivePlayerWeaponEx(playerid, weaponid, ammo)
{
    if(weaponid < 0 || weaponid > 46)
        return 0;

    AccountData[playerid][pGuns][g_aWeaponSlots[weaponid]] = weaponid;
    AccountData[playerid][pAmmo][g_aWeaponSlots[weaponid]] += ammo;

    return GivePlayerWeapon(playerid, weaponid, ammo);
}

ReturnWeaponName(weaponid)
{
    new weapon[128];
    switch(weaponid)
    {
        case 0: weapon = "Fist / Unknown";
        case 18: weapon = "Molotov Cocktail";
        case 44: weapon = "Night Vision Goggles";
        case 45: weapon = "Thermal Goggles";
        case 54: weapon = "Fall";
		case 255: weapon = "Suicide";
		case 51: weapon = "Explode";
        default: GetWeaponName(weaponid, weapon, sizeof(weapon));
    }
    return weapon;
}

stock const AdminName[8][] = 
{
	"Bukan Admin",
	"The Trial",
	"Helper",
	"Admin I",
	"Admin II",
	"Admin III",
	"Pengurus",
	"Management"
};

GetStaffRank(playerid)
{
    new contnstr[128];
    format(contnstr, sizeof(contnstr), ""RED"%s", AdminName[AccountData[playerid][pAdmin]]);

    // Tambahan optional
    if(AccountData[playerid][pTheStars])
    {
        format(contnstr, sizeof(contnstr), "%s "GREEN"The Stars", contnstr); // gabungkan
    }

    if(AccountData[playerid][pAdminGirl])
    {
        format(contnstr, sizeof(contnstr), "%s "MAGENTA"Admin Girl", contnstr); // gabungkan
    }

    if(!strcmp(AccountData[playerid][pUCP], "whoiam", true))
    {
        format(contnstr, sizeof(contnstr), ""DEEPSKYBLUE1"Developer");
    }
    else if(!strcmp(AccountData[playerid][pUCP], "gil", true))
    {
        format(contnstr, sizeof(contnstr), ""DEEPSKYBLUE1"Owner Keren");
    }
    else if(!strcmp(AccountData[playerid][pUCP], "Nexuz", true))
    {
        format(contnstr, sizeof(contnstr), ""RED"Arsitek");
    }

    return contnstr;
}

SendStaffMessage(color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 8)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 8); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string

        #emit LOAD.S.pri 8
        #emit ADD.C 4
        #emit PUSH.pri

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player)
        {
			if(AccountData[i][pTogAC]) {
				if(AccountData[i][pAdmin] >= 1 || AccountData[i][pTheStars] >= 1) {
						SendClientMessageEx(i, color, "[AdmCmd] "RED"%s", string);
				}
			}
        }
        return 1;
    }
    foreach (new i : Player)
    {
		if(AccountData[i][pTogAC]) {
			if(AccountData[i][pAdmin] >= 1 || AccountData[i][pTheStars] >= 1) {
				SendClientMessageEx(i, color, "[AdmCmd] "RED"%s", string);
			}
		}
    }
    return 1;
}

SendAdminMessage(color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 8)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 8); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string

        #emit LOAD.S.pri 8
        #emit ADD.C 4
        #emit PUSH.pri

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player)
        {
			if(AccountData[i][pTogAC]) {
				if(AccountData[i][pAdmin] >= 1 || AccountData[i][pTheStars] >= 1/*&& !AccountData[i][pDisableAdmin]*/) {
					SendClientMessageEx(i, color, "%s", string);
				}
			}
        }
        return 1;
    }
    foreach (new i : Player)
    {
		if(AccountData[i][pTogAC]) {
			if(AccountData[i][pAdmin] >= 1 || AccountData[i][pTheStars] >= 1/*&& !AccountData[i][pDisableAdmin]*/) {
				SendClientMessageEx(i, color, "%s", string);
			}
		}
    }
    return 1;
}

/*SendAnticheat(color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 8)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 8); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string

        #emit LOAD.S.pri 8
        #emit ADD.C 4
        #emit PUSH.pri

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player)
        {
            if(AccountData[i][pAdmin] >= 1) {
                     SendClientMessageEx(i, color, "[ANTICHEAT] "YELLOW_E"%s", string);
            }
        }
        return 1;
    }
    foreach (new i : Player)
    {
        if(AccountData[i][pAdmin] >= 1) {
            SendClientMessageEx(i, color, "[ANTICHEAT] "YELLOW_E"%s", string);
        }
    }
    return 1;
}*/

AddAdminLog(const Char_Name[], const Char_UCP[], const Rank[], const Action[])
{
	new query[529];
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `adminlogs` (`Name`, `UCP`, `Rank`, `Activity`, `Time`) VALUE ('%s', '%s', '%s', '%s', CURRENT_TIMESTAMP())", Char_Name, Char_UCP, Rank, Action);
	return mysql_tquery(g_SQL, query);
}

AddTweetLog(const Char_Name[], const Char_UCP[], const Text[])
{
	new query[529];
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `tweetlogs` (`Name`, `UCP`, `Text`, `Time`) VALUE ('%s', '%s', '%s', CURRENT_TIMESTAMP())", Char_Name, Char_UCP, Text);
	return mysql_tquery(g_SQL, query);
}

AddFamiliesLog(const Char_Name[], const Char_UCP[], const Activity[], const Fams_Name[])
{
	new frmxt[320], cQuery[598];
	format(frmxt, sizeof(frmxt), "%s", Activity);

	mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `familieslogs` (`Name`, `UCP`, `Activity`, `Families`, `Time`) VALUES ('%s', '%s', '%s', '%s', CURRENT_TIMESTAMP())", Char_Name, Char_UCP, Activity, Fams_Name);
	return mysql_tquery(g_SQL, cQuery);
}

AddFMoneyLog(const Char_Name[], const Char_UCP[], value, const Faction[])
{
	new query[525];
	mysql_format(g_SQL, query, sizeof(query), "INSERT INTO `factionlogs` (`Name`, `UCP`, `Value`, `Faction`, `Time`) VALUE ('%s', '%s', '%d', '%s', CURRENT_TIMESTAMP())", Char_Name, Char_UCP, value, Faction);
	return mysql_tquery(g_SQL, query);
}

AddPMoneyLog(const Char_Name[], const Char_UCP[], const Activity[], value)
{
	new frmxt[320], cQuery[598];
	format(frmxt, sizeof(frmxt), "%s", Activity);
	
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "INSERT INTO `playerlogs` (`Name`, `UCP`, `Activity`, `Value`, `Time`) VALUES ('%s', '%s', '%s', %d, CURRENT_TIMESTAMP())", Char_Name, Char_UCP, frmxt, value);
	return mysql_tquery(g_SQL, cQuery);
}

GetPlayerVipName(playerid)
{
	new name[128];
	if(AccountData[playerid][pVip] == 1)
	{
		name = ""YELLOW"Rangers Kuning";
	}
	else if(AccountData[playerid][pVip] == 2)
	{
		name = ""GREEN"Rangers Hijau";
	}
	else if(AccountData[playerid][pVip] == 3)
	{
		name = ""RED"Rangers Merah";
	}
	else 
	{
		name = "Tidak VIP";
	}
	return name;
}

//----------[ Faction Native ]----------
GetFactRank(faction, factionrank)
{
	new rank[64];
	switch(faction)
	{
		case 1: // Polisi
		{
			if(factionrank == 1)
			{
				rank = "BRIPDA";
			}
			if(factionrank == 2)
			{
				rank = "BRIPTU";
			}
			if(factionrank == 3)
			{
				rank = "BRIPKA";
			}
			if(factionrank == 4)
			{
				rank = "AIPDA";
			}
			if(factionrank == 5)
			{
				rank = "AIPTU";
			}
			if(factionrank == 6)
			{
				rank = "IPDA";
			}
			if(factionrank == 7)
			{
				rank = "IPTU";
			}
			if(factionrank == 8)
			{
				rank = "AKP";
			}
			if(factionrank == 9)
			{
				rank = "KOMPOL";
			}
			if(factionrank == 10)
			{
				rank = "AKPB";
			}
			if(factionrank == 11)
			{
				rank = "KOMBES";
			}
			if(factionrank == 12)
			{
				rank = "BRIGJEN";
			}
			if(factionrank == 13)
			{
				rank = "IRJEN";
			}
			if(factionrank == 14)
			{
				rank = "KOMJEN";
			}
			if(factionrank == 15)
			{
				rank = "JENDPOL";
			}
		}
		case 2: //pemerintah
		{
			if(factionrank == 1)
			{
				rank = "Magang";
			}
			if(factionrank == 2)
			{
				rank = "Staff";
			}
			if(factionrank == 3)
			{
				rank = "Staff Senior";
			}
			if(factionrank == 4)
			{
				rank = "Wakil Divisi";
			}
			if(factionrank == 5)
			{
				rank = "Kepala Divisi";
			}
			if(factionrank == 6)
			{
				rank = "Sekda";
			}
			if(factionrank == 7)
			{
				rank = "Wakil Gubernur";
			}
			if(factionrank == 8)
			{
				rank = "Gubernur";
			}
		}
		case 3: 
		{
			if(factionrank == 1)
			{
				rank = "Training";
			}	
			if(factionrank == 2)
			{
				rank = "Perawat";
			}
			if(factionrank == 3)
			{
				rank = "Dokter Umum";
			}
			if(factionrank == 4)
			{
				rank = "Dokter Spesialis";
			}
			if(factionrank == 5)
			{
				rank = "Komisi Disiplin";
			}
			if(factionrank == 6)
			{
				rank = "Komisi Umum";
			}
			if(factionrank == 7)
			{
				rank = "SEKBEN";
			}
			if(factionrank == 8)
			{
				rank = "Direktur SDM";
			}
			if(factionrank == 9)
			{
				rank = "Direktur Keilmuan";
			}
			if(factionrank == 10)
			{
				rank = "Wadir Utama";
			}
			if(factionrank == 11)
			{
				rank = "Direktur Utama";
			}
		}
		case 4:
		{
			if(factionrank == 1)
			{
				rank = "Magang";
			}
			if(factionrank == 2)
			{
				rank = "Junior";
			}
			if(factionrank == 3)
			{
				rank = "Senior";
			}
			if(factionrank == 4)
			{
				rank = "Kepala Transport";
			}
			if(factionrank == 5)
			{
				rank = "Trans CEO";
			}
		}
		case 5:
		{
			if(factionrank == 1)
			{
				rank = "Magang";
			}
			if(factionrank == 2)
			{
				rank = "Junior";
			}
			if(factionrank == 3)
			{
				rank = "Senior";
			}
			if(factionrank == 4)
			{
				rank = "Manager Bengkel";
			}
			if(factionrank == 5)
			{
				rank = "Wakil Bengkel";
			}
			if(factionrank == 6)
			{
				rank = "Kepala Bengkel";
			}
		}
		case 6:
		{
			if(factionrank == 1)
			{
				rank = "Magang";
			}
			if(factionrank == 2)
			{
				rank = "Junior";
			}
			if(factionrank == 3)
			{
				rank = "Senior";
			}
			if(factionrank == 4)
			{
				rank = "Manager";
			}
			if(factionrank == 5)
			{
				rank = "Wakil CEO";
			}
			if(factionrank == 6)
			{
				rank = "CEO";
			}
		}
		case 7:
		{
			if(factionrank == 1)
			{
				rank = "JENDPOL";
			}
			if(factionrank == 2)
			{
				rank = "Letnan JENDPOL";
			}
			if(factionrank == 3)
			{
				rank = "Mayor JENDPOL";
			}
			if(factionrank == 4)
			{
				rank = "Brigadir JENDPOL";
			}
			if(factionrank == 5)
			{
				rank = "Kolonel";
			}
		}

		default:
		{
			rank = "N/A";
		}
	}
	return rank;
}

GetFactionRank(playerid)
{
	new rank[48];
	if(AccountData[playerid][pFaction] == FACTION_POLISI)
	{
		if(AccountData[playerid][pFactionRank] == 1)
		{
			rank = "BRIPDA";
		}
		if(AccountData[playerid][pFactionRank] == 2)
		{
			rank = "BRIPTU";
		}
		if(AccountData[playerid][pFactionRank] == 3)
		{
			rank = "BRIPKA";
		}
		if(AccountData[playerid][pFactionRank] == 4)
		{
			rank = "AIPDA";
		}
		if(AccountData[playerid][pFactionRank] == 5)
		{
			rank = "AIPTU";
		}
		if(AccountData[playerid][pFactionRank] == 6)
		{
			rank = "IPDA";
		}
		if(AccountData[playerid][pFactionRank] == 7)
		{
			rank = "IPTU";
		}
		if(AccountData[playerid][pFactionRank] == 8)
		{
			rank = "AKP";
		}
		if(AccountData[playerid][pFactionRank] == 9)
		{
			rank = "KOMPOL";
		}
		if(AccountData[playerid][pFactionRank] == 10)
		{
			rank = "AKPB";
		}
		if(AccountData[playerid][pFactionRank] == 11)
		{
			rank = "KOMBES";
		}
		if(AccountData[playerid][pFactionRank] == 12)
		{
			rank = "BRIGJEN";
		}
		if(AccountData[playerid][pFactionRank] == 13)
		{
			rank = "IRJEN";
		}
		if(AccountData[playerid][pFactionRank] == 14)
		{
			rank = "KOMJEN";
		}
		if(AccountData[playerid][pFactionRank] == 15)
		{
			rank = "JENDPOL";
		}
	}

	if(AccountData[playerid][pFaction] == FACTION_PEMERINTAH)
	{
		if(AccountData[playerid][pFactionRank] == 1)
		{
			rank = "Magang";
		}
		if(AccountData[playerid][pFactionRank] == 2)
		{
			rank = "Staff";
		}
		if(AccountData[playerid][pFactionRank] == 3)
		{
			rank = "Staff Senior";
		}
		if(AccountData[playerid][pFactionRank] == 4)
		{
			rank = "Wakil Divisi";
		}
		if(AccountData[playerid][pFactionRank] == 5)
		{
			rank = "Kepala Divisi";
		}
		if(AccountData[playerid][pFactionRank] == 6)
		{
			rank = "Sekda";
		}
		if(AccountData[playerid][pFactionRank] == 7)
		{
			rank = "Wakil Gubernur";
		}
		if(AccountData[playerid][pFactionRank] == 8)
		{
			rank = "Gubernur";
		}
	}

	if(AccountData[playerid][pFaction] == FACTION_BENGKEL)
	{
		if(AccountData[playerid][pFactionRank] == 1)
		{
			rank = "Magang";
		}
		if(AccountData[playerid][pFactionRank] == 2)
		{
			rank = "Junior";
		}
		if(AccountData[playerid][pFactionRank] == 3)
		{
			rank = "Senior";
		}
		if(AccountData[playerid][pFactionRank] == 4)
		{
			rank = "Manager Bengkel";
		}
		if(AccountData[playerid][pFactionRank] == 5)
		{
			rank = "Wakil Bengkel";
		}
		if(AccountData[playerid][pFactionRank] == 6)
		{
			rank = "Kepala Bengkel";
		}
	}

	if(AccountData[playerid][pFaction] == FACTION_TRANS)
	{
		if(AccountData[playerid][pFactionRank] == 1)
		{
			rank = "Magang";
		}
		if(AccountData[playerid][pFactionRank] == 2)
		{
			rank = "Junior";
		}
		if(AccountData[playerid][pFactionRank] == 3)
		{
			rank = "Senior";
		}
		if(AccountData[playerid][pFactionRank] == 4)
		{
			rank = "Kepala Transport";
		}
		if(AccountData[playerid][pFactionRank] == 5)
		{
			rank = "Trans CEO";
		}
	}

	if(AccountData[playerid][pFaction] == FACTION_GOJEK)
	{
		if(AccountData[playerid][pFactionRank] == 1)
		{
			rank = "JENDPOL";
		}
		if(AccountData[playerid][pFactionRank] == 2)
		{
			rank = "Letnan JENDPOL";
		}
		if(AccountData[playerid][pFactionRank] == 3)
		{
			rank = "Mayor JENDPOL";
		}
		if(AccountData[playerid][pFactionRank] == 4)
		{
			rank = "Brigadir JENDPOL";
		}
		if(AccountData[playerid][pFactionRank] == 5)
		{
			rank = "Kolonel";
		}
	}

	if(AccountData[playerid][pFaction] == FACTION_EMS)
	{
		if(AccountData[playerid][pFactionRank] == 1)
		{
			rank = "Training";
		}	
		if(AccountData[playerid][pFactionRank] == 2)
		{
			rank = "Perawat";
		}
		if(AccountData[playerid][pFactionRank] == 3)
		{
			rank = "Dokter Umum";
		}
		if(AccountData[playerid][pFactionRank] == 4)
		{
			rank = "Dokter Spesialis";
		}
		if(AccountData[playerid][pFactionRank] == 5)
		{
			rank = "Komisi Disiplin";
		}
		if(AccountData[playerid][pFactionRank] == 6)
		{
			rank = "Komisi Umum";
		}
		if(AccountData[playerid][pFactionRank] == 7)
		{
			rank = "SEKBEN";
		}
		if(AccountData[playerid][pFactionRank] == 8)
		{
			rank = "Direktur SDM";
		}
		if(AccountData[playerid][pFactionRank] == 9)
		{
			rank = "Direktur Keilmuan";
		}
		if(AccountData[playerid][pFactionRank] == 10)
		{
			rank = "Wadir Utama";
		}
		if(AccountData[playerid][pFactionRank] == 11)
		{
			rank = "Direktur Utama";
		}
	}

	if(AccountData[playerid][pFaction] == FACTION_PEDAGANG)
	{
		if(AccountData[playerid][pFactionRank] == 1)
		{
			rank = "Magang";
		}
		if(AccountData[playerid][pFactionRank] == 2)
		{
			rank = "Junior";
		}
		if(AccountData[playerid][pFactionRank] == 3)
		{
			rank = "Senior";
		}
		if(AccountData[playerid][pFactionRank] == 4)
		{
			rank = "Manager";
		}
		if(AccountData[playerid][pFactionRank] == 5)
		{
			rank = "Wakil CEO";
		}
		if(AccountData[playerid][pFactionRank] == 6)
		{
			rank = "CEO";
		}
	}

	if(AccountData[playerid][pFactionRank] == 0)
	{
		rank = "Warga";
	}
	return rank;
}

SetPlayerPosArrest(playerid, cellid)
{
	if(cellid == 1)
	{
		SetPlayerPositionEx(playerid, 325.9671, 1833.7511, 7.8074, 88.7423, 2000);
	}
	ResetNameTag(playerid, true);
	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 0);
	ShowPlayerDialog(playerid, -1, DIALOG_STYLE_LIST, "Close", "Close", "Close", "Close");
	SetPlayerWantedLevel(playerid, 0);
	PlayerPlaySound(playerid, 1186, 0, 0, 0);
    ResetPlayerWeaponsEx(playerid);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	AccountData[playerid][pCuffed] = 0;
	AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInHouse] = -1;
	AccountData[playerid][pInRusun] = -1;
	AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInFamily] = -1;
}

SpawnPlayerInJail(playerid)
{
	new rand = random(sizeof(arrAdminJail));

	ResetNameTag(playerid, true);
	// SetPlayerPositionEx(playerid, arrAdminJail[rand][0], arrAdminJail[rand][1], arrAdminJail[rand][2], arrAdminJail[rand][3], 2000);
	SetPlayerPos(playerid, arrAdminJail[rand][0], arrAdminJail[rand][1], arrAdminJail[rand][2]);
	SetPlayerFacingAngle(playerid, arrAdminJail[rand][3]);
	SetPlayerInteriorEx(playerid, 10);
	SetPlayerVirtualWorldEx(playerid, 88);
	ClearAnimations(playerid, 1);
	return 1;
}

SetPlayerArrest(playerid, cellid)
{
	if(cellid == 1)
	{
		SetPlayerPositionEx(playerid, 325.9671, 1833.7511, 7.8074, 88.7423, 2000);
	}
	ResetNameTag(playerid, true);
	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerInterior(playerid, 0);
	ShowPlayerDialog(playerid, -1, DIALOG_STYLE_LIST, "Close", "Close", "Close", "Close");
	SetPlayerWantedLevel(playerid, 0);
	PlayerPlaySound(playerid, 1186, 0, 0, 0);
    ResetPlayerWeaponsEx(playerid);
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
	AccountData[playerid][pCuffed] = 0;
	AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInHouse] = -1;
	AccountData[playerid][pInRusun] = -1;
	AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInFamily] = -1;
}

GetFamilyRank(playerid)
{
	new rank[24];
	if(AccountData[playerid][pFamily] != -1)
	{
		if(AccountData[playerid][pFamilyRank] == 1) 
		{
			rank = "Relasi";
		}
		else if(AccountData[playerid][pFamilyRank] == 2) 
		{
			rank = "Outsider";
		}
		else if(AccountData[playerid][pFamilyRank] == 3) 
		{
			rank = "Insider";
		}
		else if(AccountData[playerid][pFamilyRank] == 4) 
		{
			rank = "Tangan Kanan";
		}
		else if(AccountData[playerid][pFamilyRank] == 5) 
		{
			rank = "Wakil Ketua";
		}
		else if(AccountData[playerid][pFamilyRank] == 6) 
		{
			rank = "Ketua";
		}
		else
		{
			rank = "N/A";
		}
	}
	else
	{
		rank = "N/A";
	}
	return rank;
}

// SendFamilyMessage(familyid, color, const str[], {Float,_}:...)
// {
//     static
//         args,
//         start,
//         end,
//         string[144]
//     ;
//     #emit LOAD.S.pri 8
//     #emit STOR.pri args

//     if(args > 12)
//     {
//         #emit ADDR.pri str
//         #emit STOR.pri start

//         for (end = start + (args - 12); end > start; end -= 4)
//         {
//             #emit LREF.pri end
//             #emit PUSH.pri
//         }
//         #emit PUSH.S str
//         #emit PUSH.C 144
//         #emit PUSH.C string
//         #emit PUSH.C args

//         #emit SYSREQ.C format
//         #emit LCTRL 5
//         #emit SCTRL 4

//         foreach (new i : Player) if(AccountData[i][pFamily] == familyid /*&& !AccountData[i][pDisableFaction]*/) {
//                      SendClientMessage(i, color, string);
//         }
//         return 1;
//     }
//     foreach (new i : Player) if(AccountData[i][pFamily] == familyid /*&& !AccountData[i][pDisableFaction]*/) {
//         SendClientMessage(i, color, str);
//     }
//     return 1;
// }

//----------[ Job Native ]----------
static const JOBName[14][] = {
	"Pengangguran",
	"Supir Bus",
	"Penambang",
	"Tukang Kayu",
	"Tukang Ayam",
	"Tukang Jahit",
	"Tukang Minyak",
	"Nelayan",
	"Pemerah Susu",
	"Petani",
	"Kargo",
	"Recycler",
	"Tukang Sampah",
	"Driver Mixer"
};

new const PlayerLevelName[][] = {
	"Unknows",
	""WHITE"Warga Baru",
	""WHITE"Starty I",
	""WHITE"Starty II",
	""GRAY"Middly I",
	""GRAY"Middly II",
	""BLUE"Nowe I",
	""BLUE"Nowe II",
	""DEEPSKYBLUE1"Bexley I",
	""DEEPSKYBLUE1"Bexley II",
	""ORANGE"Alanis I",
	""ORANGE"Alanis II",
	""LIGHTGREEN"Alezonyth I",
	""LIGHTGREEN"Alezonyth I",
	""CHARTREUSE1"Axel I",
	""CHARTREUSE1"Axel II",
	""SPRINGGREEN1"Boomer I",
	""SPRINGGREEN1"Boomer II",
	""AQUAMARINE"Bleed I",
	""AQUAMARINE"Bleed II",
	""CADETBLUE1"Bethany I",
	""CADETBLUE1"Bethany II",
	""SKYBLUE1"Blake I",
	""SKYBLUE1"Blake II",
	""DEEPPINK"Croalla I",
	""DEEPPINK"Croalla II",
	""SLATEGRAY"Camwyn I",
	""SLATEGRAY"Camwyn II",
	""RED1"Cobey I",
	""RED1"Cobey II",
	""MISTYROSE"Chermix I",
	""MISTYROSE"Chermix II",
	""YELLOW"Chantelle I",
	""YELLOW"Chantelle II",
	""DEEPSKYBLUE1"Dizzy I",
	""DEEPSKYBLUE1"Dizzy II",
	""BISQUE"Dazzle I",
	""BISQUE"Dazzle II",
	""LEMONCHIFFON"Dimitri I",
	""LEMONCHIFFON"Dimitri II",
	""LIGHTCYAN"Deanix I",
	""LIGHTCYAN"Deanix II",
	""YELLOWGREEN"Dixie I",
	""YELLOWGREEN"Dixie II",
	""TAN1"Demora I",
	""TAN1"Demora II",
	""CHOCOLATE1"Dwazian I",
	""CHOCOLATE1"Dwazian II",
	""MAROON1"Dwazian III",
	""MAROON1"Legendary I",
	""PLUM1"Legendary",
	""PLUM1"Ezambix I",
	""MEDIUMORCHID"Ezambix II",
	""MEDIUMORCHID"Emerald I",
	""PURPLE1"Emerald II",
	""PURPLE1"Elektra I",
	""PURPLE2"Elektra II",
	""PURPLE2"Emeryn I",
	""THISTLE1"Emeryn II",
	""THISTLE1"Enigma I",
	""AQUAMARINE4"Enigma II",
	""AQUAMARINE4"Elmeryx I",
	""YELLOW"Elmeryx II",
	""YELLOW"Etharnia I",
	""LIGHTGOLDENROD"Etharnia II",
	""LIGHTGOLDENROD"Fury I",
	""GOLD"Fury II",
	""GOLD"Freschia I",
	""CYAN1"Freschia II",
	""CYAN1"Fisheye I",
	""RED3"Fisheye",
	""RED3"Gloria I",
	""YELLOW"Gloria II",
	""YELLOW"Geneva I",
	""YELLOW"Geneva II",
	""ORANGE2"Hazel I",
	""ORANGE2"Hazel II",
	""LIGHTBLUE"Hope I",
	""LIGHTBLUE"Hope II",
	""LIGHTPINK"Heather I",
	""LIGHTPINK"Heather II",
	""PURPLE3"Infinity I",
	""PURPLE3"Infinity II",
	""ORANGE"Izzelia I",
	""ORANGE"Izzelia II",
	""LIGHTPINK2"Hearth I",
	""LIGHTPINK2"Hearth II",
	""YELLOW"Kyanite I",
	""YELLOW"Kyanite II",
	""GRAY21"Iluminaty I",
	""GRAY21"Iluminaty",
	""YELLOW"King I",
	""YELLOW"King II",
	""LIGHTGREEN"Bonanza I",
	""LIGHTGREEN"Bonanza II",
	""PURPLE"Kraken I",
	""PURPLE"Kraken II",
	""YELLOW"Naomi I",
	""YELLOW"Naomi II",
	""RED"Pragmatic I",
	""LIGHTSALMON"Pragmatic II",
	""LIGHTSALMON"Pragmatic III",
	""RED"The Old Player I",
	""LIGHTSALMON"The Old Player II",
	""LIGHTSALMON"The Old Player III"
};

GetPlayerJobName(playerid)
{
	new fctnr[128];

	format(fctnr, sizeof(fctnr), JOBName[AccountData[playerid][pJob]]);
	return fctnr;
}

GetPlayerLevelName(playerid)
{
	new contnstr[178];

	format(contnstr, sizeof(contnstr), PlayerLevelName[AccountData[playerid][pLevel]]);
	return contnstr;
}

/*GetPlayerLevelName(playerid)
{
	new name[566];
	if(AccountData[playerid][pLev,,el] == 1)
	{
		name = ""WHITE"Warga Baru";
	}
	else if(AccountData[playerid][pLevel] == 2)
	{
		name = ""WHITE"Starty I";
	}
	else if(AccountData[playerid][pLevel] == 3)
	{
		name = ""WHITE"Starty II";
	}
	else if(AccountData[playerid][pLevel] == 4)
	{
		name = ""GRAY"Middly I";
	}
	else if(AccountData[playerid][pLevel] == 5)
	{
		name = ""GRAY"Middly II";
	}
	else if(AccountData[playerid][pLevel] == 6)
	{
		name = ""BLUE"Nowe I";
	}
	else if(AccountData[playerid][pLevel] == 7)
	{
		name = ""BLUE"Nowe II";
	}
	else if(AccountData[playerid][pLevel] == 8)
	{
		name = ""DEEPSKYBLUE1"Bexley I";
	}
	else if(AccountData[playerid][pLevel] == 9)
	{
		name = ""DEEPSKYBLUE1"Bexley II";
	}
	else if(AccountData[playerid][pLevel] == 10)
	{
		name = ""ORANGE"Alanis I";
	}
	else if(AccountData[playerid][pLevel] == 11)
	{
		name = ""ORANGE"Alanis II";
	}
	else if(AccountData[playerid][pLevel] == 12)
	{
		name = ""LIGHTGREEN"Alezonyth I";
	}
	else if(AccountData[playerid][pLevel] == 13)

	{
		name = ""LIGHTGREEN"Alezonyth I";
	}
	else if(AccountData[playerid][pLevel] == 14)
	{
		name = ""CHARTREUSE1"Axel I";
	}
	else if(AccountData[playerid][pLevel] == 15)
	{
		name = ""CHARTREUSE1"Axel II";
	}
	else if(AccountData[playerid][pLevel] == 16)
	{
		name = ""SPRINGGREEN1"Boomer I";
	}
	else if(AccountData[playerid][pLevel] == 17)
	{
		name = ""SPRINGGREEN1"Boomer II";
	}
	else if(AccountData[playerid][pLevel] == 18)
	{
		name = ""AQUAMARINE"Bleed I";
	}
	else if(AccountData[playerid][pLevel] == 19)
	{
		name = ""AQUAMARINE"Bleed II";
	}
	else if(AccountData[playerid][pLevel] == 20)
	{
		name = ""CADETBLUE1"Bethany I";
	}
	else if(AccountData[playerid][pLevel] == 21)
	{
		name = ""CADETBLUE1"Bethany II";
	}
	else if(AccountData[playerid][pLevel] == 22)
	{
		name = ""SKYBLUE1"Blake I";
	}
	else if(AccountData[playerid][pLevel] == 23)
	{
		name = ""SKYBLUE1"Blake II";
	}
	else if(AccountData[playerid][pLevel] == 24)
	{
		name = ""DEEPPINK"Croalla I";
	}
	else if(AccountData[playerid][pLevel] == 25)
	{
		name = ""DEEPPINK"Croalla II";
	}
	else if(AccountData[playerid][pLevel] == 26)
	{
		name = ""SLATEGRAY"Camwyn I";
	}
	else if(AccountData[playerid][pLevel] == 27)
	{
		name = ""SLATEGRAY"Camwyn II";
	}
	else if(AccountData[playerid][pLevel] == 28)
	{
		name = ""RED1"Cobey I";
	}
	else if(AccountData[playerid][pLevel] == 29)
	{
		name = ""RED1"Cobey II";
	}
	else if(AccountData[playerid][pLevel] == 30)
	{
		name = ""MISTYROSE"Chermix I";
	}
	else if(AccountData[playerid][pLevel] == 31)
	{
		name = ""MISTYROSE"Chermix II";
	}
	else if(AccountData[playerid][pLevel] == 32)
	{
		name = ""YELLOW"Chantelle I";
	}
	else if(AccountData[playerid][pLevel] == 33)
	{
		name = ""YELLOW"Chantelle II";
	}
	else if(AccountData[playerid][pLevel] == 34)
	{
		name = ""DEEPSKYBLUE1"Dizzy I";
	}
	else if(AccountData[playerid][pLevel] == 35)
	{
		name = ""DEEPSKYBLUE1"Dizzy II";
	}
	else if(AccountData[playerid][pLevel] == 36)
	{
		name = ""BISQUE"Dazzle I";
	}
	else if(AccountData[playerid][pLevel] == 37)
	{
		name = ""BISQUE"Dazzle II";
	}
	else if(AccountData[playerid][pLevel] == 38)
	{
		name = ""LEMONCHIFFON"Dimitri I";
	}
	else if(AccountData[playerid][pLevel] == 39)
	{
		name = ""LEMONCHIFFON"Dimitri II";
	}
	else if(AccountData[playerid][pLevel] == 40)
	{
		name = ""LIGHTCYAN"Deanix I";
	}
	else if(AccountData[playerid][pLevel] == 41)
	{
		name = ""LIGHTCYAN"Deanix II";
	}
	else if(AccountData[playerid][pLevel] == 42)
	{
		name = ""YELLOWGREEN"Dixie I";
	}
	else if(AccountData[playerid][pLevel] == 43)
	{
		name = ""YELLOWGREEN"Dixie II";
	}
	else if(AccountData[playerid][pLevel] == 44)
	{
		name = ""TAN1"Demora I";
	}
	else if(AccountData[playerid][pLevel] == 45)
	{
		name = ""TAN1"Demora II";
	}
	else if(AccountData[playerid][pLevel] == 46)
	{
		name = ""CHOCOLATE1"Dwazian I";
	}
	else if(AccountData[playerid][pLevel] == 47)
	{
		name = ""CHOCOLATE1"Dwazian II";
	}
	else if(AccountData[playerid][pLevel] == 48)
	{
		name = ""MAROON1"Dwazian III";
	}
	else if(AccountData[playerid][pLevel] == 49)
	{
		name = ""MAROON1"Legendary I";
	}
	else if(AccountData[playerid][pLevel] == 50)
	{
		name = ""PLUM1"Legendary";
	}
	else if(AccountData[playerid][pLevel] == 51)
	{
		name = ""PLUM1"Ezambix I";
	}
	else if(AccountData[playerid][pLevel] == 52)
	{
		name = ""MEDIUMORCHID"Ezambix II";
	}
	else if(AccountData[playerid][pLevel] == 53)
	{
		name = ""MEDIUMORCHID"Emerald I";
	}
	else if(AccountData[playerid][pLevel] == 54)
	{
		name = ""PURPLE1"Emerald II";
	}
	else if(AccountData[playerid][pLevel] == 55)
	{
		name = ""PURPLE1"Elektra I";
	}
	else if(AccountData[playerid][pLevel] == 56)
	{
		name = ""PURPLE2"Elektra II";
	}
	else if(AccountData[playerid][pLevel] == 57)
	{
		name = ""PURPLE2"Emeryn I";
	}
	else if(AccountData[playerid][pLevel] == 58)
	{
		name = ""THISTLE1"Emeryn II";
	}
	else if(AccountData[playerid][pLevel] == 59)
	{
		name = ""THISTLE1"Enigma I";
	}
	else if(AccountData[playerid][pLevel] == 60)
	{
		name = ""AQUAMARINE4"Enigma II";
	}
	else if(AccountData[playerid][pLevel] == 61)
	{
		name = ""AQUAMARINE4"Elmeryx I";
	}
	else if(AccountData[playerid][pLevel] == 62)
	{
		name = ""YELLOW"Elmeryx II";
	}
	else if(AccountData[playerid][pLevel] == 63)
	{
		name = ""YELLOW"Etharnia I";
	}
	else if(AccountData[playerid][pLevel] == 64)
	{
		name = ""LIGHTGOLDENROD"Etharnia II";
	}
	else if(AccountData[playerid][pLevel] == 65)
	{
		name = ""LIGHTGOLDENROD"Fury I";
	}
	else if(AccountData[playerid][pLevel] == 66)
	{
		name = ""GOLD"Fury II";
	}
	else if(AccountData[playerid][pLevel] == 67)
	{
		name = ""GOLD"Freschia I";
	}
	else if(AccountData[playerid][pLevel] == 68)
	{
		name = ""CYAN1"Freschia II";
	}
	else if(AccountData[playerid][pLevel] == 69)
	{
		name = ""CYAN1"Fisheye I";
	}
	else if(AccountData[playerid][pLevel] == 70)
	{
		name = ""RED3"Fisheye";
	}
	else if(AccountData[playerid][pLevel] == 71)
	{
		name = ""RED3"Gloria I";
	}
	else if(AccountData[playerid][pLevel] == 72)
	{
		name = ""YELLOW"Gloria II";
	}
	else if(AccountData[playerid][pLevel] == 73)
	{
		name = ""YELLOW"Geneva I";
	}
	else if(AccountData[playerid][pLevel] == 74)
	{
		name = ""YELLOW"Geneva II";
	}
	else if(AccountData[playerid][pLevel] == 75)
	{
		name = ""ORANGE2"Hazel I";
	}
	else if(AccountData[playerid][pLevel] == 76)
	{
		name = ""ORANGE2"Hazel II";
	}
	else if(AccountData[playerid][pLevel] == 77)
	{
		name = ""LIGHTBLUE"Hope I";
	}
	else if(AccountData[playerid][pLevel] == 78)
	{
		name = ""LIGHTBLUE"Hope II";
	}
	else if(AccountData[playerid][pLevel] == 79)
	{
		name = ""LIGHTPINK"Heather I";
	}
	else if(AccountData[playerid][pLevel] == 80)
	{
		name = ""LIGHTPINK"Heather II";
	}
	else if(AccountData[playerid][pLevel] == 81)
	{
		name = ""PURPLE3"Infinity I";
	}
	else if(AccountData[playerid][pLevel] == 82)
	{
		name = ""PURPLE3"Infinity II";
	}
	else if(AccountData[playerid][pLevel] == 83)
	{
		name = ""ORANGE"Izzelia I";
	}
	else if(AccountData[playerid][pLevel] == 84)
	{
		name = ""ORANGE"Izzelia II";
	}
	else if(AccountData[playerid][pLevel] == 85)
	{
		name = ""LIGHTPINK2"Hearth I";
	}
	else if(AccountData[playerid][pLevel] == 86)
	{
		name = ""LIGHTPINK2"Hearth II";
	}
	else if(AccountData[playerid][pLevel] == 87)
	{
		name = ""YELLOW"Kyanite I";
	}
	else if(AccountData[playerid][pLevel] == 88)
	{
		name = ""YELLOW"Kyanite II";
	}
	else if(AccountData[playerid][pLevel] == 89)
	{
		name = ""GRAY21"Iluminaty I";
	}
	else if(AccountData[playerid][pLevel] == 90)
	{
		name = ""GRAY21"Iluminaty";
	}
	else if(AccountData[playerid][pLevel] == 91)
	{
		name = ""YELLOW"King I";
	}
	else if(AccountData[playerid][pLevel] == 92)
	{
		name = ""YELLOW"King II";
	}
	else if(AccountData[playerid][pLevel] == 93)
	{
		name = ""LIGHTGREEN"Bonanza I";
	}
	else if(AccountData[playerid][pLevel] == 94)
	{
		name = ""LIGHTGREEN"Bonanza II";
	}
	else if(AccountData[playerid][pLevel] == 95)
	{
		name = ""PURPLE"Kraken I";
	}
	else if(AccountData[playerid][pLevel] == 96)
	{
		name = ""PURPLE"Kraken II";
	}
	else if(AccountData[playerid][pLevel] == 97)
	{
		name = ""YELLOW"Naomi I";
	}
	else if(AccountData[playerid][pLevel] == 98)
	{
		name = ""YELLOW"Naomi II";
	}
	else if(AccountData[playerid][pLevel] == 99)
	{
		name = ""RED"Pragmatic I";
	}
	else if(AccountData[playerid][pLevel] == 100)
	{
		name = ""LIGHTSALMON"PRAGMATIC";
	}
	
	return name;
}*/

GetPlayerNameAdmin(playerid)
{
	new frmtname[128];

	format(frmtname, sizeof(frmtname), "%s", AdminName[AccountData[playerid][pAdmin]]);
	return frmtname;
}

Player_Stats(playerid, targetid)
{
	new fname[125], fid = AccountData[targetid][pFamily];
	if(fid != -1)
	{
		format(fname, sizeof(fname), FamData[fid][famName]);
	}
	else 
	{
		format(fname, sizeof(fname), "N/A");
	}

	new scoremath;
	if(AccountData[targetid][pLevel] <= 10)
	{
		scoremath = ((AccountData[targetid][pLevel] * 550) + 1);
	}
	else if(AccountData[targetid][pLevel] <= 30)
	{
		scoremath = ((AccountData[targetid][pLevel] * 700) + 1);
	}
	else if(AccountData[targetid][pLevel] <= 50)
	{
		scoremath = ((AccountData[targetid][pLevel] * 1200) + 1);
	}
	else
	{
		scoremath = ((AccountData[targetid][pLevel] * 1550) + 1);
	}

	new VipExpired[258], StarsExpired[258];
	if(AccountData[targetid][pVip] != 0 && AccountData[targetid][pVipTime] == 0)
	{
		VipExpired = ""DEEPSKYBLUE1"Permanent";
	}
	else if(AccountData[targetid][pVip] != 0 && AccountData[targetid][pVipTime] != 0)
	{
		VipExpired = RemainingTimelapse(AccountData[targetid][pVipTime]);
	}
	else
	{
		VipExpired = ""RED"Habis";
	}

	if(AccountData[targetid][pTheStars] != 0 && AccountData[targetid][pTheStarsTime] != 0)
	{
		StarsExpired = RemainingTimelapse(AccountData[targetid][pTheStarsTime]);
	}
	else
	{
		StarsExpired = ""RED"Habis";
	}

	new title[255], shstr[2125];
	format(title, sizeof(title), ""TCRP"District  "WHITE"- %s(%d) - (%s)", AccountData[targetid][pName], targetid, AccountData[targetid][pUCP]);
	format(shstr, sizeof(shstr), "Kategori\t\t-	Detail\n");
	format(shstr, sizeof(shstr), "%sCharacter UID\t\t:	%d\n", shstr, AccountData[targetid][pID]);
	format(shstr, sizeof(shstr), "%s"GRAY"Nama UCP\t\t:	"GRAY"%s\n", shstr, AccountData[targetid][pUCP]);
	format(shstr, sizeof(shstr), "%sNama Lengkap\t\t:	%s\n", shstr, AccountData[targetid][pName]);
	format(shstr, sizeof(shstr), "%s"GRAY"Tanggal Lahir\t\t:	"GRAY"%s\n", shstr, AccountData[targetid][pAge]);
	format(shstr, sizeof(shstr), "%sTinggi Badan\t\t:	%d cm\n", shstr, AccountData[targetid][pTinggiBadan]);
	format(shstr, sizeof(shstr), "%s"GRAY"Berat Badan\t\t:	"GRAY"%d kg\n", shstr, AccountData[targetid][pBeratBadan]);
	format(shstr, sizeof(shstr), "%sAsal Negara\t\t:	%s\n", shstr, AccountData[targetid][pOrigin]);
	format(shstr, sizeof(shstr), "%s"GRAY"Jenis Kelamin\t\t:	"GRAY"%s\n", shstr, (AccountData[targetid][pGender] == 2) ? ("Perempuan") : ("Laki - Laki"));
	format(shstr, sizeof(shstr), "%sPekerjaan\t\t:	%s\n", shstr, GetPlayerJobName(targetid));
	format(shstr, sizeof(shstr), "%s"GRAY"Nomor Telepon\t\t:	"GRAY"%s\n", shstr, AccountData[targetid][pPhone]);
	format(shstr, sizeof(shstr), "%sFaction\t\t:	%s\n", shstr, GetFactName(targetid));
	format(shstr, sizeof(shstr), "%s"GRAY"Faction Rank\t\t:	"GRAY"%s\n", shstr, GetFactionRank(targetid));
	format(shstr, sizeof(shstr), "%sFamilies\t\t:	%s\n", shstr, fname);
	format(shstr, sizeof(shstr), "%s"GRAY"Families Rank\t\t:	"GRAY"%s\n", shstr, GetFamilyRank(targetid));
	format(shstr, sizeof(shstr), "%sUang Kotor\t\t:	"RED"%s\n", shstr, FormatMoney(AccountData[targetid][pRedMoney]));
	format(shstr, sizeof(shstr), "%s"GRAY"Uang Saku\t\t:	"DARKGREEN"%s\n", shstr, FormatMoney(AccountData[targetid][pMoney]));
	format(shstr, sizeof(shstr), "%sUang Rekening\t\t:	"DARKGREEN"%s\n", shstr, FormatMoney(AccountData[targetid][pBankMoney]));
	format(shstr, sizeof(shstr), "%s"GRAY"Darah Merah\t\t:	"RED"%d.00\n", shstr, GetHealth(targetid));
	format(shstr, sizeof(shstr), "%sDarah Putih\t\t:	%d.00\n", shstr, GetArmor(targetid));
	format(shstr, sizeof(shstr), "%s"GRAY"Lapar\t\t:	"GRAY"%d%%\n", shstr, AccountData[targetid][pHunger]);
	format(shstr, sizeof(shstr), "%sHaus\t\t:	%d%%\n", shstr, AccountData[targetid][pThirst]);
	format(shstr, sizeof(shstr), "%s"GRAY"Stress\t\t:	"GRAY"%d%%\n", shstr, AccountData[targetid][pStress]);
	format(shstr, sizeof(shstr), "%sTotal Warning\t\t:	"YELLOW"%d/20\n", shstr, AccountData[targetid][pWarn]);
	format(shstr, sizeof(shstr), "%s"GRAY"Level\t\t:	"GRAY"%d - %s\n", shstr, AccountData[targetid][pLevel], GetPlayerLevelName(targetid));
	format(shstr, sizeof(shstr), "%sXP\t\t:	%d/%d\n", shstr, AccountData[targetid][pLevelUp], scoremath);
	format(shstr, sizeof(shstr), "%s"GRAY"Admin Level\t\t:	"GRAY"%s\n", shstr, GetPlayerNameAdmin(targetid));
	format(shstr, sizeof(shstr), "%sHandle Goodside\t\t:	%s\n", shstr, AccountData[targetid][pHandleGoodside] ? ""GREEN"Aktif" : ""RED"Tidak");
	format(shstr, sizeof(shstr), "%s"GRAY"Handle Badside\t\t:	"GRAY"%s\n", shstr, AccountData[targetid][pHandleBadside] ? ""GREEN"Aktif" : ""RED"Tidak");
	format(shstr, sizeof(shstr), "%sThe Stars\t\t:	%s\n", shstr, (AccountData[playerid][pTheStars]) ? ""GREEN"The Stars" : ""RED"Bukan The Stars");
	format(shstr, sizeof(shstr), "%s"GRAY"The Stars Expired\t\t:	"GRAY"%s\n", shstr, StarsExpired);
	format(shstr, sizeof(shstr), "%sVIP Level\t\t:	%s\n", shstr, GetPlayerVipName(targetid));
	format(shstr, sizeof(shstr), "%s"GRAY"Masa Berlaku VIP\t\t:	"GRAY"%s\n", shstr, VipExpired);
	format(shstr, sizeof(shstr), "%sPrivate Message\t\t:	%s\n", shstr, AccountData[targetid][pTogPM] ? ""GREEN"Aktif" : ""RED"Non-Aktif");
	format(shstr, sizeof(shstr), "%s"GRAY"Global Chat Message\t\t:	"GREEN"Aktif\n", shstr);
	format(shstr, sizeof(shstr), "%sSkin ID\t\t:	%d\n", shstr, AccountData[targetid][pSkin]);
	format(shstr, sizeof(shstr), "%s"GRAY"World ID\t\t:	"GRAY"%d\n", shstr, GetPlayerVirtualWorld(targetid));
	format(shstr, sizeof(shstr), "%sInterior ID\t\t:	%d\n", shstr, GetPlayerInterior(targetid));
	format(shstr, sizeof(shstr), "%s"GRAY"House ID\t\t:	"GRAY"%d\n", shstr, AccountData[targetid][pInHouse]);
	format(shstr, sizeof(shstr), "%sRusun ID\t\t:	%d\n", shstr, AccountData[targetid][pInRusun]);
	format(shstr, sizeof(shstr), "%s"GRAY"Door ID\t\t:	"GRAY"%d\n", shstr, AccountData[targetid][pInDoor]);
	format(shstr, sizeof(shstr), "%sFamily ID\t\t:	%d\n", shstr, AccountData[targetid][pInFamily]);
	format(shstr, sizeof(shstr), "%s"GRAY"Tanggal Pembuatan Karakter\t\t:	"GRAY"%s\n", shstr, AccountData[targetid][pRegDate]);
	format(shstr, sizeof(shstr), "%sRiwayat Terakhir Login\t\t:	%s\n", shstr, AccountData[targetid][pLastLogin]);
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, title, shstr, "Tutup", "");
	return 1;
}

DisplayLicensi(playerid, p2)
{
	new sima[128], simb[128], simc[128], gunlic[128], huntinglic[128];
	new timea[598], timeb[598], timec[598];

	if(AccountData[p2][pSimATime] <= gettime()) {
		format(timea, sizeof(timea), ""RED"Habis");
	} else format(timea, sizeof(timea), ""YELLOW"%s", RemainingTimelapse(AccountData[p2][pSimATime]));
	
	if(AccountData[p2][pSimBTime] <= gettime()) {
		format(timeb, sizeof(timeb), ""RED"Habis");
	} else format(timeb, sizeof(timeb), ""YELLOW"%s", RemainingTimelapse(AccountData[p2][pSimBTime]));
	
	if(AccountData[p2][pSimCTime] <= gettime()) {
		format(timec, sizeof(timec), ""RED"Habis");
	} else format(timec, sizeof(timec), ""YELLOW"%s", RemainingTimelapse(AccountData[p2][pSimCTime]));

	if(AccountData[p2][pSimA] == 1)
	{
		sima = ""GREEN"Dimiliki";
	}
	else 
	{
		sima = ""RED_E"Tidak Memiliki";
	}
	if(AccountData[p2][pSimB] == 1)
	{
		simb = ""GREEN"Dimiliki";
	}
	else 
	{
		simb = ""RED_E"Tidak Memiliki";
	}
	if(AccountData[p2][pSimC] == 1)
	{
		simc = ""GREEN"Dimiliki";
	}
	else 
	{
		simc = ""RED_E"Tidak Memiliki";
	}
	if(AccountData[p2][pGunLic] == 1)
	{
		gunlic = ""GREEN"Dimiliki";
	}
	else 
	{
		gunlic = ""RED_E"Tidak Memiliki";
	}
	if(AccountData[p2][pHuntingLic] == 1)
	{
		huntinglic = ""GREEN"Dimiliki";
	}
	else
	{
		huntinglic = ""RED_E"Tidak Memiliki";
	}

	new gunlictime[525];
	if(AccountData[p2][pGunLicTime] <= gettime()) {
		format(gunlictime, sizeof(gunlictime), ""RED"Habis");
	} else format(gunlictime, sizeof(gunlictime), ""YELLOW"%s", RemainingTimelapse(AccountData[p2][pGunLicTime]));
	
	new huntlictime[598];
	if(AccountData[p2][pHuntingLicTime] <= gettime()) {
		format(huntlictime, sizeof(huntlictime), ""RED"Habis");
	} else format(huntlictime, sizeof(huntlictime), ""YELLOW"%s", RemainingTimelapse(AccountData[p2][pHuntingLicTime]));

	static jskc[1057];
	format(jskc, sizeof(jskc), ""WHITE"Pemerintah Kota District  merilis kepemilikan lisensi dari "YELLOW"%s\n\
	\n"GREEN"-[Lisensi Mengemudi]-\
	\n"WHITE"Surat Izin Mengemudi (SIM) A: %s "WHITE"Berlaku s/d: %s\
	\n"WHITE"Surat Izin Mengemudi (SIM) B: %s "WHITE"Berlaku s/d: %s\
	\n"WHITE"Surat Izin Mengemudi (SIM) C: %s "WHITE"Berlaku s/d: %s\n\
	\n"GREEN"-[Lisensi Lainnya]-\
	\n"WHITE"Surat Izin Kepemilikan Senjata Api: %s "WHITE"Berlaku s/d: %s\
	\n"WHITE"Surat Izin Berburu: %s "WHITE"Berlaku s/d: %s\
	",
	AccountData[p2][pName],
	sima,
	timea,
	simb,
	timeb,
	simc,
	timec,
	gunlic,
	gunlictime,
	huntinglic,
	huntlictime);
	Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Lisensi", jskc, "Tutup", "");
}

DisplayBPJS(playerid, p2)
{
	static jskc[812];
	if(AccountData[p2][pBPJS] == 1)
	{
		format(jskc, sizeof(jskc), ""WHITE"========== KARTU District SEHAT ==========\
		\nNama: %s\
		\nJenis Kelamin: %s\
		\nTanggal Lahir: %s\
		\nFaskes: "ORANGE"%s\n\
		\n"WHITE"Masa Berlaku s/d: "LIGHTGREEN"%s\n\
		\n"LIGHTGREEN"-%s-\
		\n"WHITE"Mitra RSU District \
		", AccountData[p2][pName], (AccountData[p2][pGender] == 2) ? ("Perempuan") : ("Laki-Laki"), AccountData[p2][pAge], AccountData[p2][pBPJSLevel], ReturnDate(AccountData[p2][pBPJSTime]),
		AccountData[p2][pName]);
	}
	Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Kartu District  Sehat", jskc, "Tutup", "");
	return 1;
}

DisplaySKWB(playerid, nearplayer)
{
	static shstr[525];
	format(shstr, sizeof(shstr), ""WHITE"============ SURAT KETERANGAN WARGA BARU ============\
	\nSaya yang bertanda tangan dibawah ini:\n\
	\nNama: "YELLOW"%s\
	\n"WHITE"Jenis Kelamin: "YELLOW"%s\
	\n"WHITE"Tempat, Tgl Lahir: "YELLOW"%s, %s\
	\n"WHITE"Nomor Telepon: "YELLOW"%s\
	\n"WHITE"============================================\
	\nDemikian surat resmi tanda bahwa yang bersangkutan adalah Warga Baru di Kota "DEEPSKYBLUE1"District "WHITE".\n\
	\nMasa Aktif Berlaku Sampai: "DARKORANGE"%s",
	ReturnName(playerid), (AccountData[playerid][pGender] == 1) ? "Laki-Laki" : "Perempuan", AccountData[playerid][pOrigin], AccountData[playerid][pAge], AccountData[playerid][pPhone], RemainingTimelapse(AccountData[playerid][pSKWBTime]));
	ShowPlayerDialog(nearplayer, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- SKWB", shstr, "Tutup", "");
	return 1;
}

DisplaySKCK(playerid, p2)
{
	new jskc[812];
	if(AccountData[p2][pSKCK] == 1)
	{
		format(jskc, sizeof(jskc),""WHITE"========== SURAT KETERANGAN CATATAN KEPOLISIAN ==========\
		\nSaya yang bertanda tangan dibawah ini:\
		\nNama: %s\
		\nJabatan: %s\n\
		\nMenyatakan Bahwa:\
		\nNama: %s\
		\nJenis Kelamin: %s\
		\nTanggal Lahir: %s\n\
		\n"WHITE"Keterangan:\
		\n"ORANGE"%s\n\
		\n"WHITE"Masa Aktif Berlaku s/d: "LIGHTGREEN"%s\n\
		\n"WHITE"Demikian surat resmi dari Kepolisian Kota District  agar dapat digunakan sebagaimana mestinya.\n\
		\n"LIGHTGREEN"-%s-\
		\n"WHITE"- Kepolisian Kota District \
		", AccountData[p2][pSKCKNamePol], AccountData[p2][pSKCKRankPol], AccountData[p2][pName], (AccountData[p2][pGender] == 2) ? ("Perempuan") : ("Laki-Laki"), AccountData[p2][pAge], 
		AccountData[p2][pSKCKReason], ReturnDate(AccountData[p2][pSKCKTime]), AccountData[p2][pName]);
	}
	Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Surat Keterangan Catatan Kepolisian", jskc, "Tutup", "");
	return 1;
}

DisplaySKS(playerid, p2)
{
	new dannn[812];
	if(AccountData[p2][pSKS] == 1)
	{
		format(dannn, sizeof(dannn), ""WHITE"========== SURAT KETERANGAN SEHAT ==========\
		\nSaya yang bertanda tangan dibawah ini:\
		\nNama: %s\
		\nJabatan: %s\n\
		\nMenyatakan Bahwa:\
		\nNama: %s\
		\nJenis Kelamin: %s\
		\nTanggal Lahir: %s\n\
		\nMemberitahu Bahwa:\
		\n"ORANGE"%s\n\
		\n"WHITE"KETERANGAN & TANDA TANGAN\
		\nBahwa surat ini dinyatakan sah di mata negara dan hukum.\
		\nMasa Berlaku s/d "LIGHTGREEN"%s\
		\n"GREEN"-%s-\
		", AccountData[p2][pSKSNameDoc], AccountData[p2][pSKSRankDoc], AccountData[p2][pName], (AccountData[p2][pGender] == 2) ? ("Perempuan") : ("Laki-Laki"), AccountData[p2][pAge],
		AccountData[p2][pSKSReason], ReturnDate(AccountData[p2][pSKSTime]), AccountData[p2][pName]);
	}
	Dialog_Show(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Surat Keterangan Sehat", dannn, "Tutup", "");
	return 1;
}

GetBoneStatus(playerid, p2)
{
	new string[400];
	new hh = AccountData[p2][pHead];
	new hp = AccountData[p2][pPerut];
	new htk = AccountData[p2][pRHand];
	new htka = AccountData[p2][pLHand];
	new hkk = AccountData[p2][pRFoot];
	new hkka = AccountData[p2][pLFoot];
	format(string, sizeof string, "Bagian Tubuh\tKondisi\n");
	format(string, sizeof string, "%s Kepala\t%d.0%%\n", string, hh);
	format(string, sizeof string, "%s "GRAY"Perut\t%d.0%%\n", string, hp);
	format(string, sizeof string, "%s Lengan Kanan\t%d.0%%\n", string, htk);
	format(string, sizeof string, "%s "GRAY"Lengan Kiri\t%d.0%%\n", string, htka);
	format(string, sizeof string, "%s Kaki Kanan\t%d.0%%\n", string, hkk);
	format(string, sizeof string, "%s "GRAY"Kaki Kiri\t%d.0%%\n", string, hkka);
	format(string, sizeof string, "%s Lapar\t%d%%\n", string, AccountData[p2][pHunger]);
	format(string, sizeof string, "%s "GRAY"Haus\t%d%%\n", string, AccountData[p2][pThirst]);
	ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District "WHITE" - Kesehatan", string, "Tutup", "");
    return 1;
}

SendFactionMessage(factionid, color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 12)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 12); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string
        #emit PUSH.C args

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player) if(AccountData[i][pFaction] == factionid) {
                SendClientMessage(i, color, string);
        }
        return 1;
    }
    foreach (new i : Player) if(AccountData[i][pFaction] == factionid) {
        SendClientMessage(i, color, str);
    }
    return 1;
}

/*stock SendEmbedMessage(const title[], const description[], const footer_text[], const footer_url[], const thumbnail_url[], const channel_id[], color = 0xFFFFFF33)
{
	new DCC_Channel:EmbedChannel, DCC_Embed:Embed;

	EmbedChannel = DCC_FindChannelById(channel_id);

	if (!EmbedChannel) {
		return 0; // gagal mengirim pesan karena kanal tidak ditemukan
	}

	Embed = DCC_CreateEmbed(.title = title, .description = description);
	DCC_SetEmbedColor(Embed, color);

	if (strlen(footer_text) > 0) {
		DCC_SetEmbedFooter(Embed, .footer_text = footer_text, .footer_icon_url = footer_url); // set footer text jika ditemukan huruf
	}

	if (strlen(thumbnail_url) > 0) {
		DCC_SetEmbedThumbnail(Embed, .thumbnail_url = thumbnail_url);
	}

	DCC_SendChannelEmbedMessage(EmbedChannel, Embed);
	return 1;
}*/

GetFactName(playerid)
{
	new frmtname[125];

	format(frmtname, sizeof(frmtname), "%s", FactName[AccountData[playerid][pFaction]]);
	return frmtname;
}

ResetFactionMap(playerid)
{
	for(new i = 0; i < 12; i ++) {
		if(DestroyDynamicObject(PoliceObject[playerid][i]))
			PoliceObject[playerid][i] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	}
	for(new i = 0; i < 6; i ++) {
		if(DestroyDynamicObject(Bengkel_Object[playerid][i]))
			Bengkel_Object[playerid][i] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	}
	for(new i = 0; i < 7; i ++) {
		if(DestroyDynamicObject(EMSObject[playerid][i]))
			EMSObject[playerid][i] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	}
	for(new i = 0; i < 5; i++) {
		if(DestroyDynamicObject(Trans_Object[playerid][i]))
			Trans_Object[playerid][i] = STREAMER_TAG_OBJECT:INVALID_STREAMER_ID;
	}
	for(new i = 0; i < 5; i ++) {
		if(DestroyDynamicObject(PemerObject[playerid][i]))
			PemerObject[playerid][i] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	}
	for(new i = 0; i < 8; i ++) {
		if(DestroyDynamicObject(Pedagang_Objects[playerid][i]))
			Pedagang_Objects[playerid][i] = STREAMER_TAG_OBJECT: INVALID_STREAMER_ID;
	}
	return 1;
}

RefreshFactionMap(playerid)
{
	ResetFactionMap(playerid);
	
	if(AccountData[playerid][pFaction] > 0)
	{
		if(AccountData[playerid][pFaction] == FACTION_POLISI)
		{
			PoliceObject[playerid][0] = CreateCirclePickup(COLOR_CLIENT, 659.6660,-1503.6816,20.9643, 0, 0, playerid); // Polda Duty
			PoliceObject[playerid][8] = CreateCirclePickup(COLOR_CLIENT, 967.5986,2469.6765,10.9001, -1, -1, playerid); // Federal Duty

			if(AccountData[playerid][pDutyPD])
			{
				PoliceObject[playerid][1] = CreateCirclePickup(COLOR_CLIENT, 659.1224,-1519.9105,17.4683, 0, 0, playerid); // Desk Polda
				PoliceObject[playerid][2] = CreateCirclePickup(COLOR_CLIENT, 659.5682,-1493.7123,20.9623, 0, 0, playerid); // Locker Gun
				PoliceObject[playerid][3] = CreateCirclePickup(COLOR_CLIENT, 660.0930,-1516.5671,20.9643, 0, 0, playerid); // Brankas Barang
				PoliceObject[playerid][4] = CreateCirclePickup(COLOR_CLIENT, 662.8520,-1498.8215,20.9643, 0, 0, playerid); // Locker Baju
				PoliceObject[playerid][5] = CreateCirclePickup(COLOR_CLIENT, 1490.709350, -1801.254638, 13.546895, 0, 0, playerid); // Garasi
				PoliceObject[playerid][6] = CreateCirclePickup(COLOR_CLIENT, 983.5379,2474.1208,10.8549, 0, 0, playerid); // Impound
				PoliceObject[playerid][7] = CreateCirclePickup(COLOR_CLIENT, 675.5129,-1509.8757,30.5265, 0, 0, playerid); // helipad
				PoliceObject[playerid][9] = CreateCirclePickup(COLOR_CLIENT, 248.4755, 1859.1525, 14.0840, -1, -1, playerid);
				PoliceObject[playerid][10] = CreateCirclePickup(COLOR_CLIENT, 249.8746, 1828.6891, 17.6406, -1, -1, playerid);
				PoliceObject[playerid][11] = CreateCirclePickup(COLOR_CLIENT, 662.5468,-1493.5961,20.9623, 0, 0, playerid); //lockersenjataanggota
			}
		}
		
		if(AccountData[playerid][pFaction] == FACTION_PEMERINTAH)
		{
			PemerObject[playerid][0] = CreateCirclePickup(0xC855E8E0, 1410.2715,1565.2283,3010.8323, 0, 0, playerid); // Duty
			
			if(AccountData[playerid][pDutyPemerintah])
			{
				PemerObject[playerid][1] = CreateCirclePickup(0xC855E8E0, 1413.1270,1563.4674,3010.8323, 0, 0, playerid); // Locker
				PemerObject[playerid][2] = CreateCirclePickup(0xC855E8E0, 1427.3378,1555.8997,3010.8323, 0, 0, playerid); // Brankas
				PemerObject[playerid][3] = CreateCirclePickup(0xC855E8E0, 1402.9844,1523.8341,3010.8398, 0, 0, playerid); // Desk
				PemerObject[playerid][4] = CreateCirclePickup(0xC855E8E0, 1239.3116, -2029.9304, 59.9014, -1, -1, playerid); // Garasi
			}
		}
		if(AccountData[playerid][pFaction] == FACTION_EMS)
		{
			EMSObject[playerid][0] = CreateCirclePickup(0xC8F4477D, 1318.4379,742.3047,10.8784, 0, 0, playerid); // Duty
			
			if(AccountData[playerid][pDutyEms])
			{
				EMSObject[playerid][1] = CreateCirclePickup(0xC8F4477D, 1796.9568,-1116.0157,24.1013, 0, 0, playerid);
				EMSObject[playerid][2] = CreateCirclePickup(0xC8F4477D, 1315.1475,743.5298,10.8784, 0, 0, playerid); // Apotik
				EMSObject[playerid][3] = CreateCirclePickup(0xC8F4477D, 1314.4333,740.5828,10.8784, 0, 0, playerid); // Desk
				EMSObject[playerid][4] = CreateCirclePickup(0xC8F4477D, 1309.0132,745.6656,10.8714, 0, 0, playerid); // Locker
				EMSObject[playerid][5] = CreateCirclePickup(0xC8F4477D, PosBrankasEms[0], PosBrankasEms[1], PosBrankasEms[2], BrankasVirtual, BrankasInterior, playerid); // Brankas Item
				EMSObject[playerid][6] = CreateCirclePickup(0xC8F4477D, 1345.3456,741.7292,17.7031, 0, 0, playerid); // Helipad
			}
		}
		if(AccountData[playerid][pFaction] == FACTION_TRANS)
		{
			Trans_Object[playerid][0] = CreateCirclePickup(X11_YELLOW, 1547.8783, -2163.1912, 13.7381, -1, -1, playerid); // Duty

			if(AccountData[playerid][pDutyTrans])
			{
				Trans_Object[playerid][1] = CreateCirclePickup(X11_YELLOW, 1555.9905, -2179.6467, 13.7381, -1, -1, playerid);
				Trans_Object[playerid][2] = CreateCirclePickup(X11_YELLOW, 1549.8779, -2179.3242, 13.7381, -1, -1, playerid);
				Trans_Object[playerid][3] = CreateCirclePickup(X11_YELLOW, 1557.0094, -2170.8276, 13.7381, -1, -1, playerid);
				Trans_Object[playerid][4] = CreateCirclePickup(X11_YELLOW, 1501.7401, -2160.7627, 13.5650, -1, -1, playerid);
			}
		}
		if(AccountData[playerid][pFaction] == FACTION_BENGKEL)
		{
			Bengkel_Object[playerid][0] = CreateCirclePickup(0xC8F8B15C, 2859.3032,-1875.5648,11.1319, -1, -1, playerid); // Duty
			
			if(AccountData[playerid][pDutyBengkel])
			{
				Bengkel_Object[playerid][1] = CreateCirclePickup(0xC8F8B15C, 2861.9329,-1868.8961,11.1357, -1, -1, playerid); // Craft
				Bengkel_Object[playerid][2] = CreateCirclePickup(0xC8F8B15C, 2862.0681,-1873.4342,11.1365, -1, -1, playerid); // Brankas
				Bengkel_Object[playerid][3] = CreateCirclePickup(0xC8F8B15C, 2863.5364,-1876.0488,11.1394, -1, -1, playerid); // Locker
				Bengkel_Object[playerid][4] = CreateCirclePickup(0xC8F8B15C, 2856.9292,-1872.4506,11.1274, -1, -1, playerid); // Desk
				Bengkel_Object[playerid][5] = CreateCirclePickup(0xC8F8B15C, -84.8240, 1043.5159, 19.7411, -1, -1, playerid); // Duty
			}
		}
		if(AccountData[playerid][pFaction] == FACTION_PEDAGANG)
		{
			Pedagang_Objects[playerid][0] = CreateCirclePickup(0xFFCC0033, 350.9044,-1848.0898,5.3773, -1, -1, playerid); // Duty
			Pedagang_Objects[playerid][1] = CreateCirclePickup(0xFFCC0033, 354.7868,-1846.7720,5.3873, -1, -1, playerid); // Desk

			if(AccountData[playerid][pDutyPedagang])
			{
				Pedagang_Objects[playerid][2] = CreateCirclePickup(0xFFCC0033, 346.7945,-1847.1002,5.3773, -1, -1, playerid); // Locker
				Pedagang_Objects[playerid][3] = CreateCirclePickup(0xFFCC0033, 316.1964,-1801.1807,4.5922, -1, -1, playerid); // Garasi
				Pedagang_Objects[playerid][4] = CreateCirclePickup(0xFFCC0033, 321.8679,-1851.1921,5.0982, -1, -1, playerid); // Masak
				Pedagang_Objects[playerid][5] = CreateCirclePickup(0xFFCC0033, 327.2828,-1851.7909,5.0982, -1, -1, playerid); // Kulkas
				
				Pedagang_Objects[playerid][6] = CreateCirclePickup(0xFFCC0033, 856.4885, 712.6636, 5005.0396, 5, 5, playerid); // Kulkas Ems
				Pedagang_Objects[playerid][7] = CreateCirclePickup(0xFFCC0033, 856.7956, 717.3268, 5005.0396, 5, 5, playerid); // Kulkas Ems
			}
		}
	}
    return 1;
}

CarryPlayerNearest(playerid, targetid)
{
	if(IsPlayerInAnyVehicle(playerid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda harus di luar dari kendaraan!");
	if(IsPlayerInAnyVehicle(targetid)) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut harus di luar dari kendaraan!");
	foreach(new i : Player) if (IsPlayerConnected(i))
	{
		if(IsDragging[i] == targetid) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut sedang digendong orang lain!");
	}

	IsDragging[playerid] = targetid;
	AccountData[targetid][pDraggedBy] = playerid;
	ShowTDN(targetid, NOTIFICATION_WARNING, sprintf("Anda digendong oleh %s.", ReturnName(targetid)));
	return 1;
}

SQL_IsCharacterLogged(playerid)
{
	return (IsPlayerConnected(playerid) && AccountData[playerid][IsLoggedIn]);
}

GetBodyPartName(bodypart)
{
    new part[11];
    switch(bodypart)
    {
        case BODY_PART_TORSO: part = "Torso";
        case BODY_PART_GROIN: part = "Groin";
        case BODY_PART_LEFT_ARM: part = "Left Arm";
        case BODY_PART_RIGHT_ARM: part = "Right Arm";
        case BODY_PART_LEFT_LEG: part = "Left Leg";
        case BODY_PART_RIGHT_LEG: part = "Right Leg";
        case BODY_PART_HEAD: part = "Head";
        default: part = "None";
    }
    return part;
}

ResetPlayer(playerid)
{
	AccountData[playerid][EditingPOMID] = -1;
	AccountData[playerid][EditingDeerID] = -1;
	AccountData[playerid][EditingATMID] = -1;
	AccountData[playerid][EditingLADANGID] = -1;
	AccountData[playerid][EditingUraniumID] = -1;
	AccountData[playerid][EditingROBERID] = -1;
	AccountData[playerid][EditingSAMPAHID] = -1;
	AccountData[playerid][pEditTextObject] = -1;
	AccountData[playerid][pEditSlotID] = -1;
	AccountData[playerid][bEditID] = -1;
	AccountData[playerid][gEditID] = -1;
	return 1;
}

stock RemoveAlpha(color) {
    return (color & ~0xFF);
}

ShowATMTD(playerid)
{
	new xjjs[512];
	for(new txd = 0; txd < 44; txd ++){
		PlayerTextDrawShow(playerid, VR_ATMTD[playerid][txd]);
	}
	format(xjjs, sizeof(xjjs), "%s", ReturnName(playerid));
	PlayerTextDrawSetString(playerid, VR_ATMTD[playerid][7], xjjs);
	
	format(xjjs, sizeof(xjjs), "%s", FormatMoney(AccountData[playerid][pBankMoney]));
	PlayerTextDrawSetString(playerid, VR_ATMTD[playerid][30], xjjs);

	format(xjjs, sizeof(xjjs), "%d", AccountData[playerid][pBankRek]);
	PlayerTextDrawSetString(playerid, VR_ATMTD[playerid][31], xjjs);

	SelectTextDraw(playerid, 0x00FF99CC);
	Info(playerid, "Gunakan "YELLOW"'/cursor'"WHITE" jika cursor menghilang / textdraw tidak dapat ditekan");
	return 1;
}

HideATMTD(playerid)
{
	forex(txd, 44){
		PlayerTextDrawHide(playerid, VR_ATMTD[playerid][txd]);
	}
	CancelSelectTextDraw(playerid);
	return 1;
}
ShowKTPTD(playerid)
{
	static frmxt[800];

	PlayerTextDrawSetPreviewModel(playerid, ktpTextdraws[playerid][29], AccountData[playerid][pSkin]);
	PlayerTextDrawShow(playerid, ktpTextdraws[playerid][29]);
	
	for(new i = 0; i < 61; i ++) 
	{
		PlayerTextDrawShow(playerid, ktpTextdraws[playerid][i]);
	}
	format(frmxt, sizeof(frmxt), "%s", AccountData[playerid][pName]);
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][50], frmxt);
	PlayerTextDrawShow(playerid, ktpTextdraws[playerid][50]);

	format(frmxt, sizeof(frmxt), "%s", AccountData[playerid][pAge]);
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][51], frmxt);
	PlayerTextDrawShow(playerid, ktpTextdraws[playerid][51]);

	format(frmxt, sizeof(frmxt), "%s", (AccountData[playerid][pGender] == 2) ? ("Perempuan") : ("Laki-Laki"));
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][52], frmxt);
	PlayerTextDrawShow(playerid, ktpTextdraws[playerid][52]);
	
	format(frmxt, sizeof(frmxt), "%d", AccountData[playerid][pTinggiBadan]);
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][53], frmxt);
	PlayerTextDrawShow(playerid, ktpTextdraws[playerid][53]);

	format(frmxt, sizeof(frmxt), "%s", ReturnName(playerid));
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][43], frmxt);
	PlayerTextDrawShow(playerid, ktpTextdraws[playerid][43]);

	format(frmxt, sizeof(frmxt), "%s", AccountData[playerid][pOrigin]);
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][55], frmxt);
	PlayerTextDrawShow(playerid, ktpTextdraws[playerid][55]);

	format(frmxt, sizeof(frmxt), "%s", GetPlayerJobName(playerid));
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][54], frmxt);
	PlayerTextDrawShow(playerid, ktpTextdraws[playerid][54]);

	format(frmxt, sizeof(frmxt), "%s", PlayerNIK[playerid]);
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][59], frmxt);
	PlayerTextDrawShow(playerid, ktpTextdraws[playerid][59]);

	Info(playerid, "Ktp akan otomatis tertutup secara otomatis dalam waktu 10 detik");
	SetTimerEx("Hktp", 10000, false, "d", playerid);
	return 1;
}

ShowMyKTPTD(playerid, targetid)
{
	if(!IsPlayerNearPlayer(playerid, targetid, 3.0)) 
	{
		NearestSingle[playerid] = INVALID_PLAYER_ID;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada pemain manapun disekitar anda!");
	}
	if(!IsPlayerConnected(targetid)) 
	{
		NearestSingle[playerid] = INVALID_PLAYER_ID;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Pemain tersebut tidak terkoneksi ke dalam server!");
	}
	if(!AccountData[playerid][Ktp])
	{
		NearestSingle[playerid] = INVALID_PLAYER_ID;
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda belum memiliki KTP!");
	}

	static frmxt[800];
	
	format(frmxt, sizeof(frmxt), "%s", AccountData[playerid][pName]);
	PlayerTextDrawSetString(targetid, ktpTextdraws[targetid][50], frmxt);

	format(frmxt, sizeof(frmxt), "%s", AccountData[playerid][pAge]);
	PlayerTextDrawSetString(targetid, ktpTextdraws[targetid][51], frmxt);

	format(frmxt, sizeof(frmxt), "%s", (AccountData[playerid][pGender] == 2) ? ("Perempuan") : ("Laki-Laki"));
	PlayerTextDrawSetString(targetid, ktpTextdraws[targetid][52], frmxt);
	
	format(frmxt, sizeof(frmxt), "%d", AccountData[playerid][pTinggiBadan]);
	PlayerTextDrawSetString(targetid, ktpTextdraws[targetid][53], frmxt);

	format(frmxt, sizeof(frmxt), "%s", ReturnName(playerid));
	PlayerTextDrawSetString(targetid, ktpTextdraws[targetid][43], frmxt);

	format(frmxt, sizeof(frmxt), "%s", AccountData[playerid][pOrigin]);
	PlayerTextDrawSetString(targetid, ktpTextdraws[targetid][55], frmxt);

	format(frmxt, sizeof(frmxt), "%s", GetPlayerJobName(playerid));
	PlayerTextDrawSetString(targetid, ktpTextdraws[targetid][54], frmxt);

	format(frmxt, sizeof(frmxt), "%s", PlayerNIK[playerid]);
	PlayerTextDrawSetString(targetid, ktpTextdraws[targetid][59], frmxt);

	PlayerTextDrawSetPreviewModel(playerid, ktpTextdraws[playerid][29], AccountData[playerid][pSkin]);
	PlayerTextDrawShow(playerid, ktpTextdraws[playerid][29]);

	for(new i = 0; i < 61; i++)
	{
		PlayerTextDrawShow(targetid, ktpTextdraws[targetid][i]);
	}
	Info(targetid, "Ktp akan otomatis tertutup secara otomatis dalam waktu 10 detik");
	SetTimerEx("Hktp", 10000, false, "d", playerid);
	return 1;
}

CekIdentitas(playerid, targetid)
{
	static frmxt[800];
	
	format(frmxt, sizeof(frmxt), "%s", AccountData[targetid][pName]);
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][50], frmxt);

	format(frmxt, sizeof(frmxt), "%s", AccountData[targetid][pAge]);
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][51], frmxt);

	format(frmxt, sizeof(frmxt), "%s", (AccountData[targetid][pGender] == 2) ? ("Perempuan") : ("Laki-Laki"));
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][52], frmxt);
	
	format(frmxt, sizeof(frmxt), "%d", AccountData[targetid][pTinggiBadan]);
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][53], frmxt);

	format(frmxt, sizeof(frmxt), "%s", ReturnName(targetid));
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][43], frmxt);

	format(frmxt, sizeof(frmxt), "%s", AccountData[targetid][pOrigin]);
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][55], frmxt);

	format(frmxt, sizeof(frmxt), "%s", GetPlayerJobName(targetid));
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][54], frmxt);

	format(frmxt, sizeof(frmxt), "%s", PlayerNIK[targetid]);
	PlayerTextDrawSetString(playerid, ktpTextdraws[playerid][59], frmxt);

	PlayerTextDrawSetPreviewModel(playerid, ktpTextdraws[playerid][29], AccountData[playerid][pSkin]);
	PlayerTextDrawShow(playerid, ktpTextdraws[playerid][29]);

	for(new idx = 0; idx < 61; idx ++)
	{
		PlayerTextDrawShow(playerid, ktpTextdraws[playerid][idx]);
	}
	Info(playerid, "Gunakan "YELLOW"'/hktp'"WHITE" untuk menutup textdraw ktp");
	SendRPMeAboveHead(playerid, "Memeriksa ktp milik orang didepan", X11_PLUM1);
	return 1;
}

forward Hktp(playerid);
public Hktp(playerid)
{
	for(new i = 0; i < 61; i ++)
	{
		PlayerTextDrawHide(playerid, ktpTextdraws[playerid][i]);
	}
	CancelSelectTextDraw(playerid);
	return 1;
}

stock GenerateRandomNIK(playerid)
{
    for (new i = 0; i < 16; i++)
    {
        PlayerNIK[playerid][i] = random(10) + '0'; 
    }
    PlayerNIK[playerid][16] = '\0';
	return 1;
}
stock ShowTollTD(playerid, bool: Chess7)
{
	if(!Chess7)
	{
		for(new i = 0; i < 22; i++)
		{
			TextDrawHideForPlayer(playerid, OpenTollTD[i]);
			CancelSelectTextDraw(playerid);
		}
	}
	else
	{
		for(new i = 0; i < 22; i++)
		{
			TextDrawShowForPlayer(playerid, OpenTollTD[i]);
			SelectTextDraw(playerid, COLOR_BLUE);
		}
	}
	return 1;
}

/*ShowPanel(playerid, bool:toggle)
{
	if(!toggle)
	{
		PlayerTextDrawHide(playerid, SmartphonePanel[playerid]);
		PlayerTextDrawHide(playerid, InventoryPanel[playerid]);
		PlayerTextDrawHide(playerid, VehiclePanel[playerid]);
		PlayerTextDrawHide(playerid, FashionPanel[playerid]);
		PlayerTextDrawHide(playerid, InvoicesPanel[playerid]);
		PlayerTextDrawHide(playerid, DocumentPanel[playerid]);
		PlayerTextDrawHide(playerid, ClosePanel[playerid]);
		PlayerTextDrawHide(playerid, IdentPanel[playerid]);
		for(new x = 0; x < 44; x ++)
		{
			PlayerTextDrawHide(playerid, ATRP_Panel[playerid][x]);
		}
	}
	else
	{
		PlayerTextDrawShow(playerid, SmartphonePanel[playerid]);
		PlayerTextDrawShow(playerid, InventoryPanel[playerid]);
		PlayerTextDrawShow(playerid, VehiclePanel[playerid]);
		PlayerTextDrawShow(playerid, FashionPanel[playerid]);
		PlayerTextDrawShow(playerid, InvoicesPanel[playerid]);
		PlayerTextDrawShow(playerid, DocumentPanel[playerid]);
		PlayerTextDrawShow(playerid, ClosePanel[playerid]);
		PlayerTextDrawShow(playerid, IdentPanel[playerid]);
		for(new x = 0; x < 44; x ++)
		{
			PlayerTextDrawShow(playerid, ATRP_Panel[playerid][x]);
		}
	}
	return 1;
}*/

stock StrStr(const source[], const find[], bool:caseSensitive = true)
{
    new source_len = strlen(source);
    new find_len = strlen(find);

    for (new i = 0; i <= source_len - find_len; i++)
    {
        new j;
        for (j = 0; j < find_len; j++)
        {
            if (caseSensitive)
            {
                if (source[i + j] != find[j])
                    break;
            }
            else
            {
                if (tolower(source[i + j]) != tolower(find[j]))
                    break;
            }
        }

        if (j == find_len)
            return i; // Mengembalikan indeks pertama tempat substring ditemukan
    }

    return -1; // Substring tidak ditemukan
}

stock ReturnIP(playerid)
{
	static
	    ip[16];

	GetPlayerIp(playerid, ip, sizeof(ip));
	AccountData[playerid][pIP] = ip;
	return ip;
}

stock GetFuel(vehicleid)
{
	return VehicleCore[vehicleid][vCoreFuel];
}

GivePlayerXP(playerid, EXP)
{
	AccountData[playerid][pLevelUp] += EXP;
	return 1;
}

ResetNameTag(playerid, bool:mask = false)
{
	if(mask)
	{
		if(IsValidDynamic3DTextLabel(AccountData[playerid][pMaskLabel]))
			DestroyDynamic3DTextLabel(AccountData[playerid][pMaskLabel]);

		AccountData[playerid][pMaskLabel] = STREAMER_TAG_3D_TEXT_LABEL: INVALID_STREAMER_ID;
		AccountData[playerid][pMaskOn] = false;
	}
	return 1;
}

PlayVehicleAudio(playerid, vehicleid)
{
    if(!strcmp(PlayerVehicle[vehicleid][vehURL], "Off", true))
    {
        StopAudioStreamForPlayer(playerid);
        AccountData[playerid][pVehAudioPlay] = 0;
    }
    else
    {
        StopAudioStreamForPlayer(playerid);
        PlayAudioStreamForPlayer(playerid, PlayerVehicle[vehicleid][vehURL]);
        AccountData[playerid][pVehAudioPlay] = 1;
    }
    return 1;
}

PlayVehicleAudioInCar(playerid, url[])
{
    new vid = GetPlayerVehicleID(playerid);
    new vehicleid = -1;
    vehicleid = Vehicle_ReturnID(vid);

    if(vehicleid == RETURN_INVALID_VEHICLE_ID) 
        return 0;

    PlayerVehicle[vehicleid][vehAudio] = 1;
    strpack(PlayerVehicle[vehicleid][vehURL], url, 128 char);
    foreach (new i : Player)
    { 
        if(IsPlayerInVehicle(i, GetPlayerVehicleID(playerid))) 
        {
            if(!strcmp(url, "Off", true))
            {
                StopAudioStreamForPlayer(i);
                PlayerVehicle[vehicleid][vehAudio] = 0;
                AccountData[i][pVehAudioPlay] = 0;
            }
            else
            {
                StopAudioStreamForPlayer(i);
                PlayAudioStreamForPlayer(i, url);
                AccountData[i][pVehAudioPlay] = 1;
            }
        }
    }
    return 1;
}
PlayHouseAudio(playerid, houseid)
{
    if(!strcmp(HouseData[houseid][hsURL], "Off", true))
    {
        StopAudioStreamForPlayer(playerid);
        AccountData[playerid][hsAudioPlay] = 0;
    }
    else
    {
        StopAudioStreamForPlayer(playerid);
        PlayAudioStreamForPlayer(playerid, HouseData[houseid][hsURL]);
        AccountData[playerid][hsAudioPlay] = 1;
    }
    return 1;
}

PlayHouseAudioInHouse(playerid, url[])
{
    new houseid = House_Inside(playerid);
	if(houseid == -1) return false;

	HouseData[houseid][hsAudio] = 1;
	strpack(HouseData[houseid][hsURL], url, 128 char);
	foreach(new i : Player) {
		if(IsPlayerInRangeOfPoint(i, 50.0, HouseData[houseid][hsIntPos][0], HouseData[houseid][hsIntPos][1], HouseData[houseid][hsIntPos][2]) && GetPlayerVirtualWorld(playerid) == houseid && GetPlayerInterior(playerid) == HouseData[houseid][hsInt])
		{
			if(!strcmp(url, "off", true))
			{
				StopAudioStreamForPlayer(i);
				HouseData[houseid][hsAudio] = 0;
				AccountData[i][hsAudioPlay] = 0;
			}
			else 
			{
				StopAudioStreamForPlayer(i);
				PlayAudioStreamForPlayer(i, url);
				AccountData[i][hsAudioPlay] = 1;
			}
		}
	}
    return 1;
}

ReplaceString(text[])
{
    new replace[128];
    format(replace, sizeof(replace), text);

	strreplace(replace, "(e)", "\n");
	strreplace(replace, "(n)", "\n");
    strreplace(replace, "(b)", "{4285f4}");
    strreplace(replace, "(bl)", "{000000}");
    strreplace(replace, "(w)", "{FFFFFF}");
    strreplace(replace, "(r)", "{ea4335}");
    strreplace(replace, "(g)", "{34a853}");
    strreplace(replace, "(y)", "{fbbc05}");
    strreplace(replace, "(p)", "{F88081}");
    return replace;
}

/*UnloadVarsPlayerJob(playerid)
{
	if(AccountData[playerid][pJob] == JOB_BUS)
	{
		UnloadVarsBus(playerid);
	}

	if(AccountData[playerid][pJob] == JOB_MINER)
	{
		UnloadMinerJobStuffs(playerid);
	}

	if(AccountData[playerid][pJob] == JOB_BUTCHER)
	{
		UnloadVarsButcher(playerid);
	}

	if(AccountData[playerid][pJob] == JOB_RECYCLER)
	{
		UnloadVarsDaur(playerid);
	}

	if(AccountData[playerid][pJob] == JOB_FARMER)
	{
		UnloadVarsFarmer(playerid);
	}

	if(AccountData[playerid][pJob] == JOB_KARGO)
	{
		UnloadVarsKargo(playerid);
	}

	if(AccountData[playerid][pJob] == JOB_LUMBERJACK)
	{
		UnloadVarsLumber(playerid);
	}

	if(AccountData[playerid][pJob] == JOB_TAILOR)
	{
		UnloadVarsTailor(playerid);
	}

	if(AccountData[playerid][pJob] == JOB_OILMAN)
	{
		UnloadVarsOilman(playerid);
	}

	if(AccountData[playerid][pJob] == JOB_FISHERMAN)
	{
		UnloadVarsFisherman(playerid);
	}	

	if(AccountData[playerid][pJob] == JOB_MILKER)
	{
		UnloadVarsMilker(playerid);
	}	
	return 1;
}*/

UnloadVarsPlayerJob(playerid)
{
	UnloadVarsBus(playerid);
	UnloadMinerJobStuffs(playerid);
	UnloadVarsButcher(playerid);
	UnloadVarsDaur(playerid);
	UnloadVarsFarmer(playerid);
	UnloadVarsKargo(playerid);
	UnloadVarsLumber(playerid);
	UnloadVarsTailor(playerid);
	UnloadVarsOilman(playerid);
	UnloadVarsFisherman(playerid);
	UnloadVarsMilker(playerid);
	return 1;
}

LoadPlayerJob(playerid)
{
	UnloadVarsPlayerJob(playerid);

    if(AccountData[playerid][pJob] == JOB_BUS)
    {
        LoadVarsBus(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_MINER)
    {
        MinerJobStuffs(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_LUMBERJACK)
    {
        LoadVarsLumber(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_BUTCHER)
    {
        LoadVarsButcher(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_TAILOR)
    {
        LoadVarsTailor(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_OILMAN)
    {
        LoadVarsOilman(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_FISHERMAN)
    {
        LoadVarsFisherman(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_MILKER)
    {
        LoadVarsMilker(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_FARMER)
    {
        LoadVarsFarmer(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_KARGO)
    {
        LoadVarsKargo(playerid);
    }  
    if(AccountData[playerid][pJob] == JOB_RECYCLER)
    {
        LoadVarsDaur(playerid);
    }
    return 1;
}

LoadPlayerJobIcon(playerid)
{
	UnloadVarsPlayerJob(playerid);

    if(AccountData[playerid][pJob] == JOB_BUS)
    {
        LoadVarsBus(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_MINER)
    {
        MinerJobStuffs(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_LUMBERJACK)
    {
        LoadVarsLumber(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_BUTCHER)
    {
        LoadVarsButcher(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_TAILOR)
    {
        LoadVarsTailor(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_OILMAN)
    {
        LoadVarsOilman(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_FISHERMAN)
    {
        LoadVarsFisherman(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_MILKER)
    {
        LoadVarsMilker(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_FARMER)
    {
        LoadVarsFarmer(playerid);
    }
    if(AccountData[playerid][pJob] == JOB_KARGO)
    {
        LoadVarsKargo(playerid);
    }  
    if(AccountData[playerid][pJob] == JOB_RECYCLER)
    {
        LoadVarsDaur(playerid);
    }
    return 1;
}

Float:GetPlayerDistanceFromPlayer(playerid, targetid)
{
    new
        Float:x,
        Float:y,
        Float:z;

    GetPlayerPos(targetid, x, y, z);
    return GetPlayerDistanceFromPoint(playerid, x, y, z);
}

PlayerPlayNearbySound(playerid, sound, forall = 0)
{
    new
        Float:x,
        Float:y,
        Float:z;

    GetPlayerPos(playerid, x, y, z);

    if(forall) return PlayerPlaySound(playerid, sound, x, y, z);

    foreach (new i : Player) if(IsPlayerInRangeOfPoint(i, 20.0, x, y, z)) {
        PlayerPlaySound(i, sound, x, y, z);
    }
    return 1;
}

PlayerHasTazer(playerid)
{
	return (GetPlayerWeapon(playerid) == WEAPON_SILENCED && AccountData[playerid][pDutyPD] && PlayerTaserOn[playerid]);
}

TerminateConnection(playerid)
{
	foreach(new id : Player) if(AccountData[id][pSpec] == playerid && GetPlayerState(id) == PLAYER_STATE_SPECTATING)
    {
        Info(id, "Player %s telah keluar dari server pada saat anda mengawasinya.", ReturnName(playerid));
        callcmd::spec(id, "off");
    }

	foreach(new i : Player) if (AccountData[playerid][pAdmin] > 0 || AccountData[playerid][pTheStars] > 0)
	{
		if(AccountData[i][pAdmin] > 0 || AccountData[i][pTheStars] > 0)
		{
			SendClientMessageEx(i, X11_LIGHTGREY, "[Admin Disconnect] *Admin %s[%d] telah meninggalkan kota District ", AccountData[playerid][pAdminname], playerid);
		}
	}

	foreach(new i : Player) if (ChangeSeatWithPlayerID[i] == playerid)
	{
		ChangeSeatWithPlayerID[i] = INVALID_PLAYER_ID;
		ChangeSeatVehicleID[i] = -1;
	}

	foreach(new i : Player) 
	{
		if(AccountData[i][pLastShot] == playerid) {
			AccountData[i][pLastShot] = INVALID_PLAYER_ID;
		}
		if(AccountData[i][pCarSeller] == playerid) {
			AccountData[i][pCarSeller] = INVALID_PLAYER_ID;
		}
	}

	if(GetPVarType(playerid, "PlacedBB"))
    {
        DestroyDynamicObject(GetPVarInt(playerid, "PlacedBB"));
        DestroyDynamic3DTextLabel(STREAMER_TAG_3D_TEXT_LABEL:GetPVarInt(playerid, "BBLabel"));
        if(GetPVarType(playerid, "BBArea"))
        {
            foreach(new i : Player)
            {
                if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "BBArea")))
                {
                    StopAudioStreamForPlayer(i);
                    Info(i, "Pemilik boombox telah keluar dari server.");
                }
            }
        }
    }

	if(AccountData[playerid][pTaxiPlayer] != INVALID_PLAYER_ID) {
		LeaveTaxi(playerid, AccountData[playerid][pTaxiPlayer]);
	}

	if(AccountData[playerid][pShowFooter]) {
		KillTimer(AccountData[playerid][pFooterTimer]);
	}

	if (AccountData[playerid][pFlashShown]) {
		AccountData[playerid][pFlashShown] = false;
		AccountData[playerid][pFlashOn] = false;
		RemovePlayerAttachedObject(playerid, JOB_SLOT), RemovePlayerAttachedObject(playerid, 5);
	}

	foreach(new i : Player) if (IsPlayerConnected(i))
	{
		if (IsValidDynamicMapIcon(AccountData[i][pFlareIcon][playerid]))
			DestroyDynamicMapIcon(AccountData[i][pFlareIcon][playerid]);
	}
    if(IsValidVehicle(jobs::mixer[playerid][mixerVehicle]))
	{
		DestroyVehicle(jobs::mixer[playerid][mixerVehicle]);
	}
	if (AccountData[playerid][pFlareActive])
	{
		if (IsValidDynamicObject(AccountData[playerid][pFlare]))
			DestroyDynamicObject(AccountData[playerid][pFlare]);
		
		foreach(new i : Player) if (IsPlayerConnected(i))
		{
			if (IsValidDynamicMapIcon(AccountData[playerid][pFlareIcon][i]))
				DestroyDynamicMapIcon(AccountData[playerid][pFlareIcon][i]);
			
			AccountData[playerid][pFlareIcon][i] = INVALID_STREAMER_ID;
		}

		AccountData[playerid][pFlare] = INVALID_STREAMER_ID;
		AccountData[playerid][pFlareActive] = false;
	}

	if (AccountData[playerid][pAdoActive]) {
		if (IsValidDynamic3DTextLabel(AccountData[playerid][pAdoTag]))
			DestroyDynamic3DTextLabel(AccountData[playerid][pAdoTag]);
		
		AccountData[playerid][pAdoTag] = Text3D: INVALID_STREAMER_ID;
		AccountData[playerid][pAdoActive] = false;
	}
	
	UnloadVarsPlayerJob(playerid);
	ResetVariables(playerid);
	ResetNameTag(playerid, false);
	ResetSIDTag(playerid);
	ResetAdminTag(playerid);
	DestroyPlayer3DText(playerid);
	DestroyJobVehicle(playerid);
	return 1;
}

DestroyPlayer3DText(playerid)
{
	if (IsValidDynamic3DTextLabel(AccountData[playerid][pAdoTag]))
		DestroyDynamic3DTextLabel(AccountData[playerid][pAdoTag]);
	
	AccountData[playerid][pAdoTag] 		= Text3D: INVALID_STREAMER_ID;
	AccountData[playerid][pAdoActive]	= false;
	return 1;
}

ResetVariables(playerid)
{
	static const empty_player[E_PLAYERS];
	AccountData[playerid] = empty_player;


	AccountData[playerid][pUCP][0] = EOS;
	AccountData[playerid][pUCP] = EOS;

	for (new i = 0; i < MAX_CHARS; i ++) 
	{
        PlayerChar[playerid][i][0] = EOS;
    }

	for (new i = 0; i < 3; i ++) 
	{
		HouseMemberName[playerid][i][0] = EOS;
	}

	for (new i = 0; i < MAX_PLAYERS; i ++) 
	{
		NearestPlayer[playerid][i] = INVALID_PLAYER_ID;
		ListFixme[playerid][i] = INVALID_PLAYER_ID;
	}

	for(new i = 0; i != MAX_INVENTORY; i ++) if (InventoryData[playerid][i][invExists]) 
	{
		InventoryData[playerid][i][invExists] = false;
		InventoryData[playerid][i][invModel] = 0;
		InventoryData[playerid][i][invQuantity] = 0;
	}
	
	for(new i = 0; i != MAX_CONTACTS; i ++) if (ContactData[playerid][i][contactExists])
	{
		ContactData[playerid][i][contactExists] = false;
		ContactData[playerid][i][contactID] = 0;
		ContactData[playerid][i][contactOwnerID] = -1;
		ContactData[playerid][i][contactUnread] = 0;
		ContactData[playerid][i][contactNumber] = EOS;
		ListedContacts[playerid][i] = -1;
	}

	for(new i = 0; i < 4; i ++)
	{
		pToys[playerid][i][toy_model] = 0;
		pToys[playerid][i][toy_bone] = 0;
		pToys[playerid][i][toy_x] = 0.0;
		pToys[playerid][i][toy_y] = 0.0;
		pToys[playerid][i][toy_z] = 0.0;
		pToys[playerid][i][toy_rx] = 0.0;
		pToys[playerid][i][toy_ry] = 0.0;
		pToys[playerid][i][toy_rz] = 0.0;
		pToys[playerid][i][toy_sx] = 0.0;
		pToys[playerid][i][toy_sy] = 0.0;
		pToys[playerid][i][toy_sz] = 0.0;
	}

	for(new slot = 0; slot < MAX_WEAPON_SLOT; slot++)
    {
        LootWeapons[playerid][slot] = -1;
        LootAmmo[playerid][slot] = 0;
    }
    AccountData[playerid][pTempTarget] = -1;

	AccountData[playerid][pID] = -1;
	AccountData[playerid][pWeapon] = 0;

	for(new i = 0; i < MAX_RUMAH; i++)
	{
   		PlayerHouseList[playerid][i] = -1;
	}
	for(new x; x < 100; x++)
	{
		PlayerListitem[playerid][x] = -1;
	}
	IsPlayerChangeSeat[playerid] = false;
	ChangeSeatWithPlayerID[playerid] = INVALID_PLAYER_ID;
	ChangeSeatVehicleID[playerid] = -1;

	AccountData[playerid][pJobVehicle] = 0;

	ShowWarning[playerid] = false;
	WarningTimer[playerid] = 0;
	g_PlayerRobbery[playerid] = -1;
	Minigame_Locked[playerid] = false;
	pHelmetin[playerid] = false;
	pHiu[playerid] = false;

	LoginAttemps[playerid] = 0;
	LivemodeOn[playerid] = false;
	LivemodeTittle[playerid][0] = EOS;
	IsPlayerSmoking[playerid] = false;
	CountSmoking[playerid] = 0;
	SmokingDelayTime[playerid] = 0;

	PlayerVoting[playerid] = false;
	BagasiLastUse[playerid] = 0;
	BrankasLastUse[playerid] = 0;
	BrankasHouseLastUse[playerid] = 0;
	AccountData[playerid][pInGas] = -1;

	g_PendingTake[playerid] = -1;

	NearestSingle[playerid] = INVALID_PLAYER_ID;
	NearestVehicleID[playerid] = INVALID_VEHICLE_ID;

	AccountData[playerid][pSelectedSlot] = -1;
	pSelectWarungUse[playerid] = -1;
	pUnselectWarungUse[playerid] = -1;

	ShowroomVeh[playerid] = INVALID_VEHICLE_ID;
	ShakehandBy[playerid] = INVALID_PLAYER_ID;
	SignalTimer[playerid] = 0;
	SignalExists[playerid] = false;
	ClickPlayerID[playerid] = -1;
	AccountData[playerid][pFashionItem] = -1;

	pCookingTimer[playerid] = -1;

	AccountData[playerid][pFactDutyTimer] = 0;
	Smoking[playerid] = false;

	pUseItemTimer[playerid] = -1;
	PlayerTaserOn[playerid] = false;

	AccountData[playerid][AirdropPermission] = false;
	AccountData[playerid][pDutyTimer] = -1;
	AccountData[playerid][DokterLokalTimer] = -1;
	AccountData[playerid][RobJewelryTimer] = -1;
	AccountData[playerid][RobbankCashTimer] = -1;
	AccountData[playerid][ToggleFPS] = false;
	AccountData[playerid][pTaxiDuty] = 0;
	AccountData[playerid][pTaxiFee] = 0;
	AccountData[playerid][pTaxiPlayer] = INVALID_PLAYER_ID;
	AccountData[playerid][pTaxiRunDistance] = 0;
	AccountData[playerid][pTaxiOrder] = 0;

	AccountData[playerid][EditingPOMID] = -1;
	AccountData[playerid][EditingDeerID] = -1;
	AccountData[playerid][EditingATMID] = -1;
	AccountData[playerid][EditingLADANGID] = -1;
	AccountData[playerid][EditingUraniumID] = -1;
	AccountData[playerid][EditingROBERID] = -1;
	AccountData[playerid][EditingSAMPAHID] = -1;
	AccountData[playerid][pEditTextObject] = -1;
	AccountData[playerid][pEditSlotID] = -1;
	AccountData[playerid][bEditID] = -1;
	AccountData[playerid][gEditID] = -1;

	AccountData[playerid][playerClickSpawn] = 0;

	AccountData[playerid][phoneCallingWithPlayerID] = INVALID_PLAYER_ID;
	AccountData[playerid][phoneDurringConversation] = false;
	AccountData[playerid][phoneIncomingCall] = false;
	AccountData[playerid][phoneCallingTime] = 0;

	/* Stuffs Storage System */
	RusunBrankas[playerid][rusunbrankasID] = 0;
    RusunBrankas[playerid][rusunbrankasTemp] = EOS;
    RusunBrankas[playerid][rusunbrankasModel] = 0;
    RusunBrankas[playerid][rusunbrankasQuant] = 0;

	VehicleBagasi[playerid][vehiclebagasiID] = 0;
	VehicleBagasi[playerid][vehiclebagasiTemp] = EOS;
	VehicleBagasi[playerid][vehiclebagasiModel] = 0;
	VehicleBagasi[playerid][vehiclebagasiQuant] = 0;

	FactionBrankas[playerid][factionBrankasID] = 0;
    FactionBrankas[playerid][factionBrankasTemp] = EOS;
    FactionBrankas[playerid][factionBrankasModel] = 0;
    FactionBrankas[playerid][factionBrankasQuant] = 0;

	HouseBrankas[playerid][housebrankasID] = 0;
    HouseBrankas[playerid][housebrankasTemp] = EOS;
    HouseBrankas[playerid][housebrankasModel] = 0;
    HouseBrankas[playerid][housebrankasQuant] = 0;

	GudangBrankas[playerid][gudangBrankasID] = 0;
    GudangBrankas[playerid][gudangBrankasTemp] = EOS;
    GudangBrankas[playerid][gudangBrankasModel] = 0;
    GudangBrankas[playerid][gudangBrankasQuant] = 0;
	/* End */
	AccountData[playerid][menuShowed] = false;

	WeaponTick[playerid] = 0;
	WeaponTick[playerid] = 0;
	EditingWeapon[playerid] = 0;

	SetPVarInt(playerid, "FireToggle", 0);

	/* Sweeper Stuffs */
	DurringSweeping[playerid] = false;
	SweeperIndex[playerid] = 0;

	/* Fixme stuffs */
	FixmeExists[playerid] = false;
	FixmeOption[playerid] = -1;
	FixmeTime[playerid] = 0;

	eventJoin[playerid] = 0;
	eventTeams[playerid] = 0;
	eventScore_DM[playerid] = 0;
	SetPVarInt(playerid, "EventTDM", 0);
	Player_ToggleEventAntiCheat(playerid, true);

	AccountData[playerid][CurrentlyReadWA] = false;
	AccountData[playerid][CurrentlyReadTwitter] = false;
	AccountData[playerid][CurrentlyReadYellow] = false;
	AccountData[playerid][pSuspectTimer] = -1;

	// g_ucpActived[playerid] = false;
	AccountData[playerid][pNtagShown] = false;
	AccountData[playerid][pNameTagShown] = false;

	AccountData[playerid][pFlashShown] = false;
	AccountData[playerid][pFlashOn] = false;

	AccountData[playerid][aDutyTimer] = 0;
	ClothesDutyAdmin[playerid] = -1;
	AccountData[playerid][pTempOlah] = -1;
	AccountData[playerid][UsingDoor] = false;
	AccountData[playerid][pTempSQLFactMemberID] = -1;
	AccountData[playerid][pLoadingBar] = -1;
	AccountData[playerid][pInDoor] = -1;
	AccountData[playerid][pInHouse] = -1;
	AccountData[playerid][pInRusun] = -1;
	AccountData[playerid][pInBiz] = -1;
	AccountData[playerid][pInFamily] = -1;
	AccountData[playerid][pFamily] = -1;
	AccountData[playerid][IsLoggedIn] = false;
	AccountData[playerid][pSpawned] = 0;
	AccountData[playerid][PurchasedToy] = false;
	AccountData[playerid][pHealth] = 100.0;
	AccountData[playerid][pArmour] = 0.0;
	AccountData[playerid][pMaskOn] = 0;
	AccountData[playerid][pMaskID] = random(90000) + 10000;
	AccountData[playerid][pSpec] = -1;
	AccountData[playerid][pMechVeh] = INVALID_VEHICLE_ID;
	AccountData[playerid][pDragOffer] = INVALID_PLAYER_ID;
	AccountData[playerid][pDraggedBy] = INVALID_PLAYER_ID;
	IsDragging[playerid] = INVALID_PLAYER_ID;
	AccountData[playerid][pWsInvite] = -1;
	AccountData[playerid][pWsOffer] = -1;
	
	AccountData[playerid][pFlareActive] = false;
	AccountData[playerid][pAdoActive] = false;
	AccountData[playerid][pActionActive] = false;

	AccountData[playerid][pAdoTag] = Text3D: INVALID_STREAMER_ID;

	AccountData[playerid][pCall] = INVALID_PLAYER_ID;
	AccountData[playerid][pCaller] = INVALID_PLAYER_ID;
	
	AccountData[playerid][pCarSeller] = INVALID_PLAYER_ID;
	AccountData[playerid][pCarOffered] = -1;
	AccountData[playerid][pCaller] = INVALID_PLAYER_ID;
	AccountData[playerid][pLastShot] = INVALID_PLAYER_ID;
	AccountData[playerid][pTraceTime] = 0;

	AccountData[playerid][pVehicleFaction] = INVALID_VEHICLE_ID;
	AccountData[playerid][pDealerVeh] = INVALID_VEHICLE_ID;
	AccountData[playerid][pTempVehID] = INVALID_VEHICLE_ID;
	AccountData[playerid][ActivityTime] = 0;
	AccountData[playerid][pListItem] = -1;
	AccountData[playerid][pListItemGudang] = -1;
	AccountData[playerid][pSpeedLimit] = 0;
	AccountData[playerid][pTempValue] = -1;
	AccountData[playerid][pRespawnVehJob] = -1;
	AccountData[playerid][pTimerRespawn] = -1;
	AccountData[playerid][pVehListItem] = -1;
	AccountData[playerid][GarkotVehList] = -1;
	AccountData[playerid][pFacSkin] = -1;
	AccountData[playerid][ClickSpawn] = 0;
	AccountData[playerid][pWAMessage] = 0;
	AccountData[playerid][EngineOn] = 0;
	AccountData[playerid][pTurningEngine] = false;
	AccountData[playerid][pGoodMood] = 0;
	AccountData[playerid][pCheckpoint] = 0;
	AccountData[playerid][pDiPesawat] = false;
	SharelocTimer[playerid] = 0;
	PlayerPressedJump[playerid] = 0;
	TogIsiBensin[playerid] = 0;
	VehicleJobLocked[playerid] = false;
    
	Shakehand[playerid] = false;
	
	AccountData[playerid][pSelectItem] = -1;
	AccountData[playerid][pAmountInv] = 0;
	pPassengerClickMap[playerid] = false;
	pMapCP[playerid] = false;
	
	gPlayerUsingLoopingAnim[playerid] = 0;
	gPlayerAnimLibsPreloaded[playerid] = 0;
	
	format(AccountData[playerid][pTempName], MAX_PLAYER_NAME, "");
	//AntiCheat
	AccountData[playerid][pJetpack] = 0;
	AccountData[playerid][pLastUpdate] = 0;
	AccountData[playerid][pArmorTime] = 0;
	AccountData[playerid][pACTime] = 0;
	//Anim
	AccountData[playerid][pLoopAnim] = 0;
	
	AccountData[playerid][SelectBandara] = 0;
	AccountData[playerid][SelectPelabuhan] = 0;
	AccountData[playerid][SelectRusun] = 0;
	AccountData[playerid][SelectRumah] = 0;
	AccountData[playerid][SelectLastExit] = 0;
	//Toys
    AccountData[playerid][PurchasedToy] = false;
	AccountData[playerid][toySelected] = -1;
	AccountData[playerid][PurchasedToyAxp] = false;
	AccountData[playerid][PurchasedDragonToy] = false;
	AccountData[playerid][PurchasedSonicToy] = false;
	AccountData[playerid][PurchasedGrinchToy] = false;
	AccountData[playerid][PurchasedGhostToy] = false;

	AccountData[playerid][pBeratItem] = 0;
	Player_ToggleEventAntiCheat(playerid, true);
}

/*Streamer Stock*/
stock Streamer_SetPosition(type, STREAMER_ALL_TAGS:id, Float:x, Float:y, Float:z)
{
	Streamer_SetFloatData(type, id, E_STREAMER_X, x);
	Streamer_SetFloatData(type, id, E_STREAMER_Y, y);
	Streamer_SetFloatData(type, id, E_STREAMER_Z, z);
}

stock Streamer_SetRotation(type, STREAMER_ALL_TAGS:id, Float:rx, Float:ry, Float:rz)
{
	Streamer_SetFloatData(type, id, E_STREAMER_R_X, rx);
	Streamer_SetFloatData(type, id, E_STREAMER_R_Y, ry);
	Streamer_SetFloatData(type, id, E_STREAMER_R_Z, rz);
}

/*Other Function*/
stock CheckDrag(playerid)
{
	new targetid = IsDragging[playerid];
	if(targetid != INVALID_PLAYER_ID)
	{
		TogglePlayerControllable(targetid, 1);
		AccountData[targetid][pDraggedBy] = INVALID_PLAYER_ID;
	}
	return 1;
}

stock RemoveDrag(playerid)
{
	foreach(new i : Player) if (IsDragging[i] == playerid)
	{
		IsDragging[i] = INVALID_PLAYER_ID;
		TogglePlayerControllable(i, 1);
		DeletePVar(playerid, "OnCarry");
	}
	return 1;
}

stock HideTDVehicle(playerid)
{
	for(new i; i<14; i++)
	{
		TextDrawHideForPlayer(playerid, Speedo_Index[i]);
	}
	PlayerTextDrawHide(playerid, Speedo_Fuel[playerid]);
	PlayerTextDrawHide(playerid, Speedo_KMH[playerid]);
	PlayerTextDrawHide(playerid, Speedo_Location[playerid]);
	return 1;
}

stock FormatText(text[])
{
	new len = strlen(text);
	if(len > 1)
	{
		for(new i = 0; i < len; i++)
		{
			if(text[i] == 92)
			{
				// New line
			    if(text[i+1] == 'n')
			    {
					text[i] = '\n';
					for(new j = i+1; j < len; j++) text[j] = text[j+1], text[j+1] = 0;
					continue;
			    }

				// Tab
			    if(text[i+1] == 't')
			    {
					text[i] = '\t';
					for(new j = i+1; j < len-1; j++) text[j] = text[j+1], text[j+1] = 0;
					continue;
			    }

				// Literal
			    if(text[i+1] == 92)
			    {
					text[i] = 92;
					for(new j = i+1; j < len-1; j++) text[j] = text[j+1], text[j+1] = 0;
			    }
			}
		}
	}
	return 1;
}

ReturnWorkshopNearestID(slot)
{
	new tmpcount;
	if(slot < 1 && slot > MAX_WORKSHOP) return -1;
	foreach(new id : Workshop)
	{
		if(Iter_Contains(Workshop, id))
		{
	     	tmpcount++;
	       	if(tmpcount == slot)
	       	{
	        	return id;
	  		}
		}
	}
	return -1;
}
GetWorkshopNearest()
{
	new tmpcount;
	foreach(new id : Workshop)
	{
		if(Iter_Contains(Workshop, id))
		{
	     	tmpcount++;
	    }
	}
	return tmpcount;
}

stock ShowHouseTersedia(playerid)
{
    new dialogtext[8192];
    dialogtext[0] = EOS;
    new idx = 0;

    foreach(new houseid : House)
    {
        // ✅ RUMAH TERSEDIA SESUAI SISTEM GM
        if(HouseData[houseid][hsClaimed] == 0)
        {
            new string[256];

            new Float:x = HouseData[houseid][hsExtPos][0];
            new Float:y = HouseData[houseid][hsExtPos][1];
            new Float:z = HouseData[houseid][hsExtPos][2];

            new locationString[64];
            if(x == 0.0 && y == 0.0 && z == 0.0)
                format(locationString, sizeof locationString, "Lokasi Tidak Diketahui");
            else
                format(locationString, sizeof locationString, "%s", GetLocation(x, y, z));

            format(string, sizeof string,
                "[ID: "YELLOW"%d"GRAY"] %s | Type: %s | Harga: "GREEN"%d\n",
                houseid,
                locationString,
                GetTypeHouseName(houseid),
                HouseData[houseid][hsPrice]
            );

            strcat(dialogtext, string);
            PlayerHouseList[playerid][idx++] = houseid;
        }
    }

    if(idx == 0)
    {
        format(dialogtext, sizeof dialogtext, "Tidak ada rumah yang tersedia saat ini!");
        PlayerHouseList[playerid][0] = -1;
    }

    ShowPlayerDialog(playerid, LokasiHouseTersedia, DIALOG_STYLE_LIST, ""TCRP"District  "WHITE"- Rumah Tersedia", dialogtext, "Pilih", "Batal"
    );
    return 1;
}


stock ShowWorkshopLocation(playerid)
{
    if(GetWorkshopNearest() <= 0)
    return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak dapat menemukan workshop dikota.");

    new id, count = GetWorkshopNearest(), mission[2024], lstr[3024], wsstatus[128];

    strcat(mission,"No\tName\tStatus\tDistance\n",sizeof(mission));
    Loop(itt, (count + 1), 1)
    {
        id = ReturnWorkshopNearestID(itt);
        if(wData[id][wStatus] == 1)
        {
            wsstatus = "{FF0000}Closed{FFFFFF}";
        }
        else
        {
            wsstatus = "{00FF00}Opened{FFFFFF}";
        }
        if(itt == count)
        {
            format(lstr,sizeof(lstr), "%d\t%s\t%s\t"YELLOW_E"%0.2fm\n", itt, wData[id][wName], wsstatus, GetPlayerDistanceFromPoint(playerid, wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]));
        }
        else format(lstr,sizeof(lstr), "%d\t%s\t%s\t"YELLOW_E"%0.2fm\n", itt, wData[id][wName], wsstatus, GetPlayerDistanceFromPoint(playerid, wData[id][wExtposX], wData[id][wExtposY], wData[id][wExtposZ]));
        strcat(mission,lstr,sizeof(mission));
    }
    ShowPlayerDialog(playerid, GPS_NEAREST_WORKSHOP, DIALOG_STYLE_TABLIST_HEADERS,"Nearest Workshop",mission,"Select","Cancel");
    return 1;
}

Player_Item(playerid, targetid)
{
	new shstr[1218], itemname[64];
	format(shstr, sizeof(shstr), "Nama Item\tJumlah Item\n");
	for(new i = 0; i < MAX_INVENTORY; i++)
	{
		if(InventoryData[targetid][i][invExists])
		{
			strunpack(itemname, InventoryData[targetid][i][invItem]);
			format(shstr, sizeof(shstr), "%s%s\t%d\n", shstr, itemname, InventoryData[targetid][i][invQuantity]);
		}
		new title[100];
		format(title, sizeof(title), ""TCRP"District  "WHITE"- %s(%d)", ReturnName(targetid), targetid);
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, title, shstr, "Tutup", "");
	}
	return 1;
}

/*Ban_GetLongIP(const ip[])
{
  	new len = strlen(ip);
	if (!(len > 0 && len < 17))
	{
    	return 0;
	}

	new count;
	new pos;
	new dest[3];
	new val[4];
	for (new i; i < len; i++)
	{
		if (ip[i] == '.' || i == len)
		{
			strmid(dest, ip, pos, i);
			pos = (i + 1);

		    val[count] = strval(dest);
		    if (!(0 <= val[count] <= 255))
		    {
		        return 0;
			}

			count++;
			if (count > 3)
			{
				return 0;
			}
		}
	}

	if (count != 3)
	{
	    return 0;
	}
	return ((val[0] * 16777216) + (val[1] * 65536) + (val[2] * 256) + (val[3]));
}*/

ReturnDate(timestamp)
{
	new year, month, day, hour, minute, second;
	TimestampToDate(timestamp, year, month, day, hour, minute, second, 7);

	static monthname[15];
	switch (month)
	{
	    case 1: monthname = "Januari";
	    case 2: monthname = "Februari";
	    case 3: monthname = "Maret";
	    case 4: monthname = "April";
	    case 5: monthname = "Mei";
	    case 6: monthname = "Juni";
	    case 7: monthname = "Juli";
	    case 8: monthname = "Agustus";
	    case 9: monthname = "September";
	    case 10: monthname = "Oktober";
	    case 11: monthname = "November";
	    case 12: monthname = "Desember";
	}

	new date[30];
	format(date, sizeof(date), "%02d %s %d, %02d:%02d:%02d", day, monthname, year, hour, minute, second);
	//format(date, sizeof (date), "%d %s, %d - %d:%d:%d", day, monthname, year, hour, minute, second);
	return date;
}

ReturnDateNoTime(timestamp)
{
	new year, month, day, hour, minute, second;
	TimestampToDate(timestamp, year, month, day, hour, minute, second, 7);

	static monthname[15];
	switch (month)
	{
	    case 1: monthname = "Januari";
	    case 2: monthname = "Februari";
	    case 3: monthname = "Maret";
	    case 4: monthname = "April";
	    case 5: monthname = "Mei";
	    case 6: monthname = "Juni";
	    case 7: monthname = "Juli";
	    case 8: monthname = "Agustus";
	    case 9: monthname = "September";
	    case 10: monthname = "Oktober";
	    case 11: monthname = "November";
	    case 12: monthname = "Desember";
	}

	new date[30];
	format(date, sizeof(date), "%02d/%02d/%d", day, month, year, hour, minute, second);
	//format(date, sizeof (date), "%d %s, %d - %d:%d:%d", day, monthname, year, hour, minute, second);
	return date;
}

ReturnTimelapse(start, till)
{
    new ret[32];
	new second = till - start;

	const
		MINUTE = 60,
		HOUR = 60 * MINUTE,
		DAY = 24 * HOUR,
		MONTH = 30 * DAY;

	if (second == 1)
		format(ret, sizeof(ret), "a Detik");
	if (second < (1 * MINUTE))
		format(ret, sizeof(ret), "%i Detik", second);
	else if (second < (2 * MINUTE))
		format(ret, sizeof(ret), "a Menit");
	else if (second < (45 * MINUTE))
		format(ret, sizeof(ret), "%i Menit", (second / MINUTE));
	else if (second < (90 * MINUTE))
		format(ret, sizeof(ret), "an Jam");
	else if (second < (24 * HOUR))
		format(ret, sizeof(ret), "%i Jam", (second / HOUR));
	else if (second < (48 * HOUR))
		format(ret, sizeof(ret), "a Hari");
	else if (second < (30 * DAY))
		format(ret, sizeof(ret), "%i Hari", (second / DAY));
	else if (second < (12 * MONTH))
    {
		new month = floatround(second / DAY / 30);
      	if (month <= 1)
			format(ret, sizeof(ret), "a Bulan");
      	else
			format(ret, sizeof(ret), "%i Bulan", month);
	}
    else
    {
      	new year = floatround(second / DAY / 365);
      	if (year <= 1)
			format(ret, sizeof(ret), "a Tahun");
      	else
			format(ret, sizeof(ret), "%i Tahun", year);
	}

	return ret;
}

SaveAll()
{
	new time = GetTickCount();

	foreach(new i : PvtVehicles)
	{
		SavePlayerVehicle(i);
	}
	printf("Done save player and rental vehicle data %d ms", GetTickCount() - time);

	foreach(new i : Player) if (IsPlayerConnected(i))
	{
		UpdatePlayerData(i);
	}
	printf("Done save player data %d ms", GetTickCount() - time);
	return 1;
}

GetElapsedTime(time, &hours, &minutes, &seconds)
{
    hours = 0;
    minutes = 0;
    seconds = 0;

    if(time >= 3600) //jika lebih dari 1 jam (3600 = 1 jam)
    {
        hours = (time / 3600); //pembagian waktu per jam di bagi time/3600
        time -= (hours * 3600); //pengurangan di time , ex 2 jam terpakai maka di kalikan 2 * 3600 = time-7200
    }
    while (time >= 60) //hitungan menit.
    {
        minutes++; //hitungan menit bertambah selama time masih bervalue 60.
        time -= 60; // waktu berkurang per menit hitungan 60 sec dari time.
    }
    return (seconds = time);
}

//----------[ Vehicle Native ]---------
IsVehicleEmpty(vehicleid)
{
        for(new i=0; i<MAX_PLAYERS; i++)
        {
                     if(IsPlayerInVehicle(i, vehicleid)) return 0;
        }
        return 1;
}

IsABoat(vehicleid)
{
    switch (GetVehicleModel(vehicleid)) {
        case 430, 446, 452, 453, 454, 472, 473, 484, 493, 595: return 1;
    }
    return 0;
}

IsADealerVehicle(playerid, vehicleid)
{
	vehicleid = GetPlayerVehicleID(playerid);
	if(IsValidVehicle(vehicleid))
	{
		if(vehicleid == ShowroomVeh[playerid])
			return 1;
	}
	return 0;
}
IsABicycle(vehicleid)
{
	switch (GetVehicleModel(vehicleid)) {
		case 509, 481, 510: return 1;
	}
	return 0;
}

IsABike(vehicleid)
{
    switch (GetVehicleModel(vehicleid)) {
        case 448, 461..463, 468, 521..523, 581, 586, 481, 509, 510: return 1;
    }
    return 0;
}

IsAPlane(vehicleid)
{
    switch (GetVehicleModel(vehicleid)) {
        case 460, 464, 476, 511, 512, 513, 519, 520, 553, 577, 592, 593: return 1;
    }
    return 0;
}


/*IsAVehicleStorage(vehicleid)
{
	switch (GetVehicleModel(vehicleid)) {
		case 602, 496, 401, 518, 527, 589, 419, 587, 533, 526, 474, 545, 517, 410, 436,
			439, 549, 491, 445, 507, 585, 466, 492, 546, 551, 516, 467, 426, 547, 405, 
			580, 409, 550, 566, 540, 421, 529, 420, 490, 470, 596, 598, 599, 597, 499,
			609, 498, 414, 459, 482, 418, 413, 440, 579, 400, 404, 489, 505, 479, 442,
			458, 536, 575, 534, 567, 576, 412, 402, 542, 603, 475, 429, 541, 415, 480,
			562, 565, 434, 494, 502, 503, 411, 559, 561, 560, 506, 451, 558, 555, 477,
			483, 525, 504, 422, 438, 554, 428, 424, 495, 535: return 1;
	}
	return 0;
}*/

IsAVehicleStorage(vehicleid)
{
    switch (GetVehicleModel(vehicleid)) {
    case 400, 401, 402, 403, 404, 405, 406, 407, 409, 410, 411, 412, 413, 414, 415, 416,
		417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 432,
		433, 434, 436, 437, 438, 439, 440, 442, 443, 444, 445, 446, 447, 451, 452, 453,
		454, 455, 456, 457, 458, 459, 460, 464, 466, 467, 469, 470, 472,
		474, 475, 476, 477, 478, 479, 480, 482, 483, 484, 487, 488, 489, 490, 491, 492, 493,
		494, 495, 496, 497, 498, 499, 500, 502, 503, 504, 505, 506, 507, 508, 511, 512, 513,
		514, 515, 516, 517, 518, 519, 520, 523, 524, 525, 526, 527, 528, 529, 533,
		534, 535, 536, 537, 538, 540, 541, 542, 543, 544, 545, 546, 547, 548, 549, 550, 551,
		552, 553, 554, 555, 556, 557, 558, 559, 560, 561, 562, 563, 565, 566, 567, 570, 573,
		574, 575, 576, 577, 579, 580, 582, 583, 585, 587, 589, 588, 592, 593, 595,
		596, 597, 598, 599, 600, 601, 602, 603, 604, 605, 609: return 1;
	}	
    return 0;
}

IsAHelicopter(vehicleid)
{
    switch (GetVehicleModel(vehicleid)) {
        case 417, 425, 447, 465, 469, 487, 488, 497, 501, 548, 563: return 1;
    }
    return 0;
}

IsATowTruck(vehicleid)
{
	if(GetVehicleModel(vehicleid) == 485 || GetVehicleModel(vehicleid) == 525 || GetVehicleModel(vehicleid) == 583 || GetVehicleModel(vehicleid) == 574)
	{
		return 1;
	}
	return 0;
}

IsATruck(vehicleid)
{
	switch(GetVehicleModel(vehicleid))
	{
	    case 414, 455, 456, 498, 499, 609: return 1;
	    default: return 0;
	}

	return 0;
}

IsEngineVehicle(vehicleid)
{
    static const g_aEngineStatus[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0
    };
    new modelid = GetVehicleModel(vehicleid);

    if(modelid < 400 || modelid > 611)
        return 0;

    return (g_aEngineStatus[modelid - 400]);
}

IsFourWheelVehicle(vehicleid)
{
    return
        !IsABoat(vehicleid) &&
        !IsABike(vehicleid) &&
        !IsABicycle(vehicleid) &&
        !IsAPlane(vehicleid) &&
        !IsAHelicopter(vehicleid)
    ;
}

GetVehicleMaxSeats(vehicleid)
{
    static const g_arrMaxSeats[] = {
        4, 2, 2, 2, 4, 4, 1, 2, 2, 4, 2, 2, 2, 4, 2, 2, 4, 2, 4, 2, 4, 4, 2, 2, 2, 1, 4, 4, 4, 2,
        1, 7, 1, 2, 2, 0, 2, 7, 4, 2, 4, 1, 2, 2, 2, 4, 1, 2, 1, 0, 0, 2, 1, 1, 1, 2, 2, 2, 4, 4,
        2, 2, 2, 2, 1, 1, 4, 4, 2, 2, 4, 2, 1, 1, 2, 2, 1, 2, 2, 4, 2, 1, 4, 3, 1, 1, 1, 4, 2, 2,
        4, 2, 4, 1, 2, 2, 2, 4, 4, 2, 2, 1, 2, 2, 2, 2, 2, 4, 2, 1, 1, 2, 1, 1, 2, 2, 4, 2, 2, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 1, 1, 2, 2, 2, 2, 7, 7, 1, 4, 2, 2, 2, 2, 2, 4, 4, 2, 2,
        4, 4, 2, 1, 2, 2, 2, 2, 2, 2, 4, 4, 2, 2, 1, 2, 4, 4, 1, 0, 0, 1, 1, 2, 1, 2, 2, 1, 2, 4,
        4, 2, 4, 1, 0, 4, 2, 2, 2, 2, 0, 0, 7, 2, 2, 1, 4, 4, 4, 2, 2, 2, 2, 2, 4, 2, 0, 0, 0, 4,
        0, 0
    };
    new
        model = GetVehicleModel(vehicleid);

    if(400 <= model <= 611)
        return g_arrMaxSeats[model - 400];

    return 0;
}

RemoveFromVehicle(playerid)
{
    if(IsPlayerInAnyVehicle(playerid))
    {
        static
        Float:fX,
        Float:fY,
        Float:fZ;

        GetPlayerPos(playerid, fX, fY, fZ);
        SetPlayerPos(playerid, fX, fY, fZ + 1.5);
    }
    return 1;
}

GetAvailableSeat(vehicleid, start = 1)
{
    new seats = GetVehicleMaxSeats(vehicleid);

    for (new i = start; i < seats; i ++) if(!IsVehicleSeatUsed(vehicleid, i)) {
        return i;
    }
    return -1;
}

IsVehicleSeatUsed(vehicleid, seat)
{
    foreach (new i : Player) if(IsPlayerInVehicle(i, vehicleid) && GetPlayerVehicleSeat(i) == seat) {
        return 1;
    }
    return 0;
}

//Text and Chat
ColouredText(text[])
{
    new
        pos = -1,
        string[144]
    ;
    strmid(string, text, 0, 128, (sizeof(string) - 16));

    while((pos = strfind(string, "#", true, (pos + 1))) != -1)
    {
        new
            i = (pos + 1),
            hexCount
        ;
        for( ; ((string[i] != 0) && (hexCount < 6)); ++i, ++hexCount)
        {
            if(!(('a' <= string[i] <= 'f') || ('A' <= string[i] <= 'F') || ('0' <= string[i] <= '9')))
            {
                         break;
            }
        }
        if((hexCount == 6) && !(hexCount < 6))
        {
            string[pos] = '{';
            strins(string, "}", i);
        }
    }
    return string;
}

SendClientMessageEx(playerid, color, const text[], {Float, _}:...)
{
    static
        args,
            str[265];

    if((args = numargs()) == 3)
    {
            SendClientMessage(playerid, color, text);
    }
    else
    {
        while (--args >= 3)
        {
            #emit LCTRL 5
            #emit LOAD.alt args
            #emit SHL.C.alt 2
            #emit ADD.C 12
            #emit ADD
            #emit LOAD.I
            #emit PUSH.pri
        }
        #emit PUSH.S text
        #emit PUSH.C 144
        #emit PUSH.C str
        #emit PUSH.S 8
        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        SendClientMessage(playerid, color, str);

        #emit RETN
    }
    return 1;
}

/*stock SendClientMessageEx(playerid, colour, const text[], va_args<>)
{
    new str[525];
    va_format(str, sizeof(str), text, va_start<3>);
    return SendClientMessage(playerid, colour, str);
}*/

SendClientMessageToAllEx(color, const text[], {Float, _}:...)
{
    static
        args,
            str[144];

    if((args = numargs()) == 2)
    {
            SendClientMessageToAll(color, text);
    }
    else
    {
        while (--args >= 2)
        {
            #emit LCTRL 5
            #emit LOAD.alt args
            #emit SHL.C.alt 2
            #emit ADD.C 12
            #emit ADD
            #emit LOAD.I
            #emit PUSH.pri
        }
        #emit PUSH.S text
        #emit PUSH.C 144
        #emit PUSH.C str
        #emit LOAD.S.pri 8
        #emit ADD.C 4
        #emit PUSH.pri
        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        SendClientMessageToAll(color, str);

        #emit RETN
    }
    return 1;
}

SendNearbyMessage(playerid, Float:radius, color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 16)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 16); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string

        #emit LOAD.S.pri 8
        #emit CONST.alt 4
        #emit SUB
        #emit PUSH.pri

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player)
        {
            if(NearPlayer(i, playerid, radius)) {
                     SendClientMessage(i, color, string);
            }
        }
        return 1;
    }
    foreach (new i : Player)
    {
        if(NearPlayer(i, playerid, radius)) {
            SendClientMessage(i, color, str);
        }
    }
    return 1;
}

SetPlayerPosition(playerid, Float:X, Float:Y, Float:Z, Float:a, inter = 0)
{
    SetPlayerInterior(playerid, inter);
    SetPlayerPos(playerid, X, Y, Z);
	SetPlayerFacingAngle(playerid, a);
	SetCameraBehindPlayer(playerid);
	//SetPlayerWorldBounds(playerid, 20000, -20000, 20000, -20000);
}

SetVehiclePosition(playerid, vehicleid, Float:X, Float:Y, Float:Z, Float:a, inter = 0)
{
    LinkVehicleToInterior(vehicleid, inter);
    SetVehiclePos(vehicleid, X, Y, Z);
	SetVehicleZAngle(playerid, a);
	SetCameraBehindPlayer(playerid);
	//SetPlayerWorldBounds(playerid, 20000, -20000, 20000, -20000);
}

stock SetPlayerPositionEx(playerid, Float:x, Float:y, Float:z, Float:a, time = 500)
{
	if(AccountData[playerid][pFreeze])
	{
		KillTimer(AccountData[playerid][pFreezeTimer]);
		AccountData[playerid][pFreeze] = 0;
		TogglePlayerControllable(playerid, true);
	}
	// Streamer_ToggleIdleUpdate(playerid, true);
	// GameTextForPlayer(playerid, "MEMUAT OBJECT", time, 4);
	ShowPlayerFooter(playerid, "~y~MEMUAT OBJECT...", time);
	TogglePlayerControllable(playerid, false);
	SetCameraBehindPlayer(playerid);
	AccountData[playerid][pFreeze] = 1;
	SetPlayerPos(playerid, x, y, z + 0.1);
	SetPlayerFacingAngle(playerid, a);
	Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	
	AccountData[playerid][pFreezeTimer] = SetTimerEx("SetPlayerToUnfreeze", time, false, "iffff", playerid, x, y, z, a); //defer SetPlayerToUnfreeze[time](playerid);
	Player_ToggleTelportAntiCheat(playerid, true);
	return 1;
}

forward SetPlayerToUnfreeze(playerid, Float:x, Float:y, Float:z, Float:a);
public SetPlayerToUnfreeze(playerid, Float:x, Float:y, Float:z, Float:a)
{
	Streamer_ToggleIdleUpdate(playerid, false);
	SetPlayerPos(playerid, x, y, z);
	SetPlayerFacingAngle(playerid, a);
	KillTimer(AccountData[playerid][pFreezeTimer]);
	TogglePlayerControllable(playerid, true);
	AccountData[playerid][pFreeze] = 0;
	AccountData[playerid][pFreezeTimer] = -1;
	return 1;
}

ShowGlobalMessage(playerid, string[], time = 6000)
{
	if(g_Message)
	{
		for(new i = 0; i < 7; i ++)
		{
			TextDrawHideForAll(gServerMessage[i]);
			KillTimer(g_MessageTimer);
		}
	}
	TextDrawSetString(gServerMessage[4], string);
	TextDrawSetString(gServerMessage[5], sprintf("Message By: District - %s", AccountData[playerid][pAdminname]));
	for(new i = 0; i < 7; i ++)
	{
		TextDrawShowForAll(gServerMessage[i]);
	}
	g_Message = 1;
	g_MessageTimer = SetTimer("HideGlobalMessage", time, false);
	return 1;
}

forward HideGlobalMessage();
public HideGlobalMessage()
{
	if(!g_Message)
		return 0;
	
	g_Message = 0;
	KillTimer(g_MessageTimer);
	g_MessageTimer = 0;
	for(new i = 0; i < 7; i++) {
		TextDrawHideForAll(gServerMessage[i]);
	}
	return 1;
}

ShowPlayerWarning(playerid, adminid, string[], time = 6000, sound = 0)
{
	if(ShowWarning[playerid]) {
		for(new i = 0; i < 10; i++)
		{
			TextDrawHideForPlayer(playerid, ATRP_Warning[i]);
			KillTimer(WarningTimer[playerid]);
		}
	}
	TextDrawSetString(ATRP_Warning[8], string);
	TextDrawSetString(ATRP_Warning[9], sprintf("Warning by: District - %s", AccountData[adminid][pAdminname]));
	for(new i = 0; i < 10; i++) 
	{
		TextDrawShowForPlayer(playerid, ATRP_Warning[i]);
	}
	ShowWarning[playerid] = true;
	WarningTimer[playerid] = SetTimerEx("HidePlayerWarning", time, false, "d", playerid);

	if(sound) PlayerPlayNearbySound(playerid, 1085, 1);
	return 1;
}

ShowPlayerFooter(playerid, string[], time = 3000, sound = 0)
{
	if(AccountData[playerid][pShowFooter]) {
		PlayerTextDrawHide(playerid, ATRP_Footer[playerid]);
		KillTimer(AccountData[playerid][pFooterTimer]);
	}
	PlayerTextDrawSetString(playerid, ATRP_Footer[playerid], string);
	PlayerTextDrawShow(playerid, ATRP_Footer[playerid]);
	AccountData[playerid][pShowFooter] = true;
	AccountData[playerid][pFooterTimer] = SetTimerEx("HidePlayerFooter", time, false, "d", playerid);

	if(sound) PlayerPlayNearbySound(playerid, 1085, 1);
	return 1;
}

ShowSpectatorInfo(playerid, bool:mode)
{
	if(!mode)
	{
		for(new i = 0; i < 8; i ++) {
			PlayerTextDrawHide(playerid, SpectatorInfoTD[playerid][i]);
		}
	}
	else
	{
		for(new i = 0; i < 8; i ++) {
			PlayerTextDrawShow(playerid, SpectatorInfoTD[playerid][i]);
		}
	}
	return 1;
}

ShowGymTextdraw(playerid, bool:mode)
{
	if(!mode)
	{
		for (new i = 0; i < 3; i ++) PlayerTextDrawHide(playerid, ATRP_Gym[playerid][i]);
	}
	else
	{
		for (new i = 0; i < 3; i ++) PlayerTextDrawShow(playerid, ATRP_Gym[playerid][i]);
	}
	return 1;
}

ShowHbeTextdraws(playerid, mode)
{
	AccountData[playerid][pHUDMode] = mode;

	switch(AccountData[playerid][pHUDMode])
	{
		case 1: // Kiri
		{
			for(new x = 0; x < 15; x ++) PlayerTextDrawHide(playerid, HbeStuffs[playerid][x]);
			ShowHBE(playerid);
			ShowIndexHbe(playerid);
			//for(new x = 0; x < 30; x++) PlayerTextDrawShow(playerid, PipemTD[playerid][x]);
		}
		case 2:
		{
			//for(new x = 0; x < 30; x++) PlayerTextDrawHide(playerid, PipemTD[playerid][x]);
			HideHBE(playerid);
			for(new x = 0; x < 15; x ++) PlayerTextDrawShow(playerid, HbeStuffs[playerid][x]);
		}
	}
	return 1;
}

ShowTDdeathHapp(playerid, bool:Chess7)
{
	if(!Chess7)
	{
		for(new i = 0; i < 55; i++)
		{
			PlayerTextDrawHide(playerid, InjuredAgusSamp[playerid][i]);
		}
	}
	else
	{
		for(new i = 0; i < 55; i++)
		{
			PlayerTextDrawShow(playerid, InjuredAgusSamp[playerid][i]);
		}
	}
	return 1;
}

ShowIndexHbe(playerid)
{
	for(new i = 5; i < 9; i++)
	{
		PlayerTextDrawShow(playerid, PUTRABOTAKHBE[playerid][i]);
	}
	return 1;
}

stock ShowHBE(playerid)
{
	HbeIndex[playerid] = true;
	for(new i = 0; i < 15; i++)
	{
		PlayerTextDrawShow(playerid, PUTRABOTAKHBE[playerid][i]);
	}
	return 1;
}

stock ShowSpedo(playerid)
{
	for(new i = 0; i < 8; i++)
	{
		PlayerTextDrawShow(playerid, SpeedoSimpel[playerid][i]);
	}
	return 1;
}

stock HideHBE(playerid)
{
	HbeIndex[playerid] = false;
	for(new i = 0; i < 15; i++)
	{
		PlayerTextDrawHide(playerid, PUTRABOTAKHBE[playerid][i]);
	}
	return 1;
}

stock HideSpedo(playerid)
{
	for(new i = 0; i < 8; i++)
	{
		PlayerTextDrawHide(playerid, SpeedoSimpel[playerid][i]);
	}
	return 1;
}

stock SpeedVehicle(playerid)
{
	new Float:ST[4];
	if(IsPlayerInAnyVehicle(playerid)) GetVehicleVelocity(GetPlayerVehicleID(playerid),ST[0],ST[1],ST[2]);
	else GetPlayerVelocity(playerid,ST[0],ST[1],ST[2]);

	ST[3] = floatsqroot(floatpower(floatabs(ST[0]), 2.0) + floatpower(floatabs(ST[1]), 2.0) + floatpower(floatabs(ST[2]), 2.0)) * 100.0;
	return floatround(ST[3]);
}

SendPlayerToPlayer(playerid, targetid)
{
    new
        Float:x,
        Float:y,
        Float:z;
		
	if(AccountData[targetid][pSpawned] == 0 || AccountData[playerid][pSpawned] == 0)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Player/Target sedang tidak spawn!");
	
	if(AccountData[playerid][pJail] > 0 || AccountData[targetid][pJail] > 0)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Player/Target sedang di jail");
		
	if(AccountData[playerid][pArrest] > 0 || AccountData[targetid][pArrest] > 0)
		return ShowTDN(playerid, NOTIFICATION_ERROR, "Player/Target sedang di arrest");
		
    GetPlayerPos(targetid, x, y, z);

    if(IsPlayerInAnyVehicle(playerid))
    {
        SetVehiclePos(GetPlayerVehicleID(playerid), x, y + 2, z);
        LinkVehicleToInterior(GetPlayerVehicleID(playerid), GetPlayerInterior(targetid));
    }
    else
    {
        SetPlayerPosition(playerid, x + 1, y, z, 750);
    }
	// Streamer_ToggleIdleUpdate(playerid, 1);
    SetPlayerInterior(playerid, GetPlayerInterior(targetid));
    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));

    AccountData[playerid][pInHouse] = AccountData[targetid][pInHouse];
    AccountData[playerid][pInBiz] = AccountData[targetid][pInBiz];
    AccountData[playerid][pInDoor] = AccountData[targetid][pInDoor];
	AccountData[playerid][pInFamily] = AccountData[targetid][pInFamily];
	AccountData[playerid][pInRusun] = AccountData[targetid][pInRusun];
    return 1;
}

// ProxDetector(Float: f_Radius, playerid, string[],col1,col2,col3,col4,col5) 
// {
// 		new
// 			Float: f_playerPos[3];

// 		GetPlayerPos(playerid, f_playerPos[0], f_playerPos[1], f_playerPos[2]);
// 		foreach(new i : Player) 
// 		{
// 			if(!AccountData[i][pSPY]) 
// 			{
// 				if(GetPlayerVirtualWorld(i) == GetPlayerVirtualWorld(playerid)) 
// 				{
// 					if(IsPlayerInRangeOfPoint(i, f_Radius / 16, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
// 						SendClientMessage(i, col1, string);
// 					}
// 					else if(IsPlayerInRangeOfPoint(i, f_Radius / 8, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
// 						SendClientMessage(i, col2, string);
// 					}
// 					else if(IsPlayerInRangeOfPoint(i, f_Radius / 4, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
// 						SendClientMessage(i, col3, string);
// 					}
// 					else if(IsPlayerInRangeOfPoint(i, f_Radius / 2, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
// 						SendClientMessage(i, col4, string);
// 					}
// 					else if(IsPlayerInRangeOfPoint(i, f_Radius, f_playerPos[0], f_playerPos[1], f_playerPos[2])) {
// 						SendClientMessage(i, col5, string);
// 					}
// 				}
// 			}
// 			else SendClientMessage(i, col1, string);
// 		}
// 		return 1;
// }

IsPlayerNearVehicle(playerid, vehid, Float:radius)
{
	static
        Float:fX,
        Float:fY,
        Float:fZ;

    GetVehiclePos(vehid, fX, fY, fZ);

	return (GetPlayerInterior(playerid) == GetVehicleInterior(vehid) && GetPlayerVirtualWorld(playerid) == GetVehicleVirtualWorld(vehid)) && IsPlayerInRangeOfPoint(playerid, radius, fX, fY, fZ);
}

NearPlayer(playerid, targetid, Float:radius)
{
    static
        Float:fX,
        Float:fY,
        Float:fZ;

    GetPlayerPos(targetid, fX, fY, fZ);

    return (GetPlayerInterior(playerid) == GetPlayerInterior(targetid) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid)) && IsPlayerInRangeOfPoint(playerid, radius, fX, fY, fZ);
}

GetLocation(Float:fX, Float:fY, Float:fZ)
{
    enum e_ZoneData
    {
            e_ZoneName[32 char],
        Float:e_ZoneArea[6]
    };
    static const g_arrZoneData[][e_ZoneData] =
    {
        {!"The Big Ear",                     {-410.00, 1403.30, -3.00, -137.90, 1681.20, 200.00}},
        {!"Aldea Malvada",                     {-1372.10, 2498.50, 0.00, -1277.50, 2615.30, 200.00}},
        {!"Angel Pine",                        {-2324.90, -2584.20, -6.10, -1964.20, -2212.10, 200.00}},
        {!"Arco del Oeste",                    {-901.10, 2221.80, 0.00, -592.00, 2571.90, 200.00}},
        {!"Avispa Country Club",          {-2646.40, -355.40, 0.00, -2270.00, -222.50, 200.00}},
        {!"Avispa Country Club",          {-2831.80, -430.20, -6.10, -2646.40, -222.50, 200.00}},
        {!"Avispa Country Club",          {-2361.50, -417.10, 0.00, -2270.00, -355.40, 200.00}},
        {!"Avispa Country Club",          {-2667.80, -302.10, -28.80, -2646.40, -262.30, 71.10}},
        {!"Avispa Country Club",          {-2470.00, -355.40, 0.00, -2270.00, -318.40, 46.10}},
        {!"Avispa Country Club",          {-2550.00, -355.40, 0.00, -2470.00, -318.40, 39.70}},
        {!"Back o Beyond",                     {-1166.90, -2641.10, 0.00, -321.70, -1856.00, 200.00}},
        {!"Battery Point",                     {-2741.00, 1268.40, -4.50, -2533.00, 1490.40, 200.00}},
        {!"Bayside",                           {-2741.00, 2175.10, 0.00, -2353.10, 2722.70, 200.00}},
        {!"Bayside Marina",                    {-2353.10, 2275.70, 0.00, -2153.10, 2475.70, 200.00}},
        {!"Beacon Hill",                       {-399.60, -1075.50, -1.40, -319.00, -977.50, 198.50}},
        {!"Blackfield",                        {964.30, 1203.20, -89.00, 1197.30, 1403.20, 110.90}},
        {!"Blackfield",                        {964.30, 1403.20, -89.00, 1197.30, 1726.20, 110.90}},
        {!"Blackfield Chapel",            {1375.60, 596.30, -89.00, 1558.00, 823.20, 110.90}},
        {!"Blackfield Chapel",            {1325.60, 596.30, -89.00, 1375.60, 795.00, 110.90}},
        {!"Blackfield Intersection",      {1197.30, 1044.60, -89.00, 1277.00, 1163.30, 110.90}},
        {!"Blackfield Intersection",      {1166.50, 795.00, -89.00, 1375.60, 1044.60, 110.90}},
        {!"Blackfield Intersection",      {1277.00, 1044.60, -89.00, 1315.30, 1087.60, 110.90}},
        {!"Blackfield Intersection",      {1375.60, 823.20, -89.00, 1457.30, 919.40, 110.90}},
        {!"Blueberry",                         {104.50, -220.10, 2.30, 349.60, 152.20, 200.00}},
        {!"Blueberry",                         {19.60, -404.10, 3.80, 349.60, -220.10, 200.00}},
        {!"Blueberry Acres",              {-319.60, -220.10, 0.00, 104.50, 293.30, 200.00}},
        {!"Caligula's Palace",            {2087.30, 1543.20, -89.00, 2437.30, 1703.20, 110.90}},
        {!"Caligula's Palace",            {2137.40, 1703.20, -89.00, 2437.30, 1783.20, 110.90}},
        {!"Calton Heights",                    {-2274.10, 744.10, -6.10, -1982.30, 1358.90, 200.00}},
        {!"Chinatown",                         {-2274.10, 578.30, -7.60, -2078.60, 744.10, 200.00}},
        {!"City Hall",                         {-2867.80, 277.40, -9.10, -2593.40, 458.40, 200.00}},
        {!"Come-A-Lot",                        {2087.30, 943.20, -89.00, 2623.10, 1203.20, 110.90}},
        {!"Commerce",                          {1323.90, -1842.20, -89.00, 1701.90, -1722.20, 110.90}},
        {!"Commerce",                          {1323.90, -1722.20, -89.00, 1440.90, -1577.50, 110.90}},
        {!"Commerce",                          {1370.80, -1577.50, -89.00, 1463.90, -1384.90, 110.90}},
        {!"Commerce",                          {1463.90, -1577.50, -89.00, 1667.90, -1430.80, 110.90}},
        {!"Commerce",                          {1583.50, -1722.20, -89.00, 1758.90, -1577.50, 110.90}},
        {!"Commerce",                          {1667.90, -1577.50, -89.00, 1812.60, -1430.80, 110.90}},
        {!"Conference Center",            {1046.10, -1804.20, -89.00, 1323.90, -1722.20, 110.90}},
        {!"Conference Center",            {1073.20, -1842.20, -89.00, 1323.90, -1804.20, 110.90}},
        {!"Cranberry Station",            {-2007.80, 56.30, 0.00, -1922.00, 224.70, 100.00}},
        {!"Creek",                             {2749.90, 1937.20, -89.00, 2921.60, 2669.70, 110.90}},
        {!"Dillimore",                         {580.70, -674.80, -9.50, 861.00, -404.70, 200.00}},
        {!"Doherty",                           {-2270.00, -324.10, -0.00, -1794.90, -222.50, 200.00}},
        {!"Doherty",                           {-2173.00, -222.50, -0.00, -1794.90, 265.20, 200.00}},
        {!"Downtown",                          {-1982.30, 744.10, -6.10, -1871.70, 1274.20, 200.00}},
        {!"Downtown",                          {-1871.70, 1176.40, -4.50, -1620.30, 1274.20, 200.00}},
        {!"Downtown",                          {-1700.00, 744.20, -6.10, -1580.00, 1176.50, 200.00}},
        {!"Downtown",                          {-1580.00, 744.20, -6.10, -1499.80, 1025.90, 200.00}},
        {!"Downtown",                          {-2078.60, 578.30, -7.60, -1499.80, 744.20, 200.00}},
        {!"Downtown",                          {-1993.20, 265.20, -9.10, -1794.90, 578.30, 200.00}},
        {!"Downtown Los Santos",          {1463.90, -1430.80, -89.00, 1724.70, -1290.80, 110.90}},
        {!"Downtown Los Santos",          {1724.70, -1430.80, -89.00, 1812.60, -1250.90, 110.90}},
        {!"Downtown Los Santos",          {1463.90, -1290.80, -89.00, 1724.70, -1150.80, 110.90}},
        {!"Downtown Los Santos",          {1370.80, -1384.90, -89.00, 1463.90, -1170.80, 110.90}},
        {!"Downtown Los Santos",          {1724.70, -1250.90, -89.00, 1812.60, -1150.80, 110.90}},
        {!"Downtown Los Santos",          {1370.80, -1170.80, -89.00, 1463.90, -1130.80, 110.90}},
        {!"Downtown Los Santos",          {1378.30, -1130.80, -89.00, 1463.90, -1026.30, 110.90}},
        {!"Downtown Los Santos",          {1391.00, -1026.30, -89.00, 1463.90, -926.90, 110.90}},
        {!"Downtown Los Santos",          {1507.50, -1385.20, 110.90, 1582.50, -1325.30, 335.90}},
        {!"East Beach",                        {2632.80, -1852.80, -89.00, 2959.30, -1668.10, 110.90}},
        {!"East Beach",                        {2632.80, -1668.10, -89.00, 2747.70, -1393.40, 110.90}},
        {!"East Beach",                        {2747.70, -1668.10, -89.00, 2959.30, -1498.60, 110.90}},
        {!"East Beach",                        {2747.70, -1498.60, -89.00, 2959.30, -1120.00, 110.90}},
        {!"East Los Santos",              {2421.00, -1628.50, -89.00, 2632.80, -1454.30, 110.90}},
        {!"East Los Santos",              {2222.50, -1628.50, -89.00, 2421.00, -1494.00, 110.90}},
        {!"East Los Santos",              {2266.20, -1494.00, -89.00, 2381.60, -1372.00, 110.90}},
        {!"East Los Santos",              {2381.60, -1494.00, -89.00, 2421.00, -1454.30, 110.90}},
        {!"East Los Santos",              {2281.40, -1372.00, -89.00, 2381.60, -1135.00, 110.90}},
        {!"East Los Santos",              {2381.60, -1454.30, -89.00, 2462.10, -1135.00, 110.90}},
        {!"East Los Santos",              {2462.10, -1454.30, -89.00, 2581.70, -1135.00, 110.90}},
        {!"Easter Basin",                      {-1794.90, 249.90, -9.10, -1242.90, 578.30, 200.00}},
        {!"Easter Basin",                      {-1794.90, -50.00, -0.00, -1499.80, 249.90, 200.00}},
        {!"Easter Bay Airport",           {-1499.80, -50.00, -0.00, -1242.90, 249.90, 200.00}},
        {!"Easter Bay Airport",           {-1794.90, -730.10, -3.00, -1213.90, -50.00, 200.00}},
        {!"Easter Bay Airport",           {-1213.90, -730.10, 0.00, -1132.80, -50.00, 200.00}},
        {!"Easter Bay Airport",           {-1242.90, -50.00, 0.00, -1213.90, 578.30, 200.00}},
        {!"Easter Bay Airport",           {-1213.90, -50.00, -4.50, -947.90, 578.30, 200.00}},
        {!"Easter Bay Airport",           {-1315.40, -405.30, 15.40, -1264.40, -209.50, 25.40}},
        {!"Easter Bay Airport",           {-1354.30, -287.30, 15.40, -1315.40, -209.50, 25.40}},
        {!"Easter Bay Airport",           {-1490.30, -209.50, 15.40, -1264.40, -148.30, 25.40}},
        {!"Easter Bay Chemicals",         {-1132.80, -768.00, 0.00, -956.40, -578.10, 200.00}},
        {!"Easter Bay Chemicals",         {-1132.80, -787.30, 0.00, -956.40, -768.00, 200.00}},
        {!"El Castillo del Diablo",       {-464.50, 2217.60, 0.00, -208.50, 2580.30, 200.00}},
        {!"El Castillo del Diablo",       {-208.50, 2123.00, -7.60, 114.00, 2337.10, 200.00}},
        {!"El Castillo del Diablo",       {-208.50, 2337.10, 0.00, 8.40, 2487.10, 200.00}},
        {!"El Corona",                         {1812.60, -2179.20, -89.00, 1970.60, -1852.80, 110.90}},
        {!"El Corona",                         {1692.60, -2179.20, -89.00, 1812.60, -1842.20, 110.90}},
        {!"El Quebrados",                      {-1645.20, 2498.50, 0.00, -1372.10, 2777.80, 200.00}},
        {!"Esplanade East",                    {-1620.30, 1176.50, -4.50, -1580.00, 1274.20, 200.00}},
        {!"Esplanade East",                    {-1580.00, 1025.90, -6.10, -1499.80, 1274.20, 200.00}},
        {!"Esplanade East",                    {-1499.80, 578.30, -79.60, -1339.80, 1274.20, 20.30}},
        {!"Esplanade North",              {-2533.00, 1358.90, -4.50, -1996.60, 1501.20, 200.00}},
        {!"Esplanade North",              {-1996.60, 1358.90, -4.50, -1524.20, 1592.50, 200.00}},
        {!"Esplanade North",              {-1982.30, 1274.20, -4.50, -1524.20, 1358.90, 200.00}},
        {!"Fallen Tree",                       {-792.20, -698.50, -5.30, -452.40, -380.00, 200.00}},
        {!"Fallow Bridge",                     {434.30, 366.50, 0.00, 603.00, 555.60, 200.00}},
        {!"Fern Ridge",                        {508.10, -139.20, 0.00, 1306.60, 119.50, 200.00}},
        {!"Financial",                         {-1871.70, 744.10, -6.10, -1701.30, 1176.40, 300.00}},
        {!"Fisher's Lagoon",              {1916.90, -233.30, -100.00, 2131.70, 13.80, 200.00}},
        {!"Flint Intersection",           {-187.70, -1596.70, -89.00, 17.00, -1276.60, 110.90}},
        {!"Flint Range",                       {-594.10, -1648.50, 0.00, -187.70, -1276.60, 200.00}},
        {!"Fort Carson",                       {-376.20, 826.30, -3.00, 123.70, 1220.40, 200.00}},
        {!"Foster Valley",                     {-2270.00, -430.20, -0.00, -2178.60, -324.10, 200.00}},
        {!"Foster Valley",                     {-2178.60, -599.80, -0.00, -1794.90, -324.10, 200.00}},
        {!"Foster Valley",                     {-2178.60, -1115.50, 0.00, -1794.90, -599.80, 200.00}},
        {!"Foster Valley",                     {-2178.60, -1250.90, 0.00, -1794.90, -1115.50, 200.00}},
        {!"Frederick Bridge",             {2759.20, 296.50, 0.00, 2774.20, 594.70, 200.00}},
        {!"Gant Bridge",                       {-2741.40, 1659.60, -6.10, -2616.40, 2175.10, 200.00}},
        {!"Gant Bridge",                       {-2741.00, 1490.40, -6.10, -2616.40, 1659.60, 200.00}},
        {!"Ganton",                            {2222.50, -1852.80, -89.00, 2632.80, -1722.30, 110.90}},
        {!"Ganton",                            {2222.50, -1722.30, -89.00, 2632.80, -1628.50, 110.90}},
        {!"Garcia",                            {-2411.20, -222.50, -0.00, -2173.00, 265.20, 200.00}},
        {!"Garcia",                            {-2395.10, -222.50, -5.30, -2354.00, -204.70, 200.00}},
        {!"Garver Bridge",                     {-1339.80, 828.10, -89.00, -1213.90, 1057.00, 110.90}},
        {!"Garver Bridge",                     {-1213.90, 950.00, -89.00, -1087.90, 1178.90, 110.90}},
        {!"Garver Bridge",                     {-1499.80, 696.40, -179.60, -1339.80, 925.30, 20.30}},
        {!"Glen Park",                         {1812.60, -1449.60, -89.00, 1996.90, -1350.70, 110.90}},
        {!"Glen Park",                         {1812.60, -1100.80, -89.00, 1994.30, -973.30, 110.90}},
        {!"Glen Park",                         {1812.60, -1350.70, -89.00, 2056.80, -1100.80, 110.90}},
        {!"Green Palms",                       {176.50, 1305.40, -3.00, 338.60, 1520.70, 200.00}},
        {!"Greenglass College",           {964.30, 1044.60, -89.00, 1197.30, 1203.20, 110.90}},
        {!"Greenglass College",           {964.30, 930.80, -89.00, 1166.50, 1044.60, 110.90}},
        {!"Hampton Barns",                     {603.00, 264.30, 0.00, 761.90, 366.50, 200.00}},
        {!"Hankypanky Point",             {2576.90, 62.10, 0.00, 2759.20, 385.50, 200.00}},
        {!"Harry Gold Parkway",           {1777.30, 863.20, -89.00, 1817.30, 2342.80, 110.90}},
        {!"Hashbury",                          {-2593.40, -222.50, -0.00, -2411.20, 54.70, 200.00}},
        {!"Hilltop Farm",                      {967.30, -450.30, -3.00, 1176.70, -217.90, 200.00}},
        {!"Hunter Quarry",                     {337.20, 710.80, -115.20, 860.50, 1031.70, 203.70}},
        {!"Idlewood",                          {1812.60, -1852.80, -89.00, 1971.60, -1742.30, 110.90}},
        {!"Idlewood",                          {1812.60, -1742.30, -89.00, 1951.60, -1602.30, 110.90}},
        {!"Idlewood",                          {1951.60, -1742.30, -89.00, 2124.60, -1602.30, 110.90}},
        {!"Idlewood",                          {1812.60, -1602.30, -89.00, 2124.60, -1449.60, 110.90}},
        {!"Idlewood",                          {2124.60, -1742.30, -89.00, 2222.50, -1494.00, 110.90}},
        {!"Idlewood",                          {1971.60, -1852.80, -89.00, 2222.50, -1742.30, 110.90}},
        {!"Jefferson",                         {1996.90, -1449.60, -89.00, 2056.80, -1350.70, 110.90}},
        {!"Jefferson",                         {2124.60, -1494.00, -89.00, 2266.20, -1449.60, 110.90}},
        {!"Jefferson",                         {2056.80, -1372.00, -89.00, 2281.40, -1210.70, 110.90}},
        {!"Jefferson",                         {2056.80, -1210.70, -89.00, 2185.30, -1126.30, 110.90}},
        {!"Jefferson",                         {2185.30, -1210.70, -89.00, 2281.40, -1154.50, 110.90}},
        {!"Jefferson",                         {2056.80, -1449.60, -89.00, 2266.20, -1372.00, 110.90}},
        {!"Julius Thruway East",          {2623.10, 943.20, -89.00, 2749.90, 1055.90, 110.90}},
        {!"Julius Thruway East",          {2685.10, 1055.90, -89.00, 2749.90, 2626.50, 110.90}},
        {!"Julius Thruway East",          {2536.40, 2442.50, -89.00, 2685.10, 2542.50, 110.90}},
        {!"Julius Thruway East",          {2625.10, 2202.70, -89.00, 2685.10, 2442.50, 110.90}},
        {!"Julius Thruway North",         {2498.20, 2542.50, -89.00, 2685.10, 2626.50, 110.90}},
        {!"Julius Thruway North",         {2237.40, 2542.50, -89.00, 2498.20, 2663.10, 110.90}},
        {!"Julius Thruway North",         {2121.40, 2508.20, -89.00, 2237.40, 2663.10, 110.90}},
        {!"Julius Thruway North",         {1938.80, 2508.20, -89.00, 2121.40, 2624.20, 110.90}},
        {!"Julius Thruway North",         {1534.50, 2433.20, -89.00, 1848.40, 2583.20, 110.90}},
        {!"Julius Thruway North",         {1848.40, 2478.40, -89.00, 1938.80, 2553.40, 110.90}},
        {!"Julius Thruway North",         {1704.50, 2342.80, -89.00, 1848.40, 2433.20, 110.90}},
        {!"Julius Thruway North",         {1377.30, 2433.20, -89.00, 1534.50, 2507.20, 110.90}},
        {!"Julius Thruway South",         {1457.30, 823.20, -89.00, 2377.30, 863.20, 110.90}},
        {!"Julius Thruway South",         {2377.30, 788.80, -89.00, 2537.30, 897.90, 110.90}},
        {!"Julius Thruway West",          {1197.30, 1163.30, -89.00, 1236.60, 2243.20, 110.90}},
        {!"Julius Thruway West",          {1236.60, 2142.80, -89.00, 1297.40, 2243.20, 110.90}},
        {!"Juniper Hill",                      {-2533.00, 578.30, -7.60, -2274.10, 968.30, 200.00}},
        {!"Juniper Hollow",                    {-2533.00, 968.30, -6.10, -2274.10, 1358.90, 200.00}},
        {!"K.A.C.C. Military Fuels",      {2498.20, 2626.50, -89.00, 2749.90, 2861.50, 110.90}},
        {!"Kincaid Bridge",                    {-1339.80, 599.20, -89.00, -1213.90, 828.10, 110.90}},
        {!"Kincaid Bridge",                    {-1213.90, 721.10, -89.00, -1087.90, 950.00, 110.90}},
        {!"Kincaid Bridge",                    {-1087.90, 855.30, -89.00, -961.90, 986.20, 110.90}},
        {!"King's",                            {-2329.30, 458.40, -7.60, -1993.20, 578.30, 200.00}},
        {!"King's",                            {-2411.20, 265.20, -9.10, -1993.20, 373.50, 200.00}},
        {!"King's",                            {-2253.50, 373.50, -9.10, -1993.20, 458.40, 200.00}},
        {!"LVA Freight Depot",            {1457.30, 863.20, -89.00, 1777.40, 1143.20, 110.90}},
        {!"LVA Freight Depot",            {1375.60, 919.40, -89.00, 1457.30, 1203.20, 110.90}},
        {!"LVA Freight Depot",            {1277.00, 1087.60, -89.00, 1375.60, 1203.20, 110.90}},
        {!"LVA Freight Depot",            {1315.30, 1044.60, -89.00, 1375.60, 1087.60, 110.90}},
        {!"LVA Freight Depot",            {1236.60, 1163.40, -89.00, 1277.00, 1203.20, 110.90}},
        {!"Las Barrancas",                     {-926.10, 1398.70, -3.00, -719.20, 1634.60, 200.00}},
        {!"Las Brujas",                        {-365.10, 2123.00, -3.00, -208.50, 2217.60, 200.00}},
        {!"Las Colinas",                       {1994.30, -1100.80, -89.00, 2056.80, -920.80, 110.90}},
        {!"Las Colinas",                       {2056.80, -1126.30, -89.00, 2126.80, -920.80, 110.90}},
        {!"Las Colinas",                       {2185.30, -1154.50, -89.00, 2281.40, -934.40, 110.90}},
        {!"Las Colinas",                       {2126.80, -1126.30, -89.00, 2185.30, -934.40, 110.90}},
        {!"Las Colinas",                       {2747.70, -1120.00, -89.00, 2959.30, -945.00, 110.90}},
        {!"Las Colinas",                       {2632.70, -1135.00, -89.00, 2747.70, -945.00, 110.90}},
        {!"Las Colinas",                       {2281.40, -1135.00, -89.00, 2632.70, -945.00, 110.90}},
        {!"Las Payasadas",                     {-354.30, 2580.30, 2.00, -133.60, 2816.80, 200.00}},
        {!"Las Venturas Airport",         {1236.60, 1203.20, -89.00, 1457.30, 1883.10, 110.90}},
        {!"Las Venturas Airport",         {1457.30, 1203.20, -89.00, 1777.30, 1883.10, 110.90}},
        {!"Las Venturas Airport",         {1457.30, 1143.20, -89.00, 1777.40, 1203.20, 110.90}},
        {!"Las Venturas Airport",         {1515.80, 1586.40, -12.50, 1729.90, 1714.50, 87.50}},
        {!"Last Dime Motel",              {1823.00, 596.30, -89.00, 1997.20, 823.20, 110.90}},
        {!"Leafy Hollow",                      {-1166.90, -1856.00, 0.00, -815.60, -1602.00, 200.00}},
        {!"Liberty City",                      {-1000.00, 400.00, 1300.00, -700.00, 600.00, 1400.00}},
        {!"Lil' Probe Inn",                    {-90.20, 1286.80, -3.00, 153.80, 1554.10, 200.00}},
        {!"Linden Side",                       {2749.90, 943.20, -89.00, 2923.30, 1198.90, 110.90}},
        {!"Linden Station",                    {2749.90, 1198.90, -89.00, 2923.30, 1548.90, 110.90}},
        {!"Linden Station",                    {2811.20, 1229.50, -39.50, 2861.20, 1407.50, 60.40}},
        {!"Little Mexico",                     {1701.90, -1842.20, -89.00, 1812.60, -1722.20, 110.90}},
        {!"Little Mexico",                     {1758.90, -1722.20, -89.00, 1812.60, -1577.50, 110.90}},
        {!"Los Flores",                        {2581.70, -1454.30, -89.00, 2632.80, -1393.40, 110.90}},
        {!"Los Flores",                        {2581.70, -1393.40, -89.00, 2747.70, -1135.00, 110.90}},
        {!"Los Santos International",     {1249.60, -2394.30, -89.00, 1852.00, -2179.20, 110.90}},
        {!"Los Santos International",     {1852.00, -2394.30, -89.00, 2089.00, -2179.20, 110.90}},
        {!"Los Santos International",     {1382.70, -2730.80, -89.00, 2201.80, -2394.30, 110.90}},
        {!"Los Santos International",     {1974.60, -2394.30, -39.00, 2089.00, -2256.50, 60.90}},
        {!"Los Santos International",     {1400.90, -2669.20, -39.00, 2189.80, -2597.20, 60.90}},
        {!"Los Santos International",     {2051.60, -2597.20, -39.00, 2152.40, -2394.30, 60.90}},
        {!"Marina",                            {647.70, -1804.20, -89.00, 851.40, -1577.50, 110.90}},
        {!"Marina",                            {647.70, -1577.50, -89.00, 807.90, -1416.20, 110.90}},
        {!"Marina",                            {807.90, -1577.50, -89.00, 926.90, -1416.20, 110.90}},
        {!"Market",                            {787.40, -1416.20, -89.00, 1072.60, -1310.20, 110.90}},
        {!"Market",                            {952.60, -1310.20, -89.00, 1072.60, -1130.80, 110.90}},
        {!"Market",                            {1072.60, -1416.20, -89.00, 1370.80, -1130.80, 110.90}},
        {!"Market",                            {926.90, -1577.50, -89.00, 1370.80, -1416.20, 110.90}},
        {!"Market Station",                    {787.40, -1410.90, -34.10, 866.00, -1310.20, 65.80}},
        {!"Martin Bridge",                     {-222.10, 293.30, 0.00, -122.10, 476.40, 200.00}},
        {!"Missionary Hill",              {-2994.40, -811.20, 0.00, -2178.60, -430.20, 200.00}},
        {!"Montgomery",                        {1119.50, 119.50, -3.00, 1451.40, 493.30, 200.00}},
        {!"Montgomery",                        {1451.40, 347.40, -6.10, 1582.40, 420.80, 200.00}},
        {!"Montgomery Intersection",      {1546.60, 208.10, 0.00, 1745.80, 347.40, 200.00}},
        {!"Montgomery Intersection",      {1582.40, 347.40, 0.00, 1664.60, 401.70, 200.00}},
        {!"Mulholland",                        {1414.00, -768.00, -89.00, 1667.60, -452.40, 110.90}},
        {!"Mulholland",                        {1281.10, -452.40, -89.00, 1641.10, -290.90, 110.90}},
        {!"Mulholland",                        {1269.10, -768.00, -89.00, 1414.00, -452.40, 110.90}},
        {!"Mulholland",                        {1357.00, -926.90, -89.00, 1463.90, -768.00, 110.90}},
        {!"Mulholland",                        {1318.10, -910.10, -89.00, 1357.00, -768.00, 110.90}},
        {!"Mulholland",                        {1169.10, -910.10, -89.00, 1318.10, -768.00, 110.90}},
        {!"Mulholland",                        {768.60, -954.60, -89.00, 952.60, -860.60, 110.90}},
        {!"Mulholland",                        {687.80, -860.60, -89.00, 911.80, -768.00, 110.90}},
        {!"Mulholland",                        {737.50, -768.00, -89.00, 1142.20, -674.80, 110.90}},
        {!"Mulholland",                        {1096.40, -910.10, -89.00, 1169.10, -768.00, 110.90}},
        {!"Mulholland",                        {952.60, -937.10, -89.00, 1096.40, -860.60, 110.90}},
        {!"Mulholland",                        {911.80, -860.60, -89.00, 1096.40, -768.00, 110.90}},
        {!"Mulholland",                        {861.00, -674.80, -89.00, 1156.50, -600.80, 110.90}},
        {!"Mulholland Intersection",      {1463.90, -1150.80, -89.00, 1812.60, -768.00, 110.90}},
        {!"North Rock",                        {2285.30, -768.00, 0.00, 2770.50, -269.70, 200.00}},
        {!"Ocean Docks",                       {2373.70, -2697.00, -89.00, 2809.20, -2330.40, 110.90}},
        {!"Ocean Docks",                       {2201.80, -2418.30, -89.00, 2324.00, -2095.00, 110.90}},
        {!"Ocean Docks",                       {2324.00, -2302.30, -89.00, 2703.50, -2145.10, 110.90}},
        {!"Ocean Docks",                       {2089.00, -2394.30, -89.00, 2201.80, -2235.80, 110.90}},
        {!"Ocean Docks",                       {2201.80, -2730.80, -89.00, 2324.00, -2418.30, 110.90}},
        {!"Ocean Docks",                       {2703.50, -2302.30, -89.00, 2959.30, -2126.90, 110.90}},
        {!"Ocean Docks",                       {2324.00, -2145.10, -89.00, 2703.50, -2059.20, 110.90}},
        {!"Ocean Flats",                       {-2994.40, 277.40, -9.10, -2867.80, 458.40, 200.00}},
        {!"Ocean Flats",                       {-2994.40, -222.50, -0.00, -2593.40, 277.40, 200.00}},
        {!"Ocean Flats",                       {-2994.40, -430.20, -0.00, -2831.80, -222.50, 200.00}},
        {!"Octane Springs",                    {338.60, 1228.50, 0.00, 664.30, 1655.00, 200.00}},
        {!"Old Venturas Strip",           {2162.30, 2012.10, -89.00, 2685.10, 2202.70, 110.90}},
        {!"Palisades",                         {-2994.40, 458.40, -6.10, -2741.00, 1339.60, 200.00}},
        {!"Palomino Creek",                    {2160.20, -149.00, 0.00, 2576.90, 228.30, 200.00}},
        {!"Paradiso",                          {-2741.00, 793.40, -6.10, -2533.00, 1268.40, 200.00}},
        {!"Pershing Square",              {1440.90, -1722.20, -89.00, 1583.50, -1577.50, 110.90}},
        {!"Pilgrim",                           {2437.30, 1383.20, -89.00, 2624.40, 1783.20, 110.90}},
        {!"Pilgrim",                           {2624.40, 1383.20, -89.00, 2685.10, 1783.20, 110.90}},
        {!"Pilson Intersection",          {1098.30, 2243.20, -89.00, 1377.30, 2507.20, 110.90}},
        {!"Pirates in Men's Pants",       {1817.30, 1469.20, -89.00, 2027.40, 1703.20, 110.90}},
        {!"Playa del Seville",            {2703.50, -2126.90, -89.00, 2959.30, -1852.80, 110.90}},
        {!"Prickle Pine",                      {1534.50, 2583.20, -89.00, 1848.40, 2863.20, 110.90}},
        {!"Prickle Pine",                      {1117.40, 2507.20, -89.00, 1534.50, 2723.20, 110.90}},
        {!"Prickle Pine",                      {1848.40, 2553.40, -89.00, 1938.80, 2863.20, 110.90}},
        {!"Prickle Pine",                      {1938.80, 2624.20, -89.00, 2121.40, 2861.50, 110.90}},
        {!"Queens",                            {-2533.00, 458.40, 0.00, -2329.30, 578.30, 200.00}},
        {!"Queens",                            {-2593.40, 54.70, 0.00, -2411.20, 458.40, 200.00}},
        {!"Queens",                            {-2411.20, 373.50, 0.00, -2253.50, 458.40, 200.00}},
        {!"Randolph Industrial Estate",   {1558.00, 596.30, -89.00, 1823.00, 823.20, 110.90}},
        {!"Redsands East",                     {1817.30, 2011.80, -89.00, 2106.70, 2202.70, 110.90}},
        {!"Redsands East",                     {1817.30, 2202.70, -89.00, 2011.90, 2342.80, 110.90}},
        {!"Redsands East",                     {1848.40, 2342.80, -89.00, 2011.90, 2478.40, 110.90}},
        {!"Redsands West",                     {1236.60, 1883.10, -89.00, 1777.30, 2142.80, 110.90}},
        {!"Redsands West",                     {1297.40, 2142.80, -89.00, 1777.30, 2243.20, 110.90}},
        {!"Redsands West",                     {1377.30, 2243.20, -89.00, 1704.50, 2433.20, 110.90}},
        {!"Redsands West",                     {1704.50, 2243.20, -89.00, 1777.30, 2342.80, 110.90}},
        {!"Regular Tom",                       {-405.70, 1712.80, -3.00, -276.70, 1892.70, 200.00}},
        {!"Richman",                           {647.50, -1118.20, -89.00, 787.40, -954.60, 110.90}},
        {!"Richman",                           {647.50, -954.60, -89.00, 768.60, -860.60, 110.90}},
        {!"Richman",                           {225.10, -1369.60, -89.00, 334.50, -1292.00, 110.90}},
        {!"Richman",                           {225.10, -1292.00, -89.00, 466.20, -1235.00, 110.90}},
        {!"Richman",                           {72.60, -1404.90, -89.00, 225.10, -1235.00, 110.90}},
        {!"Richman",                           {72.60, -1235.00, -89.00, 321.30, -1008.10, 110.90}},
        {!"Richman",                           {321.30, -1235.00, -89.00, 647.50, -1044.00, 110.90}},
        {!"Richman",                           {321.30, -1044.00, -89.00, 647.50, -860.60, 110.90}},
        {!"Richman",                           {321.30, -860.60, -89.00, 687.80, -768.00, 110.90}},
        {!"Richman",                           {321.30, -768.00, -89.00, 700.70, -674.80, 110.90}},
        {!"Robada Intersection",          {-1119.00, 1178.90, -89.00, -862.00, 1351.40, 110.90}},
        {!"Roca Escalante",                    {2237.40, 2202.70, -89.00, 2536.40, 2542.50, 110.90}},
        {!"Roca Escalante",                    {2536.40, 2202.70, -89.00, 2625.10, 2442.50, 110.90}},
        {!"Rockshore East",                    {2537.30, 676.50, -89.00, 2902.30, 943.20, 110.90}},
        {!"Rockshore West",                    {1997.20, 596.30, -89.00, 2377.30, 823.20, 110.90}},
        {!"Rockshore West",                    {2377.30, 596.30, -89.00, 2537.30, 788.80, 110.90}},
        {!"Rodeo",                             {72.60, -1684.60, -89.00, 225.10, -1544.10, 110.90}},
        {!"Rodeo",                             {72.60, -1544.10, -89.00, 225.10, -1404.90, 110.90}},
        {!"Rodeo",                             {225.10, -1684.60, -89.00, 312.80, -1501.90, 110.90}},
        {!"Rodeo",                             {225.10, -1501.90, -89.00, 334.50, -1369.60, 110.90}},
        {!"Rodeo",                             {334.50, -1501.90, -89.00, 422.60, -1406.00, 110.90}},
        {!"Rodeo",                             {312.80, -1684.60, -89.00, 422.60, -1501.90, 110.90}},
        {!"Rodeo",                             {422.60, -1684.60, -89.00, 558.00, -1570.20, 110.90}},
        {!"Rodeo",                             {558.00, -1684.60, -89.00, 647.50, -1384.90, 110.90}},
        {!"Rodeo",                             {466.20, -1570.20, -89.00, 558.00, -1385.00, 110.90}},
        {!"Rodeo",                             {422.60, -1570.20, -89.00, 466.20, -1406.00, 110.90}},
        {!"Rodeo",                             {466.20, -1385.00, -89.00, 647.50, -1235.00, 110.90}},
        {!"Rodeo",                             {334.50, -1406.00, -89.00, 466.20, -1292.00, 110.90}},
        {!"Royal Casino",                      {2087.30, 1383.20, -89.00, 2437.30, 1543.20, 110.90}},
        {!"San Andreas Sound",            {2450.30, 385.50, -100.00, 2759.20, 562.30, 200.00}},
        {!"Santa Flora",                       {-2741.00, 458.40, -7.60, -2533.00, 793.40, 200.00}},
        {!"Santa Maria Beach",            {342.60, -2173.20, -89.00, 647.70, -1684.60, 110.90}},
        {!"Santa Maria Beach",            {72.60, -2173.20, -89.00, 342.60, -1684.60, 110.90}},
        {!"Shady Cabin",                       {-1632.80, -2263.40, -3.00, -1601.30, -2231.70, 200.00}},
        {!"Shady Creeks",                      {-1820.60, -2643.60, -8.00, -1226.70, -1771.60, 200.00}},
        {!"Shady Creeks",                      {-2030.10, -2174.80, -6.10, -1820.60, -1771.60, 200.00}},
        {!"Sobell Rail Yards",            {2749.90, 1548.90, -89.00, 2923.30, 1937.20, 110.90}},
        {!"Spinybed",                          {2121.40, 2663.10, -89.00, 2498.20, 2861.50, 110.90}},
        {!"Starfish Casino",              {2437.30, 1783.20, -89.00, 2685.10, 2012.10, 110.90}},
        {!"Starfish Casino",              {2437.30, 1858.10, -39.00, 2495.00, 1970.80, 60.90}},
        {!"Starfish Casino",              {2162.30, 1883.20, -89.00, 2437.30, 2012.10, 110.90}},
        {!"Temple",                            {1252.30, -1130.80, -89.00, 1378.30, -1026.30, 110.90}},
        {!"Temple",                            {1252.30, -1026.30, -89.00, 1391.00, -926.90, 110.90}},
        {!"Temple",                            {1252.30, -926.90, -89.00, 1357.00, -910.10, 110.90}},
        {!"Temple",                            {952.60, -1130.80, -89.00, 1096.40, -937.10, 110.90}},
        {!"Temple",                            {1096.40, -1130.80, -89.00, 1252.30, -1026.30, 110.90}},
        {!"Temple",                            {1096.40, -1026.30, -89.00, 1252.30, -910.10, 110.90}},
        {!"The Camel's Toe",              {2087.30, 1203.20, -89.00, 2640.40, 1383.20, 110.90}},
        {!"The Clown's Pocket",           {2162.30, 1783.20, -89.00, 2437.30, 1883.20, 110.90}},
        {!"The Emerald Isle",             {2011.90, 2202.70, -89.00, 2237.40, 2508.20, 110.90}},
        {!"The Farm",                          {-1209.60, -1317.10, 114.90, -908.10, -787.30, 251.90}},
        {!"The Four Dragons Casino",      {1817.30, 863.20, -89.00, 2027.30, 1083.20, 110.90}},
        {!"The High Roller",              {1817.30, 1283.20, -89.00, 2027.30, 1469.20, 110.90}},
        {!"The Mako Span",                     {1664.60, 401.70, 0.00, 1785.10, 567.20, 200.00}},
        {!"The Panopticon",                    {-947.90, -304.30, -1.10, -319.60, 327.00, 200.00}},
        {!"The Pink Swan",                     {1817.30, 1083.20, -89.00, 2027.30, 1283.20, 110.90}},
        {!"The Sherman Dam",              {-968.70, 1929.40, -3.00, -481.10, 2155.20, 200.00}},
        {!"The Strip",                         {2027.40, 863.20, -89.00, 2087.30, 1703.20, 110.90}},
        {!"The Strip",                         {2106.70, 1863.20, -89.00, 2162.30, 2202.70, 110.90}},
        {!"The Strip",                         {2027.40, 1783.20, -89.00, 2162.30, 1863.20, 110.90}},
        {!"The Strip",                         {2027.40, 1703.20, -89.00, 2137.40, 1783.20, 110.90}},
        {!"The Visage",                        {1817.30, 1863.20, -89.00, 2106.70, 2011.80, 110.90}},
        {!"The Visage",                        {1817.30, 1703.20, -89.00, 2027.40, 1863.20, 110.90}},
        {!"Unity Station",                     {1692.60, -1971.80, -20.40, 1812.60, -1932.80, 79.50}},
        {!"Valle Ocultado",                    {-936.60, 2611.40, 2.00, -715.90, 2847.90, 200.00}},
        {!"Verdant Bluffs",                    {930.20, -2488.40, -89.00, 1249.60, -2006.70, 110.90}},
        {!"Verdant Bluffs",                    {1073.20, -2006.70, -89.00, 1249.60, -1842.20, 110.90}},
        {!"Verdant Bluffs",                    {1249.60, -2179.20, -89.00, 1692.60, -1842.20, 110.90}},
        {!"Verdant Meadows",              {37.00, 2337.10, -3.00, 435.90, 2677.90, 200.00}},
        {!"Verona Beach",                      {647.70, -2173.20, -89.00, 930.20, -1804.20, 110.90}},
        {!"Verona Beach",                      {930.20, -2006.70, -89.00, 1073.20, -1804.20, 110.90}},
        {!"Verona Beach",                      {851.40, -1804.20, -89.00, 1046.10, -1577.50, 110.90}},
        {!"Verona Beach",                      {1161.50, -1722.20, -89.00, 1323.90, -1577.50, 110.90}},
        {!"Verona Beach",                      {1046.10, -1722.20, -89.00, 1161.50, -1577.50, 110.90}},
        {!"Vinewood",                          {787.40, -1310.20, -89.00, 952.60, -1130.80, 110.90}},
        {!"Vinewood",                          {787.40, -1130.80, -89.00, 952.60, -954.60, 110.90}},
        {!"Vinewood",                          {647.50, -1227.20, -89.00, 787.40, -1118.20, 110.90}},
        {!"Vinewood",                          {647.70, -1416.20, -89.00, 787.40, -1227.20, 110.90}},
        {!"Whitewood Estates",            {883.30, 1726.20, -89.00, 1098.30, 2507.20, 110.90}},
        {!"Whitewood Estates",            {1098.30, 1726.20, -89.00, 1197.30, 2243.20, 110.90}},
        {!"Willowfield",                       {1970.60, -2179.20, -89.00, 2089.00, -1852.80, 110.90}},
        {!"Willowfield",                       {2089.00, -2235.80, -89.00, 2201.80, -1989.90, 110.90}},
        {!"Willowfield",                       {2089.00, -1989.90, -89.00, 2324.00, -1852.80, 110.90}},
        {!"Willowfield",                       {2201.80, -2095.00, -89.00, 2324.00, -1989.90, 110.90}},
        {!"Willowfield",                       {2541.70, -1941.40, -89.00, 2703.50, -1852.80, 110.90}},
        {!"Willowfield",                       {2324.00, -2059.20, -89.00, 2541.70, -1852.80, 110.90}},
        {!"Willowfield",                       {2541.70, -2059.20, -89.00, 2703.50, -1941.40, 110.90}},
        {!"Yellow Bell Station",          {1377.40, 2600.40, -21.90, 1492.40, 2687.30, 78.00}},
        {!"Los Santos",                        {44.60, -2892.90, -242.90, 2997.00, -768.00, 900.00}},
        {!"Las Venturas",                      {869.40, 596.30, -242.90, 2997.00, 2993.80, 900.00}},
        {!"Bone County",                       {-480.50, 596.30, -242.90, 869.40, 2993.80, 900.00}},
        {!"Tierra Robada",                     {-2997.40, 1659.60, -242.90, -480.50, 2993.80, 900.00}},
        {!"Tierra Robada",                     {-1213.90, 596.30, -242.90, -480.50, 1659.60, 900.00}},
        {!"San Fierro",                        {-2997.40, -1115.50, -242.90, -1213.90, 1659.60, 900.00}},
        {!"Red County",                        {-1213.90, -768.00, -242.90, 2997.00, 596.30, 900.00}},
        {!"Flint County",                      {-1213.90, -2892.90, -242.90, 44.60, -768.00, 900.00}},
        {!"Whetstone",                         {-2997.40, -2892.90, -242.90, -1213.90, -1115.50, 900.00}}
    };
    new
        name[32] = "San Andreas";

    for (new i = 0; i != sizeof(g_arrZoneData); i ++) if((fX >= g_arrZoneData[i][e_ZoneArea][0] && fX <= g_arrZoneData[i][e_ZoneArea][3]) && (fY >= g_arrZoneData[i][e_ZoneArea][1] && fY <= g_arrZoneData[i][e_ZoneArea][4]) && (fZ >= g_arrZoneData[i][e_ZoneArea][2] && fZ <= g_arrZoneData[i][e_ZoneArea][5])) {
        strunpack(name, g_arrZoneData[i][e_ZoneName]);

        break;
    }
    return name;
}

ReturnNames(playerid, underscore=1, mask = 0)
{
    new
        name[MAX_PLAYER_NAME + 1];

    GetPlayerName(playerid, name, sizeof(name));

    if(!underscore) {
        for (new i = 0, len = strlen(name); i < len; i ++) {
                if(name[i] == '_') name[i] = ' ';
        }
    }

    if(mask){
        if(AccountData[playerid][pMaskOn] && !AccountData[playerid][pAdminDuty])
            format(name, sizeof(name), "Mask_#%d", AccountData[playerid][pMaskID]);
    }
    return name;
}

ReturnName(playerid)
{
	new
		name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, name, sizeof(name));

	for(new i = 0, l = strlen(name); i < l; i ++)
	{
	    if(name[i] == '_')
	    {
	        name[i] = ' ';
		}
	}
	return name;
}

stock FormatNumber(Float:amount, delimiter[2]=".", comma[2]=",")
{
	#define MAX_MONEY_String 16
	new txt[MAX_MONEY_String];
	format(txt, MAX_MONEY_String, "%d", floatround(amount));
	new l = strlen(txt);
	if (amount < 0) // -
	{
		if (l > 2) strins(txt,delimiter,l-2);
		if (l > 5) strins(txt,comma,l-5);
		if (l > 8) strins(txt,comma,l-8);
	}
	else
	{//1000000
		if (l > 2) strins(txt,delimiter,l-2);
		if (l > 5) strins(txt,comma,l-5);
		if (l > 9) strins(txt,comma,l-8);
	}
//	if (l <= 2) format(txt,sizeof( szStr ),"00,%s",txt);
	return txt;
}

FormatMoney(cCash)
{
    new szStr[18], dollar[40];
    format(szStr, sizeof(szStr), "%i", cCash);

    for(new iLen = strlen(szStr) - 3; iLen > 0; iLen -= 3)
    {
        strins(szStr, ",", iLen);
    }
	format(dollar, sizeof(dollar), "$%s", szStr);
    return dollar;
}

RandomEx(min, max)
{
    return random(max - min) + min;
}

stock IsRoleplayName(player[])
{
    forex(n,strlen(player))
    {
        if (player[n] == '_' && player[n+1] >= 'A' && player[n+1] <= 'Z') return 1;
        if (player[n] == ']' || player[n] == '[') return 0;
	}
    return 0;
}

//Date and Time
GetMonth(bulan)
{
    static
        month[12];

   	switch (bulan) {
		case 1: month = "January";
		case 2: month = "February";
		case 3: month = "March";
		case 4: month = "April";
		case 5: month = "May";
		case 6: month = "June";
		case 7: month = "July";
		case 8: month = "August";
		case 9: month = "September";
		case 10: month = "October";
		case 11: month = "November";
		case 12: month = "December";
   }
   	return month;
}

/* Clothes Store */
SetPlayerCameraFacingStore(playerid)
{
	static Float:X, Float:Y, Float:Z, Float:A;
	GetPlayerPos(playerid, X, Y, Z);
	GetPlayerFacingAngle(playerid, A);

	SetPlayerCameraPos(playerid, X, Y + 2.5, Z - 0.25);
	SetPlayerCameraLookAt(playerid, X, Y - 1.0, Z + 0.15);
	SetPlayerFacingAngle(playerid, 357.9849);
	TogglePlayerControllable(playerid, 0);
	for(new txd = 0; txd < 84; txd++)
	{
		TextDrawShowForPlayer(playerid, ClothesHapp[txd]);
	}
	for(new i = 0; i < 19; i++)
	{
		PlayerTextDrawShow(playerid, ClothesString[playerid][i]);
	}
	SelectTextDraw(playerid, COLOR_GREY);
	return 1;
}

/* Aksesoris Pvt */
SetPlayerCameraAksesorisPvt(playerid)
{
	static Float:X, Float:Y, Float:Z, Float:A;
	GetPlayerPos(playerid, X, Y, Z);
	GetPlayerFacingAngle(playerid, A);

	SetPlayerCameraPos(playerid, X, Y + 2.5, Z - 0.25);
	SetPlayerCameraLookAt(playerid, X, Y - 1.0, Z + 0.15);
	SetPlayerFacingAngle(playerid, 357.9849);
	TogglePlayerControllable(playerid, 0);
	for(new txd = 0; txd < 16; txd++)
	{
		PlayerTextDrawShow(playerid, P_CLOTHESSELECT[playerid][txd]);
	}
	SelectTextDraw(playerid, COLOR_BLUE);
	return 1;
}

RemainingTimelapse(time)
{
	new currentTime = time - gettime();
    new days = currentTime / 86400;
    new hours = (currentTime % 86400) / 3600;
    new minutes = (currentTime % 3600) / 60;

	new shstr[258];
	format(shstr, sizeof(shstr), "%d Hari %d Jam %d Menit", days, hours, minutes);
	return shstr;
}

ReturnTime()
{
    static
        date[6],
        string[72];

	getdate(date[2], date[1], date[0]);
	gettime(date[3], date[4], date[5]);

	format(string, sizeof(string), "%02d %s %d, %02d:%02d:%02d", date[0],GetMonth(date[1]), date[2], date[3], date[4], date[5]);
	return string;
}

ClearAllChat(playerid)
{
	for(new i = 0; i < 65; i ++)
	{
	    SendClientMessage(playerid, -1, " ");
	}
}

GetRPName(playerid)
{
	new
		name[MAX_PLAYER_NAME];

	GetPlayerName(playerid, name, sizeof(name));

	for(new i = 0, l = strlen(name); i < l; i ++)
	{
	    if(name[i] == '_')
	    {
	        name[i] = ' ';
		}
	}

	return name;
}

SetFactionColor(playerid)
{
    new factionid = AccountData[playerid][pFaction];

    if(factionid == 1)
	{
		SetPlayerColor(playerid, COLOR_BLUE);
	}
	else if(factionid == 2)
	{
		SetPlayerColor(playerid, COLOR_YELLOW);
	}
	else if(factionid == 3)
	{
		SetPlayerColor(playerid, COLOR_PINK2);
	}
	else if(factionid == 4)
	{
		SetPlayerColor(playerid, COLOR_GREEN);
	}
	else if(factionid == 5)
	{
		SetPlayerColor(playerid, COLOR_LBLUE);
	}
	else if(factionid == 6)
	{
		SetPlayerColor(playerid, COLOR_ORANGE2);
	}
	else
	{
		SetPlayerColor(playerid, COLOR_WHITE);
	}
	return 1;
}

//Log Server YSI
/*forward LogServer(type[], const text[], {Float,_}:...);
public LogServer(type[], const text[], {Float,_}:...)
{
	new entry[256],days, months, years, hours, minutes, seconds;

	getdate(years, months, days);
	gettime(hours, minutes, seconds);

	format(entry, sizeof(entry), "[%02d/%02d/%02d - %02d:%02d:%02d] - %s\r\n",
	days, months, years, hours, minutes, seconds, text);

	new File:hFile, tipe[50];
	format(tipe, sizeof(tipe), "Logs/%s.txt", type);
	hFile = fopen((tipe), io_append);
	fwrite(hFile, entry);
	fclose(hFile);
	return 0;
}*/

ShowMenuKarakterlist(playerid)
{
	for(new i = 0; i < 20; i++)
	{
		PlayerTextDrawShow(playerid, ChoseKarakter[playerid][i]);
	}

	for(new i = 0; i < 3; i++)
	{
		PlayerTextDrawShow(playerid, ChoseKarakterInfo[playerid][i]);
	}

	for (new i; i < MAX_CHARS; i ++) if(PlayerChar[playerid][i][0] != EOS)
    {
        PlayerTextDrawSetString(playerid, ChoseKarakterInfo[playerid][i], PlayerChar[playerid][i]);
    }

	SelectCharIndex[playerid] = 0;
	SelectTextDraw(playerid, X11_LIGHTBLUE);
	new rand = RandomEx(1, 100);

	if(PlayerChar[playerid][SelectCharIndex[playerid]][0] == EOS)
	{
		SetSpawnInfo(playerid, 0, 1, 306.2181,304.1817,1003.3047,89.1640, 0, 0, 0, 0, 0, 0);
		SetPlayerVirtualWorld(playerid, rand);
		SpawnPlayer(playerid);
		ClearAnimations(playerid);
		ApplyAnimationEx(playerid, "CRIB", "PED_Console_Loop", 4.1, 1, 0, 0, 0, 0);
	}
	else
	{
		SetSpawnInfo(playerid, 0, CharSkin[playerid][0], 306.2181,304.1817,1003.3047,89.1640, 0, 0, 0, 0, 0, 0);
		SetPlayerVirtualWorld(playerid, rand);
		SpawnPlayer(playerid);
		ClearAnimations(playerid);
		ApplyAnimationEx(playerid, "CRIB", "PED_Console_Loop", 4.1, 1, 0, 0, 0, 0);
	}

	SendClientMessage(playerid, -1, "Getting into of your character, please wait...");
	SendClientMessage(playerid, -1, "Character List has been Synchronized");
	ClearAnimations(playerid);
	ApplyAnimationEx(playerid, "CRIB", "PED_Console_Loop", 4.1, 1, 0, 0, 0, 0);
	return 1;
}

stock Register(playerid)
{
    forex (i, 55)
	{
		PlayerTextDrawShow(playerid, RegisterHapp[playerid][i]);
	}
	SelectTextDraw(playerid, 461004191);
	return 1;
}

stock HideMenuKarakter(playerid)
{
	PlayerTextDrawHide(playerid, ChoseKarakterInfo[playerid][0]);
	PlayerTextDrawHide(playerid, ChoseKarakterInfo[playerid][1]);
	PlayerTextDrawHide(playerid, ChoseKarakterInfo[playerid][2]);

	for(new i = 0; i < 20; i++)
	{
		PlayerTextDrawHide(playerid, ChoseKarakter[playerid][i]);
	}
	return 1;
}

stock ShowClothesLocation(playerid)
{
	new pelernen[1024], str[500];
    format(pelernen, sizeof(pelernen), "Nama\tLokasi\tJarak\n");
	foreach(new i : Warung) if(WarungData[i][warungType] == 3) //baju
	{
        if(i % 2 == 0)
        {
            format(str, sizeof(str), ""WHITE"Clothes\t %s\t"YELLOW"%.2f Meter\n", GetLocation(WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2]),GetPlayerDistanceFromPoint(playerid,WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2]));
            strcat(pelernen, str);
        }
		else
        {
            format(str, sizeof(str), ""GREY"Clothes\t %s\t"YELLOW"%.2f Meter\n", GetLocation(WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2]),GetPlayerDistanceFromPoint(playerid,WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2]));
            strcat(pelernen, str);
        } 
	}
	Dialog_Show(playerid, DialogGpsClothes, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District "WHITE" - Lokasi Toko", pelernen, "Select", "Close");
	return 1;
}

stock ShowShopLocation(playerid)
{
	new Happ[1024], str[500];
	format(Happ, sizeof(Happ), "Nama\tLokasi\tJarak\n");
	foreach(new i : Warung) if(WarungData[i][warungType] == 1) //shop
	{
		if(i % 2 == 0)
		{
			format(str, sizeof(str), ""GRAY"Shop\t%s\t"YELLOW"%.2f Meter\n", GetLocation(WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2]),GetPlayerDistanceFromPoint(playerid,WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2]));
			strcat(Happ, str);
		}
		else
		{
			format(str, sizeof(str), ""GREY"Shop\t %s\t"YELLOW"%.2f Meter\n", GetLocation(WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2]),GetPlayerDistanceFromPoint(playerid,WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2]));
            strcat(Happ, str);
		}
	}
	Dialog_Show(playerid, DialogGpsShop, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District "WHITE" - Lokasi Toko", Happ, "Select", "Close");
	return 1;
}

stock ShowElekLocation(playerid)
{
	new pelernen[1024], str[500];
    format(pelernen, sizeof(pelernen), "Nama\tLokasi\tJarak\n");
	foreach(new i : Warung) if(WarungData[i][warungType] == 2) //elek
	{
        if(i % 2 == 0)
        {
            format(str, sizeof(str), ""WHITE"Elektronik\t %s\t"YELLOW"%.2f Meter\n", GetLocation(WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2]),GetPlayerDistanceFromPoint(playerid,WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2]));
            strcat(pelernen, str);
        }
		else
        {
            format(str, sizeof(str), ""GREY"Elektronik\t %s\t"YELLOW"%.2f Meter\n", GetLocation(WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2]),GetPlayerDistanceFromPoint(playerid,WarungData[i][warungPOS][0], WarungData[i][warungPOS][1], WarungData[i][warungPOS][2]));
            strcat(pelernen, str);
        } 
	}
	Dialog_Show(playerid, DialogGpsElek, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District "WHITE" - Lokasi Toko", pelernen, "Select", "Close");
	return 1;
}

stock ShowAtmLocation(playerid)
{
	new str[2556], count = 0;
    format(str, sizeof(str), "Lokasi\tJarak\n");

    for(new i = 0; i < MAX_ATM; i++)
    {
        if(AtmData[i][atmX] == 0.0 && AtmData[i][atmX] == 0.0 && AtmData[i][atmX] == 0.0) 
            continue;

        count++;

        if(count % 2 == 0)
        {
            format(str, sizeof(str), "%s\t"GRAY"%s\t"YELLOW"%.2f Meter\n", str, GetLocation(AtmData[i][atmX], AtmData[i][atmY], AtmData[i][atmZ]), GetPlayerDistanceFromPoint(playerid, AtmData[i][atmX], AtmData[i][atmY], AtmData[i][atmZ]));
        }
        else 
        {
            format(str, sizeof(str), "%s\t"GREY"%s\t"YELLOW"%.2f Meter\n", str, GetLocation(AtmData[i][atmX], AtmData[i][atmY], AtmData[i][atmZ]), GetPlayerDistanceFromPoint(playerid, AtmData[i][atmX], AtmData[i][atmY], AtmData[i][atmZ]));
        }
    }
    if(count == 0)
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Atm yang tersedia saat ini!");
    }
    Dialog_Show(playerid, DialogGpsAtm, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District "WHITE" - Lokasi Atm", str, "Select", "Close");
    return 1;
}

stock ShowTrashLocation(playerid)
{
    new str[2556], count = 0;
    format(str, sizeof(str), "Lokasi\tJarak\n");

    for(new i = 0; i < MAX_DYNAMIC_TRASH; i++)
    {
        if(TrashData[i][trashPos][0] == 0.0 && TrashData[i][trashPos][1] == 0.0 && TrashData[i][trashPos][2] == 0.0) 
            continue;

        count++;

        if(count % 2 == 0)
        {
            format(str, sizeof(str), "%s\t"WHITE"%s\t"YELLOW"%.2f Meter\n", str, GetLocation(TrashData[i][trashPos][0], TrashData[i][trashPos][1], TrashData[i][trashPos][2]), GetPlayerDistanceFromPoint(playerid, TrashData[i][trashPos][0], TrashData[i][trashPos][1], TrashData[i][trashPos][2]));
        }
        else 
        {
            format(str, sizeof(str), "%s\t"GREY"%s\t"YELLOW"%.2f Meter\n", str, GetLocation(TrashData[i][trashPos][0], TrashData[i][trashPos][1], TrashData[i][trashPos][2]), GetPlayerDistanceFromPoint(playerid, TrashData[i][trashPos][0], TrashData[i][trashPos][1], TrashData[i][trashPos][2]));
        }
    }
    if(count == 0)
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Trash yang tersedia saat ini!");
    }
    Dialog_Show(playerid, DialogGpsTrash, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District "WHITE" - Lokasi Trash", str, "Select", "Close");
    return 1;
}

stock ShowGarasiLocation(playerid)
{
    new str[2556], count = 0;
    format(str, sizeof(str), "Lokasi\tJarak\n");

    for(new i = 0; i < MAX_PUBLIC_GARAGE; i++)
    {
        if(PublicGarage[i][pgPOS][0] == 0.0 && PublicGarage[i][pgPOS][1] == 0.0 && PublicGarage[i][pgPOS][2] == 0.0) 
            continue;

        count++;

        if(count % 2 == 0)
        {
            format(str, sizeof(str), "%s\t"WHITE"%s\t"YELLOW"%.2f Meter\n", str, GetLocation(PublicGarage[i][pgPOS][0], PublicGarage[i][pgPOS][1], PublicGarage[i][pgPOS][2]), GetPlayerDistanceFromPoint(playerid, PublicGarage[i][pgPOS][0], PublicGarage[i][pgPOS][1], PublicGarage[i][pgPOS][2]));
        }
        else 
        {
            format(str, sizeof(str), "%s\t"GREY"%s\t"YELLOW"%.2f Meter\n", str, GetLocation(PublicGarage[i][pgPOS][0], PublicGarage[i][pgPOS][1], PublicGarage[i][pgPOS][2]), GetPlayerDistanceFromPoint(playerid, PublicGarage[i][pgPOS][0], PublicGarage[i][pgPOS][1], PublicGarage[i][pgPOS][2]));
        }
    }
    if(count == 0)
    {
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada garasi kota yang tersedia saat ini!");
    }
    Dialog_Show(playerid, DialogGpsGarasi, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District "WHITE" - Lokasi Garasi Kota", str, "Select", "Close");
    return 1;
}

PlayerTDDestroy(playerid)
{
	for(new i = 0; i < 55; i++) PlayerTextDrawDestroy(playerid, InjuredAgusSamp[playerid][i]);
	for(new ii = 0; ii < 20; ii++) PlayerTextDrawDestroy(playerid, ClothesString[playerid][ii]);
	for(new a = 0; a < 21; a++) PlayerTextDrawDestroy(playerid, VR_BANNEDTD[playerid][a]);
	for(new b = 0; b < 16; b++) PlayerTextDrawDestroy(playerid, P_CLOTHESSELECT[playerid][b]);
	for(new c = 0; c < 61; c++) PlayerTextDrawDestroy(playerid, ktpTextdraws[playerid][c]);
	for(new d = 0; d < 41; d++) PlayerTextDrawDestroy(playerid, KTAtextdraws[playerid][d]);
	for(new e = 0; e < 44; e++) PlayerTextDrawDestroy(playerid, VR_ATMTD[playerid][e]);
	for(new f = 0; f < 15; f++) PlayerTextDrawDestroy(playerid, HbeStuffs[playerid][f]);
	for(new g = 0; g < 82; g++) PlayerTextDrawDestroy(playerid, RadialFertod[playerid][g]);
	for(new h = 0; h < 15; h++) PlayerTextDrawDestroy(playerid, PUTRABOTAKHBE[playerid][h]);
	for(new j = 0; j < 20; j++) PlayerTextDrawDestroy(playerid, ChoseKarakter[playerid][j]);
	for(new kk = 0; kk < MAX_INVENTORY; kk++) PlayerTextDrawDestroy(playerid, i_box[playerid][kk]);
	for(new aa = 0; aa < MAX_INVENTORY; aa++) PlayerTextDrawDestroy(playerid, i_model[playerid][aa]);
	for(new bb = 0; bb < MAX_INVENTORY; bb++) PlayerTextDrawDestroy(playerid, i_item[playerid][bb]);
	for(new cc = 0; cc < MAX_INVENTORY; cc++) PlayerTextDrawDestroy(playerid, i_qwt[playerid][cc]);
	for(new dd = 0; dd < 47; dd++) PlayerTextDrawDestroy(playerid, i_textdraw[playerid][dd]);
	for(new ee = 0; ee < 22; ee++) PlayerTextDrawDestroy(playerid, FlistTD[playerid][ee]);
	
	return 1;
}
GlobalTDDestroy()
{
	for(new i = 0; i < 17; i++) TextDrawDestroy(TdBadaiHapp[i]);
	for(new a = 0; a < 10; a++) TextDrawDestroy(ATRP_Warning[a]);
	for(new b = 0; b < 16; b++) TextDrawDestroy(InsuKelHapp[b]);
	for(new c = 0; c < 22; c++) TextDrawDestroy(OpenTollTD[c]);
	for(new d = 0; d < 84; d++) TextDrawDestroy(ClothesHapp[d]);
	for(new e = 0; e < 18; e++) TextDrawDestroy(KICKAGUSSAMP[e]);

	return 1;
}

IsAirVehicle(modelid)
{
    switch(modelid)
    {
        case 417, 425, 447, 469, 487, 488, 497, 511, 512, 519, 520, 548, 553, 577, 592, 593:
            return true;
    }
    return false; 
}

GetHousesPaytax(playerid)
{
	new tmpcount;
	foreach(new hid : House)
	{
	    if(!strcmp(HouseData[hid][hsOwner], AccountData[playerid][pName], true))
	    {
     		tmpcount++;
		}
	}
	return tmpcount;
}

stock AllStepDone(playerid)
{
    for(new i = 0; i < 5; i++)
    {
        if(!CreateCharStepDone[playerid][i])
            return 0;
    }
    return 1;
}

ReturnHousesPaytaxID(playerid, slot)
{
	new tmpcount;
	if(slot < 1 && slot > MAX_RUMAH) return -1;
	foreach(new hid : House)
	{
		if(!strcmp(AccountData[playerid][pName], HouseData[hid][hsOwner], true))
		{
		    tmpcount++;
		    if(tmpcount == slot)
		    {
		    	return hid;
		  	}
		}
	}
	return -1;
}

TakeWeaponLooting(playerid, targetid)
{
	for(new i = 0; i < MAX_WEAPON_SLOT; i++)
		LootMap[playerid][i] = -1;

    new frmtgun[1024];
    format(frmtgun, sizeof(frmtgun), "Senjata\tAmunisi\n");

    new weaponid, ammo, bool:found = false;
	new listIndex = 0;

    for(new slot = 1; slot < MAX_WEAPON_SLOT; slot++)
    {
        GetPlayerWeaponData(targetid, slot, weaponid, ammo);

        if(weaponid > 0)
        {
            LootWeapons[playerid][slot] = weaponid;
            LootAmmo[playerid][slot] = AccountData[targetid][pAmmo][g_aWeaponSlots[weaponid]]; 

            format(frmtgun, sizeof(frmtgun), "%s%s\t%d Ammo\n",
                frmtgun,
                ReturnWeaponName(weaponid),
                LootAmmo[playerid][slot]
            );
			LootMap[playerid][listIndex] = slot;
			listIndex++;

            found = true;
        }
        else
        {
            LootWeapons[playerid][slot] = -1;
            LootAmmo[playerid][slot] = 0;
        }
    }

    if(!found)
    {
        PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
        return ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX,
            ""TCRP"District  "WHITE" - Kepemilikan Senjata",
            "Pemain tersebut tidak memiliki senjata apapun!", "Tutup", "");
    }

    Dialog_Show(playerid, DialogTakeLooting, DIALOG_STYLE_TABLIST_HEADERS,""TCRP"District  "WHITE" - Ambil Senjata", frmtgun, "Ambil", "Tutup");
    AccountData[playerid][pTempTarget] = targetid;
    return 1;
}

Dialog:DialogTakeLooting(playerid, response, listitem, inputtext[])
{
    if(!response)
	{
		for(new i = 0; i < MAX_WEAPON_SLOT; i++)
			LootMap[playerid][i] = -1;
		AccountData[playerid][pTempTarget] = -1;
		ShowTDN(playerid, NOTIFICATION_INFO, "Anda membatalkan pilihan");
		return 1;
	} 

    new targetid = AccountData[playerid][pTempTarget];

    new slot = LootMap[playerid][listitem];
    new weaponid = LootWeapons[playerid][slot];
    new ammo = LootAmmo[playerid][slot];

    if(weaponid > 0)
    {
        GivePlayerWeaponEx(playerid, weaponid, ammo);

        AccountData[targetid][pAmmo][g_aWeaponSlots[weaponid]] = 0;
        ResetWeapon(targetid, weaponid);
        LootWeapons[playerid][slot] = -1;
        LootAmmo[playerid][slot] = 0;

        AccountData[playerid][pTempTarget] = -1;
		Info(targetid, "Senjata "RED"%s "WHITE"anda di ambil paksa oleh "CYAN"%s", ReturnWeaponName(weaponid), ReturnName(playerid));
        ShowTDN(playerid, NOTIFICATION_SUKSES, "Senjata berhasil diambil paksa");
		for(new i = 0; i < MAX_WEAPON_SLOT; i++)
			LootMap[playerid][i] = -1;
    }
    else
    {
        ShowTDN(playerid, NOTIFICATION_ERROR, "Senjata tidak tersedia atau sudah diambil!");
    }
    return 1;
}