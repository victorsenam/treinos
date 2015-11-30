// INCOMPLETO

#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 62;
const int K = 1003;
const int Q = 100007;

struct node {
    int u;
    int d;
    int r;
    bool operator <(const node & ot) const {
        if (d == ot.d)
            return r > ot.r;
        return d > ot.d;
    }
};

int adj[N][N][N];
int dist[N][K];
int visi[N][K];
int turn;
int n, m, r;
int a[Q], b[Q], k[Q], p[Q], ans[Q];

bool q_cmp (int i, int j) {
    if (a[i] == a[j])
        return k[i] > k[j];
    return a[i] < a[j];
}

void floyd (int c) {
    for (int s = 0; s < n; s++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adj[c][i][j] = min(adj[c][i][j], adj[c][i][s] + adj[c][s][j]);
}

void djs (int src, int k) {
    priority_queue<node> pq;

    for (int i = 0; i < n; i++) {
        node aux;
        aux.u = i;
        aux.r = 0;
        aux.d = adj[0][src][i];

        for (int c = 1; c < m; c++) {
            aux.d = min(aux.d, adj[c][src][i]);
            pq.push(aux);
        }
    }

    while (!pq.empty()) {
        node att = pq.top();
        pq.pop();

        if (visi[att.u][att.r] == turn)
            continue;
        visi[att.u][att.r] = turn;
        dist[att.u][att.r] = att.d;

        if (att.r == k)
            continue;

        for (int c = 0; c < m; c++) {
            for (int i = 0; i < n; i++) {
                node nxt = att;
                nxt.u = i;
                nxt.d += adj[c][att.u][i];
                nxt.r++;

                if (visi[nxt.u][nxt.r] == turn)
                    continue;

                pq.push(nxt);
            }
        }
    }
}

int main () {
    scanf("%d %d %d", &n, &m, &r);

    for (int c = 0; c < m; c++) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &adj[c][i][j]);
        floyd(c);
    }

    for (int q = 0; q < r; q++) {
        scanf("%d %d %d", a+q, b+q, k+q);
        p[q] = q;
    }

    sort(p, p+r, q_cmp);

    for (int q = 0; q < r; q++) {
        turn++;
        if (!q || a[p[q]] != a[p[q-1]])
            djs(a[p[q]], k[p[q]]);

        ans[p[q]] = dist[b[p[q]]][k[p[q]]];
    }

    for (int i = 0; i < r; i++)
        printf("%d\n", ans[i]);
}
