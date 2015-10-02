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
int ord[N];
vert best[N];
int rw;
int locw, locm;
deque<int> res;

void montaRes(vert aux) {
    res.clear();
    rw = aux.w + best[aux.v].w;
    vert att = best[aux.p];
    while (att.p != att.v) {
        res.push_back(att.v);
        att = best[att.p];
    }
    att = best[aux.v];
    while (att.p != att.v) {
        res.push_front(att.v);
        att = best[att.p];
    }
    res.push_front(att.v);
}

void djs(int ini) {
    turn++;

    for (int i = 0; i < n; i++) {
        ord[i] = i;
        best[i].w = INT_MAX;
        best[i].v = best[i].p = i;
    }
    best[ini].w = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (best[ord[j]] < best[ord[i]])
                swap(ord[i], ord[j]);
        }
        vert att = best[ord[i]];

        if (att.w >= rw)
            break;

        for (int ed = hd[att.v]; ed != -1; ed = nx[ed]) {
            vert aux = att;
            aux.w += hg[ed];
            aux.v = to[ed];
            aux.p = att.v;

            if (aux.v == att.p)
                continue;
            
            if (aux < best[aux.v]) {
                best[aux.v] = aux;
            } else if (att.p != att.v && best[aux.v].w + aux.w < rw) {
                montaRes(aux);
            }
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
