#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "LinkedBlockingQueue.h"
#include "Class.h"
#include "Object.h"

//新建队列
LinkedBlockingQueue * newLinkedBlockingQueue(){
    LinkedBlockingQueue *queue = (LinkedBlockingQueue *) malloc(sizeof (LinkedBlockingQueue));
    queue->element = NULL;
    queue->head = 0;
    queue->tail = 0;
    queue->length = 0;

    return queue;
}

void LinkedBlockingQueue_clear(LinkedBlockingQueue* queue){
    queue->element = NULL;
    queue->head = 0;
    queue->tail = 0;
    queue->length = 0;
}


//队列是否为空
bool LinkedBlockingQueue_isEmpty(LinkedBlockingQueue * queue){
    return queue->element == NULL;
}


//入队
void LinkedBlockingQueue_pushBack(LinkedBlockingQueue * queue, void *object){
    if (queue == NULL)
        return;

    LinkedBlockingQueueElement *element = (LinkedBlockingQueueElement *) malloc( sizeof (LinkedBlockingQueueElement));
    element->object = object;
    element->next = NULL;
    element->id = ((Object_TypeDef *)object)->_class->id;
//    printf("\r\nadd id = 0x%08x%08x\r\n", element->id >> 32 & 0xffffffff , element->id & 0xffffffff);


//    printf("---------------\r\n");
//    printf("%08x \r\n", object);
//    printf("%08x \r\n", ((Object_TypeDef *)object));
//    printf("%08x \r\n", ((Object_TypeDef *)object)->_class);
//    printf("%08x \r\n", ((Object_TypeDef *)object)->_class->Head);
//
//
//    printf("---------------\r\n");
//
//    printf("%08x \r\n", object);
//    printf("%08x \r\n", ((Object_TypeDef *)object)->_class);
//
//    printf("%08x \r\n", ((Object_TypeDef *)object)->_class->id);
//
//    printf("%08x \r\n", ((Object_TypeDef *)object)->_class->size);
//
//    printf("%08x \r\n", ((Object_TypeDef *)object)->_class->Head);

    queue->length++;

    if (queue->element == NULL){
        //队列为空
        queue->element = element;
        queue->head = queue->element;
        queue->tail = queue->element;
    }else{
        //队列不为空
        queue->tail->next = element;
        queue->tail = queue->tail->next;
    }
}




void *LinkedBlockingQueue_popFront(LinkedBlockingQueue * queue){
    if (queue == NULL)
        return NULL;

    if (LinkedBlockingQueue_isEmpty(queue)){
        return NULL;
    }

    void *object = queue->head->object;

    LinkedBlockingQueueElement *element = queue->head;
    queue->element = queue->element->next;

    if (queue->head == queue->tail){
        queue->head = NULL;
        queue->tail = NULL;
        queue->element = NULL;
    }else{
        queue->head = queue->head->next;
    }

    queue->length--;

    free(element);

    return object;
}





int LinkedBlockingQueue_length(LinkedBlockingQueue * queue){
    return queue->length;
}


void deleteLinkedBlockingQueue(LinkedBlockingQueue * queue){
    while (LinkedBlockingQueue_popFront(queue) != NULL);
    free(queue);
}


void LinkedBlockingQueue_forEach(LinkedBlockingQueue * queue, void (*action)(void *object)){
    if (action == NULL || queue == NULL)
        return;
    LinkedBlockingQueueElement *pElement = queue->element;

    while (pElement != NULL){

        action(pElement->object);

        pElement = pElement->next;
    }
}


bool LinkedBlockingQueue_removeById(LinkedBlockingQueue * queue, int64_t id, void (*destructor)(void *object)){
    if (queue == NULL)
        return false;
    LinkedBlockingQueueElement *pPrev = NULL;
    LinkedBlockingQueueElement *pElement = queue->element;

    while (pElement != NULL){

        if (pElement->id == id){
            if (pElement->object != NULL){
//                printf("\r\nobject found !\r\n");
                //删除
                if (pPrev != NULL) {
                    pPrev->next = queue->element->next;
                    if (pPrev->next == NULL){
                        queue->tail = NULL;
                        queue->head = NULL;
                    }
                    queue->length--;
                }else{
                    queue->element = pElement->next;
                    if (queue->element == NULL){
                        queue->tail = NULL;
                        queue->head = NULL;
                    }
                    queue->length--;
                }


                return true;
            }
        }
        pPrev = pElement;
        pElement = pElement->next;

    }

    return false;
}