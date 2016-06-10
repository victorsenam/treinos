#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define LLD "%lld"
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define LLD "%I64d"
#define DEBUG(...) {}
#endif

ll n;

int main () {
    scanf(LLD, &n);

    int cnt = 0;
    ll mov = 1;

    for (ll i = 2; i*i <= n; i++) {
        if (n%i == 0) {
            n /= i;
            if (cnt < 2)
                mov *= i;
            cnt++;
            i--;
        }
    }

    if (cnt == 1)
        printf("2\n");
    else
        printf("1\n" LLD "\n", cnt?mov:0ll);

}
