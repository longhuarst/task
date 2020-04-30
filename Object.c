//
// Created by lsxs on 2020/4/30.
//


#include "Object.h"
#include <stdlib.h>
#include "Class.h"





Object_TypeDef *newObject(){
    Object_TypeDef *obj = (Object_TypeDef *) malloc( sizeof (Object_TypeDef));
    //调用class 初始化
    classInit(obj, sizeof(Object_TypeDef));
    return obj;
}