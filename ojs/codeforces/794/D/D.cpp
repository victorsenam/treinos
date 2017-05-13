#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 3e6;
const int INIT = 5e8;

int cr[N];
vector<int> adj[N];

int n, m;

void fail () {
    printf("NO\n");
    exit(0);
}

bool compare (int u, int v) {
    if (adj[u].size() != adj[v].size()) return 1;

    for (int i = 0; i < adj[u].size(); i++)
        if (adj[u][i] != adj[v][i])
            return 1;

    return 0;
}

void dfs (int u, int sh) {
    vector<int> jnt;

    debug("Expanding %d\n", u+1);

    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (u == v) continue;
        if (cr[v] != -1 && abs(cr[v] - cr[u]) > 1) fail();
        if (cr[v] != -1) continue;

        if (compare(v, u)) {
            debug("%d is diff\n", v+1);
            jnt.push_back(v);
        } else {
            cr[v] = cr[u];
            debug("%d -> %d\n", v+1, cr[v]);
        }
    }

    for (int i = 1; i < jnt.size(); i++)
        if (compare(jnt[0], jnt[i])) fail();

    for (int i = 0; i < jnt.size(); i++) {
        cr[jnt[i]] = cr[u] + sh;
        debug("%d -> %d\n", jnt[i]+1, cr[jnt[i]]);
    }

    if (jnt.size())
        dfs(jnt[0], sh);
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 0; i < n; i++) {
        adj[i].push_back(i);
        cr[i] = -1;
        sort(adj[i].begin(), adj[i].end());
    }

    vector<int> cmp[2];
    vector<int> dv[2];

    for (int i = 0; i < adj[0].size(); i++) {
        if (adj[0][i] == 0) continue;
        dv[compare(0, adj[0][i])].push_back(adj[0][i]);
    }

    if (dv[1].size())
        cmp[0].push_back(dv[1][0]);
    for (int i = 1; i < dv[1].size(); i++)
        cmp[compare(dv[1][0], dv[1][i])].push_back(dv[1][i]);
    for (int i = 1; i < cmp[1].size(); i++) {
        if (compare(cmp[1][0], cmp[1][i]))
            fail();
    }

    for (int i = 0; i < cmp[0].size(); i++) {
        debug("%d -> %d\n", cmp[0][i]+1, INIT-1);
        cr[cmp[0][i]] = INIT-1;
    }
    for (int i = 0; i < cmp[1].size(); i++) {
        debug("%d -> %d\n", cmp[1][i]+1, INIT+1);
        cr[cmp[1][i]] = INIT+1;
    }
    for (int i = 0; i < dv[0].size(); i++) {
        debug("%d -> %d\n", dv[0][i]+1, INIT);
        cr[dv[0][i]] = INIT;
    }
    debug("1 -> %d\n", INIT);
    cr[0] = INIT;
    
    if (cmp[0].size())
        dfs(cmp[0][0], -1);
    if (cmp[1].size())
        dfs(cmp[1][0], 1);

    printf("YES\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", cr[i]);
    }
}

