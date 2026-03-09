new TempDiscordName[DCC_USERNAME_SIZE];
new DCC_Channel:g_LogChannel;
new DCC_Channel:g_AdminLogChannel;
new DCC_Channel:g_SecurityLogChannel;
new DCC_Channel:g_DeathLogChannel;

forward DCC_DM(str[]);
public DCC_DM(str[])
{
    new DCC_Channel:PM;
	PM = DCC_GetCreatedPrivateChannel();
	DCC_SendChannelMessage(PM, str);
	return 1;
}
forward DCC_DM_EMBED(str[], pin, id[]);
public DCC_DM_EMBED(str[], pin, id[])
{
	new DCC_Channel: PM, query[255];
	PM = DCC_GetCreatedPrivateChannel();
	new DCC_Embed:embed = DCC_CreateEmbed(.title="District ", .image_url="https://media.discordapp.net/attachments/1159376834337701941/1160296311287988325/A4.png?ex=65342525&is=6521b025&hm=287210874fb4c4797d73e750d1c9da1d9a8c39f9873617d5f1a38e56127a2c9b&=&width=607&height=607", .footer_text = "Pemberitahuan Tiket District ");

	new shstr[1218];
	format(shstr, sizeof(shstr), "Yang terhormat, %s.\
	\n\nMohon perhatian anda, pengambilan Tiket berhasil dilakukan.\
	\nGunakan UCP untuk login ke dalam server!\
	\nSegera masuk ke Kota **(login in-game)** dan masukkan kode verifikasi di bawah!\
	\n\n** UCP: **\
	\n```%s```\
	\n** Verification Code: **\
	\n```%d```\
	\n** IP Server: **\
	\n```PRIVATE:7777```", TempDiscordName, str, pin);

	DCC_SetEmbedDescription(embed, shstr);
	DCC_SetEmbedColor(embed, 0xf0635e);

	DCC_SendChannelEmbedMessage(PM, embed);

	mysql_format(g_SQL, query, sizeof query, "INSERT INTO `playerucp` (`ucp`, `verifycode`, `DiscordID`) VALUES ('%e', '%d', '%e')", str, pin, id);
	mysql_tquery(g_SQL, query);
	return 1;
}

forward DCC_DM_LUPAPW(pin, id[]);
public DCC_DM_LUPAPW(pin, id[])
{
	new DCC_Channel:PM;
	PM = DCC_GetCreatedPrivateChannel();

	new DCC_Embed:embed = DCC_CreateEmbed(.title="Pemulihan Akun - District ", .image_url="https://media.discordapp.net/attachments/1159376834337701941/1160296311287988325/A4.png?ex=65342525&is=6521b025&hm=287210874fb4c4797d73e750d1c9da1d9a8c39f9873617d5f1a38e56127a2c9b&=&width=669&height=669", .footer_text = "District  #1");
	new str1[1000];

	format(str1, sizeof str1, "⚠ **Peringatan**\nAnda telah meminta layanan lupa password.\nJika ini bukan permintaan anda, maka abaikan saja pesan ini!\n\n**Kode Pemulihan**:\n```\n%d\n```\nMasuklah ke server dan masukkan Kode Pemulihan untuk\nmembuat ulang kata sandi!\n**#District **\n_~Server kita terpVehInteriorah_", pin);
	
	DCC_SetEmbedDescription(embed, str1);
	DCC_SetEmbedColor(embed, 0xff9999);

	DCC_SendChannelEmbedMessage(PM, embed);

	mysql_tquery(g_SQL, sprintf("UPDATE playerucp SET verifycode='%d', password='', salt='' WHERE DiscordID='%s'", pin, id));
	// mysql_format(g_SQL, query, sizeof query, "INSERT INTO `playerucp` (`ucp`, `verifycode`, `DiscordID`) VALUES ('%e', '%d', '%e')", str, pin, id);
	// mysql_tquery(g_SQL, query);
	return 1;
}

forward CheckAccountUCP(DiscordID[]);
public CheckAccountUCP(DiscordID[])
{
	new verifycode = RandomEx(11111, 99999);
	new dc[512];
	new DCC_Channel:registchannel, DCC_User: user;
	registchannel = DCC_FindChannelById("");
	new DCC_Embed:regist = DCC_CreateEmbed(.footer_text = "Penjaga Kota District ", .thumbnail_url = "https://media.discordapp.net/attachments/1159376834337701941/1160296311287988325/A4.png?ex=65342525&is=6521b025&hm=287210874fb4c4797d73e750d1c9da1d9a8c39f9873617d5f1a38e56127a2c9b&=&width=669&height=669");
	format(dc, sizeof dc, "> :white_check_mark: UCP Berhasil di reset password!\nSilahkan cek Direct Message Anda!");

	user = DCC_FindUserById(DiscordID);
	DCC_SetEmbedDescription(regist, dc);
	DCC_SetEmbedColor(regist, 0xff9999);
	DCC_SendChannelEmbedMessage(registchannel, regist);
	DCC_CreatePrivateChannel(user, "DCC_DM_LUPAPW", "ds", verifycode, DiscordID);

	//mysql_tquery(g_SQL, sprintf("UPDATE playerucp SET `password`='' WHERE DiscordID = '%s'", DiscordID));
	return 1;
}

