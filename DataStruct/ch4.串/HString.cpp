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
Status StrInsert(HString &T, int pos, HString S){
    if (pos<1 || pos>T.length+1) { //若pos=T.length+1表示将S插入T的末尾
        return ERROR;
    }
    if (S.length) {
        if (!(T.ch = (char *)realloc(T.ch,(T.length+S.length)*sizeof(char)))) {
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

//初始化字符串为空串
void InitString(HString &S){
    S.ch = NULL;
    S.length = 0;
}

//若主串T中存在和串S值相同的子串，则返回它在主串T中第pos个字符之后第一次出现的位置，否则函数值为0
int Index(HString T, HString S, int pos){
    if (pos<1 || pos>T.length) {
        return ERROR;
    }
    HString sub;
    InitString(sub);
    int n = T.length;
    int m = S.length;
    int i = pos;
    while (i<=n-m+1) { //i如果>n-m+1,取出的子串长度小于S的长度，不符条件
        SubString(sub, T, i, S.length);
        if (StrCompare(sub, S)==0) {
            return i;
        }else{
            i++;
        }
    }
    return 0;
}

Status DeleteString(HString &T, int pos, int len){
    if (pos<1||pos>T.length||len<0||pos+len-1>T.length) {
        return ERROR;
    }
    for (int i=pos+len-1; i<T.length; i++) {
        T.ch[i-len] = T.ch[i];
    }
    T.length -= len;
    T.ch = (char *)realloc(T.ch, sizeof(char)*T.length);
    return OK;
}

Status Replace(HString &T, HString S, HString V){
    if (StrEmpty(S)) {
        return ERROR;
    }
    int i = 1; //从T中的第一个字符开始查找S
    do {
        i = Index(T, S, i);
        if (i) {  //串T中存在子串S
            DeleteString(T, i, S.length);
            StrInsert(T, i, V);
            i += V.length; //从插入串V之后的位置开始查找串S
        }
    } while (i);
    return OK;
}

//堆分配类型的字符串无法销毁
void Destory(HString T){

}

void Print(HString T){
    for (int i=0; i<T.length; i++) {
        printf("%c\n",T.ch[i]);
    }
    printf("\n");
}

