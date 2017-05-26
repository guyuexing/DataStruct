//
//  Algo2_7.hpp
//  DataStruct
//
//  Created by guyuexing on 2017/5/26.
//  Copyright © 2017年 neu. All rights reserved.
//
//实现算法2.20，2.21
#include "OptimalLinkList.hpp"

Status MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc, int (*compare)(ElemType, ElemType));

Status ListInsert_L(LinkList &L, int i, ElemType e);

void Maintest2_20();
