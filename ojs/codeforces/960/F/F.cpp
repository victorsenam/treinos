#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 100123;
set<pii> v[N];

ll res = 0;
int n, m;

bool best (pii a, pii b) {
	return a.first <= b.first && a.second >= b.second;
}

void add (int i, pii x) {
	res = max(res, x.second);
	auto it = v[i].lower_bound(x);
	if (it != v[i].end() && best(*it,x)) return;
	if (it != v[i].begin() && best(*prev(it),x)) return;
	while (it != v[i].begin() && best(x,*prev(it))) v[i].erase(prev(it));
	while (it != v[i].end() && best(x,*it)) { it = next(it); v[i].erase(prev(it)); }
	v[i].insert(x);
}

int main () {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		add(i,pii(-1,0));

	for (int i = 0; i < m; i++) {
		int a, b; ll w;
		scanf("%d %d %lld", &a, &b, &w);

		auto it = v[a].lower_bound(pii(w,0));
		add(b, pii(w,prev(it)->second+1));
	}

	printf("%lld\n", res);
}
