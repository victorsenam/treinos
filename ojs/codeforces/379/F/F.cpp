#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e6+7;

vector<int> adj[N];
int sz[N], dp[N];
int cnt;

inline bool iswhite (char c) {
    return c == ' ' || c == '\n' || c == EOF;
}

inline void getint (int & v) {
    char c;
    v = 0;
    bool ok = 0;
    while (true) {
        c = getchar();
        if (iswhite(c) && ok)
            break;
        if (iswhite(c)) continue;
        ok = 1;
        v = v*10 + (c - '0');
    }
}

int getsz (int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p || sz[v] < 0) continue;
        sz[u] += getsz(v, u);
    }
    return sz[u];
}

void cent (int u, int d) {
    assert(d < 20);
    int siz = getsz(u, u);   
    int w = u;
    do {
        u = w;
        for (int v : adj[u]) {
            if (sz[v] >= sz[u] || sz[v] < 0 || sz[v] + sz[v] < siz)
                continue;
            w = v;
            break;
        }
    } while (w != u);

    sz[u] = -1;
    dp[u] = d;

    for (int v : adj[u]) {
        if (sz[v] < 0)
            continue;
        cent(v, d+1);
    }
}

struct opn {
    int u, p, cent, subt, dst;
};

int n, qs;
int tim[N];
opn vt[N], mx[N][2];
int rs[N];

void dfs (opn cur, int d) {
    cnt++;
    vt[cur.u] = cur;
    for (int v : adj[cur.u]) {
        if (v == cur.p || dp[v] <= d) continue;
        opn nxt = cur;
        nxt.u = v;
        nxt.p = cur.u;
        if (cur.subt == cur.cent)
            nxt.subt = v;
        nxt.dst++;

        dfs(nxt, d);
    }
}

int main () {
    getint(qs);
    n = 4;
    tim[0] = 0;
    for (int i = 1; i < n; i++) {
        adj[0].pb(i);
        adj[i].pb(0);
        tim[i] = 0;
    }

    for (int i = 1; i <= qs; i++) {
        int v;
        getint(v);
        v--;

        for (int k = 0; k < 2; k++) {
            adj[n].pb(v);
            adj[v].pb(n);
            tim[n] = i;
            n++;
        }
    }

    for (int u = 0; u < n; u++) {
        mx[u][0] = mx[u][1] = opn({n,n,n,n,INT_MIN});
    }

    cent(0,0);
    
    for (int d = 0; ; d++) {
        cnt = 0;
        bool fnd = 0;
        for (int u = 0; u < n; u++) {
            if (dp[u] == d) {
                fnd = 1;
                dfs(opn({u,u,u,u,0}), d);
            }
        }

        if (!fnd)
            break;

        for (int u = 0; u < n; u++) {
            opn & cur = vt[u];
            if (dp[cur.cent] != d) continue;

            int vl = mx[cur.cent][0].dst;
            if (mx[cur.cent][1].subt != vt[u].subt)
                vl = mx[cur.cent][1].dst;
            rs[tim[cur.u]] = max(rs[tim[cur.u]], vl + cur.dst);
            
            if (mx[cur.cent][1].dst < cur.dst) {
                if (mx[cur.cent][1].subt != cur.subt)
                    mx[cur.cent][0] = mx[cur.cent][1];
                mx[cur.cent][1] = cur;
            } else if (mx[cur.cent][0].dst < cur.dst && mx[cur.cent][1].subt != cur.subt) {
                mx[cur.cent][0] = cur;
            }
        }

        assert(cnt <= n);
    }

    int mx = 2;
    for (int i = 1; i <= qs; i++) {
        mx = max(mx, rs[i]);
        cout << mx << " ";
    }
    cout << endl;
}

