#include <bits/stdc++.h>

using namespace std;

const int N = 100007;
const int M = 400007;


int hd[N], nx[M], to[M], es;
int uf[N], wf[N];
int n, m, k;
bool sp[N];
int dist[N];
int src[N];
int visi[N];
int turn;
int qu[N], qi, qf;
int s, t;

int find (int i) {
    if (uf[i] == i)
        return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    i = find(i); j = find(j);
    if (i == j)
        return;
    if (wf[i] < wf[j])
        swap(i, j);
    wf[i] += wf[j];
    uf[j] = uf[i];
}
bool solve (int q) {
    qi = qf = 0;
    for (int i = 0; i < n; i++) {
        uf[i] = i;
        wf[i] = 1;
        if (sp[i]) {
            qu[qf++] = i;
            dist[i] = 0;
            visi[i] = turn;
            src[i] = i;
        }
    }

    while (qi < qf && find(s) != find(t)) {
        int u = qu[qi++];

        for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
            if (visi[to[ed]] != turn) {
                visi[to[ed]] = turn;
                src[to[ed]] = src[u];
                dist[to[ed]] = dist[u];
                qu[qf++] = to[ed];
            } else if (dist[to[ed]] + dist[u] + 1 <= q) {
                join(u, to[ed]);
            }
        }
    }
    
    return (find(s) == find(t));
}

int main () {
    memset(hd, -1, sizeof hd);
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < k; i++) {
        int a;
        scanf("%d", &a);
        sp[a-1] = 1;
    }
    
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        nx[es] = hd[a]; hd[a] = es; to[es] = b; es++;
        nx[es] = hd[b]; hd[b] = es; to[es] = a; es++;
    }

    scanf("%d %d", &s, &t);
    s--; t--;

    int lo = 0;
    int hi = n+1;

    while (lo < hi) {
        int q = (lo+hi)/2;
        printf("%d %d %d\n", q, lo, hi);

        turn++;

        if (solve(q))
            hi = q;
        else
            lo = q+1;
    }

    if (lo == n+1)
        printf("-1\n");
    else
        printf("%d\n", lo);
}
