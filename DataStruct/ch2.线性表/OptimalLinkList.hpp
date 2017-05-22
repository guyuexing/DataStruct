//
//  OptimalLinkList.hpp
//  DataStruct
//
//  Created by guyuexing on 2017/5/22.
//  Copyright © 2017年 neu. All rights reserved.
//
#include "PublicHeader.h"

typedef int ElemType;

typedef struct LNode{  //结点类型
    ElemType data;
    struct LNode *next;
} *Link, *Position;

struct LinkList{   //链表类型
    Link header, tail;   //分别指向线性链表的头结点和最后一个结点
    int len;             //指示线性链表的元素个数
};
