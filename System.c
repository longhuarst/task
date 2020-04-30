#include "System.h"
#include <stdlib.h>





System_TypeDef * System;





void systemInit(){
    System = (System_TypeDef *)malloc(sizeof(System_TypeDef));


    //初始化 id生成器
    System->snowFlake = (SnowFlake_TypeDef *) malloc(sizeof (SnowFlake_TypeDef));
    snowFlakeInit(System->snowFlake);

    System->task = newTask();
    System->task->create = taskCreateSystem;
    System->task->remove = taskRemoveSystem;
    System->task->update = taskUpdateSystem;
    System->task->poll = taskPollingSystem;

}