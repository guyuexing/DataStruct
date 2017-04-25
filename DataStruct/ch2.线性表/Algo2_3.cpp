//
//  Algo2_3.cpp
//  DataStruct
//
//  Created by guyuexing on 17/4/25.
//  Copyright © 2017年 neu. All rights reserved.
//
/*
 该算法的时间复杂度为O(La.length + Lb.length)
 此算法之所以有线性的时间复杂度是因为：
    1.由于La和Lb中元素依值递增（同一集合中元素不等），则对Lb中的每个元素，不需要
      在La中从表头至表尾全程搜索
    2.由于用新表Lc表示“并集”，则插入操作实际上是借助“复制”操作来完成的；否则若将
      Lb中的元素插入La，为保持La中元素递增有序，必须移动元素
 因此，若以线性表表示集合并进行集合的各种运算，应先对表中元素进行排序
 */

#include "Algo2_3.hpp"

void mergeList_Sq(SqList La, SqList Lb, SqList &Lc){
    ElemType *pa = La.elem;
    ElemType *pb = Lb.elem;
    int length = La.length + Lb.length;
    ElemType *pc = (ElemType *)malloc(sizeof(ElemType)*length);
    if (!pc) {
        exit(OVERFLOWD);
    }
    Lc.elem = pc;
    Lc.length = Lc.listSize = length;

    while (pa<=La.elem+La.length-1 && pb<=Lb.elem+Lb.length-1) {
        if (*pa>=*pb) {
            *(pc++) = *(pb++);
        }else{
            *(pc++) = *(pa++);
        }
    }
    
    while (pa<=La.elem+La.length-1) {
        *pc++ = *pa++;
    }
    
    while (pb<=Lb.elem+Lb.length-1) {
        *pc++ = *pb++;
    }
}