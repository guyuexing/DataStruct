//
//  Polynomial.hpp
//  DataStruct
//
//  Created by guyuexing on 2017/5/31.
//  Copyright © 2017年 neu. All rights reserved.
//
#include "PublicHeader.h"

//抽象数据类型Polynomial的实现
typedef struct {  //项的表示，多项式的项作为LinkList的数据元素
    float coef;  //系数项
    int expn;    //指数项
} Term, PolyElemType;

typedef struct LNode{  //结点类型
    PolyElemType data;
    struct LNode *next;
} *Link, *Position;

struct Polynomial{   //链表类型
    Link header, tail;   //分别指向线性链表的头结点和最后一个结点
    int len;             //指示线性链表的元素个数
};
