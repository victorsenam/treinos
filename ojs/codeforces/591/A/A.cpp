#include <bits/stdc++.h>

using namespace std;

double p, q, l;

int main () {
    scanf("%lf %lf %lf", &l, &p, &q);

    printf("%.7f\n", l*(p/(p+q)));
}
