#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 3007;
const int M = 10000;

int hd[N], to[M], nx[M], es;
int dist[N][N];
int mds[N][5], lds[N][5];
int n, m;
int pr[4];
int qi, qf;
int qu[N];
int aux[N];
int r[5], v[5];

int main () {
    scanf("%d %d", &n, &m);

    es = 2;

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        nx[es] = hd[a]; to[es] = b; hd[a] = es++;
        //nx[es] = hd[b]; to[es] = a; hd[b] = es++;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = INT_MAX;

    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        qi = qf = 0;
        qu[qf++] = i;

        while (qi < qf) {
            int u = qu[qi++];

            for (int ed = hd[u]; ed; ed = nx[ed]) {
                if (dist[i][to[ed]] != INT_MAX) continue;
                dist[i][to[ed]] = dist[i][u] + 1;
                qu[qf++] = to[ed];
            }
        }
    }

    for (int i = 0; i < n; i++)
        aux[i] = i;

    for (int i = 0; i < n; i++) {
        int qt = n;
        for (int j = 0; j < qt; j++)
            if (dist[i][aux[j]] == INT_MAX) {
                --qt;
                swap(aux[j], aux[qt]);
                --j;
            }

        for (int k = 0; k < 4; k++)
            for (int j = k+1; j < qt; j++)
                if (dist[i][aux[j]] > dist[i][aux[k]])
                    swap(aux[j], aux[k]);
        
        for (int k = 0; k < 4; k++)
            mds[i][k] = aux[k];
    }
    for (int i = 0; i < n; i++) {
        int qt = n;
        for (int j = 0; j < qt; j++)
            if (dist[aux[j]][i] == INT_MAX) {
                --qt;
                swap(aux[j], aux[qt]);
                --j;
            }

        for (int k = 0; k < 4; k++)
            for (int j = k+1; j < qt; j++)
                if (dist[aux[j]][i] > dist[aux[k]][i])
                    swap(aux[j], aux[k]);
        
        for (int k = 0; k < 4; k++)
            lds[i][k] = aux[k];
    }

    int res = 0;
    for (int u = 0; u < n; u++) {
        for (int w = 0; w < n; w++) {
            for (int b = 0; b < 4; b++) {
                for (int c = 0; c < 4; c++) {
                    v[0] = lds[u][b];
                    v[1] = u;
                    v[2] = w;
                    v[3] = mds[v[2]][c];
                    bool ok = 1;
                    for (int i = 1; ok && i < 4; i++)
                        if (dist[v[i-1]][v[i]] == INT_MAX)
                            ok = 0;

                    for (int i = 0; ok && i < 4; i++)
                        for (int j = 0; ok && j < i; j++)
                            ok = (v[i] != v[j]);

                    if (!ok) continue;

                    int loc = 0;
                    for (int i = 1; i < 4; i++)
                        loc += dist[v[i-1]][v[i]];
                    if (loc > res) {
                        res = loc;
                        for (int i = 0; i < 4; i++)
                            pr[i] = v[i];
                    }
                }
            }
        }
    }

DEBUG("%d\n", res);
    for (int k = 0; k < 4; k++)
        printf("%d ", pr[k]+1);
    printf("\n");
}
