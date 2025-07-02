#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 20
#define MAX_PRODUCTIONS 10
#define MAX_PRODUCTION_LENGTH 10

char A[MAX_STACK_SIZE]; /* ����ջ */
char B[MAX_STACK_SIZE]; /* ʣ�മ */
char v1[MAX_STACK_SIZE] = {'i', '+', '*', '(', ')', '#'}; /* �ս�� */
char v2[MAX_STACK_SIZE] = {'E', 'G', 'T', 'S', 'F'}; /* ���ս�� */

int j = 0, b = 0, top = 0, l; /* lΪ���봮���� */

typedef struct {
    char origin; /* ��д�ַ� */
    char array[MAX_PRODUCTION_LENGTH]; /* ����ʽ�ұ��ַ� */
    int length; /* �ַ����� */
} type;

type e, t, g, g1, s, s1, f, f1; /* �ṹ����� */
type C[MAX_PRODUCTIONS][MAX_PRODUCTIONS]; /* Ԥ������� */

void print() { /* �������ջ */
    int a;
    for (a = 0; a <= top; a++)
        printf("%c", A[a]);
    printf("\t\t");
}

void print1() { /* ���ʣ�മ */
    int j;
    for (j = 0; j < b; j++) /* �������� */
        printf(" ");
    for (j = b; j <= l; j++)
        printf("%c", B[j]);
    printf("\t\t\t");
}

int main() {
    int m, n, k = 0, flag = 0, finish = 0;
    char ch, x;
    type cha; /* ��������C[m][n] */

    /* ���ķ�����ʽ��ֵ�ṹ�� */
    e.origin = 'E';
    strcpy(e.array, "TG");
    e.length = 2;
    t.origin = 'T';
    strcpy(t.array, "FS");
    t.length = 2;
    g.origin = 'G';
    strcpy(g.array, "+TG");
    g.length = 3;
    g1.origin = 'G';
    g1.array[0] = '^';
    g1.length = 1;
    s.origin = 'S';
    strcpy(s.array, "*FS");
    s.length = 3;
    s1.origin = 'S';
    s1.array[0] = '^';
    s1.length = 1;
    f.origin = 'F';
    strcpy(f.array, "(E)");
    f.length = 3;
    f1.origin = 'F';
    f1.array[0] = 'i';
    f1.length = 1;

    /* ��ʼ�������� */
    for (m = 0; m < 5; m++) {
        for (n = 0; n < 6; n++) {
            C[m][n].origin = 'N'; /* ȫ����Ϊ�� */
        }
    }

    /* �������� */
    C[0][0] = e; C[0][3] = e;
    C[1][1] = g; C[1][4] = g1; C[1][5] = g1;
    C[2][0] = t; C[2][3] = t;
    C[3][1] = s1; C[3][2] = s; C[3][4] = s1; C[3][5] = s1;
    C[4][0] = f1; C[4][3] = f;

    printf("��ʾ: ������ֻ�ܶ��� 'i', '+', '*', '(', ')' ���ɵ��� '#' �������ַ������з�����\n");
    printf("������Ҫ�������ַ���: ");
    do { /* ��������� */
        scanf("%c", &ch);
        if ((ch != 'i') && (ch != '+') && (ch != '*') && (ch != '(') && (ch != ')') && (ch != '#')) {
            printf("���봮���зǷ��ַ�\n");
            exit(1);
        }
        B[j++] = ch;
    } while (ch != '#');
    l = j; /* ���������� */
    ch = B[0]; /* ��ǰ�����ַ� */
    A[top] = '#'; A[++top] = 'E'; /* '#', 'E' ��ջ */

    printf("����\t\t����ջ\t\tʣ���ַ�\t\t���ò���ʽ\n");
    do {
        x = A[top--]; /* x Ϊ��ǰջ���ַ� */
        printf("%d", k++);
        printf("\t\t");
        for (j = 0; j <= 5; j++) { /* �ж��Ƿ�Ϊ�ս�� */
            if (x == v1[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) { /* ������ս�� */
            if (x == '#') {
                finish = 1; /* ������� */
                printf("acc!\n"); /* ���� */
                exit(0);
            }
            if (x == ch) {
                print();
                print1();
                printf("%c ƥ��\n", ch);
                ch = B[++b]; /* ��һ�������ַ� */
                flag = 0; /* �ָ���� */
            } else { /* ������ */
                print();
                print1();
                printf("%c ����\n", ch); /* ��������ս�� */
                exit(1);
            }
        } else { /* ���ս������ */
            for (j = 0; j < 5; j++) {
                if (x == v2[j]) {
                    m = j; /* �к� */
                    break;
                }
            }
            for (j = 0; j < 6; j++) {
                if (ch == v1[j]) {
                    n = j; /* �к� */
                    break;
                }
            }
            cha = C[m][n];
            if (cha.origin != 'N') { /* �ж��Ƿ�Ϊ�� */
                print();
                print1();
                printf("%c-", cha.origin); /* �������ʽ */
                for (j = 0; j < cha.length; j++)
                    printf("%c", cha.array[j]);
                printf("\n");
                for (j = cha.length - 1; j >= 0; j--) /* ����ʽ������ջ */
                    A[++top] = cha.array[j];
                if (A[top] == '^') /* Ϊ���򲻽�ջ */
                    top--;
            } else { /* ������ */
                print();
                print1();
                printf("%c ����\n", x); /* ���������ս�� */
                exit(1);
            }
        }
    } while (finish == 0);

    return 0;
}
