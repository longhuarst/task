//
// Created by lsxs on 2020/4/30.
//

#ifndef TASK_HEAP_H
#define TASK_HEAP_H


#include <stdint.h>
#include <stdbool.h>


typedef struct {
    int64_t value; //值
    void *object; //目标
}HeapElement_TypeDef;

typedef struct{
    HeapElement_TypeDef *element; //
    int size;
    int length;
    bool min; //小根堆
}Heap_TypeDef;



#endif //TASK_HEAP_H
