#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const double pi = 3.1415926535897932384626433832795028841;
const double eps = 1e-9;

int n;
double ix, iy;
double xs, ys, lx, ly, x, y;
double far, clo;

inline double dist (double xa, double ya, double xb, double yb)
{ return (xa-ya)*(xa-ya) + (xb-yb)*(xb-yb); }

double ptseg (double xa, double ya, double xb, double yb) {
    double lo = 0.0;
    double hi = 1.0;

    while (hi - lo > eps) {
        double m1 = lo + (hi-lo)/3.;
        double m2 = lo + 2.*(hi-lo)/3.;

        if (dist(xa+m1*(xb-xa), ya+m1*(yb-ya), ix, iy) > dist(xa+m2*(xb-xa), ya+m2*(yb-ya), ix, iy))
            lo = m1;
        else
            hi = m2;
    }

    double res = dist(xa+lo*(xb-xa), ya+lo*(yb-ya), ix, iy);
    printf("%f %f\n", lo, res);
    return res;
}

int main () {
    scanf("%d", &n);

    scanf("%lf %lf", &ix, &iy);

    far = 0.0;
    clo = 1.0/0.0;

    scanf("%lf %lf", &xs, &ys);
    far = max(far, dist(ix, iy, xs, ys));
    lx = xs;
    ly = ys;

    for (int i = 1; i < n; i++) {
        scanf("%lf %lf", &x, &y);

        far = max(far, dist(ix, iy, x, y));

        clo = min(clo, ptseg(lx, ly, x, y));
        lx = x;
        ly = y;
    }

    clo = min(clo, ptseg(lx, ly, xs, ys));

    printf("%lf\n", pi*(far-clo));
}
