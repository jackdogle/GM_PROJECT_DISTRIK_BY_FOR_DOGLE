#define TOTAL_ANIMS (sizeof(ANIM_LIST))
#define ANIMS_PER_PAGE (10)
#define TOTAL_PAGES (((TOTAL_ANIMS + ANIMS_PER_PAGE - 1) / ANIMS_PER_PAGE))

new gAnimPage[MAX_PLAYERS];
new Text: ElistTD[43];

new const ANIM_LIST[][32] =
{
    "liptang",
    "angkatbox",
    "camera",
    "wuzi",
    "liptang2",
    "liptang3",
    "liptang4",
    "rokok",
    "rokok2",
    "rokok3",
    "medis",
    "medis2",
    "cium",
    "cium2",
    "cium3",
    "cium4",
    "cium5",
    "cium6",
    "joget",
    "joget2",
    "joget3",
    "joget4",
    "joget5",
    "joget6",
    "joget7",
    "joget8",
    "joget9",
    "joget10",
    "onani",
    "onani2",
    "onani3",
    "angtang",
    "baseball",
    "baseball2",
    "baseball3",
    "baseball4",
    "baseball5",
    "tampar",
    "bartender",
    "bartender2",
    "bartender3",
    "bartender4",
    "bartender5",
    "bartender6",
    "bartender7",
    "bartender8",
    "geledah",
    "santai",
    "santai2",
    "santai3",
    "santai4",
    "santai5",
    "gang",
    "gang2",
    "gang3",
    "gang4",
    "gang5",
    "gang6",
    "gang7",
    "gang8",
    "gang9",
    "bicara",
    "bicara2",
    "bicara3",
    "bicara4",
    "bicara5",
    "bicara6",
    "angkat",
    "angkat",
    "angkat2",
    "angkat3",
    "angkat4",
    "kesakitan",
    "turu",
    "turu2",
    "lompat",
    "mutah",
    "sorak",
    "sorak2",
    "sorak3",
    "sorak4",
    "sorak5",
    "sorak6",
    "sorak7",
    "sorak8",
    "lambai",
    "lambai2",
    "lambai3",
    "pilok",
    "lempar",
    "kerja",
    "kerja2",
    "kerja3",
    "kerja4",
    "kerja5",
    "kerja6",
    "tusuk",
    "tusuk2",
    "tertusuk",
    "dj",
    "dj2",
    "dj3",
    "nodong",
    "nodong2",
    "nodong3",
    "nodong4",
    "kungfu",
    "nunduk",
    "mabuk",
    "nangis",
    "lelah",
    "lelah2",
    "duduk",
    "duduk2",
    "duduk3",
    "duduk4",
    "duduk5",
    "duduk6",
    "jarteng",
    "ped",
    "ped2",
    "ped3",
    "ped4",
    "ped5",
    "ped6",
    "ped7",
    "ped8",
    "ped9",
    "ped10",
    "ped11",
    "ped12",
    "ped13",
    "ped14",
    "ped15",
    "ped16",
    "kencing",
    "pusing",
    "nunjuk",
    "gatal",
    "x"
};

