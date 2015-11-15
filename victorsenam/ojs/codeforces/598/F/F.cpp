#include <bits/stdc++.h>

using namespace std;

const int N = 1007;
const int M = 103;
const double eps = 10e-9;

double x[N], y[N], a[N], b[N];
int n, m;
double x1, y11, x2, y2;
double pa, pb;

inline double getb (double x1, double y11, double x2, double y2) 
{ return (y11*x2-x1*y2)/(x2-x1); }

inline double geta (double b, double x, double y) 
{ return (y-b)/x; }

inline double dist (double x1, double y11, double x2, double y2) 
{ return sqrt((x1-x2)*(x1-x2)+(y11-y2)*(y11-y2)); }

inline double getx (double a1, double b1, double a2, double b2)
{ return (b2-b1)/(a1-a2); }

inline double gety (double x, double a, double b)
{ return (a*x+b); }

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", x+i, y+i);

        if (i) {
            b[i] = getb(x[i], y[i], x[i-1], y[i-1]);
            a[i] = geta(b[i], x[i], y[i]);
        }
    }

    b[0] = getb(x[0], y[0], x[n-1], y[n-1]);
    a[0] = geta(b[0], x[0], y[0]);

    for (int i = 0; i < m; i++) {
        scanf("%lf %lf", &x1, &y11, &x2, &y2);
        printf("==  ==\n");

        pb = getb(x1, y11, x2, y2);
        pa = geta(pb, x1, y11);
        double rx[2], ry[2];
        int rr = 0;

        for (int i = 0; i < n && rr < 2; i++) {
            double ix = getx(pa, pb, a[i], b[i]);
            double iy = gety(ix, pa, pb);

            printf("(%lf,%lf) - (%lf,%lf) - (%lf,%lf)\n", x[i], y[i], ix, iy, x[(i+n-1)%n], y[(i+n-1)%n]);

            double d1 = dist(ix, iy, x[i], y[i]);
            double d2 = dist(ix, iy, x[(i+n-1)%n], y[(i+n-1)%n]);
            double dd = dist(x[i], y[i], x[(i+n-1)%n], y[(i+n-1)%n]);

            if (abs(d1+d2 - dd) < eps) {
                rx[rr] = ix;
                ry[rr] = iy;
                rr++;
            }
        }

        if (rr == 2) {
            printf("%.20f\n", dist(rx[0], ry[0], rx[1], ry[1]));
        } else {
            printf("%.20f\n", 0);
        }
    }
}
