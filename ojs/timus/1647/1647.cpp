#include <bits/stdc++.h>

using namespace std;

double x[3], y[3];

int main () {
    scanf("%lf %lf %lf %lf %lf %lf", x, y, x+1, y+1, x+2, y+2);
    
    double p = 0.0;
    for (int i = 0; i < 3; i++)
        p += sqrt(x[i]*x[i]+y[i]*y[i]);

    double a = x[1]-x[0];
    double b = y[1]-y[0];
    double c = x[2]-x[0];
    double d = y[2]-y[0];

    double v = a*d-b*c;
    v *= v;

    double r = 2.*sqrt(a*a+b*b);
    double s = -p;
    double t = sqrt(c*c+d*d);
    printf("%.20f %.20f %.20f\n", r, s, t);

    printf("%.20f\n", 4*r*t);

    double alpha = (-s + sqrt(s*s-4*r*t))/(2.*r);

    printf("%.20f\n", alpha);
}
