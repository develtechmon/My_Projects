
#include <Servo.h>

Servo myservoLR;  
Servo myservoUD; 


void setup() {
  myservoLR.attach(9);  
  myservoUD.attach(10); 

}
void loop() {


///// Center 
    myservoLR.write(90);     
    myservoUD.write(90); 

///// Left and Right Range 
//    myservoLR.write(90+45);
//    delay(1000);  
//    myservoLR.write(90);
//    delay(1000); 
//    myservoLR.write(90-45); 
//    delay(1000); 
//    myservoLR.write(90);
//    delay(1000);  

//// Up and Down Range 
//    myservoUD.write(90+45);
//    delay(1000);  
//    myservoUD.write(90);
//    delay(1000); 
//    myservoUD.write(90-45); 
//    delay(1000); 
//    myservoUD.write(90);
//    delay(1000);  
     
  
}
