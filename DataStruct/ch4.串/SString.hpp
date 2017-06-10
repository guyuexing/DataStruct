//
//  SString.hpp
//  DataStruct
//
//  Created by haozhu on 2017/6/10.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "PublicHeader.h"

//串的定长顺序存储表示
#define MAXSTRLEN 40 //用户可在255以内定义最大串长(1个字节)

typedef char SString[MAXSTRLEN+1]; //SString是一个长度为MAXSTRLEN+1的字符数组的数据类型

SString s; //s即为长度为MAXSTRLEN+1的字符数组
