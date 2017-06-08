//
//  LinkQueue.hpp
//  DataStruct
//
//  Created by guyuexing on 2017/6/8.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "PublicHeader.h"

typedef int QElemType;

typedef struct QNode{
    QElemType data;
    QNode *next;
} *QueuePtr;

struct LinkQueue{
    QueuePtr rear,front;//队头，队尾指针
};
