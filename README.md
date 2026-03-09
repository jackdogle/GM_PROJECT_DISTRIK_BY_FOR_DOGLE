<div align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&height=250&section=header&text=PROJECT%20DISTRIK&fontSize=50&fontAlignY=38&desc=Advanced%20SA-MP%20Roleplay%20Gamemode&descAlignY=55&descAlign=50" alt="Project Distrik Banner" width="100%" />

  <h1>🏙️ GM PROJECT DISTRIK</h1>
  <p><strong>Basis Kode Gamemode SA-MP Modern, Modular, dan Berkinerja Tinggi</strong></p>

  <p>
    <a href="https://github.com/jackdogle/GM_PROJECT_DISTRIK_BY_FOR_DOGLE/releases"><img src="https://img.shields.io/badge/Version-v1.0.0-blue.svg?style=for-the-badge&logo=github" alt="Version"></a>
    <a href="https://github.com/pawn-lang/compiler"><img src="https://img.shields.io/badge/Language-Pawn-orange.svg?style=for-the-badge&logo=c" alt="Pawn Language"></a>
    <a href="https://github.com/pBlueG/SA-MP-MySQL"><img src="https://img.shields.io/badge/MySQL-R41+-4479A1.svg?style=for-the-badge&logo=mysql&logoColor=white" alt="MySQL"></a>
    <a href="https://github.com/pawn-lang/YSI-Includes"><img src="https://img.shields.io/badge/YSI-v5.0-red.svg?style=for-the-badge" alt="YSI-Includes"></a>
    <a href="https://sa-mp.com/"><img src="https://img.shields.io/badge/SA--MP-0.3.7%20%7C%200.3.DL-yellow.svg?style=for-the-badge" alt="SA-MP Version"></a>
    <br>
    <a href="https://github.com/jackdogle/GM_PROJECT_DISTRIK_BY_FOR_DOGLE/commits/main"><img src="https://img.shields.io/github/last-commit/jackdogle/GM_PROJECT_DISTRIK_BY_FOR_DOGLE?style=for-the-badge&color=success" alt="Last Commit"></a>
    <a href="https://github.com/jackdogle/GM_PROJECT_DISTRIK_BY_FOR_DOGLE/issues"><img src="https://img.shields.io/github/issues/jackdogle/GM_PROJECT_DISTRIK_BY_FOR_DOGLE?style=for-the-badge&color=critical" alt="Open Issues"></a>
    <a href="https://github.com/jackdogle/GM_PROJECT_DISTRIK_BY_FOR_DOGLE/blob/main/LICENSE"><img src="https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge" alt="License"></a>
  </p>
</div>

<hr>

<details open>
  <summary><b>📑 DAFTAR ISI</b></summary>
  <ol>
    <li><a href="#-tentang-project">Tentang Project</a></li>
    <li><a href="#-fitur-unggulan">Fitur Unggulan</a></li>
    <li><a href="#-prasyarat--dependencies">Prasyarat & Dependencies</a></li>
    <li><a href="#-panduan-instalasi">Panduan Instalasi</a></li>
    <li><a href="#-struktur-direktori">Struktur Direktori</a></li>
    <li><a href="#-konfigurasi">Konfigurasi</a></li>
    <li><a href="#-roadmap--to-do-list">Roadmap & To-Do List</a></li>
    <li><a href="#-kontribusi">Kontribusi</a></li>
    <li><a href="#-kredit">Kredit</a></li>
    <li><a href="#-lisensi">Lisensi</a></li>
  </ol>
</details>

<hr>

## 📖 TENTANG PROJECT

**GM Project Distrik** adalah gamemode San Andreas Multiplayer (SA-MP) berskala enterprise yang dirancang khusus untuk server Roleplay/Freeroam modern. Dikembangkan oleh **Jack Dogle (For Dogle)**, project ini lahir dari visi untuk menciptakan ekosistem server yang dinamis, ringan, dan sangat minim *bug*.

Berbeda dengan gamemode konvensional yang seringkali menggunakan pendekatan *monolithic* (satu file raksasa), Project Distrik mengimplementasikan arsitektur **Modular Codebase**. Hal ini memungkinkan para *developer* untuk dengan mudah menambah, memodifikasi, atau menghapus fitur tanpa merusak integritas sistem inti. Didukung oleh integrasi MySQL R41+ secara *asynchronous* dan optimisasi pustaka YSI, gamemode ini menjamin performa maksimal bahkan dengan ratusan pemain yang *online* secara bersamaan.

<br>

## ✨ FITUR UNGGULAN

Project Distrik dilengkapi dengan berbagai sistem mutakhir yang siap pakai untuk *production environment*:

