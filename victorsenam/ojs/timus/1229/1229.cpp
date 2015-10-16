#include <bits/stdc++.h>

using namespace std;

const int W = 101;
const int N = W*W + 3;
const int M = N*4 + 3;

const int di[4] = {1, -1, 0, 0};
const int dj[4] = {0, 0, 1, -1};

// 0 |- w*h       nos
// w*h            src
// w*h+1          snk
int mat[W][W];
int hd[N], nx[M], to[M], cap[M], flx[M], hl[N], es;
int q[N], qi, qf;
int h, w;
int dist[N], visi[N], turn;
int src, snk;

inline void connect (int u, int v) {
    nx[es] = hd[u]; hd[u] = es; to[u] = v; cap[es] = 1; flx[es] = 0; es++;
    nx[es] = hd[v]; hd[v] = es; to[v] = u; cap[es] = 0; flx[es] = 0; es++;
}

inline bool isVal (int i, int j, int v) {
    if (i < 0 || i >= h)
        return 0;
    if (j < 0 || j >= w)
        return 0;
    return (mat[i][j] != v);
}

bool bfs () {
    turn++;
    visi[src] = turn;
    dist[src] = 0;
    qi = qf = 0;
    q[qf++] = src;

    while (qi < qf) {
        int att = q[qi++];

        for (int ed = hd[att]; ed != -1; ed = nx[ed]) {
            if (flx[ed] < cap[ed] && visi[to[ed]] != turn) {
                visi[to[ed]] = turn;
                dist[to[ed]] = dist[att] + 1;
                q[qf++] = to[ed];
            }
        }
    }

    for (int i = 0; i < w*h+2; i++)
        printf("%d ", visi[i]==turn?dist[i]:-1);
    printf("\n");
    return visi[snk] == turn;
}

int dfs (int u, int fl) {
    if (fl == 0)
        return 0;
    if (u == snk)
        return fl;

    for (int & ed = hl[u]; ed != -1; ed = nx[ed]) {
        if (dist[u] + 1 == dist[to[ed]]) {
            int loc = dfs(to[ed], min(fl, cap[ed]-flx[ed]));
            if (loc > 0) {
                flx[ed] += loc;
                flx[ed^1] -= loc;
                return loc;
            }
        }
    }
    return 0;
}

int dinic () {
    int res = 0;
    while (bfs()) {
        printf("lala\n");
        int loc = 0;
        for (int i = 0; i < h*w+2; i++)
            hl[i] = hd[i];
        do {
            loc = dfs(src, INT_MAX);
            res += loc;
        } while (loc > 0);
    }
    return res;
}

int main () {
    scanf("%d %d", &h, &w);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            scanf("%d", &mat[i][j]);
            hd[i*w + j] = -1;
        }
    }
    hd[w*h] = hd[w*h+1] = -1;

    src = w*h;
    snk = src+1;
    
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if ((i+j)%2) {
                connect(i*w+j, w*h);
                for (int k = 0; k < 4; k++)
                    if (isVal(i+di[k], j+dj[k], mat[i][j]))
                        connect(i*w+j, (i+di[k])*w+(j+dj[k]));
            } else
                connect(i*w+j, w*h+1);
        }
    }

    printf("%d\n", dinic());
}
