/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/

#ifndef RoverDebug_h
#define RoverDebug_h


#include <stddef.h>
#include <inttypes.h>
#include <assert.h>

typedef uint32_t millis_time_t;



#define RoverMillis() millis()


#include <Arduino.h>

#include <avr/pgmspace.h>




// Diagnostic defines

//#define ROVER_FATAL(msg)     { ROVER_LOG1(msg); CansatFatal(); }
//#define ROVER_LOG_RAM()      { ROVER_LOG2(ROVER_F("Free RAM: "), CansatFreeRam()); }
//#define ROVER_LOG_FN()       ROVER_LOG3(ROVER_F(__FUNCTION__), '@', __LINE__);
//#define ROVER_LOG_TROUBLE(t) ROVER_LOG2(ROVER_F("Trouble detected: email to cchamchi@naver.com-"), t)

#ifndef ROVER_PRINT
#undef ROVER_DEBUG
#endif

#ifdef ROVER_DEBUG_ALL
#define ROVER_DEBUG
#endif

#ifdef ROVER_PRINT

    #define ROVER_LOG(msg)  {ROVER_PRINT.print('[');ROVER_PRINT.print(millis());ROVER_PRINT.print(F("] ")); ROVER_PRINT.println(F(msg));   }

    #define ROVER_ASSERT(expr) { if(!(expr)) { ROVER_LOG("Assertion failed."); ROVER_DBG_BREAK()} }


#ifdef ROVER_DEBUG
        #define ROVER_DBG_DUMP(msg, addr, len) if (len) { ROVER_PRINT.print(F(msg)); ROVER_PRINT.write((uint8_t*)addr, len); ROVER_PRINT.println(); }
        #define ROVER_DBG_BREAK()    { for(;;); }
#endif


#endif //#ifdef ROVER_PRINT

#ifndef ROVER_LOG
    #define ROVER_LOG(...)


#endif

#ifndef ROVER_DBG_BREAK
    #define ROVER_DBG_BREAK()
    #define ROVER_ASSERT(expr)
    #define ROVER_DBG_DUMP(msg, addr, len)
#endif

#endif