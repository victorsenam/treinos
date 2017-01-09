#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;

const int N = 1e3+7;
const int mv[4][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
};

char mat[N][N];
int n, m;
int dist[5][N][N];
int visi[5][N][N];

struct node {
    int i; 
    int j;
    int d;

    bool operator < (const node & ot) const {
        return d > ot.d;
    }
};

int bfs (int k) {
    priority_queue<node> qu;
    node aux;
    aux.d = 0;

    for (aux.i = 0; aux.i < n; aux.i++)
        for (aux.j = 0; aux.j < m; aux.j++)
            if (mat[aux.i][aux.j] - '1' == k) {
                qu.push(aux);
                dist[k][aux.i][aux.j] = 0;
            } else {
                dist[k][aux.i][aux.j] = 1e7;
            }

    while (qu.size()) {
        node att = qu.top();
        qu.pop();

        if (visi[k][att.i][att.j])
            continue;
        visi[k][att.i][att.j] = 1;
            

        for (int d = 0; d < 4; d++) {
            node nxt = att;
            nxt.i += mv[d][0];
            nxt.j += mv[d][1];

            if (nxt.i < 0 || nxt.i >= n ||
                nxt.j < 0 || nxt.j >= m ||
                mat[nxt.i][nxt.j] == '#')
                continue;

            nxt.d += (mat[nxt.i][nxt.j] == '.');

            if (nxt.d >= dist[k][nxt.i][nxt.j]) {
                continue;
            }
            dist[k][nxt.i][nxt.j] = nxt.d;
            qu.push(nxt);
        }
    }
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        scanf(" %s", mat[i]);

    for (int k = 0; k < 3; k++)
        bfs(k);

    int res = 1e7;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int loc = 0;
            for (int k = 0; k < 3; k++) {
                loc += dist[k][i][j];
            }
            if (mat[i][j] == '.')
                loc -= 2;

            res = min(res, loc);
        }
    }

    if (res == 1e7)
        res = -1;
    printf("%d\n", res);
}
