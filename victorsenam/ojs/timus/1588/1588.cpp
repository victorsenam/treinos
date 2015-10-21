#include <bits/stdc++.h>

using namespace std;

typedef double num;

const int N = 304;
const num eps = 1e-9;

num wg[N*N], a[N*N], b[N*N], x[N], y[N];
int n, p[N*N];

bool cmp_ed (int i, int j) {
    if (abs(a[i]-a[j]) < eps) {
        if (abs(b[i]-b[j]) < eps)
            return wg[i] > wg[j];
        return b[i] < b[j];
    }
    return a[i] < a[j];
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%lf %lf", x+i, y+i);

    int es = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            p[es] = es;
            a[es] = x[i]-x[j];
            b[es] = y[i]-y[j];
            wg[es] = sqrt(a[es]*a[es]+b[es]*b[es]);

            if (a[es] < 0) {
                a[es] = -a[es];
                b[es] = -b[es];
            }

            a[es] /= wg[es];
            b[es] /= wg[es];
            printf("((%.7lf,%.7lf)-(%.7lf,%.7lf))/%.7lf = (%.7lf,%.7lf)\n", x[i], y[i], x[j], y[j], wg[es], a[es], b[es]);
            es++;
        }
    }

    sort(p, p+es, cmp_ed);

    num res = wg[p[0]];
    for (int i = 1; i < es; i++) {
        if (abs(a[p[i-1]]-a[p[i]]) < eps && abs(b[p[i-1]]-b[p[i]]) < eps)
            continue;
        
        printf("%.7lf\n", wg[p[i]]);
        res += wg[p[i]];
    }

    printf("%.0lf\n", res);
}



