@echo off
echo === Резервное копирование реестра ===
set BACKUP_DIR=C:\RegistryBackup
if not exist "%BACKUP_DIR%" mkdir "%BACKUP_DIR%"
set BACKUP_FILE=%BACKUP_DIR%\HKCU_Software_%DATE:~-4,4%%DATE:~-10,2%%DATE:~-7,2%.reg
reg export HKEY_CURRENT_USER\Software "%BACKUP_FILE%"
echo Реестр экспортирован в %BACKUP_FILE%

echo.
echo === Настройка брандмауэра ===
:: Удаляем старое правило, если есть
netsh advfirewall firewall delete rule name="MyApp_Port8080"

:: Добавляем разрешение для входящих подключений на порт 8080
netsh advfirewall firewall add rule name="MyApp_Port8080" dir=in action=allow protocol=TCP localport=8080

echo Готово! Правило добавлено.
pause