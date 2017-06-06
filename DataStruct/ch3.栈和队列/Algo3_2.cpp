//
//  Algo3_2.cpp
//  DataStruct
//
//  Created by haozhu on 2017/6/5.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "Algo3_2.hpp"

//括号匹配算法
void check(){
    SElemType ch[80], *p, e;
    SqStack S;
    if (InitStack(S)) {  //初始化栈成功
        printf("请输入表达式:");
        gets(ch);
        p = ch;
        while (*p) {  //没有到串尾
            switch (*p) {
                case '[':
                case '(':
                    Push(S, *p); //遇到[或(则入栈
                    p++;
                    break;
                case ']':
                case ')':
                    if (!EmptyStack(S)) { //如果栈不空
                        Pop(S, e);  //出栈
                        if ((*p==']'&&e!='[')||(e!='('&&*p==')')) {
                            printf("左右括号格式不匹配");
                            exit(ERROR);
                        }else{
                            p++;   //括号是匹配的，指针右移比较下一个
                            break;
                        }
                    }else{
                        printf("缺乏左括号");
                        exit(ERROR);
                    }
                default:
                    p++;  //如果是其他的字符不处理，直接右移
                    break;
            }
        }
        if (EmptyStack(S)) {  //字符串如果匹配，结束时栈应该是空的
            printf("括号匹配\n");
        }else{
            printf("缺乏右括号\n");
        }
    }
}

void main3_2(){
    check();
}
