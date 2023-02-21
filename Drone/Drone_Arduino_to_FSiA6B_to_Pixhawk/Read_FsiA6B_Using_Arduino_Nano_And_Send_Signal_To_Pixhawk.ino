#include <PPMReader.h>

// #define CHANNEL_DEFAULT_VALUE 1500
int interruptPin = 3;

#define channelAmount 6
int CH[channelAmount];

#define sigPin 2          //set PPM signal output pin on the arduino
#define PPM_FrLen 27000   //22500   //set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PulseLen 400 //300 //set the pulse length
#define onState 1

PPMReader ppm(interruptPin, channelAmount); //PPM Library Object

void setup() {
  Serial.begin(115200);

  // for(int i=1; i<channelAmount; i++)
  // {
  //     CH[i-1]= CHANNEL_DEFAULT_VALUE;
  // }

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

}

void loop() {
  PPM_width_values();
}

void PPM_width_values()
{
  // for (int i=1; i<=channelAmount; i++)
  // {
  //   CH[i-1] = ppm.latestValidChannelValue(i,0);
  // }

  /***DAPATKAN MAKLUMAT PPM UNTUK SETIAP CHANNEL***/
   CH[0] = ppm.latestValidChannelValue(1, 1900);
   CH[1] = ppm.latestValidChannelValue(2, 1900);
   //CH[2] = map(ppm.latestValidChannelValue(3, 1900),1052,1900,1046,1900); //modify this value according to Radio Calibration value which in this case is Max
   CH[2] = ppm.latestValidChannelValue(3, 1900); //modify this value according to Radio Calibration value which in this case is Max

   CH[3] = ppm.latestValidChannelValue(4, 1900);
   CH[4] = ppm.latestValidChannelValue(5, 1900);
   CH[5] = ppm.latestValidChannelValue(6, 1900);

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


