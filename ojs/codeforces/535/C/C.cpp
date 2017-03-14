#include <bits/stdc++.h>

using namespace std;

unsigned long long int a, b, n, l, t, m, it, im;

int main () {
    scanf("%llu %llu %llu", &a, &b, &n);

    while (n--) {
        scanf("%llu %llu %llu", &l, &t, &m);

        im = m+l-1;
        it = (t-a+b)/b;

        printf("== %llu %llu\n", im, it);

        if (it < l) printf("-1\n");
        else if (it < im-1) printf("%llu\n", it);
        else {
            t -= a;
            while (a+b*(im-1) < t) {
                printf("== %d < %d\n", im, t);
                t -= b*l;
                im++;
                l++;
            }

            printf("%llu\n", im);
        }
    }
}
