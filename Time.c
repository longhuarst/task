//
// Created by lsxs on 2020/4/30.
//
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <stdio.h>

struct timeval timeval_start;
struct timeval timeval_stop;

void timeStart(){
    gettimeofday(&timeval_start, NULL);
}
void timeStop(){
    gettimeofday(&timeval_stop, NULL);
}

void printTime(){
    printf("%lld \r\n", (int64_t)timeval_start.tv_usec +  (int64_t)timeval_start.tv_sec*1000000);
    printf("%lld \r\n",(int64_t)timeval_stop.tv_usec +  (int64_t)timeval_stop.tv_sec*1000000);
    int64_t x = (int64_t)timeval_start.tv_usec +  (int64_t)timeval_start.tv_sec*1000000 - (
                                                                                      (int64_t)timeval_stop.tv_usec +  (int64_t)timeval_stop.tv_sec*1000000
            );


    printf("current time = %lld \r\n",x);//System.currentTimeMillis();
}




//----------+++~~~   3us
//1588233707565814
//1588233707567817


//-------------------------+++~~~
//current time = 1588233881955619
//current time = 1588233881956619