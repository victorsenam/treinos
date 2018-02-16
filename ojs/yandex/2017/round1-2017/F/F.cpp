#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

vector<int> adj[N];
int n;
int a, b;
queue<int> qu;
set<int> s[N];
int deg[N];

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n-1; i++) {
		scanf("%d %d", &a, &b);
		a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
		deg[i]++;
	}

	for (int i = 0; i < n; i++) {
		if (deg[i] == adj[i].size())
			qu.push(i);
	}

	int rs = 1;
	while (!qu.empty()) {
		int u = qu.front();
		qu.pop();
		
		int mx = 1;
		for (int v : adj[u]) {
			if (deg[v] == adj[v].size()) {
				for (int x : s[v]) {
					if (s[u].find(x) == s[u].end()) {
						s[u].insert(x);
					} else {
						mx = max(mx, x);
					}
				}
			} else {
				deg[v]++;
				if (deg[v] == adj[v].size())
					qu.push(v);
			}
		}

		while (s[u].find(mx) != s[u].end())
			mx++;
		cout << u+1 << ": " << mx << endl;

		s[u].insert(mx);
		rs = max(rs, mx);
		while (*(s[u].begin()) < mx)
			s[u].erase(s[u].begin());
	}

	printf("%d\n", rs);
}
