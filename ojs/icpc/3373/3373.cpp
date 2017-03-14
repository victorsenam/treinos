#include <bits/stdc++.h>

using namespace std;

const int S = 13;
const int N = 1003;

int res[N][N];
int v[N];
int m, d, t, a, b, k;
vector<int> adj[N];
map<string, int> mp;
string nam[N];
char temp[S];
string s;
int its[N];

bool my_comp (int a, int b) {
	if (res[a][d-1] == res[b][d-1])
		return nam[a] < nam[b];
	return res[a][d-1] > res[b][d-1];
}

void dfs (int u) {
	if (v[u])
		return;
	
	v[u] = 1;

	res[u][0] = adj[u].size();
	for (int i = 0; i < adj[u].size(); i++) {
		dfs(adj[u][i]);
		for (int j = 1; j < d; j++)
			res[u][j] += res[adj[u][i]][j-1];
	}
}

int main () { 
	scanf("%d", &t);
	for (int tt = 1; tt <= t; tt++) {
		scanf("%d %d", &m, &d);
		mp.clear();

		for (int i = 0; i < m; i++) {
			scanf(" %s", temp);
			
			if (mp.find(temp) == mp.end()) {
				adj[mp.size()].clear();
				a = mp.size();
				nam[mp.size()] = temp;
				mp.insert(make_pair((string) temp, mp.size()));
			} else {
				a = mp[temp];				
			}

			scanf("%d", &k);

			for (int j = 0; j < k; j++) {
				scanf(" %s", temp);
				if (mp.find(temp) == mp.end()) {
					adj[mp.size()].clear();
					b = mp.size();
					nam[mp.size()] = temp;
					mp.insert(make_pair((string) temp, mp.size()));
				} else {
					b = mp[temp];				
				}

				adj[a].push_back(b);
			}
		}

		for (int i = 0; i < mp.size(); i++) {
			its[i] = i;
			for (int j = 0; j < d; j++)
				res[i][j] = 0;
			v[i] = 0;
		}
		
		for (int i = 0; i < mp.size(); i++)
			dfs(i);

		sort(its, its+mp.size(), my_comp);

		printf("Tree %d:\n", tt);
		for (int i = 0; i < mp.size(); i++) {
			if (res[its[i]][d-1] == 0)
				break;
			if (i > 2 && res[its[i]][d-1] != res[its[2]][d-1])
				break;
			printf("%s %d\n", nam[its[i]].c_str(), res[its[i]][d-1]);
		}
		if (t != tt) 
			printf("\n");
	}
}
