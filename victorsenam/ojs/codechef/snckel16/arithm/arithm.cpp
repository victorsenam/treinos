#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

int t;
ll n, s;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%lld %lld", &n, &s);

        bool res = 1;
        if ((2ll*s)%n) {
            res = 0;
        } else {
            s *= 2ll;
            s /= n;
            
            s -= n-1;

            if (s < 2 || s%2ll) {
                s -= n-1;
                if (s < 2 || s%2ll)
                    res = 0;
            }
        }

        if (res)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
