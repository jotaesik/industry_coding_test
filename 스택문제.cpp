extern void my_push(int s);
extern int my_pop(int s);
extern void enqueue(void);
#define SIZE 10000	//맨끝에서부터 반환하니깐 내림차순이되어야한다.
int finish[10];		//각끝
void define1() {
	finish[0] = SIZE;
	for (int i = 1; i < 10; i++) {
		finish[i] = 0;
	}
}
void divide(int end,int a, int b,int c,int d) {		
	for (int i = 0; i < finish[end]; i++) {
		if (my_pop(end) > c-1) {
			my_push(a);
			finish[a]++;
		}
		else {
			my_push(b);
			finish[b]++;
		}
	}
	finish[end] = 0;
}
void sort(int a) {
	int b = 1;
	for (int i = 0; i < a; i++) {
		b = b * 2;
	}
	int c = 1024 - b;
	for (int i = 0; i < finish[11 - a]; i++) {
		if (my_pop(11 - a) > c) {
			my_push(1);
			if (my_pop(11 - a) > c + 1) {
				my_push(0);
			}
			else {
				my_push(10 - a);
				finish[10 - a]++;
			}
		}
		else {
			my_push(10 - a);
		}
	}
}
void test_main(void){
	define1();
	divide(0, 1, 2,512,1);
	divide(1, 0, 3,768,2);
	divide(0, 1, 4, 896,3);
	divide(1, 0, 5, 960,4);
	divide(0, 1, 6, 992,5);
	divide(1, 0, 7, 1008,6);
	divide(0, 1, 8, 1016,7);
	divide(1, 0, 9, 1020,8);	//분기가 다 되었어.
	//하나로뭉치기0기준
	sort(2);
	for (int i = 2; i <= 11; i++) {
		for (int j = 2; j <= i; j++) {
			sort(j);
		}
	}
	for (int i = 0; i < SIZE; i++) {
		my_pop(0);
		enqueue();
	}

}



