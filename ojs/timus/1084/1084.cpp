#include <bits/stdc++.h>

using namespace std;

const double pi = 3.14159265359;

double l, r;

int main( ){
    scanf("%lf %lf", &l, &r);
    double a = sqrt(r*r - l*l/4.0);

    if (r <= l/2)
        printf("%.3lf\n", pi*r*r);
    else if (r >= l/sqrt(2.0))
        printf("%.3lf\n", l*l);
    else
        printf("%.3lf\n", (1.0-(asin(a/r)*4.0/pi))*pi*r*r + 2*l*a);
    
}
