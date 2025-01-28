#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x20, 16, 2);

// Motor A connections
int enA = 10;
int in1 = 9;
int in2 = 6;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

#define ldr1 A1
#define ldr2 A2
#define pot1 A0
#define batt A3

int thresh = 0;
int speed1 = 0;
int speed2 = 0;
int dataLdr1 = 0;
int dataLdr2 = 0;
int battPercent = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(ldr1, INPUT);
  pinMode(ldr2, INPUT);
  pinMode(pot1, INPUT);
  pinMode(batt, INPUT);

  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  thresh = map(analogRead(pot1), 0, 1023, 500, 997);
  battPercent = map(analogRead(batt), 780, 1023, 30, 100);

  lcd.home();

  dataLdr1 = analogRead(ldr1);  //997 to 100
  dataLdr2 = analogRead(ldr2);  //997 to 100

  if (dataLdr1 < thresh || dataLdr2 < thresh) {
    speed1 = map(dataLdr1, 997, 100, 50, 255);  //997~0 and 100~255
    speed2 = map(dataLdr2, 997, 100, 50, 255);  //997~0 and 100~255
  } else {
    speed1 = 0;
    speed2 = 0;
  }

  lcd.setCursor(0, 0);
  lcd.print(dataLdr1);
  lcd.setCursor(5, 0);
  lcd.print(dataLdr2);
  lcd.setCursor(10, 0);
  lcd.print(thresh);
  lcd.setCursor(0, 1);
  lcd.print(battPercent);
  lcd.setCursor(5, 1);
  lcd.print("%");

  if (dataLdr1 > dataLdr2 && ((dataLdr1 - dataLdr2) * (dataLdr1 - dataLdr2)) > 50) {
    leftturn();
  } else if (dataLdr1 < dataLdr2 && ((dataLdr1 - dataLdr2) * (dataLdr1 - dataLdr2)) > 50) {
    rightturn();
  } else {
    forward();
  }
}

void leftturn() {
  analogWrite(enA, speed1);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void rightturn() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  analogWrite(enB, speed2);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void forward() {
  analogWrite(enA, speed1);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  analogWrite(enB, speed1);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}