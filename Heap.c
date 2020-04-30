//
// Created by lsxs on 2020/4/30.
//
#include "Heap.h"
#include <stdbool.h>
#include <stdlib.h>

Heap_TypeDef *newHeap(int size){
    Heap_TypeDef * heap = (Heap_TypeDef *) malloc(sizeof(Heap_TypeDef));

    heap->size = size;
    heap->length = 0;
    heap->min = true;
    heap->element = malloc(sizeof(HeapElement_TypeDef) * size);

    return heap;
}


void deleteHeap(Heap_TypeDef *heap, void (*destructure)(void *object)){
    for (int i=0;i<heap->length; ++i){
        destructure(heap->element[i].object);//调用传入的析构函数
    }
    free(heap->element);
    free(heap);
}



bool heapInsert(Heap_TypeDef *heap, void *object){

}


void *heapPeek(Heap_TypeDef *heap){

}


void *heapRemoveFirst(Heap_TypeDef *heap){

}

