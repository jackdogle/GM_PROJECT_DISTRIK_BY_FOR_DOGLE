#include <YSI\y_hooks>

//Enums
#define MAX_REPORTS (50)

enum reportData {
    bool:rExists,
    rType,
    rPlayer,
    rText[128 char]
};
new ReportData[MAX_REPORTS][reportData],
    Iterator:Reports<MAX_REPORTS>;

new ListReport[MAX_PLAYERS][MAX_REPORTS];
new ReportDelays[MAX_PLAYERS] = {0, ...};


Report_GetCount(playerid)
{
    new count;

    foreach(new i:Reports)
    {
        if(ReportData[i][rExists] && ReportData[i][rPlayer] == playerid)
        {
			count++;
        }
    }
    return count;
}

Report_Count()
{
    new count;
    foreach(new i:Reports) if(ReportData[i][rExists]){
        count++;
    }
    return count;
}

Report_Clear(playerid)
{
    foreach(new i:Reports)
    {
        if(ReportData[i][rExists] && ReportData[i][rPlayer] == playerid)
        {
            Report_Remove(i);
        }
    }
}

Report_Add(playerid, const text[], type = 1)
{
    for(new i; i< MAX_REPORTS; i++)
    {
        if(!ReportData[i][rExists])
        {
            ReportData[i][rExists] = true;
            ReportData[i][rType] = type;
            ReportData[i][rPlayer] = playerid;
            Iter_Add(Reports, i);
            strpack(ReportData[i][rText], text, 128 char);
            return i;
        }
    }
    return -1;
}

Report_Remove(reportid)
{
    if(reportid != -1 && ReportData[reportid][rExists] == true)
    {
        ReportData[reportid][rExists] = false;
        ReportData[reportid][rPlayer] = INVALID_PLAYER_ID;
        Iter_Remove(Reports, reportid);
    }
    return 1;
}

