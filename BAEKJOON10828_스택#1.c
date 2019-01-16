//sutdy #1 
//##BACKJOON10182_스택 코드


#include <stdio.h>
#include <string.h>
#include <ctype.h>

int i, j, count = 0; //i,j : 루프변수 count : 저장값(현재 스택에 들어있는 data 갯수)
int stack[10001]; //스택
char order[12]; //명령어입력저장.
int output[10001];//출력값저장배열
int ocnt = 0;// output이 입력될때마다 증가하는 변수. 마지막에 output 프린트를 위한 변수.

void push(int x);
void pop();
void size();
void empty();
void top();

int main()
{
	int n; //입력갯수
	while (1)
	{
		scanf("%d", &n);
		if (n >= 0 && n <= 10000) // 0<=n<=10000
			break; //조건만족시값저장
	}
	while (n)
	{
		int x = 0;
		for (i = 0; i < 12; i++) //order 초기화
		{
			order[i] = '\0';
		}
		gets(order); //명령줄 입력
		if (strncmp(order, "push", 4) == 0) //push명령어일경우
		{
			for (i = 4; i < 12; i++)
			{
				if (isdigit(order[i])) //정수일경우 값 저장 (i++자릿수늘어남,char형이기때문에 -48해서 정수값으로)
				{
					x = 10 * x + (order[i] - 48);
				}
				else if (order[i] = ' ') //공백일경우 PASS
					continue;
				else
					break;
			}
			if (x < 1 || x>100000)
				continue;
			push(x);
		}
		else if (strncmp(order, "pop", 4) == 0)
		{
			pop();
		}
		else if (strcmp(order, "size") == 0)
		{
			size();
		}
		else if (strcmp(order, "empty") == 0)
		{
			empty();
		}
		else if (strcmp(order, "top") == 0)
		{
			top();
		}
		else
			continue;
		n--;
	}
	for (i = 0; i<ocnt; i++)
	{
		printf("%d\n", output[i]);
	}
}

void push(int x)
{
	for (i = count; i >= 0; i--)
	{
		stack[i + 1] = stack[i]; //뒤로 한칸씩. 가장 최근 데이터가 배열0번으로.
	}
	stack[0] = x;
	count++;
}
void pop()
{
	if (count > 0) //1개 이상 들어있을 경우
	{
		output[ocnt] = stack[0];
		ocnt++;
		count--;
		for (i = 0; i <= count; i++) //0번을 top으로 놓기 위해서 자리이동
		{
			stack[i] = stack[i + 1];
		}
	}
	else if (count == 0) //empty일때.
	{
		output[ocnt] = -1;
		ocnt++;
	}
}
void size()
{
	output[ocnt] = count;
	ocnt++;
}
void empty()
{
	if (count == 0)
		output[ocnt] = 1;
	else
		output[ocnt] = 0;
	ocnt++;
}
void top()
{
	if (count == 0)
		output[ocnt] = -1;
	else
		output[ocnt] = stack[0];
	ocnt++;
}



/* 
코드 짜면서 어려웠던 점(시간많이걸렸던부분) : 
1.자꾸 시간 초과가 떴는데
버퍼 비우는 함수 (fflush() fseek()같은 함수들에 소요 시간 多
while(getchar())가 비슷하게 이용된다고 함.
2. 문제에 나와있는 숫자는 제대로 나오는데 10000 입력했다가 2 입력하면 안되는 경우가 종종 있어
확인해보니 배열 비우는 함수를 써도 끝부분이 초기화가 안되서 2가 20000이런식으로 계속 저장됨
그래서 for문으로 전체 명령받는 배열 다 공백문자 넣어줌.

*/
