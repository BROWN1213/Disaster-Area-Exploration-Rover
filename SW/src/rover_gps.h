/**
* @file rover_gps.h
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/

#ifndef RoverGPS_h
#define RoverGPS_h

#include "rover_gps-nmea.h"

#include <SoftwareSerial.h>

//     : public RoverTransportSerial<T>,RoverGpsNmea 

template <class T>
class RoverGPS
    : public RoverGpsNmea     
{
 public:
     RoverGPS(T& stream)
         : stream(stream),RoverGpsNmea(this->state)
     {}

     void begin(uint32_t baud) {
         stream.begin(baud);
     }
     void begin() {
         stream.begin(9600);
     }
     char readRaw()
     {
         return stream.read();
     }
     bool read(){

         int16_t numc;
         bool parsed = false;
         char c;
         //this->stream.RxModePortSet(RxMode_GPS_PORT);
         numc = stream.available();
           while (numc--) {
               c=stream.read(); //read 1 Byte
               if (decode(c)) {
                   parsed = true;
               }
           }
         return parsed;

     }
     void rx_empty(void)
     {
         char a;
         while(stream.available() > 0) {
             stream.read();
         }
     }
     //int connected() { return conn && stream; }
     int available() { return stream.available(); }
     // ground speed in m/s
     float ground_speed_ms() const {
         return state.ground_speed;
     }
     float ground_speed_km() const {
         return (state.ground_speed*3600.)/1000.;
     }
     // ground course in degrees
     float ground_course() const {
         return state.ground_course;
     }
     // number of locked satellites
     uint8_t num_sats() const {
         return state.num_sats;
     }
     // the time we last processed a message in milliseconds. This is
     // used to indicate that we have new GPS data to process
     uint32_t last_message_time_ms() const {
         return timing.last_message_time_ms;
     }
     // system time delta between the last two reported positions
     uint16_t last_message_delta_time_ms() const {
         return timing.delta_time_ms;
     }
     /// Query GPS status
     GPS_Status status() const {
         return state.status;
     }

     // location of last fix
     const Location &location() const {
         return state.location;
     }
     uint32_t time() const {
         return state.time;
     }
     uint32_t date() const {
         return state.date;
     }
   private:

     T& stream;
     GPS_State state;
     // Note allowance for an additional instance to contain blended data
     GPS_timing timing;


 };






 #endif