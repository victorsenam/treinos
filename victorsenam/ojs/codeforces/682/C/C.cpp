#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#define lld I64d
#endif

const int N = 200007;

int n;
ll a[N];
ll d[N];
int sub[N];
int hd[N], to[N], nx[N], es;
ll wg[N];
int deg[N];
int c, w;
int visi[N];
int qu[N], qi, qf;
int pai[N];

int dfs (int u, ll sum) {
    sum = max(sum, 0ll);
    int res = 0;
    sub[u] = 1;
    d[u] = sum;
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        res += dfs(to[ed], sum+wg[ed]);
        sub[u] += sub[to[ed]];
    }
    
    if (d[u] > a[u])
        return sub[u];
    return res;
}

int main () {
    scanf("%d", &n);
    for (int i =0 ; i < n; i++ ){
        scanf("%lld ", a+i);
    }

    es = 2;
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &c, &w);
        c--;
        nx[es] = hd[c]; to[es] = i; wg[es] = w; hd[c] = es++;
    }

    printf("%d\n", dfs(0, 0));
}
