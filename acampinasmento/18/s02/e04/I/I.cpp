#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1123;
int ord[N], seen[N], tempo;

vector<pii> adj[N];

void go(int u) {
	seen[u] = 1;
	for(pii e : adj[u])
		if(!seen[e.first])
			go(e.first);
	ord[u] = tempo++;
}

int b, d;

ll memo[1123][1123];
ll solve(int a, int c) {
	if(a == b && c == d) return 0;
	if(a == c) return INT_MAX;
	ll &r = memo[a][c];
	if(r != -1) return r;
	r = INT_MAX;
	if(a != b && (ord[a] > ord[c] || (c == d))) {
		for(pii e : adj[a])
			r = min(r, e.second + solve(e.first, c));
	} else {
		for(pii e : adj[c])
			r = min(r, e.second + solve(a, e.first));
	}
	return r;
}


int main () {
	int n, m, i;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		int a, b, x;
		scanf("%d %d %d", &a, &b, &x);
		adj[a].pb(pii(b, x));
	}
	for(i = 1; i <= n; i++)
		if(!seen[i])
			go(i);
	int a, c;
	scanf("%d %d %d %d", &a, &b, &c, &d);
	set<int> S;
	for(int x : {a, b, c, d}) S.insert(x);
	memset(memo, -1, sizeof memo);
	if(S.size() < 4 || solve(a, c) >= INT_MAX)
		puts("NIE");
	else printf("%lld\n", solve(a, c));
}
