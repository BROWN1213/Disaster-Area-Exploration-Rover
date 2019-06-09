/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/


#ifndef RoverLx16A_H
#define RoverLx16A_H

#define GET_LOW_BYTE(A) (uint8_t)((A))
//Macro function  get lower 8 bits of A
#define GET_HIGH_BYTE(A) (uint8_t)((A) >> 8)
//Macro function  get higher 8 bits of A
#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))
//Macro Function  put A as higher 8 bits   B as lower 8 bits   which amalgamated into 16 bits integer

#define LOBOT_SERVO_FRAME_HEADER         0x55
#define LOBOT_SERVO_MOVE_TIME_WRITE      1
#define LOBOT_SERVO_MOVE_TIME_READ       2
#define LOBOT_SERVO_MOVE_TIME_WAIT_WRITE 7
#define LOBOT_SERVO_MOVE_TIME_WAIT_READ  8
#define LOBOT_SERVO_MOVE_START           11
#define LOBOT_SERVO_MOVE_STOP            12
#define LOBOT_SERVO_ID_WRITE             13
#define LOBOT_SERVO_ID_READ              14
#define LOBOT_SERVO_ANGLE_OFFSET_ADJUST  17
#define LOBOT_SERVO_ANGLE_OFFSET_WRITE   18
#define LOBOT_SERVO_ANGLE_OFFSET_READ    19
#define LOBOT_SERVO_ANGLE_LIMIT_WRITE    20
#define LOBOT_SERVO_ANGLE_LIMIT_READ     21
#define LOBOT_SERVO_VIN_LIMIT_WRITE      22
#define LOBOT_SERVO_VIN_LIMIT_READ       23
#define LOBOT_SERVO_TEMP_MAX_LIMIT_WRITE 24
#define LOBOT_SERVO_TEMP_MAX_LIMIT_READ  25
#define LOBOT_SERVO_TEMP_READ            26
#define LOBOT_SERVO_VIN_READ             27
#define LOBOT_SERVO_POS_READ             28
#define LOBOT_SERVO_OR_MOTOR_MODE_WRITE  29
#define LOBOT_SERVO_OR_MOTOR_MODE_READ   30
#define LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE 31
#define LOBOT_SERVO_LOAD_OR_UNLOAD_READ  32
#define LOBOT_SERVO_LED_CTRL_WRITE       33
#define LOBOT_SERVO_LED_CTRL_READ        34
#define LOBOT_SERVO_LED_ERROR_WRITE      35
#define LOBOT_SERVO_LED_ERROR_READ       36

//#define LOBOT_DEBUG 1  /*Debug ：print debug value*/

class RoverLx16A{
    public:
        RoverLx16A()
            : SerialX(NULL),conn(0)
        {}

        void beginLx16(Stream& s) {
            SerialX= &s;
        }
        bool connect() {
            SerialX->flush();
            return conn = true;
        }        
        void disconnect() { conn = false; }    
        bool connected() { return conn; }
        int available() { return SerialX->available(); }           
        byte LobotCheckSum(byte buf[]);
        void Move(uint8_t id, int16_t position, uint16_t time);
        void StopMove(uint8_t id);
        void SetID(uint8_t oldID, uint8_t newID);
        int GetID(uint8_t ID);
        void OffsetAdjust(uint8_t id, int16_t offsetpos);
        void Offsetwrite(uint8_t id, int16_t offsetpos);
        void OffsetRead(uint8_t id);
        void SetMode(uint8_t id, uint8_t Mode, int16_t Speed);
        void Load(uint8_t id);
        void Unload(uint8_t id);
        int LobotSerialServoReceiveHandle(byte *ret);
        int ReadPosition(uint8_t id);
        int ReadVin(uint8_t id);
    private:
        Stream* SerialX;
        bool    conn;

};




#endif