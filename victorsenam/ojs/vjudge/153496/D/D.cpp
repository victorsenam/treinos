#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;

vector<int> adj[N];
int lm[N][2], in[N][2], n, ts;
int p[2*N], lv[N], ps;
int sd[4*N][2], val[4*N], r[N];

void dfs (int u, int d) {
    in[u][0] = ps++;
    lv[u] = d;
    for (int i = 0; i < adj[u].size(); i++)
        dfs(adj[u][i], d+1);
    in[u][1] = ps-1;
}

void build (int u, int l, int r) {
    assert(u < 4*N);
    val[u] = 0;
    sd[u][0] = l;
    sd[u][1] = r;
    if (l == r)
       return;
    int mid = (l+r)/2;
    build(2*u, l, mid);
    build(2*u+1, mid+1, r);
}

int upd (int u, int i, int x) {
    assert(u < 4*N);
    if (i < sd[u][0] || sd[u][1] < i) return val[u];
    if (sd[u][0] == i && sd[u][1] == i) return val[u] = max(val[u], x);
    return val[u] = max(upd(2*u, i, x), upd(2*u+1, i, x));
}

int get (int u, int l, int r) {
    assert(u < 4*N);
    if (r < sd[u][0] || sd[u][1] < l) return 0;
    if (sd[u][0] <= l && r <= sd[u][1]) return val[u];
    return max(upd(2*u, l, r), upd(2*u+1, l, r));
}

int main () {
    scanf("%d", &ts);

    while (ts--) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
            adj[i].clear();

        for (int i = 0; i < n; i++) {
            int pr;
            scanf("%d %d %d", &pr, &lm[i][0], &lm[i][1]);
            if (i)
                adj[pr].push_back(i);
            p[2*i] = 2*i;
            p[2*i+1] = 2*i+1;
        }

        sort(p, p+n+n, [] (int i, int j) {
            if (lm[i/2][i%2] != lm[j/2][j%2]) 
                return lm[i/2][i%2] < lm[j/2][j%2];
            return (i%2) < (j%2);
        });

        ps = 0;
        dfs(0, 0);
        build(1, 0, N-1);

        for (int _i = 0; _i < 2*n; _i++) {
            int u = p[_i]/2;
            int t = p[_i]%2;

            if (t) {
                r[u] = get(1, in[u][0], in[u][1]) - lv[u];
            } else {
                upd(1, in[u][0], lv[u]);
            }
        }

        for (int i = 0; i < n; i++) {
            if (i) printf(" ");
            printf("%d", r[i]);
        }
        printf("\n");
    }
}
