#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1007;
const ll MOD = 998244353ll;

int n, m;
ll fx[N];
int p;
int cnt;
ll vs[N], tr;

ll gcd (ll a, ll b) {
    return b ? gcd(b, a%b) : a;
}

int main () {
    freopen("cover.in", "r", stdin);
    freopen("cover.out", "w", stdout);
    
    fx[0] = 1ll;
    for (int i = 1; i < N; i++)
        fx[i] = (fx[i-1]*2ll)%MOD;

    while (scanf("%d", &n) != EOF && n) {
        tr++;
        ll res = 0;
        for (m = 1; m <= n; m++) {
            cnt = 0;
            p = (n%m);
            tr++;
            for (int i = 0; i < m; i++) {
                int u = i;
                cnt += (vs[u] != tr);
                while (u < m && vs[u] != tr) {
                    vs[u] = tr;
                    u += p;
                }
            }
            res = (res + fx[cnt])%MOD;
        }
        printf("%lld\n", res);
    }
}
