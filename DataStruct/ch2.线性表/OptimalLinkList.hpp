//
//  OptimalLinkList.hpp
//  DataStruct
//
//  Created by guyuexing on 2017/5/22.
//  Copyright © 2017年 neu. All rights reserved.
//
#include "PublicHeader.h"

typedef struct LNode{  //结点类型
    ElemType data;
    struct LNode *next;
} *Link, *Position;

struct LinkList{   //链表类型
    Link header, tail;   //分别指向线性链表的头结点和最后一个结点
    int len;             //指示线性链表的元素个数
};

Status MakeNode(Link &p, ElemType e);

void FreeNode(Link &p);

Status InitList(LinkList &L);

Status ClearList(LinkList &L);

Status DestoryList(LinkList &L);

Status InsFirst(LinkList &L, Link s, Link h);

Status DelFirst(LinkList &L, Link h, Link &q);

Status Append(LinkList &L, Link s);

Position PriorPos(LinkList L, Link p);

Status Remove(LinkList &L, Link &q);

Status InsBefore(LinkList &L, Link &p, Link s);

Status InsAfter(LinkList &L, Link &p, Link s);

Status SetCurElem(Link p, ElemType e);

ElemType GetCurElem(Link p);

Status ListEmpty(LinkList L);

int ListLength(LinkList L);

Position GetHeader(LinkList L);

Position GetLast(LinkList L);

Position NextPos(Link p);

Status LocatePos(LinkList L, int i, Link &p);

Position LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType e1, ElemType e2));

Status ListTraverse(LinkList L, void (*visit)(ElemType e));

Status OrderInsert(LinkList &L, ElemType e, Status (*compare)(ElemType, ElemType));

Status LocatElem(LinkList L, ElemType e, Position &p, int(*compare)(ElemType, ElemType));

