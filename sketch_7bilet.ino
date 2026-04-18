boolean buttonWasUp = true;
boolean ledEnabled = false;

void setup() {
  pinMode(10, OUTPUT);
  pinMode(2, INPUT_PULLUP);
}
 
void loop() {
   // узнаем, отпущена ли кнопка сейчас
   boolean buttonIsUp = digitalRead(2);
 
   // если кнопка была отпущена и не отпущена сейчас
   if (buttonWasUp && !buttonIsUp) {

      // исключаем дребезг контактов тактовой кнопки
      delay(10);

    // и считываем сигнал с кнопки снова
    buttonIsUp = digitalRead(2);

      // если кнопка нажата, то переворачиваем сигнал светодиода
      if (!buttonIsUp) {
         ledEnabled = !ledEnabled;
         digitalWrite(10, ledEnabled);
      }
   }
 
   // запоминаем состояние кнопки для новой итерации
   buttonWasUp = buttonIsUp;
}