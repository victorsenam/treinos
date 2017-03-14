#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 3007;
const int M = 6007;

ll dist[N][N];
int n, m, a, b;
int hd[M], nx[M], to[M], es;
int s[2], t[2], l[2];
int qu[N], qi, qf;

int main () {
    scanf("%d %d", &n, &m);

    es = 2;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;

        to[es] = b; nx[es] = hd[a]; hd[a] = es++;
        to[es] = a; nx[es] = hd[b]; hd[b] = es++;
    }

    for (int i = 0; i < 2; i++) {
        scanf("%d %d %d", s+i, t+i, l+i);
        s[i]--; t[i]--;
    }

    for (int i = 0; i < n; i++) {
        qi = qf = 0;
        qu[qf++] = i;
        dist[i][i] = 0;

        while (qi < qf) {
            int u = qu[qi++];

            for (int ed = hd[u]; ed; ed = nx[ed]) {
                int v = to[ed];
                if (i == v || dist[i][v] != 0) continue;
                dist[i][v] = dist[i][u] + 1;
                qu[qf++] = v;
            }
        }
    }

    if (dist[s[0]][t[0]] > l[0] || dist[s[1]][t[1]] > l[1]) {
        printf("-1\n");
        return 0;
    }

    ll res = m - dist[s[0]][t[0]] - dist[s[1]][t[1]];   
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            bool ok = 1;
            ll loc = dist[i][j];
            for (int k = 0; k < 2; k++) {
                ll diff = min(dist[s[k]][i] + dist[j][t[k]], dist[s[k]][j] + dist[i][t[k]]);
                if (diff + dist[i][j] > l[k])
                    ok = 0;
                loc += diff;
            }
            if (!ok) continue;
            res = max(res, m-loc);
        }
    }

    printf("%I64d\n", res);
}
