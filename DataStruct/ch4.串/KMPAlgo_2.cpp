//
//  KMPAlgo_2.cpp
//  DataStruct
//
//  Created by guyuexing on 2017/7/2.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "KMPAlgo_2.hpp"

//KMP改进算法
void get_nextval(SString T, int nextval[]){
    int i = 1, j = 0;
    nextval[1] = 0;
    while (i<T[0]) {
        if (j==0 || T[i]==T[j]) {
            i++;
            j++;
            if (T[i]==T[j]) {
                nextval[i] = nextval[j];
            }else{
                nextval[i] = j;
            }
        }else{
            j = nextval[j];
        }
    }
}

int index_KMP(SString T, SString S, int pos, int nextval[]){
    int i = pos;
    int j = 1;
    while (i<=T[0] && j<=S[0]) {
        if (j==0 || T[i]==T[j]) {  //匹配成功，继续比较后继字符
            i++;
            j++;
        }else{
            j = nextval[j];  //模式串右移
        }
    }
    if (j>S[0]) {
        return i-S[0];
    }else{
        return 0;
    }
}

void main_2()
{
    int i,j,*p;
    SString s1,s2; // 以教科书算法4.8之上的数据为例
    StrAssign(s1,"aaabaaaab");
    printf("主串为: ");
    Print(s1);
    StrAssign(s2,"aaaab");
    printf("子串为: ");
    Print(s2);
    i=StrLength(s2);
    p=(int*)malloc((i+1)*sizeof(int)); // 生成s2的next数组
    get_nextval(s2,p);
    printf("子串的nextval函数为: ");
    for(j=1;j<=i;j++)
        printf("%d ",*(p+j));
    printf("\n");
    printf("主串和子串在第%d个字符处首次匹配\n",index_KMP(s1,s2,1,p));
}
