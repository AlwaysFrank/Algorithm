
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

// �������ܣ���ʼ��ջ
// ����*s��ջ�ĵ�ַ
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

// �������ܣ���ջ����
// ����*s��ջ�ĵ�ַ
// ����e����ѹ��ջ��Ԫ��
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


// �������ܣ���ջ����
// ����*s��ջ�ĵ�ַ
// ����e����Ŵ�ջ�ﵯ��������
void Pop(sqStack *s, ElemType *e)
{
    if( s->top == s->base )
    {
        return;
    }
    *e = *--(s->top);
}

// �������ܣ�����ջs�ĵ�ǰ����
// ����s��ջ
int StackLen(sqStack s)
{
    return (s.top - s.base);
}

//2����ת��10����
void Bin2Dec(sqStack *s)
{
    ElemType c;
    int sum = 0;
    int len = 0;
    int i = 0;

    len = StackLen(*s);
    printf("\nջ�ĵ�ǰ������: %d\n", len);

    for( i=0; i < len; i++ )
    {
        Pop(s, &c);
        sum = sum + (c-48) * pow(2, i);
    }

    printf("ת��Ϊʮ��������: %d\n", sum);
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
    printf("\nջ�ĵ�ǰ������: %d\n", len);

    InitStack(&sqTempForHex);
    for( i=0; i < len; i+=4 )
    {
        for( j=0 ; j < 4; j++ )
        {
            Pop( s, &c ); // ȡ��ջ��Ԫ��
            sum = sum + (c-48) * pow(2, j);

            if( s->base == s->top )//��ֹ����4�ı�������ǰ����
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

    printf("ת��Ϊʮ����������: ");
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
    printf("\nջ�ĵ�ǰ������: %d\n", len);

    InitStack(&sqTempForOct);

    for( i=0; i < len; i+=3 )
    {
        for( j=0; j < 3; j++ )
        {
            Pop( s, &c ); // ȡ��ջ��Ԫ��
            sum = sum + (c-48) * pow(2, j);

            if( s->base == s->top )//��ֹ����3�ı�������ǰ����
            {
                break;
            }
        }

        Push( &sqTempForOct, sum+48 );
        sum = 0;
    }

    printf("ת��Ϊ�˽�������: ");
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

    printf("�������������������#���ű�ʾ������\n");
    scanf("%c", &c);
    while( c != '#' )
    {
        Push(&sqForDec, c);
        Push(&sqForHex, c);
        Push(&sqForOct, c);
        scanf("%c", &c);
    }

    getchar();  // ��'\n'�ӻ�����ȥ��

    Bin2Dec(&sqForDec);
    Bin2Hex(&sqForHex);
    Bin2Oct(&sqForOct);

    DestoryStack(&sqForDec);
    DestoryStack(&sqForHex);
    DestoryStack(&sqForOct);
    return 0;
}
