#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Pair;

const int maxn = 26 + 1;
vector<Pair> storeEdge, loadEdge, allocEdge;
vector<int> assignEdge[2 * maxn];
int pt[(maxn + maxn) * maxn];

// object: a, b, c, d, e, f, ...., 
// pointer: A, B, C, D, E, F, ...., 
// field: a, b, c, d, e, f, ...., 

int ObjectIndex(char ch) {
    return ch - 'a';
}

int PointerIndex(char ch) {
    assert('A' <= ch && ch <= 'Z');
    return ch - 'A' + 26;
}

int FieldIndex(char ch) {
    assert('a' <= ch && ch <= 'z');
    return ch - 'a' + 1;
}

int makeField(int v, int f) {
    return f * 52 + v;
}

int makeField(char v, char f) {
    assert(('A' <= v && v <= 'Z') || ('a' <= v && v <= 'z'));
    assert('a' <= f && f <= 'z');
    if ('a' <= v && v <= 'z') return makeField(ObjectIndex(v), FieldIndex(f));
    return makeField(PointerIndex(v), FieldIndex(f));
}

int makeField(int v, char f) {
    assert(0 <= v && v <= 51);
    assert('a' <= f && f <= 'z');
    return makeField(v, FieldIndex(f));
}

int getBase(int v) {
    int base = v % 52, field = v / 52;
    
    assert(0 <= base && base <= 52);
    assert(1 <= field && field <= 26);
    return base;
}

int getField(int v) {
    int base = v % 52, field = v / 52;
    assert(0 <= base && base <= 52);
    assert(1 <= field && field <= 26);
    return field;
}

int checkFieldNode(const char *s) {
    int n = strlen(s);
    assert(n == 1 || n == 3);
    if (n == 1) {
        return -1;
    }
    assert(s[1] == '.');
    return makeField(s[0], s[2]);
}

void propagate() {
    set<int> worklist;
    for (auto &e : allocEdge) {
        pt[e.first] |= (1 << e.second);
        worklist.insert(e.first);
    }

    while (!worklist.empty()) {
        while (!worklist.empty()) {
            int u = *worklist.begin();
            worklist.erase(worklist.begin());
            for (auto &v : assignEdge[u]) {
                if ((pt[v] & pt[u]) != pt[u]) {
                    pt[v] |= pt[u];
                    worklist.insert(v);
                }
            }
        }

        for (auto &e : storeEdge) {
            int p = e.second; // p -> q.f
            int q = getBase(e.first);
            int f = getField(e.first);
            for (int i = 0; i < 26; i++) 
                if ((pt[q] >> i) & 1) {
                    pt[makeField(i, f)] |= pt[p];
                }
        }

        for (auto &e : loadEdge) {
            // p.f -> q
            int p = getBase(e.second);
            int f = getField(e.second);
            int q = e.first;
            for (int i = 0; i < 26; i++) 
                if ((pt[p] >> i) & 1) {
                    int value = pt[makeField(i, f)];
                    if ((pt[q] & value) != value) {
                        pt[q] |= value;
                        worklist.insert(q);
                    }
                }
        }
    }
    for (auto &e : allocEdge) {
        assert(pt[e.second] | (e.first));
    }

    for (int i = 'A'; i <= 'Z'; i++) {
        int src = PointerIndex(i);
        for (int dst : assignEdge[src]) 
            assert((pt[dst] & pt[src]) == pt[src]);
    }

    for (auto &e : storeEdge) {
        int dst = e.first;
        int src = e.second;

        int base = getBase(dst);
        int f = getField(dst);
        for (int i = 0; i < 26; i++) {
            if ((pt[base] >> i) & 1) {
                assert((pt[makeField(i, f)] & pt[src]) == pt[src]);
            }
        }
    }

    for (auto &e : loadEdge) {
        int dst = e.first;
        int src = e.second;

        int base = getBase(src);
        int f = getField(src);
        for (int i = 0; i < 26; i++) {
            if ((pt[base] >> i) & 1) {
                assert((pt[makeField(i, f)] & pt[dst]) == pt[makeField(i, f)]);
            }
        }
    }
}

void output(int x) {
    for (int i = 0; i < 26; i++) {
        if ((x >> i) & 1) cout << (char)('a' + i);
    }
    cout << endl;
}

int main() {
    char receiver[10], sender[10];
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s = %s", receiver, sender);

        int R = checkFieldNode(receiver);
        int G = checkFieldNode(sender);
        if (R != -1 && G != -1) {
            assert(0);
        }
        if (R != -1 && G == -1) {
            // A.f = x
            storeEdge.push_back(Pair(R, PointerIndex(sender[0])));
        }
        if (R == -1 && G != -1) {
            // A = B.f
            loadEdge.push_back(Pair(PointerIndex(receiver[0]), G));
        }
        if (R == -1 && G == -1) {
            // A = B or A = o
            if (sender[0] >= 'a' && sender[0] <= 'z') 
                allocEdge.push_back(Pair(PointerIndex(receiver[0]), ObjectIndex(sender[0])));
            else {
                assignEdge[PointerIndex(sender[0])].push_back(PointerIndex(receiver[0]));
            }
        }
    }

    propagate();

    for (char i = 'A'; i <= 'Z'; i++) {
        cout << i << ": ";
        for (int j = 0; j < 26; j++) 
            if ((pt[PointerIndex(i)] >> j) & 1) cout << (char)(j + 'a');
        cout << endl;
    }
    return 0;
}


