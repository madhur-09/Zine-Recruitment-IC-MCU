int latchPin = 5;  // Latch pin of 74HC595 is connected to D5
int clockPin = 6;  // Clock pin of 74HC595 is connected to D6
int dataPin = 4;   // Data pin of 74HC595 is connected to D4

void setup() {
  Serial.begin(9600);

  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  myData = 0;  // data to be send
  updateShiftRegister();
  delay(500);

  // some code/algorithm that will set bits for myData

  bitSet(myData, i);
  updateShiftRegister();
}

void updateShiftRegister() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, myData);
  digitalWrite(latchPin, HIGH);
}