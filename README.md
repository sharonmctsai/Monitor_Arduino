# Monitor_Arduino

Project Name: Baby Monitor System

Student Name: Huiyun,Tsai(Sharon)   Student ID: 20104330
Video URL		: https://youtu.be/jAsg0yVedAs

Project description:

Create a baby monitoring system using Arduino Explorer IoT Kit, a temperature and humidity sensor, and a PIR sensor. The system will send notification to Line message and email via ThingSpeak when temperature and humidity is high or when motion is detected in the baby's room.

Tools, Technologies and Equipment:

Hardware Components:
Arduino MKR WiFi1010
Arduino MKR IoT Carrier 
Temperature and humidity sensor
PIR sensor 

Software Components:
Arduino IDE
Arduino Libraries
IoT platform ThingSpeak
Line messenger

Project Implementation:
Connect the IoT shield, temperature and humidity sensor, and PIR sensor to the Arduino board.Write a program using Java in the Arduino IDE to read data from the sensors.

Configure the IoT platform. Use the platform's API to send data (temperature, humidity, motion status) to the cloud.

Create a channel called “Baby monitor “in ThingSpeak with widgets to display temperature/humidity and motion status.

Configure using React and ThingHTTP to send notifications to mobile device when temperature is warm, humidity is high and motion is detected.

Set up thresholds for temperature and humidity to trigger alerts. If the temperature and humidity is high, send a notification to the mobile app.
Configure the PIR sensor to detect motion in the baby's bed. If motion is detected, send a notification to the mobile app.

They were all set to Send email notification t of  by using MATLAB Analysis every 12 hours

Project Repository:
https://github.com/sharonmctsai/Monitor_Arduino

![Screenshot 2023-12-29 at 18 08 03](https://github.com/sharonmctsai/Arduino-Project/assets/108837318/8bb4a17c-0c18-4286-bda0-19897b02b07a)
