//
//  SLinkList.hpp
//  DataStruct
//
//  Created by guyuexing on 17/5/3.
//  Copyright © 2017年 neu. All rights reserved.
//
#include "PublicHeader.h"

//线性表的静态单链表存储结构
#define MAXSIZE 100
typedef int ElemType;

typedef struct {
    ElemType data;
    int cur;
} component, SLinkList[MAXSIZE];

//定义了component这种数据类型，定义了元素是这种结构体的数组
//数组的一个分量表示一个节点，同时用游标(cur)代替指针指示结点在数组中的相对位置
//数组的第零分量可看成头结点，其指针域指示链表的第一个结点
//这种存储结构仍然需要预先分配一个较大的空间，但在做线性表的插入和删除操作时不需移动元素，仅需修改指针，仍具有链式存储结构的主要优点