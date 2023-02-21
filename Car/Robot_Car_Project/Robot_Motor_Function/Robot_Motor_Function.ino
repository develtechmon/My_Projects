int myPins[6] = {3, 4, 5, 11, 10, 9};


void moveRobot (int mySpeed, int myTurn, int maxSpeed = 255)
{
  /*
   * mySpeed and myTurn range from -100 to 100
   * + val of mySpeed is forward and - is backwards
   * + val of myTurn is left and - is right
   */
  
  mySpeed = map(mySpeed, -100, 100, -maxSpeed, maxSpeed);
  myTurn = map(myTurn, -100, 100, -maxSpeed, maxSpeed);

  int leftSpeed = mySpeed - myTurn;
  int rightSpeed = mySpeed + myTurn;

  leftSpeed = constrain(leftSpeed, -maxSpeed, maxSpeed);
  rightSpeed = constrain(rightSpeed, -maxSpeed, maxSpeed);

  if (rightSpeed > 0) {
    digitalWrite(myPins[1], 0);
    digitalWrite(myPins[2], 1);
  }
  else {
    digitalWrite(myPins[1], 1);
    digitalWrite(myPins[2], 0);
  }


  if (leftSpeed > 0) {
    digitalWrite(myPins[3], 0);
    digitalWrite(myPins[4], 1);
  }
  else {
    digitalWrite(myPins[3], 1);
    digitalWrite(myPins[4], 0);
  }

analogWrite(myPins[0], abs(rightSpeed));
analogWrite(myPins[5], abs(leftSpeed));
}


void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(myPins[i], OUTPUT);
  }
  Serial.begin(9600);

  ///////////// Testing Code /////////
  moveRobot(50,-20);
  delay(3000);
  moveRobot(0,0);

}


void loop() {


}
