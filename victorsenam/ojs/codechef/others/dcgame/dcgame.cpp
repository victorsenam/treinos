#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 2000007;

int n, m;
int a[N], p[N];
ll r[N];
char t, st;
ll lw, up;
ll val;
int uf[N], wf[N];

bool cmp_t (int i, int j) {
    return a[i] < a[j];
}

inline int find (int i) {
    if (i == uf[i]) return i;
    return uf[i] = find(uf[i]);
}

inline void join (int i, int j) {
    i = find(i); j = find(j);
    if (i == j) return;
    if (wf[i] < wf[j]) swap(i, j);
    wf[i] += wf[j];
    uf[j] = i;
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d", a+i);
        p[i] = i;
        uf[i] = i;
        wf[i] = 1;
    }

    r[n] = 0;
    stable_sort(p,p+n, cmp_t);

    for (int i = 0; i < n; i++) {
        lw = 1;
        if (p[i] && a[p[i]] >= a[p[i]-1]) {
            lw += wf[find(p[i]-1)];
            join(p[i], p[i]-1);
        }
        up = 1;
        if (p[i] < n-1 && a[p[i]] > a[p[i]+1]) {
            up += wf[find(p[i]+1)];
            join(p[i], p[i]+1);
        }

        r[i] = (lw*up);
    }

    for (int i = n-1; i >= 0; i--)
        r[i] = r[i] + r[i+1];

    ll tot = ((ll(n)*ll(n+1))>>1);

    while (m--) {
        scanf(" %c %d %c\n", &t, a+n, &st);

        if (t == '=') {
            lw = lower_bound(p, p+n, n, cmp_t) - p;
            up = upper_bound(p, p+n, n, cmp_t) - p;
            val = r[lw] - r[up];
        } else if (t == '>') {
            up = upper_bound(p, p+n, n, cmp_t) - p;
            val = r[up];
        } else {
            lw = lower_bound(p, p+n, n, cmp_t) - p;
            val = tot - r[lw];
        }

        putchar(((st-1)^1^(val&1))+1);
    }
    putchar('\n');
}
