#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e3+7;

ll memo[N][N];
ll v[2][N];
int n, m;
ll p;

ll cost (int i, int j) {
    return abs(v[0][i] - v[1][j]) + abs(v[1][j] - p);
}

ll pd (int i, int j) {
    if (i == n) return 0;
    if (j == m) return 1e15;
    ll & me = memo[i][j];
    if (me != -1)
        return me;

    me = pd(i, j+1);
    me = min(me, max( pd(i+1, j+1), cost(i,j) ));
    return me;
}

int main () {
    memset(memo, -1, sizeof memo);
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> p;
    for (int i = 0; i < n; i++) {
        cin >> v[0][i];
    }
    for (int i = 0; i < m; i++) {
        cin >> v[1][i];
    }
    sort(v[0], v[0]+n);
    sort(v[1], v[1]+m);

    ll rs = pd(0,0);
    cout << rs << endl;
}
