//
//  Algo3_3.cpp
//  DataStruct
//
//  Created by guyuexing on 2017/6/5.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "Algo3_3.hpp"

FILE *fp;

void copy(SElemType c){
    fputc(c, fp);
}

void LineEdit(){
    SqStack S;
    InitStack(S);
    printf("请输入一个文本文件，EOF结束输入:\n");
    char ch,c;
    c = getchar();
    while (c!=EOF) {
        while (c!=EOF&&c!='\n') {
            switch (c) {
                case '#': //如果是字符#，栈顶元素出栈
                    Pop(S, ch);
                    break;
                case '@': //如果是字符@，清空栈
                    ClearStack(S);
                    break;
                default:  //有效元素进栈
                    Push(S, c);
                    break;
            }
            c=getchar();  //循环获取字符，直到遇到EOF或\n结束此行的输入
        }
        StackTraverse(S, copy); //从栈底到栈顶的栈内字符传送到文件
        ClearStack(S);  //清空此行的字符
        fputc('\n', fp);  //向文件中再添加换行符
        if (c!=EOF) {
            c=getchar();  //用户又输入下一行字符
        }
    }
    DestoryStack(S);  //输入结束，销毁栈
}

void main3_3(){
    fp = fopen("ED.dat", "w");
    if (fp) {
        LineEdit();
        fclose(fp);
    }else{
        printf("建立文件失败!\n");
    }
}
