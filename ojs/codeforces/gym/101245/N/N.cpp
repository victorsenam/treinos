#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef unsigned long long int ll;
typedef pair<int, int> pii;
#define pb push_back

ll s, p;
long double eps = 1e-9;

int main () {
    scanf("%llu %llu", &s, &p);

    if (p < s) {
        printf("2\n");
        return 0;
    }

    for (ll k = 1; k <= s && k < 20; k++) {
        long double x = (double(s)/double(k));
        long double r = 1;
        for (int i = 0; i < k; i++)
            r *= x;

        if (r - p >= -eps) {
            printf("%lld\n", k);
            return 0;
        }
    }

    printf("-1\n");
}
