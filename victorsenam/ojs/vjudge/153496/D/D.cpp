#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;
const int TOT = 1e9+7;
const int K = 100;

int ts, n;
int v[N][2];
int p[N], dg[N], lv[N];
vector<int> adj[N];
int r[N];
int hd[N];
int ch[K*N][2], vl[K*N], es;

inline void create (int & u) {
    u = es++;
    vl[u] = ch[u][0] = ch[u][1] = 0;
}

int add (int & u, int i, int l, int r, int x) {
    if (l > i || r < i) return 0;
    if (!u) create(u);
    if (l == i && r == i) return (vl[u] = max(vl[u], x));

    return vl[u] = max(add(ch[u][0], i, l, (l+r)/2, x), add(ch[u][1], i, (l+r)/2+1, r, x));
}

int get (int u, int ql, int qr, int l, int r) {
    if (!u || ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return vl[u];
    return max(get(ch[u][0], ql, qr, l, (l+r)/2), get(ch[u][1], ql, qr, (l+r)/2+1, r));
}

void join (int & u, int v) {
    if (!u) {
        u = v;
        return;
    }
    if (!v)
        return;
    vl[u] = max(vl[u], vl[v]);
    join(ch[u][0], ch[v][0]);
    join(ch[u][1], ch[v][1]);
}

void dfs (int u, int d) {
    lv[u] = d;
    for (int i = 0; i < adj[u].size(); i++)
        dfs(adj[u][i], d+1);
}

int main () {
    scanf("%d", &ts);

    while (ts--) {
        scanf("%d", &n);

        es = 1;
        for (int i = 0; i < n; i++) {
            hd[i] = 0;
            scanf("%d %d %d", &p[i], &v[i][0], &v[i][1]);

            if (p[i] >= 0) {
                dg[p[i]]++;
                adj[p[i]].push_back(i);
            }
        }
        dfs(0,0);

        queue<int> qu;
        for (int i = 0; i < n; i++) {
            if (dg[i] == 0)
                qu.push(i);
        }

        while (!qu.empty()) {
            int u = qu.front();
            qu.pop();

            add(hd[u], v[u][0], 0, TOT, lv[u]);

            r[u] = get(hd[u], 0, v[u][1], 0, TOT) - lv[u];
            
            if (!u) continue;

            join(hd[p[u]], hd[u]);

            dg[p[u]]--;
            if (dg[p[u]] == 0)
                qu.push(p[u]);
        }

        for (int i = 0; i < n; i++)
            printf("%d ", r[i]);
        printf("\n");
    }
}
