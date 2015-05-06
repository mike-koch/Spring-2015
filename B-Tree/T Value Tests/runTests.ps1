Measure-Command { .\executables.ps1 | Out-Default }

Write-Host "Execution complete. Press any key to exit ..."

$x = $host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")