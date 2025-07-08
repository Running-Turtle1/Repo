#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* LR分析表 */
char *action[10][3] = {
    {"S3", "S4", NULL},    /* 状态0 */
    {NULL, NULL, "acc"},    /* 状态1 */
    {"S6", "S7", NULL},     /* 状态2 */
    {"S3", "S4", NULL},     /* 状态3 */
    {"r3", "r3", NULL},     /* 状态4 */
    {NULL, NULL, "r1"},     /* 状态5 */
    {"S6", "S7", NULL},     /* 状态6 */
    {NULL, NULL, "r3"},     /* 状态7 */
    {"r2", "r2", NULL},     /* 状态8 */
    {NULL, NULL, "r2"}      /* 状态9 */
};

int goto_table[10][2] = {
    {1, 2},    /* 状态0 */
    {0, 0},    /* 状态1 */
    {0, 5},    /* 状态2 */
    {0, 8},    /* 状态3 */
    {0, 0},    /* 状态4 */
    {0, 0},    /* 状态5 */
    {0, 9},    /* 状态6 */
    {0, 0},    /* 状态7 */
    {0, 0},    /* 状态8 */
    {0, 0}     /* 状态9 */
};

/* 文法符号定义 */
char terminals[3] = {'a', 'b', '#'};      /* 终结符 */
char non_terminals[2] = {'S', 'B'};       /* 非终结符 */
char *productions[4] = {                  /* 产生式集合 */
    "E->S",    /* 0号产生式 */
    "S->BB",   /* 1号产生式 */
    "B->aB",   /* 2号产生式 */
    "B->b"     /* 3号产生式 */
};

/* 全局变量 */
int state_stack[100];      /* 状态栈 */
char symbol_stack[100];    /* 符号栈 */
char input_string[100];    /* 输入串 */
int top_state = 0;         /* 状态栈顶指针 */
int top_symbol = 0;        /* 符号栈顶指针 */
int input_ptr = 0;         /* 输入串指针 */

void print_stacks() {
    /* 打印状态栈 */
    printf("状态栈: [");
    for (int i = 0; i <= top_state; i++) {
        printf("%d", state_stack[i]);
        if (i < top_state) printf(", ");
    }
    printf("]\t");
    
    /* 打印符号栈 */
    printf("符号栈: [");
    for (int i = 0; i <= top_symbol; i++) {
        printf("%c", symbol_stack[i]);
        if (i < top_symbol) printf(", ");
    }
    printf("]\t");
    
    /* 打印剩余输入串 */
    printf("输入串: ");
    for (int i = input_ptr; input_string[i] != '#'; i++) {
        printf("%c", input_string[i]);
    }
    printf("#\t");
}

int get_terminal_index(char c) {
    for (int i = 0; i < 3; i++) {
        if (terminals[i] == c) return i;
    }
    return -1;  /* 不是终结符 */
}

int get_non_terminal_index(char c) {
    for (int i = 0; i < 2; i++) {
        if (non_terminals[i] == c) return i;
    }
    return -1;  /* 不是非终结符 */
}

void lr_parser() {
    int step = 1;
    state_stack[0] = 0;      /* 初始状态0入栈 */
    symbol_stack[0] = '#';    /* 栈底符号 */
    
    printf("步骤\t状态栈和符号栈\t\t\t输入串\t\t动作\n");
    printf("------------------------------------------------------------\n");
    
    while (1) {
        printf("%d\t", step++);
        print_stacks();
        
        char current_char = input_string[input_ptr];
        int terminal_idx = get_terminal_index(current_char);
        
        if (terminal_idx == -1) {
            printf("\n错误: 非法输入字符 '%c'\n", current_char);
            return;
        }
        
        char *action_str = action[state_stack[top_state]][terminal_idx];
        
        if (action_str == NULL) {
            printf("\n错误: 在状态%d遇到字符'%c'没有定义的动作\n", 
                  state_stack[top_state], current_char);
            return;
        }
        
        /* 移进动作 */
        if (action_str[0] == 'S') {
            int new_state = action_str[1] - '0';
            printf("移进 %s\n", action_str);
            
            /* 状态入栈 */
            state_stack[++top_state] = new_state;
            /* 符号入栈 */
            symbol_stack[++top_symbol] = current_char;
            /* 输入指针前移 */
            input_ptr++;
        } 
        /* 归约动作 */
        else if (action_str[0] == 'r') {
            int prod_num = action_str[1] - '0';
            char *production = productions[prod_num];
            printf("归约 %s (%s)\t", action_str, production);
            
            /* 获取产生式左部 */
            char left_symbol = production[0];
            /* 获取产生式右部长度 */
            int rhs_length = strlen(production) - 3;
            
            /* 弹出状态栈和符号栈中的符号 */
            top_state -= rhs_length;
            top_symbol -= rhs_length;
            
            /* 获取新的栈顶状态 */
            int current_state = state_stack[top_state];
            /* 获取左部非终结符的索引 */
            int nt_index = get_non_terminal_index(left_symbol);
            
            if (nt_index == -1) {
                printf("\n错误: 非终结符 '%c' 未定义\n", left_symbol);
                return;
            }
            
            /* 查找goto表 */
            int new_state = goto_table[current_state][nt_index];
            if (new_state == 0) {
                printf("\n错误: 在状态%d对'%c'没有GOTO转移\n", 
                      current_state, left_symbol);
                return;
            }
            
            /* 新状态入栈 */
            state_stack[++top_state] = new_state;
            /* 左部符号入栈 */
            symbol_stack[++top_symbol] = left_symbol;
            
            printf("GOTO %d\n", new_state);
        } 
        /* 接受动作 */
        else if (strcmp(action_str, "acc") == 0) {
            printf("接受\n");
            printf("\n分析成功! 输入串符合文法规则。\n");
            return;
        }
    }
}

int main() {
    printf("实验二: LR分析器的设计\n");
    printf("支持的终结符: a, b, #\n");
    printf("文法产生式:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d: %s\n", i, productions[i]);
    }
    printf("\n");
    
    printf("请输入要分析的字符串(以#结束): ");
    char c;
    int i = 0;
    
    /* 读取输入 */
    do {
        scanf("%c", &c);
        if (c != ' ' && c != '\n') {  /* 跳过空格和换行 */
            if (c != 'a' && c != 'b' && c != '#') {
                printf("错误: 非法字符 '%c'。只允许输入a, b, #\n", c);
                return 1;
            }
            input_string[i++] = c;
        }
    } while (c != '#');
    
    printf("\n开始分析过程:\n");
    lr_parser();
    
    return 0;
}
