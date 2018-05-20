#include<stdio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0;

typedef char ElemType;
typedef int Status;
typedef struct DualNode
{
    ElemType data;
    struct DualNode *prior;
    struct DualNode *next;
}DualNode,*DuLinkList;

Status InitList(DuLinkList *L)
{
    DualNode *p,*q;
    int i;

    *L=(DuLinkList)malloc(sizeof(DualNode));

    if(!(*L))
    {
        return ERROR;
    }

    (*L)->next=(*L)->prior=NULL;
    p=(*L);

    for(i=0;i<26;i++)
    {
        q=(DualNode *)malloc(sizeof(DualNode));
        if(!q)
        {
            return ERROR;
        }

        q->data='A'+i;
        q->prior=p;
        q->next=p->next;
        p->next=q;
        p=q;
    }

    p->next=(*L)->next;
    (*L)->next->prior=p;

    return OK;
}

/*��������2 ������1 ��λ��n ��*/

/*��ӡ����*/
void DisplayDulist(DuLinkList *L, int number)
{
    int i = 0;
    for (i = 0; i < number;i++)
    {
        *L = (*L)->next;
        printf("%c",(*L)->data);
    }
    printf("\n");
}

/*����*/
void DestoryDuList(DuLinkList *L)
{
    /*���ýڵ����ͷ��ڴ�*/
    DualNode *pstNode = NULL;

    while((*L)->next != (*L))
    {
        pstNode = (*L);
        (*L)->prior->next = pstNode->next;
        (*L)->next->prior = pstNode->prior;

        (*L) = (*L)->next;

        free(pstNode);
        pstNode = NULL;
    }
    free(*L);
    (*L) = NULL;
}

void caser(DuLinkList *L,int i)
{
    if(i>0)
    {
         do
         {
            (*L)=(*L)->next;
         }while(--i);

    }
    if(i<0)
    {
        i=i-1;
        (*L)=(*L)->next;

        do
        {
            (*L)=(*L)->prior;
        }while(++i);
    }

}

int main()
{
    DuLinkList L;
    int i,n;

    InitList(&L);
    printf("������һ������:\n");
    scanf("%d",&n);
    printf("\n");

    caser(&L,n);

    /*������� 1*/
    for(i=0;i<26;i++)
    {
        L=L->next;
        printf("%c",L->data);
    }
    printf("\n");

    /*�ú�����ӡ����*/
    DisplayDulist(&L, 26);

    /*�ͷ��ڴ�*/
    DestoryDuList(&L);

    return 0;
}
