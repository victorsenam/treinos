#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 20;
const int M = 2e3+7;

int n, m;
int hd[N], to[M], nx[M], wg[M], rs[M], es;
int p[M];
int od[N], os;
int rt[N];
int vd[N], vs, usd[M];
int uf[N], wf[N];
queue<int> ign, spn;
int bri[M];

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

void printa (int ed) {
    debug("%d(%d,%d)(%d,%d) ", ed, to[ed^1]+1, to[ed]+1, find(to[ed^1])+1, find(to[ed])+1);
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
        printa(fr);
        debug("bridge\n");
        bri[(fr|1)-1] = 1;
    }

    return rt[u];
}

void go (int fr) {
    if (usd[(fr|1)-1] == vs)
        return;
    if (fr)
        usd[(fr|1)-1] = vs;

    printa(fr);

    int v = find(to[fr^1]);
    int u = find(to[fr]);
    int ref = (fr|1)-1;
    
    if (v == u) {
        debug("\n");
    } else if (fr && vd[u] == vs) {
        ign.push(ref);
        debug("ignore\n");
    } else {
        vd[u] = vs;
        if (fr) {
            spn.push(ref);
            debug("span\n");
        } else {
            debug("\n");
        }

        for (int ed = hd[u]; ed; ed = nx[ed]) {
            if ((ed|1) == (fr|1)) continue;
            if (bri[(ed|1)-1]) continue;

            go(ed);
        }
    }
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i <= n; i++) {
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

    int res = 0;
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
            }
        }
        
        debug("Find Bridges\n");
        vs++;
        os = 0;
        for (int i = 0; i < n; i++) {
            if (find(i) != i) continue;
            to[0] = i;
            to[1] = n;
            dfs(0);
        }

        debug("Classify\n");
        vs++;
        for (int i = 0; i < n; i++) {
            if (find(i) != i) continue;
            if (vd[i] == vs) continue;
            to[0] = i;
            to[1] = n;
            go(0);

            if (ign.size() > spn.size()) {
                while (spn.size()) {
                    int ed = spn.front();
                    spn.pop();
                    
                    res++;
                    rs[ed]--;
                }
                while (ign.size())
                    ign.pop();
            } else {
                while (ign.size()) {
                    int ed = ign.front();
                    ign.pop();
                    
                    res++;
                    rs[ed]++;
                }
                while (spn.size())
                    spn.pop();
            }
        }


        for (int _i = l; _i < r; _i++) {
            int ed = p[_i];
            join(to[ed],to[ed^1]);
        }
        l = r;
    }

    printf("%d\n", res);
    for (int i = 2; i < es; i += 2)
        printf("%d %d %d\n", to[i+1]+1, to[i]+1, rs[i]);
}
