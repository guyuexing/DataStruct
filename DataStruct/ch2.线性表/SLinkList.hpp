//
//  SLinkList.hpp
//  DataStruct
//
//  Created by guyuexing on 17/5/3.
//  Copyright © 2017年 neu. All rights reserved.
//
#include "PublicHeader.h"

//线性表的静态单链表存储结构
#define MAXSIZE 100
//typedef int ElemType;

typedef struct {
    ElemType data;
    int cur;
} component, SLinkList[MAXSIZE];

typedef int IntArray[MAXSIZE];
/*
 （1）
 typedef struct{
    ElemType data;
    int cur;
 }component, SLinkList[MAXSIZE];
 
 实际上将SLinkList定义为struct{ElemType data;int cur;}[MAXSIZE]这一数组类
 型，举个例子：
    SLinkList array;
 实际上是定义了一个数组array，这个数组array包含MAXSIZE个元素，每个元素都是一个struct{ElemType data;int cur;}
 类型的变量
 
 即上述定义实际上等价于struct{ElemType data;int cur;} array[MAXSIZE];
 
 （2）所以函数void InitSpace_SL(SLinkList &space)的参数实际上是一个数组的引用，这个数组必须是形如component array[MAXSIZE]中的array一样；
 而函数Status InitList(SLinkList space)的参数实际上是一个component类型的指针，在这一点上，类似于void fun(int a[])等价于void fun(int* a)。
 
 实际上，编译器编译时会将两者变换成如下形式：
 
 void InitSpace_SL(SLinkList &space) => void InitSpace_SL(component (&)[MAXSIZE]);
 
 Status InitList(SLinkList space)    => Status InitList(component* a);
 
 这一点上，lz可以在两个函数里使用printf("sizeof(space) = %d\n", sizeof(space));进行验证，打印的结果前者应该是MAXSIZE*sizeof(component)，后者应该是sizeof(int*)
 
 （3）两种方式能达到相同的效果，说起来与我们调用函数对数组进行操作类似，例如我们定义一个函数void fun(int a[MAXSIZE])，调用时我们将数组名作为实参，但是函数接收的形参只是一个指针，只不过这个指针指向实参数组的起始位置
 */

//定义了component这种数据类型，定义了元素是这种结构体的数组
//数组的一个分量表示一个节点，同时用游标(cur)代替指针指示结点在数组中的相对位置
//数组的第零分量可看成头结点，其指针域指示链表的第一个结点
//这种存储结构仍然需要预先分配一个较大的空间，但在做线性表的插入和删除操作时不需移动元素，仅需修改指针，仍具有链式存储结构的主要优点

int Malloc(SLinkList space);

void Free(SLinkList space, int i);

void InitList(SLinkList L);

Status ClearList(SLinkList L);

Status ListEmpty(SLinkList L);

int ListLength(SLinkList L);

Status GetElem(SLinkList L, int i, ElemType &elem);

int LocateElem(SLinkList L, ElemType elem);

Status priorElem(SLinkList L, ElemType cur, ElemType &prior);

Status nextElem(SLinkList L, ElemType cur, ElemType &next);

Status ListInsert(SLinkList L, ElemType elem, int i);

Status ListDelete(SLinkList L, int i, ElemType &elem);

Status ListTraverse(SLinkList L, void (*visit)(ElemType elem));
