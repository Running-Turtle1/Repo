#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 20
#define MAX_LABELS 20

FILE *fp;
char cbuffer;
char *key[8] = {"if", "else", "for", "while", "do", "return", "break", "continue"};
char *border[6] = {",", ";", "{", "}", "(", ")"};
char *arithmetic[4] = {"+", "-", "*", "/"};
char *relation[6] = {"<", "<=", "=", ">", ">=", "<>"};
char *consts[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
char *label[MAX_LABELS];
int constnum = 0, labelnum = 0;

int search(char searchchar[], int wordtype) {
    int i = 0;
    switch (wordtype) {
        case 1: // 关键字
            for (i = 0; i < 8; i++) {
                if (strcmp(key[i], searchchar) == 0)
                    return i + 1;
            }
            break;
        case 2: // 分隔符
            for (i = 0; i < 6; i++) {
                if (strcmp(border[i], searchchar) == 0)
                    return i + 1;
            }
            break;
        case 3: // 运算符
            for (i = 0; i < 4; i++) {
                if (strcmp(arithmetic[i], searchchar) == 0)
                    return i + 1;
            }
            break;
        case 4: // 关系运算符
            for (i = 0; i < 6; i++) {
                if (strcmp(relation[i], searchchar) == 0)
                    return i + 1;
            }
            break;
        case 5: // 数字
            for (i = 0; i < 10; i++) {
                if (strcmp(consts[i], searchchar) == 0)
                    return i + 1;
            }
            break;
        case 6: // 标识符
            for (i = 0; i < labelnum; i++) {
                if (strcmp(label[i], searchchar) == 0)
                    return i + 1;
            }
            label[labelnum] = (char *)malloc(strlen(searchchar) + 1);
            strcpy(label[labelnum], searchchar);
            labelnum++;
            return i + 1;
    }
    return 0;
}

char alphaprocess(char buffer) {
    int atype;
    int i = -1;
    char alphatp[MAX_TOKEN_LENGTH];
    while ((isalpha(buffer)) || (isdigit(buffer))) {
        alphatp[++i] = buffer;
        buffer = fgetc(fp);
    }
    alphatp[i + 1] = '\0';
    atype = search(alphatp, 1); // 检查是否为关键字
    if (atype) {
        printf("%s \t(1,%d)\n", alphatp, atype);
    } else {
        atype = search(alphatp, 6); // 检查是否为标识符
        printf("%s \t(6,%d)\n", alphatp, atype);
    }
    return buffer;
}

char digitprocess(char buffer) {
    int i = -1;
    char digittp[MAX_TOKEN_LENGTH];
    while (isdigit(buffer)) {
        digittp[++i] = buffer;
        buffer = fgetc(fp);
    }
    digittp[i + 1] = '\0';
    printf("%s \t(5,%d)\n", digittp, atoi(digittp)); // 输出数字及其值
    return buffer;
}

char otherprocess(char buffer) {
    int otype;
    char othertp[3]; // 增加长度以支持多字符运算符
    othertp[0] = buffer;
    othertp[1] = '\0';

    // 检查是否为运算符或关系运算符
    otype = search(othertp, 3);
    if (otype) {
        printf("%s \t(3,%d)\n", othertp, otype);
        buffer = fgetc(fp);
        return buffer;
    }

    otype = search(othertp, 4);
    if (otype) {
        char nextChar = fgetc(fp);
        othertp[1] = nextChar;
        othertp[2] = '\0';
        int otypetp = search(othertp, 4);
        if (otypetp) {
            printf("%s \t(4,%d)\n", othertp, otypetp);
        } else {
            othertp[1] = '\0';
            printf("%s \t(4,%d)\n", othertp, otype);
            ungetc(nextChar, fp); // 将下一个字符放回输入流
        }
        return fgetc(fp); // 继续读取下一个字符
    }

    // 检查是否为分隔符
    otype = search(othertp, 2);
    if (otype) {
        printf("%s \t(2,%d)\n", othertp, otype);
        buffer = fgetc(fp);
        return buffer;
    }

    // 检查是否为赋值运算符 :=
    if (buffer == ':') {
        buffer = fgetc(fp);
        if (buffer == '=') {
            printf(":= \t(2,2)\n");
            buffer = fgetc(fp);
            return buffer;
        } else {
            ungetc(buffer, fp); // 将字符放回输入流
            printf(": \t(2,1)\n");
            buffer = fgetc(fp);
            return buffer;
        }
    }

    // 检查是否为单字符符号（如 '.', '' 等）
    if (buffer == '.') {
        printf(". \t(3,4)\n"); // 假设 '.' 是运算符，编号为 4
        buffer = fgetc(fp);
        return buffer;
    }

    if (buffer == '\'') {
        char charLiteral[3];
        charLiteral[0] = buffer;
        buffer = fgetc(fp); // 读取字符
        charLiteral[1] = buffer;
        buffer = fgetc(fp); // 读取闭合的单引号
        charLiteral[2] = buffer;
        printf("'%c' \t(5,%d)\n", charLiteral[1], charLiteral[1]); // 假设字符常量的编号为 5
        buffer = fgetc(fp);
        return buffer;
    }

    // 新增对 '#'、'%'、'\' 的处理
    if (buffer == '#') {
        printf("# \t(3,5)\n"); // 假设 '#' 是运算符，编号为 5
        buffer = fgetc(fp);
        return buffer;
    }

    if (buffer == '%') {
        printf("%% \t(3,6)\n"); // 假设 '%' 是运算符，编号为 6
        buffer = fgetc(fp);
        return buffer;
    }

    if (buffer == '\\') {
        printf("\\ \t(3,7)\n"); // 假设 '\' 是运算符，编号为 7
        buffer = fgetc(fp);
        return buffer;
    }

    // 新增对双引号及其内部字符串的处理
    if (buffer == '"') {
        char stringLiteral[MAX_TOKEN_LENGTH];
        int i = 0;
        buffer = fgetc(fp); // 读取双引号内的第一个字符
        while (buffer != '"' && buffer != EOF) {
            stringLiteral[i++] = buffer;
            buffer = fgetc(fp);
        }
        stringLiteral[i] = '\0';
        if (buffer == '"') {
            printf("\"%s\" \t(6,%d)\n", stringLiteral, i); // 假设字符串常量的编号为 6
        } else {
            printf("Error: Unterminated string literal\n");
        }
        buffer = fgetc(fp);
        return buffer;
    }

    // 如果无法识别，输出错误信息
    if ((buffer != '\n') && (buffer != ' ')) {
        printf("%c error, not a word\n", buffer);
    }
    buffer = fgetc(fp);
    return buffer;
}

int main() {
    int i;
    for (i = 0; i < MAX_LABELS; i++) {
        label[i] = NULL;
    }
    if ((fp = fopen("example.cpp", "r")) == NULL) {
        printf("File open error\n");
        return 1;
    }

    cbuffer = fgetc(fp);
    while (cbuffer != EOF) {
        if (isalpha(cbuffer)) {
            cbuffer = alphaprocess(cbuffer);
        } else if (isdigit(cbuffer)) {
            cbuffer = digitprocess(cbuffer);
        } else {
            cbuffer = otherprocess(cbuffer);
        }
    }
    printf("Lexical analysis complete.\n");
    fclose(fp);
    return 0;
}
