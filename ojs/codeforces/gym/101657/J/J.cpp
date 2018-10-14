#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 13;

struct edge {
	int a, b;
};

vector<edge> adj[N];
edge ed[N+N];
int v[N];
int n;

int main () {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n;
	for (int i = 0; i < n + n; i++) {
		cin >> v[i];
		v[i]--;
	}

	for (int i = 0; i < n + n; i++) {
		ed[i].a = v[i], ed[i].b = v[(i+1)%(n+n)];
		if (adj[ed[i].a].size() == 0) {
			adj[ed[i].a].resize(4);
			adj[ed[i].a][0] = i;
			adj[ed[i].a][2] = (i+n+n-1)%(n+n);
		} else {

		}
	}
}
