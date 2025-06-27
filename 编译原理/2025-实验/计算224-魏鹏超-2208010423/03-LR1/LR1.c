�ġ�	#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <fstream>
#include <iomanip>
using namespace std;

        struct Production {
        char left;
        vector<char> rigths;
        /* ����== */
        bool operator == (Production& rhs) const {
        if (left != rhs.left)
        return false;
        for (int i = 0; i < rigths.size(); i++) {
        if (i >= rhs.rigths.size())
        return false;
        if (rigths[i] != rhs.rigths[i])
        return false;
        }
        return true;
        }
        };


        struct LR1Item {
        Production p; // ����ʽ
        int location; // ���λ��
        char next; // ��ǰ������
        };

        struct LR1Items {
        vector<LR1Item> items;
        };


        struct CanonicalCollection {
        vector<LR1Items> items; //��Ŀ������
        vector< pair<int, char> > g[100]; // ����DFA��ͼ��firstΪת�Ƶ���״̬��ţ�second�Ǿ�ʲôת��
        } CC;


        struct Grammar {
        int num;  // ����ʽ����
        vector<char> T;   // �ս��
        vector<char> N;   // ���ս��
        vector<Production> prods;  //����ʽ
        }grammar;

        map<char, set<string>> p; //����ʽ
        map<char, set<char> > first, follow; //first����follow��
        map<char, int> done; //��first���Ǳ���Ƿ��Ѿ�������
        map<char, int> nul; //�Ƿ�����Ƶ�����
        set<char> vn, vt; //���ս�����ս��
        queue< pair<LR1Items, int> > Q; //DFA���У� ���ڴ洢��ת�Ƶ���Ч��Ŀ��
        pair<int, int> action[100][100]; //action��first��ʾ����������0->ACC 1->S 2->R second��ʾת��״̬���߲���ʽ���
        int goton[100][100]; //goto��
        string str; //��������
        vector< pair<int, char> > ST; // ����ջ
        const char N = '&';
        const string blank = "                                                     ";


        inline bool in_vt(char c) {
        if (vt.find(c) != vt.end()) return true;
        return false;
        }

        inline bool in_vn(char c) {
        if (vn.find(c) != vn.end()) return true;
        return false;
        }

        int isInT(char c) {
        for (int i = 0; i < grammar.T.size(); i++) if (grammar.T[i] == c) return i + 1;
        return 0;
        }
        
        int isInN(char c) {
        for (int i = 0; i < grammar.N.size(); i++) if (grammar.N[i] == c) return i + 1;
        return 0;
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
                 �˴�������ɾ��������������now�����Щ״̬δ���ķ��ս����������ֻȥ����now�е�Ԫ�أ��������÷��ս��Ҳ�ͱ��౻"ɾ��"��
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

//��first��ʱ����dfs
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

//��first��
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

//����alpha����FIRST���� ���浽FS������
        void getFirstByAlphaSet(vector<char> &alpha, set<char> &FS) {
        bool next = true; //��ǰ�����Ƿ��ս�����ҵ�ǰ���ſ����Ƴ��գ������ж���һ������
        int idx = 0;
        while (idx < alpha.size() && next) {
        next = false;
        if (isInT(alpha[idx]) || alpha[idx] == N) { //��ǰ�������ս����գ����뵽FIRST����
        FS.insert(alpha[idx]);
        } else {
        char B = alpha[idx];
        for (auto it = first[B].begin(); it != first[B].end(); it++) {
        if (*it == '&') { //��ǰ����FIRST�������գ����nextΪ��
        next = true;
        continue;
        } else { //�ѷǿ�Ԫ�ؼ��뵽FIRST����
        FS.insert(*it);
        }
        }
        }
        idx++;
        }
        if (next) FS.insert(N); //����������ʽ�Ҳ�ĩβnext��Ϊ�棬˵��alpha�����ƿգ����ռ��뵽FIRST����
        }

// �ж���Ŀt������Ŀ��I��
        bool isInLR1Items(LR1Items &I, LR1Item &t) {
        for (auto it = I.items.begin(); it != I.items.end(); it++)
        if (it->p == t.p && it->location == t.location && it->next == t.next) return true;
        return false;
        }

//��I�ıհ�
        void closure(LR1Items &I) {
        bool flag =  true; //�б仯�ж����ޱ仯
        while (flag) {
        flag = false;
        LR1Items J;
        J.items.assign(I.items.begin(), I.items.end());
        for (auto it = J.items.begin(); it != J.items.end(); it++) { //ö��ÿ����Ŀ
        LR1Item &L = *it;
        if (L.location < L.p.rigths.size()) { //�ǹ�Լ��Ŀ
        char B = L.p.rigths[L.location]; //Բ���ұߵķ���B
        if (isInN(B)) { //���BΪ���ս��, �ѷ���������LR1��Ŀ����հ���
        set<char> FS; vector<char> alpha;
        alpha.assign(L.p.rigths.begin() + L.location + 1, L.p.rigths.end());
        alpha.push_back(L.next);
        getFirstByAlphaSet(alpha, FS); //���B�����FIRST��
        for (int i = 0; i < grammar.prods.size(); i++) {
        Production &P = grammar.prods[i];
        if (P.left == B) {
        //��B�����FIRST����Ϊ��ǰ����������������Ŀ
        for (auto it = FS.begin(); it != FS.end(); it++) {
        LR1Item t;
        t.location = 0;
        t.next = *it;
        t.p.left = P.left;
        t.p.rigths.assign(P.rigths.begin(), P.rigths.end());
        if (!isInLR1Items(I, t)) {
        flag = true; //�б仯
        I.items.push_back(t); //������Ŀ������Ŀ����
        }
        }
        }
        }
        }
        }
        }
        }
        }

// �ж��Ƿ�����Ŀ���淶���У����ڷ������
        int isInCanonicalCollection(LR1Items &I) {
        for (int i = 0; i < CC.items.size(); i++) {
        LR1Items &J = CC.items[i];
        bool flag = true;
        if (J.items.size() != I.items.size()) {
        flag = false;
        continue;
        }
        //ÿ����Ŀ���ڸ���Ŀ���У�����Ϊ���������Ŀ�����
        for (auto it = I.items.begin(); it != I.items.end(); it++) {
        LR1Item &t = *it;
        if (!isInLR1Items(J, t)) {
        flag = false;
        break;
        }
        }
        if (flag) return i + 1;
        }
        return 0;
        }

//ת�ƺ�����IΪ��ǰ����Ŀ����JΪת�ƺ����Ŀ��, ��Xת��
        void go(LR1Items &I, char X, LR1Items &J) {
        for (auto it = I.items.begin(); it != I.items.end(); it++) {
        LR1Item &L = *it;
        if (L.location < L.p.rigths.size()) { //�ǹ�Լ��Ŀ
        char B = L.p.rigths[L.location];
        if (B == X) { //�����ƥ�䣬����λ�ü�1�����µ���Ŀ������Ŀ����
        LR1Item t;
        t.location = L.location + 1;
        t.next = L.next;
        t.p.left = L.p.left;
        t.p.rigths.assign(L.p.rigths.begin(), L.p.rigths.end());
        J.items.push_back(t);
        }
        }
        }
        if (J.items.size() > 0) closure(J); //��J������Ŀ��������հ�
        }

//��ӡĳ����Ŀ��
        void printLR1Items(LR1Items &I) {
        for (auto it = I.items.begin(); it != I.items.end(); it++) {
        LR1Item &L = *it;
        cout << blank << L.p.left << "->";
        for (int i = 0; i < L.p.rigths.size(); i++) {
        if (L.location == i)
        cout << "��";
        cout << L.p.rigths[i];
        }
        if (L.location == L.p.rigths.size())
        cout << "��";
        cout << "," << L.next << "   \n";
        }
        }

//����DFA����Ŀ���淶��
        void DFA() {
        LR1Item t; //��ʼ��Ŀ
        t.location = 0; t.next = '#'; t.p.left = grammar.prods[0].left;
        t.p.rigths.assign(grammar.prods[0].rigths.begin(), grammar.prods[0].rigths.end());
        LR1Items I; //��ʼ��Ŀ��
        I.items.push_back(t);
        closure(I);
        CC.items.push_back(I); //������Ŀ��������Ŀ���淶��
        Q.push(pair<LR1Items, int>(I, 0)); //���¼������Ŀ���������չ������
        while (!Q.empty()) {
        LR1Items &S = Q.front().first;
        int sidx = Q.front().second;
        for (int i = 0; i  < grammar.T.size(); i++) { //����ÿ���ս��
        LR1Items D;
        go(S, grammar.T[i], D);
        int idx;
        if (D.items.size() > 0) { //����Ϊ��
        idx = isInCanonicalCollection(D); //�����Ƿ��Ѿ�����Ч��Ŀ������
        if (idx > 0) {
        idx = idx - 1;
        } else {
        idx = (int) CC.items.size();
        CC.items.push_back(D); //������Ŀ��������Ŀ���淶��
        Q.push(pair<LR1Items, int>(D, idx)); //������Ŀ���������չ������
        }
        //��ԭ״̬��ת��״̬��һ���ߣ����ϵ�ֵΪת�Ʒ���
        CC.g[sidx].push_back(pair<char, int>(grammar.T[i], idx));
        }
        }
        for (int i = 0; i  < grammar.N.size(); i++) { //����ÿ�����ս��
        LR1Items D;
        go(S, grammar.N[i], D);
        int idx;
        if (D.items.size() > 0) {
        idx = isInCanonicalCollection(D); //�����Ƿ��Ѿ�����Ч��Ŀ������
        if (idx != 0) {
        idx = idx - 1;
        } else {
        idx = (int) CC.items.size();
        CC.items.push_back(D); //������Ŀ��������Ŀ���淶��
        Q.push(pair<LR1Items, int>(D, idx)); //������Ŀ���������չ������
        }
        //��ԭ״̬��ת��״̬��һ���ߣ����ϵ�ֵΪת�Ʒ���
        CC.g[sidx].push_back(pair<char, int>(grammar.N[i], idx));
        }
        }
        Q.pop(); //��ǰ״̬��չ��ϣ���������
        }

        const string bk = "\n\n                                                 ";
        cout << bk << "��Ŀ������Ϊ: " << (int) CC.items.size() << '\n' << '\n';
        for (int i = 0; i < (int)CC.items.size(); i++) {
        cout << blank << "I" << i << ":" << '\n';
        printLR1Items(CC.items[i]);
        for (int j = 0; j < CC.g[i].size(); j++) {
        pair<char, int> p= CC.g[i][j];
        cout << blank << "ʶ�� " << p.first << " ת�Ƶ� I" << p.second  << '\n';
        }
        cout << '\n';
        }
        }
//����LR1������
        void productLR1AnalysisTabel() {
        for (int i = 0; i < CC.items.size(); i++) {
        LR1Items &LIt= CC.items[i];
        /* ����action�� */
        for (auto it = LIt.items.begin(); it != LIt.items.end(); it++) {
        LR1Item &L = *it;
        /* �ǹ�Լ��Ŀ */
        if (L.location < L.p.rigths.size()) {
        char a = L.p.rigths[L.location];
        int j = isInT(a);
        /* a���ս�� */
        if (j > 0) {
        j = j - 1;
        /* �ҵ���Ӧa�ĳ��ߣ��õ���ת�Ƶ���״̬ */
        for (int k = 0; k < CC.g[i].size(); k++) {
        pair<char, int> p = CC.g[i][k];
        if (p.first == a) {
        action[i][j].first = 1; // 1->S
        action[i][j].second = p.second;  //ת��״̬
        break;
        }
        }
        }
        } else { // ��Լ��Ŀ
        /* ������Ŀ */
        if (L.p.left == grammar.prods[0].left) {
        if (L.next == '#')
        action[i][grammar.T.size() - 1].first = 3;
        } else {
        /* �ս�� */
        int  j = isInT(L.next) - 1;
        /* �ҵ�����ʽ��Ӧ����� */
        for (int k = 0; k < grammar.prods.size(); k++) {
        if (L.p == grammar.prods[k]) {
        action[i][j].first = 2;
        action[i][j].second = k;
        break;
        }
        }

        }
        }
        }
        /* ����goto�� */
        for (int k = 0; k < CC.g[i].size(); k++) {
        pair<char, int> p = CC.g[i][k];
        char A = p.first;
        int j = isInN(A);
        /* �ս�� */
        if (j > 0) {
        j = j - 1;
        goton[i][j] = p.second; //ת��״̬
        }
        }
        }
        const string bk = "                 ";
        //��ӡLR1������
        cout << '\n' << "LR1������Ϊ��" << '\n';
        cout << bk;
        for (int i = 0; i < grammar.T.size() / 2; i++)
        printf("\t");
        printf("action");
        for (int i = 0; i < grammar.N.size() / 2 + grammar.T.size() / 2 + 1; i++)
        printf("\t");
        printf("          goto\n");
        printf("\t");
        cout << bk;
        for (int i = 0; i  < grammar.T.size(); i++) {
        printf("%c\t", grammar.T[i]);
        }
        printf("|\t");
        for (int i = 1; i  < grammar.N.size(); i++) {
        printf("%c\t", grammar.N[i]);
        }
        printf("\n");
        for (int i = 0; i < CC.items.size(); i++) {
        cout << bk; printf("%d\t", i);
        for (int j = 0; j < grammar.T.size(); j++) {
        if (action[i][j].first == 1) {
        printf("%c%d\t", 'S', action[i][j].second);
        } else if (action[i][j].first == 2) {
        printf("%c%d\t", 'R', action[i][j].second);
        } else if (action[i][j].first == 3) {
        printf("ACC\t");
        } else {
        printf("\t");
        }
        }
        printf("|\t");
        for (int j = 1; j < grammar.N.size(); j++) {
        if (goton[i][j]) {
        printf("%d\t", goton[i][j]);
        } else {
        printf("\t");
        }

        }
        printf("\n");
        }
        }

        void initGrammar() {
        ifstream OutFile;
        OutFile.open("/desktop/����ԭ��/ʵ��/2108010316����/LR1/production.txt");
        OutFile >> grammar.num;
        string s;
        for (int i = 0; i < grammar.num; i++) {
        OutFile >> s;
        Production tmp;
        tmp.left = s[0];
        p[s[0]].insert(s.substr(3));
        vn.insert(s[0]);
        for (int j = 3; j < s.size(); j++) tmp.rigths.push_back(s[j]);
        grammar.prods.push_back(tmp);
        }
        char ch;
        OutFile >> ch;
        while (ch != '#') {
        grammar.N.push_back(ch);
        OutFile >> ch;
        }
        OutFile >> ch;
        while (ch != '#') {
        grammar.T.push_back(ch);
        OutFile >> ch;
        }
        grammar.T.push_back('#'); //��#�����ս��
        get_nul(); //��ɨһ�飬�ж�ÿ�����ս���Ƿ�����Ƶ�Ϊ��
        get_first(); //��FIRST��
        DFA(); //����DFA
        productLR1AnalysisTabel(); //����LR1Ԥ�������
        //���������������ʼ������ջ
        cout << "\n\n                                                �������������: ";
        cin >> str;
//    str = "cccdcd";
        str += '#';
        ST.push_back(pair<int, char>(0, ' '));
        }

// ��������
        void process() {
        int ip = 0;
        int num = 1;
        string bk = "                                                       ";
        cout << "\n\n" << bk << "��������:" << '\n' << '\n';
        cout << "\t\t" << "����" << "\t\t" << "״̬ջ" << "\t\t����ջ" << "\t\t" << "ʣ�����봮" << "\t\t" << "ACTION" << "\t\t" << "GOTO" << '\n';
        do {
        cout << "\t\t" << " " << num++;
        cout << "\t\t"; for (auto it : ST) cout << it.first;
        cout << "\t\t"; for (auto it : ST) cout << char(it.second);
        cout << "\t"; string cur = str.substr(ip); cout  << setw(15) << cur;
        cout << "\t\t\t";
        int s = ST.back().first;
        char a = str[ip];
        int j = isInT(a) - 1;
        if (action[s][j].first == 1) { //�ƽ�
        ST.push_back(pair<int, char>(action[s][j].second, a));
        ip = ip + 1;
        cout << "  S" << action[s][j].second << "\t\t";
        } else if (action[s][j].first == 2) { // ��Լ
        Production &P = grammar.prods[action[s][j].second];
        cout << "  r" << action[s][j].second << "\t\t  ";
        /* �������������ʽ */
//            printf("%c->", P.left);
        for (int i = 0; i < P.rigths.size(); i++) {
        ST.pop_back();
//                printf("%c", P.rigths[i]);
        }
        s = ST.back().first;
        char A = P.left;
        j = isInN(A) - 1;
        ST.push_back(pair<int, char>(goton[s][j], A));
        cout << goton[s][j];
        } else if (action[s][j].first == 3) {   //����
        printf("  ACC\n");
        return;
        } else {
        printf("error\n");
        return;
        }
        cout << '\n';
        } while(1);
        }
        int main() {
        initGrammar();
        process();
        return 0;
        }

