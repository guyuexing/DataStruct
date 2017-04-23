//
//  main.cpp
//  ch2.线性表
//
//  Created by guyuexing on 17/4/22.
//  Copyright © 2017年 neu. All rights reserved.
//

#include <iostream>
//#include "Algo2_1.hpp"
#include "Algo2_2.hpp"

void print(ElemType &e){
    printf("%d",e);
}

int main(int argc, const char * argv[]) {
    
    /********两个线性表合并的算法，合并到末尾，去除重复元素**********/
//    SqList La, Lb;
//    Status i;
//    i = InitList(La);
//    if (i==1) {
//        for (int j = 1; j<=5; j++) {
//            ListInsert(La, j, j);
//        }
//    }
//    printf("La = ");
//    ListTraverse(La, print);
//    
//    i = InitList(Lb);
//    if (i==1) {
//        for (int j = 1; j<=5; j++) {
//            ListInsert(Lb, j, 2*j);
//        }
//    }
//    printf("Lb = ");
//    ListTraverse(Lb, print);
//    
//    Union(La, Lb);
//    printf("合并之后La = ");
//    ListTraverse(La, print);
    
    /*****两个递增线性表合并成第三个递增线性表，不去重**********/
    SqList La, Lb, Lc;
    int a[4] = {3,5,8,11};
    La.elem = a;
    La.length = sizeof(a)/sizeof(int);
    printf("La = ");
    ListTraverse(La, print);
    
    int b[7] = {2,6,8,9,11,15,20};
    Lb.elem = b;
    Lb.length = sizeof(b)/sizeof(int);
    printf("Lb = ");
    ListTraverse(Lb, print);
    
    mergeList(La, Lb, Lc);
    printf("Lc = ");
    ListTraverse(Lc, print);
    
    return 0;
}
