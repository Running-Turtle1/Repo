#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// �ؼ����б�
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return", "short", "signed", 
    "sizeof", "static", "struct", "switch", "typedef", "union", 
    "unsigned", "void", "volatile", "while"
};

#define NUM_KEYWORDS (sizeof(keywords) / sizeof(keywords[0]))

// Token����
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_SEPARATOR,
    TOKEN_COMMENT,
    TOKEN_STRING,
    TOKEN_CHAR,
    TOKEN_PREPROCESSOR,
    TOKEN_UNKNOWN,
    TOKEN_END
} TokenType;

// Token�ṹ
typedef struct {
    TokenType type;
    char value[256];
} Token;

// ����Ƿ�Ϊ�ؼ���
int isKeyword(const char *str) {
    
	int i;
	for (i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// ��ȡ��һ��Token
Token getNextToken(const char **input) {
    Token token;
    token.type = TOKEN_UNKNOWN;
    token.value[0] = '\0';

    const char *ptr = *input;
    while (isspace(*ptr)) {
        ptr++;
    }

    if (*ptr == '\0') {
        token.type = TOKEN_END;
        strcpy(token.value, "EOF");
        *input = ptr;
        return token;
    }



    // ʶ���ʶ����ؼ���
    if (isalpha(*ptr) || *ptr == '_') {
        int len = 0;
        while (isalnum(*ptr) || *ptr == '_') {
            token.value[len++] = *ptr++;
        }
        token.value[len] = '\0';
        token.type = isKeyword(token.value) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
        *input = ptr;
        return token;
    }
    
// ʶ��ͷ�ļ�
if (*ptr == '<') {
    int len = 0;
    token.value[len++] = *ptr++; // �� '<' ��ӵ� token ֵ��
    int isHeaderFile = 1; // Ĭ��Ϊͷ�ļ�
    while (*ptr && *ptr != '>') {
        if (!isspace(*ptr) && (*(ptr + 1) == '\n' || *(ptr + 1) == '\r' || *(ptr + 1) == '\0')) {
            isHeaderFile = 0; // �����һ���ַ��ǻ��з������ļ�����������Ϊ����ͷ�ļ�
        }
        token.value[len++] = *ptr++; // ��ͷ�ļ�����ӵ� token ֵ��
    }
    if (*ptr == '>') {
        token.value[len++] = *ptr++; // �� '>' ��ӵ� token ֵ��
    }
    token.value[len] = '\0';
    token.type = isHeaderFile ? TOKEN_STRING : TOKEN_OPERATOR; // �����Ƿ�ͷ�ļ�����������
    if(token.type==TOKEN_OPERATOR){
    	while(len--)
    	{
    		ptr--;
		}
		ptr++;
		token.value[0]='<';
		token.value[1]='\0';	
	} 
	
    *input = ptr;
    return token;
}





    // ʶ������
    if (isdigit(*ptr) || *ptr == '.') {
        int len = 0;
        int hasDot = 0;
        while (isdigit(*ptr) || (*ptr == '.' && !hasDot)) {
            if (*ptr == '.') {
                hasDot = 1;
            }
            token.value[len++] = *ptr++;
        }
        token.value[len] = '\0';
        token.type = TOKEN_NUMBER;
        *input = ptr;
        return token;
    }

    // ʶ��ע��
    if (*ptr == '/' && *(ptr + 1) == '/') {
        int len = 0;
        while (*ptr && *ptr != '\n') {
            token.value[len++] = *ptr++;
        }
        token.value[len] = '\0';
        token.type = TOKEN_COMMENT;
        *input = ptr;
        return token;
    }

    if (*ptr == '/' && *(ptr + 1) == '*') {
        int len = 0;
        ptr += 2;  // ���� /*
        while (*ptr && !(*ptr == '*' && *(ptr + 1) == '/')) {
            token.value[len++] = *ptr++;
        }
        if (*ptr == '*' && *(ptr + 1) == '/') {
            ptr += 2;  // ���� */
        }
        token.value[len] = '\0';
        token.type = TOKEN_COMMENT;
        *input = ptr;
        return token;
    }

    // ʶ���ַ���
    if (*ptr == '"') {
        int len = 0;
        token.value[len++] = *ptr++;
        while (*ptr && *ptr != '"') {
            token.value[len++] = *ptr++;
        }
        if (*ptr == '"') {
            token.value[len++] = *ptr++;
        }
        token.value[len] = '\0';
        token.type = TOKEN_STRING;
        *input = ptr;
        return token;
    }

    // ʶ���ַ�����
    if (*ptr == '\'') {
        int len = 0;
        token.value[len++] = *ptr++;
        while (*ptr && *ptr != '\'') {
            token.value[len++] = *ptr++;
        }
        if (*ptr == '\'') {
            token.value[len++] = *ptr++;
        }
        token.value[len] = '\0';
        token.type = TOKEN_CHAR;
        *input = ptr;
        return token;
    }

    // ʶ��������ͷָ���
    const char *operators[] = { "==", "!=", "<=", ">=", "&&", "||", "++", "--", "->", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<", ">>" };
    int matched = 0;
    int i;
	for (i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
        int len = strlen(operators[i]);
        if (strncmp(ptr, operators[i], len) == 0) {
            strncpy(token.value, ptr, len);
            token.value[len] = '\0';
            token.type = TOKEN_OPERATOR;
            ptr += len;
            matched = 1;
            break;
        }
    }

    if (!matched) {
        if (ispunct(*ptr)) {
            token.value[0] = *ptr++;
            token.value[1] = '\0';
            token.type = TOKEN_SEPARATOR;
        } else {
            token.value[0] = *ptr++;
            token.value[1] = '\0';
            token.type = TOKEN_UNKNOWN;
        }
    }

    *input = ptr;
    return token;
}

// ��ȡToken���͵��ַ�����ʾ
const char* getTokenTypeString(TokenType type) {
    switch (type) {
        case TOKEN_IDENTIFIER: return "Identifier";
        case TOKEN_KEYWORD: return "Keyword";
        case TOKEN_NUMBER: return "Number";
        case TOKEN_OPERATOR: return "Operator";
        case TOKEN_SEPARATOR: return "Separator";
        case TOKEN_COMMENT: return "Comment";
        case TOKEN_STRING: return "String";
        case TOKEN_CHAR: return "Char";
        case TOKEN_PREPROCESSOR: return "Preprocessor";
        case TOKEN_UNKNOWN: return "Unknown";
        case TOKEN_END: return "End";
        default: return "Unknown";
    }
}

// ���ļ��ж�ȡ����
char* readFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Unable to open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(length + 1);
    if (!buffer) {
        perror("Unable to allocate buffer");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);

    return buffer;
}

int main() {
    const char *filename = "example.c";
    char *sourceCode = readFile(filename);
    if (!sourceCode) {
        return 1;
    }

    const char *input = sourceCode;
    Token token;

    while ((token = getNextToken(&input)).type != TOKEN_END) {
        printf("Token Type: %s, Token Value: %s\n", getTokenTypeString(token.type), token.value);
    }

    free(sourceCode);
    return 0;
}

