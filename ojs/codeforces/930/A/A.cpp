#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

int n;
vector<int> adj[N];
int lv[N];

int dfs (int u, int l) {
	lv[l]++;
	for (int v : adj[u])
		dfs(v,l+1);
}

int main () {
	scanf("%d", &n);
	
	for (int i = 1; i < n; i++) {
		int a;
		scanf("%d", &a);
		adj[a-1].pb(i);
	}

	dfs(0,0);
	int q = 0;
	for (int i = 0; i <= n; i++)
		q += (lv[i]&1);

	printf("%d\n", q);
}
