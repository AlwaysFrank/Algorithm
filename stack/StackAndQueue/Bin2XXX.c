
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT  10

typedef char ElemType;
typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;
}sqStack;

// 函数功能：初始化栈
// 参数*s：栈的地址
void InitStack(sqStack *s)
{
    s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if( !s->base )
    {
        exit(0);
    }

    s->top = s->base;
    s->stackSize = STACK_INIT_SIZE;
}

void DestoryStack(sqStack *s)
{
    if (NULL != s->base)
    {
        free(s->base);
        s->base = NULL;
    }
}

// 函数功能：入栈操作
// 参数*s：栈的地址
// 参数e：待压入栈的元素
void Push(sqStack *s, ElemType e)
{
    if( s->top - s->base >= s->stackSize )
    {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
        if( !s->base )
        {
            exit(0);
        }
    }

    *(s->top) = e;
    s->top++;
}


// 函数功能：弹栈操作
// 参数*s：栈的地址
// 参数e：存放从栈里弹出的数据
void Pop(sqStack *s, ElemType *e)
{
    if( s->top == s->base )
    {
        return;
    }
    *e = *--(s->top);
}

// 函数功能：计算栈s的当前长度
// 参数s：栈
int StackLen(sqStack s)
{
    return (s.top - s.base);
}

//2进制转换10进制
void Bin2Dec(sqStack *s)
{
    ElemType c;
    int sum = 0;
    int len = 0;
    int i = 0;

    len = StackLen(*s);
    printf("\n栈的当前容量是: %d\n", len);

    for( i=0; i < len; i++ )
    {
        Pop(s, &c);
        sum = sum + (c-48) * pow(2, i);
    }

    printf("转化为十进制数是: %d\n", sum);
    return ;
}

void Bin2Hex(sqStack *s)
{
    ElemType c;
    int sum = 0;
    int len = 0;
    int i,j = 0;
    sqStack sqTempForHex;

    len = StackLen(*s);
    printf("\n栈的当前容量是: %d\n", len);

    InitStack(&sqTempForHex);
    for( i=0; i < len; i+=4 )
    {
        for( j=0 ; j < 4; j++ )
        {
            Pop( s, &c ); // 取出栈顶元素
            sum = sum + (c-48) * pow(2, j);

            if( s->base == s->top )//防止不是4的倍数，提前结束
            {
                break;
            }
        }

        switch( sum )
        {
            case 10: sum = 'A'; break;
            case 11: sum = 'B'; break;
            case 12: sum = 'C'; break;
            case 13: sum = 'D'; break;
            case 14: sum = 'E'; break;
            case 15: sum = 'F'; break;
            default: sum += 48;
        }

        Push( &sqTempForHex, sum );
        sum = 0;
    }

    printf("转化为十六进制数是: ");
    while( sqTempForHex.base != sqTempForHex.top )
    {
        Pop( &sqTempForHex, &c );
        printf("%c", c);
    }
    printf("(H)\n");

    DestoryStack(&sqTempForHex);

    return ;
}

void Bin2Oct(sqStack *s)
{
    ElemType c;
    int sum = 0;
    int len = 0;
    int i,j = 0;
    sqStack sqTempForOct;

    len = StackLen(*s);
    printf("\n栈的当前容量是: %d\n", len);

    InitStack(&sqTempForOct);

    for( i=0; i < len; i+=3 )
    {
        for( j=0; j < 3; j++ )
        {
            Pop( s, &c ); // 取出栈顶元素
            sum = sum + (c-48) * pow(2, j);

            if( s->base == s->top )//防止不是3的倍数，提前结束
            {
                break;
            }
        }

        Push( &sqTempForOct, sum+48 );
        sum = 0;
    }

    printf("转化为八进制数是: ");
    while( sqTempForOct.base != sqTempForOct.top )
    {
        Pop( &sqTempForOct, &c );
        printf("%c", c);
    }
    printf("(O)\n");

    DestoryStack(&sqTempForOct);

    return ;
}

int main()
{
    ElemType c;
    sqStack sqForDec;
    sqStack sqForHex;
    sqStack sqForOct;

    InitStack(&sqForDec);
    InitStack(&sqForHex);
    InitStack(&sqForOct);

    printf("请输入二进制数，输入#符号表示结束！\n");
    scanf("%c", &c);
    while( c != '#' )
    {
        Push(&sqForDec, c);
        Push(&sqForHex, c);
        Push(&sqForOct, c);
        scanf("%c", &c);
    }

    getchar();  // 把'\n'从缓冲区去掉

    Bin2Dec(&sqForDec);
    Bin2Hex(&sqForHex);
    Bin2Oct(&sqForOct);

    DestoryStack(&sqForDec);
    DestoryStack(&sqForHex);
    DestoryStack(&sqForOct);
    return 0;
}
