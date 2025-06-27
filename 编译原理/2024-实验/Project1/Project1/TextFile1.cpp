#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

map<char, set<string>> p; //����ʽ
map<char, set<pair<string, set<char>>>> select; //select��
map<char, int> nul; //�Ƿ�����Ƶ�����
map<char, set<char>> first, follow, includ; //first����follow��
map<char, int> done; //��first���Ǳ���Ƿ��Ѿ�������
set<char> vn, vt; //���ս�����ս��
map<char, map<char, string>> M; //Ԥ�������
char start; //��ʼ��
const char N = '@';
const string blank = "                                                     ";

inline bool in_vt(char c) {
    if (vt.find(c) != vt.end()) return true;
    return false;
}

inline bool in_vn(char c) {
    if (vn.find(c) != vn.end()) return true;
    return false;
}

inline bool is_low(char c) {
    if (!(c >= 'A' && c <= 'Z')) return true;
    return false;
}

bool check_has_vt(const string &now) {
    int len = (int) now.size();
    for (int i = 0; i < len; i++)
        if (in_vt(now[i])) return true;
    return false;
}

int all_null(const string &now) {
    if (now == "null") return true;
    int len = (int) now.size();
    int f = 0;
    for (int i = 0; i < len; i++)
        if (nul[now[i]] == 0) {
            return 0;
        } else if (nul[now[i]] == -1) {
            f = 1;
        }
    if (f) return -1;
    return 1;
}

void init() {
    ifstream OutFile;
    OutFile.open("/G:\Desktop\data.txt");
    char c;
    string str;
    int f = 0;
    while (!OutFile.eof()) {
        OutFile >> c >> str;
        if (!f) {f = 1; start = c;}
        p[c].insert(str);
        vn.insert(c);
    }
}

