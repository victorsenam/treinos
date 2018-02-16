#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int K = 22;
const int N = 400123;

int lca[N][K];
ll wei[N][K];
ll sum[N][K];
ll w[N];
int q;
int u = 2;

int main () {
	scanf("%d", &q);

	w[0] = 1e15; w[0] += 2;
	w[1] = 0;
	for (int k = 0; k < K; k++) {
		wei[0][k] = wei[1][k] = w[0];
		sum[0][k] = sum[1][k] = w[0];
	}

	ll last = 0;
	while (q--) {
		ll ty, p, q;
		scanf("%lld %lld %lld", &ty, &p, &q);
		p ^= last; q ^= last;
		//cout << "Query: " << ty << " " << p << " " << q << endl;
		if (ty == 1) {
			w[u] = q;
			
			for (int k = K-1; k >= 0; k--) {
				if (wei[p][k] < w[u])
					p = lca[p][k];
			}
			while (w[p] < w[u]) p = lca[p][0];
			//assert(w[p] >= w[u]);
			//cout << u << " below " << p << endl;

			lca[u][0] = p;
			wei[u][0] = max(w[u],w[p]);
			sum[u][0] = w[p];
			//cout << "[" << w[p] << "(" << p << ")";
			for (int k = 1; k < K; k++) {
				lca[u][k] = lca[lca[u][k-1]][k-1];
				wei[u][k] = max(wei[u][k-1], wei[lca[u][k-1]][k-1]);
				sum[u][k] = sum[u][k-1] + sum[lca[u][k-1]][k-1];
				//cout << " " << sum[u][k] << "(" << lca[u][k] << ")";
			}
			//cout << "]" << endl;
			u++;
		} else {
			int ans = 0;
			ll ss = w[p];
			if (ss <= q) {
				ans++;
				for (int k = K-1; k >= 0; k--) {
					if (ss + sum[p][k] <= q) {
						ss += sum[p][k];
						p = lca[p][k];
						ans += (1<<k);
					}
				}
				while (ss + w[lca[p][0]] <= q) {
					p = lca[p][0];
					ss += w[p];
					ans++;
				}
				//assert(ss + sum[p][0] > q);
			}
			printf("%d\n", ans);
			last = ans;
		}
	}
}
