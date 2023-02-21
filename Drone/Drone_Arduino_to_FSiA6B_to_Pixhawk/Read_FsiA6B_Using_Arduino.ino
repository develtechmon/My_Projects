/*

Author : Lukas Johnny
Date : 14-September-2022
Description : Use Arduino Nano to read PPM value for Fs-iA6B receiver. Below is designation for each channel
             CH1 : Roll Input
             CH2 : Pitch Input
             CH3 : Throttle Input
             Ch4 : Yaw Input
*/

#include <PPMReader.h>

int interruptPin = 3;

#define channelAmount 6
int CH[channelAmount];

PPMReader ppm(interruptPin, channelAmount); //PPM Library Object

//VARIABLE SIMPAN DATA CHANNEL
int CH1 = 1500; //1500
int CH2 = 1500; //1488
int CH3 = 1500; //1028
int CH4 = 1500; //1500
int CH5 = 1500; //1100
int CH6 = 1500; //1162

void setup() {
  Serial.begin(115200);
}

void PPM_width_values()
{
  // for (int i=1; i<=channelAmount; i++)
  // {
  //   CH[i-1] = ppm.latestValidChannelValue(i,0);
  // }

  /***DAPATKAN MAKLUMAT PPM UNTUK SETIAP CHANNEL***/
   CH[0] = ppm.latestValidChannelValue(1, 0);
   CH[1] = ppm.latestValidChannelValue(2, 0);
   CH[2] = ppm.latestValidChannelValue(3, 0);
   CH[3] = ppm.latestValidChannelValue(4, 0);
   CH[4] = ppm.latestValidChannelValue(5, 0);
   CH[5] = ppm.latestValidChannelValue(6, 0);
  /***DAPATKAN MAKLUMAT PPM UNTUK SETIAP CHANNEL***/

  //LAKUKAN SEBARANG AKTIVITI PROJECT SELEPAS DATA CHANNEL DITERIMA
  //>Code di sini
  //>Code di sini
  //>Code di sini
  //>Code di sini
  
  Serial.print("CH1:");
  Serial.print(CH[0]);

  Serial.print(" CH2:");
  Serial.print(CH[1]);

  Serial.print(" CH3:");
  Serial.print(CH[2]);

  Serial.print(" CH4:");
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

