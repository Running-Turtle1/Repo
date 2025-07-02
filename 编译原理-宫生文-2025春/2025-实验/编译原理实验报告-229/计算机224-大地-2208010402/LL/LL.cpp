#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <variant>
#include <algorithm>

using namespace std;

// �ս��ö��
enum TokenType { ID, PLUS, MUL, LPAREN, RPAREN, END };

// ���ս��ö��
enum NonTerminal { E, T, F, G, S };

// �������Ͷ���
using Symbol = variant<NonTerminal, TokenType>;

// �����жϺ���
bool isTerminal(const Symbol& s) {
    return holds_alternative<TokenType>(s);
}

// �����������
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

// ����ʽ�ṹ��
struct Production {
    NonTerminal lhs;
    vector<Symbol> rhs;
    bool isEpsilon = false;
};

// �ķ�����
vector<Production> productions = {
    {E,   {T, G}},                     // E �� TG
    {G,   {TokenType::PLUS, T, G}},     // G �� +TG
    {G,   {}, true},                    // G �� ��
    {T,   {F, S}},                      // T �� FS
    {S,   {TokenType::MUL, F, S}},      // S �� *FS
    {S,   {}, true},                    // S �� ��
    {F,   {TokenType::LPAREN, E, TokenType::RPAREN}}, // F �� (E)
    {F,   {TokenType::ID}}              // F �� i
};

// FIRST��FOLLOW��������
using FirstSet = unordered_map<TokenType, bool>;
using FollowSet = unordered_map<TokenType, bool>;
unordered_map<NonTerminal, FirstSet> firstSets;
unordered_map<NonTerminal, FollowSet> followSets;

// Ԥ�����������
using ParsingTable = unordered_map<NonTerminal, 
                         unordered_map<TokenType, const Production*>>;
ParsingTable parsingTable;

// ����FIRST����
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

// ����FOLLOW����
void computeFollow() {
    followSets[E][END] = true;

    bool changed;
    do {
        changed = false;
        for (const auto& prod : productions) {
            for (size_t i = 0; i < prod.rhs.size(); ++i) {
                if (holds_alternative<NonTerminal>(prod.rhs[i])) {
                    NonTerminal B = get<NonTerminal>(prod.rhs[i]);
                    
                    // ����A �� ��B�µ����
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

                    // ����A �� ��B �� �� �� �ŵ����
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

// ��ʼ��������
void initParsingTable() {
    for (const auto& prod : productions) {
        unordered_map<TokenType, bool> select;
        
        // ����SELECT����
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

        // ��������
        for (const auto& [t, _] : select) {
            if (parsingTable[prod.lhs].count(t)) {
                cerr << "�ķ���LL(1)! ��ͻ����ʽ: " 
                     << prod.lhs << " �ڷ��� " << t << endl;
                exit(1);
            }
            parsingTable[prod.lhs][t] = &prod;
        }
    }
}

// �﷨��������
void parse(const vector<TokenType>& input) {
    stack<Symbol> stk;
    stk.push(TokenType::END); // ������
    stk.push(E);              // ��ʼ����

    vector<TokenType> buffer(input);
    buffer.push_back(TokenType::END);
    size_t ptr = 0;

    int step = 1;
    cout << "����\t����ջ\t\tʣ������\t����" << endl;

    while (!stk.empty()) {
        Symbol top = stk.top();
        TokenType current = buffer[ptr];

        // �����ǰ״̬
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

        // ����ջ������
        if (holds_alternative<TokenType>(top)) {
            TokenType t = get<TokenType>(top);
            if (t == TokenType::END) {
                if (current == TokenType::END) {
                    cout << "����" << endl;
                    return;
                } else {
                    cout << "��������δ����" << endl;
                    exit(1);
                }
            }

            if (t == current) {
                cout << "ƥ�� " << Symbol(t) << endl;
                stk.pop();
                ptr++;
            } else {
                cout << "����Ԥ�� " << Symbol(t) 
                     << " ������ " << Symbol(current) << endl;
                exit(1);
            }
        } else {
            NonTerminal nt = get<NonTerminal>(top);
            if (!parsingTable[nt].count(current)) {
                cout << "�����޿��ò���ʽ (" 
                     << Symbol(nt) << ", " << Symbol(current) << ")" << endl;
                exit(1);
            }

            const Production* prod = parsingTable[nt][current];
            stk.pop();

            cout << "Ӧ�� " << Symbol(nt) << " �� ";
            for (const auto& s : prod->rhs) cout << s << " ";
            if (prod->isEpsilon) cout << "��";
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

    cout << "==== ����1 ====" << endl;
    parse(test1);

    cout << "\n==== ����2 ====" << endl;
    parse(test2);

    return 0;
}