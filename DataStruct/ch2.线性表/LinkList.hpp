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