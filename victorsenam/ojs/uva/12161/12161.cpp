#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 70007;

int n, md;
int hd[N], nx[N], to[N], d[N], l[N], es;
int ds[N], ord, op[N], cl[N], p[N];
map<int, int> par[N];

void preproc (int fr, int d) {
    int u = to[fr];
    op[u] = ord++;
    ds[u] = d;
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if ((ed|1) != (fr|1)) continue;
        preproc(ed, d+l[ed]);
    }
    cl[u] = ord;
}

bool cmp_t (int i, int j)
{ return op[i] < op[j]; }

int main () {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &md);
        memset(hd, 0, sizeof hd);
        es = 2;

        for (int i = 1; i < n; i++) {
            scanf("%d %d %d %d", to[es], to[es+1], d[es], l[es]);
            d[es+1] = d[es]; l[es+1] = l[es];
            nx[es] = hd[to[es^1]]; hd[to[es^1]] = es; es++;
            nx[es] = hd[to[es^1]]; hd[to[es^1]] = es; es++;
            p[i] = i;
        }

        preproc(0, 0);
        sort(p, p+n, cmp_t);
    }
}