forward CheckDiscordUCP(DiscordID[], Nama_UCP[]);
public CheckDiscordUCP(DiscordID[], Nama_UCP[])
{
	new VerifCode = RandomEx(111111, 999999);
	if(cache_num_rows())
	{
		SendEmbedMessage("District ", "> :x1: ** Nama UCP ** tersebut sudah ada dalam Database!\n> Gunakan ** Nama UCP ** yang lain", "#JAVAROLEPLAY", "", "", "1159376835772153862", 0xf0635e);
		return 1;
	}
	else 
	{
		new DCC_Guild: GuildID = DCC_FindGuildById("1159376831758221383");
		new DCC_Role: WargaRole = DCC_FindRoleById("1159376832227983456");
		new DCC_User: UserID = DCC_FindUserById(DiscordID);
		DCC_SetGuildMemberNickname(GuildID, UserID, sprintf("Warga | %s", Nama_UCP));
		DCC_AddGuildMemberRole(GuildID, UserID, WargaRole);
		
		SendEmbedMessage("District ", sprintf("> :white_check_mark: UCP **%s** telah berhasil didaftarkan!\n> Silahkan untuk mengecek direct message dari Bot", Nama_UCP), "#JAVAROLEPLAY", "", "", "1159376835772153862", 0xf0635e);
		DCC_CreatePrivateChannel(UserID, "DCC_DM_EMBED", "sds", Nama_UCP, VerifCode, DiscordID);
	}
	return 1;
}

forward CheckDiscordPlayer(DiscordID[]);
public CheckDiscordPlayer(DiscordID[])
{
	if(!cache_num_rows())
	{
		SendEmbedMessage("District ", "> :x1: Anda belum pernah membuat UCP Sebelumnya!", "Penjaga Kota District ", "", "", "1160993063234179102", 0xff0000);
	}
	else
	{
		new query[200];
		mysql_format(g_SQL, query, sizeof(query), "SELECT `ucp` FROM `playerucp` WHERE `DiscordID` = '%e'", DiscordID);
		mysql_tquery(g_SQL, query, "CheckAccountUCP", "s", DiscordID);
	}
	return 1;
}

forward CheckDiscordID(DiscordID[], Nama_UCP[]);
public CheckDiscordID(DiscordID[], Nama_UCP[])
{
	new UCP[24];
	if(cache_num_rows())
	{
		cache_get_value_name(0, "ucp", UCP);

		new frmxt[155];
		format(frmxt, sizeof(frmxt), "> :x: Sebelumnya anda sudah mengambil tiket dengan nama **%s**", UCP);
		SendEmbedMessage("District !", frmxt, "#JAVAROLEPLAY", "", "", "1159376835772153862", 0xf0635e);
		return 1;
	}
	else 
	{
		new query[200];
		mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `playerucp` WHERE `ucp`='%s'", Nama_UCP);
		mysql_tquery(g_SQL, query, "CheckDiscordUCP", "ss", DiscordID, Nama_UCP);
	}
	return 1;
}

DCMD:resetpassword(user, channel, params[])
{
	new id[21];
	if(channel != DCC_FindChannelById("1160993063234179102"))
		return 1;

	DCC_GetUserId(user, id, sizeof id);

	new characterQuery[178];
	mysql_format(g_SQL, characterQuery, sizeof(characterQuery), "SELECT * FROM `playerucp` WHERE `DiscordID` = '%s'", id);
	mysql_tquery(g_SQL, characterQuery, "CheckDiscordPlayer", "ss", id, params);
	return 1;
}

DCMD:restart(user, channel, params[])
{
	if(channel != DCC_FindChannelById("1141366469909827696"))
		return 1;
	
	new dcname[DCC_USERNAME_SIZE];
	DCC_GetUserName(user, dcname, sizeof(dcname));

	SendClientMessageToAllEx(X11_ARWIN, ""RED"%s"ARWIN1" From Discord: Server akan restart dalam 20 detik!", dcname);
	SetTimer("KickPlayerAll", 20000, false);
	DCC_SendChannelMessage(channel, "Berhasil menggunakan command discord /restart");
	return 1;
}

