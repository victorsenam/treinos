#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e2+7;
const int K = 43;

ll memo[N][K][2];

ll dp (int ed, int l, int r) {
    if (ed == 0) return ok;

    ll & me = memo[ed][d][ok];
    if (me != -1)
        return me;

    me = 0;
    int u = to[ed];

    if (d == 0 && !ok) {
        for (int x = 1; x <= k; x++)
            me = (me + dp(hd[ed],   
    } else {
        for (int x = d; x <= k-1-d; x++) {
            me = (me + (dp(hd[ed], x-1, ok)*dp(nx[ed], d, (ok||(x==d))))%MOD)%MOD;
        }
    }
    return me;
}

int main () {
}
