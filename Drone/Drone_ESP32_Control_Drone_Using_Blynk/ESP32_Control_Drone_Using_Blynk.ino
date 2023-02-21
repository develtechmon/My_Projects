#define BLYNK_PRINT serial
#include ESP8266WiFi.h
#include BlynkSimpleEsp8266.h
Servo servo;
char auth = "Mq9JcRJhCmaDvYuoJzVJ5BD2J6KI5vtZ"; //Enter your Blynk application auth token
char ssid= "Dialog 4G 025"; //Enter your WIFI name
char pass = "jangu1234"; //Enter your WIFI passowrd



void setup ()  
  serial.begin(9600);
  servo.attach(D0);
  servo.attach(D1);
  servo.attach(D2);
  servo.attach(D3);
  servo.attach(D4);
  Blynk.begin(auth, ssid, pass)


void loop() 
  Blynk.run()


BLYNK_WRITE(V0) 
  servo.write(Map(param.asInt(),0,1023,1000,2000))


BLYNK_WRITE(V1) 
   servo.write(Map(param.asInt(),0,1023,1000,2000))


BLYNK_WRITE(V2) 
  servo.write(Map(param.asInt(),0,1023,1000,2000))


BLYNK_WRITE(V3) 
  servo.write(Map(param.asInt(),0,1023,1000,2000))


BLYNK_WRITE(V4) 
  servo.write(Map(param.asInt(),0,1023,1000,2000))