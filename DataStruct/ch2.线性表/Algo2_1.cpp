//
//  Algo2_1.cpp
//  DataStruct
//
//  Created by guyuexing on 17/4/23.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "Algo2_1.hpp"

//判断两个元素是否相等，Union函数要用到
Status equal(ElemType e1, ElemType e2){
    if (e1 == e2) {
        return TRUE;
    }else{
        return FALSE;
    }
}

//将两个线性表合并的函数
void Union(SqList &La, SqList Lb){
    //先确定两个线性表的长度
    int la_len = La.length;
    int lb_len = Lb.length;
    //用来获取Lb中的每一个元素
    ElemType e;
    //遍历线性表Lb
    for (int i = 1; i<=lb_len; i++) {
        //取出表Lb中位序为i的元素赋值给e
        if (GetElem(Lb, i, e)) {
            //如果表La中没有这个这个元素e
            if (!LocateElem(La, e, equal)) {
                //那么将元素e插入到表La中，插入的位序每次需要先增加la_len
                ListInsert(La, ++la_len, e);
            }
        }
    }
}