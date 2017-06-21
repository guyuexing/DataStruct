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















