#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int dipPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const int buzzerPin = 12;

char asciiTable[128] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
  ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
  '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
  'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
  '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
  'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', 127
};

void setup() {
  lcd.begin(16, 2);
  lcd.backlight();

  for (int i = 0; i < 8; i++) {
    pinMode(dipPins[i], INPUT_PULLUP);
  }

  pinMode(buzzerPin, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("ASCII Char:");
}

void loop() {
  int binaryValue = readDipSwitch();
  
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);

  if (binaryValue < 128) {
    lcd.print(asciiTable[binaryValue]);
    digitalWrite(buzzerPin, HIGH);
    delay(200);
    digitalWrite(buzzerPin, LOW);
  } else {
    lcd.print("Out of Range");
  }

  delay(500);
}

int readDipSwitch() {
  int value = 0;
  for (int i = 0; i < 8; i++) {
    value = (value << 1) | (digitalRead(dipPins[i]) == LOW ? 1 : 0);
  }
  return value;
}
