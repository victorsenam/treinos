#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;

int n;
ll ts;

struct task {
	int a;
	ll t;
	int i;

	bool operator < (const task & o) const {
		if (t != o.t) return t < o.t;
		return i < o.i;
	}
} v[N];

set<task> good[2], bad[2];

int main () {
	scanf("%d %lld", &n, &ts);

	for (int i = 0; i < n; i++) {
		scanf("%d %lld", &v[i].a, &v[i].t);
		v[i].i = i;
		bad[0].insert(v[i]);
	}

	sort(v, v+n, [] (task a, task b) { return a.a < b.a; });
	ll mx = 0;

	int l = 0;
	ll tot = 0;
	int mxk = 0;
	for (int k = 1; k <= n; k++) {
		while (l < n && v[l].a <= k) {
			int w = (bad[1].find(v[l]) != bad[1].end());
			good[w].insert(v[l]);
			bad[w].erase(v[l]);
			l++;
		}
		
		task tsk;
		if (good[0].size()) {
			tsk = *good[0].begin();
			good[0].erase(good[0].begin());
			good[1].insert(tsk);
		} else {
			tsk = *bad[0].begin();
			bad[0].erase(bad[0].begin());
			bad[1].insert(tsk);
		}
		tot += tsk.t;

		while (good[0].size() && good[1].size() && good[0].begin()->t < good[1].rbegin()->t) {
			task pt = *good[0].begin();
			task rm = *good[1].rbegin();
			tot += pt.t - rm.t;
			good[0].erase(good[0].begin());
			good[1].erase(prev(good[1].end()));
			good[0].insert(rm);
			good[1].insert(pt);
		}

		while (tot > ts && good[1].size() && bad[0].size() && bad[0].begin()->t < good[1].rbegin()->t) {
			task pt = *bad[0].begin();
			task rm = *good[1].rbegin();
			tot += pt.t - rm.t;
			bad[0].erase(bad[0].begin());
			good[1].erase(prev(good[1].end()));
			bad[0].insert(rm);
			good[1].insert(pt);
		}

		if (tot > ts) break;
		if (good[1].size() > mx) {
			mx = good[1].size();
			mxk = k;
		}
	}
	printf("%lld\n", mx);
	printf("%d\n", mxk);
	sort(v, v+n);
	int q = mxk;
	ll sm = 0;
	for (int i = 0; mx && i < n; i++) {
		if (v[i].a <= mxk) {
			printf("%d ", v[i].i + 1);
			mx--; q--;
			sm += v[i].t;
		}
	}
	assert(mx == 0);
	for (int i = 0; q && i < n; i++) {
		if (v[i].a > mxk) {
			printf("%d ", v[i].i + 1);
			sm += v[i].t;
			q--;
		}
	}
	assert(q == 0);
	assert(sm <= ts);
	printf("\n");
}
