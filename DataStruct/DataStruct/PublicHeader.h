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

typedef int Status;  // Status是函数的类型,其值是函数结果状态代码，如OK等
typedef int Boolean; // Boolean是布尔类型,其值是TRUE或FALSE

