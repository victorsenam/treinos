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

const int N = 83;
const ll INF = 1e8;

int n, k, m;
ll adj[N][N];
int u, v;
ll w;

ll memo[N][N][N];

ll pd (int i, int j, int k) {
    if (k == 0)
        return 0;
    if (i == j)
        return INF;
    ll & me = memo[i][j][k];
    if (me != -1)
        return me;


    me = INF;

    if (i < j) {
        for (int x = i + 1; x <= j; x++) {
            me = min(me, adj[i][x] + pd(x, j, k-1));
            me = min(me, adj[i][x] + pd(x, i+1, k-1));
        }
    } else {
        for (int x = j; x < i; x++) {
            me = min(me, adj[i][x] + pd(x, j, k-1));
            me = min(me, adj[i][x] + pd(x, i-1, k-1));
        }
    }

    return me;
}

int main () {
    scanf("%d %d %d", &n, &k, &m);

    memset(memo, -1, sizeof memo);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            adj[i][j] = INF;
        }

    for (int i = 0; i < m; i++) {
        scanf("%d %d %lld", &u, &v, &w);
        u--; v--;

        adj[u][v] = min(adj[u][v], w);
    }

    ll rs = INF;
    for (int i = 0; i < n; i++)  {
        rs = min(rs, pd(i, 0, k-1));
        rs = min(rs, pd(i, n-1, k-1));
    }
    if (rs == INF)
        rs = -1;
    printf("%lld\n", rs);
}
