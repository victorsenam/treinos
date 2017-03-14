#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1e3+7;
const int mv[4][2] = {
    {0, 1},
    {1, 0},
    {-1, 0},
    {0, -1}
};

struct node {
    int i, j, d;

    node (int a, int b) : i(a), j(b), d(0) {};
    node () {};
};

int t;
int n, m;
char mat[N][N];
int dist[2][N][N];
node qu[2][N*N], fini;
int qi[2], qf[2];

bool isVal (node u, int k) {
    if (u.i < 0 || u.j < 0 || u.i >= n || u.j >= m) return 0;
    if (mat[u.i][u.j] == '#') return 0;
    for (int l = 0; l <= k; l++)
        if (dist[l][u.i][u.j] <= u.d)
            return 0;
    return 1;
}

bool bfs (int t) {
    while (qi[t] < qf[t]) {
        node att = qu[t][qi[t]++];

        for (int k = 0; k < 4; k++) {
            node nx = att;
            nx.i += mv[k][0];
            nx.j += mv[k][1];
            nx.d++;

            if (!isVal(nx, t)) continue;
            dist[t][nx.i][nx.j] = nx.d;
            qu[t][qf[t]++] = nx;
        }
    }

    return dist[t][fini.i][fini.j] < INT_MAX;
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);

        qi[0] = qf[0] = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf(" %c", &mat[i][j]);
                dist[0][i][j] = dist[1][i][j] = INT_MAX;
                if (mat[i][j] == 'F') {
                    qu[0][qf[0]++] = node(i, j);
                    dist[0][i][j] = 0;
                } else if (mat[i][j] == 'S') {
                    qu[1][qf[1]++] = node(i, j);
                    dist[1][i][j] = 0;
                } else if (mat[i][j] == 'E') {
                    fini.i = i;
                    fini.j = j;
                }
            }
        }

        bfs(0);
        if (bfs(1))
            printf("Y\n");
        else
            printf("N\n");
    }
}
