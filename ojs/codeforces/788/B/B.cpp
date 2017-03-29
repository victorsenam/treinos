#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e6+7;

int n;
int m;
ll deg[N], slf;
int uf[N], wf[N];

int find (int u) {
    if (u == uf[u]) return u;
    return uf[u] = find(uf[u]);
}

void join (int u, int v) {
    if ((u = find(u)) == (v = find(v))) return;
    if (wf[u] < wf[v]) swap(u, v);
    wf[u] += wf[v];
    uf[v] = u;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n ; i++) {
        uf[i] = i;
        wf[i] = 1;
    }

    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        if (a == b) {
            slf++;
            continue;
        }

        join(a,b);
        deg[a]++;
        deg[b]++;
    }

    int mx = 0, rp = 0;
    for (int i = 0; i < n; i++) {
        if (uf[i] == i) {
            if (wf[i] > mx) {
                rp = i;
                mx = wf[i];
            }
        }
    }

    for (int i = 0 ;i < n; i++) {
        if (uf[i] == i && i != rp && (wf[i] > 1 || deg[i])) {
            printf("0\n");
            return 0;
        }
    }

    ll res = slf*(slf-1)/2;
    res += slf*ll(m-slf);
    for (int i = 0; i < n; i++) {
        res += (deg[i]*(deg[i]-1))/2;
    }

    printf("%lld\n", res);
}
