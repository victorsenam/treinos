#include <bits/stdc++.h>

using namespace std;

const int N = 34;

char mat[N][N];
bool v[N][N];
int n;
const int mx[4] = {0, 1, 0, -1};
const int my[4] = {1, 0, -1, 0};

bool isVal (int i, int j) {
    if (i < 0 || i >= n) return 0;
    if (j < 0 || j >= n) return 0;
    return 1;
}

int dfs (int i, int j) {
    if (!isVal(i, j) || mat[i][j] == '#')
        return 1;
    if (v[i][j])
        return 0;

    v[i][j] = 1;

    int res = 0;
    for (int k = 0; k < 4; k++)
        res += dfs(i+mx[k], j+my[k]);

    return res;
}

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf(" %s", mat[i]);

    printf("%d\n", 9*(dfs(0, 0) + dfs(n-1, n-1) - 4));
}