CreateElistTD()
{
    ElistTD[0] = TextDrawCreate(485.000, 151.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[0], 114.000, 44.000);
    TextDrawAlignment(ElistTD[0], 1);
    TextDrawColor(ElistTD[0], 512819104);
    TextDrawSetShadow(ElistTD[0], 0);
    TextDrawSetOutline(ElistTD[0], 0);
    TextDrawBackgroundColor(ElistTD[0], 255);
    TextDrawFont(ElistTD[0], 4);
    TextDrawSetProportional(ElistTD[0], 1);

    ElistTD[1] = TextDrawCreate(485.000, 195.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[1], 114.000, 16.000);
    TextDrawAlignment(ElistTD[1], 1);
    TextDrawColor(ElistTD[1], 175);
    TextDrawSetShadow(ElistTD[1], 0);
    TextDrawSetOutline(ElistTD[1], 0);
    TextDrawBackgroundColor(ElistTD[1], 255);
    TextDrawFont(ElistTD[1], 4);
    TextDrawSetProportional(ElistTD[1], 1);

    ElistTD[2] = TextDrawCreate(488.000, 196.000, "LD_BEAT:chit");
    TextDrawTextSize(ElistTD[2], 7.000, 8.000);
    TextDrawAlignment(ElistTD[2], 1);
    TextDrawColor(ElistTD[2], -1);
    TextDrawSetShadow(ElistTD[2], 0);
    TextDrawSetOutline(ElistTD[2], 0);
    TextDrawBackgroundColor(ElistTD[2], 255);
    TextDrawFont(ElistTD[2], 4);
    TextDrawSetProportional(ElistTD[2], 1);

    ElistTD[3] = TextDrawCreate(486.000, 203.000, "LD_BEAT:chit");
    TextDrawTextSize(ElistTD[3], 12.000, 8.000);
    TextDrawAlignment(ElistTD[3], 1);
    TextDrawColor(ElistTD[3], -1);
    TextDrawSetShadow(ElistTD[3], 0);
    TextDrawSetOutline(ElistTD[3], 0);
    TextDrawBackgroundColor(ElistTD[3], 255);
    TextDrawFont(ElistTD[3], 4);
    TextDrawSetProportional(ElistTD[3], 1);

    ElistTD[4] = TextDrawCreate(499.000, 198.000, "Emote Animations");
    TextDrawLetterSize(ElistTD[4], 0.140, 0.999);
    TextDrawAlignment(ElistTD[4], 1);
    TextDrawColor(ElistTD[4], -1);
    TextDrawSetShadow(ElistTD[4], 0);
    TextDrawSetOutline(ElistTD[4], 0);
    TextDrawBackgroundColor(ElistTD[4], 150);
    TextDrawFont(ElistTD[4], 1);
    TextDrawSetProportional(ElistTD[4], 1);

    ElistTD[5] = TextDrawCreate(585.000, 198.000, "01/14");
    TextDrawLetterSize(ElistTD[5], 0.140, 0.999);
    TextDrawAlignment(ElistTD[5], 1);
    TextDrawColor(ElistTD[5], -1);
    TextDrawSetShadow(ElistTD[5], 0);
    TextDrawSetOutline(ElistTD[5], 0);
    TextDrawBackgroundColor(ElistTD[5], 150);
    TextDrawFont(ElistTD[5], 1);
    TextDrawSetProportional(ElistTD[5], 1);

    ElistTD[6] = TextDrawCreate(485.000, 211.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[6], 114.000, 16.000);
    TextDrawAlignment(ElistTD[6], 1);
    TextDrawColor(ElistTD[6], 175);
    TextDrawSetShadow(ElistTD[6], 0);
    TextDrawSetOutline(ElistTD[6], 0);
    TextDrawBackgroundColor(ElistTD[6], 255);
    TextDrawFont(ElistTD[6], 4);
    TextDrawSetProportional(ElistTD[6], 1);
    TextDrawSetSelectable(ElistTD[6], 1);

    ElistTD[7] = TextDrawCreate(485.000, 227.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[7], 114.000, 16.000);
    TextDrawAlignment(ElistTD[7], 1);
    TextDrawColor(ElistTD[7], 175);
    TextDrawSetShadow(ElistTD[7], 0);
    TextDrawSetOutline(ElistTD[7], 0);
    TextDrawBackgroundColor(ElistTD[7], 255);
    TextDrawFont(ElistTD[7], 4);
    TextDrawSetProportional(ElistTD[7], 1);
    TextDrawSetSelectable(ElistTD[7], 1);

    ElistTD[8] = TextDrawCreate(485.000, 243.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[8], 114.000, 16.000);
    TextDrawAlignment(ElistTD[8], 1);
    TextDrawColor(ElistTD[8], 175);
    TextDrawSetShadow(ElistTD[8], 0);
    TextDrawSetOutline(ElistTD[8], 0);
    TextDrawBackgroundColor(ElistTD[8], 255);
    TextDrawFont(ElistTD[8], 4);
    TextDrawSetProportional(ElistTD[8], 1);
    TextDrawSetSelectable(ElistTD[8], 1);

    ElistTD[9] = TextDrawCreate(485.000, 259.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[9], 114.000, 16.000);
    TextDrawAlignment(ElistTD[9], 1);
    TextDrawColor(ElistTD[9], 175);
    TextDrawSetShadow(ElistTD[9], 0);
    TextDrawSetOutline(ElistTD[9], 0);
    TextDrawBackgroundColor(ElistTD[9], 255);
    TextDrawFont(ElistTD[9], 4);
    TextDrawSetProportional(ElistTD[9], 1);
    TextDrawSetSelectable(ElistTD[9], 1);

    ElistTD[10] = TextDrawCreate(485.000, 275.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[10], 114.000, 16.000);
    TextDrawAlignment(ElistTD[10], 1);
    TextDrawColor(ElistTD[10], 175);
    TextDrawSetShadow(ElistTD[10], 0);
    TextDrawSetOutline(ElistTD[10], 0);
    TextDrawBackgroundColor(ElistTD[10], 255);
    TextDrawFont(ElistTD[10], 4);
    TextDrawSetProportional(ElistTD[10], 1);
    TextDrawSetSelectable(ElistTD[10], 1);

    ElistTD[11] = TextDrawCreate(485.000, 291.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[11], 114.000, 16.000);
    TextDrawAlignment(ElistTD[11], 1);
    TextDrawColor(ElistTD[11], 175);
    TextDrawSetShadow(ElistTD[11], 0);
    TextDrawSetOutline(ElistTD[11], 0);
    TextDrawBackgroundColor(ElistTD[11], 255);
    TextDrawFont(ElistTD[11], 4);
    TextDrawSetProportional(ElistTD[11], 1);
    TextDrawSetSelectable(ElistTD[11], 1);

    ElistTD[12] = TextDrawCreate(485.000, 307.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[12], 114.000, 16.000);
    TextDrawAlignment(ElistTD[12], 1);
    TextDrawColor(ElistTD[12], 175);
    TextDrawSetShadow(ElistTD[12], 0);
    TextDrawSetOutline(ElistTD[12], 0);
    TextDrawBackgroundColor(ElistTD[12], 255);
    TextDrawFont(ElistTD[12], 4);
    TextDrawSetProportional(ElistTD[12], 1);
    TextDrawSetSelectable(ElistTD[12], 1);

    ElistTD[13] = TextDrawCreate(485.000, 323.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[13], 114.000, 16.000);
    TextDrawAlignment(ElistTD[13], 1);
    TextDrawColor(ElistTD[13], 175);
    TextDrawSetShadow(ElistTD[13], 0);
    TextDrawSetOutline(ElistTD[13], 0);
    TextDrawBackgroundColor(ElistTD[13], 255);
    TextDrawFont(ElistTD[13], 4);
    TextDrawSetProportional(ElistTD[13], 1);
    TextDrawSetSelectable(ElistTD[13], 1);

    ElistTD[14] = TextDrawCreate(485.000, 339.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[14], 114.000, 16.000);
    TextDrawAlignment(ElistTD[14], 1);
    TextDrawColor(ElistTD[14], 175);
    TextDrawSetShadow(ElistTD[14], 0);
    TextDrawSetOutline(ElistTD[14], 0);
    TextDrawBackgroundColor(ElistTD[14], 255);
    TextDrawFont(ElistTD[14], 4);
    TextDrawSetProportional(ElistTD[14], 1);
    TextDrawSetSelectable(ElistTD[14], 1);

    ElistTD[15] = TextDrawCreate(485.000, 355.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[15], 114.000, 16.000);
    TextDrawAlignment(ElistTD[15], 1);
    TextDrawColor(ElistTD[15], 175);
    TextDrawSetShadow(ElistTD[15], 0);
    TextDrawSetOutline(ElistTD[15], 0);
    TextDrawBackgroundColor(ElistTD[15], 255);
    TextDrawFont(ElistTD[15], 4);
    TextDrawSetProportional(ElistTD[15], 1);
    TextDrawSetSelectable(ElistTD[15], 1);

    ElistTD[16] = TextDrawCreate(485.000, 371.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[16], 114.000, 16.000);
    TextDrawAlignment(ElistTD[16], 1);
    TextDrawColor(ElistTD[16], 175);
    TextDrawSetShadow(ElistTD[16], 0);
    TextDrawSetOutline(ElistTD[16], 0);
    TextDrawBackgroundColor(ElistTD[16], 255);
    TextDrawFont(ElistTD[16], 4);
    TextDrawSetProportional(ElistTD[16], 1);

    ElistTD[17] = TextDrawCreate(485.000, 388.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[17], 114.000, 22.000);
    TextDrawAlignment(ElistTD[17], 1);
    TextDrawColor(ElistTD[17], 175);
    TextDrawSetShadow(ElistTD[17], 0);
    TextDrawSetOutline(ElistTD[17], 0);
    TextDrawBackgroundColor(ElistTD[17], 255);
    TextDrawFont(ElistTD[17], 4);
    TextDrawSetProportional(ElistTD[17], 1);

    ElistTD[18] = TextDrawCreate(490.000, 390.000, "/e");
    TextDrawLetterSize(ElistTD[18], 0.140, 0.999);
    TextDrawAlignment(ElistTD[18], 1);
    TextDrawColor(ElistTD[18], -1);
    TextDrawSetShadow(ElistTD[18], 0);
    TextDrawSetOutline(ElistTD[18], 0);
    TextDrawBackgroundColor(ElistTD[18], 150);
    TextDrawFont(ElistTD[18], 1);
    TextDrawSetProportional(ElistTD[18], 1);

    ElistTD[19] = TextDrawCreate(496.000, 390.000, "(");
    TextDrawLetterSize(ElistTD[19], 0.140, 0.999);
    TextDrawAlignment(ElistTD[19], 1);
    TextDrawColor(ElistTD[19], -1);
    TextDrawSetShadow(ElistTD[19], 0);
    TextDrawSetOutline(ElistTD[19], 0);
    TextDrawBackgroundColor(ElistTD[19], 150);
    TextDrawFont(ElistTD[19], 1);
    TextDrawSetProportional(ElistTD[19], 1);

    ElistTD[20] = TextDrawCreate(498.000, 390.000, "nama");
    TextDrawLetterSize(ElistTD[20], 0.140, 0.999);
    TextDrawAlignment(ElistTD[20], 1);
    TextDrawColor(ElistTD[20], 8388863);
    TextDrawSetShadow(ElistTD[20], 0);
    TextDrawSetOutline(ElistTD[20], 0);
    TextDrawBackgroundColor(ElistTD[20], 150);
    TextDrawFont(ElistTD[20], 1);
    TextDrawSetProportional(ElistTD[20], 1);

    ElistTD[21] = TextDrawCreate(510.000, 390.000, ")");
    TextDrawLetterSize(ElistTD[21], 0.140, 0.999);
    TextDrawAlignment(ElistTD[21], 1);
    TextDrawColor(ElistTD[21], -1);
    TextDrawSetShadow(ElistTD[21], 0);
    TextDrawSetOutline(ElistTD[21], 0);
    TextDrawBackgroundColor(ElistTD[21], 150);
    TextDrawFont(ElistTD[21], 1);
    TextDrawSetProportional(ElistTD[21], 1);

    ElistTD[22] = TextDrawCreate(513.000, 390.000, "untuk memainkannya atau klik langsung");
    TextDrawLetterSize(ElistTD[22], 0.108, 0.999);
    TextDrawAlignment(ElistTD[22], 1);
    TextDrawColor(ElistTD[22], -1);
    TextDrawSetShadow(ElistTD[22], 0);
    TextDrawSetOutline(ElistTD[22], 0);
    TextDrawBackgroundColor(ElistTD[22], 150);
    TextDrawFont(ElistTD[22], 1);
    TextDrawSetProportional(ElistTD[22], 1);

    ElistTD[23] = TextDrawCreate(491.000, 398.000, "di atas");
    TextDrawLetterSize(ElistTD[23], 0.108, 0.999);
    TextDrawAlignment(ElistTD[23], 1);
    TextDrawColor(ElistTD[23], -1);
    TextDrawSetShadow(ElistTD[23], 0);
    TextDrawSetOutline(ElistTD[23], 0);
    TextDrawBackgroundColor(ElistTD[23], 150);
    TextDrawFont(ElistTD[23], 1);
    TextDrawSetProportional(ElistTD[23], 1);

    ElistTD[24] = TextDrawCreate(488.000, 214.000, "Angtang");
    TextDrawLetterSize(ElistTD[24], 0.140, 0.999);
    TextDrawTextSize(ElistTD[24], 3.000, 0.000);
    TextDrawAlignment(ElistTD[24], 1);
    TextDrawColor(ElistTD[24], -1);
    TextDrawSetShadow(ElistTD[24], 0);
    TextDrawSetOutline(ElistTD[24], 0);
    TextDrawBackgroundColor(ElistTD[24], 150);
    TextDrawFont(ElistTD[24], 1);
    TextDrawSetProportional(ElistTD[24], 1);

    ElistTD[25] = TextDrawCreate(488.000, 230.000, "Angkat");
    TextDrawLetterSize(ElistTD[25], 0.140, 0.999);
    TextDrawTextSize(ElistTD[25], 3.000, 0.000);
    TextDrawAlignment(ElistTD[25], 1);
    TextDrawColor(ElistTD[25], -1);
    TextDrawSetShadow(ElistTD[25], 0);
    TextDrawSetOutline(ElistTD[25], 0);
    TextDrawBackgroundColor(ElistTD[25], 150);
    TextDrawFont(ElistTD[25], 1);
    TextDrawSetProportional(ElistTD[25], 1);

    ElistTD[26] = TextDrawCreate(488.000, 246.000, "Angtang2");
    TextDrawLetterSize(ElistTD[26], 0.140, 0.999);
    TextDrawTextSize(ElistTD[26], 3.000, 0.000);
    TextDrawAlignment(ElistTD[26], 1);
    TextDrawColor(ElistTD[26], -1);
    TextDrawSetShadow(ElistTD[26], 0);
    TextDrawSetOutline(ElistTD[26], 0);
    TextDrawBackgroundColor(ElistTD[26], 150);
    TextDrawFont(ElistTD[26], 1);
    TextDrawSetProportional(ElistTD[26], 1);

    ElistTD[27] = TextDrawCreate(488.000, 262.000, "Angtang3");
    TextDrawLetterSize(ElistTD[27], 0.140, 0.999);
    TextDrawTextSize(ElistTD[27], 3.000, 0.000);
    TextDrawAlignment(ElistTD[27], 1);
    TextDrawColor(ElistTD[27], -1);
    TextDrawSetShadow(ElistTD[27], 0);
    TextDrawSetOutline(ElistTD[27], 0);
    TextDrawBackgroundColor(ElistTD[27], 150);
    TextDrawFont(ElistTD[27], 1);
    TextDrawSetProportional(ElistTD[27], 1);

    ElistTD[28] = TextDrawCreate(488.000, 278.000, "Angtang4");
    TextDrawLetterSize(ElistTD[28], 0.140, 0.999);
    TextDrawTextSize(ElistTD[28], 3.000, 0.000);
    TextDrawAlignment(ElistTD[28], 1);
    TextDrawColor(ElistTD[28], -1);
    TextDrawSetShadow(ElistTD[28], 0);
    TextDrawSetOutline(ElistTD[28], 0);
    TextDrawBackgroundColor(ElistTD[28], 150);
    TextDrawFont(ElistTD[28], 1);
    TextDrawSetProportional(ElistTD[28], 1);

    ElistTD[29] = TextDrawCreate(488.000, 293.000, "Liptang");
    TextDrawLetterSize(ElistTD[29], 0.140, 0.999);
    TextDrawTextSize(ElistTD[29], 3.000, 0.000);
    TextDrawAlignment(ElistTD[29], 1);
    TextDrawColor(ElistTD[29], -1);
    TextDrawSetShadow(ElistTD[29], 0);
    TextDrawSetOutline(ElistTD[29], 0);
    TextDrawBackgroundColor(ElistTD[29], 150);
    TextDrawFont(ElistTD[29], 1);
    TextDrawSetProportional(ElistTD[29], 1);

    ElistTD[30] = TextDrawCreate(488.000, 309.000, "Liptang2");
    TextDrawLetterSize(ElistTD[30], 0.140, 0.999);
    TextDrawTextSize(ElistTD[30], 3.000, 0.000);
    TextDrawAlignment(ElistTD[30], 1);
    TextDrawColor(ElistTD[30], -1);
    TextDrawSetShadow(ElistTD[30], 0);
    TextDrawSetOutline(ElistTD[30], 0);
    TextDrawBackgroundColor(ElistTD[30], 150);
    TextDrawFont(ElistTD[30], 1);
    TextDrawSetProportional(ElistTD[30], 1);

    ElistTD[31] = TextDrawCreate(488.000, 326.000, "Liptang3");
    TextDrawLetterSize(ElistTD[31], 0.140, 0.999);
    TextDrawTextSize(ElistTD[31], 3.000, 0.000);
    TextDrawAlignment(ElistTD[31], 1);
    TextDrawColor(ElistTD[31], -1);
    TextDrawSetShadow(ElistTD[31], 0);
    TextDrawSetOutline(ElistTD[31], 0);
    TextDrawBackgroundColor(ElistTD[31], 150);
    TextDrawFont(ElistTD[31], 1);
    TextDrawSetProportional(ElistTD[31], 1);

    ElistTD[32] = TextDrawCreate(488.000, 342.000, "Liptang4");
    TextDrawLetterSize(ElistTD[32], 0.140, 0.999);
    TextDrawTextSize(ElistTD[32], 3.000, 0.000);
    TextDrawAlignment(ElistTD[32], 1);
    TextDrawColor(ElistTD[32], -1);
    TextDrawSetShadow(ElistTD[32], 0);
    TextDrawSetOutline(ElistTD[32], 0);
    TextDrawBackgroundColor(ElistTD[32], 150);
    TextDrawFont(ElistTD[32], 1);
    TextDrawSetProportional(ElistTD[32], 1);

    ElistTD[33] = TextDrawCreate(488.000, 358.000, "Rokok");
    TextDrawLetterSize(ElistTD[33], 0.140, 0.999);
    TextDrawTextSize(ElistTD[33], 3.000, 0.000);
    TextDrawAlignment(ElistTD[33], 1);
    TextDrawColor(ElistTD[33], -1);
    TextDrawSetShadow(ElistTD[33], 0);
    TextDrawSetOutline(ElistTD[33], 0);
    TextDrawBackgroundColor(ElistTD[33], 150);
    TextDrawFont(ElistTD[33], 1);
    TextDrawSetProportional(ElistTD[33], 1);

    ElistTD[34] = TextDrawCreate(506.000, 372.000, "< PREV");
    TextDrawLetterSize(ElistTD[34], 0.150, 1.098);
    TextDrawTextSize(ElistTD[34], 3.000, 0.000);
    TextDrawAlignment(ElistTD[34], 3);
    TextDrawColor(ElistTD[34], -1);
    TextDrawSetShadow(ElistTD[34], 0);
    TextDrawSetOutline(ElistTD[34], 0);
    TextDrawBackgroundColor(ElistTD[34], 150);
    TextDrawFont(ElistTD[34], 1);
    TextDrawSetProportional(ElistTD[34], 1);
    TextDrawSetSelectable(ElistTD[34], 1);

    ElistTD[35] = TextDrawCreate(596.000, 372.000, "NEXT >");
    TextDrawLetterSize(ElistTD[35], 0.150, 1.098);
    TextDrawTextSize(ElistTD[35], 3.000, 0.000);
    TextDrawAlignment(ElistTD[35], 3);
    TextDrawColor(ElistTD[35], -1);
    TextDrawSetShadow(ElistTD[35], 0);
    TextDrawSetOutline(ElistTD[35], 0);
    TextDrawBackgroundColor(ElistTD[35], 150);
    TextDrawFont(ElistTD[35], 1);
    TextDrawSetProportional(ElistTD[35], 1);
    TextDrawSetSelectable(ElistTD[35], 1);

    ElistTD[36] = TextDrawCreate(532.000, 371.000, "LD_BEAT:chit");
    TextDrawTextSize(ElistTD[36], 14.000, 16.000);
    TextDrawAlignment(ElistTD[36], 1);
    TextDrawColor(ElistTD[36], 12582911);
    TextDrawSetShadow(ElistTD[36], 0);
    TextDrawSetOutline(ElistTD[36], 0);
    TextDrawBackgroundColor(ElistTD[36], 255);
    TextDrawFont(ElistTD[36], 4);
    TextDrawSetProportional(ElistTD[36], 1);
    TextDrawSetSelectable(ElistTD[36], 1);

    ElistTD[37] = TextDrawCreate(536.000, 372.000, "A");
    TextDrawLetterSize(ElistTD[37], 0.230, 1.299);
    TextDrawTextSize(ElistTD[37], 3.000, 0.000);
    TextDrawAlignment(ElistTD[37], 1);
    TextDrawColor(ElistTD[37], 255);
    TextDrawSetShadow(ElistTD[37], 0);
    TextDrawSetOutline(ElistTD[37], 0);
    TextDrawBackgroundColor(ElistTD[37], 150);
    TextDrawFont(ElistTD[37], 1);
    TextDrawSetProportional(ElistTD[37], 1);

    ElistTD[38] = TextDrawCreate(567.000, 157.000, "EMOTE LIST");
    TextDrawLetterSize(ElistTD[38], 0.280, 1.700);
    TextDrawTextSize(ElistTD[38], 3.000, 0.000);
    TextDrawAlignment(ElistTD[38], 3);
    TextDrawColor(ElistTD[38], -1);
    TextDrawSetShadow(ElistTD[38], 0);
    TextDrawSetOutline(ElistTD[38], 0);
    TextDrawBackgroundColor(ElistTD[38], 150);
    TextDrawFont(ElistTD[38], 3);
    TextDrawSetProportional(ElistTD[38], 1);

    ElistTD[39] = TextDrawCreate(550.000, 176.000, "Roleplay");
    TextDrawLetterSize(ElistTD[39], 0.200, 1.199);
    TextDrawTextSize(ElistTD[39], 3.000, 0.000);
    TextDrawAlignment(ElistTD[39], 2);
    TextDrawColor(ElistTD[39], -1);
    TextDrawSetShadow(ElistTD[39], 0);
    TextDrawSetOutline(ElistTD[39], 0);
    TextDrawBackgroundColor(ElistTD[39], 150);
    TextDrawFont(ElistTD[39], 1);
    TextDrawSetProportional(ElistTD[39], 1);

    ElistTD[40] = TextDrawCreate(527.000, 176.000, "District");
    TextDrawLetterSize(ElistTD[40], 0.200, 1.199);
    TextDrawTextSize(ElistTD[40], 3.000, 0.000);
    TextDrawAlignment(ElistTD[40], 2);
    TextDrawColor(ElistTD[40], -1);
    TextDrawSetShadow(ElistTD[40], 0);
    TextDrawSetOutline(ElistTD[40], 0);
    TextDrawBackgroundColor(ElistTD[40], 150);
    TextDrawFont(ElistTD[40], 1);
    TextDrawSetProportional(ElistTD[40], 1);

    ElistTD[41] = TextDrawCreate(576.000, 371.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[41], 23.000, 14.000);
    TextDrawAlignment(ElistTD[41], 1);
    TextDrawColor(ElistTD[41], 0);
    TextDrawSetShadow(ElistTD[41], 0);
    TextDrawSetOutline(ElistTD[41], 0);
    TextDrawBackgroundColor(ElistTD[41], 255);
    TextDrawFont(ElistTD[41], 4);
    TextDrawSetProportional(ElistTD[41], 1);
    TextDrawSetSelectable(ElistTD[41], 1);

    ElistTD[42] = TextDrawCreate(485.000, 371.000, "LD_SPAC:white");
    TextDrawTextSize(ElistTD[42], 23.000, 14.000);
    TextDrawAlignment(ElistTD[42], 1);
    TextDrawColor(ElistTD[42], 0);
    TextDrawSetShadow(ElistTD[42], 0);
    TextDrawSetOutline(ElistTD[42], 0);
    TextDrawBackgroundColor(ElistTD[42], 255);
    TextDrawFont(ElistTD[42], 4);
    TextDrawSetProportional(ElistTD[42], 1);
    TextDrawSetSelectable(ElistTD[42], 1);
    return 1;
}

