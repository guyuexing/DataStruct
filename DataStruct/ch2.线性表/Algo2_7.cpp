//
//  Algo2_7.cpp
//  DataStruct
//
//  Created by guyuexing on 2017/5/26.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "Algo2_7.hpp"

//在带头结点的单链线性表L的第i个元素之前插入元素e
Status ListInsert_L(LinkList &L, int i, ElemType e){

    Link q;  //用q指向第i个元素的前一个元素
    LocatePos(L, i-1, q);
    if (!q) { //说明值不合法
        return ERROR;
    }
    Link p; //生成一个结点，并用p指向这个结点
    if (!MakeNode(p, e)) {
        return ERROR;
    }
    //对于从第i个结点开始的链表，第i-1个结点是其头结点
    InsFirst(L, p, q);
    return OK;
}

int compare2_7(ElemType e1, ElemType e2){
    if (e1>=e2) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//已知单链线性表La和Lb的元素按值递增排列，归并La和Lb得到新的单链线性表Lc，Lc的元素也按值递增排列
Status MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc, int (*compare)(ElemType, ElemType)){
    if (!InitList(Lc)) {
        return ERROR;
    }
    Link ha = GetHeader(La);
    Link hb = GetHeader(Lb);
    Link pa = NextPos(ha);
    Link pb = NextPos(hb);
    Link q;
    
    while (!ListEmpty(La)&&ListLength(Lb)) {
        if (compare(pa->data,pb->data)) { //(pa->data>=pb->data,插入pb
            DelFirst(Lb, hb, q);  //删除Lb中的第一个结点并用q返回删除结点
            InsFirst(Lc, q, Lc.tail); //将Lb中删除的结点插入到Lc的表尾
            pb = NextPos(hb);
        }else{
            DelFirst(La, ha, q);
            InsFirst(Lc, q, Lc.tail);
            pa = NextPos(ha);
        }
    }
    if (ListLength(La)) {
        Append(Lc, pa);
    }
    if (ListLength(Lb)) {
        Append(Lc, pb);
    }
    FreeNode(ha);
    FreeNode(hb);
    return OK;
}

void visit(ElemType e){
    printf("%d ",e); // 整型
}

void Maintest2_20(){
    LinkList La,Lb,Lc;
    int j;
    InitList(La);
    for(j=1;j<=5;j++)
        ListInsert_L(La,j,j); // 顺序插入 1 2 3 4 5
    printf("La=");
    ListTraverse(La, visit);
    InitList(Lb);
    for(j=1;j<=5;j++)
        ListInsert_L(Lb,j,2*j); // 顺序插入 2 4 6 8 10
    printf("Lb=");
    ListTraverse(Lb,visit);
    InitList(Lc);
    MergeList_L(La,Lb,Lc,compare2_7); // 归并La和Lb，产生Lc
    printf("Lc=");
    ListTraverse(Lc,visit);
    DestoryList(Lc);
}