CMD:ar(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1) return PermissionError(playerid);

    new reportid, text[128];
    if(sscanf(params, "ds[128]", reportid, text)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/ar [#Report ID] [Jawaban]");
    if(reportid < 0 || reportid >= MAX_REPORTS || !ReportData[reportid][rExists]) return ShowTDN(playerid, NOTIFICATION_ERROR, "#Report ID tidak valid, gunakan ~y~'/reports'~w~ untuk melihat daftar laporan!");
    if(ReportData[reportid][rPlayer] == INVALID_PLAYER_ID) return ShowTDN(playerid, NOTIFICATION_ERROR, "Laporan sudah berakhir, pemain tersebut telah keluar kota!");

    new targetid = ReportData[reportid][rPlayer];
    SendClientMessageEx(targetid, X11_RED, "[Report Answer]: "RED"%s"WHITE" telah menjawab laporan anda", AccountData[playerid][pAdminname]);
    SendClientMessageEx(targetid, -1, "~> %s", text);
    if(targetid != playerid) 
    {
        AccountData[playerid][aReceivedReports] ++;
    }
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menjawab report dari "YELLOW"%s(%d)", AccountData[playerid][pAdminname], ReturnName(targetid), targetid);
    Report_Remove(reportid);
    return 1;
}

CMD:report(playerid, params[])
{
    new shstr[128], reportid = -1;
    if(sscanf(params, "s[128]", shstr)) return ShowTDN(playerid, NOTIFICATION_SYNTAX, "/report [message]");
    if(Report_GetCount(playerid) >= 1) return ShowTDN(playerid, NOTIFICATION_ERROR, "Kamu sudah membuat laporan sebelumnya, tunggu laporan anda diproses terlebih dahulu!");
    if(ReportDelays[playerid] >= gettime()) return ShowTDN(playerid, NOTIFICATION_ERROR, sprintf("Setidaknya anda harus menunggu %d detik!", ReportDelays[playerid] - gettime()));
    if((reportid = Report_Add(playerid, shstr)) != -1)
    {
        foreach(new i : Player) if (AccountData[i][IsLoggedIn] && AccountData[i][pTogAC]) if (AccountData[i][pAdmin] >= 1 || AccountData[i][pTheStars] >= 1)
        {
            SendClientMessageEx(i, X11_RED, "[Report #%d]:"WHITE" %s [%s] (%d)", reportid, ReturnName(playerid), AccountData[playerid][pUCP], playerid);
            SendClientMessageEx(i, -1, "~> %s", shstr);
        }
        ReportDelays[playerid] = gettime() + 120;
        Info(playerid, "Berhasil mengirim laporan, tunggu hingga laporanmu dijawab");
    }
    else ShowTDN(playerid, NOTIFICATION_ERROR, "Laporan penuh, harap tunggu.");
    return 1;
}

CMD:reports(playerid, params[])
{
    if(AccountData[playerid][pAdmin] < 1 && AccountData[playerid][pTheStars] < 1) return PermissionError(playerid);

    new shstr[3046], frmtx[525], count = 0;
    format(shstr, sizeof(shstr), "#ID\tPlayer\tReported\n");
    foreach(new x:Reports)
    {
        if(ReportData[x][rExists])
        {
            strunpack(frmtx, ReportData[x][rText]);

            format(shstr, sizeof(shstr), "%s#%d\t[%s] %s(%d)\t%.32s...\n", shstr, x, AccountData[ReportData[x][rPlayer]][pUCP], AccountData[ReportData[x][rPlayer]][pName], ReportData[x][rPlayer], frmtx);
            ListReport[playerid][count ++] = x;
        }
    }

    if(count == 0)
        Error(playerid, "Tidak ada laporan aktif saat ini!");
    else
        ShowPlayerDialog(playerid, DIALOG_REPORTS, DIALOG_STYLE_TABLIST_HEADERS, sprintf("Daftar Laporan Actived ( "RED"%d Laporan "WHITE")", Report_Count()), shstr, "Cek", "Batal");
    return 1;
}

CMD:clearreports(playerid, params[])
{
    if(!SQL_IsCharacterLogged(playerid))
        return 0;
    
    if(AccountData[playerid][pAdmin] < 3) return PermissionError(playerid);

    new 
        count;
    
    foreach(new i:Reports)
    {
        if(ReportData[i][rExists]) {
            Report_Remove(i);
            count ++;
        }
    }
    if(!count)
        return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak ada laporan untuk dihapus!");
    
    SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menghapus semua laporan yang ada di server.", GetAdminName(playerid));
    return 1;
}

hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if(dialogid == DIALOG_REPORTS)
    {
        if(response)
        {
            new reportid = ListReport[playerid][listitem], frmxt[525], shstr[598];
            if(!ReportData[reportid][rExists]) return ShowTDN(playerid, NOTIFICATION_ERROR, "#Report ID tidak valid, gunakan ~y~'/reports'~w~ untuk melihat daftar laporan!");

            strunpack(frmxt, ReportData[reportid][rText]);
            format(shstr, sizeof(shstr), ""WHITE"Player Detail: "DEEPSKYBLUE1"%s [%s] (%d)\n"WHITE"Reports: "YELLOW"%s\n"WHITE"Answer: "LIGHTGREEN"(Input Below)", 
            ReturnName(ReportData[reportid][rPlayer]), AccountData[ReportData[reportid][rPlayer]][pUCP], ReportData[reportid][rPlayer], frmxt);
            ShowPlayerDialog(playerid, DIALOG_REPORTSREPLY, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Answer Report", shstr, "Answer", "Cancel");

            SetPVarInt(playerid, "ReportListitemID", reportid);
        }
        else return 0;
    }
    else if(dialogid == DIALOG_REPORTSREPLY)
    {
        if(response)
        {
            new reportid = GetPVarInt(playerid, "ReportListitemID"), shstr[598], frmxt[525];

            if(!ReportData[reportid][rExists]) return ShowTDN(playerid, NOTIFICATION_ERROR, "#Report ID tidak valid, gunakan ~y~'/reports'~w~ untuk melihat daftar laporan!");
            if(isnull(inputtext))
            {
                format(shstr, sizeof(shstr), ""RED"Error:"WHITE" Tidak dapat diisi kosong!\n"WHITE"Player Detail: "DEEPSKYBLUE1"%s [%s] (%d)\n"WHITE"Reports: "YELLOW"%s\n"WHITE"Answer: "LIGHTGREEN"(Input Below)", 
                ReturnName(ReportData[reportid][rPlayer]), AccountData[ReportData[reportid][rPlayer]][pUCP], ReportData[reportid][rPlayer], frmxt);
                return ShowPlayerDialog(playerid, DIALOG_REPORTSREPLY, DIALOG_STYLE_INPUT, ""TCRP"District  "WHITE"- Answer Report", shstr, "Answer", "Cancel");
            }

            new targetid = ReportData[reportid][rPlayer];
            SendClientMessageEx(targetid, X11_RED, "[Report Answer]: "RED"%s"WHITE" telah menjawab laporan anda", AccountData[playerid][pAdminname]);
            SendClientMessageEx(targetid, -1, "~> %s", inputtext);
            if(ReportData[reportid][rPlayer] != playerid) AccountData[playerid][aReceivedReports] ++;
            SendStaffMessage(X11_ARWIN, ""RED"%s"ARWIN1" telah menerima laporan dari "YELLOW"%s(%d)", AccountData[playerid][pAdminname], AccountData[ReportData[reportid][rPlayer]][pName], ReportData[reportid][rPlayer]);
            Report_Remove(reportid);
            SetPVarInt(playerid, "ReportListitemID", -1);
        }
        else 
        {
            callcmd::reports(playerid, "\1");
            SetPVarInt(playerid, "ReportListitemID", -1);
        }
    }
    return 1;
}

ptask Player_ResetAsk[1000](playerid)
{
    if(!AccountData[playerid][IsLoggedIn])
        return 0;
    
    if(Report_GetCount(playerid) >= 1 && ReportDelays[playerid] <= gettime())
    {
        Report_Clear(playerid);
        SendClientMessage(playerid, X11_DARKORANGE, "<!> Laporanmu tidak diproses, kamu dapat menggunakan perintah "YELLOW"'/report'"DARKORANGE" lagi.");
    }

    if(Ask_GetCount(playerid) >= 1 && AccountData[playerid][pAskTime] <= gettime())
    {
        Ask_Clear(playerid);
        SendClientMessage(playerid, X11_DARKORANGE, "<!> Pertanyaanmu tidak dijawab, kamu dapat menggunakan perintah "YELLOW"'/ask'"DARKORANGE" lagi.");
    }
    return 1;
}
