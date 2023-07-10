#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Letak pin sensor
const int flamePin = 8; // Pin digital untuk sensor kebakaran
const int smokePin = A1; // Pin digital untuk sensor asap
const int buzzerPin = 5; // Pin digital untuk buzzer
const int thresholdFlame = 1; // Ambang batas nilai sensor kebakaran
const int thresholdSmoke = 150; // Ambang batas nilai sensor asap

void setup() {
  Serial.begin(9600);

  // LCD
  pinMode(5, OUTPUT);
  pinMode(8, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.print("WELCOME");
  delay(1000);
  lcd.clear();
  lcd.print("Project : S1SD1G");
  delay(1000);
  lcd.clear();
}

bool isFireDetected = true; // Variabel penanda kebakaran

void loop() {
  int flameValue = digitalRead(flamePin);
  int smokeValue = analogRead(smokePin);

  lcd.setCursor(0, 0);
  lcd.print("Fire       : ");
  lcd.print(flameValue);

  lcd.setCursor(0, 1);
  lcd.print("Fire Smoke : ");
  lcd.print(smokeValue);

  delay(1500);
  lcd.clear();

  if (flameValue < thresholdFlame || smokeValue > thresholdSmoke) {
    if (!isFireDetected) {
      lcd.setCursor(1, 0);
      lcd.print("WARNING!");
      lcd.setCursor(1, 1);
      lcd.print("Happened Fire!");

      activateBuzzer(); // Mengaktifkan bunyi buzzer saat terdeteksi kebakaran
      isFireDetected = true; // Mengubah variabel penanda kebakaran menjadi true
    }
  } else {
    if (isFireDetected) {
      lcd.setCursor(0, 0);
      lcd.print("No Fire/Smoke");
      lcd.setCursor(0, 1);
      lcd.print("Have A Nice Day!");

      deactivateBuzzer(); // Mematikan bunyi buzzer jika tidak ada kebakaran
      isFireDetected = false; // Mengubah variabel penanda kebakaran menjadi false
    }
  }

  delay(1000); // Jeda 1 detik antara pembacaan nilai sensor
  lcd.clear(); // Bersihkan layar LCD
}

void activateBuzzer() {
  digitalWrite(5, HIGH); // Mengaktifkan buzzer dengan memberikan sinyal tinggi
}

void deactivateBuzzer() {
  digitalWrite(5, LOW); // Mematikan buzzer dengan memberikan sinyal rendah
}
