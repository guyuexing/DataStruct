//
//  Polynomial.cpp
//  DataStruct
//
//  Created by guyuexing on 2017/5/31.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "Polynomial.hpp"

//依据a>、=、<b的指数值，分别返回1、0、-1
int compare(Term a, Term b){
    if (a.expn == b.expn) {
        return 0;
    }else{
        return (a.expn-b.expn)/abs(a.expn-b.expn);
    }
}

//分配由p指向的值为e的结点，并返回OK，若分配失败，则返回error
Status MakeNode(Link &p, PolyElemType e){
    p = (Link)malloc(sizeof(LNode));
    if (!p) {
        return ERROR;
    }
    p->data = e;
    return OK;
}

//构造一个空的线性链表P
Status InitPolyn(Polynomial &P){
    //生成头结点
    Link p = (Link)malloc(sizeof(LNode));
    if (!p) {
        return ERROR;
    }
    p->next = NULL;
    P.header = P.tail = p;
    P.len = 0;
    return OK;
}

//已知h指向线性链表的头结点，将s所指结点插入在原第一个结点之前（即s成为第一个结点）
Status InsFirst(Polynomial &P, Link s, Link h){
    //p指向原来的第一个节点
    Link p = h->next;
    h->next = s;
    s->next = p;
    if (h == P.tail) { //说明原链表为空表，头指针和尾指针均指向头结点；如果不相等，即使插入结点（只要不是插到链表尾部），也不需要移动尾指针
        P.tail = h->next;
    }
    P.len++;
    return OK;
}

Position LocateElem(Polynomial P, PolyElemType e, Status (*compare)(PolyElemType e1, PolyElemType e2)){
    Link p = P.header->next;
    while (p!=NULL) {
        if (compare(p->data,e)) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

//若升序链表L中存在与e满足判定函数compare取值为0的元素，则p返回L中第一个值为e的结点的位置，并返回true；否则p指示第一个与e满足判定函数compare>0的元素的前驱的位置，并返回false（用于一元多项式）
Status LocatElem(Polynomial P, PolyElemType e, Position &p, int(*compare)(PolyElemType, PolyElemType)){
    Link q = P.header;
    Link s;
    do {
        s = q;
        q = q->next;
    } while (q && compare(q->data,e)<0); //循环结束后q可能到了表尾，也可能是compare(q->data,e)>=0
    if (!q||compare(q->data,e)>0) {
        p = s;
        return FALSE;
    }else{
        p = q;
        return TRUE;
    }
}

//已知L为有序线性链表，将e元素按非降序插入在L中（用于一元多项式）
Status OrderInsert(Polynomial &P, PolyElemType e, int (*compare)(PolyElemType, PolyElemType)){
    Link p = P.header->next;
    Link q = P.header; //q用来表示p的前驱
    while (p!=NULL) { //之所以用p!=NULL作为循环结束条件，是为了让e能与链表L的最后一个结点元素值做比较
        
        //比较p指向结点的数据与e的大小，当p->data第一次大于等于e时，e即插入在p的前驱和p之间
        if (compare(p->data,e)>=0) {
            break;
        }
        q = p;
        p = p->next;
    }
    Link s = (Link)malloc(sizeof(LNode));
    s->data = e;
    q->next = s;
    s->next = p;
    //如果p等于NULL说明遍历到最后也没有找到比e大的值，因此e所在结点是表尾，修改表尾指针
    if (p==NULL) {
        P.tail = s;
    }
    P.len++;
    return OK;
}

//
void creatPolyn(Polynomial &P, int m){
    Position q, s;
    Term t;
    InitPolyn(P);
    printf("请输入%d个指数、系数：\n",m);
    for (int i=1; i<=m; i++) {
        scanf("%d,%f",&t.expn,&t.coef);
        if (!LocatElem(P, t, q, compare)) { //q返回与t的指数项相等的结点位置或者第一个与t满足判定函数compare>0元素的前驱位置
            if (MakeNode(s, t)) {
                InsFirst(P, s, q);
            }
        }
    }
}
