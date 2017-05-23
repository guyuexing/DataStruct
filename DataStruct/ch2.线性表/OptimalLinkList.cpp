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
        //头结点和尾结点均指向头结点
        L.tail = L.header;
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
    //p指向原来的第一个节点
    Link p = h->next;
    h->next = s;
    s->next = p;
    if (h == L.tail) { //说明原链表为空表，头指针和尾指针均指向头结点；如果不相等，即使插入结点（只要不是插到链表尾部），也不需要移动尾指针
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

//将指针s(s->data为第一个数据元素)所指(彼此以指针相链接，以NULL结尾)的一串结点链接在链表L的最后一个结点之后，并改变链表L的尾指针指向新的尾结点
Status Append(LinkList &L, Link s){
    Link p = s;
    int i = 1;
    //这段循环目的是为了找到s的最后一个结点
    while (p->next) {
        i++;
        p = p->next;
    }
    L.tail->next = s;
    //L的尾结点指向s的最后一个结点
    L.tail = p;
    L.len += i;
    return OK;
}

//已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置，若无前驱，则返回NULL
Position PriorPos(LinkList L, Link p){
    //如果p是链表L的第一个节点，无前驱
    if (p==L.header->next) {
        return NULL;
    }
    Link q = L.header->next;
    while (q->next!=L.tail) {
        if (q->next == p) {
            return q;
        }
        q = q->next;
    }
    return NULL;
}

//删除线性表L中的尾结点并以q返回，改变链表L的尾指针指向新的尾结点
Status Remove(LinkList &L, Link &q){
    //如果L为空表
    if (L.len == 0) {
        q = NULL;
        return FALSE;
    }
    //p指向L的第一个结点
    Link p = L.header->next;
    //for循环找到链表L尾结点的前一个结点
    while (p->next!=L.tail) {
        p = p->next;
    }
    q = L.tail;
    p->next = NULL;
    L.tail = p;
    L.len--;
    return OK;
}











