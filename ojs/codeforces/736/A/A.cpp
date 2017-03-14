#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

int main () {
    ll n;
    scanf("%lld", &n);

    if (n == 2) 
        printf("1\n");
    else {
        ll l = 2;
        ll c = 3;
        int res = 1;
        while (c <= n) {
            ll nw = l+c;
            l = c;
            c = nw;
            res++;
        }
        printf("%d\n", res);
    }
}
