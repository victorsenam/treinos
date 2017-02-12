#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e2+7;

const int mv[4][2] = {
    {1,0},
    {0,1},
    {-1,0},
    {0,-1}
};

vector<pair<int, int> > adj[N][N];
int n, qr, r;
pii q[N*N];

int uf[N*N], wf[N*N];

int conv (pii x) {
    return x.first*n+x.second;
}

int find (int u) {
    if (u == uf[u]) return u;
    return uf[u] = find(uf[u]);
}

void join (int u, int v) {
    if ((u = find(u)) == (v = find(v))) return;
    if (wf[u] < wf[v]) swap(u,v);
    wf[u] += wf[v];
    uf[v] = u;
}

int main () {
    freopen("countcross.in", "r", stdin);
    freopen("countcross.out", "w", stdout);

    scanf("%d %d %d", &n, &qr, &r);
    for (int i = 0; i < r; i++) {
        int a[2], b[2];
        scanf("%d %d %d %d", &a[0], &a[1], &b[0], &b[1]);
        a[0]--; a[1]--; b[0]--; b[1]--;

        adj[a[0]][a[1]].pb(pii(b[0],b[1]));
        adj[b[0]][b[1]].pb(pii(a[0],a[1]));
    }
    for (int i = 0; i < n*n; i++) {
        uf[i] = i;
        wf[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 4; k++) {
                pii nxt;
                nxt.first = i + mv[k][0];
                nxt.second = j + mv[k][1];

                if (nxt.first < 0 || nxt.first >= n || nxt.second < 0 || nxt.second >= n) continue;

                bool ok = 1;
                for (int c = 0; ok && c < adj[i][j].size(); c++)
                    if (adj[i][j][c] == nxt)
                        ok = 0;

                if (ok)
                    join(conv(pii(i,j)), conv(nxt));
            }
        }
    }

    int res = 0;
    for (int i = 0; i < qr; i++) {
        scanf("%d %d", &q[i].first, &q[i].second);
        q[i].first--; q[i].second--;
        for (int j = 0; j < i; j++) {
            if (find(conv(q[i])) != find(conv(q[j]))) {
                res++;
            }
        }
    }

    printf("%d\n", res);
}
