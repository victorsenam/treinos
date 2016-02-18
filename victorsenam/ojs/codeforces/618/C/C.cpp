#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;

ll x[N], y[N];
int n;
int p[N];
ll xi, yi, xj, yj;

ll cross (int i, int j) {
    xi = x[i]-x[p[0]];
    yi = y[i]-y[p[0]]; 
    xj = x[j]-x[p[0]];
    yj = y[j]-x[p[0]];

    return xi*yj - xj*yi;
}

bool cmp_s (int i, int j) {
    ll val = cross(i, j);

    if (val == 0)
        return (xi*xi + yi*yi < xj*xj + yj*yj);
    return val < 0;
}

bool cmp_l (int i, int j) {
    if (x[i] == x[j])
        return y[i] < y[j];
    return x[i] < x[j];
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%I64d %I64d", x+i, y+i);
        p[i] = i;
    }

    sort(p, p+n, cmp_l);
    sort(p+1, p+n, cmp_s);

    printf("%d %d ", p[0]+1, p[1]+1);

    for (int i = 2; i < n; i++) {
        if (cross(p[1], p[i])) {
            printf("%d\n", p[i]+1);
            return 0;
        }
    }
}
