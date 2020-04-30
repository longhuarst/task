//
// Created by lsxs on 2020/4/30.
//

#ifndef TASK_LINKEDBLOCKINGQUEUE_H
#define TASK_LINKEDBLOCKINGQUEUE_H

#include <stdbool.h>
#include <stdio.h>

#include <stdint.h>
typedef struct LinkedBlockingQueueElementStruct{
    struct LinkedBlockingQueueElementStruct * next;
    void * object; //目次对象
    int64_t id;//存放对象id副本
}LinkedBlockingQueueElement_TypeDef;

#define LinkedBlockingQueueElement LinkedBlockingQueueElement_TypeDef



typedef struct {
    LinkedBlockingQueueElement *element;
    LinkedBlockingQueueElement *head;
    LinkedBlockingQueueElement *tail;
    int length;
}LinkedBlockingQueue_TypeDef;





#define LinkedBlockingQueue LinkedBlockingQueue_TypeDef



LinkedBlockingQueue * newLinkedBlockingQueue();
bool LinkedBlockingQueue_isEmpty(LinkedBlockingQueue * queue);
void LinkedBlockingQueue_pushBack(LinkedBlockingQueue * queue, void *object);
void *LinkedBlockingQueue_popFront(LinkedBlockingQueue * queue);
int LinkedBlockingQueue_length(LinkedBlockingQueue * queue);
void deleteLinkedBlockingQueue(LinkedBlockingQueue * queue);
void LinkedBlockingQueue_forEach(LinkedBlockingQueue * queue, void (*action)(void *object));
bool LinkedBlockingQueue_removeById(LinkedBlockingQueue * queue, int64_t id, void (*destructor)(void *object));
void LinkedBlockingQueue_clear(LinkedBlockingQueue* queue);


typedef   LinkedBlockingQueue LBQueue;

#define newLBQueue newLinkedBlockingQueue
#define LBQueue_isEmpty LinkedBlockingQueue_isEmpty
#define LBQueue_pushBack LinkedBlockingQueue_pushBack
#define LBQueue_popFront LinkedBlockingQueue_popFront
#define LBQueue_length LinkedBlockingQueue_length
#define deleteBQueue deleteLinkedBlockingQueue
#define LBQueue_forEach LinkedBlockingQueue_forEach
#define LBQueue_removeById LinkedBlockingQueue_removeById
#define LBQueue_clear LinkedBlockingQueue_clear




#endif //TASK_LINKEDBLOCKINGQUEUE_H
