#include <bits/stdc++.h>

using namespace std;

const int MAX = 110;

vector<int> adj[MAX];
int vis[MAX];

void dfs(int v) {
	vis[v] = 1;
	for(int u : adj[v])
		if(!vis[u]) dfs(u);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int t = 1; t <= T; t++) {
		int n, v[MAX], k;
		scanf("%d%d", &n, &k);
		for(int i = 0; i < n; i++) {
			adj[i].clear();
			vis[i] = 0;
			scanf("%d", &v[i]);			
		}
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				if(abs(v[j] - v[i]) <= k) {
					adj[i].push_back(j);
					adj[j].push_back(i);
				}
			}
		}
		int ans = 0;
		for(int i = 0; i < n; i++) {
			if(!vis[i]) {
				ans++;
				dfs(i);
			}
		}
		printf("Case #%d: %d\n", t, ans);
	}
	return 0;
}
