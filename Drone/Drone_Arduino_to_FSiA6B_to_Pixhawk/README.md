# Arduino_to_FSiA6B_to_Pixhawk

### This project implying on how to override FsiA6B receiver using Arduino Nano.

#### First Install below prequisites before proceed:
a. From Arduino search for "PPM-reader" library by Aapo Nikkila, Dmitry Grigoryev

b. Use "Read_FsiA6B_Using_Arduino.ino" code to receiver PPM value. This is working and correct code now. The rest is only for my code reference

c. Next, we're going to establish schematic connection between "FsiA6B", "Arduino" and "Pixhawk". To do this refer to the connectionn pin below:
NOTE : We're reading PPM using D3 (Interrupt Pin). Therefore please connect PPM from receiver to D3 of arduino
Next, we're going create PPM output using D2 (Output Pin for PPM) which we will connect to Pixhawk (RC1)
			    
| FSIA6B | Arduino | Pixhawk |

  |   5V   |   5V    |  5V     |

  |   GND  |   GND   |  GND    |
 
  |   PPM  |   D3    |    D2     |
	
d. Use "Read_FsiA6B_Using_Arduino_Nano_And_Send_Signal_To_Pixhawk.ino" code to control drone using "Overrided" FSiA6B. This is working code now. Use
this for experiment

e. This is useful link that help me to comeout with this solution

### https://matgyver.my/2021/06/15/arduino-baca-signal-ppm-remote-rc-receiver/
### https://miscircuitos.com/how-to-read-rc-radio-signals-with-arduino-using-ppm-signal-tutorials/
## https://quadmeup.com/generate-ppm-signal-with-arduino/

