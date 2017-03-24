#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+8;

int ts;
int n;
int p[N];
int t[N][2];
int hd;
int res[N];
vector<int> adj[N];

int ch[4*N][2], vl[4*N], es;

void create (int & u) {
    fflush(stdout);
    u = es++;
    ch[u][0] = ch[u][1] = vl[u] = 0;
}

int add (int & u, int i, int l, int r, int x) {
    if (!u) create(u);
    if (l > i || r < i)
        return vl[u];
    if (l == i && r == i) {
        vl[u] += x;
        return vl[u];
    } else {
        return vl[u] = (add(ch[u][0], i, l, (l+r)/2, x) + add(ch[u][1], i, (l+r)/2+1, r, x));
    }
}

int get (int & u, int ql, int qr, int l, int r) {
    if (!u || r < ql || qr < l) return 0;
    if (l <= ql && qr <= r) return vl[u];
    return get(ch[u][0], ql, qr, (l+r)/2, (l+r)/2+1) + get(ch[u][1], ql, qr, (l+r)/2, (l+r)/2+1);
}

int dfs (int u) {
    res[u] = get(hd, t[u][0], 1e9+7, 0, 1e9+7);
    add(hd, t[u][1], 0, 1e9+7, 1);

    for (int i = 0; i < adj[u].size(); i++)
        dfs(adj[u][i]);

    add(hd, t[u][1], 0, 1e9+7, -1);
}

int main () {
    scanf("%d", &ts);

    while (ts--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            adj[i].clear();
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &p[i], &t[i][0], &t[i][1]);

            if (i)
                adj[p[i]].push_back(i);
        }

        hd = 0;
        es = 1;
        dfs(0);

        for (int i = 0; i < n; i++)
            printf("%d ", res[i]);
        printf("\n");
    }

}
