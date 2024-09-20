#include <stdio.h>
#include <math.h>
#include <time.h>
#include <limits.h>
static unsigned int a = 1;   //난수기본값
extern int process(int command, int param1, int param2);
void get_school_position(int school_index, int* posX, int* posY);
void get_student_position(int student_index, int* posX, int* posY);
void set_student_school(int student_index, int school_index);
static int counttry = 0;   //10번째인가?
static double allsum = 0;   //10번째 이후 총합비교해보자
int srand(unsigned int seed) {
    return seed;
}
int rand(void) {
    return(((a = a * 214013L + 2531011L) >> 16) & 0x7fff);
}
double dct[10000] = { 0, }; //중심점과 학생과의거리
int dcti[10000] = { 0, };  //중심점과 학생과의 거리 index정리
double dcsa[10000] = { 0, };    //학생과 학교a와의거리
double dcsb[10000] = { 0, };    //b
double dcsc[10000] = { 0, };    //c
int indexorder[10000] = { 0, };   //우선순위 개수(겹치는개수)
//int ordersame[8] = { 0, };  //최소1개에서 최대8개전부임   //우선순위가 겹칠때 index저장 //구지필요없을지도? 
double calsame[4][8] = { 0, }; //ordersame배열 사용보다는 index.a.b.c거리와 살짝 벡터같은 느낌으로
int ss[10000];  //학생이 어느 학교에 배정되는가 a-0 b-1 c-2
int as = 0;     //a학교배정
int bs = 0;     //b학교배정
int cs = 0;     //c학교배정
int sx, sy; //학교위치
int tx, ty; //학생위치
int cx = 0; //학교중심점위치x
int cy = 0; //학교중심점위치y
double sum = 0; //run될때 거리의합

