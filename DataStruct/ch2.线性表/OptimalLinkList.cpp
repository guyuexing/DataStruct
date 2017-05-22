//
//  OptimalLinkList.cpp
//  DataStruct
//
//  Created by guyuexing on 2017/5/22.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "OptimalLinkList.hpp"

//分配由p指向的值为e的结点，并返回OK，若分配失败，则返回error
Status MakeNode(Link &p, ElemType e){
    p = (Link)malloc(sizeof(LNode));
    if (!p) {
        return ERROR;
    }
    p->data = e;
    return OK;
}

//释放p所指结点
void FreeNode(Link &p){
    free(p);
    p = NULL;
}

//构造一个空的线性链表L
Status InitList(LinkList &L){
    //生成头结点
    Link p = (Link)malloc(sizeof(LNode));
    if (!p) {
        return ERROR;
    }
    p->data = NULL;
    p->next = NULL;
    L.header = L.tail = p;
    L.len = 0;
    return OK;
}

//清空线性链表L，并释放原链表的结点空间
Status ClearList(LinkList &L){
    //如果不是空表
    if (L.header!=L.tail) {
        Link p,q;
        //p，q均指向链表的第一个结点
        p = q = L.header->next;
        //将链表L的第一个结点置为空
        L.header->next = NULL;
        while (p!=L.tail) {
            q = p->next;
            free(p);
            p = q;
        }
        //释放最后一个结点
        free(L.tail);
        L.header = L.tail;
        L.len = 0;
    }
    return OK;
}

//销毁线性链表L
Status DestoryList(LinkList &L){
    ClearList(L);
    FreeNode(L.header);
    L.tail = NULL;
    L.len = 0;
    return OK;
}

//已知h指向线性链表的头结点，将s所指结点插入在第一个结点之前
Status InsFirst(LinkList &L, Link s, Link h){
    Link p = h->next;
    h->next = s;
    s->next = p;
    if (h == L.tail) { //说明原链表为空表，头指针和尾指针均指向头结点
        L.tail = h->next;
    }
    L.len++;
    return OK;
}

//已知h指向线性链表的头结点，删除链表中的第一个结点并以q返回
Status DelFirst(LinkList &L, Link h, Link &q){
    q = h->next;
    //如果q存在，即链表非空
    if (q) {
        h->next = q->next;
        //即删除第一个结点之后判断表是否为空
        if (!h->next) {
            //如果表为空，修改尾指针
            L.tail = h;
        }
        L.len--;
        return OK;
    }else{
        return FALSE;
    }
}

















