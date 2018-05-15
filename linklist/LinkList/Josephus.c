//n个人围圈报数，报m出列，最后剩下的是几号？
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}node;

/*创建N个递增的循环链表*/
node *create(int n)
{
	node *p = NULL, *head;
	head = (node*)malloc(sizeof (node ));
	p = head;
	node *s;
	int i = 1;

	if( 0 != n )
	{
		while( i <= n )
		{
			s = (node *)malloc(sizeof (node));
			s->data = i++;    // 为循环链表初始化，第一个结点为1，第二个结点为2。
			p->next = s;
			p = s;
		}
		s->next = head->next;
	}
    //head 临时变量为了构造循环链表，也可以不释放利用头节点
	free(head);

	/*返回尾节点作为HEAD*/
	return s ;
}

int main()
{
	int n = 41;
	int m = 3;
	int i;
	node *p = create(n);
	node *temp;

	m %= n;   // m在这里是等于3

    /*因为创建链表的时候返回的是尾节点，所以可以用for 循环从1开始统计*/
	while (p != p->next )/*最后一个幸存者*/
	{
		for (i = 1; i < m; i++)
		{
		    /*第1，2....M-1个人*/
			p = p->next ;
		}

        /*第m个人*/
		printf("%d->", p->next->data );

		temp = p->next ;				//删除第m个节点
		p->next = temp->next ;
		free(temp);
	}

	printf("%d\n", p->data );

	return 0;
}
/*3->6->9->12->15->18->21->24->27->30->33->36->39->1->5->10->
14->19->23->28->32->37->41->7->13->20->26->34->40->8->17->
29->38->11->25->2->22->4->35->16->31*/
