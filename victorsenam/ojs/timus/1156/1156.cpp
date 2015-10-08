#include <bits/stdc++.h>

using namespace std;

const int N = 2*52;
const int M = 103;

int hd[N], nx[M], to[M], es;
int sets[N][2], cs;
int att[2];
bool vis[N];
int cor[N];
int n, m;
int a, b;
int memo[N][N];
bool opti[N][N];
int visi[N][N];
int path[N];

bool pd (int i, int r) {
    if (r < 0)
        return 0;
    if (i == cs)
        return (r == 0);
    
    if (visi[i][r])
        return memo[i][r];
    visi[i][r] = 1;

    if (pd(i+1, r-sets[i][0])) {
        memo[i][r] = 1;
        opti[i][r] = 0;
    } else  if (pd(i+1, r-sets[i][1])) {
        memo[i][r] = 1;
        opti[i][r] = 1;
    } else {
        memo[i][r] = 0;
    }

    return memo[i][r];
}

bool dfs (int u, int c) {
    if (vis[u])
        return (cor[u] == c);

    vis[u] = 1;
    cor[u] = c;
    sets[(c>>1)][c&1]++;

    for (int ed = hd[u]; ed != -1; ed = nx[ed])
        if (!dfs(to[ed], c^1))
            return 0;

    return 1;
}

int main () {
    scanf("%d %d", &n, &m);
    memset(hd, -1, sizeof hd);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--;
        b--;

        nx[es] = hd[a]; hd[a] = es; to[es] = b; es++;
        nx[es] = hd[b]; hd[b] = es; to[es] = a; es++;
    }

    bool ok = 1;
    for (int i = 0; ok && i < 2*n; i++) {
        if (vis[i]) 
            continue;
        if (!dfs(i, 2*cs))
            ok = 0;
        cs++;
    }

    if (!ok || !pd(0,n))
        printf("IMPOSSIBLE\n");

    int att = n;
    for (int i = cs-1; i >= 0; i--) {
        path[i] = 2*i+opti[i][att];
        att -= sets[i][opti[i][att]];
    }

    for (int i = 0; i < 2*n; i++) {
        if (binary_search(path, path+cs, cor[i]))
            printf("%d ", i+1);
    }
    printf("\n");
    for (int i = 0; i < 2*n; i++) {
        if (!binary_search(path, path+cs, cor[i]))
            printf("%d ", i+1);
    }
    printf("\n");
}
