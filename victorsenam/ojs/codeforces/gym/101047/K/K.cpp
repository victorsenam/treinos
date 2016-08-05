#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e3+8;

double v[N], a[N];
int t, n;
double res;

inline double calc (double a, double b, double c)
{ return sqrt((b*b-c*c+a*a)/2.*a + b*b)*a/2.; }

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        res = 1./0.;

        for (int i = 0; i < n; i++) {
            scanf("%lf", a+i);
        }
        sort(a, a+n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                int lb = upper_bound(a+j, a+n, a[i]-a[j]) - a;
                while (lb == i || lb == j) lb++;
                if (lb >= n) continue;
                DEBUG("%.2f %.2f %.2f\n", a[i], a[j], a[lb]);
                if (a[i] + a[j] <= a[lb]) continue;
                if (a[lb] + a[i] <= a[j]) continue;
                res = min(res, calc(a[i], a[lb], a[j]));
            }
        }
        if (res == 1./0.)
            printf("-1\n");
        else
        printf("%.20f\n", res);
    }
}
