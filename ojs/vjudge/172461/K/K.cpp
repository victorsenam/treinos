#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 4007;
const ll MOD = 1e9+7;

ll memo[N][N][3];
ll n, d, t, k;

inline ll mod (ll x) {
    return ((x%MOD) + MOD)%MOD;
}

ll pd (int i, int t, int ty) {
    if (i > n || t < 0) return 0;
    if (i == n) return (t == 0);

    ll & me = memo[i][t][ty];
    if (me != -1) return me;
    
    if (ty == 0)
        me = mod((k-!!i)*mod(pd(i+1, t, 1) - pd(i+d, t, 1) + pd(i+d, t-1, 2)));
    else if (ty == 1)
        me = mod(pd(i+1, t, 1) + pd(i, t, 0));
    else
        me = mod(pd(i+1, t-1, 2) + pd(i, t, 0));

    return me;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    memset(memo, -1, sizeof memo);
    cin >> n >> d >> t >> k;
    cout << pd(0, t, 0) << endl;
}
