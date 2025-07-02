#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* LR������ */
char *action[10][3] = {
    {"S3", "S4", NULL},    /* ״̬0 */
    {NULL, NULL, "acc"},    /* ״̬1 */
    {"S6", "S7", NULL},     /* ״̬2 */
    {"S3", "S4", NULL},     /* ״̬3 */
    {"r3", "r3", NULL},     /* ״̬4 */
    {NULL, NULL, "r1"},     /* ״̬5 */
    {"S6", "S7", NULL},     /* ״̬6 */
    {NULL, NULL, "r3"},     /* ״̬7 */
    {"r2", "r2", NULL},     /* ״̬8 */
    {NULL, NULL, "r2"}      /* ״̬9 */
};

int goto_table[10][2] = {
    {1, 2},    /* ״̬0 */
    {0, 0},    /* ״̬1 */
    {0, 5},    /* ״̬2 */
    {0, 8},    /* ״̬3 */
    {0, 0},    /* ״̬4 */
    {0, 0},    /* ״̬5 */
    {0, 9},    /* ״̬6 */
    {0, 0},    /* ״̬7 */
    {0, 0},    /* ״̬8 */
    {0, 0}     /* ״̬9 */
};

/* �ķ����Ŷ��� */
char terminals[3] = {'a', 'b', '#'};      /* �ս�� */
char non_terminals[2] = {'S', 'B'};       /* ���ս�� */
char *productions[4] = {                  /* ����ʽ���� */
    "E->S",    /* 0�Ų���ʽ */
    "S->BB",   /* 1�Ų���ʽ */
    "B->aB",   /* 2�Ų���ʽ */
    "B->b"     /* 3�Ų���ʽ */
};

/* ȫ�ֱ��� */
int state_stack[100];      /* ״̬ջ */
char symbol_stack[100];    /* ����ջ */
char input_string[100];    /* ���봮 */
int top_state = 0;         /* ״̬ջ��ָ�� */
int top_symbol = 0;        /* ����ջ��ָ�� */
int input_ptr = 0;         /* ���봮ָ�� */

void print_stacks() {
    /* ��ӡ״̬ջ */
    printf("״̬ջ: [");
    for (int i = 0; i <= top_state; i++) {
        printf("%d", state_stack[i]);
        if (i < top_state) printf(", ");
    }
    printf("]\t");
    
    /* ��ӡ����ջ */
    printf("����ջ: [");
    for (int i = 0; i <= top_symbol; i++) {
        printf("%c", symbol_stack[i]);
        if (i < top_symbol) printf(", ");
    }
    printf("]\t");
    
    /* ��ӡʣ�����봮 */
    printf("���봮: ");
    for (int i = input_ptr; input_string[i] != '#'; i++) {
        printf("%c", input_string[i]);
    }
    printf("#\t");
}

int get_terminal_index(char c) {
    for (int i = 0; i < 3; i++) {
        if (terminals[i] == c) return i;
    }
    return -1;  /* �����ս�� */
}

int get_non_terminal_index(char c) {
    for (int i = 0; i < 2; i++) {
        if (non_terminals[i] == c) return i;
    }
    return -1;  /* ���Ƿ��ս�� */
}

void lr_parser() {
    int step = 1;
    state_stack[0] = 0;      /* ��ʼ״̬0��ջ */
    symbol_stack[0] = '#';    /* ջ�׷��� */
    
    printf("����\t״̬ջ�ͷ���ջ\t\t\t���봮\t\t����\n");
    printf("------------------------------------------------------------\n");
    
    while (1) {
        printf("%d\t", step++);
        print_stacks();
        
        char current_char = input_string[input_ptr];
        int terminal_idx = get_terminal_index(current_char);
        
        if (terminal_idx == -1) {
            printf("\n����: �Ƿ������ַ� '%c'\n", current_char);
            return;
        }
        
        char *action_str = action[state_stack[top_state]][terminal_idx];
        
        if (action_str == NULL) {
            printf("\n����: ��״̬%d�����ַ�'%c'û�ж���Ķ���\n", 
                  state_stack[top_state], current_char);
            return;
        }
        
        /* �ƽ����� */
        if (action_str[0] == 'S') {
            int new_state = action_str[1] - '0';
            printf("�ƽ� %s\n", action_str);
            
            /* ״̬��ջ */
            state_stack[++top_state] = new_state;
            /* ������ջ */
            symbol_stack[++top_symbol] = current_char;
            /* ����ָ��ǰ�� */
            input_ptr++;
        } 
        /* ��Լ���� */
        else if (action_str[0] == 'r') {
            int prod_num = action_str[1] - '0';
            char *production = productions[prod_num];
            printf("��Լ %s (%s)\t", action_str, production);
            
            /* ��ȡ����ʽ�� */
            char left_symbol = production[0];
            /* ��ȡ����ʽ�Ҳ����� */
            int rhs_length = strlen(production) - 3;
            
            /* ����״̬ջ�ͷ���ջ�еķ��� */
            top_state -= rhs_length;
            top_symbol -= rhs_length;
            
            /* ��ȡ�µ�ջ��״̬ */
            int current_state = state_stack[top_state];
            /* ��ȡ�󲿷��ս�������� */
            int nt_index = get_non_terminal_index(left_symbol);
            
            if (nt_index == -1) {
                printf("\n����: ���ս�� '%c' δ����\n", left_symbol);
                return;
            }
            
            /* ����goto�� */
            int new_state = goto_table[current_state][nt_index];
            if (new_state == 0) {
                printf("\n����: ��״̬%d��'%c'û��GOTOת��\n", 
                      current_state, left_symbol);
                return;
            }
            
            /* ��״̬��ջ */
            state_stack[++top_state] = new_state;
            /* �󲿷�����ջ */
            symbol_stack[++top_symbol] = left_symbol;
            
            printf("GOTO %d\n", new_state);
        } 
        /* ���ܶ��� */
        else if (strcmp(action_str, "acc") == 0) {
            printf("����\n");
            printf("\n�����ɹ�! ���봮�����ķ�����\n");
            return;
        }
    }
}

int main() {
    printf("ʵ���: LR�����������\n");
    printf("֧�ֵ��ս��: a, b, #\n");
    printf("�ķ�����ʽ:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d: %s\n", i, productions[i]);
    }
    printf("\n");
    
    printf("������Ҫ�������ַ���(��#����): ");
    char c;
    int i = 0;
    
    /* ��ȡ���� */
    do {
        scanf("%c", &c);
        if (c != ' ' && c != '\n') {  /* �����ո�ͻ��� */
            if (c != 'a' && c != 'b' && c != '#') {
                printf("����: �Ƿ��ַ� '%c'��ֻ��������a, b, #\n", c);
                return 1;
            }
            input_string[i++] = c;
        }
    } while (c != '#');
    
    printf("\n��ʼ��������:\n");
    lr_parser();
    
    return 0;
}
