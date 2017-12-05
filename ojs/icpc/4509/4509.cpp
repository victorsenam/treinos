#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 902;
const int K = 32;
const int M = N*6;
const ll INF = 1e16;

int n, m;
ll dist[N];
int grave[K][K], hole[K][K];
vector<int> v;
int from[M], to[M], wg[M];

int main () {
	while (scanf("%d %d", &n, &m) != EOF) {
		if (n == 0 && m == 0) break;
		for (int i = 0; i < n*m; i++) {
			dist[i] = INF;
			grave[i/m][i%m] = hole[i/m][j%m] = 0;
			adj[i].clear();			
		}

		int gs, hs, es = 0;
		scanf("%d", &gs);
		while (gs--) {
			int i, j;
			scanf("%d %d", &i, &j);
			grave[i][j] = 1;
		}
		scanf("%d", &hs);
		while (hs--) {
			int i, j, ni, nj;
			ll w;
			scanf("%d %d %d %d %lld", &i, &j, &ni, &nj, &w);
			hole[i][j] = 1;
			from[es] = i*m+j;
			to[es] = ni*m+nj;
			wg[es] = w;
			es++;
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (grave[i][j] || hole[i][j]) continue;
				for (int k = 0; k < 4; k++) {
					int ni = i + mv[k][0]; int nj = j + mv[k][1];
					
				}
			}
		}

		dist[0] = 0;
		bool rlx = 0;
		
	}

}
