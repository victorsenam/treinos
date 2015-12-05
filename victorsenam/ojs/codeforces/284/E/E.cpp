// SONO DEMAIS :(

#include <bits/stdc++.h>

using namespace std;

const int N = 307;

int nx[N], vis[N], u[N];
int att;
int v[N], val[N];
int p[N];
int o;
int n, q, t, a, b;

int dfs (int i) {
    if (i == 0)
        return 0;
    if (vis[i]) {
        printf("0\n");
        exit(0);
    } 

    p[o++] = i;
    vis[i] = 1;
    val[i] = v[i] + dfs(nx[i]);

    return val[i];
}

int main () {
    scanf("%d %d %d", &n, &q, &t);

    for (int i = 0; i < n; i++)
        scanf("%d", v+i);

    for (int i = 0; i < q; i++) {
        scanf("%d %d", &b, &a);
        nx[a] = b;
        u[b] = 1;
    }

    for (int i = 0; i < q; i++)
        t -= val[i] - v[i];

    printf("%d\n", t);
    return 0;

    bool ok = 0;
    for (int i = 0; i < q; i++) {
        if (u[i])
            continue;
        ok = 1;
        dfs(i);
    }

   
}
