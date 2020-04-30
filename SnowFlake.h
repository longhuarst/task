//
// Created by lsxs on 2020/4/30.
//

#ifndef TASK_SNOWFLAKE_H
#define TASK_SNOWFLAKE_H

#include <stdbool.h>
#include <stdint.h>



typedef struct{
    int64_t (*next)();
}SnowFlake_TypeDef;



extern bool snowFlakeInit(SnowFlake_TypeDef *object);

extern bool SnowflakeIdWorker(int64_t workerId, int64_t datacenterId);






#endif //TASK_SNOWFLAKE_H
