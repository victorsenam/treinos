#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

int ts;
int n, m;
vector<int> adj[N], inv[N];
int ls[N];
int vs[500], turn;
char v[N];

int main () {
	scanf("%d", &ts);

	while (ts--) {
		scanf("%d %d", &n, &m);

		for (int i = 0; i <= n; i++) {
			v[i] = 0;
			ls[i] = 0;
			adj[i].clear();
			inv[i].clear();
		}

		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d %d", &a, &b);

			adj[a].pb(b);
			inv[b].pb(a);
		}

		int cs = 0;
		for (int i : adj[0])
			v[i] = ++cs;

		bool ok = 1;
		for (int i = 1; i <= n; i++) {
			if (v[i] == 0) {
				ok = 0;
			} else {
				for (int j : inv[i])
					ok &= (j >= ls[v[i]]);
			}

			for (int j : adj[i]) {
				if (!v[j])
					v[j] = v[i];
			}

			ls[v[i]] = i;
			//cout << i << " " << ok << endl;
		}

		int cnt = 0;
		for (int i = 0; i <= n; i++)
			ls[i] = n+1;

		for (int i = n; i >= 0; i--) {
			ok &= (adj[i].size() == cnt);
			for (int j : adj[i])
				ok &= (ls[v[j]] == j);
			if (ls[v[i]] == n+1)
				cnt++;
			ls[v[i]] = i;
		}

		if (!ok)
			printf("-1\n");
		else {
			for (int i = 1; i <= n; i++)
				printf("%d ", v[i]);
			printf("\n");
		}
	}
}
