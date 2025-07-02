// LR(1)�﷨������ʵ��  
#include <stdio.h>  
#include <string.h>  

// ACTION��10��״̬��3���ս��(a/b/#)  
char* action[10][3] = {  
    "S3#", "S4#", NULL,       // ״̬0  
    NULL, NULL, "acc",        // ״̬1  
    "S6#", "S7#", NULL,       // ״̬2  
    "S3#", "S4#", NULL,       // ״̬3  
    "r3#", "r3#", NULL,       // ״̬4  
    NULL, NULL, "r1#",        // ״̬5  
    "S6#", "S7#", NULL,       // ״̬6  
    NULL, NULL, "r3#",        // ״̬7  
    "r2#", "r2#", NULL,       // ״̬8  
    NULL, NULL, "r2#"         // ״̬9  
};  

// GOTO��10��״̬��2�����ս��(S/B)  
int goto1[10][2] = {  
    {1, 2}, {0, 0}, {0, 5}, {0, 8}, {0, 0},  // ״̬0-4  
    {0, 0}, {0, 9}, {0, 0}, {0, 0}, {0, 0}   // ״̬5-9  
};  

// �ս�������ս��������ʽ  
char vt[3] = {'a', 'b', '#'};       // �ս������  
char vn[2] = {'S', 'B'};           // ���ս������  
char* LR[4] = {                    // ����ʽ  
    "E->S#",   // 0: E->S  
    "S->BB#",  // 1: S->BB  
    "B->aB#",  // 2: B->aB  
    "B->b#"    // 3: B->b  
};  

// ջ�ͱ�������  
int stateStack[10];    // ״̬ջ  
char symbolStack[10];  // ����ջ  
char inputStr[20];     // ���봮  
int topState = 0;      // ״̬ջ��ָ��  
int topSymbol = 0;     // ����ջ��ָ��  
int topInput = 0;      // ���봮ָ��  

// ��ӡ��������  
void printAnalysis(int step) {  
    printf("%d\t", step);  
    // ���״̬ջ  
    for (int i = 0; i <= topState; i++) {  
        printf("%d", stateStack[i]);  
    }  
    printf("\t\t");  
    // �������ջ  
    for (int i = 0; i <= topSymbol; i++) {  
        printf("%c", symbolStack[i]);  
    }  
    printf("\t\t");  
    // ���ʣ�����봮  
    for (int i = topInput; i < strlen(inputStr); i++) {  
        printf("%c", inputStr[i]);  
    }  
    printf("\t\t");  
}  

// ������  
void main() {  
    int step = 1;  
    char copy[10], copy1[10];  
    int currentState, actionCol, gotoCol;  
    char currentSymbol;  

    printf("==== LR(1)�﷨������ ====\n");  
    printf("������ֻ��a/b/#�ı��ʽ��");  
    scanf("%s", inputStr);  
    inputStr[strlen(inputStr)] = '#';  // ĩβ���#  
    topInput = 0;  

    // ��ʼ��ջ  
    stateStack[0] = 0; topState = 0;  
    symbolStack[0] = '#'; topSymbol = 0;  

    printf("����\t״̬ջ\t\t����ջ\t\t���봮\t\tACTION\tGOTO\n");  
    do {  
        currentState = stateStack[topState];  
        currentSymbol = inputStr[topInput];  

        // �����ս������  
        actionCol = -1;  
        for (int i = 0; i < 3; i++) {  
            if (currentSymbol == vt[i]) {  
                actionCol = i;  
                break;  
            }  
        }  
        if (actionCol == -1) {  
            printf("error: �Ƿ��ַ�\n");  
            return;  
        }  

        // ִ��ACTION����  
        printAnalysis(step);  
        if (action[currentState][actionCol] == NULL) {  
            printf("error: �޶�ӦACTION\n");  
            return;  
        }  
        strcpy(copy, action[currentState][actionCol]);  
        printf("%s", copy);  

        // �ƽ�������Sx#  
        if (copy[0] == 'S') {  
            int nextState = copy[1] - '0';  
            topState++;  
            topSymbol++;  
            stateStack[topState] = nextState;  
            symbolStack[topSymbol] = currentSymbol;  
            topInput++;  
            printf("\n");  
        }  
        // ��Լ������rx#  
        else if (copy[0] == 'r') {  
            int prodIndex = copy[1] - '0';  
            printf("\t");  
            printf("%s", LR[prodIndex]);  
            printf("\n");  

            // ������ʽ���ȳ�ջ  
            int prodLen = strlen(LR[prodIndex]) - 4;  // ��ȥ"->#"����  
            topState -= prodLen;  
            topSymbol -= prodLen;  

            // ���ҷ��ս������  
            char leftSymbol = LR[prodIndex][0];  
            gotoCol = -1;  
            for (int i = 0; i < 2; i++) {  
                if (leftSymbol == vn[i]) {  
                    gotoCol = i;  
                    break;  
                }  
            }  
            if (gotoCol == -1) {  
                printf("error: �Ƿ����ս��\n");  
                return;  
            }  

            // ѹ����״̬�ͷ���  
            currentState = stateStack[topState];  
            int nextState = goto1[currentState][gotoCol];  
            topState++;  
            topSymbol++;  
            stateStack[topState] = nextState;  
            symbolStack[topSymbol] = leftSymbol;  
        }  
        // ���ܣ�acc  
        else if (strcmp(copy, "acc") == 0) {  
            printf("acc\n");  
            break;  
        }  
        step++;  
    } while (1);  
}  