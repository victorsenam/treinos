#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
//#define DEBUG(...) {}

const int N = 12;
const int mv[4][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
};

int n, m;
char mat[N][N];
int val[N][N];
int qt;

struct point {
    int i, j;

    bool operator < (const point & ot) const {
        if (i == ot.i)
            return j < ot.j;
        return i < ot.i;
    }

    int & val () {
        return ::val[i][j];
    }

    char & mat () {
        return ::mat[i][j];
    }

    bool isblank () {
        point q;
        if (val() > 0) return 0;
        for (int k = 0; k < 4; k++) {
            q.i = i + mv[k][0];
            q.j = i + mv[k][1];
            if (q.isval() && q.val() > 0) return 1;
        }
        return 0;
    }

    bool isval () {
        return i >= 0 && i < n && j >= 0 && j < m;
    }

    bool check_blanks () {
        if (!isblank()) return 1;
        point p;
        p.i = i; p.j = j;
        point q;

        for (int k = 0; k < 4; k++) {
            bool ok = 0;
            for (int l = 0; !ok && l < 2; l++) {
                ok = 1;
                q = p;
                q.i += mv[(k+l)%4][0];
                q.j += mv[(k+l)%4][1];
                if (!q.isval() || !q.isblank()) ok = 1;
            }
            
            q = p;
            for (int l = 0; !ok && l < 2; l++) {
                q.i += mv[(k+l)%4][0];
                q.j += mv[(k+l)%4][1];
            }
            if (!q.isval() || !q.isblank()) ok = 1;

            if (!ok) return 0;
        }
        return 1;
    }

    bool put (vector<point> v) {
        point p;
        DEBUG("try at (%d,%d) -> %d\n", i, j, (int) v.size());
        qt++;
        for (int l = 0; l < v.size(); l++) {
            v[l].i += i;
            v[l].j += j;
            //DEBUG("++(%d,%d)\n", v[l].i, v[l].j);

            if (!v[l].isval() || v[l].isblank() || v[l].val() > 0) return 0;
            continue;
            for (int k = 0; k < 4; k++) {
                p = v[l];
                p.i += mv[k][0];
                p.j += mv[k][1];
                if (p.isval() && p.val() > 0) return 0;
            }
        }
        //DEBUG("putting\n");
        for (int l = 0; l < v.size(); l++)
            v[l].val() = qt;
        //DEBUG("check blanks\n");
        DEBUG("ok\n");

        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                DEBUG("%d ", ::val[x][y]);
            }
            DEBUG("\n");
        }

        return 1;
        for (int l = 0; l < v.size(); l++) {
            //DEBUG("(%d,%d)\n", v[l].i, v[l].j);
            for (int k = 0; k < 4; k++) {
                p = v[l];
                p.i += mv[k][0];
                p.j += mv[k][1];
                //DEBUG("->(%d,%d)\n", p.i, p.j);
                if (p.isval() && !p.check_blanks()) return 0;
            }
        }
        return 1;
    }

    void unput (vector<point> v) {
        //DEBUG("fail at (%d,%d)\n", i, j);
        for (int l = 0; l < v.size(); l++) {
            v[l].i += i;
            v[l].j += j;

            if (v[l].val() == qt)
                v[l].val() = 0;
        }
        qt--;
    }
};

set<vector<point> > s[N];

void gen_kminos (int i) {
    for (vector<point> v : s[i-1]) {
        for (point u : v) {
            for (int k = 0; k < 4; k++) {
                u.i += mv[k][0];
                u.j += mv[k][1];
                if (binary_search(v.begin(), v.end(), u)) continue;
                vector<point> nx = v;
                nx.push_back(u);
                for (int j = nx.size()-1; j > 0 && nx[j] < nx[j-1]; j--)
                    swap(nx[j], nx[j-1]);
                if (nx[0].i != nx[0].j || nx[0].i != 0) {
                    for (int j = nx.size()-1; j >= 0; j--) {
                        nx[j].i -= nx[0].i;
                        nx[j].j -= nx[0].j;
                    }
                }
                s[i].insert(nx);
            }
        }
    }
}

bool bt (point p) {
    point q;
    if (p.i == n) {
        for (q.i = 0; q.i < n; q.i++) {
            for (q.j = 0; q.j < m; q.j++) {
                if (q.val() == 0) return 0;
                if (!q.check_blanks()) return 0;
            }
        }
    }
    if (p.j == m) {
        p.j = 0;
        p.i++;
        return bt(p);
    }
    if (p.mat() == '.') {
        p.j++;
        return bt(p);
    }
    
    q = p;
    q.j++;
    int sz = p.mat()-'0';
    for (vector<point> v : s[sz]) {
        if (p.put(v) && bt(q)) return 1;
        p.unput(v);
    }
    return 0;
}

int main () {
    point p;
    p.i = p.j = 0;
    vector<point> v;
    v.push_back(p);
    s[1].insert(v);
    for (int i = 1; i < 10; i++) {
        gen_kminos(i);
        DEBUG("gen %d\n", i);
    }
    
    while (scanf("%d %d", &n, &m) != EOF && n) {
        qt = 0;
        for (int i = 0; i < n; i++) {
            scanf(" %s", mat[i]);
            for (int j = 0; j < m; j++) {
                val[i][j] = 0;
            }
        }

        bt(p);

        for (p.i = 0; p.i < n; p.i++) {
            for (p.j = 0; p.j < m; p.j++) {
                printf("%d ", p.val());
                continue;
                if (p.isblank())
                    printf("#");
                else
                    printf("%c", p.mat());
            }
            printf("\n");
        }
        printf("\n");
    }
}
