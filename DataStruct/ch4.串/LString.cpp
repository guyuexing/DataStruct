//
//  LString.cpp
//  DataStruct
//
//  Created by guyuexing on 2017/6/21.
//  Copyright © 2017年 neu. All rights reserved.
//

#include "LString.hpp"

#define Blank '#'

//初始化字符串T（产生空串）
void InitString(LString &T){
    T.curLen = 0;
    T.head = T.tail = NULL;
}

// 生成一个其值等于chars的串T(要求chars中不包含填补空余的字符)
// 成功返回OK，否则返回ERROR
Status StrAssign(LString &T, char *chars){
    int i = (int)strlen(chars);
    if (!i||strchr(chars, Blank)) { //strchr函数的作用是查找在字符串chars中首次出现_CTYPE_B字符的位置
        //此if条件是说当chars为空或chars中包含T要填补空余的字符则直接返回错误
        return ERROR;
    }
    T.curLen = i;
    int j = i/CHUNKSIZE;  //j为块链的节点数
    if (i%CHUNKSIZE) {
        j++;   //如果i不是块大小的整数倍，则j++
    }
    Chunk *p, *q = nullptr;
    for (int k=0; k<j; k++) {  //遍历每一个链块
        p = (Chunk *)malloc(sizeof(Chunk));
        if (!p) {
            return ERROR;
        }
        if (k==0) { //如果是第一个链块
            T.head = q = p;
        }else{
            q->next = p;
            q = p;
        }
        int m= 0;
        for (; m<CHUNKSIZE&&(*chars); m++) { //给链块赋值
            *(p->ch+m) = *(chars++);
        }
        if (!*chars) { //如果是最后一个链块，给空余的位置填补占位字符
            T.tail = p;
            for (; m<CHUNKSIZE; m++) {  //m是上一个for循环结束后的第一个空余位置出现的位置
                *(p->ch+m) = Blank;
            }
        }
    }
    return OK;
}

// 初始条件:串S存在。操作结果:由串S复制得串T(连填补空余的字符一块拷贝)
Status StrCopy(LString &T, LString S){
    Chunk *p;
    Chunk *q;
    Chunk *h = S.head;
    if (h) {
        T.curLen = S.curLen;
        p = T.head = (Chunk *)malloc(sizeof(Chunk));
        *p = *h; //给第一个块链赋值
        h = h->next;
        while (h) {
            q = p;
            p = (Chunk *)malloc(sizeof(Chunk));
            q->next = p;
            *p = *h;
            h = h->next;
        }
        p->next = NULL;
        T.tail = p;
        return OK;
    }else{
        return ERROR;
    }
}

Status StrEmpty(LString T){
    return T.curLen == 0;
}

// 若T>S,则返回值>0;若T=S,则返回值=0;若T<S,则返回值<0
int StrCompare(LString T, LString S){
    int i = 0;
    int jt = 0;
    int js = 0;
    Chunk *pt = T.head;
    Chunk *ps = S.head;
    while (i<T.curLen&&i<S.curLen) {
        i++;  //i为当前待比较的字符在T和S串中的位置
        while (*(pt->ch+jt) == Blank) { //比较的时候跳过填补空余的字符
            jt++;
            if (jt==CHUNKSIZE) {
                pt = pt->next;
                jt = 0;
            }
        }
        while (*(ps->ch+js) == Blank) { //比较的是否跳过填补空余的字符
            js++;
            if (js==CHUNKSIZE) {
                ps = ps->next;
                js = 0;
            }
        }
        if (*(ps->ch+js)!=*(pt->ch+jt)) { //比较字符
            return *(pt->ch+jt) - *(ps->ch+js); //如果比较的两字符不相等，直接返回差值
        }else{ //如果比较的两个字符相等，则同时将待比较的字符后移
            jt++;
            if (jt==CHUNKSIZE) { //取后一个字符时如果此链块结束了，则取下一个链块的字符进行比较
                pt = pt->next;
                jt = 0;
            }
            js++;
            if (js==CHUNKSIZE) {
                ps = ps->next;
                js = 0;
            }
        }
    }
    return T.curLen - S.curLen;
}

int StrLength(LString T){
    return T.curLen;
}

