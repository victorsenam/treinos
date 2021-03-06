#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 10;
const int mv[4][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};


int finstage;
char mat[N][N];
int val[N][N];
ll visi[N][N];
int qt;
int n, m;
ll turn;

struct point {
    int i, j;

    point () : i(0), j(0) {}
    point (int x, int y) : i(x), j(y) {}

    int & val ()
    { return ::val[i][j]; }
    char & mat ()
    { return ::mat[i][j]; }
    bool isval ()
    { return i >= 0 && i < n && j >= 0 && j < m; }

    bool operator < (const point & ot) const {
        if (ot.i != i) return i < ot.i;
        return j < ot.j;
    }

    bool isblank () {
        if (!isval() || val()) return 0;
        if (finstage) return 1;
        for (int k = 0; k < 4; k++) {
            point p(i+mv[k][0],j+mv[k][1]);
            if (p.isval() && p.val())
                return 1;
        }
        return 0;
    }

    bool blankok () {
        for (int l = 0; l < 2; l++)
            for (int c = 0; c < 2; c++) {
                point p(i+l,j+c);
                if (!p.isval() || !p.isblank())
                    return 1;
            }
        return 0;
    }

    bool put (vector<point> v, int sh) {
        qt++;
        for (point q : v) {
            point p(i+q.i-v[sh].i, j+q.j-v[sh].j);
            if (!p.isval() || p.val() || p.isblank()) 
                return 0;
        }
        for (point q : v) {
            point p(i+q.i-v[sh].i, j+q.j-v[sh].j);
            p.val() = qt;
        }
        return 1;
    }

    void unput (vector<point> v, int sh) {
        for (point q : v) {
            point p(i+q.i-v[sh].i, j+q.j-v[sh].j);
            if (p.isval() && p.val() == qt)
                p.val() = 0;
        }
        qt--;
    }
};

int dfs (point p) {
    if (!p.isval() || p.val() || visi[p.i][p.j] == turn) return 0;
    visi[p.i][p.j] = turn;

    int res = p.isblank();
    for (int k = 0; k < 4; k++) {
        point q(p.i+mv[k][0], p.j+mv[k][1]);
        res += dfs(q);
    }
    return res;
}

bool iscon () {
    turn++;
    point p(0,0);
    int cnt = 0;
    int tot = 0;
    for (p.i = 0; p.i < n; p.i++) {
        for (p.j = 0; p.j < m; p.j++) {
            cnt = max(dfs(p), cnt);
            tot += p.isblank();
            if (!p.blankok()) return 0;
        }
    }
    return (cnt == tot);
}

set<vector<point> > s[N];

void gen (int sz) {
    point p;
    vector<point> v;
    if (sz == 1) {
        p.i = p.j = 0;
        v.push_back(p);
        s[sz].insert(v);
    } else {
        for (vector<point> at : s[sz-1]) {
            for (int i = 0; i < at.size(); i++) {
                for (int k = 0; k < 4; k++) {
                    p = at[i];
                    p.i += mv[k][0];
                    p.j += mv[k][1];
                    if (binary_search(at.begin(), at.end(), p)) continue;
                    v = at;
                    v.push_back(p);

                    for (int j = v.size()-1; j > 0 && v[j] < v[j-1]; j--)
                        swap(v[j], v[j-1]);

                    for (int j = v.size()-1; j >= 0; j--) {
                        v[j].i -= v[0].i;
                        v[j].j -= v[0].j;
                    }
                    s[sz].insert(v);
                }
            }
        }
    }
}

bool bt (point p) {
    while (!p.isval() || p.mat() == '.') {
        if (p.j == m) {
            p.i++;
            p.j = 0;
        } else if (p.i == n) {
            finstage = 1;
            for (p.i = 2; p.i < n; p.i++)
                for (p.j = 0; p.j < m; p.j++)
                    if (!p.blankok()) {
                        return 0;
                    }
            if (!iscon()) {
                return 0;
            }
            return 1;
        } else {
            p.j++;
        }
    }
    
    int sz = p.mat()-'0';
    point nx = p;
    nx.j++;
    int cnt = 0;
    //DEBUG("(%d,%d) -> %d\n", p.i, p.j, sz);
    for (vector<point> v : s[sz]) {
        for (int j = 0; j < sz; j++) {
            if (p.put(v, j) && iscon() && bt(nx))
                return 1;
            finstage = 0;
            p.unput(v, j);
        }
    }
    return 0;
}

int main () {
    for (int i = 1; i < N; i++)
        gen(i);

    bool fs = 0;

    while (scanf("%d %d", &n, &m) != EOF && n) {
        if (fs)
            printf("\n");
        fs = 1;
        qt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf(" %c", &mat[i][j]);
                val[i][j] = 0;
            }
        }

        finstage = 0;
        assert(bt(point(0,0)));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (val[i][j])
                    printf("%c", mat[i][j]);
                else
                    printf("#");
            }
            printf("\n");
        }
    }
}
