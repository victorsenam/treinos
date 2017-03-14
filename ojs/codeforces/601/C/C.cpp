#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef double num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 107;
const int M = 1007;

double p[2][N*M];
int n, m;
int r[N], rnk;

int main () {
    scanf("%d %d", &n, &m);

    if (m == 1) {
        printf("%.20lf\n", 1.);
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", r+i);
        rnk += r[i];
    }

    p[0][0] = 1.;
    for (int i = 1; i <= n; i++) {
        bool t = (i&1);
        p[t][0] = 0.;
        for (int j = 1; j < rnk; j++) {
            double & me = p[t][j];

            me = p[t][j-1];

            double dif = 0.;
            if (j) dif += p[!t][j-1];
            if (j-m-1 >= 0) dif -= p[!t][j-m-1];
            if (j-r[i]-1 >= 0) dif += p[!t][j-r[i]-1];
            if (j-r[i] >= 0) dif -= p[!t][j-r[i]];

            me += (1./(m-1))*dif;
        }
    }

    double pr = 0.;
    for (int i = 0; i < rnk; i++)
        pr += p[(n&1)][i];
    printf("%.20lf\n", 1. + double(m-1)*pr);
}
