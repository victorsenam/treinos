// INCOMPLETO
#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-9;

struct vect {
    double x, y;

    vect() {}
    vect(double a, double b) : x(a), y(b) {}

    vect operator + (const vect & b) 
    { return vect(x+b.x, y+b.y); }
    vect operator - (const vect & b) 
    { return vect(x-b.x, y-b.y); }
    double norm_sq ()
    { return x*x+y*y; }
    vect operator * (double al)
    { return vect(x*al, y*al); }
};

double timeTo (vect w, vect s, double vm) {
    return sqrt((s.norm_sq())/(vm*vm - w.norm_sq()));
}

vect a, b;
double vm, t;
vect v, w;

int main () {
    scanf("%lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y);
    scanf("%lf %lf", &vm, &t);
    scanf("%lf %lf", &v.x, &v.y);
    scanf("%lf %lf", &w.x, &w.y);

    double fs = timeTo(v, b-a, vm);

    if (fs - t < eps) {
        printf("%.9lf\n", fs);
    } else {
        double lo = -1.0;
        double hi = 1.0;
        double lastres = 1000.0;
        double res = 0.0;
        double mini = res;

        while (hi - lo > eps && abs(lastres - res) > eps) {
            double pt = lo + (hi-lo)/3.0;
            double ps = lo + (hi-lo)*2.0/3.0;

            double tr = t + timeTo(w, b-a+((vect(pt, sqrt(1.0-pt*pt))*vm+v)*t), vm);
            double sr = t + timeTo(w, b-a+((vect(ps, sqrt(1.0-ps*ps))*vm+v)*t), vm);

            lastres = res;
            if (tr > sr) {
                lo = tr;
                res = sr;
            } else {
                hi = sr;
                res = tr;
            }
        }
        mini = res;
        lo = -1.0;
        hi = 1.0;
        while (hi - lo > eps && abs(lastres - res) > eps) {
            double pt = lo + (hi-lo)/3.0;
            double ps = lo + (hi-lo)*2.0/3.0;

            double tr = t + timeTo(w, b-a+((vect(pt, -sqrt(1.0-pt*pt))*vm+v)*t), vm);
            double sr = t + timeTo(w, b-a+((vect(ps, -sqrt(1.0-ps*ps))*vm+v)*t), vm);

            lastres = res;
            if (tr > sr) {
                lo = tr;
                res = sr;
            } else {
                hi = sr;
                res = tr;
            }
            mini = min(mini, res);
        }

        printf("%.9lf\n", mini);
    }
}
