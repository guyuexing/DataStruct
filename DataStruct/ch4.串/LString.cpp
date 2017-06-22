//
//  LString.cpp
//  DataStruct
//
//  Created by guyuexing on 2017/6/21.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "LString.hpp"

#define Blank '#'

//初始化字符串T（产生空串）
void InitString(LString &T){
    T.curLen = 0;
    T.head = T.tail = NULL;
}

// 生成一个其值等于chars的串T(要求chars中不包含填补空余的字符)
// 成功返回OK，否则返回ERROR
Status StrAssign(LString &T, char *chars){
    int i = (int)strlen(chars);
    if (!i||strchr(chars, Blank)) { //strchr函数的作用是查找在字符串chars中首次出现_CTYPE_B字符的位置
        //此if条件是说当chars为空或chars中包含T要填补空余的字符则直接返回错误
        return ERROR;
    }
    T.curLen = i;
    int j = i/CHUNKSIZE;  //j为块链的节点数
    if (i%CHUNKSIZE) {
        j++;   //如果i不是块大小的整数倍，则j++
    }
    Chunk *p, *q = nullptr;
    for (int k=0; k<j; k++) {  //遍历每一个链块
        p = (Chunk *)malloc(sizeof(Chunk));
        if (!p) {
            return ERROR;
        }
        if (k==0) { //如果是第一个链块
            T.head = q = p;
        }else{
            q->next = p;
            q = p;
        }
        int m= 0;
        for (; m<CHUNKSIZE&&(*chars); m++) { //给链块赋值
            *(p->ch+m) = *(chars++);
        }
        if (!*chars) { //如果是最后一个链块，给空余的位置填补占位字符
            T.tail = p;
            for (; m<CHUNKSIZE; m++) {  //m是上一个for循环结束后的第一个空余位置出现的位序
                *(p->ch+m) = Blank;
            }
        }
    }
    return OK;
}

// 初始条件:串S存在。操作结果:由串S复制得串T(连填补空余的字符一块拷贝)
Status StrCopy(LString &T, LString S){
    Chunk *p;
    Chunk *q;
    Chunk *h = S.head;
    if (h) {
        T.curLen = S.curLen;
        p = T.head = (Chunk *)malloc(sizeof(Chunk));
        *p = *h; //给第一个块链赋值
        h = h->next;
        while (h) {
            q = p;
            p = (Chunk *)malloc(sizeof(Chunk));
            q->next = p;
            *p = *h;
            h = h->next;
        }
        p->next = NULL;
        T.tail = p;
        return OK;
    }else{
        return ERROR;
    }
}

Status StrEmpty(LString T){
    return T.curLen == 0;
}

// 若T>S,则返回值>0;若T=S,则返回值=0;若T<S,则返回值<0
int StrCompare(LString T, LString S){
    int i = 0;
    int jt = 0;
    int js = 0;
    Chunk *pt = T.head;
    Chunk *ps = S.head;
    while (i<T.curLen&&i<S.curLen) {
        i++;  //i为当前待比较的字符在T和S串中的位置
        while (*(pt->ch+jt) == Blank) { //比较的时候跳过填补空余的字符
            jt++;
            if (jt==CHUNKSIZE) {
                pt = pt->next;
                jt = 0;
            }
        }
        while (*(ps->ch+js) == Blank) { //比较的是否跳过填补空余的字符
            js++;
            if (js==CHUNKSIZE) {
                ps = ps->next;
                js = 0;
            }
        }
        if (*(ps->ch+js)!=*(pt->ch+jt)) { //比较字符
            return *(pt->ch+jt) - *(ps->ch+js); //如果比较的两字符不相等，直接返回差值
        }else{
            jt++;
            if (jt==CHUNKSIZE) { //取后一个字符时如果此链块结束了，则取下一个链块的字符进行比较
                pt = pt->next;
                jt = 0;
            }
            js++;
            if (js==CHUNKSIZE) {
                ps = ps->next;
                js = 0;
            }
        }
    }
    return T.curLen - S.curLen;
}

int StrLength(LString T){
    return T.curLen;
}

//将T清空为空串
Status CleanStr(LString &T){
    Chunk *p, *q;
    p = T.head;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    T.head = T.tail = NULL;
    T.curLen = 0;
    return OK;
}

Status Concat(LString &T, LString S1, LString S2){
    LString t1, t2; //创建t1、t2结构体
    InitString(t1); //初始化为空串
    InitString(t2);
    StrCopy(t1, S1); //赋值S1串到t1中
    StrCopy(t2, S2);
    t1.tail->next = t2.head;
    T.head = t1.head;
    T.tail = t2.tail;
    T.curLen = t1.curLen+t2.curLen;
    return OK;
}

//用Sub返回T串第pos个字符起长度为len的子串，这里的子串不包括填充字符
Status SubString(LString &Sub, LString T, int pos, int len){
    if (pos<1||pos>T.curLen||len<0||pos+len-1>T.curLen) {
        return ERROR;
    }
    Chunk *p, *q;
    //接下来生成空的Sub串
    int n = len/CHUNKSIZE;
    if (len%CHUNKSIZE) {
        n++;
    }
    p = new Chunk;
    Sub.head = p;
    for (int i=1; i<n; i++) {
        q = new Chunk;
        p->next = q;
        p = q;
    }
    p->next = NULL;
    Sub.tail = p;
    Sub.curLen = len;
    //填充Sub尾部空余的空间
    for (int i=len%CHUNKSIZE; i<CHUNKSIZE; i++) {
        //此时p是指向Sub串的尾部
        *(p->ch+i) = Blank;
    }
    //以上是完成Sub的初始化相关工作，也填充了空余的空间
    
    q = Sub.head; //q指向Sub即将复制的块
    p = T.head;   //p指向T的当前被复制给Sub的块
    int i = 0; //i表示即将复制的字符在Sub块中的位置
    int m = 0; //m表示将要被复制的字符在T块中的序号（不同于位置）
    /*
        串：      11 22 15 14  # 51 26  # 37 38
        位置：     0  1  2  3  4  5  6  7  8  9
        序号：     1  2  3  4     5  6     7  8
     */
    int flag = 1;
    while (flag) {
        for (int k=0; k<CHUNKSIZE; k++) { //k只是当前被复制的字符在串T中的位置
            if (*(p->ch+k)!=Blank) {  //只有不是占位字符才会被复制
                m++;  //m表示当前被复制的字符在T中的序号
                if (m>=pos&&m<=pos+len-1) { //满足条件开始复制
                    if (i==CHUNKSIZE) {
                        q = q->next;
                        i = 0;
                    }
                    *(q->ch+i) = *(p->ch+k);
                    i++;
                    if (m==pos+len-1) {
                        flag = 0; //结束复制
                        break;
                    }
                }
            }
        }
        p = p->next;  //遍历完了一个块链，遍历下一个
    }
    return OK;
}

//压缩串(清除块中不必要的填补空余的字符)
void Zip(LString &T){
    //生成字符串p
    char *p = (char *)malloc(sizeof(char)*(T.curLen+1));
    Chunk *h = T.head;
    int j = 0;
    while (h) { //将串T中的非空字符提取出来复制到字符串p中
        for (int i=0; i<CHUNKSIZE; i++) {
            if (*(h->ch+i)!=Blank) {
                *(p+j) = *(h->ch+i);
                j++;
            }
        }
        h = h->next;
    }
    *(p+j) = '\0';  //串结束符
    CleanStr(T);    //清空串T
    StrAssign(T, p);//重新生成串T
}







