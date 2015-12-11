#include <bits/stdc++.h>

using namespace std;

const int N = 107;
const int M = 40007;

int n, m;
int mat[N];
int hd[N], nx[M], to[M], es;
int turn;
int a[N], b[N];
int vis[N];

bool dfs (int v) {
    for (int ed = hd[v]; ed != -1; ed = nx[ed]) {
        int u = to[ed];
        if (vis[u] == turn)
            continue;
        vis[u] = turn;

        if (mat[u] == -1 || dfs(mat[u])) {
            mat[u] = v;
            return 1;
        }
    }

    return 0;
}

int main () {
    int tt;
    scanf("%d", &tt);

    for (int ts = 1; ts <= tt; ts++) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", a+i);
            hd[i] = -1;
        }

        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d", b+i);
            mat[i] = -1;
            vis[i] = 0;
        }

        es = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (b[j] != 0 && (a[i] == 0 || b[j]%a[i]))
                    continue;
                nx[es] = hd[i]; hd[i] = es; to[es] = j; es++;
            }
        }

        int tot = 0;
        for (int i = 0; i < n; i++) {
            turn++;
            tot += dfs(i);
        }

        printf("Case %d: %d\n", ts, tot);
    }
}
