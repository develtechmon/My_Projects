## Ultrasonic Obstacle Control
### Final degree project Electronic and Automatic Engineering

The following code has been made for an Arduino board. It uses the "NewPing" library to measure the distance of 5 HC-SR04 ultrasonic sensors. 4 sensors to measure lateral distances and one to measure height. If the lower sensor measures more than 1.5 meters, the control begins to act. If any of the lateral sensors measures a distance less than 1.5 meters, it sends an RCOverride MAVLINK command, which overwrites the inputs received by the APM from the flight controller.

