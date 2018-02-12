#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 80;
const ll INF = 1e12;

int n, m;
bool conn[N][N];
ll dist[N][N];

int main () {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			dist[i][j] = INF;
		dist[i][i] = 0;
	}

	for (int i = 0; i < m; i++) {
		int a, b;
		ll t;
		scanf("%d %d %lld", &a, &b, &t);
		a--; b--;
		dist[a][b] = min(dist[a][b],t);
		dist[b][a] = min(dist[b][a],t);
		conn[a][b] = conn[b][a] = 1;
	}
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);

	ll opt = INF;
	for (int a = 0; a < n; a++) {
		for (int b = 0; b < n; b++) {
			ll diam = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					diam = max(diam, min({ dist[i][j], dist[i][a] + dist[b][j], dist[i][b] + dist[a][j] }));
				}
			}
			opt = min(opt, diam);
		}
	}

	if (opt == INF) {
		printf("-1.00000 -1.00000\n");
		return 0;
	}

	ll chg = 0;
	for (int a = 0; a < n; a++) {
		for (int b = 0; b < n; b++) {
			ll diam = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					diam = max(diam, min({ dist[i][j], dist[i][a] + dist[b][j], dist[i][b] + dist[a][j] }));
				}
			}
			if (diam == opt) {
				ll curc = INF;
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						if (dist[i][j] > diam)
							curc = min(curc, max({ diam - dist[i][a] - dist[b][j], diam - dist[i][b] - dist[a][j] }));
					}
				}
				chg = max(curc,chg);
			}
		}
	}

	if (chg == INF) chg = -1;
	printf("%lld.00000 %lld.00000\n", opt, chg);
}
