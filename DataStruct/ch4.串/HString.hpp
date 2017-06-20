//
//  HString.hpp
//  DataStruct
//
//  Created by guyuexing on 2017/6/20.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "PublicHeader.h"

typedef struct {
    char *ch; //若是非空串，则按串长分配存储区，否则ch为NULL
    int length; //串长度
}HString;
