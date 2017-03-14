#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define lld I64d
#define DEBUG(...) {}
#endif

const int N = 1000007;

ll k;
int n;

ll c[N];
ll p[N], ps;

int main () {
    scanf("%d %lld", &n, &k);

    for (ll i = 2; i*i <= k; i++) {
        if (k%i == 0)
            p[ps++] = 1ll;
        while (k%i == 0) {
            p[ps-1] *= i;
            k /= i;
        }
    }
    p[ps++] = k;


    for (int i = 0; i < n; i++)
        scanf("%lld", c+i);

    sort(c, c+n);

    for (int i = ps-1; i >= 0; i--) {
        bool ok = 0;
        for (int j = 0; !ok && j < n; j++)
            ok = (c[j]%p[i] == 0);

        if (!ok) {
            printf("No\n");
            return 0;
        }
    }
    printf("Yes\n");
}

