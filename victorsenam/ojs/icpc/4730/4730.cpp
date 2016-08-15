#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 200007;
const int M = 1000007;

int n, m;
char str[6];
int lo[N], hi[N], uf[N], wf[N];
int bit[M][2];
int t;

int find (int u) {
    if (u == uf[u]) return u;
    return uf[u] = find(uf[u]);
}

int join (int u, int v) {
    if (wf[u] < wf[v]) swap(u, v);
    wf[u] += wf[v];
    uf[v] = u;
    lo[u] = min(lo[u], lo[v]);
    hi[u] = max(hi[u], hi[v]);
    return u;
}

void add (int i, int x, int y) {
    for (i += 2; i > 0; i-=(i&-i)) {
        bit[i][0] += x;
        bit[i][1] += y;
    }
}

void get (int i) {
    int x = 0;
    int y = 0;
    for (i += 2; i < M; i+=(i&-i)) {
        x += bit[i][0];
        y += bit[i][1];
    }
    printf("%d %d\n", x, y);
}

int main () {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf("%d", hi+i);
            scanf("%d", hi+i);
            uf[i] = i;
            wf[i] = 1;
            lo[i] = hi[i];
        }

        memset(bit, 0, sizeof bit);
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf(" %s", str);
            if (str[0] == 'l') {
                double a;
                scanf("%lf", &a);
                get((int) a+1);
            } else {
                int a, b;
                scanf("%d %d", &a, &b);
                if ((a = find(a)) != (b = find(b))) {
                    add(lo[a], 1, wf[a]);
                    add(hi[a], -1, -wf[a]);
                    add(lo[b], 1, wf[b]);
                    add(hi[b], -1, -wf[b]);
                    a = join(a, b);
                    add(lo[a], -1, -wf[a]);
                    add(hi[a], 1, wf[a]);
                }
            }
        }
    }
}
