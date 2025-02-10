#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN 9
#define SS_PIN 10

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN);

bool cardPresent = false; // Флаг наличия карты

void setup() {
  Serial.begin(9600); // Настройка Serial порта
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
}

void loop() {
  if (Serial.available()) {
    String com = Serial.readStringUntil('\n');
//    Serial.print(com);/
//    lcd.setCursor(0, 0);/
//    lcd.print(com);/
    if(com == "1") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Let's go");
      delay(10000);
        lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Welcome");
    } else if(com == "0") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("No, stop");
      delay(3000);
        lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Welcome");
   } else if(com == "2") {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Expired");
      delay(5000);
        lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Welcome");
   }
  }
  
  // Если карта не обнаружена, сбрасываем флаг
  if (!mfrc522.PICC_IsNewCardPresent()) {
    cardPresent = false;
    return;
  }


  // Если карта была считана и флаг установлен, выходим
  if (cardPresent) {
    return;
  }

  // Считываем данные карты
  if (mfrc522.PICC_ReadCardSerial()) {
    // Устанавливаем флаг, что карта считана
    cardPresent = true;

    // Выводим UID карты в Serial
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");//
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println(); // Переход на новую строку//

    lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Loading...");

    // Остановка работы с картой
    mfrc522.PICC_HaltA();//
  }
}
