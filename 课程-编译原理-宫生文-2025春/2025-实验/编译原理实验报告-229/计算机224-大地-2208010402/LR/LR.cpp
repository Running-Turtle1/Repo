// LR(1)语法分析器实现  
#include <stdio.h>  
#include <string.h>  

// ACTION表：10个状态，3个终结符(a/b/#)  
char* action[10][3] = {  
    "S3#", "S4#", NULL,       // 状态0  
    NULL, NULL, "acc",        // 状态1  
    "S6#", "S7#", NULL,       // 状态2  
    "S3#", "S4#", NULL,       // 状态3  
    "r3#", "r3#", NULL,       // 状态4  
    NULL, NULL, "r1#",        // 状态5  
    "S6#", "S7#", NULL,       // 状态6  
    NULL, NULL, "r3#",        // 状态7  
    "r2#", "r2#", NULL,       // 状态8  
    NULL, NULL, "r2#"         // 状态9  
};  

// GOTO表：10个状态，2个非终结符(S/B)  
int goto1[10][2] = {  
    {1, 2}, {0, 0}, {0, 5}, {0, 8}, {0, 0},  // 状态0-4  
    {0, 0}, {0, 9}, {0, 0}, {0, 0}, {0, 0}   // 状态5-9  
};  

// 终结符、非终结符、产生式  
char vt[3] = {'a', 'b', '#'};       // 终结符集合  
char vn[2] = {'S', 'B'};           // 非终结符集合  
char* LR[4] = {                    // 产生式  
    "E->S#",   // 0: E->S  
    "S->BB#",  // 1: S->BB  
    "B->aB#",  // 2: B->aB  
    "B->b#"    // 3: B->b  
};  

// 栈和变量定义  
int stateStack[10];    // 状态栈  
char symbolStack[10];  // 符号栈  
char inputStr[20];     // 输入串  
int topState = 0;      // 状态栈顶指针  
int topSymbol = 0;     // 符号栈顶指针  
int topInput = 0;      // 输入串指针  

// 打印分析过程  
void printAnalysis(int step) {  
    printf("%d\t", step);  
    // 输出状态栈  
    for (int i = 0; i <= topState; i++) {  
        printf("%d", stateStack[i]);  
    }  
    printf("\t\t");  
    // 输出符号栈  
    for (int i = 0; i <= topSymbol; i++) {  
        printf("%c", symbolStack[i]);  
    }  
    printf("\t\t");  
    // 输出剩余输入串  
    for (int i = topInput; i < strlen(inputStr); i++) {  
        printf("%c", inputStr[i]);  
    }  
    printf("\t\t");  
}  

// 主函数  
void main() {  
    int step = 1;  
    char copy[10], copy1[10];  
    int currentState, actionCol, gotoCol;  
    char currentSymbol;  

    printf("==== LR(1)语法分析器 ====\n");  
    printf("请输入只含a/b/#的表达式：");  
    scanf("%s", inputStr);  
    inputStr[strlen(inputStr)] = '#';  // 末尾添加#  
    topInput = 0;  

    // 初始化栈  
    stateStack[0] = 0; topState = 0;  
    symbolStack[0] = '#'; topSymbol = 0;  

    printf("步骤\t状态栈\t\t符号栈\t\t输入串\t\tACTION\tGOTO\n");  
    do {  
        currentState = stateStack[topState];  
        currentSymbol = inputStr[topInput];  

        // 查找终结符索引  
        actionCol = -1;  
        for (int i = 0; i < 3; i++) {  
            if (currentSymbol == vt[i]) {  
                actionCol = i;  
                break;  
            }  
        }  
        if (actionCol == -1) {  
            printf("error: 非法字符\n");  
            return;  
        }  

        // 执行ACTION操作  
        printAnalysis(step);  
        if (action[currentState][actionCol] == NULL) {  
            printf("error: 无对应ACTION\n");  
            return;  
        }  
        strcpy(copy, action[currentState][actionCol]);  
        printf("%s", copy);  

        // 移进操作：Sx#  
        if (copy[0] == 'S') {  
            int nextState = copy[1] - '0';  
            topState++;  
            topSymbol++;  
            stateStack[topState] = nextState;  
            symbolStack[topSymbol] = currentSymbol;  
            topInput++;  
            printf("\n");  
        }  
        // 归约操作：rx#  
        else if (copy[0] == 'r') {  
            int prodIndex = copy[1] - '0';  
            printf("\t");  
            printf("%s", LR[prodIndex]);  
            printf("\n");  

            // 按产生式长度出栈  
            int prodLen = strlen(LR[prodIndex]) - 4;  // 减去"->#"长度  
            topState -= prodLen;  
            topSymbol -= prodLen;  

            // 查找非终结符索引  
            char leftSymbol = LR[prodIndex][0];  
            gotoCol = -1;  
            for (int i = 0; i < 2; i++) {  
                if (leftSymbol == vn[i]) {  
                    gotoCol = i;  
                    break;  
                }  
            }  
            if (gotoCol == -1) {  
                printf("error: 非法非终结符\n");  
                return;  
            }  

            // 压入新状态和符号  
            currentState = stateStack[topState];  
            int nextState = goto1[currentState][gotoCol];  
            topState++;  
            topSymbol++;  
            stateStack[topState] = nextState;  
            symbolStack[topSymbol] = leftSymbol;  
        }  
        // 接受：acc  
        else if (strcmp(copy, "acc") == 0) {  
            printf("acc\n");  
            break;  
        }  
        step++;  
    } while (1);  
}  