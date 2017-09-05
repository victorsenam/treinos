#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e3+7;

struct evt {
	int i, s;
	bool op;

	bool operator < (const evt & ot) const {
		if (s != ot.s)
			return s > ot.s;
		if (op != ot.op)
			return !(op);
		return i > ot.i;
	}
};

int m, n, k;
int x[N], y[N], b[N];
ll r[N];

ll sq (ll x) {
	return x*x;
}

ll dist (int a, int b, int c, int d) {
	return sq(a-c) + sq(b-d);
}

int find (int i, int j, int op) {
	int lo, hi;
	if (op) {
		// primeiro aberto
		lo = 1;
		hi = y[j] + 1;

		while (lo < hi) {
			int md = (lo+hi)/2;

			if (dist(i, md, x[j], y[j]) <= r[j]*r[j])
				hi = md;
			else
				lo = md+1;
		}
	} else {
		// ultimo aberto
		lo = y[j]-1;
		hi = m;

		while (lo < hi) {
			int md = (lo+hi+1)/2;

			if (dist(i, md, x[j], y[j]) <= r[j]*r[j])
				lo = md;
			else
				hi = md-1;
		}
	}
	return lo;
}

int main () {
	scanf("%d %d %d", &m, &n, &k);

	for (int i = 0; i < k; i++)
		scanf("%d %d %lld %d", x+i, y+i, r+i, b+i);
	
	ll rs = 0;
	int qt = 0;
	for (int i = 1; i <= n; i++) {
		cout << "x = " << i << endl;
		priority_queue<evt> pq;
		for (int j = 0; j < k; j++) {
			evt s, t;
			s.op = 1; t.op = 0;
			s.i = t.i = j;
			s.s = find(i,j,1);
			t.s = find(i,j,0);

			if (s.s > t.s) continue;
			cout << j << " reaches [" << s.s << "," << t.s << "]" << endl;
			pq.push(s);
			pq.push(t);
		}

		ll ss = 0;
		ll ls = 1;

		while (!pq.empty()) {
			evt cur = pq.top();
			//cout << "\ty = " << cur.s << endl;

			if (cur.s > ls) {
				cout << ss << " in [" << ls << "," << cur.s << ")" << cur.s - ls << endl;
				if (ss > rs) {
					rs = ss;
					qt = cur.s - ls;
				} else if (ss == rs) {
					qt += cur.s - ls;
				}
			}

			while (!pq.empty() && pq.top().s == cur.s && pq.top().op) {
				//cout << "\t\topen " << pq.top().i << endl;
				ss += b[pq.top().i];
				pq.pop();
			}

			cout << ss << " in " << cur.s << " " << 1 << endl;
			if (ss > rs) {
				rs = ss;
				qt = 1;
			} else if (ss == rs) {
				qt++;
			}

			while (!pq.empty() && pq.top().s == cur.s) {
				//cout << "\t\tclose " << pq.top().i << endl;
				ss -= b[pq.top().i];
				pq.pop();
			}

			ls = cur.s + 1;
		}
		
		if (ls > m) continue;
		cout << ss << " in [" << ls << "," << m << "]" << m - ls + 1<< endl;
		if (ss > rs) {
			rs = ss;
			qt = m - ls + 1;
		} else if (ss == rs) {
			qt += m - ls + 1;
		}
	}

	printf("%d\n%d\n", rs, qt);
}
