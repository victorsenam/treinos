#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 34;
const ll INF = 1e16;
const int mv[4][2] = {
	{1,0},{0,1},{-1,0},{0,-1}
};

int n, m;
int gr[N][N], hl[N][N];
ll ed[N*N][5];
ll dist[N][N];

void relax (ll & a, ll b, bool & c) {
	if (a > b) { 
		a = b;
		c = 1;
	}
}

int main () {
	while (scanf("%d %d", &n, &m) != EOF) {
		if (n == 0 || m == 0) return 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				gr[i][j] = 0;
				hl[i][j] = 0;
				dist[i][j] = INF;
			}
		}
		dist[0][0] = 0;

		int gs;
		scanf("%d", &gs);
		while (gs--) {
			int i, j;
			scanf("%d %d", &i, &j);
			gr[i][j] = 1;
		}
		
		int tps;
		scanf("%d", &tps);
		for (int t = 0; t < tps; t++) {
			for (int i = 0; i < 5; i++)
				scanf("%lld", &ed[t][i]);
			hl[ed[t][0]][ed[t][1]] = 1;
		}

		bool rlx = 1;
		for (int tt = 0; tt <= 2*n*m + 3; tt++) {
			rlx = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					if (hl[i][j] || gr[i][j] || dist[i][j] == INF || (i == n-1 && j == m-1)) continue;
					for (int k = 0; k < 4; k++) {
						int ni = i + mv[k][0];
						int nj = j + mv[k][1];
						if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
						if (gr[ni][nj]) continue;
						relax(dist[ni][nj], dist[i][j] + 1, rlx);
					}
				}
			}

			for (int t = 0; t < tps; t++) {
				int i = ed[t][0], j = ed[t][1];
				if (dist[i][j] == INF) continue;
				int ni = ed[t][2], nj = ed[t][3];
				relax(dist[ni][nj], dist[i][j] + ed[t][4], rlx);
			}
		}

		if (rlx) printf("Never\n");
		else if (dist[n-1][m-1] == INF) printf("Impossible\n");
		else printf("%lld\n", dist[n-1][m-1]);
	}
}
