#define MAX_CONTACTS	100

enum contactData {
	contactID,
	contactExists,
	contactName[32],
	contactNumber[64],
	contactOwnerID,
	contactUnread,
	contactBlocked
};
new ContactData[MAX_PLAYERS][MAX_CONTACTS][contactData];
new ListedContacts[MAX_PLAYERS][MAX_CONTACTS];
new PlayerContactPage[MAX_PLAYERS];

ShowContactList(playerid)
{
	new page = PlayerContactPage[playerid];

	new sha[1046], shstr[1046];
	new count = 0;

	new start_index = page * 15;
	new end_index = start_index + 15;

	strcat(sha, "Nama\tNomor\tStatus\tBlokir\n");
	for (new i = start_index; i < end_index && i < MAX_CONTACTS; i ++) if (ContactData[playerid][i][contactExists] && ContactData[playerid][i][contactOwnerID] == AccountData[playerid][pID])
	{
		new numberowner = GetNumberOwner(ContactData[playerid][i][contactNumber]);
		if(!ContactData[playerid][i][contactUnread])
		{
			format(shstr, sizeof(shstr), "%s\t%s\t%s\t%s\n",
				ContactData[playerid][i][contactName],
				ContactData[playerid][i][contactNumber],
				IsPlayerConnected(numberowner) ? ""LIGHTGREEN"(Online)" : ""ORANGE"(Offline)",
				(ContactData[playerid][i][contactBlocked] == 1) ? ""RED"Diblokir" : ""LIGHTGREEN"-");
			
			strcat(sha, shstr);
		}
		else
		{
			format(shstr, sizeof(shstr), "%s\t%s\t%s "LIGHTGREY"[%d belum dibaca]\t%s\n",
				ContactData[playerid][i][contactName],
				ContactData[playerid][i][contactNumber],
				IsPlayerConnected(numberowner) ? ""LIGHTGREEN"(Online)" : ""ORANGE"(Offline)",
				ContactData[playerid][i][contactUnread],
				(ContactData[playerid][i][contactBlocked] == 1) ? ""RED"Diblokir" : ""LIGHTGREEN"-");
			
			strcat(sha, shstr);
		}
		ListedContacts[playerid][count ++] = i;
	}

	if(count)
	{
		if(count == 15)  strcat(sha, ""LIGHTGREEN">> Halaman Selanjutnya\t\n");
		if(page != 0) strcat(sha, ""RED"<< Halaman Sebelumnya\t\n");
		ShowPlayerDialog(playerid, DialogContact, DIALOG_STYLE_TABLIST_HEADERS, sprintf(""TCRP"District  "WHITE"- Daftar Kontak (%d/100)", CountPlayerContact(playerid)), sha, "Pilih", "Batal");
		return 1;
	}
	else ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, sprintf(""TCRP"District  "WHITE"- Daftar Kontak (%d/100)", CountPlayerContact(playerid)), "Anda tidak memiliki kontak tersimpan!", "Tutup", ""), PlayerContactPage[playerid] = 0;
	return 1;
}

