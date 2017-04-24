#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e3+7;

const int mv[4][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
};

int vs[N][N][4][3];
int n, m;
char mat[N][N];

int dfs (int i, int j, int d, int t) {
    if (t == 3) return 0;
    if (i < 0 || i >= n || j < 0 || j >= m) return 0;
    if (mat[i][j] == '*')
        return 0;
    if (mat[i][j] == 'T')
        return 1;
    if (vs[i][j][d][t])
        return 0;
    vs[i][j][d][t] = 1;

    if (dfs(i+mv[d][0], j+mv[d][1], d, t))
        return 1;
    if (dfs(i, j, (d+1)%4, t+1))
        return 1;
    if (dfs(i, j, (d+3)%4, t+1))
        return 1;
    return 0;
}

int main () {
    scanf("%d %d", &n, &m);
    
    int si, sj;
    for (int i = 0; i < n; i++) {
        scanf(" %s", mat[i]);
        for (int j = 0; j < m; j++)
            if (mat[i][j] == 'S') {
                si = i;
                sj = j;
            }
    }

    for (int i = 0; i < 4; i++)
        if (dfs(si, sj, i, 0)) {
            printf("YES\n");
            return 0;
        }
    printf("NO\n");
}
