//
//  SLinkList.cpp
//  DataStruct
//
//  Created by guyuexing on 17/5/3.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "SLinkList.hpp"

void InitList(SLinkList L){
    //构造一个空的链表，表头为L的最后一个单元L[MAXSIZE-1],其余单元链成一个备用链表，表头为L的第一个单元L[0],"0"表示空指针
    L[MAXSIZE-1].cur = 0;//L的最后一个单元为空链表的表头
    for (int i=0; i<MAXSIZE-2; i++) {
        L[i].cur = i+1;
    }
    L[MAXSIZE-2].cur = 0; //0表示空指针
}

Status ClearList(SLinkList L){
    int i, j = 0, k;
    i = L[MAXSIZE-1].cur; //i为链表指向的第一个结点
    L[MAXSIZE-1].cur = 0; //链表的表头置为空，即表头不指向任何结点了
    k = L[0].cur; //备用链表的第一个结点位置赋值给k，L[0]是备用链表的表头
    L[0].cur = i; //把链表的第一个结点链接到备用链表的表头
    
    //这个while循环目的是为了找到最后一个结点的位置，并将此位置赋值给j
    while (i) {
        j = i;
        //指向下一个元素
        i = L[i].cur;
    }
    L[j].cur = k; //备用链表的第一个结点链接到链表的尾部
    return OK;
}

//判断L是否为空表
Status ListEmpty(SLinkList L){
    if (L[MAXSIZE-1].cur == 0) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//计算链表L中的元素个数
int ListLength(SLinkList L){
    int j = 0;
    int i = L[MAXSIZE-1].cur; //返回链表第一个结点的位置
    while (i) {
        j++;
        i = L[i].cur; //i指向下一个元素
    }
    return j;
}

//返回L中第i个元素值，用elem接收
Status GetElem(SLinkList L, int i, ElemType &elem){
    //如果i位置不在表L中，返回错误
    if (i<1 || i>ListLength(L)) {
        return ERROR;
    }
    //用k指向表头的序号
    int k=MAXSIZE-1;
    for (int j=1; j<=i; j++) {
        //k指向下一个位置
        k = L[k].cur;
    }
    return OK;
}

//在静态链表L中找第一个与elem相等的元素位置
int LocateElem(SLinkList L, ElemType elem){
    int i = L[MAXSIZE-1].cur;  //用i指向表L的第一个结点
    while (i) {
        if (L[i].data == elem) {
            return i;
        }else{
            i = L[i].cur; //i指向下一个结点
        }
    }
    return INFEASIBLE;
}

Status priorElem(SLinkList L, ElemType cur, ElemType &prior){
    int i = L[MAXSIZE-1].cur;  //用i指向表L中的第一个结点
    int j = 0;
    while (i) {
        if (L[i].data == cur) {
            
        }else{
            i = L[i].cur;
        }
    }
    return OK;
}
