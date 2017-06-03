//
//  SqStack.hpp
//  DataStruct
//
//  Created by haozhu on 2017/6/3.
//  Copyright © 2017年 neu. All rights reserved.
//

//栈的顺序存储表示

#include "PublicHeader.h"

typedef int SElemType;
#define STACK_INIT_SIZE 10  //存储空间初始分配量
#define STACKINCREMENT  2   //存储空间分配增量

//顺序栈
struct SqStack {
    SElemType *base;  //在栈构造之前和销毁之后，base的值为NULL
    SElemType *top;   //栈顶指针，也就是表尾
    int stackSize;    //当前已分配的存储空间，以元素为单位
};

//栈的链式表示-链栈操作参考OptimalLinkList


Status InitStack(SqStack &S);

Status DestoryStack(SqStack &S);

Status ClearStack(SqStack &S);

Status EmptyStack(SqStack S);

int LengthStack(SqStack S);

Status GetTop(SqStack S, SElemType &e);

Status Push(SqStack &S, SElemType e);

Status Pop(SqStack &S, SElemType &e);

Status StackTraverse(SqStack S, void(*visit)(SElemType));
