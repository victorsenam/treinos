#include <bits/stdc++.h>

using namespace std;

const int N = 207;

int n;
int hd[N], nx[N], to[N], es;
int lp[N], cd[N], rs[N][N], res[N];

void dfs (int u, int fr) {
    lp[u] = cd[u] = 0;

    cd[u] = 0;
    res[u] = 0;
    for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
        if (to[ed] == fr)
            continue;
        dfs(to[ed], u);
        cd[u] = max(cd[u], cd[to[ed]]+1);
        lp[u] = max(lp[u], cd[u]);
        res[u] = max(res[u], res[to[ed]]);

        for (int c = hd[u]; c != ed; c = nx[c]) {
            if (to[c] == fr)
                continue;
            lp[u] = max(lp[u], cd[to[ed]]+cd[to[c]]+2);
        }
    }

    for (int a = hd[u]; a != -1; a = nx[a]) {
        if (to[a] == fr)
            continue;
        rs[u][to[a]] = 0;
        for (int b = hd[u]; b != a; b = nx[b]) {
            if (to[b] == fr)
                continue;
            rs[u][to[a]] = max(rs[u][to[a]], lp[to[b]]);
            rs[u][to[a]] = max(rs[u][to[a]], 1+cd[to[b]]);
            for (int c = hd[u]; c != b; c = nx[c]) {
                if (to[c] == fr)
                    continue;
                rs[u][to[a]] = max(rs[u][to[a]], 2+cd[to[b]]+cd[to[c]]);
            }
        }

        res[u] = max(res[u], rs[u][to[a]]*lp[to[a]]);
    }
}

int main () {
    scanf("%d", &n);
    memset(hd, -1, sizeof hd);
    es = 0;

    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        nx[es] = hd[a]; hd[a] = es; to[es] = b; es++;
        nx[es] = hd[b]; hd[b] = es; to[es] = a; es++;
    }

    dfs(0, -1);
    printf("%d\n", res[0]);

    for (int i = 0; i < n; i++) {
        printf("[%d] ", i+1);
        printf("lp: %d, cd: %d, res: %d\n", lp[i], cd[i], res[i]);
    }
}
