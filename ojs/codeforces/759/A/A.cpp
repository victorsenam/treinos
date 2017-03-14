#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 2e5+7;

int p[N], b;
int c;
int n;

int uf[N], wf[N];

int find (int u) {
    if (uf[u] == u) return u;
    return uf[u] = find(uf[u]);
}

void join (int u, int v) {
    if ((u = find(u)) == (v = find(v))) return;
    if (wf[u] > wf[v]) swap(wf[u], wf[v]);

    wf[v] += wf[u];
    uf[u] = v;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
        p[i]--;
        uf[i] = i;
        wf[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &b);
        c += b;
    }

    c = !((c&1));

    int r = 0;

    for (int i = 0; i < n; i++)
        join(i, p[i]);
    for (int i = 0; i < n; i++)
        if (uf[i] == i)
            r++;

    if (r == 1) r = 0;

    printf("%d\n", r+c);
}
