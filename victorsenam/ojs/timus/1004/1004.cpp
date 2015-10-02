// Incompleto
// TODO: Tirar a Pq do Dijkstra

#include <bits/stdc++.h>

using namespace std;

const int N = 101;
const int M = N*N;

struct vert {
    int v, w, p;

    bool operator < (const vert & a) const
    { return w < a.w; }
};

int nx[M], hd[M], hg[M], to[M];
int es;
int n, m;
int a, b, l;
int turn;
vert best[N];
int rw;
int locw, locm;
deque<int> res;

void montaRes(vert aux) {
    res.clear();
    rw = aux.w + best[aux.v].w;
}

void djs(int ini) {
    priority_queue<vert> pq;
    turn++;

    vert att;
    att.v = att.p = ini;
    att.w = 0;
    pq.push(att);

    for (int i = n; i >= 1; i--) {
        att = best[ord[0]];
        for (int j = 1; i < n; j++)
            att = min(att, best[ord[j]]);

        if (att.w >= rw)
            break;

        for (int ed = hd[att.v]; ed != -1; ed = nx[ed]) {
            vert aux = att;
            aux.w += hg[ed];
            aux.v = to[ed];
            aux.p = att.v;

            if (aux.v == att.p)
                continue;
            
            pq.push(aux);
        }
    }
}

int main () {
    while (scanf("%d %d", &n, &m) != EOF && n != -1) {
        es = 0;
        for (int i = 0; i < n; i++)
            hd[i] = -1;

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &a, &b, &l);
            a--; b--;
            nx[es] = hd[a]; hg[es] = l; hd[a] = es; to[es++] = b;
            nx[es] = hd[b]; hg[es] = l; hd[b] = es; to[es++] = a;
        }

        rw = INT_MAX;
        for (int i = 0; i < n; i++)
            djs(i);

        if (rw == INT_MAX) {
            printf("No solution.\n");
            continue;
        }
        while (!res.empty()) {
            printf("%d ", res.front()+1);
            res.pop_front();
        }
        printf("\n");
    }
}
