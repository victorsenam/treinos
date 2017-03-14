#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e6+7;
const int K = 30;

int n, q;
int hd[N], nx[N], to[N], wg[N], es;

int size[N], pr[N];
int c_ds[K][N], c_pr[K][N], c_de[N];

int cr[N];
multiset<int> hr[N], ch[N], tt;
multiset<int>::reverse_iterator it;

int dfs (int u, int p, int curr) {
    size[u] = 1;
    pr[u] = p;
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (c_de[to[ed]] || to[ed] == p) continue;
        size[u] += dfs(to[ed], u, curr);
    }

    //debug("%d size %d\n", u+1, size[u]);
    return size[u];
}

void sds (int u, int v, int w, int p) {
    c_pr[c_de[v]][u] = v;
    c_ds[c_de[v]][u] = w;

    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (c_de[to[ed]] || to[ed] == p) continue;
        sds(to[ed], v, w + wg[ed], u);
    }
}

void build (int fr) {
    int u = to[fr];
    int p = to[fr^1];
    int w = wg[fr];
    
    //debug("root from %d\n", u+1);
    int sz = dfs(u, p, p);

    int v = n;
    while (v != u) {
        v = u;
        for (int ed = hd[u]; ed; ed = nx[ed]) {
            if (c_de[to[ed]] || pr[u] == to[ed] || size[to[ed]] + size[to[ed]] <= sz) continue;
            u = to[ed];
            break;
        }
    }

    c_de[u] = c_de[p] + 1;
    //debug("centroid %d from %d depth %d\n", u+1, p+1, c_de[u]);
    sds(u, u, 0, u);

    for (int ed = hd[u]; ed; ed = nx[ed]) {
        if (c_de[to[ed]]) continue;
        build(ed);
    }
}

void upd (int u) {
    for (int k = c_de[u] - 1; k > 0; k--) {
        // tira o pai do total
        int val = 0;
        it = ch[c_pr[k][u]].rbegin();
        if (it != ch[c_pr[k][u]].rend()) {
            val += *it;
            ++it;
            if (it != ch[c_pr[k][u]].rend())
                val += *it;
            tt.erase(tt.find(val));
        }

        // me tira do pai
        it = hr[c_pr[k+1][u]].rbegin();
        if (it != hr[c_pr[k+1][u]].rend()) {
            ch[c_pr[k][u]].erase(ch[c_pr[k][u]].find(*it));
        }


        if (cr[u]) {
            // tira valor deses vertice de mim
            hr[c_pr[k+1][u]].erase(hr[c_pr[k+1][u]].find(c_ds[k][u]));
        } else {
            // coloca o valor desse vertice em mim
            hr[c_pr[k+1][u]].insert(c_ds[k][u]);
        }

        // me coloca no pai
        it = hr[c_pr[k+1][u]].rbegin();
        if (it != hr[c_pr[k+1][u]].rend())
            ch[c_pr[k][u]].insert(*it);
        
        val = 0;
        it = ch[c_pr[k][u]].rbegin();
        if (it != ch[c_pr[k][u]].rend()) {
            val += *it;
            ++it;
            if (it != ch[c_pr[k][u]].rend())
                val += *it;
            tt.insert(val);
        }
    }
    cr[u] = !cr[u];
}

int main () {
    scanf("%d", &n);

    es = 2;
    for (int i = 1; i < n; i++) {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        a--; b--;
        
        wg[es] = w; to[es] = b; nx[es] = hd[a]; hd[a] = es++;
        wg[es] = w; to[es] = a; nx[es] = hd[b]; hd[b] = es++;
    }

    build(0);

    for (int i = 0; i < n; i++)
        upd(i);

    scanf("%d", &q);
    while (q--) {
        char c;
        int u;

        scanf(" %c", &c);

        if (c == 'A') {
            if (tt.empty())
                printf("They have disappeared.\n");
            else
                printf("%d\n", *(tt.rend()));
        } else {
            scanf("%d", &u);
            u--;
            upd(u);
        }
    }
}
