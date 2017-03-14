#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define lld I64d
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

ll a, b, c;

int main () {
    
    scanf("%lld %lld %lld", &a, &b, &c);

    b -= a;
    if (c < 0) {
        b = -b;
        c = -c;
    }
    
    bool ok = 0;
    if (c > 0) {
        if (b%c == 0 && b >= 0)
            ok = 1;
    } else {
        if (b == 0)
            ok =1;
    }

    if (ok)
        printf("YES\n");
    else
        printf("NO\n");
}
