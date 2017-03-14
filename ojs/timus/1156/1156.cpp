#include <bits/stdc++.h>

using namespace std;

const int N = 103;
const int M = 203;

int hd[N], nx[M], to[M], es;
int n, m;
int a, b;
int cor[N];
int sets[N][2];
bool visi[N][N];
bool solv[N][N];
bool memo[N][N];
bool sol[N];

void fail() {
    printf("IMPOSSIBLE\n");
    exit(0);
}

bool solve (int a, int b, int i) {
    if (a == 0 && b == 0)
        return 1;
    if (a < 0 || b < 0)
        return 0;

    if (visi[a][b])
        return memo[a][b];
    visi[a][b] = 1;

    if (solve(a-sets[i][0], b-sets[i][1], i+1)) {
        memo[a][b] = 1;
        solv[a][b] = 0;
    } else if (solve(a-sets[i][1], b-sets[i][0], i+1)) {
        memo[a][b] = 1;
        solv[a][b] = 1;
    } else {
        memo[a][b] = 0;
    }
    return memo[a][b];
}

void dfs (int u, int c) {
    if (cor[u] == -1)
        cor[u] = c;
    else if (cor[u] != c)
        fail();
    else
        return;
    
    for (int ed = hd[u]; ed != -1; ed = nx[ed])
        dfs(to[ed], c^1);
}

int main () {
    memset(cor, -1, sizeof cor);
    memset(hd, -1, sizeof hd);

    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        nx[es] = hd[a]; hd[a] = es; to[es] = b; es++;
        nx[es] = hd[b]; hd[b] = es; to[es] = a; es++;
    }

    int cs = 0;
    for (int i = 0; i < 2*n; i++) {
        if (cor[i] == -1)
            dfs(i, 2*(cs++));
        sets[(cor[i]>>1)][(cor[i]&1)]++;
    }

    if (!solve(n, n, 0))
        fail();

    a = b = n;
    for (int i = 0; i < cs; i++) {
        if (!solv[a][b]) {
            sol[2*i] = 1;
            a -= sets[i][0];
            b -= sets[i][1];
        } else {
            sol[2*i+1] = 1;
            a -= sets[i][1];
            b -= sets[i][0];
        }
    }

    for (int i = 0; i < 2*n; i++) {
        if (sol[cor[i]])
            printf("%d ", i+1);
    }
    printf("\n");
    for (int i = 0; i < 2*n; i++) {
        if (!sol[cor[i]])
            printf("%d ", i+1);
    }
    printf("\n");
}