- ✅ **Sistem Dinamis Penuh:** Manajemen Rumah, Bisnis, Faksi/Organisasi, dan Kendaraan sepenuhnya dapat dibuat dan diedit langsung dari dalam game (*in-game creation*).
- ✅ **Integrasi MySQL R41+:** Menggunakan sistem *threaded queries* untuk mencegah server *lag* atau *freeze* saat melakukan operasi database berat.
- ✅ **Optimisasi YSI Library:** Memanfaatkan `y_hooks`, `y_timers`, dan `y_iterate` untuk eksekusi kode yang jauh lebih cepat dan terstruktur.
- ✅ **Arsitektur Modular:** Sistem dipecah menjadi modul-modul independen (misal: `core/`, `systems/`, `factions/`), membuat navigasi kode menjadi sangat mudah.
- ✅ **In-Game UCP (User Control Panel):** Pemain dapat mengelola karakter, pengaturan akun, dan keamanan (PIN/2FA) langsung melalui antarmuka TextDraw yang elegan.
- ✅ **Server-Side Anti-Cheat:** Deteksi otomatis dan mitigasi terhadap eksploitasi umum seperti *Weapon Hack*, *Fly Hack*, *Speed Hack*, dan *Money Spawning*.
- ✅ **Sistem Inventaris Berbasis TextDraw:** UI interaktif untuk manajemen item karakter yang responsif dan modern.

<br>

## 🛠️ PRASYARAT & DEPENDENCIES

Sebelum memulai instalasi, pastikan lingkungan server Anda telah memenuhi persyaratan berikut. Kami sangat menyarankan penggunaan versi yang tertera untuk menghindari konflik kompilasi.

