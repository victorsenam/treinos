#include <bits/stdc++.h>

using namespace std;

const int N = 40;

bool vis[N][N];
char mat[N][N];
const int mi[4] = {0, 1, -1, 0};
const int mj[4] = {1, 0, 0, -1};
int n;

inline bool isVal (int i, int j) {
    if (i < 0 || i >= n)
        return 0;
    if (j < 0 || j >= n)
        return 0;
    if (mat[i][j] == '#')
        return 0;
    return 1;
}

int dfs (int i, int j) {
    if (vis[i][j])
        return 0;
    vis[i][j] = 1;

    int res = 0;
    int sum = 0;
    for (int k = 0; k < 4; k++) {
        if (isVal(i+mi[k], j+mj[k]))
            res += dfs(i+mi[k], j+mj[k]);
        else {
            res++;
            sum++;
        }
    }
    return res;
}

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf(" %s", mat[i]);
    
    printf("%d\n", 9*(dfs(0, 0)+dfs(n-1, n-1)-4));
}
