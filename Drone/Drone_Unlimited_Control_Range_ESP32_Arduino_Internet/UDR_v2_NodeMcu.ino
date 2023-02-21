/*  THIS CODE WAS CREATED BY ANISH DEY ON 5TH MARCH, 2020.

 *  THIS CODE IS A PART OF THE UNLIMITED DRONE RANGE V2 PROJECT.

 *  TO THE CONNECTED FLIGHT CONTROLLER.

///////////////////////// NodeMcu Code ///////////////////////////

Circuit Diagram :       

YouTube Channel link :    

Upgraded versions are upcoming stay tuned.

*/

#include <ESP8266Ping.h>

#include <SoftwareSerial.h>

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>

char auth[] = "***********";      // put your Blynk AuthToken here     

char ssid[] = "***********";      // put your WiFi Router SSID here    

char pass[] = "***********";      // put your WiFi Router Password here  

const char* remote_host = "www.google.com";

String avg_time_ms;

BlynkTimer timer;

SoftwareSerial portOne(D1,D0); //Rx Tx Terminal_Port

WidgetLCD lcd(V0);

WidgetTerminal terminal(V3);



BLYNK_WRITE(V3){

 portOne.write(param.asStr());

}

/*

void myTimerEvent2(){

  if(portOne.available() > 0){

int Read = portOne.parseInt();

if(Read == 1){

lcd.print(0,0,"GPS_OK");        

}

else if(Read == 2){

lcd.print(0,0,"NO_GPS");        

}



if(Read == 3){

lcd.print(0,1,"4G");        

}                            // Display Malfunctioning (Updating Soon)

else if(Read == 4){

lcd.print(0,1,"Rx");        

}



if(Read == 5){

lcd.print(4,1,"Armed");        

}

else if(Read == 6){

lcd.print(4,1,"Disarmed");        

}



if(Read == 7){

lcd.print(8,0,"Loiter");        

}

else if(Read == 8){

lcd.print(8,0,"Althold");        

}

else if(Read == 9){

lcd.print(8,0,"RTL");        

}

}

}*/

void myTimerEvent1(){

int i;

  if(Ping.ping(remote_host)) {

    Ping.ping(remote_host, 10);  

    i= Ping.averageTime();

    avg_time_ms = Ping.averageTime();

  }

Blynk.virtualWrite(V4,i);

analogWrite(A0,i/10);

}



void setup(){

portOne.begin(4800);

while (!portOne){;}

  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

timer.setTimer(3000, myTimerEvent1, 1); //running once in every 3 seconds.

//timer.setTimer(1000, myTimerEvent2, 5); //running 50_times in every second.

pinMode(A0,OUTPUT);

}



void loop(){

  Blynk.run();

  timer.run();

}
