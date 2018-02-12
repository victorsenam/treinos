#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 102;
int n, m;
vector<pii> adj[N];
char memo[N][N][26];

int pd (int u, int v, int c) {
	char & me = memo[u][v][c];
	if (me != -1) return me;
	me = 0;
	for (pii ed : adj[u]) if (c <= ed.second) {
		if (!pd(v,ed.first,ed.second))
			me = 1;
	}
	return me;
}

int main () {
	memset(memo, -1, sizeof memo);

	scanf("%d %d", &n, &m);

	for (int i = 0; i < m; i++) {
		int a, b; char c;
		scanf("%d %d %c", &a, &b, &c); a--; b--; c -= 'a';
		adj[a].pb(pii(b,c));
	}

	for (int i = 0; i < n; i++, printf("\n")) {
		for (int j = 0; j < n; j++)
			printf("%c", 'A' + !pd(i,j,0));
	}
}