forward KickPlayerAll();
public KickPlayerAll()
{
	foreach(new i : Player)
	{
		UpdatePlayerData(i);
		SendClientMessage(i, X11_ARWIN, "[AdmCmd] Semua database anda telah tersimpan dengan baik ke pusat!");
		KickEx(i);

		SendRconCommand("exit");
	}
	return 1;
}

DCMD:icmsg(user, channel, params[])
{
	new shstr[128], discordName[DCC_USERNAME_SIZE];

	DCC_GetUserName(user, discordName, sizeof discordName);

	if(sscanf(params, "s[128]", shstr))
	{
		SendEmbedMessage("SYNTAX USAGE", "!icmsg [pesan]", "District  #1", "", "", "1159376834337701941", 0x707371);
		return 1;
	}

	if(strlen(shstr) > 64)
	{
		SendClientMessageToAllEx(X11_ARWIN, "[Annoucement From Discord]: Pesan dari "RED"%s.", discordName);
		SendClientMessageToAllEx(X11_ARWIN, "-> %.64s ...", shstr);
		SendClientMessageToAllEx(X11_ARWIN, "... %s", shstr[64]);
	}
	else 
	{
		SendClientMessageToAllEx(X11_ARWIN, "[Annoucement From Discord]: Pesan dari "RED"%s.", discordName);
		SendClientMessageToAllEx(X11_ARWIN, "-> %s", shstr);
	}

	SendEmbedMessage("MESSAGE TO SERVER", shstr, "District  #1", "", "", "1159376834337701941", 0x707371);
	return 1;
}

DCMD:update(user, channel, params[])
{
	new shstr[1218];
	new id[21];
	DCC_GetUserId(user, id, sizeof id);

	if (strcmp(id, "1002869262135869501", true) != 0)
    {
        SendEmbedMessage("ERROR", "Hanya Founder yang dapat menggunakan discord command ini!", "District  #Updates", "", "", "1010976548326756422", 0x3bd17c);
        return 1;
    }
	
	if(isnull(params))
	{
		return SendEmbedMessage("SYNTAX USAGE", "!update [list update]", "District  #Updates", "", "", "1010976548326756422", 0x3bd17c);
	}

	format(shstr, sizeof(shstr), "%s", params);
	SendEmbedMessage("UPDATES", shstr, "District  #Updates", "https://cdn.discordapp.com/attachments/1063836454586962020/1111675562428207165/verona_1.jpg", "", "1010976548326756422", 0x3bd17c);
	return 1;
}

DCMD:players(user, channel, params[])
{
	new dc[555];

	new DCC_Embed:leave = DCC_CreateEmbed(.title = "District ", .footer_text = "Penjaga Pintu Kota #1");
	format(dc, sizeof(dc), "**Pemain yang sedang dikota District  saat ini:**\n**Jumlah:** %d", Iter_Count(Player));
	DCC_SetEmbedDescription(leave, dc);
	DCC_SetEmbedColor(leave, 0xff8fd5);
	DCC_SendChannelEmbedMessage(channel, leave);
	return 1;
}
DCMD:ambiltiket(user, channel, params[])
{
	new userID[21];
	if(channel != DCC_FindChannelById("1159376835772153862"))
		return 1;
	
	DCC_GetUserName(user, TempDiscordName, sizeof(TempDiscordName));
	
	if(isnull(params))
	{
		SendEmbedMessage("District ", "**Gunakan Format: !ambiltiket [nama ucp]**\n**NOTE: Gunakan nama UCP valid tidak kurang dari 5 atau lebih dari 10 huruf!**", "#JAVAROLEPLAY", "", "", "1159376835772153862", 0xf0635e);
		return 1;
	}

	if(!IsValidNameUCP(params))
	{
		SendEmbedMessage("District ", "> **Gunakan Nama UCP Yang Valid!**\n\n:white_check_mark:**Contoh UCP Yang Valid**: _**Cecep**_, _**Pragos**_\n:x:**Contoh UCP yang salah**: _**Banteng_Merah**_, _**Ucok?**_\n\n>>> **NOTE: Jangan menggunakan symbol pada nama ucp anda sepert `#`, `&` atau apapun itu**\n**Usahakan untuk membuat Nama UCP Jangan terlalu sulit agar dapat mudah diingat**", "#JAVAROLEPLAY", "", "", "1159376835772153862", 0xf0635e);
		return 1;
	}

	DCC_GetUserId(user, userID, sizeof(userID));

	new cQuery[200];
	mysql_format(g_SQL, cQuery, sizeof(cQuery), "SELECT * FROM `playerucp` WHERE `DiscordID`='%s'", userID);
	mysql_tquery(g_SQL, cQuery, "CheckDiscordID", "ss", userID, params);
	return 1;
}