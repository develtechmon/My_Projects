int myPins[6] = {3, 4, 5, 11, 10, 9};

void setup() {

  for (int i = 0; i < 6; i++) {
    pinMode(myPins[0], OUTPUT);
  }
  Serial.begin(9600);

  ///////////// Testing Code /////////
  // RIGHT MOTOR
  digitalWrite(myPins[1], 0);
  digitalWrite(myPins[2], 1);
  analogWrite(myPins[0], 160);

  // LEFT MOTOR
  digitalWrite(myPins[3], 0);
  digitalWrite(myPins[4], 1);
  analogWrite(myPins[5], 160);

  delay(3000);
  analogWrite(myPins[0], 0);
  analogWrite(myPins[5], 0);
}

void loop() {}
