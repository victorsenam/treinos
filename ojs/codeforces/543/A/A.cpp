#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 507;

ll mod;
ll n, m, a[N], b;
ll v[N];
ll memo[N][N];
int visi[N][N];

ll pd (int m, int n) {
    if (m == 0) return 1;
    if (n <= 0) return 0;
    
    if (visi[m][n]) return memo[m][n];
    visi[m][n] = 1;

    memo[m][n] = (pd(m, n-1) + pd(m-1, n))%mod;
    return memo[m][n];
}

int main () {
    scanf("%lld %lld %lld %lld", &n, &m, &b, &mod);

    for (int i = 0; i < n; i++)
        scanf("%lld", a+i);

    sort(a, a+n);
    
    ll res = 0;
    ll mul;

    for (int i = n-1; i >= 0; i--) {
        if (a[i] > b) continue;
        ll c_b = b;
        ll c_m = m;

        mul = 1;

        for (int j = i; j >= 0; j--) {
            if (a[j] == 0)
                v[j] = c_m;
            else
                v[j] = min(c_m, c_b/a[j]);

            c_b -= v[j]*a[j];
            c_m -= v[j];

            mul = (mul * pd(v[j]-(j==i), j+1))%mod;
        }
        if (c_m == 0)
            res = (res+mul)%mod;
    }

    printf("%lld\n", res);
}
