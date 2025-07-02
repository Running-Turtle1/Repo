#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define max 100
char ex[max];       /*存储后缀表达式*/

void trans() {        /*将算术表达式转化为后缀表达式*/
    char str[max];   /*存储原算术表达式*/
    char stack[max]; /*作为栈使用*/
    char ch;
    int sum, i, j, t, top = 0;
    printf("*****************************************\n");
    printf("*输入一个求值的表达式，以#结束。*\n");
    printf("******************************************\n");
    printf("算数表达式：");
    i = 0;                      /*获取用户输入的表达式*/
    do {
        i++;
        scanf_s("%c", &str[i], 1);  // 第三个参数1表示读取一个字符
    } while (str[i] != '#' && i != max);
    sum = i;
    t = 1;
    i = 1;
    ch = str[i];
    i++;
    while (ch != '#') {
        switch (ch) {
        case '(':                 /*判定为左括号*/
            top++;
            stack[top] = ch;
            break;
        case ')':                 /*判定为右括号*/
            while (top > 0 && stack[top] != '(') {
                ex[t] = stack[top];
                top--;
                t++;
            }
            top--;
            break;
        case '+':                 /*判定为加减号*/
        case '-':
            while (top > 0 && stack[top] != '(') {
                ex[t] = stack[top];
                top--;
                t++;
            }
            top++;
            stack[top] = ch;
            break;
        case '*':                 /*判定为乘除号*/
        case '/':
            while (top > 0 && (stack[top] == '*' || stack[top] == '/')) {
                ex[t] = stack[top];
                top--;
                t++;
            }
            top++;
            stack[top] = ch;
            break;
        case ' ':                 /*跳过空格*/
            break;
        default:                  /*判定为数字*/
            while (ch >= '0' && ch <= '9') {
                ex[t] = ch;
                t++;
                ch = str[i];
                i++;
            }
            i--;
            ex[t] = ' ';  // 添加空格以分隔数字和运算符
            t++;
            break;
        }
        ch = str[i];
        i++;
    }
    while (top > 0) {
        ex[t] = stack[top];
        t++;
        top--;
    }
    ex[t] = '#';  /*标记后缀表达式的结束*/
    printf("\n\t原来表达式：");
    for (j = 1; j < sum; j++)
        printf("%c", str[j]);
    printf("\n\t后缀表达式：");
    for (j = 1; j < t; j++)  /*注意这里是小于 t，因为 t 是后缀表达式的结束标记*/
        printf("%c", ex[j]);
}

void compvalue() {                                 /*计算后缀表达式的值*/
    float stack[max], d;                          /*作为栈使用*/
    char ch;
    int t = 1, top = 0;                           /*t为ex下标，top为stack下标*/
    ch = ex[t];
    t++;
    while (ch != '#') {
        switch (ch) {
        case '+':
            stack[top - 1] = stack[top - 1] + stack[top];
            top--;
            break;
        case '-':
            stack[top - 1] = stack[top - 1] - stack[top];
            top--;
            break;
        case '*':
            stack[top - 1] = stack[top - 1] * stack[top];
            top--;
            break;
        case '/':
            if (stack[top] != 0) {
                stack[top - 1] = stack[top - 1] / stack[top];
            }
            else {
                printf("\n\t除零错误!\n");
                exit(0);                   /*异常退出*/
            }
            top--;
            break;
        default:
            d = 0;
            while (ch >= '0' && ch <= '9') {
                d = 10 * d + (ch - '0');   /*将数字字符转化为对应的数值*/
                ch = ex[t];
                t++;
            }
            top++;
            stack[top] = d;
            break;
        }
        ch = ex[t];
        t++;
    }
    printf("\n\t计算结果:%g\n", stack[top]);
}

int main() {
    trans();
    compvalue();
    return 0;
}