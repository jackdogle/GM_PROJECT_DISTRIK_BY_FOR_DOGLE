#include <YSI\y_hooks>
//Enums
#define MAX_ASKS (50)
new ListAsks[MAX_PLAYERS][MAX_ASKS];

enum askData {
    bool:askExists,
    askType,
    askPlayer,
    askText[128 char]
};
new AskData[MAX_ASKS][askData],
    Iterator:Asks<MAX_ASKS>;


Ask_GetCount(playerid)
{
    new count;

    foreach(new i:Asks)
    {
        if(AskData[i][askExists] && AskData[i][askPlayer] == playerid)
        {
			count++;
        }
    }
    return count;
}

Ask_Count()
{
    new askcount;

    foreach(new i:Asks) if (AskData[i][askExists]) {
        askcount++;
    }
    return askcount;
}

Ask_Clear(playerid)
{
    foreach(new i:Asks)
    {
        if(AskData[i][askExists] && AskData[i][askPlayer] == playerid)
        {
            Ask_Remove(i);
        }
    }
}

Ask_Add(playerid, const text[], type = 1)
{
    for (new i = 0; i != MAX_ASKS; i ++)
    {
        if(!AskData[i][askExists])
        {
            AskData[i][askExists] = true;
            AskData[i][askType] = type;
            AskData[i][askPlayer] = playerid;
            Iter_Add(Asks, i);
            strpack(AskData[i][askText], text, 128 char);
            return i;
        }
    }
    return -1;
}

Ask_Remove(reportid)
{
    if(reportid != -1 && AskData[reportid][askExists] == true)
    {
        AskData[reportid][askExists] = false;
        AskData[reportid][askPlayer] = INVALID_PLAYER_ID;
        Iter_Remove(Asks, reportid);
    }
    return 1;
}

CMD:ask(playerid, params[])
{
    new shstr[128], askid = -1;
    if(sscanf(params, "s[128]", shstr)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/ask [message]");
    if(Ask_GetCount(playerid) >= 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu sudah membuat pertanyaan sebelumnya, tunggu pertanyaan anda dijawab terlebih dahulu!");
    if(AccountData[playerid][pAskTime] >= gettime()) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Setidaknya anda harus menunggu %d detik!", AccountData[playerid][pAskTime] - gettime()));
    if((askid = Ask_Add(playerid, shstr)) != -1)
    {
        foreach(new i : Player) if (AccountData[i][IsLoggedIn] && AccountData[i][pTogAC]) if (AccountData[i][pAdmin] >= 1 || AccountData[i][pTheStars] >= 1)
        {
            SendClientMessageEx(i, X11_YELLOW, "[Ask #%d]:"WHITE" %s [%s] (%d)", askid, ReturnName(playerid), AccountData[playerid][pUCP], playerid);
            SendClientMessageEx(i, -1, "~> %s", shstr);
        }
        AccountData[playerid][pAskTime] = gettime() + 120;
        Info(playerid, "Anda berhasil mengajukan pertanyaan, tunggu hingga pertanyaanmu dibalas");
    }
    else ShowTDN(playerid, NOTIFICATION_ERROR, "Pertanyaan server sedang penuh!");
    return 1;
}

CMD:asks(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1)
        return PermissionError(playerid);

    new list[1048], text[255], count = 0;
    format(list, sizeof(list), "#ID\tPlayer\tAsked\n");
    foreach(new i:Asks) if (AskData[i][askExists])
    {
        strunpack(text, AskData[i][askText]);

        format(list, sizeof(list), "%s#%d\t[%s] %s(%d)\t%.32s...\n", list, i, AccountData[AskData[i][askPlayer]][pUCP], AccountData[AskData[i][askPlayer]][pName], AskData[i][askPlayer], text);
        ListAsks[playerid][count++] = i;
    }

    if(count == 0)
        Error(playerid, "Tidak ada pertanyaan aktif saat ini!");
    else
        ShowPlayerDialog(playerid, DIALOG_ASKS, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Daftar Pertanyaan Actived ( "YELLOW"%d Pertanyaan"WHITE" )", Ask_Count()), list, "Cek", "Tutup");
    return 1;
}

CMD:clearask(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 3) return PermissionError(playerid);
    
    new
        count;

    foreach(new i:Asks)
    {
        if(AskData[i][askExists]) {
            Ask_Remove(i);
            count++;
        }
    }
    if(!count)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada Pertanyaan untuk dihapus.");
            
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" Menghapus semua pertanyaan di server.", GetAdminName(playerid));
    return 1;
}

