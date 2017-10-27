#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

ll n, m, k;

struct el {
	int v;
	int q;
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
    a.v.reserve(a.v.size() + b.v.size() + 3);
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
    v.v.reserve(n+2);
	for (ll i = 0; i < n; i++) {
		el c;
		c.q = 1;
		scanf("%d", &c.v);
		v.add(c);
	}

	printa();
	while (m > 1 && v.v.size() > 1) {
		if (m&1)
			junta(st,v);
		m /= 2;

		ll szi = v.sz + v.sz;
		junta(v,v);
		printa();

		if (szi == v.sz)
			break;
	}

	if (v.v.size() == 1) {
		el x = v.v.back();
		x.q = (ll(x.q)*m)%k;
		st.add(x);

		v.rem();
		m = 0;
	}

	cout << "---" << endl;
	printa();
	if (v.v.size() == 0 || m == 0) {
		printf("%lld\n", st.sz);
	} else {
		while (st.v.size() && m && v.v.size() && st.v.back().v == v.v.front().v) {
			junta(st,v);
			m--;
		}
		printa();
		printf("%lld\n", st.sz + ll(v.sz) * m);
	}
}
