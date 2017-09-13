#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 5e4+7;

set<int> s[N];
int n;
vector<int> adj[N];
int deg[N];
int vl[N];
queue<int> qu;

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n-1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;

		adj[a].pb(b);
		adj[b].pb(a);
	}
	deg[0]--;

	for (int i = 0; i < n; i++) {
		if (deg[i] + 1 == adj[i].size())
			qu.push(i);
	}

	int rs = 1;
	while (!qu.empty()) {
		int u = qu.front();
		qu.pop();
		
		cout << "========= abre " << u + 1 << endl;

		int mx = 0;
		for (int v : adj[u]) {
			if (deg[v] + 1 >= adj[v].size()) {
				cout << "filho " << v + 1 << endl;
				for (int x : s[v]) {
					cout << "<- " << x << endl;
					if (s[u].find(x) != s[u].end())
						mx = max(mx, x);
					else
						s[u].insert(x);
				}
			} else {
				cout << "pai " << v + 1 << endl;
				deg[v]++;
				if (deg[v] + 1 == adj[v].size()) {
					qu.push(v);
				}
			}
		}

		while (s[u].find(mx) != s[u].end())
			mx++;

		cout << "val " << mx << endl;

		vl[u] = mx;
		rs = max(rs, mx);

		s[u].insert(mx);
		while (*(s[u].begin()) < mx) {
			cout << "remove " << *(s[u].begin()) << endl;
			s[u].erase(s[u].begin());
		}
	}

	printf("%d\n", rs);
}
