#include <bits/stdc++.h>

using namespace std;

const int N = 107;
const int M = 407;
const int C = 2007;

struct res {
    int path;
    int length;
};

int chpts, cfpts, m, dst, en;
int hd[N], nx[M], pv[M], to[M], cf[M], wg[M], deg[M], es;
bool ch[N];
res memo[M][C];
int visi[M][C];

inline void bef (int ed, int nw) {
    nx[pv[ed]] = nw;
    pv[nw] = pv[ed];

    pv[ed] = nw;
    nx[nw] = ed;
}

void insert (int u, int nw) {
    if (!hd[u]) {
        hd[u] = nx[nw] = pv[nw] = nw;
    } else if (deg[nw] < deg[hd[u]]) {
        bef(hd[u], nw);
        hd[u] = nw;
    } else {
        int ed = nx[hd[u]];
        while (ed != hd[u] && deg[ed] < deg[nw])
            ed = nx[ed];
        bef(ed, nw);
    }
}

int main () {
    while (scanf("%d %d %d %d %d %d %d", &chpts, &m, &cfpts, &dst, to+1, &en, deg) && chpts+m+cfpts+dst+to[1]+en+deg[1]) {
        memset(hd, 0, sizeof hd);
        memset(ch, 0, sizeof ch);
        es = 2;
        wg[0] = wg[1] = 0;

        for (int i = 0; i < chpts; i++) {
            int a;
            scanf("%d", &a); a--;
            ch[a] = 1;
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d %d %d", to+es+1, to+es, deg+es, deg+es+1, wg+es);
            wg[es] = wg[es+1];
            cf[es] = cf[es+1] = 0;
            to[es]--; to[es+1]--;

            // tinha entendido errado, n precisa ordenar, mas vou deixar aq pq ta sexy...
            insert(to[es+1], es);
            insert(to[es], es+1);
            
            es += 2;
        }
        
        for (int i = 0; i < cfpts; i++) {
            int vt, ed, ds;
            scanf("%d %d %d", &vt, &ed, &ds);
            vt--;

            ed <<= 1;
            if (to[ed] == vt)
                ed++;

            cf[ed] = max(cf[ed], ds);
            cf[ed^1] = max(cf[ed^1], wg[es]-ds);
        }

        for (int i = 0; i < N; i++) {
            if (!hd[i])
                continue;
            printf("%d:", i+1);
            int ed = hd[i];
            do {
                printf(" %d(%d)", to[ed]+1, deg[ed]);
                ed = nx[ed];
            } while (ed != hd[i]);
            printf("\n");
        }
    }
}
