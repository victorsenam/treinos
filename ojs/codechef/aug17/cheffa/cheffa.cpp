#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+6;
const int MOD = 1e9+7;

int memo[N][N][51];
int visi[N][N][51], turn;
int ts, n;
int v[N];

inline int mod (int x) {
    return x%MOD;
}

int pd (int a, int b, int i) {
    if (i > n) i = n;
    if (i == n && b == 0 && a == 0)
        return 1;
    int & me = memo[a][b][i];
    if (visi[a][b][i] == turn) return me;
    visi[a][b][i] = turn;

    me = 0;
    for (int x = 0; x <= a && x <= b; x++) {
        int r = 0;
        if (i < n)
            r = v[i];
        me = mod(me + pd(b - x, x + r, i+1));
    }

    return me;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> ts;
    while (ts--) {
        turn++;
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> v[i];
        cout << pd(0,0,0) << endl;
    }
}
