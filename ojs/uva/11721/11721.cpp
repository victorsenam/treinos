#include <bits/stdc++.h>

using namespace std;

const int N = 1007;

int ts, n, m, a, b,  t;
bool sol[N];
vector<pair<int, int> > adj[N];
vector<int> rev[N];
int dist[N];

void dfs (int i) {
	if (sol[i])
		return;
	
	sol[i] = 1;

	for (int j = 0; j < rev[i].size(); j++)
		dfs(rev[i][j]);
}

int main () {
	scanf("%d", &ts);

	for (int cs = 1; cs <= ts; cs++) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++) {
			adj[i].clear();
			dist[i] = 0;
		}

		for (int j = 0; j < m; j++) {
			scanf("%d %d %d", &a, &b, &t);
			adj[a].push_back(make_pair(b, t));
			rev[b].push_back(a);
		}
		int last = -1;

		bool chn, ss;
		ss = 0;
		for (int r = 0; r < n; r++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < adj[i].size(); j++)
					dist[adj[i][j].first] = min(dist[i] + adj[i][j].second, dist[adj[i][j].first]);

		chn = 1;
		while (chn) {
			chn = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < adj[i].size(); j++) {
					int aux = dist[adj[i][j].first];
					if (adj[i][j].second == INT_MAX)
						continue;
					dist[adj[i][j].first] = min(dist[i] + adj[i][j].second, aux);
					if (dist[adj[i][j].first] < aux) {
						chn = ss = 1;
						adj[i][j].second = INT_MAX;
						dfs(i);
					}
				}
			}
		}

		printf("Case %d: ", cs);
		if (ss) {
			int ok = 0;
			for (int i = 0; i < n; i++) {
				if (!sol[i])
					continue;
				if (ok)
					printf(" ");
				else
					ok = 1;
				printf("%d", i);
			}
			printf("\n");
		} else
			printf("impossible\n");
	}
}
