//
// Created by lsxs on 2020/4/30.
//

#ifndef TASK_TASK_H
#define TASK_TASK_H

#include "TaskQueue.h"
#include "Class.h"


typedef struct {
    Class_TypeDef *_class;
    void (*run)(void);
}TaskObject_TypeDef ;

#define TaskObject TaskObject_TypeDef

//常用任务
typedef enum{
    TaskTimeCycle_60s = 0,
    TaskTimeCycle_20s,
    TaskTimeCycle_10s,
    TaskTimeCycle_5s,
    TaskTimeCycle_2s,
    TaskFreq_1_Hz,
    TaskFreq_2_Hz,
    TaskFreq_5_Hz,
    TaskFreq_10_Hz,
    TaskFreq_20_Hz,
    TaskFreq_50_Hz,
    TaskFreq_100_Hz,
    TaskFreq_200_Hz,
    TaskFreq_500_Hz,
    TaskFreq_1000_Hz,
    TaskFreq_loop,
    TaskFreq_MaxSize,
}TaskFreq_TypeDef;




typedef struct{
    uint64_t start;//起始时间戳
    uint64_t stop;//中止时间戳
    uint64_t delay;//延迟时间
}TaskTime_TypeDef;

//任意定时任务
// 可以进行任意时常的定时任务，尽量少使用，
// 过多的任意定时 在当前版本中会造成CPU占用过高
// 设置多个队列
//      1.   100 ms 内触发的任务，不断轮询
//      2.   1s     内触发的任务，100ms  轮询
//      3.   10s    内触发的任务， 1s 轮询
typedef struct{

}TaskCustom_TypeDef;


typedef struct {
    TaskQueue queue[TaskFreq_MaxSize];//任务队列矩阵

    bool flags[TaskFreq_MaxSize];

    int32_t counter;

    int64_t (*create)(TaskFreq_TypeDef Freq, void (*run)(void));
    void (*remove)(int64_t taskId);

    void (*update)();

    void (*poll)();
}Task_TypeDef;



#define Task Task_TypeDef

extern Task_TypeDef *newTask();
extern void taskPolling(Task_TypeDef *task);




extern int64_t taskCreateSystem(TaskFreq_TypeDef Freq, void (*run)(void));
extern void taskRemoveSystem(int64_t taskId);
extern void taskUpdateSystem();
extern void taskPollingSystem();




#endif //TASK_TASK_H
