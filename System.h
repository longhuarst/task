#ifndef __system_h
#define __system_h


#include "Logger.h"
#include "SnowFlake.h"

#include "TaskQueue.h"
#include "Task.h"


typedef struct {

    Logger_TypeDef *logger;


    SnowFlake_TypeDef *snowFlake;

    Task_TypeDef *task;



}System_TypeDef;


extern System_TypeDef *System;



extern void systemInit();










#endif //__system_h