hook OnGameModeInit()
{
    CreateElistTD();
    return 1;
}

ShowElistAnim(playerid)
{
    new startIndex = gAnimPage[playerid] * ANIMS_PER_PAGE;
    new endIndex = startIndex + ANIMS_PER_PAGE;

    if (endIndex > TOTAL_ANIMS)
        endIndex = TOTAL_ANIMS;

    for (new i = 0; i < ANIMS_PER_PAGE; i++)
    {
        new index = startIndex + i;
        if (index < TOTAL_ANIMS)
        {
            TextDrawSetString(ElistTD[24 + i], ANIM_LIST[index]);
            TextDrawShowForPlayer(playerid, ElistTD[6 + i]); 
            TextDrawShowForPlayer(playerid, ElistTD[24 + i]); 
        }
        else
        {
            TextDrawSetString(ElistTD[24 + i], " ");
            TextDrawHideForPlayer(playerid, ElistTD[6 + i]);
            TextDrawHideForPlayer(playerid, ElistTD[24 + i]);
        }
    }
    TextDrawShowForPlayer(playerid, ElistTD[42]); // tombol prev
    TextDrawShowForPlayer(playerid, ElistTD[41]); // tombol next
    new str[64];
    format(str, sizeof(str), "%d/%d", gAnimPage[playerid] + 1, TOTAL_PAGES);
    TextDrawSetString(ElistTD[5], str);
    TextDrawShowForPlayer(playerid, ElistTD[5]);
}

