//
//  Algo3_5.cpp
//  DataStruct
//
//  Created by guyuexing on 2017/6/6.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "Algo3_5.hpp"

//定义一个全局变量用来对搬动的次数进行计数
int c = 0;

void move(char x, int n, char z){
    printf("%i. Move disk %i from %c to %c\n", ++c,n,x,z);
}

//将塔座x上按直径由小到大且自上而下编号为1至n的n个圆盘按规则搬到塔座z上，y可用作辅助塔座
void hanoi(int n, char x, char y, char z){
    if (n==1) {
        move(x, 1, z);
    }else{
        //如果n不为1，则将x上编号为1至n-1的圆盘移动到y上，z做为辅助盘
        hanoi(n-1, x, z, y);
        move(x, n, z);
        //再将y上编号1至n-1的圆盘移动到z，x作为辅助盘
        hanoi(n-1, y, x, z);
    }
}

void main3_5(){
    int n;
    printf("3个塔座为a、b、c，圆盘最初在a座，借助b座移到c座。请输入圆盘数：");
    scanf("%d",&n);
    hanoi(n,'a','b','c');
}
