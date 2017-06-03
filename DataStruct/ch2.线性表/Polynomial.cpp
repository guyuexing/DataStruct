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
        return (a.expn-b.expn)/abs(a.expn-b.expn);  //abs是取绝对值
    }
}

//分配由p指向的值为e的结点，并返回OK，若分配失败，则返回error
Status MakeNode(Link &p, PolyElemType e){
    p = (Link)malloc(sizeof(PolynNode));
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

//构造一个空的线性链表P
Status InitPolyn(Polynomial &P){
    //生成头结点
    Link p = (Link)malloc(sizeof(PolynNode));
    if (!p) {
        return ERROR;
    }
    p->next = NULL;
    P.header = P.tail = p;
    P.len = 0;
    return OK;
}

//清空线性链表L，并释放原链表的结点空间
Status ClearPolyn(Polynomial &P){
    //如果不是空表
    if (P.header!=P.tail) {
        Link p,q;
        //p，q均指向链表的第一个结点
        p = q = P.header->next;
        //将链表L的第一个结点置为空
        P.header->next = NULL;
        while (p!=P.tail) {
            q = p->next;
            free(p);
            p = q;
        }
        //释放最后一个结点
        free(P.tail);
        //头结点和尾结点均指向头结点
        P.tail = P.header;
        P.len = 0;
    }
    return OK;
}

//销毁线性链表L
Status DestoryPolyn(Polynomial &P){
    ClearPolyn(P);
    FreeNode(P.header);
    P.tail = NULL;
    P.len = 0;
    return OK;
}


//返回线性链表头结点的位置
Position GetHeader(Polynomial P){
    return P.header;
}

//若线性链表为空表返回True，否则返回False
Status ListEmpty(Polynomial P){
    if (!P.len) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//返回线性链表的元素个数
int PolynLength(Polynomial P){
    return P.len;
}

//已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置，若无前驱，则返回NULL
Position PriorPos(Polynomial P, Link p){
    //如果p是链表L的第一个节点，无前驱
    if (p==P.header->next) {
        return NULL;
    }
    Link q = P.header->next;
    while (q->next) {
        if (q->next == p) {
            return q;
        }
        q = q->next;
    }
    return NULL;
}

//已知p指向线性链表中的一个结点，返回p所指向结点的直接后继，若无直接后继，则返回NULL
Position NextPos(Link p){
    return p->next;
}

//已知h指向线性链表的头结点，将s所指结点插入在原第一个结点之前（即s成为第一个结点）
//也可以认为是将s所指节点插入作为h节点的后继元素
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

//已知h指向线性链表的头结点，删除链表中的第一个结点并以q返回
//也可以认为是删除h所指节点的后继元素
Status DelFirst(Polynomial &P, Link h, Link &q){
    q = h->next;
    //如果q存在，即链表非空
    if (q) {
        h->next = q->next;
        //即删除第一个结点之后判断表是否为空
        if (!h->next) {
            //如果表为空，修改尾指针
            P.tail = h;
        }
        P.len--;
        return OK;
    }else{
        return FALSE;
    }
}

//已知p指向线性链表的一个结点，返回结点的数据元素的值
PolyElemType GetCurElem(Link p){
    return p->data;
}

//将指针s(s->data为第一个数据元素)所指(彼此以指针相链接，以NULL结尾)的一串结点链接在链表L的最后一个结点之后，并改变链表L的尾指针指向新的尾结点
Status Append(Polynomial &P, Link s){
    Link p = s;
    int i = 1;
    //这段循环目的是为了找到s的最后一个结点
    while (p->next) {
        i++;
        p = p->next;
    }
    P.tail->next = s;
    //L的尾结点指向s的最后一个结点
    P.tail = p;
    P.len += i;
    return OK;
}


//找到第一个与e满足compare函数关系的结点
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
        if (compare(p->data,e)>=0){
            break;
        }
        q = p;
        p = p->next;
    }
    Link s = (Link)malloc(sizeof(PolynNode));
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

//输入m项的系数和指数，建立一元多项式的有序线性链表P
void creatPolyn(Polynomial &P, int m){
    Position q, s;
    Term t;
    InitPolyn(P);
    printf("请输入%d个指数、系数：\n",m);
    for (int i=1; i<=m; i++) {
        scanf("%d,%f",&t.expn,&t.coef);
        if (!LocatElem(P, t, q, compare)) { //q用来接收与t的指数项相等的结点位置或者第一个与t满足判定函数compare>0元素的前驱位置
            //当前链表中不存在t的指数项，生成新的结点并插入链表
            if (MakeNode(s, t)) {  //生成新的节点s
                InsFirst(P, s, q);  //将节点s插入作为q节点的后继元素
            }
        }
    }
}

//打印输出一元多项式P
void PrintPolyn(Polynomial P){
    Link q = P.header->next;
    for (int i=0; i<=P.len; i++) {
        printf("指数：%d，系数：%f\n",q->data.expn,q->data.coef);
        q = q->next;
    }
}

//多项式加法：Pa = Pa+Pb，并销毁一元多项式Pb
void AddPolyn(Polynomial &Pa, Polynomial &Pb){
    Position ha,hb,pa,pb;
    Term a,b; //用a和b表示链表中的数据元素（是结构体）
    ha = GetHeader(Pa); //ha表示Pa的头结点
    hb = GetHeader(Pb); //hb表示Pb的头结点
    pa = NextPos(ha);   //pa表示Pa的第一个结点
    pb = NextPos(hb);   //pb表示Pb的第一个结点
    while (PolynLength(Pa)&&PolynLength(Pb)&&pa) {
        a = GetCurElem(pa);
        b = GetCurElem(pb);
        switch (compare(a, b)) {
            case -1:   //多项式中Pa当前结点的指数值比Pb的小
                ha = pa;
                pa = NextPos(pa);
                break;
             case 0:   //多项式中Pa当前结点的指数值与Pb相等
                pa->data.coef += pb->data.coef;
                //如果Pa中当前元素系数相加后为0，则删除此元素
                if (pa->data.coef == 0) {
                    DelFirst(Pa, ha, pa); //删除链表Pa中ha的后继元素，并用pa返回删除的元素
                    FreeNode(pa);
                }else{
                    ha = pa;   //若系数不为0，将ha向后移动一位
                }
                pa = NextPos(ha); //无论删除元素与否，pa均为ha的后继元素
                DelFirst(Pb, hb, pb); //删除Pb中pb指向的元素
                FreeNode(pb);  //释放pb指向的空间
                pb = NextPos(hb);  //pb指向hb的后继元素
                break;
            case 1:    //多项式中Pa当前结点的指数值比pb的大
                DelFirst(Pb, hb, pb);  //删除Pb中hb的后继元素(即现在的pb)，并用pb返回删除的元素
                InsFirst(Pa, pb, ha);  //向Pa中插入pb元素，插入位置为ha的后继，原ha的后继pa保持不变
                ha = ha->next; //再将ha向后移动一个位置，ha的后继就又变为pa了
                pb = NextPos(hb); //移动pb位置为hb的后继
                break;
            default:
                break;
        }
    }
    if (PolynLength(Pb)) {
        Pb.tail = hb;
        Append(Pa, pb); //连接Pb中的剩余结点
    }
    DestoryPolyn(Pb);  //销毁Pb
}

//按有序判定函数compare的约定，将值为e的节点插入或合并到升序链表P的适当位置
Status OrderInsertMerge(Polynomial &P, PolyElemType e, int(compare)(PolyElemType,PolyElemType)){
    Position p,q;
    if (LocatElem(P, e, p, compare)) {  //在P中找到与e的指数相等的节点
        p->data.coef+=e.coef;   //计算指数相等的节点合并后系数是否为0
        if (!p->data.coef) { //如果为0
            q = PriorPos(P, p);  //获取p指向节点的前驱
            if (!q) {
                q = P.header;   //说明p没有前驱，q指向P的头结点
            }
            DelFirst(P, q, p);  //删除q节点的后继(即p指向的节点)，并用p进行接收删除的节点
            FreeNode(p);
        }
        return OK;
    }else{  //没有找到与e指数相等的节点，但是用p返回了第一个与e符合compare>0节点的前驱
        if (MakeNode(q, e)) {  //用e值生成一个新节点，并用q指向这个新节点
            InsFirst(P, q, p); //将q指向的节点插入链表并作为p的后继元素
            return OK;
        }else{
            return ERROR;  //生成节点失败
        }
    }
}

//另一种多项式加法
void AddPolyn1(Polynomial &Pa, Polynomial &Pb){
    Position p = GetHeader(Pb)->next;  //p指向Pb的第一个节点
    Term t;
    while (p) {
        t = GetCurElem(p);
        OrderInsertMerge(Pa, t, compare);
        p = p->next;
    }
    DestoryPolyn(Pb);
}

//一元多项式系数取反
void Opposite(Polynomial P){
    Position p = P.header->next;
    while (p) {
        p->data.coef *= -1;
        p = NextPos(p);
    }
}

//多项式减法，Pa = Pa-Pb，并销毁Pb
void SubtractPolyn(Polynomial &Pa, Polynomial &Pb){
    Opposite(Pb);
    AddPolyn(Pa, Pb);
}

//多项式乘法，Pa=Pa*Pb，并销毁Pb
void MultiplyPolyn(Polynomial &Pa, Polynomial &Pb){
    //多项式乘法需要借助第三个链表
    Polynomial Pc;
    InitPolyn(Pc);
    Position pa = NextPos(GetHeader(Pa));
    Position pb;
    Term a,b,c;
    while (pa) {
        //每完成对Pb的一次循环遍历，需要将pb置于原位(即Pb的第一个节点处)
        pb = NextPos(GetHeader(Pb));
        //取出当前pa指向节点的数据元素
        a = GetCurElem(pa);
        while (pb) {
            //取出当前pb指向节点的数据元素
            b = GetCurElem(pb);
            c.coef = a.coef*b.coef;
            c.expn = a.expn+b.expn;
            //将c数据元素按照compare的函数关系插入到Pc中
            OrderInsertMerge(Pc, c, compare);
            pb = pb->next;
        }
        pa = pa->next;
    }
    DestoryPolyn(Pb);  //销毁Pb
    ClearPolyn(Pa);   //清空Pa
    Pa.header = Pc.header;
    Pa.tail = Pc.tail;
    Pa.len = Pc.len;
    //函数运行结束，Pc局部变量会自动销毁，但是Pc中的节点由Pa指向了因此不会销毁
}