HideElistAnim(playerid)
{
    for (new i = 0; i < ANIMS_PER_PAGE; i++)
    {
        TextDrawHideForPlayer(playerid, ElistTD[6 + i]);
        TextDrawHideForPlayer(playerid, ElistTD[24 + i]);
    }
    TextDrawHideForPlayer(playerid, ElistTD[42]); 
    TextDrawHideForPlayer(playerid, ElistTD[41]);
}

ShowAllElistTD(playerid)
{
    for(new i = 0; i < 43; i++)
    {
        TextDrawShowForPlayer(playerid, ElistTD[i]);
        SelectTextDraw(playerid, COLOR_BLUE);
    }
    return 1;
}

HideAllElistTD(playerid)
{
    for(new i = 0; i < 43; i++)
    {
        TextDrawHideForPlayer(playerid, ElistTD[i]);
        CancelSelectTextDraw(playerid);
    }
    return 1;
}

hook OnClickDynamicTextDraw(playerid, Text:clickedid)
{
    for(new i = 0; i < ANIMS_PER_PAGE; i++)
    {
        if(clickedid == ElistTD[6 + i])
        {
            new animIndex = gAnimPage[playerid] * ANIMS_PER_PAGE + i;

            if(animIndex < TOTAL_ANIMS)
            {
                new animName[32];
                format(animName, sizeof(animName), "%s", ANIM_LIST[animIndex]);
                OnPlayerApplyAnimation(playerid, animName);
                return 1;
            }
        }
    }
    if(clickedid == ElistTD[42])
    {
        if (gAnimPage[playerid] > 0)
            gAnimPage[playerid]--;

        HideElistAnim(playerid);
        ShowElistAnim(playerid);
        return 1;
    }
    if(clickedid == ElistTD[41])
    {
        if (gAnimPage[playerid] < (TOTAL_PAGES - 1))
            gAnimPage[playerid]++;

        HideElistAnim(playerid);
        ShowElistAnim(playerid);
        return 1;
    }
    if(clickedid == ElistTD[36])
    {
        HideAllElistTD(playerid);
        Info(playerid, "Gunakan /e x untuk menghentikan animasions dan eprop");
        ShowHbeTextdraws(playerid, AccountData[playerid][pHUDMode]);
        return 1;
    }
    return 1;
}

CMD:elist(playerid, params[]) 
{
    if(AccountData[playerid][pCuffed]) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang diborgol!");
	if(AccountData[playerid][pActivityTime] != 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Selama activity progress masih berjalan, anda tidak dapat menggunakan CMD!");
	if(AccountData[playerid][pInjured] > 0) return ShowTDN(playerid, NOTIFICATION_ERROR, "Tidak bisa menggunakan ini jika sedang keadaan Pingsan!");
	if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda tidak bisa menggunakan emote didalam kendaraan!");
	if(GetPVarInt(playerid, "DurringDaur")) return ShowTDN(playerid, NOTIFICATION_ERROR, "Anda sedang membawa barang, tidak dapat melakukan ini!");

	if(AccountData[playerid][pSpawned] == 1)
    {
		gAnimPage[playerid] = 0;
        ShowAllElistTD(playerid);
        ShowElistAnim(playerid);
	}
    return 1;
}
