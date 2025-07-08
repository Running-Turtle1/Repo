#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_LENGTH 100

// 全局变量
char postfix[MAX_EXPR_LENGTH];  // 存储后缀表达式
char infix[MAX_EXPR_LENGTH];    // 存储中缀表达式

// 运算符优先级
int precedence(char op) {
    switch(op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// 将中缀表达式转换为后缀表达式
void infixToPostfix() {
    char stack[MAX_EXPR_LENGTH];  // 运算符栈
    int top = -1;                 // 栈顶指针
    int j = 0;                    // 后缀表达式索引
    
    printf("\n请输入中缀表达式（以#结束）: ");
    
    // 读取中缀表达式
    int i = 0;
    do {
        scanf("%c", &infix[i]);
    } while(infix[i] != '#' && i++ < MAX_EXPR_LENGTH-1);
    infix[i] = '\0';  // 替换#为字符串结束符
    
    printf("\n原始中缀表达式: %s\n", infix);
    
    for(i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];
        
        if(isspace(token)) {
            continue;  // 跳过空格
        }
        
        if(isdigit(token) || isalpha(token)) {
            // 如果是操作数（数字或字母），直接输出
            postfix[j++] = token;
        } 
        else if(token == '(') {
            // 左括号压栈
            stack[++top] = token;
        } 
        else if(token == ')') {
            // 右括号，弹出栈顶元素直到遇到左括号
            while(top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            if(top == -1) {
                printf("错误：括号不匹配！\n");
                exit(1);
            }
            top--;  // 弹出左括号
        } 
        else {
            // 运算符，弹出栈顶优先级更高或相等的运算符
            while(top != -1 && precedence(stack[top]) >= precedence(token)) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = token;  // 当前运算符压栈
        }
    }
    
    // 弹出栈中剩余运算符
    while(top != -1) {
        if(stack[top] == '(') {
            printf("错误：括号不匹配！\n");
            exit(1);
        }
        postfix[j++] = stack[top--];
    }
    
    postfix[j] = '\0';  // 字符串结束符
    
    printf("生成的后缀表达式: %s\n", postfix);
}

// 计算后缀表达式的值
void evaluatePostfix() {
    float stack[MAX_EXPR_LENGTH];
    int top = -1;
    
    for(int i = 0; postfix[i] != '\0'; i++) {
        char token = postfix[i];
        
        if(isdigit(token)) {
            // 数字字符转换为数值并压栈
            stack[++top] = token - '0';
        } 
        else if(isalpha(token)) {
            // 处理变量（这里简化为输入值）
            float value;
            printf("请输入变量 %c 的值: ", token);
            scanf("%f", &value);
            stack[++top] = value;
        } 
        else {
            // 运算符，弹出两个操作数进行计算
            if(top < 1) {
                printf("错误：无效的表达式！\n");
                exit(1);
            }
            
            float b = stack[top--];
            float a = stack[top--];
            float result;
            
            switch(token) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': 
                    if(b == 0) {
                        printf("错误：除零错误！\n");
                        exit(1);
                    }
                    result = a / b; 
                    break;
                case '^': result = pow(a, b); break;
                default:
                    printf("错误：未知运算符 %c\n", token);
                    exit(1);
            }
            
            stack[++top] = result;  // 结果压栈
        }
    }
    
    if(top != 0) {
        printf("错误：无效的表达式！\n");
        exit(1);
    }
    
    printf("\n计算结果: %.2f\n", stack[top]);
}

int main() {
    printf("============= 逆波兰式生成与计算 =============\n");
    printf("功能说明：\n");
    printf("1. 支持运算符: + - * / ^ ( )\n");
    printf("2. 支持操作数: 数字0-9和单字母变量\n");
    printf("3. 输入表达式以#结束\n");
    printf("=============================================\n");
    
    infixToPostfix();
    evaluatePostfix();
    
    return 0;
}
