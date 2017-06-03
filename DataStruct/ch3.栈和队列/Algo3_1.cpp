//
//  Algo3_1.cpp
//  DataStruct
//
//  Created by haozhu on 2017/6/3.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "Algo3_1.hpp"

//对于输出的任意一个非负十进制整数，打印输出与其相等的八进制数
void conversion(){

    printf("请输入任意一个非负十进制数：");
    int a;
    scanf("%d",&a);
    if (a<0) {
        printf("输入数据有误");
        exit(ERROR);
    }
    SqStack S;
    InitStack(S);
    int c; //c表示除以8后的余数
    c = a%8;
    a = a/8;
    Push(S, c);
    while (a) {
        c = a%8;
        a = a/8;
        Push(S, c);
    }
    SElemType e;
    while (!EmptyStack(S)) {
        Pop(S, e);
        printf("%d",e);
    }
    printf("\n");
}

void main3_1(){
    conversion();
}
