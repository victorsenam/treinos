#include <bits/stdc++.h>

using namespace std;

const int N = 200007;
const double eps = 1e-9;

double a[N];
int n;
double lo, hi;
double mid1, mid2, t1, t2;

double solve (double x) {
    double attmin = 0.0;
    double attmax = 0.0;
    double mini = 0.0;
    double maxi = 0.0;
    
    for (int i = 0; i < n; i++) {
        attmin = min(0.0, attmin + a[i]-x);
        attmax = max(0.0, attmax + a[i]-x);

        mini = min(mini, attmin);
        maxi = max(maxi, attmax);
    }
    
    return max(maxi, -mini);
}

int main () {
    scanf("%d", &n);

    lo = 0.0;
    hi = 0.0;
    for (int i = 0; i < n; i++) {
        scanf("%lf", a+i);
        lo = min(lo, a[i]);
        hi = max(hi, a[i]);
    }

    t1 = solve(lo);
    t2 = solve(hi);

    while (hi - lo > eps || abs(t1-t2) > eps) {
        mid1 = lo + (hi-lo)/3.0;
        mid2 = lo + 2.0*(hi-lo)/3.0;

        t1 = solve(mid1);
        t2 = solve(mid2);

        if (t1 > t2) {
            lo = mid1;
        } else {
            hi = mid2;
        }
    }

    double res = t1;
    if (res < eps && res > -eps)
        res = 0.0;
    printf("%.15f\n", res);
}
