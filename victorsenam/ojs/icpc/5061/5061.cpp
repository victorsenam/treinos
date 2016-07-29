#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 50007;
const int K = 20;

int hd[N], nx[2*N], to[2*N], val[N], ch[N], es;
int pr[N][K], de[N];
int tc, str;
int deg[N];
int n, q;
int qu[N], qi, qf;

void dfs (int u, int p, int d) {
    de[u] = d;
    pr[u][0] = p;
    for (int k = 1; k < K; k++)
        pr[u][k] = pr[pr[u][k-1]][k-1];
    for (int ed = hd[u]; ed; ed = nx[ed]) {
        int v = to[ed];
        if (p == v) continue;

        dfs(v, u, d+1);
    }
}

int lca (int a, int b) {
    if (de[a] < de[b])
        swap(a, b);

    for (int k = K-1; k >= 0; k--)
        if (de[pr[a][k]] >= de[b])
            a = pr[a][k];
    if (a == b) return a;

    for (int k = K-1; k >= 0; k--)
        if (pr[a][k] != pr[b][k]) {
            a = pr[a][k];
            b = pr[b][k];
        }

        return pr[a][0];
    
}

int main () {
    scanf("%d", &tc);

    for (int ts = 1; ts <= tc; ts++) {
        scanf("%d", &n);
        es = 2;
        for (int i = 0; i < n; i++) {
            val[i] = 0;
            hd[i] = 0;
            deg[i] = 0;
            de[i] = 0;
            for (int k = 0; k < K; k++)
                pr[i][k] = 0;
        }
        for (int i = 1; i < n; i++) {
            int a, b;
            scanf("%d %d", &a, &b);

            nx[es] = hd[a]; to[es] = b; hd[a] = es++;
            nx[es] = hd[b]; to[es] = a; hd[b] = es++;
            deg[a]++; deg[b]++;
        }

        dfs(0, 0,0);
        
        qi = qf = 0;
        for (int i = 0; i < n; i++) {
            if (deg[i] == 1)
                qu[qf++] = i;
        }

        scanf("%d", &q);
        for (int i = 0; i < q; i++) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);

            int l = lca(a, b);

            val[b] += c;
            val[a] += c;
            val[l] -= c;
            if (l) val[pr[l][0]] -= c;

        }

        while (qi < qf) {
            int u = qu[qi++];

            if (!u) continue;
            val[pr[u][0]] += val[u];

            deg[pr[u][0]]--;

            if (deg[pr[u][0]] == 1)
                qu[qf++] = pr[u][0];
        }


        printf("Case #%d:\n", ts);
        for (int i = 0; i < n; i++) {
            printf("%d\n", val[i]);
        }
    }
}
