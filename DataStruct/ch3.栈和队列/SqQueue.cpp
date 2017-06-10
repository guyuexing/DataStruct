//
//  SqQueue.cpp
//  DataStruct
//
//  Created by haozhu on 2017/6/10.
//  Copyright © 2017年 neu. All rights reserved.
//
//循环队列的操作方法

#include "SqQueue.hpp"

Status InitQueue(SqQueue &Q){
    if (!(Q.base = (QElemType *)malloc(sizeof(QElemType)*MAXQSIZE))) {
        exit(OVERFLOW); //分配存储空间失败
    }
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
    return (Q.rear-Q.front+MAXQSIZE)%MAXQSIZE;
    //假如rear>front 即还没有重复使用队列空间
    //假如rear<front 即已经重复使用队列空间了，此时rear-front为负数了，加上MAXQSIZE即为元素个数
    //只有在队列为空时 rear=front，当队列满的时候，队列头指针在队列尾指针的下一个位置
}

Status GetHead(SqQueue Q, QElemType &e){
    if (Q.front == Q.rear) {
        return ERROR;
    }
    e = *(Q.base+Q.front); //考虑到有可能在对头删除了元素，Q.front位置会移动，但是Q.base指针指向位置不会移动
    return OK;
}

Status EnQueue(SqQueue &Q,QElemType e){
    //判断队列是否已经满了
    if ((Q.rear+1)%MAXQSIZE == Q.front) {
        return ERROR;
    }
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear+1)%MAXQSIZE;
    return OK;
}

Status DeQueue(SqQueue &Q, QElemType &e){
    if (Q.rear == Q.front) {
        return ERROR;
    }
    e = Q.base[Q.front];
    Q.front = (Q.front+1)%MAXQSIZE;
    return OK;
}

Status QueueTraverse(SqQueue Q, void (*visit)(QElemType)){
    int i = Q.front;
    while (i!=Q.rear) {
        visit(Q.base[i]);
        i = (i+1)%MAXQSIZE;
    }
    printf("\n");
    return OK;
}

