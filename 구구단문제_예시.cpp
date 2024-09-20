#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
extern int diff(int a);
extern void error_print(const char* s);
extern void googoo(int a, int b, int c);
int main(int argc, char* argv[])	
{
	system("mode con: cols=120 lines=30");
	int i, ch, temp[3];
	if (argc != 4)
	{
		printf("사용법 : %s [시작 단] [끝 단] [출력라인수]\n", argv[0]);
		printf("주의 : - 시작, 끝 단, 출력라인수는 1~99까지의 숫자만 넣으세요\n");
		printf("       - 시작 단이 끝 단 보다 크면 안됩니다\n");
		printf("예) %s 3 90 4\n", argv[0]);
		exit(1);
	}
	for (i = 1; i < 3; i++) //시작, 끝단의 제한 
	{
		ch = atoi(argv[i]);
		temp[i] = ch;
		if (diff(temp[i])) {
			error_print("1 ~ 99까지의 숫자만 넣으세요\n");
		}
	}
	if (temp[1] > temp[2]) {
		//시작 단이 끝 단 보다 크지 않도록 제한
		error_print("시작 단이 끝 단 보다 크면 안됩니다");
	}
	temp[0] = atoi(argv[3]);
	if (diff(temp[0]) == 0) {
		error_print("1~99까지의 숫자만 넣으세요\n");
	}
	googoo(temp[1], temp[2], temp[0]); //구구단
	return 0;
}