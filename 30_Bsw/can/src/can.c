#include "can.h"

#define CAN_INSTANCE 1

const canConfigStruct canConfig[1] = {
    {
        .baudrate = 1,
    }
};

STD_RETYPE CAN_Init() {
    return OK;
}

