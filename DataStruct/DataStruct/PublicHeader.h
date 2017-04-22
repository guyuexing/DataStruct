//
//  PublicHeader.h
//  DataStruct
//
//  Created by guyuexing on 17/4/20.
//  Copyright © 2017年 neu. All rights reserved.
//
#include <string.h>
#include <ctype.h>
#include <malloc/malloc.h>  //malloc()等
#include <limits.h> //INT_MAX等
#include <stdio.h> //EOF，NULL
#include <stdlib.h> //atoi()
#include <math.h>  //floor(),ceil(), abs()
#include <iostream> // cout cin

//函数结果状态码
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;  // Status是函数的类型,其值是函数结果状态代码，如OK等
typedef int Boolean; // Boolean是布尔类型,其值是TRUE或FALSE

/**
 *  基本的函数说明
 
    求最大值        max(表达式1,...,表达式n)
    求最小值        min(表达式1,...,表达式n)
    求绝对值        abs(表达式)
    求不足整数值     floor(表达式)
    求进位整数值     ceil(表达式)
    判定文件结束     eof(文件变量)或 eof
    判定行结束       eoln(文件变量)或 eoln
 */