/*ShowContactList(playerid)
{
	for (new ix = 0; ix != MAX_CONTACTS; ix ++) 
	{
		ContactData[playerid][ix][contactExists] = false;
	}

	new page = PlayerContactPage[playerid];
	new frmtstring[188], sha[1046], shstr[255];
	new count = 0, rowcount, Cache: result;
	
	mysql_format(g_SQL, frmtstring, sizeof(frmtstring), "SELECT * FROM `contacts` WHERE `ID`=%d ORDER BY ID ASC LIMIT %d, 15", AccountData[playerid][pID], page * 15);
	result = mysql_query(g_SQL, frmtstring, true);

	rowcount = cache_num_rows();
	for (new i = 0; i < rowcount && i < MAX_CONTACTS; i ++)
	{
		if(!ContactData[playerid][i][contactExists])
		{
			ContactData[playerid][i][contactExists] = true;
			cache_get_value_name_int(i, "contactID", ContactData[playerid][i][contactID]);
			cache_get_value_name(i, "contactName", ContactData[playerid][i][contactName]);
			cache_get_value_name(i, "contactNumber", ContactData[playerid][i][contactNumber]);
			cache_get_value_name_int(i, "contactUnread", ContactData[playerid][i][contactUnread]);
			cache_get_value_name_int(i, "contactBlocked", ContactData[playerid][i][contactBlocked]);
			cache_get_value_name_int(i, "contactOwner", ContactData[playerid][i][contactOwnerID]);
		}
	}

	strcat(sha, "Nama\tNomor\tStatus\tBlokir\n");
	for (new i = 0; i < MAX_CONTACTS; i ++) if (ContactData[playerid][i][contactExists] && ContactData[playerid][i][contactOwnerID] == AccountData[playerid][pID])
	{
		new numberowner = GetNumberOwner(ContactData[playerid][i][contactNumber]);
		if(!ContactData[playerid][i][contactUnread])
		{
			format(shstr, sizeof(shstr), "%s\t%s\t%s\t%s\n",
				ContactData[playerid][i][contactName],
				ContactData[playerid][i][contactNumber],
				IsPlayerConnected(numberowner) ? ""LIGHTGREEN"(Online)" : ""ORANGE"(Offline)",
				(ContactData[playerid][i][contactBlocked] == 1) ? ""RED"Diblokir" : ""LIGHTGREEN"-");
			
			strcat(sha, shstr);
		}
		else
		{
			format(shstr, sizeof(shstr), "%s\t%s\t%s "LIGHTGREY"[%d belum dibaca]\t%s\n",
				ContactData[playerid][i][contactName],
				ContactData[playerid][i][contactNumber],
				IsPlayerConnected(numberowner) ? ""LIGHTGREEN"(Online)" : ""ORANGE"(Offline)",
				ContactData[playerid][i][contactUnread],
				(ContactData[playerid][i][contactBlocked] == 1) ? ""RED"Diblokir" : ""LIGHTGREEN"-");
			
			strcat(sha, shstr);
		}
		ListedContacts[playerid][count ++] = i;
	}
	
	if(count)
	{
		cache_delete(result);
		if(rowcount == 15) strcat(sha, ""LIGHTGREEN">> Halaman Selanjutnya\t\n");
		if(page != 0) strcat(sha, ""RED"<< Halaman Sebelumnya\t\n");
		ShowPlayerDialog(playerid, DialogContact, DIALOG_STYLE_TABLIST_HEADERS, sprintf(""TCRP"District  "WHITE"- Daftar Kontak | Halaman (%d)", PlayerContactPage[playerid] + 1), sha, "Pilih", "Batal");
		return 1;
	}
	else ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, sprintf(""TCRP"District  "WHITE"- Daftar Kontak | Halaman (%d)", PlayerContactPage[playerid] + 1), "Anda tidak memiliki kontak tersimpan!", "Tutup", ""), PlayerContactPage[playerid] = 0;
	return 1;
}

ShowContactList(playerid)
{
	new 
		count = 0
	;

	AccountData[playerid][CurrentlyReadWA] = false;
	AccountData[playerid][pContact] = -1;

	ClearDialogListitems(playerid);

	AddDialogListitem(playerid, "Nama\tNomor\tStatus\tBlokir");
	for (new i; i < MAX_CONTACTS; i ++) if (ContactData[playerid][i][contactExists] && ContactData[playerid][i][contactOwnerID] == AccountData[playerid][pID])
	{
		new numberowner = GetNumberOwner(ContactData[playerid][i][contactNumber]);
		if(!ContactData[playerid][i][contactUnread])
		{
			AddDialogListitem(playerid, "%s\t%s\t%s\t%s", 
				ContactData[playerid][i][contactName], 
				ContactData[playerid][i][contactNumber], 
				IsPlayerConnected(numberowner) ? ""LIGHTGREEN"(Online)" : ""ORANGE"(Offline)", 
				ContactData[playerid][i][contactBlocked] ? ""RED"Diblokir" : ""LIGHTGREEN"-");
		}
		else
		{
			AddDialogListitem(playerid, "%s\t%s\t%s "LIGHTGREY"[%d belum dibaca]\t%s", 
				ContactData[playerid][i][contactName], 
				ContactData[playerid][i][contactNumber], 
				IsPlayerConnected(numberowner) ? ""LIGHTGREEN"(Online)" : ""ORANGE"(Offline)", 
				ContactData[playerid][i][contactUnread], 
				ContactData[playerid][i][contactBlocked] ? ""RED"Diblokir" : ""LIGHTGREEN"-");
		}
		ListedContacts[playerid][count ++] = i;
	}
	if(count != 0)
		ShowPlayerDialogPages(playerid, "ContactListDialog", DIALOG_STYLE_TABLIST_HEADERS, sprintf(""TCRP"District  "WHITE"- Daftar Kontak (%d/100)", CountPlayerContact(playerid)), "Pilih", "Batal", 15, ""LIGHTGREEN">> Next Page", ""RED"<< Previous Page");
	else
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Daftar Kontak (0/100)", "Anda tidak memiliki kontak tersimpan!", "Tutup", "");
	return 1;
}*/

