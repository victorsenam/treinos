#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct seg {
	int l, r;
	int c;
	bool operator < (seg o) const { return l < o.l; }
} s[1123];

struct qu {
	int l, r;
	int k, i;
	void read(int i) {
		scanf("%d %d %d", &l, &k, &r);
		r += l;
		this->i = i;
	}
	bool operator < (qu o) const { return l < o.l; }
} q[1123456];

bool ok[1123456];

int pos[112345];

int main () {
	//printf("%lld\n", LLONG_MAX);
	//printf("%llu\n", ULLONG_MAX);
	int i, n, p;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d %d %d", &s[i].c, &s[i].l, &s[i].r);
	sort(s, s + n);
	scanf("%d", &p);
	for(i = 0; i < p; i++)
		q[i].read(i);
	sort(q, q + p);
	int j = 0;
	for(i = 0; i <= 100000; i++) pos[i] = -1;
	pos[0] = 2.03e9;
	for(i = 0; i < p; i++) {
		for(; j < n && s[j].l <= q[i].l; j++)
			for(int S = 100000; S >= s[j].c; S--)
				pos[S] = max(pos[S], min(pos[S - s[j].c], s[j].r));
		ok[q[i].i] = (q[i].r < pos[q[i].k]);
		//printf("[%d] ans [%d, %d] = (%d <= %d)\n", q[i].i, q[i].l, q[i].r, pos[q[i].k], q[i].r);
	}
	for(i = 0; i < p; i++)
		puts(ok[i]? "TAK" : "NIE");
}
