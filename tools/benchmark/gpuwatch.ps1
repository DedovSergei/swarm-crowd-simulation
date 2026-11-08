# gpuwatch.ps1 -Mode wait|log [-QuietSeconds 60] [-MaxMinutes 60] [-Log path] [-Exclude name,...] [-StopFile path]
# GPU use by OTHER processes, from the Windows '\GPU Engine(*)\Utilization Percentage' counters (read-only).
# The quiet-GPU check and process logging.
#  wait: exits 0 once the summed utilization of all processes except -Exclude stays below 1% for
#        -QuietSeconds; exits 1 after -MaxMinutes. Prints a status line each minute.
#  log:  appends one CSV line every 10 s (time, other-process utilization by engine type, busiest process).
#        Stops when -StopFile exists (if given), else once an -Exclude process has existed and then exited.
param([string]$Mode = 'wait', [int]$QuietSeconds = 60, [int]$MaxMinutes = 60, [string]$Log = '',
      [string[]]$Exclude = @('benchmark_crowd', 'gpu_diag', 'bench'), [string]$StopFile = '')

function Sample {
    $s = Get-Counter '\GPU Engine(*)\Utilization Percentage' -ErrorAction SilentlyContinue
    $excluded = @(Get-Process -Name $Exclude -ErrorAction SilentlyContinue | ForEach-Object { $_.Id })
    $byType = @{}; $byPid = @{}; $total = 0.0
    foreach ($c in $s.CounterSamples) {
        if ($c.CookedValue -le 0) { continue }
        if ($c.InstanceName -notmatch 'pid_(\d+)_.*engtype_(.+)$') { continue }
        $procId = [int]$Matches[1]; $type = $Matches[2]
        if ($excluded -contains $procId) { continue }
        $total += $c.CookedValue
        $byType[$type] = $byType[$type] + $c.CookedValue
        $byPid[$procId] = $byPid[$procId] + $c.CookedValue
    }
    $top = ''
    if ($byPid.Count) {
        $t = $byPid.GetEnumerator() | Sort-Object Value -Descending | Select-Object -First 1
        $n = (Get-Process -Id $t.Key -ErrorAction SilentlyContinue).Name
        $top = "$n($($t.Key)) $([math]::Round($t.Value,1))%"
    }
    $types = ($byType.GetEnumerator() | Sort-Object Name | ForEach-Object { "$($_.Name)=$([math]::Round($_.Value,1))" }) -join ' '
    return [pscustomobject]@{ Total = $total; Types = $types; Top = $top }
}

if ($Mode -eq 'wait') {
    $start = Get-Date; $quietSince = $null; $lastReport = Get-Date
    while (((Get-Date) - $start).TotalMinutes -lt $MaxMinutes) {
        $x = Sample
        if ($x.Total -lt 1.0) { if (-not $quietSince) { $quietSince = Get-Date } } else { $quietSince = $null }
        if ($quietSince -and ((Get-Date) - $quietSince).TotalSeconds -ge $QuietSeconds) {
            Write-Output ("QUIET for {0} s at {1:HH:mm:ss}" -f $QuietSeconds, (Get-Date)); exit 0
        }
        if (((Get-Date) - $lastReport).TotalSeconds -ge 60) {
            Write-Output ("{0:HH:mm:ss} busy: other GPU use {1:N1}% [{2}] top {3}" -f (Get-Date), $x.Total, $x.Types, $x.Top); $lastReport = Get-Date
        }
        Start-Sleep -Seconds 5
    }
    Write-Output "TIMEOUT: GPU not quiet within $MaxMinutes min"; exit 1
} else {
    'time,other_total_pct,by_engine_type,busiest' | Out-File -FilePath $Log -Encoding utf8
    $seen = $false
    while ($true) {
        if ($StopFile) {
            if (Test-Path $StopFile) { break }
        } else {
            $running = [bool](Get-Process -Name $Exclude -ErrorAction SilentlyContinue)
            if ($running) { $seen = $true } elseif ($seen) { break }
        }
        $x = Sample
        [string]::Format([cultureinfo]::InvariantCulture, '{0:HH:mm:ss},{1:F2},"{2}","{3}"', (Get-Date), $x.Total, $x.Types, $x.Top) | Out-File -FilePath $Log -Append -Encoding utf8
        Start-Sleep -Seconds 10
    }
}
