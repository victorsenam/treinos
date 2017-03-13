#include <bits/stdc++.h>
//#define debug(...) {fdebug(stdout, __VA_ARGS__);}
#define debug(...) {}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;
const int K = 22;
const int DEAD = INT_MAX;

int n, qs;
int hd[N], nx[2*N], to[2*N], wg[2*N], es; // graph
int pr[N], sz[N]; // rooting
int c_pr[N][K], c_ds[N][K];
short c_de[N]; // centroid

struct node {
    int time;
    int u;
    short k;
    int val;

    inline bool operator < (const node & ot) const {
        if (val != ot.val)
            return val < ot.val;
        return u < ot.u;
    }
};

node aux[4];
int ls[N][K][4];

struct heap {
    priority_queue<node> pq;
    int currn;
    short ty;

    int get (int q) {
        debug("get %d from %d[%d]\n", q, currn, ty);
        int val = 0;
        int i = 0;
        while (val != DEAD && i < q) {
            if (pq.empty()) {
                val = DEAD;
            } else {
                aux[i] = pq.top();
                pq.pop();
                debug("\t found %d(%d) time %d/%d ", aux[i].val, aux[i].u, aux[i].time, ls[aux[i].u][aux[i].k][ty]);
                if (aux[i].time == ls[aux[i].u][aux[i].k][ty]) {
                    val += aux[i].val;      
                    i++;
                } else {
                    debug("SKIP\n");
                }
                debug("\n");
            }
        }
        for (int j = 0; j < i; j++) {
            pq.push(aux[j]);
        }
        if (val == DEAD) {
            debug("VAL: DEAD\n");
        } else {
            debug("VAL: %d\n", val);
        }
        return val;
    }

    inline void add (int u, short k, int val) {
        ls[u][k][ty]++;
        if (val == DEAD) return;
        aux[0].time = ls[u][k][ty];
        aux[0].k = k;
        aux[0].u = u;
        aux[0].val = val;
        debug("add %d(%d) on %d[%d] time %d\n", val, u, currn, ty, ls[u][k][ty]);
        pq.push(aux[0]);
    }

    inline void remove (int u, short k) {
        //debug("remove (%d) from %d[%d]\n", u, currn, ty);
        ls[u][k][ty]++;
    }
};

heap her[N], par[N], res;
int cr[N]; // info

int root (int u, int p) {
    sz[u] = 1;
    pr[u] = p;

    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (to[ed] == p || c_de[to[ed]]) continue;
        sz[u] += root(to[ed], u);
    }

    return sz[u];
}

void dfs (int u, int p, int w, int r) {
    int d = c_de[r];

    c_pr[u][d] = p;
    c_ds[u][d] = w;

    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (c_de[to[ed]] || to[ed] == p) continue;
        dfs(to[ed], u, w + wg[ed], r);
    }
}

void build (int fr, int depth) {
    int u = to[fr];
    int p = to[fr^1];
    int w = wg[fr];

    int size = root(u, u);

    int v = -1;
    while (v != u) {
        v = u;

        for (int ed = hd[u]; ed; ed = nx[ed]) {
            if (c_de[to[ed]] || pr[u] == to[ed] || sz[to[ed]] + sz[to[ed]] <= size) continue;
            u = to[ed];
            break;
        }
    }

    c_de[u] = depth;
    dfs(u, u, 0, u);

    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (c_de[to[ed]]) continue;
        build(ed, depth + 1);
    }
}

void upd (int u) {
    debug("UPDATE %d\n", u);
    int val;
    for (short k = c_de[u]-1; k > 0; k--) {
        debug("level %d\n", k);
        int p = c_pr[u][k];
        int v = c_pr[u][k+1];
        int w = c_ds[u][k];

        //res.remove(p, 0);
        //her[p].remove(v, k);

        if (cr[u]) {
            par[v].remove(u, k);
        } else {
            par[v].add(u, k, w);
        }

        her[p].add(v, k, par[v].get(1));
        res.add(p, 0, her[p].get(2));
    }

    debug("single\n");
    //res.remove(u, 0);
    
    if (cr[u]) {
        her[u].remove(u, 0);
        her[u].remove(n, K-1);
    } else {
        her[u].add(u, 0, 0);
        her[u].add(n, K-1, 0);
    }

    res.add(u, 0, her[u].get(2));

    cr[u] = !cr[u];
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < N; i++) {
        her[i].ty = 0;
        par[i].ty = 1;
        her[i].currn = par[i].currn = i;
    }
    res.ty = 2;
    res.currn = 0;

    es = 2;
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d %d", &a, &b, &wg[es]);
        a--; b--;

        wg[es+1] = wg[es];
        to[es] = b; nx[es] = hd[a]; hd[a] = es++;
        to[es] = a; nx[es] = hd[b]; hd[b] = es++;
    }

    build(0, 1);
    for (int i = 0; i < n; i++)
        upd(i);

    scanf("%d", &qs);
    while (qs--) {
        char c;
        scanf(" %c", &c);

        if (c == 'A') {
            int loc = res.get(1);
            if (loc == DEAD)
                printf("They have disappeared.\n");
            else
                printf("%d\n", loc);
        } else {
            int a;
            scanf("%d", &a);
            upd(a-1);
        }
    }
}
