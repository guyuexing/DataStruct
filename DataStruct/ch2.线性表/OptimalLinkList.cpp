//
//  OptimalLinkList.cpp
//  DataStruct
//
//  Created by guyuexing on 2017/5/22.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "OptimalLinkList.hpp"

//分配由p指向的值为e的结点，并返回OK，若分配失败，则返回error
Status MakeNode(Link &p, ElemType e){
    p = (Link)malloc(sizeof(LNode));
    if (!p) {
        return ERROR;
    }
    p->data = e;
    return OK;
}

//释放p所指结点
void FreeNode(Link &p){
    free(p);
    p = NULL;
}

//构造一个空的线性链表L
Status InitList(LinkList &L){
    //生成头结点
    Link p = (Link)malloc(sizeof(LNode));
    if (!p) {
        return ERROR;
    }
    p->data = NULL;
    p->next = NULL;
    L.header = L.tail = p;
    L.len = 0;
    return OK;
}

//清空线性链表L，并释放原链表的结点空间
Status ClearList(LinkList &L){
    //如果不是空表
    if (L.header!=L.tail) {
        Link p,q;
        //p，q均指向链表的第一个结点
        p = q = L.header->next;
        //将链表L的第一个结点置为空
        L.header->next = NULL;
        while (p!=L.tail) {
            q = p->next;
            free(p);
            p = q;
        }
        //释放最后一个结点
        free(L.tail);
        //头结点和尾结点均指向头结点
        L.tail = L.header;
        L.len = 0;
    }
    return OK;
}

//销毁线性链表L
Status DestoryList(LinkList &L){
    ClearList(L);
    FreeNode(L.header);
    L.tail = NULL;
    L.len = 0;
    return OK;
}

//已知h指向线性链表的头结点，将s所指结点插入在原第一个结点之前（即s成为第一个结点）
Status InsFirst(LinkList &L, Link s, Link h){
    //p指向原来的第一个节点
    Link p = h->next;
    h->next = s;
    s->next = p;
    if (h == L.tail) { //说明原链表为空表，头指针和尾指针均指向头结点；如果不相等，即使插入结点（只要不是插到链表尾部），也不需要移动尾指针
        L.tail = h->next;
    }
    L.len++;
    return OK;
}

//已知h指向线性链表的头结点，删除链表中的第一个结点并以q返回
Status DelFirst(LinkList &L, Link h, Link &q){
    q = h->next;
    //如果q存在，即链表非空
    if (q) {
        h->next = q->next;
        //即删除第一个结点之后判断表是否为空
        if (!h->next) {
            //如果表为空，修改尾指针
            L.tail = h;
        }
        L.len--;
        return OK;
    }else{
        return FALSE;
    }
}

//将指针s(s->data为第一个数据元素)所指(彼此以指针相链接，以NULL结尾)的一串结点链接在链表L的最后一个结点之后，并改变链表L的尾指针指向新的尾结点
Status Append(LinkList &L, Link s){
    Link p = s;
    int i = 1;
    //这段循环目的是为了找到s的最后一个结点
    while (p->next) {
        i++;
        p = p->next;
    }
    L.tail->next = s;
    //L的尾结点指向s的最后一个结点
    L.tail = p;
    L.len += i;
    return OK;
}

//已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置，若无前驱，则返回NULL
Position PriorPos(LinkList L, Link p){
    //如果p是链表L的第一个节点，无前驱
    if (p==L.header->next) {
        return NULL;
    }
    Link q = L.header->next;
    while (q->next) {
        if (q->next == p) {
            return q;
        }
        q = q->next;
    }
    return NULL;
}

//删除线性表L中的尾结点并以q返回，改变链表L的尾指针指向新的尾结点
Status Remove(LinkList &L, Link &q){
    //如果L为空表
    if (L.len == 0) {
        q = NULL;
        return FALSE;
    }
    //p指向L的第一个结点
    Link p = L.header->next;
    //for循环找到链表L尾结点的前一个结点
    while (p->next!=L.tail) {
        p = p->next;
    }
    q = L.tail;
    p->next = NULL;
    L.tail = p;
    L.len--;
    return OK;
}

