#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define lld I64d
#define DEBUG(...) {}
#endif

const int N = 300007;

int a, b;
int n, m;

int c[N];
int hd[N], to[N], nx[N], es;

int dfs (int u, int cr) {
    if (c[u] >= 0 && c[u] != cr)
        return 0;
    else if (c[u] >= 0)
        return 1;
    c[u] = cr;

    for (int ed = hd[u]; ed; ed = nx[ed])
        if (!dfs(to[ed], !cr))
            return 0;

    return 1;
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        c[i] = -1;
    }
    es = 2;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;

        nx[es] = hd[a]; to[es] = b; hd[a] = es++;
        nx[es] = hd[b]; to[es] = a; hd[b] = es++;
    } 

    bool ok = 1;
    bool cr = 0;
    for (int i = 0; ok && i < n; i++) {
        if (c[i] >= 0)
            continue;
        ok = dfs(i, cr);
        cr != cr;
    }

    if (!ok) {
        printf("-1\n");
    } else {
        for (int cr = 0; cr < 2; cr++) {
        int k = 0;
            for (int i = 0; i < n; i++)
                if (c[i] == cr)
                    k++;

            printf("%d\n", k);
            for (int i = 0; i < n; i++) {
                if (c[i] == cr)
                    printf("%d ", i+1);
            }
            printf("\n");
        }
    }
}
