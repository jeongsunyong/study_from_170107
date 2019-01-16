//#study 3
//BAEKJOON10845_큐#1


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
typedef struct node {
	int data;
	struct node* link;
}node;

node* top;
node* rear;

void push(int num, int* output,int* count,int* pcnt);
void pop(int* output,int*count,int* pcnt);
void size(int* output, int* count, int pcnt);
void empty(int* output, int* count, int pcnt);
void front(int* output, int* count, int pcnt);
void back(int* output, int* count, int pcnt);

int main()
{
	int i;
	int n=0, num=0, count=0,pcnt=0; //count : 출력count , pcount : pop/push ->
	int* output;
	char order[12];
	while (1)
	{
		scanf("%d", &n);// 1<=n<=10000
		if (n >= 1 && n <= 10000)
			break;
	}
	output = (int*)malloc(sizeof(int)*n + 1);

	while (n)
	{
		int num = 0;
    
    //printf("num:%d, n:%d , order:%s, count:%d, pcnt:%d\n,output[%d-1]:%d\n", num, n, order, count, pcnt,count,output[count-1]);
    //테스트출력줄
    
		for (i = 0; i < 12; i++)
		{
			order[i] = '\0';
		}

		gets(order);


		if (strncmp(order, "push", 4) == 0)
		{
			for (i = 4; i < 12; i++)
			{
				if (isdigit(order[i])) 
				{
					num = 10 * num + (order[i] - 48);
				}
				else if (order[i] = ' ')
					continue;
				else
					break;
			}
			if (num < 1 || num>100000)
				continue;
			push(num, output, &count, &pcnt);
		}
		else if (strcmp(order, "pop") == 0)
			pop(output,&count,&pcnt);
		else if (strcmp(order, "front") == 0)
			front(output, &count,pcnt);
		else if (strcmp(order, "back") == 0)
			back(output,&count,pcnt);
		else if (strcmp(order, "size") == 0)
			size(output,&count,pcnt);
		else if (strcmp(order, "empty") == 0)
			empty(output,&count,pcnt);
		else
			continue;
		n--;
	}
	for (i = 0; i < count; i++)
	{
		printf("%d\n", output[i]);
	}
	return 0;
}

void push(int num,int* output, int* count, int* pcnt)
{
	node* new = (node*)malloc(sizeof(node));
	new->data = num;
	if (*pcnt == 0)
	{
		top = new;
		rear = new;
	}
	else
	{
		rear->link = new;
		rear = new;
	}

	(*pcnt)++;
}
void pop(int* output, int* count, int* pcnt)
{
	node* del;
	if (*pcnt == 0)
		output[*count] = -1;
	else
	{
		output[*count] = top->data;
		top = top->link;
		(*pcnt)--;
	}
	(*count)++;
}
void size(int* output, int* count, int pcnt)
{
	output[*count] = pcnt;
	(*count)++;
}
void empty(int* output, int* count, int pcnt)
{
	if (pcnt == 0)
		output[*count] = 1;
	else
		output[*count] = 0;
	(*count)++;
}
void front(int* output, int *count, int pcnt)
{
	if (pcnt == 0)
		output[*count] = -1;
	else
		output[*count] = top->data;
	(*count)++;
}
void back(int* output, int *count, int pcnt)
{
	if (pcnt == 0)
		output[*count] = -1;
	else
		output[*count] = rear->data;
	(*count)++;
}

/*
어려웠던점
1.queue를 동적할당으로 짜는데 NULL처리가 안됨.
원래 pcnt == 0으로 (큐에 있는 데이터 수 0) 분기되는 조건문을 top == NUL / rear == NULL로 짰는데
pop으로 다 데이터가 나가고 나면 NULL포인터가 되는게 아니라 0xCDCDCDCD라는 에러가뜸.
http://raid79.tistory.com/587
참고해봤는데 비주얼스튜디오에서 메모리의 초기값은 0xcd로 채워져서 이런 에러는 보통 초기화 안한 변수 이용시 생기는 문제라고함
일단 해결 못해서 조건을 pcnt==0으로 바꿔서 사용.

*/
