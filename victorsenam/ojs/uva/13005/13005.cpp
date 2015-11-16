#include <bits/stdc++.h>

using namespace std;

const int N = 400;
const int M = 1000000;

int he[N], hd[N], to[M], nx[M], fl[M], cp[M], es;
int src, snk;
int n, qs, m;
bool comp;
int q[N], qi, qf;
int dist[N], visi[N], turn;

void connect(int a, int b, int c) {
    nx[es] = hd[a]; hd[a] = es; to[es] = b; fl[es] = 0; cp[es] = c; es++;
    nx[es] = hd[b]; hd[b] = es; to[es] = a; fl[es] = 0; cp[es] = 0; es++;
}

int bfs() {
    qi = qf = 0;
    q[qf++] = snk;
    turn++;

    for (int i = 0; i <= snk; i++)
        dist[i] = INT_MAX;

    dist[snk] = 0;

    while (qi < qf) {
        int u = q[qi++];
        if (visi[u] == turn)
            continue;
        visi[u] = turn;

        for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
            if (visi[to[ed]] == turn || dist[to[ed]] <= dist[u]+1 || fl[ed^1] >= cp[ed^1])
                continue;
            dist[to[ed]] = min(dist[to[ed]], dist[u]+1);
            q[qf++] = to[ed];
        }
    }

    return dist[src];
}

int dfs(int u, int r) {
    if (r == 0)
        return 0;

    if (u == snk)
        return r;

    for (int & ed = he[u]; ed != -1; ed = nx[ed]) {
        if (dist[u] != dist[to[ed]] + 1 || cp[ed] <= fl[ed])
            continue;

        int loc = dfs(to[ed], min(r, cp[ed]-fl[ed]));
        if (loc) {
            fl[ed] += loc;
            fl[ed^1] -= loc;
         //   printf("%d ", u);
            return loc;
        }
    }
    return 0;
}

int dinic () {
    int res = 0;
    while (bfs() < INT_MAX) {
        for (int i = 0; i <= snk; i++)
            he[i] = hd[i];
        // printf("============ \n");
        while (int loc = dfs(src, INT_MAX)) {
           // printf("%d \n", loc);
            res += loc;
        }
    }
    return res;
}

int main () {
    while (scanf("%d %d", &n, &qs) != EOF) {
        memset(hd, -1, sizeof hd);

        src = n+n;
        snk = src+1;
        comp = 0;
        
        for (int i = 0; i < n; i++) {
            scanf("%d", &m);
            if (n == m)
                comp = 1;

            connect(src, i, 1);

            for (int j = 0; j < m; j++) {
                int a;
                scanf("%d", &a);
                a--;

                connect(i, n+a, 1);
            }
        }


        for (int i = 0; i < n; i++)
            connect(n+i, snk, 0);

        for (int i = 0; i < qs; i++) {
            scanf("%d", &m);
            if (m == 0) {
                if (comp)
                    printf("N\n");
                else
                    printf("Y\n");
                continue;
            }

            if (i) {
                memset(fl, 0, sizeof fl);

                for (int j = 0; j < n; j++) 
                    cp[hd[n+j]] = 0;
            }

            for (int j = 0; j < m; j++) {
                int a;
                scanf("%d", &a);
                a--;
                
                cp[hd[n+a]] = 1;
            }

            int val = dinic();
 //           printf("%d\n", val);
            if (val == m)
                printf("Y\n");
            else
                printf("N\n");
        }
    }    
}
