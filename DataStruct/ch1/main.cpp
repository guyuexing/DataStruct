//
//  main.cpp
//  ch1
//
//  Created by guyuexing on 17/4/22.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "PublicHeader.h"
#include "Triplet.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    Triplet T;
    ElemType e;
    Status i;
    
    i = InitTriplet(T, 7, 8, 9);
    printf("调用初始化函数后, i=%d(i=1表示成功),T的三个值是：",i);
    cout << T[0] << T[1] << T[2] <<endl;
    
    i = Get(T, 1, e);
    if (i==OK) {
        cout << "T的第二个值是：" << T[1] << endl;
    }
    
    i = Put(T, 1, 20);
    if (i == OK) {
        cout << "修改值后T的三个值为：" << T[0] << T[1] << T[2] <<endl;
    }
    
    i = IsAcending(T);
    cout << "T是否是升序：" << i << endl;
    
    i = IsDescending(T);
    cout << "T是否是降序：" << i <<endl;
    
    i = Max(T, e);
    if (i == OK) {
        cout << "T中的最大值是：" << e << endl;
    }
    
    i = Min(T, e);
    if (i == OK) {
        cout << "T中的最小值是：" << e << endl;
    }
    
    Destroy(T);
    
    return 0;
}
