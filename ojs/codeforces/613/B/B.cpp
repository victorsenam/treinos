#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef ll num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;

num a[N], tot, cf, cm, m;
num cost[N];
int n, p[N];
num needs;

bool cmp_p (int i, int j)
{ return a[i] < a[j]; }

int main () {
    scanf("%d %I64d %I64d %I64d %I64d", &n, &tot, &cf, &cm, &m);

    for (int i = 0; i < n; i++) {
        scanf("%I64d", a+i);
        needs += tot - a[i];
        p[i] = i;
    }

    if (needs <= m) {
        printf("%I64d\n", cf*num(n) + cm*tot);
        for (int i = 0; i < n; i++)
            printf("%I64d ", tot);
        printf("\n");
        return 0;
    }

    sort(p, p+n, cmp_p);

    cost[0] = 0;
    for (int i = 1; i < n; i++)
        cost[i] = cost[i-1] + num(i)*(a[p[i]]-a[p[i-1]]);


    num maxi = 0;
    int res = 0;
    num resmon = m;
    needs = 0;
    for (int k = 0; k < n; k++) {
        num mon = m-needs;
        if (mon < 0)
            break;

        int l = upper_bound(cost, cost+n-k, mon) - cost - 1;
        num min = a[p[l]] + (mon-cost[l])/(l+1);

        num loc = min*cm + num(k)*cf;
        if (loc > maxi) {
            maxi = loc;
            res = k;
            resmon = mon;
        }

        needs += tot - a[p[n-k-1]];
    }

    int l = upper_bound(cost, cost+n-res, resmon) - cost - 1;
    num min = a[p[l]] + (resmon-cost[l])/(l+1);

    printf("%I64d\n", maxi);
    for (int i = 0; i <= l; i++)
        a[p[i]] = min;
    for (int i = n-res; i < n; i++)
        a[p[i]] = tot;
    for (int i = 0; i < n; i++)
        printf("%I64d ", a[i]);
}
