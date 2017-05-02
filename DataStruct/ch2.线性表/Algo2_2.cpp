//
//  Algo2_2.cpp
//  DataStruct
//
//  Created by guyuexing on 17/4/23.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "Algo2_2.hpp"

/*
 虽然此算法包含了3个循环语句，但只有当i和j均指向表中实际存在的数据元素时，才能取得数据元素的值进行相互比较；并且当其中一个线性表的数据元素均已插入到线性表LC后，只要将另外一个线性表中的剩余元素依次插入即可
 此算法的时间复杂度为O(ListLength(LA)+ListLength(LB))
 
 */

//La,Lb均为递增有序列表，将其归并为列表Lc，Lc也是递增，没有去重
void mergeList(SqList La, SqList Lb, SqList &Lc){
    //初始化Lc
    InitList(Lc);
    //取得La和Lb的长度
    int la_len = La.length;
    int lb_len = Lb.length;
    
    int i, j, k;
    i = j = 1, k = 0;
    //分别用来接收La和Lb列表的元素
    ElemType ai, bj;
    
    //当La和Lb列表中的元素均没有遍历完时
    while (i<=la_len && j <= lb_len) {
        //取出La和Lb中对应位序的元素
        GetElem(La, i, ai);
        GetElem(Lb, j, bj);
        //对元素进行比较，向Lc中插入较小的元素
        if (ai<=bj) {
            ListInsert(Lc, ++k, ai);
            i++;
        }else{
            ListInsert(Lc, ++k, bj);
            j++;
        }
    }
    
    //当La长度较长时，将未遍历到的元素插入Lc末尾
    while (i<=la_len) {
        GetElem(La, i++, ai);
        ListInsert(Lc, ++k, ai);
    }
    
    //当Lb长度较长时，将未遍历到的元素插入到Lb末尾
    while (j<=lb_len) {
        GetElem(Lb, j++, bj);
        ListInsert(Lc, ++k, bj);
    }
}

void print2_2(ElemType &e){
    printf("%d",e);
}

void example2_2(){
    /*****两个递增线性表合并成第三个递增线性表，不去重**********/
    SqList La, Lb, Lc;
    int a[4] = {3,5,8,11};
    La.elem = a;
    La.length = sizeof(a)/sizeof(int);
    printf("La = ");
    ListTraverse(La, print2_2);
    
    int b[7] = {2,6,8,9,11,15,20};
    Lb.elem = b;
    Lb.length = sizeof(b)/sizeof(int);
    printf("Lb = ");
    ListTraverse(Lb, print2_2);
    
    mergeList(La, Lb, Lc);
    printf("Lc = ");
    ListTraverse(Lc, print2_2);
}