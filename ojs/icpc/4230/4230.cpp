#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define lld I64d
#define DEBUG(...) {}
#endif

const int N = 207;
const int inf = 10000000;

const int mv[4][2] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
};

char mat[N][N];
int dis[N][N];
int n, m;
int qu[N], qi, qf;
int ini;
int p[2], q[2];
int tot;
int sum;
int qt;

inline int ps (int i, int j) {
    return i*m + j;
}

inline bool isval (int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= m || mat[i][j] == 'X')
        return 0;
    return 1;
}

int main () {
    while (scanf("%d %d", &n, &m) != EOF && n) {
        qi = qf = 0;
        tot = n*m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf(" %c", &mat[i][j]);
                dis[i][j] = inf;
                if (mat[i][j] == 'Y') {
                    ini = ps(i, j);
                } else if (mat[i][j] == 'E') {
                    qu[qf++] = ps(i, j);
                    dis[i][j] = 0;
                } else if (mat[i][j] == 'X') {
                    tot--;
                }
            }
        }
        int dmax = 0;

        while (qi < qf) {
            q[0] = qu[qi]/m;
            q[1] = qu[qi]%m;
            qi++;

            for (int k = 0; k < 4; k++) {
                for (int l = 0; l < 2; l++)
                    p[l] = q[l] + mv[k][l];
                if (!isval(p[0], p[1]))
                    continue;

                if (dis[p[0]][p[1]] == inf) {
                    dis[p[0]][p[1]] = dis[q[0]][q[1]] + 1;

                    qu[qf++] = ps(p[0], p[1]);
                    dmax = max(dmax, dis[p[0]][p[1]]);
                }
            }
        }

        double res = dis[ini/m][ini%m];
        dmax = max(int(res), dmax);
        for (int d = dis[ini/m][ini%m]; d <= dmax; d++) {
            sum = 0;
            qt = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (dis[i][j] <= d) {
                        sum += dis[i][j];
                        qt++;
                    }
                }
            }
            
            res = min(res, ((double(sum)/double(tot)) + 1. - (double(qt)/double(tot)))/(double(qt)/double(tot)) );
        }

        printf("%.3lf\n", res);
    }
}
