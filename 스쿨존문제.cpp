#include <stdio.h>
#include <math.h>
#include <time.h>
#include <limits.h>
static unsigned int a = 1;   //�����⺻��
extern int process(int command, int param1, int param2);
void get_school_position(int school_index, int* posX, int* posY);
void get_student_position(int student_index, int* posX, int* posY);
void set_student_school(int student_index, int school_index);
static int counttry = 0;   //10��°�ΰ�?
static double allsum = 0;   //10��° ���� ���պ��غ���
int srand(unsigned int seed) {
    return seed;
}
int rand(void) {
    return(((a = a * 214013L + 2531011L) >> 16) & 0x7fff);
}
double dct[10000] = { 0, }; //�߽����� �л����ǰŸ�
int dcti[10000] = { 0, };  //�߽����� �л����� �Ÿ� index����
double dcsa[10000] = { 0, };    //�л��� �б�a���ǰŸ�
double dcsb[10000] = { 0, };    //b
double dcsc[10000] = { 0, };    //c
int indexorder[10000] = { 0, };   //�켱���� ����(��ġ�°���)
//int ordersame[8] = { 0, };  //�ּ�1������ �ִ�8��������   //�켱������ ��ĥ�� index���� //�����ʿ��������? 
double calsame[4][8] = { 0, }; //ordersame�迭 ��뺸�ٴ� index.a.b.c�Ÿ��� ��¦ ���Ͱ��� ��������
int ss[10000];  //�л��� ��� �б��� �����Ǵ°� a-0 b-1 c-2
int as = 0;     //a�б�����
int bs = 0;     //b�б�����
int cs = 0;     //c�б�����
int sx, sy; //�б���ġ
int tx, ty; //�л���ġ
int cx = 0; //�б��߽�����ġx
int cy = 0; //�б��߽�����ġy
double sum = 0; //run�ɶ� �Ÿ�����

