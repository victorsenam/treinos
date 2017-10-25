#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e4+7;

struct edge {
	int a, b, c;
};

ll dist[N];
int n, m;
vector<edge> adj[N];

int solve (int t, int pn) {
	if (t < 0) return 0;
	cout << "================== with time " << t << endl;
	for (int i = 0; i < 2*n; i++)
		dist[i] = -1;
	dist[n-1] = t;
	
	queue<int> qu;
	qu.push(n-1);

	while (!qu.empty()) {
		int u = qu.front()%n;
		int p = qu.front()/n;
		int cur = qu.front();
		qu.pop();

		cout << u << " on " << p << " : " << dist[cur] << endl;

		if (dist[cur] <= 0) continue;

		for (edge ed : adj[u]) {
			int to = ed.b + (!p)*n;
			cout << "to " << ed.b << "(" << to << ") with " << ed.c << endl;
			if (dist[to] != -1) continue;
			if (ed.c > dist[cur] - 1) continue;
			dist[to] = dist[cur] - 1;
			cout << "== got " << dist[to] << endl;
			qu.push(to);
		}
	}

	cout << (dist[pn*n] != -1) <<endl;
	if (dist[pn*n] != -1)
		return 1;
	return 0;
}

int main () {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++)
		dist[i] = -1;

	for (int i = 0; i < m; i++) {
		edge ed;
		scanf("%d %d %d", &ed.a, &ed.b, &ed.c);
		ed.a--; ed.b--;
		adj[ed.a].pb(ed);
		swap(ed.a, ed.b);
		adj[ed.a].pb(ed);
	}
	
	ll hi = 1e9, lo = 0;
	while (lo < hi) {
		ll md = (lo + hi)/2;
		if (solve(md+md, 0))
			hi = md;
		else
			lo = md+1;
	}
	ll res = lo+lo;
	if (!solve(lo+lo,0))
		res = LLONG_MAX;

	hi = 1e9, lo = 0;
	while (lo < hi) {
		ll md = (lo + hi)/2;
		if (solve(md+md+1, 1))
			hi = md;
		else
			lo = md+1;
	}
	if (solve(lo+lo+1,1))
		res = min(res, lo+lo+1);

	if (res == LLONG_MAX)
		res = -1;
	printf("%lld\n", res);

}
