#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef pii tA;
typedef null_type tB;
typedef tree<tA, tB, less<tA>, rb_tree_tag, tree_order_statistics_node_update> ord_set;
// map: tA -> tB com comparador less<tA>
// pode usar como um map normalmente
// s.find_by_order(k) :: retorna iterador para o k-esimo elemento (0-index) (ou s.end())
// s.order_of_key(x)  :: retorna a qtd de elementos estritamente menores que x

const int N = 1e6+7;

int n, m;
char name[N][20];
int p[N];
ll d[N];
ll vl[N][2];
ll lgst[N];
ll cov[N];
vector<int> adj[N];
int res[N];
ord_set s[2];

void add (ll l, ll r, int i) {
	if (l >= r) return;
	s[1].insert(pii(r,i));
	s[0].insert(pii(l,i));
}

void rem (ll l, ll r, int i) {
	if (l >= r) return;
	s[1].erase(pii(r,i));
	s[0].erase(pii(l,i));
}

ll get (ll i) {
	return s[0].order_of_key(pii(i,N)) - s[1].order_of_key(pii(i,N));
}

void dfs (int u, ll lg) {
	vl[u][0] = LLONG_MAX;
	if (u >= m+1)
		vl[u][0] = 0;
	vl[u][1] = 0;

	lgst[u] = lg + d[u];

	for (int v : adj[u]) {
		dfs(v,lgst[u]);
		vl[u][0] = min(vl[u][0], vl[v][0]);
		vl[u][1] = max(vl[u][1], vl[v][0]);
		cov[u] = max(cov[u], cov[v]);
	}

	vl[u][0] += d[u];
	vl[u][1] = max(cov[u], vl[u][1]);
	add(vl[u][1],vl[u][0],u);
	cov[u] = max(vl[u][0], cov[u]);

	if (u >= m+1)
		cout << name[u] << " ";
	cout << u << ": " << vl[u][1] << " <= L < " << vl[u][0] << " || " << lgst[u] << endl;
}

ll go (int u) {
	add(vl[u][1],vl[u][0],u);
	res[u] -= get(lgst[u]);
	for (int v : adj[u])
		go(v);
	rem(vl[u][1],vl[u][0],u);
}

int main () {
	scanf("%d %d", &n, &m);
	for (int i = m+1; i <= m + n; i++) {
		scanf(" %s %d %lld", name[i], &p[i], &d[i]);
		adj[p[i]].pb(i);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d %lld", &p[i], &d[i]);
		adj[p[i]].pb(i);
	}

	dfs(0,0);

	cout << " ====== " << endl;
	for (int i = m+1; i <= m+n; i++) {
		res[i] = get(lgst[i]);
		cout << name[i] << " --> " << lgst[i] << " " << res[i] << endl;
	}

	s[0].clear(); s[1].clear();
	go(0);

	for (int i = m+1; i <= m+n; i++)
		printf("%s %d\n", name[i], res[i] + 1);
}
