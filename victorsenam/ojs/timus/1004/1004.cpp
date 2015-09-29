#include <bits/stdc++.h>

using namespace std;

const int N = 101;
const int M = N*N;

struct vert {
    int v, w, p;

    bool operator < (const vert & a) const
    { return w > a.w; }
};

int nx[M], hd[M], hg[M], to[M];
int es;
int n, m;
int a, b, l;
int turn;
int visi[N];
int from[N];
int dist[N];
int rw;
int locw, locm;
deque<int> res;

void montaRes(vert aux) {
    res.clear();
    rw = dist[aux.p] + aux.w;
    int at = aux.p;
    while (from[at] != at) {
        res.push_back(at);
        at = from[at];
    }
    at = aux.v;
    while (from[at] != at) {
        res.push_front(at);
        at = from[at];
    }
}

void djs(int ini) {
    priority_queue<vert> pq;
    turn++;

    vert att;
    att.v = att.p = ini;
    att.w = 0;
    pq.push(att);

    while (!pq.empty()) {
        att = pq.top();
        pq.pop();

        if (visi[att.v] == turn) {
            if (from[att.v] == att.p)
                continue;
            if (dist[att.p] + att.w < rw)
                montaRes(att);
            continue;
        }

        from[att.v] = att.p;
        dist[att.v] = att.w;
        visi[att.v] = turn;

        for (int ed = hd[att.v]; ed != -1; ed = nx[ed]) {
            vert aux = att;
            aux.w += hg[ed];
            aux.v = to[ed];
            aux.p = att.v;

            if (aux.v == aux.p)
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
            printf("%d ", res.front());
            res.pop_front();
        }
        printf("\n");
    }
}
