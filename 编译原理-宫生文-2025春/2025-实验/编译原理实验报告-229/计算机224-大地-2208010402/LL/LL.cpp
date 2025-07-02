#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <variant>
#include <algorithm>

using namespace std;

// 终结符枚举
enum TokenType { ID, PLUS, MUL, LPAREN, RPAREN, END };

// 非终结符枚举
enum NonTerminal { E, T, F, G, S };

// 符号类型定义
using Symbol = variant<NonTerminal, TokenType>;

// 类型判断函数
bool isTerminal(const Symbol& s) {
    return holds_alternative<TokenType>(s);
}

// 符号输出重载
ostream& operator<<(ostream& os, const Symbol& s) {
    visit([&](auto&& arg) {
        using T = decay_t<decltype(arg)>;
        if constexpr (is_same_v<T, NonTerminal>) {
            const char* names[] = {"E", "T", "F", "G", "S"};
            os << names[arg];
        } else {
            const char* names[] = {"i", "+", "*", "(", ")", "#"};
            os << names[arg];
        }
    }, s);
    return os;
}

// 产生式结构体
struct Production {
    NonTerminal lhs;
    vector<Symbol> rhs;
    bool isEpsilon = false;
};

// 文法定义
vector<Production> productions = {
    {E,   {T, G}},                     // E → TG
    {G,   {TokenType::PLUS, T, G}},     // G → +TG
    {G,   {}, true},                    // G → ε
    {T,   {F, S}},                      // T → FS
    {S,   {TokenType::MUL, F, S}},      // S → *FS
    {S,   {}, true},                    // S → ε
    {F,   {TokenType::LPAREN, E, TokenType::RPAREN}}, // F → (E)
    {F,   {TokenType::ID}}              // F → i
};

// FIRST和FOLLOW集合类型
using FirstSet = unordered_map<TokenType, bool>;
using FollowSet = unordered_map<TokenType, bool>;
unordered_map<NonTerminal, FirstSet> firstSets;
unordered_map<NonTerminal, FollowSet> followSets;

// 预测分析表类型
using ParsingTable = unordered_map<NonTerminal, 
                         unordered_map<TokenType, const Production*>>;
ParsingTable parsingTable;

// 计算FIRST集合
void computeFirst() {
    bool changed;
    do {
        changed = false;
        for (const auto& prod : productions) {
            if (prod.isEpsilon) {
                if (!firstSets[prod.lhs].count(END)) {
                    firstSets[prod.lhs][END] = true;
                    changed = true;
                }
                continue;
            }

            for (const auto& symbol : prod.rhs) {
                if (holds_alternative<TokenType>(symbol)) {
                    TokenType term = get<TokenType>(symbol);
                    if (!firstSets[prod.lhs].count(term)) {
                        firstSets[prod.lhs][term] = true;
                        changed = true;
                    }
                    break;
                } else {
                    NonTerminal nt = get<NonTerminal>(symbol);
                    for (const auto& [t, _] : firstSets[nt]) {
                        if (t != END && !firstSets[prod.lhs].count(t)) {
                            firstSets[prod.lhs][t] = true;
                            changed = true;
                        }
                    }
                    if (!firstSets[nt].count(END)) break;
                }
            }
        }
    } while (changed);
}

// 计算FOLLOW集合
void computeFollow() {
    followSets[E][END] = true;

    bool changed;
    do {
        changed = false;
        for (const auto& prod : productions) {
            for (size_t i = 0; i < prod.rhs.size(); ++i) {
                if (holds_alternative<NonTerminal>(prod.rhs[i])) {
                    NonTerminal B = get<NonTerminal>(prod.rhs[i]);
                    
                    // 处理A → αBβ的情况
                    bool canEpsilon = true;
                    for (size_t j = i+1; j < prod.rhs.size() && canEpsilon; ++j) {
                        if (holds_alternative<TokenType>(prod.rhs[j])) {
                            TokenType term = get<TokenType>(prod.rhs[j]);
                            if (!followSets[B].count(term)) {
                                followSets[B][term] = true;
                                changed = true;
                            }
                            canEpsilon = false;
                        } else {
                            NonTerminal nt = get<NonTerminal>(prod.rhs[j]);
                            for (const auto& [t, _] : firstSets[nt]) {
                                if (t != END && !followSets[B].count(t)) {
                                    followSets[B][t] = true;
                                    changed = true;
                                }
                            }
                            canEpsilon = firstSets[nt].count(END);
                        }
                    }

                    // 处理A → αB 或 β → ε的情况
                    if (canEpsilon) {
                        for (const auto& [t, _] : followSets[prod.lhs]) {
                            if (!followSets[B].count(t)) {
                                followSets[B][t] = true;
                                changed = true;
                            }
                        }
                    }
                }
            }
        }
    } while (changed);
}

