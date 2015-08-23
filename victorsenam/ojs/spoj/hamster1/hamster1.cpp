#include <bits/stdc++.h>

using namespace std;

#define PI 3.1415926535897932384626433832795028841971693993751058

int t;
double x, y, v;
double dm, hm, tric, tris, ang, angend, angstr, pt;

double calcu(double ang, double x, double y) {
    tric = (double) cos(ang);
    tris = (double) sin(ang);

    dm = v*v*tric*tris/5;
    hm = v*v*tris*tris/20;

    return x*dm+y*hm;
};

int main () {
    scanf("%d", &t);
    
    while (t--) {
        scanf("%lf %lf %lf", &v, &x, &y);

        angend = PI/2;
        angstr = 0.001;

        while(angend-angstr >= 0.0001) {
            if (calcu(angend, x, y) >= calcu(angstr, x, y)) {
                angstr = (angend+angstr)/2;
            } else {
                angend = (angend+angstr)/2;
            }
        }

        if (calcu(angstr, x, y) > calcu(angend, x, y)) ang = angstr;
        else ang = angend;

        pt = calcu(ang, x, y);
        
        printf("%.3lf %.3lf\n", ang, pt);
    }
}
