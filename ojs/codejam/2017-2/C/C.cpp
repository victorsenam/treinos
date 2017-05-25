#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int mv[4][2] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};

const int N = 53;
const int M = N*N*2;

char mat[N][N];
int visi[N][N];
int ts, tt, r, c;
vector<pii> nds;
vector<int> hits[N][N];
int cs, cnt, ss;
int val[M];

int cmp[M], open[M], clse[M], pre[M], low[M], st[M];
vector<int> adj[M], inc[M];

int go (int u) {
    if (clse[u] == tt)
        return INT_MAX;
    if (open[u] == tt)
        return pre[u];
    open[u] = tt;

    pre[u] = low[u] = cnt++;
    st[ss++] = u;

    for (int v : adj[u])
        low[u] = min(low[u], go(v));
    
    clse[u] = tt;

    if (pre[u] == low[u]) {
        while (st[ss] != u) {
            cmp[st[--ss]] = cs;
            inc[cs].push_back(u);
        }
        cs++;
    }
    return low[u];
}

void connect (int a, int b) {
    adj[a].push_back(b);
}

int turn;
void dfs (pii x, int d, int nd) {
    if (x.first < 0 || x.first >= r || x.second < 0 || x.second >= c || visi[x.first][x.second] == turn)
        return;
    visi[x.first][x.second] = turn;

    hits[x.first][x.second].push_back(nd);

    if (mat[x.first][x.second] == '#' || mat[x.first][x.second] == '|' || mat[x.first][x.second] == '-')
        return;

    if (mat[x.first][x.second] == '\\') {
        d ^= 3;
    } else if (mat[x.first][x.second] == '/') {
        d ^= 1;
    }

    x.first += mv[d][0];
    x.second += mv[d][1];

    dfs(x, d, nd);
}

int main () {
    scanf("%d", &ts);

    for (tt = 1; tt <= ts; tt++) {
        scanf("%d %d", &r, &c);

        nds.clear();

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                scanf(" %c", &mat[i][j]);
                if (mat[i][j] == '|' || mat[i][j] == '-') {
                    nds.push_back(pii(i,j));
                }
                hits[i][j].clear();
            }
        }

        for (int i = 0; i < nds.size(); i++) {
            turn++;
            dfs(nds[i], 0, i);
            turn++;
            dfs(nds[i], 2, i);
            turn++;
            dfs(nds[i], 1, i + nds.size());
            turn++;
            dfs(nds[i], 3, i + nds.size());

            adj[i].clear();
            adj[i+nds.size()].clear();
        }

        int q = nds.size();

        bool fail = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (mat[i][j] == '.') {
                    assert(hits[i][j].size() <= 2);
                    
                    if (hits[i][j].size() == 0) {
                        fail = true;
                    } else if (hits[i][j].size() == 1) {
                        int k = hits[i][j][0] = 1;
                        connect((i+nds.size())%(2*q), i);
                    } else {
                        int a = hits[i][j][0];
                        int b = hits[i][j][1];

                        connect((a+nds.size())%(2*q), b);
                        connect((b+nds.size())%(2*q), a);
                    }
                } else if (mat[i][j] == '|' || mat[i][j] == '-') {
                    for (int k = 0; k < hits[i][j].size(); k++) {
                        int a = hits[i][j][k];
                        connect(a, (a+nds.size())%(2*q));
                    }
                }
            }
        }

        cs = 0, cnt = 0, ss = 0;
        for (int i = 0; i < 2*nds.size(); i++)
            go(i);

        for (int i = 0; i < nds.size(); i++) {
            if (cmp[i] == cmp[i+nds.size()])
                fail = 1;
        }

        for (int i = cs-1; i >= 0; i++) {
            int vl = -1;
            
            for (int j = 0; j < inc[i].size(); j++) {
                int u = inc[i][j];
                if (val[u] != -1) {
                    if (vl == -1)
                        vl = val[u];
                    else if (vl != val[u])
                        fail = 1;
                }
            }
            if (vl == -1)
                vl = 1;
            for (int j = 0; j < inc[i].size(); j++) {
                int u = inc[i][j];
                val[u] = vl;
                val[(u+q)%(2*q)] = !vl;
            }
        }

        printf("Case #%d: ", tt);
        if (fail)
            printf("IMPOSSIBLE\n");
        else {
            printf("POSSIBLE\n");
            int cr = 0;
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (mat[i][j] != '|' && mat[i][j] != '-')
                        putchar(mat[i][j]);
                    else {
                        if (val[cr])
                            putchar('-');
                        else
                            putchar('|');
                        cr++;
                    }
                }
                putchar('\n');
            }
        }
    }
}
