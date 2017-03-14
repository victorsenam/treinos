#include <bits/stdc++.h>

using namespace std;

const int N = 15;
const int M = 20;

vector<pair<int, int> > adj[N];
bool v[N];
int cnt;
int cost[N];
int n, m;
int a, b, c;
int res;

void dfs(int u, int mask) {
	if (v[u])
		return;
	v[u] = 1;
	cnt--;

	for (int i = 0; i < adj[u].size(); i++) {
		if (!(mask&(1<<adj[u][i].second)))
			continue;
		dfs(adj[u][i].first, mask);
	}
}

int main () {
	int t = 0;
	while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
		for (int i = 0; i < n; i++)
			adj[i].clear();

		int mini = 0;
		int sum = 0;
		int res = 0;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			a--; b--;
			adj[a].push_back(make_pair(b, i));
			adj[b].push_back(make_pair(a, i));
			cost[i] = c;
			mini += c;
		}
		sum = mini;
		mini += 10;

		for (int mask = 0; mask < (1 << m); mask++) {
			int custo = 0;
			bool vale = 1;
			for (int i = 0; i < m; i++)
				if (mask&(1<<i))
					custo += cost[i];
			if (mini <= custo)
				continue;

			for (int i = 0; i < n; i++)
				v[i] = 0;
			cnt = n;
			dfs(0, mask);

			if (cnt)
				vale = 0;

			for (int rem = 0; rem < m && vale; rem++) {
				if (!(mask&(1<<rem)))
					continue;

				for (int i = 0; i < n; i++)
					v[i] = 0;
				cnt = n;
				dfs(0, mask - (1<<rem));

				if (cnt)
					vale = 0;
			}

			if (vale) {
				mini = custo;
				res = mask;
			}
		}

		if (mini > sum)
			printf("There is no reliable net possible for test case %d.\n", ++t);
		else
			printf("The minimal cost for test case %d is %d.\n", ++t, mini);
	}
}
