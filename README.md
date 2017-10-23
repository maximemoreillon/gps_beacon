# GPS Beacon

An Arduino based GPS beacon that can uses an XBee Pro transciever to broadcast its location.

## Parts list
* Arduino pro mini 3.3V
* U-blox NEO-6M GPS
* Xbee pro with adapter board
* 14500 Li-ion battery

## Schematic
![alt text](https://moreillon.duckdns.org/projects/images/gps_beacon_v2_schema.png)

## Requirements
* TinyGPS++ library
* Software Serial

## Payload description

* byte 0: battery percent
* bate 1: Sattelite count
* byte 2-5: Latitude * 10000 (long)
* byte 6-9: Longitude * 10000 (long)

