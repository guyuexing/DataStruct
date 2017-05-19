//
//  DuLinkList.cpp
//  DataStruct
//
//  Created by guyuexing on 2017/5/17.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "DuLinkList.hpp"

//初始化双向循环链表
Status initList(DuLinkList &L){
    L = (DuLinkList)malloc(sizeof(DuLNode));
    if (L) {
        L->next = L->prior = L;
        return OK;
    }else{
        return OVERFLOW;
    }
}

//销毁双向循环链表
Status DestoryList(DuLinkList &L){
    DuLinkList q, p = L->next;
    while (p!=L) {
        q=p->next;
        free(p);
        p=q;
    }
    free(L);
    L=NULL;
    return OK;
}

//将L重置为空表
Status ClearList(DuLinkList L){
    DuLinkList p = L->next, q; //p指向下一个结点
    while (p!=L) {  //p没到表头
        q = p->next;
        free(p);
        p = q;
    }
    L->next = L->prior = L;  //头结点的两个指针均指向自身
    return OK;
}

//判断表L是否为空表
Status ListEmpty(DuLinkList L){
    if (L->next == L && L->prior == L) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//返回L中的元素个数
int ListLength(DuLinkList L){
    int i = 0;
    //p指向L的下一个结点
    DuLinkList p = L->next;
    //p不等于
    while (p!=L) {
        i++;
        p = p->next;
    }
    return i;
}










