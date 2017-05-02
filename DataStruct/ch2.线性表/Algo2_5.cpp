//
//  Algo2_5.cpp
//  DataStruct
//
//  Created by guyuexing on 17/5/2.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "Algo2_5.hpp"

//算法2.11
//正逆位序建立带头结点的单链表时间复杂度均为O(n)
//逆位序（元素插在表头）输入n个表元素值，建立带头结点的单链线性表L
void CreateList_N(LinkList &L, int n){
    //先建立一个带头结点的单链线性表
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LinkList p;
    for (int i = n; i>0; i--) {
        //给新节点分配内存
        p = (LinkList)malloc(sizeof(LNode));
        printf("输入第%d个元素的值",i);
        scanf("%d",&p->data);
        //p的后继赋值为原来L的第一个节点
        p->next = L->next;
        //L的第一个节点赋值为p
        L->next = p;
    }
}

//正位序（元素插在表尾）输入n个表元素值，建立带头结点的单链线性表L
void CreateList_S(LinkList &L, int n){
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LinkList p = nullptr;
    LinkList q = L;
    for (int i=1; i<=n; i++) {
        p = (LinkList)malloc(sizeof(LNode));
        printf("请输入第%d个元素的值",i);
        scanf("%d",&p->data);
        //q是用来标记表L的最后一个元素的
        q->next = p;
        q = p;
    }
    //最后一个节点的后继为NULL
    p->next = NULL;
}


/*************************/
//算法2.12

//将有序的递增的线性表La和Lb合并成也是递增的线性表Lc
//我的写法
void MergeList_L(LinkList La, LinkList Lb, LinkList &Lc){
    LinkList pa = La->next;
    LinkList pb = Lb->next;
    LinkList pc;
    Lc = (LinkList)malloc(sizeof(LNode));
    Lc->next = NULL;
    while (pa && pb) {
        pc = (LinkList)malloc(sizeof(LNode));
        pc->next = NULL;
        pc->next = Lc->next;
        Lc->next = pc;
        if (pa->data<=pb->data) {
            pc->data = pa->data;
            pa = pa->next;
        }else{
            pc->data = pb->data;
            pb = pb->next;
        }
    }
    while (pa) {
        pc = (LinkList)malloc(sizeof(LNode));
        pc->next = NULL;
        pc->next = Lc->next;
        Lc->next = pc;
        pc->data = pa->data;
        pa = pa->next;
    }
    while (pb) {
        pc = (LinkList)malloc(sizeof(LNode));
        pc->next = NULL;
        pc->next = Lc->next;
        Lc->next = pc;
        pc->data = pb->data;
        pb = pb->next;
    }
}

//La和Lb均按照有序递增排列，合并La和Lb得到Lc也是按照递增排序
void MergeList_R(LinkList La, LinkList &Lb, LinkList &Lc){
    LinkList pa = La->next;
    LinkList pb = Lb->next;
    //用La的头结点作为Lc的头结点，相当于是将La和Lb的元素合并到La上了，不需要再创建存储空间，因为La和Lb的元素值始终存在，现在只不过是重新组织了一下元素之间的关系
    //算法2.12和算法2.7时间复杂度相同，但空间复杂度不同，在归并两个链表为一个链表时，不需要另建新表的结点空间，而只需将原来两个链表中节点之间的关系解除，重新按照元素值递增的关系将所有结点链接成一个链表即可
    LinkList pc = Lc = La;
    while (pa && pb) {
        if (pa->data <= pb->data) {
            pc->next = pa;
            pc = pc->next;
            pa = pa->next;
        }else{
            pc->next = pb;
            pc = pc->next;
            pb = pb->next;
        }
    }
    pc->next = pa?pa:pb;
    free(Lb);
    Lb = NULL;
}

