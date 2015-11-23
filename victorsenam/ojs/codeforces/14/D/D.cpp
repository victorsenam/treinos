#include <bits/stdc++.h>

using namespace std;

const int N = 500;

int hd[N], to[N], nx[N], es;
int fr[N], su[N];
int n;

int dfs (int u, int p) {
    fr[u] = su[u] = 0;
    for (int ed = hd[u]; ed != -1; ed = nx[ed]) {
        if (to[ed] == p)
            continue;

        dfs(to[ed], u);

        fr[u] = max(fr[u], fr[to[ed]]+1);
        su[u] = max(su[u], su[to[ed]]);

        for (int c = hd[u]; c != ed; c = nx[c]) {
            if (to[c] == p)
                continue;
            su[u] = max(su[u], fr[to[ed]]+fr[to[c]]+2);
        }
    }
    su[u] = max(su[u], fr[u]);


    return su[u];
}

int main ( ){
    memset(hd, -1, sizeof hd);
    scanf("%d", &n);

    for (int i = 1; i < n; i++) {
        int a, b;

        scanf("%d %d", &a, &b);
        a--; b--;
        nx[es] = hd[a]; hd[a] = es; to[es] = b; es++;
        nx[es] = hd[b]; hd[b] = es; to[es] = a; es++;
    }

    int res = 0;
    for (int i = 0; i < es; i+=2) {
        dfs(to[i], to[i+1]);
        dfs(to[i+1], to[i]);
        res = max(res, su[to[i]]*su[to[i+1]]);
    }
    printf("%d\n", res);
}

