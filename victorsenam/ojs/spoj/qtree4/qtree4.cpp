#include <bits/stdc++.h>
//#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#define debug(...) {}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 4e6+7;
const int K = 30;

int n, qs;
int hd[N], nx[N], to[N], wg[N], es; // graph
int pr[N], sz[N]; // rooting
int c_pr[K][N], c_ds[K][N], c_de[N]; // centroid

multiset<int> fher[N], fpar[N], res; // info
multiset<int>::reverse_iterator it;
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

    c_pr[d][u] = p;
    c_ds[d][u] = w;

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
    int val;
    debug("upd %d\n", u+1);
    for (int k = c_de[u]-1; k > 0; k--) {
        int p = c_pr[k][u];
        int v = c_pr[k+1][u];
        int w = c_ds[k][u];

        val = 0;
        if (fher[p].size() >= 2) {
            it = fher[p].rbegin();
            val += *it;
            ++it;
            val += *it;

            debug("tirando %d do res\n", val);
            res.erase(res.find(val));
        }

        if (fpar[v].size() >= 1) {
            it = fpar[v].rbegin();

            debug("tirando %d de validos de %d\n", *it, p+1);
            fher[p].erase(fher[p].find(*it));
        }

        if (cr[u]) {
            fpar[v].erase(fpar[v].find(w));
            debug("tirando %d de %d\n", w, v+1);
        } else {
            fpar[v].insert(w);
            debug("colocando %d em %d\n", w, v+1);
        }

        if (fpar[v].size() >= 1) {
            it = fpar[v].rbegin();
            debug("colocando %d em validos de %d\n", *it, p+1);
            fher[p].insert(*it);
        }

        val = 0;
        if (fher[p].size() >= 2) {
            it = fher[p].rbegin();
            val += *it;
            ++it;
            val += *it;

            debug("colocando %d em res\n", val);
            res.insert(val);
        }
    }

    val = 0;
    if (fher[u].size() >= 2) {
        it = fher[u].rbegin();
        val += *it;
        ++it;
        val += *it;

        debug("tirando %d do res\n", val);
        res.erase(res.find(val));
    }

    if (cr[u]) {
        debug("tirando %d de validos de %d\n", 0, u+1);
        fher[u].erase(fher[u].find(0));
        fher[u].erase(fher[u].find(0));
    } else {
        debug("colocando %d em validos de %d\n", 0, u+1);
        fher[u].insert(0);
        fher[u].insert(0);
    }

    val = 0;
    if (fher[u].size() >= 2) {
        it = fher[u].rbegin();
        val += *it;
        ++it;
        val += *it;

        debug("colocando %d em res\n", val);
        res.insert(val);
    }

    cr[u] = !cr[u];
}

int main () {
    scanf("%d", &n);

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
            if (res.size())
                printf("%d\n", *res.rbegin());
            else
                printf("They have disappeared.\n");
        } else {
            int a;
            scanf("%d", &a);
            upd(a-1);
        }
    }
}
