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
int n, r;
ll divs[12];
ll val;
bool isp;

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &r);

        printf("Case #1:\n");
        for (ll i = 0; i < (1ll<<(n-2)) && r; i++) {
            isp = 0;
            for (int j = 2; !isp && j < 11; j++) {
                val = 1;
                for (int k = 0; k < n-2; k++) {
                    val *= j;
                    if (i&(1ll<<k))
                        val++;
                }
                val *= j;
                val++;

                divs[j] = 0;
                for (ll k = 2; !divs[j] && k*k <= val; k++)
                    if (val%k == 0)
                        divs[j] = k;
                if (!divs[j])
                    isp = 1;
            }

            if (!isp) {
                printf("1");
                for (int j = 0; j < n-2; j++)
                    printf("%d", !!(i&(1ll<<j)));
                printf("1");

                for (int j = 2; j < 11; j++)
                    printf(" %lld", divs[j]);
                printf("\n");
                r--;
            }
        }
    }
}
