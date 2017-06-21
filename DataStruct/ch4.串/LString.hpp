//
//  LString.hpp
//  DataStruct
//
//  Created by guyuexing on 2017/6/21.
//  Copyright © 2017年 neu. All rights reserved.
//

//串的块链存储表示
#include "PublicHeader.h"

#define CHUNKSIZE 80 //可由用户定义块的大小

typedef struct Chunk{
    char ch[CHUNKSIZE];
    struct Chunk *next;
}Chunk;

typedef struct {
    Chunk *head, *tail; //串的头和尾指针
    int curLen;  //串的当前长度
}LString;