/*ShowContactList(playerid)
{
	new 
		count = 0,
		shstr[5255]
	;

	AccountData[playerid][CurrentlyReadWA] = false;
	AccountData[playerid][pContact] = -1;

	format(shstr, sizeof(shstr), "Nama\tNomor\tStatus | Pesan\tBlokir\n");
	for (new i; i < MAX_CONTACTS; i++) if (ContactData[playerid][i][contactExists] && ContactData[playerid][i][contactOwnerID] == AccountData[playerid][pID])
	{
		new numberowner = GetNumberOwner(ContactData[playerid][i][contactNumber]);
		if(!ContactData[playerid][i][contactUnread])
		{
			format(shstr, sizeof(shstr), "%s%s\t%s\t%s\t%s\n", shstr, ContactData[playerid][i][contactName], ContactData[playerid][i][contactNumber], IsPlayerConnected(numberowner) ? ""GREEN"(Online)" : ""ORANGE"(Offline)", ContactData[playerid][i][contactBlocked] ? ""RED"Diblokir" : ""GREEN"-");
			// format(shstr, sizeof(shstr), "%s%s | %s %s\n", shstr, ContactData[playerid][i][contactName], ContactData[playerid][i][contactNumber], IsPlayerConnected(numberowner) ? ""GREEN"(Online)" : ""ORANGE"(Offline)");
		}
		else
		{
			format(shstr, sizeof(shstr), "%s%s\t%s\t%s "LIGHTGREY"[%d belum dibaca]\t%s\n", shstr, ContactData[playerid][i][contactName], ContactData[playerid][i][contactNumber], IsPlayerConnected(numberowner) ? ""GREEN"(Online)" : ""ORANGE"(Offline)", ContactData[playerid][i][contactUnread], ContactData[playerid][i][contactBlocked] ? ""RED"Diblokir" : ""GREEN"-");
			// format(shstr, sizeof(shstr), "%s%s | %s %s "LIGHTGREY"[%d belum dibaca]\n", shstr, ContactData[playerid][i][contactName], ContactData[playerid][i][contactNumber], IsPlayerConnected(numberowner) ? ""GREEN"(Online)" : ""ORANGE"(Offline)", ContactData[playerid][i][contactUnread]);
		}
		ListedContacts[playerid][count ++] = i;
	}
	if(count > 0)
		ShowPlayerDialog(playerid, DialogContact, DIALOG_STYLE_TABLIST_HEADERS, sprintf(""TCRP"District  "WHITE"- Daftar Kontak (%d/100)", CountPlayerContact(playerid)), shstr, "Pilih", "Batal");
	else 
		ShowPlayerDialog(playerid, DIALOG_UNUSED, DIALOG_STYLE_MSGBOX, ""TCRP"District  "WHITE"- Daftar Kontak (0/100)", "Anda tidak memiliki kontak tersimpan!", "Tutup", "");
	return 1;
}*/

stock GetNumberOwner(const number[])
{
	foreach(new i : Player) if (IsPlayerConnected(i))
	{
		if(!strcmp(AccountData[i][pPhone], number, false) && PlayerHasItem(i, "Smartphone"))
		{
			return i;
		}
	}
	return INVALID_PLAYER_ID;
}

forward OnContactEditName(playerid, contactIndex, const newname[]);
public OnContactEditName(playerid, contactIndex, const newname[])
{
	static oldname[125];
	format(oldname, sizeof(oldname), ContactData[playerid][contactIndex][contactName]);
	strcpy(ContactData[playerid][contactIndex][contactName], newname);
	ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda mengedit nama kontak %s menjadi %s", oldname, newname));
	
	mysql_tquery(g_SQL, sprintf("UPDATE `contacts` SET `contactName`='%s' WHERE `contactID`=%d", newname, ContactData[playerid][contactIndex][contactID]));
	return 1;
}

