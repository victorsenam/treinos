#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 1e5+7;

int n, m, q;
vector<int> adj[N];
ll dw[N], bs[N]; // down and best distances
int cm[N];
ll dd[N]; // diam
map<ll, ll> memo[N];

vector<ll> vl[N], ac[N];

void calc_bs (int u, int p, ll vl) {
    debug("call %d form %d with %lld\n", u+1, p+1, vl);
    ll mx[2] = {-1, -1};

    for (int v : adj[u]) {
        if (p == v) continue;
        if (mx[0] < dw[v] + 1) {
            swap(mx[0], mx[1]);
            mx[0] = dw[v] + 1;
        } else if (mx[1] < dw[v] + 1) {
            mx[1] = dw[v] + 1;
        }
    }

    bs[u] = max(vl, mx[0]);
    debug("%d : %lld %lld\n", u+1, mx[0], mx[1]);

    for (int v : adj[u]) {
        if (v == p) continue;
        if (dw[v] + 1 == mx[0])
            calc_bs(v, u, max(mx[1], vl)+1);
        else
            calc_bs(v, u, max(mx[0], vl)+1);
    }
}

ll calc_dw (int u, int p) {
    if (cm[u] != -1) return 0;

    if (u == p)
        cm[u] = u;
    else
        cm[u] = cm[p];

    dw[u] = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        dw[u] = max(dw[u], calc_dw(v, u) + 1);
    }

    if (u == p)
        calc_bs(u, p, 0);

    return dw[u];
}

pii get_furth (int u, int p, int vl) {
    pii cur(vl, u);
    for (int v : adj[u]) {
        if (v == p) continue;
        cur = max(cur, get_furth(v, u, vl+1));
    }
    return cur;
}

int main () {
    memset(cm, -1, sizeof cm);

    scanf("%d %d %d", &n, &m, &q);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < n; i++) {
        calc_dw(i, i);

        vl[cm[i]].push_back(bs[i]);
    }

    for (int i = 0; i < n; i++) {
        if (cm[i] != i) continue;
        sort(vl[i].begin(), vl[i].end());
        
        ac[i].push_back(0);
        for (int j = 0; j < vl[i].size(); j++)
            ac[i].push_back(ac[i][j] + vl[i][j]);

        int f = get_furth(i,i,0).second;
        dd[i] = get_furth(f,f,0).first;
    }

    while (q--) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        u = cm[u]; v = cm[v];

        if (vl[u].size() > vl[v].size())
            swap(u, v);

        if (u == v) {
            printf("-1\n");
            continue;
        } else if (memo[u][v] == 0) {
            ll di = max(dd[u], dd[v]);

            memo[u][v] += ll(vl[u].size()) * ll(vl[v].size());
            debug("%lld ", memo[u][v]);
            memo[u][v] += ac[u].back() * ll(vl[v].size());
            debug("%lld ", memo[u][v]);
            memo[u][v] += ac[v].back() * ll(vl[u].size());
            debug("%lld ", memo[u][v]);

            for (int i = 0; i < vl[u].size(); i++) {
                int j = upper_bound(vl[v].begin(), vl[v].end(), di - 1 - vl[u][i]) - vl[v].begin();
                memo[u][v] += ll(j) * (di - 1 - vl[u][i]) - ac[v][j];
            debug("%lld ", memo[u][v]);
            }
        }
        printf("%.20f\n", double(memo[u][v])/double(ll(vl[u].size())*ll(vl[v].size())));
    }
}
