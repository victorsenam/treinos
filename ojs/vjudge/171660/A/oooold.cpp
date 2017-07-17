#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define fst first
#define snd second

const int N = 3123;

int h[N], a[N], b[N], x[N], y[N], r[N];
vector<int> adj[N]; int pr[N], mrk[N], deg[N];
int anc[N][N];

queue<int> q;

ll solve(deque<int> &ret) {
    if(q.empty()) return 0;
    int i = q.front(); q.pop();
    if(pr[i] != -1 && --deg[pr[i]] == 0)
        q.push(pr[i]);
    ll ans = solve(ret);
    vector<int> pos;
    pos.pb(ret.size());
    ll val = 0;
    int ct = 0;
    for(int j = int(ret.size()) - 1; j >= 0; j--) {
        if(anc[i][ret[j]]) ct++;
        ll v = ll((ct + 1) / 2) * a[i] + ll(ct / 2) * b[i];
        if(v > val) { val = v; pos.clear(); }
        else if(v < val) continue;
        pos.pb(j);
    }
    int j = *min_element(pos.begin(), pos.end(), [&ret,i](int a, int b) {
        if(a == b) return false;
        if(a < b) return i < ret[a];
        else return i > ret[b];
    });
    ret.insert(ret.begin() + j, i);
    ans += val;
    return ans;
}

void dfs(int i, int h) {
    ::h[i] = h;
    for(int j : adj[i])
        dfs(j, h + 1);
}

inline ll sq(ll x) { return x * x; }

// is i inside j?
inline bool inside(int i, int j) {
    return r[j] > r[i] && sq(x[i] - x[j]) + sq(y[i] - y[j]) < sq(r[j] - r[i]);
}

int p[N];

void go(int u, int p) {
    anc[u][p] = 1;
    for(int v : adj[u])
        go(v, p);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t, i, n, j;
    cin >> t;
    while(t--) {
        cin >> n;
        for(i = 0; i < n; i++) {
            adj[i].clear(); mrk[i] = 0;
            cin >> x[i] >> y[i] >> r[i] >> a[i] >> b[i];
            p[i] = i; pr[i] = -1; deg[i] = 0;
            for(j = 0; j < n; j++) anc[i][j] = 0;
        }
        sort(p, p + n, [](int i, int j) { return r[i] < r[j]; });
        for(int i_ = 0; i_ < n; i_++) {
            i = p[i_];
            for(j = 0; j < n; j++)
                if(!mrk[j] && inside(j, i)) {
                    mrk[j] = 1;
                    adj[i].pb(j);
                    deg[i]++;
                    pr[j] = i;
                }
        }
        for(i = 0; i < n; i++) go(i, i);
        for(i = 0; i < n; i++)
            if(pr[i] == -1)
                dfs(i, 0);
        deque<int> P;
        for(i = 0; i < n; i++)
            if(deg[i] == 0)
                q.push(i);
        printf("%lld\n", solve(P));
        for(i = 0; i < n; i++)
            printf("%d%c", P[i] + 1, " \n"[i == n - 1]);
    }
}
