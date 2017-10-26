#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n, k, m;

struct el {
	int v, q;

};

struct seq {
	vector<el> v;
	int sz;

	void add (el x) {
		sz += el.q;
		if (v.size() && el.v == v.back().x)
			v.back().q += el.q;
		
		sz -= v.back().q/k;
		v.back().q %= k;
	}
};

vector<int> v, st;

vector<int> man (vector<int> & a) {
	vector<int> r;
	int ls = 0;
	for (int i = 0; i < a.size(); i++) {
		if (r.size() && a[i] == r.back())
			ls++;
		else
			ls = 1;
		r.push_back(a[i]);
		if (ls == k) {
			while (ls) {
				r.pop_back();
				ls--;
			}
			while (r.size() > ls && r[r.size()-1-ls] == r.back())
				ls++;
		}
	}
	return r;
}

void junta (vector<int> & a, vector<int> & b) {
	for (int x : b)
		a.pb(x);
}

bool alleq (vector<int> & a) {
	for (int i = 0; i < a.size() - 1; i++)
		if (a[i] != a[i+1])
			return 0;
	return 1;
}

void printa () {
	cout << "(";
	for (int x : st)
		cout << x << " ";
	cout << ") + " << m << "*(";
	for (int x : v)
		cout << x << " ";
	cout << ")" << endl;
}

int main () {
	scanf("%d %d %d", &n, &k, &m);

	v.resize(n);
	for (int i = 0; i < n; i++)
		scanf("%d", &v[i]);
	v = man(v);
	printa();

	while (m > 1 && v.size()) {
		if (m&1)
			junta(st, v);

		vector<int> jn = v;
		junta(jn,v);
		v = man(jn);
		m /= 2;

		printa();
		if (jn == v)
			break;
	}

	st = man(st);
	printa();

	if (v.empty()) {
		printf("%lld\n", ll(st.size()));
		return 0;
	}

	if (alleq(v)) {	
		ll cnt = ll(v.size()) * m;
		while (v.size() && st.size() && v.front() == st.back()) {
			cnt++;
			st.pop_back();
		}
		printf("%lld\n", (cnt%k) + st.size());
	} else {
		ll cnt = 0;
		deque<int> cur;
		while (((m && v.size()) || cur.size()) && st.size() && !cnt) {
			int now = st.back();
			while (st.back() == now) {
				st.pop_back();
				cnt++;
			}

			while ((m && v.size()) || cur.size()) {
				if (cur.empty()) {
					for (int x : v)
						cur.push_back(x);
					m--;
				}

				if (cur.front() != now)
					break;
				else {
					cur.pop_front();
					cnt++;
				}
			}

			cnt %= k;
		}

		printf("%lld\n", cnt + ll(st.size()) + ll(cur.size()) + ll(v.size())*m);
	}
}