int number = 0; //단순계산변수
double min = 0; //최솟값설정ㄹ
int same = 0;  //우선순위 비교할때 index역할 
int cal = 0; //indexorder가 최대일때 계산해주자
double arr[32];     //calsame2차원을 1차원으로 옮기기
double arr1[32];  //arr옮기기복사본이지만 인덱스(-1)값 제외
double arr2[32];  //arr1 오름차순
int index1 = 0; //디버깅 //indexorder가 1인경우에 즉 겹치는 경우가없을때.
int index11 = 0;    //a학교
int index12 = 0;    //b학교
int index13 = 0;    //c학교배치인원
int index2 = 0; //indexorder가 2이상인경우에
int index21 = 0;    //a학교배치인원
int index22 = 0;    //b학교
int index23 = 0;    //c학교
void order(double arr2[], int count) {   //오름차순정렬
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count; j++) {
            if (arr2[i] < arr2[j]) {
                double temp = arr2[i];
                arr2[i] = arr2[j];
                arr2[j] = temp;
            }
        }
    }
}
double orderclear(int cal) {    //우선순위가 2이상 cal과 같을때 정리해보자
    min = 0;
    int count = 0;  //최대 4*8로 32경우가 잇지만,index,a,b,c 그리고 겹칠수잇는경우의 수 8가지
    for (int i = 0; i < 32; i++) {
        arr[i] = -1;
    }   //초기화
    for (int y = 0; y < cal; y++) {
        for (int x = 0; x < 4; x++) {   //2차원을 1차원으로 정렬
            int z = y * 4 + x;
            if (z % 4 == 0) {
                arr[z] = -1;
            }
            else {
                arr[z] = calsame[x][y]; //인덱스제거하기
                arr1[count] = arr[z];
                arr2[count] = arr[z];
                count++;
            }
        }
    }
    int m = 0, n = 0;   //단순변수
    int count1 = count; //헷갈리지않기위해서
    for (int i = 0; i < cal; i++) { //찾아야할 min값은 cal개수만큼
        for (int j = 0; j < count; j++) {
            order(arr2, count1);    //계속해서 새로고침 이미 사용된 index값들은 필요없으므로 갱신
            double least = arr2[0];  //첫값이 무조건 최솟값
            for (int k = 0; k < count; k++) {
                if (arr[k] == least) {  //이 최소값이 어디를 가리키는걸까
                    m = k % 3;      //학교위치
                    n = k / 3;      //인덱스위치
                }
            }
            if (m == 0) {   //학교가a이다
                if (as >= 3500) {    //만약 a인원수가 꽉찼으면
                    arr2[0] = 1000000;  //사용불가
                    if (arr2[n * 3 + 1] > arr2[n * 3 + 2]) {    //b와c의비교 b>c
                        if (bs >= 3500) {   //b도꽉찼으면
                            index23++;  //강제로c가야지
                            cs++;
                            ss[n] = 2;
                            set_student_school(n, 2);
                            least = arr2[n * 3 + 2];    //least값 변경
                            min = min + least;
                            arr2[n * 3] = 1000000;  //이쪽 인덱스를 가진것들 다못씀 
                            arr2[n * 3 + 1] = 1000000;
                            arr2[n * 3 + 2] = 1000000;
                            break;
                        }
                        else {  //b가 자리가있다면
                            index22++;
                            bs++;
                            ss[n] = 1;
                            set_student_school(n, 1);
                            least = arr2[n * 3 + 1];
                            min = min + least;
                            arr2[n * 3] = 1000000;
                            arr2[n * 3 + 1] = 1000000;
                            arr2[n * 3 + 2] = 1000000;
                            break;
                        }
                    }



                    else {  //c>b
                        if (cs >= 3500) {   //c도꽉찼으면
                            index22++;  //강제로b가야지
                            bs++;
                            ss[n] = 1;
                            set_student_school(n, 1);
                            least = arr2[n * 3 + 1];    //least값 변경
                            min = min + least;
                            arr2[n * 3] = 1000000;  //이쪽 인덱스를 가진것들 다못씀 
                            arr2[n * 3 + 1] = 1000000;
                            arr2[n * 3 + 2] = 1000000;
                            break;
                        }
                        else {  //c가 자리가있다면
                            index23++;
                            cs++;
                            ss[n] = 2;
                            set_student_school(n, 2);
                            least = arr2[n * 3 + 2];
                            min = min + least;
                            arr2[n * 3] = 1000000;
                            arr2[n * 3 + 1] = 1000000;
                            arr2[n * 3 + 2] = 1000000;
                            break;
                        }
                    }
                }
                else {  //a가 자리가있다면
                    as++;
                    ss[n] = 0;
                    set_student_school(n, 0);
                    index21++;
                    min = min + least;
                    arr2[n * 3] = 1000000;
                    arr2[n * 3 + 1] = 1000000;
                    arr2[n * 3 + 2] = 1000000;
                    break;
                }
            }
            else if (m == 1) {
                if (bs >= 3500) {
                    arr2[j] = 1000000;
                    if (arr2[n * 3] > arr2[n * 3 + 2]) {    //a>c
                        if (as >= 3500) {
                            index23++;
                            cs++;
                            ss[n] = 2;
                            set_student_school(n, 2);
                            least = arr2[n * 3 + 2];
                            min = min + least;
                            arr2[n * 3] = 1000000;
                            arr2[n * 3 + 1] = 1000000;
                            arr2[n * 3 + 2] = 1000000;
                            break;
                        }
                        else {
                            index21++;
                            as++;
                            ss[n] = 0;
                            set_student_school(n, 0);
                            least = arr2[n * 3];
                            min = min + least;
                            arr2[n * 3] = 1000000;
                            arr2[n * 3 + 1] = 1000000;
                            arr2[n * 3 + 2] = 1000000;
                            break;
                        }
                    }
                    else {      //c>a
                        if (cs >= 3500) {
                            index21++;
                            as++;
                            ss[n] = 0;
                            set_student_school(n, 0);
                            least = arr2[n * 3];
                            min = min + least;
                            arr2[n * 3] = 1000000;
                            arr2[n * 3 + 1] = 1000000;
                            arr2[n * 3 + 2] = 1000000;
                            break;
                        }
                        else {
                            index23++;
                            cs++;
                            ss[n] = 2;
                            set_student_school(n, 2);
                            least = arr2[n * 3 + 2];
                            min = min + least;
                            arr2[n * 3] = 1000000;
                            arr2[n * 3 + 1] = 1000000;
                            arr2[n * 3 + 2] = 1000000;
                            break;
                        }
                    }
                }
                else {  //b학교에 자리있을때
                    bs++;
                    ss[n] = 1;
                    min = min + least;
                    set_student_school(n, 1);
                    index22++;
                    arr2[n * 3] = 1000000;
                    arr2[n * 3 + 1] = 1000000;
                    arr2[n * 3 + 2] = 1000000;
                    break;
                }
            }






            else {  //c학교
                if (cs >= 3500) {
                    arr2[j] = 1000000;
                    if (arr2[n * 3] > arr2[n * 3 + 1]) {    //a>b
                        if (as >= 3500) {
                            index22++;
                            bs++;
                            set_student_school(n, 1);
                            least = arr2[n * 3 + 1];
                            min = min + least;
                            arr2[n * 3] = 1000000;
                            arr2[n * 3 + 1] = 1000000;
                            arr2[n * 3 + 2] = 1000000;
                            break;
                        }
                        else {
                            index21++;
                            as++;
                            set_student_school(n, 0);
                            least = arr2[n * 3];
                            min = min + least;
                            arr2[n * 3] = 1000000;
                            arr2[n * 3 + 1] = 1000000;
                            arr2[n * 3 + 2] = 1000000;
                            break;
                        }
                    }
                    else {  //b>a
                        if (bs >= 3500) {
                            index21++;
                            as++;
                            set_student_school(n, 0);
                            least = arr2[n * 3];
                            min = min + least;
                            arr2[n * 3] = 1000000;
                            arr2[n * 3 + 1] = 1000000;
                            arr2[n * 3 + 2] = 1000000;
                            break;
                        }
                        else {
                            index22++;
                            bs++;
                            set_student_school(n, 1);
                            least = arr2[n * 3 + 1];
                            min = min + least;
                            arr2[n * 3] = 1000000;
                            arr2[n * 3 + 1] = 1000000;
                            arr2[n * 3 + 2] = 1000000;
                            break;
                        }
                    }
                }
                else {
                    cs++;
                    ss[n] = 2;
                    min = min + least;
                    set_student_school(n, 2);
                    index23++;
                    arr2[n * 3] = 1000000;
                    arr2[n * 3 + 1] = 1000000;
                    arr2[n * 3 + 2] = 1000000;
                    break;
                }
            }
        }
    }
    return min;
}
void run_contest(void)
{
    for (int i = 0; i < 10000; i++) {   //관련변수초기화
        indexorder[i] = 0;
        dcsa[i] = 0;
        dcsb[i] = 0;
        dcsc[i] = 0;
        dcti[i] = 0;
        dct[i] = 0;
        ss[i] = -1;
    }
    as = 0;
    bs = 0;
    cs = 0;
    sx = 0;
    sy = 0;
    tx = 0;
    ty = 0;
    cx = 0;
    cy = 0;
    sum = 0;
    index1 = 0;
    index2 = 0;
    index11 = 0;
    index12 = 0;
    index13 = 0;
    index21 = 0;
    index22 = 0;
    index23 = 0;
    clock_t start1, end1;   //시간측정
    start1 = clock();
    for (int i = 0; i < 3; i++) {   //학교중점구하기
        get_school_position(i, &sx, &sy);
        cx = cx + sx;
        cy = cy + sy;
    }
    cx = cx / 3;
    cy = cy / 3;
    for (int i = 0; i < 10000; i++) {   //중심점과 학생들 거리구하기
        get_student_position(i, &tx, &ty);
        dct[i] = sqrt(pow(tx - cx, 2) + pow(ty - cy, 2));
    }
    for (int i = 0; i < 10000; i++) {   //인덱스정리 우선순위는?
        number = 0;
        for (int j = 0; j < 10000; j++) {
            if (dct[i] < dct[j]) {
                number++;
            }
        }
        dcti[i] = number;
    }

    for (int i = 0; i < 10000; i++) {
        get_school_position(0, &sx, &sy);
        get_student_position(i, &tx, &ty);
        dcsa[i] = sqrt(pow(tx - sx, 2) + pow(ty - sy, 2));
    }
    for (int i = 0; i < 10000; i++) {
        get_school_position(1, &sx, &sy);
        get_student_position(i, &tx, &ty);
        dcsb[i] = sqrt(pow(tx - sx, 2) + pow(ty - sy, 2));
    }
    for (int i = 0; i < 10000; i++) {
        get_school_position(2, &sx, &sy);
        get_student_position(i, &tx, &ty);
        dcsc[i] = sqrt(pow(tx - sx, 2) + pow(ty - sy, 2));
    }
    for (int i = 0; i < 10000; i++) {       //우선순위구별하는법 
        for (int j = 0; j < 10000; j++) {
            if (dcti[j] == i) {
                indexorder[i]++;
            }
        }
    }
    min = 0;    //최솟값 초기화
    for (int i = 9999; i >= 0; i--) { //가장멀리있는아이부터배치
        same = 0;
        cal = 0;
        for (int i = 0; i < 4; i++) {   //사용전 초기화
            for (int j = 0; j < 8; j++) {
                calsame[i][j] = 0;
            }
        }
        for (int j = 0; j < 10000; j++) {
            if (dcti[j] == i) {
                if (indexorder[i] == 1) { //우선순위가 1개일뿐일때
                    index1++;
                    if (dcsa[j] > dcsb[j])//조건 (a>b)
                    {
                        if (dcsa[j] > dcsc[j])//조건 (a>c)
                        {
                            if (dcsb[j] > dcsc[j])//조건 (b>c)    //a>b>C
                            {
                                if (cs >= 3500) {
                                    if (bs >= 3500) {
                                        min = dcsa[j];
                                        as++;
                                        ss[j] = 0;
                                        set_student_school(j, 0);
                                        index11++;
                                    }
                                    else {
                                        min = dcsb[j];
                                        bs++;
                                        ss[j] = 1;
                                        set_student_school(j, 1);
                                        index12++;
                                    }
                                }
                                else {
                                    min = dcsc[j];
                                    cs++;
                                    ss[j] = 2;
                                    set_student_school(j, 2);
                                    index13++;
                                }
                            }
                            else//아닐 때  //a>c>b
                            {
                                if (bs >= 3500) {
                                    if (cs >= 3500) {
                                        min = dcsa[j];
                                        as++;
                                        ss[j] = 0;
                                        set_student_school(j, 0);
                                        index11++;
                                    }
                                    else {
                                        min = dcsc[j];
                                        cs++;
                                        ss[j] = 2;
                                        set_student_school(j, 2);
                                        index13++;
                                    }
                                }
                                else {
                                    min = dcsb[j];
                                    bs++;
                                    ss[j] = 1;
                                    set_student_school(j, 1);
                                    index12++;
                                }
                            }
                        }
                        else//아닐 때  //c>a>b
                        {
                            if (bs >= 3500) {
                                if (as >= 3500) {
                                    min = dcsc[j];
                                    cs++;
                                    ss[j] = 2;
                                    set_student_school(j, 2);
                                    index13++;
                                }
                                else {
                                    min = dcsa[j];
                                    as++;
                                    ss[j] = 0;
                                    set_student_school(j, 0);
                                    index11++;
                                }
                            }
                            else {
                                min = dcsb[j];
                                bs++;
                                ss[j] = 1;
                                set_student_school(j, 1);
                                index12++;
                            }
                        }
                    }
                    else//(a>b)아닐 때 (b>=a)
                    {
                        if (dcsb[j] > dcsc[j])//조건 (b>c)
                        {
                            if (dcsa[j] > dcsc[j])//조건(a>c)     b>a>c
                            {
                                if (cs >= 3500) {
                                    if (as >= 3500) {
                                        min = dcsb[j];
                                        bs++;
                                        ss[j] = 1;
                                        set_student_school(j, 1);
                                        index12++;
                                    }
                                    else {
                                        min = dcsa[j];
                                        as++;
                                        ss[j] = 0;
                                        set_student_school(j, 0);
                                        index11++;
                                    }
                                }
                                else {
                                    min = dcsc[j];
                                    cs++;
                                    ss[j] = 2;
                                    set_student_school(j, 2);
                                    index13++;
                                }
                            }
                            else//아닐 때  //b>C>A
                            {
                                if (as >= 3500) {
                                    if (cs >= 3500) {
                                        min = dcsb[j];
                                        bs++;
                                        ss[j] = 1;
                                        set_student_school(j, 1);
                                        index12++;
                                    }
                                    else {
                                        min = dcsc[j];
                                        cs++;
                                        ss[j] = 2;
                                        set_student_school(j, 2);
                                        index13++;
                                    }
                                }
                                else {
                                    min = dcsa[j];
                                    as++;
                                    ss[j] = 0;
                                    set_student_school(j, 0);
                                    index11++;
                                }
                            }
                        }
                        else//아닐 때     c>b>a
                        {
                            if (as >= 3500) {
                                if (bs >= 3500) {
                                    min = dcsc[j];
                                    cs++;
                                    ss[j] = 2;
                                    set_student_school(j, 2);
                                    index13++;
                                }
                                else {
                                    min = dcsb[j];
                                    bs++;
                                    ss[j] = 1;
                                    set_student_school(j, 1);
                                    index12++;
                                }
                            }
                            else {
                                min = dcsa[j];
                                as++;
                                ss[j] = 0;
                                set_student_school(j, 0);
                                index11++;
                            }
                        }
                    }
                }
                else if (indexorder[i] >= 2) {  //우선순위가 2이상
                    index2++;
                    calsame[0][same] = j;
                    calsame[1][same] = dcsa[j];
                    calsame[2][same] = dcsb[j];
                    calsame[3][same] = dcsc[j];
                    same++;
                    cal++;
                    if (cal == indexorder[i]) {
                        min = orderclear(cal);
                    }
                }
                else {  //우선순위 무시
                    min = 0;
                }
            }
            else {
                min = 0;
            }
            sum = sum + min;
        }
    }
    printf("%d번째 거리최소의합 sum=%lf\n", counttry, sum);
    allsum = allsum + sum;
    //printf("%d %d %d\n", index1, index2,index1+index2);
    //printf("%d %d %d %d %d \n", index11, index12, index13,index11+index12+index13,index1);
    //printf("%d %d %d %d %d\n", index21, index22, index23,index21+index22+index23,index2);
   //printf("\n----------------------------------------\n");
   //printf("%d %d  %d %d  %d \n",counttry,as,bs,cs,as+bs+cs);
    /*for (int i = 0; i < 10000; i++) {
        printf("%d %d\n", i, ss[i]);
    }*/
    end1 = clock();
    printf("%d번째 실행시간%lf\n", counttry, (double)(end1 - start1) / CLOCKS_PER_SEC);
    counttry++;
    if (counttry == 10) {
        printf("10번째 테스트결과의 총합은 allsum=%lf\n", allsum);
    }
}