#include <stdint.h>

#include <stdbool.h>
#include "Task.h"
#include <stdlib.h>
#include "System.h"


const int timeTable[TaskFreq_MaxSize] = {
60000,
20000,
10000,
5000,
2000,
1000,
500,
200,
100,
50,
20,
10,
5,
2,
1,
};


void taskRun(void *object){
    if (object == NULL)
        return;
    ((TaskObject*)object)->run();
}



Task_TypeDef *newTask(){
    Task_TypeDef *pTask = (Task_TypeDef *)malloc(sizeof(Task_TypeDef));
    for (int i=TaskTimeCycle_60s; i<TaskFreq_MaxSize;++i){

        LBQueue_clear(&pTask->queue[i].queue);
    }
    pTask->counter = 0;
    return pTask;
}


void taskPolling(Task_TypeDef *task){
    for (int i=TaskTimeCycle_60s; i<= TaskFreq_1000_Hz; ++i){
        if (task->flags[i] == true){
            task->flags[i] = false;
            //循环队列 执行
            LBQueue_forEach(&task->queue[i].queue,taskRun);
        }
    }
}



TaskObject *newTaskObject(){
    TaskObject *obj = (TaskObject *) malloc(sizeof(TaskObject_TypeDef));
    obj->_class = newClass(sizeof(TaskObject_TypeDef));

    return obj;
}


void deleteTaskObject(void *object){
    TaskObject * obj = (TaskObject *) object;
    free(obj->_class);
    free(obj);
    obj = NULL;
}


int64_t taskCreate(Task_TypeDef *task, TaskFreq_TypeDef Freq, void (*run)(void)){
    if (Freq < TaskTimeCycle_60s || Freq > TaskFreq_loop){
        return -1;
    }
    TaskObject *object = newTaskObject();
    object->run = run;
//    printf("\r\n id = 0x%08x%08x \r\n", object->_class->id >> 32 & 0xffffffff, object->_class->id & 0xffffffff);
//



//    printf("---------------------\r\n");
//
//    printf("%08x \r\n", task);
//    printf("%08x \r\n", object);
//    printf("%08x \r\n", object->_class);
//
//    printf("%08x \r\n", object->_class->id);
//
//    printf("%08x \r\n", object->_class->size);
//
//    printf("%08x \r\n", object->_class->Head);
//
//    printf("%08x \r\n", object->run);









    LBQueue_pushBack(&task->queue[Freq].queue, object);
    return object->_class->id;
}


void taskRemove(Task_TypeDef *task, int64_t taskId){
    for(int i=TaskTimeCycle_60s; i<TaskFreq_MaxSize; ++i){
        if (LBQueue_removeById(&task->queue[i].queue, taskId, /*对象析构函数*/ deleteTaskObject) == true){
            break;
        }
    }
}








///
int64_t taskCreateSystem(TaskFreq_TypeDef Freq, void (*run)(void)){


//    printf("freq = %d \r\n", Freq);

    return taskCreate(System->task, Freq, run);
}

void taskRemoveSystem(int64_t taskId){
    taskRemove(System->task, taskId);
}




void taskUpdate(Task_TypeDef *task){

//    max = 60*1000;
    task->counter++;
    task->counter %= 60*1000;//最大60秒

    task->flags[TaskFreq_1000_Hz] = true;

    for (int i = TaskTimeCycle_60s; i< TaskFreq_1000_Hz; ++i){
        if (task->counter % timeTable[i] == 0){
            task->flags[i] = true;
        }
    }



}

void taskUpdateSystem(){
    taskUpdate(System->task);
}


void taskPollingSystem()
{
    taskPolling(System->task);
}