#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll n, m, k;

struct el {
	int v;
	ll q;
};

struct seq {
	vector<el> v;
	ll sz;

	void add (el x) {
		sz += x.q;
		if (v.size() && x.v == v.back().v)
			v.back().q += x.q;
		else
			v.pb(x);
		
		sz -= v.back().q;;
		v.back().q %= k;
		sz += v.back().q;
		if (v.back().q == 0)
			v.pop_back();
	}

	void rem () {
		sz -= v.back().q;
		v.pop_back();
	}
};

seq v, st;

void junta (seq & a, seq b) {
	for (el x : b.v)
		a.add(x);
}

void printa (seq a) {
	for (el x : a.v)
		cout << "(" << x.v << " " << x.q << ")";
}

void printa () {
	return;
	printa(st);
	cout << " + " << m << "*";
	printa(v);
	cout << endl;
}

int main () {
	scanf("%lld %lld %lld", &n, &k, &m);

	for (ll i = 0; i < n; i++) {
		el c;
		c.q = 1;
		scanf("%d", &c.v);
		v.add(c);
	}

	printa();
	while (m > 1 && v.v.size() > 1) {
		ll szi = v.sz;
		junta(v,v);
		printa();

		v.sz /= 2
		v.v.resize(v.v.size()/2);

		if (szi == v.sz)
			break;
	}

	if (v.v.size() == 1) {
		printf("%lld\n", (v.sz * m)%k);
	} else {
		printf("%lld\n", v.sz * m);
	}
}
