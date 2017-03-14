#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<double, double> pdd;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;

double p[2][N];
int n;
double acc[2];
double mac[2];

double r[2][N];

pdd getroots (double b, double c) {
    b = -b;
    double deltaroot = sqrt(b*b - 4*c);
    pdd res;
    res.first = (-b + deltaroot) / 2.;
    res.second = (-b - deltaroot) / 2.;
    return res;
}

int main () {
    scanf("%d", &n);

    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < n; i++)
            scanf("%lf", &p[k][i]);
        acc[k] = 1.;
    }
    mac[0] = 1.;
    mac[1] = 0.;


    for (int i = 0; i < n; i++) {
        pdd res = getroots(p[0][i]/mac[0] + (p[1][i]-mac[1])/mac[0], p[0][i]/mac[0]);
        r[0][i] = res.first*acc[0];
        r[1][i] = res.second*acc[1];

        for (int k = 0; k < 2; k++) {
            acc[k] -= r[k][i];
        }
        mac[0] -= p[0][i];
        mac[1] += 0.;// something!! :'(
    }

    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < n; i++)
            printf("%.20f ", r[k][i]);
        printf("\n");
    }
}
