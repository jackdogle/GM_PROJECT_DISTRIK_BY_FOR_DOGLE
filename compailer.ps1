<#
.SYNOPSIS
    SAMP PAWN PROFESSIONAL COMPILER - ULTIMATE EDITION (POWERSHELL 7)
.DESCRIPTION
    An ultra-lightweight, enterprise-grade script for compiling SA-MP Pawn gamemodes and filterscripts.
    Specially optimized for Low-End CPUs (e.g., AMD E1, Intel Celeron) with memory management and priority throttling.
.AUTHOR
    Jack Dogle (PowerShell 7 V7.0 Ultra-Lightweight Upgrade)
.VERSION
    7.0.0 (Ultra-Lightweight / Low-Spec Edition - Multi-Language)
#>

#Requires -Version 5.1
Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

# ============================================================================
# [ CONFIGURATION / KONFIGURASI ]
# ============================================================================
$Script:LANG = "ID" # Default Language: "ID" for Indonesia, "EN" for English
$Script:CompilerExe = "pawno\pawncc.exe"
$Script:IncludeDir = "pawno\include"
$Script:LogFile = "compiler_log.txt"
$Script:CompilerFlags = @("-;+", "-(+", "-d1", "-O1")

# Advanced Features Toggle
$Script:EnableBackup = $true  # Auto-backup .pwn file before compiling
$Script:EnableSound  = $true  # Play sound on Success/Fail

