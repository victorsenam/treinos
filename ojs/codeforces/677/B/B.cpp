#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;

int n;
ll t;
ll a[N];
ll k, h;
ll occ;

int main () {
    scanf("%d %I64d %I64d", &n, &h, &k);

    for (int i = 0; i < n; i++)
        scanf("%I64d", a+i);

    occ = 0;
    int j = 0;

    while (j < n || occ) {
        while (j < n && occ + a[j] <= h)
            occ += a[j++];
        
        occ = max(0ll, occ-k);
        t++;
    }

    printf("%I64d\n", t);
}
