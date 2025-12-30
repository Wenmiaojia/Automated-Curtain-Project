#include <LiquidCrystal.h>

// LCD pin mapping (UNCHANGED)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Button
const int buttonPin = 7;

// H-bridge pins
const int IN1 = 8;
const int IN2 = 9;
const int ENA = 10;

int buttonState = HIGH;
int lastButtonState = HIGH;

// false = VACANT (curtain open)
// true  = OCCUPIED (curtain closed)
bool occupied = false;

void setup() {
  lcd.begin(16, 2);

  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  stopMotor();

  // Initial display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Status:");
  lcd.setCursor(0, 1);
  lcd.print("VACANT");
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // Detect button press
  if (buttonState == LOW && lastButtonState == HIGH) {
    occupied = !occupied;   // toggle state

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Status:");
    lcd.setCursor(0, 1);

    if (occupied) {
      lcd.print("OCCUPIED");
      closeCurtain();
    } else {
      lcd.print("VACANT");
      openCurtain();
    }

    delay(200); // debounce
  }

  lastButtonState = buttonState;
}

// ===== Motor Functions =====

void openCurtain() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 180);   // speed (0–255)

  delay(3000);             // motor run time (adjust!)
  stopMotor();
}

void closeCurtain() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 180);

  delay(3000);             // motor run time (adjust!)
  stopMotor();
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}