int number = 0; //�ܼ���꺯��
double min = 0; //�ּڰ�������
int same = 0;  //�켱���� ���Ҷ� index���� 
int cal = 0; //indexorder�� �ִ��϶� ���������
double arr[32];     //calsame2������ 1�������� �ű��
double arr1[32];  //arr�ű�⺹�纻������ �ε���(-1)�� ����
double arr2[32];  //arr1 ��������
int index1 = 0; //����� //indexorder�� 1�ΰ�쿡 �� ��ġ�� ��찡������.
int index11 = 0;    //a�б�
int index12 = 0;    //b�б�
int index13 = 0;    //c�б���ġ�ο�
int index2 = 0; //indexorder�� 2�̻��ΰ�쿡
int index21 = 0;    //a�б���ġ�ο�
int index22 = 0;    //b�б�
int index23 = 0;    //c�б�
void order(double arr2[], int count) {   //������������
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
double orderclear(int cal) {    //�켱������ 2�̻� cal�� ������ �����غ���
    min = 0;
    int count = 0;  //�ִ� 4*8�� 32��찡 ������,index,a,b,c �׸��� ��ĥ���մ°���� �� 8����
    for (int i = 0; i < 32; i++) {
        arr[i] = -1;
    }   //�ʱ�ȭ
    for (int y = 0; y < cal; y++) {
        for (int x = 0; x < 4; x++) {   //2������ 1�������� ����
            int z = y * 4 + x;
            if (z % 4 == 0) {
                arr[z] = -1;
            }
            else {
                arr[z] = calsame[x][y]; //�ε��������ϱ�
                arr1[count] = arr[z];
                arr2[count] = arr[z];
                count++;
            }
        }
    }
    int m = 0, n = 0;   //�ܼ�����
    int count1 = count; //�򰥸����ʱ����ؼ�
    for (int i = 0; i < cal; i++) { //ã�ƾ��� min���� cal������ŭ
        for (int j = 0; j < count; j++) {
            order(arr2, count1);    //����ؼ� ���ΰ�ħ �̹� ���� index������ �ʿ�����Ƿ� ����
            double least = arr2[0];  //ù���� ������ �ּڰ�
            for (int k = 0; k < count; k++) {
                if (arr[k] == least) {  //�� �ּҰ��� ��� ����Ű�°ɱ�
                    m = k % 3;      //�б���ġ
                    n = k / 3;      //�ε�����ġ
                }
            }
            if (m == 0) {   //�б���a�̴�
                if (as >= 3500) {    //���� a�ο����� ��á����
                    arr2[0] = 1000000;  //���Ұ�
                    if (arr2[n * 3 + 1] > arr2[n * 3 + 2]) {    //b��c�Ǻ� b>c
                        if (bs >= 3500) {   //b����á����
                            index23++;  //������c������
                            cs++;
                            ss[n] = 2;
                            set_student_school(n, 2);
                            least = arr2[n * 3 + 2];    //least�� ����
                            min = min + least;
                            arr2[n * 3] = 1000000;  //���� �ε����� �����͵� �ٸ��� 
                            arr2[n * 3 + 1] = 1000000;
                            arr2[n * 3 + 2] = 1000000;
                            break;
                        }
                        else {  //b�� �ڸ����ִٸ�
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
                        if (cs >= 3500) {   //c����á����
                            index22++;  //������b������
                            bs++;
                            ss[n] = 1;
                            set_student_school(n, 1);
                            least = arr2[n * 3 + 1];    //least�� ����
                            min = min + least;
                            arr2[n * 3] = 1000000;  //���� �ε����� �����͵� �ٸ��� 
                            arr2[n * 3 + 1] = 1000000;
                            arr2[n * 3 + 2] = 1000000;
                            break;
                        }
                        else {  //c�� �ڸ����ִٸ�
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
                else {  //a�� �ڸ����ִٸ�
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
                else {  //b�б��� �ڸ�������
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






            else {  //c�б�
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
    for (int i = 0; i < 10000; i++) {   //���ú����ʱ�ȭ
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
    clock_t start1, end1;   //�ð�����
    start1 = clock();
    for (int i = 0; i < 3; i++) {   //�б��������ϱ�
        get_school_position(i, &sx, &sy);
        cx = cx + sx;
        cy = cy + sy;
    }
    cx = cx / 3;
    cy = cy / 3;
    for (int i = 0; i < 10000; i++) {   //�߽����� �л��� �Ÿ����ϱ�
        get_student_position(i, &tx, &ty);
        dct[i] = sqrt(pow(tx - cx, 2) + pow(ty - cy, 2));
    }
    for (int i = 0; i < 10000; i++) {   //�ε������� �켱������?
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
    for (int i = 0; i < 10000; i++) {       //�켱���������ϴ¹� 
        for (int j = 0; j < 10000; j++) {
            if (dcti[j] == i) {
                indexorder[i]++;
            }
        }
    }
    min = 0;    //�ּڰ� �ʱ�ȭ
    for (int i = 9999; i >= 0; i--) { //����ָ��ִ¾��̺��͹�ġ
        same = 0;
        cal = 0;
        for (int i = 0; i < 4; i++) {   //����� �ʱ�ȭ
            for (int j = 0; j < 8; j++) {
                calsame[i][j] = 0;
            }
        }
        for (int j = 0; j < 10000; j++) {
            if (dcti[j] == i) {
                if (indexorder[i] == 1) { //�켱������ 1���ϻ��϶�
                    index1++;
                    if (dcsa[j] > dcsb[j])//���� (a>b)
                    {
                        if (dcsa[j] > dcsc[j])//���� (a>c)
                        {
                            if (dcsb[j] > dcsc[j])//���� (b>c)    //a>b>C
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
                            else//�ƴ� ��  //a>c>b
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
                        else//�ƴ� ��  //c>a>b
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
                    else//(a>b)�ƴ� �� (b>=a)
                    {
                        if (dcsb[j] > dcsc[j])//���� (b>c)
                        {
                            if (dcsa[j] > dcsc[j])//����(a>c)     b>a>c
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
                            else//�ƴ� ��  //b>C>A
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
                        else//�ƴ� ��     c>b>a
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
                else if (indexorder[i] >= 2) {  //�켱������ 2�̻�
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
                else {  //�켱���� ����
                    min = 0;
                }
            }
            else {
                min = 0;
            }
            sum = sum + min;
        }
    }
    printf("%d��° �Ÿ��ּ����� sum=%lf\n", counttry, sum);
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
    printf("%d��° ����ð�%lf\n", counttry, (double)(end1 - start1) / CLOCKS_PER_SEC);
    counttry++;
    if (counttry == 10) {
        printf("10��° �׽�Ʈ����� ������ allsum=%lf\n", allsum);
    }
}