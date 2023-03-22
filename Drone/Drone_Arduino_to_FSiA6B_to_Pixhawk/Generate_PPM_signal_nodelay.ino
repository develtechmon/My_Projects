#define channumber 6 //How many channels have your radio?
int channel[channumber]; //read Channel values
int PPMin = 3;

void setup()
{
  Serial.begin(115200); //Start serial
  pinMode(PPMin, INPUT); // Pin 3 as input
}

void loop()
{
  //waits ultil synchronize arrives > 4 miliseconds
  if(pulseIn(PPMin , HIGH) > 2000) //If pulse > 4 miliseconds, continues
  {
    for(int i = 1; i <= channumber; i++) //Read the pulses of the remainig channels
    {
      channel[i-1]=pulseIn(PPMin, HIGH);
    }
    // for(int i = 1; i <= channumber; i++) //Prints all the values readed
    // {
    //   Serial.print("CH"); //Channel
    //   Serial.print(i); //Channel number
    //   Serial.print(": "); 
    //   Serial.println(channel[i-1]); //Print the value
    // }
      Serial.print("Ch1: ");
      Serial.print(channel[1-1]);
      Serial.print(" | Ch2: ");
      Serial.print(channel[2-1]);
      Serial.print(" | Ch3: ");
      Serial.print(channel[3-1]);
      Serial.print(" | Ch4: ");
      Serial.print(channel[4-1]);
      Serial.print(" | Ch5: ");
      Serial.print(channel[5-1]);
      Serial.print(" | Ch6: ");
      Serial.println(channel[6-1]);

    // delay(200);//Give time to print values.
  }
}