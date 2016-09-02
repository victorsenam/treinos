#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1002;
const int B = 31;
const ll MOD = 1e6+3;

ll memo[3][N][3];
int n;
ll res[N];
ll mul;
ll a[N];
int ii;

inline bool get(int i, int b) {
    return (!!(a[i]&(1ll<<b)));
}

inline ll pd (int k, int i, int v) {
    if (k == 0) return !v;
    if (i < k) return 0ll;

    return memo[k&1][i][v];
}

int main () {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; i++) {
            scanf("%lld", a+i);
            res[i+1] = 0;
        }

        ll mul = 1;
        for (int b = 0; b < B; b++) {
            for (int k = 1; k <= n; k++) {
                for (int i = k; i <= n; i++)
                    for (int v = 0; v < 2; v++) {
                        memo[k&1][i][v] = pd(k, i-1, v) + pd(k-1, i-1, (v^get(i-1, b)));
                        if (memo[k&1][i][v] >= MOD) memo[k&1][i][v] -= MOD;
                    }
                res[k] = (res[k] + (pd(k, n, 1)*mul)%MOD)%MOD;
            }
            mul = (mul*2ll)%MOD;
        }

        for (int i = 1; i <= n; i++)
            printf("%lld ", res[i]);
        printf("\n");
    }

}