| Plugin / Include | Versi Disarankan | Deskripsi | Tautan |
| :--- | :---: | :--- | :--- |
| **MySQL Plugin** | `R41` / `R47` | Database driver oleh BlueG/maddinat0r. | [Unduh](https://github.com/pBlueG/SA-MP-MySQL/releases) |
| **SSCANF2** | `v2.13.0` | Ekstraksi string dan pemrosesan command yang efisien. | [Unduh](https://github.com/Y-Less/sscanf/releases) |
| **Streamer Plugin** | `v2.9.5` | Bypass limitasi objek, pickup, 3D text SA-MP oleh Incognito. | [Unduh](https://github.com/samp-incognito/samp-streamer-plugin/releases) |
| **YSI-Includes** | `v5.0` | Pustaka makro dan fungsi tingkat lanjut oleh Y-Less. | [Unduh](https://github.com/pawn-lang/YSI-Includes) |
| **Pawn.RakNet** | `v1.4.1` | Manipulasi paket jaringan (RPC/Packets) tingkat rendah. | [Unduh](https://github.com/katursis/Pawn.RakNet/releases) |
| **Pawn Compiler** | `v3.10.10` | Zeex Compiler modern untuk kompilasi yang lebih cepat & aman. | [Unduh](https://github.com/pawn-lang/compiler/releases) |

<br>

## 🚀 PANDUAN INSTALASI

Ikuti langkah-langkah di bawah ini untuk mengimplementasikan GM Project Distrik di *local machine* atau *VPS* Anda.

### Langkah 1: Clone Repository
Buka terminal/command prompt Anda dan jalankan perintah berikut:
```bash
git clone https://github.com/jackdogle/GM_PROJECT_DISTRIK_BY_FOR_DOGLE.git
cd GM_PROJECT_DISTRIK_BY_FOR_DOGLE
```

### Langkah 2: Setup Database
1. Buka phpMyAdmin atau klien MySQL pilihan Anda (HeidiSQL, DBeaver, dll).
2. Buat database baru, misalnya `project_distrik`.
3. Import skema database yang telah disediakan:
```sql
-- Jika menggunakan command line MySQL:
mysql -u root -p project_distrik < database/distrik_schema.sql
```

### Langkah 3: Konfigurasi Server
Buka file `server.cfg` di *root directory* dan sesuaikan konfigurasi dasar:
```ini
echo Executing Server Config...
lanmode 0
rcon_password ganti_password_rcon_anda
maxplayers 100
port 7777
hostname GM Project Distrik [v1.0.0]
gamemode0 distrik 1
filterscripts 
plugins mysql sscanf streamer pawnraknet
announce 0
chatlogging 0
weburl github.com/jackdogle
onfoot_rate 40
incar_rate 40
weapon_rate 40
stream_distance 300.0
stream_rate 1000
```
*(Catatan: Tambahkan ekstensi `.so` pada baris `plugins` jika Anda menggunakan OS Linux).*

### Langkah 4: Kompilasi Script
Buka file `gamemodes/distrik.pwn` menggunakan editor favorit Anda (Pawno, Sublime Text, atau VS Code dengan ekstensi Pawn).
Tekan `F5` (atau jalankan *build task*) untuk mengkompilasi *script* menggunakan Zeex Compiler. Pastikan output menghasilkan file `distrik.amx` tanpa *Error* (Warning minor dapat diabaikan jika Anda memahami konteksnya).

### Langkah 5: Jalankan Server
- **Windows:** Klik ganda pada `samp-server.exe`.
- **Linux:** Berikan izin eksekusi dan jalankan *binary*:
```bash
chmod +x samp03svr
./samp03svr
```

<br>

## 📂 STRUKTUR DIREKTORI

Project ini menggunakan struktur folder yang terorganisir untuk menjaga kebersihan *codebase*:

```text
GM_PROJECT_DISTRIK/
├── database/               # File .sql untuk skema database
├── filterscripts/          # Script tambahan/opsional (.pwn & .amx)
├── gamemodes/
│   ├── Main.pwn         # File utama gamemode
│   ├── Main.amx         # File hasil kompilasi (Executable)
│   └── modules/            # Sistem modular (Core, Factions, Jobs, dll)
│       ├── core/
│       ├── dynamic/
│       └── ui/
├── pawno/
│   ├── include/            # Tempat meletakkan YSI, a_samp, a_mysql, dll
│   └── pawncc.exe          # Zeex Compiler
├── plugins/                # File plugin (.dll untuk Windows, .so untuk Linux)
├── scriptfiles/            # Log server, konfigurasi dinamis, dan file I/O
├── server.cfg              # Konfigurasi utama server SA-MP
└── samp-server.exe         # Executable server (Windows)
```

<br>

## ⚙️ KONFIGURASI

Sebelum mengkompilasi, Anda **wajib** menyesuaikan kredensial database dan pengaturan server di dalam *script*. Buka file `gamemodes\SERVER\utils\utils_defines.inc` (atau di bagian atas `Main.pwn` jika disatukan) dan ubah definisi berikut:

```pawn
// ==========================================
//        SERVER CORE CONFIGURATION
// ==========================================

#define SERVER_NAME         "Project Distrik Roleplay"
#define SERVER_REVISION     "v1.0.0-stable"
#define SERVER_WEBSITE      "www.project-distrik.com"
#define SERVER_DISCORD      "discord.gg/projectdistrik"

// ==========================================
//        MYSQL DATABASE CREDENTIALS
// ==========================================

#define MYSQL_HOST          "127.0.0.1"
#define MYSQL_USER          "root"
#define MYSQL_PASS          ""          // Kosongkan jika menggunakan XAMPP default
#define MYSQL_DATA          "project_distrik"

// ==========================================
//        ECONOMY & GAMEPLAY
// ==========================================

#define STARTING_CASH       5000
#define STARTING_BANK       15000
#define MAX_CHARACTER_SLOT  3
```

<br>

## 🗺️ ROADMAP & TO-DO LIST

Kami terus mengembangkan GM Project Distrik. Berikut adalah rencana pengembangan ke depan:

- [x] Migrasi sistem penyimpanan dari file (INI) ke MySQL R41+.
- [x] Implementasi arsitektur Modular menggunakan `y_hooks`.
- [x] Pembuatan Sistem Dinamis (Rumah, Bisnis, Kendaraan).
- [ ] Rework UI/UX TextDraw untuk Inventory dan Dealership.
- [ ] Integrasi *Voice Chat* (Pawn.Voice / SV).
- [ ] Penambahan sistem *Minigames* (Biliar, Basket, Casino).
- [ ] Pembuatan *Web-based* UCP yang terhubung langsung dengan database server.

<br>

## 🤝 KONTRIBUSI

Kami sangat menyambut kontribusi dari komunitas SA-MP! Jika Anda ingin menambahkan fitur, memperbaiki *bug*, atau meningkatkan optimisasi kode:

1. Lakukan **Fork** pada repository ini.
2. Buat *branch* fitur Anda (`git checkout -b feature/FiturKerenAnda`).
3. Lakukan *Commit* perubahan Anda (`git commit -m 'Menambahkan Fitur Keren'`).
4. Lakukan *Push* ke *branch* tersebut (`git push origin feature/FiturKerenAnda`).
5. Buka **Pull Request** di repository utama kami.

*Pastikan kode Anda mengikuti standar indentasi (Allman style) dan tidak merusak sistem modular yang sudah ada.*

<br>

## 🏆 KREDIT

Project ini tidak akan terwujud tanpa kontribusi luar biasa dari komunitas SA-MP. Terima kasih yang sebesar-besarnya kepada:

*   **Jack Dogle / For Dogle** - *Lead Developer & Creator* GM Project Distrik.
*   **SA-MP Team (Kalcor)** - Untuk platform San Andreas Multiplayer yang legendaris.
*   **Zeex** - Untuk *Pawn Compiler* modern yang revolusioner.
*   **Y-Less** - Untuk mahakarya *YSI-Includes* dan *sscanf*.
*   **Incognito** - Untuk *Streamer Plugin* yang sangat *powerful*.
*   **BlueG & maddinat0r** - Untuk *MySQL Plugin* yang cepat dan stabil.
*   Seluruh kontributor *open-source* dan tester di komunitas SA-MP Indonesia.

<br>

## 📄 LISENSI

Didistribusikan di bawah Lisensi **MIT**. Lihat file `LICENSE` untuk informasi lebih lanjut.

```text
MIT License

Copyright (c) 2023-Present Jack Dogle (For Dogle)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction...
```

<hr>

<div align="center">
  <sub>Dibuat dengan ❤️ oleh Komunitas SA-MP untuk Komunitas SA-MP.</sub><br>
  <sub>Jika Anda menyukai project ini, jangan lupa berikan ⭐ Star di GitHub!</sub>
</div>
