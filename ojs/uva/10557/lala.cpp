#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 103;
const int M = 2e4+7;

ll dist[N];
int n, es;
int a[M], b[M];
int mark[N];
ll w[M];
vector<int> adj[N];
ll en[N];

void dfs (int u) {
	if (mark[u] == 2)
		return;
	mark[u] = 2;
	for (int v : adj[u])
		dfs(v);
}

int main () {
	while (scanf("%d", &n) != EOF) {
		if (n == -1) break;
		es = 0;
		for (int i = 0; i < n; i++) {
			adj[i].clear();
			dist[i] = 0;
			mark[i] = 0;
			int m;
			scanf("%lld %d", &en[i], &m);
			for (int j = 0; j < m; j++) {
				scanf("%d", &b[es]);
				b[es]--;
				a[es] = i;
				w[es] = en[i];
				adj[i].pb(b[es]);
				es++;
			}

		}
		dist[0] = 100;

		for (int k = 0; k < n; k++) {
			for (int i = 0; i < es; i++) {
				if (dist[a[i]] <= 0) continue;
				dist[b[i]] = max(dist[a[i]] + w[i], dist[b[i]]);
			}
		}
		if (dist[n-1] > 0) {
			printf("winnable\n");
			continue;
		}
		ll x = dist[n-1];
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < es; i++) {
				if (dist[a[i]] <= 0) continue;
				ll cur = dist[b[i]];
				dist[b[i]] = max(dist[a[i]] + w[i], dist[b[i]]);
				if (cur != dist[b[i]])
					mark[b[i]] = 1;
			}
		}
		for (int i = 0; i < n; i++)
			if (mark[i] == 1)
				dfs(i);

		if (mark[n-1] == 2)
			printf("winnable\n");
		else
			printf("hopeless\n");
	}
}
