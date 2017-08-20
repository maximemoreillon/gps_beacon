#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define SS_RX_PIN 4
#define SS_TX_PIN 3

#define LED_PIN 12
#define BATTERY_PIN A0

#define TX_PERIOD 10000

#define BATTERY_MINIMUM 3500
#define BATTERY_MAXIMUM 4200

TinyGPSPlus GPS;
SoftwareSerial GPS_SS(SS_RX_PIN, SS_TX_PIN);

int battery_millivolt;
long last_TX_time;

void setup()
{
  Serial.begin(9600);
  GPS_SS.begin(9600);
  pinMode(LED_PIN,OUTPUT);

  last_TX_time = -TX_PERIOD;
}

void loop()
{
  while(GPS_SS.available()>0){
    GPS.encode(GPS_SS.read());
  }

  
  
  long now = millis();
  if(now-last_TX_time > TX_PERIOD)
  {
    last_TX_time = now;
    battery_monitor();
    gps_TX();
  }
  
}


