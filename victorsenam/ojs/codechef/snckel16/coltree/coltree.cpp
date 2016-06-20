#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 57;
const ll MOD = 1000000007;

int t, n, k;
vector<int> adj[N];
int visi[N][N][N];
ll memo[N][N][N];
ll choose[N][N];
int pai[N];
int a, b;
int turn;

ll mod (ll a) {
    return a%MOD;
}

int dfs (int u, int fr) {
    pai[u] = fr;
    for (int v : adj[u]) {
        if (v == fr) continue;
        dfs(v, u);
    }
}

/*
ll lala (int u, ll k) {
    if (k < 0) return 0;

    ll & me = memo[u][k];
    if (visi[u][k] == turn)
        return me;
    visi[u][k] = turn;

    me = 0;
    
    if (u == 0) {
        me = mod(k*pd(adj[u][0]));
    } else if (adj[u].size() == 1) {
        me = (k == 0);
    } else {
        for (ll i = 0; i <= k; i++) {
            //me = mod(me + mod((i+1)*pd(adj[u][0], adj[pai[u]][
        }
    }
}
*/


ll pd (int u, int ch, ll k) {
    if (k < 0) return 0;
    if (ch == adj[u].size()) return (k == 0);

    ll & me = memo[u][ch+1][k];
    if (visi[u][ch+1][k] == turn)
        return me;
    visi[u][ch+1][k] = turn;

    me = 0;

    if (u && adj[u].size() == 1) {
        me = (k <= 1);
    } else if (ch == -1) {
        me = mod(k*pd(u, ch+1, k-1));
        if (u)
            me = mod(me + pd(u, ch+1, k));
    } else if (adj[u][ch] == pai[u]) {
        me = pd(u, ch+1, k);
    } else {
        for (int i = 0; i <= k; i++) {
            me = mod(
                me + mod(
                    choose[k][i] * mod(
                        pd(u, ch+1, k-i) * pd(adj[u][ch], -1, i)
                    )
                )
            );
        }
    }

    //DEBUG("%d %d %d : %lld\n", u, ch, k, me);

    return me;
    
}

int main () {
    scanf("%d", &t);

    choose[0][0] = 1;
    for (ll i = 1; i < N; i++) {
        choose[i][0] = 1;
        choose[0][i] = 0;
    }
    for (ll i = 1; i < N; i++)
        for (ll j = 1; j < N; j++)
            choose[i][j] = mod(choose[i-1][j-1] + choose[i-1][j]);

    while (t--) {
        scanf("%d %d", &n, &k);

        for (int i = 0; i < n; i++)
            adj[i].clear();
        turn++;

        for (int i = 1; i < n; i++) {
            scanf("%d %d", &a, &b);
            a--; b--;
            
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        dfs(0, 0);

        ll res = 0;
        for (int i = 1; i <= k; i++)
            res = mod(res + mod(choose[k][i]*pd(0, -1, i)));

        printf("%lld\n", res);
    }
};
