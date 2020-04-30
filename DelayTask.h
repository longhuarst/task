//
// Created by lsxs on 2020/4/30.
//

#ifndef TASK_DELAYTASK_H
#define TASK_DELAYTASK_H


#include "LinkedBlockingQueue.h"

//延迟队列采用 优先队列会效率高  优先队列采用固定数组时， 采用二分法会加快 搜索速率，所以延迟队列具有一定的上限数目

//延迟任务

typedef enum{
    delayTask_0_1s = 0, // 小于 1s
    delayTask_1s_1n,
    delayTask_maxSize
}DelayTaskEnum;

typedef struct {
    LBQueue queue[delayTask_maxSize]; //延迟队列
}DelayTask_TypeDef;


//创建在某个时间触发的任务
void createDelayTaskAtTimestamp(int64_t timestamp){

}













void createDelayTaskAfterDays(){

}

void createDelayTaskAfterHours(){

}


void createDelayTaskAfterMintues(){

}

//创建 xx 秒后的任务
void createDelayTaskAfterSeconds(){

}

void createDelayTaskAfterMilliSeconds(){

}


void createDelayTaskAfterMicroSeconds(){

}






























#endif //TASK_DELAYTASK_H
