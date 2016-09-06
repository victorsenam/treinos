#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

ll n, q, x, y, k;

int main () {
    scanf("%lld %lld %lld %lld", &n, &x, &y, &q);

    for (int i = 0; i < q; i++) {
        scanf("%lld", &k);

        k--;

        x = y = 0;

        int cnt = 0;
        int s = n&1;
        while (k) {
            if ((k&1)^(s))
                x++;
            else
                y++;

            s = !s;
            k >>= 1;
            cnt++;
        }
        
        ll r = n - cnt;
        x += (r+1)/2;
        y += (r)/2;

        printf("%lld %lld\n", x, y);
    }
}
