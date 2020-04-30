//
// Created by lsxs on 2020/4/30.
//

#ifndef TASK_CLASS_H
#define TASK_CLASS_H

#include <stdint.h>

typedef struct{
    char Head[0];
    int64_t id;//目标id
    int size;//class大小
}Class_TypeDef;

extern void classInit(void *pObject, int size);

extern Class_TypeDef * newClass(int size);


#endif //TASK_CLASS_H
