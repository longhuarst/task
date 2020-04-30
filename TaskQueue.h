//
// Created by lsxs on 2020/4/30.
//

#ifndef TASK_TASKQUEUE_H
#define TASK_TASKQUEUE_H

#include "LinkedBlockingQueue.h"

//任务队列为 非频繁分配 释放， 暂时采用 LBQueue

typedef struct {

    LBQueue queue;




}TaskQueue_TypeDef;

#define TaskQueue TaskQueue_TypeDef




#endif //TASK_TASKQUEUE_H
