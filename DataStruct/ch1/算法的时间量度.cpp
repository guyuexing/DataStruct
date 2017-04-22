//
//  算法的时间量度.cpp
//  DataStruct
//
//  Created by guyuexing on 17/4/22.
//  Copyright © 2017年 neu. All rights reserved.
//
//N*N矩阵相乘的算法时间复杂度为O(m*n*k)
void matrix(){
    int m,n,k;
    int P[m][n], Q[n][k],R[m][k];
    for (int i = 0; i< m; i++) {
        for (int j = 0; j< k; j++) {
            R[i][j] = 0;
            for (int p =0; p< n; p++) {
                R[i][j] += P[i][p]*Q[p][j];
            }
        }
    }
}
