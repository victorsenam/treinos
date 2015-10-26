#include <bits/stdc++.h>

using namespace std;

const double pi = 3.14159265359;

int n;
double r;
double a, b;
double la, lb;
double ia, ib;

int main () {
    scanf("%d %lf", &n, &r);

    scanf("%lf %lf", &a, &b);
    ia = la = a;
    ib = lb = b;

    double res = 0.0;
    for (int i = 1; i < n; i++) {
        scanf("%lf %lf", &a, &b);

        res += sqrt((a-la)*(a-la)+(b-lb)*(b-lb));
        la = a;
        lb = b;
    }

    res += sqrt((ia-la)*(ia-la)+(ib-lb)*(ib-lb));
    printf("%.2lf\n", res+(2.0*pi*r));
}
