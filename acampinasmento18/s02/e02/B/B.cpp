#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;
int n, m;

vector<int> adj[N];
int visi[N], turn;

void dfs (int u) {
	if (visi[u] == 2) return;
	cout << "open " << u << endl;
	if (visi[u] == 1) {
		printf("NIE\n");
		exit(0);
	}
	visi[u] = 1;
	for (int v : adj[u]) {
		dfs(v);
	}
	cout << "close " << u << endl;
	visi[u] = 2;
}

int main () {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < m; i++) {
		int a, b;
		char s, t;
		scanf(" %c %d %c %d", &s, &a, &t, &b);
		a--; b--;

		if (s == '-') a += n;
		if (t == '+') b += n;

		cout << a << "-> " << b << endl;
		cout << (b+n)%(n+n) << "-> " << (a+n)%(n+n) << endl;
		adj[a].pb(b);
		adj[(b+n)%(n+n)].pb((a+n)%(n+n));
	}

	for (int i = 0; i < n+n; i++)
		dfs(i);

	printf("TAK\n");
}
