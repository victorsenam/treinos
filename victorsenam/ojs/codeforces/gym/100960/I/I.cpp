#include <bits/stdc++.h>
//#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#define debug(...) {}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 22;
const int M = 2e3+7;

int n, m;
int hd[N], to[M], nx[M], wg[M], rs[M], es;
int p[M];
int od[N], os;
int rt[N];
int vd[N], vs;
int isb[M], isi[M], cons[M];
int uf[N], wf[N];
int cst, cig;
int res;
int seen[M];

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

int mrk (int u, int p) {
    u = find(u);
    if (vd[u] == vs) return 0;
    vd[u] = vs;
    
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (!cons[(ed|1)-1] || isb[(ed|1)-1] || to[ed] == p) continue;
        if (rs[(ed|1)-1] != wg[(ed|1)-1]) continue;
        if (seen[(ed|1)-1]) continue;
        seen[(ed|1)-1] = 1;

        if (mrk(to[ed], u)) {
            debug("ST: %d %d\n", to[ed|1]+1, to[(ed|1)-1]+1);
            cst++;
        } else {
            debug("NO: %d %d\n", to[ed|1]+1, to[(ed|1)-1]+1);
            cig++;
        }
    }

    return 1;
}

int go (int u, int p) {
    u = find(u);
    if (vd[u] == vs + 1) return 0;
    vd[u] = vs + 1;

    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (!cons[(ed|1)-1] || isb[(ed|1)-1] || to[ed] == p) continue;
        if (rs[(ed|1)-1] != wg[(ed|1)-1]) continue;
        if (seen[(ed|1)-1] == 2) continue;
        seen[(ed|1)-1] = 2;

        if (go(to[ed], u)) {
            if (cig > cst) {
                debug("- (%d,%d)\n", to[ed|1]+1, to[(ed|1)-1]+1);
                rs[(ed|1)-1]--;
                res++;
            }
        } else if (cig <= cst) {
            debug("+ (%d,%d)\n", to[ed|1]+1, to[(ed|1)-1]+1);
            rs[(ed|1)-1]++;
            res++;
        }
    }

    return 1;
}

int dfs (int fr) {
    int u = find(to[fr]);

    if (vd[u] == vs)
        return od[u];

    vd[u] = vs;
    rt[u] = od[u] = os++;

    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if ((fr|1) == (ed|1)) continue;
        rt[u] = min(rt[u], dfs(ed));
    }

    if (fr && rt[u] == od[u]) {
        debug("bridge (%d,%d)\n", to[fr|1]+1, to[(fr|1)-1]+1);
        isb[(fr|1)-1] = 1;
    }

    return rt[u];
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
        rs[es] = wg[es];
        a--; b--;

        p[i] = es;
        to[es] = b; es++;
        to[es] = a; es++;
    }
    
    sort(p, p+m, [](int i, int j) {
        return wg[i] < wg[j];
    });

    res = 0;
    int l = 0;
    while (l < m) {
        int r = l;
        debug("PESO %d\n", wg[p[l]]);
        while (r < m && wg[p[l]] == wg[p[r]])
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
                cons[ed] = 1;
            }
        }
        
        vs++;
        os = 0;
        for (int i = 0; i < n; i++) {
            if (find(i) != i) continue;
            if (vd[i] == vs) continue;
            to[0] = i;
            dfs(0);
        }

        vs |= 1;
        vs++;
        for (int i = 0; i < n; i++) {
            if (find(i) != i) continue;
            if (vd[i] == vs) continue;
            cst = cig = 0;
            mrk(i, -1);
            go(i, -1);
        }

        for (int _i = l; _i < r; _i++) {
            int ed = p[_i];
            join(to[ed], to[ed^1]);
        }

        l = r;
    }

    printf("%d\n", res);
    for (int i = 2; i < es; i += 2)
        printf("%d %d %d\n", to[i+1]+1, to[i]+1, rs[i]);
}
