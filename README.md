# bilet7_gushin
# Экзаменационный билет №7

## Содержание билета

- **Задание №1** — Подключение кнопки и светодиода к микроконтроллеру с использованием внешнего прерывания (attachInterrupt)
- **Задание №2** — Создание BAT-скрипта для резервного копирования реестра и настройки брандмауэра Windows
- **Задание №3** — Загрузка скетча и BAT-скрипта в репозиторий, объяснение разницы между polling и interrupt, скриншот команды netsh advfirewall

---

## Задание №1: Скетч с внешним прерыванием

**Условие:** Подключите к микроконтроллеру кнопку (вход) и светодиод (выход). Напишите программу, которая использует `attachInterrupt` для обработки нажатия кнопки. При каждом нажатии состояние светодиода инвертируется. Дополнительно: отправляйте уведомление `"Button pressed"` по UART в монитор порта.

### Решение: `interrupt_button.ino`


// Экзаменационный билет №7 - Задание №1
// Кнопка на пине 2 (прерывание), светодиод на пине 13

const int buttonPin = 2;      // пин кнопки (поддерживает внешнее прерывание)
const int ledPin = 13;        // пин светодиода

volatile bool ledState = false;   // состояние светодиода (volatile для использования в ISR)

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);   // INPUT_PULLUP - кнопка замыкает на GND
  
  Serial.begin(9600);
  
  // attachInterrupt(прерывание, функция, режим)
  // FALLING - срабатывает при переходе из HIGH в LOW (нажатие кнопки)
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING);
}

void loop() {
  // Основной цикл пуст — вся логика в прерывании
  // Можно добавить другой код, прерывание не заблокирует его
}

void buttonISR() {
  // Инвертируем состояние светодиода
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
  
  // Отправляем уведомление в монитор порта
  Serial.println("Button pressed");
}

@echo off
echo ============================================
echo Экзаменационный билет №7 - Задание №2
echo ============================================
echo.

:: 1. Резервное копирование реестра
echo [1] Создание резервной копии реестра...
set BACKUP_DIR=C:\RegistryBackup
if not exist "%BACKUP_DIR%" mkdir "%BACKUP_DIR%"

:: Формируем имя файла с текущей датой (ГГГГММДД)
set BACKUP_FILE=%BACKUP_DIR%\HKCU_Software_%DATE:~-4,4%%DATE:~-10,2%%DATE:~-7,2%.reg

:: Экспорт ветки HKEY_CURRENT_USER\Software
reg export HKEY_CURRENT_USER\Software "%BACKUP_FILE%"

if %errorlevel% equ 0 (
    echo Резервная копия создана: %BACKUP_FILE%
) else (
    echo Ошибка при создании резервной копии!
)
echo.

:: 2. Настройка брандмауэра Windows
echo [2] Настройка брандмауэра Windows...

:: Удаляем существующее правило с таким именем (если есть)
netsh advfirewall firewall delete rule name="Exam7_Port8080" >nul 2>&1

:: Добавляем новое правило: разрешить входящие подключения на порт 8080
netsh advfirewall firewall add rule name="Exam7_Port8080" ^
    dir=in action=allow protocol=TCP localport=8080

if %errorlevel% equ 0 (
    echo Правило "Exam7_Port8080" успешно добавлено!
) else (
    echo Ошибка при добавлении правила!
)
echo.

echo ============================================
echo Задание №2 выполнено!
echo ============================================
pause


Запуск скрипта:
Открыть командную строку от имени администратора

Выполнить: firewall_backup.bat

<img width="827" height="693" alt="Аннотация 2026-04-18 115418" src="https://github.com/user-attachments/assets/823e048b-31d6-469d-a481-969145a50aee" />

<img width="1004" height="590" alt="Аннотация 2026-04-18 113155" src="https://github.com/user-attachments/assets/c9f0379c-8b72-49bb-ac93-9c8c2e8d33a4" />

Как выполнить команду:


netsh advfirewall firewall show rule name=all
Или только для созданного правила:


netsh advfirewall firewall show rule name="Exam7_Port8080"
Ожидаемый вывод:

Rule Name:                               Exam7_Port8080
Enabled:                                 Yes
Direction:                               In
Profiles:                                Domain,Private,Public
Group:                                   
LocalIP:                                 Any
RemoteIP:                                Any
Protocol:                                TCP
LocalPort:                               8080
RemotePort:                              Any





<img width="845" height="697" alt="Аннотация 2026-04-18 115437" src="https://github.com/user-attachments/assets/0a460b48-d28f-41f5-b04a-f69d7601d573" />

Загрузка в репозиторий (Git)

# Инициализация репозитория
git init

# Добавление файлов
git add interrupt_button.ino firewall_backup.bat README.md screenshot.png

# Коммит
git commit -m "Экзаменационный билет №7: прерывания + BAT-скрипт"

# Привязка к удалённому репозиторию и отправка
git remote add origin https://github.com/ваш_логин/билет7.git
git push -u origin main

*** Схема подключения кнопки и светодиода на arduino uno
<img width="923" height="592" alt="Аннотация 2026-04-18 120346" src="https://github.com/user-attachments/assets/7b7926fe-cec7-4b38-b57f-46d4fb94d9ce" />


