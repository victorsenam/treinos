#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 1123456;
int d[N], f[N];
vector<int> ps[N], adj[N];
int tempo;

void dfs(int u, int p) {
    d[u] = tempo++;
    for(int v : adj[u]) {
        if(v == p) continue;
        dfs(v, u);
        ps[u].pb(v);
    }
    f[u] = tempo - 1;
}

int bit[N];
void add(int i, int x) {
    for(i += 2; i < N; i += (i & -i))
        bit[i] += x;
}

int get(int i) {
    int sum = 0;
    for(i += 2; i; i -= (i & -i))
        sum += bit[i];
    return sum;
}

inline int get(int a, int b) { return get(b) - get(a - 1); }

int st[N], sn;

int main () {
    int i, n, q, a, b, k;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(i = 0; i < n - 1; i++) {
        cin >> a >> b; a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    st[sn++] = 0;
    vector<int> ord;
    while(sn) {
        int u = st[--sn];
        ord.pb(u);
        d[u] = tempo++;
        for(int v : adj[u]) {
            st[sn++] = v;
            adj[v].erase(search_n(adj[v].begin(), adj[v].end(), 1, u));
            ps[u].pb(v);
        }
    }
    for(int i_ = n - 1; i_ >= 0; i_--) {
        i = ord[i_];

        sort(ps[i].begin(), ps[i].end(), [](int a, int b) { return d[a] < d[b]; });
        f[i] = d[i];
        for(int v : adj[i])
            f[i] = max(f[i], f[v]);
    }
    //dfs(0, -1);
    cin >> q;
    while(q--) {
        cin >> k;
        vector<int> vs;
        for(i = 0; i < k; i++) {
            cin >> a; a--;
            vs.pb(a);
            add(d[a], 1);
        }
        if(k == 1) {
            cout << "0\n";
            add(d[vs.front()], -1);
            continue;
        }
        int ct = 0;
        int x = -1;
        for(int u : vs) {
            int sons = get(d[u], f[u]) - 1;
            if(sons == 0) ct++;
            else if(sons == k - 1)
                x = u;
        }
        if(x != -1) {
            sort(vs.begin(), vs.end(), [](int u, int v) { return d[u] < d[v]; });
            assert(vs.front() == x);
            vs.erase(vs.begin()); // rem x
            add(d[x], -1);
            int l = 0, r = int(ps[x].size()) - 1;
            while(l < r) {
                int m = (l + r + 1) / 2;
                int u = ps[x][m];
                if(d[u] <= d[vs.front()]) l = m;
                else r = m - 1;
            }
            if(d[vs.back()] <= f[ps[x][l]]) ct++;
        }
        cout << ((ct + 1) / 2) << '\n';
        for(int x : vs) add(d[x], -1);
    }
}
