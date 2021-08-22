$timestamp = Get-Date -Format "MM-dd HH:mm:ss.fff"
$bspid = adb shell pidof com.beatgames.beatsaber
while ([string]::IsNullOrEmpty($bspid)) {
    Start-Sleep -Milliseconds 100
    $bspid = adb shell pidof com.beatgames.beatsaber
}
if ($args.Count -eq 0) {
    Write-Output "Start logging!"
    adb logcat -T "$timestamp" --pid $bspid | Select-String -pattern "(Crash|QuestHook|modloader|AndroidRuntime)"
}
if ($args[0] -eq "--file") {
     Write-Output "Logging and saving to file!"
     (adb logcat -T "$timestamp" --pid $bspid | Select-String -pattern "(Crash|QuestHook|modloader|AndroidRuntime)") | Tee-Object -FilePath $PSScriptRoot/logcat.log
}
