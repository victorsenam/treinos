#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e5+7;

int nd[N];
int n, q;
vector<int> adj[N];
int pre[N], pos[N], ord;
int sb[2][N][21]; // 0 : spec, 1 : part

bool is_anc (int u, int v) {
	return pre[u] <= pre[v] && pos[v] <= pos[u];
}

int dfs (int u) {
	pre[u] = ord++;
	for (int v : adj[u])
		dfs(v);
	pos[u] = ord++;
}

int main () {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		int pr, ty;
		scanf("%d %d", &pr, &ty);

		if (pr == -1) {
			adj[0].pb(i);
			sb[0][i][0] = sb[1][i][0] = i;
		} else if (ty == 0) {
			adj[pr].pb(i);
			sb[1][i][0] = i;
			sb[0][i][0] = pr;
		} else {
			adj[pr].pb(i);
			sb[0][i][0] = i;
			sb[1][i][0] = pr;
		}
		for (int x = 0; x < 2; x++)
			for (int t = 1; t <= 20; t++)
				sb[x][i][t] = sb[x][sb[x][i][t-1]][t-1];
	}

	dfs(0);

	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		int ty, u, v;
		bool r;
		scanf("%d %d %d", &ty, &u, &v);

		if (u == v) {
			r = 0;
		} else if (ty == 1) {
			r = is_anc(u, v) && sb[0][u][20] == sb[0][v][20];
		} else {
			//v = sb[0][v][20];
			if (is_anc(v,u)) {
				r = 0;
			} else {
				for (int t = 20; t >= 0; t--) {
					int nv = sb[1][v][t];
					if (!is_anc(nv,u))
						v = nv;
				}
				v = sb[1][v][0];
				if (!is_anc(v,u)) 
					r = 0;
				else
					r = is_anc(sb[0][u][20],v);
			}
		}

		if (r)
			printf("YES\n");
		else
			printf("NO\n");
	}

}
