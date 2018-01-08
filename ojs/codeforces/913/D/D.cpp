#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;

struct task {
	int a;
	ll t;
	int i;

	bool operator < (const task & o) const {
		if (a != o.a) return a < o.a;
		if (t != o.t) return t > o.t;
		return i < o.i;
	}
} v[N];

set<task> s;
int n;
ll ts;

int main () {
	scanf("%d %lld", &n, &ts);

	for (int i = 0; i < n; i++) {
		scanf("%d %lld", &v[i].a, &v[i].t);
		v[i].i = i;
	}

	sort(v, v+n, [] (task a, task b) { return a.t < b.t; });

	int mx = 0;
	ll tot = 0;
	for (int i = 0; i < n; i++) {
		s.insert(v[i]);
		tot += v[i].t;
		if (tot > ts) break;

		while (s.size() > s.begin()->a) {
			tot -= s.begin()->t;
			s.erase(s.begin());
		}

		mx = max(mx, (int) s.size());
	}

	printf("%d\n%d\n", mx, mx);
	int q = 0;
	for (int i = 0; i < n; i++) {
		if (q < mx && mx <= v[i].a) {
			printf("%d ", v[i].i+1);
			q++;
		}
	}
	printf("\n");
}
