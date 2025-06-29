#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>

// Token 类型枚举
enum class TokenType {
    IDENT, KEYWORD,
    INT_LITERAL, FLOAT_LITERAL,
    STR_LITERAL, CHAR_LITERAL,
    OPERATOR, PUNCTUATOR,
    END_OF_FILE, UNKNOWN
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line, col;
};

static const std::unordered_map<std::string, TokenType> keywords = {
    {"if", TokenType::KEYWORD}, {"else", TokenType::KEYWORD},
    {"while", TokenType::KEYWORD}, {"for", TokenType::KEYWORD},
    {"return", TokenType::KEYWORD}, {"int", TokenType::KEYWORD},
    {"float", TokenType::KEYWORD}, {"double", TokenType::KEYWORD},
    {"char", TokenType::KEYWORD}, {"void", TokenType::KEYWORD},
};

class Lexer {
public:
    Lexer(const std::string& src)
      : source(src), curPos(0), line(1), col(1) { initTransitionTable(); }

    Token nextToken() {
        skipWhitespaceAndComments();
        if (curPos >= source.size())
            return {TokenType::END_OF_FILE, "", line, col};
        int state = 0, lastAccept = -1;
        size_t startPos = curPos, lastPos = curPos;
        int startLine = line, startCol = col;
        std::string lexeme;
        while (true) {
            // peek : [CS] Read Data
            char c = peek(); 
            int nxt = (c >= 0 && c < 128) ? transition[state][(unsigned char)c] : -1;
            if (nxt < 0) break;
            state = nxt;
            lexeme.push_back(getChar());
            if (acceptState.count(state)) {
                lastAccept = state;
                lastPos = curPos;
            }
        }
        if (lastAccept >= 0) {
            curPos = lastPos;
            std::string tk = source.substr(startPos, lastPos - startPos);
            TokenType tp = acceptState[lastAccept];
            // KEYWORD is the subset of IDENT
            if (tp == TokenType::IDENT && keywords.count(tk)) tp = TokenType::KEYWORD;
            return {tp, tk, startLine, startCol};
        }
        std::string bad = lexeme.empty() ? std::string(1, peek()) : lexeme;
        error("Invalid token: " + bad);
        getChar();
        return {TokenType::UNKNOWN, bad, line, col};
    }

private:
    std::string source;
    size_t curPos;
    int line, col;
    std::vector<std::vector<int>> transition;
    std::unordered_map<int, TokenType> acceptState;

