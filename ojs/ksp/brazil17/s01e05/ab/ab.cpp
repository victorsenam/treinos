#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;
const ll MOD = 1e9+9;

inline ll mod (ll x) {
    return x%MOD;
}

char str[N];
int nx[N][2];
ll memo[N][N+N];

int val (char c) {
    if (c == 'a')
        return 1;
    return -1;
}

ll pd (int i, int d) {
    if (!str[i])
        return 0;
    ll & me = memo[i][d+N];
    if (me != -1)
        return me;

    me = (d == 0);
    for (int k = 0; k < 2; k++) {
        int nn = nx[i+1][k];
        me = mod(me + pd(nn, d+val(str[nn])));
    }
    return me;
}

int main () {
    memset(memo, -1, sizeof memo);
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> str;
    int n = strlen(str);

    nx[n][0] = nx[n][1] = n;
    for (int i = n-1; i >= 0; i--) {
        nx[i][0] = nx[i+1][0];
        nx[i][1] = nx[i+1][1];
        nx[i][str[i]-'a'] = i;
    }

    ll res = mod(pd(0,val(str[0])) + 1);
    for (int i = 1; i < n; i++)
        if (str[i] != str[0]) {
            res = mod(res + pd(i,val(str[i])));
            break;
        }

    cout << res << endl;
}