void get_nul() {
    map<char, set<string>> cur(p); //����һ�ݲ���ʽ(��Ϊ�漰��ɾ��������Ϊ�˱���ԭ����ʽ���ڸ��Ƶ�����Ͻ���ɾ������)
    set<char> now; //���״̬δ���ķ��ս��
    for (auto it = cur.begin(); it != cur.end(); ++it) {
        nul[it->first] = -1; //״̬��Ϊ����
        for (auto i = it->second.begin(); i != it->second.end();) {
            string t = *i;
            if (t != "null") for (int j = 0, len = (int) t.size(); j < len; j++)
                if (is_low(t[j])) vt.insert(t[j]);
            if (*i == "null") {
                /*
                 �÷��ս�����Ƶ����մ������÷��ս���ı�־��Ϊ1����ɾ���÷��ս�������в���ʽ
                 �˴�������ɾ��������������now�����Щ״̬δ���ķ��ս����������ֻȥ����now�е�Ԫ�أ��������÷��ս��Ҳ�ͱ��౻��ɾ������
                */
                nul[it->first] = 1;
                break;
            } else if (check_has_vt(*i)) {
                //������ʽ�д����ս������ɾ���ò���ʽ
                auto d = i;
                ++i; //ָ���Ⱥ��ƣ���ɾ��
                it->second.erase(*d);
                continue;
            } else {
                //��ȫΪ���ս���������ò���ʽ
                ++i;
            }
        }
        if ((int) it->second.size() > 0 && nul[it->first] != 1) {
            // ����÷��ս���������Ҳ�ΪȫΪ���ս���Ĳ���ʽ����״̬��Ϊ1�������now�н��к�������
            now.insert(it->first);
        } else if (nul[it->first] == -1) {
            // ����÷��ս���������Ҳ�ΪȫΪ���ս���Ĳ���ʽ����״̬Ϊ�����������޷��Ƶ�Ϊ�մ�����Ϊ0
            nul[it->first] = 0;
        }
    }
    string bk = "                                               ";
    cout << "\n\n" << bk << "һ��ɨ���ʣ�µĲ���ʽ:" << '\n' << '\n';
    for (auto it = cur.begin(); it != cur.end(); ++it) {
        for (auto i = it->second.begin(); i != it->second.end(); ++i) {
            cout << blank << it->first << " -> "<< *i << '\n';
        }
    }
    bk = "                                                 ";
    cout << "\n\n" << bk << "һ��ɨ���״̬:" << '\n' << '\n';
    for (auto it = nul.begin(); it != nul.end(); ++it) {
        cout << blank << it->first << ": " << it->second << '\n';
    }
    cout << '\n';
    int flag; //���ڼ�¼�������ޱ仯
    do {
        flag = 0; //�տ�ʼʱ��Ϊ�ޱ仯
        for (auto it = now.begin(); it != now.end();) {
            int f = 0; //�����ж�now���Ƿ�Ӧ��ɾ���÷��ս��
            for (auto i = cur[*it].begin(); i != cur[*it].end();) {
                int check = all_null(*i);
                if (check == 1) {
                    // ������ʽ�Ҳ��ķ��ս��ȫ�����Ƶ����մ�����÷��ս�����Ƶ�����
                    nul[*it] = 1;
                    flag = f = 1; // (1)�б仯 (2)��now��ɾ���÷��ս��(ɾ���÷��ս�����в���ʽ)
                    break;
                } else if (check == 0) {
                    // ������ʽ�Ҳ��ķ��ս���еĲ����Ƶ�Ϊ�գ���ɾ���ò���ʽ
                    flag = f = 1; // ��now��ɾ���÷��ս��(ɾ���÷��ս�����в���ʽ)
                    auto d = i;
                    ++i;
                    cur[*it].erase(d);
                } else {
                    // ������ʽ�Ҳ��ķ��ս�������ڴ���״̬������ʱ����
                    ++i;
                }
            }
            // ���û�в���ʽ�˲��Ҹ÷��ս��״̬���Ǵ������򽫸÷��ս��״̬��Ϊ0���Ҵ�now��ɾ��
            if ((int) cur[*it].size() == 0 && nul[*it] == -1) {
                nul[*it] = 0;
                f = 1;
            }
            if (f) {
                // �÷��ս�����Ƶ����ջ��߲����Ƶ����գ���now��ɾ���÷��ս��
                auto d = it;
                ++it;
                now.erase(*d);
            } else {
                ++it;
            }
        }
    } while (flag);
    bk = "                                                    ";
    cout << "\n" << bk << "����״̬:" << '\n' << '\n';
    for (auto it = nul.begin(); it != nul.end(); ++it) {
        cout << blank << it->first << ": " << it->second << '\n';
    }
}

set<char> dfs(char now) {
    if (in_vt(now)) { //����Ƿ��ս������first��Ϊ����
        set<char> t;
        t.insert(now);
        return t;
    } else {
        if (done[now]) //����÷��ս����first���Ѿ�������ˣ���ֱ�ӷ��ؼ��ɣ������ظ����
            return first[now];
        for (auto it = p[now].begin(); it != p[now].end(); ++it) {
            string r = *it;
            if (r == "null") { //������Ƶ����մ����򽫿մ�����first��
                first[now].insert(N);
            } else {
                int len = (int) r.size();
                for (int i = 0; i < len; i++) {
                    if (in_vn(r[i])) { //��Ϊ���ս�������м����������������������������first��
                        auto h = dfs(r[i]); //dfs�����÷��ս����first��
                        if (nul[r[i]] && (h.find(N) != h.end())) h.erase(N); //����пմ������޳��մ�
                        for (auto j = h.begin(); j != h.end(); ++j) first[now].insert(*j); //����first��
                        if (nul[r[i]] != 1) { //�����ǰ��ĸ�����Ƶ�Ϊ�մ�������������û�пմ�����
                            break;
                        } else if (i == len - 1) { //�����ǰ��ĸ���Ƶ�Ϊ�մ����������һ��������fisrt���м��Ͽմ�
                            first[now].insert(N);
                        }
                    } else { //��Ϊ�ս������first������������
                        first[now].insert(r[i]);
                        break;
                    }
                }
            }
        }
        done[now] = 1; // ���ϱ�ǣ���ʾ�÷��ս����first���Ѿ�������ˣ��´�ʹ��ʱֱ�ӷ��ؼ��ɣ������ظ����
        return first[now];
    }
}

