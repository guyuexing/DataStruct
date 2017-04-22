//
//  1.Troplet.cpp
//  DataStruct
//
//  Created by guyuexing on 17/4/22.
//  Copyright © 2017年 neu. All rights reserved.
//
#include "Triplet.h"

//Triplet &T为引用传递, 传递其他三个参数用于初始化三元组T
Status InitTriplet (Triplet &T, ElemType v1, ElemType v2, ElemType v3){
    if (!(T = (ElemType *)malloc(sizeof(ElemType)*3))) {
        exit(OVERFLOW);
    }
    T[0] = v1;
    T[1] = v2;
    T[2] = v3;
    return OK;
}

//销毁三元组T
Status Destroy (Triplet &T){
    free(T);
    T = NULL;
    return OK;
}

//取出T中第i个元素的值
Status Get(Triplet T, int i, ElemType &e){
    if (i<0 || i >2) {
        return ERROR;
    }
    e = T[i];
    return OK;
}

//改变T中第i个元素值为e
Status Put(Triplet &T, int i, ElemType e){
    if (i<0||i>2) {
        return ERROR;
    }
    T[i] = e;
    return OK;
}

//三元组T是否是升序排序
Status IsAcending(Triplet T){
    return (T[0]<=T[1] && T[1]<=T[2]);
}

//三元组T是否是降序排序
Status IsDescending(Triplet T){
    return (T[0]>=T[1] && T[1]>=T[2]);
}

//用e返回T三元组中最大值
Status Max(Triplet T, ElemType &e){
    int MAX = T[0];
    if (T[1]>=MAX) {
        MAX = T[1];
    }
    if (T[2]>=MAX) {
        MAX = T[2];
    }
    e = MAX;
    return OK;
}

//用e返回T三元组中最小值
Status Min(Triplet T, ElemType &e){
    int MIN = T[0];
    if (T[1]<=MIN) {
        MIN = T[1];
    }
    if (T[2]<=MIN) {
        MIN = T[2];
    }
    e = MIN;
    return OK;
}

