#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char* action[10][3] = {
    {"S3", "S4", NULL},    // 状态0
    {NULL, NULL, "acc"},  // 状态1
    {"S6", "S7", NULL},    // 状态2
    {"S3", "S4", NULL},    // 状态3
    {"r3", "r3", NULL},    // 状态4
    {NULL, NULL, "r1"},    // 状态5
    {"S6", "S7", NULL},    // 状态6
    {NULL, NULL, "r3"},    // 状态7
    {"r2", "r2", NULL},    // 状态8
    {NULL, NULL, "r2"}     // 状态9
};
int goto1[10][2] = {
    {1, 2},  // 状态0
    {0, 0},  // 状态1
    {0, 5},  // 状态2
    {0, 8},  // 状态3
    {0, 0},  // 状态4
    {0, 0},  // 状态5
    {0, 9},  // 状态6
    {0, 0},  // 状态7
    {0, 0},  // 状态8
    {0, 0}   // 状态9
};
const char vt[3] = { 'a', 'b', '#' };  // 存放终结符
const char vn[2] = { 'S', 'B' };       // 存放非终结符
const char* LR[4] = { "E->S#", "S->BB#", "B->aB#", "B->b#" };  // 存放产生式

int a[10];  // 状态栈
char b[10]; // 符号栈
char c[10]; // 输入串
char c1;    // 当前输入符号
int top1, top2, top3, top, m, n;
void main() {
    int g, h, i, j, k, l, p, y, z, count;
    char x, copy[10], copy1[10];
    top1 = 0;
    top2 = 0;
    top3 = 0;
    top = 0;
    a[0] = 0;
    y = a[0];
    b[0] = '#';
    count = 0;
    z = 0;

    printf("请输入只含a b #的表达式\n");
    do {
        scanf_s("%c", &c1, 1);
        if (!isspace(c1)) {  // 跳过空白字符
            c[top3] = c1;
            top3++;
        }
    } while (c1 != '#');
    c[top3] = '\0';  // 添加字符串结束符

    printf("步骤\t状态栈\t\t符号栈\t\t输入串\t\tACTION\tGOTO\n");
    do {
        y = z;
        m = 0;
        n = 0;  // y,z指向状态栈栈顶
        g = top;
        x = c[top];
        count++;
        printf("%d\t", count);
        while (m <= top1) {  // 输出状态栈
            printf("%d ", a[m]);
            m++;
        }
        printf("\t\t");
        while (n <= top2) {  // 输出符号栈
            printf("%c", b[n]);
            n++;
        }
        printf("\t\t");
        while (g < top3) {  // 输出输入串
            printf("%c", c[g]);
            g++;
        }
        printf("\t\t");

        if (x == '#') {
            j = 2;  // '#' 对应下标 2
        }
        else if (x == 'a') {
            j = 0;  // 'a' 对应下标 0
        }
        else if (x == 'b') {
            j = 1;  // 'b' 对应下标 1
        }
        else {
            printf("error\n");
            return;
        }

        if (action[y][j] == NULL) {
            printf("error\n");
            return;
        }
        else {
            strcpy_s(copy, sizeof(copy), action[y][j]);
        }

        if (copy[0] == 'S') {  // 处理移进
            z = copy[1] - '0';
            top1++;
            top2++;
            a[top1] = z;
            b[top2] = x;
            top++;
            printf("%s\n", copy);
        }
        else if (copy[0] == 'r') {  // 处理归约
            i = 0;
            while (copy[i] != '\0') {
                printf("%c", copy[i]);
                i++;
            }
            h = copy[1] - '0';
            strcpy_s(copy1, sizeof(copy1), LR[h]);
            k = 0;
            while (copy1[k] != vn[k]) {
                k++;
            }
            l = strlen(LR[h]) - 4;
            top1 = top1 - l + 1;
            top2 = top2 - l + 1;
            y = a[top1 - 1];
            p = goto1[y][k];
            a[top1] = p;
            b[top2] = copy1[0];
            z = p;
            printf("\t%d\n", p);
        }
    } while (strcmp(action[y][j], "acc") != 0);
    printf("acc\n");
}