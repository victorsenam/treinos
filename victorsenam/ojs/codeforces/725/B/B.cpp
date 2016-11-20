#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

ll s;
char c;

int main () {
    scanf("%lld%c", &s, &c);

    s--;
    ll res = 0;
    res += 16ll*((s)/4);

    s %= 4;

    if ((s&1))
        res += 7ll;

    if (c >= 'd') 
        res += ll('f'-c);
    else
        res += ll(3+c-'a');

    printf("%lld\n", res+1);
}
