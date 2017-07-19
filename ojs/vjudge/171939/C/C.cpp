#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<ll,ll> pii;

typedef double numof;
typedef complex<numof> num;
const double pi = acos(-1.0);
const int N = 212345;

vector<int> adj[N];

int nxp2(int n) {
    if(n & (n - 1))
        n = (1 << (32 - __builtin_clz(n)));
    return n;
}

int p[N];
void FFT(num *v, num *ans, int n, int type) {
    assert(!(n & (n - 1)));
    int i, sz, o;
    p[0] = 0;
    for(i = 1; i < n; i++) p[i] = (p[i >> 1] >> 1) | ((i & 1)? (n >> 1) : 0);
    for(i = 0; i < n; i++) ans[i] = v[p[i]];
    for(sz = 1; sz < n; sz <<= 1) {
        const num wn(cos(type * pi / sz), sin(type * pi / sz));
        for(o = 0; o < n; o += (sz << 1)) {
            num w = 1;
            for(i = 0; i < sz; i++) {
                const num u = ans[o + i], t = w * ans[o + sz + i];
                ans[o + i] = u + t;
                ans[o + i + sz] = u - t;
                w *= wn;
            }
        }
    }
    if(type == -1) for(i = 0; i < n; i++) ans[i] /= n;
}

vector<num> pols[N];
#define fst first
#define snd second

vector<pii> ps;
void divide(int i, int l, int r) {
    if(l == r) {
        pols[i].resize(max(ps[l].fst, ps[l].snd) + 1, num(0));
        pols[i][ps[l].fst] = 1;
        pols[i][ps[l].snd] = 1;
        return;
    }
    int m = (l + r) / 2;
    divide(2 * i, l, m);
    divide(2 * i + 1, m + 1, r);
    int p2i = pols[2 * i].size(), p2i1 = pols[2 * i + 1].size();
    int n = nxp2(p2i + p2i1);
    pols[i].resize(n);
    pols[2 * i].resize(n, num(0));
    pols[2 * i + 1].resize(n, num(0));
    vector<num> A(n);
    FFT(&pols[2 * i][0], &A[0], n, 1);
    FFT(&pols[2 * i + 1][0], &pols[i][0], n, 1);
    for(int j = 0; j < n; j++)
        A[j] *= pols[i][j];
    FFT(&A[0], &pols[i][0], n, -1);
    pols[2 * i].resize(p2i);
    pols[2 * i + 1].resize(p2i1);
    pols[i].resize(p2i + p2i1);
    for(num &x : pols[i])
        if(abs(real(x)) > .5)
            x = 1;
        else
            x = 0;
}

bool swp[N];

void solve(int i, int l, int r, int ans) {
    if(l == r) {
        swp[l] = (ans != ps[l].fst);
        return;
    }
    for(int a = 0; a < pols[2 * i].size(); a++) {
        if(abs(real(pols[2 * i][a])) < .5) continue;
        int b = (ans - a);
        if(b >= 0 && b < pols[2 * i + 1].size() && abs(real(pols[2 * i + 1][b])) > .5) {
            int m = (l + r) / 2;
            solve(2 * i, l, m, a);
            solve(2 * i + 1, m + 1, r, b);
            return;
        }
    }
    abort();
}

int en;
int W, B, seen[N];
int co[N][2];
void dfs(int u, int c) {
    if(seen[u]) return;
    seen[u] = true;
    co[en][c] = u;
    (c? B : W)++;
    for(int v : adj[u])
        dfs(v, !c);
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int i, n, m, a, b;
    cin >> n >> m;
    for(i = 0; i < m; i++) {
        cin >> a >> b; a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int ct = 0;
    for(i = 0; i < n; i++)
        if(!seen[i]) {
            co[en][0] = co[en][1] = i;
            ct++;
            W = B = 0;
            dfs(i, 0);
            ps.pb(pii(W, B));
            en++;
        }
    random_shuffle(ps.begin(), ps.end());
    divide(1, 0, ct - 1);
    int mn = INT_MAX;
    int mni = -1;
    for(i = 0; i < int(pols[1].size()); i++)
        if(abs(real(pols[1][i])) > .5 && abs(i - (n - i)) < mn) {
            mn = min(mn, abs(i - (n - i)));
            mni = i;
        }
    cout << mn << ' ' << en - 1 << '\n';
    solve(1, 0, ct - 1, mni);
    int cur = 0;
    for(i = 0; i < en - 1; i++) {
        cur ^= swp[i];
        if(cur != swp[i + 1]) {
            cout << (co[i][0] + 1) << ' ' << (co[i + 1][1] + 1) << '\n';
        } else {
            cout << (co[i][0] + 1) << ' ' << (co[i + 1][0] + 1) << '\n';
        }
    }
}
