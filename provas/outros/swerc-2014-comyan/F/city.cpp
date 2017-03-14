#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 50009;
int x[MAX], y[MAX], w[MAX], h[MAX];
struct ev {
	int x, i;
	bool in;
	ev() {}
	ev(int a, bool b, int c) : x(a), in(b), i(c) {}
	bool operator < (ev o) const {
		if(x != o.x) return x < o.x;
		if(in != o.in) return in < o.in;
		return y[i] < y[o.i];
	}
};

struct cmp {
	bool operator()(int a, int b) {
		return y[a] < y[b];
	}
};

bool touch(int i, int j) {
	if (y[i] > y[j])
		swap(i, j);
	if (y[i] + h[i] == y[j])
		return 1;
	//if (x[i]+w[i] == x[j]) {
	//	if (y[i]<=y[j] && y[i]+h[i]>=y[j])
	//		return 1;
	//	if (y[j]<=y[i] && y[j]+h[j]>=y[i])
	//		return 1;
	//}
	return 0;
}

int S[MAX], sz[MAX]; ll ar[MAX];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}
void join(int a, int b) {
	int ba = a, bb = b;
	if((a = find(a)) == (b = find(b))) return;
	//printf("joining %d and %d\n", ba, bb);
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	ar[a] += ar[b];
	S[b] = a;
}
int ys[MAX << 2];
int ow[MAX << 2];
ev evs[MAX << 1];
int main() {
	int n, i;
	while(scanf("%d", &n) != EOF) {
		for(i = 0; i < n; i++)
			S[i] = i, sz[i] = 1;
		for(i = 0; i < n; i++) {
			scanf("%d %d %d %d", &x[i], &y[i], &w[i], &h[i]);
			evs[2*i] = ev(x[i], true, i);
			evs[2*i+1] = ev(x[i] + w[i], false, i);
			ar[i] = ll(w[i]) * ll(h[i]);
		}
		sort(evs, evs + 2 * n);
		set<int, cmp> s;
		int sz;
		ll px = LLONG_MIN;
		for(i = 0; i < 2 * n; i++) {
			if(px < evs[i].x) { px = evs[i].x; sz = 0; }
			//printf("ev x %d in %d i %d\n", evs[i].x, evs[i].in, evs[i].i);
			int j = evs[i].i;
			if(!evs[i].in) {
				s.erase(j);
				ys[sz] = y[j]; ow[sz++] = j;
				ys[sz] = y[j] + h[j]; ow[sz++] = j;
				continue;
			}
			int l = lower_bound(ys, ys + sz, y[j]) - ys;
			int r = upper_bound(ys, ys + sz, y[j] + h[j]) - ys;
			//printf("r%d - l%d %d\n", r, l, r - l);
			if(l & 1) l--;
			for(j = l; j < r; j++)
				join(evs[i].i, ow[j]);
			auto it = s.insert(evs[i].i).first;
			//printf("size %d\n", s.size());
			if(next(it) != s.end() && touch(*next(it), *it)) join(*next(it), *it);
			if(it != s.begin() && touch(*prev(it), *it)) join(*prev(it), *it);
		}
		ll mx = 0;
		for(i = 0; i < n; i++)
			if(S[i] == i) {
				mx = max(mx, ar[i]);
			}
		printf("%lld\n", mx);
	}
}
