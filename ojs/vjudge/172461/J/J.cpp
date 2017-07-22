#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct no {
    ll all, l, r, best;
    no(ll x) : all(x), l(x), r(x), best(x) {}
    no() {}
    no(ll a, ll l_, ll r_, ll b) : all(a), l(l_), r(r_), best(b) {}
};
const no empty(0, -1e16, -1e16, -1e16);

inline no join(no a, no b) {
    no c;
    c.all = a.all + b.all;
    c.l = max(a.l, a.all + b.l);
    c.r = max(b.r, a.r + b.all);
    c.best = max(a.r + b.l, max(a.best, b.best));
    return c;
}

inline no swp(no a) {
    return no(a.all, a.r, a.l, a.best);
}

const int N = 1123456;

#define printf(args...) ((void) 0)

ll v[N];

no tr[N];
int L[N], R[N];

vector<int> cp[N], adj[N];
int en = 1;
int build(int l, int r, int c) {
    printf("build(%d, %d, %d)\n", l, r, c);
    int i = en++;
    if(l == r) {
        tr[i] = no(v[cp[c][l]]);
    } else {
        int m = (l + r) / 2;
        L[i] = build(l, m, c);
        R[i] = build(m + 1, r, c);
        tr[i] = join(tr[L[i]], tr[R[i]]);
    }
    printf("(%d)%d---(%d)%d all %lld l %lld r %lld best %lld\n", l, cp[c][l] + 1, r, cp[c][r] + 1, tr[i].all, tr[i].l, tr[i].r, tr[i].best);
    return i;
}

no query(int i, int l, int r, int ql, int qr) {
    if(l > qr || r < ql) return empty;
    if(l >= ql && r <= qr) return tr[i];
    int m = (l + r) / 2;
    return join(query(L[i], l, m, ql, qr), query(R[i], m + 1, r, ql, qr));
}

int h[N], sz[N];

int seg[N];
int ch[N], ci[N], cs[N];
void hld(int u, int c) {
    ch[u] = c;
    ci[u] = cs[c]++;
    cp[c].pb(u);
    printf("cp[%d][%d] = %d\n", c, cs[c] - 1, cp[c][cs[c] - 1] + 1);
    if(adj[u].empty()) {
        seg[c] = build(0, cs[c] - 1, c);
        printf("END(%d)\n", c);
        return;
    }
    int mxi = *max_element(adj[u].begin(), adj[u].end(), [](int a, int b) { return sz[a] < sz[b]; });
    printf("%d->%d\n", u+1, mxi+1);
    hld(mxi, c);
    for(int v : adj[u])
        if(v != mxi)
            hld(v, v);
}

int p[N];

ll query(ll a, ll b) {
    printf("query(%lld, %lld)\n", a+1, b+1);
    no xa = empty, xb = empty;
    while(true) {
        if(h[ch[a]] >= h[ch[b]]) { // sobe a
            printf("up %lld--\n", a + 1);
            int l = 0;
            int r = ci[a];
            if(ch[a] == ch[b]) {
                l = ci[b];
                if(l > r) {
                    printf("shit\n");
                    no x = query(seg[ch[b]], 0, cs[ch[b]] - 1, r, l);
                    printf("%d---%d = (all %lld l %lld r %lld best %lld)\n", cp[ch[a]][l] + 1, cp[ch[a]][r] + 1, x.all, x.l, x.r, x.best);
                    xb = join(x, xb);
                } else {
                    no x = query(seg[ch[a]], 0, cs[ch[a]] - 1, l, r);
                    printf("%d---%d = (all %lld l %lld r %lld best %lld)\n", cp[ch[a]][l] + 1, cp[ch[a]][r] + 1, x.all, x.l, x.r, x.best);
                    xa = join(x, xa);
                }
                break;
            } else {
                no x = query(seg[ch[a]], 0, cs[ch[a]] - 1, l, r);
                printf("%d---%d = (all %lld l %lld r %lld best %lld)\n", cp[ch[a]][l] + 1, cp[ch[a]][r] + 1, x.all, x.l, x.r, x.best);
                xa = join(x, xa);
                a = p[ch[a]];
            }
        } else { // sobe b
            printf("up %lld\n", b + 1);
            int l = 0;
            int r = ci[b];
            no x = query(seg[ch[b]], 0, cs[ch[b]] - 1, l, r);
            xb = join(x, xb);
            b = p[ch[b]];
        }
    }
    printf("xa (%lld, %lld, %lld, %lld) xb (%lld, %lld, %lld, %lld)\n", xa.all, xa.l, xa.r, xa.best, xb.all, xb.l, xb.r, xb.best);
    return join(swp(xa), xb).best;
}

int dfs(int u, int hh) {
    h[u] = hh;
    sz[u] = 1;
    for(int v : adj[u]) {
        p[v] = u;
        adj[v].erase(search_n(adj[v].begin(), adj[v].end(), 1, u));
        sz[u] += dfs(v, hh + 1);
    }
    return sz[u];
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int i, n, a, b;
    cin >> n;
    for(i = 0; i < n - 1; i++) {
        cin >> a >> b; a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    for(i = 0; i < n; i++)
        cin >> v[i];
    dfs(0, 0);
    hld(0, 0);
    int q;
    cin >> q;
    for(i = 0; i < q; i++) {
        cin >> a >> b; a--; b--;
        cout << query(a, b) << '\n';
    }
}
