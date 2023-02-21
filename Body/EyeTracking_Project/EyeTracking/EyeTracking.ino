#include <Servo.h>

#define numOfValsRec 2
#define digitsPerValRec 3

Servo myservoLR;  
Servo myservoUD; 

int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1;
int counter = 0;
bool counterStart = false;
String receivedString;


void setup() {

  Serial.begin(9600);
  myservoLR.attach(9);  
  myservoUD.attach(10); 
  myservoLR.write(90);     
  myservoUD.write(90); 
}


void receiveData()
{

  while (Serial.available()) {

    char c = Serial.read();

    if (c == '$') {
      counterStart = true;
    }
    if (counterStart) {
      if (counter < stringLength) {
        receivedString = String(receivedString + c);
        counter++;
      }

      if (counter >= stringLength) {

        for (int i = 0; i < numOfValsRec; i++)
        {
          int num = (i * digitsPerValRec) + 1;
          valsRec[i] = receivedString.substring(num, num + digitsPerValRec).toInt();
        }

        receivedString = "";
        counter = 0;
        counterStart = false;

      }
    }
  }


}


void loop() {

receiveData();
myservoLR.write(valsRec[0]);
myservoUD.write(valsRec[1]);
}
