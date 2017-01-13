#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 75;
const int K = 23;
const ll MOD = 1e9+7;

int memo[2][(1<<K)];
char b[N+3];
int n;

ll pd (int msk, int i, bool calc = 0) {
    if (!calc) return memo[i&1][msk];
    ll me = 0;

    for (int j = 1; j <= K && !me; j++)
        me += (msk == ((1<<j)-1));

    ll cr = 0;
    for (int j = i; j < n; j++) {
        cr *= 2;
        cr += b[j]-'0';

        if (!cr) continue;
        if (cr > K) break;
        
        me = (ll(me) + pd((msk|(1<<(cr-1))), j+1))%MOD;
    }
    return memo[i&1][msk] = me;
}

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf(" %s", &b[i]);

    ll res = 0;
    for (int i = n; i >= 0; i--) {
        for (int msk = 0; msk < (1<<K); msk++) {
            ll loc = pd(msk, i, 1);
            if (!msk)
                res = (res + loc)%MOD;
        }
    }
    
    printf("%lld\n", res);
}
