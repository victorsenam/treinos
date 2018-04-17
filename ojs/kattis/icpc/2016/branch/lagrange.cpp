#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back
typedef pair<long double,ll> pdd;

const int N = 5123;

int n, b, s, r;
vector<pii> adj[N];
vector<pii> inv[N];
ll dist[2][N];
pdd memo[N];
ll acc[N];

pdd dp (double c) {
	for (int i = 1; i <= b; i++) {
		memo[i] = pdd(acc[i]*(i-1) + c, 1);
		for (int j = 1; j < i; j++)
			memo[i] = min(memo[i], pdd((acc[i] - acc[j])*(i-j-1) + memo[j].first + c, memo[j].second + 1));
	}
	return memo[b];
}

int main () {
	scanf("%d %d %d %d", &n, &b, &s, &r);

	for (int i = 0; i < n; i++) dist[0][i] = dist[1][i] = LLONG_MAX;
	
	for (int i = 0; i < r; i++) {
		int s, t, l;
		scanf("%d %d %d", &s, &t, &l);
		s--; t--;
		adj[s].pb(pii(t,l));
		inv[t].pb(pii(s,l));
	}

	priority_queue<pii> pq;
	pq.push(pii(0,b));

	while (!pq.empty()) {
		int u = pq.top().second; int w = -pq.top().first;
		pq.pop();

		if (dist[0][u] <= w) continue;
		dist[0][u] = w;
		
		for (pii ed : adj[u]) {
			pq.push(pii(-w-ed.second,ed.first));
		}
	}

	pq.push(pii(0,b));
	while (!pq.empty()) {
		int u = pq.top().second; int w = -pq.top().first;
		pq.pop();

		if (dist[1][u] <= w) continue;
		dist[1][u] = w;
		dist[0][u] += w;
		
		for (pii ed : inv[u]) {
			pq.push(pii(-w-ed.second,ed.first));
		}
	}

	sort(dist[0], dist[0]+b);
	acc[0] = 0;
	for (int i = 1; i <= b; i++) {
		acc[i] = acc[i-1] + dist[0][i-1];
	}

	ll lo = 0, hi = 20002*n;
	int ts = 70;

	while (lo < hi) {
		ll md = (lo+hi)/2;
		if (dp(double(md)/2).second <= s) hi = md;
		else lo = md + 1;
	}
	double opt = double(lo)/2; 

	//cout << "custo " << opt << endl;
	pdd aaa = dp(opt);
	//cout << aaa.first << "|" << aaa.second << endl;

	printf("%lld\n", ll(round(aaa.first - (opt*s) + 1e-8)));
}