//已知p指向线性链表L中的一个节点，将s所指节点插入在p所指节点之前，并修改指针p指向新插入的结点
Status InsBefore(LinkList &L, Link &p, Link s){
    //q是p节点的前驱
    Link q = PriorPos(L, p);
    //如果p节点没有前驱，则q指向链表L的头结点
    if (!q) {
        q = L.header;
    }
    //插入s节点
    q->next = s;
    s->next = p;
    p = s;
    L.len++;
    return OK;
}

//已知p指向线性链表L中的一个结点，将s所指结点插入在p所指节点之后，并修改指针p指向新插入的结点
Status InsAfter(LinkList &L, Link &p, Link s){
    s->next = p->next;
    p->next = s;
    if (p==L.tail) { //修改尾指针
        L.tail = s;
    }
    p = s;
    L.len++;
    return OK;
}

//已知p指向线性链表的一个结点，用e更新p指向结点的数据元素的值
Status SetCurElem(Link p, ElemType e){
    p->data = e;
    return OK;
}

//已知p指向线性链表的一个结点，返回结点的数据元素的值
ElemType GetCurElem(Link p){
    return p->data;
}

//若线性链表为空表返回True，否则返回False
Status ListEmpty(LinkList L){
    if (!L.len) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//返回线性链表的元素个数
int ListLength(LinkList L){
    return L.len;
}

//返回线性链表头结点的位置
Position GetHeader(LinkList L){
    return L.header;
}

//返回线性链表最后一个结点的位置
Position GetLast(LinkList L){
    return L.tail;
}

//已知p指向线性链表中的一个结点，返回p所指向结点的直接后继，若无直接后继，则返回NULL
Position NextPos(Link p){
    return p->next;
}

//用p返回线性链表L中第i个结点的位置，并返回OK，如果i值不合法则返回error
Status LocatePos(LinkList L, int i, Link &p){
    if (i<1 || i>ListLength(L)) {
        return ERROR;
    }
    Link q = L.header;
    int j = 0;
    while (j<i && q!=NULL) {
        j++;
        q = q->next;
    }
    if (j>i || j>ListLength(L)) {
        return ERROR;
    }
    p = q;
    return OK;
}

//返回线性链表L中第一个与e满足compare判定关系的结点的位置，若不存在这样的元素，则返回NULL
Position LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType e1, ElemType e2)){
    Link p = L.header->next;
    while (p!=NULL) {
        if (compare(p->data,e)) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

//依次对L中的每个调用数据元素调用visit函数。一旦visit失败，则操作失败
Status ListTraverse(LinkList L, void (*visit)(ElemType e)){
    Link p = L.header->next;
    while (p!=NULL) {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

//已知L为有序线性链表，将e元素按非降序插入在L中（用于一元多项式）
Status OrderInsert(LinkList &L, ElemType e, Status (*compare)(ElemType, ElemType)){
    Link p = L.header->next;
    Link q = L.header; //q用来表示p的前驱
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
        L.tail = s;
    }
    L.len++;
    return OK;
}

//若升序链表L中存在与e满足判定函数compare取值为0的元素，则p返回L中第一个值为e的结点的位置，并返回true；否则p指示第一个与e满足判定函数compare>0的元素的前驱的位置，并返回false（用于一元多项式）
Status LocatElem(LinkList L, ElemType e, Position &p, int(*compare)(ElemType, ElemType)){
//    Link q = L.header->next;
//    Link s = L.header;
//    while (!q) {
//        if (compare(q->data,e)==0) {
//            p = q;
//            return OK;
//        }else if (compare(q->data,e)>0){
//            p = s;
//            return FALSE;
//        }
//        s = q;
//        q = q->next;
//    }
    Link q = L.header;
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