//将T清空为空串
Status CleanStr(LString &T){
    Chunk *p, *q;
    p = T.head;
    while (p) {
        q = p->next;
        free(p); //释放存储字符串空间
        p = q;
    }
    T.head = T.tail = NULL;
    T.curLen = 0;
    return OK;
}

Status Concat(LString &T, LString S1, LString S2){
    LString t1, t2; //创建t1、t2结构体
    InitString(t1); //初始化为空串
    InitString(t2);
    StrCopy(t1, S1); //赋值S1串到t1中
    StrCopy(t2, S2);
    t1.tail->next = t2.head;
    T.head = t1.head;
    T.tail = t2.tail;
    T.curLen = t1.curLen+t2.curLen;
    return OK;
}

//用Sub返回T串第pos个字符起长度为len的子串，这里的子串不包括填充字符
Status SubString(LString &Sub, LString T, int pos, int len){
    if (pos<1||pos>T.curLen||len<0||pos+len-1>T.curLen) {
        return ERROR;
    }
    Chunk *p, *q;
    //接下来生成空的Sub串
    int n = len/CHUNKSIZE;
    if (len%CHUNKSIZE) {
        n++;
    }
    p = new Chunk;
    Sub.head = p;
    for (int i=1; i<n; i++) {
        q = new Chunk; //等价于malloc
        p->next = q;
        p = q;
    }
    p->next = NULL;
    Sub.tail = p;
    Sub.curLen = len;
    //填充Sub尾部空余的空间
    for (int i=len%CHUNKSIZE; i<CHUNKSIZE; i++) {
        //此时p是指向Sub串的尾部
        *(p->ch+i) = Blank;
    }
    //以上是完成Sub的初始化相关工作，也填充了空余的空间
    
    q = Sub.head; //q指向Sub即将复制的块
    p = T.head;   //p指向T的当前被复制给Sub的块
    int i = 0; //i表示即将复制的字符在Sub块中的位置
    int m = 0; //m表示将要被复制的字符在T块中的序号（不同于位置）
    /*
        串：      11 22 15 14  # 51 26  # 37 38
        位置：     0  1  2  0  1  2  0  1  2  0
        序号：     1  2  3  4     5  6     7  8
     */
    int flag = 1;
    while (flag) {
        for (int k=0; k<CHUNKSIZE; k++) { //k只是当前被复制的字符在串T中的位置
            if (*(p->ch+k)!=Blank) {  //只有不是占位字符才会被复制
                m++;  //m表示当前被复制的字符在T中的序号
                if (m>=pos&&m<=pos+len-1) { //满足条件开始复制
                    if (i==CHUNKSIZE) {
                        q = q->next;
                        i = 0;
                    }
                    *(q->ch+i) = *(p->ch+k);
                    i++;
                    if (m==pos+len-1) {
                        flag = 0; //结束复制
                        break;
                    }
                }
            }
        }
        p = p->next;  //遍历完了一个块链，遍历下一个
    }
    return OK;
}

//压缩串(清除块中不必要的填补空余的字符)
void Zip(LString &T){
    //生成字符串p
    char *p = (char *)malloc(sizeof(char)*(T.curLen+1));
    Chunk *h = T.head;
    int j = 0;
    while (h) { //将串T中的非空字符提取出来复制到字符串p中
        for (int i=0; i<CHUNKSIZE; i++) {
            if (*(h->ch+i)!=Blank) {
                *(p+j) = *(h->ch+i);
                j++;
            }
        }
        h = h->next;
    }
    *(p+j) = '\0';  //串结束符
    CleanStr(T);    //清空串T
    StrAssign(T, p);//重新生成串T
}

