#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e6;

int sieve[N];

int main () {
    int ts;
    int n;
    scanf("%d", &ts);
    while (ts--) {
        scanf("%d", &n);

        for (ll x = 6; x; x++) {
            ll y = x;
            int pr = 0;
            for (ll i = 2; i*i <= y; i++) {
                if (y%i == 0)
                    pr++;
                while (y%i == 0) 
                    y /= i;
            }

            if (y != 1)
                pr++;

            if (pr >= 3)
                n--;
            if (!n) {
                printf("%lld\n", x);
                break;
            }
        }

    }
}
