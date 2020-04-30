//
// Created by lsxs on 2020/4/30.
//

#ifndef TASK_OBJECT_H
#define TASK_OBJECT_H

#include "Class.h"




typedef struct {
    Class_TypeDef *_class;
}Object_TypeDef;


#define Object Object_TypeDef

extern Object_TypeDef *newObject();







#endif //TASK_OBJECT_H
