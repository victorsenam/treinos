#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif


int main () {
    int n, k;
    scanf("%d %d", &n, &k);
    k = min(k, n/2);

    ll res = 0;
    for (int i = 1; i <= k; i++) {
        res += n-i;
        res += n-i-k;
    }
    printf("%I64d\n", res);
}
