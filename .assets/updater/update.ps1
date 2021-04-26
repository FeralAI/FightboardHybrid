$file = 'FightboardHybrid.ino.hex'
$entry = Get-CimInstance -Class Win32_SerialPort -Filter "Name LIKE '%32u4%'" | Select-Object DeviceID
if ($null -eq $entry) {
	Write-Output 'Fightboard not found. Press the reset button on the bottom twice then try again.'
	exit
}

$port = $entry.DeviceID
& ".\avrdude.exe" -v -C".\avrdude.conf" -patmega32u4 -cavr109 -P $port -b57600 -D "-Uflash:w:${file}:i"