    void initTransitionTable() {
        int N = 100;
        transition.assign(N, std::vector<int>(128, -1));
        acceptState.clear();
        const int S_IDENT=1, S_INT=2, S_DOT=3, S_FLOAT=4, S_EXP=5, S_EXP_SIGN=6, S_EXP_NUM=7;
        const int S_STR=8, S_STR_CONT=9, S_STR_ESC=10;
        const int S_CHAR=11, S_CHAR_CONT=12, S_CHAR_ESC=13;
        int st=20;
        auto newState=[&](){ return st++; };
        // identifier
        for(char c='A';c<='Z';++c) transition[0][c]=S_IDENT;
        for(char c='a';c<='z';++c) transition[0][c]=S_IDENT;
        transition[0]['_']=S_IDENT;
        for(char c='A';c<='Z';++c) transition[S_IDENT][c]=S_IDENT;
        for(char c='a';c<='z';++c) transition[S_IDENT][c]=S_IDENT;
        for(char c='0';c<='9';++c) transition[S_IDENT][c]=S_IDENT;
        transition[S_IDENT]['_']=S_IDENT;
        acceptState[S_IDENT]=TokenType::IDENT;
        // integer & float
        for(char c='0';c<='9';++c) transition[0][c]=S_INT;
        for(char c='0';c<='9';++c) transition[S_INT][c]=S_INT;
        transition[S_INT]['.']=S_DOT;
        acceptState[S_INT]=TokenType::INT_LITERAL;
        transition[0]['.']=S_DOT;
        for(char c='0';c<='9';++c) transition[S_DOT][c]=S_FLOAT;
        for(char c='0';c<='9';++c) transition[S_FLOAT][c]=S_FLOAT;
        acceptState[S_FLOAT]=TokenType::FLOAT_LITERAL;
        transition[S_FLOAT]['e']=transition[S_FLOAT]['E']=S_EXP;
        for(char c='0';c<='9';++c) transition[S_EXP][c]=S_EXP_NUM;
        transition[S_EXP]['+']=transition[S_EXP]['-']=S_EXP_SIGN;
        for(char c='0';c<='9';++c) transition[S_EXP_SIGN][c]=S_EXP_NUM;
        for(char c='0';c<='9';++c) transition[S_EXP_NUM][c]=S_EXP_NUM;
        acceptState[S_EXP_NUM]=TokenType::FLOAT_LITERAL;
        // string literal
        transition[0]['"']=S_STR;
        for(int i=0;i<128;++i) transition[S_STR][i]=S_STR_CONT;
        for(int i=0;i<128;++i) transition[S_STR_CONT][i]=S_STR_CONT;
        transition[S_STR_CONT]['\\']=S_STR_ESC;
        for(int i=0;i<128;++i) transition[S_STR_ESC][i]=S_STR_CONT;
        int S_STR_END=newState();
        transition[S_STR_CONT]['"']=S_STR_END;
        acceptState[S_STR_END]=TokenType::STR_LITERAL;
        // char literal
        transition[0]['\'']=S_CHAR;
        for(int i=0;i<128;++i) transition[S_CHAR][i]=S_CHAR_CONT;
        for(int i=0;i<128;++i) transition[S_CHAR_CONT][i]=S_CHAR_CONT;
        transition[S_CHAR_CONT]['\\']=S_CHAR_ESC;
        for(int i=0;i<128;++i) transition[S_CHAR_ESC][i]=S_CHAR_CONT;
        int S_CHAR_END=newState();
        transition[S_CHAR_CONT]['\'']=S_CHAR_END;
        acceptState[S_CHAR_END]=TokenType::CHAR_LITERAL;
        // operators & punctuators
        auto addOp=[&](char c, TokenType tp){ int s=newState(); transition[0][c]=s; acceptState[s]=tp; };
        auto addTwo=[&](char c, char c2, TokenType tp){ int s1=newState(), s2=newState(); transition[0][c]=s1; transition[s1][c2]=s2; acceptState[s1]=tp; acceptState[s2]=tp; };
        addTwo('=','=',TokenType::OPERATOR);
        addTwo('!','=',TokenType::OPERATOR);
        addTwo('<','=',TokenType::OPERATOR);
        addTwo('>','=',TokenType::OPERATOR);
        addTwo('+','+',TokenType::OPERATOR); addTwo('+','=',TokenType::OPERATOR);
        addTwo('-','-',TokenType::OPERATOR); addTwo('-','=',TokenType::OPERATOR); addTwo('-','>',TokenType::OPERATOR);
        addTwo('*','=',TokenType::OPERATOR); addTwo('/','=',TokenType::OPERATOR); addTwo('%','=',TokenType::OPERATOR);
        addTwo('&','&',TokenType::OPERATOR); addTwo('&','=',TokenType::OPERATOR);
        addTwo('|','|',TokenType::OPERATOR); addTwo('|','=',TokenType::OPERATOR);
        addTwo('^','=',TokenType::OPERATOR); addOp('~',TokenType::OPERATOR);
        addOp(';',TokenType::PUNCTUATOR); addOp(',',TokenType::PUNCTUATOR);
        addOp('(',TokenType::PUNCTUATOR); addOp(')',TokenType::PUNCTUATOR);
        addOp('{',TokenType::PUNCTUATOR); addOp('}',TokenType::PUNCTUATOR);
        addOp('[',TokenType::PUNCTUATOR); addOp(']',TokenType::PUNCTUATOR);
        addOp(':',TokenType::PUNCTUATOR); addOp('?',TokenType::PUNCTUATOR);
    }

    char getChar() { char c=source[curPos++]; if(c=='\n'){line++;col=1;}else col++; return c; }
    char peek() const { return curPos<source.size()?source[curPos]:'\0'; }
    void skipWhitespaceAndComments() {
        while(true) {
            char c=peek();
            if(isspace(c)){getChar();continue;}
            if(c=='/'&&curPos+1<source.size()){
                if(source[curPos+1]=='/') { getChar();getChar(); while(peek()!='\n'&&peek()!='\0') getChar(); continue; }
                if(source[curPos+1]=='*') { getChar();getChar(); while(!(peek()=='*'&&curPos+1<source.size()&&source[curPos+1]=='/')){ if(peek()=='\0') return; getChar(); } getChar();getChar(); continue; }
            }
            break;
        }
    }
    [[noreturn]] void error(const std::string& msg){ std::cerr<<"[Lexer Error] Line "<<line<<", Col "<<col<<": "<<msg<<std::endl; exit(1); }
};

int main() {
    std::string code, line;
    while (std::getline(std::cin, line)) { code += line + "\n"; }
    Lexer lexer(code);
    Token tok;
    while ((tok = lexer.nextToken()).type != TokenType::END_OF_FILE) {
        std::cout << "Token(" << int(tok.type) << ", \"" << tok.lexeme << "\") at ["
                  << tok.line << "," << tok.col << "]\n";
    }
    return 0;
}
// Add Info : while 读入, 请采用文件输入测试 或 使用 CPH 测试
