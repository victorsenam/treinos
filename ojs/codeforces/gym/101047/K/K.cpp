#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 2e3+8;

double v[N], a[N];
int t, n;
double res;

inline double calc (double a, double b, double c) {
    double x = (a*a+b*b-c*c)/(2.*a);
    double h = sqrt(b*b-x*x);
    return (h*a)/2.;
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        res = 1./0.;

        for (int i = 0; i < n; i++) {
            scanf("%lf", a+i);
        }
        sort(a, a+n);
        for (int i = 1; i < n; i++) { // b
            for (int j = i+1; j < n; j++) { // a
                int c = upper_bound(a, a+i, a[j]-a[i]) - a;
                if (c >= i) continue;
                res = min(res, calc(a[j], a[i], a[c]));
            }
        }
        if (res == 1./0.)
            printf("-1\n");
        else
            printf("%.20f\n", res);
    }
}
