#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

#define double long double
const double eps = 1e-6;
const double pi = acos(-1.);

const double sq3 = sqrt(3.);

inline double myasin(double a) {
    double al = asin(a);
    if(al < 0) al += pi;
    return al;
}

inline double myacos(double a) {
    return real(acos<double>(max<double>(-1, min<double>(1, a))));
}

inline double ang2(double a, double b, double l) {
    //return myasin(sqrt((1. / (16. * a * b)) * (a + b + l) * (a + b - l) * (a - b + l) * (-a + b + l)));
    return myacos((-l * l + b * b + a * a) / (2. * a * b));
}

inline double ang(double a, double b, double c, double l) {
    return ang2(a, b, l) + ang2(b, c, l) + ang2(c, a, l);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    double a, b, c;
    while(cin >> a >> b >> c) {
        double l = max(max(abs(a - b), abs(b - c)), abs(c - a));
        double r = min(min(a + b, b + c), c + a);
        if(l > r + eps) { puts("-1.000"); continue; }
        if(ang(a, b, c, r) < 2. * pi - eps) { puts("-1.000"); continue; }
        if(ang(a, b, c, l) > 2. * pi + eps) { puts("-1.000"); continue; }
        for(int t = 0; t < 80; t++) {
            double m = (l + r) / 2.;
            if(ang(a, b, c, m) >= 2. * pi) r = m;
            else l = m;
        }
        printf("%.3Lf\n", l * l * sq3 / 4.);
    }
}
