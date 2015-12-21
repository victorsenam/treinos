#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

const int N = 100007;
const double eps = 1e-9;

int n;
double ta, tb;
double sa, sb;
double a[N], b[N], g[N];
double s[N];
int p[N];

bool cmp_it (int i, int j) {
   //return mp(b[i], -a[i]) < mp(b[j], -a[j]);
    if(b[i] < eps && b[j] < eps) return a[i] < a[j];
    if(b[i]*b[j] < eps)
        return b[i] < eps;
    return a[i]*b[j] > a[j]*b[i];
}

int main( ){
    freopen("burrito.in", "r", stdin);
    freopen("burrito.out", "w", stdout);
    scanf("%d %lf %lf", &n, &ta, &tb);

    for (int i = 0; i < n; i++)
        scanf("%lf %lf %lf", g+i, a+i, b+i);
    
    sa = sb = 0;

    for (int i = 0; i < n; i++)
        p[i] = i;

    sort(p, p+n, cmp_it);

    for (int i = 0; i < n; i++) {
        int k = p[i];
        if(b[k] < eps)
            s[k] = g[k];
        else if (tb-sb < eps)
            s[k] = 0;
        else
            s[k] = min((tb-sb)/b[k],g[k]);

        sb += b[k]*s[k];
        sa += a[k]*s[k];
    }

    if (sa < ta) {
        printf("-1 -1\n");
        return 0;
    }

    printf("%.20f %.20f\n", sa, sb);
    for (int i = 0; i < n; i++)
        printf("%.20f ", s[i]);
    printf("\n");
}
