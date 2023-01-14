#include <DHT.h>
#include <Servo.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

Servo myservo;

int waterPin = 7;
int waterLevel = 0;
int waterThreshold = 50;
int lastWater = 0;
int waterInterval = 10080;  // 1 week in minutes

void setup() {
  dht.begin();
  myservo.attach(9);
  pinMode(waterPin, INPUT);
}

void loop() {
  // Read the humidity and temperature
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if it rained in the last week
  waterLevel = analogRead(waterPin);
  if (waterLevel > waterThreshold && lastWater + waterInterval < millis()/60000) {
    lastWater = millis()/60000;
    // Water the flowers
    myservo.write(90);
    delay(1000);
    myservo.write(0);
  }
}