//在串T的第pos个字符之前插入串S 1<=pos<=StrLength(T)+1
Status StrInsert(LString &T, int pos, LString S){
    if (pos<1||pos>S.curLen+1) {
        return ERROR;
    }
    LString t;
    StrCopy(t, S); //赋值串S到t
    Zip(T);  //去掉T中多余的填补空余的字符
    
    int i = (pos-1)/CHUNKSIZE; //计算到达插入点要经过的块数
    int j = (pos-1)%CHUNKSIZE; //计算到达插入点在最后一个块链上要经过的字符数
    Chunk *p = T.head;
    Chunk *q;
    
    if (pos==1) { //串S要插在串T之前，只需要改变串T的头指针即可
        t.tail->next = T.head;
        T.head = t.head;
    }else if (j==0){ //串S插入到T的块链之间，不需要经过字符
        //找到那两个块链
        for (int k=1; k<i; k++) {
            p = p->next;
        } //循环结束后p指向两个块链的前一个块链
        q = p->next; //q指向两个块链的后一个块链
        p->next = t.head; //插入块t（和串S相同）
        t.tail->next = q;
        if (q==NULL) {
            T.tail = t.tail;
        }
    }else{  //插在一块内的两个字符之前
        for (int k=1; k<=i; k++) {
            p = p->next;  //p指向插入点所在块
        }
        q = new Chunk; //生成新块
        for (int n=0; n<j; n++) {
            *(q->ch+n) = Blank;  //将q的前j个字符填补为空余的字符
        }
        for (int n=j; n<CHUNKSIZE; n++) {
            *(q->ch+n) = *(p->ch+n); //复制插入点之后的字符到q
            *(p->ch+n) = Blank; //p的该字符重新赋值为空余字符
        }
        q->next = p->next; //将串t和q插入到串T中
        p->next = t.head;
        t.tail->next = q;
    }
    T.curLen += S.curLen;
    Zip(T); //去除T中的填补字符
    return OK;
}

//从串T中删除第pos个字符起长度为len的子串
Status StrDelete(LString &T, int pos, int len){
    if (pos<1||pos>T.curLen||len<0||len+pos-1>T.curLen) {
        return ERROR;
    }
    //找第pos个字符
    int i = 1; //当前字符是T串的第i个字符，序号（1~T.curlen）
    int j = 0; //当前字符在当前块中的位置
    Chunk *p = T.head;
    while (i<pos) {
        //这个while循环是为了防止计算第pos个字符的位置错误（相比于用if）
        while (*(p->ch+j)==Blank) { //当前位置的字符是空余字符，跳过
            j++;
            if (j==CHUNKSIZE) {
                p = p->next;
                j = 0;
            }
        }
        i++;
        j++;
        if (j==CHUNKSIZE) {
            p = p->next; //转向下一个块链
            j = 0;
        }
    } //循环结束后i=pos，j为第pos个字符在当前块链p中的位置
    
    while (i<pos+len) { //删除从第pos个字符起到第pos+len-1个字符，即长度为len
        while (*(p->ch+j)==Blank) { //跳过填补空余的字符
            j++;
            if (j == CHUNKSIZE) {
                p = p->next;
                j = 0;
            }
        }
        *(p->ch+j) = Blank; //把字符改成填补空余的字符来“删除”第i个字符
        i++;
        j++;
        if (j==CHUNKSIZE) {
            p = p->next;
            j = 0;
        }
    }
    T.curLen -= len;
    return OK;
}


int Index(LString T, LString S, int pos){
    if (pos<0||pos>T.curLen) {
        return ERROR;
    }
    LString sub;
    InitString(sub);
    int n = T.curLen;
    int m = S.curLen;
    int i = pos;
    while (i<=n-m+1) {
        SubString(sub, T, i, S.curLen);
        if (StrCompare(sub, S)==0) {
            return i;
        }else{
            i++;
        }
    }
    return 0;
}

//如果T,S,V均存在，且S是非空串，用V替换T中出现的所有与S相等且不重叠的子串
Status Replace(LString &T, LString S, LString V){
    if (StrEmpty(S)) {
        return ERROR;
    }
    int i = 1;
    do {
        i = Index(T, S, i);
        if (i) {
            StrDelete(T, i, S.curLen);
            StrInsert(T, i, V);
            i += V.curLen;
        }
    } while (i);
    return OK;
}

//输出字符串T
void StrPrint(LString T){
    Chunk *h = T.head;
    int i = 0;
    while (i<T.curLen) {
        for (int j=0; j<CHUNKSIZE; j++) {
            if (*(h->ch+j)!=Blank) {  //打印不是填补空余的字符
                printf("%c",*(h->ch+j));
                i++;
            }
        }
        h = h->next;
    }
    printf("\n");
}

//块链类型的字符串无法销毁
void DestroyString(){

}
