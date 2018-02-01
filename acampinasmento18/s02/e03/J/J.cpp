#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 200123;
int n, m;
ll t[N], d[N];
int p[N];
ll qt[N];
ll res[N];

ll ca, cb;

struct evt { 
	ll t; int i;

	bool operator < (const evt & o) const {
		return (t!=o.t)?t<o.t:i<o.i;
	}
};

set<evt> pq;

void cost (int i, bool inc) {
	if (inc) {
		cb += t[i]*qt[i];
		ca += (qt[i]-1)*qt[i]/2;
	} else {
		cb -= t[i]*qt[i];
		ca -= (qt[i]-1)*qt[i]/2;
	}
}

void rem (int i) {
	//cout << "- " << i << " and " << qt[i] << endl;
	cost(i,0);
	int j = i+qt[i];
	if (j <= n) pq.erase({(t[j]-t[i]+qt[i]-1)/qt[i],i});
}

void add (int i) {
	//cout << "+ " << i << " and " << qt[i] << endl;
	cost(i,1);
	int j = i+qt[i];
	if (j <= n) { /*cout << "to " << (t[j]-t[i])/qt[i] << endl;*/ pq.insert({(t[j]-t[i]+qt[i]-1)/qt[i],i}); }
}

int main () {
	scanf("%d %d", &n, &m);

	ll sum = 0;
	t[0] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &t[i]);
		sum -= t[i];
	}
	for (int i = 0; i < m; i++) {
		scanf("%lld", &d[i]);
		p[i] = i;
	}

	sort(p,p+m,[](int i, int j) { return d[i] < d[j]; });

	for (int i = 0; i <= n; i++) {
		qt[i] = 1;
		add(i);
	}

	for (int _i = 0; _i < m; _i++) {
		int i = p[_i];

		while (pq.size() && pq.begin()->t <= d[i]) {
			evt cur = *pq.begin();
			int a = cur.i, b = cur.i + qt[cur.i];
			//cout << "join " << a << " and " << b << endl;
			rem(a);
			rem(b);
			qt[a] += qt[b];
			add(a);
		}

		res[i] = ca*d[i] + cb;
	}
	for (int i = 0; i < m; i++) printf("%lld\n", res[i]+sum);
}
