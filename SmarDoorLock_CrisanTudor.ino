#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

#define buzzer 20

LiquidCrystal lcd(14, 15, 16, 17, 18, 19);

char keys[4][4] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

byte rowPin[4] = { 4, 5, 6, 7 };
byte colPin[4] = { 8, 9, 10, 11 };

Servo servo_Motor;
String password = "159";
int position = 0;

int wrong = 0;

int redPin = 9;
int greenPin = 8;

Keypad keypad = Keypad(makeKeymap(keys), rowPin, colPin, 4, 4);

int totalWrongAttemps = 0;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("SMART DOOR LOCK");
  delay(2000);
  lcd.clear();

  servo_Motor.attach(3);
  setLocked(true);
  delay(1000);

  pinMode(buzzer, OUTPUT);
}

void loop() {

  lcd.clear();
  lcd.print("Enter Password:");
  delay(100);

  char pressed = keypad.getKey();
  String key[3];

  if (pressed) {
    lcd.clear();
    lcd.print("Enter Password:");
    lcd.setCursor(position, 2);
    lcd.print(pressed);
    delay(500);
    if (pressed == '*' || pressed == '#') {
      position = 0;
      setLocked(true);
      lcd.clear();
    }

    else if (pressed == password[position]) {
      key[position] = pressed;
      position++;
    }

    else if (pressed != password[position]) {
      wrong++;
      position++;
    }

    if (position == 3) {
      if (wrong > 0) {
        totalWrongAttemps++;
        wrong = 0;
        position = 0;
        lcd.clear();
        lcd.print("WRONG");
        lcd.setCursor(5, 2);
        lcd.print("PASSWORD");
        delay(1000);
        setLocked(true);
      }

      else if (position == 3 && wrong == 0) {
        position = 0;
        wrong = 0;
        lcd.clear();
        lcd.print("PASSWORD");
        lcd.setCursor(6, 2);
        lcd.print("ACCEPTED");
        delay(2000);
        lcd.clear();
        lcd.print("Door Open");
        delay(2000);
        setLocked(false);
      }

      if (totalWrongAttemps == 3) {
        totalWrongAttemps = 0;
        buzzer_beep();
        delay(500);
      }
    }
  }
}

void setLocked(int locked) {
  if (locked) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    delay(1000);
    servo_Motor.attach(3);
    servo_Motor.write(10);
    delay(1000);
    servo_Motor.detach();
  } else {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    delay(1000);
    servo_Motor.attach(3);
    servo_Motor.write(90);
    delay(1000);
    servo_Motor.detach();
  }
}

void buzzer_beep() {
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  delay(1000);
  lcd.clear();
  delay(2000);
  while (1) {
    lcd.scrollDisplayLeft();
    delay(200);
  }
}