# Console prep
[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$Host.UI.RawUI.WindowTitle = "SAMP Pawn Ultimate Compiler v7.0 (Ultra-Lightweight) - Jack Dogle"
$Host.UI.RawUI.CursorSize = 100

# ============================================================================
# [ CORE FUNCTIONS / FUNGSI UTAMA ]
# ============================================================================

function Show-Header {
    Clear-Host
    Write-Host "═════════════════════════════════════════════════════════════════════════════" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "      ██╗ █████╗  ██████╗██╗  ██╗    ██████╗  ██████╗  ██████╗ ██╗     ███████╗" -ForegroundColor Cyan
    Write-Host "      ██║██╔══██╗██╔════╝██║ ██╔╝    ██╔══██╗██╔═══██╗██╔════╝ ██║     ██╔════╝" -ForegroundColor Cyan
    Write-Host "      ██║███████║██║     █████╔╝     ██║  ██║██║   ██║██║  ███╗██║     █████╗  " -ForegroundColor Cyan
    Write-Host " ██╗  ██║██╔══██║██║     ██╔═██╗     ██║  ██║██║   ██║██║   ██║██║     ██╔══╝  " -ForegroundColor Cyan
    Write-Host " ╚█████╔╝██║  ██║╚██████╗██║  ██╗    ██████╔╝╚██████╔╝╚██████╔╝███████╗███████╗" -ForegroundColor Cyan
    Write-Host "  ╚════╝ ╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝    ╚═════╝  ╚═════╝  ╚═════╝ ╚══════╝╚══════╝" -ForegroundColor Cyan
    Write-Host ""
    Write-Host "─────────────────────────────────────────────────────────────────────────────" -ForegroundColor DarkGray
    Write-Host ""
    Write-Host "          ██████╗ ██████╗ ███╗   ███╗██████╗ ██╗██╗     ███████╗██████╗ " -ForegroundColor DarkYellow
    Write-Host "         ██╔════╝██╔═══██╗████╗ ████║██╔══██╗██║██║     ██╔════╝██╔══██╗" -ForegroundColor DarkYellow
    Write-Host "         ██║     ██║   ██║██╔████╔██║██████╔╝██║██║     █████╗  ██████╔╝" -ForegroundColor Yellow
    Write-Host "         ██║     ██║   ██║██║╚██╔╝██║██╔═══╝ ██║██║     ██╔══╝  ██╔══██╗" -ForegroundColor Yellow
    Write-Host "         ╚██████╗╚██████╔╝██║ ╚═╝ ██║██║     ██║███████╗███████╗██║  ██║" -ForegroundColor Green
    Write-Host "          ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚═╝     ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝" -ForegroundColor Green
    Write-Host ""
    
    if ($Script:LANG -eq "ID") {
        Write-Host "           E D I S I   U L T R A - L I G H T W E I G H T   -   v7.0" -ForegroundColor White
        Write-Host "            (Dioptimalkan untuk Low-End CPU / AMD E1 / Intel Celeron)" -ForegroundColor DarkGray
        Write-Host "                    Didesain dan Dikembangkan oleh : Jack Dogle" -ForegroundColor DarkGray
    } else {
        Write-Host "           U L T R A - L I G H T W E I G H T   E D I T I O N   -   v7.0" -ForegroundColor White
        Write-Host "            (Optimized for Low-End CPUs / AMD E1 / Intel Celeron)" -ForegroundColor DarkGray
        Write-Host "                    Engineered and Crafted by : Jack Dogle" -ForegroundColor DarkGray
    }
    Write-Host "═════════════════════════════════════════════════════════════════════════════" -ForegroundColor Cyan
    Write-Host ""
}

function Invoke-InteractiveMenu {
    param([array]$Items, [string]$Title)

    $selectedIndex = 0
    $menuActive = $true

    # Zero-Flicker UI Optimization
    Clear-Host
    Show-Header
    Write-Host " [ MENU ] $Title" -ForegroundColor Yellow
    Write-Host "─────────────────────────────────────────────────────────────────────────────" -ForegroundColor DarkGray
    
    if ($Script:LANG -eq "ID") { Write-Host " Gunakan panah Atas/Bawah dan tekan ENTER untuk memilih:`n" -ForegroundColor Gray }
    else { Write-Host " Use Up/Down arrows and press ENTER to select:`n" -ForegroundColor Gray }
    
    $cursorTop = [Console]::CursorTop
    [Console]::CursorVisible = $false

    try {
        while ($menuActive) {
            [Console]::SetCursorPosition(0, $cursorTop)

            for ($i = 0; $i -lt $Items.Count; $i++) {
                $cleanLine = " " * 80
                [Console]::SetCursorPosition(0, [Console]::CursorTop)
                Write-Host $cleanLine -NoNewline
                [Console]::SetCursorPosition(0, [Console]::CursorTop)

                if ($i -eq $selectedIndex) {
                    Write-Host "  > [$($i+1)] $($Items[$i].DisplayName)" -ForegroundColor Cyan -BackgroundColor DarkBlue
                } else {
                    Write-Host "    [$($i+1)] $($Items[$i].DisplayName)" -ForegroundColor White -BackgroundColor Black
                }
            }

            $key = [Console]::ReadKey($true).Key
            switch ($key) {
                'UpArrow'   { if ($selectedIndex -gt 0) { $selectedIndex-- } else { $selectedIndex = $Items.Count - 1 } }
                'DownArrow' { if ($selectedIndex -lt ($Items.Count - 1)) { $selectedIndex++ } else { $selectedIndex = 0 } }
                'Enter'     { $menuActive = $false }
            }
        }
    } finally {
        [Console]::CursorVisible = $true
        [Console]::BackgroundColor = 'Black'
        Write-Host ""
    }
    
    return $Items[$selectedIndex]
}

function Play-AudioFeedback {
    param([bool]$Success)
    if (-not $Script:EnableSound) { return }
    if ($Success) {
        [System.Console]::Beep(800, 150)
        [System.Console]::Beep(1200, 200)
    } else {
        [System.Console]::Beep(300, 500)
        [System.Console]::Beep(250, 600)
    }
}

function Format-InMemoryOutput {
    param([string]$OutputData)
    if ([string]::IsNullOrWhiteSpace($OutputData)) { return }
    
    # [OPTIMASI LOW-END CPU] Mengganti Regex (-match) dengan String.Contains yang 10x lebih ringan
    $lines = $OutputData.Split([string[]]@("`r`n", "`n"), [System.StringSplitOptions]::RemoveEmptyEntries)
    foreach ($line in $lines) {
        $lowerLine = $line.ToLower()
        if ($lowerLine.Contains("error") -or $lowerLine.Contains("fatal")) {
            Write-Host $line -ForegroundColor Red
        } elseif ($lowerLine.Contains("warning")) {
            Write-Host $line -ForegroundColor Yellow
        } else {
            Write-Host $line -ForegroundColor White
        }
    }
}

function Compile-Script {
    param([string]$FilePath, [bool]$Quiet = $false)

    $fileInfo = Get-Item $FilePath
    $workDir = $fileInfo.DirectoryName
    $fileName = $fileInfo.Name
    $baseName = $fileInfo.BaseName
    $amxPath = Join-Path $workDir "$baseName.amx"

    $compilerPath = Join-Path $PSScriptRoot $Script:CompilerExe
    $includePath = Join-Path $PSScriptRoot $Script:IncludeDir

    if (-not (Test-Path $compilerPath)) {
        if ($Script:LANG -eq "ID") { Write-Host " [ ERROR ] Compiler tidak ditemukan di: $compilerPath" -ForegroundColor Red }
        else { Write-Host " [ ERROR ] Compiler not found at: $compilerPath" -ForegroundColor Red }
        return $false
    }

    # [OPTIMASI DISK I/O] Menggunakan .NET Native Copy alih-alih Copy-Item agar HDD lambat tidak lag
    if ($Script:EnableBackup) {
        $backupPath = Join-Path $workDir "$fileName.bak"
        try { [System.IO.File]::Copy($FilePath, $backupPath, $true) } catch {}
    }

    if (-not $Quiet) {
        Clear-Host
        Show-Header
        if ($Script:LANG -eq "ID") { 
            Write-Host " [ PROSES ] Mengompilasi dengan Mode Ringan (Low-Spec)..." -ForegroundColor Magenta
            Write-Host " [ TARGET ] $fileName" -ForegroundColor Cyan
            Write-Host " [ LOKASI ] $workDir" -ForegroundColor Cyan
        } else { 
            Write-Host " [ PROCESS ] Compiling with Lightweight Mode (Low-Spec)..." -ForegroundColor Magenta
            Write-Host " [ TARGET ] $fileName" -ForegroundColor Cyan
            Write-Host " [ LOCATION ] $workDir" -ForegroundColor Cyan
        }
        Write-Host "─────────────────────────────────────────────────────────────────────────────" -ForegroundColor DarkGray
    }

    $sw = [System.Diagnostics.Stopwatch]::StartNew()
    $status = "FAILED"
    $mStatus = "GAGAL"
    $color = "Red"

    $argsList = @("`"$fileName`"") + $Script:CompilerFlags + "-i`"$includePath`""

    try {
        Push-Location -Path $workDir
        
        $processInfo = New-Object System.Diagnostics.ProcessStartInfo
        $processInfo.FileName = $compilerPath
        $processInfo.Arguments = $argsList -join " "
        $processInfo.WorkingDirectory = $workDir
        $processInfo.RedirectStandardOutput = $true
        $processInfo.RedirectStandardError = $true
        $processInfo.UseShellExecute = $false
        $processInfo.CreateNoWindow = $true
        $processInfo.StandardOutputEncoding = [System.Text.Encoding]::UTF8
        $processInfo.StandardErrorEncoding = [System.Text.Encoding]::UTF8

        $process = [System.Diagnostics.Process]::Start($processInfo)
        
        # [OPTIMASI ANTI-FREEZE] Membatasi prioritas proses agar laptop Low-End tidak hang
        try { $process.PriorityClass = [System.Diagnostics.ProcessPriorityClass]::BelowNormal } catch {}

        $stdout = $process.StandardOutput.ReadToEnd()
        $stderr = $process.StandardError.ReadToEnd()
        $process.WaitForExit()
        
        $combinedOutput = "$stdout`n$stderr"
        Format-InMemoryOutput -OutputData $combinedOutput
        
        if ($process.ExitCode -eq 0) {
            $status = "SUCCESS"
            $mStatus = "BERHASIL"
            $color = "Green"
        }
    } catch {
        if ($Script:LANG -eq "ID") { Write-Host " [ CRITICAL ] Terjadi kesalahan fatal saat mengeksekusi compiler!" -ForegroundColor Red }
        else { Write-Host " [ CRITICAL ] A fatal error occurred while executing the compiler!" -ForegroundColor Red }
    } finally {
        Pop-Location
        $sw.Stop()
        
        # [OPTIMASI RAM] Memaksa PowerShell membuang cache sampah agar RAM laptop lega kembali
        [System.GC]::Collect()
    }

    Play-AudioFeedback -Success ($status -eq "SUCCESS")

    # Calculate AMX Size
    $amxSizeStr = "N/A"
    if ($status -eq "SUCCESS" -and (Test-Path $amxPath)) {
        $amxSize = (Get-Item $amxPath).Length
        if ($amxSize -ge 1MB) { $amxSizeStr = "{0:N2} MB" -f ($amxSize / 1MB) }
        else { $amxSizeStr = "{0:N2} KB" -f ($amxSize / 1KB) }
    }

    if (-not $Quiet) {
        Write-Host ""
        Write-Host "═════════════════════════════════════════════════════════════════════════════" -ForegroundColor Cyan
        if ($Script:LANG -eq "ID") {
            Write-Host " [ HASIL ] Status Kompilasi : $mStatus" -ForegroundColor $color
            Write-Host " [ STATS ] Ukuran AMX       : $amxSizeStr" -ForegroundColor Yellow
            Write-Host " [ WAKTU ] Diselesaikan dlm : $($sw.Elapsed.TotalSeconds.ToString("0.000")) detik" -ForegroundColor Gray
        } else {
            Write-Host " [ RESULT ] Compilation Status : $status" -ForegroundColor $color
            Write-Host " [ STATS  ] AMX File Size      : $amxSizeStr" -ForegroundColor Yellow
            Write-Host " [ TIME   ] Completed in       : $($sw.Elapsed.TotalSeconds.ToString("0.000")) seconds" -ForegroundColor Gray
        }
        Write-Host "═════════════════════════════════════════════════════════════════════════════" -ForegroundColor Cyan
    }

    $logPath = Join-Path $PSScriptRoot $Script:LogFile
    $logMsg = "[$(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')] $fileName - Status: $status - AMX Size: $amxSizeStr - Time: $($sw.Elapsed.TotalSeconds.ToString("0.000"))s"
    try { Add-Content -Path $logPath -Value $logMsg -ErrorAction SilentlyContinue } catch {}

    return ($status -eq "SUCCESS")
}

function Start-LiveWatchMode {
    param([string]$FilePath)
    $fileInfo = Get-Item $FilePath
    $workDir = $fileInfo.DirectoryName
    $fileName = $fileInfo.Name

    Clear-Host
    Show-Header
    
    if ($Script:LANG -eq "ID") {
        Write-Host " [ LIVE WATCH MODE ] Sedang mengawasi file: $fileName" -ForegroundColor Magenta
        Write-Host "                     Kompilasi akan berjalan otomatis setiap kali Anda menekan Save/CTRL+S." -ForegroundColor Gray
        Write-Host "                     Tekan CTRL+C untuk menghentikan pengawasan." -ForegroundColor DarkGray
    } else {
        Write-Host " [ LIVE WATCH MODE ] Monitoring file: $fileName" -ForegroundColor Magenta
        Write-Host "                     Compilation will run automatically whenever you press Save/CTRL+S." -ForegroundColor Gray
        Write-Host "                     Press CTRL+C to stop monitoring." -ForegroundColor DarkGray
    }
    Write-Host "─────────────────────────────────────────────────────────────────────────────" -ForegroundColor DarkGray
    Write-Host ""

    Compile-Script -FilePath $FilePath -Quiet $true

    $watcher = New-Object System.IO.FileSystemWatcher
    $watcher.Path = $workDir
    $watcher.Filter = $fileName
    $watcher.NotifyFilter = [System.IO.NotifyFilters]::LastWrite
    $watcher.EnableRaisingEvents = $true

    try {
        while ($true) {
            $result = $watcher.WaitForChanged([System.IO.WatcherChangeTypes]::Changed, 1000)
            if ($result.TimedOut -eq $false) {
                if ($Script:LANG -eq "ID") { Write-Host "`n[$(Get-Date -Format 'HH:mm:ss')] Perubahan terdeteksi! Mengompilasi ulang..." -ForegroundColor Cyan }
                else { Write-Host "`n[$(Get-Date -Format 'HH:mm:ss')] Changes detected! Recompiling..." -ForegroundColor Cyan }
                
                # Jeda dinaikkan jadi 500ms karena HDD lambat butuh waktu lebih lama untuk menyelesaikan save file
                Start-Sleep -Milliseconds 500 
                Compile-Script -FilePath $FilePath -Quiet $true
            }
        }
    } finally {
        $watcher.EnableRaisingEvents = $false
        $watcher.Dispose()
    }
}

function Start-BatchCompile {
    param([System.Collections.Generic.List[PSCustomObject]]$PwnFiles)
    Clear-Host
    Show-Header
    
    if ($Script:LANG -eq "ID") { Write-Host " [ BATCH COMPILE MODE ] Memulai kompilasi massal untuk $($PwnFiles.Count) file..." -ForegroundColor Magenta }
    else { Write-Host " [ BATCH COMPILE MODE ] Starting batch compilation for $($PwnFiles.Count) files..." -ForegroundColor Magenta }
    Write-Host "─────────────────────────────────────────────────────────────────────────────" -ForegroundColor DarkGray
    
    $successCount = 0
    $failCount = 0

    foreach ($file in $PwnFiles) {
        if ($Script:LANG -eq "ID") { Write-Host "`n➤ Mengompilasi: $($file.DisplayName)" -ForegroundColor Cyan }
        else { Write-Host "`n➤ Compiling: $($file.DisplayName)" -ForegroundColor Cyan }
        
        $result = Compile-Script -FilePath $file.FullPath -Quiet $true
        if ($result) { $successCount++ } else { $failCount++ }
    }

    Write-Host "`n═════════════════════════════════════════════════════════════════════════════" -ForegroundColor Cyan
    if ($Script:LANG -eq "ID") { Write-Host " [ BATCH SELESAI ] Total Sukses: $successCount | Total Gagal: $failCount" -ForegroundColor Yellow }
    else { Write-Host " [ BATCH COMPLETED ] Total Success: $successCount | Total Failed: $failCount" -ForegroundColor Yellow }
    Write-Host "═════════════════════════════════════════════════════════════════════════════" -ForegroundColor Cyan
    Play-AudioFeedback -Success ($failCount -eq 0)
}

function Scan-PwnFiles {
    $pwnFiles = [System.Collections.Generic.List[PSCustomObject]]::new()
    $searchPaths = @("gamemodes", "filterscripts")
    
    foreach ($folder in $searchPaths) {
        $fullPath = Join-Path $PSScriptRoot $folder
        if (Test-Path $fullPath) {
            $files = [System.IO.Directory]::EnumerateFiles($fullPath, "*.pwn", [System.IO.SearchOption]::TopDirectoryOnly)
            foreach ($f in $files) {
                $pwnFiles.Add([PSCustomObject]@{
                    FullPath = $f
                    DisplayName = (Get-Item $f).FullName.Replace($PSScriptRoot + "\", "")
                })
            }
        }
    }
    return $pwnFiles
}

# ============================================================================
# [ MAIN EXECUTION LOGIC / LOGIKA EKSEKUSI ]
# ============================================================================

$dragDropFile = $null
if ($args.Count -gt 0) {
    $dragDropFile = $args[0]
}

while ($true) {
    
    $scannedFiles = Scan-PwnFiles
    
    if ($null -ne $dragDropFile -and (Test-Path $dragDropFile)) {
        Compile-Script -FilePath $dragDropFile
        $dragDropFile = $null
    } else {
        $mainMenu = @(
            [PSCustomObject]@{ DisplayName = if($Script:LANG -eq "ID"){"🚀 Kompilasi File Spesifik (Single Compile)"}else{"🚀 Compile Specific File (Single Compile)"}; Action = "SINGLE" },
            [PSCustomObject]@{ DisplayName = if($Script:LANG -eq "ID"){"🔄 Live Auto-Compile (Watch Mode)"}else{"🔄 Live Auto-Compile (Watch Mode)"}; Action = "WATCH" },
            [PSCustomObject]@{ DisplayName = if($Script:LANG -eq "ID"){"📦 Kompilasi SEMUA File (Batch Compile)"}else{"📦 Compile ALL Files (Batch Compile)"}; Action = "BATCH" },
            [PSCustomObject]@{ DisplayName = if($Script:LANG -eq "ID"){"🌐 Ganti Bahasa (Change Language)"}else{"🌐 Change Language (Ganti Bahasa)"}; Action = "LANG" },
            [PSCustomObject]@{ DisplayName = if($Script:LANG -eq "ID"){"❌ Keluar"}else{"❌ Exit"}; Action = "EXIT" }
        )
        
        $titleMain = if($Script:LANG -eq "ID"){"Pilih Mode Operasi Compiler:"}else{"Select Compiler Operation Mode:"}
        $mainSelection = Invoke-InteractiveMenu -Items $mainMenu -Title $titleMain

        if ($mainSelection.Action -eq "EXIT") {
            exit
        }

        if ($mainSelection.Action -eq "LANG") {
            $langMenu = @(
                [PSCustomObject]@{ DisplayName = "🇮🇩 Bahasa Indonesia"; Action = "ID" },
                [PSCustomObject]@{ DisplayName = "🇬🇧 English"; Action = "EN" }
            )
            $langTitle = if($Script:LANG -eq "ID"){"Pilih Bahasa:"}else{"Select Language:"}
            $langSelection = Invoke-InteractiveMenu -Items $langMenu -Title $langTitle
            $Script:LANG = $langSelection.Action
            continue 
        }

        if ($scannedFiles.Count -eq 0) {
            if ($Script:LANG -eq "ID") {
                Write-Host " [ ERROR ] Tidak ada file .pwn yang ditemukan di gamemodes/filterscripts." -ForegroundColor Red
                Write-Host " Tekan tombol apapun untuk kembali..." -ForegroundColor Gray
            } else {
                Write-Host " [ ERROR ] No .pwn files found in gamemodes/filterscripts." -ForegroundColor Red
                Write-Host " Press any key to return..." -ForegroundColor Gray
            }
            [Console]::ReadKey() | Out-Null
            continue
        }

        if ($mainSelection.Action -eq "BATCH") {
            Start-BatchCompile -PwnFiles $scannedFiles
        } 
        elseif ($mainSelection.Action -eq "WATCH") {
            $titleWatch = if($Script:LANG -eq "ID"){"Pilih file yang akan diawasi (Live Watch):"}else{"Select file to monitor (Live Watch):"}
            $fileSelection = Invoke-InteractiveMenu -Items $scannedFiles -Title $titleWatch
            Start-LiveWatchMode -FilePath $fileSelection.FullPath
        }
        elseif ($mainSelection.Action -eq "SINGLE") {
            $titleSingle = if($Script:LANG -eq "ID"){"Pilih file yang akan dikompilasi:"}else{"Select file to compile:"}
            $fileSelection = Invoke-InteractiveMenu -Items $scannedFiles -Title $titleSingle
            Compile-Script -FilePath $fileSelection.FullPath
        }
    }

    Write-Host ""
    if ($Script:LANG -eq "ID") {
        Write-Host " [ AKSI ] [M] Menu Utama  |  [X] Keluar" -ForegroundColor Yellow
    } else {
        Write-Host " [ ACTION ] [M] Main Menu  |  [X] Exit" -ForegroundColor Yellow
    }
    
    $validKey = $false
    while (-not $validKey) {
        $key = [Console]::ReadKey($true).Character.ToString().ToUpper()
        switch ($key) {
            'M' { $validKey = $true } 
            'X' { exit }
        }
    }
}