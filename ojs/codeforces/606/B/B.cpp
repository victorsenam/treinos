#include <bits/stdc++.h>

using namespace std;

const int N = 507;
const int S = 100007;

int dist[N][N];
int n, m, x, y;
int qx[S], qy[S], qi, qf;
int freq[S];
int s;
char str[S];

void dfs(int x, int y, int d) {
    if (d == s)
        return;
    dist[x][y] = min(dist[x][y], d);

    int nx = x;
    int ny = y;

    if (str[d] == 'U')
        nx--;
    else if (str[d] == 'D')
        nx++;
    else if (str[d] == 'L')
        ny--;
    else
        ny++;

    if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
        nx = x;
        ny = y;
    }

    dfs(nx, ny, d+1);
}

int main () {
    scanf("%d %d %d %d", &n, &m, &x, &y);
    x--; y--;
    scanf(" %s", str);
    s = strlen(str);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dist[i][j] = s;

    dfs(x, y, 0);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            freq[dist[i][j]]++;

    for (int i = 0; i <= s; i++)
        printf("%d ", freq[i]);
    printf("\n");
}
