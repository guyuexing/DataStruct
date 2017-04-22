//
//  Triplet.h
//  DataStruct
//
//  Created by guyuexing on 17/4/22.
//  Copyright © 2017年 neu. All rights reserved.
//
#include "PublicHeader.h"

typedef int ElemType;  //定义抽象数据类型ElemType在本例中为整型
typedef ElemType * Triplet;  //Triplet为ElemType类型的指针，存放ElemType类型的地址

Status InitTriplet (Triplet &T, ElemType v1, ElemType v2, ElemType v3);

Status Destroy (Triplet &T);

Status Get(Triplet T, int i, ElemType &e);

Status Put(Triplet &T, int i, ElemType e);

Status IsAcending(Triplet T);

Status IsDescending(Triplet T);

Status Max(Triplet T, ElemType &e);

Status Min(Triplet T, ElemType &e);