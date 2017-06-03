//
//  LinkList.cpp
//  DataStruct
//
//  Created by guyuexing on 17/4/27.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "LinkList.hpp"

//构造一个空的线性链表L
Status InitLinkList(LinkList &L){
    //产生头结点，并使L指向头结点
    L = (LinkList)malloc(sizeof(LNode));
    //如果头结点为空，返回错误
    if (L==NULL) {
        exit(OVERFLOWD);
    }
    //头结点指针域为空
    L -> next = NULL;
    return OK;
}

//销毁线性表L
Status DestoryLinkList(LinkList &L){
    LinkList p;
    //如果L不为空
    while (L) {
        //设置p为L指向的下一个结点
        p = L->next;
        //释放L
        free(L);
        //将p赋值给L，继续下一个循环
        L = p;
    }
    return OK;
}

//将线性表L清空
Status ClearLinkList(LinkList L){
    LinkList p,q;
    //p为L指向的下一个结点
    p = L->next;
    //如果p存在，继续循环
    while (p) {
        //将p指向的下一个结点赋值给q
        q = p->next;
        //释放p指向的结点
        free(p);
        //将q赋值给p，继续下一个循环
        p = q;
    }
    L->next = NULL;
    return OK;
}

//判断线性表是否为空
Status ListEmpety(LinkList L){
    //如果L（头结点）指向的下一个元素为空，返回True，否则返回False
    if (!L->next) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//求线性表的长度
int ListLength(LinkList L){
    //定义i标记线性表长度
    int i = 0;
    //定义q为L头结点指向的下一个结点
    LinkList q = L->next;
    //如果q存在不为空，继续循环计数
    while (q) {
        //q赋值为q指向的下一个结点
        i++;
        q = q->next;
    }
    return i;
}

//当线性表中第i个元素存在时，将此元素赋值给e并返回OK，否则返回error
//算法的时间复杂度为O(n)
Status GetElem(LinkList L, int i, ElemType &e){
    //定义计数器表示是否找到了i位置
    int j = 1;
    //定义p指针为L头结点指向的下一个结点
    LinkList p = L->next;
    //如果p不为空并且还没有找到第i个元素，继续循环
    while (p&&j<i) {
        //计数器加1，并将p指针指向下一个元素位置
        j++;
        p = p->next;
    }
    //如果p指针为空说明线性表中不存在第i个元素，返回错误
    if (j>i||!p) {
        return ERROR;
    }
    //否则将p位置对应的数据赋值给e
    e = p->data;
    return OK;
}

//返回线性表L中第一个与元素e相等的结点位序
//compare为比较两个元素是否相等的函数，若相等返回1，否则返回0
int LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType e1, ElemType e2)){
    //标记是第几个结点中的数据与e相等
    int i = 0;
    //定义p为头结点指向的第一个结点
    LinkList p = L->next;
    //如果p存在一直循环查找
    while (p) {
        //i表明当前的p指向的是第几个结点
        i++;
        //比较p指向的结点的数据是否与e相等，如果相等则直接返回此时p指向结点的位序
        if (compare(e,p->data)) {
            return i;
        //否则将p置为当前p指向的下一个结点，继续比较
        }else{
            p = p->next;
        }
    }
    //如果遍历了整个线性表还没有找到与e相等的元素，返回0
    return 0;
}

//若cur_e是线性表L的元素且不是第一个，用pre_e返回cur_e的前驱，函数状态码为OK；否则pre_e无定义，且函数状态为INFEASIBLE
Status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e){
    //定义p为线性表的第一个元素
    LinkList p = L->next;
    LinkList q;
    //如果p有后继元素
    while (p->next) {
        //用q指向p的后继元素
        q = p->next;
        //如果p的后继元素值等于cur_e
        if (q->data == cur_e) {
            //给pre_e赋值为p的元素值
            pre_e = p->data;
            return OK;
        }
        //将p的后继q重新赋值给p
        p = q;
    }
    return INFEASIBLE;
}

//如果cur_e是线性表L的元素且不是最后一个，用next_e返回cur_e的后继元素，函数的状态码为OK；否则next_e无定义，函数状态码为INFEASIBLE
Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e){
    //定义p为L的第一个元素
    LinkList p = L->next;
    //如果p有后继元素
    while (p->next) {
        //如果p的元素值等于cur_e
        if (p->data == cur_e) {
            //将p的后继元素值赋值给next_e
            next_e = p->next->data;
            return OK;
        }
        //将p的后继重新赋值给p
        p = p->next;
    }
    return INFEASIBLE;
}

//向线性表L的第i个位置插入元素e
//算法的时间复杂度为O(n)
Status ListInsert(LinkList L, int i, ElemType e){
    //将线性表的头结点位置赋值给p
    LinkList p = L;
    //定义j为p结点在表L中的位序
    int j = 0;
    //找到表L中的第i-1个结点
    while (j<i-1&&p) {
        j++;
        p = p->next;
    }
    
    //如果i小于1或者i大于表长（即p为空）
    if (!p||j>i-1) {
        return ERROR;
    }
    //生成一个新节点
    LinkList q = (LinkList)malloc(sizeof(LNode));
    //新节点的元素值为e
    q->data = e;
    //新节点的后继为p的后继（位序为i）的后继（位序为i+1）
    q->next = p->next->next;
    //p的后继为q
    p->next = q;
    return OK;
}

//删除表L中的第i个元素，并用e返回删除的元素值
//算法的时间复杂度为O(n)
Status DeleteList(LinkList L, int i, ElemType &e){
    //定义p指向线性表L的头结点
    LinkList p = L;
    //定义j为p结点的位序
    int j = 0;
    //找到线性表的第i-1个结点，并且第i个结点不为空
    while (j<i-1 && p->next) {
        j++;
        p = p->next;
    }
    //如果i小于1或者i大于表长（即p->next为空）
    if (j>i-1 || !p->next) {
        return ERROR;
    }
    //定义q为p的后继
    LinkList q = p->next;
    e = q->data;
    //p的后继（即位序i-1的元素的后继）为p的后继的后继（即位序为i+1的元素）
    p->next = p->next->next;
    //释放位序为i的元素存储空间
    free(q);
    return OK;
}

//对线性表L中的每一个元素都执行vi函数，一旦vi失败，则操作失败
Status ListTraverse(LinkList L, void(*vi)(ElemType e)){
    LinkList p = L->next;
    while (p) {
        vi(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}
