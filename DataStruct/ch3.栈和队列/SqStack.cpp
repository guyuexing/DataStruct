//
//  SqStack.cpp
//  DataStruct
//
//  Created by haozhu on 2017/6/3.
//  Copyright © 2017年 neu. All rights reserved.
//

//顺序栈的基本操作（9个）

#include "SqStack.hpp"

//初始化栈
Status InitStack(SqStack &S){
    //构造一个空栈
    S.base = (SElemType *)malloc(sizeof(SElemType)*STACK_INIT_SIZE);
    if (!S.base) {
        //存储空间分配失败
        exit(OVERFLOWD);
    }
    S.top = S.base;
    S.stackSize = STACK_INIT_SIZE;
    return OK;
}

//销毁栈S
Status DestoryStack(SqStack &S){
    free(S.base);
    S.top = S.base = NULL;
    S.stackSize = 0;
    return OK;
}

//清空栈S
Status ClearStack(SqStack &S){
    S.top = S.base;
    return OK;
}

//若栈为空栈返回TRUE，否则返回FALSE
Status EmptyStack(SqStack S){
    if (S.base == S.top) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//返回栈的长度,即栈中的元素个数
int LengthStack(SqStack S){
    return (int)(S.top-S.base);
}

//若栈不空，则用e返回S的栈顶元素，并返回OK，否则返回Error
Status GetTop(SqStack S, SElemType &e){
    if (EmptyStack(S)) {
        return ERROR;
    }
    e = *(S.top-1); //非空栈中栈顶指针始终在栈顶元素的下一个位置上
    return OK;
}

//插入元素e为新的栈顶元素
Status Push(SqStack &S, SElemType e){
    //需要先判断栈是否已经满了
    if (LengthStack(S)>=S.stackSize) {  //栈满，需要追加存储空间
        SElemType *newBase = (SElemType *)realloc(S.base, sizeof(SElemType)*(S.stackSize+STACKINCREMENT));
        if (!newBase) {
            exit(OVERFLOWD);
        }else{
            S.base = newBase;
            S.top = S.base + S.stackSize;
            S.stackSize += STACKINCREMENT;
        }
    }
    *S.top = e;
    S.top ++;
    return OK;
}

//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回Error
Status Pop(SqStack &S, SElemType &e){
    //空栈
    if (S.base == S.top) {
        return ERROR;
    }
    e = *(--S.top);  //非空栈中栈顶指针始终在栈顶元素的下一个位置上
    return OK;
}

//从栈底到栈顶依次对栈中的每个元素调用函数visit
Status StackTraverse(SqStack S, void(*visit)(SElemType)){
    while (S.top>S.base) {
        visit(*S.base++);
    }
    printf("\n");
    return OK;
}
