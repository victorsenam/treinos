#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 407;

bool mat[N][N];
int dist[N];
bool visi[N];
int qu[N], qi, qf;
int n, m, a, b;

int main () {
    scanf("%d %d", &n, &m);


    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;

        mat[a][b] = mat[b][a] = 1;
    }

    qu[qf++] = 0;
    visi[0] = 1;
    while (qi < qf) {
        int u = qu[qi++];

        for (int i = 0; i < n; i++) {
            if (i == u || mat[u][i] == mat[0][n-1] || visi[i])
                continue;

            dist[i] = dist[u] + 1;
            visi[i] = 1;
            qu[qf++] = i;
        }
    }

    if (visi[n-1])
        printf("%d\n", dist[n-1]);
    else
        printf("-1\n");
}
