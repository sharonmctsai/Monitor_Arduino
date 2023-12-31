#include <RTCZero.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST77xx.h>

#include <WiFiNINA.h>
#include <Arduino_MKRIoTCarrier.h>
#include <ThingSpeak.h>
#include "config.h"

char ssid[] = WIFI_NAME;
char pass[] = WIFI_PASSWORD;
int status = WL_IDLE_STATUS;
int pirPin = A5;  // Pin connected to the PIR sensor
int pirValue;     // Variable to store PIR sensor value
WiFiClient wifiClient;
WiFiClient client;

MKRIoTCarrier carrier;
RTCZero rtc;

void setupWiFi() {
  // Check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // Don't continue
    while (true)
      ;
  }

  // Attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // Wait 10 seconds for connection:
    delay(5000);
  }

  // You're connected now, so print out the data:
  Serial.println("You're connected to the network");
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // Wait for serial port to connect. Needed for native USB port only
  }
  setupWiFi();
  carrier.begin();
  ThingSpeak.begin(wifiClient);
  pinMode(pirPin, INPUT);


  carrier.display.init(240, 240, SPI_MODE0);  // Adjust the values accordingly
  carrier.display.fillScreen(ST77XX_BLACK);

  rtc.begin();

 
}


void loop() {
  float temperature = carrier.Env.readTemperature();
  float humidity = carrier.Env.readHumidity();
   displayTemperatureHumidity(temperature, humidity, pirValue == HIGH);
  delay(1000);

  // Check room temperature
  if (temperature > tempTHRESHOLD) {
    Serial.print("The room is WARM: ");
    turnOnRedLED();  // Turn on the red LED
  } else {
    Serial.print("The room is COLD: ");
    turnOnBlueLED();  // Turn on the blue LED
  }
  Serial.print("Temp: ");
  Serial.println(temperature);

  // Check room humidity
  if (humidity > humiTHRESHOLD)
    Serial.print("The room is WET: ");
  else
    Serial.print("The room is DRY: ");

  Serial.print("Humidity: ");
  Serial.println(humidity);

  pirValue = digitalRead(pirPin);

  // Print the PIR sensor value to the serial monitor
  Serial.print("Movement: ");

  // Check if motion is detected
  if (pirValue == HIGH) {
    Serial.println("Movement Detected");
    blinkWhiteLED();  // Blink white LED if motion is detected
  } else {
    Serial.println("No Movement");
  }

  ThingSpeak.setField(1, temperature);
  ThingSpeak.setField(2, humidity);
  ThingSpeak.setField(3, pirValue);

  int response = ThingSpeak.writeFields(SECRET_CH_ID, SECRET_WRITE_APIKEY);

  if (response == 200) {
    Serial.println("Channel update successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(response));
  }

  delay(15000);
}



void turnOnRedLED() {
  int red = 255, green = 0, blue = 0;  // RGB values of light (red)
  int ledColour = carrier.leds.Color(red, green, blue);
  carrier.leds.fill(ledColour);
  carrier.leds.show();
}

void turnOnBlueLED() {
  int red = 0, green = 0, blue = 255;  // RGB values of light (blue)
  int ledColour = carrier.leds.Color(red, green, blue);
  carrier.leds.fill(ledColour);
  carrier.leds.show();
}

void blinkWhiteLED() {
  int white = 255;  // RGB value of light (white)
  int ledColour = carrier.leds.Color(white, white, white);

  for (int i = 0; i < 5; ++i) {
    carrier.leds.fill(ledColour);
    carrier.leds.show();
    delay(500);  // On for 500ms
    carrier.leds.fill(0);
    carrier.leds.show();
    delay(500);  // Off for 500ms
  }
}


void displayTemperatureHumidity(float temperature, float humidity, bool motionDetected) {
  carrier.display.fillScreen(ST77XX_BLACK);
  carrier.display.setCursor(20, 40);
  carrier.display.setTextColor(ST77XX_WHITE);
  carrier.display.setTextSize(2);

  // Display temperature and humidity
  carrier.display.print("Temperature: ");
  carrier.display.print(temperature);
  carrier.display.println(" °C");

  carrier.display.print("Humidity: ");
  carrier.display.print(humidity);
  carrier.display.println("%");


// Display motion status
  carrier.display.setCursor(20, 100);
  carrier.display.print("Motion: ");
  carrier.display.println(motionDetected ? "Detected" : "Not Detected");


}