CMD:ans(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1) return PermissionError(playerid);

    new askid, text[128];
    if(sscanf(params, "ds[128]", askid, text)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/ans [#Ask ID] [Jawaban]");
    if(askid < 0 || askid >= MAX_ASKS || !AskData[askid][askExists]) return ShowTDN(playerid, NOTIFICATION_ERROR, "#ID Ask tidak valid, gunakan ~y~'/asks'~w~ untuk melihat daftar!");
    if(AskData[askid][askPlayer] == INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Pertanyaan telah berakhir, pemain tersebut telah keluar kota!");
    
    new targetid = AskData[askid][askPlayer];
    SendClientMessageEx(targetid, X11_YELLOW, "[Ask Answer]: "RED"%s"WHITE" telah menjawab pertanyaan anda", AccountData[playerid][pAdminname]);
    SendClientMessageEx(targetid, -1, "~> %s", text);
    
    if(targetid != playerid)
    {
        AccountData[playerid][aReceivedReports] ++;
    }
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menjawab pertanyaan dari "YELLOW"%s(%d)", AccountData[playerid][pAdminname], ReturnName(targetid), targetid);
    Ask_Remove(askid);
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case DIALOG_ASKS:
        {
            if(!response) return 1;
            new id = ListAsks[playerid][listitem];
            if(!AskData[id][askExists]) return ShowTDN(playerid, NOTIFICATION_ERROR, "#ID Ask tidak valid, gunakan ~y~'/asks'~w~ untuk melihat daftar!");
            
            new frmtask[598], sha[525];
            strunpack(sha, AskData[id][askText]);
            format(frmtask, sizeof(frmtask), ""WHITE"Player Detail: "DEEPSKYBLUE1"%s [%s] (%d)\n"WHITE"Question: "YELLOW"%s\n"WHITE"Answer: "LIGHTGREEN"(Input Below)", 
            ReturnName(AskData[id][askPlayer]), AccountData[AskData[id][askPlayer]][pUCP], AskData[id][askPlayer], sha);
            ShowPlayerDialog(playerid, DIALOG_ASKSREPLY, DIALOG_STYLE_INPUT, "Answer Question", frmtask, "Answer", "Cancel");
            SetPVarInt(playerid, "ListASKS", id);
        }
        case DIALOG_ASKSREPLY:
        {
            if(!response) return callcmd::asks(playerid, "\1"), SetPVarInt(playerid, "ListASKS", -1);
            new id = GetPVarInt(playerid, "ListASKS"), frmtask[596], sha[525];

            if(!AskData[id][askExists]) return ShowTDN(playerid, NOTIFICATION_ERROR, "#ID Ask tidak valid, gunakan ~y~'/asks'~w~ untuk melihat daftar!");
            strunpack(sha, AskData[id][askText]);
            if(isnull(inputtext))
            {
                format(frmtask, sizeof(frmtask), ""RED"Error:"WHITE" Tidak dapat diisi kosong!\n"WHITE"Player Detail: "DEEPSKYBLUE1"P%d:"WHITE" %s\nQuestion: "YELLOW"%s\n"WHITE"Answer: "LIGHTGREEN"(Input Below)", AskData[id][askPlayer], AccountData[AskData[id][askPlayer]][pName], sha);
                ShowPlayerDialog(playerid, DIALOG_ASKSREPLY, DIALOG_STYLE_INPUT, "Answer Question", frmtask, "Answer", "Cancel");
                return 1;
            }

            new targetid = AskData[id][askPlayer];
            SendClientMessageEx(targetid, X11_YELLOW, "[Ask Answer]: "RED"%s"WHITE" telah menjawab pertanyaan anda", AccountData[playerid][pAdminname]);
            SendClientMessageEx(targetid, -1, "~> %s", inputtext);
            if(AskData[id][askPlayer] != playerid) AccountData[playerid][aReceivedReports] ++;
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menerima pertanyaan dari "YELLOW"%s(%d)", AccountData[playerid][pAdminname], AccountData[AskData[id][askPlayer]][pName], AskData[id][askPlayer]);
            Ask_Remove(id);

            SetPVarInt(playerid, "ListASKS", -1);
        }
    }
    return 1;
}