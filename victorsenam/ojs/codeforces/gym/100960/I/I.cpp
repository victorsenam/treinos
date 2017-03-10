#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 20;
const int M = 2e3+7;

int n, m;
int hd[N], to[M], nx[M], wg[M], rs[M], es;
int p[M];

int find (int u) {
    if (uf[u] == u) return u;
    return uf[u] = find(uf[u]);
}

void join (int u, int v) {
    if ((u = find(u)) == (v = find(v))) return;
    if (wf[u] > wf[v]) swap(u,v);
    wf[v] += wf[u];
    uf[u] = v;
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        wf[i] = 1;
        uf[i] = i;
    }

    es = 2;
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d %d", &a, &b, &wg[es]);
        wg[es+1] = wg[es];
        a--; b--;

        p[i] = es;
        to[es] = b; es++;
        to[es] = a; es++;
    }
    
    sort(p, p+m, [](int i, int j) {
        return wg[i] < wg[j];
    });

    int res = 0;
    int l = 0;
    while (l < n) {
        int r = l;
        while (r < n && wg[p[l]] == wg[p[r]])
            r++;

        for (int i = 0; i < n; i++)
            hd[i] = 0;
            
        for (int _i = l; _i < r; _i++) {
            int ed = p[_i];
            int a = find(to[ed]);
            int b = find(to[ed+1]);

            if (a != b) {
                nx[ed+1] = hd[a]; hd[a] = ed+1;
                nx[ed] = hd[b]; hd[b] = ed;
            }
        }
        
        cvis = cbri = 0;
        for (int i = 0; i < n; i++) {
            if (find(i) == i)
                dfs(i);
        }

        bool mv_bri = (wg[p[l]] && cbri < cvis-cbri);

        for (int _i = l; _i < r; _i++) {
            int ed = p[_i];
            
            res[ed] = wg[ed];
            if (isb[ed] && mv_bri)
                res[ed]--;
            else if (!isb[ed] && !mv_bri)
                res[ed]++;
        }
        
        l = r;
    }
}
