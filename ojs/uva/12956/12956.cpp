#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 103;
const num MOD = 1000000007ll;

num memo[N][N];
int vis[N][N];
int turn;
num comb[N][N];
int n, k;

inline num mod (num a) {
    return a%MOD;
}

num pd (int n, int g) {
    if (n == 0)
        return (g<=k);
    if (g >= k)
        return 0;

    num & me = memo[n][g];
    if (vis[n][g] == turn)
        return me;
    vis[n][g] = turn;
    
    me = 0;

    for (int j = 1; j <= n; j++)
        me = mod(me + mod(mod(mod(comb[n-1][j-1]*j)*pd(j-1, 1))*pd(n-j, g+1)));

    return me;
}

int main () {
    for (int i = 0; i < N; i++)
        comb[i][0] = 1ll;
    
    for (int i = 1; i < N; i++)
        for (int j = 1; j < N; j++)
            comb[i][j] = mod(comb[i-1][j-1]+comb[i-1][j]);

    while (scanf("%d %d", &n, &k) != EOF) {
        turn++;
        printf("%lld\n", (pd(n-1, 0))%MOD);
    }
}