forward OnContactEditNumber(playerid, contactIndex, const newnumber[]);
public OnContactEditNumber(playerid, contactIndex, const newnumber[])
{
	static oldnum[125];
	format(oldnum, sizeof(oldnum), ContactData[playerid][contactIndex][contactNumber]);
	strcpy(ContactData[playerid][contactIndex][contactNumber], newnumber);
	ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda mengedit nomor kontak %s menjadi %s", ContactData[playerid][contactIndex][contactName], newnumber));
	
	mysql_tquery(g_SQL, sprintf("UPDATE `contacts` SET `contactNumber`='%s' WHERE `contactID`=%d", newnumber, ContactData[playerid][contactIndex][contactID]));
	return 1;
}

IsNumberAlreadySaved(playerid, const number[])
{
	for(new cid; cid < MAX_CONTACTS; cid ++)
	{
		if(ContactData[playerid][cid][contactExists])
		{
			if(!strcmp(ContactData[playerid][cid][contactNumber], number, false))
				return true;
		}
	}
	return false;
}

CheckNumberBlocked(playerid, const number[])
{
	for(new cid; cid < MAX_CONTACTS; cid ++)
	{
		if(ContactData[playerid][cid][contactExists])
		{
			if(!strcmp(ContactData[playerid][cid][contactNumber], number, false))
			{
				if(ContactData[playerid][cid][contactBlocked])
					return true;
				else
					break;
			}
		}
	}
	return false;
}

GetMySavedContactName(targetid, number[])
{
	new frmtname[24];
	format(frmtname, sizeof(frmtname), "%s", number);
	for(new cid; cid < MAX_CONTACTS; cid ++) 
	{
		if(ContactData[targetid][cid][contactExists])
		{
			if(!strcmp(ContactData[targetid][cid][contactNumber], number, false))
			{
				format(frmtname, sizeof(frmtname), "%s", ContactData[targetid][cid][contactName]);
			}
		}
	}
	return frmtname;
}

CountPlayerContact(playerid)
{
	new count;
	for (new x; x < MAX_CONTACTS; x ++)
	{
		if(ContactData[playerid][x][contactExists])
		{
			count++;
		}
	}
	return count;
}

forward OnContactAdded(playerid, cid);
public OnContactAdded(playerid, cid)
{
	ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Anda berhasil menambahkan %s ke dalam kontak", ContactData[playerid][cid][contactName]));
	return 1;
}

forward OnContactAdd(playerid, id);
public OnContactAdd(playerid, id)
{
	ContactData[playerid][id][contactID] = cache_insert_id();
	return 1;
}

forward LoadPlayerContact(playerid);
public LoadPlayerContact(playerid)
{
	if(cache_num_rows())
	{
		for(new i = 0; i < cache_num_rows() && i < MAX_CONTACTS; i++)
		{
			ContactData[playerid][i][contactExists] = true;
			cache_get_value_name_int(i, "contactID", ContactData[playerid][i][contactID]);
			cache_get_value_name(i, "contactName", ContactData[playerid][i][contactName]);
			cache_get_value_name(i, "contactNumber", ContactData[playerid][i][contactNumber]);
			cache_get_value_name_int(i, "contactUnread", ContactData[playerid][i][contactUnread]);
			cache_get_value_name_int(i, "contactBlocked", ContactData[playerid][i][contactBlocked]);
			cache_get_value_name_int(i, "contactOwner", ContactData[playerid][i][contactOwnerID]);
		}
	}
	return 1;
}

forward LoadContact(playerid);
public LoadContact(playerid)
{
	new count = cache_num_rows();
	if(count)
  	{
		for (new i = 0; i < count && i < MAX_CONTACTS; i ++)
		{
			ContactData[playerid][i][contactExists] = true;
			cache_get_value_name(i, "contactName", ContactData[playerid][i][contactName]);
		    cache_get_value_name_int(i, "contactID", ContactData[playerid][i][contactID]);
		    cache_get_value_name_int(i, "contactOwner", ContactData[playerid][i][contactOwnerID]);
		    cache_get_value_name_int(i, "contactUnread", ContactData[playerid][i][contactUnread]);
			cache_get_value_name_int(i, "contactBlocked", ContactData[playerid][i][contactBlocked]);
		    cache_get_value_name(i, "contactNumber", ContactData[playerid][i][contactNumber]);
		}
		printf("Contact yang dimuat oleh %s: %d", AccountData[playerid][pName], count);
	}
}

