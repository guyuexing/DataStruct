//
//  List.cpp
//  DataStruct
//
//  Created by guyuexing on 17/4/22.
//  Copyright © 2017年 neu. All rights reserved.
//

//线性表的动态分配顺序存储结构

#include "List.hpp"

#define LIST_INIT_SIZE 10  //线性表存储空间的初始分配量
#define LIST_INCREMENT 2   //线性表存储空间的分配增量
typedef int ElemType;

struct SqList {
    ElemType *elem;    //存储空间基址
    int length;     //当前长度
    int listSize;   //当前分配的存储容量 以sizeof(ElemType)为单位
};

Status InitList(SqList &L){
    //构造一个空的顺序线性表
    L.elem = (ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    if (!L.elem) {
        //分配存储空间失败
        exit(OVERFLOW);
    }
    L.length = 0;  //空表长度
    L.listSize = LIST_INIT_SIZE;  //初始存储容量
    return OK;
}

Status DestoryList(SqList &L){
    //销毁线性顺序表
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listSize = 0;
    return OK;
}

Status ClearList(SqList &L){
    //将L置为空表
    L.length = 0;
    return OK;
}

Status ListEmpty(SqList L){
    //如果L为空表返回true
    if (L.length == 0) {
        return TRUE;
    }else{
        return FALSE;
    }
}

int ListLength(SqList L){
    //返回表L中元素个数
    return L.length;
}

Status GetElem(SqList L, int i, ElemType &e){
    if (i<1 || i>L.length) {
        exit(OVERFLOW);
    }
    e = *(L.elem-1);
    //另一种写法：e = L.elem[i-1];
    return OK;
}
/**
 *  返回L中第1个与e满足关系compare()的数据元素的位序。若这样的数据元素不存在，则返回值为0
 *
 *  @param L       线性表
 *  @param e       要比较的值
 *  @param compare 函数指针compare作为参数,比较两元素，满足关系返回1，不满足返回0
 *
 *  @return 返回位序
 */
int LocateElem(SqList L, ElemType e, Status (*compare)(ElemType,ElemType)){
    //p的初值为L中第一个元素的位置
    ElemType *p = L.elem;
    int i = 1;
    while (i<=L.length && !compare(e,*(p++))) {
        ++i;
    }
    if (i<=L.length) {
        return i;
    }else{
        return 0;
    }
}

/**
 *  若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无定义
 *
 *  @param L     线性表
 *  @param cur_e L中的数据元素
 *  @param pre_e cur_e元素的前驱
 *
 *  @return 状态码，表示是否正确返回
 */
Status PriorElem(SqList L, int cur_e, ElemType &pre_e){
    //p指针指向L中的第二个元素地址
    ElemType *p = L.elem+1;
    //从第二个元素开始，因第一个元素没有前驱
    int i = 2;
    //p指向的元素不等于cur_e继续循环查找
    while(i<=L.length && *p!=cur_e) {
        i++;
        p++;
    }
    if (i>L.length) {
        return INFEASIBLE;
    }
    //p指向了与cur_e相等的元素，将此元素的前驱赋值给pre_e
    pre_e = *(--p);
    return OK;
}

/**
 *  若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继，否则操作失败，next_e无定义
 *
 *  @param L      线性表
 *  @param cur_e  L中的元素
 *  @param next_e cure_e的后继元素
 *
 *  @return 状态码，表示是否正确返回
 */
Status NextElem(SqList L, int cur_e, ElemType &next_e){
    int i = 1;
    ElemType *p = L.elem;
    while (i<L.length && *p!=cur_e) {
        i++;
        p++;
    }
    //如果位序等于或大于L的长度，返回错误，L=length时没有后继元素
    if (i>=L.length) {
        return INFEASIBLE;
    }else{
        next_e = *++p;
        return OK;
    }
}

/**
 *  在L中第i个位置之前插入新的数据元素e，L的长度加1
 *
 *  @param L 线性表L
 *  @param i 要插入元素的位置
 *  @param e 要插入的元素
 *
 *  @return 操作结果状态码
 */
Status ListInsert(SqList &L, int i, int e){
    //输入的位置不合法
    if (i<1 || i>L.length+1) {
        return ERROR;
    }
    ElemType *newBase, *p, *q;
    if (L.length >= L.listSize) {
        //当前存储空间已满，需要增加分配
        newBase = (ElemType *)realloc(L.elem, sizeof(ElemType)*(L.listSize + LIST_INCREMENT));
        if (!newBase) {
            //存储分配失败
            exit(OVERFLOW);
        }else{
            //新基址
            L.elem = newBase;
            //线性表的长度增加
            L.listSize += LIST_INCREMENT;
        }
    }
    //找到要插入元素的地址
    q = L.elem+i-1;
    //从后往前，每个元素均向后移动一个位置，直到移动到要插入元素的位置
    for (p=L.elem+L.length-1; p>=q; p--) {
        *(p+1) = *p;
    }
    //要插入的地址赋值元素值
    *q = e;
    //线性表的长度增加
    L.length++;
    return OK;
}

/**
 *  删除L的第i个数据元素，并用e返回其值，L的长度减1
 *
 *  @param L 线性表L
 *  @param i 要删除元素的位序
 *  @param e 要删除的元素值
 *
 *  @return 结果状态码
 */
Status ListDelete(SqList &L, int i, ElemType &e){
    //i的值输入不合法
    if (i<1 || i>L.length) {
        exit(OVERFLOW);
    }
    //要删除元素的位置
    ElemType *q = L.elem+i-1;
    //要删除的元素
    e = *q;
    //删除元素后面的元素位置均要前移
    ElemType *p = L.elem + L.length - 1;
    while (p>q) {
        *(p-1) = *p;
        p--;
    }
    //线性表的长度减一
    L.length--;
    return OK;
}

/**
 *  依次对L的每个数据元素调用函数visit()。一旦visit()失败，则操作失败.visit()的形参加'&'，表明可通过调用visit()改变元素的值
 *
 *  @param L     线性表
 *  @param visit visit函数指针
 *
 *  @return 操作结果状态码
 */
Status ListTraverse(SqList L, void (*visit)(ElemType &)){
    ElemType *p = L.elem;
    for (int i = 1;i<=L.length; i++) {
        visit(*p++);
        std::cout << std::endl;
    }
    return OK;
}
