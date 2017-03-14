#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;

int hd[N], nx[N], to[N], es;
int a[N], b[N];
int n, m;
int qu[N], qi, qf;
int deg[N];

bool solve (int m) {
    if (m == (::m)+1)
        return 1;
    memset(hd, 0, sizeof hd);
    memset(deg, 0, sizeof deg);
    qi = qf = 0;
    es = 2;
    for (int i = 0; i < m; i++) {
        nx[es] = hd[a[i]]; to[es] = b[i]; hd[a[i]] = es; es++;
        deg[b[i]]++;
    }
    
    for (int i = 0; i < n; i++)
        if (!deg[i])
            qu[qf++] = i;
    int cnt = 0;

    while (qi < qf) {
        if (qf - qi > 1) return 0;
        int u = qu[qi++];
        cnt++;

        for (int ed = hd[u]; ed; ed = nx[ed]) {
            deg[to[ed]]--;
            if (deg[to[ed]] == 0)
                qu[qf++] = to[ed];
        }
    }

    return (cnt == n);
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", a+i, b+i);
        a[i]--; b[i]--;
    }

    int lo = 0; int hi = m+1;

    while (lo < hi) {
        int mid = (lo+hi)/2;

        if (solve(mid))
            hi = mid;
        else
            lo = mid+1;
    }

    if (lo == m+1)
        printf("-1");
    else
        printf("%d\n", lo);
}
