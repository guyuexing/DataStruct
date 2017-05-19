//
//  DuLinkList.hpp
//  DataStruct
//
//  Created by guyuexing on 2017/5/17.
//  Copyright © 2017年 neu. All rights reserved.
//
//线性链表的双向存储结构

#include "PublicHeader.h"

typedef int ElemType;

typedef struct DuLNode{
    DuLNode *next, *prior;
    ElemType data;
}DuLNode, *DuLinkList;
