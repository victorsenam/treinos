#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 1e5+7;

int n, m;
vector<int> adj[N];

struct trouxa {
	double dist;
	int k;
	double sum;
	int i;
	int done;

	void calc () {
		dist = (sum + m)/k;
	}

	bool operator < (const trouxa & o) const {
		if (dist != o.dist)
			return dist < o.dist;
		return i < o.i;
	}
};

trouxa v[N];
set<trouxa> s;
double sum[N];
int k[N];

int main() {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;

		adj[a].pb(b);
		adj[b].pb(a);
	}
	
	for (int i = 0; i < n; i++) {
		v[i].i = i;
		v[i].dist = 1./0.;
		v[i].done = 0;
		v[i].k = v[i].sum = 0;

		if (i == n-1)
			v[i].dist = 0;

		s.insert(v[i]);
	}

	while (!s.empty()) {
		trouxa cur = *(s.begin());
		s.erase(s.begin());

		if (cur.done) continue;
		cur.done = 1;
		v[cur.i].done = 1;

		for (int u : adj[cur.i]) {
			trouxa novo = v[u];
			if (novo.done) continue;
			sum[u] += cur.dist;
			k[u]++;
			novo.sum = sum[u];
			novo.k = k[u];
			novo.calc();
			if (novo.dist >= v[u].dist)
				continue;
			s.erase(v[u]);
			v[u] = novo;
			s.insert(v[u]);
		}
	}

	printf("%.20f\n", v[0].dist);
}
