#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT  10
#define MAXBUFFER       10

typedef double ElemType;
typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;
}sqStack;

void InitStack(sqStack *s)
{
    s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if( !s->base )
        exit(0);

    s->top = s->base;
    s->stackSize = STACK_INIT_SIZE;

    return;
}

void DestoryStack(sqStack *s)
{
    if (NULL != s->base)
    {
        free(s->base);
        s->base = NULL;
    }
    return;
}

void Push(sqStack *s, ElemType e)
{
    // 栈满，追加空间
    if( (s->top) - (s->base) >= (s->stackSize) )
    {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
        if( !s->base )
            exit(0);

        s->top = s->base + s->stackSize;
        s->stackSize = s->stackSize + STACKINCREMENT;
    }

    *(s->top) = e;      // 存放数据
    s->top++;

    return;
}

void Pop(sqStack *s, ElemType *e)
{
    if( s->top == s->base )
        return;

    *e = *(--(s->top));   // 将栈顶元素弹出并修改栈顶指针

    return;
}

int StackLen(sqStack s)
{
    return (s.top - s.base);
}

/*中缀表达式转换成逆波兰表达式*/
void Mid2Rpn(sqStack *s, sqStack *sRpn)
{
    char c;
    double popValue;

    printf("请输入中缀表达式，以#作为结束标志：");
    scanf("%c", &c);

    while( c != '#' )
    {
        while( (c>='0' && c<='9') || c == '.')
        {
            printf("%c", c);
            Push(sRpn, c);
            scanf("%c", &c);
            if( (c<'0' || c>'9') && c != '.')
            {
                printf(" ");
                Push(sRpn, ' ');
            }
        }

        if( ')' == c )
        {
            Pop(s, &popValue);
            while( '(' != (char)popValue )
            {
                printf("%c ", (char)popValue);
                Push(sRpn, popValue);
                Push(sRpn, ' ');
                Pop(s, &popValue);
            }
        }
        else if( '+'==c || '-'==c )
        {
            if( !StackLen(*s) )
            {
                Push(s, c);
            }
            else
            {
                do
                {
                    Pop(s, &popValue);
                    if( '(' == (char)popValue )
                    {
                        Push(s, popValue);
                        Push(sRpn, popValue);
                    }
                    else
                    {
                        printf("%c ", (char)popValue);
                        Push(sRpn, popValue);
                        Push(sRpn, ' ');
                    }
                }while( StackLen(*s) && '('!= (char)popValue );
                Push(s, c);
            }
        }
        else if( '*'==c || '/'==c || '('==c )
        {
            Push(s, c);
        }
        else if( '#'== c )
        {
            break;
        }
        else if(' ' == c || '.' == c)
        {
            //允许输入空格
        }
        else
        {
            printf("\n出错：输入格式错误！\n");
            return;
        }

        scanf("%c", &c);
    }


    while( StackLen(*s) )
    {
        Pop(s, &popValue);
        Push(sRpn, popValue);
        printf("%c", (char)popValue);
    }
}

void CalcRpn(sqStack *sRpn)
{
    sqStack s;
    double readCharFromStack;
    double d, e;
    char str[MAXBUFFER];
    int i = 0;
    InitStack( &s );

    printf("\n请按逆波兰表达式输入待计算数据，数据与运算符之间用空格隔开，以#作为结束标志: \n");
    Pop(sRpn, &readCharFromStack);

    while( (char)readCharFromStack != '#' )
    {
        while( isdigit((char)readCharFromStack) || (char)readCharFromStack == '.' )  // 用于过滤数字
        {
            str[i++] = (char)readCharFromStack;
            str[i] = '\0';
            if( i >= 10 )
            {
                printf("出错：输入的单个数据过大！\n");
                return;
            }
            Pop(sRpn, &readCharFromStack);
            if( (char)readCharFromStack == ' ' )
            {
                d = atof(str);
                Push(&s, d);
                i = 0;
                break;
            }
        }

        switch( (char)readCharFromStack )
        {
            case '+':
                Pop(&s, &e);
                Pop(&s, &d);
                Push(&s, d+e);
                break;
            case '-':
                Pop(&s, &e);
                Pop(&s, &d);
                Push(&s, d-e);
                break;
            case '*':
                Pop(&s, &e);
                Pop(&s, &d);
                Push(&s, d*e);
                break;
            case '/':
                Pop(&s, &e);
                Pop(&s, &d);
                if( e != 0 )
                {
                    Push(&s, d/e);
                }
                else
                {
                    printf("\n出错：除数为零！\n");
                    return;
                }
                break;
        }

        Pop(sRpn, &readCharFromStack);
    }

    Pop(&s, &d);
    printf("\n最终的计算结果为：%f\n", d);

    DestoryStack(&s);//释放临时计算栈
    return;
}

int main()
{
    sqStack s;
    sqStack sRpn;

    double popVal;

    InitStack( &s );
    InitStack( &sRpn );

    Mid2Rpn(&s, &sRpn);

    Push(&s, '#');

    /*调整栈的顺序，模拟字符串输入*/
    while( StackLen(sRpn))
    {
        Pop(&sRpn, &popVal);
        Push(&s, popVal);
        //printf("%c", (char)popVal);
    }

    //查看逆波兰表达式是否正确
    /*while( StackLen(s) )
    {
        Pop(&s, &popVal);
        printf("%c", (char)popVal);
    }*/

    CalcRpn(&s);

    //内存释放
    DestoryStack(&s);
    DestoryStack(&sRpn);
    return 0;
}
/*
test data:
1+2+(4.5+5.5)*2-10#
1+2+3+4+(2.1+0.1)-10#
*/
