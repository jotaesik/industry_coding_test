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
		printf("���� : %s [���� ��] [�� ��] [��¶��μ�]\n", argv[0]);
		printf("���� : - ����, �� ��, ��¶��μ��� 1~99������ ���ڸ� ��������\n");
		printf("       - ���� ���� �� �� ���� ũ�� �ȵ˴ϴ�\n");
		printf("��) %s 3 90 4\n", argv[0]);
		exit(1);
	}
	for (i = 1; i < 3; i++) //����, ������ ���� 
	{
		ch = atoi(argv[i]);
		temp[i] = ch;
		if (diff(temp[i])) {
			error_print("1 ~ 99������ ���ڸ� ��������\n");
		}
	}
	if (temp[1] > temp[2]) {
		//���� ���� �� �� ���� ũ�� �ʵ��� ����
		error_print("���� ���� �� �� ���� ũ�� �ȵ˴ϴ�");
	}
	temp[0] = atoi(argv[3]);
	if (diff(temp[0]) == 0) {
		error_print("1~99������ ���ڸ� ��������\n");
	}
	googoo(temp[1], temp[2], temp[0]); //������
	return 0;
}