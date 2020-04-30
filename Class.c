//
// Created by lsxs on 2020/4/30.
//




#include "Class.h"
#include "System.h"
#include <stdlib.h>
#include "SnowFlake.h"




void classInit(void *pObject, int size)
{
    ((Class_TypeDef *)pObject) -> size = size;
    ((Class_TypeDef *)pObject) -> id = System -> snowFlake -> next();
}




Class_TypeDef * newClass(int size)
{
    Class_TypeDef *class = (Class_TypeDef *) malloc(sizeof(Class_TypeDef));
    class->id = System->snowFlake->next();
    class->size = size;
}