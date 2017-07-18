#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 2e3+7;

int ts;
int n;
ll x[N], y[N], r[N], a[N], b[N];
int p[N], mrk[N];
vector<int> adj[N];
vector<int> ord;

void dfs (int u) {
    ord.pb(u);
    for (int v : adj[u])
        dfs(v);
}

ll sq (ll x)
{ return x*x; }

ll dist (int i, int j) {
    return sq(x[i] - x[j]) + sq(y[i] - y[j]);
}

bool inside (int i, int j) { // i is inside j?
    return (r[j] > r[i] && dist(i,j) <= sq(r[i] - r[j]));
}

bool isbest (int i, int j, vector<int> & res, int x) { // i é melhor q j?
    if (i < j) {
        return x < res[i];
    } else {
        return res[j] < x;
    }
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
            mrk[i] = 0;
        }

        sort(p, p+n, [] (int i, int j) { return r[i] < r[j]; });

        for (int _i = 0; _i < n; _i++) {
            int i = p[_i];
            for (int j = 0; j < n; j++) {
                if (mrk[j]) continue;
                if (inside(j,i)) {
                    mrk[j] = 1;
                    adj[i].push_back(j);
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (mrk[i]) continue;
            dfs(i);
        }

        vector<int> res;
        ll val = 0;
        for (int u : ord) {
            ll cur = 0;
            int ps = n;

            ll cnt = 0;

            for (int i = res.size()-1; i >= 0; i--) {
                if (inside(u,res[i]))
                    cnt++;

                ll loc = ((cnt+1)/2) * a[u] + (cnt/2) * b[u];
                
                if (loc > cur || (loc == cur && isbest(i,ps,res,u))) {
                    cur = loc;
                    ps = i;
                }
            }

            val += cur;

            res.pb(u);
            for (int i = int(res.size()) - 2; i >= ps; i--)
                swap(res[i], res[i+1]);
        }

        cout << val << endl;
        for (int u : res)
            cout << u + 1 << " ";
        cout << endl;
    }
}
