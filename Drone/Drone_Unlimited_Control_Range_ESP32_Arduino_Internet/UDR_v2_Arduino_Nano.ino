/*  THIS CODE WAS CREATED BY ANISH DEY ON 5TH MARCH, 2020.

 *  THIS CODE IS A PART OF THE UNLIMITED DRONE RANGE V2 PROJECT.

 *  WHILE USING THIS CODE WITH THE ARDUINO NANO, IT WILL READ DATA

 *  FROM THE NODEMCU AND USING SOME CONDITIONS IT WILL FORWARD IT 

 *  TO THE CONNECTED FLIGHT CONTROLLER.

///////////////////////// Arduino Code ///////////////////////////

Circuit Diagram :       

YouTube Channel link :    

Upgraded versions are upcoming stay tuned.

*/

#include <SoftwareSerial.h>

#include<Servo.h>

SoftwareSerial portOne(2,3); //Rx Tx Terminal_Port

Servo Ch1_out;

Servo Ch2_out;

Servo Ch3_out;

Servo Ch4_out;

Servo Ch5_out;

int Ping_time;

unsigned long previousMillis = 0; 

unsigned long int A,B,C;

int x[15],ch1[15],ch[7],i;

int Comm =0;

int ARM;

int GPS;

int Req_F_Mode;

int Update_F_Mode =1000;

int Commands_Input = 0;

void setup() {

Serial.begin(9600);

portOne.begin(4800);

pinMode(A7,INPUT);

pinMode(5,INPUT);

pinMode(4,INPUT);

Ch1_out.attach(A6);

Ch2_out.attach(A5);

Ch3_out.attach(A4);

Ch4_out.attach(A3);

Ch5_out.attach(A2);

attachInterrupt(digitalPinToInterrupt(8), Read_val_IN, FALLING);

}



void loop() {

Ping_time = map(analogRead(A7), 0, 1023, 0, 255)*10;

Read_Rx(); 



//////////////////////////////Arming_Status & GPS_Status Reading//////////////////////////////  

/*int Arming_State = digitalRead(5);//A7 in Apm 2.8 for Arming Status

int GPS_State = digitalRead(4);//A6 in Apm 2.8 for GPS Status

  if (Arming_State ==0) a++; 

  if (Arming_State ==1) b++;

  if (GPS_State ==0) c++; 

  if (GPS_State ==1) d++;    

 if (b==1){

  ARM = HIGH;

 }                                    ///////////Malfunctioning//////////// 

 else if (a!=0 && b!=0){

  ARM = LOW;

 }

 if (d==1){

  GPS = HIGH;

}  

 else if (c!=0 && d!=0){

  GPS = LOW;

 }*/

////////////////////////////////////////////////////////////////////////////////////////////// 



///////////////////////////////////Communication_Switching////////////////////////////////////

if(Commands_Input == 0){Run_Communication_Switcher();}

//////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////Terminal_Detection//////////////////////////////////////

if(portOne.available() > 0){

String Read_Data = portOne.readString();

if(Read_Data == "arm"){

  Arm();

  Serial.println("Arming");

  Commands_Input = 1;

}

else if(Read_Data == "disarm"){

  Disarm();

  Serial.println("Disarming");

  Commands_Input = 1;

}

else if(Read_Data == "take off"){

  Take_Off();

  Serial.println("Take_Off Initiated");

  Commands_Input = 1;

}

else if(Read_Data == "land"){

  Land();

  Serial.println("Landing");

  Commands_Input = 1;

}

else if(Read_Data == "rtl"){

  RTL();

  Serial.println("RTL Initiated");

  Commands_Input = 2;

}

else if(Read_Data == "front"){

  Move_front();

  Serial.println("Moving Front");

  Commands_Input = 1;

}

else if(Read_Data == "back"){

  Move_back();

  Serial.println("Moving Back");

  Commands_Input = 1;

}

else if(Read_Data == "left"){

  Move_left();

  Serial.println("Moving Left");

  Commands_Input = 1;

}



else if(Read_Data == "stop" || Read_Data == "m"){

  Serial.println("Hovering over Manual Control ");

  Commands_Input = 0;

}



else if(Read_Data == "right"){

  Move_right();

  Serial.println("Moving Right");

  Commands_Input = 1;

}

else if(Read_Data == "climb"){

  Move_up();

  Serial.println("Climbing");

  Commands_Input = 1;

}

else if(Read_Data == "loiter"){

  Commands_Input = 2;

  Serial.println("Mode:- Loiter");

  Req_F_Mode = 1000;

}

else if(Read_Data == "althold"){

  Commands_Input = 2;

  Serial.println("Mode:- Althold");

  Req_F_Mode = 1500;

} 

/*//////Display_Management//////

else{

if(GPS == HIGH){

  portOne.println("1");

}

else if(GPS == LOW){

 portOne.println("2");  

}

if(Comm == 2){

  portOne.println("3");

}

else if(Comm == 1){

 portOne.println("4");  

}

if(ARM == HIGH){

  portOne.println("5");

}                          

else if(ARM == LOW){

 portOne.println("6");  

}

if(Update_F_Mode == 1000){

  portOne.println("7");

}

else if(Update_F_Mode == 1500){

  portOne.println("8");

}

else if(Update_F_Mode == 2000){

  portOne.println("9");

}

}*/

////////////////////////////





}

//////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////Flight_Mode_Decider//////////////////////////////////////

if(Commands_Input == 0 && Comm == 1){

  Ch5_out.write(map(ch[5], 1100, 1830, 55, 125));

}

else if(Commands_Input != 0){

 if(Commands_Input == 1){

   Update_F_Mode = 1000;

 }

 else if(Commands_Input == 2){

   Update_F_Mode = Req_F_Mode;

 }

  Ch5_out.write(map(Update_F_Mode, 1000, 2000, 55, 125));

}

//////////////////////////////////////////////////////////////////////////////////////////////

}



