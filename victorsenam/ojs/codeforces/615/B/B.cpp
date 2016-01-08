#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef ll num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define DEBUG(...) {}
#endif

const int N = 100007;
const int M = 200007;

int n, m;
int hd[N], nx[M], to[M], es;
num dg[N];
int visi[N];
num res[N];

num dfs (int u) {
    if (visi[u])
        return res[u];
    visi[u] = 1;

    res[u] = 1;
    for (int ed = hd[u]; ed != -1; ed = nx[ed])
        res[u] = max(res[u], dfs(to[ed])+1);
    return res[u];
}

int main () {
    scanf("%d %d", &n, &m);

    memset(hd, -1, sizeof hd);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        if (a < b)
            swap(a, b);
        nx[es] = hd[a]; hd[a] = es; to[es] = b; es++;
        dg[a]++;
        dg[b]++;
    }

    num maxi = 0;
    for (int i = 0; i < n; i++) {
        maxi = max(maxi, dg[i]*dfs(i));
    }
    printf("%I64d\n", maxi);
}
