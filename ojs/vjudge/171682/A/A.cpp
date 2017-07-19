#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

typedef ll num;
const num eps = 0;
const int N = 1123;
const int M = 112345;
const int inf = INT_MAX;

struct dinic {
    int hd[N], nx[M], to[M], ht[M], es;
    num fl[M], cp[M];
    int n, src, snk;
    int ds[N], sn[N], tr;
    int qi, qf, qu[N];

    void init ()
    { es = 2; memset(hd, 0, sizeof hd); }

    void connect( int i, int j, num cap) {
        to[es] = j; nx[es] = hd[i]; cp[es] = cap; fl[es] = 0; hd[i] = es++;
        to[es] = i; nx[es] = hd[j]; cp[es] = fl[es] = 0; hd[j] = es++;
    }

    bool bfs () {
        tr += 2;
        qi = qf = 0;

        qu[qf++] = snk;
        ds[snk] = 0;

        while (qi < qf) {
            int u = qu[qi++];

            if (sn[u] > tr)
                continue;
            sn[u] = tr+1;

            for (int ed = hd[u]; ed; ed = nx[ed]) {
                if (cp[ed^1] - fl[ed^1] <= eps)
                    continue;
                int v = to[ed];

                if (sn[v] >= tr && ds[v] <= ds[u] + 1)
                    continue;
                sn[v] = tr;
                ds[v] = ds[u] + 1;
                qu[qf++] = v;
            }
        }
        return (sn[src] > tr);
    }

    num dfs (int u, num flw) {
        if (u == snk || flw <= eps)
            return flw;

        for (int & ed = ht[u]; ed; ed = nx[ed]) {
            int v = to[ed];
            if (cp[ed] - fl[ed] <= eps || sn[v] < tr || ds[v] + 1 != ds[u])
                continue;
            num ret = dfs(v, min(flw, cp[ed] - fl[ed]));
            if (ret > eps) {
                fl[ed] += ret;
                fl[ed^1] -= ret;
                return ret;
            }
        }

        return 0;
    }

    num maxflow () {
        num res = 0;
        while (bfs()) {
            for (int i = 0; i < n; i++)
                ht[i] = hd[i];
            num val = 0;
            do {
                res += val;
                val = dfs(src, inf);
            } while (val > eps);
        }
        return res;
    }
} f;

int n, m, c;
int A[212][212];

ll solve(ll T) {
    f.init();
    f.n = N;
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++) {
            if(A[i][j] <= T)
                f.connect(2 * m + i, 2 * j, 1);
            if(A[i][j] <= T - c)
                f.connect(2 * m + i, 2 * j + 1, 1);
        }
    for(i = 0; i < n; i++)
        f.connect(N - 1, 2 * m + i, 1);
    for(i = 0; i < 2 * m; i++)
        f.connect(i, N - 2, 1);
    f.src = N - 1;
    f.snk = N - 2;
    return f.maxflow();
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int i, j, t, k;
    cin >> t;
    while(t--) {
        cin >> n >> m >> k >> c;
        for(i = 0; i < n; i++)
            for(j = 0; j < m; j++)
                cin >> A[i][j];
        ll l = 0, r = 3e9;
        while(l < r) {
            ll m = (l + r) / 2;
            if(solve(m) >= k) r = m;
            else l = m + 1;
        }
        cout << l << '\n';
    }
}
