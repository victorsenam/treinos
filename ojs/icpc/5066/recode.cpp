#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 107;
const int L = 17;
const int S = 10007;

const int mv[6][3] = {
    {0, 0, 1},
    {0, 1, 0},
    {0, 0, -1},
    {0, -1, 0},
    {1, 0, 0},
    {-1, 0, 0}
};

struct state {
    int l, i, j;
};

ll _dist[L][N][N];
int _vis[L][N][N];
ll memo[N][S];
int visi[N][S];
state qu[N*N*L];
int qi, qf;
int l, h, w, n;
int tc;
char mat[L][N][N];
ll cst[N], val[N];
int turn;
int s;

ll & dist (state s) {
    if (_vis[s.l][s.i][s.j] != turn)
        _dist[s.l][s.i][s.j] = INT_MAX;
    _vis[s.l][s.i][s.j] = turn;
    return _dist[s.l][s.i][s.j];
}

char charat (state s) {
    return mat[s.l][s.i][s.j];
}

bool isval (state s) {
    if (s.i < 0 || s.i >= h) return 0;
    if (s.j < 0 || s.j >= w) return 0;
    if (s.l < 0 || s.l >= l) return 0;
    if (charat(s) == 'X') return 0;
    return 1;
}

ll pd (int i, ll s) {
    if (s < 0) return -100007;
    if (s == 0) return 0;
    if (i == n) return 0;

    ll & me = memo[i][s];
    if (visi[i][s] == turn)
        return me;
    visi[i][s] = turn;

    me = 0;
    me = max(me, pd(i+1, s-cst[i]) + val[i]);
    me = max(me, pd(i+1, s));

    return me;
}

int main () {
    scanf("%d", &tc);

    for (turn = 1; turn <= tc; turn++) {
        scanf("%d %d %d %d %d", &l, &h, &w, &n, &s);

        state att;
        for (int k = 0; k < l; k++)
            for (int i = 0; i < h; i++)
                for (int j = 0; j < w; j++) {
                    scanf(" %c", &mat[k][i][j]);
                    if (mat[k][i][j] == 'S') {
                        att.i = i;
                        att.j = j;
                        att.l = k;
                    }
                }

        qi = qf = 0;
        dist(att) = 0;
        qu[qf++] = att;

        state nx;
        while (qi < qf) {
            att = qu[qi++];

            for (int k = 0; k < 6; k++) {
                nx = att;
                nx.l += mv[k][0];
                nx.i += mv[k][1];
                nx.j += mv[k][2];
                if (k == 4 && charat(att) != 'U') continue;
                if (k == 5 && charat(att) != 'D') continue;

                if (!isval(nx) || dist(nx) <= dist(att)+1)
                    continue;
                dist(nx) = dist(att) + 1;
                qu[qf++] = nx;
            }
        }

        for (int i = 0; i < n; i++) {
            scanf("%d %d %d %lld", &att.l, &att.i, &att.j, &val[i]);
            att.l--; att.i--; att.j--;
            cst[i] = dist(att);
        }

        printf("%lld\n", pd(0, s/3));
    }
}