void Arm(){

  Ch1_out.write(93);

  Ch2_out.write(93);

  Ch3_out.write(55);

  Ch4_out.write(125);

delay(5000);

 Ch1_out.write(93);

 Ch2_out.write(93);

 Ch3_out.write(93);

 Ch4_out.write(93);  

}



void Disarm(){

  Ch1_out.write(93);

  Ch2_out.write(93);

  Ch3_out.write(55);

  Ch4_out.write(55);  

}





void Take_Off(){

  Ch1_out.write(93);

  Ch2_out.write(93);

  Ch3_out.write(55);

  Ch4_out.write(125);      

delay(5000);

 Ch1_out.write(93);

 Ch2_out.write(93);

 Ch3_out.write(93);

 Ch4_out.write(93); 

delay(1000);

  Ch1_out.write(93);

  Ch2_out.write(93);

  Ch3_out.write(125);

  Ch4_out.write(93); 

delay(2000);

 Ch1_out.write(93);

 Ch2_out.write(93);

 Ch3_out.write(93);

 Ch4_out.write(93);

}



void Land(){

  Ch1_out.write(93);

  Ch2_out.write(93);

  Ch3_out.write(70);

  Ch4_out.write(93);  

}



void RTL(){

  Req_F_Mode = 2000;

}



void Run_Communication_Switcher(){

if(Ping_time < 250 && ch[3] > 975 && Ping_time != 0){

  Bridge_Rx();

}

else if(Ping_time >= 250 && ch[3] > 975 && Ping_time != 0){

  Bridge_Rx();

}

else if(Ping_time < 250 && ch[3] <= 975 && Ping_time != 0){

  Bridge_IoT();

} 

else if(Ping_time >= 250 && ch[3] <= 975 && Ping_time != 0){

  RTL();

}

}



void Bridge_Rx(){

Ch1_out.write(map(ch[1], 1100, 1830, 55, 125));

Ch1_out.write(map(ch[2], 1100, 1830, 55, 125));

Ch1_out.write(map(ch[3], 1100, 1830, 55, 125));

Ch1_out.write(map(ch[4], 1100, 1830, 55, 125));

Comm=1;  

}



void Bridge_IoT(){

Ch1_out.write(map(pulseIn(9,HIGH), 9, 900, 58, 130));

Ch2_out.write(map(pulseIn(10,HIGH), 9, 900, 58, 130));

Ch3_out.write(map(pulseIn(11,HIGH), 9, 900, 58, 130));

Ch4_out.write(map(pulseIn(12,HIGH), 9, 900, 58, 130)); 

Comm=2;



}



void Move_front(){

  Ch1_out.write(93);

  Ch2_out.write(125);

  Ch3_out.write(93);

  Ch4_out.write(93); 

delay(2000);

 Ch1_out.write(93);

 Ch2_out.write(93);

 Ch3_out.write(93);

 Ch4_out.write(93);

}





void Move_back(){

  Ch1_out.write(93);

  Ch2_out.write(55);

  Ch3_out.write(93);

  Ch4_out.write(93);

delay(2000);

 Ch1_out.write(93);

 Ch2_out.write(93);

 Ch3_out.write(93);

 Ch4_out.write(93);

}



void Move_left(){

  Ch1_out.write(55);

  Ch2_out.write(93);

  Ch3_out.write(93);

  Ch4_out.write(93);

delay(2000);

 Ch1_out.write(93);

 Ch2_out.write(93);

 Ch3_out.write(93);

 Ch4_out.write(93);

}



void Move_right(){

  Ch1_out.write(125);

  Ch2_out.write(93);

  Ch3_out.write(93);

  Ch4_out.write(93);

delay(2000);

 Ch1_out.write(93);

 Ch2_out.write(93);

 Ch3_out.write(93);

 Ch4_out.write(93);

}



void Move_up(){

  Ch1_out.write(93);

  Ch2_out.write(93);

  Ch3_out.write(125);

  Ch4_out.write(93);  

delay(2000);

 Ch1_out.write(93);

 Ch2_out.write(93);

 Ch3_out.write(93);

 Ch4_out.write(93);

}



void Read_val_IN(){

A=micros(); 

C=A-B;      

B=A;        

x[i]=C;    

i=i+1;       

if(i==15){

 for(int j=0;j<15;j++) {ch1[j]=x[j];

 }

i=0;

}

} 

void Read_Rx(){

int i,j,k=0;

for(k=14;k>-1;k--){

  if(ch1[k]>10000)

  {j=k;}

}                  

for(i=1;i<=6;i++){

  ch[i]=(ch1[i+j]-1000);

}

} 
