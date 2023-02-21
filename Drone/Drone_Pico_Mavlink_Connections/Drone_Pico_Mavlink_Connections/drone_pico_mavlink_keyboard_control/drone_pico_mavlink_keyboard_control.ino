/*

Here i'm using raspberry Pi Pico W to run this code.
Connect RX of Pixhawk to UARTO TX - GPO of Pico
Connect TX of Pixhawk to UARTO RX - GP1 of Pico

Refer to Raspberry Pi Pico W pin list for reference

*/
#include "C:\Users\Lukas\Documents\Arduino\libraries\mavlinkv2\common\mavlink.h"
unsigned long HeartbeatTime = 0;

int current_roll = 0;
int current_pitch = 0;
int current_throttle = 0;  //Min value is 1150 to run motors
int current_yaw = 0;

void setup() {
  Serial1.begin(57600);
  Serial.begin(57600);
  Serial.println("MAVLink starting.");
}

void loop() {
  if ((millis() - HeartbeatTime) > 1000) {
    HeartbeatTime = millis();
    PIX_HEART_BEAT();
  }

  if (Serial.available() > 0) {
    // read incoming serial data:
    char inChar = Serial.read();

    if (inChar == 'a') {
      Serial.println("ARM DRONE");
      ARM('a');
    }

    else if (inChar == 'o') {
      Serial.println("DISARM DRONE");
      ARM('o');
    }

    else if (inChar == 't') {
      Serial.println("TAKEOFF MODE");
      TAKEOFF();
    }

    else if (inChar == 'g') {
      Serial.println("GUIDED MODE");
      CHANGEMODE(4);
    }

    else if (inChar == 's') {
      Serial.println("STABILIZE MODE");
      CHANGEMODE(0);
    }

    else if (inChar == 'r') {
      Serial.println("STABILIZE MODE");
      CHANGEMODE(6);
    }

    else if (inChar == 'l') {
      Serial.println("STABILIZE MODE");
      CHANGEMODE(9);
    }

    else if (inChar == 'v') {
      Serial.println("OVERRIDE MODE");
      OVERRIDE_RC(current_roll, current_pitch, current_throttle, current_yaw);
    }
  }
}

void PIX_HEART_BEAT() {
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  uint16_t len;
  mavlink_msg_heartbeat_pack(1, 0, &msg, MAV_TYPE_QUADROTOR, MAV_AUTOPILOT_GENERIC, 0, 1, 0);  // System ID = 255 = GCS
  len = mavlink_msg_to_send_buffer(buf, &msg);

  Serial1.write(buf, len);
}

void CHANGEMODE(int mode) {
  //Set message variables
  uint8_t _system_id = 255;     // id of computer which is sending the command (ground control software has id of 255)
  uint8_t _component_id = 151;  // seems like it can be any # except the number of what Pixhawk sys_id is
  uint8_t _target_system = 1;   // Id # of Pixhawk (should be 1)
  uint8_t _base_mode = 1;
  uint32_t _custom_mode = mode;  //10 = auto mode

  /*
Flight / Driving Modes (change custom mode above)

0 - stabilize
1 - acro
2 - althold
3 - auto
4 - guided
5 - loiter
6 - RTL
7 - Circle
8 - 
9 - Land
10 - 
11 - Drift
12
*/

  // Initialize the required buffers
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  // Pack the message
  mavlink_msg_set_mode_pack(_system_id, _component_id, &msg, _target_system, _base_mode, _custom_mode);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);  // Send the message (.write sends as bytes)
  Serial.print("\nsending set mode command...");
  Serial1.write(buf, len);  //Write data to serial port
}

void OVERRIDE_RC(int roll, int pitch, int throttle, int yaw) {
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  mavlink_msg_rc_channels_override_pack(255, 151, &msg, 1, 0, roll, pitch, throttle, yaw, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);  // CHANNEL = 1(ROLL), 2(PITCH), 3(Throttle), 4(Yaw) , 5, 6, 7, 8

  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  Serial1.write(buf, len);
}

void TAKEOFF() {

  // Method 1
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];
  mavlink_msg_command_long_pack(255, 151, &msg, 1, 1, 22, 1, 0, 0, 0, 0, 0, 0, 0.5);
  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  Serial1.write(buf, len);

  // Method 2
  // mavlink_message_t messaggio; //messaggio da inviare
  // mavlink_command_long_t comando; //struttura dati relativa al comando mavlink long
  // char buf[MAVLINK_MAX_PACKET_LEN];
  // comando.command = 22; //settaggio valori della struct relativa al comando
  // comando.target_system = 1;
  // comando.target_component = 1;
  // comando.confirmation = true;
  // comando.param1 = 0;
  // comando.param2 = 0;
  // comando.param3 = 0;
  // comando.param4 = 0;
  // comando.param5 = 0;
  // comando.param6 = 0;
  // comando.param7 = 0.5;

  // mavlink_msg_command_long_encode(255, 151, &messaggio, &comando);
  // unsigned len = mavlink_msg_to_send_buffer((uint8_t*)buf, &messaggio);
  // Serial1.write(buf, len);
}

void ARM(char menu) {
  // 400 is referring to MAV_CMD_COMPONENT_ARM_DISARM (400 ). See https://mavlink.io/en/messages/common.html

  //Method 1
  mavlink_message_t msg;
  uint8_t buf[MAVLINK_MAX_PACKET_LEN];

  if (menu == 'a') {
    mavlink_msg_command_long_pack(255, 151, &msg, 1, 1, 400, 1, 1, 0, 0, 0, 0, 0, 0);
  } else if (menu = 'o') {
    mavlink_msg_command_long_pack(255, 151, &msg, 1, 1, 400, 1, 0, 0, 0, 0, 0, 0, 0);
  }

  uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
  Serial1.write(buf, len);

  //Method 2
  // mavlink_message_t messaggio;
  // mavlink_command_long_t comando; //struttura dati relativa al comando mavlink long
  // char buf[MAVLINK_MAX_PACKET_LEN];

  // if (menu == 1) {
  // char buf[MAVLINK_MAX_PACKET_LEN];
  // comando.command = 400; //settaggio valori della struct relativa al comando
  // comando.target_system = 1;
  // comando.target_component = 1;
  // comando.confirmation = true;
  // comando.param1 = 1;
  // comando.param2 = 1;
  // comando.param3 = 0;
  // comando.param4 = 0;
  // comando.param5 = 0;
  // comando.param6 = 0;
  // comando.param7 = 0;
  // }

  // else if (menu == 0) {
  // comando.command = 400; //settaggio valori della struct relativa al comando
  // comando.target_system = 1;
  // comando.target_component = 1;
  // comando.confirmation = true;
  // comando.param1 = 0;
  // comando.param2 = 0;
  // comando.param3 = 0;
  // comando.param4 = 0;
  // comando.param5 = 0;
  // comando.param6 = 0;
  // comando.param7 = 0;
  // }

  // mavlink_msg_command_long_encode(255, 151, &messaggio, &comando);
  // unsigned len = mavlink_msg_to_send_buffer((uint8_t*)buf, &messaggio);
  // Serial1.write(buf, len);
}