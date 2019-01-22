//BAEKJOON1260_큐#2.c
//DFS & BFS
//시간초과

#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 1000
#define MAX_EDGE 10000
int i;
typedef struct stack {
	int data;
	struct stack* link;
}stack;

typedef struct g_node {
	int vertex;
	struct g_node* link_n;
}g_node;
g_node* G[MAX_VERTEX];
g_node* last[MAX_VERTEX];
g_node* first[MAX_VERTEX];
int visited[MAX_VERTEX];
int output[MAX_VERTEX];
stack *top = NULL;

void push_s(int value)
{
	stack* new = (stack*)malloc(sizeof(stack));
	new->data = value;
	new->link = top;
	top = new;
}
int pop_s()
{
	int tmp;
	if (top == NULL)
	{
		return -1;
	}
	else
	{
		tmp = top->data;
		top = top->link;
		return tmp;
	}
}
void init(int N)
{
	for (i = 1; i <= N; i++)
	{
		G[i] = first[i];
		visited[i] = 0;
		output[i - 1] = 0;
		while (pop_s() != -1)
			pop_s();
	}
}
void DFS(int V,int N)
{
	int v=V;
	int cnt=0;
	int tmp=0;
	push_s(V);
	while (cnt != N)
	{
		if (G[v] == NULL)
		{
		v = pop_s();
		}
		else if (G[v] != NULL)
		{
			if (visited[v] == 0)
			{
				visited[v] = 1;
				push_s(v);
				output[cnt] = v; 
				if (G[G[v]->vertex] != NULL && visited[G[v]->vertex] == 0)
				{
					tmp = v;
					v = G[v]->vertex;
				}
				else
				{
					v = pop_s();
				}
				cnt++;
			}
			else
			{
				if (G[v]->link_n != NULL)//
				{
					while (1)
					{
						if (G[v]->link_n != NULL)
							G[v] = G[v]->link_n;
						else
							break;
						if (visited[G[v]->vertex] == 0)
						{
							push_s(v);
							v = G[v]->vertex;
							break;
						}
					}
				}
				else
				{
					v = pop_s();
				}
			}
		}
	}

}
void BFS(int V, int N)
{
	int v = V;
	int cnt = 1;
	int tmp = 0;
	int pcnt=0,level = 0;
	int in[MAX_VERTEX] = { 0 };
	int d[MAX_VERTEX] = { 0 };
	output[0] = v;
	in[v] = 1;
	while(cnt != N)
	{
		if (visited[v] == 0)
		{
			while (G[v] != NULL && visited[v] == 0)
			{
				if (in[G[v]->vertex] == 0)
				{
					in[G[v]->vertex] = 1;
					output[cnt] = G[v]->vertex;
					d[G[v]->vertex] = level + 1;
					cnt++;

				}
				G[v] = G[v]->link_n;
			}
			if (G[v] == NULL)
				visited[v] = 1;
		}
		if (G[v] != NULL&&pcnt<=level)
		{
			if(d[v]<=d[G[v]->vertex])
			{
				push_s(v);
				tmp = G[v]->vertex;
				G[v] = G[v]->link_n;
				v = tmp;
				pcnt++;
			}
			else
			{
				G[v] = G[v]->link_n;
			}
		}
		else if (G[v] == NULL || pcnt>level)
		{
			G[v] = first[v];
			v = pop_s();
			pcnt--;
			if (v == -1)
			{
				v = V;
				level++;
				pcnt++;
			}
		}
	}
}

int main()
{
	int N, M, V, v1, v2;
	g_node *new1, *new2;
	while (1)
	{
		scanf("%d %d %d", &N, &M, &V);
		if (N <= 1000 && N >= 1 && M >= 1 && M <= 10000 && V < N && V >= 0 && M <= N * (N - 1) / 2)
			break;
	}
	for (i = 0; i < M; i++)
	{
		scanf("%d %d", &v1, &v2);
		if (v1 <= N && v1 > 0 && v2 <= N && v2 > 0 && v1 != v2)
		{
			new1 = (g_node*)malloc(sizeof(g_node));
			new2 = (g_node*)malloc(sizeof(g_node));
			new1->vertex = v2;
			new2->vertex = v1;
			if (G[v1] != NULL)
			{
				last[v1]->link_n = new1;
				last[v1] = new1; 
				new1->link_n = NULL;
			}
			else
			{
				G[v1] = new1;
				last[v1] = new1;
				first[v1] = new1;
				new1->link_n = NULL;
		
			}
			if (G[v2] != NULL)
			{
				last[v2]->link_n = new2;
				last[v2] = new2; 
				new2->link_n = NULL;
			}
			else
			{
				G[v2] = new2;
				last[v2] = new2;
				first[v2] = new2;
				new2->link_n = NULL;
			}
		}
	}
	DFS(V,N);
	for (i = 0; i < N; i++)
	{
		printf("%d ",output[i]);
	}
	init(N);
	printf("\n");
	BFS(V, N);
	for (i = 0; i < N; i++)
	{
		printf("%d ", output[i]);
	}
	return 0;
}
