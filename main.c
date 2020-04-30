#include <stdio.h>

#include "System.h"

#include <unistd.h>

#include "Object.h"

#include "Time.h"
#include "LinkedBlockingQueue.h"


#include "pthread.h"
int64_t taskid;


void run(){
    printf("run()\r\n");
    printf(" - %d \r\n", System->task->counter);

    if (System->task->counter == 30000){
        System->task->remove(taskid);
    }
}

void timer(){
    printf("timer !!!!!!!!!\r\n");

    while (true){
        usleep(1000);
        System->task->update();

    }
}
int main() {
    printf("Hello, World!\n");



    systemInit();

    pthread_t thread1;
    pthread_create(&thread1, NULL, timer, NULL);



    printf("%x ",System->snowFlake->next());


    sleep(1);

    printf("%x ",System->snowFlake->next());



//    Object *obj = newObject();
//
//    printf("obj class id = %x , ",obj->_class->id);









    LBQueue *lbq = newLBQueue();


    char * str = LBQueue_popFront(lbq);
    printf("%s \r\n", str);

    deleteBQueue(lbq);



    printf("task init....\r\n");
    timeStart();

    int64_t id = System->task->create(TaskFreq_1_Hz, run);
//    printf("\r\ntask create ok id = 0x%08x%08x\r\n", id>>32 & 0xffffffff, id & 0xffffffff);
//    System->task->remove(id);
    taskid = id;
    timeStop();
    printTime();




    while (true){

        System->task->poll();

//        int64_t id = System->snowFlake->next();
//
//        printf("0x%08x%08x  \t %lld\r\n", id >> 32 & 0xffffffff, id & 0xffffffff,id);
//
//
//        sleep(1);
    }



    return 0;
}
