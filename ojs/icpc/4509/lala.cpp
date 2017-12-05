#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 32;
const int mv[4][2] = {
	{1,0}, {0,1}, {-1,0}, {0,-1}
};
const ll INF = 1e15;

int n, m;
bool gr[N][N];
pii hl[N*N][2];
ll hs[N*N];
ll dist[N][N];

bool in (int i, int j) {
	if (i < 0 || i >= n || j < 0 || j >= m) return 0;
	return 1;
}

int main () {
	while (scanf("%d %d", &n, &m) != EOF) {
		if (!n && !m) return 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				gr[i][j] = 0;
				dist[i][j] = INF;
			}
		dist[0][0] = 0;
		int g;
		scanf("%d", &g);
		while (g--) {
			int i,j;
			scanf("%d %d", &i, &j);
			gr[i][j] = 1;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (gr[i][j]) continue;
				for (int k = 0; k < 4; k++) {
					int ni = i + mv[k][0];
					int nj = j + mv[k][1];
				}
			}
		}

		scanf("%d", &g);
		for (int k = 0; k < g; k++) {
			for (int l = 0; l < 2; l++) {
				scanf("%lld %lld", &hl[k][l].first, &hl[k][l].second);
			}
			scanf("%lld", &hs[k]);
		}

		bool rlx = 0;
		for (int k = 0; k < n*m + 4; k++) {
			rlx = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					if (gr[i][j] || dist[i][j] == INF) continue;
					for (int l = 0; l < 4; l++) {
						int ni = i+mv[l][0];
						int nj = j+mv[l][1];
						if (in(ni,nj)) {
							ll x = dist[ni][nj];
							dist[ni][nj] = min(dist[ni][nj], dist[i][j] + 1);
							if (x != dist[ni][nj]) {
								//cout << ni << " " << nj << " : " << dist[ni][nj] << endl;
								rlx = 1;
							}
						}
					}
				}
			}
			for (int l = 0; l < g; l++) {
				int i = hl[l][0].first, j = hl[l][0].second, ni = hl[l][1].first, nj = hl[l][1].second, s = hs[l];
				if (dist[i][j] == INF) continue;
				ll x = dist[ni][ni];
				dist[ni][nj] = min(dist[ni][nj], dist[i][j] + s);
				if (x != dist[ni][nj]) {
					//cout << ni << " " << nj << " : " << dist[ni][nj] << "!" << endl;
					rlx = 1;
				}
			}
		}

		if (rlx) printf("Never\n");
		else if (dist[n-1][m-1] == INF) printf("Impossible\n");
		else printf("%lld\n", dist[n-1][m-1]);
	}
}