void get_first() {
    for (auto it = vn.begin(); it != vn.end(); ++it) dfs(*it); //��ÿ�����ս������dfs
    string bk = "                                                    ";
    cout << "\n\n" << bk << "First��Ϊ:" << '\n' << '\n';
    for (auto it = first.begin(); it != first.end(); ++it) {
        cout << blank << "FIRST(" << it->first << ") = {";
        for (auto j = it->second.begin(); j != it->second.end();) {
            cout << *j++;
            if (j != it->second.end()) cout << ",";
        }
        cout << "} \n";
        
    }
}

void get_follow() {
    follow[start].insert('#'); //�ѡ�#�������ķ���ʼ���ŵ�Follow����
    for (auto it = p.begin(); it != p.end(); ++it) {
        for (auto i = it->second.begin(); i != it->second.end(); ++i) {
            string r = *i;
            int len = (int) r.size();
            for (int i = 0; i < len; i++) {
                if (in_vn(r[i]) && i != len - 1) {
                    if (in_vn(r[i + 1])) { //�ұ�Ϊ���ս��
                        //follow���м����ұ�Ϊ���ս��first�еķǿ�Ԫ��
                        for (auto it = first[r[i + 1]].begin(); it != first[r[i + 1]].end(); ++it)
                            if (*it != N) follow[r[i]].insert(*it);
                        //����ұߵķ��ս�����Ƶ�������Ϊ����ʽ���һ��Ԫ�أ�����ϲ���ʽ��ߵķ��ս����follow��
                        if (nul[r[i + 1]] && i + 1 == len - 1) includ[r[i]].insert(it->first);
                    } else {
                        follow[r[i]].insert(r[i + 1]); //�ұߵ�Ϊ�ս����ֱ�ӽ����ӵ�follow����
                    }
                } else if (in_vn(r[i])) {
                    includ[r[i]].insert(it->first);
                }
            }
        }
    }
    string bk = "                                                    ";
    cout << "\n\n" << bk << "includΪ:" << '\n' << '\n';
    for (auto it = includ.begin(); it != includ.end(); ++it) {
        cout << blank << it->first << ":{ ";
        for (auto j = it->second.begin(); j != it->second.end(); ++j) {
            cout << *j << " ";
        }
        cout << "} \n";
    }
    int flag;
    do {
        flag = 0;
        for (auto it = includ.begin(); it != includ.end(); ++it) {
            int cur = (int) follow[it->first].size();
            for (auto i = it->second.begin(); i != it->second.end(); ++i) {
                for (auto j = follow[*i].begin(); j != follow[*i].end(); ++j) {
                    follow[it->first].insert(*j);
                }
            }
            if ((int) follow[it->first].size() > cur) flag = 1;
        }
    } while (flag);
    cout << "\n\n" << bk << "Follow��Ϊ:" << '\n' << '\n';
    for (auto it = follow.begin(); it != follow.end(); ++it) {
        cout << blank << "FOLLOW(" << it->first << ") = {";
        for (auto j = it->second.begin(); j != it->second.end();) {
            cout << *j++;
            if (j != it->second.end()) cout << ",";
        }
        cout << "} \n";
    }
}

