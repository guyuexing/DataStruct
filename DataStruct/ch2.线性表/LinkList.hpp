//
//  LinkList.hpp
//  DataStruct
//
//  Created by guyuexing on 17/4/27.
//  Copyright © 2017年 neu. All rights reserved.
//
#include "PublicHeader.h"

typedef int ElemType;

struct LNode {
    //存储的数据
    ElemType data;
    //指向下个数据的指针
    LNode *next;
};

typedef LNode *LinkList;  //定义了指向LNode这种结构的指针

Status InitLinkList(LinkList &L);

Status DestoryLinkList(LinkList &L);

Status ClearLinkList(LinkList L);

Status ListEmpety(LinkList L);

int ListLength(LinkList L);

Status GetElem(LinkList L, int i, ElemType &e);

int LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType e1, ElemType e2));

Status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e);

Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e);

Status ListInsert(LinkList L, int i, ElemType e);

Status DeleteList(LinkList L, int i, ElemType &e);

Status ListTraverse(LinkList L, void(*vi)(ElemType e));