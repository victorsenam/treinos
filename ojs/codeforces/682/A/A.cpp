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

int n, m;
ll qt[2][5];

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        qt[0][i%5]++;
    for (int i = 1; i <= m; i++)
        qt[1][i%5]++;

    ll res = 0;
    for (int i = 0; i < 5; i++) {
        res += qt[0][i]*qt[1][(5-i)%5];
    }

    printf("%lld\n", res);
}