void get_select() {
    for (auto it = p.begin(); it != p.end(); ++it) {
        for (auto i = it->second.begin(); i != it->second.end(); ++i) {
            set<char> t;
            string r = *i;
            if (r == "null") {
                for (auto l = follow[it->first].begin(); l != follow[it->first].end(); ++l)
                    t.insert(*l);
                select[it->first].insert({r, t});
                continue;
            }
            int len = (int) r.size();
            for (int j = 0; j < len; j++) {
                if (in_vn(r[j])) {
                    for (auto k = first[r[j]].begin(); k != first[r[j]].end(); ++k)
                        if (*k != N) t.insert(*k);
                    if (nul[r[j]]) {
                        if (j == len - 1)
                            for (auto l = follow[it->first].begin(); l != follow[it->first].end(); ++l)
                                t.insert(*l);
                    } else {
                        break;
                    }
                } else {
                    t.insert(r[j]);
                    break;
                }
            }
            select[it->first].insert({r, t});
        }
    }
    string bk = "                                                    ";
    cout << "\n\n" << bk << "Select��Ϊ:" << '\n' << '\n';
    for (auto it = select.begin(); it != select.end(); ++it) {
        for (auto i = it->second.begin(); i != it->second.end(); ++i) {
            cout << blank << "SELECT(" << it->first << "->" << i->first << ") = {";
            for (auto j = i->second.begin(); j != i->second.end();) {
                cout << *j++;
                if (j != i->second.end()) cout << ",";
            }
            cout << "}\n";
        }
    }
}

void get_M() {
    for (auto it = select.begin(); it != select.end(); ++it)
        for (auto i = it->second.begin(); i != it->second.end(); ++i)
            for (auto j = i->second.begin(); j != i->second.end(); ++j)
                M[it->first][*j] = i->first;
    string bk = "                                                    ", bkk = "       ";
    cout << "\n\n" << bk << "Ԥ�������Ϊ:" << '\n' << '\n';
    cout << "         " << "\t\t";
    for (auto it = vt.begin(); it != vt.end(); ++it)
        cout << *it << "\t\t";
    cout << "#" << '\n';
    for (auto it = vn.begin(); it != vn.end(); ++it) {
        cout << "         " << *it << "\t\t";
        for (auto i = vt.begin(); i != vt.end(); ++i)
            cout << M[*it][*i] << "\t\t";
        cout << M[*it]['#'] << '\n';
    }
    cout << '\n';
}

void print_st(vector<char> st) {
    for (int i = 0; i < (int) st.size(); i++) {
        cout << st[i];
    }
    cout << '\n';
}

void Puts(int num, vector<char> &sta, int top, const string &str, int pos, string &info) {
    cout << "               " << num << "\t\t\t";
    for (int i = 0; i <= top; i++) cout << sta[i];
    cout << "\t\t\t";
    string cur = str.substr(pos);
    cout  << setw(15) << cur;
//    for (int i = pos; i < (int) str.size(); i++) cout << std::left<<setw(10) << str[i];
    cout << "\t\t\t";
    cout << info << '\n';
}

void check(const string &str) {
    vector<char> st(1000);
    st[0] = '#'; st[1] = start;
    int top = 1;
    int len = (int) str.size();
    int num = 1;
    string bk = "                                                       ";
    cout << "\n\n" << bk << "��������:" << '\n' << '\n';
    cout << "             " << "����" << "\t\t\t" << "����ջ" << "\t\t\t\t" << "ʣ�����봮" << "        " << "�Ƶ����ò���ʽ��ƥ��" << '\n';
    for (int i = 0; i < len;) {
        string info;
        if (st[top] == str[i]) {
            if (str[i] != '#') {
                info += "��"; info += str[i]; info += "��ƥ��";
            } else {
                info = "����";
            }
            Puts(num++, st, top, str, i, info);
            i++; top--;
            continue;
        }
        string next = M[st[top]][str[i]];
        if (next == "") {
            cout << "����" << "\n";
            exit(0);
        } else if (next == "null") {
            info += st[top--]; info += " -> "; info += next;
            Puts(num++, st, top + 1, str, i, info);
        } else {
            info += st[top--]; info += " -> "; info += next;
            Puts(num++, st, top + 1, str, i, info);
            int l = (int) next.size();
            for (int j = l - 1; j >= 0; j--) {
                st[++top] = next[j];
            }
        }
    }
    cout << '\n';
}

int main() {
    init();
    get_nul();
    get_first();
    get_follow();
    get_select();
    get_M();
    cout << "                                               ������Ҫ�����ķ��Ŵ�: ";
    string str;
    cin >> str;
    check(str);
    return 0;
}
