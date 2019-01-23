//BAEKJOON10886-덱#1

#include <stdio.h>
#include <stdlib.h>
#define MAX_ORDER_SIZE 10000
#define MAX_NUM_SIZE 100000

typedef struct dequeue {
	int data;
	struct dequeue* link_r;
	struct dequeue* link_l;
}dequeue;

dequeue* front;
dequeue* rear;
int cnt=0,remain=0;

int output[MAX_ORDER_SIZE];

void Push_front(int num)
{
	dequeue* new = (dequeue*)malloc(sizeof(dequeue));
	new->data = num;
	if (front == NULL)
	{
		front = new;
		rear = new;
		new->link_l = NULL;
		new->link_r = NULL;
	}
	else
	{
		new->link_r = front;
		front->link_l = new;
		front = new;
		new->link_l = NULL;
	}
	remain++;
}
void Push_back(int num)
{
	dequeue* new = (dequeue*)malloc(sizeof(dequeue));
	new->data = num;
	if (rear == NULL)
	{
		front = new;
		rear = new;
		new->link_l = NULL;
		new->link_r = NULL;
	}
	else
	{
		new->link_l = rear;
		rear->link_r = new;
		rear = new;
		new->link_r = NULL;
	}
	remain++;
}
int Pop_front()
{
	if (front == NULL) 
	{
		output[cnt] = -1;
	}
	else
	{
		output[cnt] = front->data;
		if (front == rear)
		{
			front = NULL;
			rear = NULL;
		}
		else
		{
			front = front->link_r;
			front->link_l = NULL;
		}
		remain--;
	}
	cnt++;
}
int Pop_back()
{
	if (rear == NULL)
	{
		output[cnt] = -1;
	}
	else
	{
		output[cnt] = rear->data;
		if (rear == front)
		{
			rear = NULL;
			front = NULL;
		}
		else
		{
			rear = rear->link_l;
			rear->link_r = NULL;
		}
		remain--;
	}
	cnt++;
}
void Size()
{
	if (remain >= 0) {
		output[cnt] = remain;
		cnt++;
	}
}
void Empty()
{
	if (remain == 0)
		output[cnt] = 1;
	else
		output[cnt] = 0;
	cnt++;
}
void Prtfront()
{
	if (front == NULL)
		output[cnt] = -1;
	else
		output[cnt] = front->data;
	cnt++;
}
void Prtback()
{
	if (rear == NULL)
		output[cnt] = -1;
	else
		output[cnt] = rear->data;
	cnt++;
}

int main()
{
	int i, N, num;
	char order[20];
	while (1)
	{
		scanf("%d", &N);
		if (N <= 10000 && N >= 1)
			break;
	}
	while (N)
	{
		order[0] = '\0';
		scanf("%s", order);
		if (strcmp(order, "push_front") == 0)
		{
			scanf("%d", &num);
			if (num < 1 || num>100000)
				continue;
			Push_front(num);
		}
		else if (strcmp(order, "push_back") == 0)
		{
			scanf("%d", &num);
			if (num < 1 || num>100000)
				continue;
			Push_back(num);
		}
		else if (strcmp(order, "pop_front") == 0)
			Pop_front();
		else if (strcmp(order, "pop_back") == 0)
			Pop_back();
		else if (strcmp(order, "size") == 0)
			Size();
		else if (strcmp(order, "empty") == 0)
			Empty();
		else if (strcmp(order, "front") == 0)
			Prtfront();
		else if (strcmp(order, "back") == 0)
			Prtback();
		N--;
	}
	for (i = 0; i < cnt; i++)
	{
		printf("%d\n", output[i]);
	}
}
