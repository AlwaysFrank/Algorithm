//n����ΧȦ��������m���У����ʣ�µ��Ǽ��ţ�
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}node;

/*����N��������ѭ������*/
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
			s->data = i++;    // Ϊѭ�������ʼ������һ�����Ϊ1���ڶ������Ϊ2��
			p->next = s;
			p = s;
		}
		s->next = head->next;
	}
    //head ��ʱ����Ϊ�˹���ѭ������Ҳ���Բ��ͷ�����ͷ�ڵ�
	free(head);

	/*����β�ڵ���ΪHEAD*/
	return s ;
}

int main()
{
	int n = 41;
	int m = 3;
	int i;
	node *p = create(n);
	node *temp;

	m %= n;   // m�������ǵ���3

    /*��Ϊ���������ʱ�򷵻ص���β�ڵ㣬���Կ�����for ѭ����1��ʼͳ��*/
	while (p != p->next )/*���һ���Ҵ���*/
	{
		for (i = 1; i < m; i++)
		{
		    /*��1��2....M-1����*/
			p = p->next ;
		}

        /*��m����*/
		printf("%d->", p->next->data );

		temp = p->next ;				//ɾ����m���ڵ�
		p->next = temp->next ;
		free(temp);
	}

	printf("%d\n", p->data );

	return 0;
}
/*3->6->9->12->15->18->21->24->27->30->33->36->39->1->5->10->
14->19->23->28->32->37->41->7->13->20->26->34->40->8->17->
29->38->11->25->2->22->4->35->16->31*/
