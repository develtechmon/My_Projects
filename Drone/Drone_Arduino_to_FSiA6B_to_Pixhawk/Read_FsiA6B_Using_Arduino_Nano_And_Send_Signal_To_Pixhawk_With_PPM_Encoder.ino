#include <PPMReader.h>
#include <Servo.h>

#define CHANNEL_DEFAULT_VALUE 1500
int interruptPin = 3;

#define channelAmount 6
int CH[channelAmount];

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

PPMReader ppm(interruptPin, channelAmount); //PPM Library Object

void setup() {
  Serial.begin(115200);

  // for(int i=1; i<channelAmount; i++)
  // {
  //     CH[i-1]= CHANNEL_DEFAULT_VALUE;
  // }

  servo1.attach(5); // roll
  servo2.attach(6); //pitch 
  servo3.attach(7); //throttle
  servo4.attach(8); //yaw
  servo5.attach(9);
  servo6.attach(10);

}

void PPM_width_values()
{
  // for (int i=1; i<=channelAmount; i++)
  // {
  //   CH[i-1] = ppm.latestValidChannelValue(i,0);
  //   servo.write(CH[i-1]);
  // }

  /***DAPATKAN MAKLUMAT PPM UNTUK SETIAP CHANNEL***/
   CH[0] = ppm.latestValidChannelValue(1, 2006);
   CH[1] = ppm.latestValidChannelValue(2, 1050);
   CH[2] = ppm.latestValidChannelValue(3, 2008); //modify this value according to Radio Calibration value which in this case is Max
   CH[3] = ppm.latestValidChannelValue(4, 2006);

   CH[4] = ppm.latestValidChannelValue(5, 2006);
   CH[5] = ppm.latestValidChannelValue(6, 2006);
  /***DAPATKAN MAKLUMAT PPM UNTUK SETIAP CHANNEL***/

  //LAKUKAN SEBARANG AKTIVITI PROJECT SELEPAS DATA CHANNEL DITERIMA
  //>Code di sini
  servo1.write(CH[0]); 
  servo2.write(CH[1]);
  servo3.write(CH[2]);
  servo4.write(CH[3]);
  servo5.write(CH[4]);
  servo6.write(CH[5]);

  Serial.print("CH1:"); // roll
  Serial.print(CH[0]);
 
  Serial.print(" CH2:"); //pitch
  Serial.print(CH[1]);

  Serial.print(" CH3:"); //throttle
  Serial.print(CH[2]);

  Serial.print(" CH4:"); //yaw
  Serial.print(CH[3]);

  Serial.print(" CH5:");
  Serial.print(CH[4]);

  Serial.print(" CH6:");
  Serial.print(CH[5]);

  Serial.println();

}


void loop() {
  PPM_width_values();
}


