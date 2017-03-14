#include <bits/stdc++.h>

// #define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define DEBUG(args...) { printf("%3d| ", __LINE__); printf(args); }
#else
#define DEBUG(args...) {}
#endif

using namespace std;

const int N = 100007;
const int K = 24;

int f[N], n, q;
int a, b;
int v_cyc[N], p_cyc[N], e_cyc[N], v_lca[N], v_cmp[N], turn;
int dist[N];
int lca[N][K];
int uf[N], wf[N];

int find (int i) {
    if (uf[i] == i) return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    if ((i = find(i)) == (j = find(j))) return;
    if (wf[i] < wf[j]) swap(i, j);
    wf[i] += wf[j];
    uf[j] = i;
}

int dfs_cyc (int i) {
    if (v_cyc[i] == turn) {
        p_cyc[i] = 0; e_cyc[i] = i;
        return i;
    }
    v_cyc[i] = turn;
    e_cyc[i] = dfs_cyc(f[i]);
    if (e_cyc[i] == -1) p_cyc[i] = -1;
    if (e_cyc[i] == -1 || e_cyc[i] == i) return -1;

    p_cyc[i] = p_cyc[f[i]]+1;
    return e_cyc[i];
}

int dfs_lca (int i) {
    if (v_lca[i] == turn) return dist[i];
    v_lca[i] = turn;
    if (e_cyc[i] != -1) {
        dist[i] = 0;
        for (int k = 0; k < K; k++)
            lca[i][k] = i;
    } else {
        dist[i] = dfs_lca(f[i]) + 1;
        lca[i][0] = f[i];
        for (int k = 1; k < K; k++)
            lca[i][k] = lca[f[i]][k-1];
    }
    return dist[i];
}

int diff (int a, int b) {
    if (a == b) return 0;

    int siz = p_cyc[f[e_cyc[a]]]+1;
    //DEBUG("size of %d cyc : %d\n", e_cyc[a], siz);

    return min( (p_cyc[a]-p_cyc[b]+siz)%siz, (p_cyc[b]-p_cyc[a]+siz)%siz );
}

int query_lca (int a, int b) {
    int res = dist[a] + dist[b];
    if (dist[b] > dist[a]) swap(a,b);
    int tp = K-1;
    while (dist[a] > dist[b]) {
        while (tp && dist[lca[a][tp]] < dist[b]) tp--;
 //       DEBUG("%d %d[%d]->%d[%d] to %d[%d]\n", tp, a, dist[a], lca[a][tp], dist[lca[a][tp]], b, dist[b]);
        a = lca[a][tp];
    }
    tp = K-1;
    while (dist[a] && a != b) {
        while (tp && (!dist[lca[a][tp]] || lca[a][tp] == lca[b][tp])) tp--;
        a = lca[a][tp];
        b = lca[b][tp];
    }
    res -= 2*dist[a];
    res += diff(a,b);
    return res;
}

int main () {
    while (scanf("%d", &n) != EOF) {
        ++turn;
        for (int i = 0; i < n; i++) {
            uf[i] = i;
            wf[i] = 1;
        }

        for (int i = 0; i < n; i++) {
            scanf("%d", f+i);
            f[i]--;
            join(i, f[i]);
        }

        for (int i = 0; i < n; i++) {
            if (v_cyc[i] == turn);
            else if (v_cmp[find(i)] == turn) {
                //DEBUG("ignore %d\n", i);
                e_cyc[i] = -1;
                p_cyc[i] = 0;
            } else {
                //DEBUG("call from %d\n", i);
                dfs_cyc(i);
                v_cmp[find(i)] = turn;
            }

            //DEBUG("%d[%d] cycles in %d at %d\n", i, find(i), p_cyc[i], e_cyc[i]);
        }

        for (int i = 0; i < n; i++) {
            //DEBUG("%d[%d] ", e_cyc[i], p_cyc[i]);
            dfs_lca(i);
 //           DEBUG("%d : %d\n", i, dist[i]);
        }
        scanf("%d", &q);

        for (int qr = 0; qr < q; qr++) {
            scanf("%d %d", &a, &b);
            a--; b--;

            if (find(a) != find(b))
                printf("-1\n");
            else
                printf("%d\n", query_lca(a, b));
        }
    }
}
