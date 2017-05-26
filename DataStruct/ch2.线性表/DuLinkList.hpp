//
//  DuLinkList.hpp
//  DataStruct
//
//  Created by guyuexing on 2017/5/17.
//  Copyright © 2017年 neu. All rights reserved.
//
//线性链表的双向存储结构

#include "PublicHeader.h"

//typedef int ElemType;

typedef struct DuLNode{
    DuLNode *next, *prior;
    ElemType data;
}DuLNode, *DuLinkList;

Status initList(DuLinkList &L);

Status DestoryList(DuLinkList &L);

Status ClearList(DuLinkList L);

Status ListEmpty(DuLinkList L);

int ListLength(DuLinkList L);

Status GetElem(DuLinkList L, int i, ElemType &e);

Status IsEqual(ElemType e1, ElemType e2);

int LocaleElem(DuLinkList L, ElemType e, Status (*compare)(ElemType, ElemType));

Status PriorElem(DuLinkList L, ElemType cur_e, ElemType &prior_e);

Status NextElem(DuLinkList L, ElemType cur_e, ElemType &next_e);

DuLinkList GetElemP(DuLinkList L, int i);

Status ListInsert(DuLinkList L, int i, ElemType e);

Status ListDelete(DuLinkList L, int i, ElemType &e);

void ListTraverse(DuLinkList L, void(*visit)(ElemType e));

void ListTraverseBack(DuLinkList L, void(*visit)(ElemType e));

