/*
Question]  26진법 산술연산 함수를 구현하시오. (4 Hour)
A B C------Z
0 1 2 ------ 25
65			90
하나의 26진수는 127자리를 넘지 않고, 숫자개수는 100개를 넘지 않는다.
주어진 question문자열을 계산하여 answer에 저장하라
(결과가 음수일 경우 문자열의 처음에 '-'로 표기할것)
외부 함수는 사용할수 없다. (#include를 통한 외부 함수 사용 금지)
ex)question
CBA + GRDAGSDZFFDAFERFEFDAFAFGADFA - ERADFDAZDFWEQQ + FAFDCVARFERAFDFAFADFDAF
// DO NOT ANY INCLUDE
*/
#define STRING_SIZE 12800
#define DEPTH_SIZE 127
#define PARAM_SIZE 100
#include <stdio.h>
int number[PARAM_SIZE][DEPTH_SIZE];	//숫자보관
char sign[PARAM_SIZE];	//기호보관
int numberPARAM_SIZE;
int numbersign;
int numberlength[PARAM_SIZE];
int answernumber[STRING_SIZE];
void remake(char answer[STRING_SIZE], const char question[STRING_SIZE]) {
	int bcount=0; 	//기호카운터
	int acount=0; 	//숫자카운터 몇개나오는지
	int acount1=0; 	//2번ㅂ째인덱스
	int  numberlengthcount = 0;	//숫자길이
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
	//i*2	i*2+1더하기
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
	//i*2	i*2+1빼기
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