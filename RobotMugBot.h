// RBotFirmware
// Rob Dobson 2016

#pragma once

#include "application.h"
#include "Utils.h"
#include "RobotPolar.h"

class RobotMugBot : public RobotPolar
{
public:
    RobotMugBot(const char* pRobotTypeName) :
        RobotPolar(pRobotTypeName)
    {

    }
};
