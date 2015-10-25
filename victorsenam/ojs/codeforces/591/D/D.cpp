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
        double lo = min(v.x - vm, v.x + vm);
        double hi = -lo;
        double lastres = 1000.0;
        double res = 0.0;

        while (hi - lo > eps && abs(lastres - res) > eps) {
            double pt = lo + (hi-lo)/3.0;
            double st = lo + (hi-lo)*2.0/3.0;

            double dy = sqrt((vm*vm)-(pt-v.x)*(pt-v.x));
            double pr = timeTo(w, (b-(a+(vect(pt,w.y+dy)*t))), vm);
            pr = min(pr, timeTo(w, (b-(a+(vect(pt,w.y-dy)*t))), vm));
            pr += t;

            dy = sqrt((vm*vm)-(st-v.x)*(st-v.x));
            double sr = timeTo(w, (b-(a+(vect(st,w.y+dy)*t))), vm);
            sr = min(sr, timeTo(w, (v-(a+(vect(st,w.y-dy)*t))), vm));
            sr += t;

            printf("%.7lf(%.7lf) %.7lf(%.7lf)\n", pr, pt, sr, st);

            res = min(sr, pr);
            
            if (pr > sr) {
                lo = pt;
            } else {
                hi = st;
            }
        }

        printf("%.9lf\n", res);
    }
}
