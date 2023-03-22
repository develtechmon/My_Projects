// ------- Include Configuration for PPM Reader --------
#include <PPMReader.h>

// #define CHANNEL_DEFAULT_VALUE 1500
int interruptPin = 3;

#define channelAmount 6
int CH[channelAmount];

#define sigPin 2          //set PPM signal output pin on the arduino
#define PPM_FrLen 27000   //22500   //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PulseLen 400 //300 //set the pulse length
#define onState 1

unsigned long eventInterval = 1000;
unsigned long previousTime1 = 0;
unsigned long previousTime2 = 0;

PPMReader ppm(interruptPin, channelAmount); //PPM Library Object

// ------- Include Configuration for Lidar ---------
#include <TFMPlus.h>  // Include TFMini Plus Library v1.5.0
TFMPlus tfmP;         // Create a TFMini Plus object
#include "printf.h"   // Modified to support Intel based Arduino
#include <SoftwareSerial.h>

SoftwareSerial mySerial(6,5); //RX, TX

int16_t tfDist = 0;    // Distance to object in centimeters
int16_t tfFlux = 0;    // Strength or quality of return signal
int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip
int counter = 0;
char dist[11];

void setup() {
  Serial.begin(115200);

  pinMode(sigPin, OUTPUT);
  digitalWrite(sigPin, !onState); 

  //Configure the interruption registers that will create the PPM signal
  cli();
  TCCR1A = 0; // set entire TCCR1 register to 0
  TCCR1B = 0;

  OCR1A = 100;  // compare match register (not very important, sets the timeout for the first interrupt)
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  TCCR1B |= (1 << CS11);  // 8 prescaler: 0,5 microseconds at 16mhz
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  sei();

  delay(20);               // Give port time to initalize
  printf_begin();          // Initialize printf.
  printf("\r\nTFMPlus Library Example - 10SEP2021\r\n");  // say 'hello'

  mySerial.begin( 115200);  // Initialize TFMPLus device serial port.
  delay(20);               // Give port time to initalize
  tfmP.begin( &mySerial);   // Initialize device library object and...

  // pass device serial port to the object.

  // Send some example commands to the TFMini-Plus
  // - - Perform a system reset - - - - - - - - - - -
  printf( "Soft reset: ");
  if( tfmP.sendCommand( SOFT_RESET, 0))
  {
    printf( "passed.\r\n");
  }
  else tfmP.printReply();

  delay(500);  // added to allow the System Rest enough time to complete

  // - - Display the firmware version - - - - - - - - -
  printf( "Firmware version: ");
  if( tfmP.sendCommand( GET_FIRMWARE_VERSION, 0))
  {
    printf( "%1u.", tfmP.version[ 0]); // print three single numbers
    printf( "%1u.", tfmP.version[ 1]); // each separated by a dot
    printf( "%1u\r\n", tfmP.version[ 2]);
  }
  else tfmP.printReply();
  // - - Set the data frame-rate to 20Hz - - - - - - - -
  printf( "Data-Frame rate: ");
  if( tfmP.sendCommand( SET_FRAME_RATE, FRAME_20))
  {
    printf( "%2uHz.\r\n", FRAME_20);
  }
  else tfmP.printReply();

  // for(int i=1; i<channelAmount; i++)
  // {
  //     CH[i-1]= CHANNEL_DEFAULT_VALUE;
  // }

}

void loop() {
  
 // unsigned long currentTime=millis();

  PPM_width_values();

}

void PPM_width_values()
{

  
  delay(20);   // Loop delay to match the 20Hz data frame rate
  counter++;
  if( tfmP.getData( tfDist, tfFlux, tfTemp)) // Get data from the device.
  {
    // printf( "Dist:%04icm ", tfDist);   // display distance,
    // printf( "Flux:%05i ",   tfFlux);   // display signal strength/quality,
    // printf( "Temp:%2i%s",  tfTemp, "C");   // display temperature,
    printf( "\r\n");                   // end-of-line.
    if(counter >= 10){
      sprintf (dist, "%04i", tfDist);
      counter=0;
    }
  }
  else                  // If the command fails...
  {
    tfmP.printFrame();  // display the error and HEX dataa
  }

  // for (int i=1; i<=channelAmount; i++)
  // {
  //   CH[i-1] = ppm.latestValidChannelValue(i,0);
  // }

  /***DAPATKAN MAKLUMAT PPM UNTUK SETIAP CHANNEL***/
   CH[0] = ppm.latestValidChannelValue(1, 0);
   CH[1] = ppm.latestValidChannelValue(2, 0);
   //CH[2] = map(ppm.latestValidChannelValue(3, 1900),1052,1900,1046,1900); //modify this value according to Radio Calibration value which in this case is Max
   CH[2] = ppm.latestValidChannelValue(3, 2076); //modify this value according to Radio Calibration value which in this case is Max

   CH[3] = ppm.latestValidChannelValue(4, 0);
   CH[4] = ppm.latestValidChannelValue(5, 0);
   CH[5] = ppm.latestValidChannelValue(6, 0);

  /***DAPATKAN MAKLUMAT PPM UNTUK SETIAP CHANNEL***/

  //LAKUKAN SEBARANG AKTIVITI PROJECT SELEPAS DATA CHANNEL DITERIMA

  if (tfDist < 60)
  {
    //Serial.println("b");
    CH[1] = 1600;//ppm.latestValidChannelValue(2, 1900);
  }
  
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

  Serial.print(" Distance:");
  Serial.print(tfDist);

  //Serial.println();
}

#define clockMultiplier 2 // set this to 2 if you are using a 16MHz arduino, leave as 1 for an 8MHz arduino

//Interruption vector. here we create the PPM signal
ISR(TIMER1_COMPA_vect){
  static boolean state = true;

  TCNT1 = 0;

  if ( state ) {
    //end pulse
    PORTD = PORTD & ~B00000100; // turn pin 2 off. Could also use: digitalWrite(sigPin,0)
    //digitalWrite(sigPin, onState);
    OCR1A = PPM_PulseLen * clockMultiplier;
    state = false;
  }

  else {
    //start pulse
    static byte cur_chan_numb;
    static unsigned int calc_rest;

    PORTD = PORTD | B00000100; // turn pin 2 on. Could also use: digitalWrite(sigPin,1)
    //digitalWrite(sigPin, !onState);
    state = true;

    if(cur_chan_numb >= channelAmount) {
      cur_chan_numb = 0;
      calc_rest += PPM_PulseLen;
      OCR1A = (PPM_FrLen - calc_rest) * clockMultiplier;
      calc_rest = 0;
    }

    else {
      OCR1A = (CH[cur_chan_numb] - PPM_PulseLen) * clockMultiplier;
      //OCR1A = (CH[cur_chan_numb]) * clockMultiplier;
      calc_rest += CH[cur_chan_numb];
      cur_chan_numb++;
    }     
  }
} 

