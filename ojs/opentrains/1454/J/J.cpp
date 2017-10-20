#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define fst first
#define snd second

const int N = 9123;

int seen[N], var[N], vn, cn;
ll d[N], dif[N];
vector<pii> adj[N], A[N];

void imp() {
	puts("-1 -1");
	exit(0);
}

void go(int u, ll v) {
	if(seen[u] && dif[u] != v) imp();
	if(seen[u]) return;
	seen[u] = 1;
	dif[u] = v;
	var[u] = vn;
	for(pii e : adj[u])
		go(e.fst, v + e.snd);
}

int in[N];
int dd[N];

bool bf(ll all, int st) {
	//printf("===== BF(>=%lld) ====\n", mn);
	for(int i = 0; i <= cn; i++) A[i].clear(), d[i] = all,dd[i] = 0, in[i] = 0;
	for(int i = 1; i <= cn; i++) {
		ll a = var[i], b = dif[i], c = var[i - 1], d = dif[i - 1];
		A[a].pb(pii(c, b - d));
		//printf("(%d, %d) with %lld\n", a, c, b - d);
	}
	queue<int> q;
	q.push(st); d[st] = 0; in[st] = 1;
	if(all == 0)
		for(int i = 0; i <= cn; i++)
			if(i != st) {
				q.push(i);
				d[i] = 0;
				in[i] = 1;
			}

	while(!q.empty()) {
		int x = q.front(); q.pop();
		in[x] = 0;
		for(pii e : A[x])
			if(d[e.fst] > d[x] + e.snd) {
				int y = e.fst;
				d[y] = d[x] + e.snd;
				if(!in[y]) {
					in[y] = 1;
					q.push(y);
					dd[y] = dd[x] + 1;
					if(dd[y] == cn + 5) return false;
				}
			}
	}
	return true;
}

ll l[N], r[N];
ll s[N], c[N];

int main() {
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%lld %lld %lld", &l[i], &r[i], &s[i]);
		l[i] += 1000000009;
		r[i] += 1000000009;
		l[i] *= 2;
		r[i] *= 2;
		c[cn++] = l[i];
		c[cn++] = r[i];
		//if(l[i] != r[i]) c[cn++] = l[i] + 1;
		//if(l[i] != r[i]) c[cn++] = r[i] - 1;;
		//c[cn++] = l[i] - 1;
		//c[cn++] = r[i] + 1;
	}
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++)
			if(l[i] - 1 >= l[j] && l[i] - 1 <= r[j])
				break;
		if(j < n) c[cn++] = l[i] - 1;
		for(j = 0; j < n; j++)
			if(r[i] + 1 >= l[j] && r[i] + 1 <= r[j])
				break;
		if(j < n) c[cn++] = r[i] + 1;
	}
	sort(c, c + cn);
	cn = unique(c, c + cn) - c;
	for(i = 0; i < n; i++) {
		l[i] = (lower_bound(c, c + cn, l[i]) - c) + 1;
		r[i] = (lower_bound(c, c + cn, r[i]) - c) + 1;
		adj[l[i] - 1].pb(pii(r[i], s[i]));
		adj[r[i]].pb(pii(l[i] - 1, -s[i]));
	}
	for(i = 0; i <= cn; i++) {
		if(seen[i]) continue;
		go(i, 0);
		vn++;
	}
	if(!bf(0, 0)) imp();
	bf(LLONG_MAX, var[cn]);
	printf("%lld ", -d[0] + dif[cn]);

	bf(LLONG_MAX, var[0]);
	printf("%lld\n", d[var[cn]] + dif[cn]);
}
