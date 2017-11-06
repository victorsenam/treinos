#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 15;
const int M = (1<<N);

struct Disc {
	int i; double p;
};

struct node {
	int u; double d;

	bool operator < (const node & o) const {
		if (d != o.d) return d > o.d;
		return u < o.u;
	}
};

int turn;
double dist[M];
int visi[M];
int n;
ll p[N], a[N];
vector<Disc> disc[N];
double dt[N];

int main () {
	while (scanf("%d", &n) != EOF) {
		if (!n) break;

		for (int i = 0; i < n; i++) {
			int k;
			scanf("%lld %lld %d", &p[i], &a[i], &k);
			disc[i].clear();

			while (k--) {
				Disc c;
				scanf("%d %lf", &c.i, &c.p);
				c.i--;
				c.p = (100. - c.p)/100.;
				disc[i].pb(c);
			}
		}

		for (int i = 0; i < (1<<n); i++) {
			dist[i] = 1./0.;
		}

		double res = 1./0.;
		dist[0] = 0;
		for (int u = 0; u < (1<<n); u++) {
			double ar = 0;
			for (int i = 0; i < n; i++) {
				dt[i] = p[i];
			}

			for (int i = 0; i < n; i++) {
				if (u&(1<<i)) {
					ar += a[i];
					for (Disc d : disc[i])
						dt[d.i] *= d.p;
				}
			}

			if (u) {
				res = min(res, dist[u]/ar);
			}
			
			for (int i = 0; i < n; i++) {
				if (u&(1<<i)) continue;
				node nx({ u | (1<<i), dist[u] + dt[i] });
				dist[nx.u] = min(dist[nx.u], nx.d);
			}
		}
		printf("%.4f\n",res);
	}
}
