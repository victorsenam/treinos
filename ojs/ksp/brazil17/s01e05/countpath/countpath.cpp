#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 20;

int adj[N][N];
int n, m;
ll memo[(1<<N)][N];

ll pd (int mask, int u) {
    ll & me = memo[mask][u];
    if (me)
        return me;
    me = 1;
    for (int i = 0; i < n; i++)
        if (adj[u][i] && !(mask&(1<<i)))
            me += pd(mask|(1<<u),i);
    return me;
}

int main () {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a,b;
        cin >> a >> b;
        adj[a][b] = adj[b][a] = 1;
    }

    ll res = 0;
    for (int i = 0; i < n; i++)
        res += pd((1<<i),i) - 1;
    cout << res << endl;
}

