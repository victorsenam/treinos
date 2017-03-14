#include <bits/stdc++.h>

using namespace std;

#define N 500
typedef int num;

bool tab[N][N];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

char at;
int oi, oj, di, dj, n, m;

bool val(int i, int j) {
    if (i < 0) return 0;
    if (i >= n) return 0;
    if (j < 0) return 0;
    if (j >= m) return 0;
    return 1;
}

bool dfs(int i, int j) {
    if (i == di && j == dj) return 1;
    if (!val(i, j)) return 0;
    if (tab[i][j]) return 0;

    tab[i][j] = 1;

    for (int k = 0; k < 4; k++)
        if (dfs(i+dx[k], j+dy[k])) return 1;

    return 0;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i =0 ; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf(" %c", &at);
            if (at=='X') tab[i][j] = 1;
            else tab[i][j] = 0;
        }
    }

    scanf("%d %d", &oi, &oj);
    scanf("%d %d", &di, &dj);
    oi--;
    oj--;
    di--;
    dj--;

    bool ok = 0;
    int cnt;
    cnt = 4;
    for (int i = 0; i < 4; i++) {
        if (!val(di+dx[i], dj+dy[i]) || ((di+dx[i] != oi || dj+dy[i] != oj) &&  tab[di+dx[i]][dj+dy[i]])) cnt--;
    }

    if (tab[di][dj]) ok = 1;
    else if (cnt > 1) ok = 1;
    
    tab[oi][oj] = 0;
    
    if (oi == di && oj == dj) {
        if (cnt >= 1) printf("YES\n");
        else printf("NO\n");
    } else if (!ok) printf("NO\n");
    else if (dfs(oi, oj)) printf("YES\n");
    else printf("NO\n");
}
