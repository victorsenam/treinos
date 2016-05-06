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
int mds[N][3];
int n, m;
int pr[4];
int qi, qf;
int qu[N];
int aux[N];
int r[4], v[4];

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
            printf("%d %d : %d\n", i+1, u+1, dist[i][u]);

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

        for (int k = 0; k < 3; k++)
            for (int j = k+1; j < qt; j++)
                if (dist[i][aux[j]] > dist[i][aux[k]])
                    swap(aux[j], aux[k]);
        
        for (int k = 0; k < 3; k++)
            mds[i][k] = aux[k];

        printf("%d #%d:", i+1, qt);
        for (int k = 0; k < 3; k++)
            printf(" %d(%d)", mds[i][k]+1, dist[i][mds[i][k]]);
        printf("\n");
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        for (r[0] = 0; r[0] < 3; r[0]++) {
            v[0] = mds[i][r[0]];
            if (dist[i][v[0]] == INT_MAX) break;
            if (i == v[0]) continue;

            for (r[1] = 0; r[1] < 3; r[1]++) {
                v[1] = mds[i][r[1]];
                if (dist[i][v[1]] == INT_MAX) break;
                if (v[0] == v[1]) continue;
                if (i == v[1]) continue;

                for (r[2] = 0; r[2] < 3; r[2]++) {
                    v[2] = mds[v[1]][r[2]];
                    if (dist[v[1]][v[2]] == INT_MAX) break;
                    if (v[0] == v[2]) continue;
                    if (v[1] == v[2]) continue;
                    if (i == v[2]) continue;
                    
                    int loc = dist[i][v[0]] + dist[i][v[1]] + dist[v[1]][v[2]];
                    if (loc > res) {
                        res = loc;
                        pr[0] = i;
                        for (int k = 1; k < 4; k++)
                            pr[k] = v[k];
                    }
                }
            }
        }
    }

    for (int k = 0; k < 4; k++)
        printf("%d ", pr[k]+1);
    printf("\n");
}
