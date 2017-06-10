//
//  SqQueue_1.cpp
//  DataStruct
//
//  Created by haozhu on 2017/6/10.
//  Copyright © 2017年 neu. All rights reserved.
//
//顺序队列，非循环队列

#include "SqQueue.hpp"

Status InitQueue(SqQueue &Q){
    QElemType *base = (QElemType *)malloc(sizeof(QElemType)*MAXQSIZE);
    if (!base) {
        exit(OVERFLOWD);
    }
    Q.base = base;
    Q.front = Q.rear = 0;
    return OK;
}

Status DestoryQueue(SqQueue &Q){
    if (Q.base) {
        free(Q.base);
    }
    Q.base = NULL;
    Q.front = Q.rear = 0;
    return OK;
}

Status ClearQueue(SqQueue &Q){
    Q.front = Q.rear = 0;
    return OK;
}

Status QueueEmpty(SqQueue Q){
    return Q.front == Q.rear;
}

int QueueLength(SqQueue Q){
    return Q.rear-Q.front;
}

Status GetHead(SqQueue Q, QElemType &e){
    if (Q.front==Q.rear) {
        return ERROR;
    }
    e = *(Q.base+Q.front);
    return OK;
}

Status EnQueue(SqQueue &Q, QElemType e){
    if (Q.rear>=MAXQSIZE) { //队列已满，需要重新分配内存空间
        Q.base = (QElemType *)realloc(Q.base, sizeof(QElemType)*(Q.rear+1));
        if (!Q.base) {
            exit(OVERFLOWD);
        }
    }
    e = Q.base[Q.rear];
    Q.rear ++;
    return OK;
}

Status DeQueue(SqQueue &Q, QElemType &e){
    if (Q.rear == Q.front) {
        return ERROR;
    }
    e = *(Q.base+Q.front);
    Q.front++;
    return OK;
}

Status QueueTraverse(SqQueue Q, void (*visit)(QElemType)){
    int i = Q.front;
    while (i<Q.rear) {
        visit(*(Q.base+i));
        i++;
    }
    printf("\n");
    return OK;
}
