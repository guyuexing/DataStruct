//
//  Algo3_4.cpp
//  DataStruct
//
//  Created by guyuexing on 2017/6/6.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "Algo3_4.hpp"

//m必须大于n，否则是死循环
int ack(int m, int n){
    if (m==0) {
        return n+1;
    }else if(n==0){
        return ack(m-1,1);
    }else{
        return ack(m-1,ack(m,n-1));
    }
}

void main3_4(){
    printf("请输入m,n:\n");
    int m, n;
    scanf("%d,%d",&m,&n);
    printf("m:%d,n:%d,ack:%d",m,n,ack(m, n));
}
