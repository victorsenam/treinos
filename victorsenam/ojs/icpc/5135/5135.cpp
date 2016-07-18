#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define lld I64d
#define DEBUG(...) {}
#endif

const int N = 100007;

int hd[N], nx[N], to[N], es;
int n;
int tc, turn;
int visi[N];
int pre[N], ret[N], os;
int vt;
int cut[N];
ll res;

int cut_vertex (int u, int fr) {
    if (visi[u] == turn) return 0;
    res++;
    visi[u] = turn;
    pre[u] = ret[u] = os++;
    int deg = 0;
    int maxi = -1;

    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (cut_vertex(to[ed], u)) {
            deg++;
            ret[u] = min(ret[u], ret[to[ed]]);
            maxi = max(maxi, ret[to[ed]]);
        } else if (to[ed] != fr) {
            ret[u] = min(ret[u], pre[to[ed]]);
        }
    }
    if ((u == vt && deg >= 2) || (u != vt && maxi >= pre[u])) 
        cut[u] = 1;

    return 1;
}

ll dfs (int u) {
    if (visi[u] == turn) return 0;
    visi[u] = turn;
    if (cut[u]) return 1;
    res++;

    int ret = 0;
    for (int ed = hd[u]; ed; ed = nx[ed])
        ret += dfs(to[ed]);
    return ret;
}

int main () {
    while (scanf("%d", &n) && n) {
        turn++; tc++;
        int init = turn;
        memset(hd, 0, sizeof hd);
        memset(cut, 0, sizeof cut);
        es = 2;

        vt = 0;
        for (int i = 0; i < n; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            a--; b--;
            vt = a;

            nx[es] = hd[a]; to[es] = b; hd[a] = es++;
            nx[es] = hd[b]; to[es] = a; hd[b] = es++;
        }

        os = 0;
        res = 0;
        cut_vertex(vt, -1);
        ll cnt = res;

        ll ways = 1;
        bool ok = 1;
        int qt = 0;
        for (int i = 0; i < N; i++) {
            if (cut[i])
                ok = 0;
            if (!cut[i] && visi[i] == init) {
                turn++;
                res = 0;
                if (dfs(i) == 1) {
                    ways *= res;
                    qt++;
                }
            }
        }
        if (ok) {
            qt = 2; 
            ways = (cnt*(cnt-1))/2;
        }

        printf("Case %d: %d %lld\n", tc, qt, ways);
    }
}
