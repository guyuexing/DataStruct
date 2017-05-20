//
//  DuLinkList.cpp
//  DataStruct
//
//  Created by guyuexing on 2017/5/17.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "DuLinkList.hpp"

//初始化双向循环链表
Status initList(DuLinkList &L){
    L = (DuLinkList)malloc(sizeof(DuLNode));
    if (L) {
        L->next = L->prior = L;
        return OK;
    }else{
        return OVERFLOW;
    }
}

//销毁双向循环链表
Status DestoryList(DuLinkList &L){
    DuLinkList q, p = L->next;
    while (p!=L) {
        q=p->next;
        free(p);
        p=q;
    }
    free(L);
    L=NULL;
    return OK;
}

//将L重置为空表
Status ClearList(DuLinkList L){
    DuLinkList p = L->next, q; //p指向下一个结点
    while (p!=L) {  //p没到表头
        q = p->next;
        free(p);
        p = q;
    }
    L->next = L->prior = L;  //头结点的两个指针均指向自身
    return OK;
}

//判断表L是否为空表
Status ListEmpty(DuLinkList L){
    if (L->next == L && L->prior == L) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//返回L中的元素个数
int ListLength(DuLinkList L){
    int i = 0;
    //p指向L的下一个结点
    DuLinkList p = L->next;
    //p不等于
    while (p!=L) {
        i++;
        p = p->next;
    }
    return i;
}

//当第i个元素存在时，其值赋给e并返回OK，否则返回error
Status GetElem(DuLinkList L, int i, ElemType &e){
    //如果i超出了链表的范围就返回错误
    if (i<1 || i>ListLength(L)) {
        return ERROR;
    }
    //p指向链表的第一个节点
    DuLinkList p = L->next;
    int j = 1; //j为计数器
    
    //循环结束后j=i，p指向第i个节点
    while (p!=L && j<i) {
        j++;
        p = p->next;
    }
    if (j>i || p == L) {  //第i个元素不存在
        return ERROR;
    }
    //取出第i个元素
    e = p->data;
    return OK;
}

//此函数用来判断两个元素是否相等
Status IsEqual(ElemType e1, ElemType e2){
    if (e1 == e2) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//返回元素e在链表L中的位序
int LocaleElem(DuLinkList L, ElemType e, Status (*compare)(ElemType, ElemType)){
    //i为计数器
    int i = 1;
    //p指向L链表中的第一个节点
    DuLinkList p = L->next;
    while (p!=L) {
        //在L中找到与e相等节点的位序
        if (compare(e,p->data)) {
            return i;
        }
        i++;
        p = p->next;
    }
    return 0;
}

//若cur_e是L的数据元素且不是第一个，则用prior_e返回它的前驱
Status PriorElem(DuLinkList L, ElemType cur_e, ElemType &prior_e){
    DuLinkList p = L->next->next;
    while (p!=L) {
        if (p->data == cur_e) {
            prior_e = p->prior->data;
            return TRUE;
        }
        p = p->next;
    }
    return FALSE;
}

//若cur_e是L的数据元素且不是最后一个，则用next_e返回它的后继
Status NextElem(DuLinkList L, ElemType cur_e, ElemType &next_e){
    /*
     我的写法：
     DuLinkList p = L->next;
        while (p != L->prior) {
            if (p->data == cur_e) {
                next_e = p->next->data;
                return TRUE;
            }
            p = p->next;
        }
     */
    
    //p指向链表L中的第二个元素
    DuLinkList p = L->next->next;
    while (p!=L) {
        if (p->prior->data == cur_e) {
            next_e = p->data;
            return TRUE;
        }
        p = p->next;
    }
    return FALSE;
}

//在双向链表L中返回第i个元素的位置指针
DuLinkList GetElemP(DuLinkList L, int i){
    /*
     我的写法：
        if (i<1 || i>ListLength(L)) {
            return NULL;
        }
        int j = 1;
        DuLinkList p = L->next;
        while (p!=L && j<i) {      //或者直接使用for循环
            p = p->next;
            j++;
        }
        if (p==L || j>i) {
            return NULL;
        }
        return p;
     */
    
    DuLinkList p = L;
    for (int j = 1; j<=i; j++) {
        p = p->next;
    }
    return p;
}

//在带头结点的双链循环线性表L中第i个位置之前插入元素e，i的合法值 1≤i≤表长+1
Status ListInsert(DuLinkList L, int i, ElemType e){
    
    //输入的i值不合法
    if (i<1 || i>ListLength(L)+1) {
        return ERROR;
    }
    
    /*
     我的写法：
        DuLinkList p = L;
        for (int j = 1; j<=i; j++) {   //经过for循环之后，p是第i个元素的位置指针
            p = p->next;
        }
     */
    
    //在L中确定第i-1个元素的位置指针
    DuLinkList p = GetElemP(L, i-1);
    if (!p) {  //第i-1个元素不存在
        return ERROR;
    }
    
    DuLinkList q = (DuLinkList)malloc(sizeof(DuLNode));
    if (!q) {
        return OVERFLOW;
    }
    q->data = e;
    q->prior = p;
    q->next = p->next;
    p->next->prior = q;
    p->next = q;
    return OK;
}

//删除带头结点的双链循环线性表L的第i个元素，i的合法值为为1≤i≤表长
Status ListDelete(DuLinkList L, int i, ElemType &e){
    //输入的i值不合法
    if (i<1 || i>ListLength(L)) {
        return ERROR;
    }
    //在L中确定第i个元素的位置指针
    DuLinkList p = GetElemP(L, i);
    if (!p) {   //第i个元素不存在
        return ERROR;
    }
    
    e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    return OK;
}

//由双链循环线性表L的头结点出发，正序对每个数据元素调用函数visit()
void ListTraverse(DuLinkList L, void(*visit)(ElemType e)){
    DuLinkList p = L->next; //p指向头结点
    while (p!=L) {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
}

//由双链循环线性表L的头结点出发，逆序对每个数据元素调用函数visit()
void ListTraverseBack(DuLinkList L, void(*visit)(ElemType e)){
    DuLinkList p = L->prior;  //p指向尾结点
    while (p!=L) {
        visit(p->data);
        p = p->prior;
    }
    printf("\n");
}
