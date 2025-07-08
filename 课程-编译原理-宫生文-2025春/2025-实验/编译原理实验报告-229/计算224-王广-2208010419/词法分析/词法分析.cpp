#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>

enum TokenType {
    KEYWORD,
    IDENTIFIER,
    INTEGER_CONSTANT,
    FLOAT_CONSTANT,
    CHAR_CONSTANT,
    STRING_CONSTANT,
    OPERATOR,
    DELIMITER,
    COMMENT,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};

class Lexer {
public:
    Lexer(const std::string& source) : source(source), pos(0) {}

    std::vector<Token> analyze() {
        std::vector<Token> tokens;
        while (pos < source.length()) {
            skipWhitespace();
            if (pos >= source.length()) break;

            char currentChar = source[pos];
            if (isalpha(currentChar) || currentChar == '_') {
                tokens.push_back(processIdentifier());
            }
            else if (isdigit(currentChar)) {
                tokens.push_back(processNumber());
            }
            else if (currentChar == '\'' || currentChar == '"') {
                tokens.push_back(processString(currentChar));
            }
            else if (isOperator(currentChar)) {
                tokens.push_back(Token(OPERATOR, std::string(1, currentChar)));
                advance();
            }
            else if (isDelimiter(currentChar)) {
                tokens.push_back(Token(DELIMITER, std::string(1, currentChar)));
                advance();
            }
            else if (currentChar == '/') {
                tokens.push_back(processComment());
            }
            else {
                tokens.push_back(Token(UNKNOWN, std::string(1, currentChar)));
                advance();
            }
        }
        return tokens;
    }

private:
    std::string source;
    size_t pos;

    void advance() {
        pos++;
    }

    void skipWhitespace() {
        while (pos < source.length() && std::isspace(source[pos])) {
            advance();
        }
    }

    bool isOperator(char c) {
        static const std::string operators = "+-*/=><!%";
        return operators.find(c) != std::string::npos;
    }

    bool isDelimiter(char c) {
        static const std::string delimiters = "();,{}[]";
        return delimiters.find(c) != std::string::npos;
    }

    Token processIdentifier() {
        size_t start = pos;
        while (pos < source.length() && (isalnum(source[pos]) || source[pos] == '_')) {
            advance();
        }
        std::string ident = source.substr(start, pos - start);
        if (isKeyword(ident)) {
            return Token(KEYWORD, ident);
        }
        return Token(IDENTIFIER, ident);
    }

    Token processNumber() {
        size_t start = pos;
        bool isFloat = false;
        while (pos < source.length() && isdigit(source[pos])) {
            advance();
        }
        if (pos < source.length() && source[pos] == '.') {
            isFloat = true;
            advance();
            while (pos < source.length() && isdigit(source[pos])) {
                advance();
            }
        }
        std::string number = source.substr(start, pos - start);
        return isFloat ? Token(FLOAT_CONSTANT, number) : Token(INTEGER_CONSTANT, number);
    }

    Token processString(char quoteChar) {
        size_t start = pos;
        advance();
        while (pos < source.length()) {
            if (source[pos] == quoteChar) {
                break;
            }
            else if (source[pos] == '\\') {
                advance(); // Skip escape character
            }
            advance();
        }
        if (pos < source.length() && source[pos] == quoteChar) {
            advance();
        }
        std::string str = source.substr(start, pos - start);
        return quoteChar == '"' ? Token(STRING_CONSTANT, str) : Token(CHAR_CONSTANT, str);
    }

    Token processComment() {
        size_t start = pos;
        advance();
        if (pos < source.length() && source[pos] == '/') {
            // Single-line comment
            while (pos < source.length() && source[pos] != '\n') {
                advance();
            }
            advance();
            return Token(COMMENT, source.substr(start, pos - start));
        }
        else if (pos < source.length() && source[pos] == '*') {
            // Multi-line comment
            advance();
            while (pos + 1 < source.length()) {
                if (source[pos] == '*' && source[pos + 1] == '/') {
                    advance();
                    advance();
                    break;
                }
                advance();
            }
            return Token(COMMENT, source.substr(start, pos - start));
        }
        return Token(UNKNOWN, source.substr(start, pos - start));
    }

    bool isKeyword(const std::string& str) {
        static const std::unordered_set<std::string> keywords = {
            "int", "float", "char", "if", "else", "for", "while", "return"
        };
        return keywords.find(str) != keywords.end();
    }
};

int main() {
    std::string sourceCode = R"(
        int main() {
            int a = 10;
            float b = 3.14;
            char c = 'A';
            return 0;
        }
    )";
   
    Lexer lexer(sourceCode);
    std::vector<Token> tokens = lexer.analyze();

    for (const auto& token : tokens) {
        std::cout << "Token: " << token.value << ", Type: ";
        switch (token.type) {
        case KEYWORD: std::cout << "KEYWORD"; break;
        case IDENTIFIER: std::cout << "IDENTIFIER"; break;
        case INTEGER_CONSTANT: std::cout << "INTEGER_CONSTANT"; break;
        case FLOAT_CONSTANT: std::cout << "FLOAT_CONSTANT"; break;
        case CHAR_CONSTANT: std::cout << "CHAR_CONSTANT"; break;
        case STRING_CONSTANT: std::cout << "STRING_CONSTANT"; break;
        case OPERATOR: std::cout << "OPERATOR"; break;
        case DELIMITER: std::cout << "DELIMITER"; break;
        case COMMENT: std::cout << "COMMENT"; break;
        case UNKNOWN: std::cout << "UNKNOWN"; break;
        }
        std::cout << std::endl;
    }

    return 0;
}