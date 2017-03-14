#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define LLD "%lld"
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define LLD "%I64d"
#define DEBUG(...) {}
#endif

const int N = 207;

int n, l, k;
double p[N];
int perm[N];
int a[N];
double memo[N][N][N];
int visi[N][N][N];

bool cmp_t(int i, int j) {
    return a[i] > a[j];
}

double pd (int i, int l, int k) {
    l = max(l, 0);
    k = min(k, n);
    if (k < 0) return 0.;
    if (i == n) return (l == 0);

    double & me = memo[i][l][k];
    if (visi[i][l][k]) return me;
    visi[i][l][k] = 1;
    me = 0.;

    me = p[perm[i]]*pd(i+1, l-1, k+a[perm[i]]) + (1.-p[perm[i]])*pd(i+1, l, k);
    return me;
}

int main () {
    scanf("%d %d %d", &n, &l, &k);

    for (int i = 0; i < n; i++) {
        scanf("%lf", p+i);
        p[i] /= 100.;
        perm[i] = i;
    }

    for (int i = 0; i < n; i++)
        scanf("%d", a+i);

    sort(perm, perm+n, cmp_t);

    printf("%.20f\n", pd(0, l, k));
}
