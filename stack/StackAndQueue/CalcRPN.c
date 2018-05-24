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
    // ջ����׷�ӿռ�
    if( (s->top) - (s->base) >= (s->stackSize) )
    {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
        if( !s->base )
            exit(0);

        s->top = s->base + s->stackSize;
        s->stackSize = s->stackSize + STACKINCREMENT;
    }

    *(s->top) = e;      // �������
    s->top++;

    return;
}

void Pop(sqStack *s, ElemType *e)
{
    if( s->top == s->base )
        return;

    *e = *(--(s->top));   // ��ջ��Ԫ�ص������޸�ջ��ָ��

    return;
}

int StackLen(sqStack s)
{
    return (s.top - s.base);
}

/*��׺���ʽת�����沨�����ʽ*/
void Mid2Rpn(sqStack *s, sqStack *sRpn)
{
    char c;
    double popValue;

    printf("��������׺���ʽ����#��Ϊ������־��");
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
            //��������ո�
        }
        else
        {
            printf("\n���������ʽ����\n");
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

    printf("\n�밴�沨�����ʽ������������ݣ������������֮���ÿո��������#��Ϊ������־: \n");
    Pop(sRpn, &readCharFromStack);

    while( (char)readCharFromStack != '#' )
    {
        while( isdigit((char)readCharFromStack) || (char)readCharFromStack == '.' )  // ���ڹ�������
        {
            str[i++] = (char)readCharFromStack;
            str[i] = '\0';
            if( i >= 10 )
            {
                printf("��������ĵ������ݹ���\n");
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
                    printf("\n��������Ϊ�㣡\n");
                    return;
                }
                break;
        }

        Pop(sRpn, &readCharFromStack);
    }

    Pop(&s, &d);
    printf("\n���յļ�����Ϊ��%f\n", d);

    DestoryStack(&s);//�ͷ���ʱ����ջ
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

    /*����ջ��˳��ģ���ַ�������*/
    while( StackLen(sRpn))
    {
        Pop(&sRpn, &popVal);
        Push(&s, popVal);
        //printf("%c", (char)popVal);
    }

    //�鿴�沨�����ʽ�Ƿ���ȷ
    /*while( StackLen(s) )
    {
        Pop(&s, &popVal);
        printf("%c", (char)popVal);
    }*/

    CalcRpn(&s);

    //�ڴ��ͷ�
    DestoryStack(&s);
    DestoryStack(&sRpn);
    return 0;
}
/*
test data:
1+2+(4.5+5.5)*2-10#
1+2+3+4+(2.1+0.1)-10#
*/
