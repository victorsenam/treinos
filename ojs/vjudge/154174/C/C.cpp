#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e4+7;

int n, m, k, ts;
int hd[N], to[2*N], nx[2*N], es;
int dg[N], in[N];
int rs[N];
int pr[N];
int got[N];

vector<int> adj[N];
set<pair<int, int> > s;
int dpt[N], rmv[N];
int res = 0;

void dfs (int u, int d) {
    if (rmv[u]) return;
    if (s.find(pii(dpt[u],u)) != s.end())
        s.erase(pii(dpt[u],u));
    dpt[u] = d;
    s.insert(pii(dpt[u],u));

    for (int v : adj[u]) {
        dfs(v, d+1);
    }
}

void root () {
    queue<int> qu;
    for (int i = 0; i < n; i++)
        if (dg[i] == 1)
            qu.push(i);

    while (!qu.empty()) {
        int u = qu.front();
        qu.pop();
        res++;

        int ed = hd[u];
        while (ed && pr[to[ed]] != -1) 
            ed = nx[ed];

        bool ok = 0;
        if (!ed) {
            pr[u] = u;
        } else {
            int v = to[ed];
            pr[u] = v;
            adj[v].push_back(u);

            dg[v]--;
            if (dg[v] == 1)
                qu.push(v);
        }
    }

    for (int u = 0; u < n; u++) {
        if (pr[u] == u || pr[pr[u]] == -1) {
            pr[u] = u;
            dfs(u, 1);
        }
    }
}

void go (int u) {
    if (rmv[u]) return;
    rmv[u] = 1;
    s.erase(pii(dpt[u], u));
    
    go(pr[u]);

    for (int v : adj[u]) {
        dfs(v, 1);
    }
}

int main () {
    scanf("%d", &ts);

    while (ts--) {
        scanf("%d %d %d", &n, &m, &k);

        for (int i = 0; i < n; i++) {
            hd[i] = 0;
            pr[i] = -1;
            dg[i] = 0;
            rmv[i] = 0;
            adj[i].clear();
        }
        s.clear();

        es = 2;
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--;

            dg[a]++; dg[b]++;
            nx[es] = hd[a]; to[es] = b; hd[a] = es++;
            nx[es] = hd[b]; to[es] = a; hd[b] = es++;
        }

        res = 0;
        root();
        while (k-- && s.size()) {
            pii cur = *s.rbegin();
            //printf("%d -> %d\n", cur.second+1, cur.first);
            res -= cur.first;

            go(cur.second);
        }
        printf("%d\n", res);
    }
}
