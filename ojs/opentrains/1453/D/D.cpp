#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

ll l, s;
ll x, y, z, w;
ll la, lb;

ll p[10][2];
int ps;

void printit (ll a, ll b) {
    if (la == a && lb == b) return;
    p[ps][0] = a;
    p[ps][1] = b;
    ps++;
    la = a;
    lb = b;
}

int main () {
    scanf("%lld %lld", &l, &s);

    w = l/2;
    x = w/2;
    y = w-x;

    z = x*y - s;
    la = lb = -1;
    ps = 0;

    if (z < 0 || z > (x-1)*(y-1) || l&1) {
        printf("-1\n");
    } else if (z == 0) {
        printf("4\n0 0\n%lld 0\n%lld %lld\n0 %lld\n", x, x, y, y);
    } else {
        printit( 0ll, 0ll);
        printit( x, 0ll);
        printit( x, 1ll);
        printit( x-z/(y-1), 1ll);
        printit( x-z/(y-1), y-z%(y-1));
        printit( x-z/(y-1)-1, y-z%(y-1));
        printit( x-z/(y-1)-1, y);
        printit( 0ll, y);

        printf("%d\n", ps);
        for (int i = 0; i < ps; i++)
            printf("%lld %lld\n", p[i][0], p[i][1]);
    }
}
