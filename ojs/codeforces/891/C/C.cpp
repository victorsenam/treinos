#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+7;

int n, m, q;
int uf[N], wf[N];
int a[N], b[N];
ll w[N];
int p[N];
int t_v[N], t_uf[N], t_wf[N], turn;

vector<int> has_w[N];
vector<int> quer[N];
int ok[N];

int find (int u) {
	if (uf[u] == u) return u;
	return uf[u] = find(uf[u]);
}

void join (int u, int v) {
	if ((u = find(u)) == (v = find(v))) return;
	if (wf[u] < wf[v]) swap(u,v);
	wf[u] += wf[v];
	uf[v] = u;
}

int t_find (int u) {
	if (t_v[u] != turn) { t_v[u] = turn; t_uf[u] = u; t_wf[u] = 1; }
	if (t_uf[u] == u) return u;
	return t_uf[u] = find(t_uf[u]);
}

bool t_join (int u, int v) { 
	if ((u = t_find(u)) == (v = t_find(v))) return 0;
	if (t_wf[u] < t_wf[v]) swap(u,v);
	t_wf[u] += t_wf[v];
	t_uf[v] = u;
	return 1;
}

int main () {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		uf[i] = i;
		wf[i] = 1;
	}

	for (int i = 0; i < m; i++) {
		scanf("%d %d %lld", &a[i], &b[i], &w[i]);
		a[i]--; b[i]--;
		p[i] = i;
	}

	sort(p, p+m, [] (int i, int j) { return w[i] < w[j]; });

	scanf("%d", &q);
	
	for (int i = 0; i < q; i++) {
		ok[i] = 1;
		int k;
		scanf("%d", &k);
		quer[i].reserve(k);
		while (k--) {
			int a;
			scanf("%d", &a);
			quer[i].pb(a-1);
		}

		sort(quer[i].begin(), quer[i].end(), [] (int i, int j) {
			return w[i] > w[j];
		});

		for (int j = 0; j < quer[i].size(); j++) {
			if (!j || w[quer[i][j]] != w[quer[i][j-1]])
				has_w[w[quer[i][j]]].pb(i);
		}
	}

	int cur_ed = 0;
	for (int cw = 1; cw <= 5e5+7; cw++) {
		for (int qr : has_w[cw]) {
			if (!ok[qr]) continue;
			turn++;
			while (!quer[qr].empty() && w[quer[qr].back()] == cw) {
				int u = find(a[quer[qr].back()]);
				int v = find(b[quer[qr].back()]);

				if (!t_join(u,v))
					ok[qr] = 0;

				quer[qr].pop_back();
			}
		}

		while (cur_ed < m && w[p[cur_ed]] == cw) {
			join(a[p[cur_ed]],b[p[cur_ed]]);
			cur_ed++;
		}
	}

	for (int i = 0; i < q; i++) {
		if (ok[i])
			printf("YES\n");
		else
			printf("NO\n");
	}
}
