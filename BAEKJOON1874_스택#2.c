//#study2
//BAEKJOON1874_스택수열

#include <stdio.h>
#include <stdlib.h>

int stack[100001];
int i,j, input = 0, result = 1, count = 0, max = 0, first = 1;
int pcount=0;
//i:루프변수, input: 입력, result : No 판단, count:+,-출력갯수(pop/push연산시++)
//max:입력값중최댓값,first:초기입력시 1회 더루프하기 위한 변수
void push(int input, char* plusminus); //PUSH연산
void pop(char* plusminus); //pop연산

int main()
{
	int n;  //첫줄정수값변수
	while (1) //n 10만이하,1이상
	{
		scanf("%d", &n);
		if (n >= 1 && n <= 100000)
			break;
	}
	char plusminus[200001]; //+,- 문자입력동적할당
	push(1, plusminus); //1미리넣어줌 (top 처음에 nullpoint라서)
	while (n) //n회 반복
	{
		if (input >= max) //(이전)입력값이 지금까지 받았던 값보다 크면 max증가
			max = input + 1;
		scanf("%d", &input); //입력
		if (stack[0] < input) //top이 입력값보다 작으면
		{
			for (i = max + first; i <= input; i++) //지금까지받았던 값 이후부터(초기값의경우 +1)PUSH
			{
				push(i, plusminus);
			}
			pop(plusminus);//입력값 POP
		}
		else if (stack[0] == input)//입력값과 top이 같은경우
		{
			pop(plusminus);//입력값 POP
		}
		else
		{
			result = 0; //어느경우에도 해당하지 않으면 NO(result 0)
		}
		n--; //n회 반복이므로 n값 감소
		first = 0;//초기 1회 이후 X
	}
	if (result)//result 초기값이면(0으로 변경 안됬으면)
	{
		for (i = 0; i < count; i++) //+,-문자열 출력
			printf("%c\n", plusminus[i]);
	}
	else//result 0이면 No출력
		printf("NO\n");
	return 0;
}
void push(int input, char* plusminus)
{
	if (pcount != 0)
	{
		for (j = pcount; j >= 0; j--)
		{
			stack[j + 1] = stack[j];
		}
	}
	stack[0] = input;
	*(plusminus + count) = '+'; //+문자열 저장
	count++;//연산횟수 count(맨 마지막에 연산 횟수만큼 +,-출력)
	pcount++;
}
void pop(char* plusminus)
{

	for (j = 0; j <= pcount; j++)
	{
		stack[j] = stack[j + 1];
	}
	*(plusminus + count) = '-'; //-문자열저장
	count++;
	pcount--;
}

/*
어려웠던점 / 시간 많이소요됬던 부분:
1.처음에 동적할당으로 짰는데 실행결과는 정상적인데 
백준 홈페이지에서 정답이 안뜨고 자꾸 런타임에러가 떴었음
->일단 배열로 고쳐서 품
다음 문제에서도 동적할당으로 짰을 때 잘 안됬었는데 동적할당 공부 필요할듯
2.처음에 짰을 때 
if (stack[0] < input) //top이 입력값보다 작으면
		{
			for (i = max + first; i <= input; i++) //지금까지받았던 값 이후부터(초기값의경우 +1)PUSH
			{
				push(i, plusminus);
			}
  이부분의i초기값 조건을
  popcount(pop 하게되면 그 다음 push까지 거리가 늘어나게되니까) + top(현재 남아있는 수 중 가장 큰수)+first 로 했었다가
  거의 모든 경우가 다 정상적으로 출력됬어서 뭐가 문제지 하고 헤맸었는데
  이경우에 (n=4) 2 3 1 4  -> 앞의 입력값이 모두 pop이 되는 경우 만족 X해서 안되는거였음.
  이런 문제를 풀때는 너무 복잡하게 모든 예시를 생각해서 변수에 적용하지  전체에 적용되는 값 하나를 잘 생각해보는게 좋을 것 같다
  
*/
