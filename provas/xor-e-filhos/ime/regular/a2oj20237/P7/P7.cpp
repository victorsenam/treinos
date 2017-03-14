#include <bits/stdc++.h>

using namespace std;

const int N = 32;
typedef int num;

const int mi[4] = {1, -1, 0, 0};
const int mj[4] = {0, 0, 1, -1};

num dist[N][N];
int ni, nj;
int toi[N][N], toj[N][N];
int grave[N][N];
int gs, hs;
int a, b;
num tele[N][N];
int n, m;
int aux;

bool canGo (int i, int j) {
    if (i < 0 || i >= n)
        return 0;
    if (j < 0 || j >= m)
        return 0;
    if (grave[i][j] == 1)
        return 0;
    return 1;
}

int main () {
    while (scanf("%d %d", &m, &n) != EOF && (n || m)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                dist[i][j] = INT_MAX;
                toi[i][j] = i;
                toj[i][j] = j;
                grave[i][j] = 0;
                tele[i][j] = 0;
            }
        }

        scanf("%d", &gs);
        for (int i = 0; i < gs; i++) {
            scanf("%d %d", &a, &b);
            swap(a,b);
            grave[a][b] = 1;
        }

        scanf("%d", &hs);
        for (int i = 0; i < hs; i++) {
            scanf("%d %d", &a, &b);
            swap(a,b);
            scanf("%d %d %d", &toj[a][b], &toi[a][b], &tele[a][b]);
            grave[a][b] = 2;
        }

        dist[0][0] = 0;

        bool chn = 0;
/*
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                printf("%d ", dist[i][j]);
            printf("\n");
        }
*/
        for (int r = 0; r <= n*m+1; r++) {
            chn = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (i == n-1 && j == m-1)
                        continue;
                    if (dist[i][j] == INT_MAX)
                        continue;

                    if (grave[i][j] == 2) {
                        ni = toi[i][j];
                        nj = toj[i][j];

                        aux = dist[ni][nj];
                        dist[ni][nj] = min(dist[i][j] + tele[i][j], dist[ni][nj]);
                        if (aux != dist[ni][nj])
                            chn = 1;
                    } else {
                        for (int k = 0; k < 4; k++) {
                            ni = i+mi[k];
                            nj = j+mj[k];
                            if (!canGo(ni, nj))
                                continue;
            
                            aux = dist[ni][nj];
                            dist[ni][nj] = min(dist[i][j] + 1, aux);
                            if (aux != dist[ni][nj])
                                chn = 1;
                        }
                    }
                }
            }

/*
            printf("===== %d =====\n", r);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++)
                    printf("%d ", dist[i][j]);
                printf("\n");
            }
*/
        }

        if (chn)
            printf("Never\n");
        else if (dist[n-1][m-1] == INT_MAX)
            printf("Impossible\n");
        else
            printf("%d\n", dist[n-1][m-1]);
    }
}
