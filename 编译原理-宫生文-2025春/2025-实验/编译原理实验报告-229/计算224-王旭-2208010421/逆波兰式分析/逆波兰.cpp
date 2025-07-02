#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_LENGTH 100

// ȫ�ֱ���
char postfix[MAX_EXPR_LENGTH];  // �洢��׺���ʽ
char infix[MAX_EXPR_LENGTH];    // �洢��׺���ʽ

// ��������ȼ�
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

// ����׺���ʽת��Ϊ��׺���ʽ
void infixToPostfix() {
    char stack[MAX_EXPR_LENGTH];  // �����ջ
    int top = -1;                 // ջ��ָ��
    int j = 0;                    // ��׺���ʽ����
    
    printf("\n��������׺���ʽ����#������: ");
    
    // ��ȡ��׺���ʽ
    int i = 0;
    do {
        scanf("%c", &infix[i]);
    } while(infix[i] != '#' && i++ < MAX_EXPR_LENGTH-1);
    infix[i] = '\0';  // �滻#Ϊ�ַ���������
    
    printf("\nԭʼ��׺���ʽ: %s\n", infix);
    
    for(i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];
        
        if(isspace(token)) {
            continue;  // �����ո�
        }
        
        if(isdigit(token) || isalpha(token)) {
            // ����ǲ����������ֻ���ĸ����ֱ�����
            postfix[j++] = token;
        } 
        else if(token == '(') {
            // ������ѹջ
            stack[++top] = token;
        } 
        else if(token == ')') {
            // �����ţ�����ջ��Ԫ��ֱ������������
            while(top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            if(top == -1) {
                printf("�������Ų�ƥ�䣡\n");
                exit(1);
            }
            top--;  // ����������
        } 
        else {
            // �����������ջ�����ȼ����߻���ȵ������
            while(top != -1 && precedence(stack[top]) >= precedence(token)) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = token;  // ��ǰ�����ѹջ
        }
    }
    
    // ����ջ��ʣ�������
    while(top != -1) {
        if(stack[top] == '(') {
            printf("�������Ų�ƥ�䣡\n");
            exit(1);
        }
        postfix[j++] = stack[top--];
    }
    
    postfix[j] = '\0';  // �ַ���������
    
    printf("���ɵĺ�׺���ʽ: %s\n", postfix);
}

// �����׺���ʽ��ֵ
void evaluatePostfix() {
    float stack[MAX_EXPR_LENGTH];
    int top = -1;
    
    for(int i = 0; postfix[i] != '\0'; i++) {
        char token = postfix[i];
        
        if(isdigit(token)) {
            // �����ַ�ת��Ϊ��ֵ��ѹջ
            stack[++top] = token - '0';
        } 
        else if(isalpha(token)) {
            // ��������������Ϊ����ֵ��
            float value;
            printf("��������� %c ��ֵ: ", token);
            scanf("%f", &value);
            stack[++top] = value;
        } 
        else {
            // ������������������������м���
            if(top < 1) {
                printf("������Ч�ı��ʽ��\n");
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
                        printf("���󣺳������\n");
                        exit(1);
                    }
                    result = a / b; 
                    break;
                case '^': result = pow(a, b); break;
                default:
                    printf("����δ֪����� %c\n", token);
                    exit(1);
            }
            
            stack[++top] = result;  // ���ѹջ
        }
    }
    
    if(top != 0) {
        printf("������Ч�ı��ʽ��\n");
        exit(1);
    }
    
    printf("\n������: %.2f\n", stack[top]);
}

int main() {
    printf("============= �沨��ʽ��������� =============\n");
    printf("����˵����\n");
    printf("1. ֧�������: + - * / ^ ( )\n");
    printf("2. ֧�ֲ�����: ����0-9�͵���ĸ����\n");
    printf("3. ������ʽ��#����\n");
    printf("=============================================\n");
    
    infixToPostfix();
    evaluatePostfix();
    
    return 0;
}
