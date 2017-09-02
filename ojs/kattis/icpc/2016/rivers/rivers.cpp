#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

char name[N][20];
ll len[N];
int n, m;
vector<ll> vt;
vector<int> adj[N];
ll rs[N];
ll mx[N];
int ans[N];
int p[N];
int q[N];

struct path {
	int u;
	ll len;

	bool operator < (const path & ot) const {
		if (len != ot.len)
			return len < ot.len;
		return u < ot.u;
	}
} res[N];

set<path> evt;
vector<int> esco[N];
int chs[N];

path dfs (int u, ll x) {
	mx[u] = x;
	res[u] = path({u,0});

	for (int v : adj[u]) {
		path cur = dfs(v, x + len[v]);

		if (res[u].u == u || res[u].len > cur.len)
			res[u] = cur;
	}

	cout << "from " << u << endl;
	for (int v : adj[u]) {
		if (res[v].u != res[u].u) {
			evt.insert(res[v]);
			cout << "add " << res[v].len << endl;
			esco[u].pb(v);
		} else {
			cout << "chose " << v << endl;
			chs[u] = v;
		}
	}

	res[u].len += len[u];
	sort(esco[u].begin(), esco[u].end(), [] (int a, int b) {
		return res[b] < res[a];
	});
	return res[u];
}

int main () {
	scanf("%d %d", &n, &m);

	len[0] = 0;
	for (int i = m + 1; i <= n + m; i++) {
		scanf(" %s %d %lld", name[i], &p[i], &len[i]);
		q[i-m-1] = i;
		adj[p[i]].pb(i);
	}

	for (int i = 1; i <= m; i++) {
		scanf("%d %lld", &p[i], &len[i]);
		adj[p[i]].pb(i);
	}

	dfs(0,0);
	evt.insert(res[0]);
	cout << "add " << res[0].len << endl;

	sort(q, q + n, [] (int i, int j) {
		return mx[i] > mx[j];
	});

	int grt = 0;
	for (int _i = 0; _i < n; _i++) {
		int i = q[_i];
		cout << "processing " << string(name[i]) << " " << mx[i] << endl;
		
		while (!evt.empty() && evt.rbegin()->len > mx[i]) {
			path cur = *prev(evt.end());
			evt.erase(prev(evt.end()));

			cout << "==== longest had len " << cur.len << " ====" << endl;

			if (esco[cur.u].empty()) {
				if (cur.u && chs[p[cur.u]] == cur.u) {
					cout << "wait" << endl;
					evt.insert(path({p[cur.u], cur.len}));
				} else {
					cout << "can't be changed" << endl;
					grt++;
				}
			} else {
				int v = esco[cur.u].back();
				esco[cur.u].pop_back();
				cout << "change " << cur.u << " from " << chs[cur.u] << " to " << v;

				if (evt.find(res[v]) == evt.end()) {
					cout << " [reborn]" << endl;
					grt--;
				} else {
					evt.erase(res[v]);
				}

				evt.insert(res[chs[cur.u]]);
				res[cur.u] = path({cur.u, res[v].len + len[cur.u]});
				evt.insert(res[cur.u]);
				cout << " detached len " << res[chs[cur.u]].len << " and created len " << res[cur.u].len << endl;
				chs[cur.u] = v;
			}
		}

		ans[i] = grt + 1;
	}

	for (int i = m + 1; i <= n + m; i++)
		printf("%s %d\n", name[i], ans[i]);
}
