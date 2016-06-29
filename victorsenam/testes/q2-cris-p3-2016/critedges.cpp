/*
 * Recebe um grafo conexo com pesos nas arestas
 * Retorna uma lista das arestas críticas do grafo (tais que a remoção causa um aumento no valor da MST)
 */

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

const int N = 2000006;

int uf[N], wf[N], hg[N];
int pai[N], lv[N];
int wg[N], ed[N][2], in[N];
int hd[N], to[N], nx[N], ref[N], es;
int p[N];
int crit[N];
int n, m;

int find (int i) {
    if (i == uf[i]) return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    if ( (i = find(i)) == (j = find(j)) ) return;
    if (wf[i] > wf[j]) swap(i, j);
    wf[j] += wf[i];
    uf[i] = j;
    if (lv[hg[i]] < lv[hg[j]])
        hg[j] = hg[i];
}

bool cmp_t (int i, int j) {
    return wg[i] < wg[j];
}

void dfs (int u, int fr) {
    pai[u] = ref[fr];
    lv[u] = lv[to[fr^1]]+1;
    uf[u] = u;
    wf[u] = 1;
    hg[u] = u;

    DEBUG("%d[%d] from %d: (%d,%d)[%d]\n", u, lv[u], pai[u], ed[pai[u]][0], ed[pai[u]][1], wg[pai[u]]);
    
    for (int ed = hd[u]; ed; ed = nx[ed])
        if ((ed|1) != (fr|1))
            dfs(to[ed], ed);
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &ed[i][0], &ed[i][1], &wg[i]);
        in[i] = 0;
        p[i] = i;
    }

    for (int i = 0; i < n; i++) {
        uf[i] = i;
        wf[i] = 1;
    }

    sort(p, p+m, cmp_t);

    DEBUG("MST edges\n");
    es = 2;
    for (int idx = 0; idx < m; idx++) {
        int i = p[idx];
        if (find(ed[i][0]) == find(ed[i][1]))
            continue;
        join(ed[i][0], ed[i][1]);

        nx[es] = hd[ed[i][0]]; to[es] = ed[i][1]; ref[es] = i; hd[ed[i][0]] = es++;
        nx[es] = hd[ed[i][1]]; to[es] = ed[i][0]; ref[es] = i; hd[ed[i][1]] = es++;
        DEBUG("%d: (%d,%d)[%d]\n", i, ed[i][0], ed[i][1], wg[i]);
        in[i] = crit[i] = 1;
    }

    lv[0] = -1;
    DEBUG("MST vertices\n");
    dfs(0, 0);

    DEBUG("Cycles\n");
    for (int idx = 0; idx < m; idx++) {
        int i = p[idx];
        
        if (in[i]) continue;

        DEBUG("%d: (%d,%d)[%d]\n", i, ed[i][0], ed[i][1], wg[i]);

        int a = hg[find(ed[i][0])];
        int b = hg[find(ed[i][1])];

        while (a != b) {
            DEBUG("%d[%d] %d[%d]\n", a, lv[a], b, lv[b]);
            if (lv[a] < lv[b]) swap(a, b);

            if (wg[pai[a]] == wg[i])
                crit[pai[a]] = 0;
            
            join(ed[pai[a]][0], ed[pai[a]][1]);
            a = hg[find(a)];
            b = hg[find(b)];
        }
    }

    DEBUG("Answer\n");
    for (int i = 0; i < m; i++)
        if (crit[i])
            printf("%d %d\n", ed[i][0], ed[i][1]);
}
