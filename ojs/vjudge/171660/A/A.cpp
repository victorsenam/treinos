#include <bits/stdc++.h>
using namespace std;
#define debug if (0)

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e3+7;

int ts;
int n;
ll x[N], y[N], r[N], a[N], b[N];
int p[N], mrk[N];
int deg[N];
vector<int> adj[N];
vector<int> ord;

vector<int> edg[N];

bool isbest (int i, int j, vector<int> & res, int x) { // i é melhor q j?
    if (i < j) {
        return x < res[i];
    } else {
        return res[j] < x;
    }
}

ll dfs (int u) {
    ll val = 0;
    int ps = ord.size();

    for (int i = 0; i < ord.size(); i++) {
        ll loc = (ll(ord.size() - i + 1)/2)*a[u] + (ll(ord.size() - i)/2)*b[u];
        debug cout << u + 1 << " ? (" << loc << "," << i << ")" << endl;
        if (loc > val || (loc == val && isbest(i, ps, ord, u))) {
            val = loc;
            ps = i;
        }
    }

    debug cout << u + 1 << " = (" << val << "," << ps << ")" << endl;

    if (ps < ord.size()) {
        edg[u].pb(ord[ps]);
        deg[ord[ps]]++;
    }
    if (ps > 0) {
        edg[ord[ps-1]].pb(u);
        deg[u]++;
    }

    ord.insert(ord.begin() + ps, u);
    for (int v : adj[u])
        val += dfs(v);
    assert(*(ord.begin() + ps) == u);
    ord.erase(ord.begin() + ps);

    return val;
}

ll sq (ll x)
{ return x*x; }

ll dist (int i, int j) {
    return sq(x[i] - x[j]) + sq(y[i] - y[j]);
}

bool inside (int i, int j) { // i is inside j?
    return (r[j] > r[i] && dist(i,j) <= sq(r[i] - r[j]));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> ts;
    while (ts--) {
        cin >> n;
        ord.clear();
        for (int i = 0; i < n; i++) {
            cin >> x[i] >> y[i] >> r[i] >> a[i] >> b[i];
            p[i] = i;

            adj[i].clear();
            edg[i].clear();
            deg[i] = 0;
            mrk[i] = 0;
        }

        sort(p, p+n, [] (int i, int j) { return r[i] < r[j]; });

        for (int _i = 0; _i < n; _i++) {
            int i = p[_i];
            for (int j = 0; j < n; j++) {
                if (mrk[j] || i == j) continue;
                if (inside(j,i)) {
                    mrk[j] = 1;
                    adj[i].push_back(j);
                }
            }
        }

        debug {
            cout << "tree" << endl;
            for (int i = 0; i < n; i++) {
                cout << i+1 << ":"; 
                for (int v : adj[i]) {
                    cout << " " << v+1;
                }
                cout << endl;
            }
        }

        ll val = 0;
        for (int i = 0; i < n; i++) {
            if (mrk[i]) continue;
            val += dfs(i);
        }
        cout << val << endl;
        
        priority_queue<int> qu;
        for (int i = 0; i < n; i++) {
            if (deg[i] == 0)
                qu.push(-i);
        }

        bool ok = 0;
        int cnn = 0;
        while (!qu.empty()) {
            cnn++;
            int u = qu.top();
            qu.pop();
            if (ok)
                cout << " ";
            ok = 1;
            cout << -u + 1;

            for (int v : edg[-u]) {
                deg[v]--;
                if (!deg[v])
                    qu.push(-v);
            }
        }
        assert(cnn == n);
        cout << endl;
    }
}
