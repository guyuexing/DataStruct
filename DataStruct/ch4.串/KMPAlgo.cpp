//
//  KMPAlgo.cpp
//  DataStruct
//
//  Created by guyuexing on 2017/7/2.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "KMPAlgo.hpp"


//求模式串T的Next函数值并存入数组next
void get_next(SString T, int next[]){
    int i = 1, j = 0;
    next[1] = 0;
    while (i<T[0]) {
        if (j==0 || T[i]==T[j]) {
            i++;
            j++;
            next[i] = j;
        }else{
            j = next[j];
        }
    }
}

//利用模式串S的next函数求S在主串T中第pos个字符之后的位置KMP算法
int Index_KMP(SString T, SString S, int pos, int next[]){
    int i = pos;
    int j = 1;  //表示S中的第j个字符应该与T中第pos个字符相比较
    while (i<=T[0] && j<=S[0]) {
        if (j==0 || T[i]==S[j]) {
            j++;
            i++;
        }else{
            j = next[j];
        }
    }
    if (j>S[0]) { //j大于S[0]说明已经比较完毕
        return i-S[0];
    }else{
        return 0;
    }
}

void main_1(){
    int i,j,*p;
    SString s1,s2; // 以教科书中图4.5为例
    char *temp = "acabaabaabcacaabc";
    StrAssign(s1,temp);
    printf("主串为: ");
    Print(s1);
    temp = "abaabcac";
    StrAssign(s2,temp);
    printf("子串为: ");
    Print(s2);
    i=StrLength(s2);
    p=(int*)malloc((i+1)*sizeof(int)); // 生成s2的next数组
    get_next(s2,p);
    printf("子串的next函数为: ");
    for(j=1;j<=i;j++)
        printf("%d ",*(p+j));
    printf("\n");
    i=Index_KMP(s1,s2,1,p);
    if(i)
        printf("主串和子串在第%d个字符处首次匹配\n",i);
    else
        printf("主串和子串匹配不成功\n");
}
