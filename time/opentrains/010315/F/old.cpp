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

const int N = 307;

int adj[3][N][N];
int n, m;
int a, b;
int uf[N], wf[N];
int c[N], cs;
int res[N][2], rs;

int find (int i) {
    if (i == uf[i]) return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    if ((i = find(i)) == (j = find(j))) return;
    if (wf[i] < wf[j])
        swap(i, j);
    wf[i] += wf[j];
    uf[j] = i;
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        uf[i] = i;
        wf[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;

        adj[0][a][b] = 1;
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adj[0][i][j] |= (adj[0][i][k] & adj[0][k][j]);
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (adj[0][i][j] && adj[0][j][i])
                join(i, j);

    cs = 0;   
    for (int i = 0; i < n; i++) {
        if (i == find(i))
            c[cs++] = i;

        for (int j = 0; j < n; j++)
            if (adj[0][i][j])
                adj[1][find(i)][find(j)] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (wf[find(i)] > 1) {
            int j;
            for (j = i+1; j < n && find(i) != find(j); j++);
            if (j == n) {
                for(j = 0; i > j && find(i) != find(j); j++);
                assert(i > j);
                res[rs][0] = i;
                res[rs][1] = j;
                rs++;
            } else {
                res[rs][0] = i;
                res[rs][1] = j;
                rs++;
            }
        }
    }

    for (int i = 0; i < cs; i++)
        for (int j = 0; j < cs; j++)
            adj[2][c[i]][c[j]] = adj[1][c[i]][c[j]];

    for (int k = 0; k < cs; k++) {
        for (int i = 0; i < cs; i++) {
            if (i == k) continue;
            for (int j = 0; j < cs; j++) {
                if (j == k || j == i) continue;
                if (adj[2][c[i]][c[k]] && adj[2][c[k]][c[j]])
                    adj[1][c[i]][c[j]] = 0;
            }
        }
    }

    for (int i = 0; i < cs; i++)
        for (int j = 0; j < cs; j++) {
            if (i == j) continue;
            if (adj[1][c[i]][c[j]]) {
                res[rs][0] = c[i];
                res[rs][1] = c[j];
                rs++;
            }
        }
    
    printf("%d %d\n", n, rs);
    for (int i = 0; i < rs; i++) {
        printf("%d %d\n", res[i][0]+1, res[i][1]+1);
    }
}
