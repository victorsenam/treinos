#include <bits/stdc++.h>

using namespace std;

const int N = 103;

int n;
int pot[2][N];
int tree[2][N];
int diff[N];
int a[N][N];
int emp[N];
int siz, turn;
int vis[N];

void initialize() {
    for (int i = 0; i < n; i++) {
        pot[1][i] = 0;
        diff[i] = INT_MAX;

        pot[0][i] = INT_MAX;
        for (int j = 0; j < n; j++)
            pot[0][i] = min(pot[0][i], a[i][j]);
    }
}

void update () {
    int del = INT_MAX;
    for (int i = 0; i < n; i++)
        if (tree[1][i] != siz)
            del = min(del, diff[i]);

    for (int i = 0; i < n; i++) {
        if (tree[0][i] != siz)
            pot[0][i] -= del;

        if (tree[1][i] != siz)
            pot[1][i] += del;
        else
            diff[i] -= del;
    }
}

void include (int u) {
    if (tree[0][u] == siz)
        return;
    tree[0][u] = siz;

    for (int j = 0; j < n; j++)
        diff[j] = min(diff[j], pot[0][u]+pot[1][j]-a[u][j]);
}

void reset_all() {
    memset(emp, -1, sizeof emp);
}

bool aug (int u) {
    if (u == -1)
        return 1;
    if (vis[u] == turn)
        return 0;
    vis[u] = turn;
    include(u);

    for (int i = 0; i < n; i++) {
        if (pot[0][u] + pot[1][i] != a[u][i])
            continue;

        tree[1][i] = siz;

        if (aug(i)) {
            emp[i] = u;
            return 1;
        }
    }
    return 0;
}

int hungarian() {
    initialize();

    for (int i = 0; i < n; i++) {
        reset_all();

        siz++;
        while (++turn && !aug(i))
            update();
    }

    int loc = 0;
    for (int i = 0; i < n; i++)
        loc += a[emp[i]][i];
    return loc;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
            a[i][j] = -a[i][j];
        }
    }

    printf("%d\n", -hungarian());
}
