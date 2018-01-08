#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3+7;
vector<int> ch[N];
int vi[N];
int vs;
int n;

int dfs (int u) {
	if (vi[u]) return 0;
	vi[u] = 1;
	vs++;

	if (ch[u].size() == 0) return 2;

	int cnl = 0;
	for (int v : ch[u]) {
		int r = dfs(v);
		if (r == 0) return 0;
		if (r == 2)
			cnl++;
	}

	if (cnl >= 3) return 1;
	return 0;
}

int main () {
	scanf("%d", &n);

	for (int i = 1; i < n; i++) {
		int p;
		scanf("%d", &p);
		p--;
		ch[p].pb(i);
	}

	bool ok = (dfs(0) == 1);
	if (vs != n) ok = 0;
	for (int i = 0; i < n; i++) {
		if (ch[i].size() != 0 && ch[i].size() < 3)
			ok = 0;
	}

	if (ok)
		printf("Yes\n");
	else
		printf("No\n");
}
