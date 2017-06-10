//
//  SqQueue.hpp
//  DataStruct
//
//  Created by haozhu on 2017/6/10.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "PublicHeader.h"

#define MAXQSIZE 5 //最大队列长度（对于循环队列，最大队列长度要减1）
typedef int QElemType;

//队列的顺序存储结构（可用于循环队列和非循环队列）
struct SqQueue{
    QElemType *base;  //初始化的动态分配存储空间，用来指向分配的顺序空间的首地址
    int front;  //头指针，若队列不空，指向队列头元素
    int rear;   //尾指针，若队列不空，指向队列尾元素的下一个位置
};
