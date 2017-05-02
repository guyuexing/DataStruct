//
//  Algo2_4.cpp
//  DataStruct
//
//  Created by guyuexing on 17/5/2.
//  Copyright © 2017年 neu. All rights reserved.
//

//另一种合并线性表的算法：La和Lb中的重复元素不重复引入到Lc中
#include "Algo2_4.hpp"

int compare(ElemType e1, ElemType e2){
    if (e1<e2) {
        return 1;
    }else if (e1==e2){
        return 0;
    }else{
        return -1;
    }
}

void MergeList(SqList La, SqList Lb, SqList &Lc){
    ElemType *pa, *pb, *pc;
    pa = La.elem;
    pb = Lb.elem;
    
    Lc.listSize = La.length+Lb.length;
    pc = Lc.elem = (ElemType *)malloc(sizeof(ElemType)*Lc.listSize);
    if (!Lc.elem) {
        exit(OVERFLOW);
    }
    
    while (pa<=La.elem+La.length-1 && pb<=Lb.elem+Lb.length) {
        switch (compare(*pa, *pb)) {
            case 1:
                *pc++ = *pa++;
                break;
            case 0:
                pa++;  //或pb++
                break;
            case -1:
                *pc++ = *pb++;
            default:
                break;
        }
    }
    
    while (pa<=La.elem+La.length-1) {
        *pc++ = *pa++;
    }
    
    while (pb<=Lb.elem+Lb.length-1) {
        *pc++ = *pb++;
    }
    Lc.length = (int)(pc-Lc.elem);
}