@ECHO OFF
SETLOCAL EnableDelayedExpansion

:: ============================================================================
:: SAMP PAWN PROFESSIONAL COMPILER - ULTIMATE EDITION V3.3
:: ============================================================================
:: Author      : Jack Dogle (Upgraded for Universal Compatibility)
:: Version     : 3.3.0 (Fast Compile Fix & UI Bug Fix)
:: Optimized   : PUSHD Pathing, Flat-Block Logic, Strict Regex, UNC Support
:: License     : Jack Dogle Private/Public License
:: ============================================================================

:: ============================================================================
:: [ BILINGUAL CONFIGURATION / KONFIGURASI BAHASA ]
:: Set LANG=EN for English | Set LANG=ID untuk Bahasa Indonesia
:: ============================================================================
SET "LANG=ID"

:: ============================================================================
:: [ SYSTEM CONFIGURATION / KONFIGURASI SISTEM ]
:: ============================================================================
SET "PAWNCC_PATH=pawno\pawncc.exe"
SET "INC_DIR=pawno\include"
SET "LOG_FILE=compiler_log.txt"

:: [ PENTING! ] Flag dikembalikan ke -d1 dan -(+ seperti semula.
:: -d3 sebelumnya membuat pawncc "stuck" lama pada gamemode besar.
SET "COMPILER_FLAGS=-;+ -(+ -d1 -O1"

:: [ TERMINAL INTERFACE SETUP ]
TITLE SAMP Pawn Ultimate Compiler v3.3 - Jack Dogle
CHCP 65001 >NUL
SET "HEADER=═════════════════════════════════════════════════════════════════════════════"
SET "LINE=─────────────────────────────────────────────────────────────────────────────"

:: [ DRAG AND DROP DETECTION ]
IF NOT "%~1"=="" (
    SET "SOURCE_FILE=%~1"
    SET "MODE=DRAG_DROP"
    GOTO PRE_COMPILE
)

:START
COLOR 0B
CLS
ECHO %HEADER%
ECHO.
ECHO       ██╗ █████╗  ██████╗██╗  ██╗    ██████╗  ██████╗  ██████╗ ██╗     ███████╗
ECHO       ██║██╔══██╗██╔════╝██║ ██╔╝    ██╔══██╗██╔═══██╗██╔════╝ ██║     ██╔════╝
ECHO       ██║███████║██║     █████╔╝     ██║  ██║██║   ██║██║  ███╗██║     █████╗  
ECHO  ██╗  ██║██╔══██║██║     ██╔═██╗     ██║  ██║██║   ██║██║   ██║██║     ██╔══╝  
ECHO  ╚█████╔╝██║  ██║╚██████╗██║  ██╗    ██████╔╝╚██████╔╝╚██████╔╝███████╗███████╗
ECHO   ╚════╝ ╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝    ╚═════╝  ╚═════╝  ╚═════╝ ╚══════╝╚══════╝
ECHO.
ECHO %LINE%
ECHO.
ECHO           ██████╗ ██████╗ ███╗   ███╗██████╗ ██╗██╗     ███████╗██████╗ 
ECHO          ██╔════╝██╔═══██╗████╗ ████║██╔══██╗██║██║     ██╔════╝██╔══██╗
ECHO          ██║     ██║   ██║██╔████╔██║██████╔╝██║██║     █████╗  ██████╔╝
ECHO          ██║     ██║   ██║██║╚██╔╝██║██╔═══╝ ██║██║     ██╔══╝  ██╔══██╗
ECHO          ╚██████╗╚██████╔╝██║ ╚═╝ ██║██║     ██║███████╗███████╗██║  ██║
ECHO           ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝     ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝
ECHO.

:: Memperbaiki bug kurung yang memotong teks dengan karakter escape ^
IF /I "%LANG%"=="ID" (
    ECHO               E D I S I   U L T I M A T E   -   v3.3 ^(S T A B I L^)
    ECHO                     Didesain dan Dikembangkan oleh : Jack Dogle
) ELSE (
    ECHO               U L T I M A T E   E D I T I O N  -  v3.3 ^(S T A B L E^)
    ECHO                     Engineered and Crafted by : Jack Dogle
)
ECHO %HEADER%
ECHO.

:: [ AUTO-SCANNER PHASE ]
IF /I "%LANG%"=="ID" ( ECHO  [ SYSTEM ] Memindai file .pwn di folder gamemodes dan filterscripts... ) ELSE ( ECHO  [ SYSTEM ] Scanning for .pwn files in gamemodes and filterscripts... )

SET "FILE_COUNT=0"
:: Scan Gamemodes
FOR %%F IN ("%~dp0gamemodes\*.pwn") DO (
    SET /A FILE_COUNT+=1
    SET "FILE_PATH_!FILE_COUNT!=%%F"
    SET "FILE_DISP_!FILE_COUNT!=gamemodes\%%~nxF"
)
:: Scan Filterscripts
FOR %%F IN ("%~dp0filterscripts\*.pwn") DO (
    SET /A FILE_COUNT+=1
    SET "FILE_PATH_!FILE_COUNT!=%%F"
    SET "FILE_DISP_!FILE_COUNT!=filterscripts\%%~nxF"
)

:: Flat Logic Routing (Mencegah CMD Block Crash)
IF !FILE_COUNT! EQU 0 GOTO ERROR_NO_FILES
IF !FILE_COUNT! EQU 1 (
    SET "SOURCE_FILE=!FILE_PATH_1!"
    GOTO PRE_COMPILE
)
GOTO SHOW_MENU

:ERROR_NO_FILES
COLOR 0C
ECHO %LINE%
IF /I "%LANG%"=="ID" (
    ECHO  [ ERROR ] Tidak ada file .pwn yang ditemukan!
    ECHO            Pastikan script ini berada di folder utama server SA-MP.
    ECHO            Atau, seret ^(Drag ^& Drop^) file .pwn langsung ke file .bat ini.
) ELSE (
    ECHO  [ ERROR ] No .pwn files found!
    ECHO            Ensure this script is in the main SA-MP server folder.
    ECHO            Or, Drag ^& Drop a .pwn file directly onto this .bat file.
)
ECHO %LINE%
PAUSE
EXIT /B

:SHOW_MENU
:: [ INTERACTIVE MENU ]
ECHO %LINE%
IF /I "%LANG%"=="ID" ( ECHO  [ MENU ] Ditemukan !FILE_COUNT! file. Silahkan pilih file untuk dikompilasi: ) ELSE ( ECHO  [ MENU ] Found !FILE_COUNT! files. Please select a file to compile: )
ECHO.
FOR /L %%I IN (1, 1, !FILE_COUNT!) DO (
    ECHO     [%%I] !FILE_DISP_%%I!
)
ECHO.
SET "USER_CHOICE="
IF /I "%LANG%"=="ID" ( SET /P "USER_CHOICE=> Masukkan Nomor (1-!FILE_COUNT!): " ) ELSE ( SET /P "USER_CHOICE=> Enter Number (1-!FILE_COUNT!): " )

:: [ ANTI-CRASH VALIDATION - MAX STABILITY ]
IF "!USER_CHOICE!"=="" GOTO START
:: Mencegah crash octal & huruf dengan regex ketat (Hanya menerima angka 1-9 di depan)
ECHO !USER_CHOICE!| FINDSTR /R "^[1-9][0-9]*$" >NUL
IF ERRORLEVEL 1 GOTO START
:: Cek range angka
IF !USER_CHOICE! LSS 1 GOTO START
IF !USER_CHOICE! GTR !FILE_COUNT! GOTO START

:: Ekstraksi array yang dijamin aman
CALL SET "SOURCE_FILE=%%FILE_PATH_!USER_CHOICE!%%"

:PRE_COMPILE
:: [ VALIDATION PHASE ]
SET "S_TIME=%TIME%"
SET "ABS_PAWNCC=%~dp0%PAWNCC_PATH%"
SET "ABS_INC=%~dp0%INC_DIR%"

IF NOT EXIST "%ABS_PAWNCC%" (
    COLOR 0C
    ECHO %LINE%
    IF /I "%LANG%"=="ID" ( ECHO  [ ERROR ] Compiler tidak ditemukan di: %PAWNCC_PATH% ) ELSE ( ECHO  [ ERROR ] Compiler not found at: %PAWNCC_PATH% )
    ECHO %LINE%
    PAUSE
    EXIT /B
)

:: [ SMART PATHING ]
FOR %%A IN ("!SOURCE_FILE!") DO (
    SET "WORK_DIR=%%~dpA"
    SET "FILE_NAME=%%~nxA"
)

:: Menggunakan PUSHD agar aman dari crash Network/UNC Drive
PUSHD "!WORK_DIR!"

:: [ COMPILATION PHASE ]
IF /I "%LANG%"=="ID" ( ECHO  [ PROSES ] Mengompilasi dengan optimasi tinggi... ) ELSE ( ECHO  [ PROCESS ] Compiling with high optimization... )
ECHO  [ TARGET ] !FILE_NAME!
ECHO  [ LOKASI ] !WORK_DIR!
ECHO %LINE%
ECHO.

:: MENJALANKAN COMPILER
"%ABS_PAWNCC%" "!FILE_NAME!" %COMPILER_FLAGS% -i"%ABS_INC%"

IF %ERRORLEVEL% EQU 0 (
    SET "STATUS=SUCCESS"
    SET "M_STATUS=BERHASIL"
    COLOR 0A
) ELSE (
    SET "STATUS=FAILED"
    SET "M_STATUS=GAGAL"
    COLOR 0C
)

:: Kembali ke direktori asli dengan aman
POPD

:: [ POST-COMPILATION ]
SET "E_TIME=%TIME%"
ECHO.
ECHO %HEADER%
IF /I "%LANG%"=="ID" (
    ECHO  [ HASIL ] Status Kompilasi : %M_STATUS%
    ECHO  [ WAKTU ] Dimulai: %S_TIME% ^| Selesai: %E_TIME%
) ELSE (
    ECHO  [ RESULT ] Compilation Status : %STATUS%
    ECHO  [ TIME   ] Started: %S_TIME% ^| Finished: %E_TIME%
)
ECHO %HEADER%

:: AUTO-LOGGING (Absolute path memastikan tidak tersesat)
ECHO [%DATE% %TIME%] !FILE_NAME! - Status: %STATUS% >> "%~dp0%LOG_FILE%"

:: [ ACTION MENU - ANTI AUTO CLOSE ]
:ACTION_MENU
ECHO.
IF /I "%LANG%"=="ID" (
    ECHO  [ AKSI ] Tekan 'R' untuk Kompilasi Ulang file yang sama.
    IF NOT "!MODE!"=="DRAG_DROP" ECHO           Tekan 'M' untuk kembali ke Menu Utama.
    ECHO           Tekan 'X' untuk KELUAR dari compiler.
) ELSE (
    ECHO  [ ACTION ] Press 'R' to Re-compile the same file.
    IF NOT "!MODE!"=="DRAG_DROP" ECHO             Press 'M' to return to Main Menu.
    ECHO             Press 'X' to EXIT compiler.
)
SET "USER_INPUT="
SET /P "USER_INPUT=> "

:: Validasi Aksi
IF /I "!USER_INPUT!"=="R" GOTO PRE_COMPILE
IF /I "!USER_INPUT!"=="X" EXIT /B
IF NOT "!MODE!"=="DRAG_DROP" (
    IF /I "!USER_INPUT!"=="M" GOTO START
)

:: Jika tidak sengaja mengetik huruf lain/Enter kosong, akan looping tanpa menutup CMD
GOTO ACTION_MENU