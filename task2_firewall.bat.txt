@echo off
echo ========================================
echo Task 2: Registry Backup and Firewall Rule
echo ========================================
echo.

:: 1. Бэкап реестра (экспорт ветки HKCU\Software)
echo [1] Creating registry backup...
set BACKUP_DIR=C:\RegistryBackup
if not exist "%BACKUP_DIR%" mkdir "%BACKUP_DIR%"
set BACKUP_FILE=%BACKUP_DIR%\HKCU_Software_%DATE:~-4,4%%DATE:~-10,2%%DATE:~-7,2%.reg
reg export HKEY_CURRENT_USER\Software "%BACKUP_FILE%"
echo Backup saved to: %BACKUP_FILE%
echo.

:: 2. Настройка брандмауэра (правило для порта 8080)
echo [2] Configuring Windows Firewall...
:: Удаляем старое правило, если существует
netsh advfirewall firewall delete rule name="MyApp_Port8080" >nul 2>&1
:: Добавляем новое правило (разрешаем входящие на порт 8080)
netsh advfirewall firewall add rule name="MyApp_Port8080" dir=in action=allow protocol=TCP localport=8080
echo Firewall rule "MyApp_Port8080" added successfully!
echo.

:: 3. Показываем все правила для скриншота
echo [3] Current firewall rules (showing first 50 lines):
echo ========================================
netsh advfirewall firewall show rule name=all | findstr /i "MyApp_Port8080"
echo ========================================
echo.
echo Task 2 completed! Press any key to exit...
pause >nul