#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e5 + 7;

double memo[N][2];
int visi[N][2];
int t[N];
char c[N];
int l[N];
double pr[N];
int n;

double fexp (double a, int e) {
    double r = 1.;
    while (e) {
        if (e&1) r *= a;
        a *= a;
        e >>= 1;
    }
    return r;
}

double calc (double p, int t) {
    p = (1.-p);
    return 1.-(fexp((2.*p-1.), t)+1.)/2.;
}

double pd (int i, bool s) {
    if (i == n) return 0.;
    double & me = memo[i][s];
    if (visi[i][s]) return me;
    visi[i][s] = 1;

    double p = (calc(pr[i], t[i]));
    return me = p*(pd(i+1, l[i]) + (l[i] != s)) + (1.-p)*(pd(i+1, !l[i]) + (l[i] == s));
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %c %lf", &t[i], &c[i], &pr[i]);
        l[i] = (c[i] == 'R');
    }

    printf("%.20f\n", pd(0,0));
}
