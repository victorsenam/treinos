#include <bits/stdc++.h>
#define debug if (1)

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;
const int K = 20;

int n;
vector<int> adj[N];

int cn_sz[N];
int cn_dep[N]; // depth on cent tree
ll res[N];
char c[N];
ll mp[(1<<K)];

inline int mnt (char c) { return (1<<(c-'a')); }

int cn_getsz (int u, int p) {
	cn_sz[u] = 1;
	for (int v : adj[u]) {
		if (p == v || cn_sz[v] == -1) continue;
		cn_sz[u] += cn_getsz(v,u);
	}
	return cn_sz[u];
}

void cn_put (int u, int p, int b, int x) {
	b ^= mnt(c[u]);
	mp[b] += x;
	for (int v : adj[u]) {
		if (p == v || cn_sz[v] == -1) continue;
		cn_put(v, u, b, x);
	}
}

ll cn_calc (int u, int p, int b) {
	b ^= mnt(c[u]);
	ll rr = mp[b];
	for (int k = 0; k < 20; k++) rr += mp[b^(1<<k)];
	for (int v : adj[u]) {
		if (p == v || cn_sz[v] == -1) continue;
		rr += cn_calc(v, u, b);
	}
	res[u] += rr;
	return rr;
}

int cn_build (int u, int depth) {
	int siz = cn_getsz(u,u);
	int w = u;
	do {
		u = w;
		for (int v : adj[u]) {
			if (cn_sz[v] == -1 || cn_sz[v] >= cn_sz[u] || cn_sz[v] + cn_sz[v] < siz)
				continue;
			w = v;
		}
	} while (u != w);

	ll tr = 1;
	mp[0] = 1;
	for (int v : adj[u]) if(cn_sz[v] != -1)
		cn_put(v,u,0,1);
	tr += mp[mnt(c[u])];
	for (int k = 0; k < 20; k++) tr += mp[mnt(c[u])^(1<<k)];
	for (int v : adj[u]) if(cn_sz[v] != -1) {
		cn_put(v,u,0,-1);
		tr += cn_calc(v,u,mnt(c[u]));
		cn_put(v,u,0,1);
	}
	for (int v : adj[u]) if(cn_sz[v] != -1)
		cn_put(v,u,0,-1);
	res[u] += tr/2;
	cn_sz[u] = -1;
	cn_dep[u] = depth;

	for (int v : adj[u]) {
		if (cn_sz[v] == -1) continue;
		int w = cn_build(v, depth+1);
	}
	return u;
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n-1; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		adj[a].pb(b); adj[b].pb(a);
	}
	scanf(" %s", c);

	cn_build(0,0);

	for (int i = 0; i < n; i++)
		printf("%lld ", res[i]);
	printf("\n");
}
