#include <stdio.h>
#include <windows.h>
#include <conio.h>
//C:\Users\82102\Desktop\test\Release\test.exe 3 90 4
int diff(int a) {
	if (1 <= a && a <= 99) {
		return 1;
	}
	else
		return 0;
}
void error_print(const char* s) {
	printf("%s\n", s);
}
void googoo(int a, int b, int c) {	
	int jul = 0; //줄개수
	int left = 0; //마지막줄에들어가는개수
	int how = 0;//몇부터 몇까ㅏ지를 출력해얗나다
	int reala = a;
	int line = 0;	//press any key 출력방법
	
	if (c <=4) {
		how = b - a + 1;
		jul = how / c;
		left = how % c;
		int stop = 0;//스탑체크하기
		int stop1 = 0;	//엔터체크하기
		line = line + 4;
		for (int k = 1; k <= jul; k++) {
			for (int i = 1; i < 10; i++) {
				line++;
				stop = 0;
				stop1 = 0;
				for (int j = 1; j <= c; j++) {
		
					if (j == c) {
						if ((line % 30) == 0) {
						
							printf("%-5d*%-5d=%-5d\t", a, i, a * i);
							stop = 1;
							stop1 = 1;
						}
						else {
							printf("%-5d*%-5d=%-5d\n", a, i, a * i);
						}
					}
					else {
						if ((line % 30) == 0) {
							printf("%-5d*%-5d=%-5d\t", a, i, a * i);
							stop = 1;
							stop1 = 0;
						}
						else {
							printf("%-5d*%-5d=%-5d\t", a, i, a * i);
						}
						
					}
					a++;
				}
				if (stop == 1 && stop1==1) {
					printf("press any key\n");
					system("pause>NULL");
					line = line +4;
				}
				else if(stop==1 && stop1==0) {
					printf("press any key");
					system("pause>NULL");
					line = line + 4;
				}
				else {

				}
				a = a - c;
			}
			a = k * c + reala;
			printf("\n");
		}
		for (int i = 1; i < 10; i++) {
			line++;
			stop = 0;
			stop1 = 0;
			for (int j = 1; j <= left; j++) {
				if (j == left) {
					if (line % 30 == 0) {
						printf("%-5d*%-5d=%-5d\t", a, i, a * i);
						stop = 1;
						stop1 = 1;
					}
					else {
						printf("%-5d*%-5d=%-5d\n", a, i, a * i);
					}
				}
				else {
					if (line % 30 == 0) {
						printf("%-5d*%-5d=%-5d\t", a, i, a * i);
						stop = 1;
						stop1 = 0;
					}
					else {
						printf("%-5d*%-5d=%-5d\t", a, i, a * i);
					}
					
				}
				a++;
			}
			if (stop == 1 && stop1 == 1) {
				printf("press any key\n");
				system("pause>NULL");
				line = line + 4;
			}
			else if (stop == 1 && stop1 == 0) {
				printf("press any key");
				system("pause>NULL");
				line = line + 4;
			}
			else {

			}
			a = a - left;
		}
	}

	else {	
		how = b - a + 1;
		jul = how / c;		
		left = how%c;		
		int count[99] = { 0, };
		int stop = 0;//스탑체크하기
		int stop1 = 0;	//엔터체크하기
		
		int find = 0;
		for (int i = 0; i < jul; i++) {
			int e = c / 4;
			int d = c % 4;
			for (int j = find; j < find + e; j++) {
				count[j] = 4;
			}
			find = find + e;
			count[find] = d;
			find++;
		}
		int realleft = left;
		int e = realleft / 4;
		int d = realleft % 4;
		for (int j = find; j < find + e; j++) {
			count[j] = 4;
		}
		find = find + e;
		count[find] = d;
		find++;
		line = 0;
		line = line + 4;
		
		for (int k = 0; k <find; k++) {
			for (int i = 1; i < 10; i++) {
				line++;
				stop = 0;
				stop1 = 0;
				for (int j = 0; j <count[k]; j++) {
					if (j == count[k]-1) {
						if (line % 30 == 0) {
							printf("%-5d*%-5d=%-5d\t", a, i, a * i);
							stop = 1;
							stop1 = 1;
						}
						else {
							printf("%-5d*%-5d=%-5d\n", a, i, a * i);
						}
					}
					else {
						if (line % 30 == 0) {
							printf("%-5d*%-5d=%-5d\t", a, i, a * i);
							stop = 1;
							stop1 = 0;
						}
						else {
							printf("%-5d*%-5d=%-5d\t", a, i, a * i);
						}
					}
					a++;
				}
				if (stop == 1 && stop1 == 1) {
					printf("press any key\n");
					system("pause>NULL");
					line = line + 4;
				}
				else if (stop == 1 && stop1 == 0) {
					printf("press any key");
					system("pause>NULL");
					line = line + 4;
				}
				else {

				}
				a = a - count[k];
			}
			a = a + count[k];
			printf("\n");
		}
	}
}