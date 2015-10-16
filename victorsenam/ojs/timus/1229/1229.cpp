// INCOMPLETO

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
    nx[es] = hd[u]; hd[u] = es; to[es] = v; cap[es] = 1; flx[es] = 0; es++;
    nx[es] = hd[v]; hd[v] = es; to[es] = u; cap[es] = 0; flx[es] = 0; es++;
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

    return visi[snk] == turn;
}

int dfs (int u, int fl) {
    if (u == snk)
        return fl;

    for (int & ed = hl[u]; ed != -1; ed = nx[ed]) {
        if (flx[ed] < cap[ed] && dist[u] + 1 == dist[to[ed]]) {
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
            if ((i+j)&1) {
                connect(src, i*w+j);
                for (int k = 0; k < 4; k++)
                    if (isVal(i+di[k], j+dj[k], mat[i][j]))
                        connect(i*w+j, (i+di[k])*w+(j+dj[k]));
            } else {
                connect(i*w+j, snk);
            }
        }
    }

    int ans = dinic();
    if (ans == w*h/2) {
        int rs = 1;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if ((i+j)&1)
                    continue;
                for (int ed = hd[i*w+j]; ed != -1; ed = nx[ed]) {
                    if (to[ed] >= w*h || flx[ed] == 0)
                        continue;

                    mat[i][j] = mat[to[ed]/w][to[ed]%w] = rs++;
                }
            }
        }
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++)
                printf("%d ", mat[i][j]);
            printf("\n");
        }
    } else {
        printf("-1\n");
    }
}
