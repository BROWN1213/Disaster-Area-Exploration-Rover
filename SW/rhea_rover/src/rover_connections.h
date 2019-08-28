/**
* @file 
* @author SeungMin Shin, Haneulbit Kim, Chan Lee
* @license This project is released under the MIT License (MIT)
* @copyright Copyright (c) 2019 Asgardia
* @date Mar 2019
* @brief ...
*/



#ifndef RoverConnections_H
#define RoverConnections_H

struct joyCommand {
    int velocity;
    int radius;
};


class RoverConnections {

    public:
        RoverConnections();
       void getDriveVals();



    private:
        struct joyCommand command_joy;

};

 

#endif