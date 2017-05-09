//
//  SLinkList.cpp
//  DataStruct
//
//  Created by guyuexing on 17/5/3.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "SLinkList.hpp"

//静态链表初始化时就已经创建了所有的存储空间，Malloc的作用是将备用链表的结点取出并返回结点位序
int Malloc(SLinkList space){
    //用i返回备用链表的第一个结点
    int i = space[0].cur;
    //如果第一个结点不为空，将备用链表的第一个结点变更为原备用链表的第二个结点
    if (i) {
        space[0].cur = space[i].cur;
    }
    return i; //返回新开辟结点的位序
}

//Free的作用是将链表中不需要的结点放回到备用链表中的第一个结点
void Free(SLinkList space, int i){
    //i结点指向的下一个结点是备用链表中的第二个结点，即将释放结点i放回到备用链表第一个位置
    space[i].cur = space[0].cur;
    space[0].cur = i;
}

//初始化静态链表
void InitList(SLinkList L){
    //构造一个空的链表，表头为L的最后一个单元L[MAXSIZE-1],其余单元链成一个备用链表，表头为L的第一个单元L[0],"0"表示空指针
    L[MAXSIZE-1].cur = 0;//L的最后一个单元为空链表的表头
    for (int i=0; i<MAXSIZE-2; i++) {
        L[i].cur = i+1;
    }
    L[MAXSIZE-2].cur = 0; //0表示空指针
}

//清空静态链表，就是将链表链接到备用链表
Status ClearList(SLinkList L){
    int i, j = 0, k;
    i = L[MAXSIZE-1].cur; //i为链表指向的第一个结点
    L[MAXSIZE-1].cur = 0; //链表的表头置为空，即表头不指向任何结点了
    k = L[0].cur; //备用链表的第一个结点位置赋值给k，L[0]是备用链表的表头
    L[0].cur = i; //把链表的第一个结点链接到备用链表的表头，这样备用链表包含了链表的所有元素
    
    //这个while循环目的是为了找到原料链表的最后一个结点的位置，并将此位置赋值给j
    while (i) {
        j = i;
        //指向下一个元素
        i = L[i].cur;
    }
    L[j].cur = k; //原备用链表的第一个结点链接到现在备用链表的尾部，这样备用链表就包括了所有的元素了
    return OK;
}

//判断L是否为空表
Status ListEmpty(SLinkList L){
    if (L[MAXSIZE-1].cur == 0) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//计算链表L中的元素个数
int ListLength(SLinkList L){
    int j = 0;
    int i = L[MAXSIZE-1].cur; //返回链表第一个结点的位置
    while (i) {
        j++;
        i = L[i].cur; //i指向下一个元素
    }
    return j;
}

//返回L中第i个元素值，用elem接收
Status GetElem(SLinkList L, int i, ElemType &elem){
    //如果i位置不在表L中，返回错误
    if (i<1 || i>ListLength(L)) {
        return ERROR;
    }
    //用k指向表头的序号
    int k=MAXSIZE-1;
    for (int j=1; j<=i; j++) {
        //k指向下一个位置
        k = L[k].cur;
    }
    elem = L[k].data;
    return OK;
}

//在静态链表L中找第一个与elem相等的元素位置
int LocateElem(SLinkList L, ElemType elem){
    int i = L[MAXSIZE-1].cur;  //用i指向表L的第一个结点
    while (i) {
        if (L[i].data == elem) {
            return i;
        }else{
            i = L[i].cur; //i指向下一个结点
        }
    }
    return INFEASIBLE;
}

//在静态链表L中找cur元素的前一个元素
Status priorElem(SLinkList L, ElemType cur, ElemType &prior){
    int i = L[MAXSIZE-1].cur;  //用i指向表L中的第一个结点
    int j = i;    //j用来表示i的前一个元素，目前都指向第一个结点
    i = L[i].cur; //用i指向表L中的第二个结点
    while (i&&j) {
        if (L[i].data == cur) {
            prior = L[j].data;
            return OK;
        }else{
            j = i;
            i = L[i].cur;
        }
    }
    return ERROR;
}

//在静态链表L中找cur元素的后一个元素
Status nextElem(SLinkList L, ElemType cur, ElemType &next){
    int i = L[MAXSIZE-1].cur; //用i指向表L中的第一个结点
    int j = L[i].cur;         //用j指向表L中的第二个结点
    while (i&&j) {
        if (L[i].data == cur) {
            next = L[j].data;
            return OK;
        }else{
            i = j;
            j = L[j].cur;
        }
    }
    return ERROR;
}

//插入数据元素elem到链表L的第i个位置
Status ListInsert(SLinkList L, ElemType elem, int i){
    if (i<1 || i>ListLength(L)) {
        return ERROR;
    }
    //p指向链表L的第一个结点,q指向L的表头
    int p = L[MAXSIZE-1].cur;
    int q = MAXSIZE-1;
    //k是待插入的结点的位序
    int k = Malloc(L);
    if (k) {
        L[k].data = elem;
        //循环找到L的第i个结点，p是第i个结点的位序，q是i前一个结点的位序
        for (int j=1; j<i; j++) {
            q = p;
            p = L[p].cur;
        }
        L[q].cur = k;
        L[k].cur = p;
        return OK;
    }
    return ERROR;
}

//删除链表L中的第i个元素，并用elem接收删除的数据
Status ListDelete(SLinkList L, int i, ElemType &elem){
    if (i<1 || i>ListLength(L)) {
        return ERROR;
    }
    int j = L[MAXSIZE-1].cur; //j指向链表的第一个元素
    int p = MAXSIZE-1; //p指向链表表头
    for (int k = 1; k<i; k++) {
        p = j;
        j = L[j].cur;
    }//循环结束后，j指向第i个元素，p指向i的前一个元素
    elem = L[j].data;
    L[p].cur = L[j].cur;
    Free(L, j);
    return OK;
}

//对链表L中的每一个结点的数据都调用Visit方法
Status ListTraverse(SLinkList L, void (*visit)(ElemType elem)){
    int i = L[MAXSIZE-1].cur;//i指向链表的第一个元素
    while (i) {//链表L中的每一个元素都调用visit方法
        visit(L[i].data);
        i = L[i].cur; //i指向下一个结点
    }
    printf("\n");
    return OK;
}
