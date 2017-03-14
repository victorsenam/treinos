#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int K = 20;
const int N = 75;
const ll MOD = 1e9+7;

int memo[(1<<K)][N];
char b[N+3];
int nx[N+3];
int n;

ll pd (int msk, int i) {
    if (memo[msk][i] != -1)
        return memo[msk][i];

    ll me = 0;

    if (!msk && i < n)
        me = pd(0, i+1);

    for (int k = 1; k < (1<<K); k = (k + k + 1))
        if (msk == k)
            me++;

    int cr = 0;
    for (int j = nx[i]; j < n; j++) {
        cr = (cr + cr + b[j] - '0');
        if (cr > K) break;
        me = (me + pd(msk|(1<<(cr-1)), j+1))%MOD;
    }
    
    memo[msk][i] = me;
    return me;
}

int main () {
    memset(memo, -1, sizeof memo);
    scanf("%d", &n);
    scanf(" %s", b);

    nx[n] = n;
    for (int i = n-1; i >= 0; i--)
        if (b[i] != '0')
            nx[i] = i;
        else
            nx[i] = nx[i+1];

    printf("%lld\n", pd(0, 0));
}
