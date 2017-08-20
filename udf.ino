void battery_monitor()
{
  battery_millivolt = map(analogRead(BATTERY_PIN),0,713,0,3785);
  
  // Blink LED if battery low
  if(battery_millivolt<BATTERY_MINIMUM && (millis()/500)%2){
    digitalWrite(LED_PIN,LOW);
  }
  else{
    digitalWrite(LED_PIN,HIGH);
  }
}

void gps_TX()
{
  byte payload[10];
  
  byte battery_bits, satellite_bits;
  long latitude_bits, longitude_bits;
  
  // converting battery level for payload
  battery_bits = constrain(map(battery_millivolt,BATTERY_MINIMUM,BATTERY_MAXIMUM,0,100),0,100);

  // converting satellite count for payload
  if(GPS.satellites.isValid()){
    satellite_bits = constrain(GPS.satellites.value(),0x00,0xff);
  }
  else{
    satellite_bits = 0;
  }

  // converting latitude and longitude for payload
  if(GPS.location.isValid()){
    latitude_bits = GPS.location.lat()*10000;
    longitude_bits = GPS.location.lng()*10000;
  }
  else
  {
    latitude_bits = 0;
    longitude_bits = 0;
  }

  // Constructing payload
  payload[0] = battery_bits;
  payload[1] = satellite_bits; 

  payload[2] = latitude_bits>>24;
  payload[3] = latitude_bits>>16;
  payload[4] = latitude_bits>>8;
  payload[5] = latitude_bits;

  payload[6] = longitude_bits>>24;
  payload[7] = longitude_bits>>16;
  payload[8] = longitude_bits>>8;
  payload[9] = longitude_bits;

  Serial.write(payload, 10);
  

}
