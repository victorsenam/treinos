#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;

int bit[N];

void add (int i, int x) {
	for (i += 2; i < N; i+=(i&-i))
		bit[i] += x;
}

int get (int i) {
	int x = 0;
	for (i += 2; i > 0; i-=(i&-i))
		x += bit[i];
	return x;
}

struct query {
	int to, type;

};

vector<query> qr[N];
int rs[N][3][3];
int l[N], d[N], r[N], u[N];
int n, q;
int p[N];

int main () {
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++)
		scanf("%d", &p[i]);
	
	for (int i = 0; i < q; i++) {
		scanf("%d %d %d %d", &l[i], &d[i], &r[i], &u[i]);

		qr[l[i]-1].pb(query({i,0}));
		qr[r[i]].pb(query({i,1}));
		qr[n].pb(query({i,2}));
	}

	for (int i = 1; i <= n; i++) {
		add(p[i],1);

		for (query q : qr[i]) {
			rs[q.to][q.type][0] = get(d[q.to]-1);
			rs[q.to][q.type][1] = get(u[q.to]) - rs[q.to][q.type][0];
			rs[q.to][q.type][2] = i - rs[q.to][q.type][1] - rs[q.to][q.type][0];
		}
	}

	for (int i = 0; i < q; i++) {
		for (int a = 2; a > 0; a--)
			for (int b = 0; b <= 2; b++)
				rs[i][a][b] -= rs[i][a-1][b];
		ll cn = 0;

		// dentro
		ll tot = n - rs[i][1][1];
		cn += tot * ll(rs[i][1][1]); // dentro com fora
		cn += ll(rs[i][1][1])*ll(rs[i][1][1]-1)/2ll; // dentro com dentro

		// esquerda
		tot -= ll(rs[i][0][0] + rs[i][0][1] + rs[i][0][2]);
		cn += ll(rs[i][0][1])*tot; // meio com resto
		cn += ll(rs[i][0][0])*ll(tot - rs[i][1][0] - rs[i][2][0]); // baixo
		cn += ll(rs[i][0][2])*ll(tot - rs[i][1][2] - rs[i][2][2]); // cima

		// direita
		tot = rs[i][1][0] + rs[i][1][2];
		cn += ll(rs[i][2][1])*tot; // meio
		cn += ll(rs[i][2][0])*ll(rs[i][1][2]);
		cn += ll(rs[i][2][2])*ll(rs[i][1][0]);

		cn += ll(rs[i][1][0])*ll(rs[i][1][2]);
		printf("%lld\n", cn);
	}
}
