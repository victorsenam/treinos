#include <bits/stdc++.h>

using namespace std;

const int N = 1003;
const int di[4] = {0, 0, 1, -1};
const int dj[4] = {1, -1, 0, 0};

bool visi[N][N];
char mat[N][N];
int res[N][N];
int uf[N*N], wf[N*N];
int n, m, k;

int find (int i) {
    if (i == uf[i])
        return i;
    return uf[i] = find(uf[i]);
}

void join (int i, int j) {
    i = find(i); j = find(j);
    if (i == j)
        return;
    if (wf[i] > wf[j])
        swap(i, j);
    wf[j] += wf[i];
    uf[i] = j;
}

inline bool isVal (int i, int j) {
    if (i < 0 || i >= n)
        return 0;
    if (j < 0 || j >= m)
        return 0;
    if (mat[i][j] == '*')
        return 0;
    return 1;
}
int dfs (int i, int j) {
    if (mat[i][j] == '*')
        return 1;
    if (!isVal(i, j))
        return 0;
    if (visi[i][j])
        return 0;
    
    visi[i][j] = 1;
    res[i][j] = 0;

    for (int k = 0; k < 4; k++)
        res[i][j] += dfs(i+di[k], j+dj[k]);

    return res[i][j];
}

int main () {
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; i++)
        scanf(" %s", mat[i]);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            uf[i*m+j] = i*m+j;
            wf[i*m+j] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!isVal(i, j))
                continue;
            for (int k = 0; k < 4; k++) {
                if (!isVal(i+di[k], j+dj[k]))
                    continue;
                join(i*m+j, (i+di[k])*m + j + dj[k]);
            }
        }
    }

    for (int i = 0; i < k; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        int p = find(a*m+b);
        dfs(p/m, p%m);
        printf("%d\n", res[p/m][p%m]);
    }
}
