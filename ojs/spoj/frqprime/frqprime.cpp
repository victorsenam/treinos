#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5 + 7;

int n, k, t;
bool comp[N];
int prs[N], ps;
ll res;

int main () {
    prs[ps++] = 1;
    for (ll i = 2; i < N; i++)
        if (!comp[i]) {
            prs[ps++] = i;
            for (ll j = i+i; j < N; j += i)
                comp[j] = 1;
        }

    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &k);

        if (k == 0) {
            printf("%lld\n", ll(n-1)*ll(n)/2ll);
            continue;
        }

        res = 0;
        for (int i = 1; i + k - 1 < ps && prs[i+k-1] <= n; i++)
            res += ll(prs[i]-prs[i-1])*ll(n+1-prs[i+k-1]);
        printf("%lld\n", res);
    }
}
