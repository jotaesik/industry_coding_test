/*
Question]  26���� ������� �Լ��� �����Ͻÿ�. (4 Hour)
A B C------Z
0 1 2 ------ 25
65			90
�ϳ��� 26������ 127�ڸ��� ���� �ʰ�, ���ڰ����� 100���� ���� �ʴ´�.
�־��� question���ڿ��� ����Ͽ� answer�� �����϶�
(����� ������ ��� ���ڿ��� ó���� '-'�� ǥ���Ұ�)
�ܺ� �Լ��� ����Ҽ� ����. (#include�� ���� �ܺ� �Լ� ��� ����)
ex)question
CBA + GRDAGSDZFFDAFERFEFDAFAFGADFA - ERADFDAZDFWEQQ + FAFDCVARFERAFDFAFADFDAF
// DO NOT ANY INCLUDE
*/
#define STRING_SIZE 12800
#define DEPTH_SIZE 127
#define PARAM_SIZE 100
#include <stdio.h>
int number[PARAM_SIZE][DEPTH_SIZE];	//���ں���
char sign[PARAM_SIZE];	//��ȣ����
int numberPARAM_SIZE;
int numbersign;
int numberlength[PARAM_SIZE];
int answernumber[STRING_SIZE];
void remake(char answer[STRING_SIZE], const char question[STRING_SIZE]) {
	int bcount=0; 	//��ȣī����
	int acount=0; 	//����ī���� ���������
	int acount1=0; 	//2����°�ε���
	int  numberlengthcount = 0;	//���ڱ���
	for (int i = 0; i < STRING_SIZE; i++) {
		if (question[i] == '+' || question[i] == '-') {
			sign[bcount] = question[i];
			bcount++;
			acount++;
			numberlength[numberlengthcount] = acount1;
			numberlengthcount++;
			acount1 = 0;
		}
		else if ('A' <= question[i] && 'Z' >= question[i]) {
			number[acount][acount1] = question[i]-65;
			acount1++;
		}
		else {
			break;
		}
	}

	numberPARAM_SIZE = acount;
	numbersign = bcount;
	for (int i = 0; i < numberPARAM_SIZE; i++) {
		for (int j = 0; j < numberlength[i]; j++) {
			number[i][DEPTH_SIZE-j] = number[i][numberlength[i]-j];
		}
		for (int j = 0; j < DEPTH_SIZE - numberlength[i]; j++) {
			number[i][j] = 0;
		}
	}
	//printf("%d %d\n", bcount, acount);
}
int* add(int x) {
	//i*2	i*2+1���ϱ�
	for (int i = 0; i < DEPTH_SIZE; i++) {
		answernumber[i] = number[x * 2][i] + number[x * 2 + 1][i];
	}
	for (int i = DEPTH_SIZE - 1; i >= 1; i--) {
		if (answernumber[i] > 25) {
			answernumber[i - 1] = answernumber[i - 1] + 1;
		}
	}
	for (int i = 0; i < STRING_SIZE; i++) {
		//printf("%d", answernumber[i]);
		//answer[i] = answernumber[i]+'0';
	}
	return answernumber;
}
int* sub(int x) {
	//i*2	i*2+1����
	for (int i = 0; i < DEPTH_SIZE; i++) {
		answernumber[i] = number[x * 2][i] -number[x * 2 + 1][i];
	}
	for (int i = DEPTH_SIZE - 1; i >= 1; i--) {
		if (answernumber[i]<0) {
			answernumber[i - 1] = answernumber[i - 1]-1;
			answernumber[i] = answernumber[i] + 25;
		}
	}
	for (int i = 0; i < STRING_SIZE; i++) {
		//printf("%d", answernumber[i]);
		//answer[i] = answernumber[i]+'0';
	}
	return answernumber;
}
void test_main(char answer[STRING_SIZE], const char question[STRING_SIZE])
{
	remake(answer, question);
	for (int i = 0; i < numbersign; i++) {
		if (sign[i] == '+') {
			add(i*2);
		}
		else if(sign[i]=='-') {//sign=='-'
			sub(i * 2);
		}
		else {
			break;
		}
	}
	for (int i = 0; i < STRING_SIZE; i++) {
		//printf("%d", answernumber[i]);
		//answer[i] = answernumber[i]+'0';
	}
	
	
	


}