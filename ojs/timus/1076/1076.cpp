#include <bits/stdc++.h>

using namespace std;

const int N = 160;

typedef int num;

num mat[N][N];
num cst[N][N];
int n;

int siz, turn;
int tree[2][N], visi[N];

int diff[N];
int matc[N];
int pot[2][N];

void initialize() {
    for (int i = 0; i < n; i++) {
        pot[0][i] = cst[i][0];
        for (int j = 1; j < n; j++)
            pot[0][i] = max(pot[0][i], cst[i][j]);

        pot[1][i] = 0;
    }

    memset(matc, -1, sizeof matc);
    memset(tree, -1, sizeof tree);
}

void reset_all () {
    for (int j = 0; j < n; j++)
        diff[j] = INT_MAX;
}

void include (int i) {
    tree[0][i] = siz;
 //   printf("%d -> ", i);
    for (int j = 0; j < n; j++) {
        diff[j] = min(diff[j], pot[0][i] + pot[1][j] - cst[i][j]);
 //       printf("%d ", diff[j]);
    }
 //   printf("\n");
}

void update () {
    int del = INT_MAX;
    for (int j = 0; j < n; j++)
        if (tree[1][j] != siz)
            del = min(del, diff[j]);

    for (int i = 0; i < n; i++)
        if (tree[0][i] == siz)
            pot[0][i] -= del;

    for (int j = 0; j < n; j++)
        if (tree[1][j] == siz)
            pot[1][j] += del;
        else
            diff[j] -= del;
    turn++;
}

bool augment (int u) {
    if (visi[u] == turn)
        return 0;
    visi[u] = turn;

    include(u);

    for (int j = 0; j < n; j++) {
        if (pot[0][u] + pot[1][j] != cst[u][j])
            continue;

        tree[1][j] = siz;

        if (matc[j] == -1 || augment(matc[j])) {
            matc[j] = u;
            return 1;
        }
    }
    return 0;
}

int hungarian() {
    initialize();
    for (siz = 0; siz < n; siz++) {
        reset_all();
        turn++;

        while (!augment(siz))
            update();
    }

    int res = 0;
    for (int i = 0; i < n; i++)
        res += cst[matc[i]][i];
    return res;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &mat[i][j]);
            cst[0][j] += mat[i][j];
        }
    }

    for (int i = n-1; i >= 0; i--)
        for (int j = 0; j < n; j++)
            cst[i][j] = - cst[0][j] + mat[i][j];


    printf("%d\n", -hungarian());
}
