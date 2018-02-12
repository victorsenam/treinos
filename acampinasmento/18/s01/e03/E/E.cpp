#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct prob {
	ll t, p; int i;
	bool operator < (prob o) const { return t * o.p < o.t * p; }
} p[112];

int n;

#define ep first
#define et second

pii memo[112][1123];
pii solve(int i, int T) {
	if(i == n) return pii(0, 0);
	pii &r = memo[i][T];
	if(r.ep != -1) return r;
	r = solve(i + 1, T);
	if(p[i].t <= T) {
		pii q = solve(i + 1, T - p[i].t);
		q.ep += p[i].p;
		q.et += p[i].t * q.ep;
		if(q.ep > r.ep || (q.ep == r.ep && q.et < r.et))
			r = q;
	}
	return r;
}

vector<int> ans;
void build(int i, int T) {
	if(i == n) return;
	pii r = solve(i, T);
	if(r == solve(i + 1, T)) return build(i + 1, T);
	ans.pb(i);
	return build(i + 1, T - p[i].t);
}

int main() {
	memset(memo, -1, sizeof memo);
	int i, T;
	scanf("%d %d", &n, &T);
	for(i = 0; i < n; i++)
		scanf("%lld %lld", &p[i].t, &p[i].p), p[i].i = i;
	sort(p, p + n);
	solve(0, T);
	build(0, T);
	printf("%d\n", int(ans.size()));
	for(int x : ans) printf("%d ", p[x].i + 1);
	putchar('\n');
}
