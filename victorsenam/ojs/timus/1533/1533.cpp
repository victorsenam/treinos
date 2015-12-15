// TA ERRADO - NÃO SEI ARRUMAR

#include <bits/stdc++.h>

using namespace std;

const int N = 103;

int mat[N][N];
bitset<N> res[N];
int turn, siz;
int visi[N];
int n;

int diff[N], match[N];
int pot[2][N];
int tree[2][N];

void dfs (int u) {
    if (visi[u] == turn)
        return;

    visi[u] = turn;

    res[u].reset();

    for (int i = 0; i < n; i++) {
        if (!mat[u][i])
            continue;

        dfs(i);
        res[u].set(i);
        res[u] |= res[i];
    }
}

void initialize() {
    for (int i = 0; i < n; i++) {
        pot[0][i] = 0;
        for (int j = 0; j < n; j++)
            pot[0][i] = max(pot[0][i], mat[i][j]);

        pot[1][i] = 0;
    }

    memset(tree, -1, sizeof tree);
    memset(match, -1, sizeof match);
}

void reset_all() {
    for (int j = 0; j < n; j++) {
        diff[j] = INT_MAX;
    }
}

void insert(int u) {
    if (tree[0][u] == siz)
        return;
    tree[0][u] = siz;
    for (int j = 0; j < n; j++)
        diff[j] = min(diff[j], pot[0][u] + pot[1][j] - mat[u][j]);
}

void update() {
    int del = INT_MAX;
    for (int j = 0; j < n; j++)
        if (tree[1][j] != siz)
            del = min(del, diff[j]);

    for (int i = 0; i < n; i++)
        if (tree[0][i] == siz)
            pot[0][i] -= del;

    for (int i = 0; i < n; i++)
        if (tree[1][i] == siz)
            pot[1][i] += del;
        else
            diff[i] -= del;
}

bool augment (int u) {
    if (visi[u] == turn)
        return 0;

    visi[u] = turn;
    insert(u);

    for (int i = 0; i < n; i++) {
        if (pot[0][u] + pot[1][i] != mat[u][i])
            continue;
        tree[1][i] = siz;

        if (match[i] == -1 || augment(match[i])) {
            match[i] = u;
            return 1;
        }
    }
    return 0;
}

int hungarian() {
    initialize();
    for (siz = 0; siz < n; siz++) {
        reset_all();

        while (++turn && !augment(siz))
            update();
    }

    int res = 0;
    for (int i = 0; i < n; i++)
        res += mat[match[i]][i];
    return res;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);

    turn++;
    for (int i = 0; i < n; i++)
        dfs(i);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == 1)
                mat[i][j] = 1;
            else if (res[j].test(i) || j == i)
                mat[i][j] = 0;
            else
                mat[i][j] = -N;
        }
    }

    printf("%d\n", n-hungarian());

    for (int i = 0; i < n; i++)
        printf("%d<->%d\n", match[i]+1, i+1);

    for (int i = 0; i < n; i++)
        if (mat[match[i]][i] == 0)
            printf("%d ", i+1);
    printf("\n");
}
