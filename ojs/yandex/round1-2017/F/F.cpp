#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

int n;
int hd[N], nx[N], to[N], es;
int visi[N], turn, pr[N], rs[N], de[N];

/*
int dfs (int u, int fr) {
    if (visi[u] == turn) return 0;
    visi[u] = turn;
    pr[u] = fr;
    siz[u] = 1;

    for (int ed = hd[u]; ed; ed = nx[ed])
        if (to[ed] != fr && !rs[to[ed]])
            siz[u] += dfs(to[ed], u);
    return siz[u];
}
*/

int furt (int u, int fr, int dep) {
    if (visi[u] == turn) return 0;
    visi[u] = turn;
    pr[u] = fr;
    de[u] = dep;

    int cr = u;

    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (to[ed] != fr && !rs[to[ed]]) {
            int v = furt(to[ed], u, dep+1);

            if (de[v] > de[cr])
                cr = v;
        }
    }

    return cr;
}

int build (int u, int depth, int fr) {
    turn++;
    u = furt(u, fr, 0);
    turn++;
    u = furt(u, fr, 0);

    int vl = de[u]/2;
    while (de[u] != vl)
        u = pr[u];

    int rr = depth;
    rs[u] = depth;

    //debug("== %d -> %d\n", u+1, rr);

    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (to[ed] != fr && !rs[to[ed]]) {
            rr = max(rr, build(to[ed], depth+1, u));
        }
    }
    return rr;
}

int main () {
    scanf("%d", &n);

    es = 2;
    for (int i = 0; i < n-1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        to[es] = v; nx[es] = hd[u]; hd[u] = es++;
        to[es] = u; nx[es] = hd[v]; hd[v] = es++;
    }

    printf("%d\n", build(0, 1, -1));
}

