//
//  List.hpp
//  DataStruct
//
//  Created by guyuexing on 17/4/22.
//  Copyright © 2017年 neu. All rights reserved.
//
#include "PublicHeader.h"

#define LIST_INIT_SIZE 10  //线性表存储空间的初始分配量
#define LIST_INCREMENT 2   //线性表存储空间的分配增量
typedef int ElemType;

//线性表的动态分配顺序存储结构
struct SqList {
    ElemType *elem;    //存储空间基址
    int length;     //当前长度
    int listSize;   //当前分配的存储容量 以sizeof(ElemType)为单位
};

Status InitList(SqList &L);

Status DestoryList(SqList &L);

Status ClearList(SqList &L);

Status ListEmpty(SqList L);

int ListLength(SqList L);

Status GetElem(SqList L, int i, ElemType &e);

int LocateElem(SqList L, ElemType e, Status (*compare)(ElemType,ElemType));

Status PriorElem(SqList L, int cur_e, ElemType &pre_e);

Status NextElem(SqList L, int cur_e, ElemType &next_e);

Status ListInsert(SqList &L, int i, int e);

Status ListDelete(SqList &L, int i, ElemType &e);

Status ListTraverse(SqList L, void (*visit)(ElemType &));
