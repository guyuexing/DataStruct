//
//  LinkQueue.cpp
//  DataStruct
//
//  Created by guyuexing on 2017/6/8.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "LinkQueue.hpp"

Status InitQueue(LinkQueue &Q){
    //初始化一个头结点，队头和队尾均指向头结点
    if (!(Q.rear=Q.front=(QueuePtr)malloc(sizeof(QNode)))) {
        exit(OVERFLOWD);
    }
    Q.front->next = NULL;
    return OK;
}

Status DestoryQueue(LinkQueue &Q){
    while (Q.front) {
        Q.rear = Q.front->next; //修改队尾指针指向头结点的下一个结点
        free(Q.front); //第一次是释放头结点
        Q.front = Q.rear;
    }
    return OK;
}

Status ClearQueue(LinkQueue &Q){
    QueuePtr p,q;
    p = Q.front->next; //p指向头结点的下一个结点
    while (p) { //释放除头结点之外的其他结点
        q = p;
        p = p->next;
        free(q);
    }
    Q.front->next = NULL;
    Q.rear = Q.front;
    return OK;
}

Status QueueEmpty(LinkQueue Q){
    return Q.front == Q.rear;
}

int QueueLength(LinkQueue Q){
    int length = 0;
    QueuePtr p = Q.front->next;
    while (p) {
        p=p->next;
        length++;
    }
    return length;
}

//若队列不空，用e返回队列的队头元素
Status GerHead(LinkQueue Q, QElemType &e){
    if (Q.front==Q.rear) { //如果队列为空
        return ERROR;
    }
    e = Q.front->next->data;
    return OK;
}

//插入队尾
Status EnQueue(LinkQueue &Q,QElemType e){
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if (!p) {
        exit(OVERFLOW); //分配存储失败
    }
    p->data = e;
    Q.rear->next = p;
    p->next = NULL;
    Q.rear = p;
    return OK;
}

//删除队头
Status DeQueue(LinkQueue &Q, QElemType &e){
    if (Q.front == Q.rear) {
        return ERROR;
    }
    QueuePtr p = Q.front->next;
    Q.front->next = p->next;
    e = p->data;
    if (Q.rear == p) {  //如果要删除的p是队列的最后一个结点，修改队尾指针
        Q.rear = Q.front;
    }
    free(p);
    return OK;
}

//从队头到队尾依次对Q的每个数据元素调用visit函数
Status QueueTraverse(LinkQueue &Q, void *visit(QElemType)){
    QueuePtr p = Q.front->next;
    while (p) {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}