forward OnWhatsappSent(playerid, targetid, contactSelected, serverid);
public OnWhatsappSent(playerid, targetid, contactSelected, serverid)
{
	ShowTDN(playerid, NOTIFICATION_SUKSES, sprintf("Pesan berhasil dikirim ke %s", ContactData[playerid][contactSelected][contactName]));
	ShowTDN(targetid, NOTIFICATION_WARNING, sprintf("Anda mendapat pesan Whatsapp baru dari %s!", GetMySavedContactName(targetid, AccountData[playerid][pPhone])));

	new cidt = AccountData[targetid][pContact];
	if(AccountData[targetid][CurrentlyReadWA])
	{
		if(!strcmp(ContactData[targetid][cidt][contactNumber], AccountData[playerid][pPhone], false))
		{
			new query[512], harlem[128], Cache:execute;
			mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `whatsapp_chats` WHERE `ID`=%d ORDER BY `chatTimestamp` ASC LIMIT 30", serverid);
			execute = mysql_query(g_SQL, query, true);
			new rows = cache_num_rows();
			if(rows)
			{
				if(rows >= 30)
				{
					mysql_format(g_SQL, harlem, sizeof(harlem), "DELETE FROM `whatsapp_chats` WHERE `ID`=%d", serverid);
					mysql_tquery(g_SQL, harlem);
				}

				ContactData[targetid][cidt][contactUnread] = 0;
				mysql_format(g_SQL, query, sizeof(query), "UPDATE `contacts` SET `contactUnread`=0 WHERE `contactID`=%d", ContactData[targetid][cidt][contactID]);
				
				new list[2500], date[64], issuer[24], watext[128];
				
				format(list, sizeof(list), "Tanggal\tPengirim\tPesan\n");
				for(new i; i < rows; ++i)
				{
					cache_get_value_name(i, "chatTimestamp", date);
					cache_get_value_name(i, "chatSender", issuer);
					cache_get_value_name(i, "chatMessage", watext);

					format(list, sizeof(list), "%s%s\t%s\t%s\n", list, date, issuer, watext);
				}
				new title[100];
				format(title, sizeof(title), "WhatsApp Chat - %s", ContactData[targetid][cidt][contactName]);
				ShowPlayerDialog(targetid, DIALOG_WHATSAPP_CHAT, DIALOG_STYLE_TABLIST_HEADERS, title, list, "Kirim", "Kembali");
			}
			else 
			{
				new list[208], title[100];
				format(list, sizeof(list), "Tanggal\tPengirim\tPesan\n");
				format(list, sizeof(list), "%sPesan dan panggilan terenkripsi secara end-to-end.", list);
				format(title, sizeof(title), "WhatsApp Chat - %s", ContactData[targetid][cidt][contactName]);
				ShowPlayerDialog(targetid, DIALOG_WHATSAPP_CHAT_EMPTY, DIALOG_STYLE_TABLIST_HEADERS, title, list, "Kirim", "Kembali");
			}

			cache_delete(execute);
		}
	}

	new query[512];
	mysql_format(g_SQL, query, sizeof(query), "SELECT * FROM `whatsapp_chats` WHERE `ID`=%d ORDER BY `chatTimestamp` ASC LIMIT 30", serverid);
	mysql_query(g_SQL, query);
	new rows = cache_num_rows();
	if(rows)
	{
		if(rows >= 30)
		{
			mysql_format(g_SQL, query, sizeof(query), "DELETE FROM `whatsapp_chats` WHERE `ID`=%d", serverid);
			mysql_tquery(g_SQL, query);
		}

		ContactData[playerid][contactSelected][contactUnread] = 0;
		mysql_format(g_SQL, query, sizeof(query), "UPDATE `contacts` SET `contactUnread`=0 WHERE `contactID`=%d", ContactData[playerid][contactSelected][contactID]);
		new list[2500], date[64], issuer[24], watext[128];

		format(list, sizeof(list), "Tanggal\tPengirim\tPesan\n");
		for(new i; i < rows; ++i)
		{
			cache_get_value_name(i, "chatTimestamp", date);
			cache_get_value_name(i, "chatSender", issuer);
			cache_get_value_name(i, "chatMessage", watext);

			format(list, sizeof(list), "%s%s\t%s\t%s\n", list, date, issuer, watext);
		}
		new title[100];
		format(title, sizeof(title), "WhatsApp Chat - %s", ContactData[playerid][contactSelected][contactName]);
		ShowPlayerDialog(playerid, DIALOG_WHATSAPP_CHAT, DIALOG_STYLE_TABLIST_HEADERS, title, list, "Kirim", "Kembali");
	}
	else 
	{
		new list[208], title[100];
		format(list, sizeof(list), "Tanggal\tPengirim\tPesan\n");
		format(list, sizeof(list), "%sPesan dan panggilan terenkripsi secara end-to-end.", list);
		format(title, sizeof(title), "WhatsApp Chat - %s", ContactData[playerid][contactSelected][contactName]);
		ShowPlayerDialog(playerid, DIALOG_WHATSAPP_CHAT_EMPTY, DIALOG_STYLE_TABLIST_HEADERS, title, list, "Kirim", "Kembali");
	}
	return 1;
}
forward OnPlayerAdvert(playerid);
public OnPlayerAdvert(playerid)
{
	ShowTDN(playerid, NOTIFICATION_SUKSES, "Anda berhasil membuat iklan");
	mysql_query(g_SQL, "SELECT * FROM `yellowpages` WHERE `ID`=1 ORDER BY `YellowDate` ASC LIMIT 30");
	new rowcount = cache_num_rows(), list[4500], tempYellowFrom[24], tempYellowDate[64], tempYellowText[128], tempYellowPhone[24];
	if(rowcount)
	{
		if(rowcount >= 30)
		{
			mysql_tquery(g_SQL, "DELETE FROM `yellowpages` WHERE `ID`=1");
		}

		format(list, sizeof(list), "Nama\tTanggal\tIklan\n");
		for(new i; i < rowcount; ++i)
		{
			cache_get_value_name(i, "YellowFrom", tempYellowFrom);
			cache_get_value_name(i, "YellowPhone", tempYellowPhone);
			cache_get_value_name(i, "YellowDate", tempYellowDate);
			cache_get_value_name(i, "YellowText", tempYellowText);

			format(list, sizeof(list), "%s"YELLOW"%s - %s\t"LIGHTGREY"%s\t"WHITE"%s\n", list, tempYellowFrom, tempYellowPhone, tempYellowDate, tempYellowText);
		}
		ShowPlayerDialog(playerid, DIALOG_YELLOW_PAGE, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Yellow Pages", list, "Iklan", "Kembali");
	}
	else
	{
		format(list, sizeof(list), "Nama\tTanggal\tIklan\n");
		format(list, sizeof(list), "%sJadilah orang pertama yang membuat iklan!", list);
		ShowPlayerDialog(playerid, DIALOG_YELLOW_PAGE_EMPTY, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Yellow Pages", list, "Iklan", "Kembali");
	}
	return 1;
}
forward OnPlayerTweet(playerid);
public OnPlayerTweet(playerid)
{
	mysql_query(g_SQL, "SELECT * FROM `tweets` WHERE `ID`=1 ORDER BY `TwitterDate` ASC LIMIT 30");
	new rows = cache_num_rows(), list[4500], tempTweetFrom[24], tempTweetDate[64], tempTweetText[128];
	if(rows)
	{
		if(rows >= 30)
		{
			mysql_tquery(g_SQL, "DELETE FROM `tweets` WHERE `ID`=1");
		}

		format(list, sizeof(list), "Username\tTanggal\tPostingan\n");
		for(new i; i < rows; ++i)
		{
			cache_get_value_name(i, "TwitterFrom", tempTweetFrom);
			cache_get_value_name(i, "TwitterDate", tempTweetDate);
			cache_get_value_name(i, "TwitterText", tempTweetText);

			format(list, sizeof(list), "%s"VTWITTER"@%s\t"GRAY"%s\t"WHITE"%s\n", list, tempTweetFrom, tempTweetDate, tempTweetText);
		}
		ShowPlayerDialog(playerid, DIALOG_TWITTER_POST, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Tweets", list, "Tweet", "Kembali");
	}
	else 
	{
		format(list, sizeof(list), "Username\tTanggal\tPostingan\n");
		format(list, sizeof(list), "%sJadilah orang pertama yang membagikan Tweet", list);
		ShowPlayerDialog(playerid, DIALOG_TWITTER_POST_EMPTY, DIALOG_STYLE_TABLIST_HEADERS, ""TCRP"District  "WHITE"- Tweets", list, "Tweet", "Kembali");
	}
	return 1;
}
