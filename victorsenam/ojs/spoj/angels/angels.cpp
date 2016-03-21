#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int H = 307;
const int N = 2000000;
const int M = N;

struct Dinic {
    int n;
    int hd[N], to[M], nx[M], he[N], es;
    ll fl[M], cp[M];
    int qu[M], qi, qf;
    int src, snk;
    int visi[N], dist[N], turn;

    void reset (int n) {
        turn = 0;
        es = 2;
        memset(hd, 0, sizeof hd);
        memset(visi, 0, sizeof visi);
        src = n; snk = n+1;
        n += 2;
    }

    int connect (int i, int j, ll cap) {
        nx[es] = hd[i]; hd[i] = es; to[es] = j; fl[es] = 0; cp[es] = cap; es++;
        nx[es] = hd[j]; hd[j] = es; to[es] = i; fl[es] = 0; cp[es] = 0; es++;
    }

    bool bfs () {
        ++turn;
        qi = qf = 0;
        qu[qf++] = snk;
        dist[snk] = 0;
        visi[snk] = turn;

        while (qi < qf) {
            int u = qu[qi++];
            he[u] = hd[u];

            for (int ed = hd[u]; ed; ed = nx[ed]) {
                int v = to[ed];
                if (fl[ed^1] == cp[ed^1] || visi[v] == turn)
                    continue;

                visi[v] = turn;
                dist[v] = dist[u] + 1;
                
                qu[qf++] = v;
            }
        }

        return (visi[src] == turn);
    }

    ll dfs (int u, ll at) {
        if (at <= 0) return 0;
        if (u == snk) return at;

        for (int & ed = he[u]; ed; ed = nx[ed]) {
            if (visi[to[ed]] != turn || dist[u] != dist[to[ed]] + 1)
                continue;
            if (ll val = dfs(to[ed], min(at, cp[ed]-fl[ed]))) {
                fl[ed] += val;
                fl[ed^1] -= val;
                return val;
            }
        }
        return 0;
    }

    int run () {
        ll res = 0;
        while (bfs())
            while (ll val = dfs(src, INT_MAX))
                res += val;
        return res;
    }
};

char mat[H][H];
int pos[H][H][2];
int a[2];
int ts;
int n, m;
Dinic flow;

int main () {
    scanf("%d", &ts);
    while (ts--) {
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf(" %c", &mat[i][j]);

        a[0] = a[1] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j && mat[i][j] == 'A' && mat[i][j-1] != mat[i][j])
                    a[0]++;
                pos[i][j][0] = a[0];
            }
            a[0]++;
        }
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                if (i && mat[i][j] == 'A' && mat[i-1][j] != mat[i][j])
                    a[1]++;
                pos[i][j][1] = a[1];
            }
            a[1]++;
        }

        flow.reset(a[0]+a[1]);

        for (int i = 0; i < a[0]; i++)
            flow.connect(flow.src, i, 1);
        for (int i = 0; i < a[1]; i++)
            flow.connect(a[0]+i, flow.snk, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 'H')
                    flow.connect(pos[i][j][0], pos[i][j][1] + a[0], 1);
            }
        }
        printf("%d\n", flow.run());
    }
}
