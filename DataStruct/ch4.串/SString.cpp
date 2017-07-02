//
//  SString.cpp
//  DataStruct
//
//  Created by haozhu on 2017/6/10.
//  Copyright © 2017年 neu. All rights reserved.
//

//串采用定长顺序存储结构
//SString是数组类型，故不需引用类型

#include "SString.hpp"

//生成一个其值等于chars的串T
Status StrAssign(SString T, char *chars){
    if (strlen(chars)>MAXSTRLEN) { //要保存的串超过了T的长度
        return ERROR;
    }else{
        T[0] = strlen(chars);  //串T的第一个位置保存字符串的长度
        for (int i=1; i<=T[0]; i++) {
            T[i] = *(chars+i-1);
        }
        return OK;
    }
}

//由串S复制得串T
Status StrCopy(SString T, SString S){
    for (int i=0; i<=S[0]; i++) {
        T[i] = S[i];
    }
    return OK;
}

//若串为空串则返回True，否则返回False
Status StrEmpty(SString T){
    if (T[0]) {
        return FALSE;
    }else{
        return TRUE;
    }
}

//返回串T的长度
int StrLength(SString T){
    return T[0];
}

//若串T,S存在，若T>S, 返回值>0，T=S,返回值=0，T<S，返回值<0
int StrCompare(SString T, SString S){
    for (int i=1; i<=T[0]&&i<=S[0]; i++) {
        if (T[i]!=S[i]) {
            return T[i]-S[i];
        }
    }
    return T[0]-S[0];
}

//将S清为空串
Status CleanStr(SString T){
    T[0] = 0; //令串长等于0
    return OK;
}

//用T返回由S1和S2联结而成的新串，若未截断，返回True，否则返回False
Status Concat(SString T, SString S1, SString S2){
    if (S1[0]+S2[0]<=MAXSTRLEN) { //字符串未截断
        T[0] = S1[0]+S2[0];
        for (int i=1; i<=S1[0]; i++) {
            T[i] = S1[i];
        }
        for (int i=1; i<=S2[0]; i++) {
            T[S1[0]+i] = S2[i];
        }
        return OK;
    }else{  //字符串截断
        T[0] = MAXSTRLEN;
        for (int i=1; i<=S1[0]&&i<=MAXSTRLEN; i++) {
            T[i] = S1[i];
        }
        for (int i=1; i<=MAXSTRLEN-S1[0]; i++) {
            T[S1[0]+i] = S2[i];  //进入了这个循环说明MAXSTRLEN-S1[0]>=1
        }
        return FALSE;
    }
}

//用sub串返回串T的第pos个字符起长度为len的子串
Status SubString(SString T, SString sub, int pos, int len){
    
    if (pos<1||pos>T[0]||len<0||pos+len-1>T[0]) {
        return ERROR;
    }
    for (int i=1; i<=len; i++) {
        sub[i] = T[pos+i-1];
    }
    sub[0] = len;
    return OK;
    
    //我的写法
    int to;
    if (pos+len-1>MAXSTRLEN) {
        to = MAXSTRLEN;
    }else{
        to = pos+len-1;
    }
    for (int i=pos,j=1; i<=to&&j<=MAXSTRLEN; i++,j++) {
        sub[j] = T[i];
    }
    return OK;
}

//若主串T中第pos个字符之后存在与S相等的子串，则返回第一个这样的子串在T中的位置，否则返回0
//算法4.1
int Index4_1(SString T, SString S, int pos){
    int i = pos;
    if (pos>0) {
        while (i<=T[0]-S[0]+1) { //i如果超过了此范围那么截取的字符串长度与S不等
            SString sub; //sub用来接收截取的字符串
            SubString(T, sub, i, S[0]);
            if (StrCompare(sub, S)==0) {
                return i;
            }else{
                i++;
            }
        }
    }
    return 0;
}

//T串为主串，S串为模式串，返回子串S在主串T中第pos个字符之后的位置，如不存在，则函数值为0，此算法的时间复杂度为O(m+n)，最坏的情况下是O(m*n)
int Index4_5(SString T, SString S, int pos){
    int i = pos; //i表示当前T中比较的字符的位序
    int j = 1;   //j表示当前S中比较的字符的位序
    if (pos) {
        while (i<=T[0]&&j<=S[0]) {
            if (T[i]==S[j]) {
                i++;
                j++;
            }else{
                j = 1;
                i = i-j+2; //i=i-(j-1)+1  j-1表示匹配上的字符数；i-(j-1)表示i退回到比较之前的位序；+1表示i移动到比较之前的下一个位置
            }
        }
        if (j>S[0]) { //j>S[0]表明S[0]中的字符均比较完，即匹配上了
            return i-S[0]; //i表示匹配上的最后一个字符的下一个字符位序，i-S[0]是模式的第一个字符在串T中的位序
        }
    }
    return 0;
}

//在串T的第pos个字符之前插入串S
Status StrInsert(SString T, int pos, SString S){
    if (pos<1 || pos>T[0]+1) {
        return ERROR;
    }
    if (T[0]+S[0]<=MAXSTRLEN) { //完全插入
        for (int i=T[0]; i>=pos; i--) {
            T[i+S[0]] = T[i]; //移动插入位置之后的字符腾出空间
        }
        for (int j=pos; j<S[0]+pos; j++) {
            T[j] = S[j-pos+1];
        }
        T[0] += S[0];
    }else{ //部分插入,不理解
        for (int i=MAXSTRLEN; i>=pos; i--) {
            T[i] = T[i-S[0]];
        }
        for (int j=pos; j<pos+S[0]; j++) {
            T[j] = S[j-pos+1];
        }
        T[0] = MAXSTRLEN;
    }
    return OK;
}

//删除串T中自第pos个字符起长度len的子串
Status DeleteStr(SString T, int pos, int len){
    if (pos<1||pos>T[0]||len<0||len+pos-1>T[0]) {
        return ERROR;
    }
    //int i=pos+len是找到要删除串的后一个字符，将要删除串后面的字符均向前移动len个位置
    for (int i=pos+len; i<=T[0]; i++) {
        T[i-len] = T[i];
    }
    T[0] -= len;
    return OK;
}

//串S存在，用V串替换串T中出现的所有与S相等的子串
Status Replace(SString &T, SString S, SString V){
    if (StrEmpty(S)) {
        return ERROR;
    }
    int i = 1; //从T中的第一个字符位置开始查找子串S
    do {
        i = Index4_5(T, S, i); //从第i个字符开始查找子串S
        if (i) { //i不为0说明找到了S串，并且i为第一个出现子串S的位置
            DeleteStr(T, i, S[0]); //删除子串S
            StrInsert(T, i, V); //在原位置插入串V
            i += V[0];  //在插入的串V后面继续查找串S
        }
    } while (i);
    return OK;
}

//SString是定长类型，不能销毁
void DestoryString(SString T){
    
}

//输出字符串T
void Print(SString T){
    for (int i = 1; i<=T[0]; i++) {
        printf("%c\n",T[i]);
    }
    printf("\n");
}






