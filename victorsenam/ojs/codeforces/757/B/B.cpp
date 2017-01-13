#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 1e5+7;

int n;
int v[N];
ll qt[N];

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);

        for (ll j = 2; j*j <= v[i]; j++) {
            if (v[i]%j == 0)
                qt[j]++;
            while (v[i]%j == 0)
                v[i] /= j;
        }
        qt[v[i]]++;
    }

    ll res = 1;
    for (int i = 2; i < N; i++) {
        res = max(res, qt[i]);
    }
    printf("%lld\n", res);
}
