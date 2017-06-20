//
//  HString.cpp
//  DataStruct
//
//  Created by guyuexing on 2017/6/20.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "HString.hpp"

//生成一个其值等于串常量chars的串T
Status StrAssign(HString &T, char *chars){
    int i,j;
    if (T.ch) { //如果T.ch存在则先释放
        free(T.ch);
    }
    i = (int)strlen(chars);
    if (!i) { //如果chars长度为0
        T.ch = NULL;
        T.length = 0;
    }else{
        T.ch = (char *)malloc(sizeof(char)*i);
        if (!T.ch) {
            exit(OVERFLOWD);
        }
        for (j=0; j<i; j++) { //拷贝串
//            *(T.ch++) = *(chars++);  效果一样
            T.ch[i] = chars[i];
        }
        T.length = i;
    }
    return OK;
}

//由串S复制得串T
Status StrCopy(HString &T, HString S){
    if (T.ch) {
        free(T.ch);
    }
    int i = S.length;
    T.ch = (char *)malloc(sizeof(char)*i);
    if (!T.ch) {
        exit(OVERFLOWD);
    }
    for (int j=0; j<i; j++) {
        T.ch[j] = S.ch[j];
    }
    T.length = i;
    return OK;
}

//若T为空串则返回True，否则返回false
Status StrEmpty(HString T){
    return T.length == 0 && T.ch == NULL;
}

int StrLength(HString T){
    return T.length;
}

Status CleanString(HString &T){
    if (T.ch) {
        free(T.ch);
        T.ch = NULL;
    }
    T.length = 0;
    return OK;
}

//若串T>S，则返回值>0, 若串T=S，则返回值=0，若串T<S，则返回值<0
int StrCompare(HString T, HString S){
    for (int i=0; i<T.length&&i<S.length; i++) {
        if (T.ch[i]!=S.ch[i]) {
            return T.ch[i]-S.ch[i];
        }
    }
    return T.length-S.length;
}

//用T返回由S1和S2联结而成的新串
Status Concat(HString &T, HString S1, HString S2){
    if (T.ch) {
        free(T.ch);
    }
    int i = S1.length+S2.length;
    T.ch = (char *)malloc(sizeof(char)*i);
    if (!T.ch) {
        exit(OVERFLOW);
    }
    for (int j=0; j<S1.length; j++) {
        T.ch[j] = S1.ch[j];
    }
    int n = S1.length;
    for (int m=0; m<S2.length; m++) {
        T.ch[n+m] = S2.ch[m];
    }
    T.length = i;
    return OK;
}

//用sub返回串T的第pos个字符起长度为len的子串
Status SubString(HString &Sub, HString T, int pos, int len){
    //pos+len-2表示第pos个字符起长度为len的子串最后一个字符的序号
    //T.length-1表示串T的最后一个字符的序号
    if (pos<1 || pos-1+len-1>T.length-1 || pos>T.length || len<0) {
        return ERROR;
    }
    if (Sub.ch) { //释放旧的空间
        free(Sub.ch);
    }
    if (!len) { //空子串
        Sub.ch = NULL;
        Sub.length = 0;
    }else{
        Sub.ch = (char *)malloc(sizeof(char)*len);
        if (!Sub.ch) {
            exit(OVERFLOWD);
        }
        for (int i=0; i<len; i++) {
            Sub.ch[i] = T.ch[pos-1+i];
        }
        Sub.length = len;
    }
    return OK;
}

//在串T的第pos个字符之前插入串S
Status Insert(HString &T, int pos, HString S){
    if (pos<1 || pos>T.length+1) { //若pos=T.length+1表示将S插入T的末尾
        return ERROR;
    }
    if (S.length) {
        if (!(T.ch = (char *)malloc(sizeof(T.length+S.length)))) {
            exit(OVERFLOW);
        }
        for (int i=T.length-1; i>=pos-1; i--) {
            T.ch[i+S.length] = T.ch[i];
        }
        for (int j=0; j<S.length; j++) {
            T.ch[pos-1+j] = S.ch[j];
        }
        T.length += S.length;
    }
    return OK;
}

//若主串T中存在和串S值相同的子串，则返回它在主串T中第pos个字符之后第一次出现的位置，否则函数值为0
int Index(HString T, HString S, int pos){
    if (pos<1 || pos>T.length) {
        
    }
    return 0;
}