// 初始化分析表
void initParsingTable() {
    for (const auto& prod : productions) {
        unordered_map<TokenType, bool> select;
        
        // 计算SELECT集合
        if (prod.isEpsilon) {
            select = followSets[prod.lhs];
        } else {
            bool hasEpsilon = true;
            for (const auto& symbol : prod.rhs) {
                if (holds_alternative<TokenType>(symbol)) {
                    TokenType term = get<TokenType>(symbol);
                    select[term] = true;
                    hasEpsilon = false;
                    break;
                } else {
                    NonTerminal nt = get<NonTerminal>(symbol);
                    for (const auto& [t, _] : firstSets[nt]) {
                        select[t] = true;
                    }
                    hasEpsilon = firstSets[nt].count(END);
                    if (!hasEpsilon) break;
                }
            }
            if (hasEpsilon) {
                for (const auto& [t, _] : followSets[prod.lhs]) {
                    select[t] = true;
                }
            }
        }

        // 填充分析表
        for (const auto& [t, _] : select) {
            if (parsingTable[prod.lhs].count(t)) {
                cerr << "文法非LL(1)! 冲突产生式: " 
                     << prod.lhs << " 在符号 " << t << endl;
                exit(1);
            }
            parsingTable[prod.lhs][t] = &prod;
        }
    }
}

// 语法分析过程
void parse(const vector<TokenType>& input) {
    stack<Symbol> stk;
    stk.push(TokenType::END); // 结束符
    stk.push(E);              // 起始符号

    vector<TokenType> buffer(input);
    buffer.push_back(TokenType::END);
    size_t ptr = 0;

    int step = 1;
    cout << "步骤\t分析栈\t\t剩余输入\t动作" << endl;

    while (!stk.empty()) {
        Symbol top = stk.top();
        TokenType current = buffer[ptr];

        // 输出当前状态
        cout << step++ << "\t";
        stack<Symbol> temp = stk;
        while (!temp.empty()) {
            cout << temp.top() << " ";
            temp.pop();
        }
        cout << "\t\t";
        for (size_t i = ptr; i < buffer.size(); ++i) {
            cout << Symbol(buffer[i]) << " ";
        }
        cout << "\t";

        // 处理栈顶符号
        if (holds_alternative<TokenType>(top)) {
            TokenType t = get<TokenType>(top);
            if (t == TokenType::END) {
                if (current == TokenType::END) {
                    cout << "接受" << endl;
                    return;
                } else {
                    cout << "错误：输入未结束" << endl;
                    exit(1);
                }
            }

            if (t == current) {
                cout << "匹配 " << Symbol(t) << endl;
                stk.pop();
                ptr++;
            } else {
                cout << "错误：预期 " << Symbol(t) 
                     << " 但遇到 " << Symbol(current) << endl;
                exit(1);
            }
        } else {
            NonTerminal nt = get<NonTerminal>(top);
            if (!parsingTable[nt].count(current)) {
                cout << "错误：无可用产生式 (" 
                     << Symbol(nt) << ", " << Symbol(current) << ")" << endl;
                exit(1);
            }

            const Production* prod = parsingTable[nt][current];
            stk.pop();

            cout << "应用 " << Symbol(nt) << " → ";
            for (const auto& s : prod->rhs) cout << s << " ";
            if (prod->isEpsilon) cout << "ε";
            cout << endl;

            if (!prod->isEpsilon) {
                for (auto it = prod->rhs.rbegin(); it != prod->rhs.rend(); ++it) {
                    stk.push(*it);
                }
            }
        }
    }
}

int main() {
    computeFirst();
    computeFollow();
    initParsingTable();

    vector<TokenType> test1 = {ID, PLUS, ID, MUL, ID};      // i + i * i
    vector<TokenType> test2 = {LPAREN, ID, PLUS, ID, RPAREN}; // (i + i)

    cout << "==== 测试1 ====" << endl;
    parse(test1);

    cout << "\n==== 测试2 ====" << endl;
    parse(test2);

    return 0;
}