#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

char c;
inline void rd(int &x) {
	while(isspace(c = getchar_unlocked()));
	x = (c - '0');
	while(isdigit(c = getchar_unlocked()))
		x = (x << 3) + (x << 1) + (c - '0');
}

int A[3002][3002];
const int bad = -100000;

const int NN = 31234567;
struct seg_i {
	int l, r;
	int i;
	inline bool empty() { return l > r; }
	inline bool bad() { return i == ::bad; }
} seg[NN];

struct ord {
	bool operator ()(int a, int b) {
		if(seg[a].l != seg[b].l)
			return seg[a].l < seg[b].l;
		return a < b;
	}
};

struct val {
	bool operator()(int a, int b) {
		if(seg[a].i != seg[a].i)
			return seg[a].i < seg[b].i;
		return a < b;
	}
};

const int N = 112345;
set<int, ord> s[N];
set<int, val> by_i;

const int M = 3123 << 2;
int tr[M]; ll lz[M];
ll sum[M];

void unlaze(int i, int l, int r) {
	tr[i] += lz[i];
	sum[i] += ll(r - l + 1) * lz[i];
	if(l != r)
		lz[2 * i] += lz[i],
		lz[2 * i + 1] += lz[i];
	lz[i] = 0;
}

void add(int i, int l, int r, int ql, int qr, int x) {
	if(i == 1) {
		//printf("adding %d to (%d, %d)\n", x, ql, qr);
	}
	unlaze(i, l, r);
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) {
		lz[i] = x;
		unlaze(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	add(2 * i, l, m, ql, qr, x);
	add(2 * i + 1, m + 1, r, ql, qr, x);
	tr[i] = max(tr[2 * i], tr[2 * i + 1]);
	sum[i] = sum[2 * i] + sum[2 * i + 1];
}

pii get(int i, int l, int r, int ql, int qr) {
	unlaze(i, l, r);
	if(l > qr || r < ql) return pii(LLONG_MIN, 0);
	if(l >= ql && r <= qr) return pii(tr[i], sum[i]);
	int m = (l + r) / 2;
	pii A = get(2 * i, l, m, ql, qr);
	pii B = get(2 * i + 1, m + 1, r, ql, qr);
	return pii(max(A.first, B.first), A.second + B.second);
}

int en = 1;
int n, m;

void add_inter(int x, int sid) {
	seg_i &S = seg[sid];
	assert(!S.bad());
	//printf("add_inter(%d, (%d, %d) i %d)\n", x, S.l, S.r, S.i);
	auto it = prev(s[x].upper_bound(sid));
	if(seg[*it].r > S.r) {
		if(seg[*it].i == bad)
			add(1, 0, m - 1, S.l, S.r, 1);
		seg[en] = seg_i{S.r + 1, seg[*it].r, seg[*it].i};
		seg[*it].r = S.l - 1;
		s[x].insert(en);
		if(seg[*it].empty()) {
			by_i.erase(*it);
			s[x].erase(it);
		}
		if(!seg[en].bad()) by_i.insert(en);
		assert(en < NN);
		en++;
		s[x].insert(sid);
		by_i.insert(sid);
		return;
	}
	if(seg[*it].i == bad)
		add(1, 0, m - 1, S.l, seg[*it].r, 1);
	seg[*it].r = seg[sid].l - 1;
	if(seg[*it].empty()) {
		by_i.erase(*it);
		s[x].erase(it);
	}
	while(true) {
		it = s[x].upper_bound(sid);
		if(it == s[x].end()) break;
		seg_i &T = seg[*it];
		if(T.l > S.r) break;
		if(T.r <= S.r) {
			if(T.bad())
				add(1, 0, m - 1, T.l, T.r, 1);
			else
				by_i.erase(*it);
			s[x].erase(it);
		} else { // break it
			int j = *it;
			s[x].erase(it);
			if(T.bad())
				add(1, 0, m - 1, T.l, S.r, 1);
			T.l = S.r + 1;
			s[x].insert(j);
			break;
		}
	}
	s[x].insert(sid);
	by_i.insert(sid);
}

ll best; ll tot;
int main () {
	int i, j, k, g;
	rd(n); rd(m); rd(k);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			rd(A[i][j]);
	for(i = 0; i < N; i++) {
		seg[en] = seg_i{0, m - 1, bad};
		assert(en < NN);
		s[i].insert(en++);
	}
	for(i = 0; i < n; i++) {
		//printf("=== ITERATION %d ===\n", i);
		while(!by_i.empty() && seg[*by_i.begin()].i <= i - k) {
			int j = *by_i.begin();
			//printf("removing (%d, %d) i %d\n", seg[j].l, seg[j].r, seg[j].i);
			by_i.erase(by_i.begin());
			assert(!seg[j].bad());
			seg[j].i = bad;
			add(1, 0, m - 1, seg[j].l, seg[j].r, -1);
		}
		for(j = 0; j < m; j++) {
			seg[en] = seg_i{max(j - k + 1, 0), j, i};
			assert(en < NN);
			add_inter(A[i][j], en++);
		}
		//printf("\n");
		if(i >= k - 1) {
			pii g = get(1, 0, m - 1, 0, m - k);
			//printf("mx %lld sum %lld\n", g.first, g.second);
			best = max(best, g.first);
			tot += g.second;
		}
	}
	printf("%d %lld\n", best, tot);
}
