#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;

int ts;
int n;
int sp[N];
double ift[N];
double res;
vector<int> adj[N];

int dfs (int u, int t, int p) {
    res += (1. - 1./double(t+1));
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, t+(sp[u]), u);
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> ts;

    ift[0] = 1;
    for (int i = 1; i < N; i++)
        ift[i] = (ift[i-1]/double(i+1));

    while (ts--) {
        cin >> n;
        res = 0;

        for (int i = 0; i < n; i++) {
            adj[i].clear();
            sp[i] = 0;
        }

        for (int i = 1; i < n; i++) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            adj[a].pb(b);
            adj[b].pb(a);
        }

        int q;
        cin >> q;
        for (int i = 0; i < q; i++) {
            int a;
            cin >> a;
            a--;
            sp[a] = 1;
        }

        dfs(0, 0, 0);
        cout << setprecision(20) << res << endl;
    }
}
